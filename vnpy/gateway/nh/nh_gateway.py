"""
"""

import sys
import pytz
from datetime import datetime
from time import sleep
from copy import copy

from vnpy.trader.constant import (
    Direction,
    Offset,
    Exchange,
    OrderType,
    Product,
    Status,
    OptionType
)
from vnpy.trader.gateway import BaseGateway
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
from vnpy.trader.utility import get_folder_path
from vnpy.trader.event import EVENT_TIMER
from vnpy.event import Event

from vnnh.api.nh import MdApi, FuturesTdApi, StockTdApi

from .futures_constant import (
    THOST_FTDC_OAS_Submitted,
    THOST_FTDC_OAS_Accepted,
    THOST_FTDC_OAS_Rejected,
    THOST_FTDC_OST_NoTradeQueueing,
    THOST_FTDC_OST_PartTradedQueueing,
    THOST_FTDC_OST_AllTraded,
    THOST_FTDC_OST_Canceled,
    THOST_FTDC_D_Buy,
    THOST_FTDC_D_Sell,
    THOST_FTDC_PD_Long,
    THOST_FTDC_PD_Short,
    THOST_FTDC_OPT_LimitPrice,
    THOST_FTDC_OPT_AnyPrice,
    THOST_FTDC_OF_Open,
    THOST_FTDC_OFEN_Close,
    THOST_FTDC_OFEN_CloseYesterday,
    THOST_FTDC_OFEN_CloseToday,
    THOST_FTDC_PC_Futures,
    THOST_FTDC_PC_Options,
    THOST_FTDC_PC_SpotOption,
    THOST_FTDC_PC_Combination,
    THOST_FTDC_CP_CallOptions,
    THOST_FTDC_CP_PutOptions,
    THOST_FTDC_HF_Speculation,
    THOST_FTDC_CC_Immediately,
    THOST_FTDC_FCC_NotForceClose,
    THOST_FTDC_TC_GFD,
    THOST_FTDC_VC_AV,
    THOST_FTDC_TC_IOC,
    THOST_FTDC_VC_CV,
    THOST_FTDC_AF_Delete
)
from .stock_constant import (
    SZSE_FTDC_CallOrPut_A,
    SZSE_FTDC_CallOrPut_E,
    SZSE_FTDC_OrdType_Limit,
    SZSE_FTDC_OrdType_Market,
    SZSE_FTDC_OC_Open,
    SZSE_FTDC_OC_Close,
    SZSE_FTDC_SIDE_Buy,
    SZSE_FTDC_SIDE_Sell,
    SZSE_FTDC_Status_Success,
    SZSE_FTDC_Status_Trade,
    SZSE_FTDC_Status_All,
    SZSE_FTDC_Status_Cancel,
    SZSE_FTDC_Status_Reject,
    SZSE_FTDC_TimeInForce_FOK,
    SZSE_FTDC_TimeInForce_IOC,
    SZSE_FTDC_TimeInForce_GFD,
)
from .stock_error import ERROR_MSG


EVENT_NH_EXERCISE = "eNhExercise"
EVENT_NH_EXERCISE_LOG = "eNhExerciseLog"

STATUS_FUTURES2VT = {
    THOST_FTDC_OAS_Submitted: Status.SUBMITTING,
    THOST_FTDC_OAS_Accepted: Status.SUBMITTING,
    THOST_FTDC_OAS_Rejected: Status.REJECTED,
    THOST_FTDC_OST_NoTradeQueueing: Status.NOTTRADED,
    THOST_FTDC_OST_PartTradedQueueing: Status.PARTTRADED,
    THOST_FTDC_OST_AllTraded: Status.ALLTRADED,
    THOST_FTDC_OST_Canceled: Status.CANCELLED
}

DIRECTION_VT2FUTURES = {
    Direction.LONG: THOST_FTDC_D_Buy,
    Direction.SHORT: THOST_FTDC_D_Sell
}
DIRECTION_FUTURES2VT = {v: k for k, v in DIRECTION_VT2FUTURES.items()}
DIRECTION_FUTURES2VT[THOST_FTDC_PD_Long] = Direction.LONG
DIRECTION_FUTURES2VT[THOST_FTDC_PD_Short] = Direction.SHORT

ORDERTYPE_VT2FUTURES = {
    OrderType.LIMIT: THOST_FTDC_OPT_LimitPrice,
    OrderType.MARKET: THOST_FTDC_OPT_AnyPrice
}
ORDERTYPE_FUTURES2VT = {v: k for k, v in ORDERTYPE_VT2FUTURES.items()}

OFFSET_VT2FUTURES = {
    Offset.OPEN: THOST_FTDC_OF_Open,
    Offset.CLOSE: THOST_FTDC_OFEN_Close,
    Offset.CLOSETODAY: THOST_FTDC_OFEN_CloseToday,
    Offset.CLOSEYESTERDAY: THOST_FTDC_OFEN_CloseYesterday,
}
OFFSET_FUTURES2VT = {v: k for k, v in OFFSET_VT2FUTURES.items()}

EXCHANGE_FUTURES2VT = {
    "CFFEX": Exchange.CFFEX,
    "SHFE": Exchange.SHFE,
    "CZCE": Exchange.CZCE,
    "DCE": Exchange.DCE,
    "INE": Exchange.INE
}

PRODUCT_FUTURES2VT = {
    THOST_FTDC_PC_Futures: Product.FUTURES,
    THOST_FTDC_PC_Options: Product.OPTION,
    THOST_FTDC_PC_SpotOption: Product.OPTION,
    THOST_FTDC_PC_Combination: Product.SPREAD
}

