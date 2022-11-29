from pathlib import Path

from vnpy.event import EventEngine, Event
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtWidgets, QtCore
from vnpy.trader.object import LogData
from ..engine import APP_NAME, EVENT_RTD_LOG


class RtdManager(QtWidgets.QWidget):
    """"""
    signal_log = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine
        self.rm_engine = main_engine.get_engine(APP_NAME)

        self.init_ui()
        self.register_event()

    def init_ui(self) -> None:
        """
        Init widget ui components.
        """
        self.setWindowTitle("Excel RTD")
        self.resize(600, 600)

        module_path = Path(__file__).parent.parent
        client_path = module_path.joinpath("vnpy_rtd.py")
        self.client_line = QtWidgets.QLineEdit(str(client_path))
        self.client_line.setReadOnly(True)

        copy_button = QtWidgets.QPushButton("复制")
        copy_button.clicked.connect(self.copy_client_path)

        self.log_monitor = QtWidgets.QTextEdit()
        self.log_monitor.setReadOnly(True)

        self.port_label = QtWidgets.QLabel(
            "使用Socket端口：请求回应9001、广播推送9002"
        )

        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(self.client_line)
        hbox.addWidget(copy_button)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.log_monitor)
        vbox.addWidget(self.port_label)
        self.setLayout(vbox)

    def register_event(self) -> None:
        """
        Register event handler.
        """
        self.signal_log.connect(self.process_log_event)

        self.event_engine.register(EVENT_RTD_LOG, self.signal_log.emit)

    def process_log_event(self, event: Event) -> None:
        """
        Show log message in monitor.
        """
        log: LogData = event.data

        msg = f"{log.time}: {log.msg}"
        self.log_monitor.append(msg)

    def copy_client_path(self) -> None:
        """
        Copy path of client python file to clipboard.
        """
        self.client_line.selectAll()
        self.client_line.copy()
