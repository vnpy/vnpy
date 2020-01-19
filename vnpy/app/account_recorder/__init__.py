# encoding: UTF-8

from pathlib import Path
from vnpy.trader.app import BaseApp

from .engine import AccountRecorder, APP_NAME

class AccountRecorderApp(BaseApp):
    """"""
    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "帐号记录"
    engine_class = AccountRecorder
    widget_name = None
    icon_name = "algo.ico"

