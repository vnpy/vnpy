from datetime import datetime
from typing import Optional, Sequence, Dict
from enum import Enum

from vnpy.event import EventEngine
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.constant import (
    Exchange,
    Product,
    Offset,
    OrderType,
    Direction,
    Status
)
from vnpy.trader.object import (
    SubscribeRequest,
    CancelRequest,
    OrderRequest,
    ContractData,
    TickData,
    OrderData,
    TradeData,
    LogData
)

from .comstar_api import TdApi

VN_ENUMS = {
    "Exchange": Exchange,
    "Product": Product,
    "Offset": Offset,
    "OrderType": OrderType,
    "Direction": Direction,
    "Status": Status
}


class ComstarGateway(BaseGateway):
    """
    VN Trader Gateway for Comstar service.
    """

    default_setting = {
        "交易服务器": "",
        "用户名": "",
        "密码": "",
        "Key": ""
    }

    exchanges = [Exchange.CFETS]

    def __init__(self, event_engine: EventEngine):
        """Constructor"""
        super().__init__(event_engine, "COMSTAR")
        self.api = UserApi(self)

    def connect(self, setting: dict):
        """"""
        td_address = setting["交易服务器"]
        username = setting["用户名"]
        password = setting["密码"]
        key = setting["Key"]

        self.api.connect(username, password, key, td_address)

    def subscribe(self, req: SubscribeRequest):
        """"""
        # Symbol format: 180406_T0 or 180406_T1
        symbol, settle_type, *_ = req.symbol.split("_") + [""]
        if settle_type not in {"T0", "T1"}:
            self.write_log("请输入清算速度T0或T1")
            return ""

        data = vn_encode(req)
        data["symbol"] = symbol
        data["settle_type"] = settle_type
        self.api.subscribe(data, self.gateway_name)

    def send_order(self, req: OrderRequest):
        """"""
        # Offset is not supported for Comstar gateawy
        req.offset = Offset.NONE

        if req.type not in {OrderType.LIMIT, OrderType.FAK}:
            self.write_log("仅支持限价单和FAK单")
            return ""

        symbol, settle_type, *_ = req.symbol.split("_") + [""]
        if settle_type not in {"T0", "T1"}:
            self.write_log("请输入清算速度T0或T1")
            return ""

        data = vn_encode(req)
        data["symbol"] = symbol
        data["settle_type"] = settle_type
        data["strategy_name"] = data.pop("reference")

        order_id = self.api.send_order(data, self.gateway_name)
        # convert to vt_orderid
        return f"{self.gateway_name}.{order_id}"

    def cancel_order(self, req: CancelRequest):
        """"""
        data = vn_encode(req)
        symbol, settle_type, *_ = req.symbol.split("_") + [""]
        data["symbol"] = symbol
        data["settle_type"] = settle_type
        self.api.cancel_order(data, self.gateway_name)

    def query_account(self):
        """"""
        pass

    def query_position(self):
        """"""
        pass

    def query_all(self):
        """"""
        self.api.get_all_contracts()
        self.api.get_all_orders()
        self.api.get_all_trades()

    def close(self):
        """"""
        self.api.close()


