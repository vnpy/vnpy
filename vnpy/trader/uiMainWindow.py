# encoding: UTF-8

# from uiFullMonitorWidget import MonitorWidget
# from uiKChartWidget import CandleForm

import psutil

from vnpy.trader.app.ctaStrategy.uiCtaWidget import CtaEngineManager
from vnpy.trader.app.dataRecorder.uiDrWidget import DrEngineManager
from vnpy.trader.app.riskManager.uiRmWidget import RmEngineManager
from vnpy.trader.uiBasicWidget import *

########################################################################
class MainWindow(QtGui.QMainWindow):
    """主窗口"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        super(MainWindow, self).__init__()
        
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        self.widgetDict = {}    # 用来保存子窗口的字典

        self.connectGatewayDict = {}

        self.initUi()
        #self.loadWindowSettings()

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
        widgetMarketM, dockMarketM = self.createDock(MarketMonitor, u'行情', QtCore.Qt.RightDockWidgetArea)
        widgetLogM, dockLogM = self.createDock(LogMonitor, u'日志', QtCore.Qt.BottomDockWidgetArea)
        widgetErrorM, dockErrorM = self.createDock(ErrorMonitor, u'错误', QtCore.Qt.BottomDockWidgetArea)
        self.widgetTradeM, dockTradeM = self.createDock(TradeMonitor, u'成交', QtCore.Qt.BottomDockWidgetArea)
        self.widgetOrderM, dockOrderM = self.createDock(OrderMonitor, u'委托', QtCore.Qt.RightDockWidgetArea)
        widgetPositionM, dockPositionM = self.createDock(PositionMonitor, u'持仓', QtCore.Qt.BottomDockWidgetArea)
        widgetAccountM, dockAccountM = self.createDock(AccountMonitor, u'资金', QtCore.Qt.BottomDockWidgetArea)
        widgetTradingW, dockTradingW = self.createDock(TradingWidget, u'交易', QtCore.Qt.LeftDockWidgetArea)
    
        self.tabifyDockWidget(dockTradeM, dockErrorM)
        self.tabifyDockWidget(dockTradeM, dockLogM)
        self.tabifyDockWidget(dockPositionM, dockAccountM)
    
        dockTradeM.raise_()
        dockPositionM.raise_()
    
        # 连接组件之间的信号
        widgetPositionM.itemDoubleClicked.connect(widgetTradingW.closePosition)
        
    #----------------------------------------------------------------------
    def initMenu(self):
        """初始化菜单"""
        # 创建操作
        connectCtpProdAction = QtGui.QAction(u'上海中期CTP', self)
        connectCtpProdAction.triggered.connect(self.connectCtpProd)

        connectCtpPostAction = QtGui.QAction(u'中期盘后CTP', self)
        connectCtpPostAction.triggered.connect(self.connectCtpPost)

        connectCtpTestAction = QtGui.QAction(u'光大CTP', self)
        connectCtpTestAction.triggered.connect(self.connectCtpEBF)

        connectCtpJRAction = QtGui.QAction(u'金瑞CTP', self)
        connectCtpJRAction.triggered.connect(self.connectCtpJR)

        connectCtpJR2Action = QtGui.QAction(u'金瑞CTP2', self)
        connectCtpJR2Action.triggered.connect(self.connectCtpJR2)

        connectCtpAction = QtGui.QAction(u'连接CTP', self)
        connectCtpAction.triggered.connect(self.connectCtp)
        
        #connectLtsAction = QtGui.QAction(u'连接LTS', self)
        #connectLtsAction.triggered.connect(self.connectLts)
        
        #connectKsotpAction = QtGui.QAction(u'连接金仕达期权', self)
        #connectKsotpAction.triggered.connect(self.connectKsotp)
        
        #connectFemasAction = QtGui.QAction(u'连接飞马', self)
        #connectFemasAction.triggered.connect(self.connectFemas)
        
        #connectXspeedAction = QtGui.QAction(u'连接飞创', self)
        #connectXspeedAction.triggered.connect(self.connectXspeed)
        
        #connectKsgoldAction = QtGui.QAction(u'连接金仕达黄金', self)
        #connectKsgoldAction.triggered.connect(self.connectKsgold)
        
        #connectSgitAction = QtGui.QAction(u'连接飞鼠', self)
        #connectSgitAction.triggered.connect(self.connectSgit)
        
        #connectWindAction = QtGui.QAction(u'连接Wind', self)
        #connectWindAction.triggered.connect(self.connectWind)
        
        #connectIbAction = QtGui.QAction(u'连接IB', self)
        #connectIbAction.triggered.connect(self.connectIb)
        
        #connectOandaAction = QtGui.QAction(u'连接OANDA', self)
        #connectOandaAction.triggered.connect(self.connectOanda)
        
        connectDbAction = QtGui.QAction(u'连接数据库', self)
        connectDbAction.triggered.connect(self.mainEngine.dbConnect)

        autoDisconnetAction = QtGui.QAction(u'自动断开重连', self)
        autoDisconnetAction.triggered.connect(self.setAutoDisconnect)
        
        testAction = QtGui.QAction(u'测试', self)
        testAction.triggered.connect(self.test)
        
        exitAction = QtGui.QAction(u'退出', self)
        exitAction.triggered.connect(self.close)
        
        aboutAction = QtGui.QAction(u'关于', self)
        aboutAction.triggered.connect(self.openAbout)
        
        contractAction = QtGui.QAction(u'查询合约', self)
        contractAction.triggered.connect(self.openContract)
        
        drAction = QtGui.QAction(u'行情数据记录', self)
        drAction.triggered.connect(self.openDr)
        
        ctaAction = QtGui.QAction(u'CTA策略', self)
        ctaAction.triggered.connect(self.openCta)

        spreadAction = QtGui.QAction(u'套利交易', self)
        spreadAction.triggered.connect(self.openSpread)

        #kChart = QtGui.QAction(u'K线图', self)
        #kChart.triggered.connect(self.openKChart)
        
        rmAction = QtGui.QAction(u'风险管理', self)
        rmAction.triggered.connect(self.openRm)        
        
        # 创建菜单
        menubar = self.menuBar()
        
        # 设计为只显示存在的接口
        sysMenu = menubar.addMenu(u'系统')
        sysMenu.addAction(connectCtpProdAction)
        sysMenu.addAction(connectCtpPostAction)
        sysMenu.addAction(connectCtpTestAction)
        sysMenu.addAction(connectCtpJRAction)
        sysMenu.addAction(connectCtpJR2Action)

        if 'CTP' in self.mainEngine.gatewayDict:
            sysMenu.addAction(connectCtpAction)
        #if 'LTS' in self.mainEngine.gatewayDict:
        #    sysMenu.addAction(connectLtsAction)
        #if 'FEMAS' in self.mainEngine.gatewayDict:
        #    sysMenu.addAction(connectFemasAction)
        #if 'XSPEED' in self.mainEngine.gatewayDict:
        #    sysMenu.addAction(connectXspeedAction)
        #if 'KSOTP' in self.mainEngine.gatewayDict:
        #    sysMenu.addAction(connectKsotpAction)
        #if 'KSGOLD' in self.mainEngine.gatewayDict:
        #    sysMenu.addAction(connectKsgoldAction)
        #if 'SGIT' in self.mainEngine.gatewayDict:
        #    sysMenu.addAction(connectSgitAction)
        sysMenu.addSeparator()
        sysMenu.addAction(autoDisconnetAction)
        #if 'IB' in self.mainEngine.gatewayDict:
        #    sysMenu.addAction(connectIbAction)
        #if 'OANDA' in self.mainEngine.gatewayDict:
        #    sysMenu.addAction(connectOandaAction)
        #sysMenu.addSeparator()
        #if 'Wind' in self.mainEngine.gatewayDict:
        #    sysMenu.addAction(connectWindAction)
        sysMenu.addSeparator()
        sysMenu.addAction(connectDbAction)
        sysMenu.addSeparator()
        sysMenu.addAction(exitAction)
        
        functionMenu = menubar.addMenu(u'功能')
        functionMenu.addAction(contractAction)
        functionMenu.addAction(drAction)
        functionMenu.addAction(rmAction)
        
        # 算法相关
        algoMenu = menubar.addMenu(u'算法')
        algoMenu.addAction(ctaAction)
        algoMenu.addAction(spreadAction)
        #algoMenu.addAction(kChart)

        # 帮助
        helpMenu = menubar.addMenu(u'帮助')
        helpMenu.addAction(aboutAction)  
        helpMenu.addAction(testAction)
    
    # ----------------------------------------------------------------------
    def initStatusBar(self):
        """初始化状态栏"""
        self.statusLabel = QtGui.QLabel()
        self.statusLabel.setAlignment(QtCore.Qt.AlignLeft)
        
        self.statusBar().addPermanentWidget(self.statusLabel)
        self.statusLabel.setText(self.getCpuMemory())
        
        self.sbCount = 0
        self.sbTrigger = 10     # 10秒刷新一次
        self.eventEngine.register(EVENT_TIMER, self.updateStatusBar)

        
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
                s = u''.join(str(e) for e in self.connectGatewayDict.values())

                if not self.connected:
                    s = s + u' [已断开]'

                self.setWindowTitle(s)

            # 定时断开
            if self.connected and self.trade_off() and self.autoDisConnect:
               self.disconnect()
               self.mainEngine.writeLog(u'断开连接{0}'.format(self.connectGatewayDict.values()))
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
                    s = u''.join(str(e) for e in self.connectGatewayDict.values())
                    self.mainEngine.writeLog(u'重新连接{0}'.format(s))

                    for key in self.connectGatewayDict.keys():
                        self.mainEngine.connect(key)

                    self.connected = True

            # 交易日收盘后保存所有委托记录，
            dt = datetime.now()
            today = datetime.now().strftime('%y%m%d')
            if dt.hour == 15 and dt.minute == 1 and len(self.connectGatewayDict) > 0 and today!=self.orderSaveDate:
                self.orderSaveDate = today
                self.mainEngine.writeLog(u'保存所有委托记录')
                orderfile = os.getcwd() +'/orders/{0}.csv'.format(self.orderSaveDate)
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
        return u'CPU使用率：%d%%   内存使用率：%d%%' % (cpuPercent, memoryPercent)        
        
    # ----------------------------------------------------------------------
    def connectCtpProd(self):
        """连接上海中期生产环境CTP接口"""

        self.mainEngine.connect('CTP_Prod')
        self.connectGatewayDict['CTP_Prod'] = u'上海中期CTP'
        self.connected = True

    # ----------------------------------------------------------------------
    def connectCtpPost(self):
        """连接上海中期盘后CTP接口"""
        self.mainEngine.connect('CTP_Post')
        self.connectGatewayDict['CTP_Post'] = u'中期盘后CTP'
        self.connected = True

    def connectCtpEBF(self):
        """连接光大期货CTP接口"""
        self.mainEngine.connect('CTP_EBF')
        self.connectGatewayDict['CTP_EBF'] = u'光大CTP'
        self.connected = True

    def connectCtpJR(self):
        """连接金瑞期货CTP接口"""
        self.mainEngine.connect('CTP_JR')
        self.connectGatewayDict['CTP_JR'] = u'金瑞CTP'
        self.connected = True

    def connectCtpJR2(self):
        """连接金瑞期货CTP接口"""
        self.mainEngine.connect('CTP_JR2')
        self.connectGatewayDict['CTP_JR2'] = u'金瑞CTP2'
        self.connected = True

    def connectCtpTest(self):
        """连接SNOW测试环境CTP接口"""
        self.mainEngine.connect('CTP_Test')
        self.connectGatewayDict['CTP_Test'] = u'SNOW测试'
        self.connected = True

    def connectCtp(self):
        """连接CTP接口"""
        self.mainEngine.connect('CTP')
        self.connectGatewayDict['CTP'] = u'CTP'
        self.connected = True

    # ----------------------------------------------------------------------
    def connectLts(self):
        """连接LTS接口"""
        self.mainEngine.connect('LTS')
        self.connectGatewayDict['LTS'] = u'LTS'
        self.connected = True
        
    #----------------------------------------------------------------------
    def connectKsotp(self):
        """连接金仕达期权接口"""
        self.mainEngine.connect('KSOTP')
        self.connectGatewayDict['KSOTP'] = u'金仕达期权'
        self.connected = True
        
    #----------------------------------------------------------------------
    def connectFemas(self):
        """连接飞马接口"""
        self.mainEngine.connect('FEMAS')
        self.connectGatewayDict['FEMAS'] = u'FEMAS飞马'
        self.connected = True
    
    #----------------------------------------------------------------------
    def connectXspeed(self):
        """连接飞马接口"""
        self.mainEngine.connect('XSPEED')
        self.connectGatewayDict['XSPEED'] = u'XSPEED飞马接口'
        self.connected = True
    
    #----------------------------------------------------------------------
    def connectKsgold(self):
        """连接金仕达黄金接口"""
        self.mainEngine.connect('KSGOLD')
        self.connectGatewayDict ['KSGOLD'] = u'金仕达黄金'
        self.connected = True
        
    #----------------------------------------------------------------------
    def connectSgit(self):
        """连接飞鼠接口"""
        self.mainEngine.connect('SGIT')
        self.connectGatewayDict['SGIT'] = u'飞鼠'
        self.connected = True
    
    #----------------------------------------------------------------------
    def connectWind(self):
        """连接Wind接口"""
        self.mainEngine.connect('Wind')
        self.connectGatewayDict['Wind'] = u'Wind'
        self.connected = True
    
    # ----------------------------------------------------------------------

    def connectIb(self):
        """连接Ib"""
        self.mainEngine.connect('IB')
        self.connectGatewayDict['IB'] = u'盈透'
        self.connected = True
        
    #----------------------------------------------------------------------
    def connectOanda(self):
        """连接OANDA"""
        self.mainEngine.connect('OANDA')
        self.connectGatewayDict['OANDA'] = u'OANDA'
        self.connected = True

    def setAutoDisconnect(self):

        if self.autoDisConnect:
            self.autoDisConnect = False
        else:
            self.autoDisConnect = True


    #----------------------------------------------------------------------
    def test(self):
        """测试按钮用的函数"""
        # 有需要使用手动触发的测试函数可以写在这里
        self.mainEngine.saveData()
        pass

    #----------------------------------------------------------------------
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
        try:

            self.widgetDict['contractM'].show()
        except KeyError:
            self.widgetDict['contractM'] = ContractMonitor(self.mainEngine)
            self.widgetDict['contractM'].show()

    # ----------------------------------------------------------------------
    def openCta(self):
        """打开CTA组件"""
        try:
            self.widgetDict['ctaM'].showMaximized()
        except KeyError:
            self.widgetDict['ctaM'] = CtaEngineManager(self.mainEngine.ctaEngine, self.eventEngine)
            self.widgetDict['ctaM'].showMaximized()

    #def openMonitor(self):
    #    try:
    #        self.widgetDict['Monitor'].showMaximized()
    #    except KeyError:
    #        self.widgetDict['Monitor'] = MonitorWidget(self.mainEngine.ctaEngine, self.eventEngine)
    #        self.widgetDict['Monitor'].showMaximized()
#
    #def openKChart(self):
    #    try:
    #        self.widgetDict['kChart'].showMaximized()
    #    except KeyError:
    #        self.widgetDict['kChart'] = CandleForm(self.mainEngine.ctaEngine, self.eventEngine, symbol='p1705', period='minute',interval=5)
    #        self.widgetDict['kChart'].showMaximized()


    #----------------------------------------------------------------------
    def openDr(self):
        """打开行情数据记录组件"""
        try:
            self.widgetDict['drM'].showMaximized()
        except KeyError:
            self.widgetDict['drM'] = DrEngineManager(self.mainEngine.drEngine, self.eventEngine)
            self.widgetDict['drM'].showMaximized()

    #----------------------------------------------------------------------
    def openRm(self):
        """打开组件"""
        try:
            self.widgetDict['rmM'].show()
        except KeyError:
            self.widgetDict['rmM'] = RmEngineManager(self.mainEngine.rmEngine, self.eventEngine)
            self.widgetDict['rmM'].show()

    # ----------------------------------------------------------------------
    def openSpread(self):
        """打开SpreadTrade组件"""

        if 'spread' in self.widgetDict:
            self.widgetDict['spread'].show()
            return

        try:
            from vnpy.trader.app.ctaStrategy.uiSpreadTrade import SpreadTradeManager
            self.widgetDict['spread'] = SpreadTradeManager(self.mainEngine.ctaEngine, self.eventEngine)
            self.widgetDict['spread'].show()
        except Exception as ex:
            return

    #----------------------------------------------------------------------
    def closeEvent(self, event):
        """关闭事件"""
        reply = QtGui.QMessageBox.question(self, u'退出',
                                           u'确认退出?', QtGui.QMessageBox.Yes | 
                                           QtGui.QMessageBox.No, QtGui.QMessageBox.No)

        if reply == QtGui.QMessageBox.Yes: 
            for widget in self.widgetDict.values():
                widget.close()
            self.saveWindowSettings()
            
            self.mainEngine.exit()
            event.accept()
        else:
            event.ignore()
            
    #----------------------------------------------------------------------
    def createDock(self, widgetClass, widgetName, widgetArea):
        """创建停靠组件"""
        widget = widgetClass(self.mainEngine, self.eventEngine)
        dock = QtGui.QDockWidget(widgetName)
        dock.setWidget(widget)
        dock.setObjectName(widgetName)
        dock.setFeatures(dock.DockWidgetFloatable|dock.DockWidgetMovable)
        self.addDockWidget(widgetArea, dock)
        return widget, dock
    
    #----------------------------------------------------------------------
    def saveWindowSettings(self):
        """保存窗口设置"""
        settings = QtCore.QSettings('vn.py', 'vn.trader')
        settings.setValue('state', self.saveState())
        settings.setValue('geometry', self.saveGeometry())
        
    #----------------------------------------------------------------------
    def loadWindowSettings(self):
        """载入窗口设置"""
        settings = QtCore.QSettings('vn.py', 'vn.trader')
        # 这里由于PyQt4的版本不同，settings.value('state')调用返回的结果可能是：
        # 1. None（初次调用，注册表里无相应记录，因此为空）
        # 2. QByteArray（比较新的PyQt4）
        # 3. QVariant（以下代码正确执行所需的返回结果）
        # 所以为了兼容考虑，这里加了一个try...except，如果是1、2的情况就pass
        # 可能导致主界面的设置无法载入（每次退出时的保存其实是成功了）
        try:
            self.restoreState(settings.value('state').toByteArray())
            self.restoreGeometry(settings.value('geometry').toByteArray())
        except AttributeError:
            pass


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

########################################################################
class AboutWidget(QtGui.QDialog):
    """显示关于信息"""

    # ----------------------------------------------------------------------
    def __init__(self, parent=None):
        """Constructor"""
        super(AboutWidget, self).__init__(parent)

        self.initUi()

    # ----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'关于VnTrader')

        text = u"""
            Developed by traders, for traders.

            License：MIT
            
            Website：www.vnpy.org

            Github：www.github.com/vnpy/vnpy
            
            """

        label = QtGui.QLabel()
        label.setText(text)
        label.setMinimumWidth(500)

        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(label)

        self.setLayout(vbox)
    