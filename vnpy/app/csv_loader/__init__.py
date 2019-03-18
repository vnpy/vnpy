from pathlib import Path

from vnpy.trader.app import BaseApp
from .CsvLoader import CsvLoader
from .base import APP_NAME


class CsvLoaderApp(BaseApp):
    """"""

    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "CSV行情载入器"
    engine_class = CsvLoader
    widget_name = "CsvLoaderWidget"
    icon_name = "cta.ico"
