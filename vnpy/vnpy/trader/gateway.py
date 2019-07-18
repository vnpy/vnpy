"""

"""

from abc import ABC, abstractmethod
from typing import Any, Sequence
from copy import copy

from vnpy.event import Event, EventEngine
from .event import (
    EVENT_TICK,
    EVENT_ORDER,
    EVENT_TRADE,
    EVENT_POSITION,
    EVENT_ACCOUNT,
    EVENT_CONTRACT,
    EVENT_LOG,
)
from .object import (
    TickData,
    OrderData,
    TradeData,
    PositionData,
    AccountData,
    ContractData,
    LogData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest
)


class BaseGateway(ABC):
    """
    Abstract gateway class for creating gateways connection
    to different trading systems.

    # How to implement a gateway:

    ---
    ## Basics
    A gateway should satisfies:
    * this class should be thread-safe:
        * all methods should be thread-safe
        * no mutable shared properties between objects.
    * all methods should be non-blocked
    * satisfies all requirements written in docstring for every method and callbacks.
    * automatically reconnect if connection lost.

    ---
    ## methods must implements:
    all @abstractmethod

    ---
    ## callbacks must response manually:
    * on_tick
    * on_trade
    * on_order
    * on_position
    * on_account
    * on_contract

    All the XxxData passed to callback should be constant, which means that
        the object should not be modified after passing to on_xxxx.
    So if you use a cache to store reference of data, use copy.copy to create a new object
    before passing that data into on_xxxx



    """

    # Fields required in setting dict for connect function.
    default_setting = {}

    # Exchanges supported in the gateway.
    exchanges = []

    def __init__(self, event_engine: EventEngine, gateway_name: str):
        """"""
        self.event_engine = event_engine
        self.gateway_name = gateway_name

    def on_event(self, type: str, data: Any = None):
        """
        General event push.
        """
        event = Event(type, data)
        self.event_engine.put(event)

    def on_tick(self, tick: TickData):
        """
        Tick event push.
        Tick event of a specific vt_symbol is also pushed.
        """
        self.on_event(EVENT_TICK, tick)
        self.on_event(EVENT_TICK + tick.vt_symbol, tick)

    def on_trade(self, trade: TradeData):
        """
        Trade event push.
        Trade event of a specific vt_symbol is also pushed.
        """
        self.on_event(EVENT_TRADE, trade)
        self.on_event(EVENT_TRADE + trade.vt_symbol, trade)

    def on_order(self, order: OrderData):
        """
        Order event push.
        Order event of a specific vt_orderid is also pushed.
        """
        self.on_event(EVENT_ORDER, order)
        self.on_event(EVENT_ORDER + order.vt_orderid, order)

    def on_position(self, position: PositionData):
        """
        Position event push.
        Position event of a specific vt_symbol is also pushed.
        """
        self.on_event(EVENT_POSITION, position)
        self.on_event(EVENT_POSITION + position.vt_symbol, position)

    def on_account(self, account: AccountData):
        """
        Account event push.
        Account event of a specific vt_accountid is also pushed.
        """
        self.on_event(EVENT_ACCOUNT, account)
        self.on_event(EVENT_ACCOUNT + account.vt_accountid, account)

    def on_log(self, log: LogData):
        """
        Log event push.
        """
        self.on_event(EVENT_LOG, log)

    def on_contract(self, contract: ContractData):
        """
        Contract event push.
        """
        self.on_event(EVENT_CONTRACT, contract)

    def write_log(self, msg: str):
        """
        Write a log event from gateway.
        """
        log = LogData(msg=msg, gateway_name=self.gateway_name)
        self.on_log(log)

    @abstractmethod
    def connect(self, setting: dict):
        """
        Start gateway connection.

        to implement this method, you must:
        * connect to server if necessary
        * log connected if all necessary connection is established
        * do the following query and response corresponding on_xxxx and write_log
            * contracts : on_contract
            * account asset : on_account
            * account holding: on_position
            * orders of account: on_order
            * trades of account: on_trade
        * if any of query above is failed,  write log.

        future plan:
        response callback/change status instead of write_log

        """
        pass

    @abstractmethod
    def close(self):
        """
        Close gateway connection.
        """
        pass

    @abstractmethod
    def subscribe(self, req: SubscribeRequest):
        """
        Subscribe tick data update.
        """
        pass

    @abstractmethod
    def send_order(self, req: OrderRequest) -> str:
        """
        Send a new order to server.

        implementation should finish the tasks blow:
        * create an OrderData from req using OrderRequest.create_order_data
        * assign a unique(gateway instance scope) id to OrderData.orderid
        * send request to server
            * if request is sent, OrderData.status should be set to Status.SUBMITTING
            * if request is failed to sent, OrderData.status should be set to Status.REJECTED
        * response on_order:
        * return OrderData.vt_orderid

        :return str vt_orderid for created OrderData
        """
        pass

    @abstractmethod
    def cancel_order(self, req: CancelRequest):
        """
        Cancel an existing order.
        implementation should finish the tasks blow:
        * send request to server
        """
        pass

    def send_orders(self, reqs: Sequence[OrderRequest]):
        """
        Send a batch of orders to server.
        Use a for loop of send_order function by default. 
        Reimplement this function if batch order supported on server.
        """
        vt_orderids = []

        for req in reqs:
            vt_orderid = self.send_order(req)
            vt_orderids.append(vt_orderid)

        return vt_orderids

    def cancel_orders(self, reqs: Sequence[CancelRequest]):
        """
        Cancel a batch of orders to server.
        Use a for loop of cancel_order function by default. 
        Reimplement this function if batch cancel supported on server.
        """
        for req in reqs:
            self.cancel_order(req)

    @abstractmethod
    def query_account(self):
        """
        Query account balance.
        """
        pass

    @abstractmethod
    def query_position(self):
        """
        Query holding positions.
        """
        pass

    def query_history(self, req: HistoryRequest):
        """
        Query bar history data.
        """
        pass

    def get_default_setting(self):
        """
        Return default setting dict.
        """
        return self.default_setting


