# encoding: UTF-8

'''
行情记录模块相关的GUI控制组件
'''
from PyQt4.QtCore import QDir
from PyQt4.QtGui import QFileSystemModel
from PyQt4.QtGui import QTreeView

from dataRecorder.drEngine import DrEngine
from uiBasicWidget import QtGui, QtCore
from eventEngine import *

from eventType import EVENT_CONTRACT


class TreeItem(object):
	def __init__(self, data, parent=None):
		self.parentItem = parent
		self.itemData = data
		self.childItems = []

	def appendChild(self, item):
		self.childItems.append(item)

	def extendChild(self, item):
		self.childItems.extend(item)

	def child(self, row):
		return self.childItems[row]

	def childCount(self):
		return len(self.childItems)

	def columnCount(self):
		return len(self.itemData)

	def data(self, column):
		try:
			return self.itemData[column]
		except IndexError:
			return None

	def parent(self):
		return self.parentItem

	def row(self):
		if self.parentItem:
			return self.parentItem.childItems.index(self)

		return 0


class TreeModel(QtCore.QAbstractItemModel):
	def __init__(self, parent=None):
		super(TreeModel, self).__init__(parent)
		self.rootItem = TreeItem((u"合约", u"tick", u"bar", u"主力"))

	def rootItem(self):
		return self.rootItem

	def setDataSource(self, data):
		self.rootItem.extendChild(data)

	def columnCount(self, parent):
		if parent.isValid():
			return parent.internalPointer().columnCount()
		else:
			return self.rootItem.columnCount()

	# def setData(self, index, value, role=None):
	# 	item = index.internalPointer()
	# 	if index.column != 0 and role == QtCore.Qt.CheckStateRole:
	# 		if value:
	# 			item.setCheckState(QtCore.Qt.checked)
	# 		else:
	# 			item.setCheckState(QtCore.Qt.Unchecked)
	# 	else:
	# 		pass
	# 	return True

	def data(self, index, role):
		if not index.isValid():
			return None

		item = index.internalPointer()

		if role == QtCore.Qt.CheckStateRole and index.column() != 0:
			return QtCore.Qt.Checked if item.data(index.column()) == True else QtCore.Qt.Unchecked

		if role != QtCore.Qt.DisplayRole:
			return None

		return item.data(index.column())

	def flags(self, index):
		if not index.isValid():
			return QtCore.Qt.NoItemFlags

		if index.column() == 0 or index.row() == 0:
			return QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable

		return QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable | QtCore.Qt.ItemIsUserCheckable

	def headerData(self, section, orientation, role):
		if orientation == QtCore.Qt.Horizontal and role == QtCore.Qt.DisplayRole:
			return self.rootItem.data(section)

		return None

	def index(self, row, column, parent):
		if not self.hasIndex(row, column, parent):
			return QtCore.QModelIndex()

		if not parent.isValid():
			parentItem = self.rootItem
		else:
			parentItem = parent.internalPointer()

		childItem = parentItem.child(row)
		if childItem:
			return self.createIndex(row, column, childItem)
		else:
			return QtCore.QModelIndex()

	def parent(self, index):
		if not index.isValid():
			return QtCore.QModelIndex()

		childItem = index.internalPointer()
		parentItem = childItem.parent()

		if parentItem == self.rootItem:
			return QtCore.QModelIndex()

		return self.createIndex(parentItem.row(), 0, parentItem)

	def rowCount(self, parent):
		if parent.column() > 0:
			return 0

		if not parent.isValid():
			parentItem = self.rootItem
		else:
			parentItem = parent.internalPointer()

		return parentItem.childCount()


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

		model = TreeModel()

		self.qTreeView.setModel(model)
		# self.qTreeView.setRootIndex(model.index())

		child = []
		yumi = TreeItem((u"玉米", False, False, False), model.rootItem)
		yumi.appendChild(TreeItem((u"c1705", False, False, False), yumi))
		yumi.appendChild(TreeItem((u"c1703", False, False, False), yumi))
		yumi.appendChild(TreeItem((u"c1707", False, False, False), yumi))
		yumi.appendChild(TreeItem((u"c1709", False, False, False), yumi))
		dianfen = TreeItem((u"淀粉", False, False, False), model.rootItem)
		dianfen.appendChild(TreeItem((u"d1705", False, False, False), dianfen))
		dianfen.appendChild(TreeItem((u"d1703", False, False, False), dianfen))
		dianfen.appendChild(TreeItem((u"d1707", False, False, False), dianfen))
		dianfen.appendChild(TreeItem((u"d1709", False, False, False), dianfen))

		child.append(yumi)
		child.append(dianfen)
		model.setDataSource(child)

		vbox = QtGui.QVBoxLayout()

		vline = QtGui.QHBoxLayout()
		vline.setSpacing(2)
		btnTickAll = QtGui.QPushButton(u"全部记录tick", self)
		btnBarAll = QtGui.QPushButton(u'全部记录bar', self)
		vline.addWidget(btnTickAll)
		vline.addWidget(btnBarAll)
		vbox.addLayout(vline)
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

	# self.eventEngine.register(EVENT_CONTRACT, self.signal.emit)


if __name__ == '__main__':
	import sys

	app = QtGui.QApplication(sys.argv)

	view = DrEditWidget(DrEngine, EventEngine)
	view.showMaximized()
	sys.exit(app.exec_())
