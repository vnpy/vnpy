from __future__ import annotations

import argparse
import json
import sys
from collections import Counter
from datetime import datetime, timedelta
from pathlib import Path
from time import sleep
from typing import Any

import requests


REPO_ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(REPO_ROOT))

from trading_config import load_trading_config, resolve_trading_config_path  # noqa: E402
from vnpy.chan import ChanAnalyzer, ChanConfig  # noqa: E402
from vnpy.trader.constant import Exchange, Interval  # noqa: E402
from vnpy.trader.object import BarData  # noqa: E402
from vnpy_okx.vnpy_okx.okx_gateway import parse_timestamp  # noqa: E402


DEFAULT_STATE_PATH = Path.home() / ".vntrader" / "okx_auto_state.json"
DEFAULT_STRATEGY_DATA_PATH = Path.home() / ".vntrader" / "cta_strategy_data.json"
DEFAULT_LOG_PATH = Path.home() / ".vntrader" / "okx_auto_stdout.log"
DEFAULT_CONFIG_PATH = REPO_ROOT / "config" / "trading_config.json"


def load_json_file(path: Path) -> dict[str, Any]:
    """Load a JSON object from disk, returning an empty object when missing."""
    if not path.exists():
        return {}
    return json.loads(path.read_text())


def is_dust_position(pos: float, position_epsilon: float) -> bool:
    """Return whether a non-zero position is only floating-point dust."""
    return pos != 0 and abs(pos) <= position_epsilon


def extract_strategy_order_lines(log_text: str, strategy_name: str) -> list[str]:
    """Return auto-trading order lines for one CTA strategy."""
    reference = f"CtaStrategy_{strategy_name}"
    return [
        line
        for line in log_text.splitlines()
        if "委托下单" in line and reference in line
    ]


def classify_runtime_gap(
    *,
    pos: float,
    position_epsilon: float,
    live_order_count: int,
    replay_buy_count: int | None,
    latest_error: str,
) -> dict[str, Any]:
    """Classify why live trades are sparse."""
    reasons: list[str] = []

    if latest_error:
        reasons.append("latest error present")

    if is_dust_position(pos, position_epsilon):
        reasons.append("dust position can block exact flat checks")
        status = "execution_blocked"
    elif replay_buy_count is None:
        status = "needs_signal_replay"
    elif replay_buy_count == 0:
        reasons.append("offline replay found no buy signals")
        status = "signal_scarcity"
    elif live_order_count <= 2 and replay_buy_count > live_order_count:
        reasons.append("offline replay found more buy signals than live orders")
        status = "execution_gap"
    else:
        status = "no_gap_detected"

    return {
        "status": status,
        "reasons": reasons,
        "pos": pos,
        "position_epsilon": position_epsilon,
        "live_order_count": live_order_count,
        "replay_buy_count": replay_buy_count,
    }


def build_chan_config(setting: dict[str, Any]) -> ChanConfig:
    """Build Chan analyzer config from strategy settings."""
    return ChanConfig(
        min_stroke_gap=setting.get("min_stroke_gap", 1),
        strict_stroke=setting.get("strict_stroke", True),
        pivot_min_segments=setting.get("pivot_min_segments", 3),
        pivot_tolerance=setting.get("pivot_tolerance", 0),
        third_buy_pullback_tolerance=setting.get("third_buy_pullback_tolerance", 0),
        second_buy_low_tolerance=setting.get("second_buy_low_tolerance", 0),
        max_bars=setting.get("max_bars") or None,
    )


def fetch_okx_1m_bars(start: datetime, end: datetime) -> list[BarData]:
    """Fetch public OKX BTC-USDT-SWAP 1m bars for diagnostics."""
    after = str(int(end.timestamp() * 1000))
    buf: dict[datetime, BarData] = {}

    while True:
        response = requests.get(
            "https://www.okx.com/api/v5/market/history-candles",
            params={
                "instId": "BTC-USDT-SWAP",
                "bar": "1m",
                "limit": "100",
                "after": after,
            },
            timeout=10,
        )
        response.raise_for_status()
        rows = response.json().get("data") or []
        if not rows:
            break

        for row in rows:
            ts, open_price, high_price, low_price, close_price, volume, turnover, _, _ = row
            dt = parse_timestamp(ts).astimezone(start.tzinfo)
            if start <= dt <= end:
                buf[dt] = BarData(
                    symbol="BTCUSDT_SWAP_OKX",
                    exchange=Exchange.GLOBAL,
                    datetime=dt,
                    interval=Interval.MINUTE,
                    volume=float(volume),
                    turnover=float(turnover),
                    open_price=float(open_price),
                    high_price=float(high_price),
                    low_price=float(low_price),
                    close_price=float(close_price),
                    gateway_name="OKX",
                )

        begin = rows[-1][0]
        begin_dt = parse_timestamp(begin).astimezone(start.tzinfo)
        if begin_dt <= start:
            break
        after = begin
        sleep(0.05)

    return [buf[dt] for dt in sorted(buf)]


