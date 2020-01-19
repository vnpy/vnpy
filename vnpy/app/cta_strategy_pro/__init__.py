from pathlib import Path

from vnpy.trader.app import BaseApp
from vnpy.trader.constant import Direction,Offset
from vnpy.trader.object import TickData, BarData, TradeData, OrderData
from vnpy.trader.utility import BarGenerator, ArrayManager

from .base import APP_NAME, StopOrder
from .engine import CtaEngine

from .template import CtaTemplate, CtaSignal, TargetPosTemplate

class CtaStrategyProApp(BaseApp):
    """"""

    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "CTA策略PRO"
    engine_class = CtaEngine
    widget_name = "CtaManager"
    icon_name = "cta.ico"
