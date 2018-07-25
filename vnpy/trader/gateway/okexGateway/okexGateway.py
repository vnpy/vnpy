# encoding: UTF-8

'''
vnpy.api.okex的gateway接入

Contributor：ipqhjjybj 大佳
'''
from __future__ import print_function


import os
import json
from datetime import datetime
from time import sleep
from copy import copy
from threading import Condition
from queue import Queue, Empty
from threading import Thread
from time import sleep

from vnpy.api.okex import OkexSpotApi, OKEX_SPOT_HOST
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath

# 价格类型映射
# 买卖类型： 限价单（buy/sell） 市价单（buy_market/sell_market）
priceTypeMap = {}
priceTypeMap['buy'] = (DIRECTION_LONG, PRICETYPE_LIMITPRICE)
priceTypeMap['buy_market'] = (DIRECTION_LONG, PRICETYPE_MARKETPRICE)
priceTypeMap['sell'] = (DIRECTION_SHORT, PRICETYPE_LIMITPRICE)
priceTypeMap['sell_market'] = (DIRECTION_SHORT, PRICETYPE_MARKETPRICE)
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 委托状态印射
statusMap = {}
statusMap[-1] = STATUS_CANCELLED
statusMap[0] = STATUS_NOTTRADED
statusMap[1] = STATUS_PARTTRADED
statusMap[2] = STATUS_ALLTRADED
statusMap[4] = STATUS_UNKNOWN


