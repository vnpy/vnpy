# encoding: UTF-8

"""
立即下载数据到数据库中，用于手动执行更新操作。
"""

from dataService import *


if __name__ == '__main__':
    #downloadMinuteBarBySymbol('BTC/USDT.OKEX', '20181012')
    #downloadMinuteBarBySymbol('BTC/USDT.HUOBIPRO', '20181012')
    #downloadMinuteBarBySymbol('BTC/USDT.BINANCE', '20181012')
    #downloadAllMinuteBar('20181012')
    
    downloadDailyBarBySymbol('BTC/USDT.BINANCE')