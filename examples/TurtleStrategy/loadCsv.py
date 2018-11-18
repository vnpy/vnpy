# encoding: UTF-8

from csv import DictReader
from datetime import datetime
from pymongo import MongoClient

from vnpy.trader.vtObject import VtBarData

from turtleEngine import DAILY_DB_NAME


#----------------------------------------------------------------------
def loadCsv(filename):
    """"""
    symbol = filename.split('.')[0]
    
    mc = MongoClient()
    db = mc[DAILY_DB_NAME]
    collection = db[symbol]
    
    with open(filename) as f:
        r = DictReader(f)
        for d in r:
            bar = VtBarData()
            bar.datetime = datetime.strptime(d['date'], '%Y/%m/%d')
            bar.vtSymbol = symbol
            bar.open = float(d['open'])
            bar.high = float(d['high'])
            bar.low = float(d['low'])
            bar.close = float(d['close'])
            bar.volume= int(d['volume'])
        
            collection.insert(bar.__dict__)
    
if __name__ == '__main__':
    loadCsv('000300.csv')
    loadCsv('000905.csv')