# encoding: UTF-8

from __future__ import absolute_import
import json
import os
import traceback

# 默认设置
from .chinese import text

# 获取全局配置
from vnpy.trader.vtGlobal import globalSetting

# 打开配置文件，读取语言配置
if globalSetting['language'] == 'english':
    from .english import text
