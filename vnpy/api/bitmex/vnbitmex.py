# encoding: UTF-8

from __future__ import print_function
import hashlib
import hmac
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


REST_HOST = 'https://www.bitmex.com/api/v1'
WEBSOCKET_HOST = 'wss://www.bitmex.com/realtime'




########################################################################
class BitmexRestApi(object):
    """REST API"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''
        self.apiSecret = ''
        
        self.active = False
        self.reqid = 0
        self.queue = Queue()
        self.pool = None
        self.sessionDict = {}   # 会话对象字典
        
        self.header = {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Accept': 'application/json'
        }
    
    #----------------------------------------------------------------------
    def init(self, apiKey, apiSecret):
        """初始化"""
        self.apiKey = apiKey
        self.apiSecret = apiSecret
        
    #----------------------------------------------------------------------
    def start(self, n=3):
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
        expires = int(time() + 5) 
        
        rq = requests.Request(url=url, data=postdict)
        p = rq.prepare()
        
        header = copy(self.header)
        header['api-expires'] = str(expires)
        header['api-key'] = self.apiKey
        header['api-signature'] = self.generateSignature(method, path, expires, params, body=p.body)
        
        # 使用长连接的session，比短连接的耗时缩短80%
        session = self.sessionDict[i]
        resp = session.request(method, url, headers=header, params=params, data=postdict)
        
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
    def generateSignature(self, method, path, expires, params=None, body=None):
        """生成签名"""
        # 对params在HTTP报文路径中，以请求字段方式序列化
        if params:
            query = urlencode(sorted(params.items()))
            path = path + '?' + query
        
        if body is None:
            body = ''
        
        msg = method + '/api/v1' + path + str(expires) + body
        signature = hmac.new(self.apiSecret, msg,
                             digestmod=hashlib.sha256).hexdigest()
        return signature
    
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
class BitmexWebsocketApi(object):
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
    API_KEY = ''
    API_SECRET = ''
    
    ## REST测试
    rest = BitmexRestApi()
    rest.init(API_KEY, API_SECRET)
    rest.start(3)
    
    data = {
        'symbol': 'XBTUSD'
    }
    rest.addReq('POST', '/position/isolate', rest.onData, postdict=data)
    #rest.addReq('GET', '/instrument', rest.onData)
    
    # WEBSOCKET测试
    #ws = BitmexWebsocketApi()
    #ws.start()
    
    #req = {"op": "subscribe", "args": ['order', 'trade', 'position', 'margin']}
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
