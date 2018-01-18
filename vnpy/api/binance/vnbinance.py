# encoding: UTF-8

import hashlib
import zlib
import json
from time import sleep
from threading import Thread

from autobahn.twisted.websocket import WebSocketClientFactory, \
    WebSocketClientProtocol, \
    connectWS
from twisted.internet import reactor, ssl
from twisted.internet.protocol import ReconnectingClientFactory
from twisted.internet.error import ReactorAlreadyRunning
import threading


from vnpy.api.binance.exceptions import BinanceAPIException, BinanceRequestException, BinanceWithdrawException
from vnpy.api.binance.websockets import BinanceSocketManager
from vnpy.api.binance.client import Client



FUNCTIONCODE_GET_ACCOUNT_BINANCE = 'get_account'
# FUNCTIONCODE_GET_ORDER = 'get_order'                  # 不准备实现
FUNCTIONCODE_GET_OPEN_ORDERS = 'get_open_orders'        # 获得所有的 open orders
FUNCTIONCODE_GET_ALL_ORDERS = "get_all_orders"          # 获得所有的 orders
FUNCTIONCODE_BUY_ORDER_BINANCE = 'buy'
FUNCTIONCODE_SELL_ORDER_BINANCE = 'sell'
FUNCTIONCODE_CANCEL_ORDER_BINANCE = 'cancel_order'
FUNCTIONCODE_GET_EXCHANGE_INFO = "get_exchange_info"

