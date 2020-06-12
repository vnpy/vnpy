
from collections import defaultdict
from typing import Dict, List, Set, Callable
from copy import copy

from vnpy.trader.object import (
    TickData, TradeData, OrderData, ContractData, BarData
)
from vnpy.trader.constant import Direction, Status, Offset, Interval
from vnpy.trader.utility import virtual, floor_to, ceil_to, round_to

from .base import SpreadData, calculate_inverse_volume


class SpreadAlgoTemplate:
    """
    Template for implementing spread trading algos.
    """
    algo_name = "AlgoTemplate"

    def __init__(
        self,
        algo_engine,
        algoid: str,
        spread: SpreadData,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: float,
        payup: int,
        interval: int,
        lock: bool,
    ):
        """"""
        self.algo_engine = algo_engine
        self.algoid: str = algoid

        self.spread: SpreadData = spread
        self.spread_name: str = spread.name

        self.offset: Offset = offset
        self.direction: Direction = direction
        self.price: float = price
        self.volume: float = volume
        self.payup: int = payup
        self.interval = interval
        self.lock = lock

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

        self.order_trade_volume: Dict[str, int] = defaultdict(int)
        self.orders: Dict[str, OrderData] = {}

        self.write_log("算法已启动")

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

            # For linear contract, traded volume must be same as target volume
            if not self.spread.is_inverse(leg.vt_symbol):
                if leg_traded != leg_target:
                    finished = False
                    break
            # For inverse contract, the difference must be lower than min volume
            else:
                leg_min_volume = self.spread.calculate_leg_volume(
                    passive_symbol, self.spread.min_volume
                )

                dif = leg_target - leg_traded
                if abs(dif) < leg_min_volume:
                    finished = False
                    break

        return finished

    def check_algo_finished(self) -> bool:
        """"""
        finished = True

        for vt_symbol, leg in self.spread.legs.items():
            leg_traded = self.leg_traded[vt_symbol]

            trading_multiplier = self.spread.trading_multipliers[vt_symbol]
            size = self.spread.get_leg_size(vt_symbol)

            if self.spread.is_inverse(vt_symbol):
                leg_target = calculate_inverse_volume(
                    self.target * trading_multiplier,
                    leg.last_price,
                    size
                )
                min_change = calculate_inverse_volume(
                    leg.min_volume,
                    leg.last_price,
                    size
                )
            else:
                leg_target = self.target * trading_multiplier
                min_change = leg.min_volume

            leg_left = leg_target - leg_traded
            if abs(leg_left) >= min_change:
                finished = False

        return finished

    def stop(self):
        """"""
        if self.is_active():
            self.cancel_all_order()
            self.status = Status.CANCELLED
            self.write_log("算法已停止")
            self.put_event()

    def update_tick(self, tick: TickData):
        """"""
        self.on_tick(tick)

    def update_trade(self, trade: TradeData):
        """"""
        # For inverse contract:
        # record coin trading volume as leg trading volume,
        # not contract volume!
        if self.spread.is_inverse(trade.vt_symbol):
            size = self.spread.get_leg_size(trade.vt_symbol)

            trade_volume = calculate_inverse_volume(
                trade.volume,
                trade.price,
                size
            )
        else:
            trade_volume = trade.volume

        if trade.direction == Direction.LONG:
            self.leg_traded[trade.vt_symbol] += trade_volume
        else:
            self.leg_traded[trade.vt_symbol] -= trade_volume

        self.calculate_traded()

        # Sum up total traded volume of each order,
        self.order_trade_volume[trade.vt_orderid] += trade.volume

        # Remove order from active list if all volume traded
        order = self.orders[trade.vt_orderid]
        trade_volume = self.order_trade_volume[order.vt_orderid]

        if trade_volume == order.volume:
            vt_orderids = self.leg_orders[order.vt_symbol]
            if order.vt_orderid in vt_orderids:
                vt_orderids.remove(order.vt_orderid)

        msg = "委托成交，{}，{}，{}@{}".format(
            trade.vt_symbol,
            trade.direction,
            trade.volume,
            trade.price
        )
        self.write_log(msg)

        self.put_event()
        self.on_trade(trade)

    def update_order(self, order: OrderData):
        """"""
        self.orders[order.vt_orderid] = order

        # Remove order from active list if rejected or cancelled
        if order.status in {Status.REJECTED, Status.CANCELLED}:
            vt_orderids = self.leg_orders[order.vt_symbol]
            if order.vt_orderid in vt_orderids:
                vt_orderids.remove(order.vt_orderid)

        self.on_order(order)

    def update_timer(self):
        """"""
        self.count += 1
        if self.count > self.interval:
            self.count = 0
            self.on_interval()

        self.put_event()

    def put_event(self):
        """"""
        self.algo_engine.put_algo_event(self)

    def write_log(self, msg: str):
        """"""
        self.algo_engine.write_algo_log(self, msg)

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
        # For inverse contract:
        # calculate contract trading volume from coin trading volume
        if self.spread.is_inverse(vt_symbol):
            size = self.spread.get_leg_size(vt_symbol)

            if self.offset == Offset.CLOSE:
                leg = self.spread.legs[vt_symbol]
                volume = volume * leg.net_pos_price / size
            else:
                volume = volume * price / size

        # Round order volume to min_volume of contract
        leg = self.spread.legs[vt_symbol]
        volume = round_to(volume, leg.min_volume)

        # If new order volume is 0, then check if algo finished
        if not volume:
            finished = self.check_algo_finished()

            if finished:
                self.status = Status.ALLTRADED
                self.put_event()

                msg = "各腿剩余数量均不足最小下单量，算法执行结束"
                self.write_log(msg)

            return

        # Round order price to pricetick of contract
        price = round_to(price, leg.pricetick)

        # Otherwise send order
        vt_orderids = self.algo_engine.send_order(
            self,
            vt_symbol,
            price,
            volume,
            direction,
            self.lock
        )

        self.leg_orders[vt_symbol].extend(vt_orderids)

        msg = "发出委托，{}，{}，{}@{}".format(
            vt_symbol,
            direction,
            volume,
            price
        )
        self.write_log(msg)

    def cancel_leg_order(self, vt_symbol: str):
        """"""
        for vt_orderid in self.leg_orders[vt_symbol]:
            self.algo_engine.cancel_order(self, vt_orderid)

    def cancel_all_order(self):
        """"""
        for vt_symbol in self.leg_orders.keys():
            self.cancel_leg_order(vt_symbol)

    def calculate_traded(self):
        """"""
        self.traded = 0

        for n, leg in enumerate(self.spread.legs.values()):
            leg_traded = self.leg_traded[leg.vt_symbol]
            trading_multiplier = self.spread.trading_multipliers[
                leg.vt_symbol]

            adjusted_leg_traded = leg_traded / trading_multiplier
            adjusted_leg_traded = round_to(
                adjusted_leg_traded, self.spread.min_volume)

            if adjusted_leg_traded > 0:
                adjusted_leg_traded = floor_to(
                    adjusted_leg_traded, self.spread.min_volume)
            else:
                adjusted_leg_traded = ceil_to(
                    adjusted_leg_traded, self.spread.min_volume)

            if not n:
                self.traded = adjusted_leg_traded
            else:
                if adjusted_leg_traded > 0:
                    self.traded = min(self.traded, adjusted_leg_traded)
                elif adjusted_leg_traded < 0:
                    self.traded = max(self.traded, adjusted_leg_traded)
                else:
                    self.traded = 0

        self.traded_volume = abs(self.traded)

        if self.target > 0 and self.traded >= self.target:
            self.status = Status.ALLTRADED
        elif self.target < 0 and self.traded <= self.target:
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


