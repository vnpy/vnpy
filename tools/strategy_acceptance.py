from __future__ import annotations

import argparse
import json
import subprocess
import sys
from collections import Counter
from collections.abc import Callable, Sequence
from dataclasses import dataclass
from datetime import datetime, timedelta
from pathlib import Path
from typing import Any


REPO_ROOT = Path(__file__).resolve().parents[1]
VENV_PYTHON = REPO_ROOT / ".venv" / "bin" / "python"
PYTHON = VENV_PYTHON if VENV_PYTHON.exists() else Path(sys.executable)


class AcceptanceError(RuntimeError):
    """Raised when acceptance configuration or execution fails."""


@dataclass(frozen=True)
class GateResult:
    """Result for a single acceptance gate."""

    strategy: str
    gate: str
    passed: bool
    summary: str


CommandRunner = Callable[[Sequence[str]], subprocess.CompletedProcess[str]]


CHAN_UNIT_TESTS = [
    "tests/test_chan_objects.py",
    "tests/test_chan_cases.py",
    "tests/test_chan_normalizer.py",
    "tests/test_chan_fractal.py",
    "tests/test_chan_stroke.py",
    "tests/test_chan_segment.py",
    "tests/test_chan_pivot.py",
    "tests/test_chan_trend.py",
    "tests/test_chan_signal.py",
    "tests/test_chan_analyzer.py",
]

CHAN_STRATEGY_TESTS = [
    "tests/test_chan_strategy.py",
]

CHAN_RUNTIME_TESTS = [
    "tests/test_auto_trading_wiring.py",
    "tests/test_telegram_async.py",
    "tests/test_okx_auto_health.py",
    "tests/test_okx_auto_trading_script.py",
]

DOUBLE_MA_UNIT_TESTS = [
    "tests/test_dynamic_sizing.py",
    "tests/test_risk_engine.py",
]

DOUBLE_MA_STRATEGY_TESTS = [
    "tests/test_auto_trading_wiring.py",
]

DOUBLE_MA_RUNTIME_TESTS = [
    "tests/test_telegram_async.py",
    "tests/test_okx_auto_health.py",
    "tests/test_okx_auto_trading_script.py",
]

GATE_ORDER = ["unit", "strategy", "runtime", "backtest"]
STRATEGY_GATES = {
    "chan": {
        "unit": CHAN_UNIT_TESTS,
        "strategy": CHAN_STRATEGY_TESTS,
        "runtime": CHAN_RUNTIME_TESTS,
        "backtest": [],
        "all": [],
    },
    "double_ma": {
        "unit": DOUBLE_MA_UNIT_TESTS,
        "strategy": DOUBLE_MA_STRATEGY_TESTS,
        "runtime": DOUBLE_MA_RUNTIME_TESTS,
        "backtest": [],
        "all": [],
    }
}

BACKTEST_CONFIGS = {
    "chan": "config/trading_config_chan_signal_only.example.json",
    "double_ma": "config/trading_config.json",
}


def get_strategy_gates(strategy: str) -> dict[str, list[str]]:
    """Return gate definitions for a strategy."""

    try:
        return STRATEGY_GATES[strategy]
    except KeyError as exc:
        raise AcceptanceError(f"unknown strategy: {strategy}") from exc


def resolve_gate_sequence(strategy: str, gate: str) -> list[str]:
    """Resolve one gate or all gates into execution order."""

    gates = get_strategy_gates(strategy)
    if gate == "all":
        return list(GATE_ORDER)
    if gate not in gates:
        raise AcceptanceError(f"unknown gate: {gate}")
    return [gate]


def run_command(command: Sequence[str]) -> subprocess.CompletedProcess[str]:
    """Run a subprocess command from the repository root."""

    return subprocess.run(
        list(command),
        cwd=REPO_ROOT,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        check=False,
    )


def run_pytest_gate(
    strategy: str,
    gate: str,
    files: Sequence[str],
    runner: CommandRunner = run_command,
) -> GateResult:
    """Run a pytest-backed gate."""

    command = [str(PYTHON), "-m", "pytest", *files, "-q"]
    completed = runner(command)
    if completed.returncode != 0:
        output = completed.stdout.strip().splitlines()
        tail = "\n".join(output[-20:])
        raise AcceptanceError(
            f"{strategy}.{gate} failed with exit code {completed.returncode}\n{tail}"
        )
    return GateResult(
        strategy=strategy,
        gate=gate,
        passed=True,
        summary=f"{strategy}.{gate}: pytest passed for {len(files)} file(s)",
    )


