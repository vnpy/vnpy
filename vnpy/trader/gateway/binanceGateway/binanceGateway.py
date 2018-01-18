# encoding: UTF-8

'''
vn.binance的gateway接入
'''

import os
import json
from datetime import datetime
from copy import copy
from threading import Condition
from Queue import Queue
from threading import Thread

import json
from vnpy.api.binance import BinanceSpotApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath

from datetime import datetime , timedelta
import time

'''
币安接口
'''
class BinanceGateway(VtGateway):
    """Binance 接口"""
    #----------------------------------------------------------------------
    def __init__(self, eventEngine , gatewayName='BINANCE'):
        """Constructor"""
        super(BinanceGateway, self).__init__(eventEngine, gatewayName)
        
        self.api_spot = BinanceApi(self)
        
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)       

        self.connected = False

        self.qryEnabled = True

        self.interval = 30
        self.accountID = "None"

        self.total_count = 0

    #----------------------------------------------------------------------
    def connect(self):
        try:
            f = file(self.filePath)
        except IOError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'BINANCE读取连接配置出错，请检查'
            self.onLog(log)
            return

        # 解析json文件
        setting = json.load(f)
        try:
            self.accountID = str(setting["accountID"])
            apiKey = str(setting['accessKey'])
            secretKey = str(setting['secretKey'])
            self.interval = float(setting['interval'])

            self.api_spot.setAccount(self.accountID)

        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'BINANCE连接配置缺少字段，请检查'
            self.onLog(log)
            return            

        self.api_spot.active = True
        self.api_spot.connect_Subpot( apiKey , secretKey)
        self.api_spot.spotExchangeInfo()

        # sub = VtSubscribeReq()
        # sub.symbol = "etc_btc.BINANCE"
        # self.subscribe(sub)

        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'BINANCE 接口初始化成功'
        self.onLog(log)

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
        self.api_spot.register(subscribeReq)

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.api_spot.sendOrder(orderReq)

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        return self.api_spot.cancel(cancelOrderReq)

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
        self.api_spot.exit()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            self.qryFunctionList = [self.api_spot.spotAccountInfo , self.api_spot.list_orders]
            #self.qryFunctionList = [self.tradeApi.queryWorkingOrders, self.tradeApi.queryAccount]

    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.total_count += 1
        if self.total_count % self.interval == 0:
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

