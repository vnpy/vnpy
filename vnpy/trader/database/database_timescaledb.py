from datetime import datetime
from typing import Optional, Sequence, List

import psycopg2
import psycopg2.extras

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

    query = ("create schema if not exists hist_md;\n"
             "\n"
             "create table if not exists hist_md.tickdata\n"
             "(\n"
             "    symbol        varchar(255)             not null,\n"
             "    exchange      varchar(255)             not null,\n"
             "    datetime      timestamp with time zone not null,\n"
             "    name          varchar(255)             not null,\n"
             "    volume        real                     not null,\n"
             "    open_interest real                     not null,\n"
             "    last_price    real                     not null,\n"
             "    last_volume   real                     not null,\n"
             "    limit_up      real                     not null,\n"
             "    limit_down    real                     not null,\n"
             "    open_price    real                     not null,\n"
             "    high_price    real                     not null,\n"
             "    low_price     real                     not null,\n"
             "    pre_close     real                     not null,\n"
             "    bid_price_1   real                     not null,\n"
             "    bid_price_2   real,\n"
             "    bid_price_3   real,\n"
             "    bid_price_4   real,\n"
             "    bid_price_5   real,\n"
             "    ask_price_1   real                     not null,\n"
             "    ask_price_2   real,\n"
             "    ask_price_3   real,\n"
             "    ask_price_4   real,\n"
             "    ask_price_5   real,\n"
             "    bid_volume_1  real                     not null,\n"
             "    bid_volume_2  real,\n"
             "    bid_volume_3  real,\n"
             "    bid_volume_4  real,\n"
             "    bid_volume_5  real,\n"
             "    ask_volume_1  real                     not null,\n"
             "    ask_volume_2  real,\n"
             "    ask_volume_3  real,\n"
             "    ask_volume_4  real,\n"
             "    ask_volume_5  real,\n"
             "    constraint tickdata_pk\n"
             "        primary key (symbol, exchange, datetime)\n"
             ");\n"
             "\n"
             "create table if not exists hist_md.bardata\n"
             "(\n"
             "    symbol        varchar(200)             not null,\n"
             "    exchange      varchar(50)              not null,\n"
             "    datetime      timestamp with time zone not null,\n"
             "    interval      varchar(50)              not null,\n"
             "    open          real,\n"
             "    high          real,\n"
             "    low           real,\n"
             "    close         real,\n"
             "    volume        real,\n"
             "    open_interest integer,\n"
             "    constraint bardata_pk\n"
             "        primary key (symbol, exchange, datetime, interval)\n"
             ");\n"
             "\n"
             "select create_hypertable('hist_md.tickdata', 'datetime', if_not_exists := true);\n"
             "select create_hypertable('hist_md.bardata', 'datetime', if_not_exists := true);\n")

    with conn.cursor() as cur:
        cur.execute(query)

    return TimescaleDBManager(conn)


