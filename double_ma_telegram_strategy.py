"""
DoubleMA策略的Telegram确认版本
在发出交易信号时会等待Telegram确认
"""

import numpy as np
import asyncio
from datetime import datetime

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

from telegram_notifier import TelegramTradeBot


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
        self.telegram: TelegramTradeBot = None
        self.backtest_report: dict = {}
        self.trade_counter: int = 0
        self.trading_config: dict = {}

        try:
            import json
            from pathlib import Path

            config_path = Path(__file__).parent / "config" / "trading_config.json"
            with open(config_path, "r") as f:
                full_config = json.load(f)
                self.trading_config = full_config.get(
                    "trading",
                    {
                        "leverage": 1,
                        "position_ratio": 0.9,
                        "trade_quantity": 1,
                        "max_position": 100,
                        "stop_loss_pct": 5.0,
                        "take_profit_pct": 10.0,
                    },
                )
        except Exception as e:
            self.write_log(f"加载交易配置失败: {e}，使用默认参数")
            self.trading_config = {
                "leverage": 1,
                "position_ratio": 0.9,
                "trade_quantity": 1,
                "max_position": 100,
                "stop_loss_pct": 5.0,
                "take_profit_pct": 10.0,
            }

        # 初始化Telegram
        try:
            self.telegram = TelegramTradeBot("config/trading_config.json")
        except Exception as e:
            self.write_log(f"Telegram初始化失败: {e}")
            self.telegram = None

    def on_init(self) -> None:
        """策略初始化"""
        self.write_log("策略初始化 - DoubleMA with Telegram确认")

        self.bg = BarGenerator(self.on_bar)
        self.am = ArrayManager()

        # 加载历史数据用于计算均线
        self.load_bar(10)

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
            try:
                import asyncio

                asyncio.create_task(
                    self.telegram.send_message(
                        f"✅ <b>DoubleMA策略已启动</b>\n"
                        f"品种: {self.vt_symbol}\n"
                        f"参数: 快线={self.fast_window}, 慢线={self.slow_window}\n"
                        f"等待交易信号..."
                    )
                )
            except Exception as e:
                self.write_log(f"发送启动通知失败: {e}")

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

        # 判断金叉/死叉
        cross_over: bool = (
            self.fast_ma0 > self.slow_ma0 and self.fast_ma1 < self.slow_ma1
        )
        cross_below: bool = (
            self.fast_ma0 < self.slow_ma0 and self.fast_ma1 > self.slow_ma1
        )

        # 交易逻辑
        if cross_over:
            self._handle_buy_signal(bar)
        elif cross_below:
            self._handle_sell_signal(bar)

        self.put_event()

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

        # 构建交易逻辑说明
        if direction > 0:
            logic = (
                f"🟢 金叉信号：快线({self.fast_ma0:.2f})上穿慢线({self.slow_ma0:.2f})\n"
                f"   前一根K线：快线{self.fast_ma1:.2f} < 慢线{self.slow_ma1:.2f}\n"
                f"   当前K线：快线{self.fast_ma0:.2f} > 慢线{self.slow_ma0:.2f}\n"
                f"   => 趋势向上，建议做多"
            )
        else:
            logic = (
                f"🔴 死叉信号：快线({self.fast_ma0:.2f})下穿慢线({self.slow_ma0:.2f})\n"
                f"   前一根K线：快线{self.fast_ma1:.2f} > 慢线{self.slow_ma1:.2f}\n"
                f"   当前K线：快线{self.fast_ma0:.2f} < 慢线{self.slow_ma0:.2f}\n"
                f"   => 趋势向下，建议做空"
            )

        quantity = self.trading_config.get("trade_quantity", 1)

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
            "volume": quantity * (volume_multiplier if volume_multiplier > 0 else 1),
            "current_pos": self.pos,
            "leverage": self.trading_config.get("leverage", 1),
            "position_ratio": self.trading_config.get("position_ratio", 0.9),
            "stop_loss_pct": self.trading_config.get("stop_loss_pct", 5.0),
            "take_profit_pct": self.trading_config.get("take_profit_pct", 10.0),
        }

        # 发送到Telegram等待确认
        if self.telegram:
            self.write_log(f"📱 发送交易请求 #{trade_id} 等待确认...")

            try:
                import asyncio

                # 创建新的事件循环来运行异步函数
                loop = asyncio.new_event_loop()
                asyncio.set_event_loop(loop)
                approved = loop.run_until_complete(
                    self.telegram.send_trade_signal(trade_id, signal_info)
                )
                loop.close()

                if approved:
                    self.write_log(f"✅ 交易 #{trade_id} 已确认，执行交易")
                    self._execute_trade(bar, direction, volume_multiplier)
                else:
                    self.write_log(f"❌ 交易 #{trade_id} 被拒绝或超时")

            except Exception as e:
                self.write_log(f"Telegram确认失败: {e}，自动执行交易")
                self._execute_trade(bar, direction, volume_multiplier)
        else:
            # 没有Telegram时直接执行
            self.write_log(f"⚠️ Telegram未配置，直接执行交易 #{trade_id}")
            self._execute_trade(bar, direction, volume_multiplier)

    def _execute_trade(self, bar: BarData, direction: int, volume_multiplier: int):
        """执行交易"""
        quantity = self.trading_config.get("trade_quantity", 1)
        volume = quantity * (volume_multiplier if volume_multiplier > 0 else 1)

        if direction > 0:  # 买入
            if self.pos < 0:  # 先平仓
                self.cover(bar.close_price, abs(self.pos))
            self.buy(bar.close_price, volume)
        else:  # 卖出
            if self.pos > 0:  # 先平仓
                self.sell(bar.close_price, abs(self.pos))
            self.short(bar.close_price, volume)

    def on_trade(self, trade: TradeData) -> None:
        """成交回调"""
        self.write_log(f"📝 成交: {trade.direction.value} {trade.volume}@{trade.price}")
        self.put_event()

        # 发送成交通知
        if self.telegram:
            try:
                import asyncio

                msg = (
                    f"✅ <b>交易成交</b>\n"
                    f"方向: {trade.direction.value}\n"
                    f"价格: {trade.price:.2f}\n"
                    f"数量: {trade.volume}\n"
                    f"时间: {trade.datetime}"
                )
                asyncio.create_task(self.telegram.send_message(msg))
            except:
                pass

    def on_order(self, order: OrderData) -> None:
        """委托回调"""
        pass

    def on_stop_order(self, stop_order: StopOrder) -> None:
        """停止单回调"""
        pass
