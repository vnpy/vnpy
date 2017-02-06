# encoding: UTF-8

'''
行情记录模块相关的GUI控制组件
'''
from PyQt4.QtCore import QDir
from PyQt4.QtGui import QFileSystemModel
from PyQt4.QtGui import QTreeView

from uiBasicWidget import QtGui, QtCore
from eventEngine import *

from eventType import EVENT_CONTRACT


class DrEditWidget(QtGui.QWidget):
    """行情数据记录引擎管理组件"""
    signal = QtCore.pyqtSignal(type(Event()))

    def __init__(self, drEngine, eventEngine, parent=None):
        """Constructor"""
        super(DrEditWidget, self).__init__(parent)

        self.drEngine = drEngine
        self.eventEngine = eventEngine

        # 保存合约详细信息的字典
        self.contractDict = {}

        self.initUi()
        self.updateSetting()
        self.registerEvent()

    def initUi(self):
        self.qTreeView = QTreeView()
        model = QFileSystemModel()
        model.setRootPath(QDir.currentPath())
        self.qTreeView.setModel(model)
        self.qTreeView.setRootIndex(model.index(QDir.currentPath()))

        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(self.qTreeView)
        self.setLayout(vbox)

    def updateSetting(self):
        pass

    def updateContract(self, event):
        """更新合约数据"""
        contract = event.dict_['data']
        self.contractDict[contract.vtSymbol] = contract
        self.contractDict[contract.symbol] = contract  # 使用常规代码（不包括交易所）可能导致重复

    # ----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateContract)
        self.eventEngine.register(EVENT_CONTRACT, self.signal.emit)
