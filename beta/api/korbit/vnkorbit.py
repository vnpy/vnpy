# encoding: utf-8

from __future__ import print_function
import urllib
import hashlib

import json
import logging
import requests
import hmac
import time
from datetime import datetime
from time import time, sleep , mktime
from Queue import Queue, Empty
from threading import Thread
import urllib
import websocket

import inspect
import requests
import cerberus


korbit_host = "https://api.korbit.co.kr/v1/"


KORBITFUNCTIONCODE_LIMIT_BID_ORDER = 'limit_bid_order'
KORBITFUNCTIONCODE_LIMIT_ASK_ORDER = 'limit_ask_order'
KORBITFUNCTIONCODE_CANCEL_ORDER = 'cancel'
KORBITFUNCTIONCODE_LIST_OPEN_ORDERS = 'list_open_orders'                # 不实现这个了，好像用不到，获得所有的 开仓单
KORBITFUNCTIONCODE_LIST_EXCHANGE_ORDERS = 'list_exchange_orders'        # 实现这个，获得所有的在交易的单子
KORBITFUNCTIONCODE_LIST_TRANSFERS = 'list_transfers'                    # 不实现这个，获得所有的 提现充值订单
KORBITFUNCTIONCODE_FEE = 'fee'                                          # 不实现这个，获得交易所手续费
KORBITFUNCTIONCODE_BALANCES = "balances"                                # 实现这个，获取用户账户持仓信息
KORBITFUNCTIONCODE_ACCOUNTS = "accounts"                                # 不实现这个，获取用户的提币地址

KORBIT_ALL_SYMBOL_PAIR = ["btc_krw","bch_krw" , "eth_krw"]
KORBIT_ALL_SYMBOLS = ["krw","btc","eth","etc","xrp","bch"]

