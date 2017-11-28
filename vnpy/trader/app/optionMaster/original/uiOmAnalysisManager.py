# encoding: UTF-8

from uiOmBase import *



########################################################################
class ScenarioValueMonitor(QtGui.QTableWidget):
    """情景分析监控工具，某一个数值"""

    #----------------------------------------------------------------------
    def __init__(self, key, parent=None):
        """Constructor"""
        super(ScenarioValueMonitor, self).__init__(parent)
        
        self.key = key
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.setEditTriggers(self.NoEditTriggers)
        
        self.setMinimumHeight(600)
        
    #----------------------------------------------------------------------
    def updateData(self, result, priceChangeArray, impvChangeArray):
        """更新界面"""        
        # 清空表格
        self.clearContents()
        
        # 设置表头
        self.setColumnCount(len(priceChangeArray))
        priceChangeHeaders = [('%s%%' %(priceChange*100)) for priceChange in priceChangeArray]
        self.setHorizontalHeaderLabels(priceChangeHeaders)
        
        self.setRowCount(len(impvChangeArray))
        impvChangeHeaders = [('%s%%' %(impvChange*100)) for impvChange in impvChangeArray]
        self.setVerticalHeaderLabels(impvChangeHeaders)

        # 设置数据
        l = [d[self.key] for d in result.values()]
        maxValue = max(l)
        minValue = min(l)
        
        # 最大和最小值相等，则说明计算逻辑有问题
        if maxValue == minValue:
            return
        
        midValue = (maxValue + minValue) / 2
        colorRatio = 255*2/(maxValue-minValue)
        
        for column, priceChange in enumerate(priceChangeArray):
            for row, impvChange in enumerate(impvChangeArray):
                value = result[(priceChange, impvChange)][self.key]
                
                # 计算颜色
                red = 255
                green = 255                
                colorValue = (value - midValue) * colorRatio
                
                if colorValue <= 0:
                    red -= abs(colorValue)
                else:
                    green -= abs(colorValue)                
                color = QtGui.QColor(red, green, 0)
                
                # 插入单元格到表格中
                cell = QtGui.QTableWidgetItem('%.1f' %value)
                cell.setBackground(color)
                cell.setForeground(COLOR_BLACK)
                self.setItem(row, column, cell)
                
        self.resizeColumnsToContents()
        self.resizeRowsToContents()


########################################################################
class ScenarioAnalysisMonitor(QtGui.QTabWidget):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, analysisEngine, parent=None):
        """Constructor"""
        super(ScenarioAnalysisMonitor, self).__init__(parent)
        
        self.engine = analysisEngine
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.valueMonitorList = []
        
        for key in ['pnl', 'delta', 'gamma', 'theta', 'vega']:
            valueMonitor = ScenarioValueMonitor(key)
            self.addTab(valueMonitor, key)
            self.valueMonitorList.append(valueMonitor)
            
    #----------------------------------------------------------------------
    def updateData(self):
        """"""
        result, priceChangeArray, impvChangeArray = self.engine.runScenarioAnalysis()
        if not result:
            return
        
        for valueMonitor in self.valueMonitorList:
            valueMonitor.updateData(result, priceChangeArray, impvChangeArray)
    
    
########################################################################
class StatisticsMonitor(QtGui.QTableWidget):
    """统计数据监控"""
    headers = [
        u'账户市值',
        u'风险度',
        u'成交量',
        u'开仓量',
        u'平仓量'
    ]     

    #----------------------------------------------------------------------
    def __init__(self, analysisEngine, parent=None):
        """Constructor"""
        super(StatisticsMonitor, self).__init__(parent)
        
        self.engine = analysisEngine
        
        self.cellDict = {}
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        # 初始化表格
        self.setColumnCount(len(self.headers))
        self.setHorizontalHeaderLabels(self.headers)
        self.setRowCount(1)
        self.verticalHeader().setVisible(False)
        self.setEditTriggers(self.NoEditTriggers)
        
        for i in range(self.columnCount()):
            self.horizontalHeader().setResizeMode(i, QtGui.QHeaderView.Stretch)
        self.verticalHeader().setResizeMode(0, QtGui.QHeaderView.Stretch)
        
        self.setFixedHeight(75)
            
        cellMarketValue = OmCell()
        cellRiskLevel = OmCell()
        cellTradeCount = OmCell()
        cellOpenCount  = OmCell()
        cellCloseCount = OmCell()
        
        self.setItem(0, 0, cellMarketValue)
        self.setItem(0, 1, cellRiskLevel)
        self.setItem(0, 2, cellTradeCount)
        self.setItem(0, 3, cellOpenCount)
        self.setItem(0, 4, cellCloseCount)
        
        self.cellDict['marketValue'] = cellMarketValue
        self.cellDict['riskLevel'] = cellRiskLevel
        self.cellDict['tradeCount'] = cellTradeCount
        self.cellDict['openCount'] = cellOpenCount
        self.cellDict['closeCount'] = cellCloseCount
        
    #----------------------------------------------------------------------
    def updateData(self):
        """"""
        marketValue, riskLevel = self.engine.getAccountMarketValue()
        
        if marketValue is not None:
            self.cellDict['marketValue'].setText('%.1f' %marketValue)
            self.cellDict['riskLevel'].setText('%.1f%%' %(riskLevel*100))
            
        tradeCount, openCount, closeCount = self.engine.getTradeCount()
        
        if tradeCount is not None:
            self.cellDict['tradeCount'].setText(str(tradeCount))
            self.cellDict['openCount'].setText(str(openCount))
            self.cellDict['closeCount'].setText(str(closeCount))


########################################################################
class AnalysisManager(QtGui.QWidget):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, omEngine, parent=None):
        """Constructor"""
        super(AnalysisManager, self).__init__(parent)
        
        self.engine = omEngine.analysisEngine
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """"""
        self.scenarioAnalysisMonitor = ScenarioAnalysisMonitor(self.engine)
        self.statisticsMonitor = StatisticsMonitor(self.engine)
        
        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(self.statisticsMonitor)
        vbox.addWidget(self.scenarioAnalysisMonitor)
        self.setLayout(vbox)
        
    #----------------------------------------------------------------------
    def updateData(self):
        """"""
        self.statisticsMonitor.updateData()
        self.scenarioAnalysisMonitor.updateData()
    
    