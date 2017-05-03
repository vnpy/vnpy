# encoding: UTF-8

import sys
import os
import ctypes
from datetime import datetime, timedelta, date
from time import sleep

from ctaStrategy.strategy import STRATEGY_CLASS
from eventType import *
from vtEngine import MainEngine
from threading import Thread

from simple_monitor import *
from setup_logger import setup_logger

setup_logger(debug=True)
# ----------------------------------------------------------------------
class NoUiMain(object):

    def __init__(self):
        # gateway 是否连接
        self.connected = False
        # gateway 的连接名称，在vtEngine.initGateway()里面定义
        self.gateway_name = 'CTP'
        # 启动的策略实例，须在catAlgo/CtaSetting.json 里面定义  [u'S28_RB1001', u'S28_TFT', u'S28_HCRB',u'atr_rsi']
        self.strategies = [u'atr_rsi']

        self.g_count = 0

        # 实例化主引擎
        self.mainEngine = MainEngine()

    def trade_off(self):
        """检查现在是否为非交易时间"""
        now = datetime.now()
        a = datetime.now().replace(hour=2, minute=35, second=0, microsecond=0)
        b = datetime.now().replace(hour=8, minute=30, second=0, microsecond=0)
        c = datetime.now().replace(hour=15, minute=30, second=0, microsecond=0)
        d = datetime.now().replace(hour=20, minute=30, second=0, microsecond=0)
        weekend = (now.isoweekday() == 6 and now >= a) or (now.isoweekday() == 7)
        off = (a <= now <= b) or (c <= now <= d) or weekend
        return off

    def disconnect(self):
        """"断开底层gateway的连接"""
        if self.mainEngine:
            self.mainEngine.disconnect(self.gateway_name)
            self.connected = False

    def onTimer(self, event):
        """定时器执行逻辑，每十秒执行一次"""

        # 十秒才执行一次检查
        self.g_count += 1
        if self.g_count <= 10:
            return
        self.g_count = 0
        print u'noUiMain.py checkpoint:{0}'.format(datetime.now())

        # 定时断开
        if self.trade_off():
            if self.connected:
                self.disconnect()
                self.mainEngine.writeLog(u'断开连接{0}'.format(self.gateway_name))
                self.mainEngine.writeLog(u'清空数据引擎')
                self.mainEngine.clearData()
                self.connected = False
            return

        # 定时重连
        if not self.connected:
            self.mainEngine.writeLog(u'清空数据引擎')
            self.mainEngine.clearData()
            self.mainEngine.writeLog(u'重新连接{0}'.format(self.gateway_name))
            self.mainEngine.connect(self.gateway_name)
            self.connected = True

    def Start(self):
        """启动"""

        # 若需要连接数据库，则启动
        #self.mainEngine.dbConnect()

        # 加载cta的配置
        self.mainEngine.ctaEngine.loadSetting()

        # 初始化策略，如果多个，则需要逐一初始化多个
        for s in self.strategies:
            self.mainEngine.ctaEngine.initStrategy(s)
            # 逐一启动策略
            self.mainEngine.ctaEngine.startStrategy(s)

        # 指定的连接配置
        self.mainEngine.connect(self.gateway_name)
        self.connected = True

        # 注册定时器，用于判断重连
        self.mainEngine.eventEngine.register(EVENT_TIMER, self.onTimer)

        # 所有的日志监控
        self.logM = LogMonitor(self.mainEngine.eventEngine)
        self.errorM = ErrorMonitor(self.mainEngine.eventEngine)
        self.tradeM = TradeMonitor(self.mainEngine.eventEngine)
        self.orderM = OrderMonitor(self.mainEngine.eventEngine, self.mainEngine)
        self.positionM = PositionMonitor(self.mainEngine.eventEngine)
        self.accountM = AccountMonitor(self.mainEngine.eventEngine)

def run_noui():

    log_file_name = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                                 'logs',
                                                 u'noUiMain_{0}.log'.format(datetime.now().strftime('%m%d_%H%M'))))

    setup_logger(filename=log_file_name, debug=False)
    noUi = NoUiMain()
    noUi.Start()


if __name__ == '__main__':
    #from PyQt4 import QtGui
    # 主程序
    thread = Thread(target=run_noui, args=())
    thread.start()

    # 创建Qt应用对象，用于事件循环
    #app = QtGui.QApplication(sys.argv)
    #run_noui()
    # 连续运行，用于输出行情
    #app.exec_()

