# encoding: UTF-8

'''
风控模块相关的GUI控制组件
'''


from vnpy.event import Event

from vnpy.trader.uiBasicWidget import QtGui, QtWidgets, QtCore
from vnpy.trader.app.riskManager.language import text


########################################################################
class RmSpinBox(QtWidgets.QSpinBox):
    """调整参数用的数值框"""

    #----------------------------------------------------------------------
    def __init__(self, value):
        """Constructor"""
        super(RmSpinBox, self).__init__()

        self.setMinimum(0)
        self.setMaximum(1000000)
        
        self.setValue(value)
    

########################################################################
class RmLine(QtWidgets.QFrame):
    """水平分割线"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(RmLine, self).__init__()
        self.setFrameShape(self.HLine)
        self.setFrameShadow(self.Sunken)
    

########################################################################
class RmEngineManager(QtWidgets.QWidget):
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
        self.setWindowTitle(text.RISK_MANAGER)
        
        # 设置界面
        self.buttonSwitchEngineStatus = QtWidgets.QPushButton(text.RISK_MANAGER_STOP)
        
        self.spinOrderFlowLimit = RmSpinBox(self.rmEngine.orderFlowLimit)
        self.spinOrderFlowClear = RmSpinBox(self.rmEngine.orderFlowClear)
        self.spinOrderSizeLimit = RmSpinBox(self.rmEngine.orderSizeLimit)
        self.spinTradeLimit = RmSpinBox(self.rmEngine.tradeLimit)
        self.spinWorkingOrderLimit = RmSpinBox(self.rmEngine.workingOrderLimit)
        self.spinOrderCancelLimit = RmSpinBox(self.rmEngine.orderCancelLimit)
        
        self.spinMarginRatioLimit = RmSpinBox(self.rmEngine.marginRatioLimit * 100) # 百分比显示配置
        self.spinMarginRatioLimit.setMaximum(100)   
        self.spinMarginRatioLimit.setSuffix('%')
        
        buttonClearOrderFlowCount = QtWidgets.QPushButton(text.CLEAR_ORDER_FLOW_COUNT)
        buttonClearTradeCount = QtWidgets.QPushButton(text.CLEAR_TOTAL_FILL_COUNT)
        buttonSaveSetting = QtWidgets.QPushButton(text.SAVE_SETTING)
        
        Label = QtWidgets.QLabel
        grid = QtWidgets.QGridLayout()
        grid.addWidget(Label(text.WORKING_STATUS), 0, 0)
        grid.addWidget(self.buttonSwitchEngineStatus, 0, 1)
        grid.addWidget(RmLine(), 1, 0, 1, 2)
        grid.addWidget(Label(text.ORDER_FLOW_LIMIT), 2, 0)
        grid.addWidget(self.spinOrderFlowLimit, 2, 1)
        grid.addWidget(Label(text.ORDER_FLOW_CLEAR), 3, 0)
        grid.addWidget(self.spinOrderFlowClear, 3, 1)
        grid.addWidget(RmLine(), 4, 0, 1, 2)
        grid.addWidget(Label(text.ORDER_SIZE_LIMIT), 5, 0)
        grid.addWidget(self.spinOrderSizeLimit, 5, 1)
        grid.addWidget(RmLine(), 6, 0, 1, 2)
        grid.addWidget(Label(text.TOTAL_TRADE_LIMIT), 7, 0)
        grid.addWidget(self.spinTradeLimit, 7, 1)
        grid.addWidget(RmLine(), 8, 0, 1, 2)
        grid.addWidget(Label(text.WORKING_ORDER_LIMIT), 9, 0)
        grid.addWidget(self.spinWorkingOrderLimit, 9, 1)
        grid.addWidget(RmLine(), 10, 0, 1, 2)
        grid.addWidget(Label(text.CONTRACT_CANCEL_LIMIT), 11, 0)
        grid.addWidget(self.spinOrderCancelLimit, 11, 1)
        grid.addWidget(RmLine(), 12, 0, 1, 2)
        grid.addWidget(Label(text.MARGIN_RATIO_LIMIT), 13, 0)
        grid.addWidget(self.spinMarginRatioLimit, 13, 1)        
        
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(buttonClearOrderFlowCount)
        hbox.addWidget(buttonClearTradeCount)
        hbox.addStretch()
        hbox.addWidget(buttonSaveSetting)
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(grid)
        vbox.addLayout(hbox)
        self.setLayout(vbox)
        
        # 连接组件信号
        self.spinOrderFlowLimit.valueChanged.connect(self.rmEngine.setOrderFlowLimit)
        self.spinOrderFlowClear.valueChanged.connect(self.rmEngine.setOrderFlowClear)
        self.spinOrderSizeLimit.valueChanged.connect(self.rmEngine.setOrderSizeLimit)
        self.spinTradeLimit.valueChanged.connect(self.rmEngine.setTradeLimit)
        self.spinWorkingOrderLimit.valueChanged.connect(self.rmEngine.setWorkingOrderLimit)
        self.spinOrderCancelLimit.valueChanged.connect(self.rmEngine.setOrderCancelLimit)
        self.spinMarginRatioLimit.valueChanged.connect(self.rmEngine.setMarginRatioLimit)

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
            self.buttonSwitchEngineStatus.setText(text.RISK_MANAGER_RUNNING)
        else:
            self.buttonSwitchEngineStatus.setText(text.RISK_MANAGER_STOP)
 
    