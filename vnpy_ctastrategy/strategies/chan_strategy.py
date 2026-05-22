from __future__ import annotations

from vnpy.chan import BuyPointType, ChanAnalyzer, ChanConfig
from vnpy_ctastrategy import (
    BarData,
    CtaTemplate,
    OrderData,
    StopOrder,
    TickData,
    TradeData,
)


class ChanStrategy(CtaTemplate):
    """Chan theory long-only CTA strategy prototype."""

    author = "VeighNa"

    fixed_size: float = 1
    min_stroke_gap: int = 1
    strict_stroke: bool = True
    pivot_min_segments: int = 3
    pivot_tolerance: float = 0
    third_buy_pullback_tolerance: float = 0
    second_buy_low_tolerance: float = 0
    max_bars: int = 300
    price_add: float = 0
    trade_enabled: bool = True
    max_position: float = 100

    latest_signal_type: str = ""
    latest_signal_reason: str = ""
    active_stop_price: float = 0
    last_signal_key: str = ""
    exit_order_sent: bool = False
    latest_chan_signal: dict = {}

    parameters = [
        "fixed_size",
        "min_stroke_gap",
        "strict_stroke",
        "pivot_min_segments",
        "pivot_tolerance",
        "third_buy_pullback_tolerance",
        "second_buy_low_tolerance",
        "max_bars",
        "price_add",
        "trade_enabled",
        "max_position",
    ]
    variables = [
        "latest_signal_type",
        "latest_signal_reason",
        "active_stop_price",
        "last_signal_key",
        "exit_order_sent",
        "latest_chan_signal",
    ]

    def on_init(self) -> None:
        """Initialize strategy state."""

        self.write_log("缠论策略初始化")
        self.analyzer = ChanAnalyzer(self._create_chan_config())

    def on_start(self) -> None:
        """Start strategy."""

        self.write_log("缠论策略启动")
        self.put_event()

    def on_stop(self) -> None:
        """Stop strategy."""

        self.write_log("缠论策略停止")
        self.put_event()

    def on_tick(self, tick: TickData) -> None:
        """Ignore tick data in the first prototype."""

        return

    def on_bar(self, bar: BarData) -> None:
        """Update Chan analyzer and trade confirmed buy signals."""

        self.cancel_all()
        snapshot = self.analyzer.update_bar(bar)

        if self.pos > 0 and self.active_stop_price and not self.exit_order_sent:
            if bar.low_price <= self.active_stop_price:
                self.sell(self.active_stop_price - self.price_add, abs(self.pos))
                self.exit_order_sent = True
                self.write_log(f"缠论止损触发: {self.active_stop_price}")
                self.put_event()
                return

        if self.pos == 0 and snapshot.signals:
            signal = snapshot.signals[-1]
            signal_key = f"{signal.type.value}:{signal.confirmed_index}"
            if signal_key != self.last_signal_key:
                self.latest_signal_type = signal.type.value
                self.latest_signal_reason = signal.reason
                self.latest_chan_signal = {
                    "type": signal.type.value,
                    "candidate_index": signal.candidate_index,
                    "confirmed_index": signal.confirmed_index,
                    "stop_price": signal.stop_price,
                    "reason": signal.reason,
                    "bar_datetime": bar.datetime.isoformat(),
                    "bar_close_price": bar.close_price,
                    "trade_enabled": self.trade_enabled,
                }
                if not self.trade_enabled:
                    self.last_signal_key = signal_key
                    self.write_log(
                        f"缠论买点触发（信号模式，不下单）: {signal.type.value}, "
                        f"stop={signal.stop_price}, reason={signal.reason}"
                    )
                    self.put_event()
                    return

                if self.fixed_size > self.max_position:
                    self.last_signal_key = signal_key
                    self.write_log(
                        f"缠论买点跳过: 下单数量 {self.fixed_size} 超过最大仓位 {self.max_position}"
                    )
                    self.put_event()
                    return

                self.buy(bar.close_price + self.price_add, self.fixed_size)
                self.active_stop_price = signal.stop_price
                self.last_signal_key = signal_key
                self.exit_order_sent = False
                self.write_log(
                    f"缠论买点触发: {signal.type.value}, "
                    f"stop={signal.stop_price}, reason={signal.reason}"
                )

        self.put_event()

    def on_order(self, order: OrderData) -> None:
        """Handle order updates."""

        return

    def on_trade(self, trade: TradeData) -> None:
        """Handle trade updates."""

        if self.pos == 0:
            self.active_stop_price = 0
            self.exit_order_sent = False
        self.put_event()

    def on_stop_order(self, stop_order: StopOrder) -> None:
        """Handle stop order updates."""

        return

    def _create_chan_config(self) -> ChanConfig:
        return ChanConfig(
            min_stroke_gap=self.min_stroke_gap,
            strict_stroke=self.strict_stroke,
            pivot_min_segments=self.pivot_min_segments,
            pivot_tolerance=self.pivot_tolerance,
            third_buy_pullback_tolerance=self.third_buy_pullback_tolerance,
            second_buy_low_tolerance=self.second_buy_low_tolerance,
            max_bars=self.max_bars or None,
        )
