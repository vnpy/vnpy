"""
Please install ibapi from Interactive Brokers github page.
"""
from copy import copy
from datetime import datetime
from queue import Empty
from threading import Thread

from ibapi import comm
from ibapi.client import EClient
from ibapi.common import MAX_MSG_LEN, NO_VALID_ID, OrderId, TickAttrib, TickerId
from ibapi.contract import Contract, ContractDetails
from ibapi.execution import Execution
from ibapi.order import Order
from ibapi.order_state import OrderState
from ibapi.ticktype import TickType
from ibapi.wrapper import EWrapper
from ibapi.errors import BAD_LENGTH

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
    SubscribeRequest
)
from vnpy.trader.constant import (
    Product,
    OrderType,
    Direction,
    Exchange,
    Currency,
    Status,
    OptionType,
)

ORDERTYPE_VT2IB = {OrderType.LIMIT: "LMT", OrderType.MARKET: "MKT"}
ORDERTYPE_IB2VT = {v: k for k, v in ORDERTYPE_VT2IB.items()}

DIRECTION_VT2IB = {Direction.LONG: "BUY", Direction.SHORT: "SELL"}
DIRECTION_IB2VT = {v: k for k, v in DIRECTION_VT2IB.items()}
DIRECTION_IB2VT["BOT"] = Direction.LONG
DIRECTION_IB2VT["SLD"] = Direction.SHORT

EXCHANGE_VT2IB = {
    Exchange.SMART: "SMART",
    Exchange.NYMEX: "NYMEX",
    Exchange.GLOBEX: "GLOBEX",
    Exchange.IDEALPRO: "IDEALPRO",
    Exchange.CME: "CME",
    Exchange.ICE: "ICE",
    Exchange.SEHK: "SEHK",
    Exchange.HKFE: "HKFE",
}
EXCHANGE_IB2VT = {v: k for k, v in EXCHANGE_VT2IB.items()}

STATUS_IB2VT = {
    "Submitted": Status.NOTTRADED,
    "Filled": Status.ALLTRADED,
    "Cancelled": Status.CANCELLED,
    "PendingSubmit": Status.SUBMITTING,
    "PreSubmitted": Status.NOTTRADED,
}

PRODUCT_VT2IB = {
    Product.EQUITY: "STK",
    Product.FOREX: "CASH",
    Product.SPOT: "CMDTY",
    Product.OPTION: "OPT",
    Product.FUTURES: "FUT",
}
PRODUCT_IB2VT = {v: k for k, v in PRODUCT_VT2IB.items()}

OPTION_VT2IB = {OptionType.CALL: "CALL", OptionType.PUT: "PUT"}

