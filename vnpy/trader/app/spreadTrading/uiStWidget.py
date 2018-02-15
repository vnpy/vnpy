# encoding: UTF-8

from collections import OrderedDict

from vnpy.event import Event
from vnpy.trader.uiQt import QtWidgets, QtCore
from vnpy.trader.uiBasicWidget import (BasicMonitor, BasicCell, PnlCell,
                                       AskCell, BidCell, BASIC_FONT)

from .stBase import (EVENT_SPREADTRADING_TICK, EVENT_SPREADTRADING_POS,
                     EVENT_SPREADTRADING_LOG, EVENT_SPREADTRADING_ALGO,
                     EVENT_SPREADTRADING_ALGOLOG)
from .stAlgo import StAlgoTemplate


STYLESHEET_START = 'background-color: rgb(111,255,244); color: black'
STYLESHEET_STOP = 'background-color: rgb(255,201,111); color: black'


########################################################################
class StTickMonitor(BasicMonitor):
    """价差行情监控"""
    
    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(StTickMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        d = OrderedDict()
        d['name'] = {'chinese':u'价差名称', 'cellType':BasicCell}
        d['bidPrice'] = {'chinese':u'买价', 'cellType':BidCell}
        d['bidVolume'] = {'chinese':u'买量', 'cellType':BidCell}
        d['askPrice'] = {'chinese':u'卖价', 'cellType':AskCell}
        d['askVolume'] = {'chinese':u'卖量', 'cellType':AskCell}
        d['time'] = {'chinese':u'时间', 'cellType':BasicCell}
        d['symbol'] = {'chinese':u'价差公式', 'cellType':BasicCell}
        self.setHeaderDict(d)
    
        self.setDataKey('name')
        self.setEventType(EVENT_SPREADTRADING_TICK)
        self.setFont(BASIC_FONT)
    
        self.initTable()
        self.registerEvent()        


########################################################################
class StPosMonitor(BasicMonitor):
    """价差持仓监控"""
    
    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(StPosMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        d = OrderedDict()
        d['name'] = {'chinese':u'价差名称', 'cellType':BasicCell}
        d['netPos'] = {'chinese':u'净仓', 'cellType':PnlCell}
        d['longPos'] = {'chinese':u'多仓', 'cellType':BasicCell}
        d['shortPos'] = {'chinese':u'空仓', 'cellType':BasicCell}
        d['symbol'] = {'chinese':u'代码', 'cellType':BasicCell}
        self.setHeaderDict(d)
    
        self.setDataKey('name')
        self.setEventType(EVENT_SPREADTRADING_POS)
        self.setFont(BASIC_FONT)
    
        self.initTable()
        self.registerEvent()        


########################################################################
class StLogMonitor(QtWidgets.QTextEdit):
    """价差日志监控"""
    signal = QtCore.Signal(type(Event()))
    
    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(StLogMonitor, self).__init__(parent)
        
        self.eventEngine = eventEngine
        
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def processLogEvent(self, event):
        """处理日志事件"""
        log = event.dict_['data']
        content = '%s:%s' %(log.logTime, log.logContent)
        self.append(content)
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.processLogEvent)
        
        self.eventEngine.register(EVENT_SPREADTRADING_LOG, self.signal.emit)


########################################################################
class StAlgoLogMonitor(BasicMonitor):
    """价差日志监控"""
    
    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(StAlgoLogMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        d = OrderedDict()
        d['logTime'] = {'chinese':u'时间', 'cellType':BasicCell}
        d['logContent'] = {'chinese':u'信息', 'cellType':BasicCell}
        self.setHeaderDict(d)
    
        self.setEventType(EVENT_SPREADTRADING_ALGOLOG)
        self.setFont(BASIC_FONT)
    
        self.initTable()
        self.registerEvent()
        

########################################################################
class StBuyPriceSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, price, parent=None):
        """Constructor"""
        super(StBuyPriceSpinBox, self).__init__(parent)
        
        self.algoEngine = algoEngine
        self.spreadName = spreadName
        
        self.setDecimals(4)
        self.setRange(-10000, 10000)
        self.setValue(price)
        
        self.valueChanged.connect(self.setPrice)
        
    #----------------------------------------------------------------------
    def setPrice(self, value):
        """设置价格"""
        self.algoEngine.setAlgoBuyPrice(self.spreadName, value)
   
    #----------------------------------------------------------------------
    def algoActiveChanged(self, active):
        """算法运行状态改变"""
        # 只允许算法停止时修改运行模式
        if active:
            self.setEnabled(False)
        else:
            self.setEnabled(True)    


########################################################################
class StSellPriceSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, price, parent=None):
        """Constructor"""
        super(StSellPriceSpinBox, self).__init__(parent)
        
        self.algoEngine = algoEngine
        self.spreadName = spreadName
        
        self.setDecimals(4)
        self.setRange(-10000, 10000)
        self.setValue(price)
        
        self.valueChanged.connect(self.setPrice)
        
    #----------------------------------------------------------------------
    def setPrice(self, value):
        """设置价格"""
        self.algoEngine.setAlgoSellPrice(self.spreadName, value)
    
    #----------------------------------------------------------------------
    def algoActiveChanged(self, active):
        """算法运行状态改变"""
        # 只允许算法停止时修改运行模式
        if active:
            self.setEnabled(False)
        else:
            self.setEnabled(True)


