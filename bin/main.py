# -*- coding: utf-8 -*-

import ctypes
import platform
import sys

from vnpy.engine.uiMainWindow import *
from vnpy.engine.vt.vtEngine import MainEngine
from vnpy.utils.vtFunction import findResPath, findConfPath


# ----------------------------------------------------------------------
def main():
    """主程序入口"""

    # 设置Windows底部任务栏图标
    if 'Windows' in platform.uname():
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('vn.trader')

    # 初始化Qt应用对象
    app = QtGui.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon(findResPath('vnpy.ico')))
    app.setFont(BASIC_FONT)

    # 设置Qt的皮肤
    try:
        f = file(findConfPath("VT_setting.json"))
        setting = json.load(f)
        if setting['darkStyle']:
            import qdarkstyle
            app.setStyleSheet(qdarkstyle.load_stylesheet(pyside=False))
    except Exception as e:
        print u"设置皮肤失败：{}".format(e.__class__)
        pass

    # 初始化主引擎和主窗口对象
    main_engine = MainEngine()
    main_window = MainWindow(main_engine, main_engine.eventEngine)
    main_window.showMaximized()

    # 在主线程中启动Qt事件循环
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
