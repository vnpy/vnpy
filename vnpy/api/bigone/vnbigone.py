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
from jwt import PyJWS
from six.moves import input

REST_HOST = 'https://big.one/api/v2/'




########################################################################
class BigoneRestApi(object):
    """REST API"""
    jws = PyJWS()

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
        
        header = {}
        header['Authorization'] = 'Bearer ' + self.generateSignature()

        try:
            # 使用长连接的session，比短连接的耗时缩短20%
            session = self.sessionDict[i]
            resp = session.request(method, url, headers=header, params=params, json=postdict)
            #resp = requests.request(method, url, headers=header, params=params, data=postdict)
            
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
    def generateSignature(self):
        """生成签名"""
        payload = '{"type":"OpenAPI","sub":"%s","nonce":%s}' %(self.apiKey, time()*1000000000)
        signature = self.jws.encode(payload, self.apiSecret)
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

    


if __name__ == '__main__':
    from datetime import datetime
    from time import sleep
    
    API_KEY = ''
    API_SECRET = ''
    
    # REST测试
    rest = BigoneRestApi()
    rest.init(API_KEY, API_SECRET)
    rest.start(1)
    
    #rest.addReq('GET', '/markets/EOS-BTC/depth', rest.onData)
    
    rest.addReq('GET', '/viewer/orders', rest.onData)
    

    input()
