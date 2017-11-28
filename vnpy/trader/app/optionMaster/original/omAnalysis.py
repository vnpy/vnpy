# encoding: UTF-8

from __future__ import division

import numpy as np

from eventType import *
from vtConstant import *
from omPricing import calculateGreeks


########################################################################
class AnalysisEngine(object):
    """
    期权组合分析引擎
    主要分析和期权相关的情况
    """

    #----------------------------------------------------------------------
    def __init__(self, omEngine):
        """Constructor"""
        self.omEngine = omEngine
        self.eventEngine = omEngine.eventEngine

        self.portfolio = None

        # 期权合约代码集合
        self.optionSymbolSet = set()

        # 帐户信息
        self.account = None
        
        # 期权成交统计
        self.optionTradeCount = 0    # 成交量
        self.optionOpenCount = 0     # 开仓量
        self.optionCloseCount = 0    # 平仓量
        
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def init(self):
        """"""
        self.portfolio = self.omEngine.portfolio
        
    #----------------------------------------------------------------------
    def calculateMarketValue(self):
        """计算期权持仓市值"""
        if not self.portfolio:
            self.portfolio = self.omEngine.portfolio
            
        marketValue = 0
        
        for option in self.portfolio.optionList:
            option.midPrice = (option.bidPrice1 + option.askPrice1) / 2
            optionMarketValue = option.netPos * option.midPrice * option.size
            marketValue += optionMarketValue
    
        return marketValue
    
    #----------------------------------------------------------------------
    def getTradeCount(self):
        """获取成交统计数据"""
        return self.optionTradeCount, self.optionOpenCount, self.optionCloseCount
    
    #----------------------------------------------------------------------
    def getAccountMarketValue(self):
        """获取帐户市值信息"""
        if not self.account:
            return None, None
        
        account = self.account
        balance = account.balance
        
        # 针对飞创提供了期权估值
        if account.balance != account.marketValue:
            accountMarketValue = account.marketValue
        else:
            positionMarketValue = self.calculateMarketValue()
            accountMarketValue = account.balance + positionMarketValue
            print account.balance, positionMarketValue
        
        # 计算风险度
        riskLevel = account.margin / balance
        
        return accountMarketValue, riskLevel

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)
        self.eventEngine.register(EVENT_ACCOUNT, self.processAccountEvent)
        self.eventEngine.register(EVENT_CONTRACT, self.processContractEvent)
    
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """"""
        trade = event.dict_['data']
        if trade.symbol not in self.optionSymbolSet:
            return
        
        if trade.offset is OFFSET_OPEN:
            self.optionOpenCount += trade.volume
        else:
            self.optionCloseCount += trade.volume
        self.optionTradeCount += trade.volume
        
    #----------------------------------------------------------------------
    def processContractEvent(self, event):
        """"""
        contract = event.dict_['data']
        
        if contract.productClass is PRODUCT_OPTION:
            self.optionSymbolSet.add(contract.symbol)
            
    #----------------------------------------------------------------------
    def processAccountEvent(self, event):
        """"""
        self.account = event.dict_['data']
        
    #----------------------------------------------------------------------
    def generateRiskReport(self):
        """输出csv格式的风险报告"""
        pass
        
    #----------------------------------------------------------------------
    def runScenarioAnalysis(self):
        """运行情景分析"""
        portfolio = self.portfolio
        if not portfolio:
            return None, None, None
        
        changeRange = 10
        priceChangeArray = np.arange(-changeRange, changeRange+1) / 100
        impvChangeArray = np.arange(-changeRange, changeRange+1) / 100
        expiryChange = 1/240    # 一个交易日对应的时间变化
        result = {}     # 分析结果
        
        for priceChange in priceChangeArray:
            for impvChange in impvChangeArray:
                portfolioPnl = 0
                portfolioDelta = 0
                portfolioGamma = 0
                portfolioTheta = 0
                portfolioVega = 0
                
                for underlying in portfolio.underlyingList:
                    portfolioPnl += underlying.midPrice * underlying.netPos * priceChange
                    portfolioDelta += underlying.theoDelta * underlying.netPos
                    
                try:
                    for option in portfolio.optionList:
                        price, delta, gamma, theta, vega = calculateGreeks(option.underlying.midPrice*(1+priceChange),
                                                                           option.strike,
                                                                           option.interestRate,
                                                                           max(option.expiryTime-expiryChange, 0),
                                                                           option.pricingImpv*(1+impvChange),
                                                                           option.optionType,
                                                                           option.size)
                        
                        portfolioPnl += (price - option.theoPrice) * option.netPos
                        portfolioDelta += delta * option.netPos
                        portfolioGamma += gamma * option.netPos
                        portfolioTheta += theta * option.netPos
                        portfolioVega += vega * option.netPos
                except ZeroDivisionError:
                    return None, None, None
                
                d = {
                    'pnl': portfolioPnl,
                    'delta': portfolioDelta,
                    'gamma': portfolioGamma,
                    'theta': portfolioTheta,
                    'vega': portfolioVega
                }
                result[(priceChange, impvChange)] = d
        
        return result, priceChangeArray, impvChangeArray
    
    