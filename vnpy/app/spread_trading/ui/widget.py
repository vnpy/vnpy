# encoding: UTF-8

# from collections import OrderedDict

from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtWidgets, QtCore, QtGui
from ..template import SpreadTradingTemplate

from ..base import (
    APP_NAME,
    EVENT_SPREADTRADING_TICK,
    EVENT_SPREADTRADING_POS,
    EVENT_SPREADTRADING_LOG,
    # EVENT_SPREADTRADING_ALGO,
    EVENT_SPREADTRADING_ALGOLOG,
    # EVENT_SPREADTRADING_ADDSPREAD,
)

from vnpy.trader.ui.widget import (
    BaseCell,
    # EnumCell,
    MsgCell,
    TimeCell,
    BidCell,
    AskCell,
    PnlCell,
    BaseMonitor,
)

STYLESHEET_START = "background-color: rgb(111,255,244); color: black"
STYLESHEET_STOP = "background-color: rgb(255,201,111); color: black"


########################################################################
class SpreadManager(QtWidgets.QWidget):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        super(SpreadManager, self).__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine
        self.st_engine = main_engine.get_engine(APP_NAME)
        #
        self.initUi()
        self.init()
        self.update_class_combo()

    # ----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle("价差策略")

        #
        tick_Monitor = StTickMonitor(self.main_engine, self.event_engine)
        pos_Monitor = StPosMonitor(self.main_engine, self.event_engine)
        log_Monitor = StLogMonitor(self.main_engine, self.event_engine)
        self.algo_Manager = StAlgoManager(self.st_engine)
        algoLog_Monitor = StAlgoLogMonitor(self.main_engine, self.event_engine)

        #
        self.class_combo = QtWidgets.QComboBox()

        add_button = QtWidgets.QPushButton("Add Trading")
        add_button.clicked.connect(self.add_trading)

        save_button = QtWidgets.QPushButton("Save")
        save_button.clicked.connect(self.save_setting)

        buttonStopAll = QtWidgets.QPushButton("全部停止")
        buttonStopAll.clicked.connect(self.algo_Manager.stopAll)

        #
        groupTick = StGroup(tick_Monitor, "价差行情")
        groupPos = StGroup(pos_Monitor, "价差持仓")
        groupLog = StGroup(log_Monitor, "日志信息")
        groupAlgo = StGroup(self.algo_Manager, "价差算法")
        groupAlgoLog = StGroup(algoLog_Monitor, "算法信息")

        #
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(self.class_combo)
        hbox.addWidget(add_button)
        hbox.addWidget(buttonStopAll)
        hbox.addWidget(save_button)

        grid = QtWidgets.QGridLayout()
        grid.addLayout(hbox, 0, 0, 1, 2)
        grid.addWidget(groupTick, 1, 0)
        grid.addWidget(groupPos, 1, 1)
        grid.addWidget(groupAlgo, 2, 0, 1, 2)
        grid.addWidget(groupLog, 3, 0)
        grid.addWidget(groupAlgoLog, 3, 1)

        #
        self.setLayout(grid)

    def update_class_combo(self):
        """"""
        self.class_combo.addItems(self.st_engine.get_all_strategy_names())

    def show(self):
        """"""
        self.showMaximized()

    def init(self):
        """"""
        self.st_engine.init()
        self.algo_Manager.initCells()

    def add_trading(self):
        spread_name = self.add_spread()
        algo_name = str(self.class_combo.currentText())
        self.add_algo(spread_name, algo_name)

    def save_setting(self):
        self.st_engine.save_setting()

    def add_spread(self):
        """"""
        parameters = {
            "spread_name": "",
            "active_vt_symbol": "",
            "active_ratio": 0,
            "active_multiplier": 0,
            "active_payup": 0,
            "passive_vt_symbol": "",
            "passive_ratio": 0,
            "passive_multiplier": 0,
            "passive_payup": 0,
        }

        editor = SettingEditor(parameters)
        n = editor.exec_()

        setting = {"spread_name": ""}
        if n == editor.Accepted:
            s = editor.get_setting()
            setting = {
                "spread_name": s["spread_name"],
                "active_legs": {
                    "vt_symbol": s["active_vt_symbol"],
                    "ratio": s["active_ratio"],
                    "multiplier": s["active_multiplier"],
                    "payup": s["active_payup"],
                },
                "passive_legs": [
                    {
                        "vt_symbol": s["passive_vt_symbol"],
                        "ratio": s["passive_ratio"],
                        "multiplier": s["passive_multiplier"],
                        "payup": s["passive_payup"],
                    }
                ],
            }

            self.st_engine.add_spread(setting)

        return setting["spread_name"]

    def delete_trading(self):
        """"""
        parameters = {"name": ""}

        editor = SettingEditor(parameters)
        n = editor.exec_()

        if n == editor.Accepted:
            s = editor.get_setting()
            self.st_engine.delete_spread(s)

    def add_algo(self, spread_name, algo_name):
        """"""
        setting = {
            "spread_name": spread_name,
            "algo_name": algo_name,
            "Params": {},
        }
        self.st_engine.add_algo(setting)
        self.algo_Manager.initCells()

    def show_algo_widget(self):
        ix = self.template_combo.currentIndex()
        current_name = self.template_combo.itemData(ix)

        for template_name, widget in self.algo_widgets.items():
            if template_name == current_name:
                widget.show()
            else:
                widget.hide()


