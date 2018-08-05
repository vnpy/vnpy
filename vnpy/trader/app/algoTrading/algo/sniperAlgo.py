# encoding: UTF-8

from __future__ import division
from collections import OrderedDict

from six import text_type

from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT,
                                    OFFSET_OPEN, OFFSET_CLOSE,
                                    STATUS_ALLTRADED, STATUS_CANCELLED, STATUS_REJECTED)
from vnpy.trader.uiQt import QtWidgets, QtGui
from vnpy.trader.app.algoTrading.algoTemplate import AlgoTemplate
from vnpy.trader.app.algoTrading.uiAlgoWidget import AlgoWidget



STATUS_FINISHED = set([STATUS_ALLTRADED, STATUS_CANCELLED, STATUS_REJECTED])


########################################################################
class SniperAlgo(AlgoTemplate):
    """狙击手算法"""
    
    templateName = u'Sniper 狙击手'

    #----------------------------------------------------------------------
    def __init__(self, engine, setting, algoName):
        """Constructor"""
        super(SniperAlgo, self).__init__(engine, setting, algoName)
        
        # 参数，强制类型转换，保证从CSV加载的配置正确
        self.vtSymbol = str(setting['vtSymbol'])            # 合约代码
        self.direction = text_type(setting['direction'])    # 买卖
        self.price = float(setting['price'])                # 价格
        self.volume = float(setting['volume'])              # 数量
        self.offset = text_type(setting['offset'])          # 开平
        
        self.vtOrderID = ''     # 委托号
        self.tradedVolume = 0   # 成交数量
        
        self.subscribe(self.vtSymbol)
        self.paramEvent()
        self.varEvent()
    
    #----------------------------------------------------------------------
    def onTick(self, tick):
        """"""
        # 执行撤单
        if self.vtOrderID:
            self.cancelAll()
            return
        
        # 做多，且卖1价格小于等于执行目标价
        if (self.direction == DIRECTION_LONG and
            tick.askPrice1 <= self.price):
            orderVolume = self.volume - self.tradedVolume
            orderVolume = min(orderVolume, tick.askVolume1)
            self.vtOrderID = self.buy(self.vtSymbol, self.price, 
                                      orderVolume, offset=self.offset)
        
        # 做空
        elif (self.direction == DIRECTION_SHORT and
              tick.bidPrice1 >= self.price):
            orderVolume = self.volume - self.tradedVolume
            orderVolume = min(orderVolume, tick.bidVolume1)
            self.vtOrderID = self.sell(self.vtSymbol, self.price, 
                                       orderVolume, offset=self.offset)            
    
        # 更新变量
        self.varEvent()        
        
    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """"""
        self.tradedVolume += trade.volume
        
        if self.tradedVolume >= self.volume:
            self.stop()
        
        self.varEvent()
    
    #----------------------------------------------------------------------
    def onOrder(self, order):
        """"""
        # 若委托已经结束，则清空委托号
        if order.status in STATUS_FINISHED:
            self.vtOrderID = ''
            
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
        self.putVarEvent(d)
    
    #----------------------------------------------------------------------
    def paramEvent(self):
        """更新参数"""
        d = OrderedDict()
        d[u'代码'] = self.vtSymbol
        d[u'方向'] = self.direction
        d[u'价格'] = self.price
        d[u'数量'] = self.volume
        d[u'开平'] = self.offset
        self.putParamEvent(d)


########################################################################
class SniperWidget(AlgoWidget):
    """"""
    
    #----------------------------------------------------------------------
    def __init__(self, algoEngine, parent=None):
        """Constructor"""
        super(SniperWidget, self).__init__(algoEngine, parent)
        
        self.templateName = SniperAlgo.templateName
        
    #----------------------------------------------------------------------
    def initAlgoLayout(self):
        """"""
        self.lineVtSymbol = QtWidgets.QLineEdit()
        
        self.comboDirection = QtWidgets.QComboBox()
        self.comboDirection.addItem(DIRECTION_LONG)
        self.comboDirection.addItem(DIRECTION_SHORT)
        self.comboDirection.setCurrentIndex(0)
        
        doubleValidator = QtGui.QDoubleValidator()
        doubleValidator.setBottom(0)
        
        self.linePrice = QtWidgets.QLineEdit()
        self.linePrice.setValidator(doubleValidator)
        
        self.lineVolume = QtWidgets.QLineEdit()
        self.lineVolume.setValidator(doubleValidator)
        
        self.comboOffset = QtWidgets.QComboBox()
        self.comboOffset.addItems(['', OFFSET_OPEN, OFFSET_CLOSE])
        self.comboOffset.setCurrentIndex(0)
        
        buttonStart = QtWidgets.QPushButton(u'启动')
        buttonStart.clicked.connect(self.addAlgo)
        buttonStart.setMinimumHeight(100)
        
        Label = QtWidgets.QLabel
        
        grid = QtWidgets.QGridLayout()
        grid.addWidget(Label(u'代码'), 0, 0)
        grid.addWidget(self.lineVtSymbol, 0, 1)
        grid.addWidget(Label(u'方向'), 1, 0)
        grid.addWidget(self.comboDirection, 1, 1)
        grid.addWidget(Label(u'价格'), 2, 0)
        grid.addWidget(self.linePrice, 2, 1)
        grid.addWidget(Label(u'数量'), 3, 0)
        grid.addWidget(self.lineVolume, 3, 1)
        grid.addWidget(Label(u'开平'), 4, 0)
        grid.addWidget(self.comboOffset, 4, 1)
        
        return grid
    
    #----------------------------------------------------------------------
    def getAlgoSetting(self):
        """"""
        setting = OrderedDict()
        setting['templateName'] = self.templateName
        setting['vtSymbol'] = str(self.lineVtSymbol.text())
        setting['direction'] = text_type(self.comboDirection.currentText())
        setting['offset'] = text_type(self.comboOffset.currentText())
        
        priceText = self.linePrice.text()
        if not priceText:
            return
        setting['price'] = float(priceText)
        
        volumeText = self.lineVolume.text()
        if not volumeText:
            return
        setting['volume'] = float(volumeText)
        
        return setting
    
    
