from logging import log
import pytz
from typing import Any, Dict, List
from datetime import datetime
from copy import copy

from vnpy.api.xtp import MdApi, TdApi
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
from vnpy.trader.utility import get_folder_path, round_to


MARKET_XTP2VT: Dict[int, Exchange] = {
    1: Exchange.SZSE,
    2: Exchange.SSE
}
MARKET_VT2XTP: Dict[Exchange, int] = {v: k for k, v in MARKET_XTP2VT.items()}

EXCHANGE_XTP2VT: Dict[int, Exchange] = {
    1: Exchange.SSE,
    2: Exchange.SZSE,
}
EXCHANGE_VT2XTP: Dict[Exchange, int] = {v: k for k, v in EXCHANGE_XTP2VT.items()}

DIRECTION_STOCK_XTP2VT: Dict[int, Any] = {
    1: (Direction.LONG, Offset.NONE),
    2: (Direction.SHORT, Offset.NONE),
    21: (Direction.LONG, Offset.OPEN),
    22: (Direction.SHORT, Offset.OPEN),
    24: (Direction.LONG, Offset.CLOSE),
    23: (Direction.SHORT, Offset.CLOSE)
}
DIRECTION_STOCK_VT2XTP: Dict[Any, int] = {v: k for k, v in DIRECTION_STOCK_XTP2VT.items()}

DIRECTION_OPTION_XTP2VT: Dict[int, Direction] = {
    1: Direction.LONG,
    2: Direction.SHORT
}
DIRECTION_OPTION_VT2XTP: Dict[Direction, int] = {v: k for k, v in DIRECTION_OPTION_XTP2VT.items()}

POSITION_DIRECTION_XTP2VT = {
    0: Direction.NET,
    1: Direction.LONG,
    2: Direction.SHORT,
    3: Direction.SHORT
}

OPTION_ORDERTYPE_XTP2VT: Dict[int, OrderType] = {
    1: OrderType.LIMIT,
    2: OrderType.MARKET,
    8: OrderType.FOK
}
OPTION_ORDERTYPE_VT2XTP: Dict[OrderType, int] = {v: k for k, v in OPTION_ORDERTYPE_XTP2VT.items()}

EQUITY_ORDERTYPE_XTP2VT: Dict[int, OrderType] = {
    1: OrderType.LIMIT,
    4: OrderType.MARKET
}
EQUITY_ORDERTYPE_VT2XTP: Dict[OrderType, int] = {v: k for k, v in EQUITY_ORDERTYPE_XTP2VT.items()}


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
    Offset.NONE: 0,
    Offset.OPEN: 1,
    Offset.CLOSE: 2,
    Offset.CLOSETODAY: 4,
    Offset.CLOSEYESTERDAY: 5
}
OFFSET_XTP2VT: Dict[int, Offset] = {v: k for k, v in OFFSET_VT2XTP.items()}

BUSINESS_VT2XTP: Dict[Any, int] = {
    "CASH": 0,
    Offset.NONE: 0,
    "MARGIN": 4,
    Offset.OPEN: 4,
    Offset.CLOSE: 4,
    "OPTION": 10,
}

OPTIONTYPE_XTP2VT = {
    1: OptionType.CALL,
    2: OptionType.PUT
}

LOGLEVEL_VT2XTP = {
    "FATAL": 0,
    "ERROR": 1,
    "WARNING": 2,
    "INFO": 3,
    "DEBUG": 4,
    "TRACE": 5,
}

CHINA_TZ = pytz.timezone("Asia/Shanghai")

