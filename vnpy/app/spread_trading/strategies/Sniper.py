from vnpy.trader.constant import (Direction, Status)
from vnpy.app.spread_trading.template import SpreadTradingTemplate

########################################################################
class SniperAlgo(SpreadTradingTemplate):
    """market order"""
    FINISHED_STATUS = [Status.ALLTRADED, Status.CANCELLED, Status.REJECTED]

    # ----------------------------------------------------------------------
    def __init__(self, algoEngine, spread):
        """Constructor"""
        super(SniperAlgo, self).__init__(algoEngine, spread)
        self.algo_name = self.__class__.__name__
        self.quoteInterval = 2  # waiting time before cancel active legs
        self.quoteCount = 0  # order count
        self.hedgeInterval = 2  # waiting time before hedge
        self.hedgeCount = 0  # hedge count

        self.active_vt_symbol = spread.activeLeg.vt_symbol
        self.passive_vt_symbols = [leg.vt_symbol for leg in spread.passiveLegs]

        # 缓存每条腿对象的字典
        self.legDict = {}
        self.legDict[spread.activeLeg.vt_symbol] = spread.activeLeg
        for leg in spread.passiveLegs:
            self.legDict[leg.vt_symbol] = leg

        self.hedgingTaskDict = {}  # 被动腿需要对冲的数量字典  vtSymbol:volume
        self.legOrderDict = {}  # vtSymbol: list of vtOrderID
        self.orderTradedDict = {}  # vtOrderID: tradedVolume

    # ----------------------------------------------------------------------
    def updateSpreadTick(self, spread):
        """价差行情更新"""
        self.spread = spread

        # 若算法没有启动则直接返回
        if not self.active:
            return

        # 若当前已有主动腿委托则直接返回
        if (self.active_vt_symbol in self.legOrderDict and
                self.legOrderDict[self.active_vt_symbol]):
            return

        # 允许做多
        if self.mode == self.MODE_LONGSHORT or self.mode == self.MODE_LONGONLY:
            # 买入
            if (spread.netPos >= 0 and
                    spread.netPos < self.maxPosSize and
                    spread.askPrice <= self.buyPrice):
                self.quoteActiveLeg(self.SPREAD_LONG)
                self.writeLog('买入开仓')

            # 卖出
            elif (spread.netPos > 0 and
                  spread.bidPrice >= self.sellPrice):
                self.quoteActiveLeg(self.SPREAD_SHORT)
                self.writeLog('卖出平仓')

        # 允许做空
        if self.mode == self.MODE_LONGSHORT or self.mode == self.MODE_SHORTONLY:
            # 做空
            if (spread.netPos <= 0 and
                    spread.netPos > -self.maxPosSize and
                    spread.bidPrice >= self.shortPrice):
                self.quoteActiveLeg(self.SPREAD_SHORT)
                self.writeLog('卖出开仓')

            # 平空
            elif (spread.netPos < 0 and
                  spread.askPrice <= self.coverPrice):
                self.quoteActiveLeg(self.SPREAD_LONG)
                self.writeLog('买入平仓')

    # ----------------------------------------------------------------------
    def updateSpreadPos(self, spread):
        """价差持仓更新"""
        self.spread = spread

    # ----------------------------------------------------------------------
    def updateTrade(self, trade):
        """成交更新"""
        pass

    # ----------------------------------------------------------------------
    def updateOrder(self, order):
        """委托更新"""
        if not self.active:
            return

        vtOrderID = order.vt_orderid
        vt_symbol = order.vt_symbol
        newTradedVolume = order.traded
        lastTradedVolume = self.orderTradedDict.get(vtOrderID, 0)

        # 检查是否有新的成交
        if newTradedVolume > lastTradedVolume:
            self.orderTradedDict[vtOrderID] = newTradedVolume  # 缓存委托已经成交数量
            volume = newTradedVolume - lastTradedVolume  # 计算本次成交数量

            if vt_symbol == self.active_vt_symbol:
                self.newActiveLegTrade(vt_symbol, order.direction, volume)
            else:
                self.newPassiveLegTrade(vt_symbol, order.direction, volume)

                # 处理完成委托
        if order.status in self.FINISHED_STATUS:
            vtOrderID = order.vt_orderid
            vt_symbol = order.vt_symbol

            # 从委托列表中移除该委托
            orderList = self.legOrderDict.get(vt_symbol, None)

            if orderList and vtOrderID in orderList:
                orderList.remove(vtOrderID)

            # 检查若是被动腿，且已经没有未完成委托，则执行对冲
            if not orderList and vt_symbol in self.passive_vt_symbols:
                self.hedgePassiveLeg(vt_symbol)

    # ----------------------------------------------------------------------
    def updateTimer(self):
        """计时更新"""
        if not self.active:
            return

        self.quoteCount += 1
        self.hedgeCount += 1

        # 计时到达报价间隔后，则对尚未成交的主动腿委托全部撤单
        # 收到撤单回报后清空委托列表，等待下次价差更新再发单
        if self.quoteCount > self.quoteInterval:
            self.cancelLegOrder(self.active_vt_symbol)
            self.quoteCount = 0

        # 计时到达对冲间隔后，则对尚未成交的全部被动腿委托全部撤单
        # 收到撤单回报后，会自动发送新的对冲委托
        if self.hedgeCount > self.hedgeInterval:
            self.cancelAllPassiveLegOrders()
            self.hedgeCount = 0

    # ----------------------------------------------------------------------
    def start(self):
        """启动"""
        # 如果已经运行则直接返回状态
        if self.active:
            return self.active

        # 做多检查
        if self.mode != self.MODE_SHORTONLY:
            if self.buyPrice >= self.sellPrice:
                self.writeLog('启动失败，允许多头交易时，买开价必须小于卖平价')
                return self.active

        # 做空检查
        if self.mode != self.MODE_LONGONLY:
            if self.shortPrice <= self.coverPrice:
                self.writeLog('启动失败，允许空头交易时，卖开价必须大于买平价')
                return self.active

        # 多空检查
        if self.mode == self.MODE_LONGSHORT:
            if self.buyPrice >= self.coverPrice:
                self.writeLog('启动失败，允许双向交易时，买开价必须小于买平价')
                return self.active

            if self.shortPrice <= self.sellPrice:
                self.writeLog('启动失败，允许双向交易时，卖开价必须大于卖平价')
                return self.active

        # 启动算法
        self.quoteCount = 0
        self.hedgeCount = 0

        self.active = True
        self.writeLog('算法启动')

        return self.active

    # ----------------------------------------------------------------------
    def stop(self):
        """停止"""
        if self.active:
            self.hedgingTaskDict.clear()
            self.cancelAllOrders()

        self.active = False
        self.writeLog('算法停止')

        return self.active

    # ----------------------------------------------------------------------
    def sendLegOrder(self, leg, legVolume):
        """发送每条腿的委托"""
        vt_symbol = leg.vt_symbol
        volume = abs(legVolume)
        payup = leg.payup

        # 发送委托
        if legVolume > 0:
            price = leg.askPrice

            if leg.shortPos > 0:
                orderList = self.algoEngine.cover(vt_symbol, price, volume, payup)
            else:
                orderList = self.algoEngine.buy(vt_symbol, price, volume, payup)

        elif legVolume < 0:
            price = leg.bidPrice

            if leg.longPos > 0:
                orderList = self.algoEngine.sell(vt_symbol, price, volume, payup)
            else:
                orderList = self.algoEngine.short(vt_symbol, price, volume, payup)

        # 保存到字典中
        if vt_symbol not in self.legOrderDict:
            self.legOrderDict[vt_symbol] = orderList
        else:
            self.legOrderDict[vt_symbol].extend(orderList)

            # ----------------------------------------------------------------------

    def quoteActiveLeg(self, direction):
        """发出主动腿"""
        spread = self.spread

        # 首先计算不带正负号的价差委托量
        if direction == self.SPREAD_LONG:
            spreadVolume = min(spread.askVolume,
                               self.maxPosSize - spread.netPos,
                               self.maxOrderSize)

            # 有价差空头持仓的情况下，则本次委托最多平完空头
            if spread.shortPos > 0:
                spreadVolume = min(spreadVolume, spread.shortPos)
        else:
            spreadVolume = min(spread.bidVolume,
                               self.maxPosSize + spread.netPos,
                               self.maxOrderSize)

            # 有价差多头持仓的情况下，则本次委托最多平完多头
            if spread.longPos > 0:
                spreadVolume = min(spreadVolume, spread.longPos)

        if spreadVolume <= 0:
            return

        # 加上价差方向
        if direction == self.SPREAD_SHORT:
            spreadVolume = -spreadVolume

        # 计算主动腿委托量
        leg = self.legDict[self.active_vt_symbol]
        legVolume = spreadVolume * leg.ratio
        self.sendLegOrder(leg, legVolume)
        self.writeLog('发出新的主动腿%s狙击单' % self.active_vt_symbol)

        self.quoteCount = 0  # 重置主动腿报价撤单等待计数

    # ----------------------------------------------------------------------
    def hedgePassiveLeg(self, vt_symbol):
        """被动腿对冲"""
        if vt_symbol not in self.hedgingTaskDict:
            return

        orderList = self.legOrderDict.get(vt_symbol, [])
        if orderList:
            return

        legVolume = self.hedgingTaskDict[vt_symbol]
        leg = self.legDict[vt_symbol]

        self.sendLegOrder(leg, legVolume)
        self.writeLog('发出新的被动腿%s对冲单' % vt_symbol)

    # ----------------------------------------------------------------------
    def hedgeAllPassiveLegs(self):
        """执行所有被动腿对冲"""
        for vt_symbol in list(self.hedgingTaskDict.keys()):
            self.hedgePassiveLeg(vt_symbol)

        self.hedgeCount = 0  # 重置被动腿对冲撤单等待计数

    # ----------------------------------------------------------------------
    def newActiveLegTrade(self, vt_symbol, direction, volume):
        """新的主动腿成交"""
        # 输出日志
        self.writeLog('主动腿%s成交，方向%s，数量%s' % (vt_symbol, direction, volume))

        # 将主动腿成交带上方向
        if direction == Direction.SHORT:
            volume = -volume

        # 计算主动腿成交后，对应的价差仓位
        spread = self.spread
        activeRatio = spread.activeLeg.ratio
        spreadVolume = round(volume / activeRatio)  # 四舍五入求主动腿成交量对应的价差份数

        # 计算价差新仓位，对应的被动腿需要对冲部分
        for leg in self.spread.passiveLegs:
            newHedgingTask = leg.ratio * spreadVolume

            if leg.vt_symbol not in self.hedgingTaskDict:
                self.hedgingTaskDict[leg.vt_symbol] = newHedgingTask
            else:
                self.hedgingTaskDict[leg.vt_symbol] += newHedgingTask

        # 发出被动腿对冲委托
        self.hedgeAllPassiveLegs()

        # ----------------------------------------------------------------------

    def newPassiveLegTrade(self, vt_symbol, direction, volume):
        """新的被动腿成交"""
        if vt_symbol in self.hedgingTaskDict:
            # 计算完成的对冲数量
            if direction == Direction.LONG:
                hedgedVolume = volume
            else:
                hedgedVolume = -volume

            # 计算剩余尚未完成的数量
            self.hedgingTaskDict[vt_symbol] -= hedgedVolume

            # 如果已全部完成，则从字典中移除
            if not self.hedgingTaskDict[vt_symbol]:
                del self.hedgingTaskDict[vt_symbol]

        # 输出日志
        self.writeLog('被动腿%s成交，方向%s，数量%s' % (vt_symbol, direction, volume))

    # ----------------------------------------------------------------------
    def cancelLegOrder(self, vt_symbol):
        """撤销某条腿的委托"""
        if vt_symbol not in self.legOrderDict:
            return

        orderList = self.legOrderDict[vt_symbol]
        if not orderList:
            return

        for vtOrderID in orderList:
            self.algoEngine.cancelOrder(vtOrderID)

        self.writeLog('撤单%s的所有委托' % vt_symbol)

    # ----------------------------------------------------------------------
    def cancelAllOrders(self):
        """撤销全部委托"""
        for orderList in list(self.legOrderDict.values()):
            for vtOrderID in orderList:
                self.algoEngine.cancelOrder(vtOrderID)

        self.writeLog('全部撤单')

    # ----------------------------------------------------------------------
    def cancelAllPassiveLegOrders(self):
        """撤销全部被动腿委托"""
        cancelPassive = False

        for vt_symbol in self.passive_vt_symbols:
            if vt_symbol in self.legOrderDict and self.legOrderDict[vt_symbol]:
                self.cancelLegOrder(vt_symbol)
                cancelPassive = True

        # 只有确实发出撤单委托时，才输出信息
        if cancelPassive:
            self.writeLog('被动腿全撤')