def run_gate(
    strategy: str,
    gate: str,
    runner: CommandRunner = run_command,
) -> GateResult:
    """Run one acceptance gate."""

    gates = get_strategy_gates(strategy)
    if gate == "backtest":
        return run_backtest_gate(strategy, runner)
    files = gates[gate]
    return run_pytest_gate(strategy, gate, files, runner)


def build_backtest_command(strategy: str) -> list[str]:
    """Build a configured acceptance backtest command."""

    try:
        config_path = BACKTEST_CONFIGS[strategy]
    except KeyError as exc:
        raise AcceptanceError(f"backtest gate is not implemented for {strategy}") from exc

    script = (
        "from tools.strategy_acceptance import run_configured_backtest\n"
        "\n"
        f"print('ACCEPTANCE_BACKTEST_REPORT', run_configured_backtest('{strategy}', '{config_path}'))\n"
    )
    return [str(PYTHON), "-c", script]


def run_configured_backtest(strategy: str, config_path: str) -> str:
    """Run a side-effect-light configured backtest and return JSON evidence."""

    from trading_config import load_trading_config, resolve_trading_config_path
    from vnpy.trader.constant import Interval
    from vnpy_ctastrategy.backtesting import BacktestingEngine
    from vnpy_ctastrategy.strategies.chan_strategy import ChanStrategy
    from vnpy_ctastrategy.strategies.double_ma_strategy import DoubleMaStrategy

    resolved_config_path = resolve_trading_config_path(Path(config_path)).resolve()
    config = load_trading_config(resolved_config_path)
    strategy_config = config["strategy"]
    backtest_config = config["backtest"]
    setting = dict(strategy_config.get("setting", {}))
    if "trade_enabled" in setting:
        setting["trade_enabled"] = bool(backtest_config.get("trade_enabled", True))

    end_date = datetime.now()
    days = int(backtest_config.get("days", 90))
    start_date = end_date - timedelta(days=days)

    engine = BacktestingEngine()
    interval = Interval(backtest_config.get("interval", "1h"))
    engine.set_parameters(
        vt_symbol=strategy_config["vt_symbol"],
        interval=interval,
        start=start_date,
        end=end_date,
        rate=backtest_config.get("rate", 0.0005),
        slippage=backtest_config.get("slippage", 0.1),
        size=backtest_config.get("size", 1),
        pricetick=backtest_config.get("pricetick", 0.0001),
        capital=backtest_config["capital"],
    )

    strategy_class = ChanStrategy if strategy == "chan" else DoubleMaStrategy
    engine.add_strategy(strategy_class=strategy_class, setting=setting)
    engine.load_data()
    bar_count = len(engine.history_data)
    if bar_count <= 0:
        raise AcceptanceError(
            f"{strategy}.backtest loaded no bars for {strategy_config['vt_symbol']}"
        )

    signal_counts = _count_chan_signals(engine.history_data, setting) if strategy == "chan" else {}
    engine.run_backtesting()
    if any("Traceback" in log or "触发异常" in log for log in engine.logs):
        raise AcceptanceError(f"{strategy}.backtest failed during replay")

    engine.calculate_result()
    stats = engine.calculate_statistics(output=False)
    evidence = build_backtest_evidence(
        strategy=strategy,
        strategy_class_name=strategy_class.__name__,
        config_path=str(resolved_config_path),
        vt_symbol=strategy_config["vt_symbol"],
        interval=interval.value,
        start_date=start_date.strftime("%Y-%m-%d"),
        end_date=end_date.strftime("%Y-%m-%d"),
        bar_count=bar_count,
        signal_counts=signal_counts,
        order_count=len(engine.get_all_orders()),
        trade_count=int(stats.get("total_trade_count", 0)),
        total_return=float(stats.get("total_return", 0)),
        sharpe_ratio=float(stats.get("sharpe_ratio", 0)),
        max_drawdown=float(stats.get("max_ddpercent", 0)),
        final_position=float(getattr(engine.strategy, "pos", 0)),
        strategy_setting=setting,
    )
    return json.dumps(evidence, sort_keys=True)


