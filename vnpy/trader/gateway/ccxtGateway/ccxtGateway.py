# encoding: UTF-8

'''
ccxt的gateway接入
'''

import os
import json
import time
import traceback
from queue import Queue, Empty
from multiprocessing.dummy import Pool
from datetime import datetime, timedelta
from copy import copy
from math import pow

import ccxt

from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath



# 委托状态类型映射
statusMapReverse = {}
statusMapReverse['open'] = STATUS_NOTTRADED
statusMapReverse['closed'] = STATUS_ALLTRADED
statusMapReverse['canceled'] = STATUS_CANCELLED

# 方向映射
directionMap = {}
directionMap[DIRECTION_LONG] = 'buy'
directionMap[DIRECTION_SHORT] = 'sell'
directionMapReverse = {v:k for k,v in directionMap.items()}

# 类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_MARKETPRICE] = 'market'
priceTypeMap[PRICETYPE_LIMITPRICE] = 'limit'


########################################################################
class CcxtGateway(VtGateway):
    """CCXT接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName=''):
        """Constructor"""
        super(CcxtGateway, self).__init__(eventEngine, gatewayName)

        self.api = CcxtApi(self)

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
            exchange = str(setting['exchange'])
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
        self.api.connect(exchange, apiKey, apiSecret, symbols)

        # 初始化并启动查询
        self.initQuery()

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        pass

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.api.sendOrder(orderReq)

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.api.cancelOrder(cancelOrderReq)

    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.api.close()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.api.qryMarketData,
                                    self.api.qryAccount,
                                    self.api.qryOrder]
            
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
class CcxtApi(object):
    """REST API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(CcxtApi, self).__init__()

        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.api = None
        self.active = False
        self.queue = Queue()
        self.pool = None
        
        self.reqID = 0
        self.localID = 0
        self.tradeID = 0
        
        self.orderDict = {}         # sysID:order
        self.localSysDict = {}      # localID:sysID
        self.reqOrderDict = {}      # reqID:order
        self.cancelDict = {}        # localID:req
        
        self.depthQryDict = {}      # reqID:symbol
        
        self.tickDict = {}
    
    #----------------------------------------------------------------------
    def run(self, i):
        """"""
        while self.active:
            try:
                req = self.queue.get(timeout=1)
                self.processReq(req)
            except Empty:
                pass
    
    #----------------------------------------------------------------------
    def addReq(self, func, args, callback):
        """"""
        self.reqID += 1
        req = (func, args, callback, self.reqID)
        self.queue.put(req)
        return self.reqID
    
    #----------------------------------------------------------------------
    def processReq(self, req):
        """"""
        try:
            func, args, callback, reqID = req
            data = func(*args)
            callback(data, reqID)
        except:
            code = 'api'
            msg = traceback.format_exc()
            self.onError(code, msg)
        
    #----------------------------------------------------------------------
    def connect(self, exchange, apiKey, apiSecret, symbols):
        """连接服务器"""
        self.exchange = exchange.upper()
        self.symbols = symbols
        
        # 初始化CCXT对象
        config = {
            'apiKey': apiKey,
            'secret': apiSecret
        }
        apiClass = ccxt.__getattribute__(exchange)
        self.api = apiClass(config)
        #self.api = ccxt.huobipro()
        
        # 启动线程池
        n = 10
        self.active = True
        self.pool = Pool(n)
        self.pool.map_async(self.run, range(n))
        
        self.writeLog(u'CCXT API（%s）启动成功' %exchange)
        
        # 初始化查询
        self.qryContract()
    
    #----------------------------------------------------------------------
    def close(self):
        """"""
        self.active = False
        if self.pool:
            self.pool.close()
            self.pool.join()
    
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
        self.localID += 1
        orderID = str(self.localID)
        vtOrderID = '.'.join([self.gatewayName, orderID])
        
        req = [
            orderReq.symbol,
            priceTypeMap[orderReq.priceType],
            directionMap[orderReq.direction],
            orderReq.volume,
            orderReq.price
        ]
        
        func = self.api.createOrder
        reqid = self.addReq(func, req, self.onSendOrder)
        
        # 缓存委托数据对象
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = orderReq.symbol
        order.exchange = self.exchange
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
            func = self.api.cancelOrder
            reqid = self.addReq(func, [sysID], self.onCancelOrder)            
        else:
            self.cancelDict[localID] = cancelOrderReq

    #----------------------------------------------------------------------
    def qryContract(self):
        """"""
        func = self.api.fetchMarkets
        self.addReq(func, [], self.onQryContract)
    
    #----------------------------------------------------------------------
    def qryTicker(self):
        """"""
        for symbol in self.symbols:
            func = self.api.fetchTicker
            self.addReq(func, [symbol], self.onQryTicker)
    
    #----------------------------------------------------------------------
    def qryDepth(self):
        """"""
        for symbol in self.symbols:
            func = self.api.fetchOrderBook
            i = self.addReq(func, [symbol], self.onQryDepth)
            self.depthQryDict[i] = symbol

    #----------------------------------------------------------------------
    def qryOrder(self):
        """"""
        for symbol in self.symbols:
            func = self.api.fetchOrders
            i = self.addReq(func, [symbol], self.onQryOrder)
    
    #----------------------------------------------------------------------
    def qryAccount(self):
        """"""
        func = self.api.fetchBalance
        self.addReq(func, [], self.onQryAccount)
        
    #----------------------------------------------------------------------
    def onSendOrder(self, data, reqid):
        """"""
        order = self.reqOrderDict[reqid]
        localID = order.orderID
        sysID = data['id']
        
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
        pass
        
    #----------------------------------------------------------------------
    def onError(self, code, error):
        """"""
        msg = u'发生异常，错误代码：%s，错误信息：%s' %(code, error)
        self.writeLog(msg)
    
    #----------------------------------------------------------------------
    def onQryOrder(self, data, reqid):
        """"""
        for d in data:
            orderUpdated = False
            tradeUpdated = False
            
            # 获取委托对象
            sysID = d['id']
            if sysID in self.orderDict:
                order = self.orderDict[sysID]
            else:
                order = VtOrderData()
                order.gatewayName = self.gatewayName
                
                order.symbol = d['symbol']
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
                
                dt = datetime.fromtimestamp(d['timestamp']/1000)
                order.orderTime = dt.strftime('%H:%M:%S')
                
                self.orderDict[sysID] = order
                orderUpdated = True
        
            # 检查是否委托有变化
            newTradedVolume = float(d['filled'])
            newStatus = statusMapReverse[d['status']]
            
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
        total = data['total']
        used = data['used']
        free = data['free']

        for currency in total.keys(): 
            account = VtAccountData()
            account.gatewayName = self.gatewayName
            
            account.accountID = currency
            account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
            
            account.balance = total[currency]
            account.available = free[currency]
            
            self.gateway.onAccount(account)        
    
    #----------------------------------------------------------------------
    def onQryContract(self, data, reqid):
        """"""
        for d in data:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            
            contract.symbol = d['symbol']
            contract.exchange = self.exchange
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = contract.vtSymbol
            contract.productClass = PRODUCT_SPOT
            contract.priceTick = pow(10, -int(d['precision']['price']))
            contract.size = 1
            
            self.gateway.onContract(contract)   
        
        self.writeLog(u'合约信息查询完成')
    
    #----------------------------------------------------------------------
    def onQryTicker(self, data, reqid):
        """"""
        symbol = data['symbol']
        tick = self.getTick(symbol)
        
        tick.openPrice = float(data['open'])
        tick.highPrice = float(data['high'])
        tick.lowPrice = float(data['low'])
        tick.lastPrice = float(data['close'])
        tick.volume = float(data['quoteVolume'])
        
        if data['timestamp']:
            tick.datetime = datetime.fromtimestamp(data['timestamp']/1000)
        else:
            tick.datetime = datetime.now()        
        tick.date = tick.datetime.strftime('%Y%m%d')
        tick.time = tick.datetime.strftime('%H:%M:%S')
        
        # 只有订阅了深度行情才推送
        if tick.bidPrice1:
            self.gateway.onTick(tick)
    
    #----------------------------------------------------------------------
    def onQryDepth(self, data, reqid):
        """"""
        symbol = self.depthQryDict.pop(reqid)
        tick = self.getTick(symbol)
        
        for n, bid in enumerate(data['bids'][:5]):
            tick.__setattr__('bidPrice%s' %(n+1), float(bid[0]))
            tick.__setattr__('bidVolume%s' %(n+1), float(bid[1]))
        
        for n, ask in enumerate(data['asks'][:5]):
            tick.__setattr__('askPrice%s' %(n+1), float(ask[0]))
            tick.__setattr__('askVolume%s' %(n+1), float(ask[1]))
        
        if data['timestamp']:
            tick.datetime = datetime.fromtimestamp(data['timestamp']/1000)
        else:
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
            tick.exchange = self.exchange
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])     
            self.tickDict[symbol] = tick
        
        return tick
    
    #----------------------------------------------------------------------
    def qryMarketData(self):
        """"""
        self.qryDepth()
        self.qryTicker()
        