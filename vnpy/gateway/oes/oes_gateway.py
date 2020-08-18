"""
Author: nanoric
"""
import hashlib
import os
from gettext import gettext as _
from threading import Lock, Thread
from datetime import datetime

from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (CancelRequest, OrderRequest,
                                SubscribeRequest)
from vnpy.trader.utility import get_file_path
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    PositionData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
)
from vnpy.api.oes import TdApi
from vnpy.trader.constant import (
    Direction,
    Offset,
    Exchange,
    OrderType,
    Product,
    Status,
    OptionType
)


mydir = os.path.dirname(__file__)
config_template_path = os.path.join(mydir, "config_template.ini")
with open(config_template_path, "rt", encoding='utf-8') as f:
    config_template = f.read()

CHANNELTYPE_OES2VT = {
    1: "委托通道",
    2: "回报通道",
    3: "查询通道",
}

OPTIONTYPE_OES2VT = {
    1: OptionType.CALL,
    2: OptionType.PUT
}

PRODUCT_OES2VT = {
    1: Product.EQUITY,
    2: Product.BOND,
    3: Product.ETF,
    4: Product.FUND,
    5: Product.OPTION
}

DIRECTION_OES2VT = {
    1: Direction.LONG,
    2: Direction.SHORT,
    3: Direction.LONG

}

EXCHANGE_OES2VT = {
    1: Exchange.SSE,
    2: Exchange.SZSE,
    3: Exchange.SSE,
    4: Exchange.SZSE,
}

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

        # self.md_api = OesMdApi(self)
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

        # self.md_api.tcp_server = setting['md_tcp_server']
        # self.md_api.qry_server = setting['md_qry_server']
        # Thread(target=self._connect_md_sync, args=(
        #     config_path, username, password)).start()

        self.td_api.connect(
            config_path=config_path,
            username=username,
            password=password,
            ord_server=setting['td_ord_server'],
            rpt_server=setting['td_rpt_server'],
            hdd_serial=setting['hdd_serial'],
            qry_server=setting['td_qry_server'],
            customize_ip=setting['customize_ip'],
            customize_mac=setting['customize_mac'],
        )

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
        # self.md_api.stop()
        self.td_api.exit()


