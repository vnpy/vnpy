# encoding: UTF-8

"""用于处理周末和节假日，以计算交易日的组件"""

from __future__ import division

import csv
import datetime
import sys
import os
from collections import OrderedDict

from vnpy.trader.uiQt import QtCore, QtWidgets, QtGui


# 常量定义
ANNUAL_TRADINGDAYS = 240

CALENDAR_FILENAME = 'TradingCalendar.csv'
PATH = os.path.abspath(os.path.dirname(__file__))
CALENDAR_FILEPATH = os.path.join(PATH, CALENDAR_FILENAME)

# 加载日历数据
try:
    with open(CALENDAR_FILEPATH, 'r') as f:
        reader = csv.DictReader(f)        
        CALENDAR = [d for d in reader]   
except IOError:
    CALENDAR = []

# TimeToMaturity缓存字典
TTM_DICT = {}      # key:date, value:float time(year)


########################################################################
class CalendarEditor(QtWidgets.QTableWidget):
    """日历编辑器"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(CalendarEditor, self).__init__()
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setColumnCount(2)
        self.horizontalHeader().setVisible(True)                # 关闭左边的垂直表头
        self.verticalHeader().setVisible(False)                 # 关闭左边的垂直表头
        self.setHorizontalHeaderLabels([u'日期', u'描述'])
        
    #----------------------------------------------------------------------
    def clearTable(self):
        """清空表格"""
        self.clear()
        self.initUi()
    
    #----------------------------------------------------------------------
    def loadCalendar(self):
        """读取日历"""
        self.clearContents()
        
        row = 0
        totalRow = self.rowCount()
        
        # 如果有则打开
        try:
            with open(CALENDAR_FILEPATH, 'r') as f:
                reader = csv.DictReader(f)
                for d in reader:
                    cellDate = QtWidgets.QTableWidgetItem(d['date'])
                    cellDescription = QtWidgets.QTableWidgetItem(d['description'])
                    
                    if row >= totalRow:
                        self.insertRow(row)
        
                    self.setItem(row, 0, cellDate)
                    self.setItem(row, 1, cellDescription)
                    
                    row = row + 1                    
                    
        # 如果没有该文件则创建
        except IOError:
            f = open(CALENDAR_FILEPATH, 'w')
            f.close()
        
    #----------------------------------------------------------------------
    def saveCalendar(self):
        """保存日历"""
        totalRow = self.rowCount()
        
        with open(CALENDAR_FILEPATH, 'w') as f:
            writer = csv.DictWriter(f, lineterminator='\n', fieldnames=['date', 'description'])
            writer.writeheader()
            
            for row in range(totalRow):
                cellDate = self.item(row, 0)
                cellDescription = self.item(row, 1)
                
                if cellDescription:
                    description = cellDescription.text()
                else:
                    description = ''

                d = {
                    'date': cellDate.text(),
                    'description': description
                }
                writer.writerow(d)
    
    #----------------------------------------------------------------------
    def initCalendar(self):
        """初始化日历"""
        initCalendarCsv()


########################################################################
class CalendarManager(QtWidgets.QWidget):
    """日历管理组件"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(CalendarManager, self).__init__()
        self.initUI()
        
    #----------------------------------------------------------------------
    def initUI(self):
        """"""
        self.setWindowTitle(u'日历管理')
        
        self.editor = CalendarEditor()
        
        buttonLoad = QtWidgets.QPushButton(u'读取日历')
        buttonSave = QtWidgets.QPushButton(u'保存日历')
        buttonInit = QtWidgets.QPushButton(u'初始化日历')
        buttonClear = QtWidgets.QPushButton(u'清空')
        
        buttonLoad.clicked.connect(self.editor.loadCalendar)
        buttonSave.clicked.connect(self.editor.saveCalendar)
        buttonInit.clicked.connect(self.editor.initCalendar)
        buttonClear.clicked.connect(self.editor.clearTable)
        
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(buttonLoad)
        hbox.addWidget(buttonSave)
        hbox.addWidget(buttonInit)
        hbox.addWidget(buttonClear)
        hbox.addStretch()
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.editor)
        
        self.setLayout(vbox)


#----------------------------------------------------------------------
def runCalendarEditor():
    """运行日历编辑器"""
    reload(sys)
    sys.setdefaultencoding('utf8')
    
    app = QtWidgets.QApplication(sys.argv)
    app.setFont(QtGui.QFont(u'微软雅黑', 12))
    
    try:
        import qdarkstyle
        app.setStyleSheet(qdarkstyle.load_stylesheet(pyside=False))
    except:
        pass        
    
    manager = CalendarManager()
    manager.showMaximized()
    
    sys.exit(app.exec_())    


#----------------------------------------------------------------------
def initCalendarCsv():
    """初始化日期文件"""
    # 读取csv中的数据并生成列表和字典
    calendarDict = OrderedDict()
    
    try:
        with open(CALENDAR_FILEPATH, 'r') as f:
            reader = csv.DictReader(f)        
            for d in reader:
                calendarDict[d['date']] = d
    except IOError:
        pass
    
    # 生成未来的数据
    today = datetime.date.today()
    oneday = datetime.timedelta(days=1)
    
    t = today
    for i in range(365*2):
        # 如果日历里没有该日期的状态，则初始化（仅判断是否周末）
        tstr = t.strftime('%Y-%m-%d')
        if tstr not in calendarDict:
            if t.weekday() == 5 or t.weekday() == 6:
                description = 'weekend'
            else:
                description = ''
            d = {
                'date': tstr,
                'description': description
            }
            calendarDict[d['date']] = d
            
        # 往下一天
        t = t + oneday
        
    # 保存到csv中
    with open(CALENDAR_FILEPATH, 'w') as f:
        writer = csv.DictWriter(f, lineterminator='\n', fieldnames=d.keys())
        writer.writeheader()
        for d in calendarDict.values():
            writer.writerow(d)


#----------------------------------------------------------------------
def getTimeToMaturity(expiryDate):
    """计算剩余的年化到期时间（交易日）"""
    # 如果有缓存则直接返回
    if expiryDate in TTM_DICT:
        return TTM_DICT[expiryDate]
    
    # 获取日期对象
    expiryDt = datetime.datetime.strptime(expiryDate, '%Y%m%d').date()
    todayDt = datetime.date.today()
    
    tradingDays = 0
    for d in CALENDAR:
        dt = datetime.datetime.strptime(d['date'], '%Y-%m-%d').date()
        # 判断是否为交易日的条件：
        # 1. 日期大于等于今日
        # 2. 日期小于等于到期日
        # 3. 日期没有描述（假期）        
        if dt>=todayDt and dt<=expiryDt and not d['description']:
            tradingDays += 1
    
    # 缓存并返回年化剩余时间
    ttm = tradingDays/ANNUAL_TRADINGDAYS
    TTM_DICT[expiryDate] = ttm
    return ttm
    
    
if __name__ == '__main__':
    runCalendarEditor()