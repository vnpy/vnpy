# encoding: UTF-8

import json
import csv
import os
import platform
from collections import OrderedDict

from six import text_type

from vnpy.event import *
from vnpy.trader import vtText
from vnpy.trader.vtEvent import *
from vnpy.trader.vtConstant import *
from vnpy.trader.vtFunction import *
from vnpy.trader.vtGateway import *
from vnpy.trader.uiQt import QtGui, QtWidgets, QtCore, BASIC_FONT


COLOR_RED = QtGui.QColor('red')
COLOR_GREEN = QtGui.QColor('green')


########################################################################
class BasicCell(QtWidgets.QTableWidgetItem):
    """基础的单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(BasicCell, self).__init__()
        self.data = None
        
        self.setTextAlignment(QtCore.Qt.AlignCenter)
        
        if text:
            self.setContent(text)
    
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        if text == '0' or text == '0.0':
            self.setText('')
        else:
            self.setText(text)


########################################################################
class NumCell(BasicCell):
    """用来显示数字的单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(NumCell, self).__init__(text)
        
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        # 考虑到NumCell主要用来显示OrderID和TradeID之类的整数字段，
        # 这里的数据转化方式使用int类型。但是由于部分交易接口的委托
        # 号和成交号可能不是纯数字的形式，因此补充了一个try...except
        try:
            num = int(text)
            self.setData(QtCore.Qt.DisplayRole, num)
        except ValueError:
            self.setText(text)
            

########################################################################
class DirectionCell(BasicCell):
    """用来显示买卖方向的单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(DirectionCell, self).__init__(text)
        
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        if text == DIRECTION_LONG or text == DIRECTION_NET:
            self.setForeground(QtGui.QColor('red'))
        elif text == DIRECTION_SHORT:
            self.setForeground(QtGui.QColor('green'))
        self.setText(text)


########################################################################
class NameCell(BasicCell):
    """用来显示合约中文的单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(NameCell, self).__init__()
        
        self.mainEngine = mainEngine
        self.data = None
        
        if text:
            self.setContent(text)
        
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        if self.mainEngine:
            # 首先尝试正常获取合约对象
            contract = self.mainEngine.getContract(text)
            
            # 如果能读取合约信息
            if contract:
                self.setText(contract.name)


########################################################################
class BidCell(BasicCell):
    """买价单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(BidCell, self).__init__(text)
        
        self.setForeground(QtGui.QColor('black'))
        self.setBackground(QtGui.QColor(255,174,201))
        
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        self.setText(text)


########################################################################
class AskCell(BasicCell):
    """卖价单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(AskCell, self).__init__(text)
        
        self.setForeground(QtGui.QColor('black'))
        self.setBackground(QtGui.QColor(160,255,160))
        
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        self.setText(text)


