# encoding: UTF-8

from __future__ import division
from collections import OrderedDict

from six import text_type

from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT)
from vnpy.trader.uiQt import QtWidgets
from vnpy.trader.app.algoTrading.algoTemplate import AlgoTemplate
from vnpy.trader.app.algoTrading.uiAlgoWidget import AlgoWidget, QtWidgets


########################################################################
class TwapAlgo(AlgoTemplate):
    """TWAP算法"""
    
    templateName = u'TWAP 时间加权平均'

    #----------------------------------------------------------------------
    def __init__(self, engine, setting, algoName):
        """Constructor"""
        super(TwapAlgo, self).__init__(engine, setting, algoName)
        
        # 参数，强制类型转换，保证从CSV加载的配置正确
        self.vtSymbol = str(setting['vtSymbol'])            # 合约代码
        self.direction = text_type(setting['direction'])    # 买卖
        self.targetPrice = float(setting['targetPrice'])    # 目标价格
        self.totalVolume = float(setting['totalVolume'])    # 总数量
        self.time = int(setting['time'])                    # 执行时间
        self.interval = int(setting['interval'])            # 执行间隔
        self.minVolume = float(setting['minVolume'])        # 最小委托数量
        self.priceLevel = int(setting['priceLevel'])        # 使用第几档价格委托
        
        # 变量
        self.orderSize = self.totalVolume / (self.time / self.interval)
        self.orderSize = self.roundValue(self.orderSize, self.minVolume)
        if self.minVolume >= 1:
            self.orderSize = int(self.orderSize)
            
        self.timerCount = 0
        self.timerTotal = 0
        self.tradedVolume = 0
        
        self.subscribe(self.vtSymbol)
        self.paramEvent()
        self.varEvent()
    
    #----------------------------------------------------------------------
    def onTick(self, tick):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """"""
        self.tradedVolume += trade.volume
        
        if self.tradedVolume >= self.totalVolume:
            self.stop()
        else:
            self.varEvent()
    
    #----------------------------------------------------------------------
    def onOrder(self, order):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onTimer(self):
        """"""
        self.timerCount += 1
        self.timerTotal += 1
        
        # 总时间结束，停止算法
        if self.timerTotal >= self.time:
            self.stop()
            return
        
        # 每到间隔发一次委托
        if self.timerCount >= self.interval:
            self.timerCount = 0
            
            tick = self.getTick(self.vtSymbol)
            if not tick:
                return
            
            size = min(self.orderSize, self.totalVolume-self.tradedVolume)
            
            # 买入
            if self.direction == DIRECTION_LONG:
                # 市场买1价小于目标买价
                if tick.bidPrice1 < self.targetPrice:
                    # 计算委托价格
                    priceMap = {
                        1: tick.askPrice1,
                        2: tick.askPrice2,
                        3: tick.askPrice3,
                        4: tick.askPrice4,
                        5: tick.askPrice5,
                    }
                    price = priceMap[self.priceLevel]
                    if price:
                        price = min(price, self.targetPrice)  # 如果深度价格为0，则使用目标价
                    else:
                        price = self.targetPrice
                    
                    # 发出委托
                    self.buy(self.vtSymbol, price, size)
                    self.writeLog(u'委托买入%s，数量%s，价格%s' %(self.vtSymbol, self.orderSize, price))
            # 卖出
            if self.direction == DIRECTION_SHORT:
                # 市场卖1价大于目标价
                if tick.askPrice1 > self.targetPrice:
                    # 计算委托价格
                    priceMap = {
                        1: tick.bidPrice1,
                        2: tick.bidPrice2,
                        3: tick.bidPrice3,
                        4: tick.bidPrice4,
                        5: tick.bidPrice5,
                    }
                    price = priceMap[self.priceLevel]
                    if price:
                        price = max(price, self.targetPrice)
                    else:
                        price = self.targetPrice
                    
                    # 发出委托
                    self.sell(self.vtSymbol, price, size)
                    self.writeLog(u'委托卖出%s，数量%s，价格%s' %(self.vtSymbol, self.orderSize, price))
        
        # 委托后等待到间隔一半的时间撤单
        elif self.timerCount == round(self.interval/2, 0):
            result = self.cancelAll()
            if result:
                self.writeLog(u'撤销之前的委托')
            
        self.varEvent()
    
    #----------------------------------------------------------------------
    def onStop(self):
        """"""
        self.writeLog(u'运行时间已到，停止算法')
        self.varEvent()
    
    #----------------------------------------------------------------------
    def varEvent(self):
        """更新变量"""
        d = OrderedDict()
        d[u'算法状态'] = self.active
        d[u'成交数量'] = self.tradedVolume
        d[u'单笔委托'] = self.orderSize
        d[u'本轮读秒'] = self.timerCount
        d[u'累计读秒'] = self.timerTotal
        d['active'] = self.active
        self.putVarEvent(d)
    
    #----------------------------------------------------------------------
    def paramEvent(self):
        """更新参数"""
        d = OrderedDict()
        d[u'代码'] = self.vtSymbol
        d[u'方向'] = self.direction
        d[u'目标价格'] = self.targetPrice
        d[u'总数量'] = self.totalVolume
        d[u'总时间（秒）'] = self.time
        d[u'间隔（秒）'] = self.interval
        d[u'委托档位'] = self.priceLevel
        self.putParamEvent(d)


