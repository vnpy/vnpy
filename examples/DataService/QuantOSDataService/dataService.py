# encoding: UTF-8

from __future__ import print_function

import datetime
import json
import time

import pandas as pd
from jaqs.data import DataApi
from pymongo import MongoClient, ASCENDING
from vnpy.trader.app.ctaStrategy.ctaBase import MINUTE_DB_NAME
from vnpy.trader.vtObject import VtBarData

"""
该文件使用到jaqs中的数据api，需要安装相关依赖和注册账号

1，注册账号（https://www.quantos.org），使用手机号注册，注册后获取API令牌。将手机号和令牌填入配置文件
2，安装jaqs（pip install jaqs），或参考https://www.quantos.org/jaqs/doc.html
3，市场代码说明 https://www.quantos.org/jaqs/doc.html
"""

# 加载配置
config = open('config.json')
setting = json.load(config)

MONGO_HOST = setting['MONGO_HOST']
MONGO_PORT = setting['MONGO_PORT']
QUANTOS_ADDR = setting['QUANTOS_ADDR']
PHONE = setting['PHONE']
QUANTOS_TOKEN = setting['QUANTOS_TOKEN']
SYMBOLS = setting['SYMBOLS']
START_DATE = setting['START_DATE']
END_DATE = setting['END_DATE']

api = DataApi(addr=QUANTOS_ADDR)  # 历史行情服务API对象
api.login(PHONE, QUANTOS_TOKEN)
mc = MongoClient(MONGO_HOST, MONGO_PORT)  # Mongo连接
db = mc[MINUTE_DB_NAME]  # 数据库


# ----------------------------------------------------------------------
def generateVtBar(d):
    """生成K线"""
    bar = VtBarData()

    bar.symbol = d['code']
    bar.vtSymbol = d['code']
    bar.date = str(d['date'])
    timeStr = str(d['time'])
    if len(timeStr) == 5:
        timeStr = '0' + timeStr
    bar.time = ':'.join([timeStr[:2], timeStr[2:4]])
    bar.open = d['open']
    bar.high = d['high']
    bar.low = d['low']
    bar.close = d['close']
    bar.volume = d['volume']
    bar.openInterest = d['oi']
    bar.datetime = datetime.datetime.strptime(' '.join([bar.date, bar.time]),
                                              '%Y%m%d %H:%M')
    return bar


# ---------------------------------------------------------------------
def downMinuteBarBySymbol(symbol, trade_date):
    """下载某一合约的分钟线数据"""
    start = time.time()

    cl = db[symbol.split('.')[0]]  # 集合
    cl.ensure_index([('datetime', ASCENDING)], unique=True)  # 添加索引

    df, msg = api.bar(symbol=symbol, trade_date=trade_date, freq="1M")
    for ix, row in df.iterrows():
        bar = generateVtBar(row)
        d = bar.__dict__
        flt = {'datetime': bar.datetime}
        cl.replace_one(flt, d, True)

    end = time.time()
    cost = (end - start) * 1000

    print(u'合约%s 日期%s 数据下载完成，耗时%s毫秒' % (symbol, trade_date, cost))


# ---------------------------------------------------------------------
def downloadAllMinuteBar(start_date, end_date):
    """下载所有配置中的合约的分钟线数据"""
    print('-' * 50)
    print(u'开始下载合约分钟线数据')
    print('-' * 50)

    for symbol in SYMBOLS:
        di = pd.date_range(start_date, end_date)
        for d in di:
            downMinuteBarBySymbol(symbol, str(d)[:10])
            time.sleep(1)

    print('-' * 50)
    print(u'合约分钟线数据下载完成')
    print('-' * 50)


if __name__ == '__main__':
    downloadAllMinuteBar(START_DATE, END_DATE)
