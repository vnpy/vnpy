from vnpy.app.cta_strategy_pro import (
    CtaTemplate,
    StopOrder,
    Direction,
    Offset,
    TickData,
    BarData,
    TradeData,
    OrderData,
    BarGenerator,
    ArrayManager,
)


class TurtleSignalStrategy_v2(CtaTemplate):
    """"""
    author = "用Python的交易员"

    x_minute = 15
    entry_window = 20
    exit_window = 10
    atr_window = 20
    fixed_size = 1
    invest_pos = 1
    invest_percent = 10     # 投资比例

    entry_up = 0
    entry_down = 0
    exit_up = 0
    exit_down = 0
    atr_value = 0

    long_entry = 0
    short_entry = 0
    long_stop = 0
    short_stop = 0

    parameters = ["x_minuite", "entry_window", "exit_window", "atr_window", "fixed_size"]
    variables = ["entry_up", "entry_down", "exit_up", "exit_down", "atr_value"]

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super(TurtleSignalStrategy_v2, self).__init__(
            cta_engine, strategy_name, vt_symbol, setting
        )

        # 获取合约乘数，保证金比例
        self.symbol_size = self.cta_engine.get_size(self.vt_symbol)
        self.symbol_margin_rate = self.cta_engine.get_margin_rate(self.vt_symbol)

        self.bg = BarGenerator(self.on_bar, window=self.x_minute)
        self.am = ArrayManager()

        self.cur_mi_price = None

    def on_init(self):
        """
        Callback when strategy is inited.
        """
        self.write_log("策略初始化")
        #self.load_bar(20)

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

        self.cur_mi_price = bar.close_price

        self.am.update_bar(bar)
        if not self.am.inited:
            return

        # Only calculates new entry channel when no position holding
        if not self.pos:
            self.entry_up, self.entry_down = self.am.donchian(
                self.entry_window
            )

        self.exit_up, self.exit_down = self.am.donchian(self.exit_window)

        if not self.pos:
            self.atr_value = self.am.atr(self.atr_window)

            self.long_entry = 0
            self.short_entry = 0
            self.long_stop = 0
            self.short_stop = 0

            self.send_buy_orders(self.entry_up)
            self.send_short_orders(self.entry_down)
        elif self.pos > 0:
            self.send_buy_orders(self.entry_up)

            sell_price = max(self.long_stop, self.exit_down)
            self.sell(sell_price, abs(self.pos), True)

        elif self.pos < 0:
            self.send_short_orders(self.entry_down)

            cover_price = min(self.short_stop, self.exit_up)
            ret = self.cover(cover_price, abs(self.pos), True)

        self.put_event()

    def update_invest_pos(self):
        """计算获取投资仓位"""
        # 获取账号资金
        capital, available, cur_percent, percent_limit = self.cta_engine.get_account()
        # 按照投资比例计算保证金
        invest_margin = capital * self.invest_percent / 100
        max_invest_pos = int(invest_margin / (self.cur_mi_price * self.symbol_size * self.symbol_margin_rate))
        self.invest_pos = max(int(max_invest_pos / 4), 1)

    def on_trade(self, trade: TradeData):
        """
        Callback of new trade data update.
        """
        pre_pos = self.pos
        if trade.direction == Direction.LONG:
            self.long_entry = trade.price
            self.long_stop = self.long_entry - 2 * self.atr_value
            self.pos += trade.volume
        else:
            self.short_entry = trade.price
            self.short_stop = self.short_entry + 2 * self.atr_value
            self.pos -= trade.volume

        self.write_log(f'{self.vt_symbol},pos {pre_pos} => {self.pos}')

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

    def send_buy_orders(self, price):
        """"""
        if self.pos >= 4:
            return

        if self.cur_mi_price <= price - self.atr_value/2:
            return

        self.update_invest_pos()

        t = self.pos / self.invest_pos

        if t < 1:
            self.buy(price, self.invest_pos, True)

        if t < 2:
            self.buy(price + self.atr_value * 0.5, self.invest_pos, True)

        if t < 3:
            self.buy(price + self.atr_value, self.invest_pos, True)

        if t < 4:
            self.buy(price + self.atr_value * 1.5, self.invest_pos, True)

    def send_short_orders(self, price):
        """"""
        if self.pos <= -4:
            return

        if self.cur_mi_price >= price + self.atr_value / 2:
            return

        self.update_invest_pos()

        t = self.pos / self.invest_pos

        if t > -1:
            self.short(price, self.invest_pos, True)

        if t > -2:
            self.short(price - self.atr_value * 0.5, self.invest_pos, True)

        if t > -3:
            self.short(price - self.atr_value, self.invest_pos, True)

        if t > -4:
            self.short(price - self.atr_value * 1.5, self.invest_pos, True)
