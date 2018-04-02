# encoding: UTF-8

# AUTHOR:李来佳
# WeChat/QQ: 28888502


from datetime import datetime
import talib as ta
import numpy as np
import math
import copy,csv
from pykalman import KalmanFilter

from vnpy.trader.app.ctaStrategy.ctaBase import *
from vnpy.trader.vtConstant import *
from vnpy.trader.app.ctaStrategy.ctaPeriod import *

DEBUGCTALOG = True

PERIOD_SECOND = 'second'  # 秒级别周期
PERIOD_MINUTE = 'minute'  # 分钟级别周期
PERIOD_HOUR = 'hour'  # 小时级别周期
PERIOD_DAY = 'day'  # 日级别周期

class CtaLineBar(object):
    """CTA K线"""
    """ 使用方法:
    1、在策略构造函数__init()中初始化
    self.lineM = None                       # 1分钟K线
    lineMSetting = {}
    lineMSetting['name'] = u'M1'
    lineMSetting['barTimeInterval'] = 60    # 1分钟对应60秒
    lineMSetting['inputEma1Len'] = 7        # EMA线1的周期
    lineMSetting['inputEma2Len'] = 21       # EMA线2的周期
    lineMSetting['inputBollLen'] = 20       # 布林特线周期
    lineMSetting['inputBollStdRate'] = 2    # 布林特线标准差
    lineMSetting['minDiff'] = self.minDiff  # 最小条
    lineMSetting['shortSymbol'] = self.shortSymbol  #商品短号
    self.lineM = CtaLineBar(self, self.onBar, lineMSetting)

    2、在onTick()中，需要导入tick数据
    self.lineM.onTick(tick)
    self.lineM5.onTick(tick) # 如果你使用2个周期

    3、在onBar事件中，按照k线结束使用；其他任何情况下bar内使用，通过对象使用即可，self.lineM.lineBar[-1].close

    """

    # 区别：
    # -使用tick模式时，当tick到达后，最新一个lineBar[-1]是当前的正在拟合的bar，不断累积tick，传统按照OnBar来计算的话，是使用LineBar[-2]。
    # -使用bar模式时，当一个bar到达时，lineBar[-1]是当前生成出来的Bar,不再更新
    TICK_MODE = 'tick'
    BAR_MODE = 'bar'

    # 参数列表，保存了参数的名称
    paramList = ['vtSymbol']
    # 参数列表

    def __init__(self, strategy, onBarFunc, setting=None):

        # OnBar事件回调函数
        self.onBarFunc = onBarFunc

        # 周期变更事件回调函数
        self.onPeriodChgFunc = None

        # K 线服务的策略
        self.strategy = strategy

        # 创建内部变量
        self.init_properties()

        if setting:
            self.setParam(setting)

            # 修正精度
            if self.minDiff < 1:
                self.round_n = 7

            ## 导入卡尔曼过滤器
            if self.inputKF:
                try:
                    self.kf = KalmanFilter(transition_matrices=[1],
                                      observation_matrices=[1],
                                      initial_state_mean=0,
                                      initial_state_covariance=1,
                                      observation_covariance=1,
                                      transition_covariance=0.01)
                except :
                    self.writeCtaLog(u'导入卡尔曼过滤器失败,需先安装 pip install pykalman')
                    self.inputKF = False

    def init_properties(self):
        """
        初始化内部变量
        :return:
        """
        self.paramList.append('barTimeInterval')
        self.paramList.append('period')
        self.paramList.append('inputPreLen')
        self.paramList.append('inputEma1Len')
        self.paramList.append('inputEma2Len')
        self.paramList.append('inputEma3Len')
        self.paramList.append('inputMa1Len')
        self.paramList.append('inputMa2Len')
        self.paramList.append('inputMa3Len')
        self.paramList.append('inputDmiLen')
        self.paramList.append('inputDmiMax')
        self.paramList.append('inputAtr1Len')
        self.paramList.append('inputAtr2Len')
        self.paramList.append('inputAtr3Len')
        self.paramList.append('inputVolLen')
        self.paramList.append('inputRsi1Len')
        self.paramList.append('inputRsi2Len')
        self.paramList.append('inputCmiLen')
        self.paramList.append('inputBollLen')
        self.paramList.append('inputBollStdRate')
        self.paramList.append('inputKdjLen')
        self.paramList.append('inputCciLen')
        self.paramList.append('inputMacdFastPeriodLen')
        self.paramList.append('inputMacdSlowPeriodLen')
        self.paramList.append('inputMacdSignalPeriodLen')
        self.paramList.append('inputKF')
        self.paramList.append('inputSkd')
        self.paramList.append('inputYb')

        self.paramList.append('minDiff')
        self.paramList.append('shortSymbol')
        self.paramList.append('activeDayJump')
        self.paramList.append('name')

        # 输入参数
        self.name = u'LineBar'
        self.mode = self.TICK_MODE  # 缺省为tick模式
        self.period = PERIOD_SECOND  # 缺省为分钟级别周期
        self.barTimeInterval = 300  # 缺省为5分钟周期

        self.barMinuteInterval = self.barTimeInterval / 60

        self.inputPreLen = EMPTY_INT  # 1

        self.inputMa1Len = EMPTY_INT  # 10
        self.inputMa2Len = EMPTY_INT  # 20
        self.inputMa3Len = EMPTY_INT  # 120

        self.inputEma1Len = EMPTY_INT  # 13
        self.inputEma2Len = EMPTY_INT  # 21
        self.inputEma3Len = EMPTY_INT  # 120

        self.inputDmiLen = EMPTY_INT  # 14           # DMI的计算周期
        self.inputDmiMax = EMPTY_FLOAT  # 30           # Dpi和Mdi的突破阈值

        self.inputAtr1Len = EMPTY_INT  # 10           # ATR波动率的计算周期(近端）
        self.inputAtr2Len = EMPTY_INT  # 26           # ATR波动率的计算周期（常用）
        self.inputAtr3Len = EMPTY_INT  # 50           # ATR波动率的计算周期（远端）

        self.inputVolLen = EMPTY_INT  # 14           # 平均交易量的计算周期

        self.inputRsi1Len = EMPTY_INT  # 7     # RSI 相对强弱指数（快曲线）
        self.inputRsi2Len = EMPTY_INT  # 14    # RSI 相对强弱指数（慢曲线）

        self.shortSymbol = EMPTY_STRING  # 商品的短代码
        self.minDiff = 1  # 商品的最小价格单位
        self.round_n = 4  # round() 小数点的截断数量
        self.activeDayJump = False  # 隔夜跳空

        # 当前的Tick
        self.curTick = None
        self.lastTick = None
        self.curTradingDay = EMPTY_STRING

        # K线保存数据
        self.bar = None  # K线数据对象
        self.lineBar = []  # K线缓存数据队列
        self.barFirstTick = False  # K线的第一条Tick数据

        # K 线的相关计算结果数据

        self.preHigh = []  # K线的前inputPreLen的的最高
        self.preLow = []  # K线的前inputPreLen的的最低

        self.lineMa1 = []  # K线的MA1均线，周期是InputMaLen1，不包含当前bar
        self.lineMa2 = []  # K线的MA2均线，周期是InputMaLen2，不包含当前bar
        self.lineMa3 = []  # K线的MA2均线，周期是InputMaLen2，不包含当前bar

        self.lineEma1 = []  # K线的EMA1均线，周期是InputEmaLen1，不包含当前bar
        self.lineEma2 = []  # K线的EMA2均线，周期是InputEmaLen2，不包含当前bar
        self.lineEma3 = []  # K线的EMA3均线，周期是InputEmaLen3，不包含当前bar

        # K线的DMI( Pdi，Mdi，ADX，Adxr) 计算数据
        self.barPdi = EMPTY_FLOAT  # bar内的升动向指标，即做多的比率
        self.barMdi = EMPTY_FLOAT  # bar内的下降动向指标，即做空的比率

        self.linePdi = []  # 升动向指标，即做多的比率
        self.lineMdi = []  # 下降动向指标，即做空的比率

        self.lineDx = []  # 趋向指标列表，最大长度为inputM*2
        self.barAdx = EMPTY_FLOAT  # Bar内计算的平均趋向指标
        self.lineAdx = []  # 平均趋向指标
        self.barAdxr = EMPTY_FLOAT  # 趋向平均值，为当日ADX值与M日前的ADX值的均值
        self.lineAdxr = []  # 平均趋向变化指标

        # K线的基于DMI、ADX计算的结果
        self.barAdxTrend = EMPTY_FLOAT  # ADX值持续高于前一周期时，市场行情将维持原趋势
        self.barAdxrTrend = EMPTY_FLOAT  # ADXR值持续高于前一周期时,波动率比上一周期高

        self.buyFilterCond = False  # 多过滤器条件,做多趋势的判断，ADX高于前一天，上升动向> inputMM
        self.sellFilterCond = False  # 空过滤器条件,做空趋势的判断，ADXR高于前一天，下降动向> inputMM

        # K线的ATR技术数据
        self.lineAtr1 = []  # K线的ATR1,周期为inputAtr1Len
        self.lineAtr2 = []  # K线的ATR2,周期为inputAtr2Len
        self.lineAtr3 = []  # K线的ATR3,周期为inputAtr3Len

        self.barAtr1 = EMPTY_FLOAT
        self.barAtr2 = EMPTY_FLOAT
        self.barAtr3 = EMPTY_FLOAT

        # K线的交易量平均
        self.lineAvgVol = []  # K 线的交易量平均

        # K线的RSI计算数据
        self.lineRsi1 = []  # 记录K线对应的RSI数值，只保留inputRsi1Len*8
        self.lineRsi2 = []  # 记录K线对应的RSI数值，只保留inputRsi2Len*8

        self.lowRsi = 30  # RSI的最低线
        self.highRsi = 70  # RSI的最高线

        self.lineRsiTop = []  # 记录RSI的最高峰，只保留 inputRsiLen个
        self.lineRsiButtom = []  # 记录RSI的最低谷，只保留 inputRsiLen个
        self.lastRsiTopButtom = {}  # 最近的一个波峰/波谷

        # K线的CMI计算数据
        self.inputCmiLen = EMPTY_INT
        self.lineCmi = []  # 记录K线对应的Cmi数值，只保留inputCmiLen*8

        # K线的布林特计算数据
        self.inputBollLen = EMPTY_INT  # K线周期
        self.inputBollStdRate = 1.5  # 两倍标准差
        self.lineBollClose = []  # 用于运算的close价格列表
        self.lineUpperBand = []  # 上轨
        self.lineMiddleBand = []  # 中线
        self.lineLowerBand = []  # 下轨
        self.lineBollStd = []  # 标准差

        self.lastBollUpper = EMPTY_FLOAT  # 最后一根K的Boll上轨数值（与MinDiff取整）
        self.lastBollMiddle = EMPTY_FLOAT  # 最后一根K的Boll中轨数值（与MinDiff取整）
        self.lastBollLower = EMPTY_FLOAT  # 最后一根K的Boll下轨数值（与MinDiff取整+1）

        # K线的KDJ指标计算数据
        self.inputKdjLen = EMPTY_INT  # KDJ指标的长度,缺省是9
        self.lineK = []  # K为快速指标
        self.lineD = []  # D为慢速指标
        self.lineJ = []  #
        self.lineKdjTop = []  # 记录KDJ最高峰，只保留 inputKdjLen个
        self.lineKdjButtom = []  # 记录KDJ的最低谷，只保留 inputKdjLen个
        self.lastKdjTopButtom = {}  # 最近的一个波峰/波谷
        self.lastK = EMPTY_FLOAT  # bar内计算时，最后一个未关闭的bar的实时K值
        self.lastD = EMPTY_FLOAT  # bar内计算时，最后一个未关闭的bar的实时值
        self.lastJ = EMPTY_FLOAT  # bar内计算时，最后一个未关闭的bar的实时J值

        # K线的MACD计算数据
        self.inputMacdFastPeriodLen = EMPTY_INT
        self.inputMacdSlowPeriodLen = EMPTY_INT
        self.inputMacdSignalPeriodLen = EMPTY_INT

        self.lineDif = []  # DIF = EMA12 - EMA26，即为talib-MACD返回值macd
        self.lineDea = []  # DEA = （前一日DEA X 8/10 + 今日DIF X 2/10），即为talib-MACD返回值
        self.lineMacd = []  # (dif-dea)*2，但是talib中MACD的计算是bar = (dif-dea)*1,国内一般是乘以2

        # K 线的CCI计算数据
        self.inputCciLen = EMPTY_INT
        self.lineCci = []

        # 卡尔曼过滤器
        self.inputKF = False
        self.kf = None
        self.lineStateMean = []
        self.lineStateCovar = []

        # 周期
        self.atan = None
        self.atan_list = []
        self.curPeriod = None  # 当前所在周期
        self.periods = []

        # 优化的多空动量线
        self.inputSkd = False
        self.inputSkdLen1 = 13  # 周期1
        self.inputSkdLen2 = 8  # 周期2
        self.lineSK = []  # 快线
        self.lineSD = []  # 慢线
        self.lowSkd = 30
        self.highSkd = 70

        # 多空趋势线
        self.inputYb = False
        self.lineYb = []

    def setParam(self, setting):
        """设置参数"""
        d = self.__dict__
        for key in self.paramList:
            if key in setting:

                d[key] = setting[key]

    def setMode(self,mode):
        """Tick/Bar模式"""
        self.mode = mode

    def onTick(self, tick):
        """行情更新
        :type tick: object
        """
        # Tick 有效性检查
        #if (tick.datetime- datetime.now()).seconds > 10:
        #    self.writeCtaLog(u'无效的tick时间:{0}'.format(tick.datetime))
        #    return

        if tick.datetime.hour == 8 or tick.datetime.hour == 20:
            self.writeCtaLog(u'竞价排名tick时间:{0}'.format(tick.datetime))
            return
        if self.lastTick is None:
            self.lastTick = tick

        self.curTick = tick

        # 3.生成x K线，若形成新Bar，则触发OnBar事件
        self.__drawLineBar(tick)

        self.lastTick = tick

        # 更新curPeriod的High，low
        if self.curPeriod is not None:
            if self.curTick.lastPrice is None:
                self.curTick.lastPrice = (self.curTick.askPrice1 + self.curTick.bidPrice1) / 2

            self.curPeriod.onPrice(self.curTick.lastPrice)

        # 4.执行 bar内计算
        self.__recountKdj(countInBar=True)

    def addBar(self, bar, bar_is_completed=False):
        """
        予以外部初始化程序增加bar
        :param bar: 
        :param bar_is_completed: 插入的bar，其周期与K线周期一致，就设为True
        :return: 
        """
        l1 = len(self.lineBar)

        if l1 == 0:
            new_bar = copy.copy(bar)
            self.lineBar.append(new_bar)
            self.curTradingDay = bar.date
            self.onBar(bar)
            return

        # 与最后一个BAR的时间比对，判断是否超过K线的周期
        lastBar = self.lineBar[-1]
        self.curTradingDay = bar.tradingDay

        is_new_bar = False
        if bar_is_completed:
            is_new_bar = True

        if self.period == PERIOD_SECOND and (bar.datetime-lastBar.datetime).seconds >= self.barTimeInterval:
            is_new_bar = True

        elif self.period == PERIOD_MINUTE and (bar.datetime - lastBar.datetime).seconds >= self.barTimeInterval*60:
            is_new_bar = True

        elif self.period == PERIOD_HOUR:
            if self.barTimeInterval == 1 and bar.datetime.hour != lastBar.datetime.hour :
                is_new_bar = True
            elif self.barTimeInterval == 2 and bar.datetime.hour != lastBar.datetime.hour \
                    and bar.datetime.hour in {1, 9, 11, 13, 15, 21, 23}:
                is_new_bar = True
            elif self.barTimeInterval == 4 and bar.datetime.hour != lastBar.datetime.hour \
                 and bar.datetime.hour in {1, 9, 13, 21}:
                is_new_bar = True

        elif self.period == PERIOD_DAY and bar.datetime.date != lastBar.datetime.date :
            is_new_bar = True

        if is_new_bar:
            # 添加新的bar
            new_bar = copy.deepcopy(bar)
            self.lineBar.append(new_bar)
            # 将上一个Bar推送至OnBar事件
            self.onBar(lastBar)
            return

        # 更新最后一个bar
        # 此段代码，针对一部分短周期生成长周期的k线更新，如3根5分钟k线，合并成1根15分钟k线。
        lastBar.close = bar.close
        lastBar.high = max(lastBar.high, bar.high)
        lastBar.low = min(lastBar.low, bar.low)
        lastBar.volume = lastBar.volume + bar.volume
        lastBar.dayVolume = bar.dayVolume

        lastBar.mid3 = round((lastBar.close + lastBar.high + lastBar.low) / 3, self.round_n)
        lastBar.mid4 = round((2*lastBar.close + lastBar.high + lastBar.low)/4, self.round_n)
        lastBar.mid5 = round((2*lastBar.close + lastBar.open + lastBar.high + lastBar.low)/5, self.round_n)

    def onBar(self, bar):
        """OnBar事件"""
        # 计算相关数据
        bar.mid3 = round(( bar.close + bar.high + bar.low)/3, self.round_n)
        bar.mid4 = round((2*bar.close + bar.high + bar.low)/4, self.round_n)
        bar.mid5 = round((2*bar.close + bar.open + bar.high + bar.low)/5, self.round_n)

        self.__recountPreHighLow()
        self.__recountMa()
        self.__recountEma()
        self.__recountDmi()
        self.__recountAtr()
        self.__recoundAvgVol()
        self.__recountRsi()
        self.__recountCmi()
        self.__recountKdj()
        self.__recountBoll()
        self.__recountMacd()
        self.__recountCci()
        self.__recountKF()
        self.__recountPeriod(bar)
        self.__recountSKD()
        self.__recountYB()
        # 回调上层调用者
        self.onBarFunc(bar)

    def displayLastBar(self):
        """显示最后一个Bar的信息"""
        msg = u'['+self.name+u']'

        if len(self.lineBar) < 2:
            return msg

        if self.mode == self.TICK_MODE:
            displayBar = self.lineBar[-2]
        else:
            displayBar = self.lineBar[-1]

        msg = msg + u'{0} o:{1};h:{2};l:{3};c:{4},v:{5}'.\
            format(displayBar.date+' '+displayBar.time, displayBar.open, displayBar.high,
                   displayBar.low, displayBar.close, displayBar.volume)

        if self.inputMa1Len > 0 and len(self.lineMa1) > 0:
            msg = msg + u',MA({0}):{1}'.format(self.inputMa1Len, self.lineMa1[-1])

        if self.inputMa2Len > 0 and len(self.lineMa2) > 0:
            msg = msg + u',MA({0}):{1}'.format(self.inputMa2Len, self.lineMa2[-1])

        if self.inputMa3Len > 0 and len(self.lineMa3) > 0:
            msg = msg + u',MA({0}):{1}'.format(self.inputMa3Len, self.lineMa3[-1])

        if self.inputEma1Len > 0 and len(self.lineEma1) > 0:
            msg = msg + u',EMA({0}):{1}'.format(self.inputEma1Len, self.lineEma1[-1])

        if self.inputEma2Len > 0 and len(self.lineEma2) > 0:
            msg = msg + u',EMA({0}):{1}'.format(self.inputEma2Len, self.lineEma2[-1])

        if self.inputDmiLen > 0 and len(self.linePdi) > 0:
            msg = msg + u',Pdi:{1};Mdi:{1};Adx:{2}'.format(self.linePdi[-1], self.lineMdi[-1], self.lineAdx[-1])

        if self.inputAtr1Len > 0 and len(self.lineAtr1) > 0:
            msg = msg + u',Atr({0}):{1}'.format(self.inputAtr1Len, self.lineAtr1[-1])

        if self.inputAtr2Len > 0 and len(self.lineAtr2) > 0:
            msg = msg + u',Atr({0}):{1}'.format(self.inputAtr2Len, self.lineAtr2[-1])

        if self.inputAtr3Len > 0 and len(self.lineAtr3) > 0:
            msg = msg + u',Atr({0}):{1}'.format(self.inputAtr3Len, self.lineAtr3[-1])

        if self.inputVolLen > 0 and len(self.lineAvgVol) > 0:
            msg = msg + u',AvgVol({0}):{1}'.format(self.inputVolLen, self.lineAvgVol[-1])

        if self.inputRsi1Len > 0 and len(self.lineRsi1) > 0:
            msg = msg + u',Rsi({0}):{1}'.format(self.inputRsi1Len, self.lineRsi1[-1])

        if self.inputRsi2Len > 0 and len(self.lineRsi2) > 0:
            msg = msg + u',Rsi({0}):{1}'.format(self.inputRsi2Len, self.lineRsi2[-1])

        if self.inputKdjLen > 0 and len(self.lineK) > 0:
            msg = msg + u',KDJ({0}):{1},{2},{3}'.format(self.inputKdjLen,
                                                        round(self.lineK[-1], self.round_n),
                                                        round(self.lineD[-1], self.round_n),
                                                        round(self.lineJ[-1], self.round_n))

        if self.inputCciLen > 0 and len(self.lineCci) > 0:
            msg = msg + u',Cci({0}):{1}'.format(self.inputCciLen, self.lineCci[-1])

        if self.inputBollLen > 0 and len(self.lineUpperBand)>0:
            msg = msg + u',Boll({0}):u:{1},m:{2},l:{3}'.\
                format(self.inputBollLen, round(self.lineUpperBand[-1], self.round_n),
                       round(self.lineMiddleBand[-1], self.round_n), round(self.lineLowerBand[-1]), self.round_n)

        if self.inputMacdFastPeriodLen >0 and len(self.lineDif)>0:
            msg = msg + u',MACD({0},{1},{2}):Dif:{3},Dea{4},Macd:{5}'.\
                format(self.inputMacdFastPeriodLen, self.inputMacdSlowPeriodLen, self.inputMacdSignalPeriodLen,
                       round(self.lineDif[-1], self.round_n),
                       round(self.lineDea[-1], self.round_n),
                       round(self.lineMacd[-1], self.round_n))

        if self.inputKF and len(self.lineStateMean) > 0:
            msg = msg + u',Kalman:{0}'.format(self.lineStateMean[-1])

        if self.inputSkd and len(self.lineSK) > 0 and len(self.lineSD) > 0:
            msg = msg + u',SK:{}/SD:{}'.format( self.lineSK[-1],self.lineSD[-1])

        return msg

    def __firstTick(self, tick):
        """ K线的第一个Tick数据"""

        self.bar = CtaBarData()                  # 创建新的K线
        # 计算K线的整点分钟周期，这里周期最小是1分钟。如果你是采用非整点分钟，例如1.5分钟，请把这段注解掉
        if self.barMinuteInterval and self.period == PERIOD_SECOND:
            self.barMinuteInterval = int(self.barTimeInterval / 60)
            if self.barMinuteInterval < 1:
                self.barMinuteInterval = 1
            fixedMin = int( tick.datetime.minute /self.barMinuteInterval) * self.barMinuteInterval
            tick.datetime = tick.datetime.replace(minute=fixedMin)

        self.bar.vtSymbol = tick.vtSymbol
        self.bar.symbol = tick.symbol
        self.bar.exchange = tick.exchange
        self.bar.openInterest = tick.openInterest

        self.bar.open = tick.lastPrice            # O L H C
        self.bar.high = tick.lastPrice
        self.bar.low = tick.lastPrice
        self.bar.close = tick.lastPrice

        self.bar.mid4 = tick.lastPrice             # 4价均价
        self.bar.mid5 = tick.lastPrice             # 5价均价

        # K线的日期时间
        self.bar.tradingDay = tick.tradingDay    # K线所在的交易日期
        self.bar.date = tick.date                # K线的日期，（夜盘的话，与交易日期不同哦）
        self.bar.datetime = tick.datetime
        # K线的日期时间（去除秒）设为第一个Tick的时间
        self.bar.datetime = self.bar.datetime.replace(second=0, microsecond=0)
        self.bar.time = self.bar.datetime.strftime('%H:%M:%S')

        # K线的日总交易量，k线内交易量
        self.bar.dayVolume = tick.volume
        if self.curTradingDay != self.bar.tradingDay or not self.lineBar:
            # bar的交易日与记录的当前交易日不一致：即该bar为新的交易日,bar的交易量为当前的tick.volume
            self.bar.volume = tick.volume
            self.curTradingDay = self.bar.tradingDay
        else:
            # bar的交易日与记录的当前交易日一致, 交易量为tick的volume，减去上一根bar的日总交易量
            self.bar.volume = tick.volume - self.lineBar[-1].dayVolume

        self.barFirstTick = True                  # 标识该Tick属于该Bar的第一个tick数据

        self.lineBar.append(self.bar)           # 推入到lineBar队列

    # ----------------------------------------------------------------------
    def __drawLineBar(self, tick):
        """生成 line Bar  """

        l1 = len(self.lineBar)

        # 保存第一个K线数据
        if l1 == 0:
            self.__firstTick(tick)
            return

        # 清除480周期前的数据，
        if l1 > 60 * 8:
            del self.lineBar[0]

        # 与最后一个BAR的时间比对，判断是否超过5分钟
        lastBar = self.lineBar[-1]

        # 处理日内的间隔时段最后一个tick，如10:15分，11:30分，15:00 和 2:30分
        endtick = False
        if (tick.datetime.hour == 10 and tick.datetime.minute == 15) \
            or (tick.datetime.hour == 11 and tick.datetime.minute == 30) \
            or (tick.datetime.hour == 15 and tick.datetime.minute == 00) \
            or (tick.datetime.hour == 2 and tick.datetime.minute == 30):
            endtick = True

        # 夜盘1:30收盘
        if self.shortSymbol in NIGHT_MARKET_SQ2 and tick.datetime.hour == 1 and tick.datetime.minute == 00:
            endtick = True

        # 夜盘23:00收盘
        if self.shortSymbol in NIGHT_MARKET_SQ3 and tick.datetime.hour == 23 and tick.datetime.minute == 00:
            endtick = True
        # 夜盘23:30收盘
        if self.shortSymbol in NIGHT_MARKET_ZZ or self.shortSymbol in NIGHT_MARKET_DL:
            if tick.datetime.hour == 23 and tick.datetime.minute == 30:
                endtick = True

        # 满足时间要求
        # 1,秒周期，tick的时间，距离最后一个bar的开始时间，已经超出bar的时间周期（barTimeInterval）
        # 2，分钟、小时周期，取整=0
        # 3、日周期，开盘时间
        # 4、不是最后一个结束tick
        is_new_bar = False

        if ((self.period == PERIOD_SECOND and (tick.datetime-lastBar.datetime).seconds >= self.barTimeInterval) \
            or
                (self.period == PERIOD_MINUTE and tick.datetime.minute % self.barTimeInterval == 0
                 and tick.datetime.minute != self.lastTick.datetime.minute)
            or
                (self.period == PERIOD_HOUR and self.barTimeInterval == 1 and tick.datetime
                 and tick.datetime.hour != self.lastTick.datetime.hour)
            or
                (self.period == PERIOD_HOUR and self.barTimeInterval == 2 and tick.datetime
                    and tick.datetime.hour != self.lastTick.datetime.hour
                    and tick.datetime.hour in {1, 9, 11, 13, 21, 23})
            or
                (self.period == PERIOD_HOUR and self.barTimeInterval == 4 and tick.datetime
                 and tick.datetime.hour != self.lastTick.datetime.hour
                 and tick.datetime.hour in {1, 9, 13, 21})
            or (self.period == PERIOD_DAY and tick.datetime
                and (tick.datetime.hour == 21 or tick.datetime.hour == 9)
                and 14 <= self.lastTick.datetime.hour <= 15)
            ) and not endtick:

            # 创建并推入新的Bar
            self.__firstTick(tick)
            # 触发OnBar事件
            self.onBar(lastBar)

        else:
            # 更新当前最后一个bar
            self.barFirstTick = False

            # 更新最高价、最低价、收盘价、成交量
            lastBar.high = max(lastBar.high, tick.lastPrice)
            lastBar.low = min(lastBar.low, tick.lastPrice)
            lastBar.close = tick.lastPrice

            # 更新日内总交易量，和bar内交易量
            lastBar.dayVolume = tick.volume
            if l1 == 1:
                # 针对第一个bar的tick volume更新
                lastBar.volume = tick.volume
            else:
                # 针对新交易日的第一个bar：于上一个bar的时间在14，当前bar的时间不在14点,初始化为tick.volume
                if self.lineBar[-2].datetime.hour == 14 and tick.datetime.hour != 14 and not endtick:
                    lastBar.volume = tick.volume
                else:
                    # 其他情况，bar为同一交易日，将tick的volume，减去上一bar的dayVolume
                    lastBar.volume = tick.volume - self.lineBar[-2].dayVolume

            # 更新Bar的颜色
            if lastBar.close > lastBar.open:
                lastBar.color = COLOR_RED
            elif lastBar.close < lastBar.open:
                lastBar.color = COLOR_BLUE
            else:
                lastBar.color = COLOR_EQUAL

    # ----------------------------------------------------------------------
    def __recountPreHighLow(self):
        """计算 K线的前周期最高和最低"""

        if self.inputPreLen <= 0:       # 不计算
            return

        # 1、lineBar满足长度才执行计算
        if len(self.lineBar) < self.inputPreLen:
            self.writeCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算High、Low需要：{1}'.
                             format(len(self.lineBar), self.inputPreLen))
            return

        # 2.计算前inputPreLen周期内(不包含当前周期）的Bar高点和低点
        preHigh = EMPTY_FLOAT
        preLow = EMPTY_FLOAT

        if self.mode == self.TICK_MODE:
            idx = 2
        else:
            idx = 1

        for i in range(len(self.lineBar)-idx, len(self.lineBar)-idx-self.inputPreLen, -1):

            if self.lineBar[i].high > preHigh or preHigh == EMPTY_FLOAT:
                preHigh = self.lineBar[i].high    # 前InputPreLen周期高点

            if self.lineBar[i].low < preLow or preLow == EMPTY_FLOAT:
                preLow = self.lineBar[i].low     # 前InputPreLen周期低点

        # 保存
        if len(self.preHigh) > self.inputPreLen * 8:
            del self.preHigh[0]
        self.preHigh.append(preHigh)

        # 保存
        if len(self.preLow)> self.inputPreLen * 8:
            del self.preLow[0]
        self.preLow.append(preLow)

    #----------------------------------------------------------------------
    def __recountMa(self):
        """计算K线的MA1 和MA2"""
        l = len(self.lineBar)

        if not (self.inputMa1Len > 0 or self.inputMa2Len > 0 or self.inputMa3Len > 0):  # 不计算
            return

        # 1、lineBar满足长度才执行计算
        if len(self.lineBar) < max(7, self.inputMa1Len, self.inputMa2Len, self.inputMa3Len)+2:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算MA需要：{1}'.
                             format(len(self.lineBar), max(7, self.inputMa1Len, self.inputMa2Len, self.inputMa3Len)+2))
            return

        # 计算第一条MA均线
        if self.inputMa1Len > 0:
            if self.inputMa1Len > l:
                ma1Len = l
            else:
                ma1Len = self.inputMa1Len

            # 3、获取前InputN周期(不包含当前周期）的K线
            if self.mode == self.TICK_MODE:
                listClose=[x.close for x in self.lineBar[-ma1Len - 1:-1]]
            else:
                listClose=[x.close for x in self.lineBar[-ma1Len:]]

            barMa1 = ta.MA(np.array(listClose, dtype=float), ma1Len)[-1]
            barMa1 = round(float(barMa1), self.round_n)

            if len(self.lineMa1) > self.inputMa1Len*8:
                del self.lineMa1[0]
            self.lineMa1.append(barMa1)

        # 计算第二条MA均线
        if self.inputMa2Len > 0:
            if self.inputMa2Len > l:
                ma2Len = l
            else:
                ma2Len = self.inputMa2Len

            # 3、获取前InputN周期(不包含当前周期）的K线
            if self.mode == self.TICK_MODE:
                listClose=[x.close for x in self.lineBar[-ma2Len - 1:-1]]
            else:
                listClose=[x.close for x in self.lineBar[-ma2Len:]]

            barMa2 = ta.MA(np.array(listClose, dtype=float), ma2Len)[-1]
            barMa2 = round(float(barMa2), self.round_n)

            if len(self.lineMa2) > self.inputMa2Len*8:
                del self.lineMa2[0]
            self.lineMa2.append(barMa2)

        # 计算第三条MA均线
        if self.inputMa3Len > 0:
            if self.inputMa3Len > l:
                ma3Len = l
            else:
                ma3Len = self.inputMa3Len

            # 3、获取前InputN周期(不包含当前周期）的K线
            if self.mode == self.TICK_MODE:
                listClose = [x.close for x in self.lineBar[-ma3Len - 1:-1]]
            else:
                listClose = [x.close for x in self.lineBar[-ma3Len:]]

            barMa3 = ta.MA(np.array(listClose, dtype=float), ma3Len)[-1]
            barMa3 = round(float(barMa3), self.round_n)

            if len(self.lineMa3) > self.inputMa3Len * 8:
                del self.lineMa3[0]
            self.lineMa3.append(barMa3)

    #----------------------------------------------------------------------
    def __recountEma(self):
        """计算K线的EMA1 和EMA2"""

        if not (self.inputEma1Len > 0 or self.inputEma2Len >0 or self.inputEma3Len > 0 ):           # 不计算
            return

        l = len(self.lineBar)

        # 1、lineBar满足长度才执行计算
        if len(self.lineBar) < max(7, self.inputEma1Len, self.inputEma2Len, self.inputEma3Len)+2:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算EMA需要：{1}'.
                             format(len(self.lineBar), max(7, self.inputEma1Len, self.inputEma2Len, self.inputEma3Len)+2))
            return

        # 计算第一条EMA均线
        if self.inputEma1Len > 0:

            if self.inputEma1Len > l:
                ema1Len = l
            else:
                ema1Len = self.inputEma1Len

            # 3、获取前InputN周期(不包含当前周期）的K线
            if self.mode == self.TICK_MODE:
                listClose=[x.close for x in self.lineBar[-ema1Len - 1:-1]]
            else:
                listClose=[x.close for x in self.lineBar[-ema1Len:]]

            barEma1 = ta.EMA(np.array(listClose, dtype=float), ema1Len)[-1]

            barEma1 = round(float(barEma1), self.round_n)

            if len(self.lineEma1) > max(self.inputEma1Len,20):
                del self.lineEma1[0]
            self.lineEma1.append(barEma1)

        # 计算第二条EMA均线
        if self.inputEma2Len > 0:
            if self.inputEma2Len > l:
                ema2Len = l
            else:
                ema2Len = self.inputEma2Len

            # 3、获取前InputN周期(不包含当前周期）的自适应均线
            if self.mode == self.TICK_MODE:
                listClose=[x.close for x in self.lineBar[-ema2Len - 1:-1]]
            else:
                listClose=[x.close for x in self.lineBar[-ema2Len:]]

            barEma2 = ta.EMA(np.array(listClose, dtype=float), ema2Len)[-1]

            barEma2 = round(float(barEma2), self.round_n)

            if len(self.lineEma2) > max(self.inputEma2Len, 20):
                del self.lineEma2[0]
            self.lineEma2.append(barEma2)

        # 计算第三条EMA均线
        if self.inputEma3Len > 0:
            if self.inputEma3Len > l:
                ema3Len = l
            else:
                ema3Len = self.inputEma3Len

            # 3、获取前InputN周期(不包含当前周期）的自适应均线
            if self.mode == self.TICK_MODE:
                listClose = [x.close for x in self.lineBar[-ema3Len - 1:-1]]
            else:
                listClose = [x.close for x in self.lineBar[-ema3Len:]]

            barEma3 = ta.EMA(np.array(listClose, dtype=float), ema3Len)[-1]

            barEma3 = round(float(barEma3), self.round_n)

            if len(self.lineEma3) > max(self.inputEma3Len, 20):
                del self.lineEma3[0]
            self.lineEma3.append(barEma3)

    def __recountDmi(self):
        """计算K线的DMI数据和条件"""

        if self.inputDmiLen <= 0:           # 不计算
            return

        # 1、lineMx满足长度才执行计算
        if len(self.lineBar) < self.inputDmiLen+1:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算DMI需要：{1}'.format(len(self.lineBar), self.inputDmiLen+1))
            return

        # 2、根据当前High，Low，(不包含当前周期）重新计算TR1，PDM，MDM和ATR
        barTr1 = EMPTY_FLOAT      # 获取InputP周期内的价差最大值之和
        barPdm = EMPTY_FLOAT      # InputP周期内的做多价差之和
        barMdm = EMPTY_FLOAT      # InputP周期内的做空价差之和

        if self.mode == self.TICK_MODE:
            idx = 2
        else:
            idx = 1

        for i in range(len(self.lineBar)-idx, len(self.lineBar)-idx-self.inputDmiLen, -1):  # 周期 inputDmiLen
            # 3.1、计算TR1

            # 当前周期最高与最低的价差
            high_low_spread = self.lineBar[i].high - self.lineBar[i].low
            # 当前周期最高与昨收价的价差
            high_preclose_spread = abs(self.lineBar[i].high - self.lineBar[i - 1].close)
            # 当前周期最低与昨收价的价差
            low_preclose_spread = abs(self.lineBar[i].low - self.lineBar[i - 1].close)

            # 最大价差
            max_spread = max(high_low_spread, high_preclose_spread, low_preclose_spread)
            barTr1 = barTr1 + float(max_spread)

            # 今高与昨高的价差
            high_prehigh_spread = self.lineBar[i].high - self.lineBar[i - 1].high
            # 昨低与今低的价差
            low_prelow_spread = self.lineBar[i - 1].low - self.lineBar[i].low

            # 3.2、计算周期内的做多价差之和
            if high_prehigh_spread > 0 and high_prehigh_spread > low_prelow_spread:
                barPdm = barPdm + high_prehigh_spread

            # 3.3、计算周期内的做空价差之和
            if low_prelow_spread > 0 and low_prelow_spread > high_prehigh_spread:
                barMdm = barMdm + low_prelow_spread

        # 6、计算上升动向指标，即做多的比率
        if barTr1 == 0:
            self.barPdi = 0
        else:
            self.barPdi = barPdm * 100 / barTr1

        if len(self.linePdi) > self.inputDmiLen+1:
            del self.linePdi[0]

        self.linePdi.append(self.barPdi)

        # 7、计算下降动向指标，即做空的比率
        if barTr1 == 0:
            self.barMdi = 0
        else:
            self.barMdi = barMdm * 100 / barTr1

        # 8、计算平均趋向指标 Adx，Adxr
        if self.barMdi + self.barPdi == 0:
            dx = 0
        else:
            dx = 100 * abs(self.barMdi - self.barPdi) / (self.barMdi + self.barPdi)

        if len(self.lineMdi) > self.inputDmiLen+1:
            del self.lineMdi[0]

        self.lineMdi.append(self.barMdi)

        if len(self.lineDx) > self.inputDmiLen+1:
            del self.lineDx[0]

        self.lineDx.append(dx)

        # 平均趋向指标，MA计算
        if len(self.lineDx) < self.inputDmiLen+1:
            self.barAdx = dx
        else:
            self.barAdx = ta.EMA(np.array(self.lineDx, dtype=float), self.inputDmiLen)[-1]

        # 保存Adx值
        if len(self.lineAdx) > self.inputDmiLen+1:
            del self.lineAdx[0]

        self.lineAdx.append(self.barAdx)

        # 趋向平均值，为当日ADX值与1周期前的ADX值的均值
        if len(self.lineAdx) == 1:
            self.barAdxr = self.lineAdx[-1]
        else:
            self.barAdxr = (self.lineAdx[-1] + self.lineAdx[-2]) / 2

        # 保存Adxr值
        if len(self.lineAdxr) > self.inputDmiLen+1:
            del self.lineAdxr[0]
        self.lineAdxr.append(self.barAdxr)

        # 7、计算A，ADX值持续高于前一周期时，市场行情将维持原趋势
        if len(self.lineAdx) < 2:
            self.barAdxTrend = False
        elif self.lineAdx[-1] > self.lineAdx[-2]:
            self.barAdxTrend = True
        else:
            self.barAdxTrend = False

        # ADXR值持续高于前一周期时,波动率比上一周期高
        if len(self.lineAdxr) < 2:
            self.barAdxrTrend = False
        elif self.lineAdxr[-1] > self.lineAdxr[-2]:
            self.barAdxrTrend = True
        else:
            self.barAdxrTrend = False

        # 多过滤器条件,做多趋势，ADX高于前一天，上升动向> inputDmiMax
        if self.barPdi > self.barMdi and self.barAdxTrend and self.barAdxrTrend and self.barPdi >= self.inputDmiMax:
            self.buyFilterCond = True

            self.writeCtaLog(u'{0}[DEBUG]Buy Signal On Bar,Pdi:{1}>Mdi:{2},adx[-1]:{3}>Adx[-2]:{4}'
                                 .format(self.curTick.datetime, self.barPdi, self.barMdi, self.lineAdx[-1], self.lineAdx[-2]))
        else:
            self.buyFilterCond = False

        # 空过滤器条件 做空趋势，ADXR高于前一天，下降动向> inputMM
        if self.barPdi < self.barMdi and self.barAdxTrend and self.barAdxrTrend and self.barMdi >= self.inputDmiMax:
            self.sellFilterCond = True

            self.writeCtaLog(u'{0}[DEBUG]Short Signal On Bar,Pdi:{1}<Mdi:{2},adx[-1]:{3}>Adx[-2]:{4}'
                                 .format(self.curTick.datetime, self.barPdi, self.barMdi, self.lineAdx[-1], self.lineAdx[-2]))
        else:
            self.sellFilterCond = False

    def __recountAtr(self):
        """计算Mx K线的各类数据和条件"""

        # 1、lineMx满足长度才执行计算
        maxAtrLen = max(self.inputAtr1Len, self.inputAtr2Len, self.inputAtr3Len)

        if maxAtrLen <= 0:      # 不计算
            return

        if len(self.lineBar) < maxAtrLen+1:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算ATR需要：{1}'.
                             format(len(self.lineBar), maxAtrLen+1))
            return

        if self.mode == self.TICK_MODE:
            idx = 2
        else:
            idx = 1

        # 首次计算
        if (self.inputAtr1Len > 0 and len(self.lineAtr1) < 1) \
                or (self.inputAtr2Len > 0 and len(self.lineAtr2) < 1) \
                or (self.inputAtr3Len > 0 and len(self.lineAtr3) < 1):

            # 根据当前High，Low，(不包含当前周期）重新计算TR1和ATR
            barTr1 = EMPTY_FLOAT      # 获取inputAtr1Len周期内的价差最大值之和
            barTr2 = EMPTY_FLOAT      # 获取inputAtr2Len周期内的价差最大值之和
            barTr3 = EMPTY_FLOAT      # 获取inputAtr3Len周期内的价差最大值之和

            j = 0

            for i in range(len(self.lineBar)-idx, len(self.lineBar)-idx-maxAtrLen, -1):  # 周期 inputP
                # 3.1、计算TR

                # 当前周期最高与最低的价差
                high_low_spread = self.lineBar[i].high - self.lineBar[i].low
                # 当前周期最高与昨收价的价差
                high_preclose_spread = abs(self.lineBar[i].high - self.lineBar[i - 1].close)
                # 当前周期最低与昨收价的价差
                low_preclose_spread = abs(self.lineBar[i].low - self.lineBar[i - 1].close)

                # 最大价差
                max_spread = max(high_low_spread, high_preclose_spread, low_preclose_spread)
                if j < self.inputAtr1Len:
                    barTr1 = barTr1 + float(max_spread)
                if j < self.inputAtr2Len:
                    barTr2 = barTr2 + float(max_spread)
                if j < self.inputAtr3Len:
                    barTr3 = barTr3 + float(max_spread)

                j = j + 1

        else: # 只计算一个

            # 当前周期最高与最低的价差
            high_low_spread = self.lineBar[0-idx].high - self.lineBar[0-idx].low
            # 当前周期最高与昨收价的价差
            high_preclose_spread = abs(self.lineBar[0-idx].high - self.lineBar[-1-idx].close)
            # 当前周期最低与昨收价的价差
            low_preclose_spread = abs(self.lineBar[0-idx].low - self.lineBar[-1-idx].close)

            # 最大价差
            barTr1 = max(high_low_spread, high_preclose_spread, low_preclose_spread)
            barTr2 = barTr1
            barTr3 = barTr1

        # 计算 ATR
        if self.inputAtr1Len > 0:
            if len(self.lineAtr1) < 1:
                self.barAtr1 = round(barTr1 / self.inputAtr1Len, self.round_n)
            else:
                self.barAtr1 = round((self.lineAtr1[-1]*(self.inputAtr1Len -1) + barTr1) / self.inputAtr1Len, self.round_n)

            if len(self.lineAtr1) > self. inputAtr1Len+1 :
                del self.lineAtr1[0]
            self.lineAtr1.append(self.barAtr1)

        if self.inputAtr2Len > 0:
            if len(self.lineAtr2) < 1:
                self.barAtr2 = round(barTr2 / self.inputAtr2Len, self.round_n)
            else:
                self.barAtr2 = round((self.lineAtr2[-1]*(self.inputAtr2Len -1) + barTr2) / self.inputAtr2Len, self.round_n)

            if len(self.lineAtr2) > self. inputAtr2Len+1:
                del self.lineAtr2[0]
            self.lineAtr2.append(self.barAtr2)

        if self.inputAtr3Len > 0:
            if len(self.lineAtr3) < 1:
                self.barAtr3 = round(barTr3 / self.inputAtr3Len, self.round_n)
            else:
                self.barAtr3 = round((self.lineAtr3[-1]*(self.inputAtr3Len -1) + barTr3) / self.inputAtr3Len, self.round_n)

            if len(self.lineAtr3) > self. inputAtr3Len+1:
                del self.lineAtr3[0]

            self.lineAtr3.append(self.barAtr3)

    #----------------------------------------------------------------------
    def __recoundAvgVol(self):
        """计算平均成交量"""

        # 1、lineBar满足长度才执行计算
        if self.inputVolLen <= 0:      # 不计算
            return

        if len(self.lineBar) < self.inputVolLen+1:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算Avg Vol需要：{1}'.
                             format(len(self.lineBar), self.inputVolLen+1))
            return

        if self.mode == self.TICK_MODE:
            listVol = [x.volume for x in self.lineBar[-self.inputVolLen-1: -1]]
        else:
            listVol = [x.volume for x in self.lineBar[-self.inputVolLen:]]

        sumVol = ta.SUM(np.array(listVol, dtype=float), timeperiod=self.inputVolLen)[-1]

        avgVol = round(sumVol/self.inputVolLen, 0)

        self.lineAvgVol.append(avgVol)

    # ----------------------------------------------------------------------
    def __recountRsi(self):
        """计算K线的RSI"""

        if self.inputRsi1Len <= 0 and self.inputRsi2Len <= 0:
            return

        # 1、lineBar满足长度才执行计算
        if len(self.lineBar) < self.inputRsi1Len+2:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算RSI需要：{1}'.
                             format(len(self.lineBar), self.inputRsi1Len + 2))
            return

        # 计算第1根RSI曲线
        # 3、inputRsi1Len(包含当前周期）的相对强弱
        if self.mode == self.TICK_MODE:
            listClose=[x.close for x in self.lineBar[-self.inputRsi1Len - 2:-1]]
            idx = 2
        else:
            listClose=[x.close for x in self.lineBar[-self.inputRsi1Len-1:]]
            idx = 1

        barRsi = ta.RSI(np.array(listClose, dtype=float), self.inputRsi1Len)[-1]
        barRsi = round(float(barRsi), self.round_n)

        l = len(self.lineRsi1)
        if l > self.inputRsi1Len*8:
            del self.lineRsi1[0]

        self.lineRsi1.append(barRsi)

        if l > 3:
            # 峰
            if self.lineRsi1[-1] < self.lineRsi1[-2] and self.lineRsi1[-3] < self.lineRsi1[-2]:
                t={}
                t["Type"] = u'T'
                t["RSI"] = self.lineRsi1[-2]
                t["Close"] = self.lineBar[-1-idx].close

                if len(self.lineRsiTop) > self.inputRsi1Len:
                    del self.lineRsiTop[0]

                self.lineRsiTop.append( t )
                self.lastRsiTopButtom = self.lineRsiTop[-1]

            # 谷
            elif self.lineRsi1[-1] > self.lineRsi1[-2] and self.lineRsi1[-3] > self.lineRsi1[-2]:
                b={}
                b["Type"] = u'B'
                b["RSI"] = self.lineRsi1[-2]
                b["Close"] = self.lineBar[-1-idx].close

                if len(self.lineRsiButtom) > self.inputRsi1Len:
                    del self.lineRsiButtom[0]
                self.lineRsiButtom.append(b)
                self.lastRsiTopButtom = self.lineRsiButtom[-1]

        # 计算第二根RSI曲线
        if self.inputRsi2Len > 0:
            if len(self.lineBar) < self.inputRsi2Len+2:
                return

            if self.mode == self.TICK_MODE:
                listClose=[x.close for x in self.lineBar[-self.inputRsi2Len - 2:-1]]
            else:
                listClose=[x.close for x in self.lineBar[-self.inputRsi2Len - 1:]]

            barRsi = ta.RSI(np.array(listClose, dtype=float), self.inputRsi2Len)[-1]
            barRsi = round(float(barRsi), self.round_n)

            l = len(self.lineRsi2)
            if l > self.inputRsi2Len*8:
                del self.lineRsi2[0]

            self.lineRsi2.append(barRsi)

    def __recountCmi(self):
        """市场波动指数（Choppy Market Index，CMI）是一个用来判断市场走势类型的技术分析指标。
        它通过计算当前收盘价与一定周期前的收盘价的差值与这段时间内价格波动的范围的比值，来判断目前的股价走势是趋势还是盘整。
        市场波动指数CMI的计算公式：
        CMI=(Abs(Close-ref(close,(n-1)))*100/(HHV(high,n)-LLV(low,n))
        其中，Abs是绝对值。
        n是周期数，例如３０。
        市场波动指数CMI的使用方法：
        这个指标的重要用途是来区分目前的股价走势类型：盘整，趋势。当CMI指标小于２０时，市场走势是盘整；当CMI指标大于２０时，市场在趋势期。
        CMI指标还可以用于预测股价走势类型的转变。因为物极必反，当CMI长期处于０附近，此时，股价走势很可能从盘整转为趋势；当CMI长期处于１００附近，此时，股价趋势很可能变弱，形成盘整。
        """

        if self.inputCmiLen <= EMPTY_INT: return

         # 1、lineBar满足长度才执行计算
        if len(self.lineBar) < self.inputCmiLen:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算CMI需要：{1}'.
                             format(len(self.lineBar), self.inputCmiLen))
            return

        if self.mode == self.TICK_MODE:
            listClose =[x.close for x in self.lineBar[-self.inputCmiLen-1:-1]]
            idx = 2
        else:
            listClose =[x.close for x in self.lineBar[-self.inputCmiLen:]]
            idx = 1

        hhv = max(listClose)
        llv = min(listClose)

        if hhv==llv:
            cmi = 100
        else:
            cmi = abs(self.lineBar[0-idx].close-self.lineBar[-1-idx].close)*100/(hhv-llv)

        cmi = round(cmi, self.round_n)

        if len(self.lineCmi) > self.inputCmiLen:
            del self.lineCmi[0]

        self.lineCmi.append(cmi)

    def __recountBoll(self):
        """布林特线"""
        if self.inputBollLen <= EMPTY_INT: return

        l = len(self.lineBar)

        if l < min(14, self.inputBollLen)+1:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算Boll需要：{1}'.
                             format(len(self.lineBar), min(14, self.inputBollLen)+1))
            return

        if l < self.inputBollLen+2:
            bollLen = l-1
        else:
            bollLen = self.inputBollLen

        # 不包含当前最新的Bar
        if self.mode == self.TICK_MODE:
            listClose=[x.close for x in self.lineBar[-bollLen - 1:-1]]
        else:
            listClose=[x.close for x in self.lineBar[-bollLen :]]
        #
        upper, middle, lower = ta.BBANDS(np.array(listClose, dtype=float),
                                         timeperiod=bollLen, nbdevup=self.inputBollStdRate,
                                         nbdevdn=self.inputBollStdRate, matype=0)
        if len(self.lineUpperBand) > self.inputBollLen*8:
            del self.lineUpperBand[0]
        if len(self.lineMiddleBand) > self.inputBollLen*8:
            del self.lineMiddleBand[0]
        if len(self.lineLowerBand) > self.inputBollLen*8:
            del self.lineLowerBand[0]
        if len(self.lineBollStd) > self.inputBollLen * 8:
            del self.lineBollStd[0]

        # 1标准差
        std = (upper[-1] - lower[-1]) / (self.inputBollStdRate*2)
        self.lineBollStd.append(std)

        u = round(upper[-1], self.round_n)
        self.lineUpperBand.append(u)                                # 上轨
        self.lastBollUpper = u - u % self.minDiff                   # 上轨取整

        m = round(middle[-1], self.round_n)
        self.lineMiddleBand.append(m)                               # 中轨
        self.lastBollMiddle = m - m % self.minDiff                  # 中轨取整

        l = round(lower[-1], self.round_n)
        self.lineLowerBand.append(l)                                # 下轨
        self.lastBollLower = l - l % self.minDiff     # 下轨取整


    def __recountKdj(self, countInBar = False):
        """KDJ指标"""
        """
        KDJ指标的中文名称又叫随机指标，是一个超买超卖指标,最早起源于期货市场，由乔治·莱恩（George Lane）首创。
        随机指标KDJ最早是以KD指标的形式出现，而KD指标是在威廉指标的基础上发展起来的。
        不过KD指标只判断股票的超买超卖的现象，在KDJ指标中则融合了移动平均线速度上的观念，形成比较准确的买卖信号依据。在实践中，K线与D线配合J线组成KDJ指标来使用。
        KDJ指标在设计过程中主要是研究最高价、最低价和收盘价之间的关系，同时也融合了动量观念、强弱指标和移动平均线的一些优点。
        因此，能够比较迅速、快捷、直观地研判行情，被广泛用于股市的中短期趋势分析，是期货和股票市场上最常用的技术分析工具。
 
        第一步 计算RSV：即未成熟随机值（Raw Stochastic Value）。
        RSV 指标主要用来分析市场是处于“超买”还是“超卖”状态：
            - RSV高于80%时候市场即为超买状况，行情即将见顶，应当考虑出仓；
            - RSV低于20%时候，市场为超卖状况，行情即将见底，此时可以考虑加仓。
        N日RSV=(N日收盘价-N日内最低价）÷(N日内最高价-N日内最低价）×100%
        第二步 计算K值：当日K值 = 2/3前1日K值 + 1/3当日RSV ; 
        第三步 计算D值：当日D值 = 2/3前1日D值 + 1/3当日K值； 
        第四步 计算J值：当日J值 = 3当日K值 - 2当日D值. 

        """
        if self.inputKdjLen <= EMPTY_INT: return

        if len(self.lineBar) < self.inputKdjLen+1:
            if not countInBar:
                self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算KDJ需要：{1}'.format(len(self.lineBar), self.inputKdjLen+1))
            return

        # 数据是Tick模式，非bar内计算
        if self.mode == self.TICK_MODE and not countInBar:
            listClose =[x.close for x in self.lineBar[-self.inputKdjLen-1:-1]]
            listHigh = [x.high for x in self.lineBar[-self.inputKdjLen - 1:-1]]
            listLow = [x.low for x in self.lineBar[-self.inputKdjLen - 1:-1]]
            idx = 2
        else:
            listClose =[x.close for x in self.lineBar[-self.inputKdjLen:]]
            listHigh = [x.high for x in self.lineBar[-self.inputKdjLen :]]
            listLow = [x.low for x in self.lineBar[-self.inputKdjLen :]]
            idx = 1

        hhv = max(listHigh)
        llv = min(listLow)

        if len(self.lineK) > 0:
            lastK =  self.lineK[-1]
        else:
            lastK = 0

        if len(self.lineD) > 0:
            lastD = self.lineD[-1]
        else:
            lastD = 0

        if hhv == llv:
            rsv = 50
        else:
            rsv = (self.lineBar[-1].close - llv)/(hhv - llv) * 100

        k = 2*lastK/3 + rsv/3
        if k < 0: k = 0
        if k > 100: k = 100

        d = 2*lastD/3 + k/3
        if d < 0: d = 0
        if d > 100: d = 100

        j = 3*k - 2*d

        if countInBar:
            self.lastD = d
            self.lastK = k
            self.lastJ = j
            return

        if len(self.lineK) > self.inputKdjLen * 8:
            del self.lineK[0]
        self.lineK.append(k)

        if len(self.lineD) > self.inputKdjLen * 8:
            del self.lineD[0]
        self.lineD.append(d)

        l = len(self.lineJ)
        if l > self.inputKdjLen * 8:
            del self.lineJ[0]
        self.lineJ.append(j)

        #增加KDJ的J谷顶和波底
        if l > 3:
            # 峰
            if self.lineJ[-1] < self.lineJ[-2] and self.lineJ[-3] <= self.lineJ[-2]:

                t={}
                t["Type"] = u'T'
                t["J"] = self.lineJ[-2]
                t["Close"] = self.lineBar[-1-idx].close

                if len(self.lineKdjTop) > self.inputKdjLen:
                    del self.lineKdjTop[0]

                self.lineKdjTop.append( t )
                self.lastKdjTopButtom = self.lineKdjTop[-1]

            # 谷
            elif self.lineJ[-1] > self.lineJ[-2] and self.lineJ[-3] >= self.lineJ[-2]:

                b={}
                b["Type"] = u'B'
                b["J"] = self.lineJ[-2]
                b["Close"] = self.lineBar[-1-idx].close

                if len(self.lineKdjButtom) > self.inputKdjLen:
                    del self.lineKdjButtom[0]
                self.lineKdjButtom.append(b)
                self.lastKdjTopButtom = self.lineKdjButtom[-1]

    def __recountMacd(self):
        """
        Macd计算方法：
        12日EMA的计算：EMA12 = 前一日EMA12 X 11/13 + 今日收盘 X 2/13
        26日EMA的计算：EMA26 = 前一日EMA26 X 25/27 + 今日收盘 X 2/27
        差离值（DIF）的计算： DIF = EMA12 - EMA26，即为talib-MACD返回值macd
        根据差离值计算其9日的EMA，即离差平均值，是所求的DEA值。
        今日DEA = （前一日DEA X 8/10 + 今日DIF X 2/10），即为talib-MACD返回值signal
        DIF与它自己的移动平均之间差距的大小一般BAR=（DIF-DEA)*2，即为MACD柱状图。
        但是talib中MACD的计算是bar = (dif-dea)*1
        """

        if self.inputMacdFastPeriodLen <= EMPTY_INT: return
        if self.inputMacdSlowPeriodLen <= EMPTY_INT: return
        if self.inputMacdSignalPeriodLen <= EMPTY_INT: return

        maxLen = max(self.inputMacdFastPeriodLen,self.inputMacdSlowPeriodLen)+self.inputMacdSignalPeriodLen+1

        #maxLen = maxLen * 3             # 注：数据长度需要足够，才能准确。测试过，3倍长度才可以与国内的文华等软件一致

        if len(self.lineBar) < maxLen:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算MACD需要：{1}'.format(len(self.lineBar), maxLen))
            return

        if self.mode == self.TICK_MODE:
            listClose =[x.close for x in self.lineBar[-maxLen:-1]]
        else:
            listClose =[x.close for x in self.lineBar[-maxLen-1:]]

        dif, dea, macd = ta.MACD(np.array(listClose, dtype=float), fastperiod=self.inputMacdFastPeriodLen,
                       slowperiod=self.inputMacdSlowPeriodLen, signalperiod=self.inputMacdSignalPeriodLen)

        #dif, dea, macd = ta.MACDEXT(np.array(listClose, dtype=float),
        #                            fastperiod=self.inputMacdFastPeriodLen, fastmatype=1,
        #                            slowperiod=self.inputMacdSlowPeriodLen, slowmatype=1,
        #                            signalperiod=self.inputMacdSignalPeriodLen, signalmatype=1)

        if len(self.lineDif) > maxLen:
            del self.lineDif[0]
        self.lineDif.append(dif[-1])

        if len(self.lineDea) > maxLen:
            del self.lineDea[0]
        self.lineDea.append(dea[-1])

        if len(self.lineMacd) > maxLen:
            del self.lineMacd[0]
        self.lineMacd.append(macd[-1]*2)            # 国内一般是2倍

    def __recountCci(self):
        """CCI计算
        顺势指标又叫CCI指标，CCI指标是美国股市技术分析 家唐纳德·蓝伯特(Donald Lambert)于20世纪80年代提出的，专门测量股价、外汇或者贵金属交易
        是否已超出常态分布范围。属于超买超卖类指标中较特殊的一种。波动于正无穷大和负无穷大之间。但是，又不需要以0为中轴线，这一点也和波动于正无穷大
        和负无穷大的指标不同。
        它最早是用于期货市场的判断，后运用于股票市场的研判，并被广泛使用。与大多数单一利用股票的收盘价、开盘价、最高价或最低价而发明出的各种技术分析
        指标不同，CCI指标是根据统计学原理，引进价格与固定期间的股价平均区间的偏离程度的概念，强调股价平均绝对偏差在股市技术分析中的重要性，是一种比
        较独特的技术指标。
        它与其他超买超卖型指标又有自己比较独特之处。象KDJ、W%R等大多数超买超卖型指标都有“0-100”上下界限，因此，它们对待一般常态行情的研判比较适用
        ，而对于那些短期内暴涨暴跌的股票的价格走势时，就可能会发生指标钝化的现象。而CCI指标却是波动于正无穷大到负无穷大之间，因此不会出现指标钝化现
        象，这样就有利于投资者更好地研判行情，特别是那些短期内暴涨暴跌的非常态行情。
        http://baike.baidu.com/view/53690.htm?fromtitle=CCI%E6%8C%87%E6%A0%87&fromid=4316895&type=syn


        """
        if self.inputCciLen <= 0:
            return

        # 1、lineBar满足长度才执行计算
        if len(self.lineBar) < self.inputCciLen+2:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算CCI需要：{1}'.
                             format(len(self.lineBar), self.inputCciLen + 2))
            return

        # 计算第1根RSI曲线

        # 3、inputCc1Len(包含当前周期）
        if self.mode == self.TICK_MODE:
            listClose = [x.close for x in self.lineBar[-self.inputCciLen - 2:-1]]
            listHigh = [x.high for x in self.lineBar[-self.inputCciLen - 2:-1]]
            listLow  = [x.low for x in self.lineBar[-self.inputCciLen - 2:-1]]
            idx = 2
        else:
            listClose = [x.close for x in self.lineBar[-self.inputCciLen-1:]]
            listHigh = [x.high for x in self.lineBar[-self.inputCciLen - 1:]]
            listLow = [x.low for x in self.lineBar[-self.inputCciLen - 1:]]
            idx = 1

        barCci = ta.CCI(high=np.array(listHigh, dtype=float), low=np.array(listLow, dtype=float),
                        close=np.array(listClose, dtype=float), timeperiod=self.inputCciLen)[-1]

        barCci = round(float(barCci), 3)

        l = len(self.lineCci)
        if l > self.inputCciLen*8:
            del self.lineCci[0]
        self.lineCci.append(barCci)

    def __recountKF(self):
        """计算卡尔曼过滤器均线"""
        min_len = 20
        if not self.inputKF or self.kf is None:
            return

        if len(self.lineStateMean) == 0 or len(self.lineStateCovar) == 0:
            listClose = []
            # 3、获取前InputN周期(不包含当前周期）的K线
            if self.mode == self.TICK_MODE:
                if len(self.lineBar)<2:
                    return
                listClose.append(self.lineBar[-2].close)
            else:
                listClose.append(self.lineBar[-1].close)

            try:
                self.kf = KalmanFilter(transition_matrices=[1],
                                       observation_matrices=[1],
                                       initial_state_mean=listClose[-1],
                                       initial_state_covariance=1,

                                       transition_covariance=0.01)
            except:
                self.writeCtaLog(u'导入卡尔曼过滤器失败,需先安装 pip install pykalman')
                self.inputKF = False

            state_means, state_covariances = self.kf.filter(np.array(listClose, dtype=float))
            m = state_means[-1].item()
            c = state_covariances[-1].item()
        else:
            m = self.lineStateMean[-1]
            c = self.lineStateCovar[-1]
            if self.mode == self.TICK_MODE:
                o = self.lineBar[-2].close
            else:
                o = self.lineBar[-1].close

            state_means, state_covariances = self.kf.filter_update(filtered_state_mean=m,
                                                                   filtered_state_covariance=c,
                                                                   observation=np.array(o, dtype=float))
            m = state_means[-1].item()
            c = state_covariances[-1].item()

        if len(self.lineStateMean) > min_len:
            del self.lineStateMean[0]
        if len(self.lineStateCovar) > min_len:
            del self.lineStateCovar[0]

        self.lineStateMean.append(m)
        self.lineStateCovar.append(c)

    def __recountPeriod(self, bar):
        """重新计算周期"""

        len_rsi = len(self.lineRsi1)

        if self.inputKF:
            if len(self.lineStateMean) < 7 or len_rsi <=0:
                return
            listMid = self.lineStateMean[-7:-1]
            malist = ta.MA(np.array(listMid, dtype=float), 5)
            lastMid = self.lineStateMean[-1]

        else:
            len_boll = len(self.lineMiddleBand)
            if len_boll <= 6 or len_rsi <= 0:
                return
            listMid = self.lineMiddleBand[-7:-1]
            lastMid = self.lineMiddleBand[-1]
            malist = ta.MA(np.array(listMid, dtype=float), 5)

        ma5 = malist[-1]
        ma5_ref1 = malist[-2]
        if ma5 <= 0 or ma5_ref1 <= 0:
            self.writeCtaLog(u'boll中轨计算均线异常')
            return
        self.atan = math.atan((ma5 / ma5_ref1 - 1) * 100 * 180 / math.pi)
        #atan2 = math.atan((ma5 / ma5_ref1 - 1) * 100) * 180 / math.pi
        #atan3 = math.atan(ma5 / ma5_ref1 - 1)* 100
        self.atan = round(self.atan,3)
        #self.writeCtaLog(u'{}/{}/{}'.format(self.atan, atan2, atan3))

        if self.curPeriod is None:
            self.writeCtaLog(u'初始化周期为震荡')
            self.curPeriod = CtaPeriod(mode=PERIOD_SHOCK, price=bar.close, pre_mode=PERIOD_INIT, dt=bar.datetime)
            self.periods.append(self.curPeriod)

        if len(self.atan_list) > 10:
            del self.atan_list[0]
        self.atan_list.append(self.atan)

        if len_rsi < 3:
            return

        # 当前期趋势是震荡
        if self.curPeriod.mode == PERIOD_SHOCK:
            # 初始化模式
            if self.curPeriod.pre_mode == PERIOD_INIT:
                if self.atan < -0.8:
                    self.curPeriod = CtaPeriod(mode=PERIOD_SHORT_EXTREME, price=bar.close, pre_mode=PERIOD_SHORT,
                                              dt=bar.datetime)
                    self.periods.append(self.curPeriod)
                    self.writeCtaLog(u'{} 角度向下,Atan:{},周期{}=》{}'.
                                     format(bar.datetime, self.atan, self.curPeriod.pre_mode, self.curPeriod.mode))
                    if self.onPeriodChgFunc is not None:
                        self.onPeriodChgFunc(self.curPeriod)

                    return
                elif self.atan > 0.8:
                    self.curPeriod = CtaPeriod(mode=PERIOD_LONG_EXTREME, price=bar.close, pre_mode=PERIOD_LONG,
                                              dt=bar.datetime)
                    self.periods.append(self.curPeriod)
                    self.writeCtaLog(u'{} 角度加速向上,Atan:{}，周期:{}=>{}'.
                                     format(bar.datetime, self.atan, self.curPeriod.pre_mode,
                                            self.curPeriod.mode))
                    if self.onPeriodChgFunc is not None:
                        self.onPeriodChgFunc(self.curPeriod)

                    return

            # 震荡 -》 空
            if self.atan <= -0.2:
                self.curPeriod = CtaPeriod(mode=PERIOD_SHORT, price=bar.close, pre_mode=PERIOD_SHOCK, dt=bar.datetime)
                self.periods.append(self.curPeriod)
                self.writeCtaLog(u'{} 角度向下,Atan:{},周期{}=》{}'.
                                 format(bar.datetime,self.atan, self.curPeriod.pre_mode, self.curPeriod.mode))
                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)
            # 震荡 =》 多
            elif self.atan >= 0.2:
                self.curPeriod = CtaPeriod(mode=PERIOD_LONG, price=bar.close, pre_mode=PERIOD_SHOCK,dt=bar.datetime)
                self.periods.append(self.curPeriod)
                self.writeCtaLog(u'{} 角度向上,Atan:{}，周期:{}=>{}'.
                                 format(bar.datetime,self.atan, self.curPeriod.pre_mode,
                                        self.curPeriod.mode))
                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)

            # 周期维持不变
            else:
                self.writeCtaLog(u'{} 角度维持，Atan:{},周期维持:{}'.
                                 format(bar.datetime, self.atan, self.curPeriod.mode))

            return

        # 当前期趋势是空
        if self.curPeriod.mode == PERIOD_SHORT:
            # 空=》空极端
            if self.atan <= -0.8 and self.atan_list[-1] < self.atan_list[-2]:
                self.curPeriod = CtaPeriod(mode=PERIOD_SHORT_EXTREME, price=bar.close, pre_mode=PERIOD_SHORT, dt=bar.datetime)
                self.periods.append(self.curPeriod)
                self.writeCtaLog(u'{} 角度极端向下,Atan:{}，注意反弹。周期:{}=>{}'.
                                 format(bar.datetime,self.atan, self.curPeriod.pre_mode, self.curPeriod.mode))
                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)

            # 空=》震荡
            elif -0.2 < self.atan < 0.2 or (self.atan >= 0.2 and self.atan_list[-2] <= -0.2):
                self.curPeriod = CtaPeriod(mode=PERIOD_SHOCK, price=bar.close, pre_mode=PERIOD_SHORT, dt=bar.datetime)
                self.periods.append(self.curPeriod)
                self.writeCtaLog(u'{} 角度平缓，Atan:{},结束下降趋势。周期:{}=>{}'.
                                 format(bar.datetime, self.atan, self.curPeriod.pre_mode,self.curPeriod.mode))
                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)

            elif self.atan > 0.2 and self.curPeriod.pre_mode == PERIOD_LONG_EXTREME and self.atan_list[-1] > self.atan_list[-2] and bar.close > lastMid:
                self.curPeriod = CtaPeriod(mode=PERIOD_SHOCK, price=bar.close, pre_mode=PERIOD_SHORT, dt=bar.datetime)
                self.periods.append(self.curPeriod)
                self.writeCtaLog(u'{} 角度平缓，Atan:{},结束下降趋势。周期:{}=>{}'.
                                 format(bar.datetime, self.atan, self.curPeriod.pre_mode, self.curPeriod.mode))
                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)

            # 周期维持空
            else:
                self.writeCtaLog(u'{} 角度向下{},周期维持:{}'.
                                 format(bar.datetime, self.atan, self.curPeriod.mode))

            return

        # 当前期趋势是多
        if self.curPeriod.mode == PERIOD_LONG:
            # 多=》多极端
            if self.atan >= 0.8 and self.atan_list[-1] > self.atan_list[-2]:
                self.curPeriod = CtaPeriod(mode=PERIOD_LONG_EXTREME, price=bar.close, pre_mode=PERIOD_LONG, dt=bar.datetime)
                self.periods.append(self.curPeriod)

                self.writeCtaLog(u'{} 角度加速向上,Atan:{}，周期:{}=>{}'.
                                 format(bar.datetime, self.atan, self.curPeriod.pre_mode,
                                        self.curPeriod.mode))
                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)

            # 多=》震荡
            elif -0.2 < self.atan < 0.2 or (self.atan <= -0.2 and self.atan_list[-2] >= 0.2):
                self.curPeriod = CtaPeriod(mode=PERIOD_SHOCK, price=bar.close, pre_mode=PERIOD_LONG, dt=bar.datetime)
                self.periods.append(self.curPeriod)
                self.writeCtaLog(u'{} 角度平缓,Atan:{},结束上升趋势。周期:{}=>{}'.
                                 format(bar.datetime, self.atan, self.curPeriod.pre_mode, self.curPeriod.mode))
                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)

            # 多=》震荡
            elif self.atan < -0.2 and self.curPeriod.pre_mode == PERIOD_SHORT_EXTREME and self.atan_list[-1] < self.atan_list[-2] and bar.close < lastMid:
                self.curPeriod = CtaPeriod(mode=PERIOD_SHOCK, price=bar.close, pre_mode=PERIOD_LONG, dt=bar.datetime)
                self.periods.append(self.curPeriod)
                self.writeCtaLog(u'{} 角度平缓,Atan:{},结束上升趋势。周期:{}=>{}'.
                                 format(bar.datetime, self.atan, self.curPeriod.pre_mode, self.curPeriod.mode))

                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)
            # 周期保持多
            else:
                self.writeCtaLog(u'{} 角度向上,Atan:{},周期维持:{}'.
                                 format(bar.datetime, self.atan, self.curPeriod.mode))
            return

        # 当前周期为多极端
        if self.curPeriod.mode == PERIOD_LONG_EXTREME:
            # 多极端 =》 空
            if self.lineRsi1[-1] < self.lineRsi1[-2] \
                    and max(self.lineRsi1[-5:-2]) >= 50 \
                    and bar.close < lastMid:

                self.curPeriod = CtaPeriod(mode=PERIOD_SHORT, price=bar.close, pre_mode=PERIOD_LONG_EXTREME,
                                               dt=bar.datetime)
                self.periods.append(self.curPeriod)

                self.writeCtaLog(u'{} 角度高位反弹向下，Atan:{} , RSI {}=》{},{}下穿中轨{},周期：{}=》{}'.
                                 format(bar.datetime, self.atan, self.lineRsi1[-2], self.lineRsi1[-1],
                                        bar.close,lastMid,
                                        self.curPeriod.pre_mode, self.curPeriod.mode))
                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)

            # 多极端 =》多
            elif self.lineRsi1[-1] < self.lineRsi1[-2] \
                    and bar.close > lastMid:
                self.curPeriod = CtaPeriod(mode=PERIOD_LONG, price=bar.close, pre_mode=PERIOD_LONG_EXTREME, dt=bar.datetime)
                self.periods.append(self.curPeriod)
                self.writeCtaLog(u'{} 角度上加速放缓，Atan:{}, & RSI{}=>{}，周期：{}=》{}'.
                                 format(bar.datetime, self.atan, self.lineRsi1[-2], self.lineRsi1[-1],
                                        self.curPeriod.pre_mode, self.curPeriod.mode))
                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)

            # 当前趋势保持多极端
            else:
                self.writeCtaLog(u'{} 角度向上加速{},周期维持:{}'.
                                 format(bar.datetime, self.atan, self.curPeriod.mode))

            return

        # 当前周期为空极端
        if self.curPeriod.mode == PERIOD_SHORT_EXTREME:
            # 空极端 =》多
            if self.lineRsi1[-1] > self.lineRsi1[-2] and min(self.lineRsi1[-5:-2]) <= 50 \
                    and bar.close > lastMid:

                self.curPeriod = CtaPeriod(mode=PERIOD_LONG, price=bar.close, pre_mode=PERIOD_SHORT_EXTREME, dt=bar.datetime)
                self.periods.append(self.curPeriod)

                self.writeCtaLog(u'{} 角度下极限低位反弹转折,Atan:{}, RSI:{}=>{},周期:{}=>{}'.
                                 format(bar.datetime, self.atan, self.lineRsi1[-2], self.lineRsi1[-1],
                                        self.curPeriod.pre_mode, self.curPeriod.mode))
                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)

            # 空极端=》空
            elif self.lineRsi1[-1] > self.lineRsi1[-2] and bar.close < lastMid:
                self.curPeriod = CtaPeriod(mode=PERIOD_SHORT, price=bar.close, pre_mode=PERIOD_SHORT_EXTREME,
                                               dt=bar.datetime)
                self.periods.append(self.curPeriod)
                self.writeCtaLog(u'{} 角度下加速放缓，Atan:{},RSI:{}=>{}, ,周期：{}=>{}'.
                                 format(bar.datetime, self.atan, self.lineRsi1[-2],self.lineRsi1[-1],
                                        self.curPeriod.pre_mode, self.curPeriod.mode))
                if self.onPeriodChgFunc is not None:
                    self.onPeriodChgFunc(self.curPeriod)

            # 保持空极端趋势
            else:
                self.writeCtaLog(u'{} 角度向下加速,Atan:{},周期维持:{}'.
                                 format(bar.datetime, self.atan, self.curPeriod.mode))

            return

    def __recountSKD(self):
        """
        改良得多空线(类似KDJ，RSI）
        :param bar: 
        :return: 
        """
        if not self.inputSkd:
            return

        if len(self.lineBar) < max(self.inputSkdLen1, self.inputSkdLen2) * 4:
            return

        # 取得Len1*2 长度的Close
        if self.mode == self.TICK_MODE:
            close_list = [x.close for x in self.lineBar[-max(self.inputSkdLen1, self.inputSkdLen2)*4:-1]]
            idx = 2
        else:
            close_list = [x.close for x in self.lineBar[-max(self.inputSkdLen1, self.inputSkdLen2)*4:]]
            idx = 1

        np_close = np.array(close_list[1:])
        np_pre_close = np.array(close_list[:-1])

        # 计算优化后的RSI指标
        #rsi1 = 100 * ta.SMA(np.maximum(np_close - np_pre_close,0),self.inputSkdLen1) / ta.SMA(np.abs(np_close - np_pre_close),self.inputSkdLen1)
        rsi1 = ta.RSI(np_close, self.inputSkdLen1)

        rsi1 = np.where(np.isnan(rsi1), 0, rsi1)

        rsi1_HHV = ta.MAX(rsi1, self.inputSkdLen2)
        rsi1_LLV = ta.MIN(rsi1, self.inputSkdLen2)

        sto = (np.abs(rsi1_HHV - rsi1_LLV) > 1e-5).astype(int) * ( 100 * (rsi1 - rsi1_LLV)/(rsi1_HHV - rsi1_LLV + 1e-5))
        sto = np.where(np.isnan(sto), 0, sto)
        sk = ta.EMA(sto, 5)
        sk = np.where(np.isnan(sk), 0, sk)
        sd = ta.EMA(sk, 3)

        if len(self.lineSK) > 60*8:
            del self.lineSK[0]

        self.lineSK.append(sk[-1])

        if len(self.lineSD) > 60 * 8:
            del self.lineSD[0]

        self.lineSD.append(sd[-1])

    def __recountYB(self):
        """某种趋势线"""

        if not self.inputYb:
            return

        # 1、lineBar满足长度才执行计算
        if len(self.lineBar) < 20:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算YB 需要：{1}'.
                             format(len(self.lineBar), 20))
            return

        emaLen = 10

        # 3、获取前InputN周期(不包含当前周期）的K线
        if self.mode == self.TICK_MODE:
            list_mid3 = [x.mid3 for x in self.lineBar[-emaLen - 1:-1]]
        else:
            list_mid3 = [x.mid3 for x in self.lineBar[-emaLen:]]

        bar_mid3_ema10 = ta.EMA(np.array(list_mid3, dtype=float), emaLen)[-1]

        bar_mid3_ema10 = round(float(bar_mid3_ema10), self.round_n)

        if len(self.lineYb) > emaLen*4:
            del self.lineYb[0]

        self.lineYb.append(bar_mid3_ema10)

    # ----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """记录CTA日志"""
        self.strategy.writeCtaLog(u'['+self.name+u']'+content)

    def debugCtaLog(self, content):
        """记录CTA日志"""
        if DEBUGCTALOG:
            self.strategy.writeCtaLog(u'['+self.name+u'-DEBUG]'+content)

