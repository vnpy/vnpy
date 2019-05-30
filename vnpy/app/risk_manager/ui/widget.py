from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtWidgets
from ..engine import APP_NAME


class RiskManager(QtWidgets.QWidget):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine
        self.risk_manager_engine = main_engine.get_engine(APP_NAME)

        self.init_ui()
        self.update_engine_status()

    def init_ui(self):
        """"""
        self.setWindowTitle("风险控制")

        # SpinBox
        self.order_flow_limit = RiskManagerSpinBox(0)
        self.order_flow_clear = RiskManagerSpinBox(0)   
        self.order_size_limit = RiskManagerSpinBox(0)     
        self.trade_limit = RiskManagerSpinBox(0)              
        self.active_order_limit = RiskManagerSpinBox(0)   
        self.order_cancel_limit = RiskManagerSpinBox(0)  

        # Button
        self.switch_button = QtWidgets.QPushButton("风控模块未启动")
        clear_order_count_button = QtWidgets.QPushButton("清空流控计数")
        clear_trade_count_button = QtWidgets.QPushButton("清空总成交计数")
        save_setting_button = QtWidgets.QPushButton("保存设置")

        # Grid layout
        Label = QtWidgets.QLabel
        grid = QtWidgets.QGridLayout()
        grid.addWidget(Label("工作状态"), 0, 0)
        grid.addWidget(self.switch_button, 0, 1)
        grid.addWidget(Label("流控上限"), 1, 0)
        grid.addWidget(self.order_flow_limit, 1, 1)
        grid.addWidget(Label("流控清空（秒）"), 2, 0)
        grid.addWidget(self.order_flow_clear, 2, 1)
        grid.addWidget(Label("单笔委托上限"), 3, 0)
        grid.addWidget(self.order_size_limit, 3, 1)        
        grid.addWidget(Label("总成交上限"), 4, 0)
        grid.addWidget(self.trade_limit, 4, 1)
        grid.addWidget(Label("活动订单上限"), 5, 0)
        grid.addWidget(self.active_order_limit, 5, 1) 
        grid.addWidget(Label("单合约撤单上限"), 6, 0)
        grid.addWidget(self.order_cancel_limit, 6, 1) 

        # Horizontal box layout
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(clear_order_count_button)
        hbox.addWidget(clear_trade_count_button)
        hbox.addWidget(save_setting_button)

        # Vertical box layout
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(grid)
        vbox.addLayout(hbox)
        self.setLayout(vbox)

        # Connect signal to SpinBox
        self.order_flow_limit.valueChanged.connect(self.risk_manager_engine.set_order_flow_limit)
        self.order_flow_clear.valueChanged.connect(self.risk_manager_engine.set_order_flow_clear)
        self.order_size_limit.valueChanged.connect(self.risk_manager_engine.set_order_size_limit)
        self.trade_limit.valueChanged.connect(self.risk_manager_engine.set_trade_limit)
        self.active_order_limit.valueChanged.connect(self.risk_manager_engine.set_active_order_limit)
        self.order_cancel_limit.valueChanged.connect(self.risk_manager_engine.set_order_cancel_limit)

        # Connect signal to button       
        self.switch_button.clicked.connect(self.switch_engine_status)
        clear_order_count_button.clicked.connect(self.risk_manager_engine.clear_order_flow_count)
        clear_trade_count_button.clicked.connect(self.risk_manager_engine.clear_trade_count)
        save_setting_button.clicked.connect(self.risk_manager_engine.save_setting)

        # Set Fix Size
        self.setFixedSize(self.sizeHint())

    def switch_engine_status(self):
        """"""
        self.risk_manager_engine.switch_engine_status()
        self.update_engine_status()

    def update_engine_status(self):
        """"""
        if self.risk_manager_engine.active:
            self.switch_button.setText("风控模块运行中")
            self.order_flow_limit.setValue(self.risk_manager_engine.order_flow_limit)
            self.order_flow_clear.setValue(self.risk_manager_engine.order_flow_clear)
            self.order_size_limit.setValue(self.risk_manager_engine.order_size_limit)   
            self.trade_limit.setValue(self.risk_manager_engine.trade_limit)              
            self.active_order_limit.setValue(self.risk_manager_engine.active_order_limit)  
            self.order_cancel_limit.setValue(self.risk_manager_engine.order_cancel_limit)
        else:
            self.switch_button.setText("风控模块未启动")
        
        self.risk_manager_engine.save_setting()


class RiskManagerSpinBox(QtWidgets.QSpinBox):
    """"""

    def __init__(self, value):
        """"""
        super(RiskManagerSpinBox, self).__init__()

        self.setMinimum(0)
        self.setMaximum(1000000)        
        self.setValue(value)
