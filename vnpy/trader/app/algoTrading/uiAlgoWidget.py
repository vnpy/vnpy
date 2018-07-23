# encoding: UTF-8

from six import text_type

from vnpy.trader.uiQt import QtWidgets


########################################################################
class AlgoWidget(QtWidgets.QFrame):
    """算法启动组件"""
    
    #----------------------------------------------------------------------
    def __init__(self, algoEngine, parent=None):
        """Constructor"""
        super(AlgoWidget, self).__init__(parent)
        
        self.templateName = ''
        self.algoEngine = algoEngine
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setFrameShape(self.Box)
        algoLayout = self.initAlgoLayout()
        
        buttonStart = QtWidgets.QPushButton(u'启动算法')
        buttonStart.clicked.connect(self.addAlgo)
        buttonStart.setMinimumHeight(100)
        
        buttonSave = QtWidgets.QPushButton(u'保存配置')
        buttonSave.clicked.connect(self.saveAlgoSetting)
        buttonSave.setMinimumHeight(100)
        
        self.lineSettingName = QtWidgets.QLineEdit()
        self.lineSettingName.setPlaceholderText(u'算法配置名称')
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(algoLayout)
        vbox.addWidget(buttonStart)
        vbox.addWidget(QtWidgets.QLabel(''))
        vbox.addWidget(QtWidgets.QLabel(''))
        vbox.addWidget(self.lineSettingName)
        vbox.addWidget(buttonSave)
        
        self.setLayout(vbox)
    
    #----------------------------------------------------------------------
    def addAlgo(self):
        """启动算法"""
        setting = self.getAlgoSetting()
        self.algoEngine.addAlgo(setting)
    
    #----------------------------------------------------------------------
    def saveAlgoSetting(self):
        """保存算法配置"""
        setting = self.getAlgoSetting()
        setting['templateName'] = self.templateName
        setting['settingName'] = text_type(self.lineSettingName.text())
        self.algoEngine.saveAlgoSetting(setting)
        
        self.lineSettingName.setText('')
    
    #----------------------------------------------------------------------
    def initAlgoLayout(self):
        """初始化算法相关的组件部分"""
        pass
        
    #----------------------------------------------------------------------
    def getAlgoSetting(self):
        """获取算法配置"""
        pass
