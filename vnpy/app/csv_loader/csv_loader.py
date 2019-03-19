"""
Author: nanoric

Load data from a csv file.

Differences to 1.9.2:
    * combine Date column and Time column into one DateTime column

Sample csv file:

```csv
"DateTime","Open","High","Low","Close","Volume"
2010-04-16T09:16:00.000000,3450.0,3488.0,3450.0,3468.0,489
2010-04-16T09:17:00.000000,3468.0,3473.8,3467.0,3467.0,302
2010-04-16T09:18:00.000000,3467.0,3471.0,3466.0,3467.0,203
2010-04-16T09:19:00.000000,3467.0,3468.2,3448.0,3448.0,280
2010-04-16T09:20:00.000000,3448.0,3459.0,3448.0,3454.0,250
2010-04-16T09:21:00.000000,3454.0,3456.8,3454.0,3456.8,109
```

"""

import csv
from datetime import datetime

from vnpy.event import EventEngine
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.database import DbBarData
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import BarData

APP_NAME = "CsvLoader"


class CsvLoader(BaseEngine):

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.file_path: str = ''

        self.symbol: str = ""
        self.exchange: Exchange = Exchange.SSE
        self.interval: Interval = Interval.MINUTE
        self.datetime_head: str = ''
        self.open_head: str = ''
        self.close_head: str = ''
        self.low_head: str = ''
        self.high_head: str = ''
        self.volume_head: str = ''

    def load(self):
        """"""
        symbol = self.symbol
        exchange = self.exchange
        interval = self.interval

        datetime_head = self.datetime_head
        open_head = self.open_head
        close_head = self.close_head
        low_head = self.low_head
        high_head = self.high_head
        volume_head = self.volume_head

        with open(self.file_path, 'rt') as f:
            reader = csv.DictReader(f)
            for item in reader:
                bar = BarData(
                    '',
                    symbol,
                    exchange,
                    datetime.fromisoformat(item[datetime_head]),
                    interval,
                    item[volume_head],
                    item[open_head],
                    item[high_head],
                    item[low_head],
                    item[close_head],
                )
            DbBarData.from_bar(bar).save()
