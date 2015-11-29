# encoding: UTF-8

import sys
import ctypes
import platform

from vtEngine import MainEngine
from uiMainWindow import *

#----------------------------------------------------------------------
def main():
    """主程序入口"""
    if platform.system() =="Windows" and platform.version() > '6':
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('vn.py demo')
    
    app = QtGui.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon('vnpy.ico'))
    app.setFont(BASIC_FONT)
    
    mainEngine = MainEngine()
    mainWindow = MainWindow(mainEngine, mainEngine.eventEngine, mainEngine.dataEngine)
    mainWindow.showMaximized()
    
    sys.exit(app.exec_())
    
if __name__ == '__main__':
    main()
