
from collections import defaultdict
from typing import Dict, List
from math import floor, ceil

from vnpy.trader.object import TickData, TradeData, OrderData, ContractData
from vnpy.trader.constant import Direction, Status, Offset
from vnpy.trader.utility import virtual

from .base import SpreadData
from .engine import SpreadAlgoEngine


class SpreadAlgoTemplate:
    """
    Template for writing spread trading algos.
    """
    algo_name = "AlgoTemplate"

    def __init__(
        self,
        algo_engine: SpreadAlgoEngine,
        algoid: str,
        spread: SpreadData,
        direction: Direction,
        price: float,
        volume: float,
        payup: int
    ):
        """"""
        self.algo_engine: SpreadAlgoEngine = algo_engine
        self.algoid: str = algoid
        self.spread: SpreadData = spread

        self.direction: Direction = direction
        self.price: float = price
        self.volume: float = volume
        self.payup: int = payup

        if direction == Direction.LONG:
            self.target = volume
        else:
            self.target = -volume

        self.status: Status = Status.NOTTRADED
        self.traded: float = 0

        self.leg_traded: Dict[str, float] = defaultdict(int)
        self.leg_orders: Dict[str, List[str]] = defaultdict[list]

    def is_active(self):
        """"""
        if self.status not in [Status.CANCELLED, Status.ALLTRADED]:
            return True
        else:
            return False

    def stop(self):
        """"""
        if self.is_active():
            self.cancel_leg_order()
            self.status = Status.CANCELLED
            self.put_event()

    def update_tick(self, tick: TickData):
        """"""
        self.on_tick(tick)

    def update_trade(self, trade: TradeData):
        """"""
        if trade.direction == Direction.LONG:
            self.leg_traded[trade.vt_symbol] += trade.volume
        else:
            self.leg_traded[trade.vt_symbol] -= trade.volume

        self.calculate_traded()

        self.on_trade(trade)

    def update_order(self, order: OrderData):
        """"""
        if not order.is_active():
            self.leg_orders[order.vt_symbol].remove(order.vt_orderid)

        self.on_order(order)

    def update_timer(self):
        """"""
        self.on_timer()

    def put_event(self):
        """"""
        self.algo_engine.put_event(self)

    def write_log(self, msg: str):
        """"""
        self.algo_engine.write_log(msg)

    def send_long_order(self, vt_symbol: str, price: float, volume: float):
        """"""
        self.send_order(vt_symbol, price, volume, Direction.LONG)

    def send_short_order(self, vt_symbol: str, price: float, volume: float):
        """"""
        self.send_order(vt_symbol, price, volume, Direction.SHORT)

    def send_order(
        self,
        vt_symbol: str,
        price: float,
        volume: float,
        direction: Direction,
    ):
        """"""
        vt_orderids = self.algo_engine.send_order(
            self,
            vt_symbol,
            price,
            volume,
            direction,
        )

        self.leg_orders[vt_symbol].extend(vt_orderids)

    def cancel_leg_order(self, vt_symbol: str):
        """"""
        for vt_orderid in self.leg_orders[vt_symbol]:
            self.algo_engine.cancel_order(vt_orderid)

    def cancel_all_order(self):
        """"""
        for vt_symbol in self.leg_orders.keys():
            self.cancel_leg_order(vt_symbol)

    def calculate_traded(self):
        """"""
        self.traded = 0

        for n, leg in enumerate(self.spread.legs.values()):
            leg_traded = self.leg_traded[leg.vt_symbol]
            adjusted_leg_traded = leg_traded / leg.trading_multiplier

            if adjusted_leg_traded > 0:
                adjusted_leg_traded = floor(adjusted_leg_traded)
            else:
                adjusted_leg_traded = ceil(adjusted_leg_traded)

            if not n:
                self.traded = adjusted_leg_traded
            else:
                if adjusted_leg_traded > 0:
                    self.traded = min(self.traded, adjusted_leg_traded)
                else:
                    self.traded = max(self.traded, adjusted_leg_traded)

        if self.traded == self.target:
            self.status = Status.ALLTRADED
        elif not self.traded:
            self.status = Status.NOTTRADED
        else:
            self.status = Status.PARTTRADED

    def get_tick(self, vt_symbol: str) -> TickData:
        """"""
        return self.algo_engine.get_tick(vt_symbol)

    def get_contract(self, vt_symbol: str) -> ContractData:
        """"""
        return self.algo_engine.get_contract(vt_symbol)

    @virtual
    def on_tick(self, tick: TickData):
        """"""
        pass

    @virtual
    def on_order(self, order: OrderData):
        """"""
        pass

    @virtual
    def on_trade(self, trade: TradeData):
        """"""
        pass

    @virtual
    def on_timer(self):
        """"""
        pass
