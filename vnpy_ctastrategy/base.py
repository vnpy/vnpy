"""
Defines constants and objects used in CtaStrategy App.
"""

from dataclasses import dataclass, field
from enum import Enum
from datetime import datetime, timedelta

from vnpy.trader.constant import Direction, Offset, Interval
from .locale import _

APP_NAME = "CtaStrategy"
STOPORDER_PREFIX = "STOP"


class StopOrderStatus(Enum):
    WAITING = _("等待中")
    CANCELLED = _("已撤销")
    TRIGGERED = _("已触发")


class EngineType(Enum):
    LIVE = _("实盘")
    BACKTESTING = _("回测")


class BacktestingMode(Enum):
    BAR = 1
    TICK = 2


@dataclass
class StopOrder:
    vt_symbol: str
    direction: Direction
    offset: Offset
    price: float
    volume: float
    stop_orderid: str
    strategy_name: str
    datetime: datetime
    lock: bool = False
    net: bool = False
    vt_orderids: list = field(default_factory=list)
    status: StopOrderStatus = StopOrderStatus.WAITING


EVENT_CTA_LOG = "eCtaLog"
EVENT_CTA_STRATEGY = "eCtaStrategy"
EVENT_CTA_STOPORDER = "eCtaStopOrder"


INTERVAL_DELTA_MAP: dict[Interval, timedelta] = {
    Interval.TICK: timedelta(milliseconds=1),
    Interval.MINUTE: timedelta(minutes=1),
    Interval.MINUTE_15: timedelta(minutes=15),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
    Interval.WEEKLY: timedelta(weeks=1),
}
