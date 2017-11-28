# encoding: UTF-8

from vtConstant import DIRECTION_LONG, DIRECTION_SHORT, OFFSET_OPEN, OFFSET_CLOSE, PRICETYPE_LIMITPRICE
from vtGateway import VtOrderReq
from eventType import *
from eventEngine import Event
from uiBasicWidget import OrderMonitor, PositionMonitor
from uiOmBase import *



########################################################################
class ChainMonitor(QtGui.QTableWidget):
    """期权链监控"""
    headers = [
        u'代码',
        u'买价',
        u'买量',
        u'买隐波',
        u'卖价',
        u'卖量',
        u'卖隐波',
        u'净仓',
        u'行权价',
        u'净仓',
        u'买价',
        u'买量',
        u'买隐波',
        u'卖价',
        u'卖量',
        u'卖隐波',
        u'代码'
    ]
    
    signalTick = QtCore.pyqtSignal(type(Event()))
    signalPos = QtCore.pyqtSignal(type(Event()))
    signalTrade = QtCore.pyqtSignal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, chain, eventEngine, parent=None):
        """Constructor"""
        super(ChainMonitor, self).__init__(parent)
        
        self.chain = chain
        self.eventEngine = eventEngine
        
        # 保存代码和持仓的字典
        self.bidPriceDict = {}
        self.bidVolumeDict = {}
        self.bidImpvDict = {}
        self.askPriceDict = {}
        self.askVolumeDict = {}
        self.askImpvDict = {}
        self.posDict = {}
        
        # 初始化
        self.initUi()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        chain = self.chain
        
        # 初始化表格
        self.setColumnCount(len(self.headers))
        self.setHorizontalHeaderLabels(self.headers)
        self.setRowCount(len(chain.strikeList) + 2)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
        
        for i in range(self.columnCount()):
            self.horizontalHeader().setResizeMode(i, QtGui.QHeaderView.Stretch)
        self.horizontalHeader().setResizeMode(0, QtGui.QHeaderView.ResizeToContents)
        self.horizontalHeader().setResizeMode(self.columnCount()-1, QtGui.QHeaderView.ResizeToContents)
        
        # 初始期货化单元格
        underlying = chain.underlying
        symbol = underlying.symbol
        
        cellSymbol = OmCell(symbol, COLOR_SYMBOL, COLOR_BLACK)
        cellBidPrice = OmCell(str(underlying.bidPrice1), COLOR_BID, COLOR_BLACK)
        cellBidVolume = OmCell(str(underlying.bidVolume1), COLOR_BID, COLOR_BLACK)
        cellAskPrice = OmCell(str(underlying.askPrice1), COLOR_ASK, COLOR_BLACK)
        cellAskVolume = OmCell(str(underlying.askVolume1), COLOR_ASK, COLOR_BLACK)
        
        cellBidPrice.data = underlying
        cellBidVolume.data = underlying
        cellAskPrice.data = underlying
        cellAskVolume.data = underlying      
        
        self.setItem(0, 0, cellSymbol)
        self.setItem(0, 1, cellBidPrice)
        self.setItem(0, 2, cellBidVolume)
        self.setItem(0, 4, cellAskPrice)
        self.setItem(0, 5, cellAskVolume)
        
        self.bidPriceDict[symbol] = cellBidPrice
        self.bidVolumeDict[symbol] = cellBidVolume
        self.askPriceDict[symbol] = cellAskPrice
        self.askVolumeDict[symbol] = cellAskVolume
        
        # 初始化call单元格
        for n, option in enumerate(chain.callList):
            row = n + 2
            
            cellSymbol = OmCell(option.symbol, COLOR_SYMBOL, COLOR_BLACK)
            cellBidPrice = OmCell(str(option.bidPrice1), COLOR_BID, COLOR_BLACK)
            cellBidVolume = OmCell(str(option.bidVolume1), COLOR_BID, COLOR_BLACK)
            cellBidImpv = OmCell('%.1f' %(option.bidImpv*100), COLOR_BID, COLOR_BLACK)
            cellAskPrice = OmCell(str(option.askPrice1), COLOR_ASK, COLOR_BLACK)
            cellAskVolume = OmCell(str(option.askVolume1), COLOR_ASK, COLOR_BLACK)
            cellAskImpv = OmCell('%.1f' %(option.askImpv*100), COLOR_ASK, COLOR_BLACK)
            cellPos = OmCell(str(option.netPos), COLOR_POS, COLOR_BLACK)
            cellStrike = OmCell(str(option.strike), COLOR_STRIKE)
            
            cellBidPrice.data = option
            cellBidVolume.data = option
            cellBidImpv.data = option
            cellAskPrice.data = option
            cellAskVolume.data = option
            cellAskImpv.data = option
            
            self.setItem(row, 0, cellSymbol)
            self.setItem(row, 1, cellBidPrice)
            self.setItem(row, 2, cellBidVolume)
            self.setItem(row, 3, cellBidImpv)
            self.setItem(row, 4, cellAskPrice)
            self.setItem(row, 5, cellAskVolume)
            self.setItem(row, 6, cellAskImpv)
            self.setItem(row, 7, cellPos)
            self.setItem(row, 8, cellStrike)
            
            self.bidPriceDict[option.symbol] = cellBidPrice
            self.bidVolumeDict[option.symbol] = cellBidVolume
            self.bidImpvDict[option.symbol] = cellBidImpv
            self.askPriceDict[option.symbol] = cellAskPrice
            self.askVolumeDict[option.symbol] = cellAskVolume            
            self.askImpvDict[option.symbol] = cellAskImpv
            self.posDict[option.symbol] = cellPos
        
        # 初始化put单元格
        for n, option in enumerate(chain.putList):
            row = n + 2
            
            cellSymbol = OmCell(option.symbol, COLOR_SYMBOL, COLOR_BLACK)
            cellBidPrice = OmCell(str(option.bidPrice1), COLOR_BID, COLOR_BLACK)
            cellBidVolume = OmCell(str(option.bidVolume1), COLOR_BID, COLOR_BLACK)
            cellBidImpv = OmCell('%.1f' %(option.bidImpv*100), COLOR_BID, COLOR_BLACK)
            cellAskPrice = OmCell(str(option.askPrice1), COLOR_ASK, COLOR_BLACK)
            cellAskVolume = OmCell(str(option.askVolume1), COLOR_ASK, COLOR_BLACK)
            cellAskImpv = OmCell('%.1f' %(option.askImpv*100), COLOR_ASK, COLOR_BLACK)
            cellPos = OmCell(str(option.netPos), COLOR_POS, COLOR_BLACK)
            cellStrike = OmCell(str(option.strike))
            
            cellBidPrice.data = option
            cellBidVolume.data = option
            cellBidImpv.data = option
            cellAskPrice.data = option
            cellAskVolume.data = option
            cellAskImpv.data = option            
            
            self.setItem(row, 9, cellPos)
            self.setItem(row, 10, cellBidPrice)
            self.setItem(row, 11, cellBidVolume)
            self.setItem(row, 12, cellBidImpv)
            self.setItem(row, 13, cellAskPrice)
            self.setItem(row, 14, cellAskVolume)
            self.setItem(row, 15, cellAskImpv)
            self.setItem(row, 16, cellSymbol)
            
            self.bidPriceDict[option.symbol] = cellBidPrice
            self.bidVolumeDict[option.symbol] = cellBidVolume
            self.bidImpvDict[option.symbol] = cellBidImpv
            self.askPriceDict[option.symbol] = cellAskPrice
            self.askVolumeDict[option.symbol] = cellAskVolume            
            self.askImpvDict[option.symbol] = cellAskImpv
            self.posDict[option.symbol] = cellPos    
            
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signalTick.connect(self.updateTick)
        self.signalPos.connect(self.updatePos)
        self.signalTrade.connect(self.updateTrade)
        
        self.eventEngine.register(EVENT_TICK + self.chain.underlying.vtSymbol, self.signalTick.emit)
        
        for option in self.chain.optionList:
            self.eventEngine.register(EVENT_TICK + option.vtSymbol, self.signalTick.emit)
            self.eventEngine.register(EVENT_TRADE + option.vtSymbol, self.signalTrade.emit)
            self.eventEngine.register(EVENT_POSITION + option.vtSymbol, self.signalPos.emit)
    
    #----------------------------------------------------------------------
    def updateTick(self, event):
        """行情更新"""
        tick = event.dict_['data']
        symbol = tick.symbol
        
        if symbol in self.chain.optionDict:
            contract = self.chain.optionDict[symbol]
            self.bidImpvDict[symbol].setText('%.1f' %(contract.bidImpv*100))
            self.askImpvDict[symbol].setText('%.1f' %(contract.askImpv*100))
        else:
            contract = self.chain.underlying
        
        self.bidPriceDict[symbol].setText(str(contract.bidPrice1))
        self.bidVolumeDict[symbol].setText(str(contract.bidVolume1))
        self.askPriceDict[symbol].setText(str(contract.askPrice1))
        self.askVolumeDict[symbol].setText(str(contract.askVolume1))
    
    #----------------------------------------------------------------------
    def updatePos(self, event):
        """持仓更新"""
        pos = event.dict_['data']
        option = self.chain.optionDict[pos.symbol]
        self.posDict[option.symbol].setText(str(option.netPos))
        
    #----------------------------------------------------------------------
    def updateTrade(self, event):
        """成交更新"""
        trade = event.dict_['data']
        option = self.chain.optionDict[trade.symbol]
        self.posDict[option.symbol].setText(str(option.netPos))


