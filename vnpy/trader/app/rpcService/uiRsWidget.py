# encoding: UTF-8

from vnpy.trader.uiQt import QtWidgets


########################################################################
class RsEngineManager(QtWidgets.QWidget):
    """RPC服务组件管理"""

    #----------------------------------------------------------------------
    def __init__(self, rsEngine, eventEngine, parent=None):
        """Constructor"""
        super(RsEngineManager, self).__init__(parent)
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'RPC服务')
        
        label = QtWidgets.QLabel(u'该模块运行于服务端')
        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(label)
        self.setLayout(vbox)
        
        
        
    
    