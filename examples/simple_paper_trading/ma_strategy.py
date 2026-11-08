"""
Simple moving-average crossover strategy used by the paper-trading demo.

This is the only file you need to change when you want to use another
strategy. The gateway, event engine, OMS, and account logic stay untouched.

Logic:
    * Build a daily close series from each tick.
    * fast MA crosses above slow MA and no position -> buy.
    * fast MA crosses below slow MA and long position -> sell all.
"""

from __future__ import annotations

import math
from collections import defaultdict

from vnpy.event import Event, EventEngine
from vnpy.trader.constant import Direction, Exchange, Interval, Offset, OrderType, Status
from vnpy.trader.engine import MainEngine
from vnpy.trader.event import EVENT_ORDER, EVENT_TICK, EVENT_TRADE
from vnpy.trader.object import (
    BarData,
    OrderData,
    OrderRequest,
    SubscribeRequest,
    TickData,
    TradeData,
)
from vnpy.trader.utility import ArrayManager, extract_vt_symbol, round_to


class MaCrossStrategy:
    """Long-only moving-average crossover strategy."""

    def __init__(
        self,
        main_engine: MainEngine,
        event_engine: EventEngine,
        gateway_name: str,
        vt_symbols: list[str],
        fast_window: int = 5,
        slow_window: int = 20,
        trade_volume: float = 5_000,
        price_add: float = 0.002,
    ) -> None:
        """Subscribe symbols and register event handlers."""
        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine
        self.gateway_name: str = gateway_name

        self.fast_window: int = fast_window
        self.slow_window: int = slow_window
        self.trade_volume: float = trade_volume
        self.price_add: float = price_add

        self.ams: dict[str, ArrayManager] = {}
        self.pos: dict[str, float] = defaultdict(float)
        self.active_symbols: set[str] = set()
        self.last_prices: dict[str, float] = {}

        vt_symbol: str
        for vt_symbol in vt_symbols:
            self.ams[vt_symbol] = ArrayManager(size=slow_window + 10)

            symbol: str
            exchange: Exchange
            symbol, exchange = extract_vt_symbol(vt_symbol)
            self.main_engine.subscribe(
                SubscribeRequest(symbol=symbol, exchange=exchange),
                self.gateway_name,
            )

        self.event_engine.register(EVENT_TICK, self.on_tick)
        self.event_engine.register(EVENT_ORDER, self.on_order)
        self.event_engine.register(EVENT_TRADE, self.on_trade)

        self.write_log(
            f"策略初始化完成：MA{fast_window}/MA{slow_window}，"
            f"合约 {', '.join(vt_symbols)}"
        )

    def on_tick(self, event: Event) -> None:
        """Update the bar series and check for a crossover signal."""
        tick: TickData = event.data
        am: ArrayManager | None = self.ams.get(tick.vt_symbol, None)
        if am is None:
            return

        self.last_prices[tick.vt_symbol] = tick.last_price

        # One tick per trading day in this demo: convert it to a daily bar
        bar: BarData = BarData(
            symbol=tick.symbol,
            exchange=tick.exchange,
            datetime=tick.datetime,
            interval=Interval.DAILY,
            open_price=tick.last_price,
            high_price=tick.last_price,
            low_price=tick.last_price,
            close_price=tick.last_price,
            volume=tick.volume,
            turnover=tick.turnover,
            gateway_name=tick.gateway_name,
        )
        am.update_bar(bar)

        if not am.inited:
            return

        fast_ma: float = float(am.sma(self.fast_window))
        slow_ma: float = float(am.sma(self.slow_window))
        if math.isnan(fast_ma) or math.isnan(slow_ma):
            return

        # One active order per symbol is enough for this demo
        if tick.vt_symbol in self.active_symbols:
            return

        pos: float = self.pos[tick.vt_symbol]

        if fast_ma > slow_ma and pos == 0:
            self.send_order(tick, Direction.LONG, self.trade_volume)
        elif fast_ma < slow_ma and pos > 0:
            self.send_order(tick, Direction.SHORT, pos)

    def send_order(
        self,
        tick: TickData,
        direction: Direction,
        volume: float
    ) -> None:
        """Send an aggressive limit order."""
        if volume <= 0:
            return

        price: float
        if direction == Direction.LONG:
            price = tick.last_price * (1 + self.price_add)
        else:
            price = tick.last_price * (1 - self.price_add)

        price = round_to(price, 0.01)

        req: OrderRequest = OrderRequest(
            symbol=tick.symbol,
            exchange=tick.exchange,
            direction=direction,
            type=OrderType.LIMIT,
            volume=volume,
            price=price,
            offset=Offset.NONE,
            reference="MA_CROSS",
        )

        vt_orderid: str = self.main_engine.send_order(req, self.gateway_name)
        if vt_orderid:
            self.active_symbols.add(tick.vt_symbol)
            self.write_log(
                f"发送委托：{tick.vt_symbol} {direction.value} "
                f"{volume:g} @ {price:.2f}"
            )

    def on_order(self, event: Event) -> None:
        """Track active orders and log terminal states."""
        order: OrderData = event.data
        if order.gateway_name != self.gateway_name:
            return

        if order.is_active():
            self.active_symbols.add(order.vt_symbol)
            return

        self.active_symbols.discard(order.vt_symbol)

        if order.status == Status.ALLTRADED:
            self.write_log(
                f"委托全部成交：{order.vt_symbol} {order.direction.value} "
                f"{order.volume:g}"
            )
        elif order.status == Status.REJECTED:
            self.write_log(f"委托被拒绝：{order.vt_symbol}")
        elif order.status == Status.CANCELLED:
            self.write_log(f"委托已撤销：{order.vt_symbol}")

    def on_trade(self, event: Event) -> None:
        """Update the strategy's own position counter."""
        trade: TradeData = event.data
        if trade.gateway_name != self.gateway_name:
            return

        if trade.direction == Direction.LONG:
            self.pos[trade.vt_symbol] += trade.volume
        else:
            self.pos[trade.vt_symbol] -= trade.volume

        self.write_log(
            f"策略成交：{trade.vt_symbol} {trade.direction.value} "
            f"{trade.volume:g} @ {trade.price:.2f}，"
            f"当前持仓 {self.pos[trade.vt_symbol]:g}"
        )

    def write_log(self, msg: str) -> None:
        """Write a strategy log through the main engine."""
        self.main_engine.write_log(msg, "MaCrossStrategy")
