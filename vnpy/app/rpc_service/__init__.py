from pathlib import Path
from vnpy.trader.app import BaseApp
from .engine import RpcEngine, APP_NAME


class RpcServiceApp(BaseApp):
    """"""
    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "RPC服务"
    engine_class = RpcEngine
    widget_name = "RpcManager"
    icon_name = "rpc.ico"
