# encoding: UTF-8

"""
批量测试相关方法
# 华富资产 李来佳
"""

import sys, os, platform, gc, copy,multiprocessing
from datetime import datetime
from time import sleep
vnpy_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))

sys.path.append(vnpy_root)

import numpy as np
import pandas as pd
import talib as ta                  # 科学计算库
import statsmodels.api as sm        # 统计库
import matplotlib
import matplotlib.pyplot as plt
import math                         # 数学计算相关
matplotlib.rcParams['figure.figsize'] = (20.0, 10.0)
import  traceback
from vnpy.trader.setup_logger import *
from vnpy.trader.app.ctaStrategy.ctaBacktesting import BacktestingEngine, OptimizationSetting, MINUTE_DB_NAME


# 合并回测结果
def combine_results(results_list):
    result_df = None

    # 判断结果集是否有数据
    if len(results_list) < 1:
        print('no records')
        return None

    effected_results = 0

    for dict in results_list:
        # 测试项目
        test_item = dict['test_item']
        # 测试csv文件
        file_name = dict['result_file']

        if not os.path.isfile(file_name):
            continue

        effected_results += 1

        # 读取测试文件
        df = pd.read_csv(file_name)
        # 修正索引为时间日期索引
        df = df.set_index(pd.DatetimeIndex(df['date']))

        if result_df is None:
            # 首个测试结果，将净值字段设置为周期
            result_df = df['rate'].to_frame(name=test_item)
            # 汇总净值
            result_df['rate'] = result_df[test_item]
        else:
            # 增加新的测试结果数据
            result_df[test_item] = df['rate']

            # 汇总净值
            result_df['rate'] = result_df['rate'] + result_df[test_item]

        # 释放内存
        l = [df]
        del df
        del l

    if effected_results > 0:
        # 净值平均
        result_df['avg_rate'] = result_df['rate'] / effected_results
        # 组合净值累加（仍然按照1个策略的总资金，累加各策略的收益）
        result_df['group_rate'] = result_df['rate'] - effected_results + 1

        # 删除累加的rate
        result_df.drop('rate', axis=1, inplace=True)

    return result_df


# 计算最大回撤，单日最大回撤
def calculate_result(result_df, rate_column):
    max_rate = 0
    max_loss = 0
    max_rate_date = None
    max_loss_date = None
    max_loss_info = '-'

    for idx in result_df.index:
        # 当前日净值
        cur_rate = result_df[rate_column].loc[idx]

        if cur_rate > max_rate:
            max_rate = cur_rate
            max_rate_date = idx.strftime('%Y-%m-%d')

        cur_loss = max_rate - cur_rate

        if cur_loss > max_loss:
            max_loss = cur_loss
            max_loss_date = idx.strftime('%Y-%m-%d')
            max_loss_percent = max_loss / max_rate
            max_loss_info = u'{} from {} to {},rate {}=>{},max loss rate {}'.format(rate_column, max_rate_date,
                                                                                    max_loss_date, max_rate, cur_rate,
                                                                                    max_loss_percent)
    return max_loss_info