########################################################################
class OkexGateway(VtGateway):
    """OKEX交易接口"""
    
    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='OKEX'):
        """Constructor"""
        super(OkexGateway, self).__init__(eventEngine, gatewayName)
        
        self.spotApi = SpotApi(self)     
        # self.api_contract = Api_contract(self)
        
        self.leverage = 0
        self.connected = False
        
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)     

    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
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
            secretKey = str(setting['secretKey'])
            trace = setting['trace']
            symbols = setting['symbols']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 初始化接口
        self.spotApi.init(apiKey, secretKey, trace, symbols)

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        pass
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.spotApi.sendOrder(orderReq)

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.spotApi.cancelOrder(cancelOrderReq)
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        pass

    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.spotApi.spotUserInfo()
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.spotApi.close()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryPosition]
            
            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 2         # 查询触发点
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
class SpotApi(OkexSpotApi):
    """OKEX的API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(SpotApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.cbDict = {}
        self.tickDict = {}
        self.orderDict = {}

        self.channelSymbolMap = {}
        
        self.localNo = 0                # 本地委托号
        self.localNoQueue = Queue()     # 未收到系统委托号的本地委托号队列
        self.localNoDict = {}           # key为本地委托号，value为系统委托号
        self.localOrderDict = {}        # key为本地委托号, value为委托对象
        self.orderIdDict = {}           # key为系统委托号，value为本地委托号
        self.cancelDict = {}            # key为本地委托号，value为撤单请求

        self.recordOrderId_BefVolume = {}       # 记录的之前处理的量

        self.cache_some_order = {}
        self.tradeID = 0

        self.registerSymbolPairArray = set([])

    #----------------------------------------------------------------------
    def onMessage(self, data):
        """信息推送""" 
        channel = data.get('channel', '')
        if not channel:
            return

        if channel in self.cbDict:
            callback = self.cbDict[channel]
            callback(data)

    #----------------------------------------------------------------------
    def onError(self, data):
        """错误推送"""
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        error.errorMsg = str(data)
        self.gateway.onError(error)
        
    #----------------------------------------------------------------------
    def onClose(self):
        """接口断开"""
        self.gateway.connected = False
        self.writeLog(u'服务器连接断开')
    
    #----------------------------------------------------------------------
    def onOpen(self):       
        """连接成功"""
        self.gateway.connected = True
        self.writeLog(u'服务器连接成功')
        
        self.login()
        
        # 推送合约数据
        for symbol in self.symbols:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            contract.symbol = symbol
            contract.exchange = EXCHANGE_OKEX
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = symbol
            contract.size = 0.00001
            contract.priceTick = 0.00001
            contract.productClass = PRODUCT_SPOT
            self.gateway.onContract(contract)
    
    #----------------------------------------------------------------------
    def initCallback(self):
        """初始化回调函数"""
        for symbol in self.symbols:
            # channel和symbol映射
            self.channelSymbolMap["ok_sub_spot_%s_ticker" % symbol] = symbol
            self.channelSymbolMap["ok_sub_spot_%s_depth_5" % symbol] = symbol
            
            # channel和callback映射
            self.cbDict["ok_sub_spot_%s_ticker" % symbol] = self.onTicker
            self.cbDict["ok_sub_spot_%s_depth_5" % symbol] = self.onDepth
            self.cbDict["ok_sub_spot_%s_order" % symbol] = self.onSubSpotOrder
            self.cbDict["ok_sub_spot_%s_balance" % symbol] = self.onSubSpotBalance

        self.cbDict['ok_spot_userinfo'] = self.onSpotUserInfo
        self.cbDict['ok_spot_orderinfo'] = self.onSpotOrderInfo
        self.cbDict['ok_spot_order'] = self.onSpotOrder
        self.cbDict['ok_spot_cancel_order'] = self.onSpotCancelOrder
        self.cbDict['login'] = self.onLogin
    
    #----------------------------------------------------------------------
    def onLogin(self, data):
        """"""
        self.writeLog(u'服务器登录成功')
        
        # 查询持仓
        self.spotUserInfo()
        
        # 订阅推送
        for symbol in self.symbols:
            self.subscribe(symbol)
        
    #----------------------------------------------------------------------
    def onTicker(self, data):
        """"""
        channel = data['channel']
        symbol = self.channelSymbolMap[channel]
        
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.symbol = symbol
            tick.exchange = EXCHANGE_OKEX
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            tick.gatewayName = self.gatewayName
            
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]
        
        d = data['data']
        tick.highPrice = float(d['high'])
        tick.lowPrice = float(d['low'])
        tick.lastPrice = float(d['last'])
        tick.volume = float(d['vol'].replace(',', ''))
        tick.date, tick.time = self.generateDateTime(d['timestamp'])
        
        if tick.bidPrice1:
            newtick = copy(tick)
            self.gateway.onTick(newtick)
    
    #----------------------------------------------------------------------
    def onDepth(self, data):
        """"""
        channel = data['channel']
        symbol = self.channelSymbolMap[channel]

        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.symbol = symbol
            tick.exchange = EXCHANGE_OKEX
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            tick.gatewayName = self.gatewayName

            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]
        
        d = data['data']
        
        tick.bidPrice1, tick.bidVolume1 = d['bids'][0]
        tick.bidPrice2, tick.bidVolume2 = d['bids'][1]
        tick.bidPrice3, tick.bidVolume3 = d['bids'][2]
        tick.bidPrice4, tick.bidVolume4 = d['bids'][3]
        tick.bidPrice5, tick.bidVolume5 = d['bids'][4]
        
        tick.askPrice1, tick.askVolume1 = d['asks'][-1]
        tick.askPrice2, tick.askVolume2 = d['asks'][-2]
        tick.askPrice3, tick.askVolume3 = d['asks'][-3]
        tick.askPrice4, tick.askVolume4 = d['asks'][-4]
        tick.askPrice5, tick.askVolume5 = d['asks'][-5]     
        
        tick.bidPrice1 = float(tick.bidPrice1)
        tick.bidPrice2 = float(tick.bidPrice2)
        tick.bidPrice3 = float(tick.bidPrice3)
        tick.bidPrice4 = float(tick.bidPrice4)
        tick.bidPrice5 = float(tick.bidPrice5)
        tick.askPrice1 = float(tick.askPrice1)
        tick.askPrice2 = float(tick.askPrice2)
        tick.askPrice3 = float(tick.askPrice3)
        tick.askPrice4 = float(tick.askPrice4)
        tick.askPrice5 = float(tick.askPrice5)   
        
        tick.bidVolume1 = float(tick.bidVolume1)
        tick.bidVolume2 = float(tick.bidVolume2)
        tick.bidVolume3 = float(tick.bidVolume3)
        tick.bidVolume4 = float(tick.bidVolume4)
        tick.bidVolume5 = float(tick.bidVolume5)
        tick.askVolume1 = float(tick.askVolume1)
        tick.askVolume2 = float(tick.askVolume2)
        tick.askVolume3 = float(tick.askVolume3)
        tick.askVolume4 = float(tick.askVolume4)
        tick.askVolume5 = float(tick.askVolume5)          
        
        tick.date, tick.time = self.generateDateTime(d['timestamp'])
        
        if tick.lastPrice:
            newtick = copy(tick)
            self.gateway.onTick(newtick)
    
    #----------------------------------------------------------------------        
    def onSpotOrder(self, data):
        """"""
        # 如果委托失败，则通知委托被拒单的信息
        if self.checkDataError(data):
            try:
                localNo = self.localNoQueue.get_nowait()
            except Empty:
                return
            
            order = self.localOrderDict[localNo]
            order.status = STATUS_REJECTED
            self.gateway.onOrder(order)
    
    #----------------------------------------------------------------------
    def onSpotCancelOrder(self, data):
        """"""
        self.checkDataError(data)
        
    #----------------------------------------------------------------------
    def onSpotUserInfo(self, data):
        """现货账户资金推送"""
        if self.checkDataError(data):
            return
        
        funds = data['data']['info']['funds']
        free = funds['free']
        freezed = funds['freezed']
        
        # 持仓信息
        for symbol in free.keys():
            frozen = float(freezed[symbol])
            available = float(free[symbol])
            
            if frozen or available:
                account = VtAccountData()
                account.gatewayName = self.gatewayName
                
                account.accountID = symbol
                account.vtAccountID = '.'.join([account.gatewayName, account.accountID])
                account.balance = frozen + available
                account.available = available
                
                self.gateway.onAccount(account)                      
        
        self.writeLog(u'持仓信息查询成功')
        
        # 查询委托
        for symbol in self.symbols:
            self.spotOrderInfo(symbol, '-1')        
            
    #----------------------------------------------------------------------
    def onSpotOrderInfo(self, data):
        """委托信息查询回调"""
        if self.checkDataError(data):
            return
        
        rawData = data['data']
        
        for d in rawData['orders']:
            self.localNo += 1
            localNo = str(self.localNo)
            orderId = str(d['order_id'])
            
            self.localNoDict[localNo] = orderId
            self.orderIdDict[orderId] = localNo
            
            if orderId not in self.orderDict:
                order = VtOrderData()
                order.gatewayName = self.gatewayName
                
                order.symbol = d['symbol']
                order.exchange = EXCHANGE_OKEX
                order.vtSymbol = '.'.join([order.symbol, order.exchange])
    
                order.orderID = localNo
                order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
                
                order.price = d['price']
                order.totalVolume = d['amount']
                order.direction, priceType = priceTypeMap[d['type']]
                date, order.orderTime = self.generateDateTime(d['create_date'])
                
                self.orderDict[orderId] = order
            else:
                order = self.orderDict[orderId]
                
            order.tradedVolume = d['deal_amount']
            order.status = statusMap[d['status']]            
            
            self.gateway.onOrder(copy(order))

    #----------------------------------------------------------------------
    def onSubSpotOrder(self, data):
        """交易数据"""
        rawData = data["data"]
        orderId = str(rawData['orderId'])  
        
        # 获取本地委托号
        if orderId in self.orderIdDict:
            localNo = self.orderIdDict[orderId]
        else:
            try:
                localNo = self.localNoQueue.get_nowait()
            except Empty:
                self.localNo += 1
                localNo = str(self.localNo)
        
        self.localNoDict[localNo] = orderId
        self.orderIdDict[orderId] = localNo        

        # 获取委托对象
        if orderId in self.orderDict:
            order = self.orderDict[orderId]
        else:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            order.symbol = rawData['symbol']
            order.exchange = EXCHANGE_OKEX
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            order.orderID = localNo
            order.vtOrderID = '.'.join([self.gatewayName, localNo])
            order.direction, priceType = priceTypeMap[rawData['tradeType']]
            order.price = float(rawData['tradeUnitPrice'])
            order.totalVolume = float(rawData['tradeAmount'])
            date, order.orderTime = self.generateDateTime(rawData['createdDate'])
        
        lastTradedVolume = order.tradedVolume
        
        order.status = statusMap[rawData['status']]
        order.tradedVolume = float(rawData['completedTradeAmount'])
        self.gateway.onOrder(copy(order))
        
        # 成交信息
        if order.tradedVolume > lastTradedVolume:
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
    
            trade.symbol = order.symbol
            trade.exchange = order.exchange
            trade.vtSymbol = order.vtSymbol
            
            self.tradeID += 1
            trade.tradeID = str(self.tradeID)
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
            
            trade.orderID = order.orderID
            trade.vtOrderID = order.vtOrderID
            
            trade.direction = order.direction
            trade.price = float(rawData['averagePrice'])
            trade.volume = order.tradedVolume - lastTradedVolume
            
            trade.tradeTime = datetime.now().strftime('%H:%M:%S')
            self.gateway.onTrade(trade)
        
        # 撤单
        if localNo in self.cancelDict:
            req = self.cancelDict[localNo]
            self.spotCancel(req)
            del self.cancelDict[localNo]        

    #----------------------------------------------------------------------        
    def onSubSpotBalance(self, data):
        """"""
        rawData = data['data']
        free = rawData['info']['free']
        freezed = rawData['info']['freezed']
        
        for symbol in free.keys():            
            account = VtAccountData()
            account.gatewayName = self.gatewayName
            
            account.accountID = symbol
            account.vtAccountID = '.'.join([account.gatewayName, account.accountID])
            account.available = float(free[symbol])
            account.balance = account.available + float(freezed[symbol])
            
            self.gateway.onAccount(account)                   
    
    #----------------------------------------------------------------------
    def init(self, apiKey, secretKey, trace, symbols):
        """初始化接口"""
        self.symbols = symbols
        self.initCallback()
        self.connect(OKEX_SPOT_HOST, apiKey, secretKey, trace)
        self.writeLog(u'接口初始化成功')

    #----------------------------------------------------------------------
    def sendOrder(self, req):
        """发单"""
        type_ = priceTypeMapReverse[(req.direction, req.priceType)]
        result = self.spotOrder(req.symbol, type_, str(req.price), str(req.volume))
        
        # 若请求失败，则返回空字符串委托号
        if not result:
            return ''
        
        # 本地委托号加1，并将对应字符串保存到队列中，返回基于本地委托号的vtOrderID
        self.localNo += 1
        self.localNoQueue.put(str(self.localNo))
        vtOrderID = '.'.join([self.gatewayName, str(self.localNo)])
        
        # 缓存委托信息
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        
        order.symbol = req.symbol
        order.exchange = EXCHANGE_OKEX
        order.vtSymbol = '.'.join([order.symbol, order.exchange])
        order.orderID= str(self.localNo)
        order.vtOrderID = vtOrderID
        order.direction = req.direction
        order.price = req.price
        order.totalVolume = req.volume
        
        self.localOrderDict[str(self.localNo)] = order

        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, req):
        """撤单"""
        localNo = req.orderID
        if localNo in self.localNoDict:
            orderID = self.localNoDict[localNo]
            self.spotCancelOrder(req.symbol, orderID)
        else:
            # 如果在系统委托号返回前客户就发送了撤单请求，则保存
            # 在cancelDict字典中，等待返回后执行撤单任务
            self.cancelDict[localNo] = req

    #----------------------------------------------------------------------
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(float(s)/1e3)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return date, time

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """快速记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    #----------------------------------------------------------------------
    def checkDataError(self, data):
        """检查回报是否存在错误"""
        rawData = data['data']
        if 'error_code' not in rawData:
            return False
        else:
            error = VtErrorData()
            error.gatewayName = self.gatewayName
            error.errorID = rawData['error_code']
            error.errorMsg = u'请求失败，功能：%s' %data['channel']
            self.gateway.onError(error)
            return True

    #----------------------------------------------------------------------
    def subscribe(self, symbol):
        """订阅行情"""
        symbol = symbol
        
        self.subscribeSpotTicker(symbol)
        self.subscribeSpotDepth(symbol, 5)
        self.subSpotOrder(symbol)
        self.subSpotBalance(symbol)
    