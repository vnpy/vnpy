"""
Batch download OKX historical bars into the local vnpy database.

Example:
    python tools/download_history.py \\
        --symbol DOGEUSDT_SWAP_OKX \\
        --exchange GLOBAL \\
        --interval 15m \\
        --start 2024-04-01 --end 2026-04-01

The symbol must match what OKX datafeed exposes (see Datafeed._map_symbol):
  SPOT:    {base}{quote}_SPOT_OKX   e.g. BTCUSDT_SPOT_OKX
  SWAP:    {base}{quote}_SWAP_OKX   e.g. DOGEUSDT_SWAP_OKX
  FUTURES: {base}{quote}_{expiry}_OKX

Chunks the range into monthly windows, retries each window with exponential
backoff, and persists results via the configured vnpy database.
"""

from __future__ import annotations

import argparse
import sys
import time
from datetime import datetime, timedelta
from pathlib import Path

# Ensure repo root is importable when invoked directly.
REPO_ROOT = Path(__file__).resolve().parents[1]
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.database import get_database
from vnpy.trader.object import HistoryRequest

try:
    from vnpy_okx import Datafeed
except (ImportError, AttributeError):
    from vnpy_okx.vnpy_okx import Datafeed


INTERVAL_MAP: dict[str, Interval] = {
    "1m": Interval.MINUTE,
    "15m": Interval.MINUTE_15,
    "1h": Interval.HOUR,
    "1H": Interval.HOUR,
    "1d": Interval.DAILY,
    "1D": Interval.DAILY,
}

MAX_ATTEMPTS = 5
INITIAL_BACKOFF = 2.0


def iter_monthly_windows(start: datetime, end: datetime):
    cursor = start
    while cursor < end:
        nxt_month = cursor.month + 1
        nxt_year = cursor.year + (1 if nxt_month > 12 else 0)
        nxt_month = nxt_month - 12 if nxt_month > 12 else nxt_month
        nxt = datetime(nxt_year, nxt_month, 1)
        yield cursor, min(nxt, end)
        cursor = nxt


def fetch_window_with_retry(
    datafeed: Datafeed,
    symbol: str,
    exchange: Exchange,
    interval: Interval,
    start: datetime,
    end: datetime,
) -> list:
    req = HistoryRequest(
        symbol=symbol,
        exchange=exchange,
        interval=interval,
        start=start,
        end=end,
    )

    last_exc: Exception | None = None
    for attempt in range(1, MAX_ATTEMPTS + 1):
        try:
            bars = datafeed.query_bar_history(req, print)
            return bars
        except Exception as exc:  # noqa: BLE001
            last_exc = exc
            backoff = INITIAL_BACKOFF * (2 ** (attempt - 1))
            print(
                f"[retry {attempt}/{MAX_ATTEMPTS}] {start:%Y-%m-%d}~{end:%Y-%m-%d} "
                f"failed: {exc!r}. sleeping {backoff:.1f}s"
            )
            time.sleep(backoff)

    raise RuntimeError(
        f"all {MAX_ATTEMPTS} attempts failed for {start:%Y-%m-%d}~{end:%Y-%m-%d}"
    ) from last_exc


def main() -> int:
    parser = argparse.ArgumentParser(description="OKX bar history batch downloader")
    parser.add_argument("--symbol", required=True, help="e.g. DOGEUSDT_SWAP_OKX")
    parser.add_argument("--exchange", default="GLOBAL", help="vnpy Exchange enum name")
    parser.add_argument("--interval", required=True, choices=list(INTERVAL_MAP.keys()))
    parser.add_argument("--start", required=True, help="YYYY-MM-DD")
    parser.add_argument("--end", required=True, help="YYYY-MM-DD")
    args = parser.parse_args()

    exchange = Exchange[args.exchange]
    interval = INTERVAL_MAP[args.interval]
    start = datetime.strptime(args.start, "%Y-%m-%d")
    end = datetime.strptime(args.end, "%Y-%m-%d")
    if end <= start:
        parser.error("--end must be after --start")

    datafeed = Datafeed()
    if not datafeed.init(print):
        print("OKX datafeed init failed (check ~/.vntrader/connect_okx.json)")
        return 1

    if args.symbol not in datafeed.symbol_map:
        print(
            f"symbol {args.symbol!r} not in OKX instrument map. "
            f"example keys: {list(datafeed.symbol_map.keys())[:5]}"
        )
        return 2

    database = get_database()

    total_bars = 0
    for win_start, win_end in iter_monthly_windows(start, end):
        print(f"=== window {win_start:%Y-%m-%d} ~ {win_end:%Y-%m-%d} ===")
        bars = fetch_window_with_retry(
            datafeed, args.symbol, exchange, interval, win_start, win_end
        )
        if bars:
            database.save_bar_data(bars)
            total_bars += len(bars)
            print(f"  saved {len(bars)} bars")
        else:
            print("  no bars returned")

    print(f"done. total bars saved: {total_bars}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
