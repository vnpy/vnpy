# encoding: UTF-8

import json
import os

# 默认设置
from chinese import constantChinese as constant
from chinese import languageChinese as language

# 获取目录上级路径
SETTING_FILENAME = 'VT_setting.json'
path = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
SETTING_FILENAME = os.path.join(path, SETTING_FILENAME)

# 打开配置文件，读取语言配置
try:
    f = file(SETTING_FILENAME)
    setting = json.load(f)
    if setting['language'] == 'English' or setting['language'] == 'english':
        from english import constantEnglish as constant
        from english import languageEnglish as language
    f.close()
except:
    pass