class CtaHourBar(CtaLineBar):
    """
    小时级别K线
    """
    def __init__(self, strategy, onBarFunc, setting=None ):

        if 'period' in setting:
            del setting['period']

        super(CtaHourBar, self).__init__(strategy, onBarFunc, setting)

    def init_properties(self):
        """
        初始化内部变量
        :return:
        """
        self.paramList.append('barTimeInterval')
        self.paramList.append('period')
        self.paramList.append('inputPreLen')
        self.paramList.append('inputEma1Len')
        self.paramList.append('inputEma2Len')
        self.paramList.append('inputEma3Len')
        self.paramList.append('inputMa1Len')
        self.paramList.append('inputMa2Len')
        self.paramList.append('inputMa3Len')
        self.paramList.append('inputDmiLen')
        self.paramList.append('inputDmiMax')
        self.paramList.append('inputAtr1Len')
        self.paramList.append('inputAtr2Len')
        self.paramList.append('inputAtr3Len')
        self.paramList.append('inputVolLen')
        self.paramList.append('inputRsi1Len')
        self.paramList.append('inputRsi2Len')
        self.paramList.append('inputCmiLen')
        self.paramList.append('inputBollLen')
        self.paramList.append('inputBollStdRate')
        self.paramList.append('inputKdjLen')
        self.paramList.append('inputCciLen')
        self.paramList.append('inputMacdFastPeriodLen')
        self.paramList.append('inputMacdSlowPeriodLen')
        self.paramList.append('inputMacdSignalPeriodLen')
        self.paramList.append('inputKF')
        self.paramList.append('inputSkd')
        self.paramList.append('inputYb')

        self.paramList.append('minDiff')
        self.paramList.append('shortSymbol')
        self.paramList.append('activeDayJump')
        self.paramList.append('name')

        # 输入参数
        self.name = u'HourBar'
        self.mode = self.TICK_MODE  # 缺省为tick模式
        self.period = PERIOD_HOUR  # 小时级别周期
        self.barTimeInterval = 1  # 缺省为小时周期

        self.barMinuteInterval = 60

        self.inputPreLen = EMPTY_INT  # 1

        self.inputMa1Len = EMPTY_INT  # 10
        self.inputMa2Len = EMPTY_INT  # 20
        self.inputMa3Len = EMPTY_INT  # 120

        self.inputEma1Len = EMPTY_INT  # 13
        self.inputEma2Len = EMPTY_INT  # 21
        self.inputEma3Len = EMPTY_INT  # 120

        self.inputDmiLen = EMPTY_INT  # 14           # DMI的计算周期
        self.inputDmiMax = EMPTY_FLOAT  # 30           # Dpi和Mdi的突破阈值

        self.inputAtr1Len = EMPTY_INT  # 10           # ATR波动率的计算周期(近端）
        self.inputAtr2Len = EMPTY_INT  # 26           # ATR波动率的计算周期（常用）
        self.inputAtr3Len = EMPTY_INT  # 50           # ATR波动率的计算周期（远端）

        self.inputVolLen = EMPTY_INT  # 14           # 平均交易量的计算周期

        self.inputRsi1Len = EMPTY_INT  # 7     # RSI 相对强弱指数（快曲线）
        self.inputRsi2Len = EMPTY_INT  # 14    # RSI 相对强弱指数（慢曲线）

        self.shortSymbol = EMPTY_STRING  # 商品的短代码
        self.minDiff = 1  # 商品的最小价格单位
        self.round_n = 4  # round() 小数点的截断数量
        self.activeDayJump = False  # 隔夜跳空

        # 当前的Tick
        self.curTick = None
        self.lastTick = None
        self.curTradingDay = EMPTY_STRING

        # K线保存数据
        self.bar = None  # K线数据对象
        self.lineBar = []  # K线缓存数据队列
        self.barFirstTick = False  # K线的第一条Tick数据

        # K 线的相关计算结果数据

        self.preHigh = []  # K线的前inputPreLen的的最高
        self.preLow = []  # K线的前inputPreLen的的最低

        self.lineMa1 = []  # K线的MA1均线，周期是InputMaLen1，不包含当前bar
        self.lineMa2 = []  # K线的MA2均线，周期是InputMaLen2，不包含当前bar
        self.lineMa3 = []  # K线的MA2均线，周期是InputMaLen2，不包含当前bar

        self.lineEma1 = []  # K线的EMA1均线，周期是InputEmaLen1，不包含当前bar
        self.lineEma2 = []  # K线的EMA2均线，周期是InputEmaLen2，不包含当前bar
        self.lineEma3 = []  # K线的EMA3均线，周期是InputEmaLen3，不包含当前bar

        # K线的DMI( Pdi，Mdi，ADX，Adxr) 计算数据
        self.barPdi = EMPTY_FLOAT  # bar内的升动向指标，即做多的比率
        self.barMdi = EMPTY_FLOAT  # bar内的下降动向指标，即做空的比率

        self.linePdi = []  # 升动向指标，即做多的比率
        self.lineMdi = []  # 下降动向指标，即做空的比率

        self.lineDx = []  # 趋向指标列表，最大长度为inputM*2
        self.barAdx = EMPTY_FLOAT  # Bar内计算的平均趋向指标
        self.lineAdx = []  # 平均趋向指标
        self.barAdxr = EMPTY_FLOAT  # 趋向平均值，为当日ADX值与M日前的ADX值的均值
        self.lineAdxr = []  # 平均趋向变化指标

        # K线的基于DMI、ADX计算的结果
        self.barAdxTrend = EMPTY_FLOAT  # ADX值持续高于前一周期时，市场行情将维持原趋势
        self.barAdxrTrend = EMPTY_FLOAT  # ADXR值持续高于前一周期时,波动率比上一周期高

        self.buyFilterCond = False  # 多过滤器条件,做多趋势的判断，ADX高于前一天，上升动向> inputMM
        self.sellFilterCond = False  # 空过滤器条件,做空趋势的判断，ADXR高于前一天，下降动向> inputMM

        # K线的ATR技术数据
        self.lineAtr1 = []  # K线的ATR1,周期为inputAtr1Len
        self.lineAtr2 = []  # K线的ATR2,周期为inputAtr2Len
        self.lineAtr3 = []  # K线的ATR3,周期为inputAtr3Len

        self.barAtr1 = EMPTY_FLOAT
        self.barAtr2 = EMPTY_FLOAT
        self.barAtr3 = EMPTY_FLOAT

        # K线的交易量平均
        self.lineAvgVol = []  # K 线的交易量平均

        # K线的RSI计算数据
        self.lineRsi1 = []  # 记录K线对应的RSI数值，只保留inputRsi1Len*8
        self.lineRsi2 = []  # 记录K线对应的RSI数值，只保留inputRsi2Len*8

        self.lowRsi = 30  # RSI的最低线
        self.highRsi = 70  # RSI的最高线

        self.lineRsiTop = []  # 记录RSI的最高峰，只保留 inputRsiLen个
        self.lineRsiButtom = []  # 记录RSI的最低谷，只保留 inputRsiLen个
        self.lastRsiTopButtom = {}  # 最近的一个波峰/波谷

        # K线的CMI计算数据
        self.inputCmiLen = EMPTY_INT
        self.lineCmi = []  # 记录K线对应的Cmi数值，只保留inputCmiLen*8

        # K线的布林特计算数据
        self.inputBollLen = EMPTY_INT  # K线周期
        self.inputBollStdRate = 1.5  # 两倍标准差
        self.lineBollClose = []  # 用于运算的close价格列表
        self.lineUpperBand = []  # 上轨
        self.lineMiddleBand = []  # 中线
        self.lineLowerBand = []  # 下轨
        self.lineBollStd = []  # 标准差

        self.lastBollUpper = EMPTY_FLOAT  # 最后一根K的Boll上轨数值（与MinDiff取整）
        self.lastBollMiddle = EMPTY_FLOAT  # 最后一根K的Boll中轨数值（与MinDiff取整）
        self.lastBollLower = EMPTY_FLOAT  # 最后一根K的Boll下轨数值（与MinDiff取整+1）

        # K线的KDJ指标计算数据
        self.inputKdjLen = EMPTY_INT  # KDJ指标的长度,缺省是9
        self.lineK = []  # K为快速指标
        self.lineD = []  # D为慢速指标
        self.lineJ = []  #
        self.lineKdjTop = []  # 记录KDJ最高峰，只保留 inputKdjLen个
        self.lineKdjButtom = []  # 记录KDJ的最低谷，只保留 inputKdjLen个
        self.lastKdjTopButtom = {}  # 最近的一个波峰/波谷
        self.lastK = EMPTY_FLOAT  # bar内计算时，最后一个未关闭的bar的实时K值
        self.lastD = EMPTY_FLOAT  # bar内计算时，最后一个未关闭的bar的实时值
        self.lastJ = EMPTY_FLOAT  # bar内计算时，最后一个未关闭的bar的实时J值

        # K线的MACD计算数据
        self.inputMacdFastPeriodLen = EMPTY_INT
        self.inputMacdSlowPeriodLen = EMPTY_INT
        self.inputMacdSignalPeriodLen = EMPTY_INT

        self.lineDif = []  # DIF = EMA12 - EMA26，即为talib-MACD返回值macd
        self.lineDea = []  # DEA = （前一日DEA X 8/10 + 今日DIF X 2/10），即为talib-MACD返回值
        self.lineMacd = []  # (dif-dea)*2，但是talib中MACD的计算是bar = (dif-dea)*1,国内一般是乘以2

        # K 线的CCI计算数据
        self.inputCciLen = EMPTY_INT
        self.lineCci = []

        # 卡尔曼过滤器
        self.inputKF = False
        self.kf = None
        self.lineStateMean = []
        self.lineStateCovar = []

        # 周期
        self.atan = None
        self.atan_list = []
        self.curPeriod = None  # 当前所在周期
        self.periods = []

        # 优化的多空动量线
        self.inputSkd = False
        self.inputSkdLen1 = 13  # 周期1
        self.inputSkdLen2 = 8  # 周期2
        self.lineSK = []  # 快线
        self.lineSD = []  # 慢线
        self.lowSkd = 30
        self.highSkd = 70

        # 多空趋势线
        self.inputYb = False
        self.lineYb = []

    def addBar(self, bar, bar_is_completed=False):
        """
        予以外部初始化程序增加bar
        :param bar:
        :param bar_is_completed: 插入的bar，其周期与K线周期一致，就设为True
        :return:
        """
        l1 = len(self.lineBar)

        if l1 == 0:
            self.lineBar.append(bar)
            self.curTradingDay = bar.date
            self.onBar(bar)
            return

        # 与最后一个BAR的时间比对，判断是否超过K线的周期
        lastBar = self.lineBar[-1]
        self.curTradingDay = bar.tradingDay if bar.tradingDay is not None else bar.date

        is_new_bar = False
        if bar_is_completed:
            is_new_bar = True

        if bar.datetime.hour > lastBar.datetime.hour and bar.datetime.hour > lastBar.datetime.hour +  self.barTimeInterval:
            is_new_bar = True
        elif bar.datetime.hour < lastBar.datetime.hour and (bar.datetime.hour + 24) > lastBar.datetime.hour + self.barTimeInterval:
            is_new_bar = True

        if is_new_bar:
            # 添加新的bar
            self.lineBar.append(bar)
            # 将上一个Bar推送至OnBar事件
            self.onBar(lastBar)
            return

        # 更新最后一个bar
        # 此段代码，针对一部分短周期生成长周期的k线更新，如3根5分钟k线，合并成1根15分钟k线。
        lastBar.close = bar.close
        lastBar.high = max(lastBar.high, bar.high)
        lastBar.low = min(lastBar.low, bar.low)
        lastBar.volume = lastBar.volume + bar.volume
        lastBar.dayVolume = bar.dayVolume

        lastBar.mid4 = round((2*lastBar.close + lastBar.high + lastBar.low)/4, self.round_n)
        lastBar.mid5 = round((2*lastBar.close + lastBar.open + lastBar.high + lastBar.low)/5, self.round_n)

