""""""
from datetime import datetime
from typing import List, Dict, Optional, Sequence, Type

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
    fn
)

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import BarData, TickData
from vnpy.trader.utility import get_file_path
from .database import BaseDatabaseManager, Driver


def init(driver: Driver, settings: dict):
    init_funcs = {
        Driver.SQLITE: init_sqlite,
        Driver.MYSQL: init_mysql,
        Driver.POSTGRESQL: init_postgresql,
    }
    assert driver in init_funcs

    db = init_funcs[driver](settings)
    bar, tick = init_models(db, driver)
    return SqlManager(bar, tick)


def init_sqlite(settings: dict):
    database = settings["database"]
    path = str(get_file_path(database))
    db = SqliteDatabase(path)
    return db


def init_mysql(settings: dict):
    keys = {"database", "user", "password", "host", "port"}
    settings = {k: v for k, v in settings.items() if k in keys}
    db = MySQLDatabase(**settings)
    return db


def init_postgresql(settings: dict):
    keys = {"database", "user", "password", "host", "port"}
    settings = {k: v for k, v in settings.items() if k in keys}
    db = PostgresqlDatabase(**settings)
    return db


class ModelBase(Model):

    def to_dict(self):
        return self.__data__


def init_models(db: Database, driver: Driver):
    class DbBarData(ModelBase):
        """
        Candlestick bar data for database storage.

        Index is defined unique with datetime, interval, symbol
        """

        id = AutoField()
        symbol: str = CharField()
        exchange: str = CharField()
        datetime: datetime = DateTimeField()
        interval: str = CharField()

        volume: float = FloatField()
        open_interest: float = FloatField()
        open_price: float = FloatField()
        high_price: float = FloatField()
        low_price: float = FloatField()
        close_price: float = FloatField()

        class Meta:
            database = db
            indexes = ((("symbol", "exchange", "interval", "datetime"), True),)

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
            db_bar.open_interest = bar.open_interest
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
                open_interest=self.open_interest,
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
            dicts = [i.to_dict() for i in objs]
            with db.atomic():
                if driver is Driver.POSTGRESQL:
                    for bar in dicts:
                        DbBarData.insert(bar).on_conflict(
                            update=bar,
                            conflict_target=(
                                DbBarData.symbol,
                                DbBarData.exchange,
                                DbBarData.interval,
                                DbBarData.datetime,
                            ),
                        ).execute()
                else:
                    for c in chunked(dicts, 50):
                        DbBarData.insert_many(
                            c).on_conflict_replace().execute()

    class DbTickData(ModelBase):
        """
        Tick data for database storage.

        Index is defined unique with (datetime, symbol)
        """

        id = AutoField()

        symbol: str = CharField()
        exchange: str = CharField()
        datetime: datetime = DateTimeField()

        name: str = CharField()
        volume: float = FloatField()
        open_interest: float = FloatField()
        last_price: float = FloatField()
        last_volume: float = FloatField()
        limit_up: float = FloatField()
        limit_down: float = FloatField()

        open_price: float = FloatField()
        high_price: float = FloatField()
        low_price: float = FloatField()
        pre_close: float = FloatField()

        bid_price_1: float = FloatField()
        bid_price_2: float = FloatField(null=True)
        bid_price_3: float = FloatField(null=True)
        bid_price_4: float = FloatField(null=True)
        bid_price_5: float = FloatField(null=True)

        ask_price_1: float = FloatField()
        ask_price_2: float = FloatField(null=True)
        ask_price_3: float = FloatField(null=True)
        ask_price_4: float = FloatField(null=True)
        ask_price_5: float = FloatField(null=True)

        bid_volume_1: float = FloatField()
        bid_volume_2: float = FloatField(null=True)
        bid_volume_3: float = FloatField(null=True)
        bid_volume_4: float = FloatField(null=True)
        bid_volume_5: float = FloatField(null=True)

        ask_volume_1: float = FloatField()
        ask_volume_2: float = FloatField(null=True)
        ask_volume_3: float = FloatField(null=True)
        ask_volume_4: float = FloatField(null=True)
        ask_volume_5: float = FloatField(null=True)

        class Meta:
            database = db
            indexes = ((("symbol", "exchange", "datetime"), True),)

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
            db_tick.open_interest = tick.open_interest
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

            return db_tick

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
                open_interest=self.open_interest,
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
            dicts = [i.to_dict() for i in objs]
            with db.atomic():
                if driver is Driver.POSTGRESQL:
                    for tick in dicts:
                        DbTickData.insert(tick).on_conflict(
                            update=tick,
                            conflict_target=(
                                DbTickData.symbol,
                                DbTickData.exchange,
                                DbTickData.datetime,
                            ),
                        ).execute()
                else:
                    for c in chunked(dicts, 50):
                        DbTickData.insert_many(c).on_conflict_replace().execute()

    db.connect()
    db.create_tables([DbBarData, DbTickData])
    return DbBarData, DbTickData


