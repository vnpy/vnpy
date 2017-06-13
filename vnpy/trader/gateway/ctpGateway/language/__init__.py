# encoding: UTF-8

import json
import os
import traceback

#print u'init {0}'.format(os.path.dirname(__file__))

# 默认设置
from chinese import text

# 是否要使用英文
from vnpy.trader.vtGlobal import globalSetting
if globalSetting['language'] == 'english':
    from english import text