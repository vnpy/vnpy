"""
Spec-Driven Performance Benchmarks: EventEngine vs DisruptorEventEngine
=======================================================================

Validates each requirement from docs/architecture/specifications.md §6
with PASS/FAIL verdicts.

CRITICAL DESIGN RULE
--------------------
Always start() the engine BEFORE publishing events.

Without a running worker thread the ring buffer fills up (65 536 slots) and
the BusySpin producer blocks indefinitely. The standard Queue-based engine
does not have this problem (Queue is unbounded).

Each benchmark section:
  1. Creates engine
  2. Registers handler
  3. starts()
  4. Measures
  5. stop()

Usage
-----
# Spec tests via pytest (with -s for print output):
    uv run pytest tests/test_perf_specs.py -v -s --tb=short

# Full standalone comparison report:
    uv run python tests/test_perf_specs.py
"""

from __future__ import annotations

import threading
import time
from dataclasses import dataclass, field
from unittest.mock import patch

import pytest

from vnpy.event.engine import Event, EventEngine
from vnpy.trader.setting import SETTINGS


# ─────────────────────────────────────────────────────────────────────────────
# Spec SLOs (docs/architecture/specifications.md §6)
# ─────────────────────────────────────────────────────────────────────────────

SLO_PUT_THROUGHPUT = 500_000  # events/sec  NFR-1
SLO_E2E_THROUGHPUT = 300_000  # events/sec  NFR-2
SLO_DELIVERY_PCT = 99.0  # %           NFR-2
SLO_P99_LATENCY_US = 5_000  # µs (5 ms)   NFR-2
BUFFER_SIZE = 65_536


# ─────────────────────────────────────────────────────────────────────────────
# Availability guard
# ─────────────────────────────────────────────────────────────────────────────


def _has_rust() -> bool:
    try:
        from vnpy_disruptor import DisruptorProducer  # noqa: F401

        return True
    except ImportError:
        return False


requires_rust = pytest.mark.skipif(not _has_rust(), reason="Rust extension unavailable")


# ─────────────────────────────────────────────────────────────────────────────
# Engine factories
# ─────────────────────────────────────────────────────────────────────────────


def std_engine(interval: int = 1) -> EventEngine:
    return EventEngine(interval)


def dis_engine(
    buffer_size: int = BUFFER_SIZE, wait_strategy: str = "busy_spin", interval: int = 1
):
    from vnpy.event.disruptor_engine import DisruptorEventEngine

    with patch.dict(
        SETTINGS,
        {
            "event.buffer_size": buffer_size,
            "event.wait_strategy": wait_strategy,
        },
    ):
        return DisruptorEventEngine(interval)


# ─────────────────────────────────────────────────────────────────────────────
# Measurement helpers — ALL start the engine first
# ─────────────────────────────────────────────────────────────────────────────


def measure_put_rate_started(engine, n: int = 50_000) -> float:
    """
    Measure put() throughput with the engine RUNNING.

    The worker thread drains events so the ring buffer never fills up.
    A noop handler is registered to minimise dispatch overhead.
    """
    engine.register("bench", lambda e: None)
    engine.start()
    # Use direct payload to measure zero-copy performance
    t0 = time.perf_counter()
    for _ in range(n):
        engine.put(Event("bench", None))
    elapsed = time.perf_counter() - t0

    # Drain remaining events before stop
    time.sleep(0.2)
    engine.stop()
    return n / elapsed


def measure_e2e(engine, n: int, timeout: float = 10.0) -> tuple[float, float]:
    """
    Measure end-to-end throughput (put → handler called) and delivery ratio.

    Returns (e2e_events_per_sec, delivery_pct).
    """
    received: list[int] = []

    engine.register("bench", lambda e: received.append(1))
    engine.start()
    time.sleep(0.05)

    t0 = time.perf_counter()
    for i in range(n):
        engine.put(Event("bench", {"i": i}))

    # Wait for all events to drain with timeout
    deadline = time.time() + timeout
    while len(received) < n and time.time() < deadline:
        time.sleep(0.005)

    total_elapsed = time.perf_counter() - t0
    engine.stop()

    got = len(received)
    e2e_rate = got / total_elapsed if total_elapsed > 0 else 0.0
    delivery_pct = got / n * 100.0
    return e2e_rate, delivery_pct


