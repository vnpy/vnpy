# encoding: UTF-8
"""
"""

from copy import copy
from datetime import datetime

from vnpy.api.ctp import *
from vnpy.trader.constant import (
    Direction,
    Offset,
    Exchange,
    PriceType,
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
from vnpy.trader.utility import get_temp_path
from vnpy.trader.event import EVENT_TIMER


STATUS_CTP2VT = {
    THOST_FTDC_OAS_Submitted: Status.SUBMITTING,
    THOST_FTDC_OAS_Accepted: Status.SUBMITTING,
    THOST_FTDC_OAS_Rejected: Status.REJECTED,
    THOST_FTDC_OST_NoTradeQueueing: Status.NOTTRADED,
    THOST_FTDC_OST_PartTradedQueueing: Status.PARTTRADED,
    THOST_FTDC_OST_AllTraded: Status.ALLTRADED,
    THOST_FTDC_OST_Canceled: Status.CANCELLED
}

DIRECTION_VT2CTP = {
    Direction.LONG: THOST_FTDC_D_Buy, 
    Direction.SHORT: THOST_FTDC_D_Sell
}
DIRECTION_CTP2VT = {v: k for k, v in DIRECTION_VT2CTP.items()}
DIRECTION_CTP2VT[THOST_FTDC_PD_Long] = Direction.LONG
DIRECTION_CTP2VT[THOST_FTDC_PD_Short] = Direction.SHORT

PRICETYPE_VT2CTP = {
    PriceType.LIMIT: THOST_FTDC_OPT_LimitPrice, 
    PriceType.MARKET: THOST_FTDC_OPT_AnyPrice
}

OFFSET_VT2CTP = {
    Offset.OPEN: THOST_FTDC_OF_Open, 
    Offset.CLOSE: THOST_FTDC_OFEN_Close,
    Offset.CLOSETODAY: THOST_FTDC_OFEN_CloseYesterday,
    Offset.CLOSEYESTERDAY: THOST_FTDC_OFEN_CloseToday,
}
OFFSET_CTP2VT = {v: k for k, v in OFFSET_VT2CTP.items()}

EXCHANGE_CTP2VT = {
    "CFFEX": Exchange.CFFEX,
    "SHFE": Exchange.SHFE,
    "CZCE": Exchange.CZCE,
    "DCE": Exchange.DCE,
    "INE": Exchange.INE
}

PRODUCT_CTP2VT = {
    THOST_FTDC_PC_Futures: Product.FUTURES,
    THOST_FTDC_PC_Options: Product.OPTION
}

OPTIONTYPE_CTP2VT = {
    THOST_FTDC_CP_CallOptions: OptionType.CALL,
    THOST_FTDC_CP_PutOptions: OptionType.PUT
}


symbol_exchange_map = {}
symbol_name_map = {}
symbol_size_map = {}

class CtpGateway(BaseGateway):
    """
    VN Trader Gateway for CTP .
    """

    default_setting = {
        "userid": "",
        "password": "",
        "brokerid": "",
        "td_address": "",
        "md_address": "",
        "auth_code": "",
        "product_info": ""
    }

    def __init__(self, event_engine):
        """Constructor"""
        super(CtpGateway, self).__init__(event_engine, "CTP")

        self.td_api = CtpTdApi(self)
        self.md_api = CtpMdApi(self)

    def connect(self, setting: dict):
        """"""
        userid = setting["userid"]
        password = setting["password"]
        brokerid = setting["brokerid"]
        td_address = setting["td_address"]
        md_address = setting["md_address"]
        auth_code = setting["auth_code"]
        product_info = setting["product_info"]
        
        if not td_address.startswith("tcp://"):
            td_address = "tcp://" + td_address
        if not md_address.startswith("tcp://"):
            md_address = "tcp://" + md_address
        
        self.td_api.connect(td_address, userid, password, brokerid, auth_code, product_info)
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


class CtpMdApi(MdApi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super(CtpMdApi, self).__init__()
        
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
        self.gateway.write_log(f"行情连接断开，原因{reason}")
    
    def onHeartBeatWarning(self, n: int):
        """"""
        pass
    
    def onRspUserLogin(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback when user is logged in.
        """
        if not error["ErrorID"]:
            self.login_status = True
            self.gateway.write_log("行情服务器登录成功")
            
            for symbol in self.subscribed:
                self.subscribeMarketData(symbol)
        else:
            self.gateway.write_error("行情登录失败", error)
    
    def onRspUserLogout(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
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
    
    def onRspUnSubMarketData(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspSubForQuoteRsp(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspUnSubForQuoteRsp(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRtnDepthMarketData(self, data: dict):
        """
        Callback of tick data update.
        """
        symbol = data["InstrumentID"]
        exchange = symbol_exchange_map.get(symbol, "")
        if not exchange:
            return
        
        timestamp = f"{data['ActionDay']} {data['UpdateTime']}.{int(data['UpdateMillisec']/100)}"
        
        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=datetime.strptime(timestamp, "%Y%m%d %H:%M:%S.%f"),
            name = symbol_name_map[symbol],
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
            gateway_name=self.gateway_name
        )
        self.gateway.on_tick(tick)
    
    def onRtnForQuoteRsp(self, data: dict):    
        """"""
        pass        

    def connect(self, address: str, userid: str, password: str, brokerid: int):
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.brokerid = brokerid
        
        # If not connected, then start connection first.
        if not self.connect_status:
            path = get_temp_path(f"{self.gateway_name}_md_" )
            self.createFtdcMdApi(str(path))
            
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
            "BrokerID": self.brokerid
        }
        
        self.reqid += 1
        self.reqUserLogin(req, self.reqid)
        
    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data update.
        """
        if self.login_status:
            self.subscribeMarketData(req.symbol)
        self.subscribed.add(req.symbol)
    
    def close(self):
        """
        Close the connection.
        """
        if self.connect_status:
            self.exit()





class CtpTdApi(TdApi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super(CtpTdApi, self).__init__()
        
        self.gateway = gateway
        self.gateway_name = gateway.gateway_name
        
        self.reqid = 0
        self.order_ref = 0
        
        self.connect_status = False
        self.login_status = False
        self.auth_staus = False
        self.login_failed = False
        
        self.userid = ""
        self.password = ""
        self.brokerid = 0
        self.auth_code = ""
        self.product_info = ""
        
        self.frontid = 0
        self.sessionid = 0
        
        self.order_data = []
        self.trade_data = []
        self.positions = {}
        self.sysid_orderid_map = {}
        
    def onFrontConnected(self):
        """"""
        self.connect_status = True
        self.gateway.write_log("交易连接成功")
        
        if self.auth_code:
            self.authenticate()
        else:
            self.login()
    
    def onFrontDisconnected(self, reason: int):
        """"""
        self.connect_status = False
        self.login_status = False
        self.gateway.write_log(f"交易连接断开，原因{reason}")        
    
    def onHeartBeatWarning(self, n: int):
        """"""
        pass
    
    def onRspAuthenticate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error['ErrorID']:
            self.authStatus = True
            self.writeLog("交易授权验证成功")
            self.login()
        else:
            self.gateway.write_error("交易授权验证失败", error)
    
    def onRspUserLogin(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not error["ErrorID"]:
            self.frontid = data["FrontID"]
            self.sessionid = data["SessionID"]
            self.login_status = True
            self.gateway.write_log("交易登录成功")
            
            # Confirm settelment
            req = {
                "BrokerID": self.brokerid,
                "InvestorID": self.userid
            }
            self.reqid += 1
            self.reqSettlementInfoConfirm(req, self.reqid)
        else:
            self.login_failed = True
            
            self.gateway.write_error("交易登录失败", error)
    
    def onRspUserLogout(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspUserPasswordUpdate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspTradingAccountPasswordUpdate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspUserAuthMethod(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspGenUserCaptcha(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspGenUserText(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspOrderInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        order_ref = data["OrderRef"]
        orderid = f"{self.frontid}.{self.sessionid}.{order_ref}"
        
        symbol = data["InstrumentID"]
        exchange = symbol_exchange_map[symbol]
        
        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=orderid,
            direction=DIRECTION_CTP2VT[data["Direction"]],
            offset=OFFSET_CTP2VT[data["CombOffsetFlag"]],
            price=data["LimitPrice"],
            volume=data["VolumeTotalOriginal"],
            status=Status.REJECTED,
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)
        
        self.gateway.write_error("交易委托失败", error)
    
    def onRspParkedOrderInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspParkedOrderAction(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
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
        
        self.reqid += 1
        self.reqQryInstrument({}, self.reqid)
            
    def onRspRemoveParkedOrder(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspRemoveParkedOrderAction(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspExecOrderInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspExecOrderAction(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspForQuoteInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQuoteInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQuoteAction(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspBatchOrderAction(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspOptionSelfCloseInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspOptionSelfCloseAction(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspCombActionInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryOrder(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryTrade(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryInvestorPosition(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not data:
            return
        
        # Get buffered position object
        key = f"{data['InstrumentID'], data['PosiDirection']}"
        position = self.positions.get(key, None)
        if not position:
            position = PositionData(
                symbol=data["InstrumentID"],
                exchange=symbol_exchange_map[data["InstrumentID"]],
                direction=DIRECTION_CTP2VT[data["PosiDirection"]],
                gateway_name=self.gateway_name
            )
            self.positions[key] = position
        
        # For SHFE position data update
        if position.exchange == Exchange.SHFE:
            if data["YdPosition"] and not data["TodayPosition"]:
                position.yd_volume = data["Position"]
        # For other exchange position data update
        else:
            position.yd_volume = data["Position"] - data["TodayPosition"]
        
        # Calculate previous position cost
        cost = position.price * position.volume
        
        # Update new position volume
        position.volume += data["Position"]
        position.pnl += data["PositionProfit"]
        
        # Calculate average position price
        if position.volume:
            cost += data["PositionCost"]
            position.price = cost / position.volume
        
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
        account = AccountData(
            accountid=data["AccountID"],
            balance=data["Balance"],
            frozen=data["FrozenMargin"]+data["FrozenCash"]+data["FrozenCommission"],
            gateway_name=self.gateway_name
        )
        account.available = data["Available"]
        
        self.gateway.on_account(account)
    
    def onRspQryInvestor(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryTradingCode(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryInstrumentMarginRate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryInstrumentCommissionRate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryExchange(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryProduct(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryInstrument(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of instrument query.
        """
        contract = ContractData(
            symbol=data["InstrumentID"],
            exchange=EXCHANGE_CTP2VT[data["ExchangeID"]],
            name=data["InstrumentName"],
            product=PRODUCT_CTP2VT[data["ProductClass"]],
            size=data["VolumeMultiple"],
            pricetick=data["PriceTick"],
            option_underlying=data["UnderlyingInstrID"],
            option_type=OPTIONTYPE_CTP2VT.get(data["OptionsType"], None),
            option_strike=data["StrikePrice"],
            option_expiry=datetime.strptime(data["ExpireDate"], "%Y%m%d"),
            gateway_name=self.gateway_name
        )
        
        self.gateway.on_contract(contract)
        
        symbol_exchange_map[contract.symbol] = contract.exchange
        symbol_name_map[contract.symbol] = contract.name
        symbol_size_map[contract.symbol] = contract.size
        
        if last:
            self.gateway.write_log("合约信息查询成功")
            
            for data in self.order_data:
                self.onRtnOrder(data)
            self.order_data.clear()
            
            for data in self.trade_data:
                self.onRtnTrade(data)
            self.trade_data.clear()
    
    def onRspQryDepthMarketData(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQrySettlementInfo(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryTransferBank(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryInvestorPositionDetail(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryNotice(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQrySettlementInfoConfirm(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryInvestorPositionCombineDetail(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryCFMMCTradingAccountKey(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryEWarrantOffset(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryInvestorProductGroupMargin(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryExchangeMarginRate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryExchangeMarginRateAdjust(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryExchangeRate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQrySecAgentACIDMap(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryProductExchRate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryProductGroup(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryMMInstrumentCommissionRate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryMMOptionInstrCommRate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryInstrumentOrderCommRate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQrySecAgentTradingAccount(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQrySecAgentCheckMode(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQrySecAgentTradeInfo(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryOptionInstrTradeCost(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryOptionInstrCommRate(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryExecOrder(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryForQuote(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryQuote(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryOptionSelfClose(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryInvestUnit(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryCombInstrumentGuard(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryCombAction(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryTransferSerial(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryAccountregister(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspError(self, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRtnOrder(self, data: dict):
        """
        Callback of order status update.
        """
        symbol = data["InstrumentID"]
        exchange = symbol_exchange_map.get(symbol, "")
        if not exchange:
            self.order_data.append(data)
            return
        
        frontid = data["FrontID"]
        sessionid = data["SessionID"]
        order_ref = data["OrderRef"]
        orderid = f"{frontid}.{sessionid}.{order_ref}"
        
        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=orderid,
            direction=DIRECTION_CTP2VT[data["Direction"]],
            offset=OFFSET_CTP2VT[data["CombOffsetFlag"]],
            price=data["LimitPrice"],
            volume=data["VolumeTotalOriginal"],
            traded=data["VolumeTraded"],
            status=STATUS_CTP2VT[data["OrderStatus"]],
            time=data["InsertTime"],
            gateway_name=self.gateway_name
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
            direction=DIRECTION_CTP2VT[data["Direction"]],
            offset=OFFSET_CTP2VT[data["OffsetFlag"]],
            price=data["Price"],
            volume=data["Volume"],
            time=data["TradeTime"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_trade(trade)        
    
    def onErrRtnOrderInsert(self, data: dict, error: dict):
        """"""
        pass
    
    def onErrRtnOrderAction(self, data: dict, error: dict):
        """"""
        pass
    
    def onRtnInstrumentStatus(self, data: dict):
        """"""
        pass
    
    def onRtnBulletin(self, data: dict):
        """"""
        pass
    
    def onRtnTradingNotice(self, data: dict):
        """"""
        pass
    
    def onRtnErrorConditionalOrder(self, data: dict):
        """"""
        pass
    
    def onRtnExecOrder(self, data: dict):
        """"""
        pass
    
    def onErrRtnExecOrderInsert(self, data: dict, error: dict):
        """"""
        pass
    
    def onErrRtnExecOrderAction(self, data: dict, error: dict):
        """"""
        pass
    
    def onErrRtnForQuoteInsert(self, data: dict, error: dict):
        """"""
        pass
    
    def onRtnQuote(self, data: dict):
        """"""
        pass
    
    def onErrRtnQuoteInsert(self, data: dict, error: dict):
        """"""
        pass
    
    def onErrRtnQuoteAction(self, data: dict, error: dict):
        """"""
        pass
    
    def onRtnForQuoteRsp(self, data: dict):
        """"""
        pass
    
    def onRtnCFMMCTradingAccountToken(self, data: dict):
        """"""
        pass
    
    def onErrRtnBatchOrderAction(self, data: dict, error: dict):
        """"""
        pass
    
    def onRtnOptionSelfClose(self, data: dict):
        """"""
        pass
    
    def onErrRtnOptionSelfCloseInsert(self, data: dict, error: dict):
        """"""
        pass
    
    def onErrRtnOptionSelfCloseAction(self, data: dict, error: dict):
        """"""
        pass
    
    def onRtnCombAction(self, data: dict):
        """"""
        pass
    
    def onErrRtnCombActionInsert(self, data: dict, error: dict):
        """"""
        pass
    
    def onRspQryContractBank(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryParkedOrder(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryParkedOrderAction(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryTradingNotice(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryBrokerTradingParams(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQryBrokerTradingAlgos(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQueryCFMMCTradingAccountToken(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRtnFromBankToFutureByBank(self, data: dict):
        """"""
        pass
    
    def onRtnFromFutureToBankByBank(self, data: dict):
        """"""
        pass
    
    def onRtnRepealFromBankToFutureByBank(self, data: dict):
        """"""
        pass
    
    def onRtnRepealFromFutureToBankByBank(self, data: dict):
        """"""
        pass
    
    def onRtnFromBankToFutureByFuture(self, data: dict):
        """"""
        pass
    
    def onRtnFromFutureToBankByFuture(self, data: dict):
        """"""
        pass
    
    def onRtnRepealFromBankToFutureByFutureManual(self, data: dict):
        """"""
        pass
    
    def onRtnRepealFromFutureToBankByFutureManual(self, data: dict):
        """"""
        pass
    
    def onRtnQueryBankBalanceByFuture(self, data: dict):
        """"""
        pass
    
    def onErrRtnBankToFutureByFuture(self, data: dict, error: dict):
        """"""
        pass
    
    def onErrRtnFutureToBankByFuture(self, data: dict, error: dict):
        """"""
        pass
    
    def onErrRtnRepealBankToFutureByFutureManual(self, data: dict, error: dict):
        """"""
        pass
    
    def onErrRtnRepealFutureToBankByFutureManual(self, data: dict, error: dict):
        """"""
        pass
    
    def onErrRtnQueryBankBalanceByFuture(self, data: dict, error: dict):
        """"""
        pass
    
    def onRtnRepealFromBankToFutureByFuture(self, data: dict):
        """"""
        pass
    
    def onRtnRepealFromFutureToBankByFuture(self, data: dict):
        """"""
        pass
    
    def onRspFromBankToFutureByFuture(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspFromFutureToBankByFuture(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRspQueryBankAccountMoneyByFuture(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        pass
    
    def onRtnOpenAccountByBank(self, data: dict):
        """"""
        pass
    
    def onRtnCancelAccountByBank(self, data: dict):
        """"""
        pass
    
    def onRtnChangeAccountByBank(self, data: dict):
        """"""
        pass
    
    def connect(self, address: str, userid: str, password: str, brokerid: int, auth_code: str, product_info: str):
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.brokerid = brokerid
        self.auth_code = auth_code
        self.product_info = product_info
        
        if not self.connect_status:
            path = get_temp_path(f"{self.gateway_name}_td_")
            self.createFtdcTraderApi(str(path))
            
            self.subscribePrivateTopic(0)
            self.subscribePublicTopic(0)
            
            self.registerFront(address)
            self.init()            
        else:
            self.authenticate()
    
    def authenticate(self):
        """
        Authenticate with auth_code and product_info.
        """
        req = {
            "UserID": self.userid,
            "BrokerID": self.brokerid,
            "AuthCode": self.auth_code,
            "ProductInfo": self.product_info
        }
        
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
        }
        
        self.reqid += 1
        self.reqUserLogin(req, self.reqid)
        
    def send_order(self, req: OrderRequest):
        """
        Send new order.
        """
        self.order_ref += 1
        
        ctp_req = {
            "InstrumentID": req.symbol,
            "LimitPrice": req.price,
            "VolumeTotalOriginal": int(req.volume),
            "OrderPriceType": PRICETYPE_VT2CTP.get(req.price_type, ""),
            "Direction": DIRECTION_VT2CTP.get(req.direction, ""),
            "CombOffsetFlag": OFFSET_VT2CTP.get(req.offset, ""),
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
        
        if req.price_type == PriceType.FAK:
            ctp_req["OrderPriceType"] = THOST_FTDC_OPT_LimitPrice
            ctp_req["TimeCondition"] = THOST_FTDC_TC_IOC
            ctp_req["VolumeCondition"] = THOST_FTDC_VC_AV
        elif req.price_type == PriceType.FOK:
            ctp_req["OrderPriceType"] = THOST_FTDC_OPT_LimitPrice
            ctp_req["TimeCondition"] = THOST_FTDC_TC_IOC
            ctp_req["VolumeCondition"] = THOST_FTDC_VC_CV            
        
        self.reqid += 1
        self.reqOrderInsert(ctp_req, self.reqid)
        
        orderid = f"{self.frontid}.{self.sessionid}.{self.order_ref}"
        order = req.create_order_data(orderid, self.gateway_name)
        self.gateway.on_order(order)
        
        return order.vt_orderid
    
    def cancel_order(self, req: CancelRequest):
        """
        Cancel existing order.
        """
        frontid, sessionid, order_ref = req.orderid.split(".")
        
        ctp_req = {
            "InstrumentID": req.symbol,
            "Exchange": req.exchange,
            "OrderRef": order_ref,
            "FrontID": int(frontid),
            "SessionID": int(sessionid),
            "ActionFlag": THOST_FTDC_AF_Delete,
            "BrokerID": self.brokerid,
            "InvestorID": self.userid
        }
        
        self.reqid += 1
        self.reqOrderAction(ctp_req, self.reqid)
    
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
        
    
    