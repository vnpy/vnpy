from vnpy.app.cta_strategy import (
    CtaTemplate,
    StopOrder,
    Direction,
    TickData,
    BarData,
    TradeData,
    OrderData,
    BarGenerator,
    ArrayManager,
)
from vnpy.trader.constant import Interval


class TurtleStrategy(CtaTemplate):
    """"""
    author = "用Python的交易员"

    entry_window = 20  # 入场通道窗口数
    exit_window = 10  # 出场通道的窗口数
    atr_window = 20  # ATR的窗口数
    risk_level = 50000  # 一个参数用来计算买入数量

    trading_size = 0  # 买入数量
    entry_up = 0  # 进入唐奇安通道的上轨
    entry_down = 0  # 进入唐奇安通道的下轨
    exit_up = 0  # 退出唐奇安上轨
    exit_down = 0  # 退出唐奇安下轨
    atr_value = 0  # ATR的值

    long_entry = 0  # 多头入场价格
    short_entry = 0  # 空头入场价格
    long_stop = 0  # 多头止损价格
    short_stop = 0  # 空头止损价格

    parameters = ["entry_window", "exit_window", "atr_window", "fixed_size"]
    variables = ["entry_up", "entry_down", "exit_up", "exit_down", "atr_value"]

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super().__init__(cta_engine, strategy_name, vt_symbol, setting)

        self.bg = BarGenerator(self.on_bar, 1, self.on_hour_bar, interval=Interval.HOUR)
        self.am = ArrayManager()

    def on_init(self):
        """
        Callback when strategy is inited.
        """
        self.write_log("策略初始化")
        self.load_bar(20)

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

    def on_hour_bar(self, bar: BarData):
        """"""
        self.cancel_all()  # 撤销所有订单

        self.am.update_bar(bar)
        if not self.am.inited:
            return

        self.entry_up, self.entry_down = self.am.donchian(self.entry_window)  # 计算入场上下轨
        self.exit_up, self.exit_down = self.am.donchian(self.exit_window)  # 计算出场上下轨

        if not self.pos:  # 空仓情况
            self.atr_value = self.am.atr(self.atr_window)

            # self.trading_size = self.risk_level / self.atr_value  # 原始数据
            self.trading_size = 1000
            # print("买入数量：{}".format(self.trading_size))

            self.long_entry = 0
            self.short_entry = 0
            self.long_stop = 0
            self.short_stop = 0

            self.buy(self.entry_up, self.trading_size, True)
            print("时间:{},买入数量：{}".format(bar.datetime, self.trading_size))

            self.short(self.entry_down, self.trading_size, True)
        elif self.pos > 0:
            sell_price = max(self.long_stop, self.exit_down)
            self.sell(sell_price, abs(self.pos), True)

        elif self.pos < 0:
            cover_price = min(self.short_stop, self.exit_up)
            self.cover(cover_price, abs(self.pos), True)

        self.put_event()

    def on_trade(self, trade: TradeData):
        """
        Callback of new trade data update.
        """
        if trade.direction == Direction.LONG:
            self.long_entry = trade.price
            self.long_stop = self.long_entry - 2 * self.atr_value
        else:
            self.short_entry = trade.price
            self.short_stop = self.short_entry + 2 * self.atr_value

    def on_order(self, order: OrderData):
        """
        Callback of new order data update.
        """
        pass

    def on_stop_order(self, stop_order: StopOrder):
        """
        Callback of stop order update.
        """
        pass
