# encoding: UTF-8

import hashlib
import zlib
import json
from time import sleep
from threading import Thread

import websocket    

# OKEX网站

OKEX_USD_SUB_SPOT = 'wss://real.okex.com:10441/websocket'       # OKEX 现货地址
OKEX_USD_CONTRACT = 'wss://real.okex.com:10440/websocket/okexapi'   # OKEX 期货地址

okex_all_symbol_type = ["usdt","btc","ltc","eth","etc","bch"]
okex_all_symbol_pairs = ["ltc_btc","eth_btc","etc_btc","bch_btc","btc_usdt","eth_usdt",\
        "ltc_usdt","etc_usdt","bch_usdt","etc_eth","bt1_btc","bt2_btc","btg_btc","qtum_btc",\
        "hsr_btc","neo_btc","gas_btc","qtum_usdt","hsr_usdt","neo_usdt","gas_usdt"]

# for test
# okex_all_symbol_pairs = ['etc_usdt']

okex_all_k_line_periods = ["1min","3min","5min","15min","30min","1hour","2hour","4hour","6hour","12hour","day","3day","week"]

okex_all_contract_symbol = ["btc","ltc","eth","bch"]
okex_all_contract_type = ["this_week","next_week","quarter"]

class OKEX_Sub_Spot_Api(object):
    """基于Websocket的API对象"""
    #----------------------------------------------------------------------
    def __init__(self):
      """Constructor"""
      self.apiKey = ''        # 用户名
      self.secretKey = ''     # 密码

      self.ws_sub_spot = None          # websocket应用对象  现货对象

      self.thread = None        # 线程初始化

    #----------------------------------------------------------------------
    def reconnect(self):
        """重新连接"""
        # 首先关闭之前的连接
        self.close()
        
        # 再执行重连任务
        self.ws_sub_spot = websocket.WebSocketApp(self.host, 
                                         on_message=self.onMessage,
                                         on_error=self.onError,
                                         on_close=self.onClose,
                                         on_open=self.onOpen)        
    
        self.thread = Thread(target=self.ws_sub_spot.run_forever)
        self.thread.start()
    
    #----------------------------------------------------------------------
    def connect_Subpot(self, apiKey , secretKey , trace = False):
        self.host = OKEX_USD_SUB_SPOT
        self.apiKey = apiKey
        self.secretKey = secretKey

        websocket.enableTrace(trace)

        self.ws_sub_spot = websocket.WebSocketApp(self.host, 
                                             on_message=self.onMessage,
                                             on_error=self.onError,
                                             on_close=self.onClose,
                                             on_open=self.onOpen)        
            
        self.thread = Thread(target=self.ws_sub_spot.run_forever)
        self.thread.start()

    #----------------------------------------------------------------------
    def readData(self, evt):
        """解压缩推送收到的数据"""
        # # 创建解压器
        # decompress = zlib.decompressobj(-zlib.MAX_WBITS)
        
        # # 将原始数据解压成字符串
        # inflated = decompress.decompress(evt) + decompress.flush()
        
        # 通过json解析字符串
        #data = json.loads(inflated)
        data = json.loads(evt)
        
        return data

    #----------------------------------------------------------------------
    def close(self):
        """关闭接口"""
        if self.thread and self.thread.isAlive():
            self.ws_sub_spot.close()
            self.thread.join()

    #----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """信息推送""" 
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
        print 'onOpen'

    #----------------------------------------------------------------------
    def subscribeSpotTicker(self, symbol_pair):
      # 现货的 ticker
        req = "{'event':'addChannel','channel':'ok_sub_spot_%s_ticker'}" % symbol_pair
        self.ws_sub_spot.send(req)

    #----------------------------------------------------------------------
    def subscribeSpotDepth(self, symbol_pair):
      # 现货的 市场深度
        req = "{'event':'addChannel','channel':'ok_sub_spot_%s_depth'}" % symbol_pair
        self.ws_sub_spot.send(req)

    #----------------------------------------------------------------------
    def subscribeSpotDepth5(self, symbol_pair):
      # 现货的 市场深度 5
        req = "{'event':'addChannel','channel':'ok_sub_spot_%s_depth_5'}" % symbol_pair
        self.ws_sub_spot.send(req)

    #----------------------------------------------------------------------
    def subscribeSpotDeals(self, symbol_pair):
        req = "{'event':'addChannel','channel':'ok_sub_spot_%s_deals'}" % symbol_pair
        self.ws_sub_spot.send(req)

    #----------------------------------------------------------------------
    def subscribeSpotKlines(self, symbol_pair , time_period):
        req = "{'event':'addChannel','channel':'ok_sub_spot_%s_kline_%s'}" % ( symbol_pair , time_period)
        self.ws_sub_spot.send(req)

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
    def sendTradingRequest(self, channel, params):
        """发送交易请求"""
        # 在参数字典中加上api_key和签名字段
        params['api_key'] = self.apiKey
        params['sign'] = self.generateSign(params)
        
        # 生成请求
        d = {}
        d['event'] = 'addChannel'
        d['channel'] = channel        
        d['parameters'] = params
        
        # 使用json打包并发送
        j = json.dumps(d)
        
        # 若触发异常则重连
        try:
            self.ws_sub_spot.send(j)
        except websocket.WebSocketConnectionClosedException:
            pass 

    #----------------------------------------------------------------------
    def spotTrade(self, symbol_pair, type_, price, amount):
        """现货委托"""
        params = {}
        params['symbol'] = str(symbol_pair)
        params['type'] = str(type_)
        params['price'] = str(price)
        params['amount'] = str(amount)
        
        channel = 'ok_spot_order'
        
        self.sendTradingRequest(channel, params)

    #----------------------------------------------------------------------
    def spotCancelOrder(self, symbol_pair, orderid):
        """现货撤单"""
        params = {}
        params['symbol'] = str(symbol_pair)
        params['order_id'] = str(orderid)
        
        channel = 'ok_spot_cancel_order'

        self.sendTradingRequest(channel, params)
    
    #----------------------------------------------------------------------
    def spotUserInfo(self):
        """查询现货账户"""
        channel = 'ok_spot_userinfo'
        self.sendTradingRequest(channel, {})

    #----------------------------------------------------------------------
    def spotOrderInfo(self, symbol_pair, orderid):
        """查询现货委托信息"""
        params = {}
        params['symbol'] = str(symbol_pair)
        params['order_id'] = str(orderid)
        
        channel = 'ok_spot_orderinfo'
        
        self.sendTradingRequest(channel, params)


    #----------------------------------------------------------------------
    # 这个 API 应该已经别废弃了
    # def subscribeSpotTrades(self , symbol_pair):
    #     """订阅现货成交信息"""
    #     channel = 'ok_sub_spot_%s_trades' % ( symbol_pair)
        
    #     self.sendTradingRequest(channel, {})

    #----------------------------------------------------------------------
    # 这个 API 应该已经别废弃了
    # def subscribeSpotUserInfo(self):
    #     """订阅现货账户信息"""
    #     channel = 'ok_sub_spot_userinfo' 
        
    #     self.sendTradingRequest(channel, {})

    #----------------------------------------------------------------------
    def login(self):
        params = {}
        params['api_key'] = self.apiKey
        params['sign'] = self.generateSign(params)
        
        # 生成请求
        d = {}
        d['event'] = 'login'
        d['parameters'] = params
        
        # 使用json打包并发送
        j = json.dumps(d)
        
        # 若触发异常则重连
        try:
            self.ws_sub_spot.send(j)
        except websocket.WebSocketConnectionClosedException:
            pass 


