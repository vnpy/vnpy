# encoding: UTF-8

import sys
import os
import ctypes
import platform

import vtPath
from vtEngine import MainEngine
from uiMainWindow import *

# 文件路径名
path = os.path.abspath(os.path.dirname(__file__))
ICON_FILENAME = 'vnpy.ico'
ICON_FILENAME = os.path.join(path, ICON_FILENAME)

SETTING_FILENAME = 'VT_setting.json'
SETTING_FILENAME = os.path.join(path, SETTING_FILENAME)


# ----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 重载sys模块，设置默认字符串编码方式为utf8
    reload(sys)
    sys.setdefaultencoding('utf8')

        # 初始化Qt应用对象
    app = QtGui.QApplication(sys.argv)

    # 初始化主引擎和主窗口对象
    mainEngine = MainEngine()
    # 连接CTP接口
    mainEngine.connect('CTP')
    # 加载所有策略
    mainEngine.ctaEngine.loadSetting()
    mainEngine.ctaEngine.writeCtaLog(u'Strategy loaded.')
    # 初始化所有策略
    for name in mainEngine.ctaEngine.strategyDict.keys():
        mainEngine.ctaEngine.initStrategy(name)
    # 启动所有策略
    for name in mainEngine.ctaEngine.strategyDict.keys():
        mainEngine.ctaEngine.startStrategy(name)
    # 停止所有策略
    for name in mainEngine.ctaEngine.strategyDict.keys():
        mainEngine.ctaEngine.stopStrategy(name)

    # 在主线程中启动Qt事件循环
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
