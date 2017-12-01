# encoding: UTF-8

"""
通过VT_setting.json加载全局配置
"""

import os
import traceback
import json
from .vtFunction import getJsonPath


settingFileName = "VT_setting.json"
settingFilePath = getJsonPath(settingFileName, __file__)

globalSetting = {}      # 全局配置字典

try:
    with open(settingFilePath, 'rb') as f:
        setting = f.read()
        if type(setting) is not str:
            setting = str(setting, encoding='utf8')
        globalSetting = json.loads(setting)
except:
    traceback.print_exc()
    
