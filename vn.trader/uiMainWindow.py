# encoding: UTF-8

import psutil

from uiBasicWidget import *
from ctaAlgo.uiCtaWidget import CtaEngineManager
from dataRecorder.uiDrWidget import DrEngineManager


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
        marketM = MarketMonitor(self.mainEngine, self.eventEngine)
        logM = LogMonitor(self.mainEngine, self.eventEngine)
        errorM = ErrorMonitor(self.mainEngine, self.eventEngine)
        tradeM = TradeMonitor(self.mainEngine, self.eventEngine)
        orderM = OrderMonitor(self.mainEngine, self.eventEngine)
        positionM = PositionMonitor(self.mainEngine, self.eventEngine)
        accountM = AccountMonitor(self.mainEngine, self.eventEngine)
        
        tradingW = TradingWidget(self.mainEngine, self.eventEngine)
        
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
        
        connectKsotpAction = QtGui.QAction(u'连接金仕达期权', self)
        connectKsotpAction.triggered.connect(self.connectKsotp)
        
        connectFemasAction = QtGui.QAction(u'连接飞马', self)
        connectFemasAction.triggered.connect(self.connectFemas)  
        
        connectXspeedAction = QtGui.QAction(u'连接飞创', self)
        connectXspeedAction.triggered.connect(self.connectXspeed)          
        
        connectKsgoldAction = QtGui.QAction(u'连接金仕达黄金', self)
        connectKsgoldAction.triggered.connect(self.connectKsgold)  
        
        connectSgitAction = QtGui.QAction(u'连接飞鼠', self)
        connectSgitAction.triggered.connect(self.connectSgit)         
        
        connectWindAction = QtGui.QAction(u'连接Wind', self)
        connectWindAction.triggered.connect(self.connectWind)
        
        connectIbAction = QtGui.QAction(u'连接IB', self)
        connectIbAction.triggered.connect(self.connectIb) 
        
        connectOandaAction = QtGui.QAction(u'连接OANDA', self)
        connectOandaAction.triggered.connect(self.connectOanda)
        
        connectDbAction = QtGui.QAction(u'连接数据库', self)
        connectDbAction.triggered.connect(self.mainEngine.dbConnect)
        
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
        
        # 创建菜单
        menubar = self.menuBar()
        
        sysMenu = menubar.addMenu(u'系统')
        sysMenu.addAction(connectCtpAction)
        sysMenu.addAction(connectLtsAction)
        sysMenu.addAction(connectFemasAction)
        sysMenu.addAction(connectXspeedAction)
        sysMenu.addAction(connectKsotpAction)
        sysMenu.addAction(connectKsgoldAction)
        sysMenu.addAction(connectSgitAction)
        sysMenu.addSeparator()
        sysMenu.addAction(connectIbAction)    
        sysMenu.addAction(connectOandaAction)
        sysMenu.addSeparator()
        sysMenu.addAction(connectWindAction)
        sysMenu.addSeparator()
        sysMenu.addAction(connectDbAction)
        sysMenu.addSeparator()
        sysMenu.addAction(exitAction)
        
        functionMenu = menubar.addMenu(u'功能')
        functionMenu.addAction(contractAction)
        functionMenu.addAction(drAction)
        
        # 算法相关
        algoMenu = menubar.addMenu(u'算法')
        algoMenu.addAction(ctaAction)
        
        # 帮助
        helpMenu = menubar.addMenu(u'帮助')
        helpMenu.addAction(aboutAction)  
        helpMenu.addAction(testAction)
    
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
    def connectKsotp(self):
        """连接金仕达期权接口"""
        self.mainEngine.connect('KSOTP')        
        
    #----------------------------------------------------------------------
    def connectFemas(self):
        """连接飞马接口"""
        self.mainEngine.connect('FEMAS')        
    
    #----------------------------------------------------------------------
    def connectXspeed(self):
        """连接飞马接口"""
        self.mainEngine.connect('XSPEED')             
    
    #----------------------------------------------------------------------
    def connectKsgold(self):
        """连接金仕达黄金接口"""
        self.mainEngine.connect('KSGOLD')            
        
    #----------------------------------------------------------------------
    def connectSgit(self):
        """连接飞鼠接口"""
        self.mainEngine.connect('SGIT')     
    
    #----------------------------------------------------------------------
    def connectWind(self):
        """连接Wind接口"""
        self.mainEngine.connect('Wind')
    
    #----------------------------------------------------------------------
    def connectIb(self):
        """连接Ib"""
        self.mainEngine.connect('IB')
        
    #----------------------------------------------------------------------
    def connectOanda(self):
        """连接OANDA"""
        self.mainEngine.connect('OANDA')
        
    #----------------------------------------------------------------------
    def test(self):
        """测试按钮用的函数"""
        api = self.mainEngine.gatewayDict['KSGOLD'].tdApi
        api.reqID += 1
        api.reqQryOrder({}, api.reqID)
        #api.reqQryTrade({}, api.reqID)

    #----------------------------------------------------------------------
    def openAbout(self):
        """打开关于"""
        try:
            self.widgetDict['aboutW'].show()
        except KeyError:
            self.widgetDict['aboutW'] = AboutWidget(self)
            self.widgetDict['aboutW'].show()
    
    #----------------------------------------------------------------------
    def openContract(self):
        """打开合约查询"""
        try:
            self.widgetDict['contractM'].show()
        except KeyError:
            self.widgetDict['contractM'] = ContractMonitor(self.mainEngine)
            self.widgetDict['contractM'].show()
            
    #----------------------------------------------------------------------
    def openCta(self):
        """打开CTA组件"""
        try:
            self.widgetDict['ctaM'].show()
        except KeyError:
            self.widgetDict['ctaM'] = CtaEngineManager(self.mainEngine.ctaEngine, self.eventEngine)
            self.widgetDict['ctaM'].show()
            
    #----------------------------------------------------------------------
    def openDr(self):
        """打开行情数据记录组件"""
        try:
            self.widgetDict['drM'].show()
        except KeyError:
            self.widgetDict['drM'] = DrEngineManager(self.mainEngine.drEngine, self.eventEngine)
            self.widgetDict['drM'].show()    
    
    #----------------------------------------------------------------------
    def closeEvent(self, event):
        """关闭事件"""
        reply = QtGui.QMessageBox.question(self, u'退出',
                                           u'确认退出?', QtGui.QMessageBox.Yes | 
                                           QtGui.QMessageBox.No, QtGui.QMessageBox.No)

        if reply == QtGui.QMessageBox.Yes: 
            for widget in self.widgetDict.values():
                widget.close()
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
    