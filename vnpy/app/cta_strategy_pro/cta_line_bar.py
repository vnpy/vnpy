# encoding: UTF-8

# AUTHOR:李来佳
# WeChat/QQ: 28888502
# 广东华富资产管理

import copy
import decimal
import math
import os
import sys
import traceback
import talib as ta
import numpy as np

from collections import OrderedDict
from datetime import datetime, timedelta

from pykalman import KalmanFilter

from vnpy.app.cta_strategy_pro.base import (
    Direction,
    Area,
    MARKET_DAY_ONLY,
    NIGHT_MARKET_23,
    NIGHT_MARKET_SQ2,
    MARKET_ZJ)
from vnpy.app.cta_strategy_pro.cta_period import CtaPeriod, Period
from vnpy.trader.object import BarData, TickData
from vnpy.trader.constant import Interval, Color, Exchange
from vnpy.trader.utility import round_to, get_trading_date, get_underlying_symbol


def get_cta_bar_class(bar_type: str):
    """根据类型名获取对象"""
    assert isinstance(bar_type, str)
    if bar_type == Interval.SECOND:
        return CtaLineBar
    if bar_type == Interval.MINUTE:
        return CtaMinuteBar
    if bar_type == Interval.HOUR:
        return CtaHourBar
    if bar_type == Interval.DAILY:
        return CtaDayBar
    if bar_type == Interval.WEEKLY:
        return CtaWeekBar

    raise Exception('no matched CTA  bar type:{}'.format(bar_type))


