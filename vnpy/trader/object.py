"""
Basic data structure used for general trading function in VN Trader.
"""

from dataclasses import dataclass
from datetime import datetime
from logging import INFO

from .constant import (STATUS_SUBMITTING, STATUS_NOTTRADED, STATUS_PARTTRADED)

ACTIVE_STATUSES = set([STATUS_SUBMITTING, STATUS_NOTTRADED, STATUS_PARTTRADED])


@dataclass
class BaseData:
    """
    Any data object needs a gateway_name as source or 
    destination and should inherit base data.
    """
    gateway_name: str


@dataclass
class TickData(BaseData):
    """
    Tick data contains information about:
        * last trade in market
        * orderbook snapshot
        * intraday market statistics.
    """
    symbol: str
    exchange: str
    datetime: datetime

    volume: float = 0
    last_price: float = 0
    last_volume: float = 0

    open_price: float = 0
    high_price: float = 0
    low_price: float = 0
    pre_close: float = 0

    bid_price_1: float = 0
    bid_price_2: float = 0
    bid_price_3: float = 0
    bid_price_4: float = 0
    bid_price_5: float = 0

    ask_price_1: float = 0
    ask_price_2: float = 0
    ask_price_3: float = 0
    ask_price_4: float = 0
    ask_price_5: float = 0

    bid_volume_1: float = 0
    bid_volume_2: float = 0
    bid_volume_3: float = 0
    bid_volume_4: float = 0
    bid_volume_5: float = 0

    ask_volume_1: float = 0
    ask_volume_2: float = 0
    ask_volume_3: float = 0
    ask_volume_4: float = 0
    ask_volume_5: float = 0

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange}"


@dataclass
class BarData(BaseData):
    """
    Candlestick bar data of a certain trading period.
    """
    symbol: str
    exchange: str
    datetime: datetime
    inteval: str

    volume: float = 0
    open_price: float = 0
    high_price: float = 0
    low_price: float = 0
    close_price: float = 0

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange}"


@dataclass
class OrderData(BaseData):
    """
    Order data contains information for tracking lastest status 
    of a specific order.
    """
    symbol: str
    exchange: str
    orderid: str

    direction: str = ""
    offset: str = ""
    price: float = 0
    volume: float = 0
    traded: float = 0
    status: str = ""
    time: str = ""

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange}"
        self.vt_orderid = f"{self.gateway_name}.{self.orderid}"

    def is_active(self):
        """
        Check if the order is active.
        """
        if self.status in ACTIVE_STATUSES:
            return True
        else:
            return False

    def create_cancel_request(self):
        """
        Create cancel request object from order.
        """
        req = CancelRequest(
            orderid=self.orderid,
            symbol=self.symbol,
            exchange=self.exchange
        )
        return req


@dataclass
class TradeData(BaseData):
    """
    Trade data contains information of a fill of an order. One order
    can have several trade fills.
    """
    symbol: str
    exchange: str
    orderid: str
    tradeid: str

    direction: str = ""
    offset: str = ""
    price: float = 0
    volume: float = 0
    time: str = ""

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange}"
        self.vt_orderid = f"{self.gateway_name}.{self.orderid}"
        self.vt_tradeid = f"{self.gateway_name}.{self.tradeid}"


@dataclass
class PositionData(BaseData):
    """
    Positon data is used for tracking each individual position holding.
    """
    symbol: str
    exchange: str
    direction: str

    volume: float = 0
    frozen: float = 0
    price: float = 0
    pnl: float = 0

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange}"
        self.vt_positionid = f"{self.vt_symbol}.{self.direction}"


@dataclass
class AccountData(BaseData):
    """
    Account data contains information about balance, frozen and
    available.
    """
    accountid: str

    balance: float = 0
    frozen: float = 0

    def __post_init__(self):
        """"""
        self.available = self.balance - self.frozen
        self.vt_accountid = f"{self.gateway_name}.{self.accountid}"


@dataclass
class LogData(BaseData):
    """
    Log data is used for recording log messages on GUI or in log files.
    """
    msg: str
    level: int = INFO

    def __post_init__(self):
        """"""
        self.time = datetime.now()


@dataclass
class ContractData(BaseData):
    """
    Contract data contains basic information about each contract traded.
    """
    symbol: str
    exchange: str
    name: str
    product: str
    size: int
    pricetick: float

    option_strike: float = 0
    option_underlying: str = '' # vt_symbol of underlying contract
    option_type: str = ''
    option_expiry: datetime = None

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange}"


@dataclass
class SubscribeRequest:
    """
    Request sending to specific gateway for subscribing tick data update.
    """
    symbol: str
    exchange: str = ''

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange}"


@dataclass
class OrderRequest:
    """
    Request sending to specific gateway for creating a new order.
    """
    symbol: str
    direction: str
    price_type: str
    volume: float
    exchange: str = ''
    price: float = 0
    offset: str = ''

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange}"


@dataclass
class CancelRequest:
    """
    Request sending to specific gateway for canceling an existing order.
    """
    orderid: str
    symbol: str = ''
    exchange: str = ''

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange}"
