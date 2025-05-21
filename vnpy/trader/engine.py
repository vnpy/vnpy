import logging
from logging import Logger, INFO
import smtplib
import os
import traceback
from abc import ABC, abstractmethod
from email.message import EmailMessage
from queue import Empty, Queue
from threading import Thread
from typing import Type, Dict, List, Optional, Union
from itertools import product
from typing import TypeVar
from collections.abc import Callable
from datetime import datetime as Datetime
from pathlib import Path

import requests

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
    Exchange,
    Interval
)
from .setting import SETTINGS
from .utility import get_folder_path, TRADER_DIR, virtual
from .converter import OffsetConverter
from .logger import DEBUG, INFO, WARNING, ERROR, CRITICAL

APP_NAME = 'MainEngine'

EngineType = TypeVar("EngineType", bound="BaseEngine")


# Forward declare class for type hints
class BaseEngine(ABC):
    pass


class MainEngine:
    """
    Acts as the core of the trading platform.
    """

    def __init__(self, event_engine: EventEngine = None) -> None:
        """"""
        if event_engine:
            self.event_engine: EventEngine = event_engine
        else:
            self.event_engine = EventEngine()
        self.event_engine.start()

        self.gateways: Dict[str, BaseGateway] = {}
        self.engines: Dict[str, BaseEngine] = {}
        self.apps: Dict[str, BaseApp] = {}
        self.intervals = SETTINGS.get('gateway.intervals', [])
        self.symbols = SETTINGS.get("gateway.symbols", [])  # hyf
        self.exchanges = SETTINGS.get("gateway.exchanges", [])  # hyf
        self.vt_symbols: list[str] = [f"{s}.{e}" for s, e in product(self.symbols, self.exchanges)]
        self.mode: str = SETTINGS.get('mode', 'LIVE')
        assert self.mode in ['LIVE', 'BACKTEST', 'TEST']

        os.chdir(TRADER_DIR)  # Change working directory
        self.init_engines()  # Initialize function engines

    def add_engine(self, engine_class: type[EngineType]) -> EngineType:
        """
        Add function engine.
        """
        engine: EngineType = engine_class(self, self.event_engine)  # type: ignore
        self.engines[engine.engine_name] = engine
        return engine

    def add_gateway(self, gateway_class: Type[BaseGateway], gateway_name: str = "") -> BaseGateway:
        """
        Add gateway.
        """
        # Use default name if gateway_name not passed
        if not gateway_name:
            gateway_name: str = gateway_class.default_name

        gateway: BaseGateway = gateway_class(self.event_engine, gateway_name)
        self.gateways[gateway_name] = gateway

        # Add gateway supported exchanges into engine
        for exchange in gateway.exchanges:
            if exchange not in self.exchanges:
                self.exchanges.append(exchange)

        return gateway

    def add_app(self, app_class: Type[BaseApp]) -> Union[BaseEngine, Type[BaseEngine], EngineType]:
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
        self.write_log("add log, oms, email engines")
        self.add_engine(LogEngine)

        oms_engine: OmsEngine = self.add_engine(OmsEngine)
        self.get_tick: Callable[[str], TickData] = oms_engine.get_tick
        self.get_order: Callable[[str], OrderData] = oms_engine.get_order
        self.get_trade: Callable[[str], TradeData] = oms_engine.get_trade
        self.get_position: Callable[[str], PositionData] = oms_engine.get_position
        self.get_account: Callable[[str], AccountData] = oms_engine.get_account
        self.get_contract: Callable[[str], ContractData] = oms_engine.get_contract
        self.get_quote: Callable[[str], QuoteData] = oms_engine.get_quote
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
        self.convert_order_request: Callable[
            [OrderRequest, str, bool, bool], list[OrderRequest]] = oms_engine.convert_order_request
        self.get_converter: Callable[[str], OffsetConverter] = oms_engine.get_converter

        email_engine: EmailEngine = self.add_engine(EmailEngine)
        self.send_email: Callable[[str, str, str], None] = email_engine.send_email

        telegram_engine: TelegramEngine = self.add_engine(TelegramEngine)
        self.send_telegram: Callable[[str], None] = telegram_engine.send_msg

    def write_log(self, msg: str, source: str = "", level=INFO) -> None:
        """
        Put log event with specific message.
        """
        log: LogData = LogData(msg=msg, gateway_name=APP_NAME if not source else source, level=level)
        event: Event = Event(EVENT_LOG, log)
        self.event_engine.put(event)

    def get_gateway(self, gateway_name: str) -> BaseGateway:
        """
        Return gateway object by name.
        """
        gateway: BaseGateway = self.gateways.get(gateway_name, None)
        if not gateway:
            self.write_log(f"Cannot find gateway: {gateway_name}")
        return gateway

    def get_engine(self, engine_name: str) -> BaseEngine:
        """
        Return engine object by name.
        """
        engine: BaseEngine = self.engines.get(engine_name, None)
        if not engine:
            self.write_log(f"Cannot find engine: {engine_name}")
        return engine

    def get_default_setting(self, gateway_name: str) -> dict[str, str | bool | int | float] | None:
        """
        Get default setting dict of a specific gateway.
        """
        gateway: BaseGateway = self.get_gateway(gateway_name)
        if gateway:
            return gateway.get_default_setting()
        return None

    def get_all_gateway_names(self) -> List[str]:
        """
        Get all names of gateway added in main engine.
        """
        return list(self.gateways.keys())

    def get_all_apps(self) -> List[BaseApp]:
        """
        Get all app objects.
        """
        return list(self.apps.values())

    def get_all_exchanges(self) -> List[Exchange]:
        """
        Get all exchanges.
        """
        return self.exchanges

    def connect(self, setting: dict, gateway_name: str) -> None:
        """
        Start connection of a specific gateway.
        """
        gateway: BaseGateway = self.get_gateway(gateway_name)
        if gateway:
            gateway.connect(setting)

    def subscribe(self, req: SubscribeRequest, gateway_name: str) -> None:
        """
        Subscribe tick data update of a specific gateway.
        """
        gateway: BaseGateway = self.get_gateway(gateway_name)
        if gateway:
            gateway.subscribe(req)

    def subscribe_all(self, gateway_name: str) -> None:
        """
        Subscribe tick data update of all contracts in a gateway.
        """
        for symbol, exchange, interval in product(self.symbols, self.exchanges, self.intervals):
            req: SubscribeRequest = SubscribeRequest(symbol=symbol, exchange=Exchange(exchange),
                                                     interval=Interval(interval))
            self.subscribe(req, gateway_name)

    def send_order(self, req: OrderRequest, gateway_name: str) -> str:
        """
        Send new order request to a specific gateway.
        """
        gateway: BaseGateway = self.get_gateway(gateway_name)
        if gateway:
            return gateway.send_order(req)
        else:
            return ""

    def cancel_order(self, req: CancelRequest, gateway_name: str) -> None:
        """
        Send cancel order request to a specific gateway.
        """
        gateway: BaseGateway = self.get_gateway(gateway_name)
        if gateway:
            gateway.cancel_order(req)

    def send_quote(self, req: QuoteRequest, gateway_name: str) -> str:
        """
        Send new quote request to a specific gateway.
        """
        gateway: BaseGateway = self.get_gateway(gateway_name)
        if gateway:
            return gateway.send_quote(req)
        else:
            return ""

    def cancel_quote(self, req: CancelRequest, gateway_name: str) -> None:
        """
        Send cancel quote request to a specific gateway.
        """
        gateway: BaseGateway = self.get_gateway(gateway_name)
        if gateway:
            gateway.cancel_quote(req)

    def query_history(self, req: HistoryRequest, gateway_name: str) -> Optional[List[BarData]]:
        """
        Query bar history data from a specific gateway.
        """
        gateway: BaseGateway = self.get_gateway(gateway_name)
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

    def start_data_stream(self):
        for exchange in self.exchanges:
            for ticker in self.tickers:
                vt_symbol = f'{ticker}.{exchange.value}'
                contract: Optional[ContractData] = self.get_contract(vt_symbol)
                if contract:
                    req: SubscribeRequest = SubscribeRequest(symbol=contract.symbol, exchange=contract.exchange)
                    self.subscribe(req, contract.gateway_name)
                else:
                    self.write_log(msg=f"Market data subscription failed, contract {vt_symbol} not found",
                                   source='MainEngine')


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

    @abstractmethod
    def close(self) -> None:
        """"""
        pass

    @virtual
    def write_log(self, msg: str, source: str = "", level=INFO) -> None:
        """
        Put log event with specific message.
        """
        source = source if source else self.engine_name
        self.main_engine.write_log(msg=msg, source=source, level=level)


