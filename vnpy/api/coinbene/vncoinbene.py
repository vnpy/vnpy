# -*- coding: utf-8 -*-
import sys
import time
import hashlib
import requests
import json
from queue import Queue, Empty
from multiprocessing.dummy import Pool
from threading import Thread

#  此处为APIID SECRET
apiid = ' '
secret = ' '

#  此处为API请求地址及参数
REST_HOST = "http://api.coinbene.com"
market_url = "http://api.coinbene.com/v1/market/"
trade_url = "http://api.coinbene.com/v1/trade/"
header_dict = {"User-Agent": "Mozilla/5.0 (Windows NT 6.1; Trident/7.0; rv:11.0) like Gecko",\
    "Content-Type":"application/json;charset=utf-8","Connection":"keep-alive"}

FUNCTIONCODE_GET_ORDERBOOK_COINBENE = "orderbook"
FUNCTIONCODE_GET_TICKER_COINBENE    = "ticker"
FUNCTIONCODE_GET_TRADE_COINBENE     = "trades"
FUNCTIONCODE_POST_BALANCE_COINBENE  = "balance"
FUNCTIONCODE_POST_CANCEL_COINBENE   = "order/cancel"
FUNCTIONCODE_POST_INFO_COINBENE   = "order/info"
FUNCTIONCODE_POST_ORDERPLACE_COINBENE   = "order/place"




class coinbeneRestApi(object):

    def __init__(self):
        self.apiKey = ''
        self.apiSecret = ''

        self.active = False
        self.reqid = 0
        self.queue = Queue()
        self.pool = None
        self.sessionDict = {}  # 会话对象字典

        self.header = {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Accept': 'application/json'
        }

    # ----------------------------------------------------------------------
    def init(self, apiKey, apiSecret):
        """初始化"""
        self.apiKey = apiKey
        self.apiSecret = apiSecret

    # ----------------------------------------------------------------------
    def start(self, n=3):
        """启动"""
        if self.active:
            return

        self.active = True
        self.pool = Pool(n)
        self.pool.map_async(self.run, range(n))

    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.active = False

        if self.pool:
            self.pool.close()
            self.pool.join()

    # ----------------------------------------------------------------------

    def addReq(self, method, path, callback, params=None, postdict=None):
        """添加请求"""
        self.reqid += 1
        req = (method, path, callback, params, postdict, self.reqid)
        self.queue.put(req)
        return self.reqid

    # ----------------------------------------------------------------------

    def processReq(self, req, i):
        """处理请求"""
        method, callback, params, postdict, reqid = req

        # 使用长连接的session，比短连接的耗时缩短80%
        session = self.sessionDict[i]
        resp = session.request(method, url, headers=header, params=params, data=postdict)

        # resp = requests.request(method, url, headers=header, params=params, data=postdict)

        code = resp.status_code
        d = resp.json()

        if code == 200:
            callback(d, reqid)
        else:
            self.onError(code, d)

    # ----------------------------------------------------------------------

    def run(self, i):
        """连续运行"""
        self.sessionDict[i] = requests.Session()

        while self.active:
            try:
                req = self.queue.get(timeout=1)
                self.processReq(req, i)
            except Empty:
                pass

    # ----------------------------------------------------------------------
    def onError(self, code, error):
        """错误回调"""
        print(u'on error {} {}'.format(code, error),file=sys.stderr)

    # ----------------------------------------------------------------------
    def onData(self, data, reqid):
        """通用回调"""
        print(u'on data:{} reqid:{}'.format(data, reqid))

    #  生成签名sign
    def sign(self,**kwargs):
        """
        将传入的参数生成列表形式，排序后用＆拼接成字符串，用hashbli加密成生sign
        """
        sign_list = []
        for key, value in kwargs.items():
            sign_list.append("{}={}".format(key, value))
        sign_list.sort()
        sign_str = "&".join(sign_list)
        mysecret = sign_str.upper().encode()
        m = hashlib.md5()
        m.update(mysecret)
        return m.hexdigest()

    #  生成时间戳
    def create_timestamp(self):
        timestamp = int(round(time.time() * 1000))
        return timestamp

#timestamp = create_timestamp()

    def http_get_nosign(self, url, i=0):
        return self.http_request(url, data=None,i=i)

    def http_post_sign(self,url,dic,i=0):
        mysign = self.sign(**dic)
        del dic['secret']
        dic['sign'] = mysign
        return self.http_request(url,data=dic,i=i)

    def http_request(self, url, data,i=0):
        session = self.sessionDict[i]
        if data == None:
            reponse = session.request(method, url, headers=header_dict, params=params, data=postdict)
            reponse = requests.get(url,headers=header_dict)
        else:
            reponse = requests.post(url,data=json.dumps(data),headers=header_dict)
        try:
            if reponse.status_code == 200:
                return json.loads(reponse.text)
            else:
                return None
        except Exception as e:
            print('http failed : %s' % e)
            return None


    #  获取最新价
    def get_ticker(self, symbol):
        """
        symbol必填，为all或交易对代码:btcusdt
        """
        url = market_url + "ticker?symbol=" + str(symbol)
        return self.http_get_nosign(url)


    #  获取挂单
    def get_orderbook(self, symbol, depth=200):
        """
        depth为选填项，默认为200
        """
        url = market_url + "orderbook?symbol=" + symbol + "&depth=" + str(depth)
        return self.http_get_nosign(url)


    #  获取成交记录
    def get_trade(self, symbol, size=300):
        """
        size:获取记录数量，按照时间倒序传输。默认300
        """
        url = market_url + "trades?symbol=" + symbol + "&size=" + str(size)
        return self.http_get_nosign(url)


    #  查询账户余额
    def post_balance(self, dic):
        """
        以字典形式传参
        apiid:可在coinbene申请,
        secret:个人密钥(请勿透露给他人),
        timestamp:时间戳,
        account:默认为exchange，
        """
        url = trade_url + "balance"
        return self.http_post_sign(url, dic)


    #  下单
    def post_order_place(self, dic):
        """
        以字典形式传参
        apiid,symbol,timestamp
        type:可选 buy-limit/sell-limit
        price:购买单价
        quantity:购买数量
        """
        url = trade_url + "order/place"
        return self.http_post_sign(url, dic)


    #  查询委托
    def post_info(self, dic):
        """
        以字典形式传参
        apiid,timestamp,secret,orderid
        """
        url = trade_url + "order/info"
        return self.http_post_sign(url, dic)


    #  查询当前委托
    def post_open_orders(self, dic):
        """
        以字典形式传参
        apiid,timestamp,secret,symbol
        """
        url = trade_url + "order/open-orders"
        return self.http_post_sign(url, dic)


    #  撤单
    def post_cancel(self, dic):
        """
        以字典形式传参
        apiid,timestamp,secret,orderid
        """
        url = trade_url + "order/cancel"
        return self.http_post_sign(url, dic)
