# encoding: UTF-8

import sys
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
import traceback

from vnpy.api.binance.exceptions import BinanceAPIException, BinanceRequestException, BinanceWithdrawException
from vnpy.api.binance.websockets import BinanceSocketManager
from vnpy.api.binance.client import Client
import urllib, requests
import urllib.parse

# 请求指令
FUNCTIONCODE_GET_ACCOUNT_BINANCE = 'get_account'
# FUNCTIONCODE_GET_ORDER = 'get_order'                  # 不准备实现
FUNCTIONCODE_GET_OPEN_ORDERS = 'get_open_orders'        # 获得所有的 open orders
FUNCTIONCODE_GET_ALL_ORDERS = "get_all_orders"          # 获得所有的 orders
FUNCTIONCODE_BUY_ORDER_BINANCE = 'buy'
FUNCTIONCODE_SELL_ORDER_BINANCE = 'sell'
FUNCTIONCODE_CANCEL_ORDER_BINANCE = 'cancel_order'
FUNCTIONCODE_GET_EXCHANGE_INFO = "get_exchange_info"

# 印射关系
binance_exchanges_dict = {
    "bcc" : "bch",
    "bccusdt": "bchusdt",
    "bccbtc" : "bchbtc",
    "bccbnb" : "bchbnb",
    "bcceth" : "bcheth",
    "BCC" : "BCH",
    "BCCUSDT": "BCHUSDT",
    "BCCBTC" : "BCHBTC",
    "BCCBNB" : "BCHBNB",
    "BCCETH" : "BCHETH"
}

exchanges_biannce_dict = {v: k for k, v in binance_exchanges_dict.items()}

'''
将 币安的某些symbol_pair 与 其他交易所统一, 比如 bcc 换成 bch
'''
def symbolFromBinanceToOtherExchanges(symbol_pair):
    global binance_exchanges_dict
    if symbol_pair in binance_exchanges_dict.keys():
        return binance_exchanges_dict[symbol_pair]
    return symbol_pair

