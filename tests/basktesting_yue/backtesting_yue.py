from collections import defaultdict
from datetime import date, datetime, timedelta
from typing import Callable
from itertools import product
from functools import lru_cache
from time import time
import multiprocessing
#empyrical风险指标计算模块
from empyrical import (sortino_ratio,annual_volatility,cagr,conditional_value_at_risk,downside_risk,stability_of_timeseries,tail_ratio,value_at_risk)
import random
import os
import numpy as np
np.seterr(divide='ignore',invalid='ignore')
import matplotlib.pyplot as plt
import scipy.stats as scs
import seaborn as sns
from pandas import DataFrame
from deap import creator, base, tools, algorithms
import redis
import zlib
import pickle
REDIS_CLIENT =redis.Redis("localhost",12580)

from vnpy.trader.constant import (Direction, Offset, Exchange, Interval, Status,OrderType)
from vnpy.trader.database import database_manager
from vnpy.trader.object import OrderData, TradeData, BarData, TickData
from vnpy.trader.utility import round_to

from vnpy.app.cta_strategy.base import (BacktestingMode, EngineType, STOPORDER_PREFIX, StopOrder, StopOrderStatus)
from vnpy.app.cta_strategy.template import CtaTemplate
sns.set_style('whitegrid')
creator.create('FitnessMax', base.Fitness, weights=(1.0,))      #优化方向1求最大值，-1求最小值
creator.create('Individual', list, fitness=creator.FitnessMax)
#年总交易日
TRADING_DAY = 365#365，252
class OptimizationSetting:
    '''
    回测优化设置
    '''

    def __init__(self):
        ''''''
        self.params = {}
        self.target_name = ''

    def add_parameter(self, name: str, start: float, end: float = None, step: float = None ):
        """
        设置优化参数
        """
        if not end and not step:
            self.params[name] = [start]
            return

        if start >= end:
            print('参数优化起始点必须小于终止点')
            return

        if step <= 0:
            print('参数优化步进必须大于0')
            return

        value = start
        value_list = []

        while value <= end:
            value_list.append(value)
            value += step

        self.params[name] = value_list

    def set_target(self, target_name: str):
        """设置优化目标"""
        self.target_name = target_name

    def generate_setting(self):

        keys = self.params.keys()
        values = self.params.values()
        products = list(product(*values))

        settings = []
        for p in products:
            setting = dict(zip(keys, p))
            settings.append(setting)

        return settings
    
    def generate_setting_ga(self):
        '''''' 
        settings_ga = []
        settings = self.generate_setting()     
        for d in settings:            
            param = [tuple(i) for i in d.items()]
            settings_ga.append(param)
        return settings_ga

