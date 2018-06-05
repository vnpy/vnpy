# encoding: UTF-8

from __future__ import division
from collections import OrderedDict

from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT)
from vnpy.trader.uiQt import QtWidgets

from algoTemplate import AlgoTemplate


########################################################################
class TwapAlgo(AlgoTemplate):
    """TWAP算法"""
    
    name = 'TWAP'

    #----------------------------------------------------------------------
    def __init__(self, engine, setting, algoName):
        """Constructor"""
        super(TwapAlgo, self).__init__(engine, setting, algoName)
        
        # 参数
        self.vtSymbol = setting['vtSymbol']     # 合约代码
        self.direction = setting['direction']   # 买卖
        self.price = setting['price']           # 目标价格
        self.totalVolume = setting['volume']    # 总数量
        self.time = setting['time']             # 执行时间
        self.interval = setting['interval']     # 执行间隔
        self.minVolume = setting['minVolume']   # 最小委托数量
        
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
                if tick.bidPrice1 < self.price:
                    self.buy(self.vtSymbol, self.price, size)
                    self.writeLog(u'委托买入%s，数量%，价格%s' %(self.vtSymbol, self.orderSize, self.price))
            # 卖出
            if self.direction == DIRECTION_SHORT:
                # 市场卖1价大于目标价
                if tick.askPrice1 > self.price:
                    self.sell(self.vtSymbol, self.price, size)
                    self.writeLog(u'委托卖出%s，数量%s，价格%s' %(self.vtSymbol, self.orderSize, self.price))
        
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
        d[u'目标价格'] = self.price
        d[u'总数量'] = self.totalVolume
        d[u'总时间（秒）'] = self.time
        d[u'间隔（秒）'] = self.interval
        self.putParamEvent(d)



########################################################################
class TwapWidget(QtWidgets.QWidget):
    """"""
    name = TwapAlgo.name

    #----------------------------------------------------------------------
    def __init__(self, algoEngine):
        """Constructor"""
        super(TwapWidget, self).__init__()
        
        self.algoEngine = algoEngine
        
        self.initUi()
        
    #----------------------------------------------------------------------
    def initUi(self):
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
        grid.addWidget(Label(u'数量取整'), 6, 0)
        grid.addWidget(self.spinMinVolume, 6, 1)
        grid.addWidget(buttonStart, 7, 0, 1, 2)
        
        self.setLayout(grid)
    
    #----------------------------------------------------------------------
    def addAlgo(self):
        """"""
        setting = {
            'vtSymbol': str(self.lineSymbol.text()),
            'direction': str(self.comboDirection.currentText()),
            'price': float(self.spinPrice.value()),
            'volume': float(self.spinVolume.value()),
            'time': int(self.spinTime.value()),
            'interval': int(self.spinInterval.value()),
            'minVolume': float(self.spinMinVolume.value())
        }
        
        self.algoEngine.addAlgo(TwapAlgo.name, setting)
        
        
        
        
    
    