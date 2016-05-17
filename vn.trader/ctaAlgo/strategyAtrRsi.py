# encoding: UTF-8

"""
一个ATR-RSI指标结合的交易策略，适合用在股指1分钟和5分钟线上。

（作者不对交易盈利做任何保证，策略代码仅供参考。）
"""


from ctaBase import *
from ctaTemplate import CtaTemplate

import talib
import numpy as np 


#################################################################
class AtrRsiStrategy(CtaTemplate):
    """结合ATR和RSI指标的一个分钟线交易策略"""
    className = "AtrRsiStrategy"
    author    = u"用python的交易员"

    #策略参数
    atrLength = 22          # 计算ATR指标的窗口数
    atrMaLength = 10        # 计算ATR均线的窗口数
    rsiLength = 5           # 计算RSI指标的窗口数
    rsiEntry = 16           # RSI的开仓信号
    trailingPercent = 0.8   # 百分比移动止损
    initDays = 10           # 初始化数据所用天数

    #策略变量
    bar = None                  # K线对象
    barMinite = EMPTY_STRING    # K线当前分钟数

    bufferSize = 100                    # 需要缓存数据的大小
    bufferCount = 0                     # 已经缓存的数据大小
    highArray = np.zeros(bufferSize)    # K线最高价数组
    lowArray = np.zeros(bufferSize)     # K线最低价数组
    closeArray = np.zeros(bufferSize)   # K线收盘价数组

    atrCount = 0                        # 目前已缓存的ATR计数
    atrArray = np.zeros(bufferSize)     # ATR指标的数组
    atrValue = 0                        # 最新的ATR指标值
    atrMa = 0                           # ATR移动平均的数值

    rsiValue = 0                        # RSI指标的数值
    rsiBuy = 0                          # RSI买开阀值
    rsiSell = 0                         # RSI卖开阀值
    intraTradeHigh = 0                  # 移动止损用的持仓周期内最高价
    intraTradeLow = 0                   # 移动止损用的持仓周期内最低价

    orderList = []                      # 保持委托代码的列表

    # 参数列表，保存了参数的名称
    paramList = [   'name',
                    'className',
                    'author',
                    'vtSymbol',
                    'atrLength',
                    'atrMaLength',
                    'rsiLength',
                    'rsiEntry',
                    'trailingPercent'   ]

    # 变量名称，保存了变量的名称
    varList = [ 'inited',
                'trading',
                'pos',
                'atrValue',
                'atrMa',
                'rsiValue',
                'rsiBuy',
                'rsiSell']

    # -------------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        '''Constructor'''
        super(AtrRsiStrategy, self).__init__(ctaEngine, setting)

    # ----------------------------------------------------------------------
    def onInit(self):
        '''初始化策略，必须由用户继承实现'''
        self.writeCtaLog(u'%s策略初始化' %self.name)

        # 初始化RSI进场阀值
        self.rsiBuy = 50 + self.rsiEntry
        self.rsiSell = 50 - self.rsiEntry

        # 载入历史数据，并采用回放计算的方式初始化策略数值
        initData = self.loadBar(self.initDays)
        for bar in initData:
            self.onBar(bar)

        self.putEvent()

    # -------------------------------------------------------------
    def onStart(self):
        '''策略启动，必须由用户继承实现'''
        self.writeCtaLog(u'%s策略启动' %self.name)
        self.putEvent()

    # ----------------------------------------------------
    def onStop(self):
        '''策略停止，必须由用户继承实现'''
        self.writeCtaLog(u'%s策略停止' %self.name)
        self.putEvent()

    # -----------------------------------------------------
    def onTick(self, tick):
        '''收到行情Tick推送，必须由用户继承实现'''
        # 计算K线
        tickMinite = tick.datetime.nimute

        if tickMinite != self.barMinite:
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
            bar.datetime = tick.datetime    # K 线的时间设为第一个tick的时间

            self.bar = bar                  # 这种写法为了减少一层访问，加快速度
            self.barMinite = tickMinite     # 更新当前的分钟
        else:
            bar = self.bar                  # 写法同样为了加快速度

            bar.high = max(bar.high, tick.lastPrice)
            bar.low = min(bar.low, tick.lastPrice)
            bar.close = tick.lastPrice

    # --------------------------------------------------------
    def onBar(self, bar):
        '''收到行情Bar数据推送，必须由用户继承实现'''
        print bar.datetime

        # 撤销之前发出的尚未成交的委托，包括限价单和停止单
        for orderID in self.orderList:
            self.cancelOrder(orderID)
        self.orderList = []

        # 保存K线数据 - Rock???
        # self.closeList.append(bar.close)
        # self.closeList.pop(0)
        # ay = np.array(self.closeList)

        self.closeArray[0:self.bufferSize-1] =  self.closeArray[1:self.bufferSize]
        self.highArray[0:self.bufferSize-1] =  self.highArray[1:self.bufferSize]
        self.lowArray[0:self.bufferSize-1] =  self.lowArray[1:self.bufferSize]

        self.closeArray[-1] = bar.close
        self.highArray[-1] = bar.high
        self.lowArray[-1] = bar.low

        self.bufferCount += 1
        if self.bufferCount < self.bufferSize:
            return

        # 计算指标数值
        self.atrValue = talib.ATR(  self.highArray,
                                    self.lowArray,
                                    self.closeArray,
                                    self.atrLength)[-1]
        self.atrArray[0:self.bufferSize-1] = self.atrArray[1:self.bufferSize]
        self.atrArray[-1] = self.atrValue

        self.atrCount += 1
        if self.atrCount < self.bufferSize:
            return

        self.atrMa = talib.MA(  self.atrArray,
                                self.atrMaLength)[-1]
        self.rsiValue = talib.RSI(   self.closeArray,
                                    self.rsiLength)[-1]

        # 判断是否要进行交易

        # 当前无仓位
        if self.pos == 0:
            self.intraTradeHigh = bar.high
            self.intraTradeLow = bar.low

            # ATR 上穿其移动平均线，说明含情短期内波动加大
            # 即处于趋势的概率大，适合CTA开仓
            if self.atrValue > self.atrMa:
                # 使用RSI指标的趋势行情时，会在超买超卖区钝化特征，作为开仓信号
                if self.rsiValue > self.rsiBuy:
                    # 这里为了保证成交，选择超价5个整数点下单
                    self.buy(bar.close+5,1)
                    return

                if self.rsiValue < self.rsiSell:
                    self.short(bar.close-5,1)
                    return

        # 持有多头仓位
        if self.pos == 1:
            # 计算多头持有期内的最高价，以及重置最低价
            self.intraTradeHigh = max(self.intraTradeHigh, bar.high)
            self.intraTradeLow = bar.low
            # 计算多头移动止损
            longStop = self.intraTradeHigh * (1-self.trailingPercent/100)
            # 发出本地止损委托，并把委托号记录下来，用于后续撤单
            orderID = self.sell(longStop, 1, stop = True)
            self.orderList.append(orderID)
            return

        # 持有空头仓位
        if self.pos == -1:
            self.intraTradeLow = min(self.intraTradeLow, bar.low)
            self.intraTradeHigh = bar.high

            shortStop = self.intraTradeLow * (1+self.trailingPercent/100)
            orderID = self.cover(shortStop, 1, stop=True)
            self.orderList.append(orderID)
            return

        # 发出状态更新事件
        self.putEvent()

    # -------------------------------------------------------------------------
    def onOrder(self, order):
        '''收到委托变化推送，必须由用户继承实现'''
        pass

    # -------------------------------------------------------------------------
    def onTrade(self, trade):
        pass


    if __name__ == '__main__':
        # 提供直接双击回测的功能
        # 导入pyQT4的包，保证matplotlib使用pyqt而不是pyside
        from ctaBacktesting import *
        from PyQt4 import QtCore, QtGui

        # 创建回测引擎
        engine = BacktestingEngine()

        # 设置回测模式为K线
        engine.setBacktestingMode(engine.BAR_MODE)

        # 设置回测用的数据起始日期
        engine.setStartDate('20120101')

        # 载入历史数据到引擎
        engine.loadHistoryData(MINUTE_DB_NAME,'IF0000')

        #设置产品相关参数
        engine.setSlippage(0.2)         # 股指1跳
        engine.setRate(0.3/10000)       # 万0.3
        engine.setSize(300)             # 点值

        # 在引擎中创建策略对象
        engine.initStrategy(AtrRsiStrategy, {})

        # 开始跑回测
        engine.runBacktesting()

        # 显示回测结果
        engine.showBacktestingResult()

