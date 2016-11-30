# encoding: UTF-8

import json
import csv
from collections import OrderedDict

from PyQt4 import QtGui, QtCore

from eventEngine import *
from vtFunction import *
from vtGateway import *
import os


#----------------------------------------------------------------------
def loadFont():
    """载入字体设置"""
    try:
        f = file("VT_setting.json")
        setting = json.load(f)
        family = setting['fontFamily']
        size = setting['fontSize']
        font = QtGui.QFont(family, size)
    except:
        font = QtGui.QFont(u'微软雅黑', 12)
    return font

BASIC_FONT = loadFont()


########################################################################
class BasicCell(QtGui.QTableWidgetItem):
    """基础的单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(BasicCell, self).__init__()
        self.data = None
        if text:
            self.setContent(text)
    
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        if text == '0' or text == '0.0' or type(text) == type(None):
            self.setText('')
        else:
            self.setText(text)


########################################################################
class DirectionCell(QtGui.QTableWidgetItem):
    """用来显示买卖方向的单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(DirectionCell, self).__init__()
        self.data = None
        if text:
            self.setContent(text)
        
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        if text == DIRECTION_LONG or text == DIRECTION_NET:
            self.setForeground(QtGui.QColor('red'))
        elif text == DIRECTION_SHORT:
            self.setForeground(QtGui.QColor('green'))
        self.setText(text)


########################################################################
class NameCell(QtGui.QTableWidgetItem):
    """用来显示合约中文名的单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(NameCell, self).__init__()
        self.data = None
        if text:
            self.setContent(text)
    
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        self.setText(text)


########################################################################
class NameCell(QtGui.QTableWidgetItem):
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
class BidCell(QtGui.QTableWidgetItem):
    """买价单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(BidCell, self).__init__()
        self.data = None

        self.setForeground(QtGui.QColor('black'))
        self.setBackground(QtGui.QColor(255,174,201))
        
        if text:
            self.setContent(text)
    
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        self.setText(text)


