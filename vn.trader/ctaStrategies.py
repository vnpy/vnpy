# encoding: UTF-8

'''
在本文件中引入所有希望在系统中使用的策略类


这个字典中保存了需要运行的策略的名称和策略类的映射关系，
用户的策略类写好后，先在该文件中引入，并设置好名称，然后
在CTA_setting.json中写入具体每个策略对象的类和合约设置。

'''

from ctaStrategyTemplate import TestStrategy
from ctaDataRecorder import DataRecorder
from ctaStrategy02 import Strategy02
from ctaStrategy03 import Strategy03
from ctaStrategy04 import Strategy04
from ctaStrategy05 import Strategy05
from ctaStrategy06 import Strategy06

strategyClassDict = {}

#strategyClassDict['TestStrategy'] = TestStrategy
#strategyClassDict['DataRecorder'] = DataRecorder
strategyClassDict['Strategy02'] = Strategy02
strategyClassDict['Strategy03'] = Strategy03
strategyClassDict['Strategy04'] = Strategy04
strategyClassDict['Strategy05'] = Strategy05
strategyClassDict['Strategy06'] = Strategy06
