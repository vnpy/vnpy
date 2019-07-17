# encoding: UTF-8
import sys

# from uiFullMonitorWidget import MonitorWidget
# from uiKChartWidget import CandleForm
print('load uiMainWindows.py')
import psutil
import traceback

from vnpy.trader.vtFunction import loadIconPath
from vnpy.trader.vtGlobal import globalSetting
from vnpy.trader.uiBasicWidget import *

########################################################################
class MainWindow(QtWidgets.QMainWindow):
    """主窗口"""

    signalStatusBar = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        super(MainWindow, self).__init__()

        self.mainEngine = mainEngine
        self.eventEngine = eventEngine

        l = self.mainEngine.getAllGatewayDetails()
        self.gatewayNameList = [d['gatewayName'] for d in l]

        self.widgetDict = {}    # 用来保存子窗口的字典

        self.connectGatewayDict = {}

        # 获取主引擎中的上层应用信息
        self.appDetailList = self.mainEngine.getAllAppDetails()

        self.initUi()
        self.loadWindowSettings('custom')

        self.connected = False
        self.autoDisConnect = False

        self.orderSaveDate = EMPTY_STRING
        self.barSaveDate = EMPTY_STRING

    # ----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        path = os.getcwd().rsplit('\\')[-1]

        self.setWindowTitle(path)
        self.initCentral()
        self.initMenu()
        self.initStatusBar()

    # ----------------------------------------------------------------------
    def initCentral(self):
        """初始化中心区域"""
        widgetMarketM, dockMarketM = self.createDock(MarketMonitor, vtText.MARKET_DATA, QtCore.Qt.RightDockWidgetArea)
        widgetLogM, dockLogM = self.createDock(LogMonitor, vtText.LOG, QtCore.Qt.BottomDockWidgetArea)
        widgetErrorM, dockErrorM = self.createDock(ErrorMonitor, vtText.ERROR, QtCore.Qt.BottomDockWidgetArea)
        self.widgetTradeM, dockTradeM = self.createDock(TradeMonitor, vtText.TRADE, QtCore.Qt.BottomDockWidgetArea)
        self.widgetOrderM, dockOrderM = self.createDock(OrderMonitor, vtText.ORDER, QtCore.Qt.RightDockWidgetArea)
        widgetWorkingOrderM, dockWorkingOrderM = self.createDock(WorkingOrderMonitor, vtText.WORKING_ORDER,
                                                                 QtCore.Qt.BottomDockWidgetArea)
        widgetPositionM, dockPositionM = self.createDock(PositionMonitor, vtText.POSITION,
                                                         QtCore.Qt.BottomDockWidgetArea)
        widgetAccountM, dockAccountM = self.createDock(AccountMonitor, vtText.ACCOUNT, QtCore.Qt.BottomDockWidgetArea)
        widgetTradingW, dockTradingW = self.createDock(TradingWidget, vtText.TRADING, QtCore.Qt.LeftDockWidgetArea)

        self.tabifyDockWidget(dockTradeM, dockErrorM)
        self.tabifyDockWidget(dockTradeM, dockLogM)
        self.tabifyDockWidget(dockPositionM, dockAccountM)
        self.tabifyDockWidget(dockPositionM, dockWorkingOrderM)

        dockTradeM.raise_()
        dockPositionM.raise_()

        # 连接组件之间的信号
        widgetPositionM.itemDoubleClicked.connect(widgetTradingW.closePosition)
        widgetMarketM.itemDoubleClicked.connect(widgetTradingW.autoFillSymbol)

        # 保存默认设置
        self.saveWindowSettings('default')

    #----------------------------------------------------------------------
    def initMenu(self):
        """初始化菜单"""

        autoDisconnetAction = QtWidgets.QAction(u'自动断开重连', self)
        autoDisconnetAction.triggered.connect(self.setAutoDisconnect)

        # 创建菜单
        menubar = self.menuBar()

        # 系统
        sysMenu = menubar.addMenu(vtText.SYSTEM)
        # 系统，连接的接口清单
        gatewayDetails = self.mainEngine.getAllGatewayDetails()

        gatewayDetails = sorted(gatewayDetails,key=lambda  gw:gw['gatewayName'])
        has_gw = False
        # 期货类接口
        for d in gatewayDetails:
            if d['gatewayType'] == GATEWAYTYPE_FUTURES:
                self.addConnectAction(sysMenu, d['gatewayName'], d['gatewayDisplayName'])
                has_gw = True

        if has_gw:
            sysMenu.addSeparator()
            has_gw = False

        for d in gatewayDetails:
            if d['gatewayType'] == GATEWAYTYPE_EQUITY:
                self.addConnectAction(sysMenu, d['gatewayName'], d['gatewayDisplayName'])
                has_gw = True
        if has_gw:
            sysMenu.addSeparator()
            has_gw = False


        for d in gatewayDetails:
            if d['gatewayType'] == GATEWAYTYPE_INTERNATIONAL:
                self.addConnectAction(sysMenu, d['gatewayName'], d['gatewayDisplayName'])
                has_gw = True
        if has_gw:
            sysMenu.addSeparator()
            has_gw = False


        for d in gatewayDetails:
            if d['gatewayType'] == GATEWAYTYPE_BTC:
                self.addConnectAction(sysMenu, d['gatewayName'], d['gatewayDisplayName'])
                has_gw = True
        if has_gw:
            sysMenu.addSeparator()
            has_gw = False

        # 系统=》自动重连， 接口连接后，断开时，自动重连
        sysMenu.addSeparator()
        sysMenu.addAction(autoDisconnetAction)

        # 系统=》连接数据库
        sysMenu.addSeparator()
        sysMenu.addAction(
            self.createAction(vtText.CONNECT_DATABASE, self.mainEngine.dbConnect, loadIconPath('database.ico')))

        # 系统=》退出菜单
        sysMenu.addSeparator()
        sysMenu.addAction(self.createAction(vtText.EXIT, self.close, loadIconPath('exit.ico')))

        # 功能应用
        appMenu = menubar.addMenu(vtText.APPLICATION)
        for appDetail in self.appDetailList:
            function = self.createOpenAppFunction(appDetail)
            action = self.createAction(appDetail['appDisplayName'], function, loadIconPath(appDetail['appIco']))
            appMenu.addAction(action)

        # 算法相关
        #algoMenu = menubar.addMenu(u'算法')
        #algoMenu.addAction(ctaAction)
        spreadAction = self.createAction(u'网格套利',self.openSpread)
        appMenu.addAction(spreadAction)
        #appMenu.addAction(kChart)

        # 帮助
        helpMenu = menubar.addMenu(vtText.HELP)
        helpMenu.addAction(
            self.createAction(vtText.CONTRACT_SEARCH, self.openContract, loadIconPath('contract.ico')))
        helpMenu.addAction(
            self.createAction(vtText.EDIT_SETTING, self.openSettingEditor, loadIconPath('editor.ico')))
        helpMenu.addSeparator()
        helpMenu.addAction(self.createAction(vtText.RESTORE, self.restoreWindow, loadIconPath('restore.ico')))
        helpMenu.addAction(self.createAction(vtText.ABOUT, self.openAbout, loadIconPath('about.ico')))
        helpMenu.addSeparator()
        helpMenu.addAction(self.createAction(vtText.TEST, self.test, loadIconPath('test.ico')))

    # ----------------------------------------------------------------------
    def initStatusBar(self):
        """初始化状态栏"""
        self.statusLabel = QtWidgets.QLabel()
        self.statusLabel.setAlignment(QtCore.Qt.AlignLeft)

        self.statusBar().addPermanentWidget(self.statusLabel)
        self.statusLabel.setText(self.getCpuMemory())

        self.sbCount = 0
        self.sbTrigger = 10     # 10秒刷新一次
        self.signalStatusBar.connect(self.updateStatusBar)
        self.eventEngine.register(EVENT_TIMER, self.signalStatusBar.emit)

    # ----------------------------------------------------------------------
    def updateStatusBar(self, event):
        """1、在状态栏更新CPU和内存信息"""
        # 2、定时断开服务器连接
        # 3、定时重连服务器
        # 4、定时保存每日的委托单
        # 5、定时执行策略的保存事件

        self.sbCount += 1

       # 更新任务栏
        if self.sbCount == self.sbTrigger:
            self.sbCount = 0
            info = self.getCpuMemory()

            if self.autoDisConnect:
                info = info + u'[自动断开重连]'

            self.statusLabel.setText(info)
            if self.connectGatewayDict:
                s = u','.join(str(e) for e in list(self.connectGatewayDict.values()))

                if not self.connected:
                    s = s + u' [已断开]'

                self.setWindowTitle(s)

            # 定时断开
            if self.connected and self.trade_off() and self.autoDisConnect:
               self.disconnect()
               self.mainEngine.writeLog(u'断开连接{0}'.format(list(self.connectGatewayDict.values())))
               self.mainEngine.writeLog(u'清空数据引擎')
               self.mainEngine.clearData()
               self.mainEngine.writeLog(u'清空委托列表')
               self.widgetOrderM.clearData()
               self.mainEngine.writeLog(u'清空交易列表')
               self.widgetTradeM.clearData()

            # 定时重连
            if not self.connected \
                    and self.autoDisConnect \
                    and not self.trade_off()\
                    and len(self.connectGatewayDict) > 0:

                    self.mainEngine.writeLog(u'清空数据引擎')
                    self.mainEngine.clearData()
                    self.mainEngine.writeLog(u'清空委托列表')
                    self.widgetOrderM.clearData()
                    self.mainEngine.writeLog(u'清空交易列表')
                    self.widgetTradeM.clearData()
                    s = u''.join(str(e) for e in list(self.connectGatewayDict.values()))
                    self.mainEngine.writeLog(u'重新连接{0}'.format(s))

                    for key in self.connectGatewayDict.keys():
                        self.mainEngine.connect(key)

                    self.connected = True

            # 交易日收盘后保存所有委托记录，
            dt = datetime.now()
            today = datetime.now().strftime('%y%m%d')
            if dt.hour == 15 and dt.minute == 16 and len(self.connectGatewayDict) > 0 and today!=self.orderSaveDate:
                self.orderSaveDate = today
                self.mainEngine.writeLog(u'保存所有委托记录')
                orders_folder = os.path.abspath(os.path.join(os.getcwd(), 'orders'))

                if not os.path.isdir(orders_folder):
                    os.mkdir(orders_folder)

                orderfile = os.path.abspath(os.path.join(orders_folder, '{}.csv'.format(self.orderSaveDate)))

                if os.path.exists(orderfile):
                    return
                else:
                    self.widgetOrderM.saveToCsv(path=orderfile)

            # 调用各策略保存数据
            if ((dt.hour == 15 and dt.minute == 1) or (dt.hour == 2 and dt.minute == 31))  \
                and len(self.connectGatewayDict) > 0 \
                and today != self.barSaveDate \
                and self.connected:
                self.barSaveDate = today
                self.mainEngine.writeLog(u'调用各策略保存数据')
                self.mainEngine.saveData()

            if not (dt.hour == 15 or dt.hour == 2):
                self.barSaveDate = EMPTY_STRING

    # ----------------------------------------------------------------------
    def getCpuMemory(self):
        """获取CPU和内存状态信息"""
        cpuPercent = psutil.cpu_percent()
        memoryPercent = psutil.virtual_memory().percent
        return vtText.CPU_MEMORY_INFO.format(cpu=cpuPercent, memory=memoryPercent)

    def setAutoDisconnect(self):
        if self.autoDisConnect:
            self.autoDisConnect = False
        else:
            self.autoDisConnect = True

    # ----------------------------------------------------------------------
    def addConnectAction(self, menu, gatewayName, displayName=''):
        """增加连接功能"""
        if gatewayName not in self.gatewayNameList:
            return

        def connect():
            r = False
            try:
                r = self.mainEngine.connect(gatewayName)
            except:
                print( "Unexpected error:", sys.exc_info()[0])
                traceback.print_exc()

            if r:
                self.connectGatewayDict[gatewayName] = gatewayName
                self.connected = True

        if not displayName:
            displayName = gatewayName

        actionName = vtText.CONNECT + displayName
        connectAction = self.createAction(actionName, connect,
                                          loadIconPath('connect.ico'))
        menu.addAction(connectAction)

        # ----------------------------------------------------------------------

    def createAction(self, actionName, function, iconPath=''):
        """创建操作功能"""
        action = QtWidgets.QAction(actionName, self)
        action.triggered.connect(function)

        if iconPath:
            icon = QtGui.QIcon(iconPath)
            action.setIcon(icon)

        return action

    # ----------------------------------------------------------------------
    def createOpenAppFunction(self, appDetail):
        """创建打开应用UI的函数"""
        def openAppFunction():
            appName = appDetail['appName']
            if appName in self.widgetDict:
                self.widgetDict[appName].show()
            else:
                try:
                    appEngine = self.mainEngine.getApp(appName)
                    app_widget = appDetail.get('appWidget')
                    if app_widget:
                        self.widgetDict[appName] = app_widget(appEngine, self.eventEngine)
                        self.widgetDict[appName].show()
                except:
                    print( "Unexpected error:", sys.exc_info()[0])
                    traceback.print_exc()

        return openAppFunction

    # ----------------------------------------------------------------------
    def test(self):
        """测试按钮用的函数"""
        # 有需要使用手动触发的测试函数可以写在这里
        self.mainEngine.qryStatus()
        self.mainEngine.saveData()
        pass

    # ----------------------------------------------------------------------
    def openAbout(self):
        """打开关于"""
        try:
            self.widgetDict['aboutW'].show()
        except KeyError:
            self.widgetDict['aboutW'] = AboutWidget(self)
            self.widgetDict['aboutW'].show()

    # ----------------------------------------------------------------------
    def openContract(self):
        """打开合约查询"""
        if 'contractM' in self.widgetDict:
            self.widgetDict['contractM'].show()
        else:
            try:
                self.widgetDict['contractM'] = ContractMonitor(self.mainEngine)
                self.widgetDict['contractM'].show()
            except :
                print( "Unexpected error:", sys.exc_info()[0])
                traceback.print_exc()

    # ----------------------------------------------------------------------
    def openSettingEditor(self):
        """打开配置编辑"""
        if 'settingEditor' in self.widgetDict:
            self.widgetDict['settingEditor'].show()
        else:
            try:
                self.widgetDict['settingEditor'] = SettingEditor(self.mainEngine)
                self.widgetDict['settingEditor'].show()
            except :
                print( "Unexpected error:", sys.exc_info()[0])
                traceback.print_exc()

    # ----------------------------------------------------------------------
    def openSpread(self):
        """打开SpreadTrade组件"""
        if 'spread' in self.widgetDict:
            self.widgetDict['spread'].show()
            return

        try:
            if self.mainEngine.ctaEngine is None:
                print( u'not init Cta Engine')
                return

            from vnpy.trader.app.ctaStrategy.uiSpreadTrade import SpreadTradeManager
            self.widgetDict['spread'] = SpreadTradeManager(self.mainEngine.ctaEngine, self.eventEngine)
            self.widgetDict['spread'].show()
        except Exception as ex:
            print( "Unexpected error:", sys.exc_info()[0])
            traceback.print_exc()
            return

    # ----------------------------------------------------------------------
    def openMultiRpcMonitor(self):
        if 'multiRpc' in self.widgetDict:
            self.widgetDict['multiRpc'].showMaximized()
            return

        try:
            from vnpy.trader.uiMultiRpcMonitor import MultiRpcServerManager

            self.widgetDict['multiRpc'] = MultiRpcServerManager()
            self.widgetDict['multiRpc'].showMaximized()
        except:
            pass

    # ----------------------------------------------------------------------
    def closeEvent(self, event):
        """关闭事件"""
        reply = QtWidgets.QMessageBox.question(self, vtText.EXIT,
                                           vtText.CONFIRM_EXIT, QtWidgets.QMessageBox.Yes |
                                           QtWidgets.QMessageBox.No, QtWidgets.QMessageBox.No)

        if reply == QtWidgets.QMessageBox.Yes:
            for widget in list(self.widgetDict.values()):
                widget.close()
            self.saveWindowSettings('custom')

            self.mainEngine.exit()
            event.accept()
        else:
            event.ignore()

    # ----------------------------------------------------------------------
    def createDock(self, widgetClass, widgetName, widgetArea):
        """创建停靠组件"""
        widget = widgetClass(self.mainEngine, self.eventEngine)
        dock = QtWidgets.QDockWidget(widgetName)
        dock.setWidget(widget)
        dock.setObjectName(widgetName)
        dock.setFeatures(dock.DockWidgetFloatable|dock.DockWidgetMovable)
        self.addDockWidget(widgetArea, dock)
        return widget, dock

    # ----------------------------------------------------------------------
    def saveWindowSettings(self, settingName):
        """保存窗口设置"""
        settings = QtCore.QSettings('vn.trader', settingName)
        settings.setValue('state', self.saveState())
        settings.setValue('geometry', self.saveGeometry())

    # ----------------------------------------------------------------------
    def loadWindowSettings(self, settingName):
        """载入窗口设置"""
        settings = QtCore.QSettings('vn.trader', settingName)
        state = settings.value('state')
        geometry = settings.value('geometry')

        # 尚未初始化
        if state is None:
            return
        # 老版PyQt
        elif isinstance(state, QtCore.QVariant):
            self.restoreState(state.toByteArray())
            self.restoreGeometry(geometry.toByteArray())
        # 新版PyQt
        elif isinstance(state, QtCore.QByteArray):
            self.restoreState(state)
            self.restoreGeometry(geometry)
        # 异常
        else:
            content = u'载入窗口配置异常，请检查'
            self.mainEngine.writeLog(content)

    def disconnect(self):
        """"断开底层gateway的连接"""
        self.mainEngine.disconnect()
        self.connected = False

    def trade_off(self):
        """检查现在是否为非交易时间"""
        now = datetime.now()
        a = datetime.now().replace(hour=2, minute=35, second=0, microsecond=0)
        b = datetime.now().replace(hour=8, minute=30, second=0, microsecond=0)
        c = datetime.now().replace(hour=15, minute=30, second=0, microsecond=0)
        d = datetime.now().replace(hour=20, minute=30, second=0, microsecond=0)
        weekend = (now.isoweekday() == 6 and now >= a) or (now.isoweekday() == 7)
        off = (a<= now <= b) or (c <= now <= d) or weekend
        return off

    # ----------------------------------------------------------------------
    def restoreWindow(self):
        """还原默认窗口设置（还原停靠组件位置）"""
        self.loadWindowSettings('default')
        self.showMaximized()


########################################################################
class AboutWidget(QtWidgets.QDialog):
    """显示关于信息"""

    # ----------------------------------------------------------------------
    def __init__(self, parent=None):
        """Constructor"""
        super(AboutWidget, self).__init__(parent)

        self.initUi()

    # ----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(vtText.ABOUT + 'VnTrader')

        text = u"""
            Developed by Traders, for Traders.

            License：MIT
            
            Website：www.vnpy.org

            Github：www.github.com/vnpy/vnpy
            
            """

        label = QtWidgets.QLabel()
        label.setText(text)
        label.setMinimumWidth(500)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(label)

        self.setLayout(vbox)
