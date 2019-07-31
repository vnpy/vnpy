#!/usr/bin/env python
#-*- coding:utf-8 -*-
############################
#File Name:
#Author: wudi
#Mail: programmerwudi@gmail.com
#Created Time: 2019-07-15 10:55:49
############################


from vnpy.trader.constant import Direction
from vnpy.trader.object import TradeData, OrderData, PositionData
from vnpy.trader.engine import BaseEngine

from vnpy.app.algo_trading import AlgoTemplate

class FutureAlgo(AlgoTemplate):
    """"""

    display_name = "跨期套利"

    default_setting = {
        "active_vt_symbol": "",
        "passive_vt_symbol": "",
        "spread_up": 0.0,
        "spread_down": 0.0,
        #"max_pos": 0.0, # 最大持仓btc数量
        "interval": 0,
        "split_order": 0.0, # btc计算 拆单量
        "max_pos_btc": 0.0, # 最大持仓btc数量
        # "is_active_close": True,  # True 1 只平仓 False 0 持续反向套利
        "is_active_close": ["是", "否"],
        "is_passtive_close": ["是", "否"]

    }

    variables = [
        "timer_count",
        "active_vt_orderid",
        "passive_vt_orderid",
        "active_pos",
        "passive_pos",
        "active_pos_btc", # 添加对等btc数量
        "passive_pos_btc",
        "pos",


    ]

    def __init__(
        self,
        algo_engine: BaseEngine,
        algo_name: str,
        setting: dict,
        #main_engine: MainEngine
    ):
        """"""
        super().__init__(algo_engine, algo_name, setting)
        #self.main_engine = main_engine
        self.holdings = {}
        # Parameters
        self.active_vt_symbol = setting["active_vt_symbol"]
        self.passive_vt_symbol = setting["passive_vt_symbol"]
        self.spread_up = setting["spread_up"]
        self.spread_down = setting["spread_down"]
        # self.max_pos = setting["max_pos"]
        self.interval = setting["interval"]
        self.max_pos_btc = setting["max_pos_btc"]
        self.split_order = setting["split_order"]
        self.is_active_close = setting["is_active_close"]
        self.is_passtive_close = setting["is_passtive_close"]


        # Variables
        self.active_vt_orderid = ""
        self.passive_vt_orderid = ""
        self.active_pos = 0
        self.passive_pos = 0
        self.timer_count = 0
        self.active_pos_btc = 0 # 添加对等btc数量
        self.passive_pos_btc = 0

        self.subscribe(self.active_vt_symbol)
        self.subscribe(self.passive_vt_symbol)


        #self.pos_act = self.get_position(self.active_vt_symbol)
        print(self.active_vt_symbol)

        # self.pos = self.algo_engine.get_position(self.active_vt_symbol)
        self.pos = 0
        self.long_pos = 0
        self.long_yd = 0
        self.long_td = 0

        self.short_pos = 0
        self.short_yd = 0
        self.short_td = 0
        self.net_active_pos = 0
        self.net_passive_pos = 0

        self.put_parameters_event()
        self.put_variables_event()


    def on_stop(self):
        """"""
        self.write_log("停止算法")

    def on_order(self, order: OrderData):
        """"""
        if order.vt_symbol == self.active_vt_symbol:
            if not order.is_active():
                self.active_vt_orderid = ""
        elif order.vt_symbol == self.passive_vt_symbol:
            if not order.is_active():
                self.passive_vt_orderid = ""
        self.put_variables_event()

    def on_trade(self, trade: TradeData):
        """"""

        # Update pos
        if trade.direction == Direction.LONG:
            if trade.vt_symbol == self.active_vt_symbol:
                self.active_pos += trade.volume
                #self.active_pos += (trade.price * self.split_order)
                self.active_pos_btc += trade.xbt
            else:
                self.passive_pos += trade.volume
                #self.passive_pos += (trade.price * self.split_order)
                self.passive_pos_btc += trade.xbt
        else:
            if trade.vt_symbol == self.active_vt_symbol:
                self.active_pos -= trade.volume
                #self.active_pos -= (trade.price * self.split_order)
                self.active_pos_btc -= trade.xbt
            else:
                self.passive_pos -= trade.volume
                #self.passive_pos -= (trade.price * self.split_order)
                self.passive_pos_btc -= trade.xbt


                    # Hedge if active symbol traded
        if trade.vt_symbol == self.active_vt_symbol:
            self.write_log("收到主动腿成交回报，执行对冲")
            # if (self.is_active_close == 1 and self.active_pos_btc == 0 and self.passive_pos_btc == 0):
            #     self.write_log("仅平仓 不对冲")
            #     return
            self.hedge()

        self.put_variables_event()

    def on_timer(self):
        """"""
        # Run algo by fixed interval
        self.timer_count += 1
        if self.timer_count < self.interval:
            self.put_variables_event()
            return
        self.timer_count = 0


        print(f"++++is close {self.is_active_close} , is_active_close == 是 {self.is_active_close == '是'}   ++++")

        #self.pos = self.algo_engine.process_position_event(self,self.active_vt_symbol)

        # 获取仓位数据
        active_position_data =  self.get_position(self.active_vt_symbol)
        passive_position_data =  self.get_position(self.passive_vt_symbol)
        self.active_pos_btc = active_position_data.notional
        self.passive_pos_btc = passive_position_data.notional
        self.net_active_pos = active_position_data.volume
        self.net_passive_pos = passive_position_data.volume
        self.active_pos = active_position_data.volume
        self.passive_pos = passive_position_data.volume

        print(f"主动退仓位btc {self.active_pos_btc}")
        print(f"被动腿仓位btc {self.passive_pos_btc}")
        print(f"主动退仓位 {self.net_active_pos}")
        print(f"被动腿仓位 {self.net_passive_pos}")
        # Make sure that tick data of both leg are available
        active_tick = self.get_tick(self.active_vt_symbol)
        passive_tick = self.get_tick(self.passive_vt_symbol)




        if not active_tick or not passive_tick:
            self.write_log("获取某条套利腿的行情失败，无法交易")
            return

        if (self.active_pos != 0 and self.active_pos_btc == 0 and active_position_data.volume != 0 ):
            self.write_log("获取套利主动腿仓位失败，无法交易")
            return

        if self.passive_pos != 0 and self.passive_pos_btc == 0 and passive_position_data.volume != 0:
            self.write_log("获取套利被动腿仓位失败，无法交易")
            return


        # Cancel all active orders before moving on
        if self.active_vt_orderid or self.passive_vt_orderid:
            self.write_log("有未成交委托，执行撤单")
            self.cancel_all()
            return



        if self.net_active_pos != 0 or self.net_passive_pos != 0:

            if (self.net_active_pos + self.net_passive_pos) != 0:
                # if (self.active_pos_btc + self.passive_pos_btc) != 0:
                self.write_log("启动时 主动腿和被动腿数量不一致，执行对冲")
                self.hedge_net()
                return
        else:
            # Make sure that active leg is fully hedged by passive leg
            if (self.active_pos + self.passive_pos) != 0:
                # if (self.active_pos_btc + self.passive_pos_btc) != 0:
                self.write_log("主动腿和被动腿数量不一致，执行对冲")
                self.hedge()
                return

        # Calculate spread
        spread_bid_price = active_tick.bid_price_1 - passive_tick.ask_price_1
        spread_ask_price = active_tick.ask_price_1 - passive_tick.bid_price_1

        # 计算bid ask volume数量
        send_active_bid_volume = active_tick.bid_volume_1 if active_tick.bid_volume_1 > (active_tick.bid_price_1 * self.split_order) else (active_tick.bid_price_1 * self.split_order)
        send_passive_bid_volume = passive_tick.bid_volume_1 if passive_tick.bid_volume_1 > (passive_tick.bid_price_1 * self.split_order) else (passive_tick.bid_price_1 * self.split_order)

        send_active_ask_volume = active_tick.ask_volume_1 if active_tick.ask_volume_1 > (active_tick.ask_price_1 * self.split_order) else (active_tick.ask_price_1 * self.split_order)
        send_passive_ask_volume = passive_tick.ask_volume_1 if passive_tick.ask_volume_1 > (passive_tick.ask_price_1 * self.split_order) else (passive_tick.ask_price_1 * self.split_order)

        # spread_bid_volume = min(active_tick.bid_volume_1,
        #             passive_tick.ask_volume_1)
        # spread_ask_volume = min(active_tick.ask_volume_1,
        #                         passive_tick.bid_volume_1)

        spread_bid_volume = min(send_active_bid_volume,
                                send_passive_ask_volume)
        spread_ask_volume = min(send_active_ask_volume,
                                send_passive_bid_volume)

        msg = f"价差盘口，买：{spread_bid_price} ({spread_bid_volume})，卖：{spread_ask_price} ({spread_ask_volume}), 主仓位 {self.active_pos_btc} btc, 被仓位{self.passive_pos_btc} btc"
        self.write_log(msg)
        #

        #
        # if (self.is_active_close == True):  # 平仓后不做继续反向买入操作
        #     pass

        # Sell condition
        if spread_bid_price > self.spread_up:
            self.write_log("套利价差超过上限，满足做空条件")

            if abs(self.active_pos_btc) > self.max_pos_btc or abs(self.passive_pos_btc) > self.max_pos_btc:
                self.write_log(f"(BTC)持仓满足最大计划持仓 {self.max_pos_btc} XBT 暂不交易, 主动仓位{self.active_pos_btc} XBT, 合约数量{active_position_data.volume}, 被动仓位 {self.passive_pos_btc} XBT, 合约数量 {passive_position_data.volume}")

            if self.is_passtive_close == "是" and self.active_pos_btc == 0 and self.passive_pos_btc == 0:
                self.write_log("仅平仓不做反向操作")
                return
            #if self.active_pos > -self.max_pos:

            if self.active_pos_btc > -self.max_pos_btc:

                self.write_log("当前持仓小于最大持仓限制，执行卖出操作")


                # volume = min(spread_bid_volume,
                #              self.active_pos + self.max_pos)

                volume = min(spread_bid_volume,
                             #(self.active_pos_btc*active_tick.bid_price_1 + self.max_pos_btc*active_tick.bid_price_1))
                             self.split_order*active_tick.bid_price_1)
                             #(self.active_pos_btc*active_tick.bid_price_1 + self.split_order*active_tick.bid_price_1))
                self.write_log(f"卖出 volume {volume}, 计算值{(self.active_pos_btc*active_tick.bid_price_1 + self.max_pos_btc*active_tick.bid_price_1)}")
                self.write_log(f"卖出 volume {volume}, 拆单计算值{(self.active_pos_btc*active_tick.bid_price_1 + self.split_order*active_tick.bid_price_1)}")


                if self.is_passtive_close == "是" and self.active_pos - volume < 0 and self.active_pos != 0:
                    self.write_log(f"仅仅平仓，执行买入操作， 买入出volume {self.active_pos}")
                    volume = self.active_pos

                self.active_vt_orderid = self.sell(
                    self.active_vt_symbol,
                    active_tick.bid_price_1,
                    volume
                )

        # Buy condition
        elif spread_ask_price < -self.spread_down:
            self.write_log("套利价差超过下限，满足做多条件")


            if self.is_active_close == "是" and self.active_pos_btc == 0  and self.passive_pos_btc == 0:
                self.write_log("仅平仓不做反向操作")
                return

            print(f"active_pos info {self.active_pos}")
            print(f"passive_pos info {self.passive_pos}")
            if abs(self.active_pos_btc) > self.max_pos_btc or abs(self.passive_pos_btc) > self.max_pos_btc:
                self.write_log(
                    f"(BTC)持仓满足最大计划持仓 {self.max_pos_btc} XBT 暂不交易, 主动仓位{self.active_pos_btc} XBT, 合约数量{active_position_data.volume}, 被动仓位 {self.passive_pos_btc} XBT, 合约数量 {passive_position_data.volume}")

            #if self.active_pos < self.max_pos:
            if self.active_pos_btc < self.max_pos_btc:


                self.write_log("当前持仓小于最大持仓限制，执行买入操作")

                # if self.active_pos_btc == 0 and self.is_active_close == 1:
                #     self.write_log("仅平仓不执行反向买入操作")
                #     return

                # volume = min(spread_ask_volume,
                #              self.max_pos - self.active_pos)

                volume = min(spread_ask_volume,
                             #(self.max_pos_btc*active_tick.ask_price_1 - self.active_pos_btc*active_tick.ask_price_1))
                             self.split_order*active_tick.ask_price_1)
                             #(self.split_order*active_tick.ask_price_1 - self.active_pos_btc*active_tick.ask_price_1))
                self.write_log(f"买入 volume {volume}, 计算值{  (self.max_pos_btc*active_tick.ask_price_1 - self.active_pos_btc*active_tick.ask_price_1)}")
                self.write_log(f"买入 volume {volume}, 拆单计算值{  (self.split_order*active_tick.ask_price_1 - self.active_pos_btc*active_tick.ask_price_1)}")


                if self.is_active_close == "是" and self.active_pos + volume > 0 and self.active_pos != 0:
                    self.write_log(f"仅仅平仓，执行买入操作， 买入出volume {self.active_pos}")
                    volume = -self.active_pos

                self.active_vt_orderid = self.buy(
                    self.active_vt_symbol,
                    active_tick.ask_price_1,
                    volume
                )



        # Update GUI
        self.put_variables_event()

    def hedge(self):
        """"""
        tick = self.get_tick(self.passive_vt_symbol)
        volume = -self.active_pos - self.passive_pos
        xbt = -self.active_pos_btc - self.passive_pos_btc

        print(f"in hedge {xbt}")
        #net_pos = abs(self.net_pos)

        if volume > 0:
            self.passive_vt_orderid = self.buy(
                self.passive_vt_symbol,
                tick.ask_price_1,
                volume
            )
        elif volume < 0:
            self.passive_vt_orderid = self.sell(
                self.passive_vt_symbol,
                tick.bid_price_1,
                abs(volume)
            )


        #if xbt > 0:
        #    self.passive_vt_orderid = self.buy(
        #        self.passive_vt_symbol,
        #        tick.ask_price_1,
        #        (tick.ask_price_1 * xbt)
        #    )
        #elif xbt < 0:
        #    self.passive_vt_orderid = self.sell(
        #        self.passive_vt_symbol,
        #        tick.bid_price_1,
        #        abs((tick.bid_price_1 * xbt))
        #    )

    def hedge_net(self):
        """"""
        tick = self.get_tick(self.passive_vt_symbol)
        volume = -self.net_active_pos - self.net_passive_pos
        # xbt = -self.active_pos_btc - self.passive_pos_btc

        if volume > 0:
            self.passive_vt_orderid = self.buy(
                self.passive_vt_symbol,
                tick.ask_price_1,
                volume
            )
        elif volume < 0:
            self.passive_vt_orderid = self.sell(
                self.passive_vt_symbol,
                tick.bid_price_1,
                abs(volume)
            )