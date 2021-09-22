from typing import Dict, Tuple
import pytz
from datetime import datetime
from dataclasses import dataclass

from vnpy.trader.gateway import BaseGateway
from vnpy.event import EventEngine
from vnpy.trader.event import EVENT_TIMER
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

from vnpy.trader.constant import (
    Direction,
    Exchange,
    OrderType,
    Product,
    Status,
    Offset
)

from .stock_api import (
    traderapi,
    mdapi,
    TORA_TSTP_D_Buy,
    TORA_TSTP_D_Sell,
    TORA_TSTP_EXD_SSE,
    TORA_TSTP_EXD_SZSE,
    TORA_TSTP_OPT_LimitPrice,
    TORA_TSTP_OST_AllTraded,
    TORA_TSTP_OST_Canceled,
    TORA_TSTP_OST_NoTradeQueueing,
    TORA_TSTP_OST_PartTradedQueueing,
    TORA_TERT_RESTART,
    TORA_TSTP_LACT_UserID,
    TORA_TSTP_LACT_AccountID,
    TORA_TSTP_PID_SHBond,
    TORA_TSTP_PID_SHFund,
    TORA_TSTP_PID_SHStock,
    TORA_TSTP_PID_SZBond,
    TORA_TSTP_PID_SZFund,
    TORA_TSTP_PID_SZStock,
    TORA_TSTP_TC_GFD,
    TORA_TSTP_VC_AV,
    TORA_TSTP_AF_Delete,
    TORA_TSTP_HF_Speculation,
    TORA_TSTP_OF_Open,
    TORA_TSTP_OF_Close,
    CTORATstpQrySecurityField,
    CTORATstpQryInvestorField,
    CTORATstpQryShareholderAccountField,
    CTORATstpQryTradingAccountField,
    CTORATstpQryPositionField,
    CTORATstpQryOrderField,
    CTORATstpQryTradeField,
    CTORATstpInputOrderField,
    CTORATstpInputOrderActionField,
    TORA_TSTP_PID_SHKC,
    TORA_TSTP_OST_Unknown,
    # TORA_TSTP_OST_Handled,
    # TORA_TSTP_PD_Net,
    # TORA_TSTP_PD_Long,
    # TORA_TSTP_PD_Short,
    # TORA_TSTP_OST_Failed,
)
from .terminal_info import get_terminal_info


EXCHANGE_TORA2VT = {
    TORA_TSTP_EXD_SSE: Exchange.SSE,
    TORA_TSTP_EXD_SZSE: Exchange.SZSE,
}
EXCHANGE_VT2TORA = {v: k for k, v in EXCHANGE_TORA2VT.items()}

PRODUCT_TORA2VT = {
    TORA_TSTP_PID_SHStock: Product.EQUITY,
    TORA_TSTP_PID_SHFund: Product.FUND,
    TORA_TSTP_PID_SHBond: Product.BOND,
    TORA_TSTP_PID_SZStock: Product.EQUITY,
    TORA_TSTP_PID_SZFund: Product.FUND,
    TORA_TSTP_PID_SZBond: Product.BOND,
    TORA_TSTP_PID_SHKC: Product.EQUITY,
}

DIRECTION_TORA2VT = {
    TORA_TSTP_D_Buy: Direction.LONG,
    TORA_TSTP_D_Sell: Direction.SHORT,
}

DIRECTION_VT2TORA = {v: k for k, v in DIRECTION_TORA2VT.items()}
ORDER_TYPE_VT2TORA: Dict[OrderType, Tuple[str, str, str]] = {
    OrderType.LIMIT: (
        TORA_TSTP_OPT_LimitPrice, TORA_TSTP_TC_GFD, TORA_TSTP_VC_AV
    ),
}

ORDER_TYPE_TORA2VT: Dict[Tuple[str, str, str], OrderType] = {
    v: k for k, v in ORDER_TYPE_VT2TORA.items()
}

