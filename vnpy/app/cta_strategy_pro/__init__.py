from pathlib import Path

from vnpy.trader.app import BaseApp
from .base import APP_NAME, StopOrder

from .engine import CtaEngine

from .template import (
    Direction,
    Offset,
    Status,
    TickData,
    BarData,
    TradeData,
    OrderData,
    CtaTemplate, CtaSignal, TargetPosTemplate, CtaProTemplate, CtaProFutureTemplate)  # noqa
from vnpy.trader.utility import BarGenerator, ArrayManager  # noqa

from .template_spread import CtaSpreadTemplate


class CtaStrategyProApp(BaseApp):
    """"""

    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "CTA策略PRO"
    engine_class = CtaEngine
    widget_name = "CtaManager"
    icon_name = "cta.ico"
