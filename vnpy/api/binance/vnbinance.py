# encoding: UTF-8

from __future__ import print_function
import json
import requests
import hmac
import hashlib
import traceback
import ssl

from queue import Queue, Empty
from threading import Thread
from multiprocessing.dummy import Pool
from time import time, sleep
from urllib import urlencode

from websocket import create_connection



REST_ENDPOINT = 'https://www.binance.com'
DATASTREAM_ENDPOINT = 'wss://stream.binance.com:9443/stream?streams='
USERSTREAM_ENDPOINT = 'wss://stream.binance.com:9443/ws/'



########################################################################
class BinanceApi(object):
    """"""
    
    ###################################################
    ## Basic Function
    ###################################################

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''
        self.secretKey = ''
        
        self.active = False
        self.reqid = 0
        self.queue = Queue()
        self.pool = None
        
        self.headers = {}
        self.secret = ''
        self.recvWindow = 5000
        
        self.dataStreamNameList = []
        self.dataStreamUrl = ''
        self.dataStreamActive = False
        self.dataStreamWs = None
        self.dataStreamThread = None
        
        self.userStreamKey = ''
        self.userStreamUrl = ''
        self.userStreamActive = False
        self.userStreamWs = None
        self.userStreamThread = None   
        
        self.keepaliveCount = 0
        self.keepaliveThread = None
        
    #----------------------------------------------------------------------
    def init(self, apiKey, secretKey, recvWindow=5000):
        """"""
        self.apiKey = apiKey
        self.secretKey = secretKey
        
        self.headers['X-MBX-APIKEY'] = apiKey
        self.secret = bytes(secretKey.encode('utf-8'))
        self.recvWindow = recvWindow
    
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
        """"""
        self.active = False
        
        if self.pool:
            self.pool.close()
            self.pool.join()
    
    #----------------------------------------------------------------------
    def request(self, method, path, params=None, signed=False, stream=False):
        """"""
        if not signed:
            url = REST_ENDPOINT + path
            headers = {}            
        else:
            if not stream:
                params['recvWindow'] = self.recvWindow
                params['timestamp'] = int(time()*1000)
                query = urlencode(sorted(params.items()))
                
                signature = hmac.new(self.secret, query.encode('utf-8'),
                                     hashlib.sha256).hexdigest()
                query += "&signature={}".format(signature)
                
                url = REST_ENDPOINT + path + '?' + query
                params = None       # 参数添加到query中后，清空参数字典
            else:
                if params:
                    query = urlencode(sorted(params.items()))
                    url = REST_ENDPOINT + path + '?' + query
                    params = None
                else:
                    url = REST_ENDPOINT + path
            
            headers = self.headers
        
        try:
            resp = requests.request(method, url, params=params, headers=headers)
            
            if resp.status_code == 200:
                return True, resp.json()
            else:
                error = {
                    'method': method,
                    'params': params,
                    'code': resp.status_code,
                    'msg': resp.json()['msg']
                }
                return False, error
        except Exception as e:
            error = {
                'method': method,
                'params': params,
                'code': e,
                'msg': traceback.format_exc()
            }            
            return False, error
    
    #----------------------------------------------------------------------
    def addReq(self, method, path, params, callback, signed=False, stream=False):
        """添加请求"""       
        self.reqid += 1
        req = (method, path, params, callback, signed, stream, self.reqid)
        self.queue.put(req)
        return self.reqid
        
    #----------------------------------------------------------------------
    def processReq(self, req):
        """"""
        method, path, params, callback, signed, stream, reqid = req
        result, data = self.request(method, path, params, signed, stream)
        
        if result:
            callback(data, reqid)
        else:
            self.onError(data, reqid)
    
    #----------------------------------------------------------------------
    def run(self, n):
        """"""
        while self.active:    
            try:
                req = self.queue.get(timeout=1)
                self.processReq(req)
            except Empty:
                pass        
    
    ###################################################
    ## REST Function
    ###################################################
    
    #----------------------------------------------------------------------
    def queryPing(self):
        """"""
        path = '/api/v1/ping'
        return self.addReq('GET', path, {}, self.onQueryPing)
    
    #----------------------------------------------------------------------
    def queryTime(self):
        """"""
        path = '/api/v1/time'
        return self.addReq('GET', path, {}, self.onQueryTime)
    
    #----------------------------------------------------------------------
    def queryExchangeInfo(self):
        """"""
        path = '/api/v1/exchangeInfo'
        return self.addReq('GET', path, {}, self.onQueryExchangeInfo)  
    
    #----------------------------------------------------------------------
    def queryDepth(self, symbol, limit=0):
        """"""
        path = '/api/v1/depth'
        params = {'symbol': symbol}
        if limit:
            params['limit'] = limit
        return self.addReq('GET', path, params, self.onQueryDepth)
    
    #----------------------------------------------------------------------
    def queryTrades(self, symbol, limit=0):
        """"""
        path = '/api/v1/trades'
        params = {'symbol': symbol}
        if limit:
            params['limit'] = limit
        return self.addReq('GET', path, params, self.onQueryTrades)  

    #----------------------------------------------------------------------
    def queryAggTrades(self, symbol, fromId=0, startTime=0, endTime=0, limit=0):
        """"""
        path = '/api/v1/aggTrades'
        
        params = {'symbol': symbol}
        if fromId:
            params['fromId'] = fromId
        if startTime:
            params['startTime'] = startTime
        if endTime:
            params['endTime'] = endTime
        if limit:
            params['limit'] = limit
        
        return self.addReq('GET', path, params, self.onQueryAggTrades)  
    
    #----------------------------------------------------------------------
    def queryKlines(self, symbol, interval, limit=0, startTime=0, endTime=0):
        """"""
        path = '/api/v1/klines'
        
        params = {
            'symbol': symbol,
            'interval': interval
        }
        if limit:
            params['limit'] = limit        
        if startTime:
            params['startTime'] = startTime
        if endTime:
            params['endTime'] = endTime
        
        return self.addReq('GET', path, params, self.onQueryKlines)  
    
    #----------------------------------------------------------------------
    def queryTicker24HR(self, symbol=''):
        """"""
        path = '/api/v1/ticker/24hr'
        params = {}
        if symbol:
            params['symbol'] = symbol
        return self.addReq('GET', path, params, self.onQueryTicker24HR)   
    
    #----------------------------------------------------------------------
    def queryTickerPrice(self, symbol=''):
        """"""
        path = '/api/v3/ticker/price'
        params = {}
        if symbol:
            params['symbol'] = symbol
        return self.addReq('GET', path, params, self.onQueryTickerPrice)  
    
    #----------------------------------------------------------------------
    def queryBookTicker(self, symbol=''):
        """"""
        path = '/api/v3/ticker/bookTicker'
        params = {}
        if symbol:
            params['symbol'] = symbol
        return self.addReq('GET', path, params, self.onQueryBookTicker)  

    #----------------------------------------------------------------------
    def newOrder(self, symbol, side, type_, price, quantity, timeInForce, 
                 newClientOrderId='', stopPrice=0, icebergQty=0, newOrderRespType=''):
        """"""
        path = '/api/v3/order'
        
        params = {
            'symbol': symbol,
            'side': side,
            'type': type_,
            'price': price,
            'quantity': quantity,
            'timeInForce': timeInForce
        }
        if newClientOrderId:
            params['newClientOrderId'] = newClientOrderId
        if timeInForce:
            params['timeInForce'] = timeInForce
        if stopPrice:
            params['stopPrice'] = stopPrice
        if icebergQty:
            params['icebergQty'] = icebergQty
        if newOrderRespType:
            params['newOrderRespType'] = newOrderRespType
            
        return self.addReq('POST', path, params, self.onNewOrder, signed=True)
        
    #----------------------------------------------------------------------
    def queryOrder(self, symbol, orderId=0, origClientOrderId=0):
        """"""
        path = '/api/v3/order'
        params = {'symbol': symbol}
        if orderId:
            params['orderId'] = orderId
        if origClientOrderId:
            params['origClientOrderId'] = origClientOrderId
        return self.addReq('GET', path, params, self.onQueryOrder, signed=True)
    
    #----------------------------------------------------------------------
    def cancelOrder(self, symbol, orderId=0, origClientOrderId='',
                    newClientOrderId=''):
        """"""
        path = '/api/v3/order'
        params = {'symbol': symbol}
        if orderId:
            params['orderId'] = orderId
        if origClientOrderId:
            params['origClientOrderId'] = origClientOrderId
        if newClientOrderId:
            params['newClientOrderId'] = newClientOrderId
        return self.addReq('DELETE', path, params, self.onCancelOrder, signed=True)        
    
    #----------------------------------------------------------------------
    def queryOpenOrders(self, symbol=''):
        """"""
        path = '/api/v3/openOrders'
        params = {}
        if symbol:
            params['symbol'] = symbol
        return self.addReq('GET', path, params, self.onQueryOpenOrders, signed=True)          
    
    #----------------------------------------------------------------------
    def queryAllOrders(self, symbol, orderId=0, limit=0):
        """"""
        path = '/api/v3/allOrders'
        params = {'symbol': symbol}
        if orderId:
            params['orderId'] = orderId
        if limit:
            params['limit'] = limit
        return self.addReq('GET', path, params, self.onQueryAllOrders, signed=True)  
    
    #----------------------------------------------------------------------
    def queryAccount(self):
        """"""
        path = '/api/v3/account'
        params = {}
        return self.addReq('GET', path, params, self.onQueryAccount, signed=True)
    
    #----------------------------------------------------------------------
    def queryMyTrades(self, symbol, limit=0, fromId=0):
        """"""
        path = '/api/v3/myTrades'
        params = {'symbol': symbol}
        if limit:
            params['limit'] = limit
        if fromId:
            params['fromId'] = fromId
        return self.addReq('GET', path, params, self.onQueryMyTrades, signed=True)
    
    #----------------------------------------------------------------------
    def startStream(self):
        """"""
        path = '/api/v1/userDataStream'
        return self.addReq('POST', path, {}, self.onStartStream, signed=True, stream=True)            
    
    #----------------------------------------------------------------------
    def keepaliveStream(self, listenKey):
        """"""
        path = '/api/v1/userDataStream'
        params = {'listenKey': listenKey}
        return self.addReq('PUT', path, params, self.onKeepaliveStream, signed=True, stream=True)
    
    #----------------------------------------------------------------------
    def closeStream(self, listenKey):
        """"""
        path = '/api/v1/userDataStream'
        params = {'listenKey': listenKey}
        return self.addReq('DELETE', path, params, self.onCloseStream, signed=True, stream=True)        

    ###################################################
    ## REST Callback
    ###################################################

    #----------------------------------------------------------------------
    def onError(self, data, reqid):
        """"""
        print((data, reqid))

    #----------------------------------------------------------------------
    def onQueryPing(self, data, reqid):
        """"""
        print((data, reqid))

    #----------------------------------------------------------------------
    def onQueryTime(self, data, reqid):
        """"""
        print((data, reqid))
        
    #----------------------------------------------------------------------
    def onQueryExchangeInfo(self, data, reqid):
        """"""
        print((data, reqid))
    
    #----------------------------------------------------------------------
    def onQueryDepth(self, data, reqid):
        """"""
        print((data, reqid))    
    
    #----------------------------------------------------------------------
    def onQueryTrades(self, data, reqid):
        """"""
        print((data, reqid))       
    
    #----------------------------------------------------------------------
    def onQueryAggTrades(self, data, reqid):
        """"""
        print((data, reqid))           
    
    #----------------------------------------------------------------------
    def onQueryKlines(self, data, reqid):
        """"""
        print((data, reqid))               
        
    #----------------------------------------------------------------------
    def onQueryTicker24HR(self, data, reqid):
        """"""
        print((data, reqid))         
    
    #----------------------------------------------------------------------
    def onQueryTickerPrice(self, data, reqid):
        """"""
        print((data, reqid))    
    
    #----------------------------------------------------------------------
    def onQueryBookTicker(self, data, reqid):
        """"""
        print((data, reqid))          
    
    #----------------------------------------------------------------------
    def onNewOrder(self, data, reqid):
        """"""
        print((data, reqid))              
    
    #----------------------------------------------------------------------
    def onQueryOrder(self, data, reqid):
        """"""
        print((data, reqid))          
        
    #----------------------------------------------------------------------
    def onCancelOrder(self, data, reqid):
        """"""
        print((data, reqid))          
        
    #----------------------------------------------------------------------
    def onQueryOpenOrders(self, data, reqid):
        """"""
        print((data, reqid))          
        
    #----------------------------------------------------------------------
    def onQueryAllOrders(self, data, reqid):
        """"""
        print((data, reqid))          
        
    #----------------------------------------------------------------------
    def onQueryAccount(self, data, reqid):
        """"""
        print((data, reqid))          
        
    #----------------------------------------------------------------------
    def onQueryMyTrades(self, data, reqid):
        """"""
        print((data, reqid))         
        
    #----------------------------------------------------------------------
    def onStartStream(self, data, reqid):
        """"""
        print((data, reqid))
    
    #----------------------------------------------------------------------
    def onKeepaliveStream(self, data, reqid):
        """"""
        print((data, reqid))              
    
    #----------------------------------------------------------------------
    def onCloseStream(self, data, reqid):
        """"""
        print((data, reqid))              
    
    ###################################################
    ## Websocket Function
    ###################################################
    
    #----------------------------------------------------------------------
    def initDataStream(self, nameList=None):
        """"""
        if nameList:
            self.dataStreamNameList = nameList
        s = '/'.join(self.dataStreamNameList)
        self.dataStreamUrl = DATASTREAM_ENDPOINT + s
        
        result = self.connectDataStream()
        if result:
            self.dataStreamActive = True
            self.dataStreamThread = Thread(target=self.runDataStream)
            self.dataStreamThread.start()
    
    #----------------------------------------------------------------------
    def runDataStream(self):
        """"""
        while self.dataStreamActive:
            try:
                stream = self.dataStreamWs.recv()
                data = json.loads(stream)
                self.onMarketData(data)
            except:
                self.onDataStreamError('Data stream connection lost')
                result = self.connectDataStream()
                if not result:
                    self.onDataStreamError(u'Waiting 3 seconds to reconnect')
                    sleep(3)
                else:
                    self.onDataStreamError(u'Data stream reconnected')
    
    #----------------------------------------------------------------------
    def closeDataStream(self):
        """"""
        self.dataStreamActive = False
        self.dataStreamThread.join()
    
    #----------------------------------------------------------------------
    def connectDataStream(self):
        """"""
        try:
            self.dataStreamWs = create_connection(self.dataStreamUrl,
                                                  sslopt={'cert_reqs': ssl.CERT_NONE})
            return True
        except:
            msg = traceback.format_exc()
            self.onDataStreamError('Connecting data stream falied: %s' %msg)
            return False
    
    #----------------------------------------------------------------------
    def onDataStreamError(self, msg):
        """"""
        print(msg)
    
    #----------------------------------------------------------------------
    def onMarketData(self, data):
        """"""
        print(data)
        
    #----------------------------------------------------------------------
    def initUserStream(self, key):
        """"""
        self.userStreamKey = key
        self.userStreamUrl = USERSTREAM_ENDPOINT + key
        
        result = self.connectUserStream()
        if result:
            self.userStreamActive = True
            self.userStreamThread = Thread(target=self.runUserStream)
            self.userStreamThread.start()
            
            self.keepaliveThread = Thread(target=self.runKeepalive)
            self.keepaliveThread.start()
    
    #----------------------------------------------------------------------
    def runUserStream(self):
        """"""
        while self.userStreamActive:
            try:
                stream = self.userStreamWs.recv()
                data = json.loads(stream)
                self.onUserData(data)                
            except:
                self.onUserStreamError('User stream connection lost')
                result = self.connectUserStream()
                if not result:
                    self.onUserStreamError(u'Waiting 3 seconds to reconnect')
                    sleep(3)
                else:
                    self.onUserStreamError(u'User stream reconnected')
    
    #----------------------------------------------------------------------
    def closeUserStream(self):
        """"""
        self.userStreamActive = False
        self.userStreamThread.join()
        self.keepaliveThread.join()
    
    #----------------------------------------------------------------------
    def connectUserStream(self):
        """"""
        try:
            self.userStreamWs = create_connection(self.userStreamUrl,
                                                  sslopt={'cert_reqs': ssl.CERT_NONE})
            return True
        except:
            msg = traceback.format_exc()
            self.onUserStreamError('Connecting user stream falied: %s' %msg)
            return False
    
    #----------------------------------------------------------------------
    def onUserStreamError(self, msg):
        """"""
        print(msg)
    
    #----------------------------------------------------------------------
    def onUserData(self, data):
        """"""
        print(data)
    
    #----------------------------------------------------------------------
    def runKeepalive(self):
        """"""
        while self.userStreamActive:
            self.keepaliveCount += 1
            
            if self.keepaliveCount >= 1800:
                self.keepaliveCount = 0
                self.keepaliveStream(self.userStreamKey)
            
            sleep(1)
        