class LogEngine(BaseEngine):
    """
    Processes log event and output with logging module.
    """

    level_map: dict[int, str] = {
        DEBUG: "DEBUG",
        INFO: "INFO",
        WARNING: "WARNING",
        ERROR: "ERROR",
        CRITICAL: "CRITICAL",
    }

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super(LogEngine, self).__init__(main_engine, event_engine, "log")

        self.active = SETTINGS["log.active"]

        self.level: int = SETTINGS["log.level"]

        self.logger: Logger = logging.getLogger("veighna")
        self.logger.setLevel(self.level)

        self.formatter: logging.Formatter = logging.Formatter(
            '%(asctime)s | %(levelname)-8s | %(message)s'
        )

        self.add_null_handler()

        if SETTINGS["log.console"]:
            self.add_console_handler()

        if SETTINGS["log.file"]:
            self.add_file_handler()

        self.register_event()  # vnpy v4.0.0 update

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
        today_date: str = Datetime.now().strftime("%Y%m%d")
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
        self.register_log(EVENT_LOG)  # vnpy v4.0.0 update

    def register_log(self, event_type: str) -> None:
        """Register log event handler"""
        self.event_engine.register(event_type, self.process_log_event)

    def process_log_event(self, event: Event) -> None:
        """
        Process log event.
        """
        if not self.active:
            return
        log: LogData = event.data
        # level: Union[str,int] = self.level_map.get(log.level, log.level)  # Do not use vnpy v4.0.0 update.
        self.logger.log(log.level, log.msg)  # Do not use vnpy v4.0.0 update.

    def close(self) -> None:
        pass


