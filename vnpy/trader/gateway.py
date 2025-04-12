from abc import ABC, abstractmethod
from typing import Optional, Callable
from copy import copy
from logging import INFO

from vnpy.event import Event, EventEngine
from .event import (
    EVENT_TICK,
    EVENT_ORDER,
    EVENT_TRADE,
    EVENT_POSITION,
    EVENT_ACCOUNT,
    EVENT_CONTRACT,
    EVENT_LOG,
    EVENT_QUOTE, EVENT_BAR,
)
from .object import (
    TickData,
    OrderData,
    TradeData,
    PositionData,
    AccountData,
    ContractData,
    LogData,
    QuoteData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest,
    QuoteRequest,
    Exchange,
    BarData
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

    # Default name for the gateway.
    default_name: str = ""

    # Fields required in setting dict for connect function.
    default_setting: dict[str, str | int | float | bool] = {}

    # Exchanges supported in the gateway.
    exchanges: list[Exchange] = []

    def __init__(self, event_engine: EventEngine, gateway_name: str) -> None:
        """"""
        self.event_engine: EventEngine = event_engine
        self.gateway_name: str = gateway_name

    def on_event(self, type: str, data: object = None) -> None:
        """
        General event push.
        """
        event: Event = Event(type, data)
        self.event_engine.put(event)

    def on_tick(self, tick: TickData) -> None:
        """
        Tick event push.
        Tick event of a specific vt_symbol is also pushed.
        """
        self.on_event(EVENT_TICK, tick)
        # Avoid redundant calls by combining event creation
        specific_event_type = EVENT_TICK + tick.vt_symbol
        self.on_event(specific_event_type, tick)

    def on_bar(self, bar: BarData) -> None:
        """
        Bar event push.
        Bar event of a specific vt_symbol is also pushed.
        """
        self.on_event(EVENT_BAR, bar)
        specific_event_type = EVENT_BAR + bar.vt_symbol
        self.on_event(specific_event_type, bar)

    def on_trade(self, trade: TradeData) -> None:
        """
        Trade event push.
        Trade event of a specific vt_symbol is also pushed.
        """
        self.on_event(EVENT_TRADE, trade)
        specific_event_type = EVENT_TRADE + trade.vt_symbol
        self.on_event(specific_event_type, trade)

    def on_order(self, order: OrderData) -> None:
        """
        Order event push.
        Order event of a specific vt_orderid is also pushed.
        """
        self.on_event(EVENT_ORDER, order)
        specific_event_type = EVENT_ORDER + order.vt_orderid
        self.on_event(specific_event_type, order)

    def on_position(self, position: PositionData) -> None:
        """
        Position event push.
        Position event of a specific vt_symbol is also pushed.
        """
        self.on_event(EVENT_POSITION, position)
        specific_event_type = EVENT_POSITION + position.vt_symbol
        self.on_event(specific_event_type, position)

    def on_account(self, account: AccountData) -> None:
        """
        Account event push.
        Account event of a specific vt_accountid is also pushed.
        """
        self.on_event(EVENT_ACCOUNT, account)
        specific_event_type = EVENT_ACCOUNT + account.vt_accountid
        self.on_event(specific_event_type, account)

    def on_quote(self, quote: QuoteData) -> None:
        """
        Quote event push.
        Quote event of a specific vt_symbol is also pushed.
        """
        self.on_event(EVENT_QUOTE, quote)
        specific_event_type = EVENT_QUOTE + quote.vt_symbol
        self.on_event(specific_event_type, quote)

    def on_log(self, log: LogData) -> None:
        """
        Log event push.
        """
        self.on_event(EVENT_LOG, log)

    def on_contract(self, contract: ContractData) -> None:
        """
        Contract event push.
        """
        self.on_event(EVENT_CONTRACT, contract)

    def write_log(self, msg: str, level=INFO) -> None:
        """
        Write a log event from gateway.
        """
        log: LogData = LogData(msg=msg, gateway_name=self.gateway_name, level=level)
        self.on_log(log)

    @abstractmethod
    def connect(self, setting: dict) -> None:
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
    def close(self) -> None:
        """
        Close gateway connection.
        """
        pass

    @abstractmethod
    def subscribe(self, req: SubscribeRequest) -> None:
        """
        Subscribe tick data update.
        """
        pass

    @abstractmethod
    def send_order(self, req: OrderRequest) -> str:
        """
        Send a new order to server.

        order_data: OrderData = req.create_order_data()
        def convert2binance_order(order_data) -> dict:
            return {}

        order_params = convert2binance_order(order_data)
        self.spot.send_order(**order_params)

        implementation should finish the tasks blow:
        * create an OrderData from req using OrderRequest.create_order_data
        * assign a unique(gateway instance scope) id to OrderData.orderid
        * send request to server
            * if request is sent, OrderData.status should be set to Status.SUBMITTING
            * if request is failed to sent, OrderData.status should be set to Status.REJECTED
        * response on_order:
        * return vt_orderid

        :return str vt_orderid for created OrderData
        """
        pass

    @abstractmethod
    def cancel_order(self, req: CancelRequest) -> None:
        """
        Cancel an existing order.
        implementation should finish the tasks blow:
        * send request to server
        """
        pass

    def send_quote(self, req: QuoteRequest) -> str:
        """
        Send a new two-sided quote to server.

        implementation should finish the tasks blow:
        * create an QuoteData from req using QuoteRequest.create_quote_data
        * assign a unique(gateway instance scope) id to QuoteData.quoteid
        * send request to server
            * if request is sent, QuoteData.status should be set to Status.SUBMITTING
            * if request is failed to sent, QuoteData.status should be set to Status.REJECTED
        * response on_quote:
        * return vt_quoteid

        :return str vt_quoteid for created QuoteData
        """
        return ""

    def cancel_quote(self, req: CancelRequest) -> None:
        """
        Cancel an existing quote.
        implementation should finish the tasks blow:
        * send request to server
        """
        return

    @abstractmethod
    def query_account(self) -> None:
        """
        Query account balance.
        """
        pass

    @abstractmethod
    def query_position(self) -> None:
        """
        Query holding positions.
        """
        pass

    def query_history(self, req: HistoryRequest) -> list[BarData]:
        """
        Query bar history data.
        """
        return []

    def get_default_setting(self) -> dict[str, str | int | float | bool]:
        """
        Return default setting dict.
        """
        return self.default_setting


class LocalOrderManager:
    """
    Management tool to support use local order id for trading.
    """

    def __init__(self, gateway: BaseGateway, order_prefix: str = "") -> None:
        """"""
        self.gateway: BaseGateway = gateway

        # For generating local orderid
        self.order_prefix: str = order_prefix
        self.order_count: int = 0
        self.orders: dict[str, OrderData] = {}        # local_orderid: order

        # Map between local and system orderid
        self.local_sys_orderid_map: dict[str, str] = {}
        self.sys_local_orderid_map: dict[str, str] = {}

        # Push order data buf
        self.push_data_buf: dict[str, dict] = {}  # sys_orderid: data

        # Callback for processing push order data
        self.push_data_callback: Callable = None

        # Cancel request buf
        self.cancel_request_buf: dict[str, CancelRequest] = {}    # local_orderid: req

        # Hook cancel order function
        self._cancel_order: Callable = gateway.cancel_order
        gateway.cancel_order = self.cancel_order

    def new_local_orderid(self) -> str:
        """
        Generate a new local orderid.
        """
        self.order_count += 1
        local_orderid: str = self.order_prefix + str(self.order_count).rjust(8, "0")
        return local_orderid

    def get_local_orderid(self, sys_orderid: str) -> str:
        """
        Get local orderid with sys orderid.
        """
        local_orderid: str = self.sys_local_orderid_map.get(sys_orderid, "")

        if not local_orderid:
            local_orderid = self.new_local_orderid()
            self.update_orderid_map(local_orderid, sys_orderid)

        return local_orderid

    def get_sys_orderid(self, local_orderid: str) -> str:
        """
        Get sys orderid with local orderid.
        """
        sys_orderid: str = self.local_sys_orderid_map.get(local_orderid, "")
        return sys_orderid

    def update_orderid_map(self, local_orderid: str, sys_orderid: str) -> None:
        """
        Update orderid map.
        """
        self.sys_local_orderid_map[sys_orderid] = local_orderid
        self.local_sys_orderid_map[local_orderid] = sys_orderid

        self.check_cancel_request(local_orderid)
        self.check_push_data(sys_orderid)

    def check_push_data(self, sys_orderid: str) -> None:
        """
        Check if any order push data waiting.
        """
        if sys_orderid not in self.push_data_buf:
            return

        data: dict = self.push_data_buf.pop(sys_orderid)
        if self.push_data_callback:
            self.push_data_callback(data)

    def add_push_data(self, sys_orderid: str, data: dict) -> None:
        """
        Add push data into buf.
        """
        self.push_data_buf[sys_orderid] = data

    def get_order_with_sys_orderid(self, sys_orderid: str) -> Optional[OrderData]:
        """"""
        local_orderid: str = self.sys_local_orderid_map.get(sys_orderid, None)
        if not local_orderid:
            return None
        else:
            return self.get_order_with_local_orderid(local_orderid)

    def get_order_with_local_orderid(self, local_orderid: str) -> OrderData:
        """"""
        order: OrderData = self.orders[local_orderid]
        return copy(order)

    def on_order(self, order: OrderData) -> None:
        """
        Keep an order buf before pushing it to gateway.
        """
        self.orders[order.orderid] = copy(order)
        self.gateway.on_order(order)

    def cancel_order(self, req: CancelRequest) -> None:
        """"""
        sys_orderid: str = self.get_sys_orderid(req.orderid)
        if not sys_orderid:
            self.cancel_request_buf[req.orderid] = req
            return

        self._cancel_order(req)

    def check_cancel_request(self, local_orderid: str) -> None:
        """"""
        if local_orderid not in self.cancel_request_buf:
            return

        req: CancelRequest = self.cancel_request_buf.pop(local_orderid)
        self.gateway.cancel_order(req)
