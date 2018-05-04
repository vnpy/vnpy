# encoding: UTF-8

import os
import json
from datetime import datetime
from copy import copy
from threading import Condition
from Queue import Queue
from threading import Thread

import json
from vnpy.api.huobi import Huobi_TradeApi , Huobi_DataApi , Huobi_DataApiSocket , wss_huobi_hosts
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath
from vnpy.Function import systemSymbolToVnSymbol , VnSymbolToSystemSymbol

from datetime import datetime , timedelta


'''
火币接口
'''
class huobiGateway(VtGateway):
    """火币 接口"""
    #----------------------------------------------------------------------
    def __init__(self, eventEngine , gatewayName='HUOBI'):
        """Constructor"""
        super(huobiGateway , self).__init__(eventEngine, gatewayName)
        
        self.tradeApi = HuobiTradeApi(self)
        self.dataApi = HuobiSocketDataApi(self)
        
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)       

        self.connected = False

        self.qryEnabled = True

        self.accountID = "None"

        self.total_count = 0
        self.delayTime = 3

        self.logger = VtLogger(  "./temp/%s.log" % (gatewayName) )

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
            accessKey = str(setting['accessKey'])
            secretKey = str(setting['secretKey'])
            interval = setting['interval']
            useAccountID = str(setting['accountID'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 设置账户ID
        self.tradeApi.setAccountID( useAccountID)

        # 初始化接口
        self.tradeApi.init(accessKey, secretKey)
        self.writeLog(u'交易接口初始化成功')

        self.tradeApi.get_symbols()
        self.writeLog(u'获得Huobi币种合约请求已发送')
        
        #self.dataApi.connect(interval,  debug)
        self.dataApi.connect()
        self.writeLog(u'行情接口初始化成功')

        # sub = VtSubscribeReq()
        # sub.symbol = "etc_btc.HUOBI"
        # self.subscribe(sub)

        # 启动查询
        self.initQuery()
        self.startQuery() 

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情，自动订阅全部行情，无需实现"""

        self.tradeApi.subscribeSymbol(subscribeReq)
        self.dataApi.subscribeSymbol(subscribeReq)

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
            self.qryFunctionList = [self.tradeApi.get_balance , self.tradeApi.order_all_list]
            #self.qryFunctionList = [self.tradeApi.queryWorkingOrders, self.tradeApi.queryAccount]

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


'''
HuobiTradeApi
'''
class HuobiTradeApi(Huobi_TradeApi):
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(HuobiTradeApi, self).__init__()

        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        self.accountID = "HUOBI"
        self.DEBUG = False

        self.localID = 0            # 本地委托号
        self.localSystemDict = {}   # key:localID, value:systemID
        self.systemLocalDict = {}   # key:systemID, value:localID
        self.workingOrderDict = {}  # key:localID, value:order
        self.reqLocalDict = {}      # key:reqID, value:localID
        self.cancelDict = {}        # key:localID, value:cancelOrderReq

        self.tradedVolumeDict = {}      # key:localID, value:volume ,已经交易成功的数量

        self.registerSymbols = set([])

        self.tradeID = 0            # 本地成交号

        self.amountScaleDict = {}   # 

        self.cancelSystemOrderFilter = set([])       # 已经撤销的系统委托，可能会因为 huobi 反应特别慢，而失败，所以加个东西过滤 ,以免造成重复订单

        self.cacheSendLocalOrder = set([])           # 缓存已经发的订单local ,用于匹配订单

        # for test
        # order = VtOrderData()
        # order.gatewayName = self.gatewayName
        # order.symbol = "zil_eth"
        # order.exchange = EXCHANGE_HUOBI
        # order.vtSymbol = "zil_eth." + EXCHANGE_HUOBI 

        # order.orderID = "0"
        # order.vtOrderID = '.'.join([order.orderID, order.gatewayName])

        # order.direction = DIRECTION_SHORT
        # order.offset = OFFSET_CLOSE

        # order.price = 0.0002494
        # order.tradedVolume = 0
        # order.totalVolume = 300
        # order.orderTime = datetime.now().strftime('%H:%M:%S')
        # order.status = STATUS_UNKNOWN

        # self.workingOrderDict["0"] = order

        # self.cacheSendLocalOrder.add("0")

    #---------------------------------------------------------------------
    def subscribeSymbol(self, subscribeReq):
        use_symbol = (subscribeReq.symbol.split('.'))[0]
        if use_symbol not in self.registerSymbols:
            self.registerSymbols.add(use_symbol)

    #---------------------------------------------------------------------
    def order_all_list(self):
        # for systemID in self.systemLocalDict.keys():
        #     self.order_info(systemID)
        for use_symbol in self.registerSymbols:
            use_symbol = (use_symbol.split('.'))[0]
            # print VnSymbolToSystemSymbol(use_symbol)
            self.orders_list(VnSymbolToSystemSymbol(use_symbol))

    #---------------------------------------------------------------------
    def setAccountID(self, useAccountID):
        self.accountID = useAccountID

    #----------------------------------------------------------------------
    def onError(self, method ,data):
        # print method , data 
        self.gateway.writeError( str(data) , str(method))
        
    '''
    发送系统委托
    '''
    def sendOrder(self, req):
        """发送委托"""
        # 检查是否填入了价格，禁止市价委托
        if req.priceType != PRICETYPE_LIMITPRICE:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorMsg = u'Huobi接口仅支持限价单'
            err.errorTime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            self.gateway.onError(err)
            return None

        symbol = (req.vtSymbol.split('.'))[0]

        req.volume = round(req.volume , int(self.amountScaleDict[systemSymbolToVnSymbol(req.symbol)]) )
        
        # print "req.price , req.volume" , req.price , req.volume
        if req.direction == DIRECTION_LONG:
            reqID = self.spotTrade( symbol = systemSymbolToVnSymbol(symbol) , price = req.price , amount = req.volume , _type = "buy-limit" , source = "api")
        else:
            reqID = self.spotTrade( symbol = systemSymbolToVnSymbol(symbol) , price = req.price , amount = req.volume , _type = "sell-limit" , source = "api")

        self.localID += 1
        localID = str(self.localID)
        self.reqLocalDict[reqID] = localID

        # 推送委托信息
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = symbol + "." + EXCHANGE_HUOBI
        order.exchange = EXCHANGE_HUOBI
        order.vtSymbol =  symbol+ "." + EXCHANGE_HUOBI

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
        order.orderTime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        order.status = STATUS_UNKNOWN

        self.workingOrderDict[localID] = order

        self.cacheSendLocalOrder.add(localID)
        
        self.gateway.writeLog( "sendOrder cacheSendLocalOrder add localID %s" % (localID))

        # self.gateway.onOrder(order)

        # 返回委托号
        return order.vtOrderID

    '''
        {u'status': u'ok', u'data': [{u'price-precision': 6, u'base-currency': u'nas', u
'symbol-partition': u'innovation', u'quote-currency': u'btc', u'amount-precision
': 4}, {u'price-precision': 2, u'base-currency': u'omg', u'symbol-partition': u'
main', u'quote-currency': u'usdt', u'amount-precision': 4}]}
    '''
    #----------------------------------------------------------------------
    def onAllSymbols(self,data, req, reqID):
        super(HuobiTradeApi, self).onAllSymbols(data, req, reqID)
        data_info = data["data"]
        for inf in data_info:
            symbol_pair = inf["base-currency"] + "_" + inf["quote-currency"]

            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            contract.symbol = symbol_pair + "." + EXCHANGE_HUOBI
            contract.exchange = EXCHANGE_HUOBI
            contract.vtSymbol = symbol_pair + "." + EXCHANGE_HUOBI
            contract.name = u'HUOBI现货%s' % symbol_pair
            contract.size = 0.1 ** int(inf["price-precision"])
            contract.priceTick =  0.1 ** int(inf["price-precision"])
            contract.productClass = PRODUCT_SPOT

            self.amountScaleDict[symbol_pair] = float(inf["amount-precision"])
            self.gateway.onContract(contract)

    '''
    {u'status': u'ok', u'data': [{u'subtype': u'', u'state': u'working', u'type': u'
spot', u'id': 932763}]}
    '''
    #----------------------------------------------------------------------
    def onGetAccounts(self,data, req, reqID):
        if data["status"] == "ok":
            self.account_id = int(data["data"][0]["id"])
        else:
            self.gateway.writeError("Error in onGetAccounts , the status is not ok! data %s" % (str(data)) , "h1")

    '''
    {u'status': u'ok', u'data': {u'list': [{u'currency': u'ast', u'balance': u'0.000
000000000000000', u'type': u'trade'}, {u'currency': u'zrx', u'balance': u'0.000000000000000000', u'type': u'frozen'}]
, u'state': u'working', u'type': u'spot', u'id': 932763}}
    '''
    #----------------------------------------------------------------------
    def onGetBalance(self, data, req, reqID):
        if data["status"] == "ok":
            try:
                dataInfo = data["data"]
                dataInfoList = dataInfo["list"]
                posTradeDict = {}
                posFrozeDict = {}
                for ll in dataInfoList:
                    if ll["type"] == "trade":
                        posTradeDict[ll["currency"]] = float(ll["balance"])
                    elif ll["type"] == "frozen":
                        posFrozeDict[ll["currency"]] = float(ll["balance"])

                all_keys = [ str(x) for x in posTradeDict.keys() if x in posFrozeDict.keys()]
                for symbol in all_keys:
                    posObj = VtPositionData()
                    posObj.gatewayName = self.gatewayName
                    posObj.symbol = symbol + "." + EXCHANGE_HUOBI
                    posObj.exchange = EXCHANGE_HUOBI
                    posObj.vtSymbol = posObj.symbol
                    posObj.direction = DIRECTION_NET
                    posObj.vtPositionName = '.'.join( [posObj.vtSymbol, posObj.direction])
                    posObj.ydPosition = float(posFrozeDict[symbol]) + float(posTradeDict[symbol])
                    posObj.position = float(posFrozeDict[symbol]) + float(posTradeDict[symbol])
                    posObj.frozen = float(posFrozeDict[symbol])
                    posObj.positionProfit = 0
                    if posObj.position > 0:
                        self.gateway.onPosition(posObj)
            except Exception,ex:
                self.gateway.writeError("Error in onGetBalance , parse data error ex:%s" % (str(ex)) , "h3")
        else:
            self.gateway.writeError("Error in onGetBalance , the status is not ok! data:%s" % (data) , "h2")

    '''
    {u'status': u'ok', u'data': u'575944654'}
    {u'status': u'error', u'err-code': u'order-limitorder-price-min-error', u'data':
 None, u'err-msg': u'limit order price error, min: `1.0E-6`'}
    '''
    #----------------------------------------------------------------------
    def onSpotTrade(self,data, req, reqID):
        """买卖回调"""
        if data["status"] != "ok":
            msg = data.get("err-msg" , u"spot error! 下单出错 ")
            code = data.get("err-code" , "h4")
            self.gateway.writeError("Error in onSpotTrade, msg: %s" % (msg) , code)

            localID = self.reqLocalDict[reqID]
            order = self.workingOrderDict[localID]
            order.status = STATUS_REJECTED

            self.gateway.onOrder(order)
            
            del self.workingOrderDict[localID]
            del self.reqLocalDict[reqID]

            if localID in self.cacheSendLocalOrder:
                self.cacheSendLocalOrder.remove(localID)
                self.gateway.writeLog( "cacheSendLocalOrder remove rejected localID %s" % (localID))
        else:
            localID = self.reqLocalDict[reqID]
            systemID = str(data['data'])
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

            if localID in self.cacheSendLocalOrder:
                self.cacheSendLocalOrder.remove(localID)
                self.gateway.writeLog( "cacheSendLocalOrder remove localID %s" % (localID))

            self.gateway.writeLog( "onSpotTrade make connect systemID %s, localID %s" % (str(systemID) , str(localID)))

    '''
    将查询到的订单 匹配已经发出的订单，来修正错误匹配部分
    '''
    #----------------------------------------------------------------------
    def autoFixMatch(self, to_compare_order , t_localID):
        self.gateway.writeLog("self.cacheSendLocalOrder : %s , t_localID %s " % (str(self.cacheSendLocalOrder) , t_localID))
        for localID in self.cacheSendLocalOrder:
            from_order = self.workingOrderDict[localID]

            if from_order.direction == to_compare_order.direction and from_order.offset == to_compare_order.offset and abs( float(from_order.price) - float(to_compare_order.price)) < 0.01 *float(to_compare_order.price) and abs( float(from_order.totalVolume) - float(to_compare_order.totalVolume)) < 0.01*float(to_compare_order.totalVolume):
                self.gateway.writeLog("autoFixMatch compare order now! t_localID %s , localID %s" % (str(t_localID) , str(localID)))
                t_localID = localID
                break
        if t_localID in self.cacheSendLocalOrder:
            self.cacheSendLocalOrder.remove(t_localID)
            self.gateway.writeLog("autoFixMatch cacheSendLocalOrder del localID %s" % (t_localID))
        return t_localID

    '''
    {u'status': u'ok', u'data': {u'account-id': 932763, u'canceled-at': 0, u'finishe
d-at': 0, u'field-cash-amount': u'0.0', u'price': u'0.100000000000000000', u'cre
ated-at': 1514956247720L, u'state': u'submitted', u'id': 575944654, u'field-amou
nt': u'0.0', u'amount': u'0.100000000000000000', u'source': u'api', u'field-fees
': u'0.0', u'type': u'sell-limit', u'symbol': u'etcbtc'}}

    {u'status': u'error', u'err-code': u'base-record-invalid', u'data': None, u'err-
msg': u'record invalid'}
    '''
    #----------------------------------------------------------------------
    def onOrderInfo(self,data, req, reqID):
        if data["status"] != 'ok':
            msg = data.get("err-msg" , u"spot onOrderInfo! 订单查询出错 ")
            code = data.get("err-code" , "h5")
            self.gateway.writeError( "onOrderInfo data info %s" % (str(data)) + " " + msg , code)
        else:
            use_order = data["data"]
            systemID = str(use_order["id"])
            status = use_order["state"]
            tradedVolume = float(use_order["field-amount"])
            volume = float(use_order["amount"])
            price = float(use_order["price"])
            side = use_order["type"]
            use_dt , use_date, now_time = self.generateDateTime(use_order["created-at"])

            local_system_dict_keys = self.systemLocalDict.keys()
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

                        self.tradedVolumeDict[localID] = tradedVolume

                    if status == "filled":
                        # 说明这个单子成交完毕了！
                        order.status = STATUS_ALLTRADED
                        self.gateway.onOrder(order)

                        del self.tradedVolumeDict[localID]
                        del self.systemLocalDict[systemID]
                        del self.workingOrderDict[localID]

                        self.cancelSystemOrderFilter.add(systemID)  # 排除已经cancel消失得单子

                    elif status in ["canceled","partial-canceled"]:
                        order.status = STATUS_CANCELLED
                        cancel_use_dt , cancel_use_date, cancel_now_time = self.generateDateTime(use_order["canceled-at"])
                        # order.cancelTime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                        order.cancelTime = cancel_use_dt.strftime("%Y-%m-%d %H:%M:%S")
                        self.gateway.onOrder(order)

                        del self.tradedVolumeDict[localID]
                        del self.systemLocalDict[systemID]
                        del self.workingOrderDict[localID]

                        self.cancelSystemOrderFilter.add(systemID)  # 排除已经cancel消失得单子

                    elif status == "partial-filled":
                        order.status = STATUS_PARTTRADED
                        self.gateway.onOrder(order)

                    elif status == "submitted":
                        order.status = STATUS_NOTTRADED
                        self.gateway.onOrder(order)
                    else:
                        self.gateway.writeError(" Exchange %s , new status %s , data %s" % (EXCHANGE_HUOBI , str(status) , str(data)), "h13")
            else:
                # 说明是以前发的单子
                if systemID not in self.cancelSystemOrderFilter:            # 排除已经cancel消失得单子
                
                    symbol_pair = systemSymbolToVnSymbol(use_order["symbol"])
                    if status not in ["filled","canceled","partial-canceled"]:
                        self.localID += 1
                        localID = str(self.localID)
                        order = VtOrderData()
                        order.gatewayName = self.gatewayName
                        order.symbol = symbol_pair + "." + self.gatewayName
                        order.exchange = EXCHANGE_HUOBI
                        order.vtSymbol = order.symbol
                        order.orderID = localID
                        order.vtOrderID = '.'.join([order.orderID, order.gatewayName])
                        order.direction = DIRECTION_LONG
                        order.offset = OFFSET_OPEN
                        if side == "sell-limit":
                            order.direction = DIRECTION_SHORT
                            order.offset = OFFSET_CLOSE
                        
                        order.price = price
                        order.totalVolume = volume
                        order.tradedVolume = tradedVolume

                        order.orderTime = now_time

                        if status == "partial-filled":
                            order.status = STATUS_PARTTRADED
                        elif status == "submitted":
                            order.status = STATUS_NOTTRADED
                        else:
                            self.gateway.writeError(" Exchange %s , new status %s , data %s" % (EXCHANGE_HUOBI , str(status) , str(data)), "h13")

                        localID = self.autoFixMatch( order , localID)
                        order.orderID = localID
                        order.vtOrderID = '.'.join([order.orderID, order.gatewayName])
                        self.gateway.writeLog(" onOrderInfo occure new order, localID %s, sysmtemID %s , order.vtSymbol %s , order.price %s" % (str(localID),str(systemID),str(order.vtSymbol),str(order.price)))

                        self.workingOrderDict[localID] = order
                        self.systemLocalDict[systemID] = localID
                        self.localSystemDict[localID] = systemID
                        self.tradedVolumeDict[localID] = tradedVolume
                        
                        self.gateway.onOrder(order)

    '''
    {u'status': u'ok', u'data': [{u'account-id': 932763, u'canceled-at': 0, u'finish
ed-at': 0, u'field-cash-amount': u'0.0', u'price': u'0.100000000000000000', u'cr
eated-at': 1514956247720L, u'state': u'submitted', u'id': 575944654, u'field-amo
unt': u'0.0', u'amount': u'0.100000000000000000', u'source': u'api', u'field-fee
s': u'0.0', u'type': u'sell-limit', u'symbol': u'etcbtc'}]}

{u'status': u'ok', u'data': [{u'account-id': 104997, u'canceled-at': 15227236227
72L, u'finished-at': 1522723623037L, u'field-cash-amount': u'0.0', u'price': u'0
.000118200000000000', u'created-at': 1522723574367L, u'state': u'canceled', u'id
': 2989125417L, u'field-amount': u'0.0', u'amount': u'4500.000000000000000000',
u'source': u'api', u'field-fees': u'0.0', u'type': u'sell-limit', u'symbol': u'z
ileth'}, {u'account-id': 104997, u'canceled-at': 1522723175114L, u'finished-at':
 1522723175455L, u'field-cash-amount': u'0.0', u'price': u'0.000118090000000000'
, u'created-at': 1522723073761L, u'state': u'canceled', u'id': 2988965031L, u'fi
eld-amount': u'0.0', u'amount': u'427.000000000000000000', u'source': u'api', u'
field-fees': u'0.0', u'type': u'sell-limit', u'symbol': u'zileth'}, {u'account-i
d': 104997, u'canceled-at': 1522722856924L, u'finished-at': 1522722857166L, u'fi
eld-cash-amount': u'0.0', u'price': u'0.000118090000000000', u'created-at': 1522
722601219L, u'state': u'canceled', u'id': 2988810840L, u'field-amount': u'0.0',
u'amount': u'369.000000000000000000', u'source': u'api', u'field-fees': u'0.0',
u'type': u'sell-limit', u'symbol': u'zileth'}, {u'account-id': 104997, u'cancele
d-at': 1522722513294L, u'finished-at': 1522722513473L, u'field-cash-amount': u'0
.0', u'price': u'3133.809999990000000000', u'created-at': 1522722453898L, u'stat
e': u'canceled', u'id': 2988762659L, u'field-amount': u'0.0', u'amount': u'4500.
000000000000000000', u'source': u'api', u'field-fees': u'0.0', u'type': u'sell-l
imit', u'symbol': u'zileth'}, {u'account-id': 104997, u'canceled-at': 1522721064
737L, u'finished-at': 1522721065015L, u'field-cash-amount': u'0.0', u'price': u'
0.000117510000000000', u'created-at': 1522720798232L, u'state': u'canceled', u'i
d': 2988196387L, u'field-amount': u'0.0', u'amount': u'4500.000000000000000000',
 u'source': u'api', u'field-fees': u'0.0', u'type': u'sell-limit', u'symbol': u'
zileth'}, {u'account-id': 104997, u'canceled-at': 1522720636221L, u'finished-at'
: 1522720636452L, u'field-cash-amount': u'0.0', u'price': u'738.4699999900000000
00', u'created-at': 1522720444067L, u'state': u'canceled', u'id': 2988071127L, u
'field-amount': u'0.0', u'amount': u'788.000000000000000000', u'source': u'api',
 u'field-fees': u'0.0', u'type': u'sell-limit', u'symbol': u'zileth'}, {u'accoun
t-id': 104997, u'canceled-at': 1522720365246L, u'finished-at': 1522720365411L, u
'field-cash-amount': u'0.0', u'price': u'10687.439999990000000000', u'created-at
': 1522720244491L, u'state': u'canceled', u'id': 2988002047L, u'field-amount': u
'0.0', u'amount': u'886.000000000000000000', u'source': u'api', u'field-fees': u
'0.0', u'type': u'sell-limit', u'symbol': u'zileth'}, {u'account-id': 104997, u'
canceled-at': 1522661450408L, u'finished-at': 1522661450635L, u'field-cash-amoun
t': u'0.0', u'price': u'10606.743367830000000000', u'created-at': 1522661353825L
, u'state': u'canceled', u'id': 2966490068L, u'field-amount': u'0.0', u'amount':
 u'292.000000000000000000', u'source': u'api', u'field-fees': u'0.0', u'type': u
'sell-limit', u'symbol': u'zileth'}, {u'account-id': 104997, u'canceled-at': 152
2661121325L, u'finished-at': 1522661121565L, u'field-cash-amount': u'0.0', u'pri
ce': u'26999.999999990000000000', u'created-at': 1522661005068L, u'state': u'can
celed', u'id': 2966364831L, u'field-amount': u'0.0', u'amount': u'490.0000000000
00000000', u'source': u'api', u'field-fees': u'0.0', u'type': u'sell-limit', u's
ymbol': u'zileth'}, {u'account-id': 104997, u'canceled-at': 1522658175111L, u'fi
nished-at': 1522658175422L, u'field-cash-amount': u'0.0', u'price': u'146.629999
990000000000', u'created-at': 1522658123930L, u'state': u'canceled', u'id': 2965
308392L, u'field-amount': u'0.0', u'amount': u'373.000000000000000000', u'source
': u'api', u'field-fees': u'0.0', u'type': u'sell-limit', u'symbol': u'zileth'},
 {u'account-id': 104997, u'canceled-at': 1522657895934L, u'finished-at': 1522657
896250L, u'field-cash-amount': u'0.0', u'price': u'0.059999990000000000', u'crea
ted-at': 1522657230867L, u'state': u'canceled', u'id': 2964978948L, u'field-amou
nt': u'0.0', u'amount': u'670.000000000000000000', u'source': u'api', u'field-fe
es': u'0.0', u'type': u'sell-limit', u'symbol': u'zileth'}]}

pre-submitted 准备提交, submitted 已提交, partial-filled 部分成交, partial-canceled 部分成交撤销, filled 完全成交, canceled 已撤销
    '''
    #----------------------------------------------------------------------
    def onOrderList(self, data, req, reqID):
        if data["status"] != 'ok':
            msg = data.get("err-msg" , u"spot onOrderList! 订单查询出错 ")
            code = data.get("err-code" , "h5")
            self.gateway.writeError( "onOrderList data info %s" % (str(data)) + " " + msg , code)
        else:
            # print data 
            try:
                orders = data["data"]
                stile_live_order_system_id = [ str(x["id"]) for x in orders]
                local_system_dict_keys = self.systemLocalDict.keys()

                for use_order in orders:
                    systemID = str(use_order["id"])
                    status = use_order["state"]
                    tradedVolume = float(use_order["field-amount"])
                    volume = float(use_order["amount"])
                    price = float(use_order["price"])
                    side = use_order["type"]
                    use_dt , use_date, now_time = self.generateDateTime(use_order["created-at"])

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
                                
                                self.tradedVolumeDict[localID] = tradedVolume

                            if status == "filled":
                                # 说明这个单子成交完毕了！
                                order.status = STATUS_ALLTRADED
                                self.gateway.onOrder(order)

                                del self.tradedVolumeDict[localID]
                                del self.systemLocalDict[systemID]
                                del self.workingOrderDict[localID]

                                self.cancelSystemOrderFilter.add(systemID)  # 排除已经cancel消失得单子

                            elif status in ["canceled","partial-canceled"]:
                                order.status = STATUS_CANCELLED
                                cancel_use_dt , cancel_use_date, cancel_now_time = self.generateDateTime(use_order["canceled-at"])
                                # order.cancelTime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                                order.cancelTime = cancel_use_date + " " + cancel_now_time
                                self.gateway.onOrder(order)

                                del self.tradedVolumeDict[localID]
                                del self.systemLocalDict[systemID]
                                del self.workingOrderDict[localID]

                                self.cancelSystemOrderFilter.add(systemID)  # 排除已经cancel消失得单子

                            elif status == "partial-filled":
                                order.status = STATUS_PARTTRADED
                                self.gateway.onOrder(order)

                            elif status == "submitted":
                                order.status = STATUS_NOTTRADED
                                self.gateway.onOrder(order)
                    else:
                        # 说明是以前发的单子
                        if systemID not in self.cancelSystemOrderFilter:        # 排除已经cancel消失得单子
                            
                            symbol_pair = systemSymbolToVnSymbol(use_order["symbol"])

                            if status not in ["filled","canceled","partial-canceled"]:
                                self.localID += 1
                                localID = str(self.localID)

                                order = VtOrderData()
                                order.gatewayName = self.gatewayName
                                order.symbol = symbol_pair + "." + self.gatewayName
                                order.exchange = EXCHANGE_HUOBI
                                order.vtSymbol = order.symbol
                                order.orderID = localID
                                order.vtOrderID = '.'.join([order.orderID, order.gatewayName])
                                order.direction = DIRECTION_LONG
                                order.offset = OFFSET_OPEN
                                if side == "sell-limit":
                                    order.direction = DIRECTION_SHORT
                                    order.offset = OFFSET_CLOSE
                                
                                order.price = price
                                order.totalVolume = volume
                                order.tradedVolume = tradedVolume

                                order.orderTime = now_time

                                if status == "partial-filled":
                                    order.status = STATUS_PARTTRADED
                                elif status == "submitted":
                                    order.status = STATUS_NOTTRADED
                                else:
                                    self.gateway.writeError(" Exchange %s , new status %s , data %s" % (EXCHANGE_HUOBI , str(status) , str(data)), "h13")

                                localID = self.autoFixMatch( order , localID)
                                order.orderID = localID
                                order.vtOrderID = '.'.join([order.orderID, order.gatewayName])
                                
                                self.gateway.writeLog(" onOrderList occure new order, localID %s, sysmtemID %s , order.vtSymbol %s , order.price %s" % (str(localID),str(systemID),str(order.vtSymbol),str(order.price)))

                                self.workingOrderDict[localID] = order
                                self.systemLocalDict[systemID] = localID
                                self.localSystemDict[localID] = systemID
                                self.tradedVolumeDict[localID] = tradedVolume
                                
                                self.gateway.onOrder(order)
            except Exception,ex:
                self.gateway.writeError("onOrderList parse error ,data %s , ex %s" % (str(data) , str(ex)) , "h15")

    '''
    {u'status': u'ok', u'data': u'575944654'}
    {u'status': u'error', u'err-code': u'order-orderstate-error', u'data': None, u'e
rr-msg': u'the order state is error'}
    '''
    #----------------------------------------------------------------------
    def onCancelOrder(self,data, req, reqID):
        if data['status'] != "ok":
            msg = data.get("err-msg" , u"spot onCancelOrder! 撤销出错 ")
            code = data.get("err-code" , "h7")
            self.gateway.writeError( "onCancelOrder data info %s" % (str(data)) + " " + msg , code)
        else:
            try:
                systemID = str(data["data"])

                # self.cancelSystemOrderFilter.add(systemID)

                localID = self.systemLocalDict[systemID]

                order = self.workingOrderDict[localID]
                # order.status = STATUS_CANCELLED
                # order.cancelTime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

                self.gateway.writeLog( "onCancelOrder 1 : order.totalVolume %s  order.tradedVolume %s order.price %s" % ( str(order.totalVolume) , str(order.tradedVolume) , str(order.price)) )

                # del self.workingOrderDict[localID]
                # del self.systemLocalDict[systemID]
                # del self.localSystemDict[localID]
                # self.gateway.onOrder(order)
            except Exception,ex:
                self.gateway.writeError("onCancelOrder parse error ,data %s , ex %s" % (str(data) , str(ex)) , "h15")

    #----------------------------------------------------------------------
    def cancel(self, req):
        localID = req.orderID
        if localID in self.localSystemDict:
            systemID = self.localSystemDict[localID]
            self.cancel_order( systemID )
        else:
            self.cancelDict[localID] = req

    #----------------------------------------------------------------------
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(float(s)/1e3)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return dt , date, time


'''
HuobiSocketDataApi  
'''
class HuobiSocketDataApi(Huobi_DataApiSocket):
    """基于websocket的TICK数据获得对象"""
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        super(HuobiSocketDataApi, self).__init__()

        self.gateway = gateway
        self.gatewayName = gateway.gatewayName

        self.tickDict = {}      # key:symbol, value:tick

        self.period_flag = False

        self.registerSymbols = set([])

    #----------------------------------------------------------------------
    def subscribeSymbol(self, subscribeReq):
        use_symbol = (subscribeReq.symbol.split('.'))[0]
        if use_symbol not in self.registerSymbols:
            self.registerSymbols.add(use_symbol)

            self.sendTickerRequest(use_symbol)
            self.sendOrderbookRequest(use_symbol)


    #----------------------------------------------------------------------
    def connect(self ):
        super(HuobiSocketDataApi, self).connect( wss_huobi_hosts)

    '''
    {u'tick': {u'count': 61, u'vol': 52095.986831, u'high': 844.4, u'amount': 61.752
2, u'low': 842.64, u'close': 843.97, u'open': 843.98, u'id': 1514882100}, u'ch':
 u'market.ethusdt.kline.1min', u'ts': 1514882159892L}
    '''
    #----------------------------------------------------------------------
    def onTicker(self , data):
        tick_info = data["tick"]
        ch = data["ch"]
        symbol_pair = systemSymbolToVnSymbol((ch.split('.'))[1])

        if symbol_pair not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.exchange = EXCHANGE_HUOBI
            tick.symbol = '.'.join([symbol_pair, tick.exchange])
            tick.vtSymbol = '.'.join([symbol_pair, tick.exchange])
            self.tickDict[symbol_pair] = tick
        else:
            tick = self.tickDict[symbol_pair]

        tick.highPrice = float(tick_info["high"])
        tick.lowPrice = float(tick_info["low"])
        tick.lastPrice = float(tick_info["close"])
        tick.volume = float(tick_info["vol"])

        tick.datetime , tick.date, tick.time = self.generateDateTime(data["ts"])

        #self.gateway.onTick(tick)


    '''
    {u'tick': {u'version': 969271128, u'bids': [[844.5, 4.8006], [843.7, 0.8419], [8
43.6, 7.7966], [843.0, 1.0], [842.8, 5.4264], [842.5, 2.0785], [842.4, 0.0034],
[842.0, 11.5309], [841.2, 1.93], [841.0, 5.0], [840.3, 10.292], [840.0, 16.1437]
, [839.0, 12.4901], [838.0, 0.9808], [837.0, 13.3458], [836.8, 0.0016], [836.1,
11.1602], [835.6, 5.1912], [835.3, 3.85], [835.0, 5.7147]], u'ts': 1514882390094
L, u'asks': [[844.6, 316.5434], [844.7, 9.62156737714624], [844.9, 57.9369], [84
5.0, 1.3333], [845.4, 3.85], [845.5, 0.1185], [845.6, 0.0237], [846.0, 3.1249],
[847.1, 99.4392], [847.2, 1.0036], [848.0, 8.492], [848.2, 7.6455], [849.0, 2.0]
, [850.0, 37.1164], [850.2, 0.0834], [850.3, 5.0], [850.5, 6.0], [851.0, 5.1], [
851.3, 1.5], [852.0, 6.0]]}, u'ch': u'market.ethusdt.depth.step5', u'ts': 151488
2390832L}
    '''
    #----------------------------------------------------------------------
    def onDepth(self , data):
        tick_info = data["tick"]
        ch = data["ch"]
        symbol_pair = systemSymbolToVnSymbol((ch.split('.'))[1])

        if symbol_pair not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.exchange = EXCHANGE_HUOBI
            tick.symbol = '.'.join([symbol_pair, tick.exchange])
            tick.vtSymbol = '.'.join([symbol_pair, tick.exchange])
            self.tickDict[symbol_pair] = tick
        else:
            tick = self.tickDict[symbol_pair]

        bids = tick_info["bids"]
        asks = tick_info["asks"]

        bids = [ (float(x[0]) , float(x[1])) for x in bids ]
        asks = [ (float(x[0]) , float(x[1])) for x in asks ]


        try:
            tick.bidPrice1, tick.bidVolume1 = bids[0]
            tick.bidPrice2, tick.bidVolume2 = bids[1]
            tick.bidPrice3, tick.bidVolume3 = bids[2]
            tick.bidPrice4, tick.bidVolume4 = bids[3]
            tick.bidPrice5, tick.bidVolume5 = bids[4]
        except Exception,ex:
            pass

        try:
            tick.askPrice1, tick.askVolume1 = asks[0]
            tick.askPrice2, tick.askVolume2 = asks[1]
            tick.askPrice3, tick.askVolume3 = asks[2]
            tick.askPrice4, tick.askVolume4 = asks[3]
            tick.askPrice5, tick.askVolume5 = asks[4]
        except Exception,ex:
            pass

        tick.datetime , tick.date, tick.time = self.generateDateTime(data["ts"])

        self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(float(s)/1e3)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return dt , date, time

'''
HuobiDataApi
'''
class HuobiDataApi(Huobi_DataApi):
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(HuobiDataApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName

        self.tickDict = {}      # key:symbol, value:tick

        self.registerSymbols = set([])

    #----------------------------------------------------------------------
    def subscribeSymbol(self, subscribeReq):
        use_symbol = (subscribeReq.symbol.split('.'))[0]
        if use_symbol not in self.registerSymbols:
            self.registerSymbols.add(use_symbol)
            s.subscribeTick(use_symbol)
            s.subscribeOrderbooks(use_symbol)
            # s.subscribeTrades("eth_usdt")

    #----------------------------------------------------------------------
    def connect(self, interval , market , debug = False):
        self.init(interval , debug)
        # 订阅行情并推送合约信息


    '''
    {u'status': u'ok', u'ch': u'market.ethusdt.kline.1min', u'data': [{u'count': 23,
     u'vol': 30112.19242, u'high': 881.5, u'amount': 34.20465022121384, u'low': 880.
    0, u'close': 881.47, u'open': 880.52, u'id': 1514942280}], u'ts': 1514942316429L
    }
    '''
    #----------------------------------------------------------------------
    def onTick(self, data):
        """实时成交推送"""
        ch = data["ch"]
        symbol_pair = VnSymbolToSystemSymbol((ch.split('.'))[1])
        data_info = data["data"]

        if symbol_pair not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.exchange = EXCHANGE_HUOBI
            tick.symbol = '.'.join([symbol_pair, tick.exchange])
            tick.vtSymbol = '.'.join([symbol_pair, tick.exchange])
            self.tickDict[symbol_pair] = tick
        else:
            tick = self.tickDict[symbol_pair]

        tick.highPrice = float(data_info["high"])
        tick.lowPrice = float(data_info["low"])
        tick.lastPrice = float(data_info["close"])
        tick.volume = float(data_info["vol"])

        tick.datetime , tick.date, tick.time = self.generateDateTime(data["ts"])

        self.gateway.onTick(tick)

    '''
    {u'status': u'ok', u'tick': {u'data': [{u'price': 879.22, u'amount': 1.8757, u'd
irection': u'buy', u'id': 17592265123820L, u'ts': 1514942408570L}], u'id': 98358
2923, u'ts': 1514942408570L}, u'ch': u'market.ethusdt.trade.detail', u'ts': 1514
942411842L}
    '''
    #----------------------------------------------------------------------
    def onTrades(self, data):
        """实时成交推送"""
        pass

    '''
    {u'status': u'ok', u'tick': {u'version': 983568451, u'bids': [[878.89, 3.412], [
878.87, 0.2536], [878.09, 2.7884], [878.0, 11.9809], [877.95, 0.351], [877.58, 8
.1561], [877.0, 29.273], [876.54, 13.0531], [876.37, 0.3105], [874.89, 2.94], [8
74.58, 0.4564], [873.98, 6.2526], [873.81, 1.0], [873.0, 0.4517], [872.59, 18.99
2], [871.0, 0.2], [870.3, 1.83], [870.29, 0.6925], [870.25, 5.3269], [870.01, 17
.3582], [870.0, 3.9505], [869.12, 62.526], [868.01, 1.0537], [868.0, 1.5683], [8
65.18, 0.1], [865.0, 13.441], [862.0, 0.3646], [861.31, 0.91], [861.3, 0.6476],
[861.0, 0.6414], [860.01, 1.77], [860.0, 327.9795], [859.23, 0.9963], [858.0, 0.
8027], [857.0, 97.268], [856.2, 2.6], [856.0, 1.702], [855.0, 137.1641], [854.43
, 1.002], [854.04, 0.01], [853.0, 0.02], [852.0, 23.3469], [851.98, 0.1023], [85
1.8, 0.0496], [851.79, 11.7182], [851.2, 1.3657], [851.0, 1.6129], [850.0, 650.9
722], [849.32, 62.526], [848.0, 20.3766], [847.0, 0.1], [845.38, 1.2061], [845.2
8, 1.2208], [845.0, 189.0879], [844.0, 0.1441], [843.6, 2.0], [843.0, 0.9724], [
842.0, 2.2], [840.11, 0.05], [840.01, 20.07], [840.0, 198.4922], [838.45, 0.05],
 [838.0, 2.7405], [836.0, 2.6215], [835.68, 0.1398], [835.56, 10.5], [835.48, 41
.3185], [835.06, 0.2969], [835.0, 18.8555], [834.98, 1.0361], [833.0, 0.1954], [
832.22, 0.0788], [832.0, 20.3165], [831.0, 21.9221], [830.85, 0.1], [830.0, 43.5
515], [828.0, 3.2548], [827.15, 77.3729], [827.0, 0.3901], [825.55, 1.2127], [82
5.0, 8.8858], [824.6, 0.2275], [823.45, 759.4628], [823.36, 0.053], [823.0, 37.5
775], [822.0, 1.0], [821.8, 0.7839], [821.5, 0.68], [821.0, 2.0], [820.0, 46.643
8], [819.9, 45.4703], [819.3, 0.1121], [819.1, 241.1267], [818.0, 2.5549], [817.
71, 0.6569], [816.0, 0.6518], [815.0, 10.2581], [812.0, 6.9248], [811.3, 1.0], [
811.0, 0.2], [810.99, 0.225], [810.32, 0.1], [810.01, 20.04], [810.0, 18.3054],
[809.39, 2.4292], [809.0, 15.01], [808.0, 2.4284], [807.85, 1.1062], [805.0, 2.0
6], [804.0, 30.7033], [803.84, 0.1], [803.01, 4.8946], [803.0, 4.052], [802.4, 1
5.0], [802.0, 26.5919], [801.1, 2.9387], [801.01, 5.9288], [801.0, 22.4892], [80
0.45, 1.8], [800.43, 0.0181], [800.13, 5.4559], [800.02, 0.6039], [800.01, 15.05
], [800.0, 110.3042], [799.0, 3.4591], [798.8, 20.0052], [798.0, 2.0], [797.0, 0
.5922], [795.0, 0.2177], [793.0, 0.5373], [791.18, 3.3072], [791.0, 1.0833], [79
0.8, 44.1261], [790.0, 9.4065], [789.9, 46.2871], [789.0, 1.3599], [788.0, 12.79
76], [786.58, 6.777], [785.6, 50.0], [785.0, 17.3532], [782.06, 2.9717], [782.0,
 1.4065], [781.0, 3.6762], [780.28, 0.2204], [780.05, 0.015], [780.01, 5.0], [78
0.0, 49.3788], [778.0, 2.0142], [777.77, 1.0], [777.0, 13.6799]], u'ts': 1514942
352037L, u'asks': [[881.46, 3.44], [881.47, 0.8], [881.48, 2.8992], [881.5, 4.37
494977878616], [881.96, 8.03], [881.98, 2.7635], [882.0, 8.502139432925171], [88
2.4, 2.2701], [882.51, 36.412115186049526], [882.65, 5.0], [883.48, 5.7395], [88
4.11, 0.97], [884.92, 17.21587515193464], [885.0, 4.4126], [885.77, 0.269], [885
.89, 5.8173], [886.0, 3.8386], [886.33, 3.6096], [886.52, 1.0363], [886.68, 0.25
02], [886.9, 3.0], [887.32, 6.2526], [887.33, 0.04], [887.42, 2.6565], [887.95,
18.992], [888.0, 66.0807], [888.28, 0.568], [888.62, 0.3631], [888.73, 0.0049],
[888.8, 0.1151], [888.87, 0.86], [888.88, 39.258], [889.0, 26.6207], [889.03, 1.
3684], [889.2, 0.3388], [889.24, 0.0093], [889.54, 0.1], [889.62, 0.8044], [889.
82, 2.2], [889.97, 10.0], [889.99, 0.2903], [890.0, 87.5491], [890.2, 17.0], [89
0.91, 37.9729], [892.0, 0.02], [892.27, 0.1277], [893.0, 2.257], [894.6, 0.0381]
, [894.9, 3.0], [895.0, 228.9291], [895.07, 0.1486], [895.65, 0.8044], [896.0, 6
.6751], [896.1, 0.6937], [896.31, 0.0225], [896.66, 0.1148], [896.8, 0.998], [89
6.93, 0.03], [897.0, 3.8446], [897.88, 1.0], [898.0, 12.2008], [898.02, 1.0], [8
98.08, 0.5815], [898.38, 2.0], [898.66, 6.152], [898.7, 0.1], [898.81, 0.0227],
[898.97, 1.7023], [898.99, 0.1775], [899.0, 33.3794], [899.03, 0.5], [899.9, 0.8
074], [899.97, 10.0], [899.98, 1.1195], [899.99, 4.5449], [900.0, 1338.4839], [9
00.18, 0.5], [900.79, 0.1], [901.0, 1.3123], [904.99, 0.86], [905.0, 1374.7797],
 [907.0, 57.7], [908.0, 2.9523], [909.0, 1.0], [910.0, 750.4343], [910.02, 3.197
5], [911.0, 1.0], [912.0, 29.7488], [915.0, 1056.5504], [916.0, 5.5423], [916.3,
 4.4], [917.0, 9.6975], [918.0, 31.3056], [918.88, 12.7076], [919.0, 10.082], [9
19.91, 0.4], [920.0, 87.0405], [920.75, 1.7977], [921.0, 2.5764], [923.0, 65.105
4], [923.11, 1.0], [923.25, 0.309], [924.0, 4.0], [925.0, 4.972], [925.88, 5.469
1], [928.0, 1.6408], [929.0, 3.4919], [929.5, 100.0], [929.98, 0.0215], [930.0,
17.3347], [930.65, 0.0026], [931.0, 25.2058], [931.5, 0.2811], [932.0, 1.5], [93
3.0, 1.935], [933.68, 0.63], [935.0, 58.4828], [935.53, 0.2012], [936.0, 0.3], [
938.0, 62.5545], [938.99, 0.25], [939.0, 1.72], [940.0, 6.2628], [942.0, 3.0072]
, [943.0, 0.0415], [945.0, 0.0551], [945.9, 0.1736], [946.63, 1.0], [947.5, 0.10
61], [948.0, 3.0], [948.72, 0.1052], [949.0, 1.0812], [949.49, 0.5412], [949.5,
100.0], [949.9, 0.0655], [949.96, 2.8117], [949.99, 3.0], [950.0, 213.381], [950
.36, 0.4017], [950.83, 2.19], [951.0, 5.0], [954.1, 4.2336], [955.0, 7.5434], [9
55.5, 2.6819], [956.0, 3.414], [956.38, 0.6392], [956.88, 0.5], [957.99, 0.1691]
, [958.0, 3.1071], [958.56, 1.415]]}, u'ch': u'market.ethusdt.depth.step0', u'ts
': 1514942352246L}
'''
    #----------------------------------------------------------------------
    def onDepth(self, data):
        """实时成交推送"""
        tick_info = data["tick"]
        ch = data["ch"]
        symbol_pair = VnSymbolToSystemSymbol((ch.split('.'))[1])

        if symbol_pair not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.exchange = EXCHANGE_HUOBI
            tick.symbol = '.'.join([symbol_pair, tick.exchange])
            tick.vtSymbol = '.'.join([symbol_pair, tick.exchange])
            self.tickDict[symbol_pair] = tick
        else:
            tick = self.tickDict[symbol_pair]

        bids = tick_info["bids"]
        asks = tick_info["asks"]

        bids = [ (float(x[0]) , float(x[1])) for x in bids ]
        asks = [ (float(x[0]) , float(x[1])) for x in asks ]

        try:
            tick.bidPrice1, tick.bidVolume1 = bids[0]
            tick.bidPrice2, tick.bidVolume2 = bids[1]
            tick.bidPrice3, tick.bidVolume3 = bids[2]
            tick.bidPrice4, tick.bidVolume4 = bids[3]
            tick.bidPrice5, tick.bidVolume5 = bids[4]
        except Exception,ex:
            pass

        try:
            tick.askPrice1, tick.askVolume1 = asks[0]
            tick.askPrice2, tick.askVolume2 = asks[1]
            tick.askPrice3, tick.askVolume3 = asks[2]
            tick.askPrice4, tick.askVolume4 = asks[3]
            tick.askPrice5, tick.askVolume5 = asks[4]
        except Exception,ex:
            pass

        tick.datetime , tick.date, tick.time = self.generateDateTime(data["ts"])

        self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(float(s)/1e3)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return dt , date, time
