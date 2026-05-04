"""
Wait Strategy Performance Comparison: Disruptor vs Standard
=========================================================

Benchmarks the institutional-grade Disruptor engine's wait strategies:
1. busy_spin      (100% CPU, Lowest Latency)
2. busy_spin_hint (High CPU, Low Latency)
3. blocking       (Low CPU, Competitive Latency)
4. Standard Engine (Baseline)
"""

import time
import threading
import statistics
from unittest.mock import patch
from vnpy.event.engine import Event, EventEngine
from vnpy.trader.setting import SETTINGS

# SLOs and Config
N_EVENTS = 500  # Reduced for faster latency sweep
N_TPUT = 50_000 # Sufficient for stable TPS
BUFFER_SIZE = 65536
TIMEOUT = 5.0    # Fail fast

def pct(data, p):
    s = sorted(data)
    return s[min(int(len(s) * p / 100), len(s) - 1)] if s else 0.0

def measure_latency(engine, n=N_EVENTS):
    lats = []
    signal = threading.Event()
    t_send = [0.0]

    def handler(e):
        lats.append((time.perf_counter() - t_send[0]) * 1_000_000)
        signal.set()

    engine.register("bench", handler)
    engine.start()
    time.sleep(0.1)  # Warm up

    for _ in range(n):
        signal.clear()
        t_send[0] = time.perf_counter()
        engine.put(Event("bench", None))
        if not signal.wait(timeout=1.0):
            print("Timeout waiting for event!")
            break

    engine.stop()
    return lats

def measure_throughput(engine, n=N_TPUT):
    received = [0]
    done = threading.Event()

    def handler(e):
        received[0] += 1
        if received[0] == n:
            done.set()

    engine.register("bench", handler)
    engine.start()

    # Pre-create events to avoid loop overhead
    events = [Event("bench", None) for _ in range(100)]

    t0 = time.perf_counter()
    for _ in range(n // 100):
        for e in events:
            engine.put(e)
    
    if not done.wait(timeout=TIMEOUT):
        print(f"    TIMEOUT: only received {received[0]}/{n} events")
    
    elapsed = time.perf_counter() - t0
    engine.stop()
    return received[0] / elapsed

def measure_throughput_batch(engine, n=N_TPUT, batch_size=100):
    received = [0]
    done = threading.Event()

    def handler(e):
        received[0] += 1
        if received[0] == n:
            done.set()

    engine.register("bench", handler)
    engine.start()

    # Pre-create events
    batch_events = [Event("bench", None) for _ in range(batch_size)]
    
    t0 = time.perf_counter()
    for _ in range(n // batch_size):
        engine.put_batch(batch_events)
    
    if not done.wait(timeout=TIMEOUT):
        print(f"    TIMEOUT: only received {received[0]}/{n} events")
    
    elapsed = time.perf_counter() - t0
    engine.stop()
    return received[0] / elapsed

def run_bench(name, engine_factory):
    print(f"\n>>> Benchmarking: {name}")
    try:
        engine = engine_factory()
        
        # Latency
        print("    Measuring latency...")
        lats = measure_latency(engine)
        p50 = pct(lats, 50)
        p99 = pct(lats, 99)
        
        # Throughput (Single Put)
        print("    Measuring throughput (Single)...")
        engine = engine_factory()
        tput_single = measure_throughput(engine, n=N_TPUT)
        
        # Throughput (Batch Put) - only for Disruptor
        tput_batch = 0
        if "Disruptor" in name:
            print("    Measuring throughput (Batch)...")
            engine = engine_factory()
            tput_batch = measure_throughput_batch(engine, n=N_TPUT)
        
        print(f"    P50 Latency: {p50:6.1f} µs")
        print(f"    P99 Latency: {p99:6.1f} µs")
        print(f"    TPS (Single): {tput_single:10,.0f}")
        if tput_batch:
            print(f"    TPS (Batch):  {tput_batch:10,.0f}")
        
        if hasattr(engine, "get_metrics"):
            m = engine.get_metrics()
            print(f"    Metrics:     processed={m['processed_count']:,}, backpressure={m['backpressure_events']}")
        
        return {"name": name, "p50": p50, "p99": p99, "tput_single": tput_single, "tput_batch": tput_batch}
    except Exception as e:
        import traceback
        traceback.print_exc()
        print(f"    FAILED: {e}")
        return None

def main():
    results = []

    # 1. Standard Engine
    results.append(run_bench("Standard Engine (Queue)", lambda: EventEngine()))

    # 2. Disruptor Strategies
    from vnpy.event.disruptor_engine import DisruptorEventEngine
    
    strategies = ["busy_spin", "busy_spin_hint", "yielding", "sleeping", "blocking"]
    for strategy in strategies:
        def factory(s=strategy):
            with patch.dict(SETTINGS, {
                "event.buffer_size": BUFFER_SIZE,
                "event.wait_strategy": s,
            }):
                return DisruptorEventEngine()
        
        results.append(run_bench(f"Disruptor ({strategy})", factory))

    # Summary Table
    print("\n" + "="*85)
    print(f"{'Strategy':<30} | {'P50 (µs)':<10} | {'P99 (µs)':<10} | {'TPS (Single)':<12} | {'TPS (Batch)':<12}")
    print("-" * 85)
    for r in results:
        if r:
            batch_str = f"{r['tput_batch']:>10,.0f}" if r['tput_batch'] else "N/A"
            print(f"{r['name']:<30} | {r['p50']:<10.1f} | {r['p99']:<10.1f} | {r['tput_single']:>12,.0f} | {batch_str:>12}")
    print("="*85)

if __name__ == "__main__":
    main()
