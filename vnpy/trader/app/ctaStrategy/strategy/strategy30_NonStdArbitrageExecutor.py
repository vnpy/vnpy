# encoding: UTF-8

# 首先写系统内置模块
import sys
import os
from datetime import datetime, timedelta, date
from time import sleep
import copy
import logging

# 第三方模块
import talib as ta
import math
import numpy
import requests
import execjs
import pykalman

# vntrader基础模块
from vnpy.trader.vtConstant import EMPTY_STRING, EMPTY_INT, DIRECTION_LONG, DIRECTION_SHORT, OFFSET_OPEN,OFFSET_CLOSE,OFFSET_CLOSETODAY,OFFSET_CLOSEYESTERDAY, STATUS_CANCELLED

# 然后CTA模块
from vnpy.trader.app.ctaStrategy.ctaTemplate import *
from vnpy.trader.app.ctaStrategy.ctaBase import *
from vnpy.trader.app.ctaStrategy.ctaPolicy import *
from vnpy.trader.app.ctaStrategy.ctaLineBar import *
from vnpy.trader.app.ctaStrategy.ctaPosition import *
from vnpy.trader.app.ctaStrategy.ctaGridTrade import *

cta_engine_path = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))

######################################from##################################
class Strategy30(CtaTemplate):
    """非标准合约的协整套利+网格交易执行器
    只接受外部界面的Grid输入

    配置参考
        {
          "name": "S28_螺纹钢跨期套利",
          "className": "Strategy28",
          "vtSymbol": "rb1705;rb1710",
          "symbol": "rb1705;rb1710",
          "shortSymbol":"RB",
          "Leg1Symbol":"rb1705",
          "Leg2Symbol":"rb1710",
          "baseUpLine":240,
          "baseMidLine":0,
          "baseDnLine":-240,
          "minDiff":1,
          "inputSS":1,
          "height":5,
          "win":10,
          "maxPos":4,
          "maxLots":4,
          "deadLine":"2017-4-20",
          "mode":"tick"
        }

    """
    className = 'Strategy30'
    author = u'李来佳'

    # 策略在外部设置的参数
    inputSS = 1                # 参数SS，下单，范围是1~100，步长为1，默认=1，
    minDiff = 1                # 商品的最小交易单位
    maxPos = 10                # 最大仓位（网格）数量

#----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting=None):
        """Constructor"""
        super(Strategy30, self).__init__(ctaEngine, setting)

        self.paramList.append('inputSS')
        self.paramList.append('Leg1Symbol')       # 近期合约
        self.paramList.append('Leg2Symbol')       # 远期合约
        self.paramList.append('minDiff')
        self.paramList.append('maxPos')
        self.paramList.append('maxLots')
        self.paramList.append('height')           #
        self.paramList.append('win')
        self.paramList.append('baseUpLine')
        self.paramList.append('baseMidLine')    # 基准中轴
        self.paramList.append('baseDnLine')

        #self.varList.remove('pos')
        self.varList.append('gridpos')
        self.varList.append('entrust')
        self.varList.append('upGrids')
        self.varList.append('dnGrids')
        self.varList.append('tradingOpen')

        self.cancelSeconds = 2                  # 未成交撤单的秒数

        self.curDateTime = None                 # 当前Tick时间
        self.curTick = None                     # 最新的tick

        self.Leg1Symbol = EMPTY_STRING
        self.Leg2Symbol = EMPTY_STRING
        self.lastLeg1Tick = None
        self.lastLeg2Tick = None

        self.firstTrade = True                  # 交易日的首个交易

        # 交易窗口
        self.tradeWindow = False
        # 开市窗口
        self.openWindow = False
        # 收市平仓窗口
        self.closeWindow = False

        # 仓位状态
        self.position = CtaPosition(self)       # 0 表示没有仓位，1 表示持有多头，-1 表示持有空头
        self.position.maxPos = self.maxPos
        self.gridpos = 0
        self.lastTradedTime = datetime.now()    # 上一交易时间

        self.tradingOpen = True                 # 允许开仓
        self.recheckPositions = True

        self.forceClose = EMPTY_STRING  # 强制平仓的日期（参数，字符串）
        self.forceCloseDate = None  # 强制平仓的日期（日期类型）
        self.forceTradingClose = False          # 强制平仓标志

        # 是否完成了策略初始化
        self.inited = False

        self.backtesting = False

        # 初始化时读取的历史数据的起始日期(可以选择外部设置)
        self.startDate = None
        self.policy = CtaPolicy()               # 成交后的执行策略

        self.recheckPositions = True              # 重新提交平仓订单。在每个交易日的下午14点59分时激活，在新的交易日（21点）开始时，重新执行。

        self.volumeList = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
        self.height = 4
        self.win = 4
        self.upGrids = EMPTY_STRING          # 做空网格的显示字符串
        self.dnGrids = EMPTY_STRING          # 做多网格的显示字符串
        self.sigle_exist = False              # 是否一次性全平仓
