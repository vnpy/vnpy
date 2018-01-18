# encoding: utf-8

import urllib
import hashlib

import json
import requests
import hmac
import time
from datetime import datetime
from time import time, sleep , mktime
from Queue import Queue, Empty
from threading import Thread
import urllib 

import hashlib
import inspect
import requests
import cerberus

SYMBOL_BTCJPY = 'btc_jpy'
SYMBOL_ETHJPY = 'eth_jpy'

FUNCTIONCODE_GETINFO_ZAIF = 'get_info'
FUNCTIONCODE_GETINFO2_ZAIF = 'get_info2'
FUNCTIONCODE_GETPERSONALINFO_ZAIF = 'get_personal_info'
FUNCTIONCODE_TRADEHISTORY_ZAIF = 'trade_history'
FUNCTIONCODE_ACTIVEORDERS_ZAIF = 'active_orders'
FUNCTIONCODE_TRADE_ZAIF = 'trade'
FUNCTIONCODE_CANCEL_ORDER_ZAIF = 'cancel_order'
FUNCTIONCODE_WITHDRAL_ZAIF = 'withdraw'
FUNCTIONCODE_DEPOSIT_HISTORY_ZAIF = 'deposit_history'
FUNCTIONCODE_WITHDRAW_HISTORY_ZAIF = 'withdraw_history'

SCHEMA = {
    'from_num': {
        'type': 'integer'
    },
    'count': {
        'type': 'integer'
    },
    'from_id': {
        'type': 'integer'
    },
    'end_id': {
        'type': ['string', 'integer']
    },
    'order': {
        'type': 'string',
        'allowed': ['ASC', 'DESC']
    },
    'since': {
        'type': 'integer'
    },
    'end': {
        'type': ['string', 'integer']
    },
    'currency_pair': {
        'type': 'string',
        'allowed': ['btc_jpy', 'xem_jpy', 'mona_jpy', 'mona_btc']
    },
    'currency': {
        'required': True,
        'type': 'string',
        'allowed': ['jpy', 'btc', 'mona']
    },
    'address': {
        'required': True,
        'type': 'string'
    },
    'message': {
        'type': 'string'
    },
    'amount': {
        'required': True,
        'type': 'number'
    },
    'opt_fee': {
        'type': 'number'
    },
    'order_id': {
        'required': True,
        'type': 'integer'
    },
    'action': {
        'required': True,
        'type': 'string',
        'allowed': ['bid', 'ask']
    },
    'price': {
        'required': True,
        'type': 'number'
    },
    'limit': {
        'type': 'number'
    }
}


