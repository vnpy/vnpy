# encoding: UTF-8

'''
动态载入所有的策略类，先从vnpy/trader/app/ctaStrategy/strategy下加载，其次，从工作目录下strategy加载。
如果重复，工作目录的strategy优先。
'''

import os
import importlib

import traceback

# 用来保存策略类的字典
STRATEGY_CLASS = {}

# ----------------------------------------------------------------------
def loadStrategyModule(moduleName):
    """使用importlib动态载入模块"""
    try:
        print('loading {0}'.format(moduleName))
        module = importlib.import_module(moduleName)

        # 遍历模块下的对象，只有名称中包含'Strategy'的才是策略类
        for k in dir(module):
            if 'Strategy' in k:
                print('adding {} into STRATEGY_CLASS'.format(k))
                v = module.__getattribute__(k)
                if k in STRATEGY_CLASS:
                    print('Replace strategy {} with {}'.format(k,moduleName))
                STRATEGY_CLASS[k] = v
    except Exception as ex:
        print('-' * 20)
        print('Failed to import strategy file %s:' % moduleName)
        print('Exception:{},{}'.format(str(ex),traceback.format_exc()))

    # 获取目录路径
path = os.path.abspath(os.path.dirname(__file__))

print('init strategies from {}'.format(path))

# 遍历strategy目录下的文件
for root, subdirs, files in os.walk(path):
    for name in files:
        # 只有文件名中包含strategy且非.pyc的文件，才是策略文件
        if 'strategy' in name and '.pyc' not in name:
            # 模块名称需要上前缀
            moduleName = 'vnpy.trader.app.ctaStrategy.strategy.' + name.replace('.py', '')
            loadStrategyModule(moduleName)


# 遍历工作目录下的文件
#stratey_working_path = os.path.abspath(os.path.join(os.getcwd(), 'strategy'))
#
#if os.path.exists(stratey_working_path):
#    print('init strategies from {}'.format(stratey_working_path))
#    for root, subdirs, files in os.walk(stratey_working_path):
#        for name in files:
#            # 只有文件名中包含strategy且非.pyc的文件，才是策略文件
#            if 'strategy' in name and '.pyc' not in name:
#                # 模块名称无需前缀
#                moduleName = name.replace('.py', '')
#                loadStrategyModule(moduleName)
#
print('finished load strategy modules')
