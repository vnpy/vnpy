# encoding: UTF-8

"""
存放全局变量的文件
"""

# 数据库
MONGO_HOST = "localhost"
MONGO_PORT = 27017
MONGO_LOGGING = False

# 语言
LANGUAGE = "chinese"

# 界面
DARK_STYLE = True
FONT_FAMILY = u"微软雅黑"
FONT_SIZE = 12


import os

settingFileName = "VT_setting.json"
path = os.path.abspath(os.path.dirname(__file__)) 
settingFileName = os.path.join(path, settingFileName)  

try:
    f = file(settingFileName)
    setting = json.load(f)
    
    MONGO_HOST = setting["mongoHost"]
    MONGO_PORT = setting["mongoPort"]
    MONGO_LOGGING = setting["mongoLogging"]
    
    LANGUAGE = setting["language"]
    
    DARK_STYLE = setting["darkStyle"]
    FONT_FAMILY = setting["fontFamily"]
    FONT_SIZE = setting["fontSize"]
    
except:
    pass
