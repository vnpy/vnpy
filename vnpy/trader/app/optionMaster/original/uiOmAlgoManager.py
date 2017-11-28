# encoding: UTF-8

from __future__ import division

from eventType import *
from eventEngine import Event
from vtConstant import *
from omAlgo import MmEeAlgo
from uiOmBase import *


########################################################################
class PriceSpreadSpin(QtGui.QDoubleSpinBox):
    """价格价差设置"""

    #----------------------------------------------------------------------
    def __init__(self, algo):
        """Constructor"""
        super(PriceSpreadSpin, self).__init__()        
        self.algo = algo
        
        self.setDecimals(1)
        self.setMinimum(0)
        self.setMaximum(1000)
        
        self.updateData()
        self.valueChanged.connect(algo.setPriceSpread)
        
    #----------------------------------------------------------------------
    def updateData(self):
        """"""
        self.setValue(self.algo.priceSpread)


########################################################################
class ImpvSpreadSpin(QtGui.QDoubleSpinBox):
    """波动率价差设置"""

    #----------------------------------------------------------------------
    def __init__(self, algo):
        """Constructor"""
        super(ImpvSpreadSpin, self).__init__()
        self.algo = algo
        
        self.setDecimals(1)
        self.setMinimum(0)
        self.setMaximum(50)
        
        self.updateData()
        self.valueChanged.connect(self.setImpvSpread)
    
    #----------------------------------------------------------------------
    def updateData(self):
        """"""
        self.setValue(self.algo.impvSpread * 100)
        
    #----------------------------------------------------------------------
    def setImpvSpread(self, value):
        """"""
        self.algo.setImpvSpread(value / 100)
        


########################################################################
class PosTargetSpin(QtGui.QSpinBox):
    """"""
    MAX_TARGET = 10000

    #----------------------------------------------------------------------
    def __init__(self, algo):
        """Constructor"""
        super(PosTargetSpin, self).__init__()
        self.algo = algo
        
        self.setMinimum(-self.MAX_TARGET)
        self.setMaximum(self.MAX_TARGET)
        
        self.updateData()
        self.valueChanged.connect(algo.setPosTarget)
        
    #----------------------------------------------------------------------
    def updateData(self):
        """"""
        self.setValue(self.algo.posTarget)
        

########################################################################
class PosRangeSpin(QtGui.QSpinBox):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algo):
        """Constructor"""
        super(PosRangeSpin, self).__init__()
        self.algo = algo
        
        self.setMinimum(0)
        self.setMaximum(100000)
        
        self.updateData()
        self.valueChanged.connect(algo.setPosRange)
        
    #----------------------------------------------------------------------
    def updateData(self):
        """"""
        self.setValue(self.algo.posRange)


########################################################################
class OrderSizeLimitSpin(QtGui.QSpinBox):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algo):
        """Constructor"""
        super(OrderSizeLimitSpin, self).__init__()
        self.algo = algo

        self.setMinimum(0)
        self.setMaximum(1000)
        
        self.updateData()
        self.valueChanged.connect(algo.setOrderSizeLimit)
        
    #----------------------------------------------------------------------
    def updateData(self):
        """"""
        self.setValue(self.algo.orderSizeLimit)


########################################################################
class TradingDirectionCombo(QtGui.QComboBox):
    """"""
    tradingDirectionList = [MmEeAlgo.LONG_SHORT, MmEeAlgo.LONG_ONLY, MmEeAlgo.SHORT_ONLY]

    #----------------------------------------------------------------------
    def __init__(self, algo):
        """Constructor"""
        super(TradingDirectionCombo, self).__init__()
        self.algo = algo
        
        self.addItems(self.tradingDirectionList)
        
        self.updateData()
        self.currentIndexChanged.connect(self.tradingDirectionChanged)
        
    #----------------------------------------------------------------------
    def tradingDirectionChanged(self, i):
        """"""
        tradingDirection = unicode(self.currentText())
        self.algo.setTradingDirection(tradingDirection)
        self.updateData()
        
    #----------------------------------------------------------------------
    def updateData(self):
        """更新数据"""
        direction = self.algo.tradingDirection
        self.setCurrentIndex(self.tradingDirectionList.index(direction))
    

