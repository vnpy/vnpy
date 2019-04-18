from datetime import datetime
from dataclasses import dataclass

@dataclass
class StLeg(object):
    """"""
    vt_symbol = ''
    ratio = 0
    multiplier = 0.0
    payup = 0

    bidPrice = 0.0
    askPrice = 0.0
    bidVolume = 0
    askVolume = 0

    longPos = 0
    shortPos = 0
    netPos = 0

########################################################################
class StSpread(object):
    """"""

    """
    Standard Spread
    """

    parameters = ["spread_name",
                  "vt_symbol",
                  "ratio",
                  "multiplier",
                  "payup", ]

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.name = ''
        self.symbol = ''

        self.activeLeg = None
        self.passiveLegs = []
        self.allLegs = []

        self.bidPrice = 0.0
        self.askPrice = 0.0
        self.bidVolume = 0
        self.askVolume = 0
        self.time = ''

        self.longPos = 0
        self.shortPos = 0
        self.netPos = 0

    # ----------------------------------------------------------------------
    def initSpread(self, setting):
        """"""
        result = False
        msg = ''

        #
        self.name = setting['spread_name']
        activeSetting = setting['active_legs']

        activeLeg = StLeg()
        activeLeg.vt_symbol = str(activeSetting['vt_symbol'])
        activeLeg.ratio = float(activeSetting['ratio'])
        activeLeg.multiplier = float(activeSetting['multiplier'])
        activeLeg.payup = int(activeSetting['payup'])
        self.addActiveLeg(activeLeg)

        #
        passiveSettingList = setting['passive_legs']
        passiveLegList = []

        for d in passiveSettingList:
            passiveLeg = StLeg()
            passiveLeg.vt_symbol = str(d['vt_symbol'])
            passiveLeg.ratio = float(d['ratio'])
            passiveLeg.multiplier = float(d['multiplier'])
            passiveLeg.payup = int(d['payup'])

            self.addPassiveLeg(passiveLeg)

        #
        result = True
        msg = '%s价差创建成功' % self.name
        return result, msg

    # ----------------------------------------------------------------------
    def start_spread(self):
        """
        Init spread with active leg
        """
        if not self.activeLeg:
            return

        # all legs list
        self.allLegs.append(self.activeLeg)
        self.allLegs.extend(self.passiveLegs)

        # spread code
        legSymbolList = []

        for leg in self.allLegs:
            if leg.multiplier >= 0:
                legSymbol = '+%s*%s' % (leg.multiplier, leg.vt_symbol)
            else:
                legSymbol = '%s*%s' % (leg.multiplier, leg.vt_symbol)
            legSymbolList.append(legSymbol)

        self.symbol = ''.join(legSymbolList)

    # ----------------------------------------------------------------------
    def calculatePrice(self):
        """"""
        self.bidPrice = 0.0
        self.askPrice = 0.0
        self.askVolume = 0
        self.bidVolume = 0

        for n, leg in enumerate(self.allLegs):
            #
            if leg.multiplier > 0:
                self.bidPrice += leg.bidPrice * leg.multiplier
                self.askPrice += leg.askPrice * leg.multiplier
            else:
                self.bidPrice += leg.askPrice * leg.multiplier
                self.askPrice += leg.bidPrice * leg.multiplier

            #
            if leg.ratio > 0:
                legAdjustedBidVolume = leg.bidVolume / leg.ratio
                legAdjustedAskVolume = leg.askVolume / leg.ratio
            else:
                legAdjustedBidVolume = leg.askVolume / abs(leg.ratio)
                legAdjustedAskVolume = leg.bidVolume / abs(leg.ratio)

            if n == 0:
                self.bidVolume = legAdjustedBidVolume  # init first leg
                self.askVolume = legAdjustedAskVolume
            else:
                self.bidVolume = min(self.bidVolume, legAdjustedBidVolume)
                self.askVolume = min(self.askVolume, legAdjustedAskVolume)

        # update time
        self.time = datetime.now().strftime('%H:%M:%S.%f')[:-3]

    # ----------------------------------------------------------------------
    def calculatePos(self):
        """"""
        #
        self.longPos = 0
        self.shortPos = 0
        self.netPos = 0

        #
        for n, leg in enumerate(self.allLegs):
            if leg.ratio > 0:
                legAdjustedLongPos = leg.longPos / leg.ratio
                legAdjustedShortPos = leg.shortPos / leg.ratio
            else:
                legAdjustedLongPos = leg.shortPos / abs(leg.ratio)
                legAdjustedShortPos = leg.longPos / abs(leg.ratio)

            if n == 0:
                self.longPos = legAdjustedLongPos
                self.shortPos = legAdjustedShortPos
            else:
                self.longPos = min(self.longPos, legAdjustedLongPos)
                self.shortPos = min(self.shortPos, legAdjustedShortPos)

        #
        self.longPos = int(self.longPos)
        self.shortPos = int(self.shortPos)
        self.netPos = self.longPos - self.shortPos

    # ----------------------------------------------------------------------
    def addActiveLeg(self, leg):
        """"""
        self.activeLeg = leg

    # ----------------------------------------------------------------------
    def addPassiveLeg(self, leg):
        """"""
        self.passiveLegs.append(leg)