# ----------------------------------------------------------------------
    def __drawLineBar(self, tick):
        """
        生成 line Bar
        :param tick:
        :return:
        """

        l1 = len(self.lineBar)

        # 保存第一个K线数据
        if l1 == 0:
            self.__firstTick(tick)
            return

        # 清除480周期前的数据，
        if l1 > 60 * 8:
            del self.lineBar[0]

        # 与最后一个BAR的时间比对，判断是否超过K线周期
        lastBar = self.lineBar[-1]

        is_new_bar = False

        if tick.datetime.hour > lastBar.datetime.hour and tick.datetime.hour > lastBar.datetime.hour +  self.barTimeInterval:
            is_new_bar = True
        elif tick.datetime.hour < lastBar.datetime.hour and (tick.datetime.hour + 24) > lastBar.datetime.hour + self.barTimeInterval:
            is_new_bar = True

        if is_new_bar:
            # 创建并推入新的Bar
            self.__firstTick(tick)
            # 触发OnBar事件
            self.onBar(lastBar)

        else:
            # 更新当前最后一个bar
            self.barFirstTick = False

            # 更新最高价、最低价、收盘价、成交量
            lastBar.high = max(lastBar.high, tick.lastPrice)
            lastBar.low = min(lastBar.low, tick.lastPrice)
            lastBar.close = tick.lastPrice

            # 更新日内总交易量，和bar内交易量
            lastBar.dayVolume = tick.volume
            if l1 == 1:
                # 针对第一个bar的tick volume更新
                lastBar.volume = tick.volume
            else:
                lastBar.volume = tick.volume - self.lineBar[-2].dayVolume

            # 更新Bar的颜色
            if lastBar.close > lastBar.open:
                lastBar.color = COLOR_RED
            elif lastBar.close < lastBar.open:
                lastBar.color = COLOR_BLUE
            else:
                lastBar.color = COLOR_EQUAL