########################################################################
class AskCell(QtGui.QTableWidgetItem):
    """买价单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, mainEngine=None):
        """Constructor"""
        super(AskCell, self).__init__()
        self.data = None

        self.setForeground(QtGui.QColor('black'))
        self.setBackground(QtGui.QColor(160,255,160))
        
        if text:
            self.setContent(text)
    
    #----------------------------------------------------------------------
    def setContent(self, text):
        """设置内容"""
        self.setText(text)


########################################################################
class BasicMonitor(QtGui.QTableWidget):
    """
    基础监控
    
    headerDict中的值对应的字典格式如下
    {'chinese': u'中文名', 'cellType': BasicCell}
    
    """
    signal = QtCore.pyqtSignal(type(Event()))

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
        
        # 字体
        self.font = None
        
        # 保存数据对象到单元格
        self.saveData = False
        
        # 默认不允许根据表头进行排序，需要的组件可以开启
        self.sorting = False
        
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
                
        # 调整列宽
        self.resizeColumns()
        
        # 重新打开排序
        if self.sorting:
            self.setSortingEnabled(True)
    
    #----------------------------------------------------------------------
    def resizeColumns(self):
        """调整各列的大小"""
        self.horizontalHeader().resizeSections(QtGui.QHeaderView.ResizeToContents)    
        
    #----------------------------------------------------------------------
    def setSorting(self, sorting):
        """设置是否允许根据表头排序"""
        self.sorting = sorting
        
    #----------------------------------------------------------------------
    def saveToCsv(self, path=EMPTY_STRING):
        """保存表格内容到CSV文件"""

        # 获取想要保存的文件名
        if not path:
            # 先隐藏右键菜单
            self.menu.close()

            path = QtGui.QFileDialog.getSaveFileName(self, '保存数据', '', 'CSV(*.csv)')

        log = VtLogData()
        log.gatewayName = u'-'

        try:
            if not os.path.exists(path):
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
                                    unicode(item.text()).encode('gbk'))
                            else:
                                rowdata.append('')
                        writer.writerow(rowdata)

                log.logContent = u'数据保存至:{0}'.format(path)

        except IOError:
            log.logContent = u'文件IO失败:{0}'.format(path)

        event1 = Event(type_=EVENT_LOG)
        event1.dict_['data'] = log
        self.eventEngine.put(event1)

    #----------------------------------------------------------------------
    def initMenu(self):
        """初始化右键菜单"""
        self.menu = QtGui.QMenu(self)    
        
        saveAction = QtGui.QAction(u'保存内容', self)
        saveAction.triggered.connect(self.saveToCsv)
        
        self.menu.addAction(saveAction)
        
    #----------------------------------------------------------------------
    def contextMenuEvent(self, event):
        """右键点击事件"""
        self.menu.popup(QtGui.QCursor.pos())    

    def clearData(self):
        """清空数据"""
        self.dataDict = {}
        self.setRowCount(0)

########################################################################
class MarketMonitor(BasicMonitor):
    """市场监控组件"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(MarketMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        # 设置表头有序字典
        d = OrderedDict()
        d['symbol'] = {'chinese':u'合约代码', 'cellType':BasicCell}
        d['vtSymbol'] = {'chinese':u'名称', 'cellType':NameCell}
        d['lastPrice'] = {'chinese':u'最新价', 'cellType':BasicCell}
        d['preClosePrice'] = {'chinese':u'昨收盘价', 'cellType':BasicCell}
        d['volume'] = {'chinese':u'成交量', 'cellType':BasicCell}
        d['openInterest'] = {'chinese':u'持仓量', 'cellType':BasicCell}
        d['openPrice'] = {'chinese':u'开盘价', 'cellType':BasicCell}
        d['highPrice'] = {'chinese':u'最高价', 'cellType':BasicCell}
        d['lowPrice'] = {'chinese':u'最低价', 'cellType':BasicCell}
        d['bidPrice1'] = {'chinese':u'买一价', 'cellType':BidCell}
        d['bidVolume1'] = {'chinese':u'买一量', 'cellType':BidCell}
        d['askPrice1'] = {'chinese':u'卖一价', 'cellType':AskCell}
        d['askVolume1'] = {'chinese':u'卖一量', 'cellType':AskCell}
        d['time'] = {'chinese':u'时间', 'cellType':BasicCell}
        d['gatewayName'] = {'chinese':u'接口', 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        # 设置数据键
        self.setDataKey('vtSymbol')
        
        # 设置监控事件类型
        self.setEventType(EVENT_TICK)
        
        # 设置字体
        self.setFont(BASIC_FONT)
        
        # 设置允许排序
        self.setSorting(True)
        
        # 初始化表格
        self.initTable()
        
        # 注册事件监听
        self.registerEvent()


########################################################################
class LogMonitor(BasicMonitor):
    """日志监控"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(LogMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        d = OrderedDict()        
        d['logTime'] = {'chinese':u'时间', 'cellType':BasicCell}
        d['logContent'] = {'chinese':u'内容', 'cellType':BasicCell}
        d['gatewayName'] = {'chinese':u'接口', 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setEventType(EVENT_LOG)
        self.setFont(BASIC_FONT)        
        self.initTable()
        self.registerEvent()


########################################################################
class ErrorMonitor(BasicMonitor):
    """错误监控"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(ErrorMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        d = OrderedDict()
        d['errorTime']  = {'chinese':u'错误时间', 'cellType':BasicCell}
        d['errorID'] = {'chinese':u'错误代码', 'cellType':BasicCell}
        d['errorMsg'] = {'chinese':u'错误信息', 'cellType':BasicCell}
        d['additionalInfo'] = {'chinese':u'补充信息', 'cellType':BasicCell}
        d['gatewayName'] = {'chinese':u'接口', 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setEventType(EVENT_ERROR)
        self.setFont(BASIC_FONT)
        self.initTable()
        self.registerEvent()


########################################################################
class TradeMonitor(BasicMonitor):
    """成交监控"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(TradeMonitor, self).__init__(mainEngine, eventEngine, parent)
        
        d = OrderedDict()
        d['tradeID'] = {'chinese':u'成交编号', 'cellType':BasicCell}
        d['orderID'] = {'chinese':u'委托编号', 'cellType':BasicCell}
        d['symbol'] = {'chinese':u'合约代码', 'cellType':BasicCell}
        d['vtSymbol'] = {'chinese':u'名称', 'cellType':NameCell}
        d['direction'] = {'chinese':u'方向', 'cellType':DirectionCell}
        d['offset'] = {'chinese':u'开平', 'cellType':BasicCell}
        d['price'] = {'chinese':u'价格', 'cellType':BasicCell}
        d['volume'] = {'chinese':u'数量', 'cellType':BasicCell}
        d['tradeTime'] = {'chinese':u'成交时间', 'cellType':BasicCell}
        d['gatewayName'] = {'chinese':u'接口', 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setEventType(EVENT_TRADE)
        self.setFont(BASIC_FONT)
        self.initTable()
        self.registerEvent()


########################################################################
class OrderMonitor(BasicMonitor):
    """委托监控"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(OrderMonitor, self).__init__(mainEngine, eventEngine, parent)

        self.mainEngine = mainEngine
        
        d = OrderedDict()
        d['orderID'] = {'chinese':u'委托编号', 'cellType':BasicCell}
        d['symbol'] = {'chinese':u'合约代码', 'cellType':BasicCell}
        d['vtSymbol'] = {'chinese':u'名称', 'cellType':NameCell}
        d['direction'] = {'chinese':u'方向', 'cellType':DirectionCell}
        d['offset'] = {'chinese':u'开平', 'cellType':BasicCell}
        d['price'] = {'chinese':u'价格', 'cellType':BasicCell}
        d['status'] = {'chinese':u'状态', 'cellType':BasicCell}
        d['orderTime'] = {'chinese':u'委托时间', 'cellType':BasicCell}
        d['totalVolume'] = {'chinese':u'委托数量', 'cellType':BasicCell}
        d['tradedVolume'] = {'chinese':u'成交数量', 'cellType':BasicCell}
        #d['updateTime'] = {'chinese':u'更新时间', 'cellType':BasicCell}
        d['cancelTime'] = {'chinese':u'撤销时间', 'cellType':BasicCell}
        d['frontID'] = {'chinese':u'前置编号', 'cellType':BasicCell}
        d['sessionID'] = {'chinese':u'会话编号', 'cellType':BasicCell}
        d['gatewayName'] = {'chinese':u'接口', 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setDataKey('vtOrderID')
        self.setEventType(EVENT_ORDER)
        self.setFont(BASIC_FONT)
        self.setSaveData(True)

        # add by Incense 20160728
        self.setSorting(True)

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
        d['symbol'] = {'chinese':u'合约代码', 'cellType':BasicCell}
        d['vtSymbol'] = {'chinese':u'名称', 'cellType':NameCell}
        d['direction'] = {'chinese':u'方向', 'cellType':DirectionCell}
        d['position'] = {'chinese':u'持仓量', 'cellType':BasicCell}
        d['ydPosition'] = {'chinese':u'昨持仓', 'cellType':BasicCell}
        d['frozen'] = {'chinese':u'冻结量', 'cellType':BasicCell}
        d['price'] = {'chinese':u'价格', 'cellType':BasicCell}
        d['gatewayName'] = {'chinese':u'接口', 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setDataKey('vtPositionName')
        self.setEventType(EVENT_POSITION)
        self.setFont(BASIC_FONT)
        self.setSaveData(True)

        # add by Incense 20160728
        self.setSorting(True)

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
        d['accountID'] = {'chinese':u'账户', 'cellType':BasicCell}
        d['preBalance'] = {'chinese':u'昨结', 'cellType':BasicCell}
        d['balance'] = {'chinese':u'净值', 'cellType':BasicCell}
        d['available'] = {'chinese':u'可用', 'cellType':BasicCell}
        d['commission'] = {'chinese':u'手续费', 'cellType':BasicCell}
        d['margin'] = {'chinese':u'保证金', 'cellType':BasicCell}
        d['closeProfit'] = {'chinese':u'平仓盈亏', 'cellType':BasicCell}
        d['positionProfit'] = {'chinese':u'持仓盈亏', 'cellType':BasicCell}
        d['gatewayName'] = {'chinese':u'接口', 'cellType':BasicCell}
        self.setHeaderDict(d)
        
        self.setDataKey('vtAccountID')
        self.setEventType(EVENT_ACCOUNT)
        self.setFont(BASIC_FONT)
        self.initTable()
        self.registerEvent()

########################################################################
class TradingWidget(QtGui.QFrame):
    """简单交易组件"""
    signal = QtCore.pyqtSignal(type(Event()))
    
    directionList = [DIRECTION_LONG,
                     DIRECTION_SHORT]

    offsetList = [OFFSET_OPEN,
                  OFFSET_CLOSE,
                  OFFSET_CLOSEYESTERDAY,
                  OFFSET_CLOSETODAY]
    
    priceTypeList = [PRICETYPE_LIMITPRICE,
                     PRICETYPE_MARKETPRICE,
                     PRICETYPE_FAK,
                     PRICETYPE_FOK]
    
    exchangeList = [EXCHANGE_NONE,
                    EXCHANGE_CFFEX,
                    EXCHANGE_SHFE,
                    EXCHANGE_DCE,
                    EXCHANGE_CZCE,
                    EXCHANGE_SSE,
                    EXCHANGE_SZSE,
                    EXCHANGE_SGE,
                    EXCHANGE_HKEX,
                    EXCHANGE_SMART,
                    EXCHANGE_NYMEX,
                    EXCHANGE_GLOBEX,
                    EXCHANGE_IDEALPRO]
    
    currencyList = [CURRENCY_NONE,
                    CURRENCY_CNY,
                    CURRENCY_USD]
    
    productClassList = [PRODUCT_NONE,
                        PRODUCT_EQUITY,
                        PRODUCT_FUTURES,
                        PRODUCT_OPTION,
                        PRODUCT_FOREX]
    
    gatewayList = ['']

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine, parent=None):
        """Constructor"""
        super(TradingWidget, self).__init__(parent)
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        self.symbol = ''
        
        # 添加交易接口
        self.gatewayList.extend(mainEngine.gatewayDict.keys())

        self.initUi()
        self.connectSignal()

    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'交易')
        self.setMaximumWidth(400)
        self.setFrameShape(self.Box)    # 设置边框
        self.setLineWidth(1)           

        # 左边部分
        labelSymbol = QtGui.QLabel(u'代码')
        labelName =  QtGui.QLabel(u'名称')
        labelDirection = QtGui.QLabel(u'方向类型')
        labelOffset = QtGui.QLabel(u'开平')
        labelPrice = QtGui.QLabel(u'价格')
        labelVolume = QtGui.QLabel(u'数量')
        labelPriceType = QtGui.QLabel(u'价格类型')
        labelExchange = QtGui.QLabel(u'交易所') 

        labelCurrency = QtGui.QLabel(u'货币')
        labelProductClass = QtGui.QLabel(u'产品类型')
        labelGateway = QtGui.QLabel(u'交易接口')

        #labelOrder = QtGui.QLabel(u'委托编号')

        self.lineSymbol = QtGui.QLineEdit()
        self.lineName = QtGui.QLineEdit()

        self.comboDirection = QtGui.QComboBox()
        self.comboDirection.addItems(self.directionList)

        self.comboOffset = QtGui.QComboBox()
        self.comboOffset.addItems(self.offsetList)

        self.spinPrice = QtGui.QDoubleSpinBox()
        self.spinPrice.setDecimals(4)
        self.spinPrice.setMinimum(-1000)    # 原来是0，为支持套利，改为-1000
        self.spinPrice.setMaximum(100000)

        self.spinVolume = QtGui.QSpinBox()
        self.spinVolume.setMinimum(0)
        self.spinVolume.setMaximum(1000000)

        self.comboPriceType = QtGui.QComboBox()
        self.comboPriceType.addItems(self.priceTypeList)
        
        self.comboExchange = QtGui.QComboBox()
        self.comboExchange.addItems(self.exchangeList)
        
        self.comboCurrency = QtGui.QComboBox()
        self.comboCurrency.addItems(self.currencyList)
        
        self.comboProductClass = QtGui.QComboBox()
        self.comboProductClass.addItems(self.productClassList)     
        
        self.comboGateway = QtGui.QComboBox()
        self.comboGateway.addItems(self.gatewayList)          

        #self.lineOrder = QtGui.QLineEdit()

        gridleft = QtGui.QGridLayout()
        gridleft.addWidget(labelSymbol, 0, 0)
        gridleft.addWidget(labelName, 1, 0)
        gridleft.addWidget(labelDirection, 2, 0)
        gridleft.addWidget(labelOffset, 3, 0)
        gridleft.addWidget(labelPrice, 4, 0)
        gridleft.addWidget(labelVolume, 5, 0)
        gridleft.addWidget(labelPriceType, 6, 0)
        gridleft.addWidget(labelExchange, 7, 0)

        gridleft.addWidget(labelCurrency, 8, 0)
        gridleft.addWidget(labelProductClass, 9, 0)   
        gridleft.addWidget(labelGateway, 10, 0)

        #gridleft.addWidget(labelOrder, 11, 0)


        gridleft.addWidget(self.lineSymbol, 0, 1)
        gridleft.addWidget(self.lineName, 1, 1)
        gridleft.addWidget(self.comboDirection, 2, 1)
        gridleft.addWidget(self.comboOffset, 3, 1)
        gridleft.addWidget(self.spinPrice, 4, 1)
        gridleft.addWidget(self.spinVolume, 5, 1)
        gridleft.addWidget(self.comboPriceType, 6, 1)	
        gridleft.addWidget(self.comboExchange, 7, 1)
        gridleft.addWidget(self.comboCurrency, 8, 1)	
        gridleft.addWidget(self.comboProductClass, 9, 1) 
        gridleft.addWidget(self.comboGateway, 10, 1)

        #gridleft.addWidget(self.lineOrder, 11, 1)


        # 右边部分
        labelBid1 = QtGui.QLabel(u'买一')
        labelBid2 = QtGui.QLabel(u'买二')
        labelBid3 = QtGui.QLabel(u'买三')
        labelBid4 = QtGui.QLabel(u'买四')
        labelBid5 = QtGui.QLabel(u'买五')

        labelAsk1 = QtGui.QLabel(u'卖一')
        labelAsk2 = QtGui.QLabel(u'卖二')
        labelAsk3 = QtGui.QLabel(u'卖三')
        labelAsk4 = QtGui.QLabel(u'卖四')
        labelAsk5 = QtGui.QLabel(u'卖五')

        self.labelBidPrice1 = QtGui.QLabel()
        self.labelBidPrice2 = QtGui.QLabel()
        self.labelBidPrice3 = QtGui.QLabel()
        self.labelBidPrice4 = QtGui.QLabel()
        self.labelBidPrice5 = QtGui.QLabel()
        self.labelBidVolume1 = QtGui.QLabel()
        self.labelBidVolume2 = QtGui.QLabel()
        self.labelBidVolume3 = QtGui.QLabel()
        self.labelBidVolume4 = QtGui.QLabel()
        self.labelBidVolume5 = QtGui.QLabel()	

        self.labelAskPrice1 = QtGui.QLabel()
        self.labelAskPrice2 = QtGui.QLabel()
        self.labelAskPrice3 = QtGui.QLabel()
        self.labelAskPrice4 = QtGui.QLabel()
        self.labelAskPrice5 = QtGui.QLabel()
        self.labelAskVolume1 = QtGui.QLabel()
        self.labelAskVolume2 = QtGui.QLabel()
        self.labelAskVolume3 = QtGui.QLabel()
        self.labelAskVolume4 = QtGui.QLabel()
        self.labelAskVolume5 = QtGui.QLabel()	

        labelLast = QtGui.QLabel(u'最新')
        self.labelLastPrice = QtGui.QLabel()
        self.labelReturn = QtGui.QLabel()

        self.labelLastPrice.setMinimumWidth(60)
        self.labelReturn.setMinimumWidth(60)

        gridRight = QtGui.QGridLayout()
        gridRight.addWidget(labelAsk5, 0, 0)
        gridRight.addWidget(labelAsk4, 1, 0)
        gridRight.addWidget(labelAsk3, 2, 0)
        gridRight.addWidget(labelAsk2, 3, 0)
        gridRight.addWidget(labelAsk1, 4, 0)
        gridRight.addWidget(labelLast, 5, 0)
        gridRight.addWidget(labelBid1, 6, 0)
        gridRight.addWidget(labelBid2, 7, 0)
        gridRight.addWidget(labelBid3, 8, 0)
        gridRight.addWidget(labelBid4, 9, 0)
        gridRight.addWidget(labelBid5, 10, 0)

        gridRight.addWidget(self.labelAskPrice5, 0, 1)
        gridRight.addWidget(self.labelAskPrice4, 1, 1)
        gridRight.addWidget(self.labelAskPrice3, 2, 1)
        gridRight.addWidget(self.labelAskPrice2, 3, 1)
        gridRight.addWidget(self.labelAskPrice1, 4, 1)
        gridRight.addWidget(self.labelLastPrice, 5, 1)
        gridRight.addWidget(self.labelBidPrice1, 6, 1)
        gridRight.addWidget(self.labelBidPrice2, 7, 1)
        gridRight.addWidget(self.labelBidPrice3, 8, 1)
        gridRight.addWidget(self.labelBidPrice4, 9, 1)
        gridRight.addWidget(self.labelBidPrice5, 10, 1)	

        gridRight.addWidget(self.labelAskVolume5, 0, 2)
        gridRight.addWidget(self.labelAskVolume4, 1, 2)
        gridRight.addWidget(self.labelAskVolume3, 2, 2)
        gridRight.addWidget(self.labelAskVolume2, 3, 2)
        gridRight.addWidget(self.labelAskVolume1, 4, 2)
        gridRight.addWidget(self.labelReturn, 5, 2)
        gridRight.addWidget(self.labelBidVolume1, 6, 2)
        gridRight.addWidget(self.labelBidVolume2, 7, 2)
        gridRight.addWidget(self.labelBidVolume3, 8, 2)
        gridRight.addWidget(self.labelBidVolume4, 9, 2)
        gridRight.addWidget(self.labelBidVolume5, 10, 2)

        # 发单按钮
        buttonSendOrder = QtGui.QPushButton(u'发单')
        #buttonCancel = QtGui.QPushButton(u'撤单')
        buttonCancelAll = QtGui.QPushButton(u'全撤')
        
        size = buttonSendOrder.sizeHint()
        buttonSendOrder.setMinimumHeight(size.height()*2)   # 把按钮高度设为默认两倍
        #buttonCancel.setMinimumHeight(size.height()*2)
        buttonCancelAll.setMinimumHeight(size.height()*2)

        # 整合布局
        hbox = QtGui.QHBoxLayout()
        hbox.addLayout(gridleft)
        hbox.addLayout(gridRight)

        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(buttonSendOrder)
        #vbox.addWidget(buttonCancel)
        vbox.addWidget(buttonCancelAll)
        vbox.addStretch()

        self.setLayout(vbox)

        # 关联更新
        buttonSendOrder.clicked.connect(self.sendOrder)
        #buttonCancel.clicked.connect(self.canelOrder)
        buttonCancelAll.clicked.connect(self.cancelAll)
        self.lineSymbol.returnPressed.connect(self.updateSymbol)

    #----------------------------------------------------------------------
    def updateSymbol(self):
        """合约变化"""
        # 读取组件数据
        symbol = str(self.lineSymbol.text())
        exchange = unicode(self.comboExchange.currentText())
        currency = unicode(self.comboCurrency.currentText())
        productClass = unicode(self.comboProductClass.currentText())           
        gatewayName = unicode(self.comboGateway.currentText())
        
        # 查询合约
        if exchange:
            vtSymbol = '.'.join([symbol, exchange])
            contract = self.mainEngine.getContract(vtSymbol)
        else:
            vtSymbol = symbol
            contract = self.mainEngine.getContract(symbol)   
        
        if contract:
            vtSymbol = contract.vtSymbol
            gatewayName = contract.gatewayName
            self.lineName.setText(contract.name)
            exchange = contract.exchange    # 保证有交易所代码
            
        # 清空价格数量
        self.spinPrice.setValue(0)
        self.spinVolume.setValue(0)

        # 清空行情显示
        self.labelBidPrice1.setText('')
        self.labelBidPrice2.setText('')
        self.labelBidPrice3.setText('')
        self.labelBidPrice4.setText('')
        self.labelBidPrice5.setText('')
        self.labelBidVolume1.setText('')
        self.labelBidVolume2.setText('')
        self.labelBidVolume3.setText('')
        self.labelBidVolume4.setText('')
        self.labelBidVolume5.setText('')	
        self.labelAskPrice1.setText('')
        self.labelAskPrice2.setText('')
        self.labelAskPrice3.setText('')
        self.labelAskPrice4.setText('')
        self.labelAskPrice5.setText('')
        self.labelAskVolume1.setText('')
        self.labelAskVolume2.setText('')
        self.labelAskVolume3.setText('')
        self.labelAskVolume4.setText('')
        self.labelAskVolume5.setText('')
        self.labelLastPrice.setText('')
        self.labelReturn.setText('')

        # 重新注册事件监听
        self.eventEngine.unregister(EVENT_TICK + self.symbol, self.signal.emit)
        self.eventEngine.register(EVENT_TICK + vtSymbol, self.signal.emit)

        # 订阅合约
        req = VtSubscribeReq()
        req.symbol = symbol
        req.exchange = exchange
        req.currency = currency
        req.productClass = productClass
        
        self.mainEngine.subscribe(req, gatewayName)

        # 更新组件当前交易的合约
        self.symbol = vtSymbol

    #----------------------------------------------------------------------
    def updateTick(self, event):
        """更新行情"""
        tick = event.dict_['data']

        if tick.vtSymbol == self.symbol:
            self.labelBidPrice1.setText(str(tick.bidPrice1))
            self.labelAskPrice1.setText(str(tick.askPrice1))
            self.labelBidVolume1.setText(str(tick.bidVolume1))
            self.labelAskVolume1.setText(str(tick.askVolume1))
            
            if tick.bidPrice2:
                self.labelBidPrice2.setText(str(tick.bidPrice2))
                self.labelBidPrice3.setText(str(tick.bidPrice3))
                self.labelBidPrice4.setText(str(tick.bidPrice4))
                self.labelBidPrice5.setText(str(tick.bidPrice5))
    
                self.labelAskPrice2.setText(str(tick.askPrice2))
                self.labelAskPrice3.setText(str(tick.askPrice3))
                self.labelAskPrice4.setText(str(tick.askPrice4))
                self.labelAskPrice5.setText(str(tick.askPrice5))
    
                self.labelBidVolume2.setText(str(tick.bidVolume2))
                self.labelBidVolume3.setText(str(tick.bidVolume3))
                self.labelBidVolume4.setText(str(tick.bidVolume4))
                self.labelBidVolume5.setText(str(tick.bidVolume5))
                
                self.labelAskVolume2.setText(str(tick.askVolume2))
                self.labelAskVolume3.setText(str(tick.askVolume3))
                self.labelAskVolume4.setText(str(tick.askVolume4))
                self.labelAskVolume5.setText(str(tick.askVolume5))	

            self.labelLastPrice.setText(str(tick.lastPrice))
            
            if tick.preClosePrice:
                rt = (tick.lastPrice/tick.preClosePrice)-1
                self.labelReturn.setText(('%.2f' %(rt*100))+'%')
            else:
                self.labelReturn.setText('')

    #----------------------------------------------------------------------
    def connectSignal(self):
        """连接Signal"""
        self.signal.connect(self.updateTick)

    #----------------------------------------------------------------------
    def sendOrder(self):
        """发单"""
        symbol = str(self.lineSymbol.text())
        exchange = unicode(self.comboExchange.currentText())
        currency = unicode(self.comboCurrency.currentText())
        productClass = unicode(self.comboProductClass.currentText())           
        gatewayName = unicode(self.comboGateway.currentText())        

        # 查询合约
        if exchange:
            vtSymbol = '.'.join([symbol, exchange])
            contract = self.mainEngine.getContract(vtSymbol)
        else:
            vtSymbol = symbol
            contract = self.mainEngine.getContract(symbol)
        
        if contract:
            if not gatewayName:
                gatewayName = contract.gatewayName
            exchange = contract.exchange    # 保证有交易所代码
            
        req = VtOrderReq()
        req.symbol = symbol
        req.exchange = exchange
        req.price = self.spinPrice.value()
        req.volume = self.spinVolume.value()
        req.direction = unicode(self.comboDirection.currentText())
        req.priceType = unicode(self.comboPriceType.currentText())
        req.offset = unicode(self.comboOffset.currentText())
        req.currency = currency
        req.productClass = productClass
        
        self.mainEngine.sendOrder(req, gatewayName)

    def canelOrder(self):
        """撤单"""
        orderRef = str(self.lineOrder.text())

        l = self.mainEngine.getAllWorkingOrders()
        for order in l:
            if order.orderID == orderRef:
                req = VtCancelOrderReq()
                req.symbol = order.symbol
                req.exchange = order.exchange
                req.frontID = order.frontID
                req.sessionID = order.sessionID
                req.orderID = order.orderID
                self.mainEngine.cancelOrder(req, order.gatewayName)


    # ----------------------------------------------------------------------
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
            
    #----------------------------------------------------------------------
    def closePosition(self, cell):
        """根据持仓信息自动填写交易组件"""
        # 读取持仓数据，cell是一个表格中的单元格对象
        pos = cell.data
        symbol = pos.symbol
        
        # 更新交易组件的显示合约
        self.lineSymbol.setText(symbol)
        self.updateSymbol()
        
        # 自动填写信息
        self.comboPriceType.setCurrentIndex(self.priceTypeList.index(PRICETYPE_LIMITPRICE))
        self.comboOffset.setCurrentIndex(self.offsetList.index(OFFSET_CLOSE))
        self.spinVolume.setValue(pos.position)

        if pos.direction == DIRECTION_LONG or pos.direction == DIRECTION_NET:
            self.comboDirection.setCurrentIndex(self.directionList.index(DIRECTION_SHORT))
        else:
            self.comboDirection.setCurrentIndex(self.directionList.index(DIRECTION_LONG))

        # 价格留待更新后由用户输入，防止有误操作


########################################################################
class ContractMonitor(BasicMonitor):
    """合约查询"""

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, parent=None):
        """Constructor"""
        super(ContractMonitor, self).__init__(parent=parent)
        
        self.mainEngine = mainEngine
        
        d = OrderedDict()
        d['symbol'] = {'chinese':u'合约代码', 'cellType':BasicCell}
        d['exchange'] = {'chinese':u'交易所', 'cellType':BasicCell}
        d['vtSymbol'] = {'chinese':u'vt系统代码', 'cellType':BasicCell}
        d['name'] = {'chinese':u'名称', 'cellType':BasicCell}
        d['productClass'] = {'chinese':u'合约类型', 'cellType':BasicCell}
        d['size'] = {'chinese':u'大小', 'cellType':BasicCell}
        d['priceTick'] = {'chinese':u'最小价格变动', 'cellType':BasicCell}
        #d['strikePrice'] = {'chinese':u'期权行权价', 'cellType':BasicCell}
        #d['underlyingSymbol'] = {'chinese':u'期权标的物', 'cellType':BasicCell}
        #d['optionType'] = {'chinese':u'期权类型', 'cellType':BasicCell}     
        self.setHeaderDict(d)
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'合约查询')
        self.setMinimumSize(800, 800)
        self.setFont(BASIC_FONT)
        self.initTable()
        self.addMenuAction()
    
    #----------------------------------------------------------------------
    def showAllContracts(self):
        """显示所有合约数据"""
        l = self.mainEngine.getAllContracts()
        d = {'.'.join([contract.exchange, contract.symbol]):contract for contract in l}
        l2 = d.keys()
        l2.sort(reverse=True)

        self.setRowCount(len(l2))
        row = 0
        
        for key in l2:
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
        refreshAction = QtGui.QAction(u'刷新', self)
        refreshAction.triggered.connect(self.refresh)
        
        self.menu.addAction(refreshAction)
    
    #----------------------------------------------------------------------
    def show(self):
        """显示"""
        super(ContractMonitor, self).show()
        self.refresh()
    
    
