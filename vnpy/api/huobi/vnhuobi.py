# encoding: utf-8

from __future__ import print_function

import base64
import hashlib
import hmac
import json
import ssl
import traceback
import urllib
import zlib
from copy import copy
from datetime import datetime
from multiprocessing.dummy import Pool
from queue import Empty, Queue
from threading import Thread
from time import sleep

import requests

from websocket import _exceptions, create_connection

# 常量定义
TIMEOUT = 10
HUOBI_API_HOST = "api.huobi.pro"
HADAX_API_HOST = "api.hadax.com"
LANG = 'zh-CN'

DEFAULT_GET_HEADERS = {
    "Content-type": "application/x-www-form-urlencoded",
    'Accept': 'application/json',
    'Accept-Language': LANG,
    'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0'
}

DEFAULT_POST_HEADERS = {
    'Content-Type': 'application/json',
    'Accept': 'application/json',
    'Accept-Language': LANG,
    'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0'    
}


#----------------------------------------------------------------------
def createSign(params, method, host, path, secretKey):
    """创建签名"""
    sortedParams = sorted(params.items(), key=lambda d: d[0], reverse=False)
    encodeParams = urllib.urlencode(sortedParams)
    
    payload = [method, host, path, encodeParams]
    payload = '\n'.join(payload)
    payload = payload.encode(encoding='UTF8')

    secretKey = secretKey.encode(encoding='UTF8')

    digest = hmac.new(secretKey, payload, digestmod=hashlib.sha256).digest()

    signature = base64.b64encode(digest)
    signature = signature.decode()
    return signature    


