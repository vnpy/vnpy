from pathlib import Path
from vnpy.trader.app import BaseApp
from .engine import RtdEngine, APP_NAME


class ExcelRtdApp(BaseApp):
    """"""
    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "Excel RTD"
    engine_class = RtdEngine
    widget_name = "RtdManager"
    icon_name = "rtd.ico"
