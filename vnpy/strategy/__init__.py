from pathlib import Path

from vnpy.trader.app import BaseApp
from .base import APP_NAME, StopOrder
from .engine import StrategyEngine
from .template import StrategyTemplate


class PortfolioStrategyApp(BaseApp):
    """
    VN Trader Portfolio Strategy App.
    Defines app metadata and main engine class for portfolio strategy functionality.
    """
    app_name = APP_NAME
    app_module = None
    app_path = Path(__file__).parent
    display_name = "PortfolioStrategy"
    engine_class = StrategyEngine
    widget_name = "PortfolioManager"
    icon_name = "portfolio.ico"