########################################################################
class TwapWidget(AlgoWidget):
    """"""
    
    #----------------------------------------------------------------------
    def __init__(self, algoEngine, parent=None):
        """Constructor"""
        super(TwapWidget, self).__init__(algoEngine, parent)
        
        self.templateName = TwapAlgo.templateName
        
    #----------------------------------------------------------------------
    def initAlgoLayout(self):
        """"""
        self.lineSymbol = QtWidgets.QLineEdit()
        
        self.comboDirection = QtWidgets.QComboBox()
        self.comboDirection.addItem(DIRECTION_LONG)
        self.comboDirection.addItem(DIRECTION_SHORT)
        self.comboDirection.setCurrentIndex(0)
        
        self.spinPrice = QtWidgets.QDoubleSpinBox()
        self.spinPrice.setMinimum(0)
        self.spinPrice.setMaximum(1000000000)
        self.spinPrice.setDecimals(8)
        
        self.spinVolume = QtWidgets.QDoubleSpinBox()
        self.spinVolume.setMinimum(0)
        self.spinVolume.setMaximum(1000000000)
        self.spinVolume.setDecimals(6)
        
        self.spinTime = QtWidgets.QSpinBox()
        self.spinTime.setMinimum(30)
        self.spinTime.setMaximum(86400)
        
        self.spinInterval = QtWidgets.QSpinBox()
        self.spinInterval.setMinimum(10)
        self.spinInterval.setMaximum(3600)
        
        self.spinMinVolume = QtWidgets.QDoubleSpinBox()
        self.spinMinVolume.setMinimum(0)
        self.spinMinVolume.setMaximum(10000)
        self.spinMinVolume.setDecimals(6)
        self.spinMinVolume.setValue(1)
        
        self.spinPriceLevel = QtWidgets.QSpinBox()
        self.spinPriceLevel.setMinimum(1)
        self.spinPriceLevel.setMaximum(5)
        self.spinPriceLevel.setValue(1)
        
        buttonStart = QtWidgets.QPushButton(u'启动')
        buttonStart.clicked.connect(self.addAlgo)
        buttonStart.setMinimumHeight(100)
        
        Label = QtWidgets.QLabel
        
        grid = QtWidgets.QGridLayout()
        grid.addWidget(Label(u'交易代码'), 0, 0)
        grid.addWidget(self.lineSymbol, 0, 1)
        grid.addWidget(Label(u'方向'), 1, 0)
        grid.addWidget(self.comboDirection, 1, 1)
        grid.addWidget(Label(u'目标价格'), 2, 0)
        grid.addWidget(self.spinPrice, 2, 1)
        grid.addWidget(Label(u'总数量'), 3, 0)
        grid.addWidget(self.spinVolume, 3, 1)
        grid.addWidget(Label(u'总时间（秒）'), 4, 0)
        grid.addWidget(self.spinTime, 4, 1)
        grid.addWidget(Label(u'间隔（秒）'), 5, 0)
        grid.addWidget(self.spinInterval, 5, 1)
        grid.addWidget(Label(u'委托档位'), 6, 0)
        grid.addWidget(self.spinPriceLevel, 6, 1)
        grid.addWidget(Label(u'数量取整'), 7, 0)
        grid.addWidget(self.spinMinVolume, 7, 1)

        return grid
    
    #----------------------------------------------------------------------
    def getAlgoSetting(self):
        """"""
        setting = OrderedDict()
        setting['templateName'] = TwapAlgo.templateName
        setting['vtSymbol'] = str(self.lineSymbol.text())
        setting['direction'] = str(self.comboDirection.currentText())
        setting['targetPrice'] = float(self.spinPrice.value())
        setting['totalVolume'] = float(self.spinVolume.value())
        setting['time'] = int(self.spinTime.value())
        setting['interval'] = int(self.spinInterval.value())
        setting['priceLevel'] = int(self.spinPriceLevel.value())
        setting['minVolume'] = float(self.spinMinVolume.value())
        
        return setting
    
    
