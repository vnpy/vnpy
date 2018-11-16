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
import base64
import zlib
from datetime import datetime, timedelta
from copy import copy
from math import pow
from urllib import urlencode

from requests import ConnectionError

from vnpy.api.rest import RestClient, Request
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath


REST_HOST = 'https://www.okex.com'
WEBSOCKET_HOST = 'wss://real.okex.com:10440/websocket/okexapi?compress=true'


# 委托状态类型映射
statusMapReverse = {}
statusMapReverse['0'] = STATUS_NOTTRADED
statusMapReverse['1'] = STATUS_PARTTRADED
statusMapReverse['2'] = STATUS_ALLTRADED
statusMapReverse['-1'] = STATUS_CANCELLED

# 方向和开平映射
typeMap = {}
typeMap[(DIRECTION_LONG, OFFSET_OPEN)] = '1'
typeMap[(DIRECTION_SHORT, OFFSET_OPEN)] = '2'
typeMap[(DIRECTION_LONG, OFFSET_CLOSE)] = '3'
typeMap[(DIRECTION_SHORT, OFFSET_CLOSE)] = '4'
typeMapReverse = {v: k for k, v in typeMap.items()}


########################################################################
class OkexfGateway(VtGateway):
    """OKEX期货接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName=''):
        """Constructor"""
        super(OkexfGateway, self).__init__(eventEngine, gatewayName)

        self.qryEnabled = False     # 是否要启动循环查询
        self.localRemoteDict = {}   # localID:remoteID
        self.orderDict = {}         # remoteID:order

        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)

        self.restApi = OkexfRestApi(self)
        self.wsApi = OkexfWebsocketApi(self)

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
            passphrase = str(setting['passphrase'])
            leverage = int(setting['leverage'])
            sessionCount = int(setting['sessionCount'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

        # 创建行情和交易接口对象
        self.restApi.connect(apiKey, apiSecret, passphrase, leverage, sessionCount)
        self.wsApi.connect(apiKey, apiSecret, passphrase)

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        self.wsApi.subscribe(subscribeReq)

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
            self.qryFunctionList = [self.queryInfo]

            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 4         # 查询触发点
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

    #----------------------------------------------------------------------
    def queryInfo(self):
        """"""
        self.restApi.queryAccount()
        self.restApi.queryPosition()


########################################################################
class OkexfRestApi(RestClient):
    """REST API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(OkexfRestApi, self).__init__()

        self.gateway = gateway                  # type: BitmexGateway # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.apiKey = ''
        self.apiSecret = ''
        self.passphrase = ''
        self.leverage = 0

        self.orderID = 1000000
        self.loginTime = 0

        self.contractDict = {}
        self.cancelDict = {}
        self.localRemoteDict = gateway.localRemoteDict
        self.orderDict = gateway.orderDict

    #----------------------------------------------------------------------
    def sign(self, request):
        """BitMEX的签名方案"""
        # 生成签名
        timestamp = str(time.time())
        request.data = json.dumps(request.data)

        if request.params:
            path = request.path + '?' + urlencode(request.params)
        else:
            path = request.path

        msg = timestamp + request.method + path + request.data
        signature = generateSignature(msg, self.apiSecret)

        # 添加表头
        request.headers = {
            'OK-ACCESS-KEY': self.apiKey,
            'OK-ACCESS-SIGN': signature,
            'OK-ACCESS-TIMESTAMP': timestamp,
            'OK-ACCESS-PASSPHRASE': self.passphrase,
            'Content-Type': 'application/json'
        }
        return request

    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, passphrase, leverage, sessionCount):
        """连接服务器"""
        self.apiKey = apiKey
        self.apiSecret = apiSecret
        self.passphrase = passphrase
        self.leverage = leverage
        self.loginTime = int(datetime.now().strftime('%y%m%d%H%M%S')) * self.orderID

        self.init(REST_HOST)
        self.start(sessionCount)
        self.writeLog(u'REST API启动成功')

        self.queryContract()

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
        self.orderID += 1
        orderID = str(self.loginTime + self.orderID)
        vtOrderID = '.'.join([self.gatewayName, orderID])

        type_ = typeMap[(orderReq.direction, orderReq.offset)]
        data = {
            'client_oid': orderID,
            'instrument_id': orderReq.symbol,
            'type': type_,
            'price': orderReq.price,
            'size': orderReq.volume,
            'leverage': self.leverage,
        }

        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = orderReq.symbol
        order.exchange = 'OKEX'
        order.vtSymbol = '.'.join([order.symbol, order.exchange])
        order.orderID = orderID
        order.vtOrderID = vtOrderID
        order.direction = orderReq.direction
        order.offset = orderReq.offset
        order.price = orderReq.price
        order.totalVolume = orderReq.volume

        self.addRequest('POST', '/api/futures/v3/order',
                        callback=self.onSendOrder,
                        data=data,
                        extra=order,
                        onFailed=self.onSendOrderFailed,
                        onError=self.onSendOrderError)
        return vtOrderID

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """"""
        symbol = cancelOrderReq.symbol
        orderID = cancelOrderReq.orderID
        remoteID = self.localRemoteDict.get(orderID, None)
        if not remoteID:
            self.cancelDict[orderID] = cancelOrderReq
            return

        req = {
            'instrument_id': symbol,
            'order_id': remoteID
        }
        path = '/api/futures/v3/cancel_order/%s/%s' % (symbol, remoteID)
        self.addRequest('POST', path,
                        callback=self.onCancelOrder,
                        data=req)

    #----------------------------------------------------------------------
    def queryContract(self):
        """"""
        self.addRequest('GET', '/api/futures/v3/instruments',
                        callback=self.onQueryContract)

    #----------------------------------------------------------------------
    def queryAccount(self):
        """"""
        self.addRequest('GET', '/api/futures/v3/accounts',
                        callback=self.onQueryAccount)

    #----------------------------------------------------------------------
    def queryPosition(self):
        """"""
        self.addRequest('GET', '/api/futures/v3/position',
                        callback=self.onQueryPosition)

    #----------------------------------------------------------------------
    def queryOrder(self):
        """"""
        for symbol in self.contractDict.keys():
            # 未成交
            req = {
                'instrument_id': symbol,
                'status': 0
            }
            path = '/api/futures/v3/orders/%s' % symbol
            self.addRequest('GET', path, params=req,
                            callback=self.onQueryOrder)

            # 部分成交
            req2 = {
                'instrument_id': symbol,
                'status': 1
            }
            self.addRequest('GET', path, params=req2,
                            callback=self.onQueryOrder)

    #----------------------------------------------------------------------
    def onQueryContract(self, data, request):
        """"""
        for d in data:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName

            contract.symbol = d['instrument_id']
            contract.exchange = 'OKEX'
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])

            contract.name = contract.symbol
            contract.productClass = PRODUCT_FUTURES
            contract.priceTick = float(d['tick_size'])
            contract.size = int(d['trade_increment'])

            self.contractDict[contract.symbol] = contract
            self.gateway.onContract(contract)

        self.writeLog(u'合约信息查询成功')

        self.queryOrder()
        self.queryAccount()
        self.queryPosition()

    #----------------------------------------------------------------------
    def onQueryAccount(self, data, request):
        """"""
        for currency, d in data['info'].items():
            account = VtAccountData()
            account.gatewayName = self.gatewayName

            account.accountID = currency
            account.vtAccountID = '.'.join([account.gatewayName, account.accountID])

            account.balance = float(d['equity'])
            account.available = float(d['total_avail_balance'])
            #account.margin = float(d['margin'])
            #account.positionProfit = float(d['unrealized_pnl'])
            #account.closeProfit = float(d['realized_pnl'])

            self.gateway.onAccount(account)

    #----------------------------------------------------------------------
    def onQueryPosition(self, data, request):
        """"""
        for d in data['holding'][0]:
            longPosition = VtPositionData()
            longPosition.gatewayName = self.gatewayName
            longPosition.symbol = d['instrument_id']
            longPosition.exchange = 'OKEX'
            longPosition.vtSymbol = '.'.join([longPosition.symbol, longPosition.exchange])
            longPosition.direction = DIRECTION_LONG
            longPosition.vtPositionName = '.'.join([longPosition.vtSymbol, longPosition.direction])
            longPosition.position = int(d['long_qty'])
            longPosition.frozen = longPosition.position - int(d['long_avail_qty'])
            longPosition.price = float(d['long_avg_cost'])

            shortPosition = copy(longPosition)
            shortPosition.direction = DIRECTION_SHORT
            shortPosition.vtPositionName = '.'.join([shortPosition.vtSymbol, shortPosition.direction])
            shortPosition.position = int(d['short_qty'])
            shortPosition.frozen = shortPosition.position - int(d['short_avail_qty'])
            shortPosition.price = float(d['short_avg_cost'])

            self.gateway.onPosition(longPosition)
            self.gateway.onPosition(shortPosition)

    #----------------------------------------------------------------------
    def onQueryOrder(self, data, request):
        """"""
        for d in data['order_info']:
            order = VtOrderData()
            order.gatewayName = self.gatewayName

            order.symbol = d['instrument_id']
            order.exchange = 'OKEX'
            order.vtSymbol = '.'.join([order.symbol, order.exchange])

            self.orderID += 1
            order.orderID = str(self.loginTime + self.orderID)
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            self.localRemoteDict[order.orderID] = d['order_id']

            order.price = float(d['price'])
            order.totalVolume = int(d['size'])
            order.tradedVolume = int(d['filled_qty'])
            order.status = statusMapReverse[d['status']]
            order.direction, order.offset = typeMapReverse[d['type']]

            dt = datetime.strptime(d['timestamp'], '%Y-%m-%dT%H:%M:%S.%fZ')
            order.orderTime = dt.strftime('%H:%M:%S')

            self.gateway.onOrder(order)
            self.orderDict[d['order_id']] = order

    #----------------------------------------------------------------------
    def onSendOrderFailed(self, data, request):
        """
        下单失败回调：服务器明确告知下单失败
        """
        order = request.extra
        order.status = STATUS_REJECTED
        self.gateway.onOrder(order)

    #----------------------------------------------------------------------
    def onSendOrderError(self, exceptionType, exceptionValue, tb, request):
        """
        下单失败回调：连接错误
        """
        order = request.extra
        order.status = STATUS_REJECTED
        self.gateway.onOrder(vtOrder)

    #----------------------------------------------------------------------
    def onSendOrder(self, data, request):
        """"""
        self.localRemoteDict[data['client_oid']] = data['order_id']
        self.orderDict[data['order_id']] = request.extra

        if data['client_oid'] in self.cancelDict:
            req = self.cancelDict.pop(data['client_oid'])
            self.cancelOrder(req)

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
class OkexfWebsocketApi(WebsocketClient):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(OkexfWebsocketApi, self).__init__()

        self.gateway = gateway
        self.gatewayName = gateway.gatewayName

        self.apiKey = ''
        self.apiSecret = ''
        self.passphrase = ''

        self.orderDict = gateway.orderDict
        self.localRemoteDict = gateway.localRemoteDict

        self.tradeID = 0
        self.callbackDict = {}
        self.channelSymbolDict = {}
        self.tickDict = {}

    #----------------------------------------------------------------------
    def unpackData(self, data):
        """重载"""
        return json.loads(zlib.decompress(data, -zlib.MAX_WBITS))

    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, passphrase):
        """"""
        self.apiKey = apiKey
        self.apiSecret = apiSecret
        self.passphrase = passphrase

        self.init(WEBSOCKET_HOST)
        self.start()

    #----------------------------------------------------------------------
    def onConnected(self):
        """连接回调"""
        self.writeLog(u'Websocket API连接成功')
        self.login()

    #----------------------------------------------------------------------
    def onDisconnected(self):
        """连接回调"""
        self.writeLog(u'Websocket API连接断开')

    #----------------------------------------------------------------------
    def onPacket(self, packet):
        """数据回调"""
        d = packet[0]

        channel = d['channel']
        callback = self.callbackDict.get(channel, None)
        if callback:
            callback(d)

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
    def login(self):
        """"""
        timestamp = str(time.time())

        msg = timestamp + 'GET' + '/users/self/verify'
        signature = generateSignature(msg, self.apiSecret)

        req = {
            "event": "login",
            "parameters": {
                "api_key": self.apiKey,
                "timestamp": timestamp,
                "passphrase": self.passphrase,
                "sign": signature
            }
        }
        self.sendPacket(req)

        self.callbackDict['login'] = self.onLogin

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """"""
        # V3到V1的代码转换
        currency, contractType = convertSymbol(subscribeReq.symbol)

        # 订阅成交
        channel1 = 'ok_sub_futureusd_%s_ticker_%s' % (currency, contractType)
        self.callbackDict[channel1] = self.onTick
        self.channelSymbolDict[channel1] = subscribeReq.symbol

        req1 = {
            'event': 'addChannel',
            'channel': channel1
        }
        self.sendPacket(req1)

        # 订阅深度
        channel2 = 'ok_sub_futureusd_%s_depth_%s_5' % (currency, contractType)
        self.callbackDict[channel2] = self.onDepth
        self.channelSymbolDict[channel2] = subscribeReq.symbol

        req2 = {
            'event': 'addChannel',
            'channel': channel2
        }
        self.sendPacket(req2)

        # 创建Tick对象
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
        tick.symbol = subscribeReq.symbol
        tick.exchange = 'OKEX'
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
        self.tickDict[tick.symbol] = tick

    #----------------------------------------------------------------------
    def onLogin(self, d):
        """"""
        data = d['data']
        if not data['result']:
            return

        # 订阅交易相关推送
        self.sendPacket({'event': 'addChannel', 'channel': 'ok_sub_futureusd_trades'})
        self.sendPacket({'event': 'addChannel', 'channel': 'ok_sub_futureusd_userinfo'})
        self.sendPacket({'event': 'addChannel', 'channel': 'ok_sub_futureusd_positions'})

        self.callbackDict['ok_sub_futureusd_trades'] = self.onTrade
        self.callbackDict['ok_sub_futureusd_userinfo'] = self.onAccount
        self.callbackDict['ok_sub_futureusd_positions'] = self.onPosition

    #----------------------------------------------------------------------
    def onTick(self, d):
        """"""
        data = d['data']
        channel = d['channel']

        symbol = self.channelSymbolDict[channel]
        tick = self.tickDict[symbol]

        tick.lastPrice = float(data['last'])
        tick.highPrice = float(data['high'])
        tick.lowPrice = float(data['low'])
        tick.volume = float(data['vol'])

        tick = copy(tick)
        self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def onDepth(self, d):
        """"""
        data = d['data']
        channel = d['channel']

        symbol = self.channelSymbolDict[channel]
        tick = self.tickDict[symbol]

        for n, buf in enumerate(data['bids']):
            price, volume = buf[:2]
            tick.__setattr__('bidPrice%s' % (n + 1), float(price))
            tick.__setattr__('bidVolume%s' % (n + 1), int(volume))

        for n, buf in enumerate(data['asks']):
            price, volume = buf[:2]
            tick.__setattr__('askPrice%s' % (n + 1), float(price))
            tick.__setattr__('askVolume%s' % (n + 1), int(volume))

        dt = datetime.fromtimestamp(data['timestamp'] / 1000)
        tick.date = dt.strftime('%Y%m%d')
        tick.time = dt.strftime('%H:%M:%S')

        tick = copy(tick)
        self.gateway.onTick(tick)

    #----------------------------------------------------------------------
    def onTrade(self, d):
        """"""
        data = d['data']
        order = self.orderDict.get(str(data['orderid']), None)
        if not order:
            currency = data['contract_name'][:3]
            expiry = str(data['contract_id'])[2:8]

            order = VtOrderData()
            order.gatewayName = self.gatewayName
            order.symbol = '%s-USD-%s' % (currency, expiry)
            order.exchange = 'OKEX'
            order.vtSymbol = '.'.join([order.symbol, order.exchange])

            restApi = self.gateway.restApi
            restApi.orderID += 1
            order.orderID = str(restApi.loginTime + restApi.orderID)
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            order.orderTime = data['create_date_str'].split(' ')[-1]
            order.price = data['price']
            order.totalVolume = int(data['amount'])
            order.direction, order.offset = typeMapReverse[str(data['type'])]

            self.localRemoteDict[order.orderID] = str(data['orderid'])
            self.orderDict[str(data['orderid'])] = order

        volumeChange = int(data['deal_amount']) - order.tradedVolume

        order.status = statusMapReverse[str(data['status'])]
        order.tradedVolume = int(data['deal_amount'])
        self.gateway.onOrder(copy(order))

        if volumeChange:
            self.tradeID += 1

            trade = VtTradeData()
            trade.gatewayName = order.gatewayName
            trade.symbol = order.symbol
            trade.exchange = order.exchange
            trade.vtSymbol = order.vtSymbol

            trade.orderID = order.orderID
            trade.vtOrderID = order.vtOrderID
            trade.tradeID = str(self.tradeID)
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])

            trade.direction = order.direction
            trade.offset = order.offset
            trade.volume = volumeChange
            trade.price = float(data['price_avg'])
            trade.tradeTime = datetime.now().strftime('%H:%M:%S')
            self.gateway.onTrade(trade)

    #----------------------------------------------------------------------
    def onAccount(self, d):
        """"""
        data = d['data']
        currency = data['symbol'].split('_')[0]

        account = VtAccountData()
        account.gatewayName = self.gatewayName
        account.accountID = currency
        account.vtAccountID = '.'.join([self.gatewayName, account.accountID])

        account.balance = data['balance']
        account.available = data['balance'] - data['keep_deposit']

        self.gateway.onAccount(account)

    #----------------------------------------------------------------------
    def onPosition(self, d):
        """"""
        data = d['data']

        for buf in data['positions']:
            position = VtPositionData()
            position.gatewayName = self.gatewayName

            currency = buf['contract_name'][:3]
            expiry = str(buf['contract_id'])[2:8]
            position.symbol = '%s-USD-%s' % (currency, expiry)
            position.exchange = 'OKEX'
            position.vtSymbol = '.'.join([position.symbol, position.exchange])
            position.position = int(buf['hold_amount'])
            position.frozen = int(buf['hold_amount']) - int(buf['eveningup'])
            position.price = float(buf['avgprice'])

            if buf['position'] == 1:
                position.direction = DIRECTION_LONG
            else:
                position.direction = DIRECTION_SHORT
            position.vtPositionName = '.'.join([position.vtSymbol, position.direction])
            self.gateway.onPosition(position)


#----------------------------------------------------------------------
def generateSignature(msg, apiSecret):
    """签名V3"""
    return base64.b64encode(hmac.new(apiSecret, msg.encode(), hashlib.sha256).digest())


symbolMap = {}      # 代码映射v3 symbol:(v1 currency, contractType)

#----------------------------------------------------------------------


def convertSymbol(symbol3):
    """转换代码"""
    if symbol3 in symbolMap:
        return symbolMap[symbol3]

    # 拆分代码
    currency, usd, expire = symbol3.split('-')

    # 计算到期时间
    expireDt = datetime.strptime(expire, '%y%m%d')
    now = datetime.now()
    delta = expireDt - now

    # 根据时间转换
    if delta <= timedelta(days=7):
        contractType = 'this_week'
    elif delta <= timedelta(days=14):
        contractType = 'next_week'
    else:
        contractType = 'quarter'

    result = (currency.lower(), contractType)
    symbolMap[symbol3] = result
    return result


#----------------------------------------------------------------------
def printDict(d):
    """"""
    print('-' * 30)
    l = sorted(d.keys())
    for k in l:
        print(k, d[k])
