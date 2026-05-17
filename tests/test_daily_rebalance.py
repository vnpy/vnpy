"""Tests for the MVP daily rebalance adapter."""

from __future__ import annotations

import json
from pathlib import Path

from pipeline.daily_rebalance import (
    call_qmt_rebalance,
    load_plan,
    save_plan,
)


def test_save_and_load_plan(tmp_path: Path) -> None:
    path = save_plan(
        plan_id="plan-1",
        weights={"510300.SH": 0.01},
        prices={"510300.SH": 4.0},
        plan_dir=tmp_path,
    )

    plan = load_plan(path)

    assert plan["plan_id"] == "plan-1"
    assert plan["weights"] == {"510300.SH": 0.01}
    assert plan["prices"] == {"510300.SH": 4.0}


def test_call_qmt_rebalance_sends_token_and_mode(monkeypatch) -> None:
    captured = {}

    class FakeResponse:
        def __enter__(self):
            return self

        def __exit__(self, *_args):
            return False

        def read(self) -> bytes:
            return b'{"ok": true, "orders": []}'

    def fake_urlopen(req, timeout):  # noqa: ANN001
        captured["url"] = req.full_url
        captured["headers"] = dict(req.header_items())
        captured["body"] = json.loads(req.data.decode("utf-8"))
        captured["timeout"] = timeout
        return FakeResponse()

    monkeypatch.setattr("pipeline.daily_rebalance.urlopen", fake_urlopen)

    response = call_qmt_rebalance(
        qmt_url="http://127.0.0.1:18080",
        plan={
            "plan_id": "plan-1",
            "weights": {"510300.SH": 0.01},
            "prices": {"510300.SH": 4.0},
        },
        mode="dry_run",
        token="secret",
    )

    assert response == {"ok": True, "orders": []}
    assert captured["url"] == "http://127.0.0.1:18080/rebalance"
    assert captured["headers"]["Authorization"] == "Bearer secret"
    assert captured["body"]["request_id"] == "plan-1-dry_run"
    assert captured["body"]["mode"] == "dry_run"
