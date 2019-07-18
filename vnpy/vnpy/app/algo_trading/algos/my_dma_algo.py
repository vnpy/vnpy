#!/usr/bin/env python
#-*- coding:utf-8 -*-
############################
#File Name:
#Author: wudi
#Mail: programmerwudi@gmail.com
#Created Time: 2019-07-15 15:06:55
############################

from vnpy.trader.constant import Offset, Direction, OrderType
from vnpy.trader.object import TradeData, OrderData, TickData
from vnpy.trader.engine import BaseEngine

from vnpy.app.algo_trading import AlgoTemplate




class MyDmaAlgo(AlgoTemplate):
    """DMA算法，直接发出限价或者市价委托"""

    templateName = u'MyDMA 直接委托'

    #----------------------------------------------------------------------
    def __init__(self, engine, setting, algoName):
        """Constructor"""
        super(MyDmaAlgo, self).__init__(engine, setting, algoName)

        # 参数，强制类型转换，保证从CSV加载的配置正确
        self.vtSymbol = str(setting['vtSymbol'])
        self.direction = text_type(setting['direction'])
        self.offset = text_type(setting['offset'])
        self.priceType = text_type(setting['priceType'])
        self.price = float(setting['price'])
        self.totalVolume = float(setting['totalVolume'])

    def on_tick(self, tick: TickData):
        """"""
        if not self.vt_orderid:
            if self.direction == Direction.LONG:
                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    self.price,
                    self.volume,
                    self.order_type,
                    self.offset
                )
                
            else:
                self.vt_orderid = self.sell(
                    self.vt_symbol,
                    self.price,
                    self.volume,
                    self.order_type,
                    self.offset
                )
        self.put_variables_event()

    def on_order(self, order: OrderData):
        """"""
        self.traded = order.traded
        self.order_status = order.status

        if not order.is_active():
            self.stop()
        self.put_variables_event()

    def on_trade(self, trade: TradeData):
        """"""
        pass   


