# encoding: UTF-8

from eventEngine import Event
from eventType import *
from uiOmBase import *
import pyqtgraph as pg


########################################################################
class VolatilityChart(pg.GraphicsWindow):
    """持仓组合波动率图表"""
    signal = QtCore.pyqtSignal(type(Event()))
    
    #----------------------------------------------------------------------
    def __init__(self, portfolio, eventEngine, parent=None):
        """Constructor"""
        super(VolatilityChart, self).__init__(parent)
        
        self.portfolio = portfolio
        self.eventEngine = eventEngine
        
        self.updateCount = 0
        self.updateTrigger = 2
        
        self.bidCurveDict = {}
        self.askCurveDict = {}
        self.pricingCurveDict = {}
        
        self.initUi()
        self.registerEvent()
    
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        portfolio = self.portfolio
        
        self.setWindowTitle(portfolio.name + u'波动率')

        pg.setConfigOptions(antialias=True)         #启用抗锯齿
        
        # 创建绘图区以及线
        for chain in portfolio.chainList:
            symbol = chain.symbol + CALL_SUFFIX

            chart = self.addPlot(title=symbol)
            chart.showGrid(x=True, y=True) 
            chart.setLabel('left', u'波动率')          #设置左边标签
            chart.setLabel('bottom', u'行权价')        #设置底部标签                

            self.bidCurveDict[symbol] = chart.plot(pen='r', symbol='t', symbolSize=8, symbolBrush='r')
            self.askCurveDict[symbol] = chart.plot(pen='g', symbolSize=8, symbolBrush='g')
            self.pricingCurveDict[symbol] = chart.plot(pen='w', symbol = 's', symbolSize=8, symbolBrush='w')
        
        self.nextRow()
        
        for chain in portfolio.chainList:
            symbol = chain.symbol + PUT_SUFFIX

            chart = self.addPlot(title=symbol)
            chart.showGrid(x=True, y=True) 
            chart.setLabel('left', u'波动率') 
            chart.setLabel('bottom', u'行权价')

            self.bidCurveDict[symbol] = chart.plot(pen='r', symbol='t', symbolSize=8, symbolBrush='r')
            self.askCurveDict[symbol] = chart.plot(pen='g', symbolSize=8, symbolBrush='g')
            self.pricingCurveDict[symbol] = chart.plot(pen='w', symbol = 's', symbolSize=8, symbolBrush='w')

    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateChart)
        self.eventEngine.register(EVENT_TIMER, self.signal.emit)    
        
    #----------------------------------------------------------------------
    def updateChart(self, event):
        """更新图表"""
        self.updateCount += 1
        if self.updateCount < self.updateTrigger:
            return
        self.updateCount = 0
        

        for chain in self.portfolio.chainList:
            strikeData = chain.strikeList
            
            # 看涨
            symbol = chain.symbol + CALL_SUFFIX
            
            bidImpvData = []
            askImpvData = []
            pricingImpvData = []
            
            for option in chain.callList:
                bidImpvData.append(option.bidImpv*100)
                askImpvData.append(option.askImpv*100)
                pricingImpvData.append(option.pricingImpv*100)
            
            self.bidCurveDict[symbol].setData(y=bidImpvData, x=strikeData)
            self.askCurveDict[symbol].setData(y=askImpvData, x=strikeData)
            self.pricingCurveDict[symbol].setData(y=pricingImpvData, x=strikeData)
            
            # 看跌
            symbol = chain.symbol + PUT_SUFFIX
            
            bidImpvData = []
            askImpvData = []
            pricingImpvData = []
            
            for option in chain.putList:
                bidImpvData.append(option.bidImpv*100)
                askImpvData.append(option.askImpv*100)
                pricingImpvData.append(option.pricingImpv*100)
            
            self.bidCurveDict[symbol].setData(y=bidImpvData, x=strikeData)
            self.askCurveDict[symbol].setData(y=askImpvData, x=strikeData)
            self.pricingCurveDict[symbol].setData(y=pricingImpvData, x=strikeData)

    #----------------------------------------------------------------------
    def closeEvent(self, event):
        """关闭事件"""
        self.saveWindowSettings()
        event.accept()        


