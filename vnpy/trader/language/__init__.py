# encoding: UTF-8

# 默认设置
from .chinese import text, constant

# 是否要使用英文
from vnpy.trader.vtGlobal import globalSetting
if globalSetting.get('language',None) == 'english':
    from vnpy.trader.language.english import text, constant