# encoding: UTF-8

from vtConstant import *

from ctaConstant import *

from datetime import datetime

########################################################################
class CtaStrategyTemplate(object):
    """CTA策略模板"""
    # 策略类的名称
    strategyClassName = 'Template'
    
    # 参数列表，保存了参数的名称
    paramList = ['vtSymbol']
    
    # 变量列表，保存了变量的名称

    varList = ['trading']

    # ----------------------------------------------------------------------
    def __init__(self, ctaEngine, name, setting=None):
        """Constructor"""
        self.ctaEngine = ctaEngine
        self.name = name

        self.vtSymbol = EMPTY_STRING        # 交易的合约vt系统代码 AU1606，SR605
        self.symbol = EMPTY_STRING          # 交易的合约代码（除郑商所外与vtSymbol一致，一般为两位代码+两位年份+两位月份）AU1606，SR1605
        self.shortSymbol = EMPTY_STRING     # 合约类型代码
        
        self.tickDbName = EMPTY_STRING      # tick数据库名称
        self.barDbName = EMPTY_STRING       # bar数据库名称
        
        self.trading = False                # 控制是否启动交易

        # 委托单状态
        self.entrust = 0            # 0 表示没有委托，1 表示存在多仓的委托，-1 表示存在空仓的委托

        # 保存委托单编号和相关委托单的字典
        # key为委托单编号
        # value为该合约相关的委托单
        self.uncompletedOrders = {}

        #self.init()                         # 初始化策略 Move to inhert strategy
        #if setting:
        #    self.setParam(setting)
    
    # ----------------------------------------------------------------------
    def init(self):
        """初始化策略（必须由用户继承实现）"""
        raise NotImplementedError
    
    # ----------------------------------------------------------------------
    def start(self):
        """启动策略（必须由用户继承实现）"""
        raise NotImplementedError
    
    # ----------------------------------------------------------------------
    def stop(self):
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
    
    # ----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        raise NotImplementedError
    
    # ----------------------------------------------------------------------
    def buy(self, price, volume, stop=False,orderTime=datetime.now()):
        """买开"""
        # 如果stop为True，则意味着发本地停止单
        if self.trading:
            if stop:
                self.writeCtaLog(u'本地停止单，Buy买开,Price:{0},Volume:{1}'.format(price, volume))
                orderID = self.ctaEngine.sendStopOrder(self.vtSymbol, CTAORDER_BUY, price, volume, self)
            else:
                self.writeCtaLog(u'Buy买开,Price:{0},Volume:{1}'.format(price, volume))

                orderID = self.ctaEngine.sendOrder(self.vtSymbol, CTAORDER_BUY, price, volume, self)

                if orderID:
                    self.entrust = 1                            # 委托状态

                    self.uncompletedOrders[orderID] = {'DIRECTION': DIRECTION_LONG,
                                           'OFFSET': OFFSET_OPEN,
                                           'Volume': volume,
                                           'Price': price,
                                           'OrderTime': orderTime
                                           }
            return orderID
        else:
            return None
    
    # ----------------------------------------------------------------------
    def sell(self, price, volume, stop=False, orderTime=datetime.now()):
        """卖平"""
        # 如果stop为True，则意味着发本地停止单
        if self.trading:
            if stop:
                self.writeCtaLog(u'本地停止单，sell卖平,Price:{0},Volume:{1}'.format(price, volume))
                orderID = self.ctaEngine.sendStopOrder(self.vtSymbol, CTAORDER_SELL, price, volume, self)
            else:
                self.writeCtaLog(u'sell卖平,Price:{0},Volume:{1}'.format(price, volume))

                orderID = self.ctaEngine.sendOrder(self.vtSymbol, CTAORDER_SELL, price, volume, self)

                if orderID:
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
            return None            

    # ----------------------------------------------------------------------
    def short(self, price, volume, stop=False, orderTime=datetime.now()):
        """卖开"""
        # 如果stop为True，则意味着发本地停止单
        if self.trading:
            if stop:
                self.writeCtaLog(u'本地停止单，short卖开,Price:{0},Volume:{1}'.format(price, volume))
                orderID = self.ctaEngine.sendStopOrder(self.vtSymbol, CTAORDER_SHORT, price, volume, self)
            else:
                self.writeCtaLog(u'short卖开,Price:{0},Volume:{1}'.format(price, volume))
                orderID = self.ctaEngine.sendOrder(self.vtSymbol, CTAORDER_SHORT, price, volume, self)

                if orderID:
                    self.entrust = -1                           # 委托状态
                    self.uncompletedOrders[orderID] = {'DIRECTION': DIRECTION_SHORT,
                                           'OFFSET': OFFSET_OPEN,
                                           'Volume': volume,
                                           'Price': price,
                                           'OrderTime':  orderTime
                                           }

            return orderID
        else:
            return None            
 
    # ----------------------------------------------------------------------
    def cover(self, price, volume, stop=False,orderTime=datetime.now()):
        """买平"""
        if self.trading:
            # 如果stop为True，则意味着发本地停止单
            if stop:
                self.writeCtaLog(u'本地停止单，cover，买平,Price:{0},Volume:{1}'.format(price, volume))
                orderID = self.ctaEngine.sendStopOrder(self.vtSymbol, CTAORDER_COVER, price, volume, self)
            else:
                self.writeCtaLog(u'Cover买平,Price:{0},Volume:{1}'.format(price, volume))

                orderID = self.ctaEngine.sendOrder(self.vtSymbol, CTAORDER_COVER, price, volume, self)

                if orderID:
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
            return None        
        
    # ----------------------------------------------------------------------
    def cancelOrder(self, orderID):
        """撤单"""
        if STOPORDERPREFIX in orderID:
            self.ctaEngine.cancelStopOrder(orderID)
        else:
            self.ctaEngine.cancelOrder(orderID)
    
    # ----------------------------------------------------------------------
    def insertTick(self, tick):
        """向数据库中插入tick数据"""
        self.ctaEngine.insertData(self.tickDbName, self.vtSymbol, tick)
    
    # ----------------------------------------------------------------------
    def insertBar(self, bar):
        """向数据库中插入bar数据"""
        self.ctaEngine.insertData(self.barDbName, self.vtSymbol, bar)
        
    # ----------------------------------------------------------------------
    def loadTick(self, startDate):
        """读取tick数据"""
        return self.ctaEngine.loadTick(self.tickDbName, self.vtSymbol, startDate)
    
    # ----------------------------------------------------------------------
    def loadBar(self, startDate):
        """读取bar数据"""
        return self.ctaEngine.loadBar(self.barDbName, self.vtSymbol, startDate)
    
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
        self.ctaEngine.writeCtaLog(self.name+':'+content)


