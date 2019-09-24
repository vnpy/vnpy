import time
from datetime import datetime, timedelta, timezone
from typing import TYPE_CHECKING

from vnpy.trader.constant import Direction, Interval, OrderType, Status

if TYPE_CHECKING:
    # noinspection PyUnresolvedReferences
    from vnpy.gateway.oanda import OandaGateway  # noqa

STATUS_OANDA2VT = {
    "PENDING": Status.NOTTRADED,
    "FILLED": Status.ALLTRADED,
    "CANCELLED": Status.CANCELLED,
    # "TRIGGERED": Status.REJECTED,
}
STOP_ORDER_STATUS_OANDA2VT = {
    "Untriggered": Status.NOTTRADED,
    "Triggered": Status.NOTTRADED,
    # Active: triggered and placed.
    # since price is market price, placed == AllTraded?
    "Active": Status.ALLTRADED,
    "Cancelled": Status.CANCELLED,
    "Rejected": Status.REJECTED,
}
DIRECTION_VT2OANDA = {Direction.LONG: "Buy", Direction.SHORT: "Sell"}
DIRECTION_OANDA2VT = {v: k for k, v in DIRECTION_VT2OANDA.items()}
DIRECTION_OANDA2VT.update({
    "None": Direction.LONG
})

OPPOSITE_DIRECTION = {
    Direction.LONG: Direction.SHORT,
    Direction.SHORT: Direction.LONG,
}

ORDER_TYPE_VT2OANDA = {
    OrderType.LIMIT: "LIMIT",
    OrderType.MARKET: "MARKET",
    OrderType.STOP: "STOP",
}

ORDER_TYPE_OANDA2VT = {v: k for k, v in ORDER_TYPE_VT2OANDA.items()}
ORDER_TYPE_OANDA2VT.update({
    'LIMIT_ORDER': OrderType.LIMIT,
    'MARKET_ORDER': OrderType.MARKET,
    'STOP_ORDER': OrderType.STOP,
})

INTERVAL_VT2OANDA = {
    Interval.MINUTE: "M1",
    Interval.HOUR: "H1",
    Interval.DAILY: "D",
    Interval.WEEKLY: "W",
}
INTERVAL_VT2OANDA_INT = {
    Interval.MINUTE: 1,
    Interval.HOUR: 60,
    Interval.DAILY: 60 * 24,
    Interval.WEEKLY: 60 * 24 * 7,
}
INTERVAL_VT2OANDA_DELTA = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
    Interval.WEEKLY: timedelta(days=7),
}

utc_tz = timezone.utc
local_tz = datetime.now(timezone.utc).astimezone().tzinfo


def generate_timestamp(expire_after: float = 30) -> int:
    """
    :param expire_after: expires in seconds.
    :return: timestamp in milliseconds
    """
    return int(time.time() * 1000 + expire_after * 1000)


def parse_datetime(dt: str) -> datetime:
    return datetime.fromisoformat(dt[:-4])


def parse_time(dt: str) -> str:
    return dt[11:26]
