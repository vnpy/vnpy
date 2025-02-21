# -*- coding=utf-8 -*-
# @Project  : 20240720
# @FilePath : vnpy/vnpy/adapters
# @File     : overview.py
# @Time     : 2025/1/13 16:10
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
from __future__ import annotations

import atexit
import copy
import datetime
import json
import os
from typing import Dict, List, Literal, Optional
import warnings

from vnpy.config import BAR_OVERVIEW_FILENAME, FACTOR_OVERVIEW_FILENAME, TICK_OVERVIEW_FILENAME, VTSYMBOL_KLINE, \
    VTSYMBOL_FACTOR
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.database import (BarOverview, TickOverview, FactorOverview, TV_BaseOverview)
from vnpy.trader.object import HistoryRequest, SubscribeRequest, BarData, TickData, FactorData
from vnpy.trader.setting import SETTINGS
from vnpy.trader.utility import (
    extract_vt_symbol,
    get_file_path
)
from vnpy.trader.utility import load_json, save_json
from vnpy.utils.datetimes import normalize_unix, datetime2unix, TimeFreq, DatetimeUtils

SYSTEM_MODE = SETTINGS.get("system.mode", "LIVE")


class OverviewEncoder(json.JSONEncoder):
    def default(self, o):
        if isinstance(o, (Exchange, Interval)):
            return o.value
        elif isinstance(o, datetime.datetime):
            return o.strftime('%Y-%m-%d %H:%M:%S')
        elif isinstance(o, datetime.date):
            return o.strftime("%Y-%m-%d")
        elif hasattr(o, '__dict__'):
            return o.__dict__
        else:
            return super().default(o)


class OverviewDecoder(json.JSONDecoder):
    def __init__(self, *args, **kwargs):
        super().__init__(object_hook=self.dict_to_object, *args, **kwargs)

    def dict_to_object(self, d):
        if 'exchange' in d:
            d['exchange'] = Exchange(d['exchange'])
        if 'interval' in d:
            d['interval'] = Interval(d['interval'])
        for dt_field in ['start', 'end']:
            if dt_field in d:
                try:
                    d[dt_field] = datetime.datetime.strptime(d[dt_field], '%Y-%m-%d %H:%M:%S')
                except ValueError:
                    d[dt_field] = datetime.datetime.strptime(d[dt_field], '%Y-%m-%d')
                except TypeError:
                    print("TypeError", d[dt_field])
        return d


"""def save_overview(filename: str, overview_data: Dict[str, TV_BaseOverview]) -> None:
    # with open(path, 'w', encoding='utf-8') as f:
    #     json.dump(overview_data, f, cls=OverviewEncoder)

    # convert overview_data to dict
    overview_data_dict = {k: v.__dict__ for k, v in overview_data.items()}  # v is TV_BaseOverview

    # use vnpy save json
    save_json(filename, overview_data_dict, cls=OverviewEncoder, mode='w')


def load_overview(filename: str, overview_cls: TV_BaseOverview.__class__) -> Dict[str, TV_BaseOverview]:
    # if not os.path.exists(file_path):
    #     return {}
    # with open(file_path, 'r', encoding='utf-8') as f:
    #     dic = json.load(f)
    #     for k, v in dic.items():
    #         dic[k] = cls(**v)
    #     return dic

    # use vnpy load json
    overviews: Dict[str, TV_BaseOverview] = {}
    overview_dict = load_json(filename=filename, cls=OverviewDecoder)
    for k, v in overview_dict.items():
        overviews[k] = overview_cls(**v)
    return overviews"""

