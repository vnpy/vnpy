# encoding: UTF-8

'''
本文件中包含的数据格式和CTA模块通用，用户有必要可以自行添加格式。
'''

from __future__ import division

# 数据库名称
SETTING_DB_NAME = 'VnTrader_Setting_Db'
TICK_DB_NAME = 'VnTrader_Tick_Db'
DAILY_DB_NAME = 'VnTrader_Daily_Db'
MINUTE_DB_NAME = 'VnTrader_1Min_Db'


# CTA引擎中涉及的数据类定义
from vnpy.trader.vtConstant import EMPTY_UNICODE, EMPTY_STRING, EMPTY_FLOAT, EMPTY_INT
