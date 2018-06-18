# encoding: UTF-8

import hashlib
import zlib
import json
from time import sleep
from threading import Thread
import traceback
import websocket
import requests
import sys

# API文档 https://github.com/okcoin-okex/OKEx.com-api-docs

from vnpy.api.okex.okexData import SPOT_TRADE_SIZE_DICT,SPOT_REST_ERROR_DICT, FUTURES_ERROR_DICT

# OKEX网站
OKEX_USD_SPOT = 'wss://real.okex.com:10441/websocket'               # OKEX (币币交易）现货地址
OKEX_USD_CONTRACT = 'wss://real.okex.com:10440/websocket/okexapi'   # OKEX 期货地址

OKEX_CONTRACT_HOST = 'https://www.okex.com/api/v1/future_hold_amount.do?symbol=%s_usd&contract_type=%s'  # 合约持仓查询地址

SPOT_CURRENCY = ["usdt",
                 "btc",
                 "ltc",
                 "eth",
                 "etc",
                 "bch"]

SPOT_SYMBOL_PAIRS = set(["ltc_btc",
               "eth_btc",
               "etc_btc",
               "bch_btc",
               "btc_usdt",
               "eth_usdt",
               "ltc_usdt",
               "etc_usdt",
               "bch_usdt",
               "etc_eth",
               "bt1_btc",
               "bt2_btc",
               "btg_btc",
               "qtum_btc",
               "hsr_btc",
               "neo_btc",
               "gas_btc",
               "qtum_usdt",
               "hsr_usdt",
                     "neo_usdt",
                     "gas_usdt"])

KLINE_PERIOD = ["1min","3min","5min","15min","30min","1hour","2hour","4hour","6hour","12hour","day","3day","week"]

CONTRACT_SYMBOL = ["btc","ltc","eth","etc","bch","eos","xrp","btg"]

# 合约类型 ：    当周，下周，季度
CONTRACT_TYPE = ["this_week", "next_week", "quarter"]


