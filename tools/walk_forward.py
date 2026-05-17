"""
Walk-forward (rolling out-of-sample) evaluation driver for CTA strategies.

Runs a sequence of non-overlapping OOS backtests over the date range, using the
strategy's default parameter setting. Writes per-window metrics to CSV plus a
summary line with aggregate OOS stats.

Example:
    python tools/walk_forward.py \\
        --strategy double_ma_strategy.DoubleMaStrategy \\
        --vt-symbol DOGEUSDT_SWAP_OKX.GLOBAL \\
        --interval 15m \\
        --start 2024-04-01 --end 2026-04-01 \\
        --train-months 6 --test-months 1 \\
        --capital 10000

Note: this first cut does not re-fit parameters in the train window — it
sanity-checks whether the supplied default setting survives OOS. A GA-per-window
variant can be layered on once walk-forward infrastructure is stable.
"""

from __future__ import annotations

import argparse
import csv
import importlib
import sys
from datetime import datetime
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[1]
if str(REPO_ROOT) not in sys.path:
    sys.path.insert(0, str(REPO_ROOT))

from vnpy.trader.constant import Interval
from vnpy_ctastrategy.backtesting import BacktestingEngine


INTERVAL_MAP: dict[str, Interval] = {
    "1m": Interval.MINUTE,
    "15m": Interval.MINUTE_15,
    "1h": Interval.HOUR,
    "1H": Interval.HOUR,
    "1d": Interval.DAILY,
    "1D": Interval.DAILY,
}


def add_months(dt: datetime, months: int) -> datetime:
    total_month = dt.month - 1 + months
    year = dt.year + total_month // 12
    month = total_month % 12 + 1
    return dt.replace(year=year, month=month, day=1, hour=0, minute=0, second=0, microsecond=0)


def resolve_strategy(dotted: str) -> type:
    """Accept forms like 'double_ma_strategy.DoubleMaStrategy' or a full module path."""
    if "." not in dotted:
        raise ValueError(f"expected 'module.ClassName', got {dotted!r}")

    module_path, class_name = dotted.rsplit(".", 1)
    candidates = [module_path]
    if not module_path.startswith("vnpy"):
        candidates.append(f"vnpy_ctastrategy.strategies.{module_path}")

    last_exc: Exception | None = None
    for candidate in candidates:
        try:
            module = importlib.import_module(candidate)
            return getattr(module, class_name)
        except (ImportError, AttributeError) as exc:  # noqa: PERF203
            last_exc = exc
    raise ImportError(f"could not resolve strategy {dotted!r}: {last_exc!r}")


def iter_test_windows(
    start: datetime,
    end: datetime,
    train_months: int,
    test_months: int,
):
    """
    Yield (train_start, train_end, test_start, test_end).
    Train window precedes each test window; windows roll forward by test_months.
    """
    test_start = add_months(start, train_months)
    while test_start < end:
        test_end = min(add_months(test_start, test_months), end)
        if test_end <= test_start:
            break
        train_start = add_months(test_start, -train_months)
        yield train_start, test_start, test_start, test_end
        test_start = test_end


def run_test_window(
    strategy_class,
    vt_symbol: str,
    interval: Interval,
    test_start: datetime,
    test_end: datetime,
    capital: float,
    rate: float,
    slippage: float,
    size: float,
    pricetick: float,
    setting: dict,
) -> dict:
    engine = BacktestingEngine()
    engine.set_parameters(
        vt_symbol=vt_symbol,
        interval=interval,
        start=test_start,
        end=test_end,
        rate=rate,
        slippage=slippage,
        size=size,
        pricetick=pricetick,
        capital=int(capital),
    )
    engine.add_strategy(strategy_class, setting)
    engine.load_data()
    engine.run_backtesting()
    engine.calculate_result()
    stats = engine.calculate_statistics(output=False)

    return {
        "test_start": test_start.strftime("%Y-%m-%d"),
        "test_end": test_end.strftime("%Y-%m-%d"),
        "total_return_pct": stats.get("total_return", 0.0),
        "sharpe_ratio": stats.get("sharpe_ratio", 0.0),
        "max_ddpercent": stats.get("max_ddpercent", 0.0),
        "profit_days": stats.get("profit_days", 0),
        "loss_days": stats.get("loss_days", 0),
        "total_days": stats.get("total_days", 0),
        "trade_count": stats.get("total_trade_count", 0),
        "end_balance": stats.get("end_balance", capital),
    }