class TimescaleDBManager(BaseDatabaseManager):
    def __init__(self, conn):
        self.__conn = conn

    def load_bar_data(self,
                      symbol: str, exchange: Exchange, interval: Interval,
                      start: datetime, end: datetime
                      ) -> Sequence[BarData]:
        columns = ('datetime', 'open', 'high', 'low', 'close', 'volume', 'open_interest')

        query = f"select {','.join(columns)} " \
                f"from hist_md.bardata " \
                f"where symbol = %s " \
                f"    and exchange = %s " \
                f"    and interval = %s " \
                f"    and datetime >= %s " \
                f"    and datetime <= %s;"

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

        query = f"select {','.join(columns)} " \
                f"from hist_md.tickdata " \
                f"where symbol = %s " \
                f"    and exchange = %s " \
                f"    and datetime >= %s " \
                f"    and datetime <= %s;"

        params = (symbol, exchange, start, end)

        with self.__conn.cursor() as cur:
            cur.execute(query, params)
            result = cur.fetchall()

        ticks = [TickData(symbol=symbol, exchange=exchange,
                          **{col: val for col, val in zip(columns, values) if val is not None})
                 for values in result]

        return ticks

    def save_bar_data(self, data: Sequence[BarData]):
        columns = ('symbol', 'exchange', 'interval', 'datetime',
                   'open', 'high', 'low', 'close', 'volume', 'open_interest')

        values = [{column: getattr(bar, column) for column in columns} for bar in data]
        query = f"insert into hist_md.bardata {','.join(columns)} values %s;"
        with self.__conn.cursor() as cur:
            psycopg2.extras.execute_values(cur, query, values)

    def save_tick_data(self, data: Sequence[TickData]):
        columns = ('symbol', 'exchange', 'datetime',
                   'name', 'volume', 'open_interest', 'last_price', 'last_volume',
                   'limit_up', 'limit_down', 'open_price', 'high_price', 'low_price', 'pre_close',
                   'bid_price_1', 'bid_price_2', 'bid_price_3', 'bid_price_4', 'bid_price_5',
                   'ask_price_1', 'ask_price_2', 'ask_price_3', 'ask_price_4', 'ask_price_5',
                   'bid_volume_1', 'bid_volume_2', 'bid_volume_3', 'bid_volume_4', 'bid_volume_5',
                   'ask_volume_1', 'ask_volume_2', 'ask_volume_3', 'ask_volume_4', 'ask_volume_5')

        values = [{column: getattr(bar, column) for column in columns} for bar in data]
        query = f"insert into hist_md.tickdata {','.join(columns)} values %s;"
        with self.__conn.cursor() as cur:
            psycopg2.extras.execute_values(cur, query, values)

    def get_newest_bar_data(self, symbol: str, exchange: Exchange, interval: Interval) -> Optional[BarData]:
        columns = ('datetime', 'open', 'high', 'low', 'close', 'volume', 'open_interest')

        query = f"select {','.join(columns)} " \
                f"from hist_md.tickdata " \
                f"where symbol = %s " \
                f"    and exchange = %s " \
                f"    and interval = %s " \
                f"order by datetime desc " \
                f"limit 1;"

        params = (symbol, exchange, interval.value)

        with self.__conn.cursor() as cur:
            cur.execute(query)
            result = cur.fetchall()

        bars = [BarData(symbol=symbol, exchange=exchange, interval=interval,
                        **{col: val for col, val in zip(columns, values) if val is not None})
                for values in result]

        if len(bars) == 0:
            return None
        else:
            return bars[0]

    def get_oldest_bar_data(self, symbol: str, exchange: Exchange, interval: Interval) -> Optional[BarData]:
        columns = ('datetime', 'open', 'high', 'low', 'close', 'volume', 'open_interest')

        query = f"select {','.join(columns)} " \
                f"from hist_md.tickdata " \
                f"where symbol = %s " \
                f"    and exchange = %s " \
                f"    and interval = %s " \
                f"order by datetime " \
                f"limit 1;"

        params = (symbol, exchange, interval.value)

        with self.__conn.cursor() as cur:
            cur.execute(query)
            result = cur.fetchall()

        bars = [BarData(symbol=symbol, exchange=exchange, interval=interval,
                        **{col: val for col, val in zip(columns, values) if val is not None})
                for values in result]

        if len(bars) == 0:
            return None
        else:
            return bars[0]

    def get_newest_tick_data(self, symbol: str, exchange: Exchange) -> Optional[TickData]:
        columns = (
            'name', 'volume', 'open_interest', 'last_price', 'last_volume',
            'limit_up', 'limit_down', 'open_price', 'high_price', 'low_price', 'pre_close',
            'bid_price_1', 'bid_price_2', 'bid_price_3', 'bid_price_4', 'bid_price_5',
            'ask_price_1', 'ask_price_2', 'ask_price_3', 'ask_price_4', 'ask_price_5',
            'bid_volume_1', 'bid_volume_2', 'bid_volume_3', 'bid_volume_4', 'bid_volume_5',
            'ask_volume_1', 'ask_volume_2', 'ask_volume_3', 'ask_volume_4', 'ask_volume_5')

        query = f"select {','.join(columns)} " \
                f"from hist_md.tickdata " \
                f"where symbol = %s " \
                f"    and exchange = %s " \
                f"order by datetime desc" \
                f"limit 1;"

        params = (symbol, exchange)

        with self.__conn.cursor() as cur:
            cur.execute(query, params)
            result = cur.fetchall()

        ticks = [TickData(symbol=symbol, exchange=exchange,
                          **{col: val for col, val in zip(columns, values) if val is not None})
                 for values in result]

        if len(ticks) == 0:
            return None
        else:
            return ticks[0]

    def get_bar_data_statistics(self, symbol: str, exchange: Exchange) -> List:
        columns = {'symbol', 'exchange', 'interval', }
        query = f"select symbol, exchange, interval, count(*) as count " \
                f"from hist_md.bardata " \
                f"group by symbol, exchange, interval; "

        with self.__conn.cursor() as cur:
            cur.execute(query)
            result = cur.fetchall()

        statistics = [{col: val for col, val in zip(columns, result)}
                      for values in result]

        return statistics

    def delete_bar_data(self, symbol: str, exchange: Exchange, interval: Interval) -> int:
        query = f"delete " \
                f"from hist_md.bardata " \
                f"where symbol = %s " \
                f"    and exchange = %s " \
                f"    and interval = %s;"

        params = (symbol, exchange, interval.value)

        with self.__conn.cursor() as cur:
            cur.execute(query, params)
            count = cur.rowcount

        return count

    def clean(self, symbol: str):
        query = f"delete " \
                f"from hist_md.bardata " \
                f"where symbol = %s; "

        params = (symbol,)

        with self.__conn.cursor() as cur:
            cur.execute(query, params)

        query = f"delete " \
                f"from hist_md.tickdata " \
                f"where symbol = %s; "

        params = (symbol,)

        with self.__conn.cursor() as cur:
            cur.execute(query, params)
