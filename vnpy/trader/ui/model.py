import csv
from typing import Any, Dict
from tzlocal import get_localzone
from PySide6.QtCore import QAbstractTableModel, QModelIndex, Qt
from PySide6 import QtWidgets, QtGui
from ..engine import MainEngine, Event, EventEngine
from ..constant import Direction
from ..event import (
    EVENT_TICK,
    EVENT_TRADE,
    EVENT_ORDER,
    EVENT_POSITION,
    EVENT_ACCOUNT,
    EVENT_LOG
)


COLOR_LONG = QtGui.QColor("red")
COLOR_SHORT = QtGui.QColor("green")
COLOR_BID = QtGui.QColor(255, 174, 201)
COLOR_ASK = QtGui.QColor(160, 255, 160)


class BaseColumn:
    """
    General column used in tableview.
    """
    def __init__(self, content):
        """"""
        self.get_content(content)
        self.text_color(content)
        self.alignment()

    def get_content(self, content) -> None:
        """
        Set text content.
        """
        self.content = str(content)

    def text_color(self, content) -> None:
        """
        Set text color.
        """
        self._color = QtGui.QColor("white")

    def alignment(self) -> None:
        """
        Set text alignment.
        """
        self._alignment = int(Qt.AlignCenter | Qt.AlignVCenter)

    def get_data(self) -> Dict[str, Any]:
        """
        Get data dict.
        """
        return {
            "content": self.content,
            "color": self._color,
            "alignment": self._alignment,
        }


class EnumColumn(BaseColumn):
    """
    Column used for showing enum data.
    """
    def __init__(self, content):
        super().__init__(content)

    def get_content(self, content) -> None:
        """
        Set text using enum.constant.value.
        """
        self.content = str(content.value)


class DirectionColumn(EnumColumn):
    """
    Column used for showing direction data.
    """
    def __init__(self, content):
        super().__init__(content)

    def text_color(self, content) -> None:
        """
        Column color is set according to direction.
        """
        if content is Direction.SHORT:
            self._color = COLOR_SHORT
        else:
            self._color = COLOR_LONG


class BidColumn(BaseColumn):
    """
    Column used for showing bid price and volume.
    """
    def __init__(self, content):
        super().__init__(content)

    def text_color(self, content) -> None:
        """
        Column color is set to bid color.
        """
        self._color = COLOR_BID


class AskColumn(BaseColumn):
    """
    Column used for showing ask price and volume.
    """
    def __init__(self, content):
        super().__init__(content)

    def text_color(self, content) -> None:
        """
        Column color is set to ask color.
        """
        self._color = COLOR_ASK


class PnlColumn(BaseColumn):
    """
    Column used for showing pnl data.
    """
    def __init__(self, content):
        super().__init__(content)

    def text_color(self, content) -> None:
        """
        Column color is set based on whether pnl is
        positive or negative.
        """
        if content < 0:
            self._color = COLOR_SHORT
        else:
            self._color = COLOR_LONG


class TimeColumn(BaseColumn):
    """
    Column used for showing time string from datetime object.
    """
    local_tz = get_localzone()

    def __init__(self, content):
        super().__init__(content)

    def get_content(self, content) -> None:
        """"""
        content = content.astimezone(self.local_tz)
        timestamp = content.strftime("%H:%M:%S")

        millisecond = int(content.microsecond / 1000)
        if millisecond:
            timestamp = f"{timestamp}.{millisecond}"
        else:
            timestamp = f"{timestamp}.000"

        self.content = timestamp


class MsgColumn(BaseColumn):
    """
    Column used for showing msg data.
    """
    def __init__(self, content):
        super().__init__(content)

    def alignment(self) -> None:
        """
        Set text alignment.
        """
        self._alignment = int(Qt.AlignLeft | Qt.AlignVCenter)


