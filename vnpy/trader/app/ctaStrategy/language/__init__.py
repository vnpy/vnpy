# encoding: UTF-8

import json
import os
import traceback

# 默认设置
from vnpy.trader.app.ctaStrategy.language.chinese import text

# 是否要使用英文
from vnpy.trader.vtGlobal import globalSetting
if len(globalSetting) > 0 and globalSetting['language'] == 'english':
    from vnpy.trader.app.ctaStrategy.language.english import text