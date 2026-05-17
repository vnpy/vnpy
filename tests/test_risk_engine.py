"""Unit tests for vnpy.trader.engine_risk.RiskEngine."""

from __future__ import annotations

from types import SimpleNamespace
from unittest.mock import MagicMock

import pytest

from vnpy.event import Event, EventEngine
from vnpy.trader.constant import Direction
from vnpy.trader.event import EVENT_ACCOUNT
from vnpy.trader.engine_risk import RiskEngine
from vnpy.trader.object import AccountData


def _account(balance: float, gateway_name: str = "OKX", accountid: str = "USDT") -> AccountData:
    return AccountData(
        gateway_name=gateway_name,
        accountid=accountid,
        balance=balance,
    )


def _fire_account(event_engine: EventEngine, account: AccountData) -> None:
    # Call the engine's handler directly via its registered callback rather than
    # pushing through the real queue; keeps tests synchronous and deterministic.
    event = Event(EVENT_ACCOUNT, account)
    for handler in event_engine._handlers.get(EVENT_ACCOUNT, []):
        handler(event)


@pytest.fixture
def engine() -> RiskEngine:
    event_engine = EventEngine()  # not started — we fire events manually
    main_engine = MagicMock()
    main_engine.write_log = MagicMock()
    risk = RiskEngine(main_engine, event_engine)
    return risk


@pytest.fixture
def strategy() -> SimpleNamespace:
    return SimpleNamespace(strategy_name="unit_test", pos=0.0)


def test_allows_orders_when_no_history(engine: RiskEngine, strategy) -> None:
    assert engine.check_order(strategy, Direction.LONG, 100.0, 0.1) is True


def test_rejects_order_above_notional_cap(engine: RiskEngine, strategy) -> None:
    # default cap is 200 USDT
    assert engine.check_order(strategy, Direction.LONG, 100.0, 5.0) is False
    assert "notional" in engine.last_rejection_reason


def test_rejects_order_above_equity_percent_cap(engine: RiskEngine, strategy) -> None:
    engine.max_order_value_usdt = 0
    engine.max_order_value_pct = 0.1
    _fire_account(engine.event_engine, _account(1000.0))

    assert engine.check_order(strategy, Direction.LONG, 100.0, 2.0) is False
    assert "pct cap" in engine.last_rejection_reason


def test_notional_cap_uses_contract_size(engine: RiskEngine, strategy) -> None:
    contract = SimpleNamespace(size=0.01)

    assert engine.check_order(
        strategy,
        Direction.LONG,
        price=100_000.0,
        volume=1.0,
        contract=contract,
    ) is False
    assert "1000.00 USDT" in engine.last_rejection_reason


def test_daily_loss_halt_blocks_opens_allows_closes(engine: RiskEngine, strategy) -> None:
    _fire_account(engine.event_engine, _account(1000.0))
    _fire_account(engine.event_engine, _account(960.0))  # 4% daily loss > 3%
    assert engine.daily_halt is True

    # new long open is blocked
    assert engine.check_order(strategy, Direction.LONG, 50.0, 1.0) is False

    # closing an existing short (pos<0) with a LONG fill is allowed
    strategy.pos = -1.0
    assert engine.check_order(strategy, Direction.LONG, 50.0, 1.0, is_close=True) is True


def test_peak_drawdown_halt_blocks_everything(engine: RiskEngine, strategy) -> None:
    _fire_account(engine.event_engine, _account(1000.0))
    _fire_account(engine.event_engine, _account(1500.0))  # new peak
    _fire_account(engine.event_engine, _account(1300.0))  # -13.3% from peak > 10%
    assert engine.drawdown_halt is True

    strategy.pos = 1.0  # even a close is blocked — drawdown is the last line
    assert engine.check_order(strategy, Direction.SHORT, 50.0, 1.0, is_close=True) is False


def test_day_rollover_resets_daily_halt(engine: RiskEngine, strategy, monkeypatch) -> None:
    engine.day_start_equity = 1000.0
    engine.day_start_date = "2020-01-01"
    engine.daily_halt = True
    engine.current_equity = 900.0

    # Simulate the date advancing by fixing _today_utc
    monkeypatch.setattr(engine, "_today_utc", lambda: "2020-01-02")
    _fire_account(engine.event_engine, _account(900.0))

    assert engine.daily_halt is False
    assert engine.day_start_equity == 900.0


def test_disabled_engine_passes_through(engine: RiskEngine, strategy) -> None:
    engine.enabled = False
    # would normally reject (notional > cap) but engine is disabled
    assert engine.check_order(strategy, Direction.LONG, 1000.0, 10.0) is True


def test_ignores_non_base_currency_accounts(engine: RiskEngine) -> None:
    _fire_account(engine.event_engine, _account(1000.0, accountid="USDT"))
    _fire_account(engine.event_engine, _account(1.0, accountid="DOGE"))

    assert engine.current_equity == 1000.0
    assert engine.daily_halt is False
    assert engine.drawdown_halt is False
