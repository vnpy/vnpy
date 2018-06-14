# encoding: UTF-8

from math import floor

from vnpy.trader.vtConstant import (EMPTY_INT, EMPTY_FLOAT, 
                                    EMPTY_STRING, EMPTY_UNICODE,
                                    DIRECTION_LONG, DIRECTION_SHORT,
                                    STATUS_ALLTRADED, STATUS_CANCELLED, STATUS_REJECTED)



########################################################################
class StAlgoTemplate(object):
    """价差算法交易模板"""
    MODE_LONGSHORT = u'双向'
    MODE_LONGONLY = u'做多'
    MODE_SHORTONLY = u'做空'

    SPREAD_LONG = 1
    SPREAD_SHORT = 2

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, spread):
        """Constructor"""
        self.algoEngine = algoEngine        # 算法引擎        
        self.spreadName = spread.name       # 价差名称
        self.spread = spread                # 价差对象      

        self.algoName = EMPTY_STRING        # 算法名称
        
        self.active = False                 # 工作状态
        self.mode = self.MODE_LONGSHORT     # 工作模式
        
        self.buyPrice = EMPTY_FLOAT         # 开平仓价格
        self.sellPrice = EMPTY_FLOAT
        self.shortPrice = EMPTY_FLOAT
        self.coverPrice = EMPTY_FLOAT
        
        self.maxPosSize = EMPTY_INT         # 最大单边持仓量
        self.maxOrderSize = EMPTY_INT       # 最大单笔委托量
    
    #----------------------------------------------------------------------
    def updateSpreadTick(self, spread):
        """"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def updateSpreadPos(self, spread):
        """"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def updateTrade(self, trade):
        """"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def updateOrder(self, order):
        """"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def updateTimer(self):
        """"""
        raise NotImplementedError
        
    #----------------------------------------------------------------------
    def start(self):
        """"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def stop(self):
        """"""
        raise NotImplementedError

    #----------------------------------------------------------------------
    def setBuyPrice(self, buyPrice):
        """设置买开的价格"""
        self.buyPrice = buyPrice
        
    #----------------------------------------------------------------------
    def setSellPrice(self, sellPrice):
        """设置卖平的价格"""
        self.sellPrice = sellPrice
        
    #----------------------------------------------------------------------
    def setShortPrice(self, shortPrice):
        """设置卖开的价格"""
        self.shortPrice = shortPrice
        
    #----------------------------------------------------------------------
    def setCoverPrice(self, coverPrice):
        """设置买平的价格"""
        self.coverPrice = coverPrice
    
    #----------------------------------------------------------------------
    def setMode(self, mode):
        """设置算法交易方向"""
        self.mode = mode
    
    #----------------------------------------------------------------------
    def setMaxOrderSize(self, maxOrderSize):
        """设置最大单笔委托数量"""
        self.maxOrderSize = maxOrderSize
        
    #----------------------------------------------------------------------
    def setMaxPosSize(self, maxPosSize):
        """设置最大持仓数量"""
        self.maxPosSize = maxPosSize
    
    #----------------------------------------------------------------------
    def putEvent(self):
        """发出算法更新事件"""
        self.algoEngine.putAlgoEvent(self)
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """输出算法日志"""
        prefix = '  '.join([self.spreadName, self.algoName])
        content = ':'.join([prefix, content])
        self.algoEngine.writeLog(content)

    #----------------------------------------------------------------------
    def getAlgoParams(self):
        """获取算法参数"""
        d = {
            "spreadName": self.spreadName,
            "algoName": self.algoName,
            "buyPrice": self.buyPrice,
            "sellPrice": self.sellPrice,
            "shortPrice": self.shortPrice,
            "coverPrice": self.coverPrice,
            "maxOrderSize": self.maxOrderSize,
            "maxPosSize": self.maxPosSize,
            "mode": self.mode
        }
        return d
    
    #----------------------------------------------------------------------
    def setAlgoParams(self, d):
        """设置算法参数"""
        self.buyPrice = d.get('buyPrice', EMPTY_FLOAT)
        self.sellPrice = d.get('sellPrice', EMPTY_FLOAT)
        self.shortPrice = d.get('shortPrice', EMPTY_FLOAT)
        self.coverPrice = d.get('coverPrice', EMPTY_FLOAT)
        self.maxOrderSize = d.get('maxOrderSize', EMPTY_INT)
        self.maxPosSize = d.get('maxPosSize', EMPTY_INT)
        self.mode = d.get('mode', self.MODE_LONGSHORT)
        

########################################################################
class SniperAlgo(StAlgoTemplate):
    """狙击算法（市价委托）"""
    FINISHED_STATUS = [STATUS_ALLTRADED, STATUS_CANCELLED, STATUS_REJECTED]

    #----------------------------------------------------------------------
    def __init__(self, algoEngine, spread):
        """Constructor"""
        super(SniperAlgo, self).__init__(algoEngine, spread)
        
        self.algoName = u'Sniper'
        self.quoteInterval = 2      # 主动腿报价撤单再发前等待的时间
        self.quoteCount = 0         # 报价计数
        self.hedgeInterval = 2      # 对冲腿对冲撤单再发前的等待时间
        self.hedgeCount = 0         # 对冲计数
        
        self.activeVtSymbol = spread.activeLeg.vtSymbol                         # 主动腿代码
        self.passiveVtSymbols = [leg.vtSymbol for leg in spread.passiveLegs]    # 被动腿代码列表
        
        # 缓存每条腿对象的字典
        self.legDict = {}
        self.legDict[spread.activeLeg.vtSymbol] = spread.activeLeg
        for leg in spread.passiveLegs:
            self.legDict[leg.vtSymbol] = leg
        
        self.hedgingTaskDict = {}           # 被动腿需要对冲的数量字典  vtSymbol:volume
        self.legOrderDict = {}              # vtSymbol: list of vtOrderID       
        self.orderTradedDict = {}           # vtOrderID: tradedVolume
        
    #----------------------------------------------------------------------
    def updateSpreadTick(self, spread):
        """价差行情更新"""
        self.spread = spread
        
        # 若算法没有启动则直接返回
        if not self.active:
            return
        
        # 若当前已有主动腿委托则直接返回
        if (self.activeVtSymbol in self.legOrderDict and
            self.legOrderDict[self.activeVtSymbol]):
            return

        # 允许做多
        if self.mode == self.MODE_LONGSHORT or self.mode == self.MODE_LONGONLY:
            # 买入
            if (spread.netPos >= 0 and 
                spread.netPos < self.maxPosSize and
                spread.askPrice <= self.buyPrice):
                self.quoteActiveLeg(self.SPREAD_LONG)
                self.writeLog(u'买入开仓')
            
            # 卖出
            elif (spread.netPos > 0 and
                  spread.bidPrice >= self.sellPrice):
                self.quoteActiveLeg(self.SPREAD_SHORT)
                self.writeLog(u'卖出平仓')
        
        # 允许做空
        if self.mode == self.MODE_LONGSHORT or self.mode == self.MODE_SHORTONLY:
            # 做空
            if (spread.netPos <= 0 and
                spread.netPos > -self.maxPosSize and
                spread.bidPrice >= self.shortPrice):
                self.quoteActiveLeg(self.SPREAD_SHORT)
                self.writeLog(u'卖出开仓')
            
            # 平空
            elif (spread.netPos < 0 and
                  spread.askPrice <= self.coverPrice):
                self.quoteActiveLeg(self.SPREAD_LONG)
                self.writeLog(u'买入平仓')
    
    #----------------------------------------------------------------------
    def updateSpreadPos(self, spread):
        """价差持仓更新"""
        self.spread = spread
    
    #----------------------------------------------------------------------
    def updateTrade(self, trade):
        """成交更新"""
        pass
    
    #----------------------------------------------------------------------
    def updateOrder(self, order):
        """委托更新"""
        if not self.active:
            return

        vtOrderID = order.vtOrderID
        vtSymbol = order.vtSymbol
        newTradedVolume = order.tradedVolume
        lastTradedVolume = self.orderTradedDict.get(vtOrderID, 0)
        
        # 检查是否有新的成交
        if newTradedVolume > lastTradedVolume:
            self.orderTradedDict[vtOrderID] = newTradedVolume       # 缓存委托已经成交数量
            volume = newTradedVolume - lastTradedVolume             # 计算本次成交数量
            
            if vtSymbol == self.activeVtSymbol:
                self.newActiveLegTrade(vtSymbol, order.direction, volume)
            else:
                self.newPassiveLegTrade(vtSymbol, order.direction, volume)            
            
        # 处理完成委托
        if order.status in self.FINISHED_STATUS:
            vtOrderID = order.vtOrderID
            vtSymbol = order.vtSymbol
            
            # 从委托列表中移除该委托
            orderList = self.legOrderDict.get(vtSymbol, None)
            
            if orderList and vtOrderID in orderList:
                orderList.remove(vtOrderID)
                
            # 检查若是被动腿，且已经没有未完成委托，则执行对冲
            if not orderList and vtSymbol in self.passiveVtSymbols:
                self.hedgePassiveLeg(vtSymbol)
    
    #----------------------------------------------------------------------
    def updateTimer(self):
        """计时更新"""
        if not self.active:
            return
        
        self.quoteCount += 1
        self.hedgeCount += 1
        
        # 计时到达报价间隔后，则对尚未成交的主动腿委托全部撤单
        # 收到撤单回报后清空委托列表，等待下次价差更新再发单
        if self.quoteCount > self.quoteInterval:
            self.cancelLegOrder(self.activeVtSymbol)
            self.quoteCount = 0
        
        # 计时到达对冲间隔后，则对尚未成交的全部被动腿委托全部撤单
        # 收到撤单回报后，会自动发送新的对冲委托
        if self.hedgeCount > self.hedgeInterval:
            self.cancelAllPassiveLegOrders()
            self.hedgeCount = 0
    
    #----------------------------------------------------------------------
    def checkPrice(self):
        """检查价格"""
        # 做多检查
        if self.mode != self.MODE_SHORTONLY:
            if self.buyPrice >= self.sellPrice:
                self.writeLog(u'启动失败，允许多头交易时BuyPrice必须小于SellPrice')
                return False
            
        # 做空检查
        if self.mode != self.MODE_LONGONLY:
            if self.shortPrice <= self.coverPrice:
                self.writeLog(u'启动失败，允许空头交易时ShortPrice必须大于CoverPrice')
                return False
            
        # 多空检查
        if self.mode == self.MODE_LONGSHORT:
            if self.buyPrice >= self.coverPrice:
                self.writeLog(u'启动失败，允许双向交易时BuyPrice必须小于CoverPrice')
                return False
            
            if self.shortPrice <= self.sellPrice:
                self.writeLog(u'启动失败，允许双向交易时ShortPrice必须大于SellPrice')
                return False
            
        return True
        
    #----------------------------------------------------------------------
    def start(self):
        """启动"""
        # 如果已经运行则直接返回状态
        if self.active:
            return self.active
        
        # 检查价格安全性
        if not self.checkPrice():
            return False
        
        # 启动算法
        self.quoteCount = 0
        self.hedgeCount = 0
            
        self.active = True
        self.writeLog(u'算法启动')
        
        return self.active
    
    #----------------------------------------------------------------------
    def stop(self):
        """停止"""
        if self.active:
            self.hedgingTaskDict.clear()
            self.cancelAllOrders()
           
        self.active = False   
        self.writeLog(u'算法停止')
        
        return self.active
    
    #----------------------------------------------------------------------
    def sendLegOrder(self, leg, legVolume):
        """发送每条腿的委托"""
        vtSymbol = leg.vtSymbol
        volume = abs(legVolume)
        payup = leg.payup
        
        # 发送委托
        if legVolume > 0:
            price = leg.askPrice
            
            if leg.shortPos > 0:
                orderList = self.algoEngine.cover(vtSymbol, price, volume, payup)
            else:
                orderList = self.algoEngine.buy(vtSymbol, price, volume, payup)
                
        elif legVolume < 0:
            price = leg.bidPrice
            
            if leg.longPos > 0:
                orderList = self.algoEngine.sell(vtSymbol, price, volume, payup)
            else:
                orderList = self.algoEngine.short(vtSymbol, price, volume, payup)
                
        # 保存到字典中
        if vtSymbol not in self.legOrderDict:
            self.legOrderDict[vtSymbol] = orderList
        else:
            self.legOrderDict[vtSymbol].extend(orderList)        
    
    #----------------------------------------------------------------------
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
        leg = self.legDict[self.activeVtSymbol]
        legVolume = spreadVolume * leg.ratio        
        self.sendLegOrder(leg, legVolume)
        self.writeLog(u'发出新的主动腿%s狙击单' %self.activeVtSymbol)
        
        self.quoteCount = 0         # 重置主动腿报价撤单等待计数

    #----------------------------------------------------------------------
    def hedgePassiveLeg(self, vtSymbol):
        """被动腿对冲"""
        if vtSymbol not in self.hedgingTaskDict:
            return
        
        orderList = self.legOrderDict.get(vtSymbol, [])
        if orderList:
            return
        
        legVolume = self.hedgingTaskDict[vtSymbol]
        leg = self.legDict[vtSymbol]
        
        self.sendLegOrder(leg, legVolume)
        self.writeLog(u'发出新的被动腿%s对冲单' %vtSymbol)
        
    #----------------------------------------------------------------------
    def hedgeAllPassiveLegs(self):
        """执行所有被动腿对冲"""
        for vtSymbol in self.hedgingTaskDict.keys():
            self.hedgePassiveLeg(vtSymbol)
        
        self.hedgeCount = 0         # 重置被动腿对冲撤单等待计数
        
    #----------------------------------------------------------------------
    def newActiveLegTrade(self, vtSymbol, direction, volume):
        """新的主动腿成交"""
        # 输出日志
        self.writeLog(u'主动腿%s成交，方向%s，数量%s' %(vtSymbol, direction, volume))        
        
        # 将主动腿成交带上方向
        if direction == DIRECTION_SHORT:
            volume = -volume
        
        # 计算主动腿成交后，对应的价差仓位
        spread = self.spread
        activeRatio = spread.activeLeg.ratio
        spreadVolume = round(volume / activeRatio)  # 四舍五入求主动腿成交量对应的价差份数
        
        # 计算价差新仓位，对应的被动腿需要对冲部分
        for leg in self.spread.passiveLegs:
            newHedgingTask = leg.ratio * spreadVolume
            
            if leg.vtSymbol not in self.hedgingTaskDict:
                self.hedgingTaskDict[leg.vtSymbol] = newHedgingTask
            else:
                self.hedgingTaskDict[leg.vtSymbol] += newHedgingTask
        
        # 发出被动腿对冲委托
        self.hedgeAllPassiveLegs()        
    
    #----------------------------------------------------------------------
    def newPassiveLegTrade(self, vtSymbol, direction, volume):
        """新的被动腿成交"""
        if vtSymbol in self.hedgingTaskDict:
            # 计算完成的对冲数量
            if direction == DIRECTION_LONG:
                hedgedVolume = volume
            else:
                hedgedVolume = -volume
                
            # 计算剩余尚未完成的数量
            self.hedgingTaskDict[vtSymbol] -= hedgedVolume
            
            # 如果已全部完成，则从字典中移除
            if not self.hedgingTaskDict[vtSymbol]:
                del self.hedgingTaskDict[vtSymbol]
                
        # 输出日志
        self.writeLog(u'被动腿%s成交，方向%s，数量%s' %(vtSymbol, direction, volume))
                
    #----------------------------------------------------------------------
    def cancelLegOrder(self, vtSymbol):
        """撤销某条腿的委托"""
        if vtSymbol not in self.legOrderDict:
            return
        
        orderList = self.legOrderDict[vtSymbol]
        if not orderList:
            return
        
        for vtOrderID in orderList:
            self.algoEngine.cancelOrder(vtOrderID)
            
        self.writeLog(u'撤单%s的所有委托' %vtSymbol)
            
    #----------------------------------------------------------------------
    def cancelAllOrders(self):
        """撤销全部委托"""
        for orderList in self.legOrderDict.values():
            for vtOrderID in orderList:
                self.algoEngine.cancelOrder(vtOrderID)
        
        self.writeLog(u'全部撤单')
    
    #----------------------------------------------------------------------
    def cancelAllPassiveLegOrders(self):
        """撤销全部被动腿委托"""
        cancelPassive = False
        
        for vtSymbol in self.passiveVtSymbols:
            if vtSymbol in self.legOrderDict and self.legOrderDict[vtSymbol]:
                self.cancelLegOrder(vtSymbol)
                cancelPassive = True

        # 只有确实发出撤单委托时，才输出信息        
        if cancelPassive:
            self.writeLog(u'被动腿全撤')
