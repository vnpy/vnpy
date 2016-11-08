# encoding: UTF-8
"""
This file tweaks ctaTemplate Module to suit multi-TimeFrame strategies.
"""

from strategyAtrRsi import *
from ctaBase import *
from ctaTemplate import CtaTemplate

########################################################################
class TC11(CtaTemplate):

    # Strategy name and author
    className = "TC11"
    author = "Zenacon"

    # Set MongoDB DataBase
    barDbName = "TestData"

    # Strategy parameters
    pGeneric_prd = 21
    pGeneric_on = True

    pATRprd_F = 13
    pATRprd_M = 21
    pATRprd_S = 63

    pBOSSplus_prd = 98
    pBOSSminus_prd = 22

    if pGeneric_on == 0:
        pRSIprd = 20
        pBBprd = 10
        pBB_ATRprd = 15
        pATRprd = 21
        pDMIprd = 21
    else:
        pRSIprd =       \
        pBBprd =        \
        pBB_ATRprd =    \
        pATRprd =       \
        pDMIprd = pGeneric_prd

    pBOSS_Mult = 1.75

    # Strategy variables
    vOBO_initialpoint = EMPTY_FLOAT
    vOBO_Stretch = EMPTY_FLOAT
    vOBO_level_L = EMPTY_FLOAT
    vOBO_level_S = EMPTY_FLOAT

    # parameters' list, record names of parameters
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol']

    # variables' list, record names of variables
    varList = ['inited',
               'trading',
               'pos']

    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(TC11, self).__init__(ctaEngine, setting)

    # ----------------------------------------------------------------------
    def onBar(self, bar, **kwargs):
        """收到Bar推送（必须由用户继承实现）"""
        # 撤销之前发出的尚未成交的委托（包括限价单和停止单）
        for orderID in self.orderList:
            self.cancelOrder(orderID)
        self.orderList = []

        # Record new information bar
        if "infobar" in kwargs:
            for i in kwargs["infobar"]:
                if kwargs["infobar"][i] is None:
                    pass
                else:
                    # print kwargs["infobar"][i]["close"]
                    self.closeArray[0:self.bufferSize - 1] = self.closeArray[1:self.bufferSize]
                    self.highArray[0:self.bufferSize - 1] = self.highArray[1:self.bufferSize]
                    self.lowArray[0:self.bufferSize - 1] = self.lowArray[1:self.bufferSize]

                    self.closeArray[-1] = bar.close
                    self.highArray[-1] = bar.high
                    self.lowArray[-1] = bar.low

        """
        Record new bar
        """
        self.closeArray[0:self.bufferSize - 1] = self.closeArray[1:self.bufferSize]
        self.highArray[0:self.bufferSize - 1] = self.highArray[1:self.bufferSize]
        self.lowArray[0:self.bufferSize - 1] = self.lowArray[1:self.bufferSize]

        self.closeArray[-1] = bar.close
        self.highArray[-1] = bar.high
        self.lowArray[-1] = bar.low

        self.bufferCount += 1
        if self.bufferCount < self.bufferSize:
            return

        """
        Calculate Indicators
        """

        vOBO_initialpoint = self.dataHTF_filled['Open']
        vOBO_Stretch = self.vATR['htf'].m * self.pBOSS_Mult

        self.atrValue = talib.ATR(self.highArray,
                                  self.lowArray,
                                  self.closeArray,
                                  self.atrLength)[-1]
        self.atrArray[0:self.bufferSize - 1] = self.atrArray[1:self.bufferSize]
        self.atrArray[-1] = self.atrValue

        self.atrCount += 1
        if self.atrCount < self.bufferSize:
            return

        self.atrMa = talib.MA(self.atrArray,
                              self.atrMaLength)[-1]
        self.rsiValue = talib.RSI(self.closeArray,
                                  self.rsiLength)[-1]

        # 判断是否要进行交易

        # 当前无仓位
        if self.pos == 0:
            self.intraTradeHigh = bar.high
            self.intraTradeLow = bar.low

            # ATR数值上穿其移动平均线，说明行情短期内波动加大
            # 即处于趋势的概率较大，适合CTA开仓
            if self.atrValue > self.atrMa:
                # 使用RSI指标的趋势行情时，会在超买超卖区钝化特征，作为开仓信号
                if self.rsiValue > self.rsiBuy:
                    # 这里为了保证成交，选择超价5个整指数点下单
                    self.buy(bar.close + 5, 1)

                elif self.rsiValue < self.rsiSell:
                    self.short(bar.close - 5, 1)

        # 持有多头仓位
        elif self.pos > 0:
            # 计算多头持有期内的最高价，以及重置最低价
            self.intraTradeHigh = max(self.intraTradeHigh, bar.high)
            self.intraTradeLow = bar.low
            # 计算多头移动止损
            longStop = self.intraTradeHigh * (1 - self.trailingPercent / 100)
            # 发出本地止损委托，并且把委托号记录下来，用于后续撤单
            orderID = self.sell(longStop, 1, stop=True)
            self.orderList.append(orderID)

        # 持有空头仓位
        elif self.pos < 0:
            self.intraTradeLow = min(self.intraTradeLow, bar.low)
            self.intraTradeHigh = bar.high

            shortStop = self.intraTradeLow * (1 + self.trailingPercent / 100)
            orderID = self.cover(shortStop, 1, stop=True)
            self.orderList.append(orderID)

        # 发出状态更新事件
        self.putEvent()

