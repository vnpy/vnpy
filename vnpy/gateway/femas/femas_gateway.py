# encoding: UTF-8
"""
"""

from datetime import datetime

from vnpy.api.femas import (
    MdApi,
    TdApi,
    USTP_FTDC_AF_Delete,
    USTP_FTDC_CAS_Accepted,
    USTP_FTDC_CAS_Rejected,
    USTP_FTDC_CAS_Submitted,
    USTP_FTDC_CHF_Speculation,
    USTP_FTDC_D_Buy,
    USTP_FTDC_D_Sell,
    USTP_FTDC_FCR_NotForceClose,
    USTP_FTDC_OF_Close,
    USTP_FTDC_OF_CloseToday,
    USTP_FTDC_OF_CloseYesterday,
    USTP_FTDC_OF_Open,
    USTP_FTDC_OPT_AnyPrice,
    USTP_FTDC_OPT_LimitPrice,
    USTP_FTDC_OS_AllTraded,
    USTP_FTDC_OS_Canceled,
    USTP_FTDC_OS_NoTradeQueueing,
    USTP_FTDC_OS_PartTradedQueueing,
    USTP_FTDC_OT_CallOptions,
    USTP_FTDC_OT_PutOptions,
    USTP_FTDC_TC_GFD,
    USTP_FTDC_TC_IOC,
    USTP_FTDC_VC_AV,
    USTP_FTDC_VC_CV
)
from vnpy.trader.constant import (
    Direction,
    Exchange,
    Offset,
    OptionType,
    OrderType,
    Status,
    Product
)
from vnpy.trader.event import EVENT_TIMER
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    AccountData,
    CancelRequest,
    ContractData,
    OrderData,
    OrderRequest,
    PositionData,
    SubscribeRequest,
    TickData,
    TradeData,
)
from vnpy.trader.utility import get_folder_path

USTP_FTDC_PD_Long = "2"
USTP_FTDC_PD_Short = "3"

STATUS_FEMAS2VT = {
    USTP_FTDC_CAS_Submitted: Status.SUBMITTING,
    USTP_FTDC_CAS_Accepted: Status.SUBMITTING,
    USTP_FTDC_CAS_Rejected: Status.REJECTED,
    USTP_FTDC_OS_NoTradeQueueing: Status.NOTTRADED,
    USTP_FTDC_OS_PartTradedQueueing: Status.PARTTRADED,
    USTP_FTDC_OS_AllTraded: Status.ALLTRADED,
    USTP_FTDC_OS_Canceled: Status.CANCELLED,
}

DIRECTION_VT2FEMAS = {
    Direction.LONG: USTP_FTDC_D_Buy,
    Direction.SHORT: USTP_FTDC_D_Sell,
}

ORDERTYPE_VT2FEMAS = {
    OrderType.LIMIT: USTP_FTDC_OPT_LimitPrice,
    OrderType.MARKET: USTP_FTDC_OPT_AnyPrice,
}

OFFSET_VT2FEMAS = {
    Offset.OPEN: USTP_FTDC_OF_Open,
    Offset.CLOSE: USTP_FTDC_OF_Close,
    Offset.CLOSETODAY: USTP_FTDC_OF_CloseYesterday,
    Offset.CLOSEYESTERDAY: USTP_FTDC_OF_CloseToday,
}
OFFSET_FEMAS2VT = {v: k for k, v in OFFSET_VT2FEMAS.items()}

DIRECTION_FEMAS2VT = {v: k for k, v in DIRECTION_VT2FEMAS.items()}
DIRECTION_FEMAS2VT[USTP_FTDC_PD_Long] = Direction.LONG
DIRECTION_FEMAS2VT[USTP_FTDC_PD_Short] = Direction.SHORT

EXCHANGE_FEMAS2VT = {
    "CFFEX": Exchange.CFFEX,
    "SHFE": Exchange.SHFE,
    "CZCE": Exchange.CZCE,
    "DCE": Exchange.DCE,
    "INE": Exchange.INE,
}

OPTIONTYPE_FEMAS2VT = {
    USTP_FTDC_OT_CallOptions: OptionType.CALL,
    USTP_FTDC_OT_PutOptions: OptionType.PUT,
}

symbol_exchange_map = {}
symbol_name_map = {}
symbol_size_map = {}