class OesTdApi(TdApi):
    userid = 0

    def __init__(self, gateway):
        """Constructor"""
        super(OesTdApi, self).__init__()
        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.reqid = 0
        self.count = 0
        self.cc = 0


    def onConnected(self,channel, data):
        """"""
        channel_msg = CHANNELTYPE_OES2VT[channel]
        self.gateway.write_log(f"{channel_msg}连接成功")

        if channel == 3:
            self.query_account()

    def onDisConnected(self,channel, data):
        """"""
        self.gateway.write_log("交易服务器连接断开")

    def onTradeReport(self, error, data):
        print("onTradeReport", data, error)

    def onOrderReport(self, error, data):
        print("onOrderReport", data, error)

    def onQueryCashAsset(self, data, error, reqid):
        # print("onQueryCashAsset", data, error)
        account = AccountData(
            accountid=data["cashAcctId"],
            balance=data["currentTotalBal"],
            frozen=data["marginAmt"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

        self.userid = data["custId"]
        self.query_position()
        self.query_contract()
        self.query_order()
        self.query_trade()

    def query_order(self):
        req = {}
        self.reqid += 1
        n = self.queryOrder(req, self.reqid)
        print("query order=", n)

    def query_trade(self):
        req = {}
        self.reqid += 1
        n = self.queryTrade(req, self.reqid)
        print("query trade=", n)

    def onQueryOrder(self, data, error, reqid):
        print("on query order", data, error)

    def onQueryTrade(self, data, error, reqid):
        print("on query trade", data, error)

    def onQueryStock(self, data, error, reqid):
        last = error["isEnd"]

        contract = ContractData(
            symbol=data["securityId"],
            exchange=EXCHANGE_OES2VT[data["mktId"]],
            product=PRODUCT_OES2VT[data["securityType"]],
            size=1,
            min_volume=data["buyQtyUnit"],
            name=data["securityName"],
            pricetick=data["priceTick"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_contract(contract)
        if last:
            self.gateway.write_log("证券合约查询完成")

    def onQueryOption(self, data, error, reqid):
        last = error["isEnd"]
        contract = ContractData(
            symbol=data["securityId"],
            exchange=EXCHANGE_OES2VT[data["mktId"]],
            product=PRODUCT_OES2VT[data["securityType"]],
            size=1,
            min_volume=data["buyQtyUnit"],
            name=data["securityName"],
            pricetick=data["priceTick"],
            option_strike=data["exercisePrice"],
            option_underlying=data["underlyingSecurityId"],
            option_type=OPTIONTYPE_OES2VT[data["contractType"]],
            option_expiry=datetime.strptime(str(data["lastTradeDay"]), "%Y%m%d"),
            gateway_name=self.gateway_name
        )
        contract.option_index = get_option_index(
            contract.option_strike, data["contractId"]
        )
        self.gateway.on_contract(contract)
        if last:
            self.gateway.write_log("期权合约查询完成")
        

    def onQueryEtf(self, data, error, reqid):
        if self.cc < 4:
            print("onQueryEtf", data, error)
            self.cc += 1 
        # last = error["isEnd"]
        # contract = ContractData(
        #     symbol=data["securityId"],
        #     exchange=EXCHANGE_OES2VT[data["mktId"]],
        #     product=PRODUCT_OES2VT[data["securityType"]],
        #     size=1,
        #     min_volume=data["buyQtyUnit"],
        #     name=data["securityName"],
        #     pricetick=data["priceTick"],
        #     option_strike=data["exercisePrice"],
        #     option_underlying=data["underlyingSecurityId"],
        #     option_type=OPTIONTYPE_OES2VT[data["contractType"]],
        #     option_expiry=datetime.strptime(str(data["lastTradeDay"]), "%Y%m%d"),
        #     gateway_name=self.gateway_name
        # )
        # contract.option_index = get_option_index(
        #     contract.option_strike, data["contract_id"]
        # )
        # self.gateway.on_contract(contract)
        # if last:
        #     self.gateway.write_log("证券合约查询完成")
    def onQueryStkHolding(self, data, error, reqid):
        pass

    def onQueryOptHolding(self, data, error, reqid):
        last = error["isEnd"]

        pos = PositionData(
            symbol=data["securityId"],
            exchange=EXCHANGE_OES2VT[data["mktId"]],
            direction=DIRECTION_OES2VT[data["positionType"]],
            volume=data["sumQty"],
            frozen=data["closeFrzQty"],
            price=data["costPrice"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(pos)

        if last:
            self.gateway.write_log("期权持仓查询成功")

    def query_account(self):
        self.reqid += 1
        self.queryCashAsset({}, self.reqid)

    def query_position(self):
        self.reqid += 1
        req = {
            "custId": self.userid,
            "mktId": 0,
            "securityType": 0,
            "productType": 0
        }
        self.queryStkHolding(req, self.reqid)

        self.reqid += 1
        self.queryOptHolding(req, self.reqid)

    def query_contract(self):
        self.reqid += 1

        stock_req = {
            "mktId": 0,
            "securityType": 0,
            "subSecurityType": 0
        }
        self.queryStock(stock_req, self.reqid)
        

        self.reqid += 1
        option_req = {
            "mktId": 0,
        }
        b=self.queryOption(option_req, self.reqid)
        print("b=", b)

        self.reqid += 1
        c=self.queryEtf(option_req, self.reqid)
        print("c=", c)

    def connect(
        self,
        config_path,
        username,
        password,
        ord_server,
        rpt_server,
        hdd_serial,
        qry_server,
        customize_ip,
        customize_mac,
    ):

        self.createTdAPi()
        self.loadCfg(config_path)
        self.setCustomizedIpAndMac(customize_ip, customize_mac)
        self.setCustomizedDriverId(hdd_serial)
        self.setThreadUsername(username)
        self.setThreadPassword(password)
        self.setThreadEnvId(0)
        self.setThreadSubscribeEnvId(0)
        self.init()


def get_option_index(strike_price: float, exchange_instrument_id: str) -> str:
    """"""
    exchange_instrument_id = exchange_instrument_id.replace(" ", "")

    if "M" in exchange_instrument_id:
        n = exchange_instrument_id.index("M")
    elif "A" in exchange_instrument_id:
        n = exchange_instrument_id.index("A")
    elif "B" in exchange_instrument_id:
        n = exchange_instrument_id.index("B")
    else:
        return str(strike_price)

    index = exchange_instrument_id[n:]
    option_index = f"{strike_price:.3f}-{index}"

    return option_index