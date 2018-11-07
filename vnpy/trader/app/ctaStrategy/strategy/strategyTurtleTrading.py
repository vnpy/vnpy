# encoding: UTF-8

"""
单标的海龟交易策略，实现了完整海龟策略中的信号部分。
"""

from __future__ import division

from vnpy.trader.vtObject import VtBarData
from vnpy.trader.vtConstant import DIRECTION_LONG, DIRECTION_SHORT
from vnpy.trader.app.ctaStrategy.ctaTemplate import (CtaTemplate, 
                                                     BarGenerator, 
                                                     ArrayManager)


########################################################################
class TurtleTradingStrategy(CtaTemplate):
    """海龟交易策略"""
    className = 'TurtleTradingStrategy'
    author = u'用Python的交易员'

    # 策略参数
    entryWindow = 55                    # 入场通道窗口
    exitWindow = 20                     # 出场通道窗口
    atrWindow = 20                      # 计算ATR波动率的窗口
    initDays = 10                       # 初始化数据所用的天数
    fixedSize = 1                       # 每次交易的数量

    # 策略变量
    entryUp = 0                         # 入场通道上轨
    entryDown = 0                       # 入场通道下轨
    exitUp = 0                          # 出场通道上轨
    exitDown = 0                        # 出场通道下轨
    atrVolatility = 0                   # ATR波动率
    
    longEntry = 0                       # 多头入场价格
    shortEntry = 0                      # 空头入场价格
    longStop = 0                        # 多头止损价格
    shortStop = 0                       # 空头止损价格
    
    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol',
                 'entryWindow',
                 'exitWindow',
                 'atrWindow',
                 'initDays',
                 'fixedSize']    

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos',
               'entryUp',
               'entryDown',
               'exitUp',
               'exitDown',
               'longEntry',
               'shortEntry',
               'longStop',
               'shortStop']  
    
    # 同步列表，保存了需要保存到数据库的变量名称
    syncList = ['pos']

    #----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(TurtleTradingStrategy, self).__init__(ctaEngine, setting)
        
        self.bg = BarGenerator(self.onBar)
        self.am = ArrayManager()
        
    #----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        self.writeCtaLog(u'%s策略初始化' %self.name)
        
        # 载入历史数据，并采用回放计算的方式初始化策略数值
        initData = self.loadBar(self.initDays)
        for bar in initData:
            self.onBar(bar)

        self.putEvent()

    #----------------------------------------------------------------------
    def onStart(self):
        """启动策略（必须由用户继承实现）"""
        self.writeCtaLog(u'%s策略启动' %self.name)
        self.putEvent()

    #----------------------------------------------------------------------
    def onStop(self):
        """停止策略（必须由用户继承实现）"""
        self.writeCtaLog(u'%s策略停止' %self.name)
        self.putEvent()

    #----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送（必须由用户继承实现）""" 
        self.bg.updateTick(tick)

    #----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        self.cancelAll()
    
        # 保存K线数据
        self.am.updateBar(bar)
        if not self.am.inited:
            return
        
        # 计算指标数值
        self.entryUp, self.entryDown = self.am.donchian(self.entryWindow)
        self.exitUp, self.exitDown = self.am.donchian(self.exitWindow)
        self.atrVolatility = self.am.atr(self.atrWindow)
        
        # 判断是否要进行交易
        if self.pos == 0:
            self.longEntry = 0
            self.shortEntry = 0
            self.longStop = 0
            self.shortStop = 0
            
            self.sendBuyOrders(self.entryUp)
            self.sendShortOrders(self.entryDown)
    
        elif self.pos > 0:
            # 加仓逻辑
            self.sendBuyOrders(self.longEntry)
            
            # 止损逻辑
            self.longStop = self.longEntry - self.atrVolatility * 2
            self.longStop = max(self.longStop, self.exitDown)
            self.sell(self.longStop, abs(self.pos), True)
    
        elif self.pos < 0:
            # 加仓逻辑
            self.sendShortOrders(self.shortEntry)
            
            # 止损逻辑
            self.shortStop = self.shortEntry + self.atrVolatility * 2
            self.shortStop = min(self.shortStop, self.exitUp)
            self.cover(self.shortStop, abs(self.pos), True)
            
        # 同步数据到数据库
        self.saveSyncData()        
    
        # 发出状态更新事件
        self.putEvent()        

    #----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        pass

    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """成交推送"""
        if trade.direction == DIRECTION_LONG:
            self.longEntry = trade.price
        else:
            self.shortEntry = trade.price
        
        # 发出状态更新事件
        self.putEvent()

    #----------------------------------------------------------------------
    def onStopOrder(self, so):
        """停止单推送"""
        pass
    
    #----------------------------------------------------------------------
    def sendBuyOrders(self, price):
        """发出一系列的买入停止单"""
        t = self.pos / self.fixedSize
        
        if t < 1:
            self.buy(price, self.fixedSize, True)

        if t < 2:
            self.buy(price + self.atrVolatility*0.5, self.fixedSize, True)
                
        if t < 3:
            self.buy(price + self.atrVolatility, self.fixedSize, True)

        if t < 4:
            self.buy(price + self.atrVolatility*1.5, self.fixedSize, True)    
    
    #----------------------------------------------------------------------
    def sendShortOrders(self, price):
        """"""
        t = self.pos / self.fixedSize
        
        if t > -1:
            self.short(price, self.fixedSize, True)
        
        if t > -2:
            self.short(price - self.atrVolatility*0.5, self.fixedSize, True)
    
        if t > -3:
            self.short(price - self.atrVolatility, self.fixedSize, True)
    
        if t > -4:
            self.short(price - self.atrVolatility*1.5, self.fixedSize, True)            
        
