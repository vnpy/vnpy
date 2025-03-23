# encoding: UTF-8
from pathlib import Path

from vnpy.trader.app import BaseApp

# from vnpy_portfoliostrategy.engine import StrategyEngine, APP_NAME
from .gateway_test_strategy import SimpleOrderStrategyEngine

class SimpleOrderStrategyApp(BaseApp):
    """"""
    app_name = 'SimpleOrderStrategyApp'
    # app_module = __module__
    app_module = None
    app_path = Path(__file__).parent
    display_name = "下单策略测试引擎"
    engine_class = SimpleOrderStrategyEngine
    widget_name = "SimpleOrderStrategy"
    # icon_name = "recorder.ico"
