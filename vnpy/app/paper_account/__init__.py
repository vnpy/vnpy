from pathlib import Path

from vnpy.trader.app import BaseApp

from .engine import PaperEngine, APP_NAME


class PaperAccountApp(BaseApp):
    """"""
    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "模拟交易"
    engine_class = PaperEngine
    widget_name = "PaperManager"
    icon_name = "paper.ico"