########################################################################
class PnlCell(BasicCell):
    """显示盈亏的单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(PnlCell, self).__init__()
        self.data = None
        self.color = ''
        if text:
            self.setContent(text)
    
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        self.setText(text)

        try:
            value = float(text)
            if value >= 0 and self.color != 'red':
                self.color = 'red'
                self.setForeground(COLOR_RED)
            elif value < 0 and self.color != 'green':
                self.color = 'green'
                self.setForeground(COLOR_GREEN)
        except ValueError:
            pass


########################################################################
class BasicMonitor(QtWidgets.QTableWidget):
    """
    基础监控
    
    headerDict中的值对应的字典格式如下
    {'chinese': u'中文名', 'cellType': BasicCell}
    
    """
    signal = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, mainEngine=None, eventEngine=None, parent=None):
        """Constructor"""
        super(BasicMonitor, self).__init__(parent)
        
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        # 保存表头标签用
        self.headerDict = OrderedDict()  # 有序字典，key是英文名，value是对应的配置字典
        self.headerList = []             # 对应self.headerDict.keys()
        
        # 保存相关数据用
        self.dataDict = {}  # 字典，key是字段对应的数据，value是保存相关单元格的字典
        self.dataKey = ''   # 字典键对应的数据字段
        
        # 监控的事件类型
        self.eventType = ''
        
        # 列宽调整状态（只在第一次更新数据时调整一次列宽）
        self.columnResized = False
        
        # 字体
        self.font = None
        
        # 保存数据对象到单元格
        self.saveData = False
        
        # 默认不允许根据表头进行排序，需要的组件可以开启
        self.sorting = False
        
        # 默认表头可调整
        self.resizeMode = QtWidgets.QHeaderView.Interactive
        
        # 初始化右键菜单
        self.initMenu()
        
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
    def setSaveData(self, saveData):
        """设置是否要保存数据到单元格"""
        self.saveData = saveData
        
    #----------------------------------------------------------------------
    def initTable(self):
        """初始化表格"""
        # 设置表格的列数
        col = len(self.headerDict)
        self.setColumnCount(col)
        
        # 设置列表头
        labels = [d['chinese'] for d in self.headerDict.values()]
        self.setHorizontalHeaderLabels(labels)
        
        # 关闭左边的垂直表头
        self.verticalHeader().setVisible(False)
        
        # 设为不可编辑
        self.setEditTriggers(self.NoEditTriggers)
        
        # 设为行交替颜色
        self.setAlternatingRowColors(True)
        
        # 设置允许排序
        self.setSortingEnabled(self.sorting)
        
        # 设为表头拉伸
        self.horizontalHeader().setSectionResizeMode(self.resizeMode)

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册GUI更新相关的事件监听"""
        self.signal.connect(self.updateEvent)
        self.eventEngine.register(self.eventType, self.signal.emit)
        
    #----------------------------------------------------------------------
    def updateEvent(self, event):
        """收到事件更新"""
        data = event.dict_['data']
        self.updateData(data)
    
    #----------------------------------------------------------------------
    def updateData(self, data):
        """将数据更新到表格中"""
        # 如果允许了排序功能，则插入数据前必须关闭，否则插入新的数据会变乱
        if self.sorting:
            self.setSortingEnabled(False)
        
        # 如果设置了dataKey，则采用存量更新模式
        if self.dataKey:
            key = data.__getattribute__(self.dataKey)
            # 如果键在数据字典中不存在，则先插入新的一行，并创建对应单元格
            if key not in self.dataDict:
                self.insertRow(0)     
                d = {}
                for n, header in enumerate(self.headerList):                  
                    content = safeUnicode(data.__getattribute__(header))
                    cellType = self.headerDict[header]['cellType']
                    cell = cellType(content, self.mainEngine)
                    
                    if self.font:
                        cell.setFont(self.font)  # 如果设置了特殊字体，则进行单元格设置
                    
                    if self.saveData:            # 如果设置了保存数据对象，则进行对象保存
                        cell.data = data
                        
                    self.setItem(0, n, cell)
                    d[header] = cell
                self.dataDict[key] = d
            # 否则如果已经存在，则直接更新相关单元格
            else:
                d = self.dataDict[key]
                for header in self.headerList:
                    content = safeUnicode(data.__getattribute__(header))
                    cell = d[header]
                    cell.setContent(content)
                    
                    if self.saveData:            # 如果设置了保存数据对象，则进行对象保存
                        cell.data = data                    
        # 否则采用增量更新模式
        else:
            self.insertRow(0)  
            for n, header in enumerate(self.headerList):
                content = safeUnicode(data.__getattribute__(header))
                cellType = self.headerDict[header]['cellType']
                cell = cellType(content, self.mainEngine)
                
                if self.font:
                    cell.setFont(self.font)

                if self.saveData:
                    cell.data = data                

                self.setItem(0, n, cell)                        
                
        ## 调整列宽
        #if not self.columnResized:
            #self.resizeColumns()
            #self.columnResized = True
        
        # 重新打开排序
        if self.sorting:
            self.setSortingEnabled(True)
    
    #----------------------------------------------------------------------
    def resizeColumns(self):
        """调整各列的大小"""
        self.horizontalHeader().resizeSections(QtWidgets.QHeaderView.ResizeToContents)    
        
    #----------------------------------------------------------------------
    def setSorting(self, sorting):
        """设置是否允许根据表头排序"""
        self.sorting = sorting
    
    #----------------------------------------------------------------------
    def setResizeMode(self, mode):
        """"""
        self.resizeMode = mode
        
    #----------------------------------------------------------------------
    def saveToCsv(self):
        """保存表格内容到CSV文件"""
        # 先隐藏右键菜单
        self.menu.close()
        
        # 获取想要保存的文件名
        path, fileType = QtWidgets.QFileDialog.getSaveFileName(self, vtText.SAVE_DATA, '', 'CSV(*.csv)')

        try:
            #if not path.isEmpty():
            if path:
                with open(unicode(path), 'wb') as f:
                    writer = csv.writer(f)
                    
                    # 保存标签
                    headers = [header.encode('gbk') for header in self.headerList]
                    writer.writerow(headers)
                    
                    # 保存每行内容
                    for row in range(self.rowCount()):
                        rowdata = []
                        for column in range(self.columnCount()):
                            item = self.item(row, column)
                            if item is not None:
                                rowdata.append(
                                    text_type(item.text()).encode('gbk'))
                            else:
                                rowdata.append('')
                        writer.writerow(rowdata)     
        except IOError:
            pass

    #----------------------------------------------------------------------
    def initMenu(self):
        """初始化右键菜单"""
        self.menu = QtWidgets.QMenu(self)    
        
        resizeAction = QtWidgets.QAction(vtText.RESIZE_COLUMNS, self)
        resizeAction.triggered.connect(self.resizeColumns)        
        
        saveAction = QtWidgets.QAction(vtText.SAVE_DATA, self)
        saveAction.triggered.connect(self.saveToCsv)
        
        self.menu.addAction(resizeAction)
        self.menu.addAction(saveAction)
        
    #----------------------------------------------------------------------
    def contextMenuEvent(self, event):
        """右键点击事件"""
        self.menu.popup(QtGui.QCursor.pos())    