########################################################################
class ChainVolatilityMonitor(QtGui.QTableWidget):
    """期权链波动率监控"""
    headers = [
        u'代码',
        u'买隐波',
        u'定价',
        u'卖隐波',
        u'行权价',
        u'买隐波',
        u'定价',
        u'卖隐波',   
        u'代码'
    ]

    #----------------------------------------------------------------------
    def __init__(self, chain, parent=None):
        """Constructor"""
        super(ChainVolatilityMonitor, self).__init__(parent)
        
        self.chain = chain
        self.cellDict = {}      # key: symbol, value: dict of cells
        
        self.initUi()
        self.itemChanged.connect(self.pricingImpvChanged)
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        chain = self.chain
        
        # 初始化表格
        self.setColumnCount(len(self.headers))
        self.setHorizontalHeaderLabels(self.headers)
        self.setRowCount(len(chain.strikeList))
        self.verticalHeader().setVisible(False)
        
        for i in range(self.columnCount()):
            self.horizontalHeader().setResizeMode(i, QtGui.QHeaderView.Stretch)
            
        # 初始化单元格
        for row, option in enumerate(chain.callList):
            cellSymbol = OmCell(option.symbol, COLOR_SYMBOL, COLOR_BLACK)
            cellBid = OmCell('%.1f' %(option.bidImpv*100), COLOR_BID, COLOR_BLACK)
            cellPricing = OmCell('%.1f' %(option.pricingImpv*100), COLOR_POS, COLOR_BLACK)
            cellAsk = OmCell('%.1f' %(option.askImpv*100), COLOR_ASK, COLOR_BLACK)
            cellStrike = OmCell(str(option.strike), COLOR_STRIKE)
            
            cellPricing.data = option.symbol
            
            self.setItem(row, 0, cellSymbol)
            self.setItem(row, 1, cellBid)
            self.setItem(row, 2, cellPricing)
            self.setItem(row, 3, cellAsk)
            self.setItem(row, 4, cellStrike)
            
            d = {}
            d['bid'] = cellBid
            d['ask'] = cellAsk
            d['pricing'] = cellPricing
            self.cellDict[option.symbol] = d
            
        for row, option in enumerate(chain.putList):
            cellSymbol = OmCell(option.symbol, COLOR_SYMBOL, COLOR_BLACK)
            cellBid = OmCell('%.1f' %(option.bidImpv*100), COLOR_BID, COLOR_BLACK)
            cellPricing = OmCell('%.1f' %(option.pricingImpv*100), COLOR_POS, COLOR_BLACK)
            cellAsk = OmCell('%.1f' %(option.askImpv*100), COLOR_ASK, COLOR_BLACK)
            
            cellPricing.data = option.symbol
            
            self.setItem(row, 5, cellBid)
            self.setItem(row, 6, cellPricing)
            self.setItem(row, 7, cellAsk)
            self.setItem(row, 8, cellSymbol)
            
            d = {}
            d['bid'] = cellBid
            d['ask'] = cellAsk
            d['pricing'] = cellPricing
            self.cellDict[option.symbol] = d        
    
    #----------------------------------------------------------------------
    def refresh(self):
        """刷新数据"""
        for option in self.chain.optionList:
            d = self.cellDict[option.symbol]
            d['bid'].setText('%.1f' %(option.bidImpv*100))
            d['ask'].setText('%.1f' %(option.askImpv*100))
            d['pricing'].setText('%.1f' %(option.pricingImpv*100))
    
    #----------------------------------------------------------------------
    def pricingImpvChanged(self, item):
        """更细定价波动率"""
        if not item.data:
            return
        
        option = self.chain.optionDict[item.data]
        newImpv = float(item.text())/100
        
        if option.pricingImpv != newImpv:
            option.pricingImpv = newImpv


