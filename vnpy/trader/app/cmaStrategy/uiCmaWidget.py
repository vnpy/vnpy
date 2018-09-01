# encoding: UTF-8

'''
CMA模块相关的GUI控制组件
'''


import os
from time import sleep
import traceback

from vnpy.trader.app.cmaStrategy.language import text
from vnpy.trader.uiBasicWidget import QtWidgets, QtGui, QtCore, BasicCell
from vnpy.trader.vtEvent import *
from vnpy.trader.app.cmaStrategy.strategy import *

########################################################################
class CmaValueMonitor(QtWidgets.QTableWidget):
    """参数监控"""

    #----------------------------------------------------------------------
    def __init__(self, parent=None):
        """Constructor"""
        super(CmaValueMonitor, self).__init__(parent)

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
            # 设置标题

            self.setColumnCount(len(data))
            self.setHorizontalHeaderLabels(data.keys())

            # 新增数据
            col = 0
            for k, v in data.items():
                cell = QtWidgets.QTableWidgetItem(v)
                self.keyCellDict[k] = cell
                self.setItem(0, col, cell)
                col += 1
            
            self.inited = True
        else:
            # 更新数据
            for k, v in data.items():
                cell = self.keyCellDict[k]
                cell.setText(str(v))

        #cell.setBackgroundColor()

        # 调整表格宽度为自适应
        self.resizeColumnsToContents()
        self.resizeRowsToContents()

########################################################################
class CmaStrategyManager(QtWidgets.QGroupBox):
    """策略管理组件"""
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, cmaEngine, eventEngine, name, parent=None):
        """Constructor"""
        super(CmaStrategyManager, self).__init__(parent)
        
        self.cmaEngine = cmaEngine
        self.eventEngine = eventEngine
        self.name = name
        
        self.initUi()
        self.updateMonitor()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setTitle(self.name)
        
        self.paramMonitor = CmaValueMonitor(self)           # 参数监控
        self.varMonitor = CmaValueMonitor(self)             # 变量监控
        
        height = 80
        self.paramMonitor.setFixedHeight(height)
        self.varMonitor.setFixedHeight(height)

        buttonInit = QtWidgets.QPushButton(text.INIT)
        buttonStart = QtWidgets.QPushButton(text.START)
        buttonStop = QtWidgets.QPushButton(text.STOP)
        buttonInitForce = QtWidgets.QPushButton(text.FORCEINIT)
        buttonInit.clicked.connect(self.init)
        buttonStart.clicked.connect(self.start)
        buttonStop.clicked.connect(self.stop)
        buttonInitForce.clicked.connect(self.initForce)
        
        hbox1 = QtWidgets.QHBoxLayout()
        hbox1.addWidget(buttonInit)
        hbox1.addWidget(buttonStart)
        hbox1.addWidget(buttonStop)
        hbox1.addWidget(buttonInitForce)

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

        # 获取策略的参数目录
        paramDict = self.cmaEngine.getStrategyParam(self.name)
        if paramDict:
            self.paramMonitor.updateData(paramDict)

        # 获取策略的变量目录
        varDict = self.cmaEngine.getStrategyVar(self.name)
        if varDict:
            self.varMonitor.updateData(varDict)        
            
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""

        # 绑定事件的更新函数为updateMonitor
        self.signal.connect(self.updateMonitor)

        # 注册事件
        self.eventEngine.register(EVENT_CTA_STRATEGY+self.name, self.signal.emit)
    
    #----------------------------------------------------------------------
    def init(self):
        """初始化策略"""
        self.cmaEngine.initStrategy(self.name)

    def initForce(self):
        """强制初始化策略"""
        self.cmaEngine.initStrategy(self.name, force = True)

    #----------------------------------------------------------------------
    def start(self):
        """启动策略"""
        self.cmaEngine.startStrategy(self.name)
        
    #----------------------------------------------------------------------
    def stop(self):
        """停止策略"""
        self.cmaEngine.stopStrategy(self.name)


########################################################################
class CmaEngineManager(QtWidgets.QWidget):
    """CTA引擎管理组件"""
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, cmaEngine, eventEngine, parent=None):
        """Constructor"""
        super(CmaEngineManager, self).__init__(parent)
        
        self.cmaEngine = cmaEngine
        self.eventEngine = eventEngine
        
        self.strategyLoaded = False
        
        self.initUi()
        self.registerEvent()
        
        # 记录日志
        self.cmaEngine.writeCtaLog(text.CMA_ENGINE_STARTED)
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'Cross Market Arbitrage')
        
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

        # 滚动区域，放置所有的CtaStrategyManager
        self.scrollArea = QtWidgets.QScrollArea()
        self.scrollArea.setWidgetResizable(True)
        
        # CTA组件的日志监控
        self.cmaLogMonitor = QtWidgets.QTextEdit()
        self.cmaLogMonitor.setReadOnly(True)
        self.cmaLogMonitor.setMaximumHeight(200)
        
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
        vbox.addWidget(self.cmaLogMonitor)
        self.setLayout(vbox)
        
    # ----------------------------------------------------------------------
    def initStrategyManager(self):
        """初始化策略管理组件界面"""        
        w = QtWidgets.QWidget()
        vbox = QtWidgets.QVBoxLayout()
        
        for name in self.cmaEngine.strategyDict.keys():
            # 为每一个策略实例，创建对应的管理组件实例
            strategyManager = CmaStrategyManager(self.cmaEngine, self.eventEngine, name)
            vbox.addWidget(strategyManager)
            sleep(0.2)
        
        vbox.addStretch()
        
        w.setLayout(vbox)
        self.scrollArea.setWidget(w)   
        
    # ----------------------------------------------------------------------
    def initAll(self):
        """全部初始化"""
        for name in self.cmaEngine.strategyDict.keys():
            self.cmaEngine.initStrategy(name)
            
    # ----------------------------------------------------------------------
    def startAll(self):
        """全部启动"""
        for name in self.cmaEngine.strategyDict.keys():
            self.cmaEngine.startStrategy(name)
            
    # ----------------------------------------------------------------------
    def stopAll(self):
        """全部停止"""
        for name in self.cmaEngine.strategyDict.keys():
            self.cmaEngine.stopStrategy(name)
            
    # ----------------------------------------------------------------------
    def load(self):
        """加载策略"""
        if not self.strategyLoaded:
            try:
                self.cmaEngine.loadSetting()
                self.initStrategyManager()
                self.strategyLoaded = True
                self.cmaEngine.writeCtaLog(text.STRATEGY_LOADED)
            except Exception as ex:
                self.cmaEngine.writeCtaError(str(ex))
                traceback.print_exc()
        
    # ----------------------------------------------------------------------
    def updateCtaLog(self, event):
        """更新CTA相关日志"""
        log = event.dict_['data']
        content = '\t'.join([log.logTime, log.logContent])
        self.cmaLogMonitor.append(content)
    
    # ----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateCtaLog)
        self.eventEngine.register(EVENT_CTA_LOG, self.signal.emit)









