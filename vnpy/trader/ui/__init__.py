import platform
import ctypes
from pathlib import Path

import qdarkstyle
from PySide2 import QtWidgets, QtGui

from .mainwindow import MainWindow
from ..setting import SETTINGS
from ..utility import get_icon_path


def create_qapp():
    """
    Create Qt Application.
    """
    qapp = QtWidgets.QApplication([])
    qapp.setStyleSheet(qdarkstyle.load_stylesheet_pyside2())

    font = QtGui.QFont(SETTINGS["font.family"], SETTINGS["font.size"])
    qapp.setFont(font)

    icon = QtGui.QIcon(get_icon_path(__file__, "vnpy.ico"))
    qapp.setWindowIcon(icon)

    if 'Windows' in platform.uname():
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(
            'VN Trader'
        )

    return qapp