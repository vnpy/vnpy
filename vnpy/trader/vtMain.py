# encoding: UTF-8

# 重载sys模块，设置默认字符串编码方式为utf8
import sys
reload(sys)
sys.setdefaultencoding('utf8')

# Python内置模块
import os
import platform

# Python三方模块
from qtpy import QtWidgets, QtGui

# vn.trader模块
from vnpy.event import EventEngine2
from vnpy.trader.vtGlobal import globalSetting
from vnpy.trader.vtEngine import MainEngine
from vnpy.trader.uiMainWindow import MainWindow, BASIC_FONT
from vnpy.trader.vtFunction import loadIconPath

# 加载底层接口
from vnpy.trader.gateway import (ctpGateway,
                                 ibGateway,
                                 huobiGateway)

# 加载上层应用
from vnpy.trader.app import (riskManager, dataRecorder,
                             ctaStrategy)


#----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 创建事件引擎
    ee = EventEngine2()
    
    # 创建主引擎
    me = MainEngine(ee)
    
    # 添加交易接口
    me.addGateway(ctpGateway)
    me.addGateway(ibGateway)
    me.addGateway(huobiGateway)
    
    # 添加上层应用
    me.addApp(riskManager)
    me.addApp(dataRecorder)
    me.addApp(ctaStrategy)
    
    # 初始化Qt应用对象
    app = QtWidgets.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon(loadIconPath()))
    app.setFont(BASIC_FONT)
    
    # 初始化主引擎和主窗口对象
    mw = MainWindow(me, ee)
    mw.showMaximized()
    
    # 在主线程中启动Qt事件循环
    sys.exit(app.exec_())


    
if __name__ == '__main__':
    main()
