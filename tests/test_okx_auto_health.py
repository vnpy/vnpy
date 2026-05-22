"""Tests for local OKX auto-trading health JSON."""

from __future__ import annotations

import json
from pathlib import Path

from tools.okx_auto_health import evaluate_health, load_state


def test_load_state_returns_empty_when_missing(tmp_path: Path) -> None:
    assert load_state(tmp_path / "missing.json") == {}


def test_evaluate_health_reports_down_when_pid_missing(tmp_path: Path) -> None:
    state_path = tmp_path / "state.json"
    state_path.write_text(json.dumps({"pid": 99999999, "strategy_trading": True}))

    result = evaluate_health(state_path=state_path, pid_path=tmp_path / "missing.pid")

    assert result["status"] == "down"
    assert result["pid_source"] == "state"
    assert "process not alive" in result["reasons"]


def test_evaluate_health_requires_tick_and_strategy(tmp_path: Path) -> None:
    state_path = tmp_path / "state.json"
    state_path.write_text(
        json.dumps(
            {
                "pid": 123,
                "okx_server": "DEMO",
                "contract_ready": True,
                "strategy_inited": True,
                "strategy_trading": True,
                "latest_tick_ts": "2026-05-16T12:00:00+00:00",
                "latest_error": "",
            }
        )
    )
    pid_path = tmp_path / "run.pid"
    pid_path.write_text("123")

    result = evaluate_health(
        state_path=state_path,
        pid_path=pid_path,
        now_iso="2026-05-16T12:00:30+00:00",
        process_alive=lambda _pid: True,
    )

    assert result["status"] == "healthy"
    assert result["tick_age_seconds"] == 30.0


def test_evaluate_health_uses_state_pid_without_pid_file(tmp_path: Path) -> None:
    state_path = tmp_path / "state.json"
    state_path.write_text(
        json.dumps(
            {
                "pid": 123,
                "okx_server": "DEMO",
                "contract_ready": True,
                "strategy_inited": True,
                "strategy_trading": True,
                "latest_tick_ts": "2026-05-16T12:00:00+00:00",
                "latest_error": "",
            }
        )
    )

    result = evaluate_health(
        state_path=state_path,
        pid_path=tmp_path / "missing.pid",
        now_iso="2026-05-16T12:00:30+00:00",
        process_alive=lambda _pid: True,
    )

    assert result["status"] == "healthy"
    assert result["pid_source"] == "state"


def test_evaluate_health_falls_back_to_live_state_pid_when_pid_file_stale(tmp_path: Path) -> None:
    state_path = tmp_path / "state.json"
    state_path.write_text(
        json.dumps(
            {
                "pid": 123,
                "okx_server": "DEMO",
                "contract_ready": True,
                "strategy_inited": True,
                "strategy_trading": True,
                "latest_tick_ts": "2026-05-16T12:00:00+00:00",
                "latest_error": "",
            }
        )
    )
    pid_path = tmp_path / "run.pid"
    pid_path.write_text("999")

    result = evaluate_health(
        state_path=state_path,
        pid_path=pid_path,
        now_iso="2026-05-16T12:00:30+00:00",
        process_alive=lambda pid: pid == 123,
    )

    assert result["status"] == "degraded_stale_pid"
    assert result["pid"] == 123
    assert result["pid_source"] == "state"
    assert "pid file stale" in result["reasons"]
    assert "process not alive" not in result["reasons"]


def test_evaluate_health_warns_when_multiple_auto_trading_processes_run(tmp_path: Path) -> None:
    state_path = tmp_path / "state.json"
    state_path.write_text(
        json.dumps(
            {
                "pid": 123,
                "okx_server": "DEMO",
                "contract_ready": True,
                "strategy_inited": True,
                "strategy_trading": True,
                "latest_tick_ts": "2026-05-16T12:00:00+00:00",
                "latest_error": "",
            }
        )
    )
    pid_path = tmp_path / "run.pid"
    pid_path.write_text("123")

    result = evaluate_health(
        state_path=state_path,
        pid_path=pid_path,
        now_iso="2026-05-16T12:00:30+00:00",
        process_alive=lambda _pid: True,
        auto_trading_pids=lambda: [123, 456],
    )

    assert result["status"] == "degraded"
    assert result["auto_trading_pids"] == [123, 456]
    assert "multiple auto-trading processes: 123,456" in result["reasons"]


def test_evaluate_health_warns_live_chan_without_latest_signal_state(tmp_path: Path) -> None:
    state_path = tmp_path / "state.json"
    state_path.write_text(
        json.dumps(
            {
                "pid": 123,
                "okx_server": "DEMO",
                "contract_ready": True,
                "strategy_class": "ChanStrategy",
                "strategy_inited": True,
                "strategy_trading": True,
                "strategy_trade_enabled": True,
                "latest_tick_ts": "2026-05-16T12:00:00+00:00",
                "latest_error": "",
            }
        )
    )
    pid_path = tmp_path / "run.pid"
    pid_path.write_text("123")

    result = evaluate_health(
        state_path=state_path,
        pid_path=pid_path,
        now_iso="2026-05-16T12:00:30+00:00",
        process_alive=lambda _pid: True,
    )

    assert result["status"] == "degraded"
    assert "Chan latest signal missing" in result["reasons"]
