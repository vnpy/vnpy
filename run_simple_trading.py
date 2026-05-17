"""
简化版自动交易系统 - 跳过回测直接连接OKX
"""

import asyncio
import json
import sys
import traceback
from datetime import datetime
from pathlib import Path

from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.object import SubscribeRequest
from vnpy.trader.utility import extract_vt_symbol, get_file_path

from vnpy_okx import OkxGateway
from vnpy_ctastrategy import CtaStrategyApp
from vnpy_ctastrategy.strategies.double_ma_strategy import DoubleMaStrategy

from telegram_notifier import TelegramTradeBot
from trading_config import load_trading_config, resolve_trading_config_path


class SimpleAutoTradingSystem:
    """简化版自动交易系统"""

    def __init__(self):
        """初始化系统"""
        # 确定配置文件路径
        script_dir = Path(__file__).parent.absolute()
        config_path = resolve_trading_config_path(script_dir / "config" / "trading_config.json")

        print(f"📂 加载配置文件: {config_path}")
        self.config = load_trading_config(config_path)

        # 加载OKX配置
        okx_config_path = get_file_path("connect_okx.json")
        if Path(okx_config_path).exists():
            with open(okx_config_path, "r") as f:
                self.okx_config = json.load(f)
            print(f"✅ 已从 {okx_config_path} 加载OKX配置")
        else:
            self.okx_config = None

        # 初始化事件引擎
        self.event_engine = EventEngine()
        self.main_engine = MainEngine(self.event_engine)

        # 初始化Telegram机器人
        self.telegram = TelegramTradeBot(str(config_path))

    async def start(self):
        """启动系统"""
        print("\n🚀 启动自动交易系统...\n")

        try:
            # 1. 启动Telegram机器人
            await self.telegram.start()

            # 2. 发送启动通知（跳过回测）
            strategy = self.config["strategy"]
            await self.telegram.send_message(
                f"🚀 <b>系统启动成功</b>\n\n"
                f"📊 交易对: {strategy['vt_symbol']}\n"
                f"⚙️ 策略: {strategy['name']}\n"
                f"   快线={strategy['setting']['fast_window']}\n"
                f"   慢线={strategy['setting']['slow_window']}\n\n"
                f"⏳ 准备连接OKX..."
            )

            # 3. 设置交易接口
            self.setup_gateway()

            # 4. 设置策略
            self.setup_strategy()

            # 5. 启动策略
            cta_engine = self.main_engine.get_engine("CtaStrategy")
            cta_engine.init_strategy("DoubleMA_Auto")
            await asyncio.sleep(2)
            cta_engine.start_strategy("DoubleMA_Auto")

            print("\n✅ 系统启动完成！")
            print("📱 Telegram已连接")
            print("⏳ 正在监听行情...\n")

            # 6. 保持运行
            await self._run_loop()

        except KeyboardInterrupt:
            print("\n\n🛑 收到停止信号")
        except Exception as e:
            print(f"\n❌ 系统错误: {e}")
            traceback.print_exc()
        finally:
            await self.stop()

    def setup_gateway(self):
        """配置交易接口"""
        if self.okx_config:
            connect_config = {
                "API Key": self.okx_config["API Key"],
                "API Secret": self.okx_config["Secret Key"],
                "Passphrase": self.okx_config["Passphrase"],
                "Server": "DEMO",  # 强制使用模拟盘
                "Proxy Address": "",
                "Proxy Port": "",
            }
            print("✅ 已配置OKX连接（强制模拟盘模式）")
        else:
            raise ValueError("未找到OKX配置")

        self.main_engine.add_gateway(OkxGateway)
        self.main_engine.connect(connect_config, "OKX")
        print("✅ 已连接到OKX 模拟盘")

    def setup_strategy(self):
        """配置策略"""
        self.main_engine.add_app(CtaStrategyApp)
        cta_engine = self.main_engine.get_engine("CtaStrategy")

        strategy_config = self.config["strategy"]
        vt_symbol = strategy_config["vt_symbol"]

        # 订阅行情
        exchange, symbol = extract_vt_symbol(vt_symbol)
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

    async def stop(self):
        """停止系统"""
        await self.telegram.send_message("🛑 自动交易系统已停止")
        await self.telegram.stop()
        self.main_engine.close()
        print("✅ 系统已安全关闭")

    async def _run_loop(self):
        """主循环"""
        while True:
            await asyncio.sleep(1)


async def main():
    """主函数"""
    system = SimpleAutoTradingSystem()
    await system.start()


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\n👋 再见！")
