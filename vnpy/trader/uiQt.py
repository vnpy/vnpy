# encoding: UTF-8

import platform

from qtpy import QtWidgets, QtGui, QtCore

from vnpy.trader.vtGlobal import globalSetting
from vnpy.trader.vtFunction import loadIconPath

BASIC_FONT = None
try:
    family = globalSetting['fontFamily']
    size = globalSetting['fontSize']
    BASIC_FONT = QtGui.QFont(family, size)
except:
    BASIC_FONT = QtGui.QFont(u'微软雅黑', 12)

#----------------------------------------------------------------------
def createQApp():
    """创建PyQt应用对象"""
    # 创建Qt应用对象
    qApp = QtWidgets.QApplication([])
    
    # 设置Qt的皮肤
    if globalSetting['darkStyle']:
        try:
            import qdarkstyle
            qApp.setStyleSheet(qdarkstyle.load_stylesheet(pyside=False))
        except ImportError:
            pass
        
    # 设置Windows底部任务栏图标
    if 'Windows' in platform.uname():
        import ctypes
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('vn.trader')  
    
    # 设置Qt字体
    qApp.setFont(BASIC_FONT)
    
    # 设置Qt图标
    qApp.setWindowIcon(QtGui.QIcon(loadIconPath('vnpy.ico')))
    
    # 返回创建好的QApp对象
    return qApp