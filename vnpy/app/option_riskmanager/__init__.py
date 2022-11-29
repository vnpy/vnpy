from pathlib import Path

import importlib_metadata
from vnpy.trader.app import BaseApp
from vnpy.trader.object import (
    OrderData,
    TradeData,
    TickData,
    BarData
)

from .engine_rm import (
    MainEngineRm, OptionRiskManagerEngine
)


class OptionRiskApp(BaseApp):
    """"""

    app_name = "OptionRiskApp"
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "价差交易"
    engine_class = OptionRiskManagerEngine
    widget_name = "MainEngineRm"
    icon_name = "spread.ico"
