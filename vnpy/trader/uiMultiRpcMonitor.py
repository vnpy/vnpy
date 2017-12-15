# encoding: UTF-8

'''
多RPC监控界面组件
Author: IncenseLee

设计思路：
1、单一RPC监控组件，包括：
    1）连接
    2）服务端状态监控（是否运行，gw名称，连接状态；操作：停止服务端，停止gw连接，启动gw连接）
    3）服务端策略状态监控（策略名称，ValueMonitor，信号。操作：启动策略，停止策略，初始化策略，强制初始化策略，特殊操作。。）
    4）服务器端Warning\Error\Nofification\Critical Log
2、多RPC监控容器，包括：
    1）从本地VT_Setting读取服务端连接信息。进行初始化和连接。
    2）订阅相应Event
    
'''


import os
import sys
from time import sleep
import json
import traceback
import platform

# 将repostory的目录i，作为根目录，添加到系统环境中。
ROOT_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
sys.path.append(ROOT_PATH)

from vnpy.trader.uiBasicWidget import QtWidgets, QtGui, QtCore
from vnpy.trader.vtEvent import *
from vnpy.trader.vtGlobal import globalSetting
from vnpy.trader.vtClient import *
from vnpy.trader.app.ctaStrategy.uiCtaWidget import  CtaValueMonitor

if str(platform.system()) == 'Windows':
    import winsound


########################################################################
class QGridSpinBox(QtWidgets.QSpinBox):
    """调整参数用的数值框"""

    # ----------------------------------------------------------------------
    def __init__(self, value):
        """Constructor"""
        super(QGridSpinBox, self).__init__()

        self.setMinimum(0)
        self.setMaximum(1000000)

        self.setValue(value)


########################################################################
class QGridLine(QtWidgets.QFrame):
    """水平分割线"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(QGridLine, self).__init__()
        self.setFrameShape(self.HLine)
        self.setFrameShadow(self.Sunken)


class StrategyMonitorWidget(QtWidgets.QGroupBox):
    """"RPC策略监控组件"""

    # ----------------------------------------------------------------------
    def __init__(self, name, mainEngine, parent=None):
        """Constructor"""
        super(StrategyMonitorWidget, self).__init__(parent)
        self.name = name
        self.mainEngine = mainEngine
        self.varTable = CtaValueMonitor(self)
        self.varTable.setMinimumHeight(80)

        self.initUi()

    def initUi(self):
        self.setTitle(self.name)
        # 策略的操作按钮：初始化/启动/停止/强制初始化
        btnInitStrategy = QtWidgets.QPushButton(u'Init')
        btnInitStrategy.clicked.connect(self.init_strategy)
        btnStartStrategy = QtWidgets.QPushButton(u'Start')
        btnStartStrategy.clicked.connect(self.start_strategy)
        btnStopStrategy = QtWidgets.QPushButton(u'Stop')
        btnStopStrategy.clicked.connect(self.stop_strategy)
        btnForceInitStrategy = QtWidgets.QPushButton(u'ForceInit')
        btnForceInitStrategy.clicked.connect(self.force_init_strategy)

        hbox1 = QtWidgets.QHBoxLayout()
        hbox1.addWidget(btnInitStrategy)
        hbox1.addWidget(btnStartStrategy)
        hbox1.addWidget(btnStopStrategy)
        hbox1.addWidget(btnForceInitStrategy)
        hbox1.addStretch()

        # 策略的运行数据表
        hbox2 = QtWidgets.QHBoxLayout()
        hbox2.addWidget(self.varTable)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox1)
        vbox.addLayout(hbox2)
        self.setLayout(vbox)

    def updateStatus(self,status_dict):
        #if 'name' not in status_dict:
        #    status_dict['name'] = self.name
        self.varTable.updateData(status_dict)

    def init_strategy(self):
        if self.mainEngine:
            self.mainEngine.initStrategy(self.name)

    def start_strategy(self):
        if self.mainEngine:
            self.mainEngine.startStrategy(self.name)

    def stop_strategy(self):
        if self.mainEngine:
            self.mainEngine.stopStrategy(self.name)

    def force_init_strategy(self):
        if self.mainEngine:
            self.mainEngine.initStrategy(self.name, force=True)

