# encoding: utf-8

import urllib
import hashlib

import json
import requests
from time import time, sleep
from Queue import Queue, Empty
from threading import Thread


# 常量定义
COINTYPE_BTC = 1
COINTYPE_LTC = 2

ACCOUNTTYPE_CNY = 1
ACCOUNTTYPE_USD = 2

LOANTYPE_CNY = 1
LOANTYPE_BTC = 2
LOANTYPE_LTC = 3
LOANTYPE_USD = 4

MARKETTYPE_CNY = 'cny'
MARKETTYPE_USD = 'usd'

SYMBOL_BTCCNY = 'BTC_CNY'
SYMBOL_LTCCNY = 'LTC_CNY'
SYMBOL_BTCUSD = 'BTC_USD'

PERIOD_1MIN = '001'
PERIOD_5MIN = '005'
PERIOD_15MIN = '015'
PERIOD_30MIN = '030'
PERIOD_60MIN = '060'
PERIOD_DAILY = '100'
PERIOD_WEEKLY = '200'
PERIOD_MONTHLY = '300'
PERIOD_ANNUALLY = '400'

# API相关定义
HUOBI_TRADE_API = 'https://api.huobi.com/apiv3'

# 功能代码
FUNCTIONCODE_GETACCOUNTINFO = 'get_account_info'
FUNCTIONCODE_GETORDERS = 'get_orders'
FUNCTIONCODE_ORDERINFO = 'order_info'
FUNCTIONCODE_BUY = 'buy'
FUNCTIONCODE_SELL = 'sell'
FUNCTIONCODE_BUYMARKET = 'buy_market'
FUNCTIONCODE_SELLMARKET = 'sell_market'
FUNCTIONCODE_CANCELORDER = 'cancel_order'
FUNCTIONCODE_GETNEWDEALORDERS = 'get_new_deal_orders'
FUNCTIONCODE_GETORDERIDBYTRADEID = 'get_order_id_by_trade_id'
FUNCTIONCODE_WITHDRAWCOIN = 'withdraw_coin'
FUNCTIONCODE_CANCELWITHDRAWCOIN = 'cancel_withdraw_coin'
FUNCTIONCODE_GETWITHDRAWCOINRESULT = 'get_withdraw_coin_result'
FUNCTIONCODE_TRANSFER = 'transfer'
FUNCTIONCODE_LOAN = 'loan'
FUNCTIONCODE_REPAYMENT = 'repayment'
FUNCTIONCODE_GETLOANAVAILABLE = 'get_loan_available'
FUNCTIONCODE_GETLOANS = 'get_loans'


#----------------------------------------------------------------------
def signature(params):
    """生成签名"""
    params = sorted(params.iteritems(), key=lambda d:d[0], reverse=False)
    message = urllib.urlencode(params)
    
    m = hashlib.md5()
    m.update(message)
    m.digest()

    sig=m.hexdigest()
    return sig    
    