class BaseTableModel(QAbstractTableModel):
    """
    Base table model
    """
    event_type: str = ""
    data_key: str = ""
    headers: dict = {}

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()
        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine
        self.register_event()

        self.rows: Dict[str, dict] = {}
        self.indices = []

        self.header_name = {i: k for i, k in enumerate(self.headers.keys())}
        self.labels = [d["display"] for d in self.headers.values()]
        self.header_data = {i: k for i, k in enumerate(self.labels)}

    def register_event(self) -> None:
        """
        Register event handler into event engine.
        """
        self.event_engine.register(self.event_type, self.process_event)

    def process_event(self, event: Event) -> None:
        """
        Process new data from event and update into model.
        """
        data = event.data
        self.update_data(data)

    def rowCount(self, index=QModelIndex()):
        """"""
        return len(self.indices)

    def columnCount(self, index=QModelIndex()):
        """"""
        return len(self.headers)

    def data(self, index, role=Qt.DisplayRole):
        """
        Get data from model.
        """
        if not index.isValid() or not (0 <= index.row() < len(self.indices)):
            return ""

        indice = self.indices[index.row()]
        row = self.rows[indice]
        column = index.column()
        key = self.header_name[column]

        if role == Qt.DisplayRole:
            return row[key]["content"]
        elif role == Qt.TextColorRole:
            return row[key]["color"]
        elif role == Qt.TextAlignmentRole:
            return row[key]["alignment"]
        return None

    def headerData(self, section: int, orientation: Qt.Orientation, role: int = Qt.DisplayRole):
        """"""
        if role == Qt.TextAlignmentRole:
            if orientation == Qt.Horizontal:
                return int(Qt.AlignCenter | Qt.AlignVCenter)
            return int(Qt.AlignRight | Qt.AlignVCenter)
        if role != Qt.DisplayRole:
            return None
        if orientation == Qt.Horizontal:
            key = self.header_data[section]
            return key
        return int(section + 1)

    def updateRows(self, data):
        """"""
        self.beginResetModel()

        row: Dict[str, Any] = {}

        for header in self.headers:
            setting = self.headers[header]["column"]
            content = setting(data.__getattribute__(header))
            row[header] = content.get_data()

        row["_rawdata"] = data

        self.rows[data.__getattribute__(self.data_key)] = row

        self.endResetModel()
        return True

    def insertRows(self, data, position, rows=1, index=QModelIndex()):
        """"""
        self.beginInsertRows(QModelIndex(), position, position + rows - 1)

        row: Dict[str, Any] = {}

        for header in self.headers:
            setting = self.headers[header]["column"]
            content = setting(data.__getattribute__(header))
            row[header] = content.get_data()

        row["_rawdata"] = data

        self.rows[data.__getattribute__(self.data_key)] = row

        self.indices.insert(0, data.__getattribute__(self.data_key))

        self.endInsertRows()
        return True

    def removeRows(self, position, rows=1, index=QModelIndex()):
        """"""
        self.beginRemoveRows(QModelIndex(), position, position + rows - 1)
        indice = self.indices.pop(position)
        self.rows.pop(indice)
        self.endRemoveRows()
        return True

    def update_data(self, data):
        """"""
        if data.__getattribute__(self.data_key) in self.indices:
            self.updateRows(data)
        else:
            self.insertRows(data, 1)

    def save_csv(self, dir: QtWidgets):
        """
        Save table data into a csv file.
        """
        path, _ = QtWidgets.QFileDialog.getSaveFileName(
            dir, "保存数据", "", "CSV(*.csv)")

        if not path:
            return

        with open(path, "w") as f:
            writer = csv.writer(f, lineterminator="\n")

            if not self.headers:
                return

            writer.writerow(self.headers)

            for row in range(self.rowCount()):
                row_data = []
                for column in range(self.columnCount()):
                    item = self.index(row, column)
                    if item:
                        row_data.append(str(item.data()))
                    else:
                        row_data.append("")
                writer.writerow(row_data)

    def get_data(self, index: QModelIndex):
        """"""
        if not index.isValid() or not (0 <= index.row() < len(self.indices)):
            return ""

        indice = self.indices[index.row()]
        data = self.rows[indice]["_rawdata"]
        return data


class TickTableModel(BaseTableModel):
    """
    Table model for tick data.
    """
    event_type = EVENT_TICK
    data_key = "vt_symbol"
    headers = {
        "symbol": {"display": "代码", "column": BaseColumn},
        "exchange": {"display": "交易所", "column": EnumColumn},
        "name": {"display": "名称", "column": BaseColumn},
        "last_price": {"display": "最新价", "column": BaseColumn},
        "volume": {"display": "成交量", "column": BaseColumn},
        "open_price": {"display": "开盘价", "column": BaseColumn},
        "high_price": {"display": "最高价", "column": BaseColumn},
        "low_price": {"display": "最低价", "column": BaseColumn},
        "bid_price_1": {"display": "买1价", "column": BidColumn},
        "bid_volume_1": {"display": "买1量", "column": BidColumn},
        "ask_price_1": {"display": "卖1价", "column": AskColumn},
        "ask_volume_1": {"display": "卖1量", "column": AskColumn},
        "datetime": {"display": "时间", "column": TimeColumn},
        "gateway_name": {"display": "接口", "column": BaseColumn}
    }


