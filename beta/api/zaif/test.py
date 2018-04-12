# encoding: utf-8

from __future__ import absolute_import
from .vnzaif import *

def testTrade():
    """测试交易"""
    accessKey = '你的accessKey'
    secretKey = '你的secretKey'
    
    # 创建API对象并初始化
    api = TradeApi()
    api.DEBUG = True
    api.init(accessKey, secretKey)
    
    # 查询账户，测试通过
    #api.get_info()

    api.get_info2()
    

    # 查询委托，测试通过
    #api.active_orders( currency_pair = SYMBOL_BTCJPY )
    
    # 阻塞
    input()    


def testData():
    """测试行情接口"""
    api = DataApi()
    
    api.init(0.5 , 1)
    
    # 订阅成交推送，测试通过
    api.subscribeTick(SYMBOL_BTCJPY)
    
    # 订阅最新价推送，测试通过
    #api.subscribeLast(SYMBOL_BTCJPY)

    # 订阅深度推送，测试通过
    api.subscribeDepth(SYMBOL_BTCJPY, 1)

    api.subscribeTrades(SYMBOL_BTCJPY)

    # 查询K线数据，测试通过
    #data = api.getKline(SYMBOL_BTCJPY, PERIOD_1MIN, 100)
    #print data
    
    input()
    
    
if __name__ == '__main__':
    #testTrade()
    #testTrade()
    testData()