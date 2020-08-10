"""
Basic widgets for VN Trader.
"""

import csv
import platform
from enum import Enum
from typing import Any, Dict
from copy import copy
from tzlocal import get_localzone

from PyQt5 import QtCore, QtGui, QtWidgets, Qt
import rqdatac
import numpy as np

import vnpy
from vnpy.event import Event, EventEngine
from ..constant import Direction, Exchange, Offset, OrderType
from ..engine import MainEngine
from ..event import (
    EVENT_TICK,
    EVENT_TRADE,
    EVENT_ORDER,
    EVENT_POSITION,
    EVENT_ACCOUNT,
    EVENT_LOG
)
from ..object import OrderRequest, SubscribeRequest, PositionData
from ..utility import load_json, save_json, get_digits
from ..setting import SETTING_FILENAME, SETTINGS


COLOR_LONG = QtGui.QColor("red")
COLOR_SHORT = QtGui.QColor("green")
COLOR_BID = QtGui.QColor(255, 174, 201)
COLOR_ASK = QtGui.QColor(160, 255, 160)
COLOR_BLACK = QtGui.QColor("black")


class BaseCell(QtWidgets.QTableWidgetItem):
    """
    General cell used in tablewidgets.
    """

    def __init__(self, content: Any, data: Any):
        """"""
        super(BaseCell, self).__init__()
        self.setTextAlignment(QtCore.Qt.AlignCenter)
        self.set_content(content, data)

    def set_content(self, content: Any, data: Any) -> None:
        """
        Set text content.
        """
        self.setText(str(content))
        self._data = data

    def get_data(self) -> Any:
        """
        Get data object.
        """
        return self._data


class EnumCell(BaseCell):
    """
    Cell used for showing enum data.
    """

    def __init__(self, content: str, data: Any):
        """"""
        super(EnumCell, self).__init__(content, data)

    def set_content(self, content: Any, data: Any) -> None:
        """
        Set text using enum.constant.value.
        """
        if content:
            super(EnumCell, self).set_content(content.value, data)


class DirectionCell(EnumCell):
    """
    Cell used for showing direction data.
    """

    def __init__(self, content: str, data: Any):
        """"""
        super(DirectionCell, self).__init__(content, data)

    def set_content(self, content: Any, data: Any) -> None:
        """
        Cell color is set according to direction.
        """
        super(DirectionCell, self).set_content(content, data)

        if content is Direction.SHORT:
            self.setForeground(COLOR_SHORT)
        else:
            self.setForeground(COLOR_LONG)


class BidCell(BaseCell):
    """
    Cell used for showing bid price and volume.
    """

    def __init__(self, content: Any, data: Any):
        """"""
        super(BidCell, self).__init__(content, data)

        self.setForeground(COLOR_BID)


class AskCell(BaseCell):
    """
    Cell used for showing ask price and volume.
    """

    def __init__(self, content: Any, data: Any):
        """"""
        super(AskCell, self).__init__(content, data)

        self.setForeground(COLOR_ASK)


class PnlCell(BaseCell):
    """
    Cell used for showing pnl data.
    """

    def __init__(self, content: Any, data: Any):
        """"""
        super(PnlCell, self).__init__(content, data)

    def set_content(self, content: Any, data: Any) -> None:
        """
        Cell color is set based on whether pnl is
        positive or negative.
        """
        super(PnlCell, self).set_content(content, data)

        if str(content).startswith("-"):
            self.setForeground(COLOR_SHORT)
        else:
            self.setForeground(COLOR_LONG)


class TimeCell(BaseCell):
    """
    Cell used for showing time string from datetime object.
    """

    local_tz = get_localzone()

    def __init__(self, content: Any, data: Any):
        """"""
        super(TimeCell, self).__init__(content, data)

    def set_content(self, content: Any, data: Any) -> None:
        """"""
        if content is None:
            return

        content = content.astimezone(self.local_tz)
        timestamp = content.strftime("%H:%M:%S")

        millisecond = int(content.microsecond / 1000)
        if millisecond:
            timestamp = f"{timestamp}.{millisecond}"

        self.setText(timestamp)
        self._data = data


