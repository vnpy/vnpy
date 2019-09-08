import hashlib
import hmac
import time
from datetime import datetime, timedelta, timezone

from vnpy.trader.constant import Direction, Interval, OrderType, Status

STATUS_BYBIT2VT = {
    "Created": Status.NOTTRADED,
    "New": Status.NOTTRADED,
    "PartiallyFilled": Status.PARTTRADED,
    "Filled": Status.ALLTRADED,
    "Cancelled": Status.CANCELLED,
    "Rejected": Status.REJECTED,
}
STOP_ORDER_STATUS_BYBIT2VT = {
    "Untriggered": Status.NOTTRADED,
    "Triggered": Status.NOTTRADED,
    # Active: triggered and placed.
    # since price is market price, placed == AllTraded?
    "Active": Status.ALLTRADED,
    "Cancelled": Status.CANCELLED,
    "Rejected": Status.REJECTED,
}
DIRECTION_VT2BYBIT = {Direction.LONG: "Buy", Direction.SHORT: "Sell"}
DIRECTION_BYBIT2VT = {v: k for k, v in DIRECTION_VT2BYBIT.items()}
DIRECTION_BYBIT2VT.update({
    "None": Direction.LONG
})

OPPOSITE_DIRECTION = {
    Direction.LONG: Direction.SHORT,
    Direction.SHORT: Direction.LONG,
}

ORDER_TYPE_VT2BYBIT = {
    OrderType.LIMIT: "Limit",
    OrderType.MARKET: "Market",
}

ORDER_TYPE_BYBIT2VT = {v: k for k, v in ORDER_TYPE_VT2BYBIT.items()}

INTERVAL_VT2BYBIT = {
    Interval.MINUTE: "1",
    Interval.HOUR: "60",
    Interval.DAILY: "D",
    Interval.WEEKLY: "W",
}
INTERVAL_VT2BYBIT_INT = {
    Interval.MINUTE: 1,
    Interval.HOUR: 60,
    Interval.DAILY: 60*24,
    Interval.WEEKLY: 60*24*7,
}
TIMEDELTA_MAP = {
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


def sign(secret: bytes, data: bytes) -> str:
    """"""
    return hmac.new(
        secret, data, digestmod=hashlib.sha256
    ).hexdigest()


def parse_datetime(dt: str) -> str:
    return dt[11:19]
