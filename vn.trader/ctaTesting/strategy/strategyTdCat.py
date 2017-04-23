# encoding: UTF-8

"""
测试回测策略
"""

from datetime import datetime
from ctaBase import *
from ctaTemplate import CtaTemplate


########################################################################################
class TdCatStrategy(CtaTemplate):
    """基于tick级别测试demo"""

    className = 'TdCatStrategy'
    author = 'Eleven'

    # 策略参数
    drawDown = 10   # 回撤阈值
    stopWin = 10    # 止盈
    stopLoss = 10   # 止损

    # 策略变量
    bar = None
    barMinute = EMPTY_STRING

    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol',
                 'drawDown',
                 'stopWin',
                 'stopLoss']

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos']

    # ----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(TdCatStrategy, self).__init__(ctaEngine, setting)

        self.lastOrder = None
        self.orderType = ''
        self.opening = False
        self.closeing = False

    # ----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        self.writeCtaLog(u'TdCat策略初始化')
        self.putEvent()

    # ----------------------------------------------------------------------
    def onStart(self):
        """启动策略（必须由用户继承实现）"""
        self.writeCtaLog(u'TdCat策略启动')
        self.putEvent()

    # ----------------------------------------------------------------------
    def onStop(self):
        """停止策略（必须由用户继承实现）"""
        self.writeCtaLog(u'TdCat策略停止')
        self.putEvent()

    # ----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送（必须由用户继承实现）"""
        # print 'lastprice:',tick.lastPrice

        if not self.opening and self.pos == 0:
            if tick.highPrice - tick.openPrice >= self.drawDown and tick.lastPrice <= tick.openPrice:
                self.opening = True
                self.short(tick.lastPrice, 1)
                print "short!"
                print 'time',tick.time
            elif tick.openPrice - tick.lowPrice >= self.drawDown and tick.lastPrice >= tick.openPrice:
                self.opening = True
                self.buy(tick.lastPrice, 1)
                print "buy!"
                print 'time',tick.time

        #存在多头仓位
        if not self.closeing and self.pos > 0:
            #止盈止损
            if tick.lastPrice - tick.openPrice >= self.stopWin or tick.openPrice - tick.lastPrice >= self.stopLoss:
                self.closeing = True
                self.sell(tick.lastPrice, 1)
                print "sell!"
                print 'time',tick.time

        # 存在空头仓位
        if not self.closeing and self.pos < 0:
            # 止盈止损
            if tick.lastPrice - tick.openPrice >= self.stopLoss or tick.openPrice - tick.lastPrice >= self.stopWin:
                self.closeing = True
                self.cover(tick.lastPrice, 1)
                print "cover!"
                print 'time', tick.time



        # 不成交，即撤单，并追单
        if self.lastOrder != None and self.lastOrder.status == u'未成交':
            self.cancelOrder(self.lastOrder.vtOrderID)
            self.lastOrder = None
        elif self.lastOrder != None and self.lastOrder.status == u'已撤销':
            # 追单并设置为不能成交
            self.sendOrder(self.orderType, tick.lastprice, 1)
            self.lastOrder = None

        # 收盘清仓
        nowTime = datetime.strptime(tick.time.split('.')[0], '%H:%M:%S').time()
        if (nowTime > datetime.strptime('14:24:10', '%H:%M:%S').time()) and (
                    nowTime <= datetime.strptime('15:00:00', '%H:%M:%S').time()):
            if not self.closeing and self.pos > 0:
                self.closeing = True
                self.sell(tick.lastPrice, 1)
                print 'sell'
            elif not self.closeing and self.pos < 0:
                self.closeing = True
                self.cover(tick.lastPrice, 1)
                print 'cover'
            self.opening = True #不再开仓
        self.putEvent()

    # ----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        pass

    # ----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        # 对于无需做细粒度委托控制的策略，可以忽略onOrder
        self.lastOrder = order
        if order.offset == u'开仓' and order.status == u'已撤销':
            self.opening = False
        elif order.status == u'已撤销':
            self.closeing = False

    # ----------------------------------------------------------------------
    def onTrade(self, trade):
        """收到成交推送（必须由用户继承实现）"""
        # 开仓单全部成交
        if trade.offset == u'开仓' and trade.status == u'全部成交':
            self.opening = False
        # 平仓单全部成交
        elif trade.status == u'全部成交':
            self.closeing = False
