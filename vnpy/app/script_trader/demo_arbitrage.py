
from time import sleep

from vnpy.app.script_trader import ScriptEngine
from vnpy.trader.constant import Direction


def run(engine: ScriptEngine):
    """"""
    # 订阅行情
    vt_symbol_1 = "XBTU19.BITMEX"
    vt_symbol_2 = "XBTUSD.BITMEX"
    engine.subscribe([vt_symbol_1, vt_symbol_2])

    # 连续执行
    while engine.strategy_active:
        # 每隔10秒执行1次
        sleep(10)

        # 计算价差
        tick_1 = engine.get_tick(vt_symbol_1)
        tick_2 = engine.get_tick(vt_symbol_2)

        if not tick_1 or not tick_2:
            engine.write_log("行情获取有问题，等待重试")
            break

        spread_bid_price = tick_1.bid_price_1 - tick_2.ask_price_1
        spread_ask_price = tick_1.ask_price_1 - tick_2.bid_price_1
        spread_symbol = f"{tick_1.symbol}-{tick_2.symbol}"

        msg = f"{spread_symbol}组合，Bid Price:{spread_bid_price}，Ask Price：{spread_ask_price}"
        engine.write_log(msg)

        # 计算仓位
        vt_positionid_1 = f"{vt_symbol_1}.{Direction.NET.value}"
        vt_positionid_2 = f"{vt_symbol_2}.{Direction.NET.value}"

        position_1 = engine.get_position(vt_positionid_1)
        position_2 = engine.get_position(vt_positionid_2)

        pos_1 = position_1.volume if position_1 else 0
        pos_2 = position_2.volume if position_2 else 0

        if pos_1 + pos_2 != 0:
            engine.write_log(f"两条腿持仓不匹配，无法继续执行，请检查")
            break

        engine.write_log(
            f"{tick_1.symbol}当前仓位：{pos_1}, {tick_2.symbol}当前仓位：{pos_2}")

        # 撤销活动委托
        active_orders = engine.get_all_active_orders()
        if active_orders:
            engine.write_log(f"有活动状态委托")

        for order in active_orders:
            engine.cancel_order(order.vt_orderid)
            engine.write_log(f"执行撤单操作{order.vt_orderid}")

        # 交易判断
        buy_price = 200    # 价差买入目标
        sell_price = 300   # 价差卖出目标
        trading_size = 1   # 交易数量

        # 当前没有仓位
        if not pos_1:
            print("当前无仓位")
            if spread_ask_price <= buy_price:
                engine.write_log(
                    f"价差ask：{spread_ask_price}, 小于买入目标：{buy_price}，买入做多")
                engine.buy(vt_symbol_1, tick_1.ask_price_5, trading_size)
                engine.short(vt_symbol_2, tick_2.bid_price_5, trading_size)
        # 当前已经持有多头仓位
        elif pos_1 > 0:
            print("当前持有价差多头仓位")
            if spread_bid_price >= sell_price:
                engine.write_log(
                    f"价差bid：{spread_bid_price}, 小于买入目标：{sell_price}，卖出平仓")
                engine.sell(vt_symbol_1, tick_1.bid_price_5, trading_size)
                engine.cover(vt_symbol_2, tick_2.ask_price_5, trading_size)
