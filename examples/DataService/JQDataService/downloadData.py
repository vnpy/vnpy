# encoding: UTF-8

"""
立即下载数据到数据库中，用于手动执行更新操作。
"""

from dataService import *


if __name__ == '__main__':
    # downloadAllMinuteBar("2018-01-01", "2018-02-01")
    # downMinuteBarBySymbol("000016.XSHG", "2018-01-01", "2018-01-10")
    downMinuteBarBySymbol("RB1905.XSGE", "2018-12-01", "2019-01-01")