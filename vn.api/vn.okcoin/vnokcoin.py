# encoding: UTF-8

import hashlib
import zlib
import json
from time import sleep
from threading import Thread

import websocket    


# OKCOIN网站
OKCOIN_CNY = 'wss://real.okcoin.cn:10440/websocket/okcoinapi'
OKCOIN_USD = 'wss://real.okcoin.com:10440/websocket/okcoinapi'

# 账户货币代码
CURRENCY_CNY = 'cny'
CURRENCY_USD = 'usd'

# 电子货币代码
SYMBOL_BTC = 'btc'
SYMBOL_LTC = 'ltc'

# 行情深度
DEPTH_20 = 20
DEPTH_60 = 60

# K线时间区间
INTERVAL_1M = '1min'
INTERVAL_3M = '3min'
INTERVAL_5M = '5min'
INTERVAL_15M = '15min'
INTERVAL_30M = '30min'
INTERVAL_1H = '1hour'
INTERVAL_2H = '2hour'
INTERVAL_4H = '4hour'
INTERVAL_6H = '6hour'
INTERVAL_1D = 'day'
INTERVAL_3D = '3day'
INTERVAL_1W = 'week'

# 交易代码，需要后缀货币名才能完整
TRADING_SYMBOL_BTC = 'btc_'
TRADING_SYMBOL_LTC = 'ltc_'

# 委托类型
TYPE_BUY = 'buy'
TYPE_SELL = 'sell'
TYPE_BUY_MARKET = 'buy_market'
TYPE_SELL_MARKET = 'sell_market'

# 期货合约到期类型
FUTURE_EXPIRY_THIS_WEEK = 'this_week'
FUTURE_EXPIRY_NEXT_WEEK = 'next_week'
FUTURE_EXPIRY_QUARTER = 'quarter'

# 期货委托类型
FUTURE_TYPE_LONG = 1
FUTURE_TYPE_SHORT = 2
FUTURE_TYPE_SELL = 3
FUTURE_TYPE_COVER = 4

# 期货是否用现价
FUTURE_ORDER_MARKET = 1
FUTURE_ORDER_LIMIT = 0

# 期货杠杆
FUTURE_LEVERAGE_10 = 10
FUTURE_LEVERAGE_20 = 20

# 委托状态
ORDER_STATUS_NOTTRADED = 0
ORDER_STATUS_PARTTRADED = 1
ORDER_STATUS_ALLTRADED = 2
ORDER_STATUS_CANCELLED = -1
ORDER_STATUS_CANCELLING = 4


