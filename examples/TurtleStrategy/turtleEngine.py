# encoding: UTF-8

from csv import DictReader
from datetime import datetime

from pymongo import MongoClient
from collections import OrderedDict, defaultdict

from vnpy.trader.vtObject import VtBarData
from vnpy.trader.vtConstant import DIRECTION_LONG, DIRECTION_SHORT

from turtleStrategy import TurtlePortfolio


DAILY_DB_NAME = 'VnTrader_Daily_Db'


SIZE_DICT = {}
PRICETICK_DICT = {}
VARIABLE_COMMISSION_DICT = {}
FIXED_COMMISSION_DICT = {}
SLIPPAGE_DICT = {}



########################################################################
class BacktestingEngine(object):
    """"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.portfolio = None
        
        # 合约配置信息
        self.vtSymbolList = []
        self.sizeDict = {}                  # 合约大小字典
        self.priceTickDict = {}             # 最小价格变动字典
        self.variableCommissionDict = {}    # 变动手续费字典
        self.fixedCommissionDict = {}       # 固定手续费字典
        self.slippageDict = {}              # 滑点成本字典
        
        self.startDt = None
        self.endDt = None
        self.currentDt = None
        
        self.dataDict = OrderedDict()
        self.tradeDict = OrderedDict()
        
        self.result = None
        self.resultList = []
    
    #----------------------------------------------------------------------
    def setPeriod(self, startDt, endDt):
        """"""
        self.startDt = startDt
        self.endDt = endDt
    
    #----------------------------------------------------------------------
    def initPortfolio(self, filename, portfolioValue=10000000):
        """"""
        with open(filename) as f:
            r = DictReader(f)
            for d in r:
                self.vtSymbolList.append(d['vtSymbol'])
                
                SIZE_DICT[d['vtSymbol']] = int(d['size'])
                PRICETICK_DICT[d['vtSymbol']] = float(d['priceTick'])
                VARIABLE_COMMISSION_DICT[d['vtSymbol']] = float(d['variableCommission'])
                FIXED_COMMISSION_DICT[d['vtSymbol']] = float(d['fixedCommission'])
                SLIPPAGE_DICT[d['vtSymbol']] = float(d['slippage'])
            
        self.portfolio = TurtlePortfolio(self)
        self.portfolio.init(portfolioValue, self.vtSymbolList, SIZE_DICT)
        
        self.writeLog(u'投资组合的合约代码%s' %(self.vtSymbolList))
        self.writeLog(u'投资组合的初始价值%s' %(portfolioValue))
    
    #----------------------------------------------------------------------
    def loadData(self):
        """"""
        mc = MongoClient()
        db = mc[DAILY_DB_NAME]
        
        for vtSymbol in self.vtSymbolList:
            flt = {'datetime':{'$gte':self.startDt,
                               '$lte':self.endDt}} 
            
            collection = db[vtSymbol]
            cursor = collection.find(flt).sort('datetime')
            
            for d in cursor:
                bar = VtBarData()
                bar.__dict__ = d
                
                barDict = self.dataDict.setdefault(bar.datetime, OrderedDict())
                barDict[bar.vtSymbol] = bar
            
            self.writeLog(u'%s数据加载完成，总数据量：%s' %(vtSymbol, cursor.count()))
        
        self.writeLog(u'全部数据加载完成')
    
    #----------------------------------------------------------------------
    def runBacktesting(self):
        """"""
        self.writeLog(u'开始回放K线数据')
        
        for dt, barDict in self.dataDict.items():
            self.currentDt = dt
            
            previousResult = self.result
            
            self.result = DailyResult(dt)
            self.result.updatePos(self.portfolio.posDict)
            self.resultList.append(self.result)
            
            if previousResult:
                self.result.updatePreviousClose(previousResult.closeDict)
            
            for bar in barDict.values():
                self.portfolio.onBar(bar)
                self.result.updateBar(bar)
        
        self.writeLog(u'K线数据回放结束')
    
    #----------------------------------------------------------------------
    def calculateResult(self):
        """"""
        self.writeLog(u'开始统计回测结果')
        
        for result in self.resultList:
            result.calculatePnl()
        
        self.writeLog(u'回测结果统计结束')
    
    #----------------------------------------------------------------------
    def sendOrder(self, vtSymbol, direction, offset, price, volume):
        """"""
        # 对价格四舍五入
        priceTick = PRICETICK_DICT[vtSymbol]
        price = int(round(price/priceTick, 0)) * priceTick
        
        # 记录成交数据
        trade = TradeData(vtSymbol, direction, offset, price, volume)
        l = self.tradeDict.setdefault(self.currentDt, [])        
        l.append(trade)
        
        self.result.updateTrade(trade)

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """"""
        print '%s:\t%s' %(datetime.now().strftime('%H:%M:%S.%f'), content)
    
    
########################################################################
class TradeData(object):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, vtSymbol, direction, offset, price, volume):
        """Constructor"""
        self.vtSymbol = vtSymbol
        self.direction = direction
        self.offset = offset
        self.price = price
        self.volume = volume


########################################################################
class DailyResult(object):
    """每日的成交记录"""

    #----------------------------------------------------------------------
    def __init__(self, date):
        """Constructor"""
        self.date = date
        
        self.closeDict = {}                     # 收盘价字典
        self.previousCloseDict = {}             # 昨收盘字典
        
        self.tradeDict = defaultdict(list)      # 成交字典
        self.posDict = {}                       # 持仓字典（开盘时）
        
        self.tradingPnl = 0
        self.holdingPnl = 0
        self.totalPnl = 0
    
    #----------------------------------------------------------------------
    def updateTrade(self, trade):
        """更新交易"""
        l = self.tradeDict[trade.vtSymbol]
        l.append(trade)
        
    #----------------------------------------------------------------------
    def updatePos(self, d):
        """更新昨持仓"""
        self.posDict.update(d)
    
    #----------------------------------------------------------------------
    def updateBar(self, bar):
        """更新K线"""
        self.closeDict[bar.vtSymbol] = bar.close
    
    #----------------------------------------------------------------------
    def updatePreviousClose(self, d):
        """更新昨收盘"""
        self.previousCloseDict.update(d)

    #----------------------------------------------------------------------
    def calculateTradingPnl(self):
        """计算当日交易盈亏"""
        for vtSymbol, l in self.tradeDict.items():
            close = self.closeDict[vtSymbol]
            size = SIZE_DICT[vtSymbol]
            
            slippage = SLIPPAGE_DICT[vtSymbol]
            variableCommission = VARIABLE_COMMISSION_DICT[vtSymbol]
            fixedCommission = FIXED_COMMISSION_DICT[vtSymbol]
            
            for trade in l:
                if trade.direction == DIRECTION_LONG:
                    side = 1
                else:
                    side = -1
                
                commissionCost = (trade.volume * fixedCommission + 
                                  trade.volume * trade.price * variableCommission)
                slippageCost = trade.volume * slippage
                    
                pnl = (close - trade.price) * trade.volume * side * size
                pnl -= (commissionCost + slippageCost)
                self.tradingPnl += pnl
    
    #----------------------------------------------------------------------
    def calculateHoldingPnl(self):
        """计算当日持仓盈亏"""
        for vtSymbol, pos in self.posDict.items():
            previousClose = self.previousCloseDict.get(vtSymbol, 0)
            close = self.closeDict[vtSymbol]
            size = SIZE_DICT[vtSymbol]
            
            pnl = (close - previousClose) * pos * size
            self.holdingPnl += pnl

    #----------------------------------------------------------------------
    def calculatePnl(self):
        """计算总盈亏"""
        self.calculateHoldingPnl()
        self.calculateTradingPnl()
        self.totalPnl = self.holdingPnl + self.tradingPnl
        