########################################################################
class SettingEditor(QtWidgets.QDialog):
    """
    For creating new strategy and editing strategy parameters.
    """

    def __init__(self, parameters: dict):
        """"""
        super(SettingEditor, self).__init__()

        self.parameters = parameters

        self.edits = {}

        self.init_ui()

    def init_ui(self):
        """"""
        form = QtWidgets.QFormLayout()

        # Add vt_symbol and name edit if add new strategy
        self.setWindowTitle(f"添加价差组合")
        button_text = "添加"
        parameters = {}
        parameters.update(self.parameters)

        for name, value in parameters.items():
            type_ = type(value)

            edit = QtWidgets.QLineEdit(str(value))
            if type_ is int:
                validator = QtGui.QIntValidator()
                edit.setValidator(validator)
            elif type_ is float:
                validator = QtGui.QDoubleValidator()
                edit.setValidator(validator)

            form.addRow(f"{name} {type_}", edit)

            self.edits[name] = (edit, type_)

        button = QtWidgets.QPushButton(button_text)
        button.clicked.connect(self.accept)
        form.addRow(button)

        self.setLayout(form)

    def get_setting(self):
        """"""
        setting = {}

        for name, tp in self.edits.items():
            edit, type_ = tp
            value_text = edit.text()

            if type_ == bool:
                if value_text == "True":
                    value = True
                else:
                    value = False
            else:
                value = type_(value_text)

            setting[name] = value

        return setting


########################################################################
class StGroup(QtWidgets.QGroupBox):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self, widget, title, parent=None):
        """Constructor"""
        super(StGroup, self).__init__(parent)

        self.setTitle(title)
        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(widget)
        self.setLayout(vbox)