class OmsEngine(BaseEngine):
    """
    Provides order management system function.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super(OmsEngine, self).__init__(main_engine, event_engine, "oms")

        self.ticks: Dict[str, TickData] = {}
        self.orders: Dict[str, OrderData] = {}
        self.trades: Dict[str, TradeData] = {}
        self.positions: Dict[str, PositionData] = {}
        self.accounts: Dict[str, AccountData] = {}
        self.contracts: Dict[str, ContractData] = {}
        self.quotes: Dict[str, QuoteData] = {}

        self.active_orders: Dict[str, OrderData] = {}
        self.active_quotes: Dict[str, QuoteData] = {}

        self.offset_converters: Dict[str, OffsetConverter] = {}

        # self.add_function()  # vnpy v4.0.0 update. it is moved to initialization of main_engine
        self.register_event()

    # def add_function(self) -> None:
    #     """Add query function to main engine."""
    #     # vnpy v4.0.0 update. it is moved to initialization of main_engine
    #     self.main_engine.get_tick = self.get_tick
    #     self.main_engine.get_order = self.get_order
    #     self.main_engine.get_trade = self.get_trade
    #     self.main_engine.get_position = self.get_position
    #     self.main_engine.get_account = self.get_account
    #     self.main_engine.get_contract = self.get_contract
    #     self.main_engine.get_quote = self.get_quote
    #
    #     self.main_engine.get_all_ticks = self.get_all_ticks
    #     self.main_engine.get_all_orders = self.get_all_orders
    #     self.main_engine.get_all_trades = self.get_all_trades
    #     self.main_engine.get_all_positions = self.get_all_positions
    #     self.main_engine.get_all_accounts = self.get_all_accounts
    #     self.main_engine.get_all_contracts = self.get_all_contracts
    #     self.main_engine.get_all_quotes = self.get_all_quotes
    #     self.main_engine.get_all_active_orders = self.get_all_active_orders
    #     self.main_engine.get_all_active_quotes = self.get_all_active_quotes
    #
    #     self.main_engine.update_order_request = self.update_order_request
    #     self.main_engine.convert_order_request = self.convert_order_request
    #     self.main_engine.get_converter = self.get_converter

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
        converter: OffsetConverter = self.offset_converters.get(order.gateway_name, None)
        if converter:
            converter.update_order(order)

    def process_trade_event(self, event: Event) -> None:
        """"""
        trade: TradeData = event.data
        self.trades[trade.vt_tradeid] = trade

        # Update to offset converter
        converter: OffsetConverter = self.offset_converters.get(trade.gateway_name, None)
        if converter:
            converter.update_trade(trade)

    def process_position_event(self, event: Event) -> None:
        """"""
        position: PositionData = event.data
        self.positions[position.vt_positionid] = position

        # Update to offset converter
        converter: OffsetConverter = self.offset_converters.get(position.gateway_name, None)
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

    def get_tick(self, vt_symbol: str) -> Optional[TickData]:
        """
        Get latest market tick data by vt_symbol.
        """
        return self.ticks.get(vt_symbol, None)

    def get_order(self, vt_orderid: str) -> Optional[OrderData]:
        """
        Get latest order data by vt_orderid.
        """
        return self.orders.get(vt_orderid, None)

    def get_trade(self, vt_tradeid: str) -> Optional[TradeData]:
        """
        Get trade data by vt_tradeid.
        """
        return self.trades.get(vt_tradeid, None)

    def get_position(self, vt_positionid: str) -> Optional[PositionData]:
        """
        Get latest position data by vt_positionid.
        """
        return self.positions.get(vt_positionid, None)

    def get_account(self, vt_accountid: str) -> Optional[AccountData]:
        """
        Get latest account data by vt_accountid.
        """
        return self.accounts.get(vt_accountid, None)

    def get_contract(self, vt_symbol: str) -> Optional[ContractData]:
        """
        Get contract data by vt_symbol.
        """
        return self.contracts.get(vt_symbol, None)

    def get_quote(self, vt_quoteid: str) -> Optional[QuoteData]:
        """
        Get latest quote data by vt_orderid.
        """
        return self.quotes.get(vt_quoteid, None)

    def get_all_ticks(self) -> List[TickData]:
        """
        Get all tick data.
        """
        return list(self.ticks.values())

    def get_all_orders(self) -> List[OrderData]:
        """
        Get all order data.
        """
        return list(self.orders.values())

    def get_all_trades(self) -> List[TradeData]:
        """
        Get all trade data.
        """
        return list(self.trades.values())

    def get_all_positions(self) -> List[PositionData]:
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

    def get_all_active_orders(self, vt_symbol: str = "") -> List[OrderData]:
        """
        Get all active orders by vt_symbol.

        If vt_symbol is empty, return all active orders.
        """
        if not vt_symbol:
            return list(self.active_orders.values())
        else:
            active_orders: List[OrderData] = [
                order
                for order in self.active_orders.values()
                if order.vt_symbol == vt_symbol
            ]
            return active_orders

    def get_all_active_quotes(self, vt_symbol: str = "") -> List[QuoteData]:
        """
        Get all active quotes by vt_symbol.
        If vt_symbol is empty, return all active qutoes.
        """
        if not vt_symbol:
            return list(self.active_quotes.values())
        else:
            active_quotes: List[QuoteData] = [
                quote
                for quote in self.active_quotes.values()
                if quote.vt_symbol == vt_symbol
            ]
            return active_quotes

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

    def close(self) -> None:
        pass


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

        # self.main_engine.send_email = self.send_email  # vnpy v4.0.0 update. it is moved to initialization of main_engine

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
                    log_msg: str = f"Email sending failed: {traceback.format_exc()}"
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


class TelegramEngine(BaseEngine):
    """Telegram message sending engine"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        super().__init__(main_engine, event_engine, "telegram")

        self.active: bool = SETTINGS.get("telegram.active", False)
        self.token: str = SETTINGS.get("telegram.token", "")
        self.chat: str = SETTINGS.get("telegram.chat", "")
        self.url: str = f"https://api.telegram.org/bot{self.token}/sendMessage"
        # refer to telegram_tutorial.md
        self.proxies: dict[str, str] = {}
        proxy: str = SETTINGS.get("telegram.proxy", "")
        if proxy:
            self.proxies["http"] = proxy
            self.proxies["https"] = proxy

        self.thread: Thread = Thread(target=self.run, daemon=True)
        self.queue: Queue = Queue()

        if self.active:
            self.register_event()
            self.thread.start()

    def register_event(self) -> None:
        """Register event handler"""
        self.event_engine.register(EVENT_LOG, self.process_log_event)

    def process_log_event(self, event: Event) -> None:
        """Process log event"""
        log: LogData = event.data

        msg = f"{log.time}\t[{log.gateway_name}] {log.msg}"
        self.queue.put(msg)

    def close(self) -> None:
        """Stop task thread"""
        if not self.active:
            return

        self.active = False
        self.thread.join()

    def run(self) -> None:
        """Task thread loop"""
        while self.active:
            try:
                msg: str = self.queue.get(block=True, timeout=1)
                self.send_msg(msg)
            except Empty:
                pass

    def send_msg(self, msg: str) -> dict:
        """Sending message"""
        data: dict = {
            "chat_id": self.chat,
            "text": msg
        }

        # Send request
        try:
            r: requests.Response = requests.post(self.url, data=data)
            return r.json()
        except Exception:
            return None
