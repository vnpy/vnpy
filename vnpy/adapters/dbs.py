# -*- coding=utf-8 -*-
# @Project  : crypto_backtrader
# @FilePath : adapters
# @File     : dbs.py
# @Time     : 2024/3/13 13:42
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description: 用于定义功能性的函数，即实现原子化的操作，比如创建db、读取db文件，写入db文件等。

import datetime
import os
import sqlite3
from abc import ABC, abstractmethod
from datetime import datetime
from typing import *
import pandas as pd
import polars as pl

from vnpy.utils.datetimes import TimeFreq
from .base import BaseDataAdapter, DataSource


#
# class DbOverview(object):
#     """
#     Overview of bar data stored in database.
#     """
#
#     symbol: str = ""
#     exchange: Exchange = None
#     interval: Interval = None
#     count: int = 0
#     start: float = None
#     end: float = None
#
#     def __init__(self, symbol: str,
#                  exchange: Exchange,
#                  interval: Interval,
#                  start: float,
#                  end: float,
#                  count: int = 0, **kwargs):
#         self.symbol = symbol
#         if isinstance(exchange, Exchange):
#             self.exchange = exchange
#         elif isinstance(exchange, str):
#             self.exchange = Exchange(exchange)
#         else:
#             raise NotImplementedError()
#         if isinstance(interval, Interval):
#             self.interval = interval
#         elif isinstance(interval, str):
#             self.interval = Interval(interval)
#         else:
#             raise NotImplementedError()
#         self.start = start
#         self.end = end
#         self.count = count
#         for k, v in kwargs.items():
#             setattr(self, k, v)
#
#     @abstractmethod
#     def to_vnpy_overview(self):
#         pass
#
#
# class DbBarOverview(DbOverview):
#     """
#     BarOverview of bar data stored in database.
#     """
#
#     symbol: str = ""
#     exchange: Exchange = None
#     interval: Interval = None
#     count: int = 0
#     start: float = None
#     end: float = None
#
#     def __init__(self, symbol: str,
#                  exchange: Exchange,
#                  interval: Interval,
#                  start: float,
#                  end: float,
#                  count: int = 0):
#         super().__init__(symbol=symbol, exchange=exchange, interval=interval, start=start, end=end, count=count)
#
#     def to_vnpy_overview(self):
#         return BarOverview(
#             symbol=self.symbol,
#             exchange=self.exchange,
#             interval=self.interval,
#             start=unix2datetime(self.start),
#             end=unix2datetime(self.end),
#             count=self.count,
#         )
#
#
# class DbFactorOverview(DbOverview):
#     """
#     BarOverview of bar data stored in database.
#     """
#
#     symbol: str = ""
#     name: str = ""
#     exchange: Exchange = None
#     interval: Interval = None
#     count: int = 0
#     start: float = None
#     end: float = None
#
#     def __init__(self, symbol: str,
#                  name: str,
#                  exchange: Exchange,
#                  interval: Interval,
#                  start: float,
#                  end: float,
#                  count: int = 0):
#         super().__init__(symbol=symbol, name=name, exchange=exchange, interval=interval, start=start, end=end,
#                          count=count)
#
#     def to_vnpy_overview(self):
#         return FactorOverview(
#             symbol=self.symbol,
#             name=self.name,
#             exchange=self.exchange,
#             interval=self.interval,
#             start=unix2datetime(self.start),
#             end=unix2datetime(self.end),
#             count=self.count,
#         )
#
#

class DBController(ABC):
    """
    用于数据库的初始化、创建、删除、alter table等具体的原子操作
    """
    database = None
    __conn__ = None  # 需要通过connect函数去初始化

    def __init__(self, *args, **kwargs):
        pass

    @abstractmethod
    def connect(self, database='', *args, **kwargs):
        pass

    @abstractmethod
    def commit(self, *args, **kwargs):
        pass

    @abstractmethod
    def close(self, *args, **kwargs):
        """close connection"""
        pass

    @abstractmethod
    def execute(self, *args, **kwargs):
        pass

    def create_table(self, *args, **kwargs):
        raise NotImplementedError("未来该函数将作为完全参数化的api")

    # @abstractmethod
    # def create_table_symbol(self, table_name='symbols', db_path=None):
    #     pass
    #
    # @abstractmethod
    # def create_table_kline(self, freq: Union[str, TimeFreq] = TimeFreq.unknown, db_path=None):
    #     pass
    #
    # @abstractmethod
    # def create_table_factor(self, factor_name: str, freq: Union[str, TimeFreq], db_path=None):
    #     pass
    #
    # @abstractmethod
    # def insert_or_get_symbol(self, symbol_name, db_path=None) -> int:
    #     pass
    #
    # @abstractmethod
    # def insert_kline(self, candle, freq: str, db_path=None):
    #     pass


