import numpy as np

from vnpy_ctastrategy import (
    CtaTemplate,
    StopOrder,
    TickData,
    BarData,
    TradeData,
    OrderData,
    BarGenerator,
    ArrayManager,
)


class DoubleMaStrategy(CtaTemplate):
    """"""

    author = "用Python的交易员"

    fast_window: int = 10
    slow_window: int = 20

    fast_ma0: float = 0.0
    fast_ma1: float = 0.0
    slow_ma0: float = 0.0
    slow_ma1: float = 0.0

    parameters = ["fast_window", "slow_window"]
    variables = ["fast_ma0", "fast_ma1", "slow_ma0", "slow_ma1"]

    def on_init(self) -> None:
        """
        Callback when strategy is inited.
        """
        self.write_log("策略初始化")

        self.bg: BarGenerator = BarGenerator(self.on_bar)
        self.am: ArrayManager = ArrayManager()

        self.load_bar(10)

    def on_start(self) -> None:
        """
        Callback when strategy is started.
        """
        self.write_log("策略启动")
        self.put_event()

    def on_stop(self) -> None:
        """
        Callback when strategy is stopped.
        """
        self.write_log("策略停止")

        self.put_event()

    def on_tick(self, tick: TickData) -> None:
        """
        Callback of new tick data update.
        """
        self.bg.update_tick(tick)

    def on_bar(self, bar: BarData) -> None:
        """
        Callback of new bar data update.
        """
        self.cancel_all()

        am: ArrayManager = self.am
        am.update_bar(bar)

        # ========== 日志输出：数据接收 ==========
        self.write_log("=" * 60)
        self.write_log(f"📊 收到K线数据 | 时间: {bar.datetime}")
        self.write_log(
            f"   价格信息 - 开: {bar.open_price:.4f} 高: {bar.high_price:.4f} 低: {bar.low_price:.4f} 收: {bar.close_price:.4f}"
        )
        self.write_log(f"   成交量: {bar.volume:.2f}")

        if not am.inited:
            self.write_log(
                f"⏳ ArrayManager 初始化中... 当前数据: {am.count}/{am.size}"
            )
            return

        # ========== 日志输出：指标计算 ==========
        fast_ma: np.ndarray = am.sma(self.fast_window, array=True)
        self.fast_ma0 = fast_ma[-1]
        self.fast_ma1 = fast_ma[-2]

        slow_ma: np.ndarray = am.sma(self.slow_window, array=True)
        self.slow_ma0 = slow_ma[-1]
        self.slow_ma1 = slow_ma[-2]

        self.write_log(
            f"📈 指标计算 - 快线({self.fast_window}): 当前={self.fast_ma0:.4f}, 上期={self.fast_ma1:.4f}"
        )
        self.write_log(
            f"📈 指标计算 - 慢线({self.slow_window}): 当前={self.slow_ma0:.4f}, 上期={self.slow_ma1:.4f}"
        )

        # ========== 日志输出：交叉判断 ==========
        cross_over: bool = (
            self.fast_ma0 > self.slow_ma0 and self.fast_ma1 < self.slow_ma1
        )
        cross_below: bool = (
            self.fast_ma0 < self.slow_ma0 and self.fast_ma1 > self.slow_ma1
        )
        golden_cross: bool = self.fast_ma0 > self.slow_ma0  # 当前金叉状态（非穿越）

        self.write_log(
            f"🔍 交叉判断 - 金叉穿越: {cross_over} | 死叉穿越: {cross_below} | 当前金叉: {golden_cross}"
        )

        # ========== 日志输出：仓位与信号 ==========
        self.write_log(f"💼 当前仓位: {self.pos}")

        if cross_over:
            self.write_log("✅ 信号触发: 金叉穿越（快线上穿慢线）")
            if self.pos == 0:
                self.write_log(f"📤 执行: 买入开仓 @ {bar.close_price:.4f}, 数量=1")
                self.buy(bar.close_price, 1)
            elif self.pos < 0:
                self.write_log(
                    f"📤 执行: 平空仓 + 开多仓 @ {bar.close_price:.4f}, 数量=1"
                )
                self.cover(bar.close_price, 1)
                self.buy(bar.close_price, 1)
            else:
                self.write_log("⏸️  已有持仓，不操作")

        elif cross_below:
            self.write_log("✅ 信号触发: 死叉穿越（快线下穿慢线）")
            if self.pos == 0:
                self.write_log(f"📤 执行: 卖出开仓 @ {bar.close_price:.4f}, 数量=1")
                self.short(bar.close_price, 1)
            elif self.pos > 0:
                self.write_log(
                    f"📤 执行: 平多仓 + 开空仓 @ {bar.close_price:.4f}, 数量=1"
                )
                self.sell(bar.close_price, 1)
                self.short(bar.close_price, 1)
            else:
                self.write_log("⏸️  已有持仓，不操作")

        else:
            # 没有交叉信号，分析为什么没命中
            if self.fast_ma0 > self.slow_ma0:
                diff_pct = (self.fast_ma0 - self.slow_ma0) / self.slow_ma0 * 100
                self.write_log(
                    f"⏸️  无信号 - 维持金叉状态，快线在慢线上方 {diff_pct:.2f}%"
                )
            elif self.fast_ma0 < self.slow_ma0:
                diff_pct = (self.slow_ma0 - self.fast_ma0) / self.slow_ma0 * 100
                self.write_log(
                    f"⏸️  无信号 - 维持死叉状态，快线在慢线下方 {diff_pct:.2f}%"
                )
            else:
                self.write_log("⏸️  无信号 - 快线与慢线持平")

            self.write_log(
                f"   上期快/慢: {self.fast_ma1:.4f}/{self.slow_ma1:.4f} | 本期快/慢: {self.fast_ma0:.4f}/{self.slow_ma0:.4f}"
            )

        self.put_event()

    def on_order(self, order: OrderData) -> None:
        """
        Callback of new order data update.
        """
        pass

    def on_trade(self, trade: TradeData) -> None:
        """
        Callback of new trade data update.
        """
        self.put_event()

    def on_stop_order(self, stop_order: StopOrder) -> None:
        """
        Callback of stop order update.
        """
        pass
