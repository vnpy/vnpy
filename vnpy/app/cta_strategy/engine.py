""""""

from vnpy.event import EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine


class CtaEngine(BaseEngine):

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        super(CtaEngine,
              self).__init__(main_engine,
                             event_engine,
                             "CtaStrategy")
