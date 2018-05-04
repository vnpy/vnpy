# encoding: UTF-8

import hashlib
import zlib
import json
from time import sleep
from threading import Thread
import urllib , requests

import websocket    
import time


# OKEX网站

OKEX_USD_SUB_SPOT = 'wss://real.okex.com:10441/websocket'       # OKEX 现货地址
OKEX_USD_CONTRACT = 'wss://real.okex.com:10440/websocket/okexapi'   # OKEX 期货地址
OKEX_CONTRACT_HOST = 'https://www.okex.com/api/v1/future_hold_amount.do?symbol=%s_usd&contract_type=%s'  # 合约持仓查询地址 

okex_all_symbol_type = ["usdt","btc","ltc","eth","etc","bch"]
# okex_all_symbol_pairs = ["ltc_btc","eth_btc","etc_btc","bch_btc","btc_usdt","eth_usdt",\
#         "ltc_usdt","etc_usdt","bch_usdt","etc_eth","bt1_btc","bt2_btc","btg_btc","qtum_btc",\
#         "hsr_btc","neo_btc","gas_btc","qtum_usdt","hsr_usdt","neo_usdt","gas_usdt","tnb_btc"]
okex_all_symbol_pairs = ["eth_btc","ltc_btc","etc_btc","bch_btc","xrp_btc","xem_btc","xlm_btc",
"iota_btc","1st_btc","aac_btc","ace_btc","act_btc","aam_btc","ark_btc","ast_btc","avt_btc","bcd_btc",
"bnt_btc","btg_btc","btm_btc","cag_btc","cmt_btc","ctr_btc","cvc_btc","dash_btc","dat_btc","dgb_btc",
"dgd_btc","dna_btc","dnt_btc","dpy_btc","edo_btc","elf_btc","eng_btc","eos_btc","evx_btc","fair_btc",
"fun_btc","gas_btc","gnt_btc","gnx_btc","hsr_btc","icn_btc","icx_btc","itc_btc","kcash_btc","knc_btc",
"lend_btc","link_btc","lrc_btc","mag_btc","mana_btc","mco_btc","mda_btc","mdt_btc","mot_btc","mth_btc",
"mtl_btc","nas_btc","neo_btc","nuls_btc","oax_btc","omg_btc","pay_btc","ppt_btc","pro_btc","qtum_btc",
"qvt_btc","rcn_btc","rct_btc","rdn_btc","read_btc","req_btc","rnt_btc","salt_btc","san_btc","show_btc",
"smt_btc","sngls_btc","snm_btc","snt_btc","ssc_btc","storj_btc","sub_btc","swftc_btc","tnb_btc",
"trx_btc","ubtc_btc","ugc_btc","ukg_btc","utk_btc","vee_btc","vib_btc","wrc_btc","wtc_btc","xmr_btc","iost_usdt",
"xuc_btc","yoyo_btc","zec_btc","zrx_btc","iost_btc","ost_eth","elf_eth","ont_eth","ast_eth","mana_eth","lend_eth",
"chat_eth","chat_btc","ont_btc","iost_eth","trx_eth","lrc_eth","smt_eth","icn_eth","link_eth","icx_eth",
"btc_usdt","eth_usdt","ltc_usdt","etc_usdt","bch_usdt","xrp_usdt","xem_usdt","xlm_usdt","nas_eth","tnb_eth",
"iota_usdt","1st_usdt","aac_usdt","ace_usdt","act_usdt","aam_usdt","ark_usdt","ast_usdt","avt_usdt","bcd_usdt",
"bnt_usdt","btg_usdt","btm_usdt","cag_usdt","cmt_usdt","ctr_usdt","cvc_usdt","dash_usdt","dat_usdt","dgb_usdt",
"dgd_usdt","dna_usdt","dnt_usdt","dpy_usdt","edo_usdt","elf_usdt","eng_usdt","eos_usdt","evx_usdt","fair_usdt",
"fun_usdt","gas_usdt","gnt_usdt","gnx_usdt","hsr_usdt","icn_usdt","icx_usdt","itc_usdt","kcash_usdt","knc_usdt",
"lend_usdt","link_usdt","lrc_usdt","mag_usdt","mana_usdt","mco_usdt","mda_usdt","mdt_usdt","mot_usdt","mth_usdt",
"mtl_usdt","nas_usdt","neo_usdt","nuls_usdt","oax_usdt","omg_usdt","pay_usdt","ppt_usdt","pro_usdt","qtum_usdt",
"qvt_usdt","rcn_usdt","rct_usdt","rdn_usdt","read_usdt","req_usdt","rnt_usdt","salt_usdt","san_usdt","show_usdt",
"smt_usdt","sngls_usdt","snm_usdt","snt_usdt","ssc_usdt","storj_usdt","sub_usdt","swftc_usdt","tnb_usdt",
"trx_usdt","ubtc_usdt","ugc_usdt","ukg_usdt","utk_usdt","vee_usdt","vib_usdt","wrc_usdt","wtc_usdt","xmr_usdt",
"xuc_usdt","yoyo_usdt","zec_usdt","zrx_usdt"]

