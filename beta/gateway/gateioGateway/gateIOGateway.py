# encoding: UTF-8

import os
import json
from datetime import datetime
from copy import copy
from threading import Condition
from Queue import Queue
from threading import Thread

import json
from vnpy.api.gate import Gate_DataApi , Gate_TradeApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath
from vnpy.Function import systemSymbolToVnSymbol , VnSymbolToSystemSymbol

from datetime import datetime , timedelta

'''
GateIO 接口
'''
class GateIOGateway(VtGateway):
    """GateIO 接口"""
    #----------------------------------------------------------------------
    def __init__(self, eventEngine , gatewayName=EXCHANGE_GATE):
        """Constructor"""
        super(GateIOGateway , self).__init__(eventEngine, gatewayName)
        
        self.tradeApi = gateIOTradeApi(self)
        self.dataApi = gateIODataApi(self)
        
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

        self.tradeApi.get_market_info()
        self.writeLog(u'获得%s币种合约请求已发送' % (EXCHANGE_GATE))

        self.dataApi.connect(interval )
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
        self.writeLog( "GateIOGateway subscribeReq %s" % (subscribeReq.symbol))
        self.tradeApi.subscribeSymbol(subscribeReq)
        self.dataApi.subscribeSymbol(subscribeReq)

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.tradeApi.sendOrder(orderReq)

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.writeLog("GateIOGateway cancelOrder %s" % (str(cancelOrderReq.__dict__)))
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
            self.qryFunctionList = [self.tradeApi.get_balance , self.tradeApi.listAllOrders]
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
gateIOTradeApi
'''
class gateIOTradeApi(Gate_TradeApi):
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(gateIOTradeApi , self).__init__()

        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        self.accountID = "GateIO"
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

        self.cancelSystemOrderFilter = set([])       # 已经撤销的系统委托，可能会因为 gateio 反应特别慢，而失败，所以加个东西过滤 ,以免造成重复订单

        self.cacheSendLocalOrder = set([])           # 缓存已经发的订单local ,用于匹配订单

        self.reqIDToSystemID = {}                    # 建立reqID 与 systemID的映射

        self.systemID_not_found_dict = {}            # 建立systemID 与 未找到订单的印射

        self.cache_trade_data = []                   # 缓存trade事件

        # for test
        # order = VtOrderData()
        # order.gatewayName = self.gatewayName
        # order.symbol = "ae_tnb"
        # order.exchange = EXCHANGE_GATE
        # order.vtSymbol = "ae_tnb." + EXCHANGE_GATE 

        # order.orderID = "0"
        # order.vtOrderID = '.'.join([order.orderID, order.gatewayName])

        # order.direction = DIRECTION_LONG
        # order.offset = OFFSET_OPEN

        # order.price = 0.00011477
        # order.tradedVolume = 0
        # order.totalVolume = 12.0
        # order.orderTime = datetime.now().strftime('%H:%M:%S')
        # order.status = STATUS_UNKNOWN

        # self.workingOrderDict["0"] = order

        # self.cacheSendLocalOrder.add("0")

    #---------------------------------------------------------------------
    def subscribeSymbol(self, subscribeReq):
        use_symbol = (subscribeReq.symbol.split('.'))[0]
        # self.gateway.writeLog( "subscribeSymbol use_symbol %s" % (use_symbol))
        if use_symbol not in self.registerSymbols:
            self.registerSymbols.add(use_symbol)

    #---------------------------------------------------------------------
    def setAccountID(self, useAccountID):
        self.accountID = useAccountID

    #---------------------------------------------------------------------
    def listAllOrders(self):
        for systemID in self.systemLocalDict.keys():
            currencyPair = "None"
            try:
                localID = self.systemLocalDict[systemID]
                order = self.workingOrderDict[localID]
                currencyPair = (order.vtSymbol.split('.'))[0]
            except Exception ,ex:
                self.gateway.writeError( "parse list order error,systemID %s , ex %s" % (str(systemID), str(ex)) , "g16")
            reqID = self.getOrder(currencyPair , systemID)
            self.reqIDToSystemID[reqID] = str(systemID)

        self.listOpenOrders()

        # 检查  渣gate的成交日志， 以避免渣gate服务器的问题导致的订单消失
        for use_symbol in self.registerSymbols:
            self.listTradeHistory(use_symbol)
    '''
    发送系统委托
    '''
    def sendOrder(self, req):
        # 检查是否填入了价格，禁止市价委托
        if req.priceType != PRICETYPE_LIMITPRICE:
            self.gateway.writeError("Gate接口斤支持限价单" , "g1")
            return None

        symbol = req.vtSymbol
        if req.direction == DIRECTION_LONG:
            reqID = self.spotTrade( symbol = systemSymbolToVnSymbol(symbol) , price = req.price , amount = req.volume , _type = "buy" )
        else:
            reqID = self.spotTrade( symbol = systemSymbolToVnSymbol(symbol) , price = req.price , amount = req.volume , _type = "sell" )

        self.localID += 1
        localID = str(self.localID)
        self.reqLocalDict[reqID] = localID

        # 推送委托信息
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = req.vtSymbol
        order.exchange = EXCHANGE_GATE
        order.vtSymbol = req.vtSymbol

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

        self.cacheSendLocalOrder.add(localID)
        
        self.gateway.writeLog( "sendOrder cacheSendLocalOrder add localID %s" % (localID))
        # self.gateway.onOrder(order)

        # print "sendOrder:" , order.__dict__
        # print "sendOrder: req" , req.__dict__
        # 返回委托号
        return order.vtOrderID

    '''
     {
        "result": "true",
        "available": {
            "BTC": "1000",
            "ETH": "968.8",
            "ETC": "0",
            },
        "locked": {
            "ETH": "1"
            }
    }
    '''
    #----------------------------------------------------------------------
    def onBalances(self,data, req, reqID):
        result_status = data.get("result", None)
        if str(result_status) == "true":
            available = data.get("available",{})
            locked = data.get("locked",{})
            all_keys = list(set(available.keys() + locked.keys()))
            union_arr = [ asset for asset in available.keys() if asset in locked.keys()]
            for asset in all_keys:
                tmp_ava = available.get(asset,0)
                tmp_locked = locked.get(asset,0)
                asset = asset.lower()
                posObj = VtPositionData()
                posObj.gatewayName = self.gatewayName
                posObj.symbol = asset + "." + EXCHANGE_GATE
                posObj.exchange = EXCHANGE_GATE
                posObj.vtSymbol = posObj.symbol
                posObj.direction = DIRECTION_NET
                posObj.vtPositionName = '.'.join( [posObj.vtSymbol, posObj.direction])
                posObj.ydPosition = float(tmp_ava) + float(tmp_locked)
                posObj.position = float(tmp_ava) + float(tmp_locked)
                posObj.frozen = float(tmp_locked)
                posObj.positionProfit = 0

                if posObj.position > 0.0:
                    self.gateway.onPosition(posObj)
        else:
            self.gateway.writeError( u"onBalances not get! gate仓位没有得到 " , "g5")

    '''
     [
                "eth_btc","etc_btc","etc_eth","zec_btc","dash_btc","ltc_btc","bcc_btc","qtum_btc",
                "qtum_eth","xrp_btc","zrx_btc","zrx_eth","dnt_eth","dpy_eth","oax_eth","lrc_eth",
                "lrc_btc","pst_eth","tnt_eth","snt_eth","snt_btc","omg_eth","omg_btc","pay_eth",
                "pay_btc","bat_eth","cvc_eth","storj_eth","storj_btc","eos_eth","eos_btc"
        ]
            
    '''
    #----------------------------------------------------------------------
    def onAllSymbols(self,data, req, reqID):
        print data 

    '''
    {
        "result": "true",
        "pairs": [
                      {
                            "eth_btc": {
                                "decimal_places": 6,
                                "min_amount": 0.0001,
                                "fee": 0.2
                            }
                      },
                      {
                            "etc_btc": {
                                "decimal_places": 6,
                                "min_amount": 0.0001,
                                "fee": 0.2
                            }
                      }
            ]
    }
    '''
    #----------------------------------------------------------------------
    def onMarketInfo(self,data, req, reqID):
        result_status = data.get("result" , None)
        if result_status == "true":
            pairs = data.get("pairs", None)
            if pairs != None:
                for info in pairs:
                    for symbol in info.keys():
                        dic = info[symbol]
                        contract = VtContractData()
                        contract.gatewayName = self.gatewayName
                        contract.symbol = symbol
                        contract.exchange = EXCHANGE_GATE
                        contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
                        contract.name = u'现货'+contract.vtSymbol
                        contract.size = 0.1 ** int(dic["decimal_places"])
                        contract.min_amount =  float(dic["min_amount"])
                        contract.productClass = PRODUCT_SPOT

                        self.gateway.onContract(contract)
            else:
                self.gateway.writeError( u"market info pairs not get! gate市场数据没有得到 pairs", "g4")
        else:
            self.gateway.writeError( u"market info not get! gate市场数据没有得到", "g3")

    '''
    {"result":"true","message":"Success","code":0,"orderNumber":485615069}
    {"result":"false","message":"Your order size is too small. The minimum is 0.001 BTC","code":20}
    '''
    #----------------------------------------------------------------------
    def onSpotTrade(self,data, req, reqID):
        result_status = data.get("result" , None)
        if result_status != "true" and result_status != True:
            msg = data.get("message" , u"spot error! 下单出错 ")
            code = data.get("code" , "g6")
            self.gateway.writeError( "onSpotTrade data info %s" % (str(data)) + " " + msg , code)

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
            systemID = str(data['orderNumber'])
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
    {u'message': u'Error: invalid order id or order is already closed.', u'code': 16
, 'systemID': '489517160', u'result': u'false'}

    {"result":true,"code":0,"message":"Success"}
    add systemID
    '''
    #----------------------------------------------------------------------
    def onCancelOrder(self,data, req, reqID):
        result_status = data.get("result" , None)
        if result_status != "true" and result_status != True:
            msg = data.get("message" , u"spot onCancelOrder! 撤销出错 ")
            code = data.get("code" , "g7")
            self.gateway.writeError( "onCancelOrder data info %s" % (str(data)) + " " + msg , code)

            try:
                code = str(code)
                if 'cancelled' in msg and code in ["16" , "17"]:
                    # 说明 gate 已经撤销了这笔单子, 或者单子不存在
                    systemID = str(data["systemID"])
                    if systemID in self.systemLocalDict.keys():
                        localID = self.systemLocalDict[systemID]
                        order = self.workingOrderDict[localID]
                        order.status = STATUS_CANCELLED
                        order.cancelTime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                        self.gateway.writeLog( "onCancelOrder 5 : order.totalVolume %s  order.tradedVolume %s order.price %s" % ( str(order.totalVolume) , str(order.tradedVolume) , str(order.price)) )
                        
                        del self.workingOrderDict[localID]
                        del self.systemLocalDict[systemID]
                        del self.localSystemDict[localID]
                        self.gateway.onOrder(order)
            except Exception,ex:
                self.gateway.writeLog("Error in parse onCancelOrder rejected , ex:%s , data:%s" % (str(ex) , str(data)))
        else:
            try:
                systemID = str(data["systemID"])

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
                self.gateway.writeError("onCancelOrder parse error ,data %s , ex %s" % (str(data) , str(ex)) , "g15")

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
    {u'elapsed': u'1.107ms', u'message': u'Success', u'code': 0, u'result': u'true',
 u'order': {u'status': u'cancelled', u'feeValue': u'0.00000000', u'filledRate':
0, u'orderNumber': u'489517146', u'timestamp': u'1521682618', u'feeCurrency': u'
BTC', u'amount': u'6', u'filledAmount': 0, u'rate': 0.0002, u'fee': u'0.00000000
 BTC', u'currencyPair': u'bcd_btc', u'initialRate': 0.0002, u'type': u'buy', u'f
eePercentage': 0.2, u'initialAmount': u'6'}}
    {u'message': u'Error: invalid order id or order cancelled.', u'code': 17, u'resu
lt': u'false'}
    {u'elapsed': u'4.033ms', u'message': u'Success', u'code': 0, u'result': u'true',
     u'order': {u'status': u'open', u'feeValue': u'0.00000000', u'filledRate': 0, u'
    orderNumber': u'489533981', u'timestamp': u'1521683681', u'feeCurrency': u'BCD',
     u'amount': u'2', u'filledAmount': 0, u'rate': 0.0006, u'fee': u'0.00000000 BCD'
    , u'currencyPair': u'bcd_btc', u'initialRate': 0.0006, u'type': u'sell', u'feePe
    rcentage': 0.2, u'initialAmount': u'2'}}
    '''
    #----------------------------------------------------------------------
    def onOrderInfo(self,data, req, reqID):
        result_status = data.get("result" , None)
        if result_status != "true" and result_status != True:
            msg = data.get("message" , u"spot onOrderInfo! 订单查询出错 ")
            code = data.get("code" , "g8")
            self.gateway.writeError( "onOrderInfo data info %s" % (str(data)) + " " + msg , code)

            #####################  to debug
            if reqID in self.reqIDToSystemID.keys():
                systemID = self.reqIDToSystemID[reqID]
                del self.reqIDToSystemID[reqID]

                if systemID not in self.cancelSystemOrderFilter:
                    if systemID in self.systemLocalDict.keys():
                        localID = self.systemLocalDict[systemID]
                        order = self.workingOrderDict.get(localID, None)
                        if order != None:
                            if systemID not in self.systemID_not_found_dict.keys():
                                self.systemID_not_found_dict[systemID] = {"localID":localID , "order":order}
        else:
            if reqID in self.reqIDToSystemID.keys():
                del self.reqIDToSystemID[reqID]
            use_order = data["order"]
            systemID = str(use_order["orderNumber"])
            status = use_order["status"]
            tradedVolume = float(use_order["filledAmount"])
            volume = float(use_order["amount"])
            price = float(use_order["rate"])
            side = use_order["type"]

            use_dt , use_date, now_time = self.generateDateTime(use_order["timestamp"])

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

                        self.cache_trade_data.append(trade)

                    if status == "closed":
                        # 说明这个单子成交完毕了！
                        self.gateway.writeLog( "onOrderInfo closed data:%s" % str(data))

                        if order.tradedVolume < order.totalVolume:
                            order.status = STATUS_CANCELLED
                            self.gateway.onOrder(order)
                        else:
                            order.status = STATUS_ALLTRADED
                            self.gateway.onOrder(order)

                        del self.tradedVolumeDict[localID]
                        del self.systemLocalDict[systemID]
                        del self.workingOrderDict[localID]

                        self.cancelSystemOrderFilter.add(systemID)  # 排除已经cancel消失得单子

                    elif status in ["cancelled"]:
                        self.gateway.writeLog( "onOrderInfo cancelled data:%s" % str(data))

                        order.status = STATUS_CANCELLED
                        order.cancelTime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                        self.gateway.onOrder(order)

                        del self.tradedVolumeDict[localID]
                        del self.systemLocalDict[systemID]
                        del self.workingOrderDict[localID]

                        self.cancelSystemOrderFilter.add(systemID)   # 排除已经cancel消失得单子

                    elif status == "open":
                        self.gateway.writeLog( "onOrderInfo open data:%s" % str(data))

                        if order.tradedVolume > 0.0:
                            order.status = STATUS_PARTTRADED 
                            self.gateway.onOrder(order)
                        else:
                            order.status = STATUS_NOTTRADED
                            self.gateway.onOrder(order)
                    else:
                        self.gateway.writeError(" Exchange %s , new status %s , data %s" % (EXCHANGE_GATE , str(status) , str(data)), "g13")

            else:
                # 说明是以前发的单子
                if systemID not in self.cancelSystemOrderFilter:        # 排除已经cancel消失得单子
                    if status not in ["closed","cancelled"]:
                        if symbol_pair in self.registerSymbols:
                            self.localID += 1
                            localID = str(self.localID)
                            symbol_pair = systemSymbolToVnSymbol(use_order["currencyPair"])
                            order = VtOrderData()
                            order.gatewayName = self.gatewayName
                            order.symbol = symbol_pair + "." + self.gatewayName
                            order.exchange = EXCHANGE_GATE
                            order.vtSymbol = order.symbol
                            order.orderID = localID
                            order.vtOrderID = '.'.join([order.orderID, order.gatewayName])
                            order.direction = DIRECTION_LONG
                            order.offset = OFFSET_OPEN
                            if side == "sell":
                                order.direction = DIRECTION_SHORT
                                order.offset = OFFSET_CLOSE
                            
                            order.price = price
                            order.totalVolume = volume
                            order.tradedVolume = tradedVolume

                            order.orderTime = now_time

                            if status == "open":
                                if order.tradedVolume > 0.0:
                                    order.status = STATUS_PARTTRADED
                                else:
                                    order.status = STATUS_NOTTRADED
                            else:
                                self.gateway.writeError(" Exchange %s , new status %s , data %s" % (EXCHANGE_GATE , str(status) , str(data)), "g13")

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
    {"result":"true","orders":
    [{"orderNumber":"485615832","type":"buy","rate":0.0002,"amount":"6","total":"0.0012","initialRate":0.0002,
    "initialAmount":"6","filledRate":0,"filledAmount":0,"currencyPair":"bcd_btc","timestamp":"1521430395","status":"open"},
    {"orderNumber":"485615840","type":"sell","rate":0.0006,"amount":"2","total":"0.0012","initialRate":0.0006,"initialAmount":"2",
    "filledRate":0,"filledAmount":0,"currencyPair":"bcd_btc","timestamp":"1521430396","status":"open"}],
    "message":"Success","code":0,"elapsed":"3.045ms"}

    {u'status': u'open', u'filledRate': u'0.00026667', u'orderNumber': 700712022, u'
timestamp': 1524467270, u'amount': u'11.46000000', u'filledAmount': u'0', u'rate
': u'0.00026667', u'initialAmount': u'11.46', u'initialRate': u'0.00026667', u't
otal': u'0.00305604', u'type': u'sell', u'currencyPair': u'AE_BTC'}
    '''
    #----------------------------------------------------------------------
    def onOrderList(self,data, req, reqID):
        # self.gateway.writeLog("onOrderList: %s" % (str(data)))
        result_status = data.get("result" , None)
        if result_status != "true" and result_status != True:
            msg = data.get("message" , u"spot onOrderList! 订单列表查询出错 ")
            code = data.get("code" , "g9")
            self.gateway.writeError(  "data info %s" % (str(data)) + " " + msg , code)
        else:
            try:
                orders = data["orders"]

                still_live_order_system_id = [ str(x["orderNumber"]) for x in orders]
                local_system_dict_keys = self.systemLocalDict.keys()
                for use_order in orders:

                    systemID = str(use_order["orderNumber"])
                    status = use_order["status"]
                    tradedVolume = float(use_order["filledAmount"])
                    price = float(use_order["rate"])
                    volume = float(use_order["amount"])
                    side = use_order["type"]
                    use_dt , use_date, now_time = self.generateDateTime(use_order["timestamp"])

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

                                self.cache_trade_data.append(trade)

                            if status == "open":
                                if tradedVolume > 0.0:
                                    order.status = STATUS_PARTTRADED
                                    self.gateway.onOrder(order)
                                else:
                                    order.status = STATUS_NOTTRADED
                                    self.gateway.onOrder(order)
                                    #elif status == "partial-filled":
                            else:
                                self.gateway.writeError(" Exchange %s , new status %s , data %s" % (EXCHANGE_GATE , str(status) , str(data)), "g13")
                    else:
                        # 说明是以前发的单子
                        self.gateway.writeLog(" registerSymbols :%s" % str(self.registerSymbols))
                        if systemID not in self.cancelSystemOrderFilter:        # 排除已经cancel消失得单子
                            if status not in ["closed","cancelled"]:
                                symbol_pair = systemSymbolToVnSymbol(use_order["currencyPair"])

                                if symbol_pair in self.registerSymbols:
                                    self.localID += 1
                                    localID = str(self.localID)
                                    order = VtOrderData()
                                    order.gatewayName = self.gatewayName
                                    order.symbol = symbol_pair + "." + self.gatewayName
                                    order.exchange = EXCHANGE_GATE
                                    order.vtSymbol = order.symbol
                                    order.orderID = localID
                                    order.vtOrderID = '.'.join([order.orderID, order.gatewayName])
                                    order.direction = DIRECTION_LONG
                                    order.offset = OFFSET_OPEN
                                    if side == "sell":
                                        order.direction = DIRECTION_SHORT
                                        order.offset = OFFSET_CLOSE
                                    
                                    order.price = price
                                    order.totalVolume = volume
                                    order.tradedVolume = tradedVolume

                                    order.orderTime = now_time

                                    if status == "open":
                                        if tradedVolume > 0.0:
                                            order.status = STATUS_PARTTRADED
                                        else:
                                            order.status = STATUS_NOTTRADED
                                    else:
                                        self.gateway.writeError(" Exchange %s , new status %s , data %s" % (EXCHANGE_GATE , str(status) , str(data)), "g13")

                                    localID = self.autoFixMatch( order , localID)
                                    order.orderID = localID
                                    order.vtOrderID = '.'.join([order.orderID, order.gatewayName])

                                    self.gateway.writeLog("onOrderList occure new order, localID %s, sysmtemID %s , order.vtSymbol %s , order.price %s" % (str(localID),str(systemID),str(order.vtSymbol),str(order.price)))

                                    self.workingOrderDict[localID] = order
                                    self.systemLocalDict[systemID] = localID
                                    self.localSystemDict[localID] = systemID
                                    self.tradedVolumeDict[localID] = tradedVolume
                                    
                                    self.gateway.onOrder(order)
            except Exception,ex:
                self.gateway.writeError("onOrderList parse error ,data %s , ex %s" % (str(data) , str(ex)) , "g15")

    '''
    {u'code': 0, u'message': u'Success', u'trades': [{u'tradeID': 50018379, u'orderN
umber': 50018379, u'amount': u'181.50', u'date': u'2018-04-23 05:48:09', u'rate'
: u'0.0001630', u'pair': u'ruff_eth', u'time_unix': 1524433689, u'total': 0.0295
845, u'type': u'buy'}, {u'tradeID': 50018370, u'orderNumber': 50018370, u'amount
': u'256.70', u'date': u'2018-04-23 05:48:06', u'rate': u'0.0001630', u'pair': u
'ruff_eth', u'time_unix': 1524433686, u'total': 0.0418421, u'type': u'buy'}, {u'
tradeID': 50008463, u'orderNumber': 50008463, u'amount': u'139.40', u'date': u'2
018-04-23 04:24:26', u'rate': u'0.0001614', u'pair': u'ruff_eth', u'time_unix':
1524428666, u'total': 0.02249916, u'type': u'buy'}, {u'tradeID': 58372905, u'orderNumber': 58372905, u'amount': u'389.48', u'dat
e': u'2018-04-15 23:39:54', u'rate': u'0.0001380', u'pair': u'ruff_eth', u'time_
unix': 1523806794, u'total': 0.05374824, u'type': u'sell'}], u'result': u'true'}
    '''
    #----------------------------------------------------------------------
    def onTradeList(self,data, req, reqID):
        result_status = data.get("result" , None)
        if result_status != "true" and result_status != True:
            msg = data.get("message" , u"spot onTradeList! 成交列表查询出错 ")
            code = data.get("code" , "g11")
            self.gateway.writeError(  "data info %s" % (str(data)) + " " + msg , code)
        else:
            trades = data["trades"]

            for trade_info in trades:
                trade_amount = float(trade_info["amount"])
                trade_price = float(trade_info["rate"])
                trade_date = trade_info["date"]

                trade_direction = DIRECTION_LONG
                if trade_direction == "sell":
                    trade_direction = DIRECTION_SHORT

                # 1、先排除 重复订单
                flag_not_occure_order = True 
                for bef_trade in self.cache_trade_data:
                    if bef_trade.direction == trade_direction and abs(float(trade_price)-float(bef_trade.price)) < 0.01 * float(bef_trade.price) and abs(float(trade_amount) - float(bef_trade.volume)) < 0.01 * float(bef_trade.volume):
                        flag_not_occure_order = False
                        break

                if flag_not_occure_order == True:
                    # 2、从消失订单中找同一价格的, 时间间隔 3 小时内 ,  成交量 <= 消失订单总量的
                    for systemID in self.systemID_not_found_dict.keys():
                        dis_order_dic = self.systemID_not_found_dict[systemID]
                        dis_order = dis_order_dic["order"]

                        if abs(float(dis_order.price ) - float(trade_price)) < 0.01 * float(trade_price):
                            # 价格已经匹配上 , 继续匹配时间
                            check_dateime = (datetime.now() - timedelta(minutes = 180)).strftime("%Y-%m-%d %H:%M:%S")
                            if trade_date >= check_dateime:
                                # 时间已经匹配上, 匹配订单总量
                                localID = dis_order_dic["localID"]
                                bef_has_volume = self.tradedVolumeDict.get(localID , 0.0)

                                if float(trade_amount) <= (order.totalVolume - float(bef_has_volume)) * 1.01:
                                    # 价格，时间，成交量都匹配上，认为是新的成交 ！
                                    
                                    self.gateway.writeLog("newTrade is found! trade_info:%s and systemID:%s ,localID :%s totalVolume:%s , price:%s , tradedVolume:%s" % (str(trade_info) , str(systemID) , str(localID) , str(order.totalVolume) , str(order.price) , str(order.tradedVolume)))
                                    newTradeVolume = float(trade_amount)
                                    order.tradedVolume = bef_has_volume + order.totalVolume
                                    self.tradedVolumeDict[localID] = order.tradedVolume

                                    # 推送新的成交
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

                                    self.tradedVolumeDict[localID] = order.tradedVolume

                                    self.cache_trade_data.append(trade)

                                    order.status = STATUS_PARTTRADED

                                    if float(order.tradedVolume) * 1.001 > float(order.totalVolume):
                                        order.status = STATUS_ALLTRADED

                                    self.gateway.writeLog("push new trade order , order.vtOrderID:%s order.tradedVolume %s , order.totalVolume %s , order.price %s" % (str(order.vtOrderID) , str(order.tradedVolume) , str(order.totalVolume ), str(order.price) ))
                                    self.gateway.onOrder(order)

    #----------------------------------------------------------------------
    def cancel(self, req):
        self.gateway.writeLog( u"cancel %s,%s" % (req.vtSymbol , req.orderID))

        localID = req.orderID
        symbol_pair = (req.vtSymbol.split('.'))[0]
        if localID in self.localSystemDict:
            systemID = self.localSystemDict[localID]
            self.cancel_order( symbol_pair ,systemID )
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
gateIODataApi
'''
class gateIODataApi(Gate_DataApi):
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(gateIODataApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName

        self.tickDict = {}      # key:symbol, value:tick

        self.registerSymbols = set([])

    #----------------------------------------------------------------------
    def subscribeSymbol(self, subscribeReq):
        use_symbol = (subscribeReq.symbol.split('.'))[0]
        if use_symbol not in self.registerSymbols:
            self.registerSymbols.add(use_symbol)
            
            self.subscribeTick(use_symbol)
            self.subscribeOrderbooks(use_symbol)

    #----------------------------------------------------------------------
    def connect(self, interval , debug = False):
        self.init(interval , debug)
        # 订阅行情并推送合约信息


    '''
    {"result":"true","last":943.1,"lowestAsk":943.1,"highestBid":930.65,
    "percentChange":2.9241762436121,"baseVolume":246844.57,
    "quoteVolume":272.5298,"high24hr":960.98,"low24hr":850}

    add currencyPair , "tnb_btc"
    '''
    #----------------------------------------------------------------------
    def onTick(self, data):
        """实时成交推送"""
        if data["result"] != "true":
            self.gateway.writeLog( "onTick not success, " + str(data))
        else:
            symbol_pair = data["currencyPair"].lower()

            if symbol_pair not in self.tickDict:
                tick = VtTickData()
                tick.gatewayName = self.gatewayName

                tick.exchange = EXCHANGE_GATE
                tick.symbol = '.'.join([symbol_pair, tick.exchange])
                tick.vtSymbol = '.'.join([symbol_pair, tick.exchange])
                self.tickDict[symbol_pair] = tick
            else:
                tick = self.tickDict[symbol_pair]

            tick.highPrice = float(data["highestBid"])
            tick.lowPrice = float(data["lowestAsk"])
            tick.lastPrice = float(data["last"])
            tick.volume = float(data["baseVolume"])

            tick.datetime = datetime.now()
            tick.date = tick.datetime.strftime("%Y%m%d")
            tick.time = tick.datetime.strftime("%H:%M:%S.%f")

            #self.gateway.onTick(tick)

    '''
    {"result":"true","asks":[[8550,0.22],[8549.62,0.052],[8542,0.0612],
    [8538.46,0.2],[8536.75,2.971],[8534.2,0.02],[8518,0.0176],[8512,0.03],
    [8511,0.0414],[8510,0.0559],[8508,0.022],[8500.01,0.04],[8500,3.073864],
    [8499.99,0.2265],[8499,0.167],[8498,0.13],[8497.73,0.1],[8495,0.11],
    [8490,0.01],[8489,0.03],[8484,0.0171],[8480,2.74305],[8477.75,0.1],
    [8469.94,0.072],[8468.61,1],[8450.54,0.02],[8450,0.23482],[8449,0.378],
    [8446.8199998,0.00497305],[8439.99,0.32],[8422.67,0.46],[8421.86,0.03024],
    [8421.13,0.107],[8420,0.0024],[8414.85,0.08],[8409.79,0.049],[8400.75,0.143],
    [8400.69,0.0013],[8400.46,0.40486],[8400,4.68915],[8399,0.34],[8398.6,0.1],
    [8398.18,0.04],[8396.95,1],[8396.5,0.1],[8392.04,2],[8390,0.032],
    [8389.21,0.0015],[8389.2,0.1],[8388.88,2.141],[8386.16,0.072],[8384.15,0.14712],
    [8380,0.13426],[8378.79,0.031],[8378,0.5588],[8377.76,4.877],[8371.39,0.09],
    [8371.23,0.05],[8371,0.03],[8370.7,0.0059],[8366.99,0.01],[8362,0.1],[8360,0.405],
    [8350.66,0.0743],[8350,1.60055],[8346.09,0.215],[8345,0.032],[8342.45,0.0433],
    [8340,0.1],[8339,0.15],[8336.53,0.06990002],[8333.34,1.3],[8330,0.2],[8322,0.08],
    [8320.62,0.0152],[8320,0.01],[8317.36,0.15],[8316.36,0.81499355],[8310.92,0.67],[8310.88,0.01],
    [8307.93,0.1],[8300.16,0.0628],[8300,0.21797663],[8290.75,0.09597886],[8288.47,0.77590301],
    [8288.25999995,0.13943891],[8288.25,0.239],[8288.06,1.039]],"bids":[[8271.83,0.15],
    [8258.82,0.043],[8258.81,0.0184],[8231.02,0.0136],[8231.01,0.936],[8231,0.1],[8230,0.0457],
    [8220,0.1],[8206,1],[8200,0.2314],[8189.04,0.12],[8189.03,4.878],[8189.02,0.0158],[8179,3.9461],
    [8178.2,0.11],[8178,0.07],[8164.96999976,0.0212475],[8150,0.6263],[8145,0.064],[8130.18,0.0122],
    [8117.54,0.17],[8110.32,0.0086],[8101,0.56225348],[8100,5.137846],[8090,0.08],[8085.75,0.01],
    [8082.25,0.02149164],[8075,0.003],[8073.45,4.878],[8061.1,0.0791],[8061,0.1561],[8050,0.0531],
    [8025,0.0031],[8024,0.7334],[8023.71,0.36],[8023.7,0.01],[8020,0.0036],[8010,0.049971],
    [8008.08,0.005],[8001,0.0031],[8000.01,0.398005],[8000,0.9557],[7998.54,0.0405],
    [7995.97,0.1948],[7995.96,0.006694],[7992.01,0.19703749],[7990,0.0125],[7987.99,0.08419601],
    [7980,0.0125],[7977.98,0.12196883],[7975,0.0031],[7970.02,0.3],[7970.01,0.08],[7970,0.0125],
    [7963.24,0.008],[7960,0.0125],[7950,0.1156],[7940,0.0125],[7930,0.0126],[7929.01,0.01],[7928.98,0.05],
    [7925,0.0031],[7920,0.0126],[7919,0.063],[7910,0.0376],[7908.89,0.15],[7903,0.06],[7901,0.0273],
    [7900.79,0.0124],[7900,0.6375],[7895,0.101],[7892.74,0.0426],[7880.22,0.3],[7880.01,0.42],
    [7878,0.0015],[7875,0.0031],[7862,0.025],[7858,0.1552],[7851,0.145],[7850,0.0031],
    [7825,0.0031],[7817.77,0.069],[7808,0.0621],[7800,0.974874],[7786.69,0.42],
    [7786.26,0.146],[7777.77,0.04987],[7777,0.1637],[7755,0.02],[7749.26,0.5],[7749.25,0.52]]}
    add currencyPair , "tnb_btc"
    '''
    #----------------------------------------------------------------------
    def onDepth(self, data):
        """实时成交推送"""
        if data["result"] != "true":
            self.gateway.writeLog( "onDepth not success, " + str(data))
        else:
            symbol_pair =  data["currencyPair"].lower()

            if symbol_pair not in self.tickDict:
                tick = VtTickData()
                tick.gatewayName = self.gatewayName

                tick.symbol = symbol_pair
                tick.exchange = EXCHANGE_GATE
                tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
                self.tickDict[symbol_pair] = tick
            else:
                tick = self.tickDict[symbol_pair]

            bids = data["bids"][:5]
            asks = data["asks"][-5:]

            bids = [ (float(x[0]) , float(x[1])) for x in bids ]
            asks = [ (float(x[0]) , float(x[1])) for x in asks ]

            asks.reverse()

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


            tick.datetime = datetime.now()
            tick.date = tick.datetime.strftime("%Y%m%d")
            tick.time = tick.datetime.strftime("%H:%M:%S.%f")

            self.gateway.onTick(tick)