class CtaEngineMonitorWidget(QtWidgets.QWidget):
    """RPC 服务端CTA引擎监控组件
    {策略名称，ValueMonitor；操作：启动策略，停止策略，初始化策略，强制初始化策略，特殊操作。。）}
    """
    # ----------------------------------------------------------------------
    def __init__(self, parent=None):
        """Constructor"""
        super(CtaEngineMonitorWidget, self).__init__(parent)
        self.mainEngine = None
        self.strategy_monitors = {}

        self.scrollArea = QtWidgets.QScrollArea()
        self.scrollArea.setWidgetResizable(True)

        self.scrollLayout = QtWidgets.QVBoxLayout()

        self.initUi()
        self.initVarMonitors = False

    def setMainEngine(self,mainEngine):
        self.mainEngine = mainEngine

    def initUi(self):
        btnLoadStrategies = QtWidgets.QPushButton(u'Load All Strategies')
        btnStartStrategies = QtWidgets.QPushButton(u'Start All Strategies')
        btnStopStrategies = QtWidgets.QPushButton(u'Stop All Strategies')

        btnLoadStrategies.clicked.connect(self.load_all_strategies)
        btnStartStrategies.clicked.connect(self.start_all_strategies)
        btnStopStrategies.clicked.connect(self.stop_all_strategies)

        hbox1 = QtWidgets.QHBoxLayout()
        hbox1.addWidget(btnLoadStrategies)
        hbox1.addWidget(btnStartStrategies)
        hbox1.addWidget(btnStopStrategies)
        hbox1.addStretch()

        self.vbox = QtWidgets.QVBoxLayout()
        self.vbox.addLayout(hbox1)
        self.vbox.addWidget(self.scrollArea)

        self.setLayout(self.vbox)

    def load_all_strategies(self):
        if self.mainEngine:
           pass

    def start_all_strategies(self):
        pass

    def stop_all_strategies(self):
        pass

    def updateStatus(self, status_dict):
        """更新状态数据"""
        if not self.mainEngine:
            return

        if not self.initVarMonitors:
            w = QtWidgets.QWidget()
            vbox = QtWidgets.QVBoxLayout()
            for k, v in status_dict.items():
                monitor = StrategyMonitorWidget(name=k, mainEngine=self.mainEngine, parent=self)
                #height = 65
                #monitor.setFixedHeight(height)

                self.strategy_monitors[k] = monitor
                vbox.addWidget(monitor)

            w.setLayout(vbox)
            self.scrollArea.setWidget(w)
            self.initVarMonitors = True

        for k, v in status_dict.items():
            if k in self.strategy_monitors:
                monitor = self.strategy_monitors[k]
                monitor.updateStatus(v)

class ServerInfoWidget(QtWidgets.QWidget):
    """服务器信息显示组件
    1）显示服务器的CPU/磁盘/内存/网络等信息
    """

    def __init__(self, parent=None):
        """Constructor"""
        super(ServerInfoWidget, self).__init__(parent)

        self.label_cpu_percent = QtWidgets.QLabel()    # CPU占用率
        self.label_mem_percent = QtWidgets.QLabel()    # 内存占用率
        self.initUi()

    def initUi(self):
        Label = QtWidgets.QLabel
        grid = QtWidgets.QGridLayout()
        grid.addWidget(Label(u'CPU'), 0, 0)
        grid.addWidget(self.label_cpu_percent, 0, 1)
        grid.addWidget(Label(u'Memory'), 0, 2)
        grid.addWidget(self.label_mem_percent, 0, 3)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(grid)
        self.setLayout(vbox)

    def update_status(self,status_dict):
        if 'cpu' in status_dict:
            self.label_cpu_percent.setNum(status_dict['cpu'])

        if 'mem' in status_dict:
            self.label_mem_percent.setNum(status_dict['mem'])

