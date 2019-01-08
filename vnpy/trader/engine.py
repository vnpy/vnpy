"""
"""

import logging
from datetime import datetime

from vnpy.event import EventEngine, Event

from .event import EVENT_LOG
from .object import LogData, SubscribeRequest, OrderRequest, CancelRequest
from .utility import Singleton, get_temp_path
from .setting import SETTINGS

class MainEngine:
    """
    Acts as the core of VN Trader.
    """

    def __init__(self, event_engine: EventEngine = None):
        """"""
        if event_engine:
            self.event_engine = event_engine
        else:
            self.event_engine = EventEngine()
        self.event_engine.start()

        self.gateways = {}
        self.apps = {}

        self.log_engine = LogEngine(self, self.event_engine)

    def write_log(self, msg: str):
        """
        Put log event with specific message.
        """
        log = LogData(msg=msg)
        event = Event(EVENT_LOG, log)
        self.event_engine.put(event)

    def get_gateway(self, gateway_name: str):
        """
        Return gateway object by name.
        """
        gateway = self.gateways.get(gateway_name, None)
        if not gateway:
            self.write_log(f"找不到底层接口：{gateway_name}")
        return gateway

    def connect(self, gateway_name: str):
        """
        Start connection of a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        if gateway:
            gateway.connect()

    def subscribe(self, req: SubscribeRequest, gateway_name: str):
        """
        Subscribe tick data update of a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        if gateway:
            gateway.subscribe(req)

    def send_order(self, req: OrderRequest, gateway_name: str):
        """
        Send new order request to a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        if gateway:
            gateway.send_order(req)

    def cancel_order(self, req: CancelRequest, gateway_name: str):
        """
        Send cancel order request to a specific gateway.
        """
        gateway = self.get_gateway(gateway_name)
        if gateway:
            gateway.send_order(req)

    def close(self):
        """
        Make sure every gateway and app is closed properly before
        programme exit.
        """
        for gateway in self.gateways.values():
            gateway.close()

        self.event_engine.stop()


class LogEngine:
    """
    Process log event and output with logging module.
    """

    __metaclass__ = Singleton

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        self.main_engine = main_engine
        self.event_engine = event_engine

        if not SETTINGS["log.active"]:
            return

        self.level = SETTINGS["log.level"]
        self.logger = logging.getLogger("VN Trader")
        self.formatter = logging.Formatter("%(asctime)s  %(levelname)s: %(message)s")
        
        self.add_null_handler()

        if SETTINGS["log.console"]:
            self.add_console_handler()
        
        if SETTINGS["log.file"]:
            self.add_file_handler()

        self.register_event()

    def add_null_handler(self):
        """
        Add null handler for logger.
        """
        null_handler = logging.NullHandler()
        self.logger.addHandler(null_handler)
    
    def add_console_handler(self):
        """
        Add console output of log.
        """
        console_handler = logging.StreamHandler()
        console_handler.setLevel(self.level)
        console_handler.setFormatter(self.formatter)
        self.logger.addHandler(console_handler)
    
    def add_file_handler(self):
        """
        Add file output of log. 
        """
        today_date = datetime.now().strftime("%Y%m%d")
        filename = f"vt_{today_date}.log"
        file_path = get_temp_path(filename)

        file_handler = logging.FileHandler(file_path, mode='w', encoding='utf8')
        file_handler.setLevel(self.level)
        file_handler.setFormatter(self.formatter)
        self.logger.StreamHandler(file_handler)

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_LOG, self.process_log_event)

    def process_log_event(self, event: Event):
        """"""
        log = event.data
        self.logger.log(log.level, log.msg)