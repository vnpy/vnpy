# encoding: UTF-8

from __future__ import print_function
import sys
import json
from datetime import datetime
from time import time, sleep

from pymongo import MongoClient, ASCENDING

from vnpy.trader.vtObject import VtBarData
from vnpy.trader.app.ctaStrategy.ctaBase import MINUTE_DB_NAME

import rqdatac as rq

# 加载配置
config = open('config.json')
setting = json.load(config)

MONGO_HOST = setting['MONGO_HOST']
MONGO_PORT = setting['MONGO_PORT']
SYMBOLS = setting['SYMBOLS']

mc = MongoClient(MONGO_HOST, MONGO_PORT)        # Mongo连接
db = mc[MINUTE_DB_NAME]                         # 数据库

USERNAME = setting['USERNAME']
PASSWORD = setting['PASSWORD']
rq.init(USERNAME, PASSWORD)

FIELDS = ['open', 'high', 'low', 'close', 'volume']

#----------------------------------------------------------------------
def generateVtBar(row, symbol):
    """生成K线"""
    bar = VtBarData()
    
    bar.symbol = symbol
    bar.vtSymbol = symbol
    bar.open = row['open']
    bar.high = row['high']
    bar.low = row['low']
    bar.close = row['close']
    bar.volume = row['volume']
    bar.datetime = row.name
    bar.date = bar.datetime.strftime("%Y%m%d")
    bar.time = bar.datetime.strftime("%H:%M:%S")
    
    return bar

#----------------------------------------------------------------------
def downMinuteBarBySymbol(symbol):
    """下载某一合约的分钟线数据"""
    start = time()

    cl = db[symbol]
    cl.ensure_index([('datetime', ASCENDING)], unique=True)         # 添加索引
    
    df = rq.get_price(symbol, frequency='1m', fields=FIELDS)
    
    for ix, row in df.iterrows():
        bar = generateVtBar(row, symbol)
        d = bar.__dict__
        flt = {'datetime': bar.datetime}
        cl.replace_one(flt, d, True)            

    end = time()
    cost = (end - start) * 1000

    print(u'合约%s数据下载完成%s - %s，耗时%s毫秒' %(symbol, df.index[0], df.index[-1], cost))

    
#----------------------------------------------------------------------
def downloadAllMinuteBar():
    """下载所有配置中的合约的分钟线数据"""
    print('-' * 50)
    print(u'开始下载合约分钟线数据')
    print('-' * 50)
    
    # 添加下载任务
    for symbol in SYMBOLS:
        downMinuteBarBySymbol(str(symbol))
    
    print('-' * 50)
    print(u'合约分钟线数据下载完成')
    print('-' * 50)
    


    