def build_backtest_evidence(
    *,
    strategy: str,
    strategy_class_name: str,
    config_path: str,
    vt_symbol: str,
    interval: str,
    start_date: str,
    end_date: str,
    bar_count: int,
    signal_counts: dict[str, Any],
    order_count: int,
    trade_count: int,
    total_return: float,
    sharpe_ratio: float,
    max_drawdown: float,
    final_position: float,
    strategy_setting: dict[str, Any],
) -> dict[str, Any]:
    """Build normalized backtest evidence for acceptance reports."""

    return {
        "strategy": strategy,
        "strategy_class": strategy_class_name,
        "config_path": config_path,
        "vt_symbol": vt_symbol,
        "interval": interval,
        "start_date": start_date,
        "end_date": end_date,
        "bar_count": bar_count,
        "signal_counts": signal_counts,
        "order_count": order_count,
        "trade_count": trade_count,
        "total_return": total_return,
        "sharpe_ratio": sharpe_ratio,
        "max_drawdown": max_drawdown,
        "final_position": final_position,
        "sizing_mode": strategy_setting.get("sizing_mode", "fixed"),
        "target_long_ratio": strategy_setting.get("target_long_ratio", 0),
        "risk_per_trade": strategy_setting.get("risk_per_trade", 0),
        "atr_multiplier": strategy_setting.get("atr_multiplier", 0),
        "max_position": strategy_setting.get("max_position", 0),
        "max_position_value": strategy_setting.get("max_position_value", 0),
        "max_position_ratio": strategy_setting.get("max_position_ratio", 0),
        "max_order_value": strategy_setting.get("max_order_value", 0),
    }


def _count_chan_signals(bars: Sequence[Any], setting: dict[str, Any]) -> dict[str, dict[str, int]]:
    """Count Chan buy and sell signals from loaded bars."""

    from vnpy.chan import ChanAnalyzer, ChanConfig

    config = ChanConfig(
        min_stroke_gap=setting.get("min_stroke_gap", 1),
        strict_stroke=setting.get("strict_stroke", False),
        pivot_min_segments=setting.get("pivot_min_segments", 3),
        pivot_tolerance=setting.get("pivot_tolerance", 0),
        third_buy_pullback_tolerance=setting.get("third_buy_pullback_tolerance", 0),
        second_buy_low_tolerance=setting.get("second_buy_low_tolerance", 0),
        max_bars=setting.get("max_bars"),
    )
    analyzer = ChanAnalyzer(config)
    buy_counts: Counter[str] = Counter()
    sell_counts: Counter[str] = Counter()

    for bar in bars:
        snapshot = analyzer.update_bar(bar)
        for signal in snapshot.signals:
            buy_counts[signal.type.value] += 1
        for signal in snapshot.sell_signals:
            sell_counts[signal.type.value] += 1

    return {
        "buy": dict(sorted(buy_counts.items())),
        "sell": dict(sorted(sell_counts.items())),
    }


def run_backtest_gate(
    strategy: str,
    runner: CommandRunner = run_command,
) -> GateResult:
    """Run the configured strategy backtest gate."""

    completed = runner(build_backtest_command(strategy))
    if completed.returncode != 0:
        output = completed.stdout.strip().splitlines()
        tail = "\n".join(output[-40:])
        raise AcceptanceError(
            f"{strategy}.backtest failed with exit code {completed.returncode}\n{tail}"
        )
    summary_line = _find_last_line(completed.stdout, "ACCEPTANCE_BACKTEST_REPORT")
    if not summary_line:
        raise AcceptanceError(f"{strategy}.backtest missing report marker")
    return GateResult(
        strategy=strategy,
        gate="backtest",
        passed=True,
        summary=summary_line or "chan.backtest: completed",
    )


def _find_last_line(output: str, marker: str) -> str:
    """Return the last output line containing marker."""

    matches = [line for line in output.splitlines() if marker in line]
    return matches[-1] if matches else ""


def build_parser() -> argparse.ArgumentParser:
    """Build CLI parser."""

    parser = argparse.ArgumentParser(description="Run strategy acceptance gates.")
    parser.add_argument("--strategy", required=True)
    parser.add_argument("--gate", required=True)
    return parser


def main(argv: Sequence[str] | None = None) -> int:
    """Run acceptance gates from CLI arguments."""

    parser = build_parser()
    args = parser.parse_args(argv)
    try:
        for gate in resolve_gate_sequence(args.strategy, args.gate):
            result = run_gate(args.strategy, gate)
            print(result.summary)
    except AcceptanceError as exc:
        print(str(exc), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
