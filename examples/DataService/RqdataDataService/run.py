# encoding: UTF-8

from __future__ import print_function

import json
import ctypes
from datetime import datetime, timedelta, time
from time import sleep
from threading import Thread
from collections import OrderedDict

import qdarkstyle
from pymongo import MongoClient, ASCENDING, DESCENDING
from pymongo.errors import ConnectionFailure

from vnpy.trader.uiQt import QtCore, QtWidgets, QtGui
from vnpy.trader.vtObject import VtBarData
from vnpy.trader.app.ctaStrategy.ctaBase import MINUTE_DB_NAME, DAILY_DB_NAME


DAY_START = time(9, 0)         # 日盘启动和停止时间
DAY_END = time(17, 15)
NIGHT_START = time(21, 0)      # 夜盘启动和停止时间
NIGHT_END = time(2, 30)


########################################################################
class RqDataManager(QtWidgets.QWidget):
    """"""
    signal = QtCore.Signal(str)

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(RqDataManager, self).__init__()
        
        self.client = None
        self.rq = None
        self.thread = Thread(target=self.run)
        
        self.productList = []
        self.symbolExchangeDict = OrderedDict()
        
        self.initUi()
        
        n1 = self.connectMongo()
        if not n1:
            return
        
        n2 = self.initRqData()
        if not n2:
            return
        
        self.count = 0
        self.active = True
        self.thread.start()
    
    #----------------------------------------------------------------------
    def connectMongo(self):
        """连接数据库"""
        try:
            self.client = MongoClient(serverSelectionTimeoutMS=10)
            self.client.server_info()
            self.writeLog(u'MongoDB连接成功')
            return True
        except ConnectionFailure:
            self.client = None
            self.writeLog(u'MongoDB连接失败')
            return False
    
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'RQData数据服务')
        self.setWindowIcon(QtGui.QIcon('vnpy.ico'))
        
        self.setFixedHeight(500)
        self.setFixedWidth(900)
        
        self.logMonitor = QtWidgets.QTextEdit()
        self.logMonitor.setReadOnly(True)
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.logMonitor)
        self.setLayout(vbox)
        
        self.signal.connect(self.updateLog)
        
        # 托盘配置
        self.tray = QtWidgets.QSystemTrayIcon()
        self.tray.setIcon(QtGui.QIcon('vnpy.ico'))
        self.tray.activated.connect(self.showManager)
        
        restoreAction = QtWidgets.QAction(u'还原', self, triggered=self.show)
        quitAction = QtWidgets.QAction(u'退出', self, triggered=self.exit)
        
        menu = QtWidgets.QMenu(QtWidgets.QApplication.desktop())
        menu.addAction(restoreAction)
        menu.addAction(quitAction)
        self.tray.setContextMenu(menu)
        
        self.tray.show()

    #----------------------------------------------------------------------
    def initRqData(self):
        """"""
        with open('config.json') as config:
            setting = json.load(config)
            
            for product in setting['product']:
                self.productList.append(product.upper())
        
        # 检查是否填写了RQData配置
        username = setting.get('rqUsername', None)
        password = setting.get('rqPassword', None)
        if not username or not password:
            self.writeLog(u'RQData的用户名和密码配置错误，请在config.json中修改')
            return False
        
        # 加载RQData
        try:
            import rqdatac as rq
        except ImportError:
            self.writeLog(u'没有安装RQData客户端，请先安装rqdatac')
            return False
        
        # 登录RQData
        self.rq = rq
        self.rq.init(username, password)
        
        # 获取本日可交易合约代码
        try:
            df = self.rq.all_instruments(type='Future', date=datetime.now())
            for ix, row in df.iterrows():
                self.symbolExchangeDict[row['order_book_id']] = row['exchange']
        except RuntimeError:
            self.writeLog(u'RQData的用户名和密码无效，请联系米筐申请试用或者购买')
            return False
    
        self.writeLog(u'RQData客户端登录成功')
        return True
    
    #----------------------------------------------------------------------
    def downloadBar(self, symbol, frequency):
        """下载合约数据"""
        if 'frequency' == '1m':
            db = self.client[MINUTE_DB_NAME]
        else:
            db = self.client[DAILY_DB_NAME]
        
        # 上期所和大商所代码改为小写
        exchange = self.symbolExchangeDict[symbol]
        if exchange in ['SHFE', 'DCE']:
            localSymbol = symbol.lower()
        else:
            localSymbol = symbol
        collection = db[localSymbol]
        
        # 获取本地数据库中最后一条记录的时间，并下载新数据
        result = collection.find_one(sort=[("datetime", DESCENDING)])
        if result:
            startDate = result['datetime']
        else:
            startDate = '20180101'
        
        if startDate:
            self.writeLog(u'%s下载更新数据，开始时间：%s' %(localSymbol, startDate))
        else:
            self.writeLog(u'%s初次下载数据，耗时可能较长，请耐心等待' %(localSymbol))
            
        df = self.rq.get_price(symbol, 
                               frequency=frequency, 
                               fields=['open', 'high', 'low', 'close', 'volume'], 
                               start_date=startDate,
                               end_date=datetime.now())
        
        # 插入到数据库
        for ix, row in df.iterrows():
            bar = self.generateBar(row, localSymbol)
            d = bar.__dict__
            flt = {'datetime': bar.datetime}
            collection.replace_one(flt, d, True)            
    
        self.writeLog(u'%s数据更新完成：%s - %s' %(localSymbol, df.index[0], df.index[-1]))
    
    #----------------------------------------------------------------------
    def generateBar(self, row, symbol):
        """生成K线对象"""
        bar = VtBarData()
        
        bar.symbol = symbol
        bar.vtSymbol = symbol
        bar.open = row['open']
        bar.high = row['high']
        bar.low = row['low']
        bar.close = row['close']
        bar.volume = row['volume']
        bar.datetime = row.name
        bar.date = bar.datetime.strftime("%Y%m%d")
        bar.time = bar.datetime.strftime("%H:%M:%S")
        
        return bar        
    
    #----------------------------------------------------------------------
    def writeLog(self, msg):
        """记录日志"""
        self.signal.emit(msg)
    
    #----------------------------------------------------------------------
    def updateLog(self, msg):
        """更新日志"""
        dt = datetime.now()
        msg = '%s:    %s' %(dt, msg)
        self.logMonitor.append(msg)
    
    #----------------------------------------------------------------------
    def run(self):
        """运行"""
        while self.active:
            sleep(1)
            
            self.count += 1
            if self.count < 10:
                continue
            self.count = 0
            
            now = datetime.now().time()
            if ((DAY_START <= now <= DAY_END) or 
                (now >= NIGHT_START) or 
                (now <= NIGHT_END)):                
                for symbol in self.symbolExchangeDict.keys():
                    download = False
                    for product in self.productList:
                        if product in symbol:
                            download = True
        
                    if download:
                        self.downloadBar(symbol, '1m')
            else:
                self.writeLog(u'非交易时间段，不执行更新')
    
    #----------------------------------------------------------------------
    def showManager(self, reason):
        """"""
        self.show()
    
    #----------------------------------------------------------------------
    def closeEvent(self, event):
        """"""
        self.hide()
        event.ignore()
    
    #----------------------------------------------------------------------
    def exit(self):
        """"""
        self.active = False
        self.thread.join()
        
        QtWidgets.qApp.quit()
        

if __name__ == '__main__':
    font = QtGui.QFont(u'微软雅黑', 12)
    
    app = QtWidgets.QApplication([])
    app.setFont(font)
    app.setStyleSheet(qdarkstyle.load_stylesheet_from_environment())
    
    ctypes.windll.shell32.SetCurrentProcessExplicitAppUserModelID('RQDataService')  
    
    manager = RqDataManager()
    manager.show()
    
    app.exec_()