OPTIONTYPE_FUTURES2VT = {
    THOST_FTDC_CP_CallOptions: OptionType.CALL,
    THOST_FTDC_CP_PutOptions: OptionType.PUT
}

MAX_FLOAT = sys.float_info.max
CHINA_TZ = pytz.timezone("Asia/Shanghai")

EXCHANGE_MD2VT = {
    "CFFEX": Exchange.CFFEX,
    "SHFE": Exchange.SHFE,
    "CZCE": Exchange.CZCE,
    "DCE": Exchange.DCE,
    "INE": Exchange.INE,
}
EXCHANGE_VT2MD = {
    Exchange.CFFEX: "CFFEX",
    Exchange.SHFE: "SHFE",
    Exchange.CZCE: "CZCE",
    Exchange.DCE: "DCE",
    Exchange.SSE: "SSE",
    Exchange.SZSE: "SZSE"
}

OPTIONTYPE_STOCK2VT = {
    SZSE_FTDC_CallOrPut_E: OptionType.CALL,
    SZSE_FTDC_CallOrPut_A: OptionType.PUT
}

ORDERTYPE_VT2STOCK = {
    OrderType.MARKET: (SZSE_FTDC_OrdType_Market, SZSE_FTDC_TimeInForce_GFD),
    OrderType.LIMIT: (SZSE_FTDC_OrdType_Limit, SZSE_FTDC_TimeInForce_GFD),
    OrderType.FAK: (SZSE_FTDC_OrdType_Limit, SZSE_FTDC_TimeInForce_IOC),
    OrderType.FAK: (SZSE_FTDC_OrdType_Limit, SZSE_FTDC_TimeInForce_FOK),
}
ORDERTYPE_STOCK2VT = {v: k for k, v in ORDERTYPE_VT2STOCK.items()}

DIRECTION_STOCK2VT = {
    SZSE_FTDC_SIDE_Buy: Direction.LONG,
    SZSE_FTDC_SIDE_Sell: Direction.SHORT
}
DIRECTION_VT2STOCK = {v: k for k, v in DIRECTION_STOCK2VT.items()}

OFFSET_STOCK2VT = {
    SZSE_FTDC_OC_Open: Offset.OPEN,
    SZSE_FTDC_OC_Close: Offset.CLOSE
}
OFFSET_VT2STOCK = {v: k for k, v in OFFSET_STOCK2VT.items()}

STATUS_STOCK2VT = {
    SZSE_FTDC_Status_Success: Status.NOTTRADED,
    SZSE_FTDC_Status_Trade: Status.PARTTRADED,
    SZSE_FTDC_Status_All: Status.ALLTRADED,
    SZSE_FTDC_Status_Cancel: Status.CANCELLED,
    SZSE_FTDC_Status_Reject: Status.REJECTED
}


symbol_exchange_map = {}
symbol_name_map = {}
symbol_size_map = {}


class NhGateway(BaseGateway):
    """"""

    default_setting = {
        "用户名": "",
        "密码": "",
        "股东号": "",
        "交易服务器": "",
        "行情服务器": "",
        "产品代码": "",
        "授权码": "",
    }

    def __init__(self, event_engine, td_class, gateway_name):
        """Constructor"""
        super().__init__(event_engine, gateway_name)

        self.md_api = NhMdApi(self)
        self.td_api = td_class(self)

    def connect(self, setting: dict):
        """"""
        userid = setting["用户名"]
        password = setting["密码"]
        party_id = setting["股东号"]
        td_address = setting["交易服务器"]
        md_address = setting["行情服务器"]
        appid = setting["产品代码"]
        auth_code = setting["授权码"]

        if not td_address.startswith("tcp://"):
            td_address = "tcp://" + td_address

        if not md_address.startswith("tcp://"):
            md_address = "tcp://" + md_address

        self.td_api.connect(td_address, userid, password, party_id, appid, auth_code)
        self.md_api.connect(md_address, userid, password)

        self.init_query()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.md_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        vt_orderid = self.td_api.send_order(req)
        return vt_orderid

    def cancel_order(self, req: CancelRequest):
        """"""
        self.td_api.cancel_order(req)

    def query_account(self):
        """"""
        self.td_api.query_account()

    def query_position(self):
        """"""
        self.td_api.query_position()

    def close(self):
        """"""
        self.td_api.close()
        self.md_api.close()

    def write_error(self, msg: str, error: dict):
        """"""
        error_id = error["ErrorID"]
        error_msg = error["ErrorMsg"]
        if not error_msg:
            error_msg = ERROR_MSG.get(error_id, "")

        msg = f"{msg}，代码：{error_id}，信息：{error_msg}"
        self.write_log(msg)

    def process_timer_event(self, event):
        """"""
        self.count += 1
        if self.count < 2:
            return
        self.count = 0

        func = self.query_functions.pop(0)
        func()
        self.query_functions.append(func)

        self.md_api.update_date()

    def init_query(self):
        """"""
        self.count = 0
        self.query_functions = [self.query_account, self.query_position]
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def send_exercise(self, req: dict):
        """"""
        self.td_api.send_exercise(req)

    def cancel_exercise(self, req: CancelRequest):
        """"""
        self.td_api.cancel_exercise(req)

    def query_exercise(self):
        """"""
        self.td_api.query_exercise()


class NhFuturesGateway(NhGateway):

    exchanges = list(EXCHANGE_FUTURES2VT.values())

    def __init__(self, event_engine):
        """"""
        super().__init__(event_engine, NhFuturesTdApi, "NHFUTURES")


