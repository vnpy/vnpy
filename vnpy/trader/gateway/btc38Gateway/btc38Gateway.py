# encoding: UTF-8

'''
vn.btc38的gateway接入
'''


import os
import json
from datetime import datetime
from copy import copy
from threading import Condition
from Queue import Queue
from threading import Thread

from vnpy.api.btc38 import vnbtc38
from vnpy.trader.vtGateway import *


SYMBOL_BTCCNY = 'BTCCNY'
SYMBOL_LTCCNY = 'LTCCNY'
SYMBOL_BTSCNY = 'BTSCNY'

SYMBOL_MAP = {}
SYMBOL_MAP[(vnbtc38.COINTYPE_BTC, 'cny')] = SYMBOL_BTCCNY
SYMBOL_MAP[(vnbtc38.COINTYPE_LTC, 'cny')] = SYMBOL_LTCCNY
SYMBOL_MAP[(vnbtc38.COINTYPE_BTC, 'usd')] = SYMBOL_BTSCNY
SYMBOL_MAP_REVERSE = {v: k for k, v in SYMBOL_MAP.items()}

MDSYMBOL_MAP = {}
MDSYMBOL_MAP['btccny'] = SYMBOL_BTCCNY
MDSYMBOL_MAP['ltccny'] = SYMBOL_LTCCNY
MDSYMBOL_MAP['btscny'] = SYMBOL_BTSCNY

DIRECTION_MAP = {}
DIRECTION_MAP[1] = DIRECTION_LONG
DIRECTION_MAP[2] = DIRECTION_SHORT

STATUS_MAP = {}
STATUS_MAP[0] = STATUS_NOTTRADED
STATUS_MAP[1] = STATUS_PARTTRADED
STATUS_MAP[2] = STATUS_ALLTRADED
STATUS_MAP[3] = STATUS_CANCELLED
STATUS_MAP[5] = STATUS_UNKNOWN
STATUS_MAP[7] = STATUS_UNKNOWN



########################################################################
class Btc38Gateway(VtGateway):
    """火币接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='BTC38'):
        """Constructor"""
        super(Btc38Gateway, self).__init__(eventEngine, gatewayName)
        
        self.market = 'cny'
        
        self.tradeApi = Btc38TradeApi(self)
        self.dataApi = Btc38DataApi(self)
        
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
        fileName = self.gatewayName + '_connect.json'
        path = os.path.abspath(os.path.dirname(__file__))
        fileName = os.path.join(path, fileName)
        
        try:
            f = file(fileName)
        except IOError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'读取连接配置出错，请检查'
            self.onLog(log)
            return
        
        # 解析json文件
        setting = json.load(f)
        try:
            accessKey = str(setting['accessKey'])
            secretKey = str(setting['secretKey'])
            interval = setting['interval']
            market = setting['market']
            debug = setting['debug']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 初始化接口
        self.tradeApi.connect(accessKey, secretKey, market, debug)
        self.writeLog(u'交易接口初始化成功')
        
        self.dataApi.connect(interval, market, debug)
        self.writeLog(u'行情接口初始化成功')
        
        # 启动查询
        self.initQuery()
        self.startQuery()
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.onLog(log)        
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情，自动订阅全部行情，无需实现"""
        pass
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        self.tradeApi.sendOrder(orderReq)
        
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.tradeApi.cancel(cancelOrderReq)
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        pass
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        pass
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.tradeApi.exit()
        self.dataApi.exit()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            self.qryFunctionList = [self.tradeApi.queryWorkingOrders, self.tradeApi.queryAccount]
            self.startQuery()  
    
    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        for function in self.qryFunctionList:
            function()
                
    #----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)
    
    #----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled
    

