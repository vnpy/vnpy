# encoding: UTF-8

from __future__ import print_function
import os
from time import sleep

from six.moves import input

from vnxtptrader import *


#----------------------------------------------------------------------
def printDict(d):
    """"""
    print('-' * 50)
    l = d.keys()
    l.sort()
    for k in l:
        print(k, d[k])


########################################################################
class TestApi(TraderApi):
    """"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(TestApi, self).__init__()
    
    #----------------------------------------------------------------------
    def onDisconnected(self, reason):
        """"""
        print('-' * 30)
        print('onDisconnected')
        print(reason)
        
    #----------------------------------------------------------------------
    def onError(self, data):
        """"""
        print('-' * 30)
        print('onError')
        printDict(data)
        
    #----------------------------------------------------------------------
    def onOrderEvent(self, data, error):
        """"""
        print('-' * 30)
        print('onOrderEvent')
        printDict(data)
        printDict(error)
        
    #----------------------------------------------------------------------
    def onTradeEvent(self, data):
        """"""
        print('-' * 30)
        print('onTradeEvent')
        printDict(data)
        
    #----------------------------------------------------------------------
    def onCancelOrderError(self, data, error):
        """"""
        print('-' * 30)
        print('onCancelOrderError')
        printDict(data)
        printDict(error)
        
    #----------------------------------------------------------------------
    def onQueryOrder(self, data, error, reqid, last):
        """"""
        print('-' * 30)
        print('onQueryOrder')
        printDict(data)
        printDict(error) 
        print(reqid)
        print(last)
        
    #----------------------------------------------------------------------
    def onQueryTrade(self, data, error, reqid, last):
        """"""
        print('-' * 30)
        print('onQueryTrade')
        printDict(data)
        printDict(error)
        print(reqid)
        print(last)        
        
    #----------------------------------------------------------------------
    def onQueryPosition(self, data, error, reqid, last):
        """"""
        print('-' * 30)
        print('onQueryPosition')
        printDict(data)
        printDict(error)
        print(reqid)
        print(last)        
        
    #----------------------------------------------------------------------
    def onQueryAsset(self, data, error, reqid, last):
        """"""
        print('-' * 30)
        print('onQueryAsset')
        printDict(data)
        printDict(error)
        print(reqid)
        print(last)        



if __name__ == '__main__':
    ip = '120.27.164.69'
    port = 6001
    user = ''
    password = ''
    reqid = 0
    
    # 创建API并初始化
    api = TestApi()
    
    api.createTraderApi(1, os.getcwd())
    api.subscribePublicTopic(0)
    api.setSoftwareCode("vnpy")
    api.setSoftwareVersion("test")
    
    # 登录
    session = api.login(ip, port, user, password, 1)
    print('login result', session)

    # 调用同步函数查询一些信息
    print('trading day is:', api.getTradingDay())
    print('api version is:', api.getApiVersion())
    print('last error is:', api.getApiLastError())
    
    # 查询资产
    sleep(2)
    reqid += 1
    n = api.queryAsset(session, reqid)
    
    # 查询持仓
    sleep(2)
    reqid += 1
    n = api.queryPosition('', session, reqid)

    # 查询委托
    sleep(2)
    reqid += 1
    n = api.queryOrders({}, session, reqid)
    
    # 查询成交
    sleep(2)
    reqid += 1
    n = api.queryTrades({}, session, reqid)
    
    # 委托
    sleep(2)
    order = {}
    order['ticker'] = '000001'  # 平安银行
    order['market'] = 1         # 深圳A股
    order['price'] = 8.5
    order['quantity'] = 100
    order['price_type'] = 1     # 限价单
    order['side'] = 1           # 买
    
    orderid = api.insertOrder(order,session)
    
    # 撤单
    sleep(2)
    cancelid = api.cancelOrder(orderid, session)
    
    # 登出
    sleep(5)
    print('logout:', api.logout(session))
    
    # 阻塞
    input()
