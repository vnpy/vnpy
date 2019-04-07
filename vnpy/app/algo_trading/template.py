from vnpy.trader.engine import BaseEngine
from vnpy.trader.object import TickData, OrderData, TradeData
from vnpy.trader.constant import OrderType, Offset

class AlgoTemplate:
    """"""
    count = 0

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
        self.active_orders = {} # vt_orderid:order

    @staticmethod
    def new(cls, algo_engine:BaseEngine, setting: dict):
        """Create new algo instance"""
        cls.count += 1
        algo_name = f"{cls.__name__}_{cls.count}"
        algo = cls(algo_engine, algo_name, setting)

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
    
    def on_stop(self):
        """"""
        pass
    
    def on_tick(self, tick: TickData):
        """"""
        pass

    def on_order(self, order: OrderData):
        """"""
        pass
    
    def on_trade(self, trade: TradeData):
        """"""
        pass
    
    def on_timer(self):
        """"""
        pass    
    
    def start(self):
        """"""
        pass
    
    def stop(self):
        """"""
        pass
    
    def buy(
        self, 
        vt_symbol, 
        price, 
        volume, 
        order_type: OrderType = OrderType.LIMIT,
        offset: Offset = Offset.NONE
    ):
        """"""
        return self.algo_engine.buy(
            vt_symbol,
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
        return self.algo_engine.buy(
            vt_symbol,
            price,
            volume,
            order_type,
            offset
        )    
    
    
    
    
    