'''
币安接口
'''
class BinanceApi(BinanceSpotApi):
    """Binance的API实现"""
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        super(BinanceApi , self).__init__()

        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.accountID = "BINANCE"
        self.active = False                     # 若为True则会在断线后自动重连

        self.localID = 0                        # 本地委托号
        self.localSystemDict = {}               # key:localID, value:systemID
        self.systemLocalDict = {}               # key:systemID, value:localID
        self.workingOrderDict = {}              # key:localID, value:order

        self.reqLocalDict = {}                  # key:reqID, value:localID
        self.cancelDict = {}                    # key:localID, value:cancelOrderReq
        self.tradedVolumeDict = {}              # key:localID, value:volume ,已经交易成功的数量
        self.tradeID = 0                        # 本地成交号

        self.tickDict = {}                      # key:symbol, value:tick

        self.registerSymbolSets = set([])

    #----------------------------------------------------------------------
    def list_orders(self):
        for symbol in self.registerSymbolSets:
            self.spotListAllOrders(symbol)

    #----------------------------------------------------------------------
    def register(self, subscribeReq):
        if subscribeReq.symbol not in self.registerSymbolSets:
            symbol = (subscribeReq.symbol.split('.'))[0]
            self.registerSymbolSets.add( symbol )
            self.subscribeSpotTicker( symbol )

    #----------------------------------------------------------------------
    def setAccount(self, useAccountID):
        self.accountID = useAccountID

    #----------------------------------------------------------------------
    def onError(self, method ,data):
        print method , data 

    #----------------------------------------------------------------------
    def sendOrder(self , req):
        """发送委托"""
        # 检查是否填入了价格，禁止市价委托
        if req.priceType != PRICETYPE_LIMITPRICE:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorMsg = u'Binance接口仅支持限价单'
            err.errorTime = datetime.now().strftime('%H:%M:%S')
            self.gateway.onError(err)
            return None

        symbol = (req.vtSymbol.split('.'))[0]
        if req.direction == DIRECTION_LONG:
            reqID = self.spotTrade( symbol_pair = symbol , type_ = "buy" ,  price = req.price , amount = req.volume)
        else:
            reqID = self.spotTrade( symbol_pair = symbol , type_ = "sell" , price = req.price , amount = req.volume)

        self.localID += 1
        localID = str(self.localID)
        self.reqLocalDict[reqID] = localID

        # 推送委托信息
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = req.symbol
        order.exchange = EXCHANGE_BINANCE
        order.vtSymbol = order.symbol

        order.orderID = localID
        order.vtOrderID = '.'.join([order.orderID, order.gatewayName])

        order.direction = req.direction
        if req.direction == DIRECTION_LONG:
            order.offset = OFFSET_OPEN
        else:
            order.offset = OFFSET_CLOSE
        order.price = req.price
        order.tradedVolume = 0
        order.totalVolume = req.volume
        order.orderTime = datetime.now().strftime('%H:%M:%S')
        order.status = STATUS_UNKNOWN

        self.workingOrderDict[localID] = order
        self.gateway.onOrder(order)

        # 返回委托号
        return order.vtOrderID

    #----------------------------------------------------------------------
    def legalSymbolToRightType(self, useSymbol):
        useSymbol = useSymbol.lower()
        return useSymbol[:-3] + "_" + useSymbol[-3:]

    '''
    {
        "timezone": "UTC",
        "serverTime": 1508631584636,
        "rateLimits": [
            {
                "rateLimitType": "REQUESTS",
                "interval": "MINUTE",
                "limit": 1200
            },
            {
                "rateLimitType": "ORDERS",
                "interval": "SECOND",
                "limit": 10
            },
            {
                "rateLimitType": "ORDERS",
                "interval": "DAY",
                "limit": 100000
            }
        ],
        "exchangeFilters": [],
        "symbols": [
            {
                "symbol": "ETHBTC",
                "status": "TRADING",
                "baseAsset": "ETH",
                "baseAssetPrecision": 8,
                "quoteAsset": "BTC",
                "quotePrecision": 8,
                "orderTypes": ["LIMIT", "MARKET"],
                "icebergAllowed": false,
                "filters": [
                    {
                        "filterType": "PRICE_FILTER",
                        "minPrice": "0.00000100",
                        "maxPrice": "100000.00000000",
                        "tickSize": "0.00000100"
                    }, {
                        "filterType": "LOT_SIZE",
                        "minQty": "0.00100000",
                        "maxQty": "100000.00000000",
                        "stepSize": "0.00100000"
                    }, {
                        "filterType": "MIN_NOTIONAL",
                        "minNotional": "0.00100000"
                    }
                ]
            }
        ]
    }
    '''
    #----------------------------------------------------------------------
    def onExchangeInfo(self, data, req, reqID):
        """通过查询交易所，获得 合约具体信息"""
        symbols = data["symbols"]
        for symbol_dic in symbols:
            symbol = self.legalSymbolToRightType(symbol_dic["symbol"])
            status = symbol_dic["status"]
            if status == "TRADING":
                filters = symbol_dic["filters"]
                price_filter = filters[0]
                volume_filter = filters[1]

                contract = VtContractData()
                contract.gatewayName = self.gatewayName
                contract.symbol = '.'.join( [symbol , EXCHANGE_BINANCE] )
                contract.exchange = EXCHANGE_BINANCE
                contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
                contract.name = contract.symbol
                contract.size = float(volume_filter["stepSize"])
                contract.priceTick = float(price_filter["tickSize"])
                contract.productClass = PRODUCT_SPOT
                self.gateway.onContract(contract)

    #----------------------------------------------------------------------
    def onAllTicker(self,msg):
        """币安支持所有 ticker 同时socket过来"""
        for symbol_pair_msg_dic in msg:
            symbol_pair = self.legalSymbolToRightType(symbol_pair_msg_dic["s"])
            price = symbol_pair_msg_dic["p"]

            if symbol_pair not in self.tickDict:
                tick = VtTickData()
                tick.gatewayName = self.gatewayName

                tick.exchange = EXCHANGE_BINANCE
                tick.symbol = '.'.join([symbol_pair, tick.exchange])
                tick.vtSymbol = '.'.join([symbol_pair, tick.exchange])
                self.tickDict[symbol] = tick
            else:
                tick = self.tickDict[symbol_pair]

            tick.highPrice = float(symbol_pair_msg_dic["h"])
            tick.lowPrice = float(symbol_pair_msg_dic["l"])
            tick.lastPrice = (float(symbol_pair_msg_dic["b"]) + float(symbol_pair_msg_dic["a"]))/2.0
            tick.volume = float(symbol_pair_msg_dic["v"])

            tick.bidPrice1 = float(symbol_pair_msg_dic["b"])
            tick.bidVolume1 = float(symbol_pair_msg_dic["B"])
            tick.askPrice1 = float(symbol_pair_msg_dic["a"])
            tick.askVolume1 = float(symbol_pair_msg_dic["A"])

            tick.bidPrice2, tick.bidVolume2 = [0 , 0]
            tick.bidPrice3, tick.bidVolume3 = [0 , 0]
            tick.bidPrice4, tick.bidVolume4 = [0 , 0]
            tick.bidPrice5, tick.bidVolume5 = [0 , 0]

            tick.askPrice2, tick.askVolume2 = [0 , 0]
            tick.askPrice3, tick.askVolume3 = [0 , 0]
            tick.askPrice4, tick.askVolume4 = [0 , 0]
            tick.askPrice5, tick.askVolume5 = [0 , 0]

            tick.datetime , tick.date , tick.time = self.generateDateTime( float(msg["E"]))
            self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def onTick(self, msg):
        symbol_pair = self.legalSymbolToRightType(msg["s"])
        price = msg["p"]

        if symbol_pair not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.exchange = EXCHANGE_BINANCE
            tick.symbol = '.'.join([symbol_pair, tick.exchange])
            tick.vtSymbol = '.'.join([symbol_pair, tick.exchange])
            self.tickDict[symbol_pair] = tick
        else:
            tick = self.tickDict[symbol_pair]

        tick.highPrice = float(msg["h"])
        tick.lowPrice = float(msg["l"])
        tick.lastPrice = (float(msg["b"]) + float(msg["a"]))/2.0
        tick.volume = float(msg["v"])

        tick.bidPrice1 = float(msg["b"])
        tick.bidVolume1 = float(msg["B"])
        tick.askPrice1 = float(msg["a"])
        tick.askVolume1 = float(msg["A"])

        tick.bidPrice2, tick.bidVolume2 = [0 , 0]
        tick.bidPrice3, tick.bidVolume3 = [0 , 0]
        tick.bidPrice4, tick.bidVolume4 = [0 , 0]
        tick.bidPrice5, tick.bidVolume5 = [0 , 0]

        tick.askPrice2, tick.askVolume2 = [0 , 0]
        tick.askPrice3, tick.askVolume3 = [0 , 0]
        tick.askPrice4, tick.askVolume4 = [0 , 0]
        tick.askPrice5, tick.askVolume5 = [0 , 0]

        tick.datetime , tick.date , tick.time = self.generateDateTime( float(msg["E"]))

        self.gateway.onTick(tick)

    '''
    {
      "e": "depthUpdate", // Event type
      "E": 123456789,     // Event time
      "s": "BNBBTC",      // Symbol
      "U": 157,           // First update ID in event
      "u": 160,           // Final update ID in event
      "b": [              // Bids to be updated
        [
          "0.0024",       // price level to be updated
          "10",
          []              // ignore
        ]
      ],
      "a": [              // Asks to be updated
        [
          "0.0026",       // price level to be updated
          "100",          // quantity
          []              // ignore
        ]
      ]
    }

    {u'a': [[u'0.00033700', u'185.00000000', []]], u'b': [], u'E': 1513908280912L, u
's': u'BNBBTC', u'u': 18190614, u'e': u'depthUpdate', u'U': 18190614}
    '''
    #----------------------------------------------------------------------
    def onDepth(self, msg):
        '''
        这里研究了很久， 决定不实现 这个方法！   
        1、因为币安数据推送的 depth 是逐条的，跟原先的方法有差别，显得不好处理
        2、币安五档 socket 推送过来，没有写具体的 币种名。。  导致无法在这个方法中进行区分
        '''
        pass
        # symbol_pair = self.legalSymbolToRightType(msg["s"])
        # if symbol not in self.tickDict:
        #     tick = VtTickData()
        #     tick.gatewayName = self.gatewayName
        #     tick.exchange = EXCHANGE_BINANCE
        #     tick.symbol = '.'.join([symbol, tick.exchange])
        #     tick.vtSymbol = '.'.join([symbol, tick.exchange])

        #     self.tickDict[symbol] = tick
        # else:
        #     tick = self.tickDict[symbol]

        # bids = msg["b"]
        # asks = msg["a"]

        # try:
        #     tick.bidPrice1, tick.bidVolume1 = bids[0]
        #     tick.bidPrice2, tick.bidVolume2 = bids[1]
        #     tick.bidPrice3, tick.bidVolume3 = bids[2]
        #     tick.bidPrice4, tick.bidVolume4 = bids[3]
        #     tick.bidPrice5, tick.bidVolume5 = bids[4]
        # except Exception,ex:
        #     pass

        # try:
        #     tick.askPrice1, tick.askVolume1 = asks[0]
        #     tick.askPrice2, tick.askVolume2 = asks[1]
        #     tick.askPrice3, tick.askVolume3 = asks[2]
        #     tick.askPrice4, tick.askVolume4 = asks[3]
        #     tick.askPrice5, tick.askVolume5 = asks[4]
        # except Exception,ex:
        #     pass

        # now = self.generateDateTime( float(msg["E"]))
        # tick.time = now.strftime('%H:%M:%S')
        # tick.date = now.strftime('%Y%m%d')
        # tick.datetime = now

        # self.gateway.onTick(tick)

    '''
            {
                "e": "trade",     # Event type
                "E": 123456789,   # Event time
                "s": "BNBBTC",    # Symbol
                "t": 12345,       # Trade ID
                "p": "0.001",     # Price
                "q": "100",       # Quantity
                "b": 88,          # Buyer order Id
                "a": 50,          # Seller order Id
                "T": 123456785,   # Trade time
                "m": true,        # Is the buyer the market maker?
                "M": true         # Ignore.
            }
    '''
    #----------------------------------------------------------------------
    def onTrades(self, msg):
        pass

    '''
    {
            "makerCommission": 15,
            "takerCommission": 15,
            "buyerCommission": 0,
            "sellerCommission": 0,
            "canTrade": true,
            "canWithdraw": true,
            "canDeposit": true,
            "balances": [
                {
                    "asset": "BTC",
                    "free": "4723846.89208129",
                    "locked": "0.00000000"
                },
                {
                    "asset": "LTC",
                    "free": "4763368.68006011",
                    "locked": "0.00000000"
                }
            ]
    }
    '''
    #----------------------------------------------------------------------
    def onGetAccount(self, data, req, reqID):

        balances = data["balances"]
        account = VtAccountData()
        account.gatewayName = self.gatewayName
        account.accountID = self.accountID
        account.vtAccountID = '.'.join([ self.gatewayName , self.accountID])
        account.balance = 0.0
        account.available = 0.0
        account.margin = 1.0
        account.closeProfit = 0.0
        account.positionProfit = 0.0
        account.commission = 0.0

        self.gateway.onAccount(account)

        for b_symbol_dic in balances:
            symbol = b_symbol_dic["asset"].lower()
            posObj = VtPositionData()
            posObj.gatewayName = self.gatewayName
            posObj.symbol = symbol + "." + EXCHANGE_BINANCE
            posObj.exchange = EXCHANGE_BINANCE
            posObj.vtSymbol = posObj.symbol
            posObj.direction = DIRECTION_NET
            posObj.vtPositionName = '.'.join( [posObj.vtSymbol, posObj.direction])
            posObj.ydPosition = float(b_symbol_dic["free"]) + float(b_symbol_dic["locked"])
            posObj.position = float(b_symbol_dic["free"]) + float(b_symbol_dic["locked"])
            posObj.frozen = float(b_symbol_dic["locked"])
            posObj.positionProfit = 0

            self.gateway.onPosition(posObj)

    '''
      [
            {
                "symbol": "LTCBTC",
                "orderId": 1,
                "clientOrderId": "myOrder1",
                "price": "0.1",
                "origQty": "1.0",
                "executedQty": "0.0",
                "status": "NEW",
                "timeInForce": "GTC",
                "type": "LIMIT",
                "side": "BUY",
                "stopPrice": "0.0",
                "icebergQty": "0.0",
                "time": 1499827319559
            }
        ]
Order status:

NEW
PARTIALLY_FILLED
FILLED
CANCELED
PENDING_CANCEL (currently unused)
REJECTED
EXPIRED

Order side:

BUY
SELL

Symbol status:

PRE_TRADING
TRADING
POST_TRADING
END_OF_DAY
HALT
AUCTION_MATCH
BREAK

    '''
    #----------------------------------------------------------------------
    def onGetOpenOrders(self, data, req, reqID):
        pass
        # for symbol_dic in data:
        #     symbol_pair = self.legalSymbolToRightType(symbol_dic["symbol"])

    '''
    [
                {
                    "symbol": "LTCBTC",
                    "orderId": 1,
                    "clientOrderId": "myOrder1",
                    "price": "0.1",
                    "origQty": "1.0",
                    "executedQty": "0.0",
                    "status": "NEW",
                    "timeInForce": "GTC",
                    "type": "LIMIT",
                    "side": "BUY",
                    "stopPrice": "0.0",
                    "icebergQty": "0.0",
                    "time": 1499827319559
                }
            ]
    '''
    #----------------------------------------------------------------------
    def onGetAllOrders(self, data, req, reqID):
        local_system_dict_keys = self.systemLocalDict.keys()
        stile_live_order_system_id = [ str(x["orderId"]) for x in data]

        for use_order in data:
            systemID = str(use_order["orderId"])
            status = use_order["status"]
            side = use_order["side"]
            tradedVolume = float(use_order["executedQty"])
            use_dt , use_date, now_time = self.generateDateTime(use_order["time"])
            # now_time = self.generateDateTime(use_order["time"])
            if systemID in local_system_dict_keys:
                localID = self.systemLocalDict[systemID]
                order = self.workingOrderDict.get(localID, None)
                if order != None:
                    bef_has_volume = self.tradedVolumeDict.get(localID , 0.0)
                    newTradeVolume = tradedVolume - bef_has_volume
                    order.tradedVolume = tradedVolume

                    if newTradeVolume > 0.000001:
                        trade = VtTradeData()
                        trade.gatewayName = self.gatewayName
                        trade.symbol = order.symbol
                        trade.vtSymbol = order.vtSymbol

                        self.tradeID += 1
                        trade.tradeID = str(self.tradeID)
                        trade.vtTradeID = '.'.join([trade.tradeID, trade.gatewayName])
                        trade.orderID = order.orderID
                        trade.vtOrderID =  order.vtOrderID

                        trade.volume = newTradeVolume
                        trade.price = order.price
                        trade.direction = order.direction
                        trade.offset = order.offset
                        trade.exchange = order.exchange
                        trade.tradeTime = now_time

                        self.gateway.onTrade(trade)

                    if status == "FILLED":
                        # 说明这个单子成交完毕了！
                        order.status = STATUS_ALLTRADED
                        self.gateway.onOrder(order)

                        del self.tradedVolumeDict[localID]
                        del self.systemLocalDict[systemID]
                        del self.workingOrderDict[localID]

                    elif status == "CANCELED":
                        order.status = STATUS_CANCELLED
                        self.gateway.onOrder(order)

                        del self.tradedVolumeDict[localID]
                        del self.systemLocalDict[systemID]
                        del self.workingOrderDict[localID]

                    elif status == "PARTIALLY_FILLED":
                        order.status = STATUS_PARTTRADED
                        self.gateway.onOrder(order)

                    elif status == "NEW":
                        order.status = STATUS_NOTTRADED
                        self.gateway.onOrder(order)
            else:
                # 说明是以前发的单子
                self.localID += 1
                localID = str(self.localID)

                symbol_pair = self.legalSymbolToRightType(use_order["symbol"])

                if status not in ["FILLED","CANCELED"]:
                    order = VtOrderData()
                    order.gatewayName = self.gatewayName
                    order.symbol = symbol_pair + "." + self.gatewayName
                    order.exchange = EXCHANGE_BINANCE
                    order.vtSymbol = order.symbol
                    order.orderID = localID
                    order.vtOrderID = '.'.join([order.orderID, order.gatewayName])
                    order.direction = DIRECTION_NET
                    order.offset = OFFSET_OPEN
                    if side == "SELL":
                        order.direction = DIRECTION_SHORT
                        order.offset = OFFSET_CLOSE
                    
                    order.price = float(use_order["price"])
                    order.totalVolume = float(use_order["origQty"])
                    order.tradedVolume = float(use_order["executedQty"])
                    use_dt , use_date, use_time = self.generateDateTime(use_order["time"])
                    order.orderTime = use_time

                    if status == "PARTIALLY_FILLED":
                        order.status = STATUS_PARTTRADED
                    elif status == "NEW":
                        order.status = STATUS_NOTTRADED

                    self.workingOrderDict[localID] = order
                    self.systemLocalDict[systemID] = localID
                    self.localSystemDict[localID] = systemID
                    self.tradedVolumeDict[localID] = float(use_order["executedQty"])
                    
                    self.gateway.onOrder(order)


    #----------------------------------------------------------------------
    def cancel(self, req):
        localID = req.orderID
        if localID in self.localSystemDict:
            systemID = self.localSystemDict[localID]
            order = self.workingOrderDict[localID]
            use_symbol = (order.symbol.split('.'))[0]

            # print "spotCancelOrder" , use_symbol , systemID
            self.spotCancelOrder( use_symbol, systemID )
        else:
            self.cancelDict[localID] = req


    '''
    Response ACK:
    {
      "symbol": "BTCUSDT",
      "orderId": 28,
      "clientOrderId": "6gCrw2kRUAF9CvJDGP16IP",
      "transactTime": 1507725176595
    }
    Response RESULT:
    {
      "symbol": "BTCUSDT",
      "orderId": 28,
      "clientOrderId": "6gCrw2kRUAF9CvJDGP16IP",
      "transactTime": 1507725176595,
      "price": "0.00000000",
      "origQty": "10.00000000",
      "executedQty": "10.00000000",
      "status": "FILLED",
      "timeInForce": "GTC",
      "type": "MARKET",
      "side": "SELL"
    }

    参数 newOrderRespType    ENUM    NO  Set the response JSON.  (ACK, RESULT, or FULL); default: RESULT.

    默认返回格式  restful 
    '''
    #----------------------------------------------------------------------
    def onGetBuyOrder(self, data, req, reqID):
        symbol = self.legalSymbolToRightType(data["symbol"])

        localID = self.reqLocalDict[reqID]
        systemID = str(data['orderId'])

        self.localSystemDict[localID] = systemID
        self.systemLocalDict[systemID] = localID

        # print systemID , localID
        # 撤单
        if localID in self.cancelDict:
            req = self.cancelDict[localID]
            self.cancel(req)
            del self.cancelDict[localID]

        # 推送委托信息
        order = self.workingOrderDict[localID]
        volume = float(data["executedQty"])
        origQty = float(data["origQty"])
        status = data["status"]

        order.tradedVolume = volume

        if status == "FILLED":
            order.status = STATUS_ALLTRADED
        elif status == "PARTIALLY_FILLED":
            order.status = STATUS_PARTTRADED
        elif status == "NEW":
            order.status = STATUS_NOTTRADED
        elif status == "CANCELED":
            order.status = STATUS_CANCELLED

        if status in ["PARTIALLY_FILLED","FILLED"]:
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            trade.symbol = order.symbol
            trade.vtSymbol = order.vtSymbol

            self.tradeID += 1
            trade.tradeID = str(self.tradeID)
            trade.vtTradeID = '.'.join([trade.tradeID, trade.gatewayName])
            trade.orderID = order.orderID
            trade.vtOrderID =  order.vtOrderID

            trade.volume = float(volume)
            trade.price = order.price
            trade.direction = order.direction
            trade.offset = order.offset
            trade.exchange = order.exchange
            use_dt , use_date, now_time = self.generateDateTime(data["transactTime"])
            trade.tradeTime = now_time

            self.gateway.onTrade(trade)

        self.tradedVolumeDict[localID] = volume
        self.gateway.onOrder(order)

    '''
    Response ACK:
    {
      "symbol": "BTCUSDT",
      "orderId": 28,
      "clientOrderId": "6gCrw2kRUAF9CvJDGP16IP",
      "transactTime": 1507725176595
    }
    Response RESULT:
    {
      "symbol": "BTCUSDT",
      "orderId": 28,
      "clientOrderId": "6gCrw2kRUAF9CvJDGP16IP",
      "transactTime": 1507725176595,
      "price": "0.00000000",
      "origQty": "10.00000000",
      "executedQty": "10.00000000",
      "status": "FILLED",
      "timeInForce": "GTC",
      "type": "MARKET",
      "side": "SELL"
    }
    '''
    #----------------------------------------------------------------------
    def onGetSellOrder(self, data, req, reqID):
        symbol = self.legalSymbolToRightType(data["symbol"])
        localID = self.reqLocalDict[reqID]
        systemID = str(data['orderId'])

        self.localSystemDict[localID] = systemID
        self.systemLocalDict[systemID] = localID

        # 撤单
        if localID in self.cancelDict:
            req = self.cancelDict[localID]
            self.cancel(req)
            del self.cancelDict[localID]

        # 推送委托信息
        order = self.workingOrderDict[localID]
        volume = float(data["executedQty"])

        if float(volume) < 0.00001:
            order.status = STATUS_NOTTRADED
        else:
            order.status = STATUS_PARTTRADED

        self.tradedVolumeDict[localID] = volume

        if float(volume) > 0.00001:
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            trade.symbol = order.symbol
            trade.vtSymbol = order.vtSymbol

            self.tradeID += 1
            trade.tradeID = str(self.tradeID)
            trade.vtTradeID = '.'.join([trade.tradeID, trade.gatewayName])
            trade.orderID = order.orderID
            trade.vtOrderID =  order.vtOrderID

            trade.volume = float(volume)
            trade.price = order.price
            trade.direction = order.direction
            trade.offset = order.offset
            trade.exchange = order.exchange
            use_dt , use_date, now_time = self.generateDateTime(data["transactTime"])
            trade.tradeTime = now_time

            self.gateway.onTrade(trade)

        self.gateway.onOrder(order)
    '''
    {
      "symbol": "LTCBTC",
      "origClientOrderId": "myOrder1",
      "orderId": 1,
      "clientOrderId": "cancelMyOrder1"
    }
    '''
    #----------------------------------------------------------------------
    def onGetCancelOrder(self, data, req, reqID):
        systemID = str(data["orderId"])
        localID = self.systemLocalDict[systemID]

        order = self.workingOrderDict[localID]
        order.status = STATUS_CANCELLED

        del self.workingOrderDict[localID]
        del self.systemLocalDict[systemID]
        del self.localSystemDict[localID]
        self.gateway.onOrder(order)

    #----------------------------------------------------------------------
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(float(s)/1e3)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return dt , date, time