########################################################################
class TradeApi(object):
    """交易接口"""
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
    
    #----------------------------------------------------------------------
    def processRequest(self, req):
        """处理请求"""
        # 读取方法和参数
        method = req['method']
        params = req['params']
        optional = req['optional']
        
        # 在参数中增加必须的字段
        params['created'] = long(time())
        params['access_key'] = self.accessKey
        params['secret_key'] = self.secretKey
        params['method'] = method
        
        # 添加签名
        sign = signature(params)
        params['sign'] = sign
        del params['secret_key']
        
        # 添加选填参数
        if optional:
            params.update(optional)
        
        # 发送请求
        payload = urllib.urlencode(params)

        r = requests.post(HUOBI_TRADE_API, params=payload)
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
    def sendRequest(self, method, params, callback, optional=None):
        """发送请求"""
        # 请求编号加1
        self.reqID += 1
        
        # 生成请求字典并放入队列中
        req = {}
        req['method'] = method
        req['params'] = params
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
    
    #----------------------------------------------------------------------
    def getAccountInfo(self, market='cny'):
        """查询账户"""
        method = FUNCTIONCODE_GETACCOUNTINFO
        params = {}
        callback = self.onGetAccountInfo
        optional = {'market': market}
        return self.sendRequest(method, params, callback, optional)
    
    #----------------------------------------------------------------------
    def getOrders(self, coinType=COINTYPE_BTC, market='cny'):
        """查询委托"""
        method = FUNCTIONCODE_GETORDERS
        params = {'coin_type': coinType}
        callback = self.onGetOrders
        optional = {'market': market}
        return self.sendRequest(method, params, callback, optional)
        
    #----------------------------------------------------------------------
    def orderInfo(self, id_, coinType=COINTYPE_BTC, market='cny'):
        """获取委托详情"""
        method = FUNCTIONCODE_ORDERINFO
        params = {
            'coin_type': coinType,
            'id': id_
        }
        callback = self.onOrderInfo
        optional = {'market': market}
        return self.sendRequest(method, params, callback, optional)
    
    #----------------------------------------------------------------------
    def buy(self, price, amount, coinType=COINTYPE_BTC, 
            tradePassword='', tradeId = '', market='cny'):
        """委托买入"""
        method = FUNCTIONCODE_BUY
        params = {
            'coin_type': coinType,
            'price': price,
            'amount': amount
        }
        callback = self.onBuy
        optional = {
            'trade_password': tradePassword,
            'trade_id': tradeId,
            'market': market
        }
        return self.sendRequest(method, params, callback, optional)

    #----------------------------------------------------------------------
    def sell(self, price, amount, coinType=COINTYPE_BTC, 
            tradePassword='', tradeId = '', market='cny'):
        """委托卖出"""
        method = FUNCTIONCODE_SELL
        params = {
            'coin_type': coinType,
            'price': price,
            'amount': amount
        }
        callback = self.onSell
        optional = {
            'trade_password': tradePassword,
            'trade_id': tradeId,
            'market': market
        }
        return self.sendRequest(method, params, callback, optional)
    
    #----------------------------------------------------------------------
    def buyMarket(self, amount, coinType=COINTYPE_BTC, 
                  tradePassword='', tradeId = '', market='cny'):
        """市价买入"""
        method = FUNCTIONCODE_BUYMARKET
        params = {
            'coin_type': coinType,
            'amount': amount
        }
        callback = self.onBuyMarket
        optional = {
            'trade_password': tradePassword,
            'trade_id': tradeId,
            'market': market
        }
        return self.sendRequest(method, params, callback, optional) 
    
    #----------------------------------------------------------------------
    def sellMarket(self, amount, coinType=COINTYPE_BTC, 
                  tradePassword='', tradeId = '', market='cny'):
        """市价卖出"""
        method = FUNCTIONCODE_SELLMARKET
        params = {
            'coin_type': coinType,
            'amount': amount
        }
        callback = self.onSellMarket
        optional = {
            'trade_password': tradePassword,
            'trade_id': tradeId,
            'market': market
        }
        return self.sendRequest(method, params, callback, optional)      
    
    #----------------------------------------------------------------------
    def cancelOrder(self, id_, coinType=COINTYPE_BTC, market='cny'):
        """撤销委托"""
        method = FUNCTIONCODE_CANCELORDER
        params = {
            'coin_type': coinType,
            'id': id_
        }
        callback = self.onCancelOrder
        optional = {'market': market}
        return self.sendRequest(method, params, callback, optional)    

    #----------------------------------------------------------------------
    def getNewDealOrders(self, market='cny'):
        """查询最新10条成交"""
        method = FUNCTIONCODE_GETNEWDEALORDERS
        params = {}
        callback = self.onGetNewDealOrders
        optional = {'market': market}
        return self.sendRequest(method, params, callback, optional)
    
    #----------------------------------------------------------------------
    def getOrderIdByTradeId(self, tradeId, coinType=COINTYPE_BTC, 
                            market='cny'):
        """通过成交编号查询委托编号"""
        method = FUNCTIONCODE_GETORDERIDBYTRADEID
        params = {
            'coin_type': coinType,
            'trade_id': tradeId
        }
        callback = self.onGetOrderIdByTradeId
        optional = {'market': market}
        return self.sendRequest(method, params, callback, optional) 
    
    #----------------------------------------------------------------------
    def withdrawCoin(self, withdrawAddress, withdrawAmount,
                     coinType=COINTYPE_BTC, tradePassword='',
                     market='cny', withdrawFee=0.0001):
        """提币"""
        method = FUNCTIONCODE_WITHDRAWCOIN
        params = {
            'coin_type': coinType,
            'withdraw_address': withdrawAddress,
            'withdraw_amount': withdrawAmount
        }
        callback = self.onWithdrawCoin
        optional = {
            'market': market,
            'withdraw_fee': withdrawFee
        }
        return self.sendRequest(method, params, callback, optional)  
    
    #----------------------------------------------------------------------
    def cancelWithdrawCoin(self, id_, market='cny'):
        """取消提币"""
        method = FUNCTIONCODE_CANCELWITHDRAWCOIN
        params = {'withdraw_coin_id': id_}
        callback = self.onCancelWithdrawCoin
        optional = {'market': market}
        return self.sendRequest(method, params, callback, optional)         
    
    #----------------------------------------------------------------------
    def onGetWithdrawCoinResult(self, id_, market='cny'):
        """查询提币结果"""
        method = FUNCTIONCODE_GETWITHDRAWCOINRESULT
        params = {'withdraw_coin_id': id_}
        callback = self.onGetWithdrawCoinResult
        optional = {'market': market}
        return self.sendRequest(method, params, callback, optional)         
    
    #----------------------------------------------------------------------
    def transfer(self, amountFrom, amountTo, amount, 
                 coinType=COINTYPE_BTC ):
        """账户内转账"""
        method = FUNCTIONCODE_TRANSFER
        params = {
            'amount_from': amountFrom,
            'amount_to': amountTo,
            'amount': amount,
            'coin_type': coinType
        }
        callback = self.onTransfer
        optional = {}
        return self.sendRequest(method, params, callback, optional)          
        
    #----------------------------------------------------------------------
    def loan(self, amount, loan_type=LOANTYPE_CNY, 
             market=MARKETTYPE_CNY):
        """申请杠杆"""
        method = FUNCTIONCODE_LOAN
        params = {
            'amount': amount,
            'loan_type': loan_type
        }
        callback = self.onLoan
        optional = {'market': market}
        return self.sendRequest(method, params, callback, optional)
    
    #----------------------------------------------------------------------
    def repayment(self, id_, amount, repayAll=0,
                  market=MARKETTYPE_CNY):
        """归还杠杆"""
        method = FUNCTIONCODE_REPAYMENT
        params = {
            'loan_id': id_,
            'amount': amount
        }
        callback = self.onRepayment
        optional = {
            'repay_all': repayAll,
            'market': market
        }
        return self.sendRequest(method, params, callback, optional)
    
    #----------------------------------------------------------------------
    def getLoanAvailable(self, market='cny'):
        """查询杠杆额度"""
        method = FUNCTIONCODE_GETLOANAVAILABLE
        params = {}
        callback = self.onLoanAvailable
        optional = {'market': market}
        return self.sendRequest(method, params, callback, optional)
    
    #----------------------------------------------------------------------
    def getLoans(self, market='cny'):
        """查询杠杆列表"""
        method = FUNCTIONCODE_GETLOANS
        params = {}
        callback = self.onGetLoans
        optional = {'market': market}
        return self.sendRequest(method, params, callback, optional)    
    
    ####################################################
    ## 回调函数
    ####################################################
    
    #----------------------------------------------------------------------
    def onError(self, error, req, reqID):
        """错误推送"""
        print error, reqID    

    #----------------------------------------------------------------------
    def onGetAccountInfo(self, data, req, reqID):
        """查询账户回调"""
        print data
    
    #----------------------------------------------------------------------
    def onGetOrders(self, data, req, reqID, fuck):
        """查询委托回调"""
        print data
        
    #----------------------------------------------------------------------
    def onOrderInfo(self, data, req, reqID):
        """委托详情回调"""
        print data

    #----------------------------------------------------------------------
    def onBuy(self, data, req, reqID):
        """买入回调"""
        print data
        
    #----------------------------------------------------------------------
    def onSell(self, data, req, reqID):
        """卖出回调"""
        print data    
        
    #----------------------------------------------------------------------
    def onBuyMarket(self, data, req, reqID):
        """市价买入回调"""
        print data
        
    #----------------------------------------------------------------------
    def onSellMarket(self, data, req, reqID):
        """市价卖出回调"""
        print data        
        
    #----------------------------------------------------------------------
    def onCancelOrder(self, data, req, reqID):
        """撤单回调"""
        print data
    
    #----------------------------------------------------------------------
    def onGetNewDealOrders(self, data, req, reqID):
        """查询最新成交回调"""
        print data    
        
    #----------------------------------------------------------------------
    def onGetOrderIdByTradeId(self, data, req, reqID):
        """通过成交编号查询委托编号回调"""
        print data    
        
    #----------------------------------------------------------------------
    def onWithdrawCoin(self, data, req, reqID):
        """提币回调"""
        print data
        
    #----------------------------------------------------------------------
    def onCancelWithdrawCoin(self, data, req, reqID):
        """取消提币回调"""
        print data      
        
    #----------------------------------------------------------------------
    def onGetWithdrawCoinResult(self, data, req, reqID):
        """查询提币结果回调"""
        print data           
        
    #----------------------------------------------------------------------
    def onTransfer(self, data, req, reqID):
        """转账回调"""
        print data
        
    #----------------------------------------------------------------------
    def onLoan(self, data, req, reqID):
        """申请杠杆回调"""
        print data      
        
    #----------------------------------------------------------------------
    def onRepayment(self, data, req, reqID):
        """归还杠杆回调"""
        print data    
    
    #----------------------------------------------------------------------
    def onLoanAvailable(self, data, req, reqID):
        """查询杠杆额度回调"""
        print data      
        
    #----------------------------------------------------------------------
    def onGetLoans(self, data, req, reqID):
        """查询杠杆列表"""
        print data        
        

