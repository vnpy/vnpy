from vnpy.app.script_trader import init_cli_trading
from vnpy.app.script_trader.cli import process_log_event
from vnpy.gateway.ib import IbGateway
from time import sleep
from datetime import datetime
import pandas as pd

# 连接到服务器
setting = {
    "TWS地址": "127.0.0.1",
    "TWS端口": 7496,
    "客户号": 8,  # 每个链接用一个独立的链接号，一个IBAPI支持32个来同时链接
    "交易账户": ""
}
engine = init_cli_trading([IbGateway])  # 返回Script_engine 示例，并且给main_engine注册了gateway
engine.connect_gateway(setting, "IB")  # 链接

# 查询资金 - 自动
sleep(2)
print("***查询资金和持仓***")
print(engine.get_all_accounts(use_df=True))
# 查询持仓
print(engine.get_all_positions(use_df=True))

# 订阅行情
from vnpy.trader.constant import Exchange
from vnpy.trader.object import SubscribeRequest

# 从我测试直接用Script_engine有问题，IB的品种太多，get_all_contracts命令不行,需要指定具体后才可以，这里使用main_engine订阅
req1 = SubscribeRequest("CL-202004-USD-FUT", Exchange.NYMEX)  # 创建行情订阅
req2 = SubscribeRequest("EUR-USD-CASH", Exchange.IDEALPRO)  # 创建行情订阅
engine.main_engine.subscribe(req1, "IB")
engine.main_engine.subscribe(req2, "IB")
vt_symbols = ["CL-202004-USD-FUT.NYMEX", "EUR-USD-CASH.IDEALPRO"]
n = 1
while n < 5:
    # 轮询获取行情
    for vt_symbol in vt_symbols:
        tick = engine.get_tick(vt_symbol)
        msg = f"最新行情, {tick}"
        engine.write_log(msg)

    n = n + 1
    # 等待3秒进入下一轮
    sleep(3)

# 使用script_engine订阅历史数据是从rqdata获取，vnpy v2.07已经提供历史数据获取，这里创建HistoryRequest来获取,
# 查询如果没有endtime，默认当前。返回历史数据输出到数据库和csv文件
# 关于api更多信息可以参见 https://interactivebrokers.github.io/tws-api/historical_bars.html
print("***从IB读取历史数据, 返回历史数据输出到数据库和csv文件***")
from vnpy.trader.object import HistoryRequest
from vnpy.trader.object import Interval

start = datetime.strptime('20200120', "%Y%m%d")

historyreq = HistoryRequest(
    symbol="CL-202004-USD-FUT",
    exchange=Exchange.NYMEX,
    start=start,
    interval=Interval.MINUTE
)
# # 读取历史数据，并把历史数据BarData放入数据库
# bardatalist = engine.main_engine.query_history(historyreq, "IB")
# from vnpy.trader.database import database_manager
#
# database_manager.save_bar_data(bardatalist)
#
# # 把历史数据BarData输出到csv
# pd.DataFrame(bardatalist).to_csv("d:\\"+str(historyreq.symbol) + ".csv", index=True, header=True)
# print("History data export to CSV")


# # 参考backtesting.ipynb, 使用自带的双均线策略回测，10日上穿60日做多，否则反之
print("***从数据库读取历史数据, 进行回测***")
from vnpy.app.cta_strategy.backtesting import BacktestingEngine
from vnpy.app.cta_strategy.strategies.double_ma_strategy import (
  DoubleMaStrategy,
)
btengine = BacktestingEngine() #新建回测引擎
btengine.set_parameters(
    vt_symbol="CL-202004-USD-FUT.NYMEX",
    interval="1m",
    start=datetime(2020, 1, 20),
    end=datetime(2020, 3, 12),
    rate = 0,
    slippage=0.01,
    size=1000,
    pricetick=0.01,
    capital=1000000,
)
btengine.add_strategy(DoubleMaStrategy, {"fast_window":10, "slow_window": 60})

btengine.load_data()
btengine.run_backtesting()
df = btengine.calculate_result()
btengine.calculate_statistics()
btengine.show_chart()

# 给script_engine载入双均线策略，实盘运行
print("***从数据库读取准备数据, 实盘运行***")
# 使用cta交易引擎
from vnpy.app.cta_strategy import CtaStrategyApp
from vnpy.app.cta_strategy.base import EVENT_CTA_LOG
engine.event_engine.register(EVENT_CTA_LOG, process_log_event)
cta_engine = engine.main_engine.add_app(CtaStrategyApp) #加入app
cta_engine.init_engine()
cta_engine.add_strategy("DoubleMaStrategy","DoubleMaStrategy_IB_12087792_v1", "12087792.IDEALPRO",{"fast_window":10, "slow_window": 50})
sleep(10)
cta_engine.init_strategy("DoubleMaStrategy_IB_12087792_v1")
sleep(10)
cta_engine.start_strategy("DoubleMaStrategy_IB_12087792_v1")