class AccountMonitorWidget(QtWidgets.QWidget):
    """账号信息显示组件"""

    def __init__(self, parent=None):
        """Constructor"""
        super(AccountMonitorWidget, self).__init__(parent)

    def initUi(self):
        pass

########################################################################
class RpcServerMonitor(QtWidgets.QWidget):
    """RPC服务端监控容器组件
    1）连接服务端，gw名称，
    2）连接状态；操作：停止服务端，停止gw连接，启动gw连接）
    3）CtaEngineMonitorWidget
    4）RpcEventLogMonitor Warning\Error\Nofification\Critical Log
    """

    signal = QtCore.Signal(type(Event()))

    # ----------------------------------------------------------------------
    def __init__(self, name, req_addr, sub_addr, sub_topics, parent=None):
        """Constructor"""
        super(RpcServerMonitor, self).__init__(parent)
        self.name = name     # rpc Gateway Name
        self.reqAddress = req_addr          # Request/Response Port
        self.pubAddress = sub_addr          # Subscribe Port
        self.subscribeTopics = sub_topics   # subscribe Topics

        # 创建事件引擎
        self.eventEngine = EventEngine2()

        self.rpc_client = None
        self.mainEngine = None

        self.server_info_monitor= None

        self.initUi()
    # ----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""

        # 1) 服务端级别按钮，
        btnConnectRpcServer = QtWidgets.QPushButton(u'Connect {0}'.format(self.name))
        btnActivateGateWayConnection = QtWidgets.QPushButton(u'activate CTP')
        btnDeactivateGateway = QtWidgets.QPushButton(u'Deactivate CTP')
        btnQryStatus = QtWidgets.QPushButton(u'Qry Status')

        btnConnectRpcServer.clicked.connect(self.connect_rpc_server)
        btnActivateGateWayConnection.clicked.connect(self.activate_gateway_connection)
        btnDeactivateGateway.clicked.connect(self.deactivate_gateway_connection)
        btnQryStatus.clicked.connect(self.qryStatus)

        hbox1 = QtWidgets.QHBoxLayout()
        hbox1.addWidget(btnConnectRpcServer)
        hbox1.addWidget(btnActivateGateWayConnection)
        hbox1.addWidget(btnDeactivateGateway)
        hbox1.addWidget(btnQryStatus)

        self.chkCritical = QtWidgets.QCheckBox('Critical')
        self.chkCritical.setChecked(True)
        self.chkError = QtWidgets.QCheckBox('Error')
        self.chkError.setChecked(True)
        self.chkWarning = QtWidgets.QCheckBox('Warning')
        self.chkWarning.setChecked(True)
        self.chkCtaLog = QtWidgets.QCheckBox('CtaLog')
        self.chkCtaLog.setChecked(True)
        self.chkTicks = QtWidgets.QCheckBox('Ticks')
        self.chkTicks.setChecked(False)
        self.chkSignal = QtWidgets.QCheckBox('Signal')
        self.chkSignal.setChecked(True)

        hbox1.addWidget(self.chkCritical)
        hbox1.addWidget(self.chkError)
        hbox1.addWidget(self.chkWarning)
        hbox1.addWidget(self.chkCtaLog)
        hbox1.addWidget(self.chkTicks)
        hbox1.addWidget(self.chkSignal)

        hbox1.addStretch()

        self.server_info_monitor = ServerInfoWidget()

        # 滚动区域，放置所有的CtaStrategyManager
        self.scrollArea = QtWidgets.QScrollArea()
        self.scrollArea.setWidgetResizable(True)

        # 2)服务端策略监控widget
        self.ctaMonitor = CtaEngineMonitorWidget(self)  # 参数监控
        self.ctaMonitor.setMinimumHeight(200)
        #self.ctaMonitor.setMinimumWidth(800)

        hbox2 = QtWidgets.QVBoxLayout()
        hbox2.addWidget(self.ctaMonitor)
        self.scrollArea.setLayout(hbox2)

        # 服务端日志监控widget
        self.logMonitor = QtWidgets.QTextEdit()
        self.logMonitor.setReadOnly(True)
        self.logMonitor.setMaximumHeight(200)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox1)
        vbox.addWidget(self.server_info_monitor)            # 添加服务监控
        vbox.addWidget(self.logMonitor)
        vbox.addWidget(self.scrollArea)

        self.setLayout(vbox)

    def connect_rpc_server(self):
        """连接到远程服务端"""
        if self.rpc_client is not None:
            return

        try:
            self.eventEngine.start(timer=False)
            self.rpc_client = VtClient(self.reqAddress, self.pubAddress, self.eventEngine)
            # 这里是订阅所有的publish event，也可以指定。
            self.rpc_client.subscribeTopic(self.subscribeTopics)
            self.rpc_client.start()

            # 初始化主引擎和主窗口对象
            self.mainEngine = ClientEngine(self.rpc_client, self.eventEngine)

            self.ctaMonitor.setMainEngine(self.mainEngine)

            # 绑定本地GUI与EventEngine的事件
            self.registerEvent()
        except Exception as ex:
            traceback.print_exc()
            self.logMonitor.append(str(ex))

    def registerEvent(self):
        """注册事件"""
        self.signal.connect(self.processEvent)

        if self.eventEngine:

            self.eventEngine.register(EVENT_CTA_LOG, self.signal.emit)
            self.eventEngine.register(EVENT_STATUS,  self.signal.emit)

    def activate_gateway_connection(self):
        """激活服务端连接网关"""
        if self.mainEngine is None:
            return

        try:
            self.mainEngine.connect(self.name)
        except Exception as ex:
            self.logMonitor.append(str(ex))

    def deactivate_gateway_connection(self):
        """服务端网关断开"""
        if self.mainEngine is None:
            return
        try:
            self.mainEngine.disconnect(self.name)
        except:
            pass

    def qryStatus(self):
        if self.mainEngine is None:
            return
        try:
            self.mainEngine.qryStatus()
        except Exception as ex:
            pass

    def processEvent(self, event):
        """"处理事件（入口）"""
        if event.type_ == EVENT_CTA_LOG and self.chkCtaLog.isChecked():
            self.updateCtaLog(event)
            return

        if event.type_ == EVENT_STATUS:
            self.updateStatus(event)
            return

        if event.type_ == EVENT_WARNING and self.chkWarning.isChecked():
            self.updateWarning(event)
            return

        if event.type_ == EVENT_ERROR and self.chkError.isChecked():
            self.updateError(event)
            return

        if event.type_ == EVENT_CRITICAL and self.chkCritical.isChecked():
            self.updateCritical(event)
            return


    def updateStatus(self,event):
        """更新Status"""
        status_dict = event.dict_['data']

        if 'strategies' in status_dict:
            strategies_status_dict = status_dict['strategies']
            self.ctaMonitor.updateStatus(strategies_status_dict)

        if 'ticks' in status_dict and self.chkTicks.isChecked():
            ticks_dict = status_dict['ticks']
            str_dict = json.dumps(ticks_dict, indent=4)
            self.logMonitor.append(str_dict)

        if 'server' in status_dict:
            server_status_dict = status_dict['server']
            self.server_info_monitor.update_status(server_status_dict)

        if 'account' in status_dict:
            account_status = status_dict['account']

    # ----------------------------------------------------------------------
    def updateCtaLog(self, event):
        """更新CTA相关日志"""
        log = event.dict_['data']
        content = '\t'.join([log.logTime, log.logContent])
        self.logMonitor.append(content)

    # ----------------------------------------------------------------------
    def updateWarning(self, event):
        """更新相关Warning """
        log = event.dict_['data']
        content = '\t'.join([log.logTime, log.logContent])
        self.logMonitor.append(content)
        winsound.PlaySound('err.wav', winsound.SND_ASYNC)

    # ----------------------------------------------------------------------
    def updateError(self, event):
        """更新相关Error """
        log = event.dict_['data']
        content = '\t'.join([log.errorTime, log.errorID,log.errorMsg,log.additionalInfo])
        self.logMonitor.append(content)
        winsound.PlaySound('err.wav', winsound.SND_ASYNC)

    # ----------------------------------------------------------------------
    def updateCritical(self, event):
        """更新相关Critical"""
        log = event.dict_['data']
        content = '\t'.join([log.logTime, log.logContent])
        self.logMonitor.append(content)
        winsound.PlaySound('err.wav', winsound.SND_ASYNC)



