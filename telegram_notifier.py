"""
Telegram交易确认机器人
处理交易前的确认、推送通知、每日报告
"""

import asyncio
from concurrent.futures import Future
from html import escape
from typing import Optional
from telegram import Bot, Update
from telegram.ext import (
    Application,
    CommandHandler,
    ContextTypes,
)

from trading_config import load_trading_config


class TelegramTradeBot:
    """Telegram交易确认机器人"""

    def __init__(self, config_path: str = "config/trading_config.json"):
        """初始化"""
        config = load_trading_config(config_path)

        self.bot_token = config["telegram"]["bot_token"]
        self.chat_id = config["telegram"]["chat_id"]
        self.mode = config.get("notification", {}).get("mode", "")
        self.approval_enabled = config["approval"]["enabled"]
        if not self.mode:
            self.mode = "approval_required" if self.approval_enabled else "notify_only"
        self.timeout = config["approval"]["timeout_seconds"]

        self.bot = Bot(token=self.bot_token)
        self.pending_approvals: dict[str, dict] = {}
        # Per-trade asyncio.Event so handlers resolve approvals instantly instead
        # of polling once per second.
        self.approval_events: dict[str, asyncio.Event] = {}
        self.approval_results: dict[str, bool] = {}
        # Set inside start() so strategies on other threads can schedule work via
        # asyncio.run_coroutine_threadsafe(coro, bot.loop).
        self.loop: Optional[asyncio.AbstractEventLoop] = None
        self.application: Application | None = None
        self.polling: bool = False

    async def start(self):
        """启动机器人"""
        self.loop = asyncio.get_running_loop()

        self.application = Application.builder().token(self.bot_token).build()

        # 注册命令处理器
        self.application.add_handler(CommandHandler("start", self.cmd_start))
        self.application.add_handler(CommandHandler("status", self.cmd_status))
        self.application.add_handler(CommandHandler("approve", self.cmd_approve))
        self.application.add_handler(CommandHandler("reject", self.cmd_reject))
        self.application.add_handler(
            CommandHandler("disable_approval", self.cmd_disable_approval)
        )
        self.application.add_handler(
            CommandHandler("enable_approval", self.cmd_enable_approval)
        )

        # 启动
        await self.application.initialize()
        await self.application.start()
        if self.mode == "approval_required" and self.application.updater:
            await self.application.updater.start_polling()
            self.polling = True

        # 发送启动通知
        await self.send_message("🚀 自动交易系统已启动！\n发送 /status 查看当前状态")

    async def stop(self):
        """停止机器人"""
        if self.application:
            await self.send_message("🛑 自动交易系统已停止")
            if self.polling and self.application.updater:
                await self.application.updater.stop()
                self.polling = False
            await self.application.stop()
            await self.application.shutdown()

    def submit_message(self, message: str) -> Future:
        """Schedule a message from non-async vn.py callback threads."""
        if self.loop is None:
            raise RuntimeError("Telegram bot loop is not running")
        return asyncio.run_coroutine_threadsafe(self.send_message(message), self.loop)

    async def cmd_start(self, update: Update, context: ContextTypes.DEFAULT_TYPE):
        """/start 命令"""
        welcome_msg = """
🤖 自动交易确认机器人

可用命令：
/status - 查看策略状态
/approve [id] - 确认交易
/reject [id] - 拒绝交易
/disable_approval - 关闭人工确认
/enable_approval - 开启人工确认

当策略发出交易信号时，我会推送详细信息给你确认。
        """
        await update.message.reply_text(welcome_msg)

    async def cmd_status(self, update: Update, context: ContextTypes.DEFAULT_TYPE):
        """/status 命令"""
        status = (
            "✅ 人工确认已开启" if self.approval_enabled else "⚡ 自动模式（无需确认）"
        )
        await update.message.reply_text(f"当前状态：{status}")

    def _resolve_approval(self, trade_id: str, approved: bool) -> bool:
        event = self.approval_events.get(trade_id)
        if event is None:
            return False
        self.approval_results[trade_id] = approved
        event.set()
        return True

    async def cmd_approve(self, update: Update, context: ContextTypes.DEFAULT_TYPE):
        """/approve 命令"""
        try:
            trade_id = context.args[0] if context.args else None
            if trade_id:
                if self._resolve_approval(trade_id, True):
                    await update.message.reply_text(f"✅ 已确认交易 #{trade_id}")
                else:
                    await update.message.reply_text(
                        f"⚠️ 没有找到待确认的交易 #{trade_id}（可能已超时或已处理）"
                    )
            else:
                resolved = [tid for tid in list(self.approval_events) if self._resolve_approval(tid, True)]
                await update.message.reply_text(
                    f"✅ 已确认 {len(resolved)} 笔待处理交易"
                )
        except Exception as e:
            await update.message.reply_text(f"❌ 确认失败: {e}")

    async def cmd_reject(self, update: Update, context: ContextTypes.DEFAULT_TYPE):
        """/reject 命令"""
        try:
            trade_id = context.args[0] if context.args else None
            if trade_id:
                if self._resolve_approval(trade_id, False):
                    await update.message.reply_text(f"❌ 已拒绝交易 #{trade_id}")
                else:
                    await update.message.reply_text(
                        f"⚠️ 没有找到待确认的交易 #{trade_id}"
                    )
            else:
                resolved = [tid for tid in list(self.approval_events) if self._resolve_approval(tid, False)]
                await update.message.reply_text(
                    f"❌ 已拒绝 {len(resolved)} 笔待处理交易"
                )
        except Exception as e:
            await update.message.reply_text(f"❌ 拒绝失败: {e}")

    async def cmd_disable_approval(
        self, update: Update, context: ContextTypes.DEFAULT_TYPE
    ):
        """关闭人工确认"""
        self.approval_enabled = False
        await update.message.reply_text("⚡ 已切换到自动模式（无需人工确认）")

    async def cmd_enable_approval(
        self, update: Update, context: ContextTypes.DEFAULT_TYPE
    ):
        """开启人工确认"""
        self.approval_enabled = True
        await update.message.reply_text("✅ 已开启人工确认模式")

    async def send_message(self, message: str):
        """发送消息"""
        try:
            await self.bot.send_message(
                chat_id=self.chat_id, text=message, parse_mode="HTML"
            )
        except Exception as e:
            print(f"发送Telegram消息失败: {e}")

    async def send_trade_signal(self, trade_id: str, signal_info: dict) -> bool:
        """
        发送交易信号请求确认

        Args:
            trade_id: 交易ID
            signal_info: 信号详细信息

        Returns:
            True if approved, False if rejected or timed out
        """
        msg = self._format_trade_message(signal_info)
        if self.mode == "notify_only" or not self.approval_enabled:
            await self.send_message(msg)
            return True

        if self.mode != "approval_required":
            return True

        self.pending_approvals[trade_id] = signal_info
        self.approval_events[trade_id] = asyncio.Event()
        self.approval_results.pop(trade_id, None)
        try:
            await self.send_message(msg)
            return await self._wait_for_approval(trade_id)
        finally:
            self.pending_approvals.pop(trade_id, None)
            self.approval_events.pop(trade_id, None)
            self.approval_results.pop(trade_id, None)

    def _format_trade_message(self, info: dict) -> str:
        """格式化交易消息"""
        direction = str(info.get("direction", ""))
        emoji = "🟢" if direction.startswith("买入") or direction.startswith("平空") else "🔴"
        backtest = info.get("backtest") or {}

        msg = f"""
{emoji} <b>交易信号</b> #{escape(str(info["trade_id"]))}

📊 <b>策略信息</b>
├ 策略: {escape(str(info["strategy_name"]))}
├ 品种: {escape(str(info["vt_symbol"]))}
└ 时间: {escape(str(info["timestamp"]))}

⚙️ <b>当前参数</b>
├ 快线: {info["params"]["fast_window"]}
└ 慢线: {info["params"]["slow_window"]}

📈 <b>回测表现</b>
├ 总收益: {backtest.get("total_return", 0)}%
├ 夏普比率: {backtest.get("sharpe_ratio", 0)}
├ 最大回撤: {backtest.get("max_drawdown", 0)}%
└ 胜率: {backtest.get("win_rate", 0)}%

💡 <b>交易逻辑</b>
{escape(str(info["logic"]))}

🎯 <b>交易详情</b>
├ 方向: {escape(direction)}
├ 价格: {info["price"]:.6f} USDT
├ 数量: {info["volume"]} 张
├ 杠杆: {info.get("leverage", 1)}x
├ 仓位比例: {info.get("position_ratio", 0.9) * 100:.0f}%
├ 目标名义金额: {info.get("notional", info["price"] * info["volume"]):.2f} USDT
├ 风控上限: {info.get("risk_cap", 0):.2f} USDT
├ 预估保证金: {(info["price"] * info["volume"] / info.get("leverage", 1)):.2f} USDT
└ 当前持仓: {info["current_pos"]} 张

⚠️ <b>风险提示</b>
├ 止损: {info.get("stop_loss_pct", 5.0)}%
└ 止盈: {info.get("take_profit_pct", 10.0)}%
        """
        if self.mode == "approval_required" and self.approval_enabled:
            msg += (
                f"\n回复 /approve {info['trade_id']} 确认"
                f"\n回复 /reject {info['trade_id']} 拒绝"
            )
        else:
            msg += "\n通知模式：该信号发送后自动进入交易流程。"
        return msg

    async def _wait_for_approval(self, trade_id: str) -> bool:
        """等待用户确认 - event-driven, no polling."""
        event = self.approval_events.get(trade_id)
        if event is None:
            return False
        try:
            await asyncio.wait_for(event.wait(), timeout=self.timeout)
        except asyncio.TimeoutError:
            await self.send_message(f"⏱ 交易 #{trade_id} 超时未确认，已取消")
            return False

        approved = bool(self.approval_results.get(trade_id, False))
        if approved:
            await self.send_message(f"✅ 交易 #{trade_id} 已执行")
        else:
            await self.send_message(f"❌ 交易 #{trade_id} 已取消")
        return approved

    async def send_daily_report(self, report: dict):
        """发送每日报告"""
        msg = f"""
📊 <b>每日交易报告</b> {report["date"]}

📈 <b>总体表现</b>
├ 初始资金: {report["initial_capital"]:,} USDT
├ 当前资金: {report["current_capital"]:,} USDT
├ 当日盈亏: {report["daily_pnl"]:+.2f} USDT ({report["daily_return"]:+.2f}%)
└ 总收益率: {report["total_return"]:+.2f}%

📝 <b>今日成交</b>
├ 成交次数: {report["trade_count"]}
├ 盈利次数: {report["win_count"]}
├ 亏损次数: {report["loss_count"]}
└ 胜率: {report["win_rate"]:.1f}%

💼 <b>当前持仓</b>
├ 品种: {report["positions"]}
└ 策略状态: {"运行中" if report["strategy_running"] else "已停止"}

⏰ 报告时间: {report["report_time"]}
        """
        await self.send_message(msg)
