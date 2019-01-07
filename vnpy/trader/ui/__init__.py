import platform
import ctypes

import qdarkstyle
from PyQt5 import QtWidgets

from .mainwindow import MainWindow


def create_qapp():
    """
    Create Qt Application.
    """
    qapp = QtWidgets.QApplication([])
    qapp.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())

    if 'Windows' in platform.uname():
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID(
            'VN Trader')

    return qapp