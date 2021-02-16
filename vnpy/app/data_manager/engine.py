import csv
from datetime import datetime
from typing import List, Tuple

from vnpy.trader.database import BarOverview, DB_TZ
from vnpy.trader.engine import BaseEngine, MainEngine, EventEngine
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.object import BarData, HistoryRequest
from vnpy.trader.rqdata import rqdata_client
from vnpy.trader.database import database_manager


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
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        datetime_head: str,
        open_head: str,
        high_head: str,
        low_head: str,
        close_head: str,
        volume_head: str,
        open_interest_head: str,
        datetime_format: str
    ) -> Tuple:
        """"""
        with open(file_path, "rt") as f:
            buf = [line.replace("\0", "") for line in f]

        reader = csv.DictReader(buf, delimiter=",")

        bars = []
        start = None
        count = 0

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
                volume=float(item[volume_head]),
                open_price=float(item[open_head]),
                high_price=float(item[high_head]),
                low_price=float(item[low_head]),
                close_price=float(item[close_head]),
                open_interest=float(open_interest),
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
    ) -> bool:
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

        try:
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

            return True
        except PermissionError:
            return False

    def get_bar_overview(self) -> List[BarOverview]:
        """"""
        return database_manager.get_bar_overview()

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

    def delete_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval
    ) -> int:
        """"""
        count = database_manager.delete_bar_data(
            symbol,
            exchange,
            interval
        )

        return count

    def download_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: str,
        start: datetime
    ) -> int:
        """
        Query bar data from RQData.
        """
        req = HistoryRequest(
            symbol=symbol,
            exchange=exchange,
            interval=Interval(interval),
            start=start,
            end=datetime.now(DB_TZ)
        )

        vt_symbol = f"{symbol}.{exchange.value}"
        contract = self.main_engine.get_contract(vt_symbol)

        # If history data provided in gateway, then query
        if contract and contract.history_data:
            data = self.main_engine.query_history(
                req, contract.gateway_name
            )
        # Otherwise use RQData to query data
        else:
            if not rqdata_client.inited:
                rqdata_client.init()

            data = rqdata_client.query_history(req)

        if data:
            database_manager.save_bar_data(data)
            return(len(data))

        return 0

    def download_tick_data(
        self,
        symbol: str,
        exchange: Exchange,
        start: datetime
    ) -> int:
        """
        Query tick data from RQData.
        """
        req = HistoryRequest(
            symbol=symbol,
            exchange=exchange,
            start=start,
            end=datetime.now(DB_TZ)
        )

        if not rqdata_client.inited:
            rqdata_client.init()

        data = rqdata_client.query_tick_history(req)

        if data:
            database_manager.save_tick_data(data)
            return(len(data))

        return 0
