# encoding: UTF-8

import hashlib
import zlib
import json,os
from time import sleep
from threading import Thread
import traceback
import websocket
import requests
import sys
import ssl
from datetime import datetime
import time
import hmac
import base64

# API文档 https://www.okex.com/docs/zh/
# OKEX V3
# By Chen zhipei

from vnpy.api.okex.okexData import SPOT_TRADE_SIZE_DICT,SPOT_REST_ERROR_DICT, FUTURES_ERROR_DICT

# OKEX网站
OKEX_USD_SPOT = 'wss://real.okex.com:10442/ws/v3'     # OKEX (币币交易）现货地址
OKEX_USD_CONTRACT = 'wss://real.okex.com:10442/ws/v3'   # OKEX 期货地址

OKEX_CONTRACT_HOST = 'https://www.okex.com/api/v1/future_hold_amount.do?symbol=%s_usd&contract_type=%s'  # 合约持仓查询地址

SPOT_CURRENCY = ["usdt",
                 "btc",
                 "ltc",
                 "eth",
                 "etc",
                 "bch",
                 "eos"]

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
               "gas_usdt",
               "eos_usdt"])

KLINE_PERIOD = ["1min","3min","5min","15min","30min","1hour","2hour","4hour","6hour","12hour","day","3day","week"]

CONTRACT_SYMBOL = ["BTC-USD","ETH-USD","EOS-USD","ETC-USD","LTC-USD"]

# 合约类型 ：    当周，下周，季度
CONTRACT_TYPE = ["this_week", "next_week", "quarter"]




