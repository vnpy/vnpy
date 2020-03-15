from datetime import datetime


from vnpy.event import Event, EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtCore, QtWidgets
from vnpy.trader.event import EVENT_CONTRACT

from ..engine import (
    APP_NAME,
    EVENT_RECORDER_LOG,
    EVENT_RECORDER_UPDATE,
    EVENT_RECORDER_EXCEPTION
)


class RecorderManager(QtWidgets.QWidget):
    """"""

    signal_log = QtCore.pyqtSignal(Event)
    signal_update = QtCore.pyqtSignal(Event)
    signal_contract = QtCore.pyqtSignal(Event)
    signal_exception = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine
        self.recorder_engine = main_engine.get_engine(APP_NAME)

        self.init_ui()
        self.register_event()
        self.recorder_engine.put_event()

    def init_ui(self):
        """"""
        self.setWindowTitle("行情记录")
        self.resize(1000, 600)

        # Create widgets
        self.symbol_line = QtWidgets.QLineEdit()
        self.symbol_line.setFixedHeight(
            self.symbol_line.sizeHint().height() * 2)

        contracts = self.main_engine.get_all_contracts()
        self.vt_symbols = [contract.vt_symbol for contract in contracts]

        self.symbol_completer = QtWidgets.QCompleter(self.vt_symbols)
        self.symbol_completer.setFilterMode(QtCore.Qt.MatchContains)
        self.symbol_completer.setCompletionMode(
            self.symbol_completer.PopupCompletion)
        self.symbol_line.setCompleter(self.symbol_completer)

        add_bar_button = QtWidgets.QPushButton("添加")
        add_bar_button.clicked.connect(self.add_bar_recording)

        remove_bar_button = QtWidgets.QPushButton("移除")
        remove_bar_button.clicked.connect(self.remove_bar_recording)

        add_tick_button = QtWidgets.QPushButton("添加")
        add_tick_button.clicked.connect(self.add_tick_recording)

        remove_tick_button = QtWidgets.QPushButton("移除")
        remove_tick_button.clicked.connect(self.remove_tick_recording)

        self.bar_recording_edit = QtWidgets.QTextEdit()
        self.bar_recording_edit.setReadOnly(True)

        self.tick_recording_edit = QtWidgets.QTextEdit()
        self.tick_recording_edit.setReadOnly(True)

        self.log_edit = QtWidgets.QTextEdit()
        self.log_edit.setReadOnly(True)

        # Set layout
        grid = QtWidgets.QGridLayout()
        grid.addWidget(QtWidgets.QLabel("K线记录"), 0, 0)
        grid.addWidget(add_bar_button, 0, 1)
        grid.addWidget(remove_bar_button, 0, 2)
        grid.addWidget(QtWidgets.QLabel("Tick记录"), 1, 0)
        grid.addWidget(add_tick_button, 1, 1)
        grid.addWidget(remove_tick_button, 1, 2)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(QtWidgets.QLabel("本地代码"))
        hbox.addWidget(self.symbol_line)
        hbox.addWidget(QtWidgets.QLabel("     "))
        hbox.addLayout(grid)
        hbox.addStretch()

        grid2 = QtWidgets.QGridLayout()
        grid2.addWidget(QtWidgets.QLabel("K线记录列表"), 0, 0)
        grid2.addWidget(QtWidgets.QLabel("Tick记录列表"), 0, 1)
        grid2.addWidget(self.bar_recording_edit, 1, 0)
        grid2.addWidget(self.tick_recording_edit, 1, 1)
        grid2.addWidget(self.log_edit, 2, 0, 1, 2)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addLayout(grid2)
        self.setLayout(vbox)

    def register_event(self):
        """"""
        self.signal_log.connect(self.process_log_event)
        self.signal_contract.connect(self.process_contract_event)
        self.signal_update.connect(self.process_update_event)
        self.signal_exception.connect(self.process_exception_event)

        self.event_engine.register(EVENT_CONTRACT, self.signal_contract.emit)
        self.event_engine.register(
            EVENT_RECORDER_LOG, self.signal_log.emit)
        self.event_engine.register(
            EVENT_RECORDER_UPDATE, self.signal_update.emit)
        self.event_engine.register(EVENT_RECORDER_EXCEPTION, self.signal_exception.emit)

    def process_log_event(self, event: Event):
        """"""
        timestamp = datetime.now().strftime("%H:%M:%S")
        msg = f"{timestamp}\t{event.data}"
        self.log_edit.append(msg)

    def process_update_event(self, event: Event):
        """"""
        data = event.data

        self.bar_recording_edit.clear()
        bar_text = "\n".join(data["bar"])
        self.bar_recording_edit.setText(bar_text)

        self.tick_recording_edit.clear()
        tick_text = "\n".join(data["tick"])
        self.tick_recording_edit.setText(tick_text)

    def process_contract_event(self, event: Event):
        """"""
        contract = event.data
        self.vt_symbols.append(contract.vt_symbol)

        model = self.symbol_completer.model()
        model.setStringList(self.vt_symbols)

    def process_exception_event(self, event: Event):
        """"""
        exc_info = event.data
        raise exc_info[1].with_traceback(exc_info[2])

    def add_bar_recording(self):
        """"""
        vt_symbol = self.symbol_line.text()
        self.recorder_engine.add_bar_recording(vt_symbol)

    def add_tick_recording(self):
        """"""
        vt_symbol = self.symbol_line.text()
        self.recorder_engine.add_tick_recording(vt_symbol)

    def remove_bar_recording(self):
        """"""
        vt_symbol = self.symbol_line.text()
        self.recorder_engine.remove_bar_recording(vt_symbol)

    def remove_tick_recording(self):
        """"""
        vt_symbol = self.symbol_line.text()
        self.recorder_engine.remove_tick_recording(vt_symbol)
