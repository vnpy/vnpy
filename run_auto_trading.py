"""
自动交易系统主程序（OKX模拟盘 + Telegram确认）
支持DoubleMA策略，带详细回测报告
"""

import asyncio
import json
import os
import signal
import time
import traceback
from datetime import datetime, timedelta
from pathlib import Path
from typing import Any

from vnpy.event import EventEngine
from vnpy.event import Event
from vnpy.trader.engine import MainEngine
from vnpy.trader.engine_risk import RiskEngine
from vnpy.trader.object import SubscribeRequest
from vnpy.trader.setting import SETTINGS
from vnpy.trader.constant import Interval
from vnpy.trader.event import EVENT_ACCOUNT, EVENT_LOG, EVENT_ORDER, EVENT_TICK, EVENT_TRADE
from vnpy.trader.utility import extract_vt_symbol, get_file_path

from vnpy_okx import OkxGateway
from vnpy_ctastrategy import CtaStrategyApp
from vnpy_ctastrategy.strategies.double_ma_strategy import DoubleMaStrategy
from vnpy_ctastrategy.strategies.chan_strategy import ChanStrategy

from double_ma_telegram_strategy import DoubleMATelegramStrategy
from telegram_notifier import TelegramTradeBot, format_strategy_signal_message
from trading_config import load_trading_config, resolve_trading_config_path


TELEGRAM_STRATEGY_CLASS_NAME = "DoubleMATelegramStrategy"
CHAN_STRATEGY_CLASS_NAME = "ChanStrategy"
STRATEGY_NAME = "DoubleMA_Auto"
GATEWAY_NAME = "OKX"
STATE_FILENAME = "okx_auto_state.json"
PID_FILENAME = "okx_auto_trading.pid"


def apply_risk_settings(config: dict[str, Any]) -> None:
    """Overlay trading-config risk keys into vn.py global runtime settings."""
    for key, value in config.get("risk", {}).items():
        SETTINGS[f"risk.{key}"] = value


def build_okx_connect_config(
    okx_config: dict[str, Any] | None,
    app_config: dict[str, Any],
) -> tuple[dict[str, Any], bool]:
    """Build OkxGateway setting dict from private or app config."""
    if okx_config:
        server = okx_config.get("Server", "DEMO")
        return (
            {
                "API Key": okx_config["API Key"],
                "Secret Key": okx_config["Secret Key"],
                "Passphrase": okx_config["Passphrase"],
                "Server": server,
                "Proxy Host": okx_config.get("Proxy Host", ""),
                "Proxy Port": int(okx_config.get("Proxy Port", 0) or 0),
                "Spread Trading": okx_config.get("Spread Trading", "False"),
                "Margin Currency": okx_config.get("Margin Currency", ""),
            },
            server == "DEMO",
        )

    if "okx" not in app_config:
        raise RuntimeError(
            "OKX config missing: create ~/.vntrader/connect_okx.json or add okx settings"
        )

    cfg = app_config["okx"]
    simulated = bool(cfg.get("use_simulated", True))
    return (
        {
            "API Key": cfg["api_key"],
            "Secret Key": cfg["api_secret"],
            "Passphrase": cfg["passphrase"],
            "Server": "DEMO" if simulated else "REAL",
            "Proxy Host": cfg.get("proxy", ""),
            "Proxy Port": int(cfg.get("proxy_port", 0) or 0),
            "Spread Trading": cfg.get("spread_trading", "False"),
            "Margin Currency": cfg.get("margin_currency", ""),
        },
        simulated,
    )


def is_strategy_config_match(
    strategy: Any,
    class_name: str,
    vt_symbol: str,
    setting: dict[str, Any],
) -> bool:
    """Return whether an existing CTA strategy matches desired runtime config."""
    current_setting = (
        strategy.get_parameters()
        if hasattr(strategy, "get_parameters")
        else getattr(strategy, "setting", setting)
    )
    return (
        strategy.__class__.__name__ == class_name
        and getattr(strategy, "vt_symbol", "") == vt_symbol
        and current_setting == setting
    )