class KlineDBAdapter(BaseDataAdapter):
    __col_mapper__ = {'open': 'open_', 'close': 'close_'}  # 主要为了解决sqlite中的关键字问题
    __col_mapper_reversed__ = {v: k for k, v in __col_mapper__.items()}
    __kline_cols__ = ['symbol_id',
                      'open_time',
                      'open_',  # 主要为了解决sqlite中的关键字问题
                      'high',
                      'low',
                      'close_',  # 主要为了解决sqlite中的关键字问题
                      'volume',
                      'quote_asset_volume',
                      'number_of_trades',
                      'taker_buy_base_asset_volume',
                      'taker_buy_quote_asset_volume',
                      'ignore', ]
    __kline_cols_origin__ = ['symbol_id',
                             'open_time',
                             'open',  # 如果不是sqlite，这里的open_和close_可以不用
                             'high',
                             'low',
                             'close',  # 如果不是sqlite，这里的open_和close_可以不用
                             'volume',
                             'quote_asset_volume',
                             'number_of_trades',
                             'taker_buy_base_asset_volume',
                             'taker_buy_quote_asset_volume',
                             'ignore', ]
    __exclude__ = ['close_time']
    dtypes = {'symbol_id': int,
              'open_time': int,
              'open_': float,
              'high': float,
              'low': float,
              'close_': float,
              'volume': float,
              'quote_asset_volume': float,
              'number_of_trades': int,
              'taker_buy_base_asset_volume': float,
              'taker_buy_quote_asset_volume': float,
              'ignore': int, }

    def __init__(self, from_: Optional[DataSource] = None, to_: Optional[DataSource] = None,
                 *args, **kwargs):
        super().__init__(from_=from_, to_=to_)
        self.set_tz('UTC')

    def set_tz(self, tz='UTC'):
        os.environ['TZ'] = tz

    @abstractmethod
    def create_table(self, table_name, *args, **kwargs):
        pass

    @abstractmethod
    def alter_table(self, table_name, column_name, column_type, comment='', *args, **kwargs):
        pass

    @abstractmethod
    def drop_table(self, table_name, *args, **kwargs):
        pass

    @abstractmethod
    def select(self, *args, **kwargs):
        pass

    @abstractmethod
    def insert(self, data, freq, *args, **kwargs):
        pass


class FactorDBAdapter(BaseDataAdapter):
    __primary_cols__ = None
    dtypes = float

    def __init__(self, from_: Optional[DataSource] = None, to_: Optional[DataSource] = None,
                 *args, **kwargs):
        super().__init__(from_=from_, to_=to_)
        self.set_tz('UTC')

    def set_tz(self, tz='UTC'):
        os.environ['TZ'] = tz

    @abstractmethod
    def create_table(self, table_name, *args, **kwargs):
        pass

    @abstractmethod
    def alter_table(self, table_name, column_name, column_type, comment='', *args, **kwargs):
        pass

    @abstractmethod
    def drop_table(self, table_name, *args, **kwargs):
        pass

    @abstractmethod
    def select(self, *args, **kwargs):
        pass

    @abstractmethod
    def insert(self, *args, **kwargs):
        pass

