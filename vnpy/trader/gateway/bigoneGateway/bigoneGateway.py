# encoding: UTF-8

'''
vnpy.api.bigone的gateway接入
'''
from __future__ import print_function

import os
import json
import time
import traceback
from datetime import datetime, timedelta
from copy import copy
from math import pow

from vnpy.api.bigone import BigoneRestApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath



# 委托状态类型映射
statusMapReverse = {}
statusMapReverse['PENDING'] = STATUS_NOTTRADED
statusMapReverse['FILLED'] = STATUS_ALLTRADED
statusMapReverse['CANCELED'] = STATUS_CANCELLED

# 方向映射
directionMap = {}
directionMap[DIRECTION_LONG] = 'BID'
directionMap[DIRECTION_SHORT] = 'ASK'
directionMapReverse = {v:k for k,v in directionMap.items()}


########################################################################
class BigoneGateway(VtGateway):
    """Bigone接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName=''):
        """Constructor"""
        super(BigoneGateway, self).__init__(eventEngine, gatewayName)

        self.restApi = RestApi(self)

        self.qryEnabled = False         # 是否要启动循环查询

        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)

    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        try:
            f = file(self.filePath)
        except IOError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'读取连接配置出错，请检查'
            self.onLog(log)
            return

        # 解析json文件
        setting = json.load(f)
        try:
            apiKey = str(setting['apiKey'])
            apiSecret = str(setting['apiSecret'])
            symbols = setting['symbols']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

        # 创建行情和交易接口对象
        self.restApi.connect(apiKey, apiSecret, symbols)

        # 初始化并启动查询
        self.initQuery()

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        pass

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.restApi.sendOrder(orderReq)

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.restApi.cancelOrder(cancelOrderReq)

    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.restApi.close()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.restApi.qryTickers,
                                    self.restApi.qryDepth,
                                    self.restApi.qryAccount,
                                    self.restApi.qryOrder]
            
            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 1         # 查询触发点
            self.qryNextFunction = 0    # 上次运行的查询函数索引

            self.startQuery()

    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.qryCount += 1

        if self.qryCount > self.qryTrigger:
            # 清空倒计时
            self.qryCount = 0

            # 执行查询函数
            function = self.qryFunctionList[self.qryNextFunction]
            function()

            # 计算下次查询函数的索引，如果超过了列表长度，则重新设为0
            self.qryNextFunction += 1
            if self.qryNextFunction == len(self.qryFunctionList):
                self.qryNextFunction = 0

    #----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)

    #----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled


########################################################################
class RestApi(BigoneRestApi):
    """REST API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(RestApi, self).__init__()

        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.localID = 0
        self.tradeID = 0
        
        self.orderDict = {}         # sysID:order
        self.localSysDict = {}      # localID:sysID
        self.reqOrderDict = {}      # reqID:order
        self.cancelDict = {}        # localID:req
        
        self.tickDict = {}
        
    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, symbols):
        """连接服务器"""
        self.init(apiKey, apiSecret)
        self.start()
        
        self.symbols = symbols
        self.writeLog(u'REST API启动成功')
        
        self.qryContract()
    
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)
    
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """"""
        #orderReq.price = 300.0
        #orderReq.volume = 0.01
        
        self.localID += 1
        orderID = str(self.localID)
        vtOrderID = '.'.join([self.gatewayName, orderID])
        
        req = {
            'market_id': orderReq.symbol,
            'side': directionMap[orderReq.direction],
            'price': str(orderReq.price),
            'amount': str(orderReq.volume)
        }
        
        reqid = self.addReq('POST', '/viewer/orders', self.onSendOrder, postdict=req)
        
        # 缓存委托数据对象
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = orderReq.symbol
        order.exchange = EXCHANGE_BIGONE
        order.vtSymbol = '.'.join([order.symbol, order.exchange])
        order.orderID = orderID
        order.vtOrderID = vtOrderID
        order.price = orderReq.price
        order.totalVolume = orderReq.volume
        order.direction = orderReq.direction
        order.status = STATUS_UNKNOWN
        
        self.reqOrderDict[reqid] = order
        
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """"""
        localID = cancelOrderReq.orderID
        
        if localID in self.localSysDict:
            sysID = self.localSysDict[localID]
            path = '/viewer/orders/%s/cancel' %sysID
            self.addReq('POST', path, self.onCancelOrder)
        else:
            self.cancelDict[localID] = cancelOrderReq

    #----------------------------------------------------------------------
    def qryContract(self):
        """"""
        self.addReq('GET', '/markets', self.onQryContract)
    
    #----------------------------------------------------------------------
    def qryTickers(self):
        """"""
        self.addReq('GET', '/tickers', self.onQryTickers)
    
    #----------------------------------------------------------------------
    def qryDepth(self):
        """"""
        for symbol in self.symbols:
            path = '/markets/%s/depth' %symbol
            self.addReq('GET', path, self.onQryDepth)

    #----------------------------------------------------------------------
    def qryOrder(self):
        """"""
        #for symbol in self.symbols:
            #req = {
                #'market_id': symbol,
                #'last': 100
            #}
            #self.addReq('GET', '/viewer/orders', self.onQryOrder, params=req)
        
        req = {
            #'market_id': symbol,
            'last': 100
        }
        self.addReq('GET', '/viewer/orders', self.onQryOrder, params=req)
    
    #----------------------------------------------------------------------
    def qryAccount(self):
        """"""
        self.addReq('GET', '/viewer/accounts', self.onQryAccount)
        
    #----------------------------------------------------------------------
    def onSendOrder(self, data, reqid):
        """"""
        if self.checkError(u'委托', data):
            return
        
        d = data['data']

        order = self.reqOrderDict[reqid]
        localID = order.orderID
        sysID = d['id']
        
        self.localSysDict[localID] = sysID
        self.orderDict[sysID] = order
        
        self.gateway.onOrder(order)
        
        # 发出等待的撤单委托
        if localID in self.cancelDict:
            req = self.cancelDict[localID]
            self.cancelOrder(req)
            del self.cancelDict[localID]
    
    #----------------------------------------------------------------------
    def onCancelOrder(self, data, reqid):
        """"""
        if self.checkError(u'撤单', data):
            return        
    
    #----------------------------------------------------------------------
    def onError(self, code, error):
        """"""
        msg = u'发生异常，错误代码：%s，错误信息：%s' %(code, error)
        self.writeLog(msg)
    
    #----------------------------------------------------------------------
    def onQryOrder(self, data, reqid):
        """"""
        if self.checkError(u'查询委托', data):
            return
        
        for node in data['data']['edges']:
            orderUpdated = False
            tradeUpdated = False
            d = node['node']
            
            # 获取委托对象
            sysID = d['id']
            if sysID in self.orderDict:
                order = self.orderDict[sysID]
            else:
                order = VtOrderData()
                order.gatewayName = self.gatewayName
                
                order.symbol = d['market_id']
                order.exchange = EXCHANGE_BIGONE
                order.vtSymbol = '.'.join([order.symbol, order.exchange])
                
                self.localID += 1
                localID = str(self.localID)
                self.localSysDict[localID] = sysID
                
                order.orderID = localID
                order.vtOrderID = '.'.join([order.gatewayName, order.orderID])
                
                order.direction = directionMapReverse[d['side']]
                order.price = float(d['price'])
                order.totalVolume = float(d['amount'])
                
                self.orderDict[sysID] = order
                orderUpdated = True
        
            # 检查是否委托有变化
            newTradedVolume = float(d['filled_amount'])
            newStatus = statusMapReverse[d['state']]
            
            if newTradedVolume != float(order.tradedVolume) or newStatus != order.status:
                orderUpdated = True
                
            if newTradedVolume != float(order.tradedVolume):
                tradeUpdated = True
                newVolume = newTradedVolume - order.tradedVolume
            
            order.tradedVolume = newTradedVolume
            order.status = newStatus
            
            # 若有更新才推送
            if orderUpdated:
                self.gateway.onOrder(order)        
            
            if tradeUpdated:
                # 推送成交
                trade = VtTradeData()
                trade.gatewayName = order.gatewayName
                
                trade.symbol = order.symbol
                trade.vtSymbol = order.vtSymbol
                
                trade.orderID = order.orderID
                trade.vtOrderID = order.vtOrderID
                
                self.tradeID += 1
                trade.tradeID = str(self.tradeID)
                trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
                
                trade.direction = order.direction
                trade.price = order.price
                trade.volume = newTradedVolume
                trade.tradeTime = datetime.now().strftime('%H:%M:%S')
                
                self.gateway.onTrade(trade)

    #----------------------------------------------------------------------
    def onQryAccount(self, data, reqid):
        """"""
        if self.checkError(u'查询资金', data):
            return
        
        for d in data['data']:
            account = VtAccountData()
            account.gatewayName = self.gatewayName
            
            account.accountID = d['asset_id']
            account.vtAccountID = '.'.join([account.gatewayName, account.accountID])
            account.balance = float(d['balance'])
            account.available = account.balance - float(d['locked_balance'])
            
            self.gateway.onAccount(account)
    
    #----------------------------------------------------------------------
    def onQryContract(self, data, reqid):
        """"""
        if self.checkError(u'查询合约', data):
            return
        
        for d in data['data']:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            
            contract.symbol = d['name']
            contract.exchange = EXCHANGE_BIGONE
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = contract.vtSymbol
            contract.productClass = PRODUCT_SPOT
            contract.priceTick = pow(10, -int(d['quoteScale']))
            contract.size = 1
            
            self.gateway.onContract(contract)   
        
        self.writeLog(u'合约信息查询完成')
    
    #----------------------------------------------------------------------
    def onQryTickers(self, data, reqid):
        """"""
        if self.checkError(u'查询行情', data):
            return
        
        dt = datetime.now()
        date = dt.strftime('%Y%m%d')
        time = dt.strftime('%H:%M:%S')
        
        for d in data['data']:
            symbol = str(d['market_id'])
            tick = self.getTick(symbol)
            
            tick.openPrice = float(d['open'])
            #tick.highPrice = float(d['high'])
            #tick.lowPrice = float(d['low'])
            tick.lastPrice = float(d['close'])
            #tick.volume = float(d['volume'])
            tick.datetime = datetime
            tick.date = date
            tick.time = time
            
            # 只有订阅了深度行情才推送
            if tick.bidPrice1:
                self.gateway.onTick(tick)
    
    #----------------------------------------------------------------------
    def onQryDepth(self, data, reqid):
        """"""
        if self.checkError(u'查询深度', data):
            return
        
        d = data['data']
        symbol = d['market_id']
        
        tick = self.getTick(symbol)
        
        for n, bid in enumerate(d['bids'][:5]):
            tick.__setattr__('bidPrice%s' %(n+1), float(bid['price']))
            tick.__setattr__('bidVolume%s' %(n+1), float(bid['amount']))
        
        for n, ask in enumerate(d['asks'][:5]):
            tick.__setattr__('askPrice%s' %(n+1), float(ask['price']))
            tick.__setattr__('askVolume%s' %(n+1), float(ask['amount']))
        
        tick.datetime = datetime.now()
        tick.date = tick.datetime.strftime('%Y%m%d')
        tick.time = tick.datetime.strftime('%H:%M:%S')        
        
        if tick.lastPrice:
            self.gateway.onTick(tick)
    
    #----------------------------------------------------------------------
    def getTick(self, symbol):
        """"""
        tick = self.tickDict.get(symbol, None)
        
        if not tick:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.symbol = symbol
            tick.exchange = EXCHANGE_BIGONE
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])     
            self.tickDict[symbol] = tick
        
        return tick

    #----------------------------------------------------------------------
    def checkError(self, name, data):
        """"""
        error = data.get('errors', None)
        if not error:
            return False
        
        msg = str(error)
        self.writeLog(u'%s触发错误：%s' %(name, msg))
        return True

#----------------------------------------------------------------------
def printDict(d):
    """"""
    print('-' * 30)
    l = d.keys()
    l.sort()
    for k in l:
        print(k, d[k])
    