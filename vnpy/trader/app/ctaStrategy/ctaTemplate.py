# encoding: UTF-8

'''
本文件包含了CTA引擎中的策略开发用模板，开发策略时需要继承CtaTemplate类。
'''

from datetime import datetime

from .ctaBase import *
from vnpy.trader.vtConstant import *


########################################################################
class CtaTemplate(object):
    """CTA策略模板"""
    
    # 策略类的名称和作者
    className = 'CtaTemplate'
    author = EMPTY_UNICODE
    
    # MongoDB数据库的名称，K线数据库默认为1分钟
    tickDbName = TICK_DB_NAME
    barDbName = MINUTE_DB_NAME
    
    # 策略的基本参数
    name = 'StrategyName'           # 策略实例名称
    vtSymbol = EMPTY_STRING        # 交易的合约vt系统代码
    symbol = EMPTY_STRING          # 交易的合约代码（除郑商所外与vtSymbol一致，一般为两位代码+两位年份+两位月份）AU1606，SR1605
    shortSymbol = EMPTY_STRING     # 合约类型代码

    productClass = EMPTY_STRING    # 产品类型（只有IB接口需要）
    currency = EMPTY_STRING        # 货币（只有IB接口需要）
    
    # 策略的基本变量，由引擎管理
    inited = False                 # 是否进行了初始化
    trading = False                # 是否启动交易，由引擎管理
    pos = 0                        # 持仓情况
    backtesting = False            # 是否回测

    # 参数列表，保存了参数的名称
    paramList = ['name',
                 'className',
                 'author',
                 'vtSymbol',
                 'symbol',
                 'shortSymbol',
                 'backtesting']
    
    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos']

    # ----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        self.ctaEngine = ctaEngine

        # 委托单状态
        self.entrust = 0            # 0 表示没有委托，1 表示存在多仓的委托，-1 表示存在空仓的委托

        # 保存委托单编号和相关委托单的字典
        # key为委托单编号
        # value为该合约相关的委托单
        self.uncompletedOrders = {}

        # 设置策略的参数
        if setting:
            self.writeCtaLog(u'基类设置参数')
            d = self.__dict__
            for key in self.paramList:
                if key in setting:
                    d[key] = setting[key]
    
    # ----------------------------------------------------------------------
    def onInit(self):
        """初始化策略（必须由用户继承实现）"""
        raise NotImplementedError
    
    # ----------------------------------------------------------------------
    def onStart(self):
        """启动策略（必须由用户继承实现）"""
        raise NotImplementedError
    
    # ----------------------------------------------------------------------
    def onStop(self):
        """停止策略（必须由用户继承实现）"""
        raise NotImplementedError

    # ----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送（必须由用户继承实现）"""
        raise NotImplementedError

    # ----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        raise NotImplementedError
    
    # ----------------------------------------------------------------------
    def onTrade(self, trade):
        """收到成交推送（必须由用户继承实现）"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        raise NotImplementedError
    
    # ----------------------------------------------------------------------
    def buy(self, price, volume, stop=False ,orderTime=datetime.now(),grid=None):
        """买开"""
        orderID = self.sendOrder(CTAORDER_BUY, price, volume, stop)
        if orderID !='':
            self.entrust = 1                            # 委托状态
            d = {'DIRECTION': DIRECTION_LONG, 'OFFSET': OFFSET_OPEN,
                 'Volume': volume, 'TradedVolume': EMPTY_INT,
                 'Price': price, 'OrderTime': orderTime}
            if grid is not None:
                d['Grid'] = grid

            self.uncompletedOrders[orderID] = d
            return orderID
        else:
            # 交易停止时发单返回空字符串
            return ''
    
    # ----------------------------------------------------------------------
    def sell(self, price, volume, stop=False, orderTime=datetime.now(),grid=None):
        """卖平"""
        orderID = self.sendOrder(CTAORDER_SELL, price, volume, stop)
        if orderID !='':
            self.entrust = -1                           # 置当前策略的委托单状态
            # 记录委托单
            d = {'DIRECTION': DIRECTION_SHORT,'OFFSET': OFFSET_CLOSE,
                 'Volume': volume, 'TradedVolume': EMPTY_INT,
                 'Price': price, 'OrderTime': orderTime}
            if grid is not None:
                d['Grid'] = grid
            self.uncompletedOrders[orderID] = d
            return orderID
        else:
            # 交易停止时发单返回空字符串
            return ''

    # ----------------------------------------------------------------------
    def short(self, price, volume, stop=False, orderTime=datetime.now(),grid = None):
        """卖开"""
        orderID = self.sendOrder(CTAORDER_SHORT, price, volume, stop)
        if orderID !='':
            self.entrust = -1                           # 委托状态
            d = {'DIRECTION': DIRECTION_SHORT, 'OFFSET': OFFSET_OPEN,
                 'Volume': volume, 'TradedVolume': EMPTY_INT,
                 'Price': price, 'OrderTime':  orderTime }
            if grid is not None:
                d['Grid'] = grid
            self.uncompletedOrders[orderID] = d
            return orderID
        else:
            # 交易停止时发单返回空字符串
            return ''
 
    # ----------------------------------------------------------------------
    def cover(self, price, volume, stop=False, orderTime=datetime.now(),grid = None):
        """买平"""
        orderID = self.sendOrder(CTAORDER_COVER, price, volume, stop)

        if orderID !='':
            self.entrust = 1                           # 置当前策略的委托单状态
            # 记录委托单
            d ={'DIRECTION': DIRECTION_LONG, 'OFFSET': OFFSET_CLOSE,
                 'Volume': volume, 'TradedVolume': EMPTY_INT,
                 'Price': price, 'OrderTime': orderTime}
            if grid is not None:
                d['Grid'] = grid
            self.uncompletedOrders[orderID] = d
            return orderID
        else:
            # 交易停止时发单返回空字符串
            return ''

    # ----------------------------------------------------------------------
    def sendOrder(self, orderType, price, volume, stop=False):
        """发送委托"""
        if self.trading:
            # 如果stop为True，则意味着发本地停止单
            if stop:
                vtOrderID = self.ctaEngine.sendStopOrder(self.vtSymbol, orderType, price, volume, self)
            else:
                vtOrderID = self.ctaEngine.sendOrder(self.vtSymbol, orderType, price, volume, self) 
            return vtOrderID
        else:
            # 交易停止时发单返回空字符串
            return ''
        
    #----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """撤单"""

        # 如果发单号为空字符串，则不进行后续操作
        if not vtOrderID or vtOrderID == '':
            return

        if STOPORDERPREFIX in vtOrderID:
            self.ctaEngine.cancelStopOrder(vtOrderID)
        else:
            self.ctaEngine.cancelOrder(vtOrderID)
    
    #----------------------------------------------------------------------
    def insertTick(self, tick):
        """向数据库中插入tick数据"""
        self.ctaEngine.insertData(self.tickDbName, self.vtSymbol, tick)
    
    #----------------------------------------------------------------------
    def insertBar(self, bar):
        """向数据库中插入bar数据"""
        self.ctaEngine.insertData(self.barDbName, self.vtSymbol, bar)
        
    #----------------------------------------------------------------------
    def loadTick(self, days):
        """读取tick数据"""
        return self.ctaEngine.loadTick(self.tickDbName, self.vtSymbol, days)
    
    #----------------------------------------------------------------------
    def loadBar(self, days):
        """读取bar数据"""
        return self.ctaEngine.loadBar(self.barDbName, self.vtSymbol, days)

    def saveData(self):
        """保持bar数据"""
        pass

    def onTimer(self):
        """定时执行任务
        由mainEngine驱动"""
        pass

    # ----------------------------------------------------------------------
    def setParam(self, setting):
        """设置参数"""
        d = self.__dict__
        for key in self.paramList:
            if key in setting:

                d[key] = setting[key]

    # ----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """记录CTA日志"""
        content = self.name + ':' + content
        self.ctaEngine.writeCtaLog(content)

    # ----------------------------------------------------------------------
    def writeCtaError(self, content):
        """记录CTA出错日志"""
        content = self.name + ':' + content
        self.ctaEngine.writeCtaError(content)

    # ----------------------------------------------------------------------
    def writeCtaWarning(self, content):
        """记录CTA告警日志"""
        content = self.name + ':' + content
        self.ctaEngine.writeCtaWarning(content)

    # ----------------------------------------------------------------------
    def writeCtaNotification(self, content):
        """记录CTA通知日志"""
        content = self.name + ':' + content

        if not self.backtesting:
            self.ctaEngine.writeCtaNotification(content)
        else:
            self.ctaEngine.writeCtaLog(content)

    # ----------------------------------------------------------------------
    def writeCtaCritical(self, content):
        """记录CTA系统异常日志"""
        content = self.name + ':' + content
        if not self.backtesting:
            self.ctaEngine.writeCtaCritical(content)
        else:
            self.ctaEngine.writeCtaError(content)

    def sendSignal(self,direction,price, level):
        """发送信号通知"""
        try:
            if not self.backtesting:
                self.ctaEngine.sendCtaSignal(source=self.name, symbol=self.vtSymbol, direction=direction, price=price, level=level)

        except Exception as ex:
            self.writeCtaError(u'sendSignal Exception:{0}'.format(str(ex)))

    #----------------------------------------------------------------------
    def putEvent(self):
        """发出策略状态变化事件"""
        self.ctaEngine.putStrategyEvent(self.name)

    #----------------------------------------------------------------------
    def getEngineType(self):
        """查询当前运行的环境"""
        return self.ctaEngine.engineType

    def getFullSymbol(self, symbol):
        """获取全路径得合约名称"""
        short_symbol = self.ctaEngine.getShortSymbol(symbol)
        if short_symbol == symbol:
            return symbol

        symbol_month = symbol.replace(short_symbol, '')
        if len(symbol_month) == 3:
            return '{0}1{1}'.format(short_symbol, symbol_month)
        else:
            return symbol

########################################################################
class TargetPosTemplate(CtaTemplate):
    """
    允许直接通过修改目标持仓来实现交易的策略模板

    开发策略时，无需再调用buy/sell/cover/short这些具体的委托指令，
    只需在策略逻辑运行完成后调用setTargetPos设置目标持仓，底层算法
    会自动完成相关交易，适合不擅长管理交易挂撤单细节的用户。

    使用该模板开发策略时，请在以下回调方法中先调用母类的方法：
    onTick
    onBar
    onOrder

    假设策略名为TestStrategy，请在onTick回调中加上：
    super(TestStrategy, self).onTick(tick)

    其他方法类同。
    """

    className = 'TargetPosTemplate'
    author = u'量衍投资'

    # 目标持仓模板的基本变量
    tickAdd = 1             # 委托时相对基准价格的超价
    lastTick = None         # 最新tick数据
    lastBar = None          # 最新bar数据
    targetPos = EMPTY_INT   # 目标持仓
    orderList = []          # 委托号列表

    # 变量列表，保存了变量的名称
    varList = ['inited',
               'trading',
               'pos',
               'targetPos']

    #----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting):
        """Constructor"""
        super(TargetPosTemplate, self).__init__(ctaEngine, setting)

    #----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情推送"""
        self.lastTick = tick

        # 实盘模式下，启动交易后，需要根据tick的实时推送执行自动开平仓操作
        if self.trading:
            self.trade()

    #----------------------------------------------------------------------
    def onBar(self, bar):
        """收到K线推送"""
        self.lastBar = bar

    #----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托推送"""
        if order.status == STATUS_ALLTRADED or order.status == STATUS_CANCELLED:
            self.orderList.remove(order.vtOrderID)

    #----------------------------------------------------------------------
    def setTargetPos(self, targetPos):
        """设置目标仓位"""
        self.targetPos = targetPos

        self.trade()

    #----------------------------------------------------------------------
    def trade(self):
        """执行交易"""
        # 先撤销之前的委托
        for vtOrderID in self.orderList:
            self.cancelOrder(vtOrderID)
        self.orderList = []

        # 如果目标仓位和实际仓位一致，则不进行任何操作
        posChange = self.targetPos - self.pos
        if not posChange:
            return

        # 确定委托基准价格，有tick数据时优先使用，否则使用bar
        longPrice = 0
        shortPrice = 0

        if self.lastTick:
            if posChange > 0:
                longPrice = self.lastTick.askPrice1 + self.tickAdd
            else:
                shortPrice = self.lastTick.bidPrice1 - self.tickAdd
        else:
            if posChange > 0:
                longPrice = self.lastBar.close + self.tickAdd
            else:
                shortPrice = self.lastBar.close - self.tickAdd

        # 回测模式下，采用合并平仓和反向开仓委托的方式
        if self.getEngineType() == ENGINETYPE_BACKTESTING:
            if posChange > 0:
                vtOrderID = self.buy(longPrice, abs(posChange))
            else:
                vtOrderID = self.short(shortPrice, abs(posChange))
            self.orderList.append(vtOrderID)

        # 实盘模式下，首先确保之前的委托都已经结束（全成、撤销）
        # 然后先发平仓委托，等待成交后，再发送新的开仓委托
        else:
            # 检查之前委托都已结束
            if self.orderList:
                return

            # 买入
            if posChange > 0:
                if self.pos < 0:
                    vtOrderID = self.cover(longPrice, abs(self.pos))
                else:
                    vtOrderID = self.buy(longPrice, abs(posChange))
            # 卖出
            else:
                if self.pos > 0:
                    vtOrderID = self.sell(shortPrice, abs(self.pos))
                else:
                    vtOrderID = self.short(shortPrice, abs(posChange))
            self.orderList.append(vtOrderID)
