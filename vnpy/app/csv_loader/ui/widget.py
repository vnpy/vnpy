from PyQt5.QtWidgets import QFileDialog
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtWidgets

from .ui import CsvLoaderUI

from ..CsvLoader import CsvLoader


class CsvLoaderWidget(QtWidgets.QWidget):
    """"""
    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        super().__init__()
        self.loader = CsvLoader(main_engine, event_engine)
        self.ui: CsvLoaderUI = CsvLoaderUI(self)

    def on_choose_button_pressed(self):
        result: str = QFileDialog.getOpenFileName(self)
        filename = result[0]
        if filename:
            self.ui.file_edit.setText(filename)

    def on_load_button_pressed(self):
        self.loader.file_path = self.ui.file_edit.text()
        self.loader.symbol = self.ui.symbol_edit.text()
        self.loader.exchange = self.ui.exchange_combo.currentData()
        self.loader.interval = self.ui.interval_combo.currentData()
        self.loader.datetime_head = self.ui.datetime_edit.text()
        self.loader.open_head = self.ui.open_edit.text()
        self.loader.close_head = self.ui.close_edit.text()
        self.loader.low_head = self.ui.low_edit.text()
        self.loader.high_head = self.ui.high_edit.text()
        self.loader.volume_head = self.ui.volume_edit.text()

        self.loader.load()