########################################################################
class ChainVolatilityManager(QtGui.QWidget):
    """期权链波动率管理"""
    IMPV_CHANGE_STEP = 0.002

    #----------------------------------------------------------------------
    def __init__(self, chain, parent=None):
        """Constructor"""
        super(ChainVolatilityManager, self).__init__(parent)
        
        self.chain = chain
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.monitor = ChainVolatilityMonitor(self.chain)
        
        buttonCallIncrease = QtGui.QPushButton(u'看涨+' + ('%.1f%%' %(self.IMPV_CHANGE_STEP*100)))
        buttonCallDecrease = QtGui.QPushButton(u'看涨-' + ('%.1f%%' %(self.IMPV_CHANGE_STEP*100)))
        buttonPutIncrease = QtGui.QPushButton(u'看跌+' + ('%.1f%%' %(self.IMPV_CHANGE_STEP*100)))
        buttonPutDecrease = QtGui.QPushButton(u'看跌-' + ('%.1f%%' %(self.IMPV_CHANGE_STEP*100)))
        buttonCallReset = QtGui.QPushButton(u'看涨重置')
        buttonPutReset = QtGui.QPushButton(u'看跌重置')
        buttonRefresh = QtGui.QPushButton(u'刷新')
        
        buttonCallIncrease.clicked.connect(self.callIncrease)
        buttonCallDecrease.clicked.connect(self.callDecrease)
        buttonPutIncrease.clicked.connect(self.putIncrease)
        buttonPutDecrease.clicked.connect(self.putDecrease)
        buttonCallReset.clicked.connect(self.callReset)
        buttonPutReset.clicked.connect(self.putReset)
        buttonRefresh.clicked.connect(self.monitor.refresh)
        
        hbox = QtGui.QHBoxLayout()
        hbox.addStretch()
        hbox.addWidget(buttonCallIncrease)
        hbox.addWidget(buttonCallReset)
        hbox.addWidget(buttonCallDecrease)
        hbox.addStretch()
        hbox.addWidget(buttonRefresh)
        hbox.addStretch()
        hbox.addWidget(buttonPutIncrease)
        hbox.addWidget(buttonPutReset)
        hbox.addWidget(buttonPutDecrease)     
        hbox.addStretch()
        
        vbox = QtGui.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.monitor)
        
        self.setLayout(vbox)
        
    #----------------------------------------------------------------------
    def callIncrease(self):
        """看涨增加"""
        for option in self.chain.callList:
            option.pricingImpv += self.IMPV_CHANGE_STEP
        self.monitor.refresh()
    
    #----------------------------------------------------------------------
    def callDecrease(self):
        """看涨减少"""
        for option in self.chain.callList:
            option.pricingImpv -= self.IMPV_CHANGE_STEP
        self.monitor.refresh()
    
    #----------------------------------------------------------------------
    def callReset(self):
        """看涨重置为中值"""
        for option in self.chain.callList:
            option.pricingImpv = option.midImpv
        self.monitor.refresh()
    
    #----------------------------------------------------------------------
    def putIncrease(self):
        """看跌增加"""
        for option in self.chain.putList:
            option.pricingImpv += self.IMPV_CHANGE_STEP
        self.monitor.refresh()
    
    #----------------------------------------------------------------------
    def putDecrease(self):
        """看跌减少"""
        for option in self.chain.putList:
            option.pricingImpv -= self.IMPV_CHANGE_STEP
        self.monitor.refresh()
    
    #----------------------------------------------------------------------
    def putReset(self):
        """看跌重置为中值"""
        for option in self.chain.putList:
            option.pricingImpv = option.midImpv
        self.monitor.refresh()



########################################################################
class VolatilityManager(QtGui.QWidget):
    """波动率管理"""

    #----------------------------------------------------------------------
    def __init__(self, omEngine, parent=None):
        """Constructor"""
        super(VolatilityManager, self).__init__(parent)
        
        self.omEngine = omEngine
        self.portfolio = omEngine.portfolio
        self.eventEngine = omEngine.eventEngine
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'波动率管理')
        
        tab = QtGui.QTabWidget()
        for chain in self.portfolio.chainList:
            chainManager = ChainVolatilityManager(chain)
            tab.addTab(chainManager, chain.symbol)
        
        chart = VolatilityChart(self.portfolio, self.eventEngine)
        
        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(chart)
        vbox.addWidget(tab)
        
        self.setLayout(vbox)
        
    