class LogTableModel(BaseTableModel):
    """
    Table model for lag data.
    """
    event_type = EVENT_LOG
    data_key = "time"
    headers = {
        "time": {"display": "时间", "column": TimeColumn},
        "msg": {"display": "信息", "column": MsgColumn},
        "gateway_name": {"display": "接口", "column": BaseColumn}
    }


class TradeTableModel(BaseTableModel):
    """
    Table model for trade model.
    """
    event_type = EVENT_TRADE
    data_key = "vt_tradeid"
    headers: Dict[str, dict] = {
        "tradeid": {"display": "成交号", "column": BaseColumn},
        "orderid": {"display": "委托号", "column": BaseColumn},
        "symbol": {"display": "代码", "column": BaseColumn},
        "exchange": {"display": "交易所", "column": EnumColumn},
        "direction": {"display": "方向", "column": DirectionColumn},
        "offset": {"display": "开平", "column": EnumColumn},
        "price": {"display": "价格", "column": BaseColumn},
        "volume": {"display": "数量", "column": BaseColumn},
        "datetime": {"display": "时间", "column": TimeColumn},
        "gateway_name": {"display": "接口", "column": BaseColumn}
    }


class OrderTableModel(BaseTableModel):
    """
    Table model for order model.
    """
    event_type = EVENT_ORDER
    data_key = "vt_orderid"
    headers: Dict[str, dict] = {
        "orderid": {"display": "委托号", "column": BaseColumn},
        "reference": {"display": "来源", "column": BaseColumn},
        "symbol": {"display": "代码", "column": BaseColumn},
        "exchange": {"display": "交易所", "column": EnumColumn},
        "type": {"display": "类型", "column": EnumColumn},
        "direction": {"display": "方向", "column": DirectionColumn},
        "offset": {"display": "开平", "column": EnumColumn},
        "price": {"display": "价格", "column": BaseColumn},
        "volume": {"display": "总数量", "column": BaseColumn},
        "traded": {"display": "已成交", "column": BaseColumn},
        "status": {"display": "状态", "column": EnumColumn},
        "datetime": {"display": "时间", "column": TimeColumn},
        "gateway_name": {"display": "接口", "column": BaseColumn}
    }

    def cancel_order(self, index: QModelIndex):
        if not index.isValid() or not (0 <= index.row() < len(self.indices)):
            return ""

        indice = self.indices[index.row()]
        order = self.rows[indice]["_rawdata"]
        req = order.create_cancel_request()
        self.main_engine.cancel_order(req, order.gateway_name)


class ActiveOrderModel(OrderTableModel):
    """
    Table model for activate order data.
    """
    def process_event(self, event) -> None:
        """
        Remove the row if order is not active.
        """
        super().process_event(event)

        order = event.data

        if not order.is_active():
            indice = self.indices.index(order.__getattribute__(self.data_key))
            self.removeRows(indice)


class PositionTableModel(BaseTableModel):
    """
    Table model for position data.
    """
    event_type = EVENT_POSITION
    data_key = "vt_positionid"
    headers = {
        "symbol": {"display": "代码", "column": BaseColumn},
        "exchange": {"display": "交易所", "column": EnumColumn},
        "direction": {"display": "方向", "column": DirectionColumn},
        "volume": {"display": "数量", "column": BaseColumn},
        "yd_volume": {"display": "昨仓", "column": BaseColumn},
        "frozen": {"display": "冻结", "column": BaseColumn},
        "price": {"display": "均价", "column": BaseColumn},
        "pnl": {"display": "盈亏", "column": PnlColumn},
        "gateway_name": {"display": "接口", "column": BaseColumn}
    }


class AccountTableModel(BaseTableModel):
    """
    Table model for account data.
    """
    event_type = EVENT_ACCOUNT
    data_key = "vt_accountid"
    headers = {
        "accountid": {"display": "账号", "column": BaseColumn},
        "balance": {"display": "余额", "column": BaseColumn},
        "frozen": {"display": "冻结", "column": BaseColumn},
        "available": {"display": "可用", "column": BaseColumn},
        "gateway_name": {"display": "接口", "column": BaseColumn}
    }
