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
    # 进入目标价格前pre_pips个价格，开始挂单
    # 成交后，马上挂平仓单，
    # 若到达止损价，撤单，止损


    templateName = u'Sniper 狙击手'

    #----------------------------------------------------------------------
    def __init__(self, engine, setting, algoName):
        """Constructor"""
        super(SniperAlgo, self).__init__(engine, setting, algoName)

        # 参数，强制类型转换，保证从CSV加载的配置正确
        self.vtSymbol = str(setting['vtSymbol'])            # 合约代码
        self.direction = text_type(setting['direction'])    # 买卖
        self.pre_pips = float(setting['pre_pips'])          # 提前下单价格
        self.min_diff = float(setting.get('min_diff'))
        self.price = float(setting['price'])                # 价格
        self.volume = float(setting['volume'])              # 数量
        self.close_price = setting.get('close_price', None)
        self.stop_price = setting.get('stop_price', None)

        self.open_orders = []     # 开仓委托号
        self.close_orders = []    # 平仓委托号

        self.opened_volume = 0   # 成交数量
        self.closed_volume = 0   # 平仓数量

        self.subscribe(self.vtSymbol)
        self.paramEvent()
        self.varEvent()

        if self.close_price is None or self.stop_price is None:
            self.writeLog(u'平仓价格和止损价价格未设置')
            self.stop()

        self.close_price = float(self.close_price)
        self.stop_price = float(self.stop_price)

        if self.direction == DIRECTION_LONG:
            if not self.close_price > self.price > self.stop_price:
                self.writeLog(u'止盈止损价不合理')
                self.stop()
        if self.direction == DIRECTION_SHORT:
            if not self.close_price < self.price < self.stop_price:
                self.writeLog(u'止盈止损价不合理')
                self.stop()
    # ----------------------------------------------------------------------
    def onTick(self, tick):
        """"""
        # 执行开仓的撤单,存在委托开仓
        if len(self.open_orders) > 0 and self.opened_volume<=0 :
            if self.direction == DIRECTION_LONG and tick.bidPrice1 > self.price + self.min_diff * self.pre_pips:
                self.writeLog(u'当前价格bidPrice1:{}离开做多:{}的提前{}个跳,撤单:{}'
                              .format(tick.bidPrice1,self.price,self.pre_pips,self.open_orders))
                self.cancelAll()
                return

            if self.direction == DIRECTION_SHORT and tick.askPrice1 < self.price - self.min_diff * self.pre_pips:
                self.writeLog(u'当前价格askPrice1:{}离开做空:{}的提前{}个跳,撤单:{}'
                              .format(tick.askPrice1, self.price, self.pre_pips, self.open_orders))
                self.cancelAll()
                return

        self.check_stop(tick)

        self.pre_open(tick)

        # 更新变量
        self.varEvent()

    def pre_open(self, tick):
        """提前委托"""

        if len(self.close_orders) > 0:
            return

        # 做多，未有委托，进入价格区域
        if self.direction == DIRECTION_LONG \
                and len(self.open_orders) == 0 \
                and self.opened_volume == 0 \
                and self.price <= tick.bidPrice1 <= self.price + self.min_diff * self.pre_pips:

            buy_orderid = self.buy(self.vtSymbol, self.price,
                                   self.volume, offset=OFFSET_OPEN)
            if len(buy_orderid) > 0:
                self.writeLog(u'开多委托成功，委托编号:{}'.format(buy_orderid))
                self.open_orders.append(buy_orderid)
            else:
                self.writeLog(u'开多委托失败')
                self.stop()

        # 做空
        if self.direction == DIRECTION_SHORT \
                and len(self.open_orders) == 0 \
                and self.price >= tick.askPrice1 >= self.price - self.min_diff * self.pre_pips:

            short_orderid = self.sell(self.vtSymbol, self.price,
                                      self.volume, offset=OFFSET_OPEN)

            if len(short_orderid) > 0:
                self.writeLog(u'开空委托成功，委托编号:{}'.format(short_orderid))
                self.open_orders.append(short_orderid)
            else:
                self.writeLog(u'开空委托失败')
                self.stop()

    def check_stop(self, tick):
        """检查止损"""
        if self.opened_volume ==0:
            return

        # 持有多单，价格低于止损价
        if self.direction == DIRECTION_LONG \
                and tick.askPrice1 <= self.stop_price:
            if len(self.close_orders) > 0:
                self.writeLog(u'存在平仓委托，先撤单')
                self.cancelAll()
            else:
                self.writeLog(u'卖出平仓')
                orderid = self.sell(vtSymbol=self.vtSymbol,price=tick.askPrice1,volume=self.opened_volume,offset=OFFSET_CLOSE)
                if len(orderid) > 0:
                    self.close_orders.append(orderid)
                    self.writeLog(u'卖出平仓委托:{}'.format(self.close_orders))
                else:
                    self.writeLog(u'卖出平仓委托失败')

        # 持有空单，价格低于止损价
        if self.direction == DIRECTION_SHORT \
                and tick.bidPrice1 >= self.stop_price:
            if len(self.close_orders) > 0:
                self.writeLog(u'存在委托，先撤单')
                self.cancelAll()
            else:
                self.writeLog(u'买入平仓')
                orderid = self.buy(vtSymbol=self.vtSymbol, price=tick.askPrice1, volume=self.opened_volume,
                          offset=OFFSET_CLOSE)
                if len(orderid) > 0:
                    self.close_orders.append(orderid)
                    self.writeLog(u'买入平仓委托:{}'.format(self.close_orders))
                else:
                    self.writeLog(u'买入平仓委托失败')

    # ----------------------------------------------------------------------
    def onTrade(self, trade):
        """成交返回"""
        if trade.offset == OFFSET_OPEN:
            self.opened_volume += trade.volume
            self.close_pos(pos_direction=trade.direction, pos_volume=trade.volume)

        if trade.offset == OFFSET_CLOSE:
            self.closed_volume += trade.volume

        if self.closed_volume == self.opened_volume:
            self.writeLog(u'平仓完成，停止算法')
            self.stop()
        else:
            if self.closed_volume < self.opened_volume and len(self.close_orders) == 0:
                self.writeLog(u'存在开平仓差:开仓{},已平:{}，继续发出平仓指令'.format(self.opened_volume,self.closed_volume))
                self.close_pos(pos_direction=self.direction,pos_volume=self.opened_volume - self.closed_volume)

        self.varEvent()

    def close_pos(self,pos_direction, pos_volume):
        # 马上发送委托平仓单
        if pos_direction == DIRECTION_LONG:
            close_orderid = self.sell(vtSymbol=self.vtSymbol,
                                      price=self.close_price,
                                      volume=pos_volume,
                                      offset=OFFSET_CLOSE)

            if len(close_orderid) > 0:
                self.writeLog(u'卖出平仓成功,价格:{},数量:{},委托单号:{}'
                              .format(self.close_price, pos_volume, close_orderid))
                self.close_orders.append(close_orderid)
            else:
                self.writeLog(u'卖出平仓委托失败')

        elif pos_direction == DIRECTION_SHORT:
            close_orderid = self.buy(vtSymbol=self.vtSymbol,
                                     price=self.close_price,
                                     volume=pos_volume,
                                     offset=OFFSET_CLOSE)

            if len(close_orderid) > 0:
                self.writeLog(u'买入平仓成功,价格:{},数量:{},委托单号:{}'
                              .format(self.close_price, pos_volume, close_orderid))
                self.close_orders.append(close_orderid)
            else:
                self.writeLog(u'买入平仓委托失败')

    # ----------------------------------------------------------------------
    def onOrder(self, order):
        """"""
        # 开仓撤单
        if order.status == STATUS_CANCELLED and order.offset == OFFSET_OPEN:
            self.writeLog(u'{}开仓撤单成功'.format(order.orderID))
            if order.orderID in self.open_orders:
                self.open_orders.remove(order.orderID)
                self.writeLog(u'剩余委托单{}'.format(self.open_orders))
            return

        if order.status == STATUS_CANCELLED and order.offset == OFFSET_CLOSE:
            self.writeLog(u'{}平仓撤单成功'.format(order.orderID))
            if order.orderID in self.close_orders:
                self.close_orders.remove(order.orderID)
                self.writeLog(u'剩余委托单{}'.format(self.open_orders))
            return

        if order.status == STATUS_ALLTRADED and order.offset == OFFSET_OPEN:
            self.writeLog(u'开仓委托 {} 执行完成'.format(order.orderID))
            if order.orderID in self.open_orders:
                self.open_orders.remove(order.orderID)
                self.writeLog(u'剩余开仓委托单{}'.format(self.open_orders))

        if order.status == STATUS_ALLTRADED and order.offset == OFFSET_CLOSE:
            self.writeLog(u'平仓委托 {} 执行完成'.format(order.orderID))
            if order.orderID in self.close_orders:
                self.close_orders.remove(order.orderID)
                self.writeLog(u'剩余平仓委托单{}'.format(self.close_orders))

        self.varEvent()

    # ----------------------------------------------------------------------
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
        d[u'开仓委托号'] = self.open_orders
        d[u'开仓数量'] = self.opened_volume
        d[u'平仓委托号'] = self.close_orders
        d[u'平仓数量'] = self.closed_volume

        self.putVarEvent(d)

    #----------------------------------------------------------------------
    def paramEvent(self):
        """更新参数"""
        d = OrderedDict()
        d[u'代码'] = self.vtSymbol
        d[u'方向'] = self.direction
        d[u'价格'] = self.price
        d[u'数量'] = self.volume
        d[u'提前跳'] = self.pre_pips
        d[u'止盈价'] = self.close_price
        d[u'止损价'] = self.stop_price
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

        self.comboClosePips = QtWidgets.QComboBox()
        self.comboClosePips.addItems(['2', '3', '4', '5', '6', '7', '8', '9'])
        self.comboClosePips.setCurrentIndex(4)
        self.comboStopPips =QtWidgets.QComboBox()
        self.comboStopPips.addItems(['2', '3', '4', '5', '6', '7', '8', '9'])
        self.comboStopPips.setCurrentIndex(2)

        self.lineVolume = QtWidgets.QLineEdit()
        self.lineVolume.setValidator(doubleValidator)

        self.comboPrePips = QtWidgets.QComboBox()
        self.comboPrePips.addItems(['2', '3', '4', '5', '6', '7', '8', '9'])
        self.comboPrePips.setCurrentIndex(0)

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
        grid.addWidget(Label(u'提前跳'), 4, 0)
        grid.addWidget(self.comboPrePips, 4, 1)
        grid.addWidget(Label(u'止盈跳'), 5, 0)
        grid.addWidget(self.comboClosePips, 5, 1)
        grid.addWidget(Label(u'止损跳'), 6, 0)
        grid.addWidget(self.comboStopPips, 6, 1)

        return grid

    #----------------------------------------------------------------------
    def getAlgoSetting(self):
        """"""
        setting = OrderedDict()
        setting['templateName'] = SniperAlgo.templateName
        setting['vtSymbol'] = str(self.lineVtSymbol.text())
        setting['direction'] = text_type(self.comboDirection.currentText())
        setting['pre_pips'] = text_type(self.comboPrePips.currentText())
        close_pips = text_type(self.comboClosePips.currentText())
        stop_pips = text_type(self.comboStopPips.currentText())

        contract = self.algo_engine.getContract(SniperAlgo.templateName, setting['vtSymbol'])
        if contract is None:
            print(u'can not find contract')
            return
        setting['min_diff'] = contract.priceTick
        priceText = self.linePrice.text()
        if not priceText:
            return
        setting['price'] = float(priceText)

        volumeText = self.lineVolume.text()
        if not volumeText:
            return
        setting['volume'] = float(volumeText)

        if setting['direction'] == DIRECTION_LONG:
            setting['close_price'] = setting['price'] + int(close_pips) * setting['min_diff']
            setting['stop_price'] = setting['price'] - int(stop_pips) * setting['min_diff']
        if setting['direction'] == DIRECTION_SHORT:
            setting['close_price'] = setting['price'] - int(close_pips) * setting['min_diff']
            setting['stop_price'] = setting['price'] + int(stop_pips) * setting['min_diff']
        return setting


