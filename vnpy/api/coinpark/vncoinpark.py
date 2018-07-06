
#!-*-coding:utf-8 -*-
#@TIME    : 2018/6/10/0010 11:19
#@Author  : incenselee


import hmac
import hashlib
import requests
import sys
import time
import base64
import json
from collections import OrderedDict

class vncoinpark():

    def __init__(self,base_url = 'https://api.coinpark.cc/v1'):
        self.base_url = base_url
        self.account_type = 0
    def auth(self, key, secret):
        self.key = bytes(key,'utf-8')
        self.secret = bytes(secret, 'utf-8')

    def public_request(self, method, api_url, **payload):
        """request public url"""
        r_url = self.base_url + api_url
        try:
            r = requests.request(method, r_url, params=payload)
            r.raise_for_status()
            if r.status_code == 200:
                j = r.json()
                error_msg = j.get('error', None)
                if error_msg is not None:
                    return False, {'error': error_msg.get('code', '1000'), 'result': error_msg.get('msg', 'error_msg')}
                return True, j.get('result', None)
            else:
                return False, {'error': 'E10000', 'result': r.status_code}
        except requests.exceptions.HTTPError as err:
            return False, {'error': 'E10001', 'result': r.text}
        except Exception as err:
            return False, {'error': 'E10002', 'result': err}

    def getSign(self, data, secret):
        result = hmac.new(secret, bytes(data,'utf-8'), hashlib.md5).hexdigest()
        return result

    def signed_request(self, api_url, cmds):
        """request a signed url"""
        r_url = self.base_url + api_url

        s_cmds = json.dumps(cmds)
        sign = self.getSign(s_cmds,self.secret)

        try:
            r = requests.post(r_url, data={'cmds':s_cmds, 'apikey':self.key,'sign':sign})
            r.raise_for_status()
            if r.status_code == 200:
                j = r.json()
                error_msg = j.get('error', None)
                if error_msg is not None:
                    return False, {'error': error_msg.get('code','1000'),'result':error_msg.get('msg','error_msg')}
                return True, j.get('result',None)
            else:
                return False, {'error': 'E10000', 'result': r.status_code}
        except requests.exceptions.HTTPError as err:
            return False, {'error': 'E10001', 'result': r.text}
        except Exception as err:
            return False, {'error': 'E10002', 'result': err}

    def get_symbols(self):
        """get all symbols"""
        return self.public_request('GET', '/mdata?cmd=pairList')

    def get_market_ticker(self, symbol):
        """get market ticker"""
        return self.public_request('GET', '/mdata?cmd=market&pair={symbol}'.format(symbol=symbol))

    def get_market_depth(self, level, symbol):
        """get market depth"""
        return self.public_request('GET', '/mdata?cmd=depth&pair={symbol}&size={level}'.format(level=level, symbol=symbol))

    def get_trades(self,symbol,size = 20):
        """get detail trade"""
        return self.public_request('GET', '/mdata?cmd=deals&pair={symbol}&size={size}'.format(symbol=symbol,size=size))

    def get_candle(self,symbol,period,size=20):
        """get candle data
        请求参数：
        cmd: "api/kline"
        body: {
            pair,       //交易对，如BIX_BTC
            period,     //k线周期，取值 ['1min', '3min', '5min', '15min', '30min', '1hour', '2hour', '4hour', '6hour', '12hour', 'day', 'week']
            size,       //要几条，1-1000，不传返回1000
        }

        返回结果：
        {
            "result":[
                {
                    "time":1512660420000,
                    "open":"0.00586568",
                    "high":"0.00586568",
                    "low":"0.00586568",
                    "close":"0.00586568",
                    "vol":"0"
                },
                {
                    "time":1512660480000,
                    "open":"0.00586568",
                    "high":"0.00586568",
                    "low":"0.00586568",
                    "close":"0.00586568",
                    "vol":"10"
                }
            ],
            "cmd":"api/kline"
        }
        """
        return self.public_request('GET', '/mdata?cmd=kline&pair={symbol}&period={period}&size={size}'.format(period=period, symbol=symbol,size=size))

    def get_userinfo(self):
        cmds = [
            {'cmd':'user/userinfo',
             'body':{}}
        ]
        return self.signed_request()

    def get_balance(self):
        """get user balance"""
        cmds = [
            {'cmd': 'transfer/assets',
             'body': {
                 'select':1
             }}
        ]
        return self.signed_request(api_url='/transfer',cmds=cmds)

    def list_orders(self, symbol_pair):
        """get orders
        请求：POST https://api.coinpark.cc/v1/orderpending
        参数:
        cmd: "orderpending/orderPendingList"
        body: {
            [pair],           //交易对,兼容参数
            [account_type],   //账户类型，0-普通账户
            page,             //第几页，从1开始
            size              //要几条
            [coin_symbol]     //交易币种
            [currency_symbol] //定价币种
            [order_side]      //交易方向，1-买，2-卖
        }

        返回结果：
        {
            "result":{
                "count":1,
                "page":1,
                "items":[
                    {
                        "id":159,
                        "createdAt": 1512756997000,
                        "account_type":0,                       //账户类型 0-普通账户
                        "coin_symbol":"LTC",                    //交易币种
                        "currency_symbol":"BTC",                //定价币种
                        "order_side":2,                         //交易方向，1-买，2-卖
                        "order_type":2,                         //订单类型，2-限价单
                        "price":"0.00900000",                   //委托价格，市价单是0
                        "amount":"1.00000000",                  //委托数量，市价买单是0
                        "money":"0.00900000",                   //委托金额，市价卖单是0
                        "deal_amount":"0.00000000",             //已成交数量
                        "deal_percent":"0.00%",                 //成交百分比
                        "unexecuted":"0.00000000",              //未成交数量
                        "status":1                              //状态，1-待成交，2-部分成交，3-完全成交，4-部分撤销，5-完全撤销，6-待撤销
                    }
                ]
            },
            "cmd":"orderpending/orderPendingList"
        }


        """
        cmds = [
            {'cmd': 'orderpending/orderPendingList',
             'body': {
                 'pair': symbol_pair,
                 'page':1,
                 'size':10
             }}
        ]
        return self.signed_request(api_url='/orderpending', cmds=cmds)

    def create_order(self, symbol_pair, order_type, order_side,price,amount,index=1):
        """create order
        请求:POST https://api.coinpark.cc/v1/orderpending
        参数：
        cmd: "orderpending/trade",
        index: 12345,       //随机数，int类型，批量时唯一标识某个cmd
        body: {
            pair,           //交易对, BIX_BTC, BIX_ETH, ...
            account_type,   //账户类型，0-普通账户
            order_type,     //交易类型，2-限价单
            order_side,     //交易方向，1-买，2-卖
            price,          //委托价格
            amount,         //委托数量
        }

        返回结果：
        {
            "result": 34,     //返回委托单id
            "index": 12345,   //用户自定义随机数
            "cmd":"orderpending/trade"
        }
        """
        cmds = [
            {'cmd': 'orderpending/trade',
             'index':index,
             'body': {
                 'pair': symbol_pair,
                 'account_type': self.account_type,
                'order_type':order_type,
                'order_side':order_side,
                'price': price,
                 'amount':amount
                }
             }
        ]

        return self.signed_request(api_url='/orderpending', cmds=cmds)

    def buy(self,symbol, price, amount, index=1):
        """buy someting"""
        print(u'api.buy:{},price={},amount={}'.format(symbol,price,amount))
        return self.create_order(symbol_pair=symbol, order_side=1, order_type=2, price=str(price), amount=amount,index=index)

    def sell(self, symbol, price, amount, index=1):
        """buy someting"""
        print(u'api.sell:{},price={},amount={}'.format(symbol, price, amount))
        return self.create_order(symbol_pair=symbol, order_side=2, order_type=2, price=str(price), amount=amount,index=index)

    def get_order(self,order_id):
        """get specfic order
        POST https://api.coinpark.cc/v1/orderpending
        请求参数：
        cmd: "orderpending/order"
        body: {
            id,           //委托单id
        }

        返回结果：
        {
            "result":{
                "id":159,
                 "createdAt": 1512756997000,
                 "account_type":0,                       //账户类型 0-普通账户
                 "pair":"LTC_BTC",                       //交易对
                 "coin_symbol":"LTC",                    //交易币种
                 "currency_symbol":"BTC",                //定价币种
                 "order_side":2,                         //交易方向，1-买，2-卖
                 "order_type":2,                         //订单类型，2-限价单
                 "price":"0.00900000",                   //委托价格，市价单是0
                 "amount":"1.00000000",                  //委托数量，市价买单是0
                 "money":"0.00900000",                   //委托金额，市价卖单是0
                 "deal_amount":"0.00000000",             //已成交数量
                 "deal_percent":"0.00%",                 //成交百分比
                 "unexecuted":"0.00000000",              //未成交数量
                 "status":1                              //状态，1-待成交，2-部分成交，3-完全成交，4-部分撤销，5-完全撤销，6-待撤销
            },
            "cmd":"orderpending/order"
        }
        """
        cmds = [
            {'cmd': 'orderpending/order',
             'body': {
                 'id': order_id
             }
             }
        ]
        return self.signed_request(api_url='/orderpending', cmds=cmds)

    def cancel_order(self,order_id,index=1):
        """cancel specfic order
        OST https://api.coinpark.cc/v1/orderpending

        请求参数：
        cmd: "orderpending/cancelTrade"
        index: 12345,       //随机数，int类型，批量时唯一标识某个cmd
        body: {
            orders_id,  //委托单id
        }

        返回结果：
        {
            "result":"撤销中",
            "index": 12345,   //用户自定义随机数
            "cmd":"orderpending/cancelTrade"
        }
        """
        cmds = [
            {'cmd': 'orderpending/cancelTrade',
             'index':index,
             'body': {
                 'orders_id': order_id
             }
             }
        ]
        return self.signed_request(api_url='/orderpending', cmds=cmds)



