from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime, timedelta
from typing import Any

from vnpy.chan import BuyPointType, BuySignal, ChanSnapshot, TrendState
from vnpy.trader.constant import Direction, Exchange, Interval, Offset
from vnpy.trader.object import BarData
from vnpy_ctastrategy.base import EngineType
from vnpy_ctastrategy.strategies.chan_strategy import ChanStrategy


class DummyEngine:
    def __init__(self) -> None:
        self.orders: list[tuple[Direction, Offset, float, float]] = []
        self.logs: list[str] = []

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
        self.orders.append((direction, offset, price, volume))
        return [str(len(self.orders))]

    def cancel_all(self, strategy: ChanStrategy) -> None:
        return

    def write_log(self, msg: str, strategy: ChanStrategy | None = None) -> None:
        self.logs.append(msg)

    def get_engine_type(self) -> EngineType:
        return EngineType.BACKTESTING

    def put_strategy_event(self, strategy: ChanStrategy) -> None:
        return


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


def _snapshot(signal: BuySignal | None = None) -> ChanSnapshot:
    signals = (signal,) if signal else ()
    return ChanSnapshot(
        bars=(),
        fractals=(),
        strokes=(),
        segments=(),
        pivots=(),
        trend=TrendState.UNKNOWN,
        signals=signals,
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

    assert engine.orders == [(Direction.LONG, Offset.OPEN, 10, 2)]
    assert strategy.latest_signal_type == BuyPointType.SECOND_BUY.value
    assert strategy.active_stop_price == 8


def test_chan_strategy_can_run_in_signal_only_mode() -> None:
    strategy, engine = _strategy({"trade_enabled": False})
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 10))

    assert engine.orders == []
    assert strategy.latest_signal_type == BuyPointType.SECOND_BUY.value
    assert "信号模式" in engine.logs[-1]


def test_chan_strategy_respects_max_position() -> None:
    strategy, engine = _strategy({"fixed_size": 2, "max_position": 1})
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 10))

    assert engine.orders == []
    assert "超过最大仓位" in engine.logs[-1]


def test_chan_strategy_does_not_duplicate_same_signal() -> None:
    strategy, engine = _strategy()
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 10))
    strategy.pos = 0
    strategy.on_bar(_bar(1, 10))

    assert len(engine.orders) == 1


def test_chan_strategy_sells_when_stop_is_touched() -> None:
    strategy, engine = _strategy()
    strategy.pos = 1
    strategy.active_stop_price = 8
    strategy.analyzer = FakeAnalyzer([_snapshot()])

    strategy.on_bar(_bar(0, 8.5))

    assert engine.orders == [(Direction.SHORT, Offset.CLOSE, 8, 1)]


def test_chan_strategy_does_not_repeat_exit_order_while_waiting_for_fill() -> None:
    strategy, engine = _strategy()
    strategy.pos = 1
    strategy.active_stop_price = 8
    strategy.analyzer = FakeAnalyzer([_snapshot()])

    strategy.on_bar(_bar(0, 8.5))
    strategy.on_bar(_bar(1, 8.3))

    assert engine.orders == [(Direction.SHORT, Offset.CLOSE, 8, 1)]
