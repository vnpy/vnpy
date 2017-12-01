# encoding: UTF-8

from __future__ import division

import os
from datetime import datetime

from vnpy.event import Event

from .omBase import EVENT_OM_LOG
from .uiOmBase import QtWidgets, QtCore
from .uiOmManualTrader import ManualTrader
from .uiOmGreeksMonitor import GreeksMonitor
from .uiOmVolatilityManager import VolatilityChart, VolatilityManager


########################################################################
class OmManager(QtWidgets.QWidget):
    """管理组件"""
    signal = QtCore.pyqtSignal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, omEngine, eventEngine, parent=None):
        """Constructor"""
        super(OmManager, self).__init__(parent)
        
        self.omEngine = omEngine
        self.eventEngine = eventEngine
        
        self.widgetDict = {}
        
        self.initUi()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'OptionMaster管理')
        
        # 读取配置文件
        settingFileList = []
        
        path = os.path.abspath(os.path.dirname(__file__))
        for root, subdirs, files in os.walk(path):
            for name in files:      
                if '_portfolio.json' in name:
                    settingFileList.append(name)
        
        # 设置界面
        self.comboSettingFile = QtWidgets.QComboBox()
        self.comboSettingFile.addItems(settingFileList)
        self.comboSettingFile.setCurrentIndex(0)
        
        self.buttonInit = QtWidgets.QPushButton(u'初始化')
        self.buttonInit.clicked.connect(self.initOmEngine)
        
        self.buttonManualTrader = QtWidgets.QPushButton(u'手动交易')
        self.buttonManualTrader.clicked.connect(self.openManualTrader)
        self.buttonManualTrader.setDisabled(True)
        
        self.buttonGreeksMonitor = QtWidgets.QPushButton(u'希腊值监控')
        self.buttonGreeksMonitor.clicked.connect(self.openGreeksMonitor)
        self.buttonGreeksMonitor.setDisabled(True)
        
        self.buttonVolatilityChart = QtWidgets.QPushButton(u'波动率图表')
        self.buttonVolatilityChart.clicked.connect(self.openVolatilityChart)
        self.buttonVolatilityChart.setDisabled(True)
        
        self.buttonVolatilityManager = QtWidgets.QPushButton(u'波动率管理')
        self.buttonVolatilityManager.clicked.connect(self.openVolatilityManager)
        self.buttonVolatilityManager.setDisabled(True)
        
        self.logMonitor = QtWidgets.QTextEdit()
        self.logMonitor.setReadOnly(True)
        
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(self.comboSettingFile)
        hbox.addWidget(self.buttonInit)
        hbox.addWidget(self.buttonManualTrader)
        hbox.addWidget(self.buttonGreeksMonitor)
        hbox.addWidget(self.buttonVolatilityChart)
        hbox.addWidget(self.buttonVolatilityManager)
        hbox.addStretch()
        
        hbox2 = QtWidgets.QHBoxLayout()
        hbox2.addStretch()
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addLayout(hbox2)
        vbox.addWidget(self.logMonitor)
        
        self.setLayout(vbox)
        
    #----------------------------------------------------------------------
    def initOmEngine(self):
        """初始化引擎"""
        path = os.path.abspath(os.path.dirname(__file__))
        fileName = unicode(self.comboSettingFile.currentText())
        fileName = os.path.join(path, fileName)
        result = self.omEngine.initEngine(fileName)
        
        if result:
            self.writeLog(u'引擎初始化成功')
            self.enableButtons()
        else:
            self.writeLog(u'请勿重复初始化引擎')
    
    #----------------------------------------------------------------------
    def enableButtons(self):
        """启用按钮"""
        self.comboSettingFile.setDisabled(True)
        self.buttonInit.setDisabled(True)
        
        self.buttonManualTrader.setEnabled(True)
        self.buttonGreeksMonitor.setEnabled(True)
        self.buttonVolatilityChart.setEnabled(True)
        self.buttonVolatilityManager.setEnabled(True)
        
    #----------------------------------------------------------------------
    def writeLog(self, content, time=''):
        """记录日志"""
        if not time:
            time = datetime.now().strftime('%H:%M:%S')
        content = time + '\t' + content
        self.logMonitor.append(content)
    
    #----------------------------------------------------------------------
    def processLogEvent(self, event):
        """处理日志事件"""
        log = event.dict_['data']
        self.writeLog(log.logContent, log.logTime)
        self.raise_()
    
    #----------------------------------------------------------------------
    def openManualTrader(self):
        """打开手动交易组件"""
        try:
            self.widgetDict['manualTrader'].showMaximized()
        except KeyError:
            self.widgetDict['manualTrader'] = ManualTrader(self.omEngine)
            self.widgetDict['manualTrader'].showMaximized()
            
    #----------------------------------------------------------------------
    def openGreeksMonitor(self):
        """打开希腊值监控组件"""
        try:
            self.widgetDict['greeksMonitor'].showMaximized()
        except KeyError:
            self.widgetDict['greeksMonitor'] = GreeksMonitor(self.omEngine)
            self.widgetDict['greeksMonitor'].showMaximized()   
            
    #----------------------------------------------------------------------
    def openVolatilityChart(self):
        """打开波动率图表组件"""
        try:
            self.widgetDict['volatilityChart'].showMaximized()
        except KeyError:
            self.widgetDict['volatilityChart'] = VolatilityChart(self.omEngine)
            self.widgetDict['volatilityChart'].showMaximized()
    
    #----------------------------------------------------------------------
    def openVolatilityManager(self):
        """打开波动率管理组件"""
        try:
            self.widgetDict['volatilityManager'].show()
        except KeyError:
            self.widgetDict['volatilityManager'] = VolatilityManager(self.omEngine)
            self.widgetDict['volatilityManager'].show()       

    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        for widget in self.widgetDict.values():
            widget.close()
            
        super(OmManager, self).close()
        
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.processLogEvent)
        
        self.eventEngine.register(EVENT_OM_LOG, self.signal.emit)
