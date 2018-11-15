# encoding: UTF-8

'''
vnpy.api.okex的gateway接入
注意：
1. 目前仅支持USD现货交易
'''

import os
import json
from datetime import datetime
from time import sleep
from copy import copy
from threading import Condition
from queue import Queue
from threading import Thread
from time import sleep
import traceback
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
priceContractOffsetTypeMap['1'] = (DIRECTION_LONG , OFFSET_OPEN)
priceContractOffsetTypeMap['2'] = (DIRECTION_SHORT , OFFSET_OPEN )
priceContractOffsetTypeMap['3'] = (DIRECTION_SHORT , OFFSET_CLOSE )
priceContractOffsetTypeMap['4'] = (DIRECTION_LONG , OFFSET_CLOSE)
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

EVENT_OKEX_INDEX_FUTURE = "eFuture_Index_OKEX"

########################################################################
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

        # 消息调试
        self.log_message = False

        self.qryFunctionList = []
    # ----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
        try:
            f = open(self.filePath, 'r')
        except IOError:
            self.writeError(u'OkexGateway.connect:读取连接配置{}出错，请检查'.format(self.filePath))
            return

        # 解析json文件
        setting = json.load(f)
        try:
            self.apiKey = str(setting['apiKey'])
            self.secretKey = str(setting['secretKey'])
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
                    if '_' in symbol and ':' not in symbol:
                        self.auto_subscribe_symbol_pairs.add(symbol)
                    elif ':' in symbol:
                        self.auto_subscribe_future_symbols.add(symbol)

            self.qryEnabled = setting.get('qryEnabled', True)
        except KeyError:
            self.writeError(u'OkexGateway.connect:连接配置缺少字段，请检查')
            return

        if spot_connect:
            self.api_spot.active = True

            for symbol_pair in self.auto_subscribe_symbol_pairs:
                self.writeLog(u'自动订阅现货合约:{}'.format(symbol_pair))
                self.api_spot.registerSymbolPairArray.add(symbol_pair)

            self.api_spot.connect(self.apiKey, self.secretKey, trace)
            self.writeLog(u'connect okex ws spot api')
            self.api_spot.setSymbolPairs(self.use_spot_symbol_pairs)

        if futures_connect:
            self.api_futures.active = True
            self.api_futures.connect(self.apiKey, self.secretKey, trace)
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
        if not self.spot_connected and not self.futures_connected:
            return False

        if self.spot_connected:
            return self.api_spot.checkStatus()

        if self.futures_connected:
            return self.api_futures.checkStatus()
    # ----------------------------------------------------------------------
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

            if symbol_pair in SPOT_SYMBOL_PAIRS:
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

    # ----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""

        # btc_usdt.OKEX => btc_usdt
        order_req_symbol = orderReq.symbol
        order_req_symbol = order_req_symbol.replace('.{}'.format(EXCHANGE_OKEX),'')

        if order_req_symbol in SPOT_SYMBOL_PAIRS:
            if self.api_spot and self.spot_connected:
                return self.api_spot.spotSendOrder(orderReq)
            else:
                self.writeError(u'现货接口未创建/连接，无法调用sendOrder')
                return ''
        else:
            if self.api_futures and self.futures_connected:
                return self.api_futures.futureSendOrder(orderReq)
            else:
                self.writeError(u'期货接口未创建/连接，无法调用sendOrder')
                return ''
    # ----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        # btc_usdt.OKEX => btc_usdt
        order_req_symbol = cancelOrderReq.symbol
        order_req_symbol = order_req_symbol.replace('.{}'.format(EXCHANGE_OKEX), '')
        if order_req_symbol in SPOT_SYMBOL_PAIRS:
            if self.spot_connected:
                self.api_spot.spotCancel(cancelOrderReq)
            else:
                self.writeError(u'现货接口未创建/连接，无法调用cancelOrder')
        else:
            if self.futures_connected:
                self.api_futures.futureCancel(cancelOrderReq)
            else:
                self.writeError(u'期货接口未创建/连接，无法调用cancelOrder')

    # ----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        if self.spot_connected:
            self.api_spot.spotUserInfo()

        if self.futures_connected:
            self.api_futures.futureUserInfo()

    # ----------------------------------------------------------------------
    def qryOrderInfo(self):
        if self.spot_connected:
            self.api_spot.spotAllOrders()

        if self.futures_connected:
            self.api_futures.futureAllUnfinishedOrderInfo()

    # ----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        if self.futures_connected:
            pass
            #self.api_futures.subscribeFuturePositions()

    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        if self.spot_connected:
            self.api_spot.active = False
            self.api_spot.close()

        if self.futures_connected:
            self.api_futures.active = False
            self.api_futures.close()

    # ----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryAccount, self.qryOrderInfo,self.qryPosition]
            #self.qryFunctionList = [self.qryOrderInfo]
            # self.qryFunctionList = []

            self.qryCount = 0  # 查询触发倒计时
            self.qryTrigger = 2  # 查询触发点
            self.qryNextFunction = 0  # 上次运行的查询函数索引

            self.startQuery()

    # ----------------------------------------------------------------------
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

    # ----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)
        self.eventEngine.register(EVENT_TIMER, self.heartbeat)

    # ----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled

    #----------------------------------------------------------------------
    def onFutureIndexPush(self, push_dic):
        """
        合约指数更新事件
        :param push_dic:
        :return:
        """
        event1 = Event(type_=EVENT_OKEX_INDEX_FUTURE)
        event1.dict_['data'] = push_dic
        self.eventEngine.put(event1)

