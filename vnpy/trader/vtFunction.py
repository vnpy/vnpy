# encoding: UTF-8

"""
包含一些开发中常用的函数
"""

import os
import decimal
import json
from datetime import datetime

MAX_NUMBER = 10000000000000
MAX_DECIMAL = 4

#----------------------------------------------------------------------
def safeUnicode(value):
    """检查接口数据潜在的错误，保证转化为的字符串正确"""
    # 检查是数字接近0时会出现的浮点数上限
    if type(value) is int or type(value) is float:
        if value > MAX_NUMBER:
            value = 0
    
    # 检查防止小数点位过多
    if type(value) is float:
        d = decimal.Decimal(str(value))
        if abs(d.as_tuple().exponent) > MAX_DECIMAL:
            value = round(value, ndigits=MAX_DECIMAL)
    
    return unicode(value)

#----------------------------------------------------------------------
def todayDate():
    """获取当前本机电脑时间的日期"""
    return datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)    

#----------------------------------------------------------------------
def loadIconPath():
    """加载程序图标路径"""
    iconName = 'vnpy.ico'
    
    # 首先尝试从当前目录加载图标
    path = os.getcwd()
    iconPath = os.path.join(path, iconName)
    if os.path.isfile(iconPath):
        return iconPath
    
    # 如果失败则从vt根目录加载图标
    else:
        path = os.path.abspath(os.path.dirname(__file__))    
        iconPath = os.path.join(path, iconName)
        return iconPath
    
    
    
    
