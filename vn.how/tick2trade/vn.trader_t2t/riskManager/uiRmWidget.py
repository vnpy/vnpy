# encoding: UTF-8

'''
风控模块相关的GUI控制组件
'''


from uiBasicWidget import QtGui, QtCore
from eventEngine import *


########################################################################
class RmSpinBox(QtGui.QSpinBox):
    """调整参数用的数值框"""

    #----------------------------------------------------------------------
    def __init__(self, value):
        """Constructor"""
        super(RmSpinBox, self).__init__()

        self.setMinimum(0)
        self.setMaximum(1000000)
        
        self.setValue(value)
    
    


########################################################################
class RmLine(QtGui.QFrame):
    """水平分割线"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(RmLine, self).__init__()
        self.setFrameShape(self.HLine)
        self.setFrameShadow(self.Sunken)
    
    
  

########################################################################
class RmEngineManager(QtGui.QWidget):
    """风控引擎的管理组件"""

    #----------------------------------------------------------------------
    def __init__(self, rmEngine, eventEngine, parent=None):
        """Constructor"""
        super(RmEngineManager, self).__init__(parent)
        
        self.rmEngine = rmEngine
        self.eventEngine = eventEngine
        
        self.initUi()
        self.updateEngineStatus()

    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'风险管理')
        
        # 设置界面
        self.buttonSwitchEngineStatus = QtGui.QPushButton(u'风控模块未启动')
        
        self.spinOrderFlowLimit = RmSpinBox(self.rmEngine.orderFlowLimit)
        self.spinOrderFlowClear = RmSpinBox(self.rmEngine.orderFlowClear)
        self.spinOrderSizeLimit = RmSpinBox(self.rmEngine.orderSizeLimit)
        self.spinTradeLimit = RmSpinBox(self.rmEngine.tradeLimit)
        self.spinWorkingOrderLimit = RmSpinBox(self.rmEngine.workingOrderLimit)
        
        buttonClearOrderFlowCount = QtGui.QPushButton(u'清空流控计数')
        buttonClearTradeCount = QtGui.QPushButton(u'清空总成交计数')
        buttonSaveSetting = QtGui.QPushButton(u'保存设置')
        
        Label = QtGui.QLabel
        grid = QtGui.QGridLayout()
        grid.addWidget(Label(u'工作状态'), 0, 0)
        grid.addWidget(self.buttonSwitchEngineStatus, 0, 1)
        grid.addWidget(RmLine(), 1, 0, 1, 2)
        grid.addWidget(Label(u'流控上限'), 2, 0)
        grid.addWidget(self.spinOrderFlowLimit, 2, 1)
        grid.addWidget(Label(u'流控清空（秒）'), 3, 0)
        grid.addWidget(self.spinOrderFlowClear, 3, 1)
        grid.addWidget(RmLine(), 4, 0, 1, 2)
        grid.addWidget(Label(u'单笔委托上限'), 5, 0)
        grid.addWidget(self.spinOrderSizeLimit, 5, 1)
        grid.addWidget(RmLine(), 6, 0, 1, 2)
        grid.addWidget(Label(u'总成交上限'), 7, 0)
        grid.addWidget(self.spinTradeLimit, 7, 1)
        grid.addWidget(RmLine(), 8, 0, 1, 2)
        grid.addWidget(Label(u'活动订单上限'), 9, 0)
        grid.addWidget(self.spinWorkingOrderLimit, 9, 1)
        
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(buttonClearOrderFlowCount)
        hbox.addWidget(buttonClearTradeCount)
        hbox.addStretch()
        hbox.addWidget(buttonSaveSetting)
        
        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(grid)
        vbox.addLayout(hbox)
        self.setLayout(vbox)
        
        # 连接组件信号
        self.spinOrderFlowLimit.valueChanged.connect(self.rmEngine.setOrderFlowLimit)
        self.spinOrderFlowClear.valueChanged.connect(self.rmEngine.setOrderFlowClear)
        self.spinOrderSizeLimit.valueChanged.connect(self.rmEngine.setOrderSizeLimit)
        self.spinTradeLimit.valueChanged.connect(self.rmEngine.setTradeLimit)
        self.spinWorkingOrderLimit.valueChanged.connect(self.rmEngine.setWorkingOrderLimit)
        
        self.buttonSwitchEngineStatus.clicked.connect(self.switchEngineSatus)
        buttonClearOrderFlowCount.clicked.connect(self.rmEngine.clearOrderFlowCount)
        buttonClearTradeCount.clicked.connect(self.rmEngine.clearTradeCount)
        buttonSaveSetting.clicked.connect(self.rmEngine.saveSetting)
        
        # 设为固定大小
        self.setFixedSize(self.sizeHint())
        
    #----------------------------------------------------------------------
    def switchEngineSatus(self):
        """控制风控引擎开关"""
        self.rmEngine.switchEngineStatus()
        self.updateEngineStatus()
        
    #----------------------------------------------------------------------
    def updateEngineStatus(self):
        """更新引擎状态"""
        if self.rmEngine.active:
            self.buttonSwitchEngineStatus.setText(u'风控模块运行中')
        else:
            self.buttonSwitchEngineStatus.setText(u'风控模块未启动')
 
    