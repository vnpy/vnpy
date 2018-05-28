# encoding: utf-8

# 该文件，为无界面启动文件，以vtServer为容器，加载MainEngine
# 配置：
#  self.gateway_name  ，gateway 的连接名称，在vtEngine.initGateway()里面定义，对应的配置文件是 "连接名称_connect.json"，
#  self.strategies：启动的策略实例，须在catStrategy/CtaSetting.json 里面定义  [u'S28_RB1001', u'S28_TFT', u'S28_HCRB',u'atr_rsi']
#  vtServer的ZMQ端口： 从VT_Setting.json中配置，根据AUTO_CONNCET_GW找到对应得端口配置

import os
import sys

import ctypes
from datetime import datetime, timedelta, date
from time import sleep
from threading import Thread

# 将repostory的目录i，作为根目录，添加到系统环境中。
ROOT_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
sys.path.append(ROOT_PATH)

from vnpy.trader.vtEvent import *
from vnpy.rpc import RpcServer
from vnpy.trader.vtEngine import MainEngine
from vnpy.trader.gateway import ctpGateway
from vnpy.trader.setup_logger import setup_logger,get_logger
from vnpy.trader.util_monitor import *
from vnpy.trader.vtGlobal import globalSetting
from vnpy.trader.util_gpid import *
from vnpy.trader.app import ctaStrategy,riskManager

AUTO_CONNCET_GW = 'CTP'
########################################################################
class VtServer(RpcServer):
    """vn.trader 无界面服务器"""

    # ----------------------------------------------------------------------
    def __init__(self, repAddress, pubAddress):
        """Constructor"""
        super(VtServer, self).__init__(repAddress, pubAddress)
        #self.usePickle()

        # gateway 是否连接
        self.connected = False
        # gateway 的连接名称，在vtEngine.initGateway()里面定义，对应的配置文件是 "连接名称_connect.json"，
        self.gateway_name = AUTO_CONNCET_GW
        # 启动的策略实例，须在catStrategy/CtaSetting.json 里面定义  [u'S28_RB1001', u'S28_TFT', u'S28_HCRB',u'atr_rsi']
        self.strategies = [u'S30_RB0510', u'S30_HCRB05']
        self.g_count = 0
        self.disconnect_signal = 0
        self.last_dt = datetime.now()

        # 创建事件引擎
        ee = EventEngine2()

        # 创建主引擎对象
        print( u'instance mainengine')
        self.engine = MainEngine(ee)

        # 添加CTP Gateway,配置文件为 CTP_Post
        self.engine.addGateway(ctpGateway, self.gateway_name)

        # 添加应用
        self.engine.addApp(ctaStrategy)
        self.engine.addApp(riskManager)


        # 注册主引擎的方法到服务器的RPC函数
        self.register(self.engine.connect)
        self.register(self.engine.disconnect)
        self.register(self.engine.subscribe)
        self.register(self.engine.sendOrder)
        self.register(self.engine.cancelOrder)
        self.register(self.engine.qryAccount)
        self.register(self.engine.qryPosition)
        self.register(self.engine.checkGatewayStatus)  # 检测gateway的连接状态
        self.register(self.engine.qryStatus)  # 检测ctaEngine的状态
        self.register(self.engine.exit)
        self.register(self.engine.writeLog)
        self.register(self.engine.dbConnect)
        self.register(self.engine.dbInsert)
        self.register(self.engine.dbQuery)
        self.register(self.engine.dbUpdate)
        self.register(self.engine.getContract)
        self.register(self.engine.getAllContracts)
        self.register(self.engine.getOrder)
        self.register(self.engine.getAllWorkingOrders)
        self.register(self.engine.getAllGatewayNames)
        self.register(self.engine.saveData)
        self.register(self.engine.initStrategy)
        self.register(self.engine.startStrategy)
        self.register(self.engine.stopStrategy)

        # 注册事件引擎发送的事件处理监听
        self.engine.eventEngine.registerGeneralHandler(self.eventHandler)


    def trade_off(self):
        """检查现在是否为非交易时间"""
        now = datetime.now()
        a = datetime.now().replace(hour=2, minute=35, second=0, microsecond=0)
        b = datetime.now().replace(hour=8, minute=55, second=0, microsecond=0)
        c = datetime.now().replace(hour=15, minute=30, second=0, microsecond=0)
        d = datetime.now().replace(hour=20, minute=55, second=0, microsecond=0)
        weekend = (now.isoweekday() == 6 and now >= a) or (now.isoweekday() == 7) or (now.isoweekday() == 1 and now <=b)
        off = (a <= now <= b) or (c <= now <= d) or weekend
        return off

    def disconnect(self):
        """"断开底层gateway的连接"""
        if self.engine:
            self.engine.disconnect(self.gateway_name)
            self.connected = False

    def onTimer(self, event):
        """定时器执行逻辑，每十秒执行一次"""

        # 十秒才执行一次检查
        self.g_count += 1
        if self.g_count <= 30:
            return
        self.g_count = 0
        dt = datetime.now()
        self.engine.qryStatus()
        if dt.hour != self.last_dt.hour:
            self.last_dt = dt
            print(u'noUiMain.py checkpoint:{0}'.format(dt))
            self.engine.writeLog( u'noUiMain.py checkpoint:{0}'.format(dt))

        # 定时断开
        if self.trade_off():
            """非交易时间"""
            if self.connected:
                self.engine.writeLog(u'断开连接{0}'.format(self.gateway_name))
                self.disconnect()
                self.engine.writeLog(u'清空数据引擎')
                self.engine.clearData()
                self.connected = False
                self.engine.writeNotification(u'非交易时间{0}，断开连接{1}'.format(dt, self.gateway_name))
            return

        # 交易时间内，定时重连和检查
        if not self.connected:
            self.engine.writeLog(u'启动连接{0}'.format(self.gateway_name))
            self.engine.writeLog(u'清空数据引擎')
            self.engine.clearData()
            self.engine.writeLog(u'重新连接{0}'.format(self.gateway_name))
            self.engine.connect(self.gateway_name)
            self.connected = True
            self.disconnect_signal = 0
            self.engine.writeNotification(u'{0}，重新连接{1}'.format(dt, self.gateway_name))
            return
        else:
            if not self.engine.checkGatewayStatus(self.gateway_name):
                self.disconnect_signal += 1

                if self.disconnect_signal >= 5:
                    self.engine.writeWarning(u'检查连接{0}异常，超过{1}次'.format(self.gateway_name,self.disconnect_signal))
                    sys.exit(0)
            else:
                self.disconnect_signal = 0

    def start(self):
        """启动"""
        super(VtServer, self).start()

        # 若需要连接数据库，则启动
        # self.mainEngine.dbConnect()

        # 加载cta的配置
        print( u'load cta setting')
        self.engine.ctaEngine.loadSetting()

        print(u'initialize all strategies')
        # 初始化策略，如果多个，则需要逐一初始化多个
        for s in self.strategies:
            print( 'init trategy {0}'.format(s))
            self.engine.ctaEngine.initStrategy(s)
            # 逐一启动策略
            print( 'start strategy {0}'.format(s))
            self.engine.ctaEngine.startStrategy(s)

        # 指定的连接配置
        if not self.trade_off():
            print( u'connect gateway:{0}'.format(self.gateway_name))
            self.engine.connect(self.gateway_name)
            self.connected = True

        # 注册定时器，用于判断重连
        self.engine.eventEngine.register(EVENT_TIMER, self.onTimer)

        # 所有的日志监控
        self.logM = LogMonitor(self.engine.eventEngine)
        self.errorM = ErrorMonitor(self.engine.eventEngine)
        self.tradeM = TradeMonitor(self.engine.eventEngine)
        self.orderM = OrderMonitor(self.engine.eventEngine, self.engine)
        self.positionM = PositionMonitor(self.engine.eventEngine)
        self.accountM = AccountMonitor(self.engine.eventEngine)

        self.engine.writeNotification(u'{0}，服务启动{1}'.format(datetime.now(),self. gateway_name))

    # ----------------------------------------------------------------------
    def eventHandler(self, event):
        """事件处理"""
        try:
            # 调用RpcServer.publish()
            if isinstance(event.type_, str):
                self.publish(event.type_, event)
            else:
                self.publish(event.type_.encode('utf-8'), event)

        except Exception as ex:
            print( u'event Handler exception:{0}'.format(str(ex)))

    # ----------------------------------------------------------------------
    def stopServer(self):
        """停止服务器"""
        print( 'stopServer')
        # 关闭引擎
        self.engine.exit()
        # 停止服务器线程
        self.stop()

