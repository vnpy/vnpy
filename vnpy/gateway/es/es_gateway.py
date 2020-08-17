from dataclasses import dataclass
from datetime import datetime
from typing import Dict, Tuple
import pytz

from vnpy.api.es import MdApi, TdApi
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

PRODUCT_TYPE_ES2VT: Dict[str, Product] = {
    "P": Product.SPOT,
    "F": Product.FUTURES,
    "O": Product.OPTION,
    "Z": Product.INDEX,
    "T": Product.EQUITY,
}

EXCHANGE_ES2VT: Dict[str, Exchange] = {
    "CFFEX": Exchange.CFFEX,
    "SGE": Exchange.SGE,
    "SHFE": Exchange.SHFE,
    "ZCE": Exchange.CZCE,   #
    "DCE": Exchange.DCE,
    "INE": Exchange.INE
}

EXCHANGE_VT2ES: Dict[Exchange, str] = {v: k for k, v in EXCHANGE_ES2VT.items()}

DIRECTION_ES2VT: Dict[str, Direction] = {
    "N": Direction.NET,
    "B": Direction.LONG,
    "S": Direction.SHORT,
}
DIRECTION_VT2ES: Dict[Direction, str] = {
    v: k for k, v in DIRECTION_ES2VT.items()}

STATUS_ES2VT: Dict[str, Status] = {
    "0": Status.SUBMITTING,
    "1": Status.SUBMITTING,
    "4": Status.NOTTRADED,
    "5": Status.PARTTRADED,
    "6": Status.ALLTRADED,
    "7": Status.CANCELLED,
    "9": Status.CANCELLED,
}

ORDERTYPE_ES2VT: Dict[str, OrderType] = {
    "1": OrderType.MARKET,
    "2": OrderType.LIMIT
}
ORDERTYPE_VT2ES = {v: k for k, v in ORDERTYPE_ES2VT.items()}

ERROR_VT2ES: Dict[str, int] = {
    "TAPIERROR_SUCCEED": 0    #成功
}
#
LOGLEVEL_VT2TAP: Dict[str, str] = {
    "APILOGLEVEL_NONE": "N",  
    "APILOGLEVEL_ERROR": "E",
    "APILOGLEVEL_WARNING": "W",
    "APILOGLEVEL_DEBUG": "D"
}
LOGLEVEL_VT2ES: Dict[str, str] = {
    "APILOGLEVEL_ERROR": "1",
    "APILOGLEVEL_WARNING": "2",
    "APILOGLEVEL_DEBUG": "3"
}

commodity_infos: Dict[str, "CommodityInfo"] = {}
contract_infos: Dict[Tuple[str, "Exchange"], "ContractInfo"] = {}

#=
FLAG_VT2TAP: Dict[str, str] = {
    "APIYNFLAG_YES": "Y",
    "APIYNFLAG_NO": "N",
    "TAPI_CALLPUT_FLAG_CALL": "C",
    "TAPI_CALLPUT_FLAG_PUT": "P",
    "TAPI_CALLPUT_FLAG_NONE": "N"
}


UserType_VT2ES: Dict[str, int] = {
    "TAPI_USERTYPE_TRADER": 30000
}
NoticeIgnoreFlag_VT2ES: Dict[str, int] = {
    "TAPINoticeIgnoreFlagType": 0x00000000,
    "TAPI_NOTICE_IGNORE_FUND": 0x00000001,
    "TAPI_NOTICE_IGNORE_POSITIONPROFIT": 0x00000020,
    "TAPINoticeIgnoreFlagType": 0xFFFFFFFF
}
CHINA_TZ = pytz.timezone("Asia/Shanghai")


