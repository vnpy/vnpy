# encoding: UTF-8

from collections import OrderedDict

from PyQt4 import QtGui, QtCore

from eventEngine import *
  

########################################################################
class BasicMonitor(QtGui.QTableWidget):
    """基础监控"""
    signal = QtCore.pyqtSignal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(BasicMonitor, self).__init__(parent)
        
        self.eventEngine = eventEngine
        
        # 保存表头标签用
        self.headerDict = OrderedDict()  # 有序字典，key是英文名，value是对应的中文名
        self.headerList = []             # 对应self.headerDict.keys()
        
        # 保存相关数据用
        self.dataDict = {}  # 字典，key是字段对应的数据，value是保存相关单元格的字典
        self.dataKey = ''   # 字典键对应的数据字段
        
        # 监控的事件类型
        self.eventType = ''
        
        # 字体
        self.font = None
        
    #----------------------------------------------------------------------
    def setHeaderDict(self, headerDict):
        """设置表头有序字典"""
        self.headerDict = headerDict
        self.headerList = headerDict.keys()
        
    #----------------------------------------------------------------------
    def setDataKey(self, dataKey):
        """设置数据字典的键"""
        self.dataKey = dataKey
        
    #----------------------------------------------------------------------
    def setEventType(self, eventType):
        """设置监控的事件类型"""
        self.eventType = eventType
        
    #----------------------------------------------------------------------
    def setFont(self, font):
        """设置字体"""
        self.font = font
        
    #----------------------------------------------------------------------
    def initTable(self):
        """初始化表格"""
        # 设置表格的列数
        col = len(self.labelDict)
        self.setColumnCount(col)
        
        # 设置列表头
        self.setHorizontalHeaderLabels(self.labelDict.values())
        
        # 关闭左边的垂直表头
        self.verticalHeader().setVisible(False)
        
        # 设为不可编辑
        self.setEditTriggers(self.NoEditTriggers)

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册GUI更新相关的事件监听"""
        self.signal.connect(self.updateData)
        self.eventEngine.register(self.eventType, self.signal.emit)
    
    #----------------------------------------------------------------------
    def updateData(self, event):
        """更新数据"""
        data = event.dict_['data']
        key = data.__getattribute__(self.dataKey)
        
        # 如果设置了dataKey，则采用存量更新模式
        if self.dataKey:
            # 如果键在数据字典中不存在，则先插入新的一行，并创建对应单元格
            if key not in self.dataDict:
                self.insertRow(0)     
                d = {}
                for n, header in enumerate(self.headerList):
                    content = unicode(data.__getattribute__(header))
                    cell = QtGui.QTableWidgetItem(content)
                    if self.font:
                        cell.setFont(font)  # 如果设置了特殊字体，则进行单元格设置
                    self.setItem(0, n, cell)
                    d[header] = cell
                self.dataDict[key] = d
            # 否则如果已经存在，则直接更新相关单元格
            else:
                d = self.dataDict[key]
                for header in self.headerList:
                    content = unicode(data.__getattribute__(header))
                    cell = d[header]
                    cell.setText(content)
        # 否则采用增量更新模式
        else:
            self.insertRow(0)  
            for n, header in enumerate(self.headerList):
                content = unicode(data.__getattribute__(header))
                cell = QtGui.QTableWidgetItem(content)
                if self.font:
                    cell.setFont(font)
                self.setItem(0, n, cell)            
                
        # 调整列宽
        self.resizeColumns()
    
    #----------------------------------------------------------------------
    def resizeColumns(self):
        """调整各列的大小"""
        self.horizontalHeader().resizeSections(QtGui.QHeaderView.ResizeToContents)    
    

########################################################################
class MarketMonitor(BasicMonitor):
    """市场监控组件"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(MarketMonitor, self).__init__(eventEngine, parent)
        
        # 设置表头有序字典
        d = OrderedDict()
        d['symbol'] = u'合约代码'
        d['vtSymbol'] = u'系统代码'
        d['lastPrice'] = u'最新价'
        d['volume'] = u'成交量'
        d['openInterest'] = u'持仓量'
        d['openPrice'] = u'开盘价'
        d['highPrice'] = u'最高价'
        d['lowPrice'] = u'最低价'
        d['bidPrice1'] = u'买一价'
        d['bidVolume1'] = u'买一量'
        d['askPrice1'] = u'卖一价'
        d['askVolume1'] = u'卖一量'
        d['tickTime'] = u'时间'
        self.setHeaderDict(d)
        
        # 设置数据键
        self.setDataKey('vtSymbol')
        
        # 设置监控事件类型
        self.setEventType(EVENT_TICK)
        
        # 初始化表格
        self.initTable()
        
        # 注册事件监听
        self.registerEvent()