class BacktestingEngine:
    """
   回测引擎
    """
    engine_type = EngineType.BACKTESTING
    gateway_name = 'BACKTESTING'

    def __init__(self):
        self.vt_symbol = ''
        self.symbol = ''
        self.exchange = None
        self.start = None
        self.end = None
        self.rate = 0
        self.slippage = 0
        self.size = 1
        self.price_tick = 0
        self.capital = 100000
        self.strategy_class = None
        self.strategy = None
        self.tick: TickData
        self.bar: BarData
        self.datetime = None

        self.interval = None
        self.days = 0
        self.callback = None
        self.history_data = []

        self.stop_order_count = 0
        self.stop_orders = {}
        self.active_stop_orders = {}

        self.limit_order_count = 0
        self.limit_orders = {}
        self.active_limit_orders = {}

        self.trade_count = 0
        self.trades = {}

        self.logs = []

        self.daily_results = {}
        self.daily_df = None
        #保存回测结果，优化结果路径
        self.result_path = None
        # 持仓盁亏初始化
        self.long_avg_cost = 0          #多头持仓均价
        self.short_avg_cost = 0         #空头持仓均价
        self.long_pos = 0               #多头仓位
        self.short_pos = 0              #空头仓位
        self.long_profit_total = 0      #多头总盈亏
        self.short_profit_total = 0     #空头总盈亏
        #净值指标
        self.net_value = 0
        self.net_value_list = []
    def set_capital(self,capital):
        """设置初始资金"""
        self.capital = capital
    def clear_data(self):
        '''
        Clear all data of last backtesting.
        '''
        self.strategy = None
        self.tick = None
        self.bar = None
        self.datetime = None

        self.stop_order_count = 0
        self.stop_orders.clear()
        self.active_stop_orders.clear()

        self.limit_order_count = 0
        self.limit_orders.clear()
        self.active_limit_orders.clear()

        self.trade_count = 0
        self.trades.clear()

        self.logs.clear()
        self.daily_results.clear()

    def set_parameters(self, vt_symbol: str, start: datetime, rate: float, slippage: float, size: float, price_tick: float, capital: int = 0, end: datetime = None, mode: BacktestingMode = BacktestingMode.BAR, ):
        ''''''
        self.mode = mode
        self.vt_symbol = vt_symbol
        if self.mode == BacktestingMode.BAR:
            self.interval = Interval.MINUTE
        self.rate = rate
        self.slippage = slippage
        self.size = size
        self.price_tick = price_tick
        self.start = start

        self.symbol, exchange_str = self.vt_symbol.split('_')
        self.exchange = Exchange(exchange_str)

        if capital:
            self.capital = capital

        if end:
            self.end = end

        if mode:
            self.mode = mode
    def add_strategy(self, strategy_class: type, setting: dict):
        ''''''
        self.strategy_class = strategy_class     
        self.strategy = strategy_class(self, strategy_class.__name__, self.vt_symbol, setting )
        #初始化策略盈亏参数
        self.strategy.capital = 0       #初始资金
        self.strategy.balance = self.capital       #总资金    
        self.strategy.long_pos = 0      #多头仓位
        self.strategy.short_pos = 0     #空头仓位
        self.strategy.long_profit = 0   #多头收益
        self.strategy.short_profit = 0  #空头收益
        self.strategy.size = self.size      #每手乘数
        self.strategy.price_tick = self.price_tick      #最小价格变动
        if setting:
            unactive_param = [loss_param for loss_param in list(setting.keys()) if loss_param not in self.strategy.parameters]
            assert not unactive_param,f"不在策略参数列表内的回测参数:{unactive_param}" 
    def load_data(self):
        """加载历史数据"""
        self.output("开始加载历史数据")
        if not self.end:
            self.end = datetime.now()
        self.history_data.clear()       #载入数据前清除历史数据
        assert self.start < self.end,"回测开始时间必须小于结束时间，请核实！"
        if self.mode == BacktestingMode.BAR:
            self.history_data = load_bar_data(self.symbol, self.exchange, self.interval, self.start, self.end)
        else:
            self.history_data = load_tick_data(self.symbol, self.exchange, self.start, self.end)

        self.output(f"历史数据加载完成，数据量：{len(self.history_data)}")

    def run_backtesting(self):
        """回放历史数据"""
        if self.mode == BacktestingMode.BAR:
            func = self.new_bar
        else:
            func = self.new_tick

        self.strategy.on_init()

        # Use the first [days] of history data for initializing strategy
        day_count = 0
        ix = 0
        for ix, data in enumerate(self.history_data):
            if self.datetime and data.datetime.day != self.datetime.day:
                day_count += 1
                if day_count >= self.days:
                    break
            self.datetime = data.datetime
            self.callback(data)

        self.strategy.inited = True
        self.output('策略初始化完成')

        self.strategy.on_start()
        self.strategy.trading = True
        self.output('开始回放历史数据')
        #回放history_data数据到on_tick/on_bar
        for data in self.history_data[ix:]:
            func(data)
        self.output('历史数据回放结束')

    def calculate_result(self):
        """
        返回daily_df:DataFrame
        """
        self.output('开始计算逐日盯市盈亏')

        if not self.trades:
            self.output('成交记录为空，无法计算')
            return

        # Add trade data into daily reuslt.
        for trade in self.trades.values():
            trade_date = trade.datetime.date()
            daily_result = self.daily_results[trade_date]
            daily_result.add_trade(trade)

        # Calculate daily result by iteration.
        pre_close = 0
        start_pos = 0

        for daily_result in self.daily_results.values():
            daily_result.calculate_pnl(pre_close, start_pos, self.size, self.rate, self.slippage )

            pre_close = daily_result.close_price
            start_pos = daily_result.end_pos

        # Generate dataframe
        results = defaultdict(list)

        for daily_result in self.daily_results.values():
            for key, value in daily_result.__dict__.items():
                results[key].append(value)

        self.daily_df = DataFrame.from_dict(results).set_index('date')

        self.output('逐日盯市盈亏计算完成')
        return self.daily_df
    #----------------------------------------------------------------------
    def statistics_status(self,array):
        """返回array均值，标准差，偏度，峰度"""
        stats = scs.describe(array)
        return stats[2],np.sqrt(stats[3]),stats[4],stats[5]  
    #----------------------------------------------------------------------
    def calculate_statistics(self, df: DataFrame = None,strategy_name=None,write_result=True):
        """计算回测结果"""
        from pyecharts.charts import (Bar,Line,Graph,Gauge,Page)#柱状图，折线图，关系图，仪表盘,多图同表
        from pyecharts import options as opts
        from pyecharts.render import make_snapshot 
        from snapshot_phantomjs import snapshot
        self.output('开始计算策略统计指标')      
        if df is None:
            #初始化统计变量
            start_date = ''
            end_date = ''
            total_days = 0
            profit_days = 0
            loss_days = 0
            end_balance = 0
            max_drawdown = 0
            max_drawdown_percent = 0
            total_net_pnl = 0
            daily_net_pnl = 0
            total_commission = 0
            daily_commission = 0
            total_slippage = 0
            daily_slippage = 0
            total_turnover = 0
            daily_turnover = 0
            total_trade_count = 0
            daily_trade_count = 0
            total_return = 0
            annual_return = 0
            return_mean = 0
            return_std = 0
            return_skew = 0
            return_kurt = 0
            sharpe_ratio = 0
            calmar_ratio = 0
            return_drawdown = 0
            return_drawdown_ratio = 0
            sortino_info = 0
            annual_volatility_info = 0
            cagr_info = 0
            annual_downside_risk = 0
            c_var = 0
            var_info = 0
            calmar_ratio = 0
            stability_return = 0
            tail_ratio_info = 0
        else:
            # Calculate balance related time series data
            trades_list =[]          #成交明细列表
            df['balance'] = df['net_pnl'].cumsum() + self.capital                               #总资金
            df['return'] = (np.log(df['balance']) - np.log(df['balance'].shift(1))).fillna(0)   #净收益率
            df['highlevel'] = (df['balance'].rolling( min_periods=1, window=len(df), center=False).max())   #净值高点
            df['drawdown'] = df['balance'] - df['highlevel']
            df['ddpercent'] = df['drawdown'] / df['highlevel'] * 100                            #回撤百分比
            # Calculate statistics value
            start_date = df.index[0]
            end_date = df.index[-1]

            total_days = len(df)
            profit_days = len(df[df['net_pnl'] > 0])
            loss_days = len(df[df['net_pnl'] < 0])

            end_balance = df['balance'].iloc[-1]            #最终收益
            max_drawdown = df['drawdown'].min()             #最大回撤
            max_drawdown_percent = df['ddpercent'].min()    #最大回撤率
            #最大回撤期
            max_drawdown_end = df["drawdown"].idxmin()
            max_drawdown_start = df["balance"][:max_drawdown_end].argmax()
            max_drawdown_duration = (max_drawdown_end - max_drawdown_start).days
            total_net_pnl = df['net_pnl'].sum()             #总净值
            daily_net_pnl = total_net_pnl / total_days      #日净值

            total_commission = df['commission'].sum()       #总手续费
            daily_commission = total_commission / total_days

            total_slippage = df['slippage'].sum()           #总滑点
            daily_slippage = total_slippage / total_days

            total_turnover = df['turnover'].sum()
            daily_turnover = total_turnover / total_days

            total_trade_count = df['trade_count'].sum()         #总交易次数
            daily_trade_count = total_trade_count / total_days

            total_return = (end_balance / self.capital - 1) * 100           #总收益率
            annual_return = total_return / total_days * TRADING_DAY         #年化收益率       
            #收益率均值，标准差，偏度，峰度
            return_mean,return_std,return_skew, return_kurt = self.statistics_status(df['return'].values) 
            #sortino_info
            sortino_info = sortino_ratio(df['return'])
            #年化波动率
            annual_volatility_info = annual_volatility(df['return'])
            #年化复合增长率
            cagr_info = cagr(df['return'])
            #年化下行风险率
            annual_downside_risk = downside_risk(df['return'])
            """CVaR即条件风险价值，其含义为在投资组合的损失超过某个给定VaR值的条件下，该投资组合的平均损失值。"""
            c_var = conditional_value_at_risk(df['return'])
            """风险价值（VaR）是对投资损失风险的一种度量。它估计在正常的市场条件下，在设定的时间段（例如一天）中，
            一组投资可能（以给定的概率）损失多少。金融业中的公司和监管机构通常使用VaR来衡量弥补可能损失所需的资产数量"""
            var_info = value_at_risk(df['return'])
            #calmar_ratio:年化收益率与历史最大回撤率之间的比率
            calmar_ratio = annual_return / abs(max_drawdown_percent)
            #收益稳定率
            stability_return = stability_of_timeseries(df['return'])
            #尾部比率0.25 == 1/4,收益1，风险4
            tail_ratio_info = tail_ratio(df['return'])
            if return_std:
                sharpe_ratio = return_mean / return_std * np.sqrt(TRADING_DAY)
            else:
                sharpe_ratio = 0
            #收益回撤比
            return_drawdown = -total_net_pnl/max_drawdown
            #收益率回撤率比
            return_drawdown_ratio = -total_return / max_drawdown_percent
            for X in range(len(df['balance'])):
                if X == 0:
                    nets_pnl = 1
                else:
                    nets_pnl = df['balance'][X]/df['balance'][X-1]-1
                self.net_value += nets_pnl
                self.net_value_list.append(round(float(self.net_value),3))
        #----------------------------------------------------------------------
        if write_result:
            self.output('-' * 70)
            if hasattr(self.strategy,'strategy_name'):
                self.output(f"策略名称：{self.strategy.strategy_name},交易标的：{self.vt_symbol}")
            else:
                self.output(f"策略名称：{strategy_name},交易标的：{self.vt_symbol}")
            self.output(f"首个交易日：\t{start_date}，最后交易日：\t{end_date}，总交易日：\t{total_days}")
            self.output(f"盈利交易日：\t{profit_days}，亏损交易日：\t{loss_days}")
            self.output(f"起始资金：\t{self.capital:,.3f}，结束资金：\t{end_balance:,.3f}")
            self.output(f"总盈亏：\t{total_net_pnl:,.3f}")
            self.output(f"总收益率：\t{total_return:,.3f}%,复利净值：\t{self.net_value_list[-1]:,.3f}")
            self.output(f"收益回撤比：\t{return_drawdown:,.3f}")
            self.output(f"收益率回撤率比：\t{return_drawdown_ratio:,.3f}")
            self.output(f"最大回撤资金: \t{max_drawdown:,.3f}")
            self.output(f"最大回撤率: {max_drawdown_percent:,.3f}%")
            self.output(f"最长回撤日期:\t{max_drawdown_start}至{max_drawdown_end},最长回撤天数: \t{max_drawdown_duration}")
            self.output(f"总手续费：\t{total_commission:,.3f}")
            self.output(f"总滑点：\t{total_slippage:,.3f}")
            self.output(f"总成交金额：\t{total_turnover:,.3f}")
            self.output(f"总成交笔数：\t{total_trade_count}")
            self.output(f"日均盈亏：\t{daily_net_pnl:,.3f}")
            self.output(f"日均手续费：\t{daily_commission:,.3f}")
            self.output(f"日均滑点：\t{daily_slippage:,.3f}")
            self.output(f"日均成交金额：\t{daily_turnover:,.3f}")
            self.output(f"日均成交笔数：\t{daily_trade_count:,.3f}")
            self.output(f"年化收益率：\t{annual_return:,.3f}%")
            self.output(f"日均收益率：\t{return_mean*100:,.3f}%，收益率标准差：\t{return_std*100:,.3f}%，收益率偏度：\t{return_skew:,.3f}，收益率峰度：\t{return_kurt:,.3f}")
            self.output(f"sharpe_ratio：\t{sharpe_ratio:,.3f}")
            self.output(f"calmar_ratio：\t{calmar_ratio:,.3f}")
            self.output(f"sortino_info：\t{sortino_info:,.3f}")
            self.output(f"年化波动率：\t{annual_volatility_info:,.3f}")
            self.output(f"年化复合增长率：\t{cagr_info:,.3f}")
            self.output(f"年化下行风险率：\t{annual_downside_risk:,.3f}")
            self.output(f"c_var：\t{c_var:,.3f}")
            self.output(f"var_info：\t{var_info:,.3f}")
            self.output(f"收益稳定率：\t{stability_return:,.3f}")
            self.output(f"尾部比率：\t{tail_ratio_info:,.3f}")

            #回测统计结果和交易明细保存到backtesting_result文件夹
            if hasattr(self.strategy,'strategy_name'):
                self.result_path = f"C:\\ProgramData\\Anaconda3\\Lib\\site-packages\\vnpy-2.0.5-py3.7.egg\\vnpy\\app\\cta_strategy\\backtesting_result\\{datetime.now().date()}_bcaktesting_{self.vt_symbol}_{self.strategy.strategy_name}.csv"
            else:
                self.result_path = f"C:\\ProgramData\\Anaconda3\\Lib\\site-packages\\vnpy-2.0.5-py3.7.egg\\vnpy\\app\\cta_strategy\\backtesting_result\\{datetime.now().date()}_bcaktesting_{self.vt_symbol}_{strategy_name}.csv"
            df.to_csv(self.result_path,encoding='utf_8_sig')    #保存回测统计数据到CSV
            #交易类转化为可读字典存到本地csv
            for trade_class in df['trades']:
                if trade_class:
                    for trade in trade_class:
                        trades_list.append(trade.__dict__)
            DataFrame(trades_list).to_csv(self.result_path.replace('_bcaktesting_','_trade_dict_'),encoding='utf_8_sig')
            #----------------------------------------------------------------------
            #pyecharts绘图写入html,mark_point标记点，mark_point_symbol标记点图形'circle', 'diamond', 'rounddiamond', 'triangle','pin', 'arrow'可选
            bar_1 = Bar()
            bar_1.add_xaxis(df['balance'].index.tolist())
            if hasattr(self.strategy,'strategy_name'):
                bar_1.add_yaxis(f"策略:{self.vt_symbol}_{self.strategy.strategy_name}\n\n总资金\n\n起止时间：{df['balance'].index[0]}至{df['balance'].index[-1]}",df['balance'].tolist())      #主标题
            else:
                bar_1.add_yaxis(f"策略:{self.vt_symbol}_{strategy_name}\n\n总资金\n\n起止时间：{df['balance'].index[0]}至{df['balance'].index[-1]}",df['balance'].tolist())      #主标题
            bar_1.set_global_opts(opts.TitleOpts(title=f"资金\n\n总收益率：{total_return:,.3f}%"),toolbox_opts=opts.ToolboxOpts())  #副标题，ToolboxOpts设置工具箱配置项 
            bar_1.set_series_opts(label_opts=opts.LabelOpts(is_show=False))  #系列配置项 
            #成交记录画图
            trade_datetime =  []
            trade_price = []
            for trade in trades_list:
                trade_datetime.append(trade["datetime"])
                trade_price.append(trade["price"])
            trades_opts_data = [opts.MarkPointItem(
                name = f"orderid:{trade['orderid']}，标的：{trade['vt_symbol']}，{trade['direction'].value}，{trade['offset'].value}，价格：{trade['price']}，成交量：{trade['volume']}",             #成交详细信息添加到name
                itemstyle_opts = opts.ItemStyleOpts(color= "#ec0000" if trade["direction"].value == "多" else "#00da3c"),
                coord = [trade["datetime"],trade["price"] * random.randrange(1000,1010) / 1000],        #标注的坐标
                value = trade["direction"].value + trade["offset"].value
            ) for trade in trades_list]

            bar_2 = Line()
            bar_2.add_xaxis(trade_datetime)
            bar_2.add_yaxis(f"交易价格：交易时间：{trade_datetime[0]}至{trade_datetime[-1]}\n\n成交笔数：{len(trades_list)}",trade_price)      #主标题
            bar_2.set_global_opts(opts.TitleOpts(title="交易记录"),toolbox_opts=opts.ToolboxOpts())  #设置工具箱配置项
            bar_2.set_series_opts(label_opts=opts.LabelOpts(is_show=False),             #标签配置项
            markpoint_opts = opts.MarkPointOpts(data = trades_opts_data,
            #标记的图形圆形："circle'"，方形："rect'"， 圆角方形："roundRect'"，三角形："triangle'"，菱形："diamond'"，水滴："pin'"，箭头：'arrow'
            symbol = "pin"
            ),
            itemstyle_opts = opts.ItemStyleOpts(color = "#ec0000",color0 = "#00da3c"),
            )  #系列配置项 


            bar_3 = Bar()
            bar_3.add_xaxis(df['balance'].index.tolist())
            bar_3.add_yaxis(f"复利净值最高点：{max(self.net_value_list)}\t复利净值最低点：{min(self.net_value_list)}",self.net_value_list)
            bar_3.set_global_opts(opts.TitleOpts(title="复利净值"),toolbox_opts=opts.ToolboxOpts())  #设置工具箱配置项   
            bar_3.set_series_opts(label_opts=opts.LabelOpts(is_show=False))  #系列配置项                  

            bar_4 = Bar()
            bar_4.add_xaxis(df['drawdown'].index.tolist())
            bar_4.add_yaxis(f"回撤资金\n\n最大回撤资金：{max_drawdown:,.3f}",df['drawdown'].tolist())
            bar_4.set_global_opts(opts.TitleOpts(title="资金"),toolbox_opts=opts.ToolboxOpts())  #设置工具箱配置项   
            bar_4.set_series_opts(label_opts=opts.LabelOpts(is_show=False))  #系列配置项     

            bar_5 = Bar()
            bar_5.add_xaxis(df['ddpercent'].index.tolist())
            bar_5.add_yaxis(f"回撤百分比\n\n最大回撤率：{max_drawdown_percent:,.3f}%",df['ddpercent'].tolist())
            bar_5.set_global_opts(opts.TitleOpts(title="回撤百分比"),toolbox_opts=opts.ToolboxOpts())  #设置工具箱配置项   
            bar_5.set_series_opts(label_opts=opts.LabelOpts(is_show=False))  #系列配置项     

            bar_6 = Bar()
            bar_6.add_xaxis(df['net_pnl'].index.tolist())
            bar_6.add_yaxis(f"日盈亏\n\n最大日盈利：{df['net_pnl'].max():,.3f}\n\n最大日亏损：{df['net_pnl'].min():,.3f}",df['net_pnl'].tolist())
            bar_6.set_global_opts(opts.TitleOpts(title="日盈亏"),toolbox_opts=opts.ToolboxOpts())  #设置工具箱配置项   
            bar_6.set_series_opts(label_opts=opts.LabelOpts(is_show=False))  #系列配置项  

            hist,bin_edges= np.histogram(df['net_pnl'], bins=50)                       
            bar_7 = Bar()
            bar_7.add_xaxis(bin_edges[1:].tolist())
            bar_7.add_yaxis("盈亏分布直方图",hist.tolist())
            bar_7.set_global_opts(opts.TitleOpts(title="频数"),toolbox_opts=opts.ToolboxOpts())  #设置工具箱配置项   
            bar_7.set_series_opts(label_opts=opts.LabelOpts(is_show=False))  #系列配置项  

            bar_8 = Bar()
            bar_8.add_xaxis(df['commission'].index.tolist())
            bar_8.add_yaxis(f"每日手续费\n\n日最高手续费:{df['commission'].max():,.3f}",df['commission'].tolist())
            bar_8.set_global_opts(opts.TitleOpts(title="手续费"),toolbox_opts=opts.ToolboxOpts())  #设置工具箱配置项
            bar_8.set_series_opts(label_opts=opts.LabelOpts(is_show=False))  #系列配置项 

            page = Page()
            page.add(bar_1)
            page.add(bar_2)
            page.add(bar_3)
            page.add(bar_4)
            page.add(bar_5)
            page.add(bar_6)
            page.add(bar_7)
            page.add(bar_8)
            #图表结果保存为html
            page.render(self.result_path.replace('.csv','.html'))
            #写入html文件后保存为gif
            #make_snapshot(snapshot,self.result_path.replace('.csv','.html'),self.result_path.replace('.csv','.gif'))   
        #----------------------------------------------------------------------
        statistics = {
            'start_date': start_date,
            'end_date': end_date,
            'total_days': total_days,
            'profit_days': profit_days,
            'loss_days': loss_days,
            'capital': self.capital,
            'end_balance': end_balance,
            'max_drawdown': max_drawdown,
            'max_drawdown_percent': max_drawdown_percent,
            "max_drawdown_duration": max_drawdown_duration,            
            'total_net_pnl': total_net_pnl,
            'daily_net_pnl': daily_net_pnl,
            'total_commission': total_commission,
            'daily_commission': daily_commission,
            'total_slippage': total_slippage,
            'daily_slippage': daily_slippage,
            'total_turnover': total_turnover,
            'daily_turnover': daily_turnover,
            'total_trade_count': total_trade_count,
            'daily_trade_count': daily_trade_count,
            'total_return': total_return,
            'annual_return': annual_return,
            'return_mean': return_mean,
            'return_std': return_std,
            'return_skew': return_skew,
            'return_kurt': return_kurt,
            'sharpe_ratio': sharpe_ratio,
            'calmar_ratio': calmar_ratio,
            'sortino_info': sortino_info,
            'annual_volatility_info': annual_volatility_info,
            'cagr_info': cagr_info,
            'annual_downside_risk': annual_downside_risk,
            'c_var': c_var,
            'var_info': var_info,
            'stability_return': stability_return,
            'tail_ratio_info': tail_ratio_info,
            'return_drawdown': return_drawdown,
            'return_drawdown_ratio': return_drawdown_ratio,
        }

        return statistics
    #----------------------------------------------------------------------
    def get_information_ratio(self,returns,benchmark=0.00008):
        #benchmark基准收益率
        diff = returns - benchmark
        return np.mean(diff) / np.std(diff) * np.sqrt(TRADING_DAY)
    #----------------------------------------------------------------------
    def show_chart(self, df: DataFrame = None):
        """matplotlib画图"""
        if df is None:
            return

        plt.figure(figsize=(10, 16))

        balance_plot = plt.subplot(5, 1, 1)
        balance_plot.set_title('Balance')
        df['balance'].plot(legend=True)

        drawdown_plot = plt.subplot(5, 1, 2)
        drawdown_plot.set_title('Drawdown')
        drawdown_plot.fill_between(range(len(df)), df['drawdown'].values)

        drawdown_percent = plt.subplot(5, 1, 3)
        drawdown_percent.set_title('DrawdownPercent')
        drawdown_percent.fill_between(range(len(df)), df['ddpercent'].values)

        pnl_plot = plt.subplot(5, 1, 4)
        pnl_plot.set_title('Daily Pnl')
        df['net_pnl'].plot(kind='bar', legend=False, grid=False, xticks=[])

        distribution_plot = plt.subplot(5, 1, 5)
        distribution_plot.set_title('Daily Pnl Distribution')
        df['net_pnl'].hist(bins=50)

        plt.show()

    def run_optimization(self, optimization_setting: OptimizationSetting,target_reverse =True):
        """多进程优化"""
        # Get optimization setting and target
        settings = optimization_setting.generate_setting()
        target_name = optimization_setting.target_name

        if not settings:
            self.output('优化参数组合为空，请检查')
            return

        if not target_name:
            self.output('优化目标未设置，请检查')
            return

        # Use multiprocessing pool for running backtesting with different setting
        pool = multiprocessing.Pool(multiprocessing.cpu_count())

        results = []
        for setting in settings:
            result = (pool.apply_async(optimize, (
                target_name,
                self.strategy_class,
                setting,
                self.vt_symbol,
                self.start,
                self.rate,
                self.slippage,
                self.size,
                self.price_tick,
                self.capital,
                self.end,
                self.mode
            )))
            results.append(result)

        pool.close()
        pool.join()

        # Sort results and output
        result_values = [result.get() for result in results]
        result_values.sort(reverse=target_reverse, key=lambda result: result[1])

        for value in result_values:
            msg = f'参数：{value[0]}, 目标：{value[1]}'
            self.output(msg)

        return result_values

    def run_ga_optimization(self, optimization_setting: OptimizationSetting, population_size=200, ngen_size=30):
        """遗传算法优化"""
        # Get optimization setting and target
        settings = optimization_setting.generate_setting_ga()
        target_name = optimization_setting.target_name

        if not settings:
            self.output('优化参数组合为空，请检查')
            return

        if not target_name:
            self.output('优化目标未设置，请检查')
            return

        # Define parameter generation function
        def generate_parameter():
            ''''''
            return random.choice(settings)
        
        def mutate_individual(individual, indpb):
            ''''''
            size = len(individual)
            paramlist = generate_parameter()
            for i in range(size):
                if random.random() < indpb:
                    individual[i] = paramlist[i]
            return individual,

        # Create ga object function
        global ga_target_name
        global ga_strategy_class
        global ga_setting
        global ga_vt_symbol
        global ga_interval
        global ga_start
        global ga_rate
        global ga_slippage
        global ga_size
        global ga_price_tick
        global ga_capital
        global ga_end
        global ga_mode

        ga_target_name = target_name
        ga_strategy_class = self.strategy_class
        ga_setting = settings[0]
        ga_vt_symbol = self.vt_symbol
        ga_interval = self.interval
        ga_start = self.start
        ga_rate = self.rate
        ga_slippage = self.slippage
        ga_size = self.size
        ga_price_tick = self.price_tick
        ga_capital = self.capital
        ga_end = self.end
        ga_mode = self.mode

        # Set up genetic algorithem
        toolbox = base.Toolbox() 
        toolbox.register('individual', tools.initIterate, creator.Individual, generate_parameter)                          
        toolbox.register('population', tools.initRepeat, list, toolbox.individual)                                            
        toolbox.register('mate', tools.cxTwoPoint)                                               
        toolbox.register('mutate', mutate_individual, indpb=1)               
        toolbox.register('evaluate', ga_optimize)                                                
        toolbox.register('select', tools.selNSGA2)       

        total_size = len(settings)
        pop_size = population_size                      #族群里面的个体数量
        lambda_ = int(pop_size * 0.5)                   #每一代产生的子女数
        mu = int(pop_size * 0.25)                       #每一代选择的个体数

        cxpb = 0.5          #种群内部个体的交叉概率  
        mutpb = 1 - cxpb    #种群内部个体的变异概率 
        ngen = ngen_size    #产生种群代数,NGEN = 10要跑10个轮回
                
        pop = toolbox.population(pop_size)      
        hof = tools.ParetoFront()               # end result of pareto front

        stats = tools.Statistics(lambda ind: ind.fitness.values)
        np.set_printoptions(suppress=True)
        stats.register('mean', np.mean, axis=0)
        stats.register('std', np.std, axis=0)
        stats.register('min', np.min, axis=0)
        stats.register('max', np.max, axis=0)

        # Multiprocessing is not supported yet.
        # pool = multiprocessing.Pool(multiprocessing.cpu_count())
        # toolbox.register('map', pool.map)

        # Run ga optimization
        self.output(f'参数优化空间：{total_size}')
        self.output(f'每代族群总数：{pop_size}')
        self.output(f'优良筛选个数：{mu}')
        self.output(f'迭代次数：{ngen}')
        self.output(f'交叉概率：{cxpb:.0%}')
        self.output(f'突变概率：{mutpb:.0%}')

        start = time()

        algorithms.eaMuPlusLambda(
            pop, 
            toolbox, 
            mu, 
            lambda_, 
            cxpb, 
            mutpb, 
            ngen, 
            stats,
            halloffame=hof
        )    
        
        end = time()
        cost = int((end - start))

        self.output(f'遗传算法优化完成，耗时{cost}秒')
        
        # Return result list
        results = []

        for parameter_values in hof:
            setting = dict(parameter_values)
            target_value = ga_optimize(parameter_values)[0]
            results.append((setting, target_value, {}))
        self.output(results)
        return results

    def update_daily_close(self, price: float):
        ''''''
        d = self.datetime.date()

        daily_result = self.daily_results.get(d, None)
        if daily_result:
            daily_result.close_price = price
        else:
            self.daily_results[d] = DailyResult(d, price)

    def new_bar(self, bar: BarData):
        ''''''
        self.bar = bar
        self.datetime = bar.datetime

        self.cross_limit_order()        #先撮合限价单
        self.cross_stop_order()         #再撮合停止单
        self.strategy.on_bar(bar)       #推送K线到策略中
        self.update_postion()           #更新持仓数据  
        self.update_daily_close(bar.close_price)

    def new_tick(self, tick: TickData):
        ''''''
        self.tick = tick
        self.datetime = tick.datetime

        self.cross_limit_order()
        self.cross_stop_order()
        self.strategy.on_tick(tick)
        self.update_postion()           #更新持仓数据  
        self.update_daily_close(tick.last_price)

    def cross_limit_order(self):
        '''
        Cross limit order with last bar/tick data.
        '''
        if self.mode == BacktestingMode.BAR:
            long_cross_price = self.bar.low_price
            short_cross_price = self.bar.high_price
            long_best_price = self.bar.open_price
            short_best_price = self.bar.open_price
        else:
            long_cross_price = self.tick.ask_price_1
            short_cross_price = self.tick.bid_price_1
            long_best_price = long_cross_price
            short_best_price = short_cross_price

        for order in list(self.active_limit_orders.values()):
            # Push order update with status 'not traded' (pending).
            if order.status == Status.SUBMITTING:
                order.status = Status.NOTTRADED
                self.strategy.on_order(order)

            # Check whether limit orders can be filled.
            long_cross = (
                order.direction == Direction.LONG 
                and order.price >= long_cross_price 
                and 0 < long_cross_price < 9999999
            )

            short_cross = (
                order.direction == Direction.SHORT 
                and order.price <= short_cross_price 
                and 0 < short_cross_price < 9999999
            )

            if not long_cross and not short_cross:
                continue

            # Push order udpate with status 'all traded' (filled).
            order.traded = order.volume
            order.status = Status.ALLTRADED
            self.strategy.on_order(order)
            self.active_limit_orders.pop(order.vt_orderid)

            # Push trade update
            self.trade_count += 1

            if long_cross:
                trade_price = min(order.price, long_best_price)
                pos_change = order.volume
            elif short_cross:
                trade_price = max(order.price, short_best_price)
                pos_change = -order.volume
            trade = TradeData(
                symbol=order.symbol,
                exchange=order.exchange,
                orderid=order.orderid,
                tradeid=str(self.trade_count),
                direction=order.direction,
                offset=order.offset,
                price=trade_price,
                volume=order.volume,
                date=self.datetime.strftime('%Y%m%d'),
                time=self.datetime.strftime('%H:%M:%S'),
                gateway_name=self.gateway_name,
            )
            trade.datetime = self.datetime

            self.strategy.pos += pos_change
            self.strategy.on_trade(trade)

            self.trades[trade.vt_tradeid] = trade
            # 更新持仓数据
            self.update_postion(trade=trade)
    def cross_stop_order(self):
        '''
        Cross stop order with last bar/tick data.
        '''
        if self.mode == BacktestingMode.BAR:
            long_cross_price = self.bar.high_price
            short_cross_price = self.bar.low_price
            long_best_price = self.bar.open_price
            short_best_price = self.bar.open_price
        else:
            long_cross_price = self.tick.last_price
            short_cross_price = self.tick.last_price
            long_best_price = long_cross_price
            short_best_price = short_cross_price

        for stop_order in list(self.active_stop_orders.values()):
            # Check whether stop order can be triggered.
            long_cross = (
                stop_order.direction == Direction.LONG 
                and stop_order.price <= long_cross_price
            )

            short_cross = (
                stop_order.direction == Direction.SHORT 
                and stop_order.price >= short_cross_price
            )

            if not long_cross and not short_cross:
                continue

            # Create order data.
            self.limit_order_count += 1

            order = OrderData(
                symbol=self.symbol,
                exchange=self.exchange,
                orderid=str(self.limit_order_count),
                direction=stop_order.direction,
                offset=stop_order.offset,
                price=stop_order.price,
                volume=stop_order.volume,
                traded=stop_order.volume,
                status=Status.ALLTRADED,
                gateway_name=self.gateway_name,
            )
            order.datetime = self.datetime
            self.limit_orders[order.vt_orderid] = order

            # Create trade data.
            if long_cross:
                trade_price = max(stop_order.price, long_best_price)
                pos_change = order.volume
            else:
                trade_price = min(stop_order.price, short_best_price)
                pos_change = -order.volume
            self.trade_count += 1

            trade = TradeData(
                symbol=order.symbol,
                exchange=order.exchange,
                orderid=order.orderid,
                tradeid=str(self.trade_count),
                direction=order.direction,
                offset=order.offset,
                price=trade_price,
                volume=order.volume,
                date=self.datetime.strftime('%Y%m%d'),
                time=self.datetime.strftime('%H:%M:%S'),
                gateway_name=self.gateway_name,
            )
            trade.datetime = self.datetime

            self.trades[trade.vt_tradeid] = trade

            # Update stop order.
            stop_order.vt_orderid = order.vt_orderid
            stop_order.status = StopOrderStatus.TRIGGERED
            if stop_order.stop_orderid in self.active_stop_orders:
                self.active_stop_orders.pop(stop_order.stop_orderid)

            # Push update to strategy.
            self.strategy.on_stop_order(stop_order)
            self.strategy.on_order(order)

            self.strategy.pos += pos_change
            self.strategy.on_trade(trade)
            # 更新持仓数据
            self.update_postion(trade=trade)
    #----------------------------------------------------------------------
    def update_postion(self, trade =None):
        """持仓监控"""
        if trade:
            if trade.direction == Direction.LONG:
                # 做多单
                if trade.offset == Offset.OPEN:
                    long_cost = self.long_avg_cost * self.long_pos
                    long_cost += trade.price * trade.volume
                    # 平均成本
                    self.long_pos += trade.volume
                    if self.long_pos > 0:
                        self.long_avg_cost = round(long_cost / float(self.long_pos), 3)

                else:
                    self.short_pos -= trade.volume
            else:
                # 做空单
                if trade.offset == Offset.OPEN:
                    short_cost = self.short_avg_cost * self.short_pos
                    short_cost += trade.price * trade.volume
                    # 平均成本
                    self.short_pos += trade.volume
                    if self.short_pos > 0:
                        self.short_avg_cost = round(short_cost / float(self.short_pos), 3)
                else:
                    self.long_pos -= trade.volume
        # 多/空仓收益
        if self.mode == BacktestingMode.BAR:
            last_price = self.bar.close_price
        else:
            last_price = self.tick.last_price
        long_profit = (last_price - self.long_avg_cost) * self.long_pos * self.size
        short_profit = (self.short_avg_cost - last_price) * self.short_pos * self.size
        if trade:
            if trade.direction == Direction.LONG:
                self.long_profit_total += long_profit               
            if trade.direction == Direction.SHORT:
                self.short_profit_total += short_profit                            
        self.strategy.long_pos = self.long_pos
        self.strategy.short_pos = self.short_pos
        self.strategy.long_profit = long_profit
        self.strategy.short_profit = short_profit
        self.strategy.balance = self.capital + self.long_profit_total + self.short_profit_total
    def load_bar(
        self, vt_symbol: str, days: int, interval: Interval, callback: Callable
    ):
        ''''''
        self.days = days
        self.callback = callback

    def load_tick(self, vt_symbol: str, days: int, callback: Callable):
        ''''''
        self.days = days
        self.callback = callback

    def send_order(self,vt_symbol, direction: Direction, offset: Offset, price: float, volume: float, stop: bool, lock: bool,strategy:CtaTemplate,order_type:OrderType):
        """
        发送委托单
        """
        #过滤非正常下单价格与委托量
        if not price or not volume or volume < 1:
            return []
        #价格，发单量取整到最小变动
        price = round_to(price, self.price_tick)
        volume = round_to(volume, 1)
        #平仓时仓位为0直接返回
        if offset == Offset.CLOSE:
            if self.strategy.pos == 0:
                return
        if stop:
            vt_orderid = self.send_stop_order(vt_symbol,direction, offset, price, volume,self,OrderType.STOP)
        else:
            vt_orderid = self.send_limit_order(vt_symbol,direction, offset, price, volume,self,OrderType.LIMIT)
        return [vt_orderid]

    def send_stop_order(self, vt_symbol, direction: Direction, offset: Offset, price: float, volume: float, strategy: CtaTemplate, order_type: OrderType, ):
        """
        发送本地停止单
        """
        self.stop_order_count += 1
        stop_order = StopOrder(
            vt_symbol=self.vt_symbol,
            direction=direction,
            offset=offset,
            price=price,
            volume=volume,
            stop_orderid=f'{STOPORDER_PREFIX}.{self.stop_order_count}',
            strategy_name=self.strategy.strategy_name,
        )

        self.active_stop_orders[stop_order.stop_orderid] = stop_order
        self.stop_orders[stop_order.stop_orderid] = stop_order
        return stop_order.stop_orderid

    def send_limit_order(self, vt_symbol, direction: Direction, offset: Offset, price: float, volume: float, strategy: CtaTemplate, order_type: OrderType, ):
        ''''''
        self.limit_order_count += 1
        
        order = OrderData(
            symbol=self.symbol,
            exchange=self.exchange,
            orderid=str(self.limit_order_count),
            direction=direction,
            offset=offset,
            price=price,
            volume=volume,
            traded=volume,
            status=Status.NOTTRADED,
            gateway_name=self.gateway_name,
        )
        order.datetime = self.datetime
        self.active_limit_orders[order.vt_orderid] = order
        self.limit_orders[order.vt_orderid] = order

        return order.vt_orderid

    def cancel_order(self, strategy: CtaTemplate, vt_orderid: str):
        '''
        Cancel order by vt_orderid.
        '''
        if vt_orderid.startswith(STOPORDER_PREFIX):
            self.cancel_stop_order(strategy, vt_orderid)
        else:
            self.cancel_limit_order(strategy, vt_orderid)

    def cancel_stop_order(self, strategy: CtaTemplate, vt_orderid: str):
        ''''''
        if vt_orderid not in self.active_stop_orders:
            return
        stop_order = self.active_stop_orders.pop(vt_orderid)

        stop_order.status = StopOrderStatus.CANCELLED
        self.strategy.on_stop_order(stop_order)

    def cancel_limit_order(self, strategy: CtaTemplate, vt_orderid: str):
        ''''''
        if vt_orderid not in self.active_limit_orders:
            return
        order = self.active_limit_orders.pop(vt_orderid)

        order.status = Status.CANCELLED
        self.strategy.on_order(order)

    def cancel_all(self, strategy: CtaTemplate):
        '''
        Cancel all orders, both limit and stop.
        '''
        vt_orderids = list(self.active_limit_orders.keys())
        for vt_orderid in vt_orderids:
            self.cancel_limit_order(strategy, vt_orderid)

        stop_orderids = list(self.active_stop_orders.keys())
        for vt_orderid in stop_orderids:
            self.cancel_stop_order(strategy, vt_orderid)

    def write_log(self, msg: str, strategy: CtaTemplate = None):
        """
        Write log message.
        """
        msg = '{0}\t{1}'.format(self.datetime,msg)
        self.logs.append(msg)
    
    def send_email(self, msg: str, strategy: CtaTemplate = None):
        '''
        Send email to default receiver.
        '''
        pass

    def sync_strategy_data(self, strategy: CtaTemplate = None):
        pass
    def get_engine_type(self):
        '''
        Return engine type.
        '''
        return self.engine_type

    def put_strategy_event(self, strategy: CtaTemplate):
        '''
        Put an event to update strategy status.
        '''
        pass

    def output(self, msg):
        '''
        Output message of backtesting engine.
        '''
        print(f'{datetime.now()}\t{msg}')
    def get_all_trades(self):
        """
        Return all trade data of current backtesting result.
        """
        return list(self.trades.values())

    def get_all_orders(self):
        """
        Return all limit order data of current backtesting result.
        """
        return list(self.limit_orders.values())

    def get_all_daily_results(self):
        """
        Return all daily result data.
        """
        return list(self.daily_results.values())


