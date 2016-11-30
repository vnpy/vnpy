# encoding: UTF-8

'''
本文件包含了CTA引擎中的策略开发用模板，开发策略时需要继承CtaTemplate类。
'''

from ctaBase import *
from vtConstant import *
from datetime import datetime


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
    def buy(self, price, volume, stop=False ,orderTime=datetime.now()):
        """买开"""
        orderID = self.sendOrder(CTAORDER_BUY, price, volume, stop)
        if orderID !='':
            self.entrust = 1                            # 委托状态

            self.uncompletedOrders[orderID] = {'DIRECTION': DIRECTION_LONG,
                                               'OFFSET': OFFSET_OPEN,
                                               'Volume': volume,
                                               'Price': price,
                                               'OrderTime': orderTime
                                              }
            return orderID
        else:
            # 交易停止时发单返回空字符串
            return ''
    
    # ----------------------------------------------------------------------
    def sell(self, price, volume, stop=False, orderTime=datetime.now()):
        """卖平"""
        orderID = self.sendOrder(CTAORDER_SELL, price, volume, stop)
        if orderID !='':
            self.entrust = -1                           # 置当前策略的委托单状态
            # 记录委托单
            self.uncompletedOrders[orderID] = {'DIRECTION': DIRECTION_SHORT,
                                               'OFFSET': OFFSET_CLOSE,
                                               'Volume': volume,
                                               'Price': price,
                                               'OrderTime': orderTime
                                              }
            return orderID
        else:
            # 交易停止时发单返回空字符串
            return ''

    # ----------------------------------------------------------------------
    def short(self, price, volume, stop=False, orderTime=datetime.now()):
        """卖开"""
        orderID = self.sendOrder(CTAORDER_SHORT, price, volume, stop)
        if orderID !='':
            self.entrust = -1                           # 委托状态
            self.uncompletedOrders[orderID] = {'DIRECTION': DIRECTION_SHORT,
                                               'OFFSET': OFFSET_OPEN,
                                               'Volume': volume,
                                               'Price': price,
                                               'OrderTime':  orderTime
                                              }
            return orderID
        else:
            # 交易停止时发单返回空字符串
            return ''
 
    # ----------------------------------------------------------------------
    def cover(self, price, volume, stop=False, orderTime=datetime.now()):
        """买平"""
        orderID = self.sendOrder(CTAORDER_COVER, price, volume, stop)

        if orderID !='':
            self.entrust = 1                           # 置当前策略的委托单状态
            # 记录委托单
            self.uncompletedOrders[orderID] = {'DIRECTION': DIRECTION_LONG,
                                               'OFFSET': OFFSET_CLOSE,
                                               'Volume': volume,
                                               'Price': price,
                                               'OrderTime': orderTime
                                              }
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

    def saveBar(self):
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
    def getToday(self):
        """查询当前日期"""
        return self.ctaEngine.getToday()
    # ----------------------------------------------------------------------
    def writeCtaLog(self, content):
        """记录CTA日志"""
        content = self.name + ':' + content
        self.ctaEngine.writeCtaLog(content)
        
    #----------------------------------------------------------------------
    def putEvent(self):
        """发出策略状态变化事件"""
        self.ctaEngine.putStrategyEvent(self.name)

    #----------------------------------------------------------------------
    def getEngineType(self):
        """查询当前运行的环境"""
        return self.ctaEngine.engineType

