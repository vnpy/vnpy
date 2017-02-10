# encoding: UTF-8

'''
行情记录模块相关的GUI控制组件
'''
import json
import re
import sys

from PyQt4.QtGui import QTreeView

from dataRecorder.drEngine import DrEngine
from eventEngine import *
from uiBasicWidget import QtGui, QtCore
from util.UiUtil import CheckBoxDelegate, ComboDelegate

reload(sys)
sys.setdefaultencoding("utf8")


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
		self.rootItem = TreeItem([u"合约", u"Tick", u"Bar", u"主力", u"交易所", u"接口"])

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
		item = index.internalPointer()
		if item is None:
			return False

		if index.column() == 5:
			result = item.setData(index.column(), value)
			if result:
				self.dataChanged.emit(index, index)
			# 如果第一条
			if item.parentItem == self.rootItem:
				for row in range(item.childCount()):
					childIndex = self.index(row, index.column(), index)
					self.setData(childIndex, value, QtCore.Qt.DisplayRole)

		if index.column() in [1, 2, 3] and role == QtCore.Qt.CheckStateRole:
			result = item.setData(index.column(), True if value == QtCore.Qt.Checked else False)
			if result:
				self.dataChanged.emit(index, index)

			# 如果第一条
			if item.parentItem == self.rootItem and index.column() in [1, 2]:
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

		if role == QtCore.Qt.TextAlignmentRole:
			return QtCore.Qt.AlignCenter

		if role == QtCore.Qt.CheckStateRole and (
						index.column() in [1, 2] or index.column() == 3 and item.parentItem != self.rootItem):
			return QtCore.Qt.Checked if item.data(index.column()) == True else QtCore.Qt.Unchecked

		if role != QtCore.Qt.DisplayRole or index.column() in [3, 4] and item.parentItem == self.rootItem:
			return None

		return item.data(index.column())

	def flags(self, index):
		if not index.isValid():
			return QtCore.Qt.NoItemFlags

		if index.column() in [0, 4]:
			return QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable

		if index.column() in [5]:
			return QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable | QtCore.Qt.ItemIsEditable

		item = index.internalPointer()
		if index.column() == 3 and item.parentItem == self.rootItem:
			return QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable

		return QtCore.Qt.ItemIsEnabled | QtCore.Qt.ItemIsSelectable | QtCore.Qt.ItemIsUserCheckable | QtCore.Qt.ItemIsEditable

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
		if row < 0 or column > self.rootItem.columnCount():
			return False
		return True


