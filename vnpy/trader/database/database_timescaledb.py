from datetime import datetime
from typing import Optional, Sequence, List

import psycopg2

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import BarData, TickData
from .database import BaseDatabaseManager, Driver


def init(_: Driver, settings: dict):
    database = settings.get('database', 'vnpy')
    host = settings['host']
    port = settings.get('port', 5421)
    username = settings.get("user", 'postgres')
    password = settings.get("password", 'postgres')

    conn = psycopg2.connect(f'postgres://{username}:{password}@{host}:{port}/{database}')

    # TODO: Create database and tables if needed

    return TimescaleDBManager(conn)


class TimescaleDBManager(BaseDatabaseManager):
    def __init__(self, conn):
        self.__conn = conn

    def load_bar_data(self,
                      symbol: str, exchange: Exchange, interval: Interval,
                      start: datetime, end: datetime
                      ) -> Sequence[BarData]:
        columns = ('datetime', 'open', 'high', 'low', 'close', 'volume', 'open_interest')

        query = f"SELECT {','.join(columns)} " \
                f"FROM bardata " \
                f"WHERE symbol = %s " \
                f"    AND exchange = %s" \
                f"    AND interval = %s " \
                f"    AND datetime >= %s " \
                f"    AND datetime <= %s;"

        params = (symbol, exchange, interval.value, start, end)

        with self.__conn.cursor() as cur:
            cur.execute(query, params)
            result = cur.fetchall()

        bars = [BarData(symbol=symbol, exchange=exchange, interval=interval,
                        **{col: val for col, val in zip(columns, values) if val is not None})
                for values in result]

        return bars

    def load_tick_data(self, symbol: str, exchange: Exchange, start: datetime, end: datetime) -> Sequence[TickData]:
        columns = (
            'name', 'volume', 'open_interest', 'last_price', 'last_volume',
            'limit_up', 'limit_down', 'open_price', 'high_price', 'low_price', 'pre_close',
            'bid_price_1', 'bid_price_2', 'bid_price_3', 'bid_price_4', 'bid_price_5',
            'ask_price_1', 'ask_price_2', 'ask_price_3', 'ask_price_4', 'ask_price_5',
            'bid_volume_1', 'bid_volume_2', 'bid_volume_3', 'bid_volume_4', 'bid_volume_5',
            'ask_volume_1', 'ask_volume_2', 'ask_volume_3', 'ask_volume_4', 'ask_volume_5')

        query = f"SELECT {','.join(columns)}" \
                f"FROM tickdata " \
                f"WHERE symbol = %s " \
                f"    AND exchange = %s" \
                f"    AND datetime >= %s " \
                f"    AND datetime <= %s;"

        params = (symbol, exchange, start, end)

        with self.__conn.cursor() as cur:
            cur.execute(query, params)
            result = cur.fetchall()

        ticks = [TickData(symbol=symbol, exchange=exchange,
                          **{col: val for col, val in zip(columns, values) if val is not None})
                 for values in result]

        return ticks

    def save_bar_data(self, data: Sequence[BarData]):
        pass

    def save_tick_data(self, data: Sequence[TickData]):
        pass

    def get_newest_bar_data(self, symbol: str, exchange: Exchange, interval: Interval) -> Optional[BarData]:
        pass

    def get_oldest_bar_data(self, symbol: str, exchange: Exchange, interval: Interval) -> Optional[BarData]:
        pass

    def get_newest_tick_data(self, symbol: str, exchange: Exchange) -> Optional[TickData]:
        pass

    def get_bar_data_statistics(self, symbol: str, exchange: Exchange) -> List:
        pass

    def delete_bar_data(self, symbol: str, exchange: Exchange, interval: Interval) -> int:
        pass

    def clean(self, symbol: str):
        pass
