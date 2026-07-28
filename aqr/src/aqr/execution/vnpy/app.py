from pathlib import Path

from vnpy.trader.app import BaseApp

from aqr.execution.vnpy.engine import APP_NAME, AqrExecutionEngine


class AqrExecutionApp(BaseApp):
    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "AQR自动执行"
    engine_class = AqrExecutionEngine
    widget_name = ""
    icon_name = ""
