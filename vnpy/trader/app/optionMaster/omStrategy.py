# encoding: UTF-8

from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT,
                                    OFFSET_OPEN, OFFSET_CLOSE)


########################################################################
class OmStrategyTemplate(object):
    """策略模板"""

    #----------------------------------------------------------------------
    def __init__(self, engine):
        """Constructor"""
        self.engine = engine
        
        self.name = ''
        
        self.inited = False
        self.trading = False
        
    #----------------------------------------------------------------------
    def onInit(self):
        """初始化"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onStart(self):
        """启动"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onStop(self):
        """停止"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onTick(self, tick):
        """行情推送"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """成交推送"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onOrder(self, order):
        """委托推送"""
        raise NotImplementedError
        
    #----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """撤单"""
        self.engine.cancelOrder(vtOrderID)
        
    #----------------------------------------------------------------------
    def buy(self, vtSymbol, price, volume):
        """开多"""
        return self.engine.buy(vtSymbol, price, volume)
        
    #----------------------------------------------------------------------
    def short(self, vtSymbol, price, volume):
        """开空"""
        return self.engine.short(vtSymbol, price, volume)        

    #----------------------------------------------------------------------
    def sell(self, vtSymbol, price, volume):
        """平多"""
        return self.engine.sell(vtSymbol, price, volume)        

    #----------------------------------------------------------------------
    def cover(self, vtSymbol, price, volume):
        """平空"""
        return self.engine.cover(vtSymbol, price, volume)        
        
    #----------------------------------------------------------------------
    def dbQuery(self, flt):
        """查询数据"""
        return self.engine.dbQuery(self.name, flt)
    
    #----------------------------------------------------------------------
    def dbUpdate(self, d, flt):
        """更新数据"""
        return self.engine.dbUpdate(self.name, d, flt)
    
    #----------------------------------------------------------------------
    def getOption(self, vtSymbol):
        """查询期权数据"""
        return self.engine.getOption(vtSymbol)
        
    #----------------------------------------------------------------------
    def getUnderlying(self, vtSymbol):
        """获取标的信息"""
        return self.engine.getUnderlying(vtSymbol)
    
    #----------------------------------------------------------------------
    def getChain(self, symbol):
        """获取期权链信息"""
        return self.engine.getChain(symbol)
    
    #----------------------------------------------------------------------
    def getPortfolio(self):
        """获取持仓组合信息"""
        return self.engine.getPortfolio()
    
    
