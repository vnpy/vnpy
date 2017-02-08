# encoding: UTF-8

'''
行情记录模块相关的GUI控制组件
'''

import json

from PyQt4.QtCore import QObject

from dataRecorder.drEngine import DrEngine
from dataRecorder.uiDrEdit import DrEditWidget
from eventEngine import *
from uiBasicWidget import QtGui, QtCore


########################################################################
class TableCell(QtGui.QTableWidgetItem):
    """居中的单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(TableCell, self).__init__()
        self.data = None
        self.setTextAlignment(QtCore.Qt.AlignCenter)
        if text:
            self.setContent(text)
    
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        if text == '0' or text == '0.0':
            self.setText('')
        else:
            self.setText(text)


########################################################################
class DrEngineManager(QtGui.QWidget):
    """行情数据记录引擎管理组件"""
    signal = QtCore.pyqtSignal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(DrEngineManager, self).__init__(parent)

        self.mainEngine = mainEngine
        self.drEngine = mainEngine.drEngine
        self.eventEngine = eventEngine

        self.initUi()
        self.updateSetting()
        self.registerEvent()

    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'行情数据记录工具')

        # 记录合约配置监控
        tickLabel = QtGui.QLabel(u'Tick记录')
        self.tickTable = QtGui.QTableWidget()
        self.tickTable.setColumnCount(2)
        self.tickTable.verticalHeader().setVisible(False)
        self.tickTable.setEditTriggers(QtGui.QTableWidget.NoEditTriggers)
        self.tickTable.horizontalHeader().setResizeMode(QtGui.QHeaderView.Stretch)
        self.tickTable.setAlternatingRowColors(True)
        self.tickTable.setHorizontalHeaderLabels([u'合约代码', u'接口'])

        barLabel = QtGui.QLabel(u'Bar记录')
        self.barTable = QtGui.QTableWidget()
        self.barTable.setColumnCount(2)
        self.barTable.verticalHeader().setVisible(False)
        self.barTable.setEditTriggers(QtGui.QTableWidget.NoEditTriggers)
        self.barTable.horizontalHeader().setResizeMode(QtGui.QHeaderView.Stretch)
        self.barTable.setAlternatingRowColors(True)
        self.barTable.setHorizontalHeaderLabels([u'合约代码', u'接口'])

        activeLabel = QtGui.QLabel(u'主力合约')
        self.activeTable = QtGui.QTableWidget()
        self.activeTable.setColumnCount(2)
        self.activeTable.verticalHeader().setVisible(False)
        self.activeTable.setEditTriggers(QtGui.QTableWidget.NoEditTriggers)
        self.activeTable.horizontalHeader().setResizeMode(QtGui.QHeaderView.Stretch)
        self.activeTable.setAlternatingRowColors(True)
        self.activeTable.setHorizontalHeaderLabels([u'主力代码', u'合约代码'])

        # 日志监控
        self.logMonitor = QtGui.QTextEdit()
        self.logMonitor.setReadOnly(True)
        self.logMonitor.setMinimumHeight(600)

        # 设置布局
        grid = QtGui.QGridLayout()

        grid.addWidget(tickLabel, 0, 0)
        grid.addWidget(barLabel, 0, 1)
        grid.addWidget(activeLabel, 0, 2)
        grid.addWidget(self.tickTable, 1, 0)
        grid.addWidget(self.barTable, 1, 1)
        grid.addWidget(self.activeTable, 1, 2)

        btnEdit = QtGui.QPushButton(u'编辑', self)
        btnRestart = QtGui.QPushButton(u'更新数据', self)

        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(grid)

        vline = QtGui.QHBoxLayout()
        vline.addWidget(btnEdit)
        vline.addWidget(btnRestart)

        vbox.addLayout(vline)
        vbox.addWidget(self.logMonitor)
        self.setLayout(vbox)

        btnEdit.clicked.connect(self.openDr)
        btnRestart.clicked.connect(self.restart)

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
        self.eventEngine.register(EVENT_DATARECORDER_LOG, self.signal.emit)

    #----------------------------------------------------------------------
    def updateSetting(self):
        """显示引擎行情记录配置"""

        self.tickTable.clearContents()
        self.tickTable.setRowCount(0)
        self.barTable.clearContents()
        self.barTable.setRowCount(0)
        self.activeTable.clearContents()
        self.activeTable.setRowCount(0)

        with open(self.drEngine.settingFileName) as f:
            drSetting = json.load(f)

            if 'tick' in drSetting:
                l = drSetting['tick']

                for setting in l:
                    self.tickTable.insertRow(0)
                    self.tickTable.setItem(0, 0, TableCell(setting[0]))
                    self.tickTable.setItem(0, 1, TableCell(setting[1]))

            if 'bar' in drSetting:
                l = drSetting['bar']

                for setting in l:
                    self.barTable.insertRow(0)
                    self.barTable.setItem(0, 0, TableCell(setting[0]))
                    self.barTable.setItem(0, 1, TableCell(setting[1]))

            if 'active' in drSetting:
                d = drSetting['active']

                for activeSymbol, symbol in d.items():
                    self.activeTable.insertRow(0)
                    self.activeTable.setItem(0, 0, TableCell(activeSymbol))
                    self.activeTable.setItem(0, 1, TableCell(symbol))

    # ----------------------------------------------------------------------
    def openDr(self):
        """打开行情数据记录组件"""
        self.mDrEditWidget = DrEditWidget(self,self.mainEngine, self.eventEngine)
        self.mDrEditWidget.setFixedSize(800,800)
        self.mDrEditWidget.show()

    def restart(self):
        self.drEngine.stop()
        self.updateSetting()
        self.mainEngine.drEngine = DrEngine(self.mainEngine, self.mainEngine.eventEngine)
