from pathlib import Path

from vnpy.trader.app import BaseApp

from .engine import RadarEngine, APP_NAME


class PaperAccountApp(BaseApp):
    """"""
    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "市场雷达"
    engine_class = RadarEngine
    widget_name = "RadarManager"
    icon_name = "radar.ico"
