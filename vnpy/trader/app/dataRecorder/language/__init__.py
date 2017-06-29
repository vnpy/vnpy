# encoding: UTF-8

import json
import os
import traceback

# 默认设置
from chinese import text

# 是否要使用英文
from vnpy.trader.vtGlobal import globalSetting
if globalSetting['language'] == 'english':
    from english import text