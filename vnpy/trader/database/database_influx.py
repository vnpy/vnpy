from datetime import datetime
from typing import Optional, Sequence, List

from influxdb import InfluxDBClient

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import BarData, TickData
from vnpy.trader.utility import generate_vt_symbol

from .database import BaseDatabaseManager, Driver, DB_TZ


influx_database = ""
influx_client = None


def init(_: Driver, settings: dict):
    database = settings["database"]
    host = settings["host"]
    port = settings["port"]
    username = settings["user"]
    password = settings["password"]

    if not username:  # if username == '' or None, skip username
        username = "root"
        password = "root"

    global influx_client
    global influx_database

    influx_database = database
    influx_client = InfluxDBClient(host, port, username, password, database)
    influx_client.create_database(database)

    return InfluxManager()


class InfluxManager(BaseDatabaseManager):

    def load_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        start: datetime,
        end: datetime,
    ) -> Sequence[BarData]:
        query = (
            "select * from bar_data"
            " where vt_symbol=$vt_symbol"
            " and interval=$interval"
            f" and time >= '{start.isoformat()}'"
            f" and time <= '{end.isoformat()}';"
        )

        bind_params = {
            "vt_symbol": generate_vt_symbol(symbol, exchange),
            "interval": interval.value
        }

        result = influx_client.query(query, bind_params=bind_params)
        points = result.get_points()

        data = []
        for d in points:
            dt = datetime.strptime(d["time"], "%Y-%m-%dT%H:%M:%SZ")

            bar = BarData(
                symbol=symbol,
                exchange=exchange,
                interval=interval,
                datetime=dt.replace(tzinfo=DB_TZ),
                open_price=d["open_price"],
                high_price=d["high_price"],
                low_price=d["low_price"],
                close_price=d["close_price"],
                volume=d["volume"],
                open_interest=d["open_interest"],
                gateway_name="DB"
            )
            data.append(bar)

        return data

    def load_tick_data(
        self, symbol: str, exchange: Exchange, start: datetime, end: datetime
    ) -> Sequence[TickData]:
        pass

    def save_bar_data(self, data: Sequence[BarData]):
        json_body = []

        bar = data[0]
        vt_symbol = bar.vt_symbol
        interval = bar.interval.value

        for bar in data:
            dt = bar.datetime.astimezone(DB_TZ)
            dt = dt.replace(tzinfo=None)

            d = {
                "measurement": "bar_data",
                "tags": {
                    "vt_symbol": vt_symbol,
                    "interval": interval
                },
                "time": dt.isoformat(),
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

        influx_client.write_points(json_body)

    def save_tick_data(self, data: Sequence[TickData]):
        pass

    def get_newest_bar_data(
        self, symbol: str, exchange: "Exchange", interval: "Interval"
    ) -> Optional["BarData"]:
        query = (
            "select last(close_price), * from bar_data"
            " where vt_symbol=$vt_symbol"
            " and interval=$interval"
        )

        bind_params = {
            "vt_symbol": generate_vt_symbol(symbol, exchange),
            "interval": interval.value
        }

        result = influx_client.query(query, bind_params=bind_params)
        points = result.get_points()

        bar = None
        for d in points:
            dt = datetime.strptime(d["time"], "%Y-%m-%dT%H:%M:%SZ")

            bar = BarData(
                symbol=symbol,
                exchange=exchange,
                interval=interval,
                datetime=dt.replace(tzinfo=DB_TZ),
                open_price=d["open_price"],
                high_price=d["high_price"],
                low_price=d["low_price"],
                close_price=d["close_price"],
                volume=d["volume"],
                open_interest=d["open_interest"],
                gateway_name="DB"
            )

        return bar

    def get_oldest_bar_data(
        self, symbol: str, exchange: "Exchange", interval: "Interval"
    ) -> Optional["BarData"]:
        query = (
            "select first(close_price), * from bar_data"
            " where vt_symbol=$vt_symbol"
            " and interval=$interval"
        )

        bind_params = {
            "vt_symbol": generate_vt_symbol(symbol, exchange),
            "interval": interval.value
        }

        result = influx_client.query(query, bind_params=bind_params)
        points = result.get_points()

        bar = None
        for d in points:
            dt = datetime.strptime(d["time"], "%Y-%m-%dT%H:%M:%SZ")

            bar = BarData(
                symbol=symbol,
                exchange=exchange,
                interval=interval,
                datetime=dt.replace(tzinfo=DB_TZ),
                open_price=d["open_price"],
                high_price=d["high_price"],
                low_price=d["low_price"],
                close_price=d["close_price"],
                volume=d["volume"],
                open_interest=d["open_interest"],
                gateway_name="DB"
            )

        return bar

    def get_newest_tick_data(
        self, symbol: str, exchange: "Exchange"
    ) -> Optional["TickData"]:
        pass

    def get_bar_data_statistics(self) -> List:
        query = "select count(close_price) from bar_data group by *"
        result = influx_client.query(query)

        r = []
        for k, v in result.items():
            tags = k[1]
            statistics = list(v)[0]

            symbol, exchange = tags["vt_symbol"].split(".")

            r.append({
                "symbol": symbol,
                "exchange": exchange,
                "interval": tags["interval"],
                "count": statistics["count"]
            })

        return r

    def delete_bar_data(
        self,
        symbol: str,
        exchange: "Exchange",
        interval: "Interval"
    ) -> int:
        """
        Delete all bar data with given symbol + exchange + interval.
        """
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
        result = influx_client.query(query1, bind_params=bind_params)
        points = result.get_points()

        for d in points:
            count = d["count"]

        # Delete data
        query2 = (
            "drop series from bar_data"
            " where vt_symbol=$vt_symbol"
            " and interval=$interval"
        )
        influx_client.query(query2, bind_params=bind_params)

        return count

    def clean(self, symbol: str):
        pass