symbol_name_map: Dict[str, str] = {}
symbol_pricetick_map: Dict[str, float] = {}


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
        "日志级别": ["FATAL", "ERROR", "WARNING", "INFO", "DEBUG", "TRACE"],
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
        log_level = LOGLEVEL_VT2XTP[setting["日志级别"]]
        software_key = setting["授权码"]

        self.md_api.connect(
            userid, password, client_id, quote_ip,
            quote_port, quote_protocol, log_level
        )
        self.td_api.connect(
            userid, password, client_id, trader_ip,
            trader_port, software_key, log_level
        )
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

    def __init__(self, gateway: XtpGateway):
        """"""
        super().__init__()

        self.gateway: XtpGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.userid: str = ""
        self.password: str = ""
        self.client_id: int = 0
        self.server_ip: str = ""
        self.server_port: int = 0
        self.protocol: int = 0
        self.session_id: int = 0

        self.connect_status: bool = False
        self.login_status: bool = False

        self.sse_inited: bool = False
        self.szse_inited: bool = False

    def onDisconnected(self, reason: int) -> None:
        """"""
        self.connect_status = False
        self.login_status = False
        self.gateway.write_log(f"行情服务器连接断开, 原因{reason}")

        self.login_server()

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
        dt = CHINA_TZ.localize(dt)

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

        tick.bid_price_1, tick.bid_price_2, tick.bid_price_3, tick.bid_price_4, tick.bid_price_5 = data["bid"][0:5]
        tick.ask_price_1, tick.ask_price_2, tick.ask_price_3, tick.ask_price_4, tick.ask_price_5 = data["ask"][0:5]
        tick.bid_volume_1, tick.bid_volume_2, tick.bid_volume_3, tick.bid_volume_4, tick.bid_volume_5 = data["bid_qty"][0:5]
        tick.ask_volume_1, tick.ask_volume_2, tick.ask_volume_3, tick.ask_volume_4, tick.ask_volume_5 = data["ask_qty"][0:5]

        pricetick = symbol_pricetick_map.get(tick.vt_symbol, 0)
        if pricetick:
            tick.last_price = round_to(data["last_price"], pricetick)
            tick.limit_up = round_to(data["upper_limit_price"], pricetick)
            tick.limit_down = round_to(data["lower_limit_price"], pricetick)
            tick.open_price = round_to(data["open_price"], pricetick)
            tick.high_price = round_to(data["high_price"], pricetick)
            tick.low_price = round_to(data["low_price"], pricetick)
            tick.pre_close = round_to(data["pre_close_price"], pricetick)

            tick.bid_price_1 = round_to(tick.bid_price_1, pricetick)
            tick.bid_price_2 = round_to(tick.bid_price_2, pricetick)
            tick.bid_price_3 = round_to(tick.bid_price_3, pricetick)
            tick.bid_price_4 = round_to(tick.bid_price_4, pricetick)
            tick.bid_price_5 = round_to(tick.bid_price_5, pricetick)
            tick.ask_price_1 = round_to(tick.ask_price_1, pricetick)
            tick.ask_price_2 = round_to(tick.ask_price_2, pricetick)
            tick.ask_price_3 = round_to(tick.ask_price_3, pricetick)
            tick.ask_price_4 = round_to(tick.ask_price_4, pricetick)
            tick.ask_price_5 = round_to(tick.ask_price_5, pricetick)

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

        if contract.product != Product.OPTION:
            self.gateway.on_contract(contract)

        symbol_name_map[contract.vt_symbol] = contract.name
        symbol_pricetick_map[contract.vt_symbol] = contract.pricetick

        if last:
            self.gateway.write_log(f"{contract.exchange.value}合约信息查询成功")

            if contract.exchange == Exchange.SSE:
                self.sse_inited = True
            else:
                self.szse_inited = True

            if self.sse_inited and self.szse_inited:
                self.gateway.td_api.query_option_info()

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
        quote_protocol: int,
        log_level: int
    ) -> None:
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
            self.createQuoteApi(self.client_id, path, log_level)
            self.login_server()
        else:
            self.gateway.write_log("行情接口已登录，请勿重复操作")

    def login_server(self) -> None:
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

    def close(self) -> None:
        """"""
        if self.connect_status:
            self.exit()

    def subscribe(self, req: SubscribeRequest) -> None:
        """"""
        if self.login_status:
            xtp_exchange = EXCHANGE_VT2XTP.get(req.exchange, "")
            self.subscribeMarketData(req.symbol, 1, xtp_exchange)

    def query_contract(self) -> None:
        """"""
        for exchange_id in EXCHANGE_XTP2VT.keys():
            self.queryAllTickers(exchange_id)


