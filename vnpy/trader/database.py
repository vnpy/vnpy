from abc import ABC, abstractmethod
from datetime import datetime
from typing import List
from pytz import timezone
from dataclasses import dataclass
from importlib import import_module

from .constant import Interval, Exchange
from .object import BarData, TickData
from .setting import SETTINGS


DB_TZ = timezone(SETTINGS["database.timezone"])


@dataclass
class BarOverview:
    """
    Overview of bar data stored in database.
    """

    symbol: str
    exchange: Exchange
    interval: Interval
    count: int
    start: datetime
    end: datetime


class BaseDatabase(ABC):
    """
    Abstract database class for connecting to different database.
    """

    @abstractmethod
    def save_bar_data(self, bars: List[BarData]) -> bool:
        """
        Save bar data into database.
        """
        pass

    @abstractmethod
    def save_tick_data(self, ticks: List[TickData]) -> bool:
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
        Return data avaible in database.
        """
        pass


driver: str = SETTINGS["database.driver"]
module_name: str = f"vnpy.database.{driver}"
try:
    database_manager: BaseDatabase = import_module(module_name).database_manager
except ModuleNotFoundError:
    print(f"找不到数据库驱动{module_name}，使用默认的SQLite数据库")
    database_manager: BaseDatabase = import_module("vnpy.database.sqlite").database_manager
