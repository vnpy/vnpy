# -*- coding: utf-8 -*-

"""
CTA模块相关的GUI控制组件
"""

from vnpy.engine.uiBasicWidget import QtGui, QtCore
from vnpy.event.eventEngine import Event, EVENT_CTA_STRATEGY, EVENT_CTA_LOG


########################################################################
class CtaValueMonitor(QtGui.QTableWidget):
    """参数监控"""

    # ----------------------------------------------------------------------
    def __init__(self, parent=None):
        """Constructor"""
        super(CtaValueMonitor, self).__init__(parent)

        self.keyCellDict = {}
        self.data = None
        self.inited = False

        self.initUi()

    # ----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setRowCount(1)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)

        self.setMaximumHeight(self.sizeHint().height())

    # ----------------------------------------------------------------------
    def updateData(self, data):
        """更新数据"""
        if not self.inited:
            self.setColumnCount(len(data))
            self.setHorizontalHeaderLabels(data.keys())

            col = 0
            for k, v in data.items():
                cell = QtGui.QTableWidgetItem(unicode(v))
                self.keyCellDict[k] = cell
                self.setItem(0, col, cell)
                col += 1

            self.inited = True
        else:
            for k, v in data.items():
                cell = self.keyCellDict[k]
                cell.setText(unicode(v))


########################################################################
class CtaStrategyManager(QtGui.QGroupBox):
    """策略管理组件"""
    signal = QtCore.pyqtSignal(type(Event()))

    # ----------------------------------------------------------------------
    def __init__(self, cta_engine, event_engine, name, parent=None):
        """Constructor"""
        super(CtaStrategyManager, self).__init__(parent)

        self.ctaEngine = cta_engine
        self.eventEngine = event_engine
        self.name = name

        self.initUi()
        self.updateMonitor()
        self.registerEvent()

    # ----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setTitle(self.name)

        self.paramMonitor = CtaValueMonitor(self)
        self.varMonitor = CtaValueMonitor(self)

        max_height = 60
        self.paramMonitor.setMaximumHeight(max_height)
        self.varMonitor.setMaximumHeight(max_height)

        button_init = QtGui.QPushButton(u'初始化')
        button_start = QtGui.QPushButton(u'启动')
        button_stop = QtGui.QPushButton(u'停止')
        button_init.clicked.connect(self.init)
        button_start.clicked.connect(self.start)
        button_stop.clicked.connect(self.stop)

        hbox1 = QtGui.QHBoxLayout()
        hbox1.addWidget(button_init)
        hbox1.addWidget(button_start)
        hbox1.addWidget(button_stop)
        hbox1.addStretch()

        hbox2 = QtGui.QHBoxLayout()
        hbox2.addWidget(self.paramMonitor)

        hbox3 = QtGui.QHBoxLayout()
        hbox3.addWidget(self.varMonitor)

        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(hbox1)
        vbox.addLayout(hbox2)
        vbox.addLayout(hbox3)

        self.setLayout(vbox)

    # ----------------------------------------------------------------------
    def updateMonitor(self, event=None):
        """显示策略最新状态"""
        param_dict = self.ctaEngine.getStrategyParam(self.name)
        if param_dict:
            self.paramMonitor.updateData(param_dict)

        var_dict = self.ctaEngine.getStrategyVar(self.name)
        if var_dict:
            self.varMonitor.updateData(var_dict)

    # ----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateMonitor)
        self.eventEngine.register(EVENT_CTA_STRATEGY + self.name, self.signal.emit)

    # ----------------------------------------------------------------------
    def init(self):
        """初始化策略"""
        self.ctaEngine.initStrategy(self.name)

    # ----------------------------------------------------------------------
    def start(self):
        """启动策略"""
        self.ctaEngine.startStrategy(self.name)

    # ----------------------------------------------------------------------
    def stop(self):
        """停止策略"""
        self.ctaEngine.stopStrategy(self.name)


########################################################################
class CtaEngineManager(QtGui.QWidget):
    """CTA引擎管理组件"""
    signal = QtCore.pyqtSignal(type(Event()))

    # ----------------------------------------------------------------------
    def __init__(self, cta_engine, event_engine, parent=None):
        """Constructor"""
        super(CtaEngineManager, self).__init__(parent)

        self.ctaEngine = cta_engine
        self.eventEngine = event_engine

        self.strategyLoaded = False

        self.initUi()
        self.registerEvent()

        # 记录日志
        self.ctaEngine.writeCtaLog(u'CTA引擎启动成功')

    # ----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'CTA策略')

        # 按钮
        load_button = QtGui.QPushButton(u'加载策略')
        init_all_button = QtGui.QPushButton(u'全部初始化')
        start_all_button = QtGui.QPushButton(u'全部启动')
        stop_all_button = QtGui.QPushButton(u'全部停止')

        load_button.clicked.connect(self.load)
        init_all_button.clicked.connect(self.initAll)
        start_all_button.clicked.connect(self.startAll)
        stop_all_button.clicked.connect(self.stopAll)

        # 滚动区域，放置所有的CtaStrategyManager
        self.scrollArea = QtGui.QScrollArea()
        self.scrollArea.setWidgetResizable(True)

        # CTA组件的日志监控
        self.ctaLogMonitor = QtGui.QTextEdit()
        self.ctaLogMonitor.setReadOnly(True)
        self.ctaLogMonitor.setMaximumHeight(200)

        # 设置布局
        hbox2 = QtGui.QHBoxLayout()
        hbox2.addWidget(load_button)
        hbox2.addWidget(init_all_button)
        hbox2.addWidget(start_all_button)
        hbox2.addWidget(stop_all_button)
        hbox2.addStretch()

        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(hbox2)
        vbox.addWidget(self.scrollArea)
        vbox.addWidget(self.ctaLogMonitor)
        self.setLayout(vbox)

    # ----------------------------------------------------------------------
    def initStrategyManager(self):
        """初始化策略管理组件界面"""
        w = QtGui.QWidget()
        vbox = QtGui.QVBoxLayout()

        for name in self.ctaEngine.strategyDict.keys():
            strategy_manager = CtaStrategyManager(self.ctaEngine, self.eventEngine, name)
            vbox.addWidget(strategy_manager)

        vbox.addStretch()

        w.setLayout(vbox)
        self.scrollArea.setWidget(w)

    # ----------------------------------------------------------------------
    def initAll(self):
        """全部初始化"""
        for name in self.ctaEngine.strategyDict.keys():
            self.ctaEngine.initStrategy(name)

    # ----------------------------------------------------------------------
    def startAll(self):
        """全部启动"""
        for name in self.ctaEngine.strategyDict.keys():
            self.ctaEngine.startStrategy(name)

    # ----------------------------------------------------------------------
    def stopAll(self):
        """全部停止"""
        for name in self.ctaEngine.strategyDict.keys():
            self.ctaEngine.stopStrategy(name)

    # ----------------------------------------------------------------------
    def load(self):
        """加载策略"""
        if not self.strategyLoaded:
            self.ctaEngine.loadSetting()
            self.initStrategyManager()
            self.strategyLoaded = True
            self.ctaEngine.writeCtaLog(u'策略加载成功')

    # ----------------------------------------------------------------------
    def updateCtaLog(self, event):
        """更新CTA相关日志"""
        log = event.dict_['data']
        content = '\t'.join([log.logTime, log.logContent])
        self.ctaLogMonitor.append(content)

    # ----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateCtaLog)
        self.eventEngine.register(EVENT_CTA_LOG, self.signal.emit)
