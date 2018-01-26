# encoding: UTF-8

import json
import requests
from socketIO_client import SocketIO
from threading import Thread
from queue import Queue, Empty


########################################################################
class FxcmApi(object):
    """FXCM"""
    API_URL = 'https://api-demo.fxcm.com:443'
    WEBSOCKET_PORT = 443
    METHOD_GET = 'get'
    METHOD_POST = 'post'
    
    MODEL_OFFER = 'Offer'
    MODEL_ACCOUNT = 'Account'
    MODEL_ORDER = 'Order'
    MODEL_OPENPOSITION = 'OpenPosition'
    MODEL_SUMMARY = 'Summary'
    MODEL_PROPERTIES = 'Properties'
    MODEL_CLOSEDPOSITION = 'ClosedPosition'

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.url = ''
        self.port = ''
        self.token = ''
        self.proxy = ''
        
        self.sio = None
        self.bearer = ''
        self.headers = None
        
        self.queue = Queue()
        self.reqid = 0
        self.active = False
        self.reqThread = None
        self.sioThread = None
        
    #----------------------------------------------------------------------
    def connect(self, url, port, token, proxy=''):
        """连接"""
        self.url = url
        self.port = port
        self.token = token
        self.proxy = proxy
        
        self.active = True
        
        self.reqThread = Thread(target=self.runReq)
        self.reqThread.start()
        
        self.sioThread = Thread(target=self.runSio)
        self.sioThread.start()
        
    #----------------------------------------------------------------------
    def stop(self):
        """停止"""
        if self.active:
            self.active = False
            self.reqThread.join()
            
            self.sio._close()
            self.sioThread.join()
        
    #----------------------------------------------------------------------
    def initSocketIO(self):
        """初始化SocketIO客户端"""
        params = {
            'access_token': self.token, 
            'agent': "leiwang-rest-api"
        }
        
        proxy = {}
        if self.proxy:
            proxy['https'] = self.proxy        
            
        self.sio = SocketIO(self.url, self.port, params=params, proxies=proxy)
        
        self.sio.on('connect', self.onConnect)
        self.sio.on('disconnect', self.onDisconnect)
        
    #----------------------------------------------------------------------
    def generateBearer(self):
        """创建通讯授权码"""
        self.bearer = "Bearer " + self.sio._engineIO_session.id + self.token
        
    #----------------------------------------------------------------------
    def generateHeaders(self):
        """生成通讯头部"""
        self.headers = {
            'User-Agent': 'request',
            'Authorization': self.bearer,
            'Accept': 'application/json',
            'Content-Type': 'application/x-www-form-urlencoded'
        }
        
    #----------------------------------------------------------------------
    def runReq(self):
        """处理主动请求"""
        while self.active:
            try:
                d = self.queue.get(timeout=1)
                self.processReq(d)
            except Empty:
                pass
    
    #----------------------------------------------------------------------
    def runSio(self):
        """处理回调数据"""
        self.initSocketIO()
        self.generateBearer()
        self.generateHeaders()        
        self.sio.wait()
        
    #----------------------------------------------------------------------
    def sendReq(self, method, uri, params, callback):
        """发出请求"""
        self.reqid += 1
        
        d = {
            'method': method,
            'uri': uri,
            'params': params,
            'callback': callback,
            'reqid': self.reqid
        }
        
        self.queue.put(d)
        
        return self.reqid
        
    #----------------------------------------------------------------------
    def processReq(self, d):
        """处理请求"""
        method = d['method']
        uri = d['uri']
        params = d['params']
        callback = d['callback']
        reqid = d['reqid']
        
        url = self.url + uri
        
        proxy = {}
        if self.proxy:
            proxy['https'] = self.proxy
        
        if method == self.METHOD_GET:
            resp = requests.get(url, headers=self.headers, params=params, proxies=proxy)
        elif method == self.METHOD_POST:
            resp = requests.post(url, headers=self.headers, data=params, proxies=proxy)
            
        if resp.status_code == 200:
            data = resp.json()
            if data["response"]["executed"] is True:
                callback(data, reqid)
                return
            self.onError(data["response"]["error"], reqid)
        else:
            self.onError(u'HTTP请求失败，错误代码%s' %resp.status_code)
        
    #----------------------------------------------------------------------
    def getInstruments(self):
        """查询合约代码"""
        uri = '/trading/get_instruments'
        reqid = self.sendReq(self.METHOD_GET, uri, {}, self.onGetInstruments)
        return reqid
    
    #----------------------------------------------------------------------
    def getModel(self, model):
        """查询表"""
        uri = '/trading/get_model'
        params = {'models': model}
        reqid = self.sendReq(self.METHOD_GET, uri, params, self.onGetTable)
        return reqid    
    
    #----------------------------------------------------------------------
    def subscribe(self, symbol):
        """订阅行情"""
        uri = '/subscribe'
        params = {'pairs': symbol}
        reqid = self.sendReq(self.METHOD_POST, uri, params, self.onSubscribe)
        self.sio.on(symbol, self.onPriceUpdate)
        return reqid
    
    #----------------------------------------------------------------------
    def unsubscribe(self, symbol):
        """退订行情"""
        uri = '/unsubscribe'
        params = {'pairs': symbol}
        reqid = self.sendReq(self.METHOD_POST, uri, params, self.onUnsubscribe)
        return reqid    
    
    #----------------------------------------------------------------------
    def subscribeModel(self, model):
        """订阅表"""
        uri = '/trading/subscribe'
        params = {'models': model}
        reqid = self.sendReq(self.METHOD_POST, uri, params, self.onSubscribeModel)
        self.sio.on(model, self.onModelUpdate)
        return reqid
    
    #----------------------------------------------------------------------
    def unsubscribeModel(self, model):
        """退订表"""
        uri = '/trading/unsubscribe'
        params = {'models': model}
        reqid = self.sendReq(self.METHOD_POST, uri, params, self.onUnsubscribeModel)
        return reqid     
    
    #----------------------------------------------------------------------
    def openTrade(self, accountID, symbol, isBuy, amount, limit, 
                  isInPips, atMarket, orderType, timeInForce,
                  rate=0, stop=0, trailingStep=0):
        """开仓交易"""
        uri = '/trading/open_trade'
        params = {
            'account_id': accountID,
            'symbol': symbol,
            'is_buy': isBuy,
            'amount': amount,
            'limit': limit,
            'is_in_pips': isInPips,
            'at_market': atMarket,
            'order_type': orderType,
            'time_in_force': timeInForce
        }
        
        if rate:
            params['rate'] = rate
            
        if stop:
            params['stop'] = stop
            
        if trailingStep:
            params['trailing_step'] = trailingStep
        
        reqid = self.sendReq(self.METHOD_POST, uri, params, self.onOpenTrade)
        return reqid       
    
    #----------------------------------------------------------------------
    def closeTrade(self, tradeID, amount, atMarket, orderType, timeInForce, rate=0):
        """平仓交易"""
        uri = '/trading/close_trade'
        params = {
            'trade_id': tradeID,
            'amount': amount,
            'at_market': atMarket,
            'order_type': orderType,
            'time_in_force': timeInForce
        }
        
        if rate:
            params['rate'] = rate

        reqid = self.sendReq(self.METHOD_POST, uri, params, self.onCloseTrade)
        return reqid        
    
    #----------------------------------------------------------------------
    def changeOrder(self, orderID, rate, range_, amount, trailingStep=0):
        """修改委托"""
        uri = '/trading/change_order'
        params = {
            'order_id': orderID,
            'rate': rate,
            'range': range_,
            'amount': amount
        }
        
        if trailingStep:
            params['trailing_step'] = trailingStep
        
        reqid = self.sendReq(self.METHOD_POST, uri, params, self.onChangeOrder)
        return reqid 
    
    #----------------------------------------------------------------------
    def deleteOrder(self, orderID):
        """撤销委托"""
        uri = '/trading/delete_order'
        params = {'order_id': orderID}
        reqid = self.sendReq(self.METHOD_POST, uri, params, self.onDeleteOrder)
        return reqid    
    
    #----------------------------------------------------------------------
    def onConnect(self):
        """连接回调"""
        print 'onConnect'
        
    #----------------------------------------------------------------------
    def onDisconnect(self):
        """断开回调"""
        print 'onClose'
        
    #----------------------------------------------------------------------
    def onError(self, error, reqid):
        """错误回调"""
        print 'onError', error
    
    #----------------------------------------------------------------------
    def onGetInstruments(self, data, reqid):
        """查询合约代码回调"""
        print data, reqid
        
    #----------------------------------------------------------------------
    def onGetTable(self, data, reqid):
        """查询表回调"""
        print data, reqid        
        
    #----------------------------------------------------------------------
    def onSubscribe(self, data, reqid):	
        """订阅行情回调"""
        print data, reqid    
    
    #----------------------------------------------------------------------
    def onUnsubscribe(self, data, reqid):
        """退订行情回调"""
        print data, reqid 
        
    #----------------------------------------------------------------------
    def onSubscribeModel(self, data, reqid):
        """订阅表回调"""
        print data, reqid    
    
    #----------------------------------------------------------------------
    def onUnsubscribeModel(self, data, reqid):
        """退订表回调"""
        print data, reqid   
        
    #----------------------------------------------------------------------
    def onOpenTrade(self, data, reqid):
        """开仓回调"""
        print data, reqid
        
    #----------------------------------------------------------------------
    def onCloseTrade(self, data, reqid):
        """平仓回调"""
        print data, reqid 
        
    #----------------------------------------------------------------------
    def onChangeOrder(self, data, reqid):
        """改单回调"""
        print data, reqid       

    #----------------------------------------------------------------------
    def onDeleteOrder(self, data, reqid):
        """撤单回调"""
        print data, reqid       
    
    #----------------------------------------------------------------------
    def onPriceUpdate(self, data):
        """行情推送"""
        print data
        
    #----------------------------------------------------------------------
    def onModelUpdate(self, data):
        """表推送"""
        print data    

    