class FemasGateway(BaseGateway):
    """
    VN Trader Gateway for FEMAS .
    """

    default_setting = {
        "userid": "",
        "password": "",
        "brokerid": "",
        "td_address": "",
        "md_address": "",
    }

    exchanges = list(EXCHANGE_FEMAS2VT.values())

    def __init__(self, event_engine):
        """Constructor"""
        super(FemasGateway, self).__init__(event_engine, "FEMAS")

        self.td_api = FemasTdApi(self)
        self.md_api = FemasMdApi(self)

    def connect(self, setting: dict):
        """"""
        userid = setting["userid"]
        password = setting["password"]
        brokerid = setting["brokerid"]
        td_address = setting["td_address"]
        md_address = setting["md_address"]

        if not td_address.startswith("tcp://"):
            td_address = "tcp://" + td_address
        if not md_address.startswith("tcp://"):
            md_address = "tcp://" + md_address

        self.td_api.connect(td_address, userid, password, brokerid)
        self.md_api.connect(md_address, userid, password, brokerid)

        self.init_query()

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.md_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.td_api.send_order(req)

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

    def write_error(self, msg: str, error_id: int, error_msg: str):
        msg = f"{msg}，代码：{error_id}，信息：{error_msg}"
        self.write_log(msg)

    def if_error_write_error(self, msg: str, error: dict):
        """
        当有错误的时候就输出错误，并返回True
        """
        error_id = error["ErrorID"]
        if error_id:
            error_msg = error["ErrorMsg"]
            self.write_error(msg, error_id, error_msg)
            return True

    def process_timer_event(self, event):
        """"""
        self.count += 1
        if self.count < 2:
            return
        self.count = 0

        func = self.query_functions.pop(0)
        func()
        self.query_functions.append(func)

    def init_query(self):
        """"""
        self.count = 0
        self.query_functions = [self.query_account, self.query_position]
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)