'''
将 其他交易所的symbol 印射到 币安的实际symbol 
'''
def symbolFromOtherExchangesToBinance(symbol_pair):
    global exchanges_biannce_dict
    if symbol_pair in exchanges_biannce_dict.keys():
        return exchanges_biannce_dict[symbol_pair]
    return symbol_pair

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

        self.DEBUG = False

        self.writeLog = None
        self.writeError = None

    #----------------------------------------------------------------------
    def connect_Subpot(self, apiKey , secretKey ):
        self.apiKey = apiKey
        self.secretKey = secretKey

        self.client = Client( apiKey , secretKey, self)
        self.client.DEBUG = self.DEBUG

        self.bm = BinanceSocketManager(self.client)

        self.bm.start_user_socket( self.onMessage)

        self.bm.start()

        self.active = True
        self.reqThread.start()

    #----------------------------------------------------------------------
    def processQueue(self):
        """处理请求队列中的请求"""
        while self.active:

            if len(self.reqQueue) == 0:
                sleep(0.1)
                continue

            (Type , req) = self.reqQueue[0]

            if req is None:
                self.reqQueue.pop(0)
                continue

            callback = req.get('callback', None)
            reqID = req.get('reqID', None)

            try:
                data = self.processRequest(req)
                # 请求成功
                if data != None :
                    if self.DEBUG:
                        self.writeLog(callback.__name__)
                    callback(data, req, reqID)
            except Exception as ex:
                self.writeError(u'processQueue exception:{},{}'.format(str(ex), traceback.format_exc()))

            self.reqQueue.pop(0)
            sleep(0.1)

    #----------------------------------------------------------------------
    def processRequest(self, req):
        """
        处理各类请求
        :param req:
        :return:
        """

        try:
            method = req['method']
            reqID = req["reqID"]
            callback = req['callback']
            data = None

            # 请求账号信息
            if method == FUNCTIONCODE_GET_ACCOUNT_BINANCE:
                data = self.client.get_account()
                # 替换 一些 symbol
                for b_symbol_dic in data["balances"]:
                    b_symbol_dic["asset"] = symbolFromBinanceToOtherExchanges(b_symbol_dic["asset"])

                self.onGetAccount(data , req , reqID)

            # 请求委托单
            elif method == FUNCTIONCODE_GET_OPEN_ORDERS:
                kwargs = req["kwargs"]
                symbol = kwargs["symbol"]

                if symbol != None:
                    data = self.client.get_open_orders(symbol = symbol)
                    # update symbol
                    for dic in data:
                        dic["symbol"] = symbolFromBinanceToOtherExchanges( dic["symbol"] )
                    callback(data , req , reqID)
                else:
                    data = self.client.get_open_orders()
                    # update symbol
                    for dic in data:
                        dic["symbol"] = symbolFromBinanceToOtherExchanges( dic["symbol"] )
                    callback(data , req , reqID)

            # 请求所有委托单
            elif method == FUNCTIONCODE_GET_ALL_ORDERS:
                kwargs = req["kwargs"]
                symbol = kwargs["symbol"]
                #if '_' not in symbol and len(symbol) in [3,4]:
                #    return None
                data = self.client.get_all_orders( symbol = symbol )
                # update symbol
                for dic in data:
                    dic["symbol"] = symbolFromBinanceToOtherExchanges( dic["symbol"] )

                callback(data , req , reqID)
            # 买入现货
            elif method == FUNCTIONCODE_BUY_ORDER_BINANCE:
                kwargs = req["kwargs"]
                symbol = self.legalSymbolUpper(kwargs["symbol"])
                quantity = float(kwargs["quantity"])
                price = float(kwargs["price"])
                price = str('%.8f' % float(price))
                data = self.client.order_limit_buy( symbol=symbol, price = price ,quantity=quantity)
                # update symbol
                data["symbol"] = symbolFromBinanceToOtherExchanges( data["symbol"] )
                callback(data , req , reqID)

            # 卖出现货
            elif method == FUNCTIONCODE_SELL_ORDER_BINANCE:
                kwargs = req["kwargs"]
                symbol = self.legalSymbolUpper(kwargs["symbol"])
                quantity = float(kwargs["quantity"])
                price = float(kwargs["price"])
                price = str('%.8f' % float(price))
                data = self.client.order_limit_sell( symbol=symbol, price = price ,quantity=quantity)
                # update symbol
                data["symbol"] = symbolFromBinanceToOtherExchanges( data["symbol"] )
                callback(data , req , reqID)

            # 取消订单
            elif method == FUNCTIONCODE_CANCEL_ORDER_BINANCE:
                kwargs = req["kwargs"]
                symbol = self.legalSymbolUpper(kwargs["symbol"])
                orderId = int(kwargs["orderId"])
                data = self.client.cancel_order( symbol = symbol , orderId = orderId )
                # update symbol
                data["symbol"] = symbolFromBinanceToOtherExchanges( data["symbol"] )

                callback(data , req , reqID)

            # 获取交易所信息
            elif method == FUNCTIONCODE_GET_EXCHANGE_INFO:
                data = self.client.get_exchange_info()
                # update symbol
                for symbol_dic in data["symbols"]:
                    symbol_dic["symbol"] = symbolFromBinanceToOtherExchanges( symbol_dic["symbol"] )
                    symbol_dic["baseAsset"] = symbolFromBinanceToOtherExchanges( symbol_dic["baseAsset"] )

                callback(data , req , reqID)

        except Exception as ex:
            if req is not None or reqID is not None:
                self.onAllError(ex, req, reqID)
            self.writeError(u'processRequest exception:{},{}'.format(str(ex), traceback.format_exc()))
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
        symbol_pair = self.legalSymbolUpper(symbol_pair)
        symbol_pair = symbolFromOtherExchangesToBinance(symbol_pair)
        if type_ == "buy":
            return self.sendTradingRequest( method = FUNCTIONCODE_BUY_ORDER_BINANCE , callback = self.onTradeOrder , kwargs = {"symbol":symbol_pair, "price":price,"quantity":amount} , optional=None)
        elif type_ == "sell":
            return self.sendTradingRequest( method = FUNCTIONCODE_SELL_ORDER_BINANCE , callback = self.onTradeOrder , kwargs = {"symbol":symbol_pair, "price":price,"quantity":amount} , optional=None)
        
        return None
        
    #----------------------------------------------------------------------
    def spotCancelOrder(self, symbol_pair, orderid):
        """现货委托撤单"""
        symbol_pair = self.legalSymbolUpper(symbol_pair)
        symbol_pair = symbolFromOtherExchangesToBinance(symbol_pair)
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
            symbol = symbolFromOtherExchangesToBinance(symbol)
        return self.sendTradingRequest( method = FUNCTIONCODE_GET_OPEN_ORDERS , callback = self.onGetOpenOrders , kwargs = {"symbol":symbol} , optional=None)

    #----------------------------------------------------------------------
    def spotListAllOrders( self , symbol):
        symbol = self.legalSymbolUpper(symbol)
        symbol = symbolFromOtherExchangesToBinance(symbol)
        return self.sendTradingRequest( method = FUNCTIONCODE_GET_ALL_ORDERS , callback = self.onGetAllOrders , kwargs = {"symbol":symbol} , optional=None)

    #----------------------------------------------------------------------
    def spotExchangeInfo(self):
        return self.sendTradingRequest( method = FUNCTIONCODE_GET_EXCHANGE_INFO , callback = self.onExchangeInfo , kwargs = {} , optional = None)

    #----------------------------------------------------------------------
    # def subcribeSymbol(self , symbol):
    #     symbol = self.legalSymbolLower(symbol)
    #     symbol = symbolFromOtherExchangesToBinance(symbol)
    #     #self.bm.start_symbol_ticker_socket( symbol , self.onTick)
    #     self.bm.start_multiplex_socket([symbol + "@ticker" , symbol + "@depth5" , symbol + "@trade"] , callback=self.onMessage)

    #----------------------------------------------------------------------
    def subscribeAllTicker(self):
        self.bm.start_ticker_socket( callback = self.onPreDealAllTicker)

    #----------------------------------------------------------------------
    def subscribeSpotTicker(self , symbol):
        if '.' in symbol:
            symbol = symbol.split('.')[0]
        if self.bm != None:
            # print "self.bm != None:"
            symbol = self.legalSymbolLower(symbol)
            symbol = symbolFromOtherExchangesToBinance(symbol)
            self.bm.start_symbol_ticker_socket(symbol, self.onPreDealTicker)

    #----------------------------------------------------------------------
    def subscribeSpotDepth(self, symbol):
        if '.' in symbol:
            symbol = symbol.split('.')[0]
        if self.bm != None:
            symbol = self.legalSymbolLower(symbol)
            symbol = symbolFromOtherExchangesToBinance(symbol)
            self.bm.start_depth_socket(symbol, self.onPreDealDepth)

    #----------------------------------------------------------------------
    def subscribeSpotTrades(self, symbol):
        if self.bm != None:
            symbol = self.legalSymbolLower(symbol)
            symbol = symbolFromOtherExchangesToBinance(symbol)
            self.bm.start_trade_socket(symbol, self.onPreDealTrades)

    #----------------------------------------------------------------------
    def http_get_request(self, url, params, add_to_headers=None):
        headers = {
            "Content-type": "application/x-www-form-urlencoded",
            'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0'
        }
        if add_to_headers:
            headers.update(add_to_headers)
        postdata = urllib.parse.urlencode(params)
        try:
            response = requests.get(url, postdata, headers=headers, timeout=5 )
            if response.status_code == 200:
                return response.json()
            else:
                return {"status": "fail"}
        except Exception as e:
            self.writeError('httpGet failed, detail is:{}'.format(str(e)))
            return {"status": "fail", "msg":e}

    # limit in [5, 10, 20, 50, 100, 500, 1000]
    #----------------------------------------------------------------------
    def getDepthSymbol(self, symbol , limit = 10):
        symbol = self.legalSymbolUpper(symbol)
        symbol = symbolFromOtherExchangesToBinance(symbol)
        url = "https://www.binance.com/api/v1/depth?symbol=%s&limit=%s" % ( symbol , str(limit))
        data = self.http_get_request( url , "")
        return data

    #----------------------------------------------------------------------
    def onMessage(self, msg):
        if 's' in msg.keys():
            msg['s'] = symbolFromBinanceToOtherExchanges(msg["s"])
        if "lastUpdateId" in msg.keys():
            self.onDepth( msg)
        else:
            if msg["e"] == "trade":
                self.onTrades(msg)
            elif "ticker" in msg["e"]:
                self.onTick(msg)

    #----------------------------------------------------------------------
    def onAllError(self, ex , req , reqID):
        self.writeError("onAllError" + str(ex))

    #----------------------------------------------------------------------
    def onPreDealAllTicker(self, msg):
        for dic in msg:
            dic["s"] = symbolFromBinanceToOtherExchanges(dic["s"])
        self.onAllTicker(msg)

    #----------------------------------------------------------------------
    def onAllTicker(self,msg):
        """币安支持所有 ticker 同时socket过来"""
        self.writeLog(u'onAllTicker:'.format(msg))

    # ----------------------------------------------------------------------
    def onPreDealTicker(self, msg):
        if 's' in msg.keys():
            msg['s'] = symbolFromBinanceToOtherExchanges(msg["s"])
        self.onTick(msg)

    #----------------------------------------------------------------------
    def onTick(self, msg):
        self.writeLog(u'onTick:'.format(msg))

    # ----------------------------------------------------------------------
    def onPreDealDepth(self, msg):
        if 's' in msg.keys():
            msg['s'] = symbolFromBinanceToOtherExchanges(msg["s"])
        self.onDepth(msg)
    #----------------------------------------------------------------------
    def onDepth(self, msg):
        self.writeLog(u'onDepth:'.format(msg))

    # ----------------------------------------------------------------------
    def onPreDealTrades(self, msg):
        if 's' in msg.keys():
            msg['s'] = symbolFromBinanceToOtherExchanges(msg["s"])
        self.onTrades(msg)
    #----------------------------------------------------------------------
    def onTrades(self, msg):
        self.writeLog(u'onTrades:{}'.format(msg))

    #----------------------------------------------------------------------
    def onGetAccount(self, data, req, reqID):
        self.writeLog(u'onGetAccount:'.format(data, req, reqID))

    #----------------------------------------------------------------------
    def onGetOpenOrders(self, data, req, reqID):
        self.writeLog(u'onGetOpenOrders:ata:{}, req:{}, reqID:{}'.format(data, req, reqID))

    #----------------------------------------------------------------------
    def onGetAllOrders(self, data, req, reqID):
        self.writeLog(u'onGetAllOrders:data:{}, req:{}, reqID:{}'.format(data, req, reqID))

    #----------------------------------------------------------------------
    def onGetBuyOrder(self, data, req, reqID):
        self.writeLog(u'onGetBuyOrder:data:{}, req:{}, reqID:{}'.format(data, req, reqID))

    #----------------------------------------------------------------------
    def onGetSellOrder(self, data, req, reqID):
        self.writeLog(u'onGetSellOrder:data:{}, req:{}, reqID:{}'.format(data, req, reqID))

    #----------------------------------------------------------------------
    def onGetCancelOrder(self, data, req, reqID):
        self.writeLog(u'onGetCancelOrder:data:{},req:{},reqId:{}'.format(data, req, reqID))

    #----------------------------------------------------------------------
    def onExchangeInfo(self, data, req, reqID):
        self.writeLog(u'onExchangeInfo:data:{},req:{},reqId:{}'.format(data, req, reqID))

    # ----------------------------------------------------------------------
    def onTradeOrder(self, data, req, reqID):
        self.writeLog (u'onTradeOrder:{}'.format(data))