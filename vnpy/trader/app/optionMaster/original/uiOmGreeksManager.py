# encoding: UTF-8

from eventType import *
from eventEngine import Event
from uiOmBase import *


########################################################################
class GreeksMonitor(QtGui.QTableWidget):
    """希腊值监控"""
    headers = [
        u'代码',
        u'多仓',
        u'空仓',
        u'净仓',
        u'Delta',
        u'Gamma',
        u'Theta',
        u'Vega',
        u'持仓Delta',
        u'持仓Gamma',
        u'持仓Theta',
        u'持仓Vega'
    ]    
    
    signal = QtCore.pyqtSignal(type(Event()))

    #----------------------------------------------------------------------
    def __init__(self, omEngine, parent=None):
        """Constructor"""
        super(GreeksMonitor, self).__init__()
        
        self.portfolio = omEngine.portfolio
        self.eventEngine = omEngine.eventEngine
        
        self.cellDict = {}      # key:symbol, value:cell dict
        self.updateTrigger = 2
        self.updateCount = 0
        
        self.initUi()
        self.initCells()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        portfolio = self.portfolio
        
        self.setWindowTitle(u'Greeks监控')
        
        # 计算所需行数
        totalRow = 1                            # 组合行
        
        if portfolio.equityDict:                # 股票行
            totalRow += len(portfolio.equityDict) + 1
            
        if portfolio.futuresDict:               # 期货行
            totalRow += len(portfolio.futuresDict) + 1
            
        if portfolio.chainDict:                 # 期权链行
            totalRow += len(portfolio.chainDict) + 1
            
        for chain in portfolio.chainList:       # 期权行
            totalRow += len(chain.optionList) + 1
    
        # 初始化表格
        self.setColumnCount(len(self.headers))
        self.setHorizontalHeaderLabels(self.headers)
        self.setRowCount(totalRow)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
        
        for i in range(self.columnCount()):
            self.horizontalHeader().setResizeMode(i, QtGui.QHeaderView.Stretch)
        self.horizontalHeader().setResizeMode(0, QtGui.QHeaderView.ResizeToContents)
        
    #----------------------------------------------------------------------
    def initCells(self):
        """初始化单元格"""
        portfolio = self.portfolio
        row = 0
        
        # 组合
        cellSymbol = OmCell(portfolio.name, COLOR_SYMBOL, COLOR_BLACK)
        cellLongPos = OmCell(0, COLOR_POS, COLOR_BLACK)
        cellShortPos = OmCell(0, COLOR_POS, COLOR_BLACK)
        cellNetPos = OmCell(0, COLOR_POS, COLOR_BLACK)
        cellPosDelta = OmCell(0, COLOR_STRIKE)
        cellPosGamma = OmCell(0, COLOR_STRIKE)
        cellPosTheta = OmCell(0, COLOR_STRIKE)
        cellPosVega = OmCell(0, COLOR_STRIKE)
        
        self.setItem(row, 0, cellSymbol)
        self.setItem(row, 1, cellLongPos)
        self.setItem(row, 2, cellShortPos)
        self.setItem(row, 3, cellNetPos)
        self.setItem(row, 8, cellPosDelta)
        self.setItem(row, 9, cellPosGamma)
        self.setItem(row, 10, cellPosTheta)
        self.setItem(row, 11, cellPosVega)
        
        d = {}
        d['longPos'] = cellLongPos
        d['shortPos'] = cellShortPos
        d['netPos'] = cellNetPos
        d['posDelta'] = cellPosDelta
        d['posGamma'] = cellPosGamma
        d['posTheta'] = cellPosTheta
        d['posVega'] = cellPosVega
        self.cellDict[portfolio.name] = d
        
        row += 1
        
        # 股票
        if portfolio.equityDict:
            row += 1    # 空行
            
            for underlying in portfolio.equityDict.values():
                cellSymbol = OmCell(underlying.symbol, COLOR_SYMBOL, COLOR_BLACK)
                cellLongPos = OmCell(0, COLOR_POS, COLOR_BLACK)
                cellShortPos = OmCell(0, COLOR_POS, COLOR_BLACK)
                cellNetPos = OmCell(0, COLOR_POS, COLOR_BLACK)
                cellTheoDelta = OmCell(str(underlying.theoDelta))
                cellPosDelta = OmCell(0, COLOR_STRIKE)
                
                self.setItem(row, 0, cellSymbol)
                self.setItem(row, 1, cellLongPos)
                self.setItem(row, 2, cellShortPos)
                self.setItem(row, 3, cellNetPos)
                self.setItem(row, 4, cellTheoDelta)
                self.setItem(row, 8, cellPosDelta)
                
                d = {}
                d['longPos'] = cellLongPos
                d['shortPos'] = cellShortPos
                d['netPos'] = cellNetPos
                d['theoDelta'] = cellTheoDelta
                d['posDelta'] = cellPosDelta
                self.cellDict[underlying.symbol] = d
                
                row += 1
                
        # 期货
        if portfolio.futuresDict:
            row += 1    # 空行
            
            for underlying in portfolio.futuresDict.values():
                cellSymbol = OmCell(underlying.symbol, COLOR_SYMBOL, COLOR_BLACK)
                cellLongPos = OmCell(0, COLOR_POS, COLOR_BLACK)
                cellShortPos = OmCell(0, COLOR_POS, COLOR_BLACK)
                cellNetPos = OmCell(0, COLOR_POS, COLOR_BLACK)
                cellTheoDelta = OmCell(str(underlying.theoDelta))
                cellPosDelta = OmCell(0, COLOR_STRIKE)
                
                self.setItem(row, 0, cellSymbol)
                self.setItem(row, 1, cellLongPos)
                self.setItem(row, 2, cellShortPos)
                self.setItem(row, 3, cellNetPos)
                self.setItem(row, 4, cellTheoDelta)
                self.setItem(row, 8, cellPosDelta)
                
                d = {}
                d['longPos'] = cellLongPos
                d['shortPos'] = cellShortPos
                d['netPos'] = cellNetPos
                d['theoDelta'] = cellTheoDelta
                d['posDelta'] = cellPosDelta
                self.cellDict[underlying.symbol] = d
                
                row += 1 
        
        # 期权链
        row += 1
        
        for chain in portfolio.chainList:
            cellSymbol = OmCell(chain.symbol + '_chain', COLOR_SYMBOL, COLOR_BLACK)
            cellLongPos = OmCell(0, COLOR_POS, COLOR_BLACK)
            cellShortPos = OmCell(0, COLOR_POS, COLOR_BLACK)
            cellNetPos = OmCell(0, COLOR_POS, COLOR_BLACK)
            cellTheoDelta = OmCell(0)
            cellTheoGamma = OmCell(0)
            cellTheoTheta = OmCell(0)
            cellTheoVega = OmCell(0)
            cellPosDelta = OmCell(0, COLOR_STRIKE)
            cellPosGamma = OmCell(0, COLOR_STRIKE)
            cellPosTheta = OmCell(0, COLOR_STRIKE)
            cellPosVega = OmCell(0, COLOR_STRIKE)
        
            self.setItem(row, 0, cellSymbol)
            self.setItem(row, 1, cellLongPos)
            self.setItem(row, 2, cellShortPos)
            self.setItem(row, 3, cellNetPos)
            self.setItem(row, 4, cellTheoDelta)
            self.setItem(row, 5, cellTheoGamma)
            self.setItem(row, 6, cellTheoTheta)
            self.setItem(row, 7, cellTheoVega)
            self.setItem(row, 8, cellPosDelta)
            self.setItem(row, 9, cellPosGamma)
            self.setItem(row, 10, cellPosTheta)
            self.setItem(row, 11, cellPosVega)
        
            d = {}
            d['longPos'] = cellLongPos
            d['shortPos'] = cellShortPos
            d['netPos'] = cellNetPos
            d['theoDelta'] = cellTheoDelta
            d['theoGamma'] = cellTheoGamma
            d['theoTheta'] = cellTheoTheta
            d['theoVega'] = cellTheoVega
            d['posDelta'] = cellPosDelta
            d['posGamma'] = cellPosGamma
            d['posTheta'] = cellPosTheta
            d['posVega'] = cellPosVega
            self.cellDict[chain.symbol + '_chain'] = d           
            
            row += 1
            
        # 期权
        for chain in portfolio.chainList:
            row += 1
            
            for option in chain.optionList:
                cellSymbol = OmCell(option.symbol, COLOR_SYMBOL, COLOR_BLACK)
                cellLongPos = OmCell(0, COLOR_POS, COLOR_BLACK)
                cellShortPos = OmCell(0, COLOR_POS, COLOR_BLACK)
                cellNetPos = OmCell(0, COLOR_POS, COLOR_BLACK)
                cellTheoDelta = OmCell(0)
                cellTheoGamma = OmCell(0)
                cellTheoTheta = OmCell(0)
                cellTheoVega = OmCell(0)
                cellPosDelta = OmCell(0, COLOR_STRIKE)
                cellPosGamma = OmCell(0, COLOR_STRIKE)
                cellPosTheta = OmCell(0, COLOR_STRIKE)
                cellPosVega = OmCell(0, COLOR_STRIKE)
            
                self.setItem(row, 0, cellSymbol)
                self.setItem(row, 1, cellLongPos)
                self.setItem(row, 2, cellShortPos)
                self.setItem(row, 3, cellNetPos)
                self.setItem(row, 4, cellTheoDelta)
                self.setItem(row, 5, cellTheoGamma)
                self.setItem(row, 6, cellTheoTheta)
                self.setItem(row, 7, cellTheoVega)
                self.setItem(row, 8, cellPosDelta)
                self.setItem(row, 9, cellPosGamma)
                self.setItem(row, 10, cellPosTheta)
                self.setItem(row, 11, cellPosVega)
            
                d = {}
                d['longPos'] = cellLongPos
                d['shortPos'] = cellShortPos
                d['netPos'] = cellNetPos
                d['theoDelta'] = cellTheoDelta
                d['theoGamma'] = cellTheoGamma
                d['theoTheta'] = cellTheoTheta
                d['theoVega'] = cellTheoVega
                d['posDelta'] = cellPosDelta
                d['posGamma'] = cellPosGamma
                d['posTheta'] = cellPosTheta
                d['posVega'] = cellPosVega
                self.cellDict[option.symbol] = d           
                
                row += 1            
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.signal.connect(self.updateTable)
        self.eventEngine.register(EVENT_TIMER, self.signal.emit)
    
    #----------------------------------------------------------------------
    def updateTable(self, event):
        """更新表格"""
        self.updateCount += 1
        if self.updateCount < self.updateTrigger:
            return
        self.updateCount = 0
    
        # 更新组合
        portfolio = self.portfolio
        d = self.cellDict[portfolio.name]
        d['longPos'].setText(str(portfolio.longPos))
        d['shortPos'].setText(str(portfolio.shortPos))
        d['netPos'].setText(str(portfolio.netPos))
        d['posDelta'].setText('%.1f' %portfolio.posDelta)
        d['posGamma'].setText('%.1f' %portfolio.posGamma)
        d['posTheta'].setText('%.1f' %portfolio.posTheta)
        d['posVega'].setText('%.1f' %portfolio.posVega)
        
        # 更新标的
        for underlying in portfolio.underlyingList:
            d = self.cellDict[underlying.symbol]
            d['longPos'].setText(str(underlying.longPos))
            d['shortPos'].setText(str(underlying.shortPos))
            d['netPos'].setText(str(underlying.netPos))
            d['posDelta'].setText('%.1f' %underlying.posDelta)
        
        # 更新期权链
        for chain in portfolio.chainList:
            d = self.cellDict[chain.symbol + '_chain']
            d['longPos'].setText(str(chain.longPos))
            d['shortPos'].setText(str(chain.shortPos))
            d['netPos'].setText(str(chain.netPos))            
            d['posDelta'].setText('%.1f' %chain.posDelta)
            d['posGamma'].setText('%.1f' %chain.posGamma)
            d['posTheta'].setText('%.1f' %chain.posTheta)
            d['posVega'].setText('%.1f' %chain.posVega)
        
        # 更新期权
        for chain in portfolio.chainList:
            for option in chain.optionList:
                d = self.cellDict[option.symbol]
                d['longPos'].setText(str(option.longPos))
                d['shortPos'].setText(str(option.shortPos))
                d['netPos'].setText(str(option.netPos))
                d['theoDelta'].setText('%.1f' %option.theoDelta)
                d['theoGamma'].setText('%.1f' %option.theoGamma)
                d['theoTheta'].setText('%.1f' %option.theoTheta)
                d['theoVega'].setText('%.1f' %option.theoVega)
                d['posDelta'].setText('%.1f' %option.posDelta)
                d['posGamma'].setText('%.1f' %option.posGamma)
                d['posTheta'].setText('%.1f' %option.posTheta)
                d['posVega'].setText('%.1f' %option.posVega)
    
    