########################################################################
class OkexSpotApi(WsSpotApi):
    """okex的API实现"""

    # ----------------------------------------------------------------------
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

        self.channelSymbolMap = {}  # 请求数据类型与合约的映射字典

        self.localNo = 1  # 本地委托号
        self.localNoQueue = Queue()  # 未收到系统委托号的本地委托号队列
        self.localNoDict = {}  # key为本地委托号，value为系统委托号
        self.orderIdDict = {}  # key为系统委托号，value为本地委托号
        self.cancelDict = {}  # key为本地委托号，value为撤单请求

        self.recordOrderId_BefVolume = {}  # 记录的之前处理的量

        self.tradeID = 0

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

    '''
    登录后，每次订单执行撤销后又这样的 推送。。不知道干啥的。先过滤掉了
    {u'binary': 1, u'product': u'spot', u'type': u'order', u'base': u'etc'
, u'quote': u'usdt', u'data': {u'status': -1, u'orderType': 0, u'price': u'25.4050', u'modifyTime':
1512288275000L, u'userId': 6548935, u'createTime': 1512288275000L, u'source': 0, u'quoteSize': u'0.0
0000000', u'executedValue': u'0.00000000', u'id': 62877909, u'filledSize': u'0.00000000', u'side': 1
, u'size': u'0.01000000'}}
    '''

    # ----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """
        响应信息处理，包括心跳响应、请求响应、数据推送
        :param ws: websocket接口
        :param evt: 消息体
        :return:
        """
        # str => json
        decmp_evt = self.inflate(evt)
        ws_data = self.readData(decmp_evt)

        if self.gateway.log_message:
            self.gateway.writeLog(u'SpotApi.onMessage:{}'.format(ws_data))

        # 消息是dict格式
        if isinstance(ws_data, dict):
            if 'event' in ws_data:
                #处理心跳得
                if ws_data['event'] == 'pong':
                    self.gateway.writeLog(u'heart beat response {}'.format(datetime.now()))
                    return
                else:
                    self.gateway.writeLog(u'其他 event:{}'.format(ws_data))
            else:
                self.gateway.writeLog(u'其他数据:{}'.format(ws_data))

        # 消息是list格式
        if isinstance(ws_data, list):
            for data in ws_data:
                channel_value = data.get('channel', None)
                if channel_value == None:
                    continue

                # 登录请求恢复
                if channel_value == 'login':
                    login_data = data.get('data', {})
                    result = login_data.get('result', False)
                    if result:
                        self.gateway.writeLog(u'Spot login success: {}'.format(datetime.now()))
                        self.gateway.spot_connected = True
                    else:
                        self.gateway.writeError(u'SpotApi login fail: {},data:{}'.format(datetime.now(), data))
                    continue

                # 功能订阅得回复
                elif channel_value == 'addChannel':
                    channel_data = data.get('data', {})
                    result = channel_data.get('result', False)
                    channel_value = channel_data.get('channel', "")
                    if result:
                        self.gateway.writeLog(u'功能订阅请求:{} 成功:'.format(channel_value))
                    continue

                # 其他回调/数据推送
                callback = self.cbDict.get(channel_value)
                if callback:
                    try:
                        callback(data)
                    except Exception as ex:
                        self.gateway.writeError(u'Spot {}回调函数处理异常，请查日志'.format(channel_value))
                        self.gateway.writeLog(u'Spot onMessage call back {} exception：{},{}'.format(channel_value, str(ex),traceback.format_exc()))
                else:
                    self.gateway.writeError(u'Spot unkown msg:{}'.format(data))

    # ----------------------------------------------------------------------
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

    # ----------------------------------------------------------------------
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

    # ----------------------------------------------------------------------
    def onClose(self, ws):
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

    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """
        订阅行情
        :param subscribeReq:
        :return:
        """
        self.gateway.writeLog(u'SpotApi.subscribe({})'.format(subscribeReq.symbol))

        # 检查：带有网关特征的品种对symbol, 如：eth_usdt.OKEX
        symbol_pair_gateway = subscribeReq.symbol
        arr = symbol_pair_gateway.split('.')
        # 提取品种对 eth_usdt
        symbol_pair = arr[0]

        # 若品种对未登记过
        if symbol_pair not in self.registerSymbolPairArray:
            # 添加登记品种对
            self.registerSymbolPairArray.add(symbol_pair)
        # 发起品种行情订阅请求
        self.subscribeSingleSymbol(symbol_pair)
        # 查询该品种对的订单
        self.spotOrderInfo(symbol_pair, '-1')

    # ----------------------------------------------------------------------
    def subscribeSingleSymbol(self, symbol):
        """
        订阅合约（对）
        :param symbol:合约（对）
        :return:
        """

        self.gateway.writeLog(u'SpotApi.subscribeSingleSymbol({})'.format(symbol))
        if symbol in SPOT_SYMBOL_PAIRS:
            # 订阅行情数据
            self.subscribeSpotTicker(symbol)
            # 订阅委托深度
            self.subscribeSpotDepth(symbol, depth=5)
            # 订阅该合约的委托成交回报（所有人，不是你得账号)
            #self.subscribeSpotDeals(symbol)
        else:
            self.gateway.writeError(u'SpotApi:订阅失败，{}不在SPOT_SYMBOL_PAIRS中，'.format(symbol))

    # ----------------------------------------------------------------------
    def spotAllOrders(self):
        """
        查询所有委托清单
        :return:
        """
        self.gateway.writeLog('SpotApi.spotAllOrders()')

        # 根据已登记的品种对清单，逐一发委托查询
        for symbol in self.registerSymbolPairArray:
            if symbol in SPOT_SYMBOL_PAIRS:
                self.spotOrderInfo(symbol, '-1')

        # 对已经发送委托，根据orderid，发出查询请求
        #for orderId in self.orderIdDict.keys():
        #    order = self.orderDict.get(orderId, None)
        #    if order != None:
        #        symbol_pair = (order.symbol.split('.'))[0]
        #        self.spotOrderInfo(symbol_pair, orderId)

    # ----------------------------------------------------------------------
    def onOpen(self, ws):
        """
        ws连接成功事件回调函数
        :param ws:
        :return:
        """
        self.gateway.spot_connected = True
        self.gateway.writeLog(u'Spot服务器连接成功')

        # 登录
        self.login()

        # 连接后查询现货账户和委托数据
        self.spotUserInfo()

        self.gateway.writeLog(u'SpotApi初始化合约信息')
        # 如果有缺省得使用合约对，就仅初始化这些合约对，否则全部初始化
        for symbol in SPOT_SYMBOL_PAIRS if len(self.use_symbol_pairs) == 0 else self.use_symbol_pairs:
            # self.subscribeSpotTicker(symbol)
            # self.subscribeSpotDepth5(symbol)
            # self.subscribeSpotDeals(symbol)

            # Ticker数据
            self.channelSymbolMap["ok_sub_spot_%s_ticker" % symbol] = symbol
            # 盘口的深度
            self.channelSymbolMap["ok_sub_spot_%s_depth_5" % symbol] = symbol
            # 所有人的交易数据
            self.channelSymbolMap["ok_sub_spot_%s_deals" % symbol] = symbol

            # 更新至数据引擎的合约信息
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            contract.exchange = EXCHANGE_OKEX
            contract.symbol = '.'.join([symbol, contract.exchange])
            contract.vtSymbol =  contract.symbol
            contract.name = u'%s[现货]' % symbol
            contract.size = 1   # 现货是1:1
            contract.priceTick = 0.0001
            contract.volumeTick = SPOT_TRADE_SIZE_DICT[symbol]
            contract.productClass = PRODUCT_SPOT
            self.gateway.onContract(contract)

        # 对所有登记得品种对，发起订阅
        for symbol_pair in self.registerSymbolPairArray:
            # 发起品种行情订阅请求
            self.subscribeSingleSymbol(symbol_pair)
            # 查询该品种对的订单
            self.spotOrderInfo(symbol_pair, '-1')

    '''
    [{
    "channel":"ok_sub_spot_bch_btc_deals",
    "data":[["1001","2463.86","0.052","16:34:07","ask"]]
    }]
    '''

    # ----------------------------------------------------------------------
    def onSpotSubDeals(self, ws_data):
        """
        当前现货委托成交信息回报
        :param ws_data:
        :return:
        """
        self.gateway.writeLog(u'SpotApi.onSpotSubDeals:{}'.format(ws_data))

    # ----------------------------------------------------------------------
    def initCallback(self):
        """
        初始化回调函数
        :return:
        """
        self.gateway.writeLog(u'ok spot api 初始化回调函数')
        # USD_SPOT 把每一个币币交易对的回调函数登记在字典中
        for symbol_pair in SPOT_SYMBOL_PAIRS:
            self.cbDict["ok_sub_spot_%s_ticker" % symbol_pair] = self.onTicker              # 该币对的行情数据回报
            self.cbDict["ok_sub_spot_%s_depth_5" % symbol_pair] = self.onDepth              # 该币对的委托深度回报
            self.cbDict["ok_sub_spot_%s_deals" % symbol_pair] = self.onSpotSubDeals         # 该币对的成交记录回报

            self.cbDict["ok_sub_spot_%s_order" % symbol_pair] = self.onSpotSubOrder         # 该币对的交易更新回报
            self.cbDict["ok_sub_spot_%s_balance" % symbol_pair] = self.onSpotBalance        # 该币对的账号信息回报

        self.cbDict['ok_spot_userinfo'] = self.onSpotUserInfo                               # 合约账户信息回报
        self.cbDict['ok_spot_orderinfo'] = self.onSpotOrderInfo                             # 委托查询信息回报

        # 下面这两个好像废弃了
        # self.cbDict['ok_sub_spot_userinfo'] = self.onSpotSubUserInfo
        # self.cbDict['ok_sub_spot_trades'] = self.onSpotSubTrades

        self.cbDict['ok_spot_order'] = self.onSpotOrder                                     # 交易委托回报
        self.cbDict['ok_spot_cancel_order'] = self.onSpotCancelOrder                        # 交易撤单回报

    # ----------------------------------------------------------------------
    """
    ok_sub_spot_X_ticker   订阅行情数据
    websocket.send("{'event':'addChannel','channel':'ok_sub_spot_X_ticker'}");
    
    X值为币对，如ltc_btc
    # Request
    {'event':'addChannel','channel':'ok_sub_spot_bch_btc_ticker'}
    # Response
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
    返回值说明
    
    buy(double): 买一价
    high(double): 最高价
    last(double): 最新成交价
    low(double): 最低价
    sell(double): 卖一价
    timestamp(long)：时间戳
    vol(double): 成交量(最近的24小时)
    """

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
        channel = ws_data.get('channel')
        data = ws_data.get('data', {})
        # 检查channel/data
        if channel is None and len(data) == 0:
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

            tick.highPrice = float(data['high'])
            tick.lowPrice = float(data['low'])
            tick.lastPrice = float(data['last'])
            tick.volume = float(data['vol'].replace(',', ''))
            # 这里不发出onTick event，留待深度行情发出
        except Exception as ex:
            self.gateway.writeError(u'SpotApi.onTicker异常')
            self.gateway.writeLog('SpotApi.onTicker channel {} exception:{},{} '.format(channel,str(ex), traceback.format_exc()))

    # ----------------------------------------------------------------------
    """
    ok_sub_spot_X_depth 订阅币币市场深度(200增量数据返回)
    websocket.send("{'event':'addChannel','channel':'ok_sub_spot_X_depth'}");
    
    X值为币对，如ltc_btc
    
    示例
    
    # Request
    {'event':'addChannel','channel':'ok_sub_spot_bch_btc_depth'}
    # Response
    [
        {
            "binary": 0,
            "channel": "ok_sub_spot_bch_btc_depth",
            "data": {
                "asks": [],
                "bids": [
                    [
                        "115",
                        "1"
                    ],
                    [
                        "114",
                        "1"
                    ],
                    [
                        "1E-8",
                        "0.0008792"
                    ]
                ],
                "timestamp": 1504529236946
            }
        }
    ]
    返回值说明
    
    bids([string, string]):买方深度
    asks([string, string]):卖方深度
    timestamp(string):服务器时间戳
    使用描述  
    
    第一次返回全量数据，根据接下来数据对第一次返回数据进行如下操作：删除（量为0时）；修改（价格相同量不同）；增加（价格不存在）。
    
    3、ok_sub_spot_X_depth_Y 订阅市场深度
    websocket.send("{'event':'addChannel','channel':'ok_sub_spot_X_depth_Y'}");
    
    X值为币对，如ltc_btc
    
    Y值为获取深度条数，如5，10，20
    
    示例
    
    # Request
    {'event':'addChannel','channel':'ok_sub_spot_bch_btc_depth_5'}
    # Response
    [
        {
            "binary": 0,
            "channel": "ok_sub_spot_bch_btc_depth_5",
            "data": {
                "asks": [],
                "bids": [
                    [
                        "115",
                        "1"
                    ],
                    [
                        "114",
                        "1"
                    ],
                    [
                        "1E-8",
                        "0.0008792"
                    ]
                ],
                "timestamp": 1504529432367
            }
        }
    ]
    返回值说明
    
    bids([string, string]):买方深度
    asks([string, string]):卖方深度
    timestamp(long):服务器时间戳
    """
    def onDepth(self, ws_data):
        """
        5档深度行情数据回报
        :param ws_data:
        :return:
        """
        channel = ws_data.get('channel')
        data = ws_data.get('data', {})
        # 检查channel/data
        if channel is None and len(data) == 0:
            return

        symbol = self.channelSymbolMap.get(channel)
        if symbol == None:
            return

        # 更新tick
        if symbol not in self.tickDict:
            tick = VtTickData()
            tick.symbol = symbol
            tick.vtSymbol = symbol
            tick.gatewayName = self.gatewayName
            self.tickDict[symbol] = tick
        else:
            tick = self.tickDict[symbol]

        tick.bidPrice1, tick.bidVolume1 = data['bids'][0]
        tick.bidPrice2, tick.bidVolume2 = data['bids'][1]
        tick.bidPrice3, tick.bidVolume3 = data['bids'][2]
        tick.bidPrice4, tick.bidVolume4 = data['bids'][3]
        tick.bidPrice5, tick.bidVolume5 = data['bids'][4]

        tick.askPrice1, tick.askVolume1 = data['asks'][-1]
        tick.askPrice2, tick.askVolume2 = data['asks'][-2]
        tick.askPrice3, tick.askVolume3 = data['asks'][-3]
        tick.askPrice4, tick.askVolume4 = data['asks'][-4]
        tick.askPrice5, tick.askVolume5 = data['asks'][-5]

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
        # print "Depth", tick.date, tick.time
        tick.tradingDay = tick.date

        # 推送tick事件
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

    """
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

