""""""

from abc import ABC

from vnpy.trader.engine import BaseEngine
from vnpy.trader.object import TickData, OrderData, TradeData, BarData

from .base import CtaOrderType, StopOrder


class CtaTemplate(ABC):
    """"""

    _inited = False
    _trading = False
    _pos = 0

    author = ""
    vt_symbol = ""

    parameters = []
    variables = []

    def __init__(self, engine: BaseEngine, setting: dict):
        """"""
        self.engine = engine

        self.vt_symbol = setting["vt_symbol"]

        for name in self.parameters:
            if name in setting:
                setattr(self, name, setting[name])

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
            stop: bool = False
    ):
        """
        Send a new order.
        """
        return self.engine.send_order(self, order_type, price, volume, stop)

    def cancel_order(self, vt_orderid):
        """
        Cancel an existing order.
        """
        self.engine.cancel_order(vt_orderid)

    def cancel_all(self):
        """
        Cancel all orders sent by strategy.
        """
        self.engine.cancel_all(self)

    def write_log(self, msg):
        """
        Write a log message.
        """
        self.engine.write_log(self, msg)

    def get_engine_type(self):
        """
        Return whether the engine is backtesting or live trading.
        """
        return self.engine.get_engine_type()

    def get_pos(self):
        """
        Return current net position of the strategy.
        """
        return self._pos
