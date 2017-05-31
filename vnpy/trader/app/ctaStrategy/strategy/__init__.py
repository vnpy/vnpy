# encoding: UTF-8

'''
动态载入所有的策略类
'''

import os
import importlib
import traceback

# 用来保存策略类的字典
STRATEGY_CLASS = {}

# 获取目录路径
path = os.path.abspath(os.path.dirname(__file__))

# 遍历strategy目录下的文件
for root, subdirs, files in os.walk(path):
    for name in files:
        # 只有文件名中包含strategy且非.pyc的文件，才是策略文件
        if 'strategy' in name and '.pyc' not in name:
            # 模块名称需要上前缀
            moduleName = 'vnpy.trader.app.ctaStrategy.strategy.' + name.replace('.py', '')
            
            # 使用importlib动态载入模块
            try:
                module = importlib.import_module(moduleName)
                
                # 遍历模块下的对象，只有名称中包含'Strategy'的才是策略类
                for k in dir(module):
                    if 'Strategy' in k:
                        v = module.__getattribute__(k)
                        STRATEGY_CLASS[k] = v
            except:
                print '-' * 20
                print ('Failed to import strategy file %s:' %moduleName)
                traceback.print_exc()
