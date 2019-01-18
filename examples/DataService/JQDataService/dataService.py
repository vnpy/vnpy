# encoding: UTF-8

from __future__ import print_function
import sys
import json
from datetime import datetime, timedelta
from time import time, sleep

from pymongo import MongoClient, ASCENDING

from vnpy.trader.vtObject import VtBarData
from vnpy.trader.app.ctaStrategy.ctaBase import MINUTE_DB_NAME

import jqdatasdk as jq

# 加载配置
config = open('config.json')
setting = json.load(config)

MONGO_HOST = setting['MONGO_HOST']
MONGO_PORT = setting['MONGO_PORT']
SYMBOLS = setting['SYMBOLS']
JQ_USERNAME = setting['JQ_USERNAME']
JQ_PASSWORD = setting['JQ_PASSWORD']

mc = MongoClient(MONGO_HOST, MONGO_PORT)        # Mongo连接
db = mc[MINUTE_DB_NAME]                         # 数据库
jq.auth(JQ_USERNAME, JQ_PASSWORD)               # 连接聚宽JQData
today = datetime.now().date()
startDate = (today - timedelta(10)).strftime('%Y-%m-%d')    # 数据下载起始日期


#----------------------------------------------------------------------
def generateVtBar(ix, row, symbol):
    """生成K线"""
    bar = VtBarData()
    
    bar.symbol = symbol
    bar.exchange = ''
    bar.vtSymbol = bar.symbol
    bar.open = row['open']
    bar.high = row['high']
    bar.low = row['low']
    bar.close = row['close']
    bar.volume = row['volume']
    bar.datetime = datetime.strptime(str(ix), '%Y-%m-%d %H:%M:%S')
    bar.date = bar.datetime.strftime("%Y%m%d")
    bar.time = bar.datetime.strftime("%H:%M:%S")
    
    return bar

#----------------------------------------------------------------------
def downMinuteBarBySymbol(symbol, start_date, end_date):
    """下载某一合约的分钟线数据"""
    start = time()

    cl = db[symbol]
    cl.ensure_index([('datetime', ASCENDING)], unique=True)         # 添加索引
    
    data = jq.get_price(symbol, start_date=start_date, end_date=end_date, frequency='minute', skip_paused=False, fq='pre', count=None)
    data = data.sort_index()
    
    for ix, row in data.iterrows():
        bar = generateVtBar(ix, row, symbol)
        d = bar.__dict__
        flt = {'datetime': bar.datetime}
        cl.replace_one(flt, d, True)            

    end = time()
    cost = (end - start) * 1000

    print(u'合约%s数据下载完成%s - %s，耗时%s毫秒' %(symbol, start_date, end_date, cost))

    
#----------------------------------------------------------------------
def downloadAllMinuteBar(start_date, end_date):
    """下载所有配置中的合约的分钟线数据"""
    print('-' * 50)
    print(u'开始下载合约分钟线数据')
    print('-' * 50)
    
    # 添加下载任务
    for symbol in SYMBOLS:
        downMinuteBarBySymbol(str(symbol), start_date, end_date)
    
    print('-' * 50)
    print(u'合约分钟线数据下载完成')
    print('-' * 50)
    


    