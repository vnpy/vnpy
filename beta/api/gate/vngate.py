# encoding: utf-8

import urllib
import hashlib

import json
import requests
from time import time, sleep
from Queue import Queue, Empty
from threading import Thread
import urlparse
from datetime import datetime
import base64
import hmac
import hashlib
import json
import gzip, binascii, os  
from cStringIO import StringIO  
import httplib


from vnpy.Function import systemSymbolToVnSymbol , VnSymbolToSystemSymbol

import json

API_QUERY_URL = 'data.gate.io'
API_TRADE_URL = 'api.gate.io'

FUNCTIONCODE_GET_SYMBOS_GATE = "pairs"
FUNCTIONCODE_GET_MARKETINFO_GATE = "marketinfo"     # 市场订单参数
FUNCTIONCODE_GET_MARKETLIST_GATE = "marketlist"     # 市场详细行情
FUNCTIONCODE_POST_BALANCE_GATE = "balances"
FUNCTIONCODE_POST_BUY_GATE = "buy"
FUNCTIONCODE_POST_SELL_GATE = "sell"
FUNCTIONCODE_POST_CANCEL_ORDERS_GATE = "cancelOrder"
FUNCTIONCODE_POST_ORDER_INFO_GATE = "getOrder"
FUNCTIONCODE_POST_ORDER_LIST_GATE = "openOrders"
FUNCTIONCODE_POST_HISTORY_TRADE = "tradeHistory"
'''
通过 TradeApi完成
'''
class Gate_TradeApi(object):
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.accessKey = ''
        self.secretKey = ''
        
        self.active = False         # API工作状态   
        self.reqID = 0              # 请求编号
        #self.reqQueue = Queue()    # 请求队列
        self.reqQueue = []          # 请求的队列
        self.reqThread = Thread(target=self.processQueue)   # 请求处理线程      

        self.account_id = None

    #----------------------------------------------------------------------
    def processRequest(self, req):
        """处理请求"""
        # 读取方法和参数
        try:
            url = req['url']
            method = req['method']
            kwargs = req['kwargs']
            resource = req["resource"]

            data = None
            if method in [FUNCTIONCODE_GET_SYMBOS_GATE , FUNCTIONCODE_GET_MARKETINFO_GATE]:
                data = self.httpGet( url, resource, '')
            elif method in [FUNCTIONCODE_POST_BALANCE_GATE , FUNCTIONCODE_POST_BUY_GATE , FUNCTIONCODE_POST_SELL_GATE , FUNCTIONCODE_POST_CANCEL_ORDERS_GATE , FUNCTIONCODE_POST_HISTORY_TRADE , FUNCTIONCODE_POST_ORDER_INFO_GATE , FUNCTIONCODE_POST_ORDER_LIST_GATE]:
                data = self.httpPost( url, resource, kwargs )
                # 添加额外信息
                if method == FUNCTIONCODE_POST_CANCEL_ORDERS_GATE:
                    data["systemID"] = kwargs["orderNumber"]
            return data
        except Exception,ex:
            print ex
            # pass
        return None

    #----------------------------------------------------------------------
    def processQueue(self):
        """处理请求队列中的请求"""
        while self.active:
            try:
                (Type , req) = self.reqQueue[0]

                callback = req['callback']
                reqID = req['reqID']
                try:
                    data = self.processRequest(req)
                    # 请求成功
                    if data != None :
                        callback(data, req, reqID)
                except Exception,ex:
                    print ex
                self.reqQueue.pop(0)
                sleep(0.1)
            except Exception,ex:
                pass

    #----------------------------------------------------------------------
    def sendRequest(self, url , resource , method, callback, kwargs = None,optional=None):
        """发送请求"""
        # 请求编号加1
        self.reqID += 1
        
        # 生成请求字典并放入队列中
        req = {}
        req['url'] = url
        req['resource'] = resource
        req['method'] = method
        req['callback'] = callback
        req['optional'] = optional
        req['kwargs'] = kwargs
        req['reqID'] = self.reqID

        if method in [  FUNCTIONCODE_POST_BALANCE_GATE , FUNCTIONCODE_POST_ORDER_LIST_GATE]:
            flag = False
            for use_method ,r in self.reqQueue:
                if use_method == method:
                    flag = True
                    break
            if False == flag:
                self.reqQueue.append( (method , req))
        else:
            self.reqQueue.append( (method , req))
        #self.reqQueue.put(req)
        
        # 返回请求编号
        return self.reqID

    #----------------------------------------------------------------------
    ####################################################
    ## 主动函数
    ####################################################    
    #----------------------------------------------------------------------
    def init(self, accessKey, secretKey):
        """初始化"""
        self.accessKey = accessKey
        self.secretKey = secretKey
        
        self.active = True
        self.reqThread.start()
    
    #----------------------------------------------------------------------
    def exit(self):
        """退出"""
        self.active = False
        
        if self.reqThread.isAlive():
            self.reqThread.join()  

    #----------------------------------------------------------------------
    def getSign(self, params, secretKey):
        bSecretKey = bytes(secretKey)
        bSecretKey = bSecretKey.encode(encoding='UTF8')

        sign = ''
        for key in params.keys():
            value = str(params[key])
            sign += key + '=' + value + '&'
        bSign = bytes(sign[:-1] )
        bSign = bSign.encode(encoding='UTF8')

        mySign = hmac.new(bSecretKey, bSign, hashlib.sha512).hexdigest()
        return mySign

    #----------------------------------------------------------------------
    def httpGet(self, url, resource, params=''):
        conn = httplib.HTTPSConnection(url, timeout=10)
        conn.request("GET", resource + '/' + params)
        response = conn.getresponse()
        data = response.read().decode('utf-8')
        return json.loads(data)

    #----------------------------------------------------------------------
    def httpPost(self, url, resource, params ):
        headers = {
            "Accept": "application/json",
            'Content-Type': 'application/x-www-form-urlencoded',
            "User-Agent": "Chrome/39.0.2171.71",
            "KEY":self.accessKey,
            "SIGN":self.getSign(params, self.secretKey)
        }

        conn = httplib.HTTPSConnection(url, timeout=10 )
        tempParams = urllib.urlencode(params) if params else '' 

        conn.request("POST", resource, tempParams, headers)
        response = conn.getresponse()
        data = response.read().decode('utf-8')

        conn.close()
        return json.loads(data)

    #----------------------------------------------------------------------
    def get_symbols(self):
        print(u'get_symbols')
        return self.sendRequest( API_QUERY_URL , "/api2/1/pairs" , FUNCTIONCODE_GET_SYMBOS_GATE ,  self.onAllSymbols ,  kwargs = {} , optional = None)

    #----------------------------------------------------------------------
    def get_market_info(self):
        print(u'get_market_info')
        return self.sendRequest( API_QUERY_URL , "/api2/1/marketinfo" , FUNCTIONCODE_GET_MARKETINFO_GATE ,  self.onMarketInfo ,  kwargs = {} , optional = None)

    #----------------------------------------------------------------------
    def get_balance(self):
        # print(u'get_balance')
        return self.sendRequest( API_TRADE_URL , "/api2/1/private/balances" ,FUNCTIONCODE_POST_BALANCE_GATE , self.onBalances , kwargs = {} , optional = None)

    #----------------------------------------------------------------------
    def spotBuy(self , symbol, rate, amount):
        print(u'spotBuy(self , %s, %s, %s)' % ( symbol, str(rate), str(amount)))
        kwargs = {'currencyPair': symbol,'rate':rate, 'amount':amount}
        return self.sendRequest( API_TRADE_URL , "/api2/1/private/buy" , FUNCTIONCODE_POST_BUY_GATE , self.onSpotTrade , kwargs = kwargs , optional = None)

    #----------------------------------------------------------------------
    def spotSell(self , symbol, rate, amount):
        print(u'spotSell(self , %s, %s, %s)' % (symbol , str(rate) , str(amount)))
        kwargs = {'currencyPair': symbol,'rate':rate, 'amount':amount}
        return self.sendRequest( API_TRADE_URL , "/api2/1/private/sell" , FUNCTIONCODE_POST_SELL_GATE , self.onSpotTrade , kwargs = kwargs , optional = None)
    
    #----------------------------------------------------------------------
    def spotTrade(self, symbol , amount, _type , price ):
        if _type == "buy":
            return self.spotBuy( symbol , price , amount )
        elif _type == "sell":
            return self.spotSell( symbol , price , amount )
        else:
            return None

    #----------------------------------------------------------------------
    def cancel_order(self , symbol , order_id):
        # print(u'cancel_order(self , %s , %s)' % (symbol , str(order_id)))
        kwargs = {"currencyPair" : symbol , "orderNumber" : order_id}
        return self.sendRequest( API_TRADE_URL ,"/api2/1/private/cancelOrder" , FUNCTIONCODE_POST_CANCEL_ORDERS_GATE , self.onCancelOrder , kwargs = kwargs , optional = None )

    #----------------------------------------------------------------------
    def getOrder( self, symbol , order_id ):
        # print(u'getOrder( self, %s , %s )' % (symbol , order_id))
        kwargs = {"currencyPair" : symbol , "orderNumber" : order_id}
        return self.sendRequest( API_TRADE_URL , "/api2/1/private/getOrder" , FUNCTIONCODE_POST_ORDER_INFO_GATE , self.onOrderInfo , kwargs = kwargs , optional = None)

    #----------------------------------------------------------------------
    def listTradeHistory(self , symbol ):
        kwargs = {"currencyPair" : symbol }
        return self.sendRequest( API_TRADE_URL , "/api2/1/private/tradeHistory" , FUNCTIONCODE_POST_HISTORY_TRADE , self.onTradeList , kwargs = kwargs , optional = None)

    #----------------------------------------------------------------------
    def listOpenOrders( self):
        # print(u'listOpenOrders( self)')
        return self.sendRequest( API_TRADE_URL , "/api2/1/private/openOrders" , FUNCTIONCODE_POST_ORDER_LIST_GATE , self.onOrderList , kwargs = {} , optional = None)

    #----------------------------------------------------------------------
    def onBalances(self,data, req, reqID):
        print(u'onBalances(self, data, req, reqID)')
        print data

    #----------------------------------------------------------------------
    def onAllSymbols(self,data, req, reqID):
        print(u'onAllSymbols(self, data, req, reqID)')
        print data

    #----------------------------------------------------------------------
    def onMarketInfo(self,data, req, reqID):
        print(u'onMarketInfo(self, data, req, reqID)')
        print data

    #----------------------------------------------------------------------
    def onSpotTrade(self,data, req, reqID):
        print(u'onSpotTrade(self, data, req, reqID)')
        print data

    #----------------------------------------------------------------------
    def onCancelOrder(self,data, req, reqID):
        print(u'onCancelOrder(self, data, req, reqID)')
        print data

    #----------------------------------------------------------------------
    def onOrderInfo(self,data, req, reqID):
        print(u'onOrderInfo(self, data, req, reqID)')
        print data

    #----------------------------------------------------------------------
    def onOrderList(self,data, req, reqID):
        print(u'onOrderList(self, data, req, reqID)')
        print data

    #----------------------------------------------------------------------
    def onTradeList(self,data, req, reqID):
        print(u'onTradeList(self, data, req, reqID)')
        print data

    



