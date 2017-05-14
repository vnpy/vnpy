# encoding: UTF-8

"""
这里的Demo是一个最简单的策略实现，并未考虑太多实盘中的交易细节，如：
1. 委托价格超出涨跌停价导致的委托失败
2. 委托未成交，需要撤单后重新委托
3. 断网后恢复交易状态
4. 等等
这些点是作者选择特意忽略不去实现，因此想实盘的朋友请自己多多研究CTA交易的一些细节，
做到了然于胸后再去交易，对自己的money和时间负责。
也希望社区能做出一个解决了以上潜在风险的Demo出来。
"""

from datetime import datetime
import pandas as pd
from ctaBase import *
from ctaTemplate import CtaTemplate


########################################################################
class MACDStrategy(CtaTemplate):
    """基于5分钟K线的macd金叉死叉策略"""
    className = 'MACDStrategy'
    author = 'Eleven'

    # 策略参数
    pshort = 24  # 短周期天数
    plong = 52  # 长周期天数
    pm = 18
    pwin = 30
    initDays = 30  # 初始化数据所用的天数

    # 策略变量
    bar = None
    barMinute = EMPTY_STRING

    fastMa = []  # 快速EMA均线数组
    fastMa0 = EMPTY_FLOAT  # 当前最新的快速EMA
    fastMa1 = EMPTY_FLOAT  # 上一根的快速EMA
    barList = []
    barDf = None

    slowMa = []  # 与上面相同
    slowMa0 = EMPTY_FLOAT
    slowMa1 = EMPTY_FLOAT

    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol',
                 'win']

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos',
               'fastMa0',
               'fastMa1',
               'slowMa0',
               'slowMa1']

    # ----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(MACDStrategy, self).__init__(ctaEngine, setting)

        # 注意策略类中的可变对象属性（通常是list和dict等），在策略初始化时需要重新创建，
        # 否则会出现多个策略实例之间数据共享的情况，有可能导致潜在的策略逻辑错误风险，
        # 策略类中的这些可变对象属性可以选择不写，全都放在__init__下面，写主要是为了阅读
        # 策略时方便（更多是个编程习惯的选择）
        self.barList =[]
        self.barDf = None
        self.longPrice = 0
        self.shortPrice = 0
        self.nowPos = 0
        self.total = 0

    # ----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        self.writeCtaLog(u'策略初始化')

        initData = self.loadBar(self.initDays)
        for bar in initData:
            self.onBar(bar)

        self.putEvent()

    # ----------------------------------------------------------------------
    def onStart(self):
        """启动策略（必须由用户继承实现）"""
        self.writeCtaLog(u'策略启动')
        self.putEvent()

    # ----------------------------------------------------------------------
    def onStop(self):
        """停止策略（必须由用户继承实现）"""
        self.writeCtaLog(u'策略停止')
        self.putEvent()

    # ----------------------------------------------------------------------
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
            bar.datetime = tick.datetime  # K线的时间设为第一个Tick的时间

            # 实盘中用不到的数据可以选择不算，从而加快速度
            # bar.volume = tick.volume
            # bar.openInterest = tick.openInterest

            self.bar = bar  # 这种写法为了减少一层访问，加快速度
            self.barMinute = tickMinute  # 更新当前的分钟

        else:  # 否则继续累加新的K线
            bar = self.bar  # 写法同样为了加快速度

            bar.high = max(bar.high, tick.lastPrice)
            bar.low = min(bar.low, tick.lastPrice)
            bar.close = tick.lastPrice

    # ----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        # 计算快慢均线
        self.barList.append(bar.__dict__)
        if len(self.barList) <= 26:
            return
        self.barDf = pd.DataFrame(self.barList)
        self.macd()
        # print self.barDf['macd']
        # print bar.__dict__
        print 'win:',self.total
        # print 'pos:',self.nowPos
        # print 'longPrice:',self.longPrice
        # print 'shortPrice:',self.shortPrice
        # 判断买卖
        # crossOver = ((list(self.barDf['macd'])[-2] < 0)
        #              and list(self.barDf['macd'])[-1] > 0 and abs(list(self.barDf['macd'])[-1]) >= 2)  # 金叉上穿
        # crossBelow = ((list(self.barDf['macd'])[-2] > 0)
        #               and list(self.barDf['macd'])[-1] < 0 and abs(list(self.barDf['macd'])[-1]) >= 2)  # 死叉下穿
        crossOver = ((list(self.barDf['macd'])[-2] < 0)
                     and list(self.barDf['macd'])[-1] > 0)  # 金叉上穿
        crossBelow = ((list(self.barDf['macd'])[-2] > 0)
                      and list(self.barDf['macd'])[-1] < 0)  # 死叉下穿

        # 金叉和死叉的条件是互斥
        # 所有的委托均以K线收盘价委托（这里有一个实盘中无法成交的风险，考虑添加对模拟市价单类型的支持）
        # if self.nowPos > 0:
        #     if bar.high >= self.longPrice + self.pwin:
        #         self.sell(self.longPrice + self.pwin, 1)
        #         self.nowPos = 0
        #         print u'[%s]多单平仓：%s' % (bar.date.decode('utf-8'),self.longPrice + self.pwin)
        #         self.total += self.pwin
        # if self.nowPos < 0:
        #     if bar.low <= self.shortPrice - self.pwin:
        #         self.cover(self.shortPrice - self.pwin, 1)
        #         self.nowPos = 0
        #         print u'[%s]空单单平仓：%s' % (bar.date.decode('utf-8'),self.shortPrice - self.pwin)
        #         self.total += self.pwin

        if crossOver:
            # 如果金叉时手头没有持仓，则直接做多
            if self.nowPos == 0:
                self.buy(bar.close, 1)
                self.nowPos = 1
                self.longPrice = bar.close
                print u'[%s]做多：%s' % (bar.date.decode('utf-8'),bar.close)
            # 如果有空头持仓，则先平空，再做多
            elif self.nowPos < 0:
                self.cover(bar.close, 1)
                print u'[%s]空单平仓：%s' % (bar.date.decode('utf-8'),bar.close)
                self.total += (self.shortPrice - bar.close)
                self.buy(bar.close, 1)
                self.nowPos = 1
                self.longPrice = bar.close
                print u'[%s]反手做多：%s' % (bar.date.decode('utf-8'),bar.close)
        # 死叉和金叉相反
        elif crossBelow:
            if self.nowPos == 0:
                self.short(bar.close, 1)
                self.nowPos = -1
                self.shortPrice = bar.close
                print u'[%s]做空：%s' % (bar.date.decode('utf-8'),bar.close)
            elif self.nowPos > 0:
                self.sell(bar.close, 1)
                self.total += (bar.close - self.longPrice)
                print u'[%s]多单平仓：%s' % (bar.date.decode('utf-8'),bar.close)
                self.short(bar.close, 1)
                self.nowPos = -1
                self.shortPrice = bar.close
                print u'[%s]反手做空：%s' % (bar.date.decode('utf-8'),bar.close)

        # 发出状态更新事件
        self.putEvent()

    def macd(self):
        ema12 = self.barDf['close'].ewm(ignore_na=False, span=self.pshort, min_periods=0, adjust=True).mean()
        ema26 = self.barDf['close'].ewm(ignore_na=False, span=self.plong, min_periods=0, adjust=True).mean()
        self.barDf['diff'] = ema12 - ema26
        self.barDf['dea'] = self.barDf['diff'].ewm(ignore_na=False, span=self.pm, min_periods=0, adjust=True).mean()
        self.barDf['macd'] = (self.barDf['diff'] - self.barDf['dea']) * 2

    # ----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        # 对于无需做细粒度委托控制的策略，可以忽略onOrder
        pass

    # ----------------------------------------------------------------------
    def onTrade(self, trade):
        """收到成交推送（必须由用户继承实现）"""
        # 对于无需做细粒度委托控制的策略，可以忽略onOrder
        pass


