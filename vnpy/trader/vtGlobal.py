# encoding: UTF-8

"""
通过VT_setting.json加载全局配置
"""
print('load vtGlobal.py')
import os
import traceback
import json
from .vtFunction import getJsonPath
globalSetting = {}      # 全局配置字典

settingFileName = "VT_setting.json"
settingFilePath = getJsonPath(settingFileName, __file__)

try:
    with open(settingFilePath,'r',encoding="utf8") as f:
        globalSetting = json.load(f)
except:
    traceback.print_exc()