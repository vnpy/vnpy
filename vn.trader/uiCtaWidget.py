# encoding: UTF-8

'''CTA模块相关的GUI控制组件'''

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> refs/remotes/vnpy/master
from uiBasicWidget import QtGui, QtCore, BasicCell
from eventEngine import *


########################################################################
class ValueMonitor(QtGui.QTableWidget):
    """数值监控"""
    signal = QtCore.pyqtSignal()

    #----------------------------------------------------------------------
    def __init__(self, parent=None):
        """Constructor"""
        super(ValueMonitor , self).__init__(parent)
        
        self.keyCellDict = {}
        self.row = 0
        self.data = None
        
        self.initUi()
        self.signal.connect(self.updateTable)
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setColumnCount(2)
        
        self.verticalHeader().setVisible(False)        
        self.horizontalHeader().setVisible(False)
        
        self.setEditTriggers(self.NoEditTriggers)
        self.setAlternatingRowColors(True)
        
    #----------------------------------------------------------------------
    def updateData(self, data):
        """更新数据"""
        self.data = data
        self.signal.emit()
        
    #----------------------------------------------------------------------
    def updateTable(self):
        """更新表格"""
        for key, value in self.data.items():
            if key in self.keyCellDict:
                cell = self.keyCellDict[key]
                cell.setText(unicode(value))
            else:
                # 创建并保存单元格
                keyCell = BasicCell(unicode(key))
                cell = BasicCell(unicode(value))
                self.keyCellDict[key] = cell
                
                # 移动到下一行
                self.insertRow(self.row)
                self.setItem(self.row, 0, keyCell)
                self.setItem(self.row, 1, cell)
                self.row += 1


########################################################################
class CtaStrategyManager(QtGui.QGroupBox):
    """策略管理组件"""

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
        
        paramLabel = QtGui.QLabel(u'参数')
        varLabel = QtGui.QLabel(u'变量')
        
        self.paramMonitor = ValueMonitor(self)
        self.varMonitor = ValueMonitor(self)
        
        buttonStart = QtGui.QPushButton(u'启动')
        buttonStop = QtGui.QPushButton(u'停止')
        buttonStart.clicked.connect(self.start)
        buttonStop.clicked.connect(self.stop)
        
        hbox = QtGui.QHBoxLayout()        
        hbox.addWidget(buttonStart)
        hbox.addWidget(buttonStop)
        hbox.addStretch()
        
        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(paramLabel)
        vbox.addWidget(self.paramMonitor)
        vbox.addWidget(varLabel)
        vbox.addWidget(self.varMonitor)
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
        self.eventEngine.register(EVENT_TIMER, self.updateMonitor)
    
    #----------------------------------------------------------------------
    def start(self):
        """启动策略"""
        self.ctaEngine.startStrategy(self.name)
        
    #----------------------------------------------------------------------
    def stop(self):
        """停止策略"""
        self.ctaEngine.stopStrategy(self.name)



########################################################################
class CtaEngineManager(QtGui.QWidget):
    """CTA引擎管理组件"""
    signal = QtCore.pyqtSignal(type(Event()))

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
        self.ctaEngine.writeCtaLog(u'CTA引擎启动成功')        
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'CTA策略')
        
        # 按钮
        loadButton = QtGui.QPushButton(u'加载策略')
        startAllButton = QtGui.QPushButton(u'全部启动')
        stopAllButton = QtGui.QPushButton(u'全部停止')
        
        loadButton.clicked.connect(self.load)
        startAllButton.clicked.connect(self.startAll)
        stopAllButton.clicked.connect(self.stopAll)
        
        # 滚动区域，放置所有的CtaStrategyManager
        self.scrollArea = QtGui.QScrollArea()
        
        # CTA组件的日志监控
        self.ctaLogMonitor = QtGui.QTextEdit()
        self.ctaLogMonitor.setReadOnly(True)
        
        # 设置布局
        hbox2 = QtGui.QHBoxLayout()
        hbox2.addWidget(loadButton)
        hbox2.addWidget(startAllButton)
        hbox2.addWidget(stopAllButton)
        hbox2.addStretch()
        
        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(hbox2)
        vbox.addWidget(self.scrollArea)
        vbox.addWidget(self.ctaLogMonitor)
        self.setLayout(vbox)
        
    #----------------------------------------------------------------------
    def initStrategyManager(self):
        """初始化策略管理组件界面"""        
        w = QtGui.QWidget()
        hbox = QtGui.QHBoxLayout()
        
        for name in self.ctaEngine.strategyDict.keys():
            strategyManager = CtaStrategyManager(self.ctaEngine, self.eventEngine, name)
            hbox.addWidget(strategyManager)
        
        w.setLayout(hbox)
        self.scrollArea.setWidget(w)        
            
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
            self.ctaEngine.loadStrategySetting()
            self.initStrategyManager()
            self.strategyLoaded = True
            self.ctaEngine.writeCtaLog(u'策略加载成功')
        
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
        
        
    
    
    
    



    
<<<<<<< HEAD
    
>>>>>>> refs/remotes/vnpy/master
=======
    
>>>>>>> refs/remotes/vnpy/master
