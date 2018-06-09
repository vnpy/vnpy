# encoding: UTF-8

from vnpy.event import Event
from vnpy.trader.uiQt import QtCore, QtWidgets

from .algoEngine import EVENT_ALGO_LOG, EVENT_ALGO_PARAM, EVENT_ALGO_VAR
from .twapAlgo import TwapWidget


########################################################################
class StopButton(QtWidgets.QPushButton):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, algoName=''):
        """Constructor"""
        super(StopButton, self).__init__()
        
        self.algoEngine = algoEngine
        self.algoName = algoName
        
        self.setStyleSheet("color:black;background-color:yellow")
        
        if algoName:
            self.setText(u'停止')
            self.clicked.connect(self.stopAlgo)
        else:
            self.setText(u'全部停止')
            self.clicked.connect(self.stopAll)
    
    #----------------------------------------------------------------------
    def stopAlgo(self):
        """"""
        self.algoEngine.stopAlgo(self.algoName)
        self.disable()
    
    #----------------------------------------------------------------------
    def stopAll(self):
        """"""
        self.algoEngine.stopAll()
    
    #----------------------------------------------------------------------
    def disable(self):
        """"""
        self.setEnabled(False)
        self.setStyleSheet("color:black;background-color:grey")
        


AlgoCell = QtWidgets.QTableWidgetItem


########################################################################
class AlgoStatusMonitor(QtWidgets.QTableWidget):
    """"""
    signalParam = QtCore.Signal(type(Event()))
    signalVar = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, algoEngine):
        """Constructor"""
        super(AlgoStatusMonitor, self).__init__()
        
        self.algoEngine = algoEngine
        self.eventEngine = algoEngine.eventEngine
        
        self.cellDict = {}
        
        self.initUi()
        self.registerEvent()
    
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        labels = [u'',
                  u'名称',
                  u'参数',
                  u'变量']
        
        self.setColumnCount(len(labels))
        self.setHorizontalHeaderLabels(labels)
        self.setRowCount(0)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)   

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signalParam.connect(self.processParamEvent)
        self.signalVar.connect(self.processVarEvent)
        
        self.eventEngine.register(EVENT_ALGO_PARAM, self.signalParam.emit)
        self.eventEngine.register(EVENT_ALGO_VAR, self.signalVar.emit)
    
    #----------------------------------------------------------------------
    def addAlgo(self, algoName):
        """新增算法"""
        self.insertRow(0)
        
        buttonStop = StopButton(self.algoEngine, algoName)
        cellName = AlgoCell(algoName)
        cellParam = AlgoCell()
        cellVar = AlgoCell()
        
        self.setCellWidget(0, 0, buttonStop)
        self.setItem(0, 1, cellName)
        self.setItem(0, 2, cellParam)
        self.setItem(0, 3, cellVar)
        
        self.cellDict[algoName] = {
            'param': cellParam,
            'var': cellVar,
            'button': buttonStop
        }
        
    #----------------------------------------------------------------------
    def processParamEvent(self, event):
        """"""
        d = event.dict_['data']
        
        algoName = d.pop('algoName')
        if algoName not in self.cellDict:
            self.addAlgo(algoName)
        
        l = []
        for k, v in d.items():
            msg = u'%s:%s' %(k, v)
            l.append(msg)
        text = ','.join(l)
        
        cell = self.cellDict[algoName]['param']
        cell.setText(text)

        self.resizeColumnsToContents()
        
    #----------------------------------------------------------------------
    def processVarEvent(self, event):
        """"""
        d = event.dict_['data']
        
        algoName = d.pop('algoName')
        if algoName not in self.cellDict:
            self.addAlgo(algoName)
            
        if 'active' in d:
            active = d.pop('active')
            if not active:
                button = self.cellDict[algoName]['button']
                button.disable()
        
        l = []
        for k, v in d.items():
            msg = u'%s:%s' %(k, v)
            l.append(msg)
        text = ','.join(l)
        
        cell = self.cellDict[algoName]['var']
        cell.setText(text)
        
        self.resizeColumnsToContents()


########################################################################
class AlgoLogMonitor(QtWidgets.QTextEdit):
    """"""
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, algoEngine):
        """Constructor"""
        super(AlgoLogMonitor, self).__init__()
        
        self.eventEngine = algoEngine.eventEngine
        
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.signal.connect(self.processEvent)
        
        self.eventEngine.register(EVENT_ALGO_LOG, self.signal.emit)
        
    #----------------------------------------------------------------------
    def processEvent(self, event):
        """"""
        log = event.dict_['data']
        if not log.gatewayName:
            log.gatewayName = u'算法引擎'
        msg = u'%s\t%s：%s' %(log.logTime, log.gatewayName, log.logContent)
        self.append(msg)



########################################################################
class AlgoManager(QtWidgets.QWidget):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, eventEngine):
        """Constructor"""
        super(AlgoManager, self).__init__()
        
        self.algoEngine = algoEngine
        self.eventEngine = eventEngine
        
        self.initUi()
        self.addAlgoWidget(TwapWidget)
        
    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'算法交易')
        
        self.statusMonitor = AlgoStatusMonitor(self.algoEngine)
        self.logMonitor = AlgoLogMonitor(self.algoEngine)
        self.tab = QtWidgets.QTabWidget()
        self.buttonStop = StopButton(self.algoEngine)
        
        self.tab.setMaximumWidth(400)
        self.buttonStop.setMaximumWidth(400)
        self.buttonStop.setFixedHeight(100)
        
        vbox1 = QtWidgets.QVBoxLayout()
        vbox1.addWidget(self.tab)
        vbox1.addStretch()
        vbox1.addWidget(self.buttonStop)
        
        vbox2 = QtWidgets.QVBoxLayout()
        vbox2.addWidget(self.statusMonitor)
        vbox2.addWidget(self.logMonitor)
        
        hbox = QtWidgets.QHBoxLayout()
        hbox.addLayout(vbox1)
        hbox.addLayout(vbox2)
        
        self.setLayout(hbox)
        
    #----------------------------------------------------------------------
    def addAlgoWidget(self, widgetClass):
        """"""
        w = widgetClass(self.algoEngine)
        self.tab.addTab(w, w.templateName)    