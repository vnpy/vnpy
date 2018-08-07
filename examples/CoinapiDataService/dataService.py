# encoding: UTF-8

from __future__ import print_function

import json
import time
import datetime

import requests
from pymongo import MongoClient, ASCENDING

from vnpy.trader.vtObject import VtBarData
from vnpy.trader.app.ctaStrategy.ctaBase import MINUTE_DB_NAME


# 加载配置
config = open('config.json')
setting = json.load(config)

MONGO_HOST = setting['MONGO_HOST']
MONGO_PORT = setting['MONGO_PORT']
APIKEY = setting['APIKEY']
SYMBOLS = setting['SYMBOLS']

mc = MongoClient(MONGO_HOST, MONGO_PORT)                        # Mongo连接
db = mc[MINUTE_DB_NAME]                                         # 数据库
headers = {'X-CoinAPI-Key': APIKEY}



#----------------------------------------------------------------------
def generateVtBar(symbol, d):
    """生成K线"""
    bar = VtBarData()
    
    bar.symbol = symbol
    bar.vtSymbol = symbol
    bar.datetime = datetime.datetime.strptime(d['time_open'], '%Y-%m-%dT%H:%M:%S.%f0Z')
    bar.date = bar.datetime.strftime('%Y%m%d')
    bar.time = bar.datetime.strftime('%H:%M:%S')
    bar.open = d['price_open']
    bar.high = d['price_high']
    bar.low = d['price_low']
    bar.close = d['price_close']
    bar.volume = d['volume_traded']
    
    return bar

#----------------------------------------------------------------------
def downMinuteBarBySymbol(symbol, period, start, end):
    """下载某一合约的分钟线数据"""
    startTime = time.time()
    
    cl = db[symbol]                                                 # 集合
    cl.ensure_index([('datetime', ASCENDING)], unique=True)         # 添加索引
    
    startDt = datetime.datetime.strptime(start, '%Y%m%d')
    endDt = datetime.datetime.strptime(end, '%Y%m%d')
    
    url = 'https://rest.coinapi.io/v1/ohlcv/%s/history' %symbol
    params = {
        'period_id': period,
        'time_start': startDt.strftime('%Y-%m-%dT%H:%M:%S.%f0Z'),
        'time_end': endDt.strftime('%Y-%m-%dT%H:%M:%S.%f0Z'),
        'limit': 10000
    }
    resp = requests.get(url, headers=headers, params=params)
    
    if resp.status_code != 200:
        print(u'%s数据下载失败' %symbol)
        return
    
    l = resp.json()
        
    for d in l:
        bar = generateVtBar(symbol, d)
        d = bar.__dict__
        flt = {'datetime': bar.datetime}
        cl.replace_one(flt, d, True)
        
    endTime = time.time()
    cost = (endTime - startTime) * 1000

    print(u'合约%s数据下载完成%s - %s，耗时%s毫秒' %(symbol, l[0]['time_period_start'],
                                                  l[-1]['time_period_end'], cost))

#----------------------------------------------------------------------
def downloadAllMinuteBar(start, end):
    """下载所有配置中的合约的分钟线数据"""
    print('-' * 50)
    print(u'开始下载合约分钟线数据')
    print('-' * 50)
    
    for symbol in SYMBOLS:
        downMinuteBarBySymbol(symbol, '1MIN', start, end)
        time.sleep(1)

    print('-' * 50)
    print(u'合约分钟线数据下载完成')
    print('-' * 50)


    