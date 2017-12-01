# encoding: UTF-8

import pyqtgraph as pg

from vnpy.event import Event
from vnpy.trader.vtEvent import EVENT_TIMER
from .uiOmBase import *


########################################################################
class VolatilityChart(pg.GraphicsWindow):
    """持仓组合波动率图表"""
    signal = QtCore.pyqtSignal(type(Event()))
    
    #----------------------------------------------------------------------
    def __init__(self, omEngine, parent=None):
        """Constructor"""
        super(VolatilityChart, self).__init__(parent)
        
        self.omEngine = omEngine
        self.portfolio = omEngine.portfolio
        self.eventEngine = omEngine.eventEngine
        
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
        
        self.setWindowTitle(u'波动率图表')

        pg.setConfigOptions(antialias=True)         #启用抗锯齿
        
        # 创建绘图区以及线
        for chain in portfolio.chainDict.values():
            symbol = chain.symbol + CALL_SUFFIX

            chart = self.addPlot(title=symbol)
            chart.showGrid(x=True, y=True) 
            chart.setLabel('left', u'波动率')          #设置左边标签
            chart.setLabel('bottom', u'行权价')        #设置底部标签                

            self.bidCurveDict[symbol] = chart.plot(pen='r', symbol='t', symbolSize=8, symbolBrush='r')
            self.askCurveDict[symbol] = chart.plot(pen='g', symbolSize=8, symbolBrush='g')
            self.pricingCurveDict[symbol] = chart.plot(pen='w', symbol = 's', symbolSize=8, symbolBrush='w')
        
        self.nextRow()
        
        for chain in portfolio.chainDict.values():
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
        self.signal.connect(self.processTimerEvent)
        self.eventEngine.register(EVENT_TIMER, self.signal.emit)    
        
    #----------------------------------------------------------------------
    def processTimerEvent(self, event):
        """处理定时事件"""
        self.updateCount += 1
        if self.updateCount >= self.updateTrigger:
            self.updateCount = 0
            self.updateChart()
        
    #----------------------------------------------------------------------
    def updateChart(self):
        """更新图表"""
        for chain in self.portfolio.chainDict.values():
            strikeData = [option.k for option in chain.callDict.values()]
            
            # 看涨
            symbol = chain.symbol + CALL_SUFFIX
            
            bidImpvData = []
            askImpvData = []
            pricingImpvData = []
            
            for option in chain.callDict.values():
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
            
            for option in chain.putDict.values():
                bidImpvData.append(option.bidImpv*100)
                askImpvData.append(option.askImpv*100)
                pricingImpvData.append(option.pricingImpv*100)
            
            self.bidCurveDict[symbol].setData(y=bidImpvData, x=strikeData)
            self.askCurveDict[symbol].setData(y=askImpvData, x=strikeData)
            self.pricingCurveDict[symbol].setData(y=pricingImpvData, x=strikeData)
            
    #----------------------------------------------------------------------
    def closeEvent(self, event):
        """关闭"""
        self.eventEngine.unregister(EVENT_TIMER, self.signal.emit)
        