class DailyResult:
    ''''''

    def __init__(self, date: date, close_price: float):
        ''''''
        self.date = date
        self.close_price = close_price
        self.pre_close = 0

        self.trades = []
        self.trade_count = 0

        self.start_pos = 0
        self.end_pos = 0

        self.turnover = 0
        self.commission = 0
        self.slippage = 0

        self.trading_pnl = 0
        self.holding_pnl = 0
        self.total_pnl = 0
        self.net_pnl = 0
    def add_trade(self, trade: TradeData):
        ''''''
        self.trades.append(trade)

    def calculate_pnl(
        self,
        pre_close: float,
        start_pos: float,
        size: int,
        rate: float,
        slippage: float,
    ):
        ''''''
        self.pre_close = pre_close

        # Holding pnl is the pnl from holding position at day start
        self.start_pos = start_pos
        self.end_pos = start_pos
        self.holding_pnl = self.start_pos * (self.close_price - self.pre_close) * size

        # Trading pnl is the pnl from new trade during the day
        self.trade_count = len(self.trades)

        for trade in self.trades:
            if trade.direction == Direction.LONG:
                pos_change = trade.volume
            else:
                pos_change = -trade.volume

            turnover = trade.price * trade.volume * size

            self.trading_pnl += pos_change * (self.close_price - trade.price) * size
            self.end_pos += pos_change
            self.turnover += turnover
            self.commission += turnover * rate
            self.slippage += trade.volume * size * slippage

        # Net pnl takes account of commission and slippage cost
        self.total_pnl = self.trading_pnl + self.holding_pnl
        self.net_pnl = self.total_pnl - self.commission - self.slippage


