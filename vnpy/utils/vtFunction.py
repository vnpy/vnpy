# -*- coding: utf-8 -*-

"""
包含一些开放中常用的函数
"""

import os
import decimal
import json
from datetime import datetime

MAX_NUMBER = 10000000000000
MAX_DECIMAL = 4


# ----------------------------------------------------------------------
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


# ----------------------------------------------------------------------
def loadMongoSetting():
    """载入MongoDB数据库的配置"""
    try:
        f = file("VT_setting.json")
        setting = json.load(f)
        host = setting['mongoHost']
        port = setting['mongoPort']
    except:
        host = 'localhost'
        port = 27017

    return host, port


# ----------------------------------------------------------------------
def todayDate():
    """获取当前本机电脑时间的日期"""
    return datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)


def findTempPath(filename):
    return _find_spec_path(filename, "temp") + '\\'


def findConfPath(filename):
    return _find_spec_path(filename, "conf")


def findResPath(filename):
    return _find_spec_path(filename, "res")


def findDataPath(filename):
    return _find_spec_path(filename, "data")


def findRootPath():
    return _find_spec_path("", "vnpy")


def _find_spec_path(filename, sub_dir):
    import vnpy
    dir_name = os.path.abspath(
        os.path.join(os.path.dirname(vnpy.__file__), os.path.pardir, sub_dir)
    )

    if not os.path.exists(dir_name):
        os.makedirs(dir_name)

    return os.path.abspath(
        os.path.join(dir_name, filename)
    )


if __name__ == '__main__':
    print findTempPath("CTP")
