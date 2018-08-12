# encoding: utf-8

from __future__ import print_function
import urllib
import hashlib
import ssl
import json
import traceback

import requests
from Queue import Queue, Empty
from threading import Thread
from multiprocessing.dummy import Pool
from time import time

import websocket



REST_HOST = "https://api.lbank.info/v1"
WEBSOCKET_HOST = 'ws://api.lbank.info/ws'



########################################################################
class LbankRestApi(object):
    """"""
    
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''
        self.secretKey = ''

        self.active = False         # API工作状态   
        self.reqID = 0              # 请求编号
        self.queue = Queue()        # 请求队列
        self.pool = None            # 线程池
        self.sessionDict = {}       # 连接池
        
    #----------------------------------------------------------------------
    def init(self, apiKey, secretKey):
        """初始化"""
        self.apiKey = apiKey
        self.secretKey = secretKey
        
    #----------------------------------------------------------------------
    def start(self, n=10):
        """"""
        if self.active:
            return
        
        self.active = True
        self.pool = Pool(n)
        self.pool.map_async(self.run, range(n))
        
    #----------------------------------------------------------------------
    def close(self):
        """退出"""
        self.active = False
        
        if self.pool:
            self.pool.close()
            self.pool.join()
    
    #----------------------------------------------------------------------
    def processReq(self, req, i):
        """处理请求"""
        # 读取方法和参数
        method, path, params, callback, reqID = req
        url = REST_HOST + path
        
        # 在参数中增加必须的字段
        params['api_key'] = self.apiKey
        params['sign'] = self.generateSignature(params)
        
        # 发送请求
        payload = urllib.urlencode(params)
        
        try:
            # 使用会话重用技术，请求延时降低80%
            session = self.sessionDict[i]
            resp = session.request(method, url, params=payload)
            #resp = requests.request(method, url, params=payload)
            
            code = resp.status_code
            d = resp.json()

            if code == 200:
                callback(d, reqID)
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
                req = self.queue.get(block=True, timeout=1)  # 获取请求的阻塞为一秒
                self.processReq(req, i)
            except Empty:
                pass    
            
    #----------------------------------------------------------------------
    def addReq(self, method, path, params, callback):
        """发送请求"""
        # 请求编号加1
        self.reqID += 1
        
        # 生成请求字典并放入队列中
        req = (method, path, params, callback, self.reqID)
        self.queue.put(req)
        
        # 返回请求编号
        return self.reqID

    #----------------------------------------------------------------------
    def generateSignature(self, params):
        """生成签名"""
        params = sorted(params.iteritems(), key=lambda d:d[0], reverse=False)
        params.append(('secret_key', self.secretKey))
        message = urllib.urlencode(params)
        
        m = hashlib.md5()
        m.update(message)
        m.digest()
    
        sig = m.hexdigest()
        return sig    

    #----------------------------------------------------------------------
    def onError(self, code, msg):
        """错误推送"""
        print(code, msg)

    #----------------------------------------------------------------------
    def onData(self, data, reqID):
        """"""
        print(data, reqID)


########################################################################
class LbankWebsocketApi(object):
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
                print(msg)                
                self.onError(msg)
                self.reconnect()
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.active = False
        
        if self.thread:
            self.ws.shutdown()
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


