"""
DoubleMA策略的Telegram确认版本
在发出交易信号时会等待Telegram确认
"""

import numpy as np
import asyncio
from datetime import datetime
from math import floor

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
from vnpy.trader.constant import Status

from trading_config import load_trading_config


class DoubleMATelegramStrategy(CtaTemplate):
    """
    DoubleMA策略（带Telegram人工确认）

    策略逻辑：
    - 快线上穿慢线（金叉）-> 买入做多
    - 快线下穿慢线（死叉）-> 卖出做空

    新增功能：
    - 每次交易前通过Telegram确认
    - 推送详细的回测信息和交易逻辑
    """

    author = "AutoTrader with Telegram"

    # 策略参数
    fast_window: int = 10
    slow_window: int = 20

    # 策略变量
    fast_ma0: float = 0.0
    fast_ma1: float = 0.0
    slow_ma0: float = 0.0
    slow_ma1: float = 0.0

    parameters = ["fast_window", "slow_window"]
    variables = ["fast_ma0", "fast_ma1", "slow_ma0", "slow_ma1"]

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """初始化"""
        super().__init__(cta_engine, strategy_name, vt_symbol, setting)

        self.bg: BarGenerator = None
        self.am: ArrayManager = None
        self.telegram = getattr(cta_engine, "telegram_notifier", None)
        self.backtest_report: dict = {}
        self.trade_counter: int = 0
        self.trading_config: dict = {}
        self.risk_config: dict = {}
        self.pending_trade_request: bool = False
        self.last_signal_at: dict[int, datetime] = {}
        self.last_any_signal_at: datetime | None = None
        self.last_signal_direction: int | None = None

        try:
            from pathlib import Path

            config_path = Path(__file__).parent / "config" / "trading_config.json"
            full_config = load_trading_config(config_path)
            self.runtime_config = full_config.get("runtime", {})
            self.risk_config = full_config.get("risk", {})
            self.trading_config = full_config.get(
                "trading",
                {
                    "leverage": 1,
                    "position_ratio": 0.05,
                    "trade_quantity": 1,
                    "max_position": 100,
                    "stop_loss_pct": 5.0,
                    "take_profit_pct": 10.0,
                },
            )
        except Exception as e:
            self.write_log(f"加载交易配置失败: {e}，使用默认参数")
            self.runtime_config = {}
            self.risk_config = {}
            self.trading_config = {
                "leverage": 1,
                "position_ratio": 0.05,
                "trade_quantity": 1,
                "max_position": 100,
                "stop_loss_pct": 5.0,
                "take_profit_pct": 10.0,
            }

    def _submit_telegram_message(self, message: str) -> None:
        """Submit Telegram notification from vn.py callback threads."""
        if not self.telegram:
            self.write_log("Telegram通知未配置，跳过发送")
            return
        try:
            future = self.telegram.submit_message(message)
        except Exception as exc:  # noqa: BLE001
            self.write_log(f"Telegram通知提交失败: {exc!r}")
            return

        def _log_failure(fut) -> None:
            try:
                fut.result()
            except Exception as exc:  # noqa: BLE001
                self.write_log(f"Telegram通知发送失败: {exc!r}")

        future.add_done_callback(_log_failure)

    def on_init(self) -> None:
        """策略初始化"""
        self.write_log("策略初始化 - DoubleMA with Telegram确认")

        self.bg = BarGenerator(self.on_bar)
        self.am = ArrayManager()

        # 加载历史数据用于计算均线
        init_days = int(self.runtime_config.get("init_days", 3) or 3)
        self.load_bar(init_days)

        # 加载回测报告（如果存在）
        try:
            import json

            with open("config/backtest_result.json", "r") as f:
                self.backtest_report = json.load(f)
            self.write_log(
                f"已加载回测报告: 收益 {self.backtest_report.get('total_return', 0):.2f}%"
            )
        except:
            self.write_log("未找到回测报告，使用默认参数")
            self.backtest_report = {
                "total_return": 0,
                "sharpe_ratio": 0,
                "max_drawdown": 0,
                "win_rate": 0,
            }

    def on_start(self) -> None:
        """策略启动"""
        self.write_log("策略启动")
        self.put_event()

        # 发送启动通知
        if self.telegram:
            self._submit_telegram_message(
                f"✅ <b>DoubleMA策略已启动</b>\n"
                f"品种: {self.vt_symbol}\n"
                f"参数: 快线={self.fast_window}, 慢线={self.slow_window}\n"
                f"等待交易信号..."
            )

    def on_stop(self) -> None:
        """策略停止"""
        self.write_log("策略停止")
        self.put_event()

    def on_tick(self, tick: TickData) -> None:
        """Tick数据回调"""
        self.bg.update_tick(tick)

    def on_bar(self, bar: BarData) -> None:
        """K线数据回调 - 核心交易逻辑"""
        self.cancel_all()

        am: ArrayManager = self.am
        am.update_bar(bar)
        if not am.inited:
            return

        # 计算均线
        fast_ma: np.ndarray = am.sma(self.fast_window, array=True)
        self.fast_ma0 = fast_ma[-1]
        self.fast_ma1 = fast_ma[-2]

        slow_ma: np.ndarray = am.sma(self.slow_window, array=True)
        self.slow_ma0 = slow_ma[-1]
        self.slow_ma1 = slow_ma[-2]

        if not self.trading:
            self.put_event()
            return

        threshold = self._ma_cross_deadband(bar.close_price)
        current_spread = self.fast_ma0 - self.slow_ma0
        previous_spread = self.fast_ma1 - self.slow_ma1

        # 判断金叉/死叉：使用阈值带过滤，避免1分钟线上快慢线贴合时来回反手。
        cross_over: bool = previous_spread <= -threshold and current_spread >= threshold
        cross_below: bool = previous_spread >= threshold and current_spread <= -threshold

        if not cross_over and not cross_below and self._is_near_cross(previous_spread, current_spread, threshold):
            self.write_log(
                "均线差值未超过阈值，跳过弱交叉: "
                f"prev={previous_spread:.8f}, curr={current_spread:.8f}, "
                f"threshold={threshold:.8f}"
            )

        # 交易逻辑
        if cross_over:
            self._handle_buy_signal(bar)
        elif cross_below:
            self._handle_sell_signal(bar)

        self.put_event()

    def _ma_cross_deadband(self, price: float) -> float:
        """Return MA spread threshold required for a valid cross signal."""
        runtime_config = getattr(self, "runtime_config", {})
        deadband_abs = float(runtime_config.get("ma_cross_deadband_abs", 0) or 0)
        deadband_pct = float(runtime_config.get("ma_cross_deadband_pct", 0.0002) or 0)
        pct_threshold = abs(price) * deadband_pct if price else 0
        return max(deadband_abs, pct_threshold, 0.0)

    @staticmethod
    def _is_near_cross(previous_spread: float, current_spread: float, threshold: float) -> bool:
        """Return true when MA spreads changed sign but stayed inside the deadband."""
        crossed_direction = (
            previous_spread <= 0 <= current_spread
            or previous_spread >= 0 >= current_spread
        )
        inside_band = abs(previous_spread) < threshold or abs(current_spread) < threshold
        return crossed_direction and inside_band

    def _handle_buy_signal(self, bar: BarData):
        """处理买入信号"""
        if self.pos == 0:
            self._send_trade_request(bar, "买入做多", 1, 0)
        elif self.pos < 0:
            self._send_trade_request(bar, "平空开多", 1, 2)  # 平空仓+开多仓

    def _handle_sell_signal(self, bar: BarData):
        """处理卖出信号"""
        if self.pos == 0:
            self._send_trade_request(bar, "卖出做空", -1, 0)
        elif self.pos > 0:
            self._send_trade_request(bar, "平多开空", -1, 2)  # 平多仓+开空仓

    def _send_trade_request(
        self, bar: BarData, direction_str: str, direction: int, volume_multiplier: int
    ):
        """
        发送交易请求等待确认

        Args:
            bar: 当前K线
            direction_str: 交易方向描述
            direction: 1为买入，-1为卖出
            volume_multiplier: 成交量倍数（平仓+开仓时为2）
        """
        self.trade_counter += 1
        trade_id = f"TRADE_{self.trade_counter:04d}"
        if self.pending_trade_request:
            self.write_log(f"已有待处理交易请求，跳过新信号 #{trade_id}")
            return

        cooldown_seconds = int(self.runtime_config.get("signal_cooldown_seconds", 300) or 0)
        last_signal = self.last_signal_at.get(direction)
        if cooldown_seconds > 0 and last_signal is not None:
            elapsed = (bar.datetime - last_signal).total_seconds()
            if 0 <= elapsed < cooldown_seconds:
                self.write_log(
                    f"同方向信号冷却中，跳过 #{trade_id}: "
                    f"{elapsed:.0f}s < {cooldown_seconds}s"
                )
                return

        reversal_cooldown_seconds = int(
            self.runtime_config.get("reversal_cooldown_seconds", cooldown_seconds) or 0
        )
        last_any_signal = getattr(self, "last_any_signal_at", None)
        last_direction = getattr(self, "last_signal_direction", None)
        if (
            reversal_cooldown_seconds > 0
            and last_any_signal is not None
            and last_direction is not None
            and last_direction != direction
        ):
            elapsed = (bar.datetime - last_any_signal).total_seconds()
            if 0 <= elapsed < reversal_cooldown_seconds:
                self.write_log(
                    f"反向信号冷却中，跳过 #{trade_id}: "
                    f"{elapsed:.0f}s < {reversal_cooldown_seconds}s, "
                    f"last_direction={last_direction}, new_direction={direction}"
                )
                return

        open_volume = self._calc_dynamic_volume(bar.close_price)

        # 构建交易逻辑说明
        if direction > 0:
            logic = (
                f"🟢 金叉信号：快线({self.fast_ma0:.6f})上穿慢线({self.slow_ma0:.6f})\n"
                f"   前一根K线：快线{self.fast_ma1:.6f} < 慢线{self.slow_ma1:.6f}\n"
                f"   当前K线：快线{self.fast_ma0:.6f} > 慢线{self.slow_ma0:.6f}\n"
                f"   => 趋势向上，建议做多"
            )
        else:
            logic = (
                f"🔴 死叉信号：快线({self.fast_ma0:.6f})下穿慢线({self.slow_ma0:.6f})\n"
                f"   前一根K线：快线{self.fast_ma1:.6f} > 慢线{self.slow_ma1:.6f}\n"
                f"   当前K线：快线{self.fast_ma0:.6f} < 慢线{self.slow_ma0:.6f}\n"
                f"   => 趋势向下，建议做空"
            )

        signal_info = {
            "trade_id": trade_id,
            "strategy_name": self.strategy_name,
            "vt_symbol": self.vt_symbol,
            "timestamp": bar.datetime.strftime("%Y-%m-%d %H:%M:%S"),
            "params": {
                "fast_window": self.fast_window,
                "slow_window": self.slow_window,
            },
            "backtest": self.backtest_report,
            "logic": logic,
            "direction": direction_str,
            "price": bar.close_price,
            "volume": open_volume * (volume_multiplier if volume_multiplier > 0 else 1),
            "current_pos": self.pos,
            "leverage": self.trading_config.get("leverage", 1),
            "position_ratio": self.trading_config.get("position_ratio", 0.05),
            "sizing_mode": self.trading_config.get("sizing_mode", "available_percent"),
            "notional": bar.close_price * open_volume,
            "risk_cap": self._risk_notional_cap(),
            "stop_loss_pct": self.trading_config.get("stop_loss_pct", 5.0),
            "take_profit_pct": self.trading_config.get("take_profit_pct", 10.0),
        }

        # Dispatch approval request non-blocking: on_bar runs on the vnpy event
        # thread, so we must not drive Telegram via a synchronous run_until_complete
        # (that would freeze market data + order callbacks).
        telegram_loop = getattr(self.telegram, "loop", None) if self.telegram else None
        if self.telegram and telegram_loop is not None:
            self.write_log(f"📱 发送交易请求 #{trade_id} 等待确认 (异步)...")
            self.pending_trade_request = True
            self.last_signal_at[direction] = bar.datetime
            self.last_any_signal_at = bar.datetime
            self.last_signal_direction = direction

            future = asyncio.run_coroutine_threadsafe(
                self.telegram.send_trade_signal(trade_id, signal_info),
                telegram_loop,
            )

            def _on_result(fut, bar=bar, direction=direction,
                           volume_multiplier=volume_multiplier, trade_id=trade_id):
                try:
                    approved = fut.result()
                except Exception as exc:  # noqa: BLE001
                    self.write_log(f"Telegram确认失败: {exc!r}，跳过交易 #{trade_id}")
                    self.pending_trade_request = False
                    return
                try:
                    if approved:
                        self.write_log(f"✅ 交易 #{trade_id} 已确认，执行交易")
                        self._execute_trade(bar, direction, volume_multiplier, open_volume)
                    else:
                        self.write_log(f"❌ 交易 #{trade_id} 被拒绝或超时")
                finally:
                    self.pending_trade_request = False

            future.add_done_callback(_on_result)
        else:
            self.write_log(
                f"⚠️ Telegram未就绪 (loop={telegram_loop!r})，跳过交易 #{trade_id}"
            )
            return

    def _account_equity(self) -> float:
        """Return the configured base-currency available balance for sizing."""
        main_engine = getattr(getattr(self, "cta_engine", None), "main_engine", None)
        if main_engine is None:
            return 0.0

        risk_config = getattr(self, "risk_config", {})
        account_currency = str(risk_config.get("account_currency", "USDT")).upper()
        try:
            accounts = list(main_engine.get_all_accounts())
        except Exception:
            return 0.0

        for account in accounts:
            if str(getattr(account, "accountid", "")).upper() == account_currency:
                return float(getattr(account, "available", getattr(account, "balance", 0)) or 0)
        return 0.0

    def _risk_notional_cap(self) -> float:
        """Return the most conservative configured per-order notional cap."""
        caps: list[float] = []
        risk_config = getattr(self, "risk_config", {})
        max_order_value = float(risk_config.get("max_order_value_usdt", 0) or 0)
        if max_order_value > 0:
            caps.append(max_order_value)

        max_order_pct = float(risk_config.get("max_order_value_pct", 0) or 0)
        equity = self._account_equity()
        if max_order_pct > 0 and equity > 0:
            caps.append(equity * max_order_pct)

        return min(caps) if caps else 0.0

    def _calc_dynamic_volume(self, price: float) -> float:
        """
        Return an open-side volume based on available balance × position_ratio × leverage.

        Fallback to trading_config["trade_quantity"] if we can't reach the main engine
        or there is no account data yet (e.g. backtest or pre-connect).
        """
        fallback = float(self.trading_config.get("trade_quantity", 1))

        main_engine = getattr(getattr(self, "cta_engine", None), "main_engine", None)
        if main_engine is None or price <= 0:
            return fallback

        equity = self._account_equity()
        if equity <= 0:
            return fallback

        leverage = float(self.trading_config.get("leverage", 1) or 1)
        position_ratio = float(self.trading_config.get("position_ratio", 0.05) or 0.05)

        contract = main_engine.get_contract(self.vt_symbol)
        contract_size = float(getattr(contract, "size", 1) or 1)
        min_volume = float(getattr(contract, "min_volume", 1) or 1)

        target_notional = equity * position_ratio * leverage
        risk_cap = self._risk_notional_cap()
        if risk_cap > 0:
            target_notional = min(target_notional, risk_cap)

        raw_volume = target_notional / (price * contract_size)
        if min_volume > 0:
            raw_volume = floor(raw_volume / min_volume) * min_volume
            if raw_volume <= 0:
                raw_volume = min_volume
        return raw_volume if raw_volume > 0 else fallback

    def _execute_trade(
        self,
        bar: BarData,
        direction: int,
        volume_multiplier: int,
        open_volume: float | None = None,
    ):
        """Close opposite pos (if any) then open new pos using dynamic sizing."""
        if open_volume is None:
            open_volume = self._calc_dynamic_volume(bar.close_price)

        if direction > 0:  # 买入
            if self.pos < 0:
                self.cover(bar.close_price, abs(self.pos))
            self.buy(bar.close_price, open_volume)
        else:  # 卖出
            if self.pos > 0:
                self.sell(bar.close_price, abs(self.pos))
            self.short(bar.close_price, open_volume)

    def on_trade(self, trade: TradeData) -> None:
        """成交回调"""
        self.write_log(f"📝 成交: {trade.direction.value} {trade.volume}@{trade.price}")
        self.put_event()

        # 发送成交通知
        # Telegram order lifecycle notifications are emitted from on_order()
        # only, so trade/order callbacks cannot arrive out of order in chat.

    def on_order(self, order: OrderData) -> None:
        """委托回调"""
        self.write_log(
            f"📨 委托: {order.status.value} {order.direction.value if order.direction else ''} "
            f"{order.volume}@{order.price}"
        )
        if not self.telegram:
            return

        terminal_statuses = {Status.ALLTRADED, Status.CANCELLED, Status.REJECTED}
        if order.status not in terminal_statuses:
            return

        if order.status == Status.ALLTRADED:
            title = "✅ <b>交易成交</b>"
        elif order.status == Status.CANCELLED:
            title = "↩️ <b>委托已撤销</b>"
        else:
            title = "❌ <b>委托拒单</b>"

        self._submit_telegram_message(
            f"{title}\n"
            f"状态: {order.status.value}\n"
            f"方向: {order.direction.value if order.direction else ''}\n"
            f"价格: {order.price:.6f}\n"
            f"数量: {order.volume}"
        )

    def on_stop_order(self, stop_order: StopOrder) -> None:
        """停止单回调"""
        pass