########################################################################
class StAlgoManager(QtWidgets.QTableWidget):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self, stEngine, parent=None):
        """Constructor"""
        super(StAlgoManager, self).__init__(parent)

        self.algoEngine = stEngine.algoEngine

        self.buttonActiveDict = {}  # spreadName: buttonActive

        self.initUi()

    # ----------------------------------------------------------------------
    def initUi(self):
        """"""
        headers = [
            "价差",
            "算法",
            "买开",
            "买平",
            "卖开",
            "卖平",
            "委托上限",
            "持仓上限",
            "模式",
            "状态",
        ]
        self.setColumnCount(len(headers))
        self.setHorizontalHeaderLabels(headers)
        self.horizontalHeader().setSectionResizeMode(
            QtWidgets.QHeaderView.Stretch
        )
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)

    # ----------------------------------------------------------------------
    def initCells(self):
        """"""
        algoEngine = self.algoEngine
        allParams = self.algoEngine.getAllAlgoParams()
        self.setRowCount(len(allParams))

        for row, d in enumerate(allParams):
            cellSpreadName = QtWidgets.QTableWidgetItem(d["spread_name"])
            cellAlgoName = QtWidgets.QTableWidgetItem(d["algo_name"])
            params = d["Params"]
            spinBuyPrice = StBuyPriceSpinBox(
                algoEngine,
                d["spread_name"],
                d["algo_name"],
                params["buyPrice"],
            )
            spinCoverPrice = StCoverPriceSpinBox(
                algoEngine,
                d["spread_name"],
                d["algo_name"],
                params["coverPrice"],
            )
            spinShortPrice = StShortPriceSpinBox(
                algoEngine,
                d["spread_name"],
                d["algo_name"],
                params["shortPrice"],
            )
            spinSellPrice = StSellPriceSpinBox(
                algoEngine,
                d["spread_name"],
                d["algo_name"],
                params["sellPrice"],
            )
            spinMaxOrderSize = StMaxOrderSizeSpinBox(
                algoEngine,
                d["spread_name"],
                d["algo_name"],
                params["maxOrderSize"],
            )
            spinMaxPosSize = StMaxPosSizeSpinBox(
                algoEngine,
                d["spread_name"],
                d["algo_name"],
                params["maxPosSize"],
            )
            comboMode = StModeComboBox(
                algoEngine, d["spread_name"], d["algo_name"], params["mode"]
            )
            buttonActive = StActiveButton(
                algoEngine, d["spread_name"], d["algo_name"]
            )

            self.setItem(row, 0, cellSpreadName)
            self.setItem(row, 1, cellAlgoName)
            self.setCellWidget(row, 2, spinBuyPrice)
            self.setCellWidget(row, 3, spinCoverPrice)
            self.setCellWidget(row, 4, spinShortPrice)
            self.setCellWidget(row, 5, spinSellPrice)
            self.setCellWidget(row, 6, spinMaxOrderSize)
            self.setCellWidget(row, 7, spinMaxPosSize)
            self.setCellWidget(row, 8, comboMode)
            self.setCellWidget(row, 9, buttonActive)
            # self.setCellWidget(row, 10, buttonDelete)

            buttonActive.signalActive.connect(comboMode.algoActiveChanged)

            self.buttonActiveDict[d["spread_name"]] = buttonActive

    # ----------------------------------------------------------------------
    def stopAll(self):
        """"""
        for button in list(self.buttonActiveDict.values()):
            button.stop()


""""""


class StBuyPriceSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, algoName, price, parent=None):
        """Constructor"""
        super(StBuyPriceSpinBox, self).__init__(parent)

        self.algoEngine = algoEngine
        self.spreadName = spreadName
        self.algoName = algoName

        self.setDecimals(8)
        self.setRange(-10000, 10000)

        self.setValue(float(price))

        self.valueChanged.connect(self.setPrice)

    # ----------------------------------------------------------------------
    def setPrice(self, value):
        """"""
        self.algoEngine.setAlgoBuyPrice(self.spreadName, self.algoName, value)


""""""


class StSellPriceSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, algoName, price, parent=None):
        """Constructor"""
        super(StSellPriceSpinBox, self).__init__(parent)

        self.algoEngine = algoEngine
        self.spreadName = spreadName
        self.algoName = algoName

        self.setDecimals(8)
        self.setRange(-10000, 10000)
        self.setValue(float(price))

        self.valueChanged.connect(self.setPrice)

    # ----------------------------------------------------------------------
    def setPrice(self, value):
        """"""
        self.algoEngine.setAlgoSellPrice(self.spreadName, self.algoName, value)


""""""


class StShortPriceSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, algoName, price, parent=None):
        """Constructor"""
        super(StShortPriceSpinBox, self).__init__(parent)

        self.algoEngine = algoEngine
        self.spreadName = spreadName
        self.algoName = algoName

        self.setDecimals(8)
        self.setRange(-10000, 10000)
        self.setValue(float(price))

        self.valueChanged.connect(self.setPrice)

    # ----------------------------------------------------------------------
    def setPrice(self, value):
        """"""
        self.algoEngine.setAlgoShortPrice(
            self.spreadName, self.algoName, value
        )


