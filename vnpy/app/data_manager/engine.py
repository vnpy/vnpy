import csv
from datetime import datetime
from typing import List, Dict

from vnpy.trader.engine import BaseEngine, MainEngine, EventEngine
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.object import BarData
from vnpy.trader.database import database_manager
from vnpy.trader.utility import extract_vt_symbol


APP_NAME = "DataManager"


class ManagerEngine(BaseEngine):
    """"""

    def __init__(
        self,
        main_engine: MainEngine,
        event_engine: EventEngine,
    ):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

    def import_data_from_csv(
        self,
        file_path: str,
        vt_symbol: str,
        interval: Interval,
        datetime_head: str,
        open_head: str,
        high_head: str,
        low_head: str,
        close_head: str,
        volume_head: str,
        open_interest_head: str,
        datetime_format: str
    ) -> None:
        """"""
        with open(file_path, "rt") as f:
            buf = [line.replace("\0", "") for line in f]

        reader = csv.DictReader(buf, delimiter=",")

        bars = []
        start = None
        count = 0
        symbol, exchange = extract_vt_symbol(vt_symbol)

        for item in reader:
            if datetime_format:
                dt = datetime.strptime(item[datetime_head], datetime_format)
            else:
                dt = datetime.fromisoformat(item[datetime_head])

            open_interest = item.get(open_interest_head, 0)

            bar = BarData(
                symbol=symbol,
                exchange=exchange,
                datetime=dt,
                interval=interval,
                volume=item[volume_head],
                open_price=item[open_head],
                high_price=item[high_head],
                low_price=item[low_head],
                close_price=item[close_head],
                open_interest=open_interest,
                gateway_name="DB",
            )

            bars.append(bar)

            # do some statistics
            count += 1
            if not start:
                start = bar.datetime

        # insert into database
        database_manager.save_bar_data(bars)

        end = bar.datetime
        return start, end, count

    def output_data_to_csv(
        self,
        file_path: str,
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        start: datetime,
        end: datetime
    ) -> None:
        """"""
        bars = self.load_bar_data(symbol, exchange, interval, start, end)

        fieldnames = [
            "symbol",
            "exchange",
            "datetime",
            "open",
            "high",
            "low",
            "close",
            "volume",
            "open_interest"
        ]

        with open(file_path, "w") as f:
            writer = csv.DictWriter(f, fieldnames=fieldnames, lineterminator="\n")
            writer.writeheader()

            for bar in bars:
                d = {
                    "symbol": bar.symbol,
                    "exchange": bar.exchange.value,
                    "datetime": bar.datetime.strftime("%Y-%m-%d %H:%M:%S"),
                    "open": bar.open_price,
                    "high": bar.high_price,
                    "low": bar.low_price,
                    "close": bar.close_price,
                    "volume": bar.volume,
                    "open_interest": bar.open_interest,
                }
                writer.writerow(d)

    def get_bar_data_available(self) -> List[Dict]:
        """"""
        data = database_manager.get_bar_data_statistics()

        for d in data:
            oldest_bar = database_manager.get_oldest_bar_data(
                d["symbol"], Exchange(d["exchange"]), d["interval"]
            )
            d["start"] = oldest_bar.datetime

            newest_bar = database_manager.get_newest_bar_data(
                d["symbol"], Exchange(d["exchange"]), d["interval"]
            )
            d["end"] = newest_bar.datetime

        return data

    def load_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        start: datetime,
        end: datetime
    ) -> List[BarData]:
        """"""
        bars = database_manager.load_bar_data(
            symbol,
            exchange,
            interval,
            start,
            end
        )

        return bars
