# encoding: UTF-8

"""用于处理周末和节假日，以计算交易日的组件"""

import shelve
from collections import OrderedDict
from datetime import date, datetime, timedelta
import datetime as DT
import sys
import os

from dmWidget import *

path = os.getcwd() + "\\database\\dateData.dm"
#path = "dateData.dm"

#----------------------------------------------------------------------
def initCalendar():
    """初始化日期文件"""
    fDate = shelve.open(path) 
    try:
        calendar = fDate['calendar']
    except KeyError:
        calendar = OrderedDict()
    
    today = date.today()
    oneday = timedelta(days=1)
    
    # 遍历未来一年
    t = today
    for i in range(365):
        # 如果日历里没有该日期的状态，则初始化（仅判断是否周末）
        if str(t) not in calendar:
            if t.weekday() == 5 or t.weekday() == 6:
                description = 'weekend'
            else:
                description = ''
            calendar[str(t)] = description
        # 往下一天
        t = t + oneday
        
    # 打开日期管理文件   
    fDate['calendar'] = calendar
    fDate.close()


#----------------------------------------------------------------------
def getTradingDays(expire):
    """计算剩余的交易日"""
    expireDt = datetime.strptime(expire, '%Y%m%d')
    expireD = expireDt.date()
    today = DT.date.today()
    
    f = shelve.open(path)
    calendar = f['calendar']
    f.close()
    
    tradingDays = 0
    
    for date, description in calendar.items():
        d = datetime.strptime(date, '%Y-%m-%d').date()
        # 判断是否为交易日的条件：
        # 1. 日期大于等于今日
        # 2. 日期小于等于到期日
        # 3. 日期没有描述（假期）
        if d>= today and d<=expireD and not description:
            tradingDays = tradingDays + 1
    
    return tradingDays
        

########################################################################
class CalendarEditor(dmTableWidget):
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
        
        fDate = shelve.open(path) 
        
        try:
            calendar = fDate['calendar']
            for key, value in calendar.items():
                cellDate = dmTableCell(key)
                cellDescription = dmTableCell(value)
                
                if row >= totalRow:
                    self.insertRow(row)
    
                self.setItem(row, 0, cellDate)
                self.setItem(row, 1, cellDescription)
                row = row + 1
        except KeyError:
            calendar = OrderedDict()
        
        fDate['calendar'] = calendar
        fDate.close()
        
    #----------------------------------------------------------------------
    def saveCalendar(self):
        """保存日历"""
        fDate = shelve.open(path) 
        calendar = fDate['calendar']
        
        totalRow = self.rowCount()
        
        for row in range(totalRow):
            cellDate = self.item(row, 0)
            cellDescription = self.item(row, 1)
            
            if cellDescription:
                description = unicode(cellDescription.text())
            else:
                description = ''
                
            if cellDate:
                date = unicode(cellDate.text())            
                calendar[date] = description
            
        fDate['calendar'] = calendar
        fDate.close()
    
    #----------------------------------------------------------------------
    def initCalendar(self):
        """初始化日历"""
        initCalendar()


########################################################################
class CalendarManager(dmWidget):
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
def main():
    """"""
    app = QtGui.QApplication(sys.argv)
  
    manager = CalendarManager()
    manager.showMaximized()
    
    sys.exit(app.exec_())    
    
    
if __name__ == '__main__':
    main()
    