def replay_chan_signals(
    *,
    start: datetime,
    end: datetime,
    warmup_days: int,
    setting: dict[str, Any],
) -> dict[str, Any]:
    """Replay public OKX bars and count post-start Chan signals."""
    warmup_start = start - timedelta(days=warmup_days)
    bars = fetch_okx_1m_bars(warmup_start, end)
    analyzer = ChanAnalyzer(build_chan_config(setting))
    buy_seen: set[tuple[str, int, float]] = set()
    sell_seen: set[tuple[str, int, float]] = set()
    buy_counts: Counter[str] = Counter()
    sell_counts: Counter[str] = Counter()
    buy_examples: list[dict[str, Any]] = []

    for bar in bars:
        snapshot = analyzer.update_bar(bar)
        if bar.datetime < start:
            continue
        for signal in snapshot.signals:
            key = (signal.type.value, signal.confirmed_index, signal.stop_price)
            if key in buy_seen:
                continue
            buy_seen.add(key)
            buy_counts[signal.type.value] += 1
            if len(buy_examples) < 10:
                buy_examples.append(
                    {
                        "datetime": bar.datetime.isoformat(),
                        "type": signal.type.value,
                        "confirmed_index": signal.confirmed_index,
                        "stop_price": signal.stop_price,
                        "close_price": bar.close_price,
                    }
                )
        for signal in snapshot.sell_signals:
            key = (signal.type.value, signal.confirmed_index, signal.stop_price)
            if key in sell_seen:
                continue
            sell_seen.add(key)
            sell_counts[signal.type.value] += 1

    return {
        "bar_count": len(bars),
        "buy_count": sum(buy_counts.values()),
        "buy_counts": dict(buy_counts),
        "sell_count": sum(sell_counts.values()),
        "sell_counts": dict(sell_counts),
        "buy_examples": buy_examples,
    }


def build_report(args: argparse.Namespace) -> dict[str, Any]:
    """Build a Chan runtime diagnostic report."""
    state = load_json_file(args.state_path)
    strategy_data = load_json_file(args.strategy_data_path)
    config = load_trading_config(resolve_trading_config_path(args.config_path))
    strategy_spec = config["strategy"]
    strategy_name = strategy_spec.get("strategy_name", "Chan_Auto")
    setting = dict(strategy_spec.get("setting", {}))
    runtime = config.get("runtime", {})
    strategy_state = strategy_data.get(strategy_name, {})
    log_text = args.log_path.read_text() if args.log_path.exists() else ""
    order_lines = extract_strategy_order_lines(log_text, strategy_name)
    pos = float(strategy_state.get("pos", 0) or 0)
    position_epsilon = float(setting.get("position_epsilon", 1e-8) or 1e-8)

    replay = None
    if args.replay_signals:
        started_at = datetime.fromisoformat(state["started_at"])
        end = datetime.now().astimezone(started_at.tzinfo)
        replay = replay_chan_signals(
            start=started_at,
            end=end,
            warmup_days=int(runtime.get("init_days", 3)),
            setting=setting,
        )

    return {
        "strategy_name": strategy_name,
        "process": {
            "pid": state.get("pid"),
            "okx_server": state.get("okx_server"),
            "strategy_inited": state.get("strategy_inited"),
            "strategy_trading": state.get("strategy_trading"),
            "strategy_trade_enabled": state.get("strategy_trade_enabled"),
            "latest_tick_ts": state.get("latest_tick_ts"),
            "latest_order_ts": state.get("latest_order_ts"),
            "latest_trade_ts": state.get("latest_trade_ts"),
            "latest_error": state.get("latest_error", ""),
        },
        "strategy_state": {
            "pos": pos,
            "last_signal_key": strategy_state.get("last_signal_key", ""),
            "active_stop_price": strategy_state.get("active_stop_price", 0),
            "active_stop_orderid": strategy_state.get("active_stop_orderid", ""),
            "exit_order_sent": strategy_state.get("exit_order_sent", False),
        },
        "live_orders": {
            "count": len(order_lines),
            "lines": order_lines[-10:],
        },
        "signal_replay": replay,
        "diagnosis": classify_runtime_gap(
            pos=pos,
            position_epsilon=position_epsilon,
            live_order_count=len(order_lines),
            replay_buy_count=replay["buy_count"] if replay else None,
            latest_error=str(state.get("latest_error", "")),
        ),
    }


def parse_args() -> argparse.Namespace:
    """Parse CLI arguments."""
    parser = argparse.ArgumentParser(description="Diagnose Chan live runtime trade gaps.")
    parser.add_argument("--config", dest="config_path", type=Path, default=DEFAULT_CONFIG_PATH)
    parser.add_argument("--state-path", type=Path, default=DEFAULT_STATE_PATH)
    parser.add_argument("--strategy-data-path", type=Path, default=DEFAULT_STRATEGY_DATA_PATH)
    parser.add_argument("--log-path", type=Path, default=DEFAULT_LOG_PATH)
    parser.add_argument("--replay-signals", action="store_true")
    return parser.parse_args()


def main() -> None:
    """Run diagnostics and print JSON evidence."""
    print(json.dumps(build_report(parse_args()), ensure_ascii=False, indent=2))


if __name__ == "__main__":
    main()
