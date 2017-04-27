# encoding: UTF-8

import os
import traceback

# 默认设置
from .Chinese import text

# 打开配置文件，读取语言配置
try:
    if os.environ.get("language") == 'english':
        from english import text
except:
    traceback.print_exc()
