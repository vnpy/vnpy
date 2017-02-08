# encoding: UTF-8

'''
行情记录模块相关的GUI控制组件
'''
from PyQt4.QtGui import QTreeView

from dataRecorder.drEngine import DrEngine
from eventEngine import *
from uiBasicWidget import QtGui, QtCore


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

	def setData(self, column, value):
		if column < 0 or column >= len(self.itemData):
			return False

		self.itemData[column] = value

		return True


class TreeModel(QtCore.QAbstractItemModel):
	def __init__(self, parent=None):
		super(TreeModel, self).__init__(parent)
		self.rootItem = TreeItem([u"合约", u"Tick", u"Bar", u"主力"])

	def rootItem(self):
		return self.rootItem

	def setDataSource(self, data):
		self.rootItem.extendChild(data)

	def columnCount(self, parent):
		if parent.isValid():
			return parent.internalPointer().columnCount()
		else:
			return self.rootItem.columnCount()

	def setData(self, index, value, role=None):
		if index.column() != 0 and role == QtCore.Qt.CheckStateRole:
			item = index.internalPointer()
			if item is None:
				return False
			result = item.setData(index.column(), True if value == QtCore.Qt.Checked else False)
			if result:
				self.dataChanged.emit(index, index)

			# 如果第一条
			if item.parentItem == self.rootItem:
				for row in range(item.childCount()):
					childIndex = self.index(row, index.column(), index)
					self.setData(childIndex, value, QtCore.Qt.CheckStateRole)

			if value == QtCore.Qt.Checked and index.column() == 3:
				for row in range(item.parentItem.childCount()):
					if row != index.row():
						siblingIndex = self.index(row, index.column(), index.parent())
						self.setData(siblingIndex, QtCore.Qt.Unchecked, QtCore.Qt.CheckStateRole)

		return True

	def data(self, index, role):
		if not index.isValid():
			return None

		item = index.internalPointer()

		if role == QtCore.Qt.CheckStateRole and index.column() != 0:
			return QtCore.Qt.Checked if item.data(index.column()) == True else QtCore.Qt.Unchecked

		if index.column() == 3 and item.parentItem == self.rootItem:
			return None

		if role != QtCore.Qt.DisplayRole:
			return None

		return item.data(index.column())

	def flags(self, index):
		if not index.isValid():
			return QtCore.Qt.NoItemFlags

		if index.column() == 0:
			return QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable

		item = index.internalPointer()
		if index.column() == 3 and item.parentItem == self.rootItem:
			return QtCore.Qt.NoItemFlags

		return QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable | QtCore.Qt.ItemIsUserCheckable

	def headerData(self, section, orientation, role):
		if orientation == QtCore.Qt.Horizontal and role == QtCore.Qt.DisplayRole:
			return self.rootItem.data(section)

		return None

	def index(self, row, column, parent):
		if not self.hasIndex(row, column, parent):
			return QtCore.QModelIndex()

		if parent is None or not parent.isValid():
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

	def hasIndex(self, row, column, parentIndex=None, *args, **kwargs):
		if row < 0 or column > 4:
			return False
		return True


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
		self.loadData()
		self.registerEvent()

	def initUi(self):

		vbox = QtGui.QVBoxLayout()

		vline = QtGui.QHBoxLayout()
		vline.setSpacing(2)
		btnTickAll = QtGui.QPushButton(u"全部记录tick", self)
		btnBarAll = QtGui.QPushButton(u'全部记录bar', self)
		btnTickAll.clicked.connect(self.selectAllTick)
		btnBarAll.clicked.connect(self.selectAllBar)

		vline.addWidget(btnTickAll)
		vline.addWidget(btnBarAll)

		vbox.addLayout(vline)

		self.qTreeView = QTreeView()
		self.model = TreeModel()
		self.qTreeView.setModel(self.model)

		vbox.addWidget(self.qTreeView)
		self.setLayout(vbox)

	def loadData(self):
		child = []
		yumi = TreeItem([u"玉米", False, False, False], self.model.rootItem)
		yumi.appendChild(TreeItem([u"c1705", False, False, False], yumi))
		yumi.appendChild(TreeItem([u"c1703", False, False, False], yumi))
		yumi.appendChild(TreeItem([u"c1707", False, False, False], yumi))
		yumi.appendChild(TreeItem([u"c1709", False, False, False], yumi))
		dianfen = TreeItem([u"淀粉", False, False, False], self.model.rootItem)
		dianfen.appendChild(TreeItem([u"d1705", False, False, False], dianfen))
		dianfen.appendChild(TreeItem([u"d1703", False, False, False], dianfen))
		dianfen.appendChild(TreeItem([u"d1707", False, False, False], dianfen))
		dianfen.appendChild(TreeItem([u"d1709", False, False, False], dianfen))

		child.append(yumi)
		child.append(dianfen)
		self.model.setDataSource(child)
		self.qTreeView.expandAll()

	def selectAllTick(self):
		self.selectAll(True, False, True)

	def selectAllBar(self):
		self.selectAll(False, True, True)

	def selectAll(self, tick=False, bar=False, select=False):
		column = None
		if tick:
			column = 1
		if bar:
			column = 2

		for row in range(self.model.rootItem.childCount()):
			childIndex = self.model.index(row, column, None)
			self.model.setData(childIndex, QtCore.Qt.Unchecked if select == False else QtCore.Qt.Checked,
			                   QtCore.Qt.CheckStateRole)

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
	view.setFixedSize(500, 500)
	view.show()
	sys.exit(app.exec_())
