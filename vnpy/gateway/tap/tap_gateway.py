from dataclasses import dataclass
from datetime import datetime
from typing import Dict, Tuple

from vnpy.api.tap import MdApi, TdApi

from vnpy.event import EventEngine
from vnpy.trader.utility import get_folder_path
from vnpy.trader.constant import (
    Exchange,
    Product,
    Direction,
    Status,
    OrderType
)
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    CancelRequest,
    OrderRequest,
    SubscribeRequest,
    TickData,
    ContractData,
    OrderData,
    TradeData,
    PositionData,
    AccountData
)

PRODUCT_TYPE_TAP2VT: Dict[str, Product] = {
    "P": Product.SPOT,
    "F": Product.FUTURES,
    "O": Product.OPTION,
    "Z": Product.INDEX,
    "T": Product.EQUITY,
}

EXCHANGE_TAP2VT: Dict[str, Exchange] = {
    "SGX": Exchange.SGX,
    "INE": Exchange.INE,
    "APEX": Exchange.APEX,
    "NYMEX": Exchange.NYMEX,
    "LME": Exchange.LME,
    "COMEX": Exchange.COMEX,
    "CBOT": Exchange.CBOT,
    "HKEX": Exchange.HKFE,
    "CME": Exchange.CME,
    "ZCE": Exchange.CZCE,
    "DCE": Exchange.DCE,
    "TOCOM": Exchange.TOCOM,
    "KRX": Exchange.KRX,
    "ICUS": Exchange.ICE,
    "ICEU": Exchange.ICE
}
EXCHANGE_VT2TAP: Dict[Exchange, str] = {v: k for k, v in EXCHANGE_TAP2VT.items()}

DIRECTION_TAP2VT: Dict[str, Direction] = {
    "N": Direction.NET,
    "B": Direction.LONG,
    "S": Direction.SHORT,
}
DIRECTION_VT2TAP: Dict[Direction, str] = {v: k for k, v in DIRECTION_TAP2VT.items()}

STATUS_TAP2VT: Dict[str, Status] = {
    "0": Status.SUBMITTING,
    "1": Status.SUBMITTING,
    "4": Status.NOTTRADED,
    "5": Status.PARTTRADED,
    "6": Status.ALLTRADED,
    "7": Status.CANCELLED,
    "9": Status.REJECTED,
}

ORDERTYPE_TAP2VT: Dict[str, OrderType] = {
    "1": OrderType.MARKET,
    "2": OrderType.LIMIT
}
ORDERTYPE_VT2TAP = {v: k for k, v in ORDERTYPE_TAP2VT.items()}

ERROR_VT2TAP: Dict[str, int] = {
    "TAPIERROR_SUCCEED": 0
}

LOGLEVEL_VT2TAP: Dict[str, str] = {
    "APILOGLEVEL_NONE": "N",
    "APILOGLEVEL_ERROR": "E",
    "APILOGLEVEL_WARNING": "W",
    "APILOGLEVEL_DEBUG": "D"
}

commodity_infos: Dict[str, "CommodityInfo"] = {}
contract_infos: Dict[Tuple[str, "Exchange"], "ContractInfo"] = {}

FLAG_VT2TAP: Dict[str, str] = {
    "APIYNFLAG_YES": "Y",
    "APIYNFLAG_NO": "N",
    "TAPI_CALLPUT_FLAG_CALL": "C",
    "TAPI_CALLPUT_FLAG_PUT": "P",
    "TAPI_CALLPUT_FLAG_NONE": "N"
}


