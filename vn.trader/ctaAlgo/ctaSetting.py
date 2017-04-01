# encoding: UTF-8

'''
在本文件中引入所有希望在系统中使用的策略类

这个字典中保存了需要运行的策略的名称和策略类的映射关系，
用户的策略类写好后，先在该文件中引入，并设置好名称，然后
在CTA_setting.json中写入具体每个策略对象的类和合约设置。
'''

#from ctaTemplate import DataRecorder
#from ctaDemo import DoubleEmaDemo
from strategy22_ArbitrageGrid import Strategy22
from strategy24_M15RB import Strategy24
from strategy25_NonStdArbitrageGrid import Strategy25
from strategy26_ArbitrageM1 import Strategy26
from strategy27_MultiPeriod import Strategy27

STRATEGY_CLASS = {}
#STRATEGY_CLASS['DataRecorder'] = DataRecorder
#STRATEGY_CLASS['DoubleEmaDemo'] = DoubleEmaDemo
STRATEGY_CLASS['Strategy22'] = Strategy22
STRATEGY_CLASS['Strategy24'] = Strategy24
STRATEGY_CLASS['Strategy25'] = Strategy25
STRATEGY_CLASS['Strategy26'] = Strategy26
STRATEGY_CLASS['Strategy27'] = Strategy27