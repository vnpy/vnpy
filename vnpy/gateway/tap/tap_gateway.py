from dataclasses import dataclass
from datetime import datetime

from vnpy.api.tap.vntap import (
    APIYNFLAG_NO, AsyncDispatchException, CreateTapQuoteAPI,
    FreeTapQuoteAPI, ITapQuoteAPINotify,
    TAPIERROR_SUCCEED, TAPI_CALLPUT_FLAG_NONE,
    TAPI_COMMODITY_TYPE_FUTURES, TAPI_COMMODITY_TYPE_INDEX,
    TAPI_COMMODITY_TYPE_OPTION, TAPI_COMMODITY_TYPE_SPOT,
    TAPI_COMMODITY_TYPE_STOCK, TapAPIApplicationInfo, TapAPIContract,
    TapAPIQuotLoginRspInfo, TapAPIQuoteLoginAuth, TapAPIQuoteWhole,
    set_async_callback_exception_handler,
    CreateITapTradeAPI
)
from vnpy.api.tap.vntap.ITapTrade import (
    ITapTradeAPINotify,
    TapAPITradeLoginRspInfo, TapAPICommodityInfo, TapAPITradeContractInfo,
    TapAPIApplicationInfo as TapTradeAPIApplicationInfo,
    TapAPITradeLoginAuth, TapAPIAccQryReq, TapAPIFundReq,
    TapAPIAccountInfo, TapAPIFundData,
    TapAPIPositionQryReq, TapAPIPositionInfo,
    TapAPIOrderQryReq, TapAPIFillQryReq,
    TapAPIOrderInfo, TapAPIFillInfo,
    TapAPINewOrder, TapAPIOrderCancelReq,
    TAPI_SIDE_NONE, TAPI_SIDE_BUY, TAPI_SIDE_SELL,
    TAPI_ORDER_STATE_QUEUED, TAPI_ORDER_STATE_PARTFINISHED,
    TAPI_ORDER_STATE_FINISHED, TAPI_ORDER_STATE_CANCELED,
    TAPI_ORDER_STATE_SUBMIT, TAPI_ORDER_TYPE_MARKET,
    TAPI_ORDER_TYPE_LIMIT
)
from vnpy.api.tap.error_codes import error_map

from vnpy.event import EventEngine
from vnpy.trader.constant import Exchange, Product, Direction, Status, OrderType
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

PRODUCT_TYPE_TAP2VT = {
    TAPI_COMMODITY_TYPE_SPOT: Product.SPOT,
    TAPI_COMMODITY_TYPE_FUTURES: Product.FUTURES,
    TAPI_COMMODITY_TYPE_OPTION: Product.OPTION,
    TAPI_COMMODITY_TYPE_INDEX: Product.INDEX,
    TAPI_COMMODITY_TYPE_STOCK: Product.EQUITY,
}

