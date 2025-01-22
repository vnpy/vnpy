# encoding: UTF-8
from pathlib import Path

from vnpy.trader.app import BaseApp

from .engine import FactorEngine, APP_NAME


class FactorMakerApp(BaseApp):
    """"""
    app_name = APP_NAME
    # app_module = __module__
    app_module = None
    app_path = Path(__file__).parent
    display_name = "因子计算引擎"
    engine_class = FactorEngine
    widget_name = "FactorMaker"
    # icon_name = "recorder.ico"