########################################################################
class Prototype(AtrRsiStrategy):

    """
    "infoArray" 字典是用来储存辅助品种信息的, 可以是同品种的不同分钟k线, 也可以是不同品种的价格。

    调用的方法:
    self.infoArray["数据库名 + 空格 + collection名"]["close"]
    self.infoArray["数据库名 + 空格 + collection名"]["high"]
    self.infoArray["数据库名 + 空格 + collection名"]["low"]
    """
    infoArray = {}
    initInfobar = {}

    def __int__(self):
        super(Prototype, self).__int__()

    # ----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        self.writeCtaLog(u'%s策略初始化' % self.name)

        # 初始化RSI入场阈值
        self.rsiBuy = 50 + self.rsiEntry
        self.rsiSell = 50 - self.rsiEntry

        # 载入历史数据，并采用回放计算的方式初始化策略数值
        initData = self.loadBar(self.initDays)
        for bar in initData:

            # 推送新数据, 同时检查是否有information bar需要推送
            # Update new bar, check whether the Time Stamp matching any information bar
            ibar = self.checkInfoBar(bar)
            self.onBar(bar, infobar=ibar)

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
            if data['datetime'] <= bar.datetime:
                try:
                    temp[info_symbol] = CtaBarData()
                    temp[info_symbol].__dict__ = data
                    self.initInfobar[info_symbol] = next(initInfoCursorDict[info_symbol])
                except StopIteration:
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
                    "low": np.zeros(self.bufferSize)
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

                self.infoArray[name]["close"][-1] = data.close
                self.infoArray[name]["high"][-1] = data.high
                self.infoArray[name]["low"][-1] = data.low

    # ----------------------------------------------------------------------
    def onBar(self, bar, **kwargs):
        """收到Bar推送（必须由用户继承实现）"""
        # 撤销之前发出的尚未成交的委托（包括限价单和停止单）
        for orderID in self.orderList:
            self.cancelOrder(orderID)
        self.orderList = []

        # Update infomation data
        # "infobar"是由不同时间或不同品种的品种数据组成的字典, 如果和执行品种的 TimeStamp 不匹配,
        # 则传入的是"None", 当time stamp和执行品种匹配时, 传入的是"Bar"
        self.updateInfoArray(kwargs["infobar"])

        # 保存K线数据
        self.closeArray[0:self.bufferSize - 1] = self.closeArray[1:self.bufferSize]
        self.highArray[0:self.bufferSize - 1] = self.highArray[1:self.bufferSize]
        self.lowArray[0:self.bufferSize - 1] = self.lowArray[1:self.bufferSize]

        self.closeArray[-1] = bar.close
        self.highArray[-1] = bar.high
        self.lowArray[-1] = bar.low

        # 若读取的缓存数据不足, 不考虑交易
        self.bufferCount += 1
        if self.bufferCount < self.bufferSize:
            return

        # 计算指标数值

        # 计算不同时间下的ATR数值

        # Only trading when information bar changes
        # 只有在30min或者1d K线更新后才可以交易
        TradeOn = False
        if any([i is not None for i in kwargs["infobar"].values()]):

            TradeOn = True
            self.scaledAtrValue1M = talib.ATR(self.highArray,
                                       self.lowArray,
                                       self.closeArray,
                                       self.atrLength)[-1] * (25) ** (0.5)
            self.atrValue30M = talib.abstract.ATR(self.infoArray["TestData @GC_30M"])[-1]
            self.rsiValue = talib.abstract.RSI(self.infoArray["TestData @GC_30M"], self.rsiLength)[-1]

        self.atrCount += 1
        if self.atrCount < self.bufferSize:
            return

        # 判断是否要进行交易

        # 当前无仓位
        if (self.pos == 0 and TradeOn == True):
            self.intraTradeHigh = bar.high
            self.intraTradeLow = bar.low

            # 1Min调整后ATR大于30MinATR
            # 即处于趋势的概率较大，适合CTA开仓
            if self.atrValue30M < self.scaledAtrValue1M:
                # 使用RSI指标的趋势行情时，会在超买超卖区钝化特征，作为开仓信号
                if self.rsiValue > self.rsiBuy:
                    # 这里为了保证成交，选择超价5个整指数点下单
                    self.buy(bar.close+5, 1)

                elif self.rsiValue < self.rsiSell:
                    self.short(bar.close-5, 1)

                # 下单后, 在下一个30Min K线之前不交易
                TradeOn = False

        # 持有多头仓位
        elif self.pos > 0:
            # 计算多头持有期内的最高价，以及重置最低价
            self.intraTradeHigh = max(self.intraTradeHigh, bar.high)
            self.intraTradeLow = bar.low
            # 计算多头移动止损
            longStop = self.intraTradeHigh * (1 - self.trailingPercent / 100)
            # 发出本地止损委托，并且把委托号记录下来，用于后续撤单
            orderID = self.sell(longStop, 1, stop=True)
            self.orderList.append(orderID)

        # 持有空头仓位
        elif self.pos < 0:
            self.intraTradeLow = min(self.intraTradeLow, bar.low)
            self.intraTradeHigh = bar.high

            shortStop = self.intraTradeLow * (1 + self.trailingPercent / 100)
            orderID = self.cover(shortStop, 1, stop=True)
            self.orderList.append(orderID)

        # 发出状态更新事件
        self.putEvent()


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
    engine.setStartDate('20100101')
    engine.setDatabase("TestData", "@GC_1M", info_symbol=[("TestData","@GC_30M")])

    # Set parameters for strategy
    d = {'atrLength': 11}
    engine.initStrategy(Prototype, d)

    # 设置产品相关参数
    engine.setSlippage(0.2)  # 股指1跳
    engine.setCommission(0.3 / 10000)  # 万0.3
    engine.setSize(300)  # 股指合约大小

    # 开始跑回测
    start = time.time()

    engine.runBacktesting()

    # 显示回测结果
    engine.showBacktestingResult()

    print 'Time consumed：%s' % (time.time() - start)