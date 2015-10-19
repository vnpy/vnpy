# encoding: UTF-8

import psutil

from uiBasicWidget import *


########################################################################
class MainWindow(QtGui.QMainWindow):
    """主窗口"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, dataEngine):
        """Constructor"""
        super(MainWindow, self).__init__()
        
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        self.dataEngine = dataEngine
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle('VnTrader')
        self.initCentral()
        self.initMenu()
        self.initStatusBar()
        
    #----------------------------------------------------------------------
    def initCentral(self):
        """初始化中心区域"""
        marketM = MarketMonitor(self.eventEngine)
        logM = LogMonitor(self.eventEngine)
        errorM = ErrorMonitor(self.eventEngine)
        tradeM = TradeMonitor(self.eventEngine)
        orderM = OrderMonitor(self.eventEngine, self.mainEngine)
        positionM = PositionMonitor(self.eventEngine)
        accountM = AccountMonitor(self.eventEngine)
        
        tradingW = TradingWidget(self.mainEngine, self.mainEngine.eventEngine, self.mainEngine.dataEngine)
        
        leftTab = QtGui.QTabWidget()
        leftTab.addTab(logM, u'日志')
        leftTab.addTab(errorM, u'错误')
        leftTab.addTab(accountM, u'账户')
        
        rightTab = QtGui.QTabWidget()
        rightTab.addTab(tradeM, u'成交')
        rightTab.addTab(orderM, u'委托')
        rightTab.addTab(positionM, u'持仓')
    
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(tradingW)
        hbox.addWidget(marketM)
        
        grid = QtGui.QGridLayout()
        grid.addLayout(hbox, 0, 0, 1, 2)
        grid.addWidget(leftTab, 1, 0)
        grid.addWidget(rightTab, 1, 1)
        
        central = QtGui.QWidget()
        central.setLayout(grid)
        self.setCentralWidget(central)
        
    #----------------------------------------------------------------------
    def initMenu(self):
        """初始化菜单"""
        # 创建操作
        connectCtpAction = QtGui.QAction(u'连接CTP', self)
        connectCtpAction.triggered.connect(self.connectCtp)
        
        connectLtsAction = QtGui.QAction(u'连接LTS', self)
        connectLtsAction.triggered.connect(self.connectLts)
        
        connectWindAction = QtGui.QAction(u'连接Wind', self)
        connectWindAction.triggered.connect(self.connectWind)
        
        testAction = QtGui.QAction(u'测试', self)
        testAction.triggered.connect(self.testSubscribe)
        
        exitAction = QtGui.QAction(u'退出', self)
        exitAction.triggered.connect(self.close)
        
        aboutAction = QtGui.QAction(u'关于', self)
        aboutAction.triggered.connect(self.openAbout)
        
        contractAction = QtGui.QAction(u'查询合约', self)
        contractAction.triggered.connect(self.openContract)
        
        # 创建菜单
        menubar = self.menuBar()
        
        sysMenu = menubar.addMenu(u'系统')
        sysMenu.addAction(connectCtpAction)
        sysMenu.addAction(connectLtsAction)
        sysMenu.addAction(connectWindAction)
        sysMenu.addAction(testAction)
        sysMenu.addAction(exitAction)
        
        functionMenu = menubar.addMenu(u'功能')
        functionMenu.addAction(contractAction)
        
        helpMenu = menubar.addMenu(u'帮助')
        helpMenu.addAction(aboutAction)
    
    #----------------------------------------------------------------------
    def initStatusBar(self):
        """初始化状态栏"""
        self.statusLabel = QtGui.QLabel()
        self.statusLabel.setAlignment(QtCore.Qt.AlignLeft)
        
        self.statusBar().addPermanentWidget(self.statusLabel)
        self.statusLabel.setText(self.getCpuMemory())
        
        self.sbCount = 0
        self.sbTrigger = 10     # 10秒刷新一次
        self.eventEngine.register(EVENT_TIMER, self.updateStatusBar)
        
    #----------------------------------------------------------------------
    def updateStatusBar(self, event):
        """在状态栏更新CPU和内存信息"""
        self.sbCount += 1
        
        if self.sbCount == self.sbTrigger:
            self.sbCount = 0
            self.statusLabel.setText(self.getCpuMemory())
    
    #----------------------------------------------------------------------
    def getCpuMemory(self):
        """获取CPU和内存状态信息"""
        cpuPercent = psutil.cpu_percent()
        memoryPercent = psutil.virtual_memory().percent
        return u'CPU使用率：%d%%   内存使用率：%d%%' % (cpuPercent, memoryPercent)        
        
    #----------------------------------------------------------------------
    def connectCtp(self):
        """连接CTP接口"""
        self.mainEngine.connect('CTP')
        
    #----------------------------------------------------------------------
    def connectLts(self):
        """连接LTS接口"""
        self.mainEngine.connect('LTS')    
    
    #----------------------------------------------------------------------
    def connectWind(self):
        """连接Wind接口"""
        self.mainEngine.connect('Wind')
    
    #----------------------------------------------------------------------
    def testSubscribe(self):
        """测试订阅"""
        req = VtSubscribeReq()
        req.symbol = '600000'
        req.exchange = EXCHANGE_SSE
        self.mainEngine.subscribe(req, 'Wind')
        
        req = VtSubscribeReq()
        req.symbol = '000062'
        req.exchange = EXCHANGE_SZSE
        self.mainEngine.subscribe(req, 'Wind')        
        
        req = VtSubscribeReq()
        req.symbol = 'IF1511'
        req.exchange = EXCHANGE_CFFEX
        self.mainEngine.subscribe(req, 'Wind')
        
        req = VtSubscribeReq()
        req.symbol = 'CU1601'
        req.exchange = EXCHANGE_SHFE
        self.mainEngine.subscribe(req, 'Wind')
        
        req = VtSubscribeReq()
        req.symbol = 'C1601'
        req.exchange = EXCHANGE_DCE
        self.mainEngine.subscribe(req, 'Wind')       
        
        req = VtSubscribeReq()
        req.symbol = 'SR1601'
        req.exchange = EXCHANGE_CZCE
        self.mainEngine.subscribe(req, 'Wind')             
        
    #----------------------------------------------------------------------
    def openAbout(self):
        """打开关于"""
        try:
            self.aboutW.show()
        except AttributeError:
            self.aboutW = AboutWidget(self)
            self.aboutW.show()
    
    #----------------------------------------------------------------------
    def openContract(self):
        """打开合约查询"""
        try:
            self.contractM.show()
        except AttributeError:
            self.contractM = ContractMonitor(self.mainEngine.dataEngine)
            self.contractM.show()
    
    #----------------------------------------------------------------------
    def closeEvent(self, event):
        """关闭事件"""
        reply = QtGui.QMessageBox.question(self, u'退出',
                                           u'确认退出?', QtGui.QMessageBox.Yes | 
                                           QtGui.QMessageBox.No, QtGui.QMessageBox.No)

        if reply == QtGui.QMessageBox.Yes:        
            self.mainEngine.exit()
            event.accept()
        else:
            event.ignore()


########################################################################
class AboutWidget(QtGui.QDialog):
    """显示关于信息"""

    #----------------------------------------------------------------------
    def __init__(self, parent=None):
        """Constructor"""
        super(AboutWidget, self).__init__(parent)

        self.initUi()

    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'关于')

        text = u"""
            VnTrader

            更新日期：2015/9/29

            作者：用Python的交易员

            License：MIT

            主页：vnpy.org

            Github：github.com/vnpy/vnpy

            QQ交流群：262656087




            开发环境

            操作系统：Windows 7 专业版 64位

            Python发行版：Python 2.7.6 (Anaconda 1.9.2 Win-32)

            CTP：vn.ctp  2015/6/1版

            图形库：PyQt4 4.11.3 Py2.7-x32

            事件驱动引擎：vn.event

            开发环境：WingIDE 5.0.6
            
            
            """

        label = QtGui.QLabel()
        label.setText(text)
        label.setMinimumWidth(500)

        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(label)

        self.setLayout(vbox)
    