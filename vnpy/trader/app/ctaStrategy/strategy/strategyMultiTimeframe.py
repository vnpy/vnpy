# encoding: UTF-8

"""
一个跨时间周期的策略，基于15分钟K线判断趋势方向，并使用5分钟RSI指标作为入场
"""

from vnpy.trader.vtObject import VtBarData
from vnpy.trader.vtConstant import EMPTY_STRING
from vnpy.trader.app.ctaStrategy.ctaTemplate import (CtaTemplate, 
                                                     BarGenerator, 
                                                     ArrayManager)


########################################################################
class MultiTimeframeStrategy(CtaTemplate):
    """跨时间周期交易策略"""
    className = 'MultiTimeframeStrategy'
    author = u'用Python的交易员'

    # 策略参数
    rsiSignal = 20          # RSI信号阈值
    rsiWindow = 14          # RSI窗口
    fastWindow = 5          # 快速均线窗口
    slowWindow = 20         # 慢速均线窗口
    
    initDays = 10           # 初始化数据所用的天数
    fixedSize = 1           # 每次交易的数量

    # 策略变量
    rsiValue = 0                        # RSI指标的数值
    rsiLong = 0                         # RSI买开阈值
    rsiShort = 0                        # RSI卖开阈值
    fastMa = 0                          # 5分钟快速均线
    slowMa = 0                          # 5分钟慢速均线
    maTrend = 0                         # 均线趋势，多头1，空头-1
    
    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol',
                 'rsiSignal',
                 'rsiWindow',
                 'fastWindow',
                 'slowWindow']    

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos',
               'rsiValue',
               'rsiLong',
               'rsiShort',
               'fastMa',
               'slowMa',
               'maTrend']  
    
    # 同步列表，保存了需要保存到数据库的变量名称
    syncList = ['pos']

    #----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(MultiTimeframeStrategy, self).__init__(ctaEngine, setting)
        
        self.rsiLong = 50 + self.rsiSignal
        self.rsiShort = 50 - self.rsiSignal
        
        # 创建K线合成器对象
        self.bg5 = BarGenerator(self.onBar, 5, self.on5MinBar)
        self.am5 = ArrayManager()
        
        self.bg15 = BarGenerator(self.onBar, 15, self.on15MinBar)
        self.am15 = ArrayManager()
        
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
        # 只需要要在一个BarGenerator中合成1分钟K线
        self.bg5.updateTick(tick)

    #----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        # 基于15分钟判断趋势过滤，因此先更新
        self.bg15.updateBar(bar)
        
        # 基于5分钟判断
        self.bg5.updateBar(bar)
        
    #----------------------------------------------------------------------
    def on5MinBar(self, bar):
        """5分钟K线"""
        self.cancelAll()

        # 保存K线数据
        self.am5.updateBar(bar)
        if not self.am5.inited:
            return
        
        # 如果15分钟数据尚未初始化完毕，则直接返回
        if not self.maTrend:
            return

        # 计算指标数值
        self.rsiValue = self.am5.rsi(self.rsiWindow)

        # 判断是否要进行交易
        
        # 当前无仓位
        if self.pos == 0:
            if self.maTrend > 0 and self.rsiValue >= self.rsiLong:
                self.buy(bar.close+5, self.fixedSize)
                
            elif self.maTrend < 0 and self.rsiValue <= self.rsiShort:
                self.short(bar.close-5, self.fixedSize)

        # 持有多头仓位
        elif self.pos > 0:
            if self.maTrend < 0 or self.rsiValue < 50:
                self.sell(bar.close-5, abs(self.pos))
            
        # 持有空头仓位
        elif self.pos < 0:
            if self.maTrend > 0 or self.rsiValue > 50:
                self.cover(bar.close+5, abs(self.pos))

        # 发出状态更新事件
        self.putEvent()        
    
    #----------------------------------------------------------------------
    def on15MinBar(self, bar):
        """15分钟K线推送"""
        self.am15.updateBar(bar)
        
        if not self.am15.inited:
            return
        
        # 计算均线并判断趋势
        self.fastMa = self.am15.sma(self.fastWindow)
        self.slowMa = self.am15.sma(self.slowWindow)
        
        if self.fastMa > self.slowMa:
            self.maTrend = 1
        else:
            self.maTrend = -1

    #----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        pass

    #----------------------------------------------------------------------
    def onTrade(self, trade):
        # 发出状态更新事件
        self.putEvent()

    #----------------------------------------------------------------------
    def onStopOrder(self, so):
        """停止单推送"""
        pass