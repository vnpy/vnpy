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


class BollReversionStrategy(CtaTemplate):
    """
    适用于 DOGE 小时线的布林回归策略
    """
    author = "Fixed_For_DOGE_1H"

    # 参数
    boll_window: int = 20  # 布林带周期，小时线通常可以用 20
    boll_dev: float = 2.0  # 标准差倍数，2.0 是回归策略的标准
    cci_window: int = 14
    atr_window: int = 24  # ATR 周期
    sl_multiplier: float = 3.0
    capital: float = 10_000
    use_ratio: float = 0.9
    leverage: float = 1
    volume_ratio: float = 1
    min_order_volume: float = 1

    # 变量
    boll_up: float = 0
    boll_down: float = 0
    boll_mid: float = 0
    cci_value: float = 0
    atr_value: float = 0
    intra_trade_high: float = 0
    intra_trade_low: float = 0
    long_stop: float = 0
    short_stop: float = 0

    parameters = [
        "boll_window",
        "boll_dev",
        "cci_window",
        "atr_window",
        "sl_multiplier",
        "capital",
        "use_ratio",
        "leverage",
        "volume_ratio",
        "min_order_volume"
    ]
    variables = [
        "boll_up",
        "boll_down",
        "boll_mid",
        "cci_value",
        "atr_value",
        "intra_trade_high",
        "intra_trade_low",
        "long_stop",
        "short_stop"
    ]

    def on_init(self) -> None:
        self.write_log("策略初始化")

        # 1. 移除 15 倍合成，只保留基础的 BarGenerator 用于处理 Tick 变 Bar (如果是回测其实只用 on_bar 也可以)
        self.bg = BarGenerator(self.on_bar)

        # 2. ArrayManager 默认需要 100 个数据初始化。
        # 10天的小时线数据 = 240根，足够初始化了。
        self.am = ArrayManager(size=100)
        self.load_bar(10)

    def on_start(self) -> None:
        self.write_log("策略启动")

    def on_stop(self) -> None:
        self.write_log("策略停止")

    def on_tick(self, tick: TickData) -> None:
        self.bg.update_tick(tick)

    def on_bar(self, bar: BarData) -> None:
        """
        直接在 on_bar (小时线) 中运行逻辑
        """
        self.cancel_all()

        am = self.am
        am.update_bar(bar)
        if not am.inited:
            return

        # 计算指标
        self.boll_up, self.boll_down = am.boll(self.boll_window, self.boll_dev)
        self.boll_mid = am.sma(self.boll_window)
        self.cci_value = am.cci(self.cci_window)
        self.atr_value = am.atr(self.atr_window)

        # 打印一下日志，确保指标在计算 (调试用，正式跑可以注释掉)
        # print(f"{bar.datetime} Close:{bar.close_price} Up:{self.boll_up:.4f} Down:{self.boll_down:.4f} CCI:{self.cci_value:.2f}")

        # === 仓位判断 ===
        if self.pos == 0:
            self.intra_trade_high = bar.high_price
            self.intra_trade_low = bar.low_price
            order_volume: float = self.calc_order_volume(
                price=bar.close_price,
                capital=self.capital,
                leverage=self.leverage,
                use_ratio=self.use_ratio,
                volume_ratio=self.volume_ratio,
                min_volume=self.min_order_volume
            )
            if order_volume <= 0:
                return

            # == 开仓逻辑 ==
            # 下单价格修改：针对 DOGE 这种低价币，不要用固定点数(如+5)，要用百分比

            # 做多：跌破下轨 + CCI超卖
            if bar.close_price < self.boll_down and self.cci_value < -100:
                # 以当前价格的 101% 买入（确保立即成交）
                price = bar.close_price * 1.01
                self.buy(price, order_volume)

            # 做空：涨破上轨 + CCI超买
            elif bar.close_price > self.boll_up and self.cci_value > 100:
                # 以当前价格的 99% 卖出
                price = bar.close_price * 0.99
                self.short(price, order_volume)

        # === 持多单 ===
        elif self.pos > 0:
            self.intra_trade_high = max(self.intra_trade_high, bar.high_price)

            # 止损
            self.long_stop = self.intra_trade_high - self.atr_value * self.sl_multiplier
            if bar.close_price < self.long_stop:
                self.sell(bar.close_price * 0.99, abs(self.pos))

            # 止盈 (回归中轨)
            elif bar.close_price >= self.boll_mid:
                self.sell(bar.close_price * 0.99, abs(self.pos))

        # === 持空单 ===
        elif self.pos < 0:
            self.intra_trade_high = bar.high_price
            self.intra_trade_low = min(self.intra_trade_low, bar.low_price)

            # 止损
            self.short_stop = self.intra_trade_low + self.atr_value * self.sl_multiplier
            if bar.close_price > self.short_stop:
                self.cover(bar.close_price * 1.01, abs(self.pos))

            # 止盈 (回归中轨)
            elif bar.close_price <= self.boll_mid:
                self.cover(bar.close_price * 1.01, abs(self.pos))

        self.put_event()