########################################################################
class TradingWidget(QtGui.QWidget):
    """交易组件"""

    #----------------------------------------------------------------------
    def __init__(self, omEngine, parent=None):
        """Constructor"""
        super(TradingWidget, self).__init__(parent)
        
        self.omEngine = omEngine
        self.mainEngine = omEngine.mainEngine
        self.portfolio = omEngine.portfolio
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setFixedWidth(200)
        
        labelTradingWidget = QtGui.QLabel(u'期权交易')
        labelSymbol = QtGui.QLabel(u'代码')
        labelDirection = QtGui.QLabel(u'方向')
        labelPrice = QtGui.QLabel(u'价格')
        labelVolume = QtGui.QLabel(u'数量')
        
        self.lineSymbol = QtGui.QLineEdit()
        self.comboDirection = QtGui.QComboBox()
        self.comboDirection.addItems([DIRECTION_LONG, DIRECTION_SHORT])
        self.linePrice = QtGui.QLineEdit()
        self.lineVolume = QtGui.QLineEdit()
        self.buttonSendOrder = QtGui.QPushButton(u'发单')
        self.buttonSendOrder.clicked.connect(self.sendOrder)
        
        grid = QtGui.QGridLayout()
        grid.addWidget(labelTradingWidget, 0, 0, 1, 2)
        grid.addWidget(labelSymbol, 1, 0)
        grid.addWidget(labelDirection, 2, 0)
        grid.addWidget(labelPrice, 3, 0)
        grid.addWidget(labelVolume, 4, 0)
        grid.addWidget(self.lineSymbol, 1, 1)
        grid.addWidget(self.comboDirection, 2, 1)
        grid.addWidget(self.linePrice, 3, 1)
        grid.addWidget(self.lineVolume, 4, 1)
        grid.addWidget(self.buttonSendOrder, 5, 0, 1, 2)
        self.setLayout(grid)

    #----------------------------------------------------------------------
    def sendOrder(self):
        """发送委托"""
        try:
            symbol = str(self.lineSymbol.text())
            direction = str(self.comboDirection.currentText())
            price = float(self.linePrice.text())
            volume = int(self.lineVolume.text())
        except:
            return
        
        contract = self.portfolio.contractDict.get(symbol, None)
        if not contract:
            return
        
        # 做多
        if direction == DIRECTION_LONG:
            # 如果空头仓位大于等于买入量，则只需平
            if contract.shortPos >= volume:
                self.fastTrade(symbol, DIRECTION_LONG, OFFSET_CLOSE, price, volume)
            # 否则先平后开
            else:
                openVolume = volume - contract.shortPos
                if contract.shortPos:
                    self.fastTrade(symbol, DIRECTION_LONG, OFFSET_CLOSE, price, contract.shortPos)
                self.fastTrade(symbol, DIRECTION_LONG, OFFSET_OPEN, price, openVolume)
        # 做空
        else:
            if contract.longPos >= volume:
                self.fastTrade(symbol, DIRECTION_SHORT, OFFSET_CLOSE, price, volume)
            else:
                openVolume = volume - contract.longPos
                if contract.longPos:
                    self.fastTrade(symbol, DIRECTION_SHORT, OFFSET_CLOSE, price, contract.longPos)
                self.fastTrade(symbol ,DIRECTION_SHORT, OFFSET_OPEN, price, openVolume)
    
    #----------------------------------------------------------------------
    def fastTrade(self, symbol, direction, offset, price, volume):
        """封装下单函数"""
        contract = self.mainEngine.getContract(symbol)
        if not contract:
            return
        
        req = VtOrderReq()
        req.symbol = symbol
        req.exchange = contract.exchange
        req.direction = direction
        req.offset = offset
        req.price = price
        req.volume = volume
        req.priceType = PRICETYPE_LIMITPRICE
        self.omEngine.sendOrder(req, contract.gatewayName)
    
    #----------------------------------------------------------------------
    def updateWidget(self, item):
        """双击监控组件单元格后自动更新组件"""
        contract = item.data
        if not contract:
            return
        
        self.lineSymbol.setText(contract.symbol)
        
        # short
        if item.background is COLOR_BID:
            self.comboDirection.setCurrentIndex(1)
            self.linePrice.setText(str(contract.bidPrice1))
            self.lineVolume.setText(str(contract.bidVolume1))
        # long
        elif item.background is COLOR_ASK:
            self.comboDirection.setCurrentIndex(0)
            self.linePrice.setText(str(contract.askPrice1))
            self.lineVolume.setText(str(contract.askVolume1))



