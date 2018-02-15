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
import websocket

import inspect
import requests
import cerberus

CURRENCY_JPY = "jpy"
SYMBOL_BTCJPY = 'btc_jpy'

FUNCTIONCODE_GET_INFO_COINCHECK = 'get_info'
FUNCTIONCODE_GET_BALANCE_COINCHECK = 'get_balance'
FUNCTIONCODE_LIST_ORDER_COINCHECK = 'list_order'
FUNCTIONCODE_BUY_ORDER_COINCHECK = 'buy'
FUNCTIONCODE_SELL_ORDER_COINCHECK = 'sell'
FUNCTIONCODE_CANCEL_ORDER_COINCHECK = 'cancel_order'
FUNCTIONCODE_HISTORY_ORDER_COINCHECK = 'history'

class TradeApi(object):
    API_account = "https://coincheck.com/api/accounts"
    API_balance = "https://coincheck.com/api/accounts/balance"
    API_trade   = "https://coincheck.com/api/exchange/orders"
    API_list_order = "https://coincheck.com/api/exchange/orders/opens"
    API_history_order = "https://coincheck.com/api/exchange/orders/transactions"
    API_cancel_order = "https://coincheck.com/api/exchange/orders/%s"

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
        self.nonce = int(mktime(datetime.now().timetuple())) * 1000000000


    def make_header(self , url , body = ""):
        ''' create request header function
        :param url: URL for the new :class:`Request` object.
        '''
        self.nonce += 1
        nonce = str(self.nonce)
        message = nonce + url + body
        signature = hmac.new(self.secretKey.encode('utf-8'), message.encode('utf-8'), hashlib.sha256).hexdigest()
        headers = {
           'ACCESS-KEY'      : self.accessKey,
           'ACCESS-NONCE'    : nonce,
           'ACCESS-SIGNATURE': signature
        }
        return headers

    #----------------------------------------------------------------------
    def processRequest(self, req):
        """处理请求"""
        # 读取方法和参数
        url = req['url']
        method = req['method']

        r = None
        headers = self.make_header(url)
        if method in [FUNCTIONCODE_GET_INFO_COINCHECK , FUNCTIONCODE_GET_BALANCE_COINCHECK , FUNCTIONCODE_LIST_ORDER_COINCHECK , FUNCTIONCODE_HISTORY_ORDER_COINCHECK]:
            r = requests.get(url  , headers=headers)
        elif method in [FUNCTIONCODE_CANCEL_ORDER_COINCHECK]:
            r = requests.delete(url , headers=headers)
        elif method in [FUNCTIONCODE_BUY_ORDER_COINCHECK , FUNCTIONCODE_SELL_ORDER_COINCHECK]:
            kwargs = req["kwargs"]
            payload = { 'rate': kwargs['rate'],
                        'amount': kwargs['amount'],
                        'order_type': method,
                        'pair': SYMBOL_BTCJPY}
            body = 'rate={rate}&amount={amount}&order_type={order_type}&pair={pair}'.format(**payload)
            headers = self.make_header(url , body)
            r = requests.post(url,headers=headers,data=body)

            # print r
            # from coincheck import order,market,account
            # ok = order.Order(access_key=self.accessKey, secret_key=self.secretKey)
            # print "???"
            # return ok.buy_btc_jpy(amount=0.01,rate=200)
            #return self.create2( rate = 200 , amount = 0.01 , order_type = 'buy' ,  pair = 'btc_jpy')
            
            #self.create2( rate = 200 , amount = 0.01 , order_type = 'buy' ,  pair = 'btc_jpy')
            #r = self.create( rate = 200 , amount = 0.01 , order_type = 'buy' ,  pair = 'btc_jpy')

        # print "!!!!!!!!!!!!!!" ,method
        # if method in [FUNCTIONCODE_BUY_ORDER_COINCHECK , FUNCTIONCODE_SELL_ORDER_COINCHECK]:
        #     print "what?" , method ,  r.status_code
        # elif method in [FUNCTIONCODE_LIST_ORDER_COINCHECK]:
        #     print "list?" , method , r.status_code

        if r != None and r.status_code == 200:
            data = r.json()
            if data['success'] == 0:
                print "error in coincheck %s" % method
                return data
            else:
                return data
        else:
            try:
                data = json.loads(r.text)
                return data
            except Exception,ex:
                return None    

    #----------------------------------------------------------------------
    def processQueue(self):
        """处理请求队列中的请求"""
        while self.active:
            try:
                #print "processQueue"
                #req = self.reqQueue.get(block=True, timeout=0.001)  # 获取请求的阻塞为一秒
                # out_arr = [s[0] for s in self.reqQueue]
                # print out_arr

                (Type , req) = self.reqQueue[0]

                callback = req['callback']
                reqID = req['reqID']
                
                data = self.processRequest(req)
                # 请求成功
                if data != None :
                    if self.DEBUG:
                        print callback.__name__
                    callback(data, req, reqID)

                self.reqQueue.pop(0)
                sleep(0.1)
            except Exception,ex:
                pass    

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

        #if method in [FUNCTIONCODE_LIST_ORDER_COINCHECK , FUNCTIONCODE_GET_BALANCE_COINCHECK , FUNCTIONCODE_BUY_ORDER_COINCHECK , FUNCTIONCODE_SELL_ORDER_COINCHECK]:
        if method in [FUNCTIONCODE_LIST_ORDER_COINCHECK , FUNCTIONCODE_GET_BALANCE_COINCHECK ]:
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


    def get_info(self):
        return self.sendRequest( self.API_account , FUNCTIONCODE_GET_INFO_COINCHECK , self.onGet_info , None)

    def get_balance(self):
        return self.sendRequest( self.API_balance , FUNCTIONCODE_GET_BALANCE_COINCHECK , self.onGet_balance , None)

    def buy_btc_jpy(self , **kwargs):
        print "buy_btc_jpy"
        return self.sendRequest( self.API_trade , FUNCTIONCODE_BUY_ORDER_COINCHECK , self.onBuy_btc , kwargs = kwargs, optional = None)

    def sell_btc_jpy(self, **kwargs):
        print "sell_btc_jpy"
        return self.sendRequest( self.API_trade , FUNCTIONCODE_SELL_ORDER_COINCHECK , self.onSell_btc , kwargs = kwargs, optional = None)

    def list_orders(self):
        return self.sendRequest( self.API_list_order , FUNCTIONCODE_LIST_ORDER_COINCHECK , self.onList_order , None)

    def cancel_orders(self , order_id):
        return self.sendRequest( self.API_cancel_order % (str(order_id)) , FUNCTIONCODE_CANCEL_ORDER_COINCHECK , self.onCancel_orders , None)

    def history_orders(self):
        return self.sendRequest( self.API_history_order , FUNCTIONCODE_HISTORY_ORDER_COINCHECK , self.onHistory_orders , None)

    ####################################################
    ## 回调函数
    ####################################################
    def onGet_info(self, data, req, reqID):
        print data
    def onGet_balance(self, data, req, reqID):
        print data
    def onBuy_btc(self, data, req, reqID):
        print data
    def onSell_btc(self, data, req, reqID):
        print data
    def onList_order(self, data, req, reqID):
        print data
    def onCancel_orders(self, data, req, reqID):
        print data
    def onHistory_orders(self, data, req, reqID):
        print data