class NhStockGateway(NhGateway):

    exchanges = [Exchange.SSE, Exchange.SZSE]

    def __init__(self, event_engine):
        """"""
        super().__init__(event_engine, NhStockTdApi, "NHSTOCK")


class NhMdApi(MdApi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.reqid = 0

        self.connect_status = False
        self.login_status = False
        self.subscribed = set()

        self.userid = ""
        self.password = ""

        self.current_date = datetime.now().strftime("%Y%m%d")

    def connect(self, address: str, userid: str, password: str):
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password

        # If not connected, then start connection first.
        if not self.connect_status:
            self.createMdApi()
            self.registerFront(address)
            self.init()

            self.connect_status = True
        # If already connected, then login immediately.
        elif not self.login_status:
            self.login()

    def login(self):
        """
        Login onto server.
        """
        req = {
            "developer_code": "xuwanxin",
            "developer_license": "xwx123",
            # "user_id": self.userid,
            # "user_password": self.password,
            "user_id": "xwx",
            "user_password": "123456",
        }
        self.reqid += 1
        self.reqUtpLogin(req, self.reqid)

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data update.
        """
        exchange_str = EXCHANGE_VT2MD[req.exchange]

        if req.exchange in {Exchange.SSE, Exchange.SZSE}:
            # Index: MD001
            # Equity: MD002
            # Bond: MD003
            # ETF: MD004
            # Option: M0301
            key = f"{exchange_str}.M0301.{req.symbol}"
        else:
            key = f"{exchange_str}.{req.symbol}"

        if self.login_status:
            self.reqid += 1
            self.reqSubscribe(key, self.reqid)

        self.subscribed.add(key)

    def close(self):
        """
        Close the connection.
        """
        if self.connect_status:
            self.exit()

    def update_date(self):
        """"""
        self.current_date = datetime.now().strftime("%Y%m%d")

    def onFrontConnected(self) -> None:
        """"""
        self.gateway.write_log("行情服务器连接成功")
        self.login()

    def onFrontDisConnected(self) -> None:
        """"""
        self.login_status = False
        self.gateway.write_log("行情服务器连接断开")

    def onHeartBeatWarning(self, timeLapse: int) -> None:
        """"""
        pass

    def onRspError(self, error: dict, reqid: int) -> None:
        """"""
        msg = f"行情接口报错，错误信息{error['error_message']}"
        self.gateway.write_log(msg)

    def onRtnMarketData(self, data: dict) -> None:
        """"""
        symbol = data["instrument_id"]

        if symbol not in symbol_exchange_map:
            return
        exchange = symbol_exchange_map.get(symbol)

        timestamp = f"{self.current_date} {data['update_time']}.{int(data['update_millisec']/100)}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H:%M:%S.%f")
        dt = CHINA_TZ.localize(dt)

        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=dt,
            name=symbol_name_map.get(symbol, ""),
            volume=data["volume"],
            open_interest=data["open_interest"],
            last_price=data["last_price"],
            limit_up=data["upper_limit_price"],
            limit_down=data["lower_limit_price"],
            open_price=adjust_price(data["open_price"]),
            high_price=adjust_price(data["highest_price"]),
            low_price=adjust_price(data["lowest_price"]),
            pre_close=adjust_price(data["pre_close_price"]),
            bid_price_1=adjust_price(data["bid_price1"]),
            ask_price_1=adjust_price(data["ask_price1"]),
            bid_volume_1=data["bid_volume1"],
            ask_volume_1=data["ask_volume1"],
            gateway_name=self.gateway_name
        )

        if data["bid_volume2"] or data["ask_volume2"]:
            tick.bid_price_2 = adjust_price(data["bid_price2"])
            tick.bid_price_3 = adjust_price(data["bid_price3"])
            tick.bid_price_4 = adjust_price(data["bid_price4"])
            tick.bid_price_5 = adjust_price(data["bid_price5"])

            tick.ask_price_2 = adjust_price(data["ask_price2"])
            tick.ask_price_3 = adjust_price(data["ask_price3"])
            tick.ask_price_4 = adjust_price(data["ask_price4"])
            tick.ask_price_5 = adjust_price(data["ask_price5"])

            tick.bid_volume_2 = data["bid_volume2"]
            tick.bid_volume_3 = data["bid_volume3"]
            tick.bid_volume_4 = data["bid_volume4"]
            tick.bid_volume_5 = data["bid_volume5"]

            tick.ask_volume_2 = data["ask_volume2"]
            tick.ask_volume_3 = data["ask_volume3"]
            tick.ask_volume_4 = data["ask_volume4"]
            tick.ask_volume_5 = data["ask_volume5"]

        self.gateway.on_tick(tick)

    def onRspUtpLogin(self, data: dict, reqid: int) -> None:
        """"""
        if not data["response_code"]:
            self.login_status = True
            self.gateway.write_log("行情服务器登录成功")

            for key in self.subscribed:
                self.reqid += 1
                self.reqSubscribe(key, self.reqid)
        else:
            msg = f"行情服务器登录失败，错误信息{data['response_string']}"
            self.gateway.write_log(msg)

    def onRspUtpLogout(self, data: dict, reqid: int) -> None:
        """"""
        pass

    def onRspSubscribe(self, data: dict, reqid: int) -> None:
        """"""
        if data["response_code"]:
            msg = f"行情订阅失败，错误信息{data['response_string']}"
            self.gateway.write_log(msg)

    def onRspUnSubscribe(self, data: dict, reqid: int) -> None:
        """"""
        pass

    def onRspQryExchange(self, data: dict, reqid: int) -> None:
        """"""
        pass

    def onRspQryInstrument(self, data: dict, reqid: int) -> None:
        """"""
        pass


class NhFuturesTdApi(FuturesTdApi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.reqid = 0
        self.order_ref = 0

        self.connect_status = False
        self.login_status = False
        self.auth_status = False
        self.login_failed = False
        self.contract_inited = False

        self.userid = ""
        self.password = ""
        self.auth_code = ""
        self.appid = ""
        self.product_info = ""

        self.frontid = 0
        self.sessionid = 0

        self.order_data = []
        self.trade_data = []
        self.positions = {}
        self.sysid_orderid_map = {}

    def onFrontConnected(self):
        """"""
        self.gateway.write_log("交易服务器连接成功")

        if self.auth_code:
            self.authenticate()
        else:
            self.login()

    def onFrontDisconnected(self, reason: int):
        """"""
        self.login_status = False
        self.gateway.write_log(f"交易服务器连接断开，原因{reason}")

    def onRspAuthenticate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error['ErrorID']:
            self.auth_status = True
            self.gateway.write_log("交易服务器授权验证成功")
            self.login()
        else:
            self.gateway.write_error("交易服务器授权验证失败", error)

    def onRspUserLogin(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error["ErrorID"]:
            self.frontid = data["FrontID"]
            self.sessionid = data["SessionID"]
            self.login_status = True
            self.gateway.write_log("交易服务器登录成功")

            # Confirm settlement
            req = {
                "InvestorID": self.userid
            }
            self.reqid += 1
            self.reqSettlementInfoConfirm(req, self.reqid)
        else:
            self.login_failed = True

            self.gateway.write_error("交易服务器登录失败", error)

    def onRspOrderInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        order_ref = data["OrderRef"]
        orderid = f"{self.frontid}_{self.sessionid}_{order_ref}"

        symbol = data["InstrumentID"]
        exchange = symbol_exchange_map[symbol]

        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=orderid,
            direction=DIRECTION_FUTURES2VT[data["Direction"]],
            offset=OFFSET_FUTURES2VT.get(data["CombOffsetFlag"], Offset.NONE),
            price=data["LimitPrice"],
            volume=data["VolumeTotalOriginal"],
            status=Status.REJECTED,
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)

        self.gateway.write_error("交易委托失败", error)

    def onRspOrderAction(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        self.gateway.write_error("交易撤单失败", error)

    def onRspQueryMaxOrderVolume(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass

    def onRspSettlementInfoConfirm(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of settlment info confimation.
        """
        self.gateway.write_log("结算信息确认成功")

        while True:
            self.reqid += 1
            n = self.reqQryInstrument({}, self.reqid)

            if not n:
                break
            else:
                sleep(1)

    def onRspQryInvestorPosition(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not data:
            return

        # Check if contract data received
        if data["InstrumentID"] in symbol_exchange_map:
            # Get buffered position object
            key = f"{data['InstrumentID'], data['PosiDirection']}"
            position = self.positions.get(key, None)
            if not position:
                position = PositionData(
                    symbol=data["InstrumentID"],
                    exchange=symbol_exchange_map[data["InstrumentID"]],
                    direction=DIRECTION_FUTURES2VT[data["PosiDirection"]],
                    gateway_name=self.gateway_name
                )
                self.positions[key] = position

            # For SHFE and INE position data update
            if position.exchange in [Exchange.SHFE, Exchange.INE]:
                if data["YdPosition"] and not data["TodayPosition"]:
                    position.yd_volume = data["Position"]
            # For other exchange position data update
            else:
                position.yd_volume = data["Position"] - data["TodayPosition"]

            # Get contract size (spread contract has no size value)
            size = symbol_size_map.get(position.symbol, 0)

            # Calculate previous position cost
            cost = position.price * position.volume * size

            # Update new position volume
            position.volume += data["Position"]
            position.pnl += data["PositionProfit"]

            # Calculate average position price
            if position.volume and size:
                cost += data["PositionCost"]
                position.price = cost / (position.volume * size)

            # Get frozen volume
            if position.direction == Direction.LONG:
                position.frozen += data["ShortFrozen"]
            else:
                position.frozen += data["LongFrozen"]

        if last:
            for position in self.positions.values():
                self.gateway.on_position(position)

            self.positions.clear()

    def onRspQryTradingAccount(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if "AccountID" not in data:
            return

        account = AccountData(
            accountid=data["AccountID"],
            balance=data["Balance"],
            frozen=data["FrozenMargin"] + data["FrozenCash"] + data["FrozenCommission"],
            gateway_name=self.gateway_name
        )
        account.available = data["Available"]
        self.gateway.on_account(account)

    def onRspQryInstrument(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of instrument query.
        """
        product = PRODUCT_FUTURES2VT.get(data["ProductClass"], None)
        if product:
            contract = ContractData(
                symbol=data["InstrumentID"],
                exchange=EXCHANGE_FUTURES2VT[data["ExchangeID"]],
                name=data["InstrumentName"],
                product=product,
                size=data["VolumeMultiple"],
                pricetick=data["PriceTick"],
                gateway_name=self.gateway_name
            )

            # For option only
            if contract.product == Product.OPTION:
                # Remove C/P suffix of CZCE option product name
                if contract.exchange == Exchange.CZCE:
                    contract.option_portfolio = data["ProductID"][:-1]
                else:
                    contract.option_portfolio = data["ProductID"]

                contract.option_underlying = data["UnderlyingInstrID"]
                contract.option_type = OPTIONTYPE_FUTURES2VT.get(data["OptionsType"], None)
                contract.option_strike = data["StrikePrice"]
                contract.option_index = str(data["StrikePrice"])
                contract.option_expiry = datetime.strptime(data["ExpireDate"], "%Y%m%d")

            self.gateway.on_contract(contract)

            symbol_exchange_map[contract.symbol] = contract.exchange
            symbol_name_map[contract.symbol] = contract.name
            symbol_size_map[contract.symbol] = contract.size

        if last:
            self.contract_inited = True
            self.gateway.write_log("合约信息查询成功")

            for data in self.order_data:
                self.onRtnOrder(data)
            self.order_data.clear()

            for data in self.trade_data:
                self.onRtnTrade(data)
            self.trade_data.clear()

    def onRtnOrder(self, data: dict):
        """
        Callback of order status update.
        """
        if not self.contract_inited:
            self.order_data.append(data)
            return

        symbol = data["InstrumentID"]
        exchange = symbol_exchange_map[symbol]

        frontid = data["FrontID"]
        sessionid = data["SessionID"]
        order_ref = data["OrderRef"]
        orderid = f"{frontid}_{sessionid}_{order_ref}"

        timestamp = f"{data['InsertDate']} {data['InsertTime']}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H:%M:%S")
        dt = CHINA_TZ.localize(dt)

        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=orderid,
            type=ORDERTYPE_FUTURES2VT[data["OrderPriceType"]],
            direction=DIRECTION_FUTURES2VT[data["Direction"]],
            offset=OFFSET_FUTURES2VT[data["CombOffsetFlag"]],
            price=data["LimitPrice"],
            volume=data["VolumeTotalOriginal"],
            traded=data["VolumeTraded"],
            status=STATUS_FUTURES2VT[data["OrderStatus"]],
            datetime=dt,
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)

        self.sysid_orderid_map[data["OrderSysID"]] = orderid

    def onRtnTrade(self, data: dict):
        """
        Callback of trade status update.
        """
        if not self.contract_inited:
            self.trade_data.append(data)
            return

        symbol = data["InstrumentID"]
        exchange = symbol_exchange_map[symbol]

        orderid = self.sysid_orderid_map[data["OrderSysID"]]

        timestamp = f"{data['TradeDate']} {data['TradeTime']}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H:%M:%S")
        dt = CHINA_TZ.localize(dt)

        trade = TradeData(
            symbol=symbol,
            exchange=exchange,
            orderid=orderid,
            tradeid=data["TradeID"],
            direction=DIRECTION_FUTURES2VT[data["Direction"]],
            offset=OFFSET_FUTURES2VT[data["OffsetFlag"]],
            price=data["Price"],
            volume=data["Volume"],
            datetime=dt,
            gateway_name=self.gateway_name
        )
        self.gateway.on_trade(trade)

    def onRspForQuoteInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error["ErrorID"]:
            symbol = data["InstrumentID"]
            msg = f"{symbol}询价请求发送成功"
            self.gateway.write_log(msg)
        else:
            self.gateway.write_error("询价请求发送失败", error)

    def connect(
        self,
        address: str,
        userid: str,
        password: str
    ):
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password

        if not self.connect_status:
            path = get_folder_path(self.gateway_name.lower())
            self.createFtdcTraderApi((str(path) + "\\Td").encode("GBK"))

            self.subscribePrivateTopic(0)
            self.subscribePublicTopic(0)

            self.registerFront(address)
            self.init()

            self.connect_status = True
        else:
            self.authenticate()

    def authenticate(self):
        """
        Authenticate with auth_code and appid.
        """
        req = {
            "UserID": self.userid,
            "BrokerID": self.brokerid,
            "AuthCode": self.auth_code,
            "AppID": self.appid
        }

        if self.product_info:
            req["UserProductInfo"] = self.product_info

        self.reqid += 1
        self.reqAuthenticate(req, self.reqid)

    def login(self):
        """
        Login onto server.
        """
        if self.login_failed:
            return

        req = {
            "UserID": self.userid,
            "Password": self.password,
            "BrokerID": self.brokerid,
            "AppID": self.appid
        }

        if self.product_info:
            req["UserProductInfo"] = self.product_info

        self.reqid += 1
        self.reqUserLogin(req, self.reqid)

    def send_order(self, req: OrderRequest):
        """
        Send new order.
        """
        if req.offset not in OFFSET_VT2FUTURES:
            self.gateway.write_log("请选择开平方向")
            return ""

        if req.type not in ORDERTYPE_VT2FUTURES:
            self.gateway.write_log(f"当前接口不支持该类型的委托{req.type.value}")
            return ""

        self.order_ref += 1

        nh_req = {
            "InstrumentID": req.symbol,
            "ExchangeID": req.exchange.value,
            "LimitPrice": req.price,
            "VolumeTotalOriginal": int(req.volume),
            "OrderPriceType": ORDERTYPE_VT2FUTURES.get(req.type, ""),
            "Direction": DIRECTION_VT2FUTURES.get(req.direction, ""),
            "CombOffsetFlag": OFFSET_VT2FUTURES.get(req.offset, ""),
            "OrderRef": str(self.order_ref),
            "InvestorID": self.userid,
            "UserID": self.userid,
            "BrokerID": self.brokerid,
            "CombHedgeFlag": THOST_FTDC_HF_Speculation,
            "ContingentCondition": THOST_FTDC_CC_Immediately,
            "ForceCloseReason": THOST_FTDC_FCC_NotForceClose,
            "IsAutoSuspend": 0,
            "TimeCondition": THOST_FTDC_TC_GFD,
            "VolumeCondition": THOST_FTDC_VC_AV,
            "MinVolume": 1
        }

        if req.type == OrderType.FAK:
            nh_req["OrderPriceType"] = THOST_FTDC_OPT_LimitPrice
            nh_req["TimeCondition"] = THOST_FTDC_TC_IOC
            nh_req["VolumeCondition"] = THOST_FTDC_VC_AV
        elif req.type == OrderType.FOK:
            nh_req["OrderPriceType"] = THOST_FTDC_OPT_LimitPrice
            nh_req["TimeCondition"] = THOST_FTDC_TC_IOC
            nh_req["VolumeCondition"] = THOST_FTDC_VC_CV

        self.reqid += 1
        self.reqOrderInsert(nh_req, self.reqid)

        orderid = f"{self.frontid}_{self.sessionid}_{self.order_ref}"
        order = req.create_order_data(orderid, self.gateway_name)
        self.gateway.on_order(order)

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """
        Cancel existing order.
        """
        frontid, sessionid, order_ref = req.orderid.split("_")

        nh_req = {
            "InstrumentID": req.symbol,
            "ExchangeID": req.exchange.value,
            "OrderRef": order_ref,
            "FrontID": int(frontid),
            "SessionID": int(sessionid),
            "ActionFlag": THOST_FTDC_AF_Delete,
            "BrokerID": self.brokerid,
            "InvestorID": self.userid
        }

        self.reqid += 1
        self.reqOrderAction(nh_req, self.reqid)

    def send_rfq(self, req: OrderRequest) -> str:
        """"""
        self.order_ref += 1

        nh_req = {
            "InstrumentID": req.symbol,
            "ExchangeID": req.exchange.value,
            "ForQuoteRef": str(self.order_ref),
            "BrokerID": self.brokerid,
            "InvestorID": self.userid
        }

        self.reqid += 1
        self.reqForQuoteInsert(nh_req, self.reqid)

        orderid = f"{self.frontid}_{self.sessionid}_{self.order_ref}"
        vt_orderid = f"{self.gateway_name}.{orderid}"

        return vt_orderid

    def query_account(self):
        """
        Query account balance data.
        """
        self.reqid += 1
        self.reqQryTradingAccount({}, self.reqid)

    def query_position(self):
        """
        Query position holding data.
        """
        if not symbol_exchange_map:
            return

        req = {
            "BrokerID": self.brokerid,
            "InvestorID": self.userid
        }

        self.reqid += 1
        self.reqQryInvestorPosition(req, self.reqid)

    def close(self):
        """"""
        if self.connect_status:
            self.exit()


class NhStockTdApi(StockTdApi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.reqid = 0
        # self.order_ref = 0

        prefix = datetime.now().strftime("%H%M%S0000")
        self.order_ref = int(prefix)

        self.connect_status = False
        self.login_status = False
        self.auth_status = False
        self.login_failed = False
        self.contract_inited = False

        self.userid = ""
        self.password = ""
        self.auth_code = ""
        self.appid = ""
        self.product_info = ""

        self.party_id = ""

        self.today_date = ""
        self.order_data = []
        self.trade_data = []

        self.orders = {}

        self.instrument_countdown = 0

    def connect(
        self,
        address: str,
        userid: str,
        password: str,
        party_id: str,
        appid: str,
        auth_code: str,
    ):
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.party_id = party_id
        self.appid = appid
        self.auth_code = auth_code

        if not self.connect_status:
            path = get_folder_path(self.gateway_name.lower())
            self.createStockTdApi((str(path) + "\\Td").encode("GBK"))

            self.subscribePrivateTopic(0)
            self.subscribePublicTopic(0)
            self.subscribeUserTopic(0)

            self.registerFront(address)
            self.init("", "")

            self.connect_status = True
        else:
            self.login()

    def login(self):
        """
        Login onto server.
        """
        if self.login_failed:
            return

        req = {
            "UserID": self.userid,
            "Password": self.password,
            "UserProductInfo": self.appid,
            "InterfaceProductInfo": self.auth_code
        }

        self.reqid += 1
        self.reqUserLogin(req, self.reqid)

    def send_order(self, req: OrderRequest):
        """
        Send new order.
        """
        if req.offset not in OFFSET_VT2STOCK:
            self.gateway.write_log("请选择开平方向")
            return ""

        if req.type not in ORDERTYPE_VT2STOCK:
            self.gateway.write_log(f"当前接口不支持该类型的委托{req.type.value}")
            return ""

        self.order_ref += 1
        ord_type, time_in_force = ORDERTYPE_VT2STOCK[req.type]

        nh_req = {
            "SecurityID": req.symbol,
            "Price": req.price,
            "OrderQty": int(req.volume),
            "OrdType": ord_type,
            "Side": DIRECTION_VT2STOCK[req.direction],
            "PositionEffect": OFFSET_VT2STOCK[req.offset],
            "TimeInForce": time_in_force,
            "ClOrdID": self.order_ref,
            "PartyID": self.party_id,
            "CoveredOrUncovered": 1,
            "OwnerType": 1
        }

        self.reqid += 1
        self.reqOptionsInsert(nh_req, self.reqid)

        orderid = str(self.order_ref)
        order = req.create_order_data(orderid, self.gateway_name)
        self.orders[orderid] = order

        self.gateway.on_order(order)
        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """
        Cancel existing order.
        """
        self.order_ref += 1

        nh_req = {"ClOrdID": self.order_ref}

        if req.orderid in self.orders:
            nh_req["OrigClOrdID"] = int(req.orderid)
        else:
            nh_req["OrderID"] = req.orderid

        self.reqid += 1
        self.reqOptionsCancel(nh_req, self.reqid)

    def query_instrument(self, event: Event):
        """"""
        self.instrument_countdown -= 1
        if self.instrument_countdown:
            return
        self.gateway.event_engine.unregister(EVENT_TIMER, self.query_instrument)

        self.reqid += 1
        self.reqQryOptions({}, self.reqid)

    def query_client(self):
        """"""
        self.reqid += 1
        self.reqQryClient(self.reqid)

    def query_account(self):
        """
        Query account balance data.
        """
        if not self.party_id:
            return
        req = {"PartyID": self.party_id}

        self.reqid += 1
        self.reqQryPartAccount(req, self.reqid)

    def query_position(self):
        """
        Query position holding data.
        """
        if not self.party_id:
            return
        req = {"PartyID": self.party_id}

        self.reqid += 1
        self.reqQryPosition(req, self.reqid)

    def close(self):
        """"""
        if self.connect_status:
            self.exit()

    def send_exercise(self, req: dict):
        """"""
        self.order_ref += 1
        self.reqid += 1

        leg1_symbol = req.get("leg1_symbol", "")
        leg2_symbol = req.get("leg2_symbol", "")

        # 单腿行权
        if not leg2_symbol:
            nh_req = {
                "ClOrdID": self.order_ref,
                "SecurityID": req["leg1_symbol"],
                "OwnerType": 1,
                "OrderQty": req["volume"],
                "PartyID": self.party_id,
            }
            self.reqExercise(nh_req, self.reqid)
        # 组合行权
        else:
            nh_req = {
                "ClOrdID": self.order_ref,
                "OwnerType": 1,
                "OrderQty": req["volume"],
                "PartyID": self.party_id,
                "LegSecurityID1": leg1_symbol,
                "LegOrderQty1": req["volume"],
                "LegSecurityID2": leg2_symbol,
                "LegOrderQty2": req["volume"],
            }
            self.reqCombExercise(nh_req, self.reqid)

    def cancel_exercise(self, req: CancelRequest):
        """"""
        self.reqid += 1
        nh_req = {"OrderID": req.orderid}
        self.reqExerciseCancel(nh_req, self.reqid)

    def query_exercise(self):
        """"""
        self.reqid += 1
        nh_req = {"PartyID": self.party_id}
        self.reqQryExercise(nh_req, self.reqid)

    def onFrontConnected(self) -> None:
        """"""
        self.gateway.write_log("交易服务器连接成功")
        self.connect_status = True

        if not self.login_status:
            self.login()

    def onFrontDisconnected(self, reqid: int) -> None:
        """"""
        self.login_status = False
        self.gateway.write_log(f"交易服务器连接断开，原因{reqid}")

    def onHeartBeatWarning(self, reqid: int) -> None:
        """"""
        pass

    def onRspSubscribeTopic(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspUserLogin(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        if not error["ErrorID"]:
            self.login_status = True
            self.gateway.write_log("交易服务器登录成功")

            self.order_ref = max(self.order_ref, data["MaxClOrdID"])
            self.today_date = data["TradingDay"]

            # self.query_instrument()
            self.instrument_countdown = 10
            self.gateway.event_engine.register(EVENT_TIMER, self.query_instrument)
        else:
            self.login_failed = True
            self.gateway.write_error("交易服务器登录失败", error)

    def onRspUserLogout(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspUserPasswordUpdate(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspStockInsert(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspStockCancel(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspOptionsInsert(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        if error["ErrorID"]:
            orderid = str(data["ClOrdID"])
            order = self.orders[orderid]
            order.status = Status.REJECTED
            self.gateway.on_order(copy(order))

            self.gateway.write_error("交易委托失败", error)

    def onRspOptionsCancel(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        if error["ErrorID"]:
            self.gateway.write_error("交易撤单失败", error)

    def onRspQuoteInsert(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspForQuote(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspQuoteCancel(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspStockLock(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspExercise(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        if error["ErrorID"]:
            msg = error["ErrorMsg"]
            self.gateway.on_event(EVENT_NH_EXERCISE_LOG, msg)
            return

        exercise = {
            "orderid": data["OrderID"],
            "volume": data["OrderQty"],
            "active": True,
            "leg1_symbol": data["SecurityID"],
        }
        self.gateway.on_event(EVENT_NH_EXERCISE, exercise)

    def onRspExerciseCancel(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        if error["ErrorID"]:
            msg = error["ErrorMsg"]
            self.gateway.on_event(EVENT_NH_EXERCISE_LOG, msg)
            return

        exercise = {
            "orderid": data["OrderID"],
            "volume": data["OrderQty"],
            "active": False,
            "leg1_symbol": data["SecurityID"],
        }
        self.gateway.on_event(EVENT_NH_EXERCISE, exercise)

    def onRspQryPartAccount(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        if data["PartyID"]:
            account = AccountData(
                accountid=data["PartyID"],
                balance=data["Balance"],
                frozen=data["FrozenMargin"] + data["FrozenPremium"] + data["FrozenCommi"],
                gateway_name=self.gateway_name
            )
            account.available = data["Available"]
            self.gateway.on_account(account)

    def onRspQryStockOrder(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspQryOptionsOrder(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspQryQuoteOrder(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspQryStockTrade(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspQryOptionsTrade(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspQryPosition(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        # Check if contract data received
        if data["SecurityID"] in symbol_exchange_map:
            size = symbol_size_map[data["SecurityID"]]
            price = data["PositionCost"] / (data["Position"] * size)

            position = PositionData(
                symbol=data["SecurityID"],
                exchange=symbol_exchange_map[data["SecurityID"]],
                direction=DIRECTION_STOCK2VT[data["Side"]],
                volume=data["Position"],
                yd_volume=data["YdPosition"],
                price=price,
                gateway_name=self.gateway_name
            )

            self.gateway.on_position(position)

    def onRspQryTopic(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspQryStock(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspQryOptions(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        if data["contractid"]:
            if data["contractid"].startswith("9"):
                exchange = Exchange.SZSE
            else:
                exchange = Exchange.SSE

            contract = ContractData(
                symbol=data["contractid"],
                exchange=exchange,
                name=data["contractsymbol"],
                product=Product.OPTION,
                size=data["contractmultiplierunit"],
                pricetick=data["ticksize"],
                option_portfolio=data["underlyingsecurityid"],
                option_underlying=data["underlyingsecurityid"] + "_" + data["expiredate"],
                option_type=OPTIONTYPE_STOCK2VT[data["callorput"]],
                option_strike=data["exerciseprice"],
                option_expiry=datetime.strptime(data["expiredate"], "%Y%m%d"),
                gateway_name=self.gateway_name
            )

            contract.option_index = get_option_index(
                contract.option_strike,
                data["contractsymbol"]
            )

            self.gateway.on_contract(contract)

            symbol_exchange_map[contract.symbol] = contract.exchange
            symbol_name_map[contract.symbol] = contract.name
            symbol_size_map[contract.symbol] = contract.size

        if last:
            self.contract_inited = True
            self.gateway.write_log("合约信息查询成功")

            for data in self.order_data:
                self.onRtnOptionsOrder(data)
            self.order_data.clear()

            for data in self.trade_data:
                self.onRtnOptionsTrade(data)
            self.trade_data.clear()

    def onRtnOptionsOrder(self, data: dict) -> None:
        """"""
        if not self.contract_inited:
            self.order_data.append(data)
            return

        symbol = data["SecurityID"]
        exchange = symbol_exchange_map[symbol]
        orderid = str(data["ClOrdID"])

        # Use system orderid for order from previous session
        if orderid not in self.orders:
            orderid = data["OrderID"]

        timestamp = f"{self.today_date} {data['TransactTimeOnly']}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H%M%S")
        dt = CHINA_TZ.localize(dt)

        order_type = ORDERTYPE_STOCK2VT[(data["OrdType"], data["TimeInForce"])]

        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=orderid,
            type=order_type,
            direction=DIRECTION_STOCK2VT[data["Side"]],
            offset=OFFSET_STOCK2VT[data["PositionEffect"]],
            price=data["Price"],
            volume=data["OrderQty"],
            traded=data["TradeQty"],
            status=STATUS_STOCK2VT[data["OrdStatus"]],
            datetime=dt,
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)

    def onRtnStockOrder(self, data: dict) -> None:
        """"""
        pass

    def onRtnQuoteOrder(self, data: dict) -> None:
        """"""
        pass

    def onRtnOptionsTrade(self, data: dict) -> None:
        """"""
        if not self.contract_inited:
            self.trade_data.append(data)
            return

        symbol = data["SecurityID"]
        exchange = symbol_exchange_map[symbol]
        orderid = str(data["ClOrdID"])

        timestamp = f"{self.today_date} {data['TransactTimeOnly']}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H%M%S")
        dt = CHINA_TZ.localize(dt)

        trade = TradeData(
            symbol=symbol,
            exchange=exchange,
            orderid=orderid,
            tradeid=data["ExecID"],
            direction=DIRECTION_STOCK2VT[data["Side"]],
            offset=OFFSET_STOCK2VT[data["PositionEffect"]],
            price=data["LastPx"],
            volume=data["LastQty"],
            datetime=dt,
            gateway_name=self.gateway_name
        )
        self.gateway.on_trade(trade)

    def onRtnStockTrade(self, data: dict) -> None:
        """"""
        pass

    def onRtnExercise(self, data: dict) -> None:
        """"""
        exercise = {
            "orderid": data["OrderID"],
            "volume": data["OrderQty"],
            "active": True,
            "leg1_symbol": data["SecurityID"],
        }
        self.gateway.on_event(EVENT_NH_EXERCISE, exercise)

    def onRspQryRate(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspQryClient(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass
        # if data["PartyID"]:
        #     self.party_id = data["PartyID"]

        # if last:
        #     self.gateway.write_log("投资者账户查询成功")

        #     self.query_instrument()

    def onRspQryClientMargin(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspQryExercise(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        if error["ErrorID"]:
            msg = error["ErrorMsg"]
            self.gateway.on_event(EVENT_NH_EXERCISE_LOG, msg)
            return

        if data["OrderID"]:
            exercise = {
                "orderid": data["OrderID"],
                "volume": data["OrderQty"],
                "active": True,
                "leg1_symbol": data["SecurityID"],
            }
            self.gateway.on_event(EVENT_NH_EXERCISE, exercise)

    def onRtnWithdrawDeposit(self, data: dict) -> None:
        """"""
        pass

    def onRspMarginCombAction(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRtnMarginCombAction(self, data: dict) -> None:
        """"""
        pass

    def onRspQrySseCombPosition(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        pass

    def onRspCombExercise(self, data: dict, error: dict, reqid: int, last: bool) -> None:
        """"""
        exercise = {
            "orderid": data["OrderID"],
            "volume": data["OrderQty"],
            "active": True,
            "leg1_symbol": data["LegSecurityID1"],
            "leg2_symbol": data["LegSecurityID2"],
        }
        self.gateway.on_event(EVENT_NH_EXERCISE, exercise)


def adjust_price(price: float) -> float:
    """"""
    if price == MAX_FLOAT:
        price = 0
    return price


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
