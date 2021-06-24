""""""
from datetime import datetime
from typing import List

from mongoengine import (
    Document,
    DateTimeField,
    FloatField,
    StringField,
    IntField,
    connect,
    QuerySet
)
from mongoengine.errors import DoesNotExist

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import BarData, TickData
from vnpy.trader.database import (
    BaseDatabase,
    BarOverview,
    DB_TZ,
    convert_tz
)
from vnpy.trader.setting import SETTINGS


class DbBarData(Document):
    """"""

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


class DbTickData(Document):
    """"""

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


class DbBarOverview(Document):
    """"""

    symbol: str = StringField()
    exchange: str = StringField()
    interval: str = StringField()
    count: int = IntField()
    start: datetime = DateTimeField()
    end: datetime = DateTimeField()

    meta = {
        "indexes": [
            {
                "fields": ("symbol", "exchange", "interval"),
                "unique": True,
            }
        ],
    }


class MongodbDatabase(BaseDatabase):
    """"""

    def __init__(self) -> None:
        """"""
        database = SETTINGS["database.database"]
        host = SETTINGS["database.host"]
        port = SETTINGS["database.port"]
        username = SETTINGS["database.user"]
        password = SETTINGS["database.password"]
        authentication_source = SETTINGS["database.authentication_source"]

        if not username:
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

    def save_bar_data(self, bars: List[BarData]) -> bool:
        """"""
        # Store key parameters
        bar = bars[0]
        symbol = bar.symbol
        exchange = bar.exchange
        interval = bar.interval

        # Upsert data into mongodb
        for bar in bars:
            bar.datetime = convert_tz(bar.datetime)

            d = bar.__dict__
            d["exchange"] = d["exchange"].value
            d["interval"] = d["interval"].value
            d.pop("gateway_name")
            d.pop("vt_symbol")
            param = to_update_param(d)

            DbBarData.objects(
                symbol=d["symbol"],
                exchange=d["exchange"],
                interval=d["interval"],
                datetime=d["datetime"],
            ).update_one(upsert=True, **param)

        # Update bar overview
        try:
            overview: DbBarOverview = DbBarOverview.objects(
                symbol=symbol,
                exchange=exchange.value,
                interval=interval.value
            ).get()
        except DoesNotExist:
            overview: DbBarOverview = DbBarOverview(
                symbol=symbol,
                exchange=exchange.value,
                interval=interval.value
            )

        if not overview.start:
            overview.start = bars[0].datetime
            overview.end = bars[-1].datetime
            overview.count = len(bars)
        else:
            overview.start = min(bars[0].datetime, overview.start)
            overview.end = max(bars[-1].datetime, overview.end)
            overview.count = DbBarData.objects(
                symbol=symbol,
                exchange=exchange.value,
                interval=interval.value
            ).count()

        overview.save()

    def save_tick_data(self, ticks: List[TickData]) -> bool:
        """"""
        for tick in ticks:
            tick.datetime = convert_tz(tick.datetime)

            d = tick.__dict__
            d["exchange"] = d["exchange"].value
            d.pop("gateway_name")
            d.pop("vt_symbol")
            param = to_update_param(d)

            DbTickData.objects(
                symbol=d["symbol"],
                exchange=d["exchange"],
                datetime=d["datetime"],
            ).update_one(upsert=True, **param)

    def load_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        start: datetime,
        end: datetime
    ) -> List[BarData]:
        """"""
        s: QuerySet = DbBarData.objects(
            symbol=symbol,
            exchange=exchange.value,
            interval=interval.value,
            datetime__gte=convert_tz(start),
            datetime__lte=convert_tz(end),
        )

        vt_symbol = f"{symbol}.{exchange.value}"
        bars: List[BarData] = []
        for db_bar in s:
            db_bar.datetime = DB_TZ.localize(db_bar.datetime)
            db_bar.exchange = Exchange(db_bar.exchange)
            db_bar.interval = Interval(db_bar.interval)
            db_bar.gateway_name = "DB"
            db_bar.vt_symbol = vt_symbol
            bars.append(db_bar)

        return bars

    def load_tick_data(
        self,
        symbol: str,
        exchange: Exchange,
        start: datetime,
        end: datetime
    ) -> List[TickData]:
        """"""
        s: QuerySet = DbTickData.objects(
            symbol=symbol,
            exchange=exchange.value,
            datetime__gte=convert_tz(start),
            datetime__lte=convert_tz(end),
        )

        vt_symbol = f"{symbol}.{exchange.value}"
        ticks: List[TickData] = []
        for db_tick in s:
            db_tick.datetime = DB_TZ.localize(db_tick.datetime)
            db_tick.exchange = Exchange(db_tick.exchange)
            db_tick.gateway_name = "DB"
            db_tick.vt_symbol = vt_symbol
            ticks.append(db_tick)

        return ticks

    def delete_bar_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval
    ) -> int:
        """"""
        count = DbBarData.objects(
            symbol=symbol,
            exchange=exchange.value,
            interval=interval.value
        ).delete()

        # Delete bar overview
        DbBarOverview.objects(
            symbol=symbol,
            exchange=exchange.value,
            interval=interval.value
        ).delete()

        return count

    def delete_tick_data(
        self,
        symbol: str,
        exchange: Exchange
    ) -> int:
        """"""
        count = DbTickData.objects(
            symbol=symbol,
            exchange=exchange.value
        ).delete()
        return count

    def get_bar_overview(self) -> List[BarOverview]:
        """
        Return data avaible in database.
        """
        # Init bar overview for old version database
        data_count = DbBarData.objects.count()
        overview_count = DbBarOverview.objects.count()
        if data_count and not overview_count:
            self.init_bar_overview()

        s: QuerySet = DbBarOverview.objects()
        overviews = []
        for overview in s:
            overview.exchange = Exchange(overview.exchange)
            overview.interval = Interval(overview.interval)
            overviews.append(overview)
        return overviews

    def init_bar_overview(self) -> None:
        """
        Init overview table if not exists.
        """
        s: QuerySet = (
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

        for d in s:
            id_data = d["_id"]

            overview = DbBarOverview()
            overview.symbol = id_data["symbol"]
            overview.exchange = id_data["exchange"]
            overview.interval = id_data["interval"]
            overview.count = d["count"]

            start_bar: DbBarData = (
                DbBarData.objects(
                    symbol=id_data["symbol"],
                    exchange=id_data["exchange"],
                    interval=id_data["interval"],
                )
                .order_by("+datetime")
                .first()
            )
            overview.start = start_bar.datetime

            end_bar: DbBarData = (
                DbBarData.objects(
                    symbol=id_data["symbol"],
                    exchange=id_data["exchange"],
                    interval=id_data["interval"],
                )
                .order_by("-datetime")
                .first()
            )
            overview.end = end_bar.datetime

            overview.save()


def to_update_param(d: dict) -> dict:
    """
    Convert data dict to update parameters.
    """
    param = {f"set__{k}": v for k, v in d.items()}
    return param


database_manager = MongodbDatabase()
