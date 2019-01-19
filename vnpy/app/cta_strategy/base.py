"""
Defines constants and objects used in CtaStrategy App.
"""

from enum import Enum
from dataclasses import dataclass
from typing import Any

from vnpy.trader.constant import Direction, Offset

APP_NAME = "CtaStrategy"
STOPORDER_PREFIX = "STOP."


class CtaOrderType(Enum):
    BUY = "买开"
    SELL = "买开"
    SHORT = "买开"
    COVER = "买开"


class StopOrderStatus(Enum):
    WAITING = "等待中"
    CANCELLED = "已撤销"
    TRIGGERED = "已触发"


class EngineType(Enum):
    LIVE = "实盘"
    BACKTESTING = "回测"


@dataclass
class StopOrder:
    vt_symbol: str
    order_type: CtaOrderType
    direction: Direction
    offset: Offset
    price: float
    volume: float
    stop_orderid: str
    strategy: Any
    status: StopOrderStatus = StopOrderStatus.WAITING
    vt_orderid: str = ""


EVENT_CTA_LOG = 'eCtaLog'
EVENT_CTA_STRATEGY = 'eCtaStrategy'
EVENT_CTA_STOPORDER = 'eCtaStopOrder'

ORDER_CTA2VT = {
    CtaOrderType.BUY: (Direction.LONG,
                       Offset.OPEN),
    CtaOrderType.SELL: (Direction.SHORT,
                        Offset.CLOSE),
    CtaOrderType.SHORT: (Direction.SHORT,
                         Offset.OPEN),
    CtaOrderType.COVER: (Direction.LONG,
                         Offset.CLOSE),
}