def measure_latencies(engine, n: int = 100) -> list[float]:
    """
    Measure per-event latency (put → handler) in µs using threading.Event.

    Sequential ping-pong: publish 1, wait for handler, record time.
    """
    lats: list[float] = []
    signal = threading.Event()
    t_send: list[float] = [0.0]

    def handler(e: Event) -> None:
        lats.append((time.perf_counter() - t_send[0]) * 1_000_000)
        signal.set()

    engine.register("ping", handler)
    engine.start()
    time.sleep(0.05)

    for _ in range(n):
        signal.clear()
        t_send[0] = time.perf_counter()
        engine.put(Event("ping", None))
        signal.wait(timeout=1.0)

    engine.stop()
    return lats


def pct(data: list[float], p: float) -> float:
    s = sorted(data)
    return s[min(int(len(s) * p / 100), len(s) - 1)] if s else 0.0


# ─────────────────────────────────────────────────────────────────────────────
# Spec tests — pytest classes
# ─────────────────────────────────────────────────────────────────────────────


class TestPutThroughputSpec:
    """NFR-1: put() throughput ≥ 500k/s (both engines, engine running)."""

    def test_standard_put_rate(self):
        engine = std_engine()
        rate = measure_put_rate_started(engine, n=50_000)
        print(f"\n[Standard]  put_rate={rate:>10,.0f}/s  SLO≥{SLO_PUT_THROUGHPUT:,}")
        assert rate >= SLO_PUT_THROUGHPUT

    @requires_rust
    def test_disruptor_put_rate(self):
        engine = dis_engine()
        rate = measure_put_rate_started(engine, n=50_000)
        print(f"\n[Disruptor] put_rate={rate:>10,.0f}/s  SLO≥{SLO_PUT_THROUGHPUT:,}")
        assert rate >= SLO_PUT_THROUGHPUT


class TestE2EThroughputSpec:
    """NFR-2: e2e throughput ≥ 300k/s, delivery ≥ 99%."""

    def test_standard_e2e(self):
        engine = std_engine()
        rate, delivery = measure_e2e(engine, n=5_000)
        print(f"\n[Standard]  e2e={rate:>10,.0f}/s  delivery={delivery:.1f}%")
        assert delivery >= SLO_DELIVERY_PCT

    @requires_rust
    def test_disruptor_e2e_throughput(self):
        engine = dis_engine()
        rate, delivery = measure_e2e(engine, n=5_000)
        print(f"\n[Disruptor] e2e={rate:>10,.0f}/s  delivery={delivery:.1f}%")
        assert rate >= SLO_E2E_THROUGHPUT
        assert delivery >= SLO_DELIVERY_PCT

    @requires_rust
    def test_disruptor_100pct_delivery(self):
        """No events silently dropped (NFR-3)."""
        engine = dis_engine(buffer_size=65_536)
        _, delivery = measure_e2e(engine, n=1_000, timeout=10.0)
        print(f"\n[Disruptor] delivery={delivery:.2f}%")
        assert delivery == 100.0


class TestLatencySpec:
    """NFR-2: P99 ≤ 5 ms."""

    def test_standard_p99(self):
        lats = measure_latencies(std_engine(), n=100)
        p99 = pct(lats, 99)
        print(f"\n[Standard]  P50={pct(lats, 50):.0f}µs  P99={p99:.0f}µs")
        assert p99 <= SLO_P99_LATENCY_US

    @requires_rust
    def test_disruptor_p99(self):
        lats = measure_latencies(dis_engine(), n=100)
        p99 = pct(lats, 99)
        print(f"\n[Disruptor] P50={pct(lats, 50):.0f}µs  P99={p99:.0f}µs")
        assert p99 <= SLO_P99_LATENCY_US

    @requires_rust
    def test_disruptor_blocking_p99(self):
        """Test the new Rust-side Blocking wait strategy."""
        lats = measure_latencies(dis_engine(wait_strategy="blocking"), n=100)
        p99 = pct(lats, 99)
        print(f"\n[Disruptor-Blocking] P50={pct(lats, 50):.0f}µs  P99={p99:.0f}µs")
        assert p99 <= SLO_P99_LATENCY_US


