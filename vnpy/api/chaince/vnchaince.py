# encoding: UTF-8

from __future__ import print_function
import requests

from queue import Queue, Empty
from multiprocessing.dummy import Pool
from time import time
from jwt import PyJWS
from .edalgorithm import EDAlgorithm

REST_HOST = 'https://api.chaince.com'

class ChainceRestApi(object):
    """"""
    jws = PyJWS()

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.jws.register_algorithm('Ed25519', EDAlgorithm())

        self.apiKey = ''
        self.secretKey = ''

        self.active = False
        self.reqid = 0
        self.queue = Queue()
        self.pool = None
        self.sessionDict = {}

    #----------------------------------------------------------------------
    def init(self, apiKey, secretKey):
        """初始化"""
        self.apiKey = str(apiKey)
        self.secretKey = str(secretKey)

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

    #----------------------------------------------------------------------
    def processReq(self, req, i):
        """处理请求"""
        method, path, callback, params, postdict, reqid = req
        url = REST_HOST + path

        header = {'Authorization': 'Bearer %s' % self.generateSignature()}

        try:
            # 使用长连接的session，比短连接的耗时缩短20%
            resp = self.sessionDict[i].request(method, url, headers=header, params=params, json=postdict)

            code = resp.status_code
            d = resp.json()

            if code == 200:
                callback(d, req)
            else:
                self.onError(code, str(d))
        except Exception as e:
            self.onError(type(e), e.message)

    #----------------------------------------------------------------------
    def run(self, i):
        """连续运行"""
        s = requests.session()
        s.keep_alive = False
        self.sessionDict[i] = s

        while self.active:
            try:
                req = self.queue.get(timeout=1)
                self.processReq(req, i)
            except Empty:
                pass

    #----------------------------------------------------------------------
    def generateSignature(self):
        """生成签名"""
        payload = '{"key": "%s", "iat": %s}' % (self.apiKey, int(time() + 10000))
        signature = self.jws.encode(payload, self.secretKey, algorithm='Ed25519')
        return signature

    #----------------------------------------------------------------------
    def onError(self, code, error):
        """错误回调"""
        print('on error')
        print(code, error)

    #----------------------------------------------------------------------
    def onData(self, data, req):
        """通用回调"""
        print('on %s' % req[1])
        print(data, req[5])


if __name__ == '__main__':
    from six.moves import input

    apiKey = ''
    secretKey = ''

    # REST测试
    rest = ChainceRestApi()
    rest.init(apiKey, secretKey)
    rest.start(1)

    rest.addReq('GET', '/orders/ceteos/today', rest.onData)

    input()
