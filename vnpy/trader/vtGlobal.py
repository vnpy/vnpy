# encoding: UTF-8

"""
通过VT_setting.json加载全局配置
"""
print('load vtGlobal.py')
import os
import traceback
import json

globalSetting = {}      # 全局配置字典

settingFileName = "VT_setting.json"
path = os.path.abspath(os.path.dirname(__file__))
settingFileName = os.path.join(path, settingFileName)

try:
    with open(settingFileName,'r',encoding="utf8") as f:
        globalSetting = json.load(f)
except:
    traceback.print_exc()