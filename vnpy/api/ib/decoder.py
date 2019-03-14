"""
Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable.
"""

"""
The Decoder knows how to transform a message's payload into higher level
IB message (eg: order info, mkt data, etc).
It will call the corresponding method from the EWrapper so that customer's code
(eg: class derived from EWrapper) can make further use of the data.
"""

import logging

from ibapi import order_condition
from ibapi.message import IN
from ibapi.wrapper import * # @UnusedWildImport
from ibapi.order import OrderComboLeg
from ibapi.contract import ContractDescription
from ibapi.contract import ComboLeg
from ibapi.server_versions import * # @UnusedWildImport
from ibapi.utils import * # @UnusedWildImport
from ibapi.softdollartier import SoftDollarTier
from ibapi.ticktype import * # @UnusedWildImport
from ibapi.tag_value import TagValue
from ibapi.scanner import ScanData
from ibapi.errors import BAD_MESSAGE
from ibapi.common import * # @UnusedWildImport


logger = logging.getLogger(__name__)


class HandleInfo(Object):
    def __init__(self, wrap=None, proc=None):
        self.wrapperMeth = wrap
        self.wrapperParams = None
        self.processMeth = proc
        if wrap is None and proc is None:
            raise ValueError("both wrap and proc can't be None")

    def __str__(self):
        s = "wrap:%s meth:%s prms:%s" % (self.wrapperMeth,
                self.processMeth, self.wrapperParams)
        return s