class XtpTdApi(TdApi):

    def __init__(self, gateway: XtpGateway):
        """"""
        super().__init__()

        self.gateway: XtpGateway = gateway
        self.gateway_name: str = gateway.gateway_name

        self.userid: str = ""
        self.password: str = ""
        self.client_id: str = ""
        self.server_ip: str = ""
        self.server_port: str = ""
        self.software_key: str = ""

        self.session_id: int = 0
        self.reqid: int = 0
        self.protocol: int = 0

        # Whether current account supports margin or option
        self.margin_trading = False
        self.option_trading = False

        self.connect_status: bool = False
        self.login_status: bool = False

        self.short_positions: Dict[str, PositionData] = {}
        self.orders: Dict[str, OrderData] = {}

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
        if error["error_id"]:
            self.gateway.write_error("交易委托失败", error)

        symbol = data["ticker"]
        if len(symbol) == 8:
            direction = DIRECTION_OPTION_XTP2VT[data["side"]]
            offset = OFFSET_XTP2VT[data["position_effect"]]
            order_type = OPTION_ORDERTYPE_XTP2VT.get(data["price_type"], OrderType.MARKET)
        else:
            direction, offset = DIRECTION_STOCK_XTP2VT[data["side"]]
            order_type = EQUITY_ORDERTYPE_XTP2VT.get(data["price_type"], OrderType.MARKET)

        orderid = str(data["order_xtp_id"])
        if orderid not in self.orders:
            order = OrderData(
                symbol=symbol,
                exchange=MARKET_XTP2VT[data["market"]],
                orderid=orderid,
                type=order_type,
                direction=direction,
                offset=offset,
                price=data["price"],
                volume=data["quantity"],
                traded=data["qty_traded"],
                status=STATUS_XTP2VT[data["order_status"]],
                gateway_name=self.gateway_name
            )
            self.orders[orderid] = order
        else:
            order = self.orders[orderid]
            order.traded = data["qty_traded"]
            order.status = STATUS_XTP2VT[data["order_status"]]

        if not order.datetime:
            timestamp = str(data["insert_time"])
            dt = datetime.strptime(timestamp, "%Y%m%d%H%M%S%f")
            dt = CHINA_TZ.localize(dt)
            order.datetime = dt

        self.gateway.on_order(copy(order))

    def onTradeEvent(self, data: dict, session: int) -> None:
        """"""
        symbol = data["ticker"]
        if len(symbol) == 8:
            direction = DIRECTION_OPTION_XTP2VT[data["side"]]
            offset = OFFSET_XTP2VT[data["position_effect"]]
        else:
            direction, offset = DIRECTION_STOCK_XTP2VT[data["side"]]

        timestamp = str(data["trade_time"])
        dt = datetime.strptime(timestamp, "%Y%m%d%H%M%S%f")
        dt = CHINA_TZ.localize(dt)

        trade = TradeData(
            symbol=symbol,
            exchange=MARKET_XTP2VT[data["market"]],
            orderid=str(data["order_xtp_id"]),
            tradeid=str(data["exec_id"]),
            direction=direction,
            offset=offset,
            price=data["price"],
            volume=data["quantity"],
            datetime=dt,
            gateway_name=self.gateway_name
        )

        if trade.orderid in self.orders:
            order = self.orders[trade.orderid]
            order.traded += trade.volume

            if order.traded < order.volume:
                order.status = Status.PARTTRADED
            else:
                order.status = Status.ALLTRADED
            self.gateway.on_order(copy(order))
        else:
            self.gateway.write_log(f"成交找不到对应委托{trade.orderid}")

        self.gateway.on_trade(trade)

    def onCancelOrderError(self, data: dict, error: dict, session: int) -> None:
        """"""
        if not error or not error["error_id"]:
            return

        self.gateway.write_error("撤单失败", error)

    def onQueryOrder(self, data: dict, error: dict, reqid: int, last: bool, session: int) -> None:
        """"""
        pass

    def onQueryTrade(self, data: dict, error: dict, reqid: int, last: bool, session: int) -> None:
        """"""
        pass

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
            direction=POSITION_DIRECTION_XTP2VT[data["position_direction"]],
            volume=data["total_qty"],
            frozen=data["total_qty"] - data["sellable_qty"],
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
            balance=round(data["total_asset"], 2),
            frozen=round(data["withholding_amount"], 2),
            gateway_name=self.gateway_name
        )
        account.available = round(data["buying_power"], 2)

        if data["account_type"] == 1:
            self.margin_trading = True
        elif data["account_type"] == 2:
            account.frozen = round(account.balance - account.available, 2)
            self.option_trading = True

        self.gateway.on_account(account)

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

    def onQueryOptionAuctionInfo(self, data: dict, error: dict, reqid: int, last: bool, session: int) -> None:
        """"""
        if not data or not data["ticker"]:
            return

        contract = ContractData(
            symbol=data["ticker"],
            exchange=MARKET_XTP2VT[data["security_id_source"]],
            name=data["symbol"],
            product=Product.OPTION,
            size=data["contract_unit"],
            min_volume=data["qty_unit"],
            pricetick=data["price_tick"],
            gateway_name=self.gateway_name
        )

        contract.option_portfolio = data["underlying_security_id"] + "_O"
        contract.option_underlying = (
            data["underlying_security_id"]
            + "-"
            + str(data["delivery_month"])
        )
        contract.option_type = OPTIONTYPE_XTP2VT.get(data["call_or_put"], None)

        contract.option_strike = data["exercise_price"]
        contract.option_expiry = datetime.strptime(
            str(data["last_trade_date"]), "%Y%m%d"
        )
        contract.option_index = get_option_index(
            contract.option_strike, data["contract_id"]
        )

        self.gateway.on_contract(contract)
        symbol_pricetick_map[contract.vt_symbol] = contract.pricetick

        if last:
            self.gateway.write_log("期权信息查询成功")

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
        software_key: str,
        log_level: int
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
            self.createTraderApi(self.client_id, path, log_level)

            self.setSoftwareKey(self.software_key)
            self.subscribePublicTopic(0)
            self.login_server()
        else:
            self.gateway.write_log("交易接口已登录，请勿重复操作")

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
            msg = f"交易服务器登录失败，原因：{error['error_msg']}"

        self.gateway.write_log(msg)

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
        if req.exchange not in MARKET_VT2XTP:
            self.gateway.write_log(f"委托失败，不支持的交易所{req.exchange.value}")
            return ""

        if self.margin_trading and req.offset == Offset.NONE:
            self.gateway.write_log(f"委托失败，两融交易需要选择开平方向")
            return ""

        # check for option type
        if len(req.symbol) == 8:
            if req.type not in OPTION_ORDERTYPE_VT2XTP:
                self.gateway.write_log(f"委托失败，不支持的期权委托类型{req.type.value}")
                return ""

            xtp_req = {
                "ticker": req.symbol,
                "market": MARKET_VT2XTP[req.exchange],
                "price": req.price,
                "quantity": int(req.volume),
                "side": DIRECTION_OPTION_VT2XTP.get(req.direction, ""),
                "position_effect": OFFSET_VT2XTP[req.offset],
                "price_type": OPTION_ORDERTYPE_VT2XTP[req.type],
                "business_type": 10
            }

        # stock type
        else:
            if req.type not in EQUITY_ORDERTYPE_VT2XTP:
                self.gateway.write_log(f"委托失败，不支持的股票委托类型{req.type.value}")
                return ""

            xtp_req = {
                "ticker": req.symbol,
                "market": MARKET_VT2XTP[req.exchange],
                "price": req.price,
                "quantity": int(req.volume),
                "price_type": EQUITY_ORDERTYPE_VT2XTP[req.type],
            }

            if self.margin_trading:
                xtp_req["side"] = DIRECTION_STOCK_VT2XTP.get((req.direction, req.offset), "")
                xtp_req["business_type"] = 4
            else:
                xtp_req["side"] = DIRECTION_STOCK_VT2XTP.get((req.direction, Offset.NONE), "")
                xtp_req["business_type"] = 0

        orderid = self.insertOrder(xtp_req, self.session_id)
        orderid = str(orderid)

        order = req.create_order_data(orderid, self.gateway_name)
        self.orders[orderid] = order
        self.gateway.on_order(copy(order))

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