########################################################################
class PricingActiveButton(QtGui.QPushButton):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algo):
        """Constructor"""
        super(PricingActiveButton, self).__init__()
        
        self.algo = algo
        self.active = False
        
        self.setText(u'定价')
        self.updateData()
        self.clicked.connect(self.changeStatus)
        
    #----------------------------------------------------------------------
    def changeStatus(self):
        """"""
        if self.active:
            self.algo.stopPricing()
        else:
            self.algo.startPricing()
        self.updateData()
        
    #----------------------------------------------------------------------
    def updateData(self):
        """"""
        self.active = self.algo.pricingActive
        if self.active:
            self.setStyleSheet(STYLESHEET_START)
        else:
            self.setStyleSheet(STYLESHEET_STOP)


########################################################################
class TradingActiveButton(QtGui.QPushButton):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algo):
        """Constructor"""
        super(TradingActiveButton, self).__init__()
        
        self.algo = algo
        self.active = False
        
        self.setText(u'交易')
        self.updateData()
        self.clicked.connect(self.changeStatus)
        
    #----------------------------------------------------------------------
    def changeStatus(self):
        """"""
        if self.active:
            self.algo.stopTrading()
        else:
            self.algo.startTrading()
        self.updateData()
        
    #----------------------------------------------------------------------
    def updateData(self):
        """"""
        self.active = self.algo.tradingActive
        if self.active:
            self.setStyleSheet(STYLESHEET_START)
        else:
            self.setStyleSheet(STYLESHEET_STOP)


