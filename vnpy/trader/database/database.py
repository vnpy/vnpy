from abc import ABC, abstractmethod
from datetime import datetime
from enum import Enum
from typing import Optional, Sequence, List, Dict, TYPE_CHECKING

from pytz import timezone

from vnpy.trader.setting import SETTINGS

if TYPE_CHECKING:
    from vnpy.trader.constant import Interval, Exchange  # noqa
    from vnpy.trader.object import BarData, TickData  # noqa

DB_TZ = timezone(SETTINGS["database.timezone"])


class Driver(Enum):
    SQLITE = "sqlite"
    MYSQL = "mysql"
    POSTGRESQL = "postgresql"
    MONGODB = "mongodb"
    INFLUX = "influxdb"
    TIMESCALEDB = 'timescaledb'


class BaseDatabaseManager(ABC):

    @abstractmethod
    def load_bar_data(
            self,
            symbol: str,
            exchange: "Exchange",
            interval: "Interval",
            start: datetime,
            end: datetime
    ) -> Sequence["BarData"]:
        pass

    @abstractmethod
    def load_tick_data(
            self,
            symbol: str,
            exchange: "Exchange",
            start: datetime,
            end: datetime
    ) -> Sequence["TickData"]:
        pass

    @abstractmethod
    def save_bar_data(
            self,
            datas: Sequence["BarData"],
    ):
        pass

    @abstractmethod
    def save_tick_data(
            self,
            datas: Sequence["TickData"],
    ):
        pass

    @abstractmethod
    def get_newest_bar_data(
            self,
            symbol: str,
            exchange: "Exchange",
            interval: "Interval"
    ) -> Optional["BarData"]:
        """
        If there is data in database, return the one with greatest datetime(newest one)
        otherwise, return None
        """
        pass

    @abstractmethod
    def get_oldest_bar_data(
            self,
            symbol: str,
            exchange: "Exchange",
            interval: "Interval"
    ) -> Optional["BarData"]:
        """
        If there is data in database, return the one with smallest datetime(oldest one)
        otherwise, return None
        """
        pass

    @abstractmethod
    def get_newest_tick_data(
            self,
            symbol: str,
            exchange: "Exchange",
    ) -> Optional["TickData"]:
        """
        If there is data in database, return the one with greatest datetime(newest one)
        otherwise, return None
        """
        pass

    @abstractmethod
    def get_bar_data_statistics(
            self,
            symbol: str,
            exchange: "Exchange",
    ) -> List[Dict]:
        """
        Return data avaible in database with a list of symbol/exchange/interval/count.
        """
        pass

    @abstractmethod
    def delete_bar_data(
            self,
            symbol: str,
            exchange: "Exchange",
            interval: "Interval"
    ) -> int:
        """
        Delete all bar data with given symbol + exchange + interval.
        """
        pass

    @abstractmethod
    def clean(self, symbol: str):
        """
        delete all records for a symbol
        """
        pass
