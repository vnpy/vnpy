"""
Event type string used in VN Trader.
"""

from vnpy.event import EVENT_TIMER  # noqa

EVENT_TICK = "eTick."
EVENT_TRADE = "eTrade."
EVENT_TRADE_UPDATE = "eTradeUpdate"
EVENT_ORDER = "eOrder."
EVENT_ORDER_UPDATE = "eOrderUpdate"
EVENT_POSITION = "ePosition."
EVENT_ACCOUNT = "eAccount."
EVENT_QUOTE = "eQuote."
EVENT_CONTRACT = "eContract."
EVENT_LOG = "eLog"
EVENT_SNAPSHOT = "eSnapshot."
EVENT_BASKET_COMPONENT = 'eBasketComponent'