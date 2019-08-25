# encoding: UTF-8

print('load vtConstant.py')

# 默认空值
EMPTY_STRING = ''
EMPTY_UNICODE = u''
EMPTY_INT = 0
EMPTY_FLOAT = 0.0

# k线颜色
COLOR_RED = u'Red'      # 上升K线
COLOR_BLUE = u'Blue'    # 下降K线
COLOR_EQUAL = u'Equal'  # 平K线

# 策略若干判断状态
NOTRUN = u'NotRun'   # 没有运行；
RUNING = u'Runing'   # 正常运行；
FORCECLOSING = u'ForceClosing'  #正在关闭
FORCECLOSED = u'ForceClosed'    #:已经关闭

# Mongo数据库相关
SERVICE_DB_NAME = 'Service'         # 运行服务信息记录库
ALGO_INFO_COL = 'algo_info'         # 算法引擎实例

ALGOTRADING_DB_NAME = 'AlgoTrading'             # AlgoTrading数据库名
ALGO_SETTING_COL_NAME = 'algo_setting'        # 算法配置集合名
ALGO_HISTORY_COL_NAME = 'algo_history'        # 算法历史集合名
ALGO_RUNNING_COL_NAME = 'algo_running'        # 正在运行的算法实例

STRATEGY_DB_NAME = 'Strategy'            # 策略（交易方案/交易计划）
TRADING_PROPOSAL_COL_NAME = 'trading_proposal'   # 交易方案
TRADING_PLAN_COL_NAME = 'trading_plan'   # 交易计划

ACCOUNT_DB_NAME = 'Account'              # 账号的数据库
ACCOUNT_INFO_COL_NAME = 'account_info'   # 账号信息表

CONTRACT_DB_NAME = 'Contract'            # 合约信息的数据库
ALL_SYMBOL_COL_NAME = 'all_symbols'      # 所有合约信息
MI_SYMBOL_COL_NAME = 'mi_symbols'        # 主力合约信息
INDEX_SYMBOL_COL_NAME = 'index_symbols'  # 指数合约信息

from vnpy.trader.language import constant

# 将常量定义添加到vtConstant.py的局部字典中
d = locals()
for name in dir(constant):
    if '__' not in name:
        d[name] = constant.__getattribute__(name)
