# encoding: UTF-8
"""
This file tweaks ctaTemplate Module to suit multi-TimeFrame strategies.
"""

from ctaBase import *
from ctaTemplate import CtaTemplate
import numpy as np

########################################################################
class BreakOut(CtaTemplate):

    """
    "infoArray" 字典是用来储存辅助品种信息的, 可以是同品种的不同分钟k线, 也可以是不同品种的价格。

    调用的方法:
    价格序列:
    self.infoArray["数据库名 + 空格 + collection名"]["close"]
    self.infoArray["数据库名 + 空格 + collection名"]["high"]
    self.infoArray["数据库名 + 空格 + collection名"]["low"]

    单个价格:
    self.infoBar["数据库名 + 空格 + collection名"]
    返回的值为一个ctaBarData 或 None
    """

    #----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """日内突破交易策略, 出场方式非常多, 本文件使用指标出场"""

        className = 'BreakOut'
        author = 'Joe'
        super(BreakOut, self).__init__(ctaEngine, setting)

        # 设置辅助品种数据字典
        self.infoArray = {}
        self.initInfobar = {}
        self.infoBar = {}

        # 缓存数据量
        self.bufferSize = 100
        self.bufferCount = 0
        self.initDays = 10

        # 设置参数
        self.pOBO_Mult = 0.5        # 计算突破点位
        # self.pProtMult = 2          # 止损的ATR倍数
        # self.pProfitMult = 2        # 止盈相对于止损的倍数
        # self.SlTp_On = False        # 止损止盈功能
        # self.EODTime = 15           # 设置日内平仓时间

        self.vOBO_stretch = EMPTY_FLOAT
        self.vOBO_initialpoint = EMPTY_FLOAT
        self.vOBO_level_L = EMPTY_FLOAT
        self.vOBO_level_S = EMPTY_FLOAT

        self.orderList = []

        # 参数列表，保存了参数的名称
        paramList = ['name',
                     'className',
                     'author',
                     'pOBO_Mult',
                     'pProtMult',
                     'pProfitMult',
                     'SlTp_On',
                     'EODTime']

        # 变量列表，保存了变量的名称
        varList = ['vOBO_stretch',
                   'vOBO_initialpoint',
                   'vOBO_level_L',
                   'vOBO_level_S']

        # ----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        self.writeCtaLog(u'%s策略初始化' % self.name)

        # 载入历史数据，并采用回放计算的方式初始化策略数值
        initData = self.loadBar(self.initDays)
        for bar in initData:

            # 推送新数据, 同时检查是否有information bar需要推送
            # Update new bar, check whether the Time Stamp matching any information bar
            ibar = self.checkInfoBar(bar)
            self.onBar(bar, infobar=ibar)

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

    # ----------------------------------------------------------------------
    def checkInfoBar(self, bar):
        """在初始化时, 检查辅助品种数据的推送(初始化结束后, 回测时不会调用)"""

        initInfoCursorDict = self.ctaEngine.initInfoCursor

        # 如果"initInfobar"字典为空, 初始化字典, 插入第一个数据
        # If dictionary "initInfobar" is empty, insert first data record
        if self.initInfobar == {}:
            for info_symbol in initInfoCursorDict:
                try:
                    self.initInfobar[info_symbol] = next(initInfoCursorDict[info_symbol])
                except StopIteration:
                    print "Data of information symbols is empty! Input is a list, not str."
                    raise

        # 若有某一品种的 TimeStamp 和执行报价的 TimeStamp 匹配, 则将"initInfobar"中的数据推送,
        # 然后更新该品种的数据
        # If any symbol's TimeStamp is matched with execution symbol's TimeStamp, return data
        # in "initInfobar", and update new data.
        temp = {}
        for info_symbol in self.initInfobar:

            data = self.initInfobar[info_symbol]

            # Update data only when Time Stamp is matched

            if (data is not None) and (data['datetime'] <= bar.datetime):

                try:
                    temp[info_symbol] = CtaBarData()
                    temp[info_symbol].__dict__ = data
                    self.initInfobar[info_symbol] = next(initInfoCursorDict[info_symbol])
                except StopIteration:
                    self.initInfobar[info_symbol] = None
                    self.ctaEngine.output("No more data for initializing %s." % (info_symbol,))
            else:
                temp[info_symbol] = None

        return temp

    # ----------------------------------------------------------------------
    def updateInfoArray(self, infobar):
        """收到Infomation Data, 更新辅助品种缓存字典"""

        for name in infobar:

            data = infobar[name]

            # Construct empty array
            if len(self.infoArray) < len(infobar) :
                self.infoArray[name] = {
                    "close": np.zeros(self.bufferSize),
                    "high": np.zeros(self.bufferSize),
                    "low": np.zeros(self.bufferSize),
                    "open": np.zeros(self.bufferSize)
                }

            if data is None:
                pass

            else:
                self.infoArray[name]["close"][0:self.bufferSize - 1] = \
                    self.infoArray[name]["close"][1:self.bufferSize]
                self.infoArray[name]["high"][0:self.bufferSize - 1] = \
                    self.infoArray[name]["high"][1:self.bufferSize]
                self.infoArray[name]["low"][0:self.bufferSize - 1] = \
                    self.infoArray[name]["low"][1:self.bufferSize]
                self.infoArray[name]["open"][0:self.bufferSize - 1] = \
                    self.infoArray[name]["open"][1:self.bufferSize]

                self.infoArray[name]["close"][-1] = data.close
                self.infoArray[name]["high"][-1] = data.high
                self.infoArray[name]["low"][-1] = data.low
                self.infoArray[name]["open"][-1] = data.open

    # ----------------------------------------------------------------------
    def onBar(self, bar, **kwargs):
        """收到Bar推送（必须由用户继承实现）"""

        # Update infomation data
        # "infobar"是由不同时间或不同品种的品种数据组成的字典, 如果和执行品种的 TimeStamp 不匹配,
        # 则传入的是"None", 当time stamp和执行品种匹配时, 传入的是"Bar"
        if "infobar" in kwargs:
            self.infoBar = kwargs["infobar"]
            self.updateInfoArray(kwargs["infobar"])

        # 若读取的缓存数据不足, 不考虑交易
        self.bufferCount += 1
        if self.bufferCount < self.bufferSize:
            return

        # 计算指标数值
        a = np.sum(self.infoArray["TestData @GC_1D"]["close"])
        if a == 0.0:
            return

        # Only updating indicators when information bar changes
        # 只有在30min或者1d K线更新后才更新指标
        TradeOn = False
        if any([i is not None for i in self.infoBar]):
            TradeOn = True
            self.vRange = self.infoArray["TestData @GC_1D"]["high"][-1] -\
                          self.infoArray["TestData @GC_1D"]["low"][-1]
            self.vOBO_stretch = self.vRange * self.pOBO_Mult
            self.vOBO_initialpoint = self.infoArray["TestData @GC_1D"]["close"][-1]
            self.vOBO_level_L = self.vOBO_initialpoint + self.vOBO_stretch
            self.vOBO_level_S = self.vOBO_initialpoint - self.vOBO_stretch

            self.atrValue30M = talib.abstract.ATR(self.infoArray["TestData @GC_30M"])[-1]

        # 判断是否要进行交易

        # 当前无仓位
        if (self.pos == 0 and TradeOn == True):

            # 撤销之前发出的尚未成交的委托（包括限价单和停止单）
            for orderID in self.orderList:
                self.cancelOrder(orderID)
            self.orderList = []

            # 若上一个30分钟K线的最高价大于OBO_level_L
            # 且当前的价格大于OBO_level_L, 则买入
            if self.infoArray["TestData @GC_30M"]["high"][-1] > self.vOBO_level_L:

                if bar.close > self.vOBO_level_L:

                    self.buy(bar.close + 0.5, 1)

                    # 下单后, 在下一个30Min K线之前不交易
                    TradeOn = False

            # 若上一个30分钟K线的最高价低于OBO_level_S
            # 且当前的价格小于OBO_level_S, 则卖出
            elif self.infoArray["TestData @GC_30M"]["low"][-1] < self.vOBO_level_S:

                if bar.close < self.vOBO_level_S:

                    self.short(bar.close - 0.5, 1)

                    # 下单后, 在下一个30Min K线之前不交易
                    TradeOn = False

        # 持有多头仓位
        elif self.pos > 0:

            # 当价格低于initialpoint水平, 出场
            if bar.close < self.vOBO_initialpoint:
                self.sell(bar.close - 0.5 , 1)

        # 持有空头仓位
        elif self.pos < 0:

            # 当价格高于initialpoint水平, 出场
            if bar.close > self.vOBO_initialpoint:
                self.cover(bar.close + 0.5, 1)


        # 发出状态更新事件
        self.putEvent()

    # ----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        pass

    # ----------------------------------------------------------------------
    def onTrade(self, trade):
        pass