########################################################################
class AlgoMonitor(QtGui.QTableWidget):
    """"""
    callHeaders = [
        u'时间',
        u'代码',
        u'最新价',
        u'涨跌',
        
        u'买隐波',
        u'买量',
        u'买价',
        u'卖价',
        u'卖量',
        u'卖隐波',
        
        u'多仓',
        u'空仓',
        u'净仓',
        
        u'算法价差',
        u'算法隐波',
        u'买限',
        u'中间',
        u'卖限',
        
        u'价格价差',
        u'隐波价差',
        u'持仓上限',
        u'持仓目标',
        u'每笔上限',
        u'方向',
        
        u'报买量',
        u'报买价',
        u'报卖价',
        u'报卖量',
        
        u'撤单次',
        u'定价',
        u'交易',
        u'成交量'
    ] 
    
    putHeaders = [header for header in callHeaders]
    putHeaders.reverse()
    
    headers = callHeaders + [u'行权价'] + putHeaders
    
    # 信号
    signalTick = QtCore.pyqtSignal(type(Event()))
    signalTrade = QtCore.pyqtSignal(type(Event()))
    signalAlgoPricing = QtCore.pyqtSignal(type(Event()))
    signalAlgoTrading = QtCore.pyqtSignal(type(Event()))
    signalAlgoControl = QtCore.pyqtSignal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, parent=None):
        """Constructor"""
        super(AlgoMonitor, self).__init__(parent)
        
        algoEngine.init()
        
        self.algoEngine = algoEngine
        self.omEngine = algoEngine.omEngine
        self.eventEngine = algoEngine.eventEngine
        self.portfolio = algoEngine.portfolio
        self.algoDict = algoEngine.algoDict
        
        self.underlyingDict = {}
        self.optionDict = {}
        self.contractDict = {}
        
        self.cellDict = {}
        self.widgetDict = {}
        
        self.initUi()
        self.initCells()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        portfolio = self.portfolio
        
        self.setWindowTitle(u'期权算法交易')
        
        # 计算所需行数
        totalRow = 0
        
        if portfolio.underlyingList:            # 标的行
            totalRow += len(portfolio.underlyingList) + 1
            
        for chain in portfolio.chainList:       # 期权行
            totalRow += len(chain.strikeList) + 1
        totalRow -= 1                           # 移除最后一行空行
    
        # 初始化表格
        self.setColumnCount(len(self.headers))
        self.setHorizontalHeaderLabels(self.headers)
        self.setRowCount(totalRow)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
    
    #----------------------------------------------------------------------
    def initCells(self):
        """初始化单元格"""
        portfolio = self.portfolio
        row = 0

        for underlying in portfolio.underlyingList:
            cellTime = OmCell()
            cellSymbol = OmCell(underlying.symbol, COLOR_SYMBOL, COLOR_BLACK)
            cellLastPrice = OmCell(str(underlying.lastPrice))
            cellChange = OmCell()
            cellBidVolume = OmCell(str(underlying.bidVolume1), COLOR_BID, COLOR_BLACK)
            cellBidPrice = OmCell(str(underlying.bidPrice1), COLOR_BID, COLOR_BLACK)
            cellAskPrice = OmCell(str(underlying.askPrice1), COLOR_ASK, COLOR_BLACK)
            cellAskVolume = OmCell(str(underlying.askVolume1), COLOR_ASK, COLOR_BLACK)
            cellLongPos = OmCell(str(underlying.longPos), COLOR_POS, COLOR_BLACK)
            cellShortPos = OmCell(str(underlying.shortPos), COLOR_POS, COLOR_BLACK)
            cellNetPos = OmCell(str(underlying.netPos), COLOR_POS, COLOR_BLACK)
            
            self.setItem(row, 0, cellTime)
            self.setItem(row, 1, cellSymbol)
            self.setItem(row, 2, cellLastPrice)
            self.setItem(row, 3, cellChange)
            self.setItem(row, 5, cellBidVolume)
            self.setItem(row, 6, cellBidPrice)
            self.setItem(row, 7, cellAskPrice)
            self.setItem(row, 8, cellAskVolume)
            self.setItem(row, 10, cellLongPos)
            self.setItem(row, 11, cellShortPos)
            self.setItem(row, 12, cellNetPos)
            
            d = {}
            d['time'] = cellTime
            d['lastPrice'] = cellLastPrice
            d['change'] = cellChange
            d['bidVolume'] = cellBidVolume
            d['bidPrice'] = cellBidPrice
            d['askPrice'] = cellAskPrice
            d['askVolume'] = cellAskVolume
            d['longPos'] = cellLongPos
            d['shortPos'] = cellShortPos
            d['netPos'] = cellNetPos
            self.cellDict[underlying.symbol] = d
            
            self.underlyingDict[underlying.symbol] = underlying
            
            row += 1

        # 期权
        for chain in portfolio.chainList:
            row += 1
            
            for i, option in enumerate(chain.callList):
                # call
                algo = self.algoEngine.algoDict[option.symbol]
                
                cellTime = OmCell()
                cellSymbol = OmCell(option.symbol, COLOR_SYMBOL, COLOR_BLACK)
                cellLastPrice = OmCell(str(option.lastPrice))
                cellChange = OmCell()
                cellBidImpv = OmCell('%.1f' %(option.bidImpv*100), COLOR_BID, COLOR_BLACK)
                cellBidVolume = OmCell(str(option.bidVolume1), COLOR_BID, COLOR_BLACK)
                cellBidPrice = OmCell(str(option.bidPrice1), COLOR_BID, COLOR_BLACK)
                cellAskPrice = OmCell(str(option.askPrice1), COLOR_ASK, COLOR_BLACK)
                cellAskVolume = OmCell(str(option.askVolume1), COLOR_ASK, COLOR_BLACK)
                cellAskImpv = OmCell('%.1f' %(option.askImpv*100), COLOR_ASK, COLOR_BLACK)
                cellLongPos = OmCell(str(option.longPos), COLOR_POS, COLOR_BLACK)
                cellShortPos = OmCell(str(option.shortPos), COLOR_POS, COLOR_BLACK)
                cellNetPos = OmCell(str(option.netPos), COLOR_POS, COLOR_BLACK)
                cellAlgoSpread = OmCell('')
                cellAlgoImpv = OmCell('')
                cellAlgoBidLimit = OmCell('', COLOR_BID, COLOR_BLACK)
                cellAlgoMid = OmCell('', COLOR_SYMBOL, COLOR_BLACK)
                cellAlgoAskLimit = OmCell('', COLOR_ASK, COLOR_BLACK)
                spinPriceSpread = PriceSpreadSpin(algo)
                spinImpvSpread = ImpvSpreadSpin(algo)
                spinPosRange = PosRangeSpin(algo)
                spinPosTarget = PosTargetSpin(algo)
                spinOrderSizeLimit = OrderSizeLimitSpin(algo)
                comboTradingDirection = TradingDirectionCombo(algo)
                cellAlgoBidVolume = OmCell('', COLOR_BID, COLOR_BLACK)
                cellAlgoBidPrice = OmCell('', COLOR_BID, COLOR_BLACK)
                cellAlgoAskPrice = OmCell('', COLOR_ASK, COLOR_BLACK)
                cellAlgoAskVolume = OmCell('', COLOR_ASK, COLOR_BLACK)
                cellCancelTimes = OmCell(str(algo.cancelTimes))
                buttonPricingActive = PricingActiveButton(algo)
                buttonTradingActive = TradingActiveButton(algo)
                cellVolume = OmCell(str(option.volume), COLOR_SYMBOL, COLOR_BLACK)
                cellStrike = OmCell(str(option.strike), COLOR_STRIKE)
                
                self.setItem(row, 0, cellTime)
                self.setItem(row, 1, cellSymbol)
                self.setItem(row, 2, cellLastPrice)
                self.setItem(row, 3, cellChange)
                self.setItem(row, 4, cellBidImpv)
                self.setItem(row, 5, cellBidVolume)
                self.setItem(row, 6, cellBidPrice)
                self.setItem(row, 7, cellAskPrice)
                self.setItem(row, 8, cellAskVolume)
                self.setItem(row, 9, cellAskImpv)
                self.setItem(row, 10, cellLongPos)
                self.setItem(row, 11, cellShortPos)
                self.setItem(row, 12, cellNetPos)
                self.setItem(row, 13, cellAlgoSpread)
                self.setItem(row, 14, cellAlgoImpv)
                self.setItem(row, 15, cellAlgoBidLimit)
                self.setItem(row, 16, cellAlgoMid)
                self.setItem(row, 17, cellAlgoAskLimit)
                self.setCellWidget(row, 18, spinPriceSpread)
                self.setCellWidget(row, 19, spinImpvSpread)
                self.setCellWidget(row, 20, spinPosRange)
                self.setCellWidget(row, 21, spinPosTarget)
                self.setCellWidget(row, 22, spinOrderSizeLimit)
                self.setCellWidget(row, 23, comboTradingDirection)
                self.setItem(row, 24, cellAlgoBidVolume)
                self.setItem(row, 25, cellAlgoBidPrice)
                self.setItem(row, 26, cellAlgoAskPrice)
                self.setItem(row, 27, cellAlgoAskVolume)
                self.setItem(row, 28, cellCancelTimes)
                self.setCellWidget(row, 29, buttonPricingActive)
                self.setCellWidget(row, 30, buttonTradingActive)
                self.setItem(row, 31, cellVolume)
                self.setItem(row, 32, cellStrike)                
                
                d = {}
                d['time'] = cellTime
                d['lastPrice'] = cellLastPrice
                d['change'] = cellChange
                d['bidImpv'] = cellBidImpv
                d['bidVolume'] = cellBidVolume
                d['bidPrice'] = cellBidPrice
                d['askPrice'] = cellAskPrice
                d['askVolume'] = cellAskVolume
                d['askImpv'] = cellAskImpv
                d['longPos'] = cellLongPos
                d['shortPos'] = cellShortPos
                d['netPos'] = cellNetPos
                d['algoSpread'] = cellAlgoSpread
                d['algoImpv'] = cellAlgoImpv
                d['algoBidLimit'] = cellAlgoBidLimit
                d['algoMid'] = cellAlgoMid
                d['algoAskLimit'] = cellAlgoAskLimit
                d['algoBidVolume'] = cellAlgoBidVolume
                d['algoBidPrice'] = cellAlgoBidPrice
                d['algoAskPrice'] = cellAlgoAskPrice
                d['algoAskVolume'] = cellAlgoAskVolume
                d['cancelTimes'] = cellCancelTimes
                d['volume'] = cellVolume
                self.cellDict[option.symbol] = d   
                
                d2 = {}
                d2['priceSpread'] = spinPriceSpread
                d2['impvSpread'] = spinImpvSpread
                d2['posRange'] = spinPosRange
                d2['targetPos'] = spinPosTarget
                d2['orderSizeLimit'] = spinOrderSizeLimit
                d2['tradingDirection'] = comboTradingDirection
                d2['pricingActive'] = buttonPricingActive
                d2['tradingActive'] = buttonTradingActive
                self.widgetDict[option.symbol] = d2
                
                self.optionDict[option.symbol] = option
                
                # put
                option = chain.putList[i]
                algo = self.algoEngine.algoDict[option.symbol]
                
                cellTime = OmCell()
                cellSymbol = OmCell(option.symbol, COLOR_SYMBOL, COLOR_BLACK)
                cellLastPrice = OmCell(str(option.lastPrice))
                cellChange = OmCell()
                cellBidImpv = OmCell('%.1f' %(option.bidImpv*100), COLOR_BID, COLOR_BLACK)
                cellBidVolume = OmCell(str(option.bidVolume1), COLOR_BID, COLOR_BLACK)
                cellBidPrice = OmCell(str(option.bidPrice1), COLOR_BID, COLOR_BLACK)
                cellAskPrice = OmCell(str(option.askPrice1), COLOR_ASK, COLOR_BLACK)
                cellAskVolume = OmCell(str(option.askVolume1), COLOR_ASK, COLOR_BLACK)
                cellAskImpv = OmCell('%.1f' %(option.askImpv*100), COLOR_ASK, COLOR_BLACK)
                cellLongPos = OmCell(str(option.longPos), COLOR_POS, COLOR_BLACK)
                cellShortPos = OmCell(str(option.shortPos), COLOR_POS, COLOR_BLACK)
                cellNetPos = OmCell(str(option.netPos), COLOR_POS, COLOR_BLACK)
                cellAlgoSpread = OmCell('')
                cellAlgoImpv = OmCell('')
                cellAlgoBidLimit = OmCell('', COLOR_BID, COLOR_BLACK)
                cellAlgoMid = OmCell('', COLOR_SYMBOL, COLOR_BLACK)
                cellAlgoAskLimit = OmCell('', COLOR_ASK, COLOR_BLACK)
                spinPriceSpread = PriceSpreadSpin(algo)
                spinImpvSpread = ImpvSpreadSpin(algo)
                spinPosRange = PosRangeSpin(algo)
                spinPosTarget = PosTargetSpin(algo)
                spinOrderSizeLimit = OrderSizeLimitSpin(algo)
                comboTradingDirection = TradingDirectionCombo(algo)
                cellAlgoBidVolume = OmCell('', COLOR_BID, COLOR_BLACK)
                cellAlgoBidPrice = OmCell('', COLOR_BID, COLOR_BLACK)
                cellAlgoAskPrice = OmCell('', COLOR_ASK, COLOR_BLACK)
                cellAlgoAskVolume = OmCell('', COLOR_ASK, COLOR_BLACK)
                cellCancelTimes = OmCell(str(algo.cancelTimes))
                buttonPricingActive = PricingActiveButton(algo)
                buttonTradingActive = TradingActiveButton(algo)
                cellVolume = OmCell(str(option.volume), COLOR_SYMBOL, COLOR_BLACK)
                
                self.setItem(row, 64, cellTime)
                self.setItem(row, 63, cellSymbol)
                self.setItem(row, 62, cellLastPrice)
                self.setItem(row, 61, cellChange)
                self.setItem(row, 60, cellBidImpv)
                self.setItem(row, 59, cellBidVolume)
                self.setItem(row, 58, cellBidPrice)
                self.setItem(row, 57, cellAskPrice)
                self.setItem(row, 56, cellAskVolume)
                self.setItem(row, 55, cellAskImpv)
                self.setItem(row, 54, cellLongPos)
                self.setItem(row, 53, cellShortPos)
                self.setItem(row, 52, cellNetPos)
                self.setItem(row, 51, cellAlgoSpread)
                self.setItem(row, 50, cellAlgoImpv)
                self.setItem(row, 49, cellAlgoBidLimit)
                self.setItem(row, 48, cellAlgoMid)
                self.setItem(row, 47, cellAlgoAskLimit)
                self.setCellWidget(row, 46, spinPriceSpread)
                self.setCellWidget(row, 45, spinImpvSpread)
                self.setCellWidget(row, 44, spinPosRange)
                self.setCellWidget(row, 43, spinPosTarget)
                self.setCellWidget(row, 42, spinOrderSizeLimit)
                self.setCellWidget(row, 41, comboTradingDirection)
                self.setItem(row, 40, cellAlgoBidVolume)
                self.setItem(row, 39, cellAlgoBidPrice)
                self.setItem(row, 38, cellAlgoAskPrice)
                self.setItem(row, 37, cellAlgoAskVolume)
                self.setItem(row, 36, cellCancelTimes)
                self.setCellWidget(row, 35, buttonPricingActive)
                self.setCellWidget(row, 34, buttonTradingActive)
                self.setItem(row, 33, cellVolume)            
                
                d = {}
                d['time'] = cellTime
                d['lastPrice'] = cellLastPrice
                d['change'] = cellChange
                d['bidImpv'] = cellBidImpv
                d['bidVolume'] = cellBidVolume
                d['bidPrice'] = cellBidPrice
                d['askPrice'] = cellAskPrice
                d['askVolume'] = cellAskVolume
                d['askImpv'] = cellAskImpv
                d['longPos'] = cellLongPos
                d['shortPos'] = cellShortPos
                d['netPos'] = cellNetPos
                d['algoSpread'] = cellAlgoSpread
                d['algoImpv'] = cellAlgoImpv
                d['algoBidLimit'] = cellAlgoBidLimit
                d['algoMid'] = cellAlgoMid
                d['algoAskLimit'] = cellAlgoAskLimit
                d['algoBidVolume'] = cellAlgoBidVolume
                d['algoBidPrice'] = cellAlgoBidPrice
                d['algoAskPrice'] = cellAlgoAskPrice
                d['algoAskVolume'] = cellAlgoAskVolume
                d['cancelTimes'] = cellCancelTimes
                d['volume'] = cellVolume
                self.cellDict[option.symbol] = d   
                
                d2 = {}
                d2['priceSpread'] = spinPriceSpread
                d2['impvSpread'] = spinImpvSpread
                d2['posRange'] = spinPosRange
                d2['targetPos'] = spinPosTarget
                d2['orderSizeLimit'] = spinOrderSizeLimit
                d2['tradingDirection'] = comboTradingDirection
                d2['pricingActive'] = buttonPricingActive
                d2['tradingActive'] = buttonTradingActive
                self.widgetDict[option.symbol] = d2     
                
                self.optionDict[option.symbol] = option
                
                # 换行
                row += 1  
        
        self.contractDict.update(self.underlyingDict)
        self.contractDict.update(self.optionDict)
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signalTick.connect(self.processTickEvent)
        self.signalTrade.connect(self.processTradeEvent)
        self.signalAlgoPricing.connect(self.processAlgoPricingEvent)
        self.signalAlgoTrading.connect(self.processAlgoTradingEvent)
        self.signalAlgoControl.connect(self.processAlgoControlEvent)
        
        for contract in self.portfolio.contractDict.values():
            self.eventEngine.register(EVENT_TICK + contract.vtSymbol, self.signalTick.emit)
            self.eventEngine.register(EVENT_TRADE + contract.vtSymbol, self.signalTrade.emit)
            
        self.eventEngine.register(EVENT_OM_ALGO_PRICING, self.signalAlgoPricing.emit)
        self.eventEngine.register(EVENT_OM_ALGO_TRADING, self.signalAlgoTrading.emit)
        self.eventEngine.register(EVENT_OM_ALGO_CONTROL, self.signalAlgoControl.emit)
    
    #----------------------------------------------------------------------
    def processTickEvent(self, event):
        """行情推送"""
        tick = event.dict_['data']
        symbol = tick.symbol
        contract = self.contractDict[symbol]
        
        d = self.cellDict[symbol]
        d['time'].setText(contract.time)
        d['lastPrice'].setText(str(contract.lastPrice))
        d['change'].setText(str(contract.change))
        d['bidVolume'].setText(str(contract.bidVolume1))
        d['bidPrice'].setText(str(contract.bidPrice1))
        d['askPrice'].setText(str(contract.askPrice1))
        d['askVolume'].setText(str(contract.askVolume1))    
        
        if symbol in self.optionDict:
            d['bidImpv'].setText('%.1f' %(contract.bidImpv*100))
            d['askImpv'].setText('%.1f' %(contract.askImpv*100))
            d['volume'].setText(str(contract.volume))       
    
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """成交推送"""
        trade = event.dict_['data']
        symbol = trade.symbol
        contract = self.contractDict[symbol]

        d = self.cellDict[symbol]
        d['longPos'].setText(str(contract.longPos))
        d['shortPos'].setText(str(contract.shortPos))
        d['netPos'].setText(str(contract.netPos)) 

    #----------------------------------------------------------------------
    def processAlgoPricingEvent(self, event):
        """算法定价事件"""
        symbol = event.dict_['data']
        algo = self.algoDict[symbol]
        
        d = self.cellDict[symbol]
        d['algoSpread'].setText(str(algo.algoSpread))
        d['algoImpv'].setText('%.1f' %(algo.algoImpv*100))
        d['algoBidLimit'].setText(str(algo.algoBidLimit))
        d['algoMid'].setText(str(algo.algoMid))
        d['algoAskLimit'].setText(str(algo.algoAskLimit)) 
        d['cancelTimes'].setText(str(algo.cancelTimes))
    
    #----------------------------------------------------------------------
    def processAlgoTradingEvent(self, event):
        """算法交易事件"""
        symbol = event.dict_['data']
        algo = self.algoDict[symbol]
        
        d = self.cellDict[symbol]
        
        if algo.algoBidVolume:
            d['algoBidVolume'].setText(str(algo.algoBidVolume))
            d['algoBidPrice'].setText(str(algo.algoBidPrice))
        else:
            d['algoBidVolume'].setText('')
            d['algoBidPrice'].setText('')
        
        if algo.algoAskVolume:
            d['algoAskPrice'].setText(str(algo.algoAskPrice))
            d['algoAskVolume'].setText(str(algo.algoAskVolume))
        else:
            d['algoAskPrice'].setText('')
            d['algoAskVolume'].setText('') 
            
    #----------------------------------------------------------------------
    def processAlgoControlEvent(self, event):
        """算法操作事件"""
        symbol = event.dict_['data']
        algo = self.algoDict[symbol]
        d = self.cellDict[symbol]
        
        # 如果定价状态为False，清空相关单元格数据
        if not algo.pricingActive:
            d['algoSpread'].setText('')
            d['algoImpv'].setText('')
            d['algoBidLimit'].setText('')
            d['algoMid'].setText('')
            d['algoAskLimit'].setText('')
            
        # 交易状态同上
        if not algo.tradingActive:
            d['algoBidVolume'].setText('')
            d['algoBidPrice'].setText('')
            d['algoAskPrice'].setText('')
            d['algoAskVolume'].setText('')
    
    #----------------------------------------------------------------------
    def updateAllWidgets(self):
        """更新所有的组件"""
        for d in self.widgetDict.values():
            for widget in d.values():
                widget.updateData()


