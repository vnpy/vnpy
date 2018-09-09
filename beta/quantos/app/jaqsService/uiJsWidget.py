# encoding: UTF-8

'''
行情记录模块相关的GUI控制组件
'''

from vnpy.event import Event
from vnpy.trader.uiQt import QtWidgets, QtCore
from .jsEngine import EVENT_JS_LOG



########################################################################
class JsEngineManager(QtWidgets.QWidget):
    """Jaqs服务管理组件"""
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, jsEngine, eventEngine, parent=None):
        """Constructor"""
        super(JsEngineManager, self).__init__(parent)
        
        self.jsEngine = jsEngine
        self.eventEngine = eventEngine
        
        self.initUi()
        self.registerEvent() 
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'Jaqs服务')
        # 日志监控
        self.logMonitor = QtWidgets.QTextEdit()
        self.logMonitor.setReadOnly(True)
        self.logMonitor.setMinimumHeight(600)
        
        # 设置布局
        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.logMonitor)
        self.setLayout(vbox)

    #----------------------------------------------------------------------
    def updateLog(self, event):
        """更新日志"""
        log = event.dict_['data']
        content = '\t'.join([log.logTime, log.logContent])
        self.logMonitor.append(content)
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateLog)
        self.eventEngine.register(EVENT_JS_LOG, self.signal.emit)