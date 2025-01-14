# -*- coding=utf-8 -*-
# @Project  : crypto_backtrader
# @FilePath : adapters
# @File     : files.py
# @Time     : 2024/3/13 13:42
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description: 用于定义功能性的函数，即实现原子化的操作，比如创建csv、读取csv文件，写入csv文件等。json/numpy/excel

import os
import datetime
import polars as pl
from typing import Optional, Union, Literal
from abc import abstractmethod
from .base import BaseDataAdapter, DataSource


class BaseConverter(object):
    pass




class KlineFileAdapter(BaseDataAdapter):
    __kline_cols__ = [
        'open_time',
        'open',
        'high',
        'low',
        'close',
        'volume',
        'quote_asset_volume',
        'number_of_trades',
        'taker_buy_base_asset_volume',
        'taker_buy_quote_asset_volume',
        'ignore', ]
    __exclude__ = ['close_time']
    dtypes = {
        'open_time': int,
        'open': float,
        'high': float,
        'low': float,
        'close': float,
        'volume': float,
        'quote_asset_volume': float,
        'number_of_trades': int,
        'taker_buy_base_asset_volume': float,
        'taker_buy_quote_asset_volume': float,
        'ignore': int, }

    def __init__(self,
                 from_: Optional[DataSource] = None,
                 to_: Optional[DataSource] = None,
                 *args, **kwargs):
        super().__init__(from_=from_, to_=to_)

    @abstractmethod
    def read(self, path: str, *args, **kwargs) -> pl.DataFrame:
        pass

    @abstractmethod
    def write(self, data: Union[pl.DataFrame], path: str, *args, **kwargs):
        pass


class FactorFileAdapter(BaseDataAdapter):
    __cols__ = None
    dtypes = float

    def __init__(self,
                 from_: Optional[DataSource] = None,
                 to_: Optional[DataSource] = None,
                 *args, **kwargs):
        super().__init__(from_=from_, to_=to_)

    @abstractmethod
    def read(self, path: str, *args, **kwargs) -> pl.DataFrame:
        pass

    @abstractmethod
    def write(self, data: Union[pl.DataFrame], path: str, *args, **kwargs):
        pass

    @abstractmethod
    def append(self, symbol, factor, orientation='columns'):
        """
        用于追加新的标的factor数据
        Parameters
        ----------
        symbol :
        factor :
        orientation :

        Returns
        -------

        """
        pass


# ====================================================
# csv
# ====================================================
class CSVKlineFileAdapter(KlineFileAdapter):
    def __init__(self,
                 from_: Optional[DataSource] = DataSource.csv,
                 to_: Optional[DataSource] = DataSource.csv,
                 *args, **kwargs):
        super().__init__(from_=from_, to_=to_)

    def read(self, path: str, sort=False, convert2datetime=True, *args, **kwargs) -> pl.DataFrame:
        self._pre_read_(path)
        df = pl.read_csv(path, *args, **kwargs)
        if sort:
            df = self._set_sorted_polars_(df, by='open_time')
        if convert2datetime:
            df = df.with_columns(
                pl.from_epoch('open_time', time_unit='ms'),
            )
        return df

    def write(self, data: Union[pl.DataFrame], path: str, not_exists: Literal['raise', 'create'] = 'create', *args,
              **kwargs):
        self._pre_write_(path, not_exists=not_exists)
        data.write_csv(path, *args, **kwargs)


class CSVFactorFileAdapter(FactorFileAdapter):
    def __init__(self,
                 from_: Optional[DataSource] = DataSource.csv,
                 to_: Optional[DataSource] = DataSource.csv,
                 *args, **kwargs):
        super().__init__(from_=from_, to_=to_)

    def read(self, path: str, *args, **kwargs) -> pl.DataFrame:
        self._pre_read_(path)
        df = pl.read_csv(path, *args, **kwargs)
        return df

    def write(self, data: Union[pl.DataFrame], path: str, not_exists: Literal['raise', 'create'] = 'create', *args,
              **kwargs):
        self._pre_write_(path, not_exists=not_exists)
        data.write_csv(path, *args, **kwargs)

    def append(self, symbol, factor, orientation='columns'):
        pass