def main() -> int:
    parser = argparse.ArgumentParser(description="Walk-forward OOS evaluation")
    parser.add_argument("--strategy", required=True, help="module.ClassName")
    parser.add_argument("--vt-symbol", required=True, help="e.g. DOGEUSDT_SWAP_OKX.GLOBAL")
    parser.add_argument("--interval", required=True, choices=list(INTERVAL_MAP.keys()))
    parser.add_argument("--start", required=True, help="YYYY-MM-DD")
    parser.add_argument("--end", required=True, help="YYYY-MM-DD")
    parser.add_argument("--train-months", type=int, default=6)
    parser.add_argument("--test-months", type=int, default=1)
    parser.add_argument("--capital", type=float, default=10_000)
    parser.add_argument("--rate", type=float, default=0.0005, help="taker fee, default 5bp")
    parser.add_argument("--slippage", type=float, default=0.0001)
    parser.add_argument("--size", type=float, default=1.0, help="contract multiplier")
    parser.add_argument("--pricetick", type=float, default=0.0001)
    parser.add_argument(
        "--setting",
        default="",
        help="JSON-encoded strategy setting, e.g. '{\"fast_window\":10,\"slow_window\":20}'",
    )
    parser.add_argument("--out", default="", help="output CSV path (default: stdout)")
    args = parser.parse_args()

    start = datetime.strptime(args.start, "%Y-%m-%d")
    end = datetime.strptime(args.end, "%Y-%m-%d")
    interval = INTERVAL_MAP[args.interval]
    strategy_class = resolve_strategy(args.strategy)

    import json
    setting: dict = json.loads(args.setting) if args.setting else {}

    rows: list[dict] = []
    for _train_start, _train_end, test_start, test_end in iter_test_windows(
        start, end, args.train_months, args.test_months
    ):
        print(f"=== OOS window {test_start:%Y-%m-%d} ~ {test_end:%Y-%m-%d} ===")
        try:
            row = run_test_window(
                strategy_class,
                args.vt_symbol,
                interval,
                test_start,
                test_end,
                args.capital,
                args.rate,
                args.slippage,
                args.size,
                args.pricetick,
                setting,
            )
        except Exception as exc:  # noqa: BLE001
            print(f"  window failed: {exc!r}")
            continue
        rows.append(row)
        print(
            f"  return={row['total_return_pct']:.2f}% "
            f"sharpe={row['sharpe_ratio']:.2f} "
            f"maxDD={row['max_ddpercent']:.2f}% "
            f"trades={row['trade_count']}"
        )

    if not rows:
        print("no windows completed")
        return 1

    agg_return = sum(r["total_return_pct"] for r in rows) / len(rows)
    agg_sharpe = sum(r["sharpe_ratio"] for r in rows) / len(rows)
    worst_dd = min((r["max_ddpercent"] for r in rows), default=0.0)
    total_trades = sum(r["trade_count"] for r in rows)

    summary = {
        "test_start": "AGGREGATE",
        "test_end": f"{len(rows)} windows",
        "total_return_pct": agg_return,
        "sharpe_ratio": agg_sharpe,
        "max_ddpercent": worst_dd,
        "profit_days": "",
        "loss_days": "",
        "total_days": "",
        "trade_count": total_trades,
        "end_balance": "",
    }
    rows.append(summary)

    fieldnames = list(rows[0].keys())
    if args.out:
        out_path = Path(args.out)
        out_path.parent.mkdir(parents=True, exist_ok=True)
        with out_path.open("w", newline="") as fh:
            writer = csv.DictWriter(fh, fieldnames=fieldnames)
            writer.writeheader()
            writer.writerows(rows)
        print(f"wrote {out_path}")
    else:
        writer = csv.DictWriter(sys.stdout, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)

    print(
        f"\nAGGREGATE: avg_return={agg_return:.2f}%  avg_sharpe={agg_sharpe:.2f}  "
        f"worst_window_dd={worst_dd:.2f}%  total_trades={total_trades}"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
