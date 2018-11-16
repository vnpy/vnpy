# encoding: UTF-8

'''
'''


from __future__ import print_function

import logging
import os
import json
import hashlib
import hmac
import sys
import time
import traceback
from datetime import datetime, timedelta
from copy import copy
from math import pow
from urllib import urlencode

from requests import ConnectionError

from vnpy.api.rest import RestClient, Request
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath


REST_HOST = 'https://www.bitmex.com/api/v1'
WEBSOCKET_HOST = 'wss://www.bitmex.com/realtime'

TESTNET_REST_HOST = 'https://testnet.bitmex.com/api/v1'
TESTNET_WEBSOCKET_HOST = 'wss://testnet.bitmex.com/realtime'


# 委托状态类型映射
statusMapReverse = {}
statusMapReverse['New'] = STATUS_NOTTRADED
statusMapReverse['Partially filled'] = STATUS_PARTTRADED
statusMapReverse['Filled'] = STATUS_ALLTRADED
statusMapReverse['Canceled'] = STATUS_CANCELLED
statusMapReverse['Rejected'] = STATUS_REJECTED

# 方向映射
directionMap = {}
directionMap[DIRECTION_LONG] = 'Buy'
directionMap[DIRECTION_SHORT] = 'Sell'
directionMapReverse = {v: k for k, v in directionMap.items()}

# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = 'Limit'
priceTypeMap[PRICETYPE_MARKETPRICE] = 'Market'


