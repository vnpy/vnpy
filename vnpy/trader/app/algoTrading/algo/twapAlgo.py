# encoding: UTF-8

from __future__ import division
from collections import OrderedDict
from datetime import datetime, timedelta
from six import text_type
import copy
from time import sleep
from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT)
from vnpy.trader.uiQt import QtWidgets
from vnpy.trader.app.algoTrading.algoTemplate import *
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
        self.offset = setting.get('offset', None)
        self.target_price = float(setting['target_price'])    # 目标价格
        self.total_volume = float(setting.get('total_volume', 1))    # 总数量
        self.total_seconds = int(setting.get('total_seconds', 120))   # 执行时间,120秒
        self.interval = int(setting.get('interval', 10))            # 执行时间间隔，10秒
        self.min_volume = float(setting.get('min_volume', 1))        # 最小委托数量
        self.price_level = int(setting.get('price_level', 1))        # 使用第几档价格委托

        # 变量
        self.order_size = self.total_volume / (self.total_seconds / self.interval)
        self.order_size = max(self.roundValue(self.order_size, self.min_volume), self.min_volume)
        if self.min_volume >= 1:
            self.order_size = int(self.order_size)

        self.timer_count = 0
        self.timer_total = 0

        # 已成交数量/均价
        self.traded_volume = 0
        self.traded_price = 0

        # 订阅合约
        self.subscribe(self.vtSymbol)

        self.plan_name = setting.get('plan_name','')
        self.plan_id = setting.get('plan_id','')
        self.plan_start_time = setting.get('plan_start_time','')
        if len(self.plan_start_time) == 0:
            self.plan_start_time = copy.copy(self.start_time)
        self.plan_stop_time = (datetime.now() + timedelta(seconds=self.total_seconds)).strftime('%Y-%m-%d %H:%M:%S')
        if self.direction == DIRECTION_LONG:
            self.plan_buy_volume = self.total_volume
            self.plan_buy_price = self.target_price
        else:
            self.plan_sell_volume = self.total_volume
            self.plan_sell_price = self.target_price

        # 推送参数/变量事件
        self.paramEvent()
        self.varEvent()

    #----------------------------------------------------------------------
    def onTick(self, tick):
        """"""
        pass

    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """成交事件处理"""

        # 平均成交成本计算
        traded_amount = self.traded_price * self.traded_volume + trade.price * trade.volume
        self.traded_volume += trade.volume
        self.traded_price = traded_amount / self.traded_volume

        # 更新交易数量和交易价格
        if self.direction == DIRECTION_LONG:
            self.buy_volume = self.traded_volume
            self.buy_price = self.traded_price
        else:
            self.sell_volume = self.traded_volume
            self.sell_price = self.traded_price

        # 目标达到，完成算法实例
        if self.traded_volume >= self.total_volume:
            self.progress = 100
            self.writeLog(u'目标达到，算法结束')
            self.varEvent()
            sleep(1)
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
        self.timer_count += 1
        self.timer_total += 1

        if self.total_volume > 0:
            self.progress = int(self.traded_volume * 100 / self.total_volume)

        if self.direction == DIRECTION_LONG:
            self.buy_volume = self.traded_volume
            self.buy_price = self.traded_price
        else:
            self.sell_volume = self.traded_volume
            self.sell_price = self.traded_price

        # 总时间结束，停止算法
        if self.timer_total >= self.total_seconds:
            if self.total_volume > 0:
                self.progress = int(self.traded_volume * 100 / self.total_volume)

            self.writeLog(u'{}运行时间结束'.format(self.algoName))
            self.stop()
            return

        # 每到间隔发一次委托
        if self.timer_count >= self.interval:
            self.timer_count = 0

            tick = self.getTick(self.vtSymbol)
            if not tick:
                self.status = RUNNING_WRONG
                self.error_msg = u'接口获取不到{}的行情信息'.format(self.vtSymbol)
                self.writeError(self.error_msg)
                return
            if self.status in [RUNNING_WRONG, RUNNING_NORMAL]:
                self.status = RUNNING_ACTIVE

            size = min(self.order_size, self.total_volume - self.traded_volume)

            # 买入
            if self.direction == DIRECTION_LONG:
                # 市场买1价小于目标买价
                if tick.bidPrice1 < self.target_price:
                    # 计算委托价格
                    priceMap = {
                        1: tick.askPrice1,
                        2: tick.askPrice2,
                        3: tick.askPrice3,
                        4: tick.askPrice4,
                        5: tick.askPrice5,
                    }
                    price = priceMap[self.price_level]
                    if price > 0:
                        price = min(price, self.target_price)  # 如果深度价格为0，则使用目标价
                    else:
                        price = self.target_price

                    # 发出委托
                    self.buy(self.vtSymbol, price, size, offset=self.offset)
                    self.writeLog(u'委托买入%s，数量%s，价格%s' %(self.vtSymbol, size, price))
                else:
                    self.writeLog(u'市场价格{}不满足买入价：{}'.format(tick.bidPrice1 , self.target_price))
            # 卖出
            if self.direction == DIRECTION_SHORT:
                # 市场卖1价大于目标价
                if tick.askPrice1 > self.target_price:
                    # 计算委托价格
                    priceMap = {
                        1: tick.bidPrice1,
                        2: tick.bidPrice2,
                        3: tick.bidPrice3,
                        4: tick.bidPrice4,
                        5: tick.bidPrice5,
                    }
                    price = priceMap[self.price_level]
                    if price > 0:
                        price = max(price, self.target_price)
                    else:
                        price = self.target_price

                    # 发出委托
                    self.sell(self.vtSymbol, price, size,offset=self.offset)
                    self.writeLog(u'委托卖出%s，数量%s，价格%s' %(self.vtSymbol, size, price))
                else:
                    self.writeLog(u'市场价格{}不满足买入价：{}'.format(tick.askPrice1, self.target_price))

        # 委托后等待到间隔一半的时间撤单
        elif self.timer_count == round(self.interval / 2, 0):
            result = self.cancelAll()
            if result:
                self.writeLog(u'撤销之前的委托')

        self.varEvent()

    #----------------------------------------------------------------------
    def onStop(self):
        """"""
        self.writeLog(u'响应停止要求，停止算法')
        self.varEvent()

    #----------------------------------------------------------------------
    def varEvent(self):
        """更新变量"""
        d = OrderedDict()
        d[u'算法状态'] = self.active
        d[u'成交数量'] = self.traded_volume
        d[u'单笔委托'] = self.order_size
        d[u'本轮读秒'] = self.timer_count
        d[u'累计读秒'] = self.timer_total
        d['active'] = self.active
        self.putVarEvent(d)

    #----------------------------------------------------------------------
    def paramEvent(self):
        """更新参数"""
        d = OrderedDict()
        d[u'代码'] = self.vtSymbol
        d[u'方向'] = self.direction
        d[u'目标价格'] = self.target_price
        d[u'总数量'] = self.total_volume
        d[u'总时间（秒）'] = self.total_seconds
        d[u'间隔（秒）'] = self.interval
        d[u'委托档位'] = self.price_level
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
        setting['target_price'] = float(self.spinPrice.value())
        setting['totalVolume'] = float(self.spinVolume.value())
        setting['time'] = int(self.spinTime.value())
        setting['interval'] = int(self.spinInterval.value())
        setting['priceLevel'] = int(self.spinPriceLevel.value())
        setting['minVolume'] = float(self.spinMinVolume.value())

        return setting


