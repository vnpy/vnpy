from pathlib import Path
from vnpy.trader.app import BaseApp
from .engine import ScriptEngine, APP_NAME


class ScriptTraderApp(BaseApp):
    """"""
    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "脚本策略"
    engine_class = ScriptEngine
    widget_name = "ScriptManager"
    icon_name = "script.ico"
