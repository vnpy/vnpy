# encoding: UTF-8

from ctaStrategyTemplate import *
from ctaObject import CtaBarData


########################################################################
class DataRecorder(CtaStrategyTemplate):
    """
    纯粹用来记录历史数据的工具（基于CTA策略），
    建议运行在实际交易程序外的一个vn.trader实例中，
    本工具会记录Tick和1分钟K线数据。
    """

    #----------------------------------------------------------------------
    def __init__(self, ctaEngine, name, setting=None):
        """Constructor"""
        super(DataRecorder, self).__init__(ctaEngine, name, setting)
        
        self.strategyClassName = 'DataRecorder'
        
        self.author = u'用Python的交易员'
        self.tickDbName = 'VtTrader_Tick_Db'
        self.barDbName = 'VtTrader_1Min_Db'
        
        self.paramList.append('author')
        
        # 数据记录相关
        self.bar = None         # K线数据对象
        self.barMinute = -1     # 当前的分钟，初始化设为-1
        
    #----------------------------------------------------------------------
    def init(self):
        """初始化"""
        self.writeCtaLog(u'数据记录工具%s初始化' %self.name)
        
    #----------------------------------------------------------------------
    def start(self):
        """启动策略（必须由用户继承实现）"""
        self.writeCtaLog(u'数据记录工具%s启动' %self.name)
    
    #----------------------------------------------------------------------
    def stop(self):
        """停止策略（必须由用户继承实现）"""
        self.writeCtaLog(u'数据记录工具%s停止' %self.name)
        
    #----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送"""
        # 收到Tick后，首先插入到数据库里
        self.insertTick(tick)
        
        # 计算K线
        tickMinute = tick.datetime.minute
        
        if tickMinute != self.barMinute:    # 如果分钟变了，则把旧的K线插入数据库，并生成新的K线
            if self.bar:
                self.onBar(self.bar)
            
            bar = CtaBarData()              # 创建新的K线，目的在于防止之前K线对象在插入Mongo中被再次修改，导致出错
            bar.vtSymbol = tick.vtSymbol
            bar.symbol = tick.symbol
            bar.exchange = tick.exchange
            
            bar.open = tick.lastPrice
            bar.high = tick.lastPrice
            bar.low = tick.lastPrice
            bar.close = tick.lastPrice
            
            bar.date = tick.date
            bar.time = tick.time
            bar.datetime = tick.datetime    # K线的时间设为第一个Tick的时间
            
            bar.volume = tick.volume
            bar.openInterest = tick.openInterest
            
            self.bar = bar                  # 这种写法为了减少一层访问，加快速度
            self.barMinute = tickMinute     # 更新当前的分钟
            
        else:                               # 否则继续累加新的K线
            bar = self.bar                  # 写法同样为了加快速度
            
            bar.high = max(bar.high, tick.lastPrice)
            bar.low = min(bar.low, tick.lastPrice)
            bar.close = tick.lastPrice
            
            bar.volume = bar.volume + tick.volume   # 成交量是累加的
            bar.openInterest = tick.openInterest    # 持仓量直接更新
        
    #----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送"""
        pass
    
    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """收到成交推送"""
        pass
    
    #----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送"""
        self.insertBar(bar)   
        
        
    