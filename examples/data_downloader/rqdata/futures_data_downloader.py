"""
自动从cf_list.csv的品种里下载数据并且保存到数据库，配合任务计划可以实现每日无人值守自动下载数据。
注意：第一次下载时，请将self.download_full改为True，每天都有连续下载时，设为False即可，但如果中间有中断，还是建议
下一次再设为True，直到连续每日下载才改为False。
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

        # change here to True if you want to download full history instead of download previous trading day only
        self.download_full = False

    def prep_download(self):
        # self.start = datetime(2011, 1, 1)

        self.end = datetime.now().date()
        # read csv commodities futures list
        with open('cf_list.csv', 'r') as f:
            reader = csv.reader(f)
            cf_list = list(reader)

        rq.init()
        today = rq.get_latest_trading_date()
        prev_trading_day = rq.get_previous_trading_date(today, 1, market='cn')

        for instrument in cf_list:
            # check if changed the dominant contract for the latest trading day
            today_dominant = rq.futures.get_dominant(instrument[1], today)
            prev_day_dominant = rq.futures.get_dominant(instrument[1], prev_trading_day)
            if today_dominant[today] == prev_day_dominant[prev_trading_day]:
                self.start = prev_trading_day
            elif today_dominant[today] != prev_day_dominant[prev_trading_day]:
                self.start = datetime(2011, 1, 1)
                print(f"品种 {instrument[1]} 的主力合约即日起从 {prev_day_dominant[prev_trading_day]} 换到 {today_dominant[today]}")
            else:
                print("####### 检查主力合约过程中出错，请手动debug！")
            if self.download_full == True:
                self.start = datetime(2011, 1, 1)
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