class CtaDayBar(CtaLineBar):
    """
    日线级别K线
    """
    def __init__(self, strategy, onBarFunc, setting=None):
        self.had_night_market = False  # 是否有夜市

        if 'period' in setting:
            del setting['period']

        if 'barTimeInterval' in setting:
            del setting['barTimeInterval']

        super(CtaDayBar, self).__init__(strategy, onBarFunc, setting)

    def init_properties(self):
        """
        初始化内部变量
        :return:
        """
        self.paramList.append('barTimeInterval')
        self.paramList.append('period')
        self.paramList.append('inputPreLen')
        self.paramList.append('inputEma1Len')
        self.paramList.append('inputEma2Len')
        self.paramList.append('inputEma3Len')
        self.paramList.append('inputMa1Len')
        self.paramList.append('inputMa2Len')
        self.paramList.append('inputMa3Len')
        self.paramList.append('inputDmiLen')
        self.paramList.append('inputDmiMax')
        self.paramList.append('inputAtr1Len')
        self.paramList.append('inputAtr2Len')
        self.paramList.append('inputAtr3Len')
        self.paramList.append('inputVolLen')
        self.paramList.append('inputRsi1Len')
        self.paramList.append('inputRsi2Len')
        self.paramList.append('inputCmiLen')
        self.paramList.append('inputBollLen')
        self.paramList.append('inputBollStdRate')
        self.paramList.append('inputKdjLen')
        self.paramList.append('inputCciLen')
        self.paramList.append('inputMacdFastPeriodLen')
        self.paramList.append('inputMacdSlowPeriodLen')
        self.paramList.append('inputMacdSignalPeriodLen')
        self.paramList.append('inputKF')
        self.paramList.append('inputSkd')
        self.paramList.append('inputYb')

        self.paramList.append('minDiff')
        self.paramList.append('shortSymbol')
        self.paramList.append('activeDayJump')
        self.paramList.append('name')

        # 输入参数
        self.name = u'DayBar'
        self.mode = self.TICK_MODE  # 缺省为tick模式
        self.period = PERIOD_DAY  # 日线级别周期
        self.barTimeInterval = 1  # 缺省为小时周期

        self.barMinuteInterval = 60*8

        self.inputPreLen = EMPTY_INT  # 1

        self.inputMa1Len = EMPTY_INT  # 10
        self.inputMa2Len = EMPTY_INT  # 20
        self.inputMa3Len = EMPTY_INT  # 120

        self.inputEma1Len = EMPTY_INT  # 13
        self.inputEma2Len = EMPTY_INT  # 21
        self.inputEma3Len = EMPTY_INT  # 120

        self.inputDmiLen = EMPTY_INT  # 14           # DMI的计算周期
        self.inputDmiMax = EMPTY_FLOAT  # 30           # Dpi和Mdi的突破阈值

        self.inputAtr1Len = EMPTY_INT  # 10           # ATR波动率的计算周期(近端）
        self.inputAtr2Len = EMPTY_INT  # 26           # ATR波动率的计算周期（常用）
        self.inputAtr3Len = EMPTY_INT  # 50           # ATR波动率的计算周期（远端）

        self.inputVolLen = EMPTY_INT  # 14           # 平均交易量的计算周期

        self.inputRsi1Len = EMPTY_INT  # 7     # RSI 相对强弱指数（快曲线）
        self.inputRsi2Len = EMPTY_INT  # 14    # RSI 相对强弱指数（慢曲线）

        self.shortSymbol = EMPTY_STRING  # 商品的短代码
        self.minDiff = 1  # 商品的最小价格单位
        self.round_n = 4  # round() 小数点的截断数量
        self.activeDayJump = False  # 隔夜跳空

        # 当前的Tick
        self.curTick = None
        self.lastTick = None
        self.curTradingDay = EMPTY_STRING

        # K线保存数据
        self.bar = None  # K线数据对象
        self.lineBar = []  # K线缓存数据队列
        self.barFirstTick = False  # K线的第一条Tick数据

        # K 线的相关计算结果数据

        self.preHigh = []  # K线的前inputPreLen的的最高
        self.preLow = []  # K线的前inputPreLen的的最低

        self.lineMa1 = []  # K线的MA1均线，周期是InputMaLen1，不包含当前bar
        self.lineMa2 = []  # K线的MA2均线，周期是InputMaLen2，不包含当前bar
        self.lineMa3 = []  # K线的MA2均线，周期是InputMaLen2，不包含当前bar

        self.lineEma1 = []  # K线的EMA1均线，周期是InputEmaLen1，不包含当前bar
        self.lineEma2 = []  # K线的EMA2均线，周期是InputEmaLen2，不包含当前bar
        self.lineEma3 = []  # K线的EMA3均线，周期是InputEmaLen3，不包含当前bar

        # K线的DMI( Pdi，Mdi，ADX，Adxr) 计算数据
        self.barPdi = EMPTY_FLOAT  # bar内的升动向指标，即做多的比率
        self.barMdi = EMPTY_FLOAT  # bar内的下降动向指标，即做空的比率

        self.linePdi = []  # 升动向指标，即做多的比率
        self.lineMdi = []  # 下降动向指标，即做空的比率

        self.lineDx = []  # 趋向指标列表，最大长度为inputM*2
        self.barAdx = EMPTY_FLOAT  # Bar内计算的平均趋向指标
        self.lineAdx = []  # 平均趋向指标
        self.barAdxr = EMPTY_FLOAT  # 趋向平均值，为当日ADX值与M日前的ADX值的均值
        self.lineAdxr = []  # 平均趋向变化指标

        # K线的基于DMI、ADX计算的结果
        self.barAdxTrend = EMPTY_FLOAT  # ADX值持续高于前一周期时，市场行情将维持原趋势
        self.barAdxrTrend = EMPTY_FLOAT  # ADXR值持续高于前一周期时,波动率比上一周期高

        self.buyFilterCond = False  # 多过滤器条件,做多趋势的判断，ADX高于前一天，上升动向> inputMM
        self.sellFilterCond = False  # 空过滤器条件,做空趋势的判断，ADXR高于前一天，下降动向> inputMM

        # K线的ATR技术数据
        self.lineAtr1 = []  # K线的ATR1,周期为inputAtr1Len
        self.lineAtr2 = []  # K线的ATR2,周期为inputAtr2Len
        self.lineAtr3 = []  # K线的ATR3,周期为inputAtr3Len

        self.barAtr1 = EMPTY_FLOAT
        self.barAtr2 = EMPTY_FLOAT
        self.barAtr3 = EMPTY_FLOAT

        # K线的交易量平均
        self.lineAvgVol = []  # K 线的交易量平均

        # K线的RSI计算数据
        self.lineRsi1 = []  # 记录K线对应的RSI数值，只保留inputRsi1Len*8
        self.lineRsi2 = []  # 记录K线对应的RSI数值，只保留inputRsi2Len*8

        self.lowRsi = 30  # RSI的最低线
        self.highRsi = 70  # RSI的最高线

        self.lineRsiTop = []  # 记录RSI的最高峰，只保留 inputRsiLen个
        self.lineRsiButtom = []  # 记录RSI的最低谷，只保留 inputRsiLen个
        self.lastRsiTopButtom = {}  # 最近的一个波峰/波谷

        # K线的CMI计算数据
        self.inputCmiLen = EMPTY_INT
        self.lineCmi = []  # 记录K线对应的Cmi数值，只保留inputCmiLen*8

        # K线的布林特计算数据
        self.inputBollLen = EMPTY_INT  # K线周期
        self.inputBollStdRate = 1.5  # 两倍标准差
        self.lineBollClose = []  # 用于运算的close价格列表
        self.lineUpperBand = []  # 上轨
        self.lineMiddleBand = []  # 中线
        self.lineLowerBand = []  # 下轨
        self.lineBollStd = []  # 标准差

        self.lastBollUpper = EMPTY_FLOAT  # 最后一根K的Boll上轨数值（与MinDiff取整）
        self.lastBollMiddle = EMPTY_FLOAT  # 最后一根K的Boll中轨数值（与MinDiff取整）
        self.lastBollLower = EMPTY_FLOAT  # 最后一根K的Boll下轨数值（与MinDiff取整+1）

        # K线的KDJ指标计算数据
        self.inputKdjLen = EMPTY_INT  # KDJ指标的长度,缺省是9
        self.lineK = []  # K为快速指标
        self.lineD = []  # D为慢速指标
        self.lineJ = []  #
        self.lineKdjTop = []  # 记录KDJ最高峰，只保留 inputKdjLen个
        self.lineKdjButtom = []  # 记录KDJ的最低谷，只保留 inputKdjLen个
        self.lastKdjTopButtom = {}  # 最近的一个波峰/波谷
        self.lastK = EMPTY_FLOAT  # bar内计算时，最后一个未关闭的bar的实时K值
        self.lastD = EMPTY_FLOAT  # bar内计算时，最后一个未关闭的bar的实时值
        self.lastJ = EMPTY_FLOAT  # bar内计算时，最后一个未关闭的bar的实时J值

        # K线的MACD计算数据
        self.inputMacdFastPeriodLen = EMPTY_INT
        self.inputMacdSlowPeriodLen = EMPTY_INT
        self.inputMacdSignalPeriodLen = EMPTY_INT

        self.lineDif = []  # DIF = EMA12 - EMA26，即为talib-MACD返回值macd
        self.lineDea = []  # DEA = （前一日DEA X 8/10 + 今日DIF X 2/10），即为talib-MACD返回值
        self.lineMacd = []  # (dif-dea)*2，但是talib中MACD的计算是bar = (dif-dea)*1,国内一般是乘以2

        # K 线的CCI计算数据
        self.inputCciLen = EMPTY_INT
        self.lineCci = []

        # 卡尔曼过滤器
        self.inputKF = False
        self.kf = None
        self.lineStateMean = []
        self.lineStateCovar = []

        # 周期
        self.atan = None
        self.atan_list = []
        self.curPeriod = None  # 当前所在周期
        self.periods = []

        # 优化的多空动量线
        self.inputSkd = False
        self.inputSkdLen1 = 13  # 周期1
        self.inputSkdLen2 = 8  # 周期2
        self.lineSK = []  # 快线
        self.lineSD = []  # 慢线
        self.lowSkd = 30
        self.highSkd = 70

        # 多空趋势线
        self.inputYb = False
        self.lineYb = []

    def addBar(self, bar, bar_is_completed=False):
        """
        予以外部初始化程序增加bar
        :param bar:
        :param bar_is_completed: 插入的bar，其周期与K线周期一致，就设为True
        :return:
        """
        l1 = len(self.lineBar)

        if l1 == 0:
            new_bar = copy.copy(bar)
            self.lineBar.append(new_bar)
            self.curTradingDay = bar.tradingDay if bar.tradingDay is not None else bar.date
            if bar_is_completed:
                self.onBar(bar)
            return

        # 与最后一个BAR的时间比对，判断是否超过K线的周期
        lastBar = self.lineBar[-1]
        self.curTradingDay = bar.tradingDay if bar.tradingDay is not None else bar.date

        is_new_bar = False
        if bar_is_completed:
            is_new_bar = True

        # 夜盘时间判断
        if self.had_night_market and bar.datetime.hour >= 21 and lastBar.datetime.hour < 21:
            is_new_bar = True
            self.curTradingDay = bar.tradingDay if bar.tradingDay is not None else bar.date

        # 日期判断
        if not is_new_bar and lastBar.tradingDay != self.curTradingDay:
            is_new_bar = True
            self.curTradingDay = bar.tradingDay if bar.tradingDay is not None else bar.date

        if is_new_bar:
            # 添加新的bar
            new_bar = copy.copy(bar)
            self.lineBar.append(new_bar)
            # 将上一个Bar推送至OnBar事件
            self.onBar(lastBar)
            return

        # 更新最后一个bar
        # 此段代码，针对一部分短周期生成长周期的k线更新，如3根5分钟k线，合并成1根15分钟k线。
        lastBar.close = bar.close
        lastBar.high = max(lastBar.high, bar.high)
        lastBar.low = min(lastBar.low, bar.low)
        lastBar.volume = lastBar.volume + bar.volume
        lastBar.dayVolume = lastBar.volume

        lastBar.mid4 = round((2*lastBar.close + lastBar.high + lastBar.low)/4, self.round_n)
        lastBar.mid5 = round((2*lastBar.close + lastBar.open + lastBar.high + lastBar.low)/5, self.round_n)

