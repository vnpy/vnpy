"""Unit test for DoubleMATelegramStrategy._calc_dynamic_volume."""

from __future__ import annotations

from types import SimpleNamespace
from unittest.mock import MagicMock
from datetime import datetime, timedelta

import pytest

from vnpy.trader.constant import Direction, Exchange, Offset, OrderType, Status


@pytest.fixture
def strategy(monkeypatch):
    # Avoid triggering Telegram init inside the strategy constructor by stubbing
    # the module before import.
    import sys

    dummy_bot = MagicMock()
    monkeypatch.setitem(sys.modules, "telegram_notifier", SimpleNamespace(TelegramTradeBot=lambda *a, **kw: dummy_bot))

    from double_ma_telegram_strategy import DoubleMATelegramStrategy

    # Construct directly without invoking CtaTemplate init (which requires a real engine)
    s = DoubleMATelegramStrategy.__new__(DoubleMATelegramStrategy)
    s.strategy_name = "unit"
    s.vt_symbol = "DOGEUSDT_SWAP_OKX.GLOBAL"
    s.trading_config = {"leverage": 3, "position_ratio": 0.5, "trade_quantity": 1}
    s.cta_engine = SimpleNamespace(main_engine=MagicMock())
    return s


def _order(status: Status, orderid: str = "order1") -> SimpleNamespace:
    return SimpleNamespace(
        status=status,
        direction=Direction.LONG,
        price=0.1115,
        volume=8.96,
        traded=8.96 if status == Status.ALLTRADED else 0,
        orderid=orderid,
        vt_orderid=f"OKX.{orderid}",
        type=OrderType.LIMIT,
        offset=Offset.OPEN,
        exchange=Exchange.GLOBAL,
    )


def test_dynamic_volume_scales_with_equity(strategy) -> None:
    account = SimpleNamespace(accountid="USDT", balance=1000.0, available=1000.0)
    contract = SimpleNamespace(size=1, min_volume=1)
    strategy.cta_engine.main_engine.get_all_accounts.return_value = [account]
    strategy.cta_engine.main_engine.get_contract.return_value = contract

    # equity=1000, ratio=0.5, leverage=3 → notional 1500; price 100 → 15 contracts
    assert strategy._calc_dynamic_volume(price=100.0) == 15.0


def test_dynamic_volume_uses_base_currency_available_balance(strategy) -> None:
    usdt = SimpleNamespace(accountid="USDT", balance=1000.0, available=100.0)
    doge = SimpleNamespace(accountid="DOGE", balance=1_000_000.0, available=1_000_000.0)
    contract = SimpleNamespace(size=1, min_volume=1)
    strategy.cta_engine.main_engine.get_all_accounts.return_value = [doge, usdt]
    strategy.cta_engine.main_engine.get_contract.return_value = contract

    # available=100, ratio=0.5, leverage=3 -> notional 150; price 10 -> 15 contracts.
    assert strategy._calc_dynamic_volume(price=10.0) == 15.0


def test_dynamic_volume_is_capped_by_risk_notional(strategy) -> None:
    account = SimpleNamespace(accountid="USDT", balance=1000.0, available=1000.0)
    contract = SimpleNamespace(size=1, min_volume=1)
    strategy.cta_engine.main_engine.get_all_accounts.return_value = [account]
    strategy.cta_engine.main_engine.get_contract.return_value = contract
    strategy.risk_config = {"max_order_value_usdt": 50.0}

    assert strategy._calc_dynamic_volume(price=10.0) == 5.0


def test_dynamic_volume_is_capped_by_risk_percent(strategy) -> None:
    account = SimpleNamespace(accountid="USDT", balance=1000.0, available=1000.0)
    contract = SimpleNamespace(size=1, min_volume=1)
    strategy.cta_engine.main_engine.get_all_accounts.return_value = [account]
    strategy.cta_engine.main_engine.get_contract.return_value = contract
    strategy.risk_config = {"max_order_value_pct": 0.1}

    assert strategy._calc_dynamic_volume(price=10.0) == 10.0


