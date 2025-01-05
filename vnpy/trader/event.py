"""
Event type string used in the trading platform.
"""

from vnpy.event import EVENT_TIMER  # noqa

EVENT_TICK = "eTick."
EVENT_BAR = "eBar."  # hyf
EVENT_TRADE = "eTrade."
EVENT_ORDER = "eOrder."
EVENT_POSITION = "ePosition."
EVENT_ACCOUNT = "eAccount."
EVENT_QUOTE = "eQuote."
EVENT_CONTRACT = "eContract."
EVENT_LOG = "eLog"


# recorder
EVENT_RECORDER_LOG = "eRecorderLog"
EVENT_RECORDER_UPDATE = "eRecorderUpdate"

# factor maker
EVENT_BAR_FACTOR = "eBarFactor."
EVENT_FACTOR = "eFactor."
