# encoding: UTF-8

from ctaBase import *
from vtConstant import *


DEBUGCTALOG = True

class CtaPolicy(object):
    """CTA的策略规则类
    包括：
    1、风险评估
    2、最低止损位置
    3、保本止损位置
    4、跟随止损/止盈位置
    5、是否加仓等

    R1,Big Range/Renko
    R2,Small Range/Renko
    """

    def __init__(self, r1Period=EMPTY_STRING, r2Period=EMPTY_STRING):

        self.openR1Period = r1Period              # 开仓周期Mode
        self.openR2Period = r2Period              # 开仓周期Mode

        self.entryPrice = EMPTY_FLOAT             # 开仓价格
        self.lastPeriodBasePrice = EMPTY_FLOAT    # 上一个周期内的最近高价/低价(看R2 Rsi的高点和低点）
        self.entryTime = None

        self.riskLevel = EMPTY_INT                # 风险评分,1、低；2、中；3、高

        self.cancelInNextBar = False

        self.addPos = False                       # 是否加仓
        self.addPosOnPips = EMPTY_INT             # 价格超过开仓价多少点时加仓
        self.addPosOnRtnPercent = EMPTY_FLOAT     # 价格回撤比例时加仓
        self.addPosOnRsiRtnWithPips = EMPTY_INT   # 价格超过开仓价，并且低位RSI反转（多：RSI低位折返，空：RSI高位折返）
        self.addPosOnKdjRtnWithPips = EMPTY_INT   # 价格超过开仓价，并且低位Kdj反转（多：Kdj低位折返，空：Kdj高位折返）

        self.exitOnStopPrice = EMPTY_FLOAT        # 固定止损价格。 这个规则最优先匹配，作为最大亏损线。
        self.exitOnWinPrice = EMPTY_FLOAT         # 固定止盈价格。

        self.exitOnProtectedPrice = EMPTY_FLOAT   # 保本价格。
        self.exitOnLastRtnPips = EMPTY_INT        # 盈利后，最后开仓价的回调点数。 使用时，pips* minDiff
        self.exitOnTopRtnPips = EMPTY_INT         # 盈利后，最高盈利的回撤点数。 使用时，pips * minDiff

        self.exitOnR2RsiRtn = False               # First RSI Return
        self.exitOnR2EmaCrossed = False           # EMA(inputEma1Len) Cross Above、 Under
        self.exitOnR2KamaCrossed = False          # AMA(inputAma1Len) Cross Above、 Under
        self.exitOnR2KamaRtn = False              # 盈利后，Kama[-1] vs Kama[-2]

        self.exitOnR1RsiRtn = False               # First RSI Return
        self.exitOnR1EmaCrossed = False           # EMA(inputEma1Len) Cross Above、 Under
        self.exitOnR1KamaCrossed = False          # AMA(inputAma1Len) Cross Above、 Under
        self.exitOnR1KamaRtn = False              # 盈利后，Kama[-1] vs Kama[-2]

        self.exitOnR1PeriodChanged = False        # R1 Period Changed, if True,openR1Period != periodMode
        self.exitOnR2PeriodChanged = False        # R2 Period Changed, if True,openR2Period != periodMode

        self.exitOnR1PeriodModes = []    # 可以与exitOnR1PeriodChanged ,指定的立场周期；进入后，激活 exitOnR2RsiRtn