def test_dynamic_volume_respects_min_volume(strategy) -> None:
    account = SimpleNamespace(accountid="USDT", balance=1000.0, available=1000.0)
    contract = SimpleNamespace(size=1, min_volume=0.01)
    strategy.cta_engine.main_engine.get_all_accounts.return_value = [account]
    strategy.cta_engine.main_engine.get_contract.return_value = contract

    vol = strategy._calc_dynamic_volume(price=123.45)
    # should be rounded to multiple of 0.01
    assert abs(vol * 100 - round(vol * 100)) < 1e-9
    assert vol > 0


def test_fallback_when_no_account(strategy) -> None:
    strategy.cta_engine.main_engine.get_all_accounts.return_value = []
    assert strategy._calc_dynamic_volume(price=50.0) == 1.0


def test_fallback_when_price_zero(strategy) -> None:
    assert strategy._calc_dynamic_volume(price=0) == 1.0


def test_strategy_uses_shared_notifier_from_engine(monkeypatch) -> None:
    import sys

    constructed = []

    def fake_bot(*_args, **_kwargs):
        constructed.append(True)
        return object()

    monkeypatch.setitem(sys.modules, "telegram_notifier", SimpleNamespace(TelegramTradeBot=fake_bot))

    from double_ma_telegram_strategy import DoubleMATelegramStrategy

    shared = object()
    engine = SimpleNamespace(telegram_notifier=shared)
    strategy = DoubleMATelegramStrategy(engine, "unit", "DOGEUSDT_SWAP_OKX.GLOBAL", {})

    assert strategy.telegram is shared
    assert constructed == []


def test_on_bar_does_not_signal_before_strategy_trading(monkeypatch) -> None:
    import sys
    import numpy as np

    monkeypatch.setitem(sys.modules, "telegram_notifier", SimpleNamespace(TelegramTradeBot=lambda *a, **kw: object()))

    from double_ma_telegram_strategy import DoubleMATelegramStrategy

    strategy = DoubleMATelegramStrategy.__new__(DoubleMATelegramStrategy)
    strategy.trading = False
    strategy.fast_window = 2
    strategy.slow_window = 3
    strategy.am = SimpleNamespace(
        inited=True,
        update_bar=lambda _bar: None,
        sma=lambda window, array=True: np.array([1.0, 3.0]) if window == 2 else np.array([2.0, 2.0]),
    )
    strategy.cancel_all = MagicMock()
    strategy.put_event = MagicMock()
    strategy._handle_buy_signal = MagicMock()
    strategy._handle_sell_signal = MagicMock()

    strategy.on_bar(SimpleNamespace())

    strategy._handle_buy_signal.assert_not_called()
    strategy._handle_sell_signal.assert_not_called()


def test_on_bar_ignores_weak_ma_cross_inside_deadband(monkeypatch) -> None:
    import sys
    import numpy as np

    monkeypatch.setitem(sys.modules, "telegram_notifier", SimpleNamespace(TelegramTradeBot=lambda *a, **kw: object()))

    from double_ma_telegram_strategy import DoubleMATelegramStrategy

    strategy = DoubleMATelegramStrategy.__new__(DoubleMATelegramStrategy)
    strategy.trading = True
    strategy.fast_window = 2
    strategy.slow_window = 3
    strategy.runtime_config = {"ma_cross_deadband_pct": 0.0002}
    strategy.am = SimpleNamespace(
        inited=True,
        update_bar=lambda _bar: None,
        sma=lambda window, array=True: np.array([0.11149, 0.11151])
        if window == 2
        else np.array([0.11150, 0.11150]),
    )
    strategy.cancel_all = MagicMock()
    strategy.put_event = MagicMock()
    strategy.write_log = MagicMock()
    strategy._handle_buy_signal = MagicMock()
    strategy._handle_sell_signal = MagicMock()

    strategy.on_bar(SimpleNamespace(close_price=0.11150))

    strategy._handle_buy_signal.assert_not_called()
    strategy._handle_sell_signal.assert_not_called()
    assert any("均线差值未超过阈值" in call.args[0] for call in strategy.write_log.call_args_list)


