"""
Author: nanoric

Load data from a csv file.

Differences to 1.9.2:
    * combine Date column and Time column into one Datetime column

Sample csv file:

```csv
"Datetime","Open","High","Low","Close","Volume"
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


APP_NAME = "CsvLoader"


class CsvLoaderEngine(BaseEngine):
    """"""

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

    def load(self,
             file_path: str,
             symbol: str,
             exchange: Exchange,
             interval: Interval,
             datetime_head: str,
             open_head: str,
             close_head: str,
             low_head: str,
             high_head: str,
             volume_head: str):
        """"""
        vt_symbol = f"{symbol}.{exchange.value}"

        start = None
        end = None
        count = 0

        with open(file_path, 'rt') as f:
            reader = csv.DictReader(f)

            for item in reader:
                db_bar = DbBarData()

                db_bar.symbol = symbol
                db_bar.exchange = exchange.value
                db_bar.datetime = datetime.fromisoformat(item[datetime_head])
                db_bar.interval = interval.value
                db_bar.volume = item[volume_head]
                db_bar.open_price = item[open_head]
                db_bar.high_price = item[high_head]
                db_bar.low_price = item[low_head]
                db_bar.close_price = item[close_head]
                db_bar.vt_symbol = vt_symbol
                db_bar.gateway_name = "DB"

                db_bar.save()

                # do some statistics
                count += 1
                if not start:
                    start = db_bar.datetime

        end = db_bar.datetime

        return start, end, count