EXCHANGE_TAP2VT = {
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
EXCHANGE_VT2TAP = {v: k for k, v in EXCHANGE_TAP2VT.items()}

DIRECTION_TAP2VT = {
    TAPI_SIDE_NONE: Direction.NET,
    TAPI_SIDE_BUY: Direction.LONG,
    TAPI_SIDE_SELL: Direction.SHORT,
}
DIRECTION_VT2TAP = {v: k for k, v in DIRECTION_TAP2VT.items()}

STATUS_TAP2VT = {
    TAPI_ORDER_STATE_SUBMIT: Status.SUBMITTING,
    TAPI_ORDER_STATE_QUEUED: Status.NOTTRADED,
    TAPI_ORDER_STATE_PARTFINISHED: Status.PARTTRADED,
    TAPI_ORDER_STATE_FINISHED: Status.ALLTRADED,
    TAPI_ORDER_STATE_CANCELED: Status.CANCELLED
}

ORDERTYPE_TAP2VT = {
    TAPI_ORDER_TYPE_LIMIT: OrderType.LIMIT,
    TAPI_ORDER_TYPE_MARKET: OrderType.MARKET,
}
ORDERTYPE_VT2TAP = {v: k for k, v in ORDERTYPE_TAP2VT.items()}


commodity_infos = {}
contract_infos = {}


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

        self.quote_api = QuoteApi(self)
        self.trade_api = TradeApi(self)

        set_async_callback_exception_handler(
            self._async_callback_exception_handler)

    def connect(self, setting: dict):
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

        self.trade_api.connect(
            trade_username,
            trade_password,
            trade_host,
            trade_port,
            auth_code
        )
        self.quote_api.connect(
            quote_username,
            quote_password,
            quote_host,
            quote_port,
            auth_code
        )

    def close(self):
        """"""
        self.trade_api.close()
        self.quote_api.close()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.quote_api.subscribe(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self.trade_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.trade_api.cancel_order(req)

    def query_account(self):
        """"""
        pass

    def query_position(self):
        """"""
        pass

    def _async_callback_exception_handler(self, e: AsyncDispatchException):
        """"""
        error_str = (f"发生内部错误，位置：\n{e.instance}.{e.function_name}，详细信息：\n"
                     f"{e.what}\n"
                     )
        print(error_str)
        self.write_log(error_str)
        return True


class QuoteApi(ITapQuoteAPINotify):
    """"""

    def __init__(self, gateway: TapGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.api = None

    def OnRspLogin(self, errorCode: int, info: TapAPIQuotLoginRspInfo):
        """"""
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log("行情服务器登录失败")
        else:
            self.gateway.write_log("行情服务器登录成功")

    def OnAPIReady(self):
        """"""
        self.api.QryCommodity()

    def OnDisconnect(self, reasonCode: int):
        """"""
        self.gateway.write_log(f"行情服务器连接断开，原因：{reasonCode}")

    def OnRspSubscribeQuote(
        self, sessionID: int, errorCode: int, isLast: str, info: TapAPIQuoteWhole
    ):
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log(f"订阅行情失败：{error_to_str(errorCode)}")
        else:
            self.update_tick(info)

    def OnRtnQuote(self, info: TapAPIQuoteWhole):
        """"""
        self.update_tick(info)

    def update_tick(self, info: TapAPIQuoteWhole):
        """"""
        symbol = info.Contract.Commodity.CommodityNo + info.Contract.ContractNo1
        exchange = EXCHANGE_TAP2VT[info.Contract.Commodity.ExchangeNo]

        contract_info = contract_infos.get((symbol, exchange), None)
        if not contract_info:
            self.gateway.write_log(f"行情合约信息无法匹配：{symbol}和{exchange}")
            return

        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=parse_datetime(info.DateTimeStamp),
            name=contract_info.name,
            volume=info.QTotalQty,
            last_price=info.QLastPrice,
            last_volume=info.QLastQty,
            limit_up=info.QLimitUpPrice,
            limit_down=info.QLimitDownPrice,
            open_price=info.QOpeningPrice,
            high_price=info.QHighPrice,
            low_price=info.QLowPrice,
            pre_close=info.QPreClosingPrice,
            bid_price_1=info.QBidPrice[0],
            bid_price_2=info.QBidPrice[1],
            bid_price_3=info.QBidPrice[2],
            bid_price_4=info.QBidPrice[3],
            bid_price_5=info.QBidPrice[4],
            ask_price_1=info.QAskPrice[0],
            ask_price_2=info.QAskPrice[1],
            ask_price_3=info.QAskPrice[2],
            ask_price_4=info.QAskPrice[3],
            ask_price_5=info.QAskPrice[4],
            bid_volume_1=info.QBidQty[0],
            bid_volume_2=info.QBidQty[1],
            bid_volume_3=info.QBidQty[2],
            bid_volume_4=info.QBidQty[3],
            bid_volume_5=info.QBidQty[4],
            ask_volume_1=info.QAskQty[0],
            ask_volume_2=info.QAskQty[1],
            ask_volume_3=info.QAskQty[2],
            ask_volume_4=info.QAskQty[3],
            ask_volume_5=info.QAskQty[4],
            gateway_name=self.gateway_name,
        )
        self.gateway.on_tick(tick)

    def connect(self, username: str, password: str, host: str, port: int, auth_code: str):
        """"""
        # Create API object
        info = TapAPIApplicationInfo()
        info.AuthCode = auth_code

        self.api, iResult = CreateTapQuoteAPI(info)
        if not self.api:
            self.gateway.write_log("行情API初始化失败")
            return

        # Set server address and port
        self.api.SetAPINotify(self)
        self.api.SetHostAddress(host, port)

        # Start connection
        login_auth = TapAPIQuoteLoginAuth()
        login_auth.UserNo = username
        login_auth.Password = password
        login_auth.ISDDA = APIYNFLAG_NO
        login_auth.ISModifyPassword = APIYNFLAG_NO

        self.api.Login(login_auth)

    def close(self):
        """"""
        self.api.SetAPINotify(None)
        FreeTapQuoteAPI(self.api)
        self.api = None

    def subscribe(self, req: SubscribeRequest):
        """"""
        contract_info = contract_infos.get((req.symbol, req.exchange), None)
        if not contract_info:
            self.gateway.write_log(
                f"找不到匹配的合约：{req.symbol}和{req.exchange.value}")
            return

        tap_contract = TapAPIContract()
        tap_contract.Commodity.ExchangeNo = EXCHANGE_VT2TAP[req.exchange]
        tap_contract.Commodity.CommodityType = contract_info.commodity_type
        tap_contract.Commodity.CommodityNo = contract_info.commodity_no
        tap_contract.ContractNo1 = contract_info.contract_no
        tap_contract.CallOrPutFlag1 = TAPI_CALLPUT_FLAG_NONE
        tap_contract.CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE

        self.api.SubscribeQuote(tap_contract)


class TradeApi(ITapTradeAPINotify):
    """"""

    def __init__(self, gateway: TapGateway):
        """"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        self.api = None

    def OnConnect(self):
        """"""
        self.gateway.write_log("交易服务器连接成功")

    def OnRspLogin(self, errorCode: int, info: TapAPITradeLoginRspInfo):
        """"""
        if errorCode != TAPIERROR_SUCCEED:
            error_msg = error_to_str(errorCode)
            self.gateway.write_log(f"交易服务器登录失败：{error_msg}")
        else:
            self.gateway.write_log("交易服务器登录成功")

    def OnAPIReady(self, code: int):
        """"""
        self.api.QryCommodity()

    def OnRspQryCommodity(
        self,
        sessionID: int,
        errorCode: int,
        isLast: str,
        info: TapAPICommodityInfo,
    ):
        """"""
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log("查询交易品种信息失败")
            return

        commodity_info = CommodityInfo(
            name=info.CommodityEngName,
            size=info.ContractSize,
            pricetick=info.CommodityTickSize
        )
        commodity_infos[info.CommodityNo] = commodity_info

        if isLast == "Y":
            self.gateway.write_log("查询交易品种信息成功")
            self.api.QryContract(None)

    def OnRspQryContract(
        self,
        sessionID: int,
        errorCode: int,
        isLast: str,
        info: TapAPITradeContractInfo
    ):
        """"""
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log("查询交易合约信息失败")
            return

        exchange = EXCHANGE_TAP2VT.get(info.ExchangeNo, None)
        commodity_info = commodity_infos.get(info.CommodityNo, None)

        if not info or not exchange or not commodity_info:
            return

        symbol = info.CommodityNo + info.ContractNo1

        if commodity_info.name:
            name = f"{commodity_info.name} {info.ContractNo1}"
        else:
            name = symbol

        contract = ContractData(
            symbol=symbol,
            exchange=exchange,
            name=name,
            product=Product.FUTURES,
            size=commodity_info.size,
            pricetick=commodity_info.pricetick,
            gateway_name=self.gateway.gateway_name
        )
        self.gateway.on_contract(contract)

        contract_info = ContractInfo(
            name=contract.name,
            exchange_no=info.ExchangeNo,
            contract_no=info.ContractNo1,
            commodity_type=info.CommodityType,
            commodity_no=info.CommodityNo,
        )
        contract_infos[(contract.symbol, contract.exchange)] = contract_info

        if isLast == "Y":
            self.gateway.write_log("查询交易合约信息成功")
            self.query_account()

    def OnRspQryAccount(
        self,
        sessionID: int,
        errorCode: int,
        isLast: str,
        info: TapAPIAccountInfo
    ):
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log(f"查询账号信息失败")
            return

        req = TapAPIFundReq()
        req.AccountNo = info.AccountNo
        self.api.QryFund(req)

    def OnRspQryFund(
        self,
        sessionID: int,
        errorCode: int,
        isLast: str,
        info: TapAPIFundData
    ):
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log(f"查询资金信息失败")
            return

        self.update_account(info)

        if isLast == "Y":
            self.gateway.write_log("查询资金信息成功")
            self.query_position()

    def OnRtnFund(self, info: TapAPIFundData):
        """"""
        self.update_account(info)

    def OnRspQryPosition(
        self,
        sessionID: int,
        errorCode: int,
        isLast: str,
        info: TapAPIPositionInfo
    ):
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log(f"查询持仓信息失败")
            return

        if info:
            self.update_position(info)

        if isLast == "Y":
            self.gateway.write_log(f"查询持仓信息成功")
            self.query_order()

    def OnRtnPosition(self, info: TapAPIPositionInfo):
        """"""
        self.update_position(info)

    def OnRspQryOrder(
        self,
        sessionID: int,
        errorCode: int,
        isLast: str,
        info: TapAPIOrderInfo
    ):
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log(f"查询委托信息失败")
            return

        if info:
            self.update_order(info)

        if isLast == "Y":
            self.gateway.write_log(f"查询委托信息成功")
            self.query_trade()

    def OnRtnOrder(self, info: TapAPIOrderInfo):
        """"""
        self.update_order(info)

    def OnRspQryFill(
        self,
        sessionID: int,
        errorCode: int,
        isLast: str,
        info: TapAPIFillInfo
    ):
        if errorCode != TAPIERROR_SUCCEED:
            self.gateway.write_log(f"查询成交信息失败")
            return

        if info:
            self.update_trade(info)

        if isLast == "Y":
            self.gateway.write_log(f"查询成交信息成功")

    def OnRtnFill(self, info: TapAPIFillInfo):
        """"""
        self.update_trade(info)

    def update_account(self, info: TapAPIAccountInfo):
        """"""
        account = AccountData(
            accountid=info.AccountNo,
            balance=info.Balance,
            frozen=info.Balance - info.Available,
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

    def update_position(self, info: TapAPIPositionInfo):
        """"""
        position = PositionData(
            symbol=info.CommodityNo + info.ContractNo,
            exchange=EXCHANGE_TAP2VT.get(info.ExchangeNo, None),
            direction=DIRECTION_TAP2VT[info.MatchSide],
            volume=info.PositionQty,
            price=info.PositionPrice,
            pnl=info.PositionProfit,
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(position)

    def update_order(self, info: TapAPIOrderInfo):
        """"""
        order = OrderData(
            symbol=info.CommodityNo + info.ContractNo,
            exchange=EXCHANGE_TAP2VT.get(info.ExchangeNo, None),
            orderid=info.OrderNo,
            type=ORDERTYPE_TAP2VT[info.OrderType],
            direction=DIRECTION_TAP2VT[info.OrderSide],
            price=info.OrderPrice,
            volume=info.OrderQty,
            traded=info.OrderMatchQty,
            status=STATUS_TAP2VT[info.OrderState],
            time=info.OrderInsertTime,
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)

    def update_trade(self, info: TapAPIFillInfo):
        """"""
        trade = TradeData(
            symbol=info.CommodityNo + info.ContractNo,
            exchange=EXCHANGE_TAP2VT.get(info.ExchangeNo, None),
            orderid=info.OrderNo,
            tradeid=info.MatchNo,
            direction=DIRECTION_TAP2VT[info.MatchSide],
            price=info.MatchPrice,
            volume=info.MatchQty,
            time=info.MatchDateTime,
            gateway_name=self.gateway_name
        )
        self.gateway.on_trade(trade)

    def connect(self, username: str, password: str, host: str, port: int, auth_code: str):
        """"""
        # Create API object
        info = TapTradeAPIApplicationInfo()
        info.AuthCode = auth_code

        self.api, iResult = CreateITapTradeAPI(info)
        if not self.api:
            self.gateway.write_log("交易API初始化失败")
            return

        # Set server address and port
        self.api.SetAPINotify(self)
        self.api.SetHostAddress(host, port, False)

        # Start connection
        login_auth = TapAPITradeLoginAuth()
        login_auth.UserNo = username
        login_auth.Password = password
        login_auth.ISModifyPassword = APIYNFLAG_NO

        self.api.Login(login_auth)

    def send_order(self, req: OrderRequest):
        """"""
        contract_info = contract_infos.get((req.symbol, req.exchange), None)
        if not contract_info:
            self.write_log(f"找不到匹配的合约：{req.symbol}和{req.exchange.value}")
            return ""

        order_req = TapAPINewOrder()
        order_req.ExchangeNo = contract_info.ExchangeNo
        order_req.CommodityNo = contract_info.CommodityNo
        order_req.ContractNo = contract_info.ContractNo
        order_req.OrderType = ORDERTYPE_VT2TAP.get(OrderRequest.type, "")
        order_req.OrderSide = DIRECTION_VT2TAP.get(OrderRequest.direction, "")
        order_req.OrderPrice = req.price
        order_req.OrderQty = req.volume

        session_id, order_id = self.api.InsertOrder(order_req)

        order = req.create_order_data(
            order_id,
            self.gateway_name
        )
        self.gateway.on_order(order)

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        cancel_req = TapAPIOrderCancelReq()

        self.api.CancelOrder(cancel_req)

    def query_account(self):
        """"""
        req = TapAPIAccQryReq()
        self.api.QryAccount(req)

    def query_position(self):
        """"""
        req = TapAPIPositionQryReq()
        self.api.QryPosition(req)

    def query_order(self):
        """"""
        req = TapAPIOrderQryReq()
        self.api.QryOrder(req)

    def query_trade(self):
        """"""
        req = TapAPIFillQryReq()
        self.api.QryFill(req)

    def close(self):
        """"""
        self.api.SetAPINotify(None)
        FreeTapQuoteAPI(self.api)
        self.api = None


def parse_datetime(dt_str: str):
    """"""
    try:
        dt = datetime.strptime(dt_str, "%Y-%m-%d %H:%M:%S.%f")
    except ValueError:
        dt = datetime(1970, 1, 1)
    return dt


def error_to_str(err_code: int) -> str:
    """"""
    try:
        return error_map[err_code]
    except KeyError:
        return f"Unknown error({err_code})"


@dataclass
class ContractInfo:
    """"""
    name: str
    exchange_no: str
    commodity_type: int
    commodity_no: str
    contract_no: str


@dataclass
class CommodityInfo:
    """"""
    name: str
    size: int
    pricetick: float
