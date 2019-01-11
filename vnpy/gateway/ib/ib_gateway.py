"""
Please install ibapi from Interactive Brokers github page.
"""
from datetime import datetime
from copy import copy
from threading import Thread
from queue import Empty

from ibapi.wrapper import EWrapper
from ibapi.client import EClient
from ibapi.contract import Contract, ContractDetails
from ibapi.order import Order
from ibapi.common import TickerId, OrderId, TickAttrib, MAX_MSG_LEN
from ibapi.ticktype import TickType
from ibapi.order_state import OrderState
from ibapi.execution import Execution
from ibapi.utils import BadMessage
from ibapi import comm

from vnpy.trader.gateway import BaseGateway
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
    DIRECTION_NET,
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
DIRECTION_IB2VT = {v: k for k, v in DIRECTION_VT2IB.items()}
DIRECTION_IB2VT["BOT"] = DIRECTION_LONG
DIRECTION_IB2VT["SLD"] = DIRECTION_SHORT

EXCHANGE_VT2IB = {
    EXCHANGE_SMART: "SMART",
    EXCHANGE_NYMEX: "NYMEX",
    EXCHANGE_GLOBEX: "GLOBEX",
    EXCHANGE_IDEALPRO: "IDEALPRO",
    EXCHANGE_CME: "CME",
    EXCHANGE_ICE: "ICE",
    EXCHANGE_HKEX: "SEHK",
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
PRODUCT_IB2VT = {v: k for k, v in PRODUCT_VT2IB.items()}

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


class IbGateway(BaseGateway):
    """"""

    default_setting = {"host": "127.0.0.1", "port": 7497, "clientid": 1}

    def __init__(self, event_engine):
        """"""
        super(IbGateway, self).__init__(event_engine, "IB")

        self.api = IbApi(self)

    def connect(self, setting: dict):
        """
        Start gateway connection.
        """
        self.api.connect(setting)

    def close(self):
        """
        Close gateway connection.
        """
        self.api.close()

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe tick data update.
        """
        self.api.subscribe(req)

    def send_order(self, req: OrderRequest):
        """
        Send a new order.
        """
        return self.api.send_order(req)

    def cancel_order(self, req: CancelRequest):
        """
        Cancel an existing order.
        """
        self.api.cancel_order(req)

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

    def __init__(self, gateway: BaseGateway):
        """"""
        super(IbApi, self).__init__()

        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.status = False

        self.reqid = 0
        self.orderid = 0
        self.clientid = 0
        self.ticks = {}
        self.orders = {}
        self.accounts = {}

        self.tick_exchange = {}

        self.client = IbClient(self)
        self.thread = Thread(target=self.client.run)

    def connectAck(self):
        """
        Callback when connection is established.
        """
        self.status = True

        log = LogData(msg="IB TWS连接成功", gateway_name=self.gateway_name)
        self.gateway.on_log(log)

    def connectionClosed(self):
        """
        Callback when connection is closed.
        """
        self.status = False

        log = LogData(msg="IB TWS连接断开", gateway_name=self.gateway_name)
        self.gateway.on_log(log)

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

        dt = datetime.fromtimestamp(time)
        time_string = dt.strftime("%Y-%m-%d %H:%M:%S.%f")
        log = LogData(
            msg=f"服务器时间: {time_string}",
            gateway_name=self.gateway_name
        )
        self.gateway.on_log(log)

    def error(self, reqId: TickerId, errorCode: int, errorString: str):
        """
        Callback of error caused by specific request.
        """
        super(IbApi, self).error(reqId, errorCode, errorString)
        log = LogData(
            msg=f"信息通知，代码：{errorCode}，内容: {errorString}",
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

        # Forex and spot product of IDEALPRO has no tick time and last price.
        # We need to calculate locally.
        exchange = self.tick_exchange[reqId]
        if exchange == EXCHANGE_IDEALPRO:
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
        super(IbApi, self).tickString(reqId, tickType, value)

        if tickType != "45":
            return

        tick = self.ticks[reqId]
        tick.datetime = datetime.fromtimestamp(value)

        self.gateway.on_tick(copy(tick))

    def orderStatus(
            self,
            orderId: OrderId,
            status: str,
            filled: float,
            remaining: float,
            avgFillPrice: float,
            permId: int,
            parentId: int,
            lastFillPrice: float,
            clientId: int,
            whyHeld: str,
            mktCapPrice: float
    ):
        """
        Callback of order status update.
        """
        super(IbApi,
              self).orderStatus(
                  orderId,
                  status,
                  filled,
                  remaining,
                  avgFillPrice,
                  permId,
                  parentId,
                  lastFillPrice,
                  clientId,
                  whyHeld,
                  mktCapPrice
              )

        orderid = str(orderId)
        order = self.orders.get(orderid, None)
        order.status = STATUS_IB2VT[status]
        order.traded = filled

        self.gateway.on_order(copy(order))

    def openOrder(
            self,
            orderId: OrderId,
            ib_contract: Contract,
            ib_order: Order,
            orderState: OrderState
    ):
        """
        Callback when opening new order.
        """
        super(IbApi, self).openOrder(orderId, ib_contract, ib_order, orderState)

        orderid = str(orderId)
        order = OrderData(
            symbol=ib_contract.conId,
            exchange=EXCHANGE_IB2VT.get(
                ib_contract.exchange,
                ib_contract.exchange
            ),
            orderid=orderid,
            direction=DIRECTION_IB2VT[ib_order.action],
            price=ib_order.lmtPrice,
            volume=ib_order.totalQuantity,
            gateway_name=self.gateway_name
        )

        self.orders[orderid] = order
        self.gateway.on_order(copy(order))

    def updateAccountValue(
            self,
            key: str,
            val: str,
            currency: str,
            accountName: str
    ):
        """
        Callback of account update.
        """
        super(IbApi, self).updateAccountValue(key, val, currency, accountName)

        if not currency or key not in ACCOUNTFIELD_IB2VT:
            return

        accountid = f'{accountName}.{currency}'
        account = self.accounts.get(accountid, None)
        if not account:
            account = AccountData(
                accountid=accountid,
                gateway_name=self.gateway_name
            )
            self.accounts[accountid] = account

        name = ACCOUNTFIELD_IB2VT[key]
        setattr(account, name, float(val))

    def updatePortfolio(
            self,
            contract: Contract,
            position: float,
            marketPrice: float,
            marketValue: float,
            averageCost: float,
            unrealizedPNL: float,
            realizedPNL: float,
            accountName: str
    ):
        """
        Callback of position update.
        """
        super(IbApi,
              self).updatePortfolio(
                  contract,
                  position,
                  marketPrice,
                  marketValue,
                  averageCost,
                  unrealizedPNL,
                  realizedPNL,
                  accountName
              )

        pos = PositionData(
            symbol=contract.conId,
            exchange=EXCHANGE_IB2VT.get(contract.exchange,
                                        contract.exchange),
            direction=DIRECTION_NET,
            volume=position,
            price=averageCost,
            pnl=unrealizedPNL,
            gateway_name=self.gateway_name
        )
        self.gateway.on_position(pos)

    def updateAccountTime(self, timeStamp: str):
        """
        Callback of account update time.
        """
        super(IbApi, self).updateAccountTime(timeStamp)
        for account in self.accounts.values():
            self.gateway.on_account(copy(account))

    def contractDetails(self, reqId: int, contractDetails: ContractDetails):
        """
        Callback of contract data update.
        """
        super(IbApi, self).contractDetails(reqId, contractDetails)

        ib_symbol = contractDetails.contract.conId
        ib_exchange = contractDetails.contract.exchange
        ib_size = contractDetails.contract.multiplier
        ib_product = contractDetails.contract.secType

        contract = ContractData(
            symbol=ib_symbol,
            exchange=EXCHANGE_IB2VT.get(ib_exchange,
                                        ib_exchange),
            name=contractDetails.longName,
            product=PRODUCT_IB2VT[ib_product],
            size=ib_size,
            pricetick=contractDetails.minTick,
            gateway_name=self.gateway_name
        )
        self.gateway.on_contract(contract)

    def execDetails(self, reqId: int, contract: Contract, execution: Execution):
        """
        Callback of trade data update.
        """
        super(IbApi, self).execDetails(reqId, contract, execution)

        today_date = datetime.now().strftime("%Y%m%d")
        trade = TradeData(
            symbol=contract.conId,
            exchange=EXCHANGE_IB2VT.get(contract.exchange,
                                        contract.exchange),
            orderid=str(execution.orderId),
            tradeid=str(execution.execId),
            direction=DIRECTION_IB2VT[execution.side],
            price=execution.price,
            volume=execution.shares,
            time=datetime.strptime(execution.time,
                                   "%Y%m%d  %H:%M:%S"),
            gateway_name=self.gateway_name
        )

        self.gateway.on_trade(trade)

    def managedAccounts(self, accountsList: str):
        """
        Callback of all sub accountid.
        """
        super(IbApi, self).managedAccounts(accountsList)

        for account_code in accountsList.split(","):
            self.client.reqAccountUpdates(True, account_code)

    def connect(self, setting: dict):
        """
        Connect to TWS.
        """
        if self.status:
            return

        self.clientid = setting["clientid"]

        self.client.connect(
            setting["host"],
            setting["port"],
            setting["clientid"]
        )

        self.thread.start()

        n = self.client.reqCurrentTime()

    def close(self):
        """
        Disconnect to TWS.
        """
        if not self.status:
            return

        self.status = False
        self.client.disconnect()

    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe tick data update.
        """
        if not self.status:
            return

        ib_contract = Contract()
        ib_contract.conId = str(req.symbol)
        ib_contract.exchange = EXCHANGE_VT2IB[req.exchange]

        # Get contract data from TWS.
        self.reqid += 1
        self.client.reqContractDetails(self.reqid, ib_contract)

        # Subscribe tick data and create tick object buffer.
        self.reqid += 1
        self.client.reqMktData(self.reqid, ib_contract, "", False, False, [])

        tick = TickData(
            symbol=req.symbol,
            exchange=req.exchange,
            datetime=datetime.now(),
            gateway_name=self.gateway_name
        )
        self.ticks[self.reqid] = tick
        self.tick_exchange[self.reqid] = req.exchange

    def send_order(self, req: OrderRequest):
        """
        Send a new order.
        """
        if not self.status:
            return ''

        self.orderid += 1

        ib_contract = Contract()
        ib_contract.conId = str(req.symbol)
        ib_contract.exchange = EXCHANGE_VT2IB[req.exchange]

        ib_order = Order()
        ib_order.orderId = self.orderid
        ib_order.clientId = self.clientid
        ib_order.action = DIRECTION_VT2IB[req.direction]
        ib_order.orderType = PRICETYPE_VT2IB[req.price_type]
        ib_order.lmtPrice = req.price
        ib_order.totalQuantity = req.volume

        self.client.placeOrder(self.orderid, ib_contract, ib_order)
        self.client.reqIds(1)

        vt_orderid = f"{self.gateway_name}.{self.orderid}"
        return vt_orderid

    def cancel_order(self, req: CancelRequest):
        """
        Cancel an existing order.
        """
        if not self.status:
            return

        self.client.cancelOrder(int(req.orderid))


class IbClient(EClient):
    """"""

    def run(self):
        """
        Reimplement the original run message loop of eclient.
        
        Remove all unnecessary try...catch... and allow exceptions to interrupt loop.
        """
        while not self.done and self.isConnected():
            try:
                text = self.msg_queue.get(block=True, timeout=0.2)

                if len(text) > MAX_MSG_LEN:
                    errorMsg = "%s:%d:%s" % (BAD_LENGTH.msg(), len(text), text)
                    self.wrapper.error(NO_VALID_ID, BAD_LENGTH.code(), errorMsg)
                    self.disconnect()
                    break

                fields = comm.read_fields(text)
                self.decoder.interpret(fields)
            except Empty:
                pass
