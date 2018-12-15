# encoding: UTF-8

'''
动态载入所有的策略类
'''
from __future__ import print_function

import os
import importlib
import traceback


# 用来保存算法类和控件类的字典
ALGO_DICT = {}
WIDGET_DICT = {}


#----------------------------------------------------------------------
def loadAlgoModule(path, prefix):
    """使用importlib动态载入算法"""
    for root, subdirs, files in os.walk(path):
        for name in files:
            # 只有文件名以Algo.py结尾的才是算法文件
            if len(name)>7 and name[-7:] == 'Algo.py':
                try:
                    # 模块名称需要模块路径前缀
                    moduleName = prefix + name.replace('.py', '')
                    module = importlib.import_module(moduleName)
                    
                    # 获取算法类和控件类
                    algo = None
                    widget = None
                    
                    for k in dir(module):
                        # 以Algo结尾的类，是算法
                        if k[-4:] == 'Algo':
                            algo = module.__getattribute__(k)
                        
                        # 以Widget结尾的类，是控件
                        if k[-6:] == 'Widget':
                            widget = module.__getattribute__(k)
                    
                    # 保存到字典中
                    if algo and widget:
                        ALGO_DICT[algo.templateName] = algo
                        WIDGET_DICT[algo.templateName] = widget
                except:
                    print ('-' * 20)
                    print ('Failed to import strategy file %s:' %moduleName)
                    traceback.print_exc()                       


# 遍历algo目录下的文件
path1 = os.path.abspath(os.path.dirname(__file__))
loadAlgoModule(path1, 'vnpy.trader.app.algoTrading.algo.')

# 遍历工作目录下的文件
path2 = os.getcwd()
loadAlgoModule(path2, '')