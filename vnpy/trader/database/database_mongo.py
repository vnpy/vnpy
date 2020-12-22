from datetime import datetime
from enum import Enum
from typing import Optional, Sequence, List
from tzlocal import get_localzone

from mongoengine import DateTimeField, Document, FloatField, StringField, connect

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import BarData, TickData

from .database import BaseDatabaseManager, Driver, DB_TZ


LOCAL_TZ = get_localzone()


def init(_: Driver, settings: dict):
    database = settings["database"]
    host = settings["host"]
    port = settings["port"]
    username = settings["user"]
    password = settings["password"]
    authentication_source = settings["authentication_source"]

    if not username:  # if username == '' or None, skip username
        username = None
        password = None
        authentication_source = None

    connect(
        db=database,
        host=host,
        port=port,
        username=username,
        password=password,
        authentication_source=authentication_source,
    )

    return MongoManager()


class DbBarData(Document):
    """
    Candlestick bar data for database storage.

    Index is defined unique with datetime, interval, symbol
    """

    symbol: str = StringField()
    exchange: str = StringField()
    datetime: datetime = DateTimeField()
    interval: str = StringField()

    volume: float = FloatField()
    open_interest: float = FloatField()
    open_price: float = FloatField()
    high_price: float = FloatField()
    low_price: float = FloatField()
    close_price: float = FloatField()

    meta = {
        "indexes": [
            {
                "fields": ("symbol", "exchange", "interval", "datetime"),
                "unique": True,
            }
        ]
    }

    def to_bar(self):
        """
        Generate BarData object from DbBarData.
        """
        bar = BarData(
            symbol=self.symbol,
            exchange=Exchange(self.exchange),
            datetime=DB_TZ.localize(self.datetime),
            interval=Interval(self.interval),
            volume=self.volume,
            open_interest=self.open_interest,
            open_price=self.open_price,
            high_price=self.high_price,
            low_price=self.low_price,
            close_price=self.close_price,
            gateway_name="DB",
        )
        return bar


class DbTickData(Document):
    """
    Tick data for database storage.

    Index is defined unique with (datetime, symbol)
    """

    symbol: str = StringField()
    exchange: str = StringField()
    datetime: datetime = DateTimeField()

    name: str = StringField()
    volume: float = FloatField()
    open_interest: float = FloatField()
    last_price: float = FloatField()
    last_volume: float = FloatField()
    limit_up: float = FloatField()
    limit_down: float = FloatField()

    open_price: float = FloatField()
    high_price: float = FloatField()
    low_price: float = FloatField()
    close_price: float = FloatField()
    pre_close: float = FloatField()

    bid_price_1: float = FloatField()
    bid_price_2: float = FloatField()
    bid_price_3: float = FloatField()
    bid_price_4: float = FloatField()
    bid_price_5: float = FloatField()

    ask_price_1: float = FloatField()
    ask_price_2: float = FloatField()
    ask_price_3: float = FloatField()
    ask_price_4: float = FloatField()
    ask_price_5: float = FloatField()

    bid_volume_1: float = FloatField()
    bid_volume_2: float = FloatField()
    bid_volume_3: float = FloatField()
    bid_volume_4: float = FloatField()
    bid_volume_5: float = FloatField()

    ask_volume_1: float = FloatField()
    ask_volume_2: float = FloatField()
    ask_volume_3: float = FloatField()
    ask_volume_4: float = FloatField()
    ask_volume_5: float = FloatField()

    meta = {
        "indexes": [
            {
                "fields": ("symbol", "exchange", "datetime"),
                "unique": True,
            }
        ],
    }

    def to_tick(self):
        """
        Generate TickData object from DbTickData.
        """
        tick = TickData(
            symbol=self.symbol,
            exchange=Exchange(self.exchange),
            datetime=DB_TZ.localize(self.datetime),
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


class MongoManager(BaseDatabaseManager):

    def load_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        start: datetime,
        end: datetime,
    ) -> Sequence[BarData]:
        s = DbBarData.objects(
            symbol=symbol,
            exchange=exchange.value,
            interval=interval.value,
            datetime__gte=convert_tz(start),
            datetime__lte=convert_tz(end),
        )
        data = [db_bar.to_bar() for db_bar in s]
        return data

    def load_tick_data(
        self, symbol: str, exchange: Exchange, start: datetime, end: datetime
    ) -> Sequence[TickData]:
        s = DbTickData.objects(
            symbol=symbol,
            exchange=exchange.value,
            datetime__gte=convert_tz(start),
            datetime__lte=convert_tz(end),
        )
        data = [db_tick.to_tick() for db_tick in s]
        return data

    @staticmethod
    def to_update_param(d) -> dict:
        dt = DB_TZ.localize(d.datetime)
        d.datetime = dt.replace(tzinfo=None)

        param = {
            "set__" + k: v.value if isinstance(v, Enum) else v
            for k, v in d.__dict__.items()
        }
        return param

    def save_bar_data(self, datas: Sequence[BarData]):
        for d in datas:
            updates = self.to_update_param(d)
            updates.pop("set__gateway_name")
            updates.pop("set__vt_symbol")
            (
                DbBarData.objects(
                    symbol=d.symbol, interval=d.interval.value, datetime=d.datetime
                ).update_one(upsert=True, **updates)
            )

    def save_tick_data(self, datas: Sequence[TickData]):
        for d in datas:
            updates = self.to_update_param(d)
            updates.pop("set__gateway_name")
            updates.pop("set__vt_symbol")
            (
                DbTickData.objects(
                    symbol=d.symbol, exchange=d.exchange.value, datetime=d.datetime
                ).update_one(upsert=True, **updates)
            )

    def get_newest_bar_data(
        self, symbol: str, exchange: "Exchange", interval: "Interval"
    ) -> Optional["BarData"]:
        s = (
            DbBarData.objects(
                symbol=symbol,
                exchange=exchange.value,
                interval=interval.value
            )
            .order_by("-datetime")
            .first()
        )
        if s:
            return s.to_bar()
        return None

    def get_oldest_bar_data(
        self, symbol: str, exchange: "Exchange", interval: "Interval"
    ) -> Optional["BarData"]:
        s = (
            DbBarData.objects(
                symbol=symbol,
                exchange=exchange.value,
                interval=interval.value
            )
            .order_by("+datetime")
            .first()
        )
        if s:
            return s.to_bar()
        return None

    def get_newest_tick_data(
        self, symbol: str, exchange: "Exchange"
    ) -> Optional["TickData"]:
        s = (
            DbTickData.objects(symbol=symbol, exchange=exchange.value)
            .order_by("-datetime")
            .first()
        )
        if s:
            return s.to_tick()
        return None

    def get_bar_data_statistics(self) -> List:
        """"""
        s = (
            DbBarData.objects.aggregate({
                "$group": {
                    "_id": {
                        "symbol": "$symbol",
                        "exchange": "$exchange",
                        "interval": "$interval",
                    },
                    "count": {"$sum": 1}
                }
            })
        )

        result = []

        for d in s:
            data = d["_id"]
            data["count"] = d["count"]
            result.append(data)

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
        count = DbBarData.objects(
            symbol=symbol,
            exchange=exchange.value,
            interval=interval.value
        ).delete()

        return count

    def clean(self, symbol: str):
        DbTickData.objects(symbol=symbol).delete()
        DbBarData.objects(symbol=symbol).delete()


def convert_tz(dt: datetime):
    """"""
    if not dt.tzinfo:
        dt = LOCAL_TZ.localize(dt)
    dt = DB_TZ.localize(dt)
    return dt.replace(tzinfo=None)
