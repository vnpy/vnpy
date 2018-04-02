# encoding: UTF-8

'''
vn.lhang的gateway接入
'''


import os
import json
from datetime import datetime
from time import sleep

from vnpy.api.lbank import LbankApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath


SYMBOL_BTCCNY = 'BTCCNY'
SYMBOL_ZECCNY = 'ZECCNY'

SYMBOL_MAP = {}
SYMBOL_MAP['btc_cny'] = SYMBOL_BTCCNY
SYMBOL_MAP['zec_cny'] = SYMBOL_ZECCNY
SYMBOL_MAP_REVERSE = {v: k for k, v in SYMBOL_MAP.items()}


DIRECTION_MAP = {}
DIRECTION_MAP['buy'] = DIRECTION_LONG
DIRECTION_MAP['sell'] = DIRECTION_SHORT

STATUS_MAP = {}
STATUS_MAP[0] = STATUS_NOTTRADED
STATUS_MAP[1] = STATUS_PARTTRADED
STATUS_MAP[2] = STATUS_ALLTRADED
STATUS_MAP[4] = STATUS_UNKNOWN
STATUS_MAP[-1] = STATUS_CANCELLED


########################################################################
class LbankGateway(VtGateway):
    """LBANK接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='LBANK'):
        """Constructor"""
        super(LbankGateway, self).__init__(eventEngine, gatewayName)
        
        self.api = LbankApi(self)
        
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
            accessKey = str(setting['apiKey'])
            secretKey = str(setting['secretKey'])
            interval = setting['interval']
            debug = setting['debug']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 初始化接口
        self.api.connect(accessKey, secretKey, interval, debug)
        self.writeLog(u'接口初始化成功')
        
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
        self.api.sendOrder(orderReq)
        
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.api.cancel(cancelOrderReq)
        
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
        self.api.exit()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            self.qryFunctionList = [self.api.queryPrice,
                                    self.api.queryWorkingOrders,
                                    self.api.queryAccount]
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
class LbankApi(LbankApi):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(LbankApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        
        self.interval = 1

        self.localID = 0            # 本地委托号
        self.localSystemDict = {}   # key:localID, value:systemID
        self.systemLocalDict = {}   # key:systemID, value:localID
        self.workingOrderDict = {}  # key:localID, value:order
        self.reqLocalDict = {}      # key:reqID, value:localID
        self.cancelDict = {}        # key:localID, value:cancelOrderReq

        self.tradeID = 0

        self.tickDict = {}      # key:symbol, value:tick

    #----------------------------------------------------------------------
    def onError(self, error, req, reqID):
        """错误推送"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorMsg = str(error)
        err.errorTime = datetime.now().strftime('%H:%M:%S.%f')[:-3]
        self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onGetTicker(self, data, req, reqID):
        """查询行情回调"""
        ticker = data['ticker']
        params = req['params']
        symbol = SYMBOL_MAP[params['symbol']]

        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.symbol = symbol
            tick.exchange = EXCHANGE_LBANK
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        tick.highPrice = float(ticker['high'])
        tick.lowPrice = float(ticker['low'])
        tick.lastPrice = float(ticker['latest'])
        tick.openPrice = tick.lastPrice - float(ticker['change'])
        tick.volume = ticker['vol']

    # ----------------------------------------------------------------------
    def onGetDepth(self, data, req, reqID):
        """查询深度回调"""
        params = req['params']
        symbol = SYMBOL_MAP[params['symbol']]
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.symbol = symbol
            tick.exchange = EXCHANGE_LBANK
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
        tick.time = now.strftime('%H:%M:%S.%f')[:-3]
        tick.date = now.strftime('%Y%m%d')

        self.gateway.onTick(tick)

    # ----------------------------------------------------------------------
    def onGetTrades(self, data, req, reqID):
        """查询历史成交"""
        print data, reqID

    # ----------------------------------------------------------------------
    def onGetKline(self, data, req, reqID):
        print data, reqID
    
    # ----------------------------------------------------------------------
    def onGetUserInfo(self, data, req, reqID):
        """查询Ｋ线回报"""
        d = data['info']
        account = VtAccountData()
        account.gatewayName = self.gatewayName
        account.accountID = self.gatewayName
        account.vtAccountID = '.'.join([account.accountID, self.gatewayName])
        account.balance = d['asset']['net']
        self.gateway.onAccount(account)

        # 推送持仓数据
        posCny = VtPositionData()
        posCny.gatewayName = self.gatewayName
        posCny.symbol = 'CNY'
        posCny.exchange = EXCHANGE_LBANK
        posCny.vtSymbol = '.'.join([posCny.symbol, posCny.exchange])
        posCny.vtPositionName = posCny.vtSymbol
        posCny.frozen = d['freeze']['cny']
        posCny.position = posCny.frozen + d['free']['cny']
        self.gateway.onPosition(posCny)

        posBtc = VtPositionData()
        posBtc.gatewayName = self.gatewayName
        posBtc.symbol = 'BTC'
        posBtc.exchange = EXCHANGE_LBANK
        posBtc.vtSymbol = '.'.join([posBtc.symbol, posBtc.exchange])
        posBtc.vtPositionName = posBtc.vtSymbol
        posBtc.frozen = d['freeze']['btc']
        posBtc.position = posBtc.frozen + d['free']['btc']
        self.gateway.onPosition(posBtc)

        posZec = VtPositionData()
        posZec.gatewayName = self.gatewayName
        posZec.symbol = 'ZEC'
        posZec.exchange = EXCHANGE_LBANK
        posZec.vtSymbol = '.'.join([posZec.symbol, posZec.exchange])
        posZec.vtPositionName = posZec.vtSymbol
        posZec.frozen = d['freeze']['zec']
        posZec.position = posZec.frozen + d['free']['zec']
        self.gateway.onPosition(posZec)

        # 查询历史委托
        self.queryOrders()

    # ----------------------------------------------------------------------
    def onCreateOrder(self, data, req, reqID):
        """发单回调"""
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

    # ----------------------------------------------------------------------
    def onCancelOrder(self, data, req, reqID):
        """撤单回调"""
        if data['result'] == 'success':
            systemID = req['params']['id']
            localID = self.systemLocalDict[systemID]

            order = self.workingOrderDict[localID]
            order.status = STATUS_CANCELLED

            del self.workingOrderDict[localID]
            self.gateway.onOrder(order)

    # ----------------------------------------------------------------------
    def onGetOrdersInfo(self, data, req, reqID):
        """查询委托回报"""
        if 'orders' in data:
            for d in data['orders']:
                systemID = d['order_id']
                localID = self.systemLocalDict[systemID]
                order = self.workingOrderDict.get(localID, None)
                if not order:
                    return

                # 记录最新成交的金额
                newTradeVolume = float(d['deal_amount']) - order.tradedVolume
                if newTradeVolume:
                    trade = VtTradeData()
                    trade.gatewayName = self.gatewayName
                    trade.symbol = order.symbol
                    trade.vtSymbol = order.vtSymbol

                    self.tradeID += 1
                    trade.tradeID = str(self.tradeID)
                    trade.vtTradeID = '.'.join([trade.tradeID, trade.gatewayName])

                    trade.volume = newTradeVolume
                    trade.price = d['avg_price']
                    trade.direction = order.direction
                    trade.offset = order.offset
                    trade.exchange = order.exchange
                    trade.tradeTime = datetime.now().strftime('%H:%M:%S.%f')[:-3]

                    self.gateway.onTrade(trade)

                # 更新委托状态
                order.tradedVolume = float(d['deal_amount'])
                order.status = STATUS_MAP.get(d['status'], STATUS_UNKNOWN)

                if newTradeVolume:
                    self.gateway.onOrder(order)

                if order.status == STATUS_ALLTRADED or order.status == STATUS_CANCELLED:
                    del self.workingOrderDict[order.orderID]

    # ----------------------------------------------------------------------
    def onGetOrdersInfoHistory(self, data, req, reqID):
        """撤单回报"""
        if 'orders' in data:
            for d in data['orders']:
                order = VtOrderData()
                order.gatewayName = self.gatewayName

                order.symbol = SYMBOL_MAP[data['symbol']]
                order.exchange = EXCHANGE_LBANK
                order.vtSymbol = '.'.join([order.symbol, order.exchange])

                systemID = d['order_id']
                self.localID += 1
                localID = str(self.localID)
                self.systemLocalDict[systemID] = localID
                self.localSystemDict[localID] = systemID
                order.orderID = localID
                order.vtOrderID = '.'.join([order.orderID, order.gatewayName])

                order.totalVolume = float(d['amount'])
                order.tradedVolume = float(d['deal_amount'])
                order.price = float(d['price'])
                order.direction = DIRECTION_MAP[d['type']]
                order.offset = OFFSET_NONE
                order.orderTime = datetime.fromtimestamp(d['create_time'], '%H:%M:%S')

                # 委托状态
                if order.tradedVolume == 0:
                    order.status = STATUS_NOTTRADED
                else:
                    order.status = STATUS_PARTTRADED

                # 缓存病推送
                self.workingOrderDict[localID] = order
                self.gateway.onOrder(order)
        
    #----------------------------------------------------------------------
    def connect(self, apiKey, secretKey, interval, debug):
        """初始化"""
        self.interval = interval
        self.DEBUG = debug

        self.init(apiKey, secretKey, self.interval)

        # 推送合约信息
        contract = VtContractData()
        contract.gatewayName = self.gatewayName
        contract.symbol = SYMBOL_BTCCNY
        contract.exchange = EXCHANGE_LBANK
        contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
        contract.name = u'人民币现货BTC'
        contract.size = 1
        contract.priceTick = 0.01
        contract.productClass = PRODUCT_SPOT
        self.gateway.onContract(contract)

        contract = VtContractData()
        contract.gatewayName = self.gatewayName
        contract.symbol = SYMBOL_ZECCNY
        contract.exchange = EXCHANGE_LBANK
        contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
        contract.name = u'人民币现货ZEC'
        contract.size = 1
        contract.priceTick = 0.01
        contract.productClass = PRODUCT_SPOT
        self.gateway.onContract(contract)
        
    #----------------------------------------------------------------------
    def sendOrder(self, req):
        """发单"""
        # 检查是否填入了价格，禁止市价委托
        if req.priceType != PRICETYPE_LIMITPRICE:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorMsg = u'LBANK接口仅支持限价单'
            err.errorTime = datetime.now().strftime('%H:%M:%S.%f')[:-3]
            self.gateway.onError(err)
            return None

        # 发送限价委托
        s = SYMBOL_MAP_REVERSE[req.symbol]

        if req.direction == DIRECTION_LONG:
            type_ = 'buy'
        else:
            type_ = 'sell'

        reqID = self.createOrder(s, type_, req.price, req.volume)

        self.localID += 1
        localID = str(self.localID)
        self.reqLocalDict[reqID] = localID

        # 推送委托信息
        order = VtOrderData()
        order.gatewayName = self.gatewayName

        order.symbol = req.symbol
        order.exchange = EXCHANGE_LBANK
        order.vtSymbol = '.'.join([order.symbol, order.exchange])

        order.orderID = localID
        order.vtOrderID = '.'.join([order.orderID, order.gatewayName])

        order.direction = req.direction
        order.offset = OFFSET_UNKNOWN
        order.price = req.price
        order.volume = req.volume
        order.orderTime = datetime.now().strftime('%H:%M:%S.%f')[:-3]
        order.status = STATUS_UNKNOWN

        self.workingOrderDict[localID] = order
        self.gateway.onOrder(order)

        # 返回委托号
        return order.vtOrderID
    
    #----------------------------------------------------------------------
    def cancel(self, req):
        """撤单"""
        localID = req.orderID
        if localID in self.localSystemDict:
            systemID = self.localSystemDict[localID]
            s = SYMBOL_MAP_REVERSE[req.symbol]
            self.cancelOrder(s, systemID)
        else:
            self.cancelDict[localID] = req

    #----------------------------------------------------------------------
    def queryOrders(self):
        """查询委托"""
        for s in SYMBOL_MAP.keys():
            self.getOrdersInfoHistory(s, '0', '1', '200')

    #----------------------------------------------------------------------
    def queryWorkingOrders(self):
        """查询活动委托"""
        for localID, order in self.workingOrderDict.items():
            if localID in self.localSystemDict:
                systemID = self.localSystemDict[localID]
                s = SYMBOL_MAP_REVERSE[order.symbol]
                self.getOrdersInfo(s, systemID)

    #----------------------------------------------------------------------
    def queryPrice(self):
        """查询行情"""
        for s in SYMBOL_MAP.keys():
            self.getTicker(s)
            self.getDepth(s, 5, 0)

    #----------------------------------------------------------------------
    def queryAccount(self):
        """查询资金和资产"""
        self.getUserInfo()