ORDER_STATUS_TORA2VT: Dict[str, Status] = {
    TORA_TSTP_OST_AllTraded: Status.ALLTRADED,
    TORA_TSTP_OST_PartTradedQueueing: Status.PARTTRADED,
    TORA_TSTP_OST_NoTradeQueueing: Status.NOTTRADED,
    TORA_TSTP_OST_Canceled: Status.CANCELLED,
    TORA_TSTP_OST_Unknown: Status.NOTTRADED,
}

OFFSET_TORA2VT = {
    TORA_TSTP_OF_Open: Offset.OPEN,
    TORA_TSTP_OF_Close: Offset.CLOSE
}

OFFSET_VT2TORA = {v: k for k, v in OFFSET_TORA2VT.items()}
ORDERTYPE_TORA2VT = {
    TORA_TSTP_OPT_LimitPrice: OrderType.LIMIT
}

CHINA_TZ = pytz.timezone("Asia/Shanghai")


ACCOUNT_USERID = "用户代码"
ACCOUNT_ACCOUNTID = "资金账号"
ADDRESS_FRONT = "前置地址"
ADDRESS_FENS = "FENS地址"


class ToraStockGateway(BaseGateway):
    """"""

    default_setting = {
        "账号": "",
        "密码": "",
        "行情服务器": "",
        "交易服务器": "",
        "账号类型": [ACCOUNT_USERID, ACCOUNT_ACCOUNTID],
        "地址类型": [ADDRESS_FRONT, ADDRESS_FENS]
    }

    exchanges = list(EXCHANGE_VT2TORA.keys())

    def __init__(self, event_engine: EventEngine):
        """"""
        super().__init__(event_engine, "TORASTOCK")

        self.td_api = ToraTdApi(self)
        self.md_api = ToraMdApi(self)

    def connect(self, setting: dict) -> None:
        """"""
        username = setting['账号']
        password = setting['密码']
        td_address = setting["交易服务器"]
        md_address = setting["行情服务器"]

        if not td_address.startswith("tcp://"):
            td_address = "tcp://" + td_address
        if not md_address.startswith("tcp://"):
            md_address = "tcp://" + md_address

        account_type = setting["账号类型"]
        address_type = setting["地址类型"]

        self.md_api.connect(username, password, md_address, account_type, address_type)
        self.td_api.connect(username, password, td_address, account_type, address_type)

        self.init_query()

    def close(self) -> None:
        """"""
        pass

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        self.md_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self.td_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        self.td_api.cancel_order(req)

    def query_account(self) -> None:
        """"""
        self.td_api.query_accounts()

    def query_position(self) -> None:
        """"""
        self.td_api.query_positions()

    def write_error(self, msg: str, error: dict):
        """"""
        error_id = error["ErrorID"]
        error_msg = error["ErrorMsg"]
        msg = f"{msg}，代码：{error_id}，信息：{error_msg}"
        self.write_log(msg)

    def process_timer_event(self, event) -> None:
        """"""
        self.count += 1
        if self.count < 2:
            return
        self.count = 0

        func = self.query_functions.pop(0)
        func()
        self.query_functions.append(func)

        self.md_api.update_date()

    def init_query(self) -> None:
        """"""
        self.count = 0
        self.query_functions = [self.query_account, self.query_position]
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)


