# encoding: UTF-8

'''
vn.coincheck的gateway接入
'''
from __future__ import print_function
import os
import json
from datetime import datetime
from copy import copy
from threading import Condition
from Queue import Queue
from threading import Thread

import json
from vnpy.api.korbit import vnkorbit , KORBIT_ALL_SYMBOL_PAIR , KORBIT_ALL_SYMBOLS
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath

from datetime import datetime , timedelta

korbit_order_status_map ={}
korbit_order_status_map["partially_filled"] = STATUS_PARTTRADED
korbit_order_status_map["unfilled"] = STATUS_NOTTRADED
korbit_order_status_map["filled"] = STATUS_ALLTRADED

class korbitGateway(VtGateway):
    """korbit接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName = "KORBIT"):
        """Constructor"""
        super(korbitGateway , self).__init__(eventEngine, gatewayName)

        self.tradeApi = KorbitTradeApi(self)
        self.dataApi = KorbitDataApi(self)

        self.fileName = self.gatewayName + "_connect.json"
        self.filePath = getJsonPath(self.fileName, __file__)       
        self.accountID = "NONE"

        self.total_count = 0
        self.delayTime = 3

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
            self.accountID = str(setting["accountID"])
            self.accessKey = str(setting['accessKey'])
            self.secretKey = str(setting['secretKey'])
            self.username = str(setting["username"])
            self.password = str(setting["password"])
            self.interval = setting['interval']
            self.debug = setting['debug']
            
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 设置账户ID
        self.tradeApi.setUserInfo( self.accountID , self.username , self.password)

        # 初始化接口
        self.tradeApi.init(self.accessKey, self.secretKey , self.username , self.password)
        self.writeLog(u'交易接口初始化成功')
        
        self.dataApi.connect(self.interval , self.debug)
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
        self.dataApi.subscribe(subscribeReq)
        self.tradeApi.subscribe(subscribeReq)

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.tradeApi.sendOrder(orderReq)

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        return self.tradeApi.cancel(cancelOrderReq)

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
            self.qryFunctionList = [ self.tradeApi.list_market_all_register , self.tradeApi.user_balances] 
            self.startQuery()  

    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.total_count += 1
        if self.total_count % self.delayTime == 0:
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

class KorbitTradeApi(vnkorbit.Korbit_TradeApi):
    def __init__(self, gateway):
        super(KorbitTradeApi , self).__init__()

        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        self.accountID = "KORBIT"
        self.DEBUG = False

        self.localID = 0            # 本地委托号
        self.localSystemDict = {}   # key:localID, value:systemID
        self.systemLocalDict = {}   # key:systemID, value:localID
        self.workingOrderDict = {}  # key:localID, value:order
        self.reqLocalDict = {}      # key:reqID, value:localID
        self.cancelDict = {}        # key:localID, value:cancelOrderReq

        self.tradedVolumeDict = {}  # key:localID, value:volume ,已经交易成功的数量

        self.tradeID = 0            # 本地成交号

        self.registerSymbolPair = set([])

    #--------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        use_symbol = (subscribeReq.symbol.split('.'))[0]
        self.registerSymbolPair.add( use_symbol )

    #--------------------------------------------------------------------
    def list_market_all_register(self):
        for symbol_pair in self.registerSymbolPair:
            self.list_market_orders(currency_pair = symbol_pair , offset = 0 , limit = 50)

    #--------------------------------------------------------------------
    def setUserInfo(self, _accountID , _username , _password):
        self.accountID = _accountID
        self.username = _username
        self.password = _password

    '''
    发送系统委托
    '''
    def sendOrder(self, req):
        """发送委托"""
        # 检查是否填入了价格，禁止市价委托
        if req.priceType != PRICETYPE_LIMITPRICE:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorMsg = u'Korbit接口仅支持限价单'
            err.errorTime = datetime.now().strftime('%H:%M:%S')
            self.gateway.onError(err)
            return None

        symbol = req.vtSymbol

        currency = (symbol.split('.'))[0]
        if req.direction == DIRECTION_LONG:
            reqID = self.buy_currency( coin_amount = req.volume , price = req.price , currency_pair = currency)
        else:
            reqID = self.sell_currency( coin_amount = req.volume , price = req.price , currency_pair = currency)

        self.localID += 1
        localID = str(self.localID)
        self.reqLocalDict[reqID] = localID


        # 推送委托信息
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = req.symbol
        order.exchange = EXCHANGE_KORBIT
        order.vtSymbol = order.symbol

        order.orderID = localID
        order.vtOrderID = '.'.join([order.orderID, order.gatewayName])

        order.direction = req.direction
        if req.direction == DIRECTION_LONG:
            order.offset = OFFSET_OPEN
        else:
            order.offset = OFFSET_CLOSE
        order.price = req.price
        order.tradedVolume = 0.0
        order.totalVolume = req.volume
        order.orderTime = datetime.now().strftime('%H:%M:%S')
        order.status = STATUS_UNKNOWN

        self.workingOrderDict[localID] = order
        self.gateway.onOrder(order)

        # 返回委托号
        return order.vtOrderID

    #--------------------------------------------------------------------
    def cancel(self, req):
        localID = req.orderID
        if localID in self.localSystemDict:
            systemID = self.localSystemDict[localID]
            symbol_pair = (req.symbol.split('.'))[0]
            self.cancel_orders( systemID , currency_pair = symbol_pair)
        else:
            self.cancelDict[localID] = req

    #--------------------------------------------------------------------
    def onError(self, method ,data):
        print(method , data) 

    #--------------------------------------------------------------------
    def on_buy_currency(self, data , req, reqID):
        if data["status"] != "success":
            print("Error in on_buy_currency")
            print(data)
        else:
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
            
            order.status = STATUS_NOTTRADED

            self.tradedVolumeDict[localID] = 0.0
            self.gateway.onOrder(order)

    #--------------------------------------------------------------------
    def on_sell_currency(self, data , req, reqID):
        """卖出回调"""
        if data["status"] != "success":
            print("Error in on_sell_currency")
        else:
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
            order.status = STATUS_NOTTRADED
            
            self.tradedVolumeDict[localID] = 0.0
            self.gateway.onOrder(order)

            print("what")

    #--------------------------------------------------------------------
    def on_list_exchange_orders(self, data , req, reqID):
        if len(data) > 0:
            local_system_dict_keys = self.systemLocalDict.keys()
            for d_order in data:
                systemID = str(d_order["id"])
                if systemID in local_system_dict_keys:
                    localID = self.systemLocalDict[systemID]
                    order = self.workingOrderDict.get(localID, None)
                    if order != None:
                        bef_has_volume = self.tradedVolumeDict.get(localID , 0.0)

                        total_need_volume = float(d_order["order_amount"])
                        nowTradeVolume = float(d_order["filled_amount"])
                        status = d_order["status"]

                        order.tradedVolume = nowTradeVolume
                        order.totalVolume = total_need_volume

                        newTradeVolume = nowTradeVolume - bef_has_volume

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
                            trade.tradeTime = datetime.now().strftime('%H:%M:%S')

                            self.gateway.onTrade(trade)

                            if korbit_order_status_map[status] == STATUS_ALLTRADED:
                                order.status = STATUS_ALLTRADED
                                del self.tradedVolumeDict[localID]
                                del self.systemLocalDict[systemID]
                                del self.workingOrderDict[localID]
                            else:
                                order.status = STATUS_PARTTRADED
                                self.tradedVolumeDict[localID] = nowTradeVolume
                            self.gateway.onOrder(order)
                else:
                    total_need_volume = float(d_order["order_amount"])
                    nowTradeVolume = float(d_order["filled_amount"])
                    status = d_order["status"]
                    side = d_order["side"]

                    if korbit_order_status_map[status] != STATUS_ALLTRADED:
                        # 说明这是一个尚未被系统记录的订单
                        self.localID += 1
                        localID = str(self.localID)
                        order = VtOrderData()
                        order.gatewayName = self.gatewayName
                        order.symbol = d_order["currency_pair"] + "." + self.gatewayName
                        order.exchange = EXCHANGE_KORBIT
                        order.vtSymbol = order.symbol

                        order.orderID = localID
                        order.vtOrderID = '.'.join([order.orderID, order.gatewayName])

                        if side == "bid":
                            order.direction = DIRECTION_LONG
                            order.offset = OFFSET_OPEN
                        else:
                            order.direction = DIRECTION_SHORT
                            order.offset = OFFSET_CLOSE
                        
                        order.price = float(d_order["price"])
                        order.tradedVolume = float(d_order["filled_amount"])
                        order.totalVolume = float(d_order["order_amount"])
                        """ """
                        dt , date , utime = self.generateDateTime(d_order["created_at"])
                        order.orderTime = date + " " + utime
                        order.status = korbit_order_status_map[status]

                        self.workingOrderDict[localID] = order
                        self.systemLocalDict[systemID] = localID
                        self.localSystemDict[localID] = systemID
                        self.gateway.onOrder(order)

    #--------------------------------------------------------------------
    def onCancelOrders(self, data , req, reqID):
        for d_order in data:
            systemID = d_order["orderId"]
            status = d_order["status"]

            if status == "success":
                localID = self.systemLocalDict[systemID]
                order = self.workingOrderDict[localID]
                order.status = STATUS_CANCELLED

                del self.workingOrderDict[localID]
                del self.systemLocalDict[systemID]
                del self.localSystemDict[localID]
                self.gateway.onOrder(order)

    #--------------------------------------------------------------------
    def onBalances(self, data , req, reqID):
        all_keys_returns = data.keys()

        total_balance = 0.0
        for symbol in all_keys_returns:
            if symbol in KORBIT_ALL_SYMBOLS:
                val = data[symbol]
                ava = float(val["available"])
                trade_vol = float(val["trade_in_use"])

                posObj = VtPositionData()
                posObj.gatewayName = self.gatewayName
                posObj.symbol = symbol + "." + EXCHANGE_KORBIT
                posObj.exchange = EXCHANGE_KORBIT
                posObj.vtSymbol = posObj.symbol
                posObj.direction = DIRECTION_LONG
                posObj.vtPositionName = '.'.join( [posObj.vtSymbol, posObj.direction])
                posObj.ydPosition = ava + trade_vol
                posObj.position = ava + trade_vol
                posObj.frozen = trade_vol
                posObj.positionProfit = 0
                self.gateway.onPosition(posObj)


        account = VtAccountData()
        account.gatewayName = self.gatewayName
        account.accountID = self.accountID
        account.vtAccountID = '.'.join([ self.gatewayName , self.accountID])
        account.balance = total_balance
        account.available = total_balance

        account.margin = 1.0
        account.closeProfit = 0.0
        account.positionProfit = 0.0
        account.commission = 0.0

        self.gateway.onAccount(account)
        
    #--------------------------------------------------------------------
    def generateDateTime(self , s):
        dt = datetime.fromtimestamp(float(s)/1e3)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return dt , date, time

class KorbitDataApi(vnkorbit.Korbit_DataApi):
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(KorbitDataApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName

        self.tickDict = {}      # key:symbol, value:tick

    #----------------------------------------------------------------------
    def subscribeSingle(self, symbol_pair):
        self.subscribeTick(symbol_pair)
        self.subscribeOrderbooks(symbol_pair)
        # self.subscribeTrades(symbol_pair)

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        self.subscribeSingle( subscribeReq.symbol)

    #----------------------------------------------------------------------
    def connect(self, interval , market , debug = False):
        self.init(interval , debug)
        
        self.subscribeSingle("bch_krw")
        
        # 订阅行情并推送合约信息
        for symbol_pair in KORBIT_ALL_SYMBOL_PAIR:
            #self.subscribeSingle( symbol_pair)

            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            contract.symbol = symbol_pair
            contract.exchange = EXCHANGE_KORBIT
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = symbol_pair
            contract.size = 0.0001
            contract.priceTick = 0.0001
            contract.productClass = PRODUCT_SPOT
            self.gateway.onContract(contract)

    #----------------------------------------------------------------------
    def onTick(self, data):
        """实时成交推送"""
        symbol = data["symbol"]
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.exchange = EXCHANGE_KORBIT
            tick.symbol = '.'.join([symbol, tick.exchange])
            tick.vtSymbol = '.'.join([symbol, tick.exchange])
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        tick.highPrice = float(data['high'])
        tick.lowPrice = float(data['low'])
        tick.lastPrice = float(data['last'])
        tick.volume = float(data['volume'])

        tick.datetime , tick.date , tick.time = self.generateDateTime(data["timestamp"])

        # now = datetime.now()
        # tick.time = now.strftime('%H:%M:%S')
        # tick.date = now.strftime('%Y%m%d')
        # tick.datetime = now

    #----------------------------------------------------------------------
    def onTrades(self, data):
        """实时成交推送"""
        #print data
        pass

    #----------------------------------------------------------------------
    def onOrderbooks(self, data):
        """实时成交推送"""
        symbol = data["symbol"]

        bids = data["bids"]
        asks = data["asks"]
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.symbol = symbol
            tick.exchange = EXCHANGE_KORBIT
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        bids = [ (float(x[0]) , float(x[1])) for x in bids ]
        asks = [ (float(x[0]) , float(x[1])) for x in asks ]
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


        tick.datetime , tick.date , tick.time = self.generateDateTime(data["timestamp"])

        # now = datetime.now()
        # tick.time = now.strftime('%H:%M:%S')
        # tick.date = now.strftime('%Y%m%d')
        # tick.datetime = now

        self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(float(s)/1e3)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return dt , date, time