########################################################################################
class OrderManagementDemoStrategy(CtaTemplate):
    """基于tick级别细粒度撤单追单测试demo"""

    className = 'OrderManagementDemoStrategy'
    author = u'用Python的交易员'

    # 策略参数
    initDays = 10  # 初始化数据所用的天数

    # 策略变量
    bar = None
    barMinute = EMPTY_STRING

    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol']

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos']

    # ----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(OrderManagementDemoStrategy, self).__init__(ctaEngine, setting)

        self.lastOrder = None
        self.orderType = ''

    # ----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        self.writeCtaLog(u'双EMA演示策略初始化')

        initData = self.loadBar(self.initDays)
        for bar in initData:
            self.onBar(bar)

        self.putEvent()

    # ----------------------------------------------------------------------
    def onStart(self):
        """启动策略（必须由用户继承实现）"""
        self.writeCtaLog(u'双EMA演示策略启动')
        self.putEvent()

    # ----------------------------------------------------------------------
    def onStop(self):
        """停止策略（必须由用户继承实现）"""
        self.writeCtaLog(u'双EMA演示策略停止')
        self.putEvent()

    # ----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送（必须由用户继承实现）"""

        # 建立不成交买单测试单
        if self.lastOrder == None:
            self.buy(tick.lastPrice - 10.0, 1)

        # CTA委托类型映射
        if self.lastOrder != None and self.lastOrder.direction == u'多' and self.lastOrder.offset == u'开仓':
            self.orderType = u'买开'

        elif self.lastOrder != None and self.lastOrder.direction == u'多' and self.lastOrder.offset == u'平仓':
            self.orderType = u'买平'

        elif self.lastOrder != None and self.lastOrder.direction == u'空' and self.lastOrder.offset == u'开仓':
            self.orderType = u'卖开'

        elif self.lastOrder != None and self.lastOrder.direction == u'空' and self.lastOrder.offset == u'平仓':
            self.orderType = u'卖平'

        # 不成交，即撤单，并追单
        if self.lastOrder != None and self.lastOrder.status == u'未成交':

            self.cancelOrder(self.lastOrder.vtOrderID)
            self.lastOrder = None
        elif self.lastOrder != None and self.lastOrder.status == u'已撤销':
            # 追单并设置为不能成交

            self.sendOrder(self.orderType, self.tick.lastprice - 10, 1)
            self.lastOrder = None

    # ----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        pass

    # ----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        # 对于无需做细粒度委托控制的策略，可以忽略onOrder
        self.lastOrder = order

    # ----------------------------------------------------------------------
    def onTrade(self, trade):
        """收到成交推送（必须由用户继承实现）"""
        # 对于无需做细粒度委托控制的策略，可以忽略onOrder
        pass
