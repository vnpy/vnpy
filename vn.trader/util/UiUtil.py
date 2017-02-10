from PyQt4 import QtCore
from PyQt4.QtGui import QStyle, QStyledItemDelegate, QStyleOptionButton, QApplication, QItemDelegate, QComboBox, \
	QItemEditorCreatorBase


class CheckBoxDelegate(QStyledItemDelegate):
	"""
	A delegate that places a fully functioning QCheckBox in every
	cell of the column to which it's applied
	"""

	def __init__(self, parent):
		QItemDelegate.__init__(self, parent)

	def createEditor(self, parent, option, index):
		'''
		Important, otherwise an editor is created if the user clicks in this cell.
		** Need to hook up a signal to the model
		'''
		return None

	def paint(self, painter, option, index):
		'''
		Paint a checkbox without the label.
		'''
		data = index.model().data(index, QtCore.Qt.CheckStateRole)
		if not data in [QtCore.Qt.Unchecked, QtCore.Qt.Checked]:
			return
		checked = data == QtCore.Qt.Checked
		check_box_style_option = QStyleOptionButton()

		if index.flags() & QtCore.Qt.ItemIsEditable == QtCore.Qt.ItemIsEditable:
			check_box_style_option.state |= QStyle.State_Enabled
		else:
			check_box_style_option.state |= QStyle.State_ReadOnly

		if checked:
			check_box_style_option.state |= QStyle.State_On
		else:
			check_box_style_option.state |= QStyle.State_Off

		check_box_style_option.rect = self.getCheckBoxRect(option)

		# this will not run - hasFlag does not exist
		# if not index.model().hasFlag(index, QtCore.Qt.ItemIsEditable):
		# check_box_style_option.state |= QStyle.State_ReadOnly

		# check_box_style_option.state |= QStyle.State_Enabled

		QApplication.style().drawControl(QStyle.CE_CheckBox, check_box_style_option, painter)

	def editorEvent(self, event, model, option, index):
		'''
		Change the data in the model and the state of the checkbox
		if the user presses the left mousebutton or presses
		Key_Space or Key_Select and this cell is editable. Otherwise do nothing.
		'''
		# print 'Check Box editor Event detected : '
		if index.flags() & QtCore.Qt.ItemIsEditable != QtCore.Qt.ItemIsEditable:
			return False

		# print 'Check Box edior Event detected : passed first check'
		# Do not change the checkbox-state
		if event.type() == QtCore.QEvent.MouseButtonRelease or event.type() == QtCore.QEvent.MouseButtonDblClick:
			if event.button() != QtCore.Qt.LeftButton or not self.getCheckBoxRect(option).contains(event.pos()):
				return False
			if event.type() == QtCore.QEvent.MouseButtonDblClick:
				return True
		elif event.type() == QtCore.QEvent.KeyPress:
			if event.key() != QtCore.Qt.Key_Space and event.key() != QtCore.Qt.Key_Select:
				return False
		else:
			return False

		# Change the checkbox-state
		self.setModelData(None, model, index)
		return True

	def setModelData(self, editor, model, index):
		'''
		The user wanted to change the old state in the opposite.
		'''
		# print 'SetModelData'
		newValue = not index.data().toBool()
		# print 'New Value : {0}'.format(newValue)
		model.setData(index, QtCore.Qt.Checked if newValue else QtCore.Qt.Unchecked, QtCore.Qt.CheckStateRole)

	def getCheckBoxRect(self, option):
		check_box_style_option = QStyleOptionButton()
		check_box_rect = QApplication.style().subElementRect(QStyle.SE_CheckBoxIndicator, check_box_style_option, None)
		check_box_point = QtCore.QPoint(option.rect.x() +
		                                option.rect.width() / 2 -
		                                check_box_rect.width() / 2,
		                                option.rect.y() +
		                                option.rect.height() / 2 -
		                                check_box_rect.height() / 2)
		return QtCore.QRect(check_box_point, check_box_rect.size())


class ComboDelegate(QItemDelegate):
	def __init__(self, parent, dataList=[]):
		QItemDelegate.__init__(self, parent)
		self.dataList = dataList

	def createEditor(self, parent, option, index):
		combo = QComboBox(parent)
		combo.addItems(self.dataList)
		return combo

	def setEditorData(self, editor, index):
		text = index.data().toString()
		index = editor.findText(text)
		editor.setCurrentIndex(index)

	def setModelData(self, editor, model, index):
		model.setData(index, str(editor.itemText(editor.currentIndex())))

	def updateEditorGeometry(self, editor, option, index):
		print option, option.rect
		editor.setGeometry(option.rect)


class GateWayListEditor(QComboBox):
	def __init__(self, widget=None, dataList=[]):
		super(GateWayListEditor, self).__init__(widget)
		self.dataList = dataList
		self.populateList()

	def getGateWay(self):
		gateWay = self.itemData(self.currentIndex(), QtCore.Qt.DisplayRole)
		return gateWay

	def setGateWay(self, gateWay):
		self.setCurrentIndex(self.findData(gateWay, QtCore.Qt.DisplayRole))

	def populateList(self):
		for i, gateWayName in enumerate(self.dataList):
			self.insertItem(i, gateWayName)
			self.setItemData(i, gateWayName, QtCore.Qt.DisplayRole)


class GateWayListItemEditorCreator(QItemEditorCreatorBase):
	def createWidget(self, parent):
		return GateWayListEditor(parent, ["CTP", "LTS", "XTP", "FEMAS", "XSPEED", "QDP", "KSOTP", "KSGOLD", "SGIT"])