class MsgCell(BaseCell):
    """
    Cell used for showing msg data.
    """

    def __init__(self, content: str, data: Any):
        """"""
        super(MsgCell, self).__init__(content, data)
        self.setTextAlignment(QtCore.Qt.AlignLeft | QtCore.Qt.AlignVCenter)


class BaseMonitor(QtWidgets.QTableWidget):
    """
    Monitor data update in VN Trader.
    """

    event_type: str = ""
    data_key: str = ""
    sorting: bool = False
    headers: Dict[str, dict] = {}

    signal: QtCore.pyqtSignal = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super(BaseMonitor, self).__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine
        self.cells: Dict[str, dict] = {}

        self.init_ui()
        self.register_event()

    def init_ui(self) -> None:
        """"""
        self.init_table()
        self.init_menu()

    def init_table(self) -> None:
        """
        Initialize table.
        """
        self.setColumnCount(len(self.headers))

        labels = [d["display"] for d in self.headers.values()]
        self.setHorizontalHeaderLabels(labels)

        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
        self.setAlternatingRowColors(True)
        self.setSortingEnabled(self.sorting)

    def init_menu(self) -> None:
        """
        Create right click menu.
        """
        self.menu = QtWidgets.QMenu(self)

        resize_action = QtWidgets.QAction("调整列宽", self)
        resize_action.triggered.connect(self.resize_columns)
        self.menu.addAction(resize_action)

        save_action = QtWidgets.QAction("保存数据", self)
        save_action.triggered.connect(self.save_csv)
        self.menu.addAction(save_action)

    def register_event(self) -> None:
        """
        Register event handler into event engine.
        """
        if self.event_type:
            self.signal.connect(self.process_event)
            self.event_engine.register(self.event_type, self.signal.emit)

    def process_event(self, event: Event) -> None:
        """
        Process new data from event and update into table.
        """
        # Disable sorting to prevent unwanted error.
        if self.sorting:
            self.setSortingEnabled(False)

        # Update data into table.
        data = event.data

        if not self.data_key:
            self.insert_new_row(data)
        else:
            key = data.__getattribute__(self.data_key)

            if key in self.cells:
                self.update_old_row(data)
            else:
                self.insert_new_row(data)

        # Enable sorting
        if self.sorting:
            self.setSortingEnabled(True)

    def insert_new_row(self, data: Any):
        """
        Insert a new row at the top of table.
        """
        self.insertRow(0)

        row_cells = {}
        for column, header in enumerate(self.headers.keys()):
            setting = self.headers[header]

            content = data.__getattribute__(header)
            cell = setting["cell"](content, data)
            self.setItem(0, column, cell)

            if setting["update"]:
                row_cells[header] = cell

        if self.data_key:
            key = data.__getattribute__(self.data_key)
            self.cells[key] = row_cells

    def update_old_row(self, data: Any) -> None:
        """
        Update an old row in table.
        """
        key = data.__getattribute__(self.data_key)
        row_cells = self.cells[key]

        for header, cell in row_cells.items():
            content = data.__getattribute__(header)
            cell.set_content(content, data)

    def resize_columns(self) -> None:
        """
        Resize all columns according to contents.
        """
        self.horizontalHeader().resizeSections(QtWidgets.QHeaderView.ResizeToContents)

    def save_csv(self) -> None:
        """
        Save table data into a csv file
        """
        path, _ = QtWidgets.QFileDialog.getSaveFileName(
            self, "保存数据", "", "CSV(*.csv)")

        if not path:
            return

        with open(path, "w") as f:
            writer = csv.writer(f, lineterminator="\n")

            writer.writerow(self.headers.keys())

            for row in range(self.rowCount()):
                row_data = []
                for column in range(self.columnCount()):
                    item = self.item(row, column)
                    if item:
                        row_data.append(str(item.text()))
                    else:
                        row_data.append("")
                writer.writerow(row_data)

    def contextMenuEvent(self, event: QtGui.QContextMenuEvent) -> None:
        """
        Show menu with right click.
        """
        self.menu.popup(QtGui.QCursor.pos())


