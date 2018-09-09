# encoding: UTF-8

from __future__ import absolute_import
from vnpy.event import Event

from vnpy.trader.vtConstant import DIRECTION_LONG, DIRECTION_SHORT, OFFSET_OPEN, OFFSET_CLOSE, PRICETYPE_LIMITPRICE
from vnpy.trader.vtObject import VtOrderReq
from vnpy.trader.vtEvent import EVENT_TICK, EVENT_TRADE
from vnpy.trader.uiBasicWidget import WorkingOrderMonitor, PositionMonitor

from .uiOmBase import *



########################################################################
class ChainMonitor(QtWidgets.QTableWidget):
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
    def __init__(self, omEngine, eventEngine, parent=None):
        """Constructor"""
        super(ChainMonitor, self).__init__(parent)
        
        self.omEngine = omEngine
        self.eventEngine = eventEngine
        
        # 保存代码和持仓的字典
        self.bidPriceDict = {}
        self.bidVolumeDict = {}
        self.bidImpvDict = {}
        self.askPriceDict = {}
        self.askVolumeDict = {}
        self.askImpvDict = {}
        self.posDict = {}
        
        # 保存期权对象的字典
        portfolio = omEngine.portfolio
        
        self.instrumentDict = {}
        self.instrumentDict.update(portfolio.optionDict)
        self.instrumentDict.update(portfolio.underlyingDict)
        
        # 初始化
        self.initUi()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        portfolio = self.omEngine.portfolio
        
        # 初始化表格
        self.setColumnCount(len(self.headers))
        self.setHorizontalHeaderLabels(self.headers)

        rowCount = 0
        rowCount += len(portfolio.underlyingDict)
        rowCount += len(portfolio.chainDict)
        for chain in portfolio.chainDict.values():
            rowCount += len(chain.callDict)
        self.setRowCount(rowCount)
        
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
        
        for i in range(self.columnCount()):
            self.horizontalHeader().setResizeMode(i, QtWidgets.QHeaderView.Stretch)
        self.horizontalHeader().setResizeMode(0, QtWidgets.QHeaderView.ResizeToContents)
        self.horizontalHeader().setResizeMode(self.columnCount()-1, QtWidgets.QHeaderView.ResizeToContents)
        
        # 初始化标的单元格
        row = 0
        
        for underlying in portfolio.underlyingDict.values():
            symbol = underlying.symbol
            
            cellSymbol = OmCell(symbol, COLOR_SYMBOL, COLOR_BLACK, underlying)
            cellBidPrice = OmCell(str(underlying.bidPrice1), COLOR_BID, COLOR_BLACK, underlying)
            cellBidVolume = OmCell(str(underlying.bidVolume1), COLOR_BID, COLOR_BLACK, underlying)
            cellAskPrice = OmCell(str(underlying.askPrice1), COLOR_ASK, COLOR_BLACK, underlying)
            cellAskVolume = OmCell(str(underlying.askVolume1), COLOR_ASK, COLOR_BLACK, underlying)
            cellPos = OmCell(str(underlying.netPos), COLOR_POS, COLOR_BLACK, underlying)
            
            self.setItem(row, 0, cellSymbol)
            self.setItem(row, 1, cellBidPrice)
            self.setItem(row, 2, cellBidVolume)
            self.setItem(row, 4, cellAskPrice)
            self.setItem(row, 5, cellAskVolume)
            self.setItem(row, 7, cellPos)
            
            self.bidPriceDict[symbol] = cellBidPrice
            self.bidVolumeDict[symbol] = cellBidVolume
            self.askPriceDict[symbol] = cellAskPrice
            self.askVolumeDict[symbol] = cellAskVolume
            self.posDict[symbol] = cellPos
            
            row += 1
            
        row += 1
            
        # 初始化期权单元格
        for chain in portfolio.chainDict.values():
            
            # call
            callRow = row
            
            for option in chain.callDict.values():    
                cellSymbol = OmCell(option.symbol, COLOR_SYMBOL, COLOR_BLACK, option)
                cellBidPrice = OmCell(str(option.bidPrice1), COLOR_BID, COLOR_BLACK, option)
                cellBidVolume = OmCell(str(option.bidVolume1), COLOR_BID, COLOR_BLACK, option)
                cellBidImpv = OmCell('%.1f' %(option.bidImpv*100), COLOR_BID, COLOR_BLACK, option)
                cellAskPrice = OmCell(str(option.askPrice1), COLOR_ASK, COLOR_BLACK, option)
                cellAskVolume = OmCell(str(option.askVolume1), COLOR_ASK, COLOR_BLACK, option)
                cellAskImpv = OmCell('%.1f' %(option.askImpv*100), COLOR_ASK, COLOR_BLACK, option)
                cellPos = OmCell(str(option.netPos), COLOR_POS, COLOR_BLACK, option)
                cellStrike = OmCell(str(option.k), COLOR_STRIKE)
                
                self.setItem(callRow, 0, cellSymbol)
                self.setItem(callRow, 1, cellBidPrice)
                self.setItem(callRow, 2, cellBidVolume)
                self.setItem(callRow, 3, cellBidImpv)
                self.setItem(callRow, 4, cellAskPrice)
                self.setItem(callRow, 5, cellAskVolume)
                self.setItem(callRow, 6, cellAskImpv)
                self.setItem(callRow, 7, cellPos)
                self.setItem(callRow, 8, cellStrike)
                
                self.bidPriceDict[option.symbol] = cellBidPrice
                self.bidVolumeDict[option.symbol] = cellBidVolume
                self.bidImpvDict[option.symbol] = cellBidImpv
                self.askPriceDict[option.symbol] = cellAskPrice
                self.askVolumeDict[option.symbol] = cellAskVolume            
                self.askImpvDict[option.symbol] = cellAskImpv
                self.posDict[option.symbol] = cellPos
                
                callRow += 1
            
            # put
            putRow = row
            
            for option in chain.putDict.values():
                cellSymbol = OmCell(option.symbol, COLOR_SYMBOL, COLOR_BLACK, option)
                cellBidPrice = OmCell(str(option.bidPrice1), COLOR_BID, COLOR_BLACK, option)
                cellBidVolume = OmCell(str(option.bidVolume1), COLOR_BID, COLOR_BLACK, option)
                cellBidImpv = OmCell('%.1f' %(option.bidImpv*100), COLOR_BID, COLOR_BLACK, option)
                cellAskPrice = OmCell(str(option.askPrice1), COLOR_ASK, COLOR_BLACK, option)
                cellAskVolume = OmCell(str(option.askVolume1), COLOR_ASK, COLOR_BLACK, option)
                cellAskImpv = OmCell('%.1f' %(option.askImpv*100), COLOR_ASK, COLOR_BLACK, option)
                cellPos = OmCell(str(option.netPos), COLOR_POS, COLOR_BLACK, option)
                
                self.setItem(putRow, 9, cellPos)
                self.setItem(putRow, 10, cellBidPrice)
                self.setItem(putRow, 11, cellBidVolume)
                self.setItem(putRow, 12, cellBidImpv)
                self.setItem(putRow, 13, cellAskPrice)
                self.setItem(putRow, 14, cellAskVolume)
                self.setItem(putRow, 15, cellAskImpv)
                self.setItem(putRow, 16, cellSymbol)
                
                self.bidPriceDict[option.symbol] = cellBidPrice
                self.bidVolumeDict[option.symbol] = cellBidVolume
                self.bidImpvDict[option.symbol] = cellBidImpv
                self.askPriceDict[option.symbol] = cellAskPrice
                self.askVolumeDict[option.symbol] = cellAskVolume            
                self.askImpvDict[option.symbol] = cellAskImpv
                self.posDict[option.symbol] = cellPos  
                
                putRow += 1
            
            row = putRow + 1
            
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signalTick.connect(self.processTickEvent)
        self.signalTrade.connect(self.processTradeEvent)
        
        portfolio = self.omEngine.portfolio
        
        for underlying in portfolio.underlyingDict.values():
            self.eventEngine.register(EVENT_TICK + underlying.vtSymbol, self.signalTick.emit)
            self.eventEngine.register(EVENT_TRADE + underlying.vtSymbol, self.signalTrade.emit)
        
        for chain in portfolio.chainDict.values():
            for option in chain.optionDict.values():
                self.eventEngine.register(EVENT_TICK + option.vtSymbol, self.signalTick.emit)
                self.eventEngine.register(EVENT_TRADE + option.vtSymbol, self.signalTrade.emit)
    
    #----------------------------------------------------------------------
    def processTickEvent(self, event):
        """行情更新"""
        tick = event.dict_['data']
        symbol = tick.symbol
        
        if symbol in self.bidImpvDict:
            option = self.instrumentDict[symbol]
            self.bidImpvDict[symbol].setText('%.1f' %(option.bidImpv*100))
            self.askImpvDict[symbol].setText('%.1f' %(option.askImpv*100))
        
        self.bidPriceDict[symbol].setText(str(tick.bidPrice1))
        self.bidVolumeDict[symbol].setText(str(tick.bidVolume1))
        self.askPriceDict[symbol].setText(str(tick.askPrice1))
        self.askVolumeDict[symbol].setText(str(tick.askVolume1))
    
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """成交更新"""
        trade = event.dict_['data']
        
        symbol = trade.symbol
        instrument = self.instrumentDict[symbol]
        self.posDict[symbol].setText(str(instrument.netPos))


