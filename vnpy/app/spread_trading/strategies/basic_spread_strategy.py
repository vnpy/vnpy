from vnpy.app.spread_trading import (
    SpreadStrategyTemplate,
    SpreadAlgoTemplate,
    SpreadData,
    OrderData,
    TradeData
)


class BasicSpreadStrategy(SpreadStrategyTemplate):
    """"""

    author = "用Python的交易员"

    buy_price = 0.0
    sell_price = 0.0
    cover_price = 0.0
    short_price = 0.0
    max_pos = 0.0
    payup = 10
    interval = 5

    spread_pos = 0.0
    buy_algoid = ""
    sell_algoid = ""
    short_algoid = ""
    cover_algoid = ""

    parameters = [
        "buy_price",
        "sell_price",
        "cover_price",
        "short_price",
        "max_pos",
        "payup",
        "interval"
    ]
    variables = [
        "spread_pos",
        "buy_algoid",
        "sell_algoid",
        "short_algoid",
        "cover_algoid",
    ]

    def __init__(
        self,
        strategy_engine,
        strategy_name: str,
        spread: SpreadData,
        setting: dict
    ):
        """"""
        super().__init__(
            strategy_engine, strategy_name, spread, setting
        )

    def on_init(self):
        """
        Callback when strategy is inited.
        """
        self.write_log("策略初始化")

    def on_start(self):
        """
        Callback when strategy is started.
        """
        self.write_log("策略启动")

    def on_stop(self):
        """
        Callback when strategy is stopped.
        """
        self.write_log("策略停止")

        self.buy_algoid = ""
        self.sell_algoid = ""
        self.short_algoid = ""
        self.cover_algoid = ""
        self.put_event()

    def on_spread_data(self):
        """
        Callback when spread price is updated.
        """
        self.spread_pos = self.get_spread_pos()

        # No position
        if not self.spread_pos:
            self.stop_close_algos()

            # Start open algos
            if not self.buy_algoid:
                self.buy_algoid = self.start_long_algo(
                    self.buy_price, self.max_pos, self.payup, self.interval
                )

            if not self.short_algoid:
                self.short_algoid = self.start_short_algo(
                    self.short_price, self.max_pos, self.payup, self.interval
                )

        # Long position
        elif self.spread_pos > 0:
            self.stop_open_algos()

            # Start sell close algo
            if not self.sell_algoid:
                self.sell_algoid = self.start_short_algo(
                    self.sell_price, self.spread_pos, self.payup, self.interval
                )

        # Short position
        elif self.spread_pos < 0:
            self.stop_open_algos()

            # Start cover close algo
            if not self.cover_algoid:
                self.cover_algoid = self.start_long_algo(
                    self.cover_price, abs(
                        self.spread_pos), self.payup, self.interval
                )

        self.put_event()

    def on_spread_pos(self):
        """
        Callback when spread position is updated.
        """
        self.spread_pos = self.get_spread_pos()
        self.put_event()

    def on_spread_algo(self, algo: SpreadAlgoTemplate):
        """
        Callback when algo status is updated.
        """
        if not algo.is_active():
            if self.buy_algoid == algo.algoid:
                self.buy_algoid = ""
            elif self.sell_algoid == algo.algoid:
                self.sell_algoid = ""
            elif self.short_algoid == algo.algoid:
                self.short_algoid = ""
            else:
                self.cover_algoid = ""

        self.put_event()

    def on_order(self, order: OrderData):
        """
        Callback when order status is updated.
        """
        pass

    def on_trade(self, trade: TradeData):
        """
        Callback when new trade data is received.
        """
        pass

    def stop_open_algos(self):
        """"""
        if self.buy_algoid:
            self.stop_algo(self.buy_algoid)

        if self.short_algoid:
            self.stop_algo(self.short_algoid)

    def stop_close_algos(self):
        """"""
        if self.sell_algoid:
            self.stop_algo(self.sell_algoid)

        if self.cover_algoid:
            self.stop_algo(self.cover_algoid)
