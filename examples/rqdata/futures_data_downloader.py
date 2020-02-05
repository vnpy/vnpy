"""
自动从CFList.csv的品种里下载数据并且保存到数据库，配合任务计划可以实现每日无人值守自动下载数据。
代码贡献者： Shouheng Zhang
Ver 1.0
"""

from datetime import datetime
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.utility import extract_vt_symbol
from vnpy.trader.object import HistoryRequest
from vnpy.trader.rqdata import rqdata_client
from vnpy.trader.database import database_manager
import csv
import rqdatac as rq


class RQDataDownload:

    def __init__(self):
        self.vt_symbol = ""
        self.interval = ""
        self.start = None
        self.end = None

        self.test = None

    def prep_download(self):
        # self.start = datetime(2011, 1, 1)

        self.end = datetime.now().date()
        # read csv commodities futures list
        with open('CFList.csv', 'r') as f:
            reader = csv.reader(f)
            CFList = list(reader)

        rq.init()
        today = rq.get_latest_trading_date()
        prevTradingDay = rq.get_previous_trading_date(today, 1, market='cn')

        for instrument in CFList:
            # check if changed the dominant contract for the latest trading day
            todayDominant = rq.futures.get_dominant(instrument[1], today)
            prevDayDominant = rq.futures.get_dominant(instrument[1], prevTradingDay)
            if todayDominant[today] == prevDayDominant[prevTradingDay]:
                self.start = prevTradingDay
            elif todayDominant[today] != prevDayDominant[prevTradingDay]:
                self.start = datetime(2011, 1, 1)
                print(f"品种 {instrument[1]} 的主力合约即日起从 {prevDayDominant[prevTradingDay]} 换到 {todayDominant[today]}")
            else:
                print("####### 检查主力合约过程中出错，请手动debug！")
            self.rq_download(instrument[0], '1m', self.start, self.end)
            self.rq_download(instrument[0], 'd', self.start, self.end)

    def rq_download(
            self,
            vt_symbol: str,
            interval: str,
            start: datetime,
            end: datetime,
    ):
        rqdata_client.init()
        symbol, exchange = extract_vt_symbol(vt_symbol)

        req = HistoryRequest(
            symbol=symbol,
            exchange=exchange,
            interval=Interval(interval),
            start=start,
            end=end
        )

        # print(req)

        data = rqdata_client.query_history(req)

        if data:
            database_manager.save_bar_data(data)
            print(f"{vt_symbol}-{interval} 历史数据下载完成")
        else:
            print(f"数据下载失败，无法得到 {vt_symbol} 的数据")

        # print(df)
        # print(data)

if __name__ == "__main__":
    # d1 = datetime(2019, 9, 1)
    # d2 = datetime(2019, 9, 10)
    a = RQDataDownload()
    a.prep_download()
    # a.rq_download('i888.DCE', '1m', d1, d2)