########################################################################
class Btc38TradeApi(vnbtc38.TradeApi):
    """交易接口"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(Btc38TradeApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName

        self.localID = 0            # 本地委托号
        self.localSystemDict = {}   # key:localID, value:systemID
        self.systemLocalDict = {}   # key:systemID, value:localID
        self.workingOrderDict = {}  # key:localID, value:order
        self.reqLocalDict = {}      # key:reqID, value:localID
        self.cancelDict = {}        # key:localID, value:cancelOrderReq

        self.tradeID = 0            # 本地成交号
    
    #----------------------------------------------------------------------
    def onError(self, error, req, reqID):
        """错误推送"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorMsg = str(error)
        err.errorTime = datetime.now().strftime('%H:%M:%S')
        self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onGetAccountInfo(self, data, req, reqID):
        """查询账户回调"""
        # 推送账户数据
        account = VtAccountData()
        account.gatewayName = self.gatewayName
        account.accountID = 'BTC38'
        account.vtAccountID = '.'.join([account.accountID, self.gatewayName])
        account.balance = data['net_asset']
        self.gateway.onAccount(account)
        
        # 推送持仓数据
        if self.market == 'cny':
            posCny = VtPositionData()
            posCny.gatewayName = self.gatewayName
            posCny.symbol = 'CNY'
            posCny.exchange = EXCHANGE_BTC38
            posCny.vtSymbol = '.'.join([posCny.symbol, posCny.exchange])
            posCny.vtPositionName = posCny.vtSymbol
            posCny.position = data['available_cny_display']
            posCny.frozen = data['frozen_cny_display']
            self.gateway.onPosition(posCny)
            
            posLtc = VtPositionData()
            posLtc.gatewayName = self.gatewayName
            posLtc.symbol = 'LTC'
            posLtc.exchange = EXCHANGE_BTC38
            posLtc.vtSymbol = '.'.join([posLtc.symbol, posLtc.exchange])
            posLtc.vtPositionName = posLtc.vtSymbol
            posLtc.position = data['available_ltc_display']
            posLtc.frozen = data['frozen_ltc_display']
            self.gateway.onPosition(posLtc)
        else:
            posUsd = VtPositionData()
            posUsd.gatewayName = self.gatewayName
            posUsd.symbol = 'USD'
            posUsd.exchange = EXCHANGE_BTC38
            posUsd.vtSymbol = '.'.join([posUsd.symbol, posUsd.exchange])
            posUsd.vtPositionName = posUsd.vtSymbol
            posUsd.position = data['available_usd_display']
            posUsd.frozen = data['frozen_usd_display']
            self.gateway.onPosition(posUsd)     
            
        posBtc = VtPositionData()
        posBtc.gatewayName = self.gatewayName
        posBtc.symbol = 'BTC'
        posBtc.exchange = EXCHANGE_BTC38
        posBtc.vtSymbol = '.'.join([posBtc.symbol, posBtc.exchange])
        posBtc.vtPositionName = posBtc.vtSymbol
        posBtc.position = data['available_btc_display']
        posBtc.frozen = data['frozen_btc_display']
        self.gateway.onPosition(posBtc)        
    
    #----------------------------------------------------------------------
    def onGetOrders(self, data, req, reqID):
        """查询委托回调"""
        for d in data:
            order = VtOrderData()
            order.gatewayName = self.gatewayName

            # 合约代码
            params = req['params']
            coin = params['coin_type']
            order.symbol = SYMBOL_MAP[(coin, self.market)]
            order.exchange = EXCHANGE_BTC38
            order.vtSymbol = '.'.join([order.symbol, order.exchange])

            # 委托号
            systemID = d['id']
            self.localID += 1
            localID = str(self.localID)
            self.systemLocalDict[systemID] = localID
            self.localSystemDict[localID] = systemID
            order.orderID = localID
            order.vtOrderID = '.'.join([order.orderID, order.gatewayName])

            # 其他信息
            order.direction = DIRECTION_MAP[d['type']]
            order.offset = OFFSET_NONE
            order.price = float(d['order_price'])
            order.totalVolume = float(d['order_amount'])
            order.tradedVolume = float(d['processed_amount'])
            order.orderTime = d['order_time']

            # 委托状态
            if order.tradedVolume == 0:
                order.status = STATUS_NOTTRADED
            else:
                order.status = STATUS_PARTTRADED

            # 缓存病推送
            self.workingOrderDict[localID] = order
            self.gateway.onOrder(order)

    #----------------------------------------------------------------------
    def onOrderInfo(self, data, req, reqID):
        """委托详情回调"""
        systemID = data['id']
        localID = self.systemLocalDict[systemID]
        order = self.workingOrderDict.get(localID, None)
        if not order:
            return

        # 记录最新成交的金额
        newTradeVolume = float(data['processed_amount']) - order.tradedVolume
        if newTradeVolume:
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            trade.symbol = order.symbol
            trade.vtSymbol = order.vtSymbol

            self.tradeID += 1
            trade.tradeID = str(self.tradeID)
            trade.vtTradeID = '.'.join([trade.tradeID, trade.gatewayName])

            trade.volume = newTradeVolume
            trade.price = data['processed_price']
            trade.direction = order.direction
            trade.offset = order.offset
            trade.exchange = order.exchange
            trade.tradeTime = datetime.now().strftime('%H:%M:%S')

            self.gateway.onTrade(trade)

        # 更新委托状态
        order.tradedVolume = float(data['processed_amount'])
        order.status = STATUS_MAP.get(data['status'], STATUS_UNKNOWN)

        if newTradeVolume:
            self.gateway.onOrder(order)

        if order.status == STATUS_ALLTRADED or order.status == STATUS_CANCELLED:
            del self.workingOrderDict[order.orderID]

    #----------------------------------------------------------------------
    def onBuy(self, data, req, reqID):
        """买入回调"""
        localID = self.reqLocalDict[reqID]
        systemID = data['id']
        self.localSystemDict[localID] = systemID
        self.systemLocalDict[systemID] = localID

        # 撤单
        if localID in self.cancelDict:
            req = self.cancelDict[localID]
            self.cancel(req)
            del self.cancelDict[localID]

        # 推送委托信息
        order = self.workingOrderDict[localID]
        if data['result'] == 'success':
            order.status = STATUS_NOTTRADED
        self.gateway.onOrder(order)
        
    #----------------------------------------------------------------------
    def onSell(self, data, req, reqID):
        """卖出回调"""
        localID = self.reqLocalDict[reqID]
        systemID = data['id']
        self.localSystemDict[localID] = systemID
        self.systemLocalDict[systemID] = localID

        # 撤单
        if localID in self.cancelDict:
            req = self.cancelDict[localID]
            self.cancel(req)
            del self.cancelDict[localID]

        # 推送委托信息
        order = self.workingOrderDict[localID]
        if data['result'] == 'success':
            order.status = STATUS_NOTTRADED
        self.gateway.onOrder(order)
        
    #----------------------------------------------------------------------
    def onBuyMarket(self, data, req, reqID):
        """市价买入回调"""
        print data
        
    #----------------------------------------------------------------------
    def onSellMarket(self, data, req, reqID):
        """市价卖出回调"""
        print data        
        
    #----------------------------------------------------------------------
    def onCancelOrder(self, data, req, reqID):
        """撤单回调"""
        if data['result'] == 'success':
            systemID = req['params']['id']
            localID = self.systemLocalDict[systemID]

            order = self.workingOrderDict[localID]
            order.status = STATUS_CANCELLED

            del self.workingOrderDict[localID]
            self.gateway.onOrder(order)
    
    #----------------------------------------------------------------------
    def onGetNewDealOrders(self, data, req, reqID):
        """查询最新成交回调"""
        print data    
        
    #----------------------------------------------------------------------
    def onGetOrderIdByTradeId(self, data, req, reqID):
        """通过成交编号查询委托编号回调"""
        print data    
        
    #----------------------------------------------------------------------
    def onWithdrawCoin(self, data, req, reqID):
        """提币回调"""
        print data
        
    #----------------------------------------------------------------------
    def onCancelWithdrawCoin(self, data, req, reqID):
        """取消提币回调"""
        print data      
        
    #----------------------------------------------------------------------
    def onGetWithdrawCoinResult(self, data, req, reqID):
        """查询提币结果回调"""
        print data           
        
    #----------------------------------------------------------------------
    def onTransfer(self, data, req, reqID):
        """转账回调"""
        print data
        
    #----------------------------------------------------------------------
    def onLoan(self, data, req, reqID):
        """申请杠杆回调"""
        print data      
        
    #----------------------------------------------------------------------
    def onRepayment(self, data, req, reqID):
        """归还杠杆回调"""
        print data    
    
    #----------------------------------------------------------------------
    def onLoanAvailable(self, data, req, reqID):
        """查询杠杆额度回调"""
        print data      
        
    #----------------------------------------------------------------------
    def onGetLoans(self, data, req, reqID):
        """查询杠杆列表"""
        print data        
    
    #----------------------------------------------------------------------
    def connect(self, accessKey, secretKey, market, debug=False):
        """连接服务器"""
        self.market = market
        self.DEBUG = debug
        
        self.init(accessKey, secretKey)

        # 查询未成交委托
        self.getOrders(vnbtc38.COINTYPE_BTC, self.market)

        if self.market == vnbtc38.MARKETTYPE_CNY:
            # 只有人民币市场才有莱特币
            self.getOrders(vnbtc38.COINTYPE_LTC, self.market)

    # ----------------------------------------------------------------------
    def queryWorkingOrders(self):
        """查询活动委托状态"""
        for order in self.workingOrderDict.values():
            # 如果尚未返回委托号，则无法查询
            if order.orderID in self.localSystemDict:
                systemID = self.localSystemDict[order.orderID]
                coin, market = SYMBOL_MAP_REVERSE[order.symbol]
                self.orderInfo(systemID, coin, market)

    # ----------------------------------------------------------------------
    def queryAccount(self):
        """查询活动委托状态"""
        self.getAccountInfo(self.market)

    # ----------------------------------------------------------------------
    def sendOrder(self, req):
        """发送委托"""
        # 检查是否填入了价格，禁止市价委托
        if req.priceType != PRICETYPE_LIMITPRICE:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorMsg = u'火币接口仅支持限价单'
            err.errorTime = datetime.now().strftime('%H:%M:%S')
            self.gateway.onError(err)
            return None

        # 发送限价委托
        coin, market = SYMBOL_MAP_REVERSE[req.symbol]

        if req.direction == DIRECTION_LONG:
            reqID = self.buy(req.price, req.volume, coinType=coin, market=self.market)
        else:
            reqID = self.sell(req.price, req.volume, coinType=coin, market=self.market)

        self.localID += 1
        localID = str(self.localID)
        self.reqLocalDict[reqID] = localID

        # 推送委托信息
        order = VtOrderData()
        order.gatewayName = self.gatewayName

        order.symbol = req.symbol
        order.exchange = EXCHANGE_BTC38
        order.vtSymbol = '.'.join([order.symbol, order.exchange])

        order.orderID = localID
        order.vtOrderID = '.'.join([order.orderID, order.gatewayName])

        order.direction = req.direction
        order.offset = OFFSET_UNKNOWN
        order.price = req.price
        order.volume = req.volume
        order.orderTime = datetime.now().strftime('%H:%M:%S')
        order.status = STATUS_UNKNOWN

        self.workingOrderDict[localID] = order
        self.gateway.onOrder(order)

        # 返回委托号
        return order.vtOrderID

    # ----------------------------------------------------------------------
    def cancel(self, req):
        """撤单"""
        localID = req.orderID
        if localID in self.localSystemDict:
            systemID = self.localSystemDict[localID]
            coin, market = SYMBOL_MAP_REVERSE[req.symbol]
            self.cancelOrder(systemID, coin, self.market)
        else:
            self.cancelDict[localID] = req


