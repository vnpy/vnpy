""""""
from datetime import datetime
from threading import Thread

from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.constant import Interval
from vnpy.trader.object import HistoryRequest, ContractData
from vnpy.trader.datafeed import datafeed
from vnpy.trader.utility import extract_vt_symbol
from vnpy.trader.database import database_manager


APP_NAME = "ChartWizard"

EVENT_CHART_HISTORY = "eChartHistory"


class ChartWizardEngine(BaseEngine):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        datafeed.init()

    def query_history(
        self,
        vt_symbol: str,
        interval: Interval,
        start: datetime,
        end: datetime
    ) -> None:
        """"""
        thread = Thread(
            target=self._query_history,
            args=[vt_symbol, interval, start, end]
        )
        thread.start()

    def _query_history(
        self,
        vt_symbol: str,
        interval: Interval,
        start: datetime,
        end: datetime
    ) -> None:
        """"""
        symbol, exchange = extract_vt_symbol(vt_symbol)

        req = HistoryRequest(
            symbol=symbol,
            exchange=exchange,
            interval=interval,
            start=start,
            end=end
        )

        contract: ContractData = self.main_engine.get_contract(vt_symbol)
        if contract:
            if contract.history_data:
                data = self.main_engine.query_history(req, contract.gateway_name)
            else:
                data = datafeed.query_bar_history(req)
        else:
            data = database_manager.load_bar_data(
                symbol,
                exchange,
                interval,
                start,
                end
            )

        event = Event(EVENT_CHART_HISTORY, data)
        self.event_engine.put(event)