class UserApi(TdApi):
    """
    Implements Comstar API.
    """

    def __init__(self, gateway: ComstarGateway):
        """Constructor"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.trades: Dict[str, TradeData] = {}
        self.orders: Dict[str, OrderData] = {}

    def on_tick(self, tick: dict):
        """"""
        data = parse_tick(tick)
        self.gateway.on_tick(data)

    def on_order(self, order: dict):
        """"""
        data = parse_order(order)

        # Filter duplicated order data push after reconnect
        last_order = self.orders.get(data.vt_orderid, None)
        if (
            last_order
            and data.traded == last_order.traded
            and data.status == last_order.status
        ):
            return
        self.orders[data.vt_orderid] = data

        self.gateway.on_order(data)

    def on_trade(self, trade: dict):
        """"""
        data = parse_trade(trade)

        # Filter duplicated trade data push after reconnect
        if data.vt_tradeid in self.trades:
            return
        self.trades[data.vt_tradeid] = data

        self.gateway.on_trade(data)

    def on_log(self, log: dict):
        data = parse_log(log)
        self.gateway.on_log(data)

    def on_login(self, data: dict):
        """"""
        if data["status"]:
            self.gateway.query_all()
            self.gateway.write_log("服务器登录成功")
        else:
            self.gateway.write_log("服务器登录失败")

    def on_disconnected(self, reason: str):
        """"""
        self.gateway.write_log(reason)

    def on_all_contracts(self, contracts: Sequence[dict]):
        """"""
        for data in contracts:
            for settle_type in ("T0", "T1"):
                contract = parse_contract(data, settle_type)
                contract.gateway_name = self.gateway_name
                self.gateway.on_contract(contract)

        self.gateway.write_log("合约信息查询成功")

    def on_all_orders(self, orders: Sequence[dict]):
        """"""
        for data in orders:
            order = parse_order(data)
            order.gateway_name = self.gateway_name
            self.gateway.on_order(order)

        self.gateway.write_log("委托信息查询成功")

    def on_all_trades(self, trades: Sequence[dict]):
        """"""
        for data in trades:
            trade = parse_trade(data)
            trade.gateway_name = self.gateway_name
            self.gateway.on_trade(trade)

        self.gateway.write_log("成交信息查询成功")

    def on_auth(self, status: bool):
        """"""
        if status:
            self.gateway.write_log("服务器授权验证成功")
        else:
            self.gateway.write_log("服务器授权验证失败")


def parse_tick(data: dict) -> TickData:
    """
    Convert json received from API to TickData object.

    XBond Depth Data Notice:
    1. Bid/Ask1 are public best price.
    2. Bid/Ask2-6 are private price data.
    """
    tick = TickData(
        symbol=f"{data['symbol']}_{data['settle_type']}",
        exchange=enum_decode(data["exchange"]),
        datetime=parse_datetime(data["datetime"]),
        name=data["name"],
        volume=float(data["volume"]),
        last_price=float(data["last_price"]),
        open_price=float(data["open_price"]),
        high_price=float(data["high_price"]),
        low_price=float(data["low_price"]),
        pre_close=float(data["pre_close"]),
        bid_price_1=float(data["bid_price_1"]),
        bid_price_2=float(data["bid_price_2"]),
        bid_price_3=float(data["bid_price_3"]),
        bid_price_4=float(data["bid_price_4"]),
        bid_price_5=float(data["bid_price_5"]),
        ask_price_1=float(data["ask_price_1"]),
        ask_price_2=float(data["ask_price_2"]),
        ask_price_3=float(data["ask_price_3"]),
        ask_price_4=float(data["ask_price_4"]),
        ask_price_5=float(data["ask_price_5"]),
        bid_volume_1=float(data["bid_volume_1"]),
        bid_volume_2=float(data["bid_volume_2"]),
        bid_volume_3=float(data["bid_volume_3"]),
        bid_volume_4=float(data["bid_volume_4"]),
        bid_volume_5=float(data["bid_volume_5"]),
        ask_volume_1=float(data["ask_volume_1"]),
        ask_volume_2=float(data["ask_volume_2"]),
        ask_volume_3=float(data["ask_volume_3"]),
        ask_volume_4=float(data["ask_volume_4"]),
        ask_volume_5=float(data["ask_volume_5"]),
        gateway_name=data["gateway_name"]
    )
    return tick


def parse_order(data: dict) -> OrderData:
    """
    Convert json received from API to OrderData object.
    """
    order = OrderData(
        symbol=f"{data['symbol']}_{data['settle_type']}",
        exchange=enum_decode(data["exchange"]),
        orderid=data["orderid"],
        type=enum_decode(data["type"]),
        direction=enum_decode(data["direction"]),
        offset=Offset.NONE,
        price=float(data["price"]),
        volume=float(data["volume"]),
        traded=float(data["traded"]),
        status=enum_decode(data["status"]),
        time=data["time"],
        gateway_name=data["gateway_name"]
    )
    return order


def parse_trade(data: dict) -> TradeData:
    """
    Convert json received from API to TradeData object.
    """
    trade = TradeData(
        symbol=f"{data['symbol']}_{data['settle_type']}",
        exchange=enum_decode(data["exchange"]),
        orderid=data["orderid"],
        tradeid=data["tradeid"],
        direction=enum_decode(data["direction"]),
        offset=Offset.NONE,
        price=float(data["price"]),
        volume=float(data["volume"]),
        time=data["time"],
        gateway_name=data["gateway_name"]
    )
    return trade


def parse_contract(data: dict, settle_type: str) -> ContractData:
    """
    Convert json received from API to ContractData object.
    """
    contract = ContractData(
        symbol=f"{data['symbol']}_{settle_type}",
        exchange=enum_decode(data["exchange"]),
        name=data["name"],
        product=enum_decode(data["product"]),
        size=int(data["size"]),
        pricetick=float(data["pricetick"]),
        min_volume=float(data["min_volume"]),
        gateway_name=data["gateway_name"]
    )
    return contract


def parse_log(data: dict) -> LogData:
    """
    从api收到的data里解析出LogData
    """
    log = LogData(
        msg=data["msg"],
        level=data["level"],
        gateway_name=data["gateway_name"]
    )
    log.time = parse_datetime(data["time"])
    return log


def parse_datetime(s: str) -> datetime:
    if "." in s:
        return datetime.strptime(s, "%Y%m%d %H:%M:%S.%f")
    elif len(s) > 0:
        return datetime.strptime(s, "%Y%m%d %H:%M:%S")
    else:
        return datetime.now()


def enum_decode(s: str) -> Optional[Enum]:
    """
    Convert string into vn.py constant enum.
    """
    if "." in s:
        name, member = s.split(".")
        return getattr(VN_ENUMS[name], member)
    else:
        return None


def vn_encode(obj: object) -> str or dict:
    """
    Convert vn.py object into json format.
    """
    if type(obj) in VN_ENUMS.values():
        return str(obj)
    else:
        s = {}
        for (k, v) in obj.__dict__.items():
            if type(v) in VN_ENUMS.values():
                s[k] = vn_encode(v)
            else:
                s[k] = str(v)
        return s
