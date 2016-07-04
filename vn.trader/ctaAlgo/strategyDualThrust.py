# encoding: UTF-8

"""
Dual Thrust策略的VN.PY实现
版本：v0.1

这里的Demo是一个最简单的策略实现，并未考虑太多实盘中的交易细节，如：
1. 委托价格超出涨跌停价导致的委托失败
2. 委托未成交，需要撤单后重新委托
3. 断网后恢复交易状态
4. 等等
这些点是作者选择特意忽略不去实现，因此想实盘的朋友请自己多多研究CTA交易的一些细节，
做到了然于胸后再去交易，对自己的money和时间负责。
也希望社区能做出一个解决了以上潜在风险的Demo出来。
"""


from ctaBase import *
from ctaTemplate import CtaTemplate
import pandas as pd

########################################################################
class DualThrust(CtaTemplate):
    """Dual Thrust策略Demo"""
    className = 'DualThrust'
    author = u'融拓科技'

    # 策略参数
    k_long = 0.1        # 多单k值参数
    k_short = 0.1       # 空单k值参数
    initDays = 10       # 初始化数据所用的天数

    # 策略变量
    bar = None
    barMinute = EMPTY_STRING

    closeHistory = []       # 缓存K线收盘价的数组
    maxHistory = 50         # 最大缓存数量

    hh = EMPTY_FLOAT   # N日High的最高价
    lc = EMPTY_FLOAT   # N日Close的最低价

    hc = EMPTY_FLOAT   # N日Close的最高价
    ll = EMPTY_FLOAT    # N日Low的最低价

    range = EMPTY_FLOAT     # N周期内的价格振幅

    date = EMPTY_STRING     # 今日日期，用于判断是否需要重新计算range
    open = EMPTY_FLOAT      # 今日开盘价
    upperPrice = EMPTY_FLOAT      # 今日多单入场价
    lowerPrice = EMPTY_FLOAT      # 今日空单入场价


    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol',
                 'k_long',
                 'k_short']

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos',
               'range'
               'open',
               'upperPrice',
               'lowerPrice']

    #----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(DualThrust, self).__init__(ctaEngine, setting)
        # 注意策略类中的可变对象属性（通常是list和dict等），在策略初始化时需要重新创建，
        # 否则会出现多个策略实例之间数据共享的情况，有可能导致潜在的策略逻辑错误风险，
        # 策略类中的这些可变对象属性可以选择不写，全都放在__init__下面，写主要是为了阅读
        # 策略时方便（更多是个编程习惯的选择）

        # 策略变量
        self.bar = None
        self.barMinute = EMPTY_STRING

        self.closeHistory = []       # 缓存K线收盘价的数组
        self.maxHistory = 50         # 最大缓存数量

        self.hh = EMPTY_FLOAT   # N日High的最高价
        self.lc = EMPTY_FLOAT   # N日Close的最低价

        self.hc = EMPTY_FLOAT   # N日Close的最高价
        self.ll = EMPTY_FLOAT    # N日Low的最低价

        self.range = EMPTY_FLOAT     # N周期内的价格振幅

        self.date = EMPTY_STRING     # 今日日期，用于判断是否需要重新计算range
        self.open = EMPTY_FLOAT      # 今日开盘价
        self.upperPrice = EMPTY_FLOAT      # 今日多单入场价
        self.lowerPrice = EMPTY_FLOAT      # 今日空单入场价
    #----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        self.writeCtaLog(u'Dual Thrust策略初始化')

        self.putEvent()

    #----------------------------------------------------------------------
    def onStart(self):
        """启动策略（必须由用户继承实现）"""
        self.writeCtaLog(u'Dual Thrust策略启动')
        self.putEvent()

    #----------------------------------------------------------------------
    def onStop(self):
        """停止策略（必须由用户继承实现）"""
        self.writeCtaLog(u'Dual Thrust策略停止')
        self.putEvent()

    #----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送（必须由用户继承实现）"""

        # 首先确定range，新交易日更新新的range
        if tick.date != self.date:
            print tick.date, tick.openPrice, tick.time
            self.date = tick.date
            self.open = tick.openPrice
            cursor = self.loadCursor(tick.date, self.initDays)
            # print tick.date, cursor
            data = pd.DataFrame(list(cursor))

            try:
                self.hh = data['high'].max()
            except:
                print tick.datetime
            self.lc = data['close'].min()
            self.hc = data['close'].max()
            self.ll = data['low'].min()

            self.range = max(self.hh - self.lc, self.hc - self.ll)
            # print self.open, self.range, self.k_long
            # print type(self.open), type(self.range), type(self.k_long),

            self.upperPrice = self.open + self.range * self.k_long
            self.lowerPrice = self.open - self.range * self.k_short


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

            # 实盘中用不到的数据可以选择不算，从而加快速度
            #bar.volume = tick.volume
            #bar.openInterest = tick.openInterest

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

        # 判断买卖
        # print type(bar.close) , type(self.upperPrice)
        crossOver = bar.close > self.upperPrice     # 突破上轨线
        crossBelow = bar.close < self.lowerPrice    # 突破下轨线

        # 金叉和死叉的条件是互斥
        # 所有的委托均以K线收盘价委托（这里有一个实盘中无法成交的风险，考虑添加对模拟市价单类型的支持）

        # 1. 反手
        # if crossOver:
        #     # 如果金叉时手头没有持仓，则直接做多
        #     if self.pos == 0:
        #         self.buy(bar.close, 1)
        #     # 如果有空头持仓，则先平空，再做多
        #     elif self.pos < 0:
        #         self.cover(bar.close, 1)
        #         self.buy(bar.close, 1)
        # # 死叉和金叉相反
        # elif crossBelow:
        #     if self.pos == 0:
        #         self.short(bar.close, 1)
        #     elif self.pos > 0:
        #         self.sell(bar.close, 1)
        #         self.short(bar.close, 1)

        # 2. 开盘价平仓
        if crossOver:
            # 如果金叉时手头没有持仓，则直接做多
            if self.pos == 0:
                self.buy(bar.close, 1)

        # 死叉和金叉相反
        elif crossBelow:
            if self.pos == 0:
                self.short(bar.close, 1)

        # 开盘价平仓
        if self.pos > 0 and bar.close < self.open:
            self.sell(bar.close, 1)
        if self.pos < 0 and bar.close > self.open:
            self.cover(bar.close, 1)

        # 发出状态更新事件
        self.putEvent()

    #----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        # 对于无需做细粒度委托控制的策略，可以忽略onOrder
        pass

    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """收到成交推送（必须由用户继承实现）"""
        # 对于无需做细粒度委托控制的策略，可以忽略onOrder
        pass


