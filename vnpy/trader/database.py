from abc import ABC, abstractmethod
from datetime import datetime
from typing import Optional, List, Dict, Tuple
from pytz import timezone

from .constant import Interval, Exchange
from .object import BarData, TickData
from .setting import SETTINGS


DB_TZ = timezone(SETTINGS["database.timezone"])


class BaseDatabase(ABC):
    """
    Abstract database class for connecting to different database.
    """

    @abstractmethod
    def save_bar_data(
        self,
        bars: List[BarData],
    ):
        """
        Save bar data into database.
        """
        pass

    @abstractmethod
    def save_tick_data(
        self,
        ticks: List[TickData],
    ):
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
    def get_bar_data_range(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval
    ) -> Tuple[Optional[datetime], Optional[datetime]]:
        """
        If there is data in database, return the datetime of oldest and latest data.
        """
        pass

    @abstractmethod
    def get_bar_data_statistics(self) -> List[Dict]:
        """
        Return data avaible in database with a list of symbol/exchange/interval/count.
        """
        pass
