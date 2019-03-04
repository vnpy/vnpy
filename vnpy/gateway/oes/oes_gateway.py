# encoding: UTF-8
"""
"""
import hashlib
import os

from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (AccountData, CancelRequest, ContractData, OrderData, OrderRequest,
                                PositionData, SubscribeRequest, TickData, TradeData)
from vnpy.trader.utility import get_file_path
from .md import OesMdApi
from .td import OesTdApi
from .utils import config_template


class OesGateway(BaseGateway):
    """
    VN Trader Gateway for BitMEX connection.
    """

    def on_tick(self, tick: TickData):
        super().on_tick(tick)

    def on_trade(self, trade: TradeData):
        super().on_trade(trade)

    def on_order(self, order: OrderData):
        super().on_order(order)

    def on_position(self, position: PositionData):
        super().on_position(position)

    def on_account(self, account: AccountData):
        super().on_account(account)

    def on_contract(self, contract: ContractData):
        super().on_contract(contract)

    default_setting = {
        "td_ord_server": "tcp://106.15.58.119:6101",
        "td_rpt_server": "tcp://106.15.58.119:6301",
        "td_qry_server": "tcp://106.15.58.119:6401",
        "md_tcp_server": "tcp://139.196.228.232:5103",
        "md_qry_server": "tcp://139.196.228.232:5203",
        "username": "",
        "password": "",
    }

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "OES")

        self.md_api = OesMdApi(self)
        self.td_api = OesTdApi(self)

    def connect(self, setting: dict):
        """"""
        if not setting['password'].startswith("md5:"):
            setting['password'] = "md5:" + hashlib.md5(setting['password'].encode()).hexdigest()

        config_path = get_file_path("vnoes.ini")
        with open(config_path, "wt") as f:
            if 'test' in setting:
                log_level = 'DEBUG'
                log_mode = 'console'
            else:
                log_level = 'WARNING'
                log_mode = 'file'
            log_dir = get_file_path('oes')
            log_path = os.path.join(log_dir, 'log.log')
            if os.path.exists(log_dir):
                os.mkdir(log_dir)
            content = config_template.format(**setting,
                                             log_level=log_level,
                                             log_mode=log_mode,
                                             log_path=log_path)
            f.write(content)

        self.td_api.connect(str(config_path))
        self.td_api.query_account()
        self.td_api.query_contracts()
        self.td_api.query_position()
        self.td_api.init_query_orders()
        self.td_api.start()

        self.md_api.connect(str(config_path))
        self.md_api.start()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.md_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.td_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        return self.td_api.cancel_order(req)

    def query_account(self):
        """"""
        return self.td_api.query_account()

    def query_position(self):
        """"""
        return self.query_position()

    def close(self):
        """"""
        self.md_api.stop()
        self.td_api.stop()
        pass
