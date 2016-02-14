# encoding: UTF-8

import sys
import ctypes
#import bsddb3 as bsddb
#sys.modules['bsddb'] = bsddb

from vtEngine import MainEngine
from uiMainWindow import *

from simple_monitor import *

from setup_logger import setup_logger

setup_logger(filename='vnpy.log',debug=True)

# ----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 设置底部任务栏图标，win7以下请注释掉
    ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('vn.py demo')
    
    app = QtGui.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon('vnpy.ico'))
    app.setFont(BASIC_FONT)
    
    mainEngine = MainEngine()
    mainWindow = MainWindow(mainEngine, mainEngine.eventEngine, mainEngine.dataEngine)
    mainWindow.showMaximized()

    logM = LogMonitor(mainEngine.eventEngine)
    ctaLogM = CtaLogMonitor(mainEngine.eventEngine)
    errorM = ErrorMonitor(mainEngine.eventEngine)
    tradeM = TradeMonitor(mainEngine.eventEngine)
    orderM = OrderMonitor(mainEngine.eventEngine, mainEngine)
    positionM = PositionMonitor(mainEngine.eventEngine)
    accountM = AccountMonitor(mainEngine.eventEngine)

    sys.exit(app.exec_())
    
if __name__ == '__main__':
    main()
