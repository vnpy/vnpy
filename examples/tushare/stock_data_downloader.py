"""
使用tushare接口自动下载股票的日线数据并保存到数据库，股票池可以自行定义，股票池文件为stock_pool.csv。
起始日期可以自行修改。
配合任务计划可以实现每日无人值守自动下载数据。
代码贡献者：Shouheng Zhang
Ver 1.0
"""

import tushare as ts
import os
import csv
from datetime import datetime
import time
from vnpy.app.csv_loader import CsvLoaderEngine
from vnpy.trader.constant import Exchange, Interval

# initial parameters
startDate = '20140101'
endDate = datetime.now().strftime("%Y%m%d")

pro = ts.pro_api()

# read csv stock pool
with open('stock_pool.csv', 'r') as f:
    reader = csv.reader(f)
    stockList = list(reader)

# download
for instrument in stockList:
    # print(instrument[0])
    for i in range(0, 5):
        while True:
            try:
                df = ts.pro_bar(ts_code=instrument[0], adj='qfq', start_date=startDate, end_date=endDate)
                df.to_csv('./stock_data/%s.csv' % instrument[0])
                time.sleep(1)
            except Exception:
                time.sleep(10)
                continue
            break

# check

for instrument in stockList:
    if os.path.getsize("./stock_data/%s.csv" % instrument[0]) / 1024 < 100:
        print(f'数据 {instrument[0]} 错误！文件大小太小，可能是空文件。')
    lastModifiedTime = os.path.getmtime("./stock_data/%s.csv" % instrument[0])
    currTime = time.time()
    if currTime - lastModifiedTime > 40 * 60:
        print(f'数据 {instrument[0]} 错误！今日文件未改变，请手动检查。')


# save data to database use csv loader
engine = CsvLoaderEngine(None, None)

with open('stock_pool.csv', 'r') as f:
    reader = csv.reader(f)
    stockList = list(reader)

for instrument in stockList:
    f = ("./stock_data/%s.csv" % instrument[0])
    if instrument[0][-2:] == 'SH':
        temp_exchange = Exchange.SSE
    elif instrument[0][-2:] == 'SZ':
        temp_exchange = Exchange.SZSE
    else:
        print(f'股票{instrument[0]}的交易所填写错误，请手动终止程序，并检查股票池文件！')
        os.system("pause")
    engine.load(
        f,
        symbol=instrument[0][:-3],
        exchange=temp_exchange,
        interval=Interval.DAILY,
        datetime_head="trade_date",
        open_head="open",
        close_head="close",
        low_head="low",
        high_head="high",
        volume_head="vol",
        datetime_format="%Y%m%d",
    )