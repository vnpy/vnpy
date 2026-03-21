"""
自动交易系统主程序（OKX模拟盘 + Telegram确认）
支持DoubleMA策略，带详细回测报告
"""

import asyncio
import json
import sys
import traceback
from datetime import datetime, timedelta
from pathlib import Path

from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.object import SubscribeRequest
from vnpy.trader.constant import Interval
from vnpy.trader.utility import extract_vt_symbol

from vnpy_okx import OkxGateway
from vnpy_ctastrategy import CtaStrategyApp
from vnpy_ctastrategy.strategies.double_ma_strategy import DoubleMaStrategy

from telegram_notifier import TelegramTradeBot


class AutoTradingSystem:
    """自动交易系统"""

    def __init__(
        self,
        config_path: str = None,
        okx_config_path: str = "/Users/miaoyuhan/.vntrader/connect_okx.json",
    ):
        """初始化系统"""
        if config_path is None:
            script_dir = Path(__file__).parent.absolute()
            config_path = script_dir / "config" / "trading_config.json"
        else:
            config_path = Path(config_path)

        print(f"📂 加载配置文件: {config_path}")

        # 加载配置
        with open(config_path, "r") as f:
            self.config = json.load(f)

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

        # 初始化Telegram机器人
        self.telegram = TelegramTradeBot(config_path)

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
        if self.okx_config:
            connect_config = {
                "API Key": self.okx_config["API Key"],
                "Secret Key": self.okx_config["Secret Key"],
                "Passphrase": self.okx_config["Passphrase"],
                "Server": self.okx_config.get("Server", "DEMO"),
                "Proxy Host": self.okx_config.get("Proxy Host", ""),
                "Proxy Port": self.okx_config.get("Proxy Port", 0),
                "Spread Trading": self.okx_config.get("Spread Trading", "False"),
                "Margin Currency": self.okx_config.get("Margin Currency", ""),
            }
            is_simulated = self.okx_config.get("Server", "DEMO") == "DEMO"
        else:
            okx_config = self.config["okx"]
            connect_config = {
                "API Key": okx_config["api_key"],
                "API Secret": okx_config["api_secret"],
                "Passphrase": okx_config["passphrase"],
                "Server": "REAL" if not okx_config["use_simulated"] else "DEMO",
                "Proxy Address": okx_config.get("proxy", ""),
                "Proxy Port": okx_config.get("proxy_port", ""),
            }
            is_simulated = okx_config["use_simulated"]

        self.main_engine.add_gateway(OkxGateway)
        self.main_engine.connect(connect_config, "OKX")
        print(f"✅ 已连接到OKX {'模拟盘' if is_simulated else '实盘'}")

    def setup_strategy(self):
        """配置策略"""
        # 添加CTA策略模块
        self.main_engine.add_app(CtaStrategyApp)

        # 获取CTA引擎并初始化
        cta_engine = self.main_engine.get_engine("CtaStrategy")
        cta_engine.init_engine()

        # 策略配置 (配置文件中已使用正确的格式: DOGEUSDT_SWAP_OKX.GLOBAL)
        strategy_config = self.config["strategy"]
        vt_symbol = strategy_config["vt_symbol"]

        # 订阅行情
        symbol, exchange = extract_vt_symbol(vt_symbol)
        req = SubscribeRequest(symbol=symbol, exchange=exchange)
        self.main_engine.subscribe(req, "OKX")

        # 添加策略
        cta_engine.add_strategy(
            class_name="DoubleMaStrategy",
            strategy_name="DoubleMA_Auto",
            vt_symbol=vt_symbol,
            setting=strategy_config["setting"],
        )

        print(f"✅ 策略已添加: {vt_symbol}")
        print(
            f"   参数: 快线={strategy_config['setting']['fast_window']}, "
            f"慢线={strategy_config['setting']['slow_window']}"
        )

    async def run_backtest_report(self):
        """运行回测并生成报告"""
        from vnpy_ctastrategy.backtesting import BacktestingEngine

        print("\n📊 正在运行回测...")

        try:
            # 创建回测引擎
            engine = BacktestingEngine()

            strategy_config = self.config["strategy"]
            backtest_config = self.config["backtest"]

            end_date = datetime.now()
            start_date = end_date - timedelta(days=90)
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
            engine.add_strategy(
                strategy_class=DoubleMaStrategy,
                setting=strategy_config["setting"],
            )

            # 运行回测
            engine.load_data()
            engine.run_backtesting()
            df = engine.calculate_result()
            stats = engine.calculate_statistics()

            # 保存回测结果
            self.backtest_report = {
                "total_return": stats.get("return_pct", 0),
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
                f"策略: DoubleMA (快线={strategy_config['setting']['fast_window']}, "
                f"慢线={strategy_config['setting']['slow_window']})"
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
            cta_engine = self.main_engine.get_engine("CtaStrategy")
            cta_engine.init_strategy("DoubleMA_Auto")
            await asyncio.sleep(2)  # 等待初始化
            cta_engine.start_strategy("DoubleMA_Auto")

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
        # 发送每日报告
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

        # 停止Telegram
        await self.telegram.stop()

        # 关闭引擎
        self.main_engine.close()
        print("✅ 系统已安全关闭")

    async def _run_loop(self):
        """主循环"""
        while True:
            await asyncio.sleep(1)

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
