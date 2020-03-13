"""
Defines constants and objects used in PortfolioStrategy App.
"""

from enum import Enum


APP_NAME = "PortfolioStrategy"


class EngineType(Enum):
    LIVE = "实盘"
    BACKTESTING = "回测"


EVENT_CTA_LOG = "eCtaLog"
EVENT_CTA_STRATEGY = "eCtaStrategy"
