# encoding: UTF-8

"""
存在跳空缺口才开仓，如：
1. 开盘价大与昨日最高价开仓
2. 开盘价小于昨日最低价开仓
3. 最新价小于等于开盘价2个tick开空
4. 最新价大于等于开盘价2个tick开多
5. 每天每个合约最多开仓4次
"""

from datetime import datetime
import pandas as pd
from ctaBase import *
from ctaTemplate import CtaTemplate


########################################################################
class GapStrategy(CtaTemplate):
    """存在跳空缺口才开仓"""
    className = 'GapStrategy'
    author = 'Eleven'

    # 策略参数
    amplitude = 2  # 开仓阈值
    maxOpenCount = 4  # 最大开仓次数
    tradeVolume = 1 # 交易数量
    size = 10   # 合约大小
    tickPrice = 1 # 最小变动价格

    # 策略变量
    openCount = 0

    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol',
                 'amplitude',
                 'maxOpenCount']

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos',
               'openCount']

    # ----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(GapStrategy, self).__init__(ctaEngine, setting)

        # 注意策略类中的可变对象属性（通常是list和dict等），在策略初始化时需要重新创建，
        # 否则会出现多个策略实例之间数据共享的情况，有可能导致潜在的策略逻辑错误风险，
        # 策略类中的这些可变对象属性可以选择不写，全都放在__init__下面，写主要是为了阅读
        # 策略时方便（更多是个编程习惯的选择）
        self.noTrading = True   # 不存在未成交订单
        self.lastOrder = None
    # ----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        self.writeCtaLog(u'策略初始化')
        # 获取昨日最高价和最低价
        self.perHigh = None
        self.perLow = None
        self.openCount = 0  # 今日开仓次数，需要保存
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
        if tick.openPrice >= self.perLow or tick.openPrice <= self.perHigh:
            return
        if tick.lastPrice >= tick.openPrice + self.tickPrice * self.amplitude:
            # 存在空单，买入止损
            if self.pos < 0 and self.noTrading:
                self.cover(tick.askPrice1, self.tradeVolume)
                self.noTrading = False
            # 无持仓，开多单
            elif self.pos == 0 and self.noTrading and self.openCount < self.maxOpenCount:
                self.buy(tick.askPrice1, self.tradeVolume)
                self.openCount += 1
                self.noTrading = False
            # 存在多单，无操作
            else:
                pass
        elif tick.lastPrice <= tick.openPrice - self.tickPrice * self.amplitude:
            # 存在多单，卖出止损
            if self.pos > 0 and self.noTrading:
                self.sell(tick.bidPrice1, self.tradeVolume)
                self.noTrading = False
            # 无持仓，开空单
            elif self.pos == 0 and self.noTrading and self.openCount < self.maxOpenCount:
                self.short(tick.bidPrice1, self.tradeVolume)
                self.openCount += 1
                self.noTrading = False
            # 存在空单，无操作
            else:
                pass
        else:
            pass

        # 处理订单回报
        if self.lastOrder != None and self.lastOrder.status == u'全部成交':
            self.noTrading = True
            self.lastOrder = None
        elif self.lastOrder != None and self.lastOrder.status == u'未成交':
            self.cancelOrder(self.lastOrder.vtOrderID)
            if self.lastOrder.offset == u'开仓':
                self.openCount -= 1
            self.noTrading = True
            self.lastOrder = None


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
