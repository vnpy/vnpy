# encoding: UTF-8
import ctypes
from uiDataRecorderMainWindow import *
from vtEngine import MainEngine

#----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 设置底部任务栏图标，win7以下请注释掉
    try:
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('vnpy')
    except:
        pass
    app = QtGui.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon('vnpy.ico'))
    app.setFont(BASIC_FONT)

    mainEngine = MainEngine()

    mainWindow = MainWindow(mainEngine, mainEngine.eventEngine)
    mainWindow.show()

    sys.exit(app.exec_())
if __name__ == '__main__':
    main()

