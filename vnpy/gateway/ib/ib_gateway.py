"""
Please install ibapi from Interactive Brokers github page.
"""
from datetime import datetime
from copy import copy

from ibapi.wrapper import EWrapper
from ibapi.client import EClient

from vnpy.trader.gateway import Gateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    ContractData,
    PositionData,
    AccountData,
    LogData,
    SubscribeRequest,
    OrderRequest,
    CancelRequest
)
from vnpy.trader.constant import (
    PRODUCT_EQUITY,
    PRODUCT_FOREX,
    PRODUCT_SPOT,
    PRODUCT_FUTURES,
    PRODUCT_OPTION,
    PRICETYPE_LIMIT,
    PRICETYPE_MARKET,
    DIRECTION_LONG,
    DIRECTION_SHORT,
    EXCHANGE_SMART,
    EXCHANGE_NYMEX,
    EXCHANGE_GLOBEX,
    EXCHANGE_IDEALPRO,
    EXCHANGE_HKEX,
    EXCHANGE_HKFE,
    EXCHANGE_CME,
    EXCHANGE_ICE,
    CURRENCY_CNY,
    CURRENCY_HKD,
    CURRENCY_USD,
    STATUS_SUBMITTING,
    STATUS_NOTTRADED,
    STATUS_PARTTRADED,
    STATUS_ALLTRADED,
    STATUS_CANCELLED,
    STATUS_REJECTED,
    OPTION_CALL,
    OPTION_PUT
)

PRICETYPE_VT2IB = {PRICETYPE_LIMIT: "LMT", PRICETYPE_MARKET: "MKT"}
PRICETYPE_IB2VT = {v: k for k, v in PRICETYPE_VT2IB.items()}

DIRECTION_VT2IB = {DIRECTION_LONG: "BUY", DIRECTION_SHORT: "SELL"}
DIRECTION_IB2VT = {v: k for k, v in DIRECTION_IB2VT.items()}

EXCHANGE_VT2IB = {
    EXCHANGE_SMART: "SMART",
    EXCHANGE_NYMEX: "NYMEX",
    EXCHANGE_GLOBEX: "GLOBEX",
    EXCHANGE_IDEALPRO: "IDEALPRO",
    EXCHANGE_CME: "CME",
    EXCHANGE_ICE: "ICE",
    EXCHANGE_HKEX: "HKEX",
    EXCHANGE_HKFE: "HKFE"
}
EXCHANGE_IB2VT = {v: k for k, v in EXCHANGE_VT2IB.items()}

STATUS_IB2VT = {
    "Submitted": STATUS_NOTTRADED,
    "Filled": STATUS_ALLTRADED,
    "Cancelled": STATUS_CANCELLED,
    "PendingSubmit": STATUS_SUBMITTING,
    "PreSubmitted": STATUS_NOTTRADED
}

PRODUCT_VT2IB = {
    PRODUCT_EQUITY: "STK",
    PRODUCT_FOREX: "CASH",
    PRODUCT_SPOT: "CMDTY",
    PRODUCT_OPTION: "OPT",
    PRODUCT_FUTURES: "FUT"
}

OPTION_VT2IB = {OPTION_CALL: "CALL", OPTION_PUT: "PUT"}

CURRENCY_VT2IB = {CURRENCY_USD: "USD", CURRENCY_CNY: "CNY", CURRENCY_HKD: "HKD"}

TICKFIELD_IB2VT = {
    0: "bid_volume_1",
    1: "bid_price_1",
    2: "ask_price_1",
    3: "ask_volume_1",
    4: "last_price",
    5: "last_volume",
    6: "high_price",
    7: "low_price",
    8: "volume",
    9: "pre_close",
    14: "open_price"
}

ACCOUNTFIELD_IB2VT = {
    "NetLiquidationByCurrency": "balance",
    "NetLiquidation": "balance",
    "UnrealizedPnL": "positionProfit",
    "AvailableFunds": "available",
    "MaintMarginReq": "margin",
}


class IbGateway(Gateway):
    """"""

    def __init__(self, event_engine):
        """"""
        super(Gateway, self).__init__(event_engine, "IB")

    def connect(self):
        """
        Start gateway connection.
        """
        pass

    def close(self):
        """
        Close gateway connection.
        """
        pass

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe tick data update.
        """
        pass

    def send_order(self, req: OrderRequest):
        """
        Send a new order.
        """
        pass

    def cancel_order(self, req: CancelRequest):
        """
        Cancel an existing order.
        """
        pass

    def query_account(self):
        """
        Query account balance.
        """
        pass

    def query_position(self):
        """
        Query holding positions.
        """
        pass


class IbApi(EWrapper):
    """"""

    def __init__(self, gateway: Gateway):
        """"""
        super(IbApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.status = False
        self.orderid = 0
        self.ticks = {}
        self.orders = {}
        self.accounts = {}
        self.contracts = {}

    def nextValidId(self, orderId: int):
        """
        Callback of next valid orderid.
        """
        super(IbApi, self).nextValidId(orderId)

        self.orderid = orderId

    def currentTime(self, time: int):
        """
        Callback of current server time of IB.
        """
        super(IbApi, self).currentTime(time)

        self.status = True

        dt = datetime.fromtimestamp(time)
        time_string = dt.strftime("%Y-%m-%d %H:%M:%S.%f")
        log = LogData(
            msg=f"IB TWS连接成功，服务器时间: {time_string}",
            gateway_name=self.gateway_name
        )
        self.gateway.on_log(log)

    def error(self, reqId: TickerId, errorCode: int, errorString: str):
        """
        Callback of error caused by specific request.
        """
        super(IbApi, self).error(reqId, errorCode, errorString)
        log = LogData(
            msg=f"发生错误，错误代码：{errorCode}，错误信息: {errorString}",
            gateway_name=self.gateway_name
        )
        self.gateway.on_log(log)

    def tickPrice(
            self,
            reqId: TickerId,
            tickType: TickType,
            price: float,
            attrib: TickAttrib
    ):
        """
        Callback of tick price update.
        """
        super(IbApi, self).tickPrice(reqId, tickType, price, attrib)

        if tickType not in TICKFIELD_IB2VT:
            return

        tick = self.ticks[reqId]
        name = TICKFIELD_IB2VT[tickType]
        setattr(tick, name, price)

        # Forex and spot product of IB has no tick time and last price.
        # We need to calculate locally.
        contract = self.contracts[reqId]
        if contract.product in (PRODUCT_FOREX, PRODUCT_SPOT):
            tick.last_price = (tick.bid_price_1 + tick.ask_price_1) / 2
            tick.datetime = datetime.now()
        self.gateway.on_tick(copy(tick))

    def tickSize(self, reqId: TickerId, tickType: TickType, size: int):
        """
        Callback of tick volume update.
        """
        super(IbApi, self).tickSize(reqId, tickType, size)

        if tickType not in TICKFIELD_IB2VT:
            return

        tick = self.ticks[reqId]
        name = TICKFIELD_IB2VT[tickType]
        setattr(tick, name, size)

        self.gateway.on_tick(copy(tick))

    def tickString(self, reqId: TickerId, tickType: TickType, value: str):
        """
        Callback of tick string update.
        """
        super().tickString(reqId, tickType, value)

        if tickType != "45":
            return

        tick = self.ticks[reqId]
        tick.datetime = datetime.fromtimestamp(value)

        self.gateway.on_tick(copy(tick))