{u'binary': 0, 
    u'data': {u'info': 
                {u'funds': 
                    {u'freezed': 
                        {u'zec': u'0', u'usdt': u'0', u'btg': u'0'
                        , u'btc': u'0', u'bt1': u'0', u'neo': u'0', u'pay': u'0', u'storj': u'0', u'iota': u'0', u'omg': u'0
                        ', u'dgd': u'0', u'bt2': u'0', u'xuc': u'0', u'gas': u'0', u'hsr': u'0', u'snt': u'0', u'dash': u'0'
                        , u'bch': u'0', u'gnt': u'0', u'bcd': u'0', u'qtum': u'0', u'bcc': u'0', u'eos': u'0', u'etc': u'0',
                         u'act': u'0', u'eth': u'0', u'ltc': u'0', u'bcs': u'0'}, u'borrow': {u'zec': u'0', u'usdt': u'0', u
                        'btg': u'0', u'btc': u'0', u'bt1': u'0', u'neo': u'0', u'pay': u'0', u'storj': u'0', u'iota': u'0',
                        u'omg': u'0', u'dgd': u'0', u'bt2': u'0', u'xuc': u'0', u'gas': u'0', u'hsr': u'0', u'snt': u'0', u'
                        dash': u'0', u'bch': u'0', u'gnt': u'0', u'bcd': u'0', u'qtum': u'0', u'bcc': u'0', u'eos': u'0', u'
                        etc': u'0', u'act': u'0', u'eth': u'0', u'ltc': u'0', u'bcs': u'0'},
                    u'free': 
                        {u'zec': u'0', u'usdt': u'0', u'btg': u'0', u'btc': u'0.00266884258369', u'bt1': u'0', u'neo': u'0',
                         u'pay': u'0', u'storj': u'0', u'iota': u'0', u'omg': u'0', u'dgd': u'0', u'bt2': u'0', u'xuc': u'3',
                         u'gas': u'0', u'hsr': u'0', u'snt': u'0', u'dash': u'0', u'bch': u'0', u'gnt': u'0', u'bcd': u'0',
                         u'qtum': u'0', u'bcc': u'0', u'eos': u'0', u'etc': u'7.9909635', u'act': u'0', u'eth': u'0', 
                         u'ltc': u'0', u'bcs': u'0'}
                    }
              }, u'result': True},
    u'channel': u'ok_spot_userinfo'}
    """

    # ----------------------------------------------------------------------
    def onSpotUserInfo(self, ws_data):
        """现货账户资金推送"""
        if 'data' not in ws_data or 'info' not in ws_data['data'] or 'funds' not in ws_data['data']['info']:
            self.gateway.writeError(u'SpotApi.onSpotUserInfo 数据不完整,请检查日志')
            self.gateway.writeLog(ws_data)
            return

        data = ws_data.get('data')
        data_info = data.get('info')
        data_info_funds = data_info.get('funds')

        # 持仓信息
        for symbol in SPOT_CURRENCY:
        #for symbol in ['btc', 'ltc', 'eth', self.currency]:
            # for symbol in :
            if symbol in data_info_funds['free']:
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName
                pos.symbol = symbol + "." + EXCHANGE_OKEX
                pos.vtSymbol = symbol + "." + EXCHANGE_OKEX
                pos.vtPositionName = symbol + "[现货]"
                pos.direction = DIRECTION_NET

                pos.frozen = float(data_info_funds['freezed'][symbol])
                pos.position = pos.frozen + float(data_info_funds['free'][symbol])

                self.gateway.onPosition(pos)

        # 账户资金
        #account = VtAccountData()
        #account.gatewayName = self.gatewayName
        #account.accountID = self.gatewayName
        #account.vtAccountID = account.accountID
        #account.balance = 0.0
        # account.balance = float(funds['asset']['net'])
        #self.gateway.onAccount(account)

    # ----------------------------------------------------------------------
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
        # for symbol in ['btc', 'ltc','eth', self.currency]:
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

    """
    委托回报数据
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
   
    {u'binary': 0, u'data': {u'orderId': 62870564, u'status': 0, u'tradeType': u'sell', u'tradeUnitPrice
': u'25.3500', u'symbol': u'etc_usdt', u'tradePrice': u'0.0000', u'createdDate': u'1512287172393', u
'averagePrice': u'0', u'tradeAmount': u'0.01000000', u'completedTradeAmount': u'0.00000000'}, u'chan
nel': u'ok_sub_spot_etc_usdt_order'}

    返回值说明：
    createdDate(string):创建日期
    orderId(long):订单id
    tradeType(string):交易类型（buy:买入；sell:卖出；buy_market:按市价买入；sell_market:按市价卖出）
    sigTradeAmount(string):单笔成交数量
    sigTradePrice(string):单笔成交价格
    tradeAmount(string):委托数量（市价卖代表要卖总数量；限价单代表委托数量）
    tradeUnitPrice(string):委托价格（市价买单代表购买总金额； 限价单代表委托价格）
    symbol(string):交易币对，如ltc_btc
    completedTradeAmount(string):已完成成交量
    tradePrice(string):成交金额
    averagePrice(string):平均成交价
    unTrade(string):当按市场价买币时表示剩余金额，其他情况表示此笔交易剩余买/卖币的数量
    status(int):-1已撤销,0等待成交,1部分成交,2完全成交,4撤单处理中
    """

    # ----------------------------------------------------------------------
    def onSpotSubOrder(self, ws_data):
        """
        交易委托更新回报（发生部分成交/全部成交/拒单/撤销时，API推送的回报)
        :param ws_data:ws推送的单个委托更新数据
        :return:
        """
        self.gateway.writeLog(u'SpotApi.onSpotSubOrder:{}'.format(ws_data))
        data = ws_data.get("data")
        if data is None: return

        # 本地和系统委托号
        ok_order_id = str(data['orderId'])

        localNo = self.orderIdDict.get(ok_order_id, None)
        if localNo == None:
            self.gateway.writeError(u'onSpotSubOrder:ok_order_id:{}与本地委托无关联,'.format(ok_order_id))
            self.gateway.writeLog(data)

            localNo = str(self.localNo)
            if ok_order_id not in self.orderIdDict:
                # orderId 不在本地缓存中，需要增加一个绑定关系
                while str(self.localNo) in self.localNoDict:
                    self.localNo += 1
                localNo = str(self.localNo)
            self.localNoDict[localNo] = ok_order_id
            self.orderIdDict[ok_order_id] = localNo
            self.gateway.writeLog(u'onFutureOrderInfo add orderid: local:{}<=>okex:{}'.format(localNo, ok_order_id))

        # 委托信息
        if ok_order_id not in self.orderDict:
            self.gateway.writeLog(u'onSpotSubOrder:添加至委托单缓存:{}'.format(data))
            order = VtOrderData()
            order.gatewayName = self.gatewayName

            order.symbol = '.'.join([data['symbol'], EXCHANGE_OKEX])
            order.vtSymbol = order.symbol

            order.orderID = localNo
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])

            order.price = float(data['tradeUnitPrice'])
            order.totalVolume = float(data['tradeAmount'])
            order.direction, priceType = priceTypeMap[data['tradeType']]
            order.offset = OFFSET_OPEN if order.direction == DIRECTION_LONG else OFFSET_CLOSE
            create_date, order.orderTime,_ = self.generateDateTime(data['createdDate'])
            self.orderDict[ok_order_id] = order
        else:
            order = self.orderDict[ok_order_id]

        order.tradedVolume = float(data['completedTradeAmount'])
        order.status = statusMap[data['status']]
        if order.status == STATUS_CANCELLED:
            dt = datetime.now()
            order.cancelTime = dt.strftime("%H:%M:%S.%f")

        # 推送现货委托单到vtGateway.onOrder event
        self.gateway.writeLog(u'onSpotSubOrder:发出OnOrder，vtOrderId={},orderStatus:{}'.format(order.vtOrderID,order.status))
        self.gateway.onOrder(copy(order))

        bef_volume = self.recordOrderId_BefVolume.get(ok_order_id, 0.0)
        now_volume = float(data['completedTradeAmount']) - bef_volume

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

            trade.price = float(data['tradeUnitPrice'])
            trade.volume = float(now_volume)

            trade.direction, priceType = priceTypeMap[data['tradeType']]
            trade.tradeTime = datetime.now().strftime('%H:%M:%S')

            # 推送onTrade事件
            self.gateway.writeLog(u'onSpotSubOrder:发出onTrader，vtOrderId={}'.format(trade.vtOrderID))
            self.gateway.onTrade(trade)

    # ----------------------------------------------------------------------
    """ 委托信息查询回调得例子
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
    """

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
        data = ws_data.get('data', {})
        # 获取所有返回的委托单清单
        orders = data.get('orders', [])

        for data_order in orders:
            ok_order_id = data_order.get('order_id')
            if ok_order_id is None:
                ok_order_id = data_order.get('orders_id')

            if ok_order_id is None:
                self.gateway.writeError(u'提取order_id出错')
                continue
            ok_order_id = str(ok_order_id)

            localNo = str(self.localNo)

            if ok_order_id not in self.orderIdDict:
                # orderId 不在本地缓存中，需要增加一个绑定关系
                while str(self.localNo) in self.localNoDict:
                    self.localNo += 1
                localNo = str(self.localNo)
                # 绑定localNo 与 orderId
                self.localNoDict[localNo] = ok_order_id
                self.orderIdDict[ok_order_id] = localNo
                self.gateway.writeLog(u'onFutureOrderInfo add orderid: local:{}<=>okex:{}'.format(localNo, ok_order_id))
            else:
                # orderid在本地缓存中，
                localNo = self.orderIdDict[ok_order_id]
                # 检验 localNo是否在本地缓存，没有则补充
                if localNo not in self.localNoDict:
                    self.localNoDict[localNo] = ok_order_id
                    self.gateway.writeLog(u'onFutureOrderInfo update orderid: local:{}<=>okex:{}'.format(localNo, ok_order_id))

            if ok_order_id not in self.orderDict:       # 不在本地委托单缓存时，添加
                self.gateway.writeLog(u'onSpotOrderInfo:添加至委托单缓存:{}'.format(data_order))
                order = VtOrderData()
                order.gatewayName = self.gatewayName

                # order.symbol = spotSymbolMap[d['symbol']]
                order.symbol = '.'.join([data_order["symbol"], EXCHANGE_OKEX])
                order.vtSymbol = order.symbol

                order.orderID = localNo
                order.vtOrderID = '.'.join([self.gatewayName, order.orderID])

                order.price = data_order['price']
                order.totalVolume = data_order['amount']
                order.direction, priceType = priceTypeMap[data_order['type']]
                create_date, order.orderTime,_ = self.generateDateTime(data_order['create_date'])
                self.orderDict[ok_order_id] = order
            else:
                order = self.orderDict[ok_order_id]                 # 使用本地缓存

            order.tradedVolume = data_order['deal_amount']      # 更新成交数量
            order.status = statusMap[data_order['status']]      # 更新成交状态
            self.gateway.writeLog('orderId:{},tradedVolume:{},status:{}'.format(order.vtOrderID,order.tradedVolume,order.status))
            self.gateway.onOrder(copy(order))                   # 提交现货委托单到vtGatway.onOrder事件

    # ----------------------------------------------------------------------
    """ onSpotOrder的回报 ws_data 例子    
        {
            "binary": 0,
            "channel": "ok_spot_order",
            "data": {
                "result": true,
                "order_id": 6189
            }
        }       
    """
    def onSpotOrder(self, ws_data):
        """
        交易委托回报
        :param ws_data:
        :return:
        """
        self.gateway.writeLog(u'SpotApi.onSpotOrder:{}'.format(ws_data))
        data = ws_data.get('data', {})

        if 'error_code' in data:
            error_id = data.get('error_code')
            self.gateway.writeError(u'SpotApi.onSpotOrder 委托返回错误:{}'.format(SPORT_WS_ERROR_DICT.get(str(error_id))), error_id=error_id)
            self.gateway.writeLog(ws_data)

            # 特殊处理服务超时得异常
            if str(error_id) == '20100':
                return

            localNo = self.localNoQueue.get_nowait()
            self.gateway.writeLog(u'移除本地localNo:{}'.format(localNo))
            vtOrderId = '.'.join([self.gatewayName,localNo])
            order = self.localOrderDict.get(vtOrderId)
            if order is not None:
                order.status = STATUS_REJECTED
                order.updateTime = datetime.now().strftime("%H:%M:%S.%f")
                order.symbol= '.'.join([order.symbol,self.gatewayName])
                order.vtsymbol=order.symbol
                order.totalVolume=order.totalVolume
                self.gateway.writeLog(u'发出OnOrder，拒单,vtOrderId={}'.format(vtOrderId))

                # 发送现货委托单（拒单消息）到vtGateway
                self.gateway.onOrder(order)
            return

        ok_order_id = data.get('order_id')

        if ok_order_id is None:
            self.gateway.writeError(u'SpotApi.onSpotOrder 委托返回中，没有orderid')
            self.gateway.writeLog(ws_data)
            return

        # 从本地编号Queue中，FIFO，提取最早的localNo
        localNo = self.localNoQueue.get_nowait()
        if localNo is None:
            self.gateway.writeError(u'SpotApi.onSpotOrder，未找到本地LocalNo，检查日志')
            self.gateway.writeLog(ws_data)
            return

        self.gateway.writeLog(u'SpotApi.onSpotOrder,绑定 local:{}  <==> ok_order_id:{}'.format(localNo,ok_order_id))
        self.localNoDict[localNo] = str(ok_order_id)
        self.orderIdDict[str(ok_order_id)] = localNo

    # ----------------------------------------------------------------------
    """
    onSpotCancelOrder得回报 ws_data例子
        {
            "binary": 0,
            "channel": "ok_spot_cancel_order",
            "data": {
                "result": true,
                "order_id": "125433027"
            }
        }
    """
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

       # #self.gateway.writeLog(u'onSpotCancelOrder:删除self.orderDict[{}]'.format(ok_order_id))
        #del self.orderDict[ok_order_id]
        #self.gateway.writeLog(u'移除 localno: {} <==> ok_order_id:{}'.format(localNo,ok_order_id))
        #del self.orderIdDict[ok_order_id]
        #del self.localNoDict[localNo]
#
    # ----------------------------------------------------------------------
    def spotSendOrder(self, req):
        """
        发出委托指令
        :param req:
        :return:
        """
        self.gateway.writeLog(u'SpotApi.spotSendOrder()')
        # 取得币币配对symbol_pair,如果上层在symbol后添加 .OKEX，需要去除
        symbol = (req.symbol.split('.'))[0]

        if not symbol in self.registerSymbolPairArray:
            self.registerSymbolPairArray.add(symbol)

        # 获取匹配okex的订单类型
        type_ = priceTypeMapReverse[(req.direction, req.priceType)]

        # 本地委托号加1，并将对应字符串保存到队列中，返回基于本地委托号的vtOrderID
        self.localNo += 1

        self.gateway.writeLog(u'localNo:{}'.format(self.localNo))
        self.localNoQueue.put(str(self.localNo))
        vtOrderID = '.'.join([self.gatewayName, str(self.localNo)])
        self.gateway.writeLog(u'创建本地Order对象，vtOrderId:{}'.format(vtOrderID))

        # 创建本地order对象
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = symbol
        order.vtSymbol = order.symbol
        order.orderID = self.localNo
        order.vtOrderID = vtOrderID
        order.price = req.price
        order.totalVolume = req.volume
        order.direction, priceType = priceTypeMap[type_]
        order.offset = OFFSET_OPEN if req.direction == DIRECTION_LONG else OFFSET_CLOSE
        order.status = STATUS_NOTTRADED
        dt = datetime.now()
        order.orderTime = dt.strftime("%H:%M:%S.%f")
        self.localOrderDict[vtOrderID] = order

        # 调用ws api发送委托
        self.gateway.writeLog(u'调用ws api发送委托')
        self.spotTrade(symbol, type_, str(req.price), str(req.volume))
        self.gateway.writeLog('SpotSendOrder:symbol:{},Type:{},price:{},volume:{}'.format(symbol, type_, str(req.price), str(req.volume)))

        return vtOrderID

    # ----------------------------------------------------------------------
    def spotCancel(self, req):
        """
        发出撤单指令
        :param req:
        :return:
        """
        # symbol = spotSymbolMapReverse[req.symbol][:4]
        symbol = (req.symbol.split('.'))[0]
        localNo = req.orderID

        if localNo in self.localNoDict:
            orderID = self.localNoDict[localNo]
            self.spotCancelOrder(symbol, orderID)
        else:
            # 如果在系统委托号返回前客户就发送了撤单请求，则保存
            # 在cancelDict字典中，等待返回后执行撤单任务
            self.cancelDict[localNo] = req

    # ----------------------------------------------------------------------
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(float(s) / 1e3)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y-%m-%d")
        return date, time, dt

########################################################################
class OkexFuturesApi(WsFuturesApi):
    """okex的合约API实现"""

    # ----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(WsFuturesApi, self).__init__()

        self.gateway = gateway  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.active = False  # 若为True则会在断线后自动重连

        self.cbDict = {}
        self.tickDict = {}
        self.orderDict = {}
        self.localOrderDict = {}  # 本地缓存的order_dict，key 是 localNo.gatewayName

        self.channelSymbolMap = {}
        self.localNo = 1  # 本地委托号
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

    # ----------------------------------------------------------------------
    def setLeverage(self, __leverage):
        """
        设置杠杆比率
        :param __leverage:
        :return:
        """
        self._use_leverage = __leverage

    # ----------------------------------------------------------------------
    def onMessage(self, *args):
        """
        信息推送的处理
        :param ws:
        :param evt:
        :return:
        """
        if len(args)==0:
            return
        evt = args[-1]
        if isinstance(evt,bytes):
            # bytes => str => json
            decmp_evt = self.inflate(evt)
            ws_data = self.readData(decmp_evt)
        else:
            ws_data = self.readData(evt)

        if self.gateway.log_message:
            self.gateway.writeLog(u'FutureApi.onMessage:{}'.format(ws_data))

        # 返回dict
        if isinstance(ws_data, dict):
            if 'event' in ws_data:
                # 处理心跳得
                if ws_data['event'] == 'pong':
                    self.writeLog(u'heart beat response {}'.format(datetime.now()))
                    return
                else:
                    self.writeLog(u'其他 event:{}'.format(ws_data))
            else:
                self.writeLog(u'其他数据:{}'.format(ws_data))

        # 返回list
        if isinstance(ws_data, list):
            for data in ws_data:
                channel_value = data['channel'] if 'channel' in data else None
                if channel_value == None:
                    continue

                # 登录请求恢复
                if channel_value == 'login':
                    if 'data' in data:
                        login_data = data['data']
                        result = login_data['result'] if 'result' in login_data else False
                        if result:
                            self.writeLog(u'登录成功: {}'.format(datetime.now()))
                            self.gateway.futures_connected = True
                        else:
                            self.gateway.writeError(u'登录失败')
                            self.writeLog(u'登录失败: {},data:{}'.format(datetime.now(), data))
                    continue

                # 功能请求回复
                elif channel_value == "addChannel":
                    if 'data' in data:
                        channel_data = data['data']
                        result = channel_data['result'] if 'result' in channel_data else False
                        channel_value = channel_data["channel"]
                        if result:
                            self.writeLog(u'请求:{} 成功:'.format(channel_value))
                            continue
                    else:
                        self.gateway.writeError(u'addChannel回复数据没有data')
                        self.writeLog(u'not data in :addChannel:{}'.format(data))

                # 其他回调/数据推送
                callback = self.cbDict.get(channel_value)
                if callback:
                    try:
                        callback(data)
                    except Exception as ex:
                        self.gateway.writeError(u'回调{}发生异常'.format(channel_value))
                        self.writeLog(u'onMessage call back {} exception：{},{}'.format(channel_value, str(ex),
                                                                               traceback.format_exc()))
                else:
                    self.gateway.writeError(u'okFutureApi:出现无回调处理的channel:{}'.format(channel_value))
                    self.writeLog(u'unkonw msg:{}'.format(data))

    # ----------------------------------------------------------------------
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

    # #----------------------------------------------------------------------
    def onErrorMsg(self, data):
        """错误信息处理"""
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        if 'data' in data and 'error_code' in data['data']:
            error_code = str(data["data"]["error_code"])
            error.errorID = error_code
            error.errorMsg = u'FutureApi Error:{}'.format(FUTURES_ERROR_DICT.get(error_code))
            self.gateway.onError(error)

    # ----------------------------------------------------------------------
    def reconnect(self):
        """
        重连
        :return:
        """
        while not self.gateway.futures_connected:
            self.writeLog(u'okex Api_contract 等待10秒后重新连接')
            self.connect(self.apiKey, self.secretKey, self.trace)

            sleep(10)
            if not self.gateway.futures_connected:
                self.reconnect()

    # ----------------------------------------------------------------------
    def onClose(self, ws):
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

    # ----------------------------------------------------------------------
    def dealSymbolFunc(self, symbol):
        """
        分解委托单symbol
        :param symbol:
        :return:
        """
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

    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """
        订阅行情
        :param subscribeReq:
        :return:
        """
        try:
            # 分解出 合约对/合约/合约类型/杠杆倍数
            (symbol_pair, symbol, contract_type, leverage) = self.dealSymbolFunc(subscribeReq.symbol)
        except Exception as ex:
            self.writeLog(u'订阅合约行情异常:{}'.format(str(ex)))
            return

        if subscribeReq.symbol not in self.registered_symbols:
            # 登记合约对（btc_usd   ltc_usd   eth_usd   etc_usd   bch_usd）
            self.registered_symbols.add(subscribeReq.symbol)
            # 订阅行情
        self.subscribeSingleSymbol(symbol, contract_type, leverage)

    # ----------------------------------------------------------------------
    def subscribeSingleSymbol(self, symbol, contract_type, leverage):
        """
        订阅行情
        :param symbol: 合约，如btc，eth，etc等
        :param contract_type: 合约类型，当周，下周，季度
        :param leverage:杠杆倍数
        :return:
        """
        self.gateway.writeLog(u'FuturesApi.subscribeSingleSymbol:symbol:{},cotract_type:{},leverage:{}'.format(symbol, contract_type, leverage))
        if symbol in CONTRACT_SYMBOL:
            # 订阅tick行情
            self.subsribeFutureTicker(symbol, contract_type)
            # 订阅深度行情
            self.subscribeFutureDepth(symbol, contract_type)
            # 查询该合约的委托清单
            self.futureOrderInfo(symbol + "_usd", -1, contract_type, status="1", current_page=1, page_length=50)
            # 订阅该合约得市场成交
            #self.subscribeFutureTrades(symbol+"_usd",contract_type)
            # self.cbDict["ok_sub_futureusd_%s_trade_%s" % (symbol+'_usd', contract_type)] = self.onFutureSub

    # ----------------------------------------------------------------------
    def futureAllOrders(self):
        """
        发出查询所有合约委托查询
        :return:
        """
        for symbol in self.registered_symbols:
            # 根据已订阅的合约清单，逐一合约发出
            try:
                (symbol_pair, symbol, contract_type, leverage) = self.dealSymbolFunc(symbol)
                self.futureOrderInfo(symbol + "_usd", -1, contract_type, status="1", current_page=1, page_length=50)
            except Exception as ex:
                self.writeLog(u'dealSymbolFunc :{}异常:{}'.format(symbol,str(ex)))
                continue

        for orderId in self.orderIdDict.keys():
            # 根据缓存的委托单id，逐一发出委托查询
            order = self.orderDict.get(orderId, None)
            if order != None:
                try:
                    symbol_pair, symbol, contract_type, leverage = self.dealSymbolFunc(order.symbol)
                    self.futureOrderInfo(symbol + "_usd", orderId, contract_type, status="1", current_page=1,
                                         page_length=50)
                except Exception as ex:
                    self.writeLog(u'发出委托单查询异常:{}'.format(str(ex)))

    # ----------------------------------------------------------------------
    def onOpen(self, ws):
        """连接成功"""
        self.gateway.futures_connected = True
        self.writeLog(u'服务器OKEX期货连接成功')
        try:
            self.initCallback()
            self.writeLog(u'服务器OKEX期货回调函数设置成功')

            for symbol in CONTRACT_SYMBOL:
                self.channelSymbolMap[
                    "ok_sub_futureusd_%s_index" % symbol] = symbol + "_usd:%s:" + self._use_leverage # + "." + EXCHANGE_OKEX

                for use_contract_type in CONTRACT_TYPE:
                    use_symbol_name = symbol + "_usd:%s:%s" % (use_contract_type, self._use_leverage)
                    # Ticker数据
                    self.channelSymbolMap["ok_sub_futureusd_%s_ticker_%s" % (symbol, use_contract_type)] = use_symbol_name
                    # 盘口的深度
                    self.channelSymbolMap["ok_sub_future_%s_depth_%s_usd" % (symbol, use_contract_type)] = use_symbol_name
                    # 所有人的交易数据
                    self.channelSymbolMap["ok_sub_futureusd_%s_trade_%s" % (symbol, use_contract_type)] = use_symbol_name

                    contract = VtContractData()
                    contract.gatewayName = self.gatewayName
                    contract.symbol = use_symbol_name  + "." + EXCHANGE_OKEX
                    contract.exchange = EXCHANGE_OKEX
                    contract.vtSymbol = contract.symbol
                    contract.name = u'期货%s_%s_%s' % (symbol, use_contract_type, self._use_leverage)
                    contract.size = 0.00001
                    contract.priceTick = 0.00001
                    contract.productClass = PRODUCT_FUTURES
                    self.gateway.onContract(contract)

                    # print contract.vtSymbol , contract.name

                    quanyi_vtSymbol = symbol + "_usd_future_qy"  + "."+ EXCHANGE_OKEX
                    contract = VtContractData()
                    contract.gatewayName = self.gatewayName
                    contract.symbol = quanyi_vtSymbol
                    contract.exchange = EXCHANGE_OKEX
                    contract.vtSymbol = contract.symbol
                    contract.name = u'期货权益%s' % (symbol)
                    contract.size = 0.00001
                    contract.priceTick = 0.00001
                    contract.productClass = PRODUCT_FUTURES
                    self.gateway.onContract(contract)

            self.writeLog(u'服务器OKEX期货合约信息更新成功')


            self.login()
            # 连接后查询账户和委托数据
            self.futureUserInfo()
            self.futureAllUnfinishedOrderInfo()
            self.futureAllIndexSymbol()

            for symbol in self.registered_symbols:
                try:
                    self.writeLog(u'okex future_api 重新订阅:'.format(symbol))
                    # 分解出 合约对/合约/合约类型/杠杆倍数
                    (symbol_pair, symbol, contract_type, leverage) = self.dealSymbolFunc(symbol)
                    self.subscribeSingleSymbol(symbol, contract_type, leverage)
                except Exception as ex:
                    self.gateway.writeError(u'订阅合约行情异常:{},{}'.format(str(ex),traceback.format_exc()))
                    continue
        except Exception as ex:
            self.gateway.writeError(u'期货onOpen异常:{},{}'.format(str(ex), traceback.format_exc()))

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """快速记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    # ----------------------------------------------------------------------
    def LoopforceGetContractDict(self, unFishedSet):
        """
        递归强制获取合约信息
        :param unFishedSet:
        :return:
        """
        if len(unFishedSet) > 0:
            new_unfishedSet = set([])
            for symbol, use_contract_type in unFishedSet:
                t_contract_name = self.getContractName(symbol, use_contract_type)
                if t_contract_name != None:
                    self.contract_name_dict[t_contract_name] = {"symbol": symbol, "contract_type": use_contract_type}
                else:
                    new_unfishedSet.add((symbol, use_contract_type))

            if unFishedSet!=new_unfishedSet:
                self.LoopforceGetContractDict(new_unfishedSet)

    # ----------------------------------------------------------------------
    def initCallback(self):
        """初始化回调函数"""
        # USD_CONTRACT
        unfinished_contract_set = set([])
        for symbol in CONTRACT_SYMBOL:
            self.cbDict["ok_sub_futureusd_%s_index" % (symbol)] = self.onFutureIndexInfo
            for use_contract_type in CONTRACT_TYPE:
                self.cbDict["ok_sub_futureusd_%s_ticker_%s" % (symbol, use_contract_type)] = self.onTicker
                self.cbDict["ok_sub_future_%s_depth_%s_usd" % (symbol, use_contract_type)] = self.onDepth
                self.cbDict["ok_sub_futureusd_%s_trade_%s" % (symbol, use_contract_type)] = self.onTrade

                t_contract_name = self.getContractName(symbol, use_contract_type)
                if t_contract_name != None:
                    self.contract_name_dict[t_contract_name] = {"symbol": symbol, "contract_type": use_contract_type}
                else:
                    unfinished_contract_set.add((symbol, use_contract_type))

        self.LoopforceGetContractDict(unfinished_contract_set)

        # print self.contract_name_dict.keys()

        self.cbDict['ok_futureusd_trade'] = self.onFutureOrder
        self.cbDict['ok_futureusd_cancel_order'] = self.onFutureOrderCancel

        self.cbDict['ok_futureusd_userinfo'] = self.onFutureUserInfo
        self.cbDict['ok_futureusd_orderinfo'] = self.onFutureOrderInfo

        self.cbDict['ok_sub_futureusd_trades'] = self.onFutureSubTrades
        self.cbDict['ok_sub_futureusd_userinfo'] = self.onFutureSubUserinfo

        self.cbDict['ok_sub_futureusd_positions'] = self.onFutureSubPositions

    # ----------------------------------------------------------------------
    '''
    推送 币币交易指数过去
    websocket.send("{'event':'addChannel','channel':'ok_sub_futureusd_X_index'}");

        ① X值为：btc, ltc, eth, etc, bch
    # Request
    {'event':'addChannel','channel':'ok_sub_futureusd_btc_index'}
    # Response
    [
        {
            "data": {
                "timestamp": "1490341322021",
                "futureIndex": "998.0"
            },
            "channel": "ok_sub_futureusd_btc_index"
        }
    ]
    返回值说明
    
    futureIndex(string): 指数
    timestamp(string): 时间戳
    '''

    def onFutureIndexInfo(self, ws_data):
        """
        指数合约推送
        :param ws_data:
        :return:
        """
        data = ws_data.get('data')

        if data is None:
            return

        channel = ws_data['channel']

        # 获取日期/时间
        t_date, t_time,_ = self.generateDateTime(float(data["timestamp"]))
        # 获取指数值
        float_index = float(data["futureIndex"])

        # 根据channnel，获取合约
        symbol_pattern = self.channelSymbolMap[channel]
        for use_contract_type in CONTRACT_TYPE:
            # 合约，
            symbol = symbol_pattern % (use_contract_type)
            push_dic = {"symbol": symbol, "date": t_date, "time": t_time, "index": float_index}
            # 调用gateway，推送event事件
            self.gateway.onFutureIndexPush(push_dic)

    # ----------------------------------------------------------------------
    """
    期货行情推送 例子
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
    """

    def checkStatus(self):
        """
        检查状态
        :return:
        """
        if len(self.tickDict) > 0:
            symbol,last_tick = list(self.tickDict.items())[0]
            if (datetime.now() - last_tick.datetime).seconds > 60:
                return False

            return True
        else:
            return False

    def onTicker(self, ws_data):
        """
        期货行情推送
        :param ws_data:
        :return:
        """
        data = ws_data.get('data', {})
        if len(data) == 0:
            return

        channel = ws_data.get('channel')
        if channel is None:
            return

        try:
            symbol = self.channelSymbolMap[channel]
            # 首次到达tick，记录在tickDict缓存
            if symbol not in self.tickDict:
                tick = VtTickData()
                tick.exchange = EXCHANGE_OKEX
                tick.symbol =  '.'.join([symbol, tick.exchange])
                tick.vtSymbol = tick.symbol

                tick.gatewayName = self.gatewayName
                self.tickDict[symbol] = tick

                # 创建symbol对应得深度行情字典缓存
                self.bids_depth_dict[symbol] = {}
                self.asks_depth_dict[symbol] = {}
            else:
                tick = self.tickDict[symbol]

            # 更新
            tick.highPrice = float(data['high'])
            tick.lowPrice = float(data['low'])
            tick.lastPrice = float(data['last'])

            if symbol.startswith('btc'):
                tick.volume = float(str(data['vol']).replace(',', ''))
                tick.volume=(tick.volume/tick.lastPrice)*100
            else:
                tick.volume = float(str(data['vol']).replace(',', ''))
                tick.volume=(tick.volume/tick.lastPrice)*10


            self.contractIdToSymbol[str(data["contractId"])] = tick.symbol
            # 待深度行情推送onTick
        except Exception as ex:
            self.gateway.writeError(u'ContractApi.onTicker exception:{}'.format(str(ex)))
            self.gateway.writeLog(ws_data)
            self.gateway.writeLog(u'ContractApi.onTicker exception:{},{}'.format(str(ex), traceback.format_exc()))

    # ----------------------------------------------------------------------
    """
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
    """
    def onDepth(self, ws_data):
        """
        期货深度行情推送
        :param ws_data:
        :return:
        okex期货的深度数据原生返回是张数，需要转换为个数。转换公式（btc把10改为100，其他币种都是乘10）：张数/成交价*10=个数
        """
        channel = ws_data.get('channel')
        data = ws_data.get('data', {})
        if channel is None or len(data) == 0:
            return

        symbol = self.channelSymbolMap.get(channel)
        if symbol is None:
            return

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

            tick_bids_depth = self.bids_depth_dict[symbol]
            tick_asks_depth = self.asks_depth_dict[symbol]

            # 更新bids得价格深度
            for inf in data.get('bids', []):
                price1, vol1, vol2, acc_vol1, acc_vol2 = inf
                if abs(float(vol1)) < 0.00001 and price1 in tick_bids_depth:
                    del tick_bids_depth[price1]
                else:
                    tick_bids_depth[price1] = float(vol1)

            try:
                # 根据bidPrice价格排序
                arr = sorted(tick_bids_depth.items(), key=lambda x: x[0])

                # 取后五个
                tick.bidPrice1, tick.bidVolume1 = arr[-1]
                tick.bidPrice2, tick.bidVolume2 = arr[-2]
                tick.bidPrice3, tick.bidVolume3 = arr[-3]
                tick.bidPrice4, tick.bidVolume4 = arr[-4]
                tick.bidPrice5, tick.bidVolume5 = arr[-5]

            except Exception as ex:
                self.writeLog(u'ContractApi.onDepth exception:{},{}'.format(str(ex), traceback.format_exc()))

            for inf in data.get('asks', []):
                price1, vol1, vol2, acc_vol1, acc_vol2 = inf
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

            # 推送onTick事件
            newtick = copy(tick)
            self.gateway.onTick(newtick)

        except Exception as ex:
            self.writeLog(u'ContractApi.onDepth exception:{},{}'.format(str(ex), traceback.format_exc()))

    # ----------------------------------------------------------------------
    """
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
    """

    def onTrade(self, ws_data):
        """
        委托全部成交回报
        :param ws_data:
        :return:
        """
        self.writeLog(u'onTrade {}'.format(ws_data))

    # ----------------------------------------------------------------------

    """
        {
            "data":{
                "result":true,
                "order_id":"5017402127"
            },
            "channel":"ok_futureusd_order"
        }
    """
    def onFutureOrder(self, ws_data):
        """
        委托下单请求响应，
        :param ws_data: 出错代码，或者委托成功得order_id
        :return:
        """

        data = ws_data.get('data', {})
        error_code = data.get('error_code')
        if error_code is not None:
            self.gateway.writeError(u'onFutureOrder委托返回错误:{}'.format(FUTURES_ERROR_DICT.get(str(error_code))), error_id=error_code)
            self.gateway.writeLog(ws_data)
            localNo = self.localNoQueue.get_nowait()
            if localNo is None:
                return

            self.gateway.writeLog(u'onFutureOrder移除本地localNo:{}'.format(localNo))
            vtOrderId = '.'.join([self.gatewayName,str(localNo)])
            order = self.localOrderDict.get(vtOrderId)
            if order:
                order.orderID=localNo
                dt = datetime.now()
                order.symbol= '.'.join([order.symbol,self.gatewayName])
                order.vtsymbol=order.symbol
                order.totalVolume=order.totalVolume
                order.cancelTime = dt.strftime("%H:%M:%S.%f")
                order.status = STATUS_REJECTED
                self.gateway.writeLog(u'onFutureOrder发出OnOrder，拒单,vtOrderId={}'.format(vtOrderId))
                # 发送期货委托单（拒单消息）到vtGateway
                self.gateway.onOrder(order)
            return
        ok_order_id = data.get('order_id')

        if ok_order_id is None:
            self.gateway.writeError(u'FuturesApi.onFutureOrder 委托返回中，没有orderid')
            self.gateway.writeLog(ws_data)
            return

        ok_order_id = str(ok_order_id)

        # 从本地编号Queue中，FIFO，提取最早的localNo
        localNo = self.localNoQueue.get_nowait()
        if localNo is None:
            self.gateway.writeError(u'FuturesApi.onSportOrder，未找到本地LocalNo，检查日志')
            self.gateway.writeLog(ws_data)
            return

        self.gateway.writeLog(u'FuturesApi.onSportOrder,绑定 local:{}  <==> ok_order_id:{}'.format(localNo, ok_order_id))
        self.localNoDict[localNo] = ok_order_id
        self.orderIdDict[ok_order_id] = localNo

    # ----------------------------------------------------------------------
    """
            {
                "data":{
                    "result":true,
                    "order_id":"5017402127"
                },
                "channel":"ok_futureusd_cancel_order"
            }
    """

    def onFutureOrderCancel(self, ws_data):
        """
        委托撤单的响应"
        :param ws_data: 
        :return: 
        """""
        data = ws_data.get('data', {})

        if 'error_code' in data:
            error_code = data.get('error_code', 0)
            self.gateway.writeError(u'SpotApi.onFutureOrderCancel 委托返回错误:{}'.format(FUTURES_ERROR_DICT.get(error_code)), error_id=error_code)
            self.gateway.writeLog(ws_data)
            return

        ok_order_id = data.get('order_id')
        if ok_order_id is None:
            self.gateway.writeError(u'SpotApi.onFutureOrderCancel 委托返回中，没有orderid')
            self.gateway.writeLog(ws_data)
            return

        ok_order_id = str(ok_order_id)
        # 获取本地委托流水号
        localNo = self.orderIdDict[ok_order_id]

        # 发送onOrder事件
        order = self.orderDict[ok_order_id]
        dt = datetime.now()
        order.cancelTime = dt.strftime("%H:%M:%S.%f")
        order.status = STATUS_CANCELLED
        # 发送现货委托单（撤单消息）到vtGateway
        self.gateway.onOrder(order)

        # 删除本地委托号与orderid的绑定
        #del self.orderDict[orderId]
        #del self.orderIdDict[orderId]
        #del self.localNoDict[localNo]

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
    balance(double): 账户余额
    symbol(string)：币种
    keep_deposit(double)：保证金
    profit_real(double)：已实现盈亏
    unit_amount(int)：合约价值
    
    实际日志（逐仓模式)
  {u'info': {
     u'ltc': {u'contracts': [], u'balance': 0, u'rights': 0}, 
     u'bch': {u'contracts': [], u'balance': 0, u'rights': 0}, 
     u'eos': {u'contracts': [], u'balance': 0, u'rights': 0}, 
     u'etc': {u'contracts': [], u'balance': 4.98, u'rights': 4.98}, 
     u'btg': {u'contracts': [], u'balance': 0, u'rights': 0}, 
     u'btc': {u'contracts': [], u'balance': 0, u'rights': 0}, 
     u'eth': {u'contracts': [], u'balance': 0, u'rights': 0}, 
     u'xrp': {u'contracts': [], u'balance': 0, u'rights': 0}
     },u'result': True}
    # 逐仓模式，持有期货合约
    u'etc': {u'contracts': 
              [{u'available': 4.92279753, u'contract_id': 201802160040063L, u'profit': -0.01702246, u'unprofit': 0.0005, 
                u'freeze': 0, u'contract_type': u'this_week', u'balance': 0.05720247, u'bond': 0.04018001}], 
            u'balance': 4.92279753, u'rights': 4.96357399},
 
  {'eos': {'risk_rate': 10000, 'account_rights': 0, 'profit_real': 0, 'keep_deposit': 0, 'profit_unreal': 0}, 
  'btc': {'risk_rate': 10000, 'account_rights': 0.01, 'profit_real': 0, 'keep_deposit': 0, 'profit_unreal': 0}, 
  'ltc': {'risk_rate': 10000, 'account_rights': 0, 'profit_real': 0, 'keep_deposit': 0, 'profit_unreal': 0}, 
  'etc': {'risk_rate': 10000, 'account_rights': 0, 'profit_real': 0, 'keep_deposit': 0, 'profit_unreal': 0}, 
  'xrp': {'risk_rate': 10000, 'account_rights': 0, 'profit_real': 0, 'keep_deposit': 0, 'profit_unreal': 0}, 
  'eth': {'risk_rate': 10000, 'account_rights': 0, 'profit_real': 0, 'keep_deposit': 0, 'profit_unreal': 0}, 
  'btg': {'risk_rate': 10000, 'account_rights': 0, 'profit_real': 0, 'keep_deposit': 0, 'profit_unreal': 0}, 
  'bch': {'risk_rate': 10000, 'account_rights': 0, 'profit_real': 0, 'keep_deposit': 0, 'profit_unreal': 0}}
    '''

    # ----------------------------------------------------------------------
    def onFutureUserInfo(self, ws_data):
        """
        合约账户信息推送（账户权益/已实现盈亏/未实现盈亏/可用/已用/冻结）
        :param ws_data:
        :return:
        """
        data = ws_data.get('data', {})
        if len(data) == 0:
            self.writeLog(u'FuturesApi.onFutureUserInfo:not data in:{}'.format(ws_data))
            return

        info = data.get("info", {})
        if len(data) == 0:
            self.writeLog(u'FuturesApi.onFutureUserInfo:not info in:{}'.format(ws_data))
            return

        for symbol, s_inf in info.items():
            if "account_rights" in s_inf.keys():
                # 说明是 全仓返回
                account = VtAccountData()
                account.gatewayName = self.gatewayName
                account.accountID = u'[全仓]{}'.format(symbol)
                account.vtAccountID = account.accountID
                account.balance = float(s_inf.get('account_rights',0.0))
                account.closeProfit = float(s_inf.get('profit_real',0.0))
                account.positionProfit = float(s_inf.get('profit_unreal',0.0))
                account.margin = float(s_inf.get('keep_deposit',0.0))

                # 更新持仓信息
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName #+ u'_Future'
                pos.symbol = u'{}.{}_Future'.format(symbol, EXCHANGE_OKEX)
                pos.vtSymbol = u'{}.{}_Future'.format(symbol, EXCHANGE_OKEX)
                pos.position = account.balance
                pos.frozen = float(s_inf.get('keep_deposit',0.0))
                pos.direction = DIRECTION_NET
                self.gateway.onPosition(pos)

                self.gateway.onAccount(account)

                # 如果该合约账号的净值大于0,则通过rest接口，逐一合约类型获取持仓
                if account.balance > 0:
                    for contractType in CONTRACT_TYPE:
                        self.query_future_position(symbol=symbol,contractType=contractType,leverage=self._use_leverage)
            else:
                # 说明是逐仓返回
                t_contracts = s_inf.get('contracts',[])
                t_balance = float(s_inf.get('balance',0.0))
                t_rights = float(s_inf.get('rights',0.0))

                #if t_balance > 0 or t_rights > 0:
                account = VtAccountData()
                account.gatewayName = self.gatewayName #+ u'_Future'
                account.accountID = u'[逐仓]{}'.format(symbol)
                account.vtAccountID = account.accountID
                account.balance = t_rights
                account.available = t_balance

                # 更新持仓信息
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName #+ u'_Future'
                pos.symbol = u'{}.{}_Future'.format(symbol,EXCHANGE_OKEX)
                pos.vtSymbol = u'{}.{}_Future'.format(symbol,EXCHANGE_OKEX)
                pos.position = t_rights
                pos.frozen = t_rights - t_balance
                pos.direction = DIRECTION_NET
                self.gateway.onPosition(pos)

            for contract in t_contracts:
                # 保证金
                account.margin += contract.get('bond',0.0)
                # 平仓盈亏
                account.closeProfit += contract.get('profit',0.0)
                # 持仓盈亏
                account.positionProfit += contract.get('unprofit',0.0)


                if account.balance > 0 or account.available > 0:
                    for contractType in CONTRACT_TYPE:
                        self.query_future_position_4fix(symbol=symbol, contractType=contractType)

                self.gateway.onAccount(account)

    def query_future_position(self, symbol, contractType, leverage):
        """全仓模式下，查询持仓信息"""
        qry_symbol = '{}_usd'.format(symbol) + ':' + contractType
        if qry_symbol in self.queryed_pos_symbols:
            sleep(0.1)
        else:
            self.queryed_pos_symbols.add(qry_symbol)
        resp = self.get_future_position(symbol='{}_usd'.format(symbol), contractType=contractType)
        result = resp.get('result', False)
        holdings = resp.get('holding', [])

        if result and len(holdings) > 0:
            for holding in holdings:
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName #+ u'_Future'
                contract_symbol = holding.get('symbol', '{}_usd'.format(symbol)) + ':' + contractType + ':' + str(
                    holding.get('lever_rate', leverage))
                # 如果此合约不在已订阅清单中，重新订阅
                if contract_symbol not in self.registered_symbols:
                    v = VtSubscribeReq()
                    v.symbol = contract_symbol
                    self.subscribe(v)

                pos.symbol = '.'.join([contract_symbol, EXCHANGE_OKEX])
                pos.vtSymbol = pos.symbol
                tick = self.tickDict.get(contract_symbol, None)

                if holding.get('buy_amount', 0) > 0:
                    # 持有多仓
                    pos.direction = DIRECTION_LONG
                    pos.vtPositionName = pos.symbol + pos.direction
                    pos.price = holding.get('buy_price_avg', 0.0)
                    price = tick.lastPrice if tick is not None else pos.price
                    if price == 0.0:
                        continue

                    # 20181110 ，改回用多少份合约
                    pos.position = holding.get('buy_amount')

                    if holding.get('buy_available') > 0:
                        pos.frozen = pos.position - holding.get('buy_available',0)
                    else:
                        pos.frozen = 0

                    pos.positionProfit = holding.get('buy_profit_real', 0.0)
                    self.gateway.onPosition(pos)
                if holding.get('sell_amount', 0) > 0:
                    sell_pos = copy(pos)
                    sell_pos.direction = DIRECTION_SHORT
                    sell_pos.vtPositionName = sell_pos.symbol + sell_pos.direction
                    sell_pos.price = holding.get('sell_price_avg', 0.0)
                    price = tick.lastPrice if tick is not None else sell_pos.price
                    if price == 0:
                        continue

                    # 20181110 改回用多少份合约
                    sell_pos.position =holding.get('sell_amount')
                    if holding.get('sell_available', 0) > 0:
                        sell_pos.frozen = sell_pos.position -  holding.get('sell_available')
                    else:
                        sell_pos.frozen = 0
                    sell_pos.positionProfit = holding.get('sell_profit_real', 0.0)
                    self.gateway.onPosition(sell_pos)

    def query_future_position_4fix(self,symbol, contractType,leverate=1):
        """
        逐仓模式下，查询仓位
        :param symbol:
        :param contractType:
        :param leverate: 默认返回10倍杠杆持仓 type=1 返回全部持仓数据
        :return:
        """
        qry_symbol = '{}_usd'.format(symbol) + ':' + contractType
        if qry_symbol in self.queryed_pos_symbols:
            sleep(0.1)
        else:
            self.queryed_pos_symbols.add(qry_symbol)
        resp = self.get_future_position_4fix(symbol='{}_usd'.format(symbol), contractType=contractType,type1=leverate)
        result = resp.get('result', False)
        holdings = resp.get('holding', [])

        if result and len(holdings) > 0:
            for holding in holdings:
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName #+ u'_Future'
                contract_symbol = holding.get('symbol', '{}_usd'.format(symbol)) + ':' + contractType + ':' + str(
                    holding.get('lever_rate', 10))
                # 如果此合约不在已订阅清单中，重新订阅
                if contract_symbol not in self.registered_symbols:
                    v = VtSubscribeReq()
                    v.symbol = contract_symbol
                    self.subscribe(v)

                pos.symbol = '.'.join([contract_symbol, EXCHANGE_OKEX])
                pos.vtSymbol = pos.symbol
                tick = self.tickDict.get(contract_symbol, None)
                pos.gatewayName = self.gatewayName #+ u'_Future'
                if holding.get('buy_amount', 0) > 0:
                    # 持有多仓
                    pos.direction = DIRECTION_LONG
                    pos.vtPositionName = pos.symbol + pos.direction
                    pos.price = holding.get('buy_price_avg', 0.0)
                    price = tick.lastPrice if tick is not None else pos.price
                    if price == 0.0:
                        continue

                    pos.position =holding.get('buy_amount')
                    if holding.get('buy_available') > 0:
                        pos.frozen = pos.position -  holding.get('buy_available',0)
                    else:
                        pos.frozen = 0
                    pos.positionProfit = holding.get('profit_real', 0.0)
                    self.gateway.onPosition(pos)
                if holding.get('sell_amount', 0) > 0:
                    sell_pos = copy(pos)
                    sell_pos.direction = DIRECTION_SHORT
                    sell_pos.vtPositionName = sell_pos.symbol + sell_pos.direction
                    sell_pos.price = holding.get('sell_price_avg', 0.0)
                    price = tick.lastPrice if tick is not None else sell_pos.price
                    if price == 0:
                        continue
                    sell_pos.position =holding.get('sell_amount')
                    if holding.get('sell_available', 0) > 0:
                        sell_pos.frozen = sell_pos.position - holding.get('sell_available',0)
                    else:
                        sell_pos.frozen = 0
                    sell_pos.positionProfit = holding.get('profit_real', 0.0)
                    self.gateway.onPosition(sell_pos)
    # ----------------------------------------------------------------------
    """ 所有委托查询回报 ws_data
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
    """
    def onFutureOrderInfo(self, ws_data):
        """
        所有委托信息查询响应
        :param ws_data:
        :return:
        """
        error_code = ws_data.get('error_code')
        if error_code is not None:
            self.gateway.writeError(u'期货委托查询报错:{}'.format(FUTURES_ERROR_DICT.get(error_code)), error_id=error_code)
            self.gateway.writeLog(u'FutureApi.onFutureOrderInfo:{}'.format(ws_data))
            return

        data = ws_data.get("data", {})

        for order_data in data.get('orders', []):
            orderId = str(order_data['order_id'])
            localNo = str(self.localNo)

            if orderId not in self.orderIdDict:
                # orderId 不在本地缓存中，需要增加一个绑定关系
                while str(self.localNo) in self.localNoDict:
                    self.localNo += 1
                localNo = str(self.localNo)
                # 绑定localNo 与 orderId
                self.localNoDict[localNo] = orderId
                self.orderIdDict[orderId] = localNo
                self.writeLog(u'onFutureOrderInfo add orderid: local:{}<=>okex:{}'.format(localNo,orderId))
            else:
                # orderid在本地缓存中，
                localNo = self.orderIdDict[orderId]
                # 检验 localNo是否在本地缓存，没有则补充
                if localNo not in self.localNoDict:
                    self.localNoDict[localNo] = orderId
                    self.writeLog(u'onFutureOrderInfo update orderid: local:{}<=>okex:{}'.format(localNo, orderId))


            # order新增或更新在orderDict
            if orderId not in self.orderDict:
                order = VtOrderData()
                order.gatewayName = self.gatewayName
                contract_name = order_data["contract_name"]
                dic_info = self.contract_name_dict[contract_name]

                use_contract_type = dic_info["contract_type"]
                order.symbol = '.'.join([order_data["symbol"] + ":" + use_contract_type + ":" + str(self._use_leverage), EXCHANGE_OKEX])

                order.vtSymbol = order.symbol
                order.orderID = self.orderIdDict[orderId]                # 更新orderId为本地的序列号
                order.vtOrderID = '.'.join([self.gatewayName, order.orderID])

                order.price = order_data.get('price')
                #volume_rate = 100 if order.symbol.startswith('btc') else 10
                order.totalVolume = order_data.get('amount')
                order.direction, offset = priceContractOffsetTypeMap.get(str(order_data.get('type')))
                order.orderTime = datetime.now().strftime("%H:%M:%S.%f")
                self.orderDict[orderId] = order
                self.gateway.writeLog(u'新增本地orderDict缓存,okex orderId:{},order.orderid:{}'.format(orderId, order.orderID))
            else:
                order = self.orderDict[orderId]

            order.tradedVolume = order_data['deal_amount']
            order.status = statusMap[int(order_data['status'])]
            # 推送期货委托单到vtGatway.OnOrder中
            self.gateway.onOrder(copy(order))

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

    # ----------------------------------------------------------------------
    def onFutureSubTrades(self, ws_data):
        """
        交易信息回报
        :param ws_data:
        :return:
        """
        error_code = ws_data.get('error_code')
        if error_code is not None:
            self.gateway.writeError(u'期货交易报错:{}'.format(FUTURES_ERROR_DICT.get(error_code)), error_id=error_code)
            self.gateway.writeLog(u'FutureApi.onFutureSubTrades:{}'.format(ws_data))
            return

        data = ws_data.get("data")
        if data is None:
            self.gateway.writeError(u'期货交易报错:No data')
            self.gateway.writeLog(u'FutureApi.onFutureSubTrades: not data {}'.format(ws_data))
            return

        orderId = str(data["orderid"])                          # okex的委托编号
        use_contract_type = data["contract_type"]               # 合约类型

        localNo = self.orderIdDict.get(orderId, None)           # 本地委托编号

        if localNo == None:
            self.gateway.writeError(u'期货交易回报，非本地发出:orderid={}'.format(orderId))
            self.gateway.writeLog(u'FutureApi.onFutureSubTrades: not localNo,bypassing this trade {}'.format(ws_data))
            return

        # 委托信息,如果不在本地缓存，创建一个
        if orderId not in self.orderDict:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            contract_name = data.get("contract_name")
            contract_info = self.contract_name_dict.get(contract_name)
            if contract_info is None:
                self.gateway.writeError(u'期货交易回报，找不到合约的登记信息')
                self.gateway.writeLog(u'no contract_name:{} in self.contract_name_dict'.format(contract_name))
                return

            symbol = contract_info["symbol"] + "_usd"                                        # 自动添加_usd结尾
            future_symbol = ':'.join([symbol, use_contract_type, str(self._use_leverage)])   # 满足格式
            order.symbol = '.'.join([future_symbol, EXCHANGE_OKEX])                          # 合约.OKE
            order.vtSymbol = order.symbol
            order.orderID = localNo
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            order.price = float(data['price'])
            order.totalVolume = float(data['amount'])
            order.direction, order.offset = priceContractOffsetTypeMap[str(data['type'])]
            order.tradedVolume = float(data['deal_amount'])
            order.status = statusMap[data['status']]
            self.orderDict[orderId] = order
            self.gateway.writeLog(u'新增order,orderid:{},symbol:{},data:{}'.format(order.orderID,order.symbol,data))
        else:
            # 更新成交数量/状态
            order = self.orderDict[orderId]

            self.gateway.writeLog(u'orderid:{},tradedVolume:{}=>{},status:{}=>{}'
                                  .format(order.orderID,
                                          order.tradedVolume, float(data['deal_amount']),
                                          order.status, statusMap[data['status']]))
            order.tradedVolume = float(data['deal_amount'])
            order.status = statusMap[data['status']]

        # 发出期货委托事件
        self.gateway.onOrder(copy(order))

        # 判断成交数量是否有变化，有，则发出onTrade事件
        bef_volume = self.recordOrderId_BefVolume.get(orderId, 0.0)
        now_volume = float(data['deal_amount']) - bef_volume

        if now_volume > 0.000001:
            self.recordOrderId_BefVolume[orderId] = float(data['deal_amount'])
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            trade.symbol = order.symbol
            trade.vtSymbol = order.symbol
            self.tradeID += 1
            trade.tradeID = str(self.tradeID)
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
            trade.orderID = localNo
            trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])

            trade.price = float(data['price'])
            trade.volume = float(now_volume)

            trade.direction, trade.offset = priceContractOffsetTypeMap[str(data['type'])]

            trade.tradeTime = (data["create_date_str"].split(' '))[1]  # u'2018-02-10 18:34:21

            self.gateway.onTrade(trade)

    def onFutureSubDeals(self,ws_data):
        """市场上所有得合约成交"""
        pass

    '''
    # Response    
    OKEX的合约是OKEX推出的以BTC/LTC等币种进行结算的虚拟合约产品，每一张合约分别代表100美元的BTC，或10美元的其他币种（LTC,ETH等）
    
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

    # ----------------------------------------------------------------------
    def onFutureSubUserinfo(self, ws_data):
        """
        子账户持仓信息回报
        :param ws_data:
        :return:
        """
        u_inf = ws_data['data']
        self.gateway.writeLog(u'onFutureSubUserinfo:{}'.format(ws_data))
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

    def get_future_position(self,symbol,contractType):
        """
        全仓用户持仓查询
        https://github.com/okcoin-okex/API-docs-OKEx.com/blob/master/API-For-Futures-CN/%E5%90%88%E7%BA%A6%E4%BA%A4%E6%98%93REST%20API.md

        :return:
        """
        try:
            future_rest = OKCoinFuture(url=OKEX_FUTURE_HOST, apikey=self.gateway.apiKey, secretkey=self.gateway.secretKey)
            resp = future_rest.future_position(symbol, contractType)
            result = json.loads(resp)
        except Exception as ex:
            self.writeLog(u'get_future_position异常:{},{}'.format(str(ex),traceback.format_exc()))
            result = {'result':False}
        return result

    def get_future_position_4fix(self,symbol,contractType,type1):
        """
        逐仓用户持仓查询
        https://github.com/okcoin-okex/API-docs-OKEx.com/blob/master/API-For-Futures-CN/%E5%90%88%E7%BA%A6%E4%BA%A4%E6%98%93REST%20API.md

        :return:
        """
        try:
            future_rest = OKCoinFuture(url = OKEX_FUTURE_HOST,apikey=self.gateway.apiKey,secretkey=self.gateway.secretKey)
            resp = future_rest.future_position_4fix(symbol,contractType,type1)
            result = json.loads(resp)
        except Exception as ex:
            self.writeLog(u'get_future_position_4fix异常:{},{}'.format(str(ex), traceback.format_exc()))
            result = {'result': False}
        return result

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
    
    {u'binary': 0, u'data': 
    {u'positions': 
    [{u'contract_name': u'ETC0216', u'balance': 0.01606774, u'contract_id': 201802160040063L, u'fixmargin': 0.0,
     u'position_id': 73790127, u'avgprice': 24.46, u'eveningup': 0.0, u'profitreal': -0.01606774, 
     u'hold_amount': 0.0, u'costprice': 24.46, u'position': 1, u'lever_rate': 10, u'bondfreez': 0.04085301, u'forcedprice': 0.0}, 
     
    {u'contract_name': u'ETC0216', u'balance': 0.01606774, u'contract_id': 201802160040063L, u'fixmargin': 0.0,
     u'position_id': 73790127,u'avgprice': 0.0, u'eveningup': 0.0, u'profitreal': -0.01606774, 
     u'hold_amount': 0.0, u'costprice':0.0, u'position': 2, u'lever_rate': 10, u'bondfreez': 0.04085301, u'forcedprice': 0.0}, 
     {u'contract_name': u'ETC0216', u'balance': 0.01606774, u'contract_id': 201802160040063L, u'fixmargin': 0.0, 
     u'position_id': 73790127, u'avgprice': 0.0, u'eveningup': 0.0, u'profitreal': -0.01606774, u'hold_amount': 0.0, 
     u'costprice': 0.0, u'position': 1, u'lever_rate': 20, u'bondfreez': 0.04085301, u'forcedprice': 0.0}, 
     {u'contract_name': u'ETC0216', u'balance': 0.01606774, u'contract_id': 201802160040063L, u'fixmargin': 
     0.0, u'position_id': 73790127, u'avgprice': 0.0, u'eveningup': 0.0, u'profitreal': -0.01606774, 
     u'hold_amount': 0.0, u'costprice': 0.0, u'position': 2, u'lever_rate': 20, u'bondfreez': 0.04085301, u'forcedprice': 0.0}],
      u'symbol': u'etc_usd', u'user_id': 6548935}, u'channel': u'ok_sub_futureusd_positions'}
        '''

    # ----------------------------------------------------------------------
    def onFutureSubPositions(self, ws_data):
        """期货子账号仓位推送"""
        # 这个逐仓才是实际的仓位 ！！

        data = ws_data.get("data")
        if data is None:
            self.gateway.writeError(u'onFutureSubPositions: no data in :{}'.format(ws_data))
            return

        symbol = data.get('symbol')
        user_id = data.get('user_id')

        positions = data["positions"]
        for inf in positions:
            if 'fixmargin' in inf.keys():
                # 逐仓模式
                contract_name = inf["contract_name"]
                position_leverage = str(inf["lever_rate"])

                # print contract_name , position_leverage , self._use_leverage
                if int(position_leverage) == int(self._use_leverage):
                    dic_inf = self.contract_name_dict[contract_name]
                    use_contract_type = dic_inf["contract_type"]

                    # print dic_inf
                    pos = VtPositionData()
                    pos.gatewayName = self.gatewayName #+ u'_Future'

                    if int(inf["position"]) == 1:
                        pos.direction = DIRECTION_LONG
                    else:
                        pos.direction = DIRECTION_SHORT
                    contract_symbol = symbol + ":" + use_contract_type + ":" + position_leverage
                    pos.symbol = contract_symbol  + "." + EXCHANGE_OKEX
                    pos.vtSymbol = pos.symbol
                    pos.vtPositionName = pos.symbol + "." + pos.direction

                    # 如果此合约不在已订阅清单中，重新订阅
                    if contract_symbol not in self.registered_symbols:
                        v = VtSubscribeReq()
                        v.symbol = contract_symbol
                        self.subscribe(v)

                    # 获取实时价格
                    tick = self.tickDict.get(symbol + ":" + use_contract_type + ":" +position_leverage, None)
                    pos.price = float(inf.get('avgprice', 0.0))
                    price = pos.price if tick is None else tick.lastPrice
                    if price == 0.0:
                        continue

                    pos.frozen = float(inf.get("hold_amount",0.0)) - float(inf.get('eveningup',0.0))
                    pos.position = float(inf.get("hold_amount",0.0))
                    pos.positionProfit = float(inf.get("profitreal",0.0))
                    # print inf , pos.symbol
                    self.gateway.onPosition(pos)
            else:
                # 全仓模式
                # 通过合约名称，获取合约类型
                contract_name = inf["contract_name"]
                dic_inf = self.contract_name_dict[contract_name]
                use_contract_type = dic_inf.get("contract_type")

                #
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName #+ u'_Future'

                # 持仓合约的方向
                pos.direction = DIRECTION_LONG if int(inf.get("position",0)) == 1 else DIRECTION_SHORT

                pos.symbol = symbol + ":" + use_contract_type + ":" + str(self._use_leverage)  + "." + EXCHANGE_OKEX
                pos.vtSymbol = pos.symbol
                pos.vtPositionName = pos.symbol + "." + pos.direction

                # 获取实时价格
                tick = self.tickDict.get(symbol + ":" + use_contract_type + ":" + str(self._use_leverage),None)
                pos.price = float(inf.get('costprice', 0.0))
                price = pos.price if tick is None else tick.lastPrice
                if price == 0.0:
                    continue
                # 计算持仓量/冻结量： 100(或10) * hold_amount/ 价格

                pos.frozen = (float(inf.get('hold_amount',0.0)) - float(inf.get('eveningup',0.0)))
                pos.position =  float(inf.get('hold_amount',0.0))
                pos.positionProfit = float(inf.get('realized',0.0))

                # print inf , pos.symbol
                self.gateway.onPosition(pos)

    # ----------------------------------------------------------------------
    def futureSendOrder(self, req):
        """
        发委托单
        :param req:
        :return:
        """
        try:
            (symbol_pair, symbol, contract_type, leverage) = self.dealSymbolFunc(req.symbol)
        except Exception as ex:
            self.gateway.writeError(u'请求合约代码格式错误:{}'.format(req.symbol))
            self.writeLog(u'futureSendOrder 请求合约代码格式错误:{},exception:{},{}'.format(req.symbol,str(ex),traceback.format_exc()))
            return ''

        # print symbol_pair(例如:btc_usd) ,  symbol(btc), contract_type(this_week) , leverage(10)
        type_ = priceContractTypeMapReverse[(req.direction, req.offset)]
        self.writeLog(u'futureSendOrder:{},{},{},{},{}'.format(symbol_pair,  symbol, contract_type, leverage, type_))
        # 本地委托号加1，并将对应字符串保存到队列中，返回基于本地委托号的vtOrderID
        self.localNo += 1
        self.localNoQueue.put(str(self.localNo))
        vtOrderID = '.'.join([self.gatewayName, str(self.localNo)])
        self.writeLog(u'futureSendOrder:创建本地订单:orderId:{}'.format(vtOrderID))

        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = symbol
        order.vtSymbol = order.symbol
        order.orderID = self.localNo
        order.vtOrderID = vtOrderID
        order.price = req.price
        order.totalVolume = req.volume
        order.direction = req.direction
        order.offset = req.offset
        order.status = STATUS_NOTTRADED
        dt = datetime.now()
        order.orderTime = dt.strftime("%H:%M:%S.%f")
        self.localOrderDict[vtOrderID] = order

        # 100美金（btc）；10美金（其他）/每份合约
        volume_rate = 100 if symbol.startswith('btc') else 10
        # 预计冻结的币量
        frozend_quote = (volume_rate/order.price) * req.volume
        # 计算杠杆后的币量
        order_amount = frozend_quote * int(leverage)

        self.writeLog(u'futureSendOrder 发送:symbol:{},合约类型:{},交易类型:{},价格:{},合约委托数:{},预计冻结{}:{},期货总额:{}'.
                      format(symbol + "_usd", contract_type , type_ , str(req.price), str(req.volume),
                             frozend_quote,symbol,order_amount,symbol))
        try:

            #orginal_volume = req.volume
            #amount = round((req.volume * req.price)/volume_rate)
            #req.volume = 1 if amount== 0 else amount
            #self.writeLog(u'转换为ok合约数:{}=>{}'.format(orginal_volume, req.volume))
            self.futureTrade(symbol + "_usd", contract_type, type_, str(req.price), str(req.volume),
                             _lever_rate=self._use_leverage)

            return vtOrderID
        except Exception as ex:
            self.gateway.writeError(u'futureSendOrder发送委托失败:{}'.format(str(ex)))
            self.writeLog(u'futureSendOrder发送委托失败.{}'.format(traceback.format_exc()))
            return ''
    # ----------------------------------------------------------------------
    def futureCancel(self, req):
        """
        发出撤单请求
        :param req:
        :return:
        """
        try:
            (symbol_pair, symbol, contract_type, leverage) = self.dealSymbolFunc(req.symbol)
        except Exception as ex:
            self.writeLog(u'futureCancel 异常:{}'.format(str(ex)))
            return

        localNo = req.orderID

        if localNo in self.localNoDict:
            # 找出okex的委托流水号
            orderID = self.localNoDict[localNo]
            # 调用接口发出撤单请求
            self.futureCancelOrder(symbol + "_usd", orderID, contract_type)
        else:
            # 如果在系统委托号返回前客户就发送了撤单请求，则保存
            # 在cancelDict字典中，等待返回后执行撤单任务
            self.cancelDict[localNo] = req

    # ----------------------------------------------------------------------
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(float(s) / 1e3)
        time = dt.strftime("%H:%M:%S.%f")
        date = dt.strftime("%Y%m%d")
        return date, time,dt

