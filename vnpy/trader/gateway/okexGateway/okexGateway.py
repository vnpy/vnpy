# encoding: UTF-8

'''
vn.okex的gateway接入

注意：
1. 前仅支持USD  现货交易，以及usd的期货交易
'''

import os
import json
from datetime import datetime
from time import sleep
from copy import copy
from threading import Condition
from Queue import Queue
from threading import Thread
from time import sleep


from vnpy.api.okex import OKEX_Sub_Spot_Api , OKEX_Contract_Api , okex_all_symbol_pairs , okex_all_contract_symbol , okex_all_symbol_type , okex_all_contract_all_symbol_usd , okex_all_contract_type
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

priceContractOffsetTypeMap = {}
priceContractOffsetTypeMap['1'] = (DIRECTION_LONG , OFFSET_OPEN)
priceContractOffsetTypeMap['2'] = (DIRECTION_SHORT , OFFSET_OPEN )
priceContractOffsetTypeMap['3'] = (DIRECTION_SHORT , OFFSET_CLOSE )
priceContractOffsetTypeMap['4'] = (DIRECTION_LONG , OFFSET_CLOSE)
priceContractTypeMapReverse = {v: k for k, v in priceContractOffsetTypeMap.items()} 

# 委托状态印射
statusMap = {}
statusMap[-1] = STATUS_CANCELLED
statusMap[0] = STATUS_NOTTRADED
statusMap[1] = STATUS_PARTTRADED
statusMap[2] = STATUS_ALLTRADED
statusMap[4] = STATUS_UNKNOWN


