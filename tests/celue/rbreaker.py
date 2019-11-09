from datetime import time
from vnpy.app.cta_strategy import (
    CtaTemplate,
    OptimizationSetting,
    StopOrder,
    TickData,
    BarData,
    TradeData,
    OrderData,
    BarGenerator,
    ArrayManager,
)

# 1 、根据昨日的OHLC计算今天的6个目标价位
## 突破买入价（Bbreak）
## 观察卖出价（Ssetup）
## 反转卖出价（Sebter）
## 反转买入价（Bsetup）
## 观察买入价（Bstup）
## 突破卖出价（Sbreak）


"""
原始策略逻辑
R-Breaker策略逻辑
 

R-Breaker的策略逻辑由以下4部分构成：

1）计算6个目标价位

根据昨日的开高低收价位计算出今日的6个目标价位，按照价格高低依次是：

突破买入价（Bbreak）
观察卖出价（Ssetup）
反转卖出价（Senter）
反转买入价（Benter）
观察买入价（Bsetup）
突破卖出价（Sbreak）
 

他们的计算方法如下：（其中a、b、c、d为策略参数）

观察卖出价（Ssetup）= High + a * (Close – Low)
观察买入（Bsetup）= Low – a * (High – Close)
反转卖出价（Senter）= b / 2 * (High + Low) – c * Low
反转买入价（Benter）= b / 2 * (High + Low) – c * High
突破卖出价（Sbreak）= Ssetup - d * (Ssetup – Bsetup)
突破买入价（Bbreak）= Bsetup + d * (Ssetup – Bsetup)
 

description

2）设计委托逻辑

趋势策略情况：

若价格>突破买入价，开仓做多；
若价格<突破卖出价，开仓做空；
 

反转策略情况：

若日最高价>观察卖出价，然后下跌导致价格<反转卖出价，开仓做空或者反手（先平仓再反向开仓）做空；
若日最低价<观察买入价，然后上涨导致价格>反转买入价，开仓做多或者反手（先平仓再反向开仓）做多；
 

3）设定相应的止盈止损。

 

4）日内策略要求收盘前平仓。
+++++++++++++++++++++++++++++++++++++++++++++++
实际上R-Breaker策略可以拆分成趋势策略和反转策略。下面分别对这对2种策略逻辑进行优化：

1）趋势策略：

若当前x分钟的最高价>观察卖出价，认为它具有上升趋势，在突破买入价挂上买入开仓的停止单；
若当前x分钟的最低价<观察买入价，认为它具有下跌趋势，在突破卖出价挂上买入开仓的停止单；
开仓后，使用固定百分比移动止损离场；
增加过滤条件：为防止横盘行情导致不断的开平仓，日内每次开仓买入开仓（卖出开仓）委托的价位都比上一次更高（更低）；
收盘前，必须平调所持有的仓位。


2）反转策略：

若当前x分钟的最高价>观察卖出价，认为它已经到了当日阻力位，可能发生行情反转，在反转卖出价挂上卖出开仓的停止单；
若当前x分钟的最低价>观察买入价，认为它已经到了当日支撑位，可能发生行情反转，在反转买入价挂上买入开仓的停止单；(这里存疑，我认为应该是小于观察买入价)
开仓后，使用固定百分比移动止损离场；
收盘前，必须平调所持有的仓位。"""


class RBraekStrategy(CtaTemplate):
    """"""

    author = "Guo"

    setup_coef = 0.25  # 观察买入价参数 a
    break_coef = 0.2  # 突破卖出价参数 d
    enter_coef_1 = 1.07  # 入场参数1
    enter_coef_2 = 0.07  # 入场参数2
    fixed_size = 1  # 买入手数
    donchian_window = 30  # 唐奇安通道参数

    trailing_long = 0.4  # 多头止损比例
    trailing_short = 0.4  # 空头止损比例

    buy_break = 0  # 突破买入价
    sell_setup = 0  # 观察卖出价
    sell_enter = 0  # 反转卖出价
    buy_enter = 0  # 反转买入价
    buy_setup = 0  # 观察买入价
    sell_break = 0  # 突破卖出价

    intra_trade_high = 0  # 交易时的最高价
    intra_trade_low = 0  # 交易时的最低价

    exit_time = time(hour=14, minute=55)  # 清仓时间

    parameters = ['setup_coef',
                  'break_coef',
                  'enter_coef_1',
                  'enter_coef_2',
                  'fixed_size',
                  'donchian_window',
                  ]

    variables = ['buy_break',
                 'sell_setup',
                 'sell_enter',
                 'buy_enter',
                 'buy_setup',
                 'sell_break'
                 ]

    def __init__(self, cta_engine, strategy_name, vt_symbol, setting):
        """"""
        self.bg = BarGenerator(self.on_bar)
        self.am = ArrayManager()
        self.bars = []

    def on_init(self):
        """初始化"""
        self.write_log('策略初始化')

    def on_start(self):
        """启动策略"""
        self.write_log('策略启动')

    def on_stop(self):
        """策略停止"""
        self.write_log('策略停止')

    def on_tick(self, tick: TickData):
        """更新tick数据"""
        self.load_tick(tick)

    def on_bar(self, bar: BarData):
        """更新K线数据"""
        self.cancel_all()  # 取消所有订单

        am = self.am
        am.update_bar(bar)  # 更新K线
        if not am.inited:
            return
