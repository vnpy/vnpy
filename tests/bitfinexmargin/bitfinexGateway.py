# encoding: UTF-8
'''
vnpy.api.bitfinex的gateway接入 对其中进行修改
'''
from __future__ import print_function
import os
import json
import hashlib
import hmac
import time
from datetime import datetime, timedelta
from copy import copy
from math import pow
import requests
import pandas as pd

from vnpy.api.bitfinex import BitfinexApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtConstant import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath
from vnpy.trader.app.ctaStrategy.ctaBase import EVENT_CTA_LOG
from vnpy.trader.vtObject import *
from vnpy.trader.app.ctaStrategy.ctaBase import *


#使用ccxt 对交易细节进行控制

from time import sleep
from datetime import datetime, timedelta
import ccxt
import numpy as np
from pandas import Series, DataFrame
from tabulate import tabulate
tabulate.PRESERVE_WHITESPACE = True
pd.set_option('expand_frame_repr', False)  



statusMapReverse = {}
statusMapReverse['ACTIVE'] = STATUS_NOTTRADED                      # pending 订单活跃状态中
statusMapReverse['PARTIALLYFILLED'] = STATUS_PARTTRADED            # 'partial filled' 部分交易
statusMapReverse['EXECUTED'] = STATUS_ALLTRADED                    # 'filled'   交易完成
statusMapReverse['CANCELED'] = STATUS_CANCELLED                    # 'cancelled'  已经全部取消

##价格类型映射
priceTypeMap = {}

priceTypeMap[PRICETYPE_LIMITPRICE] = 'LIMIT'
priceTypeMap[PRICETYPE_MARKETPRICE] = 'MARKET'
priceTypeMap[PRICETYPE_FOK] = 'FILL-OR-KILL'



# 使用ccxt 对交易细节进行控制参数
bitfinex = ccxt.bitfinex2()


# import pdb;pdb.set_trace()

