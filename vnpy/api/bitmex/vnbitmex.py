# encoding: UTF-8

from __future__ import print_function
import hashlib
import hmac
import json
import ssl
import traceback
import sys

from queue import Queue, Empty
from multiprocessing.dummy import Pool
from time import time,sleep
from datetime import datetime
import urllib.parse as urlparse
from copy import copy
from urllib.parse import urlencode
from threading import Thread
from collections import OrderedDict
from six.moves import input

import requests
import websocket


REST_HOST = 'https://www.bitmex.com/api/v1'
WEBSOCKET_HOST = 'wss://www.bitmex.com/realtime'

TESTNET_REST_HOST = 'https://testnet.bitmex.com/api/v1'
TESTNET_WEBSOCKET_HOST = 'wss://testnet.bitmex.com/realtime'


########################################################################
class BitmexRestApi(object):
    """REST API"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''
        self.apiSecret = ''
        self.host = ''
        
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
    def init(self, apiKey, apiSecret, testnet=False):
        """初始化"""
        self.apiKey = apiKey
        self.apiSecret = apiSecret
        
        if testnet:
            self.host = TESTNET_REST_HOST
        else:
            self.host = REST_HOST
        
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
        url = self.host + path
        expires = int(time() + 50)
        if params:
            params = OrderedDict(sorted(params.items()))
        rq = requests.Request(url=url, data=postdict)
        p = rq.prepare()
        
        header = copy(self.header)
        header['api-expires'] = str(expires)
        header['api-key'] = self.apiKey
        header['api-signature'] = self.generateSignature(method, path, expires, params, body=p.body)
        
        # 使用长连接的session，比短连接的耗时缩短80%
        session = self.sessionDict[i]
        print(u'url:{}'.format(url))
        print(u'header:{}'.format(header))
        print(u'params:{}'.format(params))

        resp = session.request(method, url, headers=header, params=params, data=postdict)
        
        #resp = requests.request(method, url, headers=header, params=params, data=postdict)
        
        code = resp.status_code
        d = resp.json()
        print('\nrequest:{} {}'.format(method,path))
        if code == 200:
            callback(d, reqid)
        else:
            self.onError(code, d)    
    
    #----------------------------------------------------------------------
    def run(self, i):
        """连续运行"""
        self.sessionDict[i] = requests.Session()
        
        while self.active:
            req = self.queue.get(timeout=1)
            try:
                self.processReq(req, i)
            except Exception as ex:
                print('processReq Exception:{},traceback:{}'.format(str(ex),traceback.format_exc()),file=sys.stderr)

    #----------------------------------------------------------------------
    def generateSignature(self, method, path, expires, params=None, body=None):
        """生成签名"""
        # 对params在HTTP报文路径中，以请求字段方式序列化
        if params:
            query = urlencode(sorted(params.items()))
            print('query:{}'.format(query))
            path = path + '?' + query
        
        if body is None:
            body = ''
        
        msg = method + '/api/v1' + path + str(expires) + body
        print('msg:{}'.format(msg))
        signature = hmac.new(self.apiSecret.encode('utf-8'), msg.encode('utf-8'),
                             digestmod=hashlib.sha256).hexdigest()
        print(signature)
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
        print(data)

    
########################################################################
class BitmexWebsocketApi(object):
    """Websocket API"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = None
        self.secretKey = None
        self.ws = None
        self.thread = None
        self.active = False
        self.host = ''
        self.trace = False
        self.connected = False
    #----------------------------------------------------------------------
    def reconnect(self):
        """重连"""
        self.connect()

    #----------------------------------------------------------------------
    def connect(self,apiKey, secretKey, testnet=False,trace=False):
        """"""
        self.apiKey = apiKey
        self.secretKey = secretKey
        if testnet:
            self.host = TESTNET_WEBSOCKET_HOST
        else:
            self.host = WEBSOCKET_HOST
        self.trace = trace

        try:
            websocket.enableTrace(trace)
            self.ws = websocket.WebSocketApp(self.host,
                                             on_message=self.onMessage,
                                             on_error=self.onError,
                                             on_close=self.onClose,
                                             on_open=self.onOpen)
            kwargs = {'sslopt': {'cert_reqs': ssl.CERT_NONE}}
            self.thread = Thread(target=self.ws.run_forever, kwargs=kwargs)
            self.thread.start()
        except Exception as ex:
            print(u'{} BitmexWebsocketApi connect exception :{},{}'.format(datetime.now(), str(ex), traceback.format_exc()),
                  file=sys.stderr)

    # ----------------------------------------------------------------------
    def close(self):
        """关闭接口"""
        if self.thread and self.thread.isAlive():
            self.ws.close()
            self.thread.join()

    # ----------------------------------------------------------------------
    def onClose(self):
        """关闭"""
        self.active = False
        
        if self.thread:
            self.thread.join()

    def onOpen(self,*args):
        print('websocket opened')
        self.connected = True

        #----------------------------------------------------------------------
    def onMessage(self, *args):
        """数据回调"""
        if len(args)==0:
            return
        data = json.loads(args[-1])
        print('-' * 30)
        l =sorted(data.keys())
        for k in l:
            print(k, data[k])
    
    #----------------------------------------------------------------------
    def onError(self, *args):
        """错误回调"""
        if len(args)==0:
            print('onError no args return',file=sys.stderr)
            return
        print(args[-1])
    
    #----------------------------------------------------------------------
    def sendReq(self, req):
        """发出请求"""
        if self.connected:
            self.ws.send(json.dumps(req))


if __name__ == '__main__':
    API_KEY = 'xxxx'
    API_SECRET = 'xxxx'
    
    ## REST测试
    rest = BitmexRestApi()
    rest.init(API_KEY, API_SECRET,testnet=True)
    rest.start(3)
    
    data = {
        'symbol': 'XBTUSD'
    }
    #print('rest: GET /user')
    #rest.addReq('GET','/user',rest.onData)

    #print('rest: GET /user/margin')
    #rest.addReq('GET', '/user/margin', rest.onData)

    #print('rest: GET /user/wallet')
    #rest.addReq('GET', '/user/wallet', rest.onData)

    #print('rest: GET /position')
    #rest.addReq('GET', '/position', rest.onData)

    #print('rest: POST /position/isolate')
    #rest.addReq('POST', '/position/isolate', rest.onData, postdict=data)

    #print('rest: GET /instrument')
    #rest.addReq('GET', '/instrument', rest.onData)

    print('rest: GET /trade/bucketed')
    rest.addReq('GET', '/trade/bucketed',rest.onData, params={'binSize':'1h','symbol':'XBTUSD'})

    input()
    exit(0)

    # WEBSOCKET测试
    ws = BitmexWebsocketApi()
    ws.connect(apiKey=API_KEY,secretKey=API_SECRET,testnet=True,trace=True)

    while(not ws.connected):
        print('waiting for websocket connected')
        sleep(1)

    req = {"op": "subscribe", "args": ['order', 'trade', 'position', 'margin']}
    ws.sendReq(req)
    
    expires = int(time())
    method = 'GET'
    path = '/realtime'
    msg = method + path + str(expires)
    signature = hmac.new(API_SECRET.encode('utf-8'), msg.encode('utf-8'), digestmod=hashlib.sha256).hexdigest()
    
    req = {
        'op': 'authKey',
        'args': [API_KEY, expires, signature]
    }

    ws.sendReq(req)

    req = {"op": "subscribe", "args": ['order', 'execution', 'position', 'margin']}
    req = {"op": "subscribe", "args": ['instrument']}
    ws.sendReq(req)

    input()
