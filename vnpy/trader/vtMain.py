# encoding: UTF-8

import sys
import os
import platform

import vtGlobal
from vtEngine import MainEngine
from uiMainWindow import *

# 文件路径名
path = os.path.abspath(os.path.dirname(__file__))    
ICON_FILENAME = 'vnpy.ico'
ICON_FILENAME = os.path.join(path, ICON_FILENAME)  


#----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 重载sys模块，设置默认字符串编码方式为utf8
    reload(sys)
    sys.setdefaultencoding('utf8')
    
    # 设置Windows底部任务栏图标
    if 'Windows' in platform.uname():
        import ctypes
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('vn.trader')  
    
    # 初始化Qt应用对象
    app = QtGui.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon(ICON_FILENAME))
    app.setFont(BASIC_FONT)
    
    # 设置Qt的皮肤
    if vtGlobal.DARK_STYLE:
        import qdarkstyle
        app.setStyleSheet(qdarkstyle.load_stylesheet(pyside=False))
    
    # 初始化主引擎和主窗口对象
    mainEngine = MainEngine()
    mainWindow = MainWindow(mainEngine, mainEngine.eventEngine)
    mainWindow.showMaximized()
    
    # 在主线程中启动Qt事件循环
    sys.exit(app.exec_())
    
if __name__ == '__main__':
    main()