if __name__ == '__main__':
    # 提供直接双击回测的功能
    # 导入PyQt4的包是为了保证matplotlib使用PyQt4而不是PySide，防止初始化出错
    from ctaBacktestMultiTF import *
    from PyQt4 import QtCore, QtGui
    import time

    '''
    创建回测引擎
    设置引擎的回测模式为K线
    设置回测用的数据起始日期
    载入历史数据到引擎中
    在引擎中创建策略对象

    Create backtesting engine
    Set backtest mode as "Bar"
    Set "Start Date" of data range
    Load historical data to engine
    Create strategy instance in engine
    '''
    engine = BacktestEngineMultiTF()
    engine.setBacktestingMode(engine.BAR_MODE)
    engine.setStartDate('20120101')
    engine.setEndDate('20150101')
    engine.setDatabase("TestData", "@GC_1M", info_symbol=[("TestData","@GC_30M"),
                                                          ("TestData","@GC_1D")])

    # Set parameters for strategy
    engine.initStrategy(BreakOut, {})

    # 设置产品相关参数
    engine.setSlippage(0.2)  # 股指1跳
    engine.setCommission(0.3 / 10000)  # 万0.3
    engine.setSize(1)  # 股指合约大小

    # 开始跑回测
    start = time.time()

    engine.runBacktesting()

    # 显示回测结果
    engine.showBacktestingResult()

    print 'Time consumed：%s' % (time.time() - start)