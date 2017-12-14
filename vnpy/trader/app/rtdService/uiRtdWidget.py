# encoding: UTF-8

from datetime import datetime

from vnpy.event import Event
from vnpy.trader.uiQt import QtCore, QtWidgets

from .rtdEngine import EVENT_RTDSERVICE_LOG


########################################################################
class RtdManager(QtWidgets.QWidget):
    """RTD管理工具"""
    
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, rsEngine, eventEngine, parent=None):
        """Constructor"""
        super(RtdManager, self).__init__(parent)
        
        self.rsEngine = rsEngine
        self.eventEngine = eventEngine
        
        self.initUi()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateLog)
        
        self.eventEngine.register(EVENT_RTDSERVICE_LOG, self.signal.emit)
    
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'RTD服务')
        
        self.logMonitor = QtWidgets.QTextBrowser()
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.logMonitor)
        
        self.setLayout(vbox)
    
    #----------------------------------------------------------------------
    def updateLog(self, event):
        """输出日志"""
        log = event.dict_['data']
        content = log.logTime + "\t" + log.logContent + '\n'
        self.logMonitor.append(content)
        
        
        
    
    