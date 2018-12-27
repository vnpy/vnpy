# encoding: UTF-8

'''
火币交易接口
'''

from __future__ import print_function

import base64
import hashlib
import hmac
import json
import re
import urllib
import zlib
from copy import copy

from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getTempPath, getJsonPath

REST_HOST = 'https://api.huobipro.com'
#REST_HOST = 'https://api.huobi.pro/v1'
WEBSOCKET_MARKET_HOST = 'wss://api.huobi.pro/ws'        # Global站行情
WEBSOCKET_TRADE_HOST = 'wss://api.huobi.pro/ws/v1'     # 资产和订单


#----------------------------------------------------------------------
def _split_url(url):
    """
    将url拆分为host和path
    :return: host, path
    """
    m = re.match('\w+://([^/]*)(.*)', url)
    if m:
        return m.group(1), m.group(2)


#----------------------------------------------------------------------
def createSignature(apiKey, method, host, path, secretKey, getParams=None):
    """
    创建签名
    :param getParams: dict 使用GET方法时附带的额外参数(urlparams)
    :return:
    """
    sortedParams = [
        ("AccessKeyId", apiKey),
        ("SignatureMethod", 'HmacSHA256'),
        ("SignatureVersion", "2"),
        ("Timestamp", datetime.utcnow().strftime('%Y-%m-%dT%H:%M:%S'))
    ]
    if getParams:
        sortedParams.extend(getParams.items())
        sortedParams = list(sorted(sortedParams))
    encodeParams = urllib.urlencode(sortedParams)
    
    payload = [method, host, path, encodeParams]
    payload = '\n'.join(payload)
    payload = payload.encode(encoding='UTF8')
    
    secretKey = secretKey.encode(encoding='UTF8')
    
    digest = hmac.new(secretKey, payload, digestmod=hashlib.sha256).digest()
    signature = base64.b64encode(digest)
    
    params = dict(sortedParams)
    params["Signature"] = signature
    return params


