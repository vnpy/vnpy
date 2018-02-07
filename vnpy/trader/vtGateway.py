# encoding: UTF-8

import time,os
from datetime import datetime

from vnpy.trader.vtEvent import *
from vnpy.trader.vtConstant import *
from vnpy.trader.vtObject import *

from vnpy.trader.setup_logger import setup_logger


########################################################################
class VtGateway(object):
    """交易接口"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName):
        """Constructor"""
        self.eventEngine = eventEngine
        self.gatewayName = gatewayName
        self.logger = None
        self.accountID = 'AccountID'
        self.createLogger()

    # ----------------------------------------------------------------------
    def onTick(self, tick):
        """市场行情推送"""
        # 通用事件
        event1 = Event(type_=EVENT_TICK)
        event1.dict_['data'] = tick
        self.eventEngine.put(event1)

        # 特定合约代码的事件
        event2 = Event(type_=EVENT_TICK+tick.vtSymbol)
        event2.dict_['data'] = tick
        self.eventEngine.put(event2)
    
    # ----------------------------------------------------------------------
    def onTrade(self, trade):
        """成交信息推送"""
        # 通用事件
        event1 = Event(type_=EVENT_TRADE)
        event1.dict_['data'] = trade
        self.eventEngine.put(event1)
        
        # 特定合约的成交事件
        event2 = Event(type_=EVENT_TRADE+trade.vtSymbol)
        event2.dict_['data'] = trade
        self.eventEngine.put(event2)        
    
    # ----------------------------------------------------------------------
    def onOrder(self, order):
        """订单变化推送"""
        # 通用事件
        event1 = Event(type_=EVENT_ORDER)
        event1.dict_['data'] = order
        self.eventEngine.put(event1)
        
        # 特定订单编号的事件
        event2 = Event(type_=EVENT_ORDER+order.vtOrderID)
        event2.dict_['data'] = order
        self.eventEngine.put(event2)
    
    # ----------------------------------------------------------------------
    def onPosition(self, position):
        """持仓信息推送"""
        # 通用事件
        event1 = Event(type_=EVENT_POSITION)
        event1.dict_['data'] = position
        self.eventEngine.put(event1)
        
        # 特定合约代码的事件
        event2 = Event(type_=EVENT_POSITION+position.vtSymbol)
        event2.dict_['data'] = position
        self.eventEngine.put(event2)
    
    # ----------------------------------------------------------------------
    def onAccount(self, account):
        """账户信息推送"""
        # 通用事件
        event1 = Event(type_=EVENT_ACCOUNT)
        event1.dict_['data'] = account
        self.eventEngine.put(event1)
        
        # 特定合约代码的事件
        event2 = Event(type_=EVENT_ACCOUNT+account.vtAccountID)
        event2.dict_['data'] = account
        self.eventEngine.put(event2)

        # 更新账号ID
        self.accountID = account.vtAccountID
    # ----------------------------------------------------------------------
    def onError(self, error):
        """错误信息推送"""
        # 通用事件
        event1 = Event(type_=EVENT_ERROR)
        event1.dict_['data'] = error
        self.eventEngine.put(event1)

        logMsg = u'{0}:[{1}]:{2}'.format(error.gatewayName, error.errorID,error.errorMsg )
        # 写入本地log日志
        if self.logger:
            self.logger.info(logMsg)
        else:
            self.createLogger()

    # ----------------------------------------------------------------------
    def onLog(self, log):
        """日志推送"""
        # 通用事件
        event1 = Event(type_=EVENT_LOG)
        event1.dict_['data'] = log
        self.eventEngine.put(event1)

        # 写入本地log日志
        if self.logger:
            self.logger.info(log.logContent)
        else:
            self.createLogger()

    def createLogger(self):
        filename = os.path.abspath(os.path.join(os.path.dirname(__file__),  'logs', 'Gateway'))
        print( u'create logger:{}'.format(filename))
        self.logger = setup_logger(filename=filename, name='vnpy', debug=True)

    # ----------------------------------------------------------------------
    def onContract(self, contract):
        """合约基础信息推送"""
        # 通用事件
        event1 = Event(type_=EVENT_CONTRACT)
        event1.dict_['data'] = contract
        self.eventEngine.put(event1)        
    
    # ----------------------------------------------------------------------
    def connect(self):
        """连接"""
        pass
    
    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        pass
    
    # ----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        pass
    
    # ----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        pass
    
    # ----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        pass
    
    # ----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        pass

    def checkStatus(self):
        """查询状态"""
        return True

    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        pass

    
    
    
    

    
    
    