########################################################################
class AlgoManager(QtGui.QWidget):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, omEngine, parent=None):
        """Constructor"""
        super(AlgoManager, self).__init__(parent)
        
        self.omEngine = omEngine
        self.algoEngine = omEngine.algoEngine
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'期权算法交易')
        
        self.monitor = AlgoMonitor(self.algoEngine)
        buttonStartPricing = QtGui.QPushButton(u'启动定价')
        buttonStopPricing = QtGui.QPushButton(u'停止定价')
        buttonStartTrading = QtGui.QPushButton(u'启动交易')
        buttonStopTrading = QtGui.QPushButton(u'停止交易')
        buttonAlgoControl = QtGui.QPushButton(u'算法配置')
        buttonResizeColumns = QtGui.QPushButton(u'调整列宽')
        buttonSaveSetting = QtGui.QPushButton(u'保存配置')
        
        buttonStartPricing.clicked.connect(self.startAllPricing)
        buttonStopPricing.clicked.connect(self.stopAllPricing)
        buttonStartTrading.clicked.connect(self.startAllTrading)
        buttonStopTrading.clicked.connect(self.stopAllTrading)    
        buttonAlgoControl.clicked.connect(self.openAlgoControl)
        buttonResizeColumns.clicked.connect(self.monitor.resizeColumnsToContents)
        buttonSaveSetting.clicked.connect(self.algoEngine.saveSetting)
    
        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(buttonStartPricing)
        hbox.addWidget(buttonStopPricing)
        hbox.addWidget(buttonStartTrading)
        hbox.addWidget(buttonStopTrading)
        hbox.addStretch()
        hbox.addWidget(buttonAlgoControl)
        hbox.addWidget(buttonResizeColumns)
        hbox.addWidget(buttonSaveSetting)
        
        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.monitor)
        
        self.setLayout(vbox)
        
        self.controlWidget = AlgoControlWidget(self.monitor)
        
    #----------------------------------------------------------------------
    def startAllPricing(self):
        """"""
        self.algoEngine.startAllPricing()
        self.monitor.updateAllWidgets()
        
    #----------------------------------------------------------------------
    def stopAllPricing(self):
        """"""
        self.algoEngine.stopAllPricing()
        self.monitor.updateAllWidgets()
        
    #----------------------------------------------------------------------
    def startAllTrading(self):
        """"""
        self.algoEngine.startAllTrading()
        self.monitor.updateAllWidgets()        
            
    #----------------------------------------------------------------------
    def stopAllTrading(self):
        """"""
        self.algoEngine.stopAllTrading()
        self.monitor.updateAllWidgets()          
    
    #----------------------------------------------------------------------
    def openAlgoControl(self):
        """"""
        self.controlWidget.show()
        
    #----------------------------------------------------------------------
    def closeEvent(self, event):
        """"""
        self.controlWidget.close()
        
    
