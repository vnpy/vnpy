# encoding: utf-8

import urllib
import hashlib

import requests
from Queue import Queue, Empty
from threading import Thread
from time import sleep



API_ROOT ="https://api.lbank.info/v1/"

FUNCTION_TICKER = ('ticker.do', 'get')
FUNCTION_DEPTH = ('depth.do', 'get')
FUNCTION_TRADES = ('trades.do', 'get')
FUNCTION_KLINE = ('kline.do', 'get')

FUNCTION_USERINFO = ('user_info.do', 'post')
FUNCTION_CREATEORDER = ('create_order.do', 'post')
FUNCTION_CANCELORDER = ('cancel_order.do', 'post')
FUNCTION_ORDERSINFO = ('orders_info.do', 'post')
FUNCTION_ORDERSINFOHISTORY = ('orders_info_history.do', 'post')


#----------------------------------------------------------------------
def signature(params, secretKey):
    """生成签名"""
    params = sorted(params.iteritems(), key=lambda d:d[0], reverse=False)
    params.append(('secret_key', secretKey))
    message = urllib.urlencode(params)
    
    m = hashlib.md5()
    m.update(message)
    m.digest()

    sig=m.hexdigest()
    return sig    
    

########################################################################
class LbankApi(object):
    """"""
    DEBUG = True

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''
        self.secretKey = ''

        self.interval = 1           # 每次请求的间隔等待
        self.active = False         # API工作状态   
        self.reqID = 0              # 请求编号
        self.reqQueue = Queue()     # 请求队列
        self.reqThread = Thread(target=self.processQueue)   # 请求处理线程        
    
    #----------------------------------------------------------------------
    def init(self, apiKey, secretKey, interval):
        """初始化"""
        self.apiKey = apiKey
        self.secretKey = secretKey
        self.interval = interval
        
        self.active = True
        self.reqThread.start()
        
    #----------------------------------------------------------------------
    def exit(self):
        """退出"""
        self.active = False
        
        if self.reqThread.isAlive():
            self.reqThread.join()
    
    #----------------------------------------------------------------------
    def processRequest(self, req):
        """处理请求"""
        # 读取方法和参数
        api, method = req['function']
        params = req['params']
        url = API_ROOT + api
        
        # 在参数中增加必须的字段
        params['api_key'] = self.apiKey
        
        # 添加签名
        sign = signature(params, self.secretKey)
        params['sign'] = sign
        
        # 发送请求
        payload = urllib.urlencode(params)
    
        r = requests.request(method, url, params=payload)
        if r.status_code == 200:
            data = r.json()
            return data
        else:
            return None        
    
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
                if data is None:
                    error = u'请求失败'
                    self.onError(error, req, reqID)
                elif 'error_code' in data:
                    error = u'请求出错，错误代码：%s' % data['error_code']
                    self.onError(error, req, reqID)
                # 请求成功
                else:
                    if self.DEBUG:
                        print callback.__name__                        
                    callback(data, req, reqID)

                # 流控等待
                sleep(self.interval)
                
            except Empty:
                pass    
            
    #----------------------------------------------------------------------
    def sendRequest(self, function, params, callback):
        """发送请求"""
        # 请求编号加1
        self.reqID += 1
        
        # 生成请求字典并放入队列中
        req = {}
        req['function'] = function
        req['params'] = params
        req['callback'] = callback
        req['reqID'] = self.reqID
        self.reqQueue.put(req)
        
        # 返回请求编号
        return self.reqID
    
    #----------------------------------------------------------------------
    def onError(self, error, req, reqID):
        """错误推送"""
        print error, req, reqID

    ###############################################
    # 行情接口
    ###############################################
    
    #----------------------------------------------------------------------
    def getTicker(self, symbol):
        """查询行情"""
        function = FUNCTION_TICKER
        params = {'symbol': symbol}
        callback = self.onGetTicker
        return self.sendRequest(function, params, callback)

    # ----------------------------------------------------------------------
    def getDepth(self, symbol, size, merge):
        """查询深度"""
        function = FUNCTION_DEPTH
        params = {
            'symbol': symbol,
            'size': size,
            'mege': merge
        }
        callback = self.onGetDepth
        return self.sendRequest(function, params, callback)

    # ----------------------------------------------------------------------
    def getTrades(self, symbol, size, time):
        """查询历史成交"""
        function = FUNCTION_TRADES
        params = {
            'symbol': symbol,
            'size': size,
            'time': time
        }
        callback = self.onGetTrades
        return self.sendRequest(function, params, callback)

    # ----------------------------------------------------------------------
    def getKline(self, symbol, size, type_, time):
        """查询K线"""
        function = FUNCTION_KLINE
        params = {
            'symbol': symbol,
            'size': size,
            'type': type_,
            'time': time
        }
        callback = self.onGetKline
        return self.sendRequest(function, params, callback)

    #----------------------------------------------------------------------
    def onGetTicker(self, data, req, reqID):
        """查询行情回调"""
        print data, reqID

    # ----------------------------------------------------------------------
    def onGetDepth(self, data, req, reqID):
        """查询深度回调"""
        print data, reqID

    # ----------------------------------------------------------------------
    def onGetTrades(self, data, req, reqID):
        """查询历史成交"""
        print data, reqID

    # ----------------------------------------------------------------------
    def onGetKline(self, data, req, reqID):
        """查询Ｋ线回报"""
        print data, reqID

    ###############################################
    # 交易接口
    ###############################################

    # ----------------------------------------------------------------------
    def getUserInfo(self):
        """查询账户信息"""
        function = FUNCTION_USERINFO
        params = {}
        callback = self.onGetUserInfo
        return self.sendRequest(function, params, callback)

    # ----------------------------------------------------------------------
    def createOrder(self, symbol, type_, price, amount):
        """发送委托"""
        function = FUNCTION_CREATEORDER
        params = {
            'symbol': symbol,
            'type': type_,
            'price': price,
            'amount': amount
        }
        callback = self.onCreateOrder
        return self.sendRequest(function, params, callback)

    # ----------------------------------------------------------------------
    def cancelOrder(self, symbol, orderId):
        """撤单"""
        function = FUNCTION_CANCELORDER
        params = {
            'symbol': symbol,
            'order_id': orderId
        }
        callback = self.onCancelOrder
        return self.sendRequest(function, params, callback)

    # ----------------------------------------------------------------------
    def getOrdersInfo(self, symbol, orderId):
        """查询委托"""
        function = FUNCTION_ORDERSINFO
        params = {
            'symbol': symbol,
            'order_id': orderId
        }
        callback = self.onGetOrdersInfo
        return self.sendRequest(function, params, callback)

    # ----------------------------------------------------------------------
    def getOrdersInfoHistory(self, symbol, status, currentPage, pageLength):
        """撤单"""
        function = FUNCTION_ORDERSINFOHISTORY
        params = {
            'symbol': symbol,
            'status': status,
            'current_page': currentPage,
            'page_length': pageLength
        }
        callback = self.onGetOrdersInfoHistory
        return self.sendRequest(function, params, callback)

    # ----------------------------------------------------------------------
    def onGetUserInfo(self, data, req, reqID):
        """查询账户信息"""
        print data, reqID

    # ----------------------------------------------------------------------
    def onCreateOrder(self, data, req, reqID):
        """委托回报"""
        print data, reqID

    # ----------------------------------------------------------------------
    def onCancelOrder(self, data, req, reqID):
        """撤单回报"""
        print data, reqID

    # ----------------------------------------------------------------------
    def onGetOrdersInfo(self, data, req, reqID):
        """查询委托回报"""
        print data, reqID

    # ----------------------------------------------------------------------
    def onGetOrdersInfoHistory(self, data, req, reqID):
        """撤单回报"""
        print data, reqID

