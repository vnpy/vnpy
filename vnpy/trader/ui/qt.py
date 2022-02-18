import ctypes
import platform
import sys
import traceback
import webbrowser
import types

import qdarkstyle
from PySide6 import QtGui, QtWidgets, QtCore

from ..setting import SETTINGS
from ..utility import get_icon_path


Qt = QtCore.Qt
QtCore.pyqtSignal = QtCore.Signal
QtWidgets.QAction = QtGui.QAction
QtCore.QDate.toPyDate = QtCore.QDate.toPython
QtCore.QDateTime.toPyDate = QtCore.QDateTime.toPython


def create_qapp(app_name: str = "Veighna Trader") -> QtWidgets.QApplication:
    """
    Create Qt Application.
    """
    # Set up dark stylesheet
    qapp = QtWidgets.QApplication(sys.argv)
    qapp.setStyleSheet(qdarkstyle.load_stylesheet(qt_api="pyside6"))

    # Set up font
    font = QtGui.QFont(SETTINGS["font.family"], SETTINGS["font.size"])
    qapp.setFont(font)

    # Set up icon
    icon = QtGui.QIcon(get_icon_path(__file__, "vnpy.ico"))
    qapp.setWindowIcon(icon)

    # Set up windows process ID
    if "Windows" in platform.uname():
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(
            app_name
        )

    # Hide help button for all dialogs
    # qapp.setAttribute(QtCore.Qt.AA_DisableWindowContextHelpButton)

    # Exception Handling
    exception_widget: ExceptionWidget = ExceptionWidget()

    def excepthook(exctype: type, value: Exception, tb: types.TracebackType) -> None:
        """Show exception detail with QMessageBox."""
        sys.__excepthook__(exctype, value, tb)

        msg = "".join(traceback.format_exception(exctype, value, tb))
        exception_widget.signal.emit(msg)

    sys.excepthook = excepthook

    return qapp


class ExceptionWidget(QtWidgets.QWidget):
    """"""
    signal = QtCore.pyqtSignal(str)

    def __init__(self, parent: QtWidgets.QWidget = None):
        """"""
        super().__init__(parent)

        self.init_ui()
        self.signal.connect(self.show_exception)

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle("触发异常")
        self.setFixedSize(600, 600)

        self.msg_edit = QtWidgets.QTextEdit()
        self.msg_edit.setReadOnly(True)

        copy_button = QtWidgets.QPushButton("复制")
        copy_button.clicked.connect(self._copy_text)

        community_button = QtWidgets.QPushButton("求助")
        community_button.clicked.connect(self._open_community)

        close_button = QtWidgets.QPushButton("关闭")
        close_button.clicked.connect(self.close)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(copy_button)
        hbox.addWidget(community_button)
        hbox.addWidget(close_button)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.msg_edit)
        vbox.addLayout(hbox)

        self.setLayout(vbox)

    def show_exception(self, msg: str) -> None:
        """"""
        self.msg_edit.setText(msg)
        self.show()

    def _copy_text(self) -> None:
        """"""
        self.msg_edit.selectAll()
        self.msg_edit.copy()

    def _open_community(self) -> None:
        """"""
        webbrowser.open("https://www.vnpy.com/forum/forum/2-ti-wen-qiu-zhu")
