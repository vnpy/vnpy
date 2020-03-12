from vnpy.trader.engine import BaseEngine
from vnpy.trader.object import TickData, OrderData, TradeData
from vnpy.trader.constant import OrderType, Offset, Direction
from vnpy.trader.utility import virtual


class AlgoTemplate:
    """"""

    _count = 0
    display_name = ""
    default_setting = {}
    variables = []

    def __init__(
        self,
        algo_engine: BaseEngine,
        algo_name: str,
        setting: dict
    ):
        """Constructor"""
        self.algo_engine = algo_engine
        self.algo_name = algo_name

        self.active = False
        self.active_orders = {}  # vt_orderid:order

        self.variables.insert(0, "active")

    @classmethod
    def new(cls, algo_engine: BaseEngine, setting: dict):
        """Create new algo instance"""
        cls._count += 1
        algo_name = f"{cls.__name__}_{cls._count}"
        algo = cls(algo_engine, algo_name, setting)
        return algo

    def update_tick(self, tick: TickData):
        """"""
        if self.active:
            self.on_tick(tick)

    def update_order(self, order: OrderData):
        """"""
        if self.active:
            if order.is_active():
                self.active_orders[order.vt_orderid] = order
            elif order.vt_orderid in self.active_orders:
                self.active_orders.pop(order.vt_orderid)

            self.on_order(order)

    def update_trade(self, trade: TradeData):
        """"""
        if self.active:
            self.on_trade(trade)

    def update_timer(self):
        """"""
        if self.active:
            self.on_timer()

    def on_start(self):
        """"""
        pass

    @virtual
    def on_stop(self):
        """"""
        pass

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

    def start(self):
        """"""
        self.active = True
        self.on_start()
        self.put_variables_event()

    def stop(self):
        """"""
        self.active = False
        self.cancel_all()
        self.on_stop()
        self.put_variables_event()

        self.write_log("停止算法")

    def subscribe(self, vt_symbol):
        """"""
        self.algo_engine.subscribe(self, vt_symbol)

    def buy(
        self,
        vt_symbol,
        price,
        volume,
        order_type: OrderType = OrderType.LIMIT,
        offset: Offset = Offset.NONE
    ):
        """"""
        msg = f"委托买入{vt_symbol}：{volume}@{price}"
        self.write_log(msg)

        return self.algo_engine.send_order(
            self,
            vt_symbol,
            Direction.LONG,
            price,
            volume,
            order_type,
            offset
        )

    def sell(
        self,
        vt_symbol,
        price,
        volume,
        order_type: OrderType = OrderType.LIMIT,
        offset: Offset = Offset.NONE
    ):
        """"""
        msg = f"委托卖出{vt_symbol}：{volume}@{price}"
        self.write_log(msg)

        return self.algo_engine.send_order(
            self,
            vt_symbol,
            Direction.SHORT,
            price,
            volume,
            order_type,
            offset
        )

    def cancel_order(self, vt_orderid: str):
        """"""
        self.algo_engine.cancel_order(self, vt_orderid)

    def cancel_all(self):
        """"""
        if not self.active_orders:
            return

        for vt_orderid in self.active_orders.keys():
            self.cancel_order(vt_orderid)

    def get_tick(self, vt_symbol: str):
        """"""
        return self.algo_engine.get_tick(self, vt_symbol)

    def get_contract(self, vt_symbol: str):
        """"""
        return self.algo_engine.get_contract(self, vt_symbol)

    def write_log(self, msg: str):
        """"""
        self.algo_engine.write_log(msg, self)

    def put_parameters_event(self):
        """"""
        parameters = {}
        for name in self.default_setting.keys():
            parameters[name] = getattr(self, name)

        self.algo_engine.put_parameters_event(self, parameters)

    def put_variables_event(self):
        """"""
        variables = {}
        for name in self.variables:
            variables[name] = getattr(self, name)

        self.algo_engine.put_variables_event(self, variables)
