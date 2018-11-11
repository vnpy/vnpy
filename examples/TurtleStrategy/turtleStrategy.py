# encoding: UTF-8

from collections import defaultdict

from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT,
                                    OFFSET_OPEN, OFFSET_CLOSE)
from vnpy.trader.vtUtility import ArrayManager


MAX_PRODUCT_POS = 4         # 单品种最大持仓
MAX_DIRECTION_POS = 10      # 单方向最大持仓


########################################################################
class TurtleResult(object):
    """一次完整的开平交易"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.pos = 0
        self.entry = 0                  # 开仓均价
        self.exit = 0                   # 平仓均价
        self.pnl = 0                    # 盈亏
    
    #----------------------------------------------------------------------
    def open(self, price, change):
        """开仓或者加仓"""
        cost = self.pos * self.entry    # 计算之前的开仓成本
        cost += change * price          # 加上新仓位的成本
        self.pos += change              # 加上新仓位的数量
        self.entry = cost / self.pos    # 计算新的平均开仓成本
    
    #----------------------------------------------------------------------
    def close(self, price):
        """平仓"""
        self.exit = price
        self.pnl = self.pos * (self.exit - self.entry)
    

########################################################################
class TurtleSignal(object):
    """海龟信号"""

    #----------------------------------------------------------------------
    def __init__(self, portfolio, vtSymbol, 
                 entryWindow, exitWindow, atrWindow,
                 profitCheck=False):
        """Constructor"""
        self.portfolio = portfolio      # 投资组合
        
        self.vtSymbol = vtSymbol        # 合约代码
        self.entryWindow = entryWindow  # 入场通道周期数
        self.exitWindow = exitWindow    # 出场通道周期数
        self.atrWindow = atrWindow      # 计算ATR周期数
        self.profitCheck = profitCheck  # 是否检查上一笔盈利
        
        self.am = ArrayManager(60)      # K线容器
        
        self.atrVolatility = 0          # ATR波动率
        self.entryUp = 0                # 入场通道
        self.entryDown = 0
        self.exitUp = 0                 # 出场通道
        self.exitDown = 0
        
        self.longEntry1 = 0             # 多头入场位
        self.longEntry2 = 0
        self.longEntry3 = 0
        self.longEntry4 = 0
        self.longStop = 0               # 多头止损位
        
        self.shortEntry1 = 0            # 空头入场位
        self.shortEntry2 = 0
        self.shortEntry3 = 0
        self.shortEntry4 = 0
        self.shortStop = 0              # 空头止损位
        
        self.pos = 0                    # 信号持仓
        self.result = None              # 当前的交易
        self.resultList = []            # 交易列表
        self.bar = None                 # 最新K线
        
    #----------------------------------------------------------------------
    def onBar(self, bar):
        """"""
        self.bar = bar
        self.am.updateBar(bar)
        if not self.am.inited:
            return
        
        self.generateSignal(bar)
        self.calculateIndicator()
        
    #----------------------------------------------------------------------
    def generateSignal(self, bar):
        """
        判断交易信号
        要注意在任何一个数据点：buy/sell/short/cover只允许执行一类动作
        """
        # 如果指标尚未初始化，则忽略
        if not self.longEntry1:
            return
        
        # 优先检查平仓
        if self.pos > 0:
            longExit = max(self.longStop, self.exitDown)
            if bar.low <= longExit:
                self.sell(longExit)
                return
        elif self.pos < 0:
            shortExit = min(self.shortStop, self.exitUp)
            if bar.high >= shortExit:
                self.cover(shortExit)
                return

        # 没有仓位或者持有多头仓位的时候，可以做多（加仓）
        if self.pos >= 0:
            trade = False
            
            if bar.high >= self.longEntry1 and self.pos < 1:
                self.buy(self.longEntry1, 1)
                trade = True
            
            if bar.high >= self.longEntry2 and self.pos < 2:
                self.buy(self.longEntry2, 1)
                trade = True
            
            if bar.high >= self.longEntry3 and self.pos < 3:
                self.buy(self.longEntry3, 1)
                trade = True
            
            if bar.high >= self.longEntry4 and self.pos < 4:
                self.buy(self.longEntry4, 1)
                trade = True
            
            if trade:
                return
            
        # 没有仓位或者持有空头仓位的时候，可以做空（加仓）
        if self.pos <= 0:
            if bar.low <= self.shortEntry1 and self.pos > -1:
                self.short(self.shortEntry1, 1)
            
            if bar.low <= self.shortEntry2 and self.pos > -2:
                self.short(self.shortEntry2, 1)
            
            if bar.low <= self.shortEntry3 and self.pos > -3:
                self.short(self.shortEntry3, 1)
            
            if bar.low <= self.shortEntry4 and self.pos > -4:
                self.short(self.shortEntry4, 1)
            
    #----------------------------------------------------------------------
    def calculateIndicator(self):
        """计算技术指标"""
        self.entryUp, self.entryDown = self.am.donchian(self.entryWindow)
        self.exitUp, self.exitDown = self.am.donchian(self.exitWindow)
        
        # 有持仓后，ATR波动率和入场位等都不再变化
        if not self.pos:
            self.atrVolatility = self.am.atr(self.atrWindow)
            
            self.longEntry1 = self.entryUp
            self.longEntry2 = self.entryUp + self.atrVolatility * 0.5
            self.longEntry3 = self.entryUp + self.atrVolatility * 1
            self.longEntry4 = self.entryUp + self.atrVolatility * 1.5
            
            self.shortEntry1 = self.entryDown
            self.shortEntry2 = self.entryDown - self.atrVolatility * 0.5
            self.shortEntry3 = self.entryDown - self.atrVolatility * 1
            self.shortEntry4 = self.entryDown - self.atrVolatility * 1.5
    
    #----------------------------------------------------------------------
    def newSignal(self, direction, offset, price, volume):
        """"""
        self.portfolio.newSignal(self, direction, offset, price, volume)
    
    #----------------------------------------------------------------------
    def buy(self, price, volume):
        """买入开仓"""
        price = self.calculateTradePrice(DIRECTION_LONG, price)
        
        self.open(price, volume)
        self.newSignal(DIRECTION_LONG, OFFSET_OPEN, price, volume)
        
        # 以最后一次加仓价格，加上两倍N计算止损
        self.longStop = price - self.atrVolatility * 2
    
    #----------------------------------------------------------------------
    def sell(self, price):
        """卖出平仓"""
        price = self.calculateTradePrice(DIRECTION_SHORT, price)
        volume = abs(self.pos)
        
        self.close(price)
        self.newSignal(DIRECTION_SHORT, OFFSET_CLOSE, price, volume)
    
    #----------------------------------------------------------------------
    def short(self, price, volume):
        """卖出开仓"""
        price = self.calculateTradePrice(DIRECTION_SHORT, price)
        
        self.open(price, -volume)
        self.newSignal(DIRECTION_SHORT, OFFSET_OPEN, price, volume)
        
        # 以最后一次加仓价格，加上两倍N计算止损
        self.shortStop = price + self.atrVolatility * 2
    
    #----------------------------------------------------------------------
    def cover(self, price):
        """买入平仓"""
        price = self.calculateTradePrice(DIRECTION_LONG, price)
        volume = abs(self.pos)
        
        self.close(price)
        self.newSignal(DIRECTION_LONG, OFFSET_CLOSE, price, volume)

    #----------------------------------------------------------------------
    def open(self, price, change):
        """开仓"""
        self.pos += change 
        
        if not self.result:
            self.result = TurtleResult()
        self.result.open(price, change)
    
    #----------------------------------------------------------------------
    def close(self, price):
        """平仓"""
        self.pos = 0
        
        self.result.close(price)
        self.resultList.append(self.result)
        self.result = None

    #----------------------------------------------------------------------
    def getLastPnl(self):
        """获取上一笔交易的盈亏"""
        if not self.resultList:
            return 0
        
        result = self.resultList[-1]
        return result.pnl
    
    #----------------------------------------------------------------------
    def calculateTradePrice(self, direction, price):
        """计算成交价格"""
        # 买入时，停止单成交的最优价格不能低于当前K线开盘价
        if direction == DIRECTION_LONG:
            tradePrice = max(self.bar.open, price)
        # 卖出时，停止单成交的最优价格不能高于当前K线开盘价
        else:
            tradePrice = min(self.bar.open, price)
        
        return tradePrice
        


########################################################################
class TurtlePortfolio(object):
    """海龟组合"""

    #----------------------------------------------------------------------
    def __init__(self, engine):
        """Constructor"""
        self.engine = engine
        
        self.signalDict = defaultdict(list)
        
        self.posDict = {}       # 每个品种的持仓情况
        self.totalLong = 0      # 总的多头持仓
        self.totalShort = 0     # 总的空头持仓
        
        self.tradingDict = {}   # 交易中的信号字典
    
    #----------------------------------------------------------------------
    def init(self, vtSymbolList):
        """"""
        for vtSymbol in vtSymbolList:
            signal1 = TurtleSignal(self, vtSymbol, 20, 10, 20, True)
            signal2 = TurtleSignal(self, vtSymbol, 55, 20, 20, False)
            
            l = self.signalDict[vtSymbol]
            l.append(signal1)
            l.append(signal2)
            
            self.posDict[vtSymbol] = 0
    
    #----------------------------------------------------------------------
    def onBar(self, bar):
        """"""
        for signal in self.signalDict[bar.vtSymbol]:
            signal.onBar(bar)
    
    #----------------------------------------------------------------------
    def newSignal(self, signal, direction, offset, price, volume):
        """对交易信号进行过滤，符合条件的才发单执行"""
        pos = self.posDict[signal.vtSymbol]
        
        # 开仓
        if offset == OFFSET_OPEN:
            # 检查上一次是否为盈利
            if signal.profitCheck:
                pnl = signal.getLastPnl()
                if pnl > 0:
                    return
                
            # 买入
            if direction == DIRECTION_LONG:
                # 组合持仓不能超过上限
                if self.totalLong >= MAX_DIRECTION_POS:
                    return
                
                # 单品种持仓不能超过上限
                if self.posDict[signal.vtSymbol] >= MAX_PRODUCT_POS:
                    return
            # 卖出
            else:
                if self.totalShort <= -MAX_DIRECTION_POS:
                    return
                
                if self.posDict[signal.vtSymbol] <= -MAX_PRODUCT_POS:
                    return
        # 平仓
        else:
            if direction == DIRECTION_LONG:
                # 必须有空头持仓
                if pos >= 0:
                    return
                
                # 平仓数量不能超过空头持仓
                volume = min(volume, abs(pos))
            else:
                if pos <= 0:
                    return
                
                volume = min(volume, abs(pos))
        
        # 获取当前交易中的信号，如果不是本信号，则忽略
        currentSignal = self.tradingDict.get(signal.vtSymbol, None)
        if currentSignal and currentSignal is not signal:
            return
            
        # 开仓则缓存该信号的交易状态
        if offset == OFFSET_OPEN:
            self.tradingDict[signal.vtSymbol] = signal
        # 平仓则清除该信号
        else:
            self.tradingDict.pop(signal.vtSymbol)
        
        self.sendOrder(signal.vtSymbol, direction, offset, price, volume)
    
    #----------------------------------------------------------------------
    def sendOrder(self, vtSymbol, direction, offset, price, volume):
        """"""
        # 计算合约持仓
        if direction == DIRECTION_LONG:
            self.posDict[vtSymbol] += volume
        else:
            self.posDict[vtSymbol] -= volume
        
        # 计算总持仓
        self.totalLong = 0
        self.totalShort = 0
        
        for pos in self.posDict.values():
            if pos > 0:
                self.totalLong += pos
            elif pos < 0:
                self.totalShort += pos
        
        # 向回测引擎中发单记录
        self.engine.sendOrder(vtSymbol, direction, offset, price, volume)
    