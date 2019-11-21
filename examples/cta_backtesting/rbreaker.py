from datetime import time
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


class RBraekStrategy(CtaTemplate):
    """"""

    author = "Guo"

    setup_coef = 0.25  # 观察买入价参数 a
    break_coef = 0.2  # 突破卖出价参数 d
    enter_coef_1 = 1.07  # 入场参数1
    enter_coef_2 = 0.07  # 入场参数2
    fixed_size = 10  # 买入手数
    donchian_window = 30  # 唐奇安通道参数

    trailing_long = 0.4  # 多头止损比例
    trailing_short = 0.4  # 空头止损比例
    multiplier = 3  # 反转卖出的价格乘数

    buy_break = 0  # 突破买入价
    sell_setup = 0  # 观察卖出价
    sell_enter = 0  # 反转卖出价
    buy_enter = 0  # 反转买入价
    buy_setup = 0  # 观察买入价
    sell_break = 0  # 突破卖出价

    intra_trade_high = 0  # 交易时的最高价
    intra_trade_low = 0  # 交易时的最低价

    day_high = 0
    day_open = 0
    day_close = 0
    day_low = 0
    tend_high = 0
    tend_low = 0

    exit_time = time(hour=23, minute=55)  # 清仓时间

    parameters = ['setup_coef',
                  'break_coef',
                  'enter_coef_1',
                  'enter_coef_2',
                  'fixed_size',
                  'donchian_window',
                  ]

    variables = ['buy_break',
                 'sell_setup',
                 'sell_enter',
                 'buy_enter',
                 'buy_setup',
                 'sell_break'
                 ]

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super(RBraekStrategy, self).__init__(cta_engine, strategy_name, vt_symbol, setting)
        self.bg = BarGenerator(self.on_bar)
        self.am = ArrayManager()
        self.bars = []

    def on_init(self):
        """初始化"""
        self.write_log('策略初始化')
        self.load_bar(10)

    def on_start(self):
        """启动策略"""
        self.write_log('策略启动')

    def on_stop(self):
        """策略停止"""
        self.write_log('策略停止')

    def on_tick(self, tick: TickData):
        """更新tick数据"""
        self.bg.update_tick(tick)

    def on_bar(self, bar: BarData):
        """更新K线数据"""
        self.cancel_all()  # 取消所有订单

        am = self.am
        am.update_bar(bar)  # 更新K线
        if not am.inited:
            return

        self.bars.append(bar)
        if len(self.bars) <= 2:  # 检查K线的数量
            return
        else:
            self.bars.pop(0)
            # print("当前的self.bar.pop是：{}".format(self.bars.pop(0)))
        last_bar = self.bars[-2]
        # print("当前的last_bar是：{}".format(last_bar))
        # print(last_bar.datetime.date())
        # print(bar.datetime.date())
        # exit()

        # 新交易日
        if last_bar.datetime.date() != bar.datetime.date():
            # print("last_bar.datetime.date是:{}".format(last_bar.datetime.date()))
            # print("bar.datetime.date是:{}".format(bar.datetime.date()))
            # print("二者不相等，继续后面的动作")
            if self.day_open:
                # print("day_open是{}".format(self.day_open))
                # 开始计算指标

                # 观察买入价
                self.buy_setup = self.day_low - self.setup_coef * (self.day_high - self.day_close)

                #  观察卖出价
                self.sell_setup = self.day_high + self.setup_coef * (self.day_close - self.day_low)

                #  反转买入价
                self.buy_enter = (self.enter_coef_1 / 2) * (
                        self.day_high + self.day_low) - self.enter_coef_2 * self.day_high

                # 反转卖出价
                self.sell_enter = (self.enter_coef_1 / 2) * (
                        self.day_high + self.day_low) - self.enter_coef_2 * self.day_low

                # 突破买入价
                self.buy_break = self.buy_setup + self.break_coef * (self.sell_setup - self.buy_setup)

                # 突破卖出价
                self.sell_break = self.sell_setup - self.break_coef * (self.sell_setup - self.buy_setup)

            #  为变量赋值,注意不能放在if self.day_open前面
            self.day_open = bar.open_price  # 开盘价
            self.day_high = bar.high_price  # 最高价
            self.day_low = bar.low_price  # 最低价
            self.day_close = bar.close_price  # 收盘价

        # 今日
        else:
            self.day_high = max(self.day_high, bar.high_price)
            self.day_low = min(self.day_low, bar.low_price)
            self.day_close = bar.close_price

        if not self.sell_setup:
            return

        self.tend_high, self.tend_low = am.donchian(self.donchian_window)
        # print("tend_high：{},tend_low：{}".format(self.tend_high, self.tend_low))

        # 日内策略，在某一时间退出
        if bar.datetime.time() < self.exit_time:  # 在交易时间内
            if self.pos == 0:
                self.intra_trade_high = bar.high_price
                self.intra_trade_low = bar.low_price

                # 买入条件
                if self.tend_high > self.sell_setup:  # x分钟最高价大于观察卖出价
                    long_entry = max(self.buy_break, self.day_high)
                    self.buy(long_entry, self.fixed_size, stop=True)  # 趋势行情，取突破买入价和最高价的最大值，作为停止单买入条件
                    self.short(self.sell_enter, self.multiplier * self.fixed_size, stop=True)  # 反转行情

                # 做空条件
                elif self.tend_low < self.buy_setup:  # x分钟的最低价小于观察买入价
                    shorr_entry = min(self.sell_break, self.day_low)
                    self.short(shorr_entry, self.fixed_size, stop=True)
                    self.buy(self.buy_enter, self.multiplier * self.fixed_size, stop=True)

            elif self.pos > 0:  # 有多头持仓
                self.intra_trade_high = max(self.intra_trade_high, bar.high_price)
                long_stop = self.intra_trade_high * (1 - self.trailing_long / 100)  # 按照百分比止损的价格，多头
                self.sell(long_stop, abs(self.pos), stop=True)  # 止损价格
            elif self.pos < 0:  # 有空头持仓
                self.intra_trade_low = min(self.intra_trade_low, bar.low_price)
                short_stop = self.intra_trade_low * (1 + self.trailing_short / 100)
                self.cover(short_stop, abs(self.pos), stop=True)
        # 关闭现有头寸
        else:
            if self.pos > 0:
                self.sell(bar.close_price * 0.99, abs(self.pos))
            elif self.pos < 0:
                self.cover(bar.close_price, abs(self.pos))

        self.put_event()

    def on_order(self, order: OrderData):
        pass

    def on_trade(self, trade: TradeData):
        pass

    def on_stop_order(self, stop_order: StopOrder):
        pass
