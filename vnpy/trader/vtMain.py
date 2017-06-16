# encoding: UTF-8

import sys

import os
import ctypes
import platform

# 将repostory的目录i，作为根目录，添加到系统环境中。
root_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '..' , '..'))
sys.path.append(root_path)
print sys.path

from vnpy.trader.vtEngine import MainEngine
from vnpy.trader.uiMainWindow import *
# 加载底层接口
from gateway import ctpGateway

# 初始化的接口模块，以及其指定的名称,CTP是模块，value，是该模块下的多个连接配置文件,如 CTP_JR_connect.json
init_gateway_names = {'CTP': ['CTP', 'CTP_Prod', 'CTP_Post', 'CTP_EBF', 'CTP_JR', 'CTP_JR2']}

# 文件路径名
path = os.path.abspath(os.path.dirname(__file__))
ICON_FILENAME = 'vnpy.ico'
ICON_FILENAME = os.path.join(path, ICON_FILENAME)

from setup_logger import setup_logger
setup_logger(filename='logs/vnpy_{0}.log'.format(datetime.now().strftime('%m%d_%H%M')), debug=False)

# ----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 重载sys模块，设置默认字符串编码方式为utf8
    reload(sys)
    sys.setdefaultencoding('utf8')

    # 设置Windows底部任务栏图标
    if 'Windows' in platform.uname():
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('vn.trader')  

    # 初始化Qt应用对象
    app = QtGui.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon(ICON_FILENAME))
    app.setFont(BASIC_FONT)
    
    # 设置Qt的皮肤
    try:
        from vnpy.trader.vtGlobal import globalSetting
        if globalSetting['darkStyle']:
            import qdarkstyle
            app.setStyleSheet(qdarkstyle.load_stylesheet(pyside=False))

    except:
        pass
    
    # 初始化主引擎和主窗口对象
    mainEngine = MainEngine()

    for gw_name in init_gateway_names['CTP']:
        print 'add {0}'.format(gw_name)
        mainEngine.addGateway(ctpGateway, gw_name)

    mainWindow = MainWindow(mainEngine, mainEngine.eventEngine)
    mainWindow.showMaximized()
    
    # 在主线程中启动Qt事件循环
    sys.exit(app.exec_())
    
if __name__ == '__main__':
    main()
