# encoding: UTF-8

from __future__ import division
from collections import OrderedDict

import os
import traceback
import copy
from datetime import datetime
import decimal

from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT,
                                    OFFSET_OPEN, OFFSET_CLOSE,
                                    STATUS_ALLTRADED, STATUS_CANCELLED,
                                    STATUS_REJECTED, EMPTY_STRING, EMPTY_FLOAT, EMPTY_INT)

from vnpy.trader.uiQt import QtGui

from vnpy.trader.app.algoTrading.algoTemplate import AlgoTemplate
from vnpy.trader.app.algoTrading.uiAlgoWidget import AlgoWidget, QtWidgets
from vnpy.trader.vtObject import VtTickData,VtOrderData
from vnpy.trader.vtEvent import *
from vnpy.trader.vtFunction import roundToPriceTick,get_data_path,getShortSymbol


STATUS_FINISHED = set([STATUS_ALLTRADED, STATUS_CANCELLED, STATUS_REJECTED])


########################################################################
class spreadAlgo(AlgoTemplate):
    """
    价差价比交易算法，用于套利
    # 增加下单前判断是否涨停和跌停。
    """

    templateName = u'SpreadTrading 套利'

    # ----------------------------------------------------------------------
    def __init__(self, engine, setting, algoName):
        """Constructor"""
        super(spreadAlgo, self).__init__(engine, setting, algoName)

        self.writeLog(u'配置参数:\n{}'.format(setting))
        # 配置参数
        self.strategy_name = str(setting['strategy_name'])      # 来自调用的策略实例的名称
        self.order_vtSymbol = str(setting['order_vtSymbol'])    # 价差/价比合约的名称 j1905-1-rb1905-5-BJ.SPD
        self.order_command = str(setting['order_command'])      # 交易命令 buy/sell/short/cover

        self.order_req_price = float(setting['order_price'])    # 委托价差
        self.order_req_volume = float(setting['order_volume'])  # 委托数量
        self.timer_interval = int(setting['timer_interval'])    # 检查成交的时间间隔（秒)

        # 初始化
        self.active_traded_volume = 0      # 主动腿的成交数量
        self.passive_traded_volume = 0     # 被动腿的成交数量
        self.active_traded_avg_price = 0   # 主动腿的成交均价
        self.passive_traded_avg_price = 0  # 被动腿的成交均价
        self.active_orderID = ''           # 主动委托号
        self.passive_orderID = ''          # 被动委托号
        self.active_orderID_history = ''   # 历史主动委托号
        self.passive_orderID_history = ''  # 历史被动委托号
        self.active_order_avg_price = 0       # 主动腿的报单均价
        self.passive_order_avg_price = 0      # 被动腿的报单均价
        self.active_order_volume = 0         # 主动腿的报单数量
        self.passive_order_volume = 0        # 被动腿的报单数量

        self.netPos = 0  # 净持仓
        self.count = 0  # 运行计数
        self.entrust = False  # 是否在正在交易中

        self.last_tick = None          # 最新的价差/价比价格
        self.last_active_tick = None   # 最新的主动腿价格
        self.last_passive_tick = None   # 最新的被动腿价格

        # 检查价差合约的名称
        if not self.order_vtSymbol.endswith('SPD'):
            self.writeLog(u'套利合约代码错误, 参考格式: j1905-1-rb1905-5-BJ.SPD')
            return

        self.active_vtSymbol = setting.get('leg1_symbol')       # 主动腿的真实合约
        self.active_ratio = int(setting.get('leg1_ratio',1))    # 主动腿/leg1的下单比例
        self.passive_vtSymbol = setting.get('leg2_symbol')      # 被动腿真实合约
        self.passive_ratio = int(setting.get('leg2_ratio',1))   # 被动腿/leg2的下单比例
        self.is_spread = setting.get('is_spread', False)         # 价差交易
        self.is_ratio = setting.get('is_ratio', False)           # 价比交易

        if not self.is_spread and not self.is_ratio:
            self.writeLog(u'套利配置中，缺少is_spread 或 is_ratio')
            return

        # 需要交易的数量
        self.active_target_volume = self.order_req_volume * self.active_ratio
        self.passive_target_volume = self.order_req_volume * self.passive_ratio

        # 订阅合约
        self.subscribe(self.active_vtSymbol)
        self.subscribe(self.passive_vtSymbol)
        self.subscribe(self.order_vtSymbol)

        # 获取合约基本信息
        self.active_contract = self.getContract(self.active_vtSymbol)
        self.passive_contract = self.getContract(self.passive_vtSymbol)

        self.paramEvent()
        self.varEvent()
        self.writeLog('{}.__init__()'.format(self.algoName))

        # 委托下单得费用满足
        self.invest_money_enough = False

    # ----------------------------------------------------------------------
    def onTick(self, tick):
        """"""

        if not self.active:
            return

        # 更新三个合约的tick
        if tick.vtSymbol == self.order_vtSymbol:
            self.last_tick = tick
        elif tick.vtSymbol == self.active_vtSymbol:
            self.last_active_tick = tick
        elif tick.vtSymbol == self.passive_vtSymbol:
            self.last_passive_tick = tick

        # Tick 未更新完毕
        if self.last_tick is None or self.last_passive_tick is None or self.last_active_tick is None:
            return

        # 检查资金是否满足开仓
        if not self.invest_money_enough:
            if self.order_command.lower() in ['buy', 'short']:
                if self.check_invest_money():
                    self.invest_money_enough = True
                else:
                    return
            else:
                self.invest_money_enough = True

        # 检查主动腿合约/被动腿合约，是否接近涨停/跌停价
        if self.active_traded_volume==0 and self.passive_traded_volume ==0:
            if self.active_contract is not None and self.passive_contract is not None:
                if 0 < self.last_active_tick.upperLimit < self.last_active_tick.lastPrice + self.active_contract.priceTick * 10:
                    self.writeLog(u'{}合约价格{} 接近涨停价{} 10个跳,不处理'.format(self.active_vtSymbol, self.last_active_tick.lastPrice, self.last_active_tick.upperLimit))
                    self.cancel_algo()
                    self.stop()
                    return

                if 0 < self.last_passive_tick.upperLimit < self.last_passive_tick.lastPrice + self.passive_contract.priceTick * 10:
                    self.writeLog(
                        u'{}合约价格{} 接近涨停价{} 10个跳,不处理'.format(self.passive_vtSymbol, self.last_passive_tick.lastPrice,
                                                            self.last_passive_tick.upperLimit))
                    self.cancel_algo()
                    self.stop()
                    return

                if 0 < self.last_active_tick.lastPrice - self.active_contract.priceTick * 10 < self.last_active_tick.lowerLimit:
                    self.writeLog(u'{}合约价格{} 接近跌停价{} 10个跳,不处理'.format(self.active_vtSymbol, self.last_active_tick.lastPrice, self.last_active_tick.lowerLimit))
                    self.cancel_algo()
                    self.stop()
                    return

                if 0 < self.last_passive_tick.lastPrice + self.passive_contract.priceTick * 10 < self.last_passive_tick.lowerLimit:
                    self.writeLog(
                        u'{}合约价格{} 接近跌停价{} 10个跳,不开仓'.format(self.passive_vtSymbol, self.last_passive_tick.lastPrice,
                                                            self.last_passive_tick.lowerLimit))
                    self.cancel_algo()
                    self.stop()
                    return

        # 如果有交易, 直接返回
        if self.entrust is True:
            return

        try:
            # 如果有净仓位则执行对冲
            if self.netPos:
                self.hedge()
                self.varEvent()
                return

            # 根据价差的bid/ask下单
            #  - 若买入方向限价单价格高于该价格，则会成交
            #  - 若卖出方向限价单价格低于该价格，则会成交

            updateVar = False

            if self.order_command.lower() == 'buy':
                volume = self.active_target_volume - self.active_traded_volume
                self.writeLog('{}.onTick({}), buy:{},askPrice1:{},bidPrice1:{},lastPrice:{},v:{}'
                              .format(self.algoName, self.last_tick.vtSymbol,self.order_req_price,
                              self.last_tick.askPrice1,self.last_tick.bidPrice1,self.last_tick.lastPrice,volume))

                if self.last_tick.askPrice1 <= self.order_req_price and self.last_active_tick.askVolume1 > volume > 0:
                    self.active_orderID = self.buy(self.active_vtSymbol, self.last_active_tick.askPrice1, volume, offset=OFFSET_OPEN)
                    self.active_orderID_history = self.active_orderID_history + self.active_orderID + '@' + str(
                        self.last_active_tick.askPrice1) + ':'
                    updateVar = True
                    self.entrust = True
                    self.count = 0

            elif self.order_command.lower() == 'sell':
                volume = self.active_target_volume - self.active_traded_volume
                self.writeLog('{}.onTick({}), sell:{},askPrice:{},bidPrice1:{},lastPrice:{},v:{}'
                              .format(self.algoName, self.last_tick.vtSymbol,self.order_req_price,
                              self.last_tick.askPrice1,self.last_tick.bidPrice1,self.last_tick.lastPrice,volume))

                if self.last_tick.bidPrice1 >= self.order_req_price and self.last_active_tick.bidVolume1 > volume > 0:
                    self.active_orderID = self.sell(self.active_vtSymbol, self.last_active_tick.bidPrice1, volume, offset=OFFSET_CLOSE)
                    self.active_orderID_history = self.active_orderID_history + self.active_orderID + '@' + str(
                        self.last_active_tick.bidPrice1) + ':'
                    updateVar = True
                    self.entrust = True
                    self.count = 0

            elif self.order_command.lower() == 'short':
                volume = self.active_target_volume - self.active_traded_volume

                self.writeLog('{}.onTick({}), short:{},askPrice:{},bidPrice1:{},lastPrice:{},v:{}'
                              .format(self.algoName,self.last_tick.vtSymbol, self.order_req_price,
                              self.last_tick.askPrice1,
                              self.last_tick.bidPrice1,
                              self.last_tick.lastPrice,volume))

                if self.last_tick.bidPrice1 >= self.order_req_price and self.last_active_tick.bidVolume1 > volume > 0:
                    self.active_orderID = self.sell(self.active_vtSymbol, self.last_active_tick.bidPrice1, volume, offset=OFFSET_OPEN)
                    self.active_orderID_history = self.active_orderID_history + self.active_orderID + '@' + str(
                        self.last_active_tick.bidPrice1) + ':'
                    updateVar = True
                    self.entrust = True
                    self.count = 0

            elif self.order_command.lower() == 'cover':
                volume = self.active_target_volume - self.active_traded_volume
                self.writeLog('{}.onTick({}), cover:{},askPrice:{},bidPrice1:{},lastPrice:{},v:{}'
                              .format(self.algoName, self.last_tick.vtSymbol, self.order_req_price,
                                      self.last_tick.askPrice1,
                                      self.last_tick.bidPrice1,
                                      self.last_tick.lastPrice,volume))

                if self.last_tick.askPrice1 <= self.order_req_price and self.last_active_tick.askVolume1 > volume > 0:
                    self.active_orderID = self.buy(self.active_vtSymbol, self.last_active_tick.askPrice1, volume, offset=OFFSET_CLOSE)
                    self.active_orderID_history = self.active_orderID_history + self.active_orderID + '@' + str(
                        self.last_active_tick.askPrice1) + ':'
                    updateVar = True
                    self.entrust = True
                    self.count = 0

            # 更新界面
            if updateVar is True:
                self.varEvent()
        except Exception as e:
            self.writeError(u'onTick：{},{},{}'.format(self.strategy_name, str(e), traceback.format_exc()))

    def check_invest_money(self):
        """
        检查投资金额是否满足
        :return:
        """
        # 当前净值,可用资金,资金占用比例,资金上限
        balance, avaliable, occupy_percent, percent_limit = self.engine.getAccountInfo()

        if occupy_percent >= percent_limit:
            self.writeLog(u'当前资金占用:{},超过限定:{}'.format(occupy_percent, percent_limit))
            self.cancel_algo()
            self.stop()
            return False

        # 主动腿/被动腿得短合约符号
        activate_short_symbol = getShortSymbol(self.active_vtSymbol)
        passive_short_symbol = getShortSymbol(self.passive_vtSymbol)

        activate_size = self.engine.getSize(self.active_vtSymbol)
        activate_margin_rate = self.engine.getMarginRate(self.active_vtSymbol)

        passive_size = self.engine.getSize(self.passive_vtSymbol)
        passive_margin_rate = self.engine.getMarginRate(self.passive_vtSymbol)

        activate_margin = self.active_target_volume * self.last_active_tick.lastPrice * activate_size * activate_margin_rate
        passive_margin = self.passive_target_volume * self.last_passive_tick.lastPrice * passive_size * passive_margin_rate

        invest_margin = 0
        if activate_short_symbol == passive_short_symbol:
            # 同一品种套利
            invest_margin = max(activate_margin, passive_margin)
        else:
            # 跨品种套利
            invest_margin = activate_margin + passive_margin

        target_margin = balance * (occupy_percent /100) + invest_margin

        if 100 * (target_margin / balance ) > percent_limit:
            self.writeLog(u'委托后,预计当前资金占用:{},超过限定:{}比例,不能开仓'.format(100 * (target_margin / balance), percent_limit))
            self.cancel_algo()
            self.stop()
            return False

        return True

    def cancel_algo(self):
        """
        撤销当前算法实例订单
        :return:
        """
        self.writeLog(u'{}发出算法撤单，合约:{}'.format(self.algoName, self.order_vtSymbol))
        order = VtOrderData()
        order.price = self.order_req_price
        order.symbol = self.order_vtSymbol
        order.vtSymbol = self.order_vtSymbol
        order.totalVolume = self.order_req_volume
        order.tradedVolume = EMPTY_INT
        order.orderID = self.algoName

        if len(self.engine.main_engine.connected_gw_names)>=0:
            order.gatewayName = self.engine.main_engine.connected_gw_names[0]

        order.vtOrderID = order.gatewayName + u'.' + self.algoName
        if self.order_command.lower() == 'buy':
            order.direction = DIRECTION_LONG
            order.offset = OFFSET_OPEN
        elif self.order_command.lower() == 'short':
            order.direction = DIRECTION_SHORT
            order.offset = OFFSET_OPEN
        elif self.order_command.lower() == 'sell':
            order.direction = DIRECTION_SHORT
            order.offset = OFFSET_CLOSE
        elif self.order_command.lower() == 'cover':
            order.direction = DIRECTION_LONG
            order.offset = OFFSET_CLOSE

        order.status = STATUS_CANCELLED

        # 通用事件
        event1 = Event(type_=EVENT_ORDER)
        event1.dict_['data'] = order
        self.engine.event_engine.put(event1)

    def append_trade_record(self, trade):
        """
        添加交易记录到文件
        :param trade:
        :return:
        """
        # 根据策略名称，写入 data\straetgy_name_trade.csv文件
        trade_fields = ['symbol', 'exchange', 'vtSymbol', 'tradeID', 'vtTradeID', 'orderID', 'vtOrderID', 'direction',
                        'offset', 'price', 'volume', 'tradeTime']
        trade_dict = OrderedDict()
        try:
            for k in trade_fields:
                if k == 'tradeTime':
                    trade_dict[k] = datetime.now().strftime('%Y-%m-%d') + ' ' + getattr(trade, k, EMPTY_STRING)
                else:
                    trade_dict[k] = getattr(trade, k, EMPTY_STRING)

            if self.strategy_name is not None:
                trade_file = os.path.abspath(
                    os.path.join(get_data_path(), '{}_trade.csv'.format(self.strategy_name)))
                self.append_data(file_name=trade_file, dict_data=trade_dict)
        except Exception as ex:
            self.writeError(u'写入交易记录csv出错：{},{}'.format(str(ex), traceback.format_exc()))

    # ----------------------------------------------------------------------
    def onTrade(self, trade):
        """处理成交结果"""
        self.writeLog('spreadAlgo.onTrade(), {}'.format(trade.vtSymbol))
        if trade.vtSymbol not in [self.active_vtSymbol, self.passive_vtSymbol]:
            self.writeLog(u'不认识的交易：{},{}'.format(self.strategy_name, trade.vtSymbol))
            return

        # 更新净持仓数量
        if trade.direction == DIRECTION_LONG:
            self.netPos += trade.volume
        else:
            self.netPos -= trade.volume

        # 如果是主动腿成交则需要执行对冲
        if trade.vtSymbol == self.active_vtSymbol:
            self.active_traded_avg_price = trade.price * trade.volume + self.active_traded_avg_price * self.active_traded_volume
            self.active_traded_volume += trade.volume
            self.active_traded_avg_price /= self.active_traded_volume

            # 被动腿的已成交数量，与目标数量不一致
            if self.passive_traded_volume != self.passive_target_volume and not self.entrust:
                self.hedge()

        else:
            self.passive_traded_avg_price = trade.price * trade.volume + self.passive_traded_avg_price * self.passive_traded_volume
            self.passive_traded_volume += trade.volume
            self.passive_traded_avg_price /= self.passive_traded_volume

        self.append_trade_record(trade)

        # 主动腿&被动腿都成交, 合成套利合约的成交更新事件, 并将它推送给EventEngine
        if self.passive_traded_volume == self.passive_target_volume and self.active_traded_volume == self.active_target_volume:
            traded_price = 0
            if self.is_spread:
                traded_price = self.active_traded_avg_price\
                                    - self.passive_traded_avg_price
            elif self.is_ratio:
                traded_price = 100 * self.active_traded_avg_price * self.active_traded_volume \
                                    / (self.passive_traded_avg_price * self.passive_traded_volume)
            self.writeLog(u'所有交易已完成：{},{},ActiveOrderIDs:{},PassiveOrderIDs:{}'.format(self.strategy_name,
                                                                                       traded_price,
                                                                                       self.active_orderID_history,
                                                                                       self.passive_orderID_history))

            """套利合约的成交信息推送"""
            newTrade = copy.copy(trade)
            newTrade.price = traded_price
            newTrade.tradeId = self.algoName
            newTrade.vtTradeID = newTrade.gatewayName + u'.' + self.algoName
            newTrade.symbol = self.order_vtSymbol
            newTrade.vtSymbol = self.order_vtSymbol
            newTrade.totalVolume = self.order_req_volume
            newTrade.tradedVolume = self.order_req_volume
            newTrade.orderID = self.algoName
            newTrade.vtOrderID = newTrade.gatewayName + u'.' + self.algoName
            if self.order_command.lower() == 'buy':
                newTrade.direction = DIRECTION_LONG
                newTrade.offset = OFFSET_OPEN
            elif self.order_command.lower() == 'short':
                newTrade.direction = DIRECTION_SHORT
                newTrade.offset = OFFSET_OPEN
            elif self.order_command.lower() == 'sell':
                newTrade.direction = DIRECTION_SHORT
                newTrade.offset = OFFSET_CLOSE
            elif self.order_command.lower() == 'cover':
                newTrade.direction = DIRECTION_LONG
                newTrade.offset = OFFSET_CLOSE

            # 通用事件
            event1 = Event(type_=EVENT_TRADE)
            event1.dict_['data'] = newTrade
            self.engine.event_engine.put(event1)

            # 特定合约的成交事件
            event2 = Event(type_=EVENT_TRADE + newTrade.vtSymbol)
            event2.dict_['data'] = newTrade
            self.engine.event_engine.put(event2)
            self.stop()

        self.varEvent()

    # ----------------------------------------------------------------------
    def onOrder(self, order):
        """处理报单结果"""
        self.writeLog('{}.onOrder(), {}'.format(self.algoName, order.vtSymbol))
        if order.vtSymbol not in [self.active_vtSymbol, self.passive_vtSymbol]:
            self.writeLog(u'不认识的交易：{},{}'.format(self.strategy_name, order.vtSymbol))
            return

        # TODO: CancelAll之后订单的处理
        if order.vtSymbol == self.active_vtSymbol:
            # 主动腿成交, 更新主动腿的平均成交价格
            if order.status in STATUS_FINISHED:
                self.active_orderID = ''
                self.active_order_avg_price = order.price * order.totalVolume + self.active_order_avg_price * self.active_order_volume
                self.active_order_volume += order.totalVolume
                self.active_order_avg_price /= self.active_order_volume
                self.entrust = False
        elif order.vtSymbol == self.passive_vtSymbol:
            # 被动腿都成交, 更新被动腿的平均成交价格, 合成套利合约的报单更新事件, 并将它推送给EventEngine
            if order.status in STATUS_FINISHED:
                self.passive_orderID = ''
                self.passive_order_avg_price = order.price * order.totalVolume + self.passive_order_avg_price * self.passive_order_volume
                self.passive_order_volume += order.totalVolume
                self.passive_order_avg_price /= self.passive_order_volume
                self.entrust = False

                # 套利合约的订单变化推送
                newOrder = copy.copy(order)
                order_price = 0
                if self.is_spread:
                    order_price = self.active_order_avg_price \
                                       - self.passive_order_avg_price
                elif self.is_ratio:
                    order_price = 100 * self.active_order_avg_price * self.active_order_volume \
                                       / (self.passive_order_avg_price * self.passive_order_volume)

                # 发送套利合约得onOrder事件
                newOrder.price = order_price
                newOrder.symbol = self.order_vtSymbol
                newOrder.vtSymbol = self.order_vtSymbol
                newOrder.totalVolume = self.order_req_volume
                newOrder.tradedVolume = self.order_req_volume
                newOrder.orderID = self.algoName
                newOrder.vtOrderID = newOrder.gatewayName + u'.' + self.algoName
                if self.order_command.lower() == 'buy':
                    newOrder.direction = DIRECTION_LONG
                    newOrder.offset = OFFSET_OPEN
                elif self.order_command.lower() == 'short':
                    newOrder.direction = DIRECTION_SHORT
                    newOrder.offset = OFFSET_OPEN
                elif self.order_command.lower() == 'sell':
                    newOrder.direction = DIRECTION_SHORT
                    newOrder.offset = OFFSET_CLOSE
                elif self.order_command.lower() == 'cover':
                    newOrder.direction = DIRECTION_LONG
                    newOrder.offset = OFFSET_CLOSE

                # 通用事件
                event1 = Event(type_=EVENT_ORDER)
                event1.dict_['data'] = newOrder
                self.engine.event_engine.put(event1)

                # 特定订单编号的事件
                event2 = Event(type_=EVENT_ORDER + newOrder.vtOrderID)
                event2.dict_['data'] = newOrder
                self.engine.event_engine.put(event2)

        self.varEvent()

    # ----------------------------------------------------------------------
    def onTimer(self):
        """定时检查, 未完成开仓，就撤单"""
        self.count += 1
        if self.count < self.timer_interval:
            return

        self.writeLog('spreadAlgo.onTimer()')
        self.count = 0

        # Tick 未更新完毕
        if self.last_tick is None or self.last_passive_tick is None or self.last_active_tick is None:
            return

        try:
            # 撤单(主动腿/被动腿，均未开仓
            if len(self.active_orderID) == 0 and len(self.passive_orderID) == 0:
                self.writeLog(u'{}超时撤单'.format(self.algoName))
                self.cancelAll()
                self.entrust = False
                if len(self.passive_orderID) == 0:
                    self.cancel_algo()
                    self.stop()
                return

            # 更新界面
            self.varEvent()
        except Exception as e:
            self.writeError(u'onTimer exception：{},{},{}'.format(self.strategy_name, str(e), traceback.format_exc()))

    # ----------------------------------------------------------------------
    def onStop(self):
        """"""
        self.writeLog(u'算法停止')

        self.varEvent()

    # ----------------------------------------------------------------------
    def varEvent(self):
        """更新变量"""
        d = OrderedDict()
        d[u'算法状态'] = self.active
        d[u'运行计数'] = self.count
        d[u'净持仓'] = self.netPos
        d[u'主动腿持仓'] = self.active_traded_volume
        d[u'被动腿持仓'] = self.passive_traded_volume
        d[u'主动腿委托历史'] = self.active_orderID_history
        d[u'被动腿委托历史'] = self.passive_orderID_history
        self.putVarEvent(d)

    # ----------------------------------------------------------------------
    def paramEvent(self):
        """更新参数"""
        d = OrderedDict()
        d[u'价差合约'] = self.order_vtSymbol
        d[u'交易命令'] = self.order_command
        d[u'价差'] = self.order_req_price
        d[u'数量'] = self.order_req_volume
        d[u'间隔'] = self.timer_interval
        d[u'策略名称'] = self.strategy_name
        self.putParamEvent(d)

    # ----------------------------------------------------------------------
    def hedge(self):
        """交易被动腿"""
        passiveTick = self.last_passive_tick
        volume = abs(self.netPos)

        if self.entrust:
            self.writeLog(u'正在委托中，不能实施对冲交易')
            return

        min_diff = passiveTick.askPrice1 - passiveTick.bidPrice1

        if self.order_command.lower() == 'buy':
            volume = self.passive_target_volume - self.passive_traded_volume
            if volume > 0:
                tradePrice = max(passiveTick.bidPrice1 - min_diff, passiveTick.lowerLimit)
                self.writeLog('{}.hedge(), buy'.format(self.algoName))
                self.passive_orderID = self.sell(self.passive_vtSymbol, tradePrice, volume, offset=OFFSET_OPEN)
                self.passive_orderID_history = self.passive_orderID_history + self.passive_orderID + '@' + str(tradePrice) + ':'
                self.entrust = True
                self.count = 0
        elif self.order_command.lower() == 'sell':
            volume = self.passive_target_volume - self.passive_traded_volume
            if volume > 0:
                tradePrice = min(passiveTick.askPrice1 + min_diff,passiveTick.upperLimit)
                self.writeLog('{}.hedge(), sell'.format(self.algoName))
                self.passive_orderID = self.buy(self.passive_vtSymbol, tradePrice, volume, offset=OFFSET_CLOSE)
                self.passive_orderID_history = self.passive_orderID_history + self.passive_orderID + '@' + str(tradePrice) + ':'
                self.entrust = True
                self.count = 0
        elif self.order_command.lower() == 'short':
            volume = self.passive_target_volume - self.passive_traded_volume
            if volume > 0:
                tradePrice = min(passiveTick.askPrice1 + min_diff,passiveTick.upperLimit)
                self.writeLog('{}.hedge(), short'.format(self.algoName))
                self.passive_orderID = self.buy(self.passive_vtSymbol, tradePrice, volume, offset=OFFSET_OPEN)
                self.passive_orderID_history = self.passive_orderID_history + self.passive_orderID + '@' + str(tradePrice) + ':'
                self.entrust = True
                self.count = 0
        elif self.order_command.lower() == 'cover':
            volume = self.passive_target_volume - self.passive_traded_volume
            if volume > 0:
                tradePrice = max(passiveTick.bidPrice1 - min_diff, passiveTick.lowerLimit)
                self.writeLog('{}.hedge(), cover'.format(self.algoName))
                self.passive_orderID = self.sell(self.passive_vtSymbol, tradePrice, volume, offset=OFFSET_CLOSE)
                self.passive_orderID_history = self.passive_orderID_history + self.passive_orderID + '@' + str(tradePrice) + ':'
                self.entrust = True
                self.count = 0