CURRENCY_VT2IB = {
    Currency.USD: "USD",
    Currency.CNY: "CNY",
    Currency.HKD: "HKD",
}

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
    14: "open_price",
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

    default_setting = {
        "TWS地址": "127.0.0.1",
        "TWS端口": 7497,
        "客户号": 1
    }

    exchanges = list(EXCHANGE_VT2IB.keys())

    def __init__(self, event_engine):
        """"""
        super(IbGateway, self).__init__(event_engine, "IB")

        self.api = IbApi(self)

    def connect(self, setting: dict):
        """
        Start gateway connection.
        """
        host = setting["TWS地址"]
        port = setting["TWS端口"]
        clientid = setting["客户号"]

        self.api.connect(host, port, clientid)

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
        self.contracts = {}

        self.tick_exchange = {}

        self.client = IbClient(self)
        self.thread = Thread(target=self.client.run)

    def connectAck(self):  # pylint: disable=invalid-name
        """
        Callback when connection is established.
        """
        self.status = True
        self.gateway.write_log("IB TWS连接成功")

    def connectionClosed(self):  # pylint: disable=invalid-name
        """
        Callback when connection is closed.
        """
        self.status = False
        self.gateway.write_log("IB TWS连接断开")

    def nextValidId(self, orderId: int):  # pylint: disable=invalid-name
        """
        Callback of next valid orderid.
        """
        super(IbApi, self).nextValidId(orderId)

        self.orderid = orderId

    def currentTime(self, time: int):  # pylint: disable=invalid-name
        """
        Callback of current server time of IB.
        """
        super(IbApi, self).currentTime(time)

        dt = datetime.fromtimestamp(time)
        time_string = dt.strftime("%Y-%m-%d %H:%M:%S.%f")

        msg = f"服务器时间: {time_string}"
        self.gateway.write_log(msg)

    def error(
        self, reqId: TickerId, errorCode: int, errorString: str
    ):  # pylint: disable=invalid-name
        """
        Callback of error caused by specific request.
        """
        super(IbApi, self).error(reqId, errorCode, errorString)

        msg = f"信息通知，代码：{errorCode}，内容: {errorString}"
        self.gateway.write_log(msg)

    def tickPrice(  # pylint: disable=invalid-name
        self, reqId: TickerId, tickType: TickType, price: float, attrib: TickAttrib
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

        # Update name into tick data.
        contract = self.contracts.get(tick.vt_symbol, None)
        if contract:
            tick.name = contract.name

        # Forex and spot product of IDEALPRO has no tick time and last price.
        # We need to calculate locally.
        exchange = self.tick_exchange[reqId]
        if exchange is Exchange.IDEALPRO:
            tick.last_price = (tick.bid_price_1 + tick.ask_price_1) / 2
            tick.datetime = datetime.now()
        self.gateway.on_tick(copy(tick))

    def tickSize(
        self, reqId: TickerId, tickType: TickType, size: int
    ):  # pylint: disable=invalid-name
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

    def tickString(
        self, reqId: TickerId, tickType: TickType, value: str
    ):  # pylint: disable=invalid-name
        """
        Callback of tick string update.
        """
        super(IbApi, self).tickString(reqId, tickType, value)

        if tickType != "45":
            return

        tick = self.ticks[reqId]
        tick.datetime = datetime.fromtimestamp(value)

        self.gateway.on_tick(copy(tick))

    def orderStatus(  # pylint: disable=invalid-name
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
        mktCapPrice: float,
    ):
        """
        Callback of order status update.
        """
        super(IbApi, self).orderStatus(
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
            mktCapPrice,
        )

        orderid = str(orderId)
        order = self.orders.get(orderid, None)
        order.status = STATUS_IB2VT[status]
        order.traded = filled

        self.gateway.on_order(copy(order))

    def openOrder(  # pylint: disable=invalid-name
        self,
        orderId: OrderId,
        ib_contract: Contract,
        ib_order: Order,
        orderState: OrderState,
    ):
        """
        Callback when opening new order.
        """
        super(IbApi, self).openOrder(
            orderId, ib_contract, ib_order, orderState
        )

        orderid = str(orderId)
        order = OrderData(
            symbol=ib_contract.conId,
            exchange=EXCHANGE_IB2VT.get(
                ib_contract.exchange, ib_contract.exchange),
            type=ORDERTYPE_IB2VT[ib_order.orderType],
            orderid=orderid,
            direction=DIRECTION_IB2VT[ib_order.action],
            price=ib_order.lmtPrice,
            volume=ib_order.totalQuantity,
            gateway_name=self.gateway_name,
        )

        self.orders[orderid] = order
        self.gateway.on_order(copy(order))

    def updateAccountValue(  # pylint: disable=invalid-name
        self, key: str, val: str, currency: str, accountName: str
    ):
        """
        Callback of account update.
        """
        super(IbApi, self).updateAccountValue(key, val, currency, accountName)

        if not currency or key not in ACCOUNTFIELD_IB2VT:
            return

        accountid = f"{accountName}.{currency}"
        account = self.accounts.get(accountid, None)
        if not account:
            account = AccountData(accountid=accountid,
                                  gateway_name=self.gateway_name)
            self.accounts[accountid] = account

        name = ACCOUNTFIELD_IB2VT[key]
        setattr(account, name, float(val))

    def updatePortfolio(  # pylint: disable=invalid-name
        self,
        contract: Contract,
        position: float,
        marketPrice: float,
        marketValue: float,
        averageCost: float,
        unrealizedPNL: float,
        realizedPNL: float,
        accountName: str,
    ):
        """
        Callback of position update.
        """
        super(IbApi, self).updatePortfolio(
            contract,
            position,
            marketPrice,
            marketValue,
            averageCost,
            unrealizedPNL,
            realizedPNL,
            accountName,
        )

        ib_size = contract.multiplier
        if not ib_size:
            ib_size = 1
        price = averageCost / ib_size

        pos = PositionData(
            symbol=contract.conId,
            exchange=EXCHANGE_IB2VT.get(contract.exchange, contract.exchange),
            direction=Direction.NET,
            volume=position,
            price=price,
            pnl=unrealizedPNL,
            gateway_name=self.gateway_name,
        )
        self.gateway.on_position(pos)

    def updateAccountTime(self, timeStamp: str):  # pylint: disable=invalid-name
        """
        Callback of account update time.
        """
        super(IbApi, self).updateAccountTime(timeStamp)
        for account in self.accounts.values():
            self.gateway.on_account(copy(account))

    def contractDetails(self, reqId: int, contractDetails: ContractDetails):  # pylint: disable=invalid-name
        """
        Callback of contract data update.
        """
        super(IbApi, self).contractDetails(reqId, contractDetails)

        ib_symbol = contractDetails.contract.conId
        ib_exchange = contractDetails.contract.exchange
        ib_size = contractDetails.contract.multiplier
        ib_product = contractDetails.contract.secType

        if not ib_size:
            ib_size = 1

        contract = ContractData(
            symbol=ib_symbol,
            exchange=EXCHANGE_IB2VT.get(ib_exchange, ib_exchange),
            name=contractDetails.longName,
            product=PRODUCT_IB2VT[ib_product],
            size=ib_size,
            pricetick=contractDetails.minTick,
            net_position=True,
            gateway_name=self.gateway_name,
        )

        self.gateway.on_contract(contract)

        self.contracts[contract.vt_symbol] = contract

    def execDetails(
        self, reqId: int, contract: Contract, execution: Execution
    ):  # pylint: disable=invalid-name
        """
        Callback of trade data update.
        """
        super(IbApi, self).execDetails(reqId, contract, execution)

        # today_date = datetime.now().strftime("%Y%m%d")
        trade = TradeData(
            symbol=contract.conId,
            exchange=EXCHANGE_IB2VT.get(contract.exchange, contract.exchange),
            orderid=str(execution.orderId),
            tradeid=str(execution.execId),
            direction=DIRECTION_IB2VT[execution.side],
            price=execution.price,
            volume=execution.shares,
            time=datetime.strptime(execution.time, "%Y%m%d  %H:%M:%S"),
            gateway_name=self.gateway_name,
        )

        self.gateway.on_trade(trade)

    def managedAccounts(self, accountsList: str):  # pylint: disable=invalid-name
        """
        Callback of all sub accountid.
        """
        super(IbApi, self).managedAccounts(accountsList)

        for account_code in accountsList.split(","):
            self.client.reqAccountUpdates(True, account_code)

    def connect(self, host: str, port: int, clientid: int):
        """
        Connect to TWS.
        """
        if self.status:
            return

        self.clientid = clientid
        self.client.connect(host, port, clientid)
        self.thread.start()

        self.client.reqCurrentTime()

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

        if req.exchange not in EXCHANGE_VT2IB:
            self.gateway.write_log(f"不支持的交易所{req.exchange}")
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
            gateway_name=self.gateway_name,
        )
        self.ticks[self.reqid] = tick
        self.tick_exchange[self.reqid] = req.exchange

    def send_order(self, req: OrderRequest):
        """
        Send a new order.
        """
        if not self.status:
            return ""

        if req.exchange not in EXCHANGE_VT2IB:
            self.gateway.write_log(f"不支持的交易所：{req.exchange}")
            return ""

        if req.type not in ORDERTYPE_VT2IB:
            self.gateway.write_log(f"不支持的价格类型：{req.type}")
            return ""

        self.orderid += 1

        ib_contract = Contract()
        ib_contract.conId = str(req.symbol)
        ib_contract.exchange = EXCHANGE_VT2IB[req.exchange]

        ib_order = Order()
        ib_order.orderId = self.orderid
        ib_order.clientId = self.clientid
        ib_order.action = DIRECTION_VT2IB[req.direction]
        ib_order.orderType = ORDERTYPE_VT2IB[req.type]
        ib_order.lmtPrice = req.price
        ib_order.totalQuantity = req.volume

        self.client.placeOrder(self.orderid, ib_contract, ib_order)
        self.client.reqIds(1)

        order = req.create_order_data(str(self.orderid), self.gateway_name)
        self.gateway.on_order(order)
        return order.vt_orderid

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
                    self.wrapper.error(
                        NO_VALID_ID, BAD_LENGTH.code(), errorMsg
                    )
                    self.disconnect()
                    break

                fields = comm.read_fields(text)
                self.decoder.interpret(fields)
            except Empty:
                pass