class LocalOrderManager:
    """
    Management tool to support use local order id for trading.
    """

    def __init__(self, gateway: BaseGateway):
        """"""
        self.gateway = gateway

        # For generating local orderid
        self.order_prefix = ""
        self.order_count = 0
        self.orders = {}        # local_orderid:order

        # Map between local and system orderid
        self.local_sys_orderid_map = {}
        self.sys_local_orderid_map = {}

        # Push order data buf
        self.push_data_buf = {}  # sys_orderid:data

        # Callback for processing push order data
        self.push_data_callback = None

        # Cancel request buf
        self.cancel_request_buf = {}    # local_orderid:req

    def new_local_orderid(self):
        """
        Generate a new local orderid.
        """
        self.order_count += 1
        local_orderid = str(self.order_count).rjust(8, "0")
        return local_orderid

    def get_local_orderid(self, sys_orderid: str):
        """
        Get local orderid with sys orderid.
        """
        local_orderid = self.sys_local_orderid_map.get(sys_orderid, "")

        if not local_orderid:
            local_orderid = self.new_local_orderid()
            self.update_orderid_map(local_orderid, sys_orderid)

        return local_orderid

    def get_sys_orderid(self, local_orderid: str):
        """
        Get sys orderid with local orderid.
        """
        sys_orderid = self.local_sys_orderid_map.get(local_orderid, "")
        return sys_orderid

    def update_orderid_map(self, local_orderid: str, sys_orderid: str):
        """
        Update orderid map.
        """
        self.sys_local_orderid_map[sys_orderid] = local_orderid
        self.local_sys_orderid_map[local_orderid] = sys_orderid

        self.check_cancel_request(local_orderid)
        self.check_push_data(sys_orderid)

    def check_push_data(self, sys_orderid: str):
        """
        Check if any order push data waiting.
        """
        if sys_orderid not in self.push_data_buf:
            return

        data = self.push_data_buf.pop(sys_orderid)
        if self.push_data_callback:
            self.push_data_callback(data)

    def add_push_data(self, sys_orderid: str, data: dict):
        """
        Add push data into buf.
        """
        self.push_data_buf[sys_orderid] = data

    def get_order_with_sys_orderid(self, sys_orderid: str):
        """"""
        local_orderid = self.sys_local_orderid_map.get(sys_orderid, None)
        if not local_orderid:
            return None
        else:
            return self.get_order_with_local_orderid(local_orderid)

    def get_order_with_local_orderid(self, local_orderid: str):
        """"""
        order = self.orders[local_orderid]
        return copy(order)

    def on_order(self, order: OrderData):
        """
        Keep an order buf before pushing it to gateway.
        """
        self.orders[order.orderid] = copy(order)
        self.gateway.on_order(order)

    def cancel_order(self, req: CancelRequest):
        """
        """
        sys_orderid = self.get_sys_orderid(req.orderid)
        if not sys_orderid:
            self.cancel_request_buf[req.orderid] = req
            return

        self.gateway.cancel_order(req)

    def check_cancel_request(self, local_orderid: str):
        """
        """
        if local_orderid not in self.cancel_request_buf:
            return

        req = self.cancel_request_buf.pop(local_orderid)
        self.gateway.cancel_order(req)