class TickMonitor(BaseMonitor):
    """
    Monitor for tick data.
    """

    event_type = EVENT_TICK
    data_key = "vt_symbol"
    sorting = True

    headers = {
        "symbol": {"display": "代码", "cell": BaseCell, "update": False},
        "exchange": {"display": "交易所", "cell": EnumCell, "update": False},
        "name": {"display": "名称", "cell": BaseCell, "update": True},
        "last_price": {"display": "最新价", "cell": BaseCell, "update": True},
        "volume": {"display": "成交量", "cell": BaseCell, "update": True},
        "open_price": {"display": "开盘价", "cell": BaseCell, "update": True},
        "high_price": {"display": "最高价", "cell": BaseCell, "update": True},
        "low_price": {"display": "最低价", "cell": BaseCell, "update": True},
        "bid_price_1": {"display": "买1价", "cell": BidCell, "update": True},
        "bid_volume_1": {"display": "买1量", "cell": BidCell, "update": True},
        "ask_price_1": {"display": "卖1价", "cell": AskCell, "update": True},
        "ask_volume_1": {"display": "卖1量", "cell": AskCell, "update": True},
        "datetime": {"display": "时间", "cell": TimeCell, "update": True},
        "gateway_name": {"display": "接口", "cell": BaseCell, "update": False},
    }


class LogMonitor(BaseMonitor):
    """
    Monitor for log data.
    """

    event_type = EVENT_LOG
    data_key = ""
    sorting = False

    headers = {
        "time": {"display": "时间", "cell": TimeCell, "update": False},
        "msg": {"display": "信息", "cell": MsgCell, "update": False},
        "gateway_name": {"display": "接口", "cell": BaseCell, "update": False},
    }


class TradeMonitor(BaseMonitor):
    """
    Monitor for trade data.
    """

    event_type = EVENT_TRADE
    data_key = ""
    sorting = True

    headers: Dict[str, dict] = {
        "tradeid": {"display": "成交号 ", "cell": BaseCell, "update": False},
        "orderid": {"display": "委托号", "cell": BaseCell, "update": False},
        "symbol": {"display": "代码", "cell": BaseCell, "update": False},
        "exchange": {"display": "交易所", "cell": EnumCell, "update": False},
        "direction": {"display": "方向", "cell": DirectionCell, "update": False},
        "offset": {"display": "开平", "cell": EnumCell, "update": False},
        "price": {"display": "价格", "cell": BaseCell, "update": False},
        "volume": {"display": "数量", "cell": BaseCell, "update": False},
        "datetime": {"display": "时间", "cell": TimeCell, "update": False},
        "gateway_name": {"display": "接口", "cell": BaseCell, "update": False},
    }


class OrderMonitor(BaseMonitor):
    """
    Monitor for order data.
    """

    event_type = EVENT_ORDER
    data_key = "vt_orderid"
    sorting = True

    headers: Dict[str, dict] = {
        "orderid": {"display": "委托号", "cell": BaseCell, "update": False},
        "symbol": {"display": "代码", "cell": BaseCell, "update": False},
        "exchange": {"display": "交易所", "cell": EnumCell, "update": False},
        "type": {"display": "类型", "cell": EnumCell, "update": False},
        "direction": {"display": "方向", "cell": DirectionCell, "update": False},
        "offset": {"display": "开平", "cell": EnumCell, "update": False},
        "price": {"display": "价格", "cell": BaseCell, "update": False},
        "volume": {"display": "总数量", "cell": BaseCell, "update": True},
        "traded": {"display": "已成交", "cell": BaseCell, "update": True},
        "status": {"display": "状态", "cell": EnumCell, "update": True},
        "datetime": {"display": "时间", "cell": TimeCell, "update": True},
        "gateway_name": {"display": "接口", "cell": BaseCell, "update": False},
    }

    def init_ui(self):
        """
        Connect signal.
        """
        super(OrderMonitor, self).init_ui()

        self.setToolTip("双击单元格撤单")
        self.itemDoubleClicked.connect(self.cancel_order)

    def cancel_order(self, cell: BaseCell) -> None:
        """
        Cancel order if cell double clicked.
        """
        order = cell.get_data()
        req = order.create_cancel_request()
        self.main_engine.cancel_order(req, order.gateway_name)


