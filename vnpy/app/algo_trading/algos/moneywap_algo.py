from vnpy.trader.constant import Offset, Direction
from vnpy.trader.object import TradeData
from vnpy.trader.engine import BaseEngine

from vnpy.app.algo_trading import AlgoTemplate


class MoneywapAlgo(AlgoTemplate):
    """"""

    display_name = "Money 時間平均"

    default_setting = {
        "vt_symbol": "",
        "direction": [Direction.LONG.value, Direction.SHORT.value],
        "total_amt": 0,
        "price": 0.0,
        "time": 600,
        "offset": [
            Offset.NONE.value,
            Offset.CLOSETODAY.value,
        ]
    }

    variables = [
        "traded",
        "order_volume",
        "timer_count",
        "total_count",
        "total_amt",
        "interval",
        "volume"
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
        self.total_amt = setting["total_amt"]
        self.price = setting["price"]
        self.time = setting["time"]
        self.offset = Offset(setting["offset"])

        # Variables
        tick = self.get_tick(self.vt_symbol)
        if tick and self.direction == Direction.LONG:
            self.price = tick.ask_price_1
        if tick and self.direction == Direction.SHORT:
            self.price = tick.bid_price_1

        self.volume = self.total_amt // self.price  # 總數量
        self.interval = self.time // self.volume
        self.order_volume = 1
        self.timer_count = 0
        self.total_count = 0
        self.traded = 0

        self.subscribe(self.vt_symbol)
        self.put_parameters_event()
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
        self.total_count += 1
        self.put_variables_event()

        if self.total_count >= self.time:
            self.write_log("执行时间已结束，停止算法")
            self.stop()
            return

        if self.timer_count < self.interval:
            return
        self.timer_count = 0

        tick = self.get_tick(self.vt_symbol)
        if not tick:
            return

        self.cancel_all()

        left_volume = self.volume - self.traded
        order_volume = min(self.order_volume, left_volume)

        self.write_log(
            f"價格 {self.price},{tick.bid_price_1},{tick.ask_price_1}")
        if self.direction == Direction.LONG:
            if tick.ask_price_1 <= self.price:
                self.write_log(f"買進 {self.price},{order_volume}")
                self.buy(self.vt_symbol, self.price,
                         order_volume, offset=self.offset)
            else:

                self.price = tick.ask_price_5
        else:
            if tick.bid_price_1 >= self.price:
                self.write_log(f"賣出 {self.price},{order_volume}")
                self.sell(self.vt_symbol, self.price,
                          order_volume, offset=self.offset)
            else:
                self.price = tick.bid_price_5