'''
通过 DataApi完成
'''
class Gate_DataApi(object):
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.active = False
        
        self.taskInterval = 3                       # 每轮请求延时
        self.taskList = []                          # 订阅的任务列表
        self.taskThread = Thread(target=self.run)   # 处理任务的线程

    #----------------------------------------------------------------------
    def init(self, interval, debug):
        """初始化"""
        self.taskInterval = interval
        self.DEBUG = debug
        
        self.active = True
        self.taskThread.start()

    #----------------------------------------------------------------------
    def exit(self):
        """退出"""
        self.active = False
        
        if self.taskThread.isAlive():
            self.taskThread.join()

    #----------------------------------------------------------------------
    def run(self):
        """连续运行"""
        while self.active:
            for url, resource ,callback ,params in self.taskList:
                try:
                    data = self.http_get_request(url, resource , params )
                    if isinstance(data , dict):
                        data["currencyPair"] = params
                        callback( data )
                except Exception, e:
                    print e
            sleep(self.taskInterval)

    #----------------------------------------------------------------------
    def http_get_request(self, url, resource ,params  ):
        conn = httplib.HTTPSConnection(url, timeout=10)
        conn.request("GET", resource + '/' + params)
        try:
            response = conn.getresponse()
            data = response.read().decode('utf-8')
            return json.loads(data)
        except Exception as e:
            print("httpGet failed, detail is:%s" %e)
            return {"status":"fail","msg":e}

    #----------------------------------------------------------------------
    def subscribeTick(self, symbol):
        """订阅实时成交数据"""
        url = "/api2/1/ticker"
        task = (API_QUERY_URL , url , self.onTick , symbol)
        self.taskList.append(task)

    #----------------------------------------------------------------------
    def subscribeTrades(self, symbol):
        """订阅实时成交数据"""
        url =  "/api2/1/tradeHistory"
        task = (API_QUERY_URL , url, self.onTrades , symbol)
        self.taskList.append(task)
    
    #----------------------------------------------------------------------
    def subscribeOrderbooks(self, symbol):
        """订阅实时成交数据"""
        url =  "/api2/1/orderBook"

        task = (API_QUERY_URL , url, self.onDepth , symbol)
        self.taskList.append(task)

    #----------------------------------------------------------------------
    def onTick(self, data):
        """实时成交推送"""
        print data

    #----------------------------------------------------------------------
    def onTrades(self, data):
        """实时成交推送"""
        print data

    #----------------------------------------------------------------------
    def onDepth(self, data):
        """实时成交推送"""
        print data