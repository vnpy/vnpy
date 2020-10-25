""""""
from abc import ABC
from copy import copy
from typing import Dict, Set, List, TYPE_CHECKING
from collections import defaultdict

from vnpy.trader.constant import Interval, Direction, Offset
from vnpy.trader.object import BarData, TickData, OrderData, TradeData
from vnpy.trader.utility import virtual

if TYPE_CHECKING:
    from .engine import StrategyEngine


class StrategyTemplate(ABC):
    """"""

    author = ""
    parameters = []
    variables = []

    def __init__(
        self,
        strategy_engine: "StrategyEngine",
        strategy_name: str,
        vt_symbols: List[str],
        setting: dict,
    ):
        """"""
        self.strategy_engine: "StrategyEngine" = strategy_engine
        self.strategy_name: str = strategy_name
        self.vt_symbols: List[str] = vt_symbols

        self.inited: bool = False
        self.trading: bool = False
        self.pos: Dict[str, int] = defaultdict(int)

        self.orders: Dict[str, OrderData] = {}
        self.active_orderids: Set[str] = set()

        # Copy a new variables list here to avoid duplicate insert when multiple
        # strategy instances are created with the same strategy class.
        self.variables: List = copy(self.variables)
        self.variables.insert(0, "inited")
        self.variables.insert(1, "trading")
        self.variables.insert(2, "pos")

        self.update_setting(setting)

    def update_setting(self, setting: dict) -> None:
        """
        Update strategy parameter wtih value in setting dict.
        """
        for name in self.parameters:
            if name in setting:
                setattr(self, name, setting[name])

    @classmethod
    def get_class_parameters(cls) -> Dict:
        """
        Get default parameters dict of strategy class.
        """
        class_parameters = {}
        for name in cls.parameters:
            class_parameters[name] = getattr(cls, name)
        return class_parameters

    def get_parameters(self) -> Dict:
        """
        Get strategy parameters dict.
        """
        strategy_parameters = {}
        for name in self.parameters:
            strategy_parameters[name] = getattr(self, name)
        return strategy_parameters

    def get_variables(self) -> Dict:
        """
        Get strategy variables dict.
        """
        strategy_variables = {}
        for name in self.variables:
            strategy_variables[name] = getattr(self, name)
        return strategy_variables

    def get_data(self) -> Dict:
        """
        Get strategy data.
        """
        strategy_data = {
            "strategy_name": self.strategy_name,
            "vt_symbols": self.vt_symbols,
            "class_name": self.__class__.__name__,
            "author": self.author,
            "parameters": self.get_parameters(),
            "variables": self.get_variables(),
        }
        return strategy_data

    @virtual
    def on_init(self) -> None:
        """
        Callback when strategy is inited.
        """
        pass

    @virtual
    def on_start(self) -> None:
        """
        Callback when strategy is started.
        """
        pass

    @virtual
    def on_stop(self) -> None:
        """
        Callback when strategy is stopped.
        """
        pass

    @virtual
    def on_tick(self, tick: TickData) -> None:
        """
        Callback of new tick data update.
        """
        pass

    @virtual
    def on_bars(self, bars: Dict[str, BarData]) -> None:
        """
        Callback of new bar data update.
        """
        pass

    def update_trade(self, trade: TradeData) -> None:
        """
        Callback of new trade data update.
        """
        if trade.direction == Direction.LONG:
            self.pos[trade.vt_symbol] += trade.volume
        else:
            self.pos[trade.vt_symbol] -= trade.volume

    def update_order(self, order: OrderData) -> None:
        """
        Callback of new order data update.
        """
        self.orders[order.vt_orderid] = order

        if not order.is_active() and order.vt_orderid in self.active_orderids:
            self.active_orderids.remove(order.vt_orderid)

    def buy(self, vt_symbol: str, price: float, volume: float, lock: bool = False) -> List[str]:
        """
        Send buy order to open a long position.
        """
        return self.send_order(vt_symbol, Direction.LONG, Offset.OPEN, price, volume, lock)

    def sell(self, vt_symbol: str, price: float, volume: float, lock: bool = False) -> List[str]:
        """
        Send sell order to close a long position.
        """
        return self.send_order(vt_symbol, Direction.SHORT, Offset.CLOSE, price, volume, lock)

    def short(self, vt_symbol: str, price: float, volume: float, lock: bool = False) -> List[str]:
        """
        Send short order to open as short position.
        """
        return self.send_order(vt_symbol, Direction.SHORT, Offset.OPEN, price, volume, lock)

    def cover(self, vt_symbol: str, price: float, volume: float, lock: bool = False) -> List[str]:
        """
        Send cover order to close a short position.
        """
        return self.send_order(vt_symbol, Direction.LONG, Offset.CLOSE, price, volume, lock)

    def send_order(
        self,
        vt_symbol: str,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: float,
        lock: bool = False
    ) -> List[str]:
        """
        Send a new order.
        """
        if self.trading:
            vt_orderids = self.strategy_engine.send_order(
                self, vt_symbol, direction, offset, price, volume, lock
            )

            for vt_orderid in vt_orderids:
                self.active_orderids.add(vt_orderid)

            return vt_orderids
        else:
            return []

    def cancel_order(self, vt_orderid: str) -> None:
        """
        Cancel an existing order.
        """
        if self.trading:
            self.strategy_engine.cancel_order(self, vt_orderid)

    def cancel_all(self) -> None:
        """
        Cancel all orders sent by strategy.
        """
        for vt_orderid in list(self.active_orderids):
            self.cancel_order(vt_orderid)

    def get_pos(self, vt_symbol: str) -> int:
        """"""
        return self.pos.get(vt_symbol, 0)

    def get_order(self, vt_orderid: str) -> OrderData:
        """"""
        return self.orders.get(vt_orderid, None)

    def get_all_active_orderids(self) -> List[OrderData]:
        """"""
        return list(self.active_orderids)

    def write_log(self, msg: str) -> None:
        """
        Write a log message.
        """
        self.strategy_engine.write_log(msg, self)

    def load_bars(self, days: int, interval: Interval = Interval.MINUTE) -> None:
        """
        Load historical bar data for initializing strategy.
        """
        self.strategy_engine.load_bars(self, days, interval)

    def put_event(self) -> None:
        """
        Put an strategy data event for ui update.
        """
        if self.inited:
            self.strategy_engine.put_strategy_event(self)

    def send_email(self, msg) -> None:
        """
        Send email to default receiver.
        """
        if self.inited:
            self.strategy_engine.send_email(msg, self)

    def sync_data(self):
        """
        Sync strategy variables value into disk storage.
        """
        if self.trading:
            self.strategy_engine.sync_strategy_data(self)