# for test
# okex_all_symbol_pairs = ['etc_usdt']

okex_all_k_line_periods = ["1min","3min","5min","15min","30min","1hour","2hour","4hour","6hour","12hour","day","3day","week"]

okex_all_contract_symbol = ["btc","ltc","eth","etc","bch","eos","xrp","btg"]
okex_all_contract_type = ["this_week","next_week","quarter"]

okex_all_contract_all_symbol_usd = []
for symbol in okex_all_contract_symbol:
    okex_all_contract_all_symbol_usd.append( symbol + "_usd")

class OKEX_Sub_Spot_Api(object):
    """基于Websocket的API对象"""
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.apiKey = ''         # 用户名
        self.secretKey = ''      # 密码

        self.ws_sub_spot = None          # websocket应用对象  现货对象

        self.thread = None       # 线程初始化

        self.active = False      # 还存活

        self.trace = False

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
    
        self.thread = Thread(target=self.ws_sub_spot.run_forever , args = (None , None , 60, 30))
        self.thread.start()
    
    #----------------------------------------------------------------------
    def connect_Subpot(self, apiKey , secretKey , trace = False):
        self.host = OKEX_USD_SUB_SPOT
        self.apiKey = apiKey
        self.secretKey = secretKey
        self.trace = trace

        websocket.enableTrace(trace)

        self.ws_sub_spot = websocket.WebSocketApp(self.host, 
                                             on_message=self.onMessage,
                                             on_error=self.onError,
                                             on_close=self.onClose,
                                             on_open=self.onOpen)        
            
        self.thread = Thread(target = self.ws_sub_spot.run_forever , args = (None , None , 60, 30))
        # self.thread_heart = Thread(target = self.run_forever_heart)

        self.thread.start()
        # self.thread_heart.start()

    #----------------------------------------------------------------------
    def run_forever_heart(self ):
        while 1:
            time.sleep(30)
            self.sendHeartBeat()

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
        print(u'vnokex.close')
        if self.thread and self.thread.isAlive():    
            self.ws_sub_spot.close()
            self.thread.join()
            # self.thread_heart.join()

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
    def subscribeSpotTicker(self, symbol_pair):
        # 现货的 ticker
        print(u'OKEX_Sub_Spot_Api.subscribeSpotTicker:{}'.format(symbol_pair))
        req = "{'event':'addChannel','channel':'ok_sub_spot_%s_ticker'}" % symbol_pair
        self.ws_sub_spot.send(req)

    #----------------------------------------------------------------------
    def subscribeSpotDepth(self, symbol_pair):
        # 现货的 市场深度
        print(u'OKEX_Sub_Spot_Api.subscribeSpotDepth:{}'.format(symbol_pair))
        req = "{'event':'addChannel','channel':'ok_sub_spot_%s_depth'}" % symbol_pair
        self.ws_sub_spot.send(req)

    #----------------------------------------------------------------------
    def subscribeSpotDepth5(self, symbol_pair):
        # 现货的 市场深度 5
        print(u'OKEX_Sub_Spot_Api.subscribeSpotDepth5:{}'.format(symbol_pair))
        req = "{'event':'addChannel','channel':'ok_sub_spot_%s_depth_5'}" % symbol_pair
        self.ws_sub_spot.send(req)

    #----------------------------------------------------------------------
    def subscribeSpotDeals(self, symbol_pair):
        print(u'OKEX_Sub_Spot_Api.subscribeSpotDeals:{}'.format(symbol_pair))
        req = "{'event':'addChannel','channel':'ok_sub_spot_%s_deals'}" % symbol_pair
        self.ws_sub_spot.send(req)

    #----------------------------------------------------------------------
    def subscribeSpotKlines(self, symbol_pair , time_period):
        print(u'OKEX_Sub_Spot_Api.subscribeSpotKlines:{}'.format(symbol_pair))
        req = "{'event':'addChannel','channel':'ok_sub_spot_%s_kline_%s'}" % ( symbol_pair , time_period)
        self.ws_sub_spot.send(req)

    #----------------------------------------------------------------------
    def sendHeartBeat(self):
        """
        发送心跳
        :return:
        """
        d = {'event': 'ping'}
        # 若触发异常则重连
        try:
            # print(u'OKEX_Sub_Spot_Api sendHeartBeat')
            j = json.dumps(d)
            self.ws_sub_spot.send(j)
        except websocket.WebSocketConnectionClosedException as ex:
            print(u'OKEX_Sub_Spot_Api sendHeartBeat Exception:{}'.format(str(ex)))

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
        # print(u'OKEX_Sub_Spot_Api.sendTradingRequest')
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
        print(u'vnokex.stopTrade:symbol:{} type:{} price:{} amount:{}'.format(symbol_pair, type_, price,amount))
        params = {}
        params['symbol'] = str(symbol_pair)
        params['type'] = str(type_)
        params['price'] = str(price)
        params['amount'] = str(amount)
        
        channel = 'ok_spot_order'
        
        self.sendTradingRequest(channel, params)

    #----------------------------------------------------------------------
    def spotCancelOrder(self, symbol_pair, orderid):
        """
        现货撤单指令
        :param symbol:现货合约
        :param orderid:
        :return:
        """
        print(u'spotCancelOrder:{} orderid:{}'.format(symbol_pair, orderid))
        params = {}
        params['symbol'] = str(symbol_pair)
        params['order_id'] = str(orderid)
        
        channel = 'ok_spot_cancel_order'

        self.sendTradingRequest(channel, params)
    
    #----------------------------------------------------------------------
    def spotUserInfo(self):
        """
        查询现货账户"
        :return: 
        """
        # print(u'spotUserInfo()')

        channel = 'ok_spot_userinfo'
        self.sendTradingRequest(channel, {})

    #----------------------------------------------------------------------
    def spotOrderInfo(self, symbol_pair, orderid):
        """
        查询现货委托信息
        :param symbol: 现货合约
        :param orderid: 委托编号
        :return:
        """
        # print(u'spotOrderInfo:{},orderid:{}'.format(symbol_pair,orderid))

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
            self.ws_sub_spot.send(j)
        except websocket.WebSocketConnectionClosedException:
            print(u'vnokex.login exception:{},{}'.format(str(ex), traceback.format_exc()) )
            return False


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
        self.active = False     # 还存活

        self.use_lever_rate = 10

        self.trace = False

    #-----------------------------------------------------------------------
    def connect_Contract(self, apiKey , secretKey , trace = False):
        self.host = OKEX_USD_CONTRACT
        self.apiKey = apiKey
        self.secretKey = secretKey
        self.trace = trace

        websocket.enableTrace(trace)

        self.ws_contract = websocket.WebSocketApp(self.host, 
                                           on_message=self.onMessage,
                                           on_error=self.onError,
                                           on_close=self.onClose,
                                           on_open=self.onOpen)        
          
        self.thread = Thread(target=self.ws_contract.run_forever , args = (None , None , 60, 30))
        # self.thread_heart = Thread(target=self.run_forever_heart )
        # self.thread = Thread(target = self.run_forever)
        self.thread.start()
        # self.thread_heart.start()

    #-----------------------------------------------------------------------
    def run_forever_heart(self ):
        while 1:
            time.sleep(30)
            self.sendHeartBeat()

    #----------------------------------------------------------------------
    def http_get_request(self, url, params, add_to_headers=None , TIMEOUT = 5):
        headers = {
            "Content-type": "application/x-www-form-urlencoded",
            'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0'
        }
        if add_to_headers:
            headers.update(add_to_headers)
        postdata = urllib.urlencode(params)
        try:
            #response = requests.get(url, postdata, headers=headers, timeout=TIMEOUT)
            response = requests.get(url , headers=headers, timeout=TIMEOUT)
            if response.status_code == 200:
                return response.json()
            else:
                return {"status":"fail"}
        except Exception as e:
            print("httpGet failed, detail is:%s" %e)
            return {"status":"fail","msg":e}

    #----------------------------------------------------------------------
    def getContractName(self, symbol_no_usd , contract_type):
        try:
            url = OKEX_CONTRACT_HOST % (symbol_no_usd , contract_type)
            data = self.http_get_request( url , {} )

            if type(data) == type([]) and len(data) > 0:
                d1 = data[0]
                contract_name = d1["contract_name"]
                return contract_name
        except Exception , ex:
            print ex
        return None

    #----------------------------------------------------------------------
    def close(self):
        """关闭接口"""
        if self.thread and self.thread.isAlive():
            self.ws_contract.close()
            self.thread.join()
            # self.thread_heart.join()

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
        print(u'subsribeFutureTicker:{} contract_type:{}'.format(symbol, contract_type))
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_ticker_%s'}" % (symbol , contract_type)
        self.ws_contract.send(req)

    def subscribeFutureKline(self, symbol , contract_type , time_period):
        print(u'subscribeFutureKline:{} contract_type:{} time_period:{}'.format(symbol, contract_type , time_period))
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_kline_%s_%s'}" % (symbol , contract_type , time_period)
        self.ws_contract.send(req)

    def subscribeFutureDepth(self, symbol , contract_type):
        print(u'subscribeFutureDepth:{} contract_type:{}'.format(symbol, contract_type))
        req = "{'event':'addChannel','channel':'ok_sub_future_%s_depth_%s_usd'}" % (symbol , contract_type )
        self.ws_contract.send(req)

    def subscribeFutureDepth20(self, symbol , contract_type):
        print(u'subscribeFutureDepth20:{} contract_type:{}'.format(symbol, contract_type))
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_depth_%s_20'}" % (symbol , contract_type)
        self.ws_contract.send(req)

    def subscribeFutureTrades(self, symbol , contract_type):
        print(u'subscribeFutureTrades:{} contract_type:{}'.format(symbol, contract_type))
        req = "{'event':'addChannel','channel':'ok_sub_futureusd_%s_trade_%s'}" % (symbol , contract_type)
        self.ws_contract.send(req)

    def subscribeFutureIndex(self, symbol ):
        print(u'subscribeFutureIndex:{} '.format(symbol))
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
        print(u'future_login')
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
    def futureSubscribeIndex(self , symbol):
        print(u'futureSubscribeIndex:{} '.format(symbol))
        channel = 'ok_sub_futureusd_%s_index' % symbol
        self.sendTradingRequest(channel, {})

    #----------------------------------------------------------------------
    def futureAllIndexSymbol(self):
        print(u'futureAllIndexSymbol')
        for symbol in okex_all_contract_symbol:
            self.futureSubscribeIndex(symbol)

    #----------------------------------------------------------------------
    def futureTrade(self, symbol_pair, contract_type ,type_, price, amount , _match_price = '0' , _lever_rate = None):
        """期货委托"""
        print(u'futureTrade:{},{},{},{},{},{},{}'.format(symbol_pair , contract_type ,type_, price, amount , _match_price , _lever_rate ))
        params = {}
        params['symbol'] = str(symbol_pair)
        params['contract_type'] = str(contract_type)
        params['price'] = str(price)
        params['amount'] = str(amount)
        params['type'] = type_                  # 1:开多 2:开空 3:平多 4:平空
        params['match_price'] = _match_price    # 是否为对手价： 0:不是 1:是 当取值为1时,price无效

        if _lever_rate != None:
            params['lever_rate'] = _lever_rate
        else:
            params['lever_rate'] = str(self.use_lever_rate)
        
        channel = 'ok_futureusd_trade'
        
        self.sendTradingRequest(channel, params)

    #----------------------------------------------------------------------
    def futureCancelOrder(self, symbol_pair, orderid , contract_type):
        """期货撤单"""
        print(u'futureCancelOrder:{},{},{}'.format(symbol_pair, orderid , contract_type))
        params = {}
        params['symbol'] = str(symbol_pair)
        params['order_id'] = str(orderid)
        params['contract_type'] = str(contract_type)
        
        channel = 'ok_futureusd_cancel_order'

        self.sendTradingRequest(channel, params)

    #----------------------------------------------------------------------
    def futureUserInfo(self):
        """查询期货账户"""
        print(u'futureUserInfo')
        channel = 'ok_futureusd_userinfo'
        self.sendTradingRequest(channel, {})

    #----------------------------------------------------------------------
    # def futureSubUserInfo(self):
    #     channel = 'ok_sub_futureusd_userinfo'
    #     self.sendTradingRequest(channel, {})

    #----------------------------------------------------------------------
    def futureOrderInfo(self , symbol_pair , order_id , contract_type , status , current_page , page_length = 50):
        """查询期货委托"""
        print(u'futureOrderInfo( {} , {} , {} , {} , {} , {})'.format(symbol_pair , order_id , contract_type , status , current_page , page_length))
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
    def futureAllUnfinishedOrderInfo(self):
        print(u'futureAllUnfinishedOrderInfo')
        for symbol in okex_all_contract_symbol:
            symbol_usd = symbol + "_usd"
            for contract_type in okex_all_contract_type:
                self.futureOrderInfo( symbol_usd , -1 , contract_type , 1 , 1 , 50)

    #----------------------------------------------------------------------
    def subscribeFutureTrades( self):
        print(u'subscribeFutureTrades')
        channel = 'ok_sub_futureusd_trades'
        self.sendTradingRequest(channel, {})

    #----------------------------------------------------------------------
    def subscribeFutureUserInfo(self):
        """订阅期货账户信息"""
        print(u'subscribeFutureUserInfo')
        channel = 'ok_sub_futureusd_userinfo' 
        
        self.sendTradingRequest(channel, {})
        
    #----------------------------------------------------------------------
    def subscribeFuturePositions(self):
        """订阅期货持仓信息"""
        print(u'subscribeFuturePositions')
        channel = 'ok_sub_futureusd_positions' 
        
        self.sendTradingRequest(channel, {})    
    