########################################################################
class ManualTrader(QtGui.QWidget):
    """手动交易组件"""

    #----------------------------------------------------------------------
    def __init__(self, omEngine, parent=None):
        """Constructor"""
        super(ManualTrader, self).__init__(parent)
        
        self.omEngine = omEngine
        self.mainEngine = omEngine.mainEngine
        self.eventEngine = omEngine.eventEngine
        self.portfolio = omEngine.portfolio
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'期权手动交易')
        
        posMonitor = PositionMonitor(self.mainEngine, self.eventEngine)
        for i in range(posMonitor.columnCount()):
            posMonitor.horizontalHeader().setResizeMode(QtGui.QHeaderView.Stretch)
        posMonitor.setSorting(False)
        
        orderMonitor = OrderMonitor(self.mainEngine, self.eventEngine)
        for i in range(orderMonitor.columnCount()):
            orderMonitor.horizontalHeader().setResizeMode(QtGui.QHeaderView.Stretch)
        orderMonitor.setSorting(False)
            
        tradingWidget = TradingWidget(self.omEngine)
        
        tab = QtGui.QTabWidget()
        for chain in self.portfolio.chainList:
            chainMonitor = ChainMonitor(chain, self.eventEngine)
            tab.addTab(chainMonitor, chain.symbol)
            chainMonitor.itemDoubleClicked.connect(tradingWidget.updateWidget)

        
        vbox1 = QtGui.QVBoxLayout()
        vbox1.addWidget(orderMonitor)
        vbox1.addWidget(posMonitor)
        
        vbox2 = QtGui.QVBoxLayout()
        vbox2.addWidget(tradingWidget)
        vbox2.addStretch()
        
        hbox = QtGui.QHBoxLayout()
        hbox.addLayout(vbox1)
        hbox.addLayout(vbox2)
        
        vbox3 = QtGui.QVBoxLayout()
        vbox3.addWidget(tab)
        vbox3.addLayout(hbox)
        
        self.setLayout(vbox3)
    
    