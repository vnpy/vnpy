# encoding: UTF-8

'''
本文件中实现了CTA策略引擎，针对CTA类型的策略，抽象简化了部分底层接口的功能。

关于平今和平昨规则：
1. 普通的平仓OFFSET_CLOSET等于平昨OFFSET_CLOSEYESTERDAY
2. 只有上期所的品种需要考虑平今和平昨的区别
3. 当上期所的期货有今仓时，调用Sell和Cover会使用OFFSET_CLOSETODAY，否则
   会使用OFFSET_CLOSE
4. 以上设计意味着如果Sell和Cover的数量超过今日持仓量时，会导致出错（即用户
   希望通过一个指令同时平今和平昨）
5. 采用以上设计的原因是考虑到vn.trader的用户主要是对TB、MC和金字塔类的平台
   感到功能不足的用户（即希望更高频的交易），交易策略不应该出现4中所述的情况
6. 对于想要实现4中所述情况的用户，需要实现一个策略信号引擎和交易委托引擎分开
   的定制化统结构（没错，得自己写）

 Modified by IncenseLee（李来佳）
 1、增加单一策略里，多个vtSymbol的配置。
 2、修改loadSetting和SaveSetting
'''

print('load ctaEngine.py')
import json
import os
import traceback
from collections import OrderedDict
from datetime import datetime, timedelta
import re
import csv
import copy
import decimal

from vnpy.trader.vtEvent import *
from vnpy.trader.vtConstant import *
from vnpy.trader.vtGateway import VtSubscribeReq, VtOrderReq, VtCancelOrderReq, VtLogData, VtSignalData
from vnpy.trader.app.ctaStrategy.ctaBase import *
from vnpy.trader.setup_logger import setup_logger
from vnpy.trader.vtFunction import todayDate, getJsonPath
from vnpy.trader.util_mail import sendmail
# 加载 strategy目录下所有的策略
from vnpy.trader.app.ctaStrategy.strategy import STRATEGY_CLASS
try:
    from vnpy.trader.util_wechat import *
except:
    print('import util_wechat fail')

MATRIX_DB_NAME = 'matrix'                               # 虚拟策略矩阵的数据库名称
POSITION_DISPATCH_COLL_NAME = 'position_dispatch'       # 虚拟策略矩阵的策略调度配置collection名称
POSITION_DISPATCH_HISTORY_COLL_NAME = 'position_dispatch_history'       # 虚拟策略矩阵的策略调度配置collection名称