class PositionMonitor(BaseMonitor):
    """
    Monitor for position data.
    """

    event_type = EVENT_POSITION
    data_key = "vt_positionid"
    sorting = True

    headers = {
        "symbol": {"display": "代码", "cell": BaseCell, "update": False},
        "exchange": {"display": "交易所", "cell": EnumCell, "update": False},
        "direction": {"display": "方向", "cell": DirectionCell, "update": False},
        "volume": {"display": "数量", "cell": BaseCell, "update": True},
        "yd_volume": {"display": "昨仓", "cell": BaseCell, "update": True},
        "frozen": {"display": "冻结", "cell": BaseCell, "update": True},
        "price": {"display": "均价", "cell": BaseCell, "update": True},
        "pnl": {"display": "盈亏", "cell": PnlCell, "update": True},
        "gateway_name": {"display": "接口", "cell": BaseCell, "update": False},
    }


class AccountMonitor(BaseMonitor):
    """
    Monitor for account data.
    """

    event_type = EVENT_ACCOUNT
    data_key = "vt_accountid"
    sorting = True

    headers = {
        "accountid": {"display": "账号", "cell": BaseCell, "update": False},
        "balance": {"display": "余额", "cell": BaseCell, "update": True},
        "frozen": {"display": "冻结", "cell": BaseCell, "update": True},
        "available": {"display": "可用", "cell": BaseCell, "update": True},
        "gateway_name": {"display": "接口", "cell": BaseCell, "update": False},
    }


class ConnectDialog(QtWidgets.QDialog):
    """
    Start connection of a certain gateway.
    """

    def __init__(self, main_engine: MainEngine, gateway_name: str):
        """"""
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.gateway_name: str = gateway_name
        self.filename: str = f"connect_{gateway_name.lower()}.json"

        self.widgets: Dict[str, QtWidgets.QWidget] = {}

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle(f"连接{self.gateway_name}")

        # Default setting provides field name, field data type and field default value.
        default_setting = self.main_engine.get_default_setting(
            self.gateway_name)

        # Saved setting provides field data used last time.
        loaded_setting = load_json(self.filename)

        # Initialize line edits and form layout based on setting.
        form = QtWidgets.QFormLayout()

        for field_name, field_value in default_setting.items():
            field_type = type(field_value)

            if field_type == list:
                widget = QtWidgets.QComboBox()
                widget.addItems(field_value)

                if field_name in loaded_setting:
                    saved_value = loaded_setting[field_name]
                    ix = widget.findText(saved_value)
                    widget.setCurrentIndex(ix)
            else:
                widget = QtWidgets.QLineEdit(str(field_value))

                if field_name in loaded_setting:
                    saved_value = loaded_setting[field_name]
                    widget.setText(str(saved_value))

                if "密码" in field_name:
                    widget.setEchoMode(QtWidgets.QLineEdit.Password)

            form.addRow(f"{field_name} <{field_type.__name__}>", widget)
            self.widgets[field_name] = (widget, field_type)

        button = QtWidgets.QPushButton("连接")
        button.clicked.connect(self.connect)
        form.addRow(button)

        self.setLayout(form)

    def connect(self) -> None:
        """
        Get setting value from line edits and connect the gateway.
        """
        setting = {}
        for field_name, tp in self.widgets.items():
            widget, field_type = tp
            if field_type == list:
                field_value = str(widget.currentText())
            else:
                field_value = field_type(widget.text())
            setting[field_name] = field_value

        save_json(self.filename, setting)

        self.main_engine.connect(setting, self.gateway_name)

        self.accept()


