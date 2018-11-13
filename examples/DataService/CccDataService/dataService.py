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
config = open("config.json")
setting = json.load(config)

MONGO_HOST = setting["MONGO_HOST"]
MONGO_PORT = setting["MONGO_PORT"]
SYMBOLS = setting["SYMBOLS"]

mc = MongoClient(MONGO_HOST, MONGO_PORT)  # Mongo连接
db = mc[MINUTE_DB_NAME]  # 数据库


# ----------------------------------------------------------------------
def generateVtBar(vtSymbol, d):
    """生成K线"""
    bar = VtBarData()
    bar.vtSymbol = vtSymbol
    bar.symbol, bar.exchange = bar.vtSymbol.split(".")

    bar.datetime = datetime.datetime.fromtimestamp(d["time"])
    bar.date = bar.datetime.strftime("%Y%m%d")
    bar.time = bar.datetime.strftime("%H:%M:%S")

    bar.open = d["open"]
    bar.high = d["high"]
    bar.low = d["low"]
    bar.close = d["close"]
    bar.volume = d["volumeto"]

    return bar


# ----------------------------------------------------------------------
def downloadMinuteBarBySymbol(vtSymbol, end):
    """下载某一合约的分钟线数据"""
    end = datetime.datetime.strptime(end, "%Y%m%d")
    startTime = time.time()

    cl = db[vtSymbol]
    cl.ensure_index([("datetime", ASCENDING)], unique=True)

    symbol, exchange = vtSymbol.split(".")
    fsym, tsym = symbol.split("/")

    url = "https://min-api.cryptocompare.com/data/histominute"
    params = {
        "fsym": fsym,
        "tsym": tsym,
        "e": exchange,
        "toTs": int(time.mktime(end.timetuple())),
    }
    resp = requests.get(url, headers={}, params=params)

    if resp.status_code != 200:
        print(u"%s数据下载失败" % vtSymbol)
        return

    j = resp.json()
    l = j["Data"]

    for d in l:
        bar = generateVtBar(vtSymbol, d)
        d = bar.__dict__
        flt = {"datetime": bar.datetime}
        cl.replace_one(flt, d, True)

    endTime = time.time()
    cost = (endTime - startTime) * 1000

    print(
        u"合约%s数据下载完成%s - %s，耗时%s毫秒"
        % (
            vtSymbol,
            datetime.datetime.fromtimestamp(l[0]["time"]),
            datetime.datetime.fromtimestamp(l[-1]["time"]),
            cost,
        )
    )


# ----------------------------------------------------------------------
def downloadAllMinuteBar(end):
    """下载所有配置中的合约的分钟线数据"""
    print("-" * 50)
    print(u"开始下载合约分钟线数据")
    print("-" * 50)

    for symbol in SYMBOLS:
        downloadMinuteBarBySymbol(symbol, end)
        time.sleep(1)

    print("-" * 50)
    print(u"合约分钟线数据下载完成")
    print("-" * 50)
