# encoding: UTF-8

'''
动态载入所有的Gateway
'''

import os
import importlib
import traceback

# 用来保存Gateway类的字典
GATEWAY_DICT = {}

# 获取目录路径
path = os.path.abspath(os.path.dirname(__file__))

# 遍历strategy目录下的文件
for root, subdirs, files in os.walk(path):
    if path != root:
        continue
    
    for foldername in subdirs:
        # 接口目录名中必须含有Gateway
        if 'Gateway' in foldername:
            # 模块名称需要上前缀
            moduleName = 'gateway.' + foldername
            
            try:
                # 使用importlib动态载入模块，并保存到字典中
                module = importlib.import_module(moduleName)
                GATEWAY_DICT[module.gatewayName] = module
            except:
                traceback.print_exc()