class TapGateway(BaseGateway):
    """
    VN Trader gateway for Esunny 9.0.
    """

    default_setting = {
        "quote_username": "",
        "quote_password": "",
        "quote_host": "",
        "quote_port": 0,
        "trade_username": "",
        "trade_password": "",
        "trade_host": "",
        "trade_port": 0,
        "auth_code": ""
    }

    exchanges = list(EXCHANGE_VT2TAP.keys())

    def __init__(self, event_engine: EventEngine):
        """"""
        super().__init__(event_engine, "TAP")

        self.md_api = QuoteApi(self)
        self.td_api = TradeApi(self)

    def connect(self, setting: dict) -> None:
        """"""
        quote_username = setting["quote_username"]
        quote_password = setting["quote_password"]
        quote_host = setting["quote_host"]
        quote_port = setting["quote_port"]
        trade_username = setting["trade_username"]
        trade_password = setting["trade_password"]
        trade_host = setting["trade_host"]
        trade_port = setting["trade_port"]
        auth_code = setting["auth_code"]

        self.td_api.connect(
            trade_username,
            trade_password,
            trade_host,
            trade_port,
            auth_code
        )
        self.md_api.connect(
            quote_username,
            quote_password,
            quote_host,
            quote_port,
            auth_code
        )

    def close(self) -> None:
        """"""
        self.td_api.close()
        self.md_api.close()

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
        pass

    def query_position(self) -> None:
        """"""
        pass

    # def _async_callback_exception_handler(self, e: AsyncDispatchException):
    #     """"""
    #     error_str = (f"发生内部错误，位置：\n{e.instance}.{e.function_name}，详细信息：\n"
    #                  f"{e.what}\n"
    #                  )
    #     print(error_str)
    #     self.write_log(error_str)


