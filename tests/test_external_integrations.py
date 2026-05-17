"""Opt-in tests that touch real external systems.

Run only when VNPY_RUN_EXTERNAL_TESTS=1 is set. The QMT execute test has a
second safety switch: VNPY_RUN_QMT_EXECUTE_TESTS=1.
"""

from __future__ import annotations

from datetime import datetime
import json
import os

import pytest

from tools.external_checks import (
    check_qmt_health,
    check_qmt_positions,
    check_qmt_rebalance,
    check_rdagent_cli,
    check_telegram_get_me,
    check_telegram_send_message,
    execute_enabled,
    external_enabled,
    require_env,
)


pytestmark = pytest.mark.external


def _skip_unless_external() -> None:
    if not external_enabled():
        pytest.skip("set VNPY_RUN_EXTERNAL_TESTS=1 to run real external checks")


def _qmt_probe_payload() -> tuple[dict[str, float], dict[str, float]]:
    weights = json.loads(os.getenv("QMT_TEST_WEIGHTS_JSON", '{"510300.SH": 0.01}'))
    prices = json.loads(os.getenv("QMT_TEST_PRICES_JSON", '{"510300.SH": 4.0}'))
    return {str(k): float(v) for k, v in weights.items()}, {
        str(k): float(v) for k, v in prices.items()
    }


def test_external_qmt_health() -> None:
    _skip_unless_external()
    env = require_env("QMT_BRIDGE_URL")

    payload = check_qmt_health(env["QMT_BRIDGE_URL"])

    assert payload["ok"] is True
    assert "runtime_ok" in payload


def test_external_qmt_positions() -> None:
    _skip_unless_external()
    env = require_env("QMT_BRIDGE_URL", "QMT_BRIDGE_TOKEN")

    payload = check_qmt_positions(env["QMT_BRIDGE_URL"], env["QMT_BRIDGE_TOKEN"])

    assert payload["ok"] is True
    assert "positions" in payload
    assert "cash" in payload


def test_external_qmt_rebalance_dry_run_is_idempotent() -> None:
    _skip_unless_external()
    env = require_env("QMT_BRIDGE_URL", "QMT_BRIDGE_TOKEN")
    weights, prices = _qmt_probe_payload()
    request_id = f"pytest-dry-run-{datetime.now():%Y%m%d}"

    first = check_qmt_rebalance(
        env["QMT_BRIDGE_URL"],
        env["QMT_BRIDGE_TOKEN"],
        request_id,
        "dry_run",
        weights,
        prices,
    )
    second = check_qmt_rebalance(
        env["QMT_BRIDGE_URL"],
        env["QMT_BRIDGE_TOKEN"],
        request_id,
        "dry_run",
        weights,
        prices,
    )

    assert first["ok"] is True
    assert first == second
    assert first["mode"] == "dry_run"


def test_external_qmt_rebalance_execute() -> None:
    _skip_unless_external()
    if not execute_enabled():
        pytest.skip("set VNPY_RUN_QMT_EXECUTE_TESTS=1 to place simulated QMT orders")
    env = require_env("QMT_BRIDGE_URL", "QMT_BRIDGE_TOKEN")
    weights, prices = _qmt_probe_payload()
    request_id = f"pytest-execute-{datetime.now():%Y%m%d%H%M%S}"

    payload = check_qmt_rebalance(
        env["QMT_BRIDGE_URL"],
        env["QMT_BRIDGE_TOKEN"],
        request_id,
        "execute",
        weights,
        prices,
    )

    assert payload["ok"] is True
    assert payload["mode"] == "execute"
    assert "order_ids" in payload


def test_external_telegram_get_me() -> None:
    _skip_unless_external()
    env = require_env("TELEGRAM_BOT_TOKEN")

    payload = check_telegram_get_me(env["TELEGRAM_BOT_TOKEN"])

    assert payload["ok"] is True
    assert payload["result"]["is_bot"] is True


def test_external_telegram_send_message() -> None:
    _skip_unless_external()
    env = require_env("TELEGRAM_BOT_TOKEN", "TELEGRAM_CHAT_ID")

    payload = check_telegram_send_message(
        env["TELEGRAM_BOT_TOKEN"],
        env["TELEGRAM_CHAT_ID"],
        "vnpy external integration test",
    )

    assert payload["ok"] is True


def test_external_rdagent_cli_available() -> None:
    _skip_unless_external()

    payload = check_rdagent_cli()

    assert payload["ok"] is True, payload
