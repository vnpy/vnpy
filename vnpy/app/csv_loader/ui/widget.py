"""
Author: nanoric

UI is designed by Qt Designer. source at csv_loader.ui
compile:
```
pyuic5 csv_loader.ui -o uic/uic_csv_loader.py
```
"""

from gettext import gettext as _

from vnpy.event import EventEngine
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtWidgets, QtCore

from .uic.uic_csv_loader import Ui_CsvLoader
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
        self.setWindowFlags(
            (self.windowFlags() | QtCore.Qt.CustomizeWindowHint)
            & ~QtCore.Qt.WindowMaximizeButtonHint)

        self.ui = Ui_CsvLoader()
        self.ui.setupUi(self)

        for i in Interval:
            self.ui.interval_combo.addItem(str(i.name), i)

        for i in Exchange:
            self.ui.exchange_combo.addItem(str(i.name), i)

    def on_choose_button_pressed(self):
        """"""
        result: str = QtWidgets.QFileDialog.getOpenFileName(self)
        filename = result[0]
        if filename:
            self.ui.file_edit.setText(filename)

    def on_load_button_pressed(self):
        """"""
        file_path = self.ui.file_edit.text()
        symbol = self.ui.symbol_edit.text()
        exchange = self.ui.exchange_combo.currentData()
        interval = self.ui.interval_combo.currentData()
        datetime_head = self.ui.datetime_edit.text()
        open_head = self.ui.open_edit.text()
        low_head = self.ui.low_edit.text()
        high_head = self.ui.high_edit.text()
        close_head = self.ui.close_edit.text()
        volume_head = self.ui.volume_edit.text()

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
            volume_head
        )

        msg = f"""
        CSV载入成功
        代码：{symbol}
        交易所：{exchange.value}
        周期：{interval.value}
        起始：{start}
        结束：{end}
        总数量：{count}
        """
        QtWidgets.QMessageBox.information(self, _("载入成功！"), msg)
