import csv
from datetime import datetime
from typing import List, Optional, Callable, Literal, Union, Dict
from logging import DEBUG, INFO, ERROR, WARNING
import polars as pl
import os

from vnpy.trader.engine import BaseEngine, MainEngine, EventEngine, Event, EVENT_LOG
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.object import BarData, TickData, ContractData, HistoryRequest, LogData
from vnpy.trader.database import BaseDatabase, get_database, BarOverview, DB_TZ
from vnpy.trader.datafeed import BaseDatafeed, get_datafeed
from vnpy.trader.utility import ZoneInfo

APP_NAME = "DataManager"


class DataManagerEngine(BaseEngine):
    """"""

    SAVE_PATH_TEMPLATE = "{exchange}/spot/1m/{symbol}_1m_{start}_{end}.csv"

    def __init__(
            self,
            main_engine: MainEngine,
            event_engine: EventEngine,
    ) -> None:
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.database: BaseDatabase = get_database()
        self.datafeed: BaseDatafeed = get_datafeed()

    def __gen_save_path__(self, save_dir: str, exchange: Exchange, symbol: str, start: datetime, end: datetime) -> str:
        save_path = os.path.join(save_dir,
                                 self.SAVE_PATH_TEMPLATE.format(exchange=exchange.name.lower(), symbol=symbol,
                                                                start=start.strftime("%Y-%m-%d %H:%M:%S"),
                                                                end=end.strftime("%Y-%m-%d %H:%M:%S")))
        if not os.path.exists(os.path.dirname(save_path)):
            os.makedirs(os.path.dirname(save_path))
        return save_path

    def import_data_from_csv(
            self,
            file_path: str,
            symbol: str,
            exchange: Exchange,
            interval: Interval,
            tz_name: str,
            datetime_head: str,
            open_head: str,
            high_head: str,
            low_head: str,
            close_head: str,
            volume_head: str,
            turnover_head: str,
            open_interest_head: str,
            datetime_format: str
    ) -> tuple:
        """"""
        with open(file_path, "rt") as f:
            buf: list = [line.replace("\0", "") for line in f]

        reader: csv.DictReader = csv.DictReader(buf, delimiter=",")

        bars: List[BarData] = []
        start: datetime = None
        count: int = 0
        tz = ZoneInfo(tz_name)

        for item in reader:
            if datetime_format:
                dt: datetime = datetime.strptime(item[datetime_head], datetime_format)
            else:
                dt: datetime = datetime.fromisoformat(item[datetime_head])
            dt = dt.replace(tzinfo=tz)

            turnover = item.get(turnover_head, 0)
            open_interest = item.get(open_interest_head, 0)

            bar: BarData = BarData(
                symbol=symbol,
                exchange=exchange,
                datetime=dt,
                interval=interval,
                volume=float(item[volume_head]),
                open_price=float(item[open_head]),
                high_price=float(item[high_head]),
                low_price=float(item[low_head]),
                close_price=float(item[close_head]),
                turnover=float(turnover),
                open_interest=float(open_interest),
                gateway_name="DB",
            )

            bars.append(bar)

            # do some statistics
            count += 1
            if not start:
                start = bar.datetime

        end: datetime = bar.datetime

        # insert into database
        self.database.save_bar_data(bars)

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
        bars: List[BarData] = self.load_bar_data(symbol, exchange, interval, start, end)

        fieldnames: list = [
            "symbol",
            "exchange",
            "datetime",
            "open",
            "high",
            "low",
            "close",
            "volume",
            "turnover",
            "open_interest"
        ]

        try:
            with open(file_path, "w") as f:
                writer: csv.DictWriter = csv.DictWriter(f, fieldnames=fieldnames, lineterminator="\n")
                writer.writeheader()

                for bar in bars:
                    d: dict = {
                        "symbol": bar.symbol,
                        "exchange": bar.exchange.value,
                        "datetime": bar.datetime.strftime("%Y-%m-%d %H:%M:%S"),
                        "open": bar.open_price,
                        "high": bar.high_price,
                        "low": bar.low_price,
                        "close": bar.close_price,
                        "turnover": bar.turnover,
                        "volume": bar.volume,
                        "open_interest": bar.open_interest,
                    }
                    writer.writerow(d)

            return True
        except PermissionError:
            return False

    def get_bar_overview(self) -> List[BarOverview]:
        """"""
        return self.database.get_bar_overview()

    def load_bar_data(
            self,
            symbol: str,
            exchange: Exchange,
            interval: Interval,
            start: datetime,
            end: datetime
    ) -> List[BarData]:
        """"""
        bars: List[BarData] = self.database.load_bar_data(
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
        count: int = self.database.delete_bar_data(
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
            start: datetime,
            output: Callable = None,
            method: Literal["gateway", "datafeed"] = "",
            save: bool = False,
            save_dir: Union[str, Literal["database"]] = "",
            end: datetime = None,
    ) -> int:
        """
        Query bar data from datafeed.
        """
        if not output:
            output = self.write_log
        end = datetime.now(DB_TZ) if not end else end
        req: HistoryRequest = HistoryRequest(
            symbol=symbol,
            exchange=exchange,
            interval=Interval(interval),
            start=start,
            end=end
        )

        vt_symbol: str = f"{symbol}.{exchange.value}"
        contract: Optional[ContractData] = self.main_engine.get_contract(vt_symbol)

        if not method:
            # If history data provided in gateway, then query
            if contract and contract.history_data:
                data: List[BarData] = self.main_engine.query_history(
                    req, contract.gateway_name
                )
            # Otherwise use datafeed to query data
            else:
                data: Union[List[Union[BarData, Dict]], pl.DataFrame] = self.datafeed.query_bar_history(req=req)
        elif method == "gateway":
            data: List[BarData] = self.main_engine.query_history(req, contract.gateway_name)
        elif method == "datafeed":
            data: List[BarData] = self.datafeed.query_bar_history(req, output)
        else:
            raise ValueError(f"Invalid method value: {method}")

        if save and data is not None:
            assert save_dir, "Save directory must be provided when save is True"
            if save_dir == "database":
                self.database.save_bar_data(data, stream=False)
            else:
                if isinstance(data, pl.DataFrame):
                    # save polars dataframe to csv
                    start = data[0, "datetime"]
                    end = data[-1, "datetime"]
                    save_path: str = self.__gen_save_path__(save_dir, exchange, symbol, start, end)
                    data.write_csv(file=save_path, include_header=True, )
                elif isinstance(data, list) and isinstance(data[0], dict):
                    data: pl.DataFrame = pl.from_dicts(data)
                    start = data[0, "datetime"]
                    end = data[-1, "datetime"]
                    save_path: str = self.__gen_save_path__(save_dir, exchange, symbol, start, end)
                    data.write_csv(file=save_path, include_header=True, )
                else:
                    raise NotImplementedError("Only polars dataframe is supported for saving to csv")
            return len(data)

        return 0

    def download_tick_data(
            self,
            symbol: str,
            exchange: Exchange,
            start: datetime,
            output: Callable,
            method: Literal["gateway", "datafeed"] = ""
    ) -> int:
        """
        Query tick data from datafeed.
        """
        req: HistoryRequest = HistoryRequest(
            symbol=symbol,
            exchange=exchange,
            start=start,
            end=datetime.now(DB_TZ)
        )

        data: List[TickData] = self.datafeed.query_tick_history(req, output)

        if data:
            self.database.save_tick_data(data)
            return (len(data))

        return 0

    def write_log(self, msg: str, level: int = INFO) -> None:
        """"""
        log: LogData = LogData(msg=msg, gateway_name=APP_NAME, level=level)
        event: Event = Event(EVENT_LOG, log)
        self.event_engine.put(event)

    # def read_data(self, base_path: str, tickers: list, interval: str) -> dict:
    #     """
    #     Read raw Kline CSV files for multiple tickers and convert them to Polars DataFrames.
    #
    #     Parameters:
    #         base_path (str): The base directory containing the Kline CSV files.
    #         tickers (list): List of tickers (e.g., ["BNB", "BTC", "ETH"]).
    #         interval (str): The interval folder (e.g., "1m").
    #
    #     Returns:
    #         dict: A dictionary containing Polars DataFrames for "open", "high", "low", "close", and "volume".
    #     """
    #     # Define column names for the CSV files
    #     column_names = [
    #         "Open_time", "open", "high", "low", "close", "volume",
    #         "Close_time", "Quote_asset_volume", "Number_of_trades",
    #         "Taker_buy_base_asset_volume", "Taker_buy_quote_asset_volume", "Ignore"
    #     ]
    #
    #     schema = {
    #         "Open_time": pl.Int64,
    #         "open": pl.Float64,
    #         "high": pl.Float64,
    #         "low": pl.Float64,
    #         "close": pl.Float64,
    #         "volume": pl.Float64,
    #         "Close_time": pl.Int64,
    #         "Quote_asset_volume": pl.Float64,
    #         "Number_of_trades": pl.Int64,
    #         "Taker_buy_base_asset_volume": pl.Float64,
    #         "Taker_buy_quote_asset_volume": pl.Float64,
    #         "Ignore": pl.Utf8,
    #     }
    #
    #     tickers_data = {}
    #
    #     for ticker in tickers:
    #         # Construct the path to the ticker's data files
    #         ticker_path = os.path.join(base_path, ticker, interval)
    #
    #         if not os.path.exists(ticker_path):
    #             print(f"Path not found: {ticker_path}")
    #             continue
    #
    #         # List all CSV files for the ticker
    #         csv_files = [f for f in os.listdir(ticker_path) if f.endswith(".csv")]
    #
    #         # Read all files for this ticker
    #         ticker_df = pl.concat(
    #             [
    #                 pl.read_csv(
    #                     os.path.join(ticker_path, file),
    #                     has_header=False,
    #                     new_columns=column_names,
    #                     schema=schema,
    #                     low_memory=True
    #                 ).select(["Open_time", "open", "high", "low", "close", "volume"])
    #                 for file in csv_files
    #             ],
    #             how="vertical",
    #         )
    #
    #         # Parse datetime and keep required columns
    #         ticker_df = ticker_df.select([
    #             pl.from_epoch(pl.col("Open_time"), time_unit='ms').alias("datetime"),
    #             pl.col("open"), pl.col("high"), pl.col("low"), pl.col("close"), pl.col("volume")
    #         ])
    #         tickers_data[ticker] = ticker_df
    #
    #     return tickers_data
    #
    # # Combine data into OHLCV format
    # def convert_to_ohlcv(self, tickers_data: dict) -> dict:
    #     """
    #     Convert tickers_data into OHLCV format.
    #
    #     Parameters:
    #         tickers_data (dict): A dictionary containing tickers as keys and Polars DataFrames as values.
    #
    #     Returns:
    #         dict: A dictionary containing Polars DataFrames for "open", "high", "low", "close", and "volume".
    #     """
    #     ohlcv_data = {
    #         "open": [],
    #         "high": [],
    #         "low": [],
    #         "close": [],
    #         "volume": []
    #     }
    #
    #     for ticker, df in tickers_data.items():
    #         datetime_col = df.select("datetime")
    #         for key in ohlcv_data.keys():
    #             ohlcv_data[key].append(
    #                 pl.concat([datetime_col, df.select([key]).rename({key: ticker})], how="horizontal")
    #             )
    #
    #     # Concatenate all ticker data into single Polars DataFrames for each OHLCV type
    #     final_data = {
    #         key: pl.concat(value, how="align") if value else pl.DataFrame()
    #         for key, value in ohlcv_data.items()
    #     }
    #
    #     return final_data
    #
    # def load_data_from_csv(self, base_path, tickers, interval):
    #     tickers_data = self.read_data(base_path, tickers, interval)
    #
    #     converted_data = self.convert_to_ohlcv(tickers_data)
    #
    #     return converted_data
