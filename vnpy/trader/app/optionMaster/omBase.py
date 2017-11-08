# encoding: UTF-8

from collections import OrderedDict

from vnpy.trader.vtConstant import *
from vnpy.trader.vtObject import VtTickData


########################################################################
class OmInstrument(VtTickData):
    """交易合约对象"""

    #----------------------------------------------------------------------
    def __init__(self, contract):
        """Constructor"""
        super(OmInstrument, self).__init__()
        
        # 初始化合约信息
        self.exchange = contract.exchange
        self.vtSymbol = contract.vtSymbol
    
        self.size = contract.size
        self.priceTick = contract.priceTick
        self.gatewayName = contract.gatewayName
        
        # 中间价
        self.midPrice = EMPTY_FLOAT
        
        # 持仓数据
        self.longPos = EMPTY_INT
        self.shortPos = EMPTY_INT
        self.netPos = EMPTY_INT
        
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
        
        self.bidPrice1 = tick.bidPrice1
        self.askPrice1 = tick.askPrice1
        self.bidVolume1 = tick.bidVolume1
        self.askVolume1 = tick.askVolume1

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
                
        self.calculateNetPos()
    
    #----------------------------------------------------------------------
    def newPos(self, pos):
        """持仓更新"""
        if pos.direction is DIRECTION_LONG:
            self.longPos = pos.position
        else:
            self.shortPos = pos.position
            
        self.calculateNetPos()
        
    #----------------------------------------------------------------------
    def calculateNetPos(self):
        """计算净持仓"""
        self.netPos = self.longPos - self.shortPos    


########################################################################
class OmUnderlying(OmInstrument):
    """标的物"""

    #----------------------------------------------------------------------
    def __init__(self, contract, chainList):
        """Constructor"""
        super(OmUnderlying, self).__init__(contract)
        
        # 以该合约为标的物的期权链字典
        self.chainDict = OrderedDict((chain.symbol, chain) for chain in chainList)
        
        # 希腊值
        self.theoDelta = EMPTY_FLOAT    # 理论delta值
        self.posDelta = EMPTY_FLOAT     # 持仓delta值
        
    #----------------------------------------------------------------------
    def newTick(self, tick):
        """行情更新"""
        super(OmUnderlying, self).newTick(tick)
        
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
        
    #----------------------------------------------------------------------
    def calculatePosGreeks(self):
        """计算持仓希腊值"""
        self.posDelta = self.theoDelta * self.netPos    


########################################################################
class OmEquity(OmUnderlying):
    """股票"""

    #----------------------------------------------------------------------
    def __init__(self, contract, chainList):
        """Constructor"""
        super(OmEquity, self).__init__(contract, chainList)


########################################################################
class OmFutures(OmUnderlying):
    """期货"""

    #----------------------------------------------------------------------
    def __init__(self, contract, chainList):
        """Constructor"""
        super(OmFutures, self).__init__(contract, chainList)



    
    