from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine

APP_NAME = "PaperAccount"


class PaperEngine(BaseEngine):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

    def process_contract_event(self, event: Event):
        """"""
        pass