class OkexApi(object):
    """交易接口"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.host = ''          # 服务器
        self.apiKey = ''        # 用户名
        self.secretKey = ''     # 密码
        self.passphrase = ''
        self.ws = None          # websocket应用对象  现货对象
        self.thread = None      # 初始化线程

    #----------------------------------------------------------------------
    def reconnect(self):
        """重新连接"""
        # 首先关闭之前的连接
        self.close()
        try:
            # 再执行重连任务
            self.ws = websocket.WebSocketApp(self.host,
                                             on_message=self.onMessage,
                                             on_error=self.onError,
                                             on_close=self.onClose,
                                             on_open=self.onOpen)

            kwargs = {'sslopt': {'cert_reqs': ssl.CERT_NONE}}
            self.thread = Thread(target=self.ws.run_forever, kwargs=kwargs, name='Okex_websock')
            self.thread.start()
        except Exception as ex:
            print(u'{} OkexApi reconnect exception :{},{}'.format(datetime.now(), str(ex), traceback.format_exc()),
                  file=sys.stderr)

    def connect(self, apiKey, secretKey, passphrase, trace=False):
        """
        连接网关
        :param apiKey   : 申请的API key
        :param secretKey: 签名key
        :param trace    : 是否开启websocket的日志跟踪功能，输出到StreamHandler
        :return:
        """
        # 更新websocket服务器地址/API key/
        self.host = OKEX_USD_CONTRACT
        self.apiKey = apiKey
        self.secretKey = secretKey
        self.passphrase = passphrase
        self.trace = trace
        try:
            websocket.enableTrace(trace)

            self.ws = websocket.WebSocketApp(self.host,
                                             on_message=self.onMessage,
                                             on_error=self.onError,
                                             on_close=self.onClose,
                                             on_open=self.onOpen)
            kwargs = {'sslopt': {'cert_reqs': ssl.CERT_NONE}}
            self.thread = Thread(target=self.ws.run_forever, kwargs=kwargs)
            self.thread.start()
        except Exception as ex:
            print(u'{} wsFuturesApi connect exception :{},{}'.format(datetime.now(), str(ex),traceback.format_exc()), file=sys.stderr)

    def readData(self, evt):
        """
        解码推送收到的数据
        :param evt:
        :return:
        """
        if isinstance(evt,bytes):
            evt = evt.decode('utf-8')
        data = json.loads(evt)
        return data

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
    def onMessage(self, *args):
        """
        信息推送事件
        :param ws:  接口
        :param evt: 事件
        :return:
        """
        evt = None
        if len(args) == 2:
            evt = args[-1]
        print(u'vnokex.onMessage:{}'.format(evt))

    def onError(self, *args):
        """
        接口错误推送事件
        :param ws:
        :param evt:
        :return:
        """
        evt = None
        if len(args) == 2:
            evt = args[-1]
        print(u'vnokex.onApiError:{}'.format(evt))

    def onClose(self, ws):
        """
        接口断开事件
        :param ws:
        :return:
        """
        print(u'vnokex.onClose')

    def onOpen(self, ws):
        """
        接口打开事件
        :param ws:
        :return:
        """
        print(u'vnokex.onOpen')

    def inflate(self,data):
        """解压数据流"""
        decompress = zlib.decompressobj(-zlib.MAX_WBITS)
        inflated = decompress.decompress(data)
        inflated += decompress.flush()
        #  bytes=>string
        if isinstance(inflated,bytes):
            inflated = inflated.decode('utf-8')
        return inflated

    def generateSign(self, params):
        """生成签名"""
        #print(u'vnokex.generateSign')
        l = []
        for key in sorted(params.keys()):
            l.append('%s=%s' %(key, params[key]))
        l.append('secret_key=%s' %self.secretKey)
        sign = '&'.join(l)
        return hashlib.md5(sign.encode('utf-8')).hexdigest().upper()

    def sendRequest(self, channel, params):
        """发送指令请求"""
        #print(u'vnokex.sendRequest:{}'.format(channel))
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

    def sendDataRequest(self, channel):
        """发送数据请求"""
        #print(u'vnokex.sendDataRequest:{}'.format(channel))
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
        # d = {'event': 'ping'}
        # # 若触发异常则重连
        # try:
        #     #print(u'vnokex.sendHeartBeat')
        #     j = json.dumps(d)
        #     self.ws.send(j)
        # except websocket.WebSocketConnectionClosedException as ex:
        #     print(u'vnokex.sendHeartBeat Exception:{}'.format(str(ex)), file=sys.stderr)
        pass

    def login_params(self):
        times = str(time.time())
        message = times + 'GET'+'/users/self/verify'
        mac = hmac.new(bytes(message, encoding='utf-8'), bytes(self.secretKey, encoding='utf-8'), digestmod='sha256')
        d = mac.digest()
        sign = base64.b64encode(d)

        login_param = {"op":"login","args":[self.apiKey, self.passphrase, times, sign.decode("utf-8")]}
        login_str = json.dumps(login_param)
        return login_str

    def onSpotUserInfo(self,ws_data):
        pass

    def login(self):
        """
        登录
        :return: True/False
        """
        print(u'vnokex.login()')
        times = str(time.time())
        message = times + 'GET'+'/users/self/verify'
        mac = hmac.new(bytes(self.secretKey, encoding='utf8'), bytes(message, encoding='utf-8'), digestmod='sha256')
        d = mac.digest()
        sign = base64.b64encode(d)
        login_param = {"op":"login","args":[self.apiKey, self.passphrase, times, sign.decode("utf-8")]}
        login_str = json.dumps(login_param)
        j = login_str
        # 使用json打包并发送
        # j = json.dumps(d)

        # 若触发异常则重连
        try:
            self.ws.send(j)
            return True
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'vnokex.login exception:{},{}'.format(str(ex), traceback.format_exc()), file=sys.stderr)
            return False


class WsSpotApi(OkexApi):
    """现货交易接口"""

    def __init__(self):
        """Constructor"""
        super(WsSpotApi, self).__init__()

    def sendTransfer(self,symbol, amount,tfrom, tto):
        method = 'POST'
        request_path = '/api/account/v3/transfer'
        params={
            'amount':amount,
            'currency':symbol,
            'from':tfrom,
            'to':tto
        }
        self.send_request(method, request_path, params)

    def subscribeSpotTicker(self, symbol):

        req = {"op":"subscribe","args":["spot/ticker:%s"%symbol]}
        req = json.dumps(req)
        self.ws.send(req)

    def subscribeSpotDepth(self, symbol):
        """订阅现货的深度"""

        req = {"op": "subscribe", "args": ["spot/depth5:%s" % symbol]}
        req = json.dumps(req)
        self.ws.send(req)

    def subscribeSpotTrades(self, symbol):
        """
        订阅成交记录
        :param symbol:
        :return:
        """
        req = {"op":"subscribe","args":["spot/order:%s"%symbol]}
        req = json.dumps(req)
        self.ws.send(req)

    def subscribeSpotKlines(self, symbol, period):
        """
        订阅K线数据
        :param symbol:
        :param period:
        :return:
        """
        #print(u'vnokex.subscribeSpotKlines:{} {}'.format(symbol,period))
        # channel = 'ok_sub_spot_%s_kline_%s' %(symbol, period)
        # self.sendDataRequest(channel)
        pass

    def spotTrade(self, symbol, type_, price, amount,order_id=0):
        """现货委托"""
        params = {
            'client_oid':order_id,
            'instrument_id':symbol,
            'side':type_,
            'type':'limit',
            'size':amount,
            'price':price,
            'margin_trading':'1'
        }
        method = 'POST'
        request_path = '/api/spot/v3/orders'
        self.send_request(method, request_path, params)

    def send_request(self, method, request_path, params, cursor=False):
        if method == 'GET':
            url = '?'
            for key,value in params.items():
                url = url + str(key)+'='+str(value)+'&'
            request_path = request_path + url[0:-1]
        url = 'https://www.okex.com'+ request_path
        urlt = 'https://www.okex.com' + '/api/general/v3/time'
        response2 = requests.get(urlt)
        if response2.status_code == 200:
            timestamp = response2.json()['iso']
        body = json.dumps(params) if method == 'POST' else ''
        message = str(timestamp) + method + request_path + body
        mac = hmac.new(bytes(self.secretKey, encoding='utf8'), bytes(message, encoding='utf-8'), digestmod='sha256')
        d = mac.digest()
        sign = base64.b64encode(d)
        head = dict()
        head['Content-Type'] = 'application/json'
        head['OK-ACCESS-KEY'] = self.apiKey
        head['OK-ACCESS-SIGN'] = sign
        head['OK-ACCESS-TIMESTAMP'] = str(timestamp)
        head['OK-ACCESS-PASSPHRASE'] = self.passphrase
        header = head

        if method == 'POST':
            response=requests.post(url, data=body, headers=header)
        else:
            response = requests.get(url, data=body, headers=header)

        if str(response.status_code).startswith('2'):
            if cursor is True:
                return response.text

            self.onMessage(response.text)

        # print(response.text)

        try:
            res_header = response.headers
            if False:
                r = dict()
                try:
                    r['before'] = res_header['OK-BEFORE']
                    r['after'] = res_header['OK-AFTER']
                except:
                    print("")
                return response.json(), r
            else:
                return response.json()
        except ValueError:
            raise print(response.text)

    def spotCancelOrder(self, symbol, orderid):
        """
        现货撤单指令
        :param symbol:现货合约
        :param orderid:
        :return:
        """
        method = 'POST'
        request_path = '/api/spot/v3/cancel_orders/%s'%orderid

        params = {
            'instrument_id':symbol.lower()
        }

        self.send_request(method, request_path, params)

    def spotUserInfo(self):
        """
        查询现货账户
        :return:
        """
        # req = {"op":"subscribe","args":["spot/account:BTC","spot/account:USDT","spot/account:ETH","spot/account:EOS"]}
        # j = json.dumps(req)
        # self.ws.send(j)
        # # self.querySpotAccount()
        #
        # method = 'GET'
        # request_path = '/api/spot/v3/accounts'
        # respose = self.send_request(method, request_path, {},cursor=True)

        # self.onSpotUserInfo(respose)
        pass

    def spotOrderInfo(self, symbol):
        """
        # 查询现货委托信息
        # :param symbol: 现货合约
        # :param orderid: 委托编号
        # :return:
        # """
        method = 'GET'
        request_path = '/api/spot/v3/orders?instrument_id=%s&status=open'%(symbol)
        self.send_request(method, request_path, {})


