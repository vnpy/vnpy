# encoding: UTF-8

from __future__ import division

import numpy as np

from .uiOmBase import *


########################################################################
class ScenarioValueMonitor(QtWidgets.QTableWidget):
    """情景分析监控工具，某一个数值"""

    #----------------------------------------------------------------------
    def __init__(self, key, parent=None):
        """Constructor"""
        super(ScenarioValueMonitor, self).__init__(parent)
        
        self.key = key
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setEditTriggers(self.NoEditTriggers)
        
        self.setMinimumHeight(600)
        
    #----------------------------------------------------------------------
    def updateData(self, result, priceChangeArray, impvChangeArray):
        """更新界面"""        
        # 清空表格
        self.clearContents()
        
        # 设置表头
        self.setColumnCount(len(priceChangeArray))
        priceChangeHeaders = [('price %s%%' %(priceChange*100)) for priceChange in priceChangeArray]
        self.setHorizontalHeaderLabels(priceChangeHeaders)
        
        self.setRowCount(len(impvChangeArray))
        impvChangeHeaders = [('impv %s%%' %(impvChange*100)) for impvChange in impvChangeArray]
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
                cell = QtWidgets.QTableWidgetItem('%.1f' %value)
                cell.setBackground(color)
                cell.setForeground(COLOR_BLACK)
                self.setItem(row, column, cell)
                
        self.resizeColumnsToContents()
        self.resizeRowsToContents()


########################################################################
class ScenarioAnalysisMonitor(QtWidgets.QTabWidget):
    """情景分析监控组件"""

    #----------------------------------------------------------------------
    def __init__(self, parent=None):
        """Constructor"""
        super(ScenarioAnalysisMonitor, self).__init__(parent)
        
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
    def updateData(self, result, priceChangeArray, impvChangeArray):
        """更新数据"""
        for valueMonitor in self.valueMonitorList:
            valueMonitor.updateData(result, priceChangeArray, impvChangeArray)


########################################################################
class AnalysisManager(QtWidgets.QWidget):
    """研究分析管理"""

    #----------------------------------------------------------------------
    def __init__(self, omEngine, parent=None):
        """Constructor"""
        super(AnalysisManager, self).__init__(parent)
        
        self.omEngine = omEngine
        self.portfolio = omEngine.portfolio
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
        """初始化界面"""
        self.setWindowTitle(u'持仓分析')
        
        self.scenarioAnalysisMonitor = ScenarioAnalysisMonitor()
        
        self.buttonScenarioAnalysis = QtWidgets.QPushButton(u'情景分析')
        self.buttonScenarioAnalysis.clicked.connect(self.updateData)
        
        hbox = QtWidgets.QHBoxLayout()
        hbox.addWidget(self.buttonScenarioAnalysis)
        hbox.addStretch()
        
        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.scenarioAnalysisMonitor)
        self.setLayout(vbox)
        
    #----------------------------------------------------------------------
    def updateData(self):
        """更新数据"""
        result, priceChangeArray, impvChangeArray = self.runScenarioAnalysis()
        if result:
            self.scenarioAnalysisMonitor.updateData(result, priceChangeArray, impvChangeArray)
    
    #----------------------------------------------------------------------
    def runScenarioAnalysis(self):
        """运行情景分析"""
        portfolio = self.portfolio
        calculateGreeks = portfolio.model.calculateGreeks
        
        if not portfolio:
            return None, None, None
        
        changeRange = 5
        priceChangeArray = np.arange(-changeRange, changeRange+1) / 100
        impvChangeArray = np.arange(-changeRange, changeRange+1) / 100
        expiryChange = 1/240    # 一个交易日对应的时间变化
        result = {}     # 分析结果
        
        for priceChange in priceChangeArray:
            for impvChange in impvChangeArray:
                portfolioPnl = 0
                portfolioDelta = 0
                portfolioGamma = 0
                portfolioTheta = 0
                portfolioVega = 0
                
                for underlying in portfolio.underlyingDict.values():
                    portfolioPnl += underlying.midPrice * underlying.netPos * priceChange
                    portfolioDelta += underlying.theoDelta * underlying.netPos
                    
                try:
                    for option in portfolio.optionDict.values():
                        if not option.netPos:
                            continue
                        
                        price, delta, gamma, theta, vega = calculateGreeks(option.underlying.midPrice*(1+priceChange),
                                                                           option.k,
                                                                           option.r,
                                                                           max(option.t-expiryChange, 0),
                                                                           option.pricingImpv*(1+impvChange),
                                                                           option.cp)
                        
                        portfolioPnl += (price - option.theoPrice) * option.netPos * option.size
                        portfolioDelta += delta * option.netPos * option.size
                        portfolioGamma += gamma * option.netPos * option.size
                        portfolioTheta += theta * option.netPos * option.size
                        portfolioVega += vega * option.netPos * option.size
                except ZeroDivisionError:
                    return None, None, None
                
                d = {
                    'pnl': portfolioPnl,
                    'delta': portfolioDelta,
                    'gamma': portfolioGamma,
                    'theta': portfolioTheta,
                    'vega': portfolioVega
                }
                result[(priceChange, impvChange)] = d
        
        return result, priceChangeArray, impvChangeArray    
    