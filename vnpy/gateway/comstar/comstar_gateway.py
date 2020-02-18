import json
import types
from datetime import datetime
from typing import Any, Type

from vnpy.api.comstar import TdApi
from vnpy.event import EventEngine
from vnpy.trader.constant import Exchange, Product, Offset, OrderType, Direction, Status
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    SubscribeRequest,
    CancelRequest,
    OrderRequest,
    ContractData, TickData, OrderData, TradeData)


class ComstarGateway(BaseGateway):
    """
    VN Trader Gateway for Cfets  service.
    """
    default_setting = {
        "交易服务器": "",
        "用户名": "",
        "密码": "",
        "Key": ""
    }

    exchanges = [Exchange.IBE]

    def __init__(self, event_engine: EventEngine):
        """Constructor"""
        super().__init__(event_engine, "CFETS")

        self.symbol_gateway_map = {}
        self.orders = {}
        self.requests = {}

        self.api = TdApi()
        self.api.callback = self.api_callback

    def connect(self, setting: dict):
        """"""
        td_address = setting["交易服务器"]
        username = setting["用户名"]
        password = setting["密码"]
        key = setting["Key"]

        if self.api.connect(username, password, key, td_address):
            self.write_log("服务器连接成功")
            self.query_all()
        else:
            self.write_log("服务器连接失败")

    def subscribe(self, req: SubscribeRequest):
        """"""
        gateway_name = self.symbol_gateway_map.get(req.vt_symbol, "")
        self.api.subscribe(req, gateway_name)

    def send_order(self, req: OrderRequest):
        """"""
        gateway_name = self.symbol_gateway_map.get(req.vt_symbol, "")
        # 1表示阻塞, 0非阻塞
        return self.api.send_order(req, gateway_name, blocks=1)

    def cancel_order(self, req: CancelRequest):
        """"""
        gateway_name = self.symbol_gateway_map.get(req.vt_symbol, "")
        self.api.cancel_order(req, gateway_name)

    def query_account(self):
        """"""
        pass

    def query_position(self):
        """"""
        pass

    def query_all(self):
        """"""
        contracts = self.api.get_all_contracts(blocks=1)
        for contract in contracts:
            contract = vn_decoder(contract, ContractData)
            self.symbol_gateway_map[contract.vt_symbol] = contract.gateway_name
            contract.gateway_name = self.gateway_name
            self.on_contract(contract)
        self.write_log("合约信息查询成功")

        orders = self.api.get_all_orders(blocks=1)
        for order in orders:
            order = vn_decoder(order, OrderData)
            order.gateway_name = self.gateway_name
            self.on_order(order)
        self.write_log("委托信息查询成功")

        trades = self.api.get_all_trades(blocks=1)
        for trade in trades:
            trade = vn_decoder(trade, TradeData)
            trade.gateway_name = self.gateway_name
            self.on_trade(trade)
        self.write_log("成交信息查询成功")

    def close(self):
        """"""
        self.api.close()

    def api_callback(self, topic: str, data: Any):
        """"""
        if topic == 'on_tick':
            data = vn_decoder(data, TickData)
            self.on_tick(data)
        elif topic == 'on_order':
            data = vn_decoder(data, OrderData)
            self.on_order(data)
        elif topic == 'on_trade':
            data = vn_decoder(data, TradeData)
            self.on_trade(data)
        else:
            print("Not implemented: ", topic, data)


def revise(data):
    # 先修数
    if hasattr(data, "exchange"):
        data.exchange = enum_decoder(data.exchange)
    if hasattr(data, "product"):
        data.product = enum_decoder(data.product)
    if hasattr(data, "offset"):
        data.offset = enum_decoder(data.offset)
    if hasattr(data, "type"):
        data.type = enum_decoder(data.type)
    if hasattr(data, "direction"):
        data.direction = enum_decoder(data.direction)
    if hasattr(data, "datetime"):
        data.datetime = get_time(data.datetime)
    if hasattr(data, "status"):
        data.status = enum_decoder(data.status)
        # 替换类实例的方法
        data.is_active = types.MethodType(OrderData.is_active, data)
    return data


VN_ENUMS = {
    'Exchange': Exchange, 'Product': Product, 'Offset': Offset, 'OrderType': OrderType,
    'Direction': Direction, 'Status': Status
}


def enum_decoder(s: str):
    name, member = s.split(".")
    return getattr(VN_ENUMS[name], member)


def __init__(self, d: dict):
    self.__dict__ = d


# 将json(或dict)格式转成指定的类
def vn_decoder(d: dict, clz: Type):
    before = clz.__init__
    clz.__init__ = __init__
    obj = json.loads(json.dumps(d), object_hook=clz)
    clz.__init__ = before
    # 修数
    return revise(obj)


def get_time(s: str):
    if "." in s:
        hms, r = s.split(".")
        return datetime.strptime(hms, "%Y%m%d %H:%M:%S")
    else:
        return None