class TradingWidget(QtWidgets.QWidget):
    """
    General manual trading widget.
    """

    signal_tick = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine

        self.vt_symbol: str = ""
        self.price_digits: int = 0

        self.init_ui()
        self.register_event()

    def init_ui(self) -> None:
        """"""
        self.setFixedWidth(300)

        # Trading function area
        exchanges = self.main_engine.get_all_exchanges()
        self.exchange_combo = QtWidgets.QComboBox()
        self.exchange_combo.addItems([exchange.value for exchange in exchanges])

        self.symbol_line = QtWidgets.QLineEdit()
        self.symbol_line.returnPressed.connect(self.set_vt_symbol)

        self.name_line = QtWidgets.QLineEdit()
        self.name_line.setReadOnly(True)

        self.direction_combo = QtWidgets.QComboBox()
        self.direction_combo.addItems(
            [Direction.LONG.value, Direction.SHORT.value])

        self.offset_combo = QtWidgets.QComboBox()
        self.offset_combo.addItems([offset.value for offset in Offset])

        self.order_type_combo = QtWidgets.QComboBox()
        self.order_type_combo.addItems(
            [order_type.value for order_type in OrderType])

        double_validator = QtGui.QDoubleValidator()
        double_validator.setBottom(0)

        self.price_line = QtWidgets.QLineEdit()
        self.price_line.setValidator(double_validator)

        self.volume_line = QtWidgets.QLineEdit()
        self.volume_line.setValidator(double_validator)

        self.gateway_combo = QtWidgets.QComboBox()
        self.gateway_combo.addItems(self.main_engine.get_all_gateway_names())

        self.price_check = QtWidgets.QCheckBox()
        self.price_check.setToolTip("设置价格随行情更新")

        send_button = QtWidgets.QPushButton("委托")
        send_button.clicked.connect(self.send_order)

        cancel_button = QtWidgets.QPushButton("全撤")
        cancel_button.clicked.connect(self.cancel_all)

        grid = QtWidgets.QGridLayout()
        grid.addWidget(QtWidgets.QLabel("交易所"), 0, 0)
        grid.addWidget(QtWidgets.QLabel("代码"), 1, 0)
        grid.addWidget(QtWidgets.QLabel("名称"), 2, 0)
        grid.addWidget(QtWidgets.QLabel("方向"), 3, 0)
        grid.addWidget(QtWidgets.QLabel("开平"), 4, 0)
        grid.addWidget(QtWidgets.QLabel("类型"), 5, 0)
        grid.addWidget(QtWidgets.QLabel("价格"), 6, 0)
        grid.addWidget(QtWidgets.QLabel("数量"), 7, 0)
        grid.addWidget(QtWidgets.QLabel("接口"), 8, 0)
        grid.addWidget(self.exchange_combo, 0, 1, 1, 2)
        grid.addWidget(self.symbol_line, 1, 1, 1, 2)
        grid.addWidget(self.name_line, 2, 1, 1, 2)
        grid.addWidget(self.direction_combo, 3, 1, 1, 2)
        grid.addWidget(self.offset_combo, 4, 1, 1, 2)
        grid.addWidget(self.order_type_combo, 5, 1, 1, 2)
        grid.addWidget(self.price_line, 6, 1, 1, 1)
        grid.addWidget(self.price_check, 6, 2, 1, 1)
        grid.addWidget(self.volume_line, 7, 1, 1, 2)
        grid.addWidget(self.gateway_combo, 8, 1, 1, 2)
        grid.addWidget(send_button, 9, 0, 1, 3)
        grid.addWidget(cancel_button, 10, 0, 1, 3)

        # Market depth display area
        bid_color = "rgb(255,174,201)"
        ask_color = "rgb(160,255,160)"

        self.bp1_label = self.create_label(bid_color)
        self.bp2_label = self.create_label(bid_color)
        self.bp3_label = self.create_label(bid_color)
        self.bp4_label = self.create_label(bid_color)
        self.bp5_label = self.create_label(bid_color)

        self.bv1_label = self.create_label(
            bid_color, alignment=QtCore.Qt.AlignRight)
        self.bv2_label = self.create_label(
            bid_color, alignment=QtCore.Qt.AlignRight)
        self.bv3_label = self.create_label(
            bid_color, alignment=QtCore.Qt.AlignRight)
        self.bv4_label = self.create_label(
            bid_color, alignment=QtCore.Qt.AlignRight)
        self.bv5_label = self.create_label(
            bid_color, alignment=QtCore.Qt.AlignRight)

        self.ap1_label = self.create_label(ask_color)
        self.ap2_label = self.create_label(ask_color)
        self.ap3_label = self.create_label(ask_color)
        self.ap4_label = self.create_label(ask_color)
        self.ap5_label = self.create_label(ask_color)

        self.av1_label = self.create_label(
            ask_color, alignment=QtCore.Qt.AlignRight)
        self.av2_label = self.create_label(
            ask_color, alignment=QtCore.Qt.AlignRight)
        self.av3_label = self.create_label(
            ask_color, alignment=QtCore.Qt.AlignRight)
        self.av4_label = self.create_label(
            ask_color, alignment=QtCore.Qt.AlignRight)
        self.av5_label = self.create_label(
            ask_color, alignment=QtCore.Qt.AlignRight)

        self.lp_label = self.create_label()
        self.return_label = self.create_label(alignment=QtCore.Qt.AlignRight)

        form = QtWidgets.QFormLayout()
        form.addRow(self.ap5_label, self.av5_label)
        form.addRow(self.ap4_label, self.av4_label)
        form.addRow(self.ap3_label, self.av3_label)
        form.addRow(self.ap2_label, self.av2_label)
        form.addRow(self.ap1_label, self.av1_label)
        form.addRow(self.lp_label, self.return_label)
        form.addRow(self.bp1_label, self.bv1_label)
        form.addRow(self.bp2_label, self.bv2_label)
        form.addRow(self.bp3_label, self.bv3_label)
        form.addRow(self.bp4_label, self.bv4_label)
        form.addRow(self.bp5_label, self.bv5_label)

        # Overall layout
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(grid)
        vbox.addLayout(form)
        self.setLayout(vbox)

    def create_label(
        self,
        color: str = "",
        alignment: int = QtCore.Qt.AlignLeft
    ) -> QtWidgets.QLabel:
        """
        Create label with certain font color.
        """
        label = QtWidgets.QLabel()
        if color:
            label.setStyleSheet(f"color:{color}")
        label.setAlignment(alignment)
        return label

    def register_event(self) -> None:
        """"""
        self.signal_tick.connect(self.process_tick_event)
        self.event_engine.register(EVENT_TICK, self.signal_tick.emit)

    def process_tick_event(self, event: Event) -> None:
        """"""
        tick = event.data
        if tick.vt_symbol != self.vt_symbol:
            return

        price_digits = self.price_digits

        self.lp_label.setText(f"{tick.last_price:.{price_digits}f}")
        self.bp1_label.setText(f"{tick.bid_price_1:.{price_digits}f}")
        self.bv1_label.setText(str(tick.bid_volume_1))
        self.ap1_label.setText(f"{tick.ask_price_1:.{price_digits}f}")
        self.av1_label.setText(str(tick.ask_volume_1))

        if tick.pre_close:
            r = (tick.last_price / tick.pre_close - 1) * 100
            self.return_label.setText(f"{r:.2f}%")

        if tick.bid_price_2:
            self.bp2_label.setText(f"{tick.bid_price_2:.{price_digits}f}")
            self.bv2_label.setText(str(tick.bid_volume_2))
            self.ap2_label.setText(f"{tick.ask_price_2:.{price_digits}f}")
            self.av2_label.setText(str(tick.ask_volume_2))

            self.bp3_label.setText(f"{tick.bid_price_3:.{price_digits}f}")
            self.bv3_label.setText(str(tick.bid_volume_3))
            self.ap3_label.setText(f"{tick.ask_price_3:.{price_digits}f}")
            self.av3_label.setText(str(tick.ask_volume_3))

            self.bp4_label.setText(f"{tick.bid_price_4:.{price_digits}f}")
            self.bv4_label.setText(str(tick.bid_volume_4))
            self.ap4_label.setText(f"{tick.ask_price_4:.{price_digits}f}")
            self.av4_label.setText(str(tick.ask_volume_4))

            self.bp5_label.setText(f"{tick.bid_price_5:.{price_digits}f}")
            self.bv5_label.setText(str(tick.bid_volume_5))
            self.ap5_label.setText(f"{tick.ask_price_5:.{price_digits}f}")
            self.av5_label.setText(str(tick.ask_volume_5))

        if self.price_check.isChecked():
            self.price_line.setText(f"{tick.last_price:.{price_digits}f}")

    def set_vt_symbol(self) -> None:
        """
        Set the tick depth data to monitor by vt_symbol.
        """
        symbol = str(self.symbol_line.text())
        if not symbol:
            return

        # Generate vt_symbol from symbol and exchange
        exchange_value = str(self.exchange_combo.currentText())
        vt_symbol = f"{symbol}.{exchange_value}"

        if vt_symbol == self.vt_symbol:
            return
        self.vt_symbol = vt_symbol

        # Update name line widget and clear all labels
        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            self.name_line.setText("")
            gateway_name = self.gateway_combo.currentText()
        else:
            self.name_line.setText(contract.name)
            gateway_name = contract.gateway_name

            # Update gateway combo box.
            ix = self.gateway_combo.findText(gateway_name)
            self.gateway_combo.setCurrentIndex(ix)

            # Update price digits
            self.price_digits = get_digits(contract.pricetick)

        self.clear_label_text()
        self.volume_line.setText("")
        self.price_line.setText("")

        # Subscribe tick data
        req = SubscribeRequest(
            symbol=symbol, exchange=Exchange(exchange_value)
        )

        self.main_engine.subscribe(req, gateway_name)

    def clear_label_text(self) -> None:
        """
        Clear text on all labels.
        """
        self.lp_label.setText("")
        self.return_label.setText("")

        self.bv1_label.setText("")
        self.bv2_label.setText("")
        self.bv3_label.setText("")
        self.bv4_label.setText("")
        self.bv5_label.setText("")

        self.av1_label.setText("")
        self.av2_label.setText("")
        self.av3_label.setText("")
        self.av4_label.setText("")
        self.av5_label.setText("")

        self.bp1_label.setText("")
        self.bp2_label.setText("")
        self.bp3_label.setText("")
        self.bp4_label.setText("")
        self.bp5_label.setText("")

        self.ap1_label.setText("")
        self.ap2_label.setText("")
        self.ap3_label.setText("")
        self.ap4_label.setText("")
        self.ap5_label.setText("")

    def send_order(self) -> None:
        """
        Send new order manually.
        """
        symbol = str(self.symbol_line.text())
        if not symbol:
            QtWidgets.QMessageBox.critical(self, "委托失败", "请输入合约代码")
            return

        volume_text = str(self.volume_line.text())
        if not volume_text:
            QtWidgets.QMessageBox.critical(self, "委托失败", "请输入委托数量")
            return
        volume = float(volume_text)

        price_text = str(self.price_line.text())
        if not price_text:
            price = 0
        else:
            price = float(price_text)

        req = OrderRequest(
            symbol=symbol,
            exchange=Exchange(str(self.exchange_combo.currentText())),
            direction=Direction(str(self.direction_combo.currentText())),
            type=OrderType(str(self.order_type_combo.currentText())),
            volume=volume,
            price=price,
            offset=Offset(str(self.offset_combo.currentText())),
        )

        gateway_name = str(self.gateway_combo.currentText())

        self.main_engine.send_order(req, gateway_name)

    def cancel_all(self) -> None:
        """
        Cancel all active orders.
        """
        order_list = self.main_engine.get_all_active_orders()
        for order in order_list:
            req = order.create_cancel_request()
            self.main_engine.cancel_order(req, order.gateway_name)

    def update_with_cell(self, cell: BaseCell) -> None:
        """"""
        data = cell.get_data()

        self.symbol_line.setText(data.symbol)
        self.exchange_combo.setCurrentIndex(
            self.exchange_combo.findText(data.exchange.value)
        )

        self.set_vt_symbol()

        if isinstance(data, PositionData):
            if data.direction == Direction.SHORT:
                direction = Direction.LONG
            else:
                direction = Direction.SHORT

            self.direction_combo.setCurrentIndex(
                self.direction_combo.findText(direction.value)
            )
            self.offset_combo.setCurrentIndex(
                self.offset_combo.findText(Offset.CLOSE.value)
            )
            self.volume_line.setText(str(data.volume))


