# encoding: UTF-8

'''
CTA模块相关的GUI控制组件
'''


from vnpy.event import Event
from vnpy.trader.vtEvent import *
from vnpy.trader.uiBasicWidget import QtGui, QtCore, QtWidgets, BasicCell

from vnpy.trader.app.ctaStrategy.language import text


########################################################################
class CtaValueMonitor(QtWidgets.QTableWidget):
    """参数监控"""

    #----------------------------------------------------------------------
    def __init__(self, parent=None):
        """Constructor"""
        super(CtaValueMonitor, self).__init__(parent)
        
        self.keyCellDict = {}
        self.data = None
        self.inited = False
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setRowCount(1)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
        
        self.setMaximumHeight(self.sizeHint().height())
        
    #----------------------------------------------------------------------
    def updateData(self, data):
        """更新数据"""
        if not self.inited:
            self.setColumnCount(len(data))
            self.setHorizontalHeaderLabels(data.keys())
            
            col = 0
            for k, v in data.items():
                cell = QtWidgets.QTableWidgetItem(unicode(v))
                self.keyCellDict[k] = cell
                self.setItem(0, col, cell)
                col += 1
            
            self.inited = True
        else:
            for k, v in data.items():
                cell = self.keyCellDict[k]
                cell.setText(unicode(v))


########################################################################
class CtaStrategyManager(QtWidgets.QGroupBox):
    """策略管理组件"""
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, ctaEngine, eventEngine, name, parent=None):
        """Constructor"""
        super(CtaStrategyManager, self).__init__(parent)
        
        self.ctaEngine = ctaEngine
        self.eventEngine = eventEngine
        self.name = name
        
        self.initUi()
        self.updateMonitor()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setTitle(self.name)
        
        self.paramMonitor = CtaValueMonitor(self)
        self.varMonitor = CtaValueMonitor(self)
        
        height = 65
        self.paramMonitor.setFixedHeight(height)
        self.varMonitor.setFixedHeight(height)
        
        buttonInit = QtWidgets.QPushButton(text.INIT)
        buttonStart = QtWidgets.QPushButton(text.START)
        buttonStop = QtWidgets.QPushButton(text.STOP)
        buttonInit.clicked.connect(self.init)
        buttonStart.clicked.connect(self.start)
        buttonStop.clicked.connect(self.stop)
        
        hbox1 = QtWidgets.QHBoxLayout()     
        hbox1.addWidget(buttonInit)
        hbox1.addWidget(buttonStart)
        hbox1.addWidget(buttonStop)
        hbox1.addStretch()
        
        hbox2 = QtWidgets.QHBoxLayout()
        hbox2.addWidget(self.paramMonitor)
        
        hbox3 = QtWidgets.QHBoxLayout()
        hbox3.addWidget(self.varMonitor)
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox1)
        vbox.addLayout(hbox2)
        vbox.addLayout(hbox3)

        self.setLayout(vbox)
        
    #----------------------------------------------------------------------
    def updateMonitor(self, event=None):
        """显示策略最新状态"""
        paramDict = self.ctaEngine.getStrategyParam(self.name)
        if paramDict:
            self.paramMonitor.updateData(paramDict)
            
        varDict = self.ctaEngine.getStrategyVar(self.name)
        if varDict:
            self.varMonitor.updateData(varDict)        
            
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateMonitor)
        self.eventEngine.register(EVENT_CTA_STRATEGY+self.name, self.signal.emit)
    
    #----------------------------------------------------------------------
    def init(self):
        """初始化策略"""
        self.ctaEngine.initStrategy(self.name)
    
    #----------------------------------------------------------------------
    def start(self):
        """启动策略"""
        self.ctaEngine.startStrategy(self.name)
        
    #----------------------------------------------------------------------
    def stop(self):
        """停止策略"""
        self.ctaEngine.stopStrategy(self.name)