class Korbit_TradeApi(object):
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.accessKey = ''
        self.secretKey = ''
        self.__token = {}

        self.active = False        # API 工作状态
        self.reqID = 0             # 请求编号

        # self.reqQueue = Queue()    # 请求队列
        self.reqQueue = []          # 请求的队列

        self.reqThread = Thread(target=self.processQueue)   # 请求处理线程

        self.DEBUG = True

    '''
    直接发送 request ,获得身份
    '''
    def request_post(self, path, headers=None, data=None):
        url = korbit_host + path
        response = requests.post(url, headers=headers, data=data, timeout=20)
        try:
            return response.json()
        except json.decoder.JSONDecodeError as e:
            print("exception: {}, response_text: {}".format(e, response.text))
            return response.text

    '''
    直接发送 get request ,获得其他数据
    '''
    def request_get(self, url, headers=None, params=None):
        response = requests.get( url, headers=headers, params=params, timeout=self.__timeout)
        try:
            return response.json()
        except json.decoder.JSONDecodeError as e:
            logging.error("exception: {}, response_text: {}".format(e, response.text))
            return response.text
    '''
    直接发送 request ,获得 token
    '''
    # https://apidocs.korbit.co.kr/#authentication
    def create_token_directly(self, username, password):
        payload = {
            'client_id': self.accessKey,
            'client_secret': self.secretKey,
            'username': username,
            'password': password,
            'grant_type': "password"
        }
        self.__token = self.request_post("oauth2/access_token", data=payload)
        return self.__token

    def refresh_token(self):
        payload = {
            'client_id': self.__client_id,
            'client_secret': self.__secret,
            'refresh_token': self.__token['refresh_token'],
            'grant_type': "refresh_token"
        }
        self.__token = self.request_post("oauth2/access_token", data=payload)
        return self.__token

    #----------------------------------------------------------------------
    def exit(self):
        """退出"""
        self.active = False

        if self.reqThread.isAlive():
            self.reqThread.join()

    @property
    def nonce(self):
        return int(time() * 1000)

    @property
    def headers(self):
        return {
            'Accept': 'application/json',
            'Authorization': "{} {}".format(self.__token['token_type'], self.__token['access_token'])
        }

    #----------------------------------------------------------------------
    def processRequest(self , req):
        """处理请求"""
        # 读取方法和参数
        url = req['url']
        method = req['method']

        r = None
        headers = self.headers
        kwargs = req["kwargs"]
        if method in [KORBITFUNCTIONCODE_LIMIT_BID_ORDER , KORBITFUNCTIONCODE_LIMIT_ASK_ORDER, KORBITFUNCTIONCODE_CANCEL_ORDER]:
            if method in [KORBITFUNCTIONCODE_CANCEL_ORDER]:
                payload = {
                    'id': kwargs["ids"],
                    'currency_pair': kwargs["currency_pair"],
                    'nonce': self.nonce
                }
                r = requests.post(url  , headers=headers , data = payload)
            else:
                payload = {
                    'type': 'limit',
                    'currency_pair': kwargs["currency_pair"],
                    'price': kwargs["price"],
                    'coin_amount': kwargs["coin_amount"],
                    'fiat_amount': None,
                    'nonce': self.nonce
                }

                r = requests.post(url  , headers=headers , data = payload)
        elif method in [KORBITFUNCTIONCODE_LIST_EXCHANGE_ORDERS , KORBITFUNCTIONCODE_BALANCES]:

            if method in [KORBITFUNCTIONCODE_LIST_EXCHANGE_ORDERS]:
                payload = {
                    'currency_pair': kwargs["currency_pair"],
                    'offset': kwargs["offset"],
                    'limit': kwargs["limit"]
                }
                r = requests.get(url , headers = headers , params = payload)

            elif method in [KORBITFUNCTIONCODE_BALANCES]:

                r = requests.get(url , headers = headers )

        # print url , method, headers , kwargs ,  r
        if r != None and r.status_code == 200:
            data = r.json()
            return data
        else:
            try:
                data = json.loads(r.text)
                print("Error in r , " , data)
                return data
            except Exception as ex:
                print(ex)
                return None

    #----------------------------------------------------------------------
    def processQueue(self):
        """处理请求队列中的请求"""
        while self.active:
            try:
                # req = self.reqQueue.get(block=True, timeout=0.1)  # 获取请求的阻塞为一秒
                if len(self.reqQueue) > 0:
                    (Type , req) = self.reqQueue[0]
                    self.reqQueue.pop(0)

                    callback = req['callback']
                    reqID = req['reqID']

                    data = self.processRequest(req)

                    # 请求成功
                    if data != None :
                        if self.DEBUG:
                            print(callback.__name__)
                        callback(data, req, reqID)

                    sleep(0.1)

            except Exception as ex:
                print(ex)

    #----------------------------------------------------------------------
    def sendRequest(self, url , method, callback, kwargs = None,optional=None):
        """发送请求"""
        # 请求编号加1
        self.reqID += 1

        # 生成请求字典并放入队列中
        req = {}
        req['url'] = url
        req['method'] = method
        req['callback'] = callback
        req['optional'] = optional
        req['kwargs'] = kwargs
        req['reqID'] = self.reqID

        if method in [KORBITFUNCTIONCODE_LIST_EXCHANGE_ORDERS ]:
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
    def exit(self):
        """退出"""
        self.active = False

        if self.reqThread.isAlive():
            self.reqThread.join()

    ####################################################
    ## 主动函数
    ####################################################
    #----------------------------------------------------------------------
    def init(self, accessKey, secretKey , username , password):
        """初始化"""
        self.accessKey = accessKey
        self.secretKey = secretKey

        self.create_token_directly( username , password)

        self.active = True
        self.reqThread.start()

    #----------------------------------------------------------------------
    def buy_currency(self , coin_amount, price, currency_pair="btc_krw"):
        kwargs = {"currency_pair":currency_pair , "coin_amount":coin_amount , "price":int(price)}
        return self.sendRequest( korbit_host + "user/orders/buy" , KORBITFUNCTIONCODE_LIMIT_BID_ORDER , self.on_buy_currency , kwargs = kwargs, optional = None)
    #----------------------------------------------------------------------
    def sell_currency(self , coin_amount , price , currency_pair="btc_krw"):
        kwargs = {"currency_pair":currency_pair , "coin_amount":coin_amount , "price":int(price)}
        return self.sendRequest( korbit_host + "user/orders/sell" , KORBITFUNCTIONCODE_LIMIT_ASK_ORDER , self.on_sell_currency , kwargs = kwargs, optional = None)
    #----------------------------------------------------------------------
    def list_market_orders(self , currency_pair = "btc_krw" , offset = 0 , limit = 50):
        kwargs = {"currency_pair":currency_pair , "offset":offset , "limit":limit}
        return self.sendRequest( korbit_host + "user/orders",KORBITFUNCTIONCODE_LIST_EXCHANGE_ORDERS , self.on_list_exchange_orders , kwargs = kwargs , optional = None)
    #----------------------------------------------------------------------
    def cancel_orders(self , order_id , currency_pair = "btc_krw"):
        kwargs = {"currency_pair":currency_pair , "ids": order_id}
        return self.sendRequest( korbit_host + "user/orders/cancel" , KORBITFUNCTIONCODE_CANCEL_ORDER , self.onCancelOrders , kwargs = kwargs , optional = None)
    #----------------------------------------------------------------------
    def user_balances(self):
        return self.sendRequest( korbit_host + "user/balances" , KORBITFUNCTIONCODE_BALANCES , self.onBalances , kwargs = {} , optional = None)

    ####################################################
    ## 回调函数
    ####################################################
    def on_buy_currency(self, data , req, reqID):
        print(data)
    #----------------------------------------------------------------------
    def on_sell_currency(self, data , req, reqID):
        print(data)
    #----------------------------------------------------------------------
    def on_list_exchange_orders(self, data , req, reqID):
        print(data)
    #----------------------------------------------------------------------
    def onCancelOrders(self, data , req, reqID):
        print(data)
    #----------------------------------------------------------------------
    def onBalances(self, data , req, reqID):
        print(data)

