# encoding: UTF-8

from __future__ import division
from collections import OrderedDict
from operator import attrgetter

from eventType import *
from vtConstant import *
from vtGateway import VtSubscribeReq

from omPricing import calculateGreeks, calculateImpv
from omTool import calculateExpiryTime


########################################################################
class OmContract(object):
    """合约数据结构"""

    #----------------------------------------------------------------------
    def __init__(self, symbol):
        """Constructor"""        
        # 代码相关
        self.symbol = symbol
        self.exchange = EMPTY_STRING
        self.vtSymbol = EMPTY_STRING
        
        # 合约属性
        self.size = EMPTY_INT
        self.priceTick = EMPTY_FLOAT
        self.gatewayName = EMPTY_STRING
        
        # 常规行情
        self.openPrice = EMPTY_FLOAT
        self.lastPrice = EMPTY_FLOAT
        self.volume = EMPTY_INT
        self.openInterest = EMPTY_INT
        self.time = EMPTY_STRING
        self.date = EMPTY_STRING
        self.change = EMPTY_FLOAT
        
        self.upperLimit = EMPTY_STRING
        self.lowerLimit = EMPTY_STRING
        
        # 报价数据
        self.bidPrice1 = EMPTY_FLOAT
        self.bidPrice2 = EMPTY_FLOAT
        self.bidPrice3 = EMPTY_FLOAT
        self.bidPrice4 = EMPTY_FLOAT
        self.bidPrice5 = EMPTY_FLOAT
        
        self.askPrice1 = EMPTY_FLOAT
        self.askPrice2 = EMPTY_FLOAT
        self.askPrice3 = EMPTY_FLOAT
        self.askPrice4 = EMPTY_FLOAT
        self.askPrice5 = EMPTY_FLOAT   
        
        self.bidVolume1 = EMPTY_FLOAT
        self.bidVolume2 = EMPTY_FLOAT
        self.bidVolume3 = EMPTY_FLOAT
        self.bidVolume4 = EMPTY_FLOAT
        self.bidVolume5 = EMPTY_FLOAT
        
        self.askVolume1 = EMPTY_FLOAT
        self.askVolume2 = EMPTY_FLOAT
        self.askVolume3 = EMPTY_FLOAT
        self.askVolume4 = EMPTY_FLOAT
        self.askVolume5 = EMPTY_FLOAT  
        
        # 中间价（定价、估值用）
        self.midPrice = EMPTY_FLOAT         
        
        # 持仓数据
        self.longPos = 0
        self.shortPos = 0
        self.netPos = 0
        
        # 行情初始化
        self.tickInited = False
        
    #----------------------------------------------------------------------
    def newTick(self, tick):
        """行情更新"""
        if not self.tickInited:
            self.date = tick.date
            self.openPrice = tick.openPrice
            self.upperLimit = tick.upperLimit
            self.lowerLimit = tick.lowerLimit
            self.tickInited = True
            
        self.lastPrice = tick.lastPrice
        self.volume = tick.volume
        self.openInterest = tick.openInterest
        self.time = tick.time
        self.change = self.lastPrice - self.openPrice
        
        self.bidPrice1 = tick.bidPrice1
        self.askPrice1 = tick.askPrice1
        self.bidVolume1 = tick.bidVolume1
        self.askVolume1 = tick.askVolume1
        
        self.midPrice = (self.bidPrice1 + self.askPrice1)/2

    #----------------------------------------------------------------------
    def newTrade(self, trade):
        """成交更新"""
        if trade.direction is DIRECTION_LONG:
            if trade.offset is OFFSET_OPEN:
                self.longPos += trade.volume
            else:
                self.shortPos -= trade.volume
        else:
            if trade.offset is OFFSET_OPEN:
                self.shortPos += trade.volume
            else:
                self.longPos -= trade.volume
                
        self.netPos = self.longPos - self.shortPos
    
    #----------------------------------------------------------------------
    def newPos(self, pos):
        """持仓更新"""
        if pos.direction is DIRECTION_LONG:
            self.longPos = pos.position
        else:
            self.shortPos = pos.position
        
        self.netPos = self.longPos - self.shortPos
    
    #----------------------------------------------------------------------
    def init(self, contract):
        """初始化"""
        self.exchange = contract.exchange
        self.vtSymbol = contract.vtSymbol
        
        self.size = contract.size
        self.priceTick = contract.priceTick