def optimize(
    target_name: str,
    strategy_class: CtaTemplate,
    setting: dict,
    vt_symbol: str,
    start: datetime,
    rate: float,
    slippage: float,
    size: float,
    price_tick: float,
    capital: int,
    end: datetime,
    mode: BacktestingMode
):
    '''
    Function for running in multiprocessing.pool
    '''
    engine = BacktestingEngine()
    engine.clear_data()
    engine.set_parameters(
        vt_symbol=vt_symbol,
        start=start,
        rate=rate,
        slippage=slippage,
        size=size,
        price_tick=price_tick,
        capital=capital,
        end=end,
        mode=mode
    )
    engine.add_strategy(strategy_class, setting)
    engine.load_data()
    engine.run_backtesting()
    daily_df = engine.calculate_result()
    statistics = engine.calculate_statistics(daily_df,write_result=False)
    target_value = statistics[target_name]
    return (str(setting), target_value, statistics)


@lru_cache(maxsize=1000000)
def _ga_optimize(parameter_values: tuple):
    ''''''
    setting = dict(parameter_values)

    result = optimize(
        ga_target_name,
        ga_strategy_class,
        setting,
        ga_vt_symbol,
        ga_start,
        ga_rate,
        ga_slippage,
        ga_size,
        ga_price_tick,
        ga_capital,
        ga_end,
        ga_mode
    )
    return (result[1],)


