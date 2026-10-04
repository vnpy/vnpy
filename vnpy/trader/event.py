"""
Event type string used in the trading platform.
"""

from vnpy.event import EVENT_TIMER  # noqa

EVENT_TICK: str = "eTick."
EVENT_TRADE: str = "eTrade."
EVENT_ORDER: str = "eOrder."
EVENT_POSITION: str = "ePosition."
EVENT_ACCOUNT: str = "eAccount."
EVENT_QUOTE: str = "eQuote."
EVENT_CONTRACT: str = "eContract."
EVENT_LOG: str = "eLog"
