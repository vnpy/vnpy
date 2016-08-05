# encoding: UTF-8
import ctypes
from dataRecorderAlone.uiDataRecorderMainWindow import *
from vtEngine import MainEngine
import sys

#----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 设置底部任务栏图标，win7以下请注释掉
    try:
        ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('RT. Data Recorder')
    except:
        pass
    app = QtGui.QApplication(sys.argv)
    app.setWindowIcon(QtGui.QIcon('RT.ico'))
    app.setFont(BASIC_FONT)

    mainEngine = MainEngine()
    # mainEngine.drEngine = None      # 默认是dataRecorder中的drEngine，此模块中应使用dataRecorderAlone中的drEngine
    mainWindow = MainWindow(mainEngine, mainEngine.eventEngine)
    mainWindow.show()

    sys.exit(app.exec_())
if __name__ == '__main__':
    main()