""""""


class StCoverPriceSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, algoName, price, parent=None):
        """Constructor"""
        super(StCoverPriceSpinBox, self).__init__(parent)

        self.algoEngine = algoEngine
        self.spreadName = spreadName
        self.algoName = algoName

        self.setDecimals(8)
        self.setRange(-10000, 10000)
        self.setValue(float(price))

        self.valueChanged.connect(self.setPrice)

    # ----------------------------------------------------------------------
    def setPrice(self, value):
        """"""
        self.algoEngine.setAlgoCoverPrice(
            self.spreadName, self.algoName, value
        )


""""""


class StMaxPosSizeSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, algoName, size, parent=None):
        """Constructor"""
        super(StMaxPosSizeSpinBox, self).__init__(parent)

        self.algoEngine = algoEngine
        self.spread_name = spreadName
        self.algo_name = algoName

        self.setDecimals(8)
        self.setRange(-10000, 10000)
        self.setValue(size)

        self.valueChanged.connect(self.setSize)

    # ----------------------------------------------------------------------
    def setSize(self, size):
        """"""
        self.algoEngine.setAlgoMaxPosSize(
            self.spread_name, self.algo_name, size
        )


""""""


class StMaxOrderSizeSpinBox(QtWidgets.QDoubleSpinBox):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, algoName, size, parent=None):
        """Constructor"""
        super(StMaxOrderSizeSpinBox, self).__init__(parent)

        self.algoEngine = algoEngine
        self.spreadName = spreadName
        self.algoName = algoName

        self.setDecimals(8)
        self.setRange(-10000, 10000)
        self.setValue(size)

        self.valueChanged.connect(self.setSize)

    # ----------------------------------------------------------------------
    def setSize(self, size):
        """"""
        self.algoEngine.setAlgoMaxOrderSize(
            self.spreadName, self.algoName, size
        )


""""""


class StModeComboBox(QtWidgets.QComboBox):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, algoName, mode, parent=None):
        """Constructor"""
        super(StModeComboBox, self).__init__(parent)

        self.algoEngine = algoEngine
        self.spreadName = spreadName
        self.algoName = algoName

        all_modes = [
            SpreadTradingTemplate.MODE_LONGSHORT,
            SpreadTradingTemplate.MODE_LONGONLY,
            SpreadTradingTemplate.MODE_SHORTONLY,
        ]
        self.addItems(all_modes)
        self.setCurrentIndex(all_modes.index(mode))

        self.currentIndexChanged.connect(self.setMode)

    # ----------------------------------------------------------------------
    def setMode(self):
        """"""
        mode = str(self.currentText())
        self.algoEngine.setAlgoMode(self.spreadName, self.algoName, mode)

    # ----------------------------------------------------------------------
    def algoActiveChanged(self, active):
        """"""
        # not allow change settings when algo running
        if active:
            self.setEnabled(False)
        else:
            self.setEnabled(True)


""""""


class StActiveButton(QtWidgets.QPushButton):
    """"""

    signalActive = QtCore.pyqtSignal(bool)

    # ----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, algoName, parent=None):
        """Constructor"""
        super(StActiveButton, self).__init__(parent)

        self.algoEngine = algoEngine
        self.spread_name = spreadName
        self.algo_name = algoName

        self.active = False
        self.setStopped()

        self.clicked.connect(self.buttonClicked)

    # ----------------------------------------------------------------------
    def buttonClicked(self):
        """"""
        if self.active:
            self.stop()
        else:
            self.start()

    # ----------------------------------------------------------------------
    def stop(self):
        """"""
        algoActive = self.algoEngine.stopAlgo(self.spread_name, self.algo_name)
        if not algoActive:
            self.setStopped()

    # ----------------------------------------------------------------------
    def start(self):
        """"""
        algoActive = self.algoEngine.startAlgo(
            self.spread_name, self.algo_name
        )
        if algoActive:
            self.setStarted()

    # ----------------------------------------------------------------------
    def setStarted(self):
        """"""
        self.setText("运行中")
        self.setStyleSheet(STYLESHEET_START)

        self.active = True
        self.signalActive.emit(self.active)

    # ----------------------------------------------------------------------
    def setStopped(self):
        """"""
        self.setText("已停止")
        self.setStyleSheet(STYLESHEET_STOP)

        self.active = False
        self.signalActive.emit(self.active)


