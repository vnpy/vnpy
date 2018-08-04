# encoding: UTF-8

'''
vnpy.api.bitmex的gateway接入
'''
from __future__ import print_function

import os
import json
import hashlib
import hmac
import time
import traceback
from datetime import datetime, timedelta
from copy import copy
from math import pow

from vnpy.api.bitmex import BitmexRestApi, BitmexWebsocketApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath

# 委托状态类型映射
statusMapReverse = {}
statusMapReverse['New'] = STATUS_NOTTRADED
statusMapReverse['Partially filled'] = STATUS_PARTTRADED
statusMapReverse['Filled'] = STATUS_ALLTRADED
statusMapReverse['Canceled'] = STATUS_CANCELLED
statusMapReverse['Rejected'] = STATUS_REJECTED

# 方向映射
directionMap = {}
directionMap[DIRECTION_LONG] = 'Buy'
directionMap[DIRECTION_SHORT] = 'Sell'
directionMapReverse = {v:k for k,v in directionMap.items()}

# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = 'Limit'
priceTypeMap[PRICETYPE_MARKETPRICE] = 'Market'



########################################################################
class BitmexGateway(VtGateway):
    """Bitfinex接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName=''):
        """Constructor"""
        super(BitmexGateway, self).__init__(eventEngine, gatewayName)

        self.restApi = RestApi(self)
        self.wsApi = WebsocketApi(self)

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
            sessionCount = int(setting['sessionCount'])
            symbols = setting['symbols']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

        # 创建行情和交易接口对象
        self.restApi.connect(apiKey, apiSecret, sessionCount)
        self.wsApi.connect(apiKey, apiSecret, symbols)

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
        self.wsApi.close()
    
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.queryAccount]

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
class RestApi(BitmexRestApi):
    """REST API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(RestApi, self).__init__()

        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.orderId = 1000000
        self.date = int(datetime.now().strftime('%y%m%d%H%M%S')) * self.orderId
        
    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, sessionCount):
        """连接服务器"""
        self.init(apiKey, apiSecret)
        self.start(sessionCount)
        
        self.writeLog(u'REST API启动成功')
    
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
        self.orderId += 1
        orderId = self.date + self.orderId
        vtOrderID = '.'.join([self.gatewayName, str(orderId)])
        
        req = {
            'symbol': orderReq.symbol,
            'side': directionMap[orderReq.direction],
            'ordType': priceTypeMap[orderReq.priceType],            
            'price': orderReq.price,
            'orderQty': orderReq.volume,
            'clOrdID': str(orderId)
        }
        self.addReq('POST', '/order', self.onSendOrder, postdict=req)
        
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """"""
        orderID = cancelOrderReq.orderID
        if orderID.isdigit():
            req = {'clOrdID': orderID}
        else:
            req = {'orderID': orderID}
        
        self.addReq('DELETE', '/order', self.onCancelOrder, params=req)

    #----------------------------------------------------------------------
    def onSendOrder(self, data, reqid):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onCancelOrder(self, data, reqid):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onError(self, code, error):
        """"""
        e = VtErrorData()
        e.errorID = code
        e.errorID = error
        self.gateway.onError(e)
        

