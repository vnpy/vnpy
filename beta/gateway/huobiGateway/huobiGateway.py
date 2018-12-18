# encoding: UTF-8

'''
'''

from __future__ import print_function

import base64
import hashlib
import hmac
import json
import re
import urllib
import zlib

from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.vtGateway import *

REST_HOST = 'https://api.huobipro.com'
WEBSOCKET_MARKET_HOST = 'wss://api.huobi.pro/ws'  # Global站行情
WEBSOCKET_ASSETS_HOST = 'wss://api.huobi.pro/ws/v1'  # 资产和订单
WEBSOCKET_CONTRACT_HOST = 'wss://www.hbdm.com/ws'  # 合约站行情


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
def createSignature(apiKey, method, host, path, secretKey):
    """创建签名"""
    sortedParams = (
        ("AccessKeyId", apiKey),
        ("SignatureMethod", 'HmacSHA256'),
        ("SignatureVersion", "2"),
        ("Timestamp", datetime.utcnow().strftime('%Y-%m-%dT%H:%M:%S'))
    )
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
class HuobiRestApi(RestClient):
    
    def __init__(self, gateway):  # type: (VtGateway)->HuobiRestApi
        super(HuobiRestApi, self).__init__()
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        
        self.apiKey = ""
        self.apiSecret = ""
        self.signHost = ""
    
    #----------------------------------------------------------------------
    def sign(self, request):
        request.headers = {
            "User-Agent":
                "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/39.0.2171.71 Safari/537.36"}
        additionalParams = createSignature(self.apiKey,
                                           request.method,
                                           self.signHost,
                                           request.path,
                                           self.apiSecret)
        if not request.params:
            request.params = additionalParams
        else:
            request.params.update(additionalParams)
        if request.method == "POST":
            request.headers['Content-Type'] = 'application/json'
        return request
    
    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, sessionCount=3):
        """连接服务器"""
        self.apiKey = apiKey
        self.apiSecret = apiSecret
        
        host, path = _split_url(REST_HOST)
        self.init(REST_HOST)
        self.signHost = host
        self.start(sessionCount)
    
    #----------------------------------------------------------------------
    def qeuryAccount(self):
        self.addRequest('GET', '/v1/account/accounts', self.onAccount)
    
    #----------------------------------------------------------------------
    def onAccount(self, data, request):  # type: (dict, Request)->None
        pass
    
    #----------------------------------------------------------------------
    def cancelWithdraw(self, id):
        self.addRequest('POST',
                        "/v1/dw/withdraw-virtual/" + str(id) + "/cancel",
                        self.onWithdrawCanceled
                        )

    #----------------------------------------------------------------------
    def onWithdrawCanceled(self, data, request):  # type: (dict, Request)->None
        pass


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
        pass
    
    #----------------------------------------------------------------------
    @staticmethod
    def unpackData(data):
        return json.loads(zlib.decompress(data, 31))
    
    #----------------------------------------------------------------------
    def onPacket(self, packet):
        """
        这里我新增了一个onHuobiPacket的函数，也可以让子类重写这个函数，然后调用super.onPacket
        """
        if 'ping' in packet:
            self.sendPacket({'pong': packet['ping']})
            return
        
        # todo: use another error handing method
        if 'err-msg' in packet:
            return self.onHuobiErrorPacket(packet)
        
        if "op" in packet and packet["op"] == "auth":
            return self.onLogin(packet)
        
        self.onHuobiPacket(packet)
    
    #----------------------------------------------------------------------
    def onHuobiPacket(self, packet):  # type: (dict)->None
        pass
    
    #----------------------------------------------------------------------
    def onHuobiErrorPacket(self, packet):  # type: (dict)->None
        print("error : {}".format(packet))


########################################################################
class HuobiAssetsWebsocketApi(HuobiWebsocketApiBase):
    
    def connect(self, apiKey, apiSecret, host=WEBSOCKET_ASSETS_HOST):
        """
        这里我使用重写connect，添加了默认参数。这样写感觉~~不太好~~，不过目前想到的比较好的方式就是这样了
        虽然在Python中可以直接把这个connect()写成不接收host和path的形式，但是PyCharm会提示重载错误，所以不接收host和path似乎不太好？
        
        我觉得最好的写法应该是这个函数不接收host和path。同时为了让PyCharm不提示重载错误(减少歧义)，应该给
        HuobiWebsocketApiBase.connect起另外一个名字。
        """
        return super(HuobiAssetsWebsocketApi, self). \
            connect(apiKey, apiSecret, host)
    
    #----------------------------------------------------------------------
    def onConnected(self):
        self.login()
    
    #----------------------------------------------------------------------
    def subscribeAccount(self):
        """
        :param symbol: str ethbtc, ltcbtc, etcbtc, bchbtc
        :param period: str 1min, 5min, 15min, 30min, 60min, 1day, 1mon, 1week, 1year
        """
        self.sendPacket({
            "op": "sub",
            "cid": "any thing you want",
            "topic": "accounts"
        })
    
    #----------------------------------------------------------------------
    def onHuobiPacket(self, packet):  # type: (dict)->None
        if 'op' in packet:
            if packet['op'] == 'sub':
                timestamp = packet['ts']
                topic = packet['topic']
                """
                  "data": {
    "event": "order.match|order.place|order.refund|order.cancel|order.fee-refund|margin.transfer|margin.loan|margin.interest|margin.repay|other",
    "list": [
      {
        "account-id": 419013,
        "currency": "usdt",
        "type": "trade",
        "balance": "500009195917.4362872650"
      },
      {
        "account-id": 419013,
        "currency": "btc",
        "type": "frozen",
        "balance": "9786.6783000000"
      }
    ]
  }
                """
                pass


########################################################################
class HuobiMarketWebsocketApi(HuobiWebsocketApiBase):
    
    #----------------------------------------------------------------------
    def connect(self, apiKey, apiSecret, host=WEBSOCKET_MARKET_HOST):
        """
        这里我使用重写connect，添加了默认参数。这样写感觉~~不太好~~，不过目前想到的比较好的方式就是这样了
        虽然在Python中可以直接把这个connect()写成不接收host和path的形式，但是PyCharm会提示重载错误，所以不接收host和path似乎不太好？
        
        我觉得最好的写法应该是这个函数不接收host和path。同时为了让PyCharm不提示重载错误(减少歧义)，应该给
        HuobiWebsocketApiBase.connect起另外一个名字。
        """
        return super(HuobiMarketWebsocketApi, self). \
            connect(apiKey, apiSecret, host)
    
    #----------------------------------------------------------------------
    def subscribeKLine(self, symbol, period):  # type:(str, str)->None
        """
        :param symbol: str ethbtc, ltcbtc, etcbtc, bchbtc
        :param period: str 1min, 5min, 15min, 30min, 60min, 1day, 1mon, 1week, 1year
        :return:
        """
        self.sendPacket({
            "sub": "market." + symbol + ".kline." + period,
            "id": "any thing you want"
        })
    
    #----------------------------------------------------------------------
    def onHuobiPacket(self, packet):  # type: (dict)->None
        # code for test purpose only
        if 'ch' in packet:
            if packet['ch'] == 'market.btcusdt.kline.1min':
                timestamp = packet['ts']
                data = packet['tick']
                id = data['id']
                amount = data['amount']
                count = data['count']
                open = data['open']
                close = data['close']
                low = data['low']
                high = data['high']
                vol = data['vol']
                pass