""""""


class StDeleteButton(QtWidgets.QPushButton):
    """"""

    signalActive = QtCore.pyqtSignal(bool)

    # ----------------------------------------------------------------------
    def __init__(self, algoEngine, spreadName, algoName, parent=None):
        """Constructor"""
        super(StDeleteButton, self).__init__(parent)

        self.algoEngine = algoEngine
        self.spread_name = spreadName
        self.algo_name = algoName

        self.setInit()
        self.clicked.connect(self.cancel)

    # ----------------------------------------------------------------------
    def setDeleted(self):
        """"""
        self.setText("Deleted！")
        self.setStyleSheet(STYLESHEET_STOP)
        self.signalActive.emit(False)

    # ----------------------------------------------------------------------
    def setInit(self):
        """"""
        self.setText("Delete")
        self.setStyleSheet(STYLESHEET_START)
        self.signalActive.emit(True)


########################################################################
class StTickMonitor(BaseMonitor):
    """"""

    event_type = EVENT_SPREADTRADING_TICK
    data_key = "name"
    sorting = True

    headers = {
        "name": {"display": "价差名称", "cell": BaseCell, "update": False},
        "bidPrice": {"display": "买价", "cell": BidCell, "update": True},
        "bidVolume": {"display": "买量", "cell": BidCell, "update": True},
        "askPrice": {"display": "卖价", "cell": AskCell, "update": True},
        "askVolume": {"display": "卖量", "cell": AskCell, "update": True},
        "time": {"display": "时间", "cell": BaseCell, "update": True},
        "symbol": {"display": "价差公式", "cell": BaseCell, "update": False},
    }


########################################################################
class StPosMonitor(BaseMonitor):
    """"""

    event_type = EVENT_SPREADTRADING_POS
    data_key = "name"

    headers = {}
    headers["name"] = {"display": "价差名称", "cell": BaseCell, "update": True}
    headers["netPos"] = {"display": "净仓", "cell": PnlCell, "update": True}
    headers["longPos"] = {"display": "多仓", "cell": BaseCell, "update": True}
    headers["shortPos"] = {"display": "空仓", "cell": BaseCell, "update": True}
    headers["symbol"] = {"display": "代码", "cell": BaseCell, "update": True}


########################################################################
class StLogMonitor(BaseMonitor):
    """"""

    event_type = EVENT_SPREADTRADING_LOG
    data_key = ""
    sorting = False

    headers = {
        "time": {"display": "时间", "cell": TimeCell, "update": True},
        "msg": {"display": "信息", "cell": MsgCell, "update": True},
    }

    def init_ui(self):
        """
        Stretch last column.
        """
        super(StLogMonitor, self).init_ui()

        self.horizontalHeader().setSectionResizeMode(
            1, QtWidgets.QHeaderView.Stretch
        )

    def insert_new_row(self, data):
        """
        Insert a new row at the top of table.
        """
        super(StLogMonitor, self).insert_new_row(data)
        self.resizeRowToContents(0)


########################################################################
class StAlgoLogMonitor(BaseMonitor):
    """"""

    # ----------------------------------------------------------------------
    event_type = EVENT_SPREADTRADING_ALGOLOG

    headers = {
        "time": {"display": "时间", "cell": TimeCell, "update": True},
        "msg": {"display": "信息", "cell": MsgCell, "update": True},
    }

    def init_ui(self):
        """
        Stretch last column.
        """
        super(StAlgoLogMonitor, self).init_ui()

        self.horizontalHeader().setSectionResizeMode(
            1, QtWidgets.QHeaderView.Stretch
        )

    def insert_new_row(self, data):
        """
        Insert a new row at the top of table.
        """
        super(StAlgoLogMonitor, self).insert_new_row(data)
        self.resizeRowToContents(0)