class EsGateway(BaseGateway):
    """
    VN Trader gateway for Esunny(new version) 9.0.
    """

    default_setting = {
        "行情账号": "Q497525430",
        "行情密码": "797878",
        "行情服务器": "61.163.243.173",
        "行情端口": 6161,
        "交易账号": "Q497525430",
        "交易密码": "797878",
        "交易服务器": "61.163.243.173",
        "交易端口": 6160,
        "授权码": "Demo_TestCollect"
    }

    exchanges = list(EXCHANGE_VT2ES.keys())

    def __init__(self, event_engine: EventEngine):
        """"""
        super().__init__(event_engine, "ES")

        self.md_api = QuoteApi(self)
        self.td_api = EsTradeApi(self)

    def connect(self, setting: dict) -> None:
        """"""
        quote_username = setting["行情账号"]
        quote_password = setting["行情密码"]
        quote_host = setting["行情服务器"]
        quote_port = setting["行情端口"]
        trade_username = setting["交易账号"]
        trade_password = setting["交易密码"]
        trade_host = setting["交易服务器"]
        trade_port = setting["交易端口"]
        auth_code = setting["授权码"]

        self.md_api.connect(
            quote_username,
            quote_password,
            quote_host,
            quote_port,
            auth_code
        )
        self.td_api.connect(
            trade_username,
            trade_password,
            trade_host,
            trade_port,
            auth_code
        )

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
        pass

    def query_position(self) -> None:
        """"""
        pass


