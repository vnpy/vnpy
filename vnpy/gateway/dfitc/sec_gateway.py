from typing import Any, Dict, List
from datetime import datetime
from copy import copy

from vnpy.event import EventEngine
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.constant import (
    Exchange,
    Product,
    Direction,
    OrderType,
    Status,
    Offset,
    OptionType
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
from vnpy.trader.utility import get_folder_path
from vnpy.api.dfitc import (
    MdApi,
    TdApi,
    DFITCSEC_PQF_Extend,
    DFITCSEC_EI_SH,
    DFITCSEC_EI_SZ,
    DFITCSEC_OT_LimitPrice,
    DFITCSEC_OT_SHBESTFRTradeLeftWithdraw,
    DFITCSEC_SOP_LimitPrice,
    DFITCSEC_SOP_LastPrice,
    DFITCSEC_OCF_Open,
    DFITCSEC_OCF_Close,
    DFITCSEC_ED_Buy,
    DFITCSEC_ED_Sell,
    DFITCSEC_OT_CALL,
    DFITCSEC_OT_PUT

)

EXCHANGE_SEC2VT = {
    DFITCSEC_EI_SH: Exchange.SSE,
    DFITCSEC_EI_SZ: Exchange.SZSE
}
EXCHANGE_VT2SEC: Dict[Exchange, int] = {v: k for k, v in EXCHANGE_SEC2VT.items()}

STOCK_PRICE_TYPE_SEC2VT: Dict[int, OrderType] = {
    DFITCSEC_OT_LimitPrice: OrderType.LIMIT,
    DFITCSEC_OT_SHBESTFRTradeLeftWithdraw: OrderType.MARKET
}
STOCK_PRICE_TYPE_VT2SEC: Dict[OrderType, int] = {v: k for k, v in STOCK_PRICE_TYPE_SEC2VT.items()}

OPTION_PRICE_TYPE_SEC2VT: Dict[int, OrderType] = {
    DFITCSEC_SOP_LimitPrice: OrderType.LIMIT,
    DFITCSEC_SOP_LastPrice: OrderType.MARKET
}
OPTION_PRICE_TYPE_VT2SEC: Dict[OrderType, int] = {v: k for k, v in OPTION_PRICE_TYPE_SEC2VT.items()}

OFFSET_VT2SEC: Dict[Offset, int] = {
    Offset.OPEN: DFITCSEC_OCF_Open,
    Offset.CLOSE: DFITCSEC_OCF_Close,

}
OFFSET_SEC2VT: Dict[int, Offset] = {v: k for k, v in OFFSET_VT2SEC.items()}

DIRECTION_VT2SEC = {
    Direction.LONG: DFITCSEC_ED_Buy,
    Direction.SHORT: DFITCSEC_ED_Sell
}
DIRECTION_SEC2VT: Dict[int, Direction] = {v: k for k, v in DIRECTION_VT2SEC.items()}

symbol_name_map: Dict[str, str] = {}
symbol_pricetick_map: Dict[str, float] = {}


class SecGateway(BaseGateway):
    """
    VN Trader Gateway for sec .
    """

    default_setting: Dict[str, Any] = {
        "账号": "",
        "密码": "",
        "客户号": 1,
        "行情地址": "",
        "交易地址": "",
        "行情协议": ["TCP", "UDP"],
        "授权码": "",
        "产品号": ""
    }

    exchanges: List[Exchange] = list(EXCHANGE_VT2SEC.keys())

    def __init__(self, event_engine: EventEngine):
        """"""
        super().__init__(event_engine, "SEC")

        self.md_api = SecMdApi(self)
        self.td_api = SecTdApi(self)

    def connect(self, setting: dict) -> None:
        """"""
        account_id = setting["账号"]
        password = setting["密码"]
        client_id = int(setting["客户号"])
        md_address = setting["行情地址"]
        td_address = setting["交易地址"]
        quote_protocol = setting["行情协议"]
        auth_code = setting["授权码"]
        appid = setting["产品号"]

        if (
            (not md_address.startswith("tcp://"))
            and (not md_address.startswith("ssl://"))
        ):
            md_address = "tcp://" + md_address

        if (
            (not td_address.startswith("tcp://"))
            and (not td_address.startswith("ssl://"))
        ):
            td_address = "tcp://" + td_address

        if quote_protocol == "UDP":
            md_address = md_address.replace("tcp", "udp")

        self.md_api.connect(
            account_id,
            password,
            client_id,
            md_address,
            auth_code,
            appid
        )
        self.td_api.connect(
            account_id,
            password,
            client_id,
            td_address,
            auth_code,
            appid
        )
        # self.init_query()

    def close(self) -> None:
        """"""
        self.md_api.close()
        self.td_api.close()

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        self.md_api.subscrbie(req)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        return self.td_api.send_order(req)

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        self.td_api.cancel_order(req)

    def query_account(self) -> None:
        """"""
        self.td_api.query_account()

    def query_position(self) -> None:
        """"""
        self.td_api.query_position()

    def process_timer_event(self, event) -> None:
        """"""
        self.count += 1
        if self.count < 2:
            return
        self.count = 0

        func = self.query_functions.pop(0)
        func()
        self.query_functions.append(func)

    def init_query(self) -> None:
        """"""
        self.count = 0
        self.query_functions = [self.query_account, self.query_position]
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def write_error(self, msg: str, error: dict) -> None:
        """"""
        error_id = error["errorID"]
        error_msg = error["errorMsg"]
        msg = f"{msg}，代码：{error_id}，信息：{error_msg}"
        self.write_log(msg)


class SecMdApi(MdApi):

    def __init__(self, gateway: SecGateway):
        """"""
        super().__init__()

        self.gateway: SecGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.account_id: str = ""
        self.password: str = ""
        self.client_id: int = 0
        self.md_address: str = ""
        self.server_port: int = 0
        self.session_id: int = 0

        self.connect_status: bool = False
        self.login_status: bool = False
        self.compressflag: int = 1
        self.auth_code: str = ""
        self.app_id: str = ""
        self.collectInterType: int = 1

        self.reqid: int = 0

        self.connect_status = False
        self.login_status = False
        self.subscribed = set()

        self.sse_inited: bool = False
        self.szse_inited: bool = False

    def onFrontConnected(self):
        """"""
        self.login_server()
        self.connect_status = True

    def onFrontDisconnected(self, reason: int) -> None:
        """"""
        self.connect_status = False
        self.login_status = False
        self.login_status_option = False
        self.gateway.write_log(f"行情服务器连接断开, 原因{reason}")

    def onRspStockUserLogin(self, data: dict, error: dict) -> None:
        if not error:
            self.gateway.write_log("股票行情服务器登录成功")
        else:
            self.gateway.write_error("股票行情服务器登录失败", error)

    def onRspSOPUserLogin(self, data: dict, error: dict) -> None:
        if not error:
            self.gateway.write_log("股票期权行情服务器登录成功")
            self.login_status = True
        else:
            self.gateway.write_error("股票期权行情服务器登录失败", error)

    def onRspError(self, error: dict) -> None:
        """"""
        self.gateway.write_error("行情接口报错", error)

    def onRspStockSubMarketData(self, data: dict, error: dict) -> None:
        """"""
        if not error or not error["errorID"]:
            return

        self.gateway.write_error("股票行情订阅失败", error)

    def onRspSOPSubMarketData(self, data: dict, error: dict) -> None:
        """"""
        if not error or not error["errorID"]:
            return

        self.gateway.write_error("股票期权行情订阅失败", error)

    def onSOPMarketData(self, data: dict) -> None:
        """"""
        timestamp = str(data["tradingDay"]) + str(data["updateTime"])
        dt = datetime.strptime(timestamp, "%Y%m%d%H%M%S%f")

        tick = TickData(
            symbol=data["securityID"],
            exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
            datetime=dt,
            volume=data["tradeQty"],
            last_price=data["latestPrice"],
            limit_up=data["upperLimitPrice"],
            limit_down=data["lowerLimitPrice"],
            open_price=data["openPrice"],
            high_price=data["highestPrice"],
            low_price=data["lowestPrice"],
            pre_close=data["preClosePrice"],
            gateway_name=self.gateway_name
        )
        tick.bid_price_1 = data["bidPrice1"]
        tick.bid_price_2 = data["bidPrice2"]
        tick.bid_price_3 = data["bidPrice3"]
        tick.bid_price_4 = data["bidPrice4"]
        tick.bid_price_5 = data["bidPrice5"]

        tick.ask_price_1 = data["askPrice1"]
        tick.ask_price_2 = data["askPrice2"]
        tick.ask_price_3 = data["askPrice3"]
        tick.ask_price_4 = data["askPrice4"]
        tick.ask_price_5 = data["askPrice5"]

        tick.bid_volume_1 = data["bidQty1"]
        tick.bid_volume_2 = data["bidQty2"]
        tick.bid_volume_3 = data["bidQty3"]
        tick.bid_volume_4 = data["bidQty4"]
        tick.bid_volume_5 = data["bidQty5"]

        tick.ask_volume_1 = data["askQty1"]
        tick.ask_volume_2 = data["askQty2"]
        tick.ask_volume_3 = data["askQty3"]
        tick.ask_volume_4 = data["askQty4"]
        tick.ask_volume_5 = data["askQty5"]

        tick.name = symbol_name_map.get(tick.vt_symbol, tick.symbol)
        self.gateway.on_tick(tick)

    def onStockMarketData(self, data: dict) -> None:
        """"""
        timestamp = str(data["tradingDay"]) + str(data["updateTime"])
        dt = datetime.strptime(timestamp, "%Y%m%d%H%M%S%f")

        tick = TickData(
            symbol=data["securityID"],
            exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
            datetime=dt,
            volume=data["tradeQty"],
            last_price=data["latestPrice"],
            limit_up=data["upperLimitPrice"],
            limit_down=data["lowerLimitPrice"],
            open_price=data["openPrice"],
            high_price=data["highestPrice"],
            low_price=data["lowestPrice"],
            pre_close=data["preClosePrice"],
            gateway_name=self.gateway_name
        )
        tick.bid_price_1 = data["bidPrice1"]
        tick.bid_price_2 = data["bidPrice2"]
        tick.bid_price_3 = data["bidPrice3"]
        tick.bid_price_4 = data["bidPrice4"]
        tick.bid_price_5 = data["bidPrice5"]

        tick.ask_price_1 = data["askPrice1"]
        tick.ask_price_2 = data["askPrice2"]
        tick.ask_price_3 = data["askPrice3"]
        tick.ask_price_4 = data["askPrice4"]
        tick.ask_price_5 = data["askPrice5"]

        tick.bid_volume_1 = data["bidQty1"]
        tick.bid_volume_2 = data["bidQty2"]
        tick.bid_volume_3 = data["bidQty3"]
        tick.bid_volume_4 = data["bidQty4"]
        tick.bid_volume_5 = data["bidQty5"]

        tick.ask_volume_1 = data["askQty1"]
        tick.ask_volume_2 = data["askQty2"]
        tick.ask_volume_3 = data["askQty3"]
        tick.ask_volume_4 = data["askQty4"]
        tick.ask_volume_5 = data["askQty5"]

        tick.name = symbol_name_map.get(tick.vt_symbol, tick.symbol)
        self.gateway.on_tick(tick)

    def onRspStockAvailableQuot(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSopAvailableQuot(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspUserMDPasswordUpdate(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspSOPUnSubMarketData(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspSOPUserLogout(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLUserLogin(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLUserLogout(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspStockUnSubMarketData(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspStockUserLogout(self, data: dict, error: dict) -> None:
        """"""
        pass

    def connect(
        self,
        account_id: str,
        password: str,
        client_id: int,
        md_address: str,
        auth_code,
        appid
    ) -> None:
        """"""
        self.account_id = account_id
        self.password = password
        self.client_id = client_id
        self.md_address = md_address
        self.auth_code = auth_code
        self.app_id = appid

        # Create API object
        if not self.connect_status:
            path = str(get_folder_path(self.gateway_name.lower()))
            self.createDFITCMdApi(path, md_address)
            self.init()

    def login_server(self) -> None:
        """"""
        self.reqid += 1
        data = {
            "requestID": self.reqid,
            "accountID": self.account_id,
            "password": self.password,
            "compressflag": self.compressflag,
            "authenticCode": self.auth_code,
            "appID": self.app_id,
            "collectInterType": self.collectInterType
        }
        n = self.reqStockUserLogin(data)

        self.reqid += 1
        data["requestID"] = self.reqid
        m = self.reqSOPUserLogin(data)

        print("Md login: n, m", n, m)

    def close(self) -> None:
        """"""
        if self.connect_status:
            self.exit()

    def subscrbie(self, req: SubscribeRequest) -> None:
        """"""
        if self.login_status_stock:
            self.reqid += 1

            if check_option_symbol(req.symbol):
                symbol = str(EXCHANGE_VT2SEC[req.exchange] + req.symbol)
                self.subscribeSOPMarketData(symbol, self.reqid)
            else:
                symbol = str(EXCHANGE_VT2SEC[req.exchange] + req.symbol)
                self.subscribeStockMarketData(symbol, self.reqid)

        self.subscribed.add(req)


class SecTdApi(TdApi):

    def __init__(self, gateway: SecGateway):
        """"""
        super().__init__()

        self.gateway: SecGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.account_id: str = ""
        self.password: str = ""
        self.client_id: str = ""
        self.auth_code: str = ""
        self.compressflag: int = 0
        self.auth_code: str = ""
        self.app_id: str = ""
        self.collectInterType: int = 1

        self.session_id: int = 0
        self.reqid: int = 0
        self.localid: int = 10000
        self.orders: Dict[str, OrderData] = {}

        # Whether current account supports margin or option
        self.margin_trading = False
        self.option_trading = False

        self.connect_status: bool = False
        self.login_status: bool = False

    def onFrontConnected(self) -> None:
        """"""
        self.login_server()
        self.connect_status = True

    def onFrontDisconnected(self, reason: int) -> None:
        """"""
        self.connect_status = False
        self.login_status = False
        self.gateway.write_log(f"交易服务器连接断开, 原因{reason}")

    def onRspStockUserLogin(self, data: dict, error: dict) -> None:
        if not error:
            self.gateway.write_log("股票交易服务器登录成功")
        else:
            self.gateway.write_error("股票交易服务器登录失败", error)

    def onRspSOPUserLogin(self, data: dict, error: dict) -> None:
        if not error:
            self.gateway.write_log("股票期权交易服务器登录成功")
            self.login_status = True
        else:
            self.gateway.write_error("股票期权交易服务器登录失败", error)

    def onRspError(self, error: dict) -> None:
        """"""
        self.gateway.write_error("交易接口报错", error)

    def onStockEntrustOrderRtn(self, data: dict) -> None:
        """股票报单回报"""
        # 更新最大报单编号
        new_localid = data["localOrderID"]
        self.localid = max(self.localid, new_localid)

        # 获取报单数据对象
        if new_localid in self.orders:
            order = self.orders[new_localid]
        else:
            order = OrderData(
                symbol=data["securityID"],
                exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
                orderid=str(new_localid),
                direction=DIRECTION_SEC2VT[data["entrustDirection"]],
                price=data["entrustPrice"],
                volume=data["entrustQty"],
                datetime=data["entrustTime"],
                product=Product.EQUITY,
                gateway_name=self.gateway_name
            )
            self.orders[new_localid] = order

        # 确定委托状态
        if order.volume == order.traded:
            order.status = Status.ALLTRADED
        elif order.traded > 0:
            order.status = Status.PARTTRADED
        else:
            order.status = Status.NOTTRADED

        self.gateway.on_order(copy(order))

    def onSOPEntrustOrderRtn(self, data: dict) -> None:
        """期权报单回报"""
        # 更新最大报单编号
        new_localid = data["localOrderID"]
        self.localid = max(self.localid, new_localid)

        # 获取报单数据对象
        if new_localid in self.orders:
            order = self.orders[new_localid]
        else:
            order = OrderData(
                symbol=data["securityID"],
                exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
                orderid=str(new_localid),
                direction=DIRECTION_SEC2VT[data["entrustDirection"]],
                offset=OFFSET_SEC2VT[data["openCloseFlag"]],
                price=data["entrustPrice"],
                volume=data["entrustQty"],
                datetime=data["entrustTime"],
                product=Product.OPTION,
                gateway_name=self.gateway_name
            )
            self.orders[new_localid] = order

        # 确定委托状态
        if order.volume == order.traded:
            order.status = Status.ALLTRADED
        elif order.traded > 0:
            order.status = Status.PARTTRADED
        else:
            order.status = Status.NOTTRADED

        self.gateway.on_order(copy(order))

    def onStockTradeRtn(self, data: dict) -> None:
        """股票成交推送"""
        # 更新成交信息
        trade = TradeData(
            symbol=data["securityID"],
            exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
            tradeid=data["tradeID"],
            orderid=str(data["localOrderID"]),
            direction=DIRECTION_SEC2VT[data["entrustDirection"]],
            price=data["tradePrice"],
            volume=data["tradeQty"],
            datetime=data["tradeTime"],
            gateway_name=self.gateway_name
        )

        self.gateway.on_trade(trade)

        # 获取报单数据对象
        localid = data["localOrderID"]
        order = self.orders.get(localid, None)
        if not order:
            return

        order.traded += trade.volume
        order.traded = min(order.volume, order.traded)

        # 确定委托状态
        if order.volume == order.traded:
            order.status = Status.ALLTRADED
        elif order.traded > 0:
            order.status = Status.PARTTRADED

        self.gateway.on_order(copy(order))

    def onSOPTradeRtn(self, data: dict) -> None:
        """期权成交推送"""
        # 更新成交信息
        trade = TradeData(
            symbol=data["securityID"],
            exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
            tradeid=data["tradeID"],
            orderid=str(data["localOrderID"]),
            direction=DIRECTION_SEC2VT[data["entrustDirection"]],
            offset=OFFSET_SEC2VT[data["openCloseFlag"]],
            price=data["tradePrice"],
            volume=data["tradeQty"],
            datetime=data["tradeTime"],
            gateway_name=self.gateway_name
        )

        self.gateway.on_trade(trade)

        # 获取报单数据对象
        localid = data["localOrderID"]
        order = self.orders.get(localid, None)
        if not order:
            return

        # 获取报单数据对象
        localid = data["localOrderID"]
        order = self.orders.get(localid, None)
        if not order:
            return

        order.traded += trade.volume
        order.traded = min(order.volume, order.traded)

        # 确定委托状态
        if order.volume == order.traded:
            order.status = Status.ALLTRADED
        elif order.traded > 0:
            order.status = Status.PARTTRADED

        self.gateway.on_order(copy(order))

    def onStockWithdrawOrderRtn(self, data: dict) -> None:
        """股票撤单推送"""
        # 更新最大报单编号
        new_localid = data["localOrderID"]
        self.localid = max(self.localid, int(new_localid))

        # 获取报单数据对象
        if new_localid in self.orders:
            order = self.orders[new_localid]
        else:
            order = OrderData(
                symbol=data["securityID"],
                exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
                orderid=str(new_localid),
                direction=DIRECTION_SEC2VT[data["entrustDirection"]],
                price=data["entrustPrice"],
                traded=data["tradeQty"],
                volume=data["tradeQty"]+data["withdrawQty"],
                datetime=data["entrustTime"],
                product=Product.EQUITY,
                gateway_name=self.gateway_name
            )
            self.orders[new_localid] = order

        if data["withdrawQty"]:
            order.status = Status.CANCELLED

        self.gateway.on_order(copy(order))

    def onSOPWithdrawOrderRtn(self, data: dict) -> None:
        """期权撤单推送"""
        # 更新最大报单编号
        new_localid = data["localOrderID"]
        self.localid = max(self.localid, int(new_localid))

        # 获取报单数据对象
        if new_localid in self.orders:
            order = self.orders[new_localid]
        else:
            order = OrderData(
                symbol=data["securityID"],
                exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
                orderid=str(new_localid),
                direction=DIRECTION_SEC2VT[data["entrustDirection"]],
                price=data["entrustPrice"],
                traded=data["tradeQty"],
                offset=OFFSET_SEC2VT[data["openCloseFlag"]],
                volume=data["tradeQty"]+data["withdrawQty"],
                datetime=data["entrustTime"],
                product=Product.OPTION,
                gateway_name=self.gateway_name
            )
            self.orders[new_localid] = order

        if data["withdrawQty"]:
            order.status = Status.CANCELLED

        self.gateway.on_order(copy(order))

    def onRspSOPEntrustOrder(self, data: dict, error: dict) -> None:
        """期权发单错误"""
        if error:
            order = OrderData(
                orderid=str(error["localOrderID"]),
                status=Status.REJECTED,
                gateway_name=self.gateway_name,
            )
            self.gateway.on_order(order)

            self.gateway.write_error("期权委托错误", error)

    def onRspSOPWithdrawOrder(self, data: dict, error: dict) -> None:
        """撤单错误"""
        if error:
            self.gateway.write_error("撤单错误", error)

    def onRspStockQryStockStaticInfo(self, data: dict, error: dict, last: bool) -> None:
        """股票合约查询回报"""
        if not data:
            return

        if data["securityID"] == "510050":
            contract = ContractData(
                symbol=data["securityID"],
                exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
                name=data["securityName"].decode("GBK"),
                size=data["tradeUnit"],
                pricetick=0.001,
                product=Product.EQUITY,
                gateway_name=self.gateway_name
            )
            self.gateway.on_contract(contract)

        if last:
            msg = "股票交易合约信息获取完成"
            self.gateway.write_log(msg)

    def onRspSOPQryContactInfo(self, data: dict, error: dict, last: bool) -> None:
        """期权合约查询回报"""
        if not data:
            return

        contract = ContractData(
            symbol=data["securityOptionID"],
            exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
            name=data["contractName"].decode("GBK"),
            size=data["contactUnit"],
            pricetick=data["miniPriceChange"],
            product=Product.OPTION,
            option_strike=data["execPrice"],
            option_underlying="-".join([data["securityID"], str(data["endTradingDay"])[2:-2]]),
            option_expiry=str(data["endTradingDay"]),
            gateway_name=self.gateway_name
        )

        # 期权类型
        if data["optType"] == DFITCSEC_OT_CALL:
            contract.option_type = OptionType.CALL
        elif data["optType"] == DFITCSEC_OT_PUT:
            contract.option_type = OptionType.PUT

        # 推送
        self.gateway.on_contract(contract)

        if last:
            msg = "期权交易合约信息获取完成"
            self.gateway.write_log(msg)

    def onRspStockQryCapitalAccountInfo(self, data: dict, error: dict, last: bool) -> None:
        """股票资金账户查询回报"""
        if not data:
            return

        account = AccountData(
            accountid=data["accountID"] + "_Stock",
            available=data["availableFunds"],
            balance=data["totalFunds"],
            frozen=data["totalFunds"] - data["availableFunds"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

    def onRspSOPQryCapitalAccountInfo(self, data: dict, error: dict) -> None:
        """期权资金账户查询回报"""
        if not data:
            return
        account = AccountData(
            accountid=data["accountID"] + "_Option",
            available=data["availableFunds"],
            balance=data["totalFunds"],
            frozen=data["totalFunds"] - data["availableFunds"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

    def onRspStockQryPosition(self, data: dict, error: dict, last: bool) -> None:
        """股票持仓查询回报"""
        if not data or not data["securityID"]:
            return

        pos = PositionData(
            symbol=data["securityID"],
            exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
            direction=Direction.NEt,
            postiion=data["position"],
            price=data["avgPositionPrice"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(pos)

    def onRspSOPQryPosition(self, data: dict, error: dict, last: bool) -> None:
        """期权持仓查询回报"""
        if not data:
            return

        pos = PositionData(
            symbol=data["securityOptionID"],
            exchange=EXCHANGE_SEC2VT[data["exchangeID"]],
            direction=DIRECTION_SEC2VT[data["entrustDirection"]],
            postiion=data["position"],
            price=data["openAvgPrice"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(pos)

    def onRspStockQryAccountInfo(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspStockQryShareholderInfo(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspStockTransferFunds(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspStockEntrustBatchOrder(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspStockWithdrawBatchOrder(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspStockCalcAbleEntrustQty(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspStockCalcAblePurchaseETFQty(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspStockQryFreezeFundsDetail(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspStockQryFreezeStockDetail(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspStockQryTransferStockDetail(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspStockQryTransferFundsDetail(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspStockQryStockInfo(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspStockQryTradeTime(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspSOPUserLogout(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspSOPUserPasswordUpdate(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspSOPGroupSplit(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspSOPQryGroupPosition(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSOPLockOUnLockStock(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSOPQryEntrustOrder(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSOPQrySerialTrade(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSOPQryCollateralPosition(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSOPQryAccountInfo(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspSOPQryShareholderInfo(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspSOPCalcAbleEntrustQty(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspSOPQryAbleLockStock(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSOPExectueOrder(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspSOPQryExecAssiInfo(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSOPQryTradeTime(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSOPQryExchangeInfo(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSOPQryCommission(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSOPQryDeposit(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspSOPQryContractObjectInfo(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspStockWithdrawOrder(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspStockUserLogout(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspStockUserPasswordUpdate(self, data: dict, error: dict) -> None:
        """"""
        pas
    def onRspStockQryEntrustOrder(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspStockQryRealTimeTrade(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspStockQrySerialTrade(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLUserLogin(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLUserLogout(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLQryAbleFinInfo(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLQryAbleSloInfo(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLTransferCollateral(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLDirectRepayment(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLRepayStockTransfer(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLEntrustCrdtOrder(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLEntrustOrder(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLCalcAbleEntrustCrdtQty(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLQryCrdtFunds(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLQryCrdtContract(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLQryCrdtConChangeInfo(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLTransferFunds(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLQryAccountInfo(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLQryCapitalAccountInfo(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLQryShareholderInfo(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLQryPosition(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLQryEntrustOrder(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLQrySerialTrade(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLQryRealTimeTrade(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLQryFreezeFundsDetail(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLQryFreezeStockDetail(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLQryTransferFundsDetail(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLWithdrawOrder(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLQrySystemTime(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLQryTransferredContract(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLDesirableFundsOut(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onRspFASLQryGuaranteedContract(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onRspFASLQryUnderlyingContract(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onFASLEntrustOrderRtn(self, data: dict) -> None:
        """"""
        pass

    def onFASLTradeRtn(self, data: dict) -> None:
        """"""
        pass

    def onFASLWithdrawOrderRtn(self, data: dict) -> None:
        """"""
        pass

    def connect(
        self,
        account_id: str,
        password: str,
        client_id: int,
        td_address: str,
        auth_code,
        appid
    ) -> None:
        """"""
        self.account_id = account_id
        self.password = password
        self.client_id = client_id
        self.auth_code = auth_code
        self.app_id = appid

        # Create API object
        if not self.connect_status:
            path = str(get_folder_path(self.gateway_name.lower()))
            self.createDFITCSECTraderApi(path, td_address)
            self.init()

    def login_server(self) -> None:
        """"""
        self.reqid += 1
        data = {
            "requestID": self.reqid,
            "accountID": self.account_id,
            "password": self.password,
            "compressflag": self.compressflag,
            "authenticCode": self.auth_code,
            "appID": self.app_id,
            "collectInterType": self.collectInterType
        }
        self.reqStockUserLogin(data)

        self.reqid += 1
        data["requestID"] = self.reqid
        self.reqSOPUserLogin(data)

    def close(self) -> None:
        """"""
        if self.connect_status:
            self.exit()

    def query_option_info(self) -> None:
        """"""
        self.reqid += 1
        self.queryOptionAuctionInfo({}, self.session_id, self.reqid)

    def send_order(self, req: OrderRequest) -> str:
        """"""
        self.reqid += 1
        self.localid += 1

        sec_req = {
            "securityID": req.symbol,
            "exchangeID": EXCHANGE_VT2SEC[req.exchange],
            "entrustPrice": req.price,
            "entrustQty": int(req.volume),
            "localOrderID": self.localid,
            "accountID": self.account_id,
            "requestID": self.reqid,
            "entrustDirection": DIRECTION_VT2SEC[req.direction]
        }

        # Option order
        if check_option_symbol(req.symbol):
            sec_req["orderType"] = OPTION_PRICE_TYPE_VT2SEC.get(req.ordertype, "")
            sec_req["openCloseFlag"] = OFFSET_VT2SEC.get(req.offset, "")
            self.reqSOPEntrustOrder(sec_req)
            product = Product.OPTION
        # Stock order
        else:
            sec_req["orderType"] = STOCK_PRICE_TYPE_VT2SEC.get(req.ordertype, "")
            self.reqStockEntrustOrder(sec_req)
            product = Product.EQUITY

        order = OrderData(
            symbol=req.symbol,
            exchange=req.exchange,
            orderid=str(self.localid),
            price=req.price,
            volume=req.volume,
            direction=req.direction,
            offset=req.offset,
            product=product
        )
        self.orders[str(self.localid)] = order

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        self.reqid += 1
        req = {
            "localOrderID": int(req.orderid),
            "accountID": self.account_id,
            "requestID": self.reqid
        }

        order = self.orders.get(req.orderid, None)
        if not order or order.product == Product.OPTION:
            self.reqSOPWithdrawOrder(req)
        else:
            self.reqStockWithdrawOrder(req)

    def query_account(self) -> None:
        """"""
        self.reqid += 1
        req = {}
        req["requestID"] = self.reqid
        req["accountID"] = self.account_id
        self.reqSOPQryCapitalAccountInfo(req)

        self.reqid += 1
        req["FundsQryFlag"] = DFITCSEC_PQF_Extend
        self.reqStockQryCapitalAccountInfo(req)

    def query_position(self) -> None:
        """"""
        self.reqid += 1
        req = {}
        req["requestID"] = self.reqid
        req["accountID"] = self.account_id
        self.reqSOPQryPosition(req)

        self.reqid += 1
        self.reqStockQryPosition(req)

    def qry_option_contracts(self) -> None:
        """查询期权合约"""
        self.reqid += 1
        req = {}
        req["requestID"] = self.reqid
        req["accountID"] = self.account_id
        self.reqSOPQryContactInfo(req)

    def qryStockContracts(self) -> None:
        """查询股票合约"""
        self.reqid += 1
        req = {}
        req["exchangeID"] = "SH"
        req["requestID"] = self.reqid
        req["accountID"] = self.accountid
        self.reqStockQryStockStaticInfo(req)


def check_option_symbol(symbol) -> bool:
    """检查是否为期权代码"""
    if len(symbol) > 6:
        return True
    return False
