import logging
from logging import Logger
import smtplib
import os
import traceback
from abc import ABC
from pathlib import Path
from datetime import datetime
from email.message import EmailMessage
from queue import Empty, Queue
from threading import Thread
from typing import Type, Callable, TypeVar

from vnpy.event import Event, EventEngine
from .app import BaseApp
from .event import (
    EVENT_TICK,
    EVENT_ORDER,
    EVENT_TRADE,
    EVENT_POSITION,
    EVENT_ACCOUNT,
    EVENT_CONTRACT,
    EVENT_LOG,
    EVENT_QUOTE
)
from .gateway import BaseGateway
from .object import (
    CancelRequest,
    LogData,
    OrderRequest,
    QuoteData,
    QuoteRequest,
    SubscribeRequest,
    HistoryRequest,
    OrderData,
    BarData,
    TickData,
    TradeData,
    PositionData,
    AccountData,
    ContractData,
    Exchange
)
from .setting import SETTINGS
from .utility import get_folder_path, TRADER_DIR
from .converter import OffsetConverter
from .locale import _


EngineType = TypeVar("EngineType", bound="BaseEngine")


class MainEngine:
    """
    Acts as the core of the trading platform.
    """

    def __init__(self, event_engine: EventEngine | None = None) -> None:
        """"""
        if event_engine:
            self.event_engine: EventEngine = event_engine
        else:
            self.event_engine = EventEngine()
        self.event_engine.start()

        self.gateways: dict[str, BaseGateway] = {}
        self.engines: dict[str, BaseEngine] = {}
        self.apps: dict[str, BaseApp] = {}
        self.exchanges: list[Exchange] = []

        os.chdir(TRADER_DIR)    # Change working directory
        self.init_engines()     # Initialize function engines

    def add_engine(self, engine_class: Type[EngineType]) -> EngineType:
        """
        Add function engine.
        """
        engine: EngineType = engine_class(self, self.event_engine)      # type: ignore
        self.engines[engine.engine_name] = engine
        return engine

    def add_gateway(self, gateway_class: Type[BaseGateway], gateway_name: str = "") -> BaseGateway:
        """
        Add gateway.
        """
        # Use default name if gateway_name not passed
        if not gateway_name:
            gateway_name = gateway_class.default_name

        gateway: BaseGateway = gateway_class(self.event_engine, gateway_name)
        self.gateways[gateway_name] = gateway

        # Add gateway supported exchanges into engine
        for exchange in gateway.exchanges:
            if exchange not in self.exchanges:
                self.exchanges.append(exchange)

        return gateway

    def add_app(self, app_class: Type[BaseApp]) -> "BaseEngine":
        """
        Add app.
        """
        app: BaseApp = app_class()
        self.apps[app.app_name] = app

        engine: BaseEngine = self.add_engine(app.engine_class)
        return engine

    def init_engines(self) -> None:
        """
        Init all engines.
        """
        self.add_engine(LogEngine)

        oms_engine: OmsEngine = self.add_engine(OmsEngine)
        self.get_order: Callable[[str], OrderData | None] = oms_engine.get_order
        self.get_trade: Callable[[str], TradeData | None] = oms_engine.get_trade
        self.get_position: Callable[[str], PositionData | None] = oms_engine.get_position
        self.get_account: Callable[[str], AccountData | None] = oms_engine.get_account
        self.get_contract: Callable[[str], ContractData | None] = oms_engine.get_contract
        self.get_quote: Callable[[str], QuoteData | None] = oms_engine.get_quote
        self.get_all_ticks: Callable[[], list[TickData]] = oms_engine.get_all_ticks
        self.get_all_orders: Callable[[], list[OrderData]] = oms_engine.get_all_orders
        self.get_all_trades: Callable[[], list[TradeData]] = oms_engine.get_all_trades
        self.get_all_positions: Callable[[], list[PositionData]] = oms_engine.get_all_positions
        self.get_all_accounts: Callable[[], list[AccountData]] = oms_engine.get_all_accounts
        self.get_all_contracts: Callable[[], list[ContractData]] = oms_engine.get_all_contracts
        self.get_all_quotes: Callable[[], list[QuoteData]] = oms_engine.get_all_quotes
        self.get_all_active_orders: Callable[[], list[OrderData]] = oms_engine.get_all_active_orders
        self.get_all_active_quotes: Callable[[], list[QuoteData]] = oms_engine.get_all_active_quotes
        self.update_order_request: Callable[[OrderRequest, str, str], None] = oms_engine.update_order_request
        self.convert_order_request: Callable[[OrderRequest, str, bool, bool], list[OrderRequest]] = oms_engine.convert_order_request
        self.get_converter: Callable[[str], OffsetConverter | None] = oms_engine.get_converter

        email_engine: EmailEngine = self.add_engine(EmailEngine)
        self.send_email: Callable[[str, str, str | None], None] = email_engine.send_email

    def write_log(self, msg: str, source: str = "") -> None:
        """
        Put log event with specific message.
        """
        log: LogData = LogData(msg=msg, gateway_name=source)
        event: Event = Event(EVENT_LOG, log)
        self.event_engine.put(event)

    def get_gateway(self, gateway_name: str) -> BaseGateway | None:
        """
        Return gateway object by name.
        """
        gateway: BaseGateway | None = self.gateways.get(gateway_name, None)
        if not gateway:
            self.write_log(_("找不到底层接口：{}").format(gateway_name))
        return gateway

    def get_engine(self, engine_name: str) -> "BaseEngine" | None:
        """
        Return engine object by name.
        """
        engine: BaseEngine | None = self.engines.get(engine_name, None)
        if not engine:
            self.write_log(_("找不到引擎：{}").format(engine_name))
        return engine

    def get_default_setting(self, gateway_name: str) -> dict[str, str | bool | int | float] | None:
        """
        Get default setting dict of a specific gateway.
        """
        gateway: BaseGateway | None = self.get_gateway(gateway_name)
        if gateway:
            return gateway.get_default_setting()
        return None

    def get_all_gateway_names(self) -> list[str]:
        """
        Get all names of gateway added in main engine.
        """
        return list(self.gateways.keys())

    def get_all_apps(self) -> list[BaseApp]:
        """
        Get all app objects.
        """
        return list(self.apps.values())

    def get_all_exchanges(self) -> list[Exchange]:
        """
        Get all exchanges.
        """
        return self.exchanges

    def connect(self, setting: dict, gateway_name: str) -> None:
        """
        Start connection of a specific gateway.
        """
        gateway: BaseGateway | None = self.get_gateway(gateway_name)
        if gateway:
            gateway.connect(setting)

    def subscribe(self, req: SubscribeRequest, gateway_name: str) -> None:
        """
        Subscribe tick data update of a specific gateway.
        """
        gateway: BaseGateway | None = self.get_gateway(gateway_name)
        if gateway:
            gateway.subscribe(req)

    def send_order(self, req: OrderRequest, gateway_name: str) -> str:
        """
        Send new order request to a specific gateway.
        """
        gateway: BaseGateway | None = self.get_gateway(gateway_name)
        if gateway:
            return gateway.send_order(req)
        else:
            return ""

    def cancel_order(self, req: CancelRequest, gateway_name: str) -> None:
        """
        Send cancel order request to a specific gateway.
        """
        gateway: BaseGateway | None = self.get_gateway(gateway_name)
        if gateway:
            gateway.cancel_order(req)

    def send_quote(self, req: QuoteRequest, gateway_name: str) -> str:
        """
        Send new quote request to a specific gateway.
        """
        gateway: BaseGateway | None = self.get_gateway(gateway_name)
        if gateway:
            return gateway.send_quote(req)
        else:
            return ""

    def cancel_quote(self, req: CancelRequest, gateway_name: str) -> None:
        """
        Send cancel quote request to a specific gateway.
        """
        gateway: BaseGateway | None = self.get_gateway(gateway_name)
        if gateway:
            gateway.cancel_quote(req)

    def query_history(self, req: HistoryRequest, gateway_name: str) -> list[BarData]:
        """
        Query bar history data from a specific gateway.
        """
        gateway: BaseGateway | None = self.get_gateway(gateway_name)
        if gateway:
            return gateway.query_history(req)
        else:
            return []

    def close(self) -> None:
        """
        Make sure every gateway and app is closed properly before
        programme exit.
        """
        # Stop event engine first to prevent new timer event.
        self.event_engine.stop()

        for engine in self.engines.values():
            engine.close()

        for gateway in self.gateways.values():
            gateway.close()