########################################################################
class TradingWidget(QtWidgets.QWidget):
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
        
        labelTradingWidget = QtWidgets.QLabel(u'期权交易')
        labelSymbol = QtWidgets.QLabel(u'代码')
        labelDirection = QtWidgets.QLabel(u'方向')
        labelPrice = QtWidgets.QLabel(u'价格')
        labelVolume = QtWidgets.QLabel(u'数量')
        
        self.lineSymbol = QtWidgets.QLineEdit()
        self.comboDirection = QtWidgets.QComboBox()
        self.comboDirection.addItems([DIRECTION_LONG, DIRECTION_SHORT])
        self.linePrice = QtWidgets.QLineEdit()
        self.lineVolume = QtWidgets.QLineEdit()
        self.buttonSendOrder = QtWidgets.QPushButton(u'发单')
        self.buttonSendOrder.clicked.connect(self.sendOrder)
        
        grid = QtWidgets.QGridLayout()
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
        
        instrument = self.portfolio.instrumentDict.get(symbol, None)
        if not instrument:
            return
        
        # 做多
        if direction == DIRECTION_LONG:
            # 如果空头仓位大于等于买入量，则只需平
            if instrument.shortPos >= volume:
                self.fastTrade(symbol, DIRECTION_LONG, OFFSET_CLOSE, price, volume)
            # 否则先平后开
            else:
                openVolume = volume - instrument.shortPos
                if instrument.shortPos:
                    self.fastTrade(symbol, DIRECTION_LONG, OFFSET_CLOSE, price, instrument.shortPos)
                self.fastTrade(symbol, DIRECTION_LONG, OFFSET_OPEN, price, openVolume)
        # 做空
        else:
            if instrument.longPos >= volume:
                self.fastTrade(symbol, DIRECTION_SHORT, OFFSET_CLOSE, price, volume)
            else:
                openVolume = volume - instrument.longPos
                if instrument.longPos:
                    self.fastTrade(symbol, DIRECTION_SHORT, OFFSET_CLOSE, price, instrument.longPos)
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
        self.mainEngine.sendOrder(req, contract.gatewayName)
    
    #----------------------------------------------------------------------
    def updateWidget(self, item):
        """双击监控组件单元格后自动更新组件"""
        instrument = item.data
        if not instrument:
            return
        
        self.lineSymbol.setText(instrument.symbol)
        
        # short
        if item.background is COLOR_BID:
            self.comboDirection.setCurrentIndex(1)
            self.linePrice.setText(str(instrument.bidPrice1))
            self.lineVolume.setText(str(instrument.bidVolume1))
        # long
        elif item.background is COLOR_ASK:
            self.comboDirection.setCurrentIndex(0)
            self.linePrice.setText(str(instrument.askPrice1))
            self.lineVolume.setText(str(instrument.askVolume1))