class QuoteApi(MdApi):
    """
    Implementation of TAP quote api.
    """

    def __init__(self, gateway: EsGateway):
        """"""
        super().__init__()

        self.gateway: EsGateway = gateway
        self.gateway_name: str = gateway.gateway_name

    def onRspLogin(self, error: int, data: dict) -> None:
        """
        Callback of login request.
        """
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"行情服务器登录失败：{error}")
        else:
            self.gateway.write_log("行情服务器登录成功")

    def onAPIReady(self) -> None:
        """
        Callback when API is ready for sending requests or queries.
        """
        pass

    def onDisconnect(self, reason: int) -> None:
        """
        Callback when connection to ES server is lost.
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
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"订阅行情失败：{error}")
        else:
            self.update_tick(data)

    def onRtnQuote(self, data: dict) -> None:
        """
        Callback of new data update.
        """
        self.update_tick(data)

    def update_tick(self, data: dict) -> None:
        """
        Convert ES quote data structure into TickData event and push it.
        """
        symbol = data["CommodityNo"] + data["ContractNo1"]
        exchange = EXCHANGE_ES2VT[data["ExchangeNo"]]

        contract_info = contract_infos.get((symbol, exchange), None)
        if not contract_info:
            self.gateway.write_log(f"行情合约信息无法匹配：{symbol}和{exchange}")
            return

        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=generate_datetime(data["DateTimeStamp"]),
            name=contract_info.name,
            volume=data["QTotalQty"],
            last_price=data["QLastPrice"],
            last_volume=data["QLastQty"],
            limit_up=data["QLimitUpPrice"],
            limit_down=data["QLimitDownPrice"],
            open_price=data["QOpeningPrice"],
            high_price=data["QHighPrice"],
            low_price=data["QLowPrice"],
            pre_close=data["QPreClosingPrice"],
            bid_price_1=data["QBidPrice"][0],
            bid_price_2=data["QBidPrice"][1],
            bid_price_3=data["QBidPrice"][2],
            bid_price_4=data["QBidPrice"][3],
            bid_price_5=data["QBidPrice"][4],
            ask_price_1=data["QAskPrice"][0],
            ask_price_2=data["QAskPrice"][1],
            ask_price_3=data["QAskPrice"][2],
            ask_price_4=data["QAskPrice"][3],
            ask_price_5=data["QAskPrice"][4],
            bid_volume_1=data["QBidQty"][0],
            bid_volume_2=data["QBidQty"][1],
            bid_volume_3=data["QBidQty"][2],
            bid_volume_4=data["QBidQty"][3],
            bid_volume_5=data["QBidQty"][4],
            ask_volume_1=data["QAskQty"][0],
            ask_volume_2=data["QAskQty"][1],
            ask_volume_3=data["QAskQty"][2],
            ask_volume_4=data["QAskQty"][3],
            ask_volume_5=data["QAskQty"][4],
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
        Starting connection to ES server.
        """
        self.init()
        # General API setting
        path = get_folder_path(self.gateway_name.lower())
        self.setTapQuoteAPIDataPath(str(path))
        self.setTapQuoteAPILogLevel(LOGLEVEL_VT2TAP["APILOGLEVEL_NONE"])

        # Create API object
        req = {
            "AuthCode": auth_code,
            "KeyOperationLogPath": str(path)
        }
        self.createTapQuoteAPI(req, 0)

        # Set server address and port
        self.setHostAddress(host, port)

        # Start connection
        data = {
            "UserNo": username,
            "Password": password,
            "ISModifyPassword": FLAG_VT2TAP["APIYNFLAG_NO"],
            "ISDDA": FLAG_VT2TAP["APIYNFLAG_NO"]
        }
        self.login(data)

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to new market data update.
        """
        contract_info = contract_infos.get((req.symbol, req.exchange), None)
        if not contract_info:
            self.gateway.write_log(
                f"找不到匹配的合约：{req.symbol}和{req.exchange.value}")
            return

        es_contract = {
            "ExchangeNo": EXCHANGE_VT2ES[req.exchange],
            "CommodityType": contract_info.commodity_type,
            "CommodityNo": contract_info.commodity_no,
            "ContractNo1": contract_info.contract_no,
            "CallOrPutFlag1": FLAG_VT2TAP["TAPI_CALLPUT_FLAG_NONE"],
            "CallOrPutFlag2": FLAG_VT2TAP["TAPI_CALLPUT_FLAG_NONE"]
        }

        self.subscribeQuote(tap_contract)


class EsTradeApi(TdApi):
    """
    Implementation of ES trade api.
    """

    def __init__(self, gateway: EsGateway):
        """"""
        super().__init__()

        self.gateway: EspGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.account_no = ""        # required when sending order request
        self.cancel_reqs = {}       # waiting cancel order requests before OrderNo received

        # for mapping relationship between ES OrderNo and ClientOrderNo
        self.sys_local_map = {}
        self.local_sys_map = {}
        self.sys_server_map = {}

    def onConnect(self) -> None:
        """
        Callback when connection is established with ES server.
        """
        self.gateway.write_log("交易服务器连接成功")

    def onRspLogin(self, error: int, data: dict) -> None:
        """
        Callback of login request.
        """
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"交易服务器登录失败，错误码：{error}")
        else:
            self.gateway.write_log("交易服务器登录成功")

    def onAPIReady(self, code: int) -> None:
        """
        Callback when API is ready for sending requests or queries.
        """
        for j in range(1, 180):
            tuple_commodity = self.getCommodity(username, j, 1)
            session = tuple_commodity[0]
            error = tuple_commodity[1]
            data = tuple_commodity[2]
            last = tuple_commodity[3]
       
            if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
                self.gateway.write_log("查询交易品种信息失败")
                return

            commodity_info = CommodityInfo(
                name=data["CommodityName"],       
                size=int(data["ContractSize"]),
                pricetick=data["CommodityTickSize"]
            )
            commodity_infos[data["CommodityNo"]] = commodity_info

            if last == "Y":
                self.gateway.write_log("查询交易品种信息成功")
                print("get commodity ok")
                req = {}
                self.onRspQryContract(req)

    # def onRspQryCommodity(
    #     self,
    #     session: int,
    #     error: int,
    #     last: str,
    #     data: dict,
    # ) -> None:
    #     """
    #     Callback of commodity query with size and pricetick data.
    #     """
    #     if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
    #         self.gateway.write_log("查询交易品种信息失败")
    #         return

    #     commodity_info = CommodityInfo(
    #         name=data["CommodityEngName"],
    #         size=int(data["ContractSize"]),
    #         pricetick=data["CommodityTickSize"]
    #     )
    #     commodity_infos[data["CommodityNo"]] = commodity_info

    #     if last == "Y":
    #         self.gateway.write_log("查询交易品种信息成功")
            
    #         self.onRspQryContract(req)

    def onRspQryContract(
        self,
        req

    ) -> None:
        req = {}
        for j in range(1, 180):
            tuple_contract = self.getContract(username, req, j, 1)

            session = tuple_contract[0]
            error = tuple_contract[1]
            data = tuple_contract[2]
            last = tuple_contract[3]

        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
            self.gateway.write_log("查询交易合约信息失败")
            return

        exchange = EXCHANGE_ES2VT.get(data["ExchangeNo"], None)
        commodity_info = commodity_infos.get(data["CommodityNo"], None)

        if not data or not exchange or not commodity_info:
            return

        if data["CommodityType"] == "F":
            symbol = data["CommodityNo"] + data["ContractNo1"]

            if commodity_info.name:
                name = f"{commodity_info.name} {data['ContractNo1']}"
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
                exchange_no=data["ExchangeNo"],
                contract_no=data["ContractNo1"],
                commodity_type=data["CommodityType"],
                commodity_no=data["CommodityNo"],
            )
            contract_infos[(contract.symbol, contract.exchange)
                           ] = contract_info

        if last == "Y":
            self.gateway.write_log("查询交易合约信息成功")
            self.query_account()

    def onRtnPositionProfit(self, data: dict) -> None:
        """"""
        pass

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
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"查询账号信息失败")
            return

        req = {
            "AccountNo": data["AccountNo"]
        }
        self.qryFund(req)

    def onRspQryFund(
        self,
        session: int,
        error: int,
        last: str,
        data: dict
    ) -> None:
        """Callback of account fund query"""
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
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
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
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
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
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
        if data["ErrorCode"] != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"委托下单失败，错误码: {data['ErrorCode']}")
            return

        self.update_order(data)

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
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
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
        if error != ERROR_VT2ES["TAPIERROR_SUCCEED"]:
            self.gateway.write_log(f"委托操作失败：{error}")
            return

    def update_account(self, data: dict) -> None:
        """
        Convert ES fund data structure into AccountData event and push it.
        """
        self.account_no = data["AccountNo"]

        account = AccountData(
            accountid=data["AccountNo"],
            balance=data["Balance"],
            frozen=data["Balance"] - data["Available"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

    def update_position(self, data: dict) -> None:
        """
        Convert ES position summary structure into PositionData event and push it.
        """
        position = PositionData(
            symbol=data["CommodityNo"] + data["ContractNo"],
            exchange=EXCHANGE_ES2VT.get(data["ExchangeNo"], None),
            direction=DIRECTION_ES2VT[data["MatchSide"]],
            volume=data["PositionQty"],
            price=data["PositionPrice"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(position)

    def update_order(self, data: dict) -> None:
        """
        Convert ES order data structure into OrderData event and push it.
        """
        self.local_sys_map[data["ClientOrderNo"]] = data["OrderNo"]
        self.sys_local_map[data["OrderNo"]] = data["ClientOrderNo"]
        self.sys_server_map[data["OrderNo"]] = data["ServerFlag"]

        order = OrderData(
            symbol=data["CommodityNo"] + data["ContractNo"],
            exchange=EXCHANGE_ES2VT.get(data["ExchangeNo"], None),
            orderid=data["ClientOrderNo"],
            type=ORDERTYPE_ES2VT.get(data["OrderType"], data["OrderType"]),
            direction=DIRECTION_ES2VT[data["OrderSide"]],
            price=data["OrderPrice"],
            volume=data["OrderQty"],
            traded=data["OrderMatchQty"],
            status=STATUS_ES2VT.get(data["OrderState"], Status.SUBMITTING),
            datetime=generate_datetime(data["OrderInsertTime"]),
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)

        # Send waiting cancel request to server
        if data["ClientOrderNo"] in self.cancel_reqs:
            req = self.cancel_reqs.pop(data["ClientOrderNo"])
            self.cancel_order(req)

    def update_trade(self, data: dict) -> None:
        """
        Convert ES fill data structure into TradeData event and push it.
        """
        orderid = self.sys_local_map[data["OrderNo"]]

        trade = TradeData(
            symbol=data["CommodityNo"] + data["ContractNo"],
            exchange=EXCHANGE_ES2VT.get(data["ExchangeNo"], None),
            orderid=orderid,
            tradeid=data["MatchNo"],
            direction=DIRECTION_ES2VT[data["MatchSide"]],
            price=data["MatchPrice"],
            volume=data["MatchQty"],
            datetime=generate_datetime(data["MatchDateTime"]),
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
        Starting connection to ES server.
        """
        self.init()

        # General API setting
        path = get_folder_path(self.gateway_name.lower())
        #self.setEsTradeAPIDataPath(str(path))
        #self.setEsTradeAPILogLevel(LOGLEVEL_VT2ES["APILOGLEVEL_ERROR"])

        # Create API object
        req = {
            "AuthCode": auth_code,
            "KeyOperationLogPath": str(path)
        }
        self.createEsTradeAPI()  # 原生函数有一个返回值nResult

        # Set server address and port

        SystemType_VT2ES: Dict[str, int] = {
            "TAPI_SYSTEM_TYPE_ESUNNY": 1
        }
        LoginType_VT2ES: Dict[str, int] = {
            "TAPI_LOGINTYPE_NORMAL": 1
        }
        req = {
            "SystemType": SystemType_VT2ES["TAPI_SYSTEM_TYPE_ESUNNY"],
            "UserNo": username,
            "LoginIP": host,
            "LoginProt": port,
            "LoginType": LoginType_VT2ES["TAPI_LOGINTYPE_NORMAL"]
        }
        self.setUserInfo(req)

        # Start connection
        data = {
            "UserNo": username,
            "UserType": UserType_VT2ES["TAPI_USERTYPE_TRADER"],
            "AuthCode": auth_code,
            "AppID": auth_code,
            "Password": password,
            "ISModifyPassword": "N",
            "ISDDA": "N",
            "NoticeIgnoreFlag": NoticeIgnoreFlag_VT2ES["TAPI_NOTICE_IGNORE_POSITIONPROFIT"]
        }
        self.startUser(username,data)
        print("connect td")

    def send_order(self, req: OrderRequest) -> str:
        """
        Send new order to ES server.
        """
        contract_info = contract_infos.get((req.symbol, req.exchange), None)
        if not contract_info:
            self.gateway.write_log(
                f"找不到匹配的合约：{req.symbol}和{req.exchange.value}")
            return ""

        if req.type not in ORDERTYPE_VT2ES:
            self.gateway.write_log(f"不支持的委托类型: {req.type.value}")
            return ""

        order_req = {
            "AccountNo": self.account_no,
            "ExchangeNo": contract_info.exchange_no,
            "CommodityType": contract_info.commodity_type,
            "CommodityNo": contract_info.commodity_no,
            "ContractNo": contract_info.contract_no,
            "OrderType": ORDERTYPE_VT2ES[req.type],
            "OrderSide": DIRECTION_VT2ES[req.direction],
            "OrderPrice": req.price,
            "OrderQty": int(req.volume),
        }

        error_id, sesion, order_id = self.insertOrder(order_req)

        if not order_id:
            self.gateway.write_log(f"委托请求失败，错误号：{error_id}")
            return

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

        cancel_req = {
            "OrderNo": order_no,
            "ServerFlag": server_flag,
        }

        self.cancelOrder(cancel_req)

    def query_account(self) -> None:
        """
        Query account number data (and account fund data will be auto queried in callback).
        """
        self.qryAccount({})

    def query_position(self) -> None:
        """
        Query position summary.
        """
        self.qryPositionSummary({})

    def query_order(self) -> None:
        """
        Query today order data.
        """
        self.qryOrder({})

    def query_trade(self) -> None:
        """
        Query today trade data.
        """
        self.qryFill({})


def generate_datetime(timestamp: str) -> datetime:
    """
    Convert timestamp string to datetime object.
    """
    if "-" in timestamp:
        if "." in timestamp:
            dt = datetime.strptime(timestamp, "%Y-%m-%d %H:%M:%S.%f")
        else:
            dt = datetime.strptime(timestamp, "%Y-%m-%d %H:%M:%S")
    else:
        dt = datetime.strptime(timestamp, "%y%m%d%H%M%S.%f")

    dt = dt.replace(tzinfo=CHINA_TZ)
    return dt


@dataclass
class ContractInfo:
    """
    For storing extra data of contract from ES trading server.
    """
    name: str
    exchange_no: str
    commodity_type: int
    commodity_no: str
    contract_no: str


@dataclass
class CommodityInfo:
    """
    For storing extra data of commodity from ES trading server.
    """
    name: str
    size: int
    pricetick: float
