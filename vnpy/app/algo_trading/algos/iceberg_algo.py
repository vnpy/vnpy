from vnpy.trader.constant import Offset, Direction
from vnpy.trader.object import TradeData, OrderData, TickData
from vnpy.trader.engine import BaseEngine

from vnpy.app.algo_trading import AlgoTemplate


class IcebergAlgo(AlgoTemplate):
    """"""

    display_name = "Iceberg 冰山"

    default_setting = {
        "vt_symbol": "",
        "direction": [Direction.LONG.value, Direction.SHORT.value],
        "price": 0.0,
        "volume": 0.0,
        "display_volume": 0.0,
        "interval": 0,
        "offset": [
            Offset.NONE.value,
            Offset.OPEN.value,
            Offset.CLOSE.value,
            Offset.CLOSETODAY.value,
            Offset.CLOSEYESTERDAY.value
        ]
    }

    variables = [
        "traded",
        "timer_count",
        "vt_orderid"
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
        self.vt_symbol = setting["vt_symbol"]
        self.direction = Direction(setting["direction"])
        self.price = setting["price"]
        self.volume = setting["volume"]
        self.display_volume = setting["display_volume"]
        self.interval = setting["interval"]
        self.offset = Offset(setting["offset"])

        # Variables
        self.timer_count = 0
        self.vt_orderid = ""
        self.traded = 0

        self.last_tick = None

        self.subscribe(self.vt_symbol)
        self.put_parameters_event()
        self.put_variables_event()

    def on_stop(self):
        """"""
        self.write_log("停止算法")

    def on_tick(self, tick: TickData):
        """"""
        self.last_tick = tick

    def on_order(self, order: OrderData):
        """"""
        msg = f"委托号：{order.vt_orderid}，委托状态：{order.status.value}"
        self.write_log(msg)

        if not order.is_active():
            self.vt_orderid = ""
            self.put_variables_event()

    def on_trade(self, trade: TradeData):
        """"""
        self.traded += trade.volume

        if self.traded >= self.volume:
            self.write_log(f"已交易数量：{self.traded}，总数量：{self.volume}")
            self.stop()
        else:
            self.put_variables_event()

    def on_timer(self):
        """"""
        self.timer_count += 1

        if self.timer_count < self.interval:
            self.put_variables_event()
            return

        self.timer_count = 0

        contract = self.get_contract(self.vt_symbol)
        if not contract:
            return

        # If order already finished, just send new order
        if not self.vt_orderid:
            order_volume = self.volume - self.traded
            order_volume = min(order_volume, self.display_volume)

            if self.direction == Direction.LONG:
                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )
            else:
                self.vt_orderid = self.sell(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )
        # Otherwise check for cancel
        else:
            if self.direction == Direction.LONG:
                if self.last_tick.ask_price_1 <= self.price:
                    self.cancel_order(self.vt_orderid)
                    self.vt_orderid = ""
                    self.write_log(u"最新Tick卖一价，低于买入委托价格，之前委托可能丢失，强制撤单")
            else:
                if self.last_tick.bid_price_1 >= self.price:
                    self.cancel_order(self.vt_orderid)
                    self.vt_orderid = ""
                    self.write_log(u"最新Tick买一价，高于卖出委托价格，之前委托可能丢失，强制撤单")

        self.put_variables_event()
