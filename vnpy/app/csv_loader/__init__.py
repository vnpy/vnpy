from pathlib import Path

from vnpy.trader.app import BaseApp
from .engine import APP_NAME, CsvLoaderEngine


class CsvLoaderApp(BaseApp):
    """"""

    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "CSV载入"
    engine_class = CsvLoaderEngine
    widget_name = "CsvLoaderWidget"
    icon_name = "csv.ico"
