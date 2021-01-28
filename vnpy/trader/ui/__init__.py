import ctypes
import platform
import sys
import traceback
import webbrowser
import types

import qdarkstyle
from PyQt5 import QtGui, QtWidgets, QtCore

from .mainwindow import MainWindow
from ..setting import SETTINGS
from ..utility import get_icon_path


def excepthook(exctype: type, value: Exception, tb: types.TracebackType) -> None:
    """
    Raise exception under debug mode, otherwise
    show exception detail with QMessageBox.
    """
    sys.__excepthook__(exctype, value, tb)

    msg = "".join(traceback.format_exception(exctype, value, tb))
    dialog = ExceptionDialog(msg)
    dialog.exec_()


def create_qapp(app_name: str = "VN Trader") -> QtWidgets.QApplication:
    """
    Create Qt Application.
    """
    sys.excepthook = excepthook

    QtWidgets.QApplication.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)

    qapp = QtWidgets.QApplication(sys.argv)
    qapp.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())

    font = QtGui.QFont(SETTINGS["font.family"], SETTINGS["font.size"])
    qapp.setFont(font)

    icon = QtGui.QIcon(get_icon_path(__file__, "vnpy.ico"))
    qapp.setWindowIcon(icon)

    if "Windows" in platform.uname():
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(
            app_name
        )

    return qapp


class ExceptionDialog(QtWidgets.QDialog):
    """"""

    def __init__(self, msg: str):
        """"""
        super().__init__()

        self.msg: str = msg

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle("触发异常")
        self.setFixedSize(600, 600)

        self.msg_edit = QtWidgets.QTextEdit()
        self.msg_edit.setText(self.msg)
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

    def _copy_text(self) -> None:
        """"""
        self.msg_edit.selectAll()
        self.msg_edit.copy()

    def _open_community(self) -> None:
        """"""
        webbrowser.open("https://www.vnpy.com/forum/forum/2-ti-wen-qiu-zhu")
