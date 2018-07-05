# encoding: UTF-8

'''
vnpy.api.lhang的gateway接入
'''

from __future__ import print_function

import os
import json
from datetime import datetime
from time import sleep
from copy import copy

from vnpy.api.lbank import LbankRestApi, LbankWebsocketApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath


directionMap = {}
directionMap[DIRECTION_LONG] = 'buy'
directionMap[DIRECTION_SHORT] = 'sell'
directionMapReverse = {v:k for k,v in directionMap.items()}

statusMapReverse = {}
statusMapReverse[0] = STATUS_NOTTRADED
statusMapReverse[1] = STATUS_PARTTRADED
statusMapReverse[2] = STATUS_ALLTRADED
statusMapReverse[4] = STATUS_UNKNOWN
statusMapReverse[-1] = STATUS_CANCELLED


########################################################################
class LbankGateway(VtGateway):
    """FCOIN接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName=''):
        """Constructor"""
        super(LbankGateway, self).__init__(eventEngine, gatewayName)

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
            secretKey = str(setting['secretKey'])
            symbols = setting['symbols']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

        # 创建行情和交易接口对象
        self.restApi.connect(apiKey, secretKey, symbols)

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
            self.qryFunctionList = [self.restApi.qryAccount,
                                    self.restApi.qryWorkingOrder,
                                    self.restApi.qryCompletedOrder,
                                    self.restApi.qryMarketData]
            
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
class RestApi(LbankRestApi):
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
        
        self.tickDict = {}          # symbol:tick
        self.reqSymbolDict = {}
        
    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, symbols):
        """连接服务器"""
        self.init(apiKey, apiSecret)
        self.start()
        
        self.symbols = symbols
        for symbol in symbols:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.symbol = symbol
            tick.exchange = EXCHANGE_LBANK
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[symbol] = tick
        
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
        self.localID += 1
        orderID = str(self.localID)
        vtOrderID = '.'.join([self.gatewayName, orderID])
        
        req = {
            'symbol': orderReq.symbol,
            'type': directionMap[orderReq.direction],
            'price': orderReq.price,
            'amount': orderReq.volume
        }
        
        reqid = self.addReq('POST', '/create_order.do', req, self.onSendOrder)
        
        # 缓存委托数据对象
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = orderReq.symbol
        order.exchange = EXCHANGE_LBANK
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
            order = self.orderDict[sysID]
            req = {
                'symbol': order.symbol,
                'order_id': sysID
            }            
            self.addReq('POST', '/cancel_order.do', req, self.onCancelOrder)
            
        else:
            self.cancelDict[localID] = cancelOrderReq

    #----------------------------------------------------------------------
    def qryContract(self):
        """"""
        self.addReq('GET', '/accuracy.do', {}, self.onQryContract)

    #----------------------------------------------------------------------
    def qryCompletedOrder(self):
        """"""
        for symbol in self.symbols:
            req = {
                'symbol': symbol,
                'current_page': '1',
                'page_length': '100'
            }
            self.addReq('POST', '/orders_info_history.do', req, self.onQryOrder)
    
    #----------------------------------------------------------------------
    def qryWorkingOrder(self):
        """"""
        for symbol in self.symbols:
            req = {
                'symbol': symbol,
                'current_page': '1',
                'page_length': '100'
            }
            self.addReq('POST', '/orders_info_no_deal.do', req, self.onQryOrder)        
    
    #----------------------------------------------------------------------
    def qryAccount(self):
        """"""
        self.addReq('POST', '/user_info.do', {}, self.onQryAccount)
    
    #----------------------------------------------------------------------
    def qryDepth(self):
        """"""
        for symbol in self.symbols:
            req = {
                'symbol': symbol,
                'size': '5'
            }
            i = self.addReq('GET', '/depth.do', req, self.onQryDepth)
            self.reqSymbolDict[i] = symbol
    
    #----------------------------------------------------------------------
    def qryTicker(self):
        """"""
        for symbol in self.symbols:
            req = {'symbol': symbol}
            i = self.addReq('GET', '/ticker.do', req, self.onQryTicker)    
            self.reqSymbolDict[i] = symbol
    
    #----------------------------------------------------------------------
    def qryMarketData(self):
        """"""
        self.qryDepth()
        self.qryTicker()
    
    #----------------------------------------------------------------------
    def onSendOrder(self, data, reqid):
        """"""
        order = self.reqOrderDict[reqid]
        localID = order.orderID
        sysID = data['order_id']
        
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
        if 'orders' not in data:
            return
        
        if not isinstance(data['orders'], list):
            return
        
        data['orders'].reverse()
        
        for d in data['orders']:
            orderUpdated = False
            tradeUpdated = False
            
            # 获取委托对象
            sysID = d['order_id']
            if sysID in self.orderDict:
                order = self.orderDict[sysID]
            else:
                order = VtOrderData()
                order.gatewayName = self.gatewayName
                
                order.symbol = d['symbol']
                order.exchange = EXCHANGE_LBANK
                order.vtSymbol = '.'.join([order.symbol, order.exchange])
                
                self.localID += 1
                localID = str(self.localID)
                self.localSysDict[localID] = sysID
                
                order.orderID = localID
                order.vtOrderID = '.'.join([order.gatewayName, order.orderID])
                
                order.direction = directionMapReverse[d['type']]
                order.price = float(d['price'])
                order.totalVolume = float(d['amount'])
                
                dt = datetime.fromtimestamp(d['create_time']/1000)
                order.orderTime = dt.strftime('%H:%M:%S')
                
                self.orderDict[sysID] = order
                orderUpdated = True
        
            # 检查是否委托有变化
            newTradedVolume = float(d['deal_amount'])
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
        info = data['info']
        asset = info['asset']
        free = info['free']
        freeze = info['freeze']
        
        for currency in asset.keys():
            account = VtAccountData()
            account.gatewayName = self.gatewayName
            
            account.accountID = currency
            account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
            account.balance = float(asset[currency])
            account.available = float(free[currency])
            
            self.gateway.onAccount(account)    
    
    #----------------------------------------------------------------------
    def onQryContract(self, data, reqid):
        """"""
        for d in data:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            
            contract.symbol = str(d['symbol'])
            contract.exchange = EXCHANGE_LBANK
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = contract.vtSymbol
            contract.productClass = PRODUCT_SPOT
            contract.priceTick = pow(10, -int(d['priceAccuracy']))
            contract.size = 1
            
            self.gateway.onContract(contract)   
        
        self.writeLog(u'合约信息查询完成')
    
    #----------------------------------------------------------------------
    def onQryTicker(self, data, reqid):
        """"""
        ticker = data['ticker']
        
        symbol = self.reqSymbolDict.pop(reqid)
        tick = self.tickDict[symbol]
        
        tick.highPrice = float(ticker['high'])
        tick.lowPrice = float(ticker['low'])
        tick.lastPrice = float(ticker['latest'])
        tick.volume = float(ticker['vol'])
        
        tick.datetime = datetime.fromtimestamp(int(data['timestamp']/1000))
        tick.date = tick.datetime.strftime('%Y%m%d')
        tick.time = tick.datetime.strftime('%H:%M:%S')
        
        if tick.bidPrice1:
            self.gateway.onTick(copy(tick))
    
    #----------------------------------------------------------------------
    def onQryDepth(self, data, reqid):
        """"""
        symbol = self.reqSymbolDict.pop(reqid)
        tick = self.tickDict[symbol]        
        
        bids = data['bids']
        asks = data['asks']
        
        tick.bidPrice1, tick.bidVolume1 = bids[0]
        tick.bidPrice2, tick.bidVolume2 = bids[1]
        tick.bidPrice3, tick.bidVolume3 = bids[2]
        tick.bidPrice4, tick.bidVolume4 = bids[3]
        tick.bidPrice5, tick.bidVolume5 = bids[4]
        
        tick.askPrice1, tick.askVolume1 = asks[0]
        tick.askPrice2, tick.askVolume2 = asks[1]
        tick.askPrice3, tick.askVolume3 = asks[2]
        tick.askPrice4, tick.askVolume4 = asks[3]
        tick.askPrice5, tick.askVolume5 = asks[4]        
        
        if tick.lastPrice:
            self.gateway.onTick(copy(tick))     
        

########################################################################
class WebsocketApi(LbankWebsocketApi):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(WebsocketApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        
        self.symbols = []
        self.channelTickDict = {}
        
    #----------------------------------------------------------------------
    def connect(self, symbols):
        """"""
        self.symbols = symbols
        self.start()
    
    #----------------------------------------------------------------------
    def onConnect(self):
        """连接回调"""
        self.writeLog(u'Websocket API连接成功')
        self.subscribe()
        
    #----------------------------------------------------------------------
    def subscribe(self):
        """"""
        for symbol in self.symbols:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.symbol = symbol
            tick.exchange = EXCHANGE_LBANK
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            
            channelDepth = 'lh_sub_spot_%s_depth_20' %symbol
            #channelTrades = 'lh_sub_spot_%s_ticker' %symbol 
            self.channelTickDict[channelDepth] = tick
           # self.channelTickDict[channelTrades] = tick
            
            for channel in [channelDepth]: #, channelTrades]:
                req = {
                    'event': 'addChannel',
                    'channel': channel
                }
                self.sendReq(req)
    
    #----------------------------------------------------------------------
    def onData(self, data):
        """数据回调"""
        channel = data['channel']
        print(data)
        if 'trades' in channel:
            self.onTick(data)
        elif 'depth' in channel:
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
    def onTick(self, data):
        """"""
        if 'data' not in data:
            return
        
        channel = data['channel']
        tick = self.channelTickDict[channel]
        
        fill = data['data'][0]
        tick.lastPrice = float(fill[0])
        tick.datetime = datetime.fromtimestamp(int(fill[2])/1000)
        tick.date = tick.datetime.strftime('%Y%m%d')
        tick.time = tick.datetime.strftime('%H:%M:%S')
        
        self.gateway.onTick(copy(tick))

    #----------------------------------------------------------------------
    def onDepth(self, data):
        """"""
        if 'data' not in data:
            return
        
        channel = data['channel']
        tick = self.channelTickDict[channel]

        d = data['data']
        bids = d['bids']
        asks = d['asks']
        
        tick.bidPrice1, tick.bidVolume1 = bids[0]
        tick.bidPrice2, tick.bidVolume2 = bids[1]
        tick.bidPrice3, tick.bidVolume3 = bids[2]
        tick.bidPrice4, tick.bidVolume4 = bids[3]
        tick.bidPrice5, tick.bidVolume5 = bids[4]
        
        tick.askPrice1, tick.askVolume1 = asks[0]
        tick.askPrice2, tick.askVolume2 = asks[1]
        tick.askPrice3, tick.askVolume3 = asks[2]
        tick.askPrice4, tick.askVolume4 = asks[3]
        tick.askPrice5, tick.askVolume5 = asks[4]        
        
        tick.lastPrice = (tick.askPrice1 + tick.askPrice2) / 2
        
        tick.datetime = datetime.fromtimestamp(d['timestamp']/1000)
        tick.date = tick.datetime.strftime('%Y%m%d')
        tick.time = tick.datetime.strftime('%H:%M:%S')
        
        self.gateway.onTick(copy(tick))        