class ActiveOrderMonitor(OrderMonitor):
    """
    Monitor which shows active order only.
    """

    def process_event(self, event) -> None:
        """
        Hides the row if order is not active.
        """
        super(ActiveOrderMonitor, self).process_event(event)

        order = event.data
        row_cells = self.cells[order.vt_orderid]
        row = self.row(row_cells["volume"])

        if order.is_active():
            self.showRow(row)
        else:
            self.hideRow(row)


class ContractManager(QtWidgets.QWidget):
    """
    Query contract data available to trade in system.
    """

    headers: Dict[str, str] = {
        "vt_symbol": "本地代码",
        "symbol": "代码",
        "exchange": "交易所",
        "name": "名称",
        "product": "合约分类",
        "size": "合约乘数",
        "pricetick": "价格跳动",
        "min_volume": "最小委托量",
        "gateway_name": "交易接口",
    }

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle("合约查询")
        self.resize(1000, 600)

        self.filter_line = QtWidgets.QLineEdit()
        self.filter_line.setPlaceholderText("输入合约代码或者交易所，留空则查询所有合约")

        self.button_show = QtWidgets.QPushButton("查询")
        self.button_show.clicked.connect(self.show_contracts)

        labels = []
        for name, display in self.headers.items():
            label = f"{display}\n{name}"
            labels.append(label)

        self.contract_table = QtWidgets.QTableWidget()
        self.contract_table.setColumnCount(len(self.headers))
        self.contract_table.setHorizontalHeaderLabels(labels)
        self.contract_table.verticalHeader().setVisible(False)
        self.contract_table.setEditTriggers(self.contract_table.NoEditTriggers)
        self.contract_table.setAlternatingRowColors(True)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(self.filter_line)
        hbox.addWidget(self.button_show)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.contract_table)

        self.setLayout(vbox)

    def show_contracts(self) -> None:
        """
        Show contracts by symbol
        """
        flt = str(self.filter_line.text())

        all_contracts = self.main_engine.get_all_contracts()
        if flt:
            contracts = [
                contract for contract in all_contracts if flt in contract.vt_symbol
            ]
        else:
            contracts = all_contracts

        self.contract_table.clearContents()
        self.contract_table.setRowCount(len(contracts))

        for row, contract in enumerate(contracts):
            for column, name in enumerate(self.headers.keys()):
                value = getattr(contract, name)
                if isinstance(value, Enum):
                    cell = EnumCell(value, contract)
                else:
                    cell = BaseCell(value, contract)
                self.contract_table.setItem(row, column, cell)

        self.contract_table.resizeColumnsToContents()