def get_strategy_spec(config: dict[str, Any]) -> dict[str, Any]:
    """Return normalized managed strategy config."""
    strategy_config = config["strategy"]
    return {
        "class_name": strategy_config.get("class_name", TELEGRAM_STRATEGY_CLASS_NAME),
        "strategy_name": strategy_config.get("strategy_name", STRATEGY_NAME),
        "vt_symbol": strategy_config["vt_symbol"],
        "setting": strategy_config.get("setting", {}),
    }


def validate_strategy_safety(config: dict[str, Any]) -> None:
    """Reject unsafe auto-trading strategy configurations."""
    spec = get_strategy_spec(config)
    if spec["class_name"] != CHAN_STRATEGY_CLASS_NAME:
        return

    setting = spec["setting"]
    if not bool(setting.get("trade_enabled", True)):
        return

    risk_config = config.get("risk", {})
    if not risk_config.get("enabled", False):
        raise ValueError("ChanStrategy live trading requires risk.enabled=true")
    if float(setting.get("max_position", 0) or 0) <= 0:
        raise ValueError("ChanStrategy live trading requires setting.max_position")
    if float(risk_config.get("max_order_value_usdt", 0) or 0) <= 0:
        raise ValueError("ChanStrategy live trading requires risk.max_order_value_usdt")
    if float(risk_config.get("max_daily_loss_pct", 0) or 0) <= 0:
        raise ValueError("ChanStrategy live trading requires risk.max_daily_loss_pct")

    sizing_mode = str(setting.get("sizing_mode", "fixed"))
    if sizing_mode == "risk_per_trade":
        if float(setting.get("risk_per_trade", 0) or 0) <= 0:
            raise ValueError("ChanStrategy risk_per_trade sizing requires setting.risk_per_trade")
    elif sizing_mode == "target_ratio":
        if float(setting.get("target_long_ratio", 0) or 0) <= 0:
            raise ValueError("ChanStrategy target_ratio sizing requires setting.target_long_ratio")


def format_strategy_label(strategy_config: dict[str, Any]) -> str:
    """Return a human-readable strategy label for reports."""
    class_name = strategy_config.get("class_name", "DoubleMA")
    setting = strategy_config.get("setting", {})
    if class_name in {"DoubleMA", TELEGRAM_STRATEGY_CLASS_NAME}:
        return (
            f"DoubleMA (快线={setting.get('fast_window', '-')}, "
            f"慢线={setting.get('slow_window', '-')})"
        )
    return f"{class_name} ({setting})"


def build_strategy_signal_key(signal: dict[str, Any]) -> str:
    """Return a stable key for deduplicating strategy signal notifications."""
    if signal.get("signal_key"):
        return str(signal["signal_key"])

    return ":".join(
        str(signal.get(key, ""))
        for key in ("type", "confirmed_index", "bar_datetime")
    )


def build_backtest_strategy_setting(
    strategy_config: dict[str, Any],
    backtest_config: dict[str, Any],
) -> dict[str, Any]:
    """Return strategy settings for backtest without weakening runtime safety."""
    setting = dict(strategy_config.get("setting", {}))
    if "trade_enabled" in setting:
        setting["trade_enabled"] = bool(backtest_config.get("trade_enabled", True))
    return setting


def get_backtest_period(
    backtest_config: dict[str, Any],
    end: datetime | None = None,
) -> tuple[datetime, datetime]:
    """Return configured backtest start and end datetimes."""
    end_dt = end or datetime.now()
    days = int(backtest_config.get("days", 90))
    return end_dt - timedelta(days=days), end_dt


