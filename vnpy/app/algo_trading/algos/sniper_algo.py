from vnpy.trader.constant import Offset, Direction
from vnpy.trader.object import TradeData, OrderData, TickData
from vnpy.trader.engine import BaseEngine

from vnpy.app.algo_trading import AlgoTemplate


class SniperAlgo(AlgoTemplate):
    """"""

    display_name = "Sniper 狙击手"

    default_setting = {
        "vt_symbol": "",
        "direction": [Direction.LONG.value, Direction.SHORT.value],
        "price": 0.0,
        "volume": 0.0,
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
        self.offset = Offset(setting["offset"])

        # Variables
        self.vt_orderid = ""
        self.traded = 0

        self.subscribe(self.vt_symbol)
        self.put_parameters_event()
        self.put_variables_event()

    def on_tick(self, tick: TickData):
        """"""
        if self.vt_orderid:
            self.cancel_all()
            return

        if self.direction == Direction.LONG:
            if tick.ask_price_1 <= self.price:
                order_volume = self.volume - self.traded
                order_volume = min(order_volume, tick.ask_volume_1)

                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )
        else:
            if tick.bid_price_1 >= self.price:
                order_volume = self.volume - self.traded
                order_volume = min(order_volume, tick.bid_volume_1)

                self.vt_orderid = self.sell(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )

        self.put_variables_event()

    def on_order(self, order: OrderData):
        """"""
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
