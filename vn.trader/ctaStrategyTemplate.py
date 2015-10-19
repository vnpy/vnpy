# encoding: UTF-8

from ctaConstant import *


########################################################################
class CtaStrategyTemplate(object):
    """CTA策略模板"""
    # 策略类的名称
    strategyClassName = 'Template'
    
    # 参数列表，保存了参数的名称
    paramList = ['vtSymbol']
    
    # 变量列表，保存了变量的名称
    varList = []

    #----------------------------------------------------------------------
    def __init__(self, ctaEngine, setting=None):
        """Constructor"""
        self.ctaEngine = ctaEngine
        
        self.vtSymbol = EMPTY_STRING        # 交易的合约vt系统代码
        
        self.tickDbName = EMPTY_STRING      # tick数据库名称
        self.barDbName = EMPTY_STRING       # bar数据库名称
        
        self.trading = False                # 控制是否启动交易
        
        self.init()                         # 初始化策略
        
        if setting:
            self.setParam(setting)
    
    #----------------------------------------------------------------------
    def init(self):
        """初始化策略（必须由用户继承实现）"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def start(self):
        """启动策略（必须由用户继承实现）"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def stop(self):
        """停止策略（必须由用户继承实现）"""
        raise NotImplementedError
        
    #----------------------------------------------------------------------
    def onTick(self, tick):
        """收到行情TICK推送（必须由用户继承实现）"""
        raise NotImplementedError
        
    #----------------------------------------------------------------------
    def onOrder(self, order):
        """收到委托变化推送（必须由用户继承实现）"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """收到成交推送（必须由用户继承实现）"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onBar(self, bar):
        """收到Bar推送（必须由用户继承实现）"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def buy(self, price, volume, stop=False):
        """买开"""
        # 如果stop为True，则意味着发本地停止单
        if self.trading:
            if stop:
                orderID = self.ctaEngine.sendStopOrder(self.vtSymbol, CTAORDER_BUY, price, volume, self)
            else:
                orderID = self.ctaEngine.sendOrder(self.vtSymbol, CTAORDER_BUY, price, volume, self)
            return orderID
        else:
            return None
    
    #----------------------------------------------------------------------
    def sell(self, price, volume, stop=False):
        """卖平"""
        # 如果stop为True，则意味着发本地停止单
        if self.trading:
            if stop:
                orderID = self.ctaEngine.sendStopOrder(self.vtSymbol, CTAORDER_SELL, price, volume, self)
            else:
                orderID = self.ctaEngine.sendOrder(self.vtSymbol, CTAORDER_SELL, price, volume, self)  
            return orderID
        else:
            return None            

    #----------------------------------------------------------------------
    def short(self, price, volume, stop=False):
        """卖开"""
        # 如果stop为True，则意味着发本地停止单
        if self.trading:
            if stop:
                orderID = self.ctaEngine.sendStopOrder(self.vtSymbol, CTAORDER_SHORT, price, volume, self)
            else:
                orderID = self.ctaEngine.sendOrder(self.vtSymbol, CTAORDER_SHORT, price, volume, self)   
            return orderID
        else:
            return None            
 
    #----------------------------------------------------------------------
    def cover(self, price, volume, stop=False):
        """买平"""
        if self.trading:
            # 如果stop为True，则意味着发本地停止单
            if stop:
                orderID = self.ctaEngine.sendStopOrder(self.vtSymbol, CTAORDER_COVER, price, volume, self)
            else:
                orderID = self.ctaEngine.sendOrder(self.vtSymbol, CTAORDER_COVER, price, volume, self) 
            return orderID
        else:
            return None        
        
    #----------------------------------------------------------------------
    def cancelOrder(self, orderID):
        """撤单"""
        if STOPORDERPREFIX in orderID:
            self.ctaEngine.cancelStopOrder(orderID)
        else:
            self.ctaEngine.cancelOrder(orderID)
    
    #----------------------------------------------------------------------
    def insertTick(self, tick):
        """向数据库中插入tick数据"""
        self.ctaEngine.insertData(self.tickDbName, self.vtSymbol, tick)
    
    #----------------------------------------------------------------------
    def insertBar(self, bar):
        """向数据库中插入bar数据"""
        self.ctaEngine.insertData(self.barDbName, self.vtSymbol, bar)
        
    #----------------------------------------------------------------------
    def loadTick(self, startDate):
        """读取tick数据"""
        return self.ctaEngine.loadTick(self.tickDbName, self.vtSymbol, startDate)
    
    #----------------------------------------------------------------------
    def loadBar(self, startDate):
        """读取bar数据"""
        return self.ctaEngine.loadBar(self.barDbName, self.vtSymbol, startDate)
    
    #----------------------------------------------------------------------    
    def setParam(self, setting):
        """设置参数"""
        d = self.__dict__
        for key in self.paramList:
            if key in setting:
                d[key] = paramDict[key]
                
    #----------------------------------------------------------------------
    def getToday(self):
        """查询当前日期"""
        return self.ctaEngine.getToday()
    
    
    