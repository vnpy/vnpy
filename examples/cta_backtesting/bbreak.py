from datetime import time
from vnpy.app.cta_strategy import (
    CtaTemplate,
    StopOrder,
    TickData,
    BarData,
    TradeData,
    OrderData,
    BarGenerator,
    ArrayManager
)


class RBreakStrategy(CtaTemplate):
    """"""
    author = "KeKe"
    setup_coef = 0.25
    break_coef = 0.2
    enter_coef_1 = 1.07
    enter_coef_2 = 0.07
    fixed_size = 1
    donchian_window = 30

    trailing_long = 0.4
    trailing_short = 0.4
    multiplier = 3

    buy_break = 0  # 突破买入价
    sell_setup = 0  # 观察卖出价
    sell_enter = 0  # 反转卖出价
    buy_enter = 0  # 反转买入价
    buy_setup = 0  # 观察买入价
    sell_break = 0  # 突破卖出价

    intra_trade_high = 0
    intra_trade_low = 0

    day_high = 0
    day_open = 0
    day_close = 0
    day_low = 0
    tend_high = 0
    tend_low = 0

    exit_time = time(hour=23, minute=55)

    parameters = ["setup_coef", "break_coef", "enter_coef_1", "enter_coef_2", "fixed_size", "donchian_window"]
    variables = ["buy_break", "sell_setup", "sell_enter", "buy_enter", "buy_setup", "sell_break"]

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super(RBreakStrategy, self).__init__(
            cta_engine, strategy_name, vt_symbol, setting
        )

        self.bg = BarGenerator(self.on_bar)
        self.am = ArrayManager()
        self.bars = []

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
        self.cancel_all()

        am = self.am
        am.update_bar(bar)
        if not am.inited:
            return

        self.bars.append(bar)
        if len(self.bars) <= 2:
            return
        else:
            self.bars.pop(0)
        last_bar = self.bars[-2]


        # New Day
        if last_bar.datetime.date() != bar.datetime.date():
            print("last_bar.datetime.date是:{}".format(last_bar.datetime.date()))
            print("bar.datetime.date是:{}".format(bar.datetime.date()))
            print("二者不相等，继续后面的动作")
            if self.day_open:
                self.buy_setup = self.day_low - self.setup_coef * (self.day_high - self.day_close)  # 观察买入价
                self.sell_setup = self.day_high + self.setup_coef * (self.day_close - self.day_low)  # 观察卖出价

                self.buy_enter = (self.enter_coef_1 / 2) * (
                        self.day_high + self.day_low) - self.enter_coef_2 * self.day_high  # 反转买入价

                self.sell_enter = (self.enter_coef_1 / 2) * (
                        self.day_high + self.day_low) - self.enter_coef_2 * self.day_low  # 反转卖出价


                self.buy_break = self.buy_setup + self.break_coef * (self.sell_setup - self.buy_setup)  # 突破买入价

                self.sell_break = self.sell_setup - self.break_coef * (self.sell_setup - self.buy_setup)  # 突破卖出价

            self.day_open = bar.open_price
            self.day_high = bar.high_price
            self.day_close = bar.close_price
            self.day_low = bar.low_price

        # Today
        else:
            self.day_high = max(self.day_high, bar.high_price)
            self.day_low = min(self.day_low, bar.low_price)
            self.day_close = bar.close_price

        if not self.sell_setup:
            return

        self.tend_high, self.tend_low = am.donchian(self.donchian_window)

        if bar.datetime.time() < self.exit_time:

            if self.pos == 0:
                self.intra_trade_low = bar.low_price
                self.intra_trade_high = bar.high_price

                if self.tend_high > self.sell_setup:
                    long_entry = max(self.buy_break, self.day_high)
                    self.buy(long_entry, self.fixed_size, stop=True)

                    self.short(self.sell_enter, self.multiplier * self.fixed_size, stop=True)

                elif self.tend_low < self.buy_setup:
                    short_entry = min(self.sell_break, self.day_low)
                    self.short(short_entry, self.fixed_size, stop=True)

                    self.buy(self.buy_enter, self.multiplier * self.fixed_size, stop=True)

            elif self.pos > 0:
                self.intra_trade_high = max(self.intra_trade_high, bar.high_price)
                long_stop = self.intra_trade_high * (1 - self.trailing_long / 100)
                self.sell(long_stop, abs(self.pos), stop=True)

            elif self.pos < 0:
                self.intra_trade_low = min(self.intra_trade_low, bar.low_price)
                short_stop = self.intra_trade_low * (1 + self.trailing_short / 100)
                self.cover(short_stop, abs(self.pos), stop=True)

        # Close existing position
        else:
            if self.pos > 0:
                self.sell(bar.close_price * 0.99, abs(self.pos))
            elif self.pos < 0:
                self.cover(bar.close_price * 1.01, abs(self.pos))

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
