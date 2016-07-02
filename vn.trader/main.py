# encoding: UTF-8
import time
import sys
import ctypes
try:
    import bsddb
except:
    import bsddb3 as bsddb
    sys.modules['bsddb'] = bsddb
import json
from ctaStrategies import strategyClassDict


from vtEngine import MainEngine
from PyQt4.QtCore import QCoreApplication
from simple_monitor import *
from setup_logger import setup_logger

setup_logger(debug=True)
# ----------------------------------------------------------------------
def main():    
    app = QCoreApplication(sys.argv)
    mainEngine = MainEngine()
    mainEngine.dbConnect()
    mainEngine.connect('CTP_Prod')


    def loadStrategySetting(setting_file_name):
        """读取引擎中的策略配置"""
        with open(setting_file_name) as f:
            # 读取文件内容串=》Json对象
            d = json.load(f)

            # 策略实例名称，配置内容
            for name, setting in d.items():

                # 策略的类名称
                strategyClassName = setting['strategyClassName']

                if strategyClassName in strategyClassDict:
                    # 透过策略类字典，反射获取策略
                    strategyClass = strategyClassDict[strategyClassName]

                    # 初始化策略的设置
                    mainEngine.ctaEngine.initStrategy(name, strategyClass, setting)
                else:
                    mainEngine.writeLog(u'无法找到策略类：' + strategyClassName)
                    break

    loadStrategySetting('CTA_setting.json')
    mainEngine.ctaEngine.startStrategy('Test1')
    logM = LogMonitor(mainEngine.eventEngine)
    errorM = ErrorMonitor(mainEngine.eventEngine)
    tradeM = TradeMonitor(mainEngine.eventEngine)
    orderM = OrderMonitor(mainEngine.eventEngine, mainEngine)
    positionM = PositionMonitor(mainEngine.eventEngine)
    accountM = AccountMonitor(mainEngine.eventEngine)
    

    app.exec_()
    

if __name__ == '__main__':
    main()