########################################################################
class TradeApi(object):
    """交易接口"""
    __API_URL = 'https://api.zaif.jp/tapi'
    DEBUG = True
     #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.accessKey = ''
        self.secretKey = ''
        
        self.active = False         # API工作状态   
        self.reqID = 0              # 请求编号
        self.reqQueue = Queue()     # 请求队列
        self.reqThread = Thread(target=self.processQueue)   # 请求处理线程      
        self.nonce = int(mktime(datetime.now().timetuple()))

    def params_pre_processing(self, schema_keys, params):
        schema = self.__get_schema(schema_keys)
        self.__validate(schema, params)
        return self.__edit_params(params)

    @classmethod
    def __get_schema(cls, keys):
        schema = {}
        for key in keys:
            schema[key] = SCHEMA[key]
        return schema

    @classmethod
    def __edit_params(cls, params):
        if 'from_num' in params:
            params['from'] = params['from_num']
            del (params['from_num'])
        return params

    @classmethod
    def __validate(cls, schema, param):
        v = cerberus.Validator(schema)
        if v.validate(param):
            return
        raise Exception(json.dumps(v.errors))

    def __get_parameter(self , func_name, params):
        params['method'] = func_name
        params['nonce'] = self.nonce
        self.nonce += 1
        return urllib.urlencode(params)


    def __get_header(self, params):
        signature = hmac.new(bytearray(self.secretKey.encode('utf-8')), digestmod=hashlib.sha512)
        signature.update(params.encode('utf-8'))

        return {
            'key': str(self.accessKey),
            'sign': str(signature.hexdigest())
        } 
    
    #----------------------------------------------------------------------
    
    def processRequest(self, req):
        """处理请求"""
        # 读取方法和参数
        schema_keys = req['schema_keys']
        method = req['method']
        kwargs = req['kwargs']

        optional = req['optional']
        params = self.params_pre_processing(schema_keys, kwargs)
        params = self.__get_parameter(method, params)
        header = self.__get_header(params)

        r = requests.post(self.__API_URL , data=params , headers=header)
        if r != None:
            try:
                data = r.json()
                if data['success'] == 0:
                    print "error in vnzaif %s" % method
                    return data
                else:
                    return data
            except Exception,ex:
                return None
        else:
            return None    
    '''
    def processRequest(self, req):
        schema_keys = req['schema_keys']
        kwargs = req['kwargs']
        method = req['method']
        optional = req['optional']
        params = self.params_pre_processing(schema_keys, kwargs)
        params = self.__get_parameter(method, params)
        header = self.__get_header(params)
        response = requests.post(self.__API_URL, data=params, headers=header)
        if response.status_code != 200:
            raise Exception('return status code is {}'.format(response.status_code))
        res = json.loads(response.text)
        if res['success'] == 0:
            raise Exception(res['error'])
        return res['return']
    '''
    #----------------------------------------------------------------------
    def processQueue(self):
        """处理请求队列中的请求"""
        while self.active:
            try:
                req = self.reqQueue.get(block=True, timeout=1)  # 获取请求的阻塞为一秒
                callback = req['callback']
                reqID = req['reqID']
                
                data = self.processRequest(req)
                
                # 请求失败
                if 'code' in data and 'message' in data:
                    error = u'错误信息：%s' %data['message']
                    self.onError(error, req, reqID)
                # 请求成功
                else:
                    if self.DEBUG:
                        print callback.__name__
                    callback(data, req, reqID)
                
            except Empty:
                pass    

    #----------------------------------------------------------------------
    def sendRequest(self, method, schema_keys , kwargs , callback, optional=None):
        """发送请求"""
        # 请求编号加1
        self.reqID += 1
        
        # 生成请求字典并放入队列中
        req = {}
        req['method'] = method
        req['schema_keys'] = schema_keys
        req['kwargs'] = kwargs
        #req['params'] = params
        req['callback'] = callback
        req['optional'] = optional
        req['reqID'] = self.reqID
        self.reqQueue.put(req)
        
        # 返回请求编号
        return self.reqID

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
    
    #---------------------------------------------------
    '''
    def get_info(self):
        print FUNCTIONCODE_GETINFO_ZAIF
        method = FUNCTIONCODE_GETINFO_ZAIF
        key = {}
        params = {}
        callback = self.onGet_info
        optional = {}
        print params
        return self.sendRequest(method, key, params,callback, optional)
    '''

    def get_info2(self):
        method = FUNCTIONCODE_GETINFO2_ZAIF
        key = {}
        params = {}
        callback = self.onGet_info2
        optional = {}
        return self.sendRequest(method, key, params, callback, optional)

    def trade_history(self , **kwargs):
        method = FUNCTIONCODE_TRADEHISTORY_ZAIF
        schema_keys = ['from_num', 'count', 'from_id', 'end_id', 'order', 'since', 'end', 'currency_pair']
        callback = self.onTradeHistory
        optional = {}
        return self.sendRequest(method, schema_keys, kwargs, callback, optional)

    def active_orders(self , **kwargs):
        method = FUNCTIONCODE_ACTIVEORDERS_ZAIF
        schema_keys = ['currency_pair']
        callback = self.onActiveOrders
        optional = {}
        return self.sendRequest(method, schema_keys, kwargs, callback, optional)

    def withdraw_history(self , **kwargs):
        method = FUNCTIONCODE_WITHDRAW_HISTORY_ZAIF
        schema_keys = ['currency', 'from_num', 'count', 'from_id', 'end_id', 'order', 'since', 'end']
        callback = self.onWithdrawHistory
        optional = {}
        return self.sendRequest(method, schema_keys, kwargs, callback, optional)

    def deposit_history(self , **kwargs):
        method = FUNCTIONCODE_DEPOSIT_HISTORY_ZAIF
        schema_keys = ['currency', 'from_num', 'count', 'from_id', 'end_id', 'order', 'since', 'end']
        callback = self.onDepositHistory
        optional = {}
        return self.sendRequest(method, schema_keys, kwargs, callback, optional)

    def withdraw(self , **kwargs):
        method = FUNCTIONCODE_WITHDRAL_ZAIF
        schema_keys = ['currency', 'address', 'message', 'amount', 'opt_fee']
        callback = self.onWithdraw
        optional = {}
        return self.sendRequest(method, schema_keys, kwargs, callback, optional)

    def cancel_order(self, **kwargs):
        method = FUNCTIONCODE_CANCEL_ORDER_ZAIF
        schema_keys = ['order_id']
        callback = self.onCancelOrder
        optional = {}
        return self.sendRequest(method, schema_keys, kwargs, callback, optional)

    def trade(self, **kwargs):
        method = FUNCTIONCODE_TRADE_ZAIF
        schema_keys = ['currency_pair', 'action', 'price', 'amount', 'limit']
        callback = self.onTrade
        optional = {}
        return self.sendRequest(method, schema_keys, kwargs, callback, optional)

    ####################################################
    ## 回调函数
    ####################################################
    '''
    def onGet_info(self, data, req, reqID):
        """用户信息"""
        print data
    '''
    def onTrade(self, data, req, reqID):
        print data
        
    def onCancelOrder(self, data, req, reqID):
        print data

    def onWithdraw(self, data, req, reqID):
        print data

    def onDepositHistory(self, data, req, reqID):
        print data

    def onWithdrawHistory(self, data, req, reqID):
        print data

    def onTradeHistory(self, data, req, reqID):
        print data

    def onActiveOrders(self, data, req, reqID):
        print data

    def onGet_info2(self, data, req, reqID):
        """用户信息"""
        print data




