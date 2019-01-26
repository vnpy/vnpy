from pathlib import Path

from vnpy.trader.app import BaseApp
from .engine import CtaEngine
from .template import CtaTemplate
from .base import APP_NAME


class CtaStrategyApp(BaseApp):
    """"""

    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "CTA策略"
    engine_class = CtaEngine
    widget_name = "CtaManager"
    icon_name = "cta.ico"
