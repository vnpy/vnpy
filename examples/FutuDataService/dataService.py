# encoding: UTF-8

import sys
import json
from datetime import datetime, timedelta
from time import time, sleep

from pymongo import MongoClient, ASCENDING

from vnpy.trader.vtObject import VtBarData
from vnpy.trader.app.ctaStrategy.ctaBase import MINUTE_DB_NAME

import futuquant as ft

# 加载配置
config = open('config.json')
setting = json.load(config)

MONGO_HOST = setting['MONGO_HOST']
MONGO_PORT = setting['MONGO_PORT']
SYMBOLS = setting['SYMBOLS']

mc = MongoClient(MONGO_HOST, MONGO_PORT)        # Mongo连接
db = mc[MINUTE_DB_NAME]                         # 数据库
quote = ft.OpenQuoteContext()                   # 富途行情接口
today = datetime.now().date()
startDate = (today - timedelta(10)).strftime('%Y-%m-%d')    # 数据下载起始日期


#----------------------------------------------------------------------
def generateVtBar(row):
    """生成K线"""
    bar = VtBarData()
    
    bar.symbol = row['code']
    bar.exchange = ''
    bar.vtSymbol = bar.symbol
    bar.open = row['open']
    bar.high = row['high']
    bar.low = row['low']
    bar.close = row['close']
    bar.volume = row['volume']
    bar.datetime = datetime.strptime(row['time_key'], '%Y-%m-%d %H:%M:%S')
    bar.date = bar.datetime.strftime("%Y%m%d")
    bar.time = bar.datetime.strftime("%H:%M:%S")
    
    return bar

#----------------------------------------------------------------------
def downMinuteBarBySymbol(symbol):
    """下载某一合约的分钟线数据"""
    start = time()

    cl = db[symbol]
    cl.ensure_index([('datetime', ASCENDING)], unique=True)         # 添加索引
    
    code, data = quote.get_history_kline(symbol, start=startDate, ktype='K_1M')
    if code:
        print u'合约%s数据下载失败：%s' %(symbol, data)
        return
        
    data = data.sort_index()
    
    for ix, row in data.iterrows():
        bar = generateVtBar(row)
        d = bar.__dict__
        flt = {'datetime': bar.datetime}
        cl.replace_one(flt, d, True)            

    end = time()
    cost = (end - start) * 1000

    print u'合约%s数据下载完成%s - %s，耗时%s毫秒' %(symbol, data.iloc[0]['time_key'], 
                                                  data.iloc[-1]['time_key'], cost)

    
#----------------------------------------------------------------------
def downloadAllMinuteBar():
    """下载所有配置中的合约的分钟线数据"""
    print '-' * 50
    print u'开始下载合约分钟线数据'
    print '-' * 50
    
    # 添加下载任务
    for symbol in SYMBOLS:
        downMinuteBarBySymbol(str(symbol))
    
    print '-' * 50
    print u'合约分钟线数据下载完成'
    print '-' * 50
    


    