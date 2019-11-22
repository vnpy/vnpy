from vnpy.app.cta_strategy import (
    CtaTemplate,
    StopOrder,
    TickData,
    BarData,
    TradeData,
    OrderData,
    BarGenerator,
    ArrayManager,
    Direction,
)


class BollStrategyMultiplier(CtaTemplate):
    """移动止损策略"""

    author = "Guo"

    boll_window = 18  # 布林窗口数
    boll_dev = 3.4  # 布林标准差
    fixed_size = 1  # 下单手数
    atr_window = 20  # atr周期
    atr_multiplier = 2  # atr乘数

    boll_up = 0
    boll_down = 0
    boll_mid = 0

    atr_value = 0
    intra_trade_high = 0  # 交易周期内的最高价
    long_stop_lose = 0  # 多头止损价格
    intra_trade_low = 0  # 交易周期内的最低价
    short_stop_lose = 0  # 空头止损价格

    long_entry = 0  # 多头入场价格
    long_take_profit = 0  # 多头止盈价格
    short_entry = 0  # 空头入场价格
    short_take_profit = 0  # 空头止盈价格
    fixed_tack_profit = 500  # 止盈参数

    parameters = [
        "boll_window",
        "boll_dev",
        "fixed_size",
        "atr_window",
        "atr_multiplier",
        "fixed_tack_profit",
    ]
    variables = [
        "boll_up",
        "boll_down",
        "boll_mid",
        "atr_value",
        "intra_trade_high",
        "long_stop_lose",
        "intra_trade_low",
        "short_stop_lose",
        "long_entry",
        "long_take_profit",
        "short_entry",
        "short_take_profit",
        "fixed_tack_profit",
    ]

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super().__init__(cta_engine, strategy_name, vt_symbol, setting)

        self.bg = BarGenerator(self.on_bar, 15, self.on_15min_bar)
        self.am = ArrayManager()

    def on_init(self):
        """
        Callback when strategy is inited.
        """
        self.write_log("策略初始化")
        self.load_bar(10)

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

    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        self.bg.update_tick(tick)

    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        self.bg.update_bar(bar)

    def on_15min_bar(self, bar: BarData):
        """"""
        self.cancel_all()

        am = self.am
        am.update_bar(bar)
        if not am.inited:
            return

        self.boll_up, self.boll_down = am.boll(self.boll_window, self.boll_dev)
        self.boll_mid = am.sma(self.boll_window)
        self.atr_value = am.atr(self.atr_window)

        if self.pos == 0:
            self.buy(self.boll_up, self.fixed_size, True)
            self.short(self.boll_down, self.fixed_size, True)

            self.intra_trade_high = bar.high_price
            self.intra_trade_low = bar.low_price

            # 如果没有持仓重新初始化参数
            self.long_entry = 0
            self.long_take_profit = 0
            self.short_entry = 0
            self.short_take_profit = 0

        elif self.pos > 0:
            # if bar.close_price <= self.boll_mid:  # 收盘价小于中轨
            #     self.sell(bar.close_price - 5, abs(self.pos))
            # self.sell(self.boll_mid, abs(self.pos), True)  # 布林中轨的停止单

            self.intra_trade_high = max(
                self.intra_trade_high, bar.high_price
            )  # 更新交易内最高价
            self.intra_trade_low = bar.low_price

            self.long_stop_lose = (
                    self.intra_trade_high - self.atr_value * self.atr_multiplier
            )  # atr通道*2

            self.long_stop_lose = max(
                self.boll_mid, self.long_stop_lose
            )  # 两者最大值，防止两次开仓,线跌破的那个最大为出场价格
            self.sell(self.long_stop_lose, abs(self.pos), True)
            if self.long_take_profit:  # 如果该字典存在,这里不能用停止单
                self.sell(self.long_take_profit, abs(self.pos))

        elif self.pos < 0:
            # if bar.close_price >= self.boll_mid:
            #     self.cover(bar.close_price + 5, abs(self.pos))
            # self.cover(self.boll_mid, abs(self.pos), True)

            self.intra_trade_low = min(self.intra_trade_low, bar.low_price)
            self.intra_trade_high = bar.high_price

            self.short_stop_lose = (
                    self.intra_trade_low + self.atr_value * self.atr_multiplier
            )

            self.short_stop_lose = min(self.boll_mid, self.short_stop_lose)
            self.cover(self.short_stop_lose, abs(self.pos), True)
            if self.short_take_profit:
                self.sell(self.short_take_profit, abs(self.pos))
        self.put_event()

    def on_order(self, order: OrderData):
        """
        Callback of new order data update.
        """
        pass

    def on_trade(self, trade: TradeData):
        """
        获取真实成交价
        """

        if self.pos != 0:  # 如果没有持仓
            if trade.direction == Direction.LONG:  # 如果为多头持仓
                self.long_entry = trade.price  # 多头入场=成交价格
                self.long_take_profit = (
                        self.long_entry + self.fixed_tack_profit
                )  # 多头止盈价格
            else:
                self.short_entry = trade.price
                self.short_take_profit = self.short_entry - self.fixed_tack_profit

        self.put_event()


def on_stop_order(self, stop_order: StopOrder):
    """
    Callback of stop order update.
    """
    pass
