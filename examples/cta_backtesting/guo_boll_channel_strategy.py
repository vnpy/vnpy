from vnpy.app.cta_strategy import (
    CtaTemplate,
    StopOrder,
    TickData,
    BarData,
    TradeData,
    OrderData,
    BarGenerator,
    ArrayManager,
)
from vnpy.trader.constant import Interval


class GuoBollChannelStrategy(CtaTemplate):
    """"""

    author = "Guo"

    boll_window = 600  # 布林周期数
    boll_dev = 3.5  # 标准差
    cci_window = 10  # cci的N
    atr_window = 30  # atr的N
    sl_multiplier = 5.2
    fixed_size = 4  # 下单手数

    boll_up = 0  # 布林上轨
    boll_down = 0  # 布林下轨
    cci_value = 0  # cci的值
    atr_value = 0  # atr的值

    intra_trade_high = 0  # 交易最高价
    intra_trade_low = 0  # 交易最低价
    long_stop = 0  # 多头停止单
    short_stop = 0  # 空头停止单

    parameters = ["boll_window", "boll_dev", "fixed_size"]
    variables = ["boll_up", "boll_down", "long_stop", "short_stop"]

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super(GuoBollChannelStrategy, self).__init__(
            cta_engine, strategy_name, vt_symbol, setting
        )

        self.bg = BarGenerator(self.on_bar, 30, self.on_15min_bar)
        self.am = ArrayManager(size=1000)

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

    # def on_15min_bar(self, bar: BarData):
    #     """"""
    #     self.cancel_all()
    #
    #     am = self.am
    #     am.update_bar(bar)
    #     if not am.inited:
    #         return
    #
    #     self.boll_up, self.boll_down = am.boll(self.boll_window, self.boll_dev)
    #     self.cci_value = am.cci(self.cci_window)
    #     self.atr_value = am.atr(self.atr_window)
    #
    #     if self.pos == 0:
    #         self.intra_trade_high = bar.high_price
    #         self.intra_trade_low = bar.low_price
    #
    #         if self.cci_value > 0:
    #             self.buy(self.boll_up, self.fixed_size, True)
    #         elif self.cci_value < 0:
    #             self.short(self.boll_down, self.fixed_size, True)
    #
    #     elif self.pos > 0:
    #         self.intra_trade_high = max(self.intra_trade_high, bar.high_price)
    #         self.intra_trade_low = bar.low_price
    #
    #         self.long_stop = self.intra_trade_high - self.atr_value * self.sl_multiplier
    #         self.sell(self.long_stop, abs(self.pos), True)
    #
    #     elif self.pos < 0:
    #         self.intra_trade_high = bar.high_price
    #         self.intra_trade_low = min(self.intra_trade_low, bar.low_price)
    #
    #         self.short_stop = self.intra_trade_low + self.atr_value * self.sl_multiplier
    #         self.cover(self.short_stop, abs(self.pos), True)
    #
    #     self.put_event()
    def on_15min_bar(self, bar: BarData):
        """"""

        # 撤销全部订单
        self.cancel_all()

        # 更新K线
        am = self.am
        am.update_bar(bar)
        if not am.inited:
            return

        # 计算各类指标
        ## 布林上下轨
        self.boll_up, self.boll_down = am.boll(self.boll_window, self.boll_dev, array=True)
        ## 布林中轨
        self.boll_mid = am.sma(self.boll_window, array=True)

        # self.cci_value = am.cci(self.cci_window)
        # self.atr_value = am.atr(self.atr_window)

        # 定义上穿,开多
        cross_over = am.close_array[-2] < self.boll_up[-2] and bar.close_price > self.boll_up[-1]
        # 下穿中轨，平多仓
        cross_over_cover = am.close[-2] > self.boll_mid[-2] and bar.close_price < self.boll_mid[-1]

        # 定义下穿，开空
        cross_below = am.close_array[-2] > self.boll_down[-2] and bar.close_price < self.boll_mid[-1]
        # 上穿中轨，平空仓
        cross_below_cover = am.close[-2] < self.boll_mid[-2] and bar.close_price > self.boll_mid[-1]

        # 下单逻辑
        if self.pos == 0:  # 没有持仓
            if cross_over:  # 上传上轨
                self.buy(bar.close_price * 1.02, self.fixed_size)
            elif cross_below:  # 下穿下轨
                self.short(bar.close_price * 0.98, self.fixed_size)
        elif self.pos < 0:  # 持有空头
            if cross_over:  # 上传上轨
                self.sell(bar.close_price, self.fixed_size)  # 先平空仓
                self.buy(bar.close_price * 1.02, self.fixed_size)  # 开多仓
            elif cross_below_cover:  # 空头平仓信号
                self.sell(bar.close_price, self.fixed_size)
        elif self.pos > 0:  # 持有多头
            if cross_below:
                self.cover(bar.close_price, self.fixed_size)  # 先平多
                self.short(bar.close_price * 1.02, self.fixed_size * 1.02)  # 买入
        self.put_event()

    def on_order(self, order: OrderData):
        """
        Callback of new order data update.
        """
        pass

    def on_trade(self, trade: TradeData):
        """
        Callback of new trade data update.
        """
        self.put_event()

    def on_stop_order(self, stop_order: StopOrder):
        """
        Callback of stop order update.
        """
        pass
