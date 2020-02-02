"""
Basic data structure used for general trading function in VN Trader.
"""

from dataclasses import dataclass
from datetime import datetime
from logging import INFO

from .constant import Direction, Exchange, Interval, Offset, Status, Product, OptionType, OrderType

ACTIVE_STATUSES = set([Status.SUBMITTING, Status.NOTTRADED, Status.PARTTRADED, Status.CANCELLING])


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
    date: str = ""  # '%Y-%m-%d'
    time: str = ""  # '%H:%M:%S.%f'
    trading_day: str = ""  # '%Y-%m-%d'

    name: str = ""
    volume: float = 0
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
    datetime: datetime  # bar的开始时间
    trading_day: str = ""  # '%Y-%m-%d'

    interval: Interval = None  # constant.py Internal 1m, 1h, 1d, 1w .etc
    volume: float = 0
    open_interest: float = 0
    open_price: float = 0
    high_price: float = 0
    low_price: float = 0
    close_price: float = 0

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"


@dataclass
class RenkoBarData(BarData):
    """
    Renko bar data of a certain trading period.
    """
    seconds: int = 0  # 当前Bar的秒数（针对RenkoBar)
    high_seconds: int = -1  # 当前Bar的上限秒数
    low_seconds: int = -1  # 当前bar的下限秒数
    height: float = 3  # 当前Bar的高度限制（针对RenkoBar和RangeBar类）
    up_band: float = 0  # 高位区域的基线
    down_band: float = 0  # 低位区域的基线
    low_time = None  # 最后一次进入低位区域的时间
    high_time = None  # 最后一次进入高位区域的时间


@dataclass
class OrderData(BaseData):
    """
    Order data contains information for tracking lastest status
    of a specific order.
    """

    symbol: str
    exchange: Exchange
    orderid: str
    sys_orderid: str = ""

    type: OrderType = OrderType.LIMIT
    direction: Direction = ""
    offset: Offset = Offset.NONE
    price: float = 0
    volume: float = 0
    traded: float = 0
    status: Status = Status.SUBMITTING
    time: str = ""
    cancel_time: str = ""

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"
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
            orderid=self.orderid, symbol=self.symbol, exchange=self.exchange
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
    sys_orderid: str = ""

    direction: Direction = ""

    offset: Offset = Offset.NONE
    price: float = 0
    volume: float = 0
    time: str = ""
    datetime: datetime = None
    strategy_name: str = ""  # 策略名

    # 股票使用
    trade_amount: float = 0  # 成交金额
    commission: float = 0  # 手续费(印花税+佣金+过户费）
    holder_id: str = ""  # 股东代码
    comment: str = ""  # 备注

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"
        self.vt_orderid = f"{self.gateway_name}.{self.orderid}"
        self.vt_tradeid = f"{self.gateway_name}.{self.tradeid}"


@dataclass
class PositionData(BaseData):
    """
    Positon data is used for tracking each individual position holding.
    """

    symbol: str
    exchange: Exchange
    direction: Direction

    volume: float = 0
    frozen: float = 0
    price: float = 0
    pnl: float = 0
    yd_volume: float = 0

    # 股票相关
    holder_id: str = ""  # 股东代码

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"
        self.vt_positionid = f"{self.gateway_name}.{self.vt_symbol}.{self.direction.value}"


@dataclass
class AccountData(BaseData):
    """
    Account data contains information about balance, frozen and
    available.
    """

    accountid: str
    pre_balance: float = 0  # 昨净值
    balance: float = 0  # 当前净值
    frozen: float = 0  # 冻结资金
    currency: str = ""  # 币种
    commission: float = 0  # 手续费
    margin: float = 0  # 使用保证金
    close_profit: float = 0  # 平仓盈亏
    holding_profit: float = 0  # 持仓盈亏
    trading_day: str = ""  # 当前交易日

    def __post_init__(self):
        """"""
        self.available = self.balance - self.frozen
        self.vt_accountid = f"{self.gateway_name}.{self.accountid}"


@dataclass
class VtFundsFlowData(BaseData):
    """历史资金流水数据类(股票专用）"""

    # 账号代码相关
    accountid: str  # 账户代码
    exchange: Exchange = None

    currency: str = ""  # 币种
    trade_date: str = ""  # 成交日期
    trade_price: float = 0  # 成交价格
    trade_volume: float = 0  # 成交数量
    trade_amount: float = 0  # 发生金额( 正数代表卖出，或者转入资金，获取分红等，负数代表买入股票或者出金)
    fund_remain: float = 0  # 资金余额
    contract_id: str = ""  # 合同编号
    business_name: str = ""  # 业务名称
    symbol: str = ""  # 合约代码（证券代码）
    holder_id: str = ""  # 股东代码
    direction: str = ""  # 买卖类别：转,买，卖..
    comment: str = ""  # 备注

    def __post_init__(self):
        if self.exchange:
            self.vt_symbol = f"{self.symbol}.{self.exchange.value}"
        else:
            self.vt_symbol = self.symbol

        self.vt_accountid = f"{self.gateway_name}.{self.accountid}"


@dataclass
class LogData(BaseData):
    """
    Log data is used for recording log messages on GUI or in log files.
    """

    msg: str
    level: int = INFO
    additional_info: str = ""

    def __post_init__(self):
        """"""
        self.time = datetime.now()


@dataclass
class ContractData(BaseData):
    """
    Contract data contains basic information about each contract traded.
    """

    symbol: str
    exchange: Exchange
    name: str
    product: Product
    size: int
    pricetick: float
    margin_rate: float = 0.1  # 保证金比率

    min_volume: float = 1  # minimum trading volume of the contract
    stop_supported: bool = False  # whether server supports stop order
    net_position: bool = False  # whether gateway uses net position volume
    history_data: bool = False  # whether gateway provides bar history data

    option_strike: float = 0
    option_underlying: str = ""  # vt_symbol of underlying contract
    option_type: OptionType = None
    option_expiry: datetime = None

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"


@dataclass
class SubscribeRequest:
    """
    Request sending to specific gateway for subscribing tick/bar data update.
    """

    symbol: str
    exchange: Exchange
    is_bar: bool = False

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"

    def __eq__(self, other):
        return self.vt_symbol == other.vt_symbol


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
    offset: Offset = Offset.NONE

    def __post_init__(self):
        """"""
        self.vt_symbol = f"{self.symbol}.{self.exchange.value}"

    def create_order_data(self, orderid: str, gateway_name: str):
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
            volume=self.volume,
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