class SpreadStrategyTemplate:
    """
    Template for implementing spread trading strategies.
    """

    author: str = ""
    parameters: List[str] = []
    variables: List[str] = []

    def __init__(
        self,
        strategy_engine,
        strategy_name: str,
        spread: SpreadData,
        setting: dict
    ):
        """"""
        self.strategy_engine = strategy_engine
        self.strategy_name = strategy_name
        self.spread = spread
        self.spread_name = spread.name

        self.inited = False
        self.trading = False

        self.variables = copy(self.variables)
        self.variables.insert(0, "inited")
        self.variables.insert(1, "trading")

        self.vt_orderids: Set[str] = set()
        self.algoids: Set[str] = set()

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
            "spread_name": self.spread_name,
            "class_name": self.__class__.__name__,
            "author": self.author,
            "parameters": self.get_parameters(),
            "variables": self.get_variables(),
        }
        return strategy_data

    def update_spread_algo(self, algo: SpreadAlgoTemplate):
        """
        Callback when algo status is updated.
        """
        if not algo.is_active() and algo.algoid in self.algoids:
            self.algoids.remove(algo.algoid)

        self.on_spread_algo(algo)

    def update_order(self, order: OrderData):
        """
        Callback when order status is updated.
        """
        if not order.is_active() and order.vt_orderid in self.vt_orderids:
            self.vt_orderids.remove(order.vt_orderid)

        self.on_order(order)

    @virtual
    def on_init(self):
        """
        Callback when strategy is inited.
        """
        pass

    @virtual
    def on_start(self):
        """
        Callback when strategy is started.
        """
        pass

    @virtual
    def on_stop(self):
        """
        Callback when strategy is stopped.
        """
        pass

    @virtual
    def on_spread_data(self):
        """
        Callback when spread price is updated.
        """
        pass

    @virtual
    def on_spread_tick(self, tick: TickData):
        """
        Callback when new spread tick data is generated.
        """
        pass

    @virtual
    def on_spread_bar(self, bar: BarData):
        """
        Callback when new spread bar data is generated.
        """
        pass

    @virtual
    def on_spread_pos(self):
        """
        Callback when spread position is updated.
        """
        pass

    @virtual
    def on_spread_algo(self, algo: SpreadAlgoTemplate):
        """
        Callback when algo status is updated.
        """
        pass

    @virtual
    def on_order(self, order: OrderData):
        """
        Callback when order status is updated.
        """
        pass

    @virtual
    def on_trade(self, trade: TradeData):
        """
        Callback when new trade data is received.
        """
        pass

    def start_algo(
        self,
        direction: Direction,
        price: float,
        volume: float,
        payup: int,
        interval: int,
        lock: bool,
        offset: Offset
    ) -> str:
        """"""
        if not self.trading:
            return ""

        algoid: str = self.strategy_engine.start_algo(
            self,
            self.spread_name,
            direction,
            offset,
            price,
            volume,
            payup,
            interval,
            lock
        )

        self.algoids.add(algoid)

        return algoid

    def start_long_algo(
        self,
        price: float,
        volume: float,
        payup: int,
        interval: int,
        lock: bool = False,
        offset: Offset = Offset.NONE
    ) -> str:
        """"""
        return self.start_algo(
            Direction.LONG, price, volume,
            payup, interval, lock, offset
        )

    def start_short_algo(
        self,
        price: float,
        volume: float,
        payup: int,
        interval: int,
        lock: bool = False,
        offset: Offset = Offset.NONE
    ) -> str:
        """"""
        return self.start_algo(
            Direction.SHORT, price, volume,
            payup, interval, lock, offset
        )

    def stop_algo(self, algoid: str):
        """"""
        if not self.trading:
            return

        self.strategy_engine.stop_algo(self, algoid)

    def stop_all_algos(self):
        """"""
        for algoid in list(self.algoids):
            self.stop_algo(algoid)

    def buy(self, vt_symbol: str, price: float, volume: float, lock: bool = False) -> List[str]:
        """"""
        return self.send_order(vt_symbol, price, volume, Direction.LONG, Offset.OPEN, lock)

    def sell(self, vt_symbol: str, price: float, volume: float, lock: bool = False) -> List[str]:
        """"""
        return self.send_order(vt_symbol, price, volume, Direction.SHORT, Offset.CLOSE, lock)

    def short(self, vt_symbol: str, price: float, volume: float, lock: bool = False) -> List[str]:
        """"""
        return self.send_order(vt_symbol, price, volume, Direction.SHORT, Offset.OPEN, lock)

    def cover(self, vt_symbol: str, price: float, volume: float, lock: bool = False) -> List[str]:
        """"""
        return self.send_order(vt_symbol, price, volume, Direction.LONG, Offset.CLOSE, lock)

    def send_order(
        self,
        vt_symbol: str,
        price: float,
        volume: float,
        direction: Direction,
        offset: Offset,
        lock: bool
    ) -> List[str]:
        """"""
        if not self.trading:
            return []

        vt_orderids: List[str] = self.strategy_engine.send_order(
            self,
            vt_symbol,
            price,
            volume,
            direction,
            offset,
            lock
        )

        for vt_orderid in vt_orderids:
            self.vt_orderids.add(vt_orderid)

        return vt_orderids

    def cancel_order(self, vt_orderid: str):
        """"""
        if not self.trading:
            return

        self.strategy_engine.cancel_order(self, vt_orderid)

    def cancel_all_orders(self):
        """"""
        for vt_orderid in self.vt_orderids:
            self.cancel_order(vt_orderid)

    def put_event(self):
        """"""
        self.strategy_engine.put_strategy_event(self)

    def write_log(self, msg: str):
        """"""
        self.strategy_engine.write_strategy_log(self, msg)

    def get_spread_tick(self) -> TickData:
        """"""
        return self.spread.to_tick()

    def get_spread_pos(self) -> float:
        """"""
        return self.spread.net_pos

    def get_leg_tick(self, vt_symbol: str) -> TickData:
        """"""
        leg = self.spread.legs.get(vt_symbol, None)

        if not leg:
            return None

        return leg.tick

    def get_leg_pos(self, vt_symbol: str, direction: Direction = Direction.NET) -> float:
        """"""
        leg = self.spread.legs.get(vt_symbol, None)

        if not leg:
            return None

        if direction == Direction.NET:
            return leg.net_pos
        elif direction == Direction.LONG:
            return leg.long_pos
        else:
            return leg.short_pos

    def send_email(self, msg: str):
        """
        Send email to default receiver.
        """
        if self.inited:
            self.strategy_engine.send_email(msg, self)

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
            callback = self.on_spread_bar

        self.strategy_engine.load_bar(self.spread, days, interval, callback)

    def load_tick(self, days: int):
        """
        Load historical tick data for initializing strategy.
        """
        self.strategy_engine.load_tick(self.spread, days, self.on_spread_tick)
