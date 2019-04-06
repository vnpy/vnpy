
from vnpy.event import EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import (EVENT_TICK, EVENT_TIMER, EVENT_ORDER, EVENT_TRADE)


class AlgoEngine(BaseEngine):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """Constructor"""
        super().__init__(main_engine, event_engine)
        
        self.algos = {}
        self.symbol_algo_map = {}
        self.orderid_algo_map = {}
        
        self.register_event()
    
    def register_event(self):
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
    
    def process_tick_event(self):
        """"""
        pass
        
    def process_timer_event(self):
        """"""
        pass        
        
    def process_trade_event(self):
        """"""
        pass        
    
    def process_order_event(self):
        """"""
        pass    
    
    def start_algo(self, setting: dict):
        """"""
        pass
    
    def stop_algo(self, algo_name: dict):
        """"""
        pass
        
    def stop_all(self):
        """"""
        pass
    
    def subscribe(self, algo, vt_symbol):
        """"""
        pass
    
    def send_order(
        self, 
        algo, 
        vt_symbol
    ):
        """"""
        pass
