# encoding: UTF-8

import os

# 默认设置
from .chinese import text, constant

# 打开配置文件，读取语言配置
try:
    if os.environ.get("language") == 'english':
        from english import text, constant
except:
    pass
