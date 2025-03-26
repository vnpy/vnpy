from abc import ABCMeta, abstractmethod
from collections import defaultdict
from typing import TYPE_CHECKING

import polars as pl

from vnpy.trader.object import BarData, TradeData, OrderData
from vnpy.trader.constant import Offset, Direction


if TYPE_CHECKING:
    from vnpy.alpha.strategy.backtesting import BacktestingEngine


class AlphaStrategy(metaclass=ABCMeta):
    """Alpha strategy template class"""

    def __init__(
        self,
        strategy_engine: "BacktestingEngine",
        strategy_name: str,
        vt_symbols: list[str],
        setting: dict
    ) -> None:
        """Constructor"""
        self.strategy_engine: BacktestingEngine = strategy_engine
        self.strategy_name: str = strategy_name
        self.vt_symbols: list[str] = vt_symbols

        # Position data dictionaries
        self.pos_data: dict[str, float] = defaultdict(float)        # Actual positions
        self.target_data: dict[str, float] = defaultdict(float)     # Target positions

        # Order cache containers
        self.orders: dict[str, OrderData] = {}
        self.active_orderids: set[str] = set()

        # Set strategy parameters
        for k, v in setting.items():
            if hasattr(self, k):
                setattr(self, k, v)

    @abstractmethod
    def on_init(self) -> None:
        """Initialization callback"""
        pass

    @abstractmethod
    def on_bars(self, bars: dict[str, BarData]) -> None:
        """Bar slice callback"""
        pass

    @abstractmethod
    def on_trade(self, trade: TradeData) -> None:
        """Trade callback"""
        pass

    def update_trade(self, trade: TradeData) -> None:
        """Update trade data"""
        if trade.direction == Direction.LONG:
            self.pos_data[trade.vt_symbol] += trade.volume
        else:
            self.pos_data[trade.vt_symbol] -= trade.volume

        self.on_trade(trade)

    def update_order(self, order: OrderData) -> None:
        """Update order data"""
        self.orders[order.vt_orderid] = order

        if not order.is_active() and order.vt_orderid in self.active_orderids:
            self.active_orderids.remove(order.vt_orderid)

    def get_signal(self) -> pl.DataFrame:
        """Get current signal"""
        return self.strategy_engine.get_signal()

    def buy(self, vt_symbol: str, price: float, volume: float) -> list[str]:
        """Buy to open position"""
        return self.send_order(vt_symbol, Direction.LONG, Offset.OPEN, price, volume)

    def sell(self, vt_symbol: str, price: float, volume: float) -> list[str]:
        """Sell to close position"""
        return self.send_order(vt_symbol, Direction.SHORT, Offset.CLOSE, price, volume)

    def short(self, vt_symbol: str, price: float, volume: float) -> list[str]:
        """Sell to open position"""
        return self.send_order(vt_symbol, Direction.SHORT, Offset.OPEN, price, volume)

    def cover(self, vt_symbol: str, price: float, volume: float) -> list[str]:
        """Buy to close position"""
        return self.send_order(vt_symbol, Direction.LONG, Offset.CLOSE, price, volume)

    def send_order(
        self,
        vt_symbol: str,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: float
    ) -> list[str]:
        """Send order"""
        vt_orderids: list = self.strategy_engine.send_order(
            self, vt_symbol, direction, offset, price, volume
        )

        for vt_orderid in vt_orderids:
            self.active_orderids.add(vt_orderid)

        return vt_orderids

    def cancel_order(self, vt_orderid: str) -> None:
        """Cancel order"""
        self.strategy_engine.cancel_order(self, vt_orderid)

    def cancel_all(self) -> None:
        """Cancel all active orders"""
        for vt_orderid in list(self.active_orderids):
            self.cancel_order(vt_orderid)

    def get_pos(self, vt_symbol: str) -> float:
        """Query current position"""
        return self.pos_data[vt_symbol]

    def get_target(self, vt_symbol: str) -> float:
        """Query target position"""
        return self.target_data[vt_symbol]

    def set_target(self, vt_symbol: str, target: int) -> None:
        """Set target position"""
        self.target_data[vt_symbol] = target

    def execute_trading(self, bars: dict[str, BarData], price_add: float) -> None:
        """Execute position adjustment based on targets"""
        self.cancel_all()

        # Only send orders for contracts with current bar data
        for vt_symbol, bar in bars.items():
            # Calculate position difference
            target: float = self.get_target(vt_symbol)
            pos: float = self.get_pos(vt_symbol)
            diff: float = target - pos

            # Long position
            if diff > 0:
                # Calculate long order price
                order_price: float = bar.close_price * (1 + price_add)

                # Calculate cover and buy volumes
                cover_volume: float = 0
                buy_volume: float = 0

                if pos < 0:
                    cover_volume = min(diff, abs(pos))
                    buy_volume = diff - cover_volume
                else:
                    buy_volume = diff

                # Send corresponding orders
                if cover_volume:
                    self.cover(vt_symbol, order_price, cover_volume)

                if buy_volume:
                    self.buy(vt_symbol, order_price, buy_volume)
            # Short position
            elif diff < 0:
                # Calculate short order price
                order_price = bar.close_price * (1 - price_add)

                # Calculate sell and short volumes
                sell_volume: float = 0
                short_volume: float = 0

                if pos > 0:
                    sell_volume = min(abs(diff), pos)
                    short_volume = abs(diff) - sell_volume
                else:
                    short_volume = abs(diff)

                # Send corresponding orders
                if sell_volume:
                    self.sell(vt_symbol, order_price, sell_volume)

                if short_volume:
                    self.short(vt_symbol, order_price, short_volume)

    def write_log(self, msg: str) -> None:
        """Write log message"""
        self.strategy_engine.write_log(msg, self)

    def get_cash_available(self) -> float:
        """Get available cash"""
        return self.strategy_engine.get_cash_available()

    def get_holding_value(self) -> float:
        """Get holding market value"""
        return self.strategy_engine.get_holding_value()

    def get_portfolio_value(self) -> float:
        """Get total portfolio value"""
        return self.get_cash_available() + self.get_holding_value()

    def get_cash(self) -> float:
        """Legacy compatibility method"""
        return self.get_cash_available()