# ----------------------------------------------------------------------
    def __drawLineBar(self, tick):
        """
        生成 line Bar
        :param tick:
        :return:
        """

        l1 = len(self.lineBar)

        # 保存第一个K线数据
        if l1 == 0:
            self.__firstTick(tick)
            return

        # 清除480周期前的数据，
        if l1 > 60 * 8:
            del self.lineBar[0]

        # 与最后一个BAR的时间比对，判断是否超过K线周期
        lastBar = self.lineBar[-1]

        is_new_bar = False

        if tick.tradingDay != lastBar.tradingDay:
            is_new_bar = True


        if is_new_bar:
            # 创建并推入新的Bar
            self.__firstTick(tick)
            # 触发OnBar事件
            self.onBar(lastBar)

        else:
            # 更新当前最后一个bar
            self.barFirstTick = False

            # 更新最高价、最低价、收盘价、成交量
            lastBar.high = max(lastBar.high, tick.lastPrice)
            lastBar.low = min(lastBar.low, tick.lastPrice)
            lastBar.close = tick.lastPrice

            # 更新日内总交易量，和bar内交易量
            lastBar.dayVolume = tick.volume
            if l1 == 1:
                # 针对第一个bar的tick volume更新
                lastBar.volume = tick.volume
            else:
                lastBar.volume = tick.volume - self.lineBar[-2].dayVolume

            # 更新Bar的颜色
            if lastBar.close > lastBar.open:
                lastBar.color = COLOR_RED
            elif lastBar.close < lastBar.open:
                lastBar.color = COLOR_BLUE
            else:
                lastBar.color = COLOR_EQUAL

