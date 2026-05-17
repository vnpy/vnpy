"""
测试脚本：验证配置加载和Telegram连接
不连接OKX，只测试配置读取和Telegram消息推送
"""

import json
import asyncio
from pathlib import Path
from telegram import Bot
from vnpy.trader.utility import get_file_path

from trading_config import load_trading_config, resolve_trading_config_path


def test_config_loading():
    """测试配置文件加载"""
    print("=" * 60)
    print("🔍 测试配置加载")
    print("=" * 60)

    # 1. 加载交易配置
    trading_config_path = resolve_trading_config_path("config/trading_config.json")
    if trading_config_path.exists():
        trading_config = load_trading_config(trading_config_path)
        print(f"✅ 交易配置已加载: {trading_config_path}")
        print(f"   交易对: {trading_config['strategy']['vt_symbol']}")
        print(f"   策略: {trading_config['strategy']['name']}")
        print(f"   快线: {trading_config['strategy']['setting']['fast_window']}")
        print(f"   慢线: {trading_config['strategy']['setting']['slow_window']}")
        print(f"   Telegram Chat ID: {trading_config['telegram']['chat_id']}")
    else:
        print(f"❌ 交易配置不存在: {trading_config_path}")
        return False

    # 2. 加载OKX配置
    okx_config_path = get_file_path("connect_okx.json")
    if okx_config_path.exists():
        with open(okx_config_path, "r") as f:
            okx_config = json.load(f)
        print(f"\n✅ OKX配置已加载: {okx_config_path}")
        print(f"   API Key: {okx_config['API Key'][:8]}...{okx_config['API Key'][-4:]}")
        print(f"   Server: {okx_config['Server']}")
        print(f"   Passphrase: {'*' * len(okx_config['Passphrase'])}")
    else:
        print(f"\n❌ OKX配置不存在: {okx_config_path}")
        return False

    return trading_config, okx_config


async def test_telegram(config):
    """测试Telegram连接"""
    print("\n" + "=" * 60)
    print("📱 测试Telegram连接")
    print("=" * 60)

    try:
        bot_token = config["telegram"]["bot_token"]
        chat_id = config["telegram"]["chat_id"]

        print(f"   Bot Token: {bot_token[:15]}...{bot_token[-10:]}")
        print(f"   Chat ID: {chat_id}")

        bot = Bot(token=bot_token)

        # 获取Bot信息
        bot_info = await bot.get_me()
        print(f"✅ Telegram Bot已连接")
        print(f"   Bot名称: {bot_info.first_name}")
        print(f"   Bot用户名: @{bot_info.username}")

        # 发送测试消息
        test_message = (
            "🚀 <b>自动交易系统测试</b>\n\n"
            "✅ 配置加载成功\n"
            f"📊 交易对: {config['strategy']['vt_symbol']}\n"
            f"⚙️ 策略: {config['strategy']['name']}\n"
            f"   快线={config['strategy']['setting']['fast_window']}\n"
            f"   慢线={config['strategy']['setting']['slow_window']}\n\n"
            "⏳ 系统测试完成，准备就绪！"
        )

        await bot.send_message(chat_id=chat_id, text=test_message, parse_mode="HTML")
        print(f"✅ 测试消息已发送到Chat ID: {chat_id}")
        print("   请检查你的Telegram，应该已经收到消息")

        return True

    except Exception as e:
        print(f"❌ Telegram测试失败: {e}")
        print("\n💡 可能原因:")
        print("   1. 网络无法访问Telegram（可能需要代理）")
        print("   2. Bot Token错误")
        print("   3. Chat ID错误")
        print("   4. 未给Bot发送过 /start")
        return False


def test_backtest_config(config):
    """测试回测配置"""
    print("\n" + "=" * 60)
    print("📊 回测配置")
    print("=" * 60)

    backtest = config["backtest"]
    print(f"回测周期: {backtest['start_date']} ~ {backtest['end_date']}")
    print(f"K线周期: {backtest['interval']}")
    print(f"初始资金: {backtest['capital']} USDT")
    print(f"✅ 回测配置正常")


async def main():
    """主函数"""
    print("\n" + "=" * 60)
    print("🚀 自动交易系统 - 配置测试")
    print("=" * 60 + "\n")

    # 测试配置加载
    configs = test_config_loading()
    if not configs:
        print("\n❌ 配置加载失败，请检查配置文件")
        return

    trading_config, okx_config = configs

    # 测试回测配置
    test_backtest_config(trading_config)

    # 测试Telegram
    telegram_ok = await test_telegram(trading_config)

    # 总结
    print("\n" + "=" * 60)
    print("📋 测试结果总结")
    print("=" * 60)
    print("✅ 交易配置: 正常")
    print("✅ OKX配置: 正常")
    print("✅ 回测配置: 正常")
    print(
        f"{'✅' if telegram_ok else '❌'} Telegram: {'正常' if telegram_ok else '失败'}"
    )

    if telegram_ok:
        print("\n🎉 所有测试通过！可以启动交易系统了")
        print("   运行: python run_auto_trading.py")
    else:
        print("\n⚠️ Telegram连接失败，请检查:")
        print("   1. Bot Token是否正确")
        print("   2. Chat ID是否正确")
        print("   3. 是否已给Bot发送过/start")


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\n\n👋 测试已取消")