########################################################################
class CtaEngine(object):
    """CTA策略引擎"""

    # 策略配置文件
    settingFileName = 'CTA_setting.json'
    settingfilePath = getJsonPath(settingFileName, __file__)

    # ----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine

        # 当前日期
        self.today = todayDate()

        # 保存策略实例的Dict
        # key为策略名称，value为策略实例，注意策略名称不允许重复
        self.strategyDict = {}

        # 保存策略设置的字典
        # key为策略名称，value为策略设置，注意策略名称不允许重复
        self.settingDict = {}

        # 保存vtSymbol和策略实例映射的字典（用于推送tick数据）
        # 由于可能多个strategy交易同一个vtSymbol，因此key为vtSymbol
        # value为包含所有相关strategy对象的list
        self.tickStrategyDict = {}

        # 保存vtOrderID和strategy对象映射的字典（用于推送order和trade数据）
        # key为vtOrderID，value为strategy对象
        self.orderStrategyDict = {}

        # 本地停止单编号计数
        self.stopOrderCount = 0
        # stopOrderID = STOPORDERPREFIX + str(stopOrderCount)

        # 本地停止单字典
        # key为stopOrderID，value为stopOrder对象
        self.stopOrderDict = {}  # 停止单撤销后不会从本字典中删除
        self.workingStopOrderDict = {}  # 停止单撤销后会从本字典中删除

        # 持仓缓存字典
        # key为vtSymbol，value为PositionBuffer对象
        self.posBufferDict = {}

        # 成交号集合，用来过滤已经收到过的成交推送
        self.tradeSet = set()

        # 引擎类型为实盘
        self.engineType = ENGINETYPE_TRADING

        # tick缓存
        self.tickDict = {}

        # 未能订阅的symbols
        self.pendingSubcribeSymbols = {}

        # 注册事件监听
        self.registerEvent()

        # 持仓调度的order_id记录
        self.dispatch_pos_order_dict = {}
        self.strategy_group = EMPTY_STRING

        self.logger = None
        self.strategy_loggers = {}
        self.createLogger()

    def analysis_vtSymbol(self, vtSymbol):
        """
        分析合约
        :param vtSymbol:
        :return:
        """
        base_symbol, quote_symbol,exchange = None,None,None

        if '.' not in vtSymbol:
            exchange = None
            symbol_pair = vtSymbol
        else:
            s1 = vtSymbol.split('.')
            exchange = s1[1]
            symbol_pair = s1[0]

        if '_' not in symbol_pair:
            return vtSymbol, quote_symbol,exchange

        s2 = symbol_pair.split('_')
        base_symbol = s2[0]
        quote_symbol = s2[1]
        return base_symbol, quote_symbol, exchange

    # ----------------------------------------------------------------------
    def sendOrder(self, vtSymbol, orderType, price, volume, strategy, priceType=PRICETYPE_LIMITPRICE):
        """发单"""
        base_symbol, quote_symbol, exchange = self.analysis_vtSymbol(vtSymbol)

        contract = self.mainEngine.getContract(vtSymbol)
        if contract is None:
            self.writeCtaError(
                u'vtEngine.sendOrder取不到{}合约得信息,{}发送{}委托:{},v{}失败'.format(vtSymbol, strategy.name, orderType, price,
                                                                         volume))
            return ''

        req = VtOrderReq()
        req.symbol = contract.symbol  # 合约代码
        req.exchange = contract.exchange # 交易所
        req.vtSymbol = contract.vtSymbol
        req.price = self.roundToPriceTick(contract.priceTick, price)  # 价格

        req.volume = self.roundToVolumeTick(volumeTick=contract.volumeTick,volume=volume)  # 数量

        if strategy:
            req.productClass = strategy.productClass
            req.currency = strategy.currency
        else:
            req.productClass = ''
            req.currency = ''

        # 设计为CTA引擎发出的委托只允许使用限价单
        # modified by incense, 通过参数传递
        req.priceType = priceType  # 价格类型

        # CTA委托类型映射
        if orderType == CTAORDER_BUY:
            req.direction = DIRECTION_LONG  # 合约方向
            req.offset = OFFSET_OPEN  # 开/平
        elif orderType == CTAORDER_SELL:
            req.direction = DIRECTION_SHORT

            # 只有上期所才要考虑平今平昨
            if contract.exchange != EXCHANGE_SHFE:
                req.offset = OFFSET_CLOSE
            else:
                # 获取持仓缓存数据
                posBuffer = self.posBufferDict.get(vtSymbol, None)
                # 如果获取持仓缓存失败，则默认平昨
                if not posBuffer:
                    self.writeCtaLog(u'获取持仓缓存失败，则默认平昨')
                    req.offset = OFFSET_CLOSE

                # modified by IncenseLee 2016/11/08，改为优先平昨仓
                elif posBuffer.longYd:
                    self.writeCtaLog(u'{}优先平昨，昨多仓:{}，平仓数:{}'.format(vtSymbol, posBuffer.longYd, volume))
                    req.offset = OFFSET_CLOSE
                    # if posBuffer.longYd >= volume:
                    #    posBuffer.longYd -= volume
                    #    self.writeCtaLog(u'{}剩余昨多仓{}'.format(vtSymbol,posBuffer.longYd))
                else:
                    self.writeCtaLog(u'{}平今,今多仓:{},{}'.format(vtSymbol, posBuffer.longToday, volume))
                    req.offset = OFFSET_CLOSETODAY
                    # if posBuffer.longToday >= volume:
                    #    posBuffer.longToday -= volume
                    #    self.writeCtaLog(u'{}剩余今多仓{}'.format(vtSymbol, posBuffer.longToday))

                # 否则如果有多头今仓，则使用平今
                # elif posBuffer.longToday:
                #    req.offset= OFFSET_CLOSETODAY
                # 其他情况使用平昨
                # else:
                #    req.offset = OFFSET_CLOSE

        elif orderType == CTAORDER_SHORT:
            req.direction = DIRECTION_SHORT
            req.offset = OFFSET_OPEN

        elif orderType == CTAORDER_COVER:
            req.direction = DIRECTION_LONG

            # 只有上期所才要考虑平今平昨
            if contract.exchange != EXCHANGE_SHFE:
                req.offset = OFFSET_CLOSE
            else:
                # 获取持仓缓存数据
                posBuffer = self.posBufferDict.get(vtSymbol, None)
                # 如果获取持仓缓存失败，则默认平昨
                if not posBuffer:
                    req.offset = OFFSET_CLOSE

                # modified by IncenseLee 2016/11/08，改为优先平昨仓
                elif posBuffer.shortYd:
                    self.writeCtaLog(u'{}优先平昨,昨空仓:{},平仓数:{}'.format(vtSymbol, posBuffer.shortYd, volume))
                    req.offset = OFFSET_CLOSE
                    # if posBuffer.shortYd >= volume:
                    #    posBuffer.shortYd -= volume
                    #    self.writeCtaLog(u'{}剩余昨空仓{}'.format(vtSymbol, posBuffer.shortYd))
                else:
                    self.writeCtaLog(u'{}平今,今空仓:{},平仓数:{}'.format(vtSymbol, posBuffer.shortToday, volume))
                    req.offset = OFFSET_CLOSETODAY
                    # if posBuffer.shortToday >= volume:
                    #    posBuffer.shortToday -= volume
                    #    self.writeCtaLog(u'{}剩余今空仓{}'.format(vtSymbol, posBuffer.shortToday))

                # 否则如果有空头今仓，则使用平今
                # elif posBuffer.shortToday:
                #    req.offset= OFFSET_CLOSETODAY
                # 其他情况使用平昨
                # else:
                #    req.offset = OFFSET_CLOSE

        vtOrderID = self.mainEngine.sendOrder(req, contract.gatewayName)  # 发单

        if vtOrderID is None or len(vtOrderID) == 0:
            self.writeCtaError(u'{} 发送委托失败. {} {} {} {}'.format(strategy.name if strategy else 'CtaEngine', vtSymbol, req.offset, req.direction, volume, price))
            return ''

        if strategy:
            self.orderStrategyDict[vtOrderID] = strategy  # 保存vtOrderID和策略的映射关系
            msg = u'策略%s发送委托，%s, %s，%s，%s@%s' % (strategy.name, vtSymbol, req.offset, req.direction, volume, price)
            self.writeCtaLog(msg)
        else:
            msg = u'%s发送委托，%s, %s，%s，%s@%s' % ('CtaEngine', vtSymbol, req.offset, req.direction, volume, price)
            self.writeCtaLog(msg)

        # 发送微信
        #try:
        #    sendWeChatMsg(msg, target=self.mainEngine.gatewayDetailList[0]['gatewayName'])
        #except:
        #    pass

        return vtOrderID

    # ----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """撤单"""
        # 查询报单对象
        # 1.调用主引擎接口，查询委托单对象
        order = self.mainEngine.getOrder(vtOrderID)

        # 如果查询成功
        if order:
            # 2.检查是否报单（委托单）还有效，只有有效时才发出撤单指令
            orderFinished = (order.status == STATUS_ALLTRADED or order.status == STATUS_CANCELLED)
            if not orderFinished:
                req = VtCancelOrderReq()
                req.symbol = order.symbol
                req.exchange = order.exchange
                req.frontID = order.frontID
                req.sessionID = order.sessionID
                req.orderID = order.orderID
                self.mainEngine.cancelOrder(req, order.gatewayName)

                # 发送微信
                #try:
                #    msg = u'发送撤单指令，%s, %s，%s' % (order.symbol, order.orderID, order.gatewayName)
                #    sendWeChatMsg(msg, target=self.mainEngine.gatewayDetailList[0]['gatewayName'])
                #except:
                #    pass
            else:
                if order.status == STATUS_ALLTRADED:
                    self.writeCtaLog(u'委托单({0}已执行，无法撤销'.format(vtOrderID))
                if order.status == STATUS_CANCELLED:
                    self.writeCtaLog(u'委托单({0}已撤销，无法再次撤销'.format(vtOrderID))
        # 查询不成功
        else:
            self.writeCtaLog(u'委托单({0}不存在'.format(vtOrderID))

    # ----------------------------------------------------------------------
    def cancelOrders(self, symbol, offset=EMPTY_STRING):
        """撤销所有单"""
        # Symbol参数:指定合约的撤单；
        # OFFSET参数:指定Offset的撤单,缺省不填写时，为所有

        l = self.mainEngine.getAllWorkingOrders()

        self.writeCtaLog(u'从所有订单{0}中撤销{1}'.format(len(l), symbol))

        for order in l:

            if symbol == EMPTY_STRING:
                symbolCond = True
            else:
                symbolCond = order.symbol == symbol

            if offset == EMPTY_STRING:
                offsetCond = True
            else:
                offsetCond = order.offset == offset

            if symbolCond and offsetCond:
                req = VtCancelOrderReq()
                req.symbol = order.symbol
                req.exchange = order.exchange
                req.frontID = order.frontID
                req.sessionID = order.sessionID
                req.orderID = order.orderID
                self.writeCtaLog(u'撤单:{0}/{1},{2}{3}手'
                                 .format(order.symbol, order.orderID, order.offset,
                                         order.totalVolume - order.tradedVolume))
                self.mainEngine.cancelOrder(req, order.gatewayName)

                # 发送微信
                #try:
                #    msg = u'撤销所有单，{}'.format(symbol)
                #    sendWeChatMsg(msg, target=self.mainEngine.gatewayDetailList[0]['gatewayName'])
                #except:
                #    pass

    # ----------------------------------------------------------------------
    def sendStopOrder(self, vtSymbol, orderType, price, volume, strategy):
        """发停止单（本地实现）"""

        # 1.生成本地停止单ID
        self.stopOrderCount += 1
        stopOrderID = STOPORDERPREFIX + str(self.stopOrderCount)

        # 2.创建停止单对象
        so = StopOrder()
        so.vtSymbol = vtSymbol  # 代码
        so.orderType = orderType  # 停止单类型
        so.price = price  # 价格
        so.volume = volume  # 数量
        so.strategy = strategy  # 来源策略
        so.stopOrderID = stopOrderID  # Id
        so.status = STOPORDER_WAITING  # 状态

        if orderType == CTAORDER_BUY:
            so.direction = DIRECTION_LONG
            so.offset = OFFSET_OPEN
        elif orderType == CTAORDER_SELL:
            so.direction = DIRECTION_SHORT
            so.offset = OFFSET_CLOSE
        elif orderType == CTAORDER_SHORT:
            so.direction = DIRECTION_SHORT
            so.offset = OFFSET_OPEN
        elif orderType == CTAORDER_COVER:
            so.direction = DIRECTION_LONG
            so.offset = OFFSET_CLOSE

            # 保存stopOrder对象到字典中
        self.stopOrderDict[stopOrderID] = so  # 字典中不会删除
        self.workingStopOrderDict[stopOrderID] = so  # 字典中会删除

        msg = u'发停止单成功，Id:{},Symbol:{},Type:{},Price:{},Volume:{}'.format(stopOrderID, vtSymbol, orderType, price, volume)
        self.writeCtaLog(msg)

        # 发送微信
        #try:#
        #    sendWeChatMsg(msg, target=self.mainEngine.gatewayDetailList[0]['gatewayName'])
        #except:
        #    pass
        return stopOrderID

    # ----------------------------------------------------------------------
    def cancelStopOrder(self, stopOrderID):
        """撤销停止单
        Incense Li modified 20160124：
        增加返回True 和 False
        """
        # 1.检查停止单是否存在
        if stopOrderID in self.workingStopOrderDict:
            so = self.workingStopOrderDict[stopOrderID]
            so.status = STOPORDER_CANCELLED  # STOPORDER_WAITING =》STOPORDER_CANCELLED
            del self.workingStopOrderDict[stopOrderID]  # 删除
            self.writeCtaLog(u'撤销停止单:{0}成功.'.format(stopOrderID))

            # 发送微信
            #try:
            #    sendWeChatMsg(u'撤销停止单:{0}成功.'.format(stopOrderID), target=self.mainEngine.gatewayDetailList[0]['gatewayName'])
            #except:
            #    pass
            return True
        else:
            self.writeCtaLog(u'撤销停止单:{0}失败，不存在Id.'.format(stopOrderID))

            # 发送微信
            #try:
            #    sendWeChatMsg(u'撤销停止单:{0}失败，不存在Id.'.format(stopOrderID), target=self.mainEngine.gatewayDetailList[0]['gatewayName'])
            #except:
            #    pass
            return False

    # ----------------------------------------------------------------------
    def processStopOrder(self, tick):
        """收到行情后处理本地停止单（检查是否要立即发出）"""
        vtSymbol = tick.vtSymbol

        # 1.首先检查是否有策略交易该合约
        if vtSymbol in self.tickStrategyDict:
            # 2.遍历等待中的停止单，检查是否会被触发
            for so in (self.workingStopOrderDict.values()):
                if so.vtSymbol == vtSymbol:
                    # 3. 触发标识判断
                    longTriggered = so.direction == DIRECTION_LONG and tick.lastPrice >= so.price  # 多头停止单被触发
                    shortTriggered = so.direction == DIRECTION_SHORT and tick.lastPrice <= so.price  # 空头停止单被触发

                    # 4.触发处理
                    if longTriggered or shortTriggered:

                        # 5.设定价格，买入和卖出分别以涨停跌停价发单（模拟市价单）
                        if so.direction == DIRECTION_LONG:
                            price = tick.upperLimit
                        else:
                            price = tick.lowerLimit

                        # 6.更新停止单状态，触发
                        so.status = STOPORDER_TRIGGERED

                        # 7.发单
                        self.sendOrder(so.vtSymbol, so.orderType, price, so.volume, so.strategy)

                        # 8.删除停止单
                        del self.workingStopOrderDict[so.stopOrderID]

    # ----------------------------------------------------------------------
    def procecssTickEvent(self, event):
        """处理行情推送事件"""

        # 1. 获取事件的Tick数据
        tick = event.dict_['data']
        tick = copy.copy(tick)
        # 移除待订阅的合约清单
        if tick.vtSymbol in self.pendingSubcribeSymbols:
            self.writeCtaLog(u'已成功订阅{0}，从待订阅清单中移除'.format(tick.vtSymbol))
            del self.pendingSubcribeSymbols[tick.vtSymbol]

        # 缓存最新tick
        self.tickDict[tick.vtSymbol] = tick

        # 2.收到tick行情后，优先处理本地停止单（检查是否要立即发出）
        self.processStopOrder(tick)

        # 3.推送tick到对应的策略对象进行处理
        if tick.vtSymbol in self.tickStrategyDict:

            # 4.将vtTickData数据转化为ctaTickData
            ctaTick = CtaTickData()
            d = ctaTick.__dict__
            for key in d.keys():
                if key in tick.__dict__:
                    d[key] = tick.__getattribute__(key)

            if not ctaTick.datetime:
                # 添加datetime字段
                tickDate = tick.date.replace('-', '')
                ctaTick.datetime = datetime.strptime(' '.join([tickDate, tick.time]), '%Y%m%d %H:%M:%S.%f')

            # 逐个推送到策略实例中
            l = self.tickStrategyDict[tick.vtSymbol]
            for strategy in l:
                self.callStrategyFunc(strategy, strategy.onTick, ctaTick)

    # ----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """处理委托推送事件"""
        # 1.获取事件的Order数据
        order = event.dict_['data']

        # order.vtOrderID 在gateway中，已经格式化为 gatewayName.vtOrderID

        # 2.判断order是否在策略的映射字典中
        if order.vtOrderID in self.orderStrategyDict:
            # 3.提取对应的策略
            strategy = self.orderStrategyDict[order.vtOrderID]
            # 4.触发策略的委托推送事件方法
            strategy.onOrder(order)
        else:
            # 检查调度的平仓
            self.onOrder_dispatch_close_pos(order)

    # ----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """处理成交推送事件"""

        # 1.获取事件的Trade数据
        trade = event.dict_['data']

        # 过滤已经收到过的成交回报
        if trade.vtTradeID in self.tradeSet:
            return
        self.tradeSet.add(trade.vtTradeID)

        # 将成交推送到策略对象中
        if trade.vtOrderID in self.orderStrategyDict:
            # 3.提取对应的策略
            strategy = self.orderStrategyDict[trade.vtOrderID]

            # 计算策略持仓 ( canceled by IncenseLee )
            # if trade.direction == DIRECTION_LONG:
            #    strategy.pos += trade.volume
            # else:
            #    strategy.pos -= trade.volume

            self.callStrategyFunc(strategy, strategy.onTrade, trade)

        # 更新持仓缓存数据
        if trade.vtSymbol in self.tickStrategyDict:
            posBuffer = self.posBufferDict.get(trade.vtSymbol, None)
            if not posBuffer:
                posBuffer = PositionBuffer()
                posBuffer.vtSymbol = trade.vtSymbol
                self.posBufferDict[trade.vtSymbol] = posBuffer
            posBuffer.updateTradeData(trade)

    # ----------------------------------------------------------------------

    def processPositionEvent(self, event):
        """处理持仓推送"""
        pos = event.dict_['data']

        # 更新持仓缓存数据
        if True:  # pos.vtSymbol in self.tickStrategyDict:
            posBuffer = self.posBufferDict.get(pos.vtSymbol, None)
            if not posBuffer:
                posBuffer = PositionBuffer()
                posBuffer.vtSymbol = pos.vtSymbol
                self.posBufferDict[pos.vtSymbol] = posBuffer
            posBuffer.updatePositionData(pos)

    # ----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""

        # 注册行情数据推送（Tick数据到达）的响应事件
        self.eventEngine.register(EVENT_TICK, self.procecssTickEvent)

        # 注册订单推送的响应事件
        self.eventEngine.register(EVENT_ORDER, self.processOrderEvent)

        # 注册成交推送（交易）的响应时间
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)

        # 注册持仓更新事件
        self.eventEngine.register(EVENT_POSITION, self.processPositionEvent)

        # 账号更新事件（借用账号更新事件，来检查是否有未订阅的合约信息）
        self.eventEngine.register(EVENT_ACCOUNT, self.checkUnsubscribedSymbols)

        # 注册定时器事件
        self.eventEngine.register(EVENT_TIMER, self.processTimerEvent)

        # 注册强制止损事件
        self.eventEngine.register(EVENT_ACCOUNT_LOSS, self.processAccoutLossEvent)

        # 注册定时清除dispatch临时持仓

    def processAccoutLossEvent(self, event):
        """处理止损时间"""
        balance = event.dict_['data']
        self.writeCtaLog(u'净值{0}低于止损线，执行强制止损'.format(balance))
        self.mainEngine.writeLog(u'净值{0}低于止损线，执行强制止损'.format(balance))

        self.cancelOrders(symbol=EMPTY_STRING)

        for posBuffer in (self.posBufferDict.values()):

            if posBuffer.shortYd > 0:
                self.writeCtaLog(u'{0}合约持有昨空单{1}手，强平'.format(posBuffer.vtSymbol, posBuffer.shortYd))
                tick = self.tickDict.get(posBuffer.vtSymbol, None)

                if not tick:
                    self.writeCtaLog(u'找不对{0}的最新Tick数据'.format(posBuffer.vtSymbol))
                    continue

                self.sendOrder(posBuffer.vtSymbol, orderType=CTAORDER_COVER, price=tick.upperLimit,
                               volume=posBuffer.shortYd, strategy=None)

            if posBuffer.shortToday > 0:
                self.writeCtaLog(u'{0}合约持有今空单{1}手，强平'.format(posBuffer.vtSymbol, posBuffer.shortToday))
                tick = self.tickDict.get(posBuffer.vtSymbol, None)

                if not tick:
                    self.writeCtaLog(u'找不对{0}的最新Tick数据'.format(posBuffer.vtSymbol))
                    continue

                self.sendOrder(posBuffer.vtSymbol, orderType=CTAORDER_COVER, price=tick.upperLimit,
                               volume=posBuffer.shortToday, strategy=None)

            if posBuffer.longYd > 0:
                self.writeCtaLog(u'{0}合约持有昨多单{1}手，强平'.format(posBuffer.vtSymbol, posBuffer.longYd))
                tick = self.tickDict.get(posBuffer.vtSymbol, None)

                if not tick:
                    self.writeCtaLog(u'找不对{0}的最新Tick数据'.format(posBuffer.vtSymbol))
                    continue

                self.sendOrder(posBuffer.vtSymbol, orderType=CTAORDER_SELL, price=tick.lowerLimit,
                               volume=posBuffer.longYd, strategy=None)

            if posBuffer.longToday > 0:
                self.writeCtaLog(u'{0}合约持有今多单{1}手，强平'.format(posBuffer.vtSymbol, posBuffer.longToday))
                tick = self.tickDict.get(posBuffer.vtSymbol, None)

                if not tick:
                    self.writeCtaLog(u'找不对{0}的最新Tick数据'.format(posBuffer.vtSymbol))
                    continue

                self.sendOrder(posBuffer.vtSymbol, orderType=CTAORDER_SELL, price=tick.lowerLimit,
                               volume=posBuffer.longToday, strategy=None)

    def processTimerEvent(self, event):
        """定时器事件"""

        # 触发每个策略的定时接口
        for strategy in list(self.strategyDict.values()):
            strategy.onTimer()

    # ----------------------------------------------------------------------
    def insertData(self, dbName, collectionName, data):
        """插入数据到数据库（这里的data可以是CtaTickData或者CtaBarData）"""
        self.mainEngine.dbInsert(dbName, collectionName, data.__dict__)

    # ----------------------------------------------------------------------
    def loadBar(self, dbName, collectionName, days):
        """从数据库中读取Bar数据，startDate是datetime对象"""
        startDate = self.today - timedelta(days)

        d = {'datetime': {'$gte': startDate}}
        barData = self.mainEngine.dbQuery(dbName, collectionName, d)

        l = []
        for d in barData:
            bar = CtaBarData()
            bar.__dict__ = d
            l.append(bar)

        return l

    # ----------------------------------------------------------------------

    def loadTick(self, dbName, collectionName, days):
        """从数据库中读取Tick数据，startDate是datetime对象"""
        startDate = self.today - timedelta(days)

        d = {'datetime': {'$gte': startDate}}
        tickData = self.mainEngine.dbQuery(dbName, collectionName, d)

        l = []
        for d in tickData:
            tick = CtaTickData()
            tick.__dict__ = d
            l.append(tick)

        return l

        # ----------------------------------------------------------------------

    # 日志相关
    def writeCtaLog(self, content, strategy_name=None):
        """快速发出CTA模块日志事件"""
        log = VtLogData()
        log.logContent = content
        event = Event(type_=EVENT_CTA_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)

        if strategy_name is None:
            # 写入本地log日志
            if self.logger:
                self.logger.info(content)
            else:
                self.createLogger()
        else:
            if strategy_name in self.strategy_loggers:
                self.strategy_loggers[strategy_name].info(content)
            else:
                self.createLogger(strategy_name=strategy_name)

    def createLogger(self, strategy_name=None):
        """
        创建日志记录
        :return:
        """
        currentFolder = os.path.abspath(os.path.join(os.getcwd(), 'logs'))
        if os.path.isdir(currentFolder):
            # 如果工作目录下，存在data子目录，就使用data子目录
            path = currentFolder
        else:
            # 否则，使用缺省保存目录 vnpy/trader/app/ctaStrategy/data
            path = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', 'logs'))

        if strategy_name is None:
            filename = os.path.abspath(os.path.join(path, 'ctaEngine'))

            print(u'create logger:{}'.format(filename))
            self.logger = setup_logger(filename=filename, name='ctaEngine', debug=True)
        else:
            filename = os.path.abspath(os.path.join(path, str(strategy_name)))
            print(u'create logger:{}'.format(filename))
            self.strategy_loggers[strategy_name] = setup_logger(filename=filename, name=str(strategy_name), debug=True)

    def writeCtaError(self, content, strategy_name=None):
        """快速发出CTA模块错误日志事件"""
        if strategy_name is not None:
            if strategy_name in self.strategy_loggers:
                self.strategy_loggers[strategy_name].error(content)
            else:
                self.createLogger(strategy_name=strategy_name)
                try:
                    self.strategy_loggers[strategy_name].error(content)
                except Exception as ex:
                    pass

        self.mainEngine.writeError(content)

    def writeCtaWarning(self, content, strategy_name=None):
        """快速发出CTA模块告警日志事件"""
        if strategy_name is not None:
            if strategy_name in self.strategy_loggers:
                self.strategy_loggers[strategy_name].warning(content)
            else:
                self.createLogger(strategy_name=strategy_name)
                try:
                    self.strategy_loggers[strategy_name].warning(content)
                except Exception as ex:
                    pass
        self.mainEngine.writeWarning(content)

    def writeCtaNotification(self, content, strategy_name=None):
        """快速发出CTA模块通知事件"""
        self.mainEngine.writeNotification(content)

    def writeCtaCritical(self, content, strategy_name=None):
        """快速发出CTA模块异常日志事件"""
        if strategy_name is not None:
            if strategy_name in self.strategy_loggers:
                self.strategy_loggers[strategy_name].critical(content)
            else:
                self.createLogger(strategy_name=strategy_name)
                try:
                    self.strategy_loggers[strategy_name].critical(content)
                except Exception as ex:
                    pass
        self.mainEngine.writeCritical(content)

    def sendAlertToWechat(self,content,target):
        """发送微信告警"""
        gw = EMPTY_STRING
        if len(self.mainEngine.connected_gw_names)>0:
            gw = self.mainEngine.connected_gw_names[0]
        else:
            if len(self.mainEngine.gatewayDetailList) > 0:
                d = self.mainEngine.gatewayDetailList[0]
                if isinstance(d, dict):
                    gw = d.get('gatewayDisplayName','Gateway')

        if len(gw)>0:
            content = u'[gw:{}]{}'.format(gw,content)
        try:
            from vnpy.trader import util_wechat
            self.writeCtaLog(u'发送微信通知:{}'.format(content))
            util_wechat.sendWeChatMsg(content=content, target=target,level=util_wechat.WECHAT_LEVEL_DEBUG)
        except Exception as ex:
            self.writeCtaError(u'调用微信接口失败:{} {}'.format(str(ex), traceback.format_exc()))

    def sendCtaSignal(self, source, symbol, direction, price, level):
        """发出交易信号"""
        s = VtSignalData()
        s.source = source
        s.symbol = symbol
        s.direction = direction
        s.price = price
        s.level = level
        event = Event(type_=EVENT_SIGNAL)
        event.dict_['data'] = s
        self.eventEngine.put(event)

    # ----------------------------------------------------------------------
    # 订阅合约相关
    def subscribe(self, strategy, symbol):
        """订阅合约，不成功时，加入到待订阅列表"""
        contract = self.mainEngine.getContract(symbol)

        if contract:
            # 4.构造订阅请求包
            req = VtSubscribeReq()
            req.symbol = contract.symbol
            req.exchange = contract.exchange

            # 对于IB接口订阅行情时所需的货币和产品类型，从策略属性中获取
            if hasattr(strategy,'currency'):
                req.currency = strategy.currency
            if hasattr(strategy, 'productClass'):
                req.productClass = strategy.productClass

            # 5.调用主引擎的订阅接口
            self.mainEngine.subscribe(req, contract.gatewayName)
        else:
            print(u'Warning, can not find {0} in contracts'.format(symbol))
            self.writeCtaLog(u'交易合约{}无法找到，添加到待订阅列表'.format(symbol))
            self.pendingSubcribeSymbols[symbol] = strategy

    def checkUnsubscribedSymbols(self, event):
        """持仓更新信息时，检查未提交的合约"""
        for symbol in self.pendingSubcribeSymbols.keys():
            contract = self.mainEngine.getContract(symbol)
            if contract:
                # 获取合约的缩写号
                s = self.getShortSymbol(symbol)
                # if s == symbol:    # 合约缩写提取失败
                #    continue
                dt = datetime.now()
                # 若为中金所的合约，白天才提交订阅请求
                if s in MARKET_ZJ and not (9 < dt.hour < 16):
                    continue

                self.writeCtaLog(u'重新提交合约{0}订阅请求'.format(symbol))
                strategy = self.pendingSubcribeSymbols[symbol]
                self.subscribe(strategy=strategy, symbol=symbol)

    # ----------------------------------------------------------------------
    # 策略相关（加载/初始化/启动/停止)
    def checkStrategy(self, name):
        """
        检查策略
        :param name:
        :return: NOTRUN：没有运行；RUNING：正常运行；FORCECLOSING:正在关闭;FORCECLOSED:已经关闭
        """
        if name not in self.strategyDict:
            return NOTRUN

        strategy = self.strategyDict[name]
        if hasattr(strategy, 'forceTradingClose'):
            if strategy.forceTradingClose == False:
                return RUNING

            if strategy.trading:
                return FORCECLOSING
            else:
                return FORCECLOSED

        return RUNING

    def loadStrategy(self, setting, is_dispatch=False):
        """
        载入策略
        :param setting: 策略设置参数
        :param is_dispatch: 是否为调度
        :return:
        """
        try:
            name = setting['name']
            className = setting['className']
        except Exception as e:
            self.writeCtaLog(u'载入策略出错：%s' % e)
            self.mainEngine.writeCritical(u'载入策略出错：%s' % e)
            return False

        # 获取策略类
        strategyClass = STRATEGY_CLASS.get(className, None)
        if not strategyClass:
            self.writeCtaLog(u'STRATEGY_CLASS找不到策略类：%s' % className)
            self.mainEngine.writeCritical(u'STRATEGY_CLASS找不到策略类：%s' % className)
            return False

        if is_dispatch:
            # 属于调度
            runing_status = self.checkStrategy(name)
            if name in self.settingDict:
                if runing_status == RUNING:
                    self.writeCtaLog(u'策略{}正常运行，不做加载'.format(name))
                    return False
                elif runing_status in [FORCECLOSING, FORCECLOSED]:
                    try:
                        cur_strategy = self.strategyDict[name]
                        cur_strategy.cancelForceClose()
                        self.settingDict[name] = setting
                        self.writeCtaLog(u'撤销运行中策略{}的强制清仓，恢复运行'.format(name))
                        return False
                    except Exception as ex:
                        self.writeCtaCritical(u'撤销运行中策略{}的强制清仓时异常：{},{}'.format(name, str(ex),traceback.format_exc()))

                        return False
        else:
            # 防止策略重名
            if name in self.strategyDict:
                self.writeCtaLog(u'策略实例重名：%s' % name)
                return False

            # 检查策略中的forceClose，如果当前日期超过最后平仓日期一周，不再启动。
            if 'forceClose' in setting:
                try:
                    forceCloseDate = datetime.strptime(setting['forceClose'], '%Y-%m-%d')
                    dt = datetime.now()
                    if (dt - forceCloseDate).days > 7:
                        self.writeCtaLog(u'日期超过最后平仓日期,不再启动')
                        return False
                except Exception as ex:
                    self.writeCtaCritical(u'配置文件的强制平仓日期提取异常:{}'.format(str(ex)))
                    traceback.print_exc()

        self.settingDict[name] = setting

        # 1.创建策略对象
        strategy = strategyClass(self, setting)
        self.strategyDict[name] = strategy

        # 2.保存Tick映射关系（symbol <==> Strategy[] )
        # modifid by Incenselee 支持多个Symbol的订阅
        symbols = []
        # 套利合约
        if strategy.vtSymbol.find(' ') != -1:
            # 排除SP SPC SPD
            s = strategy.vtSymbol.split(' ')
            if len(s) > 1:
                arb_symbols = s[1]

                # 只提取leg1合约
                if arb_symbols.find('&') != -1:
                    symbols = arb_symbols.split('&')
                symbols.append(strategy.vtSymbol)
            else:
                symbols.append(s[0])
        else:
            symbols = strategy.vtSymbol.split(';')

        # 数字货币 btc_usdt.OKEX
        #if strategy.vtSymbol.find('.') != -1:
        #    symbol_pairs = strategy.vtSymbol.split('.')
        #    if len(symbol_pairs)==2:
        #        symbols.append(symbol_pairs[0])

        # 判断是否有Leg1Symbol,Leg2Symbol 两个合约属性
        if hasattr(strategy, 'Leg1Symbol'):
            if strategy.Leg1Symbol not in symbols:
                symbols.append(strategy.Leg1Symbol)
        if hasattr(strategy, 'Leg2Symbol'):
            if strategy.Leg2Symbol not in symbols:
                symbols.append(strategy.Leg2Symbol)

        for symbol in symbols:
            self.writeCtaLog(u'添加合约{}与策略{}的匹配目录'.format(symbol,strategy.name))
            if symbol in self.tickStrategyDict:
                l = self.tickStrategyDict[symbol]
            else:
                l = []
                self.tickStrategyDict[symbol] = l
            l.append(strategy)

            # 3.订阅合约
            self.writeCtaLog(u'向gateway订阅合约{0}'.format(symbol))
            self.pendingSubcribeSymbols[symbol] = strategy
            self.subscribe(strategy=strategy, symbol=symbol)

        # 自动初始化
        if 'auto_init' in setting:
            if setting['auto_init'] == True:
                self.writeCtaLog(u'自动初始化策略：{}'.format(name))
                try:
                    self.initStrategy(name=name)
                except Exception as ex:
                    self.writeCtaCritical(u'初始化策略：{} 异常,{},{}'.format(name,str(ex),traceback.format_exc()))
                    return False

        if 'auto_start' in setting:
            if setting['auto_start'] == True:
                self.writeCtaLog(u'自动启动策略：{}'.format(name))
                try:
                    self.startStrategy(name=name)
                except Exception as ex:
                    self.writeCtaCritical(u'自动启动策略：{} 异常,{},{}'.format(name, str(ex), traceback.format_exc()))
                    return False
        return True

    def initStrategy(self, name, force=False):
        """初始化策略"""
        if name in self.strategyDict:
            strategy = self.strategyDict[name]

            if not strategy.inited or force == True:
                self.callStrategyFunc(strategy, strategy.onInit, force)
                # strategy.onInit(force=force)
                # strategy.inited = True
            else:
                self.writeCtaLog(u'请勿重复初始化策略实例：%s' % name)
        else:
            self.writeCtaError(u'策略实例不存在：%s' % name)

    def startStrategy(self, name):
        """启动策略"""
        # 1.判断策略名称是否存在字典中
        if name in self.strategyDict:

            # 2.提取策略
            strategy = self.strategyDict[name]

            # 3.判断策略是否运行
            if strategy.inited and not strategy.trading:
                # 4.设置运行状态
                strategy.trading = True
                # 5.启动策略
                self.callStrategyFunc(strategy, strategy.onStart)
        else:
            self.writeCtaError(u'策略实例不存在：%s' % name)

    def stopStrategy(self, name):
        """停止策略运行"""
        # 1.判断策略名称是否存在字典中
        if name in self.strategyDict:
            # 2.提取策略
            strategy = self.strategyDict[name]

            # 3.停止交易
            if strategy.trading:
                # 4.设置交易状态为False
                strategy.trading = False
                # 5.调用策略的停止方法
                self.callStrategyFunc(strategy, strategy.onStop)

                # 6.对该策略发出的所有限价单进行撤单
                for vtOrderID, s in self.orderStrategyDict.items():
                    if s is strategy:
                        self.cancelOrder(vtOrderID)

                # 7.对该策略发出的所有本地停止单撤单
                for stopOrderID, so in self.workingStopOrderDict.items():
                    if so.strategy is strategy:
                        self.cancelStopOrder(stopOrderID)
        else:
            self.writeCtaError(u'策略实例不存在：%s' % name)

    def removeStrategy(self, strategy_name):
        """
        移除策略
        :param strategy_name: 策略实例名
        :return: True/False，errMsg
        """
        # 移除策略设置,下次启动不再执行该设置
        if strategy_name in self.settingDict:
            self.settingDict.pop(strategy_name, None)

        try:
            strategy = self.strategyDict[strategy_name]

            # 1、将运行dict的策略移除.
            self.strategyDict[strategy_name] = None
            self.writeCtaLog(u'将运行dict的策略{}关联移除'.format(strategy_name))
            self.strategyDict.pop(strategy_name, None)

            strategy.trading = False

            # 2、撤销所有委托单
            if hasattr(strategy, 'cancelAllOrders'):
                strategy.cancelAllOrders()

            # 3、将策略的持仓，登记在dispatch_long_pos/dispatch_short_pos,移除json文件
            if strategy.inited and strategy.position is not None and (
                    strategy.position.longPos != 0 or strategy.position.shortPos != 0):
                strategy.inited = False
                pos_list = strategy.getPositions()
                self.writeCtaLog(u'被移除策略{}的持仓情况:{}'.format(strategy.name, pos_list))
                if len(pos_list) > 0:
                    for pos in pos_list:
                        # 添加多头持仓
                        if pos['direction'] == DIRECTION_LONG and pos['volume'] > 0:
                            symbol = pos['vtSymbol']

                            d = {
                                'strategy_group': self.strategy_group,
                                'strategy': strategy.name,
                                'vtSymbol': symbol,
                                'direction': 'long',
                                'volume': pos['volume'],
                                'expire_datetime': datetime.now() + timedelta(minutes=3),
                                'retry': 0
                            }
                            self.writeCtaLog(u'插入持仓信息到数据库:{}'.format(d))
                            self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, d)

                            # 添加到历史记录
                            h = {'strategy_group': self.strategy_group,
                                 'strategy': strategy.name, 'vtSymbol': symbol, 'direction': 'long',
                                 'volume': pos['volume'], 'action': 'add', 'comment': 'removed_strategy',
                                 'result': True, 'datetime': datetime.now()}
                            self.writeCtaLog(u'插入记录信息到数据库:{}'.format(h))
                            self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)

                        # 添加空头持仓
                        if pos['direction'] == DIRECTION_SHORT and pos['volume'] > 0:
                            symbol = pos['vtSymbol']

                            d = {
                                'strategy_group': self.strategy_group,
                                'strategy': strategy.name,
                                'vtSymbol': symbol,
                                'direction': 'short',
                                'volume': pos['volume'],
                                'expire_datetime': datetime.now() + timedelta(minutes=3),
                                'retry': 0
                            }
                            self.writeCtaLog(u'插入持仓信息到数据库:{}'.format(d))
                            self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, d)

                            # 添加到历史记录
                            h = {'strategy_group': self.strategy_group,
                                 'strategy': strategy.name, 'vtSymbol': symbol, 'direction': 'short',
                                 'volume': pos['volume'], 'action': 'add', 'comment': 'removed_strategy',
                                 'result': True, 'datetime': datetime.now()}
                            self.writeCtaLog(u'插入记录信息到数据库:{}'.format(h))
                            self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)

                    self.writeCtaLog(u'调度仓位添加完毕')

            # 4、清除策略持仓持久化文件
            if strategy.gt:
                # 删除策略持仓文件
                remove_json_file = strategy.gt.getJsonFilePath()
                if isinstance(remove_json_file, str) and os.path.isfile(remove_json_file):
                    try:
                        self.writeCtaLog(u'删除策略持仓文件{}'.format(remove_json_file))
                        os.remove(remove_json_file)
                    except Exception as ex:
                        self.writeCtaError(u'{}异常{},{}'.format(datetime.now(), str(ex), traceback.format_exc()))

            # 5、设置策略状态为停止
            strategy.onStop()

            # 6、将策略从tick的接收列表中移除
            symbols = strategy.vtSymbol.split(';')

            for symbol in symbols:
                if symbol in self.tickStrategyDict:
                    self.writeCtaLog(u'将策略{}从合约{}-策略列表中移除'.format(strategy.name, symbol))
                    symbol_strategy_list = self.tickStrategyDict[symbol]
                    if strategy in symbol_strategy_list:
                        self.writeCtaLog(u'移除策略{}的{}订阅'.format(strategy.name, symbol))
                        symbol_strategy_list.remove(strategy)
                    else:
                        self.writeCtaError(u'策略{}在合约{}订阅列表中找不到'.format(strategy.name, symbol))
                else:
                    self.writeCtaError(u'没有找到合约{}的策略列表'.format(symbol))

            return True, ''

        except Exception as ex:
            errMsg = u'移除策略异常:{},{}'.format(str(ex), traceback.format_exc())
            self.writeCtaCritical(errMsg)
            traceback.print_exc()
            return False, errMsg

    def get_data_path(self):
        """
        获取CTA策略的对应数据目录
        :return:
        """
        # 工作目录
        currentFolder = os.path.abspath(os.path.join(os.getcwd(), u'data'))
        if os.path.isdir(currentFolder):
            # 如果工作目录下，存在data子目录，就使用data子目录
            path = currentFolder
        else:
            # 否则，使用缺省保存目录 vnpy/trader/app/ctaStrategy/data
            path = os.path.abspath(os.path.join(os.path.dirname(__file__), u'data'))

        return path

    def get_logs_path(self):
        """
        获取CTA策略的对应日志目录
        :return:
        """
        # 工作目录
        logsFolder = os.path.abspath(os.path.join(os.getcwd(), u'logs'))
        if not os.path.exists(logsFolder):
            os.mkdir(logsFolder)
        return logsFolder

    def set_strategy_group(self,strategy_group):
        """
        更新策略组名称
        :param strategy_group:
        :return:
        """
        if self.strategy_group!=strategy_group:
            self.writeCtaLog(u'更新策略组名：{}=>{}'.format(self.strategy_group, strategy_group))
            self.strategy_group = strategy_group

    def clear_dispatch_pos(self):
        """
        对调度转移的剩余仓位，进行清仓
        要考虑涨跌停的情况哦。
        :return: 
        """
        # 针对国内期货市场，初步判断是否在交易时间内
        if self.is_trade_off():
            return

        self.writeCtaLog(u'开始对调度转移的剩余仓位，进行清仓')
        flt = {'strategy_group': self.strategy_group, 'expire_datetime': {'$lt': datetime.now()}}
        expired_pos_list = []
        try:
            expired_pos_list = self.mainEngine.dbQuery(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, d=flt)
        except Exception as ex:
            self.writeCtaLog(u'clear_dispatch_pos exception:{},{}'.format(str(ex), traceback.format_exc()))
            return

        if len(expired_pos_list) == 0:
            self.writeCtaLog(u'clear_dispatch_pos，没有调度剩余的仓位')
            return

        for expired_pos in expired_pos_list:
            if expired_pos['volume'] == 0:
                self.writeCtaError(u'clear_dispatch_pos，pos 为空：{},删除'.format(expired_pos))
                flt = {'_id': expired_pos['_id']}
                self.mainEngine.dbDelete(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, flt)
                continue

            # 检查是否在交易时间内
            symbol = expired_pos['vtSymbol']
            short_symbol = self.getShortSymbol(symbol)
            if not self.is_trade_window(short_symbol):
                self.writeCtaLog(u'{}不在交易时间内，不处理'.format(symbol))
                continue

            # 检查是否有缓存的tick
            tick = self.tickDict.get(expired_pos['vtSymbol'], None)
            if not tick:
                self.writeCtaLog(u'clear_dispatch_pos，找不对{}的最新Tick数据,暂时不能平仓'.format(expired_pos['vtSymbol']))
                # 可能是没订阅
                contract = self.mainEngine.getContract(expired_pos['vtSymbol'])
                if contract:
                    req = VtSubscribeReq()
                    req.symbol = contract.symbol
                    req.exchange = contract.exchange
                    # .调用主引擎的订阅接口
                    self.writeCtaLog(u'调用主引擎的订阅接口:{}'.format(expired_pos['vtSymbol']))
                    self.mainEngine.subscribe(req, gatewayName=None)

                expired_pos['datetime'] = datetime.now() + timedelta(minutes=10)
                expired_pos['retry'] += 1
                flt = {'_id': expired_pos['_id']}
                self.mainEngine.dbUpdate(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, expired_pos, flt)
                self.writeCtaLog(u'更新下次检查的时间:{}'.format(expired_pos))
                continue

            # 如果是多单
            if expired_pos['direction'] == 'long':
                curPos = self.posBufferDict.get(expired_pos['vtSymbol'], None)
                if curPos is None:
                    self.writeCtaCritical(u'ctaEngine.clear_dispatch_pos,{}没有在持仓中'.format(expired_pos['vtSymbol']))
                    h = {'strategy_group': self.strategy_group, 'strategy': 'clear_dispatch_pos',
                         'vtSymbol': expired_pos['vtSymbol'], 'direction': expired_pos['direction'],
                         'volume': expired_pos['volume'], 'action': 'clean',
                         'comment': 'no_positions_info,retry:{}'.format(expired_pos['retry']),
                         'result': False, 'datetime': datetime.now()}
                    self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME,h)

                    # 没有持仓，可能是onPosition还没到。 retry低于三次，延长更新时间
                    if expired_pos['retry'] <= 3:
                        expired_pos['retry'] += 1
                        expired_pos['datetime'] = datetime.now() + timedelta(minutes=2)
                        flt = {'_id': expired_pos['_id']}
                        self.mainEngine.dbUpdate(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, expired_pos, flt)
                        self.writeCtaLog(u'更新下次检查的时间:{}'.format(expired_pos))
                    else:
                        self.writeCtaCritical(u'clear_dispatch_pos,持仓信息 为空，尝试超过三次：{},删除'.format(expired_pos))
                        flt = {'_id': expired_pos['_id']}
                        self.mainEngine.dbDelete(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, flt)
                    continue

                sell_longYd, sell_longToday = 0, 0
                self.writeCtaLog(u'{}持仓昨{}/今{}'.format(expired_pos['vtSymbol'], curPos.longYd, curPos.longToday))

                if curPos.longYd + curPos.longToday < expired_pos['volume']:
                    self.writeCtaCritical(
                        u'{} ctaEngineclear_dispatch_pos, 持仓昨{}/今{},不满足平仓数量{}'.format(datetime.now(), curPos.longYd,
                                                                                      curPos.longToday, expired_pos['volume']))
                    sell_longYd, sell_longToday = curPos.longYd, curPos.longToday
                    h = {'strategy_group': self.strategy_group, 'strategy': 'clear_dispatch_pos',
                         'vtSymbol': expired_pos['vtSymbol'], 'direction': expired_pos['direction'],
                         'volume': curPos.longYd + curPos.longToday, 'action': 'clean',
                         'comment': 'part satisfied,require:{}'.format(expired_pos['volume']),
                         'result': True, 'datetime': datetime.now()}
                    self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)

                else:
                    if curPos.longYd >= expired_pos['volume']:
                        sell_longYd = expired_pos['volume']
                    if curPos.longYd == 0:
                        sell_longToday = expired_pos['volume']
                    else:
                        sell_longYd = curPos.longYd
                        sell_longToday = expired_pos['volume'] - sell_longYd

                if sell_longYd > 0:
                    self.writeCtaLog(u'clear_dispatch_pos发出平昨多仓:{},数量:{}，价格:{}'.format(expired_pos['vtSymbol'], sell_longYd,tick.lowerLimit))
                    order_id = self.sendOrder(expired_pos['vtSymbol'], orderType=CTAORDER_SELL, price=tick.lowerLimit,
                                   volume=sell_longYd, strategy=None, priceType=PRICETYPE_FAK)
                    if order_id:
                        self.dispatch_pos_order_dict[order_id] = {'vtSymbol':expired_pos['vtSymbol'],'orderType':CTAORDER_SELL,
                                                                     'price':tick.lowerLimit,'volume':sell_longYd,'retry':0}

                    else:
                        self.writeCtaCritical(u'clear_dispatch_pos发出平昨多仓异常:{},数量:{}'.format(expired_pos['vtSymbol'], sell_longYd))

                    h = {'strategy_group': self.strategy_group, 'strategy': 'clear_dispatch_pos',
                         'vtSymbol': expired_pos['vtSymbol'], 'direction': expired_pos['direction'],
                         'volume': sell_longYd, 'action': 'clean',
                         'comment': 'sell_longYd',
                         'result': True if order_id else False, 'datetime': datetime.now()}
                    self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)

                if sell_longToday > 0:
                    self.writeCtaLog(u'clear_dispatch_pos发出平今多仓:{},数量:{}'.format(expired_pos['vtSymbol'], sell_longToday))
                    order_id = self.sendOrder(vtSymbol=expired_pos['vtSymbol'], orderType=CTAORDER_SELL, price=tick.lowerLimit,
                                   volume=sell_longToday, strategy=None)
                    if order_id:
                        self.dispatch_pos_order_dict[order_id] = {'vtSymbol':expired_pos['vtSymbol'],'orderType':CTAORDER_SELL,
                                                                     'price':tick.lowerLimit,'volume':sell_longYd,'retry':0}
                    else:
                        self.writeCtaCritical(u'clear_dispatch_pos发出平昨多仓异常:{},数量:{}'.format(expired_pos['vtSymbol'], sell_longToday))

                    h = {'strategy_group': self.strategy_group, 'strategy': 'clear_dispatch_pos',
                         'vtSymbol': expired_pos['vtSymbol'], 'direction': expired_pos['direction'],
                         'volume': sell_longToday, 'action': 'clean',
                         'comment': 'sell_longToday',
                         'result': True if order_id else False, 'datetime': datetime.now()}
                    self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)

                self.writeCtaLog(u'清除当前持仓{}'.format(expired_pos))
                flt = {'_id': expired_pos['_id']}
                self.mainEngine.dbDelete(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, flt)

            if expired_pos['direction'] == 'short':
                curPos = self.posBufferDict.get(expired_pos['vtSymbol'], None)
                if curPos is None:
                    self.writeCtaCritical(u'{} ctaEngine.clear_dispatch_pos,{}没有在持仓中'.format(datetime.now(), expired_pos['vtSymbol']))
                    h = {'strategy_group': self.strategy_group, 'strategy': 'clear_dispatch_pos',
                         'vtSymbol': expired_pos['vtSymbol'], 'direction': expired_pos['direction'],
                         'volume': expired_pos['volume'], 'action': 'clean',
                         'comment': 'no_positions_info,retry:{}'.format(expired_pos['retry']),
                         'result': False, 'datetime': datetime.now()}
                    self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)

                    # 没有持仓，可能是onPosition还没到。 retry低于三次，延长更新时间
                    if expired_pos['retry'] <= 3:
                        expired_pos['retry'] += 1
                        expired_pos['datetime'] = datetime.now() + timedelta(minutes=2)
                        flt = {'_id': expired_pos['_id']}
                        self.mainEngine.dbUpdate(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, expired_pos, flt)
                        self.writeCtaLog(u'更新下次检查的时间:{}'.format(expired_pos))
                    else:
                        self.writeCtaCritical(u'clear_dispatch_pos,持仓信息 为空，尝试超过三次：{},删除'.format(expired_pos))
                        flt = {'_id': expired_pos['_id']}
                        self.mainEngine.dbDelete(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, flt)

                    continue

                cover_shortYd ,cover_shortToday = 0, 0
                self.writeCtaLog(u'{}持仓昨{}/今{},'.format( expired_pos['volume'], curPos.shortYd, curPos.shortToday))

                if curPos.shortYd + curPos.shortToday < expired_pos['volume']:
                    self.writeCtaCritical(u'{} ctaEngineclear_dispatch_pos, 持仓昨{}/今{},不满足平仓数量{}'.format(datetime.now(), curPos.shortYd,curPos.shortToday,expired_pos['volume']))
                    cover_shortYd, cover_shortToday = curPos.shortYd, curPos.shortToday
                    h = {'strategy_group': self.strategy_group, 'strategy': 'clear_dispatch_pos',
                         'vtSymbol': expired_pos['vtSymbol'], 'direction': expired_pos['direction'],
                         'volume': curPos.shortYd + curPos.shortToday, 'action': 'clean',
                         'comment': 'part satisfied,require:{}'.format(expired_pos['volume']),
                         'result': True, 'datetime': datetime.now()}
                    self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)

                else:
                    if curPos.shortYd >= expired_pos['volume']:
                        cover_shortYd = expired_pos['volume']
                    elif curPos.shortYd == 0:
                        cover_shortToday = expired_pos['volume']
                    else:
                        cover_shortYd = curPos.shortYd
                        cover_shortToday = expired_pos['volume'] - cover_shortYd

                if cover_shortYd > 0:
                    self.writeCtaLog(u'clear_dispatch_pos发出平昨空仓:{},数量:{}'.format(expired_pos['volume'], cover_shortYd))
                    order_id = self.sendOrder(vtSymbol=expired_pos['vtSymbol'], orderType=CTAORDER_COVER, price=tick.upperLimit,
                               volume=cover_shortYd, strategy=None, priceType=PRICETYPE_FAK)

                    if order_id:
                        self.dispatch_pos_order_dict[order_id] = {'vtSymbol':expired_pos['vtSymbol'], 'orderType':CTAORDER_COVER,
                                                                     'price':tick.upperLimit, 'volume':cover_shortYd, 'retry':0}

                    else:
                        self.writeCtaCritical(u'clear_dispatch_pos发出平昨多仓异常:{},数量:{}'.format(expired_pos['vtSymbol'], cover_shortYd))

                    h = {'strategy_group': self.strategy_group, 'strategy': 'clear_dispatch_pos',
                         'vtSymbol': expired_pos['vtSymbol'], 'direction': expired_pos['direction'],
                         'volume': cover_shortYd, 'action': 'clean',
                         'comment': 'sell_longYd',
                         'result': True if order_id else False, 'datetime': datetime.now()}
                    self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)

                if cover_shortToday > 0:
                    self.writeCtaLog(u'clear_dispatch_pos发出平今空仓:{},数量:{}'.format(expired_pos['volume'], cover_shortToday))
                    order_id = self.sendOrder(vtSymbol=expired_pos['vtSymbol'], orderType=CTAORDER_COVER, price=tick.upperLimit,
                                   volume=cover_shortToday, strategy=None, priceType=PRICETYPE_FAK)

                    if order_id:
                        self.dispatch_pos_order_dict[order_id] = {'vtSymbol': expired_pos['vtSymbol'],
                                                                     'orderType': CTAORDER_COVER,
                                                                     'price': tick.upperLimit, 'volume': cover_shortToday,
                                                                     'retry': 0}
                    else:
                        self.writeCtaCritical(
                            u'clear_dispatch_pos发出平昨多仓异常:{},数量:{}'.format(expired_pos['vtSymbol'], cover_shortToday))

                    h = {'strategy_group': self.strategy_group, 'strategy': 'clear_dispatch_pos',
                         'vtSymbol': expired_pos['vtSymbol'], 'direction': expired_pos['direction'],
                         'volume': cover_shortToday, 'action': 'clean',
                         'comment': 'sell_longToday',
                         'result': True if order_id else False, 'datetime': datetime.now()}
                    self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)

                self.writeCtaLog(u'清除当前持仓{}'.format(expired_pos))
                flt = {'_id': expired_pos['_id']}
                self.mainEngine.dbDelete(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, flt)

    def onOrder_dispatch_close_pos(self, order):
        """
        调度仓位池，发出的委托平仓清单，onOrder事件
        :param order:
        :return:
        """
        if order.vtOrderID not in self.dispatch_pos_order_dict:
            #self.writeCtaError(u'Order不在调度字典中:{}'.format(order.vtOrderID))
            return

        if order.offset == OFFSET_OPEN:
            self.writeCtaError(u'开仓Order不应该在调度字典中:{}'.format(order.vtOrderID))
            del self.dispatch_pos_order_dict[order.vtOrderID]
            return

        self.writeCtaLog(
            u'onOrder_dispatch_close_pos()报单更新，orderID:{0},{1},totalVol:{2},tradedVol:{3},offset:{4},price:{5},direction:{6},status:{7}'
            .format(order.orderID, order.vtSymbol, order.totalVolume, order.tradedVolume,
                    order.offset, order.price, order.direction, order.status))

        # 如果order执行完毕，移除登记
        if order.totalVolume == order.tradedVolume:
            self.writeCtaLog(u'平仓订单执行完毕')
            del self.dispatch_pos_order_dict[order.vtOrderID]
            return

        # 如果order执行失败，重新提交订单，提高retry次数
        if order.status in [STATUS_CANCELLED, STATUS_REJECTED]:
            if order.tradedVolume > 0:
                new_order_volume = order.totalVolume - order.tradedVolume
            else:
                new_order_volume = order.totalVolume

            old_order = self.dispatch_pos_order_dict[order.vtOrderID]

            # 如果order执行失败，retry次数超过限制，取消order，重新加入调度库，并发出critial邮件.
            if old_order['retry'] > 20:
                self.writeCtaCritical(u'onOrder_dispatch_close_pos order retry次数超过20次.{}'.format(old_order))
                del self.dispatch_pos_order_dict[order.vtOrderID]

                h = {'strategy_group': self.strategy_group, 'strategy': 'clear_dispatch_pos',
                     'vtSymbol': old_order['vtSymbol'], 'direction': 'short' if old_order['orderType'] == CTAORDER_COVER else 'long',
                     'volume': old_order['volume'], 'action': 'clean',
                     'comment': 'FAK retry:{}'.format(old_order['retry']),
                     'result': False, 'datetime': datetime.now()}
                self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)

                d = {
                    'strategy_group': self.strategy_group,
                    'strategy': 'onOrder_dispatch_close_pos',
                    'vtSymbol': old_order['vtSymbol'],
                    'direction': 'short' if old_order['orderType'] == CTAORDER_COVER else 'long',
                    'volume': old_order['volume'],
                    'expire_datetime': datetime.now() + timedelta(minutes=2),
                    'retry': 0
                }
                self.writeCtaLog(u'重新插入持仓信息到数据库:{}'.format(d))
                self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, d)

                return

            new_order_id = self.sendOrder(vtSymbol=old_order['vtSymbol'], orderType=old_order['orderType'], price=old_order['price'],
                                          volume= new_order_volume, strategy=None, priceType=PRICETYPE_FAK)

            if new_order_id:
                self.dispatch_pos_order_dict[new_order_id] = {'vtSymbol': old_order['vtSymbol'],
                                                                     'orderType': old_order['orderType'],
                                                                     'price': old_order['price'], 'volume': new_order_volume,
                                                                     'retry': old_order['retry']+1}

            else:
                d = {
                    'strategy_group': self.strategy_group,
                    'strategy': 'onOrder_dispatch_close_pos',
                    'vtSymbol': old_order['vtSymbol'],
                    'direction': 'short' if old_order['orderType'] == CTAORDER_COVER else 'long',
                    'volume': old_order['volume'],
                    'expire_datetime': datetime.now() + timedelta(minutes=10),
                    'retry': 0
                }
                self.writeCtaLog(u'提交订单失败，重新插入持仓信息到数据库:{}'.format(d))
                self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, d)

            del self.dispatch_pos_order_dict[order.vtOrderID]
        else:
            self.writeCtaError(u'订单返回状态{}，不属于reject/cancel.'.format(order.status))

    def get_dispatch_avaliable_pos(self, vtSymbol, direction):
        """
        获取可以使用的空余仓位
        :param vtSymbol:
        :param direction: long/short
        :return: []
        """
        flt = {
            'strategy_group': self.strategy_group,
            'vtSymbol':vtSymbol,
            'direction':direction
        }
        try:
            rt = self.mainEngine.dbQuery(MATRIX_DB_NAME,POSITION_DISPATCH_COLL_NAME,d=flt)
            return rt
        except Exception as ex:
            self.writeCtaLog(u'get_dispatch_avaliable_pos exception:{},{}'.format(str(ex),traceback.format_exc()))
            return []

    def apply_dispatch_pos(self, strategy_name, vtSymbol, direction, volume):
        """
        申请使用调度转移的仓位
        :param strategy_name: 策略名称
        :param vtSymbol: 品种合约
        :param direction: 方向, DIRECTION_LONG/DIRECTION_SHORT
        :param volume: 数量
        :return: 0，没有仓位/不允许。 其他，可使用的数量
        """
        self.writeCtaLog(u'apply_dispatch_pos:{},{},{},v:{}'.format(strategy_name, vtSymbol, direction, volume))

        if direction == DIRECTION_LONG:
            direction = 'long'
        elif direction == DIRECTION_SHORT:
            direction = 'short'

        if self.mainEngine.dbClient is None:
            self.writeCtaCritical(u'apply_dispatch_pos：数据库连接失败,无法获取调度转移的仓位。strategy_group:{},gateway:{}'.format(self.strategy_group,self.mainEngine.connected_gw_names))
            return 0

        # 检查参数
        if volume < 1 :
            h = {'strategy_group':self.strategy_group,
                 'strategy': strategy_name, 'vtSymbol': vtSymbol, 'direction': direction,
                 'volume': volume, 'action': 'apply', 'comment': 'volume_is_zero', 'result': False,'datetime':datetime.now()}
            self.mainEngine.dbInsert(MATRIX_DB_NAME,POSITION_DISPATCH_HISTORY_COLL_NAME,h)
            return 0

        # 查询是否有空余的持仓
        dispatch_pos_list = self.get_dispatch_avaliable_pos(vtSymbol,direction)

        # 查询结果为空白
        if len(dispatch_pos_list) == 0:
            self.writeCtaLog(u'apply_dispatch_pos:没有适合的仓位')
            h = {'strategy_group': self.strategy_group,
                 'strategy': strategy_name, 'vtSymbol': vtSymbol, 'direction': direction,
                 'volume': volume, 'action': 'apply', 'comment': 'symbol_not_in_list', 'result': False,
                 'datetime': datetime.now()}
            self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)
            return 0

        self.writeCtaLog(u'avaliable_pos:{}'.format(dispatch_pos_list))

        satisfy_volume = 0

        for dispatch_pos in dispatch_pos_list:
            # 满足需求
            if dispatch_pos['volume'] > volume:
                self.writeCtaLog(u'{}调度仓位：id={}，volume={},满足需求仓位：{}'.format(vtSymbol,dispatch_pos['_id'],dispatch_pos['volume'] , volume))
                satisfy_volume += volume
                # 更新仓位池记录
                dispatch_pos['volume'] -= volume
                flt = {'_id': dispatch_pos['_id']}

                self.writeCtaLog(u'更新调度仓位记录:{}'.format(dispatch_pos))
                self.mainEngine.dbUpdate(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, d=dispatch_pos, flt=flt)

                # 写入历史记录
                h = {'strategy_group': self.strategy_group,'strategy': strategy_name, 'vtSymbol': vtSymbol, 'direction': direction,
                 'volume': volume, 'action': 'apply', 'comment': 'volume_satisfied', 'result': True,
                 'datetime': datetime.now()}
                self.mainEngine.dbInsert(MATRIX_DB_NAME,POSITION_DISPATCH_HISTORY_COLL_NAME,h)
                return satisfy_volume

            # 部分或刚好满足
            satisfy_volume += dispatch_pos['volume']
            self.writeCtaLog(u'{} 调度仓位：id={},volume={}，部分/刚好满足需求仓位：{}，'.format(vtSymbol,dispatch_pos['_id'], dispatch_pos['volume'], volume))
            volume -= dispatch_pos['volume']

            # 删除仓位池记录
            flt = {'_id': dispatch_pos['_id']}
            self.writeCtaLog(u'删除数据库调度仓位记录:{}'.format(dispatch_pos))
            self.mainEngine.dbDelete(MATRIX_DB_NAME, POSITION_DISPATCH_COLL_NAME, flt)

            # 写入历史记录
            h = {'strategy_group': self.strategy_group, 'strategy': strategy_name, 'vtSymbol': vtSymbol,
                 'direction': direction,
                 'volume': dispatch_pos['volume'], 'action': 'apply', 'comment': 'volume_satisfied', 'result': True,
                 'datetime': datetime.now()}
            self.mainEngine.dbInsert(MATRIX_DB_NAME, POSITION_DISPATCH_HISTORY_COLL_NAME, h)

            # 当剩余需求volume为0时，跳出循环
            if volume == 0:
                break
        self.writeCtaLog(u'总满足{}仓位：{}'.format(vtSymbol,satisfy_volume))
        return satisfy_volume


    # ----------------------------------------------------------------------
    # 策略配置相关
    def saveSetting(self):
        """保存策略配置"""
        try:
            with open(self.settingfilePath, 'w') as f:
                l = list(self.settingDict.values())
                jsonL = json.dumps(l, indent=4)
                f.write(jsonL)
        except Exception as ex:
            self.writeCtaCritical(u'保存策略配置异常:{},{}'.format(str(ex),traceback.format_exc()))

    def loadSetting(self):
        """
        读取策略配置文件，CTA_setting.json
        逐一运行
        :return: 
        """
        try:
            with open(self.settingfilePath,'r',encoding='UTF-8') as f:
                l = json.load(f)
                for setting in l:
                    try:
                        self.loadStrategy(setting)
                    except Exception as ex:
                        self.writeCtaCritical(u'加载策略配置{}:异常{}，{}'.format(setting, str(ex), traceback.format_exc()))
                        traceback.print_exc()
            self.loadPosition()
        except Exception as ex:
            self.writeCtaCritical(u'加载策略配置异常:{},{}'.format(str(ex),traceback.format_exc()))


    # ----------------------------------------------------------------------
    # 策略运行监控相关
    def getStrategyVar(self, name):
        """获取策略当前的变量字典"""
        if name in self.strategyDict:
            # 获取策略实例
            strategy = self.strategyDict[name]
            varDict = OrderedDict()
            
            for key in strategy.varList:
                if hasattr(strategy,key):
                    varDict[key] = strategy.__getattribute__(key)
            
            return varDict
        else:
            self.writeCtaLog(u'策略实例不存在：' + name)    
            return None

    def getStrategyParam(self, name):
        """获取策略的参数字典"""
        if name in self.strategyDict:
            # 获取策略实例
            strategy = self.strategyDict[name]
            paramDict = OrderedDict()
            
            for key in strategy.paramList:
                if hasattr(strategy, key):
                    paramDict[key] = strategy.__getattribute__(key)
            
            return paramDict
        else:
            self.writeCtaLog(u'策略实例不存在：' + name)    
            return None

    def getStategyPos(self, name):
        """
        获取策略的持仓字典
        :param name:策略名
        :return:
        """
        if name in self.strategyDict:
            # 获取策略实例
            strategy = self.strategyDict[name]
            pos_list = []

            if strategy.inited:
                # 有 ctaPosition属性
                if hasattr(strategy, 'position'):
                    # 多仓
                    long_pos = {}
                    long_pos['symbol'] = strategy.vtSymbol
                    long_pos['direction'] = 'long'
                    long_pos['volume'] = strategy.position.longPos
                    if long_pos['volume'] > 0:
                        pos_list.append(long_pos)

                    # 空仓
                    short_pos = {}
                    short_pos['symbol'] = strategy.vtSymbol
                    short_pos['direction'] = 'short'
                    short_pos['volume'] = abs(strategy.position.shortPos)
                    if short_pos['volume'] > 0:
                        pos_list.append(short_pos)

                # 模板缺省pos属性
                elif hasattr(strategy, 'pos'):
                    if strategy.pos > 0:
                        long_pos = {}
                        long_pos['symbol'] = strategy.vtSymbol
                        long_pos['direction'] = 'long'
                        long_pos['volume'] = strategy.pos
                        #long_pos['datetime'] = datetime.now()
                        if long_pos['volume'] > 0:
                            pos_list.append(long_pos)
                    elif strategy.pos < 0:
                        short_pos = {}
                        short_pos['symbol'] = strategy.vtSymbol
                        short_pos['direction'] = 'short'
                        short_pos['volume'] = abs(strategy.pos)
                        #short_pos['datetime'] = datetime.now()
                        if short_pos['volume'] > 0:
                            pos_list.append(short_pos)

            return pos_list
        else:
            self.writeCtaLog(u'getStategyPos 策略实例不存在：' + name)
            return []

    def updateStrategySetting(self,strategy_name,setting_key,setting_value):
        """
        更新策略的某项设置
        :param strategy_name: 
        :param setting_key: 
        :param setting_value: 
        :return: 
        """
        setting_dict = None
        strategy = None
        if strategy_name in self.settingDict:
            setting_dict = self.settingDict[strategy_name]

        if strategy_name in self.strategyDict:
            # 获取策略实例
            strategy = self.strategyDict[strategy_name]

        assert setting_dict is not None and strategy is not None

        # 更新策略配置
        self.writeCtaLog(u'更新cta_setting中{}的配置{}:{}=>{} '.format(strategy_name,setting_key,setting_dict[setting_key],setting_value))
        setting_dict[setting_key] = setting_value

        # 更新运行策略的设置
        d = strategy.__dict__
        if setting_key in d:
            self.writeCtaLog(u'更新运行中{}策略{}变量:{}=>{}'.format(strategy_name, setting_key, d[setting_key], setting_value))
            d[setting_key] = setting_value

    def getStrategySetting(self, name):
        """
        获取策略的配置参数
        :param name: 策略实例名称
        :return: 
        """

        if name in self.settingDict:
            return self.settingDict[name]

        else:
            return None
    # ----------------------------------------------------------------------
    def putStrategyEvent(self, name):
        """触发策略状态变化事件（通常用于通知GUI更新）"""
        event = Event(EVENT_CTA_STRATEGY+name)
        d = 'putevent'
        event.dict_['data'] = d
        self.eventEngine.put(event)

        # 触发系统状态更新事件
        self.mainEngine.qryStatus()

    # ----------------------------------------------------------------------
    def callStrategyFunc(self, strategy, func, params=None):
        """调用策略的函数，若触发异常则捕捉"""
        try:
            if params:
                func(params)
            else:
                func()
        except Exception:
            # 停止策略，修改状态为未初始化
            strategy.trading = False
            strategy.inited = False

            # 发出日志
            content =u'策略{}触发异常已停止.{}'.format(strategy.name,traceback.format_exc())
            self.writeCtaError(content)
            self.mainEngine.writeCritical(content)

            if hasattr(strategy,'backtesting') and hasattr(strategy,'wechat_source'):
                if not strategy.backtesting and len(strategy.wechat_source)>0:
                    self.sendAlertToWechat(content=content,target=strategy.wechat_source)

    # ----------------------------------------------------------------------
    # 仓位持久化相关
    def savePosition(self):
        """保存所有策略的持仓情况到数据库"""
        for strategy in list(self.strategyDict.values()):
            flt = {'name': strategy.name,
                   'vtSymbol': strategy.vtSymbol}

            d = {'name': strategy.name,
                 'vtSymbol': strategy.vtSymbol,
                 'pos': strategy.pos}

            self.mainEngine.dbUpdate(POSITION_DB_NAME, strategy.className,
                                     d, flt, True)

            content = '策略%s持仓保存成功' % strategy.name
            self.writeCtaLog(content)

    def loadPosition(self):
        """从数据库载入策略的持仓情况"""
        try:
            for strategy in (self.strategyDict.values()):
                flt = {'name': strategy.name,
                       'vtSymbol': strategy.vtSymbol}
                posData = self.mainEngine.dbQuery(POSITION_DB_NAME, strategy.className, flt)

                for d in posData:
                    strategy.pos = d['pos']
        except:
            self.writeCtaLog(u'loadPosition Exception from Mongodb')

    # ----------------------------------------------------------------------
    # 公共方法相关
    def roundToPriceTick(self, priceTick, price):
        """取整价格到合约最小价格变动"""
        if not priceTick:
            return price

        newPrice = round(price / priceTick, 0) * priceTick

        if isinstance(priceTick,float):
            price_exponent = decimal.Decimal(str(newPrice))
            tick_exponent = decimal.Decimal(str(priceTick))
            if abs(price_exponent.as_tuple().exponent) > abs(tick_exponent.as_tuple().exponent):
                newPrice = round(newPrice, ndigits=abs(tick_exponent.as_tuple().exponent))
                newPrice = float(str(newPrice))
        return newPrice

    def roundToVolumeTick(self,volumeTick,volume):
        if volumeTick == 0:
            return volume
        newVolume = round(volume / volumeTick, 0) * volumeTick
        if isinstance(volumeTick,float):
            v_exponent = decimal.Decimal(str(newVolume))
            vt_exponent = decimal.Decimal(str(volumeTick))
            if abs(v_exponent.as_tuple().exponent) > abs(vt_exponent.as_tuple().exponent):
                newVolume = round(newVolume, ndigits=abs(vt_exponent.as_tuple().exponent))
                newVolume = float(str(newVolume))

        return newVolume

    def getShortSymbol(self, symbol):
        """取得合约的短号"""
        # 套利合约
        if symbol.find(' ') != -1:
            # 排除SP SPC SPD
            s = symbol.split(' ')
            if len(s) < 2:
                return symbol
            symbol = s[1]

            # 只提取leg1合约
            if symbol.find('&') != -1:
                s = symbol.split('&')
                if len(s) < 2:
                    return symbol
                symbol = s[0]

        p = re.compile(r"([A-Z]+)[0-9]+", re.I)
        shortSymbol = p.match(symbol)

        if shortSymbol is None:
            self.writeCtaLog(u'{0}不能正则分解'.format(symbol))
            return symbol

        return shortSymbol.group(1)

    # ----------------------------------------------------------------------
    def getAccountInfo(self):
        """获取账号的实时权益、可用资金、仓位比例
        Added by Incenselee
        暂不支持多接口同时运行哦
        """
        return self.mainEngine.getAccountInfo()

    # ---------------------------------------------------------------------
    def saveStrategyData(self):
        """保存策略的数据"""

        # 1.判断策略名称是否存在字典中
        for key in self.strategyDict.keys():

            # 2.提取策略
            strategy = self.strategyDict[key]

            if strategy is None:
                continue

            # 3.判断策略是否运行
            if strategy.inited and strategy.trading:

                try:
                    # 5.保存策略数据
                    strategy.saveData()
                except:
                    traceback.print_exc()

    def clearData(self):
        """清空运行数据"""
        self.writeCtaLog(u'ctaEngine.clearData()清空运行数据')
        self.tickDict = {}
        self.orderStrategyDict = {}
        self.workingStopOrderDict = {}
        self.posBufferDict = {}
        self.stopOrderDict = {}

    def qryStatus(self):
        """查询cta Engined的运行状态"""

        # 查询最新tick和更新时间
        tick_status_dict = OrderedDict()
        for k,v in self.tickDict.items():
            tick_status_dict[k] = str(v.date + ' ' + v.time)

        # 查询策略运行状态
        strategy_status_dict = OrderedDict()
        for strategy_name in self.strategyDict.keys():
            varList = self.getStrategyVar(strategy_name)
            strategy_status_dict[strategy_name] = varList

        return tick_status_dict, strategy_status_dict

    def qrySize(self,vtSymbol):
        """
        查询合约的大小
        :param vtSymbol: 
        :return: 
        """
        c = self.mainEngine.getContract(vtSymbol)
        if c is None:
            self.writeCtaError(u'qrySize:查询不到{}合约信息'.format(vtSymbol))
            return 10
        else:
           return c.size

    def qryMarginRate(self,vtSymbol):
        """
        提供给策略查询品种的保证金比率
        :param vtSymbol: 
        :return: 
        """
        c = self.mainEngine.getContract(vtSymbol)
        if c is None:
            self.writeCtaError(u'qryMarginRate:查询不到{}合约信息'.format(vtSymbol))
            return 0.1
        else:
            # 返回空头/多头保证金费率的最大值
            if c.longMarginRatio > EMPTY_FLOAT and c.shortMarginRatio > EMPTY_FLOAT:
                return max(c.longMarginRatio, c.shortMarginRatio)
            else:
                self.writeCtaError(u'合约{}的多头保证金率:{},空头保证金率:{}'.format(vtSymbol,c.longMarginRatio,c.shortMarginRatio))
                return 0.1

    def is_trade_off(self):
        """
        检查现在是否为非交易时间
        针对国内商品期货，先排除大部分，其余通过is_trade_windows(short_symbol)来判断
        :return:
        """
        now = datetime.now()
        midnight_end = datetime.now().replace(hour=2, minute=29, second=0, microsecond=0)
        morning_begin = datetime.now().replace(hour=9, minute=00, second=0, microsecond=0)
        afternoon_close = datetime.now().replace(hour=15, minute=00, second=0, microsecond=0)
        midnight_begin = datetime.now().replace(hour=21, minute=00, second=0, microsecond=0)
        weekend = (now.isoweekday() == 6 and now >= midnight_end) or (now.isoweekday() == 7)  or (now.isoweekday() == 1 and now <= midnight_end)
        off = (midnight_end <= now <= morning_begin) or (afternoon_close <= now <= midnight_begin) or weekend
        return off

    # ----------------------------------------------------------------------
    def is_trade_window(self, short_symbol):
        """交易与平仓窗口"""
        # 交易窗口 避开早盘和夜盘的前5分钟，防止隔夜跳空。

        if len(short_symbol) == 0:
            return False
        short_symbol = short_symbol.upper()

        dt = datetime.now()

        midnight_end = dt.replace(hour=2, minute=30, second=0, microsecond=0)
        sq2_midnight_end = dt.replace(hour=1, minute=00, second=0, microsecond=0)
        sq3_midnight_end = dt.replace(hour=23, minute=00, second=0, microsecond=0)
        zzdl_midnight_end = dt.replace(hour=23, minute=30, second=0, microsecond=0)
        morning_begin = dt.replace(hour=9, minute=00, second=0, microsecond=0)
        zj_morning_begin = dt.replace(hour=9, minute=30, second=0, microsecond=0)
        morning_break = dt.replace(hour=10, minute=15, second=0, microsecond=0)
        morning_restart = dt.replace(hour=10, minute=30, second=0, microsecond=0)
        morning_close = dt.replace(hour=11, minute=30, second=0, microsecond=0)
        afternoon_begin = dt.replace(hour=13, minute=30, second=0, microsecond=0)
        afternoon_close = dt.replace(hour=15, minute=00, second=0, microsecond=0)
        zj_afternoon_begin = dt.replace(hour=13, minute=00, second=0, microsecond=0)
        zj_afternoon_close = dt.replace(hour=15, minute=15, second=0, microsecond=0)
        night_begin = dt.replace(hour=21, minute=00, second=0, microsecond=0)

        # 股指期货，国债早上9：30前、午休盘11:30~13:00,收盘15:15
        if short_symbol in MARKET_ZJ:
            if zj_morning_begin <= dt <= morning_close or zj_afternoon_begin <= dt <= zj_afternoon_close:
                return True
            else:
                return False

        # 上期，AU,AG ：日盘，夜盘（21：00~2：30）
        if short_symbol in NIGHT_MARKET_SQ1:
            if morning_begin <= dt <= morning_break or \
                    morning_restart <= dt <= morning_close or \
                    afternoon_begin <= dt <= afternoon_close or \
                    night_begin <= dt or dt <= midnight_end:
                return True
            else:
                return False

        # 上期，CU等有色金属\沥青：日盘，夜盘(21:00~1:00)
        if short_symbol in NIGHT_MARKET_SQ2:
            if morning_begin <= dt <= morning_break or \
                    morning_restart <= dt <= morning_close or \
                    afternoon_begin <= dt <= afternoon_close or \
                    night_begin <= dt or dt <= sq2_midnight_end:
                return True
            else:
                return False

        # 上期，RB/HC/RU ：日盘，夜盘（21：00~23：00）
        if short_symbol in NIGHT_MARKET_SQ3:
            if morning_begin <= dt <= morning_break or \
                    morning_restart <= dt <= morning_close or \
                    afternoon_begin <= dt <= afternoon_close or \
                    night_begin <= dt <= sq3_midnight_end:
                return True
            else:
                return False

        # 郑商、大连 21:00 ~ 23:30
        if short_symbol in NIGHT_MARKET_ZZ or short_symbol in NIGHT_MARKET_DL:
            if morning_begin <= dt <= morning_break or \
                    morning_restart <= dt <= morning_close or \
                    afternoon_begin <= dt <= afternoon_close or \
                    night_begin <= dt <= zzdl_midnight_end:
                return True
            else:
                return False

        return True

