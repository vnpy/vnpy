# encoding: utf-8

import sys
import urllib
import urllib.parse as urlparse

import json
import requests
from time import time, sleep

from threading import Thread
from datetime import datetime
from websocket import create_connection
import base64
import hmac
import hashlib
import json
import gzip, binascii, os  
import time

import websocket
import time
from time import  sleep , mktime
import random
import traceback

from vnpy.trader.vtFunction import systemSymbolToVnSymbol , VnSymbolToSystemSymbol

FCOIN_MARKET_URL = "api.fcoin.com/v2"
FCOIN_TRADE_URL = "api.fcoin.com/v2"
FCOIN_WSS_HOST = "wss://api.fcoin.com/v2/ws"

FUNCTIONCODE_GET_SYMBOS_FCOIN = "get_symbols"
FUNCTIONCODE_GET_ACCOUNTS_FCOIN = "get_accounts"
FUNCTIONCODE_GET_GET_BALANCE_FCOIN = "get_balance"
FUNCTIONCODE_POST_SEND_ORDERS_FCOIN = "send_order"
FUNCTIONCODE_POST_CANCEL_ORDERS_FCOIN = "cancel_order"
FUNCTIONCODE_GET_ORDER_INFO_FCOIN = "order_info"
FUNCTIONCODE_GET_ORDER_LIST_FCOIN = "order_list"
'''
交易接口
'''
class Fcoin_TradeApi(object):
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

        self.trade_info_limit_dic = None

    #----------------------------------------------------------------------
    def processRequest(self, req):
        """处理请求"""
        # 读取方法和参数
        try:
            url = req['url']
            method = req['method']
            kwargs = req['kwargs']

            data = None
            if method in [FUNCTIONCODE_GET_SYMBOS_FCOIN]:
                data = self.public_request(FCOIN_MARKET_URL, resource = url, params = kwargs)
            elif method in [ FUNCTIONCODE_GET_GET_BALANCE_FCOIN , FUNCTIONCODE_GET_ORDER_LIST_FCOIN , FUNCTIONCODE_GET_ORDER_INFO_FCOIN]:
                data = self.signed_request( 'GET' , url , kwargs )
            elif method in [ FUNCTIONCODE_POST_SEND_ORDERS_FCOIN , FUNCTIONCODE_POST_CANCEL_ORDERS_FCOIN]:
                data = self.signed_request( 'POST' , url , kwargs )
            return data
        except Exception as ex:
            print(u'{} Error in processRequest:{}{}'.format(datetime.now(), str(ex),traceback.format_exc()), file=sys.stderr)
            # pass
        return None

    #----------------------------------------------------------------------
    def processQueue(self):
        """处理请求队列中的请求"""
        while self.active:

            if len(self.reqQueue) == 0:
                sleep(0.1)
                continue

            (Type , req) = self.reqQueue[0]
            callback = req['callback']
            reqID = req['reqID']
            try:
                data = self.processRequest(req)
                # 请求成功
                if data != None :
                    # print "11 " ,callback , data, req, reqID
                    callback(data, req, reqID)
                    # print "22"
            except Exception as ex:
                print('{} processQueue Exception:{} {}'.format(datetime.now(), str(ex),traceback.format_exc()), file=sys.stderr)
            self.reqQueue.pop(0)
            sleep(0.1)

    #----------------------------------------------------------------------
    def is_same_req(self, req1 , req2):
        flag = False
        try:
            if req1["url"] == req2["url"]:
                return True
        except Exception as ex:
            print(u'Error in is_same_req , req1:{} , req2:{},exception:{}'.format(req1 , req2,str(ex)),file=sys.stderr)
        return flag

    #各种请求,获取数据方式
    # ----------------------------------------------------------------------
    def public_request(self, url, resource, params):
        """request public url"""
        r_url = "https://" + url + resource
        postdata = urlparse.urlencode(params)
        try:
            r = requests.get(r_url, postdata )
            r.raise_for_status()
        except Exception as ex:
            print("httpGet failed, detail is:%s" %ex)
            return {"status":"fail","msg":ex}

        if r != None and r.status_code == 200:
            return r.json()
        else:
            if r == None:
                print("http_get_request r is None")
                return {"status":"fail","msg":"http_get_request r is None" }

            print("r.status_code failed, r.status_code:%s" % r.status_code)
            return {"status":"fail","msg":"r.status_code = {}".format(r.status_code) }

    #----------------------------------------------------------------------
    def get_signed(self, sig_str):
        """signed params use sha512"""
        # sig_str = base64.b64decode(bytes(sig_str))
        sig_str = base64.b64encode(sig_str)
        signature = base64.b64encode(hmac.new(self.secretKey.encode(encoding='UTF-8'), sig_str, digestmod=hashlib.sha1).digest())
        return signature
        
    #----------------------------------------------------------------------
    def signed_request(self, method, resource, kwargs ):
        """request a signed url"""
        param=''
        if kwargs:
            sort_pay = list(kwargs.items())
            sort_pay.sort()
            for k in sort_pay:
                param += '&' + str(k[0]) + '=' + str(k[1])
            param = param.lstrip('&')

        timestamp = str(int(time.time() * 1000))

        full_url = "https://" + FCOIN_TRADE_URL + resource

        if method == 'GET':
            if param:
                full_url = full_url + '?' + param
            sig_str = method + full_url + timestamp
        #elif method == 'POST':
        else:
            sig_str = method + full_url + timestamp + param

        signature = self.get_signed(sig_str.encode(encoding='UTF-8'))

        headers = {
            'FC-ACCESS-KEY': self.accessKey,
            'FC-ACCESS-SIGNATURE': signature,
            'FC-ACCESS-TIMESTAMP': timestamp
        }

        r = None
        try:
            r = requests.request(method, full_url, headers = headers, json=kwargs)
            r.raise_for_status()
        except Exception as ex:
            print(u'signed_request exception:{},{}'.format(str(ex), traceback.format_exc()), file=sys.stderr)
            failed_state_json = {"status":"fail","msg": str(ex) }
            if r == None:
                print("signed_request r is None")
                return {"status":"fail","msg":"signed_request r is None" }
            else:
                content_json = r.json()
                failed_state_json["status"] = content_json.get('status' , 'fail')
                failed_state_json["msg"] = content_json.get('msg' , str(ex) )
                return failed_state_json

        if r != None and r.status_code == 200:
            return r.json()
        else:
            if r == None:
                print("signed_request r is None")
                return {"status":"fail","msg":"signed_request r is None" }

            print("r.status_code failed, r.status_code:%s" % r.status_code)
            return {"status":"fail","msg":"r.status_code = {}".format(r.status_code) }

    #----------------------------------------------------------------------
    def sendRequest(self, resource , method, callback, kwargs = None,optional=None):
        """发送请求"""
        # 请求编号加1
        self.reqID += 1
        
        # 生成请求字典并放入队列中
        req = {}
        req['url'] = resource
        req['method'] = method
        req['callback'] = callback
        req['optional'] = optional
        req['kwargs'] = kwargs
        req['reqID'] = self.reqID

        try:
            if method in [FUNCTIONCODE_GET_GET_BALANCE_FCOIN,FUNCTIONCODE_GET_ORDER_LIST_FCOIN ]:
                flag = False
                for use_method ,r in self.reqQueue:
                    if use_method == method:
                        flag = True
                        break
                if False == flag:
                    self.reqQueue.append( (method , req))
            elif method in [ FUNCTIONCODE_POST_CANCEL_ORDERS_FCOIN,FUNCTIONCODE_GET_ORDER_INFO_FCOIN ]:
                flag = False
                for use_method ,r in self.reqQueue:
                    if use_method == method:
                        if self.is_same_req( r , req) == True:
                            flag = True
                            break
                if False == flag:
                    self.reqQueue.append( (method , req))
            else:
                self.reqQueue.append((method, req))
        except Exception as ex:
            print(u'sendRequest exception:{},{}'.format(str(ex), traceback.format_exc()), file=sys.stderr)
        
        # 返回请求编号
        return self.reqID

    # ----------------------------------------------------------------------
    ####################################################
    ## 主动函数
    ####################################################    
    # ----------------------------------------------------------------------
    def init(self, accessKey, secretKey):
        """初始化"""
        self.accessKey = accessKey
        self.secretKey = secretKey
        
        self.active = True
        self.reqThread.start()
    
    # ----------------------------------------------------------------------
    def exit(self):
        """退出"""
        self.active = False
        
        if self.reqThread.isAlive():
            self.reqThread.join()  

    '''
    获得所有交易对
    '''
    #----------------------------------------------------------------------
    def get_symbols(self):
        # print(u'vnfcoin.get_symbols')
        kwargs = {}
        return self.sendRequest( '/public/symbols' , FUNCTIONCODE_GET_SYMBOS_FCOIN , self.onAllSymbols , kwargs = kwargs , optional = None)

    #----------------------------------------------------------------------
    def get_balance(self):
        # print(u'vnfcoin.get_balance')
        kwargs = {}
        return self.sendRequest( '/accounts/balance' , FUNCTIONCODE_GET_GET_BALANCE_FCOIN , self.onGetBalance , kwargs = kwargs , optional = None)

    #----------------------------------------------------------------------
    def spotTrade(self, symbol , _type, price , volume):
        print(u'vnfcoin.spotTrade')
        symbol = VnSymbolToSystemSymbol(symbol)
        side = "buy"
        if _type == "buy":
            side = "buy"
        else:
            side = "sell"
        kwargs = { "symbol":symbol, "side":side, "type":"limit", "price":price, "amount": volume}
        print(u'vnfcoin.spotTrade:{}'.format(kwargs))
        return self.sendRequest( "/orders", FUNCTIONCODE_POST_SEND_ORDERS_FCOIN , self.onSpotTrade , kwargs = kwargs , optional = None)

    '''
    symbol      交易对
    states      订单状态     submitted , filled
    before      查询某个页码之前的订单
    after       查询某个页码之后的订单
    limit       每页的订单数量，默认为 20 条
    '''
    # ----------------------------------------------------------------------
    def orders_list(self, symbol , states = "submitted"):
        # print(u'vnfcoin.orders_list')
        if '.' in symbol:
            symbol = symbol.split('.')[0]
        if '_'in symbol:
            symbol = VnSymbolToSystemSymbol(symbol)
        kwargs = { "symbol":symbol , "states":states}
        return self.sendRequest( "/orders", FUNCTIONCODE_GET_ORDER_LIST_FCOIN , self.onOrderList , kwargs = kwargs , optional = None)

    # ----------------------------------------------------------------------
    def order_info(self, order_id):
        # print(u'vnfcoin.order_info')
        kwargs = { }
        return self.sendRequest( "/orders/{order_id}".format(order_id=order_id), FUNCTIONCODE_GET_ORDER_INFO_FCOIN , self.onOrderInfo , kwargs = kwargs , optional = None)

    # ----------------------------------------------------------------------
    def cancel_order(self, order_id):
        print(u'vnfcoin.cancel_order')
        kwargs = {}
        return self.sendRequest( '/orders/{order_id}/submit-cancel'.format(order_id=order_id), FUNCTIONCODE_POST_CANCEL_ORDERS_FCOIN , self.onCancelOrder , kwargs = kwargs , optional = None)

    # ----------------------------------------------------------------------
    def onAllSymbols(self,data, req, reqID):
        print(data)

    '''
    已完成订单
    {"status":3008,"msg":"submit cancel invalid order state"}
    已完成订单
    -mJeAvSsGP4lmbHWciEMBnU3XnsnRjQG39FYqIvf7TU
    {u'status': 0}
    '''
    # ----------------------------------------------------------------------
    def onCancelOrder(self, data, req,reqID):
        print(data)

    # ----------------------------------------------------------------------
    def onGetBalance(self,data, req, reqID):
        print(data)
    '''
    错误单返回 结果 
    {'status': 1001, 'msg': u'bad argument: amount'}
    正确单返回结果
    {u'status': 0, u'data': u'FqR0e0zmPFK4NQlgrc8sl1qmvpv-lEPQxawdrOBGZuA='}
    '''
    # ----------------------------------------------------------------------
    def onSpotTrade(self,data, req, reqID):
        print(data)

    '''
    已完成订单
    {u'status': 0, u'data': 
    {u'created_at': 1528530599997L, u'fill_fees': u'3.000000000000000000', u'price': u'0.591000000000000000', u'state': u'filled', u'filled_amount': u'3000.000000000000000000', u'id': u'U-RcMGl_XUdfs2yI-98a0hQzoMVlVPYiqt
XvmZio9F8=', u'source': u'web', u'amount': u'3000.000000000000000000', u'executed_value': u'1773.000000000000000000', u'type': u'limit', u'symbol': u'ftusdt', u'side': u'buy'}}    
    未完成订单
    {u'status': 0, u'data': {u'created_at': 1528617873671L, u'fill_fees': u'0.000000000000000000', u'price': u'0.300000000000000000', u'state': u'submitted', u'filled_amount': u'0.000000000000000000', u'id': u'-mJeAvSsGP4lmbHWciEMBnU3XnsnRjQG39
FYqIvf7TU=', u'source': u'api', u'amount': u'1.000000000000000000', u'executed_value': u'0.000000000000000000', u'type': u'limit', u'symbol': u'ftusdt', u'side': u'buy'}}
    '''
    #----------------------------------------------------------------------
    def onOrderInfo(self,data, req, reqID):
        print(data)

    '''
    已完成订单 的取消状态
    {u'status': 0, u'data': {u'created_at': 1528530599997L, u'fill_fees': u'3.000000
000000000000', u'price': u'0.591000000000000000', u'state': u'filled', u'filled_
amount': u'3000.000000000000000000', u'id': u'U-RcMGl_XUdfs2yI-98a0hQzoMVlVPYiqt
XvmZio9F8=', u'source': u'web', u'amount': u'3000.000000000000000000', u'execute
d_value': u'1773.000000000000000000', u'type': u'limit', u'symbol': u'ftusdt', u
'side': u'buy'}}
    未完成订单 的取消状态
    {u'status': 0, u'data': {u'created_at': 1528530599997L, u'fill_fees': u'3.000000
000000000000', u'price': u'0.591000000000000000', u'state': u'filled', u'filled_
amount': u'3000.000000000000000000', u'id': u'U-RcMGl_XUdfs2yI-98a0hQzoMVlVPYiqt
XvmZio9F8=', u'source': u'web', u'amount': u'3000.000000000000000000', u'execute
d_value': u'1773.000000000000000000', u'type': u'limit', u'symbol': u'ftusdt', u
'side': u'buy'}}
    '''
    #----------------------------------------------------------------------
    def onOrderList(self,data, req, reqID):
        print(data)

