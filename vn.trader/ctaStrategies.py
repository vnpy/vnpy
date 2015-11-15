# encoding: UTF-8

'''
在本文件中引入所有希望在系统中使用的策略类
当作配置文件，每次增加删除策略时，需要维护此字典
'''

from ctaStrategyTemplate import TestStrategy

strategyClassDict = {}
strategyClassDict[u'TestStrategy'] = TestStrategy
