# encoding: UTF-8

'''
vnpy.api.okex的gateway接入
更新OKEX V3
By Chenzhipei
'''

import os
import json
from datetime import datetime, timedelta
from time import sleep
import time as td
from copy import copy
from threading import Condition
from queue import Queue
from threading import Thread
from time import sleep
import traceback
import ast
import zlib         # 新增解压功能

from vnpy.api.okex import WsSpotApi, WsFuturesApi, SPOT_SYMBOL_PAIRS, CONTRACT_SYMBOL, CONTRACT_TYPE, SPOT_CURRENCY
from vnpy.api.okex.okexData import SPOT_TRADE_SIZE_DICT, SPOT_REST_ERROR_DICT, SPORT_WS_ERROR_DICT, FUTURES_ERROR_DICT

from vnpy.api.okex.OkcoinFutureAPI import OKEX_FUTURE_HOST,OKCoinFuture
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath
from vnpy.trader.vtConstant import EXCHANGE_OKEX, DIRECTION_NET, PRODUCT_SPOT, DIRECTION_LONG, DIRECTION_SHORT, PRICETYPE_LIMITPRICE, PRICETYPE_MARKETPRICE, OFFSET_OPEN, OFFSET_CLOSE
from vnpy.trader.vtConstant import STATUS_CANCELING,STATUS_CANCELLED, STATUS_NOTTRADED, STATUS_PARTTRADED, STATUS_ALLTRADED, STATUS_UNKNOWN, STATUS_REJECTED, PRODUCT_FUTURES
from vnpy.trader.vtObject import VtErrorData

# 价格类型映射
# 买卖类型： 限价单（buy/sell） 市价单（buy_market/sell_market）
priceTypeMap = {}
priceTypeMap['buy'] = (DIRECTION_LONG, PRICETYPE_LIMITPRICE)
priceTypeMap['buy_market'] = (DIRECTION_LONG, PRICETYPE_MARKETPRICE)
priceTypeMap['sell'] = (DIRECTION_SHORT, PRICETYPE_LIMITPRICE)
priceTypeMap['sell_market'] = (DIRECTION_SHORT, PRICETYPE_MARKETPRICE)
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()}

priceContractOffsetTypeMap = {}
priceContractOffsetTypeMap['1'] = (DIRECTION_LONG, OFFSET_OPEN)
priceContractOffsetTypeMap['2'] = (DIRECTION_SHORT, OFFSET_OPEN)
priceContractOffsetTypeMap['3'] = (DIRECTION_SHORT, OFFSET_CLOSE)
priceContractOffsetTypeMap['4'] = (DIRECTION_LONG, OFFSET_CLOSE)
priceContractTypeMapReverse = {v: k for k, v in priceContractOffsetTypeMap.items()}

# 委托状态印射
statusMap = {}
statusMap[-1] = STATUS_CANCELLED    # 撤单
statusMap[0] = STATUS_NOTTRADED     # 未成交
statusMap[1] = STATUS_PARTTRADED    # 部分成交
statusMap[2] = STATUS_ALLTRADED     # 全部成交
statusMap[3] = STATUS_UNKNOWN
statusMap[4] = STATUS_UNKNOWN       # 未知状态
statusMap[5] = STATUS_CANCELING       # 撤销中
statusMap['open'] = STATUS_NOTTRADED
statusMap['cancelled'] = STATUS_CANCELLED
statusMap['filled'] = STATUS_ALLTRADED
statusMap['part_filled'] = STATUS_PARTTRADED

EVENT_OKEX_INDEX_FUTURE = "eFuture_Index_OKEX"


