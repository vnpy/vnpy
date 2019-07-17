# -*- coding: utf-8 -*-
"""
基于uiKline扩展得widgets
华富资产/李来佳
"""

import sys
import os
import ctypes
import platform
system = platform.system()
from threading import Thread
# 将repostory的目录，作为根目录，添加到系统环境中。
ROOT_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), '..' , '..'))
sys.path.append(ROOT_PATH)

from vnpy.trader.uiKLine.uiCrosshair import Crosshair
from vnpy.trader.uiKLine.uiKLine import  *
from time import sleep

from pymongo import MongoClient, ASCENDING
from pymongo.errors import ConnectionFailure,AutoReconnect

class RenkoKline(QtWidgets.QWidget):
    """
    砖型图得显示
    1、显示
    2、数据加载：从Mongodb，从本地文件
    3、定时数据更新
    4、加载文件时，选择指标
    """
    def __init__(self, parent=None, setting={}):
        self.parent = parent
        super(RenkoKline, self).__init__(parent)

        self.kline_name = setting.get('kline_name','kline_name')
        self.canvas = None

        self.main_indicators = sorted(setting.get('main_indicators',[]))
        self.sub_indicators = sorted(setting.get('sub_indicators',[]))

        # 数据来自文件
        self.csv_file =  setting.get('csv_file',None)

        # 数据来自mongodb
        self.host = None
        self.port = None
        self.db = None
        self.collection = None
        self.is_live = None
        # MongoDB数据库相关
        self.dbClient = None  # MongoDB客户端对象
        self.db_has_connected = False

        self.last_bar_dt = None

        self.initUI()

        if self.csv_file is not None and os.path.exists(self.csv_file):
            self.datathread = Thread(self.loadData,args={})
            self.datathread.start()

        elif 'mongo' in setting:
            mongo_setting = setting.get('mongo')
            self.host = mongo_setting.get('ip', 'localhost')
            self.port = mongo_setting.get('port', 27017)
            self.db = mongo_setting.get('db', None)
            self.collection = mongo_setting.get('collection',None)
            self.is_live = mongo_setting.get('is_live',False)

            if self.db is not None and self.collection is not None:
                self.dbConnect()
                self.datathread = Thread(target=self.loadDb, args=())
                self.datathread.start()

    def initUI(self):
        """
        初始化界面
        :return:
        """
        vbox = QtWidgets.QVBoxLayout()
        self.canvas = KLineWidget(display_vol=False, display_sub=True)
        self.canvas.show()
        self.canvas.KLtitle.setText('{}'.format(self.kline_name), size='18pt')

        for indicator in self.main_indicators:
            self.canvas.add_indicator(indicator=indicator, is_main=True)

        for indicator in self.sub_indicators:
            self.canvas.add_indicator(indicator=indicator, is_main=False)

        vbox.addWidget(self.canvas)
        self.setLayout(vbox)

    def loadData(self):
        if self.canvas:
            df = pd.read_csv(self.csv_file)
            df = df.set_index(pd.DatetimeIndex(df['datetime']))
            self.canvas.loadData(df, main_indicators=self.main_indicators, sub_indicators=self.sub_indicators)

    def loadDb(self):
        try:
            d = {}
            qryData = self.dbQueryBySort(dbName=self.db,collectionName=self.collection,d=d,sortName='datetime',sortType=1)
            bars = []
            for data in qryData:
                bar = {
                    'datetime':data.get('datetime'),
                    'open':data.get('open'),
                    'close':data.get('close'),
                    'high':data.get('high'),
                    'low':data.get('low'),
                    'openInterest':0,
                    'volume':data.get('volume',0)
                }
                bars.append(bar)
                self.last_bar_dt = data.get('datetime')

            print(u'一共从数据库加载{}根bar'.format(len(bars)))
            df = pd.DataFrame(bars)
            df = df.set_index(pd.DatetimeIndex(df['datetime']))
            self.canvas.loadData(df, main_indicators=self.main_indicators, sub_indicators=self.sub_indicators)
        except Exception as ex:
            print(u'加载bar异常:{}'.format(str(ex)))

    def dbConnect(self):
        try:
            self.dbClient = MongoClient(self.host, self.port, connectTimeoutMS=500)
        except Exception as ex:
            print(u'连接Mongodb:{} {} 异常:{}'.format(self.host, self.port, str(ex)))

    def dbQueryBySort(self, dbName, collectionName, d, sortName, sortType, limitNum=0):
        """从MongoDB中读取数据，d是查询要求，sortName是排序的字段,sortType是排序类型
          返回的是数据库查询的指针"""
        try:
            if self.dbClient:
                db = self.dbClient[dbName]
                collection = db[collectionName]
                if limitNum > 0:
                    cursor = collection.find(d).sort(sortName, sortType).limit(limitNum)
                else:
                    cursor = collection.find(d).sort(sortName, sortType)
                if cursor:
                    return list(cursor)
                else:
                    return []
            else:
                print(u'数据库查询出错')
                if self.db_has_connected:
                    self.writeLog(u'重新尝试连接数据库')
                    self.dbConnect()
        except AutoReconnect as ex:
            print(u'数据库连接断开重连:{}'.format(str(ex)))
            sleep(1)
        except ConnectionFailure:
            self.dbClient = None
            print(u'数据库连接断开')
            if self.db_has_connected:
                print(u'重新尝试连接数据库')
                self.dbConnect()
        except Exception as ex:
            self.writeError(u'dbQueryBySort exception:{}'.format(str(ex)))

        return []


