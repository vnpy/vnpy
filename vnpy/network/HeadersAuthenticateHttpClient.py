# encoding: UTF-8


########################################################################
from abc import abstractmethod

from vnpy.network.HttpClient import HttpClient


########################################################################
class HeadersAuthenticateHttpClient(HttpClient):
    """
    该类简化了RESTFulAPI客户端的重载。
    该类提供了一个setUser函数，可以方便地设置apiKey和apiSecret。
    使用self.apiKey和self.apiSecret便可以访问设置后的值
    要建立一个签名在HTTP Headers的RESTFul客户端，继承该类并重载authencitate即可。
    """
    
    #----------------------------------------------------------------------
    def __init__(self):
        super(HeadersAuthenticateHttpClient, self).__init__()
        self.apiKey = None  # type: str
        self.apiSecret = None  # type: str
    
    #----------------------------------------------------------------------
    def beforeRequest(self, method, path, params, data):  # type: (str, str, dict, dict)->(str, str, dict, dict, dict)
        return method, path, params, data, self.onAuthenticate(method, path, params, data)
    
    #----------------------------------------------------------------------
    @abstractmethod
    def onAuthenticate(self, method, path, params, data):
        """
        重载该函数以添加签名到头部
        该函数在每个请求之前都会被调用。
        @:return dict  返回的数据会被加入到HTTP请求头部中
        
        """
        return {}
