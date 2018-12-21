# encoding: UTF-8

from __future__ import print_function
import sys
import json
from datetime import datetime
from time import time, sleep

from pymongo import MongoClient, ASCENDING
import pandas as pd

from vnpy.trader.vtObject import VtBarData, VtTickData
from vnpy.trader.app.ctaStrategy.ctaBase import (MINUTE_DB_NAME, 
                                                 DAILY_DB_NAME, 
                                                 TICK_DB_NAME)

import rqdatac as rq

# 加载配置
config = open('config.json')
setting = json.load(config)

mc = MongoClient()                  # Mongo连接
dbMinute = mc[MINUTE_DB_NAME]       # 数据库
dbDaily = mc[DAILY_DB_NAME]
dbTick = mc[TICK_DB_NAME]

USERNAME = setting['rqUsername']
PASSWORD = setting['rqPassword']
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
def generateVtTick(row, symbol):
    """生成K线"""
    tick = VtTickData()
    tick.symbol = symbol
    tick.vtSymbol = symbol
    
    tick.lastPrice = row['last']
    tick.volume = row['volume']
    tick.openInterest = row['open_interest']
    tick.datetime = row.name
    tick.openPrice = row['open']
    tick.highPrice = row['high']
    tick.lowPrice = row['low']
    tick.preClosePrice = row['prev_close']
    tick.upperLimit = row['limit_up']
    tick.lowerLimit = row['limit_down']
    
    tick.bidPrice1 = row['b1']
    tick.bidPrice2 = row['b2']
    tick.bidPrice3 = row['b3']
    tick.bidPrice4 = row['b4']
    tick.bidPrice5 = row['b5']
    
    tick.bidVolume1 = row['b1_v']
    tick.bidVolume2 = row['b2_v']
    tick.bidVolume3 = row['b3_v']
    tick.bidVolume4 = row['b4_v']
    tick.bidVolume5 = row['b5_v']    
    
    tick.askPrice1 = row['a1']
    tick.askPrice2 = row['a2']
    tick.askPrice3 = row['a3']
    tick.askPrice4 = row['a4']
    tick.askPrice5 = row['a5']
    
    tick.askVolume1 = row['a1_v']
    tick.askVolume2 = row['a2_v']
    tick.askVolume3 = row['a3_v']
    tick.askVolume4 = row['a4_v']
    tick.askVolume5 = row['a5_v']        
    
    return tick

#----------------------------------------------------------------------
def downloadMinuteBarBySymbol(symbol):
    """下载某一合约的分钟线数据"""
    start = time()

    cl = dbMinute[symbol]
    cl.ensure_index([('datetime', ASCENDING)], unique=True)         # 添加索引
    
    df = rq.get_price(symbol, frequency='1m', fields=FIELDS)
    
    for ix, row in df.iterrows():
        bar = generateVtBar(row, symbol)
        d = bar.__dict__
        flt = {'datetime': bar.datetime}
        cl.replace_one(flt, d, True)            

    end = time()
    cost = (end - start) * 1000

    print(u'合约%s的分钟K线数据下载完成%s - %s，耗时%s毫秒' %(symbol, df.index[0], df.index[-1], cost))

#----------------------------------------------------------------------
def downloadDailyBarBySymbol(symbol):
    """下载某一合约日线数据"""
    start = time()

    cl = dbDaily[symbol]
    cl.ensure_index([('datetime', ASCENDING)], unique=True)         # 添加索引
    
    df = rq.get_price(symbol, frequency='1d', fields=FIELDS, end_date=datetime.now().strftime('%Y%m%d'))
    
    for ix, row in df.iterrows():
        bar = generateVtBar(row, symbol)
        d = bar.__dict__
        flt = {'datetime': bar.datetime}
        cl.replace_one(flt, d, True)            

    end = time()
    cost = (end - start) * 1000

    print(u'合约%s的日K线数据下载完成%s - %s，耗时%s毫秒' %(symbol, df.index[0], df.index[-1], cost))

#----------------------------------------------------------------------
def downloadTickBySymbol(symbol, date):
    """下载某一合约日线数据"""
    start = time()

    cl = dbTick[symbol]
    cl.ensure_index([('datetime', ASCENDING)], unique=True)         # 添加索引
    
    df = rq.get_price(symbol, 
                      frequency='tick', 
                      start_date=date, 
                      end_date=date)
    
    for ix, row in df.iterrows():
        tick = generateVtTick(row, symbol)
        d = tick.__dict__
        flt = {'datetime': tick.datetime}
        cl.replace_one(flt, d, True)            

    end = time()
    cost = (end - start) * 1000

    print(u'合约%sTick数据下载完成%s - %s，耗时%s毫秒' %(symbol, df.index[0], df.index[-1], cost))