class QuoteApi(MdApi):
    """
    Implementation of TAP quote api.
    """

    def __init__(self, gateway: TapGateway):
        """"""
        super().__init__()

        self.gateway: TapGateway = gateway
        self.gateway_name: str = gateway.gateway_name

    def onRspLogin(self, error: int, data: dict) -> None:
        """
        Callback of login request.
        """
        if error != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"行情服务器登录失败：{error_to_str(error)}")
        else:
            self.gateway.write_log("行情服务器登录成功")

    def onAPIReady(self) -> None:
        """
        Callback when API is ready for sending requests or queries.
        """
        self.qryCommodity()

    def onDisconnect(self, reason: int) -> None:
        """
        Callback when connection to TAP server is lost.
        """
        self.gateway.write_log(f"行情服务器连接断开，原因：{reason}")

    def onRspSubscribeQuote(
        self,
        session: int,
        error: int,
        last: str,
        data: dict
    ) -> None:
        """
        Callback of subscribe market data request.
        """
        if error != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"订阅行情失败：{error_to_str(error)}")
        else:
            self.update_tick(data)

    def onRtnQuote(self, data: dict) -> None:
        """
        Callback of new data update.
        """
        self.update_tick(data)

    def update_tick(self, data: dict) -> None:
        """
        Convert TAP quote data structure into TickData event and push it.
        """
        symbol = data.Contract.Commodity.CommodityNo + data.Contract.ContractNo1
        exchange = EXCHANGE_TAP2VT[data.Contract.Commodity.ExchangeNo]

        contract_info = contract_infos.get((symbol, exchange), None)
        if not contract_info:
            self.gateway.write_log(f"行情合约信息无法匹配：{symbol}和{exchange}")
            return

        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=parse_datetime(data.DateTimeStamp),
            name=contract_info.name,
            volume=data.QTotalQty,
            last_price=data.QLastPrice,
            last_volume=data.QLastQty,
            limit_up=data.QLimitUpPrice,
            limit_down=data.QLimitDownPrice,
            open_price=data.QOpeningPrice,
            high_price=data.QHighPrice,
            low_price=data.QLowPrice,
            pre_close=data.QPreClosingPrice,
            bid_price_1=data.QBidPrice[0],
            bid_price_2=data.QBidPrice[1],
            bid_price_3=data.QBidPrice[2],
            bid_price_4=data.QBidPrice[3],
            bid_price_5=data.QBidPrice[4],
            ask_price_1=data.QAskPrice[0],
            ask_price_2=data.QAskPrice[1],
            ask_price_3=data.QAskPrice[2],
            ask_price_4=data.QAskPrice[3],
            ask_price_5=data.QAskPrice[4],
            bid_volume_1=data.QBidQty[0],
            bid_volume_2=data.QBidQty[1],
            bid_volume_3=data.QBidQty[2],
            bid_volume_4=data.QBidQty[3],
            bid_volume_5=data.QBidQty[4],
            ask_volume_1=data.QAskQty[0],
            ask_volume_2=data.QAskQty[1],
            ask_volume_3=data.QAskQty[2],
            ask_volume_4=data.QAskQty[3],
            ask_volume_5=data.QAskQty[4],
            gateway_name=self.gateway_name,
        )
        self.gateway.on_tick(tick)

    def connect(
        self,
        username: str,
        password: str,
        host: str,
        port: int,
        auth_code: str
    ) -> None:
        """
        Starting connection to TAP server.
        """
        # General API setting
        path = get_folder_path(self.gateway_name.lower())
        self.setTapQuoteAPIDataPath(str(path))

        self.setTapQuoteAPILogLevel(LOGLEVEL_VT2TAP["APILOGLEVEL_NONE"])

        # Create API object
        data = self.tapAPIApplicationInfo()
        data.AuthCode = auth_code
        data.KeyOperationLogPath = str(path)

        self.api, iResult = self.createTapQuoteAPI(data)
        if not self.api:
            self.gateway.write_log("行情API初始化失败")
            return

        # Set server address and port
        self.setAPINotify(self)
        self.setHostAddress(host, port)

        # Start connection
        login_auth = self.tapAPIQuoteLoginAuth()
        login_auth.UserNo = username
        login_auth.Password = password
        login_auth.ISDDA = FLAG_VT2TAP["APIYNFLAG_NO"]
        login_auth.ISModifyPassword = FLAG_VT2TAP["APIYNFLAG_NO"]

        self.Login(login_auth)

    def close(self):
        """
        Release TAP API resources.
        """
        if self.api:
            self.setAPINotify(None)
            self.freeTapQuoteAPI(self.api)
            # self.api = None

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to new market data update.
        """
        contract_info = contract_infos.get((req.symbol, req.exchange), None)
        if not contract_info:
            self.gateway.write_log(
                f"找不到匹配的合约：{req.symbol}和{req.exchange.value}")
            return

        tap_contract = self.tapAPIContract()
        tap_contract.Commodity.ExchangeNo = EXCHANGE_VT2TAP[req.exchange]
        tap_contract.Commodity.CommodityType = contract_info.commodity_type
        tap_contract.Commodity.CommodityNo = contract_info.commodity_no
        tap_contract.ContractNo1 = contract_info.contract_no
        tap_contract.CallOrPutFlag1 = FLAG_VT2TAP["TAPI_CALLPUT_FLAG_NONE"]
        tap_contract.CallOrPutFlag2 = FLAG_VT2TAP["TAPI_CALLPUT_FLAG_NONE"]

        self.SubscribeQuote(tap_contract)


class TradeApi(TdApi):
    """
    Implementation of TAP trade api.
    """

    def __init__(self, gateway: TapGateway):
        """"""
        super().__init__()

        self.gateway: TapGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.account_no = ""        # required when sending order request
        self.cancel_reqs = {}       # waiting cancel order requests before OrderNo received

        # for mapping relationship between TAP OrderNo and ClientOrderNo
        self.sys_local_map = {}
        self.local_sys_map = {}
        self.sys_server_map = {}

    def onConnect(self) -> None:
        """
        Callback when connection is established with TAP server.
        """
        self.gateway.write_log("交易服务器连接成功")

    def onRspLogin(self, error: int, data: dict) -> None:
        """
        Callback of login request.
        """
        if error != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"交易服务器登录失败：{error_to_str(error)}")
        else:
            self.gateway.write_log("交易服务器登录成功")

    def onAPIReady(self, code: int) -> None:
        """
        Callback when API is ready for sending requests or queries.
        """
        self.qryCommodity()

    def onRspQryCommodity(
        self,
        session: int,
        error: int,
        last: str,
        data: dict,
    ) -> None:
        """
        Callback of commodity query with size and pricetick data.
        """
        if error != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log("查询交易品种信息失败")
            return

        commodity_info = CommodityInfo(
            name=data.CommodityEngName,
            size=int(data.ContractSize),
            pricetick=data.CommodityTickSize
        )
        commodity_infos[data.CommodityNo] = commodity_info

        if last == "Y":
            self.gateway.write_log("查询交易品种信息成功")
            self.QryContract(None)

    def onRspQryContract(
        self,
        session: int,
        error: int,
        last: str,
        data: dict
    ) -> None:
        """
        Callback of contract query with detailed contract data.
        """
        if error != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log("查询交易合约信息失败")
            return

        exchange = EXCHANGE_TAP2VT.get(data.ExchangeNo, None)
        commodity_info = commodity_infos.get(data.CommodityNo, None)

        if not data or not exchange or not commodity_info:
            return

        if data.CommodityType == "F":
            symbol = data.CommodityNo + data.ContractNo1

            if commodity_info.name:
                name = f"{commodity_info.name} {data.ContractNo1}"
            else:
                name = symbol

            contract = ContractData(
                symbol=symbol,
                exchange=exchange,
                name=name,
                product=Product.FUTURES,
                size=commodity_info.size,
                pricetick=commodity_info.pricetick,
                net_position=True,
                gateway_name=self.gateway.gateway_name
            )
            self.gateway.on_contract(contract)

            contract_info = ContractInfo(
                name=contract.name,
                exchange_no=data.ExchangeNo,
                contract_no=data.ContractNo1,
                commodity_type=data.CommodityType,
                commodity_no=data.CommodityNo,
            )
            contract_infos[(contract.symbol, contract.exchange)] = contract_info

        if last == "Y":
            self.gateway.write_log("查询交易合约信息成功")
            self.query_account()

    def onRspQryAccount(
        self,
        session: int,
        error: int,
        last: str,
        data: dict
    ) -> None:
        """
        Callback of account number query.
        """
        if error != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"查询账号信息失败")
            return

        req = self.tapAPIFundReq()
        req.AccountNo = data.AccountNo
        self.QryFund(req)

    def onRspQryFund(
        self,
        session: int,
        error: int,
        last: str,
        data: dict
    ) -> None:
        """Callback of account fund query"""
        if error != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"查询资金信息失败")
            return

        self.update_account(data)

        if last == "Y":
            self.gateway.write_log("查询资金信息成功")
            self.query_position()

    def onRtnFund(self, data: dict) -> None:
        """
        Callback of account fund update.
        """
        self.update_account(data)

    def onRspQryPositionSummary(
        self,
        session: int,
        error: int,
        last: str,
        data: dict
    ) -> None:
        """
        Callback of position summary query.

        Position summary reflects the sum of positions on each contract.
        """
        if error != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"查询持仓信息失败")
            return

        if data:
            self.update_position(data)

        if last == "Y":
            self.gateway.write_log(f"查询持仓信息成功")
            self.query_order()

    def onRtnPositionSummary(self, data: dict) -> None:
        """
        Callback of position summary update.
        """
        self.update_position(data)

    def onRspQryOrder(
        self,
        session: int,
        error: int,
        last: str,
        data: dict
    ) -> None:
        """
        Callback of today's order query.
        """
        if error != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"查询委托信息失败")
            return

        if data:
            self.update_order(data)

        if last == "Y":
            self.gateway.write_log(f"查询委托信息成功")
            self.query_trade()

    def onRtnOrder(self, data: dict) -> None:
        """
        Callback of order update.
        """
        if data.ErrorCode != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"委托下单失败：{error_to_str(data.ErrorCode)}")

        if data.OrderInfo:
            self.update_order(data.OrderInfo)

    def onRspQryFill(
        self,
        session: int,
        error: int,
        last: str,
        data: dict
    ) -> None:
        """
        Callback of today's order fill (trade) query.
        """
        if error != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"查询成交信息失败")
            return

        if data:
            self.update_trade(data)

        if last == "Y":
            self.gateway.write_log(f"查询成交信息成功")

    def onRtnFill(self, data: dict) -> None:
        """
        Callback of trade update.
        """
        self.update_trade(data)

    def onRspOrderAction(
        self,
        session: int,
        error: int,
        data: dict
    ) -> None:
        """
        Callback of order action (cancel/amend) request.
        """
        if error != ERROR_VT2TAP["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"委托操作失败：{error_to_str(error)}")
            return

    def update_account(self, data: dict) -> None:
        """
        Convert TAP fund data structure into AccountData event and push it.
        """
        self.account_no = data.AccountNo

        account = AccountData(
            accountid=data.AccountNo,
            balance=data.Balance,
            frozen=data.Balance - data.Available,
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

    def update_position(self, data: dict) -> None:
        """
        Convert TAP position summary structure into PositionData event and push it.
        """
        position = PositionData(
            symbol=data.CommodityNo + data.ContractNo,
            exchange=EXCHANGE_TAP2VT.get(data.ExchangeNo, None),
            direction=DIRECTION_TAP2VT[data.MatchSide],
            volume=data.PositionQty,
            price=data.PositionPrice,
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(position)

    def update_order(self, data: dict) -> None:
        """
        Convert TAP order data structure into OrderData event and push it.
        """
        self.local_sys_map[data.ClientOrderNo] = data.OrderNo
        self.sys_local_map[data.OrderNo] = data.ClientOrderNo
        self.sys_server_map[data.OrderNo] = data.ServerFlag

        order = OrderData(
            symbol=data.CommodityNo + data.ContractNo,
            exchange=EXCHANGE_TAP2VT.get(data.ExchangeNo, None),
            orderid=data.ClientOrderNo,
            type=ORDERTYPE_TAP2VT.get(data.OrderType, data.OrderType),
            direction=DIRECTION_TAP2VT[data.OrderSide],
            price=data.OrderPrice,
            volume=data.OrderQty,
            traded=data.OrderMatchQty,
            status=STATUS_TAP2VT.get(data.OrderState, Status.SUBMITTING),
            time=data.OrderInsertTime,
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)

        # Send waiting cancel request to server
        if data.ClientOrderNo in self.cancel_reqs:
            req = self.cancel_reqs.pop(data.ClientOrderNo)
            self.cancel_order(req)

    def update_trade(self, data: dict) -> None:
        """
        Convert TAP fill data structure into TradeData event and push it.
        """
        orderid = self.sys_local_map[data.OrderNo]

        trade = TradeData(
            symbol=data.CommodityNo + data.ContractNo,
            exchange=EXCHANGE_TAP2VT.get(data.ExchangeNo, None),
            orderid=orderid,
            tradeid=data.MatchNo,
            direction=DIRECTION_TAP2VT[data.MatchSide],
            price=data.MatchPrice,
            volume=data.MatchQty,
            time=data.MatchDateTime,
            gateway_name=self.gateway_name
        )
        self.gateway.on_trade(trade)

    def connect(
        self,
        username: str,
        password: str,
        host: str,
        port: int,
        auth_code: str
    ) -> None:
        """
        Starting connection to TAP server.
        """
        # General API setting
        path = get_folder_path(self.gateway_name.lower())
        self.setITapTradeAPIDataPath(str(path))

        self.setITapTradeAPILogLevel(LOGLEVEL_VT2TAP["APILOGLEVEL_NONE"])

        # Create API object
        data = self.tapTradeAPIApplicationInfo()
        data.AuthCode = auth_code
        data.KeyOperationLogPath = str(path)

        self.api, iResult = self.createITapTradeAPI(data)
        if not self.api:
            self.gateway.write_log("交易API初始化失败")
            return

        # Set server address and port
        self.setAPINotify(self)
        self.setHostAddress(host, port, False)

        # Start connection
        login_auth = self.tapAPITradeLoginAuth()
        login_auth.UserNo = username
        login_auth.Password = password
        login_auth.ISModifyPassword = FLAG_VT2TAP["APIYNFLAG_NO"]

        self.Login(login_auth)

    def send_order(self, req: OrderRequest) -> str:
        """
        Send new order to TAP server.
        """
        contract_info = contract_infos.get((req.symbol, req.exchange), None)
        if not contract_info:
            self.write_log(f"找不到匹配的合约：{req.symbol}和{req.exchange.value}")
            return ""

        if req.type not in ORDERTYPE_VT2TAP:
            self.write_log(f"不支持的委托类型: {req.type.value}")
            return ""

        order_req = self.tapAPINewOrder()
        order_req.ExchangeNo = contract_info.exchange_no
        order_req.CommodityNo = contract_info.commodity_no
        order_req.CommodityType = contract_info.commodity_type
        order_req.ContractNo = contract_info.contract_no
        order_req.OrderType = ORDERTYPE_VT2TAP[req.type]
        order_req.OrderSide = DIRECTION_VT2TAP[req.direction]
        order_req.OrderPrice = req.price
        order_req.OrderQty = int(req.volume)
        order_req.AccountNo = self.account_no

        retv, session_id, order_id = self.insertOrder(order_req)

        order = req.create_order_data(
            order_id,
            self.gateway_name
        )
        self.gateway.on_order(order)

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest) -> None:
        """
        Cancel an existing order.

        If LocalOrderNo/OrderNo map is not ready yet (from query or update callback),
        the cancel request will be put into cancel_reqs dict waiting.
        """
        order_no = self.local_sys_map.get(req.orderid, "")
        if not order_no:
            self.cancel_reqs[req.orderid] = req
            return

        server_flag = self.sys_server_map[order_no]

        cancel_req = self.apAPIOrderCancelReq()
        cancel_req.OrderNo = order_no
        cancel_req.ServerFlag = server_flag

        self.cancelOrder(cancel_req)

    def query_account(self) -> None:
        """
        Query account number data (and account fund data will be auto queried in callback).
        """
        req = self.apAPIAccQryReq()
        self.qryAccount(req)

    def query_position(self) -> None:
        """
        Query position summary.
        """
        req = self.tapAPIPositionQryReq()
        self.qryPositionSummary(req)

    def query_order(self) -> None:
        """
        Query today order data.
        """
        req = self.tapAPIOrderQryReq()
        self.QryOrder(req)

    def query_trade(self) -> None:
        """
        Query today trade data.
        """
        req = self.tapAPIFillQryReq()
        self.qryFill(req)

    def close(self) -> None:
        """
        Release TAP API resources.
        """
        if self.api:
            self.setAPINotify(None)
            self.freeITapTradeAPI(self.api)
            self.api = None


def parse_datetime(dt_str: str) -> datetime:
    """
    Convert timestamp string to datetime object.
    """
    try:
        dt = datetime.strptime(dt_str, "%Y-%m-%d %H:%M:%S.%f")
    except ValueError:
        dt = datetime(1970, 1, 1)
    return dt


def error_to_str(err_code: int) -> str:
    """
    Convert error code to error message string.
    """
    try:
        return error_map[err_code]
    except KeyError:
        return f"Unknown error({err_code})"


@dataclass
class ContractInfo:
    """
    For storing extra data of contract from TAP trading server.
    """
    name: str
    exchange_no: str
    commodity_type: int
    commodity_no: str
    contract_no: str


@dataclass
class CommodityInfo:
    """
    For storing extra data of commodity from TAP trading server.
    """
    name: str
    size: int
    pricetick: float