########################################################################
class Btc38DataApi(vnbtc38.DataApi):
    """行情接口"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(Btc38DataApi, self).__init__()

        self.market = 'cny'
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName

        self.tickDict = {}      # key:symbol, value:tick

    
    #----------------------------------------------------------------------
    def onTick(self, data):
        """实时成交推送"""
        print data
        
    #----------------------------------------------------------------------
    def onQuote(self, data):
        """实时报价推送"""
        ticker = data['ticker']
        symbol = MDSYMBOL_MAP[ticker['symbol']]

        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.symbol = symbol
            tick.exchange = EXCHANGE_BTC38
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        tick.highPrice = ticker['high']
        tick.lowPrice = ticker['low']
        tick.lastPrice = ticker['last']
        tick.volume = ticker['vol']
    
    #----------------------------------------------------------------------
    def onDepth(self, data):
        """实时深度推送"""
        symbol = MDSYMBOL_MAP[data['symbol']]
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.symbol = symbol
            tick.exchange = EXCHANGE_BTC38
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        tick.bidPrice1, tick.bidVolume1 = data['bids'][0]
        tick.bidPrice2, tick.bidVolume2 = data['bids'][1]
        tick.bidPrice3, tick.bidVolume3 = data['bids'][2]
        tick.bidPrice4, tick.bidVolume4 = data['bids'][3]
        tick.bidPrice5, tick.bidVolume5 = data['bids'][4]

        tick.askPrice1, tick.askVolume1 = data['asks'][0]
        tick.askPrice2, tick.askVolume2 = data['asks'][1]
        tick.askPrice3, tick.askVolume3 = data['asks'][2]
        tick.askPrice4, tick.askVolume4 = data['asks'][3]
        tick.askPrice5, tick.askVolume5 = data['asks'][4]

        now = datetime.now()
        tick.time = now.strftime('%H:%M:%S')
        tick.date = now.strftime('%Y%m%d')

        self.gateway.onTick(tick)
        
    #----------------------------------------------------------------------
    def connect(self, interval, market, debug=False):
        """连接服务器"""
        self.market = market

        self.init(interval, debug)

        # 订阅行情并推送合约信息
        if self.market == vnbtc38.MARKETTYPE_CNY:
            self.subscribeQuote(vnbtc38.SYMBOL_BTCCNY)
            self.subscribeQuote(vnbtc38.SYMBOL_LTCCNY)

            self.subscribeDepth(vnbtc38.SYMBOL_BTCCNY, 5)
            self.subscribeDepth(vnbtc38.SYMBOL_LTCCNY, 5)

            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            contract.symbol = SYMBOL_BTCCNY
            contract.exchange = EXCHANGE_BTC38
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = u'人民币现货BTC'
            contract.size = 1
            contract.priceTick = 0.01
            contract.productClass = PRODUCT_SPOT
            self.gateway.onContract(contract)

            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            contract.symbol = SYMBOL_LTCCNY
            contract.exchange = EXCHANGE_BTC38
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = u'人民币现货LTC'
            contract.size = 1
            contract.priceTick = 0.01
            contract.productClass = PRODUCT_SPOT
            self.gateway.onContract(contract)
