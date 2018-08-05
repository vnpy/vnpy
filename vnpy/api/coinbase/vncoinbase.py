# encoding: UTF-8

from __future__ import print_function

import hashlib
import hmac
import base64
import json
import ssl
import traceback

from queue import Queue, Empty
from multiprocessing.dummy import Pool
from time import time
from urlparse import urlparse
from copy import copy
from urllib import urlencode
from threading import Thread

from six.moves import input

import requests
import websocket


REST_HOST = 'https://api-public.sandbox.pro.coinbase.com'
WEBSOCKET_HOST = 'wss://ws-feed-public.sandbox.pro.coinbase.com'



########################################################################
class CoinbaseRestApi(object):
    """REST API"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''
        self.secretKey = ''
        self.passphrase = ''
        self.hmacKey = ''
        
        self.active = False
        self.reqid = 0
        self.queue = Queue()
        self.pool = None
        self.sessionDict = {}   # 会话对象字典
        
        self.header = {
            'Content-Type': 'Application/JSON'
        }
    
    #----------------------------------------------------------------------
    def init(self, apiKey, secretKey, passphrase):
        """初始化"""
        self.apiKey = apiKey
        self.secretKey = secretKey
        self.passphrase = passphrase
        
        self.hmacKey = base64.b64decode(self.secretKey)
        
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
        timestamp = str(time())
        
        if postdict:
            rq = requests.Request(url=url, data=json.dumps(postdict))
        else:
            rq = requests.Request(url=url)
        p = rq.prepare()
        
        header = copy(self.header)
        header['CB-ACCESS-KEY'] = self.apiKey
        header['CB-ACCESS-PASSPHRASE'] = self.passphrase
        header['CB-ACCESS-TIMESTAMP'] = timestamp
        header['CB-ACCESS-SIGN'] = self.generateSignature(method, path, timestamp, params, body=p.body)
        
        # 使用长连接的session，比短连接的耗时缩短80%
        session = self.sessionDict[i]
        if postdict:
            resp = session.request(method, url, headers=header, params=params, data=json.dumps(postdict))
        else:
            resp = session.request(method, url, headers=header, params=params)
        
        #resp = requests.request(method, url, headers=header, params=params, data=postdict)
        
        code = resp.status_code
        d = resp.json()
        
        if code == 200:
            callback(d, reqid)
        else:
            self.onError(code, d)    
    
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
    def generateSignature(self, method, path, timestamp, params=None, body=None):
        """生成签名"""
        # 对params在HTTP报文路径中，以请求字段方式序列化
        if params:
            query = urlencode(sorted(params.items()))
            path = path + '?' + query
        
        if body is None:
            body = ''
        
        msg = timestamp + method + path + body
        msg = msg.encode('ascii')
        signature = hmac.new(self.hmacKey, msg, hashlib.sha256)
        signature64 = base64.b64encode(signature.digest()).decode('utf-8')
        return signature64
    
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

    
########################################################################
class CoinbaseWebsocketApi(object):
    """Websocket API"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.ws = None
        self.thread = None
        self.active = False
    
    #----------------------------------------------------------------------
    def start(self):
        """启动"""
        self.ws = websocket.create_connection(WEBSOCKET_HOST,
                                              sslopt={'cert_reqs': ssl.CERT_NONE})
    
        self.active = True
        self.thread = Thread(target=self.run)
        self.thread.start()
        
        self.onConnect()
    
    #----------------------------------------------------------------------
    def reconnect(self):
        """重连"""
        self.ws = websocket.create_connection(WEBSOCKET_HOST,
                                              sslopt={'cert_reqs': ssl.CERT_NONE})   
        
        self.onConnect()
        
    #----------------------------------------------------------------------
    def run(self):
        """运行"""
        while self.active:
            try:
                stream = self.ws.recv()
                data = json.loads(stream)
                self.onData(data)
            except:
                msg = traceback.format_exc()
                self.onError(msg)
                self.reconnect()
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.active = False
        
        if self.thread:
            self.thread.join()
        
    #----------------------------------------------------------------------
    def onConnect(self):
        """连接回调"""
        print('connected')
    
    #----------------------------------------------------------------------
    def onData(self, data):
        """数据回调"""
        print('-' * 30)
        l = data.keys()
        l.sort()
        for k in l:
            print(k, data[k])
    
    #----------------------------------------------------------------------
    def onError(self, msg):
        """错误回调"""
        print(msg)
    
    #----------------------------------------------------------------------
    def sendReq(self, req):
        """发出请求"""
        self.ws.send(json.dumps(req))      





if __name__ == '__main__':
    API_KEY = '2982e190ce2785b862c36f7748ec6864'
    API_SECRET = 'sUXjm5HZKA+Dru9+dtekGF6DlfQnHvbQCs+DaTuOTSBFR+vvMIiWkpPTwHcfZwNapSRpFhjNerrb111hojazIA=='
    PASSPHRASE = 'vnpytesting'
    
    # REST测试
    rest = CoinbaseRestApi()
    rest.init(API_KEY, API_SECRET, PASSPHRASE)
    rest.start(1)
    
    #data = {
        #'symbol': 'XBTUSD'
    #}
    #rest.addReq('POST', '/position/isolate', rest.onData, postdict=data)
    
    rest.addReq('GET', '/orders', rest.onData, {'status': 'all'})
    
    ## WEBSOCKET测试
    #ws = CoinbaseWebsocketApi()
    #ws.start()
    
    #req = {
        #'type': 'subscribe',
        #"product_ids": [
            #"ETH-USD"
        #],
        #"channels": ['level2']        
    #}
    #ws.sendReq(req)
    
    #expires = int(time())
    #method = 'GET'
    #path = '/realtime'
    #msg = method + path + str(expires)
    #signature = hmac.new(API_SECRET, msg, digestmod=hashlib.sha256).hexdigest()
    
    #req = {
        #'op': 'authKey', 
        #'args': [API_KEY, expires, signature]
    #}    
    
    #ws.sendReq(req)
    
    #req = {"op": "subscribe", "args": ['order', 'execution', 'position', 'margin']}
    #req = {"op": "subscribe", "args": ['instrument']}
    #ws.sendReq(req)

    input()