########################################################################
class AlgoControlWidget(QtGui.QWidget):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algoMonitor, parent=None):
        """Constructor"""
        super(AlgoControlWidget, self).__init__(parent)
        
        self.monitor = algoMonitor
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setWindowTitle(u'算法全局设置')
        
        self.spinPriceSpread = QtGui.QDoubleSpinBox()
        self.spinPriceSpread.setDecimals(1)
        self.spinPriceSpread.setMinimum(0)
        self.spinPriceSpread.setMaximum(1000)
        
        self.spinImpvSpread = QtGui.QDoubleSpinBox()
        self.spinImpvSpread.setDecimals(1)
        self.spinImpvSpread.setMinimum(0)
        self.spinPriceSpread.setMaximum(50)
        
        self.spinPosRange = QtGui.QSpinBox()
        self.spinPosRange.setMinimum(0)
        self.spinPosRange.setMaximum(100000)

        self.spinOrderSizeLimit = QtGui.QSpinBox()
        self.spinOrderSizeLimit.setMinimum(0)
        self.spinOrderSizeLimit.setMaximum(1000)

        self.comboTradingDirection = QtGui.QComboBox()
        self.comboTradingDirection.addItems(TradingDirectionCombo.tradingDirectionList)
        
        buttonPriceSpread = QtGui.QPushButton(u'设置价格价差')
        buttonImpvSpread = QtGui.QPushButton(u'设置隐波价差')
        buttonPosRange = QtGui.QPushButton(u'设置持仓范围')
        buttonOrderSizeLimit = QtGui.QPushButton(u'设置委托大小')
        buttonTradingDirection = QtGui.QPushButton(u'设置交易方向')
        
        buttonPriceSpread.clicked.connect(self.setPriceSpreadForAll)
        buttonImpvSpread.clicked.connect(self.setImpvSpreadForAll)
        buttonPosRange.clicked.connect(self.setPosRangeForAll)
        buttonOrderSizeLimit.clicked.connect(self.setOrderSizeLimitForAll)
        buttonTradingDirection.clicked.connect(self.setTradingDirectionForAll)
        
        grid = QtGui.QGridLayout()
        grid.addWidget(self.spinPriceSpread, 0, 0)
        grid.addWidget(self.spinImpvSpread, 1, 0)
        grid.addWidget(self.spinPosRange, 2, 0)
        grid.addWidget(self.spinOrderSizeLimit, 3, 0)
        grid.addWidget(self.comboTradingDirection, 4, 0)
        grid.addWidget(buttonPriceSpread, 0, 1)
        grid.addWidget(buttonImpvSpread, 1, 1)
        grid.addWidget(buttonPosRange, 2, 1)
        grid.addWidget(buttonOrderSizeLimit, 3, 1)
        grid.addWidget(buttonTradingDirection, 4, 1)
        self.setLayout(grid)
        
    #----------------------------------------------------------------------
    def setPriceSpreadForAll(self):
        """"""
        priceSpread = self.spinPriceSpread.value()
        
        for algo in self.monitor.algoDict.values():
            algo.setPriceSpread(priceSpread)
            
        self.monitor.updateAllWidgets()
    
    #----------------------------------------------------------------------
    def setImpvSpreadForAll(self):
        """"""
        impvSpread = self.spinImpvSpread.value() / 100
        
        for algo in self.monitor.algoDict.values():
            algo.setImpvSpread(impvSpread)
            
        self.monitor.updateAllWidgets()
    
    #----------------------------------------------------------------------
    def setPosRangeForAll(self):
        """"""
        posRange = self.spinPosRange.value()
        
        for algo in self.monitor.algoDict.values():
            algo.setPosRange(posRange)
            
        self.monitor.updateAllWidgets()
    
    #----------------------------------------------------------------------
    def setOrderSizeLimitForAll(self):
        """"""
        limit = self.spinOrderSizeLimit.value()
        
        for algo in self.monitor.algoDict.values():
            algo.setOrderSizeLimit(limit)
            
        self.monitor.updateAllWidgets()
    
    #----------------------------------------------------------------------
    def setTradingDirectionForAll(self):
        """"""
        direction = unicode(self.comboTradingDirection.currentText())
        
        for algo in self.monitor.algoDict.values():
            algo.setTradingDirection(direction)
            
        self.monitor.updateAllWidgets()
