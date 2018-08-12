# encoding: UTF-8
import base64
import hashlib
import hmac
import urllib
from multiprocessing.dummy import Pool
from time import time

import requests
from six.moves import input
from queue import Queue, Empty

REST_HOST = 'https://api.bithumb.com'


########################################################################
class BithumbRestApi(object):

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''
        self.apiSecret = ''

        self.active = False
        self.reqid = 0
        self.queue = Queue()
        self.pool = None  # type: Pool
        self.sessionDict = {}

    #----------------------------------------------------------------------
    def init(self, apiKey, apiSecret):
        """初始化"""
        self.apiKey = str(apiKey)
        self.apiSecret = str(apiSecret)

    #----------------------------------------------------------------------
    def start(self, n=10):
        """启动"""
        if self.active:
            return

        self.active = True
        self.pool = Pool(n)
        self.pool.map_async(self.run, range(n))

    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.active = False

        if self.pool:
            self.pool.close()
            self.pool.join()

    #----------------------------------------------------------------------
    def addReq(self, method, path, callback, params=None, postdict=None):
        """添加请求"""
        self.reqid += 1
        req = (method, path, callback, params, postdict, self.reqid)
        self.queue.put(req)
        return self.reqid

    def processReq(self, req, i):
        """处理请求"""
        method, path, callback, params, postdict, reqid = req
        url = REST_HOST + path

        body = ''
        header = {}

        # 如果调用的是需要签名的API，则加上签名
        # 不是以/public/开头的API都需要签名
        if path[:8] != '/public/':
            nonce = BithumbRestApi.generateNonce()

            # 如果有参数，使用urlencode编码参数
            body = urllib.urlencode(postdict) if postdict else ''

            # 加上签名
            header = {
                'Api-Key': self.apiKey,
                'Api-Sign': self.generateSignature(path, body, nonce),
                'Api-Nonce': nonce,
                'Content-Type': 'application/x-www-form-urlencoded'
            }

        try:
            # 使用长连接的session，比短连接的耗时缩短20%
            session = self.sessionDict[i]
            resp = session.request(method, url, headers=header, params=params, data=body)

            code = resp.status_code
            d = resp.json()

            if code == 200:
                callback(d, reqid)
            else:
                self.onError(code, str(d))
        except Exception as e:
            self.onError(type(e), e.message)

    #----------------------------------------------------------------------
    def run(self, i):
        """连续运行"""
        self.sessionDict[i] = requests.Session()

        while self.active:
            try:
                req = self.queue.get(timeout=1)
                self.processReq(req, i)
            except Empty:
                pass

    #----------------------------------------------------------------------
    def generateSignature(self, path, body, nonce):
        """生成签名"""
        # 要签名的数据包括path，body和nonce，用\x00隔开
        data = path + chr(0) + body + chr(0) + nonce

        # 签名的核心方法：hmac-sha512
        # 签名流程：base64(hex(hmac-sha512(要签名的数据)))
        return base64.b64encode(hmac.new(bytes(self.apiSecret), data, hashlib.sha512).hexdigest())

    #----------------------------------------------------------------------
    def onError(self, code, error):
        """错误回调"""
        print('on error')
        print(code, error)

    #----------------------------------------------------------------------
    def onData(self, data, reqid):
        """通用回调"""
        print('on data')
        print(data, reqid)

    #----------------------------------------------------------------------
    @staticmethod  # 静态函数:不依赖于self的函数
    def generateNonce():
        """生成时间戳"""
        return str(int(time() * 1000))


if __name__ == '__main__':
    API_KEY = '0c2f5621ac18d26d51ce640b25eb44f9'
    API_SECRET = '62bb8b4e263476f443f8d3dbf0aad6bc'

    rest = BithumbRestApi()
    rest.init(apiKey=API_KEY, apiSecret=API_SECRET)
    rest.start(1)


    def onBtcTick(jsonObj, reqid):
        print('on_btc_tick : \n{}'.format(jsonObj))
        pass


    def onAccountInfo(jsonObj, reqid):
        print('on_account_info : \n{}'.format(jsonObj))
        pass


    rest.addReq('POST', '/public/ticker/BTC', onBtcTick)
    rest.addReq('POST', '/info/account', onAccountInfo, postdict={'currency': 'BTC'})

    input()