########################################################################
class OmUnderlying(OmContract):
    """标的物"""

    #----------------------------------------------------------------------
    def __init__(self, symbol):
        """Constructor"""
        super(OmUnderlying, self).__init__(symbol)
        
        self.chainList = []
        self.chainDict = OrderedDict()      # 期权链对象        
        
        self.theoDelta = EMPTY_FLOAT
        self.posDelta = EMPTY_FLOAT
        
    #----------------------------------------------------------------------
    def newTick(self, tick):
        """行情更新"""
        super(OmUnderlying, self).newTick(tick)
        
        self.midPrice = (tick.bidPrice1 + tick.askPrice1)/2
        self.theoDelta = self.size * self.midPrice / 100
        
        # 遍历推送自己的行情到期权链中
        for chain in self.chainList:
            chain.newUnderlyingTick()

    #----------------------------------------------------------------------
    def newTrade(self, trade):
        """成交更新"""
        super(OmUnderlying, self).newTrade(trade)
        self.calculatePosGreeks()
    
    #----------------------------------------------------------------------
    def newPos(self, pos):
        """持仓更新"""
        super(OmUnderlying, self).newPos(pos)
        self.calculatePosGreeks()
    
    #----------------------------------------------------------------------
    def init(self, contract, chainList):
        """初始化"""
        super(OmUnderlying, self).init(contract)
        
        self.chainList = chainList
        self.chainDict = OrderedDict([(chain.symbol, chain) for chain in chainList])
        self.theoDelta = self.size * self.midPrice / 100
        self.gatewayName = contract.gatewayName
        
    #----------------------------------------------------------------------
    def calculatePosGreeks(self):
        """计算持仓希腊值"""
        self.posDelta = self.theoDelta * self.netPos
        


########################################################################
class OmEquity(OmUnderlying):
    """股票"""

    #----------------------------------------------------------------------
    def __init__(self, symbol):
        """Constructor"""
        super(OmEquity, self).__init__(symbol)


########################################################################
class OmFutures(OmUnderlying):
    """期货"""

    #----------------------------------------------------------------------
    def __init__(self, symbol):
        """Constructor"""
        super(OmFutures, self).__init__(symbol)
        
        self.expiryDate = EMPTY_STRING


########################################################################
class OmOption(OmContract):
    """期权"""

    #----------------------------------------------------------------------
    def __init__(self, symbol):
        """Constructor"""
        super(OmOption, self).__init__(symbol)
        
        # 期权属性
        self.underlying = None
        self.strike = EMPTY_FLOAT
        self.optionType = EMPTY_INT     # +1/-1 call/put
        
        self.interestRate = EMPTY_FLOAT
        self.expiryDate = EMPTY_STRING
        self.expiryTime = EMPTY_FLOAT        
        
        # 标的相关
        self.underlyingPrice = EMPTY_FLOAT
        
        # 波动率属性
        self.bidImpv = EMPTY_FLOAT
        self.askImpv = EMPTY_FLOAT
        self.midImpv = EMPTY_FLOAT
        
        # 定价公式
        self.pricingFormula = calculateGreeks
        self.impvFormula = calculateImpv
        
        # 模型定价
        self.pricingImpv = EMPTY_FLOAT

        self.theoPrice = EMPTY_FLOAT    # 理论价
        self.theoDelta = EMPTY_FLOAT    # 合约的希腊值（乘以了合约大小）
        self.theoGamma = EMPTY_FLOAT
        self.theoTheta = EMPTY_FLOAT
        self.theoVega = EMPTY_FLOAT
        
        self.posDelta = EMPTY_FLOAT     # 持仓的希腊值（乘以了持仓）
        self.posGamma = EMPTY_FLOAT
        self.posTheta = EMPTY_FLOAT
        self.posVega = EMPTY_FLOAT
        
    #----------------------------------------------------------------------
    def newTick(self, tick):
        """行情更新"""
        super(OmOption, self).newTick(tick)
        self.calculateImpv()
    
    #----------------------------------------------------------------------
    def newUnderlyingTick(self):
        """标的行情更新"""
        self.underlyingPrice = self.underlying.midPrice
        
        self.calculateImpv()
        self.calculateTheoGreeks()
        self.calculatePosGreeks()
        
    #----------------------------------------------------------------------
    def newTrade(self, trade):
        """成交更新"""
        super(OmOption, self).newTrade(trade)
        self.calculatePosGreeks()
    
    #----------------------------------------------------------------------
    def newPos(self, pos):
        """持仓更新"""
        super(OmOption, self).newPos(pos)
        self.calculatePosGreeks()
    
    #----------------------------------------------------------------------
    def init(self, contract, underlying, interestRate):
        """初始化"""
        super(OmOption, self).init(contract)
        
        self.underlying = underlying
        self.strike = contract.strikePrice
        self.interestRate = interestRate
        
        # 计算到期剩余时间（年化）
        self.expiryDate = contract.expiryDate
        self.expiryTime = calculateExpiryTime(self.expiryDate)
        
        # 转换期权类型
        if contract.optionType is OPTION_CALL:
            self.optionType = 1
        else:
            self.optionType = -1
            
        self.gatewayName = contract.gatewayName
        
    #----------------------------------------------------------------------
    def calculateImpv(self):
        """计算隐含波动率"""
        if not self.underlyingPrice:
            return        
        
        self.askImpv = self.impvFormula(self.askPrice1, self.underlyingPrice, self.strike,
                                        self.interestRate, self.expiryTime, self.optionType)
        self.bidImpv = self.impvFormula(self.bidPrice1, self.underlyingPrice, self.strike,
                                        self.interestRate, self.expiryTime, self.optionType)
        self.midImpv = (self.askImpv + self.bidImpv) / 2
        #self.pricingImpv = self.midImpv
    
    #----------------------------------------------------------------------
    def calculateTheoGreeks(self):
        """计算理论希腊值"""
        if not self.underlyingPrice or not self.pricingImpv:
            return
        
        result = self.pricingFormula(self.underlyingPrice, self.strike, self.interestRate,
                                     self.expiryTime, self.pricingImpv, self.optionType,
                                     self.size)
        self.theoPrice, self.theoDelta, self.theoGamma, self.theoTheta, self.theoVega = result
        
    #----------------------------------------------------------------------
    def calculatePosGreeks(self):
        """计算持仓希腊值"""
        self.posDelta = self.theoDelta * self.netPos
        self.posGamma = self.theoGamma * self.netPos
        self.posTheta = self.theoTheta * self.netPos
        self.posVega = self.theoVega * self.netPos            