def single_strategy_test(test_settings):
    """
    根据设置参数，执行回测品种，
    :param strategyClass: 策略类
    :param test_settings: 策略参数设置
            test_settings['bar_file']: 回测的bar csv文件路径
            test_settings['bar_interval']: 回测的Bar csv周期
            test_settings['report_file']: 净值输出报告的保存路径
    :return: 
    """

    from vnpy.trader.vtEvent import EventEngine2
    eventEngine = EventEngine2()
    eventEngine.start()

    # 创建回测引擎
    engine = BacktestingEngine(eventEngine=eventEngine)
    # 设置回测的策略类
    engine.setStrategyName(test_settings['name'])
    # 创建日志
    if 'debug' in test_settings:
        engine.createLogger(debug=test_settings['debug'])
    else:
        engine.createLogger()

        # 设置引擎的回测模式
        if test_settings['mode'] == 'tick':
            engine.setBacktestingMode(engine.TICK_MODE)
        else:
            engine.setBacktestingMode(engine.BAR_MODE)

    strategy_settings = copy.copy(test_settings)
    # 设置回测的策略类
    if 'filenamePrefix' in strategy_settings:
        engine.setStrategyName(strategy_settings["filenamePrefix"])
    else:
        engine.setStrategyName(test_settings['name'])

    if 'is_7x24' in test_settings:
        engine.is_7x24 = test_settings['is_7x24']

    # del strategy_settings['size']
    #del strategy_settings['margin_rate']
    del strategy_settings['initCapital']

    if 'report_file' in strategy_settings:
        del strategy_settings['report_file']

    # 设置回测用的数据起始日期
    if 'start_date' in strategy_settings:
        engine.setStartDate(test_settings['start_date'], initDays = strategy_settings.get('initDays', 10))
        del strategy_settings['start_date']
    else:
        engine.setStartDate('20110101',initDays = strategy_settings.get('initDays',10))

    # 设置回测用的数据结束日期
    if 'end_date' in test_settings:
        engine.setEndDate(test_settings['end_date'])
        del strategy_settings['end_date']
    else:
        engine.setEndDate('20171201')

    # engine.connectMysql()
    engine.setDatabase(dbName=MINUTE_DB_NAME, symbol=test_settings['vtSymbol'])

    # 设置产品相关参数
    if 'slippage' in test_settings and test_settings['slippage'] > 0:
        engine.setSlippage(test_settings['slippage'])
    else:
        engine.setSlippage(0)
    engine.setRate(test_settings['rate'] if 'rate' in test_settings else float(0.0001))  # 万1
    engine.setSize(test_settings['size'])  # 合约大小
    engine.setMinDiff(test_settings['minDiff']) # 合约价格最小跳动
    engine.setMarginRate(test_settings['margin_rate']) # 合约保证金率
    if 'fixCommission' in test_settings:
        engine.fixCommission = float(test_settings['fixCommission'])  # 固定交易费用（每次开平仓收费）

    # 删除本地json文件
    data_path = os.path.abspath(os.path.join(os.getcwd(),'data'))
    if not os.path.exists(data_path):
        os.mkdir(data_path)

    logs_path = os.path.abspath(os.path.join(os.getcwd(), 'logs'))
    if not os.path.exists(logs_path):
        os.mkdir(logs_path)

    up_grid_json_file = os.path.abspath(os.path.join(data_path,'{0}_upGrids.json'.format(test_settings['name'])))
    dn_grid_json_file = os.path.abspath(os.path.join(data_path,'{0}_dnGrids.json'.format(test_settings['name'])))
    grid_json_file = os.path.abspath(os.path.join(data_path,'{0}_Grids.json'.format(test_settings['name'])))
    policy_json_file = os.path.abspath(os.path.join(data_path, '{0}_Policy.json'.format(test_settings['name'])))

    if os.path.isfile(up_grid_json_file):
        print(u'{0} exist,remove it'.format(up_grid_json_file))
        try:
            os.remove(up_grid_json_file)
        except Exception as ex:
            print(u'{0}：{1}'.format(Exception, ex))
            return False

    if os.path.isfile(dn_grid_json_file):
        print(u'{0}exist,remove it'.format(dn_grid_json_file))
        try:
            os.remove(dn_grid_json_file)
        except Exception as ex:
            print(u'{0}：{1}'.format(Exception, ex))
            return False

    if os.path.isfile(grid_json_file):
        print(u'{0}exist,remove it'.format(grid_json_file))
        try:
            os.remove(grid_json_file)
        except Exception as ex:
            print(u'{0}：{1}'.format(Exception, ex))
            return False

    if os.path.isfile(policy_json_file):
        print(u'{0}exist,remove it'.format(policy_json_file))
        try:
            os.remove(policy_json_file)
        except Exception as ex:
            print(u'{0}：{1}'.format(Exception, ex))
            return False

    # 在引擎中创建策略对象
    print(u'run {} using:{}'.format(test_settings['strategy'],strategy_settings))
    engine.initStrategy(test_settings['strategy'], setting=strategy_settings)

    # 设置每日净值的报告文档存储路径
    daily_report_file = 'DailyList.csv' if 'report_file' not in test_settings else test_settings['report_file']
    engine.setDailyReportName(daily_report_file)

    # 使用简单复利模式计算
    engine.usageCompounding = False  # True时，只针对FINAL_MODE有效

    # 启用实时计算净值模式REALTIME_MODE / FINAL_MODE 回测结束时统一计算模式
    engine.calculateMode = engine.REALTIME_MODE
    engine.capital = test_settings['initCapital']  # 设置期初资金
    engine.initCapital = test_settings['initCapital']  # 设置期初资金
    engine.avaliable = test_settings['initCapital']  # 设置期初资金
    engine.netCapital = test_settings['initCapital']
    engine.maxCapital = test_settings['initCapital']  # 设置期初资金
    engine.maxNetCapital = test_settings['initCapital']  # 设置期初资金
    engine.percentLimit = test_settings['percentLimit']  # 设置资金使用上限比例(%)
    engine.barTimeInterval = 60 * test_settings['bar_interval']  # 回测文件中，bar的周期秒数，用于csv文件自动减时间

    try:
        # 前置动作(无参数)
        pre_functions = test_settings.get('pre_functions',[])
        for fun_name in pre_functions:
            try:
                if not isinstance(fun_name,str):
                    continue
                if hasattr(engine.strategy,fun_name):
                    fun = getattr(engine.strategy,fun_name)
                    if fun is not None:
                        fun()
            except Exception as ex:
                print(u'调用前置动作异常:{},{}'.format(str(ex),traceback.format_exc()),file=sys.stderr)

        # 开始跑回测
        if 'bar_file' in test_settings:
            engine.runBackTestingWithBarFile(test_settings['bar_file'])
        else:
            engine.runBackTestingWithDataSource()

        print('{}finished loop bars'.format(test_settings['name']))
        # 显示回测结果
        engine.showBacktestingResult()

        # 保存策略得内部数据
        engine.saveStrategyData()

        print('{} finished'.format(test_settings['name']))

        return True
    except Exception as ex:
        print(u'single_strategy_test exception:{}'.format(str(ex)))
        traceback.print_exc()
        return False