class OkexGateway(VtGateway):
    """OKEX交易接口"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='OKEX'):
        """Constructor"""
        super(OkexGateway, self).__init__(eventEngine, gatewayName)

        self.api_spot = OkexSpotApi(self)           # 现货交易接口
        self.api_futures = OkexFuturesApi(self)     # 期货交易接口

        self.apiKey = EMPTY_STRING
        self.secretKey = EMPTY_STRING
        self.passphrase = EMPTY_STRING
        self.leverage = 0
        self.spot_connected = False                 # 现货交易接口连接状态
        self.use_spot_symbol_pairs = set()          # 使用现货合约对（从配置文件读取，减少运算量）
        self.auto_subscribe_symbol_pairs = set()    # 自动订阅现货合约对清单
        self.auto_subscribe_future_symbols = set()  # 自动订阅期货合约清单

        self.futures_connected = False              # 期货交易接口连接状态

        self.qryCount = 0                           # 查询触发倒计时
        self.qryTrigger = 2                         # 查询触发点
        self.hbCount = 0                            # 心跳触发倒计时
        self.hbTrigger = 30                         # 心跳触发点

        # gateway 配置文件
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)
        self.log_message = False
        self.qryFunctionList = []

    def connect(self):
        """连接"""
        # 载入json文件
        try:
            f = open(self.filePath, 'r')
        except IOError:
            self.writeError(u'OkexGateway.connect:读取连接配置{}出错，请检查'.format(self.filePath))
            return
        setting = json.load(f)
        try:
            self.apiKey = str(setting['apiKey'])
            self.secretKey = str(setting['secretKey'])
            self.passphrase = str(setting['passphrase'])
            trace = setting['trace']
            self.leverage = setting.get('leverage', 1)
            spot_connect = setting['spot_connect']
            futures_connect = setting['futures_connect']
            self.log_message = setting.get('log_message', False)
            # 若限定使用的合约对
            if "symbol_pairs" in setting.keys():
                self.use_spot_symbol_pairs = set(setting["symbol_pairs"])
            # 若希望连接后自动订阅
            if 'auto_subscribe' in setting.keys():
                auto_subscribe = set(setting['auto_subscribe'])
                for symbol in auto_subscribe:
                    if ':' in symbol or 'SWAP' in symbol:
                        self.auto_subscribe_future_symbols.add(symbol)
                    else:
                        self.auto_subscribe_symbol_pairs.add(symbol)
            self.qryEnabled = setting.get('qryEnabled', True)
        except KeyError:
            self.writeError(u'OkexGateway.connect:连接配置缺少字段，请检查')
            return
        if spot_connect:
            self.api_spot.active = True
            for symbol_pair in self.auto_subscribe_symbol_pairs:
                self.writeLog(u'自动订阅现货合约:{}'.format(symbol_pair))
                self.api_spot.registerSymbolPairArray.add(symbol_pair)
            self.api_spot.connect(self.apiKey, self.secretKey,self.passphrase, trace)
            self.writeLog(u'connect okex ws spot api')
            self.api_spot.setSymbolPairs(self.use_spot_symbol_pairs)
        if futures_connect:
            self.api_futures.active = True
            self.api_futures.connect(self.apiKey, self.secretKey,self.passphrase, trace)
            self.writeLog(u'connect okex ws contract api')
            for future_symbol in self.auto_subscribe_future_symbols:
                self.writeLog(u'添加订阅期货合约:{}'.format(future_symbol))
                self.api_futures.registered_symbols.add(future_symbol)
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'接口初始化成功'
        self.onLog(log)
        # 启动查询
        self.initQuery()
        self.startQuery()

    def sendTransfer(self, symbol, amount, tfrom, tto):
        """
        转币操作
        :param symbol:
        :param amount:
        :param tfrom:
        :param tto:
        :return:
        """
        self.api_futures.sendTransfer(symbol, amount, tfrom, tto)

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

    def checkStatus(self):
        """
        检查接口运行状态
        :return:
        """
        if not self.spot_connected and not self.futures_connected:
            return False
        # if self.spot_connected:
        #     return self.api_spot.checkStatus()
        if self.futures_connected:
            return self.api_futures.checkStatus()

    def subscribe(self, subscribeReq):
        """
        订阅行情
        :param subscribeReq: VtSubscribeReq,
        :return:
        """
        try:
            symbol_pair_gateway = subscribeReq.symbol
            arr = symbol_pair_gateway.split('.')
            # 提取品种对 eth_usdt
            symbol_pair = arr[0]
            if symbol_pair.find('-USDT')>0:
                if self.api_spot and self.spot_connected:
                    self.api_spot.subscribe(subscribeReq)
                else:
                    self.writeError(u'现货接口未创建/未连接，无法调用subscribe')
                    self.auto_subscribe_symbol_pairs.add(symbol_pair)
            else:
                if self.api_futures and self.futures_connected:
                    self.api_futures.subscribe(subscribeReq)
                else:
                    self.writeError(u'期货接口未创建/未连接，无法调用subscribe')

        except Exception as ex:
            self.writeError(u'OkexGateway.subscribe 异常,请检查日志:{}'.format(str(ex)))
            self.writeLog(u'OkexGateway.subscribe Exception :{},{}'.format(str(ex), traceback.format_exc()))

    def sendOrder(self, orderReq):
        """发单"""
        order_req_symbol = orderReq.symbol
        order_req_symbol = order_req_symbol.replace('.{}'.format(EXCHANGE_OKEX),'')
        if order_req_symbol.split('-')[-1].isdigit() is False and order_req_symbol.endswith('SWAP') is False:
            if self.api_spot and self.spot_connected:
                return self.api_spot.spotSendOrder(orderReq)
            else:
                self.writeError(u'现货接口未创建/连接，无法调用sendOrder')
                return ''
        else:
            if self.api_futures and self.futures_connected:
                return self.api_futures.sendFutureSendOrder(orderReq)
            else:
                self.writeError(u'期货接口未创建/连接，无法调用sendOrder')
                return ''

    def checkOrderStatus(self, orderReq):
        """检查订单情况"""
        order_req_symbol = orderReq.symbol
        order_req_symbol = order_req_symbol.replace('.{}'.format(EXCHANGE_OKEX), '')
        if 'USDT' in order_req_symbol:
            if self.spot_connected:
                return self.api_spot.querySpotOrder(orderReq)
            else:
                self.writeError(u'现货接口未创建/连接，checkOrder')
        else:
            if self.futures_connected:
                return self.api_futures.queryFutureOrder(orderReq)
            else:
                self.writeError(u'期货接口未创建/连接，无法调用checkOrder')

    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        order_req_symbol = cancelOrderReq.symbol
        order_req_symbol = order_req_symbol.replace('.{}'.format(EXCHANGE_OKEX), '')
        if order_req_symbol.find('USDT') != -1:
            if self.spot_connected:
                self.api_spot.spotCancel(cancelOrderReq)
            else:
                self.writeError(u'现货接口未创建/连接，无法调用cancelOrder')
        else:
            if self.futures_connected:
                self.api_futures.sendFutureCancelOrder(cancelOrderReq)
            else:
                self.writeError(u'期货接口未创建/连接，无法调用cancelOrder')

    def qryAccount(self):
        """查询账户资金"""
        if self.spot_connected:
            self.api_spot.spotUserInfo()

        if self.futures_connected:
            self.api_futures.queryAllFutureAccountInfo()

    def qryOrderInfo(self):
        # if self.spot_connected:
        #     self.api_spot.spotAllOrders()
        #
        if self.futures_connected:
            # self.api_futures.queryAllFutureOrderInfo()
            pass

    def qryPosition(self):
        """查询持仓"""
        if self.futures_connected:
            self.api_futures.queryAllFuturePositionInfo()

    def close(self):
        """关闭"""
        if self.spot_connected:
            self.api_spot.active = False
            self.api_spot.close()
        if self.futures_connected:
            self.api_futures.active = False
            self.api_futures.close()

    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryAccount, self.qryOrderInfo, self.qryPosition]

            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 2         # 查询触发点
            self.qryNextFunction = 0    # 上次运行的查询函数索引

            self.startQuery()

    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.qryCount += 1
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

    def heartbeat(self,event):
        """
        心跳
        :return:
        """
        self.hbCount += 1
        if self.hbCount < self.hbTrigger:
            return
        # 清空倒计时
        self.hbCount = 0
        # 发送心跳请求
        if self.api_spot.active and self.spot_connected:
            self.api_spot.sendHeartBeat()

        if self.api_futures.active and self.futures_connected:
            self.api_futures.sendHeartBeat()

    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)
        # self.eventEngine.register(EVENT_TIMER, self.heartbeat)

    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled

    def onFutureIndexPush(self, push_dic):
        """
        合约指数更新事件
        :param push_dic:
        :return:
        """
        event1 = Event(type_=EVENT_OKEX_INDEX_FUTURE)
        event1.dict_['data'] = push_dic
        self.eventEngine.put(event1)

class WalletApi():
    pass


class OkexSpotApi(WsSpotApi):
    """okex的API实现"""

    def __init__(self, gateway):
        """Constructor"""
        super(WsSpotApi, self).__init__()

        self.gateway = gateway  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        self.active = False  # 若为True则会在断线后自动重连

        self.cbDict = {}        # 回调函数字典
        self.tickDict = {}      # 缓存最新tick字典
        self.orderDict = {}     # 委托单字典
        self.localOrderDict = {} # 本地缓存的order_dict，key 是 localNo.gatewayName
        self.clientorderDict = {}   #client_oid和orderId的对应,key是order_id
        self.channelSymbolMap = {}  # 请求数据类型与合约的映射字典

        self.localNo = 10000  # 本地委托号
        self.orderId = 1000000
        self.loginTime = 0
        self.localNoQueue = Queue()  # 未收到系统委托号的本地委托号队列
        self.localNoDict = {}  # key为本地委托号，value为系统委托号
        self.orderIdDict = {}  # key为系统委托号，value为本地委托号
        self.cancelDict = {}  # key为本地委托号，value为撤单请求

        self.recordOrderId_BefVolume = {}  # 记录的之前处理的量

        self.tradeID = 10000

        # 缺省启动得品种对队列
        self.use_symbol_pairs = set([])

        # 已登记的品种对队列
        self.registerSymbolPairArray = set([])

        # 初始化回调函数
        self.initCallback()

    def setSymbolPairs(self, symbol_pairs):
        """
        设置合约对
        :param symbol_pairs: set[]
        :return:
        """
        if isinstance(symbol_pairs,list):
            self.use_symbol_pairs = set(symbol_pairs)
        elif isinstance(symbol_pairs, set):
            self.use_symbol_pairs = symbol_pairs
        self.gateway.writeLog(u'设置合约对:{}'.format(symbol_pairs))

    def onMessage(self, *args):
        """
        响应信息处理，包括心跳响应、请求响应、数据推送
        :param ws: websocket接口
        :param evt: 消息体
        :return:
        """
        if len(args) == 0:
            return
        evt = args[-1]
        if isinstance(evt,bytes):
            # bytes => str => json
            decmp_evt = self.inflate(evt)
            ws_data = self.readData(decmp_evt)
        else:
            ws_data = self.readData(evt)

        if isinstance(ws_data, dict):
            if 'event' in ws_data:
                if ws_data['event'] == 'pong':
                    self.gateway.writeLog(u'heart beat response {}'.format(datetime.now()))
                    return
                if ws_data['event'] == 'login':
                    self.gateway.writeLog(u'现货接口连接成功')
                    self.onOpens()
                # else:
                #     self.gateway.writeLog(u'其他 event:{}'.format(ws_data))
            if 'table' in ws_data:
                if ws_data['table'].endswith('ticker'):
                    self.onTicker(ws_data['data'])
                if ws_data['table'].endswith('depth5'):
                    self.onDepth(ws_data['data'])
                if ws_data['table'].endswith('account'):
                    self.onSpotUserInfo(ws_data['data'])
                if ws_data['table'].endswith('order'):
                    self.onSpotSubOrder(ws_data['data'])
            if 'client_oid' in ws_data:
                self.onSpotOrder(ws_data)
        if isinstance(ws_data, list):
            for data in ws_data:
                if 'client_oid' in data:
                    self.onSpotOrderInfo(data)

    def onError(self, *args):
        """Api方法重载,错误推送"""
        if len(args)== 0:
            return
        evt = args[-1]
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        error.errorID = 0
        if isinstance(evt, bytes):
            decom_evt = self.inflate(evt)
            error.errorMsg = str(decom_evt)
        else:
            error.errorMsg = str(evt)
        self.gateway.onError(error)

    def onErrorMsg(self, data):
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        if 'data' in data and 'error_code' in data['data']:
            error_code =data['data']['error_code']
            error.errorMsg = u'SpotApi 出错:{}'.format(SPORT_WS_ERROR_DICT.get(str(error_code)))
            error.errorID = error_code
        else:
            error.errorMsg = str(data)
        self.gateway.onError(error)

    def onClose(self, *args):
        """
        断开接口
        :param ws: websocket
        :return:
        """
        # 如果尚未连上，则忽略该次断开提示
        if not self.gateway.spot_connected:
            self.gateway.writeLog(u'spot接口未连接，忽略断开提示')
            return
        self.gateway.spot_connected = False
        self.gateway.writeLog(u'Spot服务器连接断开')
        # 重新连接
        if self.active:
            def reconnect():
                while not self.gateway.spot_connected:
                    self.gateway.writeLog(u'等待10秒后重新连接')
                    sleep(10)
                    if not self.gateway.spot_connected:
                        self.reconnect()
            t = Thread(target=reconnect)
            t.start()

    def subscribe(self, subscribeReq):
        """
        订阅行情
        :param subscribeReq:
        :return:
        """
        self.gateway.writeLog(u'SpotApi.subscribe({})'.format(subscribeReq.symbol))
        symbol_pair_gateway = subscribeReq.symbol
        arr = symbol_pair_gateway.split('.')
        symbol_pair = arr[0]
        # 若品种对未登记过添加登记品种对
        if symbol_pair not in self.registerSymbolPairArray:
            self.registerSymbolPairArray.add(symbol_pair)
        self.subscribeSingleSymbol(symbol_pair)
        self.spotOrderInfo(symbol_pair)

    def subscribeSingleSymbol(self, symbol):
        """
        订阅合约（对）
        :param symbol:合约（对）
        :return:
        """
        self.gateway.writeLog(u'SpotApi.subscribeSingleSymbol({})'.format(symbol))
        self.subscribeSpotTicker(symbol)
        self.subscribeSpotDepth(symbol)
        self.subscribeSpotTrades(symbol)
        self.spotOrderInfo(symbol)

    def spotAllOrders(self):
        """
        查询所有委托清单
        :return:
        """
        # self.gateway.writeLog('SpotApi.spotAllOrders()')
        #
        # # 根据已登记的品种对清单，逐一发委托查询
        # for symbol in self.registerSymbolPairArray:
        #     if symbol in SPOT_SYMBOL_PAIRS:
        #         self.spotOrderInfo(symbol, '-1')
        pass

    def onOpen(self, *args):
        """
        ws连接成功事件回调函数
        :param ws:
        :return:
        """
        self.gateway.spot_connected = True
        self.gateway.writeLog(u'Spot服务器连接成功')
        self.loginTime = int(datetime.now().strftime('%y%m%d%H%M%S'))*self.orderId
        self.login()

    def onOpens(self):
        """
        登录成功后，进行一系列查询过程
        :return:
        """
        for symbol_pair in list(self.registerSymbolPairArray):
            self.subscribeSingleSymbol(symbol_pair)
            self.spotUserInfo()

    def onSpotSubDeals(self, ws_data):
        """
        当前现货委托成交信息回报
        :param ws_data:
        :return:
        """
        self.gateway.writeLog(u'SpotApi.onSpotSubDeals:{}'.format(ws_data))

    def initCallback(self):
        """
        初始化回调函数
        :return:
        """
        pass

    def checkStatus(self):
        """
        检查状态
        :return:
        """
        if len(self.tickDict)>0:
            symbol,last_tick = list(self.tickDict.items())[0]
            if (datetime.now()-last_tick.datetime).seconds > 60:
                return False
            return True
        else:
            return False

    def onTicker(self, ws_data):
        """
        tick行情数据回报
        :param ws_data: dict
        :return:
        """
        data = ws_data[0]
        try:
            symbol = data['instrument_id']
            if symbol not in self.tickDict:
                tick = VtTickData()
                tick.exchange = EXCHANGE_OKEX
                tick.symbol = symbol
                tick.vtSymbol = symbol
                tick.gatewayName = self.gatewayName
                self.tickDict[symbol] = tick
            else:
                tick = self.tickDict[symbol]
            tick.highPrice = float(data['high_24h'])
            tick.lowPrice = float(data['low_24h'])
            tick.lastPrice = float(data['last'])
            tick.volume = float(data['base_volume_24h'].split('.')[0])
        except Exception as ex:
            self.gateway.writeError(u'SpotApi.onTicker异常')
            self.gateway.writeLog('SpotApi.onTicker exception:{},{} '.format(str(ex), traceback.format_exc()))

    def onDepth(self, ws_data):
        """
        :param ws_data:
        :return:
        """
        data = ws_data[0]
        symbol = data['instrument_id']
        # 更新tick
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.symbol = symbol
            tick.vtSymbol = symbol
            tick.gatewayName = self.gatewayName
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]
        tick.bidPrice1, tick.bidVolume1 = data['bids'][0][0:2]
        tick.bidPrice2, tick.bidVolume2 = data['bids'][1][0:2]
        tick.bidPrice3, tick.bidVolume3 = data['bids'][2][0:2]
        tick.bidPrice4, tick.bidVolume4 = data['bids'][3][0:2]
        tick.bidPrice5, tick.bidVolume5 = data['bids'][4][0:2]

        tick.askPrice1, tick.askVolume1 = data['asks'][0][0:2]
        tick.askPrice2, tick.askVolume2 = data['asks'][1][0:2]
        tick.askPrice3, tick.askVolume3 = data['asks'][2][0:2]
        tick.askPrice4, tick.askVolume4 = data['asks'][3][0:2]
        tick.askPrice5, tick.askVolume5 = data['asks'][4][0:2]

        tick.bidPrice1, tick.bidVolume1 = float(tick.bidPrice1), float(tick.bidVolume1)
        tick.bidPrice2, tick.bidVolume2 = float(tick.bidPrice2), float(tick.bidVolume2)
        tick.bidPrice3, tick.bidVolume3 = float(tick.bidPrice3), float(tick.bidVolume3)
        tick.bidPrice4, tick.bidVolume4 = float(tick.bidPrice4), float(tick.bidVolume4)
        tick.bidPrice5, tick.bidVolume5 = float(tick.bidPrice5), float(tick.bidVolume5)
        tick.askPrice1, tick.askVolume1 = float(tick.askPrice1), float(tick.askVolume1)
        tick.askPrice2, tick.askVolume2 = float(tick.askPrice2), float(tick.askVolume2)
        tick.askPrice3, tick.askVolume3 = float(tick.askPrice3), float(tick.askVolume3)
        tick.askPrice4, tick.askVolume4 = float(tick.askPrice4), float(tick.askVolume4)
        tick.askPrice5, tick.askVolume5 = float(tick.askPrice5), float(tick.askVolume5)

        tick.date, tick.time,tick.datetime = self.generateDateTime(data['timestamp'])
        tick.tradingDay = tick.date
        if tick.lastPrice == 0 and tick.askPrice1 != 0 and tick.bidPrice1 != 0:
            tick.lastPrice = (tick.askPrice1 + tick.bidPrice1) / 2
        if tick.lastPrice == 0 or tick.askPrice1 == 0 or tick.bidPrice1 == 0:
            print('onDepth drop tick {},lastprice:{},askprice1={},bidPrice1:{}'
                  .format(tick.vtSymbol, tick.lastPrice, tick.askPrice1, tick.bidPrice1))
            return
        newtick = copy(tick)

        self.gateway.onTick(newtick)

    def onSpotBalance(self, ws_data):
        """
        现货账号更新回报
        交易发生金额变动之后会触发这个回报
        :param data:
        :return:
        """
        # print data
        data = ws_data.get('data')
        if data is None:
            self.gateway.writeError(u'SpotApi.onSpotBalance, no data in ws_data')
            return
        data_info = data.get('info')
        if data_info is None:
            self.gateway.writeError(u'SpotApi.onSpotBalance, no info in data')
            return
        data_info_free = data_info.get('free', {})          # 可用资产
        data_info_freezed = data_info.get('freezed')                # 冻结资产
        if data_info_freezed is None or not isinstance(data_info_freezed, dict):
            self.gateway.writeError(u'SpotApi.onSpotBalance, no freezed in data_info')
            self.gateway.writeLog(ws_data)
            return
        # 只更新freezed内容
        for symbol, position in data_info_freezed.items():
            pos = VtPositionData()
            pos.gatewayName = self.gatewayName
            pos.symbol = symbol   + "." + EXCHANGE_OKEX
            pos.vtSymbol = symbol + "." + EXCHANGE_OKEX
            pos.vtPositionName = symbol + u'[现货]'
            pos.direction = DIRECTION_NET
            pos.frozen = float(position)
            pos.position = pos.frozen + float(data_info_free.get(symbol, 0))
            self.gateway.onPosition(pos)


    def onSpotUserInfo(self, ws_data):
        """现货账户资金推送"""
        if isinstance(ws_data, str):
            ws_data = json.loads(ws_data)
        for data in ws_data:
            account = VtAccountData()
            account.gatewayName = self.gatewayName
            account.accountID = data['currency']
            account.vtAccountID = data['currency'] + ".{}".format(EXCHANGE_OKEX)
            account.balance = float(data['balance'])
            self.gateway.onAccount(account)

    def onSpotSubUserInfo(self, ws_data):
        """
        现货子账户资金推送
        :param ws_data:
        :return:
        """
        if 'data' not in ws_data or 'info' not in ws_data['data'] or 'funds' not in ws_data['data']['info']:
            self.gateway.writeError(u'SpotApi.onSpotSubUserInfo 数据不完整,请检查日志')
            self.gateway.writeLog(ws_data)
            return
        data = ws_data.get('data')
        data_info = data.get('info')
        # 持仓信息
        for symbol in SPOT_CURRENCY:
            if symbol in data_info['free']:
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName
                pos.symbol = symbol         # + "." + EXCHANGE_OKEX
                pos.vtSymbol = symbol       #+ "." + EXCHANGE_OKEX
                pos.vtPositionName = symbol
                pos.direction = DIRECTION_NET
                pos.frozen = float(data_info['freezed'][symbol])
                pos.position = pos.frozen + float(data_info['free'][symbol])
                self.gateway.onPosition(pos)

    def onSpotSubOrder(self, ws_data):
        """
        交易委托更新回报（发生部分成交/全部成交/拒单/撤销时，API推送的回报)
        :param ws_data:ws推送的单个委托更新数据
        :return:
        """
        data = ws_data[0]
        if 'client_oid' in data:
            if data['client_oid'] is not '' and data['client_oid'] is not '0':
                orderId = str(data['client_oid'])
            else:
                orderId = str(data['order_id'])
                self.clientorderDict[orderId] = str(data['order_id'])
        else:
            orderId = self.clientorderDict[data['order_id']]
        if orderId not in self.orderIdDict:
            while str(self.localNo) in self.localNoDict:
                self.localNo += 1
            localNo = str(self.localNo)
            self.localNoDict[localNo] = orderId
            self.orderIdDict[orderId] = localNo
            self.gateway.writeLog(u'onFutureOrderInfo add orderid: local:{}<=>okex:{}'.format(localNo, orderId))
        if orderId not in self.orderDict:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            order.symbol = data['instrument_id']
            order.vtSymbol = order.symbol
            order.orderID = orderId
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            order.price = float(data['price'])
            order.totalVolume = float(data['size'])
            order.direction, priceType =data['side'],'limit'
            order.offset = OFFSET_OPEN
            create_date, order.orderTime,_ = self.generateDateTime(data['timestamp'])
            self.orderDict[orderId] = order
        else:
            order = self.orderDict[orderId]
        order.tradedVolume = float(data['filled_size'])
        order.status = statusMap[data['status']]
        if order.status == STATUS_CANCELLED:
            dt = datetime.now()
            order.cancelTime = dt.strftime("%H:%M:%S.%f")
        self.gateway.writeLog(u'onSpotSubOrder:发出OnOrder，vtOrderId={},orderStatus:{}'.format(order.vtOrderID,order.status))
        self.gateway.onOrder(copy(order))
        bef_volume = self.recordOrderId_BefVolume.get(orderId, 0.0)
        now_volume = float(data['filled_size']) - bef_volume
        if now_volume > 0.000001:
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            trade.symbol = order.symbol
            trade.vtSymbol = order.symbol
            self.tradeID += 1
            trade.tradeID = str(self.tradeID)
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
            trade.orderID = orderId
            trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
            trade.price = float(data['filled_notional'])/float(data['filled_size'])
            trade.volume = float(now_volume)
            trade.direction, priceType = data['side'],'limit'
            trade.tradeTime = datetime.now().strftime('%H:%M:%S')
            self.gateway.writeLog(u'onSpotSubOrder:发出onTrader，vtOrderId={}'.format(trade.vtOrderID))
            self.gateway.onTrade(trade)

    def onSpotOrderInfo(self, ws_data):
        """
        所有委托信息查询响应
        self.spotOrderInfo(symbol_pair, '-1')时，返回symbol_pair所有未完成订单
        self.spotOrderInfo(symbol_pair, orderId)时，返回symbol_pair、orderId的订单
        :param ws_data：orders 清单
        :return:
        """
        self.gateway.writeLog(u'SpApi.onSpotOrderInfo:{}'.format(ws_data))

        # 获取channel的数据
        data = ws_data
        # 获取所有返回的委托单清单

        if data['client_oid'] is not '0' and data['client_oid'] is not '':
            orderId = str(data['client_oid'])
            self.clientorderDict[ws_data['order_id']] = orderId

        else:
            orderId = str(data['order_id'])
            self.clientorderDict[ws_data['order_id']] = orderId
            localNo = str(self.localNo)

        if orderId not in self.orderIdDict:
            while str(self.localNo) in self.localNoDict:
                self.localNo += 1

            localNo = str(self.localNo)
                # 绑定localNo 与 orderId
            self.localNoDict[localNo] = orderId
            self.orderIdDict[orderId] = localNo
        else:
                # orderid在本地缓存中，
            localNo = self.orderIdDict[orderId]
                # 检验 localNo是否在本地缓存，没有则补充
            if localNo not in self.localNoDict:
                self.localNoDict[localNo] = orderId
                self.gateway.writeLog(u'onFutureOrderInfo update orderid: local:{}<=>okex:{}'.format(localNo, orderId))

        if orderId not in self.orderDict:
            # 不在本地委托单缓存时，添加
            self.gateway.writeLog(u'onSpotOrderInfo:添加至委托单缓存:{}'.format(orderId))
            order = VtOrderData()
            order.gatewayName = self.gatewayName
                # order.symbol = spotSymbolMap[d['symbol']]
            order.symbol =data['instrument_id']
            order.vtSymbol = order.symbol

            order.orderID = orderId
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])

            order.price = float(data['price'])
            order.totalVolume = int(data['size'])
            order.direction, priceType = data['side'],'现货开仓'
            create_date, order.orderTime,_ = self.generateDateTime(data['created_at'])
            self.orderDict[orderId] = order
        else:
            order = self.orderDict[orderId]                 # 使用本地缓存

        order.tradedVolume = int(data['filled_size'])      # 更新成交数量
        order.status = data['status']      # 更新成交状态
        self.gateway.writeLog('orderId:{},tradedVolume:{},status:{}'.format(order.vtOrderID,order.tradedVolume,order.status))
        self.gateway.onOrder(copy(order))                   # 提交现货委托单到vtGatway.onOrder事件

    def onSpotOrder(self, ws_data):
        """
        交易委托回报
        :param ws_data:
        :return:
        """
        client_oid = ws_data.get('client_oid')
        if client_oid is not '':
            self.clientorderDict[ws_data['order_id']] = client_oid
        vtOrderId = '.'.join([self.gatewayName,str(client_oid)])
        order = self.localOrderDict.get(vtOrderId)
        if order:
            order.orderID = client_oid
            order.symbol = '.'.join([order.symbol, self.gatewayName])
            order.vtsymbol = order.symbol
            order.status = STATUS_NOTTRADED
            order.updateTime = datetime.now().strftime("%H:%M:%S.%f")
            order.totalVolume=order.totalVolume
            self.gateway.onOrder(order)
            return

    def onSpotCancelOrder(self, ws_data):
        """
        撤单请求回报
        :param ws_data:
        :return:
        """
        self.gateway.writeLog(u'SpotApi.onSpotCancelOrder()')
        data = ws_data.get('data', {})
        if 'error_code' in data:
            error_id = data.get('error_code')
            self.gateway.writeError(u'SpotApi.onSpotCancelOrder 委托返回错误:{}'.format(SPORT_WS_ERROR_DICT.get(str(error_id))), error_id=error_id)
            self.gateway.writeLog(ws_data)
            return
        ok_order_id = data.get('order_id')
        ok_result = data.get('result',False)
        if ok_order_id is None:
            self.gateway.writeError(u'SpotApi.onSpotCancelOrder 委托返回中，没有order_id')
            self.gateway.writeLog(ws_data)
            return
        if not ok_result:
            self.gateway.writeError(u'SpotApi.onSpotCancelOrder 撤单失败')
            self.gateway.writeLog(ws_data)
            return
        ok_order_id = str(ok_order_id)
        localNo = self.orderIdDict[ok_order_id]
        if ok_order_id not in self.orderDict:
            self.gateway.writeLog(u'onSpotCancelOrder,{}的订单不在self.orderDict,创建order对象'.format(ok_order_id))
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            order.symbol = '.'.join([data['symbol'], EXCHANGE_OKEX])
            order.vtSymbol = order.symbol
            order.orderID = localNo
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            self.orderDict[ok_order_id] = order
        else:
            order = self.orderDict[ok_order_id]
        order.status = STATUS_CANCELLED
        dt = datetime.now()
        order.cancelTime = dt.strftime("%H:%M:%S.%f")
        # 发送现货委托单（撤单消息）到vtGateway
        self.gateway.onOrder(order)

    def spotSendOrder(self, req):
        """
        发出委托指令
        :param req:
        :return:
        """
        self.gateway.writeLog(u'SpotApi.spotSendOrder()')
        symbol = (req.symbol.split('.'))[0]
        symbol = symbol.lower()
        if not symbol in self.registerSymbolPairArray:
            self.registerSymbolPairArray.add(symbol)

        # 获取匹配okex的订单类型
        type_ = priceTypeMapReverse[(req.direction, req.priceType)]

        # 本地委托号加1，并将对应字符串保存到队列中，返回基于本地委托号的vtOrderID
        # self.localNo += 1
        self.orderId += 1
        # self.gateway.writeLog(u'localNo:{}'.format(self.localNo))
        # self.localNoQueue.put(str(self.localNo))
        orderId = 'Spot'+ str(self.loginTime + self.orderId)
        vtOrderID = '.'.join([self.gatewayName, orderId])
        self.gateway.writeLog(u'创建本地Order对象，vtOrderId:{}'.format(vtOrderID))

        # 创建本地order对象
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = symbol
        order.vtSymbol = order.symbol
        order.orderID = orderId
        order.vtOrderID = vtOrderID
        order.price = req.price
        order.totalVolume = req.volume
        # order.direction, priceType = priceTypeMap[type_]
        order.direction = req.direction
        order.offset = OFFSET_OPEN if req.direction == DIRECTION_LONG else OFFSET_CLOSE
        order.status = STATUS_NOTTRADED
        dt = datetime.now()
        order.orderTime = dt.strftime("%H:%M:%S.%f")
        self.localOrderDict[vtOrderID] = order
        if order.direction == DIRECTION_LONG:
            type_ = 'buy'
        if order.direction == DIRECTION_SHORT:
            type_ = 'sell'
        # 调用ws api发送委托
        self.gateway.writeLog(u'调用ws api发送委托')
        self.spotTrade(symbol, type_, str(req.price), str(req.volume),orderId)
        self.gateway.writeLog('SpotSendOrder:symbol:{},Type:{},price:{},volume:{}'.format(symbol, type_, str(req.price), str(req.volume)))

        return vtOrderID

    def spotCancel(self, req):
        """
        发出撤单指令
        :param req:
        :return:
        """
        symbol = (req.symbol.split('.'))[0]
        localNo = req.orderID
        self.spotCancelOrder(symbol, localNo)
        # else:
        #     # 如果在系统委托号返回前客户就发送了撤单请求，则保存
        #     # 在cancelDict字典中，等待返回后执行撤单任务
        #     self.cancelDict[localNo] = req

    def generateDateTime(self, s):
        """生成时间"""
        s = s.split('.')[0]
        s = s.split('T')[0]+u' '+s.split('T')[1]
        s = td.mktime(td.strptime(s, "%Y-%m-%d %H:%M:%S"))
        s = s + 60*60*8
        dt = datetime.fromtimestamp(s)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return date, time,dt


class OkexFuturesApi(WsFuturesApi):
    """okex的合约API实现"""

    def __init__(self, gateway):
        """Constructor"""
        super(OkexFuturesApi, self).__init__() #TODO????

        self.gateway = gateway  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        self.active = False  # 若为True则会在断线后自动重连
        self.cbDict = {}
        self.tickDict = {}
        self.orderDict = {}
        self.localOrderDict = {}  # 本地缓存的order_dict，key 是 localNo.gatewayName
        self.channelSymbolMap = {}
        # self.orderId = 1000000 #
        self.loginTime = 0
        self.localNo = 0  # 本地委托号
        self.localNoQueue = Queue()  # 未收到系统委托号的本地委托号队列
        self.localNoDict = {}  # key为本地委托号，value为系统委托号
        self.orderIdDict = {}  # key为系统委托号，value为本地委托号
        self.cancelDict = {}  # key为本地委托号，value为撤单请求

        self.recordOrderId_BefVolume = {}  # 记录的之前处理的量
        self.tradeID = 0
        self.registered_symbols = set([])
        self.queryed_pos_symbols = set([])
        self._use_leverage = "10"           # 缺省使用的杠杆比率

        self.bids_depth_dict = {}
        self.asks_depth_dict = {}
        self.contract_name_dict = {}
        self.contractIdToSymbol = {}

        self.CONTRACT_SYMBOL_SWAP = ["BTC-USD-SWAP", "ETH-USD-SWAP", "EOS-USD-SWAP", "ETC-USD-SWAP", "LTC-USD-SWAP"]

    def queryFutureOrder(self, orderReq):
        """

        :param orderReq:
        :return:
        """
        orderID = orderReq.orderID
        symbol = orderReq.symbol
        return self.queryFutureOrderStatus(symbol, orderID)

    def treatFutureOrderStatus(self, response):
        if response == {}:
            return STATUS_CANCELLED
        else:
            index = response['status']
            orderIndex = {'-1':STATUS_CANCELLED, '0':STATUS_NOTTRADED, '1':STATUS_PARTTRADED, '2':STATUS_ALLTRADED}
            return orderIndex[index]

    def queryFutureAccount(self):
        """

        :return:
        """
        for symbol in self.registered_symbols:
            symbol = self.dealSymbolFunc(symbol)[1]
            self.queryFuturesAccountInfo(symbol)

    def setLeverage(self, __leverage):
        """
        设置杠杆比率
        :param __leverage:
        :return:
        """
        self._use_leverage = __leverage

    def onMessage(self, *args):
        """
        信息推送的处理
        :param ws:
        :param evt:
        :return:
        """
        # self.onClose()
        if len(args)==0:
            return
        evt = args[-1]
        if isinstance(evt,bytes):
            decmp_evt = self.inflate(evt) # bytes => str => json
            ws_data = self.readData(decmp_evt)
        else:
            ws_data = self.readData(evt)
        if self.gateway.log_message:
            self.gateway.writeLog(u'FutureApi.onMessage:{}'.format(ws_data))
        if isinstance(ws_data, dict):
            if 'event' in ws_data:
                if ws_data['event'] == 'pong':
                    # TODO：设置重连机制
                    return
                elif ws_data['event'] == 'login':
                    self.writeLog(u'期货接口登陆成功')
                    self.onOpens()
                # else:
                    # self.gateway.writeLog(ws_data)
            elif 'table' in ws_data:
                if ws_data['table'].endswith('ticker'):
                    self.onTicker(ws_data['data'])
                elif ws_data['table'].endswith('depth5'):
                    self.onDepth(ws_data['data'])
                elif ws_data['table'].endswith('account'):
                    self.onFutureAccountInfo(ws_data['data'])
                elif ws_data['table'].endswith('position'):
                    self.onFuturePositionInfo(ws_data['data'])
                elif ws_data['table'].endswith('order'):
                    self.onFutureTrades(ws_data['data'])
            elif 'client_oid' in ws_data:  # 委托后发送回应
                self.treatRespondFutureOrder(ws_data)
            else: # 报错信息 35008
                self.gateway.writeLog(u'很烦很烦')
                self.gateway.writeLog(ws_data)
        else:
            self.gateway.writeLog(u'其他信息')
            self.gateway.writeLog(ws_data)

    def onError(self, *args):
        """重载WsFutureApi.onError错误Event推送"""
        if len(args)== 0:
            return
        evt = args[-1]
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        if isinstance(evt,bytes):
            decom_evt = self.inflate(evt)
            error.errorMsg = str(decom_evt)
        else:
            error.errorMsg = str(evt)
        self.gateway.onError(error)

    def onErrorMsg(self, data):
        """错误信息处理"""
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        if 'data' in data and 'error_code' in data['data']:
            error_code = str(data["data"]["error_code"])
            error.errorID = error_code
            error.errorMsg = u'FutureApi Error:{}'.format(FUTURES_ERROR_DICT.get(error_code))
            self.gateway.onError(error)

    def reconnect(self):
        """
        重连
        :return:
        """
        while not self.gateway.futures_connected:
            self.writeLog(u'okex Api_contract 等待10秒后重新连接')
            self.connect(self.apiKey, self.secretKey, self.passphrase, self.trace)
            sleep(10)
            if not self.gateway.futures_connected:
                self.reconnect()

    def writechaLog(self, content):
        """

        :param content:
        :return:
        """
        self.writeLog(content)

    def onClose(self):
        """接口断开"""
        # 如果尚未连上，则忽略该次断开提示
        if not self.gateway.futures_connected:
            return
        self.gateway.futures_connected = False
        self.writeLog(u'期货服务器连接断开')
        # 重新连接
        if self.active:
            self.writeLog(u'重新连接期货服务器')
            t = Thread(target=self.reconnect)
            t.start()

    def dealSymbolFunc(self, symbol):
        """
        分解委托单symbol
        :param symbol:
        :return:
        """
        if symbol.find(':') == -1:
            symbol_pair = symbol
            symbol = symbol
            contract_type = 'this_week'
            leverage = '10'
            return (symbol_pair, symbol, contract_type, leverage)
        arr = symbol.split('.')
        symbol_pair = arr[0]
        l = symbol_pair.split(':')
        if len(l) !=3:
            self.gateway.writeError(u'合约代码{}错误:'.format(symbol))
            raise ValueError(u'合约代码{}错误:'.format(symbol))
        symbol, contract_type, leverage = l[0], l[1], l[2]
        if contract_type not in CONTRACT_TYPE:
            self.gateway.writeError(u'合约类型错误:{}'.format(contract_type))
            raise ValueError(u'合约类型{}不在:{}中'.format(contract_type,CONTRACT_TYPE))
        symbol = symbol.replace("_usd", "")

        return (symbol_pair, symbol, contract_type, leverage)

    def subscribe(self, subscribeReq):
        """
        订阅行情,外接okexGateway, 在vtEngine中的dataEngine进行调用
        :param subscribeReq:
        :return:
        """
        self.subscribeSingleSymbol(subscribeReq.symbol)

    def subscribeSingleSymbol(self, symbol):
        """
        订阅单个对象的行情（Ticker, depth, Trade)
        :param symbol: 合约，如btc，eth，etc等
        :param contract_type: 合约类型，当周，下周，季度
        :param leverage:杠杆倍数
        :return:
        """
        self.subsribeFutureTicker(symbol)
        self.subscribeFutureDepth(symbol)
        self.subscribeFutureTrades(symbol)
        self.queryFutureOrderInfo(symbol, status="6", current_page=1, page_length=50)

    def treatFutureOrderInfo(self, symbol_pair, message):
        """
        处理函数：用于处理查询订单返回来的信息
            1.重新设定本地单子
        :param message:
        :return:
        """
        if message['order_info'] == []:
            return
        orders = message['order_info']
        if orders == []:
            self.gateway.writeLog(u'{}目前没有订单信息'.format(symbol_pair))
            return
        for tmp_order in orders:
            if tmp_order['client_oid'] == '': # 不是我们的订单
                return
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            order.symbol = tmp_order['instrument_id']
            order.vtSymbol = '{}.'.format(self.gatewayName) + tmp_order['instrument_id']
            order.orderID = tmp_order['client_oid'] # 用户设置的订单ID
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            order.price = float(tmp_order['price'])
            order.totalVolume = int(tmp_order['size'])
            order.tradedVolume = int(tmp_order['filled_qty'])
            order.direction, order.offset = priceContractOffsetTypeMap[str(tmp_order['type'])]
            order.status = statusMap[int(tmp_order['status'])]

            self.orderDict[order.orderID] = order # 重新订阅本地订单
            self.gateway.onOrder(order)

    def onOpen(self):
        """
        连接
        1.设置回调函数
        2.设置合约信息
        3.
        """
        self.writeLog(u'服务器OKEX期货————onOpen')
        self.gateway.futures_connected = True
        self.loginTime = int(datetime.now().strftime('%y%m%d%H%M%S')) * 10000
        try:
            self.initCallback()
            for symbol in CONTRACT_SYMBOL:
                for use_contract_type in CONTRACT_TYPE:
                    for key, items in self.contractInfo.items():
                        if symbol in key and use_contract_type==items:
                            use_symbol_name = key
                            contract = VtContractData()
                            contract.gatewayName = self.gatewayName
                            contract.symbol = use_symbol_name
                            contract.exchange = EXCHANGE_OKEX
                            contract.vtSymbol = use_symbol_name  + "." + EXCHANGE_OKEX
                            contract.productClass = PRODUCT_FUTURES
                            self.gateway.onContract(contract)
            for symbol in self.CONTRACT_SYMBOL_SWAP:
                contract = VtContractData()
                contract.gatewayName = self.gatewayName
                contract.symbol = symbol
                contract.exchange = EXCHANGE_OKEX
                contract.vtSymbol = symbol + "." + EXCHANGE_OKEX
                contract.productClass = PRODUCT_FUTURES
                self.gateway.onContract(contract)
            self.login()
            self.subFutureAllIndexSymbol()
        except Exception as ex:
            self.gateway.writeError(u'期货onOpen异常:{},{}'.format(str(ex), traceback.format_exc()))

    def onOpens(self):
        """
        客户端登录成功后，用于订阅行情
        :return:
        """
        for symbol in self.registered_symbols:
            try:
                (symbol_pair, symbol, contract_type, leverage) = self.dealSymbolFunc(symbol)
                self.subscribeSingleSymbol(symbol)
                self.subFutureUserInfo(symbol)
                self.subFuturePositionInfo(symbol)
                self.queryFuturesAccountInfo(symbol)
                self.queryFuturePosition(symbol)
            except Exception as ex:
                self.gateway.writeError(u'订阅合约行情异常:{},{}'.format(str(ex), traceback.format_exc()))
                continue

    def queryAllFutureAccountInfo(self):
        """
        查询订阅品种的账户信息
        :return:
        """
        for symbol in self.registered_symbols:
            (symbol_pair, symbol, contract_type, leverage) = self.dealSymbolFunc(symbol)
            self.queryFuturesAccountInfo(symbol)

    def queryAllFuturePositionInfo(self):
        """
        查询订阅品种的持仓信息
        :return:
        """
        for symbol in self.registered_symbols:
            (symbol_pair, symbol, contract_type, leverage) = self.dealSymbolFunc(symbol)
            self.queryFuturePosition(symbol)

    def queryAllFutureOrderInfo(self):
        """
        查询订阅品种的未完成订单信息
        :return:
        """
        for symbol in self.registered_symbols:
            (symbol_pair, symbol, contract_type, leverage) = self.dealSymbolFunc(symbol)
            self.queryFutureOrderInfo(symbol, status="6", current_page=1, page_length=50)

    def treatFutureAccountInfo(self, message, symbol):
        """
        处理函数：用于处理查询账户信息返回来的信息
        :param symbol:
        :param message:
        :return:
        """
        if message == []:
            return
        accountInfo = VtAccountData()
        accountInfo.accountID = symbol
        accountInfo.gatewayName = self.gatewayName
        if 'SWAP' in symbol:
            accountInfo.balance = float(message['info']['equity']) # 权益
            accountInfo.available = float(message['info']['total_avail_balance'])  # 账户余额
            accountInfo.closeProfit = float(message['info']['realized_pnl'])
            accountInfo.positionProfit = float(message['info']['unrealized_pnl'])
        else:
            margin_mode = message['margin_mode']
            if margin_mode == 'crossed':
                accountInfo.available = float(message['total_avail_balance']) # 账户余额
                accountInfo.balance = float(message['equity']) # 权益
                accountInfo.closeProfit = float(message['realized_pnl'])
                accountInfo.positionProfit = float(message['unrealized_pnl'])
            else:
                accountInfo.available = float(message['total_avail_balance']) # 账户余额
                accountInfo.balance = float(message['equity']) # 权益
        self.gateway.onAccount(accountInfo)

    def treatFuturePositionInfo(self, message, symbol):
        """
        处理函数：用于处理持仓信息查询返回的内容
        :param message:
        :param symbol:
        :return:
        """
        # TODO 设置能检测的东西
        data = message['holding'][0]
        if 'SWAP' not in symbol:
            if 'crossed' in data: # 全仓
                # if len(message['holding']) == 0:
                #     self.gateway.writeLog(u'没有仓位')
                #     return
                # data = message['holding'][0]
                # Long
                pos = VtPositionData()
                pos.position = float(data['long_qty'])
                if pos.position != 0:
                    pos.gatewayName = self.gatewayName
                    pos.symbol = data['instrument_id']
                    pos.vtSymbol = self.gatewayName + '.' + pos.symbol
                    pos.price = float(data['long_avg_cost'])
                    pos.direction = DIRECTION_LONG
                    pos.leverage = int(data['leverage'])
                    pos.margin_mode = data['margin_mode']
                    pos.positionProfit = data['realised_pnl']
                    self.gateway.onPosition(pos)
                # Short
                pos = VtPositionData()
                pos.position = float(data['short_qty'])
                if pos.position != 0:
                    pos.gatewayName = self.gatewayName
                    pos.symbol = data['instrument_id']
                    pos.vtSymbol = self.gatewayName + '.' + pos.symbol
                    pos.price = float(data['short_avg_cost'])
                    pos.direction = DIRECTION_SHORT
                    pos.leverage = int(data['leverage'])
                    pos.margin_mode = data['margin_mode']
                    pos.positionProfit = data['realised_pnl']
                    self.gateway.onPosition(pos)
            else: # 逐仓
                # Long
                pos = VtPositionData()
                pos.position = float(data['long_qty'])
                if pos.position != 0:
                    pos.gatewayName = self.gatewayName
                    pos.symbol = data['instrument_id']
                    pos.vtSymbol = self.gatewayName + '.' + pos.symbol
                    pos.price = float(data['long_avg_cost'])
                    pos.direction = DIRECTION_LONG
                    pos.leverage = int(data['leverage'])
                    pos.margin_mode = data['margin_mode']
                    pos.positionProfit = data['realised_pnl']
                    self.gateway.onPosition(pos)
                # Short
                pos = VtPositionData()
                pos.position = float(data['short_qty'])
                if pos.position != 0:
                    pos.gatewayName = self.gatewayName
                    pos.symbol = data['instrument_id']
                    pos.vtSymbol = self.gatewayName + '.' + pos.symbol
                    pos.price = float(data['short_avg_cost'])
                    pos.direction = DIRECTION_SHORT
                    pos.leverage = int(data['leverage'])
                    pos.margin_mode = data['margin_mode']
                    pos.positionProfit = data['realised_pnl']
                    self.gateway.onPosition(pos)
        else:
            if 'crossed' in data:  # 全仓
                data = message['holding'][0]
                pos = VtPositionData()
                pos.position = float(data['position'])
                pos.price = float(data['avg_cost'])
                pos.direction = DIRECTION_LONG if data['side'] == 'long' else DIRECTION_SHORT
                pos.positionProfit = float(data['realized_pnl'])
                pos.symbol = data['instrument_id']
                pos.vtSymbol = self.gatewayName + '.' + pos.symbol
                self.gateway.onPosition(pos)
            else:
                pos = VtPositionData()
                pos.position = float(data['position'])
                pos.price = float(data['avg_cost'])
                pos.direction = DIRECTION_LONG if data['side'] == 'long' else DIRECTION_SHORT
                pos.positionProfit = float(data['realized_pnl'])
                pos.symbol = data['instrument_id']
                pos.vtSymbol = self.gatewayName + '.' + pos.symbol
                self.gateway.onPosition(pos)

    def writeLog(self, content):
        """
        快速记录日志
        """
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    def initCallback(self):
        """
        初始化回调函数. 1.获取合约信息，2.设置回调函数（在onMessage中起作用）
        :return
        """
        self.queryContractInfo('SWAP')
        self.queryContractInfo('JiaoGe')

    def onFutureIndexInfo(self, ws_data):
        """
        ws, 接收指数合约推送
        :param ws_data:
        :return:
        """
        data = ws_data.get('data')

        if data is None:
            return
        channel = ws_data['channel']
        t_date, t_time,_ = self.generateDateTime(float(data["timestamp"]))
        float_index = float(data["futureIndex"])
        symbol_pattern = self.channelSymbolMap[channel]
        for use_contract_type in CONTRACT_TYPE:
            symbol = symbol_pattern % (use_contract_type)
            push_dic = {"symbol": symbol, "date": t_date, "time": t_time, "index": float_index}
            self.gateway.onFutureIndexPush(push_dic)

    def checkStatus(self):
        """
        检查状态
        :return:
        """
        if len(self.tickDict) > 0:
            symbol,last_tick = list(self.tickDict.items())[0]
            # self.gateway.writeLog(u'日常检查，最近tick时间：{}'.format(last_tick.datetime.strftime('%Y-%m-%d %H:%M:%S')))
            if (datetime.now() - last_tick.datetime).seconds > 10:
                last_tick.datetime = datetime.now()
                # self.gateway.writeError(u'【注意：行情出现断开连接】')
                self.gateway.writeLog(u'【重新连接】')
                # self.onClose()
                return False
            return True
        else:
            return False

    def onTicker(self, ws_data):
        """
        ws, 接收期货行情
        :param ws_data:
        :return:
        """
        data = ws_data[0]

        try:
            symbol = data['instrument_id']
            if symbol not in self.tickDict:
                tick = VtTickData()
                tick.exchange = EXCHANGE_OKEX
                tick.symbol = symbol
                tick.vtSymbol = tick.symbol
                tick.gatewayName = self.gatewayName
                self.tickDict[symbol] = tick
                self.bids_depth_dict[symbol] = {}
                self.asks_depth_dict[symbol] = {}
            else:
                tick = self.tickDict[symbol]
                tick.datetime = datetime.now()
            self.bids_depth_dict[symbol] = {}
            self.asks_depth_dict[symbol] = {}
            tick.highPrice = float(data['high_24h'])
            tick.lowPrice = float(data['low_24h'])
            tick.lastPrice = float(data['last'])
            tick.volume = float(data['volume_24h'])
        except Exception as ex:
            self.gateway.writeError(u'ContractApi.onTicker exception:{}'.format(str(ex)))
            self.gateway.writeLog(ws_data)
            self.gateway.writeLog(u'ContractApi.onTicker exception:{},{}'.format(str(ex), traceback.format_exc()))

    def onDepth(self, ws_data):
        """
        ws, 接收深度信息
        期货深度行情推送。okex期货的深度数据原生返回是张数，需要转换为个数。
        转换公式（btc把10改为100，其他币种都是乘10） ：张数/成交价*10=个数
        :param ws_data:
        :return:
        """
        symbol = ws_data[0]['instrument_id']
        data = ws_data[0]
        try:
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
            self.bids_depth_dict[symbol] = {}
            self.asks_depth_dict[symbol] = {}
            tick_bids_depth = self.bids_depth_dict[symbol]
            tick_asks_depth = self.asks_depth_dict[symbol]
            # 更新bids得价格深度
            for inf in list(data['bids']):
                price1, vol1,acc_vol1, acc_vol2 = inf
                if abs(float(vol1)) < 0.00001 and price1 in tick_bids_depth:
                    del tick_bids_depth[price1]
                else:
                    tick_bids_depth[price1] = float(vol1)
            try:
                # 根据bidPrice价格排序
                arr = sorted(tick_bids_depth.items(), key=lambda x: x[0])
                tick.bidPrice1, tick.bidVolume1 = arr[-1]
                tick.bidPrice2, tick.bidVolume2 = arr[-2]
                tick.bidPrice3, tick.bidVolume3 = arr[-3]
                tick.bidPrice4, tick.bidVolume4 = arr[-4]
                tick.bidPrice5, tick.bidVolume5 = arr[-5]
            except Exception as ex:
                self.writeLog(u'ContractApi.onDepth exception:{},{}'.format(str(ex), traceback.format_exc()))
            for inf in list(data['asks']):
                price1, vol1,acc_vol1, acc_vol2 = inf
                if abs(float(vol1)) < 0.00001 and price1 in tick_asks_depth:
                    del tick_asks_depth[price1]
                else:
                    tick_asks_depth[price1] = float(vol1)
            try:
                # 根据ask价格排序
                arr = sorted(tick_asks_depth.items(),  key=lambda x: x[0])
                # 取前五个
                tick.askPrice1, tick.askVolume1 = arr[0]
                tick.askPrice2, tick.askVolume2 = arr[1]
                tick.askPrice3, tick.askVolume3 = arr[2]
                tick.askPrice4, tick.askVolume4 = arr[3]
                tick.askPrice5, tick.askVolume5 = arr[4]
            except Exception as ex:
                self.writeLog(u'ContractApi.onDepth exception:{},{}'.format(str(ex), traceback.format_exc()))
            tick.date, tick.time ,tick.datetime= self.generateDateTime(data['timestamp'])
            newtick = copy(tick)
            self.writeLog('tickTime:{};tickSymbol:{}'.format(tick.time, tick.symbol))
            self.gateway.onTick(newtick)
        except Exception as ex:
            self.writeLog(u'ContractApi.onDepth exception:{},{}'.format(str(ex), traceback.format_exc()))

    def onTrade(self, ws_data):
        """
        委托全部成交回报
        :param ws_data:
        :return:
        """
        self.writeLog(u'onTrade {}'.format(ws_data))

    def treatRespondFutureOrder(self, ws_data):
        """
        ws, 绑定本地订单
        委托下单请求响应，撤单请求响应，拒单请求响应等，将订单和本地编号挂起
        :param ws_data: 出错代码，或者委托成功得order_id
        :return:
        """
        data = ws_data
        self.gateway.writeLog(ws_data)
        error_code = data.get('error_code')
        if int(error_code) != 0:
            self.gateway.writeError(u'onFutureOrder委托返回错误:{}'.format(FUTURES_ERROR_DICT.get(str(error_code))), error_id=error_code)
            self.gateway.writeLog(ws_data)
            localNo = self.localNoQueue.get_nowait()
            if localNo is None:
                return
            self.gateway.writeLog(u'onFutureOrder移除本地localNo:{}'.format(localNo))
            order = self.localOrderDict.get(localNo)
            if order:
                order.orderID = localNo
                order.symbol = order.symbol
                order.vtsymbol = '.'.join([self.gatewayName, order.symbol])
                order.totalVolume = order.totalVolume
                dt = datetime.now()
                order.cancelTime = dt.strftime("%H:%M:%S.%f")
                order.status = STATUS_REJECTED # 发送期货委托单（拒单消息）到vtGateway
                self.gateway.writeLog(u'onFutureOrder发出OnOrder，拒单,vtOrderId={}'.format(localNo))
                self.gateway.onOrder(order)
            return
        ok_order_id = data.get('client_oid')
        if ok_order_id is None:
            self.gateway.writeError(u'FuturesApi.onFutureOrder 委托返回中，没有orderid')
            self.gateway.writeLog(ws_data)
            return
        localNo = self.localNoQueue.get_nowait() # 从本地编号Queue中，FIFO，提取最早的localNo
        if localNo is None:
            self.gateway.writeError(u'FuturesApi.onSportOrder，未找到本地LocalNo，检查日志')
            self.gateway.writeLog(ws_data)
            return
        self.localNoDict[localNo] = ok_order_id
        self.orderIdDict[ok_order_id] = localNo

    def onFutureTrades(self, ws_data):
        """
        ws，接收成交信息(onTrade, onOrder)
        Trade交易信息回报, 包括onOrder，onTrade信息回报
        :param ws_data:
        :return:
        """
        data = ws_data[0]
        orderId = str(data["client_oid"])                          # okex的委托编号
        if orderId not in self.orderDict:
            symbol = data['instrument_id']                                       # 自动添加_usd结尾
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            order.symbol = symbol                        # 合约.OKE
            order.vtSymbol = self.gatewayName + '.' + symbol
            order.orderID = orderId
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            order.price = float(data['price'])
            order.totalVolume = int(data['size'])
            order.tradedVolume = int(data['filled_qty'])
            order.direction, order.offset = priceContractOffsetTypeMap[str(data['type'])]
            order.status = statusMap[int(data['status'])]
            self.orderDict[orderId] = order
        else:
            order = self.orderDict[orderId]
            order.tradedVolume = float(data['filled_qty'])
            order.status = statusMap[int(data['status'])]
        self.gateway.onOrder(copy(order))
        bef_volume = self.recordOrderId_BefVolume.get(orderId, 0.0)
        now_volume = float(data['filled_qty']) - bef_volume
        if now_volume > 0.000001:
            self.recordOrderId_BefVolume[orderId] = float(data['filled_qty'])
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            trade.symbol = order.symbol
            trade.vtSymbol = order.symbol     # + '.{}'.format(EXCHANGE_OKEX)
            self.tradeID += 1
            trade.tradeID = str(self.tradeID)
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
            trade.orderID = orderId
            trade.vtOrderID = 'OKEX_1.' + orderId
            trade.price = float(data['price_avg'])
            trade.volume = float(now_volume)
            trade.direction, trade.offset = priceContractOffsetTypeMap[str(data['type'])]
            times = data['timestamp']
            timea, timeb, times = self.generateDateTime(times)
            trade.tradeTime = times
            self.gateway.onTrade(trade)

    def onFuturePositionInfo(self, ws_data):
        """
        ws， 接收账户持仓信息(onPosition)
        针对单币种的持仓信息回调函数
        :param ws_data:
        :return:
        """
        if isinstance(ws_data, list):
            data = ws_data[0] # 针对交割
            if 'long_qty' in data and int(data['long_qty']) != 0:         # 交割
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName  # + u'_Future'
                pos.symbol = data['instrument_id']
                pos.vtSymbol = self.gatewayName + '.' + pos.symbol
                pos.position = float(data['long_qty'])
                pos.price = float(data['long_avg_cost'])
                pos.direction = DIRECTION_LONG
                pos.leverage = int(data['leverage'])
                pos.margin_mode = data['margin_mode']
                pos.positionProfit = data['realised_pnl']
                self.gateway.onPosition(pos)
            if 'short_qty' in data and int(data['short_qty']) != 0:
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName  # + u'_Future'
                pos.symbol = data['instrument_id']
                pos.vtSymbol = self.gatewayName + '.' + pos.symbol
                pos.position = float(data['short_qty'])
                pos.price = float(data['short_avg_cost'])
                pos.direction = DIRECTION_SHORT
                pos.leverage = int(data['leverage'])
                pos.margin_mode = data['margin_mode']
                pos.positionProfit = data['realised_pnl']
                self.gateway.onPosition(pos)
        else:
            self.gateway.writeLog(u'onFuturePositionInfo 其他信息')

    def onFutureAccountInfo(self, ws_data):
        """
        ws, 接收账户信息
        推送，账户信息（onAccount)
        合约账户信息推送（账户权益/已实现盈亏/未实现盈亏/可用/已用/冻结）
        :param ws_data:
        :return: # TODO: 交割和永续注意一下
        """
        # if isinstance(ws_data,list):
        data = ws_data[0]
        try:
            symbol = data['instrument_id']
            account = VtAccountData()
            account.accountID = symbol
            account.vtAccountID = self.gatewayName + '.' + account.accountID
            account.gatewayName = self.gatewayName
            account.balance = float(data['equity'])  # 账户权益
            account.closeProfit = float(data['realized_pnl'])
            account.positionProfit = float(data['unrealized_pnl'])
            account.available = float(data['total_avail_balance'])
            account.margin_mode = 'crossed' if data['margin_mode'] == 'crossed' else 'fixed'
            self.gateway.onAccount(account)
        except:
            for symbol, s_inf in data.items():
                account = VtAccountData()
                account.gatewayName = self.gatewayName
                account.balance = float(s_inf['equity'])  # 账户权益
                account.closeProfit = float(s_inf['realized_pnl'])
                account.positionProfit = float(s_inf['unrealized_pnl'])
                account.margin = float(s_inf['margin']) # 保证金
                account.available = float(s_inf['total_avail_balance'])
                account.margin_mode = 'crossed' if s_inf['margin_mode'] == 'crossed' else 'fixed'
                account_list = []
                for num, key in enumerate(self.contractInfo.keys()):
                    if symbol in key and 'SWAP' not in key:
                        account.accountID = key
                        account.vtAccountID = self.gatewayName + '.' + account.accountID
                        account_list.append(key)
                for account in account_list: # TODO:这里不能对交割合约进行发送account信息
                    self.gatewayName.onAccount(account)

    def sendFutureSendOrder(self, req):
        """
        发送委托
        :param req:
        :return:
        """
        try:
            (symbol_pair, symbol, contract_type, leverage) = self.dealSymbolFunc(req.symbol)
        except Exception as ex:
            self.gateway.writeError(u'请求合约代码格式错误:{}'.format(req.symbol))
            self.writeLog(u'futureSendOrder 请求合约代码格式错误:{},exception:{},{}'.format(req.symbol,str(ex),traceback.format_exc()))
            return ''

        # symbol_pair(例如:btc_usd) ,  symbol(btc), contract_type(this_week) , leverage(10)
        type_ = priceContractTypeMapReverse[(req.direction, req.offset)]
        self.writeLog(u'futureSendOrder:{},price:{},num:{},type:{}'.format(symbol, req.price, req.volume, type_))
        # 本地委托号加1，并将对应字符串保存到队列中，返回基于本地委托号的vtOrderID
        self.localNo += 1
        localNo = 'Aa'+ str(self.loginTime + self.localNo)
        self.localNoQueue.put(str(localNo))
        vtOrderID = "{}.{}".format(self.gatewayName, localNo)
        self.writeLog(u'futureSendOrder:创建本地订单:orderId:{}'.format(localNo))

        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = symbol
        order.vtSymbol = "{}.{}".format(symbol, EXCHANGE_OKEX)
        order.orderID = localNo
        order.vtOrderID = vtOrderID
        order.price = req.price
        order.totalVolume = req.volume
        order.direction = req.direction
        order.offset = req.offset
        order.status = STATUS_NOTTRADED
        order.orderTime = datetime.now().strftime("%H:%M:%S.%f")
        self.localOrderDict[localNo] = order
        try:
            self.futureTrade(symbol, type_, str(req.price), str(req.volume), order_id=localNo)
            return vtOrderID
        except Exception as ex:
            self.gateway.writeError(u'futureSendOrder发送委托失败:{}'.format(str(ex)))
            self.writeLog(u'futureSendOrder发送委托失败.{}'.format(traceback.format_exc()))
            return False

    def sendFutureCancelOrder(self, req):
        """
        发出撤单请求
        :param req:
        :return:
        """
        localNo = req.orderID
        status, response = self.queryFutureCancelOrder(req.symbol, localNo)
        if status:
            self.gateway.writeLog(u'撤单成功')
            self.treatFutureOrderCancel(response)
            return True
        else:
            self.gateway.writeLog(u'撤单失败')
            return False

    def treatFutureOrderCancel(self, ws_data):
        """
        委托撤单的响应
        :param ws_data:
        :return:
        """
        ok_order_id = ws_data.get('client_oid','')
        order = self.orderDict[ok_order_id]
        dt = datetime.now()
        order.cancelTime = dt.strftime("%H:%M:%S.%f")
        order.status = STATUS_CANCELLED
        self.gateway.onOrder(order)

    def generateDateTime(self, s):
        """生成时间"""
        s = s.split('.')[0]
        s = s.split('T')[0]+u' '+s.split('T')[1]
        s = td.mktime(td.strptime(s, "%Y-%m-%d %H:%M:%S"))
        s = s + 60*60*8
        dt = datetime.fromtimestamp(s)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return date, time,dt