'''
Fcoin 的数据接口
'''
class Fcoin_DataApi(object):
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.active = False
        
        self.taskInterval = 3                       # 每轮请求延时
        self.taskList = []                        # 订阅的任务列表
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
                    callback(self.http_get_request(url, resource , params ))
                except Exception as ex:
                    print(u'run exception:{},{}'.format(str(ex),traceback.format_exc()),file=sys.stderr)
            sleep(self.taskInterval)

    #----------------------------------------------------------------------
    def rightFormatSimple(self, symbol):
        symbol = ''.join(symbol.split('_'))
        return symbol.lower()


    #各种请求,获取数据方式
    #----------------------------------------------------------------------
    def http_get_request(self , url , resource , params):
        """request public url"""
        r_url = "https://" + url + resource
        postdata = urlparse.urlencode(params)
        try:
            r = requests.get(r_url, postdata )
            r.raise_for_status()
        except Exception as ex:
            print(u'http_get_request exception:{}'.format(str(ex),traceback.format_exc()),file=sys.stderr)
            return {"status":"fail","msg":str(ex)}
        if r.status_code == 200:
            return r.json()
    '''
    {u'status': 0, u'data': {u'type': u'ticker.ftusdt', u'ticker': [0.483877, 99.0,0.483876, 91.0, 0.483877, 6763.79, 0.5625, 0.66, 0.3994, 105720494.48557205, 495
23332.79558287], u'seq': 616993}}
    '''
    #----------------------------------------------------------------------
    def subscribeTick(self, symbol):
        """订阅实时成交数据"""
        #url = FCOIN_MARKET_URL + '/market/history/kline'
        symbol = self.rightFormatSimple(symbol)
        params = {}
        task = (FCOIN_MARKET_URL , '/market/ticker/{symbol}'.format(symbol=symbol) , self.onTick , params)
        if task not in self.taskList:
            self.taskList.append(task)
    '''
    {u'status': 0, u'data': [{u'price': 0.483877, u'amount': 99.0, u'side': u'buy',u'ts': 1528474777106L, u'id': 616961000}]}
    '''
    #----------------------------------------------------------------------
    def subscribeTrades(self, symbol):
        """订阅实时成交数据"""
        symbol = self.rightFormatSimple(symbol)
        params = {}

        task = (FCOIN_MARKET_URL , '/market/trades/{symbol}'.format(symbol = symbol) , self.onTrades , params)
        if task not in self.taskList:
            self.taskList.append(task)
    
    '''
    {u'status': 0, u'data': {u'type': u'depth.L20.ftusdt', u'seq': 617017, 
    u'bids':[0.483876, 41.0, 0.483612, 1.0, 0.483, 565.3, 0.482998, 18.7, 0.482949, 1.0, 0.482912, 3000.0, 0.482807, 20.0, 0.48, 857.96, 0.476, 2955.3, 0.47581, 402.81, 0.47574, 184.9, 0.475738, 183.0, 0.475, 1569.3, 0.472039, 297.0, 0.471, 30.0, 0.470314, 200.0, 0.470313, 221.61, 0.47, 3092.68, 0.469608, 400.0, 0.469606, 284.0],
    u'ts': 1528474816007L, 
    u'asks': [0.483877, 6763.79, 0.483879, 95.0, 0.48388, 99.0, 0.483881, 102.0, 0.483882, 1166.66, 0.484407, 20.0, 0.484848, 3000.0, 0.484997, 95.0, 0.484998, 92.0, 0.485, 991.76, 0.485008, 92.0, 0.485009, 98.0, 0.48678,283.94689891, 0.486793, 91.0, 0.486794, 91.0, 0.486795, 3.0, 0.486796, 96.0, 0.
     486797, 20.0, 0.486798, 20.0, 0.486799, 90.0]}}
    '''
    #----------------------------------------------------------------------
    def subscribeOrderbooks(self, symbol , level = "L20"):
        """订阅实时成交数据"""
        # level in ["L20" , "L100" , "full"]
        # url = FCOIN_MARKET_URL + '/market/depth'
        symbol = self.rightFormatSimple(symbol)
        params = {}
        task = (FCOIN_MARKET_URL , '/market/depth/{level}/{symbol}'.format(level=level, symbol=symbol) , self.onDepth , params)
        if task not in self.taskList:
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
    def onDepth(self, data):
        """实时成交推送"""
        print( data)


