# encoding: UTF-8

import sys
import json
from datetime import datetime, timedelta
from time import time, sleep

from pymongo import MongoClient, ASCENDING

from vnpy.trader.vtObject import VtBarData
from vnpy.trader.app.ctaStrategy.ctaBase import MINUTE_DB_NAME
from vnpy.trader.gateway.tkproGateway.DataApi import DataApi


# 交易所类型映射
exchangeMap = {}
exchangeMap['CFFEX'] = 'CFE'
exchangeMap['SHFE'] = 'SHF'
exchangeMap['CZCE'] = 'CZC'
exchangeMap['DCE'] = 'DCE'
exchangeMap['SSE'] = 'SH'
exchangeMap['SZSE'] = 'SZ'
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 加载配置
config = open('config.json')
setting = json.load(config)
config.close()

MONGO_HOST = setting['MONGO_HOST']
MONGO_PORT = setting['MONGO_PORT']
SYMBOLS = setting['SYMBOLS']
USERNAME = setting['USERNAME']
TOKEN = setting['TOKEN']
DATA_SERVER = setting['DATA_SERVER']

# 创建API对象
mc = MongoClient(MONGO_HOST, MONGO_PORT)        # Mongo连接
db = mc[MINUTE_DB_NAME]                         # 数据库


#----------------------------------------------------------------------
def generateVtBar(row):
    """生成K线"""
    bar = VtBarData()
    
    symbol, exchange = row['symbol'].split('.')
    
    bar.symbol = symbol
    bar.exchange = exchangeMapReverse[exchange]
    bar.vtSymbol = '.'.join([bar.symbol, bar.exchange])
    bar.open = row['open']
    bar.high = row['high']
    bar.low = row['low']
    bar.close = row['close']
    bar.volume = row['volume']
    
    bar.date = str(row['trade_date'])
    bar.time = str(row['time'])
    bar.datetime = datetime.strptime(' '.join([bar.date, bar.time]), '%Y%m%d %H%M%S')
    
    return bar

#----------------------------------------------------------------------
def downMinuteBarBySymbol(api, vtSymbol, startDate):
    """下载某一合约的分钟线数据"""
    start = time()

    cl = db[vtSymbol]
    cl.ensure_index([('datetime', ASCENDING)], unique=True)         # 添加索引
    
    dt = datetime.strptime(startDate, '%Y%m%d')
    today = datetime.now()
    delta = timedelta(1)
    
    code, exchange = vtSymbol.split('.')
    symbol = '.'.join([code, exchangeMap[exchange]]) 
    
    while dt <= today:
        d = int(dt.strftime('%Y%m%d'))
        df, msg = api.bar(symbol, freq='1M', trade_date=d)
        dt += delta
        
        if df is None:
            continue
        
        for ix, row in df.iterrows():
            bar = generateVtBar(row)
            d = bar.__dict__
            flt = {'datetime': bar.datetime}
            cl.replace_one(flt, d, True)    
        

    end = time()
    cost = (end - start) * 1000

    print u'合约%s数据下载完成%s - %s，耗时%s毫秒' %(vtSymbol, startDate, today.strftime('%Y%m%d'), cost)

    
#----------------------------------------------------------------------
def downloadAllMinuteBar(api):
    """下载所有配置中的合约的分钟线数据"""
    print '-' * 50
    print u'开始下载合约分钟线数据'
    print '-' * 50
    
    startDt = datetime.today() - 10 * timedelta(1)
    startDate = startDt.strftime('%Y%m%d')
    
    # 添加下载任务
    for symbol in SYMBOLS:
        downMinuteBarBySymbol(api, str(symbol), startDate)
    
    print '-' * 50
    print u'合约分钟线数据下载完成'
    print '-' * 50
    

if __name__ == '__main__':
    downloadAllMinuteBar()
    