########################################################################
class CtaEngineManager(QtWidgets.QWidget):
    """CTA引擎管理组件"""
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, ctaEngine, eventEngine, parent=None):
        """Constructor"""
        super(CtaEngineManager, self).__init__(parent)
        
        self.ctaEngine = ctaEngine
        self.eventEngine = eventEngine
        
        self.strategyLoaded = False
        
        self.initUi()
        self.registerEvent()
        
        # 记录日志
        self.ctaEngine.writeCtaLog(text.CTA_ENGINE_STARTED)        
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(text.CTA_STRATEGY)
        
        # 按钮
        loadButton = QtWidgets.QPushButton(text.LOAD_STRATEGY)
        initAllButton = QtWidgets.QPushButton(text.INIT_ALL)
        startAllButton = QtWidgets.QPushButton(text.START_ALL)
        stopAllButton = QtWidgets.QPushButton(text.STOP_ALL)
        savePositionButton = QtWidgets.QPushButton(text.SAVE_POSITION_DATA)
        
        loadButton.clicked.connect(self.load)
        initAllButton.clicked.connect(self.initAll)
        startAllButton.clicked.connect(self.startAll)
        stopAllButton.clicked.connect(self.stopAll)
        savePositionButton.clicked.connect(self.ctaEngine.savePosition)
        
        # 滚动区域，放置所有的CtaStrategyManager
        self.scrollArea = QtWidgets.QScrollArea()
        self.scrollArea.setWidgetResizable(True)
        
        # CTA组件的日志监控
        self.ctaLogMonitor = QtWidgets.QTextEdit()
        self.ctaLogMonitor.setReadOnly(True)
        self.ctaLogMonitor.setMaximumHeight(200)
        
        # 设置布局
        hbox2 = QtWidgets.QHBoxLayout()
        hbox2.addWidget(loadButton)
        hbox2.addWidget(initAllButton)
        hbox2.addWidget(startAllButton)
        hbox2.addWidget(stopAllButton)
        hbox2.addWidget(savePositionButton)
        hbox2.addStretch()
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox2)
        vbox.addWidget(self.scrollArea)
        vbox.addWidget(self.ctaLogMonitor)
        self.setLayout(vbox)
        
    #----------------------------------------------------------------------
    def initStrategyManager(self):
        """初始化策略管理组件界面"""        
        w = QtWidgets.QWidget()
        vbox = QtWidgets.QVBoxLayout()
        
        for name in self.ctaEngine.strategyDict.keys():
            strategyManager = CtaStrategyManager(self.ctaEngine, self.eventEngine, name)
            vbox.addWidget(strategyManager)
        
        vbox.addStretch()
        
        w.setLayout(vbox)
        self.scrollArea.setWidget(w)   
        
    #----------------------------------------------------------------------
    def initAll(self):
        """全部初始化"""
        for name in self.ctaEngine.strategyDict.keys():
            self.ctaEngine.initStrategy(name)    
            
    #----------------------------------------------------------------------
    def startAll(self):
        """全部启动"""
        for name in self.ctaEngine.strategyDict.keys():
            self.ctaEngine.startStrategy(name)
            
    #----------------------------------------------------------------------
    def stopAll(self):
        """全部停止"""
        for name in self.ctaEngine.strategyDict.keys():
            self.ctaEngine.stopStrategy(name)
            
    #----------------------------------------------------------------------
    def load(self):
        """加载策略"""
        if not self.strategyLoaded:
            self.ctaEngine.loadSetting()
            self.initStrategyManager()
            self.strategyLoaded = True
            self.ctaEngine.writeCtaLog(text.STRATEGY_LOADED)
        
    #----------------------------------------------------------------------
    def updateCtaLog(self, event):
        """更新CTA相关日志"""
        log = event.dict_['data']
        content = '\t'.join([log.logTime, log.logContent])
        self.ctaLogMonitor.append(content)
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateCtaLog)
        self.eventEngine.register(EVENT_CTA_LOG, self.signal.emit)
        
    #----------------------------------------------------------------------
    def closeEvent(self, event):
        """关闭窗口时的事件"""
        reply = QtWidgets.QMessageBox.question(self, text.SAVE_POSITION_DATA,
                                           text.SAVE_POSITION_QUESTION, QtWidgets.QMessageBox.Yes | 
                                           QtWidgets.QMessageBox.No, QtWidgets.QMessageBox.No)
    
        if reply == QtWidgets.QMessageBox.Yes: 
            self.ctaEngine.savePosition()
            
        event.accept()
        
        
    
    
    
    



    
    