class WsFuturesApi(object):

    def __init__(self):
        """Constructor"""
        self.apiKey = ''  # 用户名
        self.secretKey = ''  # 密码
        self.passphrase = ''
        self.ws = None  # websocket应用对象  期货对象
        self.active = False  # 还存活
        self.use_lever_rate = 10
        self.trace = False
        self.contractInfo = {} # 储存合约信息

    def connect(self, apiKey, secretKey, passphrase, trace=False):
        """

        :param apiKey:
        :param secretKey:
        :param passphrase:
        :param trace:
        :return:
        """
        self.host = OKEX_USD_CONTRACT
        self.apiKey = apiKey
        self.secretKey = secretKey
        self.passphrase = passphrase
        self.trace = trace
        self.writechaLog(apiKey)
        self.writechaLog(secretKey)
        self.writechaLog(passphrase)
        try:
            websocket.enableTrace(trace)

            self.ws = websocket.WebSocketApp(self.host,
                                             on_message=self.onMessage,
                                             on_error=self.onError,
                                             on_close=self.onClose,
                                             on_open=self.onOpen)
            kwargs = {'sslopt': {'cert_reqs': ssl.CERT_NONE}}
            self.thread = Thread(target=self.ws.run_forever, kwargs=kwargs)
            self.thread.start()
        except Exception as ex:
            print(u'{} wsFuturesApi connect exception :{},{}'.format(datetime.now(), str(ex),traceback.format_exc()), file=sys.stderr)

    def writechaLog(self, content):
        """

        :param content:
        :return:
        """
        pass

    def queryContractInfo(self, type_contract):
        """
        主动获取：获取合约信息，主要针对交割合约，含有日期
        :return:
        """
        method = 'GET'
        if 'SWAP' in type_contract:
            request_path = '/api/swap/v3/instruments'
        else:
            request_path = '/api/futures/v3/instruments'
        response = self.send_request(method, request_path,{}, onMessage=False,reback=True)
        if response is None:
            print('{},response is None'.format(type_contract))
            return
        res  = json.loads(response)
        for each in res:
            if 'SWAP'in type_contract:
                self.contractInfo[each['instrument_id']] = 'SWAP'
            else:
                self.contractInfo[each['instrument_id']] = each['alias']

    def sendTransfer(self, symbol, amount, tfrom, tto):
        """
        转币 0:子账户 1:币币 3:合约 4:C2C 5:币币杠杆 6:钱包 7:ETT 8:余币宝 9 永续合约
        :param symbol: 币种，需要大写
        :param amount:
        :param tfrom:
        :param tto:
        :return:
        """
        method = 'POST'
        request_path = '/api/account/v3/transfer'
        params={
            'amount':amount,
            'currency':symbol,
            'from':tfrom,
            'to':tto
        }
        self.send_request(method, request_path, params)

    def sendHeartBeat(self):
        """
        发送心跳
        :return:
        """
        d = {'op': 'subscribe',
             'args':'ping'}
        # 若触发异常则重连
        try:
            print(u'vnokex.futuresApi.sendHeartBeat')
            j = json.dumps(d)
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'vnokex.futuresApi.sendHeartBeat Exception:{}'.format(str(ex)), file=sys.stderr)

    def close(self):
        """关闭接口"""
        if self.thread and self.thread.isAlive():
            self.ws.close()
            self.thread.join()

    def inflate(self, data):
        """
        解压数据流
        """
        decompress = zlib.decompressobj(-zlib.MAX_WBITS)
        inflated = decompress.decompress(data)
        inflated += decompress.flush()
        if isinstance(inflated, bytes):        #  bytes=>string
            inflated = inflated.decode('utf-8')
        return inflated

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

    def onMessage(self, *args):
        """信息推送"""
        if len(args)>0:
            print(args[-1])

    def onError(self, *args):
        """错误推送"""
        if len(args) > 0:
            print('OkexContractApi.onError:{}'.format(args[-1]))

    def onClose(self, ws):
        """接口断开"""
        print('OkexContractApi.onClose')

    # ----------------------------------------------------------------------
    def onOpen(self, *args):
        """接口打开"""
        print('OkexContractApi.onOpen')

    def subsribeFutureTicker(self, symbol):
        """
        ws，订阅ticker频道
        :param symbol:
        :return:
        """
        if symbol.endswith('SWAP'):
            req = {"op":"subscribe","args":["swap/ticker:%s"%symbol]}
        else:
            req = {"op":"subscribe","args":["futures/ticker:%s"%symbol]}
        req = json.dumps(req)
        try:
            self.ws.send(req)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex), traceback.format_exc()),
                  file=sys.stderr)
        except Exception as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex), traceback.format_exc()),
                  file=sys.stderr)

    def subscribeFutureKline(self, symbol):
        """
        ws, 订阅Kline平道
        :param symbol:
        :param contract_type:
        :param time_period:
        :return:
        """
        pass

    def subscribeFutureDepth(self, symbol):
        """
        ws，订阅Depth
        :param symbol:
        :return:
        """
        if symbol.endswith('SWAP'):
            req = {"op": "subscribe", "args": ["swap/depth5:%s"%symbol]}
        else:
            req = {"op": "subscribe", "args": ["futures/depth5:%s" % symbol]}
        req = json.dumps(req)
        try:
            self.ws.send(req)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex), traceback.format_exc()),
                  file=sys.stderr)
        except Exception as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex), traceback.format_exc()),
                  file=sys.stderr)

    def subscribeFutureTrades(self, symbol):
        """
        ws，订阅交易频道
        :param symbol:
        :param contract_type:
        :return:
        """
        if symbol.endswith('SWAP'):
            req = {"op": "subscribe", "args": ["swap/order:%s"%symbol]}
        else:
            req = {"op": "subscribe", "args": ["futures/order:%s"%symbol]}
        req = json.dumps(req)
        try:
            self.ws.send(req)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex), traceback.format_exc()),
                  file=sys.stderr)
        except Exception as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex), traceback.format_exc()),
                  file=sys.stderr)

    def subscribeFutureIndex(self, symbol):
        # req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_index'}" % (symbol)
        # self.ws.send(req)
        pass

    def setSingleleverage(self, symbol, leverage, margin_mode=None, instrument_id=None, direction=None):
        """
        设置币种全仓和逐仓
        :param symbol:
        :param leverage:
        :param margin_mode:
        :param instrument_id:
        :param direction:
        :return:
        """
        method = 'POST'
        lower_case = symbol.split('-')[0].lower()
        if symbol.endswith('SWAP'):
            # 永续
            # 1.逐仓-多仓 2.逐仓-空仓 3.全仓
            request_path = '/api/swap/v3/accounts/%s/leverage' % symbol
            parameter = dict()
            if margin_mode is None: # 全仓模式
                parameter["leverage"] = leverage
                parameter["side"] = 3
            else:
                parameter["leverage"] = leverage
                parameter["side"] = margin_mode
            request_path += self.__dictToStr(parameter)
            self.send_request(method,request_path,{})
        else:
            # 交割
            request_path = '/api/futures/v3/accounts/%s/leverage' % lower_case
            parameter = dict()
            if margin_mode is None: # 全仓模式
                parameter['leverage'] = leverage
                request_path += self.__dictToStr(parameter)
                self.send_request(method, request_path, {})
            else: # 逐仓模式
                if direction is not None:
                    parameter['leverage'] = leverage
                    parameter['direction'] = direction
                    parameter['instrument_id'] = symbol
                    request_path += self.__dictToStr(parameter)
                    self.send_request(method, request_path, {})
                else:
                    parameter['leverage'] = leverage
                    parameter['direction'] = 'long'
                    parameter['instrument_id'] = symbol
                    request_path += self.__dictToStr(parameter)
                    self.send_request(method, request_path, {})
                    parameter['leverage'] = leverage
                    parameter['direction'] = 'short'
                    parameter['instrument_id'] = symbol
                    request_path += self.__dictToStr(parameter)
                    self.send_request(method, request_path, {})

    def __dictToStr(self, dic):
        """
        将dict转换为纯str
        :param dic:
        :return:
        """
        c = '{'
        for key, value in dic.items():
            c += ("\"%s\":\"%s\"" % (key, value))
        c += '}'
        return  c

    def queryFuturePosition(self, symbol):
        """
        主动获取：查询单币种的持仓信息
        :param symbol:
        :return:
        """
        method = 'GET'
        if symbol.endswith('SWAP'):
            request_path = '/api/swap/v3/%s/position' % symbol
        else:
            request_path = '/api/futures/v3/%s/position'%symbol
        response = self.send_request(method, request_path, {}, onMessage=False, reback=True)
        if response is None:
            return
        response = json.loads(response)
        self.treatFuturePositionInfo(response, symbol)

    def treatFuturePositionInfo(self, message, symbol):
        """
        处理函数：用于处理持仓信息查询返回的内容
        :param message:
        :return:
        """
        pass

    def login_params(self):
        times = str(time.time())
        message = times + 'GET'+'/users/self/verify'
        mac = hmac.new(bytes(self.secretKey, encoding='utf8'), bytes(message, encoding='utf-8'), digestmod='sha256')
        d = mac.digest()
        sign = base64.b64encode(d)

        login_param = {"op":"login","args":[self.apiKey, self.passphrase, times, sign.decode("utf-8")]}
        login_str = json.dumps(login_param)
        return login_str

    def login(self):
        """
        登录
        :return:
        """
        times = str(time.time())
        message = times + 'GET'+'/users/self/verify'
        mac = hmac.new(bytes(self.secretKey, encoding='utf8'), bytes(message, encoding='utf-8'), digestmod='sha256')
        d = mac.digest()
        sign = base64.b64encode(d)

        login_param = {"op":"login","args":[self.apiKey, self.passphrase, times, sign.decode("utf-8")]}
        login_str = json.dumps(login_param)
        j = login_str
        # 若触发异常则重连
        try:
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'OkexContractApi.login exception:{},{}'.format(str(ex), traceback.format_exc()), file=sys.stderr)
        except Exception as ex:
            print(u'OkexContractApi.login exception:{},{}'.format(str(ex), traceback.format_exc()), file=sys.stderr)

    def futureSubscribeIndex(self, symbol):
        """
        订阅期货合约指数行情
        :param symbol: 合约
        :return:
        """
        # channel = 'ok_sub_futureusd_%s_index' % symbol
        # self.sendTradingRequest(channel, {})
        pass

    def subFutureAllIndexSymbol(self):
        """
        订阅所有的期货合约指数行情 TODO: 需要做
        :return:
        """
        # for symbol in CONTRACT_SYMBOL:
        #     self.futureSubscribeIndex(symbol)
        pass

    def futureTrade(self, symbol_pair, type_, price, amount, _match_price='0', order_id=0):
        """
        期货委托
        :return
        """
        params = {
                     'client_oid': order_id,
                     'instrument_id': symbol_pair,
                     'type': type_,
                     'price': price,
                     'size': amount,
                     'match_price':'0' ,
                     'leverage':'10'}
        method = 'POST'
        if symbol_pair.endswith('SWAP'):
            request_path = '/api/swap/v3/order'
        else:
            request_path = '/api/futures/v3/order'
        self.send_request(method, request_path, params)


    def send_request(self, method, request_path, params, onMessage=True, reback=False):
        """
        REST_API接口
        :param method:
        :param request_path:
        :param params:
        :param cursor:
        :return:
        """
        base_url = 'https://www.okex.com'
        time_stamp_url = 'https://www.okex.com/api/general/v3/time'
        time_response = requests.get(time_stamp_url)
        if time_response.status_code == 200:
            timestamp = time_response.json()['iso']
        else:
            return
        body = json.dumps(params) if method == 'POST' else ''
        sign_name = self.signature(timestamp, method, request_path, self.secretKey, body)
        if not self.passphrase:
            print('s')
        header = self.get_header(self.apiKey, sign_name, timestamp, self.passphrase)
        url = base_url + request_path

        if method == 'POST':
            response=requests.post(url, data=body, headers=header)
        else:
            response = requests.get(url, data=body, headers=header)

        if str(response.status_code).startswith('2'):
            if onMessage:
                self.onMessage(response.text)
                return  response.text
            elif reback:
                return response.text
        else:
            print("错误：{}".format(response.text))


    def signature(self, timestamp, method, request_path, secret_key, body):
        """
        隶属send_order
        :param params:
        :return:
        """
        message = str(timestamp) + str.upper(method) + request_path + body
        mac = hmac.new(bytes(secret_key, encoding='utf8'), bytes(message, encoding='utf-8'), digestmod='sha256')
        d = mac.digest()
        return base64.b64encode(d)

    def get_header(self, api_key, sign, timestamp, passphrase='123456'):
        """
        隶属send_order
        :param params:
        :return:
        """
        header = dict()
        header['Content-Type'] = 'application/json'
        header['OK-ACCESS-KEY'] = api_key
        header['OK-ACCESS-SIGN'] = sign
        header['OK-ACCESS-TIMESTAMP'] = str(timestamp)
        header['OK-ACCESS-PASSPHRASE'] = '123456'
        return header

    def parse_params_to_str(self, params):
        """
        隶属send_order
        :param params:
        :return:
        """
        url = '?'
        for key, value in params.items():
            url = url + str(key) + '=' + str(value) + '&'
        return url[0:-1]

    def queryFutureCancelOrder(self, symbol_pair, orderid):
        """
        主动函数：期货撤单指令
        :param symbol_pair: 合约对
        :param orderid: 委托单编号
        :param contract_type: 合约类型
        :return:
        """

        method = 'POST'
        if symbol_pair.endswith('SWAP'):
            request_path = '/api/swap/v3/cancel_order/%s/%s'%(symbol_pair,orderid)
        else:
            request_path = '/api/futures/v3/cancel_order/%s/%s' % (symbol_pair, orderid)

        response = self.send_request(method, request_path,{},onMessage=False, reback=True)
        if response is None:
            print('symbol_pair:{},orderId:{} respon is None'.format(symbol_pair, orderid))
            return False,'false'
        response = json.loads(response)
        if response['result']:
            return True, response
        else:
            return False,'false'

    def subFutureUserInfo(self,symbol='BTC'):
        """
        ws, 订阅账户频道信息
        """
        if symbol.endswith('SWAP'):
            req = {"op":"subscribe","args":["swap/account:%s"%symbol]}
        else:
            req = {"op": "subscribe", "args": ["futures/account:%s" % symbol.split('-USD')[0]]}
        j = json.dumps(req)
        try:
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex),traceback.format_exc()), file=sys.stderr)
        except Exception as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex), traceback.format_exc()), file=sys.stderr)

    def queryFutureOrderStatus(self, symbol, orderID):
        """
        查询订单状态
        :param symbol:
        :param orderID:
        :return:
        """
        method = 'GET'
        if symbol.endswith('SWAP'):
            request_path = ''
        else:
            request_path = '/api/futures/v3/orders/'+symbol+'/'+orderID
        response = self.send_request(method, request_path, {}, onMessage=False, reback=True)
        if response is None:
            return
        response = json.loads(response)
        return self.treatFutureOrderStatus(response)

    def treatFutureOrderStatus(self, response):
        pass

    def queryFuturesAccountInfo(self, symbol):
        """
        主动获取：查询账户对应币种信息
        :param symbol:
        :return:
        """
        method = 'GET'
        if symbol.endswith('SWAP'):
            request_path = '/api/swap/v3/%s/accounts'%symbol
        else:
            request_path = '/api/futures/v3/accounts/' + symbol.split('-')[0].lower()
        response = self.send_request(method, request_path, {}, onMessage=False, reback=True)
        if response is None:
            return
        response = json.loads(response)
        self.treatFutureAccountInfo(response, symbol)

    def treatFutureAccountInfo(self, message, symbol):
        """
        处理函数：用于处理查询账户信息返回来的信息
        :param message:
        :return:
        """
        pass

    def subFuturePositionInfo(self,symbol):
        """
        ws, 订阅期货账户持仓
        """
        if symbol.endswith('SWAP'):
            req = {"op":"subscribe","args":["swap/position:%s"%symbol]}
        else:
            req = {"op": "subscribe", "args": ["futures/position:%s" % symbol]}
        j = json.dumps(req)
        try:
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex), traceback.format_exc()),
                  file=sys.stderr)
        except Exception as ex:
            print(u'OkexContractApi.sendTradingRequest exception:{},{}'.format(str(ex), traceback.format_exc()),
                  file=sys.stderr)

    def queryFutureOrderInfo(self, symbol_pair, status, current_page, page_length=50):
        """
        主动函数：发出查询期货订单列表
        :param symbol_pair: 合约对
        :param order_id: 委托单编号
        :param contract_type: 合约类型
        :param status: 状态
        :param current_page:当前页
        :param page_length: 每页长度
        :return:
        """

        method = 'GET'
        if symbol_pair.endswith('SWAP'):
            request_path = '/api/swap/v3/orders/%s?status=%s&from=%s&limit=%s'%(symbol_pair, status,current_page,page_length)
        else:
            symbol_pair = symbol_pair
            request_path = '/api/futures/v3/orders/%s?status=%s&from=%s&limit=%s' % (symbol_pair, status, current_page, page_length)
        response = self.send_request(method, request_path, {}, onMessage=False, reback=True) # TODO 需要检查
        if response is None:
            return
        response = json.loads(response)
        self.treatFutureOrderInfo(symbol_pair,response)

    def treatFutureOrderInfo(self, symbol_pair, message):
        """
        处理函数：用于处理查询订单返回来的信息
        :param message:
        :return:
        """
        pass

