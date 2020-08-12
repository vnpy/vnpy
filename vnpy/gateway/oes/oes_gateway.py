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
from vnpy.trader.constant import Exchange
from vnpy.trader.utility import get_file_path
from vnpy.api.oes import TdApi


mydir = os.path.dirname(__file__)
config_template_path = os.path.join(mydir, "config_template.ini")
with open(config_template_path, "rt", encoding='utf-8') as f:
    config_template = f.read()

class OesGateway(BaseGateway):
    """
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

    exchanges = [Exchange.SSE, Exchange.SZSE]

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "OES")

        self.td_api = OesTdApi(self)


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

        self.td_api.connect(
            config_path=config_path,
            username=username,
            password=password,
            ord_server=setting['td_ord_server'],
            rpt_server=setting['td_rpt_server'],
            qry_server=setting['td_qry_server'],
            hdd_serial=setting['hdd_serial'],
            customize_ip=setting['customize_ip'],
            customize_mac=setting['customize_mac'],
        )

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
        # self.md_api.stop()
        self.td_api.stop()


class OesTdApi(TdApi):
    def __init__(self, gateway):
        """Constructor"""
        super(OesTdApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.reqid = 0

    def onConnected(self, channel_type, data):
        print("onConnected", data)

    def onDisconnected(self, channel_type, data):
        print("onDisConnected", data)

    def connect(
        self,
        config_path,
        username,
        password,
        ord_server,
        rpt_server,
        qry_server,
        hdd_serial,
        customize_ip,
        customize_mac,
        ):

        a=self.createTdAPi()
        b=self.loadCfg(config_path)
        c=self.setCustomizedIpAndMac(customize_ip, customize_mac)
        d=self.setCustomizedDriverId(hdd_serial)
        e=self.setThreadUsername(username)
        f=self.setThreadPassword(password)
        g=self.setThreadEnvId(0)
        h=self.setThreadSubscribeEnvId(0)
        i=self.init()
        print(a,b,c,d,e,f,g,h,i)
        
