"""
"""

from vnpy.event import EventEngine, Event

from .event import EVENT_LOG
from .object import LogData, SubscribeRequest, OrderRequest, CancelRequest


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

    def write_log(self, msg: str):
        """
        Put log event with specific message.
        """
        log = LogData(msg=msg)
        event = Event(EVENT_LOG, log)
        self.event_engine.put(event)

    def get_gateway(gateway_name: str):
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
