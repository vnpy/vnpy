# encoding: utf-8

import json
from time import time, sleep
from threading import Thread
from datetime import datetime
import base64
import hmac
import hashlib
import json
import gzip, binascii, os  

import urllib , requests

import websocket    
import time

from vnpy.trader.vtFunction import systemSymbolToVnSymbol , VnSymbolToSystemSymbol

import json

GATEIO_SOCKET_URL = "wss://ws.gate.io/v3"

'''
'''
class Gate_WSDataApi(object):
    """基于Websocket的API对象"""
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.host = ''          # 服务器地址
        self.apiKey = ''        # 用户名
        self.secretKey = ''     # 密码
        
        self.ws = None          # websocket应用对象
        self.thread = None      # 工作线程

        self.subscribeStrList = set([])
    #----------------------------------------------------------------------
    def reconnect(self):
        """重新连接"""
        # 首先关闭之前的连接
        #self.close()
        
        # 再执行重连任务
        self.ws = websocket.WebSocketApp(self.host, 
                                         on_message=self.onMessage,
                                         on_error=self.onError,
                                         on_close=self.onClose,
                                         on_open=self.onOpen)        
    
        self.thread = Thread(target=self.ws.run_forever , args = (None , None , 60, 30))
        self.thread.start()
    
    #----------------------------------------------------------------------
    def connect_Subpot(self, apiKey , secretKey , trace = False):
        self.host = GATEIO_SOCKET_URL
        self.apiKey = apiKey
        self.secretKey = secretKey
        self.trace = trace

        websocket.enableTrace(trace)

        self.ws = websocket.WebSocketApp(self.host, 
                                             on_message=self.onMessage,
                                             on_error=self.onError,
                                             on_close=self.onClose,
                                             on_open=self.onOpen)        
            
        self.thread = Thread(target = self.ws.run_forever , args = (None , None , 60, 30))
        # self.thread_heart = Thread(target = self.run_forever_heart)

        self.thread.start()
        # self.thread_heart.start()

    #----------------------------------------------------------------------
    def onMessage(self, ws, evt):
        """
        信息推送事件
        :param ws:  接口
        :param evt: 事件
        :return:
        """
        print(u'vngate_nwe.onMessage:{}'.format(evt))
        
    #----------------------------------------------------------------------
    def onError(self, ws, evt):
        """
        接口错误推送事件
        :param ws:
        :param evt:
        :return:
        """
        print(u'vngate_nwe.onApiError:{}'.format(evt))
        
    #----------------------------------------------------------------------
    def onClose(self, ws):
        """
        接口断开事件
        :param ws:
        :return:
        """
        print(u'vngate_nwe.onClose')
        
    #----------------------------------------------------------------------
    def onOpen(self, ws):
        """
        接口打开事件
        :param ws:
        :return:
        """
        print(u'vngate_nwe.onOpen')

    #----------------------------------------------------------------------
    def sendSocketCmd( self, client_id , method , json_params = []):
        send_json = {
            "id": client_id,
            "method": method,
            "params": json_params
        }
        self.ws.send( json.dumps(send_json))

    '''
    vngate_nwe.onMessage:{"error": null, "result": {"period": 86400, "open": "18.1604", "close": "17.03"
, "high": "18.53", "low": "16.54", "last": "17.03", "change": "-6.22", "quoteVolume": "1015826.99811
89865", "baseVolume": "17910280.42194529534205249261"}, "id": 1}
    '''
    #----------------------------------------------------------------------
    def querySpotTicker(self , u_id , symbol_pair = "EOS_USDT" , time_period = 86400):
        symbol_pair = systemSymbolToVnSymbol(symbol_pair)
        self.sendSocketCmd( u_id , "ticker.query" , [ symbol_pair , time_period])

    '''
    vngate_nwe.onMessage:{
    "error": null,
    "result": {
        "asks": [
            [
                "16.9507",
                "293.6242489299"
            ],
            [
                "16.9586",
                "1591.5376104592"
            ],
        ],
        "bids": [
            [
                "16.95",
                "0.1094"
            ],
            [
                "16.9471",
                "163.602"
            ],
            [
                "16.9431",
                "1.4607"
            ],

        ]
    },
    "id": 1
}

    '''
    #----------------------------------------------------------------------
    def querySpotDepth(self , u_id , symbol_pair = "EOS_USDT" , limit = 5 , interval = "0.00000001"):
        symbol_pair = systemSymbolToVnSymbol(symbol_pair)
        self.sendSocketCmd( u_id , "depth.query" , [ symbol_pair , limit , interval])

    '''
    {
    "error": null,
    "result": [
        {
            "id": 7177814,
            "time": 1523887673.562782,
            "price": "6.05",
            "amount": "20",
            "type": "buy"
        },
        {
            "id": 7177813,
            "time": 1523887354.256974,
            "price": "6.05",
            "amount": "15",
            "type": "buy"
        },
    ],
    "id": 12309
}
    '''
    #----------------------------------------------------------------------
    def querySpotTrades(self, u_id , symbol_pair = "EOS_USDT" , limit = 2 , last_id = 7177813):
        symbol_pair = systemSymbolToVnSymbol(symbol_pair)
        self.sendSocketCmd( u_id , "trades.query" , [ symbol_pair , limit , last_id])
    '''
    {
    "error": null, 
    "result": [
        [
            1492358400, time
            "7000.00",  open
            "8000.0",   close
            "8100.00",  highest
            "6800.00",  lowest
            "1000.00"   volume
            "123456.00" amount
            "BTC_USDT"  market name
        ]
        ...
    ]
    "id": 12312
    }
    '''
    #----------------------------------------------------------------------
    def querySpotKline(self, u_id , symbol_pair = "BTC_USDT", start = 1516951219 , end_time = 1516951219 , interval = 1800):
        symbol_pair = systemSymbolToVnSymbol(symbol_pair)
        self.sendSocketCmd( u_id , "kline.query" , [ symbol_pair , start , end_time, interval])

    '''
    vngate_nwe.onMessage:{"error": null, "result": {"status": "success"}, "id": 2}
    vngate_nwe.onMessage:{"method": "ticker.update", "params": ["BOT_USDT", {"period": 86400, "open": "0
    .7383", "close": "0.9048", "high": "1.015", "low": "0.715", "last": "0.9048", "change": "22.55", "qu
    oteVolume": "4565863.1552367147", "baseVolume": "4071168.7349472209511"}], "id": null}
    vngate_nwe.onMessage:{"method": "ticker.update", "params": ["BOT_USDT", {"period": 86400, "open": "0
    .7383", "close": "0.9049", "high": "1.015", "low": "0.715", "last": "0.9049", "change": "22.56", "qu
    oteVolume": "4571805.6819467147", "baseVolume": "4076546.0501166889511"}], "id": null}
    '''
    #----------------------------------------------------------------------
    def subscribeSpotTicker(self, u_id , symbol_pair = "BOT_USDT"):
        symbol_pair = systemSymbolToVnSymbol(symbol_pair)
        self.sendSocketCmd( u_id , "ticker.subscribe" , [ symbol_pair ])

    '''
    vngate_nwe.onMessage:{"method": "depth.update", "params": [true, {"asks": [["0.893", "813.385"], ["0
.8931", "102.65936009"], ["0.8932", "288.8898"], ["0.9058", "2028"], ["0.9067", "10"], ["0.9076", "4
87.11"], ["0.9084", "1000"], ["0.9085", "17.49966971"], ["0.9086", "49.468551235"], ["0.9087", "1950
.59"]], "bids": [["0.8929", "88.76"], ["0.8921", "198.01888"], ["0.892", "256.09"], ["0.8919", "3280
.5348"], ["0.8803", "1382"], ["0.8802", "2257.925"], ["0.8801", "16.58862017"], ["0.88", "300"], ["0
.8779", "822.56"], ["0.8669", "774.0223"]]}, "BOT_USDT"], "id": null}
vngate_nwe.onMessage:{"method": "depth.update", "params": [false, {"bids": [["0.8929", "110.0925"]]}
, "BOT_USDT"], "id": null}

    Can only subscribe one market at the same time, market list is not supported currently. For multiple subscriptions, only the last one takes effect.

    '''
    #----------------------------------------------------------------------
    def subscribeSpotDepth(self, u_id , symbol_pair = "BOT_USDT" , limit = 30, interval = "0.00000001"):
        symbol_pair = systemSymbolToVnSymbol(symbol_pair)
        self.sendSocketCmd( u_id , "depth.subscribe" , [ symbol_pair , limit , interval])

    '''
    vngate_nwe.onMessage:{"error": null, "result": {"status": "success"}, "id": 3}
vngate_nwe.onMessage:{"method": "trades.update", "params": ["BOT_USDT", [{"id": 56675623, "time": 15
25592829.2169299, "price": "0.9096", "amount": "310.3478", "type": "sell"}, {"id": 56675622, "time":
 1525592829.2167261, "price": "0.9096", "amount": "461", "type": "sell"}, {"id": 56667395
, "time": 1525591676.7347641, "price": "0.9085", "amount": "847.41", "type": "sell"}]], "id": null}
    '''
    #----------------------------------------------------------------------
    def subscribeSpotTrades(self, u_id , symbol_pair = "BOT_USDT"  ):
        symbol_pair = systemSymbolToVnSymbol(symbol_pair)
        self.sendSocketCmd( u_id , "trades.subscribe" , [ symbol_pair ])

    '''
    vngate_nwe.onMessage:{"error": null, "result": {"status": "success"}, "id": 3}
vngate_nwe.onMessage:{"method": "kline.update", "params": [[1525591800, "0.9085", "0.9174", "0.9217"
, "0.9049", "78364.430712655", "71495.1179278982815", "BOT_USDT"]], "id": null}
    '''
    #----------------------------------------------------------------------
    def subscribeSpotKline(self, u_id , symbol_pair = "BOT_USDT" , interval = 1800):
        symbol_pair = systemSymbolToVnSymbol(symbol_pair)
        self.sendSocketCmd( u_id , "kline.subscribe" , [ symbol_pair , interval]) 