#
        self.baseUpLine = EMPTY_INT             # 网格做空起步线
        self.baseMidLine = EMPTY_INT         # 基准中轴线，区分多空
        self.baseDnLine = EMPTY_INT             # 网格做多起步线

        self.upRate = 1                      # 做空网格间距放大比率
        self.dnRate = 1                      # 做多网格间距放大比率
        self.rebuildUpGrid = False           # 重建网格标志
        self.rebuildDnGrid = False           # 重建网格标志
        self.rebuildGrid = False             # 分钟触发重建网格

        self.maxLots = 10                       # 网格的最大数量#

        self.logMsg = EMPTY_STRING              # 临时输出日志变量


        if setting:

            # 根据配置文件更新参数
            self.setParam(setting)

        self.onInit()

    #----------------------------------------------------------------------
    def onInit(self, force = False):
        """初始化       
        """
        if force:
            self.writeCtaLog(u'策略强制初始化')
            self.inited = False
            self.trading = False                        # 控制是否启动交易
        else:
            self.writeCtaLog(u'策略初始化')
            if self.inited:
                self.writeCtaLog(u'已经初始化过，不再执行')
                return

        # 初始化持仓相关数据
        self.position.pos = EMPTY_INT
        self.pos = self.position.pos
        self.gridpos = self.position.pos
        self.position.maxPos = self.maxPos

        # 初始化网格
        self.gridHeight = self.height * self.minDiff      # 网格距离跳数*每跳高度
        self.gridWin = self.win * self.minDiff            # 止盈跳数*每跳高度

        if self.baseUpLine == EMPTY_INT:
            self.writeCtaLog(u'初始化baseUpLine为空，缺省设置为50个MinDiff')
            self.baseUpLine = 9999 * self.minDiff         # 网格做空起步线
        if self.baseDnLine == EMPTY_INT:
            self.writeCtaLog(u'baseDnLine，缺省设置为-50个MinDiff')
            self.baseDnLine = -9999 * self.minDiff        # 网格做多起步线

        self.upLine = self.baseUpLine                   # 网格做空的上轨
        self.dnLine = self.baseDnLine                   # 网格做多的下轨

        # 创建网格交易策略
        self.gt = CtaGridTrade(strategy=self, maxlots=self.maxLots, height=self.gridHeight, win=self.gridWin,
                               vol=self.inputSS, minDiff=self.minDiff)
        # 更新网格仓位策略
        if self.volumeList:
            self.gt.volumeList = self.volumeList
        else:
            self.gt.volumeList = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]


        # 初始化网格交易器（或从本地记录文件中获取）
        self.__initGrids()

        # 更新初始化标识和交易标识
        self.inited = True
        self.trading = True                             # 控制是否启动交易
        self.recheckPositions = True

        self.putEvent()
        self.writeCtaLog(u'策略初始化完成')

    def onStart(self):
        """启动策略（必须由用户继承实现）"""
        self.writeCtaLog(u'启动')
        self.trading = True

    #----------------------------------------------------------------------
    def onStop(self):
        """停止策略（必须由用户继承实现）"""
        self.uncompletedOrders.clear()
        self.recheckPositions = True

        self.position.clear()
        self.gridpos = self.position.pos
        self.entrust = 0

        self.writeCtaLog(u'保存下网格')
        self.gt.save(direction=DIRECTION_LONG)
        self.writeCtaLog(u'保存上网格')
        self.gt.save(direction=DIRECTION_SHORT)

        self.trading = False
        self.writeCtaLog(u'停止' )
        self.putEvent()

    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """交易更新"""
        self.writeCtaLog(u'{0},OnTrade(),当前持仓：{1} '.format(self.curDateTime, self.position.pos))

    #----------------------------------------------------------------------
    def onOrder(self, order):
        """报单更新"""
        self.writeCtaLog(u'OnOrder()报单更新，orderID:{0},{1},totalVol:{2},tradedVol:{3},offset:{4},price:{5},direction:{6},status:{7}'
                         .format(order.orderID, order.vtSymbol, order.totalVolume,order.tradedVolume,
                                 order.offset, order.price, order.direction, order.status))

        orderkey = order.gatewayName+u'.'+order.orderID

        if orderkey in self.uncompletedOrders:

            if order.totalVolume == order.tradedVolume:
                # 开仓，平仓委托单全部成交
                self.__onOrderAllTraded(order)

            elif order.tradedVolume > 0 and not order.totalVolume == order.tradedVolume :
                # 委托单部分成交
                self.__onOrderPartTraded(order)

            elif order.offset == OFFSET_OPEN and order.status == STATUS_CANCELLED:
                # 开仓委托单被撤销
                pass

            else:
                self.writeCtaLog(u'OnOrder()委托单返回，total:{0},traded:{1}'
                                 .format(order.totalVolume, order.tradedVolume,))

        self.__updateGridsDisplay()
        self.pos = self.position.pos
        self.gridpos = self.position.pos
        self.writeCtaLog(u'OnOrder()self.gridpos={0}'.format(self.gridpos))
        self.putEvent()

    def __onOrderAllTraded(self, order):
        """订单的所有成交事件"""
        self.writeCtaLog(u'onOrderAllTraded(),{0},委托单全部完成'.format(order.orderTime ))
        orderkey = order.gatewayName+u'.'+order.orderID

        # 平空仓完成(cover)
        if self.uncompletedOrders[orderkey]['DIRECTION'] == DIRECTION_LONG and order.offset != OFFSET_OPEN:
            # 通过orderID，找到对应的网格
            grid = self.uncompletedOrders[orderkey]['Grid']

            if grid is not None:
                orders = grid.orderRef.split(';')
                if len(orders) == 2 and orderkey in orders:
                    self.writeCtaLog(u'更新网格:closePrice={0}的{1}平空'.format(grid.closePrice, order.vtSymbol))
                    orders.remove(orderkey)
                    grid.orderRef = orders[0]
                elif len(orders) == 1 and orderkey in orders:
                    self.writeCtaLog(u'更新网格:closePrice={0}的{1}平空'.format(grid.closePrice, order.vtSymbol))
                    grid.orderRef = EMPTY_STRING
                    grid.orderStatus = False
                    grid.openStatus = False
                    grid.closeStatus = False
                    grid.tradedVolume = EMPTY_INT
                    grid.openDatetime = EMPTY_STRING
                    # 更新仓位
                    direction = grid.direction
                    if direction == DIRECTION_LONG:
                        self.writeCtaLog(u'更新仓位，正套网格平多仓{0}手'.format(grid.volume))
                        self.position.closePos(DIRECTION_SHORT, vol=grid.volume)
                        self.writeCtaLog(u'移除网格{0},{1}'.format(grid.direction, grid.openPrice))
                        self.gt.dnGrids.remove(grid)
                    else:
                        self.writeCtaLog(u'更新仓位，反套网格平空仓{0}手'.format(grid.volume))
                        self.position.closePos(DIRECTION_LONG, vol=grid.volume)
                        self.writeCtaLog(u'移除网格{0},{1}'.format(grid.direction, grid.openPrice))
                        self.gt.upGrids.remove(grid)
                    self.entrust = 0
                    self.gridpos = self.position.pos
                    self.gt.save(direction=direction)


                else:
                    self.writeCtaLog(u'异常，orderRef:{0}对应的网格内，Ref字段:{1}'.format(orderkey, grid.orderRef))
            else:
                self.writeCtaLog(u'异常，找不到orderRef:{0}对应的网格'.format(orderkey))

        # 平多仓完成(sell)
        if self.uncompletedOrders[orderkey]['DIRECTION'] == DIRECTION_SHORT and order.offset != OFFSET_OPEN:
            # 通过orderID，找到对应的网格
            grid = self.uncompletedOrders[orderkey]['Grid']
            if grid is not None:
                orders = grid.orderRef.split(';')
                if len(orders) == 2 and orderkey in orders:
                    self.writeCtaLog(u'更新网格:closePrice={0}的{1}平多'.format(grid.closePrice, order.vtSymbol))
                    orders.remove(orderkey)
                    grid.orderRef = orders[0]
                elif len(orders) == 1 and orderkey in orders:
                    self.writeCtaLog(u'更新网格:closePrice={0}的{1}平多'.format(grid.closePrice, order.vtSymbol))
                    grid.orderRef = EMPTY_STRING
                    grid.orderStatus = False
                    grid.openStatus = False
                    grid.closeStatus = False
                    grid.tradedVolume = EMPTY_INT
                    grid.openDatetime = EMPTY_STRING
                    # 更新仓位
                    direction = grid.direction
                    if direction == DIRECTION_LONG: # 网格的开仓方向是开多
                        self.writeCtaLog(u'更新仓位，正套网格平多仓{0}手'.format(grid.volume))
                        self.position.closePos(DIRECTION_SHORT, vol=grid.volume)
                        self.writeCtaLog(u'移除网格{0},{1}'.format(grid.direction,grid.openPrice))
                        self.gt.dnpGrids.remove(grid)
                    else:                           # 网格的开仓方向是开空
                        self.writeCtaLog(u'更新仓位，反套网格平空仓{0}手'.format(grid.volume))
                        self.position.closePos(DIRECTION_LONG, vol=grid.volume)
                        self.writeCtaLog(u'移除网格{0},{1}'.format(grid.direction, grid.openPrice))
                        self.gt.upGrids.remove(grid)
                    self.gridpos = self.position.pos
                    self.entrust = 0
                    self.gt.save(direction=direction)

                else:
                    self.writeCtaLog(u'异常，orderRef:{0}对应的网格内，Ref字段:{1}'.format(orderkey, grid.orderRef))
            else:
                self.writeCtaLog(u'异常，找不到orderRef:{0}对应的网格'.format(orderkey))

        # 开多仓完成
        if self.uncompletedOrders[orderkey]['DIRECTION'] == DIRECTION_LONG and order.offset == OFFSET_OPEN:
            self.writeCtaLog(u'{0}开多仓完成'.format(order.vtSymbol))
            # 通过orderID，找到对应的网格
            grid = self.uncompletedOrders[orderkey]['Grid']

            if grid is not None:
                orders = grid.orderRef.split(';')
                if len(orders) == 2 and orderkey in orders:
                    self.writeCtaLog(u'更新网格:Grid.OpenPrice={0}的{1}开多{2}'.format(grid.openPrice, order.vtSymbol, order.price))
                    orders.remove(orderkey)
                    grid.orderRef = orders[0]
                elif len(orders) == 1 and orderkey in orders:
                    self.writeCtaLog(u'更新网格:Grid.OpenPrice={0}的{1}开多{2}'.format(grid.openPrice, order.vtSymbol, order.price))
                    grid.orderRef = EMPTY_STRING
                    grid.openStatus = True
                    grid.orderStatus = False
                    grid.openDatetime = self.curDateTime
                    # 更新仓位
                    self.writeCtaLog(u'更新仓位，网格{0}仓{1}手'.format(grid.direction, grid.volume))
                    self.position.openPos(grid.direction, vol=grid.volume, price=grid.openPrice)
                    self.pos = self.position.pos
                    self.gridpos = self.position.pos
                    self.entrust = 0

                else:
                    self.writeCtaLog(u'异常，orderRef:{0}对应的网格内，Ref字段:{1}'.format(orderkey, grid.orderRef))

                direction = grid.direction
                self.gt.save(direction=direction)
            else:
                self.writeCtaLog(u'异常，找不到orderRef:{0}对应的网格'.format(orderkey))

        # 开空仓完成
        if self.uncompletedOrders[orderkey]['DIRECTION'] == DIRECTION_SHORT and order.offset == OFFSET_OPEN:
            self.writeCtaLog(u'开空仓完成'.format(order.vtSymbol))
            # 通过orderID，找到对应的网格
            grid = self.uncompletedOrders[orderkey]['Grid']

            if grid is not None:
                orders = grid.orderRef.split(';')
                if len(orders) == 2 and orderkey in orders:
                    self.writeCtaLog(u'更新网格:Grid.OpenPrice={0}的{1}开空{2}'.format(grid.openPrice, order.vtSymbol,order.price))
                    orders.remove(orderkey)
                    grid.orderRef = orders[0]
                elif len(orders) == 1 and orderkey in orders:
                    self.writeCtaLog(u'更新网格:Grid.OpenPrice={0}的{1}开空{2}'.format(grid.openPrice, order.vtSymbol,order.price))
                    grid.orderRef = EMPTY_STRING
                    grid.orderStatus = False
                    grid.openStatus = True
                    grid.openDatetime = self.curDateTime
                    # 更新仓位
                    self.writeCtaLog(u'更新仓位，网格{0}仓{1}手'.format(grid.direction, grid.volume))
                    self.position.openPos(grid.direction, vol=grid.volume, price=grid.openPrice)
                    self.pos = self.position.pos
                    self.gridpos = self.position.pos
                    self.entrust = 0
                else:
                    self.writeCtaLog(u'异常，orderRef:{0}对应的网格内，Ref字段:{1}'.format(orderkey, grid.orderRef))

                direction = grid.direction
                self.gt.save(direction=direction)

            else:
                self.writeCtaLog(u'异常，找不到orderRef:{0}对应的网格'.format(orderkey))
        try:
            del self.uncompletedOrders[orderkey]
        except Exception as ex:
            self.writeCtaLog(u'onOrder uncompletedOrders中找不到{0}'.format(orderkey))
        self.__updateGridsDisplay()

    def __onOrderPartTraded(self, order):
        """订单部分成交"""
        self.writeCtaLog(u'onOrderPartTraded(),{0},委托单部分完成'.format(order.orderTime ))
        orderkey = order.gatewayName+u'.'+order.orderID
        if orderkey in self.uncompletedOrders:
            self.uncompletedOrders[orderkey]['TradedVolume'] = order.tradedVolume
        else:
            self.writeCtaLog(u'异常，找不到委托单:{0}'.format(orderkey))

        self.__updateGridsDisplay()
    def __onOpenOrderCanceled(self, order):
        """委托开仓单撤销"""
        self.writeCtaLog(u'__onOpenOrderCanceled(),{0},委托开仓单已撤销'.format(order.orderTime ))

        orderkey = order.gatewayName+u'.'+order.orderID

        if self.uncompletedOrders[orderkey]['DIRECTION'] == DIRECTION_LONG :
            # 更新网格交易器
            updateGrid = self.gt.getGrid(direction=DIRECTION_LONG, openPrice=order.price,
                                         orderRef=order.orderID, t=u'OpenPrice')
            if type(updateGrid)!=type(None):
                self.writeCtaLog(u'更新网格[{0}]的状态为开多仓撤销'.format(updateGrid.openPrice))
                updateGrid.openStatus = False
                updateGrid.openDatetime = EMPTY_STRING
            else:
                self.writeCtaLog(u'异常，找不到网格[{0}]'.format(order.price))

            self.gt.save(direction=DIRECTION_LONG)

        if self.uncompletedOrders[orderkey]['DIRECTION'] == DIRECTION_SHORT :

            # 更新网格交易器
            updateGrid = self.gt.getGrid(direction=DIRECTION_SHORT, openPrice=order.price,
                                         orderRef=order.orderID, t=u'OpenPrice')
            if type(updateGrid)!=type(None):
                self.writeCtaLog(u'更新网格[{0}]的状态为开空仓撤销'.format(updateGrid.openPrice))
                updateGrid.openStatus = False
                updateGrid.openDatetime = EMPTY_STRING
            else:
                self.writeCtaLog(u'异常，找不到网格[{0}]'.format(order.price))

            self.gt.save(direction=DIRECTION_SHORT)

        self.__updateGridsDisplay()

    # ----------------------------------------------------------------------
    def onStopOrder(self, orderRef):
        """停止单更新"""
        self.writeCtaLog(u'{0},停止单触发，orderRef:{1}'.format(self.curDateTime, orderRef))
        pass

    # ----------------------------------------------------------------------
    def __combineTick(self, tick):
        """合并两腿合约，成为套利合约"""

        combinable = False

        if tick.vtSymbol == self.Leg1Symbol:
            # leg1合约
            self.lastLeg1Tick = tick
            if self.lastLeg2Tick is not None:
                if self.lastLeg1Tick.datetime == self.lastLeg2Tick.datetime:
                    combinable = True
        elif tick.vtSymbol == self.Leg2Symbol:
            # leg2合约
            self.lastLeg2Tick = tick
            if self.lastLeg1Tick is not None:
                if self.lastLeg2Tick.datetime == self.lastLeg1Tick.datetime:
                    combinable = True

        # 不能合并
        if not combinable:
            return None

        spread_tick = CtaTickData()
        spread_tick.vtSymbol = self.vtSymbol
        spread_tick.symbol = self.symbol

        spread_tick.datetime = tick.datetime
        spread_tick.date = tick.date
        spread_tick.time = tick.time

        # 以下情况，基本为单腿涨跌停，不合成价差Tick
        if (self.lastLeg1Tick.askPrice1 == float('1.79769E308') or self.lastLeg1Tick.askPrice1 == 0 or self.lastLeg1Tick.bidPrice1 == self.lastLeg1Tick.upperLimit) and self.lastLeg1Tick.askVolume1 == 0:
            self.writeCtaLog(u'leg1:{0}涨停{1}，不合成价差Tick'.format(self.lastLeg1Tick.vtSymbol,self.lastLeg1Tick.bidPrice1))
            return None
        if (self.lastLeg1Tick.bidPrice1 == float('1.79769E308') or self.lastLeg1Tick.bidPrice1 == 0 or self.lastLeg1Tick.askPrice1 == self.lastLeg1Tick.lowerLimit) and self.lastLeg1Tick.bidVolume1 == 0:
            self.writeCtaLog(u'leg1:{0}跌停{1}，不合成价差Tick'.format(self.lastLeg1Tick.vtSymbol, self.lastLeg1Tick.askPrice1))
            return None
        if (self.lastLeg2Tick.askPrice1 == float('1.79769E308') or self.lastLeg2Tick.askPrice1 == 0 or self.lastLeg2Tick.bidPrice1 == self.lastLeg2Tick.upperLimit) and self.lastLeg2Tick.askVolume1 == 0:
            self.writeCtaLog(u'leg2:{0}涨停{1}，不合成价差Tick'.format(self.lastLeg2Tick.vtSymbol, self.lastLeg2Tick.bidPrice1))
            return None
        if (self.lastLeg2Tick.bidPrice1 == float('1.79769E308') or self.lastLeg2Tick.bidPrice1 == 0 or self.lastLeg2Tick.askPrice1 == self.lastLeg2Tick.lowerLimit) and self.lastLeg2Tick.bidVolume1 == 0:
            self.writeCtaLog(u'leg2:{0}跌停{1}，不合成价差Tick'.format(self.lastLeg2Tick.vtSymbol, self.lastLeg2Tick.askPrice1))
            return None

        # 叫卖价差=leg1.askPrice1 - leg2.bidPrice1，volume为两者最小
        spread_tick.askPrice1 = self.lastLeg1Tick.askPrice1 - self.lastLeg2Tick.bidPrice1
        spread_tick.askVolume1 = min(self.lastLeg1Tick.askVolume1, self.lastLeg2Tick.bidVolume1)

        # 叫买价差=leg1.bidPrice1 - leg2.askPrice1，volume为两者最小
        spread_tick.bidPrice1 = self.lastLeg1Tick.bidPrice1 - self.lastLeg2Tick.askPrice1
        spread_tick.bidVolume1 = min(self.lastLeg1Tick.bidVolume1, self.lastLeg2Tick.askVolume1)

        return spread_tick

    def __checkLiquidity(self):
        """检查流动性缺失"""
        if self.lastLeg1Tick.bidPrice1 <= self.lastLeg1Tick.lastPrice <= self.lastLeg1Tick.askPrice1 \
            and self.lastLeg2Tick.bidPrice1 <= self.lastLeg2Tick.lastPrice <= self.lastLeg2Tick.askPrice1:
            return True

        self.writeCtaLog(u'流动性缺失导致最新价超出买1卖1范围')
        return False

    # ----------------------------------------------------------------------
    def __arbShort(self,grid):
        """非标准合约的套利反套（开空）指令"""
        self.writeCtaLog(u'套利价差反套（开空）单,price={0},volume={1}'.format(grid.openPrice, grid.volume))

        if not self.trading:
            self.writeCtaLog(u'停止状态，不开仓')
            return None

        bidPrice = self.lastLeg1Tick.bidPrice1 - self.lastLeg2Tick.askPrice1

        if self.lastLeg1Tick.bidPrice1 >= self.lastLeg1Tick.lastPrice:
            if self.lastLeg1Tick.bidVolume1 < 3:
                shortPrice = self.lastLeg1Tick.lastPrice - 2*self.minDiff
            elif self.lastLeg1Tick.bidVolume1 < 10:
                shortPrice = self.lastLeg1Tick.lastPrice - self.minDiff
            else:
                shortPrice = self.lastLeg1Tick.lastPrice
        else:
            if self.lastLeg1Tick.bidVolume1 < 10 or self.lastLeg1Tick.bidVolume1 <= grid.volume:
                shortPrice = self.lastLeg1Tick.bidPrice1 - self.minDiff
            else:
                shortPrice = self.lastLeg1Tick.bidPrice1

        if self.lastLeg2Tick.askPrice1 <= self.lastLeg2Tick.lastPrice:
            if self.lastLeg2Tick.askVolume1 < 3:
                buyPrice = self.lastLeg2Tick.lastPrice+2*self.minDiff
            elif self.lastLeg2Tick.askVolume1 < 10:
                buyPrice = self.lastLeg2Tick.lastPrice + self.minDiff
            else:
                buyPrice = self.lastLeg2Tick.lastPrice
        else:
            if self.lastLeg2Tick.askVolume1 < 10 or self.lastLeg2Tick.bidVolume1 <= grid.volume:
                buyPrice = self.lastLeg2Tick.askPrice1 + self.minDiff
            else:
                buyPrice = self.lastLeg2Tick.askPrice1

        if bidPrice < grid.openPrice:
            self.writeCtaLog(u'实际价差{0}不满足:{1}'.format(bidPrice, grid.openPrice))
            return None

        if (shortPrice - buyPrice + self.minDiff) < grid.openPrice:
            self.writeCtaLog(u'买卖价差{0}不满足:{1}'.format(shortPrice - buyPrice + self.minDiff, grid.openPrice))
            return None

        # 开空leg1
        orderID = self.ctaEngine.sendOrder(self.Leg1Symbol, CTAORDER_SHORT, shortPrice, grid.volume, self)
        if orderID is None or len(orderID) == 0:
            self.writeCtaLog(u'异常，Leg1开空仓失败')
            return None
        orders = orderID
        self.uncompletedOrders[orderID] = {'SYMBOL':self.Leg1Symbol, 'DIRECTION': DIRECTION_SHORT,
                                           'OFFSET': OFFSET_OPEN, 'Volume': grid.volume,
                                           'Price': shortPrice, 'TradedVolume': EMPTY_INT,
                                           'OrderTime': self.curDateTime,
                                           'Grid': grid}

        # 开多leg2
        orderID = self.ctaEngine.sendOrder(self.Leg2Symbol, CTAORDER_BUY, buyPrice, grid.volume, self)
        if orderID is None or len(orderID) == 0:
            self.writeCtaLog(u'异常，Leg2开多仓失败')
            # 这里要不要处理之前的Leg1开仓？（放在后面cancelorder中处理）
            return None
        orders = orders + ';' + orderID
        self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg2Symbol, 'DIRECTION': DIRECTION_LONG,
                                           'OFFSET': OFFSET_OPEN, 'Volume': grid.volume,
                                           'Price': buyPrice, 'TradedVolume': EMPTY_INT,
                                           'OrderTime': self.curDateTime,
                                           'Grid': grid}
        grid.orderStatus = True
        grid.orderDatetime = self.curDateTime

        self.entrust = -1
        self.writeCtaLog(u'arb short Orders：{0}'.format(orders))
        return orders

    # ----------------------------------------------------------------------
    def __arbBuy(self,grid):
        """非标准合约的套利正套（开多）指令"""
        self.writeCtaLog(u'套利价差正套（开多）单,price={0},volume={1}'.format(grid.openPrice, grid.volume))
        if not self.trading:
            self.writeCtaLog(u'停止状态，不开仓')
            return None

        askPrice = self.lastLeg1Tick.askPrice1 - self.lastLeg2Tick.bidPrice1
        if self.lastLeg1Tick.askPrice1 <= self.lastLeg1Tick.lastPrice:
            if self.lastLeg1Tick.askVolume1 < 3:
                buyPrice = self.lastLeg1Tick.lastPrice+2*self.minDiff
            elif self.lastLeg1Tick.askVolume1 < 10:
                buyPrice = self.lastLeg1Tick.lastPrice + self.minDiff
            else:
                buyPrice = self.lastLeg1Tick.lastPrice
        else:
            if self.lastLeg1Tick.askVolume1 < 10 or self.lastLeg1Tick.bidVolume1 <= grid.volume:
                buyPrice = self.lastLeg1Tick.askPrice1 + self.minDiff
            else:
                buyPrice = self.lastLeg1Tick.askPrice1

        if self.lastLeg2Tick.bidPrice1 >= self.lastLeg2Tick.lastPrice:
            if self.lastLeg2Tick.bidVolume1 < 3:
                shortPrice = self.lastLeg2Tick.lastPrice - 2*self.minDiff
            elif self.lastLeg2Tick.bidVolume1 < 10:
                shortPrice = self.lastLeg2Tick.lastPrice - self.minDiff
            else:
                shortPrice = self.lastLeg2Tick.lastPrice
        else:
            if self.lastLeg2Tick.bidVolume1 < 10 or self.lastLeg2Tick.bidVolume1 <= grid.volume:
                shortPrice = self.lastLeg2Tick.bidPrice1 - self.minDiff
            else:
                shortPrice = self.lastLeg2Tick.bidPrice1

        if askPrice > grid.openPrice:
            self.writeCtaLog(u'实际价差{0}不满足:{1}'.format(askPrice, grid.openPrice))
            return None

        if (buyPrice - shortPrice - self.minDiff) > grid.openPrice:
            self.writeCtaLog(u'对价价差{0}不满足:{1}'.format((buyPrice - shortPrice - self.minDiff), grid.openPrice))
            return None

        # 开多leg1
        orderID = self.ctaEngine.sendOrder(self.Leg1Symbol, CTAORDER_BUY, buyPrice, grid.volume, self)
        if orderID is None or len(orderID) == 0:
            self.writeCtaLog(u'异常，Leg1开多仓失败')
            return None
        orders = orderID
        self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg1Symbol, 'DIRECTION': DIRECTION_LONG,
                                           'OFFSET': OFFSET_OPEN, 'Volume': grid.volume,
                                           'Price': buyPrice, 'TradedVolume': EMPTY_INT,
                                           'OrderTime': self.curDateTime,
                                           'Grid': grid}

        # 开空leg2
        orderID = self.ctaEngine.sendOrder(self.Leg2Symbol, CTAORDER_SHORT, shortPrice, grid.volume, self)
        if (orderID is None) or len(orderID) == 0:
            self.writeCtaLog(u'异常，Leg2开空仓失败')
            # 这里要不要处理之前的Leg1开仓？（放在后面cancelorder中处理）
            return None
        orders = orders + ';' + orderID
        self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg2Symbol, 'DIRECTION': DIRECTION_SHORT,
                                           'OFFSET': OFFSET_OPEN, 'Volume': grid.volume,
                                           'Price': shortPrice, 'TradedVolume': EMPTY_INT,
                                           'OrderTime': self.curDateTime,
                                           'Grid':grid}
        grid.orderStatus = True
        self.entrust = 1
        grid.orderDatetime = self.curDateTime
        self.writeCtaLog(u'arb Buy Orders：{0}'.format(orders))
        return orders

    # ----------------------------------------------------------------------
    def __arbSell(self, grid, force = False):
        """非标准合约的套利平正套（平多）指令"""
        self.writeCtaLog(u'套利价差正套（平多）单,price={0},volume={1}'.format(grid.closePrice, grid.volume))
        if not self.trading:
            self.writeCtaLog(u'停止状态，不开仓')
            return None

        bidPrice = self.lastLeg1Tick.bidPrice1 - self.lastLeg2Tick.askPrice1

        if self.lastLeg1Tick.bidPrice1 >= self.lastLeg1Tick.lastPrice:
            if self.lastLeg1Tick.bidVolume1 < 3:
                sellPrice = self.lastLeg1Tick.lastPrice - 2*self.minDiff
            elif self.lastLeg1Tick.bidVolume1 < 10:
                sellPrice = self.lastLeg1Tick.lastPrice - self.minDiff
            else:
                sellPrice = self.lastLeg1Tick.lastPrice
        else:
            if self.lastLeg1Tick.bidVolume1 < 10 or self.lastLeg1Tick.bidVolume1 <= grid.volume:
                sellPrice = self.lastLeg1Tick.bidPrice1 - self.minDiff
            else:
                sellPrice = self.lastLeg1Tick.bidPrice1

        if self.lastLeg2Tick.askPrice1 <= self.lastLeg2Tick.lastPrice:

            if self.lastLeg2Tick.askVolume1 < 3:
                coverPrice = self.lastLeg2Tick.lastPrice + 2*self.minDiff
            elif self.lastLeg2Tick.askVolume1 < 10:
                coverPrice = self.lastLeg2Tick.lastPrice + self.minDiff
            else:
                coverPrice = self.lastLeg2Tick.lastPrice

        else:
            if self.lastLeg2Tick.askVolume1 < 10 or self.lastLeg2Tick.bidVolume1 <= grid.volume:
                coverPrice = self.lastLeg2Tick.askPrice1 + self.minDiff
            else:
                coverPrice = self.lastLeg2Tick.askPrice1

        if bidPrice < grid.closePrice and not force:
            self.writeCtaLog(u'实际价差{0}不满足:{1}'.format(bidPrice, grid.closePrice))
            return None

        #if sellPrice - coverPrice < grid.closePrice and not force:
        #    self.writeCtaLog(u'对价差{0}不满足:{1}'.format(bidPrice, grid.closePrice))
        #    return None

        if force:
            sellPrice -= self.minDiff
            coverPrice += self.minDiff

        leg1Pos = self.ctaEngine.posBufferDict.get(self.Leg1Symbol, None)
        leg2Pos = self.ctaEngine.posBufferDict.get(self.Leg2Symbol, None)

        if leg1Pos is None:
            self.writeCtaLog(u'查询不到Leg1:{0}的持仓数据'.format(self.Leg1Symbol))
            return None
        if leg2Pos is None:
            self.writeCtaLog(u'查询不到Leg2:{0}的持仓数据'.format(self.Leg2Symbol))
            return None

        if leg1Pos.longPosition < grid.volume:
            self.writeCtaLog(u'{0}仓位{1}不足{2}'.format(self.Leg1Symbol,leg1Pos.longPosition,grid.volume))
            return  None
        if leg2Pos.shortPosition < grid.volume:
            self.writeCtaLog(u'{0}仓位{1}不足{2}'.format(self.Leg2Symbol,leg2Pos.shortPosition,grid.volume))
            return None

        # ------------------平多leg1---------------------------------
        # 只有1手的情况下
        if grid.volume == 1 or self.backtesting:
            orderID = self.ctaEngine.sendOrder(self.Leg1Symbol, CTAORDER_SELL, sellPrice, grid.volume, self)
            orders = orderID
            if orderID is None:
                self.writeCtaLog(u'异常，Leg1:{0}平多仓失败'.format(self.Leg1Symbol))
                return None
            self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg1Symbol, 'DIRECTION': DIRECTION_SHORT,
                                               'OFFSET': OFFSET_CLOSE, 'Volume': grid.volume, 'TradedVolume': EMPTY_INT,
                                               'Price': sellPrice, 'OrderTime': self.curDateTime,
                                               'Grid': grid}

        else:
            # 昨仓有，并且少于平仓数量
            if leg1Pos.longYd > EMPTY_INT and  leg1Pos.longYd <  grid.volume:
                volYd  = leg1Pos.longYd             # 昨仓全平
                volToday = grid.volume - volYd      # 剩余的数量，平今仓

                self.writeCtaLog(u'{0}昨仓:{1}/今仓:{2}，分别平昨仓:{3}手、:今仓{4}手'
                                 .format(self.Leg1Symbol, leg1Pos.longYd, leg1Pos.longToday, volYd, volToday))

                # 平昨仓(第一次调用时，ctaEngine同样使用昨仓优先）
                orderID = self.ctaEngine.sendOrder(self.Leg1Symbol, CTAORDER_SELL, sellPrice,
                                                   volYd, self)
                if orderID is None:
                    self.writeCtaLog(u'异常，Leg1:{0}平多仓（昨仓:{1}手）失败'.format(self.Leg1Symbol,volYd))
                    return None
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg1Symbol, 'DIRECTION': DIRECTION_SHORT,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': volYd, 'TradedVolume': EMPTY_INT,
                                                   'Price': sellPrice, 'OrderTime': self.curDateTime,
                                                   'Grid': grid}
                # 更新持仓数据中的昨仓为0，避免瞬间连续平仓引发的昨仓数量不足
                leg1Pos.longYd = 0

                orders = orderID
                 # 平今仓
                orderID = self.ctaEngine.sendOrder(self.Leg1Symbol, CTAORDER_SELL, sellPrice, volToday, self)
                if orderID is None:
                    self.writeCtaLog(u'异常，Leg1:{0}平多仓（今仓:{1}手）失败'.format(self.Leg1Symbol,volToday))
                    return None
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg1Symbol, 'DIRECTION': DIRECTION_SHORT,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': volToday, 'TradedVolume': EMPTY_INT,
                                                   'Price': sellPrice, 'OrderTime': self.curDateTime,
                                                   'Grid': grid}

                orders = orders + ';' + orderID

            # 剩余：要么昨仓数量大于平仓数量、要么没有昨仓数量，今仓数量 >= 平仓数量，都交给catEngine自己解决
            else:
                orderID = self.ctaEngine.sendOrder(self.Leg1Symbol, CTAORDER_SELL, sellPrice, grid.volume, self)
                orders = orderID
                if orderID is None:
                    self.writeCtaLog(u'异常，Leg1:{0}平多仓:{1}手失败'.format(self.Leg1Symbol,grid.volume))
                    return None
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg1Symbol, 'DIRECTION': DIRECTION_SHORT,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': grid.volume, 'TradedVolume': EMPTY_INT,
                                                   'Price': sellPrice, 'OrderTime': self.curDateTime,
                                                   'Grid': grid}

        # --------------平空leg2-----------------------

        # 只有1手的情况下
        if grid.volume == 1 or self.backtesting:
            orderID = self.ctaEngine.sendOrder(self.Leg2Symbol, CTAORDER_COVER, coverPrice, grid.volume, self)
            if orderID is None:
                self.writeCtaLog(u'异常，Leg2:{0}平空仓失败'.format(self.Leg2Symbol))
                # 这里要不要处理之前的Leg1开仓？（放在后面cancelorder中处理）
                return None
            orders = orders + ';' + orderID
            self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg2Symbol, 'DIRECTION': DIRECTION_LONG,
                                               'OFFSET': OFFSET_CLOSE, 'Volume': grid.volume, 'TradedVolume': EMPTY_INT,
                                               'Price': coverPrice, 'OrderTime': self.curDateTime,
                                               'Grid': grid}
        else:
            # 昨仓有，并且少于平仓数量
            if leg2Pos.shortYd > EMPTY_INT and leg2Pos.shortYd < grid.volume:
                volYd = leg2Pos.shortYd                 # 平所有的昨仓
                volToday = grid.volume - volYd          # 剩余的今仓平
                self.writeCtaLog(u'{0}当前昨仓{1}/今仓:{2},分别平昨仓:{3}、今仓:{4}'
                                 .format(self.Leg2Symbol,leg2Pos.shortYd, leg2Pos.shortToday, volYd, volToday))

                # 平昨仓
                orderID = self.ctaEngine.sendOrder(self.Leg2Symbol, CTAORDER_COVER, coverPrice, volYd, self)
                if orderID is None:
                    self.writeCtaLog(u'异常，Leg2:{0}平空仓(昨仓:{1}手）失败'.format(self.Leg2Symbol, volYd))
                    return None

                orders = orders + ';' + orderID
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg2Symbol, 'DIRECTION': DIRECTION_LONG,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': volYd, 'TradedVolume': EMPTY_INT,
                                                   'Price': coverPrice, 'OrderTime': self.curDateTime,
                                                   'Grid': grid}
                # 更新持仓数据中的昨仓为0，避免瞬间连续平仓引发的昨仓数量不足
                leg2Pos.shortYd = 0

                # 平今仓
                orderID = self.ctaEngine.sendOrder(self.Leg2Symbol, CTAORDER_COVER, coverPrice, volToday, self)
                if orderID is None:
                    self.writeCtaLog(u'异常，Leg2:{0}平空仓(今仓:{1}）失败'.format(self.Leg2Symbol, volToday))
                    return None

                orders = orders + ';' + orderID
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg2Symbol, 'DIRECTION': DIRECTION_LONG,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': volToday, 'TradedVolume': EMPTY_INT,
                                                   'Price': coverPrice, 'OrderTime': self.curDateTime,
                                                   'Grid': grid}
            else:
                # 其他情况
                orderID = self.ctaEngine.sendOrder(self.Leg2Symbol, CTAORDER_COVER, coverPrice, grid.volume, self)
                if orderID is None:
                    self.writeCtaLog(u'异常，Leg2:{0}平空仓({1}手)失败'.format(self.Leg2Symbol, grid.volume))
                    # 这里要不要处理之前的Leg1开仓？（放在后面cancelorder中处理）
                    return None
                orders = orders + ';' + orderID
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg2Symbol, 'DIRECTION': DIRECTION_LONG,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': grid.volume,
                                                   'Price': coverPrice, 'TradedVolume': EMPTY_INT,
                                                   'OrderTime': self.curDateTime,
                                                   'Grid': grid}

        self.entrust = -1
        grid.orderDatetime = self.curDateTime
        self.writeCtaLog(u'arb Sell Orders：{0}'.format(orders))
        return orders

    # ----------------------------------------------------------------------
    def __arbCover(self, grid, force = False):
        """非标准合约的套利平反套（平空）指令"""
        self.writeCtaLog(u'套利价差平反套（平多）单,price={0},volume={1}'.format(grid.closePrice, grid.volume))
        if not self.trading:
            self.writeCtaLog(u'停止状态，不开仓')
            return None

        askPrice = self.lastLeg1Tick.askPrice1 - self.lastLeg2Tick.bidPrice1
        if self.lastLeg1Tick.askPrice1 <= self.lastLeg1Tick.lastPrice:
            if self.lastLeg1Tick.askVolume1 < 3:
                coverPrice = self.lastLeg1Tick.lastPrice+2*self.minDiff
            elif self.lastLeg1Tick.askVolume1 < 10:
                coverPrice = self.lastLeg1Tick.lastPrice + self.minDiff
            else:
                coverPrice = self.lastLeg1Tick.lastPrice

        else:
            if self.lastLeg1Tick.askVolume1 < 10 or self.lastLeg1Tick.bidVolume1 <= grid.volume:
                coverPrice = self.lastLeg1Tick.askPrice1 + self.minDiff
            else:
                coverPrice = self.lastLeg1Tick.askPrice1

        if self.lastLeg2Tick.bidPrice1 >= self.lastLeg2Tick.lastPrice:
            if self.lastLeg2Tick.bidVolume1 < 3:
                sellPrice = self.lastLeg2Tick.lastPrice - 2*self.minDiff
            elif self.lastLeg2Tick.bidVolume1 < 10:
                sellPrice = self.lastLeg2Tick.lastPrice - self.minDiff
            else:
                sellPrice = self.lastLeg2Tick.lastPrice

        else:
            if self.lastLeg2Tick.bidVolume1 < 10 or self.lastLeg2Tick.bidVolume1 <= grid.volume:
                sellPrice = self.lastLeg2Tick.bidPrice1 - self.minDiff
            else:
                sellPrice = self.lastLeg2Tick.bidPrice1

        if askPrice > grid.closePrice and not force:
            self.writeCtaLog(u'实际价差{0}不满足:{1}'.format(askPrice, grid.closePrice))
            return None

        #if (coverPrice - sellPrice) > grid.closePrice and not force:
        #    self.writeCtaLog(u'对价价差{0}不满足:{1}'.format((coverPrice - sellPrice), grid.closePrice))
        #    return None

        if force:
            coverPrice +=self.minDiff
            sellPrice -= self.minDiff

        leg1Pos = self.ctaEngine.posBufferDict.get(self.Leg1Symbol, None)
        leg2Pos = self.ctaEngine.posBufferDict.get(self.Leg2Symbol, None)

        if leg1Pos is None:
            self.writeCtaLog(u'查询不到Leg1:{0}的持仓数据'.format(self.Leg1Symbol))
            return None
        if leg2Pos is None:
            self.writeCtaLog(u'查询不到Leg2:{0}的持仓数据'.format(self.Leg2Symbol))
            return None

        if leg1Pos.shortPosition < grid.volume:
            self.writeCtaLog(u'{0}仓位{1}不足{2}'.format(self.Leg1Symbol, leg1Pos.shortPosition, grid.volume))
            return None
        if leg2Pos.longPosition < grid.volume:
            self.writeCtaLog(u'{0}仓位{1}不足{2}'.format(self.Leg2Symbol, leg2Pos.longPosition, grid.volume))
            return None

        # 平空leg1
        # 只有1手的情况下
        if grid.volume == 1 or self.backtesting:
            orderID = self.ctaEngine.sendOrder(self.Leg1Symbol, CTAORDER_COVER, coverPrice, grid.volume, self)
            if orderID is None:
                self.writeCtaLog(u'Leg1:{0}平空仓({1}手)失败'.format(self.Leg1Symbol, grid.volume))
                return None
            orders = orderID
            self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg1Symbol, 'DIRECTION': DIRECTION_LONG,
                                               'OFFSET': OFFSET_CLOSE, 'Volume': grid.volume, 'TradedVolume': EMPTY_INT,
                                               'Price': coverPrice, 'OrderTime': self.curDateTime,
                                               'Grid': grid}
        else:
            # 昨仓有，并且少于平仓数量
            if leg1Pos.shortYd > EMPTY_INT and leg1Pos.shortYd < grid.volume:
                volYd = leg1Pos.shortYd             # 昨仓全平
                volToday = grid.volume - volYd      # 今仓平剩余部分
                self.writeCtaLog(u'{0}分别平昨仓:{1}、今仓:{2}'.format(self.Leg1Symbol, volYd, volToday))

                # 优先平昨仓
                orderID = self.ctaEngine.sendOrder(self.Leg1Symbol, CTAORDER_COVER, coverPrice, volYd, self)
                if orderID is None:
                    self.writeCtaLog(u'Leg1:{0}平空仓(昨仓:{1}手）失败'.format(self.Leg1Symbol, volYd))
                    return None
                orders = orderID
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg1Symbol, 'DIRECTION': DIRECTION_LONG,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': volYd, 'TradedVolume': EMPTY_INT,
                                                   'Price': coverPrice, 'OrderTime': self.curDateTime,
                                                   'Grid': grid}
                # 更新持仓数据中的昨仓为0，避免瞬间连续平仓引发的昨仓数量不足
                leg1Pos.shortYd = 0

                # 平今仓
                orderID = self.ctaEngine.sendOrder(self.Leg1Symbol, CTAORDER_COVER, coverPrice, volToday, self)
                if orderID is None:
                    self.writeCtaLog(u'Leg1:{0}平空仓(今仓:{1}手）失败'.format(self.Leg1Symbol, volToday))
                    # 这里要不要处理之前的Leg1开仓？（放在后面cancelorder中处理）
                    return None
                orders = orders + ';' + orderID
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg1Symbol, 'DIRECTION': DIRECTION_LONG,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': volToday, 'TradedVolume': EMPTY_INT,
                                                   'Price': coverPrice, 'OrderTime': self.curDateTime,
                                                   'Grid': grid}
            else:
                # 其他情况(全部昨天仓/全部今仓）
                orderID = self.ctaEngine.sendOrder(self.Leg1Symbol, CTAORDER_COVER, coverPrice, grid.volume, self)
                if orderID is None:
                    self.writeCtaLog(u'Leg1:{0}平空仓({1}手)失败'.format(self.Leg1Symbol, grid.volume))
                    # 这里要不要处理之前的Leg1开仓？（放在后面cancelorder中处理）
                    return None
                orders = orderID
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg1Symbol, 'DIRECTION': DIRECTION_LONG,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': grid.volume, 'TradedVolume': EMPTY_INT,
                                                   'Price': coverPrice, 'OrderTime': self.curDateTime,
                                                   'Grid': grid}

        # 平多leg2


        # 只有1手的情况下
        if grid.volume == 1 or self.backtesting:
            orderID = self.ctaEngine.sendOrder(self.Leg2Symbol, CTAORDER_SELL, sellPrice, grid.volume, self)
            orders = orders + ';' + orderID
            if orderID is None:
                self.writeCtaLog(u'Leg2:{0}平多仓({1}手)失败'.format(self.Leg2Symbol, grid.volume))
                return None
            self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg2Symbol, 'DIRECTION': DIRECTION_SHORT,
                                               'OFFSET': OFFSET_CLOSE, 'Volume': grid.volume, 'TradedVolume': EMPTY_INT,
                                               'Price': sellPrice, 'OrderTime': self.curDateTime,
                                               'Grid': grid}

        else:
            # 昨仓有，并且少于平仓数量
            if leg2Pos.longYd > EMPTY_INT and leg2Pos.longYd < grid.volume:
                volYd= leg2Pos.longYd
                volToday = grid.volume - volYd

                self.writeCtaLog(u'{0}分别平今仓:{1}、:昨仓{2}'.format(self.Leg2Symbol, volToday, volYd))

                # 平昨仓(第一次调用时，ctaEngine同样使用昨仓优先）
                orderID = self.ctaEngine.sendOrder(self.Leg2Symbol, CTAORDER_SELL, sellPrice, volYd, self)

                if orderID is None:
                    self.writeCtaLog(u'Leg2:{0}平多仓（昨仓:{1}手）失败'.format(self.Leg2Symbol, volYd))
                    return None
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg2Symbol, 'DIRECTION': DIRECTION_SHORT,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': volYd, 'TradedVolume': EMPTY_INT,
                                                   'Price': sellPrice, 'OrderTime': self.curDateTime,
                                                   'Grid': grid}

                # 更新持仓数据中的昨仓为0，避免瞬间连续平仓引发的昨仓数量不足
                leg2Pos.longYd = 0

                orders = orders + ';' + orderID
                # 平今仓
                orderID = self.ctaEngine.sendOrder(self.Leg2Symbol, CTAORDER_SELL, sellPrice, volToday, self)
                if orderID is None:
                    self.writeCtaLog(u'Leg2:{0}平多仓（昨仓）失败'.format(self.Leg2Symbol))
                    return None
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg2Symbol, 'DIRECTION': DIRECTION_SHORT,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': volToday, 'TradedVolume': EMPTY_INT,
                                                   'Price': sellPrice, 'OrderTime': self.curDateTime,
                                                   'Grid': grid}

                orders = orders + ';' + orderID

            # 剩余：要么昨仓数量大于平仓数量、要么没有昨仓数量，今仓数量 >= 平仓数量，都交给catEngine自己解决
            else:
                orderID = self.ctaEngine.sendOrder(self.Leg2Symbol, CTAORDER_SELL, sellPrice, grid.volume, self)
                orders = orders + ';' + orderID
                if orderID is None:
                    self.writeCtaLog(u'Leg2:{0}平多仓（{1}手）失败'.format(self.Leg2Symbol, grid.volume))
                    return None
                self.uncompletedOrders[orderID] = {'SYMBOL': self.Leg2Symbol, 'DIRECTION': DIRECTION_SHORT,
                                                   'OFFSET': OFFSET_CLOSE, 'Volume': grid.volume, 'TradedVolume': EMPTY_INT,
                                                   'Price': sellPrice,
                                                   'OrderTime': self.curDateTime,
                                                   'Grid': grid}

        self.entrust = 1
        grid.orderDatetime = self.curDateTime
        self.writeCtaLog(u'arb Cover Orders：{0}'.format(orders))
        return orders

    # ----------------------------------------------------------------------
    def onTick(self, tick):
        """行情更新
        :type tick: object
        """
        # 更新策略执行的时间（用于回测时记录发生的时间）
        self.curDateTime = tick.datetime

        spread_tick = None

        # 合并tick
        if tick.vtSymbol != self.vtSymbol:
            spread_tick = self.__combineTick(tick)
        if spread_tick is None :
            return

        # 修正lastPrice，大于中轴(0)时，取最小值，小于中轴时，取最大值
        if spread_tick.bidPrice1 > self.baseMidLine and spread_tick.askPrice1 > self.baseMidLine:
            spread_tick.lastPrice = min(spread_tick.bidPrice1, spread_tick.askPrice1)
        elif spread_tick.bidPrice1 < self.baseMidLine and spread_tick.askPrice1 < self.baseMidLine:
            spread_tick.lastPrice = max(spread_tick.bidPrice1, spread_tick.askPrice1)

        self.curTick = spread_tick

        if not self.backtesting:
            dt = datetime.now()
            if  (dt.hour >= 3 and dt.hour < 8) or (dt.hour >= 16 and dt.hour < 20):
                return

        if (spread_tick.datetime.hour >= 3 and spread_tick.datetime.hour <= 8) or (spread_tick.datetime.hour >= 16 and spread_tick.datetime.hour <= 20):
            self.writeCtaLog(u'休市/集合竞价排名时数据不处理')
            self.__initGrids()
            return

        if not self.recheckPositions and self.closeWindow:
            self.writeCtaLog(u'激活重新提交平仓单')
            self.recheckPositions = True

        # 2、计算交易时间和平仓时间
        self.__timeWindow(spread_tick)

        # 4、交易逻辑
        # 首先检查是否是实盘运行还是数据预处理阶段
        if not self.inited :
            return

        # 初始化网格交易器（或从本地记录文件中获取）
        self.__initGrids()

        if self.tradeWindow and not self.closeWindow and self.recheckPositions:
            self.writeCtaLog(u'交易时间，重新计算持仓')
            # 重新计算持仓
            self.__recheckPositions()

        if not self.tradeWindow and self.closeWindow and not self.recheckPositions:
            self.writeCtaLog(u'收盘时间，重置计算持仓标志')
            self.recheckPositions = True
            if self.inited:
                self.gt.save(direction=DIRECTION_LONG)
                self.gt.save(direction=DIRECTION_SHORT)

        # 执行撤单逻辑
        self.__cancelLogic(self.curDateTime)

        if self.curDateTime.second == 0:
            self.__updateGridsDisplay()

        if self.entrust == 0:
            # 获取满足的未挂单(开空单）
            pendingGrids = self.gt.getGrids(direction=DIRECTION_SHORT,
                                            end=spread_tick.bidPrice1)

            if len(pendingGrids) > 1:
                self.writeCtaLog(u'有多个挂单，只选择价格最高的一个')
                sortedGrids = sorted(pendingGrids, key=lambda g:g.openPrice)
                pendingGrids = sortedGrids[-1:]

            # 提交挂单
            for x in pendingGrids[:]:
                if self.position.avaliablePos2Add() < 1:
                    msg = u'持空仓数量已满，不再开仓'
                    if msg != self.logMsg:
                        self.logMsg = msg
                        self.writeCtaLog(msg)
                    continue

                if not (spread_tick.bidPrice1 >= x.openPrice):
                    msg = u'spread_tick.bidPrice1:{0}< 网格:{1},不开空仓'.format(spread_tick.bidPrice1, x.openPrice)
                    if msg != self.logMsg:
                        self.logMsg = msg
                        self.writeCtaLog(msg)
                    continue

                if not self.__checkAccountLimit():
                    msg = u'资金占用超过限制值，不开仓'
                    if msg != self.logMsg:
                        self.logMsg = msg
                        self.writeCtaLog(msg)
                    continue

                # 调用套利下单指令
                ref = self.__arbShort(x)
                if ref is not None and len(ref)>0:
                    self.writeCtaLog(u'开空委托单号{0}'.format(ref))
                    self.gt.updateOrderRef(direction=DIRECTION_SHORT, openPrice=x.openPrice, orderRef=ref)
                else:
                    self.writeCtaLog(u'开空委托单失败:{0},v:{1}'.format(x.openPrice, x.volume))

            # 获取满足价格的未挂单(开多单）
            pendingGrids = self.gt.getGrids(direction=DIRECTION_LONG,
                                            end=spread_tick.askPrice1)

            if len(pendingGrids) > 1:
                self.writeCtaLog(u'有多个挂单，只选择价格最低的一个')
                sortedGrids = sorted(pendingGrids, key=lambda g: g.openPrice)
                pendingGrids = sortedGrids[0:1]

            # 逐一提交挂单
            for x in pendingGrids:
                if self.position.avaliablePos2Add() < 1:
                    msg = u'持多仓数量已满，不再开多仓'
                    if msg != self.logMsg:
                        self.logMsg = msg
                        self.writeCtaLog(msg)
                    continue

                if not spread_tick.askPrice1 <= x.openPrice:
                    msg = u'spread_tick.askPrice1:{0} > 网格:{1},不开多仓'.format(spread_tick.askPrice1, x.openPrice)
                    if msg != self.logMsg:
                        self.logMsg = msg
                        self.writeCtaLog(msg)
                    continue

                if not self.__checkAccountLimit():
                    msg = u'资金占用超过限制值，不开仓'
                    if msg != self.logMsg:
                        self.logMsg = msg
                        self.writeCtaLog(msg)
                    continue

                ref = self.__arbBuy(x)
                if ref is not None and len(ref) > 0:
                    self.writeCtaLog(u'开多委托单号{0}'.format(ref))
                    self.gt.updateOrderRef(direction=DIRECTION_LONG, openPrice=x.openPrice, orderRef=ref)
                else:
                    self.writeCtaLog(u'开多委托单失败:{0},v:{1}'.format(x.openPrice, x.volume))

        # 持有正套的单
        if self.position.longPos > 0 and self.entrust == 0 and self.tradeWindow:

            # 从网格获取，未平仓状态，价格，注意检查是否有可以平仓的网格
            pendingGrids = self.gt.getGrids(direction=DIRECTION_LONG, opened=True, closed=False, ordered=False,
                                            begin=999999 , end= -999999)
            for x in pendingGrids:
                if self.sigle_exist and len(pendingGrids) > 1:
                    continue

                if x.closePrice < spread_tick.bidPrice1:
                    ref = self.__arbSell(x)
                    if ref is not None:
                        self.writeCtaLog(u'平正套（平多）委托单号{0}'.format(ref))
                        self.gt.updateOrderRef(direction=DIRECTION_LONG, openPrice=x.openPrice, orderRef=ref)
                    else:
                        self.writeCtaLog(u'平正套（平多）委托单失败:{0},v:{1}'.format(x.closePrice, x.volume))

        # 持有反套的单，检查平仓条件
        if self.position.shortPos < 0 and self.entrust == 0 and self.tradeWindow:

            # 从网格获取，未平仓状态，价格
            pendingGrids = self.gt.getGrids(direction=DIRECTION_SHORT, opened=True, closed=False, ordered=False,
                                            begin=-999999, end=999999)

            for x in pendingGrids:
                if self.sigle_exist and len(pendingGrids) > 1:
                    continue

                if x.closePrice > spread_tick.askPrice1:
                    ref = self.__arbCover(x)
                    if ref is not None:
                        self.writeCtaLog(u'平反套（平空）委托单号{0}'.format(ref))
                        self.gt.updateOrderRef(direction=DIRECTION_SHORT, openPrice=x.openPrice, orderRef=ref)
                    else:
                        self.writeCtaLog(u'平反套（平空）委托单失败:{0},v:{1}'.format(x.closePrice, x.volume))


    # ----------------------------------------------------------------------
    def onBar(self, bar):
        """分钟K线数据更新
        bar，k周期数据
        """
        pass
    # ----------------------------------------------------------------------
    def __initGrids(self):
        if len(self.gt.upGrids) <= 0 or len(self.gt.dnGrids) <= 0:
            self.writeCtaLog(u'__initGrids(),初始化网格交易器')
            self.gt.initGrid(upline=self.baseUpLine, dnline=self.baseDnLine)
            self.writeCtaLog(u'__initGrids(),初始化网格完成')
            self.recheckPositions = True

    def __updateGridsDisplay(self):
        """更新网格显示信息"""
        self.upGrids = self.gt.toStr(direction=DIRECTION_SHORT)
        self.writeCtaLog(self.upGrids)

        self.dnGrids = self.gt.toStr(direction=DIRECTION_LONG)
        self.writeCtaLog(self.dnGrids)

    def __closeAllGrids(self, direction, closePrice):
        """对所有的网格强制平仓"""
        if direction == DIRECTION_SHORT:
            # 扫描上网格
            for x in self.gt.upGrids[:]:
                # 已发送订单，已开仓，未平仓
                if not x.openStatus or x.closeStatus:
                    continue

                if x.orderStatus and x.orderRef != EMPTY_STRING and x.orderDatetime is not None:
                    orders = x.orderRef.split(';')
                    if len(orders) == 1:
                        self.writeCtaLog(u'{0}只有单腿委托{1}'.format(x.openPrice, orders[0]))
                        continue

                    # 当前分钟内，不再委托强平
                    if x.orderDatetime.minute == self.curDateTime.minute:
                        continue

                    self.writeCtaLog(u'取消平仓单:[ref={0},closeprice={1}]'.format(x.orderRef, x.closePrice))
                    for order in orders:
                        self.writeCtaLog(u'撤单:{0}'.format(order))
                        self.cancelOrder(order)

                    sleep(0.3)

                oldPrice = x.closePrice
                x.closePrice = closePrice
                ref = self.__arbCover(x, force=True)

                if ref:
                    x.orderRef = ref
                    x.orderStatus = True
                    x.orderDatetime = self.curDateTime
                    self.writeCtaLog(u'强制提交平空委托单[closeprice={0},volume={1}]'
                                     .format(x.closePrice, x.volume))
                else:
                    self.writeCtaLog(u'提交平仓委托单失败')
                    x.closePrice = oldPrice

        if direction == DIRECTION_LONG:
            # 扫描下网格
            for x in self.gt.dnGrids[:]:
                if not x.openStatus or x.closeStatus:
                    self.writeCtaLog(u'网格[open={0},close={1} 不满足状态'.format(x.openPrice, x.closePrice))
                    continue

                if x.orderStatus and x.orderRef != EMPTY_STRING and x.orderDatetime is not None:
                    orders = x.orderRef.split(';')
                    if len(orders) == 1:
                        self.writeCtaLog(u'{0}只有单腿委托{1}'.format(x.openPrice, orders[0]))
                        continue

                    if x.orderDatetime.minute == self.curDateTime.minute:
                        continue

                    self.writeCtaLog(u'取消平多单:[ref={0},closeprice={1}]'.format(x.orderRef, x.closePrice))

                    for order in orders:
                        self.writeCtaLog(u'撤单:{0}'.format(order))
                        self.cancelOrder(order)

                    sleep(0.3)

                oldPrice = x.closePrice
                x.closePrice = closePrice
                # 强制平仓
                ref = self.__arbSell(x, force=True)
                if ref:
                    x.orderRef = ref
                    x.orderStatus = True
                    x.orderDatetime = self.curDateTime
                    self.writeCtaLog(
                        u'强制提交平多委托单[closeprice={0},volume={1}]'.format(x.closePrice, x.volume ))
                else:
                    self.writeCtaLog(u'提交平仓委托单失败')
                    x.closePrice = oldPrice


    # ----------------------------------------------------------------------
    def __timeWindow(self, tick):
        """交易与平仓窗口"""
        # 交易窗口 避开早盘和夜盘的前5分钟，防止隔夜跳空。
        self.closeWindow = False
        self.tradeWindow = False
        self.openWindow = False

        # 初始化当日的首次交易
        #if (tick.datetime.hour == 9 or tick.datetime.hour == 21) and tick.datetime.minute == 0 and tick.datetime.second ==0:
        #  self.firstTrade = True

        # 开市期，波动较大，用于判断止损止盈，或开仓
        if (tick.datetime.hour == 9 or tick.datetime.hour == 21) and tick.datetime.minute < 10:
            self.openWindow = True

        # 日盘
        if tick.datetime.hour == 9 and ((tick.datetime.minute >= 0 and self.shortSymbol not in MARKET_ZJ) or tick.datetime.minute >= 15):
            self.tradeWindow = True
            return

        if tick.datetime.hour == 10:
            if (tick.datetime.minute <= 15 or tick.datetime.minute >= 30) or self.shortSymbol in MARKET_ZJ:
                self.tradeWindow = True
                return

        if tick.datetime.hour == 11 and tick.datetime.minute <= 30:
            self.tradeWindow = True
            return

        # 中金所是13:00开盘，大连、郑商、上期所，是13:30开盘
        if tick.datetime.hour == 13 and tick.datetime.minute >= 00:
            self.tradeWindow = True
            return

        # 大连、郑商、上期所，是15:00  收盘
        if tick.datetime.hour == 14:
            if tick.datetime.minute < 59 or self.shortSymbol in MARKET_ZJ:
                self.tradeWindow = True
                return

            if tick.datetime.minute == 59:                 # 日盘平仓
                self.closeWindow = True
                return

        # 中金所是15:15收盘
        if tick.datetime.hour == 15 and self.shortSymbol in MARKET_ZJ:
            if tick.datetime.minute < 14:
                self.tradeWindow = True
                return

            if tick.datetime.minute >= 14:                 # 日盘平仓
                self.closeWindow = True
                return

        # 夜盘
        if tick.datetime.hour == 21 and tick.datetime.minute >= 0:
            self.tradeWindow = True
            return

        # 上期 贵金属， 次日凌晨2:30
        if self.shortSymbol in NIGHT_MARKET_SQ1:
            if tick.datetime.hour == 22 or tick.datetime.hour == 23 or tick.datetime.hour == 0 or tick.datetime.hour ==1:
                self.tradeWindow = True
                return

            if tick.datetime.hour == 2:
                if tick.datetime.minute < 29:                 # 收市前29分钟
                    self.tradeWindow = True
                    return
                if tick.datetime.minute == 29:                 # 夜盘平仓
                    self.closeWindow = True
                    return
            return

        # 上期 有色金属，黑色金属，沥青 次日01:00
        if self.shortSymbol in NIGHT_MARKET_SQ2:
            if tick.datetime.hour == 22 or tick.datetime.hour == 23:
                self.tradeWindow = True
                return

            if tick.datetime.hour == 0:
                if tick.datetime.minute < 59:              # 收市前29分钟
                    self.tradeWindow = True
                    return

                if tick.datetime.minute == 59:                 # 夜盘平仓
                    self.closeWindow = True
                    return

            return

        # 上期 天然橡胶  23:00
        if self.shortSymbol in NIGHT_MARKET_SQ3:

            if tick.datetime.hour == 22:
                if tick.datetime.minute < 59:              # 收市前1分钟
                    self.tradeWindow = True
                    return

                if tick.datetime.minute == 59:                 # 夜盘平仓
                        self.closeWindow = True
                        return

        # 郑商、大连 23:30
        if self.shortSymbol in NIGHT_MARKET_ZZ or self.shortSymbol in NIGHT_MARKET_DL:
            if tick.datetime.hour == 22:
                self.tradeWindow = True
                return

            if tick.datetime.hour == 23:
                if tick.datetime.minute < 29:                 # 收市前1分钟
                    self.tradeWindow = True
                    return
                if tick.datetime.minute == 29 and tick.datetime.second > 30:                 # 夜盘平仓
                    self.closeWindow = True
                    return
            return

    def __checkAccountLimit(self):
        """主动检查是否超过总体资金占用比例"""
        c, a, p, pl = self.ctaEngine.getAccountInfo()
        if p > pl:
            return False

        return True

    def __recheckPositions(self):
        """重新计算持仓"""
        self.writeCtaLog(u'扫描网格，重新计算持仓')
        # 重置position
        self.position.clear()
        checks = EMPTY_INT

        # 扫描上网格
        for x in self.gt.upGrids[:]:
            # 已发送订单，已开仓，未平仓
            if x.openStatus and not x.closeStatus:
                closePrice = min(x.closePrice, self.curTick.lastPrice)
                x.orderRef = EMPTY_STRING
                # 未平仓的volume=网格的volume-已交易的volume，
                # 更新仓位
                self.position.openPos(direction=DIRECTION_SHORT, vol=x.volume - x.tradedVolume,
                                      price=x.openPrice)

                checks = checks + 1
                self.writeCtaLog(u'增加空仓{0},V:{1}'.format(x.openPrice,x.volume - x.tradedVolume))

            elif x.orderStatus and not x.openStatus:
                self.writeCtaLog(u'重置网格[{0}]的开仓单委托'.format(x.openPrice))
                x.orderStatus = False
                x.orderRef = EMPTY_STRING

        if checks == EMPTY_INT:
            self.writeCtaLog(u'上网格没空单')

        checks = EMPTY_INT
        # 扫描下网格
        for x in self.gt.dnGrids[:]:
            # 已发送订单，已开仓，未平仓
            if x.openStatus and not x.closeStatus:
                closePrice = max(x.closePrice, self.curTick.lastPrice)

                x.orderRef = EMPTY_STRING
                # 未平仓的volume=网格的volume-已交易的volume，
                # 更新仓位
                self.position.openPos(direction=DIRECTION_LONG, vol=x.volume - x.tradedVolume,
                                      price=x.openPrice)

                checks = checks + 1
                self.writeCtaLog(u'增加多仓{0},V:{1}'.format(x.openPrice, x.volume - x.tradedVolume))

            elif x.orderStatus and not x.openStatus:
                self.writeCtaLog(u'重置网格[{0}]的开仓单委托'.format(x.openPrice))
                x.orderStatus = False
                x.orderRef = EMPTY_STRING

        if checks == EMPTY_INT:
            self.writeCtaLog(u'下网格没有多单')

        self.gridpos = self.position.pos
        # 重置为已执行
        self.recheckPositions = False

    def __cancelLogic(self, dt, force=False):
        "撤单逻辑"""
        if len(self.uncompletedOrders) < 1:
            return

        canceled_keys = []

        #if ((dt - self.lastOrderTime).seconds > self.cancelSeconds / i ) \
        #        or force:  # 超过设置的时间还未成交
        """
        {'SYMBOL': self.Leg1Symbol, 'DIRECTION': DIRECTION_SHORT,
         'OFFSET': OFFSET_OPEN, 'Volume': grid.volume,
         'Price': shortPrice, 'TradedVolume':0 ,
         'OrderTime': self.curDateTime,
         'Grid': grid}
         """

        order_keys = self.uncompletedOrders.keys()

        for order_key in order_keys:
            if order_key not in self.uncompletedOrders:
                self.writeCtaLog(u'{0}不在未完成的委托单中。'.format(order_key))
                continue
            order = self.uncompletedOrders[order_key]
            order_time = order['OrderTime']
            order_symbol = copy.copy(order['SYMBOL'])
            order_volume = order['Volume'] - order['TradedVolume']
            order_price = order['Price']

            if (dt - order_time).seconds > self.cancelSeconds:
                self.writeCtaLog(u'{0}超时{1}秒未成交，取消委托单：{2}'.format(order_symbol, (dt - order_time).seconds, order))

                # 获得对应的网格,检查网格是否两个lge的order都未成交
                grid = order['Grid']
                orders_in_grid = grid.orderRef.split(';')
                if len(orders_in_grid) > 1:
                    self.writeCtaLog(u'{0}=>{1}网格两腿超时未成交，均撤单'.format(grid.openPrice,grid.closePrice))
                    for order_in_grid in orders_in_grid:
                        # 分别撤销委托单
                        self.cancelOrder(str(order_in_grid))
                        self.writeCtaLog(u'删除orderID:{0}'.format(order_in_grid))
                        try:
                            del self.uncompletedOrders[order_in_grid]
                        except Exception as ex:
                            self.writeCtaLog(u'uncompletedOrders找不到{0}'.format(order_in_grid))

                    grid.orderStatus = False
                    grid.orderRef = EMPTY_STRING
                    grid.orderDatetime = None
                    self.entrust = 0
                    continue

                # 撤销该委托单
                self.cancelOrder(str(order_key))

                # 撤销的委托单，属于平仓类，需要追平
                if order['OFFSET'] == OFFSET_CLOSE:
                    # 属于平多委托单
                    if order['DIRECTION'] == DIRECTION_SHORT:

                        if order_symbol == self.Leg1Symbol:
                            sellPrice = min(self.lastLeg1Tick.bidPrice1, self.lastLeg1Tick.lastPrice) - self.minDiff
                        else:
                            sellPrice = min(self.lastLeg2Tick.bidPrice1, self.lastLeg2Tick.lastPrice) - self.minDiff

                        orderID = self.ctaEngine.sendOrder(order_symbol, CTAORDER_SELL, sellPrice, order_volume, self)

                        if orderID is None:
                            self.writeCtaLog(u'重新提交{0} {1}手平多单{2}失败'.format(order_symbol,order_volume,sellPrice))
                            continue

                        # 添加到待删除的清单
                        canceled_keys.append(order_key)
                        # 更新网格的委托单
                        grid = order['Grid']
                        grid.orderRef = grid.orderRef.replace(order_key, orderID)
                        # 重新添加平多委托单
                        self.uncompletedOrders[orderID] = {'SYMBOL': order_symbol, 'DIRECTION': DIRECTION_SHORT,
                                                           'OFFSET': OFFSET_CLOSE, 'Volume': order_volume,'TradedVolume': EMPTY_INT,
                                                           'Price': sellPrice, 'OrderTime': self.curDateTime,
                                                           'Grid': grid}

                    # 属于平空委托单
                    else:
                        # 获取对价
                        if order_symbol == self.Leg1Symbol:
                            coverPrice = max(self.lastLeg1Tick.askPrice1, self.lastLeg1Tick.lastPrice) + self.minDiff
                        else:
                            coverPrice = max(self.lastLeg2Tick.askPrice1, self.lastLeg2Tick.lastPrice) + self.minDiff

                        orderID = self.ctaEngine.sendOrder(order_symbol, CTAORDER_COVER, coverPrice, order_volume, self)
                        if orderID is None:
                            self.writeCtaLog(u'重新提交{0} {1}手平空单{2}失败'.format(order_symbol, order_volume, coverPrice))
                            continue

                        # 添加到待删除的清单
                        canceled_keys.append(order_key)
                        # 更新网格的委托单
                        grid = order['Grid']
                        grid.orderRef = grid.orderRef.replace(order_key, orderID)
                        # 重新添加平空委托单
                        self.uncompletedOrders[orderID] = {'SYMBOL': order_symbol, 'DIRECTION': DIRECTION_LONG,
                                                           'OFFSET': OFFSET_CLOSE, 'Volume': order_volume,'TradedVolume': EMPTY_INT,
                                                           'Price': coverPrice, 'OrderTime': self.curDateTime,
                                                           'Grid': grid}

                # 撤销的委托单，属于开仓类，需要追开
                else:
                    # 属于开空委托单
                    if order['DIRECTION'] == DIRECTION_SHORT:
                        if order_symbol == self.Leg1Symbol:
                            shortPrice = min(self.lastLeg1Tick.bidPrice1, self.lastLeg1Tick.lastPrice) - self.minDiff
                        else:
                            shortPrice = min(self.lastLeg2Tick.bidPrice1, self.lastLeg2Tick.lastPrice) - self.minDiff

                        # 发送委托
                        orderID = self.ctaEngine.sendOrder(order_symbol, CTAORDER_SHORT, shortPrice, order_volume, self)
                        if orderID is None or len(orderID) == 0:
                            self.writeCtaLog(u'重新提交{0} {1}手开空单{2}失败'.format(order_symbol, order_volume, shortPrice))
                            continue

                        # 添加到待删除的清单
                        canceled_keys.append(order_key)
                        # 更新网格的委托单
                        grid = order['Grid']
                        grid.orderRef = grid.orderRef.replace(order_key, orderID)
                        if shortPrice < order_price:
                            # 修正止盈点位
                            if grid.direction == DIRECTION_SHORT:
                                grid.closePrice -= (order_price-shortPrice)
                            else:
                                grid.closePrice += (order_price-shortPrice)
                        # 重新添加开空委托单
                        self.uncompletedOrders[orderID] = {'SYMBOL': order_symbol, 'DIRECTION': DIRECTION_SHORT,
                                                           'OFFSET': OFFSET_OPEN, 'Volume': order_volume,
                                                           'Price': shortPrice, 'TradedVolume': EMPTY_INT,
                                                           'OrderTime': self.curDateTime,
                                                           'Grid': grid}
                    # 属于开多委托单
                    else:
                        if order_symbol == self.Leg1Symbol:
                            buyPrice = max(self.lastLeg1Tick.askPrice1, self.lastLeg1Tick.lastPrice) + self.minDiff
                        else:
                            buyPrice = max(self.lastLeg2Tick.askPrice1, self.lastLeg2Tick.lastPrice) + self.minDiff

                        # 发送委托
                        orderID = self.ctaEngine.sendOrder(order_symbol, CTAORDER_BUY, buyPrice, order_volume, self)
                        if orderID is None or len(orderID) == 0:
                            self.writeCtaLog(u'重新提交{0} {1}手开多单{2}失败'.format(order_symbol, order_volume, buyPrice))
                            continue

                        # 添加到待删除的清单
                        canceled_keys.append(order_key)
                        # 更新网格的委托单
                        grid = order['Grid']
                        grid.orderRef = grid.orderRef.replace(order_key, orderID)
                        if buyPrice > order_price:
                            # 修正止盈点位
                            if grid.direction == DIRECTION_SHORT:
                                grid.closePrice -= (buyPrice - order_price)
                            else:
                                grid.closePrice += (buyPrice - order_price)

                        # 重新添加开空委托单
                        self.uncompletedOrders[orderID] = {'SYMBOL': order_symbol, 'DIRECTION': DIRECTION_LONG,
                                                           'OFFSET': OFFSET_OPEN, 'Volume': order_volume,
                                                           'Price': buyPrice, 'TradedVolume': EMPTY_INT,
                                                           'OrderTime': self.curDateTime,
                                                           'Grid': grid}

        # 删除撤单的订单
        for key in canceled_keys:
            if key in self.uncompletedOrders:
                self.writeCtaLog(u'删除orderID:{0}'.format(key))
                del self.uncompletedOrders[key]


    # ----------------------------------------------------------------------
    def saveData(self, id):
        """保存过程数据"""
        # 保存K线
        if not self.backtesting:
            return