class DrEditWidget(QtGui.QWidget):
	"""行情数据记录引擎管理组件"""
	signal = QtCore.pyqtSignal(type(Event()))

	def __init__(self, drWidget, mainEngine, eventEngine, parent=None):
		"""Constructor"""
		super(DrEditWidget, self).__init__(parent)
		self.drWidget = drWidget
		self.mainEngine = mainEngine
		self.eventEngine = eventEngine
		self.hasChanged = False

		# 保存合约详细信息的字典
		self.contractDict = {}

		self.initUi()
		self.updateSetting()
		self.loadData()
		self.registerEvent()

	def closeEvent(self, QCloseEvent):
		if self.hasChanged:
			self.drWidget.restart()

	def initUi(self):

		vbox = QtGui.QVBoxLayout()

		vline = QtGui.QHBoxLayout()
		vline.setSpacing(2)
		btnTickAll = QtGui.QPushButton(u"全部记录Tick", self)
		btnBarAll = QtGui.QPushButton(u'全部记录Bar', self)
		btnSaveAll = QtGui.QPushButton(u'保存设置(重启后生效)', self)
		btnTickAll.clicked.connect(self.selectAllTick)
		btnBarAll.clicked.connect(self.selectAllBar)
		btnSaveAll.clicked.connect(self.saveSetting)

		vline.addWidget(btnTickAll)
		vline.addWidget(btnBarAll)
		vline.addWidget(btnSaveAll)

		vbox.addLayout(vline)

		self.qTreeView = QTreeView()
		self.model = TreeModel()
		self.qTreeView.setModel(self.model)
		self.qTreeView.setSelectionMode(QtGui.QAbstractItemView.NoSelection)
		self.qTreeView.setItemDelegateForColumn(1, CheckBoxDelegate(self))
		self.qTreeView.setItemDelegateForColumn(2, CheckBoxDelegate(self))
		self.qTreeView.setItemDelegateForColumn(3, CheckBoxDelegate(self))
		self.qTreeView.setItemDelegateForColumn(5, ComboDelegate(self, ["CTP", "LTS", "XTP", "FEMAS", "XSPEED", "QDP",
		                                                                "KSOTP", "KSGOLD", "SGIT"]))

		vbox.addWidget(self.qTreeView)
		self.setLayout(vbox)

	def getContractChineseName(self, str):
		line = str.strip().decode('utf-8', 'ignore')  # 处理前进行相关的处理，包括转换成Unicode等
		p2 = re.compile(ur'[^\u4e00-\u9fa5]')  # 中文的编码范围是：\u4e00到\u9fa5
		zh = " ".join(p2.split(line)).strip()
		zh = ",".join(zh.split())
		outStr = zh  # 经过相关处理后得到中文的文本
		return outStr

	def loadData(self):
		child = []

		tick = {}
		bar = {}
		active = []
		with open(self.mainEngine.drEngine.settingFileName) as f:
			drSetting = json.load(f)
			if 'tick' in drSetting:
				l = drSetting['tick']

				for setting in l:
					tick[setting[0]] = setting[1]

			if 'bar' in drSetting:
				l = drSetting['bar']

				for setting in l:
					bar[setting[0]] = setting[1]

			if 'active' in drSetting:
				d = drSetting['active']

				for activeSymbol, symbol in d.items():
					active.append(symbol)

		contractDict = {}
		contracts = self.mainEngine.getAllContracts()
		for contract in contracts:
			contractName = self.getContractChineseName(contract.name)
			gateWayName = u"CTP"
			hasTick = tick.has_key(contract.symbol)
			hasBar = bar.has_key(contract.symbol)
			hasActive = contract.symbol in active
			if hasTick:
				gateWayName = tick[contract.symbol]
			elif hasBar:
				gateWayName = bar[contract.symbol]
			if contractDict.has_key(contractName):
				parentItem = contractDict[contractName]
				item = TreeItem([contract.symbol, hasTick, hasBar, hasActive, contract.exchange, gateWayName],
				                parentItem)
				parentItem.appendChild(item)
			else:
				item = TreeItem([contractName, False, False, False, contract.exchange, gateWayName],
				                self.model.rootItem)
				contractDict[contractName] = item
				child.append(item)
				subItem = TreeItem([contract.symbol, hasTick, hasBar, hasActive, contract.exchange, gateWayName], item)
				item.appendChild(subItem)

		# yumi = TreeItem([u"玉米", False, False, False, "SH", "CTP"], self.model.rootItem)
		# yumi.appendChild(TreeItem([u"c1705", False, False, False, "SH", "CTP"], yumi))
		# yumi.appendChild(TreeItem([u"c1703", False, False, False, "SH", "CTP"], yumi))
		# yumi.appendChild(TreeItem([u"c1707", False, False, False, "SH", "CTP"], yumi))
		# yumi.appendChild(TreeItem([u"c1709", False, False, False, "SH", "CTP"], yumi))
		# dianfen = TreeItem([u"淀粉", False, False, False, "SH", "CTP"], self.model.rootItem)
		# dianfen.appendChild(TreeItem([u"d1705", False, False, False, "SH", "CTP"], dianfen))
		# dianfen.appendChild(TreeItem([u"d1703", False, False, False, "SH", "CTP"], dianfen))
		# dianfen.appendChild(TreeItem([u"d1707", False, False, False, "SH", "CTP"], dianfen))
		# dianfen.appendChild(TreeItem([u"d1709", False, False, False, "SH", "CTP"], dianfen))
		#
		# child.append(yumi)
		# child.append(dianfen)
		self.model.setDataSource(child)
		self.qTreeView.expandAll()

	def saveSetting(self):
		setting = {}
		setting["tick"] = []
		setting["bar"] = []
		setting["active"] = {}
		queue = Queue()
		queue.put(self.model.rootItem)
		while queue.qsize() > 0:
			item = queue.get()
			for child in item.childItems:
				queue.put(child)
			if item.parentItem is not None and item.parentItem != self.model.rootItem:
				name = item.data(0)
				interface = item.data(5)
				if item.data(1):
					setting["tick"].append([name, interface])
				if item.data(2):
					setting["bar"].append([name, interface])
				if item.data(3):
					setting["active"][item.parentItem.data(0)] = name
		if self.mainEngine.drEngine.saveSetting(setting):
			self.hasChanged = True
			self.close()

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
		self.eventEngine.register(EVENT_CONTRACT, self.signal.emit)


if __name__ == '__main__':
	import sys

	app = QtGui.QApplication(sys.argv)

	view = DrEditWidget(None, DrEngine, EventEngine)
	view.setFixedSize(650, 500)
	view.show()
	sys.exit(app.exec_())