########################################################################
class okexGateway(VtGateway):
    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='OKEX'):
        """Constructor"""
        super(okexGateway, self).__init__(eventEngine, gatewayName)
        
        self.api_spot = Api_Spot(self)     
        self.api_contract = Api_contract(self)
        
        self.qryEnabled = True

        self.leverage = 0
        self.connected = False

        self.connected_contract = False
        
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
            leverage = setting['leverage']
            to_connect_spot = setting['spot_connect']
            to_connect_future = setting['future_connect']

            self.qryEnabled = setting['qryEnabled']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 初始化接口
        self.leverage = leverage
        
        if to_connect_spot == True:
            self.api_spot.active = True
            self.api_spot.connect_Subpot( apiKey, secretKey, trace)

        if to_connect_future == True:
            self.api_contract.active = True
            self.api_contract.connect_Contract(apiKey , secretKey , trace)
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'接口初始化成功'
        self.onLog(log)
        
        # 启动查询
        self.initQuery()
        # self.startQuery()

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        print "OKEX subscribe! " , subscribeReq.symbol
        """订阅行情"""
        if ':' not in subscribeReq.symbol:
            if self.connected:
                self.api_spot.subscribe(subscribeReq)
            else:
                print "OKEX spot has not been connected!"
        else:
            if self.connected_contract:
                self.api_contract.subscribe(subscribeReq)
            else:
                print "OKEX contract has not been connected!"
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        if ':' not in orderReq.symbol: 
            return self.api_spot.spotSendOrder(orderReq)
        else:
            return self.api_contract.futureSendOrder(orderReq)
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        if self.connected == True:
            self.api_spot.spotCancel(cancelOrderReq)
        if self.connected_contract == True:
            self.api_contract.contractCancel(cancelOrderReq)
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        if self.connected == True:
            self.api_spot.spotUserInfo()
        if self.connected_contract == True:
            self.api_contract.futureUserInfo()

    #----------------------------------------------------------------------
    def qryOrderInfo(self):
        # if self.connected == True:
        #     self.api_spot.spotAllOrders()
        if self.connected_contract == True:
            self.api_contract.futureAllUnfinishedOrderInfo()

    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        pass
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        if self.connected == True:
            self.api_spot.active = False
            self.api_spot.close()

        if self.connected_contract == True:
            self.api_contract.active = False
            self.api_contract.close()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表

            self.qryFunctionList = []
            # self.qryFunctionList = [ self.qryAccount]
            # self.qryFunctionList = [self.qryAccount , self.qryOrderInfo]
            #self.qryFunctionList = []
            
            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 4         # 查询触发点
            self.qryNextFunction = 0    # 上次运行的查询函数索引
            
            self.startQuery()  
    
    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.qryCount += 1
        
        if self.qryCount > self.qryTrigger and len(self.qryFunctionList) > 0:
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
class Api_contract(OKEX_Contract_Api):
    """okex的合约API实现"""
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(Api_contract, self).__init__()

        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.active = False             # 若为True则会在断线后自动重连

        self.cbDict = {}
        self.tickDict = {}
        self.orderDict = {}

        self.channelSymbolMap = {}
        self.localNo = 0                # 本地委托号
        self.localNoQueue = Queue()     # 未收到系统委托号的本地委托号队列
        self.localNoDict = {}           # key为本地委托号，value为系统委托号
        self.orderIdDict = {}           # key为系统委托号，value为本地委托号
        self.cancelDict = {}            # key为本地委托号，value为撤单请求

        self.recordOrderId_BefVolume = {}       # 记录的之前处理的量

        self.cache_some_order = {}      
        self.tradeID = 0

        self.registerSymbolPairArray = set([])

        self._use_leverage = "10"

        self.bids_depth_dict = {}
        self.asks_depth_dict = {}

        self.contract_name_dict = {}

        self.contractIdToSymbol = {}

    #----------------------------------------------------------------------
    def setLeverage(self , __leverage):
        self._use_leverage = __leverage

    #----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """信息推送""" 
        # print evt
        data = self.readData(evt)[0]
        try:
            channel = data['channel']
        except Exception,ex:
            channel = None
        if channel == None:
            return
        
        # try:
        if channel == "addChannel" and 'data' in data:
            channel = data['data']["channel"]

        # DEBUG !!! 
        # if 'depth' not in channel and 'tick' not in channel:
        #     print data

        # print channel , self.cbDict
        if channel != "addChannel" and 'future' in channel and channel != 'login': 
            # print channel
            try:
                callback = self.cbDict[channel]
                callback(data)
            except Exception,ex:
                print ex

    #----------------------------------------------------------------------
    def onError(self, ws, evt):
        """错误推送"""
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        error.errorMsg = str(evt)
        self.gateway.onError(error)

    #----------------------------------------------------------------------
    def onError(self, data):
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        error.errorMsg = str(data["data"]["error_code"])
        self.gateway.onError(error)

    #----------------------------------------------------------------------
    def reconnect(self):
        while not self.gateway.connected_contract:            
            self.writeLog(u'okex Api_contract 等待10秒后重新连接')
            self.connect_Contract(self.apiKey , self.secretKey , self.trace)
            sleep(10)
            if not self.gateway.connected_contract:
                self.reconnect()

    #----------------------------------------------------------------------
    def onClose(self, ws):
        """接口断开"""
        # 如果尚未连上，则忽略该次断开提示
        if not self.gateway.connected_contract:
            return
        
        self.gateway.connected_contract = False
        self.writeLog(u'服务器连接断开')
        
        # 重新连接
        if self.active:
            t = Thread(target=self.reconnect)
            t.start()

    #----------------------------------------------------------------------
    def dealSymbolFunc(self, symbol):
        arr = symbol.split('.')
        symbol_pair = arr[0]
        (symbol, contract_type , leverage) = symbol_pair.split(':')
        symbol = symbol.replace("_usd" , "")

        return  (symbol_pair , symbol, contract_type , leverage)

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        (symbol_pair , symbol, contract_type , leverage) = self.dealSymbolFunc(subscribeReq.symbol)
        
        if symbol_pair not in self.registerSymbolPairArray:
            self.registerSymbolPairArray.add(symbol_pair)
            self.subscribeSingleSymbol( symbol, contract_type , leverage)
            
    #----------------------------------------------------------------------
    def subscribeSingleSymbol(self, symbol , contract_type , leverage):
        # print "subscribeSingleSymbol" , symbol ,  contract_type , leverage
        if symbol in okex_all_contract_symbol:
            self.subsribeFutureTicker(symbol , contract_type)
            self.subscribeFutureDepth(symbol , contract_type)
            self.futureOrderInfo( symbol + "_usd"  , -1 , contract_type , status = "1" , current_page = 1 , page_length = 50)
            #self.subscribeFutureTrades(symbol)

    #----------------------------------------------------------------------
    def contractAllOrders(self):
        for symbol in self.registerSymbolPairArray:
            (symbol_pair , symbol, contract_type , leverage) = self.dealSymbolFunc(symbol)
            self.futureOrderInfo( symbol + "_usd" , -1 , contract_type , status = "1" , current_page = 1 , page_length = 50)

        for orderId in self.orderIdDict.keys():
            order = self.orderDict.get(orderId , None)
            if order != None:
                symbol_pair ,  symbol, contract_type , leverage = self.dealSymbolFunc(order.symbol)
                self.futureOrderInfo(symbol + "_usd" , orderId , contract_type , status = "1" , current_page = 1 , page_length = 50)

    #----------------------------------------------------------------------
    def onOpen(self, ws):       
        """连接成功"""
        self.gateway.connected_contract = True
        self.writeLog(u'服务器OKEX合约连接成功')
        
        self.initCallback()

        for symbol in okex_all_contract_symbol:
            self.channelSymbolMap["ok_sub_futureusd_%s_index" % symbol] = symbol + "_usd:%s:" + self._use_leverage

            for use_contract_type in okex_all_contract_type:
                use_symbol_name = symbol + "_usd:%s:%s" % (use_contract_type , self._use_leverage)  
                #Ticker数据
                self.channelSymbolMap["ok_sub_futureusd_%s_ticker_%s" % (symbol,use_contract_type)] = use_symbol_name
                #盘口的深度
                self.channelSymbolMap["ok_sub_future_%s_depth_%s_usd" % (symbol,use_contract_type)] = use_symbol_name
                #所有人的交易数据
                self.channelSymbolMap["ok_sub_futureusd_%s_trade_%s" % (symbol,use_contract_type)] = use_symbol_name

                contract = VtContractData()
                contract.gatewayName = self.gatewayName
                contract.symbol = use_symbol_name + "." + EXCHANGE_OKEX
                contract.exchange = EXCHANGE_OKEX
                contract.vtSymbol = contract.symbol
                contract.name = u'OKEX期货%s_%s_%s' % (symbol,use_contract_type, self._use_leverage)
                contract.size = 0.00001
                contract.priceTick = 0.00001
                contract.productClass = PRODUCT_FUTURES
                self.gateway.onContract(contract)

                #print contract.vtSymbol , contract.name 

                quanyi_vtSymbol = symbol + "_usd_future_qy." + EXCHANGE_OKEX
                contract = VtContractData()
                contract.gatewayName = self.gatewayName
                contract.symbol = quanyi_vtSymbol
                contract.exchange = EXCHANGE_OKEX
                contract.vtSymbol = contract.symbol
                contract.name = u'OKEX期货权益%s' % (symbol)
                contract.size = 0.00001
                contract.priceTick = 0.00001
                contract.productClass = PRODUCT_FUTURES
                self.gateway.onContract(contract)

        self.login()
        # 连接后查询账户和委托数据
        self.futureUserInfo()
        self.futureAllUnfinishedOrderInfo()
        self.futureAllIndexSymbol()

        # print "test"
        
        self.subscribeSingleSymbol("etc","this_week","10")
        self.subscribeSingleSymbol("eos","this_week","10")
        self.subscribeSingleSymbol("xrp","this_week","10")
        self.subscribeSingleSymbol("btg","this_week","10")

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """快速记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)


    #----------------------------------------------------------------------
    def LoopforceGetContractDict(self, unFishedSet):
        if len(unFishedSet) > 0:
            new_unfishedSet = set([])
            for symbol ,use_contract_type in unFishedSet:
                t_contract_name = self.getContractName( symbol , use_contract_type)
                if t_contract_name != None:
                    self.contract_name_dict[t_contract_name] = {"symbol":symbol,"contract_type":use_contract_type}
                else:
                    new_unfishedSet.add( (symbol , use_contract_type) )

            self.LoopforceGetContractDict(new_unfishedSet)

    #----------------------------------------------------------------------
    def initCallback(self):
        """初始化回调函数"""
        # USD_CONTRACT
        unfinished_contract_set = set([])
        for symbol in okex_all_contract_symbol:
            self.cbDict["ok_sub_futureusd_%s_index" % (symbol)] = self.onFutureIndexInfo
            for use_contract_type in okex_all_contract_type:
                self.cbDict["ok_sub_futureusd_%s_ticker_%s" % (symbol,use_contract_type)] = self.onTicker
                self.cbDict["ok_sub_future_%s_depth_%s_usd" % (symbol,use_contract_type)] = self.onDepth
                self.cbDict["ok_sub_futureusd_%s_trade_%s" % (symbol,use_contract_type)] = self.onTrade

                t_contract_name = self.getContractName( symbol , use_contract_type)
                if t_contract_name != None:
                    self.contract_name_dict[t_contract_name] = {"symbol":symbol,"contract_type":use_contract_type}
                else:
                    unfinished_contract_set.add( (symbol , use_contract_type) )

        self.LoopforceGetContractDict( unfinished_contract_set)

        # print self.contract_name_dict.keys()

        self.cbDict['ok_futureusd_trade'] = self.onFutureOrder
        self.cbDict['ok_futureusd_cancel_order'] = self.onFutureOrderCancel

        self.cbDict['ok_futureusd_userinfo'] = self.onFutureUserInfo 
        self.cbDict['ok_futureusd_orderinfo'] = self.onFutureOrderInfo

        self.cbDict['ok_sub_futureusd_trades'] = self.onFutureSubTrades
        self.cbDict['ok_sub_futureusd_userinfo'] = self.onFutureSubUserinfo

        self.cbDict['ok_sub_futureusd_positions'] = self.onFutureSubPositions
    
    '''
    推送 币币交易指数过去
    '''
    #----------------------------------------------------------------------
    def onFutureIndexInfo(self, data):
        if 'data' not in data:
            return
        channel = data['channel']
        if channel == 'addChannel':
            return
        try:
            rawData = data["data"]
            t_date ,t_time = self.generateDateTime(float(rawData["timestamp"]))
            float_index = float(rawData["futureIndex"])

            symbol_pattern = self.channelSymbolMap[channel]
            for use_contract_type in okex_all_contract_type:
                symbol = symbol_pattern % (use_contract_type)

                push_dic = {"symbol":symbol , "date":t_date , "time":t_time , "index":float_index}
                self.gateway.onFutureIndexPush(push_dic)

        except Exception , ex:
            print "onFutureIndexInfo" , ex
    '''
    [
        {
            "data": {
                "limitHigh": "1030.3",
                "vol": 276406,
                "last": 998.05,
                "sell": 998.05,
                "buy": 997.61,
                "unitAmount": 100,
                "hold_amount": 180178,
                "contractId": 20170324034,
                "high": 1049.18,
                "low": 973.15,
                "limitLow": "968.1"
            },
            "channel": "ok_sub_futureusd_btc_ticker_this_week"
        }
    ]
    '''
    #----------------------------------------------------------------------
    def onTicker(self, data):
        """"""
        if 'data' not in data:
            return

        channel = data['channel']
        if channel == 'addChannel':
            return

        # print "ticker"
        # print data
        try:
            symbol = self.channelSymbolMap[channel]
            # (no_usd_symbol , use_contract_type) = self.cbReverseDict[channel]
            # symbol = no_usd_symbol + "_usd:" + use_contract_type + ":" + self._use_leverage
            if symbol not in self.tickDict:
                tick = VtTickData()
                tick.exchange = EXCHANGE_OKEX
                tick.symbol = '.'.join([ symbol , tick.exchange])
                tick.vtSymbol = tick.symbol

                tick.gatewayName = self.gatewayName
                self.tickDict[symbol] = tick

                self.bids_depth_dict[symbol] = {} 
                self.asks_depth_dict[symbol] = {}
            else:
                tick = self.tickDict[symbol]

                tick_bids_depth = self.bids_depth_dict[symbol]
                tick_asks_depth = self.asks_depth_dict[symbol]
            
            rawData = data['data']
            tick.highPrice = float(rawData['high'])
            tick.lowPrice = float(rawData['low'])
            tick.lastPrice = float(rawData['last'])
            tick.volume = float(str(rawData['vol']).replace(',', ''))

            self.contractIdToSymbol[str(rawData["contractId"])] = tick.symbol
            # tick.date, tick.time = self.generateDateTime(rawData['timestamp'])

            # newtick = copy(tick)
            # self.gateway.onTick(newtick)
        except Exception,ex:
            print "onTicker" , ex
            #print "Error in onTicker " , channel
    
    '''
    [
        {
            "data": {
                "timestamp": 1490337551299,
                "asks": [
                    [
                        "996.72",
                        "20.0",
                        "2.0065",
                        "85.654",
                        "852.0"
                    ]
                ],
                "bids": [
                    [
                        "991.67",
                        "6.0",
                        "0.605",
                        "0.605",
                        "6.0"
                    ]
            },
            "channel": "ok_sub_futureusd_btc_depth_this_week"
        }
    ]
    timestamp(long): 服务器时间戳
    asks(array):卖单深度 数组索引(string) 0 价格, 1 量(张), 2 量(币) 3, 累计量(币) 4,累积量(张)
    bids(array):买单深度 数组索引(string) 0 价格, 1 量(张), 2 量(币) 3, 累计量(币) 4,累积量(张)
    使用描述:
        1，第一次返回全量数据
        2，根据接下来数据对第一次返回数据进行，如下操作
        删除（量为0时）
        修改（价格相同量不同）
        增加（价格不存在）
    {u'binary': 0, u'data': {u'timestamp': 1515745170254L, u'bids': [[33.824, 6, 1.7
738, 1.7738, 6], [33.781, 6, 1.7761, 7.6905, 26], [33.775, 6, 1.7764, 9.4669, 32
], [33.741, 0, 11.2622, 20.1331, 68], [33.692, 6, 1.7808, 991.3629, 3341], [33.6
35, 7, 2.0811, 1213.9536, 4090], [33.633, 0, 2.3786, 1223.1365, 4121], [33.629,
0, 1.1894, 1224.3259, 4125], [33.62, 14, 4.1641, 1218.1177, 4104], [33.617, 0, 1
.4873, 1225.8132, 4130], [33.614, 7, 2.0824, 1221.6875, 4116], [33.601, 0, 1.785
6, 1344.853, 4530], [33.591, 4, 1.1907, 1343.4074, 4525], [33.581, 16, 4.7645, 1
351.7451, 4553], [33.579, 6, 1.7868, 1353.5319, 4559], [33.552, 6, 1.7882, 1360.
0871, 4581], [33.543, 0, 1.4906, 1386.5663, 4670], [33.54, 136, 40.5485, 1423.88
44, 4795], [33.539, 9, 2.6834, 1426.5678, 4804], [33.53, 50, 14.912, 1441.4798,
4854], [33.525, 5, 1.4914, 1442.9712, 4859], [33.522, 5, 1.4915, 1444.4627, 4864
], [33.511, 10, 2.984, 1448.6402, 4878], [33.502, 0, 2.6864, 1409.2357, 4746], [
33.479, 4, 1.1947, 2353.4177, 7909], [25.245, 0, 9.9029, 21190.5178, 68253], [25
.235, 0, 10.3031, 21200.8209, 68279], [25.225, 0, 4.3607, 21205.1816, 68290], [2
5.215, 0, 3.9658, 21209.1474, 68300], [25.205, 0, 3.9674, 21213.1148, 68310]], u
'asks': [[43.493, 0, 3.2189, 21250.6634, 74286], [43.473, 0, 4.8305, 21247.4445,
 74272], [43.463, 0, 5.5219, 21242.614, 74251], [43.453, 0, 5.5232, 21237.0921,
74227], [43.433, 0, 3.6838, 21231.5689, 74203], [34.238, 500, 146.0365, 5495.506
5, 18746], [34.18, 5, 1.4628, 3523.3267, 12000], [34.159, 6, 1.7564, 3521.8639,
11995], [34.137, 5, 1.4646, 3020.1076, 10282], [34.107, 6, 1.7591, 2013.2213, 68
46], [34.105, 4, 1.1728, 2011.4622, 6840], [34.09, 4, 1.1733, 1345.1823, 4568],
[34.072, 500, 146.748, 1324.3485, 4497], [34.07, 6, 1.761, 1177.6005, 3997], [34
.068, 683, 200.4813, 1175.8395, 3991], [34.063, 0, 1.1742, 944.5044, 3203], [34.
039, 15, 4.4067, 975.3582, 3308], [34.025, 0, 1.4695, 943.3302, 3199], [34.024,
7, 2.0573, 970.9515, 3293], [34.014, 0, 1.4699, 941.8607, 3194], [33.992, 5, 1.4
709, 815.0705, 2763], [33.977, 0, 1.4715, 784.8013, 2660], [33.976, 0, 1.4716, 7
83.3298, 2655], [33.971, 0, 2.3549, 781.8582, 2650], [33.968, 0, 2.0607, 779.503
3, 2642], [33.965, 0, 1.1776, 777.4426, 2635], [33.96, 0, 2.0612, 776.265, 2631]
, [33.953, 200, 58.9049, 811.8338, 2752], [33.909, 13, 3.8337, 294.4836, 997], [
33.908, 0, 7.0779, 315.7585, 1069], [33.905, 27, 7.9634, 286.5209, 970], [33.899
, 8, 2.3599, 261.4503, 885], [33.895, 9, 2.6552, 259.0904, 877], [33.894, 0, 4.4
255, 273.2863, 925], [33.893, 13, 3.8356, 256.4352, 868], [33.891, 0, 4.1308, 26
8.8608, 910], [33.884, 6, 1.7707, 252.5996, 855], [33.878, 13, 3.8372, 250.8289,
 849], [33.825, 0, 17.7383, 17.7383, 60]]}, u'channel': u'ok_sub_future_etc_dept
h_this_week_usd'}
    '''
    #----------------------------------------------------------------------
    def onDepth(self, data):
        """"""
        if 'data' not in data:
            return
        try:
            channel = data['channel']
            symbol = self.channelSymbolMap[channel]
        except Exception,ex:
            symbol = None

        if symbol == None:
            return

        # print "onDepth"
        # print data
        try:
            if 'data' not in data:
                return
            # (no_usd_symbol , use_contract_type) = self.cbReverseDict[channel]
            # symbol = no_usd_symbol + "_usd:" + use_contract_type + ":" + self._use_leverage
            if symbol not in self.tickDict:
                tick = VtTickData()
                tick.symbol = symbol
                tick.vtSymbol = symbol
                tick.gatewayName = self.gatewayName
                self.tickDict[symbol] = tick

                self.bids_depth_dict[symbol] = {} 
                self.asks_depth_dict[symbol] = {}
            else:
                tick = self.tickDict[symbol]

                tick_bids_depth = self.bids_depth_dict[symbol]
                tick_asks_depth = self.asks_depth_dict[symbol]
            

            rawData = data['data']
            try:
                for inf in rawData["bids"]:
                    price1, vol1 , vol2 , acc_vol1 , acc_vol2 = inf

                    #self.bids_depth_dict[price1] = float(vol1)
                    tick_bids_depth[price1] = float(vol1)

                    if abs(float(vol1)) < 0.00001:
                        #del self.bids_depth_dict[price1]
                        del tick_bids_depth[price1]

                #arr = sorted(self.bids_depth_dict.items(), lambda x, y: cmp(x[0], y[0]))
                arr = sorted(tick_bids_depth.items(), lambda x, y: cmp(x[0], y[0]))

                tick.bidPrice1, tick.bidVolume1  = arr[-1]
                tick.bidPrice2, tick.bidVolume2  = arr[-2]
                tick.bidPrice3, tick.bidVolume3  = arr[-3]
                tick.bidPrice4, tick.bidVolume4  = arr[-4]
                tick.bidPrice5, tick.bidVolume5  = arr[-5]
            except Exception,ex:
                print ex
                # print "!!! contract onDepth bids rawData[]:" , tick.symbol , ex
                # print rawData

            try:
                for inf in rawData["asks"]:
                    price1, vol1 , vol2 , acc_vol1 , acc_vol2 = inf
                    #self.asks_depth_dict[price1] = float(vol1)
                    tick_asks_depth[price1] = float(vol1)

                    if abs(float(vol1)) < 0.00001:
                        #del self.asks_depth_dict[price1]
                        del tick_asks_depth[price1]

                #arr = sorted(self.asks_depth_dict.items(), lambda x, y: cmp(x[0], y[0]))
                arr = sorted(tick_asks_depth.items(), lambda x, y: cmp(x[0], y[0]))

                tick.askPrice1, tick.askVolume1  = arr[0]
                tick.askPrice2, tick.askVolume2  = arr[1]
                tick.askPrice3, tick.askVolume3  = arr[2]
                tick.askPrice4, tick.askVolume4  = arr[3]
                tick.askPrice5, tick.askVolume5  = arr[4]     
            
            except Exception,ex:
                print ex
                # print "~~~ contract onDepth asks rawData[]:" , tick.symbol , ex
                # print rawData

            tick.date, tick.time = self.generateDateTime(rawData['timestamp'])
            # print "Depth", tick.date , tick.time
            
            newtick = copy(tick)
            self.gateway.onTick(newtick)
        except Exception,ex:
            print "onDepth" , ex

    #----------------------------------------------------------------------
    def onTrade(self, data):
        pass
        # if 'data' not in data:
        #     return
        # try:
        #     channel = data['channel']
        #     symbol = self.channelSymbolMap[channel]
        # except Exception,ex:
        #     symbol = None

        # if symbol == None:
        #     return

    '''
    [
        {
            "data":{
                "result":true,
                "order_id":5017287829
            },
            "channel":"ok_futureusd_trade"
        }
    ]

    real data
    {u'binary': 0, u'data': {u'order_id': 230874269033472L, u'result': True}, u'channel': u'ok_futureusd_trade'}
    '''
    #----------------------------------------------------------------------
    def onFutureOrder(self, data):
        """委托信息查询回调"""
        try:
            rawData = data['data']
            if 'error_code' in rawData.keys():
                print data
                return

            orderId = str(rawData['order_id'])
            
            # 尽管websocket接口的委托号返回是异步的，但经过测试是
            # 符合先发现回的规律，因此这里通过queue获取之前发送的
            # 本地委托号，并把它和推送的系统委托号进行映射

            # localNo = self.orderIdDict.get(orderId , None)
            # if localNo == None:
            
            localNo = self.localNoQueue.get_nowait()
            
            print "localNo:", localNo , "orderId" , orderId
            self.localNoDict[localNo] = orderId
            self.orderIdDict[orderId] = localNo

            # print orderId , self.cache_some_order
            if orderId in self.cache_some_order.keys():
                arr = self.cache_some_order[orderId]
                for d in arr:
                    # print "self.onFutureSubTrades" 
                    # print d
                    # print self.onFutureSubTrades(d)
                    self.onFutureSubTrades(d)

                # 处理完就删除掉这里
                del self.cache_some_order[orderId]
            
            # 检查是否有系统委托号返回前就发出的撤单请求，若有则进
            # 行撤单操作
            if localNo in self.cancelDict:
                req = self.cancelDict[localNo]
                self.spotCancel(req)
                del self.cancelDict[localNo]
        except Exception,ex:
            print "onFutureOrder", ex
    '''
    [
        {
            "data":{
                "result":true,
                "order_id":"5017402127"
            },
            "channel":"ok_futureusd_cancel_order"
        }
    ]
    '''
    #----------------------------------------------------------------------
    def onFutureOrderCancel(self , data):
        """委托信息查询回调"""
        if 'data' not in data:
            return

        if 'error' in data["data"].keys():
            self.onError(data)
            return

        rawData = data['data']
        orderId = str(rawData['order_id'])

        localNo = self.orderIdDict[orderId]
        order = self.orderDict[orderId]

        order.status = STATUS_CANCELLED
        self.gateway.onOrder(order)

        del self.orderDict[orderId]
        del self.orderIdDict[orderId]
        del self.localNoDict[localNo]

        if orderId in self.cache_some_order.keys():
            del self.cache_some_order[orderId]

    '''
    逐仓返回：
    [{
        "channel": "ok_futureusd_userinfo",
        "data": {
            "info": {
                "btc": {
                    "balance": 0.00000673,
                    "contracts": [{
                        "available": 0.00000673,
                        "balance": 0,
                        "bond": 0,
                        "contract_id": 20150327013,
                        "contract_type": "quarter",
                        "freeze": 0,
                        "profit": 0,
                        "unprofit": 0
                    }],
                    "rights": 0.00000673
                },
                "ltc": {
                    "balance": 0.00007773,
                    "contracts": [{
                        "available": 16.5915,
                        "balance": 0,
                        "bond": 0.70871722,
                        "contract_type": "this_week",
                        "contractid": 20150130115,
                        "freeze": 0,
                        "profit": 17.30020414,
                        "unprofit": -1.8707
                    }, {
                        "available": 0.00007773,
                        "balance": 0.03188496,
                        "bond": 0,
                        "contract_type": "quarter",
                        "contractid": 20150327116,
                        "freeze": 0,
                        "profit": -0.03188496,
                        "unprofit": 0
                    }],
                    "rights": 0.00007773
                }
            },
            "result": true
        }
    }]
    balance(double): 账户余额
    symbol(string)：币种
    keep_deposit(double)：保证金
    profit_real(double)：已实现盈亏
    unit_amount(int)：合约价值
    逐仓信息
    balance(double):账户余额
    available(double):合约可用
    balance(double):合约余额
    bond(double):固定保证金
    contract_id(long):合约ID
    contract_type(string):合约类别
    freeze(double):冻结
    profit(double):已实现盈亏
    unprofit(double):未实现盈亏
    rights(double):账户权益
    全仓返回：
    [{
        "channel": "ok_futureusd_userinfo",
        "data": {
            "info": {
                "btc": {
                    "account_rights": 1,
                    "keep_deposit": 0,
                    "profit_real": 3.33,
                    "profit_unreal": 0,
                    "risk_rate": 10000
                },
                "ltc": {
                    "account_rights": 2,
                    "keep_deposit": 2.22,
                    "profit_real": 3.33,
                    "profit_unreal": 2,
                    "risk_rate": 10000
                }
            },
            "result": true
        }
    }]

    实际日志
    {u'binary': 0, u'data': {u'info': {u'ltc': {u'contracts': [], u'balance': 0, u'rights': 0}, u'bch':
{u'contracts': [], u'balance': 0, u'rights': 0}, u'eos': {u'contracts': [], u'balance': 0, u'rights'
: 0}, u'etc': {u'contracts': [], u'balance': 4.98, u'rights': 4.98}, u'btg': {u'contracts': [], u'ba
lance': 0, u'rights': 0}, u'btc': {u'contracts': [], u'balance': 0, u'rights': 0}, u'eth': {u'contra
cts': [], u'balance': 0, u'rights': 0}, u'xrp': {u'contracts': [], u'balance': 0, u'rights': 0}}, u'
result': True}, u'channel': u'ok_futureusd_userinfo'}

{u'contracts': [], u'balance': 0, u'rights': 0}, u'eos': {u'contracts': [], u'balance': 0, u'rights'
: 0}, u'etc': {u'contracts': [{u'available': 4.92279753, u'contract_id': 201802160040063L, u'profit'
: -0.01702246, u'unprofit': 0.0005, u'freeze': 0, u'contract_type': u'this_week', u'balance': 0.0572
0247, u'bond': 0.04018001}], u'balance': 4.92279753, u'rights': 4.96357399}, u'btg': {u'contracts':
[], u'balance': 0, u'rights': 0}, u'btc': {u'contracts': [], u'balance': 0, u'rights': 0}, u'eth': {
u'contracts': [], u'balance': 0, u'rights': 0}, u'xrp': {u'contracts': [], u'balance': 0, u'rights':
 0}}, u'result': True}, u'channel': u'ok_futureusd_userinfo'}


 u'etc': {u'contracts': [{u'available': 4.92279753, u'contract_id': 201802160040063L, u'profit'
: -0.01702246, u'unprofit': 0.0005, u'freeze': 0, u'contract_type': u'this_week', u'balance': 0.0572
0247, u'bond': 0.04018001}]
    '''
    #----------------------------------------------------------------------
    def onFutureUserInfo(self, data):
        try:
            rawData = data['data']
            info = rawData["info"]
            for symbol in info.keys():
                u_inf = info[symbol]
                if "account_rights" in u_inf.keys():
                    # 说明是 全仓返回
                    pass
                    # account = VtAccountData()
                    # account.gatewayName = self.gatewayName
                    # account.accountID = self.gatewayName
                    # account.vtAccountID = account.accountID
                    # account.balance = float(u_inf["account_rights"])
                    # self.gateway.onAccount(account)   
                else:
                    # 说明是逐仓返回
                    t_contracts = u_inf["contracts"]
                    t_balance = float(u_inf["balance"])
                    t_rights = float(u_inf["rights"])

                    ##  下面这段 好像用不到
                    # for one_contract in t_contracts:
                    #     pos = VtPositionData()
                    #     pos.gatewayName = self.gatewayName
                    #     pos.symbol = symbol + "_usd:%s:%s.%s" % ( one_contract["contract_type"], self._use_leverage,EXCHANGE_OKEX)
                    #     pos.vtSymbol = pos.symbol
                    #     pos.direction = DIRECTION_NET
                    #     pos.frozen = float(one_contract["freeze"])
                    #     pos.position = pos.frozen + float(one_contract["balance"])
                        
                    #     self.gateway.onPosition(pos)

                    if t_balance > 0 or t_rights > 0:

                        account = VtAccountData()
                        account.gatewayName = self.gatewayName
                        account.accountID = symbol + "_usd_future_qy." + EXCHANGE_OKEX
                        account.vtAccountID = account.accountID 
                        account.balance = t_rights
                        self.gateway.onAccount(account)  

                        # pos = VtPositionData()
                        # pos.gatewayName = self.gatewayName
                        # pos.symbol = symbol + "_usd_future_qy." + EXCHANGE_OKEX 
                        # pos.vtSymbol = pos.symbol
                        # pos.direction = DIRECTION_NET
                        # pos.frozen = t_rights - t_balance
                        # pos.position = t_rights

                        # self.gateway.onPosition(pos)

        except Exception,ex:
            print ex


    '''
    [
        {
            "data":{
                "result":true,
                "orders":[
                    {
                        "fee":0,
                        "amount":1,
                        "price":2,
                        "contract_name":"LTC0331",
                        "symbol":"ltc_usd",
                        "create_date":1490347972000,
                        "status":-1,
                        "lever_rate":10,
                        "deal_amount":0,
                        "price_avg":0,
                        "type":1,
                        "order_id":5017402127,
                        "unit_amount":10
                    }
                ]
            },
            "channel":"ok_futureusd_orderinfo"
        }
    ]
    '''
    #----------------------------------------------------------------------
    def onFutureOrderInfo(self, data):
        """委托信息查询回调"""
        if "error_code" in data.keys():
            print data
            return 
        try:
            rawData = data["data"]

            for d in rawData['orders']:
                self.localNo += 1
                localNo = str(self.localNo)
                orderId = str(d['order_id'])
                
                self.localNoDict[localNo] = orderId
                self.orderIdDict[orderId] = localNo
                
                if orderId not in self.orderDict:
                    order = VtOrderData()
                    order.gatewayName = self.gatewayName
                    contract_name = d["contract_name"]
                    dic_info = self.contract_name_dict[contract_name]

                    use_contract_type = dic_info["contract_type"]

                    order.symbol = '.'.join([d["symbol"] + ":" + use_contract_type + ":" + str(self._use_leverage) , EXCHANGE_OKEX])
                    
                    order.vtSymbol = order.symbol
        
                    order.orderID = localNo

                    order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
                    
                    order.price = d['price']
                    order.totalVolume = d['amount']
                    order.direction, offset = priceContractOffsetTypeMap[str(d['type'])]
                    
                    self.orderDict[orderId] = order

                else:
                    order = self.orderDict[orderId]
                
                order.tradedVolume = d['deal_amount']
                order.status = statusMap[int(d['status'])]            
                self.gateway.onOrder(copy(order))

        except Exception,ex:
            print ex
    
    '''
    [{
            "data":{
                amount:1
                contract_id:20170331115,
                contract_name:"LTC0331",
                contract_type:"this_week",
                create_date:1490583736324,
                create_date_str:"2017-03-27 11:02:16",
                deal_amount:0,
                fee:0,
                lever_rate:20,
                orderid:5058491146,
                price:0.145,
                price_avg:0,
                status:0,
                system_type:0,
                type:1,
                unit_amount:10,
                user_id:101
            },
            "channel":"ok_sub_futureusd_trades"
        }
    ]
实际数据
    ok_sub_futureusd_trades
{u'binary': 0, u'data': {u'orderid': 230874269033472L, u'contract_name': u'ETC0216', u'fee': 0.0, u'
user_id': 6548935, u'contract_id': 201802160040063L, u'price': 24.555, u'create_date_str': u'2018-02
-10 18:34:21', u'amount': 1.0, u'status': 0, u'system_type': 0, u'unit_amount': 10.0, u'price_avg':
0.0, u'contract_type': u'this_week', u'create_date': 1518258861775L, u'lever_rate': 10.0, u'type': 1
, u'deal_amount': 0.0}, u'channel': u'ok_sub_futureusd_trades'}
ok_sub_futureusd_trades
{u'binary': 0, u'data': {u'orderid': 230874269033472L, u'contract_name': u'ETC0216', u'fee': 0.0, u'
user_id': 6548935, u'contract_id': 201802160040063L, u'price': 24.555, u'create_date_str': u'2018-02
-10 18:34:21', u'amount': 1.0, u'status': 0, u'system_type': 0, u'unit_amount': 10.0, u'price_avg':
0.0, u'contract_type': u'this_week', u'create_date': 1518258861775L, u'lever_rate': 10.0, u'type': 1
, u'deal_amount': 0.0}, u'channel': u'ok_sub_futureusd_trades'}
    '''
    #----------------------------------------------------------------------
    def onFutureSubTrades(self, data):
        """发单"""
        try:
            if "error_code" in data.keys():
                print data
                return 
            rawData = data["data"]
            orderId = str(rawData["orderid"])
            use_contract_type = rawData["contract_type"]

            localNo = self.orderIdDict.get(orderId , None)

            if localNo == None:
                arr = self.cache_some_order.get(orderId , None)
                if arr == None:
                    arr = []
                    arr.append( data)
                    self.cache_some_order[orderId] = arr
                else:
                    arr.append( data)
                return 

            # 委托信息
            if orderId not in self.orderDict:
                order = VtOrderData()
                order.gatewayName = self.gatewayName

                symbol = (self.contract_name_dict[ rawData["contract_name"] ])["symbol"] + "_usd"
                
                order.symbol = '.'.join([ symbol + ":" + use_contract_type + ":" + str(self._use_leverage) , EXCHANGE_OKEX])
                #order.symbol = spotSymbolMap[rawData['symbol']]
                order.vtSymbol = order.symbol
        
                order.orderID = localNo
                order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
                
                order.price = float(rawData['price'])
                order.totalVolume = float(rawData['amount'])

                order.direction, order.offset = priceContractOffsetTypeMap[str(rawData['type'])]
                
                self.orderDict[orderId] = order
            else:
                order = self.orderDict[orderId]
                
            order.tradedVolume = float(rawData['deal_amount'])
            order.status = statusMap[rawData['status']]
            
            self.gateway.onOrder(copy(order))

            bef_volume = self.recordOrderId_BefVolume.get( orderId , 0.0 )
            now_volume = float(rawData['deal_amount']) - bef_volume

            self.recordOrderId_BefVolume[orderId] = float(rawData['deal_amount'])

            if now_volume > 0.000001:
                trade = VtTradeData()
                trade.gatewayName = self.gatewayName
 
                trade.symbol = order.symbol
                trade.vtSymbol = order.symbol            
                
                self.tradeID += 1
                trade.tradeID = str(self.tradeID)
                trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
                
                trade.orderID = localNo
                trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
                
                trade.price = float(rawData['price'])
                trade.volume = float(now_volume)
                
                trade.direction, trade.offset = priceContractOffsetTypeMap[str(rawData['type'])] 
                
                trade.tradeTime =  (rawData["create_date_str"].split(' '))[1]     #u'2018-02-10 18:34:21
                #tmp_date, tmp_time = self.generateDateTime(float(rawData["create_date"]))  # 1518258861775L
                #trade.tradeTime = str(tmp_time)
                
                self.gateway.onTrade(trade)
        except Exception,ex:
            print "onFutureSubTrades" , ex

    '''
    # Response
逐仓信息
 [{
        "data":{
            "balance":10.16491751,
            "symbol":"ltc_usd",
            "contracts":[
                {
                    "bond":0.50922987,
                    "balance":0.50922987,
                    "profit":0,
                    "freeze":1.72413792,
                    "contract_id":20170331115,
                    "available":6.51526374
                },
                {
                    "bond":0,
                    "balance":0,
                    "profit":0,
                    "freeze":1.64942529,
                    "contract_id":20170407135,
                    "available":6.51526374
                },
                {
                    "bond":0,
                    "balance":0,
                    "profit":0,
                    "freeze":0.27609056,
                    "contract_id":20170630116,
                    "available":6.51526374
                }
            ]
        },
        "channel":"ok_sub_futureusd_userinfo"
    }]
全仓信息
[{
    "data":{
        "balance":0.2567337,
        "symbol":"btc_usd",
        "keep_deposit":0.0025,
        "profit_real":-0.00139596,
        "unit_amount":100
    },
    "channel":"ok_sub_futureusd_userinfo"
}]

信息
{u'binary': 0, u'data': {u'contracts': [{u'available': 4.96199982, u'contract_id': 201802160040063L,
 u'profit': -0.01800018, u'freeze': 0.0, u'balance': 0.01800018, u'bond': 0.0}], u'symbol': u'etc_us
d', u'balance': 4.96199982}, u'channel': u'ok_sub_futureusd_userinfo'}
    '''
    #----------------------------------------------------------------------
    def onFutureSubUserinfo(self, data):
        u_inf = data['data']
        if "account_rights" in u_inf.keys():
            # 说明是 全仓返回
            pass
            # account = VtAccountData()
            # account.gatewayName = self.gatewayName
            # account.accountID = self.gatewayName
            # account.vtAccountID = account.accountID
            # account.balance = float(u_inf["account_rights"])
            # self.gateway.onAccount(account)   
        else:
            pass
            # 感觉这里不是很有用。。。  遂放弃

            # 说明是逐仓返回

            # t_contracts = u_inf["contracts"]
            # t_symbol = u_inf["symbol"].replace('_usd',"")
            # for one_contract in t_contracts:
            #     account = VtAccountData()
                # account.gatewayName = self.gatewayName
                # account.accountID = self.gatewayName

                # pos = VtPositionData()
                # pos.gatewayName = self.gatewayName
                # #pos.symbol = t_symbol + "_usd:%s:%s.%s" % ( one_contract["contract_type"], self._use_leverage,EXCHANGE_OKEX)
                # pos.symbol = self.contractIdToSymbol[one_contract["contract_id"]]
                # pos.vtSymbol = pos.symbol
                # pos.direction = DIRECTION_NET
                # pos.frozen = float(one_contract["freeze"])
                # pos.position = pos.frozen + float(one_contract["balance"])
                
                # self.gateway.onPosition(pos)

    '''
    [{
        "data":{
            "positions":[
                {
                    "position":"1",
                    "contract_name":"BTC0630",
                    "costprice":"994.89453079",
                    "bondfreez":"0.0025",
                    "avgprice":"994.89453079",
                    "contract_id":20170630013,
                    "position_id":27782857,
                    "eveningup":"0",
                    "hold_amount":"0",
                    "margin":0,
                    "realized":0
                },
                {
                    "position":"2",
                    "contract_name":"BTC0630",
                    "costprice":"1073.56",
                    "bondfreez":"0.0025",
                    "avgprice":"1073.56",
                    "contract_id":20170630013,
                    "position_id":27782857,
                    "eveningup":"0",
                    "hold_amount":"0",
                    "margin":0,
                    "realized":0
                }
            ],
            "symbol":"btc_usd",
            "user_id":101
        },
        "channel":"ok_sub_futureusd_positions"
}]
逐仓返回
[{
    "data":{
        "positions":[
            {
                "position":"1",
                "profitreal":"0.0",
                "contract_name":"LTC0407",
                "costprice":"0.0",
                "bondfreez":"1.64942529",
                "forcedprice":"0.0",
                "avgprice":"0.0",
                "lever_rate":10,
                "fixmargin":0,
                "contract_id":20170407135,
                "balance":"0.0",
                "position_id":27864057,
                "eveningup":"0.0",
                "hold_amount":"0.0"
            },
            {
                "position":"2",
                "profitreal":"0.0",
                "contract_name":"LTC0407",
                "costprice":"0.0",
                "bondfreez":"1.64942529",
                "forcedprice":"0.0",
                "avgprice":"0.0",
                "lever_rate":10,
                "fixmargin":0,
                "contract_id":20170407135,
                "balance":"0.0",
                "position_id":27864057,
                "eveningup":"0.0",
                "hold_amount":"0.0"
            }
        "symbol":"ltc_usd",
        "user_id":101
    }]

实际返回的数据

{u'binary': 0, u'data': {u'positions': [{u'contract_name': u'ETC0216', u'balance': 0.01606774, u'con
tract_id': 201802160040063L, u'fixmargin': 0.0, u'position_id': 73790127, u'avgprice': 24.46, u'even
ingup': 0.0, u'profitreal': -0.01606774, u'hold_amount': 0.0, u'costprice': 24.46, u'position': 1, u
'lever_rate': 10, u'bondfreez': 0.04085301, u'forcedprice': 0.0}, {u'contract_name': u'ETC0216', u'b
alance': 0.01606774, u'contract_id': 201802160040063L, u'fixmargin': 0.0, u'position_id': 73790127,
u'avgprice': 0.0, u'eveningup': 0.0, u'profitreal': -0.01606774, u'hold_amount': 0.0, u'costprice':
0.0, u'position': 2, u'lever_rate': 10, u'bondfreez': 0.04085301, u'forcedprice': 0.0}, {u'contract_
name': u'ETC0216', u'balance': 0.01606774, u'contract_id': 201802160040063L, u'fixmargin': 0.0, u'po
sition_id': 73790127, u'avgprice': 0.0, u'eveningup': 0.0, u'profitreal': -0.01606774, u'hold_amount
': 0.0, u'costprice': 0.0, u'position': 1, u'lever_rate': 20, u'bondfreez': 0.04085301, u'forcedpric
e': 0.0}, {u'contract_name': u'ETC0216', u'balance': 0.01606774, u'contract_id': 201802160040063L, u
'fixmargin': 0.0, u'position_id': 73790127, u'avgprice': 0.0, u'eveningup': 0.0, u'profitreal': -0.0
1606774, u'hold_amount': 0.0, u'costprice': 0.0, u'position': 2, u'lever_rate': 20, u'bondfreez': 0.
04085301, u'forcedprice': 0.0}], u'symbol': u'etc_usd', u'user_id': 6548935}, u'channel': u'ok_sub_f
utureusd_positions'}
    '''
    #----------------------------------------------------------------------
    def onFutureSubPositions(self, data):
        """发单"""
        # 这个逐仓才是实际的仓位 ！！
        try:
            rawData = data["data"]
            symbol = rawData["symbol"]
            positions = rawData["positions"]
            for inf in positions:
                if 'fixmargin' in inf.keys():
                    contract_name = inf["contract_name"]
                    position_leverage = str(inf["lever_rate"])

                    # print contract_name , position_leverage , self._use_leverage
                    if int(position_leverage) == int(self._use_leverage):
                        dic_inf = self.contract_name_dict[contract_name]
                        use_contract_type = dic_inf["contract_type"]

                        # print dic_inf
                        pos = VtPositionData()
                        pos.gatewayName = self.gatewayName

                        if int(inf["position"]) == 1:
                            pos.direction = DIRECTION_LONG
                        else:
                            pos.direction = DIRECTION_SHORT

                        pos.symbol = symbol + ":" + use_contract_type + ":" + position_leverage + "." + EXCHANGE_OKEX
                        pos.vtSymbol = pos.symbol
                        pos.vtPositionName = pos.symbol + "." + pos.direction
                        
                        pos.frozen = float(inf["hold_amount"])-float(inf['eveningup'])
                        pos.position = float(inf["hold_amount"]) 
                        pos.positionProfit = float(inf["profitreal"])

                        # print inf , pos.symbol 
                        self.gateway.onPosition(pos)
                else:
                    print "!!!!!  amazing " , data
        except Exception , ex:
            print "Error in onFutureSubPositions" , ex

        # rawData = data["data"]
        # symbol = rawData["symbol"]
        # positions = rawData["positions"]
        # for inf in positions:
        #     if 'margin' in inf.keys():
        #         contract_name = inf["contract_name"]
        #         dic_inf = self.contract_name_dict[contract_name]
        #         use_contract_type = dic_inf["contract_type"]

        #         pos = VtPositionData()
        #         pos.gatewayName = self.gatewayName
        #         pos.symbol = symbol + ":" + use_contract_type + ":" + self._use_leverage + "." + EXCHANGE_OKEX
        #         pos.vtSymbol = pos.symbol
        #         if int(inf["position"]) == 1:
        #             pos.direction = DIRECTION_LONG
        #         else:
        #             pos.direction = DIRECTION_SHORT
        #         pos.frozen = float(inf['bondfreez'])
        #         pos.position = float(inf["margin"])
        #         self.gateway.onPosition(pos)
        #     else:
        #         contract_name = inf["contract_name"]
        #         dic_inf = self.contract_name_dict[contract_name]
        #         use_contract_type = dic_inf["contract_type"]

        #         pos = VtPositionData()
        #         pos.gatewayName = self.gatewayName
        #         pos.symbol = symbol + ":" + use_contract_type + ":" + self._use_leverage + "." + EXCHANGE_OKEX
        #         pos.vtSymbol = pos.symbol
        #         if int(inf["position"]) == 1:
        #             pos.direction = DIRECTION_LONG
        #         else:
        #             pos.direction = DIRECTION_SHORT
        #         pos.frozen = float(inf['bondfreez'])
        #         pos.position = float(inf["balance"])
        #         self.gateway.onPosition(pos)
    
    #----------------------------------------------------------------------
    def futureSendOrder(self, req):
        """发单"""
        symbol_pair ,  symbol, contract_type , leverage = self.dealSymbolFunc(req.symbol)

        # print symbol_pair ,  symbol, contract_type , leverage 
        type_ = priceContractTypeMapReverse[(req.direction, req.offset)]

        # print symbol + "_usd", contract_type , type_ , str(req.price), str(req.volume)
        self.futureTrade(symbol + "_usd", contract_type , type_ , str(req.price), str(req.volume) , _lever_rate = self._use_leverage)
        
        # 本地委托号加1，并将对应字符串保存到队列中，返回基于本地委托号的vtOrderID
        self.localNo += 1
        self.localNoQueue.put(str(self.localNo))
        vtOrderID = '.'.join([self.gatewayName, str(self.localNo)])
        return vtOrderID
    
    #----------------------------------------------------------------------
    def contractCancel(self, req):
        """撤单"""
        symbol_pair , symbol, contract_type , leverage = self.dealSymbolFunc(req.symbol)

        localNo = req.orderID
        
        if localNo in self.localNoDict:
            orderID = self.localNoDict[localNo]
            self.futureCancelOrder(symbol + "_usd", orderID , contract_type)
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



########################################################################
class Api_Spot(OKEX_Sub_Spot_Api):
    """okex的API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(Api_Spot, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        
        self.active = False             # 若为True则会在断线后自动重连

        self.cbDict = {}
        self.tickDict = {}
        self.orderDict = {}

        self.channelSymbolMap = {}
        
        self.localNo = 0                # 本地委托号
        self.localNoQueue = Queue()     # 未收到系统委托号的本地委托号队列
        self.localNoDict = {}           # key为本地委托号，value为系统委托号
        self.orderIdDict = {}           # key为系统委托号，value为本地委托号
        self.cancelDict = {}            # key为本地委托号，value为撤单请求

        self.recordOrderId_BefVolume = {}       # 记录的之前处理的量

        self.cache_some_order = {}
        self.tradeID = 0

        self.registerSymbolPairArray = set([])
        
        self.initCallback()
        

    '''
    登录后，每次订单执行撤销后又这样的 推送。。不知道干啥的。先过滤掉了
    {u'binary': 1, u'product': u'spot', u'type': u'order', u'base': u'etc'
, u'quote': u'usdt', u'data': {u'status': -1, u'orderType': 0, u'price': u'25.4050', u'modifyTime':
1512288275000L, u'userId': 6548935, u'createTime': 1512288275000L, u'source': 0, u'quoteSize': u'0.0
0000000', u'executedValue': u'0.00000000', u'id': 62877909, u'filledSize': u'0.00000000', u'side': 1
, u'size': u'0.01000000'}}
    '''
    #----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """信息推送""" 
        # print evt
        data = self.readData(evt)[0]
        try:
            channel = data['channel']
        except Exception,ex:
            channel = None
        if channel == None:
            return
        # try:
        if channel == "addChannel" and 'data' in data:
            channel = data['data']["channel"]
        if channel != "addChannel" and 'future' not in channel and channel != 'login': 

            callback = self.cbDict[channel]
            callback(data)

        # if 'depth' not in channel and 'ticker' not in channel and 'deals' not in channel and 'userinfo' not in channel and 'future' not in channel:
        #     print data

        # except Exception,ex:
        #     print "Error in callback cbDict ", channel

            #print self.cbDict

    #----------------------------------------------------------------------
    def onError(self, ws, evt):
        """错误推送"""
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        error.errorMsg = str(evt)
        self.gateway.onError(error)

    #----------------------------------------------------------------------
    def onError(self, data):
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        error.errorMsg = str(data["data"]["error_code"])
        self.gateway.onError(error)

    #----------------------------------------------------------------------
    def reconnect(self):
        while not self.gateway.connected:            
            self.writeLog(u'okex api_spot 等待10秒后重新连接')
            self.connect_Subpot(self.apiKey , self.secretKey , self.trace)
            #self.connect_Contract(self.apiKey , self.secretKey , self.trace)
            sleep(10)
            if not self.gateway.connected:
                self.reconnect()

    #----------------------------------------------------------------------
    def onClose(self, ws):
        """接口断开"""
        # 如果尚未连上，则忽略该次断开提示
        if not self.gateway.connected:
            return
        
        self.gateway.connected = False
        self.writeLog(u'服务器连接断开')
        
        # 重新连接
        if self.active:
            t = Thread(target=self.reconnect)
            t.start()

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        symbol_pair_gateway = subscribeReq.symbol
        arr = symbol_pair_gateway.split('.')
        symbol_pair = arr[0]
        
        print "subscribe" , symbol_pair
        if symbol_pair not in self.registerSymbolPairArray:
            self.registerSymbolPairArray.add(symbol_pair)
            self.subscribeSingleSymbol( symbol_pair)
            self.spotOrderInfo(symbol_pair , '-1')


    #----------------------------------------------------------------------
    def subscribeSingleSymbol(self, symbol ):
        # print "subscribeSingleSymbol ", symbol
        if symbol in okex_all_symbol_pairs:
            self.subscribeSpotTicker(symbol )
            self.subscribeSpotDepth5(symbol )
            #self.subscribeSpotTrades(symbol)

    #----------------------------------------------------------------------
    def contractAllOrders(self):
        for symbol in self.registerSymbolPairArray:
            symbol = (symbol.split('.'))[0]
            if symbol in okex_all_symbol_pairs:
                self.spotOrderInfo(symbol , '-1')

        for orderId in self.orderIdDict.keys():
            order = self.orderDict.get(orderId , None)
            if order != None:
                symbol_pair = (order.symbol.split('.'))[0]
                self.spotOrderInfo(symbol_pair , orderId)

    #----------------------------------------------------------------------
    def onOpen(self, ws):       
        """连接成功"""
        self.gateway.connected = True
        self.writeLog(u'服务器连接成功')
        
        self.login()
        # 连接后查询账户和委托数据
        self.spotUserInfo()
        
        # self.subscribeSingleSymbol("etc_usdt")
        for symbol in okex_all_symbol_pairs:
            # self.subscribeSpotTicker(symbol)
            # self.subscribeSpotDepth5(symbol)
            # self.subscribeSpotDeals(symbol)
            #Ticker数据
            self.channelSymbolMap["ok_sub_spot_%s_ticker" % symbol] = symbol
            #盘口的深度
            self.channelSymbolMap["ok_sub_spot_%s_depth_5" % symbol] = symbol
            #所有人的交易数据
            self.channelSymbolMap["ok_sub_spot_%s_deals" % symbol] = symbol

            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            contract.symbol = symbol
            contract.exchange = EXCHANGE_OKEX
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = u'OKEX现货%s' % symbol
            contract.size = 0.00001
            contract.priceTick = 0.00001
            contract.productClass = PRODUCT_SPOT
            self.gateway.onContract(contract)

    '''
    [{
    "channel":"ok_sub_spot_bch_btc_deals",
    "data":[["1001","2463.86","0.052","16:34:07","ask"]]
    }]
    '''
    #----------------------------------------------------------------------
    def onSpotSubDeals(self, data):
        if 'data' not in data:
            return
        rawData = data["data"]

        # print rawData

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """快速记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)
        
    #----------------------------------------------------------------------
    def initCallback(self):
        """初始化回调函数"""
        # USD_SPOT
        for symbol_pair in okex_all_symbol_pairs:
            self.cbDict["ok_sub_spot_%s_ticker" % symbol_pair] = self.onTicker
            self.cbDict["ok_sub_spot_%s_depth_5" % symbol_pair] = self.onDepth
            self.cbDict["ok_sub_spot_%s_deals" % symbol_pair] = self.onSpotSubDeals

            self.cbDict["ok_sub_spot_%s_order" % symbol_pair] = self.onSpotSubOrder
            self.cbDict["ok_sub_spot_%s_balance" % symbol_pair] = self.onSpotBalance

        self.cbDict['ok_spot_userinfo'] = self.onSpotUserInfo
        self.cbDict['ok_spot_orderinfo'] = self.onSpotOrderInfo

        # 下面这两个好像废弃了
        #self.cbDict['ok_sub_spot_userinfo'] = self.onSpotSubUserInfo
        #self.cbDict['ok_sub_spot_trades'] = self.onSpotSubTrades
        
        self.cbDict['ok_spot_order'] = self.onSpotOrder
        self.cbDict['ok_spot_cancel_order'] = self.onSpotCancelOrder
    
    '''
    [
        {
            "binary": 0,
            "channel": "ok_sub_spot_bch_btc_ticker",
            "data": {
                "high": "10000",
                "vol": "185.03743858",
                "last": "111",
                "low": "0.00000001",
                "buy": "115",
                "change": "101",
                "sell": "115",
                "dayLow": "0.00000001",
                "dayHigh": "10000",
                "timestamp": 1500444626000
            }
        }
    ]
    '''
    #----------------------------------------------------------------------
    def onTicker(self, data):
        print data
        """"""
        if 'data' not in data:
            return
        
        channel = data['channel']
        if channel == 'addChannel':
            return
        try:
            symbol = self.channelSymbolMap[channel]
            
            if symbol not in self.tickDict:
                tick = VtTickData()
                tick.exchange = EXCHANGE_OKEX
                tick.symbol = '.'.join([symbol, tick.exchange])
                tick.vtSymbol = '.'.join([symbol, tick.exchange])

                tick.gatewayName = self.gatewayName
                self.tickDict[symbol] = tick
            else:
                tick = self.tickDict[symbol]
            
            rawData = data['data']
            tick.highPrice = float(rawData['high'])
            tick.lowPrice = float(rawData['low'])
            tick.lastPrice = float(rawData['last'])
            tick.volume = float(rawData['vol'].replace(',', ''))
            # tick.date, tick.time = self.generateDateTime(rawData['timestamp'])
            
            # print "ticker", tick.date , tick.time
            # newtick = copy(tick)
            # self.gateway.onTick(newtick)
        except Exception,ex:
            print "Error in onTicker " , channel
    
    #----------------------------------------------------------------------
    def onDepth(self, data):
        """"""
        if 'data' not in data:
            return
        try:
            channel = data['channel']
            symbol = self.channelSymbolMap[channel]
        except Exception,ex:
            symbol = None

        if symbol == None:
            return
        
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.symbol = symbol
            tick.vtSymbol = symbol
            tick.gatewayName = self.gatewayName
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]
        
        if 'data' not in data:
            return
        rawData = data['data']

        try:
            tick.bidPrice1, tick.bidVolume1 = rawData['bids'][0]
            tick.bidPrice2, tick.bidVolume2 = rawData['bids'][1]
            tick.bidPrice3, tick.bidVolume3 = rawData['bids'][2]
            tick.bidPrice4, tick.bidVolume4 = rawData['bids'][3]
            tick.bidPrice5, tick.bidVolume5 = rawData['bids'][4]
        except Exception,ex:
            print "rawData['bids']" ,ex
            print rawData
        
        try:
            tick.askPrice1, tick.askVolume1 = rawData['asks'][-1]
            tick.askPrice2, tick.askVolume2 = rawData['asks'][-2]
            tick.askPrice3, tick.askVolume3 = rawData['asks'][-3]
            tick.askPrice4, tick.askVolume4 = rawData['asks'][-4]
            tick.askPrice5, tick.askVolume5 = rawData['asks'][-5]     
        except Exception,ex:
            print "rawData['asks'][-1]", ex 
            print rawData
        
        tick.date, tick.time = self.generateDateTime(rawData['timestamp'])
        # print "Depth", tick.date , tick.time
        
        newtick = copy(tick)
        self.gateway.onTick(newtick)

    '''
    [
        {
            "base": "bch",
            "binary": 0,
            "channel": "ok_sub_spot_bch_btc_balance",
            "data": {
                "info": {
                    "free": {
                        "btc": 5814.850605790395
                    },
                    "freezed": {
                        "btc": 7341
                    }
                }
            },
            "product": "spot",
            "quote": "btc",
            "type": "order"
        }
    ]
    '''
    def onSpotBalance(self, data):
        """交易发生金额变动之后会触发这个函数"""
        print data
        rawData = data['data']
        info = rawData['info']

        for symbol in info["freezed"].keys():
            pos = VtPositionData()
            pos.gatewayName = self.gatewayName
            pos.symbol = symbol + "." + EXCHANGE_OKEX
            pos.vtSymbol = symbol + "." + EXCHANGE_OKEX
            pos.direction = DIRECTION_NET
            pos.frozen = float(info['freezed'][symbol])
            pos.position = pos.frozen + float(info['free'][symbol])
            self.gateway.onPosition(pos)

    '''
    [{"binary":0,"channel":"ok_spot_userinfo","data":{"result":true,"info":{"funds":{"borrow":{"dgd":"0"
,"bcd":"0","bcc":"0","bch":"0","hsr":"0","xuc":"0","omg":"0","eos":"0","qtum":"0","btc":"0","act":"0
","bcs":"0","btg":"0","etc":"0","eth":"0","usdt":"0","gas":"0","zec":"0","neo":"0","ltc":"0","bt1":"
0","bt2":"0","iota":"0","pay":"0","storj":"0","gnt":"0","snt":"0","dash":"0"},"free":{"dgd":"0","bcd
":"0","bcc":"0","bch":"0","hsr":"0","xuc":"3","omg":"0","eos":"0","qtum":"0","btc":"0.00266884258369
","act":"0","bcs":"0","btg":"0","etc":"7.9909635","eth":"0","usdt":"0","gas":"0","zec":"0","neo":"0"
,"ltc":"0","bt1":"0","bt2":"0","iota":"0","pay":"0","storj":"0","gnt":"0","snt":"0","dash":"0"},"fre
ezed":{"dgd":"0","bcd":"0","bcc":"0","bch":"0","hsr":"0","xuc":"0","omg":"0","eos":"0","qtum":"0","b
tc":"0","act":"0","bcs":"0","btg":"0","etc":"0","eth":"0","usdt":"0","gas":"0","zec":"0","neo":"0","
ltc":"0","bt1":"0","bt2":"0","iota":"0","pay":"0","storj":"0","gnt":"0","snt":"0","dash":"0"}}}}}]
{u'binary': 0, u'data': {u'info': {u'funds': {u'freezed': {u'zec': u'0', u'usdt': u'0', u'btg': u'0'
, u'btc': u'0', u'bt1': u'0', u'neo': u'0', u'pay': u'0', u'storj': u'0', u'iota': u'0', u'omg': u'0
', u'dgd': u'0', u'bt2': u'0', u'xuc': u'0', u'gas': u'0', u'hsr': u'0', u'snt': u'0', u'dash': u'0'
, u'bch': u'0', u'gnt': u'0', u'bcd': u'0', u'qtum': u'0', u'bcc': u'0', u'eos': u'0', u'etc': u'0',
 u'act': u'0', u'eth': u'0', u'ltc': u'0', u'bcs': u'0'}, u'borrow': {u'zec': u'0', u'usdt': u'0', u
'btg': u'0', u'btc': u'0', u'bt1': u'0', u'neo': u'0', u'pay': u'0', u'storj': u'0', u'iota': u'0',
u'omg': u'0', u'dgd': u'0', u'bt2': u'0', u'xuc': u'0', u'gas': u'0', u'hsr': u'0', u'snt': u'0', u'
dash': u'0', u'bch': u'0', u'gnt': u'0', u'bcd': u'0', u'qtum': u'0', u'bcc': u'0', u'eos': u'0', u'
etc': u'0', u'act': u'0', u'eth': u'0', u'ltc': u'0', u'bcs': u'0'}, u'free': {u'zec': u'0', u'usdt'
: u'0', u'btg': u'0', u'btc': u'0.00266884258369', u'bt1': u'0', u'neo': u'0', u'pay': u'0', u'storj
': u'0', u'iota': u'0', u'omg': u'0', u'dgd': u'0', u'bt2': u'0', u'xuc': u'3', u'gas': u'0', u'hsr'
: u'0', u'snt': u'0', u'dash': u'0', u'bch': u'0', u'gnt': u'0', u'bcd': u'0', u'qtum': u'0', u'bcc'
: u'0', u'eos': u'0', u'etc': u'7.9909635', u'act': u'0', u'eth': u'0', u'ltc': u'0', u'bcs': u'0'}}
}, u'result': True}, u'channel': u'ok_spot_userinfo'}
    '''
    #----------------------------------------------------------------------
    def onSpotUserInfo(self, data):
        """现货账户资金推送"""
        rawData = data['data']
        info = rawData['info']
        funds = rawData['info']['funds']
        
        # 持仓信息
        #for symbol in ['btc', 'ltc','eth', self.currency]:
        for symbol in okex_all_symbol_type:
            if symbol in funds['free']:
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName
                
                pos.symbol = symbol + "." + EXCHANGE_OKEX
                pos.vtSymbol = symbol + "." + EXCHANGE_OKEX
                pos.vtPositionName = symbol
                pos.direction = DIRECTION_NET
                
                pos.frozen = float(funds['freezed'][symbol])
                pos.position = pos.frozen + float(funds['free'][symbol])
                
                self.gateway.onPosition(pos)

        # 账户资金
        account = VtAccountData()
        account.gatewayName = self.gatewayName
        account.accountID = self.gatewayName
        account.vtAccountID = account.accountID
        account.balance = 0.0
        #account.balance = float(funds['asset']['net'])
        self.gateway.onAccount(account)    
    
    #----------------------------------------------------------------------
    # 这个 API 现在文档没找到。。 好像废弃了
    def onSpotSubUserInfo(self, data):
        """现货账户资金推送"""
        if 'data' not in data:
            return
        
        rawData = data['data']
        info = rawData['info']
        
        # 持仓信息
        #for symbol in ['btc', 'ltc','eth', self.currency]:
        for symbol in okex_all_symbol_type:
            if symbol in info['free']:
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName
                
                pos.symbol = symbol + "." + EXCHANGE_OKEX
                pos.vtSymbol = symbol + "." + EXCHANGE_OKEX
                pos.vtPositionName = symbol
                pos.direction = DIRECTION_NET
                
                pos.frozen = float(info['freezed'][symbol])
                pos.position = pos.frozen + float(info['free'][symbol])
                
                self.gateway.onPosition(pos)  

    '''
    交易数据
    [
        {
            "base": "bch",
            "binary": 0,
            "channel": "ok_sub_spot_bch_btc_order",
            "data": {
                "symbol": "bch_btc",
                "tradeAmount": "1.00000000",
                "createdDate": "1504530228987",
                "orderId": 6191,
                "completedTradeAmount": "0.00000000",
                "averagePrice": "0",
                "tradePrice": "0.00000000",
                "tradeType": "buy",
                "status": 0,
                "tradeUnitPrice": "113.00000000"
            },
            "product": "spot",
            "quote": "btc",
            "type": "balance"
        }
    ]

    {u'binary': 0, u'data': {u'orderId': 62870564, u'status': 0, u'tradeType': u'sell', u'tradeUnitPrice
': u'25.3500', u'symbol': u'etc_usdt', u'tradePrice': u'0.0000', u'createdDate': u'1512287172393', u
'averagePrice': u'0', u'tradeAmount': u'0.01000000', u'completedTradeAmount': u'0.00000000'}, u'chan
nel': u'ok_sub_spot_etc_usdt_order'}
    '''
    #----------------------------------------------------------------------
    def onSpotSubOrder(self, data):
        """交易数据"""
        if 'data' not in data:
            return

        rawData = data["data"]
        
        # 本地和系统委托号
        orderId = str(rawData['orderId'])

        # 这时候出现None , 情况是 已经发出了单子，但是系统这里还没建立 索引
        # 先这样返回试一下
        # 因为 发完单，订单变化是先推送的。。导致不清楚他的localID
        # 现在的处理方式是， 先缓存这里的信息，等到出现了 localID，再来处理这一段
        localNo = self.orderIdDict.get(orderId , None)
        if localNo == None:
            arr = self.cache_some_order.get(orderId , None)
            if arr == None:
                arr = []
                arr.append( data)
                self.cache_some_order[orderId] = arr
            else:
                arr.append( data)
            return 

        # 委托信息
        if orderId not in self.orderDict:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            
            order.symbol = '.'.join([rawData['symbol'] , EXCHANGE_OKEX])
            #order.symbol = spotSymbolMap[rawData['symbol']]
            order.vtSymbol = order.symbol
    
            order.orderID = localNo
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.price = float(rawData['tradeUnitPrice'])
            order.totalVolume = float(rawData['tradeAmount'])
            order.direction, priceType = priceTypeMap[rawData['tradeType']]    
            
            self.orderDict[orderId] = order
        else:
            order = self.orderDict[orderId]
            
        order.tradedVolume = float(rawData['completedTradeAmount'])
        order.status = statusMap[rawData['status']]
        
        self.gateway.onOrder(copy(order))

        bef_volume = self.recordOrderId_BefVolume.get( orderId , 0.0 )
        now_volume = float(rawData['completedTradeAmount']) - bef_volume

        self.recordOrderId_BefVolume[orderId] = float(rawData['completedTradeAmount'])

        if now_volume > 0.000001:
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName

            trade.symbol = order.symbol
            trade.vtSymbol = order.symbol            
            
            self.tradeID += 1
            trade.tradeID = str(self.tradeID)
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
            
            trade.orderID = localNo
            trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
            
            trade.price = float(rawData['tradeUnitPrice'])
            trade.volume = float(now_volume)
            
            trade.direction, priceType = priceTypeMap[rawData['tradeType']]    
            
            trade.tradeTime = datetime.now().strftime('%H:%M:%S')
            
            self.gateway.onTrade(trade)
        
        """
        原来的OK coin方式，不过数据一直没有 所以换一种方式
        # 成交信息
        if 'sigTradeAmount' in rawData and float(rawData['sigTradeAmount'])>0:
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            
            trade.symbol = spotSymbolMap[rawData['symbol']]
            trade.vtSymbol = order.symbol            
            
            trade.tradeID = str(rawData['id'])
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
            
            trade.orderID = localNo
            trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
            
            trade.price = float(rawData['sigTradePrice'])
            trade.volume = float(rawData['sigTradeAmount'])
            
            trade.direction, priceType = priceTypeMap[rawData['tradeType']]    
            
            trade.tradeTime = datetime.now().strftime('%H:%M:%S')
            
            self.gateway.onTrade(trade)
        """
    '''
    [
        {
            "binary": 0,
            "channel": "ok_spot_orderinfo",
            "data": {
                "result": true,
                "orders": [
                    {
                        "symbol": "bch_btc",
                        "amount": "0.10000000",
                        "price": "1.00000000",
                        "avg_price": 0,
                        "create_date": 1504529828000,
                        "type": "buy",
                        "deal_amount": 0,
                        "order_id": 6189,
                        "status": -1
                    }
                ]
            }
        }
    ]
    '''
    #----------------------------------------------------------------------
    def onSpotOrderInfo(self, data):
        """委托信息查询回调"""
        if "error_code" in data.keys():
            print data
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
                
                #order.symbol = spotSymbolMap[d['symbol']]
                order.symbol = '.'.join([d["symbol"] , EXCHANGE_OKEX])
                order.vtSymbol = order.symbol
    
                order.orderID = localNo
                order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
                
                order.price = d['price']
                order.totalVolume = d['amount']
                order.direction, priceType = priceTypeMap[d['type']]
                
                self.orderDict[orderId] = order
            else:
                order = self.orderDict[orderId]
                
            order.tradedVolume = d['deal_amount']
            order.status = statusMap[d['status']]            
            
            self.gateway.onOrder(copy(order))

    '''
    [
        {
            "binary": 0,
            "channel": "ok_spot_order",
            "data": {
                "result": true,
                "order_id": 6189
            }
        }
    ]
    '''
    def onSpotOrder(self, data):
        rawData = data['data']
        if 'error_code' in rawData.keys():
            print data
            return

        orderId = str(rawData['order_id'])
        
        # 尽管websocket接口的委托号返回是异步的，但经过测试是
        # 符合先发现回的规律，因此这里通过queue获取之前发送的
        # 本地委托号，并把它和推送的系统委托号进行映射

        # localNo = self.orderIdDict.get(orderId , None)
        # if localNo == None:
        
        localNo = self.localNoQueue.get_nowait()
        
        self.localNoDict[localNo] = orderId
        self.orderIdDict[orderId] = localNo

        # print orderId , self.cache_some_order
        if orderId in self.cache_some_order.keys():
            arr = self.cache_some_order[orderId]
            for d in arr:
                self.onSpotSubOrder(d)

            # 处理完就删除掉这里
            del self.cache_some_order[orderId]
        
        # 检查是否有系统委托号返回前就发出的撤单请求，若有则进
        # 行撤单操作
        if localNo in self.cancelDict:
            req = self.cancelDict[localNo]
            self.spotCancel(req)
            del self.cancelDict[localNo]

    
    '''
    [
        {
            "binary": 0,
            "channel": "ok_spot_cancel_order",
            "data": {
                "result": true,
                "order_id": "125433027"
            }
        }
    ]
    '''
    #----------------------------------------------------------------------
    def onSpotCancelOrder(self, data):
        """撤单回报"""
        if 'data' not in data:
            return

        if 'error' in data["data"].keys():
            self.onError(data)
            return

        rawData = data['data']
        orderId = str(rawData['order_id'])

        localNo = self.orderIdDict[orderId]

        order = self.orderDict[orderId]
        # 感觉下面的判断是多余的
        # if orderId not in self.orderDict:
        #     order = VtOrderData()
        #     order.gatewayName = self.gatewayName
            
        #     order.symbol = '.'.join([rawData['symbol'] , EXCHANGE_OKEX])
        #     order.vtSymbol = order.symbol
    
        #     order.orderID = localNo
        #     order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
        #     self.orderDict[orderId] = order
        # else:
        #     order = self.orderDict[orderId]

        order.status = STATUS_CANCELLED
        self.gateway.onOrder(order)

        del self.orderDict[orderId]
        del self.orderIdDict[orderId]
        del self.localNoDict[localNo]

        if orderId in self.cache_some_order.keys():
            del self.cache_some_order[orderId]
    
    #----------------------------------------------------------------------
    def spotSendOrder(self, req):
        """发单"""
        #symbol = spotSymbolMapReverse[req.symbol][:4]
        symbol = (req.symbol.split('.'))[0]
        type_ = priceTypeMapReverse[(req.direction, req.priceType)]

        self.spotTrade(symbol, type_, str(req.price), str(req.volume))
        
        # 本地委托号加1，并将对应字符串保存到队列中，返回基于本地委托号的vtOrderID
        self.localNo += 1
        self.localNoQueue.put(str(self.localNo))
        vtOrderID = '.'.join([self.gatewayName, str(self.localNo)])
        return vtOrderID
    
    #----------------------------------------------------------------------
    def spotCancel(self, req):
        """撤单"""
        #symbol = spotSymbolMapReverse[req.symbol][:4]
        symbol = (req.symbol.split('.'))[0]
        localNo = req.orderID
        
        if localNo in self.localNoDict:
            orderID = self.localNoDict[localNo]
            self.spotCancelOrder(symbol, orderID)
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
