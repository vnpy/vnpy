#!/usr/bin/env python
# coding=utf8
"""
上交所，市场代码 SHSE
深交所，市场代码 SZSE
中金所，市场代码 CFFEX
上期所，市场代码 SHFE
大商所，市场代码 DCE
郑商所，市场代码 CZCE
纽约商品交易所， 市场代码 CMX (GLN, SLN)
伦敦国际石油交易所， 市场代码 IPE (OIL, GAL)
纽约商业交易所， 市场代码 NYM (CON, HON)
芝加哥商品期货交易所，市场代码 CBT (SOC, SBC, SMC, CRC)
纽约期货交易所，市场代码 NYB (SGN)

"""
from gmsdk.api import md
from vtGateway import VtTickData

ret = md.init(
    username='171322809@qq.com',
    password='88888888',
    mode=2
)

import arrow


def to_local(utc):
    return arrow.get(utc).to('local')


def gm_to_vt(exchange, sym, tick):
    obj = VtTickData()

    obj.symbol = sym              # 合约代码
    obj.exchange = exchange            # 交易所代码
    obj.vtSymbol = sym            # 合约在vt系统中的唯一代码，通常是 合约代码.交易所代码

    local_time = to_local(tick.utc_time)
    # 成交数据
    obj.lastPrice = round(tick.last_price, 2)            # 最新成交价
    obj.lastVolume = tick.last_volume             # 最新成交量
    obj.volume = tick.cum_volume                 # 今天总成交量
    obj.openInterest = tick.cum_position           # 持仓量
    obj.time = local_time.strftime('%H:%M:%S')                # 时间 11:20:56.5
    obj.date = local_time.strftime('%Y%m%d')                # 日期 20151009

    # 常规行情
    obj.openPrice = tick.open            # 今日开盘价
    obj.highPrice = tick.high            # 今日最高价
    obj.lowPrice = tick.low             # 今日最低价
    obj.preClosePrice = tick.pre_close

    obj.upperLimit = tick.upper_limit           # 涨停价
    obj.lowerLimit = tick.lower_limit           # 跌停价

    # 一档行情
    obj.bidPrice1, obj.bidVolume1 = tick.bids[0]

    obj.askPrice1, obj.askVolume1 = tick.asks[0]
    return obj


def get_last_n_ticks(exchange, sym, n):
    ticks = md.get_last_n_ticks('%s.%s' % (exchange, sym), 10)
    res = []
    for tick in ticks:
        res.append(gm_to_vt(exchange, sym, tick))
    return res[::-1]


if __name__ == '__main__':
    for tick in get_last_n_ticks('SHFE', 'ag1606', 10):
        print tick.date, tick.time, tick
