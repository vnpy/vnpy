
from time import sleep
from csv import DictReader
from pathlib import Path

from vnpy.app.script_trader import ScriptEngine
from vnpy.trader.constant import Direction


def run(engine: ScriptEngine):
    """"""
    engine.write_log("开始执行篮子委托")

    # 载入篮子委托CSV文件
    path = Path(__file__).parent
    csv_path = path.joinpath("order.csv")

    orders = {}
    with open(csv_path) as f:
        reader = DictReader(f)

        for d in reader:
            orders[d["vt_symbol"]] = int(d["volume"])

    engine.write_log("篮子委托CSV文件加载完毕")

    # 订阅行情
    engine.subscribe(list(orders.keys()))
    engine.write_log("订阅篮子股票行情成功")

    # 连续执行
    execution_times = 100
    execution_count = 0

    while engine.strategy_active:
        # 等待1分钟
        sleep(60)

        # 一共执行100次
        execution_count += 1
        if execution_count > execution_times:
            break
        engine.write_log(f"当前执行轮数：{execution_count}")

        # 逐个委托执行
        for vt_symbol, volume in orders.items():
            # 计算每轮委托数量
            order_volume = volume / execution_times

            # 获取最新行情
            tick = engine.get_tick(vt_symbol)
            if not tick:
                engine.write_log(f"无法获取行情{vt_symbol}")
                continue

            # 执行委托
            if order_volume > 0:
                engine.buy(vt_symbol, tick.ask_price_5, order_volume)
                engine.write_log(
                    f"买入{vt_symbol}, {order_volume}@{tick.ask_price_5}")
            else:
                engine.sell(vt_symbol, tick.bid_price_5, abs(order_volume))
                engine.write_log(
                    f"卖出{vt_symbol}, {order_volume}@{tick.bid_price_5}")

    # 最终退出
    engine.write_log("篮子委托执行完毕")
