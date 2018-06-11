# encoding: UTF-8

"""
通过VT_setting.json加载全局配置
"""

import os
import traceback
import json
from .vtFunction import loadJsonSetting

settingFileName = "VT_setting.json"
globalSetting = loadJsonSetting(settingFileName)