########################################################################
class OkexApi(object):    
    """交易接口"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.host = ''          # 服务器
        self.apiKey = ''        # 用户名
        self.secretKey = ''     # 密码
  
        self.ws = None          # websocket应用对象  现货对象
        self.thread = None      # 初始化线程

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
    def connect(self, apiKey, secretKey, trace=False):
        """
        连接网关
        :param apiKey   : 申请的API key
        :param secretKey: 签名key
        :param trace    : 是否开启websocket的日志跟踪功能，输出到StreamHandler
        :return:
        """
        # 更新websocket服务器地址/API key/
        self.host = OKEX_USD_SPOT
        self.apiKey = apiKey
        self.secretKey = secretKey

        # 是否开启日志
        websocket.enableTrace(trace)

        # 创建websocket，绑定本地回调函数 onMessage/onError/onClose/onOpen
        self.ws = websocket.WebSocketApp(self.host, 
                                             on_message=self.onMessage,
                                             on_error=self.onError,
                                             on_close=self.onClose,
                                             on_open=self.onOpen)        
            
        self.thread = Thread(target=self.ws.run_forever)
        self.thread.start()

    #----------------------------------------------------------------------
    def readData(self, evt):
        """
        解码推送收到的数据
        :param evt:
        :return:
        """
        data = json.loads(evt)
        return data

    #----------------------------------------------------------------------
    def close(self):
        """
        关闭接口
        :return:
        """

        if self.thread and self.thread.isAlive():
            print(u'vnokex.close')
            self.ws.close()
            self.thread.join()

    #----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """
        信息推送事件
        :param ws:  接口
        :param evt: 事件
        :return:
        """
        print(u'vnokex.onMessage:{}'.format(evt))
        
    #----------------------------------------------------------------------
    def onError(self, ws, evt):
        """
        接口错误推送事件
        :param ws:
        :param evt:
        :return:
        """
        print(u'vnokex.onApiError:{}'.format(evt))

        
    #----------------------------------------------------------------------
    def onClose(self, ws):
        """
        接口断开事件
        :param ws:
        :return:
        """
        print(u'vnokex.onClose')
        
    #----------------------------------------------------------------------
    def onOpen(self, ws):
        """
        接口打开事件
        :param ws:
        :return:
        """
        print(u'vnokex.onOpen')
        
    #----------------------------------------------------------------------
    def generateSign(self, params):
        """生成签名"""
        #print(u'vnokex.generateSign')
        l = []
        for key in sorted(params.keys()):
            l.append('%s=%s' %(key, params[key]))
        l.append('secret_key=%s' %self.secretKey)
        sign = '&'.join(l)
        return hashlib.md5(sign.encode('utf-8')).hexdigest().upper()

    #----------------------------------------------------------------------
    def sendRequest(self, channel, params):
        """发送指令请求"""
        print(u'vnokex.sendRequest:{}'.format(channel))
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
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'vnokex.sendTradingRequest Exception:{}'.format(str(ex)),file=sys.stderr)

    #----------------------------------------------------------------------
    def sendDataRequest(self, channel):
        """发送数据请求"""
        print(u'vnokex.sendDataRequest:{}'.format(channel))
        d = {}
        d['event'] = 'addChannel'
        d['channel'] = channel
        j = json.dumps(d)
        
        # 若触发异常则重连
        try:
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'vnokex.sendDataRequest Exception:{},{}'.format(str(ex),traceback.format_exc()), file=sys.stderr)
        except Exception as ex:
            print(u'vnokex.sendDataRequest Exception:{},{}'.format(str(ex),traceback.format_exc()), file=sys.stderr)

    def sendHeartBeat(self):
        """
        发送心跳
        :return:
        """
        d = {'event': 'ping'}
        # 若触发异常则重连
        try:
            print(u'vnokex.sendHeartBeat')
            j = json.dumps(d)
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'vnokex.sendHeartBeat Exception:{}'.format(str(ex)), file=sys.stderr)

    #----------------------------------------------------------------------
    def login(self):
        """
        登录
        :return: True/False
        """
        print(u'vnokex.login()')
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
            self.ws.send(j)
            return True
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'vnokex.login exception:{},{}'.format(str(ex), traceback.format_exc()), file=sys.stderr)
            return False


########################################################################
class WsSpotApi(OkexApi):
    """现货交易接口"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(WsSpotApi, self).__init__()

    #----------------------------------------------------------------------
    def subscribeSpotTicker(self, symbol):
        print(u'vnokex.subscribeSpotTicker:{}'.format(symbol))

        """订阅现货的Tick"""
        channel = 'ok_sub_spot_%s_ticker' %symbol
        self.sendDataRequest(channel)

    #----------------------------------------------------------------------
    def subscribeSpotDepth(self, symbol, depth=0):
        """订阅现货的深度"""
        print(u'vnokex.subscribeSpotDepth:{}'.format(symbol))

        channel = 'ok_sub_spot_%s_depth' %symbol
        if depth:
            channel = channel + '_' + str(depth)
        self.sendDataRequest(channel)

    #----------------------------------------------------------------------
    def subscribeSpotDeals(self, symbol):
        """
        订阅成交记录
        :param symbol:
        :return:
        """
        print(u'vnokex.subscribeSpotDeals:{}'.format(symbol))
        channel = 'ok_sub_spot_%s_deals' %symbol
        self.sendDataRequest(channel)

    #----------------------------------------------------------------------
    def subscribeSpotKlines(self, symbol, period):
        """
        订阅K线数据
        :param symbol:
        :param period:
        :return:
        """
        print(u'vnokex.subscribeSpotKlines:{} {}'.format(symbol,period))
        channel = 'ok_sub_spot_%s_kline_%s' %(symbol, period)
        self.sendDataRequest(channel)

    #----------------------------------------------------------------------
    def spotTrade(self, symbol, type_, price, amount):
        """现货委托"""
        print(u'vnokex.stopTrade:symbol:{} type:{} price:{} amount:{}'.format(symbol, type_, price,amount))

        params = {}
        params['symbol'] = str(symbol)
        params['type'] = str(type_)

        if str(type_) == 'buy' or str(type_) == 'sell':
            params['price'] = str(price)
            params['amount'] = str(amount)
        elif str(type_) == 'buy_market':
            params['type'] = str(type_)
        elif str(type_) == 'sell_market':
            params['amount'] = str(amount)

        channel = 'ok_spot_order'
        
        self.sendRequest(channel, params)

    #----------------------------------------------------------------------
    def spotCancelOrder(self, symbol, orderid):
        """
        现货撤单指令
        :param symbol:现货合约
        :param orderid:
        :return:
        """
        print(u'vnokex.spotCancelOrder:{} orderid:{}'.format(symbol, orderid))
        params = {}
        params['symbol'] = str(symbol)
        params['order_id'] = str(orderid)
        
        channel = 'ok_spot_cancel_order'

        self.sendRequest(channel, params)
    
    #----------------------------------------------------------------------
    def spotUserInfo(self):
        """
        查询现货账户"
        :return: 
        """""
        print(u'vnokex.spotUserInfo()')
        channel = 'ok_spot_userinfo'
        self.sendRequest(channel, {})

    #----------------------------------------------------------------------
    def spotOrderInfo(self, symbol, orderid):
        """
        查询现货委托信息
        :param symbol: 现货合约
        :param orderid: 委托编号
        :return:
        """
        print(u'vnokex.spotOrderInfo:{},orderid:{}'.format(symbol,orderid))

        params = {}
        params['symbol'] = str(symbol)
        params['order_id'] = str(orderid)
        
        channel = 'ok_spot_orderinfo'
        
        self.sendRequest(channel, params)


