"""
Basic data structure used for general trading function in the trading platform.
"""
from collections import defaultdict
from dataclasses import dataclass, field
from datetime import datetime
from logging import INFO
from typing import Optional

from .constant import Direction, Exchange, Interval, Offset, Status, Product, OptionType, OrderType
from ..config import VTSYMBOL_BARDATA, VTSYMBOL_FACTORDATA, VTSYMBOL_TICKDATA

ACTIVE_STATUSES = set([Status.SUBMITTING, Status.NOTTRADED, Status.PARTTRADED])


@dataclass
class BaseData:
    """
    Any data object needs a gateway_name as source
    and should inherit base data.
    """
    gateway_name: str = field(default=None)
    extra: dict = field(default=None, init=False)

    VTSYMBOL_TEMPLATE: str = field(default=None, init=False)


@dataclass
class TickData(BaseData):
    """
    Tick data contains information about:
        * last trade in market
        * orderbook snapshot
        * intraday market statistics.
    """

    symbol: str = field(default=None, init=True)
    exchange: Exchange = field(default=None, init=True)
    datetime: datetime = field(default=None, init=True)

    name: str = ""
    volume: float = 0
    turnover: float = 0
    open_interest: float = 0
    last_price: float = 0
    last_volume: float = 0
    limit_up: float = 0
    limit_down: float = 0

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

    localtime: datetime = None

    VTSYMBOL_TEMPLATE = VTSYMBOL_TICKDATA

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = self.VTSYMBOL_TEMPLATE.format(symbol=self.symbol, exchange=self.exchange.value)


@dataclass
class FactorData(BaseData):
    """
    Factor data contains information about:
        * factor value
        * factor name
        * factor frequency
    """

    symbol: str = field(default=None, init=True)
    exchange: Exchange = field(default=None, init=True)
    datetime: datetime = field(default=None, init=True)
    factor_name: str = field(default="factor_unknown", init=True)
    interval: Interval = field(default=None, init=True)

    value: float = None

    VTSYMBOL_TEMPLATE = VTSYMBOL_FACTORDATA

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = self.VTSYMBOL_TEMPLATE.format(interval=self.interval.value, symbol=self.symbol,
                                                            factorname=self.factor_name, exchange=self.exchange.value)


@dataclass
class BarData(BaseData):
    """
    Candlestick bar data of a certain trading period.
    """

    symbol: str = field(default=None, init=True)
    exchange: Exchange = field(default=None, init=True)
    datetime: datetime = field(default=None, init=True)

    interval: Interval = None
    volume: float = 0  # quoted asset volume (����һ�㶼��usdt�Ƽ�, ��ô�����volume����usdt�Ƽۺ��volume)
    turnover: float = 0
    open_interest: float = 0
    open_price: float = 0
    high_price: float = 0
    low_price: float = 0
    close_price: float = 0
    quote_asset_volume: float = 0
    number_of_trades: float = 0
    taker_buy_base_asset_volume: float = 0
    taker_buy_quote_asset_volume: float = 0

    VTSYMBOL_TEMPLATE = VTSYMBOL_BARDATA

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = self.VTSYMBOL_TEMPLATE.format(symbol=self.symbol, exchange=self.exchange.value)


@dataclass
class OrderData(BaseData):
    """
    Order data contains information for tracking lastest status
    of a specific order.
    """

    symbol: str = field(default=None, init=True)
    exchange: Exchange = field(default=None, init=True)
    orderid: str = field(default=None, init=True)

    type: OrderType = OrderType.LIMIT
    direction: Direction | None = None
    offset: Offset = Offset.NONE
    price: float = 0
    volume: float = 0
    stop_loss_price: float = 0
    take_profit_price: float = 0
    traded: float = 0
    status: Status = Status.SUBMITTING
    datetime: Datetime | None = None
    reference: str = ""

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = f"{self.symbol}.{self.exchange.value}"
        self.vt_orderid: str = f"{self.gateway_name}-{self.orderid}"

    def is_active(self) -> bool:
        """
        Check if the order is active.
        """
        return self.status in ACTIVE_STATUSES

    def create_cancel_request(self) -> "CancelRequest":
        """
        Create cancel request object from order.
        """
        req: CancelRequest = CancelRequest(
            orderid=self.orderid, symbol=self.symbol, exchange=self.exchange
        )
        return req