########################################################################
class TradeApi(object):
    """交易API"""
    HUOBI = 'huobi'
    HADAX = 'hadax'
    
    SYNC_MODE = 'sync'
    ASYNC_MODE = 'async'

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.accessKey = ''
        self.secretKey = ''
    
        self.mode = self.ASYNC_MODE
        self.active = False         # API工作状态   
        self.reqid = 0              # 请求编号
        self.queue = Queue()        # 请求队列
        self.pool = None            # 线程池
        
    #----------------------------------------------------------------------
    def init(self, host, accessKey, secretKey, mode=None):
        """初始化"""
        if host == self.HUOBI:
            self.hostname = HUOBI_API_HOST
        else:
            self.hostname = HADAX_API_HOST
        self.hosturl = 'https://%s' %self.hostname
            
        self.accessKey = accessKey
        self.secretKey = secretKey
        
        if mode:
            self.mode = mode
            
        self.proxies = {}
        
        return True
        
    #----------------------------------------------------------------------
    def start(self, n=10):
        """启动"""
        self.active = True
        
        if self.mode == self.ASYNC_MODE:
            self.pool = Pool(n)
            self.pool.map_async(self.run, range(n))
        
    #----------------------------------------------------------------------
    def close(self):
        """停止"""
        self.active = False
        self.pool.close()
        self.pool.join()
        
    #----------------------------------------------------------------------
    def httpGet(self, url, params):
        """HTTP GET"""        
        headers = copy(DEFAULT_GET_HEADERS)
        postdata = urllib.urlencode(params)
        
        try:
            response = requests.get(url, postdata, headers=headers, timeout=TIMEOUT)
            if response.status_code == 200:
                return True, response.json()
            else:
                return False, u'GET请求失败，状态代码：%s' %response.status_code
        except Exception as e:
            return False, u'GET请求触发异常，原因：%s' %e
    
    #----------------------------------------------------------------------    
    def httpPost(self, url, params, add_to_headers=None):
        """HTTP POST"""       
        headers = copy(DEFAULT_POST_HEADERS)
        postdata = json.dumps(params)
        
        try:
            response = requests.post(url, postdata, headers=headers, timeout=TIMEOUT)
            if response.status_code == 200:
                return True, response.json()
            else:
                return False, u'POST请求失败，返回信息：%s' %response.json()
        except Exception as e:
            return False, u'POST请求触发异常，原因：%s' %e
        
    #----------------------------------------------------------------------
    def generateSignParams(self):
        """生成签名参数"""
        timestamp = datetime.utcnow().strftime('%Y-%m-%dT%H:%M:%S')
        d = {
            'AccessKeyId': self.accessKey,
            'SignatureMethod': 'HmacSHA256',
            'SignatureVersion': '2',
            'Timestamp': timestamp
        }    
        
        return d
        
    #----------------------------------------------------------------------
    def apiGet(self, path, params):
        """API GET"""
        method = 'GET'
        
        params.update(self.generateSignParams())
        params['Signature'] = createSign(params, method, self.hostname, path, self.secretKey)
        
        url = self.hosturl + path
        
        return self.httpGet(url, params)
    
    #----------------------------------------------------------------------
    def apiPost(self, path, params):
        """API POST"""
        method = 'POST'
        
        signParams = self.generateSignParams()
        signParams['Signature'] = createSign(signParams, method, self.hostname, path, self.secretKey)
        
        url = self.hosturl + path + '?' + urllib.urlencode(signParams)

        return self.httpPost(url, params)
    
    #----------------------------------------------------------------------
    def addReq(self, path, params, func, callback):
        """添加请求"""       
        # 异步模式
        if self.mode == self.ASYNC_MODE:
            self.reqid += 1
            req = (path, params, func, callback, self.reqid)
            self.queue.put(req)
            return self.reqid
        # 同步模式
        else:
            return func(path, params)
    
    #----------------------------------------------------------------------
    def processReq(self, req):
        """处理请求"""
        path, params, func, callback, reqid = req
        result, data = func(path, params)
        
        if result:
            if data['status'] == 'ok':
                callback(data['data'], reqid)
            else:
                msg = u'错误代码：%s，错误信息：%s' %(data['err-code'], data['err-msg'])
                self.onError(msg, reqid)
        else:
            self.onError(data, reqid)
            
            # 失败的请求重新放回队列，等待下次处理
            self.queue.put(req)
    
    #----------------------------------------------------------------------
    def run(self, n):
        """连续运行"""
        while self.active:    
            try:
                req = self.queue.get(timeout=1)
                self.processReq(req)
            except Empty:
                pass
    
    #----------------------------------------------------------------------
    def getSymbols(self):
        """查询合约代码"""
        if self.hostname == HUOBI_API_HOST:
            path = '/v1/common/symbols'
        else:
            path = '/v1/hadax/common/symbols'

        params = {}
        func = self.apiGet
        callback = self.onGetSymbols
        
        return self.addReq(path, params, func, callback)
    
    #----------------------------------------------------------------------
    def getCurrencys(self):
        """查询支持货币"""
        if self.hostname == HUOBI_API_HOST:
            path = '/v1/common/currencys'
        else:
            path = '/v1/hadax/common/currencys'

        params = {}
        func = self.apiGet
        callback = self.onGetCurrencys
        
        return self.addReq(path, params, func, callback)   
    
    #----------------------------------------------------------------------
    def getTimestamp(self):
        """查询系统时间"""
        path = '/v1/common/timestamp'
        params = {}
        func = self.apiGet
        callback = self.onGetTimestamp
        
        return self.addReq(path, params, func, callback) 
    
    #----------------------------------------------------------------------
    def getAccounts(self):
        """查询账户"""
        path = '/v1/account/accounts'
        params = {}
        func = self.apiGet
        callback = self.onGetAccounts
    
        return self.addReq(path, params, func, callback)         
    
    #----------------------------------------------------------------------
    def getAccountBalance(self, accountid):
        """查询余额"""
        if self.hostname == HUOBI_API_HOST:
            path = '/v1/account/accounts/%s/balance' %accountid
        else:
            path = '/v1/hadax/account/accounts/%s/balance' %accountid
            
        params = {}
        func = self.apiGet
        callback = self.onGetAccountBalance
    
        return self.addReq(path, params, func, callback) 
    
    #----------------------------------------------------------------------
    def getOrders(self, symbol, states, types=None, startDate=None, 
                  endDate=None, from_=None, direct=None, size=None):
        """查询委托"""
        path = '/v1/order/orders'
        
        params = {
            'symbol': symbol,
            'states': states
        }
        
        if types:
            params['types'] = types
        if startDate:
            params['start-date'] = startDate
        if endDate:
            params['end-date'] = endDate        
        if from_:
            params['from'] = from_
        if direct:
            params['direct'] = direct
        if size:
            params['size'] = size        
    
        func = self.apiGet
        callback = self.onGetOrders
    
        return self.addReq(path, params, func, callback)     
    
    #----------------------------------------------------------------------
    def getMatchResults(self, symbol, types=None, startDate=None, 
                  endDate=None, from_=None, direct=None, size=None):
        """查询委托"""
        path = '/v1/order/matchresults'

        params = {
            'symbol': symbol
        }

        if types:
            params['types'] = types
        if startDate:
            params['start-date'] = startDate
        if endDate:
            params['end-date'] = endDate        
        if from_:
            params['from'] = from_
        if direct:
            params['direct'] = direct
        if size:
            params['size'] = size        

        func = self.apiGet
        callback = self.onGetMatchResults

        return self.addReq(path, params, func, callback)   
    
    #----------------------------------------------------------------------
    def getOrder(self, orderid):
        """查询某一委托"""
        path = '/v1/order/orders/%s' %orderid
    
        params = {}
    
        func = self.apiGet
        callback = self.onGetOrder
    
        return self.addReq(path, params, func, callback)             
    
    #----------------------------------------------------------------------
    def getMatchResult(self, orderid):
        """查询某一委托"""
        path = '/v1/order/orders/%s/matchresults' %orderid
    
        params = {}
    
        func = self.apiGet
        callback = self.onGetMatchResult
    
        return self.addReq(path, params, func, callback)     
    
    #----------------------------------------------------------------------
    def placeOrder(self, accountid, amount, symbol, type_, price=None, source=None):
        """下单"""
        if self.hostname == HUOBI_API_HOST:
            path = '/v1/order/orders/place'
        else:
            path = '/v1/hadax/order/orders/place'
        
        params = {
            'account-id': accountid,
            'amount': amount,
            'symbol': symbol,
            'type': type_
        }
        
        if price:
            params['price'] = price
        if source:
            params['source'] = source     

        func = self.apiPost
        callback = self.onPlaceOrder

        return self.addReq(path, params, func, callback)           
    
    #----------------------------------------------------------------------
    def cancelOrder(self, orderid):
        """撤单"""
        path = '/v1/order/orders/%s/submitcancel' %orderid
        
        params = {}
        
        func = self.apiPost
        callback = self.onCancelOrder

        return self.addReq(path, params, func, callback)          
    
    #----------------------------------------------------------------------
    def batchCancel(self, orderids):
        """批量撤单"""
        path = '/v1/order/orders/batchcancel'
    
        params = {
            'order-ids': orderids
        }
    
        func = self.apiPost
        callback = self.onBatchCancel
    
        return self.addReq(path, params, func, callback)     
        
    #----------------------------------------------------------------------
    def onError(self, msg, reqid):
        """错误回调"""
        print(msg, reqid)
        
    #----------------------------------------------------------------------
    def onGetSymbols(self, data, reqid):
        """查询代码回调"""
        #print reqid, data 
        for d in data:
            print(d)
    
    #----------------------------------------------------------------------
    def onGetCurrencys(self, data, reqid):
        """查询货币回调"""
        print(reqid, data)        
    
    #----------------------------------------------------------------------
    def onGetTimestamp(self, data, reqid):
        """查询时间回调"""
        print(reqid, data)    
        
    #----------------------------------------------------------------------
    def onGetAccounts(self, data, reqid):
        """查询账户回调"""
        print(reqid, data)     
    
    #----------------------------------------------------------------------
    def onGetAccountBalance(self, data, reqid):
        """查询余额回调"""
        print(reqid, data)
        for d in data['data']['list']:
            print(d)
        
    #----------------------------------------------------------------------
    def onGetOrders(self, data, reqid):
        """查询委托回调"""
        print(reqid, data)    
        
    #----------------------------------------------------------------------
    def onGetMatchResults(self, data, reqid):
        """查询成交回调"""
        print(reqid, data)      
        
    #----------------------------------------------------------------------
    def onGetOrder(self, data, reqid):
        """查询单一委托回调"""
        print(reqid, data)    
        
    #----------------------------------------------------------------------
    def onGetMatchResult(self, data, reqid):
        """查询单一成交回调"""
        print(reqid, data)    
        
    #----------------------------------------------------------------------
    def onPlaceOrder(self, data, reqid):
        """委托回调"""
        print(reqid, data)
    
    #----------------------------------------------------------------------
    def onCancelOrder(self, data, reqid):
        """撤单回调"""
        print(reqid, data)          
        
    #----------------------------------------------------------------------
    def onBatchCancel(self, data, reqid):
        """批量撤单回调"""
        print(reqid, data)      