########################################################################
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


class WsFuturesApi(object):
    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''  # 用户名
        self.secretKey = ''  # 密码

        self.ws = None  # websocket应用对象  期货对象
        self.active = False  # 还存活

        self.use_lever_rate = 10

        self.trace = False

    # -----------------------------------------------------------------------
    def connect(self, apiKey, secretKey, trace=False):
        self.host = OKEX_USD_CONTRACT
        self.apiKey = apiKey
        self.secretKey = secretKey
        self.trace = trace

        websocket.enableTrace(trace)

        self.ws = websocket.WebSocketApp(self.host,
                                         on_message=self.onMessage,
                                         on_error=self.onError,
                                         on_close=self.onClose,
                                         on_open=self.onOpen)

        self.thread = Thread(target=self.ws.run_forever, args=(None, None, 60, 30))
        self.thread.start()

    # ----------------------------------------------------------------------
    def http_get_request(self, url, params, add_to_headers=None, TIMEOUT=5):
        headers = {
            "Content-type": "application/x-www-form-urlencoded",
            'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0'
        }
        if add_to_headers:
            headers.update(add_to_headers)
        #postdata = urllib.urlencode(params)
        try:
            # response = requests.get(url, postdata, headers=headers, timeout=TIMEOUT)
            response = requests.get(url, headers=headers, timeout=TIMEOUT)
            if response.status_code == 200:
                return response.json()
            else:
                return {"status": "fail"}
        except Exception as e:
            print(u'httpGet failed :{}'.format(str(e)), file=sys.stderr)
            return {"status": "fail", "msg": e}

    # ----------------------------------------------------------------------
    def getContractName(self, symbol_no_usd, contract_type):
        try:
            url = OKEX_CONTRACT_HOST % (symbol_no_usd, contract_type)
            data = self.http_get_request(url, {})

            if type(data) == type([]) and len(data) > 0:
                d1 = data[0]
                contract_name = d1["contract_name"]
                return contract_name

        except Exception as ex:
            print(u'OkexContractApi.getContractName exception:{},{}'.format(str(ex),traceback.format_exc()), file=sys.stderr)
            return None

    def sendHeartBeat(self):
        """
        发送心跳
        :return:
        """
        d = {'event': 'ping'}
        # 若触发异常则重连
        try:
            print(u'vnokex.futuresApi.sendHeartBeat')
            j = json.dumps(d)
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'vnokex.futuresApi.sendHeartBeat Exception:{}'.format(str(ex)), file=sys.stderr)

    # ----------------------------------------------------------------------
    def close(self):
        """关闭接口"""
        if self.thread and self.thread.isAlive():
            self.ws.close()
            self.thread.join()

    # ----------------------------------------------------------------------
    def readData(self, evt):
        """解压缩推送收到的数据"""
        # # 创建解压器
        # decompress = zlib.decompressobj(-zlib.MAX_WBITS)

        # # 将原始数据解压成字符串
        # inflated = decompress.decompress(evt) + decompress.flush()

        # 通过json解析字符串
        # data = json.loads(inflated)
        data = json.loads(evt)

        return data

    # ----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """信息推送"""
        print(evt)

    # ----------------------------------------------------------------------
    def onError(self, ws, evt):
        """错误推送"""
        print('OkexContractApi.onError:{}'.format(evt))

    # ----------------------------------------------------------------------
    def onClose(self, ws):
        """接口断开"""
        print('OkexContractApi.onClose')

    # ----------------------------------------------------------------------
    def onOpen(self, ws):
        """接口打开"""
        print('OkexContractApi.onOpen')

    def subsribeFutureTicker(self, symbol, contract_type):
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_ticker_%s'}" % (symbol, contract_type)
        self.ws.send(req)

    def subscribeFutureKline(self, symbol, contract_type, time_period):
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_kline_%s_%s'}" % (
        symbol, contract_type, time_period)
        self.ws.send(req)

    def subscribeFutureDepth(self, symbol, contract_type):
        req = "{'event':'addChannel','channel':'ok_sub_future_%s_depth_%s_usd'}" % (symbol, contract_type)
        self.ws.send(req)

    def subscribeFutureDepth20(self, symbol, contract_type):
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_depth_%s_20'}" % (symbol, contract_type)
        self.ws.send(req)

    def subscribeFutureTrades(self, symbol, contract_type):
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_trade_%s'}" % (symbol, contract_type)
        self.ws.send(req)

    def subscribeFutureIndex(self, symbol):
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_index'}" % (symbol)
        self.ws.send(req)

    # ----------------------------------------------------------------------
    def generateSign(self, params):
        """生成签名"""
        l = []
        for key in sorted(params.keys()):
            l.append('%s=%s' % (key, params[key]))
        l.append('secret_key=%s' % self.secretKey)
        sign = '&'.join(l)
        return hashlib.md5(sign.encode('utf-8')).hexdigest().upper()

    # ----------------------------------------------------------------------
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
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex),traceback.format_exc()), file=sys.stderr)
        except Exception as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex), traceback.format_exc()), file=sys.stderr)

    # ----------------------------------------------------------------------

    def login(self):
        """
        登录
        :return:
        """
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
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'OkexContractApi.login exception:{},{}'.format(str(ex), traceback.format_exc()), file=sys.stderr)
        except Exception as ex:
            print(u'OkexContractApi.login exception:{},{}'.format(str(ex), traceback.format_exc()), file=sys.stderr)

    # ----------------------------------------------------------------------

    def futureSubscribeIndex(self, symbol):
        """
        订阅期货合约指数行情
        :param symbol: 合约
        :return:
        """
        channel = 'ok_sub_futureusd_%s_index' % symbol
        self.sendTradingRequest(channel, {})

    # ----------------------------------------------------------------------
    def futureAllIndexSymbol(self):
        """
        订阅所有的期货合约指数行情
        :return:
        """
        for symbol in CONTRACT_SYMBOL:
            self.futureSubscribeIndex(symbol)

    # ----------------------------------------------------------------------
    def futureTrade(self, symbol_pair, contract_type, type_, price, amount, _match_price='0', _lever_rate=None):
        """期货委托"""
        params = {}
        params['symbol'] = str(symbol_pair)
        params['contract_type'] = str(contract_type)
        params['price'] = str(price)
        params['amount'] = str(amount)
        params['type'] = type_  # 1:开多 2:开空 3:平多 4:平空
        params['match_price'] = _match_price  # 是否为对手价： 0:不是 1:是 当取值为1时,price无效

        if _lever_rate != None:
            params['lever_rate'] = _lever_rate
        else:
            params['lever_rate'] = str(self.use_lever_rate)

        channel = 'ok_futureusd_trade'

        self.sendTradingRequest(channel, params)

    # ----------------------------------------------------------------------
    def futureCancelOrder(self, symbol_pair, orderid, contract_type):
        """
        期货撤单指令
        :param symbol_pair: 合约对
        :param orderid: 委托单编号
        :param contract_type: 合约类型
        :return:
        """
        params = {}
        params['symbol'] = str(symbol_pair)
        params['order_id'] = str(orderid)
        params['contract_type'] = str(contract_type)

        channel = 'ok_futureusd_cancel_order'

        self.sendTradingRequest(channel, params)

    # ----------------------------------------------------------------------
    def futureUserInfo(self):
        """查询期货账户"""
        channel = 'ok_futureusd_userinfo'
        self.sendTradingRequest(channel, {})

    # ----------------------------------------------------------------------
    # def futureSubUserInfo(self):
    #     channel = 'ok_sub_futureusd_userinfo'
    #     self.sendTradingRequest(channel, {})

    # ----------------------------------------------------------------------
    def futureOrderInfo(self, symbol_pair, order_id, contract_type, status, current_page, page_length=50):
        """
        发出查询期货委托
        :param symbol_pair: 合约对
        :param order_id: 委托单编号
        :param contract_type: 合约类型
        :param status: 状态
        :param current_page:当前页
        :param page_length: 每页长度
        :return:
        """
        params = {}
        params['symbol'] = str(symbol_pair)
        params['order_id'] = str(order_id)
        params['contract_type'] = str(contract_type)
        params['status'] = str(status)
        params['current_page'] = str(current_page)
        params['page_length'] = str(page_length)

        channel = 'ok_futureusd_orderinfo'

        self.sendTradingRequest(channel, params)

    # ----------------------------------------------------------------------
    def futureAllUnfinishedOrderInfo(self):
        """
        订阅所有未完成的委托单信息
        :return:
        """
        for symbol in CONTRACT_SYMBOL:
            symbol_usd = symbol + "_usd"
            for contract_type in CONTRACT_TYPE:
                # orderid = -1,
                self.futureOrderInfo(symbol_usd, -1, contract_type, 1, 1, 50)

    # ----------------------------------------------------------------------
    def subscribeFutureTrades(self):
        """
        订阅期货成交回报
        :return:
        """
        channel = 'ok_sub_futureusd_trades'
        self.sendTradingRequest(channel, {})

    # ----------------------------------------------------------------------
    def subscribeFutureUserInfo(self):
        """订阅期货账户信息"""
        channel = 'ok_sub_futureusd_userinfo'

        self.sendTradingRequest(channel, {})

    # ----------------------------------------------------------------------
    def subscribeFuturePositions(self):
        """订阅期货持仓信息"""
        channel = 'ok_sub_futureusd_positions'

        self.sendTradingRequest(channel, {})