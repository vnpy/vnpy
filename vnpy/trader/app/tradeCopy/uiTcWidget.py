# encoding: UTF-8

import shelve

from vnpy.event import Event
from vnpy.trader.uiQt import QtCore, QtGui, QtWidgets
from vnpy.trader.vtFunction import getTempPath

from .tcEngine import EVENT_TC_LOG


########################################################################
class TcManager(QtWidgets.QWidget):
    """"""
    REQ_ADDRESS = 'tcp://localhost:2015'
    SUB_ADDRESS = 'tcp://localhost:2018'   
    REP_ADDRESS = 'tcp://*:2015'
    PUB_ADDRESS = 'tcp://*:2018'
    COPY_RATIO = '1'
    INTERVAL = '1'
    
    settingFileName = 'TradeCopy.vt'
    settingFilePath = getTempPath(settingFileName)
    
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, tcEngine, eventEngine, parent=None):
        """Constructor"""
        super(TcManager, self).__init__(parent)
        
        self.tcEngine = tcEngine
        self.eventEngine = eventEngine
        
        self.initUi()
        self.loadSetting()
        self.registerEvent()
        
        self.tcEngine.writeLog(u'欢迎使用TradeCopy交易复制模块')
    
    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'交易复制')
        self.setMinimumWidth(700)
        self.setMinimumHeight(700)
        
        # 创建组件
        self.lineReqAddress = QtWidgets.QLineEdit(self.REQ_ADDRESS)
        self.lineSubAddress= QtWidgets.QLineEdit(self.SUB_ADDRESS)
        self.lineRepAddress = QtWidgets.QLineEdit(self.REP_ADDRESS)
        self.linePubAddress = QtWidgets.QLineEdit(self.PUB_ADDRESS)
        
        validator = QtGui.QDoubleValidator()
        validator.setBottom(0)
        self.lineCopyRatio = QtWidgets.QLineEdit()
        self.lineCopyRatio.setValidator(validator)
        self.lineCopyRatio.setText(self.COPY_RATIO)
        
        validator2 = QtGui.QIntValidator()
        validator2.setBottom(1)
        self.lineInterval = QtWidgets.QLineEdit()
        self.lineInterval.setValidator(validator2)
        self.lineInterval.setText(self.INTERVAL)
        
        self.buttonProvider = QtWidgets.QPushButton(u'启动发布者')
        self.buttonProvider.clicked.connect(self.startProvider)
        
        self.buttonSubscriber = QtWidgets.QPushButton(u'启动订阅者')
        self.buttonSubscriber.clicked.connect(self.startSubscriber)
        
        self.buttonStopEngine = QtWidgets.QPushButton(u'停止')
        self.buttonStopEngine.clicked.connect(self.stopEngine)
        self.buttonStopEngine.setEnabled(False)
        
        self.buttonResetAddress = QtWidgets.QPushButton(u'重置地址')
        self.buttonResetAddress.clicked.connect(self.resetAddress)
        
        self.logMonitor = QtWidgets.QTextEdit()
        self.logMonitor.setReadOnly(True)
        
        self.widgetList = [
            self.lineCopyRatio,
            self.lineInterval,
            self.linePubAddress,
            self.lineSubAddress,
            self.lineRepAddress,
            self.lineReqAddress,
            self.buttonProvider,
            self.buttonSubscriber,
            self.buttonResetAddress
        ]
        
        # 布局
        QLabel = QtWidgets.QLabel
        grid = QtWidgets.QGridLayout()
        
        grid.addWidget(QLabel(u'响应地址'), 0, 0)
        grid.addWidget(self.lineRepAddress, 0, 1)
        grid.addWidget(QLabel(u'请求地址'), 0, 2)
        grid.addWidget(self.lineReqAddress, 0, 3)
        
        grid.addWidget(QLabel(u'发布地址'), 1, 0)
        grid.addWidget(self.linePubAddress, 1, 1)
        grid.addWidget(QLabel(u'订阅地址'), 1, 2)
        grid.addWidget(self.lineSubAddress, 1, 3)
        
        grid.addWidget(QLabel(u'发布间隔（秒）'), 2, 0)
        grid.addWidget(self.lineInterval, 2, 1)
        grid.addWidget(QLabel(u'复制比例（倍）'), 2, 2)
        grid.addWidget(self.lineCopyRatio, 2, 3)
        
        grid.addWidget(self.buttonProvider, 3, 0, 1, 2)
        grid.addWidget(self.buttonSubscriber, 3, 2, 1, 2)
        grid.addWidget(self.buttonStopEngine, 4, 0, 1, 2)
        grid.addWidget(self.buttonResetAddress, 4, 2, 1, 2)
        
        grid.addWidget(self.logMonitor, 5, 0, 1, 4)
        
        self.setLayout(grid)
    
    #----------------------------------------------------------------------
    def saveSetting(self):
        """"""
        f = shelve.open(self.settingFilePath)
        f['repAddress'] = self.lineRepAddress.text()
        f['reqAddress'] = self.lineReqAddress.text()
        f['pubAddress'] = self.linePubAddress.text()
        f['subAddress'] = self.lineSubAddress.text()
        f['copyRatio'] = self.lineCopyRatio.text()
        f['interval'] = self.lineInterval.text()
        f.close()
    
    #----------------------------------------------------------------------
    def loadSetting(self):
        """"""
        f = shelve.open(self.settingFilePath)
        if f:
            self.lineRepAddress.setText(f['repAddress'])
            self.lineReqAddress.setText(f['reqAddress'])
            self.linePubAddress.setText(f['pubAddress'])
            self.lineSubAddress.setText(f['subAddress'])
            self.lineCopyRatio.setText(f['copyRatio'])
            self.lineInterval.setText(f['interval'])
        f.close()        
    
    #----------------------------------------------------------------------
    def resetAddress(self):
        """"""
        self.lineReqAddress.setText(self.REQ_ADDRESS)
        self.lineRepAddress.setText(self.REP_ADDRESS)
        self.linePubAddress.setText(self.PUB_ADDRESS)
        self.lineSubAddress.setText(self.SUB_ADDRESS)
    
    #----------------------------------------------------------------------
    def stopEngine(self):
        """"""
        self.tcEngine.stop()
        
        for widget in self.widgetList:
            widget.setEnabled(True)
        self.buttonStopEngine.setEnabled(False)

    #----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.signal.connect(self.processLogEvent)
        self.eventEngine.register(EVENT_TC_LOG, self.signal.emit)
    
    #----------------------------------------------------------------------
    def processLogEvent(self, event):
        """"""
        log = event.dict_['data']
        txt = '%s:  %s' %(log.logTime, log.logContent)
        self.logMonitor.append(txt)
    
    #----------------------------------------------------------------------
    def startProvider(self):
        """"""
        repAddress = str(self.lineRepAddress.text())
        pubAddress = str(self.linePubAddress.text())
        interval = int(self.lineInterval.text())
        self.tcEngine.startProvider(repAddress, pubAddress, interval)
        
        for widget in self.widgetList:
            widget.setEnabled(False)
        self.buttonStopEngine.setEnabled(True)
        
    #----------------------------------------------------------------------
    def startSubscriber(self):
        """"""
        reqAddress = str(self.lineReqAddress.text())
        subAddress = str(self.lineSubAddress.text())
        copyRatio = float(self.lineCopyRatio.text())
        self.tcEngine.startSubscriber(reqAddress, subAddress, copyRatio)
    
        for widget in self.widgetList:
            widget.setEnabled(False)
        self.buttonStopEngine.setEnabled(True)