def multi_period_test(gid, group_setting):
    """
    多周期回测品种组合
    1、对group_settings进行分解，分解出各个运行周期的参数设置
    2、逐一周期运行测试
    3、添加回测结果
    :param gid: 测试组名
    :param group_setting：dict，包含参数，多周期清单
     如果多周期，则对每一周期执行回测，并汇总结果。
     :return 回测的每日净值统计文件
    """

    # 回测的分钟周期
    minutes_interval_list = group_setting['minute_list']  # 回测分钟队列（3，5，10等）

    strategyClass = group_setting['strategy']

    # 测试批次时间
    test_dt = datetime.now().strftime('%Y%m%d_%H%M')

    # 回测结果队列，对应测试分钟队列
    daily_results = []
    return_results = []

    # 启动多进程
    pool = multiprocessing.Pool(multiprocessing.cpu_count())
    l = []

    # 逐一分钟级别进行回测
    for m_i in minutes_interval_list:
        settings = copy.copy(group_setting)
        del settings['minute_list']

        settings['name'] = '{}_{}_{}_M{}'.format(gid, strategyClass.className, group_setting['symbol'], m_i)

        # 资金占用比例，根据组合内周期数量，进行平均分配
        settings['percentLimit'] = group_setting['percentLimit']/ len(minutes_interval_list)
        settings['vtSymbol'] = group_setting['symbol']
        settings['MinInterval'] = m_i

        settings['mode'] = 'bar'
        settings['backtesting'] = True
        settings['bar_interval'] = group_setting['bar_interval'] if 'bar_interval' in group_setting else 1
        settings['strategy'] = strategyClass
        # 回测报告文件保存路径: 组合，测试实例名称,测试时间
        daily_report_file = os.path.abspath(os.path.join(group_setting['report_folder'], u'{}_daily_{}.csv'
                                                         .format(settings['name'], test_dt)))

        settings['report_file'] = daily_report_file

        #if rt:
            # 回测报告集登记
        daily_results.append({'test_item': 'M{}'.format(m_i), 'result_file': daily_report_file})

        l.append(pool.apply_async(single_strategy_test, (settings,)))
        #rt = single_strategy_test(test_settings=settings)

        # 执行内存回收
        gc.collect()
        sleep(10)

    result_list = [res.get() for res in l]

    for idx, rt in enumerate(result_list):
        if rt:
            return_results.append(daily_results[idx])

    pool.close()
    pool.join()
    return return_results

def run_multiperiod_test(gid, group_settings):
    """
    运行多周期的组合测试    
    :param gid: 组合名称
    :param group_settings: 
    :return: 
    """
    m = '_'.join(str(e) for e in group_settings['minute_list'])
    if 'report_folder' in group_settings:
        final_file = os.path.abspath(os.path.join(group_settings['report_folder'], '{}_{}_Report_{}.csv'.format(gid, group_settings['symbol'], m)))
    else:
        # 报告所在目录
        report_folder = os.path.abspath(os.path.join(os.getcwd(), 'logs', gid))
        if not os.path.exists(report_folder):
            os.mkdir(report_folder)
        # 汇总报告文件
        final_file = os.path.abspath(
            os.path.join(report_folder, '{}_{}_Report_{}.csv'.format(gid, group_settings['symbol'], m)))
        group_settings['report_folder'] = report_folder

    if not os.path.exists(group_settings['report_folder']):
        os.makedirs(group_settings['report_folder'])

    # 运行回测方法,统计结果
    daily_results = multi_period_test(gid, group_settings)

    # 统计结果
    backtest_df = combine_results(daily_results)

    # 保存汇总记录到文件
    backtest_df.to_csv(final_file)

    # 显示资金曲线汇总
    fig, ax1 = plt.subplots()

    period_columns = [item['test_item'] for item in daily_results]

    fig.patch.set_facecolor('white')
    ax1.plot(backtest_df[period_columns])
    ax1.legend()

    # 释放内存
    l = [backtest_df]
    del backtest_df
    del l

    # 释放内存
    gc.collect()
    print( 'finished run_multiparameter_test')

