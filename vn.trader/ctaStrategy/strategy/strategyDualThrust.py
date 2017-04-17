# encoding: UTF-8

"""
DualThrust交易策略
"""

from datetime import time

import sys
sys.path.append('..')

from ctaBase import *
from ctaTemplate import CtaTemplate


########################################################################
class DualThrustStrategy(CtaTemplate):
    """DualThrust交易策略"""
    className = 'DualThrustStrategy'
    author = u'用Python的交易员'

    # 策略参数
    fixedSize = 100
    k1 = 0.4
    k2 = 0.6

    initDays = 10

    # 策略变量
    bar = None                  # K线对象
    barMinute = EMPTY_STRING    # K线当前的分钟
    barList = []                # K线对象的列表

    dayOpen = 0
    dayHigh = 0
    dayLow = 0
    
    range = 0
    longEntry = 0
    shortEntry = 0
    exitTime = time(hour=14, minute=55)

    longEntered = False
    shortEntered = False

    orderList = []                      # 保存委托代码的列表

    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol',
                 'k1',
                 'k2']    

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos',
               'range',
               'longEntry',
               'shortEntry',
               'exitTime']  

    #----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(DualThrustStrategy, self).__init__(ctaEngine, setting) 
        
        self.barList = []

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
        # 计算K线
        tickMinute = tick.datetime.minute

        if tickMinute != self.barMinute:    
            if self.bar:
                self.onBar(self.bar)

            bar = CtaBarData()              
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

            self.bar = bar                  # 这种写法为了减少一层访问，加快速度
            self.barMinute = tickMinute     # 更新当前的分钟
        else:                               # 否则继续累加新的K线
            bar = self.bar                  # 写法同样为了加快速度

            bar.high = max(bar.high, tick.lastPrice)
            bar.low = min(bar.low, tick.lastPrice)
            bar.close = tick.lastPrice

    #----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        # 撤销之前发出的尚未成交的委托（包括限价单和停止单）
        for orderID in self.orderList:
            self.cancelOrder(orderID)
        self.orderList = []

        # 计算指标数值
        self.barList.append(bar)
        
        if len(self.barList) <= 2:
            return
        else:
            self.barList.pop(0)
        lastBar = self.barList[-2]
        
        # 新的一天
        if lastBar.datetime.date() != bar.datetime.date():
            # 如果已经初始化
            if self.dayHigh:
                self.range = self.dayHigh - self.dayLow
                self.longEntry = bar.open + self.k1 * self.range
                self.shortEntry = bar.open - self.k2 * self.range           
                
            self.dayOpen = bar.open
            self.dayHigh = bar.high
            self.dayLow = bar.low

            self.longEntered = False
            self.shortEntered = False
        else:
            self.dayHigh = max(self.dayHigh, bar.high)
            self.dayLow = min(self.dayLow, bar.low)

        # 尚未到收盘
        if not self.range:
            return

        if bar.datetime.time() < self.exitTime:
            if self.pos == 0:
                if bar.close > self.dayOpen:
                    if not self.longEntered:
                        vtOrderID = self.buy(self.longEntry, self.fixedSize, stop=True)
                        self.orderList.append(vtOrderID)
                else:
                    if not self.shortEntered:
                        vtOrderID = self.short(self.shortEntry, self.fixedSize, stop=True)
                        self.orderList.append(vtOrderID)
    
            # 持有多头仓位
            elif self.pos > 0:
                self.longEntered = True

                # 多头止损单
                vtOrderID = self.sell(self.shortEntry, self.fixedSize, stop=True)
                self.orderList.append(vtOrderID)
                
                # 空头开仓单
                if not self.shortEntered:
                    vtOrderID = self.short(self.shortEntry, self.fixedSize, stop=True)
                    self.orderList.append(vtOrderID)
                
            # 持有空头仓位
            elif self.pos < 0:
                self.shortEntered = True

                # 空头止损单
                vtOrderID = self.cover(self.longEntry, self.fixedSize, stop=True)
                self.orderList.append(vtOrderID)
                
                # 多头开仓单
                if not self.longEntered:
                    vtOrderID = self.buy(self.longEntry, self.fixedSize, stop=True)
                    self.orderList.append(vtOrderID)  
            
        # 收盘平仓
        else:
            if self.pos > 0:
                vtOrderID = self.sell(bar.close * 0.99, abs(self.pos))
                self.orderList.append(vtOrderID)
            elif self.pos < 0:
                vtOrderID = self.cover(bar.close * 1.01, abs(self.pos))
                self.orderList.append(vtOrderID) 
 
        # 发出状态更新事件
        self.putEvent()

    #----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        pass

    #----------------------------------------------------------------------
    def onTrade(self, trade):
        # 发出状态更新事件
        self.putEvent()


if __name__ == '__main__':
    # 提供直接双击回测的功能
    # 导入PyQt4的包是为了保证matplotlib使用PyQt4而不是PySide，防止初始化出错
    from ctaBacktesting import *
    from PyQt4 import QtCore, QtGui
    
    # 创建回测引擎
    engine = BacktestingEngine()
    
    # 设置引擎的回测模式为K线
    engine.setBacktestingMode(engine.BAR_MODE)

    # 设置回测用的数据起始日期
    engine.setStartDate('20120101')
    
    # 设置产品相关参数
    engine.setSlippage(0.2)     # 股指1跳
    engine.setRate(0.3/10000)   # 万0.3
    engine.setSize(300)         # 股指合约大小 
    engine.setPriceTick(0.2)    # 股指最小价格变动
    
    # 设置使用的历史数据库
    engine.setDatabase(MINUTE_DB_NAME, 'IF0000')
    
    # 在引擎中创建策略对象
    engine.initStrategy(DualThrustStrategy, {})
    
    # 开始跑回测
    engine.runBacktesting()
    
    # 显示回测结果
    engine.showBacktestingResult()
    
    ## 跑优化
    #setting = OptimizationSetting()                 # 新建一个优化任务设置对象
    #setting.setOptimizeTarget('capital')            # 设置优化排序的目标是策略净盈利
    #setting.addParameter('atrLength', 12, 20, 2)    # 增加第一个优化参数atrLength，起始11，结束12，步进1
    #setting.addParameter('atrMa', 20, 30, 5)        # 增加第二个优化参数atrMa，起始20，结束30，步进1
    #setting.addParameter('rsiLength', 5)            # 增加一个固定数值的参数
    
    ## 性能测试环境：I7-3770，主频3.4G, 8核心，内存16G，Windows 7 专业版
    ## 测试时还跑着一堆其他的程序，性能仅供参考
    #import time    
    #start = time.time()
    
    ## 运行单进程优化函数，自动输出结果，耗时：359秒
    #engine.runOptimization(AtrRsiStrategy, setting)            
    
    ## 多进程优化，耗时：89秒
    ##engine.runParallelOptimization(AtrRsiStrategy, setting)     
    
    #print u'耗时：%s' %(time.time()-start)