class BaseEngine(ABC):
    """
    Abstract class for implementing a function engine.
    """

    def __init__(
        self,
        main_engine: MainEngine,
        event_engine: EventEngine,
        engine_name: str,
    ) -> None:
        """"""
        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine
        self.engine_name: str = engine_name

    def close(self) -> None:
        """"""
        pass


class LogEngine(BaseEngine):
    """
    Processes log event and output with logging module.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__(main_engine, event_engine, "log")

        if not SETTINGS["log.active"]:
            return

        self.level: int = SETTINGS["log.level"]

        self.logger: Logger = logging.getLogger("veighna")
        self.logger.setLevel(self.level)

        self.formatter: logging.Formatter = logging.Formatter(
            "%(asctime)s  %(levelname)s: %(message)s"
        )

        self.add_null_handler()

        if SETTINGS["log.console"]:
            self.add_console_handler()

        if SETTINGS["log.file"]:
            self.add_file_handler()

        self.register_event()

    def add_null_handler(self) -> None:
        """
        Add null handler for logger.
        """
        null_handler: logging.NullHandler = logging.NullHandler()
        self.logger.addHandler(null_handler)

    def add_console_handler(self) -> None:
        """
        Add console output of log.
        """
        console_handler: logging.StreamHandler = logging.StreamHandler()
        console_handler.setLevel(self.level)
        console_handler.setFormatter(self.formatter)
        self.logger.addHandler(console_handler)

    def add_file_handler(self) -> None:
        """
        Add file output of log.
        """
        today_date: str = datetime.now().strftime("%Y%m%d")
        filename: str = f"vt_{today_date}.log"
        log_path: Path = get_folder_path("log")
        file_path: Path = log_path.joinpath(filename)

        file_handler: logging.FileHandler = logging.FileHandler(
            file_path, mode="a", encoding="utf8"
        )
        file_handler.setLevel(self.level)
        file_handler.setFormatter(self.formatter)
        self.logger.addHandler(file_handler)

    def register_event(self) -> None:
        """"""
        self.event_engine.register(EVENT_LOG, self.process_log_event)

    def process_log_event(self, event: Event) -> None:
        """
        Process log event.
        """
        log: LogData = event.data
        self.logger.log(log.level, log.msg)


class OmsEngine(BaseEngine):
    """
    Provides order management system function.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__(main_engine, event_engine, "oms")

        self.ticks: dict[str, TickData] = {}
        self.orders: dict[str, OrderData] = {}
        self.trades: dict[str, TradeData] = {}
        self.positions: dict[str, PositionData] = {}
        self.accounts: dict[str, AccountData] = {}
        self.contracts: dict[str, ContractData] = {}
        self.quotes: dict[str, QuoteData] = {}

        self.active_orders: dict[str, OrderData] = {}
        self.active_quotes: dict[str, QuoteData] = {}

        self.offset_converters: dict[str, OffsetConverter] = {}

        self.register_event()

    def register_event(self) -> None:
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_POSITION, self.process_position_event)
        self.event_engine.register(EVENT_ACCOUNT, self.process_account_event)
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)
        self.event_engine.register(EVENT_QUOTE, self.process_quote_event)

    def process_tick_event(self, event: Event) -> None:
        """"""
        tick: TickData = event.data
        self.ticks[tick.vt_symbol] = tick

    def process_order_event(self, event: Event) -> None:
        """"""
        order: OrderData = event.data
        self.orders[order.vt_orderid] = order

        # If order is active, then update data in dict.
        if order.is_active():
            self.active_orders[order.vt_orderid] = order
        # Otherwise, pop inactive order from in dict
        elif order.vt_orderid in self.active_orders:
            self.active_orders.pop(order.vt_orderid)

        # Update to offset converter
        converter: OffsetConverter | None = self.offset_converters.get(order.gateway_name, None)
        if converter:
            converter.update_order(order)

    def process_trade_event(self, event: Event) -> None:
        """"""
        trade: TradeData = event.data
        self.trades[trade.vt_tradeid] = trade

        # Update to offset converter
        converter: OffsetConverter | None = self.offset_converters.get(trade.gateway_name, None)
        if converter:
            converter.update_trade(trade)

    def process_position_event(self, event: Event) -> None:
        """"""
        position: PositionData = event.data
        self.positions[position.vt_positionid] = position

        # Update to offset converter
        converter: OffsetConverter | None = self.offset_converters.get(position.gateway_name, None)
        if converter:
            converter.update_position(position)

    def process_account_event(self, event: Event) -> None:
        """"""
        account: AccountData = event.data
        self.accounts[account.vt_accountid] = account

    def process_contract_event(self, event: Event) -> None:
        """"""
        contract: ContractData = event.data
        self.contracts[contract.vt_symbol] = contract

        # Initialize offset converter for each gateway
        if contract.gateway_name not in self.offset_converters:
            self.offset_converters[contract.gateway_name] = OffsetConverter(self)

    def process_quote_event(self, event: Event) -> None:
        """"""
        quote: QuoteData = event.data
        self.quotes[quote.vt_quoteid] = quote

        # If quote is active, then update data in dict.
        if quote.is_active():
            self.active_quotes[quote.vt_quoteid] = quote
        # Otherwise, pop inactive quote from in dict
        elif quote.vt_quoteid in self.active_quotes:
            self.active_quotes.pop(quote.vt_quoteid)

    def get_tick(self, vt_symbol: str) -> TickData | None:
        """
        Get latest market tick data by vt_symbol.
        """
        return self.ticks.get(vt_symbol, None)

    def get_order(self, vt_orderid: str) -> OrderData | None:
        """
        Get latest order data by vt_orderid.
        """
        return self.orders.get(vt_orderid, None)

    def get_trade(self, vt_tradeid: str) -> TradeData | None:
        """
        Get trade data by vt_tradeid.
        """
        return self.trades.get(vt_tradeid, None)

    def get_position(self, vt_positionid: str) -> PositionData | None:
        """
        Get latest position data by vt_positionid.
        """
        return self.positions.get(vt_positionid, None)

    def get_account(self, vt_accountid: str) -> AccountData | None:
        """
        Get latest account data by vt_accountid.
        """
        return self.accounts.get(vt_accountid, None)

    def get_contract(self, vt_symbol: str) -> ContractData | None:
        """
        Get contract data by vt_symbol.
        """
        return self.contracts.get(vt_symbol, None)

    def get_quote(self, vt_quoteid: str) -> QuoteData | None:
        """
        Get latest quote data by vt_orderid.
        """
        return self.quotes.get(vt_quoteid, None)

    def get_all_ticks(self) -> list[TickData]:
        """
        Get all tick data.
        """
        return list(self.ticks.values())

    def get_all_orders(self) -> list[OrderData]:
        """
        Get all order data.
        """
        return list(self.orders.values())

    def get_all_trades(self) -> list[TradeData]:
        """
        Get all trade data.
        """
        return list(self.trades.values())

    def get_all_positions(self) -> list[PositionData]:
        """
        Get all position data.
        """
        return list(self.positions.values())

    def get_all_accounts(self) -> list[AccountData]:
        """
        Get all account data.
        """
        return list(self.accounts.values())

    def get_all_contracts(self) -> list[ContractData]:
        """
        Get all contract data.
        """
        return list(self.contracts.values())

    def get_all_quotes(self) -> list[QuoteData]:
        """
        Get all quote data.
        """
        return list(self.quotes.values())

    def get_all_active_orders(self) -> list[OrderData]:
        """
        Get all active orders.
        """
        return list(self.active_orders.values())

    def get_all_active_quotes(self) -> list[QuoteData]:
        """
        Get all active quotes.
        """
        return list(self.active_quotes.values())

    def update_order_request(self, req: OrderRequest, vt_orderid: str, gateway_name: str) -> None:
        """
        Update order request to offset converter.
        """
        converter: OffsetConverter | None = self.offset_converters.get(gateway_name, None)
        if converter:
            converter.update_order_request(req, vt_orderid)

    def convert_order_request(
        self,
        req: OrderRequest,
        gateway_name: str,
        lock: bool,
        net: bool = False
    ) -> list[OrderRequest]:
        """
        Convert original order request according to given mode.
        """
        converter: OffsetConverter | None = self.offset_converters.get(gateway_name, None)
        if not converter:
            return [req]

        reqs: list[OrderRequest] = converter.convert_order_request(req, lock, net)
        return reqs

    def get_converter(self, gateway_name: str) -> OffsetConverter | None:
        """
        Get offset converter object of specific gateway.
        """
        return self.offset_converters.get(gateway_name, None)