# ----------------------------------------------------------------------
def printLog(content):
    """打印日志"""
    print( datetime.now().strftime("%H:%M:%S"), '\t', content)

# ----------------------------------------------------------------------
def runServer():
    """运行服务器"""

    try:
        log_file_name = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)),
                                                 'logs', u'noUiMain.log'))
    except Exception as ex:
        print( u'Use local dict:{0}'.format(os.getcwd()))
        log_file_name = os.path.abspath(os.path.join(os.getcwd(), 'logs', u'noUiMain.log'))

    setup_logger(filename=log_file_name, debug=False)

    # Req/Publish端口
    try:
        zmqAddressDict = globalSetting['ZMQ']
        zmqAddress = zmqAddressDict[AUTO_CONNCET_GW]
        reqAddress = zmqAddress['ReqAddress']
        pubAddress = zmqAddress['PubAddress']
    except:
        reqAddress = 'tcp://*:2014'
        pubAddress = 'tcp://*:2016'

    # 创建并启动服务器
    server = VtServer(reqAddress, pubAddress)
    server.start()

    printLog('-' * 50)
    printLog(u'Request端口:{0}'.format(reqAddress))
    printLog(u'Publish端口:{0}'.format(pubAddress))
    printLog(u'Trader服务器已启动')


if __name__ == '__main__':

    # 主程序
    thread = Thread(target=runServer, args=())
    thread.start()