def ga_optimize(parameter_values: list):
    ''''''
    return _ga_optimize(tuple(parameter_values))

@lru_cache(maxsize=10)
def load_bar_data(
    symbol: str,
    exchange: Exchange,
    interval: Interval,
    start: datetime,
    end: datetime
):
    """bar数据redis序列化存取"""
    file_name = f"{symbol}_{exchange.value}_{start.date()}_{end.date()}_bar"
    redis_data = REDIS_CLIENT.hget(file_name, file_name)
    if not redis_data:
        bar_data = database_manager.load_bar_data( symbol, exchange, interval, start, end )
        REDIS_CLIENT.hset(file_name, file_name, zlib.compress(pickle.dumps(bar_data), 5))       
    else:
        bar_data = pickle.loads(zlib.decompress(redis_data))
    return bar_data
    """数据缓存为pkl格式到本地硬盘"""
"""    dir_path = f"H:\\pickle_data\\"
    file_name = f"{symbol}_{exchange.value}_{start.date()}_{end.date()}_bar"
    pickle_path = dir_path + file_name + ".pkl"
    data_size  =0 
    if not os.path.exists(pickle_path):
        bar_data = database_manager.load_bar_data( symbol, exchange, interval, start, end )
        pickle_file = open(pickle_path,'wb')    
        pickle.dump(bar_data,pickle_file)
        pickle_file.close()
    else:        
        pickle_file = open(pickle_path,'rb')
        bar_data =pickle.load(pickle_file)
        pickle_file.close()
    #pickle_data文件夹大于50G删除缓存数据
    for dirpath, dirnames, filenames in os.walk(dir_path):
        for file_name in filenames:         #当前目录所有文件名
            data_size += os.path.getsize(dirpath + file_name)
    if data_size / (1024 ** 3) > 50:
        for dirpath, dirnames, filenames in os.walk(dir_path):
            for file_name in filenames:           
                os.remove(dirpath + file_name)    
    return bar_data"""