#
# # ====================================================
# # sqlite _todo_: move it to vnpy_sqlite
# # ====================================================
# class SqliteDBController(DBController):
#     """
#     用于数据库的初始化等 与数据无关的操作
#     """
#
#     def execute(self, *args, **kwargs):
#         pass
#
#     def __init__(self, db_path: str = None, db_dir: str = None, db_name: str = None):
#         super().__init__(db_path, db_dir, db_name)
#
#     def connect(self, db_path=None):
#         if db_path is None:
#             db_path = self.db_path
#         self.conn = sqlite3.connect(db_path)
#         return self.conn
#
#     def commit(self, conn=None):
#         if conn is None:
#             conn = self.conn
#         conn.commit()
#
#     def close(self, conn=None):
#         if conn is None:
#             conn = self.conn
#         conn.close()
#
#     def create_table_symbol(self, table_name='symbols', db_path=None):
#         conn = self.connect(db_path=db_path)
#
#         cursor = conn.cursor()
#         status = cursor.execute(f'''
#             CREATE TABLE IF NOT EXISTS {table_name}(
#                 symbol_id INTEGER PRIMARY KEY AUTOINCREMENT,
#                 symbol_name TEXT UNIQUE NOT NULL
#             )
#         ''')
#         self.commit(conn)
#         self.close(conn)
#         return status  # todo: 返回状态码需要完善，可以直接对接sqlite
#
#     def create_table_kline(self, freq: Union[str, TimeFreq] = TimeFreq.unknown, db_path=None):
#         """
#         # todo: 将open_和close_的转换集成到controller，这样不同的数据库都能方便的调用这个转换。read时从close_转为close，write时从close转为close_
#
#         Parameters
#         ----------
#         freq :
#         db_path :
#
#         Returns
#         -------
#
#         """
#         conn = self.connect(db_path=db_path)
#         cursor = conn.cursor()
#
#         status = cursor.execute(f'''
#             CREATE TABLE IF NOT EXISTS klines_{freq}(
#                 kline_id INTEGER PRIMARY KEY AUTOINCREMENT,
#                 symbol_id INTEGER not null,
#                 open_time INTEGER not null,
#                 open_ REAL,
#                 high REAL,
#                 low REAL,
#                 close_ REAL,
#                 volume REAL,
#                 quote_asset_volume REAL,
#                 number_of_trades INTEGER,
#                 taker_buy_base_asset_volume REAL,
#                 taker_buy_quote_asset_volume REAL,
#                 ignore INTEGER,
#                 UNIQUE(symbol_id, open_time),
#                 FOREIGN KEY(symbol_id) REFERENCES symbols(symbol_id)
#             );
#         ''')
#
#         self.commit(conn)
#         self.close(conn)
#         return status
#
#     def create_table_factor(self, factor_name: str, freq: Union[str, TimeFreq], db_path=None):
#         conn = self.connect(db_path=db_path)
#
#         cursor = conn.cursor()
#
#         cursor.execute(f'''
#             CREATE TABLE IF NOT EXISTS factor_{factor_name}_{freq}(
#                 kline_id
#                 UNIQUE(symbol_id, open_time),
#                 FOREIGN KEY(symbol_id) REFERENCES symbols(symbol_id)
#             );
#         ''')
#
#         self.commit(conn)
#         self.close(conn)
#         return db_path
#
#     def insert_or_get_symbol(self, symbol_name, db_path=None) -> int:
#         """
#
#         Parameters
#         ----------
#         symbol_name :
#         db_path :
#
#         Returns
#         -------
#         int, symbol_id
#
#         """
#         conn = self.connect(db_path=db_path)
#         cursor = conn.cursor()
#
#         cursor.execute('SELECT symbol_id FROM symbols WHERE symbol_name = ?', (symbol_name,))
#         result = cursor.fetchone()
#         if result:
#             return result[0]
#
#         cursor.execute('INSERT INTO symbols (symbol_name) VALUES (?)', (symbol_name,))
#         self.commit(conn)
#         self.close(conn)
#         return cursor.lastrowid
#
#     def insert_kline(self, candle, freq: str, db_path=None):
#         """
#         live stream websocket中获取的kline数据插入到数据库中
#
#         Parameters
#         ----------
#         candle :
#         db_path :
#
#         Returns
#         -------
#
#         """
#         print(FutureWarning('This method is not tested yet.'))
#         conn = self.connect(db_path=db_path)
#         cursor = conn.cursor()
#
#         symbol_id = SqliteDBController.insert_or_get_symbol(candle['s'], db_path)
#
#         try:
#             cursor.execute(f'''
#                 INSERT OR REPLACE INTO klines_{freq} (symbol_id,
#                                                 open_time,
#                                                 open_,
#                                                 high,
#                                                 low,
#                                                 close_,
#                                                 volume,
#                                                 quote_asset_volume,
#                                                 number_of_trades,
#                                                 taker_buy_base_asset_volume,
#                                                 taker_buy_quote_asset_volume,
#                                                 ignore)
#                 VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?,?,?,?,?)
#             ''', (
#                 symbol_id, candle['t'], candle['o'], candle['h'], candle['l'], candle['c'],
#                 candle['v'], candle['q'], candle['n'], candle['V'], candle['Q'], candle['B']
#             ))
#         except sqlite3.Error as e:
#             print(f"SQLite error: {e}")
#
#         self.commit(conn)
#         self.close(conn)
#
#     def delete_old_klines(self, days_to_keep: int, db_path=None):
#         # Calculate the date threshold
#         threshold_date = (datetime.datetime.utcnow().date() - datetime.timedelta(days=days_to_keep)).strftime(
#             '%Y-%m-%d %H:%M:%S')
#
#         conn = self.connect(db_path=db_path)
#         cursor = conn.cursor()
#
#         cursor.execute('DELETE FROM klines WHERE open_time < ?', (threshold_date,))
#
#         self.commit(conn)
#         self.close(conn)
#
#     def create_column(self, table_name: str, column_name: Union[str, List[str]],
#                       column_type: Union[str, List[str]], db_path: str = None):
#         conn = self.connect(db_path=db_path)
#         cursor = conn.cursor()
#         if isinstance(column_name, list):
#             for col, col_type in zip(column_name, column_type):
#                 cursor.execute(f'ALTER TABLE {table_name} ADD COLUMN {col} {col_type}')
#         elif isinstance(column_name, str):
#             cursor.execute(f'ALTER TABLE {table_name} ADD COLUMN {column_name} {column_type}')
#         self.commit(conn)
#         self.close(conn)
#
#
# class SqliteKlineDBAdapter(KlineDBAdapter):
#     """
#     主要用于存储回测使用的kline数据
#     """
#
#     def create_table(self, table_name, *args, **kwargs):
#         pass
#
#     def alter_table(self, table_name, column_name, column_type, comment='', *args, **kwargs):
#         pass
#
#     def drop_table(self, table_name, *args, **kwargs):
#         pass
#
#     def select(self, *args, **kwargs):
#         pass
#
#     def insert(self, *args, **kwargs):
#         pass
#
#     def __init__(self,
#                  from_: Optional[DataSource] = DataSource.sqlite,
#                  to_: Optional[DataSource] = DataSource.sqlite,
#                  *args, **kwargs):
#         super().__init__(from_=from_, to_=to_)
#         self.__controller__ = SqliteDBController()
#
#     def read(self, db_path: str, table_name: str, columns=None, exclude=None, *args,
#              **kwargs) -> pl.DataFrame:
#         """todo: 读取一个时间段的数据
#
#         Parameters
#         ----------
#         columns :
#         data :
#         db_path :
#         table_name :
#         exclude : List[str], default ['close_time'],
#             columns to exclude
#
#         Returns
#         -------
#
#         """
#         if columns is None:
#             columns = []
#         if exclude is None:
#             exclude = ['close_time']
#         conn = sqlite3.connect(db_path)
#
#         # (symbol_id, open_time, open_, high, low, close_, volume, quote_asset_volume, number_of_trades, taker_buy_base_asset_volume, taker_buy_quote_asset_volume, ignore)
#         # todo: 将open_和close_的转换集成到controller，这样不同的数据库都能方便的调用这个转换。read时从close_转为close，write时从close转为close_
#         if columns:
#             sql = f"""SELECT {','.join(columns)} FROM {table_name}"""
#         else:
#             sql = f"""SELECT * FROM {table_name}"""
#
#         df = pl.read_database(query=sql, connection=conn, *args, **kwargs)
#         df = df.drop(exclude)  # sqlite doesn't support exclude columns in sql, so we drop it here
#         conn.commit()
#         conn.close()
#         return df
#
#     def write(self, data: Union[pl.DataFrame], db_path: str, table_name: str, exclude: List[str] = None,
#               if_exists="fail",
#               *args, **kwargs) -> int:
#         if exclude is None:
#             exclude = ['close_time']
#         else:
#             if 'close_time' not in exclude:
#                 exclude.append('close_time')
#         data = data.drop(exclude)
#         if not db_path.startswith('sqlite'):
#             db_path = f'sqlite:///{db_path}'
#         rows_affected = data.write_database(table_name=table_name, connection=db_path, if_table_exists=if_exists,
#                                             engine='sqlalchemy', *args, **kwargs)
#         return rows_affected
#
#     def append(self, data: Union[pl.DataFrame], db_path: str, table_name: str, exclude: List[str] = None,
#                if_exists="append",
#                *args, **kwargs) -> int:
#         if exclude is None:
#             exclude = ['close_time']
#         else:
#             if 'close_time' not in exclude:
#                 exclude.append('close_time')
#         data = data.drop(exclude)
#         if not db_path.startswith('sqlite'):
#             db_path = f'sqlite:///{db_path}'
#         rows_affected = data.write_database(table_name=table_name, connection=db_path, if_table_exists=if_exists,
#                                             engine='sqlalchemy', *args, **kwargs)
#         return rows_affected
#
#     def insert_single_symbol(self, data: pl.DataFrame, symbol_id: int, db_path: str, table_name: str,
#                              exclude=None):
#         """插入单个资产的数据
#
#         Parameters
#         ----------
#         data :
#         db_path :
#         table_name :
#         exclude : List[str], default ['close_time'],
#             columns to exclude
#
#         Returns
#         -------
#
#         """
#         if exclude is None:
#             exclude = ['close_time']
#         conn = sqlite3.connect(db_path)
#         cursor = conn.cursor()
#         temp_data = data.drop(exclude)
#         cols = temp_data.columns
#         cols = [self.__col_mapper__[col] if col in self.__col_mapper__ else col for col in cols]
#         temp_data = temp_data.to_numpy().tolist()
#         # (symbol_id, open_time, open_, high, low, close_, volume, quote_asset_volume, number_of_trades, taker_buy_base_asset_volume, taker_buy_quote_asset_volume, ignore)
#
#         sql = f"""INSERT INTO {table_name}
#         {tuple(['symbol_id'] + cols)}
#         VALUES {','.join([str(tuple([symbol_id] + row)) for row in temp_data])}"""
#         cursor.execute(sql)
#
#         conn.commit()
#         conn.close()
#
#     def update(self):
#         pass
#
#     def delete(self):
#         pass
#
#     def query(self):
#         pass
#
#     def create(self):
#         pass
#
#     def insert_kline_data_from_concated_csv(self, data: pl.DataFrame, symbol, kline_database_path, freq: str):
#         """
#
#         Parameters
#         ----------
#         data :
#         kline_database_path :
#
#         Returns
#         -------
#
#         """
#
#         symbol_id = SqliteDBController.insert_or_get_symbol(symbol, kline_database_path)
#
#         conn = sqlite3.connect(kline_database_path)
#         cursor = conn.cursor()
#
#         # with open(csv_filepath, 'r') as csvfile:
#         #     csvreader = csv.reader(csvfile)
#         #     next(csvreader)  # Skip the header row
#         raw = data.to_numpy()
#
#         for row in raw:
#             open_time, open_price, high_price, low_price, close_price, volume, quote_asset_volume, num_trades, taker_buy_base_asset_volume, taker_buy_quote_asset_volume, ignore = [
#                 dtype(x) for dtype, x in zip(self.dtypes.values(), row)]
#
#             try:
#                 cursor.execute(f'''
#                                         INSERT OR REPLACE INTO klines_{freq} (symbol_id,
#                                                                         open_time
#                                                                         open_,
#                                                                         high,
#                                                                         low,
#                                                                         close_,
#                                                                         volume,
#                                                                         quote_asset_volume,
#                                                                         number_of_trades,
#                                                                         taker_buy_base_asset_volume,
#                                                                         taker_buy_quote_asset_volume,
#                                                                         ignore)
#                                         VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?,?,?,?)
#                                     ''', (
#                     symbol_id, open_time, open_price, high_price, low_price, close_price, volume,
#                     quote_asset_volume,
#                     num_trades, taker_buy_base_asset_volume, taker_buy_quote_asset_volume, ignore
#                 ))
#             except sqlite3.Error as e:
#                 print(f"SQLite error: {e}")
#
#         conn.commit()
#         conn.close()
#
#     def fetch_kline_data(self, symbol: str, interval: str, end_time: datetime, historical_data_window: int or None,
#                          kline_database_path: str):
#         """generated by copilot
#
#         Parameters
#         ----------
#         symbol :
#         interval :
#         end_time :
#         historical_data_window :
#         kline_database_path :
#
#         Returns
#         -------
#
#         """
#         conn = sqlite3.connect(kline_database_path)
#         cursor = conn.cursor()
#
#         # Fetch symbol_id for the given symbol_name
#         cursor.execute('SELECT symbol_id FROM symbols WHERE symbol_name = ?', (symbol.lower(),))
#         symbol_id = cursor.fetchone()
#         if not symbol_id:
#             print(f"No data found for symbol {symbol}.")
#             return None
#         symbol_id = symbol_id[0]
#
#         # Fetch interval_id for the given interval_name
#         cursor.execute('SELECT interval_id FROM intervals WHERE interval_name = ?', (interval,))
#         interval_id = cursor.fetchone()
#         if not interval_id:
#             print(f"No data found for interval {interval}.")
#             return None
#         interval_id = interval_id[0]
#
#         # If historical_data_window is specified, then calculate the start time for the data
#         if historical_data_window:
#             start_time_window = end_time - datetime.timedelta(minutes=historical_data_window)
#             cursor.execute('''
#                 SELECT start_time, open_price, low_price, high_price, close_price, num_trades, base_asset_volume
#                 FROM klines
#                 WHERE symbol_id = ? AND interval_id = ? AND start_time >= ? AND start_time < ?
#                 ORDER BY start_time
#             ''', (symbol_id, interval_id, start_time_window.strftime('%Y-%m-%d %H:%M:%S'),
#                   end_time.strftime('%Y-%m-%d %H:%M:%S')))
#         else:
#             # If historical_data_window is None, fetch all data
#             cursor.execute('''
#                 SELECT start_time, open_price, low_price, high_price, close_price, num_trades, base_asset_volume
#                 FROM klines
#                 WHERE symbol_id = ? AND interval_id = ? AND start_time < ?
#                 ORDER BY start_time
#             ''', (symbol_id, interval_id, end_time.strftime('%Y-%m-%d %H:%M:%S')))
#
#         rows = cursor.fetchall()
#         conn.close()
#
#         if not rows:
#             if historical_data_window:
#                 print(
#                     f"No Kline data found for {symbol} with interval {interval} in the last {historical_data_window} minutes.")
#             else:
#                 print(f"No Kline data found for {symbol} with interval {interval}.")
#             return None
#
#         # Convert the rows to a Pandas DataFrame for better manipulation and visualization
#         df = pd.DataFrame(rows, columns=['start_time', 'open', 'low', 'high', 'close', 'num_trades', 'volume'])
#         df.set_index('start_time', inplace=True)
#         return df
#
#
# class SqliteFactorDBAdapter(FactorDBAdapter):
#     """
#     主要用于存储因子数据，应该设计为较为好的通用性、低耦合性
#     """
#
#     def create_table(self, table_name, *args, **kwargs):
#         pass
#
#     def alter_table(self, table_name, column_name, column_type, comment='', *args, **kwargs):
#         pass
#
#     def drop_table(self, table_name, *args, **kwargs):
#         pass
#
#     def select(self, *args, **kwargs):
#         pass
#
#     def insert(self, *args, **kwargs):
#         pass
#
#     def __init__(self,
#                  from_: Optional[DataSource] = DataSource.sqlite,
#                  to_: Optional[DataSource] = DataSource.sqlite,
#                  *args, **kwargs):
#         super().__init__(from_=from_, to_=to_)
#         self.__controller__ = SqliteDBController()
#
#     def read(self, db_path: str, table_name: str, columns=None, exclude=None, *args,
#              **kwargs) -> pl.DataFrame:
#         """
#
#         Parameters
#         ----------
#         db_path :
#         table_name :
#         exclude : List[str], default None,
#             columns to exclude
#
#         Returns
#         -------
#
#         """
#         if columns is None:
#             columns = []
#         conn = sqlite3.connect(db_path)
#
#         # (symbol_id, open_time, open_, high, low, close_, volume, quote_asset_volume, number_of_trades, taker_buy_base_asset_volume, taker_buy_quote_asset_volume, ignore)
#         if columns:
#             sql = f"""SELECT {','.join(columns)} FROM {table_name}"""
#         else:
#             sql = f"""SELECT * FROM {table_name}"""
#
#         df = pl.read_database(query=sql, connection=conn, *args, **kwargs)
#         df = df.drop(exclude)  # sqlite doesn't support exclude columns in sql, so we drop it here
#         conn.commit()
#         conn.close()
#         return df
#
#     def write(self, data: Union[pl.DataFrame], db_path: str, table_name: str, exclude: Optional[list] = None,
#               if_exists="fail",
#               *args, **kwargs) -> int:
#         if exclude is not None and len(exclude) > 0:
#             data = data.drop(exclude)
#         if not db_path.startswith('sqlite'):
#             db_path = f'sqlite:///{db_path}'
#         rows_affected = data.write_database(table_name=table_name, connection=db_path, if_table_exists=if_exists,
#                                             engine='sqlalchemy', *args, **kwargs)
#         return rows_affected
#
#     def insert_single_symbol(self, data: pl.DataFrame, symbol_id: int, db_path: str, table_name: str,
#                              exclude=None):
#         """插入单个资产的数据
#
#         Parameters
#         ----------
#         data :
#         db_path :
#         table_name :
#         exclude : List[str], default none,
#             columns to exclude
#
#         Returns
#         -------
#
#         """
#         if exclude is None:
#             exclude = ['close_time']
#         conn = sqlite3.connect(db_path)
#         cursor = conn.cursor()
#         temp_data = data.drop(exclude)
#         cols = temp_data.columns
#         cols = [self.__col_mapper__[col] if col in self.__col_mapper__ else col for col in cols]
#         temp_data = temp_data.to_numpy().tolist()
#         # (symbol_id, open_time, open_, high, low, close_, volume, quote_asset_volume, number_of_trades, taker_buy_base_asset_volume, taker_buy_quote_asset_volume, ignore)
#
#         sql = f"""INSERT INTO {table_name}
#         {tuple(['symbol_id'] + cols)}
#         VALUES {','.join([str(tuple([symbol_id] + row)) for row in temp_data])}"""
#         cursor.execute(sql)
#
#         conn.commit()
#         conn.close()
#
#     def update(self):
#         pass
#
#     def delete(self):
#         pass
#
#     def query(self):
#         pass
#
#     def create(self):
#         pass
#
#     def insert_kline_data_from_concated_csv(self, data: pl.DataFrame, symbol, kline_database_path, freq: str):
#         """
#
#         Parameters
#         ----------
#         data :
#         kline_database_path :
#
#         Returns
#         -------
#
#         """
#
#         symbol_id = SqliteDBController.insert_or_get_symbol(symbol, kline_database_path)
#
#         conn = sqlite3.connect(kline_database_path)
#         cursor = conn.cursor()
#
#         # with open(csv_filepath, 'r') as csvfile:
#         #     csvreader = csv.reader(csvfile)
#         #     next(csvreader)  # Skip the header row
#         raw = data.to_numpy()
#
#         for row in raw:
#             open_time, open_price, high_price, low_price, close_price, volume, quote_asset_volume, num_trades, taker_buy_base_asset_volume, taker_buy_quote_asset_volume, ignore = [
#                 dtype(x) for dtype, x in zip(self.dtypes.values(), row)]
#
#             try:
#                 cursor.execute(f'''
#                                         INSERT OR REPLACE INTO klines_{freq} (symbol_id,
#                                                                         open_time
#                                                                         open_,
#                                                                         high,
#                                                                         low,
#                                                                         close_,
#                                                                         volume,
#                                                                         quote_asset_volume,
#                                                                         number_of_trades,
#                                                                         taker_buy_base_asset_volume,
#                                                                         taker_buy_quote_asset_volume,
#                                                                         ignore)
#                                         VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?,?,?,?)
#                                     ''', (
#                     symbol_id, open_time, open_price, high_price, low_price, close_price, volume,
#                     quote_asset_volume,
#                     num_trades, taker_buy_base_asset_volume, taker_buy_quote_asset_volume, ignore
#                 ))
#             except sqlite3.Error as e:
#                 print(f"SQLite error: {e}")
#
#         conn.commit()
#         conn.close()


# ====================================================
# see details about clickhouse in package vnpy_clickhouse
# ====================================================

