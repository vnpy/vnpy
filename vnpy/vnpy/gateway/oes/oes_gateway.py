"""
Author: nanoric
"""
import hashlib
import os
from gettext import gettext as _
from threading import Lock, Thread

from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (CancelRequest, OrderRequest,
                                SubscribeRequest)
from vnpy.trader.utility import get_file_path
from .oes_md import OesMdApi
from .oes_td import OesTdApi, EXCHANGE_VT2OES
from .utils import config_template


class OesGateway(BaseGateway):
    """
    VN Trader Gateway for OES

    Because the design of OES API, multiple gateway instance with a same account is currently
        not supported.
    running multiple gateway instance with the same account will make send_order and
        cancel_order fail frequently, because:
        * seq_index is not unique between instances
        * value range of client_id is too small to create a unique hash for different client.
    """

    default_setting = {
        "td_ord_server": "",
        "td_rpt_server": "",
        "td_qry_server": "",
        "md_tcp_server": "",
        "md_qry_server": "",
        "username": "",
        "password": "",
        "hdd_serial": "",
        "customize_ip": "",
        "customize_mac": "",
    }

    exchanges = list(EXCHANGE_VT2OES.keys())

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "OES")

        self.md_api = OesMdApi(self)
        self.td_api = OesTdApi(self)

        self._lock_subscribe = Lock()
        self._lock_send_order = Lock()
        self._lock_cancel_order = Lock()
        self._lock_query_position = Lock()
        self._lock_query_account = Lock()

    def connect(self, setting: dict):
        """"""
        if not setting['password'].startswith("md5:"):
            setting['password'] = "md5:" + \
                hashlib.md5(setting['password'].encode()).hexdigest()

        username = setting['username']
        password = setting['password']

        config_path = str(get_file_path("vnoes.ini"))
        with open(config_path, "wt") as f:
            if 'test' in setting:
                log_level = 'DEBUG'
                log_mode = 'console'
            else:
                log_level = 'WARNING'
                log_mode = 'file'
            log_dir = get_file_path('oes')
            log_path = os.path.join(log_dir, 'log.log')
            if not os.path.exists(log_dir):
                os.mkdir(log_dir)
            content = config_template.format(**setting,
                                             log_level=log_level,
                                             log_mode=log_mode,
                                             log_path=log_path)
            f.write(content)

        self.md_api.tcp_server = setting['md_tcp_server']
        self.md_api.qry_server = setting['md_qry_server']
        Thread(target=self._connect_md_sync, args=(
            config_path, username, password)).start()

        self.td_api.ord_server = setting['td_ord_server']
        self.td_api.rpt_server = setting['td_rpt_server']
        self.td_api.qry_server = setting['td_qry_server']
        self.td_api.hdd_serial = setting['hdd_serial']
        self.td_api.customize_ip = setting['customize_ip']
        self.td_api.customize_mac = setting['customize_mac']
        Thread(target=self._connect_td_sync, args=(
            config_path, username, password)).start()

    def _connect_td_sync(self, config_path, username, password):
        self.td_api.config_path = config_path
        self.td_api.username = username
        self.td_api.password = password
        if self.td_api.connect():
            self.write_log(_("成功连接到交易服务器"))
            self.td_api.query_contracts()
            # self.td_api.query_account()
            self.write_log("合约信息查询成功")
            # self.td_api.query_position()
            # self.td_api.query_orders()
            self.td_api.start()
        else:
            self.write_log(_("无法连接到交易服务器，请检查你的配置"))

    def _connect_md_sync(self, config_path, username, password):
        self.md_api.config_path = config_path
        self.md_api.username = username
        self.md_api.password = password
        if self.md_api.connect():
            self.write_log(_("成功连接到行情服务器"))
            self.md_api.start()
        else:
            self.write_log(_("无法连接到行情服务器，请检查你的配置"))

    def subscribe(self, req: SubscribeRequest):
        """"""
        with self._lock_subscribe:
            self.md_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        with self._lock_send_order:
            return self.td_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        with self._lock_cancel_order:
            self.td_api.cancel_order(req)

    def query_account(self):
        """"""
        with self._lock_query_account:
            self.td_api.query_account()

    def query_position(self):
        """"""
        with self._lock_query_position:
            self.td_api.query_position()

    def close(self):
        """"""
        self.md_api.stop()
        self.td_api.stop()
