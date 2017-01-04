# encoding: UTF-8

import vtGlobal

import sys
import os
import ctypes
import platform
from argparse import ArgumentParser

import vtPath
from vtEngine import MainEngine

from shutdown import autoShutdown, autoUIShutdown

# 文件路径名
path = os.path.abspath(os.path.dirname(__file__))

ICON_FILENAME = 'vnpy.ico'
ICON_FILENAME = os.path.join(path, ICON_FILENAME)

SETTING_FILENAME = 'VT_setting.json'
SETTING_FILENAME = os.path.join(path, SETTING_FILENAME)

# CTP_CONNECTION = 'CTP_connection.json'
# CTP_CONNECTION = os.path.join(path, CTP_CONNECTION)


# ----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 重载sys模块，设置默认字符串编码方式为utf8
    reload(sys)
    sys.setdefaultencoding('utf8')

    # 初始化主引擎
    mainEngine = MainEngine()
    # 绑定其从参数
    vtGlobal.cmdArgs = cmdArgs

    # 默认启用ui模式
    if cmdArgs.ui:
        # 设置Windows底部任务栏图标
        if 'Windows' in platform.uname():
            ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('vn.trader')

            # 初始化Qt应用对象
        app = QtGui.QApplication(sys.argv)
        app.setWindowIcon(QtGui.QIcon(ICON_FILENAME))
        app.setFont(BASIC_FONT)

        # 设置Qt的皮肤
        try:
            f = file(cmdArgs.vt)
            setting = json.load(f)
            if setting['darkStyle']:
                import qdarkstyle
                app.setStyleSheet(qdarkstyle.load_stylesheet(pyside=False))
        except:
            pass

        # 初始化主窗口对象
        mainWindow = MainWindow(mainEngine, mainEngine.eventEngine)
        mainWindow.showMaximized()
    else:
        app = None

    # 默认自动关闭进程
    if cmdArgs.shutdown:
        if cmdArgs.ui:
            autoUIShutdown(mainEngine)
        else:
            autoShutdown(mainEngine)

    # 直接连接CTP
    if cmdArgs.ctp:
        print("CTP connecting... ")
        mainEngine.connect("CTP")

    # 启动实例，这部分逻辑保持在最后一步
    if cmdArgs.ui:
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
    opt.add_argument("--no-ui", dest="ui", action="store_false", help="无UI模式")
    opt.set_defaults(ui=True)

    # VT_setting.json 文件路径
    opt.add_argument("--vt", default=SETTING_FILENAME, help="重新指定VT_setting.json的绝对路径")

    # CTP_connection.sjon 文件路径
    opt.add_argument("--CTP_connect", help="重新指定CTP_connection.json的绝对路径")

    opt.add_argument("--ctp", dest='ctp', action="store_true", help="是否自动建立CTP链接")
    opt.set_defaults(ctp=False)

    # 不自动关闭
    opt.add_argument("--no-shutdown", dest="shutdown", action="store_false", help="不启用自动关闭进程")
    opt.set_defaults(shutdown=True)

    # 生成参数实例
    cmdArgs = opt.parse_args()

    if cmdArgs.ui:
        from uiMainWindow import *
    # print(cmdArgs)
    main()
