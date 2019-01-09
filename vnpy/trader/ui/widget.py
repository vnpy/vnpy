"""
Basic widgets for VN Trader.
"""

import csv
from typing import Any

from PyQt5 import QtWidgets, QtGui, QtCore

from vnpy.event import EventEngine, Event
from ..constant import DIRECTION_LONG, DIRECTION_SHORT, DIRECTION_NET
from ..engine import MainEngine
from ..event import (EVENT_TICK, EVENT_ORDER, EVENT_TRADE, EVENT_ACCOUNT,
                     EVENT_POSITION, EVENT_CONTRACT, EVENT_LOG)

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
        super(BaseCel, self).__init__()
        self.setTextAlignment(QtCore.Qt.AlignCenter)
        self.set_content(content, data)

    def set_content(self, content: Any, data: Any):
        """
        Set text content.
        """
        self.setText(str(content))
        self._data = data

    def get_data(self):
        """
        Get data object.
        """
        return self._data


class DirectionCell(BaseCell):
    """
    Cell used for showing direction data.
    """

    def __init__(self, content: str, data: Any):
        """"""
        super(DirectionCell, self).__init__(content, data)

    def set_content(self, content: Any, data: Any):
        """
        Cell color is set according to direction.
        """
        super(DirectionCell, self).set_content(content, data)

        if content == DIRECTION_SHORT:
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

        self.setForeground(COLOR_BLACK)
        self.setForeground(COLOR_BID)


class AskCell(BaseCell):
    """
    Cell used for showing ask price and volume.
    """

    def __init__(self, content: Any, data: Any):
        """"""
        super(AskCell, self).__init__(content, data)

        self.setForeground(COLOR_BLACK)
        self.setForeground(COLOR_ASK)


class PnlCell(BaseCell):
    """
    Cell used for showing pnl data.
    """

    def __init__(self, content: Any, data: Any):
        """"""
        super(PnlCell, self).__init__(content, data)

    def set_content(self, content: Any, data: Any):
        """
        Cell color is set based on whether pnl is 
        positive or negative.
        """
        super(PnlCell, self).set_content(content, data)

        if content.startswith("-"):
            self.setForeground(COLOR_SHORT)
        else:
            self.setForeground(COLOR_LONG)


class TimeCell(BaseCell):
    """
    Cell used for showing time string from datetime object.
    """

    def __init__(self, content: Any, data: Any):
        """"""
        super(TimeCell, self).__init__(content, data)

    def set_content(self, content: Any, data: Any):
        """
        Time format is 12:12:12.5
        """
        timestamp = content.strftime("%H:%M:%S")

        millisecond = int(content.microsecond / 1000)
        if millisecond:
            timestamp = f"{timestamp}.{millisecond}"

        self.setText(timestamp)
        self._data = data


class BaseMonitor(QtWidgets.QTableWidget):
    """
    Monitor data update in VN Trader.
    """

    event_type = ""
    data_key = ""
    sorting = False
    headers = {}

    signal = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super(BaseMonitor, self).__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine
        self.cells = {}

        self.init_ui()
        self.register_event()

    def init_ui(self):
        """"""
        self.init_table()
        self.init_menu()

    def init_table(self):
        """
        Initialize table.
        """
        self.setColumnCount(len(self.headers))

        labels = [d['display'] for d in self.headers.values()]
        self.setHorizontalHeaderLabels(labels)

        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
        self.setAlternatingRowColors(True)
        self.setSortingEnabled(self.sorting)

    def init_menu(self):
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

    def register_event(self):
        """
        Register event handler into event engine.
        """
        self.signal.connect(self.process_event)
        self.event_engine.register(self.event_type, self.process_event)

    def process_event(self, event):
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

    def insert_new_row(self, data):
        """
        Insert a new row at the top of table.
        """
        self.insertRow(0)

        row_cells = {}
        for column, header in enumerate(self.headers.keys()):
            setting = self.headers[header]

            content = data.__getattribute__(header)
            cell = setting['cell'](content, data)
            self.setItem(0, column, cell)

            if setting['update']:
                row_cells[header] = cell

        if self.data_key:
            key = data.__getattribute__(self.data_key)
            self.cells[key] = row_cells

    def update_old_row(self, data):
        """
        Update an old row in table.
        """
        key = data.__getattribute__(self.data_key)
        row_cells = self.cells[key]

        for header, cell in row_cells:
            content = data.__getattribute__(header)
            cell.set_content(content, data)

    def resize_columns(self):
        """
        Resize all columns according to contents.
        """
        self.horizontalHeader().resizeSections(
            QtWidgets.QHeaderView.ResizeToContents)

    def save_csv(self):
        """
        Save table data into a csv file
        """
        path, _ = QtWidgets.QFileDialog.getSaveFileName(self, "保存数据", "",
                                                        "CSV(*.csv)")

        if not path:
            return

        with open(path, "wb") as f:
            writer = csv.writer(f)
            writer.writerow(self.headers.keys())

            for row in range(self.rowCount()):
                row_data = []
                for column in range(self.columnCount()):
                    item = self.item(row, column)
                    if item:
                        row_data.append(text_type(item.text()))
                    else:
                        row_data.append("")
                writer.writerow(row_data)


