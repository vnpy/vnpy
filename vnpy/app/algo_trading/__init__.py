from pathlib import Path

from vnpy.trader.app import BaseApp

from .engine import AlgoEngine, APP_NAME
from .template import AlgoTemplate


class AlgoTradingApp(BaseApp):
    """"""

    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "算法交易"
    engine_class = AlgoEngine
    widget_name = "AlgoManager"
    icon_name = "algo.ico"