########################################################################
class spreadWidget(AlgoWidget):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, parent=None):
        """Constructor"""
        super(spreadWidget, self).__init__(algoEngine, parent)

        self.templateName = spreadAlgo.templateName

    #----------------------------------------------------------------------
    def initAlgoLayout(self):
        """"""
        self.lineStrategyName = QtWidgets.QLineEdit()
        self.lineVtSymbol = QtWidgets.QLineEdit()

        validator = QtGui.QDoubleValidator()
        validator.setBottom(0)
        intValidator = QtGui.QIntValidator()
        intValidator.setBottom(1)

        self.lineSpread = QtWidgets.QLineEdit()
        self.lineSpread.setValidator(validator)

        self.lineVolume = QtWidgets.QLineEdit()
        self.lineVolume.setValidator(intValidator)

        self.lineTradeCommand = QtWidgets.QLineEdit()

        self.lineInterval = QtWidgets.QLineEdit()
        self.lineInterval.setValidator(intValidator)

        Label = QtWidgets.QLabel

        grid = QtWidgets.QGridLayout()
        grid.addWidget(Label(u'价差合约'), 0, 0)
        grid.addWidget(self.lineVtSymbol, 0, 1)
        grid.addWidget(Label(u'交易命令'), 1, 0)
        grid.addWidget(self.lineTradeCommand, 1, 1)
        grid.addWidget(Label(u'套利价差'), 2, 0)
        grid.addWidget(self.lineSpread, 2, 1)
        grid.addWidget(Label(u'委托数量'), 3, 0)
        grid.addWidget(self.lineVolume, 3, 1)
        grid.addWidget(Label(u'运行间隔'), 4, 0)
        grid.addWidget(self.lineInterval, 4, 1)
        grid.addWidget(Label(u'策略名称'), 5, 0)
        grid.addWidget(self.lineStrategyName, 5, 1)

        return grid

    #----------------------------------------------------------------------
    def getAlgoSetting(self):
        """"""
        setting = OrderedDict()
        setting['templateName'] = self.templateName
        setting['vtSymbol'] = str(self.lineVtSymbol.text())
        setting['tradeCommand'] = str(self.lineTradeCommand.text())
        setting['spread'] = float(self.lineSpread.text())
        setting['volume'] = float(self.lineVolume.text())
        setting['interval'] = int(self.lineInterval.text())
        setting['strategyName'] = str(self.lineStrategyName.text())

        return setting
