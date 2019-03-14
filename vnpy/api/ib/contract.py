"""
Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable.
"""


"""
	SAME_POS    = open/close leg value is same as combo
	OPEN_POS    = open
	CLOSE_POS   = close
	UNKNOWN_POS = unknown
"""


from ibapi.object_implem import Object


(SAME_POS, OPEN_POS, CLOSE_POS, UNKNOWN_POS) = range(4)


class ComboLeg(Object):
    def __init__(self):
        self.conId = 0  # type: int
        self.ratio = 0  # type: int
        self.action = ""      # BUY/SELL/SSHORT
        self.exchange = ""
        self.openClose = 0   # type: int; LegOpenClose enum values
        # for stock legs when doing short sale
        self.shortSaleSlot = 0
        self.designatedLocation = ""
        self.exemptCode = -1


    def __str__(self):
        return ",".join((
            str(self.conId),
            str(self.ratio),
            str(self.action),
            str(self.exchange),
            str(self.openClose),
            str(self.shortSaleSlot),
            str(self.designatedLocation),
            str(self.exemptCode)))


class DeltaNeutralContract(Object):
    def __init__(self):
        self.conId = 0   # type: int
        self.delta = 0.  # type: float
        self.price = 0.  # type: float

    def __str__(self):
        return ",".join((
            str(self.conId),
            str(self.delta),
            str(self.price)))


class Contract(Object):
    def __init__(self):
        self.conId = 0
        self.symbol = ""
        self.secType = ""
        self.lastTradeDateOrContractMonth = ""
        self.strike = 0.  # float !!
        self.right = ""
        self.multiplier = ""
        self.exchange = ""
        self.primaryExchange = "" # pick an actual (ie non-aggregate) exchange that the contract trades on.  DO NOT SET TO SMART.
        self.currency = ""
        self.localSymbol = ""
        self.tradingClass = ""
        self.includeExpired = False
        self.secIdType = ""	  # CUSIP;SEDOL;ISIN;RIC
        self.secId = ""

        #combos
        self.comboLegsDescrip = ""  # type: str; received in open order 14 and up for all combos
        self.comboLegs = None     # type: list<ComboLeg>
        self.deltaNeutralContract = None


    def __str__(self):
        s = ",".join((
            str(self.conId),
            str(self.symbol),
            str(self.secType),
            str(self.lastTradeDateOrContractMonth),
            str(self.strike),
            str(self.right),
            str(self.multiplier),
            str(self.exchange),
            str(self.primaryExchange),
            str(self.currency),
            str(self.localSymbol),
            str(self.tradingClass),
            str(self.includeExpired),
            str(self.secIdType),
            str(self.secId)))
        s += "combo:" + self.comboLegsDescrip

        if self.comboLegs:
            for leg in self.comboLegs:
                s += ";" + str(leg)

        if self.deltaNeutralContract:
            s += ";" + str(self.deltaNeutralContract)

        return s


class ContractDetails(Object):
    def __init__(self):
        self.contract = Contract()
        self.marketName = ""
        self.minTick = 0.
        self.orderTypes = ""
        self.validExchanges = ""
        self.priceMagnifier = 0
        self.underConId = 0
        self.longName = ""
        self.contractMonth = ""
        self.industry = ""
        self.category = ""
        self.subcategory = ""
        self.timeZoneId = ""
        self.tradingHours = ""
        self.liquidHours = ""
        self.evRule = ""
        self.evMultiplier = 0
        self.mdSizeMultiplier = 0
        self.aggGroup = 0
        self.underSymbol = ""
        self.underSecType = ""
        self.marketRuleIds = ""
        self.secIdList = None
        self.realExpirationDate = ""
        self.lastTradeTime = ""
        # BOND values
        self.cusip = ""
        self.ratings = ""
        self.descAppend = ""
        self.bondType = ""
        self.couponType = ""
        self.callable = False
        self.putable = False
        self.coupon = 0
        self.convertible = False
        self.maturity = ""
        self.issueDate = ""
        self.nextOptionDate = ""
        self.nextOptionType = ""
        self.nextOptionPartial = False
        self.notes = ""

    def __str__(self):
        s = ",".join((
            str(self.contract),
            str(self.marketName),
            str(self.minTick),
            str(self.orderTypes),
            str(self.validExchanges),
            str(self.priceMagnifier),
            str(self.underConId),
            str(self.longName),
            str(self.contractMonth),
            str(self.industry),
            str(self.category),
            str(self.subcategory),
            str(self.timeZoneId),
            str(self.tradingHours),
            str(self.liquidHours),
            str(self.evRule),
            str(self.evMultiplier),
            str(self.mdSizeMultiplier),
            str(self.underSymbol),
            str(self.underSecType),
            str(self.marketRuleIds),
            str(self.aggGroup),
            str(self.secIdList),
            str(self.realExpirationDate),
            str(self.cusip),
            str(self.ratings),
            str(self.descAppend),
            str(self.bondType),
            str(self.couponType),
            str(self.callable),
            str(self.putable),
            str(self.coupon),
            str(self.convertible),
            str(self.maturity),
            str(self.issueDate),
            str(self.nextOptionDate),
            str(self.nextOptionType),
            str(self.nextOptionPartial),
            str(self.notes)))
        return s


class ContractDescription(Object):
    def __init__(self):
        self.contract = Contract()
        self.derivativeSecTypes = None   # type: list of strings


