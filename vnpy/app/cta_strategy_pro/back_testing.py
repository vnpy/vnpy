# encoding: UTF-8

'''
本文件中包含的是CTA模块的组合回测引擎，回测引擎的API和CTA引擎一致，
可以使用和实盘相同的代码进行回测。
华富资产 李来佳
'''
from __future__ import division

import sys
import os
import importlib
import csv
import copy
import pandas as pd
import traceback
import numpy as np
import logging

from collections import OrderedDict, defaultdict
from datetime import datetime, timedelta
from functools import lru_cache
from pathlib import Path

from .base import (
    EngineType,
    STOPORDER_PREFIX,
    StopOrder,
    StopOrderStatus
)
from .template import CtaTemplate

from .cta_fund_kline import FundKline

from vnpy.trader.object import (
    BarData,
    TickData,
    OrderData,
    TradeData,
    ContractData
)
from vnpy.trader.constant import (
    Exchange,
    Direction,
    Offset,
    Status,
    OrderType,
    Product
)
from vnpy.trader.converter import PositionHolding

from vnpy.trader.utility import (
    get_underlying_symbol,
    round_to,
    extract_vt_symbol,
    format_number,
    import_module_by_str
)

from vnpy.trader.util_logger import setup_logger


class BackTestingEngine(object):
    """
    CTA回测引擎
    函数接口和策略引擎保持一样，
    从而实现同一套代码从回测到实盘。
    针对1分钟bar的回测
    或者tick级别得回测
    提供对组合回测/批量回测得服务

    """

    def __init__(self, event_engine=None):
        """Constructor"""

        # 绑定事件引擎
        self.event_engine = event_engine

        self.mode = 'bar'  # 'bar': 根据1分钟k线进行回测， 'tick'，根据分笔tick进行回测

        # 引擎类型为回测
        self.engine_type = EngineType.BACKTESTING
        self.contract_type = 'future'  # future, stock, digital

        # 回测策略相关
        self.classes = {}  # 策略类，class_name: stategy_class
        self.class_module_map = {}  # 策略类名与模块名映射 class_name: mudule_name
        self.strategies = {}  # 回测策略实例, key = strategy_name, value= strategy
        self.symbol_strategy_map = defaultdict(list)  # vt_symbol: strategy list

        self.test_name = 'portfolio_test_{}'.format(datetime.now().strftime('%M%S'))  # 回测策略组合的实例名字
        self.daily_report_name = ''  # 策略的日净值报告文件名称

        self.test_start_date = ''  # 组合回测启动得日期
        self.init_days = 0  # 初始化天数
        self.test_end_date = ''  # 组合回测结束日期

        self.slippage = {}  # 回测时假设的滑点
        self.commission_rate = {}  # 回测时假设的佣金比例（适用于百分比佣金）
        self.fix_commission = {}  # 每手固定手续费
        self.size = {}  # 合约大小，默认为1
        self.price_tick = {}  # 价格最小变动
        self.margin_rate = {}  # 回测合约的保证金比率
        self.price_dict = {}  # 登记vt_symbol对应的最新价
        self.contract_dict = {}  # 登记vt_symbol得对应合约信息
        self.symbol_exchange_dict = {}  # 登记symbol: exchange的对应关系

        self.data_start_date = None  # 回测数据开始日期，datetime对象 （用于截取数据）
        self.data_end_date = None  # 回测数据结束日期，datetime对象 （用于截取数据）
        self.strategy_start_date = None  # 策略启动日期（即前面的数据用于初始化），datetime对象

        self.stop_order_count = 0  # 本地停止单编号
        self.stop_orders = {}  # 本地停止单
        self.active_stop_orders = {}  # 活动本地停止单

        self.limit_order_count = 0  # 限价单编号
        self.limit_orders = OrderedDict()  # 限价单字典
        self.active_limit_orders = OrderedDict()  # 活动限价单字典，用于进行撮合用

        self.order_strategy_dict = {}  # orderid 与 strategy的映射

        # 持仓缓存字典
        # key为vt_symbol，value为PositionBuffer对象
        self.pos_holding_dict = {}

        self.trade_count = 0  # 成交编号
        self.trade_dict = OrderedDict()  # 用于统计成交收益时，还没处理得交易
        self.trades = OrderedDict()  # 记录所有得成交记录
        self.trade_pnl_list = []  # 交易记录列表

        self.long_position_list = []  # 多单持仓
        self.short_position_list = []  # 空单持仓

        self.holdings = {}  # 多空持仓

        # 当前最新数据，用于模拟成交用
        self.gateway_name = u'BackTest'

        self.last_bar = {}  # 最新的bar
        self.last_tick = {}  # 最新tick
        self.last_dt = None  # 最新时间

        # csvFile相关
        self.bar_interval_seconds = 60  # csv文件，属于K线类型，K线的周期（秒数）,缺省是1分钟

        # 费用风控情况
        self.percent = 0.0
        self.percent_limit = 30  # 投资仓位比例上限

        # 回测计算相关
        self.use_margin = True  # 使用保证金模式（期货使用，计算保证金时，按照开仓价计算。股票是按照当前价计算）

        self.init_capital = 1000000  # 期初资金
        self.cur_capital = self.init_capital  # 当前资金净值
        self.net_capital = self.init_capital  # 实时资金净值（每日根据capital和持仓浮盈计算）
        self.max_capital = self.init_capital  # 资金最高净值
        self.max_net_capital = self.init_capital
        self.avaliable = self.init_capital

        self.max_pnl = 0  # 最高盈利
        self.min_pnl = 0  # 最大亏损
        self.max_occupy_rate = 0  # 最大保证金占比
        self.winning_result = 0  # 盈利次数
        self.losing_result = 0  # 亏损次数

        self.total_trade_count = 0  # 总成交数量
        self.total_winning = 0  # 总盈利
        self.total_losing = 0  # 总亏损
        self.total_turnover = 0  # 总成交金额（合约面值）
        self.total_commission = 0  # 总手续费
        self.total_slippage = 0  # 总滑点

        self.time_list = []  # 时间序列
        self.pnl_list = []  # 每笔盈亏序列
        self.capital_list = []  # 盈亏汇总的时间序列
        self.drawdown_list = []  # 回撤的时间序列
        self.drawdown_rate_list = []  # 最大回撤比例的时间序列(成交结算）

        self.max_net_capital_time = ''
        self.max_drawdown_rate_time = ''
        self.daily_max_drawdown_rate = 0  # 按照日结算价计算

        self.pnl_strategy_dict = {}  # 策略实例的平仓盈亏

        self.is_plot_daily = False
        self.daily_list = []  # 按日统计得序列
        self.daily_first_benchmark = None

        self.logger = None
        self.strategy_loggers = {}
        self.debug = False

        self.is_7x24 = False
        self.logs_path = None
        self.data_path = None

        self.fund_kline_dict = {}
        self.active_fund_kline = False

    def create_fund_kline(self, name, use_renko=False):
        """
        创建资金曲线
        :param name: 账号名，或者策略名
        :param use_renko:
        :return:
        """
        setting = {}
        setting.update({'name': name})
        setting['para_ma1_len'] = 5
        setting['para_ma2_len'] = 10
        setting['para_ma3_len'] = 20
        setting['para_active_yb'] = True
        setting['price_tick'] = 0.01
        setting['underlying_symbol'] = 'fund'
        if use_renko:
            # 使用砖图，高度是资金的千分之一
            setting['height'] = self.init_capital * 0.001
            setting['use_renko'] = True

        fund_kline = FundKline(cta_engine=self, setting=setting)
        self.fund_kline_dict.update({name: fund_kline})
        return fund_kline

    def get_fund_kline(self, name: str = None):
        # 指定资金账号/策略名
        if name:
            kline = self.fund_kline_dict.get(name, None)
            return kline

        # 没有指定账号，并且存在一个或多个资金K线
        if len(self.fund_kline_dict) > 0:
            # 优先找vt_setting中，配置了strategy_groud的资金K线
            kline = self.fund_kline_dict.get(self.test_name, None)

            # 找不到，返回第一个
            if kline is None:
                kline = self.fund_kline_dict.values()[0]
            return kline
        else:
            return None

    def get_account(self, vt_accountid: str = ""):
        """返回账号的实时权益，可用资金，仓位比例,投资仓位比例上限"""
        if self.net_capital == 0.0:
            self.percent = 0.0

        return self.net_capital, self.avaliable, self.percent, self.percent_limit

    def set_test_start_date(self, start_date: str = '20100416', init_days: int = 10):
        """设置回测的启动日期"""
        self.test_start_date = start_date
        self.init_days = init_days

        self.data_start_date = datetime.strptime(start_date, '%Y%m%d')

        # 初始化天数
        init_time_delta = timedelta(init_days)

        self.strategy_start_date = self.data_start_date + init_time_delta
        self.write_log(u'设置：回测数据开始日期:{},初始化数据为{}天，策略自动启动日期:{}'
                       .format(self.data_start_date, self.init_days, self.strategy_start_date))

    def set_test_end_date(self, end_date: str = ''):
        """设置回测的结束日期"""
        self.test_end_date = end_date
        if end_date:
            self.data_end_date = datetime.strptime(end_date, '%Y%m%d')
            # 若不修改时间则会导致不包含dataEndDate当天数据
            self.data_end_date.replace(hour=23, minute=59)
        else:
            self.data_end_date = datetime.now()
        self.write_log(u'设置：回测数据结束日期:{}'.format(self.data_end_date))

    def set_init_capital(self, capital: float):
        """设置期初净值"""
        self.cur_capital = capital  # 资金
        self.net_capital = capital  # 实时资金净值（每日根据capital和持仓浮盈计算）
        self.max_capital = capital  # 资金最高净值
        self.max_net_capital = capital
        self.avaliable = capital
        self.init_capital = capital

    def set_margin_rate(self, vt_symbol: str, margin_rate: float):
        """设置某个合约得保证金比率"""
        self.margin_rate.update({vt_symbol: margin_rate})

    @lru_cache()
    def get_margin_rate(self, vt_symbol: str):
        return self.margin_rate.get(vt_symbol, 0.1)

    def set_slippage(self, vt_symbol: str, slippage: float):
        """设置滑点点数"""
        self.slippage.update({vt_symbol: slippage})

    @lru_cache()
    def get_slippage(self, vt_symbol: str):
        """获取滑点"""
        return self.slippage.get(vt_symbol, 0)

    def set_size(self, vt_symbol: str, size: int):
        """设置合约大小"""
        self.size.update({vt_symbol: size})

    @lru_cache()
    def get_size(self, vt_symbol: str):
        """查询合约的size"""
        return self.size.get(vt_symbol, 10)

    def set_price(self, vt_symbol: str, price: float):
        self.price_dict.update({vt_symbol: price})

    def get_price(self, vt_symbol: str):
        return self.price_dict.get(vt_symbol, None)

    def set_commission_rate(self, vt_symbol: str, rate: float):
        """设置佣金比例"""
        self.commission_rate.update({vt_symbol: rate})

        if rate >= 0.1:
            self.fix_commission.update({vt_symbol: rate})

    def get_commission_rate(self, vt_symbol: str):
        """ 获取保证金比例，缺省万分之一"""
        return self.commission_rate.get(vt_symbol, float(0.00001))

    def get_fix_commission(self, vt_symbol: str):
        return self.fix_commission.get(vt_symbol, 0)

    def set_price_tick(self, vt_symbol: str, price_tick: float):
        """设置价格最小变动"""
        self.price_tick.update({vt_symbol: price_tick})

    def get_price_tick(self, vt_symbol: str):
        return self.price_tick.get(vt_symbol, 1)

    def set_contract(self, symbol: str, exchange: Exchange, product: Product, name: str, size: int,
                     price_tick: float, margin_rate: float = 0.1):
        """设置合约信息"""
        vt_symbol = '.'.join([symbol, exchange.value])
        if vt_symbol not in self.contract_dict:
            c = ContractData(
                gateway_name=self.gateway_name,
                symbol=symbol,
                exchange=exchange,
                name=name,
                product=product,
                size=size,
                pricetick=price_tick,
                margin_rate=margin_rate
            )
            self.contract_dict.update({vt_symbol: c})
            self.set_size(vt_symbol, size)
            self.set_margin_rate(vt_symbol, margin_rate)
            self.set_price_tick(vt_symbol, price_tick)
            self.symbol_exchange_dict.update({symbol: exchange})

    @lru_cache()
    def get_contract(self, vt_symbol):
        """获取合约配置信息"""
        return self.contract_dict.get(vt_symbol)

    @lru_cache()
    def get_exchange(self, symbol: str):
        return self.symbol_exchange_dict.get(symbol, Exchange.LOCAL)

    def get_position_holding(self, vt_symbol: str, gateway_name: str = ''):
        """ 查询合约在账号的持仓（包含多空）"""
        k = f'{gateway_name}.{vt_symbol}'
        holding = self.holdings.get(k, None)
        if not holding:
            symbol, exchange = extract_vt_symbol(vt_symbol)
            if self.contract_type == 'future':
                product = Product.FUTURES
            elif self.contract_type == 'stock':
                product = Product.EQUITY
            else:
                product = Product.SPOT
            contract = ContractData(gateway_name=gateway_name,
                                    name=vt_symbol,
                                    product=product,
                                    symbol=symbol,
                                    exchange=exchange,
                                    size=self.get_size(vt_symbol),
                                    pricetick=self.get_price_tick(vt_symbol),
                                    margin_rate=self.get_margin_rate(vt_symbol))
            holding = PositionHolding(contract)
            self.holdings[k] = holding
        return holding

    def set_name(self, test_name):
        """
        设置组合的运行实例名称
        :param test_name:
        :return:
        """
        self.test_name = test_name

    def set_daily_report_name(self, report_file):
        """
        设置策略的日净值记录csv保存文件名（含路径）
        :param report_file: 保存文件名（含路径）
        :return:
        """
        self.daily_report_name = report_file

    def prepare_env(self, test_settings):
        """
        根据配置参数，准备环境
        包括：
        回测名称 ，是否debug，数据目录/日志目录，
        资金/保证金类型/仓位控制
        回测开始/结束日期
        :param test_settings:
        :return:
        """
        self.output('back_testing prepare_env')
        if 'name' in test_settings:
            self.set_name(test_settings.get('name'))

        self.mode = test_settings.get('mode', 'bar')
        self.output(f'采用{self.mode}方式回测')

        self.contract_type = test_settings.get('contract_type', 'future')
        self.output(f'测试合约主要为{self.contract_type}')

        self.debug = test_settings.get('debug', False)

        # 更新数据目录
        if 'data_path' in test_settings:
            self.data_path = test_settings.get('data_path')
        else:
            self.data_path = os.path.abspath(os.path.join(os.getcwd(), 'data'))

        print(f'数据输出目录:{self.data_path}')

        # 更新日志目录
        if 'logs_path' in test_settings:
            self.logs_path = os.path.abspath(os.path.join(test_settings.get('logs_path'), self.test_name))
        else:
            self.logs_path = os.path.abspath(os.path.join(os.getcwd(), 'log', self.test_name))
        print(f'日志输出目录:{self.logs_path}')

        # 创建日志
        self.create_logger(debug=self.debug)

        # 设置资金
        if 'init_capital' in test_settings:
            self.write_log(u'设置期初资金:{}'.format(test_settings.get('init_capital')))
            self.set_init_capital(test_settings.get('init_capital'))

        # 缺省使用保证金方式。（期货使用保证金/股票不使用保证金）
        self.use_margin = test_settings.get('use_margin', True)

        # 设置最大资金使用比例
        if 'percent_limit' in test_settings:
            self.write_log(u'设置最大资金使用比例:{}%'.format(test_settings.get('percent_limit')))
            self.percent_limit = test_settings.get('percent_limit')

        if 'start_date' in test_settings:
            if 'strategy_start_date' not in test_settings:
                init_days = test_settings.get('init_days', 10)
                self.write_log(u'设置回测开始日期:{}，数据加载日数:{}'.format(test_settings.get('start_date'), init_days))
                self.set_test_start_date(test_settings.get('start_date'), init_days)
            else:
                start_date = test_settings.get('start_date')
                strategy_start_date = test_settings.get('strategy_start_date')
                self.write_log(u'使用指定的数据开始日期：{}和策略启动日期:{}'.format(start_date, strategy_start_date))
                self.test_start_date = start_date
                self.data_start_date = datetime.strptime(start_date.replace('-', ''), '%Y%m%d')
                self.strategy_start_date = datetime.strptime(strategy_start_date.replace('-', ''), '%Y%m%d')

        if 'end_date' in test_settings:
            self.write_log(u'设置回测结束日期:{}'.format(test_settings.get('end_date')))
            self.set_test_end_date(test_settings.get('end_date'))

        # 准备数据
        if 'symbol_datas' in test_settings:
            self.write_log(u'准备数据')
            self.prepare_data(test_settings.get('symbol_datas'))

        if self.mode == 'tick':
            self.tick_path = test_settings.get('tick_path', None)

        # 设置bar文件的时间间隔秒数
        if 'bar_interval_seconds' in test_settings:
            self.write_log(u'设置bar文件的时间间隔秒数：{}'.format(test_settings.get('bar_interval_seconds')))
            self.bar_interval_seconds = test_settings.get('bar_interval_seconds')

        # 资金曲线
        self.active_fund_kline = test_settings.get('active_fund_kline', False)
        if self.active_fund_kline:
            # 创建资金K线
            self.create_fund_kline(self.test_name, use_renko=test_settings.get('use_renko', False))

        self.is_plot_daily = test_settings.get('is_plot_daily', False)

        # 加载所有本地策略class
        self.load_strategy_class()

    def prepare_data(self, data_dict):
        """
        准备组合数据
        :param data_dict:
        :return:
        """
        self.output('prepare_data')

        if len(data_dict) == 0:
            self.write_log(u'请指定回测数据和文件')
            return

        for symbol, symbol_data in data_dict.items():
            self.write_log(u'配置{}数据:{}'.format(symbol, symbol_data))
            self.set_price_tick(symbol, symbol_data.get('price_tick', 1))

            self.set_slippage(symbol, symbol_data.get('slippage', 0))

            self.set_size(symbol, symbol_data.get('symbol_size', 10))
            margin_rate = symbol_data.get('margin_rate', 0.1)
            self.set_margin_rate(symbol, margin_rate)

            self.set_commission_rate(symbol, symbol_data.get('commission_rate', float(0.0001)))

            self.set_contract(
                symbol=symbol,
                name=symbol,
                exchange=Exchange(symbol_data.get('exchange', 'LOCAL')),
                product=Product(symbol_data.get('product', "期货")),
                size=symbol_data.get('symbol_size', 10),
                price_tick=symbol_data.get('price_tick', 1),
                margin_rate=margin_rate
            )

    def new_tick(self, tick):
        """新得tick"""
        self.last_tick.update({tick.vt_symbol: tick})
        if self.last_dt is None or (tick.datetime and tick.datetime > self.last_dt):
            self.last_dt = tick.datetime

        self.set_price(tick.vt_symbol, tick.last_price)

        self.cross_stop_order(tick=tick)  # 撮合停止单
        self.cross_limit_order(tick=tick)  # 先撮合限价单

        # 更新账号级别资金曲线(只有持仓时，才更新)
        fund_kline = self.get_fund_kline(self.test_name)
        if fund_kline is not None and (len(self.long_position_list) > 0 or len(self.short_position_list) > 0):
            fund_kline.update_account(self.last_dt, self.net_capital)

        for strategy in self.symbol_strategy_map.get(tick.vt_symbol, []):
            # 更新策略的资金K线
            fund_kline = self.fund_kline_dict.get(strategy.strategy_name, None)
            if fund_kline:
                hold_pnl = fund_kline.get_hold_pnl()
                if hold_pnl != 0:
                    fund_kline.update_strategy(dt=self.last_dt, hold_pnl=hold_pnl)

            # 推送tick到策略中
            strategy.on_tick(tick)  # 推送K线到策略中

            # 到达策略启动日期,启动策略
            if not strategy.trading and self.strategy_start_date < tick.datetime:
                strategy.trading = True
                strategy.on_start()
                self.output(u'{}策略启动交易'.format(strategy.strategy_name))

    def new_bar(self, bar):
        """新的K线"""
        self.last_bar.update({bar.vt_symbol: bar})
        if self.last_dt is None or (bar.datetime and bar.datetime > self.last_dt):
            self.last_dt = bar.datetime
        self.set_price(bar.vt_symbol, bar.close_price)
        self.cross_stop_order(bar=bar)  # 撮合停止单
        self.cross_limit_order(bar=bar)  # 先撮合限价单

        # 更新账号的资金曲线(只有持仓时，才更新)
        fund_kline = self.get_fund_kline(self.test_name)
        if fund_kline is not None and (len(self.long_position_list) > 0 or len(self.short_position_list) > 0):
            fund_kline.update_account(self.last_dt, self.net_capital)

        for strategy in self.symbol_strategy_map.get(bar.vt_symbol, []):
            # 更新策略的资金K线
            fund_kline = self.fund_kline_dict.get(strategy.strategy_name, None)
            if fund_kline:
                hold_pnl = fund_kline.get_hold_pnl()
                if hold_pnl != 0:
                    fund_kline.update_strategy(dt=self.last_dt, hold_pnl=hold_pnl)

            # 推送K线到策略中
            strategy.on_bar(bar)  # 推送K线到策略中

            # 到达策略启动日期,启动策略
            if not strategy.trading and self.strategy_start_date < bar.datetime:
                strategy.trading = True
                strategy.on_start()
                self.output(u'{}策略启动交易'.format(strategy.strategy_name))

    def load_strategy_class(self):
        """
        Load strategy class from source code.
        """
        self.write_log('加载所有策略class')
        # 加载 vnpy/app/cta_strategy_pro/strategies的所有策略
        path1 = Path(__file__).parent.joinpath("strategies")
        self.load_strategy_class_from_folder(
            path1, "vnpy.app.cta_strategy_pro.strategies")

    def load_strategy_class_from_folder(self, path: Path, module_name: str = ""):
        """
        Load strategy class from certain folder.
        """
        for dirpath, dirnames, filenames in os.walk(str(path)):
            for filename in filenames:
                if filename.endswith(".py"):
                    strategy_module_name = ".".join(
                        [module_name, filename.replace(".py", "")])
                elif filename.endswith(".pyd"):
                    strategy_module_name = ".".join(
                        [module_name, filename.split(".")[0]])
                else:
                    continue
                self.load_strategy_class_from_module(strategy_module_name)

    def load_strategy_class_from_module(self, module_name: str):
        """
        Load/Reload strategy class from module file.
        """
        try:
            module = importlib.import_module(module_name)

            for name in dir(module):
                value = getattr(module, name)
                if (isinstance(value, type) and issubclass(value, CtaTemplate) and value is not CtaTemplate):
                    class_name = value.__name__
                    if class_name not in self.classes:
                        self.write_log(f"加载策略类{module_name}.{class_name}")
                    else:
                        self.write_log(f"更新策略类{module_name}.{class_name}")
                    self.classes[class_name] = value
                    self.class_module_map[class_name] = module_name
            return True
        except:  # noqa
            msg = f"策略文件{module_name}加载失败，触发异常：\n{traceback.format_exc()}"
            self.write_error(msg)
            self.output(msg)
            return False

    def load_strategy(self, strategy_name: str, strategy_setting: dict = None):
        """
        装载回测的策略
        setting是参数设置，包括
            class_name: str, 策略类名字
            vt_symbol: str, 缺省合约
            setting: {}, 策略的参数
            auto_init: True/False, 策略是否自动初始化
            auto_start: True/False， 策略是否自动启动
        """

        # 获取策略的类名
        class_name = strategy_setting.get('class_name', None)
        if class_name is None or strategy_name is None:
            self.write_error(u'setting中没有class_name')
            return

        # strategy_class => module.strategy_class
        if '.' not in class_name:
            module_name = self.class_module_map.get(class_name, None)
            if module_name:
                class_name = module_name + '.' + class_name
                self.write_log(u'转换策略为全路径:{}'.format(class_name))

        # 获取策略类的定义
        strategy_class = import_module_by_str(class_name)
        if strategy_class is None:
            self.write_error(u'加载策略模块失败:{}'.format(class_name))
            return

        # 处理 vt_symbol
        vt_symbol = strategy_setting.get('vt_symbol')
        if '.' in vt_symbol:
            symbol, exchange = extract_vt_symbol(vt_symbol)
        elif self.contract_type == 'future':
            symbol = vt_symbol
            underly_symbol = get_underlying_symbol(symbol).upper()
            exchange = self.get_exchange(f'{underly_symbol}99')
            vt_symbol = '.'.join([symbol, exchange.value])
        else:
            symbol = vt_symbol
            exchange = Exchange.LOCAL
            vt_symbol = '.'.join([symbol, exchange.value])

        # 在期货组合回测，中需要把一般配置的主力合约，更换为指数合约
        if '99' not in symbol and exchange != Exchange.SPD and self.contract_type == 'future':
            underly_symbol = get_underlying_symbol(symbol).upper()
            self.write_log(u'更新vt_symbol为指数合约:{}=>{}'.format(vt_symbol, underly_symbol + '99.' + exchange.value))
            vt_symbol = underly_symbol.upper() + '99.' + exchange.value
            strategy_setting.update({'vt_symbol': vt_symbol})

        # 属于自定义套利合约
        if exchange == Exchange.SPD:
            symbol_pairs = symbol.split('-')
            active_symbol = get_underlying_symbol(symbol_pairs[0])
            passive_symbol = get_underlying_symbol(symbol_pairs[2])
            new_vt_symbol = '-'.join([active_symbol.upper() + '99',
                                      symbol_pairs[1],
                                      passive_symbol.upper() + '99',
                                      symbol_pairs[3],
                                      symbol_pairs[4]]) + '.SPD'
            self.write_log(u'更新vt_symbol为指数合约:{}=>{}'.format(vt_symbol, new_vt_symbol))
            vt_symbol = new_vt_symbol
            strategy_setting.update({'vt_symbol': vt_symbol})

        # 取消自动启动
        if 'auto_start' in strategy_setting:
            strategy_setting.update({'auto_start': False})

        # 策略参数设置
        setting = strategy_setting.get('setting', {})

        # 强制更新回测为True
        setting.update({'backtesting': True})

        # 创建实例
        strategy = strategy_class(self, strategy_name, vt_symbol, setting)

        # 保存到策略实例映射表中
        self.strategies.update({strategy_name: strategy})

        # 更新vt_symbol合约与策略的订阅关系
        self.subscribe_symbol(strategy_name=strategy_name, vt_symbol=vt_symbol)

        if strategy_setting.get('auto_init', False):
            self.write_log(u'自动初始化策略')
            strategy.on_init()

        if strategy_setting.get('auto_start', False):
            self.write_log(u'自动启动策略')
            strategy.on_start()

        if self.active_fund_kline:
            # 创建策略实例的资金K线
            self.create_fund_kline(name=strategy_name, use_renko=False)

    def subscribe_symbol(self, strategy_name: str, vt_symbol: str, gateway_name: str = '', is_bar: bool = False):
        """订阅合约"""
        strategy = self.strategies.get(strategy_name, None)
        if not strategy:
            return False

        # 添加 合约订阅 vt_symbol <=> 策略实例 strategy 映射.
        strategies = self.symbol_strategy_map[vt_symbol]
        strategies.append(strategy)
        return True

    # ---------------------------------------------------------------------
    def save_strategy_data(self):
        """保存策略数据"""
        for strategy in self.strategies.values():
            self.write_log(u'save strategy data')
            strategy.save_data()

    def send_order(self,
                   strategy: CtaTemplate,
                   vt_symbol: str,
                   direction: Direction,
                   offset: Offset,
                   price: float,
                   volume: float,
                   stop: bool,
                   lock: bool,
                   order_type: OrderType = OrderType.LIMIT,
                   gateway_name: str = None):
        """发单"""
        price_tick = self.get_price_tick(vt_symbol)
        price = round_to(price, price_tick)

        if stop:
            return self.send_local_stop_order(
                strategy=strategy,
                vt_symbol=vt_symbol,
                direction=direction,
                offset=offset,
                price=price,
                volume=volume,
                lock=lock,
                gateway_name=gateway_name
            )
        else:
            return self.send_limit_order(
                strategy=strategy,
                vt_symbol=vt_symbol,
                direction=direction,
                offset=offset,
                price=price,
                volume=volume,
                lock=lock,
                gateway_name=gateway_name
            )

    def send_limit_order(self,
                         strategy: CtaTemplate,
                         vt_symbol: str,
                         direction: Direction,
                         offset: Offset,
                         price: float,
                         volume: float,
                         lock: bool,
                         order_type: OrderType = OrderType.LIMIT,
                         gateway_name: str = None
                         ):
        self.limit_order_count += 1
        order_id = str(self.limit_order_count)
        symbol, exchange = extract_vt_symbol(vt_symbol)
        if gateway_name is None:
            gateway_name = self.gateway_name
        order = OrderData(
            gateway_name=gateway_name,
            symbol=symbol,
            exchange=exchange,
            orderid=order_id,
            direction=direction,
            offset=offset,
            type=order_type,
            price=round_to(value=price, target=self.get_price_tick(symbol)),
            volume=volume,
            status=Status.NOTTRADED,
            time=str(self.last_dt)
        )

        # 保存到限价单字典中
        self.active_limit_orders[order.vt_orderid] = order
        self.limit_orders[order.vt_orderid] = order
        self.order_strategy_dict.update({order.vt_orderid: strategy})

        self.write_log(f'创建限价单:{order.__dict__}')

        return [order.vt_orderid]

    def send_local_stop_order(
            self,
            strategy: CtaTemplate,
            vt_symbol: str,
            direction: Direction,
            offset: Offset,
            price: float,
            volume: float,
            lock: bool,
            gateway_name: str = None):

        """"""
        self.stop_order_count += 1

        stop_order = StopOrder(
            vt_symbol=vt_symbol,
            direction=direction,
            offset=offset,
            price=price,
            volume=volume,
            stop_orderid=f"{STOPORDER_PREFIX}.{self.stop_order_count}",
            strategy_name=strategy.strategy_name,
        )
        self.write_log(f'创建本地停止单:{stop_order.__dict__}')
        self.order_strategy_dict.update({stop_order.stop_orderid: strategy})

        self.active_stop_orders[stop_order.stop_orderid] = stop_order
        self.stop_orders[stop_order.stop_orderid] = stop_order

        return [stop_order.stop_orderid]

    def cancel_order(self, strategy: CtaTemplate, vt_orderid: str):
        """撤单"""
        if vt_orderid.startswith(STOPORDER_PREFIX):
            return self.cancel_stop_order(strategy, vt_orderid)
        else:
            return self.cancel_limit_order(strategy, vt_orderid)

    def cancel_limit_order(self, strategy: CtaTemplate, vt_orderid: str):
        """限价单撤单"""
        if vt_orderid in self.active_limit_orders:
            order = self.active_limit_orders[vt_orderid]
            register_strategy = self.order_strategy_dict.get(vt_orderid, None)
            if register_strategy.strategy_name != strategy.strategy_name:
                return False
            order.status = Status.CANCELLED
            order.cancelTime = str(self.last_dt)
            self.active_limit_orders.pop(vt_orderid, None)
            strategy.on_order(order)
            return True
        return False

    def cancel_stop_order(self, strategy: CtaTemplate, vt_orderid: str):
        """本地停止单撤单"""
        if vt_orderid not in self.active_stop_orders:
            return False
        stop_order = self.active_stop_orders.pop(vt_orderid)

        stop_order.status = StopOrderStatus.CANCELLED
        strategy.on_stop_order(stop_order)
        return True

    def cancel_all(self, strategy):
        """撤销某个策略的所有委托单"""
        self.cancel_orders(strategy=strategy)

    def cancel_orders(self, vt_symbol: str = None, offset: Offset = None, strategy: CtaTemplate = None):
        """撤销所有单"""
        # Symbol参数:指定合约的撤单；
        # OFFSET参数:指定Offset的撤单,缺省不填写时，为所有
        # strategy参数： 指定某个策略的单子

        if len(self.active_limit_orders) > 0:
            self.write_log(u'从所有订单中,撤销：开平：{}，合约：{}，策略:{}'
                           .format(offset,
                                   vt_symbol if vt_symbol is not None else u'所有',
                                   strategy.strategy_name if strategy else None))

        for vt_orderid in list(self.active_limit_orders.keys()):
            order = self.active_limit_orders.get(vt_orderid, None)
            order_strategy = self.order_strategy_dict.get(vt_orderid, None)
            if order is None or order_strategy is None:
                continue

            if offset is None:
                offset_cond = True
            else:
                offset_cond = order.offset == offset

            if vt_symbol is None:
                symbol_cond = True
            else:
                symbol_cond = order.vt_symbol == vt_symbol

            if strategy is None:
                strategy_cond = True
            else:
                strategy_cond = strategy.strategy_name == order_strategy.strategy_name

            if offset_cond and symbol_cond and strategy_cond:
                self.write_log(u'撤销订单:{},{} {}@{}'
                               .format(vt_orderid, order.direction, order.price, order.volume))
                order.status = Status.CANCELLED
                order.cancel_time = str(self.last_dt)
                del self.active_limit_orders[vt_orderid]
                if strategy:
                    strategy.on_order(order)

        for stop_orderid in list(self.active_stop_orders.keys()):
            order = self.active_stop_orders.get(stop_orderid, None)
            order_strategy = self.order_strategy_dict.get(stop_orderid, None)
            if order is None or order_strategy is None:
                continue

            if offset is None:
                offset_cond = True
            else:
                offset_cond = order.offset == offset

            if vt_symbol is None:
                symbol_cond = True
            else:
                symbol_cond = order.vt_symbol == vt_symbol

            if strategy is None:
                strategy_cond = True
            else:
                strategy_cond = strategy.strategy_name == order_strategy.strategy_name

            if offset_cond and symbol_cond and strategy_cond:
                self.write_log(u'撤销本地停止单:{},{} {}@{}'
                               .format(stop_orderid, order.direction, order.price, order.volume))
                order.status = Status.CANCELLED
                order.cancel_time = str(self.last_dt)
                self.active_stop_orders.pop(stop_orderid, None)
                if strategy:
                    strategy.on_stop_order(order)

    def cross_stop_order(self, bar: BarData = None, tick: TickData = None):
        """
        Cross stop order with last bar/tick data.
        """
        vt_symbol = bar.vt_symbol if bar else tick.vt_symbol

        for stop_orderid in list(self.active_stop_orders.keys()):
            stop_order = self.active_stop_orders[stop_orderid]
            strategy = self.order_strategy_dict.get(stop_orderid, None)
            if stop_order.vt_symbol != vt_symbol or stop_order is None or strategy is None:
                continue

            # 若买入方向停止单价格高于等于该价格，则会触发
            if bar:
                long_cross_price = round_to(value=bar.low_price, target=self.get_price_tick(vt_symbol))
                long_cross_price -= self.get_price_tick(vt_symbol)
                # 若卖出方向停止单价格低于等于该价格，则会触发
                short_cross_price = round_to(value=bar.high_price, target=self.get_price_tick(vt_symbol))
                short_cross_price += self.get_price_tick(vt_symbol)
                # 在当前时间点前发出的买入委托可能的最优成交价
                long_best_price = round_to(value=bar.open_price,
                                           target=self.get_price_tick(vt_symbol)) + self.get_price_tick(vt_symbol)

                # 在当前时间点前发出的卖出委托可能的最优成交价
                short_best_price = round_to(value=bar.open_price,
                                            target=self.get_price_tick(vt_symbol)) - self.get_price_tick(vt_symbol)
            else:
                long_cross_price = tick.last_price
                short_cross_price = tick.last_price
                long_best_price = tick.last_price
                short_best_price = tick.last_price

            # Check whether stop order can be triggered.
            long_cross = stop_order.direction == Direction.LONG and stop_order.price <= long_cross_price

            short_cross = stop_order.direction == Direction.SHORT and stop_order.price >= short_cross_price

            if not long_cross and not short_cross:
                continue

            # Create order data.
            self.limit_order_count += 1
            symbol, exchange = extract_vt_symbol(vt_symbol)
            order = OrderData(
                symbol=symbol,
                exchange=exchange,
                orderid=str(self.limit_order_count),
                direction=stop_order.direction,
                offset=stop_order.offset,
                price=stop_order.price,
                volume=stop_order.volume,
                status=Status.ALLTRADED,
                gateway_name=self.gateway_name,
            )
            order.datetime = self.last_dt
            self.write_log(f'停止单被触发:\n{stop_order.__dict__}\n=>委托单{order.__dict__}')
            self.limit_orders[order.vt_orderid] = order

            # Create trade data.
            if long_cross:
                trade_price = max(stop_order.price, long_best_price)
            else:
                trade_price = min(stop_order.price, short_best_price)

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
                time=self.last_dt.strftime("%Y-%m-%d %H:%M:%S"),
                datetime=self.last_dt,
                gateway_name=self.gateway_name,
            )
            trade.strategy_name = strategy.strategy_name
            trade.datetime = self.last_dt
            self.write_log(f'停止单触发成交:{trade.__dict__}')
            self.trade_dict[trade.vt_tradeid] = trade
            self.trades[trade.vt_tradeid] = copy.copy(trade)

            # Update stop order.
            stop_order.vt_orderids.append(order.vt_orderid)
            stop_order.status = StopOrderStatus.TRIGGERED

            self.active_stop_orders.pop(stop_order.stop_orderid)

            # Push update to strategy.
            strategy.on_stop_order(stop_order)
            strategy.on_order(order)
            self.append_trade(trade)
            holding = self.get_position_holding(vt_symbol=trade.vt_symbol)
            holding.update_trade(trade)
            strategy.on_trade(trade)

    def cross_limit_order(self, bar: BarData = None, tick: TickData = None):
        """基于最新数据撮合限价单"""

        vt_symbol = bar.vt_symbol if bar else tick.vt_symbol

        # 遍历限价单字典中的所有限价单
        for vt_orderid in list(self.active_limit_orders.keys()):
            order = self.active_limit_orders.get(vt_orderid, None)
            if order.vt_symbol != vt_symbol:
                continue

            strategy = self.order_strategy_dict.get(order.vt_orderid, None)
            if strategy is None:
                self.write_error(u'找不到vt_orderid:{}对应的策略'.format(order.vt_orderid))
                continue
            if bar:
                buy_cross_price = round_to(value=bar.low_price,
                                           target=self.get_price_tick(vt_symbol)) + self.get_price_tick(
                    vt_symbol)  # 若买入方向限价单价格高于该价格，则会成交
                sell_cross_price = round_to(value=bar.high_price,
                                            target=self.get_price_tick(vt_symbol)) - self.get_price_tick(
                    vt_symbol)  # 若卖出方向限价单价格低于该价格，则会成交
                buy_best_cross_price = round_to(value=bar.open_price,
                                                target=self.get_price_tick(vt_symbol)) + self.get_price_tick(
                    vt_symbol)  # 在当前时间点前发出的买入委托可能的最优成交价
                sell_best_cross_price = round_to(value=bar.open_price,
                                                 target=self.get_price_tick(vt_symbol)) - self.get_price_tick(
                    vt_symbol)  # 在当前时间点前发出的卖出委托可能的最优成交价
            else:
                buy_cross_price = tick.last_price
                sell_cross_price = tick.last_price
                buy_best_cross_price = tick.last_price
                sell_best_cross_price = tick.last_price

            # 判断是否会成交
            buy_cross = order.direction == Direction.LONG and order.price >= buy_cross_price
            sell_cross = order.direction == Direction.SHORT and order.price <= sell_cross_price

            # 如果发生了成交
            if buy_cross or sell_cross:
                # 推送成交数据
                self.trade_count += 1  # 成交编号自增1

                trade_id = str(self.trade_count)
                symbol, exchange = extract_vt_symbol(vt_symbol)
                trade = TradeData(
                    gateway_name=self.gateway_name,
                    symbol=symbol,
                    exchange=exchange,
                    tradeid=trade_id,
                    orderid=order.orderid,
                    direction=order.direction,
                    offset=order.offset,
                    volume=order.volume,
                    time=self.last_dt.strftime("%Y-%m-%d %H:%M:%S"),
                    datetime=self.last_dt
                )

                # 以买入为例：
                # 1. 假设当根K线的OHLC分别为：100, 125, 90, 110
                # 2. 假设在上一根K线结束(也是当前K线开始)的时刻，策略发出的委托为限价105
                # 3. 则在实际中的成交价会是100而不是105，因为委托发出时市场的最优价格是100
                if buy_cross:
                    trade_price = min(order.price, buy_best_cross_price)

                else:
                    trade_price = max(order.price, sell_best_cross_price)
                trade.price = trade_price

                # 记录该合约来自哪个策略实例
                trade.strategy_name = strategy.strategy_name

                strategy.on_trade(trade)

                for cov_trade in self.convert_spd_trade(trade):
                    self.trade_dict[cov_trade.vt_tradeid] = cov_trade
                    self.trades[cov_trade.vt_tradeid] = copy.copy(cov_trade)
                    self.write_log(u'vt_trade_id:{0}'.format(cov_trade.vt_tradeid))

                    # 更新持仓缓存数据
                    pos_buffer = self.pos_holding_dict.get(cov_trade.vt_symbol, None)
                    if not pos_buffer:
                        pos_buffer = PositionHolding(self.get_contract(vt_symbol))
                        self.pos_holding_dict[cov_trade.vt_symbol] = pos_buffer
                    pos_buffer.update_trade(cov_trade)
                    self.write_log(u'{} : crossLimitOrder: TradeId:{},  posBuffer = {}'.format(cov_trade.strategy_name,
                                                                                               cov_trade.tradeid,
                                                                                               pos_buffer.to_str()))

                    # 写入交易记录
                    self.append_trade(cov_trade)

                    # 更新资金曲线
                    if 'SPD' not in cov_trade.vt_symbol:
                        fund_kline = self.get_fund_kline(cov_trade.strategy_name)
                        if fund_kline:
                            fund_kline.update_trade(cov_trade)

                # 推送委托数据
                order.traded = order.volume
                order.status = Status.ALLTRADED

                strategy.on_order(order)

                # 从字典中删除该限价单
                self.active_limit_orders.pop(vt_orderid, None)

        # 实时计算模式
        self.realtime_calculate()

    def convert_spd_trade(self, trade):
        """转换为品种对的交易记录"""
        if trade.exchange != Exchange.SPD:
            return [trade]

        try:
            active_symbol, active_rate, passive_symbol, passive_rate, spd_type = trade.symbol.split('-')
            active_rate = int(active_rate)
            passive_rate = int(passive_rate)
            active_exchange = self.get_exchange(active_symbol)
            active_vt_symbol = active_symbol + '.' + active_exchange.value
            passive_exchange = self.get_exchange(passive_symbol)
            # passive_vt_symbol = active_symbol + '.' + passive_exchange.value
            # 主动腿成交记录
            act_trade = TradeData(gateway_name=self.gateway_name,
                                  symbol=active_symbol,
                                  exchange=active_exchange,
                                  orderid='spd_' + str(trade.orderid),
                                  tradeid='spd_act_' + str(trade.tradeid),
                                  direction=trade.direction,
                                  offset=trade.offset,
                                  strategy_name=trade.strategy_name,
                                  price=self.get_price(active_vt_symbol),
                                  volume=int(trade.volume * active_rate),
                                  time=trade.time,
                                  datetime=trade.datetime
                                  )

            # 被动腿成交记录
            # 交易方向与spd合约方向相反
            pas_trade = TradeData(gateway_name=self.gateway_name,
                                  symbol=passive_symbol,
                                  exchange=passive_exchange,
                                  orderid='spd_' + str(trade.orderid),
                                  tradeid='spd_pas_' + str(trade.tradeid),
                                  direction=Direction.LONG if trade.direction == Direction.SHORT else Direction.SHORT,
                                  offset=trade.offset,
                                  strategy_name=trade.strategy_name,
                                  time=trade.time,
                                  datetime=trade.datetime
                                  )

            # 根据套利合约的类型+主合约的价格，反向推导出被动合约的价格

            if spd_type == 'BJ':
                pas_trade.price = (act_trade.price * active_rate * 100 / trade.price) / passive_rate
            else:
                pas_trade.price = (act_trade.price * active_rate - trade.price) / passive_rate

            pas_trade.price = round_to(value=pas_trade.price, target=self.get_price_tick(pas_trade.vt_symbol))
            pas_trade.volume = int(trade.volume * passive_rate)
            pas_trade.time = trade.time

            # 返回原交易记录，主动腿交易记录，被动腿交易记录
            return [trade, act_trade, pas_trade]

        except Exception as ex:
            self.write_error(u'转换主动/被动腿异常:{}'.format(str(ex)))
            return [trade]

    def update_pos_buffer(self):
        """更新持仓信息,把今仓=>昨仓"""

        for k, v in self.pos_holding_dict.items():
            if v.long_td > 0:
                self.write_log(u'调整多单持仓:今仓{}=> 0 昨仓{} => 昨仓:{}'.format(v.long_td, v.long_yd, v.long_pos))
                v.long_td = 0
                v.longYd = v.long_pos

            if v.short_td > 0:
                self.write_log(u'调整空单持仓:今仓{}=> 0 昨仓{} => 昨仓:{}'.format(v.short_td, v.short_yd, v.short_pos))
                v.short_td = 0
                v.short_yd = v.short_pos

    def get_data_path(self):
        """
        获取数据保存目录
        :return:
        """
        if self.data_path is not None:
            data_folder = self.data_path
        else:
            data_folder = os.path.abspath(os.path.join(os.getcwd(), 'data'))
            self.data_path = data_folder
        if not os.path.exists(data_folder):
            os.makedirs(data_folder)
        return data_folder

    def get_logs_path(self):
        """
        获取日志保存目录
        :return:
        """
        if self.logs_path is not None:
            logs_folder = self.logs_path
        else:
            logs_folder = os.path.abspath(os.path.join(os.getcwd(), 'log'))
            self.logs_path = logs_folder

        if not os.path.exists(logs_folder):
            os.makedirs(logs_folder)

        return logs_folder

    def create_logger(self, strategy_name=None, debug=False):
        """
        创建日志
        :param strategy_name 策略实例名称
        :param debug:是否详细记录日志
        :return:
        """
        if strategy_name is None:
            filename = os.path.abspath(os.path.join(self.get_logs_path(), '{}'.format(
                self.test_name if len(self.test_name) > 0 else 'portfolio_test')))
            print(u'create logger:{}'.format(filename))
            self.logger = setup_logger(file_name=filename,
                                       name=self.test_name,
                                       log_level=logging.DEBUG if debug else logging.ERROR,
                                       backtesing=True)
        else:
            filename = os.path.abspath(
                os.path.join(self.get_logs_path(), '{}_{}'.format(self.test_name, str(strategy_name))))
            print(u'create logger:{}'.format(filename))
            self.strategy_loggers[strategy_name] = setup_logger(file_name=filename,
                                                                name=str(strategy_name),
                                                                log_level=logging.DEBUG if debug else logging.ERROR,
                                                                backtesing=True)

    def write_log(self, msg: str, strategy_name: str = None, level: int = logging.DEBUG):
        """记录日志"""
        # log = str(self.datetime) + ' ' + content
        # self.logList.append(log)

        if strategy_name is None:
            # 写入本地log日志
            if self.logger:
                self.logger.log(msg=msg, level=level)
            else:
                self.create_logger(debug=self.debug)
        else:
            if strategy_name in self.strategy_loggers:
                self.strategy_loggers[strategy_name].log(msg=msg, level=level)
            else:
                self.create_logger(strategy_name=strategy_name, debug=self.debug)

    def write_error(self, msg, strategy_name=None):
        """记录异常"""

        if strategy_name is None:
            if self.logger:
                self.logger.error(msg)
            else:
                self.create_logger(debug=self.debug)
        else:
            if strategy_name in self.strategy_loggers:
                self.strategy_loggers[strategy_name].error(msg)
            else:
                self.create_logger(strategy_name=strategy_name, debug=self.debug)
                try:
                    self.strategy_loggers[strategy_name].error(msg)
                except Exception as ex:
                    print('{}'.format(datetime.now()), file=sys.stderr)
                    print('could not create cta logger for {},excption:{},trace:{}'.format(strategy_name, str(ex),
                                                                                           traceback.format_exc()))
                    print(msg, file=sys.stderr)

    def output(self, content):
        """输出内容"""
        print(self.test_name + "\t" + content)

    def realtime_calculate(self):
        """实时计算交易结果
        支持多空仓位并存"""

        if len(self.trade_dict) < 1:
            return

        # 获取所有未处理得成交单
        vt_tradeids = list(self.trade_dict.keys())

        result_list = []  # 保存交易记录
        longid = ''
        shortid = ''

        # 对交易记录逐一处理
        for vt_tradeid in vt_tradeids:

            trade = self.trade_dict.pop(vt_tradeid, None)
            if trade is None:
                continue

            if trade.volume == 0:
                continue
            # buy trade
            if trade.direction == Direction.LONG and trade.offset == Offset.OPEN:
                self.write_log(f'{trade.vt_symbol} buy, price:{trade.price},volume:{trade.volume}')
                # 放入多单仓位队列
                self.long_position_list.append(trade)

            # cover trade，
            elif trade.direction == Direction.LONG and trade.offset == Offset.CLOSE:
                g_id = trade.vt_tradeid  # 交易组（多个平仓数为一组）
                g_result = None  # 组合的交易结果

                cover_volume = trade.volume
                self.write_log(f'{trade.vt_symbol} cover:{cover_volume}')
                while cover_volume > 0:
                    # 如果当前没有空单，属于异常行为
                    if len(self.short_position_list) == 0:
                        self.write_error(u'异常!没有空单持仓，不能cover')
                        raise Exception(u'异常!没有空单持仓，不能cover')
                        return

                    cur_short_pos_list = [s_pos.volume for s_pos in self.short_position_list]

                    self.write_log(u'{}当前空单:{}'.format(trade.vt_symbol, cur_short_pos_list))

                    # 来自同一策略，同一合约才能撮合
                    pop_indexs = [i for i, val in enumerate(self.short_position_list) if
                                  val.vt_symbol == trade.vt_symbol and val.strategy_name == trade.strategy_name]

                    if len(pop_indexs) < 1:
                        self.write_error(u'异常，{}没有对应symbol:{}的空单持仓'.format(trade.strategy_name, trade.vt_symbol))
                        raise Exception(u'realtimeCalculate2() Exception,没有对应symbol:{0}的空单持仓'.format(trade.vt_symbol))
                        return

                    pop_index = pop_indexs[0]
                    # 从未平仓的空头交易
                    open_trade = self.short_position_list.pop(pop_index)

                    # 开空volume，不大于平仓volume
                    if cover_volume >= open_trade.volume:
                        self.write_log(f'cover volume:{cover_volume}, 满足:{open_trade.volume}')
                        cover_volume = cover_volume - open_trade.volume
                        if cover_volume > 0:
                            self.write_log(u'剩余待平数量:{}'.format(cover_volume))

                        self.write_log(
                            f'{open_trade.vt_symbol} coverd, price: {trade.price},volume:{open_trade.volume}')

                        result = TradingResult(open_price=open_trade.price,
                                               open_datetime=open_trade.datetime,
                                               exit_price=trade.price,
                                               close_datetime=trade.datetime,
                                               volume=-open_trade.volume,
                                               rate=self.get_commission_rate(trade.vt_symbol),
                                               slippage=self.get_slippage(trade.vt_symbol),
                                               size=self.get_size(trade.vt_symbol),
                                               group_id=g_id,
                                               fix_commission=self.get_fix_commission(trade.vt_symbol))

                        t = OrderedDict()
                        t['gid'] = g_id
                        t['strategy'] = open_trade.strategy_name
                        t['vt_symbol'] = open_trade.vt_symbol
                        t['open_time'] = open_trade.time
                        t['open_price'] = open_trade.price
                        t['direction'] = u'Short'
                        t['close_time'] = trade.time
                        t['close_price'] = trade.price
                        t['volume'] = open_trade.volume
                        t['profit'] = result.pnl
                        t['commission'] = result.commission
                        self.trade_pnl_list.append(t)

                        # 非自定义套利对，才更新到策略盈亏
                        if not open_trade.vt_symbol.endswith('SPD'):
                            # 更新策略实例的累加盈亏
                            self.pnl_strategy_dict.update(
                                {open_trade.strategy_name: self.pnl_strategy_dict.get(open_trade.strategy_name,
                                                                                      0) + result.pnl})

                            msg = u'gid:{} {}[{}:开空tid={}:{}]-[{}.平空tid={},{},vol:{}],净盈亏pnl={},手续费:{}' \
                                .format(g_id, open_trade.vt_symbol, open_trade.time, shortid, open_trade.price,
                                        trade.time, vt_tradeid, trade.price,
                                        open_trade.volume, result.pnl, result.commission)

                            self.write_log(msg)
                        result_list.append(result)

                        if g_result is None:
                            if cover_volume > 0:
                                # 属于组合
                                g_result = copy.deepcopy(result)

                        else:
                            # 更新组合的数据
                            g_result.turnover = g_result.turnover + result.turnover
                            g_result.commission = g_result.commission + result.commission
                            g_result.slippage = g_result.slippage + result.slippage
                            g_result.pnl = g_result.pnl + result.pnl

                            # 所有仓位平完
                            if cover_volume == 0:
                                self.write_log(u'所有平空仓位撮合完毕')
                                g_result.volume = abs(trade.volume)

                    # 开空volume,大于平仓volume，需要更新减少tradeDict的数量。
                    else:
                        remain_volume = open_trade.volume - cover_volume
                        self.write_log(f'{open_trade.vt_symbol} short pos: {open_trade.volume} => {remain_volume}')

                        result = TradingResult(open_price=open_trade.price,
                                               open_datetime=open_trade.datetime,
                                               exit_price=trade.price,
                                               close_datetime=trade.datetime,
                                               volume=-cover_volume,
                                               rate=self.get_commission_rate(trade.vt_symbol),
                                               slippage=self.get_slippage(trade.vt_symbol),
                                               size=self.get_size(trade.vt_symbol),
                                               group_id=g_id,
                                               fix_commission=self.get_fix_commission(trade.vt_symbol))

                        t = OrderedDict()
                        t['gid'] = g_id
                        t['strategy'] = open_trade.strategy_name
                        t['vt_symbol'] = open_trade.vt_symbol
                        t['open_time'] = open_trade.time
                        t['open_price'] = open_trade.price
                        t['direction'] = u'Short'
                        t['close_time'] = trade.time
                        t['close_price'] = trade.price
                        t['volume'] = cover_volume
                        t['profit'] = result.pnl
                        t['commission'] = result.commission
                        self.trade_pnl_list.append(t)

                        # 非自定义套利对，才更新盈亏
                        if not (open_trade.vt_symbol.endswith('SPD') or open_trade.vt_symbol.endswith('SPD99')):
                            # 更新策略实例的累加盈亏
                            self.pnl_strategy_dict.update(
                                {open_trade.strategy_name: self.pnl_strategy_dict.get(open_trade.strategy_name,
                                                                                      0) + result.pnl})

                            msg = u'gid:{} {}[{}:开空tid={}:{}]-[{}.平空tid={},{},vol:{}],净盈亏pnl={},手续费:{}' \
                                .format(g_id, open_trade.vt_symbol, open_trade.time, shortid, open_trade.price,
                                        trade.time, vt_tradeid, trade.price,
                                        cover_volume, result.pnl, result.commission)

                            self.write_log(msg)

                        # 更新（减少）开仓单的volume,重新推进开仓单列表中
                        open_trade.volume = remain_volume
                        self.write_log(u'更新（减少）开仓单的volume,重新推进开仓单列表中:{}'.format(open_trade.volume))
                        self.short_position_list.append(open_trade)
                        cur_short_pos_list = [s_pos.volume for s_pos in self.short_position_list]
                        self.write_log(u'当前空单:{}'.format(cur_short_pos_list))

                        cover_volume = 0
                        result_list.append(result)

                        if g_result is not None:
                            # 更新组合的数据
                            g_result.turnover = g_result.turnover + result.turnover
                            g_result.commission = g_result.commission + result.commission
                            g_result.slippage = g_result.slippage + result.slippage
                            g_result.pnl = g_result.pnl + result.pnl
                            g_result.volume = abs(trade.volume)

                if g_result is not None:
                    self.write_log(u'组合净盈亏:{0}'.format(g_result.pnl))

            # Short Trade
            elif trade.direction == Direction.SHORT and trade.offset == Offset.OPEN:
                self.write_log(f'{trade.vt_symbol}, short: price:{trade.price},volume{trade.volume}')
                self.short_position_list.append(trade)
                continue

            # sell trade
            elif trade.direction == Direction.SHORT and trade.offset == Offset.CLOSE:
                g_id = trade.vt_tradeid  # 交易组（多个平仓数为一组）
                g_result = None  # 组合的交易结果

                sell_volume = trade.volume

                while sell_volume > 0:
                    if len(self.long_position_list) == 0:
                        self.write_error(f'异常，没有{trade.vt_symbol}的多仓')
                        raise RuntimeError(u'realtimeCalculate2() Exception,没有开多单')
                        return

                    pop_indexs = [i for i, val in enumerate(self.long_position_list) if
                                  val.vt_symbol == trade.vt_symbol and val.strategy_name == trade.strategy_name]
                    if len(pop_indexs) < 1:
                        self.write_error(f'没有{trade.strategy_name}对应的symbol{trade.vt_symbol}多单数据,')
                        raise RuntimeError(
                            f'realtimeCalculate2() Exception,没有对应的symbol{trade.vt_symbol}多单数据,')
                        return

                    cur_long_pos_list = [s_pos.volume for s_pos in self.long_position_list]

                    self.write_log(u'{}当前多单:{}'.format(trade.vt_symbol, cur_long_pos_list))

                    pop_index = pop_indexs[0]
                    open_trade = self.long_position_list.pop(pop_index)
                    # 开多volume，不大于平仓volume
                    if sell_volume >= open_trade.volume:
                        self.write_log(f'{open_trade.vt_symbol},Sell Volume:{sell_volume} 满足:{open_trade.volume}')
                        sell_volume = sell_volume - open_trade.volume

                        self.write_log(f'{open_trade.vt_symbol},sell, price:{trade.price},volume:{open_trade.volume}')

                        result = TradingResult(open_price=open_trade.price,
                                               open_datetime=open_trade.datetime,
                                               exit_price=trade.price,
                                               close_datetime=trade.datetime,
                                               volume=open_trade.volume,
                                               rate=self.get_commission_rate(trade.vt_symbol),
                                               slippage=self.get_slippage(trade.vt_symbol),
                                               size=self.get_size(trade.vt_symbol),
                                               group_id=g_id,
                                               fix_commission=self.get_fix_commission(trade.vt_symbol))

                        t = OrderedDict()
                        t['gid'] = g_id
                        t['strategy'] = open_trade.strategy_name
                        t['vt_symbol'] = open_trade.vt_symbol
                        t['open_time'] = open_trade.time
                        t['open_price'] = open_trade.price
                        t['direction'] = u'Long'
                        t['close_time'] = trade.time
                        t['close_price'] = trade.price
                        t['volume'] = open_trade.volume
                        t['profit'] = result.pnl
                        t['commission'] = result.commission
                        self.trade_pnl_list.append(t)

                        # 非自定义套利对，才更新盈亏
                        if not (open_trade.vt_symbol.endswith('SPD') or open_trade.vt_symbol.endswith('SPD99')):
                            # 更新策略实例的累加盈亏
                            self.pnl_strategy_dict.update(
                                {open_trade.strategy_name: self.pnl_strategy_dict.get(open_trade.strategy_name,
                                                                                      0) + result.pnl})

                            msg = u'gid:{} {}[{}:开多tid={}:{}]-[{}.平多tid={},{},vol:{}],净盈亏pnl={},手续费:{}' \
                                .format(g_id, open_trade.vt_symbol,
                                        open_trade.time, longid, open_trade.price,
                                        trade.time, vt_tradeid, trade.price,
                                        open_trade.volume, result.pnl, result.commission)

                            self.write_log(msg)
                        result_list.append(result)

                        if g_result is None:
                            if sell_volume > 0:
                                # 属于组合
                                g_result = copy.deepcopy(result)
                        else:
                            # 更新组合的数据
                            g_result.turnover = g_result.turnover + result.turnover
                            g_result.commission = g_result.commission + result.commission
                            g_result.slippage = g_result.slippage + result.slippage
                            g_result.pnl = g_result.pnl + result.pnl

                            if sell_volume == 0:
                                g_result.volume = abs(trade.volume)

                    # 开多volume,大于平仓volume，需要更新减少tradeDict的数量。
                    else:
                        remain_volume = open_trade.volume - sell_volume
                        self.write_log(f'{open_trade.vt_symbol} short pos: {open_trade.volume} => {remain_volume}')

                        result = TradingResult(open_price=open_trade.price,
                                               open_datetime=open_trade.datetime,
                                               exit_price=trade.price,
                                               close_datetime=trade.datetime,
                                               volume=sell_volume,
                                               rate=self.get_commission_rate(trade.vt_symbol),
                                               slippage=self.get_slippage(trade.vt_symbol),
                                               size=self.get_size(trade.vt_symbol),
                                               group_id=g_id,
                                               fix_commission=self.get_fix_commission(trade.vt_symbol))

                        t = OrderedDict()
                        t['gid'] = g_id
                        t['strategy'] = open_trade.strategy_name
                        t['vt_symbol'] = open_trade.vt_symbol
                        t['open_time'] = open_trade.time
                        t['open_price'] = open_trade.price
                        t['direction'] = u'Long'
                        t['close_time'] = trade.time
                        t['close_price'] = trade.price
                        t['volume'] = sell_volume
                        t['profit'] = result.pnl
                        t['commission'] = result.commission
                        self.trade_pnl_list.append(t)

                        # 非自定义套利对，才更新盈亏
                        if not (open_trade.vt_symbol.endswith('SPD') or open_trade.vt_symbol.endswith('SPD99')):
                            # 更新策略实例的累加盈亏
                            self.pnl_strategy_dict.update(
                                {open_trade.strategy_name: self.pnl_strategy_dict.get(open_trade.strategy_name,
                                                                                      0) + result.pnl})

                            msg = u'Gid:{} {}[{}:开多tid={}:{}]-[{}.平多tid={},{},vol:{}],净盈亏pnl={},手续费:{}' \
                                .format(g_id, open_trade.vt_symbol, open_trade.time, longid, open_trade.price,
                                        trade.time, vt_tradeid, trade.price, sell_volume, result.pnl,
                                        result.commission)

                            self.write_log(msg)

                        # 减少开多volume,重新推进多单持仓列表中
                        open_trade.volume = remain_volume
                        self.long_position_list.append(open_trade)

                        sell_volume = 0
                        result_list.append(result)

                        if g_result is not None:
                            # 更新组合的数据
                            g_result.turnover = g_result.turnover + result.turnover
                            g_result.commission = g_result.commission + result.commission
                            g_result.slippage = g_result.slippage + result.slippage
                            g_result.pnl = g_result.pnl + result.pnl
                            g_result.volume = abs(trade.volume)

                if g_result is not None:
                    self.write_log(u'组合净盈亏:{0}'.format(g_result.pnl))

        # 计算仓位比例
        occupy_money = 0.0  # 保证金
        occupy_long_money_dict = {}  # 多单保证金，key为合约短号，value为保证金
        occupy_short_money_dict = {}  # 空单保证金，key为合约短号，value为保证金
        occupy_underly_symbol_set = set()  # 所有合约短号

        long_pos_dict = {}
        short_pos_dict = {}
        if len(self.long_position_list) > 0:
            for t in self.long_position_list:
                # 不计算套利合约的持仓占用保证金
                if t.vt_symbol.endswith('SPD') or t.vt_symbol.endswith('SPD99'):
                    continue
                # 当前持仓的保证金
                if self.use_margin:
                    cur_occupy_money = t.price * abs(t.volume) * self.get_size(t.vt_symbol) * self.get_margin_rate(
                        t.vt_symbol)
                else:
                    cur_occupy_money = self.get_price(t.vt_symbol) * abs(t.volume) * self.get_size(
                        t.vt_symbol) * self.get_margin_rate(t.vt_symbol)

                # 更新该合约短号的累计保证金
                underly_symbol = get_underlying_symbol(t.symbol)
                occupy_underly_symbol_set.add(underly_symbol)
                occupy_long_money_dict.update(
                    {underly_symbol: occupy_long_money_dict.get(underly_symbol, 0) + cur_occupy_money})

                if t.vt_symbol in long_pos_dict:
                    long_pos_dict[t.vt_symbol] += abs(t.volume)
                else:
                    long_pos_dict[t.vt_symbol] = abs(t.volume)

        if len(self.short_position_list) > 0:
            for t in self.short_position_list:
                # 不计算套利合约的持仓占用保证金
                if t.vt_symbol.endswith('SPD') or t.vt_symbol.endswith('SPD99'):
                    continue
                # 当前空单保证金
                if self.use_margin:
                    cur_occupy_money = max(self.get_price(t.vt_symbol), t.price) * abs(t.volume) * self.get_size(
                        t.vt_symbol) * self.get_margin_rate(t.vt_symbol)
                else:
                    cur_occupy_money = self.get_price(t.vt_symbol) * abs(t.volume) * self.get_size(
                        t.vt_symbol) * self.get_margin_rate(t.vt_symbol)

                # 该合约短号的累计空单保证金
                underly_symbol = get_underlying_symbol(t.symbol)
                occupy_underly_symbol_set.add(underly_symbol)
                occupy_short_money_dict.update(
                    {underly_symbol: occupy_short_money_dict.get(underly_symbol, 0) + cur_occupy_money})

                if t.vt_symbol in short_pos_dict:
                    short_pos_dict[t.vt_symbol] += abs(t.volume)
                else:
                    short_pos_dict[t.vt_symbol] = abs(t.volume)

        # 计算多空的保证金累加（对锁的取最大值)
        for underly_symbol in occupy_underly_symbol_set:
            occupy_money += max(occupy_long_money_dict.get(underly_symbol, 0),
                                occupy_short_money_dict.get(underly_symbol, 0))

        # 可用资金 = 当前净值 - 占用保证金
        self.avaliable = self.net_capital - occupy_money
        # 当前保证金占比
        self.percent = round(float(occupy_money * 100 / self.net_capital), 2)
        # 更新最大保证金占比
        self.max_occupy_rate = max(self.max_occupy_rate, self.percent)

        # 检查是否有平交易
        if len(result_list) == 0:
            msg = u''
            if len(self.long_position_list) > 0:
                msg += u'持多仓{0},'.format(str(long_pos_dict))

            if len(self.short_position_list) > 0:
                msg += u'持空仓{0},'.format(str(short_pos_dict))

            msg += u'资金占用:{0},仓位:{1}%%'.format(occupy_money, self.percent)

            self.write_log(msg)
            return

        # 对交易结果汇总统计
        for result in result_list:
            if result.pnl > 0:
                self.winning_result += 1
                self.total_winning += result.pnl
            else:
                self.losing_result += 1
                self.total_losing += result.pnl
            self.cur_capital += result.pnl
            self.max_capital = max(self.cur_capital, self.max_capital)
            self.net_capital = max(self.net_capital, self.cur_capital)
            self.max_net_capital = max(self.net_capital, self.max_net_capital)
            # self.maxVolume = max(self.maxVolume, result.volume)
            drawdown = self.net_capital - self.max_net_capital
            drawdown_rate = round(float(drawdown * 100 / self.max_net_capital), 4)

            self.pnl_list.append(result.pnl)
            self.time_list.append(result.close_datetime)
            self.capital_list.append(self.cur_capital)
            self.drawdown_list.append(drawdown)
            self.drawdown_rate_list.append(drawdown_rate)

            self.total_trade_count += 1
            self.total_turnover += result.turnover
            self.total_commission += result.commission
            self.total_slippage += result.slippage

            msg = u'[gid:{}] {} 交易盈亏:{},交易手续费:{}回撤:{}/{},账号平仓权益:{},持仓权益：{}，累计手续费:{}' \
                .format(result.group_id, result.close_datetime, result.pnl, result.commission, drawdown,
                        drawdown_rate, self.cur_capital, self.net_capital, self.total_commission)

            self.write_log(msg)

        # 重新计算一次avaliable
        self.avaliable = self.net_capital - occupy_money
        self.percent = round(float(occupy_money * 100 / self.net_capital), 2)

    def saving_daily_data(self, d, c, m, commission, benchmark=0):
        """保存每日数据"""
        data = {}
        data['date'] = d.strftime('%Y/%m/%d')  # 日期
        data['capital'] = c  # 当前平仓净值
        data['max_capital'] = m  # 之前得最高净值
        today_holding_profit = 0  # 持仓浮盈
        long_pos_occupy_money = 0
        short_pos_occupy_money = 0
        strategy_pnl = {}
        for strategy in self.strategies.keys():
            strategy_pnl.update({strategy: self.pnl_strategy_dict.get(strategy, 0)})

        positionMsg = ""
        for longpos in self.long_position_list:
            # 不计算套利合约的持仓盈亏
            if longpos.vt_symbol.endswith('SPD') or longpos.vt_symbol.endswith('SPD99'):
                continue
            symbol = longpos.vt_symbol
            # 计算持仓浮盈浮亏/占用保证金
            holding_profit = 0
            last_price = self.get_price(symbol)
            if last_price is not None:
                holding_profit = (last_price - longpos.price) * longpos.volume * self.get_size(symbol)
                long_pos_occupy_money += last_price * abs(longpos.volume) * self.get_size(
                    symbol) * self.get_margin_rate(symbol)

            # 账号的持仓盈亏
            today_holding_profit += holding_profit

            # 计算每个策略实例的持仓盈亏
            strategy_pnl.update({longpos.strategy_name: strategy_pnl.get(longpos.strategy_name, 0) + holding_profit})

            positionMsg += "{},long,p={},v={},m={};".format(symbol, longpos.price, longpos.volume, holding_profit)

        for shortpos in self.short_position_list:
            # 不计算套利合约的持仓盈亏
            if shortpos.vt_symbol.endswith('SPD') or shortpos.vt_symbol.endswith('SPD99'):
                continue
            symbol = shortpos.vt_symbol
            # 计算持仓浮盈浮亏/占用保证金
            holding_profit = 0
            last_price = self.get_price(symbol)
            if last_price is not None:
                holding_profit = (shortpos.price - last_price) * shortpos.volume * self.get_size(symbol)
                short_pos_occupy_money += last_price * abs(shortpos.volume) * self.get_size(
                    symbol) * self.get_margin_rate(symbol)

            # 账号的持仓盈亏
            today_holding_profit += holding_profit
            # 计算每个策略实例的持仓盈亏
            strategy_pnl.update({shortpos.strategy_name: strategy_pnl.get(shortpos.strategy_name, 0) + holding_profit})

            positionMsg += "{},short,p={},v={},m={};".format(symbol, shortpos.price, shortpos.volume, holding_profit)

        data['net'] = c + today_holding_profit  # 当日净值（含持仓盈亏）
        data['rate'] = (c + today_holding_profit) / self.init_capital
        data['occupy_money'] = max(long_pos_occupy_money, short_pos_occupy_money)
        data['occupy_rate'] = data['occupy_money'] / data['capital']
        data['commission'] = commission

        data.update(self.price_dict)

        data.update(strategy_pnl)

        self.daily_list.append(data)

        # 更新每日浮动净值
        self.net_capital = data['net']

        # 更新最大初次持仓浮盈净值
        if data['net'] > self.max_net_capital:
            self.max_net_capital = data['net']
            self.max_net_capital_time = data['date']
        drawdown_rate = round((float(self.max_net_capital - data['net']) * 100) / self.max_net_capital, 4)
        if drawdown_rate > self.daily_max_drawdown_rate:
            self.daily_max_drawdown_rate = drawdown_rate
            self.max_drawdown_rate_time = data['date']

        msg = u'{}:  net={}, capital={} max={} margin={} commission={}， pos: {}' \
            .format(data['date'],
                    data['net'], c, m,
                    today_holding_profit,
                    commission,
                    positionMsg)

        if not self.debug:
            self.output(msg)
        else:
            self.write_log(msg)

        # 今仓 =》 昨仓
        for holding in self.holdings.values():
            if holding.long_td > 0:
                self.write_log(
                    f'{holding.vt_symbol} 多单今仓{holding.long_td},昨仓:{holding.long_yd}=> 昨仓:{holding.long_pos}')
                holding.long_td = 0
                holding.long_yd = holding.long_pos
            if holding.short_td > 0:
                self.write_log(
                    f'{holding.vt_symbol} 空单今仓{holding.short_td},昨仓:{holding.short_yd}=> 昨仓:{holding.short_pos}')
                holding.short_td = 0
                holding.short_yd = holding.short_pos

    # ---------------------------------------------------------------------
    def export_trade_result(self):
        """
        导出交易结果（开仓-》平仓, 平仓收益）
        导出每日净值结果表
        :return:
        """
        if len(self.trade_pnl_list) == 0:
            self.write_log('no traded records')
            return

        s = self.test_name.replace('&', '')
        s = s.replace(' ', '')
        trade_list_csv_file = os.path.abspath(os.path.join(self.get_logs_path(), '{}_trade_list.csv'.format(s)))

        self.write_log(u'save trade records to:{}'.format(trade_list_csv_file))
        import csv
        csv_write_file = open(trade_list_csv_file, 'w', encoding='utf8', newline='')

        fieldnames = ['gid', 'strategy', 'vt_symbol', 'open_time', 'open_price', 'direction', 'close_time',
                      'close_price',
                      'volume', 'profit', 'commission']

        writer = csv.DictWriter(f=csv_write_file, fieldnames=fieldnames, dialect='excel')
        writer.writeheader()

        for row in self.trade_pnl_list:
            writer.writerow(row)

        # 导出每日净值记录表
        if not self.daily_list:
            return

        if self.daily_report_name == '':
            daily_csv_file = os.path.abspath(os.path.join(self.get_logs_path(), '{}_daily_list.csv'.format(s)))
        else:
            daily_csv_file = self.daily_report_name
        self.write_log(u'save daily records to:{}'.format(daily_csv_file))

        csv_write_file2 = open(daily_csv_file, 'w', encoding='utf8', newline='')
        fieldnames = ['date', 'capital', 'net', 'max_capital', 'rate', 'commission', 'long_money', 'short_money',
                      'occupy_money', 'occupy_rate', 'today_margin_long', 'today_margin_short']
        # 添加合约的每日close价
        fieldnames.extend(sorted(self.price_dict.keys()))
        # 添加策略列表
        fieldnames.extend(sorted(self.strategies.keys()))
        writer2 = csv.DictWriter(f=csv_write_file2, fieldnames=fieldnames, dialect='excel')
        writer2.writeheader()

        for row in self.daily_list:
            writer2.writerow(row)

        if self.is_plot_daily:
            # 生成净值曲线图片
            df = pd.DataFrame(self.daily_list)
            df = df.set_index('date')
            from vnpy.trader.utility import display_dual_axis
            plot_file = os.path.abspath(os.path.join(self.get_logs_path(), '{}_plot.png'.format(s)))

            # 双坐标输出，左侧坐标是净值（比率），右侧是各策略的实际资金收益曲线
            display_dual_axis(df=df, columns1=['rate'], columns2=list(self.strategies.keys()), image_name=plot_file)

        return

    def get_result(self):
        # 返回回测结果
        d = {}
        d['init_capital'] = self.init_capital
        d['profit'] = self.cur_capital - self.init_capital
        d['max_capital'] = self.max_net_capital  # 取消原 maxCapital

        if len(self.pnl_list) == 0:
            return {}, [], []

        d['max_pnl'] = max(self.pnl_list)
        d['min_pnl'] = min(self.pnl_list)

        d['max_occupy_rate'] = self.max_occupy_rate
        d['total_trade_count'] = self.total_trade_count
        d['total_turnover'] = self.total_turnover
        d['total_commission'] = self.total_commission
        d['total_slippage'] = self.total_slippage
        d['time_list'] = self.time_list
        d['pnl_list'] = self.pnl_list
        d['capital_list'] = self.capital_list
        d['drawdown_list'] = self.drawdown_list
        d['drawdown_rate_list'] = self.drawdown_rate_list  # 净值最大回撤率列表
        d['winning_rate'] = round(100 * self.winning_result / len(self.pnl_list), 4)

        average_winning = 0  # 这里把数据都初始化为0
        average_losing = 0
        profit_loss_ratio = 0

        if self.winning_result:
            average_winning = self.total_winning / self.winning_result  # 平均每笔盈利
        if self.losing_result:
            average_losing = self.total_losing / self.losing_result  # 平均每笔亏损
        if average_losing:
            profit_loss_ratio = -average_winning / average_losing  # 盈亏比

        d['average_winning'] = average_winning
        d['average_losing'] = average_losing
        d['profit_loss_ratio'] = profit_loss_ratio

        # 计算Sharp
        if not self.daily_list:
            return {}, [], []

        capital_net_list = []
        capital_list = []
        for row in self.daily_list:
            capital_net_list.append(row['net'])
            capital_list.append(row['capital'])

        capital = pd.Series(capital_net_list)
        log_returns = np.log(capital).diff().fillna(0)
        sharpe = (log_returns.mean() * 252) / (log_returns.std() * np.sqrt(252))
        d['sharpe'] = sharpe

        return d, capital_net_list, capital_list

    def show_backtesting_result(self):
        """显示回测结果"""

        d, daily_net_capital, daily_capital = self.get_result()

        if len(d) == 0:
            self.output(u'无交易结果')
            return {}, ''

        # 导出交易清单
        self.export_trade_result()

        result_info = OrderedDict()

        # 输出
        self.output('-' * 30)
        result_info.update({u'第一笔交易': str(d['time_list'][0])})
        self.output(u'第一笔交易：\t%s' % d['time_list'][0])

        result_info.update({u'最后一笔交易': str(d['time_list'][-1])})
        self.output(u'最后一笔交易：\t%s' % d['time_list'][-1])

        result_info.update({u'总交易次数': d['total_trade_count']})
        self.output(u'总交易次数：\t%s' % format_number(d['total_trade_count']))

        result_info.update({u'期初资金': d['init_capital']})
        self.output(u'期初资金：\t%s' % format_number(d['init_capital']))

        result_info.update({u'总盈亏': d['profit']})
        self.output(u'总盈亏：\t%s' % format_number(d['profit']))

        result_info.update({u'资金最高净值': d['max_capital']})
        self.output(u'资金最高净值：\t%s' % format_number(d['max_capital']))

        result_info.update({u'资金最高净值时间': str(self.max_net_capital_time)})
        self.output(u'资金最高净值时间：\t%s' % self.max_net_capital_time)

        result_info.update({u'每笔最大盈利': d['max_pnl']})
        self.output(u'每笔最大盈利：\t%s' % format_number(d['max_pnl']))

        result_info.update({u'每笔最大亏损': d['min_pnl']})
        self.output(u'每笔最大亏损：\t%s' % format_number(d['min_pnl']))

        result_info.update({u'净值最大回撤': min(d['drawdown_list'])})
        self.output(u'净值最大回撤: \t%s' % format_number(min(d['drawdown_list'])))

        result_info.update({u'净值最大回撤率': self.daily_max_drawdown_rate})
        self.output(u'净值最大回撤率: \t%s' % format_number(self.daily_max_drawdown_rate))

        result_info.update({u'净值最大回撤时间': str(self.max_drawdown_rate_time)})
        self.output(u'净值最大回撤时间：\t%s' % self.max_drawdown_rate_time)

        result_info.update({u'胜率': d['winning_rate']})
        self.output(u'胜率：\t%s' % format_number(d['winning_rate']))

        result_info.update({u'盈利交易平均值': d['average_winning']})
        self.output(u'盈利交易平均值\t%s' % format_number(d['average_winning']))

        result_info.update({u'亏损交易平均值': d['average_losing']})
        self.output(u'亏损交易平均值\t%s' % format_number(d['average_losing']))

        result_info.update({u'盈亏比': d['profit_loss_ratio']})
        self.output(u'盈亏比：\t%s' % format_number(d['profit_loss_ratio']))

        result_info.update({u'最大资金占比': d['max_occupy_rate']})
        self.output(u'最大资金占比：\t%s' % format_number(d['max_occupy_rate']))

        result_info.update({u'平均每笔盈利': d['profit'] / d['total_trade_count']})
        self.output(u'平均每笔盈利：\t%s' % format_number(d['profit'] / d['total_trade_count']))

        result_info.update({u'平均每笔滑点成本': d['total_slippage'] / d['total_trade_count']})
        self.output(u'平均每笔滑点成本：\t%s' % format_number(d['total_slippage'] / d['total_trade_count']))

        result_info.update({u'平均每笔佣金': d['total_commission'] / d['total_trade_count']})
        self.output(u'平均每笔佣金：\t%s' % format_number(d['total_commission'] / d['total_trade_count']))

        result_info.update({u'Sharpe Ratio': d['sharpe']})
        self.output(u'Sharpe Ratio：\t%s' % format_number(d['sharpe']))

        return result_info

    def put_strategy_event(self, strategy: CtaTemplate):
        """发送策略更新事件，回测中忽略"""
        pass

    def clear_backtesting_result(self):
        """清空之前回测的结果"""
        # 清空限价单相关
        self.limit_order_count = 0
        self.limit_orders.clear()
        self.active_limit_orders.clear()

        # 清空成交相关
        self.trade_count = 0
        self.trade_dict.clear()
        self.trades.clear()
        self.trade_pnl_list = []

    def append_trade(self, trade: TradeData):
        """
        根据策略名称，写入 logs\test_name_straetgy_name_trade.csv文件
        :param trade:
        :return:
        """
        strategy_name = getattr(trade, 'strategy', self.test_name)
        trade_fields = ['symbol', 'exchange', 'vt_symbol', 'tradeid',
                        'vt_tradeid', 'orderid', 'vt_orderid',
                        'direction',
                        'offset', 'price', 'volume', 'time']

        d = OrderedDict()
        try:
            for k in trade_fields:
                if k in ['exchange', 'direction', 'offset']:
                    d[k] = getattr(trade, k).value
                else:
                    d[k] = getattr(trade, k, '')

            trade_file = os.path.abspath(os.path.join(self.get_logs_path(), '{}_trade.csv'.format(strategy_name)))
            self.append_data(file_name=trade_file, dict_data=d)
        except Exception as ex:
            self.write_error(u'写入交易记录csv出错：{},{}'.format(str(ex), traceback.format_exc()))

    #  保存记录相关
    def append_data(self, file_name: str, dict_data: OrderedDict, field_names: list = None):
        """
        添加数据到csv文件中
        :param file_name:  csv的文件全路径
        :param dict_data:  OrderedDict
        :return:
        """
        if field_names is None or field_names == []:
            dict_fieldnames = list(dict_data.keys())
        else:
            dict_fieldnames = field_names

        try:
            if not os.path.exists(file_name):
                self.write_log(u'create csv file:{}'.format(file_name))
                with open(file_name, 'a', encoding='utf8', newline='') as csvWriteFile:
                    writer = csv.DictWriter(f=csvWriteFile, fieldnames=dict_fieldnames, dialect='excel')
                    self.write_log(u'write csv header:{}'.format(dict_fieldnames))
                    writer.writeheader()
                    writer.writerow(dict_data)
            else:
                with open(file_name, 'a', encoding='utf8', newline='') as csvWriteFile:
                    writer = csv.DictWriter(f=csvWriteFile, fieldnames=dict_fieldnames, dialect='excel',
                                            extrasaction='ignore')
                    writer.writerow(dict_data)
        except Exception as ex:
            self.write_error(u'append_data exception:{}'.format(str(ex)))


########################################################################
class TradingResult(object):
    """每笔交易的结果"""

    def __init__(self, open_price, open_datetime, exit_price, close_datetime, volume, rate, slippage, size, group_id,
                 fix_commission=0.0):
        """Constructor"""
        self.open_price = open_price  # 开仓价格
        self.exit_price = exit_price  # 平仓价格

        self.open_datetime = open_datetime  # 开仓时间datetime
        self.close_datetime = close_datetime  # 平仓时间

        self.volume = volume  # 交易数量（+/-代表方向）
        self.group_id = group_id  # 主交易ID（针对多手平仓）

        self.turnover = (self.open_price + self.exit_price) * size * abs(volume)  # 成交金额
        if fix_commission > 0:
            self.commission = fix_commission * abs(self.volume)
        else:
            self.commission = abs(self.turnover * rate)  # 手续费成本
        self.slippage = slippage * 2 * size * abs(volume)  # 滑点成本
        self.pnl = ((self.exit_price - self.open_price) * volume * size
                    - self.commission - self.slippage)  # 净盈亏