########################################################################
class WebsocketApi(BitmexWebsocketApi):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(WebsocketApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        
        self.apiKey = ''
        self.apiSecret = ''
        
        self.callbackDict = {
            'trade': self.onTick,
            'orderBook10': self.onDepth,
            'execution': self.onTrade,
            'order': self.onOrder,
            'position': self.onPosition,
            'margin': self.onAccount,
            'instrument': self.onContract
        }
        
        self.tickDict = {}
        self.accountDict = {}
        self.orderDict = {}
        self.tradeSet = set()
        
    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, symbols):
        """"""
        self.apiKey = apiKey
        self.apiSecret = apiSecret
        
        for symbol in symbols:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.symbol = symbol
            tick.exchange = EXCHANGE_BITMEX
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[symbol] = tick
            
        self.start()
    
    #----------------------------------------------------------------------
    def onConnect(self):
        """连接回调"""
        self.writeLog(u'Websocket API连接成功')
        self.authenticate()
    
    #----------------------------------------------------------------------
    def onData(self, data):
        """数据回调"""
        if 'request' in data:
            req = data['request']
            success = data['success']
            
            if success:
                if req['op'] == 'authKey':
                    self.writeLog(u'Websocket API验证授权成功')
                    self.subscribe()
            
        elif 'table' in data:
            name = data['table']
            callback = self.callbackDict[name]
            
            if isinstance(data['data'], list):
                for d in data['data']:
                    callback(d)
            else:
                callback(data['data'])
            
            #if data['action'] == 'update' and data['table'] != 'instrument':
                #callback(data['data'])
            #elif data['action'] == 'partial':
                #for d in data['data']:
                    #callback(d)

    
    #----------------------------------------------------------------------
    def onError(self, msg):
        """错误回调"""
        self.writeLog(msg)
    
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)    

    #----------------------------------------------------------------------
    def authenticate(self):
        """"""
        expires = int(time.time())
        method = 'GET'
        path = '/realtime'
        msg = method + path + str(expires)
        signature = hmac.new(self.apiSecret, msg, digestmod=hashlib.sha256).hexdigest()
        
        req = {
            'op': 'authKey', 
            'args': [self.apiKey, expires, signature]
        }
        self.sendReq(req)

    #----------------------------------------------------------------------
    def subscribe(self):
        """"""
        req = {
            'op': 'subscribe',
            'args': ['instrument', 'trade', 'orderBook10', 'execution', 'order', 'position', 'margin']
        }
        self.sendReq(req)
    
    #----------------------------------------------------------------------
    def onTick(self, d):
        """"""
        symbol = d['symbol']

        tick = self.tickDict.get(symbol, None)
        if not tick:
            return
        
        tick.lastPrice = d['price']
        
        date, time = str(d['timestamp']).split('T')
        tick.date = date.replace('-', '')
        tick.time = time.replace('Z', '')
        
        self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def onDepth(self, d):
        """"""
        symbol = d['symbol']
        tick = self.tickDict.get(symbol, None)
        if not tick:
            return
        
        for n, buf in enumerate(d['bids'][:5]):
            price, volume = buf
            tick.__setattr__('bidPrice%s' %(n+1), price)
            tick.__setattr__('bidVolume%s' %(n+1), volume)
        
        for n, buf in enumerate(d['asks'][:5]):
            price, volume = buf
            tick.__setattr__('askPrice%s' %(n+1), price)
            tick.__setattr__('askVolume%s' %(n+1), volume)                
        
        date, time = str(d['timestamp']).split('T')
        tick.date = date.replace('-', '')
        tick.time = time.replace('Z', '')
        
        self.gateway.onTick(tick)
    
    #----------------------------------------------------------------------
    def onTrade(self, d):
        """"""
        if not d['lastQty']:
            return
        
        tradeID = d['execID']
        if tradeID in self.tradeSet:
            return
        self.tradeSet.add(tradeID)
        
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        trade.symbol = d['symbol']
        trade.exchange = EXCHANGE_BITMEX
        trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
        if d['clOrdID']:
            orderID = d['clOrdID']
        else:
            orderID = d['orderID']
        trade.orderID = orderID
        trade.vtOrderID = '.'.join([trade.gatewayName, trade.orderID])
        
        
        trade.tradeID = tradeID
        trade.vtTradeID = '.'.join([trade.gatewayName, trade.tradeID])
        
        trade.direction = directionMapReverse[d['side']]
        trade.price = d['lastPx']
        trade.volume = d['lastQty']
        trade.tradeTime = d['timestamp'][0:10].replace('-', '')
        
        self.gateway.onTrade(trade)
    
    #----------------------------------------------------------------------
    def onOrder(self, d):
        """"""
        if 'ordStatus' not in d:
            return
        
        sysID = d['orderID']
        if sysID in self.orderDict:
            order = self.orderDict[sysID]
        else:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            
            order.symbol = d['symbol']
            order.exchange = EXCHANGE_BITMEX
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            if d['clOrdID']:
                orderID = d['clOrdID']
            else:
                orderID = sysID
            order.orderID = orderID
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.direction = directionMapReverse[d['side']]
            
            if d['price']:
                order.price = d['price']
                
            order.totalVolume = d['orderQty']
            order.orderTime = d['timestamp'][0:10].replace('-', '')
    
            self.orderDict[sysID] = order
        
        order.tradedVolume = d.get('cumQty', order.tradedVolume)
        order.status = statusMapReverse.get(d['ordStatus'], STATUS_UNKNOWN)
    
        self.gateway.onOrder(order)        

    #----------------------------------------------------------------------
    def onPosition(self, d):
        """"""
        pos = VtPositionData()
        pos.gatewayName = self.gatewayName
        
        pos.symbol = d['symbol']
        pos.exchange = EXCHANGE_BITMEX
        pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])
        
        pos.direction = DIRECTION_NET
        pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
        pos.position = d['currentQty']
        pos.frozen = 0      # 期货没有冻结概念，会直接反向开仓
        
        self.gateway.onPosition(pos)        
    
    #----------------------------------------------------------------------
    def onAccount(self, d):
        """"""
        accoundID = str(d['account'])
        
        if accoundID in self.accountDict:
            account = self.accountDict[accoundID]
        else:
            account = VtAccountData()
            account.gatewayName = self.gatewayName
        
            account.accountID = accoundID
            account.vtAccountID = '.'.join([account.gatewayName, account.accountID])
            
            self.accountDict[accoundID] = account
        
        account.balance = d.get('marginBalance', account.balance)
        account.available = d.get('availableMargin', account.available)
        account.closeProfit = d.get('realisedPnl', account.closeProfit)
        account.positionProfit = d.get('unrealisedPnl', account.positionProfit)
        
        self.gateway.onAccount(account)        

    #----------------------------------------------------------------------
    def onContract(self, d):
        """"""
        if 'tickSize' not in d:
            return
        
        contract = VtContractData()
        contract.gatewayName = self.gatewayName
        
        contract.symbol = d['symbol']
        contract.exchange = EXCHANGE_BITMEX
        contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
        contract.name = contract.vtSymbol
        contract.productClass = PRODUCT_FUTURES
        contract.priceTick = d['tickSize']
        contract.size = d['multiplier']
        
        self.gateway.onContract(contract)        


#----------------------------------------------------------------------
def printDict(d):
    """"""
    print('-' * 30)
    l = d.keys()
    l.sort()
    for k in l:
        print(k, d[k])
    