class AboutDialog(QtWidgets.QDialog):
    """
    About VN Trader.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle(f"关于VN Trader")

        text = f"""
            By Traders, For Traders.


            License：MIT
            Website：www.vnpy.com
            Github：www.github.com/vnpy/vnpy


            vn.py - {vnpy.__version__}
            Python - {platform.python_version()}
            PyQt5 - {Qt.PYQT_VERSION_STR}
            Numpy - {np.__version__}
            RQData - {rqdatac.__version__}
            """

        label = QtWidgets.QLabel()
        label.setText(text)
        label.setMinimumWidth(500)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(label)
        self.setLayout(vbox)


class GlobalDialog(QtWidgets.QDialog):
    """
    Start connection of a certain gateway.
    """

    def __init__(self):
        """"""
        super().__init__()

        self.widgets: Dict[str, Any] = {}

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle("全局配置")
        self.setMinimumWidth(800)

        settings = copy(SETTINGS)
        settings.update(load_json(SETTING_FILENAME))

        # Initialize line edits and form layout based on setting.
        form = QtWidgets.QFormLayout()

        for field_name, field_value in settings.items():
            field_type = type(field_value)
            widget = QtWidgets.QLineEdit(str(field_value))

            form.addRow(f"{field_name} <{field_type.__name__}>", widget)
            self.widgets[field_name] = (widget, field_type)

        button = QtWidgets.QPushButton("确定")
        button.clicked.connect(self.update_setting)
        form.addRow(button)

        scroll_widget = QtWidgets.QWidget()
        scroll_widget.setLayout(form)

        scroll_area = QtWidgets.QScrollArea()
        scroll_area.setWidgetResizable(True)
        scroll_area.setWidget(scroll_widget)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(scroll_area)
        self.setLayout(vbox)

    def update_setting(self) -> None:
        """
        Get setting value from line edits and update global setting file.
        """
        settings = {}
        for field_name, tp in self.widgets.items():
            widget, field_type = tp
            value_text = widget.text()

            if field_type == bool:
                if value_text == "True":
                    field_value = True
                else:
                    field_value = False
            else:
                field_value = field_type(value_text)

            settings[field_name] = field_value

        QtWidgets.QMessageBox.information(
            self,
            "注意",
            "全局配置的修改需要重启VN Trader后才会生效！",
            QtWidgets.QMessageBox.Ok
        )

        save_json(SETTING_FILENAME, settings)
        self.accept()