############################################################################################
class BitfinexGateay(VtGateway):
    """Bitfinex接口"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName=''):
        """Constructor"""

        super(BitfinexGateay, self).__init__(eventEngine, gatewayName)
        self.api = GatewayApi(self)

        self.qryEnabled = False                                                    # 是否要启动循环查询

        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)

        self.connected = False
        self.count = 0

    # ----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 如果 accessKey accessSec pairs 在初始化的时候已经设置了，则不用配置文件里的了
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
            secretKey = str(setting['secretKey'])
            symbols = setting['symbols']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

        if self.connected:
            return

        # 创建行情和交易接口对象
        self.api.connect(apiKey, secretKey, symbols)
        self.connected = True

        #----------added---------------------------------
        setQryEnabled = setting.get('setQryEnabled', None)
        self.setQryEnabled(setQryEnabled)

        setQryFreq = setting.get('setQryFreq', 60)
        self.initQuery(setQryFreq)


    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        pass

    # ----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.api.sendOrder(orderReq)

    # ----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.api.cancelOrder(cancelOrderReq)

    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.api.close()

    # -------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.api.onPosition()
    # ----------------------------------------------------------------------
    def qryAccount(self):
        """"""
        self.api.onWallet()

    #----------------------------------------------------------------------
    def initQuery(self, freq = 60):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.queryInfo]

            self.qryCount = 0                           # 查询触发倒计时
            self.qryTrigger = freq                      # 查询触发点
            self.qryNextFunction = 0                    # 上次运行的查询函数索引

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

    # ----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)

    # ----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled

    #----------------------------------------------------------------------
    def queryInfo(self):
        """"""
        self.api.queryAccount()
        self.api.queryPosition()
        # self.api.queryOrder()

    # ----------------------------------------------------------------------
    # 启动初始化程序接口，在策略在持仓期间停止重启时候进行持仓信息的查询，这里使用restful 接口进行查
    def initPosition(self,vtSymbol):
        # 接下来是检验下数据看是不是进行了仓位的初始化
        print("策略启动 仓位initposition初始化")
        self.api.queryPosition()


    def qryAllOrders(self,vtSymbol,order_id,status=None):
        pass


    def loadHistoryBar(self, vtSymbol, type_, size=None, since=None):
        symbol = vtSymbol.split(':')[0]


        typeMap = {}
        typeMap['1min'] = '1m'
        typeMap['5min'] = '5m'
        typeMap['15min'] = '15m'
        typeMap['30min'] = '30m'
        typeMap['60min'] = '1h'
        typeMap['360min'] = '6h'

        url = f'https://api.bitfinex.com/v2/candles/trade:{typeMap[type_]}:t{symbol}/hist'

        params = {}
        if size:
            params['limit'] = size
        if since:
            params['start'] = since

        r = requests.get(url, headers={
            'Content-Type': 'application/x-www-form-urlencoded',
            'Accept': 'application/json'
        }, params=params, timeout=10)

        df = pd.DataFrame(r.json(), columns=["MTS", "open", "close", "high", "low", "volume"])

        df["datetime"] = df["MTS"].map(lambda x: datetime.fromtimestamp(x / 1000))
        df['volume'] = df['volume'].map(lambda x: float(x))
        df['open'] = df['open'].map(lambda x: float(x))
        df['high'] = df['high'].map(lambda x: float(x))
        df['low'] = df['low'].map(lambda x: float(x))
        df['close'] = df['close'].map(lambda x: float(x))
        pm = df.sort_values(by="datetime", ascending=True)                # 对时间以及数据进行转换
        print("pm",pm)
        return pm


    # 这里是下载kindle 的数据主要是在实盘之中进行使用的
    def loadKindleBar(self, vtSymbol, type_, size=None, since=None):
        symbol = vtSymbol.split(':')[0]

        typeMap = {}
        typeMap['1min'] = '1m'
        typeMap['5min'] = '5m'
        typeMap['15min'] = '15m'
        typeMap['30min'] = '30m'
        typeMap['60min'] = '1h'
        typeMap['360min'] = '6h'

        url = f'https://api.bitfinex.com/v2/candles/trade:{typeMap[type_]}:t{symbol}/hist'

        params = {}
        if size:
            params['limit'] = size
        if since:
            params['start'] = since

        r = requests.get(url, headers={
            'Content-Type': 'application/x-www-form-urlencoded',
            'Accept': 'application/json'
        }, params=params, timeout=10)

        df = pd.DataFrame(r.json(), columns=["MTS", "open", "close", "high", "low", "volume"])

        df["datetime"] = df["MTS"].map(lambda x: datetime.fromtimestamp(x / 1000))
        df['volume'] = df['volume'].map(lambda x: float(x))
        df['open'] = df['open'].map(lambda x: float(x))
        df['high'] = df['high'].map(lambda x: float(x))
        df['low'] = df['low'].map(lambda x: float(x))
        df['close'] = df['close'].map(lambda x: float(x))
        pm = df.sort_values(by="datetime", ascending=True)                # 对时间以及数据进行转换
        # print("###############################pm##############################################")
        # print(pm)
        return pm



########################################################################
class GatewayApi(BitfinexApi):
    """API实现"""

    # ----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(GatewayApi, self).__init__()

        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        self.symbols = []


        # 根据其中的api 接口这里传入的是utc 标准时间格式数组
        self.orderId = 1
        self.date = int(datetime.now().timestamp()) * self.orderId

        self.currencys = []
        self.tickDict = {}
        self.bidDict = {}
        self.askDict = {}
        self.orderLocalDict = {}                                   # 维护的本地订单编号字典
        self.channelDict = {}                                      # ChannelID : (Channel, Symbol)

        self.accountDict = {}                                      # 在定义account 账号时候使用

        # 因为在bitfinex上没有order 的开平的属性，但是可以记录pos 的多、空、none 属性辅助判定
        # 首先获得positon 的direction，然后根据order 交易的正负值去进行定义
        self.direction = DIRECTION_NET                            # 默认方向为空方向，在初始化时候ps 时候，定义为none

    # ----------------------------------------------------------------------
    def connect(self, apiKey, secretKey, symbols):
        """连接服务器"""
        self.apiKey = apiKey
        self.secretKey = secretKey
        self.symbols = symbols

        self.start()
        self.writeLog(u'交易API启动成功')

    # ----------------------------------------------------------------------
    def onConnect(self):
        """"""
        for symbol in self.symbols:
            self.subscribe(symbol, 'ticker')
            self.subscribe(symbol, 'book')
        self.writeLog(u'行情推送订阅成功')

        # 只获取数据，不交易
        self.authenticate()
        self.writeLog(u'认证成功，交易推送订阅成功')

        self.sendRestReq('/symbols_details', self.onSymbolDetails,post=False)

    # ----------------------------------------------------------------------
    def subscribe(self, symbol, channel):
        """"""
        if not symbol.startswith("t"):
            symbol = "t" + symbol

        req = {
            'event': 'subscribe',
            'channel': channel,
            'symbol': symbol
        }
        self.sendReq(req)

    # ----------------------------------------------------------------------
    def authenticate(self):
        """"""
        nonce = int(time.time() * 1000000)
        authPayload = 'AUTH' + str(nonce)
        signature = hmac.new(
            self.secretKey.encode(),
            msg=authPayload.encode(),
            digestmod=hashlib.sha384
        ).hexdigest()

        req = {
            'apiKey': self.apiKey,
            'event': 'auth',
            'authPayload': authPayload,
            'authNonce': nonce,
            'authSig': signature
        }

        self.sendReq(req)

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    # ----------------------------------------------------------------------
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(s / 1000.0)
        date = dt.strftime('%Y-%m-%d')
        time = dt.strftime("%H:%M:%S.%f")
        return date, time

    def sendOrder(self, orderReq):

        amount = 0                                         # 在引入amount 之前定义amount变量，防止后边变量引入报错
        self.orderId += 1
        orderId = self.date + self.orderId
        vtOrderID = ':'.join([self.gatewayName, str(orderId)])

        # 注意对amount 的定义，因为监听传过来有四种组合
        if orderReq.direction == DIRECTION_LONG and orderReq.offset == OFFSET_OPEN:          # 买开  buy
            amount = orderReq.volume
        elif orderReq.direction == DIRECTION_SHORT and orderReq.offset == OFFSET_CLOSE:      # 卖平  sell
            amount = -orderReq.volume
        elif orderReq.direction == DIRECTION_SHORT and orderReq.offset == OFFSET_OPEN:       # 卖开   short
            amount = -orderReq.volume
        elif orderReq.direction == DIRECTION_LONG and orderReq.offset == OFFSET_CLOSE:       # 买平   cover
            amount = orderReq.volume

        oSymbol = orderReq.symbol
        if not oSymbol.startswith("t"):
            oSymbol = "t" + oSymbol

        o = {
            'cid': orderId,                       # Should be unique in the day (UTC) (not enforced)  int45
            'type': priceTypeMap[orderReq.priceType],
            'symbol': oSymbol,
            'amount': str(amount),
            'price': str(orderReq.price)
        }

        req = [0, 'on', None, o]
        self.sendReq(req)
        return vtOrderID

    # ----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """"""
        orderId = int(cancelOrderReq.orderID)
        date = cancelOrderReq.sessionID

        req = [
            0,
            'oc',
            None,
            {
                'cid': orderId,
                'cid_date': date,
            }
        ]

        self.sendReq(req)

    # ----------------------------------------------------------------------
    def calc(self):
        """"""
        l = []
        for currency in self.currencys:
            l.append(['wallet_exchange_' + currency])

        req = [0, 'calc', None, l]
        self.sendReq(req)

    # ----------------------------------------------------------------------
    def onData(self, data):
        """"""

        if isinstance(data, dict):
            self.onResponse(data)
        else:
            self.onUpdate(data)

    # ----------------------------------------------------------------------
    def printData(self, data):


        print(data)
        self.writeLog(u'认证成功，交易推送订阅成功 %s'%(data))

    # ----------------------------------------------------------------------
    def onResponse(self, data):
        """"""
        if 'event' not in data:
            return

        # 如果有错误的返回信息，要打印出来
        print("[onResponse]data:" + json.dumps(data))

        if data['event'] == 'subscribed':
            symbol = str(data['symbol'].replace('t', ''))
            self.channelDict[data['chanId']] = (data['channel'], symbol)

    # ----------------------------------------------------------------------
    def onUpdate(self, data):
        """"""
        if data[1] == u'hb':
            return

        channelID = data[0]

        if not channelID:
            self.onTradeUpdate(data)
        else:
            self.onDataUpdate(data)

    # ----------------------------------------------------------------------
    def onDataUpdate(self, data):
        """"""
        channelID = data[0]
        channel, symbol = self.channelDict[channelID]
        symbol = str(symbol.replace('t', ''))

        # 获取Tick对象
        if symbol in self.tickDict:
            tick = self.tickDict[symbol]
        else:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.symbol = symbol
            tick.exchange = EXCHANGE_BITFINEX
            tick.vtSymbol = ':'.join([tick.symbol, tick.exchange])

            self.tickDict[symbol] = tick

        l = data[1]

        # 常规行情更新
        if channel == 'ticker':
            tick.volume = float(l[-3])
            tick.highPrice = float(l[-2])
            tick.lowPrice = float(l[-1])
            tick.lastPrice = float(l[-4])
            tick.openPrice = float(tick.lastPrice - l[4])
        # 深度报价更新
        elif channel == 'book':
            bid = self.bidDict.setdefault(symbol, {})
            ask = self.askDict.setdefault(symbol, {})

            if len(l) > 3:
                for price, count, amount in l:
                    price = float(price)
                    count = int(count)
                    amount = float(amount)

                    if amount > 0:
                        bid[price] = amount
                    else:
                        ask[price] = -amount
            else:
                price, count, amount = l
                price = float(price)
                count = int(count)
                amount = float(amount)

                if not count:
                    if price in bid:
                        del bid[price]
                    elif price in ask:
                        del ask[price]
                else:
                    if amount > 0:
                        bid[price] = amount
                    else:
                        ask[price] = -amount

            # Bitfinex的深度数据更新是逐档推送变动情况，而非5档一起推
            # 因此会出现没有Bid或者Ask的情况，这里使用try...catch过滤
            # 只有买卖深度满足5档时才做推送
            try:
                # BID
                bidPriceList = bid.keys()
                bidPriceList = sorted(bidPriceList)

                tick.bidPrice1 = bidPriceList[0]
                tick.bidPrice2 = bidPriceList[1]
                tick.bidPrice3 = bidPriceList[2]
                tick.bidPrice4 = bidPriceList[3]
                tick.bidPrice5 = bidPriceList[4]

                tick.bidVolume1 = bid[tick.bidPrice1]
                tick.bidVolume2 = bid[tick.bidPrice2]
                tick.bidVolume3 = bid[tick.bidPrice3]
                tick.bidVolume4 = bid[tick.bidPrice4]
                tick.bidVolume5 = bid[tick.bidPrice5]

                # ASK
                askPriceList = ask.keys()
                askPriceList = sorted(askPriceList)

                tick.askPrice1 = askPriceList[0]
                tick.askPrice2 = askPriceList[1]
                tick.askPrice3 = askPriceList[2]
                tick.askPrice4 = askPriceList[3]
                tick.askPrice5 = askPriceList[4]

                tick.askVolume1 = ask[tick.askPrice1]
                tick.askVolume2 = ask[tick.askPrice2]
                tick.askVolume3 = ask[tick.askPrice3]
                tick.askVolume4 = ask[tick.askPrice4]
                tick.askVolume5 = ask[tick.askPrice5]
            except IndexError:
                return

        dt = datetime.now()
        tick.date = dt.strftime('%Y%m%d')
        tick.time = dt.strftime('%H:%M:%S.%f')
        tick.datetime = dt

        # 推送
        self.gateway.onTick(copy(tick))

    # ----------------------------------------------------------------------
    def onTradeUpdate(self, data):
        """"""
        name = data[1]
        info = data[2]

        # -----------------
        if name == 'os':                                             # orders活动委托，发单委托
            for l in info:
                self.onOrder(l)
            self.writeLog(u' os  快照 活动委托orders获取成功')
        elif name in ['on', 'ou', 'oc']:                             # orders活动委托，发单更新
            self.onOrder(info)
            self.writeLog(u'活动委托orders更新成功')

        elif name == 'te':                                          # trade
            self.onTrade(info)


        elif name == 'ps':                                          # position,这里是推送是关键是在ui 上显示pos 的基础
            for l in info:
                self.onPosition(l)
                self.writeLog(u'初始化持仓信息获取成功 快照')
        elif name in ['pn', 'pu', 'pc']:                            # position update这种形式是高级查询 包含利润，杠杆等信息

            self.onPosition(info)
            self.writeLog(u'持仓信息【更新】成功')                     # 注意这里获取的每一个资金账户之中的每一个币种，情况单独列举出来
        elif name == 'ws':                                          # wallets 账户信息包含 exchange  margin
            for l in info:
                self.onWallet(l)
            self.writeLog(u'账户资金获取成功 快照')
        elif name == 'wu':                                          # wallets 账户信息仅包含usd 信息   [0, 'wu', ['margin', 'USD', 213.06576039, 0, None]]
            self.onWallet(info)
            self.writeLog(u'账户资金 usd 【更新】获取成功')


    def onWallet(self, data):
        # 因为这里是使用margin 进行交易   第一次获得账户的快照信息
        if str(data[0]) == 'margin':
            """
             ['margin', 'USD', 213.11012559, 0, None]
             ['margin', 'ETC', 0.00079896, 0, None]
             ['margin', 'ETH', 0.00457842, 0, None]

            """
            account = VtAccountData()
            account.vtAccountID = self.gatewayName
            account.gatewayName = self.gatewayName
            account.accountID = str(data[1])                                       # 交易的币种
            account.vtAccountID = ':'.join([account.gatewayName, account.accountID])
            account.balance = float(data[2])                                       # 现有的数量
            if data[-1]:
                account.available = float(data[-1])

            self.gateway.onAccount(account)


    def onPosition(self, data):

        pos = VtPositionData()

        Symbol = data[0].split('t')[-1]
        pos.symbol = Symbol
        pos.gatewayName = self.gatewayName
        pos.exchange = EXCHANGE_BITFINEX
        pos.vtSymbol = ':'.join([pos.symbol, pos.exchange])                       # 合约在vt系统中的唯一代码，合约代码:交易所代码

        # 进行细力度的控制，仅有在仓位是 active 状态下才进行计算
        pos.position = abs(data[2])                  # 这里取持仓量是绝对值
        if data[2] > 0:
            pos.direction = DIRECTION_LONG          # 定义到头仓位
        elif data[2] < 0:
            pos.direction = DIRECTION_SHORT         # 定义空头仓位
        else:
            pos.direction = DIRECTION_NET           # 定义没有none 仓位 需要注意的是在进行平仓的动作之后，我们默认的为 net ，怎么去维护我们的pos ,在ctaenging中

        # 这里定义了一个全局变量方便后边引用对交易信息，已经订单信息进行判断
        self.direction = pos.direction

        pos.vtPositionName = ':'.join([pos.vtSymbol, pos.direction])
        pos.frozen = 0                               # 期货没有冻结概念，会直接反向开仓
        pos.price = data[3]                          # 持仓均价
        if data[6]:                                  # 持仓盈亏
            pos.positionProfit = data[6]
        self.gateway.onPosition(pos)

    #----------------------------------------------------------------------
    def queryPosition(self):
        """"""
        self.sendRestReq('/positions', self.onQueryPosition , post=True)

        # 接下来是检验下数据看是不是进行了仓位的初始化
        print("启用连续查询 仓位position初始化")





    #----------------------------------------------------------------------
    def queryAccount(self):
        """"""
        self.sendRestReq('/margin_infos', self.onQueryAccount , post=True)
        self.writeLog(u"启用连续查询 仓位margin账户初始化")
        self.sendRestReq('/margin_infos', self.printData , post=True)



    def onOrder(self, data):

        order = VtOrderData()
        order.gatewayName = self.gatewayName

        order.symbol = str(data[3].replace('t', ''))                               # 交易对 EOSUSD
        order.exchange = EXCHANGE_BITFINEX                                         # 交易对 BITFINEX
        order.vtSymbol = ':'.join([order.symbol, order.exchange])                  # vnpy 系统编号 EOSUSD:BITFINEX

        order.orderID = str(data[2])                                               # 交易对 1553115420502   交易所返回的client订单编号
        order.vtOrderID = ':'.join([order.gatewayName, order.orderID])             # vnpy 系统编号 BITFINEX:1553115420502
        order.priceType = str(data[8])                                             # 价格类型

        # 当之前没有仓位的状态下
        """
        buy ---- sell
        long  open /   short close
        short ---cover
        short open /  long  close

        """
        # 之前没有仓位，那么 买开 或者  卖开
        if self.direction == DIRECTION_NET:
            if data[7] > 0:
                print('之前仓位为0，买开')
                self.writeLog(u'之前仓位为0，买开')
                order.direction = DIRECTION_LONG
                order.offset = OFFSET_OPEN
            else:
                print('之前仓位为0，卖开')
                self.writeLog(u'之前仓位为0，卖开')
                order.direction = DIRECTION_SHORT
                order.offset = OFFSET_OPEN
        # 之前有多头持仓 那么加仓 那么减仓（卖出）
        elif self.direction == DIRECTION_LONG:  # 如果持有多仓仓位(注意这里是之前的仓位)
            if data[7] > 0:
                print('之前持有多头仓位，买开加仓')
                self.writeLog(u'之前持有多头仓位，买开加仓')
                order.direction = DIRECTION_LONG
                order.offset = OFFSET_OPEN
            else:
                print('之前持有多头仓位，卖出减仓')
                self.writeLog(u'之前持有多头仓位，卖出减仓')
                order.direction = DIRECTION_SHORT
                order.offset = OFFSET_CLOSE
        # 之前持有空头仓位 那么加仓  那么平仓（买入）
        elif self.direction == DIRECTION_SHORT:
            if data[7] > 0:
                print('之前持有空头仓位，平空减仓')
                self.writeLog(u'之前持有空头仓位，平空减仓')
                order.direction = DIRECTION_LONG
                order.offset = OFFSET_CLOSE
            else:
                print('之前持有空头仓位，做空加仓')
                self.writeLog(u'之前持有空头仓位，做空加仓')
                order.direction = DIRECTION_SHORT
                order.offset = OFFSET_OPEN

        order.price = float(data[16])                                     # 价格

        # 根据后边对其中的持仓的处理，首先推送到是position 为了避免冲突所以，这里全部置为0
        order.totalVolume = 0
        order.tradedVolume = 0
        order.thisTradedVolume = 0
        order.signalTradedVolume = abs(data[7]) - abs(data[6])                # 这里定义一个新的变量作为策略之中的判定使用

        # 在非完全成交状态下的判断,目前映射状态有很多
        if str(data[13]) == 'INSUFFICIENT BALANCE (U1)' or str(data[13]) =='INSUFFICIENTBALANCE(G1)was:PARTIALLYFILLED':
            # order.status = "资金量不足"
            order.status = STATUS_UNKNOWN  # 状态为 未知
            print("资金量不足")
            self.writeLog(u'资金量不足')
        else:
            orderStatus = str(data[13].split('@')[0])
            orderStatus = orderStatus.replace(' ', '')
            order.status = statusMapReverse[orderStatus]                        # 对应的映射为STATUS_ALLTRADED    完全成交

        order.sessionID, order.orderTime = self.generateDateTime(data[4])       # 订单创建时间
        if order.status == STATUS_CANCELLED:
            buf, order.cancelTime = self.generateDateTime(data[5])

        # ===============================本地的订单编号为，key 为ID即order 编号，此标号为trade   values 为订单cid 即我们传入的cid
        self.orderLocalDict[data[0]] = order.orderID
        self.gateway.onOrder(order)
        self.calc()


    # ----------------------------------------------------------------------
    def onTrade(self, data):

        trade = VtTradeData()
        trade.gatewayName = self.gatewayName

        trade.symbol = data[1].replace('t', '')
        trade.exchange = EXCHANGE_BITFINEX
        trade.vtSymbol = ':'.join([trade.symbol, trade.exchange])


        bitfinex_id = self.orderLocalDict.get(data[3], None)
        if not bitfinex_id:
            self.orderLocalDict[data[3]] = data[11]
        trade.orderID = self.orderLocalDict[data[3]]

        trade.vtOrderID = ':'.join([trade.gatewayName, str(trade.orderID)])
        # 注意返回值之中的第一个是trade 的编号id,这里需要是str
        trade.tradeID = str(data[0])
        trade.vtTradeID = ':'.join([trade.gatewayName, trade.tradeID])

        # 因为trade 返回只有成交的数量，没有成交的方向，所以可以根据仓位来进行判定，思路与order 是一致的；
        # 这里的trade 还是很有必要的，因为在部分的策略之中，是根据trade 的方向进行开仓与加仓的仓位的 价格的变化的，比如海龟交易策略
        if data[4] > 0 and self.direction == DIRECTION_LONG:
            print('成交（加仓）')
            trade.direction = DIRECTION_LONG
            trade.offset = OFFSET_OPEN
        elif data[4] > 0 and self.direction == DIRECTION_SHORT:
            print('买平')
            trade.direction = DIRECTION_LONG
            trade.offset = OFFSET_CLOSE
        elif data[4] > 0 and self.direction == DIRECTION_NET:
            print('买开')
            trade.direction = DIRECTION_LONG
            trade.offset = OFFSET_OPEN

        elif data[4] < 0 and self.direction == DIRECTION_LONG:
            print('卖平')
            trade.direction = DIRECTION_SHORT
            trade.offset = OFFSET_CLOSE
        elif data[4] < 0 and self.direction == DIRECTION_SHORT:
            print('做空加仓')
            trade.direction = DIRECTION_SHORT
            trade.offset = OFFSET_OPEN
        elif data[4] < 0 and self.direction == DIRECTION_NET:
            print('卖开')
            trade.direction = DIRECTION_SHORT
            trade.offset = OFFSET_OPEN

        trade.price = data[5]                                        # 成交的价格
        buf, trade.tradeTime = self.generateDateTime(data[2])        # 成交的时间


        # 根据目前的测试 暂时修改为  v3
        trade.volume = 0                         # 成交的数量v1
        trade.signalvolume = abs(data[4])        # 这里重新定义一个新的标量作为策略之中的判定使用

        self.gateway.onTrade(trade)


    # ----------------------------------------------------------------------
    def onSymbolDetails(self, data):

        for d in data:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            contract.symbol = d['pair'].upper()                                    # btcusd ---->BTCUSD
            contract.exchange = EXCHANGE_BITFINEX
            contract.vtSymbol = ':'.join([contract.symbol, contract.exchange])      # 合约在vt系统中的唯一代码，通常是 合约代码:交易所代码
            contract.name = contract.vtSymbol                                       # 合约中文名
            contract.productClass = PRODUCT_SPOT                                    # 现货交易

            # contract.size = 1                                                          # 合约大小 数字货币现货合约大小为1
            # contract.priceTick = pow(10, d["price_precision"])                         # 10 的5次方
            # contract.price_precision = d["price_precision"]

            contract.size = float(d['minimum_order_size'])                                # 下单数量精度
            contract.price_precision = d["price_precision"]
            contract_priceTick = pow(10, -int(d["price_precision"]))                      # 下单价格精度
            contract.priceTick = self.as_num(contract_priceTick)
            # print('bitfinexgateway contract._dict_', contract.__dict__)

            self.gateway.onContract(contract)

        self.writeLog(u'合约信息查询成功')


    def as_num(self,x):
        y = '{:.5f}'.format(x)        # 5f表示保留5位小数点的float型
        return y


    # ----------------------------------------------------------------------
    def onQueryPosition(self, data):


        for d in data:
            if float(d['amount']) > 0:                                                                #注意字符串转换成浮点数字
                longPosition = VtPositionData()
                longPosition.gatewayName = self.gatewayName
                # print(" 启动 onQueryPosition  longPosition.gatewayName  ",longPosition.gatewayName )
                longPosition.symbol = d['symbol'].upper()                                      # btcusd ---->BTCUSD
                longPosition.exchange = EXCHANGE_BITFINEX
                longPosition.vtSymbol = ':'.join([longPosition.symbol, longPosition.exchange])         # 合约在vt系统中的唯一代码，通常是 合约代码:交易所代码
                longPosition.direction = DIRECTION_LONG          # 定义到头仓位
                longPosition.vtPositionName = ':'.join([longPosition.vtSymbol, longPosition.direction])
                longPosition.price = float(d['base'])
                longPosition.positionProfit = float(d['pl'])
                longPosition.position = abs(float(d['amount']))
                self.gateway.onPosition(longPosition)
            elif float(d['amount']) < 0:
                shortPosition = VtPositionData()
                shortPosition.gatewayName = self.gatewayName
                shortPosition.symbol = d['symbol'].upper()                                      # btcusd ---->BTCUSD
                shortPosition.exchange = EXCHANGE_BITFINEX
                shortPosition.vtSymbol = ':'.join([shortPosition.symbol, shortPosition.exchange])         # 合约在vt系统中的唯一代码，通常是 合约代码:交易所代码
                shortPosition.position = abs(float(d['amount']))
                shortPosition.direction = DIRECTION_SHORT
                shortPosition.vtPositionName = ':'.join([shortPosition.vtSymbol, shortPosition.direction])
                shortPosition.price = float(d['base'])
                shortPosition.positionProfit = float(d['pl'])
                self.gateway.onPosition(shortPosition)

        self.writeLog(u'仓位初始化查询成功')

    # ----------------------------------------------------------------------
    def onQueryAccount(self, data):
        # 这里是仅仅对margin account 账户信息进行优化处理
        pd = data[0]
        account = VtAccountData()
        account.vtAccountID = self.gatewayName
        account.gatewayName = self.gatewayName
        account.accountID = 'USD'  # 交易的币种
        account.vtAccountID = ':'.join([account.gatewayName, account.accountID])

        account.balance = float(pd['margin_balance'])                         # 账户净值
        account.available = float(pd['net_value'])                            # 可用资金
        account.margin = float(pd['required_margin'])                         # 保证金占用
        account.positionProfit = float(pd['unrealized_pl'])                   # 持仓盈亏
        # account.closeProfit = float(d['realized_pnl'])

        self.gateway.onAccount(account)




    # =====发送钉钉消息，id填上使用的机器人的id
    def send_dingding_msg(self, content, robot_id='5cc1fc681a06a263ea3467cec845'):
        try:
            msg = {
                "msgtype": "text",
                "text": {"content": content + '\n' + datetime.now().strftime("%m-%d %H:%M:%S")}}
            headers = {"Content-Type": "application/json;charset=utf-8"}
            url = 'https://oapi.dingtalk.com/robot/send?access_token=' + robot_id
            body = json.dumps(msg)
            requests.post(url, data=body, headers=headers)
            print('成功发送钉钉')
        except Exception as e:
            print("发送钉钉失败:", e)

    # =====获取bitfinex交易所k线
    def get_bitfinex_candle_data(self,exchange, symbol, time_interval, limit):
        while True:
            try:
                content = exchange.fetch_ohlcv(symbol=symbol, timeframe=time_interval, limit=limit)
                break
            except Exception as e:
                self.send_dingding_msg(content='抓不到k线，稍等重试')
                print(e)
                sleep(5 * 1)

        df = pd.DataFrame(content, dtype=float)
        df.rename(columns={0: 'MTS', 1: 'open', 2: 'high', 3: 'low', 4: 'close', 5: 'volume'}, inplace=True)
        df['candle_begin_time'] = pd.to_datetime(df['MTS'], unit='ms')
        df['candle_begin_time_GMT8'] = df['candle_begin_time'] + timedelta(hours=8)
        # df = df[['candle_begin_time_GMT8', 'open', 'high', 'low', 'close', 'volume']]
        # 在这里使用的是中国本地时间 所以需要GMT8 如果在服务器上跑直接使用candle_begin_time这一列就可以了
        df = df[['candle_begin_time', 'open', 'high', 'low', 'close', 'volume']]

        return df