########################################################################
class BitmexGateway(VtGateway):
    """Bitfinex接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName=''):
        """Constructor"""
        super(BitmexGateway, self).__init__(eventEngine, gatewayName)

        self.restApi = BitmexRestApi(self)
        self.wsApi = BitmexWebsocketApi(self)

        self.qryEnabled = False         # 是否要启动循环查询

        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)

        self.exchange = constant.EXCHANGE_BITMEX

    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        try:
            f = open(self.filePath)
        except IOError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'读取连接配置出错，请检查'
            self.onLog(log)
            return

        # 解析json文件
        setting = json.load(f)
        f.close()
        try:
            apiKey = str(setting['apiKey'])
            apiSecret = str(setting['apiSecret'])
            sessionCount = int(setting['sessionCount'])
            symbols = setting['symbols']
            testnet = setting.get('testnet', False)
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

        # 创建行情和交易接口对象
        self.restApi.connect(apiKey, apiSecret, sessionCount, testnet)
        self.wsApi.connect(apiKey, apiSecret, symbols, testnet)

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        self.wsApi.subscribeMarketData(subscribeReq.symbol)

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.restApi.sendOrder(orderReq)

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.restApi.cancelOrder(cancelOrderReq)

    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.restApi.stop()
        self.wsApi.stop()

    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.queryAccount]

            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 1         # 查询触发点
            self.qryNextFunction = 0    # 上次运行的查询函数索引

            self.startQuery()

    #----------------------------------------------------------------------
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

    #----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)

    #----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled


########################################################################
class BitmexRestApi(RestClient):
    """REST API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(BitmexRestApi, self).__init__()

        self.gateway = gateway                  # type: BitmexGateway # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.apiKey = ''
        self.apiSecret = ''

        self.orderId = 1000000
        self.loginTime = 0

    #----------------------------------------------------------------------
    def sign(self, request):
        """BitMEX的签名方案"""
        # 生成签名
        expires = int(time.time() + 5)

        if request.params:
            query = urlencode(request.params)
            path = request.path + '?' + query
        else:
            path = request.path

        if request.data:
            request.data = urlencode(request.data)
        else:
            request.data = ''

        msg = request.method + '/api/v1' + path + str(expires) + request.data
        signature = hmac.new(self.apiSecret, msg,
                             digestmod=hashlib.sha256).hexdigest()

        # 添加表头
        headers = {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Accept': 'application/json',
            'api-key': self.apiKey,
            'api-expires': str(expires),
            'api-signature': signature
        }

        request.headers = headers
        return request

    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, sessionCount, testnet):
        """连接服务器"""
        self.apiKey = apiKey
        self.apiSecret = apiSecret

        self.loginTime = int(datetime.now().strftime('%y%m%d%H%M%S')) * self.orderId

        if not testnet:
            self.init(REST_HOST)
        else:
            self.init(TESTNET_REST_HOST)

        self.start(sessionCount)

        self.writeLog(u'REST API启动成功')

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):  # type: (VtOrderReq)->str
        """"""
        self.orderId += 1
        orderId = str(self.loginTime + self.orderId)
        vtOrderID = '.'.join([self.gatewayName, orderId])

        data = {
            'symbol': orderReq.symbol,
            'side': directionMap[orderReq.direction],
            'ordType': priceTypeMap[orderReq.priceType],
            'price': orderReq.price,
            'orderQty': orderReq.volume,
            'clOrdID': str(orderId)
        }

        # 只有限价单才有price字段
        if orderReq.priceType == PRICETYPE_LIMITPRICE:
            data['price'] = orderReq.price

        vtOrder = VtOrderData.createFromGateway(
            self.gateway,
            orderId=orderId,
            symbol=orderReq.symbol,
            exchange=self.gateway.exchange,
            price=orderReq.price,
            volume=orderReq.volume,
            direction=orderReq.direction,
            offset=orderReq.offset,
        )

        self.addRequest('POST', '/order', callback=self.onSendOrder, data=data, extra=vtOrder,
                        onFailed=self.onSendOrderFailed,
                        onError=self.onSendOrderError,
                        )
        return vtOrderID

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """"""
        orderID = cancelOrderReq.orderID

        if orderID.isdigit():
            params = {'clOrdID': orderID}
        else:
            params = {'orderID': orderID}

        self.addRequest('DELETE', '/order', callback=self.onCancelOrder, params=params,
                        onError=self.onCancelOrderError,
                        )

    #----------------------------------------------------------------------
    def onSendOrderFailed(self, _, request):
        """
        下单失败回调：服务器明确告知下单失败
        """
        vtOrder = request.extra  # type: VtOrderData
        vtOrder.status = constant.STATUS_REJECTED
        self.gateway.onOrder(vtOrder)
        pass

    #----------------------------------------------------------------------
    def onSendOrderError(self, exceptionType, exceptionValue, tb, request):
        """
        下单失败回调：连接错误
        """
        vtOrder = request.extra  # type: VtOrderData
        vtOrder.status = constant.STATUS_REJECTED
        self.gateway.onOrder(vtOrder)

        # 意料之中的错误只有ConnectionError，若还有其他错误，最好还是记录一下，用原来的onError记录即可
        if not issubclass(exceptionType, ConnectionError):
            self.onError(exceptionType, exceptionValue, tb, request)

    #----------------------------------------------------------------------
    def onSendOrder(self, data, request):
        """"""
        pass

    #----------------------------------------------------------------------
    def onCancelOrderError(self, exceptionType, exceptionValue, tb, request):
        """
        撤单失败回调：连接错误
        """
        # 意料之中的错误只有ConnectionError，若还有其他错误，最好还是记录一下，用原来的onError记录即可
        if not issubclass(exceptionType, ConnectionError):
            self.onError(exceptionType, exceptionValue, tb, request)

    #----------------------------------------------------------------------
    def onCancelOrder(self, data, request):
        """"""
        pass

    #----------------------------------------------------------------------
    def onFailed(self, httpStatusCode, request):  # type:(int, Request)->None
        """
        请求失败处理函数（HttpStatusCode!=2xx）.
        默认行为是打印到stderr
        """
        e = VtErrorData()
        e.gatewayName = self.gatewayName
        e.errorID = httpStatusCode
        e.errorMsg = request.response.text
        self.gateway.onError(e)
        print(request.response.text)

    #----------------------------------------------------------------------
    def onError(self, exceptionType, exceptionValue, tb, request):
        """
        Python内部错误处理：默认行为是仍给excepthook
        """
        e = VtErrorData()
        e.gatewayName = self.gatewayName
        e.errorID = exceptionType
        e.errorMsg = exceptionValue
        self.gateway.onError(e)

        sys.stderr.write(self.exceptionDetail(exceptionType, exceptionValue, tb, request))


