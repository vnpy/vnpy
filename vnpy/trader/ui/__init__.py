import platform
import ctypes

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

    if 'Windows' in platform.uname():
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(
            'VN Trader')

    return qapp