class CtaLineBar(object):
    """CTA K线"""

    """ 使用方法:
    1、在策略构造函数__init()中初始化
    self.lineM = None                       # 1分钟K线
    lineMSetting = {}
    lineMSetting['name'] = u'M1'
    lineMSetting['bar_interval'] = 60    # 1分钟对应60秒
    lineMSetting['inputEma1Len'] = 7        # EMA线1的周期
    lineMSetting['inputEma2Len'] = 21       # EMA线2的周期
    lineMSetting['inputBollLen'] = 20       # 布林特线周期
    lineMSetting['inputBollStdRate'] = 2    # 布林特线标准差
    lineMSetting['price_tick'] = self.price_tick  # 最小条
    lineMSetting['underlying_symbol'] = self.underlying_symbol  #商品短号
    self.lineM = CtaLineBar(self, self.onBar, lineMSetting)

    2、在onTick()中，需要导入tick数据
    self.lineM.onTick(tick)
    self.lineM5.onTick(tick) # 如果你使用2个周期

    3、在onBar事件中，按照k线结束使用；其他任何情况下bar内使用，通过对象使用即可，self.lineM.lineBar[-1].close

    # 创建30分钟K线（类似文华，用交易日内，累加分钟够30根1min bar）
    lineM30Setting = {}
    lineM30Setting['name'] = u'M30'
    lineM30Setting['interval'] = Interval.MINUTE
    lineM30Setting['bar_interval'] = 30
    lineM30Setting['mode'] = CtaLineBar.TICK_MODE
    lineM30Setting['price_tick'] = self.price_tick
    lineM30Setting['underlying_symbol'] = self.underlying_symbol
    self.lineM30 = CtaMinuteBar(self, self.onBarM30, lineM30Setting)

    # 创建2小时K线
    lineH2Setting = {}
    lineH2Setting['name'] = u'H2'
    lineH2Setting['interval'] = Interval.HOUR
    lineH2Setting['bar_inverval'] = 2
    lineH2Setting['mode'] = CtaLineBar.TICK_MODE
    lineH2Setting['price_tick'] = self.price_tick
    lineH2Setting['underlying_symbol'] = self.underlying_symbol
    self.lineH2 = CtaHourBar(self, self.onBarH2, lineH2Setting)

    # 创建的日K线
    lineDaySetting = {}
    lineDaySetting['name'] = u'D1'
    lineDaySetting['mode'] = CtaDayBar.TICK_MODE
    lineDaySetting['price_tick'] = self.price_tick
    lineDaySetting['underlying_symbol'] = self.underlying_symbol
    self.lineD = CtaDayBar(self, self.onBarD, lineDaySetting)
    """

    # 区别：
    # -使用tick模式时，当tick到达后，最新一个lineBar[-1]是当前的正在拟合的bar，不断累积tick，传统按照OnBar来计算的话，是使用LineBar[-2]。
    # -使用bar模式时，当一个bar到达时，lineBar[-1]是当前生成出来的Bar,不再更新
    TICK_MODE = 'tick'
    BAR_MODE = 'bar'

    CB_ON_BAR = 'cb_on_bar'
    CB_ON_PERIOD = 'cb_on_period'

    # 参数列表，保存了参数的名称
    paramList = ['vt_symbol']

    # 参数列表

    def __init__(self, strategy, cb_on_bar, setting=None):

        # OnBar事件回调函数
        self.cb_on_bar = cb_on_bar

        # 周期变更事件回调函数
        self.cb_on_period = None

        # K 线服务的策略
        self.strategy = strategy

        self.underly_symbol = ''  # 商品的短代码
        self.price_tick = 1  # 商品的最小价格单位
        self.round_n = 4  # round() 小数点的截断数量

        self.is_7x24 = False

        # 当前的Tick
        self.cur_tick = None
        self.last_tick = None
        self.cur_datetime = None
        self.cur_trading_day = ''
        self.cur_price = 0

        # K线保存数据
        self.cur_bar = None  # K线数据对象，代表最后一根/未走完的bar
        self.line_bar = []  # K线缓存数据队列
        self.bar_len = 0  # 当前K线得真实数量
        self.max_hold_bars = 2000
        self.is_first_tick = False  # K线的第一条Tick数据

        # (实时运行时，或者addbar小于bar得周期时，不包含最后一根Bar）
        self.open_array = np.zeros(self.max_hold_bars)  # 与lineBar一致得开仓价清单
        self.high_array = np.zeros(self.max_hold_bars)  # 与lineBar一致得最高价清单
        self.low_array = np.zeros(self.max_hold_bars)  # 与lineBar一致得最低价清单
        self.close_array = np.zeros(self.max_hold_bars)  # 与lineBar一致得收盘价清单

        self.mid3_array = np.zeros(self.max_hold_bars)  # 收盘价/最高/最低价 的平均价
        self.mid4_array = np.zeros(self.max_hold_bars)  # 收盘价*2/最高/最低价 的平均价
        self.mid5_array = np.zeros(self.max_hold_bars)  # 收盘价*2/开仓价/最高/最低价 的平均价

        self.export_filename = None
        self.export_fields = []

        # 创建内部变量
        self.init_properties()

        # 创建初始化指标
        self.init_indicators()

        # 启动实时得函数
        self.rt_funcs = set()
        self.rt_executed = False

        # 注册回调函数
        self.cb_dict = {}

        if setting:
            self.set_params(setting)

            # 修正self.minute_interval
            if self.interval == Interval.SECOND:
                self.minute_interval = int(self.bar_interval / 60)
            elif self.interval == Interval.MINUTE:
                self.minute_interval = self.bar_interval
            elif self.interval == Interval.HOUR:
                self.minute_interval = 60
            elif self.interval == Interval.DAILY:
                self.minute_interval = 60 * 24
            # 修正精度
            if self.price_tick < 1:
                exponent = decimal.Decimal(str(self.price_tick))
                self.round_n = max(abs(exponent.as_tuple().exponent), 4)

            # 导入卡尔曼过滤器
            if self.para_active_kf:
                try:
                    self.kf = KalmanFilter(transition_matrices=[1],
                                           observation_matrices=[1],
                                           initial_state_mean=0,
                                           initial_state_covariance=1,
                                           observation_covariance=1,
                                           transition_covariance=0.01)
                except Exception:
                    self.write_log(u'导入卡尔曼过滤器失败,需先安装 pip install pykalman')
                    self.para_active_kf = False

    def registerEvent(self, event_type, cb_func):
        """注册事件回调函数"""
        self.cb_dict.update({event_type: cb_func})
        if event_type == self.CB_ON_PERIOD:
            self.cb_on_period = cb_func

    def init_param_list(self):
        self.paramList.append('bar_interval')
        self.paramList.append('interval')
        self.paramList.append('mode')

        self.paramList.append('para_pre_len')
        self.paramList.append('para_ma1_len')
        self.paramList.append('para_ma2_len')
        self.paramList.append('para_ma3_len')

        self.paramList.append('para_ema1_len')
        self.paramList.append('para_ema2_len')
        self.paramList.append('para_ema3_len')

        self.paramList.append('para_dmi_len')
        self.paramList.append('para_dmi_max')

        self.paramList.append('para_atr1_len')
        self.paramList.append('para_atr2_len')
        self.paramList.append('para_atr3_len')

        self.paramList.append('para_vol_len')

        self.paramList.append('para_rsi1_len')
        self.paramList.append('para_rsi2_len')

        self.paramList.append('para_cmi_len')

        self.paramList.append('para_boll_len')
        self.paramList.append('para_boll_tb_len')
        self.paramList.append('para_boll_std_rate')
        self.paramList.append('para_boll2_len')
        self.paramList.append('para_boll2_tb_len')
        self.paramList.append('para_boll2_std_rate')

        self.paramList.append('para_kdj_len')
        self.paramList.append('para_kdj_tb_len')
        self.paramList.append('para_kdj_slow_len')
        self.paramList.append('para_kdj_smooth_len')

        self.paramList.append('para_cci_len')

        self.paramList.append('para_macd_fast_len')
        self.paramList.append('para_macd_slow_len')
        self.paramList.append('para_macd_signal_len')

        self.paramList.append('para_active_kf')

        self.paramList.append('para_sar_step')
        self.paramList.append('para_sar_limit')

        self.paramList.append('para_active_skd')
        self.paramList.append('para_skd_fast_len')
        self.paramList.append('para_skd_slow_len')
        self.paramList.append('para_skd_low')
        self.paramList.append('para_skd_high')

        self.paramList.append('para_active_yb')
        self.paramList.append('para_yb_len')
        self.paramList.append('para_yb_ref')

        self.paramList.append('para_golden_n')

        self.paramList.append('para_active_area')

        self.paramList.append('para_bias_len')
        self.paramList.append('para_bias2_len')
        self.paramList.append('para_bias3_len')

        self.paramList.append('is_7x24')

        self.paramList.append('price_tick')
        self.paramList.append('underly_symbol')

        self.paramList.append('name')

    def init_properties(self):
        """
        初始化内部变量
        :return:
        """
        self.init_param_list()

        # 输入参数
        self.name = u'LineBar'
        self.mode = self.TICK_MODE  # 缺省为tick模式
        self.interval = Interval.SECOND  # 缺省为分钟级别周期
        self.bar_interval = 300  # 缺省为5分钟周期

        self.minute_interval = self.bar_interval / 60

    def __getstate__(self):
        """移除Pickle dump()时不支持的Attribute"""
        state = self.__dict__.copy()
        # Remove the unpicklable entries.
        remove_keys = ['strategy', 'cb_on_bar', 'cb_on_period']
        for key in self.__dict__.keys():
            if key in remove_keys:
                del state[key]
        return state

    def __setstate__(self, state):
        """Pickle load()"""
        self.__dict__.update(state)

    def restore(self, state):
        """从Pickle中恢复数据"""
        for key in state.__dict__.keys():
            self.__dict__[key] = state.__dict__[key]

    def init_indicators(self):
        """ 定义所有的指标数据"""

        # 指标参数
        self.para_pre_len = 0  # 20        # 前高前低的周期长度

        self.para_ma1_len = 0  # 10        # 第一根MA均线的周期长度
        self.para_ma2_len = 0  # 20        # 第二根MA均线的周期长度
        self.para_ma3_len = 0  # 120       # 第三根MA均线的周期长度

        self.para_ema1_len = 0  # 13       # 第一根EMA均线的周期长度
        self.para_ema2_len = 0  # 21       # 第二根EMA均线的周期长度
        self.para_ema3_len = 0  # 120      # 第三根EMA均线的周期长度

        self.para_dmi_len = 0  # 14           # DMI的计算周期
        self.para_dmi_max = 0  # 30           # Dpi和Mdi的突破阈值

        self.para_atr1_len = 0  # 10           # ATR波动率的计算周期(近端）
        self.para_atr2_len = 0  # 26           # ATR波动率的计算周期（常用）
        self.para_atr3_len = 0  # 50           # ATR波动率的计算周期（远端）

        self.para_vol_len = 0  # 14           # 平均交易量的计算周期

        self.para_rsi1_len = 0  # 7     # RSI 相对强弱指数（快曲线）
        self.para_rsi2_len = 0  # 14    # RSI 相对强弱指数（慢曲线）

        self.para_cmi_len = 0  # 计算CMI强度的周期

        self.para_boll_len = 0  # 布林的计算K线周期
        self.para_boll_tb_len = 0  # 布林的计算K线周期( 适用于TB的计算方式）
        self.para_boll_std_rate = 2  # 布林标准差（缺省2倍）

        self.para_boll2_len = 0  # 第二条布林的计算K线周期
        self.para_boll2_tb_len = 0  # 第二跳布林的计算K线周期( 适用于TB的计算方式）
        self.para_boll2_std_sate = 2  # 第二条布林标准差（缺省2倍）

        self.para_kdj_len = 0  # KDJ指标的长度,缺省是9
        self.para_kdj_tb_len = 0  # KDJ指标的长度,缺省是9 ( for TB)
        self.para_kdj_slow_len = 3  # KDJ K值平滑指标
        self.para_kdj_smooth_len = 3  # KDJ D值平滑指标

        self.para_cci_len = 0  # 计算CCI的K线周期

        self.para_macd_fast_len = 0  # 计算MACD的K线周期
        self.para_macd_slow_len = 0  # 慢线周期
        self.para_macd_signal_len = 0  # 平滑周期

        self.para_active_kf = False  # 是否激活卡尔曼均线计算

        self.para_sar_step = 0  # 抛物线的参数
        self.para_sar_limit = 0  # 抛物线参数

        self.para_active_skd = False  # 是否激活摆动指标
        self.para_skd_fast_len = 13  # 摆动指标快线周期1
        self.para_skd_slow_len = 8  # 摆动指标慢线周期2
        self.para_skd_low = 30  # 摆动指标下限区域
        self.para_skd_high = 70  # 摆动指标上限区域

        self.para_active_yb = False  # 是否激活多空趋势线
        self.para_yb_ref = 1  # 趋势线参照周期
        self.para_yb_len = 10  # 趋势线观测周期

        self.para_golden_n = 0  # 黄金分割的观测周期（一般设置为60，或120）

        self.para_active_area = False  # 是否激活区域划分

        self.para_bias_len = 0  # 乖离率观测周期1
        self.para_bias2_len = 0  # 乖离率观测周期2
        self.para_bias3_len = 0  # 乖离率观测周期3

        # K 线的相关计算结果数据
        self.line_pre_high = []  # K线的前para_pre_len的的最高
        self.line_pre_low = []  # K线的前para_pre_len的的最低

        self.line_ma1 = []  # K线的MA(para_ma1_len)均线，不包含未走完的bar
        self.line_ma2 = []  # K线的MA(para_ma2_len)均线，不包含未走完的bar
        self.line_ma3 = []  # K线的MA(para_ma3_len)均线，不包含未走完的bar
        self._rt_ma1 = None  # K线的实时MA(para_ma1_len)
        self._rt_ma2 = None  # K线的实时MA(para_ma2_len)
        self._rt_ma3 = None  # K线的实时MA(para_ma3_len)
        self.line_ma1_atan = []  # K线的MA(para_ma2_len)均线斜率
        self.line_ma2_atan = []  # K线的MA(para_ma2_len)均线斜率
        self.line_ma3_atan = []  # K线的MA(para_ma2_len)均线斜率
        self._rt_ma1_atan = None
        self._rt_ma2_atan = None
        self._rt_ma3_atan = None

        self.ma12_count = 0  # ma1 与 ma2 ,金叉/死叉后第几根bar
        self.ma13_count = 0  # ma1 与 ma3 ,金叉/死叉后第几根bar
        self.ma23_count = 0  # ma2 与 ma3 ,金叉/死叉后第几根bar

        self.line_ema1 = []  # K线的EMA1均线，周期是InputEmaLen1，不包含当前bar
        self.line_ema2 = []  # K线的EMA2均线，周期是InputEmaLen2，不包含当前bar
        self.line_ema3 = []  # K线的EMA3均线，周期是InputEmaLen3，不包含当前bar

        self._rt_ema1 = None  # K线的实时EMA(para_ema1_len)
        self._rt_ema2 = None  # K线的实时EMA(para_ema2_len)
        self._rt_ema3 = None  # K线的实时EMA(para_ema3_len)

        # K线的DMI( Pdi，Mdi，ADX，Adxr) 计算数据
        self.cur_pdi = 0  # bar内的升动向指标，即做多的比率
        self.cur_mdi = 0  # bar内的下降动向指标，即做空的比率

        self.line_pdi = []  # 升动向指标，即做多的比率
        self.line_mdi = []  # 下降动向指标，即做空的比率

        self.line_dx = []  # 趋向指标列表，最大长度为inputM*2
        self.cur_adx = 0  # Bar内计算的平均趋向指标
        self.line_adx = []  # 平均趋向指标
        self.cur_adxr = 0  # 趋向平均值，为当日ADX值与M日前的ADX值的均值
        self.line_adxr = []  # 平均趋向变化指标

        # K线的基于DMI、ADX计算的结果
        self.cur_adx_trend = 0  # ADX值持续高于前一周期时，市场行情将维持原趋势
        self.cur_adxr_trend = 0  # ADXR值持续高于前一周期时,波动率比上一周期高

        self.signal_adx_long = False  # 多过滤器条件,做多趋势的判断，ADX高于前一天，上升动向> inputMM
        self.signal_adx_short = False  # 空过滤器条件,做空趋势的判断，ADXR高于前一天，下降动向> inputMM

        # K线的ATR技术数据
        self.line_atr1 = []  # K线的ATR1,周期为inputAtr1Len
        self.line_atr2 = []  # K线的ATR2,周期为inputAtr2Len
        self.line_atr3 = []  # K线的ATR3,周期为inputAtr3Len

        self.cur_atr1 = 0
        self.cur_atr2 = 0
        self.cur_atr3 = 0

        # K线的交易量平均
        self.line_vol_ma = []  # K 线的交易量平均

        # K线的RSI计算数据
        self.line_rsi1 = []  # 记录K线对应的RSI数值，只保留inputRsi1Len*8
        self.line_rsi2 = []  # 记录K线对应的RSI数值，只保留inputRsi2Len*8
        self.para_rsi_low = 30  # RSI的最低线
        self.para_rsi_high = 70  # RSI的最高线
        self.rsi_top_list = []  # 记录RSI的最高峰，只保留 inputRsiLen个
        self.rsi_buttom_list = []  # 记录RSI的最低谷，只保留 inputRsiLen个
        self.cur_rsi_top_buttom = {}  # 最近的一个波峰/波谷

        # K线的CMI计算数据
        self.line_cmi = []  # 记录K线对应的Cmi数值，只保留inputCmiLen*8

        # K线的布林特计算数据
        self.line_boll_upper = []  # 上轨
        self.line_boll_middle = []  # 中线
        self.line_boll_lower = []  # 下轨
        self.line_boll_std = []  # 标准差
        self.line_upper_atan = []
        self.line_middle_atan = []
        self.line_lower_atan = []
        self._rt_upper = 0
        self._rt_middle = 0
        self._rt_lower = 0
        self._rt_upper_atan = 0
        self._rt_middle_atan = 0
        self._rt_lower_atan = 0

        self.cur_upper = 0  # 最后一根K的Boll上轨数值（与MinDiff取整）
        self.cur_middle = 0  # 最后一根K的Boll中轨数值（与MinDiff取整）
        self.cur_lower = 0  # 最后一根K的Boll下轨数值（与MinDiff取整+1）

        self.line_boll2_upper = []  # 上轨
        self.line_boll2_middle = []  # 中线
        self.line_boll2_lower = []  # 下轨
        self.line_boll2_std = []  # 标准差
        self.line_upper2_atan = []
        self.line_middle2_atan = []
        self.line_lower2_atan = []
        self._rt_upper2 = None
        self._rt_middle2 = None
        self._rt_lower2 = None
        self._rt_upper2_atan = None
        self._rt_middle2_atan = None
        self._rt_lower2_atan = None

        self.cur_upper2 = 0  # 最后一根K的Boll2上轨数值（与MinDiff取整）
        self.cur_middle2 = 0  # 最后一根K的Boll2中轨数值（与MinDiff取整）
        self.cur_lower2 = 0  # 最后一根K的Boll2下轨数值（与MinDiff取整+1）

        # K线的KDJ指标计算数据
        self.line_k = []  # K为快速指标
        self.line_d = []  # D为慢速指标
        self.line_j = []  #
        self.kdj_top_list = []  # 记录KDJ最高峰，只保留 inputKdjLen个
        self.kdj_buttom_list = []  # 记录KDJ的最低谷，只保留 inputKdjLen个
        self.line_rsv = []  # RSV
        self.cur_kdj_top_buttom = {}  # 最近的一个波峰/波谷
        self.cur_k = 0  # bar内计算时，最后一个未关闭的bar的实时K值
        self.cur_d = 0  # bar内计算时，最后一个未关闭的bar的实时值
        self.cur_j = 0  # bar内计算时，最后一个未关闭的bar的实时J值

        self.cur_kd_count = 0  # > 0, 金叉， < 0 死叉
        self.cur_kd_cross = 0  # 最近一次金叉/死叉的点位
        self.cur_kd_cross_price = 0  # 最近一次发生金叉/死叉的价格

        # K线的MACD计算数据(26,12,9)
        self.line_dif = []  # DIF = EMA12 - EMA26，即为talib-MACD返回值macd
        self.line_dea = []  # DEA = （前一日DEA X 8/10 + 今日DIF X 2/10），即为talib-MACD返回值
        self.line_macd = []  # (dif-dea)*2，但是talib中MACD的计算是bar = (dif-dea)*1,国内一般是乘以2
        self.macd_segment_list = []  # macd 金叉/死叉的段列表，记录价格的最高/最低，Dif的最高，最低，Macd的最高/最低，Macd面接
        self._rt_dif = None
        self._rt_dea = None
        self._rt_macd = None
        self.cur_macd_count = 0  # macd 金叉/死叉
        self.cur_macd_cross = 0  # 最近一次金叉/死叉的点位
        self.cur_macd_cross_price = 0  # 最近一次发生金叉/死叉的价格
        self.rt_macd_count = 0  # 实时金叉/死叉, default = 0； -1 实时死叉； 1：实时金叉
        self.rt_macd_cross = 0  # 实时金叉/死叉的位置
        self.rt_macd_cross_price = 0  # 发生实时金叉死叉时的价格
        self.dif_top_divergence = False  # mcad dif 与price 顶背离
        self.dif_buttom_divergence = False  # mcad dif 与price 底背离
        self.macd_top_divergence = False  # mcad 面积 与price 顶背离
        self.macd_buttom_divergence = False  # mcad 面积 与price 底背离

        # K 线的CCI计算数据
        self.line_cci = []

        # 卡尔曼过滤器
        self.kf = None
        self.line_state_mean = []  # 卡尔曼均线
        self.line_state_covar = []  # 方差

        # SAR 抛物线
        self.cur_sar_direction = ''  # up/down
        self.line_sar = []
        self.line_sar_top = []
        self.line_sar_buttom = []
        self.line_sar_sr_up = []
        self.line_sar_ep_up = []
        self.line_sar_af_up = []
        self.line_sar_sr_down = []
        self.line_sar_ep_down = []
        self.line_sar_af_down = []
        self.cur_sar_count = 0  # SAR 上升下降变化后累加

        # 周期
        self.cur_atan = None
        self.line_atan = []
        self.cur_period = None  # 当前所在周期
        self.period_list = []

        # 优化的多空动量线
        self.line_skd_rsi = []  # 参照的RSI
        self.line_skd_sto = []  # 根据RSI演算的STO
        self.line_sk = []  # 快线
        self.line_sd = []  # 慢线
        self.cur_skd_count = 0  # 当前金叉/死叉后累加
        self._rt_sk = None  # 实时SK值
        self._rt_sd = None  # 实时SD值
        self.cur_skd_divergence = 0  # 背离，>0,底背离， < 0 顶背离
        self.skd_top_list = []  # SK 高位
        self.skd_buttom_list = []  # SK 低位
        self.cur_skd_cross = 0  # 最近一次金叉/死叉的点位
        self.cur_skd_cross_price = 0  # 最近一次发生金叉/死叉的价格
        self.rt_skd_count = 0  # 实时金叉/死叉, default = 0； -1 实时死叉； 1：实时金叉
        self.rt_skd_cross = 0  # 实时金叉/死叉的位置
        self.rt_skd_cross_price = 0  # 发生实时金叉死叉时的价格

        # 多空趋势线
        self.line_yb = []
        self.cur_yb_count = 0  # 当前黄/蓝累加
        self._rt_yb = None

        # 黄金分割
        self.cur_p192 = None  # HH-(HH-LL) * 0.192;
        self.cur_p382 = None  # HH-(HH-LL) * 0.382;
        self.cur_p500 = None  # (HH+LL)/2;
        self.cur_p618 = None  # HH-(HH-LL) * 0.618;
        self.cur_p809 = None  # HH-(HH-LL) * 0.809;

        # 智能划分区域
        self.area_list = []
        self.cur_area = None
        self.pre_area = None

        # BIAS
        self.line_bias = []  # BIAS1
        self.line_bias2 = []  # BIAS2
        self.line_bias3 = []  # BIAS3
        self.cur_bias = 0  # 最后一个bar的BIAS1值
        self.cur_bias2 = 0  # 最后一个bar的BIAS2值
        self.cur_bias3 = 0  # 最后一个bar的BIAS3值
        self._rt_bias = None
        self._rt_bias2 = None
        self._rt_bias3 = None

    def set_params(self, setting: dict = {}):
        """设置参数"""
        d = self.__dict__
        for key in self.paramList:
            if key in setting:
                d[key] = setting[key]

    def set_mode(self, mode: str):
        """Tick/Bar模式"""
        self.mode = mode

    def on_tick(self, tick: TickData):
        """行情更新
        :type tick: object
        """
        # Tick 有效性检查
        if not self.is_7x24 and (tick.datetime.hour == 8 or tick.datetime.hour == 20):
            self.write_log(u'竞价排名tick时间:{0}'.format(tick.datetime))
            return
        self.cur_datetime = tick.datetime

        self.cur_tick = copy.copy(tick)

        # 兼容 标准套利合约，它没有last_price
        if self.cur_tick.last_price is None or self.cur_tick.last_price == 0:
            if self.cur_tick.ask_price_1 == 0 and self.cur_tick.bid_price_1 == 0:
                return

            self.cur_price = round_to((self.cur_tick.ask_price_1 + self.cur_tick.bid_price_1) / 2, self.price_tick)
            self.cur_tick.last_price = self.cur_price
        else:
            self.cur_price = self.cur_tick.last_price

        # 3.生成x K线，若形成新Bar，则触发OnBar事件
        self.generate_bar(copy.copy(self.cur_tick))

        # 更新curPeriod的High，low
        if self.cur_period is not None:
            self.cur_period.onPrice(self.cur_tick.last_price)

    def add_bar(self, bar: BarData, bar_is_completed: bool = False, bar_freq: int = 1):
        """
        予以外部初始化程序增加bar
        予以外部初始化程序增加bar
        :param bar:
        :param bar_is_completed: 插入的bar，其周期与K线周期一致，就设为True
        :param bar_freq: 插入的bar，其分钟周期数
        :return:
        """
        self.bar_len = len(self.line_bar)

        # 更新最后价格
        self.cur_price = bar.close_price
        self.cur_datetime = bar.datetime + timedelta(minutes=bar_freq)

        if self.bar_len == 0:
            new_bar = copy.deepcopy(bar)
            self.line_bar.append(new_bar)
            self.cur_trading_day = bar.trading_day
            self.on_bar(bar)
            return

        # 与最后一个BAR的时间比对，判断是否超过K线的周期
        lastBar = self.line_bar[-1]
        self.cur_trading_day = bar.trading_day

        is_new_bar = False
        if bar_is_completed:
            is_new_bar = True

        if self.interval == Interval.SECOND:
            if (bar.datetime - lastBar.datetime).seconds >= self.bar_interval:
                is_new_bar = True
        elif self.interval == Interval.MINUTE:
            bar_today_time = bar.datetime.replace(hour=0, minute=0, second=0, microsecond=0)
            cur_bar_minute = int((bar.datetime - bar_today_time).total_seconds() / 60 / self.bar_interval)
            last_bar_today_time = lastBar.datetime.replace(hour=0, minute=0, second=0, microsecond=0)
            last_bar_minute = int((lastBar.datetime - last_bar_today_time).total_seconds() / 60 / self.bar_interval)
            if cur_bar_minute != last_bar_minute:
                is_new_bar = True

        elif self.interval == Interval.HOUR:
            if self.bar_interval == 1 and bar.datetime.hour != lastBar.datetime.hour:
                is_new_bar = True
            elif self.bar_interval == 2 and bar.datetime.hour != lastBar.datetime.hour \
                    and bar.datetime.hour in {1, 9, 11, 13, 15, 21, 23}:
                is_new_bar = True
            elif self.bar_interval == 4 and bar.datetime.hour != lastBar.datetime.hour \
                    and bar.datetime.hour in {1, 9, 13, 21}:
                is_new_bar = True
            else:
                cur_bars_in_day = int(bar.datetime.hour / self.bar_interval)
                last_bars_in_day = int(lastBar.datetime.hour / self.bar_interval)
                if cur_bars_in_day != last_bars_in_day:
                    is_new_bar = True

        elif self.interval == Interval.DAILY:
            if bar.trading_day != lastBar.trading_day:
                is_new_bar = True

        if is_new_bar:
            # 添加新的bar
            new_bar = copy.deepcopy(bar)
            self.line_bar.append(new_bar)
            # 将上一个Bar推送至OnBar事件
            self.on_bar(lastBar)

        else:
            # 更新最后一个bar
            # 此段代码，针对一部分短周期生成长周期的k线更新，如3根5分钟k线，合并成1根15分钟k线。
            lastBar.close_price = bar.close_price
            lastBar.high_price = max(lastBar.high_price, bar.high_price)
            lastBar.low_price = min(lastBar.low_price, bar.low_price)
            lastBar.volume += bar.volume

            lastBar.open_interest = bar.open_interest

            # 实时计算
            self.rt_executed = False

    def on_bar(self, bar: BarData):
        """OnBar事件"""
        # 计算相关数据
        bar_mid3 = round((bar.close_price + bar.high_price + bar.low_price) / 3, self.round_n)
        bar_mid4 = round((2 * bar.close_price + bar.high_price + bar.low_price) / 4, self.round_n)
        bar_mid5 = round((2 * bar.close_price + bar.open_price + bar.high_price + bar.low_price) / 5, self.round_n)

        # 扩展open,close,high,low numpy array列表
        self.open_array[:-1] = self.open_array[1:]
        self.open_array[-1] = bar.open_price

        self.high_array[:-1] = self.high_array[1:]
        self.high_array[-1] = bar.high_price

        self.low_array[:-1] = self.low_array[1:]
        self.low_array[-1] = bar.low_price

        self.close_array[:-1] = self.close_array[1:]
        self.close_array[-1] = bar.close_price

        self.mid3_array[:-1] = self.mid3_array[1:]
        self.mid3_array[-1] = bar_mid3

        self.mid4_array[:-1] = self.mid4_array[1:]
        self.mid4_array[-1] = bar_mid4

        self.mid5_array[:-1] = self.mid5_array[1:]
        self.mid5_array[-1] = bar_mid5

        self.bar_len = len(self.line_bar)

        self.__count_pre_high_low()
        self.__count_ma()
        self.__count_ema()
        self.__count_dmi()
        self.__count_atr()
        self.__count_vol_ma()
        self.__count_rsi()
        self.__count_cmi()
        self.__count_kdj()
        self.__count_kdj_tb()
        self.__count_boll()
        self.__count_macd()
        self.__count_cci()
        self.__count_kf()
        self.__count_period(bar)
        self.__count_skd()
        self.__count_yb()
        self.__count_sar()
        self.__count_golden_section()
        self.__count_area(bar)
        self.__count_bias()
        self.export_to_csv(bar)

        self.rt_executed = False

        # 回调上层调用者
        if self.cb_on_bar:
            self.cb_on_bar(bar)

    def check_rt_funcs(self, func):
        """
        1.检查调用函数名是否在实时计算函数清单中，如果没有，则添加
        2. 如果当前tick/addbar之后，没有被执行过实时计算，就执行一次
        :param func:
        :return:
        """
        if func not in self.rt_funcs:
            self.write_log(u'{}添加{}到实时函数中'.format(self.name, str(func.__name__)))
            self.rt_funcs.add(func)

        self.run_rt_count()

    def run_rt_count(self):
        """
        根据实时计算得要求，执行实时指标计算
        :return:
        """
        if self.rt_executed:
            return

        for func in list(self.rt_funcs):
            try:
                func()
            except Exception as ex:
                print(u'{}调用实时计算,异常:{},{}'.format(self.name, str(ex), traceback.format_exc()), file=sys.stderr)

        self.rt_executed = True

    def export_to_csv(self, bar: BarData):
        """ 输出到csv文件"""
        if self.export_filename is None or len(self.export_fields) == 0:
            return
        field_names = []
        save_dict = {}
        for field in self.export_fields:
            field_name = field.get('name', None)
            attr_name = field.get('attr', None)
            source = field.get('source', None)
            type_ = field.get('type_', None)
            if field_name is None or attr_name is None or source is None or type_ is None:
                continue
            field_names.append(field_name)
            if source == 'bar':
                save_dict[field_name] = getattr(bar, str(attr_name), None)
            else:
                if type_ == 'list':
                    list_obj = getattr(self, str(attr_name), None)
                    if list_obj is None or len(list_obj) == 0:
                        save_dict[field_name] = 0
                    else:
                        save_dict[field_name] = list_obj[-1]
                else:
                    save_dict[field_name] = getattr(self, str(attr_name), 0)

        if len(save_dict) > 0:
            self.append_data(file_name=self.export_filename, dict_data=save_dict, field_names=field_names)

    def get_last_bar_str(self):
        """获取显示最后一个Bar的信息"""
        msg = u'[' + self.name + u']'

        if len(self.line_bar) < 2:
            return msg

        if self.mode == self.TICK_MODE:
            display_bar = self.line_bar[-2]
        else:
            display_bar = self.line_bar[-1]

        msg = msg + u'[td:{}] dt:{} o:{};h:{};l:{};c:{},v:{}'. \
            format(display_bar.trading_day, display_bar.datetime.strftime('%Y-%m-%d %H:%M:%S'), display_bar.open_price,
                   display_bar.high_price,
                   display_bar.low_price, display_bar.close_price, display_bar.volume)

        if self.para_ma1_len > 0 and len(self.line_ma1) > 0:
            msg = msg + u',MA({0}):{1}'.format(self.para_ma1_len, self.line_ma1[-1])

        if self.para_ma2_len > 0 and len(self.line_ma2) > 0:
            msg = msg + u',MA({0}):{1}'.format(self.para_ma2_len, self.line_ma2[-1])
            if self.ma12_count == 1:
                msg = msg + u'MA{}金叉MA{}'.format(self.para_ma1_len, self.para_ma2_len)
            elif self.ma12_count == -1:
                msg = msg + u'MA{}死叉MA{}'.format(self.para_ma1_len, self.para_ma2_len)

        if self.para_ma3_len > 0 and len(self.line_ma3) > 0:
            msg = msg + u',MA({0}):{1}'.format(self.para_ma3_len, self.line_ma3[-1])
            if self.ma13_count == 1:
                msg = msg + u'MA{}金叉MA{}'.format(self.para_ma1_len, self.para_ma3_len)
            elif self.ma13_count == -1:
                msg = msg + u'MA{}死叉MA{}'.format(self.para_ma1_len, self.para_ma3_len)

            if self.ma23_count == 1:
                msg = msg + u'MA{}金叉MA{}'.format(self.para_ma2_len, self.para_ma3_len)
            elif self.ma23_count == -1:
                msg = msg + u'MA{}死叉MA{}'.format(self.para_ma2_len, self.para_ma3_len)

        if self.para_ema1_len > 0 and len(self.line_ema1) > 0:
            msg = msg + u',EMA({0}):{1}'.format(self.para_ema1_len, self.line_ema1[-1])

        if self.para_ema2_len > 0 and len(self.line_ema2) > 0:
            msg = msg + u',EMA({0}):{1}'.format(self.para_ema2_len, self.line_ema2[-1])

        if self.para_ema3_len > 0 and len(self.line_ema3) > 0:
            msg = msg + u',EMA({0}):{1}'.format(self.para_ema3_len, self.line_ema3[-1])

        if self.para_dmi_len > 0 and len(self.line_pdi) > 0:
            msg = msg + u',Pdi:{1};Mdi:{1};Adx:{2}'.format(self.line_pdi[-1], self.line_mdi[-1], self.line_adx[-1])

        if self.para_atr1_len > 0 and len(self.line_atr1) > 0:
            msg = msg + u',Atr({0}):{1}'.format(self.para_atr1_len, self.line_atr1[-1])

        if self.para_atr2_len > 0 and len(self.line_atr2) > 0:
            msg = msg + u',Atr({0}):{1}'.format(self.para_atr2_len, self.line_atr2[-1])

        if self.para_atr3_len > 0 and len(self.line_atr3) > 0:
            msg = msg + u',Atr({0}):{1}'.format(self.para_atr3_len, self.line_atr3[-1])

        if self.para_vol_len > 0 and len(self.line_vol_ma) > 0:
            msg = msg + u',AvgVol({0}):{1}'.format(self.para_vol_len, self.line_vol_ma[-1])

        if self.para_rsi1_len > 0 and len(self.line_rsi1) > 0:
            msg = msg + u',Rsi({0}):{1}'.format(self.para_rsi1_len, self.line_rsi1[-1])

        if self.para_rsi2_len > 0 and len(self.line_rsi2) > 0:
            msg = msg + u',Rsi({0}):{1}'.format(self.para_rsi2_len, self.line_rsi2[-1])

        if self.para_kdj_len > 0 and len(self.line_k) > 0:
            msg = msg + u',KDJ({},{},{}):{},{},{}'.format(self.para_kdj_len,
                                                          self.para_kdj_slow_len,
                                                          self.para_kdj_smooth_len,
                                                          round(self.line_k[-1], self.round_n),
                                                          round(self.line_d[-1], self.round_n),
                                                          round(self.line_j[-1], self.round_n))

        if self.para_kdj_tb_len > 0 and len(self.line_k) > 0:
            msg = msg + u',KDJ_TB({},{},{}):{},K:{},D:{},J:{}'.format(self.para_kdj_tb_len,
                                                                      self.para_kdj_slow_len,
                                                                      self.para_kdj_smooth_len,
                                                                      round(self.line_rsv[-1], self.round_n),
                                                                      round(self.line_k[-1], self.round_n),
                                                                      round(self.line_d[-1], self.round_n),
                                                                      round(self.line_j[-1], self.round_n))

        if self.para_cci_len > 0 and len(self.line_cci) > 0:
            msg = msg + u',Cci({0}):{1}'.format(self.para_cci_len, self.line_cci[-1])

        if (self.para_boll_len > 0 or self.para_boll_tb_len > 0) and len(self.line_boll_upper) > 0:
            msg = msg + u',Boll({}):std:{},mid:{},up:{},low:{},Atan:[mid:{},up:{},low:{}]'. \
                format(self.para_boll_len, round(self.line_boll_std[-1], self.round_n),
                       round(self.line_boll_middle[-1], self.round_n),
                       round(self.line_boll_upper[-1], self.round_n),
                       round(self.line_boll_lower[-1], self.round_n),
                       round(self.line_middle_atan[-1], 2) if len(self.line_middle_atan) > 0 else 0,
                       round(self.line_upper_atan[-1], 2) if len(self.line_upper_atan) > 0 else 0,
                       round(self.line_lower_atan[-1], 2) if len(self.line_lower_atan) > 0 else 0)

        if (self.para_boll2_len > 0 or self.para_boll2_tb_len > 0) and len(self.line_boll_upper) > 0:
            msg = msg + u',Boll2({}):std:{},m:{},u:{},l:{}'. \
                format(self.para_boll2_len, round(self.line_boll_std[-1], self.round_n),
                       round(self.line_boll2_middle[-1], self.round_n),
                       round(self.line_boll2_upper[-1], self.round_n),
                       round(self.line_boll2_lower[-1], self.round_n))

        if self.para_macd_fast_len > 0 and len(self.line_dif) > 0:
            msg = msg + u',MACD({0},{1},{2}):Dif:{3},Dea{4},Macd:{5}'. \
                format(self.para_macd_fast_len, self.para_macd_slow_len, self.para_macd_signal_len,
                       round(self.line_dif[-1], self.round_n),
                       round(self.line_dea[-1], self.round_n),
                       round(self.line_macd[-1], self.round_n))
            if len(self.line_macd) > 2:
                if self.line_macd[-2] < 0 < self.line_macd[-1]:
                    msg = msg + u'金叉 '
                elif self.line_macd[-2] > 0 > self.line_macd[-1]:
                    msg = msg + u'死叉 '

                if self.dif_top_divergence:
                    msg = msg + u'Dif顶背离 '
                if self.macd_top_divergence:
                    msg = msg + u'MACD顶背离 '
                if self.dif_buttom_divergence:
                    msg = msg + u'Dif底背离 '
                if self.macd_buttom_divergence:
                    msg = msg + u'MACD底背离 '

        if self.para_active_kf and len(self.line_state_mean) > 0:
            msg = msg + u',Kalman:{0}'.format(self.line_state_mean[-1])

        if self.para_active_skd and len(self.line_sk) > 1 and len(self.line_sd) > 1:
            msg = msg + u',SK:{}/SD:{}{}{},count:{}' \
                .format(round(self.line_sk[-1], 2),
                        round(self.line_sd[-1], 2),
                        u'金叉' if self.cur_skd_count == 1 else u'',
                        u'死叉' if self.cur_skd_count == -1 else u'',
                        self.cur_skd_count)

            if self.cur_skd_divergence == 1:
                msg = msg + u'底背离'
            elif self.cur_skd_divergence == -1:
                msg = msg + u'顶背离'

        if self.para_active_yb and len(self.line_yb) > 1:
            c = 'Blue' if self.line_yb[-1] < self.line_yb[-2] else 'Yellow'
            msg = msg + u',YB:{},[{}({})]'.format(self.line_yb[-1], c, self.cur_yb_count)

        if self.para_sar_step > 0 and self.para_sar_limit > 0:
            if len(self.line_sar) > 1:
                msg = msg + u',Sar:{},{}(h={},l={}),#{}' \
                    .format(self.cur_sar_direction,
                            round(self.line_sar[-2], self.round_n),
                            self.line_sar_top[-1],
                            self.line_sar_buttom[-1],
                            self.cur_sar_count)
        if self.para_active_area:
            msg = msg + 'Area:{}'.format(self.cur_area)

        if self.para_bias_len > 0 and len(self.line_bias) > 0:
            msg = msg + u',Bias({}):{}]'. \
                format(self.para_bias_len, round(self.line_bias[-1], self.round_n))

        if self.para_bias2_len > 0 and len(self.line_bias2) > 0:
            msg = msg + u',Bias2({}):{}]'. \
                format(self.para_bias2_len, round(self.line_bias2[-1], self.round_n))

        if self.para_bias3_len > 0 and len(self.line_bias3) > 0:
            msg = msg + u',Bias3({}):{}]'. \
                format(self.para_bias3_len, round(self.line_bias3[-1], self.round_n))

        return msg

    def first_tick(self, tick: TickData):
        """ K线的第一个Tick数据"""

        self.cur_bar = BarData(
            gateway_name=tick.gateway_name,
            symbol=tick.symbol,
            exchange=tick.exchange,
            datetime=tick.datetime
        )  # 创建新的K线
        # 计算K线的整点分钟周期，这里周期最小是1分钟。如果你是采用非整点分钟，例如1.5分钟，请把这段注解掉
        if self.minute_interval and self.interval == Interval.SECOND:
            self.minute_interval = int(self.bar_interval / 60)
            if self.minute_interval < 1:
                self.minute_interval = 1
            fixedMin = int(tick.datetime.minute / self.minute_interval) * self.minute_interval
            tick.datetime = tick.datetime.replace(minute=fixedMin)

        self.cur_bar.vt_symbol = tick.vt_symbol
        self.cur_bar.symbol = tick.symbol
        self.cur_bar.exchange = tick.exchange
        self.cur_bar.open_interest = tick.open_interest

        self.cur_bar.open_price = tick.last_price  # O L H C
        self.cur_bar.high_price = tick.last_price
        self.cur_bar.low_price = tick.last_price
        self.cur_bar.close_price = tick.last_price

        self.cur_bar.mid4 = tick.last_price  # 4价均价
        self.cur_bar.mid5 = tick.last_price  # 5价均价

        # K线的日期时间
        self.cur_bar.trading_day = tick.trading_day  # K线所在的交易日期
        self.cur_bar.date = tick.date  # K线的日期，（夜盘的话，与交易日期不同哦）
        self.cur_bar.datetime = tick.datetime
        if (self.interval == Interval.SECOND and self.bar_interval % 60 == 0) \
                or self.interval in [Interval.MINUTE, Interval.HOUR, Interval.DAILY]:
            # K线的日期时间（去除秒）设为第一个Tick的时间
            self.cur_bar.datetime = self.cur_bar.datetime.replace(second=0, microsecond=0)
        self.cur_bar.time = self.cur_bar.datetime.strftime('%H:%M:%S')
        self.cur_bar.volume = tick.volume
        if self.cur_trading_day != self.cur_bar.trading_day or not self.line_bar:
            # bar的交易日与记录的当前交易日不一致：
            self.cur_trading_day = self.cur_bar.trading_day

        self.is_first_tick = True  # 标识该Tick属于该Bar的第一个tick数据

        self.line_bar.append(self.cur_bar)  # 推入到lineBar队列

    # ----------------------------------------------------------------------
    def generate_bar(self, tick: TickData):
        """生成 line Bar  """

        self.bar_len = len(self.line_bar)

        # 保存第一个K线数据
        if self.bar_len == 0:
            self.first_tick(tick)
            return

        # 清除480周期前的数据，
        if self.bar_len > self.max_hold_bars:
            del self.line_bar[0]

        # 与最后一个BAR的时间比对，判断是否超过5分钟
        lastBar = self.line_bar[-1]

        # 处理日内的间隔时段最后一个tick，如10:15分，11:30分，15:00 和 2:30分
        endtick = False
        if not self.is_7x24:
            if (tick.datetime.hour == 10 and tick.datetime.minute == 15) \
                    or (tick.datetime.hour == 11 and tick.datetime.minute == 30) \
                    or (tick.datetime.hour == 15 and tick.datetime.minute == 00) \
                    or (tick.datetime.hour == 2 and tick.datetime.minute == 30):
                endtick = True

            # 夜盘1:30收盘
            if self.underly_symbol in NIGHT_MARKET_SQ2 and tick.datetime.hour == 1 and tick.datetime.minute == 00:
                endtick = True

            # 夜盘23:00收盘
            if self.underly_symbol in NIGHT_MARKET_23 and tick.datetime.hour == 23 and tick.datetime.minute == 00:
                endtick = True

        # 满足时间要求
        # 1,秒周期，tick的时间，距离最后一个bar的开始时间，已经超出bar的时间周期（barTimeInterval）
        # 2，分钟周期，tick的时间属于的bar不等于最后一个bar的时间属于的bar
        # 3，小时周期，取整=0
        # 4、日周期，开盘时间
        # 5、不是最后一个结束tick
        is_new_bar = False

        if self.last_tick is None:  # Fix for Min10, 13:30 could not generate
            self.last_tick = tick

        # self.write_log('drawLineBar: datetime={}, lastPrice={}, endtick={}'.format(tick.datetime.strftime("%Y%m%d %H:%M:%S"), tick.last_price, endtick))
        if not endtick:
            if self.interval == Interval.SECOND:
                if (tick.datetime - lastBar.datetime).total_seconds() >= self.bar_interval:
                    is_new_bar = True

            elif self.interval == Interval.MINUTE:
                # 时间到达整点分钟数，例如5分钟的 0,5,15,20,,.与上一个tick的分钟数不是同一分钟
                cur_bars_in_day = int(((tick.datetime - datetime.strptime(tick.datetime.strftime('%Y-%m-%d'),
                                                                          '%Y-%m-%d')).total_seconds() / 60 / self.bar_interval))
                last_bars_in_day = int(((lastBar.datetime - datetime.strptime(lastBar.datetime.strftime('%Y-%m-%d'),
                                                                              '%Y-%m-%d')).total_seconds() / 60 / self.bar_interval))

                if cur_bars_in_day != last_bars_in_day:
                    is_new_bar = True

            elif self.interval == Interval.HOUR:
                if self.bar_interval == 1 and tick.datetime is not None and tick.datetime.hour != self.last_tick.datetime.hour:
                    is_new_bar = True

                elif not self.is_7x24 and self.bar_interval == 2 and tick.datetime is not None \
                        and tick.datetime.hour != self.last_tick.datetime.hour \
                        and tick.datetime.hour in {1, 9, 11, 13, 21, 23}:
                    is_new_bar = True

                elif not self.is_7x24 and self.bar_interval == 4 and tick.datetime is not None \
                        and tick.datetime.hour != self.last_tick.datetime.hour \
                        and tick.datetime.hour in {1, 9, 13, 21}:
                    is_new_bar = True
                else:
                    cur_bars_in_day = int(tick.datetime.hour / self.bar_interval)
                    last_bars_in_day = int(lastBar.datetime.hour / self.bar_interval)
                    if cur_bars_in_day != last_bars_in_day:
                        is_new_bar = True

            elif self.interval == Interval.DAILY:
                if not self.is_7x24:
                    if tick.datetime is not None \
                            and (tick.datetime.hour == 21 or tick.datetime.hour == 9) \
                            and 14 <= self.last_tick.datetime.hour <= 15:
                        is_new_bar = True
                else:
                    if tick.date != lastBar.date:
                        is_new_bar = True

        if is_new_bar:
            # 创建并推入新的Bar
            self.first_tick(tick)
            # 触发OnBar事件
            self.on_bar(lastBar)

        else:
            # 更新当前最后一个bar
            self.is_first_tick = False

            # 更新最高价、最低价、收盘价、成交量
            lastBar.high_price = max(lastBar.high_price, tick.last_price)
            lastBar.low_price = min(lastBar.low_price, tick.last_price)
            lastBar.close_price = tick.last_price
            lastBar.open_interest = tick.open_interest
            lastBar.volume += tick.volume

            # 更新Bar的颜色
            if lastBar.close_price > lastBar.open_price:
                lastBar.color = Color.RED
            elif lastBar.close_price < lastBar.open_price:
                lastBar.color = Color.BLUE
            else:
                lastBar.color = Color.EQUAL

            # 实时计算
            self.rt_executed = False

        if not endtick:
            self.last_tick = tick

    # ----------------------------------------------------------------------
    def __count_pre_high_low(self):
        """计算 K线的前周期最高和最低"""

        if self.para_pre_len <= 0:  # 不计算
            return
        count_len = min(self.para_pre_len, self.bar_len)

        # 2.计算前inputPreLen周期内(不包含当前周期）的Bar高点和低点
        preHigh = max(self.high_array[-count_len:])
        preLow = min(self.low_array[-count_len:])

        # 保存
        if len(self.line_pre_high) > self.max_hold_bars:
            del self.line_pre_high[0]
        self.line_pre_high.append(preHigh)

        # 保存
        if len(self.line_pre_low) > self.max_hold_bars:
            del self.line_pre_low[0]
        self.line_pre_low.append(preLow)

    # ----------------------------------------------------------------------
    def __count_sar(self):
        """计算K线的SAR"""

        if self.bar_len < 5:
            return

        if not (self.para_sar_step > 0 or self.para_sar_limit > self.para_sar_step):  # 不计算
            return

        if len(self.line_sar_sr_up) == 0 and len(self.line_sar_sr_down) == 0:
            if self.line_bar[-2].close > self.line_bar[-5].close:
                # 标记为上涨趋势
                sr0 = min(self.low_array[0:])
                af0 = 0
                ep0 = self.high_array[-1]
                self.line_sar_sr_up.append(sr0)
                self.line_sar_ep_up.append(ep0)
                self.line_sar_af_up.append(af0)
                self.line_sar.append(sr0)
                self.cur_sar_direction = 'up'
                self.cur_sar_count = 0
            else:
                # 标记为下跌趋势
                sr0 = max(self.high_array[0:])
                af0 = 0
                ep0 = self.low_array[-1]
                self.line_sar_sr_down.append(sr0)
                self.line_sar_ep_down.append(ep0)
                self.line_sar_af_down.append(af0)
                self.line_sar.append(sr0)
                self.cur_sar_direction = 'down'
                self.cur_sar_count = 0
            self.line_sar_top.append(self.line_bar[-2].high)  # SAR的谷顶
            self.line_sar_buttom.append(self.line_bar[-2].low)  # SAR的波底
        elif len(self.line_sar_sr_up) > 0:
            if self.low_array[-1] > self.line_sar_sr_up[-1]:
                sr0 = self.line_sar_sr_up[-1]
                ep0 = self.high_array[-1]  # 文华使用前一个K线的最高价
                af0 = min(self.para_sar_limit,
                          self.line_sar_af_up[-1] + self.para_sar_step)  # 文华的af随着K线的数目增加而递增，没有判断新高
                sr = sr0 + af0 * (ep0 - sr0)
                self.line_sar_sr_up.append(sr)
                self.line_sar_ep_up.append(ep0)
                self.line_sar_af_up.append(af0)
                self.line_sar.append(sr)
                self.cur_sar_count += 1
                # self.write_log('Up: sr0={},ep0={},af0={},sr={}'.format(sr0, ep0, af0, sr))
            elif self.low_array[-1] <= self.line_sar_sr_up[-1]:
                ep0 = max(self.high_array[-len(self.line_sar_sr_up):])
                sr0 = ep0
                af0 = 0
                self.line_sar_sr_down.append(sr0)
                self.line_sar_ep_down.append(ep0)
                self.line_sar_af_down.append(af0)
                self.line_sar.append(sr0)
                self.cur_sar_direction = 'down'
                # self.write_log('Up->Down: sr0={},ep0={},af0={},sr={}'.format(sr0, ep0, af0, sr0))
                # self.write_log('lineSarTop={}, lineSarButtom={}, len={}'.format(self.lineSarTop[-1], self.lineSarButtom[-1],len(self.lineSarSrUp)))
                self.line_sar_top.append(self.line_bar[-2].high)
                self.line_sar_buttom.append(self.line_bar[-2].low)
                self.line_sar_sr_up = []
                self.line_sar_ep_up = []
                self.line_sar_af_up = []
                sr0 = self.line_sar_sr_down[-1]
                ep0 = self.low_array[-1]  # 文华使用前一个K线的最低价
                af0 = min(self.para_sar_limit,
                          self.line_sar_af_down[-1] + self.para_sar_step)  # 文华的af随着K线的数目增加而递增，没有判断新高
                sr = sr0 + af0 * (ep0 - sr0)
                self.line_sar_sr_down.append(sr)
                self.line_sar_ep_down.append(ep0)
                self.line_sar_af_down.append(af0)
                self.line_sar.append(sr)
                self.cur_sar_count = 0
                # self.write_log('Down: sr0={},ep0={},af0={},sr={}'.format(sr0, ep0, af0, sr))
        elif len(self.line_sar_sr_down) > 0:
            if self.high_array[-1] < self.line_sar_sr_down[-1]:
                sr0 = self.line_sar_sr_down[-1]
                ep0 = self.low_array[-1]  # 文华使用前一个K线的最低价
                af0 = min(self.para_sar_limit,
                          self.line_sar_af_down[-1] + self.para_sar_step)  # 文华的af随着K线的数目增加而递增，没有判断新高
                sr = sr0 + af0 * (ep0 - sr0)
                self.line_sar_sr_down.append(sr)
                self.line_sar_ep_down.append(ep0)
                self.line_sar_af_down.append(af0)
                self.line_sar.append(sr)
                self.cur_sar_count -= 1
                # self.write_log('Down: sr0={},ep0={},af0={},sr={}'.format(sr0, ep0, af0, sr))
            elif self.high_array[-1] >= self.line_sar_sr_down[-1]:
                ep0 = min(self.low_array[-len(self.line_sar_sr_down):])
                sr0 = ep0
                af0 = 0
                self.line_sar_sr_up.append(sr0)
                self.line_sar_ep_up.append(ep0)
                self.line_sar_af_up.append(af0)
                self.line_sar.append(sr0)
                self.cur_sar_direction = 'up'
                # self.write_log('Down->Up: sr0={},ep0={},af0={},sr={}'.format(sr0, ep0, af0, sr0))
                # self.write_log('lineSarTop={}, lineSarButtom={}, len={}'.format(self.lineSarTop[-1], self.lineSarButtom[-1],len(self.lineSarSrDown)))
                self.line_sar_top.append(self.line_bar[-2].high)
                self.line_sar_buttom.append(self.line_bar[-2].low)
                self.line_sar_sr_down = []
                self.line_sar_ep_down = []
                self.line_sar_af_down = []
                sr0 = self.line_sar_sr_up[-1]
                ep0 = self.high_array[-1]  # 文华使用前一个K线的最高价
                af0 = min(self.para_sar_limit,
                          self.line_sar_af_up[-1] + self.para_sar_step)  # 文华的af随着K线的数目增加而递增，没有判断新高
                sr = sr0 + af0 * (ep0 - sr0)
                self.line_sar_sr_up.append(sr)
                self.line_sar_ep_up.append(ep0)
                self.line_sar_af_up.append(af0)
                self.line_sar.append(sr)
                self.cur_sar_count = 0
                self.write_log('Up: sr0={},ep0={},af0={},sr={}'.format(sr0, ep0, af0, sr))

        # 更新抛物线的最高值和最低值
        if self.line_sar_top[-1] < self.high_array[-1]:
            self.line_sar_top[-1] = self.high_array[-1]
        if self.line_sar_buttom[-1] > self.low_array[-1]:
            self.line_sar_buttom[-1] = self.low_array[-1]

        if len(self.line_sar) > self.max_hold_bars:
            del self.line_sar[0]

    # ----------------------------------------------------------------------
    def __count_ma(self):
        """计算K线的MA1 和MA2"""

        if not (self.para_ma1_len > 0 or self.para_ma2_len > 0 or self.para_ma3_len > 0):  # 不计算
            return

        # 1、lineBar满足长度才执行计算
        if self.bar_len < min(7, self.para_ma1_len, self.para_ma2_len, self.para_ma3_len) + 2:
            self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算MA需要：{1}'.
                           format(self.bar_len,
                                  min(7, self.para_ma1_len, self.para_ma2_len, self.para_ma3_len) + 2))
            return

        # 计算第一条MA均线
        if self.para_ma1_len > 0:
            count_len = min(self.para_ma1_len, self.bar_len)

            barMa1 = ta.MA(self.close_array[-count_len:], count_len)[-1]
            barMa1 = round(float(barMa1), self.round_n)

            if len(self.line_ma1) > self.max_hold_bars:
                del self.line_ma1[0]
            self.line_ma1.append(barMa1)

            # 计算斜率
            if len(self.line_ma1) > 2 and self.line_ma1[-2] != 0:
                ma1_atan = math.atan((self.line_ma1[-1] / self.line_ma1[-2] - 1) * 100) * 180 / math.pi
                ma1_atan = round(ma1_atan, 3)
                if len(self.line_ma1_atan) > self.max_hold_bars:
                    del self.line_ma1_atan[0]
                self.line_ma1_atan.append(ma1_atan)

        # 计算第二条MA均线
        if self.para_ma2_len > 0:
            count_len = min(self.para_ma2_len, self.bar_len)
            barMa2 = ta.MA(self.close_array[-count_len:], count_len)[-1]
            barMa2 = round(float(barMa2), self.round_n)

            if len(self.line_ma2) > self.max_hold_bars:
                del self.line_ma2[0]
            self.line_ma2.append(barMa2)

            # 计算斜率
            if len(self.line_ma2) > 2 and self.line_ma2[-2] != 0:
                ma2_atan = math.atan((self.line_ma2[-1] / self.line_ma2[-2] - 1) * 100) * 180 / math.pi
                ma2_atan = round(ma2_atan, 3)
                if len(self.line_ma2_atan) > self.max_hold_bars:
                    del self.line_ma2_atan[0]
                self.line_ma2_atan.append(ma2_atan)

        # 计算第三条MA均线
        if self.para_ma3_len > 0:
            count_len = min(self.para_ma3_len, self.bar_len)
            barMa3 = ta.MA(self.close_array[-count_len:], count_len)[-1]
            barMa3 = round(float(barMa3), self.round_n)

            if len(self.line_ma3) > self.max_hold_bars:
                del self.line_ma3[0]
            self.line_ma3.append(barMa3)

            # 计算斜率
            if len(self.line_ma3) > 2 and self.line_ma3[-2] != 0:
                ma3_atan = math.atan((self.line_ma3[-1] / self.line_ma3[-2] - 1) * 100) * 180 / math.pi
                ma3_atan = round(ma3_atan, 3)
                if len(self.line_ma3_atan) > self.max_hold_bars:
                    del self.line_ma3_atan[0]
                self.line_ma3_atan.append(ma3_atan)

        # 计算MA1，MA2，MA3的金叉死叉
        if len(self.line_ma1) >= 2 and len(self.line_ma2) > 2:
            golden_cross = False
            dead_cross = False

            if self.line_ma1[-1] > self.line_ma1[-2] \
                    and self.line_ma1[-1] > self.line_ma2[-1] \
                    and self.line_ma1[-2] <= self.line_ma2[-2]:
                golden_cross = True

            if self.line_ma1[-1] < self.line_ma1[-2] \
                    and self.line_ma1[-1] < self.line_ma2[-1] \
                    and self.line_ma1[-2] >= self.line_ma2[-2]:
                dead_cross = True

            if self.ma12_count <= 0:
                if golden_cross:
                    self.ma12_count = 1
                elif self.line_ma1[-1] < self.line_ma2[-1]:
                    self.ma12_count -= 1

            elif self.ma12_count >= 0:
                if dead_cross:
                    self.ma12_count = -1
                elif self.line_ma1[-1] > self.line_ma2[-1]:
                    self.ma12_count += 1

        if len(self.line_ma2) >= 2 and len(self.line_ma3) > 2:
            golden_cross = False
            dead_cross = False
            if self.line_ma2[-1] > self.line_ma2[-2] \
                    and self.line_ma2[-1] > self.line_ma3[-1] \
                    and self.line_ma2[-2] <= self.line_ma3[-2]:
                golden_cross = True

            if self.line_ma2[-1] < self.line_ma2[-2] \
                    and self.line_ma2[-1] < self.line_ma3[-1] \
                    and self.line_ma2[-2] >= self.line_ma3[-2]:
                dead_cross = True

            if self.ma23_count <= 0:
                if golden_cross:
                    self.ma23_count = 1
                elif self.line_ma2[-1] < self.line_ma3[-1]:
                    self.ma23_count -= 1

            elif self.ma23_count >= 0:
                if dead_cross:
                    self.ma23_count = -1
                elif self.line_ma2[-1] > self.line_ma3[-1]:
                    self.ma23_count += 1

        if len(self.line_ma1) >= 2 and len(self.line_ma3) > 2:
            golden_cross = False
            dead_cross = False
            if self.line_ma1[-1] > self.line_ma1[-2] \
                    and self.line_ma1[-1] > self.line_ma3[-1] \
                    and self.line_ma1[-2] <= self.line_ma3[-2]:
                golden_cross = True

            if self.line_ma1[-1] < self.line_ma1[-2] \
                    and self.line_ma1[-1] < self.line_ma3[-1] \
                    and self.line_ma1[-2] >= self.line_ma3[-2]:
                dead_cross = True

            if self.ma13_count <= 0:
                if golden_cross:
                    self.ma13_count = 1
                elif self.line_ma1[-1] < self.line_ma3[-1]:
                    self.ma13_count -= 1

            elif self.ma13_count >= 0:
                if dead_cross:
                    self.ma13_count = -1
                elif self.line_ma1[-1] > self.line_ma3[-1]:
                    self.ma13_count += 1

    def rt_count_ma(self):
        """
        实时计算MA得值
        :param ma_num:第几条均线, 1，对应inputMa1Len,,,,
        :return:
        """
        if self.para_ma1_len > 0:
            count_len = min(self.bar_len, self.para_ma1_len)
            if count_len > 0:
                close_ma_array = ta.MA(np.append(self.close_array[-count_len:], [self.line_bar[-1].close_price]), count_len)
                self._rt_ma1 = round(float(close_ma_array[-1]), self.round_n)

                # 计算斜率
                if len(close_ma_array) > 2 and close_ma_array[-2] != 0:
                    self._rt_ma1_atan = round(
                        math.atan((close_ma_array[-1] / close_ma_array[-2] - 1) * 100) * 180 / math.pi, 3)

        if self.para_ma2_len > 0:
            count_len = min(self.bar_len, self.para_ma2_len)
            if count_len > 0:
                close_ma_array = ta.MA(np.append(self.close_array[-count_len:], [self.line_bar[-1].close_price]), count_len)
                self._rt_ma2 = round(float(close_ma_array[-1]), self.round_n)

                # 计算斜率
                if len(close_ma_array) > 2 and close_ma_array[-2] != 0:
                    self._rt_ma2_atan = round(
                        math.atan((close_ma_array[-1] / close_ma_array[-2] - 1) * 100) * 180 / math.pi, 3)

        if self.para_ma3_len > 0:
            count_len = min(self.bar_len, self.para_ma3_len)
            if count_len > 0:
                close_ma_array = ta.MA(np.append(self.close_array[-count_len:], [self.line_bar[-1].close_price]), count_len)
                self._rt_ma3 = round(float(close_ma_array[-1]), self.round_n)

                # 计算斜率
                if len(close_ma_array) > 2 and close_ma_array[-2] != 0:
                    self._rt_ma3_atan = round(
                        math.atan((close_ma_array[-1] / close_ma_array[-2] - 1) * 100) * 180 / math.pi, 3)

    @property
    def rt_ma1(self):
        self.check_rt_funcs(self.rt_count_ma)
        if self._rt_ma1 is None and len(self.line_ma1) > 0:
            return self.line_ma1[-1]
        return self._rt_ma1

    @property
    def rt_ma2(self):
        self.check_rt_funcs(self.rt_count_ma)
        if self._rt_ma2 is None and len(self.line_ma2) > 0:
            return self.line_ma2[-1]
        return self._rt_ma2

    @property
    def rt_ma3(self):
        self.check_rt_funcs(self.rt_count_ma)
        if self._rt_ma3 is None and len(self.line_ma3) > 0:
            return self.line_ma3[-1]
        return self._rt_ma3

    @property
    def rt_ma1_atan(self):
        self.check_rt_funcs(self.rt_count_ma)
        if self._rt_ma1_atan is None and len(self.line_ma1_atan) > 0:
            return self.line_ma1_atan[-1]
        return self._rt_ma1_atan

    @property
    def rt_ma2_atan(self):
        self.check_rt_funcs(self.rt_count_ma)
        if self._rt_ma2_atan is None and len(self.line_ma2_atan) > 0:
            return self.line_ma2_atan[-1]
        return self._rt_ma2_atan

    @property
    def rt_ma3_atan(self):
        self.check_rt_funcs(self.rt_count_ma)
        if self._rt_ma3_atan is None and len(self.line_ma3_atan) > 0:
            return self.line_ma3_atan[-1]
        return self._rt_ma3_atan

    # ----------------------------------------------------------------------
    def __count_ema(self):
        """计算K线的EMA1 和EMA2"""

        if not (self.para_ema1_len > 0 or self.para_ema2_len > 0 or self.para_ema3_len > 0):  # 不计算
            return

        ema1_data_len = min(self.para_ema1_len * 4, self.para_ema1_len + 40) if self.para_ema1_len > 0 else 0
        ema2_data_len = min(self.para_ema2_len * 4, self.para_ema2_len + 40) if self.para_ema2_len > 0 else 0
        ema3_data_len = min(self.para_ema3_len * 4, self.para_ema3_len + 40) if self.para_ema3_len > 0 else 0
        max_data_len = max(ema1_data_len, ema2_data_len, ema3_data_len)
        # 1、lineBar满足长度才执行计算
        if self.bar_len < max_data_len:
            self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算EMA需要：{1}'.
                           format(len(self.line_bar), max_data_len))
            return

        # 计算第一条EMA均线
        if self.para_ema1_len > 0:
            count_len = min(self.para_ema1_len, self.bar_len)

            # 3、获取前InputN周期(不包含当前周期）的K线
            barEma1 = ta.EMA(self.close_array[-ema1_data_len:], count_len)[-1]
            barEma1 = round(float(barEma1), self.round_n)

            if len(self.line_ema1) > self.max_hold_bars:
                del self.line_ema1[0]
            self.line_ema1.append(barEma1)

        # 计算第二条EMA均线
        if self.para_ema2_len > 0:
            count_len = min(self.bar_len, self.para_ema2_len)

            # 3、获取前InputN周期(不包含当前周期）的自适应均线

            barEma2 = ta.EMA(self.close_array[-ema2_data_len:], count_len)[-1]

            barEma2 = round(float(barEma2), self.round_n)

            if len(self.line_ema2) > self.max_hold_bars:
                del self.line_ema2[0]
            self.line_ema2.append(barEma2)

        # 计算第三条EMA均线
        if self.para_ema3_len > 0:
            count_len = min(self.bar_len, self.para_ema3_len)

            # 3、获取前InputN周期(不包含当前周期）的自适应均线
            barEma3 = ta.EMA(self.close_array[-ema3_data_len:], count_len)[-1]
            barEma3 = round(float(barEma3), self.round_n)

            if len(self.line_ema3) > self.max_hold_bars:
                del self.line_ema3[0]
            self.line_ema3.append(barEma3)

    # ----------------------------------------------------------------------
    def rt_count_ema(self):
        """计算K线的EMA1 和EMA2"""

        if not (self.para_ema1_len > 0 or self.para_ema2_len > 0 or self.para_ema3_len > 0):  # 不计算
            return

        ema1_data_len = min(self.para_ema1_len * 4, self.para_ema1_len + 40) if self.para_ema1_len > 0 else 0
        ema2_data_len = min(self.para_ema2_len * 4, self.para_ema2_len + 40) if self.para_ema2_len > 0 else 0
        ema3_data_len = min(self.para_ema3_len * 4, self.para_ema3_len + 40) if self.para_ema3_len > 0 else 0
        max_data_len = max(ema1_data_len, ema2_data_len, ema3_data_len)
        # 1、lineBar满足长度才执行计算
        if self.bar_len < max_data_len:
            return

        # 计算第一条EMA均线
        if self.para_ema1_len > 0:
            count_len = min(self.para_ema1_len, self.bar_len)

            # 3、获取前InputN周期(不包含当前周期）的K线
            barEma1 = ta.EMA(np.append(self.close_array[-ema1_data_len:], [self.cur_price]), count_len)[-1]
            self._rt_ema1 = round(float(barEma1), self.round_n)

        # 计算第二条EMA均线
        if self.para_ema2_len > 0:
            count_len = min(self.bar_len, self.para_ema2_len)

            # 3、获取前InputN周期(不包含当前周期）的自适应均线

            barEma2 = ta.EMA(np.append(self.close_array[-ema2_data_len:], [self.cur_price]), count_len)[-1]

            self._rt_ema2 = round(float(barEma2), self.round_n)

        # 计算第三条EMA均线
        if self.para_ema3_len > 0:
            count_len = min(self.bar_len, self.para_ema3_len)

            # 3、获取前InputN周期(不包含当前周期）的自适应均线
            barEma3 = ta.EMA(np.append(self.close_array[-ema3_data_len:], [self.cur_price]), count_len)[-1]
            self._rt_ema3 = round(float(barEma3), self.round_n)

    @property
    def rt_ema1(self):
        self.check_rt_funcs(self.rt_count_ema)
        if self._rt_ema1 is None and len(self.line_ema1) > 0:
            return self.line_ema1[-1]
        return self._rt_ema1

    @property
    def rt_ema2(self):
        self.check_rt_funcs(self.rt_count_ema)
        if self._rt_ema2 is None and len(self.line_ema2) > 0:
            return self.line_ema2[-1]
        return self._rt_ema2

    @property
    def rt_ema3(self):
        self.check_rt_funcs(self.rt_count_ema)
        if self._rt_ema3 is None and len(self.line_ema3) > 0:
            return self.line_ema3[-1]
        return self._rt_ema3

    def __count_dmi(self):
        """计算K线的DMI数据和条件"""

        if self.para_dmi_len <= 0:  # 不计算
            return

        # 1、lineMx满足长度才执行计算
        if len(self.line_bar) < self.para_dmi_len + 1:
            self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算DMI需要：{1}'.format(len(self.line_bar), self.para_dmi_len + 1))
            return

        # 2、根据当前High，Low，(不包含当前周期）重新计算TR1，PDM，MDM和ATR
        barTr1 = 0  # 获取InputP周期内的价差最大值之和
        barPdm = 0  # InputP周期内的做多价差之和
        barMdm = 0  # InputP周期内的做空价差之和

        for i in range(self.bar_len - 1, self.bar_len - 1 - self.para_dmi_len, -1):  # 周期 inputDmiLen
            # 3.1、计算TR1

            # 当前周期最高与最低的价差
            high_low_spread = self.line_bar[i].high - self.line_bar[i].low
            # 当前周期最高与昨收价的价差
            high_preclose_spread = abs(self.line_bar[i].high - self.line_bar[i - 1].close)
            # 当前周期最低与昨收价的价差
            low_preclose_spread = abs(self.line_bar[i].low - self.line_bar[i - 1].close)

            # 最大价差
            max_spread = max(high_low_spread, high_preclose_spread, low_preclose_spread)
            barTr1 = barTr1 + float(max_spread)

            # 今高与昨高的价差
            high_prehigh_spread = self.line_bar[i].high - self.line_bar[i - 1].high
            # 昨低与今低的价差
            low_prelow_spread = self.line_bar[i - 1].low - self.line_bar[i].low

            # 3.2、计算周期内的做多价差之和
            if high_prehigh_spread > 0 and high_prehigh_spread > low_prelow_spread:
                barPdm = barPdm + high_prehigh_spread

            # 3.3、计算周期内的做空价差之和
            if low_prelow_spread > 0 and low_prelow_spread > high_prehigh_spread:
                barMdm = barMdm + low_prelow_spread

        # 6、计算上升动向指标，即做多的比率
        if barTr1 == 0:
            self.cur_pdi = 0
        else:
            self.cur_pdi = barPdm * 100 / barTr1

        if len(self.line_pdi) > self.max_hold_bars:
            del self.line_pdi[0]

        self.line_pdi.append(self.cur_pdi)

        # 7、计算下降动向指标，即做空的比率
        if barTr1 == 0:
            self.cur_mdi = 0
        else:
            self.cur_mdi = barMdm * 100 / barTr1

        # 8、计算平均趋向指标 Adx，Adxr
        if self.cur_mdi + self.cur_pdi == 0:
            dx = 0
        else:
            dx = 100 * abs(self.cur_mdi - self.cur_pdi) / (self.cur_mdi + self.cur_pdi)

        if len(self.line_mdi) > self.max_hold_bars:
            del self.line_mdi[0]

        self.line_mdi.append(self.cur_mdi)

        if len(self.line_dx) > self.max_hold_bars:
            del self.line_dx[0]

        self.line_dx.append(dx)

        # 平均趋向指标，MA计算
        if len(self.line_dx) < self.para_dmi_len + 1:
            self.cur_adx = dx
        else:
            self.cur_adx = ta.EMA(np.array(self.line_dx, dtype=float), self.para_dmi_len)[-1]

        # 保存Adx值
        if len(self.line_adx) > self.max_hold_bars:
            del self.line_adx[0]

        self.line_adx.append(self.cur_adx)

        # 趋向平均值，为当日ADX值与1周期前的ADX值的均值
        if len(self.line_adx) == 1:
            self.cur_adxr = self.line_adx[-1]
        else:
            self.cur_adxr = (self.line_adx[-1] + self.line_adx[-2]) / 2

        # 保存Adxr值
        if len(self.line_adxr) > self.max_hold_bars:
            del self.line_adxr[0]
        self.line_adxr.append(self.cur_adxr)

        # 7、计算A，ADX值持续高于前一周期时，市场行情将维持原趋势
        if len(self.line_adx) < 2:
            self.cur_adx_trend = False
        elif self.line_adx[-1] > self.line_adx[-2]:
            self.cur_adx_trend = True
        else:
            self.cur_adx_trend = False

        # ADXR值持续高于前一周期时,波动率比上一周期高
        if len(self.line_adxr) < 2:
            self.cur_adxr_trend = False
        elif self.line_adxr[-1] > self.line_adxr[-2]:
            self.cur_adxr_trend = True
        else:
            self.cur_adxr_trend = False

        # 多过滤器条件,做多趋势，ADX高于前一天，上升动向> inputDmiMax
        if self.cur_pdi > self.cur_mdi and self.cur_adx_trend and self.cur_adxr_trend and self.cur_pdi >= self.para_dmi_max:
            self.signal_adx_long = True
            self.write_log(u'{0}[DEBUG]Buy Signal On Bar,Pdi:{1}>Mdi:{2},adx[-1]:{3}>Adx[-2]:{4}'
                           .format(self.cur_tick.datetime, self.cur_pdi, self.cur_mdi, self.line_adx[-1],
                                   self.line_adx[-2]))
        else:
            self.signal_adx_long = False

        # 空过滤器条件 做空趋势，ADXR高于前一天，下降动向> inputMM
        if self.cur_pdi < self.cur_mdi and self.cur_adx_trend and self.cur_adxr_trend and self.cur_mdi >= self.para_dmi_max:
            self.signal_adx_short = True

            self.write_log(u'{0}[DEBUG]Short Signal On Bar,Pdi:{1}<Mdi:{2},adx[-1]:{3}>Adx[-2]:{4}'
                           .format(self.cur_tick.datetime, self.cur_pdi, self.cur_mdi, self.line_adx[-1],
                                   self.line_adx[-2]))
        else:
            self.signal_adx_short = False

    def __count_atr(self):
        """计算Mx K线的各类数据和条件"""
        # 1、lineMx满足长度才执行计算
        maxAtrLen = max(self.para_atr1_len, self.para_atr2_len, self.para_atr3_len)
        if maxAtrLen <= 0:  # 不计算
            return

        data_need_len = min(7, maxAtrLen)

        if self.bar_len < data_need_len:
            self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算ATR需要：{1}'.
                           format(self.bar_len, data_need_len))
            return

        # 计算 ATR
        if self.para_atr1_len > 0:
            count_len = min(self.bar_len, self.para_atr1_len)
            cur_atr1 = ta.ATR(self.high_array[-count_len * 2:], self.low_array[-count_len * 2:],
                                   self.close_array[-count_len * 2:], count_len)
            self.cur_atr1 = round(cur_atr1[-1], self.round_n)
            if len(self.line_atr1) > self.max_hold_bars:
                del self.line_atr1[0]
            self.line_atr1.append(self.cur_atr1)

        if self.para_atr2_len > 0:
            count_len = min(self.bar_len, self.para_atr2_len)
            cur_atr2 = ta.ATR(self.high_array[-count_len * 2:], self.low_array[-count_len * 2:],
                                   self.close_array[-count_len * 2:], count_len)
            self.cur_atr2 = round(cur_atr2[-1], self.round_n)
            if len(self.line_atr2) > self.max_hold_bars:
                del self.line_atr2[0]
            self.line_atr2.append(self.cur_atr2)

        if self.para_atr3_len > 0:
            count_len = min(self.bar_len, self.para_atr3_len)
            cur_atr3 = ta.ATR(self.high_array[-count_len * 2 :], self.low_array[-count_len * 2:],
                                   self.close_array[-count_len * 2:], count_len)
            self.cur_atr3 = round(cur_atr3[-1], self.round_n)

            if len(self.line_atr3) > self.max_hold_bars:
                del self.line_atr3[0]

            self.line_atr3.append(self.cur_atr3)

    # ----------------------------------------------------------------------
    def __count_vol_ma(self):
        """计算平均成交量"""

        # 1、lineBar满足长度才执行计算
        if self.para_vol_len <= 0:  # 不计算
            return

        bar_len = min(self.bar_len, self.para_vol_len)
        sumVol = sum([x.volume for x in self.line_bar[-bar_len:]])
        avgVol = round(sumVol / bar_len, 0)

        if len(self.line_vol_ma) > self.max_hold_bars:
            del self.line_vol_ma[0]
        self.line_vol_ma.append(avgVol)

    # ----------------------------------------------------------------------
    def __count_rsi(self):
        """计算K线的RSI"""
        if self.para_rsi1_len <= 0 and self.para_rsi2_len <= 0:
            return

        # 1、lineBar满足长度才执行计算
        if len(self.line_bar) < self.para_rsi1_len + 2:
            self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算RSI需要：{1}'.
                           format(len(self.line_bar), self.para_rsi1_len + 2))
            return

        # 计算第1根RSI曲线
        # 3、inputRsi1Len(包含当前周期）的相对强弱

        barRsi = ta.RSI(self.close_array[-2 * self.para_rsi1_len:], self.para_rsi1_len)[-1]
        barRsi = round(float(barRsi), self.round_n)

        if len(self.line_rsi1) > self.max_hold_bars:
            del self.line_rsi1[0]

        self.line_rsi1.append(barRsi)

        if len(self.line_rsi1) > 3:
            # 峰
            if self.line_rsi1[-1] < self.line_rsi1[-2] and self.line_rsi1[-3] < self.line_rsi1[-2]:
                t = {}
                t["Type"] = u'T'
                t["RSI"] = self.line_rsi1[-2]
                t["Close"] = self.close_array[-1]

                if len(self.rsi_top_list) > self.max_hold_bars:
                    del self.rsi_top_list[0]

                self.rsi_top_list.append(t)
                self.cur_rsi_top_buttom = self.rsi_top_list[-1]

            # 谷
            elif self.line_rsi1[-1] > self.line_rsi1[-2] and self.line_rsi1[-3] > self.line_rsi1[-2]:
                b = {}
                b["Type"] = u'B'
                b["RSI"] = self.line_rsi1[-2]
                b["Close"] = self.close_array[-1]

                if len(self.rsi_buttom_list) > self.max_hold_bars:
                    del self.rsi_buttom_list[0]
                self.rsi_buttom_list.append(b)
                self.cur_rsi_top_buttom = self.rsi_buttom_list[-1]

        # 计算第二根RSI曲线
        if self.para_rsi2_len > 0:
            if self.bar_len < self.para_rsi2_len + 2:
                return

            barRsi = ta.RSI(self.close_array[-2 * self.para_rsi2_len:], self.para_rsi2_len)[-1]
            barRsi = round(float(barRsi), self.round_n)

            if len(self.line_rsi2) > self.max_hold_bars:
                del self.line_rsi2[0]

            self.line_rsi2.append(barRsi)

    def __count_cmi(self):
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
        if self.para_cmi_len <= 0:
            return

        # 1、lineBar满足长度才执行计算
        if self.bar_len < self.para_cmi_len:
            self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算CMI需要：{1}'.
                           format(len(self.line_bar), self.para_cmi_len))
            return

        hhv = max(self.close_array[-self.para_cmi_len:])
        llv = min(self.close_array[-self.para_cmi_len:])

        if hhv == llv:
            cmi = 100
        else:
            cmi = abs(self.close_array[-1] - self.close_array[-self.para_cmi_len]) * 100 / (hhv - llv)

        cmi = round(cmi, self.round_n)

        if len(self.line_cmi) > self.max_hold_bars:
            del self.line_cmi[0]

        self.line_cmi.append(cmi)

    def __count_boll(self):
        """布林特线"""
        if not (self.para_boll_len > 0
                or self.para_boll2_len > 0
                or self.para_boll_tb_len > 0
                or self.para_boll2_tb_len > 0):  # 不计算
            return

        if self.para_boll_len > 0:
            if self.bar_len < min(7, self.para_boll_len):
                self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算Boll需要：{1}'.
                               format(len(self.line_bar), min(14, self.para_boll_len) + 1))
            else:
                bollLen = min(self.bar_len, self.para_boll_len)

                # 不包含当前最新的Bar
                upper_list, middle_list, lower_list = ta.BBANDS(self.close_array,
                                                                timeperiod=bollLen, nbdevup=self.para_boll_std_rate,
                                                                nbdevdn=self.para_boll_std_rate, matype=0)
                if len(self.line_boll_upper) > self.max_hold_bars:
                    del self.line_boll_upper[0]
                if len(self.line_boll_middle) > self.max_hold_bars:
                    del self.line_boll_middle[0]
                if len(self.line_boll_lower) > self.max_hold_bars:
                    del self.line_boll_lower[0]
                if len(self.line_boll_std) > self.max_hold_bars:
                    del self.line_boll_std[0]

                # 1标准差
                std = (upper_list[-1] - lower_list[-1]) / (self.para_boll_std_rate * 2)
                self.line_boll_std.append(std)

                upper = round(upper_list[-1], self.round_n)
                self.line_boll_upper.append(upper)  # 上轨
                self.cur_upper = upper - upper % self.price_tick  # 上轨取整

                middle = round(middle_list[-1], self.round_n)
                self.line_boll_middle.append(middle)  # 中轨
                self.cur_middle = middle - middle % self.price_tick  # 中轨取整

                lower = round(lower_list[-1], self.round_n)
                self.line_boll_lower.append(lower)  # 下轨
                self.cur_lower = lower - lower % self.price_tick  # 下轨取整

                # 计算斜率
                if len(self.line_boll_upper) > 2 and self.line_boll_upper[-2] != 0:
                    up_atan = math.atan((self.line_boll_upper[-1] / self.line_boll_upper[-2] - 1) * 100) * 180 / math.pi
                    up_atan = round(up_atan, 3)
                    if len(self.line_upper_atan) > self.max_hold_bars:
                        del self.line_upper_atan[0]
                    self.line_upper_atan.append(up_atan)
                if len(self.line_boll_middle) > 2 and self.line_boll_middle[-2] != 0:
                    mid_atan = math.atan(
                        (self.line_boll_middle[-1] / self.line_boll_middle[-2] - 1) * 100) * 180 / math.pi
                    mid_atan = round(mid_atan, 3)
                    if len(self.line_middle_atan) > self.max_hold_bars:
                        del self.line_middle_atan[0]
                    self.line_middle_atan.append(mid_atan)
                if len(self.line_boll_lower) > 2 and self.line_boll_lower[-2] != 0:
                    low_atan = math.atan(
                        (self.line_boll_lower[-1] / self.line_boll_lower[-2] - 1) * 100) * 180 / math.pi
                    low_atan = round(low_atan, 3)
                    if len(self.line_lower_atan) > self.max_hold_bars:
                        del self.line_lower_atan[0]
                    self.line_lower_atan.append(low_atan)

        if self.para_boll2_len > 0:
            if self.bar_len < min(14, self.para_boll2_len) + 1:
                self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算Boll2需要：{1}'.
                               format(len(self.line_bar), min(14, self.para_boll2_len) + 1))
            else:
                boll2Len = min(self.bar_len, self.para_boll2_len)

                # 不包含当前最新的Bar
                upper_list, middle_list, lower_list = ta.BBANDS(self.close_array[-2 * self.para_boll2_len],
                                                                timeperiod=boll2Len, nbdevup=self.para_boll2_std_sate,
                                                                nbdevdn=self.para_boll2_std_sate, matype=0)
                if len(self.line_boll2_upper) > self.max_hold_bars:
                    del self.line_boll2_upper[0]
                if len(self.line_boll2_middle) > self.max_hold_bars:
                    del self.line_boll2_middle[0]
                if len(self.line_boll2_lower) > self.max_hold_bars:
                    del self.line_boll2_lower[0]
                if len(self.line_boll2_std) > self.max_hold_bars:
                    del self.line_boll2_std[0]

                # 1标准差
                std = (upper_list[-1] - lower_list[-1]) / (self.para_boll2_std_sate * 2)
                self.line_boll2_std.append(std)

                upper = round(upper_list[-1], self.round_n)
                self.line_boll2_upper.append(upper)  # 上轨
                self.cur_upper2 = upper - upper % self.price_tick  # 上轨取整

                middle = round(middle_list[-1], self.round_n)
                self.line_boll2_middle.append(middle)  # 中轨
                self.cur_middle2 = middle - middle % self.price_tick  # 中轨取整

                lower = round(lower_list[-1], self.round_n)
                self.line_boll2_lower.append(lower)  # 下轨
                self.cur_lower2 = lower - lower % self.price_tick  # 下轨取整

                # 计算斜率
                if len(self.line_boll2_upper) > 2 and self.line_boll2_upper[-2] != 0:
                    up_atan = math.atan(
                        (self.line_boll2_upper[-1] / self.line_boll2_upper[-2] - 1) * 100) * 180 / math.pi
                    up_atan = round(up_atan, 3)
                    if len(self.line_upper2_atan) > self.max_hold_bars:
                        del self.line_upper2_atan[0]
                    self.line_upper2_atan.append(up_atan)
                if len(self.line_boll2_middle) > 2 and self.line_boll2_middle[-2] != 0:
                    mid_atan = math.atan(
                        (self.line_boll2_middle[-1] / self.line_boll2_middle[-2] - 1) * 100) * 180 / math.pi
                    mid_atan = round(mid_atan, 3)
                    if len(self.line_middle2_atan) > self.max_hold_bars:
                        del self.line_middle2_atan[0]
                    self.line_middle2_atan.append(mid_atan)
                if len(self.line_boll2_lower) > 2 and self.line_boll2_lower[-2] != 0:
                    low_atan = math.atan(
                        (self.line_boll2_lower[-1] / self.line_boll2_lower[-2] - 1) * 100) * 180 / math.pi
                    low_atan = round(low_atan, 3)
                    if len(self.line_lower2_atan) > self.max_hold_bars:
                        del self.line_lower2_atan[0]
                    self.line_lower2_atan.append(low_atan)

        if self.para_boll_tb_len > 0:
            if self.bar_len < min(14, self.para_boll_tb_len) + 1:
                self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算Boll需要：{1}'.
                               format(len(self.line_bar), min(14, self.para_boll_tb_len) + 1))
            else:
                bollLen = min(self.bar_len, self.para_boll_tb_len)

                # 不包含当前最新的Bar

                if len(self.line_boll_upper) > self.max_hold_bars:
                    del self.line_boll_upper[0]
                if len(self.line_boll_middle) > self.max_hold_bars:
                    del self.line_boll_middle[0]
                if len(self.line_boll_lower) > self.max_hold_bars:
                    del self.line_boll_lower[0]
                if len(self.line_boll_std) > self.max_hold_bars:
                    del self.line_boll_std[0]

                # 1标准差
                std = np.std(self.close_array[-2 * bollLen:], ddof=1)
                self.line_boll_std.append(std)

                middle = np.mean(self.close_array[-2 * bollLen:])
                self.line_boll_middle.append(middle)  # 中轨
                self.cur_middle = middle - middle % self.price_tick  # 中轨取整

                upper = middle + self.para_boll_std_rate * std
                self.line_boll_upper.append(upper)  # 上轨
                self.cur_upper = upper - upper % self.price_tick  # 上轨取整

                lower = middle - self.para_boll_std_rate * std
                self.line_boll_lower.append(lower)  # 下轨
                self.cur_lower = lower - lower % self.price_tick  # 下轨取整

                # 计算斜率
                if len(self.line_boll_upper) > 2 and self.line_boll_upper[-2] != 0:
                    up_atan = math.atan((self.line_boll_upper[-1] / self.line_boll_upper[-2] - 1) * 100) * 180 / math.pi
                    up_atan = round(up_atan, 3)
                    if len(self.line_upper_atan) > self.max_hold_bars:
                        del self.line_upper_atan[0]
                    self.line_upper_atan.append(up_atan)
                if len(self.line_boll_middle) > 2 and self.line_boll_middle[-2] != 0:
                    mid_atan = math.atan(
                        (self.line_boll_middle[-1] / self.line_boll_middle[-2] - 1) * 100) * 180 / math.pi
                    mid_atan = round(mid_atan, 3)
                    if len(self.line_middle_atan) > self.max_hold_bars:
                        del self.line_middle_atan[0]
                    self.line_middle_atan.append(mid_atan)
                if len(self.line_boll_lower) > 2 and self.line_boll_lower[-2] != 0:
                    low_atan = math.atan(
                        (self.line_boll_lower[-1] / self.line_boll_lower[-2] - 1) * 100) * 180 / math.pi
                    low_atan = round(low_atan, 3)
                    if len(self.line_lower_atan) > self.max_hold_bars:
                        del self.line_lower_atan[0]
                    self.line_lower_atan.append(low_atan)

        if self.para_boll2_tb_len > 0:
            if self.bar_len < min(14, self.para_boll2_tb_len) + 1:
                self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算Boll2需要：{1}'.
                               format(len(self.line_bar), min(14, self.para_boll2_tb_len) + 1))
            else:
                boll2Len = min(self.bar_len, self.para_boll2_tb_len)

                if len(self.line_boll2_upper) > self.max_hold_bars:
                    del self.line_boll2_upper[0]
                if len(self.line_boll2_middle) > self.max_hold_bars:
                    del self.line_boll2_middle[0]
                if len(self.line_boll2_lower) > self.max_hold_bars:
                    del self.line_boll2_lower[0]
                if len(self.line_boll2_std) > self.max_hold_bars:
                    del self.line_boll2_std[0]

                # 1标准差
                std = np.std(self.close_array[-2 * boll2Len:], ddof=1)
                self.line_boll2_std.append(std)

                middle = np.mean(self.close_array[-2 * boll2Len:])
                self.line_boll2_middle.append(middle)  # 中轨
                self.cur_middle2 = middle - middle % self.price_tick  # 中轨取整

                upper = middle + self.para_boll2_std_sate * std
                self.line_boll2_upper.append(upper)  # 上轨
                self.cur_upper2 = upper - upper % self.price_tick  # 上轨取整

                lower = middle - self.para_boll2_std_sate * std
                self.line_boll2_lower.append(lower)  # 下轨
                self.cur_lower2 = lower - lower % self.price_tick  # 下轨取整

                # 计算斜率
                if len(self.line_boll2_upper) > 2 and self.line_boll2_upper[-2] != 0:
                    up_atan = math.atan(
                        (self.line_boll2_upper[-1] / self.line_boll2_upper[-2] - 1) * 100) * 180 / math.pi
                    up_atan = round(up_atan, 3)
                    if len(self.line_upper2_atan) > self.max_hold_bars:
                        del self.line_upper2_atan[0]
                    self.line_upper2_atan.append(up_atan)
                if len(self.line_boll2_middle) > 2 and self.line_boll2_middle[-2] != 0:
                    mid_atan = math.atan(
                        (self.line_boll2_middle[-1] / self.line_boll2_middle[-2] - 1) * 100) * 180 / math.pi
                    mid_atan = round(mid_atan, 3)
                    if len(self.line_middle2_atan) > self.max_hold_bars:
                        del self.line_middle2_atan[0]
                    self.line_middle2_atan.append(mid_atan)
                if len(self.line_boll2_lower) > 2 and self.line_boll2_lower[-2] != 0:
                    low_atan = math.atan(
                        (self.line_boll2_lower[-1] / self.line_boll2_lower[-2] - 1) * 100) * 180 / math.pi
                    low_atan = round(low_atan, 3)
                    if len(self.line_lower2_atan) > self.max_hold_bars:
                        del self.line_lower2_atan[0]
                    self.line_lower2_atan.append(low_atan)

    def rt_count_boll(self):
        """实时计算布林上下轨，斜率"""
        boll_01_len = max(self.para_boll_len, self.para_boll_tb_len)
        boll_02_len = max(self.para_boll2_len, self.para_boll2_tb_len)

        if not (boll_01_len > 0 or boll_02_len > 0):  # 不计算
            return

        if boll_01_len > 0:
            if self.bar_len < min(14, boll_01_len) + 1:
                return

            bollLen = min(boll_01_len, self.bar_len)

            if self.para_boll_tb_len == 0:
                upper_list, middle_list, lower_list = ta.BBANDS(self.close_array[-bollLen:],
                                                                timeperiod=bollLen, nbdevup=self.para_boll_std_rate,
                                                                nbdevdn=self.para_boll_std_rate, matype=0)

                # 1标准差
                std = (upper_list[-1] - lower_list[-1]) / (self.para_boll_std_rate * 2)
                self._rt_upper = round(upper_list[-1], self.round_n)
                self._rt_middle = round(middle_list[-1], self.round_n)
                self._rt_lower = round(lower_list[-1], self.round_n)
            else:
                # 1标准差
                std = np.std(np.append(self.close_array[-boll_01_len:], [self.line_bar[-1].close]), ddof=1)
                middle = np.mean(np.append(self.close_array[-boll_01_len:], [self.line_bar[-1].close]))
                self._rt_middle = round(middle, self.round_n)
                upper = middle + self.para_boll_std_rate * std
                self._rt_upper = round(upper, self.round_n)
                lower = middle - self.para_boll_std_rate * std
                self._rt_lower = round(lower, self.round_n)

            # 计算斜率
            if len(self.line_boll_upper) > 2 and self.line_boll_upper[-1] != 0:
                up_atan = math.atan((self._rt_upper / self.line_boll_upper[-1] - 1) * 100) * 180 / math.pi
                self._rt_upper_atan = round(up_atan, 3)

            if len(self.line_boll_middle) > 2 and self.line_boll_middle[-1] != 0:
                mid_atan = math.atan((self._rt_middle / self.line_boll_middle[-1] - 1) * 100) * 180 / math.pi
                self._rt_middle_atan = round(mid_atan, 3)

            if len(self.line_boll_lower) > 2 and self.line_boll_lower[-1] != 0:
                low_atan = math.atan((self._rt_lower / self.line_boll_lower[-1] - 1) * 100) * 180 / math.pi
                self._rt_lower_atan = round(low_atan, 3)

        if boll_02_len > 0:
            if self.bar_len < min(14, boll_02_len) + 1:
                return

            bollLen = min(boll_02_len, self.bar_len)

            if self.para_boll2_tb_len == 0:
                upper_list, middle_list, lower_list = ta.BBANDS(self.close_array[-bollLen:],
                                                                timeperiod=bollLen, nbdevup=self.para_boll_std_rate,
                                                                nbdevdn=self.para_boll_std_rate, matype=0)

                # 1标准差
                std = (upper_list[-1] - lower_list[-1]) / (self.para_boll2_std_sate * 2)
                self._rt_upper2 = round(upper_list[-1], self.round_n)
                self._rt_middle2 = round(middle_list[-1], self.round_n)
                self._rt_lower2 = round(lower_list[-1], self.round_n)
            else:
                # 1标准差
                std = np.std(np.append(self.close_array[-boll_02_len:], [self.line_bar[-1].close]), ddof=1)
                middle = np.mean(np.append(self.close_array[-boll_02_len:], [self.line_bar[-1].close]))
                self._rt_middle2 = round(middle, self.round_n)
                upper = middle + self.para_boll_std_rate * std
                self._rt_upper2 = round(upper, self.round_n)
                lower = middle - self.para_boll_std_rate * std
                self._rt_lower2 = round(lower, self.round_n)

            # 计算斜率
            if len(self.line_boll2_upper) > 2 and self.line_boll2_upper[-1] != 0:
                up_atan = math.atan((self._rt_upper2 / self.line_boll2_upper[-1] - 1) * 100) * 180 / math.pi
                self._rt_upper2_atan = round(up_atan, 3)

            if len(self.line_boll2_middle) > 2 and self.line_boll2_middle[-1] != 0:
                mid_atan = math.atan((self._rt_middle2 / self.line_boll2_middle[-1] - 1) * 100) * 180 / math.pi
                self._rt_middle2_atan = round(mid_atan, 3)

            if len(self.line_boll2_lower) > 2 and self.line_boll2_lower[-1] != 0:
                low_atan = math.atan((self._rt_lower2 / self.line_boll2_lower[-1] - 1) * 100) * 180 / math.pi
                self._rt_lower2_atan = round(low_atan, 3)

    @property
    def rt_upper(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_upper is None and len(self.line_boll_upper) > 0:
            return self.line_boll_upper[-1]
        return self._rt_upper

    @property
    def rt_middle(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_middle is None and len(self.line_boll_middle) > 0:
            return self.line_boll_middle[-1]
        return self._rt_middle

    @property
    def rt_lower(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_lower is None and len(self.line_boll_lower) > 0:
            return self.line_boll_lower[-1]
        return self._rt_lower

    @property
    def rt_upper_atan(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_upper_atan is None and len(self.line_upper_atan) > 0:
            return self.line_upper_atan[-1]
        return self._rt_upper_atan

    @property
    def rt_middle_atan(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_middle_atan is None and len(self.line_middle_atan) > 0:
            return self.line_middle_atan[-1]
        return self._rt_middle_atan

    @property
    def rt_lower_atan(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_lower_atan is None and len(self.line_lower_atan) > 0:
            return self.line_lower_atan[-1]
        return self._rt_lower_atan

    @property
    def rt_upper2(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_upper2 is None and len(self.line_boll2_upper) > 0:
            return self.line_boll2_upper[-1]
        return self._rt_upper2

    @property
    def rt_middle2(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_middle2 is None and len(self.line_boll2_middle) > 0:
            return self.line_boll2_middle[-1]
        return self._rt_middle2

    @property
    def rt_lower2(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_lower2 is None and len(self.line_boll2_lower) > 0:
            return self.line_boll2_lower[-1]
        return self._rt_lower2

    @property
    def rt_upper2_atan(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_upper2_atan is None and len(self.line_upper2_atan) > 0:
            return self.line_upper2_atan[-1]
        return self._rt_upper2_atan

    @property
    def rt_middle2_atan(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_middle2_atan is None and len(self.line_middle2_atan) > 0:
            return self.line_middle2_atan[-1]
        return self._rt_middle2_atan

    @property
    def rt_lower2_atan(self):
        self.check_rt_funcs(self.rt_count_boll)
        if self._rt_lower2_atan is None and len(self.line_lower2_atan) > 0:
            return self.line_lower2_atan[-1]
        return self._rt_lower2_atan

    def __count_kdj(self):
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
        if self.para_kdj_len <= 0:
            return

        if len(self.line_bar) < self.para_kdj_len + 1:
            self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算KDJ需要：{1}'.format(len(self.line_bar), self.para_kdj_len + 1))
            return

        if self.para_kdj_slow_len == 0:
            self.para_kdj_slow_len = 3
        if self.para_kdj_smooth_len == 0:
            self.para_kdj_smooth_len = 3

        inputKdjLen = min(self.para_kdj_len, self.bar_len)

        hhv = max(self.high_array[-inputKdjLen:])
        llv = min(self.low_array[-inputKdjLen:])

        if len(self.line_k) > 0:
            lastK = self.line_k[-1]
        else:
            lastK = 0

        if len(self.line_d) > 0:
            lastD = self.line_d[-1]
        else:
            lastD = 0

        if hhv == llv:
            rsv = 50
        else:
            rsv = (self.close_array[-1] - llv) / (hhv - llv) * 100

        self.line_rsv.append(rsv)

        k = (self.para_kdj_slow_len - 1) * lastK / self.para_kdj_slow_len + rsv / self.para_kdj_slow_len
        if k < 0:
            k = 0
        if k > 100:
            k = 100

        d = (self.para_kdj_smooth_len - 1) * lastD / self.para_kdj_smooth_len + k / self.para_kdj_smooth_len
        if d < 0:
            d = 0
        if d > 100:
            d = 100

        j = self.para_kdj_smooth_len * k - (self.para_kdj_smooth_len - 1) * d

        if len(self.line_k) > self.max_hold_bars:
            del self.line_k[0]
        self.line_k.append(k)

        if len(self.line_d) > self.max_hold_bars:
            del self.line_d[0]
        self.line_d.append(d)

        if len(self.line_j) > self.max_hold_bars:
            del self.line_j[0]
        self.line_j.append(j)

        # 增加KDJ的J谷顶和波底
        if len(self.line_j) > 3:
            # 峰
            if self.line_j[-1] < self.line_j[-2] and self.line_j[-3] <= self.line_j[-2]:
                t = {
                    'Type': 'T',
                    'J': self.line_j[-2],
                    'Close': self.close_array[-1]}

                if len(self.kdj_top_list) > self.max_hold_bars:
                    del self.kdj_top_list[0]

                self.kdj_top_list.append(t)
                self.cur_kdj_top_buttom = self.kdj_top_list[-1]

            # 谷
            elif self.line_j[-1] > self.line_j[-2] and self.line_j[-3] >= self.line_j[-2]:
                b = {
                    'Type': u'B',
                    'J': self.line_j[-2],
                    'Close': self.close_array[-1]
                }
                if len(self.kdj_buttom_list) > self.max_hold_bars:
                    del self.kdj_buttom_list[0]
                self.kdj_buttom_list.append(b)
                self.cur_kdj_top_buttom = self.kdj_buttom_list[-1]

        self.__update_kd_cross()

    def __count_kdj_tb(self):
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
        if self.para_kdj_tb_len <= 0:
            return

        if self.para_kdj_tb_len + self.para_kdj_smooth_len > self.max_hold_bars:
            self.max_hold_bars = self.para_kdj_tb_len + self.para_kdj_smooth_len + 1

        if self.para_kdj_slow_len == 0:
            self.para_kdj_slow_len = 3
        if self.para_kdj_smooth_len == 0:
            self.para_kdj_smooth_len = 3

        if self.bar_len < 3:
            return

        data_len = min(self.bar_len, self.para_kdj_tb_len)

        hhv = max(self.high_array[-data_len:])
        llv = min(self.low_array[-data_len:])

        if len(self.line_k) > 0:
            lastK = self.line_k[-1]
        else:
            lastK = 0

        if len(self.line_d) > 0:
            lastD = self.line_d[-1]
        else:
            lastD = 0

        if hhv == llv:
            rsv = 50
        else:
            rsv = (self.close_array - llv) / (hhv - llv) * 100

        self.line_rsv.append(rsv)

        k = (self.para_kdj_slow_len - 1) * lastK / self.para_kdj_slow_len + rsv / self.para_kdj_slow_len
        if k < 0:
            k = 0
        if k > 100:
            k = 100

        d = (self.para_kdj_smooth_len - 1) * lastD / self.para_kdj_smooth_len + k / self.para_kdj_smooth_len
        if d < 0:
            d = 0
        if d > 100:
            d = 100

        j = self.para_kdj_smooth_len * k - (self.para_kdj_smooth_len - 1) * d

        if len(self.line_k) > self.max_hold_bars:
            del self.line_k[0]
        self.line_k.append(k)

        if len(self.line_d) > self.max_hold_bars:
            del self.line_d[0]
        self.line_d.append(d)

        if len(self.line_j) > self.max_hold_bars:
            del self.line_j[0]
        self.line_j.append(j)

        # 增加KDJ的J谷顶和波底
        if len(self.line_j) > 3:
            # 峰
            if self.line_j[-1] < self.line_j[-2] and self.line_j[-3] <= self.line_j[-2]:
                t = {
                    'Type': 'T',
                    'J': self.line_j[-2],
                    'Close': self.close_array[-1]
                }
                if len(self.kdj_top_list) > self.max_hold_bars:
                    del self.kdj_top_list[0]

                self.kdj_top_list.append(t)
                self.cur_kdj_top_buttom = self.kdj_top_list[-1]

            # 谷
            elif self.line_j[-1] > self.line_j[-2] and self.line_j[-3] >= self.line_j[-2]:

                b = {
                    'Type': 'B',
                    'J': self.line_j[-2],
                    'Close': self.close_array
                }
                if len(self.kdj_buttom_list) > self.max_hold_bars:
                    del self.kdj_buttom_list[0]
                self.kdj_buttom_list.append(b)
                self.cur_kdj_top_buttom = self.kdj_buttom_list[-1]

        self.__update_kd_cross()

    def __update_kd_cross(self):
        """更新KDJ金叉死叉"""
        if len(self.line_k) < 2 or len(self.line_d) < 2:
            return

        # K值大于D值
        if self.line_k[-1] > self.line_d[-1]:
            if self.line_k[-2] > self.line_d[-2]:
                # 延续金叉
                self.cur_kd_count = max(1, self.cur_kd_count) + 1
            else:
                # 发生金叉
                self.cur_kd_count = 1
                self.cur_kd_cross = round((self.line_k[-1] + self.line_k[-2]) / 2, 2)
                self.cur_kd_cross_price = self.line_bar[-1].close

        # K值小于D值
        else:
            if self.line_k[-2] < self.line_d[-2]:
                # 延续死叉
                self.cur_kd_count = min(-1, self.cur_kd_count) - 1
            else:
                # 发生死叉
                self.cur_kd_count = -1
                self.cur_kd_cross = round((self.line_k[-1] + self.line_k[-2]) / 2, 2)
                self.cur_kd_cross_price = self.line_bar[-1].close

    def __count_macd(self):
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

        if self.para_macd_fast_len <= 0 or self.para_macd_slow_len <= 0 or self.para_macd_signal_len <= 0:
            return

        maxLen = max(self.para_macd_fast_len, self.para_macd_slow_len) + self.para_macd_signal_len + 1

        # maxLen = maxLen * 3             # 注：数据长度需要足够，才能准确。测试过，3倍长度才可以与国内的文华等软件一致

        if self.bar_len < maxLen:
            self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算MACD需要：{1}'.format(len(self.line_bar), maxLen))
            return

        dif_list, dea_list, macd_list = ta.MACD(self.close_array[-2 * maxLen:], fastperiod=self.para_macd_fast_len,
                                                slowperiod=self.para_macd_slow_len,
                                                signalperiod=self.para_macd_signal_len)

        # dif, dea, macd = ta.MACDEXT(np.array(listClose, dtype=float),
        #                            fastperiod=self.inputMacdFastPeriodLen, fastmatype=1,
        #                            slowperiod=self.inputMacdSlowPeriodLen, slowmatype=1,
        #                            signalperiod=self.inputMacdSignalPeriodLen, signalmatype=1)

        if len(self.line_dif) > self.max_hold_bars:
            del self.line_dif[0]
        self.line_dif.append(round(dif_list[-1], 2))

        if len(self.line_dea) > self.max_hold_bars:
            del self.line_dea[0]
        self.line_dea.append(round(dea_list[-1], 2))

        if len(self.line_macd) > self.max_hold_bars:
            del self.line_macd[0]
        self.line_macd.append(round(macd_list[-1] * 2, 2))  # 国内一般是2倍

        # 更新 “段”（金叉-》死叉；或 死叉-》金叉)
        segment = self.macd_segment_list[-1] if len(self.macd_segment_list) > 0 else {}

        # 创建新的段
        if (self.line_macd[-1] > 0 and self.cur_macd_count <= 0) or \
                (self.line_macd[-1] < 0 and self.cur_macd_count >= 0):
            segment = {}
            # 金叉/死叉，更新位置&价格
            self.cur_macd_count, self.rt_macd_count = (1, 1) if self.line_macd[-1] > 0 else (-1, -1)
            self.cur_macd_cross = round((self.line_dif[-1] + self.line_dea[-1]) / 2, 2)
            self.cur_macd_cross_price = self.close_array[-1]
            self.rt_macd_cross = self.cur_macd_cross
            self.rt_macd_cross_price = self.cur_macd_cross_price
            # 更新段
            segment.update({
                'macd_count': self.cur_macd_count,
                'max_price': self.high_array[-1],
                'min_price': self.low_array[-1],
                'max_dif': self.line_dif[-1],
                'min_dif': self.line_dif[-1],
                'macd_area': abs(self.line_macd[-1]),
                'max_macd': self.line_macd[-1],
                'min_macd': self.line_macd[-1]
            })
            self.macd_segment_list.append(segment)

            # 新得能量柱>0，判断是否有底背离，同时，取消原有顶背离
            if self.line_macd[-1] > 0:
                self.dif_buttom_divergence = self.is_dif_divergence(direction=Direction.SHORT)
                self.macd_buttom_divergence = self.is_macd_divergence(direction=Direction.SHORT)
                self.dif_top_divergence = False
                self.macd_top_divergence = False

            # 新得能量柱<0，判断是否有顶背离，同时，取消原有底背离
            elif self.line_macd[-1] < 0:
                self.dif_buttom_divergence = False
                self.macd_buttom_divergence = False
                self.dif_top_divergence = self.is_dif_divergence(direction=Direction.LONG)
                self.macd_top_divergence = self.is_macd_divergence(direction=Direction.LONG)

        else:
            # 继续金叉
            if self.line_macd[-1] > 0 and self.cur_macd_count > 0:
                self.cur_macd_count += 1

                segment.update({
                    'macd_count': self.cur_macd_count,
                    'max_price': max(segment.get('max_price', self.high_array[-1]), self.high_array[-1]),
                    'min_price': min(segment.get('min_price', self.low_array[-1]), self.low_array[-1]),
                    'max_dif': max(segment.get('max_dif', self.line_dif[-1]), self.line_dif[-1]),
                    'min_dif': min(segment.get('min_dif', self.line_dif[-1]), self.line_dif[-1]),
                    'macd_area': segment.get('macd_area', 0) + abs(self.line_macd[-1]),
                    'max_macd': max(segment.get('max_macd', self.line_macd[-1]), self.line_macd[-1])
                })
                # 取消实时得记录
                self.rt_macd_count = 0
                self.rt_macd_cross = 0
                self.rt_macd_cross_price = 0

            # 继续死叉
            elif self.line_macd[-1] < 0 and self.cur_macd_count < 0:
                self.cur_macd_count -= 1
                segment.update({
                    'macd_count': self.cur_macd_count,
                    'max_price': max(segment.get('max_price', self.high_array[-1]), self.high_array[-1]),
                    'min_price': min(segment.get('min_price', self.low_array[-1]), self.low_array[-1]),
                    'max_dif': max(segment.get('max_dif', self.line_dif[-1]), self.line_dif[-1]),
                    'min_dif': min(segment.get('min_dif', self.line_dif[-1]), self.line_dif[-1]),
                    'macd_area': segment.get('macd_area', 0) + abs(self.line_macd[-1]),
                    'min_macd': min(segment.get('min_macd', self.line_macd[-1]), self.line_macd[-1])
                })

                # 取消实时得记录
                self.rt_macd_count = 0
                self.rt_macd_cross = 0
                self.rt_macd_cross_price = 0

        # 删除超过10个的macd段
        if len(self.macd_segment_list) > 10:
            self.macd_segment_list.pop(0)

    def rt_count_macd(self):
        """
        (实时）Macd计算方法：
        12日EMA的计算：EMA12 = 前一日EMA12 X 11/13 + 今日收盘 X 2/13
        26日EMA的计算：EMA26 = 前一日EMA26 X 25/27 + 今日收盘 X 2/27
        差离值（DIF）的计算： DIF = EMA12 - EMA26，即为talib-MACD返回值macd
        根据差离值计算其9日的EMA，即离差平均值，是所求的DEA值。
        今日DEA = （前一日DEA X 8/10 + 今日DIF X 2/10），即为talib-MACD返回值signal
        DIF与它自己的移动平均之间差距的大小一般BAR=（DIF-DEA)*2，即为MACD柱状图。
        但是talib中MACD的计算是bar = (dif-dea)*1
        """
        if self.para_macd_fast_len <= 0 or self.para_macd_slow_len <= 0 or self.para_macd_signal_len <= 0:
            return

        maxLen = max(self.para_macd_fast_len, self.para_macd_slow_len) + self.para_macd_signal_len + 1
        if self.bar_len < maxLen:
            return

        dif, dea, macd = ta.MACD(np.append(self.close_array[-maxLen:], [self.line_bar[-1].close]),
                                 fastperiod=self.para_macd_fast_len,
                                 slowperiod=self.para_macd_slow_len, signalperiod=self.para_macd_signal_len)

        self._rt_dif = round(dif[-1], 2) if len(dif) > 0 else None
        self._rt_dea = round(dea[-1], 2) if len(dea) > 0 else None
        self._rt_macd = round(macd[-1] * 2, 2) if len(macd) > 0 else None

        # 判断是否实时金叉/死叉
        if self._rt_macd is not None:
            # 实时金叉
            if self._rt_macd >= 0 and self.line_macd[-1] < 0:
                self.rt_macd_count = 1
                self.rt_macd_cross = round((self._rt_dif + self._rt_dea) / 2, 2)
                self.rt_macd_cross_price = self.cur_price

            # 实时死叉
            elif self._rt_macd <= 0 and self.line_macd[-1] > 0:
                self.rt_macd_count = -1
                self.rt_macd_cross = round((self._rt_dif + self._rt_dea) / 2, 2)
                self.rt_macd_cross_price = self.cur_price

    @property
    def rt_dif(self):
        self.check_rt_funcs(self.rt_count_macd)
        if self._rt_dif is None and len(self.line_dif) > 0:
            return self.line_dif[-1]
        return self._rt_dif

    @property
    def rt_dea(self):
        self.check_rt_funcs(self.rt_count_macd)
        if self._rt_dea is None and len(self.line_dea) > 0:
            return self.line_dea[-1]
        return self._rt_dea

    @property
    def rt_macd(self):
        self.check_rt_funcs(self.rt_count_macd)
        if self._rt_macd is None and len(self.line_macd) > 0:
            return self.line_macd[-1]
        return self._rt_macd

    def is_dif_divergence(self, direction):
        """
        检查MACD DIF是否与价格有背离
        :param: direction，多：检查是否有顶背离，空，检查是否有底背离
        """
        s1, s2 = None, None  # s1,倒数的一个匹配段；s2，倒数第二个匹配段
        for seg in reversed(self.macd_segment_list):

            if direction == Direction.LONG:
                if seg.get('macd_count', 0) > 0:
                    if s1 is None:
                        s1 = seg
                        continue
                    elif s2 is None:
                        s2 = seg
                        break
            else:
                if seg.get('macd_count', 0) < 0:
                    if s1 is None:
                        s1 = seg
                        continue
                    elif s2 is None:
                        s2 = seg
                        break

        if not all([s1, s2]):
            return False

        if direction == Direction.LONG:
            s1_max_price = s1.get('max_price', None)
            s2_max_price = s2.get('max_price', None)
            s1_dif_max = s1.get('max_dif', None)
            s2_dif_max = s2.get('max_dif', None)
            if s1_max_price is None or s2_max_price is None or s1_dif_max is None and s2_dif_max is None:
                return False

            # 顶背离，只能在零轴上方才判断
            if s1_dif_max < 0 or s2_dif_max < 0:
                return False

            # 价格创新高（超过前高得0.99）；dif指标没有创新高
            if s1_max_price >= s2_max_price * 0.99 and s1_dif_max < s2_dif_max:
                return True

        if direction == Direction.SHORT:
            s1_min_price = s1.get('min_price', None)
            s2_min_price = s2.get('min_price', None)
            s1_dif_min = s1.get('min_dif', None)
            s2_dif_min = s2.get('min_dif', None)
            if s1_min_price is None or s2_min_price is None or s1_dif_min is None and s2_dif_min is None:
                return False

            # 底部背离，只能在零轴下方才判断
            if s1_dif_min > 0 or s1_dif_min > 0:
                return False

            # 价格创新低，dif没有创新低
            if s1_min_price <= s2_min_price * 1.01 and s1_dif_min > s2_dif_min:
                return True

        return False

    def is_macd_divergence(self, direction):
        """
        检查MACD 能量柱是否与价格有背离
        :param: direction，多：检查是否有顶背离，空，检查是否有底背离
        """
        s1, s2 = None, None  # s1,倒数的一个匹配段；s2，倒数第二个匹配段
        for seg in reversed(self.macd_segment_list):

            if direction == Direction.LONG:
                if seg.get('macd_count', 0) > 0:
                    if s1 is None:
                        s1 = seg
                        continue
                    elif s2 is None:
                        s2 = seg
                        break
            else:
                if seg.get('macd_count', 0) < 0:
                    if s1 is None:
                        s1 = seg
                        continue
                    elif s2 is None:
                        s2 = seg
                        break

        if not all([s1, s2]):
            return False

        if direction == Direction.LONG:
            s1_max_price = s1.get('max_price', None)
            s2_max_price = s2.get('max_price', None)
            s1_area = s1.get('macd_area', None)
            s2_area = s2.get('macd_area', None)
            if s1_max_price is None or s2_max_price is None or s1_area is None and s2_area is None:
                return False

            # 价格创新高（超过前高得0.99）；MACD能量柱没有创更大面积
            if s1_max_price >= s2_max_price * 0.99 and s1_area < s2_area:
                return True

        if direction == Direction.SHORT:
            s1_min_price = s1.get('min_price', None)
            s2_min_price = s2.get('min_price', None)
            s1_area = s1.get('macd_area', None)
            s2_area = s2.get('macd_area', None)
            if s1_min_price is None or s2_min_price is None or s1_area is None and s2_area is None:
                return False

            # 价格创新低，MACD能量柱没有创更大面积
            if s1_min_price <= s2_min_price * 1.01 and s1_area < s2_area:
                return True

        return False

    def __count_cci(self):
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

        if self.para_cci_len <= 0:
            return

        # 1、lineBar满足长度才执行计算
        if len(self.line_bar) < self.para_cci_len + 2:
            self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算CCI需要：{1}'.
                           format(len(self.line_bar), self.para_cci_len + 2))
            return

        # 计算第1根RSI曲线

        cur_cci = ta.CCI(high=self.high_array[-2 * self.para_cci_len:], low=self.low_array[-2 * self.para_cci_len:],
                         close=self.close_array[-2 * self.para_cci_len:], timeperiod=self.para_cci_len)[-1]

        cur_cci = round(float(cur_cci), 3)

        if len(self.line_cci) > self.max_hold_bars:
            del self.line_cci[0]
        self.line_cci.append(cur_cci)

    def __count_kf(self):
        """计算卡尔曼过滤器均线"""
        if not self.para_active_kf or self.kf is None:
            return
        if self.bar_len < 2:
            return

        if len(self.line_state_mean) == 0 or len(self.line_state_covar) == 0:
            try:
                self.kf = KalmanFilter(transition_matrices=[1],
                                       observation_matrices=[1],
                                       initial_state_mean=self.close_array[-1],
                                       initial_state_covariance=1,
                                       transition_covariance=0.01)
            except Exception:
                self.write_log(u'导入卡尔曼过滤器失败,需先安装 pip install pykalman')
                self.para_active_kf = False

            state_means, state_covariances = self.kf.filter(self.close_array)
            m = state_means[-1].item()
            c = state_covariances[-1].item()
        else:
            m = self.line_state_mean[-1]
            c = self.line_state_covar[-1]

            state_means, state_covariances = self.kf.filter_update(filtered_state_mean=m,
                                                                   filtered_state_covariance=c,
                                                                   observation=self.close_array[-1])
            m = state_means[-1].item()
            c = state_covariances[-1].item()

        if len(self.line_state_mean) > self.max_hold_bars:
            del self.line_state_mean[0]
        if len(self.line_state_covar) > self.max_hold_bars:
            del self.line_state_covar[0]

        self.line_state_mean.append(m)
        self.line_state_covar.append(c)

    def __count_period(self, bar):
        """重新计算周期"""

        len_rsi = len(self.line_rsi1)

        if self.para_active_kf:
            if len(self.line_state_mean) < 7 or len_rsi <= 0:
                return
            listMid = self.line_state_mean[-7:-1]
            malist = ta.MA(np.array(listMid, dtype=float), 5)
            lastMid = self.line_state_mean[-1]

        else:
            len_boll = len(self.line_boll_middle)
            if len_boll <= 6 or len_rsi <= 0:
                return
            listMid = self.line_boll_middle[-7:-1]
            lastMid = self.line_boll_middle[-1]
            malist = ta.MA(np.array(listMid, dtype=float), 5)

        ma5 = malist[-1]
        ma5_ref1 = malist[-2]
        if ma5 <= 0 or ma5_ref1 <= 0:
            self.write_log(u'boll中轨计算均线异常')
            return
        if self.para_active_kf:
            self.cur_atan = math.atan((ma5 / ma5_ref1 - 1) * 100) * 180 / math.pi
        else:
            # 当前均值,与前5均值得价差,除以标准差
            self.cur_atan = math.atan((ma5 - ma5_ref1) / self.line_boll_std[-1]) * 180 / math.pi

        # atan2 = math.atan((ma5 / ma5_ref1 - 1) * 100) * 180 / math.pi
        # atan3 = math.atan(ma5 / ma5_ref1 - 1)* 100
        self.cur_atan = round(self.cur_atan, 3)
        # self.write_log(u'{}/{}/{}'.format(self.atan, atan2, atan3))

        if self.cur_period is None:
            self.write_log(u'初始化周期为震荡')
            self.cur_period = CtaPeriod(mode=Period.SHOCK, price=bar.close_price, pre_mode=Period.INIT, dt=bar.datetime)
            self.period_list.append(self.cur_period)

        if len(self.line_atan) > self.max_hold_bars:
            del self.line_atan[0]
        self.line_atan.append(self.cur_atan)

        if len_rsi < 3:
            return

        # 当前期趋势是震荡
        if self.cur_period.mode == Period.SHOCK:
            # 初始化模式
            if self.cur_period.pre_mode == Period.INIT:
                if self.cur_atan < -45:
                    self.cur_period = CtaPeriod(mode=Period.SHORT_EXTREME, price=bar.close_price, pre_mode=Period.SHORT,
                                                dt=bar.datetime)
                    self.period_list.append(self.cur_period)
                    self.write_log(u'{} 角度向下,Atan:{},周期{}=》{}'.
                                   format(bar.datetime, self.cur_atan, self.cur_period.pre_mode, self.cur_period.mode))
                    if self.cb_on_period:
                        self.cb_on_period(self.cur_period)

                    return
                elif self.cur_atan > 45:
                    self.cur_period = CtaPeriod(mode=Period.LONG_EXTREME, price=bar.close_price, pre_mode=Period.LONG,
                                                dt=bar.datetime)
                    self.period_list.append(self.cur_period)
                    self.write_log(u'{} 角度加速向上,Atan:{}，周期:{}=>{}'.
                                   format(bar.datetime, self.cur_atan, self.cur_period.pre_mode,
                                          self.cur_period.mode))
                    if self.cb_on_period:
                        self.cb_on_period(self.cur_period)

                    return

            # 震荡 -》 空
            if self.cur_atan <= -20:
                self.cur_period = CtaPeriod(mode=Period.SHORT, price=bar.close_price, pre_mode=Period.SHOCK,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)
                self.write_log(u'{} 角度向下,Atan:{},周期{}=》{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.pre_mode, self.cur_period.mode))
                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)
            # 震荡 =》 多
            elif self.cur_atan >= 20:
                self.cur_period = CtaPeriod(mode=Period.LONG, price=bar.close_price, pre_mode=Period.SHOCK,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)
                self.write_log(u'{} 角度向上,Atan:{}，周期:{}=>{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.pre_mode,
                                      self.cur_period.mode))
                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)

            # 周期维持不变
            else:
                self.write_log(u'{} 角度维持，Atan:{},周期维持:{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.mode))

            return

        # 当前期趋势是空
        if self.cur_period.mode == Period.SHORT:
            # 空=》空极端
            if self.cur_atan <= -45 and self.line_atan[-1] < self.line_atan[-2]:
                self.cur_period = CtaPeriod(mode=Period.SHORT_EXTREME, price=bar.close_price, pre_mode=Period.SHORT,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)
                self.write_log(u'{} 角度极端向下,Atan:{}，注意反弹。周期:{}=>{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.pre_mode, self.cur_period.mode))
                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)

            # 空=》震荡
            elif -20 < self.cur_atan < 20 or (self.cur_atan >= 20 and self.line_atan[-2] <= -20):
                self.cur_period = CtaPeriod(mode=Period.SHOCK, price=bar.close_price, pre_mode=Period.SHORT,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)
                self.write_log(u'{} 角度平缓，Atan:{},结束下降趋势。周期:{}=>{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.pre_mode, self.cur_period.mode))
                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)

            elif self.cur_atan > 20 and self.cur_period.pre_mode == Period.LONG_EXTREME and self.line_atan[-1] > \
                    self.line_atan[-2] and bar.close_price > lastMid:
                self.cur_period = CtaPeriod(mode=Period.SHOCK, price=bar.close_price, pre_mode=Period.SHORT,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)
                self.write_log(u'{} 角度平缓，Atan:{},结束下降趋势。周期:{}=>{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.pre_mode, self.cur_period.mode))
                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)

            # 周期维持空
            else:
                self.write_log(u'{} 角度向下{},周期维持:{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.mode))

            return

        # 当前期趋势是多
        if self.cur_period.mode == Period.LONG:
            # 多=》多极端
            if self.cur_atan >= 45 and self.line_atan[-1] > self.line_atan[-2]:
                self.cur_period = CtaPeriod(mode=Period.LONG_EXTREME, price=bar.close_price, pre_mode=Period.LONG,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)

                self.write_log(u'{} 角度加速向上,Atan:{}，周期:{}=>{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.pre_mode,
                                      self.cur_period.mode))
                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)

            # 多=》震荡
            elif -20 < self.cur_atan < 20 or (self.cur_atan <= -20 and self.line_atan[-2] >= 20):
                self.cur_period = CtaPeriod(mode=Period.SHOCK, price=bar.close_price, pre_mode=Period.LONG,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)
                self.write_log(u'{} 角度平缓,Atan:{},结束上升趋势。周期:{}=>{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.pre_mode, self.cur_period.mode))
                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)

            # 多=》震荡
            elif self.cur_atan < -20 and self.cur_period.pre_mode == Period.SHORT_EXTREME and self.line_atan[-1] < \
                    self.line_atan[-2] and bar.close_price < lastMid:
                self.cur_period = CtaPeriod(mode=Period.SHOCK, price=bar.close_price, pre_mode=Period.LONG,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)
                self.write_log(u'{} 角度平缓,Atan:{},结束上升趋势。周期:{}=>{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.pre_mode, self.cur_period.mode))

                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)
            # 周期保持多
            else:
                self.write_log(u'{} 角度向上,Atan:{},周期维持:{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.mode))
            return

        # 当前周期为多极端
        if self.cur_period.mode == Period.LONG_EXTREME:
            # 多极端 =》 空
            if self.line_rsi1[-1] < self.line_rsi1[-2] \
                    and max(self.line_rsi1[-5:-2]) >= 50 \
                    and bar.close_price < lastMid:

                self.cur_period = CtaPeriod(mode=Period.SHORT, price=bar.close_price, pre_mode=Period.LONG_EXTREME,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)

                self.write_log(u'{} 角度高位反弹向下，Atan:{} , RSI {}=》{},{}下穿中轨{},周期：{}=》{}'.
                               format(bar.datetime, self.cur_atan, self.line_rsi1[-2], self.line_rsi1[-1],
                                      bar.close_price, lastMid,
                                      self.cur_period.pre_mode, self.cur_period.mode))
                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)

            # 多极端 =》多
            elif self.line_rsi1[-1] < self.line_rsi1[-2] \
                    and bar.close_price > lastMid:
                self.cur_period = CtaPeriod(mode=Period.LONG, price=bar.close_price, pre_mode=Period.LONG_EXTREME,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)
                self.write_log(u'{} 角度上加速放缓，Atan:{}, & RSI{}=>{}，周期：{}=》{}'.
                               format(bar.datetime, self.cur_atan, self.line_rsi1[-2], self.line_rsi1[-1],
                                      self.cur_period.pre_mode, self.cur_period.mode))
                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)

            # 当前趋势保持多极端
            else:
                self.write_log(u'{} 角度向上加速{},周期维持:{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.mode))

            return

        # 当前周期为空极端
        if self.cur_period.mode == Period.SHORT_EXTREME:
            # 空极端 =》多
            if self.line_rsi1[-1] > self.line_rsi1[-2] and min(self.line_rsi1[-5:-2]) <= 50 \
                    and bar.close_price > lastMid:

                self.cur_period = CtaPeriod(mode=Period.LONG, price=bar.close_price, pre_mode=Period.SHORT_EXTREME,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)

                self.write_log(u'{} 角度下极限低位反弹转折,Atan:{}, RSI:{}=>{},周期:{}=>{}'.
                               format(bar.datetime, self.cur_atan, self.line_rsi1[-2], self.line_rsi1[-1],
                                      self.cur_period.pre_mode, self.cur_period.mode))
                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)

            # 空极端=》空
            elif self.line_rsi1[-1] > self.line_rsi1[-2] and bar.close_price < lastMid:
                self.cur_period = CtaPeriod(mode=Period.SHORT, price=bar.close_price, pre_mode=Period.SHORT_EXTREME,
                                            dt=bar.datetime)
                self.period_list.append(self.cur_period)
                self.write_log(u'{} 角度下加速放缓，Atan:{},RSI:{}=>{}, ,周期：{}=>{}'.
                               format(bar.datetime, self.cur_atan, self.line_rsi1[-2], self.line_rsi1[-1],
                                      self.cur_period.pre_mode, self.cur_period.mode))
                if self.cb_on_period:
                    self.cb_on_period(self.cur_period)

            # 保持空极端趋势
            else:
                self.write_log(u'{} 角度向下加速,Atan:{},周期维持:{}'.
                               format(bar.datetime, self.cur_atan, self.cur_period.mode))

            return

    def __count_skd(self):
        """
        改良得多空线(类似KDJ，RSI）
        :param bar:
        :return:
        """
        if not self.para_active_skd:
            return

        data_len = max(self.para_skd_fast_len * 2, self.para_skd_fast_len + 20)
        if self.bar_len < data_len:
            return

        # 计算最后一根Bar的RSI指标
        last_rsi = ta.RSI(self.close_array[-data_len:], self.para_skd_fast_len)[-1]
        # 添加到lineSkdRSI队列
        if len(self.line_skd_rsi) > self.max_hold_bars:
            del self.line_skd_rsi[0]
        self.line_skd_rsi.append(last_rsi)

        if len(self.line_skd_rsi) < self.para_skd_slow_len:
            return

        # 计算最后根的最高价/最低价
        rsi_HHV = max(self.line_skd_rsi[-self.para_skd_slow_len:])
        rsi_LLV = min(self.line_skd_rsi[-self.para_skd_slow_len:])

        # 计算STO
        if rsi_HHV == rsi_LLV:
            sto = 0
        else:
            sto = 100 * (last_rsi - rsi_LLV) / (rsi_HHV - rsi_LLV)
        sto_len = len(self.line_skd_sto)
        if sto_len > self.max_hold_bars:
            del self.line_skd_sto[0]
        self.line_skd_sto.append(sto)

        # 根据STO，计算SK = EMA(STO,5)
        if sto_len < 5:
            return
        sk = ta.EMA(np.array(self.line_skd_sto, dtype=float), 5)[-1]
        sk = round(sk, self.round_n)
        if len(self.line_sk) > self.max_hold_bars:
            del self.line_sk[0]
        self.line_sk.append(sk)

        if len(self.line_sk) < 3:
            return

        sd = ta.EMA(np.array(self.line_sk, dtype=float), 3)[-1]
        sd = round(sd, self.round_n)
        if len(self.line_sd) > self.max_hold_bars:
            del self.line_sd[0]
        self.line_sd.append(sd)

        if len(self.line_sd) < 2:
            return

        for t in self.skd_top_list[-1:]:
            t['bars'] += 1

        for b in self.skd_buttom_list[-1:]:
            b['bars'] += 1

        #  记录所有SK的顶部和底部
        # 峰(顶部)
        if self.line_sk[-1] < self.line_sk[-2] and self.line_sk[-3] < self.line_sk[-2]:
            t = {}
            t['type'] = u'T'
            t['sk'] = self.line_sk[-2]
            t['price'] = max([self.high_array[-4:]])
            t['time'] = self.line_bar[-1].datetime
            t['bars'] = 0
            if len(self.skd_top_list) > self.max_hold_bars:
                del self.skd_top_list[0]
            self.skd_top_list.append(t)
            if self.cur_skd_count > 0:
                # 检查是否有顶背离
                if self.is_skd_divergence(direction=Direction.LONG):
                    self.cur_skd_divergence = -1

        # 谷(底部)
        elif self.line_sk[-1] > self.line_sk[-2] and self.line_sk[-3] > self.line_sk[-2]:
            b = {}
            b['type'] = u'B'
            b['sk'] = self.line_sk[-2]
            b['price'] = min([bar.low_price for bar in self.line_bar[-4:]])
            b['time'] = self.line_bar[-1].datetime
            b['bars'] = 0
            if len(self.skd_buttom_list) > self.max_hold_bars:
                del self.skd_buttom_list[0]
            self.skd_buttom_list.append(b)
            if self.cur_skd_count < 0:
                # 检查是否有底背离
                if self.is_skd_divergence(direction=Direction.SHORT):
                    self.cur_skd_divergence = 1

        # 判断是否金叉和死叉
        if self.line_sk[-1] > self.line_sk[-2] \
                and self.line_sk[-2] < self.line_sd[-2] \
                and self.line_sk[-1] > self.line_sd[-1]:
            golden_cross = True
        else:
            golden_cross = False

        if self.line_sk[-1] < self.line_sk[-2] \
                and self.line_sk[-2] > self.line_sd[-2] \
                and self.line_sk[-1] < self.line_sd[-1]:
            dead_cross = True
        else:
            dead_cross = False

        if self.cur_skd_count <= 0:
            if golden_cross:
                # 金叉
                self.cur_skd_count = 1
                self.cur_skd_cross = (self.line_sk[-1] + self.line_sk[-2] + self.line_sd[-1] + self.line_sd[-2]) / 4
                self.rt_skd_count = self.cur_skd_count
                self.rt_skd_cross = self.cur_skd_cross
                if self.rt_skd_cross_price == 0 or self.cur_price < self.rt_skd_cross_price:
                    self.rt_skd_cross_price = self.cur_price
                self.cur_skd_cross_price = self.cur_price
                if self.cur_skd_divergence < 0:
                    # 若原来是顶背离，消失
                    self.cur_skd_divergence = 0

            else:  # if self.line_sk[-1] < self.line_sk[-2]:
                # 延续死叉
                self.cur_skd_count -= 1
                # 取消实时的数据
                self.rt_skd_count = 0
                self.rt_skd_cross = 0
                self.rt_skd_cross_price = 0

                # 延续顶背离
                if self.cur_skd_divergence < 0:
                    self.cur_skd_divergence -= 1
            return

        elif self.cur_skd_count >= 0:
            if dead_cross:
                self.cur_skd_count = -1
                self.cur_skd_cross = (self.line_sk[-1] + self.line_sk[-2] + self.line_sd[-1] + self.line_sd[-2]) / 4
                self.rt_skd_count = self.cur_skd_count
                self.rt_skd_cross = self.cur_skd_cross
                if self.rt_skd_cross_price == 0 or self.cur_price > self.rt_skd_cross_price:
                    self.rt_skd_cross_price = self.cur_price
                self.cur_skd_cross_price = self.cur_price

                # 若原来是底背离，消失
                if self.cur_skd_divergence > 0:
                    self.cur_skd_divergence = 0

            else:
                # 延续金叉
                self.cur_skd_count += 1

                # 取消实时的数据
                self.rt_skd_count = 0
                self.rt_skd_cross = 0
                self.rt_skd_cross_price = 0

                # 延续底背离
                if self.cur_skd_divergence > 0:
                    self.cur_skd_divergence += 1

    def __get_2nd_item(self, line):
        """
        获取第二个合适的选项
        :param line:
        :return:
        """
        bars = 0
        for item in reversed(line):
            bars += item['bars']
            if bars > 5:
                return item

        return line[0]

    def is_skd_divergence(self, direction, runtime=False):
        """
        检查是否有背离
        :param:direction，多：检查是否有顶背离，空，检查是否有底背离
        :return:
        """
        if len(self.skd_top_list) < 2 or len(self.skd_buttom_list) < 2 or self._rt_sk is None or self._rt_sd is None:
            return False

        t1 = self.skd_top_list[-1]
        t2 = self.__get_2nd_item(self.skd_top_list[:-1])
        b1 = self.skd_buttom_list[-1]
        b2 = self.__get_2nd_item(self.skd_buttom_list[:-1])

        if runtime:
            # 峰(顶部)
            if self._rt_sk < self.line_sk[-1] and self.line_sk[-2] < self.line_sk[-1]:
                t1 = {}
                t1['type'] = u'T'
                t1['sk'] = self.line_sk[-1]
                t1['price'] = max(self.high_array[-4:])
                t1['time'] = self.line_bar[-1].datetime
                t1['bars'] = 0
                t2 = self.__get_2nd_item(self.skd_top_list)
            # 谷(底部)
            elif self._rt_sk > self.line_sk[-1] and self.line_sk[-2] > self.line_sk[-1]:
                b1 = {}
                b1['type'] = u'B'
                b1['sk'] = self.line_sk[-1]
                b1['price'] = min(self.low_array[-4:])
                b1['time'] = self.line_bar[-1].datetime
                b1['bars'] = 0
                b2 = self.__get_2nd_item(self.skd_buttom_list)

        # 检查顶背离
        if direction == Direction.LONG:
            t1_price = t1.get('price', 0)
            t2_price = t2.get('price', 0)
            t1_sk = t1.get('sk', 0)
            t2_sk = t2.get('sk', 0)
            b1_sk = b1.get('sk', 0)

            t2_t1_price_rate = ((t1_price - t2_price) / t2_price) if t2_price != 0 else 0
            t2_t1_sk_rate = ((t1_sk - t2_sk) / t2_sk) if t2_sk != 0 else 0
            # 背离：价格创新高，SK指标没有创新高
            if t2_t1_price_rate > 0 and t2_t1_sk_rate < 0 and b1_sk > self.para_skd_high:
                return True

        elif direction == Direction.SHORT:
            b1_price = b1.get('price', 0)
            b2_price = b2.get('price', 0)
            b1_sk = b1.get('sk', 0)
            b2_sk = b2.get('sk', 0)
            t1_sk = t1.get('sk', 0)
            b2_b1_price_rate = ((b1_price - b2_price) / b2_price) if b2_price != 0 else 0
            b2_b1_sk_rate = ((b1_sk - b2_sk) / b2_sk) if b2_sk != 0 else 0
            # 背离：价格创新低，指标没有创新低
            if b2_b1_price_rate < 0 and b2_b1_sk_rate > 0 and t1_sk < self.para_skd_low:
                return True

        return False

    def rt_count_sk_sd(self):
        """
        计算实时SK/SD
        :return:
        """
        if not self.para_active_skd:
            return

        # 准备得数据长度
        data_len = max(self.para_skd_fast_len * 2, self.para_skd_fast_len + 20)
        if len(self.line_bar) < data_len:
            return

        # 收盘价 = 结算bar + 最后一个未结束得close
        close_list = self.close_array[-data_len:]
        close_list.append(self.line_bar[-1].close)
        # close_list = [x.close for x in self.lineBar[-data_len:]]

        # 计算最后得动态RSI值
        last_rsi = ta.RSI(self.close_array[-2 * self.para_skd_fast_len:], self.para_skd_fast_len)[-1]

        # 所有RSI值长度不足计算标准
        if len(self.line_skd_rsi) < self.para_skd_slow_len:
            return

        # 拼接RSI list
        rsi_list = self.line_skd_rsi[1 - self.para_skd_slow_len:]
        rsi_list.append(last_rsi)

        # 获取 RSI得最高/最低值
        rsi_HHV = max(rsi_list)
        rsi_LLV = min(rsi_list)

        # 计算动态STO
        if rsi_HHV == rsi_LLV:
            sto = 0
        else:
            sto = 100 * (last_rsi - rsi_LLV) / (rsi_HHV - rsi_LLV)

        sto_len = len(self.line_skd_sto)
        if sto_len < 5:
            self._rt_sk = self.line_sk[-1] if len(self.line_sk) > 0 else 0
            self._rt_sd = self.line_sd[-1] if len(self.line_sd) > 0 else 0
            return

        # 历史STO
        sto_list = self.line_skd_sto[:]
        sto_list.append(sto)

        self._rt_sk = ta.EMA(np.array(sto_list, dtype=float), 5)[-1]
        self._rt_sk = round(self._rt_sk, self.round_n)
        sk_list = self.line_sk[:]
        sk_list.append(self._rt_sk)
        if len(sk_list) < 5:
            self._rt_sd = self.line_sd[-1] if len(self.line_sd) > 0 else 0
        else:
            self._rt_sd = ta.EMA(np.array(sk_list, dtype=float), 3)[-1]
            self._rt_sd = round(self._rt_sd, self.round_n)

    def is_skd_has_risk(self, direction, dist=15, runtime=False):
        """
        检查SDK的方向风险
        :return:
        """
        if not self.para_active_skd or len(self.line_sk) < 2 or self._rt_sk is None:
            return False

        if runtime:
            sk = self._rt_sk
        else:
            sk = self.line_sk[-1]
        if direction == Direction.LONG and sk >= 100 - dist:
            return True

        if direction == Direction.SHORT and sk <= dist:
            return True

        return False

    def is_skd_high_dead_cross(self, runtime=False, high_skd=None):
        """
        检查是否高位死叉
        :return:
        """
        if not self.para_active_skd or len(self.line_sk) < self.para_skd_slow_len:
            return False

        if high_skd is None:
            high_skd = self.para_skd_high

        if runtime:
            # 兼容写法，如果老策略没有配置实时运行，又用到实时数据，就添加
            if self.rt_count_skd not in self.rt_funcs:
                self.write_log(u'skd_is_high_dead_cross(),添加rt_countSkd到实时函数中')
                self.rt_funcs.add(self.rt_count_skd)
                self.rt_count_sk_sd()
            if self._rt_sk is None or self._rt_sd is None:
                return False

            # 判断是否实时死叉
            dead_cross = self._rt_sk < self.line_sk[-1] and self.line_sk[-1] > self.line_sd[
                -1] and self._rt_sk < self._rt_sd

            # 实时死叉
            if self.cur_skd_count >= 0 and dead_cross:
                skd_last_cross = (self._rt_sk + self.line_sk[-1] + self._rt_sd + self.line_sd[-1]) / 4
                # 记录bar内首次死叉后的值:交叉值，价格
                if self.rt_skd_count >= 0:
                    self.rt_skd_count = -1
                    self.rt_skd_cross = skd_last_cross
                    self.rt_skd_cross_price = self.cur_price
                    # self.write_log(u'{} rt Dead Cross at:{} ,price:{}'
                    #                 .format(self.name, self.skd_rt_last_cross, self.skd_rt_cross_price))

                if skd_last_cross > high_skd:
                    return True

        # 非实时，高位死叉
        if self.cur_skd_count < 0 and self.cur_skd_cross > high_skd:
            return True

        return False

    def is_skd_low_golden_cross(self, runtime=False, low_skd=None):
        """
        检查是否低位金叉
        :return:
        """
        if not self.para_active_skd or len(self.line_sk) < self.para_skd_slow_len:
            return False
        if low_skd is None:
            low_skd = self.para_skd_low

        if runtime:
            # 兼容写法，如果老策略没有配置实时运行，又用到实时数据，就添加
            if self.rt_count_skd not in self.rt_funcs:
                self.write_log(u'skd_is_low_golden_cross添加rt_countSkd到实时函数中')
                self.rt_funcs.add(self.rt_count_skd)
                self.rt_count_sk_sd()

            if self._rt_sk is None or self._rt_sd is None:
                return False
            # 判断是否金叉和死叉
            golden_cross = self._rt_sk > self.line_sk[-1] and self.line_sk[-1] < self.line_sd[
                -1] and self._rt_sk > self._rt_sd

            if self.cur_skd_count <= 0 and golden_cross:
                # 实时金叉
                skd_last_cross = (self._rt_sk + self.line_sk[-1] + self._rt_sd + self.line_sd[-1]) / 4

                if self.rt_skd_count <= 0:
                    self.rt_skd_count = 1
                    self.rt_skd_cross = skd_last_cross
                    self.rt_skd_cross_price = self.cur_price
                    # self.write_log(u'{} rt Gold Cross at:{} ,price:{}'
                    #                 .format(self.name, self.skd_rt_last_cross, self.skd_rt_cross_price))
                if skd_last_cross < low_skd:
                    return True

        # 非实时低位金叉
        if self.cur_skd_count > 0 and self.cur_skd_cross < low_skd:
            return True

        return False

    def rt_count_skd(self):
        """
        实时计算 SK,SD值，并且判断计算是否实时金叉/死叉
        :return:
        """
        if self.para_active_skd:
            # 计算实时指标 rt_SK, rt_SD
            self.rt_count_sk_sd()

            # 计算 实时金叉/死叉
            self.is_skd_high_dead_cross(runtime=True, high_skd=0)
            self.is_skd_low_golden_cross(runtime=True, low_skd=100)

    @property
    def rt_sk(self):
        self.check_rt_funcs(self.rt_count_skd)
        if self._rt_sk is None and len(self.line_sk) > 0:
            return self.line_sk[-1]
        return self._rt_sk

    @property
    def rt_sd(self):
        self.check_rt_funcs(self.rt_count_skd)
        if self._rt_sd is None and len(self.line_sd) > 0:
            return self.line_sd[-1]
        return self._rt_sd

    def __count_yb(self):
        """某种趋势线"""

        if not self.para_active_yb:
            return

        if self.para_yb_len < 1:
            return

        if self.para_yb_ref < 1:
            self.write_log(u'参数 self.inputYbRef:{}不能低于1'.format(self.para_yb_ref))
            return

        # 1、lineBar满足长度才执行计算
        # if len(self.lineBar) < 4 * self.inputYbLen:
        #    self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算YB 需要：{1}'.
        #                     format(len(self.lineBar), 4 * self.inputYbLen))
        #    return

        ema_len = min(self.bar_len, self.para_yb_len)
        if ema_len < 3:
            self.write_log(u'数据未充分,当前Bar数据数量：{0}'.
                           format(len(self.line_bar)))
            return
        # 3、获取前InputN周期(不包含当前周期）的K线
        bar_mid3_ema10 = ta.EMA(self.mid3_array[-ema_len * 4:], ema_len)[-1]
        bar_mid3_ema10 = round(float(bar_mid3_ema10), self.round_n)

        if len(self.line_yb) > self.max_hold_bars:
            del self.line_yb[0]

        self.line_yb.append(bar_mid3_ema10)

        if len(self.line_yb) < self.para_yb_ref + 1:
            return

        if self.line_yb[-1] > self.line_yb[-1 - self.para_yb_ref]:
            self.cur_yb_count = self.cur_yb_count + 1 if self.cur_yb_count >= 0 else 1
        else:
            self.cur_yb_count = self.cur_yb_count - 1 if self.cur_yb_count <= 0 else -1

    def rt_count_yb(self):
        """
        实时计算黄蓝
        :return:
        """
        if not self.para_active_yb:
            return
        if self.para_yb_len < 1:
            return
        if self.para_yb_ref < 1:
            self.write_log(u'参数 self.inputYbRef:{}不能低于1'.format(self.para_yb_ref))
            return

        ema_len = min(len(self.line_bar), self.para_yb_len)
        if ema_len < 3:
            self.write_log(u'数据未充分,当前Bar数据数量：{0}'.
                           format(len(self.line_bar)))
            return
        # 3、获取前InputN周期(包含当前周期）的K线
        list_mid3 = [x.mid3 for x in self.line_bar[-ema_len * 4:-1]]
        last_bar_mid3 = (self.line_bar[-1].close + self.line_bar[-1].high + self.line_bar[-1].low) / 3
        list_mid3.append(last_bar_mid3)
        bar_mid3_ema10 = ta.EMA(np.array(list_mid3, dtype=float), ema_len)[-1]
        self._rt_yb = round(float(bar_mid3_ema10), self.round_n)

    @property
    def rt_yb(self):
        self.check_rt_funcs(self.rt_count_yb)
        if self._rt_yb is None and len(self.line_yb) > 0:
            return self.line_yb[-1]
        return self._rt_yb

    def __count_golden_section(self):
        """
        重新计算黄金分割线
        :return:
        """
        if self.para_golden_n < 0:
            return
        if self.bar_len < 2:
            return
        bar_len = min(self.para_golden_n, self.bar_len)

        hhv = max(self.high_array[-bar_len:])
        llv = min(self.low_array[-bar_len:])

        self.cur_p192 = hhv - (hhv - llv) * 0.192
        self.cur_p382 = hhv - (hhv - llv) * 0.382
        self.cur_p500 = (hhv + llv) / 2
        self.cur_p618 = hhv - (hhv - llv) * 0.618
        self.cur_p809 = hhv - (hhv - llv) * 0.809

        # 根据最小跳动取整
        self.cur_p192 = round_to(self.cur_p192, self.price_tick)
        self.cur_p382 = round_to(self.cur_p382, self.price_tick)
        self.cur_p500 = round_to(self.cur_p500, self.price_tick)
        self.cur_p618 = round_to(self.cur_p618, self.price_tick)
        self.cur_p809 = round_to(self.cur_p809, self.price_tick)

    def __count_area(self, bar):
        """计算布林和MA的区域"""
        if not self.para_active_area:
            return

        if len(self.line_ma1) < 2 or len(self.line_boll_middle) < 2:
            return

        last_area = self.area_list[-1] if len(self.area_list) > 0 else None
        new_area = None
        # 判断做多/做空，判断在那个区域
        # 做多：均线（169）向上，且中轨在均线上方(不包含金叉死叉点集)
        # 做空：均线（169）向下，且中轨在均线下方（不包含金叉死叉点集）

        if self.line_boll_middle[-1] > self.line_ma1[-1] > self.line_ma1[-2]:
            # 做多
            if self.line_boll_middle[-1] >= bar.close_price >= max(self.line_ma1[-1], self.line_boll_lower[-1]):
                # 判断 A 的区域 ( ma169或下轨 ~ 中轨)
                new_area = Area.LONG_A
            elif self.line_boll_upper[-1] >= bar.close_price > self.line_boll_middle[-1]:
                # 判断 B 的区域( 中轨 ~ 上轨)
                new_area = Area.LONG_B
            elif self.line_boll_upper[-1] < bar.close_price:
                # 判断 C 的区域( 上轨~ )
                new_area = Area.LONG_C
            elif max(self.line_ma1[-1], self.line_boll_lower[-1]) > bar.close_price >= min(self.line_ma1[-1],
                                                                                           self.line_boll_lower[-1]):
                # 判断 D 的区域( 下轨~均线~ )
                new_area = Area.LONG_D
            elif min(self.line_boll_lower[-1], self.line_ma1[-1]) > bar.close_price:
                # 判断 E 的区域( ~下轨或均线下方 )
                new_area = Area.LONG_E
        elif self.line_ma1[-2] > self.line_ma1[-1] > self.line_boll_middle[-1]:
            # 做空
            if self.line_boll_middle[-1] <= bar.close_price <= min(self.line_ma1[-1], self.line_boll_upper[-1]):
                # 判断 A 的区域 ( ma169或上轨 ~ 中轨)
                new_area = Area.SHORT_A
            elif self.line_boll_lower[-1] <= bar.close_price < self.line_boll_middle[-1]:
                # 判断 B 的区域( 下轨~中轨 )
                new_area = Area.SHORT_B
            elif self.line_boll_lower[-1] > bar.close_price:
                # 判断 C 的区域( ~下轨 )
                new_area = Area.SHORT_C
            elif min(self.line_ma1[-1], self.line_boll_upper[-1]) < bar.close_price <= max(self.line_ma1[-1],
                                                                                           self.line_boll_upper[-1]):
                # 判断 D 的区域(均线~上轨 )
                new_area = Area.SHORT_D
            elif max(self.line_ma1[-1], self.line_boll_upper[-1]) < bar.close_price:
                # 判断 E 的区域( 上轨~ )
                new_area = Area.SHORT_E

        if last_area != new_area:
            self.area_list.append(new_area)
            self.cur_area = new_area
            self.pre_area = last_area

    def __count_bias(self):
        """乖离率"""
        # BIAS1 : (CLOSE-MA(CLOSE,L1))/MA(CLOSE,L1)*100;
        if not (self.para_bias_len > 0 or self.para_bias2_len > 0 or self.para_bias3_len > 0):
            # 不计算
            return

        if self.para_bias_len > 0:
            if self.bar_len < min(6, self.para_bias_len) + 1:
                self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算Bias需要：{1}'.
                               format(len(self.line_bar), min(14, self.para_bias_len) + 1))
            else:

                BiasLen = min(self.para_bias_len, self.bar_len)

                # 计算BIAS
                m = np.mean(self.close_array[-BiasLen:])
                bias = (self.close_array[-1] - m) / m * 100
                self.line_bias.append(bias)  # 中轨
                if len(self.line_bias) > self.max_hold_bars:
                    del self.line_bias[0]

                self.cur_bias = bias

        if self.para_bias2_len > 0:
            if self.bar_len < min(6, self.para_bias2_len) + 1:
                self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算Bias2需要：{1}'.
                               format(len(self.line_bar), min(14, self.para_bias2_len) + 1))
            else:
                Bias2Len = min(self.bar_len, self.para_bias2_len)
                # 计算BIAS2
                m = np.mean(self.close_array[-Bias2Len:])
                bias2 = (self.close_array[-1] - m) / m * 100
                self.line_bias2.append(bias2)  # 中轨
                if len(self.line_bias2) > self.max_hold_bars:
                    del self.line_bias2[0]
                self.cur_bias2 = bias2

        if self.para_bias3_len > 0:
            if self.bar_len < min(6, self.para_bias3_len) + 1:
                self.write_log(u'数据未充分,当前Bar数据数量：{0}，计算Bias3需要：{1}'.
                               format(len(self.line_bar), min(14, self.para_bias3_len) + 1))
            else:
                Bias3Len = min(self.bar_len, self.para_bias3_len)
                # 计算BIAS3
                m = np.mean(self.close_array[-Bias3Len:])
                bias3 = (self.close_array[-1] - m) / m * 100
                self.line_bias3.append(bias3)  # 中轨
                if len(self.line_bias3) > self.max_hold_bars:
                    del self.line_bias3[0]

                self.cur_bias3 = bias3

    def rt_count_bias(self):
        """实时计算乖离率"""
        if not (self.para_bias_len > 0 or self.para_bias2_len or self.para_bias3_len > 0):  # 不计算
            return

        if self.para_bias_len > 0:
            if self.bar_len < min(6, self.para_bias_len) + 1:
                return
            else:
                biasLen = min(self.bar_len, self.para_bias_len) - 1

                # 计算BIAS
                m = np.mean(np.append(self.close_array[-biasLen:], [self.cur_price]))
                self._rt_bias = (self.cur_price - m) / m * 100

        if self.para_bias2_len > 0:
            if self.bar_len < min(6, self.para_bias2_len) + 1:
                return
            else:
                biasLen = min(self.bar_len, self.para_bias2_len) - 1

                # 计算BIAS
                m = np.mean(np.append(self.close_array[-biasLen:], [self.cur_price]))
                self._rt_bias2 = (self.cur_price - m) / m * 100

        if self.para_bias3_len > 0:
            if self.bar_len < min(6, self.para_bias3_len) + 1:
                return
            else:
                biasLen = min(self.bar_len, self.para_bias3_len) - 1

            # 计算BIAS
            m = np.mean(np.append(self.close_array[-biasLen:], [self.cur_price]))
            self._rt_bias3 = (self.cur_price - m) / m * 100

    @property
    def rt_bias(self):
        self.check_rt_funcs(self.rt_count_bias)
        if self._rt_bias is None and len(self.line_bias) > 0:
            return self.line_bias[-1]
        return self._rt_bias

    @property
    def rt_bias2(self):
        self.check_rt_funcs(self.rt_count_bias)
        if self._rt_bias2 is None and len(self.line_bias2) > 0:
            return self.line_bias2[-1]
        return self._rt_bias2

    @property
    def rt_bias3(self):
        self.check_rt_funcs(self.rt_count_bias)
        if self._rt_bias3 is None and len(self.line_bias3) > 0:
            return self.line_bias3[-1]
        return self._rt_bias3

    # ----------------------------------------------------------------------
    def write_log(self, content):
        """记录CTA日志"""
        self.strategy.write_log(u'[' + self.name + u']' + content)

    def append_data(self, file_name, dict_data, field_names=None):
        """
        添加数据到csv文件中
        :param file_name:  csv的文件全路径
        :param dict_data:  OrderedDict
        :return:
        """
        if not isinstance(dict_data, dict):
            print(u'{}.append_data，输入数据不是dict'.format(self.name), file=sys.stderr)
            return

        dict_fieldnames = list(dict_data.keys()) if field_names is None else field_names

        if not isinstance(dict_fieldnames, list):
            print(u'{}append_data，输入字段不是list'.format(self.name), file=sys.stderr)
            return
        try:
            if not os.path.exists(file_name):
                self.write_log(u'create csv file:{}'.format(file_name))
                with open(file_name, 'a', encoding='utf8', newline='') as csvWriteFile:
                    writer = csv.DictWriter(f=csvWriteFile, fieldnames=dict_fieldnames, dialect='excel')
                    self.write_log(u'write csv header:{}'.format(dict_fieldnames))
                    writer.writeheader()
                    writer.writerow(dict_data)
            else:
                dt = dict_data.get('datetime', None)
                if dt is not None:
                    dt_index = dict_fieldnames.index('datetime')
                    last_dt = self.get_csv_last_dt(file_name=file_name, dt_index=dt_index,
                                                   line_length=sys.getsizeof(dict_data) / 8 + 1)
                    if last_dt is not None and dt < last_dt:
                        print(u'新增数据时间{}比最后一条记录时间{}早，不插入'.format(dt, last_dt))

                        return

                with open(file_name, 'a', encoding='utf8', newline='') as csvWriteFile:
                    writer = csv.DictWriter(f=csvWriteFile, fieldnames=dict_fieldnames, dialect='excel',
                                            extrasaction='ignore')
                    writer.writerow(dict_data)
        except Exception as ex:
            print(u'{}.append_data exception:{}/{}'.format(self.name, str(ex), traceback.format_exc()))

    def get_csv_last_dt(self, file_name, dt_index=0, line_length=1000):
        """
        获取csv文件最后一行的日期数据(第dt_index个字段必须是 '%Y-%m-%d %H:%M:%S'格式
        :param file_name:文件名
        :param line_length: 行数据的长度
        :return: None，文件不存在，或者时间格式不正确
        """
        with open(file_name, 'r') as f:
            f_size = os.path.getsize(file_name)
            if f_size < line_length:
                line_length = f_size
            f.seek(f_size - line_length)  # 移动到最后1000个字节
            for row in f.readlines()[-1:]:

                datas = row.split(',')
                if len(datas) > dt_index + 1:
                    try:
                        last_dt = datetime.strptime(datas[dt_index], '%Y-%m-%d %H:%M:%S')
                        return last_dt
                    except Exception:
                        return None
            return None

    def is_shadow_line(self, open, high, low, close, direction, shadow_rate, wave_rate):
        """
        是否上影线/下影线
        :param open: 开仓价
        :param high: 最高价
        :param low: 最低价
        :param close: 收盘价
        :param direction: 方向（多/空）
        :param shadown_rate: 上影线比例（百分比）
        :param wave_rate:振幅（百分比）
        :return:
        """
        if close <= 0 or high <= low or shadow_rate <= 0 or wave_rate <= 0:
            self.write_log(u'是否上下影线,参数出错.close={}, high={},low={},shadow_rate={},wave_rate={}'
                           .format(close, high, low, shadow_rate, wave_rate))
            return False

        # 振幅 = 高-低 / 收盘价 百分比
        cur_wave_rate = round(100 * float((high - low) / close), 2)

        # 上涨时，判断上影线
        if direction == Direction.LONG:
            # 上影线比例 = 上影线（高- max（开盘，收盘））/ 当日振幅=（高-低）
            cur_shadow_rate = round(100 * float((high - max(open, close)) / (high - low)), 2)
            if cur_wave_rate >= wave_rate and cur_shadow_rate >= shadow_rate:
                return True

        # 下跌时，判断下影线
        elif direction == Direction.SHORT:
            cur_shadow_rate = round(100 * float((min(open, close) - low) / (high - low)), 2)
            if cur_wave_rate >= wave_rate and cur_shadow_rate >= shadow_rate:
                return True

        return False

    def is_end_tick(self, tick_dt):
        """
        根据短合约和时间，判断是否为最后一个tick
        :param tick_dt:
        :return:
        """
        if self.is_7x24:
            return False

        # 中金所，只有11：30 和15：15，才有最后一个tick
        if self.underly_symbol in MARKET_ZJ:
            if (tick_dt.hour == 11 and tick_dt.minute == 30) or (tick_dt.hour == 15 and tick_dt.minute == 15):
                return True
            else:
                return False

        # 其他合约(上期所/郑商所/大连）
        if 2 <= tick_dt.hour < 23:
            if (tick_dt.hour == 10 and tick_dt.minute == 15) \
                    or (tick_dt.hour == 11 and tick_dt.minute == 30) \
                    or (tick_dt.hour == 15 and tick_dt.minute == 00) \
                    or (tick_dt.hour == 2 and tick_dt.minute == 30):
                return True
            else:
                return False

        # 夜盘1:30收盘
        if self.underly_symbol in NIGHT_MARKET_SQ2 and tick_dt.hour == 1 and tick_dt.minute == 00:
            return True

        # 夜盘23:00收盘
        if self.underly_symbol in NIGHT_MARKET_23 and tick_dt.hour == 23 and tick_dt.minute == 00:
            return True

        return False

    def get_data(self):
        """
        获取数据，供外部系统查看
        :return: dict:
        {
        name: []， # k线名称
        type: k线类型：second, minute , hour, day, week
        interval: 周期
        symbol: 品种,
        main_indicators: [] , 主图指标
        sub_indicators: []， 附图指标
        start_time: '', 开始时间
        end_time: ''，结束时间
        data_list: list of dict
        }

        """
        # 根据参数，生成主图指标和附图指标
        indicators = {}

        # 前高/前低（通道）
        if isinstance(self.para_pre_len, int) and self.para_pre_len > 0:
            indicator = {
                'name': 'preHigh{}'.format(self.para_pre_len),
                'attr_name': 'line_pre_high',
                'is_main': True,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
            indicator = {
                'name': 'preLow{}'.format(self.para_pre_len),
                'attr_name': 'line_pre_low',
                'is_main': True,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # EMA 均线（主图）
        if isinstance(self.para_ema1_len, int) and self.para_ema1_len > 0:
            indicator = {
                'name': 'EMA{}'.format(self.para_ema1_len),
                'attr_name': 'line_ema1',
                'is_main': True,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
        if isinstance(self.para_ema2_len, int) and self.para_ema2_len > 0:
            indicator = {
                'name': 'EMA{}'.format(self.para_ema2_len),
                'attr_name': 'line_ema2',
                'is_main': True,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
        if isinstance(self.para_ema3_len, int) and self.para_ema3_len > 0:
            indicator = {
                'name': 'EMA{}'.format(self.para_ema3_len),
                'attr_name': 'line_ema3',
                'is_main': True,
                'type': 'line'
            }
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # MA 均线 （主图）
        if isinstance(self.para_ma1_len, int) and self.para_ma1_len > 0:
            indicator = {
                'name': 'MA{}'.format(self.para_ma1_len),
                'attr_name': 'line_ma1',
                'is_main': True,
                'type': 'line'
            }
            indicators.update({indicator.get('name'): copy.copy(indicator)})
        if isinstance(self.para_ma2_len, int) and self.para_ma2_len > 0:
            indicator = {
                'name': 'MA{}'.format(self.para_ma2_len),
                'attr_name': 'line_ma2',
                'is_main': True,
                'type': 'line'
            }
            indicators.update({indicator.get('name'): copy.copy(indicator)})
        if isinstance(self.para_ma3_len, int) and self.para_ma3_len > 0:
            indicator = {
                'name': 'MA{}'.format(self.para_ma3_len),
                'attr_name': 'line_ma3',
                'is_main': True,
                'type': 'line'
            }
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 动能指标（附图）
        if isinstance(self.para_dmi_len, int) and self.para_dmi_len > 0:
            indicator = {
                'name': 'ADX({})'.format(self.para_dmi_len),
                'attr_name': 'line_adx',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
            indicator = {
                'name': 'ADXR({})'.format(self.para_dmi_len),
                'attr_name': 'line_adxr',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 平均波动率 (副图）
        if isinstance(self.para_atr1_len, int) and self.para_atr1_len > 0:
            indicator = {
                'name': 'ATR{}'.format(self.para_atr1_len),
                'attr_name': 'line_atr1',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
        if isinstance(self.para_atr2_len, int) and self.para_atr2_len > 0:
            indicator = {
                'name': 'ATR{}'.format(self.para_atr2_len),
                'attr_name': 'line_atr2',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
        if isinstance(self.para_atr3_len, int) and self.para_atr3_len > 0:
            indicator = {
                'name': 'ATR{}'.format(self.para_atr3_len),
                'attr_name': 'line_atr3',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 平均成交量（ 副图）
        if isinstance(self.para_vol_len, int) and self.para_vol_len > 0:
            indicator = {
                'name': 'AgvVol({})'.format(self.para_vol_len),
                'attr_name': 'line_vol_ma',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 摆动指标（附图）
        if isinstance(self.para_rsi1_len, int) and self.para_rsi1_len > 0:
            indicator = {
                'name': 'RSI({})'.format(self.para_rsi1_len),
                'attr_name': 'line_rsi1',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
        if isinstance(self.para_rsi2_len, int) and self.para_rsi2_len > 0:
            indicator = {
                'name': 'RSI({})'.format(self.para_rsi2_len),
                'attr_name': 'line_rsi2',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 市场波动指数 （副图）
        if isinstance(self.para_cmi_len, int) and self.para_cmi_len > 0:
            indicator = {
                'name': 'CMI({})'.format(self.para_cmi_len),
                'attr_name': 'line_cmi',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 布林通道 (主图)
        if (isinstance(self.para_boll_len, int) and self.para_boll_len > 0) or (
                isinstance(self.para_boll_tb_len, int) and self.para_boll_tb_len > 0):
            boll_len = max(self.para_boll_tb_len, self.para_boll_len)
            indicator = {
                'name': 'BOLL({})_U'.format(boll_len),
                'attr_name': 'line_boll_upper',
                'is_main': True,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
            indicator = {
                'name': 'BOLL({})_M'.format(boll_len),
                'attr_name': 'line_boll_middle',
                'is_main': True,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
            indicator = {
                'name': 'BOLL({})_L'.format(boll_len),
                'attr_name': 'line_boll_lower',
                'is_main': True,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 布林通道 (主图)
        if (isinstance(self.para_boll2_len, int) and self.para_boll2_len > 0) or (
                isinstance(self.para_boll2_tb_len, int) and self.para_boll2_tb_len > 0):
            boll_len = max(self.para_boll2_tb_len, self.para_boll2_len)
            indicator = {
                'name': 'BOLL_U'.format(boll_len),
                'attr_name': 'line_boll2_upper',
                'is_main': True,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
            indicator = {
                'name': 'BOLL({})_M'.format(boll_len),
                'attr_name': 'line_boll2_middle',
                'is_main': True,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
            indicator = {
                'name': 'BOLL({})_L'.format(boll_len),
                'attr_name': 'line_boll2_lower',
                'is_main': True,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # KDJ 摆动指标 (副图)
        if (isinstance(self.para_kdj_len, int) and self.para_kdj_len > 0) or (
                isinstance(self.para_kdj_tb_len, int) and self.para_kdj_tb_len > 0):
            kdj_len = max(self.para_kdj_tb_len, self.para_kdj_len)
            indicator = {
                'name': 'KDJ({})_K'.format(kdj_len),
                'attr_name': 'line_k',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
            indicator = {
                'name': 'KDJ({})_D'.format(kdj_len),
                'attr_name': 'line_d',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # CCI 动能指标 (副图)
        if isinstance(self.para_cci_len, int) and self.para_cci_len > 0:
            indicator = {
                'name': 'CCI({})'.format(self.para_cci_len),
                'attr_name': 'line_cci',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        if isinstance(self.para_macd_fast_len, int) and self.para_macd_fast_len > 0:
            indicator = {
                'name': 'Dif',
                'attr_name': 'line_dif',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
            indicator = {
                'name': 'Dea',
                'attr_name': 'line_dea',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
            indicator = {
                'name': 'Macd',
                'attr_name': 'line_macd',
                'is_main': False,
                'type': 'bar'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 卡尔曼均线
        if self.para_active_kf:
            indicator = {
                'name': 'KF',
                'attr_name': 'line_state_mean',
                'is_main': True,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 摆动指标
        if self.para_active_skd:
            indicator = {
                'name': 'SK',
                'attr_name': 'line_sk',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
            indicator = {
                'name': 'SD',
                'attr_name': 'line_sd',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 重心线
        if self.para_active_yb:
            indicator = {
                'name': 'YB',
                'attr_name': 'line_yb',
                'is_main': True,
                'type': 'bar'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 抛物线 (主图指标)
        if self.para_sar_step > 0:
            indicator = {
                'name': 'SAR',
                'attr_name': 'line_sar',
                'is_main': True,
                'type': 'point'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 乖离率(附图）
        if self.para_bias_len > 0:
            indicator = {
                'name': 'Bias{}'.format(self.para_bias_len),
                'attr_name': 'line_bias',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})
        if self.para_bias2_len > 0:
            indicator = {
                'name': 'Bias{}'.format(self.para_bias2_len),
                'attr_name': 'line_bias2',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        if self.para_bias3_len > 0:
            indicator = {
                'name': 'Bias{}'.format(self.para_bias3_len),
                'attr_name': 'line_bias3',
                'is_main': False,
                'type': 'line'}
            indicators.update({indicator.get('name'): copy.copy(indicator)})

        # 逐一填充数据到pandas
        bar_list = [OrderedDict({'datetime': bar.datetime,
                                 'open': bar.open_price, 'high': bar.high_price, 'low': bar.low_price,
                                 'close': bar.close_price,
                                 'volume': bar.volume, 'open_interest': bar.open_interest}) for bar in self.line_bar]

        bar_len = len(bar_list)
        if bar_len == 0:
            return {}

        # 补充数据
        main_indicators = []
        sub_indicators = []
        for k, v in indicators.items():
            attr_name = v.get('attr_name', None)
            if attr_name is None or not hasattr(self, attr_name):
                continue
            attr_data_list = getattr(self, attr_name, [])
            data_len = len(attr_data_list)
            if data_len == 0:
                continue
            if data_len > bar_len:
                attr_data_list = attr_data_list[-bar_len:]
            elif data_len < bar_len:
                first_data = attr_data_list[0]
                attr_data_list = [first_data] * (bar_len - data_len) + attr_data_list

            # 逐一增加到bar_list的每个dict中
            for i in range(bar_len):
                bar_list[i].update({k: attr_data_list[i]})

            if v.get('is_main', False):
                main_indicators.append({'name': k, 'type': v.get('type')})
            else:
                sub_indicators.append({'name': k, 'type': v.get('type')})

        return {
            'name': self.name,
            'type': self.interval,
            'interval': self.bar_interval,
            'symbol': self.line_bar[-1].vt_symbol,
            'main_indicators': list(sorted(main_indicators, key=lambda x: x['name'])),
            'sub_indicators': list(sorted(sub_indicators, key=lambda x: x['name'])),
            'start_time': bar_list[0].get('datetime'),
            'end_time': bar_list[-1].get('datetime'),
            'data_list': bar_list}


class CtaMinuteBar(CtaLineBar):
    """
    分钟级别K线
    对比基类CtaLineBar
    """

    def __init__(self, strategy, cb_on_bar, setting=None):

        if 'interval' in setting:
            del setting['interval']

        super(CtaMinuteBar, self).__init__(strategy, cb_on_bar, setting)

        # 一天内bar的数量累计
        self.bars_count = 0
        self.minutes_adjust = -15
        self.m1_bars_count = 0

    def __getstate__(self):
        """移除Pickle dump()时不支持的Attribute"""
        return super().__getstate__()

    def __setstate__(self, state):
        """Pickle load()"""
        self.__dict__.update(state)

    def restore(self, state):
        """从Pickle中恢复数据"""
        for key in state.__dict__.keys():
            self.__dict__[key] = state.__dict__[key]

    def init_properties(self):
        """
        初始化内部变量
        :return:
        """
        self.init_param_list()

        # 输入参数
        self.name = u'MinuteBar'
        self.mode = self.TICK_MODE  # 缺省为tick模式
        self.interval = Interval.MINUTE  # 分钟级别周期
        self.bar_interval = 5  # 缺省为5分钟周期

        self.minute_interval = self.bar_interval  # 1分钟

    def add_bar(self, bar, bar_is_completed=False, bar_freq=1):
        """
        予以外部初始化程序增加bar
        :param bar:
        :param bar_is_completed: 插入的bar，其周期与K线周期一致，就设为True
         :param bar_freq, bar对象得frequency
        :return:
        """
        # self.write_log("addBar(): {}, o={}, h={}, l={}, c={}, v={}".format(bar.datetime.strftime("%Y%m%d %H:%M:%S"),
        #     bar.open, bar.high, bar.low_price, bar.close_price, bar.volume
        # ))
        if bar.trading_day is None:
            if self.is_7x24:
                bar.trading_day = bar.datetime.strftime('%Y-%m-%d')
            else:
                bar.trading_day = get_trading_date(bar.datetime)

        # 更新最后价格
        self.cur_price = bar.close_price
        self.cur_datetime = bar.datetime

        bar_len = len(self.line_bar)

        if bar_len == 0:
            self.line_bar.append(bar)
            self.cur_trading_day = bar.trading_day
            # self.m1_bars_count += bar_freq
            if bar_is_completed:
                # self.m1_bars_count = 0
                self.on_bar(bar)
            # 计算当前加入的 bar的1分钟，属于当日的第几个1分钟
            minutes_passed = (bar.datetime - datetime.strptime(bar.datetime.strftime('%Y-%m-%d'),
                                                               '%Y-%m-%d')).total_seconds() / 60
            # 计算，当前的bar，属于当日的第几个bar
            self.bars_count = int(minutes_passed / self.bar_interval)
            return

        # 与最后一个BAR的时间比对，判断是否超过K线的周期
        lastBar = self.line_bar[-1]

        is_new_bar = False
        if bar_is_completed:
            is_new_bar = True

        minutes_passed = (bar.datetime - datetime.strptime(bar.datetime.strftime('%Y-%m-%d'),
                                                           '%Y-%m-%d')).total_seconds() / 60
        if self.underly_symbol in MARKET_ZJ:
            if int(bar.datetime.strftime('%H%M')) > 1130 and int(bar.datetime.strftime('%H%M')) < 1600:
                # 扣除11:30到13:00的中场休息的90分钟
                minutes_passed = minutes_passed - 90
        else:
            if int(bar.datetime.strftime('%H%M')) > 1015 and int(bar.datetime.strftime('%H%M')) <= 1130:
                # 扣除10:15到10:30的中场休息的15分钟
                minutes_passed = minutes_passed - 15
            elif int(bar.datetime.strftime('%H%M')) > 1130 and int(bar.datetime.strftime('%H%M')) < 1600:
                # 扣除(10:15到10:30的中场休息的15分钟)&(11:30到13:30的中场休息的120分钟)
                minutes_passed = minutes_passed - 135
        bars_passed = int(minutes_passed / self.bar_interval)

        # 不在同一交易日，推入新bar
        if self.cur_trading_day != bar.trading_day:
            is_new_bar = True
            self.cur_trading_day = bar.trading_day
            self.bars_count = bars_passed
            # self.write_log("drawLineBar(): {}, m1_bars_count={}".format(bar.datetime.strftime("%Y%m%d %H:%M:%S"),
            #                                                              self.m1_bars_count))
        else:
            if bars_passed != self.bars_count:
                is_new_bar = True
                self.bars_count = bars_passed

                # self.write_log("addBar(): {}, bars_count={}".format(bar.datetime.strftime("%Y%m%d %H:%M:%S"),
                #                                                      self.bars_count))

        # 数字货币，如果bar的前后距离，超过周期，重新开启一个新的bar
        if self.is_7x24 and (bar.datetime - lastBar.datetime).total_seconds() >= 60 * self.bar_interval:
            is_new_bar = True

        if is_new_bar:
            new_bar = copy.deepcopy(bar)
            # 添加新的bar
            self.line_bar.append(new_bar)
            # 将上一个Bar推送至OnBar事件
            self.on_bar(lastBar)
        else:
            # 更新最后一个bar
            # 此段代码，针对一部分短周期生成长周期的k线更新，如3根5分钟k线，合并成1根15分钟k线。
            lastBar.close_price = bar.close_price
            lastBar.high_price = max(lastBar.high_price, bar.high_price)
            lastBar.low_price = min(lastBar.low_price, bar.low_price)
            lastBar.volume = lastBar.volume + bar.volume
            lastBar.open_interest = bar.open_interest

            # 实时计算
            self.rt_executed = False

    # ----------------------------------------------------------------------
    def generate_bar(self, tick):
        """
        生成 line Bar
        :param tick:
        :return:
        """

        bar_len = len(self.line_bar)

        minutes_passed = (tick.datetime - datetime.strptime(tick.datetime.strftime('%Y-%m-%d'),
                                                            '%Y-%m-%d')).total_seconds() / 60
        if self.underly_symbol in MARKET_ZJ:
            if int(tick.datetime.strftime('%H%M')) > 1130 and int(tick.datetime.strftime('%H%M')) < 1600:
                # 扣除11:30到13:00的中场休息的90分钟
                minutes_passed = minutes_passed - 90
        else:
            if int(tick.datetime.strftime('%H%M')) > 1015 and int(tick.datetime.strftime('%H%M')) <= 1130:
                # 扣除10:15到10:30的中场休息的15分钟
                minutes_passed = minutes_passed - 15
            elif int(tick.datetime.strftime('%H%M')) > 1130 and int(tick.datetime.strftime('%H%M')) < 1600:
                # 扣除(10:15到10:30的中场休息的15分钟)&(11:30到13:30的中场休息的120分钟)
                minutes_passed = minutes_passed - 135
        bars_passed = int(minutes_passed / self.bar_interval)

        # 保存第一个K线数据
        if bar_len == 0:
            self.first_tick(tick)
            self.bars_count = bars_passed
            return

        # 清除480周期前的数据，
        if bar_len > self.max_hold_bars:
            del self.line_bar[0]

        # 与最后一个BAR的时间比对，判断是否超过K线周期
        lastBar = self.line_bar[-1]
        is_new_bar = False

        endtick = False
        if not self.is_7x24:
            # 处理日内的间隔时段最后一个tick，如10:15分，11:30分，15:00 和 2:30分
            if (tick.datetime.hour == 10 and tick.datetime.minute == 15) \
                    or (tick.datetime.hour == 11 and tick.datetime.minute == 30) \
                    or (tick.datetime.hour == 15 and tick.datetime.minute == 00) \
                    or (tick.datetime.hour == 2 and tick.datetime.minute == 30):
                endtick = True

            # 夜盘1:30收盘
            if self.underly_symbol in NIGHT_MARKET_SQ2 and tick.datetime.hour == 1 and tick.datetime.minute == 00:
                endtick = True

            # 夜盘23:00收盘
            if self.underly_symbol in NIGHT_MARKET_23 and tick.datetime.hour == 23 and tick.datetime.minute == 00:
                endtick = True

            if endtick is True:
                return

        is_new_bar = False

        # 不在同一交易日，推入新bar
        if self.cur_trading_day != tick.trading_day:
            # self.write_log('{} drawLineBar() new_bar,{} curTradingDay:{},tick.trading_day:{} bars_count={}'
            #                 .format(self.name, tick.datetime.strftime("%Y-%m-%d %H:%M:%S"), self.cur_trading_day,
            #                         tick.trading_day, self.bars_count))

            is_new_bar = True
            self.cur_trading_day = tick.trading_day
            self.bars_count = bars_passed

        else:
            # 同一交易日，看过去了多少个周期的Bar
            if bars_passed != self.bars_count:
                is_new_bar = True
                self.bars_count = bars_passed
                # self.write_log('{} drawLineBar() new_bar,{} bars_count={}'
                #                 .format(self.name, tick.datetime, self.bars_count))

        self.last_minute = tick.datetime.minute

        # 数字货币市场，分钟是连续的，所以只判断是否取整，或者与上一根bar的距离
        if self.is_7x24:
            if (
                    tick.datetime.minute % self.bar_interval == 0 and tick.datetime.minute != lastBar.datetime.minute) or (
                    tick.datetime - lastBar.datetime).total_seconds() > self.bar_interval * 60:
                # self.write_log('{} drawLineBar() new_bar,{} lastbar:{}, bars_count={}'
                #                 .format(self.name, tick.datetime, lastBar.datetime,
                #                         self.bars_count))
                is_new_bar = True

        if is_new_bar:
            # 创建并推入新的Bar
            self.first_tick(tick)
            # 触发OnBar事件
            self.on_bar(lastBar)
        else:
            # 更新当前最后一个bar
            self.barFirstTick = False

            # 更新最高价、最低价、收盘价、成交量
            lastBar.high_price = max(lastBar.high, tick.last_price)
            lastBar.low_price = min(lastBar.low_price, tick.last_price)
            lastBar.close_price = tick.last_price
            lastBar.open_interest = tick.open_interest
            lastBar.volume += tick.volume

            # 更新Bar的颜色
            if lastBar.close_price > lastBar.open_price:
                lastBar.color = Color.RED
            elif lastBar.close_price < lastBar.open_price:
                lastBar.color = Color.BLUE
            else:
                lastBar.color = Color.EQUAL

            # 实时计算
            self.rt_executed = False


class CtaHourBar(CtaLineBar):
    """
    小时级别K线
    对比基类CtaLineBar
    """

    def __init__(self, strategy, cb_on_bar, setting=None):

        if 'interval' in setting:
            del setting['interval']

        super(CtaHourBar, self).__init__(strategy, cb_on_bar, setting)

        # bar内得分钟数量累计
        self.m1_bars_count = 0
        self.last_minute = None

    def __getstate__(self):
        """移除Pickle dump()时不支持的Attribute"""
        return super().__getstate__()

    def __setstate__(self, state):
        """Pickle load()"""
        self.__dict__.update(state)

    def restore(self, state):
        """从Pickle中恢复数据"""
        for key in state.__dict__.keys():
            self.__dict__[key] = state.__dict__[key]

    def init_properties(self):
        """
        初始化内部变量
        :return:
        """
        self.init_param_list()

        # 输入参数
        self.name = u'HourBar'
        self.mode = self.TICK_MODE  # 缺省为tick模式
        self.interval = Interval.HOUR  # 小时级别周期
        self.bar_interval = 1  # 缺省为小时周期

        self.minute_interval = 60  #

    def add_bar(self, bar, bar_is_completed=False, bar_freq=1):
        """
        予以外部初始化程序增加bar
        :param bar:
        :param bar_is_completed: 插入的bar，其周期与K线周期一致，就设为True
         :param bar_freq, bar对象得frequency
        :return:
        """
        if bar.trading_day is None:
            if self.is_7x24:
                bar.trading_day = bar.date
            else:
                bar.trading_day = get_trading_date(bar.datetime)

        # 更新最后价格
        self.cur_price = bar.close_price
        self.cur_datetime = bar.datetime
        bar_len = len(self.line_bar)

        if bar_len == 0:
            self.line_bar.append(bar)
            self.cur_trading_day = bar.trading_day
            self.m1_bars_count += bar_freq
            if bar_is_completed:
                self.m1_bars_count = 0
                self.on_bar(bar)
            return

        # 与最后一个BAR的时间比对，判断是否超过K线的周期
        lastBar = self.line_bar[-1]

        is_new_bar = False
        if bar_is_completed:
            is_new_bar = True

        if self.cur_trading_day is None:
            self.cur_trading_day = bar.trading_day

        if self.cur_trading_day != bar.trading_day:
            is_new_bar = True
            self.cur_trading_day = bar.trading_day

        if self.is_7x24:
            if (bar.datetime - lastBar.datetime).total_seconds() >= 3600 * self.bar_interval:
                is_new_bar = True
                self.cur_trading_day = bar.trading_day

        if self.m1_bars_count + bar_freq > 60 * self.bar_interval:
            is_new_bar = True

        if is_new_bar:
            # 添加新的bar
            self.line_bar.append(bar)
            self.m1_bars_count = bar_freq
            # 将上一个Bar推送至OnBar事件
            self.on_bar(lastBar)

        else:
            # 更新最后一个bar
            # 此段代码，针对一部分短周期生成长周期的k线更新，如3根5分钟k线，合并成1根15分钟k线。
            lastBar.close_price = bar.close_price
            lastBar.high_price = max(lastBar.high_price, bar.high_price)
            lastBar.low_price = min(lastBar.low_price, bar.low_price)
            lastBar.volume = lastBar.volume + bar.volume
            lastBar.open_interest = bar.open_interest

            self.m1_bars_count += bar_freq

            # 实时计算
            self.rt_executed = False

        # ----------------------------------------------------------------------

    def generate_bar(self, tick):
        """
        生成 line Bar
        :param tick:
        :return:
        """

        bar_len = len(self.line_bar)

        # 保存第一个K线数据
        if bar_len == 0:
            self.first_tick(tick)
            return

        # 清除480周期前的数据，
        if bar_len > self.max_hold_bars:
            del self.line_bar[0]
        endtick = False
        if not self.is_7x24:
            # 处理日内的间隔时段最后一个tick，如10:15分，11:30分，15:00 和 2:30分
            if (tick.datetime.hour == 10 and tick.datetime.minute == 15) \
                    or (tick.datetime.hour == 11 and tick.datetime.minute == 30) \
                    or (tick.datetime.hour == 15 and tick.datetime.minute == 00) \
                    or (tick.datetime.hour == 2 and tick.datetime.minute == 30):
                endtick = True

            # 夜盘1:30收盘
            if self.underly_symbol in NIGHT_MARKET_SQ2 and tick.datetime.hour == 1 and tick.datetime.minute == 00:
                endtick = True

            # 夜盘23:00收盘
            if self.underly_symbol in NIGHT_MARKET_23 and tick.datetime.hour == 23 and tick.datetime.minute == 00:
                endtick = True

        # 与最后一个BAR的时间比对，判断是否超过K线周期
        lastBar = self.line_bar[-1]
        is_new_bar = False

        if self.last_minute is None:
            if tick.datetime.second == 0:
                self.m1_bars_count += 1
            self.last_minute = tick.datetime.minute

        # 不在同一交易日，推入新bar
        if self.cur_trading_day != tick.trading_day:
            is_new_bar = True
            # 去除分钟和秒数
            tick.datetime = datetime.strptime(tick.datetime.strftime('%Y-%m-%d %H:00:00'), '%Y-%m-%d %H:%M:%S')
            tick.time = tick.datetime.strftime('%H:%M:%S')
            self.last_minute = tick.datetime.minute
            self.cur_trading_day = tick.trading_day
            # self.write_log('{} drawLineBar() new_bar,{} curTradingDay:{},tick.trading_day:{}'
            #                 .format(self.name, tick.datetime.strftime("%Y-%m-%d %H:%M:%S"), self.cur_trading_day,
            #                         tick.trading_day))

        else:
            # 同一交易日，看分钟是否一致
            if tick.datetime.minute != self.last_minute and not endtick:
                self.m1_bars_count += 1
                self.last_minute = tick.datetime.minute

        if self.is_7x24:
            # 数字货币，用前后时间间隔
            if (tick.datetime - lastBar.datetime).total_seconds() >= 3600 * self.bar_interval:
                # self.write_log('{} drawLineBar() new_bar,{} - {} > 3600 * {} '
                #                 .format(self.name, tick.datetime.strftime("%Y-%m-%d %H:%M:%S"),
                #                         lastBar.datetime.strftime("%Y-%m-%d %H:%M:%S"),
                #                         self.barTimeInterval))
                is_new_bar = True
                # 去除分钟和秒数
                tick.datetime = datetime.strptime(tick.datetime.strftime('%Y-%m-%d %H:00:00'), '%Y-%m-%d %H:%M:%S')
                tick.time = tick.datetime.strftime('%H:%M:%S')
                if len(tick.trading_day) > 0:
                    self.cur_trading_day = tick.trading_day
                else:
                    self.cur_trading_day = tick.date
        else:
            # 国内期货,用bar累加
            if self.m1_bars_count > 60 * self.bar_interval:
                # self.write_log('{} drawLineBar() new_bar,{} {} > 60 * {} '
                #                 .format(self.name, tick.datetime.strftime("%Y-%m-%d %H:%M:%S"),
                #                         self.m1_bars_count,
                #                         self.barTimeInterval))
                is_new_bar = True
                # 去除秒数
                tick.datetime = datetime.strptime(tick.datetime.strftime('%Y-%m-%d %H:%M:00'), '%Y-%m-%d %H:%M:%S')
                tick.time = tick.datetime.strftime('%H:%M:%S')

        if is_new_bar:
            # 创建并推入新的Bar
            self.first_tick(tick)
            self.m1_bars_count = 1
            # 触发OnBar事件
            self.on_bar(lastBar)

        else:
            # 更新当前最后一个bar
            self.barFirstTick = False

            # 更新最高价、最低价、收盘价、成交量
            lastBar.high_price = max(lastBar.high_price, tick.last_price)
            lastBar.low_price = min(lastBar.low_price, tick.last_price)
            lastBar.close_price = tick.last_price
            lastBar.open_interest = tick.open_interest

            lastBar.volume += tick.volume

            # 更新Bar的颜色
            if lastBar.close_price > lastBar.open_price:
                lastBar.color = Color.RED
            elif lastBar.close_price < lastBar.open_price:
                lastBar.color = Color.BLUE
            else:
                lastBar.color = Color.EQUAL

            # 实时计算
            self.rt_executed = False

        if not endtick:
            self.lastTick = tick


class CtaDayBar(CtaLineBar):
    """
    日线级别K线(只支持1日线）
    """

    def __init__(self, strategy, cb_on_bar, setting=None):
        self.had_night_market = False  # 是否有夜市

        if 'interval' in setting:
            del setting['interval']

        if 'bar_interval' in setting:
            del setting['bar_interval']

        super(CtaDayBar, self).__init__(strategy, cb_on_bar, setting)

    def __getstate__(self):
        """移除Pickle dump()时不支持的Attribute"""
        return super().__getstate__()

    def __setstate__(self, state):
        """Pickle load()"""
        self.__dict__.update(state)

    def restore(self, state):
        """从Pickle中恢复数据"""
        for key in state.__dict__.keys():
            self.__dict__[key] = state.__dict__[key]

    def init_properties(self):
        """
        初始化内部变量
        :return:
        """
        self.init_param_list()

        # 输入参数
        self.name = u'DayBar'
        self.mode = self.TICK_MODE  # 缺省为tick模式
        self.interval = Interval.DAILY  # 日线级别周期
        self.bar_interval = 1  # 缺省为1天

        self.minute_interval = 60 * 24

    def add_bar(self, bar, bar_is_completed=False, bar_freq=1):
        """
        予以外部初始化程序增加bar
        :param bar:
        :param bar_is_completed: 插入的bar，其周期与K线周期一致，就设为True
        :param bar_freq, bar对象得frequency
        :return:
        """
        # 更新最后价格
        self.cur_price = bar.close_price
        self.cur_datetime = bar.datetime

        bar_len = len(self.line_bar)

        if bar_len == 0:
            new_bar = copy.deepcopy(bar)
            self.line_bar.append(new_bar)
            self.cur_trading_day = bar.trading_day if bar.trading_day is not None else bar.date
            if bar_is_completed:
                self.on_bar(bar)
            return

        # 与最后一个BAR的时间比对，判断是否超过K线的周期
        lastBar = self.line_bar[-1]
        self.cur_trading_day = bar.trading_day if bar.trading_day is not None else bar.date

        is_new_bar = False
        if bar_is_completed:
            is_new_bar = True

        # 夜盘时间判断（当前的bar时间在21点后，上一根Bar的时间在21点前
        if not self.is_7x24 and bar.datetime.hour >= 21 and lastBar.datetime.hour < 21:
            is_new_bar = True
            self.cur_trading_day = bar.trading_day if bar.trading_day is not None else bar.date

        # 日期判断
        if not is_new_bar and lastBar.trading_day != self.cur_trading_day:
            is_new_bar = True
            self.cur_trading_day = bar.trading_day if bar.trading_day is not None else bar.date

        if is_new_bar:
            # 添加新的bar
            new_bar = copy.deepcopy(bar)
            self.line_bar.append(new_bar)
            # 将上一个Bar推送至OnBar事件
            self.on_bar(lastBar)
        else:
            # 更新最后一个bar
            # 此段代码，针对一部分短周期生成长周期的k线更新，如3根5分钟k线，合并成1根15分钟k线。
            lastBar.close_price = bar.close_price
            lastBar.high_price = max(lastBar.high_price, bar.high_price)
            lastBar.low_price = min(lastBar.low_price, bar.low_price)
            lastBar.volume = lastBar.volume + bar.volume
            lastBar.open_interest = bar.open_interest

            # 实时计算
            self.rt_executed = False

    # ----------------------------------------------------------------------
    def generate_bar(self, tick):
        """
        生成 line Bar
        :param tick:
        :return:
        """

        bar_len = len(self.line_bar)

        # 保存第一个K线数据
        if bar_len == 0:
            self.first_tick(tick)
            return

        # 清除480周期前的数据，
        if bar_len > self.max_hold_bars:
            del self.line_bar[0]

        # 与最后一个BAR的时间比对，判断是否超过K线周期
        lastBar = self.line_bar[-1]

        is_new_bar = False

        # 交易日期不一致，新的交易日
        if len(tick.trading_day) > 0 and tick.trading_day != lastBar.trading_day:
            is_new_bar = True

        # 数字货币方面，如果当前tick 日期与bar的日期不一致.(取消，按照上面的统一处理，因为币安是按照UTC时间算的每天开始，ok是按照北京时间开始)
        # if self.is_7x24 and tick.date != lastBar.date:
        #    is_new_bar = True

        if is_new_bar:
            # 创建并推入新的Bar
            self.first_tick(tick)
            # 触发OnBar事件
            self.on_bar(lastBar)

        else:
            # 更新当前最后一个bar
            self.barFirstTick = False

            # 更新最高价、最低价、收盘价、成交量
            lastBar.high_price = max(lastBar.high_price, tick.last_price)
            lastBar.low_price = min(lastBar.low_price, tick.last_price)
            lastBar.close_price = tick.last_price
            lastBar.open_interest = tick.open_interest
            lastBar.volume += tick.volume

            # 更新Bar的颜色
            if lastBar.close_price > lastBar.open_price:
                lastBar.color = Color.RED
            elif lastBar.close_price < lastBar.open_price:
                lastBar.color = Color.BLUE
            else:
                lastBar.color = Color.EQUAL

            # 实时计算
            self.rt_executed = False

        self.lastTick = tick


class CtaWeekBar(CtaLineBar):
    """
    周线级别K线
    """

    def __init__(self, strategy, cb_on_bar, setting=None):
        self.had_night_market = False  # 是否有夜市

        if 'interval' in setting:
            del setting['interval']

        if 'bar_interval' in setting:
            del setting['bar_interval']

        super(CtaWeekBar, self).__init__(strategy, cb_on_bar, setting)

        # 使用周一作为周线时间
        self.use_monday = False
        # 开始的小时/分钟/秒
        self.bar_start_hour_dt = '21:00:00'

        if self.is_7x24:
            # 数字货币，使用周一的开始时间
            self.use_monday = True
            self.bar_start_hour_dt = '00:00:00'
        else:
            # 判断是否期货
            if self.underly_symbol is not None:
                if len(self.underly_symbol) <= 4:
                    # 是期货
                    if get_underlying_symbol(self.underly_symbol) in MARKET_DAY_ONLY:
                        # 日盘期货
                        self.use_monday = True
                        if get_underlying_symbol(self.underly_symbol) in MARKET_ZJ:
                            # 中金所
                            self.bar_start_hour_dt = '09:15:00'
                        else:
                            # 其他日盘期货
                            self.bar_start_hour_dt = '09:00:00'
                    else:
                        # 夜盘期货
                        self.use_monday = False
                        self.bar_start_hour_dt = '21:00:00'
                else:
                    # 可能是股票
                    self.use_monday = True
                    self.bar_start_hour_dt = '09:30:00'
            else:
                # 可能是股票
                self.use_monday = True
                self.bar_start_hour_dt = '09:30:00'

    def __getstate__(self):
        """移除Pickle dump()时不支持的Attribute"""
        return super().__getstate__()

    def __setstate__(self, state):
        """Pickle load()"""
        self.__dict__.update(state)

    def restore(self, state):
        """从Pickle中恢复数据"""
        for key in state.__dict__.keys():
            self.__dict__[key] = state.__dict__[key]

    def init_properties(self):
        """
        初始化内部变量
        :return:
        """

        self.init_param_list()

        # 输入参数
        self.name = u'WeekBar'
        self.mode = self.TICK_MODE  # 缺省为tick模式
        self.interval = Interval.WEEKLY  # 周线级别周期
        self.bar_interval = 1  # 为1周
        self.minute_interval = 60 * 24 * 7

    def add_bar(self, bar, bar_is_completed=False, bar_freq=1):
        """
        予以外部初始化程序增加bar
        :param bar:
        :param bar_is_completed: 插入的bar，其周期与K线周期一致，就设为True
        :param bar_freq, bar对象得frequency
        :return:

        # 国内期货,周线时间开始为周五晚上21点
        # 股票，周线开始时间为周一
        # 数字货币，周线的开始时间为周一

        """
        # 更新最后价格
        self.cur_price = bar.close_price
        self.cur_datetime = bar.datetime

        bar_len = len(self.line_bar)

        if bar_len == 0:
            new_bar = copy.deepcopy(bar)
            new_bar.datetime = self.get_bar_start_dt(bar.datetime)
            self.write_log(u'周线开始时间:{}=>{}'.format(bar.datetime, new_bar.datetime))
            self.line_bar.append(new_bar)
            self.cur_trading_day = bar.trading_day
            if bar_is_completed:
                self.on_bar(bar)
            return

        # 与最后一个BAR的时间比对，判断是否超过K线的周期
        lastBar = self.line_bar[-1]
        self.cur_trading_day = bar.trading_day

        is_new_bar = False
        if bar_is_completed:
            is_new_bar = True

        # 时间判断,与上一根Bar的时间，超过7天
        if (bar.datetime - lastBar.datetime).total_seconds() >= 60 * 60 * 24 * 7:
            is_new_bar = True
            self.cur_trading_day = bar.trading_day

        if is_new_bar:
            # 添加新的bar
            new_bar = copy.deepcopy(bar)
            new_bar.datetime = self.get_bar_start_dt(bar.datetime)
            self.write_log(u'新周线开始时间:{}=>{}'.format(bar.datetime, new_bar.datetime))
            self.line_bar.append(new_bar)
            # 将上一个Bar推送至OnBar事件
            self.on_bar(lastBar)
        else:
            # 更新最后一个bar
            # 此段代码，针对一部分短周期生成长周期的k线更新，如3根5分钟k线，合并成1根15分钟k线。
            lastBar.close_price = bar.close_price
            lastBar.high_price = max(lastBar.high_price, bar.high_price)
            lastBar.low_price = min(lastBar.low_price, bar.low_price)
            lastBar.volume = lastBar.volume + bar.volume

            lastBar.open_interest = bar.open_interest

            # 实时计算
            self.rt_executed = False

    def get_bar_start_dt(self, cur_dt):
        """获取当前时间计算的周线Bar开始时间"""

        if self.use_monday:
            # 使用周一. 例如当前是周二，weekday=1,相当于减去一天
            monday_dt = cur_dt.replace(hour=0, minute=0, second=0, microsecond=0) - timedelta(days=cur_dt.weekday())
            start_dt = datetime.strptime(monday_dt.strftime('%Y-%m-%d') + ' ' + self.bar_start_hour_dt,
                                         '%Y-%m-%d %H:%M:%S')
            return start_dt

        else:
            # 使用周五
            week_day = cur_dt.weekday()

            if week_day >= 5 or (week_day == 4 and cur_dt.hour > 20):
                # 周六或周天; 或者周五晚上21:00以后
                friday_dt = cur_dt.replace(hour=0, minute=0, second=0, microsecond=0) - timedelta(
                    days=cur_dt.weekday() - 4)
            else:
                # 周一~周五白天
                friday_dt = cur_dt.replace(hour=0, minute=0, second=0, microsecond=0) - timedelta(
                    days=cur_dt.weekday() + 2)

            friday_night_dt = datetime.strptime(friday_dt.strftime('%Y-%m-%d') + ' ' + self.bar_start_hour_dt,
                                                '%Y-%m-%d %H:%M:%S')
            return friday_night_dt

    # ----------------------------------------------------------------------
    def generate_bar(self, tick):
        """
        生成 line Bar
        :param tick:
        :return:
        """

        bar_len = len(self.line_bar)

        # 保存第一个K线数据
        if bar_len == 0:
            self.first_tick(tick)
            return

        # 清除480周期前的数据，
        if bar_len > self.max_hold_bars:
            del self.line_bar[0]

        # 与最后一个BAR的时间比对，判断是否超过K线周期
        lastBar = self.line_bar[-1]

        is_new_bar = False

        # 交易日期不一致，新的交易日
        if (tick.datetime - lastBar.datetime).total_seconds() >= 60 * 60 * 24 * 7:
            is_new_bar = True

        if is_new_bar:
            # 创建并推入新的Bar
            self.first_tick(tick)
            # 触发OnBar事件
            self.on_bar(lastBar)

        else:
            # 更新当前最后一个bar
            self.barFirstTick = False

            # 更新最高价、最低价、收盘价、成交量
            lastBar.high_price = max(lastBar.high_price, tick.last_price)
            lastBar.low_price = min(lastBar.low_price, tick.last_price)
            lastBar.close_price = tick.last_price
            lastBar.open_interest = tick.open_interest
            # 更新日内总交易量，和bar内交易量
            lastBar.volume += tick.volume

            # 更新Bar的颜色
            if lastBar.close_price > lastBar.open_price:
                lastBar.color = Color.RED
            elif lastBar.close_price < lastBar.open_price:
                lastBar.color = Color.BLUE
            else:
                lastBar.color = Color.EQUAL

            # 实时计算
            self.rt_executed = False

        self.last_tick = tick

