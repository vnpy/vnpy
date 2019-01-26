""""""

from abc import ABC
from typing import Any, Callable

from vnpy.trader.constant import Interval
from vnpy.trader.object import BarData, OrderData, TickData, TradeData
from .base import CtaOrderType, StopOrder


class CtaTemplate(ABC):
    """"""

    author = ""
    parameters = []
    variables = []

    def __init__(
        self,
        cta_engine: Any,
        strategy_name: str,
        vt_symbol: str,
        setting: dict,
    ):
        """"""
        self.cta_engine = cta_engine
        self.strategy_name = strategy_name
        self.vt_symbol = vt_symbol

        self.inited = False
        self.trading = False
        self.pos = 0

        self.variables.insert(0, "inited")
        self.variables.insert(1, "trading")
        self.variables.insert(2, "pos")

        self.update_setting(setting)

    def update_setting(self, setting: dict):
        """
        Update strategy parameter wtih value in setting dict.
        """
        for name in self.parameters:
            if name in setting:
                setattr(self, name, setting[name])

    @classmethod
    def get_class_parameters(cls):
        """
        Get default parameters dict of strategy class.
        """
        class_parameters = {}
        for name in cls.parameters:
            class_parameters[name] = getattr(cls, name)
        return class_parameters

    def get_parameters(self):
        """
        Get strategy parameters dict.
        """
        strategy_parameters = {}
        for name in self.parameters:
            strategy_parameters[name] = getattr(self, name)
        return strategy_parameters

    def get_variables(self):
        """
        Get strategy variables dict.
        """
        strategy_variables = {}
        for name in self.variables:
            strategy_variables[name] = getattr(self, name)
        return strategy_variables

    def get_data(self):
        """
        Get strategy data.
        """
        strategy_data = {
            "strategy_name": self.strategy_name,
            "vt_symbol": self.vt_symbol,
            "class_name": self.__class__.__name__,
            "author": self.author,
            "parameters": self.get_parameters(),
            "variables": self.get_variables(),
        }
        return strategy_data

    def on_init(self):
        """
        Callback when strategy is inited.
        """
        pass

    def on_start(self):
        """
        Callback when strategy is started.
        """
        pass

    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        pass

    def on_trade(self, trade: TradeData):
        """
        Callback of new trade data update.
        """
        pass

    def on_order(self, order: OrderData):
        """
        Callback of new order data update.
        """
        pass

    def on_stop_order(self, stop_order: StopOrder):
        """
        Callback of stop order update.
        """
        pass

    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        pass

    def buy(self, price: float, volume: float, stop: bool = False):
        """
        Send buy order to open a long position.
        """
        return self.send_order(CtaOrderType.BUY, price, volume, stop)

    def sell(self, price: float, volume: float, stop: bool = False):
        """
        Send sell order to close a long position.
        """
        return self.send_order(CtaOrderType.SELL, price, volume, stop)

    def short(self, price: float, volume: float, stop: bool = False):
        """
        Send short order to open as short position.
        """
        return self.send_order(CtaOrderType.SHORT, price, volume, stop)

    def cover(self, price: float, volume: float, stop: bool = False):
        """
        Send cover order to close a short position.
        """
        return self.send_order(CtaOrderType.COVER, price, volume, stop)

    def send_order(
        self,
        order_type: CtaOrderType,
        price: float,
        volume: float,
        stop: bool = False,
    ):
        """
        Send a new order.
        """
        return self.cta_engine.send_order(
            self, order_type, price, volume, stop
        )

    def cancel_order(self, vt_orderid: str):
        """
        Cancel an existing order.
        """
        self.cta_engine.cancel_order(vt_orderid)

    def cancel_all(self):
        """
        Cancel all orders sent by strategy.
        """
        self.cta_engine.cancel_all(self)

    def write_log(self, msg: str):
        """
        Write a log message.
        """
        self.cta_engine.write_log(self, msg)

    def get_engine_type(self):
        """
        Return whether the cta_engine is backtesting or live trading.
        """
        return self.cta_engine.get_engine_type()

    def load_bar(
        self,
        days: int,
        interval: Interval = Interval.MINUTE,
        callback: Callable = None,
    ):
        """
        Load historical bar data for initializing strategy.
        """
        if not callback:
            callback = self.on_bar

        self.cta_engine.load_bar(self.vt_symbol, days, interval, callback)

    def load_tick(self, days: int):
        """
        Load historical tick data for initializing strategy.
        """
        self.cta_engine.load_tick(self.vt_symbol, days, self.on_tick)

    def put_event(self):
        """
        Put an strategy data event for ui update.
        """
        self.cta_engine.put_strategy_event(self)