########################################################################
class BitmexWebsocketApi(WebsocketClient):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(BitmexWebsocketApi, self).__init__()

        self.gateway = gateway
        self.gatewayName = gateway.gatewayName

        self.apiKey = ''
        self.apiSecret = ''

        self.callbackDict = {
            'trade': self.onTick,
            'orderBook10': self.onDepth,
            'execution': self.onTrade,
            'order': self.onOrder,
            'position': self.onPosition,
            'margin': self.onAccount,
            'instrument': self.onContract
        }

        self.tickDict = {}
        self.accountDict = {}
        self.orderDict = {}
        self.tradeSet = set()

    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, symbols, testnet):
        """"""
        self.apiKey = apiKey
        self.apiSecret = apiSecret

        if not testnet:
            self.init(WEBSOCKET_HOST)
        else:
            self.init(TESTNET_WEBSOCKET_HOST)

        self.start()

        for symbol in symbols:
            self.subscribeMarketData(symbol)

    #----------------------------------------------------------------------
    def subscribeMarketData(self, symbol):
        """订阅行情"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
        tick.symbol = symbol
        tick.exchange = EXCHANGE_BITMEX
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
        self.tickDict[symbol] = tick

    #----------------------------------------------------------------------
    def onConnected(self):
        """连接回调"""
        self.writeLog(u'Websocket API连接成功')
        self.authenticate()

    #----------------------------------------------------------------------
    def onDisconnected(self):
        """连接回调"""
        self.writeLog(u'Websocket API连接断开')
        self.authenticate()

    #----------------------------------------------------------------------
    def onPacket(self, packet):
        """数据回调"""
        if 'error' in packet:
            self.writeLog(u'Websocket API报错：%s' % packet['error'])

            if 'not valid' in packet['error']:
                self.active = False

        elif 'request' in packet:
            req = packet['request']
            success = packet['success']

            if success:
                if req['op'] == 'authKey':
                    self.writeLog(u'Websocket API验证授权成功')
                    self.subscribe()

        elif 'table' in packet:
            name = packet['table']
            callback = self.callbackDict[name]

            if isinstance(packet['data'], list):
                for d in packet['data']:
                    callback(d)
            else:
                callback(packet['data'])

    #----------------------------------------------------------------------
    def onError(self, exceptionType, exceptionValue, tb):
        """Python错误回调"""
        e = VtErrorData()
        e.gatewayName = self.gatewayName
        e.errorID = exceptionType
        e.errorMsg = exceptionValue
        self.gateway.onError(e)

        sys.stderr.write(self.exceptionDetail(exceptionType, exceptionValue, tb))

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    #----------------------------------------------------------------------
    def authenticate(self):
        """"""
        expires = int(time.time())
        method = 'GET'
        path = '/realtime'
        msg = method + path + str(expires)
        signature = hmac.new(self.apiSecret, msg, digestmod=hashlib.sha256).hexdigest()

        req = {
            'op': 'authKey',
            'args': [self.apiKey, expires, signature]
        }
        self.sendPacket(req)

    #----------------------------------------------------------------------
    def subscribe(self):
        """"""
        req = {
            'op': 'subscribe',
            'args': ['instrument', 'trade', 'orderBook10', 'execution', 'order', 'position', 'margin']
        }
        self.sendPacket(req)

    #----------------------------------------------------------------------
    def onTick(self, d):
        """"""
        symbol = d['symbol']

        tick = self.tickDict.get(symbol, None)
        if not tick:
            return

        tick.lastPrice = d['price']

        date, time = str(d['timestamp']).split('T')
        tick.date = date.replace('-', '')
        tick.time = time.replace('Z', '')

        tick = copy(tick)
        self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def onDepth(self, d):
        """"""
        symbol = d['symbol']
        tick = self.tickDict.get(symbol, None)
        if not tick:
            return

        for n, buf in enumerate(d['bids'][:5]):
            price, volume = buf
            tick.__setattr__('bidPrice%s' % (n + 1), price)
            tick.__setattr__('bidVolume%s' % (n + 1), volume)

        for n, buf in enumerate(d['asks'][:5]):
            price, volume = buf
            tick.__setattr__('askPrice%s' % (n + 1), price)
            tick.__setattr__('askVolume%s' % (n + 1), volume)

        date, time = str(d['timestamp']).split('T')
        tick.date = date.replace('-', '')
        tick.time = time.replace('Z', '')

        tick = copy(tick)
        self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def onTrade(self, d):
        """"""
        if not d['lastQty']:
            return

        tradeID = d['execID']
        if tradeID in self.tradeSet:
            return
        self.tradeSet.add(tradeID)

        trade = VtTradeData()
        trade.gatewayName = self.gatewayName

        trade.symbol = d['symbol']
        trade.exchange = EXCHANGE_BITMEX
        trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
        if d['clOrdID']:
            orderID = d['clOrdID']
        else:
            orderID = d['orderID']
        trade.orderID = orderID
        trade.vtOrderID = '.'.join([trade.gatewayName, trade.orderID])

        trade.tradeID = tradeID
        trade.vtTradeID = '.'.join([trade.gatewayName, trade.tradeID])

        # bug check:
        if d['side'] not in directionMapReverse:
            logging.debug('trade wthout side : %s', d)
            return

        trade.direction = directionMapReverse[d['side']]
        trade.price = d['lastPx']
        trade.volume = d['lastQty']
        trade.tradeTime = d['timestamp'][0:10].replace('-', '')

        self.gateway.onTrade(trade)

    #----------------------------------------------------------------------
    def onOrder(self, d):
        """"""
        if 'ordStatus' not in d:
            return

        sysID = d['orderID']
        if sysID in self.orderDict:
            order = self.orderDict[sysID]
        else:
            order = VtOrderData()
            order.gatewayName = self.gatewayName

            order.symbol = d['symbol']
            order.exchange = EXCHANGE_BITMEX
            order.vtSymbol = '.'.join([order.symbol, order.exchange])

            if d['clOrdID']:
                orderID = d['clOrdID']
            else:
                orderID = sysID
            order.orderID = orderID
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])

            order.direction = directionMapReverse[d['side']]

            if d['price']:
                order.price = d['price']

            order.totalVolume = d['orderQty']
            order.orderTime = d['timestamp'][0:10].replace('-', '')

            self.orderDict[sysID] = order

        order.tradedVolume = d.get('cumQty', order.tradedVolume)
        order.status = statusMapReverse.get(d['ordStatus'], STATUS_UNKNOWN)

        self.gateway.onOrder(order)

    #----------------------------------------------------------------------
    def onPosition(self, d):
        """"""
        pos = VtPositionData()
        pos.gatewayName = self.gatewayName

        pos.symbol = d['symbol']
        pos.exchange = EXCHANGE_BITMEX
        pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])

        pos.direction = DIRECTION_NET
        pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
        pos.position = d['currentQty']
        pos.frozen = 0      # 期货没有冻结概念，会直接反向开仓

        self.gateway.onPosition(pos)

    #----------------------------------------------------------------------
    def onAccount(self, d):
        """"""
        accoundID = str(d['account'])

        if accoundID in self.accountDict:
            account = self.accountDict[accoundID]
        else:
            account = VtAccountData()
            account.gatewayName = self.gatewayName

            account.accountID = accoundID
            account.vtAccountID = '.'.join([account.gatewayName, account.accountID])

            self.accountDict[accoundID] = account

        account.balance = d.get('marginBalance', account.balance)
        account.available = d.get('availableMargin', account.available)
        account.closeProfit = d.get('realisedPnl', account.closeProfit)
        account.positionProfit = d.get('unrealisedPnl', account.positionProfit)

        self.gateway.onAccount(account)

    #----------------------------------------------------------------------
    def onContract(self, d):
        """"""
        if 'tickSize' not in d:
            return

        contract = VtContractData()
        contract.gatewayName = self.gatewayName

        contract.symbol = d['symbol']
        contract.exchange = EXCHANGE_BITMEX
        contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
        contract.name = contract.vtSymbol
        contract.productClass = PRODUCT_FUTURES
        contract.priceTick = d['tickSize']
        contract.size = d['lotSize']

        self.gateway.onContract(contract)


#----------------------------------------------------------------------
def printDict(d):
    """"""
    print('-' * 30)
    l = sorted(d.keys())
    for k in l:
        print(k, d[k])