########################################################################
class MarketMonitor(BasicMonitor):
    """市场监控组件"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(MarketMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        # 设置表头有序字典
        d = OrderedDict()
        d['gatewayName'] = {'chinese':vtText.GATEWAY, 'cellType':BasicCell}
        d['symbol'] = {'chinese':vtText.CONTRACT_SYMBOL, 'cellType':BasicCell}
        d['lastPrice'] = {'chinese':vtText.LAST_PRICE, 'cellType':BasicCell}
        d['volume'] = {'chinese':vtText.VOLUME, 'cellType':BasicCell}
        d['openPrice'] = {'chinese':vtText.OPEN_PRICE, 'cellType':BasicCell}
        d['highPrice'] = {'chinese':vtText.HIGH_PRICE, 'cellType':BasicCell}
        d['lowPrice'] = {'chinese':vtText.LOW_PRICE, 'cellType':BasicCell}
        d['bidPrice1'] = {'chinese':vtText.BID_PRICE_1, 'cellType':BidCell}
        d['bidVolume1'] = {'chinese':vtText.BID_VOLUME_1, 'cellType':BidCell}
        d['askPrice1'] = {'chinese':vtText.ASK_PRICE_1, 'cellType':AskCell}
        d['askVolume1'] = {'chinese':vtText.ASK_VOLUME_1, 'cellType':AskCell}
        d['time'] = {'chinese':vtText.TIME, 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setDataKey('vtSymbol')
        self.setEventType(EVENT_TICK)
        self.setFont(BASIC_FONT)
        self.setSorting(False)
        self.setResizeMode(QtWidgets.QHeaderView.Stretch)
        
        self.initTable()
        self.registerEvent()
        
        self.setFixedHeight(400)


########################################################################
class LogMonitor(BasicMonitor):
    """日志监控"""
    signalError = QtCore.Signal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(LogMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        d = OrderedDict()        
        d['gatewayName'] = {'chinese':vtText.GATEWAY, 'cellType':BasicCell}
        d['logTime'] = {'chinese':vtText.TIME, 'cellType':BasicCell}
        d['logContent'] = {'chinese':vtText.CONTENT, 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setEventType(EVENT_LOG)
        self.setFont(BASIC_FONT)        
        self.initTable()
        self.registerEvent()
        
        self.signalError.connect(self.processErrorEvent)
        self.eventEngine.register(EVENT_ERROR, self.signalError.emit)
        
        self.horizontalHeader().setSectionResizeMode(2, QtWidgets.QHeaderView.Stretch)
        self.setFixedHeight(200)
    
    #----------------------------------------------------------------------
    def processErrorEvent(self, event):
        """"""
        error = event.dict_['data']
        logContent = u'发生错误，错误代码:%s，错误信息:%s' %(error.errorID, error.errorMsg)
        
        self.insertRow(0)
        cellLogTime = BasicCell(error.errorTime)
        cellLogContent = BasicCell(logContent)
        cellGatewayName = BasicCell(error.gatewayName)
        
        self.setItem(0, 0, cellGatewayName)
        self.setItem(0, 1, cellLogTime)
        self.setItem(0, 2, cellLogContent)



########################################################################
class TradeMonitor(BasicMonitor):
    """成交监控"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(TradeMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        d = OrderedDict()
        d['gatewayName'] = {'chinese':vtText.GATEWAY, 'cellType':BasicCell}
        d['tradeID'] = {'chinese':vtText.TRADE_ID, 'cellType':NumCell}
        d['orderID'] = {'chinese':vtText.ORDER_ID, 'cellType':NumCell}
        d['symbol'] = {'chinese':vtText.CONTRACT_SYMBOL, 'cellType':BasicCell}
        d['direction'] = {'chinese':vtText.DIRECTION, 'cellType':DirectionCell}
        d['price'] = {'chinese':vtText.PRICE, 'cellType':BasicCell}
        d['volume'] = {'chinese':vtText.VOLUME, 'cellType':BasicCell}
        d['tradeTime'] = {'chinese':vtText.TRADE_TIME, 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setEventType(EVENT_TRADE)
        self.setFont(BASIC_FONT)
        self.setSorting(True)
        self.setResizeMode(QtWidgets.QHeaderView.Stretch)
        
        self.initTable()
        self.registerEvent()

        self.setFixedHeight(200)
        

########################################################################
class OrderMonitor(BasicMonitor):
    """委托监控"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(OrderMonitor, self).__init__(mainEngine, eventEngine, parent)

        self.mainEngine = mainEngine
        
        d = OrderedDict()
        d['gatewayName'] = {'chinese':vtText.GATEWAY, 'cellType':BasicCell}
        d['orderID'] = {'chinese':vtText.ORDER_ID, 'cellType':NumCell}
        d['symbol'] = {'chinese':vtText.CONTRACT_SYMBOL, 'cellType':BasicCell}
        d['direction'] = {'chinese':vtText.DIRECTION, 'cellType':DirectionCell}
        d['price'] = {'chinese':vtText.PRICE, 'cellType':BasicCell}
        d['totalVolume'] = {'chinese':vtText.ORDER_VOLUME, 'cellType':BasicCell}
        d['tradedVolume'] = {'chinese':vtText.TRADED_VOLUME, 'cellType':BasicCell}
        d['status'] = {'chinese':vtText.ORDER_STATUS, 'cellType':BasicCell}
        d['orderTime'] = {'chinese':vtText.ORDER_TIME, 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setDataKey('vtOrderID')
        self.setEventType(EVENT_ORDER)
        self.setFont(BASIC_FONT)
        self.setSaveData(True)
        self.setSorting(True)
        self.setResizeMode(QtWidgets.QHeaderView.Stretch)
        
        self.initTable()
        self.registerEvent()
        self.connectSignal()
        
    #----------------------------------------------------------------------
    def connectSignal(self):
        """连接信号"""
        # 双击单元格撤单
        self.itemDoubleClicked.connect(self.cancelOrder) 
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cell):
        """根据单元格的数据撤单"""
        order = cell.data
        
        req = VtCancelOrderReq()
        req.symbol = order.symbol
        req.exchange = order.exchange
        req.frontID = order.frontID
        req.sessionID = order.sessionID
        req.orderID = order.orderID
        self.mainEngine.cancelOrder(req, order.gatewayName)


########################################################################
class PositionMonitor(BasicMonitor):
    """持仓监控"""
    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(PositionMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        d = OrderedDict()
        d['gatewayName'] = {'chinese':vtText.GATEWAY, 'cellType':BasicCell}
        d['symbol'] = {'chinese':vtText.CONTRACT_SYMBOL, 'cellType':BasicCell}
        d['direction'] = {'chinese':vtText.DIRECTION, 'cellType':DirectionCell}
        d['position'] = {'chinese':vtText.POSITION, 'cellType':BasicCell}
        d['frozen'] = {'chinese':vtText.FROZEN, 'cellType':BasicCell}
        d['price'] = {'chinese':vtText.PRICE, 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setDataKey('vtPositionName')
        self.setEventType(EVENT_POSITION)
        self.setFont(BASIC_FONT)
        self.setSaveData(True)
        self.setResizeMode(QtWidgets.QHeaderView.Stretch)
        
        self.initTable()
        self.registerEvent()
        
        
########################################################################
class AccountMonitor(BasicMonitor):
    """账户监控"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(AccountMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        d = OrderedDict()
        d['gatewayName'] = {'chinese':vtText.GATEWAY, 'cellType':BasicCell}
        d['accountID'] = {'chinese':vtText.ACCOUNT_ID, 'cellType':BasicCell}
        d['balance'] = {'chinese':vtText.BALANCE, 'cellType':BasicCell}
        d['available'] = {'chinese':vtText.AVAILABLE, 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setDataKey('vtAccountID')
        self.setEventType(EVENT_ACCOUNT)
        self.setFont(BASIC_FONT)
        self.setSaveData(True)
        self.setResizeMode(QtWidgets.QHeaderView.Stretch)
        
        self.initTable()
        self.registerEvent()
    
    #----------------------------------------------------------------------
    def updateData(self, data):
        """更新数据"""
        super(AccountMonitor, self).updateData(data)

        # 如果该委托已完成，则隐藏该行
        vtAccountID = data.vtAccountID
        cellDict = self.dataDict[vtAccountID]
        cell = cellDict['balance']
        row = self.row(cell)
        
        if data.balance == 0:    
            self.hideRow(row)
        else:
            self.showRow(row)


########################################################################
class DepthMonitor(QtWidgets.QTableWidget):
    """报价深度监控"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        super(DepthMonitor, self).__init__()    
        
        self.mainEngine = mainEngine
        
        self.contractSize = 1   # 合约乘数
        self.cellDict = {}
        
        self.initUi()
    
    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        labels = [u'价格',
                  u'数量',
                  u'总额']
        
        self.setColumnCount(len(labels))
        self.setHorizontalHeaderLabels(labels)
        self.setRowCount(11)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)   
        self.horizontalHeader().setSectionResizeMode(QtWidgets.QHeaderView.Stretch) 
        self.verticalHeader().setSectionResizeMode(QtWidgets.QHeaderView.Stretch) 
        
        left = QtCore.Qt.AlignLeft
        right = QtCore.Qt.AlignRight
        
        # 单元格
        askColor = 'green'
        bidColor = 'red'
        lastColor = 'orange'
        
        self.addCell('askPrice5', 0, 0, askColor)
        self.addCell('askPrice4', 1, 0, askColor)
        self.addCell('askPrice3', 2, 0, askColor)
        self.addCell('askPrice2', 3, 0, askColor)
        self.addCell('askPrice1', 4, 0, askColor)
        self.addCell('lastPrice', 5, 0, lastColor)
        self.addCell('bidPrice1', 6, 0, bidColor)
        self.addCell('bidPrice2', 7, 0, bidColor)
        self.addCell('bidPrice3', 8, 0, bidColor)
        self.addCell('bidPrice4', 9, 0, bidColor)
        self.addCell('bidPrice5', 10, 0, bidColor)
        
        self.addCell('askVolume5', 0, 1, askColor)
        self.addCell('askVolume4', 1, 1, askColor)
        self.addCell('askVolume3', 2, 1, askColor)
        self.addCell('askVolume2', 3, 1, askColor)
        self.addCell('askVolume1', 4, 1, askColor)
        self.addCell('todayChange', 5, 1, lastColor)
        self.addCell('bidVolume1', 6, 1, bidColor)
        self.addCell('bidVolume2', 7, 1, bidColor)
        self.addCell('bidVolume3', 8, 1, bidColor)
        self.addCell('bidVolume4', 9, 1, bidColor)
        self.addCell('bidVolume5', 10, 1, bidColor)
        
        self.addCell('askValue5', 0, 2, askColor)
        self.addCell('askValue4', 1, 2, askColor)
        self.addCell('askValue3', 2, 2, askColor)
        self.addCell('askValue2', 3, 2, askColor)
        self.addCell('askValue1', 4, 2, askColor)
        self.addCell('bidValue1', 6, 2, bidColor)
        self.addCell('bidValue2', 7, 2, bidColor)
        self.addCell('bidValue3', 8, 2, bidColor)
        self.addCell('bidValue4', 9, 2, bidColor)
        self.addCell('bidValue5', 10, 2, bidColor)
        
    #----------------------------------------------------------------------
    def addCell(self, name, row, col, color, alignment=None):
        """新增单元格"""
        cell = QtWidgets.QTableWidgetItem()
        self.setItem(row, col, cell)
        self.cellDict[name] = cell
        
        if color:
            cell.setForeground(QtGui.QColor(color))
        
        if alignment:
            cell.setTextAlignment(alignment)
        else:
            cell.setTextAlignment(QtCore.Qt.AlignCenter)
    
    #----------------------------------------------------------------------
    def updateCell(self, name, value, decimals=None, data=None):
        """更新单元格"""
        if decimals is not None:
            text = '%.*f' %(decimals, value)
        else:
            text = '%s' %value
            
        cell = self.cellDict[name]
        cell.setText(text)
        
        if data:
            cell.price = data
    
    #----------------------------------------------------------------------
    def updateTick(self, tick):
        """更新Tick"""
        valueDecimals = 2
        
        # bid
        self.updateCell('bidPrice1', tick.bidPrice1, data=tick.bidPrice1)
        self.updateCell('bidPrice2', tick.bidPrice2, data=tick.bidPrice2)
        self.updateCell('bidPrice3', tick.bidPrice3, data=tick.bidPrice3)
        self.updateCell('bidPrice4', tick.bidPrice4, data=tick.bidPrice4)
        self.updateCell('bidPrice5', tick.bidPrice5, data=tick.bidPrice5)
        
        self.updateCell('bidVolume1', tick.bidVolume1, data=tick.bidPrice1)
        self.updateCell('bidVolume2', tick.bidVolume2, data=tick.bidPrice2)
        self.updateCell('bidVolume3', tick.bidVolume3, data=tick.bidPrice3)
        self.updateCell('bidVolume4', tick.bidVolume4, data=tick.bidPrice4)
        self.updateCell('bidVolume5', tick.bidVolume5, data=tick.bidPrice5)
        
        self.updateCell('bidValue1', tick.bidPrice1*tick.bidVolume1*self.contractSize, valueDecimals, data=tick.bidPrice1)
        self.updateCell('bidValue2', tick.bidPrice2*tick.bidVolume2*self.contractSize, valueDecimals, data=tick.bidPrice2)
        self.updateCell('bidValue3', tick.bidPrice3*tick.bidVolume3*self.contractSize, valueDecimals, data=tick.bidPrice3)
        self.updateCell('bidValue4', tick.bidPrice4*tick.bidVolume4*self.contractSize, valueDecimals, data=tick.bidPrice4)
        self.updateCell('bidValue5', tick.bidPrice5*tick.bidVolume5*self.contractSize, valueDecimals, data=tick.bidPrice5)
        
        # ask
        self.updateCell('askPrice1', tick.askPrice1, data=tick.askPrice1)
        self.updateCell('askPrice2', tick.askPrice2, data=tick.askPrice2)
        self.updateCell('askPrice3', tick.askPrice3, data=tick.askPrice3)
        self.updateCell('askPrice4', tick.askPrice4, data=tick.askPrice4)
        self.updateCell('askPrice5', tick.askPrice5, data=tick.askPrice5)
        
        self.updateCell('askVolume1', tick.askVolume1, data=tick.askPrice1)
        self.updateCell('askVolume2', tick.askVolume2, data=tick.askPrice2)
        self.updateCell('askVolume3', tick.askVolume3, data=tick.askPrice3)
        self.updateCell('askVolume4', tick.askVolume4, data=tick.askPrice4)
        self.updateCell('askVolume5', tick.askVolume5, data=tick.askPrice5)
        
        self.updateCell('askValue1', tick.askPrice1*tick.askVolume1*self.contractSize, valueDecimals, data=tick.askPrice1)
        self.updateCell('askValue2', tick.askPrice2*tick.askVolume2*self.contractSize, valueDecimals, data=tick.askPrice2)
        self.updateCell('askValue3', tick.askPrice3*tick.askVolume3*self.contractSize, valueDecimals, data=tick.askPrice3)
        self.updateCell('askValue4', tick.askPrice4*tick.askVolume4*self.contractSize, valueDecimals, data=tick.askPrice4)
        self.updateCell('askValue5', tick.askPrice5*tick.askVolume5*self.contractSize, valueDecimals, data=tick.askPrice5)
        
        # today
        self.updateCell('lastPrice', tick.lastPrice)
        
        if tick.openPrice:
            todayChange = tick.lastPrice/tick.openPrice - 1
        else:
            todayChange = 0
            
        self.updateCell('todayChange', ('%.2f%%' %(todayChange*100)))
    
    #----------------------------------------------------------------------
    def updateVtSymbol(self, vtSymbol):
        """更换显示行情标的"""
        for cell in self.cellDict.values():
            cell.setText('')
        
        contract = self.mainEngine.getContract(vtSymbol)
        if contract:
            self.contractSize = contract.size
        else:
            self.contractSize = 1


########################################################################
class TradingWidget(QtWidgets.QFrame):
    """简单交易组件"""
    signal = QtCore.Signal(type(Event()))
    
    directionList = [DIRECTION_LONG,
                     DIRECTION_SHORT]

    priceTypeList = [PRICETYPE_LIMITPRICE,
                     PRICETYPE_MARKETPRICE]
    
    gatewayList = ['']

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(TradingWidget, self).__init__(parent)
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        self.vtSymbol = ''
        
        # 添加交易接口
        l = mainEngine.getAllGatewayDetails()
        gatewayNameList = [d['gatewayName'] for d in l]
        self.gatewayList.extend(gatewayNameList)

        self.initUi()
        self.registerEvent()

    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(vtText.TRADING)
        self.setFixedHeight(400)
        self.setFixedWidth(600)
        self.setFrameShape(self.Box)    # 设置边框
        self.setLineWidth(1)           

        # 左边部分
        labelPriceType = QtWidgets.QLabel(vtText.PRICE_TYPE)
        labelSymbol = QtWidgets.QLabel(u'VT代码')
        labelPrice = QtWidgets.QLabel(vtText.PRICE)
        labelVolume = QtWidgets.QLabel(u'数量')
        
        self.comboPriceType = QtWidgets.QComboBox()
        self.comboPriceType.addItems(self.priceTypeList)
        
        self.lineSymbol = QtWidgets.QLineEdit()
        
        validator = QtGui.QDoubleValidator()
        validator.setBottom(0)        

        self.linePrice = QtWidgets.QLineEdit()
        self.linePrice.setValidator(validator)
        
        self.lineVolume = QtWidgets.QLineEdit()
        self.lineVolume.setValidator(validator)
        
        gridLeft = QtWidgets.QGridLayout()
        gridLeft.addWidget(labelPriceType, 0, 0)
        gridLeft.addWidget(labelSymbol, 1, 0)
        gridLeft.addWidget(labelPrice, 2, 0)
        gridLeft.addWidget(labelVolume, 3, 0)
        
        gridLeft.addWidget(self.comboPriceType, 0, 1)
        gridLeft.addWidget(self.lineSymbol, 1, 1)
        gridLeft.addWidget(self.linePrice, 2, 1)
        gridLeft.addWidget(self.lineVolume, 3, 1)
        
        # 右边部分
        self.depthMonitor = DepthMonitor(self.mainEngine, self.eventEngine)

        # 发单按钮
        buttonBuy = QtWidgets.QPushButton(u'买入')
        buttonSell = QtWidgets.QPushButton(u'卖出')
        buttonCancelAll = QtWidgets.QPushButton(vtText.CANCEL_ALL)
        
        size = buttonBuy.sizeHint()
        buttonBuy.setMinimumHeight(size.height()*2)
        buttonSell.setMinimumHeight(size.height()*2)
        buttonCancelAll.setMinimumHeight(size.height()*2)
        
        buttonBuy.clicked.connect(self.sendBuyOrder)
        buttonSell.clicked.connect(self.sendSellOrder)
        buttonCancelAll.clicked.connect(self.cancelAll)
        
        buttonBuy.setStyleSheet('color:white;background-color:red')
        buttonSell.setStyleSheet('color:white;background-color:green')
        buttonCancelAll.setStyleSheet('color:black;background-color:yellow')
        
        gridButton = QtWidgets.QGridLayout()
        gridButton.addWidget(buttonBuy, 0, 0)
        gridButton.addWidget(buttonSell, 0, 1)
        gridButton.addWidget(buttonCancelAll, 1, 0, 1, 2)
        
        # 整合布局
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(gridLeft)
        vbox.addLayout(gridButton)
        
        hbox = QtWidgets.QHBoxLayout()
        hbox.addLayout(vbox)
        hbox.addWidget(self.depthMonitor)
        
        self.setLayout(hbox)

        # 关联更新
        self.lineSymbol.returnPressed.connect(self.updateSymbol)
        self.depthMonitor.itemDoubleClicked.connect(self.updatePrice)

    #----------------------------------------------------------------------
    def updateSymbol(self):
        """合约变化"""
        self.vtSymbol = str(self.lineSymbol.text())
        contract = self.mainEngine.getContract(self.vtSymbol)
        
        if not contract:
            return
        
        # 清空价格数量
        self.linePrice.clear()
        self.lineVolume.clear()

        self.depthMonitor.updateVtSymbol(self.vtSymbol)
        
        # 订阅合约
        req = VtSubscribeReq()
        req.symbol = contract.symbol
        self.mainEngine.subscribe(req, contract.gatewayName)

    #----------------------------------------------------------------------
    def updateTick(self, event):
        """更新行情"""
        tick = event.dict_['data']
        if tick.vtSymbol != self.vtSymbol:
            return
        self.depthMonitor.updateTick(tick)

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateTick)
        self.eventEngine.register(EVENT_TICK, self.signal.emit)        
    
    #----------------------------------------------------------------------
    def updatePrice(self, cell):
        """"""
        try:
            price = cell.price
        except AttributeError:
            return
        self.linePrice.setText(str(price))

    #----------------------------------------------------------------------
    def sendOrder(self, direction):
        """发单"""
        vtSymbol = str(self.lineSymbol.text())
        contract = self.mainEngine.getContract(vtSymbol)
        if not contract:
            return

        # 获取价格
        priceText = self.linePrice.text()
        if not priceText:
            return
        price = float(priceText)
        
        # 获取数量
        volumeText = self.lineVolume.text()
        if not volumeText:
            return
        
        if '.' in volumeText:
            volume = float(volumeText)
        else:
            volume = int(volumeText)
        
        # 委托
        req = VtOrderReq()
        req.symbol = contract.symbol
        req.price = price
        req.volume = volume
        req.direction = direction
        req.priceType = text_type(self.comboPriceType.currentText())
        
        self.mainEngine.sendOrder(req, contract.gatewayName)
    
    #----------------------------------------------------------------------
    def sendBuyOrder(self):
        """"""
        self.sendOrder(DIRECTION_LONG)
        
    #----------------------------------------------------------------------
    def sendSellOrder(self):
        """"""
        self.sendOrder(DIRECTION_SHORT)
        
    #----------------------------------------------------------------------
    def cancelAll(self):
        """一键撤销所有委托"""
        l = self.mainEngine.getAllWorkingOrders()
        for order in l:
            req = VtCancelOrderReq()
            req.symbol = order.symbol
            req.exchange = order.exchange
            req.frontID = order.frontID
            req.sessionID = order.sessionID
            req.orderID = order.orderID
            self.mainEngine.cancelOrder(req, order.gatewayName)


########################################################################
class ContractMonitor(BasicMonitor):
    """合约查询"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, parent=None):
        """Constructor"""
        super(ContractMonitor, self).__init__(parent=parent)
        
        self.mainEngine = mainEngine
        
        d = OrderedDict()
        d['symbol'] = {'chinese':vtText.CONTRACT_SYMBOL, 'cellType':BasicCell}
        d['exchange'] = {'chinese':vtText.EXCHANGE, 'cellType':BasicCell}
        d['vtSymbol'] = {'chinese':vtText.VT_SYMBOL, 'cellType':BasicCell}
        d['productClass'] = {'chinese':vtText.PRODUCT_CLASS, 'cellType':BasicCell}
        d['size'] = {'chinese':vtText.CONTRACT_SIZE, 'cellType':BasicCell}
        d['priceTick'] = {'chinese':vtText.PRICE_TICK, 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        # 过滤显示用的字符串
        self.filterContent = EMPTY_STRING
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setMinimumSize(800, 800)
        self.setFont(BASIC_FONT)
        self.setResizeMode(QtWidgets.QHeaderView.Stretch)
        self.initTable()
        self.addMenuAction()
    
    #----------------------------------------------------------------------
    def showAllContracts(self):
        """显示所有合约数据"""
        l = self.mainEngine.getAllContracts()
        d = {'.'.join([contract.exchange, contract.symbol]):contract for contract in l}
        l2 = list(d.keys())
        l2.sort(reverse=True)

        self.setRowCount(len(l2))
        row = 0
        
        for key in l2:
            # 如果设置了过滤信息且合约代码中不含过滤信息，则不显示
            if self.filterContent and self.filterContent not in key:
                continue
            
            contract = d[key]
            
            for n, header in enumerate(self.headerList):
                content = safeUnicode(contract.__getattribute__(header))
                cellType = self.headerDict[header]['cellType']
                cell = cellType(content)
                
                if self.font:
                    cell.setFont(self.font)  # 如果设置了特殊字体，则进行单元格设置
                    
                self.setItem(row, n, cell)          
            
            row = row + 1        
    
    #----------------------------------------------------------------------
    def refresh(self):
        """刷新"""
        self.menu.close()   # 关闭菜单
        self.clearContents()
        self.setRowCount(0)
        self.showAllContracts()
    
    #----------------------------------------------------------------------
    def addMenuAction(self):
        """增加右键菜单内容"""
        refreshAction = QtWidgets.QAction(vtText.REFRESH, self)
        refreshAction.triggered.connect(self.refresh)
        
        self.menu.addAction(refreshAction)
    
    #----------------------------------------------------------------------
    def show(self):
        """显示"""
        super(ContractMonitor, self).show()
        self.refresh()
        
    #----------------------------------------------------------------------
    def setFilterContent(self, content):
        """设置过滤字符串"""
        self.filterContent = content
    

########################################################################
class ContractManager(QtWidgets.QWidget):
    """合约管理组件"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, parent=None):
        """Constructor"""
        super(ContractManager, self).__init__(parent=parent)
        
        self.mainEngine = mainEngine
        
        self.initUi()
    
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(vtText.CONTRACT_SEARCH)
        
        self.lineFilter = QtWidgets.QLineEdit()
        self.buttonFilter = QtWidgets.QPushButton(vtText.SEARCH)
        self.buttonFilter.clicked.connect(self.filterContract)        
        self.monitor = ContractMonitor(self.mainEngine)
        self.monitor.refresh()
        
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(self.lineFilter)
        hbox.addWidget(self.buttonFilter)
        hbox.addStretch()
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.monitor)
        
        self.setLayout(vbox)
        
    #----------------------------------------------------------------------
    def filterContract(self):
        """显示过滤后的合约"""
        content = str(self.lineFilter.text())
        self.monitor.setFilterContent(content)
        self.monitor.refresh()


########################################################################
class WorkingOrderMonitor(OrderMonitor):
    """活动委托监控"""
    STATUS_COMPLETED = [STATUS_ALLTRADED, STATUS_CANCELLED, STATUS_REJECTED]

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(WorkingOrderMonitor, self).__init__(mainEngine, eventEngine, parent)
        
    #----------------------------------------------------------------------
    def updateData(self, data):
        """更新数据"""
        super(WorkingOrderMonitor, self).updateData(data)

        # 如果该委托已完成，则隐藏该行
        if data.status in self.STATUS_COMPLETED:
            vtOrderID = data.vtOrderID
            cellDict = self.dataDict[vtOrderID]
            cell = cellDict['status']
            row = self.row(cell)
            self.hideRow(row)    
    

########################################################################
class SettingEditor(QtWidgets.QWidget):
    """配置编辑器"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, parent=None):
        """Constructor"""
        super(SettingEditor, self).__init__(parent)
        
        self.mainEngine = mainEngine
        self.currentFileName = ''
        
        self.initUi()
    
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(vtText.EDIT_SETTING)
        
        self.comboFileName = QtWidgets.QComboBox()
        self.comboFileName.addItems(jsonPathDict.keys())
        
        buttonLoad = QtWidgets.QPushButton(vtText.LOAD)
        buttonSave = QtWidgets.QPushButton(vtText.SAVE)
        buttonLoad.clicked.connect(self.loadSetting)
        buttonSave.clicked.connect(self.saveSetting)
        
        self.editSetting = QtWidgets.QTextEdit()
        self.labelPath = QtWidgets.QLabel()
        
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(self.comboFileName)
        hbox.addWidget(buttonLoad)
        hbox.addWidget(buttonSave)
        hbox.addStretch()
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.editSetting)
        vbox.addWidget(self.labelPath)
        
        self.setLayout(vbox)
        
    #----------------------------------------------------------------------
    def loadSetting(self):
        """加载配置"""
        self.currentFileName = str(self.comboFileName.currentText())
        filePath = jsonPathDict[self.currentFileName]
        self.labelPath.setText(filePath)
        
        with open(filePath) as f:
            self.editSetting.clear()
            
            for line in f:
                line = line.replace('\n', '')   # 移除换行符号
                line = line.decode('UTF-8')
                self.editSetting.append(line)
    
    #----------------------------------------------------------------------
    def saveSetting(self):
        """保存配置"""
        if not self.currentFileName:
            return
        
        filePath = jsonPathDict[self.currentFileName]
        
        with open(filePath, 'w') as f:
            content = self.editSetting.toPlainText()
            content = content.encode('UTF-8')
            f.write(content)
        
    #----------------------------------------------------------------------
    def show(self):
        """显示"""
        # 更新配置文件下拉框
        self.comboFileName.clear()
        self.comboFileName.addItems(jsonPathDict.keys())
        
        # 显示界面
        super(SettingEditor, self).show()

    
    
