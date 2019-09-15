
from collections import defaultdict
from typing import Dict, List
from math import floor, ceil

from vnpy.trader.object import TickData, TradeData, OrderData, ContractData
from vnpy.trader.constant import Direction, Status
from vnpy.trader.utility import virtual

from .base import SpreadData


class SpreadAlgoTemplate:
    """
    Template for writing spread trading algos.
    """
    algo_name = "AlgoTemplate"

    def __init__(
        self,
        algo_engine,
        algoid: str,
        spread: SpreadData,
        direction: Direction,
        price: float,
        volume: float,
        payup: int,
        interval: int
    ):
        """"""
        self.algo_engine = algo_engine
        self.algoid: str = algoid

        self.spread: SpreadData = spread
        self.spread_name: str = spread.name

        self.direction: Direction = direction
        self.price: float = price
        self.volume: float = volume
        self.payup: int = payup
        self.interval = interval

        if direction == Direction.LONG:
            self.target = volume
        else:
            self.target = -volume

        self.status: Status = Status.NOTTRADED  # Algo status
        self.count: int = 0                     # Timer count
        self.traded: float = 0                  # Volume traded
        self.traded_volume: float = 0           # Volume traded (Abs value)

        self.leg_traded: Dict[str, float] = defaultdict(int)
        self.leg_orders: Dict[str, List[str]] = defaultdict(list)

    def is_active(self):
        """"""
        if self.status not in [Status.CANCELLED, Status.ALLTRADED]:
            return True
        else:
            return False

    def check_order_finished(self):
        """"""
        finished = True

        for leg in self.spread.legs.values():
            vt_orderids = self.leg_orders[leg.vt_symbol]

            if vt_orderids:
                finished = False
                break

        return finished

    def check_hedge_finished(self):
        """"""
        active_symbol = self.spread.active_leg.vt_symbol
        active_traded = self.leg_traded[active_symbol]

        spread_volume = self.spread.calculate_spread_volume(
            active_symbol, active_traded
        )

        finished = True

        for leg in self.spread.passive_legs:
            passive_symbol = leg.vt_symbol

            leg_target = self.spread.calculate_leg_volume(
                passive_symbol, spread_volume
            )
            leg_traded = self.leg_traded[passive_symbol]

            if leg_traded != leg_target:
                finished = False
                break

        return finished

    def stop(self):
        """"""
        if self.is_active():
            self.cancel_all_order()
            self.status = Status.CANCELLED
            self.put_algo_event()

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
        self.count += 1
        if self.count < self.interval:
            return
        self.count = 0

        self.on_interval()

    def put_event(self):
        """"""
        self.algo_engine.put_event(self)

    def write_log(self, msg: str):
        """"""
        self.algo_engine.write_algo_log(msg)

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

        self.traded_volume = abs(self.traded)

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
    def on_interval(self):
        """"""
        pass
