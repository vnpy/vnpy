from dataclasses import dataclass, field
from enum import Enum

from vnpy.trader.constant import Direction, Offset

APP_NAME = "PortfolioStrategy"


class StrategyState:
    """Strategy State"""

    NOTINITED = "Not Initialized"
    INITING = "Initializing"
    INITED = "Initialized"
    STARTING = "Starting"
    TRADING = "Trading"
    STOPPING = "Stopping"
    STOPPED = "Stopped"


class AlgoStatus:
    """Algorithm status"""
    RUNNING = "running"
    PAUSED = "paused"
    STOPPED = "stopped"
    FINISHED = "finished"

class StopOrderStatus(Enum):
    WAITING = "WAITING"
    CANCELLED = "CANCELLED"
    TRIGGERED = "TRIGGERED"


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
    lock: bool = False
    vt_orderids: list = field(default_factory=list)
    status: StopOrderStatus = StopOrderStatus.WAITING


EVENT_PORTFOLIO_LOG = "ePortfolioLog"
EVENT_PORTFOLIO_STRATEGY = "ePortfolioStrategy"
