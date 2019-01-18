from pathlib import Path

from vnpy.trader.app import BaseApp
from .cta_engine import CtaEngine


class CtaStrategyApp(BaseApp):
    """"""
    app_name = "CtaStrategy"
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "CTA策略"
    engine_class = CtaEngine
    widget_name = "CtaManager"
    icon_name = "cta.ico"