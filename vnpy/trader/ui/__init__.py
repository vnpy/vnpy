import ctypes
import platform
import sys
import traceback

import qdarkstyle
from PyQt5 import QtGui, QtWidgets

from .mainwindow import MainWindow
from ..setting import SETTINGS
from ..utility import get_icon_path


def excepthook(exctype, value, tb):
    """异常捕捉钩子"""
    msg = "".join(traceback.format_exception(exctype, value, tb))
    QtWidgets.QMessageBox.critical(
        None, "Exception", msg, QtWidgets.QMessageBox.Ok
    )


def create_qapp():
    """
    Create Qt Application.
    """
    sys.excepthook = excepthook

    qapp = QtWidgets.QApplication([])
    qapp.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())

    font = QtGui.QFont(SETTINGS["font.family"], SETTINGS["font.size"])
    qapp.setFont(font)

    icon = QtGui.QIcon(get_icon_path(__file__, "vnpy.ico"))
    qapp.setWindowIcon(icon)

    if "Windows" in platform.uname():
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(
            "VN Trader"
        )

    return qapp
