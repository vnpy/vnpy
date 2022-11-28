"""
Event type string used in VN Trader.
所有以 eUnimportant_ 开头的都是非重要事件
"""

EVENT_TIMER = "eTimer"

EVENT_TICK = "eTick."
EVENT_UNIMPORTANT_TICK = "eUnimportant_Tick."            # 非重要tick，如篮子成分股tick

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