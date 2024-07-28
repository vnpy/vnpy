from abc import ABC, abstractmethod
from datetime import datetime
from types import ModuleType
from typing import List
from dataclasses import dataclass
from importlib import import_module

from .constant import Interval, Exchange
from .object import BarData, TickData
from .setting import SETTINGS
from .utility import ZoneInfo
from .locale import _
import json
import os
from datetime import datetime
from typing import List, Dict, Tuple, Union



DB_TZ = ZoneInfo(SETTINGS["database.timezone"])


def convert_tz(dt: datetime) -> datetime:
    """
    Convert timezone of datetime object to DB_TZ.
    """
    dt: datetime = dt.astimezone(DB_TZ)
    return dt.replace(tzinfo=None)


@dataclass
class BarOverview:
    """
    BarOverview of bar data stored in database.
    """

    symbol: str = ""
    exchange: Exchange = None
    interval: Interval = None
    count: int = 0
    start: datetime = None
    end: datetime = None
    
    def __init__(self, symbol: str, exchange: Exchange, interval: Interval, start: datetime, end: datetime, count: int=0):
        self.symbol = symbol
        self.exchange = exchange
        self.interval = interval
        self.start = start
        self.end = end
        self.count = count

@dataclass
class TickOverview:
    """
    BarOverview of tick data stored in database.
    """

    symbol: str = ""
    exchange: Exchange = None
    count: int = 0
    start: datetime = None
    end: datetime = None


class BaseDatabase(ABC):
    """
    Abstract database class for connecting to different database.
    """

    @abstractmethod
    def save_bar_data(self, bars: List[BarData], stream: bool = False) -> bool:
        """
        Save bar data into database.
        """
        pass

    @abstractmethod
    def save_tick_data(self, ticks: List[TickData], stream: bool = False) -> bool:
        """
        Save tick data into database.
        """
        pass

    @abstractmethod
    def load_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        start: datetime,
        end: datetime
    ) -> List[BarData]:
        """
        Load bar data from database.
        """
        pass

    @abstractmethod
    def load_tick_data(
        self,
        symbol: str,
        exchange: Exchange,
        start: datetime,
        end: datetime
    ) -> List[TickData]:
        """
        Load tick data from database.
        """
        pass

    @abstractmethod
    def delete_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval
    ) -> int:
        """
        Delete all bar data with given symbol + exchange + interval.
        """
        pass

    @abstractmethod
    def delete_tick_data(
        self,
        symbol: str,
        exchange: Exchange
    ) -> int:
        """
        Delete all tick data with given symbol + exchange.
        """
        pass

    @abstractmethod
    def get_bar_overview(self) -> List[BarOverview]:
        """
        Return bar data avaible in database.
        """
        pass

    @abstractmethod
    def get_tick_overview(self) -> List[TickBarOverview]:
        """
        Return tick data avaible in database.
        """
        pass


database: BaseDatabase = None


def get_database() -> BaseDatabase:
    """"""
    # Return database object if already inited
    global database
    if database:
        return database

    # Read database related global setting
    database_name: str = SETTINGS["database.name"]
    module_name: str = f"vnpy_{database_name}"

    # Try to import database module
    try:
        module: ModuleType = import_module(module_name)
    except ModuleNotFoundError:
        print(_("找不到数据库驱动{}，使用默认的SQLite数据库").format(module_name))
        module: ModuleType = import_module("vnpy_sqlite")

    # Create database object from module
    database = module.Database()
    return database



def load_overview(file_path: str) -> Dict[Tuple[str, str, str], Dict]:
    if not os.path.exists(file_path):
        return {}
    with open(file_path, 'r') as f:
        return json.load(f)

def save_overview(file_path: str, overview_data: Dict[Tuple[str, str, str], Dict]) -> None:
    with open(file_path, 'w') as f:
        json.dump(overview_data, f)

def update_bar_overview(symbol: str, exchange: Exchange, interval: Interval, bars: List, file_path: str, stream: bool) -> None:
    overview_data = load_overview(file_path)

    key = (exchange.name, interval.name, symbol)
    if key not in overview_data:
        overview = BarOverview(
            symbol=symbol,
            exchange=exchange,
            interval=interval,
            start=bars[0].datetime,
            end=bars[-1].datetime,
            count=len(bars)
        )
    else:
        overview_dict = overview_data[key]
        overview = BarOverview(
            symbol=overview_dict['symbol'],
            exchange=overview_dict['exchange'],
            interval=overview_dict['interval'],
            start=datetime.fromisoformat(overview_dict['start']),
            end=datetime.fromisoformat(overview_dict['end']),
            count=overview_dict['count']
        )

        if stream:
            overview.end = bars[-1].datetime
            overview.count += len(bars)
        else:
            overview.start = min(bars[0].datetime, overview.start)
            overview.end = max(bars[-1].datetime, overview.end)
            overview.count = len(bars)  # 假设bars包含所有K线数据

    overview_data[key] = {
        'symbol': overview.symbol,
        'exchange': overview.exchange,
        'interval': overview.interval,
        'start': overview.start.isoformat(),
        'end': overview.end.isoformat(),
        'count': overview.count
    }

    save_overview(file_path, overview_data)

