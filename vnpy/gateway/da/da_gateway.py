"""
"""

from datetime import datetime
from copy import copy
from collections import defaultdict
from typing import List
from csv import DictReader
from io import StringIO

import wmi
import pytz
import requests

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
    HistoryRequest,
    BarData,
    SubscribeRequest,
)


STATUS_DA2VT = {
    "1": Status.SUBMITTING,
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
    "CME": Exchange.CME,
    "CME_CBT": Exchange.CBOT,
    "LME": Exchange.LME,
    "SGXQ": Exchange.SGX,
    "HKEX": Exchange.HKFE,
    "APEX": Exchange.APEX,
    "CFFEX": Exchange.CFFEX,
    "SHFE": Exchange.SHFE,
    "DCE": Exchange.DCE,
    "CZCE": Exchange.CZCE
}
EXCHANGE_VT2DA = {v: k for k, v in EXCHANGE_DA2VT.items()}

PRODUCT_DA2VT = {
    "F": Product.FUTURES,
    "O": Product.OPTION,
}

OPTIONTYPE_DA2VT = {
    "R": OptionType.CALL,
    "F": OptionType.PUT
}

CHINA_TZ = pytz.timezone("Asia/Shanghai")

symbol_name_map = {}
symbol_currency_map = {}
currency_account_map = {}
account_currency_map = {}


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

    def query_history(self, req: HistoryRequest) -> List[BarData]:
        """"""
        print(req)
        path = "http://222.73.120.40:8609/api/HistoryQuote"

        params = {
            "type": "M1",
            "exchangeNo": EXCHANGE_VT2DA[req.exchange],
            "symbol": req.symbol,
            "startTime": req.start.strftime("%Y-%m-%d"),
            "count": ""
        }

        if req.end:
            params["endTime"] = req.end.strftime("%Y-%m-%d")

        headers = {"Accept-Encoding": "gzip"}

        r = requests.get(path, headers=headers, params=params)

        bars = []
        reader = DictReader(StringIO(r.json()))
        for d in reader:
            dt = datetime.strptime(d["时间"], "%Y-%m-%d %H:%M")
            dt = CHINA_TZ.localize(dt)

            bar = BarData(
                symbol=req.symbol,
                exchange=req.exchange,
                interval=req.interval,
                datetime=dt,
                open_price=float(d["开盘价"]),
                high_price=float(d["最高价"]),
                low_price=float(d["最低价"]),
                close_price=float(d["收盘价"]),
                volume=int(d["成交量"]),
                gateway_name=self.gateway_name
            )
            bars.append(bar)

        return bars

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
        symbol = data["TreatyCode"]
        exchange = EXCHANGE_DA2VT.get(data["ExchangeCode"], None)
        if not exchange:
            return

        dt = datetime.strptime(data['Time'], "%Y-%m-%d %H:%M:%S")
        dt = CHINA_TZ.localize(dt)

        tick = TickData(
            symbol=symbol,
            exchange=exchange,
            datetime=dt,
            volume=to_int(data["FilledNum"]),
            open_interest=to_int(data["HoldNum"]),
            limit_up=to_float(data["LimitUpPrice"]),
            limit_down=to_float(data["LimitDownPrice"]),
            last_price=to_float(data["CurrPrice"]),
            open_price=to_float(data["Open"]),
            high_price=to_float(data["High"]),
            low_price=to_float(data["Low"]),
            pre_close=to_float(data["PreSettlementPrice"]),
            bid_price_1=to_float(data["BuyPrice"]),
            bid_price_2=to_float(data["BuyPrice2"]),
            bid_price_3=to_float(data["BuyPrice3"]),
            bid_price_4=to_float(data["BuyPrice4"]),
            bid_price_5=to_float(data["BuyPrice5"]),
            ask_price_1=to_float(data["SalePrice"]),
            ask_price_2=to_float(data["SalePrice2"]),
            ask_price_3=to_float(data["SalePrice3"]),
            ask_price_4=to_float(data["SalePrice4"]),
            ask_price_5=to_float(data["SalePrice5"]),
            bid_volume_1=to_int(data["BuyNumber"]),
            bid_volume_2=to_int(data["BuyNumber2"]),
            bid_volume_3=to_int(data["BuyNumber3"]),
            bid_volume_4=to_int(data["BuyNumber4"]),
            bid_volume_5=to_int(data["BuyNumber5"]),
            ask_volume_1=to_int(data["SaleNumber"]),
            ask_volume_2=to_int(data["SaleNumber2"]),
            ask_volume_3=to_int(data["SaleNumber3"]),
            ask_volume_4=to_int(data["SaleNumber4"]),
            ask_volume_5=to_int(data["SaleNumber5"]),
            gateway_name=self.gateway_name
        )
        tick.name = symbol_name_map[tick.vt_symbol]
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
            self.createMarketApi(False, "market_log.txt")

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
            self.reqMarketData(da_req, self.reqid)

        self.subscribed[req.symbol] = req

    def close(self):
        """
        Close the connection.
        """
        pass


