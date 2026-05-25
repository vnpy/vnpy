from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime, timedelta
from typing import Any

import pytest

from vnpy.chan import BuyPointType, BuySignal, ChanSnapshot, SellPointType, SellSignal, TrendState
from vnpy.trader.constant import Direction, Exchange, Interval, Offset
from vnpy.trader.object import BarData, TickData, TradeData
from vnpy_ctastrategy.base import EngineType
from vnpy_ctastrategy.strategies.chan_strategy import ChanStrategy


class DummyEngine:
    def __init__(self) -> None:
        self.orders: list[tuple[Direction, Offset, float, float, bool]] = []
        self.logs: list[str] = []
        self.history_bars: list[BarData] = []

    def send_order(
        self,
        strategy: ChanStrategy,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: float,
        stop: bool,
        lock: bool,
        net: bool,
    ) -> list[str]:
        self.orders.append((direction, offset, price, volume, stop))
        return [str(len(self.orders))]

    def cancel_all(self, strategy: ChanStrategy) -> None:
        return

    def write_log(self, msg: str, strategy: ChanStrategy | None = None) -> None:
        self.logs.append(msg)

    def get_engine_type(self) -> EngineType:
        return EngineType.BACKTESTING

    def put_strategy_event(self, strategy: ChanStrategy) -> None:
        return

    def load_bar(
        self,
        vt_symbol: str,
        days: int,
        interval: Interval,
        callback: Any,
        use_database: bool,
    ) -> list[BarData]:
        return self.history_bars


@dataclass
class FakeAnalyzer:
    snapshots: list[ChanSnapshot]

    def update_bar(self, bar: BarData) -> ChanSnapshot:
        if len(self.snapshots) == 1:
            return self.snapshots[0]
        return self.snapshots.pop(0)


def _bar(index: int, close_price: float = 10) -> BarData:
    return BarData(
        symbol="TEST",
        exchange=Exchange.LOCAL,
        datetime=datetime(2026, 1, 1, 9, 30) + timedelta(minutes=index),
        interval=Interval.MINUTE,
        open_price=close_price,
        high_price=close_price + 1,
        low_price=close_price - 1,
        close_price=close_price,
        gateway_name="TEST",
    )


def _tick(index: int, price: float = 10) -> TickData:
    return TickData(
        symbol="TEST",
        exchange=Exchange.LOCAL,
        datetime=datetime(2026, 1, 1, 9, 30) + timedelta(minutes=index),
        last_price=price,
        volume=index + 1,
        gateway_name="TEST",
    )


def _trade(index: int, price: float = 10, volume: float = 1) -> TradeData:
    return TradeData(
        symbol="TEST",
        exchange=Exchange.LOCAL,
        orderid=str(index),
        tradeid=str(index),
        direction=Direction.LONG,
        offset=Offset.OPEN,
        price=price,
        volume=volume,
        datetime=datetime(2026, 1, 1, 9, 30) + timedelta(minutes=index),
        gateway_name="TEST",
    )


def _snapshot(signal: BuySignal | None = None) -> ChanSnapshot:
    signals = (signal,) if signal else ()
    return ChanSnapshot(
        bars=(),
        fractals=(),
        strokes=(),
        segments=(),
        pivots=(),
        segment_metrics=(),
        trend=TrendState.UNKNOWN,
        signals=signals,
        sell_signals=(),
    )


def _signal(type: BuyPointType = BuyPointType.SECOND_BUY) -> BuySignal:
    return BuySignal(
        id=0,
        type=type,
        candidate_index=1,
        confirmed_index=2,
        stop_price=8,
        reason="test signal",
    )


def _sell_signal(type: SellPointType = SellPointType.THIRD_SELL) -> SellSignal:
    return SellSignal(
        id=0,
        type=type,
        candidate_index=1,
        confirmed_index=2,
        stop_price=12,
        reason="test sell signal",
    )


def _sell_snapshot(signal: SellSignal | None = None) -> ChanSnapshot:
    sell_signals = (signal,) if signal else ()
    return ChanSnapshot(
        bars=(),
        fractals=(),
        strokes=(),
        segments=(),
        pivots=(),
        segment_metrics=(),
        trend=TrendState.UNKNOWN,
        signals=(),
        sell_signals=sell_signals,
    )


def _strategy(setting: dict[str, Any] | None = None) -> tuple[ChanStrategy, DummyEngine]:
    engine = DummyEngine()
    strategy = ChanStrategy(engine, "chan", "TEST.LOCAL", setting or {})
    strategy.on_init()
    strategy.trading = True
    return strategy, engine