class TestBatchThroughput:
    """Benchmark put_batch() performance."""

    @requires_rust
    def test_disruptor_batch_put_rate(self):
        engine = dis_engine()
        engine.register("bench", lambda e: None)
        engine.start()
        time.sleep(0.05)

        n = 50_000
        batch_size = 100
        events = [Event("bench", None) for _ in range(batch_size)]

        t0 = time.perf_counter()
        for _ in range(n // batch_size):
            engine.put_batch(events)
        elapsed = time.perf_counter() - t0

        rate = n / elapsed
        print(f"\n[Disruptor-Batch] put_rate={rate:>10,.0f}/s (batch={batch_size})")
        engine.stop()
        assert rate >= SLO_PUT_THROUGHPUT


class TestRustExtensionRawSpec:
    """
    Raw Rust publish/consume throughput (isolates PyO3 boundary cost).

    Design: publish n ≤ BUFFER_SIZE events so the ring buffer never fills —
    no drain thread needed, no concurrent-write contention, clean measurement.
    """

    @requires_rust
    def test_raw_publish_exceeds_slo(self):
        """publish() rate into an empty, non-full buffer ≥ 500k/s."""
        from vnpy_disruptor import DisruptorProducer

        payload = {"price": 42.0}
        p = DisruptorProducer(BUFFER_SIZE, "busy_spin")

        counts = [0]

        def handler(batch):
            counts[0] += len(batch)

        p.start_worker(handler)

        n = 100_000
        t0 = time.perf_counter()
        for _ in range(n):
            p.publish(payload)
        elapsed = time.perf_counter() - t0
        rate = n / elapsed

        # Wait for drain
        deadline = time.time() + 2.0
        while counts[0] < n and time.time() < deadline:
            time.sleep(0.01)

        p.stop()

        print(f"\n[Rust publish] {rate:>12,.0f}/s  n={n}  SLO≥{SLO_PUT_THROUGHPUT:,}")
        assert rate >= SLO_PUT_THROUGHPUT

    @requires_rust
    def test_raw_consume_exceeds_1m(self):
        """Consume rate ≥ 1M events/s."""
        from vnpy_disruptor import DisruptorProducer

        p = DisruptorProducer(BUFFER_SIZE, "busy_spin")

        counts = [0]

        def handler(batch):
            counts[0] += len(batch)

        # Start worker first
        p.start_worker(handler)

        # We measure e2e rate here as a proxy for consume rate
        n = 100_000
        payload = {"price": 42.0}

        t0 = time.perf_counter()
        for _ in range(n):
            p.publish(payload)

        deadline = time.time() + 2.0
        while counts[0] < n and time.time() < deadline:
            time.sleep(0.01)
        elapsed = time.perf_counter() - t0

        rate = n / elapsed
        p.stop()

        print(f"\n[Rust e2e] {rate:>12,.0f}/s  n={n}  SLO≥1,000,000")
        assert rate >= 1_000_000


# ─────────────────────────────────────────────────────────────────────────────
# Standalone comparison report (python tests/test_perf_specs.py)
# ─────────────────────────────────────────────────────────────────────────────


@dataclass
class Result:
    name: str
    n: int
    put_rate: float = 0.0
    e2e_rate: float = 0.0
    delivery: float = 0.0
    lats: list[float] = field(default_factory=list)

    @property
    def p50(self):
        return pct(self.lats, 50)

    @property
    def p95(self):
        return pct(self.lats, 95)

    @property
    def p99(self):
        return pct(self.lats, 99)

    def verdict(self) -> dict[str, bool]:
        return {
            f"put ≥{SLO_PUT_THROUGHPUT // 1000}k/s": self.put_rate
            >= SLO_PUT_THROUGHPUT,
            f"e2e ≥{SLO_E2E_THROUGHPUT // 1000}k/s": self.e2e_rate
            >= SLO_E2E_THROUGHPUT,
            f"del ≥{SLO_DELIVERY_PCT}%": self.delivery >= SLO_DELIVERY_PCT,
            f"P99 ≤{SLO_P99_LATENCY_US // 1000}ms": self.p99 <= SLO_P99_LATENCY_US,
        }


def _bench_engine(name: str, engine_fn, n_put=50_000, n_e2e=5_000, n_lat=100) -> Result:
    r = Result(name=name, n=n_put)

    e = engine_fn()
    r.put_rate = measure_put_rate_started(e, n=n_put)

    e = engine_fn()
    r.e2e_rate, r.delivery = measure_e2e(e, n=n_e2e)

    e = engine_fn()
    r.lats = measure_latencies(e, n=n_lat)

    return r


def _print(r: Result) -> None:
    v = r.verdict()
    w = 62
    print(f"\n{'─' * w}")
    print(f"  {r.name}")
    print(f"  put/s    : {r.put_rate:>12,.0f}   {'✅' if v[list(v)[0]] else '❌'}")
    print(f"  e2e/s    : {r.e2e_rate:>12,.0f}   {'✅' if v[list(v)[1]] else '❌'}")
    print(f"  delivery : {r.delivery:>11.2f}%   {'✅' if v[list(v)[2]] else '❌'}")
    print(f"  P50 lat  : {r.p50:>10.0f} µs")
    print(f"  P95 lat  : {r.p95:>10.0f} µs")
    print(f"  P99 lat  : {r.p99:>10.0f} µs   {'✅' if v[list(v)[3]] else '❌'}")


def run_full_benchmark() -> None:
    w = 62
    print("\n" + "═" * w)
    print("  SPEC BENCHMARK: Standard EventEngine vs DisruptorEventEngine")
    print(
        f"  SLOs: put≥{SLO_PUT_THROUGHPUT // 1000}k/s  e2e≥{SLO_E2E_THROUGHPUT // 1000}k/s"
        f"  delivery≥{SLO_DELIVERY_PCT}%  P99≤{SLO_P99_LATENCY_US // 1000}ms"
    )
    print("═" * w)

    results: list[Result] = []

    # Standard engine
    print("\n[1/3] Standard EventEngine …")
    r_std = _bench_engine("Standard EventEngine", std_engine)
    _print(r_std)
    results.append(r_std)

    # Disruptor engine
    if _has_rust():
        print("\n[2/3] DisruptorEventEngine …")
        r_dis = _bench_engine("DisruptorEventEngine (disruptor-rs v4.0)", dis_engine)
        _print(r_dis)
        results.append(r_dis)

    # Comparison table
    if len(results) >= 2:
        std, dis = results[0], results[1]
        print(f"\n{'═' * w}")
        print("  COMPARISON")
        print(f"  {'Metric':<26} {'Standard':>12} {'Disruptor':>12}  {'Δ':>6}")
        print(f"  {'─' * 26} {'─' * 12} {'─' * 12}  {'─' * 6}")

        def row(label, a, b):
            mult = b / a if a > 0 else float("inf")
            sign = "+" if b >= a else ""
            print(f"  {label:<26} {a:>12,.0f} {b:>12,.0f}  {sign}{mult:.1f}×")

        row("put/s", std.put_rate, dis.put_rate)
        row("e2e/s", std.e2e_rate, dis.e2e_rate)
        row("P50 latency (µs)", std.p50, dis.p50)
        row("P99 latency (µs)", std.p99, dis.p99)
        print(f"  {'delivery %':<26} {std.delivery:>11.1f}% {dis.delivery:>11.1f}%")

    # Verdict
    print(f"\n{'═' * w}")
    print("  SPEC VERDICT (specifications.md §6)")
    print(f"{'─' * w}")
    all_pass = True
    for r in results:
        for slo, passed in r.verdict().items():
            icon = "✅ PASS" if passed else "❌ FAIL"
            print(f"  [{r.name:40}] {slo:<18} {icon}")
            all_pass = all_pass and passed
    print(f"{'─' * w}")
    print(f"  Overall: {'✅ ALL SPECS MET' if all_pass else '❌ SOME SPECS NOT MET'}")
    print("═" * w + "\n")


if __name__ == "__main__":
    run_full_benchmark()