@lru_cache(maxsize=10)
def load_tick_data(
    symbol: str,
    exchange: Exchange,
    start: datetime,
    end: datetime
):
    """tick数据redis序列化存取"""
    file_name = f"{symbol}_{exchange.value}_{start.date()}_{end.date()}_tick"
    redis_data = REDIS_CLIENT.hget(file_name, file_name)
    if not redis_data:
        tick_data = database_manager.load_tick_data( symbol, exchange, start, end )
        REDIS_CLIENT.hset(file_name, file_name, zlib.compress(pickle.dumps(tick_data), 5))        
    else:
        tick_data = pickle.loads(zlib.decompress(redis_data))
    return tick_data
    """数据缓存为pkl格式到本地硬盘"""
"""    dir_path = f"H:\\pickle_data\\"
    file_name = f"{symbol}_{exchange.value}_{start.date()}_{end.date()}_tick"
    pickle_path = dir_path + file_name + ".pkl"
    data_size  =0 
    if not os.path.exists(pickle_path):
        tick_data = database_manager.load_tick_data( symbol, exchange, start, end )
        pickle_file = open(pickle_path,'wb')    
        pickle.dump(tick_data,pickle_file)
        pickle_file.close()
    else:        
        pickle_file = open(pickle_path,'rb')
        tick_data =pickle.load(pickle_file)
        pickle_file.close()
    #pickle_data文件夹大于50G删除缓存数据
    for dirpath, dirnames, filenames in os.walk(dir_path):
        for file_name in filenames:         #当前目录所有文件名
            data_size += os.path.getsize(dirpath + file_name)
    if data_size / (1024 ** 3) > 50:
        for dirpath, dirnames, filenames in os.walk(dir_path):
            for file_name in filenames:           
                os.remove(dirpath + file_name)    
    return tick_data"""
# GA related global value
ga_end = None
ga_mode = None
ga_target_name = None
ga_strategy_class = None
ga_setting = None
ga_vt_symbol = None
ga_interval = None
ga_start = None
ga_rate = None
ga_slippage = None
ga_size = None
ga_price_tick = None
ga_capital = None