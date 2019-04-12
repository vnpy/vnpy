""""""
from enum import Enum
from typing import List

from peewee import (
    AutoField,
    CharField,
    Database,
    DateTimeField,
    FloatField,
    Model,
    MySQLDatabase,
    PostgresqlDatabase,
    SqliteDatabase,
    chunked,
)

from .constant import Exchange, Interval
from .object import BarData, TickData
from .setting import SETTINGS
from .utility import get_file_path


class Driver(Enum):
    SQLITE = "sqlite"
    MYSQL = "mysql"
    POSTGRESQL = "postgresql"


_db: Database
_driver: Driver


def init():
    global _driver
    db_settings = {k[9:]: v for k, v in SETTINGS.items() if k.startswith("database.")}
    _driver = Driver(db_settings["driver"])

    init_funcs = {
        Driver.SQLITE: init_sqlite,
        Driver.MYSQL: init_mysql,
        Driver.POSTGRESQL: init_postgresql,
    }

    assert _driver in init_funcs
    del db_settings["driver"]
    return init_funcs[_driver](db_settings)


def init_sqlite(settings: dict):
    global _db
    database = settings["database"]

    _db = SqliteDatabase(str(get_file_path(database)))


def init_mysql(settings: dict):
    global _db
    _db = MySQLDatabase(**settings)


def init_postgresql(settings: dict):
    global _db
    _db = PostgresqlDatabase(**settings)


init()


class ModelBase(Model):
    def to_dict(self):
        return self.__data__


class DbBarData(ModelBase):
    """
    Candlestick bar data for database storage.

    Index is defined unique with datetime, interval, symbol
    """

    id = AutoField()
    symbol = CharField()
    exchange = CharField()
    datetime = DateTimeField()
    interval = CharField()

    volume = FloatField()
    open_price = FloatField()
    high_price = FloatField()
    low_price = FloatField()
    close_price = FloatField()

    class Meta:
        database = _db
        indexes = ((("datetime", "interval", "symbol"), True),)

    @staticmethod
    def from_bar(bar: BarData):
        """
        Generate DbBarData object from BarData.
        """
        db_bar = DbBarData()

        db_bar.symbol = bar.symbol
        db_bar.exchange = bar.exchange.value
        db_bar.datetime = bar.datetime
        db_bar.interval = bar.interval.value
        db_bar.volume = bar.volume
        db_bar.open_price = bar.open_price
        db_bar.high_price = bar.high_price
        db_bar.low_price = bar.low_price
        db_bar.close_price = bar.close_price

        return db_bar

    def to_bar(self):
        """
        Generate BarData object from DbBarData.
        """
        bar = BarData(
            symbol=self.symbol,
            exchange=Exchange(self.exchange),
            datetime=self.datetime,
            interval=Interval(self.interval),
            volume=self.volume,
            open_price=self.open_price,
            high_price=self.high_price,
            low_price=self.low_price,
            close_price=self.close_price,
            gateway_name="DB",
        )
        return bar

    @staticmethod
    def save_all(objs: List["DbBarData"]):
        """
        save a list of objects, update if exists.
        """
        with _db.atomic():
            if _driver is Driver.POSTGRESQL:
                for bar in objs:
                    DbBarData.insert(bar.to_dict()).on_conflict(
                        update=bar.to_dict(),
                        conflict_target=(
                            DbBarData.datetime,
                            DbBarData.interval,
                            DbBarData.symbol,
                        ),
                    ).execute()
            else:
                for c in chunked(objs, 50):
                    DbBarData.insert_many(c).on_conflict_replace()