########################################################################
class OkCoinApi(object):
    """基于Websocket的API对象"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''        # 用户名
        self.secretKey = ''     # 密码
        self.host = ''          # 服务器地址
        
        self.currency = ''      # 货币类型（usd或者cny）
        
        self.ws = None          # websocket应用对象
        self.thread = None      # 工作线程
    
    #######################
    ## 通用函数
    #######################
    
    #----------------------------------------------------------------------
    def readData(self, evt):
        """解压缩推送收到的数据"""
        # 创建解压器
        decompress = zlib.decompressobj(-zlib.MAX_WBITS)
        
        # 将原始数据解压成字符串
        inflated = decompress.decompress(evt) + decompress.flush()
        
        # 通过json解析字符串
        data = json.loads(inflated)
        
        return data
    
    #----------------------------------------------------------------------
    def generateSign(self, params):
        """生成签名"""
        l = []
        for key in sorted(params.keys()):
            l.append('%s=%s' %(key, params[key]))
        l.append('secret_key=%s' %self.secretKey)
        sign = '&'.join(l)
        return hashlib.md5(sign.encode('utf-8')).hexdigest().upper()
    
    #----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """信息推送""" 
        print 'onMessage'
        data = self.readData(evt)
        print data
        
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
        print 'onOpen'
        
    #----------------------------------------------------------------------
    def connect(self, host, apiKey, secretKey, trace=False):
        """连接服务器"""
        self.host = host
        self.apiKey = apiKey
        self.secretKey = secretKey
        
        if self.host == OKCOIN_CNY:
            self.currency = CURRENCY_CNY
        else:
            self.currency = CURRENCY_USD
            
        websocket.enableTrace(trace)
        
        self.ws = websocket.WebSocketApp(host, 
                                         on_message=self.onMessage,
                                         on_error=self.onError,
                                         on_close=self.onClose,
                                         on_open=self.onOpen)        
        
        self.thread = Thread(target=self.ws.run_forever)
        self.thread.start()
        
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
    def close(self):
        """关闭接口"""
        if self.thread and self.thread.isAlive():
            self.ws.close()
            self.thread.join()
        
    #----------------------------------------------------------------------
    def sendMarketDataRequest(self, channel):
        """发送行情请求"""
        # 生成请求
        d = {}
        d['event'] = 'addChannel'
        d['binary'] = True
        d['channel'] = channel
        
        # 使用json打包并发送
        j = json.dumps(d)
        
        # 若触发异常则重连
        try:
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException:
            pass
        
    #----------------------------------------------------------------------
    def sendTradingRequest(self, channel, params):
        """发送交易请求"""
        # 在参数字典中加上api_key和签名字段
        params['api_key'] = self.apiKey
        params['sign'] = self.generateSign(params)
        
        # 生成请求
        d = {}
        d['event'] = 'addChannel'
        d['binary'] = True
        d['channel'] = channel        
        d['parameters'] = params
        
        # 使用json打包并发送
        j = json.dumps(d)
        
        # 若触发异常则重连
        try:
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException:
            pass 
    
    #######################
    ## 现货相关
    #######################        
    
    #----------------------------------------------------------------------
    def subscribeSpotTicker(self, symbol):
        """订阅现货普通报价"""
        self.sendMarketDataRequest('ok_sub_spot%s_%s_ticker' %(self.currency, symbol))
    
    #----------------------------------------------------------------------
    def subscribeSpotDepth(self, symbol, depth):
        """订阅现货深度报价"""
        self.sendMarketDataRequest('ok_sub_spot%s_%s_depth_%s' %(self.currency, symbol, depth))   
        
    #----------------------------------------------------------------------
    def subscribeSpotTradeData(self, symbol):
        """订阅现货成交记录"""
        self.sendMarketDataRequest('ok_sub_spot%s_%s_trades' %(self.currency, symbol))
        
    #----------------------------------------------------------------------
    def subscribeSpotKline(self, symbol, interval):
        """订阅现货K线"""
        self.sendMarketDataRequest('ok_sub_spot%s_%s_kline_%s' %(self.currency, symbol, interval))
        
    #----------------------------------------------------------------------
    def spotTrade(self, symbol, type_, price, amount):
        """现货委托"""
        params = {}
        params['symbol'] = str(symbol+self.currency)
        params['type'] = str(type_)
        params['price'] = str(price)
        params['amount'] = str(amount)
        
        channel = 'ok_spot%s_trade' %(self.currency)
        
        self.sendTradingRequest(channel, params)
        
    #----------------------------------------------------------------------
    def spotCancelOrder(self, symbol, orderid):
        """现货撤单"""
        params = {}
        params['symbol'] = str(symbol+self.currency)
        params['order_id'] = str(orderid)
        
        channel = 'ok_spot%s_cancel_order' %(self.currency)

        self.sendTradingRequest(channel, params)
        
    #----------------------------------------------------------------------
    def spotUserInfo(self):
        """查询现货账户"""
        channel = 'ok_spot%s_userinfo' %(self.currency)
        
        self.sendTradingRequest(channel, {})
        
    #----------------------------------------------------------------------
    def spotOrderInfo(self, symbol, orderid):
        """查询现货委托信息"""
        params = {}
        params['symbol'] = str(symbol+self.currency)
        params['order_id'] = str(orderid)
        
        channel = 'ok_spot%s_orderinfo' %(self.currency)
        
        self.sendTradingRequest(channel, params)
        
    #----------------------------------------------------------------------
    def subscribeSpotTrades(self):
        """订阅现货成交信息"""
        channel = 'ok_sub_spot%s_trades' %(self.currency)
        
        self.sendTradingRequest(channel, {})
        
    #----------------------------------------------------------------------
    def subscribeSpotUserInfo(self):
        """订阅现货账户信息"""
        channel = 'ok_sub_spot%s_userinfo' %(self.currency)
        
        self.sendTradingRequest(channel, {})
    
    #######################
    ## 期货相关
    #######################       
    
    #----------------------------------------------------------------------
    def subscribeFutureTicker(self, symbol, expiry):
        """订阅期货普通报价"""
        self.sendMarketDataRequest('ok_sub_future%s_%s_ticker_%s' %(self.currency, symbol, expiry))
    
    #----------------------------------------------------------------------
    def subscribeFutureDepth(self, symbol, expiry, depth):
        """订阅期货深度报价"""
        self.sendMarketDataRequest('ok_sub_future%s_%s_depth_%s_%s' %(self.currency, symbol, 
                                                                      expiry, depth))   
        
    #----------------------------------------------------------------------
    def subscribeFutureTradeData(self, symbol, expiry):
        """订阅期货成交记录"""
        self.sendMarketDataRequest('ok_sub_future%s_%s_trade_%s' %(self.currency, symbol, expiry))
        
    #----------------------------------------------------------------------
    def subscribeFutureKline(self, symbol, expiry, interval):
        """订阅期货K线"""
        self.sendMarketDataRequest('ok_sub_future%s_%s_kline_%s_%s' %(self.currency, symbol, 
                                                                      expiry, interval))
        
    #----------------------------------------------------------------------
    def subscribeFutureIndex(self, symbol):
        """订阅期货指数"""
        self.sendMarketDataRequest('ok_sub_future%s_%s_index' %(self.currency, symbol))
    
    #----------------------------------------------------------------------
    def futureTrade(self, symbol, expiry, type_, price, amount, order, leverage):
        """期货委托"""
        params = {}
        params['symbol'] = str(symbol+self.currency)
        params['type'] = str(type_)
        params['price'] = str(price)
        params['amount'] = str(amount)
        params['contract_type'] = str(expiry)
        params['match_price'] = str(order)
        params['lever_rate'] = str(leverage)
        
        channel = 'ok_future%s_trade' %(self.currency)
        
        self.sendTradingRequest(channel, params)
        
    #----------------------------------------------------------------------
    def futureCancelOrder(self, symbol, expiry, orderid):
        """期货撤单"""
        params = {}
        params['symbol'] = str(symbol+self.currency)
        params['order_id'] = str(orderid)
        params['contract_type'] = str(expiry)
        
        channel = 'ok_future%s_cancel_order' %(self.currency)

        self.sendTradingRequest(channel, params)
        
    #----------------------------------------------------------------------
    def futureUserInfo(self):
        """查询期货账户"""
        channel = 'ok_future%s_userinfo' %(self.currency)
        
        self.sendTradingRequest(channel, {})
        
    #----------------------------------------------------------------------
    def futureOrderInfo(self, symbol, expiry, orderid, status, page, length):
        """查询期货委托信息"""
        params = {}
        params['symbol'] = str(symbol+self.currency)
        params['order_id'] = str(orderid)
        params['contract_type'] = expiry
        params['status'] = status
        params['current_page'] = page
        params['page_length'] = length
        
        channel = 'ok_future%s_orderinfo' %(self.currency)
        
        self.sendTradingRequest(channel, params)
        
    #----------------------------------------------------------------------
    def subscribeFutureTrades(self):
        """订阅期货成交信息"""
        channel = 'ok_sub_future%s_trades' %(self.currency)
        
        self.sendTradingRequest(channel, {})
        
    #----------------------------------------------------------------------
    def subscribeFutureUserInfo(self):
        """订阅期货账户信息"""
        channel = 'ok_sub_future%s_userinfo' %(self.currency)
        
        self.sendTradingRequest(channel, {})
        
    #----------------------------------------------------------------------
    def subscribeFuturePositions(self):
        """订阅期货持仓信息"""
        channel = 'ok_sub_future%s_positions' %(self.currency)
        
        self.sendTradingRequest(channel, {})    
    