"""def update_bar_overview(symbol: str,
                        exchange: Exchange,
                        interval: Interval,
                        bars: Union[List, pl.DataFrame],
                        file_path: str,
                        stream: bool = False) -> None:
    if isinstance(bars, list) and isinstance(bars[0], BarData):
        raise NotImplementedError()
    elif isinstance(bars, list) and isinstance(bars[0], (list, tuple)):
        overview_dict = load_overview(file_path, cls=BarOverview)
        # 新增overview
        vt_symbol: str = VTSYMBOL_KLINE.format(interval=interval.value, symbol=bars[0][1], exchange=exchange.name)
        if vt_symbol not in overview_dict:
            overview = BarOverview(
                symbol=symbol,
                exchange=exchange,
                interval=interval,
                start=bars[0][0],  # the first value is datetime
                end=bars[-1][0],  # the first value is datetime
                count=len(bars)
            )
        else:
            # 读取已存储的overview
            overview = overview_dict[vt_symbol]

            if stream:
                overview.end = bars[-1][0]
                overview.count += len(bars)
            else:
                overview.start = min(bars[0][0], overview.start)
                overview.end = max(bars[-1][0], overview.end)
                overview.count = len(bars)  # 假设bars包含所有K线数据

        overview_dict[vt_symbol] = overview

        save_overview(file_path, overview_dict)
    elif isinstance(bars, pl.DataFrame):
        # find the first and last datetime
        start = bars['datetime'].min()
        end = bars['datetime'].max()
        count = len(bars)"""


def get_timedelta(interval: Interval) -> datetime.timedelta:
    """
    Get the timedelta for a given interval.

    Parameters:
        interval (Interval): Candlestick interval (e.g., 1m, 1h, 1d).

    Returns:
        timedelta: Time delta corresponding to the interval.
    """
    interval_map = {
        Interval.MINUTE: datetime.timedelta(minutes=1),
        Interval.HOUR: datetime.timedelta(hours=1),
        Interval.DAILY: datetime.timedelta(days=1),
        Interval.WEEKLY: datetime.timedelta(weeks=1)
    }
    return interval_map.get(interval, datetime.timedelta(minutes=1))  # Default to 1 minute if unknown