# ============================================
# zc
# ============================================
class ConverterCSV2Clickhouse(BaseConverter):
    def __init__(self):
        super().__init__()

    def read_raw_kline_data(self, base_path: str, tickers: list, interval: str, start_date: str, end_date: str) -> dict:
        """
        Read raw Kline CSV files for multiple tickers within a specified date range and convert them into Polars DataFrames.

        Parameters:
            base_path (str): The base directory containing the Kline CSV files.
            tickers (list): List of tickers (e.g., ["BNB", "BTC", "ETH"]).
            interval (str): The interval folder (e.g., "1m").
            start_date (str): Start date in the format "YYYY-MM-DD".
            end_date (str): End date in the format "YYYY-MM-DD".

        Returns:
            dict: A dictionary where each key is a ticker symbol and the value is a Polars DataFrame
                  containing "open", "high", "low", "close", and "volume" data within the date range.
        """
        # Define the column names for the CSV files (based on the file structure)
        column_names = [
            "Open_time", "open", "high", "low", "close", "volume",
            "Close_time", "Quote_asset_volume", "Number_of_trades",
            "Taker_buy_base_asset_volume", "Taker_buy_quote_asset_volume", "Ignore"
        ]

        # Define the expected schema for the CSV files to ensure consistent data types
        schema = {
            "Open_time": pl.Int64,
            "open": pl.Float64,
            "high": pl.Float64,
            "low": pl.Float64,
            "close": pl.Float64,
            "volume": pl.Float64,
            "Close_time": pl.Int64,
            "Quote_asset_volume": pl.Float64,
            "Number_of_trades": pl.Int64,
            "Taker_buy_base_asset_volume": pl.Float64,
            "Taker_buy_quote_asset_volume": pl.Float64,
            "Ignore": pl.Utf8,
        }

        # Parse start and end dates
        start_date_obj = datetime.datetime.strptime(start_date, "%Y-%m-%d").date()
        end_date_obj = datetime.datetime.strptime(end_date, "%Y-%m-%d").date()

        # Dictionary to store the processed Polars DataFrame for each ticker
        tickers_data = {}

        for ticker in tickers:
            # Construct the full path to the directory containing the ticker's CSV files
            ticker_path = os.path.join(base_path, ticker, interval)

            # Check if the directory exists; if not, skip the ticker
            if not os.path.exists(ticker_path):
                print(f"Path not found: {ticker_path}")
                continue

            # Find all CSV files in the directory for the current ticker
            csv_files = [
                f for f in os.listdir(ticker_path) if f.endswith(".csv")
                                                      and start_date_obj <= datetime.datetime.strptime(
                    '-'.join(f.split("-")[2:]).replace(".csv", ""), "%Y-%m-%d").date() <= end_date_obj
            ]

            # Read and concatenate all filtered CSV files into a single Polars DataFrame for the ticker
            ticker_df = pl.concat(
                [
                    pl.read_csv(
                        os.path.join(ticker_path, file),
                        has_header=False,  # The CSV files don't have headers
                        new_columns=column_names,  # Assign the predefined column names
                        schema=schema,  # Use the predefined schema for consistency
                        low_memory=True  # Optimize memory usage during parsing
                    ).select(["Open_time", "open", "high", "low", "close", "volume"])
                    # Select only the necessary columns
                    for file in csv_files
                ],
                how="vertical",  # Concatenate vertically
            )

            # Parse the "Open_time" column to datetime and retain only relevant columns
            ticker_df = ticker_df.select([
                pl.from_epoch(pl.col("Open_time"), time_unit='ms').alias("datetime"),  # Convert epoch to datetime
                pl.col("open"), pl.col("high"), pl.col("low"), pl.col("close"), pl.col("volume")
            ])

            # Store the DataFrame in the dictionary using the ticker as the key
            tickers_data[ticker] = ticker_df

        return tickers_data

    def convert_tickers_to_ohlcv_format(self, tickers_data: dict) -> dict:
        """
        Convert tickers' Polars DataFrames into OHLCV format for further processing.

        Parameters:
            tickers_data (dict): A dictionary where keys are ticker symbols and values are Polars DataFrames.

        Returns:
            dict: A dictionary containing Polars DataFrames for each OHLCV type ("open", "high", "low", "close", "volume"),
                  where each DataFrame has tickers as columns.
        """
        # Initialize a dictionary to store the data for each OHLCV type
        ohlcv_data = {
            "open": [],
            "high": [],
            "low": [],
            "close": [],
            "volume": []
        }

        for ticker, df in tickers_data.items():
            # Extract the datetime column to maintain alignment
            datetime_col = df.select("datetime")

            # Process each OHLCV type and store the ticker's data
            for key in ohlcv_data.keys():
                # Combine datetime with the specific column (renamed to the ticker)
                ohlcv_data[key].append(
                    pl.concat([datetime_col, df.select([key]).rename({key: ticker})], how="horizontal")
                )

        # Concatenate all tickers' data for each OHLCV type into a single Polars DataFrame
        final_data = {
            key: pl.concat(value, how="align") if value else pl.DataFrame()
            for key, value in ohlcv_data.items()
        }

        return final_data

    def load_and_format_kline_data(self, base_path: str, tickers: list, interval: str) -> dict:
        """
        Load raw Kline CSV files for multiple tickers and format them into OHLCV format.

        Parameters:
            base_path (str): The base directory containing the Kline CSV files.
            tickers (list): List of tickers (e.g., ["BNB", "BTC", "ETH"]).
            interval (str): The interval folder (e.g., "1m").

        Returns:
            dict: A dictionary containing Polars DataFrames for "open", "high", "low", "close", and "volume".
        """
        # Step 1: Read raw data for all tickers
        tickers_data = self.read_raw_kline_data(base_path, tickers, interval)

        # Step 2: Convert raw data into OHLCV format
        formatted_data = self.convert_tickers_to_ohlcv_format(tickers_data)

        return formatted_data

    def flatten_to_database_format(self, data: dict[str, pl.DataFrame]) -> pl.DataFrame:
        """
        Flatten OHLCV data into a single Polars DataFrame with an additional 'bar' column.

        Parameters:
            data (dict): A dictionary where keys are bar types ("open", "high", etc.) and values are Polars DataFrames.

        Returns:
            pl.DataFrame: A single Polars DataFrame containing all the OHLCV data with a 'bar' column indicating the type.
        """
        # Add a 'bar' column indicating the type of data (e.g., "open", "close")
        dataframes = [
            df.with_columns(pl.lit(bar).alias('bar')) for bar, df in data.items()
        ]

        # Concatenate all the DataFrames vertically into one
        return pl.concat(dataframes, how='vertical')

    def flatten_memory_factor_to_database_format(self, factor_data: dict[str, pl.DataFrame]) -> pl.DataFrame:
        """
        Convert a dictionary of factor DataFrames into a single table with columns: datetime, ticker, factor_1, factor_2, etc.

        Parameters:
            factor_data (dict): A dictionary where keys are factor names and values are Polars DataFrames
                                with columns: datetime, BTCUSDT, ETHUSDT, etc.

        Returns:
            pl.DataFrame: A Polars DataFrame with columns: datetime, ticker, factor_1, factor_2, etc.
        """
        # Initialize an empty list to collect transformed DataFrames
        factor_tables = []

        for factor_name, df in factor_data.items():
            # Use unpivot to reshape the DataFrame to long format
            unpivoted_df = df.unpivot(
                index=["datetime"],  # Keep "datetime" as the index
                value_name=factor_name  # New column name for the factor values
            ).rename({"variable": "ticker"})  # Rename the "variable" column to "ticker"
            factor_tables.append(unpivoted_df)

        # Merge all unpivoted DataFrames on "datetime" and "ticker"
        result = factor_tables[0]
        for other_table in factor_tables[1:]:
            result = result.join(other_table, left_on=["datetime", "ticker"], right_on=["datetime", "ticker"],
                                 how="full",
                                 coalesce=True)

        return result