########################################################################
class OmChain(object):
    """期权链"""

    #----------------------------------------------------------------------
    def __init__(self, symbol):
        """Constructor"""
        self.symbol = symbol
        
        # 标的
        self.underlying = None
        
        # 原始容器
        self.callDict = OrderedDict()
        self.putDict = OrderedDict()
        
        # 生成的容器
        self.optionDict = OrderedDict()
        self.optionList = []
        self.callList = []
        self.putList = []
        self.strikeList = []
        
        # 定价数据
        self.interestRate = EMPTY_FLOAT
        self.expiryDate = EMPTY_STRING
        self.expiryTime = EMPTY_FLOAT        
        
        # 持仓数据
        self.longPos = EMPTY_INT
        self.shortPos = EMPTY_INT
        self.netPos = EMPTY_INT
        
        self.posDelta = EMPTY_FLOAT
        self.posGamma = EMPTY_FLOAT
        self.posTheta = EMPTY_FLOAT
        self.posVega = EMPTY_FLOAT
        
    #----------------------------------------------------------------------
    def init(self, underlying, callList, putList):
        """初始化"""
        self.underlying = underlying
        
        # 根据行权价排序期权列表，并生成衍生容器
        self.callList = sorted(callList, key=attrgetter('strike'))
        self.putList = sorted(putList, key=attrgetter('strike'))
        
        self.callDict = OrderedDict([(option.symbol, option) for option in self.callList])
        self.putDict = OrderedDict([(option.symbol, option) for option in self.putList])
        
        self.optionDict.update(self.callDict)
        self.optionDict.update(self.putDict)
        self.optionList = self.optionDict.values()
        
        self.strikeList = [option.strike for option in self.callList]
        
        # 读取数据
        option = self.optionList[0]
        self.interestRate = option.interestRate
        self.expiryDate = option.expiryDate
        self.expiryTime = option.expiryTime
    
    #----------------------------------------------------------------------
    def newTick(self, tick):
        """期权行情更新"""
        option = self.optionDict[tick.symbol]
        option.newTick(tick)
    
    #----------------------------------------------------------------------
    def newUnderlyingTick(self):
        """期货行情更新"""
        for option in self.optionList:
            option.newUnderlyingTick()
            
        self.calculatePosGreeks()
        
    #----------------------------------------------------------------------
    def newTrade(self, trade):
        """期权成交更新"""
        option = self.optionDict[trade.symbol]
        option.newTrade(trade)
        
        self.calculatePosGreeks()
    
    #----------------------------------------------------------------------
    def newPos(self, pos):
        """期权持仓更新"""
        option = self.optionDict[pos.symbol]
        option.newPos(pos)
        
        self.calculatePosGreeks()
    
    #----------------------------------------------------------------------
    def calculatePosGreeks(self):
        """计算持仓希腊值"""
        self.longPos = 0
        self.shortPos = 0
        self.netPos = 0
        self.posDelta = 0
        self.posGamma = 0
        self.posTheta = 0
        self.posVega = 0
        
        for option in self.optionList:
            self.longPos += option.longPos
            self.shortPos += option.shortPos
            
            self.posDelta += option.posDelta
            self.posGamma += option.posGamma
            self.posTheta += option.posTheta
            self.posVega += option.posVega
        
        self.netPos = self.longPos - self.shortPos