class Decoder(Object):
    def __init__(self, wrapper, serverVersion):
        self.wrapper = wrapper
        self.serverVersion = serverVersion
        self.discoverParams()
        #self.printParams()


    def processTickPriceMsg(self, fields):
        next(fields)
        decode(int, fields)

        reqId = decode(int, fields)
        tickType = decode(int, fields)
        price = decode(float, fields)
        size = decode(int, fields) # ver 2 field
        attrMask = decode(int, fields) # ver 3 field

        attrib = TickAttrib()

        attrib.canAutoExecute = attrMask == 1

        if self.serverVersion >= MIN_SERVER_VER_PAST_LIMIT:
            attrib.canAutoExecute = attrMask & 1 != 0
            attrib.pastLimit = attrMask & 2 != 0
            if self.serverVersion >= MIN_SERVER_VER_PRE_OPEN_BID_ASK:
                attrib.preOpen = attrMask & 4 != 0

        self.wrapper.tickPrice(reqId, tickType, price, attrib)

        # process ver 2 fields
        sizeTickType = TickTypeEnum.NOT_SET
        if TickTypeEnum.BID == tickType:
            sizeTickType = TickTypeEnum.BID_SIZE
        elif TickTypeEnum.ASK == tickType:
            sizeTickType = TickTypeEnum.ASK_SIZE
        elif TickTypeEnum.LAST == tickType:
            sizeTickType = TickTypeEnum.LAST_SIZE
        elif TickTypeEnum.DELAYED_BID == tickType:
            sizeTickType = TickTypeEnum.DELAYED_BID_SIZE
        elif TickTypeEnum.DELAYED_ASK == tickType:
            sizeTickType = TickTypeEnum.DELAYED_ASK_SIZE
        elif TickTypeEnum.DELAYED_LAST == tickType:
            sizeTickType = TickTypeEnum.DELAYED_LAST_SIZE

        if sizeTickType != TickTypeEnum.NOT_SET:
            self.wrapper.tickSize(reqId, sizeTickType, size)


    def processOrderStatusMsg(self, fields):

        next(fields)
        if self.serverVersion < MIN_SERVER_VER_MARKET_CAP_PRICE:
            decode(int, fields)
        orderId = decode(int, fields)
        status = decode(str, fields)

        if self.serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS:
            filled = decode(float, fields)
        else:
            filled = decode(int, fields)

        if self.serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS:
            remaining = decode(float, fields)
        else:
            remaining = decode(int, fields)

        avgFillPrice = decode(float, fields)

        permId = decode(int, fields) # ver 2 field
        parentId = decode(int, fields) # ver 3 field
        lastFillPrice = decode(float, fields) # ver 4 field
        clientId = decode(int, fields) # ver 5 field
        whyHeld = decode(str, fields) # ver 6 field

        if self.serverVersion >= MIN_SERVER_VER_MARKET_CAP_PRICE:
            mktCapPrice = decode(float, fields)
        else:
            mktCapPrice = None

        self.wrapper.orderStatus(orderId, status, filled, remaining,
            avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld, mktCapPrice)


    def processOpenOrder(self, fields):

        next(fields)

        if self.serverVersion < MIN_SERVER_VER_ORDER_CONTAINER:
            version = decode(int, fields)
        else:
            version = self.serverVersion

        order = Order()
        order.orderId = decode(int, fields)

        contract = Contract()

        contract.conId = decode(int, fields) # ver 17 field
        contract.symbol = decode(str, fields)
        contract.secType = decode(str, fields)
        contract.lastTradeDateOrContractMonth = decode(str, fields)
        contract.strike = decode(float, fields)
        contract.right = decode(str, fields)
        if version >= 32:
            contract.multiplier = decode(str, fields)
        contract.exchange = decode(str, fields)
        contract.currency = decode(str, fields)
        contract.localSymbol = decode(str, fields)  # ver 2 field
        if version >= 32:
            contract.tradingClass = decode(str, fields)

        # read order fields
        order.action = decode(str, fields)

        if self.serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS:
            order.totalQuantity = decode(float, fields)
        else:
            order.totalQuantity = decode(int, fields)

        order.orderType = decode(str, fields)
        if version < 29:
            order.lmtPrice = decode(float, fields)
        else:
            order.lmtPrice = decode(float, fields, SHOW_UNSET)
        if version < 30:
            order.auxPrice = decode(float, fields)
        else:
            order.auxPrice = decode(float, fields, SHOW_UNSET)
        order.tif = decode(str, fields)
        order.ocaGroup = decode(str, fields)
        order.account = decode(str, fields)
        order.openClose = decode(str, fields)

        order.origin = decode(int, fields)

        order.orderRef = decode(str, fields)
        order.clientId = decode(int, fields) # ver 3 field
        order.permId = decode(int, fields)   # ver 4 field

        order.outsideRth = decode(bool, fields) # ver 18 field
        order.hidden = decode(bool, fields) # ver 4 field
        order.discretionaryAmt = decode(float, fields) # ver 4 field
        order.goodAfterTime = decode(str, fields) # ver 5 field

        _sharesAllocation = decode(str, fields) # deprecated ver 6 field

        order.faGroup = decode(str, fields) # ver 7 field
        order.faMethod = decode(str, fields) # ver 7 field
        order.faPercentage = decode(str, fields) # ver 7 field
        order.faProfile = decode(str, fields) # ver 7 field

        if self.serverVersion >= MIN_SERVER_VER_MODELS_SUPPORT:
            order.modelCode = decode(str, fields)

        order.goodTillDate = decode(str, fields) # ver 8 field

        order.rule80A = decode(str, fields) # ver 9 field
        order.percentOffset = decode(float, fields, SHOW_UNSET) # ver 9 field
        order.settlingFirm = decode(str, fields) # ver 9 field
        order.shortSaleSlot = decode(int, fields) # ver 9 field
        order.designatedLocation = decode(str, fields) # ver 9 field
        if self.serverVersion == MIN_SERVER_VER_SSHORTX_OLD:
            decode(int, fields)
        elif version >= 23:
            order.exemptCode = decode(int, fields)
        order.auctionStrategy = decode(int, fields) # ver 9 field
        order.startingPrice = decode(float, fields, SHOW_UNSET) # ver 9 field
        order.stockRefPrice = decode(float, fields, SHOW_UNSET) # ver 9 field
        order.delta = decode(float, fields, SHOW_UNSET) # ver 9 field
        order.stockRangeLower = decode(float, fields, SHOW_UNSET) # ver 9 field
        order.stockRangeUpper = decode(float, fields, SHOW_UNSET) # ver 9 field
        order.displaySize = decode(int, fields) # ver 9 field

        #if( version < 18) {
        #		# will never happen
        #		/* order.rthOnly = */ readBoolFromInt()
        #}

        order.blockOrder = decode(bool, fields) # ver 9 field
        order.sweepToFill = decode(bool, fields) # ver 9 field
        order.allOrNone = decode(bool, fields) # ver 9 field
        order.minQty = decode(int, fields, SHOW_UNSET) # ver 9 field
        order.ocaType = decode(int, fields) # ver 9 field
        order.eTradeOnly = decode(bool, fields) # ver 9 field
        order.firmQuoteOnly = decode(bool, fields) # ver 9 field
        order.nbboPriceCap = decode(float, fields, SHOW_UNSET) # ver 9 field

        order.parentId = decode(int, fields) # ver 10 field
        order.triggerMethod = decode(int, fields) # ver 10 field

        order.volatility = decode(float, fields, SHOW_UNSET) # ver 11 field
        order.volatilityType = decode(int, fields) # ver 11 field
        order.deltaNeutralOrderType = decode(str, fields) # ver 11 field (had a hack for ver 11)
        order.deltaNeutralAuxPrice = decode(float, fields, SHOW_UNSET) # ver 12 field

        if version >= 27 and order.deltaNeutralOrderType:
            order.deltaNeutralConId = decode(int, fields)
            order.deltaNeutralSettlingFirm = decode(str, fields)
            order.deltaNeutralClearingAccount = decode(str, fields)
            order.deltaNeutralClearingIntent = decode(str, fields)

        if version >= 31 and order.deltaNeutralOrderType:
            order.deltaNeutralOpenClose = decode(str, fields)
            order.deltaNeutralShortSale = decode(bool, fields)
            order.deltaNeutralShortSaleSlot = decode(int, fields)
            order.deltaNeutralDesignatedLocation = decode(str, fields)

        order.continuousUpdate = decode(bool, fields) # ver 11 field

        # will never happen
        #if( self.serverVersion == 26) {
        #	order.stockRangeLower = readDouble()
        #	order.stockRangeUpper = readDouble()
        #}

        order.referencePriceType = decode(int, fields) # ver 11 field

        order.trailStopPrice = decode(float, fields, SHOW_UNSET) # ver 13 field

        if version >= 30:
            order.trailingPercent = decode(float, fields, SHOW_UNSET)

        order.basisPoints = decode(float, fields, SHOW_UNSET) # ver 14 field
        order.basisPointsType = decode(int, fields, SHOW_UNSET) # ver 14 field
        contract.comboLegsDescrip = decode(str, fields) # ver 14 field

        if version >= 29:
            comboLegsCount = decode(int, fields)

            if comboLegsCount > 0:
                contract.comboLegs = []
                for _ in range(comboLegsCount):
                    comboLeg = ComboLeg()
                    comboLeg.conId = decode(int, fields)
                    comboLeg.ratio = decode(int, fields)
                    comboLeg.action = decode(str, fields)
                    comboLeg.exchange = decode(str, fields)
                    comboLeg.openClose = decode(int, fields)
                    comboLeg.shortSaleSlot = decode(int, fields)
                    comboLeg.designatedLocation = decode(str, fields)
                    comboLeg.exemptCode = decode(int, fields)
                    contract.comboLegs.append(comboLeg)

            orderComboLegsCount = decode(int, fields)
            if orderComboLegsCount > 0:
                order.orderComboLegs = []
                for _ in range(orderComboLegsCount):
                    orderComboLeg = OrderComboLeg()
                    orderComboLeg.price = decode(float, fields, SHOW_UNSET)
                    order.orderComboLegs.append(orderComboLeg)

        if version >= 26:
            smartComboRoutingParamsCount = decode(int, fields)
            if smartComboRoutingParamsCount > 0:
                order.smartComboRoutingParams = []
                for _ in range(smartComboRoutingParamsCount):
                    tagValue = TagValue()
                    tagValue.tag = decode(str, fields)
                    tagValue.value = decode(str, fields)
                    order.smartComboRoutingParams.append(tagValue)

        if version >= 20:
            order.scaleInitLevelSize = decode(int, fields, SHOW_UNSET)
            order.scaleSubsLevelSize = decode(int, fields, SHOW_UNSET)
        else:
            # ver 15 fields
            order.notSuppScaleNumComponents = decode(int, fields, SHOW_UNSET)
            order.scaleInitLevelSize = decode(int, fields, SHOW_UNSET) # scaleComponectSize

        order.scalePriceIncrement = decode(float, fields, SHOW_UNSET) # ver 15 field

        if version >= 28 and order.scalePriceIncrement != UNSET_DOUBLE \
                and order.scalePriceIncrement > 0.0:
            order.scalePriceAdjustValue = decode(float, fields, SHOW_UNSET)
            order.scalePriceAdjustInterval = decode(int, fields, SHOW_UNSET)
            order.scaleProfitOffset = decode(float, fields, SHOW_UNSET)
            order.scaleAutoReset = decode(bool, fields)
            order.scaleInitPosition = decode(int, fields, SHOW_UNSET)
            order.scaleInitFillQty = decode(int, fields, SHOW_UNSET)
            order.scaleRandomPercent = decode(bool, fields)

        if version >= 24:
            order.hedgeType = decode(str, fields)
            if order.hedgeType:
                order.hedgeParam = decode(str, fields)

        if version >= 25:
            order.optOutSmartRouting = decode(bool, fields)

        order.clearingAccount = decode(str, fields) # ver 19 field
        order.clearingIntent = decode(str, fields) # ver 19 field

        if version >= 22:
            order.notHeld = decode(bool, fields)

        if version >= 20:
            deltaNeutralContractPresent = decode(bool, fields)
            if deltaNeutralContractPresent:
                contract.deltaNeutralContract = DeltaNeutralContract()
                contract.deltaNeutralContract.conId = decode(int, fields)
                contract.deltaNeutralContract.delta = decode(float, fields)
                contract.deltaNeutralContract.price = decode(float, fields)

        if version >= 21:
            order.algoStrategy = decode(str, fields)
            if order.algoStrategy:
                algoParamsCount = decode(int, fields)
                if algoParamsCount > 0:
                    order.algoParams = []
                    for _ in range(algoParamsCount):
                        tagValue = TagValue()
                        tagValue.tag = decode(str, fields)
                        tagValue.value = decode(str, fields)
                        order.algoParams.append(tagValue)

        if version >= 33:
            order.solicited = decode(bool, fields)

        orderState = OrderState()

        order.whatIf = decode(bool, fields) # ver 16 field

        orderState.status = decode(str, fields) # ver 16 field
        if self.serverVersion >= MIN_SERVER_VER_WHAT_IF_EXT_FIELDS:
            orderState.initMarginBefore = decode(str, fields)
            orderState.maintMarginBefore = decode(str, fields)
            orderState.equityWithLoanBefore = decode(str, fields)
            orderState.initMarginChange = decode(str, fields)
            orderState.maintMarginChange = decode(str, fields)
            orderState.equityWithLoanChange = decode(str, fields)

        orderState.initMarginAfter = decode(str, fields) # ver 16 field
        orderState.maintMarginAfter = decode(str, fields) # ver 16 field
        orderState.equityWithLoanAfter = decode(str, fields) # ver 16 field

        orderState.commission = decode(float, fields, SHOW_UNSET) # ver 16 field
        orderState.minCommission = decode(float, fields, SHOW_UNSET) # ver 16 field
        orderState.maxCommission = decode(float, fields, SHOW_UNSET) # ver 16 field
        orderState.commissionCurrency = decode(str, fields) # ver 16 field
        orderState.warningText = decode(str, fields) # ver 16 field

        if version >= 34:
            order.randomizeSize = decode(bool, fields)
            order.randomizePrice = decode(bool, fields)

        if self.serverVersion >= MIN_SERVER_VER_PEGGED_TO_BENCHMARK:
            if order.orderType == "PEG BENCH":
                order.referenceContractId = decode(int, fields)
                order.isPeggedChangeAmountDecrease = decode(bool, fields)
                order.peggedChangeAmount = decode(float, fields)
                order.referenceChangeAmount = decode(float, fields)
                order.referenceExchangeId = decode(str, fields)

            conditionsSize = decode(int, fields)
            if conditionsSize > 0:
                order.conditions = []
                for _ in range(conditionsSize):
                    conditionType = decode(int, fields)
                    condition = order_condition.Create(conditionType)
                    condition.decode(fields)
                    order.conditions.append(condition)

                order.conditionsIgnoreRth = decode(bool, fields)
                order.conditionsCancelOrder = decode(bool, fields)

            order.adjustedOrderType = decode(str, fields)
            order.triggerPrice = decode(float, fields)
            order.trailStopPrice = decode(float, fields)
            order.lmtPriceOffset = decode(float, fields)
            order.adjustedStopPrice = decode(float, fields)
            order.adjustedStopLimitPrice = decode(float, fields)
            order.adjustedTrailingAmount = decode(float, fields)
            order.adjustableTrailingUnit = decode(int, fields)

        if self.serverVersion >= MIN_SERVER_VER_SOFT_DOLLAR_TIER:
            name = decode(str, fields)
            value = decode(str, fields)
            displayName = decode(str, fields)
            order.softDollarTier = SoftDollarTier(name, value, displayName)

        if self.serverVersion >= MIN_SERVER_VER_CASH_QTY:
            order.cashQty = decode(float,fields)

        if self.serverVersion >= MIN_SERVER_VER_AUTO_PRICE_FOR_HEDGE:
            order.dontUseAutoPriceForHedge = decode(bool,fields)

        if self.serverVersion >= MIN_SERVER_VER_ORDER_CONTAINER:
            order.isOmsContainer = decode(bool, fields)

        if self.serverVersion >= MIN_SERVER_VER_D_PEG_ORDERS:
            order.discretionaryUpToLimitPrice = decode(bool, fields)

        self.wrapper.openOrder(order.orderId, contract, order, orderState)


    def processPortfolioValueMsg(self, fields):

        next(fields)
        version = decode(int, fields)

        # read contract fields
        contract = Contract()
        contract.conId = decode(int, fields) # ver 6 field
        contract.symbol = decode(str, fields)
        contract.secType = decode(str, fields)
        contract.lastTradeDateOrContractMonth = decode(str, fields)
        contract.strike = decode(float, fields)
        contract.right = decode(str, fields)

        if version >= 7:
            contract.multiplier = decode(str, fields)
            contract.primaryExchange = decode(str, fields)

        contract.currency = decode(str, fields)
        contract.localSymbol = decode(str, fields) # ver 2 field
        if version >= 8:
            contract.tradingClass = decode(str, fields)

        if self.serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS:
            position = decode(float, fields)
        else:
            position = decode(int, fields)

        marketPrice = decode(float, fields)
        marketValue = decode(float, fields)
        averageCost = decode(float, fields) # ver 3 field
        unrealizedPNL = decode(float, fields) # ver 3 field
        realizedPNL = decode(float, fields) # ver 3 field

        accountName = decode(str, fields) # ver 4 field

        if version == 6 and self.serverVersion == 39:
            contract.primaryExchange = decode(str, fields)

        self.wrapper.updatePortfolio( contract,
            position, marketPrice, marketValue, averageCost,
            unrealizedPNL, realizedPNL, accountName)


    def processContractDataMsg(self, fields):

        next(fields)
        version = decode(int, fields)

        reqId = -1
        if version >= 3:
            reqId = decode(int, fields)

        contract = ContractDetails()
        contract.contract.symbol = decode(str, fields)
        contract.contract.secType = decode(str, fields)
        self.readLastTradeDate(fields, contract, False)
        contract.contract.strike = decode(float, fields)
        contract.contract.right = decode(str, fields)
        contract.contract.exchange = decode(str, fields)
        contract.contract.currency = decode(str, fields)
        contract.contract.localSymbol = decode(str, fields)
        contract.marketName = decode(str, fields)
        contract.contract.tradingClass = decode(str, fields)
        contract.contract.conId = decode(int, fields)
        contract.minTick = decode(float, fields)
        if self.serverVersion >= MIN_SERVER_VER_MD_SIZE_MULTIPLIER:
            contract.mdSizeMultiplier = decode(int, fields)
        contract.contract.multiplier = decode(str, fields)
        contract.orderTypes = decode(str, fields)
        contract.validExchanges = decode(str, fields)
        contract.priceMagnifier = decode(int, fields) # ver 2 field
        if version >= 4:
            contract.underConId = decode(int, fields)
        if version >= 5:
            contract.longName = decode(str, fields)
            contract.contract.primaryExchange = decode(str, fields)
        if version >= 6:
            contract.contractMonth = decode(str, fields)
            contract.industry = decode(str, fields)
            contract.category = decode(str, fields)
            contract.subcategory = decode(str, fields)
            contract.timeZoneId = decode(str, fields)
            contract.tradingHours = decode(str, fields)
            contract.liquidHours = decode(str, fields)
        if version >= 8:
            contract.evRule = decode(str, fields)
            contract.evMultiplier = decode(int, fields)
        if version >= 7:
            secIdListCount = decode(int, fields)
            if secIdListCount > 0:
                contract.secIdList = []
                for _ in range(secIdListCount):
                    tagValue = TagValue()
                    tagValue.tag = decode(str, fields)
                    tagValue.value = decode(str, fields)
                    contract.secIdList.append(tagValue)

        if self.serverVersion >= MIN_SERVER_VER_AGG_GROUP:
            contract.aggGroup = decode(int, fields)

        if self.serverVersion >= MIN_SERVER_VER_UNDERLYING_INFO:
            contract.underSymbol = decode(str, fields)
            contract.underSecType = decode(str, fields)

        if self.serverVersion >= MIN_SERVER_VER_MARKET_RULES:
            contract.marketRuleIds = decode(str, fields)

        if self.serverVersion >= MIN_SERVER_VER_REAL_EXPIRATION_DATE:
            contract.realExpirationDate = decode(str, fields)

        self.wrapper.contractDetails(reqId, contract)


    def processBondContractDataMsg(self, fields):

        next(fields)
        version = decode(int, fields)

        reqId = -1
        if version >= 3:
            reqId = decode(int, fields)

        contract = ContractDetails()
        contract.contract.symbol = decode(str, fields)
        contract.contract.secType = decode(str, fields)
        contract.cusip = decode(str, fields)
        contract.coupon = decode(int, fields)
        self.readLastTradeDate(fields, contract, True)
        contract.issueDate = decode(str, fields)
        contract.ratings = decode(str, fields)
        contract.bondType = decode(str, fields)
        contract.couponType = decode(str, fields)
        contract.convertible = decode(bool, fields)
        contract.callable = decode(bool, fields)
        contract.putable = decode(bool, fields)
        contract.descAppend = decode(str, fields)
        contract.contract.exchange = decode(str, fields)
        contract.contract.currency = decode(str, fields)
        contract.marketName = decode(str, fields)
        contract.contract.tradingClass = decode(str, fields)
        contract.contract.conId = decode(int, fields)
        contract.minTick = decode(float, fields)
        if self.serverVersion >= MIN_SERVER_VER_MD_SIZE_MULTIPLIER:
            contract.mdSizeMultiplier = decode(int, fields)
        contract.orderTypes = decode(str, fields)
        contract.validExchanges = decode(str, fields)
        contract.nextOptionDate = decode(str, fields) # ver 2 field
        contract.nextOptionType = decode(str, fields) # ver 2 field
        contract.nextOptionPartial = decode(bool, fields) # ver 2 field
        contract.notes = decode(str, fields) # ver 2 field
        if version >= 4:
            contract.longName = decode(str, fields)
        if version >= 6:
            contract.evRule = decode(str, fields)
            contract.evMultiplier = decode(int, fields)
        if version >= 5:
            secIdListCount = decode(int, fields)
            if secIdListCount > 0:
                contract.secIdList = []
                for _ in range(secIdListCount):
                    tagValue = TagValue()
                    tagValue.tag = decode(str, fields)
                    tagValue.value = decode(str, fields)
                    contract.secIdList.append(tagValue)

        if self.serverVersion >= MIN_SERVER_VER_AGG_GROUP:
            contract.aggGroup = decode(int, fields)

        if self.serverVersion >= MIN_SERVER_VER_MARKET_RULES:
            contract.marketRuleIds = decode(str, fields)

        self.wrapper.bondContractDetails(reqId, contract)

    def processScannerDataMsg(self, fields):
        next(fields)
        decode(int, fields)
        reqId = decode(int, fields)

        numberOfElements = decode(int, fields)

        for _ in range(numberOfElements):
            data = ScanData()
            data.contract = ContractDetails()

            data.rank = decode(int, fields)
            data.contract.contract.conId = decode(int, fields) # ver 3 field
            data.contract.contract.symbol = decode(str, fields)
            data.contract.contract.secType = decode(str, fields)
            data.contract.contract.lastTradeDateOrContractMonth = decode(str, fields)
            data.contract.contract.strike = decode(float, fields)
            data.contract.contract.right = decode(str, fields)
            data.contract.contract.exchange = decode(str, fields)
            data.contract.contract.currency = decode(str, fields)
            data.contract.contract.localSymbol = decode(str, fields)
            data.contract.marketName = decode(str, fields)
            data.contract.contract.tradingClass = decode(str, fields)
            data.distance = decode(str, fields)
            data.benchmark = decode(str, fields)
            data.projection = decode(str, fields)
            data.legsStr = decode(str, fields)
            self.wrapper.scannerData(reqId, data.rank, data.contract,
                data.distance, data.benchmark, data.projection, data.legsStr)

        self.wrapper.scannerDataEnd(reqId)


    def processExecutionDataMsg(self, fields):
        next(fields)
        version = self.serverVersion

        if(self.serverVersion < MIN_SERVER_VER_LAST_LIQUIDITY):
            version = decode(int, fields)

        reqId = -1
        if version >= 7:
            reqId = decode(int, fields)

        orderId = decode(int, fields)

        # decode contract fields
        contract = Contract()
        contract.conId = decode(int, fields) # ver 5 field
        contract.symbol = decode(str, fields)
        contract.secType = decode(str, fields)
        contract.lastTradeDateOrContractMonth = decode(str, fields)
        contract.strike = decode(float, fields)
        contract.right = decode(str, fields)
        if version >= 9:
            contract.multiplier = decode(str, fields)
        contract.exchange = decode(str, fields)
        contract.currency = decode(str, fields)
        contract.localSymbol = decode(str, fields)
        if version >= 10:
            contract.tradingClass = decode(str, fields)

        # decode execution fields
        execution = Execution()
        execution.orderId = orderId
        execution.execId = decode(str, fields)
        execution.time = decode(str, fields)
        execution.acctNumber = decode(str, fields)
        execution.exchange = decode(str, fields)
        execution.side = decode(str, fields)

        if self.serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS:
                execution.shares = decode(float, fields)
        else:
                execution.shares = decode(int, fields)

        execution.price = decode(float, fields)
        execution.permId = decode(int, fields) # ver 2 field
        execution.clientId = decode(int, fields)  # ver 3 field
        execution.liquidation = decode(int, fields) # ver 4 field

        if version >= 6:
            execution.cumQty = decode(float, fields)
            execution.avgPrice = decode(float, fields)

        if version >= 8:
            execution.orderRef = decode(str, fields)

        if version >= 9:
            execution.evRule = decode(str, fields)
            execution.evMultiplier = decode(float, fields)
        if self.serverVersion >= MIN_SERVER_VER_MODELS_SUPPORT:
            execution.modelCode = decode(str, fields)
        if self.serverVersion >= MIN_SERVER_VER_LAST_LIQUIDITY:
            execution.lastLiquidity = decode(int, fields)

        self.wrapper.execDetails(reqId, contract, execution)


    def processHistoricalDataMsg(self, fields):
        next(fields)

        if self.serverVersion < MIN_SERVER_VER_SYNT_REALTIME_BARS:
            decode(int, fields)

        reqId = decode(int, fields)
        startDateStr = decode(str, fields) # ver 2 field
        endDateStr = decode(str, fields) # ver 2 field

        itemCount = decode(int, fields)

        for _ in range(itemCount):
            bar = BarData()
            bar.date = decode(str, fields)
            bar.open = decode(float, fields)
            bar.high = decode(float, fields)
            bar.low = decode(float, fields)
            bar.close = decode(float, fields)
            bar.volume = decode(int, fields)
            bar.average = decode(float, fields)

            if self.serverVersion < MIN_SERVER_VER_SYNT_REALTIME_BARS:
                decode(str, fields)

            bar.barCount = decode(int, fields) # ver 3 field

            self.wrapper.historicalData(reqId, bar)

        # send end of dataset marker
        self.wrapper.historicalDataEnd(reqId, startDateStr, endDateStr)

    def processHistoricalDataUpdateMsg(self, fields):
        next(fields)
        reqId = decode(int, fields)
        bar = BarData()
        bar.barCount = decode(int, fields)
        bar.date = decode(str, fields)
        bar.open = decode(float, fields)
        bar.close = decode(float, fields)
        bar.high = decode(float, fields)
        bar.low = decode(float, fields)
        bar.average = decode(float, fields)
        bar.volume = decode(int, fields)
        self.wrapper.historicalDataUpdate(reqId, bar)

    def processRealTimeBarMsg(self, fields):
        next(fields)
        decode(int, fields)
        reqId = decode(int, fields)

        bar = RealTimeBar()
        bar.time = decode(int, fields)
        bar.open = decode(float, fields)
        bar.high = decode(float, fields)
        bar.low = decode(float, fields)
        bar.close = decode(float, fields)
        bar.volume = decode(int, fields)
        bar.wap = decode(float, fields)
        bar.count = decode(int, fields)

        self.wrapper.realtimeBar(reqId, bar.time, bar.open, bar.high, bar.low, bar.close, bar.volume, bar.wap, bar.count)

    def processTickOptionComputationMsg(self, fields):
        optPrice = None
        pvDividend = None
        gamma = None
        vega = None
        theta = None
        undPrice = None

        next(fields)
        version = decode(int, fields)
        reqId = decode(int, fields)
        tickTypeInt = decode(int, fields)

        impliedVol = decode(float, fields)
        delta = decode(float, fields)

        if impliedVol < 0:    # -1 is the "not computed" indicator
            impliedVol = None
        if delta == -2: # -2 is the "not computed" indicator
            delta = None

        if version >= 6 or \
            tickTypeInt == TickTypeEnum.MODEL_OPTION or \
                        tickTypeInt == TickTypeEnum.DELAYED_MODEL_OPTION:

            optPrice = decode(float, fields)
            pvDividend = decode(float, fields)

            if optPrice == -1:    # -1 is the "not computed" indicator
                optPrice = None
            if pvDividend == -1:  # -1 is the "not computed" indicator
                pvDividend = None

        if version >= 6:
            gamma = decode(float, fields)
            vega = decode(float, fields)
            theta = decode(float, fields)
            undPrice = decode(float, fields)

            if gamma == -2:  # -2 is the "not yet computed" indicator
                gamma = None
            if vega == -2:    # -2 is the "not yet computed" indicator
                vega = None
            if theta == -2:  # -2 is the "not yet computed" indicator
                theta = None
            if undPrice == -1:             # -1 is the "not computed" indicator
                undPrice = None

        self.wrapper.tickOptionComputation(reqId, tickTypeInt, impliedVol,
            delta, optPrice, pvDividend, gamma, vega, theta, undPrice)



    def processDeltaNeutralValidationMsg(self, fields):
        next(fields)
        decode(int, fields)
        reqId = decode(int, fields)

        deltaNeutralContract = DeltaNeutralContract()

        deltaNeutralContract.conId = decode(int, fields)
        deltaNeutralContract.delta = decode(float, fields)
        deltaNeutralContract.price = decode(float, fields)

        self.wrapper.deltaNeutralValidation(reqId, deltaNeutralContract)


    def processMarketDataTypeMsg(self, fields):
        next(fields)
        decode(int, fields)
        reqId = decode(int, fields)
        marketDataType = decode(int, fields)

        self.wrapper.marketDataType(reqId, marketDataType)

    def processCommissionReportMsg(self, fields):
        next(fields)
        decode(int, fields)

        commissionReport = CommissionReport()
        commissionReport.execId = decode(str, fields)
        commissionReport.commission = decode(float, fields)
        commissionReport.currency = decode(str, fields)
        commissionReport.realizedPNL = decode(float, fields)
        commissionReport.yield_ = decode(float, fields)
        commissionReport.yieldRedemptionDate = decode(int, fields)

        self.wrapper.commissionReport(commissionReport)


    def processPositionDataMsg(self, fields):
        next(fields)
        version = decode(int, fields)

        account = decode(str, fields)

        # decode contract fields
        contract = Contract()
        contract.conId = decode(int, fields)
        contract.symbol = decode(str, fields)
        contract.secType = decode(str, fields)
        contract.lastTradeDateOrContractMonth = decode(str, fields)
        contract.strike = decode(float, fields)
        contract.right = decode(str, fields)
        contract.multiplier = decode(str, fields)
        contract.exchange = decode(str, fields)
        contract.currency = decode(str, fields)
        contract.localSymbol = decode(str, fields)
        if version >= 2:
            contract.tradingClass = decode(str, fields)

        if self.serverVersion >= MIN_SERVER_VER_FRACTIONAL_POSITIONS:
            position = decode(float, fields)
        else:
            position = decode(int, fields)

        avgCost = 0.
        if version >= 3:
            avgCost = decode(float, fields)

        self.wrapper.position(account, contract, position, avgCost)


    def processPositionMultiMsg(self, fields):
        next(fields)
        decode(int, fields)
        reqId = decode(int, fields)
        account = decode(str, fields)

        # decode contract fields
        contract = Contract()
        contract.conId = decode(int, fields)
        contract.symbol = decode(str, fields)
        contract.secType = decode(str, fields)
        contract.lastTradeDateOrContractMonth = decode(str, fields)
        contract.strike = decode(float, fields)
        contract.right = decode(str, fields)
        contract.multiplier = decode(str, fields)
        contract.exchange = decode(str, fields)
        contract.currency = decode(str, fields)
        contract.localSymbol = decode(str, fields)
        contract.tradingClass = decode(str, fields)
        position = decode(float, fields)
        avgCost = decode(float, fields)
        modelCode = decode(str, fields)

        self.wrapper.positionMulti(reqId, account, modelCode, contract, position, avgCost)


    def processSecurityDefinitionOptionParameterMsg(self, fields):
        next(fields)

        reqId = decode(int, fields)
        exchange = decode(str, fields)
        underlyingConId = decode(int, fields)
        tradingClass = decode(str, fields)
        multiplier = decode(str, fields)

        expCount = decode(int, fields)
        expirations = set()
        for _ in range(expCount):
            expiration = decode(str, fields)
            expirations.add(expiration)

        strikeCount = decode(int, fields)
        strikes = set()
        for _ in range(strikeCount):
            strike = decode(float, fields)
            strikes.add(strike)

        self.wrapper.securityDefinitionOptionParameter(reqId, exchange,
            underlyingConId, tradingClass, multiplier, expirations, strikes)


    def processSecurityDefinitionOptionParameterEndMsg(self, fields):
        next(fields)

        reqId = decode(int, fields)
        self.wrapper.securityDefinitionOptionParameterEnd(reqId)


    def processSoftDollarTiersMsg(self, fields):
        next(fields)

        reqId = decode(int, fields)
        nTiers = decode(int, fields)

        tiers = []
        for _ in range(nTiers):
                tier = SoftDollarTier()
                tier.name = decode(str, fields)
                tier.val = decode(str, fields)
                tier.displayName = decode(str, fields)
                tiers.append(tier)

        self.wrapper.softDollarTiers(reqId, tiers)


    def processFamilyCodesMsg(self, fields):
        next(fields)

        nFamilyCodes = decode(int, fields)
        familyCodes = []
        for _ in range(nFamilyCodes):
            famCode = FamilyCode()
            famCode.accountID = decode(str, fields)
            famCode.familyCodeStr = decode(str, fields)
            familyCodes.append(famCode)

        self.wrapper.familyCodes(familyCodes)


    def processSymbolSamplesMsg(self, fields):
        next(fields)

        reqId = decode(int, fields)
        nContractDescriptions = decode(int, fields)
        contractDescriptions = []
        for _ in range(nContractDescriptions):
            conDesc = ContractDescription()
            conDesc.contract.conId = decode(int, fields)
            conDesc.contract.symbol = decode(str, fields)
            conDesc.contract.secType = decode(str, fields)
            conDesc.contract.primaryExchange = decode(str, fields)
            conDesc.contract.currency = decode(str, fields)

            nDerivativeSecTypes = decode(int, fields)
            conDesc.derivativeSecTypes = []
            for _ in range(nDerivativeSecTypes):
                derivSecType = decode(str, fields)
                conDesc.derivativeSecTypes.append(derivSecType)
            contractDescriptions.append(conDesc)

        self.wrapper.symbolSamples(reqId, contractDescriptions)

    def processSmartComponents(self,fields):
        next(fields)
        reqId = decode(int, fields)
        n = decode(int, fields)

        smartComponentMap = []
        for _ in range(n):
            smartComponent = SmartComponent()
            smartComponent.bitNumber = decode(int, fields)
            smartComponent.exchange = decode(str, fields)
            smartComponent.exchangeLetter = decode(str, fields)
            smartComponentMap.append(smartComponent)

        self.wrapper.smartComponents(reqId, smartComponentMap)

    def processTickReqParams(self,fields):
        next(fields)
        tickerId = decode(int, fields)
        minTick = decode(float, fields)
        bboExchange = decode(str, fields)
        snapshotPermissions = decode(int, fields)
        self.wrapper.tickReqParams(tickerId, minTick, bboExchange, snapshotPermissions)

    def processMktDepthExchanges(self,fields):
        next(fields)
        depthMktDataDescriptions = []
        nDepthMktDataDescriptions = decode(int, fields)

        if nDepthMktDataDescriptions > 0:
            for _ in range(nDepthMktDataDescriptions):
                desc = DepthMktDataDescription()
                desc.exchange = decode(str, fields)
                desc.secType = decode(str, fields)
                if self.serverVersion >= MIN_SERVER_VER_SERVICE_DATA_TYPE:
                    desc.listingExch = decode(str, fields)
                    desc.serviceDataType = decode(str, fields)
                    desc.aggGroup = decode(int, fields)
                else:
                    decode(int,fields) #boolean notSuppIsL2
                depthMktDataDescriptions.append(desc)

        self.wrapper.mktDepthExchanges(depthMktDataDescriptions)

    def processHeadTimestamp(self,fields):
        next(fields)
        reqId = decode(int, fields)
        headTimestamp = decode(str, fields)
        self.wrapper.headTimestamp(reqId,headTimestamp)

    def processTickNews(self,fields):
        next(fields)
        tickerId = decode( int, fields)
        timeStamp = decode(int, fields)
        providerCode = decode(str, fields)
        articleId = decode(str, fields)
        headline = decode(str, fields)
        extraData = decode(str, fields)
        self.wrapper.tickNews(tickerId, timeStamp, providerCode, articleId, headline, extraData)

    def processNewsProviders(self,fields):
        next(fields)
        newsProviders = []
        nNewsProviders = decode(int, fields)
        if nNewsProviders > 0:
            for _ in range(nNewsProviders):
                provider = NewsProvider()
                provider.code = decode(str, fields)
                provider.name = decode(str, fields)
                newsProviders.append(provider)

        self.wrapper.newsProviders(newsProviders)

    def processNewsArticle(self,fields):
        next(fields)
        reqId = decode(int, fields)
        articleType = decode(int, fields)
        articleText = decode(str, fields)
        self.wrapper.newsArticle(reqId, articleType, articleText)

    def processHistoricalNews(self,fields):
        next(fields)
        requestId = decode(int, fields)
        time = decode(str, fields)
        providerCode = decode(str, fields)
        articleId = decode(str, fields)
        headline = decode(str, fields)
        self.wrapper.historicalNews(requestId, time, providerCode, articleId, headline)

    def processHistoricalNewsEnd(self,fields):
        next(fields)
        reqId = decode(int, fields)
        hasMore = decode(bool, fields)
        self.wrapper.historicalNewsEnd(reqId, hasMore)

    def processHistogramData(self,fields):
        next(fields)
        reqId = decode(int, fields)
        numPoints = decode(int, fields)

        histogram = []
        for _ in range(numPoints):
            dataPoint = HistogramData()
            dataPoint.price = decode(float,fields)
            dataPoint.count = decode(int,fields)
            histogram.append(dataPoint)

        self.wrapper.histogramData(reqId, histogram)

    def processRerouteMktDataReq(self, fields):
        next(fields)
        reqId = decode(int, fields)
        conId = decode(int, fields)
        exchange = decode(str, fields)

        self.wrapper.rerouteMktDataReq(reqId, conId, exchange)

    def processRerouteMktDepthReq(self, fields):
        next(fields)
        reqId = decode(int, fields)
        conId = decode(int, fields)
        exchange = decode(str, fields)

        self.wrapper.rerouteMktDepthReq(reqId, conId, exchange)

    def processMarketRuleMsg(self, fields):
        next(fields)
        marketRuleId = decode(int, fields)

        nPriceIncrements = decode(int, fields)
        priceIncrements = []

        if nPriceIncrements > 0:
            for _ in range(nPriceIncrements):
                prcInc = PriceIncrement()
                prcInc.lowEdge = decode(float, fields)
                prcInc.increment = decode(float, fields)
                priceIncrements.append(prcInc)

        self.wrapper.marketRule(marketRuleId, priceIncrements)

    def processPnLMsg(self, fields):
        next(fields)
        reqId = decode(int, fields)
        dailyPnL = decode(float, fields)
        unrealizedPnL = None
        realizedPnL = None

        if self.serverVersion >= MIN_SERVER_VER_UNREALIZED_PNL:
            unrealizedPnL = decode(float, fields)

        if self.serverVersion >= MIN_SERVER_VER_REALIZED_PNL:
            realizedPnL = decode(float, fields)

        self.wrapper.pnl(reqId, dailyPnL, unrealizedPnL, realizedPnL)

    def processPnLSingleMsg(self, fields):
        next(fields)
        reqId = decode(int, fields)
        pos = decode(int, fields)
        dailyPnL = decode(float, fields)
        unrealizedPnL = None
        realizedPnL = None

        if self.serverVersion >= MIN_SERVER_VER_UNREALIZED_PNL:
            unrealizedPnL = decode(float, fields)

        if self.serverVersion >= MIN_SERVER_VER_REALIZED_PNL:
            realizedPnL = decode(float, fields)

        value = decode(float, fields)

        self.wrapper.pnlSingle(reqId, pos, dailyPnL, unrealizedPnL, realizedPnL, value)

    def processHistoricalTicks(self, fields):
        next(fields)
        reqId = decode(int, fields)
        tickCount = decode(int, fields)

        ticks = []

        for _ in range(tickCount):
            historicalTick = HistoricalTick()
            historicalTick.time = decode(int, fields)
            next(fields) # for consistency
            historicalTick.price = decode(float, fields)
            historicalTick.size = decode(int, fields)
            ticks.append(historicalTick)

        done = decode(bool, fields)

        self.wrapper.historicalTicks(reqId, ticks, done)

    def processHistoricalTicksBidAsk(self, fields):
        next(fields)
        reqId = decode(int, fields)
        tickCount = decode(int, fields)

        ticks = []

        for _ in range(tickCount):
            historicalTickBidAsk = HistoricalTickBidAsk()
            historicalTickBidAsk.time = decode(int, fields)
            mask = decode(int, fields)
            tickAttribBidAsk = TickAttribBidAsk()
            tickAttribBidAsk.askPastHigh = mask & 1 != 0
            tickAttribBidAsk.bidPastLow = mask & 2 != 0
            historicalTickBidAsk.tickAttribBidAsk = tickAttribBidAsk
            historicalTickBidAsk.priceBid = decode(float, fields)
            historicalTickBidAsk.priceAsk = decode(float, fields)
            historicalTickBidAsk.sizeBid = decode(int, fields)
            historicalTickBidAsk.sizeAsk = decode(int, fields)
            ticks.append(historicalTickBidAsk)

        done = decode(bool, fields)

        self.wrapper.historicalTicksBidAsk(reqId, ticks, done)

    def processHistoricalTicksLast(self, fields):
        next(fields)
        reqId = decode(int, fields)
        tickCount = decode(int, fields)

        ticks = []

        for _ in range(tickCount):
            historicalTickLast = HistoricalTickLast()
            historicalTickLast.time = decode(int, fields)
            mask = decode(int, fields)
            tickAttribLast = TickAttribLast()
            tickAttribLast.pastLimit = mask & 1 != 0
            tickAttribLast.unreported = mask & 2 != 0
            historicalTickLast.tickAttribLast = tickAttribLast
            historicalTickLast.price = decode(float, fields)
            historicalTickLast.size = decode(int, fields)
            historicalTickLast.exchange = decode(str, fields)
            historicalTickLast.specialConditions = decode(str, fields)
            ticks.append(historicalTickLast)

        done = decode(bool, fields)

        self.wrapper.historicalTicksLast(reqId, ticks, done)

    def processTickByTickMsg(self, fields):
        next(fields)
        reqId = decode(int, fields)
        tickType = decode(int, fields)
        time = decode(int, fields)

        if tickType == 0:
            # None
            pass
        elif tickType == 1 or tickType == 2:
            # Last or AllLast
            price = decode(float, fields)
            size = decode(int, fields)
            mask = decode(int, fields)

            tickAttribLast = TickAttribLast()
            tickAttribLast.pastLimit = mask & 1 != 0
            tickAttribLast.unreported = mask & 2 != 0
            exchange = decode(str, fields)
            specialConditions = decode(str, fields)

            self.wrapper.tickByTickAllLast(reqId, tickType, time, price, size, tickAttribLast,
                                           exchange, specialConditions)
        elif tickType == 3:
            # BidAsk
            bidPrice = decode(float, fields)
            askPrice = decode(float, fields)
            bidSize = decode(int, fields)
            askSize = decode(int, fields)
            mask = decode(int, fields)
            tickAttribBidAsk = TickAttribBidAsk()
            tickAttribBidAsk.bidPastLow = mask & 1 != 0
            tickAttribBidAsk.askPastHigh = mask & 2 != 0

            self.wrapper.tickByTickBidAsk(reqId, time, bidPrice, askPrice, bidSize,
                                          askSize, tickAttribBidAsk)
        elif tickType == 4:
            # MidPoint
            midPoint = decode(float, fields)

            self.wrapper.tickByTickMidPoint(reqId, time, midPoint)

    def processOrderBoundMsg(self, fields):
        next(fields)
        reqId = decode(int, fields)
        apiClientId = decode(int, fields)
        apiOrderId = decode(int, fields)

        self.wrapper.orderBound(reqId, apiClientId, apiOrderId)

    def processMarketDepthL2Msg(self, fields):
        next(fields)
        decode(int, fields)
        reqId = decode(int, fields)

        position = decode(int, fields)
        marketMaker = decode(str, fields)
        operation = decode(int, fields)
        side = decode(int, fields)
        price = decode(float, fields)
        size = decode(int, fields)
        isSmartDepth = False

        if self.serverVersion >= MIN_SERVER_VER_SMART_DEPTH:
            isSmartDepth = decode(bool, fields)

        self.wrapper.updateMktDepthL2(reqId, position, marketMaker,
                        operation, side, price, size, isSmartDepth)

    ######################################################################

    def readLastTradeDate(self, fields, contract: ContractDetails, isBond: bool):
        lastTradeDateOrContractMonth = decode(str, fields)
        if lastTradeDateOrContractMonth is not None:
            splitted = lastTradeDateOrContractMonth.split()
            if len(splitted) > 0:
                if isBond:
                    contract.maturity = splitted[0]
                else:
                    contract.contract.lastTradeDateOrContractMonth = splitted[0]

            if len(splitted) > 1:
                contract.lastTradeTime = splitted[1]

            if isBond and len(splitted) > 2:
                contract.timeZoneId = splitted[2]

    ######################################################################

    def discoverParams(self):
        meth2handleInfo = {}
        for handleInfo in self.msgId2handleInfo.values():
            meth2handleInfo[handleInfo.wrapperMeth] = handleInfo

        methods = inspect.getmembers(EWrapper, inspect.isfunction)
        for (_, meth) in methods:
            #logger.debug("meth %s", name)
            sig = inspect.signature(meth)
            handleInfo = meth2handleInfo.get(meth, None)
            if handleInfo is not None:
                handleInfo.wrapperParams = sig.parameters

            #for (pname, param) in sig.parameters.items():
            #     logger.debug("\tparam %s %s %s", pname, param.name, param.annotation)


    def printParams(self):
        for (_, handleInfo) in self.msgId2handleInfo.items():
            if handleInfo.wrapperMeth is not None:
                logger.debug("meth %s", handleInfo.wrapperMeth.__name__)
                if handleInfo.wrapperParams is not None:
                    for (pname, param) in handleInfo.wrapperParams.items():
                        logger.debug("\tparam %s %s %s", pname, param.name, param.annotation)


    def interpretWithSignature(self, fields, handleInfo):
        if handleInfo.wrapperParams is None:
            logger.debug("%s: no param info in %s", fields, handleInfo)
            return

        nIgnoreFields = 2 #bypass msgId and versionId faster this way
        if len(fields) - nIgnoreFields != len(handleInfo.wrapperParams) - 1:
            logger.error("diff len fields and params %d %d for fields: %s and handleInfo: %s",
                         len(fields), len(handleInfo.wrapperParams), fields,
                         handleInfo)
            return

        fieldIdx = nIgnoreFields
        args = []
        for (pname, param) in handleInfo.wrapperParams.items():
            if pname != "self":
                logger.debug("field %s ", fields[fieldIdx])
                try:
                    arg = fields[fieldIdx].decode('UTF-8')
                except UnicodeDecodeError:
                    arg = fields[fieldIdx].decode('latin-1')
                logger.debug("arg %s type %s", arg, param.annotation)
                if param.annotation is int:
                    arg = int(arg)
                elif param.annotation is float:
                    arg = float(arg)

                args.append(arg)
                fieldIdx += 1

        method = getattr(self.wrapper, handleInfo.wrapperMeth.__name__)
        logger.debug("calling %s with %s %s", method, self.wrapper, args)
        method(*args)

    def interpret(self, fields):
        if len(fields) == 0:
            logger.debug("no fields")
            return

        sMsgId = fields[0]
        nMsgId = int(sMsgId)

        handleInfo = self.msgId2handleInfo.get(nMsgId, None)

        if handleInfo is None:
            logger.debug("%s: no handleInfo", fields)
            return

        try:
            if handleInfo.wrapperMeth is not None:
                logger.debug("In interpret(), handleInfo: %s", handleInfo)
                self.interpretWithSignature(fields, handleInfo)
            elif handleInfo.processMeth is not None:
                handleInfo.processMeth(self, iter(fields))
        except BadMessage:
                theBadMsg = ",".join(fields)
                self.wrapper.error(NO_VALID_ID, BAD_MESSAGE.code(),
                                   BAD_MESSAGE.msg() + theBadMsg)
                raise


    msgId2handleInfo = {
        IN.TICK_PRICE: HandleInfo(proc=processTickPriceMsg),
        IN.TICK_SIZE: HandleInfo(wrap=EWrapper.tickSize),
        IN.ORDER_STATUS: HandleInfo(proc=processOrderStatusMsg),
        IN.ERR_MSG: HandleInfo(wrap=EWrapper.error),
        IN.OPEN_ORDER: HandleInfo(proc=processOpenOrder),
        IN.ACCT_VALUE: HandleInfo(wrap=EWrapper.updateAccountValue),
        IN.PORTFOLIO_VALUE: HandleInfo(proc=processPortfolioValueMsg),
        IN.ACCT_UPDATE_TIME: HandleInfo(wrap=EWrapper.updateAccountTime),
        IN.NEXT_VALID_ID: HandleInfo(wrap=EWrapper.nextValidId, ),
        IN.CONTRACT_DATA: HandleInfo(proc=processContractDataMsg),
        IN.EXECUTION_DATA: HandleInfo(proc=processExecutionDataMsg),
        IN.MARKET_DEPTH: HandleInfo(wrap=EWrapper.updateMktDepth),
        IN.MARKET_DEPTH_L2: HandleInfo(proc=processMarketDepthL2Msg),
        IN.NEWS_BULLETINS: HandleInfo(wrap=EWrapper.updateNewsBulletin),
        IN.MANAGED_ACCTS: HandleInfo(wrap=EWrapper.managedAccounts),
        IN.RECEIVE_FA: HandleInfo(wrap=EWrapper.receiveFA),
        IN.HISTORICAL_DATA: HandleInfo(proc=processHistoricalDataMsg),
        IN.HISTORICAL_DATA_UPDATE: HandleInfo(proc=processHistoricalDataUpdateMsg),
        IN.BOND_CONTRACT_DATA: HandleInfo(proc=processBondContractDataMsg),
        IN.SCANNER_PARAMETERS: HandleInfo(wrap=EWrapper.scannerParameters),
        IN.SCANNER_DATA: HandleInfo(proc=processScannerDataMsg),
        IN.TICK_OPTION_COMPUTATION: HandleInfo(proc=processTickOptionComputationMsg),
        IN.TICK_GENERIC: HandleInfo(wrap=EWrapper.tickGeneric),
        IN.TICK_STRING: HandleInfo(wrap=EWrapper.tickString),
        IN.TICK_EFP: HandleInfo(wrap=EWrapper.tickEFP),
        IN.CURRENT_TIME: HandleInfo(wrap=EWrapper.currentTime),
        IN.REAL_TIME_BARS: HandleInfo(proc=processRealTimeBarMsg),
        IN.FUNDAMENTAL_DATA: HandleInfo(wrap=EWrapper.fundamentalData),
        IN.CONTRACT_DATA_END: HandleInfo(wrap=EWrapper.contractDetailsEnd),
        IN.OPEN_ORDER_END: HandleInfo(wrap=EWrapper.openOrderEnd),
        IN.ACCT_DOWNLOAD_END: HandleInfo(wrap=EWrapper.accountDownloadEnd),
        IN.EXECUTION_DATA_END: HandleInfo(wrap=EWrapper.execDetailsEnd),
        IN.DELTA_NEUTRAL_VALIDATION: HandleInfo(proc=processDeltaNeutralValidationMsg),
        IN.TICK_SNAPSHOT_END: HandleInfo(wrap=EWrapper.tickSnapshotEnd),
        IN.MARKET_DATA_TYPE: HandleInfo(wrap=EWrapper.marketDataType),
        IN.COMMISSION_REPORT: HandleInfo(proc=processCommissionReportMsg),
        IN.POSITION_DATA: HandleInfo(proc=processPositionDataMsg),
        IN.POSITION_END: HandleInfo(wrap=EWrapper.positionEnd),
        IN.ACCOUNT_SUMMARY: HandleInfo(wrap=EWrapper.accountSummary),
        IN.ACCOUNT_SUMMARY_END: HandleInfo(wrap=EWrapper.accountSummaryEnd),
        IN.VERIFY_MESSAGE_API: HandleInfo(wrap=EWrapper.verifyMessageAPI),
        IN.VERIFY_COMPLETED: HandleInfo(wrap=EWrapper.verifyCompleted),
        IN.DISPLAY_GROUP_LIST: HandleInfo(wrap=EWrapper.displayGroupList),
        IN.DISPLAY_GROUP_UPDATED: HandleInfo(wrap=EWrapper.displayGroupUpdated),
        IN.VERIFY_AND_AUTH_MESSAGE_API: HandleInfo(wrap=EWrapper.verifyAndAuthMessageAPI),
        IN.VERIFY_AND_AUTH_COMPLETED: HandleInfo(wrap=EWrapper.verifyAndAuthCompleted),
        IN.POSITION_MULTI: HandleInfo(proc=processPositionMultiMsg),
        IN.POSITION_MULTI_END: HandleInfo(wrap=EWrapper.positionMultiEnd),
        IN.ACCOUNT_UPDATE_MULTI: HandleInfo(wrap=EWrapper.accountUpdateMulti),
        IN.ACCOUNT_UPDATE_MULTI_END: HandleInfo(wrap=EWrapper.accountUpdateMultiEnd),
        IN.SECURITY_DEFINITION_OPTION_PARAMETER: HandleInfo(proc=processSecurityDefinitionOptionParameterMsg),
        IN.SECURITY_DEFINITION_OPTION_PARAMETER_END: HandleInfo(proc=processSecurityDefinitionOptionParameterEndMsg),
        IN.SOFT_DOLLAR_TIERS: HandleInfo(proc=processSoftDollarTiersMsg),
        IN.FAMILY_CODES: HandleInfo(proc=processFamilyCodesMsg),
        IN.SYMBOL_SAMPLES: HandleInfo(proc=processSymbolSamplesMsg),
        IN.SMART_COMPONENTS: HandleInfo(proc=processSmartComponents),
        IN.TICK_REQ_PARAMS: HandleInfo(proc=processTickReqParams),
        IN.MKT_DEPTH_EXCHANGES: HandleInfo(proc=processMktDepthExchanges),
        IN.HEAD_TIMESTAMP: HandleInfo(proc=processHeadTimestamp),
        IN.TICK_NEWS: HandleInfo(proc=processTickNews),
        IN.NEWS_PROVIDERS: HandleInfo(proc=processNewsProviders),
        IN.NEWS_ARTICLE: HandleInfo(proc=processNewsArticle),
        IN.HISTORICAL_NEWS: HandleInfo(proc=processHistoricalNews),
        IN.HISTORICAL_NEWS_END: HandleInfo(proc=processHistoricalNewsEnd),
        IN.HISTOGRAM_DATA: HandleInfo(proc=processHistogramData),
        IN.REROUTE_MKT_DATA_REQ: HandleInfo(proc=processRerouteMktDataReq),
        IN.REROUTE_MKT_DEPTH_REQ: HandleInfo(proc=processRerouteMktDepthReq),
        IN.MARKET_RULE: HandleInfo(proc=processMarketRuleMsg),
        IN.PNL: HandleInfo(proc=processPnLMsg),
        IN.PNL_SINGLE: HandleInfo(proc=processPnLSingleMsg),
        IN.HISTORICAL_TICKS: HandleInfo(proc=processHistoricalTicks),
        IN.HISTORICAL_TICKS_BID_ASK: HandleInfo(proc=processHistoricalTicksBidAsk),
        IN.HISTORICAL_TICKS_LAST: HandleInfo(proc=processHistoricalTicksLast),
        IN.TICK_BY_TICK: HandleInfo(proc=processTickByTickMsg),
        IN.ORDER_BOUND: HandleInfo(proc=processOrderBoundMsg)
   }