class FemasMdApi(MdApi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super(FemasMdApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.reqid = 0

        self.connect_status = False
        self.login_status = False
        self.subscribed = set()

        self.userid = ""
        self.password = ""
        self.brokerid = 0

    def onFrontConnected(self):
        """
        Callback when front server is connected.
        """
        self.connect_status = True
        self.gateway.write_log("行情服务器连接成功")
        self.login()

    def onFrontDisconnected(self, reason: int):
        """
        Callback when front server is disconnected.
        """
        self.connect_status = False
        self.login_status = False
        self.gateway.write_log(f"行情服务器连接断开，原因{reason}")

    def onRspUserLogin(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback when user is logged in.
        """
        if self.gateway.if_error_write_error("行情服务器登录失败", error):
            return
        self.login_status = True
        self.gateway.write_log("行情服务器登录成功")

        for symbol in self.subscribed:
            self.subMarketData(symbol)

    def onRspError(self, error: dict, reqid: int, last: bool):
        """
        Callback when error occured.
        """
        self.gateway.if_error_write_error("行情接口报错", error)

    def onRspSubMarketData(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if self.gateway.if_error_write_error("行情订阅失败", error):
            return

    def onRtnDepthMarketData(self, data: dict):
        """
        Callback of tick data update.
        """
        symbol = data["InstrumentID"]
        exchange = symbol_exchange_map.get(symbol, "")
        if not exchange:
            return

        timestamp = f"{data['TradingDay']} {data['UpdateTime']}.{int(data['UpdateMillisec'] / 100)}"

        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=datetime.strptime(timestamp, "%Y%m%d %H:%M:%S.%f"),
            name=symbol_name_map[symbol],
            volume=data["Volume"],
            last_price=data["LastPrice"],
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
            gateway_name=self.gateway_name,
        )
        self.gateway.on_tick(tick)

    def connect(self, address: str, userid: str, password: str, brokerid: int):
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.brokerid = brokerid

        # If not connected, then start connection first.
        if not self.connect_status:
            path = get_folder_path(self.gateway_name.lower())
            self.createFtdcMdApi(str(path) + "\\Md")
            # 订阅主题
            self.subscribeMarketDataTopic(100, 2)
            self.registerFront(address)
            self.init()
        # If already connected, then login immediately.
        elif not self.login_status:
            self.login()

    def login(self):
        """
        Login onto server.
        """
        req = {
            "UserID": self.userid,
            "Password": self.password,
            "BrokerID": self.brokerid,
        }

        self.reqid += 1
        self.reqUserLogin(req, self.reqid)

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data update.
        """
        if self.login_status:
            self.subMarketData(req.symbol)
        self.subscribed.add(req.symbol)

    def close(self):
        """
        Close the connection.
        """
        if self.connect_status:
            self.exit()


class FemasTdApi(TdApi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super(FemasTdApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.reqid = 0
        self.localid = int(10e5 + 8888)

        self.connect_status = False
        self.login_status = False
        self.login_failed = False

        self.userid = ""
        self.password = ""
        self.brokerid = 0

        self.order_data = []
        self.trade_data = []
        self.positions = {}
        self.sysid_orderid_map = {}

    def onFrontConnected(self):
        """"""
        self.connect_status = True
        self.gateway.write_log("交易服务器连接成功")

        self.login()

    def onFrontDisconnected(self, reason: int):
        """"""
        self.connect_status = False
        self.login_status = False
        self.gateway.write_log(f"交易服务器连接断开，原因{reason}")

    def onRspUserLogin(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error["ErrorID"]:
            if data["MaxOrderLocalID"]:
                self.localid = int(data["MaxOrderLocalID"])

            self.login_status = True
            self.gateway.write_log("交易服务器登录成功")

            self.reqid += 1
            self.reqQryInstrument({}, self.reqid)
        else:
            self.login_failed = True

            self.gateway.if_error_write_error("交易服务器登录失败", error)

    def onRspOrderInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if self.gateway.if_error_write_error("交易委托失败", error):
            return

        orderid = data["UserOrderLocalID"]
        symbol = data["InstrumentID"]
        exchange = symbol_exchange_map[symbol]
        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=orderid,
            direction=DIRECTION_FEMAS2VT[data["Direction"]],
            offset=OFFSET_FEMAS2VT[data["OffsetFlag"]],
            price=data["LimitPrice"],
            volume=data["Volume"],
            status=Status.REJECTED,
            gateway_name=self.gateway_name,
        )
        self.gateway.on_order(order)

    def onRspOrderAction(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if self.gateway.if_error_write_error("交易撤单失败", error):
            return

    def onRspQueryMaxOrderVolume(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass

    def onRspSettlementInfoConfirm(
        self, data: dict, error: dict, reqid: int, last: bool
    ):
        """
        Callback of settlment info confimation.
        """
        self.gateway.write_log("结算信息确认成功")

        self.reqid += 1
        self.reqQryInstrument({}, self.reqid)

    def onRspQryInvestorPosition(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not data:
            return

        # Get buffered position object
        key = f"{data['InstrumentID'], data['Direction']}"
        position = self.positions.get(key, None)
        if not position:
            position = PositionData(
                symbol=data["InstrumentID"],
                exchange=symbol_exchange_map[data["InstrumentID"]],
                direction=DIRECTION_FEMAS2VT[data["Direction"]],
                gateway_name=self.gateway_name,
            )
            self.positions[key] = position

        position.yd_volume = data["YdPosition"]
        # Calculate previous position cost
        cost = position.price * position.volume

        # Update new position volume
        position.volume += data["Position"]

        # Calculate average position price
        if position.volume:
            cost += data["PositionCost"]
            position.price = cost / position.volume

        # Get frozen volume
        position.frozen += data["FrozenPosition"]

        if last:
            for position in self.positions.values():
                self.gateway.on_position(position)

            self.positions.clear()

    def onRspQryInvestorAccount(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        account = AccountData(
            accountid=data["AccountID"],
            frozen=data["LongMargin"] + data["ShortMargin"],
            balance=data["PreBalance"],
            gateway_name=self.gateway_name,
        )

        self.gateway.on_account(account)

    def onRspQryInstrument(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of instrument query.
        """
        # Femas gateway provides no ProductClass data, so need to determine
        # product type using other logic.
        option_type = OPTIONTYPE_FEMAS2VT.get(data["OptionsType"], None)
        if option_type:
            product = Product.OPTION
        elif data["InstrumentID_2"]:
            product = Product.SPREAD
        else:
            product = Product.FUTURES

        contract = ContractData(
            symbol=data["InstrumentID"],
            exchange=EXCHANGE_FEMAS2VT[data["ExchangeID"]],
            name=data["InstrumentName"],
            size=data["VolumeMultiple"],
            pricetick=data["PriceTick"],
            product=product,
            gateway_name=self.gateway_name
        )

        if product == Product.OPTION:
            contract.option_underlying = data["UnderlyingInstrID"]
            contract.option_type = OPTIONTYPE_FEMAS2VT.get(
                data["OptionsType"], None)
            contract.option_strike = data["StrikePrice"]
            contract.option_expiry = datetime.strptime(
                data["ExpireDate"], "%Y%m%d")

        self.gateway.on_contract(contract)

        symbol_exchange_map[contract.symbol] = contract.exchange
        symbol_name_map[contract.symbol] = contract.name
        symbol_size_map[contract.symbol] = contract.size

        if last:
            self.gateway.write_log("合约信息查询成功")

    def onRtnOrder(self, data: dict):
        """
        Callback of order status update.
        """
        # 更新最大报单编号
        self.localid = max(self.localid, int(
            data["UserOrderLocalID"]))  # 检查并增加本地报单编号

        symbol = data["InstrumentID"]
        exchange = symbol_exchange_map.get(symbol, "")
        if not exchange:
            self.order_data.append(data)
            return

        orderid = data["UserOrderLocalID"]
        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=orderid,
            direction=DIRECTION_FEMAS2VT[data["Direction"]],
            offset=OFFSET_FEMAS2VT[data["OffsetFlag"]],
            price=data["LimitPrice"],
            volume=data["Volume"],
            traded=data["VolumeTraded"],
            status=STATUS_FEMAS2VT[data["OrderStatus"]],
            time=data["InsertTime"],
            gateway_name=self.gateway_name,
        )
        self.gateway.on_order(order)

        self.sysid_orderid_map[data["OrderSysID"]] = orderid

    def onRtnTrade(self, data: dict):
        """
        Callback of trade status update.
        """
        symbol = data["InstrumentID"]
        exchange = symbol_exchange_map.get(symbol, "")
        if not exchange:
            self.trade_data.append(data)
            return

        orderid = self.sysid_orderid_map[data["OrderSysID"]]

        trade = TradeData(
            symbol=symbol,
            exchange=exchange,
            orderid=orderid,
            tradeid=data["TradeID"],
            direction=DIRECTION_FEMAS2VT[data["Direction"]],
            offset=OFFSET_FEMAS2VT[data["OffsetFlag"]],
            price=data["TradePrice"],
            volume=data["TradeVolume"],
            time=data["TradeTime"],
            gateway_name=self.gateway_name,
        )
        self.gateway.on_trade(trade)

    def connect(self, address: str, userid: str, password: str, brokerid: int):
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.brokerid = brokerid
        self.address = address

        if not self.connect_status:
            path = get_folder_path(self.gateway_name.lower())
            self.createFtdcTraderApi(str(path) + "\\Td")

            self.subscribePrivateTopic(0)
            self.subscribePublicTopic(0)
            self.subscribeUserTopic(0)

            self.registerFront(address)
            self.init()
        else:
            if not self.login_status:
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
            "BrokerID": self.brokerid,
        }

        self.reqid += 1
        self.reqUserLogin(req, self.reqid)

    def send_order(self, req: OrderRequest):
        """
        Send new order.
        """
        self.localid += 1
        orderid = str(self.localid).rjust(12, "0")

        femas_req = {
            "InstrumentID": req.symbol,
            "ExchangeID": str(req.exchange).split(".")[1],
            "BrokerID": self.brokerid,
            "InvestorID": self.userid,
            "UserID": self.userid,
            "LimitPrice": req.price,
            "Volume": int(req.volume),
            "OrderPriceType": ORDERTYPE_VT2FEMAS.get(req.type, ""),
            "Direction": DIRECTION_VT2FEMAS.get(req.direction, ""),
            "OffsetFlag": OFFSET_VT2FEMAS.get(req.offset, ""),
            "UserOrderLocalID": orderid,
            "HedgeFlag": USTP_FTDC_CHF_Speculation,
            "ForceCloseReason": USTP_FTDC_FCR_NotForceClose,
            "IsAutoSuspend": 0,
            "TimeCondition": USTP_FTDC_TC_GFD,
            "VolumeCondition": USTP_FTDC_VC_AV,
            "MinVolume": 1,
        }

        if req.type == OrderType.FAK:
            femas_req["OrderPriceType"] = USTP_FTDC_OPT_LimitPrice
            femas_req["TimeCondition"] = USTP_FTDC_TC_IOC
            femas_req["VolumeCondition"] = USTP_FTDC_VC_AV
        elif req.type == OrderType.FOK:
            femas_req["OrderPriceType"] = USTP_FTDC_OPT_LimitPrice
            femas_req["TimeCondition"] = USTP_FTDC_TC_IOC
            femas_req["VolumeCondition"] = USTP_FTDC_VC_CV

        self.reqid += 1
        self.reqOrderInsert(femas_req, self.reqid)

        order = req.create_order_data(orderid, self.gateway_name)
        self.gateway.on_order(order)

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """
        Cancel existing order.
        """
        self.localid += 1
        orderid = str(self.localid).rjust(12, "0")

        femas_req = {
            "InstrumentID": req.symbol,
            "ExchangeID": str(req.exchange).split(".")[1],
            "UserOrderLocalID": req.orderid,
            "UserOrderActionLocalID": orderid,
            "ActionFlag": USTP_FTDC_AF_Delete,
            "BrokerID": self.brokerid,
            "InvestorID": self.userid,
            "UserID": self.userid,
        }

        self.reqid += 1
        self.reqOrderAction(femas_req, self.reqid)

    def query_account(self):
        """
        Query account balance data.
        """
        req = {
            "BrokerID": self.brokerid,
            "InvestorID": self.userid,
            "UserID": self.userid,
        }
        self.reqid += 1
        self.reqQryInvestorAccount(req, self.reqid)

    def query_position(self):
        """
        Query position holding data.
        """
        if not symbol_exchange_map:
            return

        req = {
            "BrokerID": self.brokerid,
            "InvestorID": self.userid,
            "UserID": self.userid,
        }

        self.reqid += 1
        self.reqQryInvestorPosition(req, self.reqid)

    def close(self):
        """"""
        if self.connect_status:
            self.exit()
