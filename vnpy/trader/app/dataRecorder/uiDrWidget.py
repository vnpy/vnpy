# encoding: UTF-8

'''
行情记录模块相关的GUI控制组件
'''

from vnpy.event import Event
from vnpy.trader.uiQt import QtWidgets, QtCore
from .drBase import EVENT_DATARECORDER_LOG
from .language import text


########################################################################
class TableCell(QtWidgets.QTableWidgetItem):
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
class DrEngineManager(QtWidgets.QWidget):
    """行情数据记录引擎管理组件"""
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, drEngine, eventEngine, parent=None):
        """Constructor"""
        super(DrEngineManager, self).__init__(parent)
        
        self.drEngine = drEngine
        self.eventEngine = eventEngine
        
        self.initUi()
        self.updateSetting()
        self.registerEvent() 
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(text.DATA_RECORDER)
        
        # 记录合约配置监控
        tickLabel = QtWidgets.QLabel(text.TICK_RECORD)
        self.tickTable = QtWidgets.QTableWidget()
        self.tickTable.setColumnCount(2)
        self.tickTable.verticalHeader().setVisible(False)
        self.tickTable.setEditTriggers(QtWidgets.QTableWidget.NoEditTriggers)
        self.tickTable.setAlternatingRowColors(True)
        self.tickTable.setHorizontalHeaderLabels([text.CONTRACT_SYMBOL, text.GATEWAY])
        
        barLabel = QtWidgets.QLabel(text.BAR_RECORD)
        self.barTable = QtWidgets.QTableWidget()
        self.barTable.setColumnCount(2)
        self.barTable.verticalHeader().setVisible(False)
        self.barTable.setEditTriggers(QtWidgets.QTableWidget.NoEditTriggers)
        self.barTable.setAlternatingRowColors(True)        
        self.barTable.setHorizontalHeaderLabels([text.CONTRACT_SYMBOL, text.GATEWAY])

        activeLabel = QtWidgets.QLabel(text.DOMINANT_CONTRACT)
        self.activeTable = QtWidgets.QTableWidget()
        self.activeTable.setColumnCount(2)
        self.activeTable.verticalHeader().setVisible(False)
        self.activeTable.setEditTriggers(QtWidgets.QTableWidget.NoEditTriggers)
        self.activeTable.setAlternatingRowColors(True)        
        self.activeTable.setHorizontalHeaderLabels([text.DOMINANT_SYMBOL, text.CONTRACT_SYMBOL])

        # 日志监控
        self.logMonitor = QtWidgets.QTextEdit()
        self.logMonitor.setReadOnly(True)
        self.logMonitor.setMinimumHeight(600)
        
        # 设置布局
        grid = QtWidgets.QGridLayout()
        
        grid.addWidget(tickLabel, 0, 0)
        grid.addWidget(barLabel, 0, 1)
        grid.addWidget(activeLabel, 0, 2)
        grid.addWidget(self.tickTable, 1, 0)
        grid.addWidget(self.barTable, 1, 1)
        grid.addWidget(self.activeTable, 1, 2)        
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(grid)
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
        self.eventEngine.register(EVENT_DATARECORDER_LOG, self.signal.emit)
        
    #----------------------------------------------------------------------
    def updateSetting(self):
        """显示引擎行情记录配置"""
        setting, activeSetting = self.drEngine.getSetting()
        
        for d in setting.values():
            if 'tick' in d and d['tick']:
                self.tickTable.insertRow(0)
                self.tickTable.setItem(0, 0, TableCell(d['symbol']))
                self.tickTable.setItem(0, 1, TableCell(d['gateway']))                
                
            if 'bar' in d and d['bar']:
                self.barTable.insertRow(0)
                self.barTable.setItem(0, 0, TableCell(d['symbol']))
                self.barTable.setItem(0, 1, TableCell(d['gateway'])) 

        for vtSymbol, activeSymbol in activeSetting.items():
            self.activeTable.insertRow(0)
            self.activeTable.setItem(0, 0, TableCell(activeSymbol))
            self.activeTable.setItem(0, 1, TableCell(vtSymbol))
                
        self.tickTable.resizeColumnsToContents()
        self.barTable.resizeColumnsToContents()
        self.activeTable.resizeColumnsToContents()
    
    
    
    



    
    