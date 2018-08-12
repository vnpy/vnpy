# encoding: UTF-8

from __future__ import division
from collections import OrderedDict

from six import text_type

from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT,
                                    OFFSET_OPEN, OFFSET_CLOSE,
                                    STATUS_ALLTRADED, STATUS_CANCELLED, STATUS_REJECTED)
from vnpy.trader.uiQt import QtWidgets
from vnpy.trader.app.algoTrading.algoTemplate import AlgoTemplate
from vnpy.trader.app.algoTrading.uiAlgoWidget import AlgoWidget, QtWidgets



STATUS_FINISHED = set([STATUS_ALLTRADED, STATUS_CANCELLED, STATUS_REJECTED])


########################################################################
class StopAlgo(AlgoTemplate):
    """停止单算法，也可以用于止损单"""
    
    templateName = u'STOP 条件委托'

    #----------------------------------------------------------------------
    def __init__(self, engine, setting, algoName):
        """Constructor"""
        super(StopAlgo, self).__init__(engine, setting, algoName)
        
        # 参数，强制类型转换，保证从CSV加载的配置正确
        self.vtSymbol = str(setting['vtSymbol'])            # 合约代码
        self.direction = text_type(setting['direction'])    # 买卖
        self.stopPrice = float(setting['stopPrice'])        # 触发价格
        self.totalVolume = float(setting['totalVolume'])    # 数量
        self.offset = text_type(setting['offset'])          # 开平
        self.priceAdd = float(setting['priceAdd'])          # 下单时的超价
        
        self.vtOrderID = ''     # 委托号
        self.tradedVolume = 0   # 成交数量
        self.orderStatus = ''   # 委托状态
        
        self.subscribe(self.vtSymbol)
        self.paramEvent()
        self.varEvent()
    
    #----------------------------------------------------------------------
    def onTick(self, tick):
        """"""
        # 如果已经发出委托，则忽略行情事件
        if self.vtOrderID:
            return
        
        # 如果到达止损位，才触发委托
        if (self.direction == DIRECTION_LONG and 
            tick.lastPrice >= self.stopPrice):
            # 计算超价委托价格
            price = self.stopPrice + self.priceAdd
            
            # 避免价格超过涨停价
            if tick.upperLimit:    
                price = min(price, tick.upperLimit)
                
            func = self.buy
        else:
            price = self.stopPrice - self.priceAdd
            
            if tick.lowerLimit:
                price = max(price, tick.lowerLimit)
                
            func = self.sell
            
        self.vtOrderID = func(self.vtSymbol, price, self.volume, offset=self.offset)
        
        msg = u'停止单已触发，代码：%s，方向：%s, 价格：%s，数量：%s，开平：%s' %(self.vtSymbol,
                                                                                self.direction,
                                                                                self.stopPrice,
                                                                                self.totalVolume,
                                                                                self.offset)
        self.writeLog(msg)
        
        # 更新变量
        self.varEvent()        
        
    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onOrder(self, order):
        """"""
        self.tradedVolume = order.tradedVolume
        self.orderStatus = order.status
        
        if self.orderStatus in STATUS_FINISHED:
            self.stop()
        
        self.varEvent()
    
    #----------------------------------------------------------------------
    def onTimer(self):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onStop(self):
        """"""
        self.writeLog(u'停止算法')
        self.varEvent()
        
    #----------------------------------------------------------------------
    def varEvent(self):
        """更新变量"""
        d = OrderedDict()
        d[u'算法状态'] = self.active
        d[u'委托号'] = self.vtOrderID
        d[u'成交数量'] = self.tradedVolume
        d[u'委托状态'] = self.orderStatus
        d['active'] = self.active
        self.putVarEvent(d)
    
    #----------------------------------------------------------------------
    def paramEvent(self):
        """更新参数"""
        d = OrderedDict()
        d[u'代码'] = self.vtSymbol
        d[u'方向'] = self.direction
        d[u'触发价格'] = self.stopPrice
        d[u'数量'] = self.totalVolume
        d[u'开平'] = self.offset
        self.putParamEvent(d)


########################################################################
class StopWidget(AlgoWidget):
    """"""
    
    #----------------------------------------------------------------------
    def __init__(self, algoEngine, parent=None):
        """Constructor"""
        super(StopWidget, self).__init__(algoEngine, parent)
        
        self.templateName = StopAlgo.templateName
        
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
        
        self.comboOffset = QtWidgets.QComboBox()
        self.comboOffset.addItems(['', OFFSET_OPEN, OFFSET_CLOSE])
        self.comboOffset.setCurrentIndex(0)
        
        self.spinPriceAdd = QtWidgets.QDoubleSpinBox()
        self.spinPriceAdd.setMinimum(0)
        self.spinPriceAdd.setMaximum(1000000000)
        self.spinPriceAdd.setDecimals(8)        
        
        buttonStart = QtWidgets.QPushButton(u'启动')
        buttonStart.clicked.connect(self.addAlgo)
        buttonStart.setMinimumHeight(100)
        
        Label = QtWidgets.QLabel
        
        grid = QtWidgets.QGridLayout()
        grid.addWidget(Label(u'代码'), 0, 0)
        grid.addWidget(self.lineSymbol, 0, 1)
        grid.addWidget(Label(u'方向'), 1, 0)
        grid.addWidget(self.comboDirection, 1, 1)
        grid.addWidget(Label(u'价格'), 2, 0)
        grid.addWidget(self.spinPrice, 2, 1)
        grid.addWidget(Label(u'数量'), 3, 0)
        grid.addWidget(self.spinVolume, 3, 1)
        grid.addWidget(Label(u'开平'), 4, 0)
        grid.addWidget(self.comboOffset, 4, 1)
        grid.addWidget(Label(u'超价'), 5, 0)
        grid.addWidget(self.spinPriceAdd, 5, 1)        
        
        return grid
    
    #----------------------------------------------------------------------
    def getAlgoSetting(self):
        """"""
        setting = OrderedDict()
        setting['templateName'] = StopAlgo.templateName
        setting['vtSymbol'] = str(self.lineSymbol.text())
        setting['direction'] = text_type(self.comboDirection.currentText())
        setting['stopPrice'] = float(self.spinPrice.value())
        setting['totalVolume'] = float(self.spinVolume.value())
        setting['offset'] = text_type(self.comboOffset.currentText())
        setting['priceAdd'] = float(self.spinPriceAdd.value())
        
        return setting
    
    