########################################################################
class MultiKlineWindow(QtWidgets.QMainWindow):
    """多窗口显示K线
    包括：

    """

    # ----------------------------------------------------------------------
    def __init__(self, parent=None,settings = []):
        """Constructor"""
        super(MultiKlineWindow, self).__init__(parent)

        self.settings = settings
        self.kline_dict = {}
        self.initUi()

        self.load_multi_kline()
    # ----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'多K线')
        self.maximumSize()
        self.mdi = QtWidgets.QMdiArea()
        self.setCentralWidget(self.mdi)

        # 创建菜单
        menubar = self.menuBar()
        file_menu = menubar.addMenu("File")
        file_menu.addAction("Cascade")
        file_menu.addAction("Tiled")
        file_menu.triggered[QtWidgets.QAction].connect(self.windowaction)

    def windowaction(self,q):
        if q.text() == "cascade":
            self.mdi.cascadeSubWindows()

        if q.text() == "Cascade":
            self.mdi.tileSubWindows()
    # ----------------------------------------------------------------------
    def load_multi_kline(self):
        """加载多周期窗口"""

        try:
           for setting in self.settings:

                sub_window = QtWidgets.QMdiSubWindow()
                sub_window.setWindowTitle(setting.get('kline_name'))
                renko_kline = RenkoKline(parent=self, setting=setting)
                sub_window.setWidget(renko_kline)
                self.mdi.addSubWindow(renko_kline)
                #renko_kline.loadData()
                renko_kline.show()

           self.mdi.tileSubWindows()

        except Exception as ex:
            traceback.print_exc()
            QtWidgets.QMessageBox.warning(self, 'Exception', u' Exception', QtWidgets.QMessageBox.Cancel,
                                          QtWidgets.QMessageBox.NoButton)

            return

    def closeEvent(self, event):
        """关闭窗口时的事件"""
        sys.exit(0)

# 功能测试
########################################################################

from vnpy.trader.uiQt import createQApp
from vnpy.trader.vtFunction import loadIconPath

def display_multi_window():
    qApp = createQApp()

    qApp.setWindowIcon(QtGui.QIcon(loadIconPath('dashboard.ico')))
    settings = []
    collections = ['RB99_5','RB99_10']
    for collection in collections:
        s = {
            'kline_name':collection,
            'mongo':
                {
                    'host':'localhost',
                    'port':27017,
                    'db':'Renko_Db',
                    'collection':collection,
                    'is_live':True
                }
        }
        settings.append(s)

    w = MultiKlineWindow(parent=None,settings=settings)
    w.showMaximized()
    sys.exit(qApp.exec_())

if __name__ == '__main__':
    try:
        display_multi_window()

    except Exception as ex:
        print(u'exception:{},trace:{}'.format(str(ex), traceback.format_exc()))
