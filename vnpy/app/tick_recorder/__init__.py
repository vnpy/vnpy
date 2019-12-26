from pathlib import Path

from vnpy.trader.app import BaseApp
from vnpy.trader.constant import Direction
from vnpy.trader.object import TickData, BarData, TradeData, OrderData
from vnpy.trader.utility import BarGenerator, ArrayManager

from .engine import TickRecorderEngine, APP_NAME

class TickRecorderApp(BaseApp):
    """"""
    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "Tick行情记录"
    engine_class = TickRecorderEngine
    widget_name = "RecorderManager"
    icon_name = "recorder.ico"
