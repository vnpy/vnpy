from pathlib import Path

from vnpy.trader.app import BaseApp
from .template import SpreadTradingTemplate
from .engine import SpreadEngine
from .base import APP_NAME


class SpreadTradingApp(BaseApp):
    """"""

    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "价差交易"
    engine_class = SpreadEngine
    widget_name = "SpreadManager"
    icon_name = "st.ico"
