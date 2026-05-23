from __future__ import annotations

import subprocess

import pytest

from tools import strategy_acceptance


def test_registry_contains_chan_gates() -> None:
    gates = strategy_acceptance.get_strategy_gates("chan")

    assert set(gates) == {"unit", "strategy", "runtime", "backtest", "all"}


def test_registry_contains_double_ma_gates() -> None:
    gates = strategy_acceptance.get_strategy_gates("double_ma")

    assert set(gates) == {"unit", "strategy", "runtime", "backtest", "all"}


def test_unknown_strategy_fails() -> None:
    with pytest.raises(strategy_acceptance.AcceptanceError, match="unknown strategy"):
        strategy_acceptance.get_strategy_gates("missing")


def test_unknown_gate_fails() -> None:
    with pytest.raises(strategy_acceptance.AcceptanceError, match="unknown gate"):
        strategy_acceptance.resolve_gate_sequence("chan", "missing")


def test_all_gate_runs_in_order() -> None:
    sequence = strategy_acceptance.resolve_gate_sequence("chan", "all")

    assert sequence == ["unit", "strategy", "runtime", "backtest"]


def test_pytest_gate_uses_expected_command() -> None:
    seen: list[list[str]] = []

    def fake_runner(command):
        seen.append(list(command))
        return subprocess.CompletedProcess(command, 0, stdout="1 passed\n")

    result = strategy_acceptance.run_pytest_gate(
        "chan",
        "strategy",
        ["tests/test_chan_strategy.py"],
        runner=fake_runner,
    )

    assert result.passed is True
    assert seen[0][1:3] == ["-m", "pytest"]
    assert seen[0][-2:] == ["tests/test_chan_strategy.py", "-q"]


def test_pytest_gate_failure_reports_tail() -> None:
    def fake_runner(command):
        return subprocess.CompletedProcess(command, 1, stdout="line\nFAILED test\n")

    with pytest.raises(strategy_acceptance.AcceptanceError, match="FAILED test"):
        strategy_acceptance.run_pytest_gate(
            "chan",
            "strategy",
            ["tests/test_chan_strategy.py"],
            runner=fake_runner,
        )


def test_chan_backtest_command_contains_config() -> None:
    command = strategy_acceptance.build_backtest_command("chan")

    assert any(
        "config/trading_config_chan_signal_only.example.json" in item
        for item in command
    )
    assert command[0].endswith("python")


def test_backtest_command_avoids_auto_trading_runtime() -> None:
    command = strategy_acceptance.build_backtest_command("chan")
    script = "\n".join(command)

    assert "AutoTradingSystem" not in script
    assert "Telegram" not in script


def test_double_ma_backtest_command_contains_config() -> None:
    command = strategy_acceptance.build_backtest_command("double_ma")

    assert any("config/trading_config.json" in item for item in command)
    assert command[0].endswith("python")


def test_backtest_gate_extracts_report_line() -> None:
    def fake_runner(command):
        return subprocess.CompletedProcess(
            command,
            0,
            stdout="noise\nACCEPTANCE_BACKTEST_REPORT {'trade_count': 7}\n",
        )

    result = strategy_acceptance.run_backtest_gate("chan", runner=fake_runner)

    assert result.passed is True
    assert "trade_count" in result.summary


def test_double_ma_backtest_gate_extracts_report_line() -> None:
    def fake_runner(command):
        return subprocess.CompletedProcess(
            command,
            0,
            stdout="noise\nACCEPTANCE_BACKTEST_REPORT {'trade_count': 155}\n",
        )

    result = strategy_acceptance.run_backtest_gate("double_ma", runner=fake_runner)

    assert result.passed is True
    assert "trade_count" in result.summary


def test_backtest_gate_failure_reports_tail() -> None:
    def fake_runner(command):
        return subprocess.CompletedProcess(command, 1, stdout="bad\nTraceback\n")

    with pytest.raises(strategy_acceptance.AcceptanceError, match="Traceback"):
        strategy_acceptance.run_backtest_gate("chan", runner=fake_runner)


def test_backtest_gate_rejects_missing_report_marker() -> None:
    def fake_runner(command):
        return subprocess.CompletedProcess(command, 0, stdout="backtest swallowed error\n")

    with pytest.raises(strategy_acceptance.AcceptanceError, match="missing report"):
        strategy_acceptance.run_backtest_gate("chan", runner=fake_runner)


def test_backtest_evidence_includes_sizing_fields() -> None:
    report = strategy_acceptance.build_backtest_evidence(
        strategy="chan",
        strategy_class_name="ChanStrategy",
        config_path="/tmp/config.json",
        vt_symbol="BTCUSDT_SWAP_OKX.GLOBAL",
        interval="1h",
        start_date="2025-05-23",
        end_date="2026-05-23",
        bar_count=100,
        signal_counts={"buy": {"first_buy": 1}, "sell": {}},
        order_count=1,
        trade_count=1,
        total_return=1.2,
        sharpe_ratio=0.5,
        max_drawdown=-0.3,
        final_position=0.005,
        strategy_setting={"sizing_mode": "risk_per_trade", "risk_per_trade": 0.01},
    )

    assert report["sizing_mode"] == "risk_per_trade"
    assert report["risk_per_trade"] == 0.01
