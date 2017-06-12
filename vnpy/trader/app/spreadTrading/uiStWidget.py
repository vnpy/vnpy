# encoding: UTF-8

from collections import OrderedDict

from vnpy.trader.uiQt import QtWidgets
from vnpy.trader.uiBasicWidget import (BasicMonitor, BasicCell, 
                                       AskCell, BidCell, BASIC_FONT)

from .stBase import EVENT_SPREADTRADING_TICK



########################################################################
class StTickMonitor(BasicMonitor):
    """"""
    
    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(StTickMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        # 设置表头有序字典
        d = OrderedDict()
        d['name'] = {'chinese':u'价差名称', 'cellType':BasicCell}
        d['bidPrice'] = {'chinese':u'买价', 'cellType':BidCell}
        d['bidVolume'] = {'chinese':u'买量', 'cellType':BidCell}
        d['askPrice'] = {'chinese':u'卖价', 'cellType':AskCell}
        d['askVolume'] = {'chinese':u'卖量', 'cellType':AskCell}
        d['time'] = {'chinese':u'时间', 'cellType':BasicCell}
        d['symbol'] = {'chinese':u'代码', 'cellType':BasicCell}
        self.setHeaderDict(d)
    
        # 设置数据键
        self.setDataKey('name')
    
        # 设置监控事件类型
        self.setEventType(EVENT_SPREADTRADING_TICK)
    
        # 设置字体
        self.setFont(BASIC_FONT)
    
        # 初始化表格
        self.initTable()
    
        # 注册事件监听
        self.registerEvent()        


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
        
        # 创建按钮
        buttonLoadSetting = QtWidgets.QPushButton(u'加载配置')
        
        buttonLoadSetting.clicked.connect(self.stEngine.loadSetting)
        
        # 创建组件
        tickMonitor = StTickMonitor(self.mainEngine, self.eventEngine)
        
        # 设置布局
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(buttonLoadSetting)
        hbox.addStretch()
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(tickMonitor)
        
        self.setLayout(vbox)
        
    #----------------------------------------------------------------------
    def show(self):
        """重载显示"""
        self.showMaximized()
        
        
    
    
    
    