'''
OKEX 合约接口

[{
    "channel": "btc_forecast_price",
    "timestamp":"1490341322021",
    "data": "998.8"
}]
data(string): 预估交割价格
timestamp(string): 时间戳
操作说明
无需订阅，交割前一小时自动返回

这段数据，交割前会自动返回
'''
class OKEX_Contract_Api(object):
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''        # 用户名
        self.secretKey = ''     # 密码

        self.ws_contract = None          # websocket应用对象  期货对象


    #-----------------------------------------------------------------------
    def connect_Contract(self, apiKey , secretKey , trace = False):
        self.host = OKEX_USD_CONTRACT
        self.apiKey = apiKey
        self.secretKey = secretKey

        websocket.enableTrace(trace)

        self.ws_contract = websocket.WebSocketApp(self.host, 
                                           on_message=self.onMessage,
                                           on_error=self.onError,
                                           on_close=self.onClose,
                                           on_open=self.onOpen)        
          
        self.thread = Thread(target=self.ws_contract.run_forever)
        self.thread.start()

    #-----------------------------------------------------------------------
    #----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """信息推送""" 
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
        print 'onOpen'

    def subsribeFutureTicker(self, symbol , contract_type):
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_ticker_%s'}" % (symbol , contract_type)
        self.ws_contract.send(req)

    def subscribeFutureKline(self, symbol , contract_type , time_period):
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_kline_%s_%s'}" % (symbol , contract_type , time_period)
        self.ws_contract.send(req)

    def subscribeFutureDepth(self, symbol , contract_type):
        req = "{'event':'addChannel','channel':'ok_sub_future_%s_depth_%s_usd'}" % (symbol , contract_type )
        self.ws_contract.send(req)

    def subscribeFutureDepth20(self, symbol , contract_type):
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_depth_%s_20'}" % (symbol , contract_type)
        self.ws_contract.send(req)

    def subscribeFutureTrades(self, symbol , contract_type):
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_trade_%s'}" % (symbol , contract_type)
        self.ws_contract.send(req)

    def subscribeFutureIndex(self, symbol ):
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_index'}" % (symbol)
        self.ws_contract.send(req)

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
    def sendTradingRequest(self, channel, params):
        """发送交易请求"""
        # 在参数字典中加上api_key和签名字段
        params['api_key'] = self.apiKey
        params['sign'] = self.generateSign(params)
        
        # 生成请求
        d = {}
        d['event'] = 'addChannel'
        d['channel'] = channel        
        d['parameters'] = params
        
        # 使用json打包并发送
        j = json.dumps(d)
        
        # 若触发异常则重连
        try:
            self.ws_contract.send(j)
        except websocket.WebSocketConnectionClosedException:
            pass 

    #----------------------------------------------------------------------
    def login(self):
        params = {}
        params['api_key'] = self.apiKey
        params['sign'] = self.generateSign(params)
        
        # 生成请求
        d = {}
        d['event'] = 'login'
        d['parameters'] = params
        
        # 使用json打包并发送
        j = json.dumps(d)
        
        # 若触发异常则重连
        try:
            self.ws_contract.send(j)
        except websocket.WebSocketConnectionClosedException:
            pass 

    #----------------------------------------------------------------------
    def futureTrade(self, symbol_pair, contract_type ,type_, price, amount , _match_price = '0' , _lever_rate = '10'):
        """期货委托"""
        params = {}
        params['symbol'] = str(symbol_pair)
        params['contract_type'] = str(contract_type)
        params['price'] = str(price)
        params['amount'] = str(amount)
        params['type'] = type_                  # 1:开多 2:开空 3:平多 4:平空
        params['match_price'] = _match_price    # 是否为对手价： 0:不是 1:是 当取值为1时,price无效
        params['lever_rate'] = _lever_rate
        
        channel = 'ok_futureusd_trade'
        
        self.sendTradingRequest(channel, params)

    #----------------------------------------------------------------------
    def futureCancelOrder(self, symbol_pair, orderid , contract_type):
        """期货撤单"""
        params = {}
        params['symbol'] = str(symbol_pair)
        params['order_id'] = str(orderid)
        params['contract_type'] = str(contract_type)
        
        channel = 'ok_futureusd_cancel_order'

        self.sendTradingRequest(channel, params)

    #----------------------------------------------------------------------
    def futureUserInfo(self):
        """查询期货账户"""
        channel = 'ok_futureusd_userinfo'
        self.sendTradingRequest(channel, {})

    #----------------------------------------------------------------------
    def futureOrderInfo(self , symbol_pair , order_id , contract_type , status , current_page , page_length = 10):
        """查询期货委托"""
        params = {}
        params['symbol'] = str(symbol_pair)
        params['order_id'] = str(order_id)
        params['contract_type'] = str(contract_type)
        params['status'] = str(status)
        params['current_page'] = str(current_page)
        params['page_length'] = str(page_length)
        
        channel = 'ok_futureusd_orderinfo'
        
        self.sendTradingRequest(channel, params)

    #----------------------------------------------------------------------
    def subscribeFutureTrades( self):
        channel = 'ok_sub_futureusd_trades'
        self.sendTradingRequest(channel, {})

    #----------------------------------------------------------------------
    def subscribeFutureUserInfo(self):
        """订阅期货账户信息"""
        channel = 'ok_sub_futureusd_userinfo' 
        
        self.sendTradingRequest(channel, {})
        
    #----------------------------------------------------------------------
    def subscribeFuturePositions(self):
        """订阅期货持仓信息"""
        channel = 'ok_sub_futureusd_positions' 
        
        self.sendTradingRequest(channel, {})    
    