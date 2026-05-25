from __future__ import annotations

from dataclasses import asdict

from vnpy.chan import BuySignal, ChanAnalyzer, ChanConfig, SellSignal
from vnpy.trader.position_sizing import PositionSizingRequest, calculate_position_size
from vnpy_ctastrategy import (
    BarData,
    BarGenerator,
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
    sizing_mode: str = "fixed"
    target_long_ratio: float = 0.05
    risk_per_trade: float = 0.01
    capital: float = 0
    min_volume: float = 0
    volume_step: float = 0
    max_order_value: float = 0
    max_position_value: float = 0
    max_position_ratio: float = 0
    atr_value: float = 0
    atr_multiplier: float = 1
    init_days: int = 0

    latest_signal_type: str = ""
    latest_signal_reason: str = ""
    active_stop_price: float = 0
    active_stop_orderid: str = ""
    last_signal_key: str = ""
    exit_order_sent: bool = False
    latest_chan_signal: dict = {}
    warmup_bar_count: int = 0

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
        "sizing_mode",
        "target_long_ratio",
        "risk_per_trade",
        "capital",
        "min_volume",
        "volume_step",
        "max_order_value",
        "max_position_value",
        "max_position_ratio",
        "atr_value",
        "atr_multiplier",
        "init_days",
    ]
    variables = [
        "latest_signal_type",
        "latest_signal_reason",
        "active_stop_price",
        "active_stop_orderid",
        "last_signal_key",
        "exit_order_sent",
        "latest_chan_signal",
    ]

    def on_init(self) -> None:
        """Initialize strategy state."""

        self.write_log("缠论策略初始化")
        self.bg: BarGenerator = BarGenerator(self.on_bar)
        self.analyzer = ChanAnalyzer(self._create_chan_config())
        self.warmup_bar_count = 0
        if self.init_days > 0:
            self.load_bar(self.init_days, callback=self._warmup_bar)
            self.write_log(f"缠论预热完成: {self.warmup_bar_count} bars")

    def on_start(self) -> None:
        """Start strategy."""

        self.write_log("缠论策略启动")
        self.put_event()

    def on_stop(self) -> None:
        """Stop strategy."""

        self.write_log("缠论策略停止")
        self.put_event()

    def on_tick(self, tick: TickData) -> None:
        """Update bar generator with live tick data."""

        self.bg.update_tick(tick)

    def on_bar(self, bar: BarData) -> None:
        """Update Chan analyzer and trade confirmed buy signals."""

        if self.pos == 0:
            self.cancel_all()
        snapshot = self.analyzer.update_bar(bar)

        if self.pos > 0:
            if snapshot.sell_signals:
                sell_signal = snapshot.sell_signals[-1]
                signal_key = self._build_sell_signal_key(sell_signal)
                if signal_key != self.last_signal_key:
                    self.cancel_all()
                    close_volume = self._calculate_close_volume(bar)
                    if close_volume <= 0:
                        self.write_log("缠论卖点清仓跳过: sizing returned zero volume")
                        self.put_event()
                        return
                    self.sell(bar.close_price - self.price_add, close_volume)
                    self.latest_signal_type = sell_signal.type.value
                    self.latest_signal_reason = sell_signal.reason
                    self.last_signal_key = signal_key
                    self.active_stop_orderid = ""
                    self.exit_order_sent = True
                    self.write_log(
                        f"缠论卖点清仓: {sell_signal.type.value}, reason={sell_signal.reason}"
                    )
                    self.put_event()
                    return

            self._ensure_stop_order()
            self.put_event()
            return

        if self.pos == 0 and snapshot.signals:
            signal = snapshot.signals[-1]
            signal_key = self._build_signal_key(signal)
            if signal_key != self.last_signal_key:
                self.latest_signal_type = signal.type.value
                self.latest_signal_reason = signal.reason
                sizing = self._calculate_entry_sizing(bar, signal)
                self.latest_chan_signal = {
                    "signal_key": signal_key,
                    "type": signal.type.value,
                    "sizing_mode": self.sizing_mode,
                    "target_ratio": self.target_long_ratio,
                    "risk_per_trade": self.risk_per_trade,
                    "candidate_index": signal.candidate_index,
                    "confirmed_index": signal.confirmed_index,
                    "stop_price": signal.stop_price,
                    "reason": signal.reason,
                    "bar_datetime": bar.datetime.isoformat(),
                    "bar_close_price": bar.close_price,
                    "sizing": asdict(sizing) if sizing else {},
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

                order_volume = self._calculate_entry_volume(sizing)
                if order_volume <= 0:
                    self.last_signal_key = signal_key
                    self.write_log(
                        "缠论买点跳过: sizing returned zero volume, "
                        f"reason={sizing.reason if sizing else 'fixed size unavailable'}"
                    )
                    self.put_event()
                    return

                if self.sizing_mode == "fixed" and self.fixed_size > self.max_position:
                    self.last_signal_key = signal_key
                    self.write_log(
                        f"缠论买点跳过: 下单数量 {self.fixed_size} 超过最大仓位 {self.max_position}"
                    )
                    self.put_event()
                    return

                self.buy(bar.close_price + self.price_add, order_volume)
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
            self.active_stop_orderid = ""
            self.exit_order_sent = False
        else:
            self._ensure_stop_order()
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

    def _warmup_bar(self, bar: BarData) -> None:
        """Feed historical bars into Chan analyzer without trading."""
        self.analyzer.update_bar(bar)
        self.warmup_bar_count += 1

    def _build_signal_key(self, signal: BuySignal) -> str:
        """Build a stable key for the same logical Chan signal across windows."""
        return f"{signal.type.value}:{signal.confirmed_index}:{signal.stop_price}"

    def _build_sell_signal_key(self, signal: SellSignal) -> str:
        """Build a stable key for the same logical Chan sell signal."""
        return f"{signal.type.value}:{signal.confirmed_index}:{signal.stop_price}"

    def _ensure_stop_order(self) -> None:
        """Ensure the open long position has one local stop order."""
        if not self.active_stop_price or self.active_stop_orderid or self.pos <= 0:
            return

        vt_orderids = self.sell(self.active_stop_price, abs(self.pos), stop=True)
        self.active_stop_orderid = vt_orderids[0] if vt_orderids else ""
        self.exit_order_sent = bool(self.active_stop_orderid)
        self.write_log(f"缠论止损单已提交: {self.active_stop_price}")

    def _calculate_entry_sizing(self, bar: BarData, signal: BuySignal):
        """Calculate entry sizing for non-fixed modes."""
        if self.sizing_mode == "fixed":
            return None

        return calculate_position_size(
            PositionSizingRequest(
                mode=self.sizing_mode,
                target_ratio=self.target_long_ratio,
                risk_per_trade=self.risk_per_trade,
                price=bar.close_price,
                current_volume=self.pos,
                equity=self.capital,
                stop_price=signal.stop_price,
                atr=self.atr_value,
                atr_multiplier=self.atr_multiplier,
                min_volume=self.min_volume,
                volume_step=self.volume_step,
                max_position=self.max_position,
                max_position_value=self.max_position_value,
                max_position_ratio=self.max_position_ratio,
                max_order_value=self.max_order_value,
            )
        )

    def _calculate_entry_volume(self, sizing) -> float:
        """Return entry order volume for current sizing mode."""
        if self.sizing_mode == "fixed":
            return self.fixed_size
        if not sizing:
            return 0
        return max(sizing.order_volume, 0)

    def _calculate_close_volume(self, bar: BarData) -> float:
        """Return close volume for sell-signal clearing."""
        if self.sizing_mode == "fixed":
            return abs(self.pos)

        sizing = calculate_position_size(
            PositionSizingRequest(
                mode="target_ratio",
                target_ratio=0,
                risk_per_trade=0,
                price=bar.close_price,
                current_volume=self.pos,
                equity=self.capital or 1,
                min_volume=self.min_volume,
                volume_step=self.volume_step,
                max_position=self.max_position,
                max_position_value=self.max_position_value,
                max_position_ratio=self.max_position_ratio,
                max_order_value=self.max_order_value,
            )
        )
        return abs(sizing.order_volume)