class ToraMdApi(mdapi.CTORATstpMdSpi):

    def __init__(self, gateway):
        """Constructor"""
        super(ToraMdApi, self).__init__()

        self.gateway: ToraStockGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.reqid: int = 0
        self.api: mdapi.CTORATstpMdApi_CreateTstpMdApi = None

        self.connect_status: bool = False
        self.login_status: bool = False
        self.subscribed = set()

        self.userid: str = ""
        self.password: str = ""
        self.address: str = ""

    def OnFrontConnected(self) -> None:
        """
        Callback when front server is connected.
        """
        self.gateway.write_log("行情服务器连接成功")
        self.login()

    def OnFrontDisconnected(self, reason: int) -> None:
        """
        Callback when front server is disconnected.
        """
        self.login_status = False
        self.gateway.write_log(f"行情服务器连接断开，原因{reason}")

    def OnRspUserLogin(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """
        Callback when user is logged in.
        """
        if not error["ErrorID"]:
            self.login_status = True
            self.gateway.write_log("行情服务器登录成功")

        else:
            self.gateway.write_error("行情服务器登录失败", error)

    def OnRspError(self, error: dict, reqid: int, last: bool) -> None:
        """
        Callback when error occured.
        """
        self.gateway.write_error("行情接口报错", error)

    def OnRspSubMarketData(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """"""
        if not error or not error["ErrorID"]:
            return

        self.gateway.write_error("行情订阅失败", error)

    def OnRtnDepthMarketData(self, data: dict) -> None:
        """
        Callback of tick data update.
        """
        current_date = data["TradingDay"]
        current_time = data["UpdateTime"]
        dt = datetime.strptime(
            f'{current_date}-{current_time}', "%Y%m%d-%H:%M:%S"
        )
        dt = CHINA_TZ.localize(dt)

        tick = TickData(
            symbol=data["SecurityID"],
            exchange=EXCHANGE_TORA2VT[bytes.decode(data["ExchangeID"])],
            datetime=dt,
            name=data["SecurityName"],
            volume=0,
            open_interest=data["OpenInterest"],
            last_price=data["LastPrice"],
            last_volume=data["Volume"],
            limit_up=data["UpperLimitPrice"],
            limit_down=data["LowerLimitPrice"],
            open_price=data["OpenPrice"],
            high_price=data["HighestPrice"],
            low_price=data["LowestPrice"],
            pre_close=data["PreClosePrice"],
            bid_price_1=data["BidPrice1"],
            ask_price_1=data["AskPrice1"],
            bid_volume_1=data["BidVolume1"],
            ask_volume_1=data["AskVolume1"],
            gateway_name=self.gateway_name
        )

        if data["BidVolume2"] or data["AskVolume2"]:
            tick.bid_price_2 = data["BidPrice2"]
            tick.bid_price_3 = data["BidPrice3"]
            tick.bid_price_4 = data["BidPrice4"]
            tick.bid_price_5 = data["BidPrice5"]

            tick.ask_price_2 = data["AskPrice2"]
            tick.ask_price_3 = data["AskPrice3"]
            tick.ask_price_4 = data["AskPrice4"]
            tick.ask_price_5 = data["AskPrice5"]

            tick.bid_volume_2 = data["BidVolume2"]
            tick.bid_volume_3 = data["BidVolume3"]
            tick.bid_volume_4 = data["BidVolume4"]
            tick.bid_volume_5 = data["BidVolume5"]

            tick.ask_volume_2 = data["AskVolume2"]
            tick.ask_volume_3 = data["AskVolume3"]
            tick.ask_volume_4 = data["AskVolume4"]
            tick.ask_volume_5 = data["AskVolume5"]

        self.gateway.on_tick(tick)

    def connect(
        self,
        userid: str,
        password: str,
        address: str,
        account_type: str,
        address_type: str
    ) -> None:
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.address = address
        self.account_type = account_type
        self.address_type = address_type

        # If not connected, then start connection first.
        if not self.connect_status:
            self.api = mdapi.CTORATstpMdApi_CreateTstpMdApi()

            self.api.RegisterSpi(self)

            if self.address_type == ADDRESS_FRONT:
                self.api.RegisterFront(address)
            else:
                self.api.RegisterNameServer(address)

            self.api.Init()
            self.connect_status = True
        # If already connected, then login immediately.
        elif not self.login_status:
            self.login()

    def login(self) -> None:
        """
        Login to server.
        """
        login_req = mdapi.CTORATstpReqUserLoginField()
        login_req.LogInAccount = self.userid
        login_req.Password = self.password
        login_req.UserProductInfo = "vnpy_2.0"
        login_req.TerminalInfo = get_terminal_info()

        if self.account_type == ACCOUNT_USERID:
            login_req.LogInAccountType = TORA_TSTP_LACT_UserID
        else:
            login_req.LogInAccountType = TORA_TSTP_LACT_AccountID

        self.reqid += 1
        self.api.ReqUserLogin(login_req, self.reqid)

    def subscribe(self, req: SubscribeRequest) -> None:
        """
        Subscribe to tick data update.
        """
        if self.login_status:
            exchange = EXCHANGE_VT2TORA[req.exchange]
            self.api.SubscribeMarketData([str.encode(req.symbol)], exchange)

    def close(self) -> None:
        """
        Close the connection.
        """
        if self.connect_status:
            self.exit()

    def update_date(self) -> None:
        """"""
        self.current_date = datetime.now().strftime("%Y%m%d")


class ToraTdApi(traderapi.CTORATstpTraderSpi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super(ToraTdApi, self).__init__()

        self.gateway: ToraStockGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.reqid: int = 0
        self.order_ref: int = 0

        self.connect_status: bool = False
        self.login_status: bool = False
        self.auth_status: bool = False
        self.login_failed: bool = False

        self.investor_id: str = None
        self.shareholder_ids: Dict[Exchange, str] = {}
        self.account_id: str = None
        self.localid: int = 10000
        self.api: traderapi.CTORATstpTraderApi.CreateTstpTraderApi = None
        self.userid: str = ""
        self.password: str = ""
        self.frontid: int = 0
        self.sessionid: int = 0

        self.sysid_orderid_map = {}
        self.orders = {}

    def OnFrontConnected(self) -> None:
        """"""
        self.gateway.write_log("交易服务器连接成功")
        self.login()

    def OnFrontDisconnected(self, reason: int) -> None:
        """"""
        self.login_status = False
        self.gateway.write_log(f"交易服务器连接断开，原因{reason}")

    def OnRspUserLogin(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """"""
        if not error["ErrorID"]:
            self.frontid = data["FrontID"]
            self.sessionid = data["SessionID"]
            self.login_status = True
            self.gateway.write_log("交易服务器登录成功")

            self.query_contracts()
            self.query_investors()
            self.query_shareholder_ids()

        else:
            self.login_failed = True

            self.gateway.write_error("交易服务器登录失败", error)

    def OnRspOrderAction(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """"""
        error_id = error["ErrorID"]
        if error_id:
            self.gateway.write_error("交易撤单失败", error)

    def OnRtnOrder(self, data: dict) -> None:
        """
        Callback of order status update.
        """
        symbol = data["SecurityID"]
        exchange = EXCHANGE_TORA2VT[bytes.decode(data["ExchangeID"])]

        frontid = data["FrontID"]
        sessionid = data["SessionID"]
        order_ref = data["OrderRef"]
        order_id = f"{frontid}_{sessionid}_{order_ref}"

        timestamp = f"{data['InsertDate']} {data['InsertTime']}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H:%M:%S")
        dt = CHINA_TZ.localize(dt)

        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=order_id,
            type=ORDERTYPE_TORA2VT[bytes.decode(data["OrderPriceType"])],
            direction=Direction.NET,
            price=data["LimitPrice"],
            volume=data["VolumeTotalOriginal"],
            traded=data["VolumeTraded"],
            status=ORDER_STATUS_TORA2VT[bytes.decode(data["OrderStatus"])],
            datetime=dt,
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)

        self.sysid_orderid_map[data["OrderSysID"]] = order_id

        self.orders[order_id] = OrderInfo(
            order_ref,
            exchange,
            sessionid,
            frontid,
        )

    def OnRtnTrade(self, data: dict) -> None:
        """
        Callback of trade status update.
        """
        symbol = data["SecurityID"]
        exchange = EXCHANGE_TORA2VT[bytes.decode(data["ExchangeID"])]

        orderid = self.sysid_orderid_map[data["OrderSysID"]]

        timestamp = f"{data['TradeDate']} {data['TradeTime']}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H:%M:%S")
        dt = CHINA_TZ.localize(dt)

        trade = TradeData(
            symbol=symbol,
            exchange=exchange,
            orderid=orderid,
            tradeid=data["TradeID"],
            direction=Direction.NET,
            price=data["Price"],
            volume=data["Volume"],
            datetime=dt,
            gateway_name=self.gateway_name
        )
        self.gateway.on_trade(trade)

    def OnRspQrySecurity(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """
        Callback of instrument query.
        """
        if last:
            self.gateway.write_log("合约信息查询成功")
        if not data:
            return

        contract_data = ContractData(
            gateway_name=self.gateway.gateway_name,
            symbol=data["SecurityID"],
            exchange=EXCHANGE_TORA2VT[bytes.decode(data["ExchangeID"])],
            name=data["SecurityName"],
            product=PRODUCT_TORA2VT.get(bytes.decode(data["ProductID"]), Product.EQUITY),
            size=data["VolumeMultiple"],
            pricetick=data["PriceTick"],
            min_volume=data["MinLimitOrderBuyVolume"],
            stop_supported=False,
            net_position=True,
            history_data=False,
        )
        self.gateway.on_contract(contract_data)

    def OnRspQryTradingAccount(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """"""
        if not data:
            return

        self.account_id = data["AccountID"]
        account_data = AccountData(
            gateway_name=self.gateway.gateway_name,
            accountid=data["AccountID"],
            balance=data["Available"],
            frozen=data["FrozenCash"] + data["FrozenCommission"]
        )
        self.gateway.on_account(account_data)

    def OnRspQryShareholderAccount(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """"""
        if not data:
            return

        exchange = EXCHANGE_TORA2VT[bytes.decode(data["ExchangeID"])]
        self.shareholder_ids[exchange] = data["ShareholderID"]

    def OnRspQryInvestor(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """"""
        if not data:
            return
        self.investor_id = data["InvestorID"]

    def OnRspQryPosition(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """"""
        if not data:
            return

        if data["InvestorID"] != self.investor_id:
            self.gateway.write_log("OnRspQryPosition:收到其他账户的仓位信息")
            return

        volume = data["TodayBSPos"]
        if volume == 0:
            price = data["TotalPosCost"]
        else:
            price = data["TotalPosCost"] / volume

        frozen = data["HistoryPosFrozen"] + data["TodayBSFrozen"] + \
            data["TodayPRFrozen"]
        position_data = PositionData(
            gateway_name=self.gateway.gateway_name,
            symbol=data["SecurityID"],
            exchange=EXCHANGE_TORA2VT[bytes.decode(data["ExchangeID"])],
            direction=Direction.NET,
            volume=volume,
            frozen=frozen,
            price=price,
            pnl=data["LastPrice"] * volume - data["TotalPosCost"],
            yd_volume=data["HistoryPos"],
        )
        self.gateway.on_position(position_data)

    def OnErrRtnOrderInsert(self, data: dict, error: dict) -> None:
        """"""
        order_ref = data["OrderRef"]
        order_id = f"{self.frontid}_{self.sessionid}_{order_ref}"
        dt = datetime.now()
        dt = CHINA_TZ.localize(dt)

        order = OrderData(
            symbol=data["SecurityID"],
            exchange=EXCHANGE_TORA2VT[bytes.decode(data["ExchangeID"])],
            orderid=order_id,
            type=ORDERTYPE_TORA2VT[bytes.decode(data["OrderPriceType"])],
            direction=Direction.NET,
            price=data["LimitPrice"],
            volume=data["VolumeTotalOriginal"],
            traded=0,
            status=Status.REJECTED,
            datetime=dt,
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)

        self.gateway.write_log(
            f"拒单({order_id}):"
            f"错误码:{error['ErrorID']}, 错误消息:{error['ErrorMsg']}"
        )

    def OnErrRtnOrderAction(self, data: dict, error: dict) -> None:
        """"""
        pass

    def OnRtnCondOrder(self, data: dict) -> None:
        """"""
        pass

    def OnRspOrderInsert(
        self,
        data: dict,
        error: dict,
        reqid: int,
        last: bool
    ) -> None:
        """"""
        pass

    def connect(
        self,
        userid: str,
        password: str,
        address: str,
        account_type: str,
        address_type: str
    ) -> None:
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.address = address
        self.account_type = account_type
        self.address_type = address_type

        if not self.connect_status:
            self.api = traderapi.CTORATstpTraderApi.CreateTstpTraderApi()

            self.api.RegisterSpi(self)

            if self.address_type == ADDRESS_FRONT:
                self.api.RegisterFront(address)
            else:
                self.api.RegisterNameServer(address)

            self.api.SubscribePrivateTopic(TORA_TERT_RESTART)
            self.api.SubscribePublicTopic(TORA_TERT_RESTART)
            self.api.Init()
            self.connect_status = True

    def login(self) -> None:
        """
        Login onto server.
        """
        login_req = traderapi.CTORATstpReqUserLoginField()
        login_req.LogInAccount = self.userid
        login_req.Password = self.password
        login_req.UserProductInfo = "vnpy_2.0"
        login_req.TerminalInfo = get_terminal_info()

        if self.account_type == ACCOUNT_USERID:
            login_req.LogInAccountType = TORA_TSTP_LACT_UserID
        else:
            login_req.LogInAccountType = TORA_TSTP_LACT_AccountID

        self.reqid += 1
        self.api.ReqUserLogin(login_req, self.reqid)

    def query_contracts(self) -> None:
        """"""
        req = CTORATstpQrySecurityField()
        self.reqid += 1
        self.api.ReqQrySecurity(req, self.reqid)

    def query_investors(self) -> None:
        """"""
        req = CTORATstpQryInvestorField()
        self.reqid += 1
        self.api.ReqQryInvestor(req, self.reqid)

    def query_shareholder_ids(self) -> None:
        """"""
        req = CTORATstpQryShareholderAccountField()
        self.reqid += 1
        self.api.ReqQryShareholderAccount(req, self.reqid)

    def query_accounts(self) -> None:
        """"""
        req = CTORATstpQryTradingAccountField()
        self.reqid += 1
        self.api.ReqQryTradingAccount(req, self.reqid)

    def query_positions(self) -> None:
        """"""
        req = CTORATstpQryPositionField()
        self.reqid += 1
        self.api.ReqQryPosition(req, self.reqid)

    def query_orders(self) -> None:
        """"""
        req = CTORATstpQryOrderField()
        self.reqid += 1
        self.api.ReqQryOrder(req, self.reqid)

    def query_trades(self) -> None:
        """"""
        req = CTORATstpQryTradeField()
        self.reqid += 1
        self.api.ReqQryTrade(req, self.reqid)

    def send_order(self, req: OrderRequest):
        """"""
        self.reqid += 1
        order_ref = self._get_new_order_id()

        opt, tc, vc = ORDER_TYPE_VT2TORA[req.type]

        info = CTORATstpInputOrderField()
        info.ShareholderID = self.shareholder_ids[req.exchange]
        info.SecurityID = req.symbol
        info.ExchangeID = EXCHANGE_VT2TORA[req.exchange]
        info.OrderRef = order_ref
        info.OrderPriceType = opt
        info.Direction = DIRECTION_VT2TORA[req.direction]
        info.CombOffsetFlag = TORA_TSTP_OF_Open
        info.CombHedgeFlag = TORA_TSTP_HF_Speculation
        info.LimitPrice = req.price
        info.VolumeTotalOriginal = int(req.volume)
        info.TimeCondition = tc
        info.VolumeCondition = vc

        order_id = f"{self.frontid}_{self.sessionid}_{order_ref}"

        self.orders[order_id] = OrderInfo(
            order_ref,
            EXCHANGE_VT2TORA[req.exchange],
            self.sessionid,
            self.frontid,
        )
        self.gateway.on_order(
            req.create_order_data(order_id, self.gateway.gateway_name)
        )
        self.api.ReqOrderInsert(info, self.reqid)

        return f"{self.gateway_name}.{order_id}"

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        self.reqid += 1
        info = CTORATstpInputOrderActionField()
        info.InvestorID = self.investor_id
        info.ExchangeID = EXCHANGE_VT2TORA[req.exchange]
        info.SecurityID = req.symbol

        order_info = self.orders[req.orderid]
        info.OrderRef = order_info.local_order_id
        info.FrontID = order_info.front_id
        info.SessionID = order_info.session_id
        info.ActionFlag = TORA_TSTP_AF_Delete

        self.api.ReqOrderAction(info, self.reqid)

    def _get_new_order_id(self) -> int:
        """"""
        self.localid += 1
        order_id = str(self.localid)
        return order_id


@dataclass()
class OrderInfo:
    local_order_id: str
    exchange_id: str
    session_id: int
    front_id: int