########################################################################
class OmPortfolio(object):
    """持仓组合"""

    #----------------------------------------------------------------------
    def __init__(self, name):
        """Constructor"""
        self.name = name
        
        # 原始容器
        self.futuresDict = OrderedDict()
        self.equityDict = OrderedDict()
        self.chainDict = OrderedDict()
        
        # 初始化生成的容器
        self.underlyingDict = OrderedDict()
        self.underlyingList = []
        self.chainList = []
        self.contractDict = {}
        self.optionChainDict = {}   # option symbol: chain object
        self.optionDict = {}        # option symbol: option object
        self.optionList = []
        
        # 持仓数据
        self.longPos = EMPTY_INT
        self.shortPos = EMPTY_INT
        self.netPos = EMPTY_INT
        
        self.posDelta = EMPTY_FLOAT
        self.posGamma = EMPTY_FLOAT
        self.posTheta = EMPTY_FLOAT
        self.posVega = EMPTY_FLOAT
        
    #----------------------------------------------------------------------
    def init(self, futuresDict, equityDict, chainDict):
        """初始化数据结构"""
        self.futuresDict = futuresDict
        self.equityDict = equityDict
        self.chainDict = chainDict
        
        self.underlyingDict.update(self.futuresDict)
        self.underlyingDict.update(self.equityDict)
        self.underlyingList = self.underlyingDict.values()
        self.chainList = chainDict.values()
        
        self.contractDict.update(self.futuresDict)
        self.contractDict.update(self.equityDict)

        for chain in self.chainList:
            self.contractDict.update(chain.callDict)
            self.contractDict.update(chain.putDict)
            
            for option in chain.optionList:
                self.optionChainDict[option.symbol] = chain
                self.optionDict[option.symbol] = option
                self.optionList.append(option)
    
    #----------------------------------------------------------------------
    def calculatePosGreeks(self):
        """计算持仓希腊值"""
        self.longPos = 0
        self.shortPos = 0
        self.netPos = 0
        self.posDelta = 0
        self.posGamma = 0
        self.posTheta = 0
        self.posVega = 0
        
        for underlying in self.underlyingList:
            self.posDelta += underlying.posDelta
        
        for chain in self.chainList:
            self.longPos += chain.longPos
            self.shortPos += chain.shortPos
            
            self.posDelta += chain.posDelta
            self.posGamma += chain.posGamma
            self.posTheta += chain.posTheta
            self.posVega += chain.posVega
        
        self.netPos = self.longPos - self.shortPos        
    
    #----------------------------------------------------------------------
    def newTick(self, tick):
        """行情推送"""
        if tick.symbol in self.optionChainDict:
            chain = self.optionChainDict[tick.symbol]
            chain.newTick(tick)
        elif tick.symbol in self.underlyingDict:
            underlying = self.underlyingDict[tick.symbol]
            underlying.newTick(tick)
            self.calculatePosGreeks()
    
    #----------------------------------------------------------------------
    def newTrade(self, trade):
        """成交推送"""
        if trade.symbol in self.optionChainDict:
            chain = self.optionChainDict[trade.symbol]
            chain.newTrade(trade)
        else:
            underlying = self.underlyingDict[trade.symbol]
            underlying.newTrade(trade)
        self.calculatePosGreeks()
            
    #----------------------------------------------------------------------
    def newPos(self, pos):
        """持仓推送"""
        if pos.symbol in self.optionChainDict:
            chain = self.optionChainDict[pos.symbol]
            chain.newPos(pos)
        elif pos.symbol in self.underlyingDict:
            underlying = self.underlyingDict[pos.symbol]
            underlying.newPos(pos)    
        self.calculatePosGreeks()
    
    