class DataApiSocket(object):
    """基于websocket的API对象"""
    #----------------------------------------------------------------------
    def __init__(self ):
        """Constructor"""
        self.host = ''          # 服务器地址
        
        self.currency = ''      # 货币类型（usd或者cny）
        
        self.ws = None          # websocket应用对象
        self.thread = None      # 工作线程

    #######################
    ## 通用函数
    #######################
    #----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """信息推送""" 
        print 'onMessage'
        print evt
        
    #----------------------------------------------------------------------
    def onError(self, ws, evt):
        """错误推送"""
        print 'onError'
        print evt
        
    #----------------------------------------------------------------------
    def onClose(self, ws):
        """接口断开"""
        print 'onClose'
        
    #----------------------------------------------------------------------
    def onOpen(self, ws):
        """接口打开"""
        print "onOpen"
        self.sendOrderbookRequest()
        self.sendTradesRequest()

    #----------------------------------------------------------------------
    def connect(self, host,  trace=False):
        """连接服务器"""
        self.host = host
        
        self.currency = CURRENCY_JPY
            
        websocket.enableTrace(trace)
        
        self.ws = websocket.WebSocketApp(host, 
                                         on_message=self.onMessage,
                                         on_error=self.onError,
                                         on_close=self.onClose,
                                         on_open=self.onOpen)        

        self.thread = Thread(target=self.ws.run_forever)
        self.thread.start()

        sleep(8)

    #----------------------------------------------------------------------
    def reconnect(self):
        """重新连接"""
        # 首先关闭之前的连接
        self.close()
        
        # 再执行重连任务
        self.ws = websocket.WebSocketApp(self.host, 
                                         on_message=self.onMessage,
                                         on_error=self.onError,
                                         on_close=self.onClose,
                                         on_open=self.onOpen)        
    
        self.thread = Thread(target=self.ws.run_forever)
        self.thread.start()

    #----------------------------------------------------------------------
    def exit(self):
        self.close()

    #----------------------------------------------------------------------
    def close(self):
        """关闭接口"""
        if self.thread and self.thread.isAlive():
            self.ws.close()
            self.thread.join()

    #----------------------------------------------------------------------
    def sendOrderbookRequest(self):
        """发送行情请求 , 订阅 orderbook"""
        # 生成请求
        d = {}
        d['type'] = 'subscribe'
        d['channel'] = "btc_jpy-orderbook"
        
        # 使用json打包并发送
        j = json.dumps(d)
        
        # 若触发异常则重连
        try:
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException:
            pass

    #----------------------------------------------------------------------
    def sendTradesRequest(self):
        """订阅最近的交易记录 """
        
        # 生成请求
        d = {}
        d['type'] = 'subscribe'
        d['channel'] = "btc_jpy-trades"
        
        # 使用json打包并发送
        j = json.dumps(d)
        
        # 若触发异常则重连
        try:
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException:
            pass 



class DataApi(object):

    '''get latest information of coincheck market'''
    TICK_SYMBOL_URL = {
        SYMBOL_BTCJPY: 'https://coincheck.com/api/ticker'
    }
    '''get latest deal history of coincheck market'''
    TRADES_SYMBOL_URL = {
        SYMBOL_BTCJPY: 'https://coincheck.com/api/trades'
    }
    '''get latest asks/bids information of coincheck market'''
    ORDERBOOKERS_SYMBOL_URL = {
        SYMBOL_BTCJPY: 'https://coincheck.com/api/order_books'
    }

    DEBUG = False

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
    def subscribeTrades(self, symbol):
        """订阅实时成交数据"""
        url = self.TRADES_SYMBOL_URL[symbol]
        task = (url, self.onTrades)
        self.taskList.append(task)
    
    #----------------------------------------------------------------------
    def subscribeOrderbooks(self, symbol):
        """订阅实时成交数据"""
        url = self.ORDERBOOKERS_SYMBOL_URL[symbol]
        task = (url, self.onOrderbooks)
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
    def onOrderbooks(self, data):
        """实时成交推送"""
        print data

if __name__ == '__main__':
    pass