########################################################################
class LogMonitor(BasicMonitor):
    """日志监控"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(LogMonitor, self).__init__(eventEngine, parent)
        
        d = OrderedDict()
        d['gatewayName'] = u'接口'
        d['logTime'] = u'时间'
        d['logContent'] = u'内容'
        self.setHeaderDict(d)
        
        self.setEventType(EVENT_LOG)
        self.initTable()
        self.registerEvent()


########################################################################
class ErrorMonitor(BasicMonitor):
    """错误监控"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(ErrorMonitor, self).__init__(eventEngine, parent)
        
        d = OrderedDict()
        d['gatewayName'] = u'接口'
        d['errorID'] = u'错误代码'
        d['errorMsg'] = u'错误信息'
        self.setHeaderDict(d)
        
        self.setEventType(EVENT_ERROR)
        self.initTable()
        self.registerEvent()


########################################################################
class TradeMonitor(BasicMonitor):
    """成交监控"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(TradeMonitor, self).__init__(eventEngine, parent)
        
        d = OrderedDict()
        d['gatewayName'] = u'接口'
        d['tradeID'] = u'成交编号'
        d['orderID'] = u'委托编号'
        d['symbol'] = u'合约代码'
        d['direction'] = u'方向'
        d['offset'] = u'开平'
        d['price'] = u'价格'
        d['volume'] = u'数量'
        d['tradeTime'] = u'成交时间'
        self.setHeaderDict(d)
        
        self.setEventType(EVENT_TRADE)
        self.initTable()
        self.registerEvent()


########################################################################
class OrderMonitor(BasicMonitor):
    """委托监控"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(OrderMonitor, self).__init__(eventEngine, parent)
        
        d = OrderedDict()
        d['gatewayName'] = u'接口'
        d['orderID'] = u'委托编号'
        d['symbol'] = u'合约代码'
        d['direction'] = u'方向'
        d['offset'] = u'开平'
        d['price'] = u'价格'
        d['totalVolume'] = u'委托数量'
        d['tradedVolume'] = u'成交数量'
        d['status'] = u'状态'
        d['orderTime'] = u'委托时间'
        d['tradeTime'] = u'撤销时间'
        d['frontID'] = u'前置编号'
        d['sessionID'] = u'会话编号'
        self.setHeaderDict(d)
        
        self.setDataKey('vtOrderID')
        self.setEventType(EVENT_ORDER)
        self.initTable()
        self.registerEvent()


########################################################################
class PositionMonitor(BasicMonitor):
    """持仓监控"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(PositionMonitor, self).__init__(eventEngine, parent)
        
        d = OrderedDict()
        d['gatewayName'] = u'接口'
        d['symbol'] = u'合约代码'
        d['direction'] = u'方向'
        d['position'] = u'持仓量'
        d['frozen'] = u'冻结量'
        d['price'] = u'价格'
        self.setHeaderDict(d)
        
        self.setDataKey('vtPositionName')
        self.setEventType(EVENT_POSITION)
        self.initTable()
        self.registerEvent()


########################################################################
class AccountMonitor(BasicMonitor):
    """账户监控"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, parent=None):
        """Constructor"""
        super(AccountMonitor, self).__init__(eventEngine, parent)
        
        d = OrderedDict()
        d['gatewayName'] = u'接口'
        d['accountID'] = u'账户'
        d['preBalance'] = u'昨结'
        d['balance'] = u'净值'
        d['available'] = u'可用'
        d['commission'] = u'手续费'
        d['margin'] = u'保证金'
        d['closeProfit'] = u'平仓盈亏'
        d['positionProfit'] = u'持仓盈亏'
        self.setHeaderDict(d)
        
        self.setDataKey('vtAccountID')
        self.setEventType(EVENT_ACCOUNT)
        self.initTable()
        self.registerEvent()
    
    