if __name__ == '__main__':
    # 以下内容是一段回测脚本的演示，用户可以根据自己的需求修改
    # 建议使用ipython notebook或者spyder来做回测
    # 同样可以在命令模式下进行回测（一行一行输入运行）
    # 提供直接双击回测的功能
    # 导入PyQt4的包是为了保证matplotlib使用PyQt4而不是PySide，防止初始化出错

    from ctaBacktesting import *

    # 创建回测引擎
    engine = BacktestingEngine()

    # 设置引擎的回测模式为K线

    engine.setBacktestingMode(engine.TICK_MODE)

    # 设置回测用的数据起始日期
    engine.setStartDate('20160104')

    # 载入历史数据到引擎中
    engine.loadHistoryData('VnTrader_Tick_Db', 'pp_hot')

    # 设置产品相关参数
    # engine.setSlippage(0.2)     # 股指1跳
    # engine.setRate(0.3/10000)   # 万0.3
    # engine.setSize(300)         # 股指合约大小
    engine.setSlippage(2)     # pp2跳
    engine.setRate(1.0/10000)   # 万0.3
    engine.setSize(5)         # pp合约大小

    # 在引擎中创建策略对象
    # 有的策略需要vtSymbol去读取数据库，比如Dual Thrust, 传入setting
    engine.initStrategy(DualThrust, {"vtSymbol": "pp_hot"})

    # 开始跑回测
    engine.runBacktesting()

    # 显示回测结果
    # spyder或者ipython notebook中运行时，会弹出盈亏曲线图
    # 直接在cmd中回测则只会打印一些回测数值
    engine.showBacktestingResult()
