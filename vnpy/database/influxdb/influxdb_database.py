""""""
from datetime import datetime
from typing import List
import shelve

from influxdb import InfluxDBClient

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import BarData, TickData
from vnpy.trader.database import (
    BaseDatabase,
    BarOverview,
    DB_TZ,
    convert_tz
)
from vnpy.trader.setting import SETTINGS
from vnpy.trader.utility import (
    generate_vt_symbol,
    extract_vt_symbol,
    get_file_path
)


class InfluxdbDatabase(BaseDatabase):
    """"""
    overview_filename = "influxdb_overview"
    overview_filepath = str(get_file_path(overview_filename))

    def __init__(self) -> None:
        """"""
        database = SETTINGS["database.database"]
        user = SETTINGS["database.user"]
        password = SETTINGS["database.password"]
        host = SETTINGS["database.host"]
        port = SETTINGS["database.port"]

        self.client = InfluxDBClient(host, port, user, password, database)
        self.client.create_database(database)

    def save_bar_data(self, bars: List[BarData]) -> bool:
        """"""
        json_body = []

        bar = bars[0]
        vt_symbol = bar.vt_symbol
        interval = bar.interval

        for bar in bars:
            bar.datetime = convert_tz(bar.datetime)

            d = {
                "measurement": "bar_data",
                "tags": {
                    "vt_symbol": vt_symbol,
                    "interval": interval.value
                },
                "time": bar.datetime.isoformat(),
                "fields": {
                    "open_price": bar.open_price,
                    "high_price": bar.high_price,
                    "low_price": bar.low_price,
                    "close_price": bar.close_price,
                    "volume": bar.volume,
                    "open_interest": bar.open_interest,
                }
            }
            json_body.append(d)

        self.client.write_points(json_body, batch_size=10000)

        # Update bar overview
        symbol, exchange = extract_vt_symbol(vt_symbol)
        key = f"{vt_symbol}_{interval.value}"

        f = shelve.open(self.overview_filepath)
        overview = f.get(key, None)

        if not overview:
            overview = BarOverview(
                symbol=symbol,
                exchange=exchange,
                interval=interval
            )
            overview.count = len(bars)
            overview.start = bars[0].datetime
            overview.end = bars[-1].datetime
        else:
            overview.start = min(overview.start, bars[0].datetime)
            overview.end = max(overview.end, bars[-1].datetime)

            query = (
                "select count(close_price) from bar_data"
                " where vt_symbol=$vt_symbol"
                " and interval=$interval"
            )
            bind_params = {
                "vt_symbol": vt_symbol,
                "interval": interval.value
            }
            result = self.client.query(query, bind_params=bind_params)
            points = result.get_points()

            for d in points:
                overview.count = d["count"]

        f[key] = overview
        f.close()

    def save_tick_data(self, ticks: List[TickData]) -> bool:
        """"""
        pass

    def load_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        start: datetime,
        end: datetime
    ) -> List[BarData]:
        """"""
        query = (
            "select * from bar_data"
            " where vt_symbol=$vt_symbol"
            " and interval=$interval"
            f" and time >= '{start.date().isoformat()}'"
            f" and time <= '{end.date().isoformat()}';"
        )

        bind_params = {
            "vt_symbol": generate_vt_symbol(symbol, exchange),
            "interval": interval.value
        }

        result = self.client.query(query, bind_params=bind_params)
        points = result.get_points()

        bars: List[BarData] = []
        for d in points:
            dt = datetime.strptime(d["time"], "%Y-%m-%dT%H:%M:%SZ")

            bar = BarData(
                symbol=symbol,
                exchange=exchange,
                interval=interval,
                datetime=DB_TZ.localize(dt),
                open_price=d["open_price"],
                high_price=d["high_price"],
                low_price=d["low_price"],
                close_price=d["close_price"],
                volume=d["volume"],
                open_interest=d["open_interest"],
                gateway_name="DB"
            )
            bars.append(bar)

        return bars

    def load_tick_data(
        self,
        symbol: str,
        exchange: Exchange,
        start: datetime,
        end: datetime
    ) -> List[TickData]:
        """"""
        pass

    def delete_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval
    ) -> int:
        """"""
        bind_params = {
            "vt_symbol": generate_vt_symbol(symbol, exchange),
            "interval": interval.value
        }

        # Query data count
        query1 = (
            "select count(close_price) from bar_data"
            " where vt_symbol=$vt_symbol"
            " and interval=$interval"
        )
        result = self.client.query(query1, bind_params=bind_params)
        points = result.get_points()

        for d in points:
            count = d["count"]

        # Delete data
        query2 = (
            "drop series from bar_data"
            " where vt_symbol=$vt_symbol"
            " and interval=$interval"
        )
        self.client.query(query2, bind_params=bind_params)

        # Delete overview
        f = shelve.open(self.overview_filepath)
        vt_symbol = generate_vt_symbol(symbol, exchange)
        key = f"{vt_symbol}_{interval.value}"
        if key in f:
            f.pop(key)
        f.close()

        return count

    def delete_tick_data(
        self,
        symbol: str,
        exchange: Exchange
    ) -> int:
        """"""
        pass

    def get_bar_overview(self) -> List[BarOverview]:
        """
        Return data avaible in database.
        """
        # Init bar overview if not exists
        query = "select count(close_price) from bar_data"
        result = self.client.query(query)
        points = result.get_points()
        data_count = 0
        for d in points:
            data_count = d["count"]

        f = shelve.open(self.overview_filepath)
        overview_count = len(f)

        if data_count and not overview_count:
            self.init_bar_overview()

        overviews = list(f.values())
        f.close()
        return overviews

    def init_bar_overview(self) -> None:
        """
        Init overview table if not exists.
        """
        f = shelve.open(self.overview_filepath)

        query: str = "select count(close_price) from bar_data group by *"
        result = self.client.query(query)

        for k, v in result.items():
            tags = k[1]
            data = list(v)[0]

            vt_symbol = tags["vt_symbol"]
            symbol, exchange = extract_vt_symbol(vt_symbol)
            interval = Interval(tags["interval"])

            overview = BarOverview(
                symbol=symbol,
                exchange=exchange,
                interval=interval,
                count=data["count"]
            )
            overview.start = self.get_bar_datetime(vt_symbol, interval, 1)
            overview.end = self.get_bar_datetime(vt_symbol, interval, -1)

            key = f"{vt_symbol}_{interval.value}"
            f[key] = overview

        f.close()

    def get_bar_datetime(self, vt_symbol: str, interval: Interval, order: int) -> datetime:
        """"""
        if order > 0:
            keyword = "last"
        else:
            keyword = "first"

        query = (
            f"select {keyword}(close_price), * from bar_data"
            " where vt_symbol=$vt_symbol"
            " and interval=$interval"
        )

        bind_params = {
            "vt_symbol": vt_symbol,
            "interval": interval.value
        }

        result = self.client.query(query, bind_params=bind_params)
        points = result.get_points()

        for d in points:
            dt = datetime.strptime(d["time"], "%Y-%m-%dT%H:%M:%SZ")

        return dt


database_manager = InfluxdbDatabase()
