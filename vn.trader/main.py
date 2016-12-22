# encoding: UTF-8

import sys
import os
import ctypes
import platform
from argparse import ArgumentParser

import vtPath
from vtEngine import MainEngine

from shutdown import autoShutdown

# 文件路径名
path = os.path.abspath(os.path.dirname(__file__))
ICON_FILENAME = 'vnpy.ico'
ICON_FILENAME = os.path.join(path, ICON_FILENAME)

SETTING_FILENAME = 'VT_setting.json'
SETTING_FILENAME = os.path.join(path, SETTING_FILENAME)


# ----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 重载sys模块，设置默认字符串编码方式为utf8
    reload(sys)
    sys.setdefaultencoding('utf8')

    # 初始化主引擎和主窗口对象
    mainEngine = MainEngine()
    # 绑定其从参数
    mainEngine.args = args

    # 启用ui模式
    if args.ui:
        # 设置Windows底部任务栏图标
        if 'Windows' in platform.uname():
            ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('vn.trader')

            # 初始化Qt应用对象
        app = QtGui.QApplication(sys.argv)
        app.setWindowIcon(QtGui.QIcon(ICON_FILENAME))
        app.setFont(BASIC_FONT)

        # 设置Qt的皮肤
        try:
            f = file(args.vt)
            setting = json.load(f)
            if setting['darkStyle']:
                import qdarkstyle
                app.setStyleSheet(qdarkstyle.load_stylesheet(pyside=False))
        except:
            pass

        mainWindow = MainWindow(mainEngine, mainEngine.eventEngine)
        mainWindow.showMaximized()
    else:
        app = None

    # 自动关闭进程
    if args.shutdown:
        autoShutdown(mainEngine)

    # 启动实例
    if args.ui:
        # 在主线程中启动Qt事件循环
        sys.exit(app.exec_())
    else:
        # 不启用UI模式
        mainEngine.exit()


if __name__ == '__main__':
    # 载入命令行启动参数
    opt = ArgumentParser(
        prog="vnpy",
        description="Args of vnpy.",
    )
    opt = ArgumentParser()

    # UI开关
    opt.add_argument("--no-ui", dest="ui", action="store_false", help="NOT use UI.")
    opt.set_defaults(ui=True)

    # VT_setting.json 文件路径
    opt.add_argument("--vt", default=SETTING_FILENAME, help="VT_setting.json file.")

    # 不自动关闭
    opt.add_argument("--no-shutdown", dest="shutdown", action="store_false", help="NOT auto to close.")
    opt.set_defaults(shutdown=True)

    # 生成参数实例
    args = opt.parse_args()

    if args.ui:
        from uiMainWindow import *

    print(args)
    # main()