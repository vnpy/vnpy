"""
"""

from datetime import datetime
from threading import Thread

import wmi

from vnpy.api.da import (
    MarketApi, 
    FutureApi,
    DAF_SUB_Append,
    DAF_TYPE_Future
)
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


STATUS_DA2VT = {
    "1": Status.SUBMITTING,,
    "2": Status.NOTTRADED,
    "3": Status.PARTTRADED,
    "4": Status.ALLTRADED,
    "5": Status.CANCELLED,
    "6": Status.CANCELLED,
    "7": Status.REJECTED,
    "8": Status.SUBMITTING,
    "9": Status.SUBMITTING,
    "A": Status.SUBMITTING,
}

DIRECTION_VT2DA = {
    Direction.LONG: "1",
    Direction.SHORT: "2"
}
DIRECTION_DA2VT = {v: k for k, v in DIRECTION_VT2DA.items()}


ORDERTYPE_VT2DA = {
    OrderType.LIMIT: "1",
    OrderType.MARKET: "2"
}
ORDERTYPE_DA2VT = {v: k for k, v in ORDERTYPE_VT2DA.items()}

OFFSET_VT2DA = {
    Offset.OPEN: "1",
    Offset.CLOSE: "2",
    Offset.CLOSETODAY: "3",
    Offset.CLOSEYESTERDAY: "4",
}
OFFSET_DA2VT = {v: k for k, v in OFFSET_VT2DA.items()}

EXCHANGE_DA2VT = {
    "APEX": Exchange.APEX,
    # "SGXQ": Exchange.SGX,
    # "NYMEX": Exchange.NYMEX,
    # "LME": Exchange.LME,
    # "CME_CBT": Exchange.CBOT,
    # "HKEX": Exchange.HKFE,
    # "CME": Exchange.CME,
    # "TOCOM": Exchange.TOCOM,
    # "KRX": Exchange.KRX,
    # "ICE": Exchange.ICE
}
EXCHANGE_VT2DA = {v: k for k, v in EXCHANGE_DA2VT.items()}

PRODUCT_DA2VT = {
    "F": Product.FUTURES,
    "O": Product.OPTION,
}

# OPTIONTYPE_DA2VT = {
#     THOST_FTDC_CP_CallOptions: OptionType.CALL,
#     THOST_FTDC_CP_PutOptions: OptionType.PUT
# }


symbol_exchange_map = {}
symbol_name_map = {}
symbol_size_map = {}


class DaGateway(BaseGateway):
    """
    VN Trader Gateway for DA .
    """

    default_setting = {
        "用户名": "",
        "密码": "",
        "交易服务器": "",
        "行情服务器": "",
        "授权码": ""
    }

    exchanges = list(EXCHANGE_DA2VT.values())

    def __init__(self, event_engine):
        """Constructor"""
        super().__init__(event_engine, "DA")

        self.future_api = DaFutureApi(self)
        self.market_api = DaMarketApi(self)

    def connect(self, setting: dict):
        """"""
        userid = setting["用户名"]
        password = setting["密码"]
        future_address = setting["交易服务器"]
        market_address = setting["行情服务器"]
        auth_code = setting["授权码"]
        
        if not future_address.startswith("tcp://"):
            future_address = "tcp://" + future_address
        if not market_address.startswith("tcp://"):
            market_address = "tcp://" + market_address

        self.future_api.connect(future_address, userid, password, auth_code)
        self.market_api.connect(market_address, userid, password, auth_code)

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.market_api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """"""
        return self.future_api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """"""
        self.future_api.cancel_order(req)

    def query_account(self):
        """"""
        pass

    def query_position(self):
        """"""
        pass

    def close(self):
        """"""
        self.future_api.close()
        self.market_api.close()

    def write_error(self, msg: str, error: dict):
        """"""
        error_id = error["ErrorID"]
        error_msg = error["ErrorMsg"]
        msg = f"{msg}，代码：{error_id}，信息：{error_msg}"
        self.write_log(msg)