def multi_parameter_test(gid, settings_list):
    """
    不同参数的回测组合
    :param gid: 组合ID
    :param settings_list: 参数列表 
    :return: 
    """
    # 回测结果队列，对应测试参数队列
    daily_results = []
    return_results = []

    # 每个测试的参数名称
    para_list = [i['paraName'] for i in settings_list]

    if len(para_list) == 0:
        return daily_results

    # 启动多进程
    pool = multiprocessing.Pool(multiprocessing.cpu_count())
    #pool = multiprocessing.Pool(2)
    l = []

    print('multi_parameter_test,total:{}'.format(len(settings_list)))

    for idx, strategy_settings in enumerate(settings_list):
        settings = copy.copy(strategy_settings)
        # 测试时间
        test_dt = datetime.now().strftime('%Y%m%d_%H%M')

        del settings['log_file']
        if 'minute_list' in settings:
            del settings['minute_list']
        settings['vtSymbol'] = settings['symbol']
        settings['mode'] = 'bar'
        settings['backtesting'] = True
        if 'bar_interval' not in settings:
            settings['bar_interval'] = 1

        # 回测报告文件保存路径: 组合，测试实例名称,测试时间
        daily_report_file = os.path.abspath(os.path.join(settings['report_folder'], u'{}_daily_{}.csv'.format(settings['name'], test_dt)))

        settings['report_file'] = daily_report_file

        l.append(pool.apply_async(single_strategy_test, (settings,)))

        # 回测报告集登记
        daily_results.append({'test_item': settings['paraName'], 'result_file': daily_report_file})

        # 执行内存回收
        gc.collect()
        sleep(10)

    result_list = [res.get() for res in l]

    # 返回结果是正确的，才添加到返回列表中
    for idx, rt in enumerate(result_list):
        if rt:
            return_results.append(daily_results[idx])

    pool.close()
    pool.join()

    return return_results

def run_multiparameter_test(gid, settings_list):
    """
    多策略组测试
    :param gid: 
    :param settings_list: 
    :return:     """
    if len(settings_list) == 0:
        raise ReferenceError('Zero settings')

    first_setting = settings_list[0]

    paraNames = '_'.join(i['paraName'] for i in settings_list)
    if 'report_folder' in first_setting:
        report_folder = first_setting['report_folder']
        final_file = os.path.abspath(os.path.join(first_setting['report_folder'],
                                                  '{}_{}_Report_{}.csv'.format(gid, first_setting['symbol'],
                                                                               paraNames)))
    else:
        # 报告所在目录
        report_folder = os.path.abspath(os.path.join(os.getcwd(), 'logs'))
        final_file = os.path.abspath(
            os.path.join(report_folder, '{}_{}_Report_{}.csv'.format(gid, first_setting['symbol'], paraNames)))

    if not os.path.exists(report_folder):
        os.makedirs(report_folder)

    for settings in settings_list:
        settings['report_folder'] = report_folder

    # 运行回测方法,统计结果
    daily_results = multi_parameter_test(gid, settings_list)

    # 统计结果
    #backtest_df = combine_results(daily_results)

    # 保存汇总记录到文件
    #backtest_df.to_csv(final_file)

    # 显示资金曲线汇总
   ##fig, ax = plt.subplots()

    #period_columns = [item['test_item'] for item in daily_results]

    #fig.patch.set_facecolor('white')

    #for column in period_columns:
    #    ax.plot(backtest_df[column], label=column)

    #ax.legend()

    #title = u'{} {}'.format(gid, paraNames)
    #plt.title(title)

    #fig.savefig(u'{}/rate.png'.format(report_folder))

    ## 释放内存
    gc.collect()

    print( 'finished run_multiparameter_test')

def single_func(para):
    logger=setup_logger('MyLog', name='my{}'.format(para))
    if para > 5:
        print( u'more than 5')
        logger.info('More than 5')
        return True
    else:
        print ('less')
        logger.info('Less than 5')
        return False

def multi_func():

    import logging
    # 启动多进程
    pool = multiprocessing.Pool(multiprocessing.cpu_count())

    logger = setup_logger('MyLog')

    logger.info('main process')
    l = []

    for i in range(0,10):
        l.append(pool.apply_async(single_func,(i,)))

    results = [res.get() for res in l]

    pool.close()
    pool.join()