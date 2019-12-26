from vnpy.app.cta_strategy import (
    StopOrder,
    TickData,
    BarData,
    TradeData,
    OrderData,
    BarGenerator,
    ArrayManager,
    CtaSignal,
    TargetPosTemplate
)


class RsiSignal(CtaSignal):
    """"""

    def __init__(self, rsi_window: int, rsi_level: float):
        """Constructor"""
        super().__init__()

        self.rsi_window = rsi_window
        self.rsi_level = rsi_level
        self.rsi_long = 50 + self.rsi_level
        self.rsi_short = 50 - self.rsi_level

        self.bg = BarGenerator(self.on_bar)
        self.am = ArrayManager()

    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        self.bg.update_tick(tick)

    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        self.am.update_bar(bar)
        if not self.am.inited:
            self.set_signal_pos(0)

        rsi_value = self.am.rsi(self.rsi_window)

        if rsi_value >= self.rsi_long:
            self.set_signal_pos(1)
        elif rsi_value <= self.rsi_short:
            self.set_signal_pos(-1)
        else:
            self.set_signal_pos(0)


class CciSignal(CtaSignal):
    """"""

    def __init__(self, cci_window: int, cci_level: float):
        """"""
        super().__init__()

        self.cci_window = cci_window
        self.cci_level = cci_level
        self.cci_long = self.cci_level
        self.cci_short = -self.cci_level

        self.bg = BarGenerator(self.on_bar)
        self.am = ArrayManager()

    def on_tick(self, tick: TickData):
        """
        Callback of new tick data update.
        """
        self.bg.update_tick(tick)

    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        self.am.update_bar(bar)
        if not self.am.inited:
            self.set_signal_pos(0)

        cci_value = self.am.cci(self.cci_window)

        if cci_value >= self.cci_long:
            self.set_signal_pos(1)
        elif cci_value <= self.cci_short:
            self.set_signal_pos(-1)
        else:
            self.set_signal_pos(0)


class MaSignal(CtaSignal):
    """"""

    def __init__(self, fast_window: int, slow_window: int):
        """"""
        super().__init__()

        self.fast_window = fast_window
        self.slow_window = slow_window

        self.bg = BarGenerator(self.on_bar, 5, self.on_5min_bar)
        self.am = ArrayManager()

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

    def on_5min_bar(self, bar: BarData):
        """"""
        self.am.update_bar(bar)
        if not self.am.inited:
            self.set_signal_pos(0)

        fast_ma = self.am.sma(self.fast_window)
        slow_ma = self.am.sma(self.slow_window)

        if fast_ma > slow_ma:
            self.set_signal_pos(1)
        elif fast_ma < slow_ma:
            self.set_signal_pos(-1)
        else:
            self.set_signal_pos(0)


class MultiSignalStrategy(TargetPosTemplate):
    """"""

    author = "用Python的交易员"

    rsi_window = 14
    rsi_level = 20
    cci_window = 30
    cci_level = 10
    fast_window = 5
    slow_window = 20

    signal_pos = {}

    parameters = ["rsi_window", "rsi_level", "cci_window",
                  "cci_level", "fast_window", "slow_window"]
    variables = ["signal_pos", "target_pos"]

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        super().__init__(cta_engine, strategy_name, vt_symbol, setting)

        self.rsi_signal = RsiSignal(self.rsi_window, self.rsi_level)
        self.cci_signal = CciSignal(self.cci_window, self.cci_level)
        self.ma_signal = MaSignal(self.fast_window, self.slow_window)

        self.signal_pos = {
            "rsi": 0,
            "cci": 0,
            "ma": 0
        }

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
        super(MultiSignalStrategy, self).on_tick(tick)

        self.rsi_signal.on_tick(tick)
        self.cci_signal.on_tick(tick)
        self.ma_signal.on_tick(tick)

        self.calculate_target_pos()

    def on_bar(self, bar: BarData):
        """
        Callback of new bar data update.
        """
        super(MultiSignalStrategy, self).on_bar(bar)

        self.rsi_signal.on_bar(bar)
        self.cci_signal.on_bar(bar)
        self.ma_signal.on_bar(bar)

        self.calculate_target_pos()

    def calculate_target_pos(self):
        """"""
        self.signal_pos["rsi"] = self.rsi_signal.get_signal_pos()
        self.signal_pos["cci"] = self.cci_signal.get_signal_pos()
        self.signal_pos["ma"] = self.ma_signal.get_signal_pos()

        target_pos = 0
        for v in self.signal_pos.values():
            target_pos += v

        self.set_target_pos(target_pos)

    def on_order(self, order: OrderData):
        """
        Callback of new order data update.
        """
        super(MultiSignalStrategy, self).on_order(order)

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
