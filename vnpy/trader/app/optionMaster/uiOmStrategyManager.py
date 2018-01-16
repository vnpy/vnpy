# encoding: UTF-8

'''
OM策略引擎的GUI控制组件
'''


from vnpy.event import Event
from vnpy.trader.vtEvent import *
from vnpy.trader.uiBasicWidget import QtGui, QtCore, QtWidgets, BasicCell

from .omBase import EVENT_OM_STRATEGYLOG, EVENT_OM_STRATEGY


########################################################################
class ValueMonitor(QtWidgets.QTableWidget):
    """参数监控"""

    #----------------------------------------------------------------------
    def __init__(self, editable=False, parent=None):
        """Constructor"""
        super(ValueMonitor, self).__init__(parent)
        
        self.keyCellDict = {}
        self.data = None
        self.inited = False
        self.editable = editable
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setRowCount(1)
        self.verticalHeader().setVisible(False)
        
        if not self.editable:
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
                cell.key = k

                self.keyCellDict[k] = cell
                self.setItem(0, col, cell)
                col += 1
            
            self.inited = True
        else:
            for k, v in data.items():
                cell = self.keyCellDict[k]
                cell.setText(unicode(v))
                

########################################################################
class StrategyManager(QtWidgets.QGroupBox):
    """策略管理组件"""
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, engine, eventEngine, name, parent=None):
        """Constructor"""
        super(StrategyManager, self).__init__(parent)
        
        self.engine = engine
        self.eventEngine = eventEngine
        self.name = name
        
        self.initUi()
        self.updateMonitor()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setTitle(self.name)
        
        self.paramMonitor = ValueMonitor(True, self)
        self.varMonitor = ValueMonitor(False, self)
        
        height = 65
        self.paramMonitor.setFixedHeight(height)
        self.varMonitor.setFixedHeight(height)
        
        buttonInit = QtWidgets.QPushButton(u'初始化')
        buttonStart = QtWidgets.QPushButton(u'启动')
        buttonStop = QtWidgets.QPushButton(u'停止')
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
        
        self.paramMonitor.itemChanged.connect(self.setParam)
        
    #----------------------------------------------------------------------
    def updateMonitor(self, event=None):
        """显示策略最新状态"""
        paramDict = self.engine.getStrategyParam(self.name)
        if paramDict:
            self.paramMonitor.updateData(paramDict)
            
        varDict = self.engine.getStrategyVar(self.name)
        if varDict:
            self.varMonitor.updateData(varDict)        
            
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateMonitor)
        self.eventEngine.register(EVENT_OM_STRATEGY+self.name, self.signal.emit)
    
    #----------------------------------------------------------------------
    def init(self):
        """初始化策略"""
        self.engine.initStrategy(self.name)
    
    #----------------------------------------------------------------------
    def start(self):
        """启动策略"""
        self.engine.startStrategy(self.name)
        
    #----------------------------------------------------------------------
    def stop(self):
        """停止策略"""
        self.engine.stopStrategy(self.name)
    
    #----------------------------------------------------------------------
    def setParam(self, cell):
        """更新参数"""
        text = unicode(cell.text())
        key = cell.key
        
        if text.isdigit():
            if '.' in text:
                value = float(text)
            else:
                value = int(text)
        else:
            value = text
        
        self.engine.setStrategyParam(self.name, key, value)


########################################################################
class StrategyEngineManager(QtWidgets.QWidget):
    """引擎管理组件"""
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, omEngine, parent=None):
        """Constructor"""
        super(StrategyEngineManager, self).__init__(parent)
        
        self.engine = omEngine.strategyEngine
        self.eventEngine = omEngine.eventEngine
        
        self.strategyLoaded = False
        
        self.initUi()
        self.registerEvent()
        
        # 记录日志
        self.engine.writeLog(u'期权策略引擎启动')        
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'期权策略')
        
        # 按钮
        loadButton = QtWidgets.QPushButton(u'加载策略')
        initAllButton = QtWidgets.QPushButton(u'全部初始化')
        startAllButton = QtWidgets.QPushButton(u'全部启动')
        stopAllButton = QtWidgets.QPushButton(u'全部停止')
        
        loadButton.clicked.connect(self.load)
        initAllButton.clicked.connect(self.initAll)
        startAllButton.clicked.connect(self.startAll)
        stopAllButton.clicked.connect(self.stopAll)
        
        # 滚动区域，放置所有的StrategyManager
        self.scrollArea = QtWidgets.QScrollArea()
        self.scrollArea.setWidgetResizable(True)
        
        # 日志监控
        self.ctaLogMonitor = QtWidgets.QTextEdit()
        self.ctaLogMonitor.setReadOnly(True)
        self.ctaLogMonitor.setMaximumHeight(200)
        
        # 设置布局
        hbox2 = QtWidgets.QHBoxLayout()
        hbox2.addWidget(loadButton)
        hbox2.addWidget(initAllButton)
        hbox2.addWidget(startAllButton)
        hbox2.addWidget(stopAllButton)
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
        
        for name in self.engine.strategyDict.keys():
            strategyManager = StrategyManager(self.engine, self.eventEngine, name)
            vbox.addWidget(strategyManager)
        
        vbox.addStretch()
        
        w.setLayout(vbox)
        self.scrollArea.setWidget(w)   
        
    #----------------------------------------------------------------------
    def initAll(self):
        """全部初始化"""
        self.engine.initAll()    
            
    #----------------------------------------------------------------------
    def startAll(self):
        """全部启动"""
        self.engine.startAll()
            
    #----------------------------------------------------------------------
    def stopAll(self):
        """全部停止"""
        self.engine.stopAll()
            
    #----------------------------------------------------------------------
    def load(self):
        """加载策略"""
        if not self.strategyLoaded:
            self.engine.loadSetting()
            self.initStrategyManager()
            self.strategyLoaded = True
            self.engine.writeLog(u'策略加载成功')
        
    #----------------------------------------------------------------------
    def updateLog(self, event):
        """更新相关日志"""
        log = event.dict_['data']
        content = '\t'.join([log.logTime, log.logContent])
        self.ctaLogMonitor.append(content)
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateLog)
        self.eventEngine.register(EVENT_OM_STRATEGYLOG, self.signal.emit)

    
    
    
    



    
    