def test_chan_strategy_sends_buy_on_confirmed_signal() -> None:
    strategy, engine = _strategy({"fixed_size": 2})
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 10))

    assert engine.orders == [(Direction.LONG, Offset.OPEN, 10, 2, False)]
    assert strategy.latest_signal_type == BuyPointType.SECOND_BUY.value
    assert strategy.active_stop_price == 8
    assert strategy.active_stop_orderid == ""
    assert strategy.latest_chan_signal == {
        "signal_key": "second_buy:2:8",
        "type": "second_buy",
        "sizing_mode": "fixed",
        "target_ratio": 0.05,
        "risk_per_trade": 0.01,
        "candidate_index": 1,
        "confirmed_index": 2,
        "stop_price": 8,
        "reason": "test signal",
        "bar_datetime": "2026-01-01T09:30:00",
        "bar_close_price": 10,
        "sizing": {},
        "trade_enabled": True,
    }


def test_chan_strategy_warms_up_analyzer_without_trading() -> None:
    engine = DummyEngine()
    engine.history_bars = [_bar(0, 10), _bar(1, 11), _bar(2, 12)]
    strategy = ChanStrategy(engine, "chan", "TEST.LOCAL", {"init_days": 3})

    strategy.on_init()

    assert engine.orders == []
    assert strategy.warmup_bar_count == 3
    assert len(strategy.analyzer.raw_bars) == 3
    assert strategy.latest_chan_signal == {}
    assert engine.logs[-1] == "缠论预热完成: 3 bars"


def test_chan_strategy_can_run_in_signal_only_mode() -> None:
    strategy, engine = _strategy({"trade_enabled": False})
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 10))

    assert engine.orders == []
    assert strategy.latest_signal_type == BuyPointType.SECOND_BUY.value
    assert strategy.latest_chan_signal["trade_enabled"] is False
    assert "信号模式" in engine.logs[-1]


def test_chan_strategy_respects_max_position() -> None:
    strategy, engine = _strategy({"fixed_size": 2, "max_position": 1})
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 10))

    assert engine.orders == []
    assert "超过最大仓位" in engine.logs[-1]


def test_chan_strategy_uses_risk_per_trade_sizing_for_buy() -> None:
    strategy, engine = _strategy(
        {
            "sizing_mode": "risk_per_trade",
            "risk_per_trade": 0.01,
            "capital": 10_000,
            "max_position": 0.05,
            "min_volume": 0.001,
            "volume_step": 0.001,
        }
    )
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 100_000))

    assert engine.orders == [(Direction.LONG, Offset.OPEN, 100_000, 0.001, False)]
    assert strategy.latest_chan_signal["sizing_mode"] == "risk_per_trade"
    assert strategy.latest_chan_signal["risk_per_trade"] == 0.01
    assert strategy.latest_chan_signal["sizing"]["unit_risk"] == 99_992


def test_chan_strategy_risk_per_trade_signal_only_records_sizing_without_order() -> None:
    strategy, engine = _strategy(
        {
            "trade_enabled": False,
            "sizing_mode": "risk_per_trade",
            "risk_per_trade": 0.01,
            "capital": 10_000,
            "volume_step": 0.001,
        }
    )
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 100_000))

    assert engine.orders == []
    assert strategy.latest_chan_signal["sizing"]["risk_amount"] == 100


def test_chan_strategy_target_ratio_mode_is_available() -> None:
    strategy, engine = _strategy(
        {
            "sizing_mode": "target_ratio",
            "target_long_ratio": 0.05,
            "capital": 10_000,
            "max_position": 0.05,
            "volume_step": 0.001,
        }
    )
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 100_000))

    assert engine.orders == [(Direction.LONG, Offset.OPEN, 100_000, 0.005, False)]
    assert strategy.latest_chan_signal["target_ratio"] == 0.05


def test_chan_strategy_uses_position_ratio_cap_for_low_price_symbol() -> None:
    strategy, engine = _strategy(
        {
            "sizing_mode": "target_ratio",
            "target_long_ratio": 1,
            "capital": 10_000,
            "max_position": 0,
            "max_position_ratio": 0.5,
            "volume_step": 1,
        }
    )
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 0.1))

    assert engine.orders == [(Direction.LONG, Offset.OPEN, 0.1, 50_000, False)]
    assert strategy.latest_chan_signal["sizing"]["order_value"] == 5_000
    assert "max_position_ratio" in strategy.latest_chan_signal["sizing"]["reason"]


def test_chan_strategy_does_not_duplicate_same_signal() -> None:
    strategy, engine = _strategy()
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 10))
    strategy.pos = 0
    strategy.on_bar(_bar(1, 10))

    assert len(engine.orders) == 1


