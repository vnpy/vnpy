from enum import Enum

APP_NAME = "PortfolioStrategy"


class EngineType(Enum):
    LIVE = "LIVE"
    BACKTESTING = "BACKTESTING"


EVENT_PORTFOLIO_LOG = "ePortfolioLog"
EVENT_PORTFOLIO_STRATEGY = "ePortfolioStrategy"