'''
API接口    Fcoin 的 websocket api 文档不够全
'''

class Fcoin_DataApiSocket(object):
    """基于Websocket的API对象"""
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.host = ''          # 服务器地址
        
        self.ws = None          # websocket应用对象
        self.thread = None      # 工作线程

        self.subscribeStrList = set([])

    #----------------------------------------------------------------------
    def reconnect(self):
        """重新连接"""
        # 首先关闭之前的连接
        #self.close()
        
        # 再执行重连任务
        self.ws = websocket.WebSocketApp(self.host, 
                                         on_message=self.onMessage,
                                         on_error=self.onError,
                                         on_close=self.onClose,
                                         on_open=self.onOpen)        
    
        self.thread = Thread(target=self.ws.run_forever , args = (None , None , 60, 30))
        self.thread.start()

    #----------------------------------------------------------------------
    def connect_Subpot(self , trace = False):
        self.host = FCOIN_WSS_HOST
        self.trace = trace

        websocket.enableTrace(trace)

        self.ws = websocket.WebSocketApp(self.host, 
                                             on_message=self.onMessage,
                                             on_error=self.onError,
                                             on_close=self.onClose,
                                             on_open=self.onOpen)        
            
        self.thread = Thread(target = self.ws.run_forever , args = (None , None , 60, 30))
        # self.thread_heart = Thread(target = self.run_forever_heart)

        self.thread.start()
        # self.thread_heart.start()

    #----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """
        信息推送事件
        :param ws:  接口
        :param evt: 事件
        :return:
        """
        print(u'vnfcoin.onMessage:{}'.format(evt))
        
    #----------------------------------------------------------------------
    def onError(self, ws, evt):
        """
        接口错误推送事件
        :param ws:
        :param evt:
        :return:
        """
        print(u'vnfcoin.onApiError:{}'.format(evt))
        
    #----------------------------------------------------------------------
    def onClose(self, ws):
        """
        接口断开事件
        :param ws:
        :return:
        """
        print(u'vnfcoin.onClose')
        
    #----------------------------------------------------------------------
    def onOpen(self, ws):
        """
        接口打开事件
        :param ws:
        :return:
        """
        print(u'vnfcoin.onOpen')

        # req = {
        #     "cmd" : 'sub',
        #     "args" : ['ticker.ftusdt'],
        #     "id" : '1'
        # }
        # print json.dumps(req)
        # self.ws.send( json.dumps( req))

    #----------------------------------------------------------------------
    def sendSocketCmd( self, cmd , args , client_id ):
        send_json = {
            "cmd": 'sub',
            "args": args,
            "params": client_id
        }
        self.ws.send( json.dumps(send_json))

    #----------------------------------------------------------------------
    def subscribeTicker( self , symbol ):
        symbol = VnSymbolToSystemSymbol(symbol)
        self.sendSocketCmd( "sub" , ["ticker.%s" % symbol] , "1")

    '''
    depth.L20.ethbtc
    level in [""]
    '''
    #----------------------------------------------------------------------
    def subscribeDepth( self , symbol , level = "L20"):
        symbol = VnSymbolToSystemSymbol(symbol)
        self.sendSocketCmd( "sub" , ["depth.%s.%s" % ( level ,symbol) ] , "2")

    #----------------------------------------------------------------------
    