def test_chan_strategy_treats_tiny_residual_position_as_flat_for_next_entry() -> None:
    strategy, engine = _strategy({"fixed_size": 2})
    strategy.pos = -6.938893903907228e-18
    strategy.active_stop_price = 8
    strategy.active_stop_orderid = "STOP.1"
    strategy.exit_order_sent = True
    next_signal = BuySignal(
        id=0,
        type=BuyPointType.SECOND_BUY,
        candidate_index=3,
        confirmed_index=4,
        stop_price=9,
        reason="next signal",
    )
    strategy.analyzer = FakeAnalyzer([_snapshot(next_signal)])

    strategy.on_bar(_bar(0, 10))

    assert strategy.pos == 0
    assert engine.orders == [(Direction.LONG, Offset.OPEN, 10, 2, False)]
    assert strategy.active_stop_price == 9
    assert strategy.active_stop_orderid == ""
    assert strategy.exit_order_sent is False


def test_chan_strategy_distinguishes_different_confirmed_signals() -> None:
    strategy, engine = _strategy({"trade_enabled": False})
    first = _signal()
    next_signal = BuySignal(
        id=0,
        type=first.type,
        candidate_index=3,
        confirmed_index=4,
        stop_price=first.stop_price,
        reason=first.reason,
    )
    strategy.analyzer = FakeAnalyzer([_snapshot(first), _snapshot(next_signal)])

    strategy.on_bar(_bar(0, 10))
    strategy.on_bar(_bar(1, 10))

    assert engine.orders == []
    assert sum("缠论买点触发" in log for log in engine.logs) == 2


def test_chan_strategy_clears_stop_state_after_tiny_residual_close() -> None:
    strategy, _engine = _strategy()
    strategy.pos = -6.938893903907228e-18
    strategy.active_stop_price = 8
    strategy.active_stop_orderid = "STOP.1"
    strategy.exit_order_sent = True

    strategy.on_trade(_trade(0, 8, 1))

    assert strategy.pos == 0
    assert strategy.active_stop_price == 0
    assert strategy.active_stop_orderid == ""
    assert strategy.exit_order_sent is False


def test_chan_strategy_sells_when_stop_is_touched() -> None:
    strategy, engine = _strategy()
    strategy.pos = 1
    strategy.active_stop_price = 8
    strategy.analyzer = FakeAnalyzer([_snapshot()])

    strategy.on_bar(_bar(0, 8.5))

    assert engine.orders == [(Direction.SHORT, Offset.CLOSE, 8, 1, True)]


def test_chan_strategy_does_not_repeat_exit_order_while_waiting_for_fill() -> None:
    strategy, engine = _strategy()
    strategy.pos = 1
    strategy.active_stop_price = 8
    strategy.analyzer = FakeAnalyzer([_snapshot()])

    strategy.on_bar(_bar(0, 8.5))
    strategy.on_bar(_bar(1, 8.3))

    assert engine.orders == [(Direction.SHORT, Offset.CLOSE, 8, 1, True)]


def test_chan_strategy_places_stop_order_after_entry_trade() -> None:
    strategy, engine = _strategy({"fixed_size": 2})
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 10))
    strategy.pos = 2
    strategy.on_trade(_trade(0, 10, 2))

    assert engine.orders[-1] == (Direction.SHORT, Offset.CLOSE, 8, 2, True)


@pytest.mark.parametrize(
    "sell_type",
    [
        SellPointType.FIRST_SELL,
        SellPointType.SECOND_SELL,
        SellPointType.THIRD_SELL,
    ],
)
def test_chan_strategy_exits_on_sell_signal(sell_type: SellPointType) -> None:
    strategy, engine = _strategy()
    strategy.pos = 1
    strategy.active_stop_orderid = "STOP.1"
    strategy.analyzer = FakeAnalyzer([_sell_snapshot(_sell_signal(sell_type))])

    strategy.on_bar(_bar(0, 10))

    assert engine.orders == [(Direction.SHORT, Offset.CLOSE, 10, 1, False)]
    assert strategy.latest_signal_type == sell_type.value
    assert "卖点清仓" in engine.logs[-1]


def test_chan_strategy_risk_per_trade_sell_signal_clears_position() -> None:
    strategy, engine = _strategy({"sizing_mode": "risk_per_trade", "capital": 10_000})
    strategy.pos = 0.005
    strategy.active_stop_orderid = "STOP.1"
    strategy.analyzer = FakeAnalyzer([_sell_snapshot(_sell_signal())])

    strategy.on_bar(_bar(0, 100_000))

    assert engine.orders == [(Direction.SHORT, Offset.CLOSE, 100_000, 0.005, False)]


def test_chan_strategy_routes_ticks_into_bar_generator() -> None:
    strategy, _engine = _strategy()
    calls: list[TickData] = []

    class FakeBarGenerator:
        def update_tick(self, tick: TickData) -> None:
            calls.append(tick)

    strategy.bg = FakeBarGenerator()
    tick = _tick(0, 10)

    strategy.on_tick(tick)

    assert calls == [tick]
