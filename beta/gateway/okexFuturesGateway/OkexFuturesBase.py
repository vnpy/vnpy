# encoding: UTF-8
import base64
import hashlib
import hmac
import json
import urllib

import time

from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebsocketClient


#----------------------------------------------------------------------
def paramsToDataV1(params):
    return urllib.urlencode(sorted(params.items()))


#----------------------------------------------------------------------
def signV1(dataWithApiKey, apiSecret):
    """
    usage:
    params = { ... , 'api_key': ...}
    data = paramsToData(params)
    signature = sign(data, apiSecret)
    data += "&sign" + signature

    :param dataWithApiKey: sorted urlencoded args with apiKey
    :return: param 'sign' for okex api
    """
    dataWithSecret = dataWithApiKey + "&secret_key=" + apiSecret
    return hashlib.md5(dataWithSecret.encode()).hexdigest().upper()


#----------------------------------------------------------------------
def signV3(dataToSign, apiSecret):
    return base64.b64encode( hmac.new(apiSecret, dataToSign.encode(), hashlib.sha256).digest())


########################################################################
class OkexFuturesRestBaseV1(RestClient):
    host = 'https://www.okex.com/api/v1'

    #----------------------------------------------------------------------
    def __init__(self):
        super(OkexFuturesRestBaseV1, self).__init__()
        self.apiKey = None
        self.apiSecret = None

    #----------------------------------------------------------------------
    # noinspection PyMethodOverriding
    def init(self, apiKey, apiSecret, apiPassphrase):
        # type: (str, str, str) -> any
        super(OkexFuturesRestBaseV1, self).init(self.host)
        self.apiKey = apiKey
        self.apiSecret = apiSecret

    #----------------------------------------------------------------------
    def sign(self, request):  # type: (Request)->Request
        args = request.params or {}
        args.update(request.data or {})
        if 'sign' in args:
            args.pop('sign')
        if 'apiKey' not in args:
            args['api_key'] = self.apiKey
        data = paramsToDataV1(args)
        signature = signV1(data, self.apiSecret)
        data += "&sign=" + signature

        request.headers = {'Content-Type': 'application/x-www-form-urlencoded'}
        request.data = data
        return request


########################################################################
class OkexFuturesRestBaseV3(RestClient):
    """
    Okex Rest API v3基础类
    """
    host = 'https://www.okex.com'

    #----------------------------------------------------------------------
    def __init__(self):
        super(OkexFuturesRestBaseV3, self).__init__()
        self.apiKey = None
        self.apiSecret = None
        self.apiPassphrase = None

    #----------------------------------------------------------------------
    # noinspection PyMethodOverriding
    def init(self, apiKey, apiSecret, apiPassphrase):
        # type: (str, str, str) -> any
        super(OkexFuturesRestBaseV3, self).init(self.host)
        self.apiKey = apiKey
        self.apiSecret = apiSecret
        self.apiPassphrase = apiPassphrase

    #----------------------------------------------------------------------
    def sign(self, request):  # type: (Request)->Request
        timestamp = str(time.time())

        data = json.dumps(request.data)
        request.data = data
        dataToSign = timestamp + request.method + request.path + data

        signature = signV3(dataToSign, self.apiSecret)

        request.headers = {
            'OK-ACCESS-KEY': self.apiKey,
            'OK-ACCESS-SIGN': signature,
            'OK-ACCESS-TIMESTAMP': timestamp,
            'OK-ACCESS-PASSPHRASE': self.apiPassphrase,
            'Content-Type': 'application/json'
        }
        return request


########################################################################
class OkexFuturesWebSocketBase(WebsocketClient):
    """
    Okex期货websocket客户端
    实例化后使用init设置apiKey和secretKey（apiSecret）
    """
    host = 'wss://real.okex.com:10440/websocket/okexapi?compress=true'

    def __init__(self):
        super(OkexFuturesWebSocketBase, self).__init__()
        super(OkexFuturesWebSocketBase, self).init(OkexFuturesWebSocketBase.host)
        self.apiKey = None
        self.apiSecret = None
        self.apiPassphrase = None

        self.autoLogin = True

        self.onConnected = self._onConnected

    #----------------------------------------------------------------------
    # noinspection PyMethodOverriding
    def init(self, apiKey, secretKey, apiPassphrase, autoLogin=True):

        self.apiKey = apiKey
        self.apiSecret = secretKey
        self.apiPassphrase = apiPassphrase
        self.autoLogin = autoLogin

    #----------------------------------------------------------------------
    def sendPacket(self, dictObj, authenticate=False):
        if authenticate:
            pass
        return super(OkexFuturesWebSocketBase, self).sendPacket(dictObj)

    #----------------------------------------------------------------------
    def _login(self, ):
        timestamp = str(time.time())

        data = timestamp + 'GET' + '/users/self/verify'
        signature = signV3(data, self.apiSecret)

        self.sendPacket({
            "event": "login",
            "parameters": {
                "api_key": self.apiKey,
                "timestamp": timestamp,
                "passphrase": self.apiPassphrase,
                "sign": signature,
            }
        }, authenticate=False)

    #----------------------------------------------------------------------
    def _onConnected(self):
        if self.autoLogin:
            self._login()
