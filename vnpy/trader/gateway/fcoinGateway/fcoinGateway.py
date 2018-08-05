# encoding: UTF-8

'''
vnpy.api.fcoin的gateway接入
'''
from __future__ import print_function

import os
import json
import time
import traceback
from datetime import datetime, timedelta
from copy import copy
from math import pow

from vnpy.api.fcoin import FcoinRestApi, FcoinWebsocketApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath

# 委托状态类型映射
statusMapReverse = {}
statusMapReverse['submitted'] = STATUS_NOTTRADED
statusMapReverse['partial_filled'] = STATUS_PARTTRADED
statusMapReverse['partial_canceled'] = STATUS_CANCELLED
statusMapReverse['filled'] = STATUS_ALLTRADED
statusMapReverse['canceled'] = STATUS_CANCELLED
statusMapReverse['pending_cancel'] = STATUS_UNKNOWN

# 方向映射
directionMap = {}
directionMap[DIRECTION_LONG] = 'buy'
directionMap[DIRECTION_SHORT] = 'sell'
directionMapReverse = {v:k for k,v in directionMap.items()}

# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = 'limit'
priceTypeMap[PRICETYPE_MARKETPRICE] = 'market'



########################################################################
class FcoinGateway(VtGateway):
    """FCOIN接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName=''):
        """Constructor"""
        super(FcoinGateway, self).__init__(eventEngine, gatewayName)

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
            symbols = setting['symbols']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

        # 创建行情和交易接口对象
        self.restApi.connect(apiKey, apiSecret, symbols)
        self.wsApi.connect(apiKey, apiSecret, symbols)

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
        self.wsApi.close()
    
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.restApi.qryPosition,
                                    self.restApi.qryOrderSubmitted,
                                    self.restApi.qryOrderPartialFilled,
                                    self.restApi.qryOrderCanceled,
                                    self.restApi.qryOrderFilled,
                                    self.restApi.qryOrderPartialCanceled]
            
            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 3         # 查询触发点
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
class RestApi(FcoinRestApi):
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
            'symbol': orderReq.symbol,
            'side': directionMap[orderReq.direction],
            'type': priceTypeMap[orderReq.priceType],
            'price': orderReq.price,
            'amount': orderReq.volume
        }
        
        reqid = self.addReq('POST', '/orders', self.onSendOrder, postdict=req)
        
        # 缓存委托数据对象
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = orderReq.symbol
        order.exchange = EXCHANGE_FCOIN
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
            path = '/orders/%s/submit-cancel' %sysID
            self.addReq('POST', path, self.onCancelOrder)
        else:
            self.cancelDict[localID] = cancelOrderReq

    #----------------------------------------------------------------------
    def qryContract(self):
        """"""
        self.addReq('GET', '/public/symbols', self.onQryContract)

    #----------------------------------------------------------------------
    def qryOrder(self, state):
        """"""
        for symbol in self.symbols:
            req = {
                'symbol': symbol,
                'states': state,
                'limit': 50
            }
            self.addReq('GET', '/orders', self.onQryOrder, params=req)
    
    #----------------------------------------------------------------------
    def qryOrderSubmitted(self):
        """"""
        self.qryOrder('submitted')
    
    #----------------------------------------------------------------------
    def qryOrderPartialFilled(self):
        """"""
        self.qryOrder('partial_filled')
    
    #----------------------------------------------------------------------
    def qryOrderPartialCanceled(self):
        """"""
        self.qryOrder('partial_canceled')
    
    #----------------------------------------------------------------------
    def qryOrderFilled(self):
        """"""
        self.qryOrder('filled')
        
    #----------------------------------------------------------------------
    def qryOrderCanceled(self):
        """"""
        self.qryOrder('canceled')
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """"""
        self.addReq('GET', '/accounts/balance', self.onQryPosition)
        
    #----------------------------------------------------------------------
    def onSendOrder(self, data, reqid):
        """"""
        if 'msg' in data:
            self.writeLog(data['msg'])
            return
        
        if 'data' in data:
            order = self.reqOrderDict[reqid]
            localID = order.orderID
            sysID = data['data']
            
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
        data['data'].reverse()
        
        for d in data['data']:
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
                order.exchange = EXCHANGE_FCOIN
                order.vtSymbol = '.'.join([order.symbol, order.exchange])
                
                self.localID += 1
                localID = str(self.localID)
                self.localSysDict[localID] = sysID
                
                order.orderID = localID
                order.vtOrderID = '.'.join([order.gatewayName, order.orderID])
                
                order.direction = directionMapReverse[d['side']]
                order.price = float(d['price'])
                order.totalVolume = float(d['amount'])
                
                dt = datetime.fromtimestamp(d['created_at']/1000)
                order.orderTime = dt.strftime('%H:%M:%S')
                
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
    def onQryPosition(self, data, reqid):
        """"""
        for d in data['data']:
            account = VtAccountData()
            account.gatewayName = self.gatewayName
            
            account.accountID = d['currency']
            account.vtAccountID = '.'.join([account.gatewayName, account.accountID])
            account.balance = float(d['balance'])
            account.available = account.balance - float(d['frozen'])
            
            self.gateway.onAccount(account)            
    
    #----------------------------------------------------------------------
    def onQryContract(self, data, reqid):
        """"""
        for d in data['data']:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            
            contract.symbol = d['name']
            contract.exchange = EXCHANGE_FCOIN
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = contract.vtSymbol
            contract.productClass = PRODUCT_SPOT
            contract.priceTick = pow(10, -int(d['price_decimal']))
            contract.size = 1
            
            self.gateway.onContract(contract)   
        
        self.writeLog(u'合约信息查询完成')
    

########################################################################
class WebsocketApi(FcoinWebsocketApi):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(WebsocketApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        
        self.apiKey = ''
        self.apiSecret = ''
        self.symbols = []
        
        self.tickDict = {}
        
    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, symbols):
        """"""
        self.apiKey = apiKey
        self.apiSecret = apiSecret
        self.symbols = symbols
        
        self.start()
    
    #----------------------------------------------------------------------
    def onConnect(self):
        """连接回调"""
        self.writeLog(u'Websocket API连接成功')
        
    #----------------------------------------------------------------------
    def subscribe(self):
        """"""
        l = []
        for symbol in self.symbols:
            l.append('ticker.' + symbol)
            l.append('depth.L20.' + symbol)
            
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.symbol = symbol
            tick.exchange = EXCHANGE_FCOIN
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[symbol] = tick
            
        req = {
            'cmd': 'sub',
            'args': l,
            'id': 1
        }
        self.sendReq(req)
    
    #----------------------------------------------------------------------
    def onData(self, data):
        """数据回调"""
        type_ = data['type']
        if 'hello' in type_:
            self.subscribe()
        elif 'ticker' in type_:
            self.onTick(data)
        elif 'depth' in type_:
            self.onDepth(data)
            
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
    def onTick(self, d):
        """"""
        symbol = d['type'].split('.')[-1]
        tick = self.tickDict[symbol]
        
        ticker = d['ticker']
        tick.openPrice = ticker[6]
        tick.highPrice = ticker[7]
        tick.lowPrice = ticker[8]
        tick.lastPrice = ticker[0]
        tick.volume = ticker[9]
        
        if tick.askPrice1:
            self.gateway.onTick(copy(tick))

    #----------------------------------------------------------------------
    def onDepth(self, d):
        """"""
        symbol = d['type'].split('.')[-1]
        tick = self.tickDict[symbol]  
        
        bids = d['bids']
        asks = d['asks']
        
        tick.bidPrice1 = bids[0]
        tick.bidPrice2 = bids[2]
        tick.bidPrice3 = bids[4]
        tick.bidPrice4 = bids[6]
        tick.bidPrice5 = bids[8]
        
        tick.askPrice1 = asks[0]
        tick.askPrice2 = asks[2]
        tick.askPrice3 = asks[4]
        tick.askPrice4 = asks[6]
        tick.askPrice5 = asks[8]  
        
        tick.bidVolume1 = bids[1]
        tick.bidVolume2 = bids[3]
        tick.bidVolume3 = bids[5]
        tick.bidVolume4 = bids[7]
        tick.bidVolume5 = bids[9]
        
        tick.askVolume1 = asks[1]
        tick.askVolume2 = asks[3]
        tick.askVolume3 = asks[5]
        tick.askVolume4 = asks[7]
        tick.askVolume5 = asks[9]        
        
        tick.datetime = datetime.fromtimestamp(d['ts']/1000)
        tick.date = tick.datetime.strftime('%Y%m%d')
        tick.time = tick.datetime.strftime('%H:%M:%S')
        
        if tick.lastPrice:
            self.gateway.onTick(copy(tick))        


#----------------------------------------------------------------------
def printDict(d):
    """"""
    print('-' * 30)
    l = d.keys()
    l.sort()
    for k in l:
        print(k, d[k])
    