"""
author: nanoric

TODO:
 * Linux support

"""
from vnpy.api.tora.vntora import (
    AsyncDispatchException, set_async_callback_exception_handler)

from vnpy.event import EventEngine
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (CancelRequest, OrderRequest, SubscribeRequest)
from .constant import EXCHANGE_VT2TORA
from .md import ToraMdApi
from .td import ToraTdApi


def is_valid_front_address(address: str):
    return address.startswith("tcp://") or address.startswith("udp://")


class ToraGateway(BaseGateway):
    """"""

    default_setting = {
        "账号": "",
        "密码": "",
        "交易服务器": "",
        "行情服务器": "",
    }

    exchanges = list(EXCHANGE_VT2TORA.keys())

    def __init__(self, event_engine: EventEngine):
        """"""
        super().__init__(event_engine, "TORA")

        self._md_api = ToraMdApi(self)
        self._td_api = ToraTdApi(self)

        set_async_callback_exception_handler(
            self._async_callback_exception_handler)

    def connect(self, setting: dict):
        """"""
        username = setting['账号']
        password = setting['密码']
        td_address = setting["交易服务器"]
        md_address = setting["行情服务器"]

        if not is_valid_front_address(td_address):
            td_address = "tcp://" + td_address
        if not is_valid_front_address(md_address):
            md_address = "tcp://" + md_address

        self._md_api.username = username
        self._md_api.password = password
        self._md_api.md_address = md_address
        self._md_api.connect()

        self._td_api.username = username
        self._td_api.password = password
        self._td_api.td_address = td_address
        self._td_api.connect()

    def close(self):
        """"""
        self._md_api.stop()
        self._td_api.stop()
        self._md_api.join()
        self._td_api.join()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self._md_api.subscribe([req.symbol], req.exchange)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self._td_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self._td_api.cancel_order(req)

    def query_account(self):
        """"""
        self._td_api.query_accounts()

    def query_position(self):
        """"""
        self._td_api.query_positions()

    def _async_callback_exception_handler(self, e: AsyncDispatchException):
        error_str = f"发生内部错误：\n" f"位置：{e.instance}.{e.function_name}" f"详细信息：{e.what}"
        self.write_log(error_str)
