"""Tests for log event forwarding."""

from __future__ import annotations

from types import SimpleNamespace

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import LogEngine
from vnpy.trader.event import EVENT_LOG
from vnpy.trader.object import LogData


def test_log_engine_treats_braces_as_plain_text(monkeypatch) -> None:
    calls = []

    def fake_log(level, message, *args, **kwargs):
        calls.append((level, message, args, kwargs))

    monkeypatch.setattr("vnpy.trader.engine.logger.log", fake_log)
    engine = LogEngine(SimpleNamespace(), EventEngine())
    log = LogData(msg="headers {'x-simulated-trading': '1'}", gateway_name="OKX")

    engine.process_log_event(Event(EVENT_LOG, log))

    assert calls == [
        (
            "INFO",
            "{}",
            ("headers {'x-simulated-trading': '1'}",),
            {"gateway_name": "OKX"},
        )
    ]
