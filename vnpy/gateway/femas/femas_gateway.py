""""""

import pytz
from datetime import datetime
from time import sleep

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
DIRECTION_FEMAS2VT = {v: k for k, v in DIRECTION_VT2FEMAS.items()}

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

CHINA_TZ = pytz.timezone("Asia/Shanghai")


symbol_exchange_map = {}
symbol_name_map = {}
symbol_size_map = {}


class FemasGateway(BaseGateway):
    """
    VN Trader Gateway for FEMAS .
    """

    default_setting = {
        "用户名": "",
        "密码": "",
        "经纪商代码": "",
        "交易服务器": "",
        "行情服务器": "",
        "产品名称": "",
        "授权编码": "",
        "产品信息": "",
    }

    exchanges = list(EXCHANGE_FEMAS2VT.values())

    def __init__(self, event_engine):
        """Constructor"""
        super(FemasGateway, self).__init__(event_engine, "FEMAS")

        self.td_api = FemasTdApi(self)
        self.md_api = FemasMdApi(self)

    def connect(self, setting: dict):
        """"""
        userid = setting["用户名"]
        password = setting["密码"]
        brokerid = setting["经纪商代码"]
        td_address = setting["交易服务器"]
        md_address = setting["行情服务器"]

        if not td_address.startswith("tcp://"):
            td_address = "tcp://" + td_address
        if not md_address.startswith("tcp://"):
            md_address = "tcp://" + md_address

        appid = setting["产品名称"]
        auth_code = setting["授权编码"]
        product_info = setting["产品信息"]

        self.td_api.connect(td_address, userid, password, brokerid, auth_code, appid, product_info)
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

    def write_error(self, msg: str, error: dict):
        """"""
        error_id = error["ErrorID"]
        error_msg = error["ErrorMsg"]
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
        self.auth_staus = False
        self.login_failed = False

        self.subscribed = set()

        self.userid = ""
        self.password = ""
        self.brokerid = 0

    def onFrontConnected(self):
        """
        Callback when front server is connected.
        """
        self.gateway.write_log("行情服务器连接成功")
        self.login()

    def onFrontDisconnected(self, reason: int):
        """
        Callback when front server is disconnected.
        """
        self.login_status = False
        self.gateway.write_log(f"行情服务器连接断开，原因{reason}")

    def onRspUserLogin(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback when user is logged in.
        """
        if not error["ErrorID"]:
            self.login_status = True
            self.gateway.write_log("行情服务器登录成功")

            for symbol in self.subscribed:
                self.subMarketData(symbol)
        else:
            self.gateway.write_error("行情服务器登录失败", error)

    def onRspError(self, error: dict, reqid: int, last: bool):
        """
        Callback when error occured.
        """
        self.gateway.write_error("行情接口报错", error)

    def onRspSubMarketData(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error or not error["ErrorID"]:
            return

        self.gateway.write_error("行情订阅失败", error)

    def onRtnDepthMarketData(self, data: dict):
        """
        Callback of tick data update.
        """
        symbol = data["InstrumentID"]
        exchange = symbol_exchange_map.get(symbol, "")
        if not exchange:
            return

        timestamp = f"{data['TradingDay']} {data['UpdateTime']}.{int(data['UpdateMillisec'] / 100)}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H:%M:%S.%f")
        dt = CHINA_TZ.localize(dt)

        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=dt,
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

            self.subscribeMarketDataTopic(100, 2)
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
        self.login_status = False

        self.userid = ""
        self.investorid = ""
        self.password = ""
        self.brokerid = 0
        self.auth_code = ""
        self.appid = ""
        self.product_info = ""

        self.positions = {}
        self.tradeids = set()

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

    def onRspDSUserCertification(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error["ErrorID"]:
            self.auth_staus = True
            self.gateway.write_log("交易服务器授权验证成功")
            self.login()
        else:
            self.gateway.write_error("交易服务器授权验证失败", error)

    def onRspUserLogin(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error["ErrorID"]:
            if data["MaxOrderLocalID"]:
                self.localid = int(data["MaxOrderLocalID"])

            self.login_status = True
            self.gateway.write_log("交易服务器登录成功")

            self.query_investor()
        else:
            self.login_failed = True

            self.gateway.write_error("交易服务器登录失败", error)

    def onRspQryUserInvestor(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        self.investorid = data['InvestorID']
        self.gateway.write_log("投资者代码查询成功")

        sleep(1)    # Wait 1 second due to flow control
        self.reqid += 1
        self.reqQryInstrument({}, self.reqid)

    def onRspOrderInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error["ErrorID"]:
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

        self.gateway.write_error("交易委托失败", error)

    def onRspOrderAction(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error["ErrorID"]:
            return

        self.gateway.write_error("交易撤单失败", error)

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
        # product type using following logic.
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
            # Remove C/P suffix of CZCE option product name
            if contract.exchange == Exchange.CZCE:
                contract.option_portfolio = data["ProductID"][:-1]
            else:
                contract.option_portfolio = data["ProductID"]

            contract.option_underlying = data["UnderlyingInstrID"]
            contract.option_type = OPTIONTYPE_FEMAS2VT.get(data["OptionsType"], None)
            contract.option_strike = data["StrikePrice"]
            contract.option_index = str(data["StrikePrice"])
            contract.option_expiry = datetime.strptime(data["ExpireDate"], "%Y%m%d")

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
        timestamp = f"{data['InsertDate']} {data['InsertTime']}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H:%M:%S")
        dt = CHINA_TZ.localize(dt)

        order = OrderData(
            symbol=data["InstrumentID"],
            exchange=EXCHANGE_FEMAS2VT[data["ExchangeID"]],
            orderid=data["UserOrderLocalID"],
            direction=DIRECTION_FEMAS2VT[data["Direction"]],
            offset=OFFSET_FEMAS2VT[data["OffsetFlag"]],
            price=data["LimitPrice"],
            volume=data["Volume"],
            traded=data["VolumeTraded"],
            status=STATUS_FEMAS2VT[data["OrderStatus"]],
            datettime=dt,
            gateway_name=self.gateway_name,
        )

        self.localid = max(self.localid, int(order.orderid))
        self.gateway.on_order(order)

    def onRtnTrade(self, data: dict):
        """
        Callback of trade status update.
        """
        # Filter duplicate trade data push
        tradeid = data["TradeID"]
        if tradeid in self.tradeids:
            return
        self.tradeids.add(tradeid)

        timestamp = f"{data['TradeDate']} {data['TradeTime']}"
        dt = datetime.strptime(timestamp, "%Y%m%d %H:%M:%S")
        dt = CHINA_TZ.localize(dt)

        trade = TradeData(
            symbol=data["InstrumentID"],
            exchange=EXCHANGE_FEMAS2VT[data["ExchangeID"]],
            orderid=data["UserOrderLocalID"],
            tradeid=tradeid,
            direction=DIRECTION_FEMAS2VT[data["Direction"]],
            offset=OFFSET_FEMAS2VT[data["OffsetFlag"]],
            price=data["TradePrice"],
            volume=data["TradeVolume"],
            datetime=dt,
            gateway_name=self.gateway_name,
        )

        self.gateway.on_trade(trade)

    def connect(
        self,
        address: str,
        userid: str,
        password: str,
        brokerid: int,
        auth_code: str,
        appid: str,
        product_info: str
    ):
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.brokerid = brokerid
        self.address = address
        self.auth_code = auth_code
        self.appid = appid
        self.product_info = product_info

        if not self.connect_status:
            path = get_folder_path(self.gateway_name.lower())
            self.createFtdcTraderApi(str(path) + "\\Td")

            self.subscribePrivateTopic(0)
            self.subscribePublicTopic(0)
            self.subscribeUserTopic(0)

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
            "AppID": self.appid,
            "AuthCode": self.auth_code,
            "EncryptType": "1",
        }

        if self.product_info:
            req["UserProductInfo"] = self.product_info

        self.reqid += 1
        self.reqDSUserCertification(req, self.reqid)

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

    def query_investor(self):
        """"""
        self.reqid += 1

        req = {
            "BrokerID": self.brokerid,
            "UserID": self.userid,
        }

        self.reqQryUserInvestor(req, self.reqid)

    def send_order(self, req: OrderRequest):
        """
        Send new order.
        """
        if req.offset not in OFFSET_VT2FEMAS:
            self.gateway.write_log("请选择开平方向")
            return ""

        self.localid += 1
        orderid = str(self.localid).rjust(12, "0")

        femas_req = {
            "InstrumentID": req.symbol,
            "ExchangeID": str(req.exchange).split(".")[1],
            "BrokerID": self.brokerid,
            "InvestorID": self.investorid,
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
            "InvestorID": self.investorid,
            "UserID": self.userid,
        }

        self.reqid += 1
        self.reqOrderAction(femas_req, self.reqid)

    def query_account(self):
        """
        Query account balance data.
        """
        if not self.investorid:
            return

        req = {
            "BrokerID": self.brokerid,
            "InvestorID": self.investorid,
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
            "InvestorID": self.investorid,
            "UserID": self.userid,
        }

        self.reqid += 1
        self.reqQryInvestorPosition(req, self.reqid)

    def close(self):
        """"""
        if self.connect_status:
            self.exit()