class DaFutureApi(FutureApi):
    """"""

    def __init__(self, gateway):
        """Constructor"""
        super().__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.reqid = 0
        self.local_no = int(datetime.now().strftime("%Y%m%d") + "000000")

        self.connect_status = False
        self.login_status = False
        self.auth_staus = False
        self.login_failed = False

        self.userid = ""
        self.password = ""
        self.auth_code = ""
        self.mac_address = get_mac_address()

        self.exchange_page = defaultdict(int)

        self.orders = {}
        self.order_info = {}

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

            # self.reqid += 1
            # self.reqQryExchange({}, self.reqid)

            # 查询账户信息
            self.query_account()
            self.query_position()
            self.query_order()
            self.query_trade()
        else:
            self.login_failed = True
            self.gateway.write_error("交易服务器登录失败", error)

    def onRspNeedVerify(self, firstLogin: bool, hasSetQA: bool):
        """"""
        print("on rsp need verify", firstLogin, hasSetQA)

    def onRspOrderInsert(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        if not data["OrderNo"]:
            return

        errorid = error["ErrorID"]
        orderid = data["LocalNo"]
        order = self.orders[orderid]

        if errorid:
            order.status = Status.REJECTED
            self.gateway.write_error("交易委托失败", error)
        else:
            timestamp = f"{data['OrderDate']} {data['OrderTime']}"
            dt = datetime.strptime(timestamp, "%Y-%m-%d %H:%M:%S")
            order.datetime = CHINA_TZ.localize(dt)

            self.order_info[order.orderid] = (data["OrderNo"], data["SystemNo"])

        self.gateway.on_order(copy(order))

    def onRspOrderCancel(self, data: dict, error: dict, reqid: int, last: bool):
        """"""
        errorid = error["ErrorID"]
        if errorid:
            self.gateway.write_error("交易撤单失败", error)

    def onRspSettlementInfoConfirm(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of settlment info confimation.
        """
        self.gateway.write_log("结算信息确认成功")

        self.reqid += 1
        self.reqQryInstrument({}, self.reqid)

    def onRspQryInstrument(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of instrument query.
        """
        if error["ErrorID"]:
            return

        product = PRODUCT_DA2VT.get(data["CommodityType"], None)

        if product:
            contract = ContractData(
                symbol=data["CommodityCode"],
                exchange=EXCHANGE_DA2VT[data["ExchangeNo"]],
                name=data["ContractFName"],
                product=product,
                size=data["ProductDot"] / data["UpperTick"],
                pricetick=data["UpperTick"],
                history_data=True,
                gateway_name=self.gateway_name
            )

            if product == Product.OPTION:
                contract.option_type = OPTIONTYPE_DA2VT[data["OptionType"]]
                contract.option_strike = to_float(data["OptionStrikePrice"])
                contract.option_expiry = datetime.strptime(data["LastTradeDay"], "%Y%m%d")

            symbol_name_map[contract.vt_symbol] = contract.name
            symbol_currency_map[contract.symbol] = data["CommodityFCurrencyNo"]

            self.gateway.on_contract(contract)

        if last:
            current_page = self.exchange_page[contract.exchange] + 1
            self.gateway.write_log(f"{contract.exchange.value}第{current_page}页合约信息查询成功")

            self.exchange_page[contract.exchange] += 1
            self.query_contract(contract.exchange, self.exchange_page[contract.exchange])

    def onRspQryExchange(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of order query.
        """
        print(data)

    def onRspQryOrder(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of order query.
        """
        if data["TreatyCode"]:
            timestamp = f"{data['OrderDate']} {data['OrderTime']}"
            dt = datetime.strptime(timestamp, "%Y-%m-%d %H:%M:%S")
            dt = CHINA_TZ.localize(dt)

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
                datetime=dt,
                gateway_name=self.gateway_name
            )

            self.local_no = max(self.local_no, int(data["LocalNo"]))
            self.orders[order.orderid] = order
            self.order_info[order.orderid] = (data["OrderNo"], data["SystemNo"])

            self.gateway.on_order(copy(order))

        if last:
            self.gateway.write_log("委托信息查询成功")

    def onRspQryTrade(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of trade query.
        """
        if data["TreatyCode"]:
            self.update_trade(data)

        if last:
            self.gateway.write_log("成交信息查询成功")

    def update_trade(self, data: dict):
        """"""
        timestamp = f"{data['FilledDate']} {data['FilledTime']}"
        dt = datetime.strptime(timestamp, "%Y-%m-%d %H:%M:%S")
        dt = CHINA_TZ.localize(dt)

        trade = TradeData(
            symbol=data["TreatyCode"],
            exchange=EXCHANGE_DA2VT[data["ExchangeCode"]],
            orderid=data["LocalNo"],
            tradeid=data["FilledNo"],
            direction=DIRECTION_DA2VT[data["BuySale"]],
            offset=OFFSET_DA2VT[data["AddReduce"]],
            price=float(data["FilledPrice"]),
            volume=int(data["FilledNumber"]),
            datetime=dt,
            gateway_name=self.gateway_name
        )
        self.gateway.on_trade(trade)

    def onRspQryCapital(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of trade query.
        """
        account = AccountData(
            accountid=data["CurrencyNo"],
            balance=float(data["TodayBalance"]),
            frozen=float(data["FreezenMoney"]),
            gateway_name=self.gateway_name
        )

        currency_account_map[data["CurrencyNo"]] = data["AccountNo"]
        account_currency_map[data["AccountNo"]] = data["CurrencyNo"]
        self.gateway.on_account(account)

        if last:
            self.gateway.write_log("资金信息查询成功")

    def onRspQryTotalPosition(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of position query.
        """
        if data["TreatyCode"]:
            long_position = PositionData(
                symbol=data["TreatyCode"],
                exchange=EXCHANGE_DA2VT[data["ExchangeNo"]],
                direction=Direction.LONG,
                volume=data["BuyHoldNumber"],
                price=data["BuyHoldOpenPrice"],
                gateway_name=self.gateway_name
            )
            self.gateway.on_position(long_position)

            short_position = PositionData(
                symbol=data["TreatyCode"],
                exchange=EXCHANGE_DA2VT[data["ExchangeNo"]],
                direction=Direction.SHORT,
                volume=data["SaleHoldNumber"],
                price=data["SaleHoldOpenPrice"],
                gateway_name=self.gateway_name
            )
            self.gateway.on_position(short_position)

        if last:
            self.gateway.write_log("持仓信息查询成功")

    def onRtnOrder(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of order status update.
        """
        orderid = data["LocalOrderNo"]
        self.local_no = max(self.local_no, int(orderid))

        order = self.orders.get(orderid, None)
        if not order:
            return

        order.traded = data["FilledNumber"]

        if data["IsCanceled"] == "1":
            order.status = Status.CANCELLED
        elif order.traded == order.volume:
            order.status = Status.ALLTRADED
        elif order.traded > 0:
            order.status = Status.PARTTRADED
        else:
            order.status = Status.NOTTRADED

        self.gateway.on_order(copy(order))

    def onRtnTrade(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of trade status update.
        """
        self.update_trade(data)

    def onRtnCapital(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of capital status update.
        """
        currency = account_currency_map[data["AccountNo"]]

        account = AccountData(
            accountid=currency,
            balance=data["TodayTotal"],
            frozen=data["FrozenDeposit"],
            gateway_name=self.gateway_name
        )

        self.gateway.on_account(account)

    def onRtnPosition(self, data: dict, error: dict, reqid: int, last: bool):
        """
        Callback of position status update.
        """
        long_position = PositionData(
            symbol=data["TreatyCode"],
            exchange=EXCHANGE_DA2VT[data["ExchangeNo"]],
            direction=Direction.LONG,
            volume=data["BuyHoldNumber"],
            price=data["BuyHoldOpenPrice"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(long_position)

        short_position = PositionData(
            symbol=data["TreatyCode"],
            exchange=EXCHANGE_DA2VT[data["ExchangeNo"]],
            direction=Direction.SHORT,
            volume=data["SaleHoldNumber"],
            price=data["SaleHoldOpenPrice"],
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(short_position)

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
            self.createFutureApi(False, "future_log.txt")

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
        self.reqUserLogin(req, self.reqid)

    def send_order(self, req: OrderRequest):
        """
        Send new order.
        """
        self.local_no += 1

        currency = symbol_currency_map[req.symbol]
        account_no = currency_account_map[currency]

        da_req = {
            "UserId": self.userid,
            "AccountNo": account_no,
            "LocalNo": str(self.local_no),
            "TradePwd": self.password,
            "ExchangeCode": EXCHANGE_VT2DA[req.exchange],
            "TreatyCode": req.symbol,
            "BuySale": DIRECTION_VT2DA[req.direction],
            "OrderPrice": str(req.price),
            "OrderNumber": str(int(req.volume)),
            "PriceType": ORDERTYPE_VT2DA[req.type],
            "ValidDate": "1"
        }

        self.reqid += 1
        self.reqOrderInsert(da_req, self.reqid)

        order = req.create_order_data(str(self.local_no), self.gateway_name)

        self.orders[order.orderid] = order
        self.gateway.on_order(order)

        return order.vt_orderid

    def cancel_order(self, req: CancelRequest):
        """
        Cancel existing order.
        """
        order = self.orders[req.orderid]

        # Reject cancel if order info not received from server
        if order.orderid not in self.orders_info:
            msg = f"撤单失败，尚未收到服务端返回的委托信息{order.orderid}"
            self.gateway.write_log(msg)
            return
        
        currency = symbol_currency_map[req.symbol]
        account_no = currency_account_map[currency]
        order_no, system_no = self.order_info[order.orderid]

        da_req = {
            "UserId": self.userid,
            "LocalNo": req.orderid,
            "AccountNo": account_no,
            "TradePwd": self.password,
            "ExchangeCode": EXCHANGE_VT2DA[req.exchange],
            "TreatyCode": req.symbol,
            "BuySale": DIRECTION_VT2DA[order.direction],
            "OrderNo": order_no,
            "SystemNo": system_no
        }

        self.reqid += 1
        self.reqOrderCancel(da_req, self.reqid)

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
        da_req = {"UserId": self.userid}

        self.reqid += 1
        self.reqQryTrade(da_req, self.reqid)

    def query_position(self):
        """
        Query position holding data.
        """
        da_req = {"AccountNo": self.userid}

        self.reqid += 1
        self.reqQryTotalPosition(da_req, self.reqid)

    def query_contract(self, exchange, page=0):
        """
        Query contract data.
        """
        da_exchange = EXCHANGE_VT2DA[exchange]

        req = {
            "PageIndex": page * 1000,
            "ExchangeNo": da_exchange
        }

        self.reqid += 1
        self.reqQryInstrument(req, self.reqid)

    def close(self):
        """"""
        pass


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


def to_int(data: str) -> int:
    """"""
    if not data:
        return 0
    else:
        return int(data)


def to_float(data: str) -> float:
    """"""
    if not data:
        return 0.0
    else:
        return float(data)