########################################################################
class HuobiGateway(VtGateway):
    """火币接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='HUOBI'):
        """Constructor"""
        super(HuobiGateway, self).__init__(eventEngine, gatewayName)

        self.localID = 10000
        
        self.accountDict = {}
        self.orderDict = {}
        self.localOrderDict = {}
        self.orderLocalDict = {}

        self.restApi = HuobiRestApi(self)                   
        self.tradeWsApi = HuobiTradeWebsocketApi(self)      
        self.marketWsApi = HuobiMarketWebsocketApi(self)    

        self.qryEnabled = False         # 是否要启动循环查询

        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)

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
        try:
            accessKey = str(setting['accessKey'])
            secretKey = str(setting['secretKey'])
            symbols = setting['symbols']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

        # 创建行情和交易接口对象
        self.restApi.connect(symbols, accessKey, secretKey)
        self.tradeWsApi.connect(symbols, accessKey, secretKey)
        self.marketWsApi.connect(symbols, accessKey, secretKey)

        # 初始化并启动查询
        #self.initQuery()

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        pass

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
        self.tradeWsApi.stop()
        self.marketWsApi.stop()

    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryInfo]

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
    
    #----------------------------------------------------------------------
    def writeLog(self, msg):
        """"""
        log = VtLogData()
        log.logContent = msg
        log.gatewayName = self.gatewayName
        
        event = Event(EVENT_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)
        


########################################################################
class HuobiRestApi(RestClient):
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):  # type: (VtGateway)->HuobiRestApi
        """"""
        super(HuobiRestApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        
        self.symbols = []
        self.apiKey = ""
        self.apiSecret = ""
        self.signHost = ""
        
        self.accountDict = gateway.accountDict
        self.orderDict = gateway.orderDict
        self.orderLocalDict = gateway.orderLocalDict
        self.localOrderDict = gateway.localOrderDict
        
        self.accountid = ''     # 
        self.cancelReqDict = {}
        
    #----------------------------------------------------------------------
    def sign(self, request):
        request.headers = {
            "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.71 Safari/537.36"
        }
        paramsWithSignature = createSignature(self.apiKey,
                                           request.method,
                                           self.signHost,
                                           request.path,
                                           self.apiSecret,
                                           request.params)
        request.params = paramsWithSignature
   
        if request.method == "POST":
            request.headers['Content-Type'] = 'application/json'
   
        return request
    
    #----------------------------------------------------------------------
    def connect(self, symbols, apiKey, apiSecret, sessionCount=3):
        """连接服务器"""
        self.symbols = symbols
        self.apiKey = apiKey
        self.apiSecret = apiSecret
        
        host, path = _split_url(REST_HOST)
        self.init(REST_HOST)
        
        self.signHost = host
        self.start(sessionCount)
        
        self.queryContract()
    
    #----------------------------------------------------------------------
    def queryAccount(self):
        """"""
        self.addRequest('GET', '/v1/account/accounts', self.onQueryAccount)
    
    #----------------------------------------------------------------------
    def queryAccountBalance(self):
        """"""
        path = '/v1/account/accounts/%s/balance' %self.accountid
        self.addRequest('GET', path, self.onQueryAccountBalance)
    
    #----------------------------------------------------------------------
    def queryOrder(self):
        """"""
        path = '/v1/order/orders'
        
        todayDate = datetime.now().strftime('%Y-%m-%d')
        statesActive = 'submitted,partial-filled'
        
        for symbol in self.symbols:
            params = {
                'symbol': symbol,
                'states': statesActive,
                'end_date': todayDate
            }
            self.addRequest('GET', path, self.onQueryOrder, params=params)

    #----------------------------------------------------------------------
    def queryContract(self):
        """"""
        self.addRequest('GET', '/v1/common/symbols', self.onQueryContract)
    
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """"""
        self.gateway.localID += 1
        localID = str(self.gateway.localID)
        vtOrderID = '.'.join([self.gatewayName, localID])

        if orderReq.direction == DIRECTION_LONG:
            type_ = 'buy-limit'
        else:
            type_ = 'sell-limit'
        
        params = {
            'account-id': self.accountid,
            'amount': str(orderReq.volume),
            'symbol': orderReq.symbol,
            'type': type_,
            'price': orderReq.price,
            'source': 'api'
        }
        
        self.addRequest('POST', path, self.onSendOrder, 
                        params=params, extra=localID)

        # 返回订单号
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelReq):
        """"""
        localID = cancelOrderReq.orderID
        orderID = self.localOrderDict.get(localID, None)

        if orderID:
            path = '/v1/order/orders/%s/submitcancel' %orderID
            self.addRequest('POST', path, self.onCancelOrder)
            
            if localID in self.cancelReqDict:
                del self.cancelReqDict[localID]
        else:
            self.cancelReqDict[localID] = cancelOrderReq        
    
    #----------------------------------------------------------------------
    def onQueryAccount(self, data, request):  # type: (dict, Request)->None
        """"""
        for d in data['data']:
            if str(d['type']) == 'spot':
                self.accountid = str(d['id'])
                self.gateway.writeLog(u'交易账户%s查询成功' %self.accountid)        
        
        self.queryAccountBalance()
    
    #----------------------------------------------------------------------
    def onQueryAccountBalance(self, data, request):  # type: (dict, Request)->None
        """"""
        for d in data['data']['list']:
            currency = d['currency']
            account = self.accountDict.get(currency, None)

            if not account:
                account = VtAccountData()
                account.gatewayName = self.gatewayName
                account.accountID = d['currency']
                account.vtAccountID = '.'.join([account.gatewayName, account.accountID])
                
                self.accountDict[currency] = account
            
            if d['type'] == 'trade':
                account.available = float(d['balance'])
            elif d['type'] == 'frozen':
                account.margin = float(d['balance'])
            
            account.balance = account.margin + account.available

        for account in self.accountDict.values():
            self.gateway.onAccount(account)   
        
        self.gateway.writeLog(u'账户资金信息查询成功')
        self.queryOrder()
    
    #----------------------------------------------------------------------
    def onQueryOrder(self, data, request):  # type: (dict, Request)->None
        """"""
        print(data)
        
        data.reverse()

        for d in data:
            orderID = d['id']
            strOrderID = str(orderID)

            self.localID += 1
            localID = str(self.localID)

            self.orderLocalDict[strOrderID] = localID
            self.localOrderDict[localID] = strOrderID

            order = VtOrderData()
            order.gatewayName = self.gatewayName

            order.orderID = localID
            order.vtOrderID = '.'.join([order.gatewayName, order.orderID])

            order.symbol = d['symbol']
            order.exchange = EXCHANGE_HUOBI
            order.vtSymbol = '.'.join([order.symbol, order.exchange])

            order.price = float(d['price'])
            order.totalVolume = float(d['amount'])
            order.tradedVolume = float(d['field-amount'])
            order.status = statusMapReverse.get(d['state'], STATUS_UNKNOWN)

            if 'buy' in d['type']:
                order.direction = DIRECTION_LONG
            else:
                order.direction = DIRECTION_SHORT
            order.offset = OFFSET_NONE
            
            order.orderTime = datetime.fromtimestamp(d['created-at']/1000).strftime('%H:%M:%S')
            if d['canceled-at']:
                order.cancelTime = datetime.fromtimestamp(d['canceled-at']/1000).strftime('%H:%M:%S')

            self.orderDict[orderID] = order
            self.gateway.onOrder(order)
        
        self.gateway.writeLog(u'委托信息查询成功')

    #----------------------------------------------------------------------
    def onQueryContract(self, data, request):  # type: (dict, Request)->None
        """"""
        for d in data['data']:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName

            contract.symbol = d['base-currency'] + d['quote-currency']
            contract.exchange = EXCHANGE_HUOBI
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])

            contract.name = '/'.join([d['base-currency'].upper(), d['quote-currency'].upper()])
            contract.priceTick = 1 / pow(10, d['price-precision'])
            contract.size = 1 / pow(10, d['amount-precision'])
            contract.productClass = PRODUCT_SPOT

            self.gateway.onContract(contract)

        self.gateway.writeLog(u'合约信息查询成功')
        self.queryAccount()        

    #----------------------------------------------------------------------
    def onSendOrder(self, data, request):  # type: (dict, Request)->None
        """"""
        localID = request.extra
        orderID = data
        self.localOrderDict[localID] = orderID
        
        req = self.cancelReqDict.get(localID, None)
        if req:
            self.cancelOrder(req)
    
    #----------------------------------------------------------------------
    def onCancelOrder(self, data, request):  # type: (dict, Request)->None
        """"""
        self.gateway.writeLog(u'委托撤单成功：%s' %data)


########################################################################
class HuobiWebsocketApiBase(WebsocketClient):
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(HuobiWebsocketApiBase, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        
        self.apiKey = ''
        self.apiSecret = ''
        self.signHost = ''
        self.path = ''
    
    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, url):
        """"""
        self.apiKey = apiKey
        self.apiSecret = apiSecret
        
        host, path = _split_url(url)
        
        self.init(url)
        self.signHost = host
        self.path = path
        self.start()
    
    #----------------------------------------------------------------------
    def login(self):
        params = {
            'op': 'auth',
        }
        params.update(
            createSignature(self.apiKey,
                            'GET',
                            self.signHost,
                            self.path,
                            self.apiSecret)
        )
        return self.sendPacket(params)
    
    #----------------------------------------------------------------------
    def onLogin(self, packet):
        """"""
        pass
    
    #----------------------------------------------------------------------
    @staticmethod
    def unpackData(data):
        return json.loads(zlib.decompress(data, 31))    
    
    #----------------------------------------------------------------------
    def onPacket(self, packet):
        """"""
        if 'ping' in packet:
            self.sendPacket({'pong': packet['ping']})
            return
        
        if 'err-msg' in packet:
            return self.onErrorMsg(packet)
        
        if "op" in packet and packet["op"] == "auth":
            return self.onLogin()
        
        self.onData(packet)
    
    #----------------------------------------------------------------------
    def onData(self, packet):  # type: (dict)->None
        """"""
        print("data : {}".format(packet))
    
    #----------------------------------------------------------------------
    def onErrorMsg(self, packet):  # type: (dict)->None
        """"""
        self.gateway.writeLog(packet['err-msg'])


########################################################################
class HuobiTradeWebsocketApi(HuobiWebsocketApiBase):
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """"""
        super(HuobiTradeWebsocketApi, self).__init__(gateway)
        
        self.reqID = 10000
        
        self.accountDict = gateway.accountDict
        self.orderDict = gateway.orderDict
        self.orderLocalDict = gateway.orderLocalDict
        self.localOrderDict = gateway.localOrderDict
    
    #----------------------------------------------------------------------
    def connect(self, symbols, apiKey, apiSecret):
        """"""
        self.symbols = symbols
        
        super(HuobiTradeWebsocketApi, self).connect(apiKey, 
                                                    apiSecret,
                                                    WEBSOCKET_TRADE_HOST)
    
    #----------------------------------------------------------------------
    def subscribeTopic(self):
        """"""
        # 订阅资金变动
        self.reqID += 1
        req = {
            "op": "sub",
            "cid": str(self.reqID),
            "topic": "accounts"            
        }
        self.sendPacket(req)
        
        # 订阅委托变动
        for symbol in self.symbols:
            self.reqID += 1
            req = {
                "op": "sub",
                "cid": str(self.reqID),
                "topic": 'orders.%s' %symbol            
            }
            self.sendPacket(req)
    
    #----------------------------------------------------------------------
    def onConnected(self):
        """"""
        self.login()
    
    #----------------------------------------------------------------------
    def onLogin(self):
        """"""
        self.gateway.writeLog(u'交易Websocket服务器登录成功')
        
        self.subscribeTopic()
        
    #----------------------------------------------------------------------
    def onData(self, packet):  # type: (dict)->None
        """"""
        op = packet.get('op', None)
        if op != 'notify':
            return
        
        topic = packet['topic']
        if topic == 'accounts':
            self.onAccount(packet['data'])
        elif 'orders' in topic:
            self.onOrder(packet['data'])
        
    #----------------------------------------------------------------------
    def onAccount(self, data):
        """"""
        for d in data['list']:
            account = self.accountDict.get(d['currency'], None)
            if not account:
                continue
            
            if d['type'] == 'trade':
                account.available = float(d['balance'])
            elif d['type'] == 'frozen':
                account.margin = float(d['balance'])
            
            account.balance = account.margin + account.available   
            self.gateway.onAccount(account)

    #----------------------------------------------------------------------
    def onOrder(self, data):
        """"""
        orderID = data['id']
        strOrderID = str(orderID)
        order = self.orderDict.get(strOrderID, None)
        
        if not order:
            self.gateway.localID += 1
            localID = str(self.gateway.localID)

            self.orderLocalDict[strOrderID] = localID
            self.localOrderDict[localID] = strOrderID

            order = VtOrderData()
            order.gatewayName = self.gatewayName
    
            order.orderID = localID
            order.vtOrderID = '.'.join([order.gatewayName, order.orderID])
    
            order.symbol = data['symbol']
            order.exchange = EXCHANGE_HUOBI
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
    
            order.price = float(data['order-price'])
            order.totalVolume = float(data['order-amount'])
            
            dt = datetime.fromtimestamp(data['created-at']/1000)
            order.orderTime = dt.strftime('%H:%M:%S')
        
        order.tradedVolume += float(data['filled-amount'])
        order.status = statusMapReverse.get(data['order-state'], STATUS_UNKNOWN)        
        
        self.gateway.onOrder(order)
        
        
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName

        trade.tradeID = data['seq-id']
        trade.vtTradeID = '.'.join([trade.tradeID, trade.gatewayName])

        trade.symbol = data['symbol']
        trade.exchange = EXCHANGE_HUOBI
        trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
        trade.direction = order.direction
        trade.offset = order.offset
        trade.orderID = order.orderID
        trade.vtOrderID = order.vtOrderID
        
        trade.price = float(data['price'])
        trade.volume = float(data['filled-amount'])

        dt = datetime.now()
        trade.tradeTime = dt.strftime('%H:%M:%S')

        self.gateway.onTrade(trade)
    
    #----------------------------------------------------------------------
    def onOrderOld(self, data):
        """"""
        orderID = data['id']
        strOrderID = str(orderID)
       
        newTrade = False 
        order = self.orderDict.get(strOrderID, None)
        
        if not order:
            self.gateway.localID += 1
            localID = str(self.gateway.localID)

            self.orderLocalDict[strOrderID] = localID
            self.localOrderDict[localID] = strOrderID

            order = VtOrderData()
            order.gatewayName = self.gatewayName
    
            order.orderID = localID
            order.vtOrderID = '.'.join([order.gatewayName, order.orderID])
    
            order.symbol = data['symbol']
            order.exchange = EXCHANGE_HUOBI
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
    
            order.price = float(data['order-price'])
            order.totalVolume = float(data['order-amount'])
            
            dt = datetime.fromtimestamp(data['created-at']/1000)
            order.orderTime = dt.strftime('%H:%M:%S')
        else:
            oldTradedVolume = order.tradedVolume
            if oldTradedVolume != float(data['filled-amount']):
                newTrade = True
        
        order.tradedVolume = float(data['filled-amount'])
        order.status = statusMapReverse.get(data['order-state'], STATUS_UNKNOWN)        
        
        self.gateway.onOrder(order)
        
        if newTrade:
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName

            trade.tradeID = data['seq-id']
            trade.vtTradeID = '.'.join([trade.tradeID, trade.gatewayName])

            trade.symbol = data['symbol']
            trade.exchange = EXCHANGE_HUOBI
            trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])

            if 'buy' in data['order-type']:
                trade.direction = DIRECTION_LONG
            else:
                trade.direction = DIRECTION_SHORT
            trade.offset = OFFSET_NONE

            trade.orderID = order.orderID
            trade.vtOrderID = order.vtOrderID
            
            trade.price = float(data['price'])
            trade.volume = order.tradedVolume - oldTradedVolume

            dt = datetime.fromtimestamp(d['created-at']/1000)
            trade.tradeTime = dt.strftime('%H:%M:%S')

            self.gateway.onTrade(trade)


########################################################################
class HuobiMarketWebsocketApi(HuobiWebsocketApiBase):
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """"""
        super(HuobiMarketWebsocketApi, self).__init__(gateway)
        
        self.reqID = 10000
        self.tickDict = {}
    
    #----------------------------------------------------------------------
    def connect(self, symbols, apiKey, apiSecret):
        """"""
        self.symbols = symbols
        
        super(HuobiMarketWebsocketApi, self).connect(apiKey, 
                                                     apiSecret,
                                                     WEBSOCKET_MARKET_HOST)
    
    #----------------------------------------------------------------------
    def onConnected(self):
        """"""
        self.subscribeTopic()
    
    #----------------------------------------------------------------------
    def subscribeTopic(self):  # type:()->None
        """
        """
        for symbol in self.symbols:
            # 创建Tick对象
            tick = VtTickData()
            tick.gatewayName = self.gatewayName
            tick.symbol = symbol
            tick.exchange = EXCHANGE_HUOBI
            tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            self.tickDict[symbol] = tick            
            
            # 订阅深度和成交
            self.reqID += 1
            req = {
                "sub": "market.%s.depth.step0" %symbol,
                "id": str(self.reqID)     
            }
            self.sendPacket(req)
            
            self.reqID += 1
            req = {
                "sub": "market.%s.detail" %symbol,
                "id": str(self.reqID)     
            }
            self.sendPacket(req)
    
    #----------------------------------------------------------------------
    def onData(self, packet):  # type: (dict)->None
        """"""
        if 'ch' in packet:
            if 'depth.step' in packet['ch']:
                self.onMarketDepth(packet)
            elif 'detail' in packet['ch']:
                self.onMarketDetail(packet)
        elif 'err-code' in packet:
            self.gateway.writeLog(u'错误代码：%s, 信息：%s' %(data['err-code'], data['err-msg']))
        
    #----------------------------------------------------------------------
    def onMarketDepth(self, data):
        """行情深度推送 """
        symbol = data['ch'].split('.')[1]

        tick = self.tickDict.get(symbol, None)
        if not tick:
            return

        tick.datetime = datetime.fromtimestamp(data['ts']/1000)
        tick.date = tick.datetime.strftime('%Y%m%d')
        tick.time = tick.datetime.strftime('%H:%M:%S.%f')

        bids = data['tick']['bids']
        for n in range(5):
            l = bids[n]
            tick.__setattr__('bidPrice' + str(n+1), float(l[0]))
            tick.__setattr__('bidVolume' + str(n+1), float(l[1]))

        asks = data['tick']['asks']
        for n in range(5):
            l = asks[n]
            tick.__setattr__('askPrice' + str(n+1), float(l[0]))
            tick.__setattr__('askVolume' + str(n+1), float(l[1]))

        if tick.lastPrice:
            newtick = copy(tick)
            self.gateway.onTick(newtick)

    #----------------------------------------------------------------------
    def onMarketDetail(self, data):
        """市场细节推送"""
        symbol = data['ch'].split('.')[1]

        tick = self.tickDict.get(symbol, None)
        if not tick:
            return

        tick.datetime = datetime.fromtimestamp(data['ts']/1000)
        tick.date = tick.datetime.strftime('%Y%m%d')
        tick.time = tick.datetime.strftime('%H:%M:%S.%f')

        t = data['tick']
        tick.openPrice = float(t['open'])
        tick.highPrice = float(t['high'])
        tick.lowPrice = float(t['low'])
        tick.lastPrice = float(t['close'])
        tick.volume = float(t['vol'])
        tick.preClosePrice = float(tick.openPrice)

        if tick.bidPrice1:
            newtick = copy(tick)
            self.gateway.onTick(newtick)