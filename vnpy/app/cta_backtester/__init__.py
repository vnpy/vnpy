from pathlib import Path

from vnpy.trader.app import BaseApp

from .engine import BacktesterEngine, APP_NAME


class CtaBacktesterApp(BaseApp):
    """"""

    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = "CTA回测"
    engine_class = BacktesterEngine
    widget_name = "BacktesterManager"
    icon_name = "backtester.ico"


def test_cta():
    cta = CtaBacktesterApp
    print("app_name:{}".format(cta.app_name))

# 调试
if __name__ == "__main__":
    test_cta()