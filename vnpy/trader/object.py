"""
Basic data structure used for general trading function in VN Trader.
"""
from dataclasses import dataclass
from datetime import datetime
from logging import INFO

from .constant import (
    Direction, Exchange, Interval, Offset, Status, Product, OptionType, OrderType,
    Currency
)

ACTIVE_STATUSES = set([Status.SUBMITTING, Status.NOTTRADED, Status.PARTTRADED])


@dataclass
class BaseData:
    """
    Any data object needs a gateway_name as source
    and should inherit base data.
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
    exchange: Exchange
    datetime: datetime

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

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"


@dataclass
class BarData(BaseData):
    """
    Candlestick bar data of a certain trading period.
    """

    symbol: str
    exchange: Exchange
    datetime: datetime

    interval: Interval = None
    volume: float = 0
    turnover: float = 0
    open_interest: float = 0
    open_price: float = 0
    high_price: float = 0
    low_price: float = 0
    close_price: float = 0

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"


@dataclass(eq=bool)
class OrderData(BaseData):
    """
    Order data contains information for tracking lastest status
    of a specific order.
    """

    symbol: str
    exchange: Exchange
    orderid: str

    type: OrderType = OrderType.LIMIT
    direction: Direction = None
    offset: Offset = Offset.NONE
    signal_price: float = None              # 信号价格, 一般是last_price
    price: float = None                     # 限价
    backtest_price: float = 0               # 回测理论成交价
    volume: float = 0
    traded: float = 0
    status: Status = Status.SUBMITTING
    datetime: datetime = None
    reference: str = ""

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"
        self.vt_orderid = f"{self.gateway_name}.{self.orderid}"
        self.reference = f"{self.gateway_name}.{self.orderid}"

    def is_active(self) -> bool:
        """
        Check if the order is active.
        """
        if self.status in ACTIVE_STATUSES:
            return True
        else:
            return False

    def create_cancel_request(self) -> "CancelRequest":
        """
        Create cancel request object from order.
        """
        req = CancelRequest(
            orderid=self.orderid, symbol=self.symbol, exchange=self.exchange,
            reference=self.reference
        )
        return req


@dataclass
class TradeData(BaseData):
    """
    Trade data contains information of a fill of an order. One order
    can have several trade fills.
    """

    symbol: str
    exchange: Exchange
    orderid: str
    tradeid: str
    direction: Direction = None
    offset: Offset = Offset.NONE
    signal_price: float = 0                 # 产生信号的价格
    limit_price: float = 0                  # 委托价，限价
    price: float = 0                        # 成交价
    slippage: float = 0                     # 滑点
    backtest_price: float = 0               # 回测理论成交价
    backtest_real_slippage: float = 0       # 实盘与回测的误差
    volume: float = 0
    datetime: datetime = None

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"
        self.vt_orderid = f"{self.gateway_name}.{self.orderid}"
        self.vt_tradeid = f"{self.gateway_name}.{self.tradeid}"
        try:
            self.slippage = self.signal_price - self.price
        except Exception:
            pass
        self.backtest_real_slippage = self.backtest_price - self.price
        if self.direction == Direction.SHORT:
            self.slippage = -self.slippage
            self.backtest_real_slippage = -self.backtest_real_slippage


@dataclass(eq=True)
class PositionData(BaseData):
    """
    Positon data is used for tracking each individual position holding.
    """

    symbol: str

    exchange: Exchange
    direction: Direction
    product: Product = Product.OTHERS
    volume: float = 0
    frozen: float = 0
    price: float = 0
    pnl: float = 0
    yd_volume: float = 0
    author_id: int = 0
    strategy_id: int = 0
    sell_able: int = 0                  # 可卖数量
    purchase_able: int = 0              # 可申赎数量(股票是可申购、如果是ETF，就是可赎回)

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"
        self.vt_positionid = f"{self.vt_symbol}.{self.product.name}.{self.direction.name}"


@dataclass
class AccountData(BaseData):
    """
    Account data contains information about balance, frozen and
    available.
    """

    accountid: str

    balance: float = 0
    frozen: float = 0
    currency: Currency = Currency.CNY

    def __post_init__(self):
        """"""
        self.available = self.balance - self.frozen
        self.vt_accountid = f"{self.gateway_name}.{self.currency.value}.{self.accountid}"


@dataclass
class LogData(BaseData):
    """
    Log data is used for recording log messages on GUI or in log files.
    """

    msg: str
    level: int = INFO
    author_name: str = None
    author_id: str = None
    strategy_id: str = None
    strategy_name: str = None

    def __post_init__(self):
        """"""
        self.time = datetime.now()


@dataclass(unsafe_hash=True)
class ContractData(BaseData):
    """
    Contract data contains basic information about each contract traded.
    """

    symbol: str
    exchange: Exchange
    name: str
    product: Product
    size: float
    pricetick: float

    min_volume: float = 1           # minimum trading volume of the contract
    stop_supported: bool = False    # whether server supports stop order
    net_position: bool = False      # whether gateway uses net position volume
    history_data: bool = False      # whether gateway provides bar history data

    option_strike: float = 0
    option_underlying: str = ""     # vt_symbol of underlying contract
    option_type: OptionType = None
    option_expiry: datetime = None
    option_portfolio: str = ""
    option_index: str = ""          # for identifying options with same strike price

    etf_purchase_redem: str = ""         # ETF申赎代码
    etf_purchase_redem_min: str = 0      # ETF申赎最小数量

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"


@dataclass
class QuoteData(BaseData):
    """
    Quote data contains information for tracking lastest status
    of a specific quote.
    """

    symbol: str
    exchange: Exchange
    quoteid: str

    bid_price: float = 0.0
    bid_volume: int = 0
    ask_price: float = 0.0
    ask_volume: int = 0
    bid_offset: Offset = Offset.NONE
    ask_offset: Offset = Offset.NONE
    status: Status = Status.SUBMITTING
    datetime: datetime = None
    reference: str = ""

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"
        self.vt_quoteid = f"{self.gateway_name}.{self.quoteid}"

    def is_active(self) -> bool:
        """
        Check if the quote is active.
        """
        return self.status in ACTIVE_STATUSES

    def create_cancel_request(self) -> "CancelRequest":
        """
        Create cancel request object from quote.
        """
        req = CancelRequest(
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

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"


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
    signal_price: float = 0
    offset: Offset = Offset.NONE
    reference: str = ""

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"

    def create_order_data(self, orderid: str, gateway_name: str) -> OrderData:
        """
        Create order data from request.
        """
        order = OrderData(
            symbol=self.symbol,
            exchange=self.exchange,
            orderid=orderid,
            type=self.type,
            direction=self.direction,
            offset=self.offset,
            price=self.price,
            signal_price=self.signal_price,
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
    reference: str = None

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"


@dataclass
class HistoryRequest:
    """
    Request sending to specific gateway for querying history data.
    """

    symbol: str
    exchange: Exchange
    start: datetime
    end: datetime = None
    interval: Interval = None

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"


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

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"

    def create_quote_data(self, quoteid: str, gateway_name: str) -> QuoteData:
        """
        Create quote data from request.
        """
        quote = QuoteData(
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


@dataclass
class BasketComponent(BaseData):
    basket_name: str
    symbol: str
    exchange: Exchange
    name: str
    share: int                              # 成分数量
    premium_ratio: float                    # 溢价比例
    cash_substitute: float                  # 替代总额
    redemption_cash_substitute: float       # 赎回替代金额;对于跨境 ETF、跨市场 ETF、黄金 ETF 和现金债券 ETF，
    # 该字段为 0.0000;此字段只有当替代标志为‘2’时才有效.

    substitute_flag: int = 1                # 现金替代标志
    # 0 表示该证券为沪市证券，禁止现金替代（必须有证券）
    # 1 表示该证券为沪市证券，可以进行现金替代（先用证券，证券不足的话用现金替代）
    # 2 表示该证券为沪市证券，必须用现金替代。
    # 3 表示该证券为深市证券，退补现金替代。
    # 4 表示该证券为深市证券，必须现金替代。
    # 5 表示非沪深市场成分证券退补现金替代。
    # 6 表示非沪深市场成份证券必须现金替代。

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"

    def cash_flag(self):
        flg = int(self.substitute_flag)
        if flg in (0, ):
            return 0  # 禁止
        elif flg in (1, 3, 5):
            return 1  # 可以
        else:
            return 2  # 必须