# encoding: UTF-8
import hashlib
import urllib


########################################################################
from vnpy.network.HttpClient import HttpClient


########################################################################
class OkexFutureHttpClient(HttpClient):
    
    #----------------------------------------------------------------------
    def __init__(self):
        super(OkexFutureHttpClient, self).__init__()
        self.apiKey = None
        self.apiSecret = None
    
    #----------------------------------------------------------------------
    # noinspection PyMethodOverriding
    def init(self, apiKey, apiSecret):
        # type: (str, str) -> any
        super(OkexFutureHttpClient, self).init('https://www.okex.com/api/v1')
        self.apiKey = apiKey
        self.apiSecret = apiSecret

#----------------------------------------------------------------------
    def beforeRequest(self, method, path, params, data):  # type: (str, str, dict, dict)->(str, str, dict, dict, dict)
        args = params or {}
        args.update(data or {})
        if 'sign' in args:
            args.pop('sign')
        if 'apiKey' not in args:
            args['api_key'] = self.apiKey
        data = urllib.urlencode(sorted(args.items()))
        data += "&secret_key=" + self.apiSecret
        
        sign = hashlib.md5(data.encode()).hexdigest().upper()
        data += "&sign=" + sign

        return method, path, params, data, {'Content-Type': 'application/x-www-form-urlencoded'}