class OverviewHandler:
    """
    Handles the overview metadata for market bars in memory,
    loads data on startup, updates dynamically, and saves on exit.

    TODO: 和community上有人说的一样, 其实不应该只看两端的时间, 中间如果存在跳空的数据也应该用某种方式记录下来

    """
    bar_overview_filepath = str(get_file_path(BAR_OVERVIEW_FILENAME))
    tick_overview_filepath = str(get_file_path(TICK_OVERVIEW_FILENAME))
    factor_overview_filepath = str(get_file_path(FACTOR_OVERVIEW_FILENAME))

    def __init__(self, path: str = ""):
        """
        Initialize OverviewHandler by loading existing overview data.

        Parameters:
            path (str): Path to the JSON file where overview data is stored.
        """
        self.filename = path  # TODO: deprecate it
        warnings.warn('"path" in OverviewHandler.__init__ will be deprecated', DeprecationWarning)

        self.overview_dict: Dict[str, BarOverview] = {}  # Stores metadata in memory
        # init database overview file
        self.bar_overview = self.load_overview_hyf(filename=self.bar_overview_filepath, overview_cls=BarOverview)
        self.tick_overview = self.load_overview_hyf(filename=self.tick_overview_filepath, overview_cls=TickOverview)
        self.factor_overview = self.load_overview_hyf(filename=self.factor_overview_filepath,
                                                      overview_cls=FactorOverview)

        # Register the save function to execute when the program exits
        atexit.register(self.save_overview)

    def load_overview(self):
        """
        Load overview data from the JSON file into memory using OverviewDecoder.
        """
        if os.path.exists(self.filename):
            overview_data = load_json(self.filename, cls=OverviewDecoder)
            self.overview_dict = {k: BarOverview(**v) for k, v in overview_data.items()}
            print(f"OverviewHandler: Loaded {len(self.overview_dict)} overview records from {self.filename}.")
        else:
            print("OverviewHandler: No existing overview file found. Starting fresh.")

        for vt_symbol in SETTINGS.get("vt_symbols", ""):
            symbol, exchange = extract_vt_symbol(vt_symbol)
            interval = Interval.MINUTE
            vt_symbol = VTSYMBOL_KLINE.format(interval=interval.value, symbol=symbol, exchange=exchange.name)
            if vt_symbol not in self.overview_dict:
                self.overview_dict[vt_symbol] = BarOverview(
                    symbol=symbol,
                    exchange=exchange,
                    interval=interval,
                    count=0
                )

    def load_overview_hyf(self, filename: str, overview_cls: TV_BaseOverview.__class__) -> Dict[str, TV_BaseOverview]:
        # if not os.path.exists(file_path):
        #     return {}
        # with open(file_path, 'r', encoding='utf-8') as f:
        #     dic = json.load(f)
        #     for k, v in dic.items():
        #         dic[k] = cls(**v)
        #     return dic

        # use vnpy load json
        overviews: Dict[str, TV_BaseOverview] = {}
        overview_dict = load_json(filename=filename, cls=OverviewDecoder)
        for k, v in overview_dict.items():
            overviews[k] = overview_cls(**v)
        return overviews

    def save_overview(self):
        """
        Save the in-memory overview data to a JSON file using OverviewEncoder.
        """
        overview_data_dict = {k: v.__dict__ for k, v in self.overview_dict.items()}
        save_json(self.filename, overview_data_dict, cls=OverviewEncoder, mode="w")
        print(f"OverviewHandler: Saved {len(self.overview_dict)} overview records to {self.filename}.")

    def save_overview_hyf(self, task_type: Literal['bar', 'factor', 'tick']) -> None:
        if task_type == 'bar':
            overview_data = self.bar_overview
            filename = os.path.basename(self.bar_overview_filepath)
        elif task_type == 'factor':
            overview_data = self.factor_overview
            filename = os.path.basename(self.factor_overview_filepath)
        elif task_type == 'tick':
            overview_data = self.tick_overview
            filename = os.path.basename(self.tick_overview_filepath)
        else:
            raise ValueError(f"task_type {task_type} is not supported.")

        # convert overview_data to dict
        overview_data_dict = {k: v.__dict__ for k, v in overview_data.items()}  # v is TV_BaseOverview

        # use vnpy save json
        save_json(filename, overview_data_dict, cls=OverviewEncoder, mode='w')

    def update_overview_hyf(self, task_type: Optional[Literal["bar", "factor", "tick"]] = None,
                            data_list: List[BarData, TickData, FactorData] = None,
                            is_stream: bool = True):
        """Update the in-memory overview data when new data arrives.

        Parameters
        ----------
        task_type :
        data_list :
        is_stream : bool
            If True, the data is streaming data, otherwise it is historical data.

        Returns
        -------

        """
        if not data_list:
            return
        if task_type == 'bar':
            overview_dict = self.bar_overview
        elif task_type == 'tick':
            overview_dict = self.tick_overview
        elif task_type == 'factor':
            overview_dict = self.factor_overview
        else:
            raise ValueError(f"task_type {task_type} is not supported.")

        first, last = data_list[0], data_list[-1]
        vt_symbol = first.vt_symbol
        interval = first.interval
        symbol = first.symbol
        exchange = first.exchange
        overview = copy.deepcopy(overview_dict.get(vt_symbol, None))

        if not overview:
            overview = BarOverview(
                symbol=symbol,
                exchange=exchange,
                interval=interval,
                start=first.datetime,
                end=last.datetime,
                count=len(data_list)
            )
        elif is_stream:
            # 根据interval计算出期望的时间间隔, 预计最新的数据.start应该是本地overview.end的相差interval的时间
            expected_gap_ms = TimeFreq(interval.value).value
            if (first.datetime - overview.end).total_seconds() * 1000 > expected_gap_ms and not SYSTEM_MODE == "TEST":
                raise ValueError(f"数据时间间隔不符合预期, 请检查数据是否有跳空")
            overview.end = last.datetime
            overview.count += len(data_list)
        else:
            # 有历史数据, 所以先把新的bar insert到数据库, 然后取全量数据更新overview

            # 根据interval计算出期望的时间间隔, 预计最新的数据.start应该是本地overview.end的相差interval的时间
            n, tf = DatetimeUtils.split_time_str(interval.value)
            expected_gap_ms = n * tf.value
            if (first.datetime - overview.end).total_seconds() * 1000 > expected_gap_ms and not SYSTEM_MODE == "TEST":
                raise ValueError(f"数据时间间隔不符合预期, 请检查数据是否有跳空")  # zc: 补数据

            # update start and end
            # TODO: 和community上有人说的一样, 其实不应该只看两端的时间, 中间如果存在跳空的数据也应该用某种方式记录下来
            overview.start = min(overview.start, first.datetime)
            overview.end = max(overview.end, last.datetime)

        overview_dict[vt_symbol] = overview
        if task_type == 'bar':
            assert overview_dict == self.bar_overview
        self.save_overview_hyf(task_type=task_type)

    def update_bar_overview(self, symbol: str, exchange: Exchange, interval: Interval, bars: List[tuple]):
        """
        Update the in-memory overview data when new bars arrive.

        Parameters:
            symbol (str): Trading symbol (e.g., BTCUSDT).
            exchange (Exchange): Exchange (e.g., Binance, CME).
            interval (Interval): Candlestick interval (e.g., 1m, 1h, 1d).
            bars (List[tuple]): List of bar data in tuple format (datetime, price, volume, etc.).
        """
        if not bars:
            return

        vt_symbol = VTSYMBOL_KLINE.format(interval=interval.value, symbol=symbol, exchange=exchange.name)

        # If this symbol has no stored overview, create a new entry
        if vt_symbol not in self.overview_dict:
            self.overview_dict[vt_symbol] = BarOverview(
                symbol=symbol,
                exchange=exchange,
                interval=interval,
                start=bars[0][0],  # First bar's timestamp
                end=bars[-1][0],  # Last bar's timestamp
                count=len(bars)
            )
        else:
            overview = self.overview_dict[vt_symbol]

            # Update start/end timestamps and bar count
            overview.start = min(overview.start, bars[0][0])
            overview.end = max(overview.end, bars[-1][0])
            overview.count += len(bars)

        print(f"OverviewHandler: Updated {vt_symbol} with {len(bars)} new bars.")

    def check_missing_data(self) -> List[HistoryRequest]:
        """
        Scan all overview records and detect missing historical data.
        Generates a list of HistoryRequest objects for any missing data.

        Returns:
            List[HistoryRequest]: List of missing data requests.
        """

        missing_requests = []
        current_time = datetime.datetime.now(tz=datetime.timezone.utc)

        for vt_symbol, overview in self.overview_dict.items():
            if overview.start is None:
                expected_end = datetime.datetime(2024, 1, 1, 0, 0, 0)
            else:
                expected_end = overview.end + get_timedelta(overview.interval)

            # If current time is significantly ahead, request missing data
            if current_time > expected_end:
                print(
                    f"OverviewVT: Missing data detected for {vt_symbol}. Expected end: {expected_end}, Current time: {current_time}")

                missing_requests.append(
                    HistoryRequest(
                        symbol=overview.symbol,
                        exchange=overview.exchange,
                        start=expected_end,
                        end=current_time,
                        interval=overview.interval
                    )
                )

        return missing_requests

    def check_subscribe_stream(self) -> List[SubscribeRequest]:
        """
        Scan all overview records and generate subscription requests for real-time tick data updates.

        Returns:
            List[SubscribeRequest]: A list of tick data subscription requests.
        """
        subscribe_requests = []
        for vt_symbol, bar_overview in self.overview_dict.items():
            print(f"OverviewHandler: Subscribing to real-time data for {vt_symbol}.")
            subscribe_requests.append(
                SubscribeRequest(
                    symbol=bar_overview.symbol,
                    exchange=bar_overview.exchange,
                    interval=bar_overview.interval
                )
            )

        return subscribe_requests
