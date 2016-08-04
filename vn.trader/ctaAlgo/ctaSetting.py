# encoding: UTF-8

'''
在本文件中引入所有希望在系统中使用的策略类

这个字典中保存了需要运行的策略的名称和策略类的映射关系，
用户的策略类写好后，先在该文件中引入，并设置好名称，然后
在CTA_setting.json中写入具体每个策略对象的类和合约设置。
'''

from ctaDemo import DoubleEmaDemo

STRATEGY_CLASS = {}
STRATEGY_CLASS['DoubleEmaDemo'] = DoubleEmaDemo