########################################################################
class MultiRpcServerManager(QtWidgets.QMainWindow):
    """多RPC服务端监控界面
    包括：
    1）从本地VT_Setting读取服务端连接信息。进行初始化和连接。
    2）订阅相应Event
    """

    # ----------------------------------------------------------------------
    def __init__(self, parent=None):
        """Constructor"""
        super(MultiRpcServerManager, self).__init__(parent)
        self.rpc_servers_loaded = False

        self.initUi()

        self.load_rpc_servers()
    # ----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'远程监控')
        self.maximumSize()
        self.mdi = QtWidgets.QMdiArea()
        self.setCentralWidget(self.mdi)

        # 创建菜单
        menubar = self.menuBar()
        file_menu = menubar.addMenu("File")
        file_menu.addAction("Cascade")
        file_menu.addAction("Tiled")
        file_menu.triggered[QtWidgets.QAction].connect(self.windowaction)

    def windowaction(self,q):
        if q.text() == "cascade":
            self.mdi.cascadeSubWindows()

        if q.text() == "Cascade":
            self.mdi.tileSubWindows()
    # ----------------------------------------------------------------------
    def load_rpc_servers(self):
        """从vt_Setting.Json加载所有RPC服务器信息"""

        if self.rpc_servers_loaded:
            QtWidgets.QMessageBox.warning(self, u'Already Loaded')
            return

        try:
            zmqAddressDict = globalSetting['ZMQ']

            w = QtWidgets.QWidget()
            vbox = QtWidgets.QVBoxLayout()

            for k,v in zmqAddressDict.items():
                if k == 'CTP_Post':
                    continue
                reqAddress = v['ReqAddress']
                pubAddress = v['PubAddress']
                subscribes = v['SubscribeTopic']
                sub_window = QtWidgets.QMdiSubWindow()
                sub_window.setWindowTitle(k)
                rpc_monitor = RpcServerMonitor(name=k, req_addr=reqAddress, sub_addr=pubAddress, sub_topics=subscribes, parent=self)
                sub_window.setWidget(rpc_monitor)
                self.mdi.addSubWindow(rpc_monitor)
                rpc_monitor.show()

            self.mdi.tileSubWindows()

        except Exception as ex:
            traceback.print_exc()
            QtWidgets.QMessageBox.warning(self, 'Exception',u'Load vt_Setting.json Exception', QtWidgets.QMessageBox.Cancel,
                                          QtWidgets.QMessageBox.NoButton, QtGui.QMessageBox.NoButton)

            return


    def closeEvent(self, event):
        """关闭窗口时的事件"""
        sys.exit(0)


def main():

    from vnpy.trader.uiQt import createQApp

    qApp = createQApp()

    qApp.setWindowIcon(QtGui.QIcon(loadIconPath('dashboard.ico')))
    w = MultiRpcServerManager()
    w.showMaximized()
    sys.exit(qApp.exec_())


if __name__ == '__main__':
    main()