class AutoTradingSystem:
    """自动交易系统"""

    def __init__(
        self,
        config_path: str = None,
        okx_config_path: str | Path | None = None,
    ):
        """初始化系统"""
        if okx_config_path is None:
            okx_config_path = get_file_path("connect_okx.json")

        if config_path is None:
            script_dir = Path(__file__).parent.absolute()
            config_path = script_dir / "config" / "trading_config.json"
        else:
            config_path = Path(config_path)

        config_path = resolve_trading_config_path(config_path).resolve()
        self.config_path = config_path
        print(f"📂 加载配置文件: {config_path}")

        # 加载配置
        self.config = load_trading_config(config_path)
        validate_strategy_safety(self.config)
        apply_risk_settings(self.config)

        self.okx_config_path = okx_config_path
        if Path(okx_config_path).exists():
            with open(okx_config_path, "r") as f:
                self.okx_config = json.load(f)
            print(f"✅ 已从 {okx_config_path} 加载OKX配置")
        else:
            print(f"⚠️ 未找到OKX配置文件: {okx_config_path}，使用config中的配置")
            self.okx_config = None

        # 初始化事件引擎
        self.event_engine = EventEngine()
        self.main_engine = MainEngine(self.event_engine)
        self.state_path = get_file_path(STATE_FILENAME)
        self.pid_path = get_file_path(PID_FILENAME)
        self.contract_timeout = float(self.config.get("runtime", {}).get("contract_timeout", 30))
        self.tick_timeout = float(self.config.get("runtime", {}).get("tick_timeout", 30))
        self.init_timeout = float(self.config.get("runtime", {}).get("init_timeout", 60))
        self.state: dict[str, Any] = {
            "pid": os.getpid(),
            "started_at": datetime.now().astimezone().isoformat(),
            "okx_server": "",
            "simulated": None,
            "contract_ready": False,
            "strategy_name": get_strategy_spec(self.config)["strategy_name"],
            "strategy_class": get_strategy_spec(self.config)["class_name"],
            "strategy_inited": False,
            "strategy_trading": False,
            "strategy_trade_enabled": get_strategy_spec(self.config)["setting"].get("trade_enabled", True),
            "latest_chan_signal": {},
            "latest_tick_ts": "",
            "latest_order_ts": "",
            "latest_trade_ts": "",
            "latest_account_ts": "",
            "latest_error": "",
            "risk": {},
        }
        # 注册风控引擎（熔断）——必须在 CtaEngine 之前注册，保证 CtaEngine 能通过
        # main_engine.engines["risk"] 查到。
        self.risk_engine: RiskEngine = self.main_engine.add_engine(RiskEngine)
        self.register_state_handlers()
        self.pid_path.write_text(str(os.getpid()), encoding="utf-8")
        self.write_state()

        # 初始化Telegram机器人
        self.telegram = TelegramTradeBot(self.config_path)
        self.last_notified_strategy_signal_key = ""

        # 交易计数器
        self.trade_counter = 0
        self.daily_stats = {
            "date": datetime.now().strftime("%Y-%m-%d"),
            "trades": [],
            "initial_capital": self.config["backtest"]["capital"],
            "current_capital": self.config["backtest"]["capital"],
        }

    def setup_gateway(self):
        """配置交易接口"""
        connect_config, is_simulated = build_okx_connect_config(self.okx_config, self.config)
        self.state["okx_server"] = connect_config["Server"]
        self.state["simulated"] = is_simulated
        self.write_state()

        self.main_engine.add_gateway(OkxGateway)
        self.main_engine.connect(connect_config, GATEWAY_NAME)
        print(f"✅ 已连接到OKX {'模拟盘' if is_simulated else '实盘'}")

    def setup_strategy(self):
        """配置策略"""
        # 添加CTA策略模块
        self.main_engine.add_app(CtaStrategyApp)

        # 获取CTA引擎并初始化
        cta_engine = self.main_engine.get_engine("CtaStrategy")
        cta_engine.telegram_notifier = self.telegram
        cta_engine.classes[TELEGRAM_STRATEGY_CLASS_NAME] = DoubleMATelegramStrategy
        cta_engine.classes[CHAN_STRATEGY_CLASS_NAME] = ChanStrategy
        cta_engine.init_engine()

        # 策略配置 (配置文件中已使用正确的格式: DOGEUSDT_SWAP_OKX.GLOBAL)
        strategy_spec = get_strategy_spec(self.config)
        vt_symbol = strategy_spec["vt_symbol"]
        self.wait_for_contract(vt_symbol, timeout=self.contract_timeout)
        self.wait_for_gateway_api("public_api", timeout=self.contract_timeout)

        self.upsert_strategy(cta_engine)

        symbol, exchange = extract_vt_symbol(vt_symbol)
        req = SubscribeRequest(symbol=symbol, exchange=exchange)
        self.main_engine.subscribe(req, GATEWAY_NAME)

        print(f"✅ 策略已添加: {vt_symbol}")
        print(f"   策略: {strategy_spec['strategy_name']} ({strategy_spec['class_name']})")
        print(f"   参数: {strategy_spec['setting']}")

    def register_state_handlers(self) -> None:
        """Register handlers that persist process health state for schedulers."""
        self.event_engine.register(EVENT_TICK, self.process_state_event)
        self.event_engine.register(EVENT_ORDER, self.process_state_event)
        self.event_engine.register(EVENT_TRADE, self.process_state_event)
        self.event_engine.register(EVENT_ACCOUNT, self.process_state_event)
        self.event_engine.register(EVENT_LOG, self.process_state_event)

    def write_state(self) -> None:
        """Persist runtime state atomically enough for local health checks."""
        self.state_path.write_text(
            json.dumps(self.state, ensure_ascii=False, indent=2),
            encoding="utf-8",
        )

    def process_state_event(self, event: Event) -> None:
        """Update health state from vn.py events."""
        now = datetime.now().astimezone().isoformat()
        data = event.data
        if event.type.startswith(EVENT_TICK):
            if getattr(data, "vt_symbol", "") == get_strategy_spec(self.config)["vt_symbol"]:
                self.state["latest_tick_ts"] = now
                self.state["latest_price"] = getattr(data, "last_price", 0)
        elif event.type.startswith(EVENT_ORDER):
            self.state["latest_order_ts"] = now
            self.state["latest_order_status"] = getattr(getattr(data, "status", None), "value", "")
        elif event.type.startswith(EVENT_TRADE):
            self.state["latest_trade_ts"] = now
        elif event.type.startswith(EVENT_ACCOUNT):
            self.state["latest_account_ts"] = now
        elif event.type == EVENT_LOG:
            msg = getattr(data, "msg", "")
            if any(pattern in msg for pattern in ["failed", "失败", "Exception", "拒单", "Wrong", "Insufficient"]):
                self.state["latest_error"] = msg[:500]

        self.state["risk"] = self.risk_engine.snapshot()
        self.capture_strategy_state()
        self.write_state()

    def capture_strategy_state(self) -> None:
        """Persist strategy-specific observable state."""
        try:
            cta_engine = self.main_engine.get_engine("CtaStrategy")
            strategy_spec = get_strategy_spec(self.config)
            strategy_name = strategy_spec["strategy_name"]
            strategy = cta_engine.strategies.get(strategy_name)
        except Exception:  # noqa: BLE001
            return

        if not strategy:
            return

        self.state["strategy_trade_enabled"] = getattr(strategy, "trade_enabled", True)
        latest_signal = getattr(strategy, "latest_chan_signal", None)
        if latest_signal:
            self.state["latest_chan_signal"] = latest_signal
            self.notify_strategy_signal(
                strategy_name,
                strategy_spec["vt_symbol"],
                latest_signal,
            )

    def notify_strategy_signal(
        self,
        strategy_name: str,
        vt_symbol: str,
        latest_signal: dict[str, Any],
    ) -> None:
        """Send a deduplicated strategy signal notification from runtime scope."""
        signal_key = build_strategy_signal_key(latest_signal)
        if not signal_key or signal_key == self.last_notified_strategy_signal_key:
            return

        self.last_notified_strategy_signal_key = signal_key
        message = format_strategy_signal_message(strategy_name, vt_symbol, latest_signal)
        try:
            self.telegram.submit_message(message)
        except Exception as exc:  # noqa: BLE001
            self.state["latest_error"] = f"strategy signal notification failed: {exc}"

    def wait_for_contract(self, vt_symbol: str, timeout: float, interval: float = 0.2):
        """Wait until OKX contract metadata is available."""
        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            contract = self.main_engine.get_contract(vt_symbol)
            if contract:
                self.state["contract_ready"] = True
                self.write_state()
                return contract
            time.sleep(interval)
        self.state["latest_error"] = f"contract not ready: {vt_symbol}"
        self.write_state()
        raise TimeoutError(f"OKX contract not ready: {vt_symbol}")

    def wait_for_tick(self, vt_symbol: str, timeout: float, interval: float = 0.2) -> None:
        """Wait for first tick after subscription so startup is real, not cosmetic."""
        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            tick = self.main_engine.get_tick(vt_symbol)
            if tick:
                return
            time.sleep(interval)
        self.state["latest_error"] = f"tick not received: {vt_symbol}"
        self.write_state()
        raise TimeoutError(f"OKX tick not received: {vt_symbol}")

    def wait_for_gateway_api(
        self,
        api_name: str,
        timeout: float,
        interval: float = 0.2,
    ) -> None:
        """Wait until an OKX websocket API is connected before sending packets."""
        deadline = time.monotonic() + timeout
        while time.monotonic() < deadline:
            gateway = self.main_engine.get_gateway(GATEWAY_NAME)
            api = getattr(gateway, api_name, None) if gateway else None
            if getattr(api, "connected", False):
                return
            time.sleep(interval)

        self.state["latest_error"] = f"{api_name} not connected"
        self.write_state()
        raise TimeoutError(f"OKX {api_name} not connected")

    def upsert_strategy(self, cta_engine) -> None:
        """Create or replace the managed CTA strategy with desired settings."""
        strategy_spec = get_strategy_spec(self.config)
        strategy_name = strategy_spec["strategy_name"]
        class_name = strategy_spec["class_name"]
        vt_symbol = strategy_spec["vt_symbol"]
        setting = strategy_spec["setting"]
        existing = cta_engine.strategies.get(strategy_name)

        if existing and not is_strategy_config_match(
            existing,
            class_name,
            vt_symbol,
            setting,
        ):
            if getattr(existing, "trading", False):
                cta_engine.stop_strategy(strategy_name)
            if not cta_engine.remove_strategy(strategy_name):
                raise RuntimeError(f"failed to remove stale strategy {strategy_name}")
            existing = None

        if not existing:
            cta_engine.add_strategy(
                class_name=class_name,
                strategy_name=strategy_name,
                vt_symbol=vt_symbol,
                setting=setting,
            )

        strategy = cta_engine.strategies[strategy_name]
        if hasattr(strategy, "telegram"):
            strategy.telegram = self.telegram

    async def init_and_start_strategy(self) -> None:
        """Initialize and start strategy with explicit readiness checks."""
        cta_engine = self.main_engine.get_engine("CtaStrategy")
        strategy_name = get_strategy_spec(self.config)["strategy_name"]
        future = cta_engine.init_strategy(strategy_name)
        await asyncio.to_thread(future.result, self.init_timeout)

        strategy = cta_engine.strategies[strategy_name]
        if not strategy.inited:
            raise RuntimeError(f"{strategy_name} init did not complete")
        self.state["strategy_inited"] = True
        self.write_state()

        cta_engine.start_strategy(strategy_name)
        if not strategy.trading:
            raise RuntimeError(f"{strategy_name} did not start")
        self.state["strategy_trading"] = True
        self.write_state()

    async def run_backtest_report(self):
        """运行回测并生成报告"""
        from vnpy_ctastrategy.backtesting import BacktestingEngine

        print("\n📊 正在运行回测...")

        try:
            # 创建回测引擎
            engine = BacktestingEngine()

            strategy_config = self.config["strategy"]
            backtest_config = self.config["backtest"]
            backtest_strategy_setting = build_backtest_strategy_setting(
                strategy_config,
                backtest_config,
            )

            start_date, end_date = get_backtest_period(backtest_config)
            print(
                f"   回测周期: {start_date.strftime('%Y-%m-%d')} ~ {end_date.strftime('%Y-%m-%d')}"
            )

            # 设置参数
            vt_symbol_backtest = strategy_config["vt_symbol"]

            engine.set_parameters(
                vt_symbol=vt_symbol_backtest,
                interval=Interval.HOUR,
                start=start_date,
                end=end_date,
                rate=backtest_config.get("rate", 0.0005),
                slippage=backtest_config.get("slippage", 0.1),
                size=backtest_config.get("size", 1),
                pricetick=backtest_config.get("pricetick", 0.0001),
                capital=backtest_config["capital"],
            )

            # 添加策略
            strategy_class = (
                ChanStrategy
                if strategy_config.get("class_name") == CHAN_STRATEGY_CLASS_NAME
                else DoubleMaStrategy
            )
            engine.add_strategy(
                strategy_class=strategy_class,
                setting=backtest_strategy_setting,
            )

            # 运行回测
            engine.load_data()
            engine.run_backtesting()
            df = engine.calculate_result()
            stats = engine.calculate_statistics()

            # 保存回测结果
            self.backtest_report = {
                "total_return": stats.get("total_return", 0),
                "sharpe_ratio": stats.get("sharpe_ratio", 0),
                "max_drawdown": stats.get("max_ddpercent", 0),
                "win_rate": stats.get("win_pct", 0),
                "trade_count": stats.get("total_trade_count", 0),
                "daily_pnl": stats.get("daily_pnl", 0),
                "start_date": start_date.strftime("%Y-%m-%d"),
                "end_date": end_date.strftime("%Y-%m-%d"),
            }

            # 打印回测报告
            print("\n" + "=" * 60)
            print("📊 回测报告")
            print("=" * 60)
            print(
                f"回测周期: {start_date.strftime('%Y-%m-%d')} ~ {end_date.strftime('%Y-%m-%d')}"
            )
            print(
                "策略: "
                f"{format_strategy_label({**strategy_config, 'setting': backtest_strategy_setting})}"
            )
            print("-" * 60)
            print(f"总收益率: {self.backtest_report['total_return']:+.2f}%")
            print(f"夏普比率: {self.backtest_report['sharpe_ratio']:.2f}")
            print(f"最大回撤: {self.backtest_report['max_drawdown']:.2f}%")
            print(f"胜率: {self.backtest_report['win_rate']:.2f}%")
            print(f"交易次数: {self.backtest_report['trade_count']}")
            print("=" * 60)

            # 发送Telegram通知
            await self.telegram.send_message(
                f"✅ <b>系统启动成功</b>\n\n"
                f"📊 <b>回测报告</b> ({self.backtest_report['start_date']} ~ {self.backtest_report['end_date']})\n"
                f"├ 总收益: {self.backtest_report['total_return']:+.2f}%\n"
                f"├ 夏普: {self.backtest_report['sharpe_ratio']:.2f}\n"
                f"├ 回撤: {self.backtest_report['max_drawdown']:.2f}%\n"
                f"└ 胜率: {self.backtest_report['win_rate']:.2f}%\n\n"
                f"策略已就绪，等待交易信号..."
            )

        except Exception as e:
            print(f"❌ 回测失败: {e}")
            traceback.print_exc()
            self.backtest_report = {
                "total_return": 0,
                "sharpe_ratio": 0,
                "max_drawdown": 0,
                "win_rate": 0,
                "trade_count": 0,
            }

    async def start(self):
        """启动系统"""
        print("🚀 启动自动交易系统...\n")

        try:
            # 1. 启动Telegram机器人
            await self.telegram.start()

            # 2. 运行回测报告
            await self.run_backtest_report()

            # 3. 设置交易接口
            self.setup_gateway()

            # 4. 设置策略
            self.setup_strategy()

            # 5. 启动策略
            await self.init_and_start_strategy()
            self.wait_for_tick(get_strategy_spec(self.config)["vt_symbol"], timeout=self.tick_timeout)

            print("\n✅ 系统启动完成！")
            print("📱 Telegram已连接，交易信号将推送到你的手机")
            print("⏳ 正在监听市场...\n")

            # 6. 保持运行
            await self._run_loop()

        except KeyboardInterrupt:
            print("\n\n🛑 收到停止信号，正在关闭系统...")
        except Exception as e:
            print(f"\n❌ 系统错误: {e}")
            traceback.print_exc()
        finally:
            await self.stop()

    async def stop(self):
        """停止系统"""
        self.state["strategy_trading"] = False
        self.write_state()

        # 发送每日报告
        try:
            await self.telegram.send_daily_report(
                {
                    "date": self.daily_stats["date"],
                    "initial_capital": self.daily_stats["initial_capital"],
                    "current_capital": self.daily_stats["current_capital"],
                    "daily_pnl": sum(t.get("pnl", 0) for t in self.daily_stats["trades"]),
                    "daily_return": 0,
                    "total_return": (
                        (
                            self.daily_stats["current_capital"]
                            / self.daily_stats["initial_capital"]
                        )
                        - 1
                    )
                    * 100,
                    "trade_count": len(self.daily_stats["trades"]),
                    "win_count": len(
                        [t for t in self.daily_stats["trades"] if t.get("pnl", 0) > 0]
                    ),
                    "loss_count": len(
                        [t for t in self.daily_stats["trades"] if t.get("pnl", 0) < 0]
                    ),
                    "win_rate": 0,
                    "positions": "无",
                    "strategy_running": False,
                    "report_time": datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                }
            )
        except Exception as exc:  # noqa: BLE001
            print(f"⚠️ 发送停止报告失败: {exc}")

        # 停止Telegram
        try:
            await self.telegram.stop()
        except Exception as exc:  # noqa: BLE001
            print(f"⚠️ 停止Telegram失败: {exc}")

        # 关闭引擎
        self.main_engine.close()
        print("✅ 系统已安全关闭")

    async def _run_loop(self):
        """主循环"""
        stop_event = asyncio.Event()
        loop = asyncio.get_running_loop()
        for sig in (signal.SIGINT, signal.SIGTERM):
            try:
                loop.add_signal_handler(sig, stop_event.set)
            except NotImplementedError:
                pass

        while not stop_event.is_set():
            try:
                await asyncio.wait_for(stop_event.wait(), timeout=1)
            except asyncio.TimeoutError:
                pass

            # 检查是否需要发送每日报告（每天晚上11点）
            now = datetime.now()
            if now.hour == 23 and now.minute == 0:
                # TODO: 发送每日报告
                await asyncio.sleep(60)  # 避免重复发送


async def main():
    """主函数"""
    # 检查配置文件
    config_path = Path("config/trading_config.json")
    if not config_path.exists():
        print("❌ 配置文件不存在: config/trading_config.json")
        print("请复制 config/trading_config.example.json 并填写你的配置")
        return

    # 启动系统
    system = AutoTradingSystem()
    await system.start()


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\n👋 再见！")
