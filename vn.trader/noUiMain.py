# encoding: UTF-8
import time
import sys
import os
import ctypes
try:
    import bsddb
except:
    import bsddb3 as bsddb
    sys.modules['bsddb'] = bsddb
import json
from ctaAlgo.ctaSetting import STRATEGY_CLASS

from vtEngine import MainEngine
from PyQt4.QtCore import QCoreApplication
from simple_monitor import *
from setup_logger import setup_logger

setup_logger(debug=True)
# ----------------------------------------------------------------------
def main():    
    app = QCoreApplication(sys.argv)
    mainEngine = MainEngine()
    # 若需要连接数据库，则启动
    mainEngine.dbConnect()
    # 指定的连接配置
    mainEngine.connect('CTP_Prod')
    # 加载cta的配置
    mainEngine.ctaEngine.loadSetting()
    # 初始化策略，如果多个，则需要逐一初始化多个
    mainEngine.ctaEngine.initStrategy(u'S26_PTA套利')
    # 逐一启动策略
    mainEngine.ctaEngine.startStrategy(u'S26_PTA套利')

    logM = LogMonitor(mainEngine.eventEngine)
    errorM = ErrorMonitor(mainEngine.eventEngine)
    tradeM = TradeMonitor(mainEngine.eventEngine)
    orderM = OrderMonitor(mainEngine.eventEngine, mainEngine)
    positionM = PositionMonitor(mainEngine.eventEngine)
    accountM = AccountMonitor(mainEngine.eventEngine)
    

    app.exec_()
    

if __name__ == '__main__':
    main()
