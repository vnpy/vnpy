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
TRADING_SYMBOL_LTS = 'ltc_'

# 委托类型
TYPE_BUY = 'buy'
TYPE_SELL = 'sell'
TYPE_BUY_MARKET = 'buy_market'
TYPE_SELL_MARKET = 'sell_market'


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
    def sendMarketDataRequest(self, channel):
        """发送行情请求"""
        # 生成请求
        d = {}
        d['event'] = 'addChannel'
        d['binary'] = True
        d['channel'] = channel
        
        # 使用json打包并发送
        j = json.dumps(d)
        self.ws.send(j)
        
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
        self.ws.send(j)    
        
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
        params['symbol'] = str(symbol)
        params['type'] = str(type_+self.currency)
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
        
        channel = 'ok_spot%s_orderinfo'
        
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
        

if __name__ == "__main__":
    # 在OkCoin网站申请这两个Key，分别对应用户名和密码
    apiKey = ''
    secretKey = ''
    
    # 创建API对象
    api = OkCoinApi()
    
    # 连接服务器，并等待1秒
    api.connect(OKCOIN_CNY, apiKey, secretKey, True)
    
    sleep(1)
    
    # 测试现货行情API
    #api.subscribeSpotTicker(SYMBOL_BTC)
    #api.subscribeSpotTradeData(SYMBOL_BTC)
    #api.subscribeSpotDepth(SYMBOL_BTC, DEPTH_20)
    #api.subscribeSpotKline(SYMBOL_BTC, INTERVAL_1M)
    
    # 测试现货交易API
    #api.subscribeSpotTrades()
    #api.subscribeSpotUserInfo()
    api.spotUserInfo()
    #api.spotTrade(symbol, type_, price, amount)
    #api.spotCancelOrder(symbol, orderid)
    #api.spotOrderInfo(symbol, orderid)
    
    raw_input()