class DaMarketApi(MarketApi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.reqid = 0

        self.connect_status = False
        self.login_status = False
        self.subscribed = {}
        self.mac_address = get_mac_address()

        self.userid = ""
        self.password = ""
        self.auth_code = ""

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

    def onRspUserLogin(self, error: dict, reqid: int, last: bool):
        """
        Callback when user is logged in.
        """
        if not error["ErrorID"]:
            self.login_status = True
            self.gateway.write_log("行情服务器登录成功")

            for req in self.subscribed.values():
                self.subscribe(req)
        else:
            self.gateway.write_error("行情服务器登录失败", error)

    def onRspMarketData(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of tick data update.
        """
        print('on rsp', data, error)
        symbol = data["TreatyCode"]
        exchange = EXCHANGE_DA2VT.get(data["ExchangeCode"], None)
        if not exchange:
            return

        timestamp = f"{data['TradeDay']} {data['Time']}"

        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=datetime.strptime(timestamp, "%Y%m%d %H:%M:%S.%f"),
            name=symbol_name_map[symbol],
            volume=int(data["FilledNum"]),
            open_interest=int(data["HoldNum"]),
            limit_up=float(data["LimitUpPrice"]),
            limit_down=float(data["LimitDownPrice"]),
            last_price=float(data["CurrPrice"]),
            open_price=float(data["Open"]),
            high_price=float(data["High"]),
            low_price=float(data["Low"]),
            pre_close=float(data["PreSettlementPrice"]),
            bid_price_1=float(data["BuyPrice"]),
            bid_price_2=float(data["BuyPrice2"]),
            bid_price_3=float(data["BuyPrice3"]),
            bid_price_4=float(data["BuyPrice4"]),
            bid_price_5=float(data["BuyPrice5"]),
            ask_price_1=float(data["SalePrice"]),
            ask_price_2=float(data["SalePrice2"]),
            ask_price_3=float(data["SalePrice3"]),
            ask_price_4=float(data["SalePrice4"]),
            ask_price_5=float(data["SalePrice5"]),
            bid_volume_1=int(data["BuyNumber"]),
            bid_volume_2=int(data["BuyNumber2"]),
            bid_volume_3=int(data["BuyNumber3"]),
            bid_volume_4=int(data["BuyNumber4"]),
            bid_volume_5=int(data["BuyNumber5"]),
            ask_volume_1=int(data["SaleNumber"]),
            ask_volume_2=int(data["SaleNumber2"]),
            ask_volume_3=int(data["SaleNumber3"]),
            ask_volume_4=int(data["SaleNumber4"]),
            ask_volume_5=int(data["SaleNumber5"]),
            gateway_name=self.gateway_name
        )
        self.gateway.on_tick(tick)

    def connect(self, address: str, userid: str, password: str, auth_code: str):
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.auth_code = auth_code

        # If not connected, then start connection first.
        if not self.connect_status:
            # path = get_folder_path(self.gateway_name.lower())
            self.createMarketApi(True, "market_log.txt")

            self.registerNameServer(address)
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
            "UserId": self.userid,
            "UserPwd": self.password,
            "AuthorCode": self.auth_code,
            "MacAddress": self.mac_address,
            "ComputerName": "Dev Server",
            "SoftwareName": "vn.py",
            "SoftwareVersion": "2.0",
        }

        self.reqid += 1
        self.reqUserLogin(req, self.reqid)

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe to tick data update.
        """
        if self.login_status:
            da_exchange = EXCHANGE_VT2DA.get(req.exchange, "")
            if not da_exchange:
                self.gateway.write_log(f"不支持的交易所{req.exchange.value}")
                return
            
            da_code = f"{da_exchange},{req.symbol}"
            
            da_req = {
                "MarketType": DAF_TYPE_Future,
                "SubscMode": DAF_SUB_Append,
                "MarketCount": 1,
                "MarketTrcode": da_code,
            }
            self.reqid += 1
            i = self.reqMarketData(da_req, self.reqid)
            print(i, da_req)

        self.subscribed[req.symbol] = req

    def close(self):
        """
        Close the connection.
        """
        if self.connect_status:
            self.exit()


class DaFutureApi(FutureApi):
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
        self.auth_staus = False
        self.login_failed = False

        self.userid = ""
        self.password = ""
        self.auth_code = ""
        self.mac_address = get_mac_address()

    def onFrontConnected(self):
        """"""
        self.gateway.write_log("交易服务器连接成功")
        self.login()

    def onFrontDisconnected(self, reason: int):
        """"""
        self.login_status = False
        self.gateway.write_log(f"交易服务器连接断开，原因{reason}")

    def onRspUserLogin(self, error: dict, reqid: int, last: bool):
        """"""
        if not error["ErrorID"]:
            self.login_status = True
            self.gateway.write_log("交易服务器登录成功")

            # 查询可交易合约
            for exchange in EXCHANGE_DA2VT.values():
                self.query_contract(exchange)
        else:
            self.login_failed = True
            self.gateway.write_error("交易服务器登录失败", error)
    
    def onRspNeedVerify(self, firstLogin: bool, hasSetQA: bool):
        """"""
        print("on rsp need verify", firstLogin, hasSetQA)

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
            direction=DIRECTION_DA2VT[data["Direction"]],
            offset=OFFSET_DA2VT.get(data["CombOffsetFlag"], Offset.NONE),
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

        self.reqid += 1
        self.reqQryInstrument({}, self.reqid)

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
                direction=DIRECTION_DA2VT[data["PosiDirection"]],
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

    def onRspQryExchange(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of instrument query.
        """
        print(data)

    def onRspQryInstrument(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of instrument query.
        """
        product = PRODUCT_DA2VT.get(data["CommodityType"], None)
        if product:
            contract = ContractData(
                symbol=data["CommodityCode"],
                exchange=EXCHANGE_DA2VT[data["ExchangeNo"]],
                name=data["ContractFName"],
                product=product,
                size=data["ProductDot"] / data["UpperTick"],
                pricetick=data["UpperTick"],
                gateway_name=self.gateway_name
            )

            self.gateway.on_contract(contract)

        if last:
            self.gateway.write_log("合约信息查询成功")

    def onRspQryOrder(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of order query.
        """
        order = OrderData(
            symbol=data["TreatyCode"],
            exchange=EXCHANGE_DA2VT[data["ExchangeCode"]],
            orderid=data["LocalNo"],
            type=ORDERTYPE_DA2VT[data["PriceType"]],
            direction=DIRECTION_DA2VT[data["BuySale"]],
            offset=OFFSET_DA2VT[data["AddReduce"]],
            price=float(data["OrderPrice"]),
            volume=int(data["OrderNumber"]),
            traded=int(data["FilledNumber"]),
            status=STATUS_DA2VT[data["OrderState"]],
            time=data["OrderTime"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_order(order)

    def onRspQryTrade(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of trade query.
        """
        trade = TradeData(
            symbol=data["TreatyCode"],
            exchange=EXCHANGE_DA2VT[data["ExchangeCode"]],
            orderid=data["LocalNo"],
            tradeid=data["FilledNo"]
            direction=DIRECTION_DA2VT[data["BuySale"]],
            offset=OFFSET_DA2VT[data["AddReduce"]],
            price=float(data["FilledPrice"]),
            volume=int(data["FilledNumber"]),
            time=data["FilledTime"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_trade(trade)

    def onRspQryCapital(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of trade query.
        """
        account = AccountData(
            accountid=data["UserId"],
            balance=float(data["TodayBalance"])
            frozen=float(data["FreezenMoney"]),
            gateway_name=self.gateway_name
        )
        self.gateway.on_account(account)

    def onRspQryPosition(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of trade query.
        """
        position = PositionData(
            symbol=data["ContCode"],
            exchange=EXCHANGE_DA2VT[data["ExchangeNo"]],
            direction=DIRECTION_DA2VT[data["Direct"]],
            volume=data["HoldVol"],
            price=data["HoldPrice"],
            gateway_name=self.gateway_name
        )   
        self.gateway.on_position(position)

    def onRtnOrder(self, data: dict):
        """
        Callback of order status update.
        """
        pass

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
            direction=DIRECTION_DA2VT[data["Direction"]],
            offset=OFFSET_DA2VT[data["OffsetFlag"]],
            price=data["Price"],
            volume=data["Volume"],
            time=data["TradeTime"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_trade(trade)

    def update_trade(self, data: dict):
        """"""
        pass

    def update_account(self, data: dict):
        """"""
        pass

    def update_position(self, data: dict):
        """"""
        pass

    def connect(
        self,
        address: str,
        userid: str,
        password: str,
        auth_code: str
    ):
        """
        Start connection to server.
        """
        self.userid = userid
        self.password = password
        self.auth_code = auth_code
        
        if not self.connect_status:
            #path = get_folder_path(self.gateway_name.lower())
            self.createFutureApi(True, "future_log.txt")

            self.registerNameServer(address)
            self.init()

            self.connect_status = True
        else:
            self.login()

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
        req = {
            "UserId": self.userid,
            "UserPwd": self.password,
            "AuthorCode": self.auth_code,
            "MacAddress": self.mac_address,
            "ComputerName": "Dev Server",
            "SoftwareName": "vn.py",
            "SoftwareVersion": "2.0",
        }

        self.reqid += 1
        n = self.reqUserLogin(req, self.reqid)
        print("login", n)

    def send_order(self, req: OrderRequest):
        """
        Send new order.
        """
        self.order_ref += 1

        da_req = {
            "InstrumentID": req.symbol,
            "ExchangeID": req.exchange.value,
            "LimitPrice": req.price,
            "VolumeTotalOriginal": int(req.volume),
            "OrderPriceType": ORDERTYPE_VT2DA.get(req.type, ""),
            "Direction": DIRECTION_VT2DA.get(req.direction, ""),
            "CombOffsetFlag": OFFSET_VT2DA.get(req.offset, ""),
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
            da_req["OrderPriceType"] = THOST_FTDC_OPT_LimitPrice
            da_req["TimeCondition"] = THOST_FTDC_TC_IOC
            da_req["VolumeCondition"] = THOST_FTDC_VC_AV
        elif req.type == OrderType.FOK:
            da_req["OrderPriceType"] = THOST_FTDC_OPT_LimitPrice
            da_req["TimeCondition"] = THOST_FTDC_TC_IOC
            da_req["VolumeCondition"] = THOST_FTDC_VC_CV

        self.reqid += 1
        self.reqOrderInsert(da_req, self.reqid)

        orderid = f"{self.frontid}_{self.sessionid}_{self.order_ref}"
        order = req.create_order_data(orderid, self.gateway_name)
        self.gateway.on_order(order)

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """
        Cancel existing order.
        """
        frontid, sessionid, order_ref = req.orderid.split("_")

        da_req = {
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
        self.reqOrderAction(da_req, self.reqid)

    def query_account(self):
        """
        Query account balance data.
        """
        self.reqid += 1
        self.reqQryCapital({}, self.reqid)
    
    def query_order(self):
        """
        Query account balance data.
        """
        self.reqid += 1
        self.reqQryOrder({}, self.reqid)

    def query_trade(self):
        """
        Query account balance data.
        """
        self.reqid += 1
        self.reqQryTrade({}, self.reqid)

    def query_position(self):
        """
        Query position holding data.
        """
        self.reqid += 1
        self.reqQryPosition({}, self.reqid)
    
    def query_contract(self, exchange, page=1):
        """
        Query contract data.
        """
        da_exchange = EXCHANGE_VT2DA[exchange]

        req = {
            "PageIndex": page,
            "ExchangeNo": da_exchange
        }

        self.reqid += 1
        self.reqQryInstrument(req, self.reqid)

    def close(self):
        """"""
        if self.connect_status:
            self.exit()


def get_network_interface():
    """"""
    c = wmi.WMI()
    interfaces = c.Win32_NetworkAdapterConfiguration(IPEnabled=1)
    if not interfaces:
        return None

    # Use interface with default ip gateway
    for interface in interfaces:
        if interface.DefaultIPGateway:
            return interface

    # Otherwise use last one
    return interface


def get_mac_address():
    """"""
    interface = get_network_interface()
    if not interface:
        return ""

    return interface.MACAddress