class BinanceSpotApi(object):
    """基于Websocket的API对象"""
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''        # 用户名
        self.secretKey = ''     # 密码

        self.client = None      # 客户端管理器
        self.bm = None          # sockets 管理器

        self.reqID = 0              # 请求编号
        # self.reqQueue = Queue()     # 请求队列
        self.reqQueue = []          # 请求的队列
        self.reqThread = Thread(target=self.processQueue)   # 请求处理线程

        self.active = False      # API工作状态  

    #----------------------------------------------------------------------
    def connect_Subpot(self, apiKey , secretKey ):
        self.apiKey = apiKey
        self.secretKey = secretKey

        self.client = Client( apiKey , secretKey)

        self.bm = BinanceSocketManager(self.client)

        # self.bm.start_user_socket( self.onMessage)

        self.bm.start()

        self.active = True
        self.reqThread.start()


    #----------------------------------------------------------------------
    def processQueue(self):
        """处理请求队列中的请求"""
        while self.active:
            try:
                #req = self.reqQueue.get(block=True, timeout=0.001)  # 获取请求的阻塞为一秒
                (Type , req) = self.reqQueue[0]

                callback = req['callback']
                reqID = req['reqID']
                
                try:
                    data = self.processRequest(req)
                    # 请求成功
                    if data != None :
                        if self.DEBUG:
                            print callback.__name__
                        callback(data, req, reqID)
                except Exception,ex:
                    print ex
                self.reqQueue.pop(0)
                sleep(0.1)
            except Exception,ex:
                pass

    #----------------------------------------------------------------------
    def processRequest(self, req):
        try:
            method = req['method']
            reqID = req["reqID"]
            
            data = None
            if method == FUNCTIONCODE_GET_ACCOUNT_BINANCE:
                data = self.client.get_account()
                self.onGetAccount(data , req , reqID)
            elif method == FUNCTIONCODE_GET_OPEN_ORDERS:
                kwargs = req["kwargs"]
                symbol = kwargs["symbol"]

                if symbol != None:
                    data = self.client.get_open_orders(symbol = symbol)
                    self.onGetOpenOrders(data , req , reqID)
                else:
                    data = self.client.get_open_orders()
                    self.onGetOpenOrders(data , req , reqID)

            elif method == FUNCTIONCODE_GET_ALL_ORDERS:
                kwargs = req["kwargs"]
                symbol = kwargs["symbol"]
                data = self.client.get_all_orders( symbol = symbol )
                self.onGetAllOrders(data , req , reqID)

            elif method == FUNCTIONCODE_BUY_ORDER_BINANCE:
                kwargs = req["kwargs"]
                symbol = self.legalSymbolUpper(kwargs["symbol"])
                quantity = float(kwargs["quantity"])
                price = float(kwargs["price"])
                data = self.client.order_limit_buy( symbol=symbol, price = price ,quantity=quantity)
                self.onGetBuyOrder(data , req , reqID)
                
            elif method == FUNCTIONCODE_SELL_ORDER_BINANCE:
                kwargs = req["kwargs"]
                symbol = self.legalSymbolUpper(kwargs["symbol"])
                quantity = float(kwargs["quantity"])
                price = float(kwargs["price"])
                data = self.client.order_limit_sell( symbol=symbol, price = price ,quantity=quantity)
                self.onGetSellOrder(data , req , reqID)

            elif method == FUNCTIONCODE_CANCEL_ORDER_BINANCE:
                kwargs = req["kwargs"]
                symbol = self.legalSymbolUpper(kwargs["symbol"])
                orderId = int(kwargs["orderId"])
                data = self.client.cancel_order( symbol = symbol , orderId = orderId )
                self.onGetCancelOrder(data , req , reqID)

            elif method == FUNCTIONCODE_GET_EXCHANGE_INFO:
                data = self.client.get_exchange_info()
                self.onExchangeInfo(data , req , reqID)

        except Exception,ex:
            print ex
            # pass

    #----------------------------------------------------------------------
    def legalSymbolLower(self, symbol):
        symbol = symbol.lower()
        symbol = ''.join(symbol.split('_'))
        return symbol

    #----------------------------------------------------------------------
    def legalSymbolUpper(self, symbol):
        symbol = symbol.upper()
        symbol = ''.join(symbol.split('_'))
        return symbol

    #----------------------------------------------------------------------
    def exit(self):
        """退出"""
        self.active = False
        if self.bm != None:
            self.bm.close()
        
        if self.reqThread.isAlive():
            self.reqThread.join()    

    #-----------------------------------------------------------------------
    def sendTradingRequest(self, method , callback , kwargs = None,optional=None):
        # 请求编号加1
        self.reqID += 1
        # 生成请求字典并放入队列中
        req = {}
        req['method'] = method
        req['callback'] = callback
        req['optional'] = optional
        req['kwargs'] = kwargs
        req['reqID'] = self.reqID

        if method in [FUNCTIONCODE_GET_OPEN_ORDERS , FUNCTIONCODE_GET_ACCOUNT_BINANCE ]:
            flag = False
            for use_method ,r in self.reqQueue:
                if use_method == method:
                    flag = True
                    break
            if False == flag:
                self.reqQueue.append( (method , req))
        else:
            self.reqQueue.append( (method , req))

        # 返回请求编号
        return self.reqID

    #----------------------------------------------------------------------
    def spotTrade(self, symbol_pair, type_, price, amount):
        """现货委托"""
        symbol_pair = self.legalSymbolLower(symbol_pair)
        if type_ == "buy":
            return self.sendTradingRequest( method = FUNCTIONCODE_BUY_ORDER_BINANCE , callback = self.onGetBuyOrder , kwargs = {"symbol":symbol_pair, "price":price,"quantity":amount} , optional=None)
        elif type_ == "sell":
            return self.sendTradingRequest( method = FUNCTIONCODE_SELL_ORDER_BINANCE , callback = self.onGetSellOrder , kwargs = {"symbol":symbol_pair, "price":price,"quantity":amount} , optional=None)
        
        return None
    #----------------------------------------------------------------------
    def spotCancelOrder(self, symbol_pair, orderid):
        symbol_pair = self.legalSymbolUpper(symbol_pair)
        return self.sendTradingRequest( method = FUNCTIONCODE_CANCEL_ORDER_BINANCE , callback = self.onGetCancelOrder , kwargs = {"symbol":symbol_pair,"orderId":int(orderid)} , optional=None)

    #----------------------------------------------------------------------
    def spotAccountInfo(self):
        """列出账户"""
        return self.sendTradingRequest( method = FUNCTIONCODE_GET_ACCOUNT_BINANCE , callback = self.onGetAccount , kwargs = {} , optional = None)

    #----------------------------------------------------------------------
    def spotListOpenOrders(self , symbol = None):
        """列出所有的 orders"""
        if symbol != None:
            symbol = self.legalSymbolUpper(symbol)
        return self.sendTradingRequest( method = FUNCTIONCODE_GET_OPEN_ORDERS , callback = self.onGetOpenOrders , kwargs = {"symbol":symbol} , optional=None)

    #----------------------------------------------------------------------
    def spotListAllOrders( self , symbol):
        symbol = self.legalSymbolUpper(symbol)
        return self.sendTradingRequest( method = FUNCTIONCODE_GET_ALL_ORDERS , callback = self.onGetAllOrders , kwargs = {"symbol":symbol} , optional=None)

    #----------------------------------------------------------------------
    def spotExchangeInfo(self):
        return self.sendTradingRequest( method = FUNCTIONCODE_GET_EXCHANGE_INFO , callback = self.onExchangeInfo , kwargs = {} , optional = None)

    #----------------------------------------------------------------------
    def subcribeSymbol(self , symbol):
        symbol = self.legalSymbolLower(symbol)
        #self.bm.start_symbol_ticker_socket( symbol , self.onTick)
        self.bm.start_multiplex_socket([symbol + "@ticker" , symbol + "@depth5" , symbol + "@trade"] , callback=self.onMessage)

    #----------------------------------------------------------------------
    def subscribeAllTicker(self):
        self.bm.start_ticker_socket( callback = self.onAllTicker)

    #----------------------------------------------------------------------
    def subscribeSpotTicker(self , symbol):
        if self.bm != None:
            symbol = self.legalSymbolLower(symbol)
            self.bm.start_symbol_ticker_socket( symbol , self.onTick)

    #----------------------------------------------------------------------
    def subscribeSpotDepth(self, symbol):
        if self.bm != None:
            symbol = self.legalSymbolLower(symbol)
            self.bm.start_depth_socket(symbol , self.onDepth)

    #----------------------------------------------------------------------
    def subscribeSpotTrades(self, symbol):
        if self.bm != None:
            symbol = self.legalSymbolLower(symbol)
            self.bm.start_trade_socket(symbol , self.onTrades)

    #----------------------------------------------------------------------
    def onMessage(self, msg):
        if "lastUpdateId" in msg.keys():
            self.onDepth( msg)
        else:
            if msg["e"] == "trade":
                self.onTrades(msg)
            elif "ticker" in msg["e"]:
                self.onTicker(msg)

    #----------------------------------------------------------------------
    def onAllTicker(self,msg):
        """币安支持所有 ticker 同时socket过来"""
        print msg

    #----------------------------------------------------------------------
    def onTicker(self, msg):
        print msg

    #----------------------------------------------------------------------
    def onDepth(self, msg):
        print msg

    #----------------------------------------------------------------------
    def onTrades(self, msg):
        print msg

    #----------------------------------------------------------------------
    def onGetAccount(self, data, req, reqID):
        print data

    #----------------------------------------------------------------------
    def onGetOpenOrders(self, data, req, reqID):
        print data

    #----------------------------------------------------------------------
    def onGetAllOrders(self, data, req, reqID):
        print data

    #----------------------------------------------------------------------
    def onGetBuyOrder(self, data, req, reqID):
        print data

    #----------------------------------------------------------------------
    def onGetSellOrder(self, data, req, reqID):
        print data

    #----------------------------------------------------------------------
    def onGetCancelOrder(self, data, req, reqID):
        print data

    #----------------------------------------------------------------------
    def onExchangeInfo(self, data, req, reqID):
        print data