def test_on_bar_triggers_strong_ma_cross_outside_deadband(monkeypatch) -> None:
    import sys
    import numpy as np

    monkeypatch.setitem(sys.modules, "telegram_notifier", SimpleNamespace(TelegramTradeBot=lambda *a, **kw: object()))

    from double_ma_telegram_strategy import DoubleMATelegramStrategy

    strategy = DoubleMATelegramStrategy.__new__(DoubleMATelegramStrategy)
    strategy.trading = True
    strategy.fast_window = 2
    strategy.slow_window = 3
    strategy.runtime_config = {"ma_cross_deadband_pct": 0.0002}
    strategy.am = SimpleNamespace(
        inited=True,
        update_bar=lambda _bar: None,
        sma=lambda window, array=True: np.array([0.11146, 0.11154])
        if window == 2
        else np.array([0.11150, 0.11150]),
    )
    strategy.cancel_all = MagicMock()
    strategy.put_event = MagicMock()
    strategy.write_log = MagicMock()
    strategy._handle_buy_signal = MagicMock()
    strategy._handle_sell_signal = MagicMock()
    bar = SimpleNamespace(close_price=0.11150)

    strategy.on_bar(bar)

    strategy._handle_buy_signal.assert_called_once_with(bar)
    strategy._handle_sell_signal.assert_not_called()


def test_opposite_signal_respects_reversal_cooldown(strategy) -> None:
    strategy.runtime_config = {
        "signal_cooldown_seconds": 0,
        "reversal_cooldown_seconds": 300,
    }
    strategy.trade_counter = 0
    strategy.pending_trade_request = False
    strategy.last_signal_at = {}
    strategy.last_signal_direction = 1
    strategy.last_any_signal_at = datetime(2026, 5, 17, 20, 0, 0)
    strategy._calc_dynamic_volume = MagicMock(return_value=8.96)
    strategy.write_log = MagicMock()
    bar = SimpleNamespace(close_price=0.1115, datetime=strategy.last_any_signal_at + timedelta(seconds=60))

    strategy._send_trade_request(bar, "卖出做空", -1, 0)

    strategy._calc_dynamic_volume.assert_not_called()
    assert any("反向信号冷却中" in call.args[0] for call in strategy.write_log.call_args_list)


def test_order_notifications_skip_intermediate_status(strategy) -> None:
    strategy.telegram = object()
    strategy._submit_telegram_message = MagicMock()
    strategy.write_log = MagicMock()

    strategy.on_order(_order(Status.SUBMITTING))
    strategy.on_order(_order(Status.NOTTRADED))

    strategy._submit_telegram_message.assert_not_called()


def test_order_notifications_emit_only_terminal_status(strategy) -> None:
    strategy.telegram = object()
    strategy._submit_telegram_message = MagicMock()
    strategy.write_log = MagicMock()

    strategy.on_order(_order(Status.ALLTRADED))

    strategy._submit_telegram_message.assert_called_once()
    msg = strategy._submit_telegram_message.call_args.args[0]
    assert "交易成交" in msg
    assert "全部成交" in msg


def test_trade_callback_does_not_send_duplicate_telegram(strategy) -> None:
    strategy.telegram = object()
    strategy._submit_telegram_message = MagicMock()
    strategy.write_log = MagicMock()
    strategy.put_event = MagicMock()
    trade = SimpleNamespace(
        direction=Direction.LONG,
        volume=8.96,
        price=0.1115,
        datetime="2026-05-17 19:57:12+08:00",
    )

    strategy.on_trade(trade)

    strategy._submit_telegram_message.assert_not_called()