########################################################################
class DataApi(object):
    """行情接口"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.ws = None
        self.url = ''
        
        self.reqid = 0
        self.active = False
        self.thread = Thread(target=self.run)
        
        self.subDict = {}
        
        self.url = ''
        
    #----------------------------------------------------------------------
    def run(self):
        """执行连接"""
        while self.active:
            try:
                stream = self.ws.recv()
                result = zlib.decompress(stream, 47).decode('utf-8')
                data = json.loads(result)
                self.onData(data)
            except zlib.error:
                self.onError(u'数据解压出错：%s' %stream)
            except:
                self.onError('行情服务器连接断开')
                result = self.reconnect()
                if not result:
                    self.onError(u'等待3秒后再次重连')
                    sleep(3)
                else:
                    self.onError(u'行情服务器重连成功')
                    self.resubscribe()
    
    #----------------------------------------------------------------------
    def reconnect(self):
        """重连"""
        try:
            self.ws = create_connection(self.url)
            return True
        except:
            msg = traceback.format_exc()
            self.onError(u'行情服务器重连失败：%s' %msg)            
            return False
        
    #----------------------------------------------------------------------
    def resubscribe(self):
        """重新订阅"""
        d = self.subDict
        self.subDict = {}
        for topic in d.keys():
            self.subTopic(topic)
        
    #----------------------------------------------------------------------
    def connect(self, url):
        """连接"""
        self.url = url
        
        try:
            self.ws = create_connection(self.url, sslopt={'cert_reqs': ssl.CERT_NONE})
            self.active = True
            self.thread.start()
            
            return True
        except:
            msg = traceback.format_exc()
            self.onError(u'行情服务器连接失败：%s' %msg)
            return False 
        
    #----------------------------------------------------------------------
    def close(self):
        """停止"""
        if self.active:
            self.active = False
            self.thread.join()
            self.ws.close()
        
    #----------------------------------------------------------------------
    def sendReq(self, req):
        """发送请求"""
        stream = json.dumps(req)
        self.ws.send(stream)            
        
    #----------------------------------------------------------------------
    def pong(self, data):
        """响应心跳"""
        req = {'pong': data['ping']}
        self.sendReq(req)
    
    #----------------------------------------------------------------------
    def subTopic(self, topic):
        """订阅主题"""
        if topic in self.subDict:
            return
        
        self.reqid += 1
        req = {
            'sub': topic,
            'id': str(self.reqid)
        }
        self.sendReq(req)
        
        self.subDict[topic] = str(self.reqid)
    
    #----------------------------------------------------------------------
    def unsubTopic(self, topic):
        """取消订阅主题"""
        if topic not in self.subDict:
            return
        req = {
            'unsub': topic,
            'id': self.subDict[topic]
        }
        self.sendReq(req)
        
        del self.subDict[topic]
    
    #----------------------------------------------------------------------
    def subscribeMarketDepth(self, symbol):
        """订阅行情深度"""
        topic = 'market.%s.depth.step0' %symbol
        self.subTopic(topic)
        
    #----------------------------------------------------------------------
    def subscribeTradeDetail(self, symbol):
        """订阅成交细节"""
        topic = 'market.%s.trade.detail' %symbol
        self.subTopic(topic)
        
    #----------------------------------------------------------------------
    def subscribeMarketDetail(self, symbol):
        """订阅市场细节"""
        topic = 'market.%s.detail' %symbol
        self.subTopic(topic)
        
    #----------------------------------------------------------------------
    def onError(self, msg):
        """错误推送"""
        print(msg)
        
    #----------------------------------------------------------------------
    def onData(self, data):
        """数据推送"""
        if 'ping' in data:
            self.pong(data)
        elif 'ch' in data:
            if 'depth.step' in data['ch']:
                self.onMarketDepth(data)
            elif 'trade.detail' in data['ch']:
                self.onTradeDetail(data)
            elif 'detail' in data['ch']:
                self.onMarketDetail(data)
        elif 'err-code' in data:
            self.onError(u'错误代码：%s, 信息：%s' %(data['err-code'], data['err-msg']))
    
    #----------------------------------------------------------------------
    def onMarketDepth(self, data):
        """行情深度推送 """
        print(data)
    
    #----------------------------------------------------------------------
    def onTradeDetail(self, data):
        """成交细节推送"""
        print(data)
    
    #----------------------------------------------------------------------
    def onMarketDetail(self, data):
        """市场细节推送"""
        print(data)
