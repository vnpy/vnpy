# encoding: UTF-8

from __future__ import print_function
import hashlib
import hmac
import json
import ssl
import traceback
import base64

from queue import Queue, Empty
from multiprocessing.dummy import Pool
from time import time
from urlparse import urlparse
from copy import copy
from urllib import urlencode
from threading import Thread

import requests
import websocket
from six.moves import input


REST_HOST = 'https://api.fcoin.com/v2'
WEBSOCKET_HOST = 'wss://api.fcoin.com/v2/ws'




########################################################################
class FcoinRestApi(object):
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
    
    #----------------------------------------------------------------------
    def processReq(self, req, i):
        """处理请求"""
        method, path, callback, params, postdict, reqid = req
        url = REST_HOST + path
        timestamp = str(int(time()) * 1000) 
        
        header = {}
        header['FC-ACCESS-TIMESTAMP'] = timestamp
        header['FC-ACCESS-KEY'] = self.apiKey
        header['FC-ACCESS-SIGNATURE'] = self.generateSignature(method, url, timestamp, params, postdict)
        
        try:
            # 使用长连接的session，比短连接的耗时缩短80%
            session = self.sessionDict[i]
            resp = session.request(method, url, headers=header, params=params, json=postdict)
            #resp = requests.request(method, url, headers=header, params=params, data=postdict)
            
            #if method != 'GET':
                #print '-' * 30
                #print 'method', method
                #print 'url', url
                #print 'header', header
                #print 'params', params
                #print 'postdict', postdict        
            
            code = resp.status_code
            d = resp.json()
            
            if code == 200:
                callback(d, reqid)
            else:
                self.onError(code, d)    
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
    def generateSignature(self, method, path, timestamp, params=None, postdict=None):
        """生成签名"""
        # 对params在HTTP报文路径中，以请求字段方式序列化
        if params:
            query = urlencode(sorted(params.items()))
            path = path + '?' + query
        
        if postdict:
            post = urlencode(sorted(postdict.items()))
        else:
            post = ''
        
        msg = method + path + timestamp + post
        msg = base64.b64encode(msg)
        
        signature = hmac.new(self.apiSecret, msg, digestmod=hashlib.sha1).digest()
        signature = base64.b64encode(signature)
        
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
class FcoinWebsocketApi(object):
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
    from datetime import datetime
    from time import sleep
    
    API_KEY = '88893f839fbd49f4b5fcb03e7c15c015'
    API_SECRET = 'ef383295cf4e4c128e6d18d7e9564b12'
    
    # REST测试
    rest = FcoinRestApi()
    rest.init(API_KEY, API_SECRET)
    rest.start(3)
       
    #rest.addReq('GET', '/accounts/balance', rest.onData)
    
    # 查委托
    #states = ['submitted', 'partial_filled', 'partial_canceled', 
              #'filled', 'canceled', 'pending_cancel']    
    #req = {
        #'symbol': 'ethusdt',
        #'start': datetime.now().strftime('%Y%m%d'),
        #'states': 'submitted',
        #'limit': 500        
    #}
    
    #for i in range(10):
        #rest.addReq('GET', '/orders', rest.onData, params=req)
        #sleep(2)
        
    req = {
        'symbol': 'ethusdt',
        'side': 'buy',
        'type': 'limit',
        'price': 300,
        'amount': 0.01
    }    
    rest.addReq('POST', '/orders', rest.onData, postdict=req)
    #sleep(1)
    #rest.addReq('POST', '/orders', rest.onData, params=req)

    ## WS测试
    #ws = FcoinWebsocketApi()
    #ws.start()
    
    #req = {
        #'cmd': 'sub',
        #'args': ['depth.L20.btcusdt'],
        #'id': 1
    #}
    
    #ws.sendReq(req)

    input()
    
    
