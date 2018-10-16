# encoding: UTF-8
import hashlib
import urllib

from vnpy.api.rest import Request, RestClient
from vnpy.api.websocket import WebSocketClient


#----------------------------------------------------------------------
def sign(dataWithApiKey, apiSecret):
    """
    :param dataWithApiKey: sorted urlencoded args with apiKey
    :return: param 'sign' for okex api
    """
    dataWithSecret = dataWithApiKey + "&secret_key=" + apiSecret
    return hashlib.md5(dataWithSecret.encode()).hexdigest().upper()


########################################################################
class OkexFutureRestBase(RestClient):
    host = 'https://www.okex.com/api/v1'
    
    #----------------------------------------------------------------------
    def __init__(self):
        super(OkexFutureRestBase, self).__init__()
        self.apiKey = None
        self.apiSecret = None
    
    #----------------------------------------------------------------------
    # noinspection PyMethodOverriding
    def init(self, apiKey, apiSecret):
        # type: (str, str) -> any
        super(OkexFutureRestBase, self).init(self.host)
        self.apiKey = apiKey
        self.apiSecret = apiSecret

    #----------------------------------------------------------------------
    def beforeRequest(self, req):  # type: (Request)->Request
        args = req.params or {}
        args.update(req.data or {})
        if 'sign' in args:
            args.pop('sign')
        if 'apiKey' not in args:
            args['api_key'] = self.apiKey
        data = urllib.urlencode(sorted(args.items()))
        signature = sign(data, self.apiSecret)
        data += "&sign=" + signature

        req.headers = {'Content-Type': 'application/x-www-form-urlencoded'}
        req.data = data
        return req


########################################################################
class OkexFutureWebSocketBase(WebSocketClient):
    """
    Okex期货websocket客户端
    实例化后使用init设置apiKey和secretKey（apiSecret）
    """
    host = 'wss://real.okex.com:10440/websocket/okexapi'
    
    def __init__(self):
        super(OkexFutureWebSocketBase, self).__init__()
        super(OkexFutureWebSocketBase, self).init(OkexFutureWebSocketBase.host)
        self.apiKey = None
        self.apiSecret = None
    
    #----------------------------------------------------------------------
    # noinspection PyMethodOverriding
    def init(self, apiKey, secretKey):
        
        self.apiKey = apiKey
        self.apiSecret = secretKey
    
    #----------------------------------------------------------------------
    def sendPacket(self, dictObj, authenticate=False):
        if authenticate:
            data = urllib.urlencode(sorted(dictObj.items()))
            signature = sign(data, self.apiSecret)
            dictObj['sign'] = signature
        return super(OkexFutureWebSocketBase, self).sendPacket(dictObj)
