"""
Author: Zehua Wei (nanoric)
"""

from vnpy.event import EventEngine
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtCore, QtWidgets

from ..engine import APP_NAME


class CsvLoaderWidget(QtWidgets.QWidget):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.engine = main_engine.get_engine(APP_NAME)

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("CSV载入")
        self.setFixedWidth(300)

        self.setWindowFlags(
            (self.windowFlags() | QtCore.Qt.CustomizeWindowHint)
            & ~QtCore.Qt.WindowMaximizeButtonHint)

        file_button = QtWidgets.QPushButton("选择文件")
        file_button.clicked.connect(self.select_file)

        load_button = QtWidgets.QPushButton("载入数据")
        load_button.clicked.connect(self.load_data)

        self.file_edit = QtWidgets.QLineEdit()
        self.symbol_edit = QtWidgets.QLineEdit()

        self.exchange_combo = QtWidgets.QComboBox()
        for i in Exchange:
            self.exchange_combo.addItem(str(i.name), i)

        self.interval_combo = QtWidgets.QComboBox()
        for i in Interval:
            self.interval_combo.addItem(str(i.name), i)

        self.datetime_edit = QtWidgets.QLineEdit("Datetime")
        self.open_edit = QtWidgets.QLineEdit("Open")
        self.high_edit = QtWidgets.QLineEdit("High")
        self.low_edit = QtWidgets.QLineEdit("Low")
        self.close_edit = QtWidgets.QLineEdit("Close")
        self.volume_edit = QtWidgets.QLineEdit("Volume")

        self.format_edit = QtWidgets.QLineEdit("%Y-%m-%d %H:%M:%S")

        info_label = QtWidgets.QLabel("合约信息")
        info_label.setAlignment(QtCore.Qt.AlignCenter)

        head_label = QtWidgets.QLabel("表头信息")
        head_label.setAlignment(QtCore.Qt.AlignCenter)

        format_label = QtWidgets.QLabel("格式信息")
        format_label.setAlignment(QtCore.Qt.AlignCenter)

        form = QtWidgets.QFormLayout()
        form.addRow(file_button, self.file_edit)
        form.addRow(QtWidgets.QLabel())
        form.addRow(info_label)
        form.addRow("代码", self.symbol_edit)
        form.addRow("交易所", self.exchange_combo)
        form.addRow("周期", self.interval_combo)
        form.addRow(QtWidgets.QLabel())
        form.addRow(head_label)
        form.addRow("时间戳", self.datetime_edit)
        form.addRow("开盘价", self.open_edit)
        form.addRow("最高价", self.high_edit)
        form.addRow("最低价", self.low_edit)
        form.addRow("收盘价", self.close_edit)
        form.addRow("成交量", self.volume_edit)
        form.addRow(QtWidgets.QLabel())
        form.addRow(format_label)
        form.addRow("时间格式", self.format_edit)
        form.addRow(QtWidgets.QLabel())
        form.addRow(load_button)

        self.setLayout(form)

    def select_file(self):
        """"""
        result: str = QtWidgets.QFileDialog.getOpenFileName(
            self, filter="CSV (*.csv)")
        filename = result[0]
        if filename:
            self.file_edit.setText(filename)

    def load_data(self):
        """"""
        file_path = self.file_edit.text()
        symbol = self.symbol_edit.text()
        exchange = self.exchange_combo.currentData()
        interval = self.interval_combo.currentData()
        datetime_head = self.datetime_edit.text()
        open_head = self.open_edit.text()
        low_head = self.low_edit.text()
        high_head = self.high_edit.text()
        close_head = self.close_edit.text()
        volume_head = self.volume_edit.text()
        datetime_format = self.format_edit.text()

        start, end, count = self.engine.load(
            file_path,
            symbol,
            exchange,
            interval,
            datetime_head,
            open_head,
            high_head,
            low_head,
            close_head,
            volume_head,
            datetime_format
        )

        msg = f"\
        CSV载入成功\n\
        代码：{symbol}\n\
        交易所：{exchange.value}\n\
        周期：{interval.value}\n\
        起始：{start}\n\
        结束：{end}\n\
        总数量：{count}\n\
        "
        QtWidgets.QMessageBox.information(self, "载入成功！", msg)