########################################################################
class StShortPriceSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, price, parent=None):
        """Constructor"""
        super(StShortPriceSpinBox, self).__init__(parent)
        
        self.algoEngine = algoEngine
        self.spreadName = spreadName
        
        self.setDecimals(4)
        self.setRange(-10000, 10000)
        self.setValue(price)
        
        self.valueChanged.connect(self.setPrice)
        
    #----------------------------------------------------------------------
    def setPrice(self, value):
        """设置价格"""
        self.algoEngine.setAlgoShortPrice(self.spreadName, value)

    #----------------------------------------------------------------------
    def algoActiveChanged(self, active):
        """算法运行状态改变"""
        # 只允许算法停止时修改运行模式
        if active:
            self.setEnabled(False)
        else:
            self.setEnabled(True)


########################################################################
class StCoverPriceSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, price, parent=None):
        """Constructor"""
        super(StCoverPriceSpinBox, self).__init__(parent)
        
        self.algoEngine = algoEngine
        self.spreadName = spreadName
        
        self.setDecimals(4)
        self.setRange(-10000, 10000)
        self.setValue(price)
        
        self.valueChanged.connect(self.setPrice)
        
    #----------------------------------------------------------------------
    def setPrice(self, value):
        """设置价格"""
        self.algoEngine.setAlgoCoverPrice(self.spreadName, value)
    
    #----------------------------------------------------------------------
    def algoActiveChanged(self, active):
        """算法运行状态改变"""
        # 只允许算法停止时修改运行模式
        if active:
            self.setEnabled(False)
        else:
            self.setEnabled(True)    


########################################################################
class StMaxPosSizeSpinBox(QtWidgets.QSpinBox):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, size, parent=None):
        """Constructor"""
        super(StMaxPosSizeSpinBox, self).__init__(parent)
        
        self.algoEngine = algoEngine
        self.spreadName = spreadName
        
        self.setRange(-10000, 10000)
        self.setValue(size)
        
        self.valueChanged.connect(self.setSize)
        
    #----------------------------------------------------------------------
    def setSize(self, size):
        """设置价格"""
        self.algoEngine.setAlgoMaxPosSize(self.spreadName, size)

    #----------------------------------------------------------------------
    def algoActiveChanged(self, active):
        """算法运行状态改变"""
        # 只允许算法停止时修改运行模式
        if active:
            self.setEnabled(False)
        else:
            self.setEnabled(True)
            
            
########################################################################
class StMaxOrderSizeSpinBox(QtWidgets.QSpinBox):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, size, parent=None):
        """Constructor"""
        super(StMaxOrderSizeSpinBox, self).__init__(parent)
        
        self.algoEngine = algoEngine
        self.spreadName = spreadName
        
        self.setRange(-10000, 10000)
        self.setValue(size)
        
        self.valueChanged.connect(self.setSize)
        
    #----------------------------------------------------------------------
    def setSize(self, size):
        """设置价格"""
        self.algoEngine.setAlgoMaxOrderSize(self.spreadName, size)    

    #----------------------------------------------------------------------
    def algoActiveChanged(self, active):
        """算法运行状态改变"""
        # 只允许算法停止时修改运行模式
        if active:
            self.setEnabled(False)
        else:
            self.setEnabled(True)