class EmailEngine(BaseEngine):
    """
    Provides email sending function.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__(main_engine, event_engine, "email")

        self.thread: Thread = Thread(target=self.run)
        self.queue: Queue = Queue()
        self.active: bool = False

    def send_email(self, subject: str, content: str, receiver: str | None = None) -> None:
        """"""
        # Start email engine when sending first email.
        if not self.active:
            self.start()

        # Use default receiver if not specified.
        if not receiver:
            receiver = SETTINGS["email.receiver"]

        msg: EmailMessage = EmailMessage()
        msg["From"] = SETTINGS["email.sender"]
        msg["To"] = receiver
        msg["Subject"] = subject
        msg.set_content(content)

        self.queue.put(msg)

    def run(self) -> None:
        """"""
        server: str = SETTINGS["email.server"]
        port: int = SETTINGS["email.port"]
        username: str = SETTINGS["email.username"]
        password: str = SETTINGS["email.password"]

        while self.active:
            try:
                msg: EmailMessage = self.queue.get(block=True, timeout=1)

                try:
                    with smtplib.SMTP_SSL(server, port) as smtp:
                        smtp.login(username, password)
                        smtp.send_message(msg)
                except Exception:
                    log_msg: str = _("邮件发送失败: {}").format(traceback.format_exc())
                    self.main_engine.write_log(log_msg, "EMAIL")
            except Empty:
                pass

    def start(self) -> None:
        """"""
        self.active = True
        self.thread.start()

    def close(self) -> None:
        """"""
        if not self.active:
            return

        self.active = False
        self.thread.join()