########################################################################
class ManualTrader(QtWidgets.QWidget):
    """手动交易组件"""

    #----------------------------------------------------------------------
    def __init__(self, omEngine, parent=None):
        """Constructor"""
        super(ManualTrader, self).__init__(parent)
        
        self.omEngine = omEngine
        self.mainEngine = omEngine.mainEngine
        self.eventEngine = omEngine.eventEngine
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'手动交易')
        
        posMonitor = PositionMonitor(self.mainEngine, self.eventEngine)
        for i in range(posMonitor.columnCount()):
            posMonitor.horizontalHeader().setResizeMode(QtWidgets.QHeaderView.Stretch)
        posMonitor.setSorting(False)
        
        orderMonitor = WorkingOrderMonitor(self.mainEngine, self.eventEngine)
        for i in range(orderMonitor.columnCount()):
            orderMonitor.horizontalHeader().setResizeMode(QtWidgets.QHeaderView.Stretch)
        orderMonitor.setSorting(False)
            
        tradingWidget = TradingWidget(self.omEngine)
        
        chainMonitor = ChainMonitor(self.omEngine, self.eventEngine)
        chainMonitor.itemDoubleClicked.connect(tradingWidget.updateWidget)
        
        vbox1 = QtWidgets.QVBoxLayout()
        vbox1.addWidget(orderMonitor)
        vbox1.addWidget(posMonitor)
        
        vbox2 = QtWidgets.QVBoxLayout()
        vbox2.addWidget(tradingWidget)
        vbox2.addStretch()
        
        hbox = QtWidgets.QHBoxLayout()
        hbox.addLayout(vbox1)
        hbox.addLayout(vbox2)
        
        vbox3 = QtWidgets.QVBoxLayout()
        vbox3.addWidget(chainMonitor)
        vbox3.addLayout(hbox)
        
        self.setLayout(vbox3)
    
    