########################################################################
class StModeComboBox(QtWidgets.QComboBox):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, mode, parent=None):
        """Constructor"""
        super(StModeComboBox, self).__init__(parent)
        
        self.algoEngine = algoEngine
        self.spreadName = spreadName
        
        l = [StAlgoTemplate.MODE_LONGSHORT, 
             StAlgoTemplate.MODE_LONGONLY,
             StAlgoTemplate.MODE_SHORTONLY]
        self.addItems(l)
        self.setCurrentIndex(l.index(mode))
        
        self.currentIndexChanged.connect(self.setMode)
        
    #----------------------------------------------------------------------
    def setMode(self):
        """设置模式"""
        mode = unicode(self.currentText())
        self.algoEngine.setAlgoMode(self.spreadName, mode)
    
    #----------------------------------------------------------------------
    def algoActiveChanged(self, active):
        """算法运行状态改变"""
        # 只允许算法停止时修改运行模式
        if active:
            self.setEnabled(False)
        else:
            self.setEnabled(True)


########################################################################
class StActiveButton(QtWidgets.QPushButton):
    """"""
    signalActive = QtCore.Signal(bool)

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, parent=None):
        """Constructor"""
        super(StActiveButton, self).__init__(parent)
        
        self.algoEngine = algoEngine
        self.spreadName = spreadName
        
        self.active = False
        self.setStopped()
        
        self.clicked.connect(self.buttonClicked)
        
    #----------------------------------------------------------------------
    def buttonClicked(self):
        """改变运行模式"""
        if self.active:
            self.stop()
        else:
            self.start()
    
    #----------------------------------------------------------------------
    def stop(self):
        """停止"""
        algoActive = self.algoEngine.stopAlgo(self.spreadName)
        if not algoActive:
            self.setStopped()        
            
    #----------------------------------------------------------------------
    def start(self):
        """启动"""
        algoActive = self.algoEngine.startAlgo(self.spreadName)
        if algoActive:
            self.setStarted()        
        
    #----------------------------------------------------------------------
    def setStarted(self):
        """算法启动"""
        self.setText(u'运行中')
        self.setStyleSheet(STYLESHEET_START)
        
        self.active = True
        self.signalActive.emit(self.active)
    
    #----------------------------------------------------------------------
    def setStopped(self):
        """算法停止"""
        self.setText(u'已停止')
        self.setStyleSheet(STYLESHEET_STOP)
        
        self.active = False
        self.signalActive.emit(self.active)
    

