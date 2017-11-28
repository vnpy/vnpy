# encoding: UTF-8

from PyQt4 import QtGui, QtCore

from eventEngine import Event
from eventType import *


########################################################################
class HedgingManager(QtGui.QWidget):
    """对冲管理组件"""
    signal = QtCore.pyqtSignal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, omEngine, parent=None):
        """Constructor"""
        super(HedgingManager, self).__init__(parent)
        
        self.portfolio = omEngine.portfolio
        self.hedgingEngine = omEngine.hedgingEngine
        self.eventEngine = omEngine.eventEngine
        
        self.initUi()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化"""
        self.setWindowTitle(u'对冲管理')
        
        self.comboUnderlyingSymbol = QtGui.QComboBox()
        l = [underlying.symbol for underlying in self.portfolio.underlyingList]
        self.comboUnderlyingSymbol.addItems(l)

        # 如果对冲引擎的代码在当前组合的列表中，则选中
        if self.hedgingEngine.underlyingSymbol in l:
            self.comboUnderlyingSymbol.setCurrentIndex(l.index(self.hedgingEngine.underlyingSymbol))
        # 否则可能是因为组合发生了变化，修改对冲标的代码
        else:
            self.setUnderlyingSymbol()
        
        self.spinTargetDelta = QtGui.QSpinBox()
        self.spinTargetDelta.setMinimum(-100000)
        self.spinTargetDelta.setMaximum(100000)
        self.spinTargetDelta.setValue(self.hedgingEngine.targetDelta)
        
        self.spinDeltaRange = QtGui.QSpinBox()
        self.spinDeltaRange.setMinimum(0)
        self.spinDeltaRange.setMaximum(100000)
        self.spinDeltaRange.setValue(self.hedgingEngine.deltaRange)
        
        self.spinHedgingTrigger = QtGui.QSpinBox()
        self.spinHedgingTrigger.setMinimum(1)
        self.spinHedgingTrigger.setMaximum(3600)
        self.spinHedgingTrigger.setValue(self.hedgingEngine.hedgingTrigger)
        
        self.spinMaxOrderSize = QtGui.QSpinBox()
        self.spinMaxOrderSize.setMinimum(1)
        self.spinMaxOrderSize.setMaximum(1000)
        self.spinMaxOrderSize.setValue(self.hedgingEngine.maxOrderSize)
        
        self.spinMaxSpreadTick = QtGui.QSpinBox()
        self.spinMaxSpreadTick.setMinimum(1)
        self.spinMaxSpreadTick.setMaximum(30)
        self.spinMaxSpreadTick.setValue(self.hedgingEngine.maxSpreadTick)        
        
        self.labelDeltaUpLimit = QtGui.QLabel(str(self.hedgingEngine.deltaUpLimit))
        self.labelDeltaDownLimit = QtGui.QLabel(str(self.hedgingEngine.deltaDownLimit))
        self.labelHedgingCount = QtGui.QLabel(str(self.hedgingEngine.hedgingCount))
        
        self.buttonActive = QtGui.QPushButton(u'已停止')
        self.buttonActive.clicked.connect(self.switchEngineStatus)
        
        self.buttonSaveSetting = QtGui.QPushButton(u'保存配置')
        self.buttonSaveSetting.clicked.connect(self.hedgingEngine.saveSetting)
        
        grid = QtGui.QGridLayout()
        grid.addWidget(QtGui.QLabel(u'标的代码'), 0, 0)
        grid.addWidget(self.comboUnderlyingSymbol, 0, 1)
        grid.addWidget(QtGui.QLabel(u'对冲频率（秒）'), 1, 0)
        grid.addWidget(self.spinHedgingTrigger, 1, 1)
        grid.addWidget(QtGui.QLabel(u'目标Delta'), 2, 0)
        grid.addWidget(self.spinTargetDelta, 2, 1)
        grid.addWidget(QtGui.QLabel(u'Delta范围'), 3, 0)
        grid.addWidget(self.spinDeltaRange, 3, 1)
        grid.addWidget(QtGui.QLabel(u'单笔最大'), 4, 0)
        grid.addWidget(self.spinMaxOrderSize, 4, 1)        
        grid.addWidget(QtGui.QLabel(u'最大价差'), 5, 0)
        grid.addWidget(self.spinMaxSpreadTick, 5, 1)        

        grid.addWidget(self.buttonActive, 6, 0, 1, 2)
        
        grid.addWidget(QtGui.QLabel(u'Delta上限'), 7, 0)
        grid.addWidget(self.labelDeltaUpLimit, 7, 1)
        grid.addWidget(QtGui.QLabel(u'Delta下限'), 8, 0)
        grid.addWidget(self.labelDeltaDownLimit, 8, 1)        
        grid.addWidget(QtGui.QLabel(u'对冲读秒'), 9, 0)
        grid.addWidget(self.labelHedgingCount, 9, 1)
        
        grid.addWidget(self.buttonSaveSetting, 10, 0, 1, 2)
        
        self.setLayout(grid)
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateEngineStatus)
        self.spinTargetDelta.valueChanged.connect(self.setTargetDelta)
        self.spinDeltaRange.valueChanged.connect(self.setDeltaRange)
        self.spinHedgingTrigger.valueChanged.connect(self.setHedgingTrigger)
        self.spinMaxOrderSize.valueChanged.connect(self.setMaxOrderSize)
        self.spinMaxSpreadTick.valueChanged.connect(self.setMaxSpreadTick)
        
        self.eventEngine.register(EVENT_OM_HEDGING_STATUS, self.signal.emit)
    
    #----------------------------------------------------------------------
    def updateDeltaLimit(self):
        """更新Delta上下限"""
        self.labelDeltaUpLimit.setText(str(self.hedgingEngine.deltaUpLimit))
        self.labelDeltaDownLimit.setText(str(self.hedgingEngine.deltaDownLimit))
        
    #----------------------------------------------------------------------
    def updateEngineStatus(self, event):
        """更新引擎状态"""
        self.labelHedgingCount.setText(str(self.hedgingEngine.hedgingCount))
    
    #----------------------------------------------------------------------
    def setTargetDelta(self):
        """设置目标Delta值"""
        self.hedgingEngine.setTargetDelta(int(self.spinTargetDelta.value()))
        self.updateDeltaLimit()
        
    #----------------------------------------------------------------------
    def setDeltaRange(self):
        """设置Delta范围"""
        self.hedgingEngine.setDeltaRange(int(self.spinDeltaRange.value()))
        self.updateDeltaLimit()
        
    #----------------------------------------------------------------------
    def setHedgingTrigger(self):
        """设置对冲间隔"""
        self.hedgingEngine.setHedgingTrigger(int(self.spinHedgingTrigger.value()))
        
    #----------------------------------------------------------------------
    def setUnderlyingSymbol(self):
        """设置标的代码"""
        self.hedgingEngine.resetUnderlying(str(self.comboUnderlyingSymbol.currentText()))
        
    #----------------------------------------------------------------------
    def setMaxOrderSize(self):
        """"""
        self.hedgingEngine.setMaxOrderSize(int(self.spinMaxOrderSize.value()))    
        
    #----------------------------------------------------------------------
    def setMaxSpreadTick(self):
        """"""
        self.hedgingEngine.setMaxSpreadTick(int(self.spinMaxSpreadTick.value()))
        
    #----------------------------------------------------------------------
    def switchEngineStatus(self):
        """改变引擎状态"""
        if self.hedgingEngine.hedgingActive:
            self.hedgingEngine.stop()
            self.buttonActive.setText(u'已停止')
        else:
            self.hedgingEngine.start()
            self.buttonActive.setText(u'运行中')
        
    
    