########################################################################
class PositionBuffer(object):
    """持仓缓存信息（本地维护的持仓数据）"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.vtSymbol = EMPTY_STRING
        
        # 多头
        self.longPosition = EMPTY_INT
        self.longToday = EMPTY_INT
        self.longYd = EMPTY_INT

        # 空头
        self.shortPosition = EMPTY_INT
        self.shortToday = EMPTY_INT
        self.shortYd = EMPTY_INT

        self.frozen = EMPTY_FLOAT

    # ----------------------------------------------------------------------
    def toStr(self):
        """更新显示信息"""
        str = u'long:{},yd:{},td:{}, short:{},yd:{},td:{}, fz:{};' \
            .format(self.longPosition, self.longYd, self.longToday,
                    self.shortPosition, self.shortYd, self.shortToday,self.frozen)
        return str
    #----------------------------------------------------------------------
    def updatePositionData(self, pos):
        """更新持仓数据"""
        if pos.direction == DIRECTION_SHORT:
            self.shortPosition = pos.position  # >=0
            self.shortYd = pos.ydPosition  # >=0
            self.shortToday = self.shortPosition - self.shortYd  # >=0
            self.frozen = pos.frozen
        else:
            self.longPosition = pos.position  # >=0
            self.longYd = pos.ydPosition  # >=0
            self.longToday = self.longPosition - self.longYd  # >=0
            self.frozen = pos.frozen

    #----------------------------------------------------------------------
    def updateTradeData(self, trade):
        """更新成交数据"""

        if trade.direction == DIRECTION_SHORT:
            # 空头和多头相同
            if trade.offset == OFFSET_OPEN:
                self.shortPosition += trade.volume
                self.shortToday += trade.volume
            elif trade.offset == OFFSET_CLOSETODAY:
                self.longPosition -= trade.volume
                self.longToday -= trade.volume
            else:
                self.longPosition -= trade.volume
                self.longYd -= trade.volume

            if self.longPosition <= 0:
                self.longPosition = 0
            if self.longToday <= 0:
                self.longToday = 0
            if self.longYd <= 0:
                self.longYd = 0
        else:
            # 多方开仓，则对应多头的持仓和今仓增加
            if trade.offset == OFFSET_OPEN:
                self.longPosition += trade.volume
                self.longToday += trade.volume
            # 多方平今，对应空头的持仓和今仓减少
            elif trade.offset == OFFSET_CLOSETODAY:
                self.shortPosition -= trade.volume
                self.shortToday -= trade.volume
            else:
                self.shortPosition -= trade.volume
                self.shortYd -= trade.volume

            if self.shortPosition <= 0:
                self.shortPosition = 0
            if self.shortToday <= 0:
                self.shortToday = 0
            if self.shortYd <= 0:
                self.shortYd = 0
            # 多方平昨，对应空头的持仓和昨仓减少