########################################################################
class TestStrategy(CtaStrategyTemplate):
    """测试策略"""
    
    # ----------------------------------------------------------------------
    def __init__(self, ctaEngine, name, setting=None):
        """Constructor"""
        super(TestStrategy, self).__init__(ctaEngine, name, setting)
        
        self.strategyClassName = 'TestStrategy'
        
        self.author = u'用Python的交易员'    # 作者
        
        self.pos = EMPTY_INT            # 持仓
        self.lastPrice = EMPTY_FLOAT    # 最新价
        
        # 参数和变量列表设置
        self.paramList.append('author')
        
        self.varList.append('pos')
        self.varList.append('lastPrice')
    
    # ----------------------------------------------------------------------
    def init(self):
        """初始化策略（必须由用户继承实现）"""
        self.writeCtaLog(u'测试策略%s初始化' %self.name)
    
    # ----------------------------------------------------------------------
    def start(self):
        """启动策略（必须由用户继承实现）"""
        self.writeCtaLog(u'测试策略%s启动' %self.name)
    
    # ----------------------------------------------------------------------
    def stop(self):
        """停止策略（必须由用户继承实现）"""
        self.writeCtaLog(u'测试策略%s停止' %self.name)
        
    # ----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送（必须由用户继承实现）"""
        self.writeCtaLog(u'测试策略%s收到Tick' %self.name)
        self.lastPrice = tick.lastPrice
        
    # ----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        self.writeCtaLog(u'onOrder不会被调用')
    
    # ----------------------------------------------------------------------
    def onTrade(self, trade):
        """收到成交推送（必须由用户继承实现）"""
        self.writeCtaLog(u'onTrade不会被调用')
    
    # ----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        self.writeCtaLog(u'测试策略%s收到Bar' %self.name)    
        
        
    
