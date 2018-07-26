# encoding: UTF-8

"""
立即下载数据到数据库中，用于手动执行更新操作。
"""

from dataService import *


if __name__ == '__main__':
    downMinuteBarBySymbol('BINANCE_SPOT_BTC_USDT', '1MIN', '20180725', '20180726')