# encoding: UTF-8

from __future__ import division

import json
import csv
import datetime
import sys
import os
from collections import OrderedDict

from PyQt4 import QtCore, QtGui

path = os.path.abspath(os.path.dirname(__file__))

#----------------------------------------------------------------------
def outputSettingJson(setting, name):
    """输出配置文件"""
    content = json.dumps(setting, indent=4)
    with open(name, 'w') as f:
        f.write(content)

#----------------------------------------------------------------------
def generatePortfolioSetting():
    """生成配置文件"""
    setting = {
        'name': 'm_portfolio',
        
        'equity': [],
        
        'futures': ['m1709', 'm1801'],
        
        'chain':[            
            {
                'chainSymbol': 'm1709',
                'underlyingSymbol': 'm1709',
                'underlyingType': 'futures',
                'interestRate': 0.03
            },
            
            {
                'chainSymbol': 'm1801',
                'underlyingSymbol': 'm1801',
                'underlyingType': 'futures',
                'interestRate': 0.03
            }            
        ]
    }
    
    fileName = setting['name'] + '.json'
    outputSettingJson(setting, fileName)    
    



"""用于处理周末和节假日，以计算交易日的组件"""


#path = "dateData.dm"

CALENDAR_FILENAME = 'TradingCalendar.csv'
ANNUAL_TRADINGDAYS = 240


#----------------------------------------------------------------------
def initCalendarCsv():
    """初始化日期文件"""
    # 读取csv中的数据并生成列表和字典
    fileName = os.path.join(path, CALENDAR_FILENAME)
    calendarDict = OrderedDict()
    
    try:
        with open(fileName, 'r') as f:
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
        tstr = t.strfime('%Y-%m-%d')
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
    with open(fileName, 'w') as f:
        writer = csv.DictWriter(f, lineterminator='\n', fieldnames=d.keys())
        writer.writeheader()
        for d in calendarDict.values():
            writer.writerow(d)


########################################################################
class CalendarEditor(QtGui.QTableWidget):
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
        fileName = os.path.join(path, CALENDAR_FILENAME)
        
        # 如果有则打开
        try:
            with open(fileName, 'r') as f:
                reader = csv.DictReader(f)
                for d in reader:
                    cellDate = QtGui.QTableWidgetItem(d['date'])
                    cellDescription = QtGui.QTableWidgetItem(d['description'])
                    
                    if row >= totalRow:
                        self.insertRow(row)
        
                    self.setItem(row, 0, cellDate)
                    self.setItem(row, 1, cellDescription)
                    
                    row = row + 1                    
                    
        # 如果没有该文件则创建
        except IOError:
            f = open(fileName, 'w')
            f.close()
        
    #----------------------------------------------------------------------
    def saveCalendar(self):
        """保存日历"""
        totalRow = self.rowCount()
        fileName = os.path.join(path, CALENDAR_FILENAME)
        
        with open(fileName, 'w') as f:
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
class CalendarManager(QtGui.QWidget):
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
        
        buttonLoad = QtGui.QPushButton(u'读取日历')
        buttonSave = QtGui.QPushButton(u'保存日历')
        buttonInit = QtGui.QPushButton(u'初始化日历')
        buttonClear = QtGui.QPushButton(u'清空')
        
        buttonLoad.clicked.connect(self.editor.loadCalendar)
        buttonSave.clicked.connect(self.editor.saveCalendar)
        buttonInit.clicked.connect(self.editor.initCalendar)
        buttonClear.clicked.connect(self.editor.clearTable)
        
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(buttonLoad)
        hbox.addWidget(buttonSave)
        hbox.addWidget(buttonInit)
        hbox.addWidget(buttonClear)
        hbox.addStretch()
        
        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.editor)
        
        self.setLayout(vbox)


#----------------------------------------------------------------------
def runCalendarEditor():
    """运行日历编辑器"""
    reload(sys)
    sys.setdefaultencoding('utf8')
    
    app = QtGui.QApplication(sys.argv)
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
def calculateExpiryTime(expiryDate):
    """计算剩余的年化到期时间（交易日）"""
    expiryDt = datetime.datetime.strptime(expiryDate, '%Y%m%d').date()
    todayDt = datetime.date.today()
    
    fileName = os.path.join(path, CALENDAR_FILENAME)
    calendarDict = OrderedDict()
    with open(fileName, 'r') as f:
        reader = csv.DictReader(f)        
        l = [d for d in reader]   
    
    tradingDays = 0
    for d in l:
        dt = datetime.datetime.strptime(d['date'], '%Y/%m/%d').date()
        # 判断是否为交易日的条件：
        # 1. 日期大于等于今日
        # 2. 日期小于等于到期日
        # 3. 日期没有描述（假期）        
        if dt>=todayDt and dt<=expiryDt and not d['description']:
            tradingDays += 1
    
    # 返回年化剩余时间
    return tradingDays/ANNUAL_TRADINGDAYS


if __name__ == "__main__":
    
    generatePortfolioSetting()
    
    #runCalendarEditor()