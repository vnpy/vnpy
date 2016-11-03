# encoding: UTF-8

# AUTHOR:李来佳
# WeChat/QQ: 28888502

from vtConstant import *
from ctaBase import *

from datetime import datetime

import talib as ta
import numpy
import copy,csv


DEBUGCTALOG = True

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

    # 参数列表，保存了参数的名称
    paramList = ['vtSymbol']

    def __init__(self, strategy, onBarFunc, setting=None,):

        # OnBar事件回调函数
        self.onBarFunc = onBarFunc

        # 参数列表
        self.paramList.append('barTimeInterval')
        self.paramList.append('inputPreLen')
        self.paramList.append('inputEma1Len')
        self.paramList.append('inputEma2Len')
        self.paramList.append('inputDmiLen')
        self.paramList.append('inputDmiMax')
        self.paramList.append('inputAtr1Len')
        self.paramList.append('inputAtr2Len')
        self.paramList.append('inputAtr3Len')
        self.paramList.append('inputVolLen')
        self.paramList.append('inputRsiLen')
        self.paramList.append('inputCmiLen')
        self.paramList.append('inputBollLen')
        self.paramList.append('inputBollStdRate')


        self.paramList.append('minDiff')
        self.paramList.append('shortSymbol')
        self.paramList.append('activeDayJump')
        self.paramList.append('name')


        # 输入参数
        self.name = u'LineBar'
        self.barTimeInterval = 300

        self.inputPreLen = EMPTY_INT    #1

        self.inputEma1Len = EMPTY_INT   # 13
        self.inputEma2Len = EMPTY_INT   # 21

        self.inputDmiLen = EMPTY_INT    # 14           # DMI的计算周期
        self.inputDmiMax = EMPTY_FLOAT  # 30           # Dpi和Mdi的突破阈值

        self.inputAtr1Len = EMPTY_INT   # 10           # ATR波动率的计算周期(近端）
        self.inputAtr2Len = EMPTY_INT   # 26           # ATR波动率的计算周期（常用）
        self.inputAtr3Len = EMPTY_INT   # 50           # ATR波动率的计算周期（远端）

        self.inputVolLen = EMPTY_INT    # 14           # 平均交易量的计算周期

        self.inputRsiLen = EMPTY_INT    # 7    # RSI 相对强弱指数

        self.shortSymbol = EMPTY_STRING # 商品的短代码
        self.minDiff = 1                # 商品的最小价格单位

        self.activeDayJump = False      # 隔夜跳空

        # 当前的Tick
        self.curTick = None

        # K 线服务的策略
        self.strategy = strategy

        # K线保存数据
        self.bar = None                # K线数据对象
        self.lineBar = []              # K线缓存数据队列
        self.barFirstTick =False       # K线的第一条Tick数据

        # K 线的相关计算结果数据

        self.preHigh = []               # K线的前inputPreLen的的最高
        self.preLow = []                # K线的前inputPreLen的的最低

        self.lineEma1 = []              # K线的EMA1均线，周期是InputEmaLen1，包含当前bar
        self.lineEma1MtmRate = []       # K线的EMA1均线 的momentum(3) 动能

        self.lineEma2 = []              # K线的EMA2均线，周期是InputEmaLen2，包含当前bar
        self.lineEma2MtmRate = []       # K线的EMA2均线 的momentum(3) 动能

        # K线的DMI( Pdi，Mdi，ADX，Adxr) 计算数据
        self.barPdi = EMPTY_FLOAT      # bar内的升动向指标，即做多的比率
        self.barMdi = EMPTY_FLOAT      # bar内的下降动向指标，即做空的比率

        self.linePdi = []             # 升动向指标，即做多的比率
        self.lineMdi = []             # 下降动向指标，即做空的比率

        self.lineDx = []              # 趋向指标列表，最大长度为inputM*2
        self.barAdx = EMPTY_FLOAT     # Bar内计算的平均趋向指标
        self.lineAdx = []             # 平均趋向指标
        self.barAdxr = EMPTY_FLOAT    # 趋向平均值，为当日ADX值与M日前的ADX值的均值
        self.lineAdxr = []            # 平均趋向变化指标

        # K线的基于DMI、ADX计算的结果
        self.barAdxTrend = EMPTY_FLOAT        # ADX值持续高于前一周期时，市场行情将维持原趋势
        self.barAdxrTrend = EMPTY_FLOAT       # ADXR值持续高于前一周期时,波动率比上一周期高

        self.buyFilterCond = False          # 多过滤器条件,做多趋势的判断，ADX高于前一天，上升动向> inputMM
        self.sellFilterCond = False         # 空过滤器条件,做空趋势的判断，ADXR高于前一天，下降动向> inputMM

        # K线的ATR技术数据
        self.lineAtr1 = []              # K线的ATR1,周期为inputAtr1Len
        self.lineAtr2 = []              # K线的ATR2,周期为inputAtr2Len
        self.lineAtr3 = []              # K线的ATR3,周期为inputAtr3Len

        self.barAtr1 = EMPTY_FLOAT
        self.barAtr2 = EMPTY_FLOAT
        self.barAtr3 = EMPTY_FLOAT

        # K线的交易量平均
        self.lineAvgVol = []        # K 线的交易量平均

        # K线的RSI计算数据
        self.lineRsi = []           # 记录K线对应的RSI数值，只保留inputRsiLen*8

        self.lowRsi = 30            # RSI的最低线
        self.highRsi = 70           # RSI的最高线

        self.lineRsiTop = []        # 记录RSI的最高峰，只保留 inputRsiLen个
        self.lineRsiButtom = []     # 记录RSI的最低谷，只保留 inputRsiLen个
        self.lastRsiTopButtom = None # 最近的一个波峰/波谷

         # K线的CMI计算数据
        self.inputCmiLen = EMPTY_INT
        self.lineCmi = []           # 记录K线对应的Cmi数值，只保留inputCmiLen*8

        # K线的布林特计算数据
        self.inputBollLen = EMPTY_INT  # K线周期
        self.inputBollStdRate = 1.5      # 两倍标准差

        self.lineUpperBand = []            # 上轨
        self.lineMiddleBand = []           # 中线
        self.lineLowerBand = []            # 下轨

        if setting:
            self.setParam(setting)

    def setParam(self, setting):
        """设置参数"""
        d = self.__dict__
        for key in self.paramList:
            if key in setting:

                d[key] = setting[key]

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

        self.curTick = tick

        # 3.生成x K线，若形成新Bar，则触发OnBar事件
        self.__drawLineBar(tick)

    def addBar(self,bar):
        """予以外部初始化程序增加bar"""
        l1 = len(self.lineBar)

        if l1 == 0:
            self.lineBar.append(bar)
            self.onBar(bar)
            return

        # 与最后一个BAR的时间比对，判断是否超过K线的周期
        lastBar = self.lineBar[-1]

        if (bar.datetime - lastBar.datetime).seconds >= self.barTimeInterval:
            self.lineBar.append(bar)
            self.onBar(bar)
            return

        # 更新最后一个bar
        lastBar.close = bar.close
        lastBar.high = max(lastBar.high, bar.high)
        lastBar.low = min(lastBar.low, bar.low)
        lastBar.volume = lastBar.volume + bar.volume


    def onBar(self, bar):
        """OnBar事件"""
        # 计算相关数据
        self.__recountPreHighLow()
        self.__recountEma()
        self.__recountDmi()
        self.__recountAtr()
        self.__recoundAvgVol()
        self.__recountRsi()
        self.__recountCmi()
        self.__recountBoll()


        # 回调上层调用者
        self.onBarFunc(bar)


    def __firstTick(self,tick):
        """ K线的第一个Tick数据"""
        self.bar = CtaBarData()                  # 创建新的K线

        self.bar.vtSymbol = tick.vtSymbol
        self.bar.symbol = tick.symbol
        self.bar.exchange = tick.exchange

        self.bar.open = tick.lastPrice            # O L H C
        self.bar.high = tick.lastPrice
        self.bar.low = tick.lastPrice
        self.bar.close = tick.lastPrice

        # K线的日期时间
        self.bar.date = tick.date                # K线的日期时间（去除秒）设为第一个Tick的时间
        self.bar.time = tick.time              # K线的日期时间（去除秒）设为第一个Tick的时间
        self.bar.datetime = tick.datetime

        self.bar.volume = tick.volume
        self.bar.openInterest = tick.openInterest

        self.barFirstTick = True                  # 标识该Tick属于该Bar的第一个tick数据

        self.lineBar.append(self.bar)           # 推入到lineBar队列

    # ----------------------------------------------------------------------
    def __drawLineBar(self, tick):
        """生成 line Bar  """

        l1 = len(self.lineBar)

        # 保存第一个K线数据
        if l1 == 0:
            self.__firstTick(tick)
            self.onBar(self.bar)
            return

        # 清除8交易小时前的数据，
        if l1 > 60 * 8:
            del self.lineBar[0]

        # 与最后一个BAR的时间比对，判断是否超过5分钟
        lastBar = self.lineBar[-1]

        # 专门处理隔夜跳空。隔夜跳空会造成开盘后EMA和ADX的计算错误。
        if len(self.lineAtr2) < 1:
            priceInBar = 5 * self.minDiff
        else:
            priceInBar = self.lineAtr2[-1]

        jumpBars = int(abs(tick.lastPrice - lastBar.close)/priceInBar)

        # 开盘时间
        if (tick.datetime.hour == 9 or tick.datetime.hour == 21) \
                and tick.datetime.minute == 0 and tick.datetime.second == 0 \
                and lastBar.datetime.hour != tick.datetime.hour \
                and jumpBars > 0 and self.activeDayJump:

            priceInYesterday = lastBar.close

            self.writeCtaLog(u'line Bar jumpbars:{0}'.format(jumpBars))

            if tick.lastPrice > priceInYesterday:           # 价格往上跳

                # 生成砖块递增K线,减小ATR变动
                for i in range(0, jumpBars, 1):
                    upbar = copy.deepcopy(lastBar)
                    upbar.open = priceInYesterday + float(i * priceInBar)
                    upbar.low = upbar.open
                    upbar.close = priceInYesterday + float((i+1) * priceInBar)
                    upbar.high = upbar.close
                    upbar.volume = 0

                    self.lineBar.append(upbar)
                    self.onBar(upbar)

            else:                                            # 价格往下跳
                # 生成递减K线,减小ATR变动
                for i in range(0, jumpBars, 1):

                    downbar = copy.deepcopy(lastBar)
                    downbar.open = priceInYesterday - float(i * priceInBar)
                    downbar.high = downbar.open
                    downbar.close = priceInYesterday - float((i+1) * priceInBar)
                    downbar.low = downbar.close
                    downbar.volume = 0

                    self.lineBar.append(downbar)
                    self.onBar(downbar)

            # 生成平移K线，减小Pdi，Mdi、ADX变动
            for i in range(0, jumpBars*2, 1):
                equalbar=copy.deepcopy(self.lineBar[-1])
                equalbar.volume = 0
                self.lineBar.append(equalbar)
                self.onBar(equalbar)

            # 重新指定为最后一个Bar
            lastBar = self.lineBar[-1]

        # 处理日内的间隔时段最后一个tick，如10:15分，11:30分，15:00 和 2:30分
        endtick = False
        if (tick.datetime.hour == 10 and tick.datetime.minute == 15 ) \
            or (tick.datetime.hour == 11 and tick.datetime.minute == 30 ) \
            or (tick.datetime.hour == 15 and tick.datetime.minute == 00 ) \
            or (tick.datetime.hour == 2 and tick.datetime.minute == 30 ):
            endtick = True

        if self.shortSymbol in NIGHT_MARKET_SQ2 and tick.datetime.hour == 1 and tick.datetime.minute == 00:
            endtick = True

        if self.shortSymbol in NIGHT_MARKET_SQ3 and tick.datetime.hour == 23 and tick.datetime.minute == 00:
            endtick = True

        if self.shortSymbol in NIGHT_MARKET_ZZ or self.shortSymbol in NIGHT_MARKET_DL:
            if tick.datetime.hour == 23 and tick.datetime.minute == 30:
                endtick = True

        # 满足时间要求
        if (tick.datetime-lastBar.datetime).seconds >= self.barTimeInterval and not endtick:

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
            lastBar.volume = lastBar.volume + tick.volume

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

        for i in range(len(self.lineBar)-2, len(self.lineBar)-2-self.inputPreLen, -1):

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


    def __recountEma(self):
        """计算K线的EMA1 和EMA2"""
        l = len(self.lineBar)

        # 1、lineBar满足长度才执行计算
        if len(self.lineBar) < max(7, self.inputEma1Len, self.inputEma2Len)+2:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算EMA需要：{1}'.
                             format(len(self.lineBar), max(7, self.inputEma1Len, self.inputEma2Len)+2))
            return

        # 计算第一条EMA均线
        if self.inputEma1Len > 0:

            if self.inputEma1Len > l:
                ema1Len = l
            else:
                ema1Len = self.inputEma1Len

            # 3、获取前InputN周期(不包含当前周期）的自适应均线
            listClose=[x.close for x in self.lineBar[-ema1Len - 1:-1]]

            barEma1 = ta.EMA(numpy.array(listClose, dtype=float), ema1Len)[-1]

            barEma1 = round(float(barEma1), 3)

            if len(self.lineEma1) > self.inputEma1Len*8:
                del self.lineEma1[0]
            self.lineEma1.append(barEma1)

        # 计算第二条EMA均线
        if self.inputEma2Len > 0:

            if self.inputEma2Len > l:
                ema2Len = l
            else:
                ema2Len = self.inputEma2Len

            # 3、获取前InputN周期(不包含当前周期）的自适应均线
            listClose=[x.close for x in self.lineBar[-ema2Len - 1:-1]]
            barEma2 = ta.EMA(numpy.array(listClose, dtype=float), ema2Len)[-1]

            barEma2 = round(float(barEma2), 3)

            if len(self.lineEma2) > self.inputEma1Len*8:
                del self.lineEma2[0]
            self.lineEma2.append(barEma2)


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

        for i in range(len(self.lineBar)-2, len(self.lineBar)-2-self.inputDmiLen, -1):  # 周期 inputDmiLen
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
            self.barAdx = ta.EMA(numpy.array(self.lineDx, dtype=float), self.inputDmiLen)[-1]

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

        # 首次计算
        if (self.inputAtr1Len > 0 and len(self.lineAtr1) < 1) \
                or (self.inputAtr2Len > 0 and len(self.lineAtr2) < 1) \
                or (self.inputAtr3Len > 0 and len(self.lineAtr3) < 1):

            # 根据当前High，Low，(不包含当前周期）重新计算TR1和ATR
            barTr1 = EMPTY_FLOAT      # 获取inputAtr1Len周期内的价差最大值之和
            barTr2 = EMPTY_FLOAT      # 获取inputAtr2Len周期内的价差最大值之和
            barTr3 = EMPTY_FLOAT      # 获取inputAtr3Len周期内的价差最大值之和

            j = 0
            for i in range(len(self.lineBar)-2, len(self.lineBar)-2-maxAtrLen, -1):  # 周期 inputP
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
            high_low_spread = self.lineBar[-2].high - self.lineBar[-2].low
            # 当前周期最高与昨收价的价差
            high_preclose_spread = abs(self.lineBar[-2].high - self.lineBar[-3].close)
            # 当前周期最低与昨收价的价差
            low_preclose_spread = abs(self.lineBar[-2].low - self.lineBar[-3].close)

            # 最大价差
            barTr1 = max(high_low_spread, high_preclose_spread, low_preclose_spread)
            barTr2 = barTr1
            barTr3 = barTr1

        # 计算 ATR
        if self.inputAtr1Len > 0:
            if len(self.lineAtr1) < 1:
                self.barAtr1 = round(barTr1 / self.inputAtr1Len, 3)
            else:
                self.barAtr1 = round((self.lineAtr1[-1]*(self.inputAtr1Len -1) + barTr1) / self.inputAtr1Len, 3)

            if len(self.lineAtr1) > self. inputAtr1Len+1 :
                del self.lineAtr1[0]
            self.lineAtr1.append(self.barAtr1)

        if self.inputAtr2Len > 0:
            if len(self.lineAtr2) < 1:
                self.barAtr2 = round(barTr2 / self.inputAtr2Len, 3)
            else:
                self.barAtr2 = round((self.lineAtr2[-1]*(self.inputAtr2Len -1) + barTr2) / self.inputAtr2Len, 3)

            if len(self.lineAtr2) > self. inputAtr2Len+1:
                del self.lineAtr2[0]
            self.lineAtr2.append(self.barAtr2)

        if self.inputAtr3Len > 0:
            if len(self.lineAtr3) < 1:
                self.barAtr3 = round(barTr3 / self.inputAtr3Len, 3)
            else:
                self.barAtr3 = round((self.lineAtr3[-1]*(self.inputAtr3Len -1) + barTr3) / self.inputAtr3Len, 3)

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

        listVol = [x.volume for x in self.lineBar[-self.inputVolLen-1: -1]]

        sumVol = ta.SUM(numpy.array(listVol, dtype=float), timeperiod=self.inputVolLen)[-1]

        avgVol = round(sumVol/self.inputVolLen, 0)

        self.lineAvgVol.append(avgVol)

    # ----------------------------------------------------------------------
    def __recountRsi(self):
        """计算K线的RSI"""

        if self.inputRsiLen <= 0: return

        # 1、lineBar满足长度才执行计算
        if len(self.lineBar) < self.inputRsiLen+2:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算RSI需要：{1}'.
                             format(len(self.lineBar), self.inputRsiLen+2))
            return

        # 3、inputRsiLen(包含当前周期）的相对强弱
        listClose=[x.close for x in self.lineBar[-self.inputRsiLen - 2:]]
        barRsi = ta.RSI(numpy.array(listClose, dtype=float), self.inputRsiLen)[-1]
        barRsi = round(float(barRsi), 3)

        l = len(self.lineRsi)
        if l > self.inputRsiLen*8:
            del self.lineRsi[0]

        self.lineRsi.append(barRsi)

        if l > 3:
            # 峰
            if self.lineRsi[-1] < self.lineRsi[-2] and self.lineRsi[-3] < self.lineRsi[-2]:

                t={}
                t["Type"] = u'T'
                t["RSI"] = self.lineRsi[-2]
                t["Close"] = self.lineBar[-2].close


                if len(self.lineRsiTop) > self.inputRsiLen:
                    del self.lineRsiTop[0]

                self.lineRsiTop.append( t )
                self.lastRsiTopButtom = self.lineRsiTop[-1]

            # 谷
            elif self.lineRsi[-1] > self.lineRsi[-2] and self.lineRsi[-3] > self.lineRsi[-2]:

                b={}
                b["Type"] = u'B'
                b["RSI"] = self.lineRsi[-2]
                b["Close"] = self.lineBar[-2].close

                if len(self.lineRsiButtom) > self.inputRsiLen:
                    del self.lineRsiButtom[0]
                self.lineRsiButtom.append(b)
                self.lastRsiTopButtom = self.lineRsiButtom[-1]

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

        listClose =[x.close for x in self.lineBar[-self.inputCmiLen:]]
        hhv = max(listClose)
        llv = min(listClose)

        if hhv==llv:
            cmi = 100
        else:
            cmi = abs(self.lineBar[-1].close-self.lineBar[-2].close)*100/(hhv-llv)

        cmi = round(cmi, 2)

        if len(self.lineCmi) > self.inputCmiLen:
            del self.lineCmi[0]

        self.lineCmi.append(cmi)

    def __recountBoll(self):
        """布林特线"""
        if self.inputBollLen < EMPTY_INT: return

        l = len(self.lineBar)

        if l < min(7, self.inputBollLen)+1:
            self.debugCtaLog(u'数据未充分,当前Bar数据数量：{0}，计算Boll需要：{1}'.
                             format(len(self.lineBar), min(7, self.inputBollLen)+1))
            return

        if l < self.inputBollLen+2:
            bollLen = l-1
        else:
            bollLen = self.inputBollLen

        # 不包含当前最新的Bar
        listClose=[x.close for x in self.lineBar[-bollLen - 1:-1]]
        #
        upper, middle, lower = ta.BBANDS(numpy.array(listClose, dtype=float),
                                         timeperiod=bollLen, nbdevup=self.inputBollStdRate,
                                         nbdevdn=self.inputBollStdRate, matype=0)

        self.lineUpperBand.append(upper[-1])
        self.lineMiddleBand.append(middle[-1])
        self.lineLowerBand.append(lower[-1])


    # ----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """记录CTA日志"""
        self.strategy.writeCtaLog(u'['+self.name+u']'+content)

    def debugCtaLog(self,content):
        """记录CTA日志"""
        if DEBUGCTALOG:
            self.strategy.writeCtaLog(u'['+self.name+u'-DEBUG]'+content)