class SqlManager(BaseDatabaseManager):

    def __init__(self, class_bar: Type[Model], class_tick: Type[Model]):
        self.class_bar = class_bar
        self.class_tick = class_tick

    def load_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        start: datetime,
        end: datetime,
    ) -> Sequence[BarData]:
        s = (
            self.class_bar.select()
                .where(
                (self.class_bar.symbol == symbol)
                & (self.class_bar.exchange == exchange.value)
                & (self.class_bar.interval == interval.value)
                & (self.class_bar.datetime >= start)
                & (self.class_bar.datetime <= end)
            )
            .order_by(self.class_bar.datetime)
        )
        data = [db_bar.to_bar() for db_bar in s]
        return data

    def load_tick_data(
        self, symbol: str, exchange: Exchange, start: datetime, end: datetime
    ) -> Sequence[TickData]:
        s = (
            self.class_tick.select()
                .where(
                (self.class_tick.symbol == symbol)
                & (self.class_tick.exchange == exchange.value)
                & (self.class_tick.datetime >= start)
                & (self.class_tick.datetime <= end)
            )
            .order_by(self.class_tick.datetime)
        )

        data = [db_tick.to_tick() for db_tick in s]
        return data

    def save_bar_data(self, datas: Sequence[BarData]):
        ds = [self.class_bar.from_bar(i) for i in datas]
        self.class_bar.save_all(ds)

    def save_tick_data(self, datas: Sequence[TickData]):
        ds = [self.class_tick.from_tick(i) for i in datas]
        self.class_tick.save_all(ds)

    def get_newest_bar_data(
        self, symbol: str, exchange: "Exchange", interval: "Interval"
    ) -> Optional["BarData"]:
        s = (
            self.class_bar.select()
                .where(
                (self.class_bar.symbol == symbol)
                & (self.class_bar.exchange == exchange.value)
                & (self.class_bar.interval == interval.value)
            )
            .order_by(self.class_bar.datetime.desc())
            .first()
        )
        if s:
            return s.to_bar()
        return None

    def get_oldest_bar_data(
        self, symbol: str, exchange: "Exchange", interval: "Interval"
    ) -> Optional["BarData"]:
        s = (
            self.class_bar.select()
                .where(
                (self.class_bar.symbol == symbol)
                & (self.class_bar.exchange == exchange.value)
                & (self.class_bar.interval == interval.value)
            )
            .order_by(self.class_bar.datetime.asc())
            .first()
        )
        if s:
            return s.to_bar()
        return None

    def get_newest_tick_data(
        self, symbol: str, exchange: "Exchange"
    ) -> Optional["TickData"]:
        s = (
            self.class_tick.select()
                .where(
                (self.class_tick.symbol == symbol)
                & (self.class_tick.exchange == exchange.value)
            )
            .order_by(self.class_tick.datetime.desc())
            .first()
        )
        if s:
            return s.to_tick()
        return None

    def get_bar_data_statistics(self) -> List[Dict]:
        """"""
        s = (
            self.class_bar.select(
                self.class_bar.symbol,
                self.class_bar.exchange,
                self.class_bar.interval,
                fn.COUNT(self.class_bar.id).alias('ct')
            ).group_by(
                self.class_bar.symbol,
                self.class_bar.exchange,
                self.class_bar.interval
            )
        )

        result = []

        for data in s:
            result.append({
                "symbol": data.symbol,
                "exchange": data.exchange,
                "interval": data.interval,
                "count": data.ct
            })

        return result

    def delete_bar_data(
        self,
        symbol: str,
        exchange: "Exchange",
        interval: "Interval"
    ) -> int:
        """
        Delete all bar data with given symbol + exchange + interval.
        """
        query = self.class_bar.delete().where(
            (self.class_bar.symbol == symbol)
            & (self.class_bar.exchange == exchange.value)
            & (self.class_bar.interval == interval.value)
        )
        count = query.execute()
        return count

    def clean(self, symbol: str):
        self.class_bar.delete().where(self.class_bar.symbol == symbol).execute()
        self.class_tick.delete().where(self.class_tick.symbol == symbol).execute()
