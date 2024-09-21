from abc import ABC, abstractmethod
from copy import copy
from datetime import datetime
from typing import TYPE_CHECKING, Optional
from collections import defaultdict

import pandas as pd
import polars as pl

from vnpy.trader.constant import Interval, Direction, Offset, Exchange
from vnpy.trader.object import BarData, TickData, OrderData, TradeData, FactorData
from vnpy.trader.utility import virtual, BarGenerator, extract_vt_symbol, convert_dict_to_dataframe

from vnpy.app.portfolio_strategy.base import EngineType

if TYPE_CHECKING:
    from vnpy.app.portfolio_strategy.engine import StrategyEngine


class StrategyTemplate(ABC):
    """Portfolio Strategy Template"""

    author: str = ""
    parameters: list = []
    variables: list = []
    factors: list = []  # {factor_name}_{interval}
    exchange: Exchange = Exchange.BINANCE
    interval: Interval = Interval.MINUTE

    def __init__(
            self,
            strategy_engine: "StrategyEngine",
            strategy_name: str,
            vt_symbols: list[str],
            setting: dict
    ) -> None:
        """Constructor"""
        self.strategy_engine: "StrategyEngine" = strategy_engine
        self.strategy_name: str = strategy_name
        self.vt_symbols: list[str] = vt_symbols

        self.portfolio_value: float = 0

        # Control variables for strategy status
        self.inited: bool = False
        self.trading: bool = False

        # Position data dictionaries
        self.pos_data: dict[str, float] = defaultdict(float)  # Actual position
        self.target_data: dict[str, float] = defaultdict(float)  # Target position

        # Tick and Bar data dictionaries
        self.ticks: dict[str, TickData] = defaultdict(TickData)
        self.bars: dict[str, BarData] = defaultdict(BarData)

        # Order cache and active orders
        self.orders: dict[str, OrderData] = {}
        self.active_orderids: set[str] = set()

        # Copy the list of variables and insert default ones
        self.variables: list = copy(self.variables)
        self.variables.insert(0, "inited")
        self.variables.insert(1, "trading")
        self.variables.insert(2, "pos_data")
        self.variables.insert(3, "target_data")

        # Set strategy parameters
        self.update_setting(setting)
        self.init_factors()

    def init_factors(self) -> None:
        """Initialize strategy factors"""
        self.factor_dict: dict[tuple[str, str], FactorData] = {}
        self.status_dict: dict[tuple[str, str], bool] = {}
        for vt_symbol in self.vt_symbols:
            symbol, _ = extract_vt_symbol(vt_symbol, is_factor=False)
            for factor_name in self.factors:
                factor: FactorData = FactorData(
                    symbol=symbol,
                    exchange=self.exchange,
                    datetime=datetime.now(),
                    interval=self.interval,
                    value=0,
                    factor_name=factor_name,
                    gateway_name="strategy_template"
                )
                self.factor_dict[(symbol, factor_name)] = factor
                self.status_dict[(symbol, factor_name)] = False

    def update_setting(self, setting: dict) -> None:
        """Set strategy parameters"""
        for name in self.parameters:
            if name in setting:
                setattr(self, name, setting[name])

    def init_status_dict(self) -> None:
        """Initialize factor check list"""
        self.status_dict.update((key, False) for key in self.status_dict)

    @classmethod
    def get_class_parameters(cls) -> dict:
        """Get default strategy parameters"""
        class_parameters: dict = {}
        for name in cls.parameters:
            class_parameters[name] = getattr(cls, name)
        return class_parameters

    def get_parameters(self) -> dict:
        """Get strategy parameters"""
        strategy_parameters: dict = {}
        for name in self.parameters:
            strategy_parameters[name] = getattr(self, name)
        return strategy_parameters

    def get_variables(self) -> dict:
        """Get strategy variables"""
        strategy_variables: dict = {}
        for name in self.variables:
            strategy_variables[name] = getattr(self, name)
        return strategy_variables

    def get_data(self) -> dict:
        """Get strategy status data"""
        strategy_data: dict = {
            "strategy_name": self.strategy_name,
            "vt_symbols": self.vt_symbols,
            "class_name": self.__class__.__name__,
            "author": self.author,
            "parameters": self.get_parameters(),
            "variables": self.get_variables(),
            "factors": self.factors,
            "factor_data": self.factor_dict
        }
        return strategy_data

    @virtual
    def on_init(self) -> None:
        """Strategy initialization callback"""
        self.inited = True

    @virtual
    def on_start(self) -> None:
        """Strategy start callback"""
        self.trading = True

    @virtual
    def on_stop(self) -> None:
        """Strategy stop callback"""
        self.trading = False

    @virtual
    def on_tick(self, tick: TickData) -> None:
        """Tick data push callback"""
        if tick.vt_symbol in self.vt_symbols:
            self.ticks[tick.vt_symbol] = tick

    @virtual
    def on_bars(self, bars: dict[str, BarData]) -> None:
        """Bar slice callback"""
        pass

    def on_bar(self, bar: BarData) -> None:
        """Bar data push callback"""
        if bar.vt_symbol in self.vt_symbols:
            self.bars[bar.vt_symbol] = bar

    def on_factor(self, factor: FactorData) -> None:
        """Factor push callback"""
        if self.trading:
            updated_all: bool = self.update_factor(factor)
            if updated_all:
                factor_df: Optional[pd.DataFrame, pl.DataFrame] = convert_dict_to_dataframe(data=self.factor_dict, is_polars=False)
                self.calculate(factor_df)
                self.rebalance_portfolio(self.bars)
                self.init_status_dict()

    def update_factor(self, factor: FactorData) -> bool:
        """Factor data update"""
        symbol = factor.symbol
        factor_name = factor.factor_name
        key = (symbol, factor_name)
        if key in self.factor_dict:
            self.factor_dict[key] = factor
            self.status_dict[key] = True
        else:
            self.write_log(f"Factor {factor.factor_name} is not in the strategy factor list")

        return all(self.status_dict.values())

    @abstractmethod
    def calculate(self, df) -> None:
        """Factor push completion callback"""
        pass

    def update_trade(self, trade: TradeData) -> None:
        """Update trade data"""
        if trade.direction == Direction.LONG:
            self.pos_data[trade.vt_symbol] += trade.volume
        else:
            self.pos_data[trade.vt_symbol] -= trade.volume

    def update_order(self, order: OrderData) -> None:
        """Update order data"""
        self.orders[order.vt_orderid] = order

        if not order.is_active() and order.vt_orderid in self.active_orderids:
            self.active_orderids.remove(order.vt_orderid)

    def buy(self, vt_symbol: str, price: float, volume: float, lock: bool = False, net: bool = False) -> list[str]:
        """Buy to open position"""
        return self.send_order(vt_symbol, Direction.LONG, Offset.OPEN, price, volume, lock, net)

    def sell(self, vt_symbol: str, price: float, volume: float, lock: bool = False, net: bool = False) -> list[str]:
        """Sell to close position"""
        return self.send_order(vt_symbol, Direction.SHORT, Offset.CLOSE, price, volume, lock, net)

    def short(self, vt_symbol: str, price: float, volume: float, lock: bool = False, net: bool = False) -> list[str]:
        """Sell to open position"""
        return self.send_order(vt_symbol, Direction.SHORT, Offset.OPEN, price, volume, lock, net)

    def cover(self, vt_symbol: str, price: float, volume: float, lock: bool = False, net: bool = False) -> list[str]:
        """Buy to close position"""
        return self.send_order(vt_symbol, Direction.LONG, Offset.CLOSE, price, volume, lock, net)

    def send_order(
            self,
            vt_symbol: str,
            direction: Direction,
            offset: Offset,
            price: float,
            volume: float,
            lock: bool = False,
            net: bool = False,
    ) -> list[str]:
        """Send order"""
        if self.trading:
            vt_orderids: list = self.strategy_engine.send_order(
                self, vt_symbol, direction, offset, price, volume, lock, net
            )
            for vt_orderid in vt_orderids:
                self.active_orderids.add(vt_orderid)
            return vt_orderids
        else:
            return []

    def cancel_order(self, vt_orderid: str) -> None:
        """Cancel order"""
        if self.trading:
            self.strategy_engine.cancel_order(self, vt_orderid)

    def cancel_all(self) -> None:
        """Cancel all active orders"""
        for vt_orderid in list(self.active_orderids):
            self.cancel_order(vt_orderid)

    def get_pos(self, vt_symbol: str) -> float:
        """Get current position"""
        return self.pos_data.get(vt_symbol, 0)

    def get_target(self, vt_symbol: str) -> float:
        """Get target position"""
        return self.target_data[vt_symbol]

    def set_target(self, vt_symbol: str, target: float) -> None:
        """Set target position"""
        self.target_data[vt_symbol] = target

    def rebalance_portfolio(self, bars: dict[str, BarData]) -> None:
        """Rebalance portfolio based on target positions"""
        self.cancel_all()

        # Place orders only for symbols with the current bar data
        for vt_symbol, bar in bars.items():
            # Calculate position difference
            target: float = self.get_target(vt_symbol)
            pos: float = self.get_pos(vt_symbol)
            diff: float = target - pos

            # Long position
            if diff > 0:
                # Calculate order price for long
                order_price: float = self.calculate_price(vt_symbol, Direction.LONG, bar.close_price)

                # Determine cover and buy volumes
                cover_volume: float = 0
                buy_volume: float = 0

                if pos < 0:
                    cover_volume = min(diff, abs(pos))
                    buy_volume = diff - cover_volume
                else:
                    buy_volume = diff

                # Place orders
                if cover_volume:
                    self.cover(vt_symbol, order_price, cover_volume)

                if buy_volume:
                    self.buy(vt_symbol, order_price, buy_volume)

            # Short position
            elif diff < 0:
                # Calculate order price for short
                order_price: float = self.calculate_price(vt_symbol, Direction.SHORT, bar.close_price)

                # Determine sell and short volumes
                sell_volume: float = 0
                short_volume: float = 0

                if pos > 0:
                    sell_volume = min(abs(diff), pos)
                    short_volume = abs(diff) - sell_volume
                else:
                    short_volume = abs(diff)

                # Place orders
                if sell_volume:
                    self.sell(vt_symbol, order_price, sell_volume)

                if short_volume:
                    self.short(vt_symbol, order_price, short_volume)

    @virtual
    def calculate_price(self, vt_symbol: str, direction: Direction, reference: float) -> float:
        """Calculate the rebalancing order price (can be overridden)"""
        return reference

    def get_order(self, vt_orderid: str) -> Optional[OrderData]:
        """Get order data"""
        return self.orders.get(vt_orderid, None)

    def get_all_active_orderids(self) -> list[str]:
        """Get all active order IDs"""
        return list(self.active_orderids)

    def write_log(self, msg: str) -> None:
        """Log a message"""
        self.strategy_engine.write_log(msg, self)

    def get_engine_type(self) -> EngineType:
        """Get the engine type"""
        return self.strategy_engine.get_engine_type()

    def get_pricetick(self, vt_symbol: str) -> float:
        """Get the price tick of the contract"""
        return self.strategy_engine.get_pricetick(self, vt_symbol)

    def get_size(self, vt_symbol: str) -> float | None:
        """Get the contract multiplier"""
        return self.strategy_engine.get_size(self, vt_symbol)

    def load_bars(self, days: int, interval: Interval = Interval.MINUTE) -> None:
        """Load historical bar data for initialization"""
        self.strategy_engine.load_bars(self, days, interval)

    def put_event(self) -> None:
        """Push strategy data update event"""
        if self.inited:
            self.strategy_engine.put_strategy_event(self)

    def send_email(self, msg: str) -> None:
        """Send an email notification"""
        if self.inited:
            self.strategy_engine.send_email(msg, self)

    def sync_data(self) -> None:
        """Sync strategy state data to a file"""
        if self.trading:
            self.strategy_engine.sync_strategy_data(self)