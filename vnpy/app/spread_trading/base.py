# encoding: UTF-8


APP_NAME = "SpreadStrategy"
EVENT_SPREADTRADING_ADDSPREAD = "eSpreadTradingAddSpread"
EVENT_SPREADTRADING_TICK = "eSpreadTradingTick."
EVENT_SPREADTRADING_POS = "eSpreadTradingPos."
EVENT_SPREADTRADING_LOG = "eSpreadTradingLog"
EVENT_SPREADTRADING_ALGO = "eSpreadTradingAlgo."
EVENT_SPREADTRADING_ALGOLOG = "eSpreadTradingAlgoLog"


########################################################################
class StLeg(object):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.vtSymbol = ""
        self.ratio = 0
        self.multiplier = 0.0
        self.payup = 0

        self.bidPrice = 0.0
        self.askPrice = 0.0
        self.bidVolume = 0
        self.askVolume = 0

        self.longPos = 0
        self.shortPos = 0
        self.netPos = 0
