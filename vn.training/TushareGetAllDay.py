#coding=utf8

import tushare as ts
import pymongo
import json
#import csv
import time

#conn = pymongo.Connection('222.73.15.21', port=7017)

i=0

while i < 10000:
    print time.localtime
    i=i+1
    code =  "%06d" % i
    print code
    df = ts.get_hist_data(code)

    #conn.db.DayAll.insert(json.loads(df.to_json(orient='index')))