class Korbit_DataApi(object):

    simple_ticker_url = korbit_host + "ticker"
    detail_ticker_url = korbit_host + "ticker/detailed"
    orderbook_url = korbit_host + "orderbook"
    transactions_url = korbit_host + "transactions"
    constants_url = korbit_host + "constants"

    def __init__(self ):
        self.active = False

        self.taskInterval = 0                       # 每轮请求延时
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
            for url, callback , symbol in self.taskList:
                try:
                    r = requests.get(url)
                    if r.status_code == 200:
                        data = r.json()
                        data["symbol"] = symbol
                        if self.DEBUG:
                            print(callback.__name__)
                        callback(data)
                except Exception as e:
                    print("Korbit_DataApi" , e)
            sleep(self.taskInterval)

    #----------------------------------------------------------------------
    def subscribeTick(self, symbol):
        """订阅实时成交数据"""
        url = self.detail_ticker_url + "?currency_pair=" + symbol
        task = (url, self.onTick , symbol)
        self.taskList.append( task)

    #----------------------------------------------------------------------
    def subscribeTrades(self, symbol ):
        """订阅实时成交数据"""
        # time in ('minute','hour','day')
        url = self.transactions_url + "?currency_pair=" + symbol + "&time=" + "minute"
        task = (url, self.onTrades , symbol)
        self.taskList.append(task)

    #----------------------------------------------------------------------
    def subscribeOrderbooks(self, symbol):
        """订阅实时成交数据"""
        url = self.orderbook_url + "?currency_pair=" + symbol
        task = (url, self.onOrderbooks , symbol)
        self.taskList.append(task)

    #----------------------------------------------------------------------
    def onTick(self, data):
        """实时成交推送"""
        print(data)
    #----------------------------------------------------------------------
    def onTrades(self, data):
        """实时成交推送"""
        print(data)

    #----------------------------------------------------------------------
    def onOrderbooks(self, data):
        """实时成交推送"""
        print(data)
