# encoding: UTF-8

from __future__ import division

from collections import OrderedDict, defaultdict

from PyQt5 import QtWidgets, QtGui
from typing import Any, ClassVar, List, Dict, Union

from vnpy.trader.app.algoTrading.algoTemplate import AlgoTemplate
from vnpy.trader.app.algoTrading.uiAlgoWidget import AlgoWidget
from vnpy.trader.vtConstant import constant
import typing

# 活动委托状态
STATUS_ACTIVE = [
    constant.STATUS_NOTTRADED,
    constant.STATUS_PARTTRADED,
    constant.STATUS_UNKNOWN,
]

_paramsForClass = defaultdict(dict)  # type: Dict[object, Dict[str, AlgoTemplate2Param]]

validatorClasses = {
    int: QtGui.QIntValidator,
    float: QtGui.QDoubleValidator,
    # key not exist for other types
}


# ----------------------------------------------------------------------
def param(name, displayName, internalType=str, choices=None):
    # ----------------------------------------------------------------------
    def paramDecorator(cls):
        _paramsForClass[cls][name] = AlgoTemplate2Param(
            name=name,
            displayName=displayName,
            internalType=internalType,
            choices=choices,
        )
        return cls

    return paramDecorator


# ----------------------------------------------------------------------
def paramsForClass(cls):
    backup = cls
    while cls.__class__ != object:
        if cls in _paramsForClass:
            return _paramsForClass[cls]
        cls = cls.__class__
    raise KeyError(
        "class {} has no param assigned, use @param to decorate it".format(
            backup.__name__
        )
    )


# ----------------------------------------------------------------------
def paramsForInstance(instance):
    return paramsForClass(instance.__class__)


# ----------------------------------------------------------------------
def getWidgetText(widget):
    if "currentText" in widget.__dict__:
        return widget.currentText()
    if "plainText" in widget.__dict__:
        return widget.plainText()
    return widget.text()


########################################################################
class AlgoTemplate2Param:

    # ----------------------------------------------------------------------
    def __init__(self, name, displayName, internalType, choices):
        self.name = name  # type: str
        self.displayName = displayName  # type: str
        self.internalType = internalType
        self.choices = choices  # type: [str]


# ----------------------------------------------------------------------
def generateWidgetClass(algoClass):  # type: (Any)->object
    templateName = algoClass.templateName

    ########################################################################
    class Widget(AlgoWidget):

        # ----------------------------------------------------------------------
        def __init__(self, algoEngine, parent=None):
            AlgoWidget.__init__(self, algoEngine, parent)
            self.templateName = templateName
            if "_inputs" not in self.__dict__:
                self._inputs = {}

        # ----------------------------------------------------------------------
        def _generateInputWidgetForParam(
            self, param
        ):  # type: (AlgoTemplate2Param)->Any
            if param.choices is None:
                # 如果没有选项提供， UI应该是一个可以随意输入的编辑框
                widget = QtWidgets.QLineEdit()

                # 某些内部数据可以使用qt的validator来检查输入值
                if param.internalType in validatorClasses:
                    validator = validatorClasses[param.internalType]()
                    widget.setValidator(validator)

            else:
                # 如果有选项提供，那UI应该是一个下拉框
                widget = QtWidgets.QComboBox()
                widget.addItems(param.choices)
                widget.setCurrentIndex(0)
            if "_inputs" not in self.__dict__:
                self._inputs = {}
            self._inputs[param.name] = widget
            return widget

        # ----------------------------------------------------------------------
        def initAlgoLayout(self):
            grid = QtWidgets.QGridLayout()
            for i, param in enumerate(paramsForClass(algoClass).values()):
                grid.addWidget(QtWidgets.QLabel(param.name), i, 0)

                inputWidget = self._generateInputWidgetForParam(param)
                grid.addWidget(inputWidget, i, 1)

            return grid

        # ----------------------------------------------------------------------
        def getAlgoSetting(self):
            setting = OrderedDict()

            setting["templateName"] = self.templateName
            for name, param in paramsForClass(algoClass).items():
                internalType = param.internalType
                setting[name] = internalType(getWidgetText(self._inputs[name]))
            return setting

    return Widget
