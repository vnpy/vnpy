from vnpy.trader.constant import Direction
from vnpy.trader.object import TradeData, OrderData, PositionData
from vnpy.trader.engine import BaseEngine

from vnpy.app.algo_trading import AlgoTemplate

class CSAAlgo(AlgoTemplate):
    """"""

    display_name = "CSA 跨期套利"

    default_setting = {
        "active_vt_symbol": "",
        "passive_vt_symbol": "",
        "spread_up": 0.0,
        "spread_down": 0.0,
        #"max_pos": 0.0, # 最大持仓btc数量
        "interval": 0,
        "interval_pos_btc": 0.0, # btc计算 拆单量
        "max_pos_btc": 0.0, # 最大持仓btc数量
        # "is_active_close": True,  # True 1 只平仓 False 0 持续反向套利
        "is_active_close": ["是", "否"],
        "is_passive_close": ["是", "否"]

    }

    variables = [
        "timer_count",
        "active_vt_orderid",
        "passive_vt_orderid",
        "active_pos",
        "passive_pos",
        "active_pos_btc", # 添加对等btc数量
        "passive_pos_btc",
    ]

    def __init__(
        self,
        algo_engine: BaseEngine,
        algo_name: str,
        setting: dict,
    ):
        """"""
        super().__init__(algo_engine, algo_name, setting)
        self.holdings = {}
        # Parameters
        self.active_vt_symbol = setting["active_vt_symbol"]
        self.passive_vt_symbol = setting["passive_vt_symbol"]
        self.spread_up = setting["spread_up"]
        self.spread_down = setting["spread_down"]
        self.interval = setting["interval"]
        self.max_pos_btc = setting["max_pos_btc"]
        self.interval_pos_btc = setting["interval_pos_btc"]
        self.is_active_close = setting["is_active_close"]
        self.is_passive_close = setting["is_passive_close"]


        # Variables
        self.active_vt_orderid = ""
        self.passive_vt_orderid = ""
        self.active_pos = 0
        self.passive_pos = 0
        self.timer_count = 0
        self.active_pos_btc = 0
        self.passive_pos_btc = 0

        self.subscribe(self.active_vt_symbol)
        self.subscribe(self.passive_vt_symbol)

        print(self.active_vt_symbol)

        self.active_pos_volume = 0
        self.passive_pos_volume = 0

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
                self.active_pos_btc += trade.xbt
            else:
                self.passive_pos += trade.volume
                self.passive_pos_btc += trade.xbt
        else:
            if trade.vt_symbol == self.active_vt_symbol:
                self.active_pos -= trade.volume
                self.active_pos_btc -= trade.xbt
            else:
                self.passive_pos -= trade.volume
                self.passive_pos_btc -= trade.xbt


        # Hedge if active symbol traded
        if trade.vt_symbol == self.active_vt_symbol:
            self.write_log("收到主动腿成交回报，执行对冲")
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

        # Cancel all active orders before moving on
        if self.active_vt_orderid or self.passive_vt_orderid:
            self.write_log("有未成交委托，执行撤单")
            self.cancel_all()
            return

        print(f"++++ Active close {self.is_active_close}, {self.is_active_close == '是'} ++++")

        # 获取仓位数据
        active_position_data =  self.get_position(self.active_vt_symbol)
        passive_position_data =  self.get_position(self.passive_vt_symbol)
        self.active_pos_btc = active_position_data.notional
        self.passive_pos_btc = passive_position_data.notional
        self.active_pos_volume = active_position_data.volume
        self.passive_pos_volume = passive_position_data.volume
        self.active_pos = active_position_data.volume
        self.passive_pos = passive_position_data.volume

        print(f"主动退仓位btc {self.active_pos_btc}")
        print(f"被动腿仓位btc {self.passive_pos_btc}")
        print(f"主动腿仓位 {self.active_pos_volume}")
        print(f"被动腿仓位 {self.passive_pos_volume}")
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

        if (self.active_pos_volume != 0 or self.passive_pos_volume != 0) and (self.active_pos_volume + self.passive_pos_volume) != 0:
                self.write_log("启动时 主动腿和被动腿数量不一致，执行对冲")
                self.hedge_net()
                return

        # Calculate spread
        spread_bid_price = active_tick.bid_price_1 - passive_tick.ask_price_1
        spread_ask_price = active_tick.ask_price_1 - passive_tick.bid_price_1

        interval_active_bid_volume  = active_tick.bid_price_1 * self.interval_pos_btc
        interval_passive_ask_volume = passive_tick.ask_price_1 * self.interval_pos_btc
        interval_active_ask_volume  = active_tick.ask_price_1 * self.interval_pos_btc
        interval_passive_bid_volume = passive_tick.bid_price_1 * self.interval_pos_btc

        spread_bid_volume = min(active_tick.bid_volume_1,
                                passive_tick.ask_volume_1)
        spread_ask_volume = min(active_tick.ask_volume_1,
                                passive_tick.bid_volume_1)
        spread_interval_bid_volume = min(interval_active_bid_volume,
                                         interval_passive_ask_volume)
        spread_interval_ask_volume = min(interval_active_ask_volume,
                                         interval_passive_bid_volume)

        msg = f"价差盘口，买：{spread_bid_price} ({spread_bid_volume})，卖：{spread_ask_price} ({spread_ask_volume}), 主仓位 {self.active_pos_btc} btc, 被仓位{self.passive_pos_btc} btc"
        self.write_log(msg)

        if abs(self.active_pos_btc) > self.max_pos_btc or abs(self.passive_pos_btc) > self.max_pos_btc:
            self.write_log(f"(BTC)持仓满足最大计划持仓 {self.max_pos_btc} XBT 暂不交易, 主动仓位{self.active_pos_btc} XBT, 合约数量{active_position_data.volume}, 被动仓位 {self.passive_pos_btc} XBT, 合约数量 {passive_position_data.volume}")


        # Sell condition
        if spread_bid_price > self.spread_up:
            self.write_log("套利价差超过上限，满足做空条件")


            if self.is_passive_close == "是" and self.active_pos_btc == 0 and self.passive_pos_btc == 0:
                self.write_log("仅平仓不做正向操作")
                return

            if self.active_pos_btc > -self.max_pos_btc:
                self.write_log("当前持仓小于最大持仓限制，执行卖出操作")

                if self.is_passive_close == "是":
                    left_max_pos_btc = self.active_pos_btc
                else:
                    left_max_pos_btc = self.active_pos_btc + self.max_pos_btc

                left_max_pos_active_bid_volume = active_tick.bid_price_1 * left_max_pos_btc
                left_max_pos_passive_ask_volume = passive_tick.ask_price_1 * left_max_pos_btc
                left_max_pos_volume = min(left_max_pos_active_bid_volume,
                                          left_max_pos_passive_ask_volume)

                volume = min(spread_bid_volume,
                             spread_interval_bid_volume,
                             left_max_pos_volume)

                self.write_log(f"卖出 volume {volume}, 计算值{left_max_pos_volume}, 拆单计算值{spread_interval_bid_volume}")

                self.active_vt_orderid = self.sell(
                    self.active_vt_symbol,
                    active_tick.bid_price_1,
                    volume
                )

        # Buy condition
        elif spread_ask_price < self.spread_down:
            self.write_log("套利价差超过下限，满足做多条件")

            if self.is_active_close == "是" and self.active_pos_btc == 0  and self.passive_pos_btc == 0:
                self.write_log("仅平仓不做反向操作")
                return

            if self.active_pos_btc < self.max_pos_btc:
                self.write_log("当前持仓小于最大持仓限制，执行买入操作")

                if self.is_active_close == "是":
                    left_max_pos_btc = abs(self.active_pos_btc)
                else:
                    left_max_pos_btc = self.max_pos_btc - self.active_pos_btc


                left_max_pos_active_ask_volume = active_tick.ask_price_1 * left_max_pos_btc
                left_max_pos_passive_bid_volume = passive_tick.bid_price_1 * left_max_pos_btc
                left_max_pos_volume = min(left_max_pos_active_ask_volume,
                                          left_max_pos_passive_bid_volume)

                volume = min(spread_ask_volume,
                             spread_interval_ask_volume,
                             left_max_pos_volume)

                self.write_log(f"买入 volume {volume}, 计算值{left_max_pos_volume}, 拆单计算值{spread_interval_ask_volume}")

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

    def hedge_net(self):
        """"""
        tick = self.get_tick(self.passive_vt_symbol)
        volume = -self.active_pos_volume - self.passive_pos_volume
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
