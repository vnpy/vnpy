from vnpy.trader.constant import Direction
from vnpy.trader.object import TradeData, OrderData
from vnpy.trader.engine import BaseEngine

from vnpy.app.algo_trading import AlgoTemplate


class ArbitrageAlgo(AlgoTemplate):
    """"""

    display_name = "Arbitrage 套利"

    default_setting = {
        "active_vt_symbol": "",
        "passive_vt_symbol": "",        
        "spread_up": 0.0,
        "spread_down": 0.0,
        "max_pos": 0,
        "interval": 0,
    }

    variables = [
        "timer_count",
        "active_vt_orderid",
        "passive_vt_orderid",
        "net_pos",
        "acum_pos"
    ]

    def __init__(
        self,
        algo_engine: BaseEngine,
        algo_name: str,
        setting: dict
    ):
        """"""
        super().__init__(algo_engine, algo_name, setting)

        # Parameters
        self.active_vt_symbol = setting["active_vt_symbol"]
        self.passive_vt_symbol = setting["passive_vt_symbol"]
        self.spread_up = setting["spread_up"]
        self.spread_down = setting["spread_down"]
        self.max_pos = setting["max_pos"]
        self.interval = setting["interval"]
       
        # Variables
        self.active_vt_orderid = ""
        self.passive_vt_orderid = ""
        self.net_pos = 0
        self.acum_pos = 0
        self.timer_count = 0

        self.subscribe(self.active_vt_symbol)
        self.subscribe(self.passive_vt_symbol)
        self.put_parameters_event()
        self.put_variables_event()

    def on_stop(self):
        """"""
        self.write_log("停止算法")

    def on_order(self, order: OrderData):
        """"""
        if order.vt_symbol == self.active_vt_symbol:
            if not order.is_active():
                self.active_vt_orderid = ""
        elif order.vt_symbol == self.passive_vt_symbol:
            if not order.is_active():
                self.passive_vt_orderid = ""
        self.put_variables_event()

    def on_trade(self, trade: TradeData):
        """"""
        # Update net position volume
        if trade.direction == Direction.LONG:
            self.net_pos += trade.volume
        else:
            self.net_pos -= trade.volume

        # Update active symbol position           
        if trade.vt_symbol == self.active_vt_symbol:
            if trade.direction == Direction.LONG:
                self.acum_pos += trade.volume
            else:
                self.acum_pos -= trade.volume

        # Hedge if active symbol traded     
        if trade.vt_symbol == self.active_vt_symbol:
            self.hedge()
        
        self.put_variables_event()

    def on_timer(self):
        """"""
        self.timer_count += 1
        if self.timer_count < self.interval:
            self.put_variables_event()
            return
        self.timer_count = 0

        if self.active_vt_orderid or self.passive_vt_orderid:
            self.cancel_all()
            return
        
        if self.net_pos:
            self.hedge()
            return
      
        active_tick = self.get_tick(self.active_vt_symbol)
        passive_tick = self.get_tick(self.passive_vt_symbol)
        if not active_tick or not passive_tick:
            return

        # Calculate spread
        spread_bid_price = active_tick.bid_price_1 - passive_tick.ask_price_1
        spread_ask_price = active_tick.ask_price_1 - passive_tick.bid_price_1

        spread_bid_volume = min(active_tick.bid_volume_1, passive_tick.ask_volume_1)
        spread_ask_volume = min(active_tick.ask_volume_1, passive_tick.bid_volume_1)

        # Sell condition      
        if spread_bid_price > self.spread_up:
            if self.acum_pos <= -self.max_pos:
                return
            else:
                self.active_vt_orderid = self.sell(
                    self.active_vt_symbol,
                    active_tick.bid_price_1,
                    spread_bid_volume               
                )

        # Buy condition
        elif spread_ask_price < -self.spread_down:
            if self.acum_pos >= self.max_pos:
                return
            else:
                self.active_vt_orderid = self.buy(
                    self.active_vt_symbol,
                    active_tick.ask_price_1,
                    spread_ask_volume
                )
        self.put_variables_event()
    
    def hedge(self):
        """"""
        tick = self.get_tick(self.passive_vt_symbol)
        volume = abs(self.net_pos)

        if self.net_pos > 0:
            self.passive_vt_orderid = self.sell(
                self.passive_vt_symbol,
                tick.bid_price_5,
                volume
            )
        elif self.net_pos < 0:
            self.passive_vt_orderid = self.buy(
                self.passive_vt_symbol,
                tick.ask_price_5,
                volume
            )
