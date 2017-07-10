# encoding: UTF-8

"""
通过VT_setting.json加载全局配置
"""

import os
import traceback
import json
from vtFunction import getJsonPath

globalSetting = {}      # 全局配置字典


settingFileName = "VT_setting.json"
settingFilePath = getJsonPath(settingFileName, __file__)

try:
    f = file(settingFileName)
    globalSetting = json.load(f)
except:
    traceback.print_exc()
    
