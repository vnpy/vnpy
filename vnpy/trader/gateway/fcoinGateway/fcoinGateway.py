# encoding: UTF-8

import os
import json


import json
from vnpy.api.fcoin import Fcoin_TradeApi, Fcoin_DataApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, systemSymbolToVnSymbol , VnSymbolToSystemSymbol
from vnpy.trader.vtConstant import EXCHANGE_FCOIN,PRICETYPE_LIMITPRICE,PRODUCT_SPOT,\
    DIRECTION_LONG,DIRECTION_SHORT,DIRECTION_NET, OFFSET_OPEN,OFFSET_CLOSE, \
    STATUS_PARTTRADED,STATUS_UNKNOWN,STATUS_REJECTED,STATUS_NOTTRADED,STATUS_CANCELLED,STATUS_ALLTRADED
from datetime import datetime , timedelta
from time import sleep
import traceback
'''
Fcoin 接口
'''
class FcoinGateway(VtGateway):
    """fcoin接口"""
    #----------------------------------------------------------------------
    def __init__(self, eventEngine , gatewayName='FCOIN'):
        """Constructor"""
        super(FcoinGateway , self).__init__(eventEngine, gatewayName)
        
        self.tradeApi = FcoinTradeApi(self)
        self.dataApi = FcoinDataApi(self)
        
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)       

        self.connected = False

        self.qryEnabled = True

        self.accountID = "None"

        self.total_count = 0
        self.delayTime = 10

        self.log_message = False  # 记录接口数据
        self.auto_subscribe_symbol_pairs = set()  # 自动订阅现货合约对清单
        self.use_spot_symbol_pairs = set()  # 使用现货合约对（从配置文件读取，减少运算量）
    # ----------------------------------------------------------------------
    def connect(self):
        """连接"""
        try:
            # 载入json文件
            with open(self.filePath) as f:
                # 解析json文件
                setting = json.load(f)
                try:
                    accessKey = str(setting['accessKey'])
                    secretKey = str(setting['secretKey'])
                    interval = setting.get('interval',1)
                    useAccountID = str(setting['accountID'])

                    self.log_message = setting.get('log_message', False)
                    # 若限定使用的合约对
                    if "symbol_pairs" in setting.keys():
                        self.use_spot_symbol_pairs = set(setting["symbol_pairs"])

                    # 若希望连接后自动订阅
                    if 'auto_subscribe' in setting.keys():
                        self.auto_subscribe_symbol_pairs = set(setting['auto_subscribe'])

                except KeyError:
                    self.writeError(u'连接配置缺少字段，请检查:{}'.format(self.filePath))

                    return
        except IOError:
            self.writeError(u'读取连接配置出错，请检查:{}'.format(self.filePath))
            return
        
        # 设置账户ID
        self.tradeApi.setAccountID(useAccountID)

        for symbol_pair in self.auto_subscribe_symbol_pairs:
            self.writeLog(u'自动订阅现货合约:{}'.format(symbol_pair))
            self.dataApi.registerSymbols.add(symbol_pair)
            self.tradeApi.registerSymbols.add(symbol_pair)

        # 初始化接口
        self.tradeApi.init(accessKey, secretKey)
        self.tradeApi.DEBUG = self.log_message
        self.writeLog(u'交易接口初始化成功')

        self.tradeApi.get_symbols()
        self.writeLog(u'获得{}币种合约请求已发送'.format(EXCHANGE_FCOIN))
        
        self.dataApi.connect(interval=interval,  debug=self.log_message)
        self.writeLog(u'fcoin 行情接口初始化成功')


        # 启动查询
        self.initQuery()
        self.startQuery() 

    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情，自动订阅全部行情，无需实现"""
        self.writeLog( "fcoinGateway subscribeReq %s" % (subscribeReq.symbol))
        symbol_pair = subscribeReq.symbol.split('.')[0]
        if len(self.use_spot_symbol_pairs) > 0 and  symbol_pair in self.use_spot_symbol_pairs:
            self.tradeApi.subscribeSymbol(subscribeReq)
            self.dataApi.subscribeSymbol(subscribeReq)
        else:
            self.writeError(u'{}不在配置的行情合约对中，请先添加'.format(symbol_pair))

    # ----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.tradeApi.sendOrder(orderReq)

    # ----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        if len(cancelOrderReq.vtSymbol) == 0 and len(cancelOrderReq.symbol)>0:
            cancelOrderReq.vtSymbol = cancelOrderReq.symbol
        elif len(cancelOrderReq.vtSymbol) > 0 and len(cancelOrderReq.symbol) == 0:
            cancelOrderReq.symbol = cancelOrderReq.vtSymbol
        return self.tradeApi.cancel(cancelOrderReq)

    # ----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        pass
        
    # ----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        pass
    
    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.tradeApi.exit()
        self.dataApi.exit()
        
    # ----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            self.qryFunctionList = [self.tradeApi.listAllOrders]
            #self.qryFunctionList = [self.tradeApi.queryWorkingOrders, self.tradeApi.queryAccount]

        # 查询所有交易参数：系统支持的交易市场的参数信息，包括交易费，最小下单量，价格精度等。
        self.tradeApi.get_symbols()

        # 查询持仓
        self.tradeApi.get_balance()


    # ----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.total_count += 1
        if self.total_count % self.delayTime == 0:
            for function in self.qryFunctionList:
                function()

        if self.total_count % 30 == 0:
            self.tradeApi.get_balance()
                
    # ----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)

    # ----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled

'''
fcoinTradeApi
'''
class FcoinTradeApi(Fcoin_TradeApi):
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(FcoinTradeApi , self).__init__()

        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        self.accountID = "FCOIN"
        self.DEBUG  = False

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
            except Exception as ex:
                self.gateway.writeError( "parse list order error,systemID %s , ex %s" % (str(systemID), str(ex)) , "g16")
            reqID = self.order_info( systemID)
            self.reqIDToSystemID[reqID] = str(systemID)

        # 检查  渣gate的成交日志， 以避免渣gate服务器的问题导致的订单消失
        for use_symbol in self.registerSymbols:
            self.orders_list(use_symbol , states = "submitted")
            sleep(0.1)
            self.orders_list(use_symbol , states = "partial_filled")

    '''
    {u'status': 0, u'data': 
      [{u'quote_currency': u'usdt', u'base_currency': u'btc',u'price_decimal': 2, u'name': u'btcusdt', u'amount_decimal': 4}, 
      {u'quote_currency': u'usdt', u'base_currency': u'eth', u'price_decimal': 2, u'name': u'ethusdt', u'amount_decimal': 4}, 
      {u'quote_currency': u'usdt', u'base_currency': u'bch', u'price_decimal': 2, u'name': u'bchusdt', u'amount_decimal': 4}, 
      {u'quote_currency': u'usdt', u'base_currency': u'ltc', u'price_decimal': 2, u'name': u'ltcusdt', u'amount_decimal': 4}, 
      {u'quote_currency': u'usdt', u'base_currency': u'ft', u'price_decimal': 6, u'name': u'ftusdt', u'amount_decimal': 2}, 
      {u'quote_currency': u'eth', u'base_currency': u'ft', u'price_decimal': 8, u'name': u'fteth', u'amount_decimal': 2}, 
      {u'quote_currency': u'eth', u'base_currency': u'zip', u'price_decimal': 8, u'name': u'zipeth', u'amount_decimal': 2}, 
      {u'quote_currency': u'usdt', u'base_currency': u'etc', u'price_decimal': 2, u'name': u'etcusdt', u'amount_decimal': 4}, 
      {u'quote_currency': u'btc', u'base_currency': u'ft', u'price_decimal': 8, u'name': u'ftbtc', u'amount_decimal': 2}]}
    '''
    # ----------------------------------------------------------------------
    def onAllSymbols(self,data, req, reqID):
        if self.DEBUG:
            print(data)
        result_status = data.get("status" , None)
        if str(result_status) == "0":
            pairs = data.get('data' , None)
            if pairs != None:
                for info in pairs:
                    symbol_pair = info["base_currency"] + "_" + info["quote_currency"]
                    self.gateway.use_spot_symbol_pairs.add(symbol_pair)

                    contract = VtContractData()
                    contract.gatewayName = self.gatewayName
                    contract.symbol = symbol_pair + "." + EXCHANGE_FCOIN
                    contract.exchange = EXCHANGE_FCOIN
                    contract.vtSymbol = symbol_pair + "." + EXCHANGE_FCOIN
                    contract.name = u'FCOIN现货%s' % symbol_pair
                    contract.size = 1
                    contract.priceTick = round(0.1 ** int(info['price_decimal']),int(info['price_decimal']))
                    contract.productClass = PRODUCT_SPOT
                    contract.volumeTick = round(0.1 ** int(info['amount_decimal']),int(info['amount_decimal']))
                    self.gateway.onContract(contract)

        else:
            self.gateway.writeError( u"market info not get! fcoin市场数据没有得到", "f3")

    '''
    发送系统委托
    '''
    #---------------------------------------------------------------------
    def sendOrder(self, req):
        # 检查是否填入了价格，禁止市价委托
        if req.priceType != PRICETYPE_LIMITPRICE:
            self.gateway.writeError("Fcoin接口仅支持限价单" , "g1")
            return None

        symbol = req.vtSymbol
        if req.direction == DIRECTION_LONG:
            reqID = self.spotTrade( symbol = systemSymbolToVnSymbol(symbol) , _type = "buy" , price = req.price , volume = req.volume )
        else:
            reqID = self.spotTrade( symbol = systemSymbolToVnSymbol(symbol) , _type = "sell" , price = req.price , volume = req.volume)

        self.localID += 1
        localID = str(self.localID)
        self.reqLocalDict[reqID] = localID

        # 推送委托信息
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = req.vtSymbol
        order.exchange = EXCHANGE_FCOIN
        order.vtSymbol = req.vtSymbol

        order.orderID = localID
        order.vtOrderID = '.'.join([ order.gatewayName,order.orderID])

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
    {u'status': 0, u'data': [{u'available': u'0.000000000000000000', u'currency': u'
zil', u'frozen': u'0.000000000000000000', u'balance': u'0.000000000000000000'},
{u'available': u'0.000000000000000000', u'currency': u'omg', u'frozen': u'0.0000
00000000000000', u'balance': u'0.000000000000000000'}, {u'available': u'4.698033
150126758917', u'currency': u'btc', u'frozen': u'0.000000000000000000', u'balanc
e': u'4.698033150126758917'}, {u'available': u'0.000000000000000000', u'currency
': u'icx', u'frozen': u'0.000000000000000000', u'balance': u'0.00000000000000000
0'}, {u'available': u'0.451232205502201079', u'currency': u'eth', u'frozen': u'0
.000000000000000000', u'balance': u'0.451232205502201079'}, {u'available': u'0.0
00000000000000000', u'currency': u'btm', u'frozen': u'0.000000000000000000', u'b
alance': u'0.000000000000000000'}, {u'available': u'0.055768745744915762', u'cur
rency': u'bch', u'frozen': u'0.000000000000000000', u'balance': u'0.055768745744
915762'}, {u'available': u'0.420928988807311474', u'currency': u'ltc', u'frozen'
: u'0.000000000000000000', u'balance': u'0.420928988807311474'}, {u'available':
u'2737.891969594195540892', u'currency': u'usdt', u'frozen': u'0.000000000000000
000', u'balance': u'2737.891969594195540892'}, {u'available': u'0.00096187488951
9338', u'currency': u'ft', u'frozen': u'0.000000000000000000', u'balance': u'0.0
00961874889519338'}, {u'available': u'974.441354464058907300', u'currency': u'zi
p', u'frozen': u'0.000000000000000000', u'balance': u'974.441354464058907300'},
{u'available': u'0.244376439974901042', u'currency': u'etc', u'frozen': u'0.0000
00000000000000', u'balance': u'0.244376439974901042'}]}
    '''
    #----------------------------------------------------------------------
    def onGetBalance(self,data, req, reqID):
        result_status = data.get("status" , None)
        if str(result_status) == "0":
            info_result = data.get("data", None)
            for info in info_result:
                available = float(info.get("available",0.0))
                frozen = float(info.get("frozen",0.0))
                balance = float(info.get("balance",0.0))
                asset = info.get("currency","")

                if len(asset) > 0:
                    asset = asset.lower()
                    posObj = VtPositionData()
                    posObj.gatewayName = self.gatewayName
                    posObj.symbol = asset + "." + EXCHANGE_FCOIN
                    posObj.exchange = EXCHANGE_FCOIN
                    posObj.vtSymbol = posObj.symbol
                    posObj.direction = DIRECTION_NET
                    posObj.vtPositionName = '.'.join( [posObj.vtSymbol, posObj.direction])
                    posObj.ydPosition = float(available) + float(frozen)
                    posObj.position = balance
                    posObj.frozen = float(frozen)
                    posObj.positionProfit = 0

                    if posObj.position > 0.0:
                        self.gateway.onPosition(posObj)
        else:
            self.gateway.writeError( u"onGetBalance not get! fcoin仓位没有得到 " , "f5")
    '''
    错误单返回 结果 
    {'status': 1001, 'msg': u'bad argument: amount'}
    {'status': 429,  'msg': 'exceed api request limit'}
    正确单返回结果
    {u'status': 0, u'data': u'FqR0e0zmPFK4NQlgrc8sl1qmvpv-lEPQxawdrOBGZuA='}
    '''
    #----------------------------------------------------------------------
    def onSpotTrade(self,data, req, reqID):
        result_status = data.get("status" , None)
        if str(result_status) != "0":
            msg = data.get("msg" , u"spot error! 下单出错 ")
            code = data.get("status" , "f6")
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
            systemID = str(data["data"])

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
    已完成订单
    {"status":3008,"msg":"submit cancel invalid order state"}
    已完成订单
    -mJeAvSsGP4lmbHWciEMBnU3XnsnRjQG39FYqIvf7TU
    {u'status': 0}

    {u'status': 0}  然后 onOrderInfo
{u'status': 0, u'data': {u'created_at': 1528707853275L, u'fill_fees': u'0.000000
000000000000', u'price': u'0.319466000000000000', u'state': u'canceled', u'fille
d_amount': u'0.000000000000000000', u'id': u'pCtOk-4BByozBRwi1yKeN3ObsLkap5ieRt6
wuNK_M1E=', u'source': u'api', u'amount': u'10.000000000000000000', u'executed_v
alue': u'0.000000000000000000', u'type': u'limit', u'symbol': u'ftusdt', u'side'
: u'buy'}}

    '''
    #----------------------------------------------------------------------
    def onCancelOrder(self, data, req, reqID):
        if self.DEBUG:
            print(data)
        result_status = data.get("status" , None)
        if result_status is None or result_status !=0 :
            msg = data.get("msg" , u"spot onCancelOrder! 撤销出错 ")
            code = data.get("code" , "f7")
            self.gateway.writeError( "onCancelOrder data info %s" % (str(data)) + " " + msg , code)

            try:
                code = str(code)
                if code in ["3008"]:
                    localID = self.reqLocalDict[reqID]

                    if localID in self.workingOrderDict.keys():
                        order = self.workingOrderDict[localID]
                        order.status = STATUS_CANCELLED

                        self.gateway.onOrder(order)

                        del self.workingOrderDict[localID]
                        del self.reqLocalDict[reqID]

                        if localID in self.localSystemDict.keys():
                            systemID = self.localSystemDict[localID]
                            del self.systemLocalDict[systemID]

            except Exception as ex:
                self.gateway.writeLog("Error in parse onCancelOrder rejected , ex:%s , data:%s" % (str(ex) , str(data)))
        else:
            try:
                localID = self.reqLocalDict.get(reqID,None)
                if localID is None:
                    self.gateway.writeError(u'onCancelOrder, could not find {} in self.requLocalDct'.format(reqID))
                    return
                if localID in self.workingOrderDict:
                    order = self.workingOrderDict[localID]
                    self.gateway.writeLog( "onCancelOrder 1 : order.totalVolume %s  order.tradedVolume %s order.price %s" % ( str(order.totalVolume) , str(order.tradedVolume) , str(order.price)) )
                    order.status = STATUS_CANCELLED
                    self.gateway.onOrder(order)

                    del self.workingOrderDict[localID]
                    del self.reqLocalDict[reqID]
                    if localID in self.localSystemDict.keys():
                        systemID = self.localSystemDict[localID]
                        del self.systemLocalDict[systemID]

            except Exception as ex:
                self.gateway.writeError("onCancelOrder parse error ,data {} , ex {},trace:{}".format(str(data) , str(ex), traceback.format_exc()) , "f15")

    '''
    将查询到的订单 匹配已经发出的订单，来修正错误匹配部分
    '''
    #----------------------------------------------------------------------
    def autoFixMatch(self, to_compare_order , t_localID):
        self.gateway.writeLog("self.cacheSendLocalOrder : %s , t_localID %s " % (str(self.cacheSendLocalOrder) , t_localID))
        for localID in self.cacheSendLocalOrder:
            from_order = self.workingOrderDict[localID]

            if from_order.direction == to_compare_order.direction and from_order.offset == to_compare_order.offset and abs( float(from_order.price) - float(to_compare_order.price)) < 0.0001 *float(to_compare_order.price) and abs( float(from_order.totalVolume) - float(to_compare_order.totalVolume)) < 0.0001*float(to_compare_order.totalVolume):
                self.gateway.writeLog("autoFixMatch compare order now! t_localID %s , localID %s" % (str(t_localID) , str(localID)))
                t_localID = localID
                break
        if t_localID in self.cacheSendLocalOrder:
            self.cacheSendLocalOrder.remove(t_localID)
            self.gateway.writeLog("autoFixMatch cacheSendLocalOrder del localID %s" % (t_localID))
        return t_localID

    '''
    已完成订单
    {u'status': 0, u'data': {u'created_at': 1528530599997L, u'fill_fees': u'3.000000
000000000000', u'price': u'0.591000000000000000', u'state': u'filled', u'filled_
amount': u'3000.000000000000000000', u'id': u'U-RcMGl_XUdfs2yI-98a0hQzoMVlVPYiqt
XvmZio9F8=', u'source': u'web', u'amount': u'3000.000000000000000000', u'execute
d_value': u'1773.000000000000000000', u'type': u'limit', u'symbol': u'ftusdt', u
'side': u'buy'}}
    未完成订单
    {u'status': 0, u'data': {u'created_at': 1528617873671L, u'fill_fees': u'0.000000
000000000000', u'price': u'0.300000000000000000', u'state': u'submitted', u'fill
ed_amount': u'0.000000000000000000', u'id': u'-mJeAvSsGP4lmbHWciEMBnU3XnsnRjQG39
FYqIvf7TU=', u'source': u'api', u'amount': u'1.000000000000000000', u'executed_v
alue': u'0.000000000000000000', u'type': u'limit', u'symbol': u'ftusdt', u'side'
: u'buy'}}

    new state !!   这是还没被处理的 新返回阶段
    pending_cancel   
    partial_filled  

submitted   已提交
partial_filled  部分成交
partial_canceled    部分成交已撤销
filled  完全成交
canceled    已撤销
pending_cancel  撤销已提交
    '''
    #----------------------------------------------------------------------
    def onOrderInfo(self,data, req, reqID):
        if self.DEBUG:
            print(data)
        result_status = data.get("status" , None)
        if str(result_status) != "0" and result_status != True:
            msg = data.get("msg" , u"spot onOrderInfo! 订单查询出错")
            code = data.get("code" , "f8")
            self.gateway.writeError( "onCancelOrder data info %s" % (str(data)) + " " + msg , code)
        else:
            use_order = data["data"]
            systemID = use_order["id"]
            status = use_order["state"]
            tradedVolume = float(use_order["filled_amount"])
            totalVolume = float(use_order["amount"])
            price = float(use_order["price"])
            side = use_order["side"]

            use_dt , use_date, now_time = self.generateDateTime(use_order["created_at"])

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
                        trade.vtTradeID = '.'.join([trade.gatewayName,trade.tradeID])
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

                    # 订单已经结束
                    if status in ["filled","canceled","partial_canceled"]:
                        # 判断是否是 撤销单
                        if tradedVolume + 0.000001 < totalVolume:
                            order.status = STATUS_CANCELLED
                        else:
                            order.status = STATUS_ALLTRADED
                            order.cancelTime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                        self.gateway.onOrder(order)

                        del self.tradedVolumeDict[localID]
                        del self.systemLocalDict[systemID]
                        del self.workingOrderDict[localID]

                        self.cancelSystemOrderFilter.add(systemID)  # 排除已经cancel消失得单子

                    elif status in [ "partial_filled" , "submitted" ]:
                        if tradedVolume > 0.0000001:
                            order.status = STATUS_PARTTRADED
                        else:
                            order.status = STATUS_NOTTRADED

                        self.gateway.onOrder(order)
                    else:
                        if tradedVolume > 0.0000001:
                            order.status = STATUS_PARTTRADED
                            self.gateway.onOrder(order)
                        self.gateway.writeError(" Exchange %s , new status %s , data %s" % (EXCHANGE_FCOIN , str(status) , str(data)), "f13")
            else:
                # 说明是以前发的单子
                if systemID not in self.cancelSystemOrderFilter:        # 排除已经cancel消失得单子
                    if status not in ["filled" , "canceled","partial_canceled"]:
                        symbol_pair = systemSymbolToVnSymbol(use_order["symbol"])
                        if symbol_pair in self.registerSymbols:
                            self.localID += 1
                            localID = str(self.localID)
                            
                            order = VtOrderData()
                            order.gatewayName = self.gatewayName
                            order.symbol = symbol_pair + "." + self.gatewayName
                            order.exchange = EXCHANGE_FCOIN
                            order.vtSymbol = order.symbol
                            order.orderID = localID
                            order.vtOrderID = '.'.join([order.gatewayName,order.orderID])
                            order.direction = DIRECTION_LONG
                            order.offset = OFFSET_OPEN
                            if side == "sell":
                                order.direction = DIRECTION_SHORT
                                order.offset = OFFSET_CLOSE
                            
                            order.price = price
                            order.totalVolume = totalVolume
                            order.tradedVolume = tradedVolume

                            order.orderTime = now_time

                            if status in [ "partial_filled" , "submitted" ]:
                                if order.tradedVolume > 0.0000001:
                                    order.status = STATUS_PARTTRADED
                                else:
                                    order.status = STATUS_NOTTRADED
                            else:
                                self.gateway.writeError(" Exchange %s , new status %s , data %s" % (EXCHANGE_FCOIN , str(status) , str(data)), "f13")

                            if order.tradedVolume > 0.00000001:
                                order.status = STATUS_PARTTRADED

                            localID = self.autoFixMatch( order , localID)
                            order.orderID = localID
                            order.vtOrderID = '.'.join([order.gatewayName,order.orderID,])
                            self.gateway.writeLog(" onOrderInfo occure new order, localID %s, sysmtemID %s , order.vtSymbol %s , order.price %s" % (str(localID),str(systemID),str(order.vtSymbol),str(order.price)))

                            self.workingOrderDict[localID] = order
                            self.systemLocalDict[systemID] = localID
                            self.localSystemDict[localID] = systemID
                            self.tradedVolumeDict[localID] = tradedVolume
                            
                            self.gateway.onOrder(order)


    '''

    未完成订单 的取消状态
    {u'status': 0, u'data': [{u'created_at': 1528638175889L, u'fill_fees': u'0.00000
0000000000000', u'price': u'0.300000000000000000', u'state': u'submitted', u'fil
led_amount': u'0.000000000000000000', u'id': u'FqR0e0zmPFK4NQlgrc8sl1qmvpv-lEPQx
awdrOBGZuA=', u'source': u'api', u'amount': u'1.000000000000000000', u'executed_
value': u'0.000000000000000000', u'type': u'limit', u'symbol': u'ftusdt', u'side
': u'buy'}]}

    错误的订单状态:
    {'status': 1004, 'msg': u'invalid symbol: ftusdts'}
    '''
    #----------------------------------------------------------------------
    def onOrderList(self,data, req, reqID):
        if self.DEBUG:
            print (data)
        result_status = data.get("status" , None)
        if str(result_status) != "0":
            msg = data.get("msg" , u"spot onOrderList! 订单列表查询出错 ")
            code = data.get("status" , "f9")
            self.gateway.writeError(  "data info %s" % (str(data)) + " " + msg , code)
        else:
            try:
                orders = data["data"]
                still_live_order_system_id = [ str(x["id"]) for x in orders]
                local_system_dict_keys = self.systemLocalDict.keys()

                for use_order in orders:
                    systemID = str(use_order["id"])
                    status = use_order["state"]
                    tradedVolume = float(use_order["filled_amount"])
                    totalVolume = float(use_order["amount"])
                    price = float(use_order["price"])
                    side = use_order["side"]
                    use_dt , use_date, now_time = self.generateDateTime(use_order["created_at"])

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
                                trade.vtTradeID = '.'.join([ trade.gatewayName,trade.tradeID])
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

                            if status == "submitted":
                                if tradedVolume > 0.00000001:
                                    order.status = STATUS_PARTTRADED
                                    self.gateway.onOrder(order)
                                else:
                                    order.status = STATUS_NOTTRADED
                                    self.gateway.onOrder(order)
                            else:
                                if tradedVolume > 0.0000001:
                                    order.status = STATUS_PARTTRADED
                                    self.gateway.onOrder(order)
                                self.gateway.writeError(" Exchange %s , new status %s , data %s" % (EXCHANGE_FCOIN , str(status) , str(data)), "f13")
                    else:
                        # 说明是以前发的单子
                        # self.gateway.writeLog(" registerSymbols :%s" % str(self.registerSymbols))
                        if systemID not in self.cancelSystemOrderFilter:        # 排除已经cancel消失得单子
                            if status not in ["filled","canceled"]:
                                symbol_pair = systemSymbolToVnSymbol(use_order["symbol"])

                                if symbol_pair in self.registerSymbols:
                                    self.localID += 1
                                    localID = str(self.localID)
                                    order = VtOrderData()
                                    order.gatewayName = self.gatewayName
                                    order.symbol = symbol_pair + "." + self.gatewayName
                                    order.exchange = EXCHANGE_FCOIN
                                    order.vtSymbol = order.symbol
                                    order.orderID = localID
                                    order.vtOrderID = '.'.join([ order.gatewayName,order.orderID])
                                    order.direction = DIRECTION_LONG
                                    order.offset = OFFSET_OPEN
                                    if side == "sell":
                                        order.direction = DIRECTION_SHORT
                                        order.offset = OFFSET_CLOSE
                                    
                                    order.price = price
                                    order.totalVolume = totalVolume
                                    order.tradedVolume = tradedVolume

                                    order.orderTime = now_time

                                    if status == "open":
                                        if tradedVolume > 0.0:
                                            order.status = STATUS_PARTTRADED
                                        else:
                                            order.status = STATUS_NOTTRADED
                                    else:
                                        self.gateway.writeError(" Exchange %s , new status %s , data %s" % (EXCHANGE_FCOIN , str(status) , str(data)), "g13")

                                    if tradedVolume > 0.0000001:
                                        order.status = STATUS_PARTTRADED

                                    localID = self.autoFixMatch( order , localID)
                                    order.orderID = localID
                                    order.vtOrderID = '.'.join([order.gatewayName,order.orderID])

                                    self.gateway.writeLog("onOrderList occure new order, localID %s, sysmtemID %s , order.vtSymbol %s , order.price %s" % (str(localID),str(systemID),str(order.vtSymbol),str(order.price)))

                                    self.workingOrderDict[localID] = order
                                    self.systemLocalDict[systemID] = localID
                                    self.localSystemDict[localID] = systemID
                                    self.tradedVolumeDict[localID] = tradedVolume
                                    
                                    self.gateway.onOrder(order)
            except Exception as ex:
                self.gateway.writeError("onOrderList parse error ,data %s , ex %s" % (str(data) , str(ex)) , "f15")

    #----------------------------------------------------------------------
    def cancel(self, req):
        self.gateway.writeLog( u"cancel %s,%s" % (req.vtSymbol , req.orderID))

        localID = req.orderID
        symbol_pair = (req.vtSymbol.split('.'))[0]
        if localID in self.localSystemDict:
            systemID = self.localSystemDict[localID]
            self.cancel_order( systemID )
        else:
            self.cancelDict[localID] = req

    # ----------------------------------------------------------------------
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(float(s)/1e3)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return dt , date, time

'''
FcoinDataApi
'''
class FcoinDataApi(Fcoin_DataApi):
    # ----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(FcoinDataApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName

        self.tickDict = {}      # key:symbol, value:tick

        self.registerSymbols = set([])

    # ----------------------------------------------------------------------
    def subscribeSymbol(self, subscribeReq):
        use_symbol = (subscribeReq.symbol.split('.'))[0]
        if use_symbol not in self.registerSymbols:
            self.registerSymbols.add(use_symbol)
            self.gateway.writeLog("subscribeTick symbol:{}".format(use_symbol))
            self.gateway.writeLog("subscribeOrderbooks symbol:{}".format(use_symbol))
        self.subscribeTick(use_symbol)
        self.subscribeOrderbooks(use_symbol)

    # ----------------------------------------------------------------------
    def connect(self, interval, debug=False):
        self.init(interval, debug)
        for symbol in self.registerSymbols:
            self.subscribeTick(symbol)
            self.subscribeOrderbooks(symbol)

    '''
    [
      "最新成交价",
      "最近一笔成交的成交量",
      "最大买一价",
      "最大买一量",
      "最小卖一价",
      "最小卖一量",
      "24小时前成交价",
      "24小时内最高价",
      "24小时内最低价",
      "24小时内基准货币成交量, 如 btcusdt 中 btc 的量",
      "24小时内计价货币成交量, 如 btcusdt 中 usdt 的量"
    ]
    {u'status': 0, u'data': {u'type': u'ticker.ftusdt', u'ticker': [0.483877, 99.0,
0.483876, 91.0, 0.483877, 6763.79, 0.5625, 0.66, 0.3994, 105720494.48557205, 495
23332.79558287], u'seq': 616993}}
    '''
    #----------------------------------------------------------------------
    def onTick(self, data):
        """实时成交推送"""
        result_status = data.get("status" , None)
        if str(result_status) != "0":
            self.gateway.writeLog( "onTick not success, " + str(data))
        else:
            info = data["data"]
            u_type = info["type"]
            ticker = info["ticker"]

            last_price = float(ticker[0])
            use_volume = float(ticker[-1])

            symbol_pair = (u_type.split('.'))[1]
            symbol_pair = systemSymbolToVnSymbol(symbol_pair)

            if symbol_pair not in self.tickDict:
                tick = VtTickData()
                tick.gatewayName = self.gatewayName

                tick.exchange = EXCHANGE_FCOIN
                tick.symbol = '.'.join([symbol_pair, tick.exchange])
                tick.vtSymbol = '.'.join([symbol_pair, tick.exchange])
                self.tickDict[symbol_pair] = tick
            else:
                tick = self.tickDict[symbol_pair]

            tick.highPrice = last_price
            tick.lowPrice = last_price
            tick.lastPrice = last_price
            tick.volume = use_volume

            tick.datetime = datetime.now()
            tick.date = tick.datetime.strftime("%Y%m%d")
            tick.time = tick.datetime.strftime("%H:%M:%S.%f")

    '''
    {u'status': 0, u'data': {u'type': u'depth.L20.ftusdt', u'seq': 617017, u'bids':
[0.483876, 41.0, 0.483612, 1.0, 0.483, 565.3, 0.482998, 18.7, 0.482949, 1.0, 0.4
82912, 3000.0, 0.482807, 20.0, 0.48, 857.96, 0.476, 2955.3, 0.47581, 402.81, 0.4
7574, 184.9, 0.475738, 183.0, 0.475, 1569.3, 0.472039, 297.0, 0.471, 30.0, 0.470
314, 200.0, 0.470313, 221.61, 0.47, 3092.68, 0.469608, 400.0, 0.469606, 284.0],
u'ts': 1528474816007L, u'asks': [0.483877, 6763.79, 0.483879, 95.0, 0.48388, 99.
0, 0.483881, 102.0, 0.483882, 1166.66, 0.484407, 20.0, 0.484848, 3000.0, 0.48499
7, 95.0, 0.484998, 92.0, 0.485, 991.76, 0.485008, 92.0, 0.485009, 98.0, 0.48678,
 283.94689891, 0.486793, 91.0, 0.486794, 91.0, 0.486795, 3.0, 0.486796, 96.0, 0.
486797, 20.0, 0.486798, 20.0, 0.486799, 90.0]}}
    '''
    #----------------------------------------------------------------------
    def onDepth(self, data):
        result_status = data.get("status", None)
        if str(result_status) != "0":
            self.gateway.writeLog( "onDepth not success, " + str(data))
        else:
            info = data["data"]
            u_type = info["type"]
            symbol_pair = (u_type.split('.'))[-1]
            symbol_pair = systemSymbolToVnSymbol(symbol_pair)

            if symbol_pair not in self.tickDict:
                tick = VtTickData()
                tick.gatewayName = self.gatewayName

                tick.symbol = symbol_pair
                tick.exchange = EXCHANGE_FCOIN
                tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
                self.tickDict[symbol_pair] = tick
            else:
                tick = self.tickDict[symbol_pair]

            bids_data = info["bids"]
            asks_data = info["asks"]

            bids_data = [float(x) for x in bids_data]
            asks_data = [float(x) for x in asks_data]
        
            llen_bids = len(bids_data)
            llen_asks = len(asks_data)

            new_bids_arr = []
            for i in range(0,int(llen_bids / 2)):
                new_bids_arr.append( [bids_data[2*i] , bids_data[2*i+1]] )

            new_asks_arr = []
            for i in range(0,int(llen_asks / 2)):
                new_asks_arr.append( [asks_data[2*i] , asks_data[2*i+1]] )

            sort_bids_data = sorted(new_bids_arr , key=lambda price_pair: price_pair[0] )
            sort_asks_data = sorted(new_asks_arr, key=lambda price_pair: price_pair[0] )

            sort_bids_data.reverse()

            bids = sort_bids_data[:5]
            asks = sort_asks_data[:5]

            try:
                tick.bidPrice1, tick.bidVolume1 = bids[0]
                tick.bidPrice2, tick.bidVolume2 = bids[1]
                tick.bidPrice3, tick.bidVolume3 = bids[2]
                tick.bidPrice4, tick.bidVolume4 = bids[3]
                tick.bidPrice5, tick.bidVolume5 = bids[4]
            except Exception as ex:
                pass

            try:
                tick.askPrice1, tick.askVolume1 = asks[0]
                tick.askPrice2, tick.askVolume2 = asks[1]
                tick.askPrice3, tick.askVolume3 = asks[2]
                tick.askPrice4, tick.askVolume4 = asks[3]
                tick.askPrice5, tick.askVolume5 = asks[4]
            except Exception as ex:
                pass

            tick.datetime = datetime.now()
            tick.date = tick.datetime.strftime("%Y%m%d")
            tick.time = tick.datetime.strftime("%H:%M:%S.%f")

            self.gateway.onTick(tick)

            