@dataclass
class TradeData(BaseData):
    """
    Trade data contains information of a fill of an order. One order
    can have several trade fills.
    """

    symbol: str = field(default=None, init=True)
    exchange: Exchange = field(default=None, init=True)
    orderid: str = field(default=None, init=True)
    tradeid: str = field(default=None, init=True)
    direction: Direction = None

    offset: Offset = Offset.NONE
    price: float = 0
    volume: float = 0
    datetime: datetime = None
    reference: str = ""

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = f"{self.symbol}.{self.exchange.value}"
        self.vt_orderid: str = f"{self.gateway_name}.{self.orderid}"
        self.vt_tradeid: str = f"{self.gateway_name}.{self.tradeid}"


@dataclass
class PositionData(BaseData):
    """
    Position data is used for tracking each individual position holding.
    """

    symbol: str = field(default=None, init=True)
    exchange: Exchange = field(default=None, init=True)
    direction: Direction = field(default=None, init=True)

    volume: float = 0
    frozen: float = 0
    price: float = 0
    pnl: float = 0
    yd_volume: float = 0

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = f"{self.symbol}.{self.exchange.value}"
        self.vt_positionid: str = f"{self.gateway_name}.{self.vt_symbol}.{self.direction.value}"


@dataclass
class AccountData(BaseData):
    """
    Account data contains information about balance, frozen and
    available.
    """

    accountid: str = field(default=None, init=True)

    balance: float = 0
    frozen: float = 0

    def __post_init__(self) -> None:
        """"""
        self.available: float = self.balance - self.frozen
        self.vt_accountid: str = f"{self.gateway_name}.{self.accountid}"


@dataclass
class LogData(BaseData):
    """
    Log data is used for recording log messages on GUI or in log files.
    """

    msg: str = field(default=None, init=True)
    level: int = field(default=INFO, init=True)

    def __post_init__(self) -> None:
        """"""
        self.msg = f"[{self.gateway_name+']:':<17} {self.msg}"
        self.time: datetime = datetime.now()


@dataclass
class ContractData(BaseData):
    """
    Contract data contains basic information about each contract traded.
    """

    symbol: str = field(default=None, init=True)
    exchange: Exchange = field(default=None, init=True)
    name: str = field(default=None, init=True)
    product: Product = field(default=None, init=True)
    size: float = field(default=None, init=True)
    pricetick: float = field(default=None, init=True)
    interval: Interval = field(default=None, init=True)  # hyf

    min_volume: float = 1           # minimum trading volume of the contract
    max_volume: float | None = None      # maximum order volume
    stop_supported: bool = False    # whether server supports stop order
    net_position: bool = False      # whether gateway uses net position volume
    history_data: bool = False      # whether gateway provides bar history data

    option_strike: float | None = None
    option_underlying: str | None = None     # vt_symbol of underlying contract
    option_type: OptionType | None = None
    option_listed: datetime | None = None
    option_expiry: datetime | None = None
    option_portfolio: str | None = None
    option_index: str | None = None          # for identifying options with same strike price

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = f"{self.symbol}.{self.exchange.value}"


