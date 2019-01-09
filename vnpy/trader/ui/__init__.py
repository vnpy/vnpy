import platform
import ctypes
from pathlib import Path

import qdarkstyle
from PyQt5 import QtWidgets, QtGui

from .mainwindow import MainWindow
from ..setting import SETTINGS


def create_qapp():
    """
    Create Qt Application.
    """
    qapp = QtWidgets.QApplication([])
    qapp.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())

    font = QtGui.QFont(SETTINGS["font.family"], SETTINGS["font.size"])
    qapp.setFont(font)

    ui_path = Path(__file__).parent
    icon_path = ui_path.joinpath("ico", "vnpy.ico")
    icon = QtGui.QIcon(str(icon_path))
    qapp.setWindowIcon(icon)

    if 'Windows' in platform.uname():
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(
            'VN Trader'
        )

    return qapp