########################################################################
class StAlgoManager(QtWidgets.QTableWidget):
    """价差算法管理组件"""

    #----------------------------------------------------------------------
    def __init__(self, stEngine, parent=None):
        """Constructor"""
        super(StAlgoManager, self).__init__(parent)
        
        self.algoEngine = stEngine.algoEngine
        
        self.buttonActiveDict = {}       # spreadName: buttonActive
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化表格"""
        headers = [u'价差',
                   u'算法',
                   'BuyPrice',
                   'SellPrice',
                   'CoverPrice',
                   'ShortPrice',
                   u'委托上限',
                   u'持仓上限',
                   u'模式',
                   u'状态']
        self.setColumnCount(len(headers))
        self.setHorizontalHeaderLabels(headers)
        self.horizontalHeader().setResizeMode(QtWidgets.QHeaderView.Stretch)
        
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
        
    #----------------------------------------------------------------------
    def initCells(self):
        """初始化单元格"""
        algoEngine = self.algoEngine
        
        l = self.algoEngine.getAllAlgoParams()
        self.setRowCount(len(l))
        
        for row, d in enumerate(l):            
            cellSpreadName = QtWidgets.QTableWidgetItem(d['spreadName'])
            cellAlgoName = QtWidgets.QTableWidgetItem(d['algoName'])
            spinBuyPrice = StBuyPriceSpinBox(algoEngine, d['spreadName'], d['buyPrice'])
            spinSellPrice = StSellPriceSpinBox(algoEngine, d['spreadName'], d['sellPrice'])
            spinShortPrice = StShortPriceSpinBox(algoEngine, d['spreadName'], d['shortPrice'])
            spinCoverPrice = StCoverPriceSpinBox(algoEngine, d['spreadName'], d['coverPrice'])
            spinMaxOrderSize = StMaxOrderSizeSpinBox(algoEngine, d['spreadName'], d['maxOrderSize'])
            spinMaxPosSize = StMaxPosSizeSpinBox(algoEngine, d['spreadName'], d['maxPosSize'])
            comboMode = StModeComboBox(algoEngine, d['spreadName'], d['mode'])
            buttonActive = StActiveButton(algoEngine, d['spreadName'])
            
            self.setItem(row, 0, cellSpreadName)
            self.setItem(row, 1, cellAlgoName)
            self.setCellWidget(row, 2, spinBuyPrice)
            self.setCellWidget(row, 3, spinSellPrice)
            self.setCellWidget(row, 4, spinCoverPrice)
            self.setCellWidget(row, 5, spinShortPrice)
            self.setCellWidget(row, 6, spinMaxOrderSize)
            self.setCellWidget(row, 7, spinMaxPosSize)
            self.setCellWidget(row, 8, comboMode)
            self.setCellWidget(row, 9, buttonActive)
            
            buttonActive.signalActive.connect(spinBuyPrice.algoActiveChanged)
            buttonActive.signalActive.connect(spinSellPrice.algoActiveChanged)
            buttonActive.signalActive.connect(spinShortPrice.algoActiveChanged)
            buttonActive.signalActive.connect(spinCoverPrice.algoActiveChanged)
            buttonActive.signalActive.connect(spinMaxOrderSize.algoActiveChanged)
            buttonActive.signalActive.connect(spinMaxPosSize.algoActiveChanged)
            buttonActive.signalActive.connect(comboMode.algoActiveChanged)
            
            self.buttonActiveDict[d['spreadName']] = buttonActive
            
    #----------------------------------------------------------------------
    def stopAll(self):
        """停止所有算法"""
        for button in self.buttonActiveDict.values():
            button.stop()     


########################################################################
class StGroup(QtWidgets.QGroupBox):
    """集合显示"""

    #----------------------------------------------------------------------
    def __init__(self, widget, title, parent=None):
        """Constructor"""
        super(StGroup, self).__init__(parent)
        
        self.setTitle(title)
        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(widget)
        self.setLayout(vbox)
        

########################################################################
class StManager(QtWidgets.QWidget):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, stEngine, eventEngine, parent=None):
        """Constructor"""
        super(StManager, self).__init__(parent)
        
        self.stEngine = stEngine
        self.mainEngine = stEngine.mainEngine
        self.eventEngine = eventEngine
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'价差交易')
        
        # 创建组件
        tickMonitor = StTickMonitor(self.mainEngine, self.eventEngine)
        posMonitor = StPosMonitor(self.mainEngine, self.eventEngine)
        logMonitor = StLogMonitor(self.mainEngine, self.eventEngine)
        self.algoManager = StAlgoManager(self.stEngine)
        algoLogMonitor = StAlgoLogMonitor(self.mainEngine, self.eventEngine)
        
        # 创建按钮
        buttonInit = QtWidgets.QPushButton(u'初始化')
        buttonInit.clicked.connect(self.init)       
        
        buttonStopAll = QtWidgets.QPushButton(u'全部停止')
        buttonStopAll.clicked.connect(self.algoManager.stopAll)
        
        # 创建集合
        groupTick = StGroup(tickMonitor, u'价差行情')
        groupPos = StGroup(posMonitor, u'价差持仓')
        groupLog = StGroup(logMonitor, u'日志信息')
        groupAlgo = StGroup(self.algoManager, u'价差算法')
        groupAlgoLog = StGroup(algoLogMonitor, u'算法信息')
        
        # 设置布局
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(buttonInit)
        hbox.addStretch()
        hbox.addWidget(buttonStopAll)
        
        grid = QtWidgets.QGridLayout()
        grid.addLayout(hbox, 0, 0, 1, 2)
        grid.addWidget(groupTick, 1, 0)
        grid.addWidget(groupPos, 1, 1)
        grid.addWidget(groupAlgo, 2, 0, 1, 2)
        grid.addWidget(groupLog, 3, 0)
        grid.addWidget(groupAlgoLog, 3, 1)

        self.setLayout(grid)
        
    #----------------------------------------------------------------------
    def show(self):
        """重载显示"""
        self.showMaximized()
        
    #----------------------------------------------------------------------
    def init(self):
        """初始化"""
        self.stEngine.init()
        self.algoManager.initCells()
    
    
    
    