class DbTickData(ModelBase):
    """
    Tick data for database storage.

    Index is defined unique with (datetime, symbol)
    """

    id = AutoField()

    symbol = CharField()
    exchange = CharField()
    datetime = DateTimeField()

    name = CharField()
    volume = FloatField()
    last_price = FloatField()
    last_volume = FloatField()
    limit_up = FloatField()
    limit_down = FloatField()

    open_price = FloatField()
    high_price = FloatField()
    low_price = FloatField()
    close_price = FloatField()
    pre_close = FloatField()

    bid_price_1 = FloatField()
    bid_price_2 = FloatField()
    bid_price_3 = FloatField()
    bid_price_4 = FloatField()
    bid_price_5 = FloatField()

    ask_price_1 = FloatField()
    ask_price_2 = FloatField()
    ask_price_3 = FloatField()
    ask_price_4 = FloatField()
    ask_price_5 = FloatField()

    bid_volume_1 = FloatField()
    bid_volume_2 = FloatField()
    bid_volume_3 = FloatField()
    bid_volume_4 = FloatField()
    bid_volume_5 = FloatField()

    ask_volume_1 = FloatField()
    ask_volume_2 = FloatField()
    ask_volume_3 = FloatField()
    ask_volume_4 = FloatField()
    ask_volume_5 = FloatField()

    class Meta:
        database = _db
        indexes = ((("datetime", "symbol"), True),)

    @staticmethod
    def from_tick(tick: TickData):
        """
        Generate DbTickData object from TickData.
        """
        db_tick = DbTickData()

        db_tick.symbol = tick.symbol
        db_tick.exchange = tick.exchange.value
        db_tick.datetime = tick.datetime
        db_tick.name = tick.name
        db_tick.volume = tick.volume
        db_tick.last_price = tick.last_price
        db_tick.last_volume = tick.last_volume
        db_tick.limit_up = tick.limit_up
        db_tick.limit_down = tick.limit_down
        db_tick.open_price = tick.open_price
        db_tick.high_price = tick.high_price
        db_tick.low_price = tick.low_price
        db_tick.pre_close = tick.pre_close

        db_tick.bid_price_1 = tick.bid_price_1
        db_tick.ask_price_1 = tick.ask_price_1
        db_tick.bid_volume_1 = tick.bid_volume_1
        db_tick.ask_volume_1 = tick.ask_volume_1

        if tick.bid_price_2:
            db_tick.bid_price_2 = tick.bid_price_2
            db_tick.bid_price_3 = tick.bid_price_3
            db_tick.bid_price_4 = tick.bid_price_4
            db_tick.bid_price_5 = tick.bid_price_5

            db_tick.ask_price_2 = tick.ask_price_2
            db_tick.ask_price_3 = tick.ask_price_3
            db_tick.ask_price_4 = tick.ask_price_4
            db_tick.ask_price_5 = tick.ask_price_5

            db_tick.bid_volume_2 = tick.bid_volume_2
            db_tick.bid_volume_3 = tick.bid_volume_3
            db_tick.bid_volume_4 = tick.bid_volume_4
            db_tick.bid_volume_5 = tick.bid_volume_5

            db_tick.ask_volume_2 = tick.ask_volume_2
            db_tick.ask_volume_3 = tick.ask_volume_3
            db_tick.ask_volume_4 = tick.ask_volume_4
            db_tick.ask_volume_5 = tick.ask_volume_5

        return tick

    def to_tick(self):
        """
        Generate TickData object from DbTickData.
        """
        tick = TickData(
            symbol=self.symbol,
            exchange=Exchange(self.exchange),
            datetime=self.datetime,
            name=self.name,
            volume=self.volume,
            last_price=self.last_price,
            last_volume=self.last_volume,
            limit_up=self.limit_up,
            limit_down=self.limit_down,
            open_price=self.open_price,
            high_price=self.high_price,
            low_price=self.low_price,
            pre_close=self.pre_close,
            bid_price_1=self.bid_price_1,
            ask_price_1=self.ask_price_1,
            bid_volume_1=self.bid_volume_1,
            ask_volume_1=self.ask_volume_1,
            gateway_name="DB",
        )

        if self.bid_price_2:
            tick.bid_price_2 = self.bid_price_2
            tick.bid_price_3 = self.bid_price_3
            tick.bid_price_4 = self.bid_price_4
            tick.bid_price_5 = self.bid_price_5

            tick.ask_price_2 = self.ask_price_2
            tick.ask_price_3 = self.ask_price_3
            tick.ask_price_4 = self.ask_price_4
            tick.ask_price_5 = self.ask_price_5

            tick.bid_volume_2 = self.bid_volume_2
            tick.bid_volume_3 = self.bid_volume_3
            tick.bid_volume_4 = self.bid_volume_4
            tick.bid_volume_5 = self.bid_volume_5

            tick.ask_volume_2 = self.ask_volume_2
            tick.ask_volume_3 = self.ask_volume_3
            tick.ask_volume_4 = self.ask_volume_4
            tick.ask_volume_5 = self.ask_volume_5

        return tick

    @staticmethod
    def save_all(objs: List["DbTickData"]):
        with _db.atomic():
            if _driver is Driver.POSTGRESQL:
                for bar in objs:
                    DbTickData.insert(bar.to_dict()).on_conflict(
                        update=bar.to_dict(),
                        preserve=(DbTickData.id),
                        conflict_target=(DbTickData.datetime, DbTickData.symbol),
                    ).execute()
            else:
                for c in chunked(objs, 50):
                    DbBarData.insert_many(c).on_conflict_replace()


_db.connect()
_db.create_tables([DbBarData, DbTickData])