class TickMonitor(BaseMonitor):
    """
    Monitor for tick data.
    """
    event_type = EVENT_TICK
    data_key = "vt_symbol"
    sorting = True

    headers = {
        'symbol': {
            'display': '代码',
            'cell': BaseCell,
            'update': False
        },
        'last_price': {
            'display': '最新价',
            'cell': BaseCell,
            'update': True
        },
        'volume': {
            'display': '成交量',
            'cell': BaseCell,
            'update': True
        },
        'open_price': {
            'display': '开盘价',
            'cell': BaseCell,
            'update': True
        },
        'high_price': {
            'display': '最高价',
            'cell': BaseCell,
            'update': True
        },
        'low_price': {
            'display': '最低价',
            'cell': BaseCell,
            'update': True
        },
        'bid_price_1': {
            'display': '买1价',
            'cell': BidCell,
            'update': True
        },
        'bid_volume_1': {
            'display': '买1量',
            'cell': BidCell,
            'update': True
        },
        'ask_price_1': {
            'display': '卖1价',
            'cell': AskCell,
            'update': True
        },
        'ask_volume_1': {
            'display': '卖1量',
            'cell': AskCell,
            'update': True
        },
        'time': {
            'display': '时间',
            'cell': TimeCell,
            'update': True
        },
        'gateway_name': {
            'display': '接口',
            'cell': BaseCell,
            'update': False
        }
    }


class LogMonitor(BaseMonitor):
    """
    Monitor for log data.
    """
    event_type = EVENT_LOG
    data_key = ""
    sorting = False

    headers = {
        'time': {
            'display': '时间',
            'cell': BaseCell,
            'update': False
        },
        'msg': {
            'display': '信息',
            'cell': BaseCell,
            'update': False
        },
        'gateway_name': {
            'display': '接口',
            'cell': BaseCell,
            'update': False
        }
    }

    def process_event(self, event):
        """Resize row heights for diplaying long log message."""
        super(LogMonitor, self).process_event(event)
        self.resizeRowToContents(0)


class TradeMonitor(BaseMonitor):
    """
    Monitor for trade data.
    """
    event_type = EVENT_TRADE
    data_key = ""
    sorting = True

    headers = {
        'tradeid': {
            'display': "成交号 ",
            'cell': BaseCell,
            'update': False
        },
        'orderid': {
            'display': '委托号',
            'cell': BaseCell,
            'update': False
        },
        'symbol': {
            'display': '代码',
            'cell': BaseCell,
            'update': False
        },
        'direction': {
            'display': '方向',
            'cell': DirectionCell,
            'update': False
        },
        'offset': {
            'display': '开平',
            'cell': BaseCell,
            'update': False
        },
        'price': {
            'display': '价格',
            'cell': BaseCell,
            'update': False
        },
        'volume': {
            'display': '数量',
            'cell': BaseCell,
            'update': False
        },
        'gateway_name': {
            'display': '接口',
            'cell': BaseCell,
            'update': False
        }
    }


class OrderMonitor(BaseMonitor):
    """
    Monitor for order data.
    """
    event_type = EVENT_ORDER
    data_key = "vt_orderid"
    sorting = True

    headers = {
        'orderid': {
            'display': '委托号',
            'cell': BaseCell,
            'update': False
        },
        'symbol': {
            'display': '代码',
            'cell': BaseCell,
            'update': False
        },
        'direction': {
            'display': '方向',
            'cell': DirectionCell,
            'update': False
        },
        'offset': {
            'display': '开平',
            'cell': BaseCell,
            'update': False
        },
        'price': {
            'display': '价格',
            'cell': BaseCell,
            'update': False
        },
        'volume': {
            'display': '总数量',
            'cell': BaseCell,
            'update': True
        },
        'traded': {
            'display': '已成交',
            'cell': BaseCell,
            'update': True
        },
        'status': {
            'display': '状态',
            'cell': BaseCell,
            'update': True
        },
        'time': {
            'display': '时间',
            'cell': BaseCell,
            'update': True
        },
        'gateway_name': {
            'display': '接口',
            'cell': BaseCell,
            'update': False
        }
    }

class PositionMonitor(BaseMonitor):
    """
    Monitor for position data.
    """
    event_type = EVENT_POSITION
    data_key = "vt_positionid"
    sorting = True

    headers = {
        'symbol': {
            'display': '代码',
            'cell': BaseCell,
            'update': False
        },
        'direction': {
            'display': '方向',
            'cell': DirectionCell,
            'update': False
        },
        'volume': {
            'display': '数量',
            'cell': BaseCell,
            'update': True
        },
        'frozen': {
            'display': '冻结',
            'cell': BaseCell,
            'update': True
        },
        'price': {
            'display': '均价',
            'cell': BaseCell,
            'update': False
        },
        'pnl': {
            'display': '盈亏',
            'cell': PnlCell,
            'update': True
        },
        'gateway_name': {
            'display': '接口',
            'cell': BaseCell,
            'update': False
        }
    }


class AccountMonitor(BaseMonitor):
    """
    Monitor for account data.
    """
    event_type = EVENT_ACCOUNT
    data_key = "vt_accountid"
    sorting = True

    headers = {
        'accountid': {
            'display': '账号',
            'cell': BaseCell,
            'update': False
        },
        'balance': {
            'display': '余额',
            'cell': BaseCell,
            'update': True
        },
        'frozen': {
            'display': '冻结',
            'cell': BaseCell,
            'update': True
        },
        'available': {
            'display': '可用',
            'cell': BaseCell,
            'update': True
        },
        'gateway_name': {
            'display': '接口',
            'cell': BaseCell,
            'update': False
        }
    }
