# encoding: UTF-8

'''
vn.zb的gateway接入
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

from vnpy.trader.vtGateway import *
from vnpy.api.zb import ZB_Sub_Spot_Api , zb_all_symbol_pairs , zb_all_symbols , zb_all_real_pair

from vnpy.trader.vtFunction import getJsonPath


# 价格类型映射
# 买卖类型： 限价单（buy/sell） 市价单（buy_market/sell_market）
zb_priceTypeMap = {}
zb_priceTypeMap["1"] = (DIRECTION_LONG, PRICETYPE_LIMITPRICE)
zb_priceTypeMap['buy_market'] = (DIRECTION_LONG, PRICETYPE_MARKETPRICE)
zb_priceTypeMap["0"] = (DIRECTION_SHORT, PRICETYPE_LIMITPRICE)
zb_priceTypeMap['sell_market'] = (DIRECTION_SHORT, PRICETYPE_MARKETPRICE)
zb_priceTypeMapReverse = {v: k for k, v in zb_priceTypeMap.items()} 

# 委托状态印射
zb_statusMap = {}

zb_statusMap[0] = STATUS_NOTTRADED
zb_statusMap[1] = STATUS_CANCELLED
zb_statusMap[2] = STATUS_ALLTRADED
zb_statusMap[3] = STATUS_PARTTRADED

class zbGateway(VtGateway):
    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='ZB'):
        """Constructor"""
        super(zbGateway, self).__init__(eventEngine, gatewayName)
        
        self.api_spot = ZB_API_Spot(self)     
        
        self.connected = False
        
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)     


        self.qryEnabled = True

        self.countTimer = 0
        self.localTimeDelay = 3

        # 启动查询
        self.initQuery()
        self.startQuery()

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
            trace = setting["trace"]
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 初始化接口
        
        self.api_spot.active = True
        self.api_spot.connect_Subpot( apiKey, secretKey, trace)
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'接口初始化成功'
        self.onLog(log)
        
        # 启动查询
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        self.api_spot.subscribe(subscribeReq)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.api_spot.spotSendOrder(orderReq)
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.api_spot.spotCancel(cancelOrderReq)
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        self.api_spot.spotUserInfo()

    #----------------------------------------------------------------------
    def qryOrderInfo(self):
        self.api_spot.spotAllOrders()

    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        pass
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.api_spot.active = False
        self.api_spot.close()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            #self.qryFunctionList = [self.qryAccount , self.qryOrderInfo]
            self.qryFunctionList = [ self.qryOrderInfo]
            #self.qryFunctionList = []
            
            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 2         # 查询触发点
            self.qryNextFunction = 0    # 上次运行的查询函数索引
            
    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.qryCount += 1

        self.countTimer += 1

        if self.countTimer % self.localTimeDelay == 0:
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

class ZB_API_Spot(ZB_Sub_Spot_Api):
    """ zb 的 API实现 """
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(ZB_API_Spot, self).__init__()

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

        self.tradeID = 0

        self.local_status_dict = {}
        self.registerSymbolPairArray = set([])
        
        self.initCallback()

    #----------------------------------------------------------------------
    def subscribe(self ,subscribeReq):
        """订阅行情"""
        symbol_pair_gateway = subscribeReq.symbol
        arr = symbol_pair_gateway.split('.')
        symbol_pair = arr[0]
        
        if symbol_pair not in self.registerSymbolPairArray:
            self.registerSymbolPairArray.add(symbol_pair)
            self.subscirbeSinglePair( symbol_pair)

    #----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """信息推送""" 
        # print evt
        data = self.readData(evt)
        try:
            channel = data['channel']
        except Exception,ex:
            channel = None
        if channel == None:
            return

        callback = self.cbDict[channel]
        callback(data)

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
    def onClose(self, ws):
        """接口断开"""
        # 如果尚未连上，则忽略该次断开提示
        if not self.gateway.connected:
            return
        
        self.gateway.connected = False
        self.writeLog(u'服务器连接断开')
        
        # 重新连接
        if self.active:
            def reconnect():
                while not self.gateway.connected:            
                    self.writeLog(u'等待10秒后重新连接')
                    sleep(10)
                    if not self.gateway.connected:
                        self.reconnect()
            
            t = Thread(target=reconnect)
            t.start()

    #----------------------------------------------------------------------
    def subscirbeSinglePair(self ,symbol_pair):
        if symbol_pair in zb_all_symbol_pairs:
            self.subscribeSpotTicker(symbol_pair)
            self.subscribeSpotDepth(symbol_pair)
            #self.self.subscribeSpotTrades(symbol_pair)

    #----------------------------------------------------------------------
    def onOpen(self, ws):       
        """连接成功"""
        self.gateway.connected = True
        self.writeLog(u'服务器连接成功')

        self.spotUserInfo()

        self.subscirbeSinglePair("btc_qc")

        for symbol in zb_all_symbol_pairs:
            
            #self.subscirbeSinglePair(symbol)

            use_symbol = symbol.replace('_','')

            #Ticker数据
            self.channelSymbolMap["%s_ticker" % use_symbol] = symbol
            #盘口的深度
            self.channelSymbolMap["%s_depth" % use_symbol] = symbol
            #所有人的交易数据
            self.channelSymbolMap["%s_trades" % use_symbol] = symbol

            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            contract.symbol = symbol
            contract.exchange = EXCHANGE_ZB
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = u'ZB现货%s' % symbol
            contract.size = 0.00001
            contract.priceTick = 0.00001
            contract.productClass = PRODUCT_SPOT
            self.gateway.onContract(contract)

    #----------------------------------------------------------------------
    def initCallback(self):
        for symbol_pair in zb_all_symbol_pairs:
            use_symbol = symbol_pair.replace('_','')

            self.cbDict["%s_ticker" % use_symbol] = self.onTicker
            self.cbDict["%s_depth" % use_symbol] = self.onDepth
            self.cbDict["%s_trades" % use_symbol] = self.onTrades

            self.cbDict["%s_order" % use_symbol] = self.onSpotOrder
            self.cbDict["%s_cancelorder" % use_symbol] = self.onSpotCancelOrder
            self.cbDict["%s_getorder" % use_symbol] = self.onSpotGetOrder
            self.cbDict["%s_getorders" % use_symbol] = self.onSpotGetOrders
            ####self.cbDict["%s_getordersignoretradetype" % use_symbol] = self.onSpotGetOrdersignoretradetype
            self.cbDict["%s_getordersignoretradetype" % use_symbol] = self.onSpotGetOrders

            # self.cbDict["%s_ticker" % symbol_pair] = self.onTicker
            # self.cbDict["%s_depth" % symbol_pair] = self.onDepth
            # self.cbDict["%s_trades" % symbol_pair] = self.onTrades

            # self.cbDict["%s_order" % symbol_pair] = self.onSpotOrder
            # self.cbDict["%s_cancelorder" % symbol_pair] = self.onSpotCancelOrder
            # self.cbDict["%s_getorder" % symbol_pair] = self.onSpotGetOrder
            # self.cbDict["%s_getorders" % symbol_pair] = self.onSpotGetOrders
            # ####self.cbDict["%s_getordersignoretradetype" % use_symbol] = self.onSpotGetOrdersignoretradetype
            # self.cbDict["%s_getordersignoretradetype" % use_symbol] = self.onSpotGetOrders

        self.cbDict["getaccountinfo"] = self.onSpotUserInfo

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """快速记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    #----------------------------------------------------------------------
    def onTicker(self, data):
        """"""
        if 'ticker' not in data:
            return
        channel = data['channel']
        if channel == 'addChannel':
            return
        try:
            symbol = self.channelSymbolMap[channel]
            if symbol not in self.tickDict:
                tick = VtTickData()
                tick.exchange = EXCHANGE_ZB
                tick.symbol = '.'.join([symbol, tick.exchange])
                tick.vtSymbol = '.'.join([symbol, tick.exchange])

                tick.gatewayName = self.gatewayName
                self.tickDict[symbol] = tick
            else:
                tick = self.tickDict[symbol]
        
            rawData = data['ticker']
            tick.highPrice = float(rawData['high'])
            tick.lowPrice = float(rawData['low'])
            tick.lastPrice = float(rawData['last'])
            tick.volume = float(rawData['vol'])

            tick.date, tick.time = self.generateDateTime(data['date'])
            
            # print "ticker", tick.date , tick.time
            # newtick = copy(tick)
            # self.gateway.onTick(newtick)
        except Exception,ex:
            print "Error in onTicker " , channel

    #----------------------------------------------------------------------
    def onDepth(self, data):
        """"""
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
        
        if 'asks' not in data:
            return

        asks = data["asks"]
        bids = data["bids"]
        

        tick.bidPrice1, tick.bidVolume1 = bids[0]
        tick.bidPrice2, tick.bidVolume2 = bids[1]
        tick.bidPrice3, tick.bidVolume3 = bids[2]
        tick.bidPrice4, tick.bidVolume4 = bids[3]
        tick.bidPrice5, tick.bidVolume5 = bids[4]
        
        tick.askPrice1, tick.askVolume1 = asks[-1]
        tick.askPrice2, tick.askVolume2 = asks[-2]
        tick.askPrice3, tick.askVolume3 = asks[-3]
        tick.askPrice4, tick.askVolume4 = asks[-4]
        tick.askPrice5, tick.askVolume5 = asks[-5]     
        
        tick.date, tick.time = self.generateDateTimeAccordingLocalTime()
        # print "Depth", tick.date , tick.time
        
        newtick = copy(tick)
        self.gateway.onTick(newtick)

    '''
    //# Request
    {
        'event':'addChannel',
        'channel':'ltcbtc_trades',
    }
    //# Response
    {
        "data": [
            {
                "date":"1443428902",
                "price":"1565.91",
                "amount":"0.553",
                "tid":"37594617",
                "type":"sell",
                "trade_type":"ask"
            }...
        ],
        "no": 1031995,
        "channel": "ltcbtc_trades"
    }
                    
    '''
    #----------------------------------------------------------------------
    def onTrades(self, data):
        pass
        # try:
        #     channel = data['channel']
        #     symbol = self.channelSymbolMap[channel]
        # except Exception,ex:
        #     symbol = None

        # if symbol == None:
        #     return

    #----------------------------------------------------------------------
    def spotAllOrders(self):
        for symbol_pair in self.registerSymbolPairArray:
            self.spotGetOrderSignOrderTradeType(symbol_pair , 1 , 50 , 1)

    #----------------------------------------------------------------------
    def onSpotOrder(self, data):
        code = data["code"]
        if str(code) != "1000":
            errorData = {"data":{"error_code":str(code)}}
            self.onError(errorData)
            return 

        rawData = json.loads(data['data'].replace("entrustId",'"entrustId"'))
        orderId = str(rawData["entrustId"])
        # 尽管websocket接口的委托号返回是异步的，但经过测试是
        # 符合先发现回的规律，因此这里通过queue获取之前发送的
        # 本地委托号，并把它和推送的系统委托号进行映射
        localNo = self.localNoQueue.get_nowait()

        self.localNoDict[localNo] = orderId
        self.orderIdDict[orderId] = localNo

        t_symbol = (data["channel"].split('_'))[0]
        symbol = zb_all_real_pair[t_symbol]

        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = '.'.join([symbol , EXCHANGE_ZB])
        order.vtSymbol = order.symbol
        order.orderID = localNo
        order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
        self.orderDict[orderId] = order
        order.status = STATUS_UNKNOWN


        local_status = self.local_status_dict.get( str(localNo) , None)

        if local_status != None:
            order.direction, priceType = zb_priceTypeMap[str(local_status)]

        self.gateway.onOrder(order)
        
        # 检查是否有系统委托号返回前就发出的撤单请求，若有则进
        # 行撤单操作
        if localNo in self.cancelDict:
            req = self.cancelDict[localNo]
            self.spotCancel(req)
            del self.cancelDict[localNo]

    '''
    {
        "success": true,
        "code": 1000,
        "channel": "ltcbtc_cancelorder",
        "message": "操作成功。",
        "no": "1472814987517496849777"
    }
    '''
    #----------------------------------------------------------------------
    def onSpotCancelOrder(self, data):
        code = data["code"]
        if str(code) != "1000":
            errorData = {"data":{"error_code":str(code)}}
            self.onError(errorData)
            return 

        symbol , orderId = data["no"].split('.')
        orderId = str(orderId)
        localNo = self.orderIdDict[orderId]

        if orderId not in self.orderDict:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            
            order.symbol = '.'.join([symbol , EXCHANGE_ZB])
            order.vtSymbol = order.symbol
    
            order.orderID = localNo
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            self.orderDict[orderId] = order
        else:
            order = self.orderDict[orderId]

        order.status = STATUS_CANCELLED
        self.gateway.onOrder(order)

        del self.orderDict[orderId]
        del self.orderIdDict[orderId]
        del self.localNoDict[localNo]


    #----------------------------------------------------------------------
    def spotSendOrder(self, req):
        """发单"""
        symbol = (req.symbol.split('.'))[0]
        type_ = zb_priceTypeMapReverse[(req.direction, req.priceType)]

        self.spotTrade(symbol, type_, str(req.price), str(req.volume))
        
        # 本地委托号加1，并将对应字符串保存到队列中，返回基于本地委托号的vtOrderID
        self.localNo += 1
        self.localNoQueue.put(str(self.localNo))

        self.local_status_dict[str(self.localNo)] = str(type_)

        vtOrderID = '.'.join([self.gatewayName, str(self.localNo)])
        return vtOrderID
    
    #----------------------------------------------------------------------
    def spotCancel(self, req):
        """撤单"""
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
    def onSpotGetOrder(self , data):
        """生成时间"""
        code = data["code"]
        if str(code) != "1000":
            errorData = {"data":{"error_code":str(code)}}
            self.onError(errorData)
            return 
        rawData = data['data'].replace('{','{"').replace('}','"}').replace(":",'":"').replace(',','","').replace('}","{','}{').\
            replace(':"[',':[').replace('}{','},{').replace(']",','],').replace('}"}','}}').replace(':"{"',':{"')
        orderId = str(rawData["id"])

        # 这时候出现None , 情况是 已经发出了单子，但是系统这里还没建立 索引
        # 先这样返回试一下
        # 因为 发完单，订单变化是先推送的。。导致不清楚他的localID
        # 现在的处理方式是， 先缓存这里的信息，等到出现了 localID，再来处理这一段
        localNo = self.orderIdDict.get(orderId , None)
        if localNo == None:
            print "Error , localNo is none !" + str(localNo)
            return 

        # 委托信息
        if orderId not in self.orderDict:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            
            symbol = zb_all_real_pair[rawData["currency"].replace('_',"")]

            order.symbol = '.'.join([symbol, EXCHANGE_ZB])
            #order.symbol = spotSymbolMap[rawData['symbol']]
            order.vtSymbol = order.symbol
    
            order.orderID = localNo
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.price = float(rawData['price'])
            order.totalVolume = float(rawData['total_amount'])
            order.direction, priceType = zb_priceTypeMap[str(rawData['type'])]    
            
            self.orderDict[orderId] = order
        else:
            order = self.orderDict[orderId]
            
        order.tradedVolume = float(rawData['trade_amount'])
        order.status = zb_statusMap[int(rawData['status'])]
        
        self.gateway.onOrder(copy(order))

        bef_volume = self.recordOrderId_BefVolume.get( orderId , 0.0 )
        now_volume = float(rawData['trade_amount']) - bef_volume

        if now_volume > 0.00001:
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
            
            trade.direction, priceType = zb_priceTypeMap[str(rawData['type'])] 
            
            trade.tradeTime = datetime.now().strftime('%H:%M:%S')
            
            self.gateway.onTrade(trade)

        if order.status in [STATUS_CANCELLED , STATUS_ALLTRADED]:
            del self.orderIdDict[orderId]
            del self.orderDict[orderId]

    #----------------------------------------------------------------------
    def onSpotGetOrders(self, data):
        code = data["code"]
        if str(code) != "1000":
            errorData = {"data":{"error_code":str(code)}}
            self.onError(errorData)
            return 

        rawData = data['data'].replace('{','{"').replace('}','"}').replace(":",'":"').replace(',','","').replace('}","{','}{').\
            replace(':"[',':[').replace('}{','},{').replace(']",','],').replace('}"}','}}').replace(':"{"',':{"')
        rawData = json.loads(rawData)

        orderDictKeys = self.orderDict.keys()

        system_has_orderID_list = self.orderIdDict.keys()

        for d in rawData:
            orderId = str(d["id"])
            if orderId in system_has_orderID_list:
                localNo = self.orderIdDict[orderId]
                order = self.orderDict[orderId]

                order.price = float(d["price"])
                order.totalVolume = float(d["total_amount"])
                order.tradedVolume = float(d['trade_amount'])
                order.status = zb_statusMap[int(d['status'])]

                self.gateway.onOrder(copy(order))

                bef_volume = self.recordOrderId_BefVolume.get( orderId , 0.0 )
                now_volume = float(d['trade_amount']) - bef_volume

                if now_volume > 0.00001:
                    trade = VtTradeData()
                    trade.gatewayName = self.gatewayName

                    trade.symbol = order.symbol
                    trade.vtSymbol = order.symbol            
                    
                    self.tradeID += 1
                    trade.tradeID = str(self.tradeID)
                    trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
                    
                    trade.orderID = localNo
                    trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
                    
                    trade.price = float(d['price'])
                    trade.volume = float(now_volume)
                    
                    trade.direction, priceType = zb_priceTypeMap[str(d['type'])] 
                    
                    trade.tradeTime = datetime.now().strftime('%H:%M:%S')
                    
                    self.gateway.onTrade(trade)

                if order.status in [STATUS_CANCELLED , STATUS_ALLTRADED]:
                    del self.orderIdDict[orderId]
                    del self.orderDict[orderId]

            else:
                if zb_statusMap[int(d['status'])] not in [STATUS_CANCELLED , STATUS_ALLTRADED]:
                    self.localNo += 1
                    localNo = str(self.localNo)
                    orderId = str(d['id'])
                    self.localNoDict[localNo] = orderId
                    self.orderIdDict[orderId] = localNo

                    order = VtOrderData()
                    order.gatewayName = self.gatewayName

                    symbol = zb_all_real_pair[d["currency"].replace('_',"")]
                    
                    order.symbol = '.'.join([symbol , EXCHANGE_ZB])
                    order.vtSymbol = order.symbol
        
                    order.orderID = localNo
                    order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
                    
                    order.price = float(d['price'])
                    order.totalVolume = float(d['total_amount'])
                    order.direction, priceType = zb_priceTypeMap[str(d['type'])]
                    
                    self.orderDict[orderId] = order
                
                    order.tradedVolume = float(d['trade_amount'])
                    order.status = zb_statusMap[int(d['status'])]            
                    
                    self.gateway.onOrder(copy(order))

    #----------------------------------------------------------------------
    # def onSpotGetOrdersignoretradetype(self, data):
        """取消tradeType字段过滤，可同时获取买单和卖单，每次请求返回pageSize<100条记录"""
        """因为跟 getOrders 功能重复，统一处理了"""

    '''
    {
        "message": "操作成功",
        "no": "15207605119",
        "data": {
            "coins": [
                {
                    "freez": "1.35828369",
                    "enName": "BTC",
                    "unitDecimal": 8,
                    "cnName": "BTC",
                    "unitTag": "฿",
                    "available": "0.72771906",
                    "key": "btc"
                },
                {
                    "freez": "0.011",
                    "enName": "LTC",
                    "unitDecimal": 8,
                    "cnName": "LTC",
                    "unitTag": "Ł",
                    "available": "3.51859814",
                    "key": "ltc"
                },
                ...
            ],
            "base": {
                "username": "15207605119",
                "trade_password_enabled": true,
                "auth_google_enabled": true,
                "auth_mobile_enabled": true
            }
        },
        "code": 1000,
        "channel": "getaccountinfo",
        "success": true
    }
    '''
    #----------------------------------------------------------------------
    def onSpotUserInfo(self, data):
        code = data["code"]
        if str(code) != "1000":
            errorData = {"data":{"error_code":str(code)}}
            self.onError(errorData)
            return 
        try:

            rawData = data['data'].replace('{','{"').replace('}','"}').replace(":",'":"').replace(',','","').replace('}","{','}{').\
            replace(':"[',':[').replace('}{','},{').replace(']",','],').replace('}"}','}}').replace(':"{"',':{"')

            rawData = json.loads(rawData)
            coins = rawData["coins"]

        except Exception,ex:
            print ex

        for coin in coins:
            symbol = coin["cnName"].lower()
            if symbol in zb_all_symbols:
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName

                pos.symbol = symbol + "." + EXCHANGE_ZB
                pos.vtSymbol = symbol + "." + EXCHANGE_ZB
                pos.vtPositionName = symbol
                pos.direction = DIRECTION_NET

                pos.frozen = float(coin["freez"])
                pos.position = pos.frozen + float(coin["available"])

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
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(float(s)/1e3)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return date, time

    #----------------------------------------------------------------------
    def generateDateTimeAccordingLocalTime(self):
        dt = datetime.now()
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return date, time
        