@dataclass
class QuoteData(BaseData):
    """
    Quote data contains information for tracking lastest status
    of a specific quote.
    """

    symbol: str = field(default=None, init=True)
    exchange: Exchange = field(default=None, init=True)
    quoteid: str = field(default=None, init=True)

    bid_price: float = 0.0
    bid_volume: int = 0
    ask_price: float = 0.0
    ask_volume: int = 0
    bid_offset: Offset = Offset.NONE
    ask_offset: Offset = Offset.NONE
    status: Status = Status.SUBMITTING
    datetime: datetime | None = None
    reference: str = ""

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = f"{self.symbol}.{self.exchange.value}"
        self.vt_quoteid: str = f"{self.gateway_name}.{self.quoteid}"

    def is_active(self) -> bool:
        """
        Check if the quote is active.
        """
        return self.status in ACTIVE_STATUSES

    def create_cancel_request(self) -> "CancelRequest":
        """
        Create cancel request object from quote.
        """
        req: CancelRequest = CancelRequest(
            orderid=self.quoteid, symbol=self.symbol, exchange=self.exchange
        )
        return req


@dataclass
class SubscribeRequest:
    """
    Request sending to specific gateway for subscribing tick data update.
    """

    symbol: str
    exchange: Exchange
    interval: Interval

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = f"{self.symbol}.{self.exchange.value}"


@dataclass
class OrderRequest:
    """
    Request sending to specific gateway for creating a new order.
    """

    symbol: str
    exchange: Exchange
    direction: Direction
    type: OrderType
    volume: float
    price: float = 0
    stop_loss: float = 0
    take_profit: float = 0
    strategy_name: str = ""
    offset: Offset = Offset.NONE
    reference: str = ""

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = f"{self.symbol}.{self.exchange.value}"

    def create_order_data(self, orderid: Optional[str], gateway_name: Optional[str]) -> OrderData:
        """
        Create order data from request.
        """
        orderid = f"{self.symbol}-{self.strategy_name}-{str(datetime.now().timestamp()).split('.')[0]}"
        if self.direction == Direction.LONG:
            stop_loss_price = self.price * (1 - self.stop_loss)
            take_profit_price = self.price * (1 + self.take_profit)
        else:
            stop_loss_price = self.price * (1 + self.stop_loss)
            take_profit_price = self.price * (1 - self.take_profit)
        order: OrderData = OrderData(
            symbol=self.symbol,
            exchange=self.exchange,
            orderid=orderid,
            type=self.type,
            direction=self.direction,
            offset=self.offset,
            price=self.price,
            stop_loss_price=stop_loss_price,
            take_profit_price=take_profit_price,
            volume=self.volume,
            reference=self.reference,
            gateway_name=gateway_name,
        )
        return order


@dataclass
class CancelRequest:
    """
    Request sending to specific gateway for canceling an existing order.
    """

    orderid: str
    symbol: str
    exchange: Exchange

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = f"{self.symbol}.{self.exchange.value}"


@dataclass
class HistoryRequest:
    """
    Request sending to specific gateway for querying history data.
    """

    symbol: str
    exchange: Exchange
    start: datetime
    end: datetime | None = None
    interval: Interval | None = None

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = f"{self.symbol}.{self.exchange.value}"


@dataclass
class QuoteRequest:
    """
    Request sending to specific gateway for creating a new quote.
    """

    symbol: str
    exchange: Exchange
    bid_price: float
    bid_volume: int
    ask_price: float
    ask_volume: int
    bid_offset: Offset = Offset.NONE
    ask_offset: Offset = Offset.NONE
    reference: str = ""

    def __post_init__(self) -> None:
        """"""
        self.vt_symbol: str = f"{self.symbol}.{self.exchange.value}"

    def create_quote_data(self, quoteid: str, gateway_name: str) -> QuoteData:
        """
        Create quote data from request.
        """
        quote: QuoteData = QuoteData(
            symbol=self.symbol,
            exchange=self.exchange,
            quoteid=quoteid,
            bid_price=self.bid_price,
            bid_volume=self.bid_volume,
            ask_price=self.ask_price,
            ask_volume=self.ask_volume,
            bid_offset=self.bid_offset,
            ask_offset=self.ask_offset,
            reference=self.reference,
            gateway_name=gateway_name,
        )
        return quote
