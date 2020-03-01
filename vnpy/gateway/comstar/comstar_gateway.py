from datetime import datetime
from typing import Sequence

from vnpy.api.comstar import TdApi
from vnpy.event import EventEngine
from vnpy.trader.constant import Exchange, Product, Offset, OrderType, Direction, Status
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    SubscribeRequest,
    CancelRequest,
    OrderRequest,
    ContractData, TickData, OrderData, TradeData, LogData)


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
        self.symbol_gateway_map = {}
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
        gateway_name = self.symbol_gateway_map.get(req.vt_symbol, "")
        data = vn_encode(req)
        # 清算速度
        data['settle_type'] = 'T1'
        self.api.subscribe(data, gateway_name)

    def send_order(self, req: OrderRequest):
        """"""
        gateway_name = self.symbol_gateway_map.get(req.vt_symbol, "")
        data = vn_encode(req)
        # 清算速度
        data['settle_type'] = 'T1'
        # 策略名称
        data['strategy_name'] = ''
        # 1表示阻塞, 0非阻塞
        return self.api.send_order(data, gateway_name, blocks=1)

    def cancel_order(self, req: CancelRequest):
        """"""
        gateway_name = self.symbol_gateway_map.get(req.vt_symbol, "")
        data = vn_encode(req)
        self.api.cancel_order(data, gateway_name)

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
    TdApi的一个具体实现，结合gateway重写了回调函数
    """

    def __init__(self, gateway):
        """Constructor"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

    def on_tick(self, tick: dict):
        data = parse_tick(tick)
        self.gateway.on_tick(data)

    def on_order(self, order: dict):
        data = parse_order(order)
        self.gateway.on_order(data)

    def on_trade(self, trade: dict):
        data = parse_trade(trade)
        self.gateway.on_trade(data)

    def on_log(self, log: dict):
        data = LogData(
            msg=log['msg'],
            level=log['level'],
            gateway_name=log['gateway_name']
        )
        data.time = parse_datetime(log['time'])
        self.gateway.on_log(data)

    def on_login(self, data: dict):
        if data['status']:
            self.gateway.query_all()
            self.gateway.write_log("服务器登录成功")
        else:
            self.gateway.write_log("服务器登录失败")

    def on_disconnected(self, reason: str):
        self.gateway.write_log(reason)

    def on_all_contracts(self, contracts: Sequence[dict]):
        for data in contracts:
            contract = parse_contract(data)
            self.gateway.symbol_gateway_map[contract.vt_symbol] = contract.gateway_name
            contract.gateway_name = self.gateway_name
            self.gateway.on_contract(contract)
        self.gateway.write_log("合约信息查询成功")

    def on_all_orders(self, orders: Sequence[dict]):
        for data in orders:
            order = parse_order(data)
            order.gateway_name = self.gateway_name
            self.gateway.on_order(order)
        self.gateway.write_log("委托信息查询成功")

    def on_all_trades(self, trades: Sequence[dict]):
        for data in trades:
            trade = parse_trade(data)
            trade.gateway_name = self.gateway_name
            self.gateway.on_trade(trade)
        self.gateway.write_log("成交信息查询成功")

    def on_auth(self, status: bool):
        if status:
            self.gateway.write_log("服务器授权验证成功")
        else:
            self.gateway.write_log("服务器授权验证失败")


def parse_tick(data: dict) -> TickData:
    """
    从api收到的data里解析出TickData
    Xbond 行情第1档是公有最优行情，第2至6档是私有行情
    因为TickData只有5档行情, 所以没有填充最后一档私有行情
    """
    tick = TickData(
        symbol=data['symbol'],
        exchange=enum_decode(data['exchange']),
        datetime=parse_datetime(data['datetime']),
        name=data['name'],
        volume=float(data['volume']),
        last_price=float(data['last_price']),
        open_price=float(data['open_price']),
        high_price=float(data['high_price']),
        low_price=float(data['low_price']),
        pre_close=float(data['pre_close']),
        bid_price_1=float(data['bid_price_1']),
        bid_price_2=float(data['bid_price_2']),
        bid_price_3=float(data['bid_price_3']),
        bid_price_4=float(data['bid_price_4']),
        bid_price_5=float(data['bid_price_5']),
        ask_price_1=float(data['ask_price_1']),
        ask_price_2=float(data['ask_price_2']),
        ask_price_3=float(data['ask_price_3']),
        ask_price_4=float(data['ask_price_4']),
        ask_price_5=float(data['ask_price_5']),
        bid_volume_1=float(data['bid_volume_1']),
        bid_volume_2=float(data['bid_volume_2']),
        bid_volume_3=float(data['bid_volume_3']),
        bid_volume_4=float(data['bid_volume_4']),
        bid_volume_5=float(data['bid_volume_5']),
        ask_volume_1=float(data['ask_volume_1']),
        ask_volume_2=float(data['ask_volume_2']),
        ask_volume_3=float(data['ask_volume_3']),
        ask_volume_4=float(data['ask_volume_4']),
        ask_volume_5=float(data['ask_volume_5']),
        gateway_name=data['gateway_name']
    )
    return tick


def parse_order(data: dict) -> OrderData:
    """
    从api收到的data里解析出OrderData
    """
    order = OrderData(
        symbol=data['symbol'],
        exchange=enum_decode(data['exchange']),
        orderid=data['orderid'],
        type=enum_decode(data['type']),
        direction=enum_decode(data['direction']),
        price=float(data['price']),
        volume=float(data['volume']),
        traded=float(data['traded']),
        status=enum_decode(data['status']),
        time=data['time'],
        gateway_name=data['gateway_name']
    )
    return order


def parse_trade(data: dict) -> TradeData:
    """
    从api收到的data里解析出TradeData
    """
    trade = TradeData(
        symbol=data['symbol'],
        exchange=enum_decode(data['exchange']),
        orderid=data['orderid'],
        tradeid=data['tradeid'],
        direction=enum_decode(data['direction']),
        price=float(data['price']),
        volume=float(data['volume']),
        time=data['time'],
        gateway_name=data['gateway_name']
    )
    return trade


def parse_contract(data: dict) -> ContractData:
    """
    从api收到的data里解析出ContractData
    """
    contract = ContractData(
        symbol=data['symbol'],
        exchange=enum_decode(data['exchange']),
        name=data['name'],
        product=enum_decode(data['product']),
        size=int(data['size']),
        pricetick=float(data['pricetick']),
        min_volume=float(data['min_volume']),
        gateway_name=data['gateway_name']
    )
    return contract


def parse_datetime(s: str) -> datetime:
    if "." in s:
        return datetime.strptime(s, "%Y%m%d %H:%M:%S.%f")
    elif len(s) > 0:
        return datetime.strptime(s, "%Y%m%d %H:%M:%S")
    else:
        return datetime.now()


VN_ENUMS = {
    'Exchange': Exchange, 'Product': Product, 'Offset': Offset, 'OrderType': OrderType,
    'Direction': Direction, 'Status': Status
}


def enum_decode(s: str):
    """
    从字符串解析成VN_ENUMS里的enum
    """
    name, member = s.split(".")
    return getattr(VN_ENUMS[name], member)


def vn_encode(obj: object) -> str or dict:
    """
    将类变成json格式
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
