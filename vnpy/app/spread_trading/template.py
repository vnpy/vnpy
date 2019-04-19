# encoding: UTF-8


########################################################################
class SpreadTradingTemplate(object):
    """"""

    MODE_LONGSHORT = "双向"
    MODE_LONGONLY = "做多"
    MODE_SHORTONLY = "做空"

    SPREAD_LONG = 1
    SPREAD_SHORT = 2

    # ----------------------------------------------------------------------

    def __init__(self, algoEngine, spread):
        """"""
        self.algoEngine = algoEngine
        self.spread_name = spread.name
        self.spread = spread

        self.algoName = ""

        self.active = False  # algo status
        self.mode = self.MODE_LONGSHORT  # algo mode

        self.buyPrice = 0.0
        self.sellPrice = 0.0
        self.shortPrice = 0.0
        self.coverPrice = 0.0

        self.maxPosSize = 0
        self.maxOrderSize = 0

    # ----------------------------------------------------------------------
    def updateSpreadTick(self, spread):
        """"""
        raise NotImplementedError

    # ----------------------------------------------------------------------
    def updateSpreadPos(self, spread):
        """"""
        raise NotImplementedError

    # ----------------------------------------------------------------------
    def updateTrade(self, trade):
        """"""
        raise NotImplementedError

    # ----------------------------------------------------------------------
    def updateOrder(self, order):
        """"""
        raise NotImplementedError

    # ----------------------------------------------------------------------
    def updateTimer(self):
        """"""
        raise NotImplementedError

    # ----------------------------------------------------------------------
    def start(self):
        """"""
        raise NotImplementedError

    # ----------------------------------------------------------------------
    def stop(self):
        """"""
        raise NotImplementedError

    # ----------------------------------------------------------------------
    def setBuyPrice(self, buyPrice):
        """"""
        self.buyPrice = buyPrice

    # ----------------------------------------------------------------------
    def setSellPrice(self, sellPrice):
        """"""
        self.sellPrice = sellPrice

    # ----------------------------------------------------------------------
    def setShortPrice(self, shortPrice):
        """"""
        self.shortPrice = shortPrice

    # ----------------------------------------------------------------------
    def setCoverPrice(self, coverPrice):
        """"""
        self.coverPrice = coverPrice

    # ----------------------------------------------------------------------
    def setMode(self, mode):
        """"""
        self.mode = mode

    # ----------------------------------------------------------------------
    def setMaxOrderSize(self, maxOrderSize):
        """"""
        self.maxOrderSize = maxOrderSize

    # ----------------------------------------------------------------------
    def setMaxPosSize(self, maxPosSize):
        """"""
        self.maxPosSize = maxPosSize

    # ----------------------------------------------------------------------
    def putEvent(self):
        """"""
        self.algoEngine.putAlgoEvent(self)

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """"""
        prefix = "  ".join([self.spread_name, self.algo_name])
        content = ":".join([prefix, content])
        self.algoEngine.write_Log(content)

    # ----------------------------------------------------------------------
    def getAlgoParams(self):
        """"""
        d = {
            "spread_name": self.spread_name,
            "algo_name": self.algo_name,
            "Params": {
                "buyPrice": self.buyPrice,
                "sellPrice": self.sellPrice,
                "shortPrice": self.shortPrice,
                "coverPrice": self.coverPrice,
                "maxOrderSize": self.maxOrderSize,
                "maxPosSize": self.maxPosSize,
                "mode": self.mode,
            },
        }
        return d

    # ----------------------------------------------------------------------
    def setAlgoParams(self, d):
        """"""
        self.Parmas = d.get("Params", None)
        if self.Parmas:
            self.buyPrice = self.Parmas.get("buyPrice", 0.0)
            self.sellPrice = self.Parmas.get("sellPrice", 0.0)
            self.shortPrice = self.Parmas.get("shortPrice", 0.0)
            self.coverPrice = self.Parmas.get("coverPrice", 0.0)
            self.maxOrderSize = self.Parmas.get("maxOrderSize", 0)
            self.maxPosSize = self.Parmas.get("maxPosSize", 0)
            self.mode = self.Parmas.get("mode", self.MODE_LONGSHORT)
