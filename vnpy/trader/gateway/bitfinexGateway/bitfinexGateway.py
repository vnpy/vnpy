# encoding: UTF-8

'''
vnpy.api.bitfinex的gateway接入
'''

import os
import json
import hashlib
import hmac
import time
from datetime import datetime, timedelta
from copy import copy
from math import pow

from vnpy.api.bitfinex import BitfinexApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath

# 委托状态类型映射
statusMapReverse = {}
statusMapReverse['ACTIVE'] = STATUS_NOTTRADED
statusMapReverse['PARTIALLY FILLED'] = STATUS_PARTTRADED
statusMapReverse['EXECUTED'] = STATUS_ALLTRADED
statusMapReverse['CANCELED'] = STATUS_CANCELLED

# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = 'EXCHANGE LIMIT'
priceTypeMap[PRICETYPE_MARKETPRICE] = 'EXCHANGE MARKET'



########################################################################
class BitfinexGateay(VtGateway):
    """Bitfinex接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName=''):
        """Constructor"""
        super(BitfinexGateay, self).__init__(eventEngine, gatewayName)

        self.api = GatewayApi(self)

        self.qryEnabled = False         # 是否要启动循环查询

        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)

    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
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
            symbols = setting['symbols']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

        # 创建行情和交易接口对象
        self.api.connect(apiKey, secretKey, symbols)

        # 初始化并启动查询
        #self.initQuery()

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        pass

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.api.sendOrder(orderReq)

    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.api.cancelOrder(cancelOrderReq)

    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.api.close()
    
    #----------------------------------------------------------------------
    def queryAccount(self):
        """"""
        self.api.queryAccount()

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
class GatewayApi(BitfinexApi):
    """API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(GatewayApi, self).__init__()

        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.orderId = 1000000
        self.date = int(datetime.now().strftime('%y%m%d%H%M%S')) * self.orderId
        
        self.apiKey = ''
        self.secretKey = ''
        self.symbols = []
        self.currencys = []

        self.tickDict = {}
        self.bidDict = {}
        self.askDict = {}
        self.orderLocalDict = {}
        
        self.channelDict = {}       # ChannelID : (Channel, Symbol)

    #----------------------------------------------------------------------
    def connect(self, apiKey, secretKey, symbols):
        """连接服务器"""
        self.apiKey = apiKey
        self.secretKey = secretKey
        self.symbols = symbols
        
        self.start()
        self.writeLog(u'交易API启动成功')
        
    #----------------------------------------------------------------------
    def onConnect(self):
        """"""
        for symbol in self.symbols:
            self.subscribe(symbol, 'ticker')
            self.subscribe(symbol, 'book')
        self.writeLog(u'行情推送订阅成功')             
        
        self.authenticate()
        self.writeLog(u'交易推送订阅成功')
        
        self.sendRestReq('/symbols_details', self.onSymbolDetails)
    
    #----------------------------------------------------------------------
    def subscribe(self, symbol, channel):
        """"""
        req = {
            'event': 'subscribe',
            'channel': channel,
            'symbol': symbol
        }
        self.sendReq(req)
        
    #----------------------------------------------------------------------
    def authenticate(self):
        """"""
        nonce = int(time.time() * 1000000)
        authPayload = 'AUTH' + str(nonce)
        signature = hmac.new(
          self.secretKey.encode(),
          msg = authPayload.encode(),
          digestmod = hashlib.sha384
        ).hexdigest()
        
        req = {
          'apiKey': self.apiKey,
          'event': 'auth',
          'authPayload': authPayload,
          'authNonce': nonce,
          'authSig': signature
        }
        
        self.sendReq(req)

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    #----------------------------------------------------------------------
    def generateDateTime(self, s):
        """生成时间"""
        dt = datetime.fromtimestamp(s/1000.0)
        date = dt.strftime('%Y-%m-%d')
        time = dt.strftime("%H:%M:%S.%f")
        return date, time    
    
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """"""
        self.orderId += 1
        orderId = self.date + self.orderId
        vtOrderID = '.'.join([self.gatewayName, str(orderId)])
        
        if orderReq.direction == DIRECTION_LONG:
            amount = orderReq.volume
        else:
            amount = -orderReq.volume
            
        o = {
            'cid': orderId,
            'type': priceTypeMap[orderReq.priceType],
            'symbol': 't' + orderReq.symbol,
            'amount': str(amount),
            'price': str(orderReq.price)
        }
        
        req = [0, 'on', None, o]
        self.sendReq(req)
        
        return vtOrderID
    
    #----------------------------------------------------------------------
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
    
    #----------------------------------------------------------------------
    def calc(self):
        """"""
        l = []
        for currency in self.currencys:
            l.append(['wallet_exchange_' + currency])
        
        req = [0, 'calc', None, l]
        self.sendReq(req)
    
    #----------------------------------------------------------------------
    def onData(self, data):
        """"""
        if isinstance(data, dict):
            self.onResponse(data)
        else:
            self.onUpdate(data)
    
    #----------------------------------------------------------------------
    def onResponse(self, data):
        """"""
        if 'event' not in data:
            return
        
        if data['event'] == 'subscribed':
            symbol = str(data['symbol'].replace('t', ''))
            #symbol = str(data['symbol'])
            self.channelDict[data['chanId']] = (data['channel'], symbol)
    
    #----------------------------------------------------------------------
    def onUpdate(self, data):
        """"""
        if data[1] == u'hb':
            return
        
        channelID = data[0]
        
        if not channelID:
            self.onTradeUpdate(data)
        else:
            self.onDataUpdate(data)
    
    #----------------------------------------------------------------------
    def onDataUpdate(self, data):
        """"""
        channelID = data[0]
        channel, symbol = self.channelDict[channelID]
        symbol = str(symbol.replace('t', ''))
        #symbol = str(symbol)
        
        # 获取Tick对象
        if symbol in self.tickDict:
            tick = self.tickDict[symbol]
        else:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.symbol = symbol
            tick.exchange = EXCHANGE_BITFINEX
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            
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
                        bid[price ] = amount
                    else:
                        ask[price] = -amount
            
            # Bitfinex的深度数据更新是逐档推送变动情况，而非5档一起推
            # 因此会出现没有Bid或者Ask的情况，这里使用try...catch过滤
            # 只有买卖深度满足5档时才做推送
            try:
                # BID
                bidPriceList = bid.keys()
                bidPriceList.sort(reverse=True)
                
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
                askPriceList.sort()
                
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
    
    #----------------------------------------------------------------------
    def onTradeUpdate(self, data):
        """"""
        name = data[1]
        info = data[2]
        
        if name == 'ws':
            for l in info:
                self.onWallet(l)
            self.writeLog(u'账户资金获取成功')
        elif name == 'wu':
            self.onWallet(info)
        elif name == 'os':
            for l in info:
                self.onOrder(l)
            self.writeLog(u'活动委托获取成功')
        elif name in ['on', 'ou', 'oc']:
            self.onOrder(info)
        elif name == 'te':
            self.onTrade(info)
    
    #----------------------------------------------------------------------
    def onWallet(self, data):
        """"""
        if str(data[0]) == 'exchange':
            account = VtAccountData()
            account.gatewayName = self.gatewayName
            
            account.accountID = str(data[1])
            account.vtAccountID = '.'.join([account.gatewayName, account.accountID])
            account.balance = float(data[2])
            account.available = float(data[-1])
            
            self.gateway.onAccount(account)            
    
    #----------------------------------------------------------------------
    def onOrder(self, data):
        """"""
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        
        order.symbol = str(data[3].replace('t', ''))
        order.exchange = EXCHANGE_BITFINEX
        order.vtSymbol = '.'.join([order.symbol, order.exchange])
        
        order.orderID = str(data[2])
        order.vtOrderID = '.'.join([order.gatewayName, order.orderID])
        
        if data[7] > 0:
            order.direction = DIRECTION_LONG
        elif data[7] < 0:
            order.direction = DIRECTION_SHORT
            
        order.price = float(data[16])
        order.totalVolume = abs(data[7])
        order.tradedVolume = order.totalVolume - abs(data[6])
        
        orderStatus = str(data[13].split('@')[0])
        orderStatus = orderStatus.replace(' ', '')
        order.status = statusMapReverse[orderStatus]
        
        order.sessionID, order.orderTime = self.generateDateTime(data[4])
        if order.status == STATUS_CANCELLED:
            buf, order.cancelTime = self.generateDateTime(data[5])
        
        self.orderLocalDict[data[0]] = order.orderID
        
        self.gateway.onOrder(order)      
        
        self.calc()
    
    #----------------------------------------------------------------------
    def onTrade(self, data):
        """"""
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        trade.symbol = data[1].replace('t', '')
        trade.exchange = EXCHANGE_BITFINEX
        trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
        trade.orderID = self.orderLocalDict[data[3]]
        trade.vtOrderID = '.'.join([trade.gatewayName, trade.orderID])
        trade.tradeID = str(data[0])
        trade.vtTradeID = '.'.join([trade.gatewayName, trade.tradeID])
        
        if data[4] > 0:
            trade.direction = DIRECTION_LONG
        else:
            trade.direction = DIRECTION_SHORT
            
        trade.price = data[5]
        trade.volume = abs(data[4])
        buf, trade.tradeTime = self.generateDateTime(data[2])
        
        self.gateway.onTrade(trade)        
    
    #----------------------------------------------------------------------
    def onSymbolDetails(self, data):
        """"""
        for d in data:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            
            contract.symbol = d['pair'].upper()
            contract.exchange = EXCHANGE_BITFINEX
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = contract.vtSymbol
            contract.productClass = PRODUCT_SPOT
            contract.priceTick = pow(10, d["price_precision"])
            contract.size = 1    
            
            self.gateway.onContract(contract)
        
        self.writeLog(u'合约信息查询成功')
