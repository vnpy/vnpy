# encoding: UTF-8

import csv
import traceback
from collections import OrderedDict

from six import text_type

from vnpy.event import Event
from vnpy.trader.uiQt import QtCore, QtWidgets

from .algoEngine import (EVENT_ALGO_LOG, EVENT_ALGO_PARAM, 
                         EVENT_ALGO_VAR, EVENT_ALGO_SETTING)
from .algo import WIDGET_DICT



########################################################################
class StopButton(QtWidgets.QPushButton):
    """停止算法用按钮"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, algoName=''):
        """Constructor"""
        super(StopButton, self).__init__()
        
        self.algoEngine = algoEngine
        self.algoName = algoName
        
        self.setStyleSheet("color:black;background-color:yellow")
        
        if algoName:
            self.setText(u'停止')
            self.clicked.connect(self.stopAlgo)
        else:
            self.setText(u'停止全部算法')
            self.clicked.connect(self.stopAll)
    
    #----------------------------------------------------------------------
    def stopAlgo(self):
        """停止某一算法"""
        self.algoEngine.stopAlgo(self.algoName)
        self.disable()
    
    #----------------------------------------------------------------------
    def stopAll(self):
        """停止全部算法"""
        self.algoEngine.stopAll()
    
    #----------------------------------------------------------------------
    def disable(self):
        """禁用按钮"""
        self.setEnabled(False)
        self.setStyleSheet("color:black;background-color:grey")


AlgoCell = QtWidgets.QTableWidgetItem


########################################################################
class AlgoStatusMonitor(QtWidgets.QTableWidget):
    """算法状态监控"""
    signalParam = QtCore.Signal(type(Event()))
    signalVar = QtCore.Signal(type(Event()))
    
    MODE_WORKING = 'working'
    MODE_HISTORY = 'history'

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, mode):
        """Constructor"""
        super(AlgoStatusMonitor, self).__init__()
        
        self.algoEngine = algoEngine
        self.eventEngine = algoEngine.eventEngine
        self.mode = mode
        
        self.cellDict = {}
        
        self.initUi()
        self.registerEvent()
    
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        labels = [u'',
                  u'名称',
                  u'参数',
                  u'变量']
        
        self.setColumnCount(len(labels))
        self.setHorizontalHeaderLabels(labels)
        self.setRowCount(0)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
        self.setAlternatingRowColors(True)
        
        if self.mode == self.MODE_HISTORY:
            self.hideColumn(0)

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signalParam.connect(self.processParamEvent)
        self.signalVar.connect(self.processVarEvent)
        
        self.eventEngine.register(EVENT_ALGO_PARAM, self.signalParam.emit)
        self.eventEngine.register(EVENT_ALGO_VAR, self.signalVar.emit)
    
    #----------------------------------------------------------------------
    def addAlgo(self, algoName):
        """新增算法"""
        self.insertRow(0)
        
        buttonStop = StopButton(self.algoEngine, algoName)
        cellName = AlgoCell(algoName)
        cellParam = AlgoCell()
        cellVar = AlgoCell()
        
        self.setCellWidget(0, 0, buttonStop)
        self.setItem(0, 1, cellName)
        self.setItem(0, 2, cellParam)
        self.setItem(0, 3, cellVar)
        
        self.cellDict[algoName] = {
            'param': cellParam,
            'var': cellVar,
            'button': buttonStop
        }
        
        if self.mode == self.MODE_HISTORY:
            self.hideRow(0)
        
    #----------------------------------------------------------------------
    def processParamEvent(self, event):
        """处理参数事件"""
        d = event.dict_['data']
        
        algoName = d['algoName']
        if algoName not in self.cellDict:
            self.addAlgo(algoName)
        
        text = self.generateText(d)
        cell = self.cellDict[algoName]['param']
        cell.setText(text)

        self.resizeColumnsToContents()
        
    #----------------------------------------------------------------------
    def processVarEvent(self, event):
        """处理变量事件"""
        d = event.dict_['data']
        
        algoName = d['algoName']
        if algoName not in self.cellDict:
            self.addAlgo(algoName)
            
        if 'active' in d:
            active = d['active']
            
            # 若算法已经结束
            if not active:
                # 禁用按钮
                cells = self.cellDict[algoName]
                button = cells['button']
                button.disable()
                
                # 根据模式决定显示或者隐藏该行
                cell = cells['var']
                row = self.row(cell)
                if self.mode == self.MODE_WORKING:
                    self.hideRow(row)
                else:
                    self.showRow(row)
        
        text = self.generateText(d)
        cell = self.cellDict[algoName]['var']
        cell.setText(text)
        
        self.resizeColumnsToContents()
    
    #----------------------------------------------------------------------
    def generateText(self, d):
        """从字典生成字符串"""
        l = []
        for k, v in d.items():
            if k not in ['algoName']:
                msg = u'%s:%s' %(k, v)
                l.append(msg)
        text = ','.join(l)        
        return text


########################################################################
class AlgoLogMonitor(QtWidgets.QTextEdit):
    """"""
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, algoEngine):
        """Constructor"""
        super(AlgoLogMonitor, self).__init__()
        
        self.eventEngine = algoEngine.eventEngine
        
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.signal.connect(self.processEvent)
        
        self.eventEngine.register(EVENT_ALGO_LOG, self.signal.emit)
        
    #----------------------------------------------------------------------
    def processEvent(self, event):
        """"""
        log = event.dict_['data']
        if not log.gatewayName:
            log.gatewayName = u'算法引擎'
        msg = u'%s\t%s：%s' %(log.logTime, log.gatewayName, log.logContent)
        self.append(msg)


########################################################################
class StartButton(QtWidgets.QPushButton):
    """基于配置启动算法用按钮"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, setting):
        """Constructor"""
        super(StartButton, self).__init__()
        
        self.algoEngine = algoEngine
        self.setting = setting
        
        self.setStyleSheet("color:black;background-color:green")
        self.setText(u'启动')
        
        self.clicked.connect(self.startAlgo)
        
    #----------------------------------------------------------------------
    def startAlgo(self):
        """启动算法"""
        self.algoEngine.addAlgo(self.setting)
    
    #----------------------------------------------------------------------
    def updateSetting(self, setting):
        """更新配置"""
        self.setting = setting
    

