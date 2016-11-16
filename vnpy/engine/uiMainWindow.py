# -*- coding: utf-8 -*-

import psutil

from vnpy.engine.cta.uiCtaWidget import CtaEngineManager
from vnpy.engine.dr.uiDrWidget import DrEngineManager
from vnpy.engine.rm.uiRmWidget import RmEngineManager
from vnpy.engine.uiBasicWidget import *


########################################################################
class MainWindow(QtGui.QMainWindow):
    """主窗口"""
    signalStatusBar = QtCore.pyqtSignal(type(Event()))

    # ----------------------------------------------------------------------
    def __init__(self, main_engine, event_engine):
        """Constructor"""
        super(MainWindow, self).__init__()

        self.mainEngine = main_engine
        self.eventEngine = event_engine

        self.widgetDict = {}  # 用来保存子窗口的字典

        self.sbTrigger = 10  # 10秒刷新一次
        self.sbCount = 0
        self.statusLabel = QtGui.QLabel()

        self.initUi()
        self.loadWindowSettings()

    # ----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle('VnTrader')
        self.initCentral()
        self.initMenu()
        self.initStatusBar()

    # ----------------------------------------------------------------------
    def initCentral(self):
        """初始化中心区域"""
        self.createDock(MarketMonitor, u'行情', QtCore.Qt.RightDockWidgetArea)
        widget_log_m, dock_log_m = self.createDock(LogMonitor, u'日志', QtCore.Qt.BottomDockWidgetArea)
        widget_error_m, dock_error_m = self.createDock(ErrorMonitor, u'错误', QtCore.Qt.BottomDockWidgetArea)
        widget_trade_m, dock_trade_m = self.createDock(TradeMonitor, u'成交', QtCore.Qt.BottomDockWidgetArea)
        self.createDock(OrderMonitor, u'委托', QtCore.Qt.RightDockWidgetArea)
        widget_position_m, dock_position_m = self.createDock(PositionMonitor, u'持仓', QtCore.Qt.BottomDockWidgetArea)
        widget_account_m, dock_account_m = self.createDock(AccountMonitor, u'资金', QtCore.Qt.BottomDockWidgetArea)
        widget_trading_w, dock_trading_w = self.createDock(TradingWidget, u'交易', QtCore.Qt.LeftDockWidgetArea)

        self.tabifyDockWidget(dock_trade_m, dock_error_m)
        self.tabifyDockWidget(dock_trade_m, dock_log_m)
        self.tabifyDockWidget(dock_position_m, dock_account_m)

        dock_trade_m.raise_()
        dock_position_m.raise_()

        # 连接组件之间的信号
        widget_position_m.itemDoubleClicked.connect(widget_trading_w.closePosition)

    # ----------------------------------------------------------------------
    # noinspection PyUnresolvedReferences
    def initMenu(self):
        """初始化菜单"""
        # 创建操作
        connect_ctp_action = QtGui.QAction(u'连接CTP', self)
        connect_ctp_action.triggered.connect(lambda: self.mainEngine.connect('CTP'))

        connect_lts_action = QtGui.QAction(u'连接LTS', self)
        connect_lts_action.triggered.connect(lambda: self.mainEngine.connect('LTS'))

        connect_xtp_action = QtGui.QAction(u'连接XTP', self)
        connect_xtp_action.triggered.connect(lambda: self.mainEngine.connect('XTP'))

        connect_ksotp_action = QtGui.QAction(u'连接金仕达期权', self)
        connect_ksotp_action.triggered.connect(lambda: self.mainEngine.connect('KSOTP'))

        connect_femas_action = QtGui.QAction(u'连接飞马', self)
        connect_femas_action.triggered.connect(lambda: self.mainEngine.connect('FEMAS'))

        connect_xspeed_action = QtGui.QAction(u'连接飞创', self)
        connect_xspeed_action.triggered.connect(lambda: self.mainEngine.connect('XSPEED'))

        connect_ksgold_action = QtGui.QAction(u'连接金仕达黄金', self)
        connect_ksgold_action.triggered.connect(lambda: self.mainEngine.connect('KSGOLD'))

        connect_sgit_action = QtGui.QAction(u'连接飞鼠', self)
        connect_sgit_action.triggered.connect(lambda: self.mainEngine.connect('SGIT'))

        connect_wind_action = QtGui.QAction(u'连接Wind', self)
        connect_wind_action.triggered.connect(lambda: self.mainEngine.connect('Wind'))

        connect_ib_action = QtGui.QAction(u'连接IB', self)
        connect_ib_action.triggered.connect(lambda: self.mainEngine.connect('IB'))

        connect_oanda_action = QtGui.QAction(u'连接OANDA', self)
        connect_oanda_action.triggered.connect(lambda: self.mainEngine.connect('OANDA'))

        connect_okcoin_action = QtGui.QAction(u'连接OKCOIN', self)
        connect_okcoin_action.triggered.connect(lambda: self.mainEngine.connect('OKCOIN'))

        connect_db_action = QtGui.QAction(u'连接数据库', self)
        connect_db_action.triggered.connect(self.mainEngine.dbConnect)

        test_action = QtGui.QAction(u'测试', self)
        test_action.triggered.connect(self.test)

        exit_action = QtGui.QAction(u'退出', self)
        exit_action.triggered.connect(self.close)

        about_action = QtGui.QAction(u'关于', self)
        about_action.triggered.connect(self.openAbout)

        contract_action = QtGui.QAction(u'查询合约', self)
        contract_action.triggered.connect(self.openContract)

        dr_action = QtGui.QAction(u'行情数据记录', self)
        dr_action.triggered.connect(self.openDr)

        cta_action = QtGui.QAction(u'CTA策略', self)
        cta_action.triggered.connect(self.openCta)

        rm_action = QtGui.QAction(u'风险管理', self)
        rm_action.triggered.connect(self.openRm)

        # 创建菜单
        menu_bar = self.menuBar()

        # 设计为只显示存在的接口
        sys_menu = menu_bar.addMenu(u'系统')
        if 'CTP' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_ctp_action)
        if 'LTS' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_lts_action)
        if 'XTP' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_xtp_action)
        if 'FEMAS' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_femas_action)
        if 'XSPEED' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_xspeed_action)
        if 'KSOTP' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_ksotp_action)
        if 'KSGOLD' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_ksgold_action)
        if 'SGIT' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_sgit_action)
        sys_menu.addSeparator()
        if 'IB' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_ib_action)
        if 'OANDA' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_oanda_action)
        if 'OKCOIN' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_okcoin_action)
        sys_menu.addSeparator()
        if 'Wind' in self.mainEngine.gatewayDict:
            sys_menu.addAction(connect_wind_action)
        sys_menu.addSeparator()
        sys_menu.addAction(connect_db_action)
        sys_menu.addSeparator()
        sys_menu.addAction(exit_action)

        function_menu = menu_bar.addMenu(u'功能')
        function_menu.addAction(contract_action)
        function_menu.addAction(dr_action)
        function_menu.addAction(rm_action)

        # 算法相关
        algo_menu = menu_bar.addMenu(u'算法')
        algo_menu.addAction(cta_action)

        # 帮助
        help_menu = menu_bar.addMenu(u'帮助')
        help_menu.addAction(about_action)
        help_menu.addAction(test_action)

    # ----------------------------------------------------------------------
    def initStatusBar(self):
        """初始化状态栏"""
        self.statusLabel = QtGui.QLabel()
        self.statusLabel.setAlignment(QtCore.Qt.AlignLeft)

        self.statusBar().addPermanentWidget(self.statusLabel)
        self.statusLabel.setText(self.getCpuMemory())

        self.sbCount = 0
        self.sbTrigger = 10  # 10秒刷新一次
        self.signalStatusBar.connect(self.updateStatusBar)
        self.eventEngine.register(EVENT_TIMER, self.signalStatusBar.emit)

    # ----------------------------------------------------------------------
    def updateStatusBar(self, event):
        """在状态栏更新CPU和内存信息"""
        self.sbCount += 1

        if self.sbCount == self.sbTrigger:
            self.sbCount = 0
            self.statusLabel.setText(self.getCpuMemory())

    # ----------------------------------------------------------------------
    @staticmethod
    def getCpuMemory():
        """获取CPU和内存状态信息"""
        cpu_percent = psutil.cpu_percent()
        memory_percent = psutil.virtual_memory().percent
        return u'CPU使用率：%d%%   内存使用率：%d%%' % (cpu_percent, memory_percent)

    # ----------------------------------------------------------------------
    @staticmethod
    def test():
        """测试按钮用的函数"""
        # 有需要使用手动触发的测试函数可以写在这里
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

    # ----------------------------------------------------------------------
    def openDr(self):
        """打开行情数据记录组件"""
        try:
            self.widgetDict['drM'].showMaximized()
        except KeyError:
            self.widgetDict['drM'] = DrEngineManager(self.mainEngine.drEngine, self.eventEngine)
            self.widgetDict['drM'].showMaximized()

    # ----------------------------------------------------------------------
    def openRm(self):
        """打开组件"""
        try:
            self.widgetDict['rmM'].show()
        except KeyError:
            self.widgetDict['rmM'] = RmEngineManager(self.mainEngine.rmEngine, self.eventEngine)
            self.widgetDict['rmM'].show()

    # ----------------------------------------------------------------------
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

    # ----------------------------------------------------------------------
    def createDock(self, widget_class, widget_name, widget_area):
        """创建停靠组件"""
        widget = widget_class(self.mainEngine, self.eventEngine)
        dock = QtGui.QDockWidget(widget_name)
        dock.setWidget(widget)
        dock.setObjectName(widget_name)
        dock.setFeatures(dock.DockWidgetFloatable | dock.DockWidgetMovable)
        self.addDockWidget(widget_area, dock)
        return widget, dock

    # ----------------------------------------------------------------------
    def saveWindowSettings(self):
        """保存窗口设置"""
        settings = QtCore.QSettings('vn.py', 'vn.trader')
        settings.setValue('state', self.saveState())
        settings.setValue('geometry', self.saveGeometry())

    # ----------------------------------------------------------------------
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

            GitHub：www.github.com/vnpy/vnpy

            """

        label = QtGui.QLabel()
        label.setText(text)
        label.setMinimumWidth(500)

        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(label)

        self.setLayout(vbox)
