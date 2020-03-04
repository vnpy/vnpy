from typing import Any, Sequence, Dict, List
from datetime import datetime
from threading import Thread

from vnpy.api.xtp import MdApi,TdApi
from vnpy.event import EventEngine
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.constant import (
    Exchange,
    Product,
    Direction,
    OrderType,
    Status,
    Offset
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


MARKET_XTP2VT: Dict[int, Exchange] = {
    1: Exchange.SSE,
    2: Exchange.SZSE,
}
MARKET_VT2XTP: Dict[Exchange, int] = {v: k for k, v in MARKET_XTP2VT.items()}

EXCHANGE_XTP2VT: Dict[int, Exchange] = {
    1: Exchange.SSE,
    2: Exchange.SZSE,
}
EXCHANGE_VT2XTP: Dict[Exchange, int] = {v: k for k, v in EXCHANGE_XTP2VT.items()}

DIRECTION_XTP2VT: Dict[int, Any] = {
    1: (Direction.LONG, Offset.NONE),
    2: (Direction.SHORT, Offset.NONE),
    3: (Direction.LONG, Offset.OPEN), #21
    4: (Direction.SHORT, Offset.OPEN), #22
    5: (Direction.LONG, Offset.CLOSE),#24
    6: (Direction.SHORT, Offset.CLOSE)#23
}
DIRECTION_VT2XTP: Dict[Any, int] = {v: k for k, v in DIRECTION_XTP2VT.items()}

ORDERTYPE_XTP2VT: Dict[int, OrderType] = {
    1: OrderType.LIMIT,
    2: OrderType.MARKET
}
ORDERTYPE_VT2XTP: Dict[OrderType, int] = {v: k for k, v in ORDERTYPE_XTP2VT.items()}

PROTOCOL_VT2XTP: Dict[str, int] = {
    "TCP": 1,
    "UDP": 2
}

STATUS_XTP2VT: Dict[int, Status] = {
    0: Status.SUBMITTING,
    1: Status.ALLTRADED,
    2: Status.PARTTRADED,
    3: Status.CANCELLED,
    4: Status.NOTTRADED,
    5: Status.CANCELLED,
    6: Status.REJECTED,
    7: Status.SUBMITTING
}

PRODUCT_XTP2VT: Dict[int, Product] = {
    0: Product.EQUITY,
    1: Product.INDEX,
    2: Product.FUND,
    3: Product.BOND,
    4: Product.OPTION,
    5: Product.EQUITY,
    6: Product.OPTION
}

OFFSET_VT2XTP: Dict[Offset, int] = {
    
}


symbol_name_map = {}
symbol_exchange_map = {}


class XtpGateway(BaseGateway):

    default_setting: Dict[str, Any] = {
        "账号": "",
        "密码": "",
        "客户号": 1,
        "行情地址": "",
        "行情端口": 0,
        "交易地址": "",
        "交易端口": 0,
        "行情协议": ["TCP", "UDP"],
        "授权码": ""
    }

    exchanges: List[Exchange] = list(EXCHANGE_VT2XTP.keys())

    def __init__(self, event_engine: EventEngine):
        """"""
        super().__init__(event_engine, "XTP")

        self.md_api = XtpMdApi(self)
        self.td_api = XtpTdApi(self)

    def connect(self, setting: dict) -> None:
        """"""
        userid = setting["账号"]
        password = setting["密码"]
        client_id = int(setting["客户号"])
        quote_ip = setting["行情地址"]
        quote_port = int(setting["行情端口"])
        trader_ip = setting["交易地址"]
        trader_port = int(setting["交易端口"])
        quote_protocol = setting["行情协议"]
        software_key = setting["授权码"]

        self.md_api.connect(userid, password, client_id,
                               quote_ip, quote_port, quote_protocol)
        self.td_api.connect(userid, password, client_id,
                                trader_ip, trader_port, software_key)
        self.init_query()

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
        error_id = error["error_id"]
        error_msg = error["error_msg"]
        msg = f"{msg}，代码：{error_id}，信息：{error_msg}"
        self.write_log(msg)

class XtpMdApi(MdApi):

    def __init__(self, gateway: BaseGateway):
        """"""
        super().__init__()

        self.gateway: BaseGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.userid: str = ""
        self.password: str = ""
        self.client_id: int = 0
        self.server_ip: str = ""
        self.server_port: int = 0
        self.protocol :int = 0
        self.session_id: int = 0

        self.connect_status = False
        self.login_status = False

    def onDisconnected(self, reason: int) -> None:
        """"""
        self.connect_status = False
        self.login_status = False
        self.gateway.write_log(f"行情服务器连接断开, 原因{reason}")

        n = self.login()

        if n:
            self.session_id = n
            self.connect_status = True
            self.login_status = True

            self.gateway.write_log(f"交易服务器登录成功，会话编号：{self.session_id}")
        else:
            self.gateway.write_log("行情服务器登录失败")


    def onError(self, error: dict) -> None:
        """"""
        self.gateway.write_error("行情接口报错", error)

    def onSubMarketData(self, data: dict, error: dict, last: bool) -> None:
        """"""
        if not error or not error["error_id"]:
            return

        self.gateway.write_error("行情订阅失败", error)

    def onUnSubMarketData(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onDepthMarketData(self, data: dict) -> None:
        """"""
        timestamp = str(data["data_time"])
        dt = datetime.strptime(timestamp, "%Y%m%d%H%M%S%f")

        tick = TickData(
            symbol=data["ticker"],
            exchange=EXCHANGE_XTP2VT[data["exchange_id"]],
            datetime=dt,
            volume=data["qty"],
            last_price=data["last_price"],
            limit_up=data["upper_limit_price"],
            limit_down=data["lower_limit_price"],
            open_price=data["open_price"],
            high_price=data["high_price"],
            low_price=data["low_price"],
            pre_close=data["pre_close_price"],
            gateway_name=self.gateway_name
        )

        if type(data["bid"]) == list:
            tick.bid_price_1, tick.bid_price_2, tick.bid_price_3, tick.bid_price_4, tick.bid_price_5 = data["bid"][0:5]
            tick.ask_price_1, tick.ask_price_2, tick.ask_price_3, tick.ask_price_4, tick.ask_price_5 = data["ask"][0:5]
            tick.bid_volume_1, tick.bid_volume_2, tick.bid_volume_3, tick.bid_volume_4, tick.bid_volume_5 = data["bid_qty"][0:5]
            tick.ask_volume_1, tick.ask_volume_2, tick.ask_volume_3, tick.ask_volume_4, tick.ask_volume_5 = data["ask_qty"][0:5]

        elif type(data["bid"]) == float:
            tick.bid_price_1 = data["bid"]
            tick.ask_price_1 = data["ask"]
            tick.bid_volume_1 = data["bid_qty"]
            tick.ask_volume_1 = data["ask_qty"]

        tick.name = symbol_name_map.get(tick.vt_symbol, tick.symbol)

        self.gateway.on_tick(tick)

    def onSubOrderBook(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onUnSubOrderBook(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onOrderBook(self, data: dict) -> None:
        """"""
        pass

    def onSubTickByTick(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onUnSubTickByTick(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onTickByTick(self, data: dict) -> None:
        """"""
        pass

    def onSubscribeAllMarketData(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onUnSubscribeAllMarketData(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onSubscribeAllOrderBook(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onUnSubscribeAllOrderBook(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onSubscribeAllTickByTick(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onUnSubscribeAllTickByTick(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onQueryAllTickers(self, data: dict, error: dict, last: bool) -> None:
        """"""
        contract = ContractData(
            symbol=data["ticker"],
            exchange=EXCHANGE_XTP2VT[data["exchange_id"]],
            name=data["ticker_name"],
            product=PRODUCT_XTP2VT[data["ticker_type"]],
            size=1,
            pricetick=data["price_tick"],
            min_volume=data["buy_qty_unit"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_contract(contract)

        symbol_name_map[contract.vt_symbol] = contract.name

        if contract.product != Product.INDEX:
            symbol_exchange_map[contract.symbol] = contract.exchange

        if last:
            self.gateway.write_log(f"{contract.exchange.value}合约信息查询成功")

    def onQueryTickersPriceInfo(self, data: dict, error: dict, last: bool) -> None:
        """"""
        pass

    def onSubscribeAllOptionMarketData(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onUnSubscribeAllOptionMarketData(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onSubscribeAllOptionOrderBook(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onUnSubscribeAllOptionOrderBook(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onSubscribeAllOptionTickByTick(self, data: dict, error: dict) -> None:
        """"""
        pass

    def onUnSubscribeAllOptionTickByTick(self, data: dict, error: dict) -> None:
        """"""
        pass


    def connect(
        self,
        userid: str,
        password: str,
        client_id: int,
        server_ip: str,
        server_port: int,
        quote_protocol: int
    ):
        """"""
        self.userid = userid
        self.password = password
        self.client_id = client_id
        self.server_ip = server_ip
        self.server_port = server_port
        self.protocol = PROTOCOL_VT2XTP[quote_protocol]

        # Create API object

        if not self.connect_status:
            
            path = str(get_folder_path(self.gateway_name.lower()))
            self.createQuoteApi(
                self.client_id,
                path,
            )

            self.login_server()

    def login_server(self):
        """"""
        n = self.login(
            self.server_ip,
            self.server_port,
            self.userid,
            self.password,
            self.protocol
        )
        if not n:
            self.connect_status = True
            self.login_status = True
            msg = "行情服务器登录成功"
            self.query_contract()
            self.init()
        else:
            msg = f"行情服务器登录失败，原因：{n}"
        self.gateway.write_log(msg)

    def close(self):
        """"""
        if self.connect_status:
            self.exit()

    def subscrbie(self, req: SubscribeRequest):
        """"""
        if self.login_status:
            xtp_exchange = EXCHANGE_VT2XTP.get(req.exchange, "")
            self.subscribeMarketData(req.symbol, 1,xtp_exchange)

    def query_contract(self):
        """"""
        for exchange_id in EXCHANGE_XTP2VT.keys():
            self.queryAllTickers(exchange_id)


class XtpTdApi(TdApi):

    def __init__(self, gateway: BaseGateway):
        """"""
        super().__init__()

        self.gateway: BaseGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.userid: str = ""
        self.password: str = ""
        self.client_id: str = ""
        self.server_ip: str = ""
        self.server_port: str = ""
        self.software_key: str = ""

        self.connect_status: bool = False
        self.login_status: bool = False
        self.session_id: int = 0
        self.reqid: int = 0
        self.protocol: int = 0

        # Whether current account supports margin or option
        self.margin_trading = False
        self.option_trading = False

        #
        self.short_positions = {}

    def onDisconnected(self, session: int, reason: int) -> None:
        """"""
        self.connect_status = False
        self.login_status = False
        self.gateway.write_log(f"交易服务器连接断开, 原因{reason}")

        self.login_server()

    def onError(self, error: dict) -> None:
        """"""
        self.gateway.write_error("交易接口报错", error)

    def onOrderEvent(self, data: dict, error: dict, session: int) -> None:
        """"""
        print("onOrderEvent", data, error)
        if error["error_id"]:
            self.gateway.write_error("交易委托失败", error)

        direction, offset = DIRECTION_XTP2VT[data["side"]]

        order = OrderData(
            symbol=data["ticker"],
            exchange=MARKET_XTP2VT[data["market"]],
            orderid=str(data["order_xtp_id"]),
            type=ORDERTYPE_XTP2VT[data["price_type"]],
            direction=direction,
            offset=offset,
            price=data["price"],
            volume=data["quantity"],
            traded=data["qty_traded"],
            status=STATUS_XTP2VT[data["order_status"]],
            time=data["insert_time"],
            gateway_name=self.gateway_name
        )

        self.gateway.on_order(order)

    def onTradeEvent(self, data: dict, session: int) -> None:
        """"""
        print("onTradeEvent", data, error)
        direction, offset = DIRECTION_XTP2VT[data["side"]]

        trade = TradeData(
            symbol=data["ticker"],
            exchange=MARKET_XTP2VT[data["market"]],
            orderid=str(data["order_xtp_id"]),
            tradeid=str(data["exec_id"]),
            direction=direction,
            offset=offset,
            price=data["price"],
            volume=data["quantity"],
            time=data["trade_time"],
            gateway_name=self.gateway_name
        )

        self.gateway.on_trade(trade)

    def onCancelOrderError(self, data: dict, error: dict, session: int) -> None:
        """"""
        if not error or not error["error_id"]:
            return

        self.gateway.write_error("撤单失败", error)

    def onQueryOrder(self, data: dict, error: dict, last: bool, session: int) -> None:
        """"""
        self.updateOrder(data)

        if last:
            self.gateway.write_log("查询委托信息成功")

    def onQueryTrade(self, data: dict, error: dict, last: bool, session: int) -> None:
        """"""
        if self.check_error("查询成交", error):
            return

        self.updateTrade(data)

        if last:
            self.gateway.write_log("查询成交信息成功")

    def onQueryPosition(
        self,
        data: dict,
        error: dict,
        request: int,
        last: bool,
        session: int
    ) -> None:
        """"""
        if data["market"] == 0:
            return

        position = PositionData(
            symbol=data["ticker"],
            exchange=MARKET_XTP2VT[data["market"]],
            direction=Direction.LONG,
            volume=data["total_qty"],
            frozen=data["locked_position"],
            price=data["avg_price"],
            pnl=data["unrealized_pnl"],
            yd_volume=data["yesterday_position"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(position)

    def onQueryAsset(
        self,
        data: dict,
        error: dict,
        request: int,
        last: bool,
        session: int
    ) -> None:
        """"""
        account = AccountData(
            accountid=self.userid,
            balance=data["buying_power"],
            frozen=data["withholding_amount"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

        if data["account_type"] == 1:
            self.margin_trading = True
        elif data["account_type"] == 2:
            self.option_trading = True

    def onQueryStructuredFund(self, data: dict, error: dict, last: bool, session: int) -> None:
        """"""
        pass

    def onQueryFundTransfer(self, data: dict, error: dict, last: bool, session: int) -> None:
        """"""
        pass

    def onFundTransfer(self, data: dict, session: int) -> None:
        """"""
        pass

    def onQueryETF(self, data: dict, error: dict, last: bool, session: int) -> None:
        """"""
        pass

    def onQueryETFBasket(self, data: dict, error: dict, last: bool, session: int) -> None:
        """"""
        pass

    def onQueryIPOInfoList(self, data: dict, error: dict, last: bool, session: int) -> None:
        """"""
        pass

    def onQueryIPOQuotaInfo(self, data: dict, error: dict, last: bool, session: int) -> None:
        """"""
        pass

    def onQueryOptionAuctionInfo(self, data: dict, error: dict, last: bool, session: int) -> None:
        """"""
        pass

    def onQueryCreditDebtInfo(
        self,
        data: dict,
        error: dict,
        request: int,
        last: bool,
        session: int
    ) -> None:
        """"""
        if data["debt_type"] == 1:
            symbol = data["ticker"]
            exchange = MARKET_XTP2VT[data["market"]]

            position = self.short_positions.get(symbol, None)
            if not position:
                position = PositionData(
                    symbol=symbol,
                    exchange=exchange,
                    direction=Direction.SHORT,
                    gateway_name=self.gateway_name
                )
                self.short_positions[symbol] = position

            position.volume += data["remain_qty"]

        if last:
            for position in self.short_positions.values():
                self.gateway.on_position(position)

            self.short_positions.clear()

    def connect(
        self,
        userid: str,
        password: str,
        client_id: int,
        server_ip: str,
        server_port: int,
        software_key: str
    ) -> None:
        """"""

        self.userid = userid
        self.password = password
        self.client_id = client_id
        self.server_ip = server_ip
        self.server_port = server_port
        self.software_key = software_key
        self.protocol = PROTOCOL_VT2XTP["TCP"]

        # Create API object
        if not self.connect_status:
            path = str(get_folder_path(self.gateway_name.lower()))

            self.createTraderApi(
                self.client_id,
                path,
            )

            self.setSoftwareKey(self.software_key)
            self.subscribePublicTopic(0)
            self.login_server()

    def login_server(self) -> None:
        """"""
        n = self.login(
            self.server_ip,
            self.server_port,
            self.userid,
            self.password,
            self.protocol
        )

        if n:
            self.session_id = n
            self.connect_status = True
            self.login_status = True
            msg = f"交易服务器登录成功, 会话编号：{self.session_id}"
            self.init()

        else:
            error = self.getApiLastError()
            msg = f"交易服务器登录失败，原因：{error.error_msg}"

        self.gateway.write_log(msg)

    def close(self) -> None:
        """"""
        if self.connect_status:
            self.exit()

    def send_order(self, req: OrderRequest) -> str:
        """"""
        if req.exchange not in MARKET_VT2XTP:
            self.gateway.write_log(f"委托失败，不支持的交易所{req.exchange.value}")
            return ""

        if req.type not in ORDERTYPE_VT2XTP:
            self.gateway.write_log(f"委托失败，不支持的委托类型{req.type.value}")
            return ""

        xtp_req = {
            "ticker": req.symbol,
            "market": MARKET_VT2XTP[req.exchange],
            "price": req.price,
            "quantity": int(req.volume),
            "side": DIRECTION_VT2XTP.get((req.direction, req.offset), ""),
            "price_type": ORDERTYPE_VT2XTP[req.type],
            "position_effect"
        }
        # xtp_req["ticker"] = req.symbol
        # xtp_req["market"] = MARKET_VT2XTP[req.exchange]
        # xtp_req["price"] = req.price
        # xtp_req["quantity"] = int(req.volume)
        # xtp_req["side"] = DIRECTION_VT2XTP.get((req.direction, req.offset), "")
        # xtp_req["price_type"] = ORDERTYPE_VT2XTP[req.type]

        if req.offset == Offset.NONE:
            xtp_req["business_type"] = 0
            xtp_req["position_effect"] = 1
        elif req.offset == Offset.OPEN:

        else:
            xtp_req["business_type"] = 4

        # ajust for option type
        if len(req.symbol) == 8:
            xtp_req["business_type"] = 10


        orderid = self.insertOrder(xtp_req, self.session_id)

        order = req.create_order_data(str(orderid), self.gateway_name)
        self.gateway.on_order(order)
        print("send_order result:", orderid)

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        self.cancelOrder(int(req.orderid), self.session_id)

    def query_account(self) -> None:
        """"""
        if not self.connect_status:
            return

        self.reqid += 1
        self.queryAsset(self.session_id, self.reqid)

    def query_position(self) -> None:
        """"""
        if not self.connect_status:
            return

        self.reqid += 1
        self.queryPosition("", self.session_id, self.reqid)

        if self.margin_trading:
            self.reqid += 1
            self.queryCreditDebtInfo(self.session_id, self.reqid)

    def check_error(self, func_name: str, error: dict):
        """"""
        if error and error.error_id:
            msg = f"{func_name}发生错误, 代码：{error.error_id}，信息：{error.error_msg}"
            self.gateway.write_log(msg)
            return True
        else:
            return False

