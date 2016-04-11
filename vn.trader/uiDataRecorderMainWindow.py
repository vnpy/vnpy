# encoding: UTF-8
import psutil
import sys
reload(sys)
sys.setdefaultencoding('utf-8')
from uiDataRecorder import *
BASIC_FONT = QtGui.QFont(u'微软雅黑', 10)


########################################################################
class MainWindow(QtGui.QMainWindow):
    """
    类名称：MainWindow
    类描述：客户端主界面窗口
    创建人：freeitaly
    """
    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        super(MainWindow, self).__init__()

        self.mainEngine = mainEngine
        self.eventEngine = eventEngine

        self.initUi()
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'期货Tick存储@订阅')
        self.initCentral()
        self.initMenu()
        self.initStatusBar()

    #----------------------------------------------------------------------
    def initCentral(self):
        """初始化中心区域"""

        dr_W = DataRecorder(self.mainEngine, self.eventEngine)

        vBox = QtGui.QVBoxLayout()
        vBox.addWidget(dr_W)

        central = QtGui.QWidget()
        central.setLayout(vBox)
        self.setCentralWidget(central)
    #----------------------------------------------------------------------
    def initMenu(self):
        """初始化菜单"""
        # 创建操作
        exitAction = QtGui.QAction(u'退出', self)
        exitAction.triggered.connect(self.close)

        # aboutAction = QtGui.QAction(u'关于', self)
        # aboutAction.triggered.connect(self.openAbout)


        # 创建菜单
        menubar = self.menuBar()

        sysMenu = menubar.addMenu(u'系统')

        sysMenu.addAction(exitAction)

        # helpMenu = menubar.addMenu(u'帮助')
        # helpMenu.addAction(aboutAction)

    #----------------------------------------------------------------------
    def initStatusBar(self):
        """初始化状态栏"""
        self.statusLabel = QtGui.QLabel()
        self.statusLabel.setAlignment(QtCore.Qt.AlignLeft)

        self.statusBar().addPermanentWidget(self.statusLabel)
        self.statusLabel.setText(self.getCpuMemory())

        self.sbCount = 0
        self.sbTrigger = 10     # 10秒刷新一次
    #----------------------------------------------------------------------
    def updateStatusBar(self, event):
        """在状态栏更新CPU和内存信息"""
        self.sbCount += 1

        if self.sbCount == self.sbTrigger:
            self.sbCount = 0
            self.statusLabel.setText(self.getCpuMemory())

    #----------------------------------------------------------------------
    def getCpuMemory(self):
        """获取CPU和内存状态信息"""
        cpuPercent = psutil.cpu_percent()
        memoryPercent = psutil.virtual_memory().percent
        return u'CPU使用率：%d%%    内存使用率：%d%%    ' % (cpuPercent, memoryPercent)

    #----------------------------------------------------------------------

    #----------------------------------------------------------------------
    def closeEvent(self, event):
        """关闭事件"""
        reply = QtGui.QMessageBox.question(self, u'退出',
                                           u'确认退出?', QtGui.QMessageBox.Yes |
                                           QtGui.QMessageBox.No, QtGui.QMessageBox.No)

        if reply == QtGui.QMessageBox.Yes:
            event.accept()
            self.mainEngine.exit()
        else:
            event.ignore()