########################################################################
class DeleteButton(QtWidgets.QPushButton):
    """删除算法用按钮"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, setting):
        """Constructor"""
        super(DeleteButton, self).__init__()
        
        self.algoEngine = algoEngine
        self.setting = setting
        
        self.setStyleSheet("color:black;background-color:red")
        self.setText(u'删除')
        
        self.clicked.connect(self.deleteAlgoSetting)
        
    #----------------------------------------------------------------------
    def deleteAlgoSetting(self):
        """删除算法配置"""
        self.algoEngine.deleteAlgoSetting(self.setting)
    
    #----------------------------------------------------------------------
    def updateSetting(self, setting):
        """更新配置"""
        self.setting = setting
    

########################################################################
class AlgoSettingMonitor(QtWidgets.QTableWidget):
    """"""
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, algoEngine):
        """Constructor"""
        super(AlgoSettingMonitor, self).__init__()
        
        self.algoEngine = algoEngine
        self.eventEngine = algoEngine.eventEngine
        
        self.cellDict = {}
        
        self.initUi()
        self.registerEvent()
    
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        labels = ['',
                  '',
                  u'名称',
                  u'算法',
                  u'参数']
        
        self.setColumnCount(len(labels))
        self.setHorizontalHeaderLabels(labels)
        self.setRowCount(0)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)   

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.processEvent)
        
        self.eventEngine.register(EVENT_ALGO_SETTING, self.signal.emit)
    
    #----------------------------------------------------------------------
    def processEvent(self, event):
        """处理事件"""
        setting = event.dict_['data']
        settingName = setting['settingName']
        
        # 删除配置行
        if len(setting) == 1:
            d = self.cellDict.pop(settingName)
            cell = d['text']
            row = self.row(cell)
            self.removeRow(row)
        # 新增配置行
        elif settingName not in self.cellDict:
            self.insertRow(0)
        
            buttonStart = StartButton(self.algoEngine, setting)
            buttonDelete = DeleteButton(self.algoEngine, setting)
            cellSettingName = AlgoCell(settingName)
            cellTemplateName = AlgoCell(setting['templateName'])
            cellSettingText = AlgoCell(self.generateText(setting))
            
            self.setCellWidget(0, 0, buttonStart)
            self.setCellWidget(0, 1, buttonDelete)
            self.setItem(0, 2, cellSettingName)
            self.setItem(0, 3, cellTemplateName)
            self.setItem(0, 4, cellSettingText)
            
            self.cellDict[settingName] = {
                'start': buttonStart,
                'template': cellTemplateName,
                'text': cellSettingText,
                'delete': buttonDelete
            }
        # 更新已有配置行
        else:
            d = self.cellDict[settingName]
            d['start'].updateSetting(setting)
            d['template'].setText(setting['templateName'])
            d['text'].setText(self.generateText(setting))
            d['delete'].updateSetting(setting)
        
        self.resizeColumnsToContents()
    
    #----------------------------------------------------------------------
    def generateText(self, d):
        """从字典生成字符串"""
        l = []
        for k, v in d.items():
            if k not in ['settingName', 'templateName', '_id']:
                msg = u'%s:%s' %(k, v)
                l.append(msg)
        text = ','.join(l)
        return text


########################################################################
class AlgoManager(QtWidgets.QWidget):
    """算法交易管理组件"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, eventEngine, parent=None):
        """Constructor"""
        super(AlgoManager, self).__init__(parent)
        
        self.algoEngine = algoEngine
        self.eventEngine = eventEngine
        
        self.widgetDict = {}
        
        self.initUi()
        self.changeWidget()
        self.algoEngine.loadAlgoSetting()   # 界面初始化后，再加载算法配置
        
    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'算法交易')
        
        #buttonWidth = 400
        #buttonHeight = 60        
        
        self.comboTemplate = QtWidgets.QComboBox()
        #self.comboTemplate.setMaximumWidth(buttonWidth)
        self.comboTemplate.currentIndexChanged.connect(self.changeWidget)
        
        vbox = QtWidgets.QVBoxLayout()
        for templateName, widgetClass in WIDGET_DICT.items():
            widget = widgetClass(self.algoEngine)
            #widget.setMaximumWidth(buttonWidth)
            widget.hide()
            vbox.addWidget(widget)
            
            self.widgetDict[templateName] = widget
            self.comboTemplate.addItem(templateName)
        
        self.buttonStop = StopButton(self.algoEngine)
        
        self.buttonAddAlgo = QtWidgets.QPushButton(u'启动篮子算法')
        self.buttonAddAlgo.setStyleSheet("color:white;background-color:green")
        self.buttonAddAlgo.clicked.connect(self.addAlgoFromCsv)
        
        self.buttonSaveSetting = QtWidgets.QPushButton(u'加载算法配置')
        self.buttonSaveSetting.setStyleSheet("color:white;background-color:blue")
        self.buttonSaveSetting.clicked.connect(self.saveSettingFromCsv)
        
        self.lineRepPort = QtWidgets.QLineEdit('8899')
        self.linePubPort = QtWidgets.QLineEdit('9988')
        
        self.buttonStartRpc = QtWidgets.QPushButton(u'启动RPC服务')
        self.buttonStartRpc.setStyleSheet("color:black;background-color:orange")
        self.buttonStartRpc.clicked.connect(self.startRpc)
        
        label = QtWidgets.QLabel(u'算法类型')
        label.setFixedWidth(100)
        
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(label)
        hbox.addWidget(self.comboTemplate)
        
        grid = QtWidgets.QGridLayout()
        grid.addWidget(QtWidgets.QLabel(u'REP端口'), 0, 0)
        grid.addWidget(self.lineRepPort, 0, 1)
        grid.addWidget(QtWidgets.QLabel(u'PUB端口'), 1, 0)
        grid.addWidget(self.linePubPort, 1, 1)
        
        vbox1 = QtWidgets.QVBoxLayout()
        vbox1.addLayout(hbox)
        vbox1.addLayout(vbox)
        vbox1.addStretch()
        vbox1.addWidget(self.buttonStop)
        vbox1.addWidget(self.buttonAddAlgo)
        vbox1.addWidget(self.buttonSaveSetting)
        vbox1.addStretch()
        vbox1.addLayout(grid)
        vbox1.addWidget(self.buttonStartRpc)
        
        workingMonitor = AlgoStatusMonitor(self.algoEngine, AlgoStatusMonitor.MODE_WORKING)
        workingMonitor.setFixedWidth(1500)
        
        historyMonitor = AlgoStatusMonitor(self.algoEngine, AlgoStatusMonitor.MODE_HISTORY)
        logMonitor = AlgoLogMonitor(self.algoEngine)        
        settingMonitor = AlgoSettingMonitor(self.algoEngine)
        
        tab1 = QtWidgets.QTabWidget()
        tab1.addTab(workingMonitor, u'运行中')
        tab1.addTab(historyMonitor, u'已结束')
        
        tab2 = QtWidgets.QTabWidget()
        tab2.addTab(logMonitor, u'日志信息')
        
        tab3 = QtWidgets.QTabWidget()
        tab3.addTab(settingMonitor, u'算法配置')
        
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(tab2)
        hbox.addWidget(tab3)
        
        vbox2 = QtWidgets.QVBoxLayout()
        vbox2.addWidget(tab1)
        vbox2.addLayout(hbox)
        
        hbox2 = QtWidgets.QHBoxLayout()
        hbox2.addLayout(vbox1)
        hbox2.addLayout(vbox2)
        
        self.setLayout(hbox2)
    
    #----------------------------------------------------------------------
    def changeWidget(self):
        """"""
        for widget in self.widgetDict.values():
            widget.hide()
            
        templateName = text_type(self.comboTemplate.currentText())
        widget = self.widgetDict[templateName]
        widget.show()
    
    #----------------------------------------------------------------------
    def addAlgoWidget(self, widgetClass):
        """添加算法控制组件 """
        w = widgetClass(self.algoEngine)
        self.tab.addTab(w, w.templateName)
    
    #----------------------------------------------------------------------
    def loadCsv(self, path):
        """读取CSV配置文件"""
        try:
            with open(text_type(path)) as f:
                buf = [line.encode('UTF-8') for line in f]
            
            reader = csv.DictReader(buf)
            l = []
            
            for d in reader:
                setting = OrderedDict()    
                for name in reader.fieldnames:
                    setting[str(name)] = d[name]
                l.append(setting)
            
            return l
        
        except:
            msg = traceback.format_exc()
            self.algoEngine.writeLog(u'读取CSV文件失败：\n' + msg)
            return []
    
    #----------------------------------------------------------------------
    def saveSettingFromCsv(self):
        """从CSV加载配置到数据库"""
        path, fileType = QtWidgets.QFileDialog.getOpenFileName(self, u'加载算法配置', '', 'CSV(*.csv)')
        l = self.loadCsv(path)
        for setting in l:
            self.algoEngine.saveAlgoSetting(setting)
    
    #----------------------------------------------------------------------
    def addAlgoFromCsv(self):
        """从CSV启动一篮子算法"""
        path, fileType = QtWidgets.QFileDialog.getOpenFileName(self, u'启动篮子算法', '', 'CSV(*.csv)        ')
        l = self.loadCsv(path)
        for setting in l:
            self.algoEngine.addAlgo(setting)
    
    #----------------------------------------------------------------------
    def startRpc(self):
        """启动算法服务"""
        try:
            repPort = int(self.lineRepPort.text())
            pubPort = int(self.linePubPort.text())
        except:
            self.algoEngine.writeLog(u'请检查RPC端口，只能使用整数')
            return
        
        self.algoEngine.startRpc(repPort, pubPort)
    
    #----------------------------------------------------------------------
    def show(self):
        """"""
        self.showMaximized()
        
        
