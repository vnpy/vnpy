# encoding: UTF-8

'''
vn.binance的gateway接入
'''

import os,sys
import json
from datetime import datetime
from copy import copy
from threading import Condition
from queue import Queue
from threading import Thread
import traceback
import json
from datetime import datetime , timedelta
import time

from vnpy.api.binance import BinanceSpotApi,BinanceAPIException,BinanceRequestException
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtFunction import systemSymbolToVnSymbol , VnSymbolToSystemSymbol
from vnpy.trader.vtConstant import PRICETYPE_LIMITPRICE, DIRECTION_LONG, DIRECTION_NET,DIRECTION_SHORT, PRODUCT_SPOT, EXCHANGE_BINANCE, OFFSET_OPEN, OFFSET_CLOSE
from vnpy.trader.vtConstant import STATUS_UNKNOWN, STATUS_REJECTED, STATUS_ALLTRADED, STATUS_CANCELLED, STATUS_PARTTRADED, STATUS_NOTTRADED
'''
币安接口
'''
class BinanceGateway(VtGateway):
    """Binance 接口"""
    # ----------------------------------------------------------------------
    def __init__(self, eventEngine , gatewayName='BINANCE'):
        """Constructor"""
        super(BinanceGateway, self).__init__(eventEngine, gatewayName)

        # 创建现货交易API实例
        self.api_spot = BinanceApi(self)

        # 绑定写入日志和错误
        self.api_spot.writeLog = self.writeLog
        self.api_spot.writeError = self.writeError

        self.connected = False
        self.qryEnabled = True

        self.interval = 30
        self.accountID = "None"
        self.total_count = 0

        # gateway 配置文件
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)

        self.auto_subscribe_symbol_pairs = set()  # 自动订阅现货合约对清单

        # 消息调试
        self.log_message = False

    # ----------------------------------------------------------------------
    def connect(self):
        try:
            f = open(self.filePath, 'r')
        except IOError:
            self.writeError(u'BINANCE读取连接配置出错，请检查')
            return

        # 解析json文件
        setting = json.load(f)
        try:
            self.accountID = str(setting["accountID"])
            apiKey = str(setting['accessKey'])
            secretKey = str(setting['secretKey'])
            self.interval = float(setting['interval'])
            self.log_message = setting['log_message'] if 'log_message' in setting else False
            self.api_spot.setAccount(self.accountID)
            # 若希望连接后自动订阅
            if 'auto_subscribe' in setting.keys():
                self.auto_subscribe_symbol_pairs = set(setting['auto_subscribe'])

        except KeyError:
            self.writeLog(u'BINANCE连接配置缺少字段，请检查')
            return



        self.api_spot.active = True

        if self.log_message:
            self.api_spot.DEBUG = True

        self.api_spot.connect_Subpot(apiKey, secretKey)
        self.api_spot.spotExchangeInfo()

        for symbol_pair in self.auto_subscribe_symbol_pairs:
            self.writeLog(u'{}自动订阅现货合约:{}'.format(EXCHANGE_BINANCE, symbol_pair))
            sub = VtSubscribeReq()
            sub.symbol = symbol_pair
            self.subscribe(sub)


        self.writeLog(u'{}接口初始化成功'.format(self.gatewayName))

        # 启动查询
        self.initQuery()
        self.startQuery()

    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情，自动订阅全部行情，无需实现"""
        self.api_spot.register(subscribeReq)

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        try:
            return self.api_spot.sendOrder(orderReq)
        except Exception as ex:
            self.writeError(u'send order Exception:{},{}'.format(str(ex),traceback.format_exc()))

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

    def writeLog(self, content):
        """
        记录日志文件
        :param content:
        :return:
        """
        if self.logger:
            self.logger.info(content)

    def writeError(self, content, error_id = 0):
        """
        发送错误通知/记录日志文件
        :param content:
        :return:
        """
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        error.errorID = error_id
        error.errorMsg = content
        self.onError(error)

        if self.logger:
            self.logger.error(content)

        print(u'{} error:{}'.format(self.gatewayName, content), file=sys.stderr)
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

        self.reqToLocalID = {}                  # req 跟 localID建立本地映射

        self.tickDict = {}                      # key:symbol, value:tick

        self.registerSymbolSets = set([])

        self.tick_depth_array_dict = {}         # 用于计算 ticker 的 depth 的数据 
        self.symbol_real_depth_dict = {}        # 用于保存所有的深度数据的 dict 

    #----------------------------------------------------------------------
    def list_orders(self):
        """列出所有订单"""

        # 根据订阅清单，逐一发出订单列表查询请求
        for symbol in self.registerSymbolSets:
            self.spotListAllOrders(symbol)

    #----------------------------------------------------------------------
    def register(self, subscribeReq):
        """
        登记订阅行情
        :param subscribeReq:
        :return:
        """
        symbol = (subscribeReq.symbol.split('.'))[0]
        if symbol not in self.registerSymbolSets:
            self.registerSymbolSets.add( symbol )
        self.subscribeSpotTicker( symbol )
        self.subscribeSpotDepth( symbol )

    #----------------------------------------------------------------------
    def setAccount(self, useAccountID):
        self.accountID = useAccountID

    #----------------------------------------------------------------------
    def sendOrder(self , req):
        """发送委托"""
        # 检查是否填入了价格，禁止市价委托
        if req.priceType != PRICETYPE_LIMITPRICE:
            self.gateway.writeError(u'Binance接口仅支持限价单' , "sendOrder Error") 
            return None

        # 排除 symbol_pair.gateway后序
        symbol = (req.vtSymbol.split('.'))[0]

        self.gateway.writeLog( "send order %s,%s,%s,%s" % (req.vtSymbol , str(req.direction) , str(req.price) , str(req.volume) ))

        try:
            reqID = self.spotTrade(symbol_pair=symbol, type_="buy" if req.direction == DIRECTION_LONG else "sell",  price=float(req.price), amount=req.volume)

        except BinanceAPIException as ex:
            self.gateway.writeError(content=ex.message, error_id=ex.code)
            self.gateway.writeLog(traceback.format_exc())
            return None
        except BinanceRequestException as ex:
            self.gateway.writeError(content=ex.message)
            self.gateway.writeLog(traceback.format_exc())
            return None
        except Exception as ex:
            self.gateway.writeError(str(ex))
            self.gateway.writeLog(traceback.format_exc())
            return None

        if reqID is None:
            self.gateway.writeError(u'委托异常: %s,%s,%s,%s'.format(req.vtSymbol , str(req.direction) , str(req.price) , str(req.volume) ))
            return None

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
        order.vtOrderID = '.'.join([ order.gatewayName,order.orderID])

        order.direction = req.direction
        order.offset = OFFSET_OPEN if req.direction == DIRECTION_LONG else OFFSET_CLOSE

        order.price = float(req.price)
        order.tradedVolume = 0
        order.totalVolume = req.volume
        order.orderTime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        order.status = STATUS_UNKNOWN

        self.workingOrderDict[localID] = order
        
        self.reqToLocalID[reqID] = localID
        self.gateway.onOrder(order)

        # 返回委托号
        return order.vtOrderID


        """
            400 Filter failure: MIN_NOTIONAL -1013 <PreparedRequest [POST]> {'data': {'times
tamp': 1521525104380L, 'price': '0.00000100', 'side': 'BUY', 'timeInForce': 'GTC
', 'signature': '300c376ca6838c37c2a9e3c54b0870c657729a2df5f7016ddd48c2700537362
6', 'type': 'LIMIT', 'symbol': u'TNBBTC', 'quantity': 100.0}}

print ex.status_code, ex.message , ex.code , ex.request , ex.uri , ex.kwargs 
       """
    # ----------------------------------------------------------------------
    def onAllError(self, ex , req , reqID):

        self.gateway.writeError(content=str(ex) + ' ' + getattr(ex,'uri',''),error_id=getattr(ex,'status_code',0))
        
        # 判断是否应该是 发出的无效订单
        localID = self.reqToLocalID.get( reqID , None)
        if localID != None:
            order = self.workingOrderDict[localID]
            if order != None:
                # 推送 币安 拒绝单 过去
                order.status = STATUS_REJECTED
                self.gateway.onOrder(order)
                del self.workingOrderDict[localID]
                del self.reqToLocalID[reqID]
            else:
                self.gateway.writeError( u"order is None , 不能找到order %s" % (str(localID)), "b4")
        # else:
        #     self.gateway.writeError( u"localID is None , 不能找到localID %s" % (str(localID)), "b3")

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
        for symbol_dict in symbols:
            #symbol = systemSymbolToVnSymbol(symbol_dic["symbol"])
            symbol = '{}_{}'.format(symbol_dict.get('baseAsset', '').lower(),symbol_dict.get('quoteAsset', '').lower())
            if symbol == '_':
                continue
            status = symbol_dict.get("status", None)
            if status == "TRADING":
                filters = symbol_dict["filters"]
                price_filter = filters[0]
                volume_filter = filters[1]

                contract = VtContractData()
                contract.gatewayName = self.gatewayName
                contract.symbol = '.'.join( [symbol , EXCHANGE_BINANCE] )
                contract.exchange = EXCHANGE_BINANCE
                contract.vtSymbol = contract.symbol 
                contract.name = u"现货" + contract.vtSymbol
                contract.size = float(volume_filter["stepSize"])
                contract.priceTick = float(price_filter["tickSize"])
                contract.productClass = PRODUCT_SPOT
                contract.volumeTick = float(volume_filter["minQty"])

                self.gateway.onContract(contract)

    #----------------------------------------------------------------------
    def onAllTicker(self,msg):
        """币安支持所有 ticker 同时socket过来"""
        for symbol_pair_msg_dic in msg:
            symbol_pair = systemSymbolToVnSymbol(symbol_pair_msg_dic["s"])

            vtSymbol = '.'.join([symbol_pair , EXCHANGE_BINANCE])
            price = symbol_pair_msg_dic["p"]

            if symbol_pair not in self.tickDict:
                tick = VtTickData()
                tick.gatewayName = self.gatewayName

                tick.exchange = EXCHANGE_BINANCE
                tick.symbol = '.'.join([symbol_pair, tick.exchange])
                tick.vtSymbol = tick.symbol
                self.tickDict[tick.symbol] = tick
            else:
                tick = self.tickDict[vtSymbol]

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
        symbol_pair = systemSymbolToVnSymbol(msg["s"])
        symbol = symbol_pair + "." + EXCHANGE_BINANCE
        price = msg["p"]

        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.exchange = EXCHANGE_BINANCE
            tick.symbol = '.'.join([symbol_pair, tick.exchange])
            tick.vtSymbol = tick.symbol 
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        tick.highPrice = float(msg["h"])
        tick.lowPrice = float(msg["l"])
        tick.lastPrice = (float(msg["b"]) + float(msg["a"]))/2.0
        tick.volume = float(msg["v"])

        tick.bidPrice1 = float(msg["b"])
        tick.bidVolume1 = float(msg["B"])
        tick.askPrice1 = float(msg["a"])
        tick.askVolume1 = float(msg["A"])

        # tick.bidPrice2, tick.bidVolume2 = [0 , 0]
        # tick.bidPrice3, tick.bidVolume3 = [0 , 0]
        # tick.bidPrice4, tick.bidVolume4 = [0 , 0]
        # tick.bidPrice5, tick.bidVolume5 = [0 , 0]

        # tick.askPrice2, tick.askVolume2 = [0 , 0]
        # tick.askPrice3, tick.askVolume3 = [0 , 0]
        # tick.askPrice4, tick.askVolume4 = [0 , 0]
        # tick.askPrice5, tick.askVolume5 = [0 , 0]

        tick.datetime , tick.date , tick.time = self.generateDateTime( float(msg["E"]))

        #self.gateway.onTick(tick)

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
    def onDepth(self, msg):
        upper_symbol = msg.get('s',None)
        if upper_symbol is None:
            return
        symbol_pair = systemSymbolToVnSymbol(upper_symbol)
        first_update_id = msg["U"]
        final_update_id = msg["u"]
        bids = msg["b"]
        asks = msg["a"]
        uu_time_stamp = msg["E"]

        all_keys = self.symbol_real_depth_dict.keys()

        # print "onDepth"
        # 判断是否已经 读取过历史数据
        if symbol_pair in all_keys:
            # print "if symbol_pair in all_keys:"
            info = self.symbol_real_depth_dict[symbol_pair]
            depth_dict_bids = info["depth_dict_bids"]
            depth_dict_asks = info["depth_dict_asks"]
            last_event_id = info["last_event_id"]
            if int(last_event_id) + 1 >= int(first_update_id) and int(last_event_id) < int(final_update_id):
                for b_arr in bids:
                    price , volume , tmp_arr = b_arr
                    price = float(price)
                    volume = float(volume)
                    if volume > 0:
                        depth_dict_bids[price] = volume
                    else:
                        if price in depth_dict_bids.keys():
                            del depth_dict_bids[price]
                for a_arr in asks:
                    price , volume , tmp_arr = a_arr
                    price = float(price)
                    volume = float(volume)
                    if volume > 0:
                        depth_dict_asks[price] = volume
                    else:
                        if price in depth_dict_asks.keys():
                            del depth_dict_asks[price]

                self.symbol_real_depth_dict[symbol_pair]["last_event_id"] = str(final_update_id)
            else:
                if int(last_event_id) + 1 < int(first_update_id):
                    # 说明信息已经不及时了
                    del self.symbol_real_depth_dict[symbol_pair]
                    self.tick_depth_array_dict[symbol_pair] = [msg]
                    self.gateway.writeLog( "del update info %s's depth" % symbol_pair)

                    self.dealMsgArrayInfo(symbol_pair)
        else:
            # print "else symbol_pair in all_keys:"
            if symbol_pair not in self.tick_depth_array_dict:
                self.tick_depth_array_dict[symbol_pair] = [msg]
            else:
                self.tick_depth_array_dict[symbol_pair].append( msg)
            self.dealMsgArrayInfo(symbol_pair)

        # print "self.symbol_real_depth_dict"
        # print self.symbol_real_depth_dict

        depth_dict_bids = self.symbol_real_depth_dict[symbol_pair]["depth_dict_bids"]
        depth_dict_asks = self.symbol_real_depth_dict[symbol_pair]["depth_dict_asks"]

        symbol = symbol_pair + "." + EXCHANGE_BINANCE
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.symbol = symbol
            tick.vtSymbol = tick.symbol
            tick.exchange = EXCHANGE_BINANCE
            tick.gatewayName = self.gatewayName
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        try:
            arr = sorted(depth_dict_bids.items(),  key=lambda x: x[0])
            # print "tick1" , arr
            arr_len = len(arr)
            (tick.bidPrice1, tick.bidVolume1)  = arr[-1] if arr_len >=1 else (0,0)
            (tick.bidPrice2, tick.bidVolume2)  = arr[-2] if arr_len >=2 else (0,0)
            (tick.bidPrice3, tick.bidVolume3)  = arr[-3] if arr_len >=3 else (0,0)
            (tick.bidPrice4, tick.bidVolume4)  = arr[-4] if arr_len >=4 else (0,0)
            (tick.bidPrice5, tick.bidVolume5)  = arr[-5] if arr_len >=5 else (0,0)
        except Exception as ex:
            self.gateway.writeError(u'OnDepth Exception:{}'.format(str(ex)))
            self.gateway.writeLog(u'OnDepth {}'.format(traceback.format_exc()))

        try:
            arr = sorted(depth_dict_asks.items(), key=lambda x: x[0])
            # print "tick2", arr
            arr_len = len(arr)
            (tick.askPrice1, tick.askVolume1)  = arr[0] if arr_len >=1 else (0,0)
            (tick.askPrice2, tick.askVolume2)  = arr[1] if arr_len >=2 else (0,0)
            (tick.askPrice3, tick.askVolume3)  = arr[2] if arr_len >=3 else (0,0)
            (tick.askPrice4, tick.askVolume4)  = arr[3] if arr_len >=4 else (0,0)
            (tick.askPrice5, tick.askVolume5)  = arr[4] if arr_len >=5 else (0,0)
        except Exception as ex:
            self.gateway.writeError(u'OnDepth Exception:{}'.format(str(ex)))
            self.gateway.writeLog(u'OnDepth {}'.format(traceback.format_exc()))

        tick.datetime , tick.date, tick.time = self.generateDateTime(uu_time_stamp)
        
        # print tick.__dict__
        self.gateway.onTick(tick)
        #self.gateway.onTick(copy(tick))

    # 处理msg数据
    def dealMsgArrayInfo(self, symbol_pair):
        # print "in dealMsgArrayInfo"
        data = self.getDepthSymbol(symbol_pair )
        depth_dict_bids = {}
        depth_dict_asks = {}
        lastUpdateId = data["lastUpdateId"]
        bids = data["bids"]
        asks = data["asks"]
        for b_arr in bids:
            price , volume , tmp_arr = b_arr
            price = float(price)
            volume = float(volume)
            depth_dict_bids[price] = volume
        for a_arr in asks:
            price , volume , tmp_arr = a_arr
            price = float(price)
            volume = float(volume)
            depth_dict_asks[price] = volume

        arr = self.tick_depth_array_dict.get(symbol_pair , [])
        for msg in arr:
            first_update_id = msg["U"]
            final_update_id = msg["u"]
            if int(final_update_id) > int(lastUpdateId) :
                bids = msg["b"]
                asks = msg["a"]
                for b_arr in bids:
                    price , volume , tmp_arr = b_arr
                    price = float(price)
                    volume = float(volume)
                    if volume > 0:
                        depth_dict_bids[price] = volume
                for a_arr in asks:
                    price , volume , tmp_arr = a_arr
                    price = float(price)
                    volume = float(volume)
                    if volume > 0:
                        depth_dict_asks[price] = volume

                lastUpdateId = final_update_id
        self.tick_depth_array_dict[symbol_pair] = []

        self.symbol_real_depth_dict[symbol_pair] = {"last_event_id":str(lastUpdateId) ,  "depth_dict_bids":depth_dict_bids , "depth_dict_asks":depth_dict_asks}


    #----------------------------------------------------------------------
    # def onDepth(self, msg):
        '''
        这里研究了很久， 决定不实现 这个方法！   
        1、因为币安数据推送的 depth 是逐条的，跟原先的方法有差别，显得不好处理
        2、币安五档 socket 推送过来，没有写具体的 币种名。。  导致无法在这个方法中进行区分
        '''
        # pass
        # symbol_pair = systemSymbolToVnSymbol(msg["s"])
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

            if posObj.position > 0.0:
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
        #     symbol_pair = systemSymbolToVnSymbol(msg["s"])

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
                    bef_has_volume = self.tradedVolumeDict.get(localID, 0.0)
                    newTradeVolume = tradedVolume - bef_has_volume
                    self.writeLog('{} 成交:{} ,之前累计成交:{},当次成交:{}'.format(localID, tradedVolume, bef_has_volume, newTradeVolume))
                    order.tradedVolume = tradedVolume

                    if newTradeVolume > 0.000001:
                        trade = VtTradeData()
                        trade.gatewayName = self.gatewayName
                        trade.symbol = order.symbol
                        trade.vtSymbol = order.vtSymbol

                        self.tradeID += 1
                        trade.tradeID = str(self.tradeID)
                        trade.vtTradeID = '.'.join([trade.gatewayName, trade.tradeID])
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

                    if status == "FILLED":
                        # 说明这个单子成交完毕了！
                        order.status = STATUS_ALLTRADED
                        self.gateway.onOrder(order)

                        del self.tradedVolumeDict[localID]
                        del self.systemLocalDict[systemID]
                        del self.workingOrderDict[localID]

                    elif status == "CANCELED":
                        order.status = STATUS_CANCELLED

                        order.cancelTime = use_date + " " + now_time
                        self.gateway.onOrder(order)

                        del self.tradedVolumeDict[localID]
                        del self.systemLocalDict[systemID]
                        del self.workingOrderDict[localID]

                    # 部分成交
                    elif status == "PARTIALLY_FILLED":
                        order.status = STATUS_PARTTRADED
                        self.gateway.onOrder(order)

                    elif status == "NEW":
                        order.status = STATUS_NOTTRADED
                        self.gateway.onOrder(order)
            else:
                # 说明是以前发的单子

                symbol_pair =  systemSymbolToVnSymbol(use_order["symbol"])

                if status not in ["FILLED","CANCELED"]:
                    self.localID += 1
                    localID = str(self.localID)
                    order = VtOrderData()
                    order.gatewayName = self.gatewayName
                    order.symbol = symbol_pair + "." + self.gatewayName
                    order.exchange = EXCHANGE_BINANCE
                    order.vtSymbol = order.symbol
                    order.orderID = localID
                    order.vtOrderID = '.'.join([order.gatewayName,order.orderID])
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

    # ----------------------------------------------------------------------
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
    def onTradeOrder(self, data, req, reqID):
        symbol = systemSymbolToVnSymbol(data["symbol"])

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

        use_dt , use_date, now_time = self.generateDateTime(data["transactTime"])
        if status == "FILLED":
            order.status = STATUS_ALLTRADED
        elif status == "PARTIALLY_FILLED":
            order.status = STATUS_PARTTRADED
        elif status == "NEW":
            order.status = STATUS_NOTTRADED
        elif status == "CANCELED":
            order.status = STATUS_CANCELLED
            order.cancelTime = use_date + " " + now_time
        else:
            self.gateway.writeError( "%s new status" % EXCHANGE_BINANCE , "b20")

        if status in ["PARTIALLY_FILLED","FILLED"]:
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            trade.symbol = order.symbol
            trade.vtSymbol = order.vtSymbol

            self.tradeID += 1
            trade.tradeID = str(self.tradeID)
            trade.vtTradeID = '.'.join([trade.gatewayName,trade.tradeID])
            trade.orderID = order.orderID
            trade.vtOrderID =  order.vtOrderID

            trade.volume = float(volume)
            trade.price = order.price
            trade.direction = order.direction
            trade.offset = order.offset
            trade.exchange = order.exchange
            
            trade.tradeTime = use_date + " " + now_time

            self.gateway.onTrade(trade)

        self.tradedVolumeDict[localID] = volume
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
        order.cancelTime = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

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