########################################################################
class DataApi(object):
    """行情接口"""
    TICK_SYMBOL_URL = {
        SYMBOL_BTCCNY: 'http://api.huobi.com/staticmarket/detail_btc_json.js',
        SYMBOL_LTCCNY: 'http://api.huobi.com/staticmarket/detail_ltc_json.js',
        SYMBOL_BTCUSD: 'http://api.huobi.com/usdmarket/detail_btc_json.js'
    }
    
    QUOTE_SYMBOL_URL = {
        SYMBOL_BTCCNY: 'http://api.huobi.com/staticmarket/ticker_btc_json.js',
        SYMBOL_LTCCNY: 'http://api.huobi.com/staticmarket/ticker_ltc_json.js',
        SYMBOL_BTCUSD: 'http://api.huobi.com/usdmarket/ticker_btc_json.js'
    }  
    
    DEPTH_SYMBOL_URL = {
        SYMBOL_BTCCNY: 'http://api.huobi.com/staticmarket/depth_btc_json.js',
        SYMBOL_LTCCNY: 'http://api.huobi.com/staticmarket/depth_ltc_json.js',
        SYMBOL_BTCUSD: 'http://api.huobi.com/usdmarket/depth_btc_json.js'
    }    
    
    KLINE_SYMBOL_URL = {
        SYMBOL_BTCCNY: 'http://api.huobi.com/staticmarket/btc_kline_[period]_json.js',
        SYMBOL_LTCCNY: 'http://api.huobi.com/staticmarket/btc_kline_[period]_json.js',
        SYMBOL_BTCUSD: 'http://api.huobi.com/usdmarket/btc_kline_[period]_json.js'
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
    def subscribeQuote(self, symbol):
        """订阅实时报价数据"""
        url = self.QUOTE_SYMBOL_URL[symbol]
        task = (url, self.onQuote)
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
    def onQuote(self, data):
        """实时报价推送"""
        print data    
    
    #----------------------------------------------------------------------
    def onDepth(self, data):
        """实时深度推送"""
        print data        

    #----------------------------------------------------------------------
    def getKline(self, symbol, period, length=0):
        """查询K线数据"""
        url = self.KLINE_SYMBOL_URL[symbol]
        url = url.replace('[period]', period)
        
        if length:
            url = url + '?length=' + str(length)
            
        try:
            r = requests.get(url)
            if r.status_code == 200:
                data = r.json()
                return data
        except Exception, e:
            print e
            return None