class DataApi(object):
    """
行情接口
    """
    TICK_SYMBOL_URL = {
        SYMBOL_BTCJPY: 'https://api.zaif.jp/api/1/ticker/btc_jpy',
        SYMBOL_ETHJPY: 'https://api.zaif.jp/api/1/ticker/eth_jpy'
    }

    TRADES_SYMBOL_URL = {
        SYMBOL_BTCJPY: 'https://api.zaif.jp/api/1/trades/btc_jpy',
        SYMBOL_ETHJPY: 'https://api.zaif.jp/api/1/trades/eth_jpy',
    }

    DEPTH_SYMBOL_URL = {
        SYMBOL_BTCJPY: 'https://api.zaif.jp/api/1/depth/btc_jpy',
        SYMBOL_ETHJPY: 'https://api.zaif.jp/api/1/depth/eth_jpy',
    }

    LAST_SYMBOL_URL = {
        SYMBOL_BTCJPY: 'https://api.zaif.jp/api/1/last_price/btc_jpy',
        SYMBOL_ETHJPY: 'https://api.zaif.jp/api/1/last_price/eth_jpy',
    }


    DEBUG = True

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
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
            for url, callback in self.taskList:
                try:
                    r = requests.get(url)
                    if r.status_code == 200:
                        data = r.json()
                        if self.DEBUG:
                            print callback.__name__

                        data = {"return_symbol": (url.split('/'))[-1].split('_')[0] , "data":data}
                        #data["return_symbol"] = 
                        callback(data)
                except Exception, e:
                    print e
                    
            sleep(self.taskInterval)


    #----------------------------------------------------------------------
    def subscribeTick(self, symbol):
        """订阅实时成交数据"""
        url = self.TICK_SYMBOL_URL[symbol]
        task = (url, self.onTick)
        self.taskList.append(task)

    #----------------------------------------------------------------------
    def subscribeLast(self, symbol):
        """订阅实时成交数据"""
        url = self.LAST_SYMBOL_URL[symbol]
        task = (url, self.onLast)
        self.taskList.append(task)
    

    #----------------------------------------------------------------------
    def subscribeTrades(self, symbol):
        """订阅实时报价数据"""
        url = self.TRADES_SYMBOL_URL[symbol]
        task = (url, self.onTrades)
        self.taskList.append(task)

    #----------------------------------------------------------------------
    def subscribeDepth(self, symbol, level=0):
        """订阅深度数据"""
        url = self.DEPTH_SYMBOL_URL[symbol]
        
        if level:
            url = url.replace('json', str(level))
        
        task = (url, self.onDepth)
        self.taskList.append(task)        


    #----------------------------------------------------------------------
    def onTick(self, data):
        """实时成交推送"""
        print data

    #----------------------------------------------------------------------
    def onLast(self, data):
        """实时深度推送"""
        print data        
    #----------------------------------------------------------------------
    def onTrades(self, data):
        """实时深度推送"""
        print data        
    #----------------------------------------------------------------------
    def onDepth(self, data):
        """实时深度推送"""
        print data        

