"""
Event type string used in the trading platform.
"""

from vnpy.event import EVENT_TIMER  # noqa

EVENT_TICK = "eTick."
EVENT_TRADE = "eTrade."
EVENT_ORDER = "eOrder."
EVENT_POSITION = "ePosition."
EVENT_ACCOUNT = "eAccount."
EVENT_QUOTE = "eQuote."
EVENT_CONTRACT = "eContract."
EVENT_LOG = "eLog"

# ================================= apps =================================
# name rule: EVENT_<APP_NAME>_<ACTION/EVENT_NAME>
# ========================================================================
# data recorder
# EVENT_RECORDER_LOG = "eRecorderLog"  # tell the LogEngine to log the message
EVENT_BAR = "eBar."  # hyf

EVENT_RECORDER_UPDATE = "eRecorderUpdate"  # signal to indicate the recorder has been updated
EVENT_RECORDER_RECORD = "eRecorderRecord"  # signal to trigger the recorder to record data
EVENT_RECORDER_EXCEPTION = "eRecorderException"  # signal to indicate the recorder has an exception

# factor maker. fixme: annotations are not specified
EVENT_BAR_FACTOR = "eBarFactor."
EVENT_FACTOR = "eFactor."

# EVENT_FACTORMAKER_LOG = "eFactorMakerLog"   # tell the LogEngine to log the message
EVENT_FACTORMAKER = "eFactorMaker"