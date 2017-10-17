# encoding: UTF-8

'''
本文件中实现了风控引擎，用于提供一系列常用的风控功能：
1. 委托流控（单位时间内最大允许发出的委托数量）
2. 总成交限制（每日总成交数量限制）
3. 单笔委托的委托数量控制
4. 总仓位控制

todo：本风控模块仅支持一个gateway的连接。如果超过多个gateway的连接，仓位模块就会无效啦。
'''

import json
import os
import platform
from datetime import datetime

from vnpy.trader.vtEvent import *
from vnpy.trader.vtConstant import *
from vnpy.trader.vtGateway import VtLogData


########################################################################
class RmEngine(object):
    """风控引擎"""
    settingFileName = 'RM_setting.json'
    path = os.path.abspath(os.path.dirname(__file__))
    settingFileName = os.path.join(path, settingFileName)
    
    name = u'风控模块'

    #----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine
        
        # 是否启动风控
        self.active = False
        
        # 流控相关
        self.orderFlowCount = EMPTY_INT     # 单位时间内委托计数
        self.orderFlowLimit = EMPTY_INT     # 委托限制
        self.orderFlowClear = EMPTY_INT     # 计数清空时间（秒）
        self.orderFlowTimer = EMPTY_INT     # 计数清空时间计时

        # 总仓位相关(0~100+)
        self.percentLimit = 99              # 仓位比例限制
        self.percent = EMPTY_FLOAT          # 当前持仓比例
        self.preBalance = EMPTY_FLOAT       # 昨结
        self.balance = EMPTY_FLOAT          # 当前账号权益
        self.avaliable = EMPTY_FLOAT        # 当前仓位可用资金

        # 强制止损相关
        self.lossLimit = 100000             # 净值亏损线
        self.lastEventTime = None           # 上一次发出净值止损的时间

        # 单笔委托相关
        self.orderSizeLimit = EMPTY_INT     # 单笔委托最大限制
    
        # 成交统计相关
        self.tradeCount = EMPTY_INT         # 当日成交合约数量统计
        self.tradeLimit = EMPTY_INT         # 当日成交合约数量限制
        
        # 活动合约相关
        self.workingOrderLimit = EMPTY_INT  # 活动合约最大限制

        self.loadSetting()
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def loadSetting(self):
        """读取配置"""
        with open(self.settingFileName) as f:
            d = json.load(f)
            
            # 设置风控参数
            self.active = d['active']
            self.orderFlowLimit = d['orderFlowLimit']
            self.orderFlowClear = d['orderFlowClear']
            self.orderSizeLimit = d['orderSizeLimit']
            self.tradeLimit = d['tradeLimit']
            self.workingOrderLimit = d['workingOrderLimit']

            try:
                if d['percentLimit']>0 and d['percentLimit']<100:
                    self.percentLimit = d['percentLimit']
            except KeyError:
                self.percentLimit = 99

            try:
                if d['lossLimit'] > 0:
                    self.lossLimit = d['lossLimit']
            except KeyError:
                self.lossLimit = 10


    # ----------------------------------------------------------------------
    def saveSetting(self):
        """保存风控参数"""
        with open(self.settingFileName, 'w') as f:
            # 保存风控参数
            d = {}

            d['active'] = self.active
            d['orderFlowLimit'] = self.orderFlowLimit
            d['orderFlowClear'] = self.orderFlowClear
            d['orderSizeLimit'] = self.orderSizeLimit
            d['tradeLimit'] = self.tradeLimit
            d['workingOrderLimit'] = self.workingOrderLimit
            d['percentLimit'] = self.percentLimit
            d['lossLimit'] = self.lossLimit

            # 写入json
            jsonD = json.dumps(d, indent=4)
            f.write(jsonD)
        
    # ----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_TRADE, self.updateTrade)
        self.eventEngine.register(EVENT_TIMER, self.updateTimer)
        self.eventEngine.register(EVENT_ACCOUNT, self.updateAccount)
    
    # ----------------------------------------------------------------------
    def updateTrade(self, event):
        """更新成交数据"""
        trade = event.dict_['data']
        self.tradeCount += trade.volume
    
    # ----------------------------------------------------------------------
    def updateTimer(self, event):
        """更新定时器"""
        self.orderFlowTimer += 1
        
        # 如果计时超过了流控清空的时间间隔，则执行清空
        if self.orderFlowTimer >= self.orderFlowClear:
            self.orderFlowCount = 0
            self.orderFlowTimer = 0
    # ----------------------------------------------------------------------
    def updateAccount(self,event):
        """更新账号资金
        add by Incense
        （仅支持一个连接哦。多连接就不做了）
        """
        account = event.dict_['data']
        self.balance = account.balance
        self.available = account.available
        self.preBalance = account.preBalance

        if self.balance == EMPTY_FLOAT:
            self.percent = EMPTY_FLOAT
        else:
            self.percent = round((self.balance - self.available)*100/self.balance,2)

        if self.preBalance ==EMPTY_FLOAT:
            return

        # 判断亏损
        if self.lossLimit > 0 :

            # 当前资金 低于 止损线，存在持仓
            if self.lossLimit < self.balance < self.lossLimit*1.05 and self.balance != self.available:
                self.mainEngine.writeWarning(u'净值{}低于止损线1.05比例{}，濒临强制止损'.format(self.balance,self.lossLimit))

            # 当前资金 低于 止损线，存在持仓
            if self.balance < self.lossLimit and self.balance != self.available:

                # 第一次发出
                if self.lastEventTime is None:
                    self.writeRiskLog(u'净值低于止损线，强制止损')
                    self.mainEngine.writeCritical(u'净值低于止损线，强制止损')
                    self.lastEventTime = datetime.now()
                    event = Event(type_=EVENT_ACCOUNT_LOSS)
                    event.dict_['data'] = self.balance
                    self.eventEngine.put(event)

                # 判断是否超时
                else:
                    if (datetime.now() - self.lastEventTime).seconds > 10:
                        self.writeRiskLog(u'净值低于止损线，，超时10秒未生效，强制止损')
                        self.writeRiskLog(u'净值低于止损线，，超时10秒未生效，强制止损')
                        self.lastEventTime = datetime.now()
                        event = Event(type_=EVENT_ACCOUNT_LOSS)
                        event.dict_['data'] = self.balance
                        self.eventEngine.put(event)


    def getAccountInfo(self):
        """获取当前账号的权益、可用资金、当前仓位比例, 投资仓位比例上限
        仅支持1个账号哦。
        """
        return self.balance, self.available, self.percent, self.percentLimit

    # ----------------------------------------------------------------------
    def writeRiskLog(self, content):
        """快速发出日志事件"""
        # 发出报警提示音

        if platform.uname() == 'Windows':
            import winsound
            winsound.PlaySound("SystemHand", winsound.SND_ASYNC) 
        
        # 发出日志事件
        log = VtLogData()
        log.logContent = content
        log.gatewayName = self.name
        event = Event(type_=EVENT_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)      
    
    # ----------------------------------------------------------------------
    def checkRisk(self, orderReq):
        """检查风险"""
        # 如果没有启动风控检查，则直接返回成功
        if not self.active:
            return True
        
        # 检查委托数量
        if orderReq.volume > self.orderSizeLimit:
            self.writeRiskLog(u'单笔委托数量%s，超过限制%s' 
                              %(orderReq.volume, self.orderSizeLimit))

            self.mainEngine.writeWarning(u'单笔委托数量%s，超过限制%s'
                              %(orderReq.volume, self.orderSizeLimit))
            return False
        
        # 检查成交合约量
        if self.tradeCount >= self.tradeLimit:
            self.writeRiskLog(u'今日总成交合约数量%s，超过限制%s' 
                              %(self.tradeCount, self.tradeLimit))
            self.mainEngine.writeWarning(u'今日总成交合约数量%s，超过限制%s'
                              %(self.tradeCount, self.tradeLimit))
            return False
        
        # 检查流控
        if self.orderFlowCount >= self.orderFlowLimit:
            self.writeRiskLog(u'委托流数量%s，超过限制每%s秒%s' 
                              %(self.orderFlowCount, self.orderFlowClear, self.orderFlowLimit))
            self.mainEngine.writeWarning(u'委托流数量%s，超过限制每%s秒%s'
                              %(self.orderFlowCount, self.orderFlowClear, self.orderFlowLimit))
            return False
        
        # 检查总活动合约
        workingOrderCount = len(self.mainEngine.getAllWorkingOrders())
        if workingOrderCount >= self.workingOrderLimit:
            self.writeRiskLog(u'当前活动委托数量%s，超过限制%s'
                              %(workingOrderCount, self.workingOrderLimit))
            self.mainEngine.writeWarning(u'当前活动委托数量%s，超过限制%s'
                              %(workingOrderCount, self.workingOrderLimit))
            return False


        # 检查仓位 add by Incense 20160728
        if orderReq.offset == OFFSET_OPEN:
            if self.percent > self.percentLimit:
                self.writeRiskLog(u'当前仓位:{0},超过限制:{1}，不允许开仓'.format(self.percent, self.percentLimit))

                self.mainEngine.writeWarning(u'当前仓位:{0},超过限制:{1}，不允许开仓'.format(self.percent, self.percentLimit))
                return False

        # 对于通过风控的委托，增加流控计数
        self.orderFlowCount += 1
        
        return True    
    
    # ----------------------------------------------------------------------
    def clearOrderFlowCount(self):
        """清空流控计数"""
        self.orderFlowCount = 0
        self.writeRiskLog(u'清空流控计数')
        
    # ----------------------------------------------------------------------
    def clearTradeCount(self):
        """清空成交数量计数"""
        self.tradeCount = 0
        self.writeRiskLog(u'清空总成交计数')

    # ----------------------------------------------------------------------
    def setOrderFlowLimit(self, n):
        """设置流控限制"""
        self.orderFlowLimit = n
        
    # ----------------------------------------------------------------------
    def setOrderFlowClear(self, n):
        """设置流控清空时间"""
        self.orderFlowClear = n
        
    # ----------------------------------------------------------------------
    def setOrderSizeLimit(self, n):
        """设置委托最大限制"""
        self.orderSizeLimit = n
        
    # ----------------------------------------------------------------------
    def setTradeLimit(self, n):
        """设置成交限制"""
        self.tradeLimit = n
        
    # ----------------------------------------------------------------------
    def setWorkingOrderLimit(self, n):
        """设置活动合约限制"""
        self.workingOrderLimit = n

    # ----------------------------------------------------------------------
    def setAccountPercentLimit(self,n):
        """设置最大开仓比例"""
        self.percentLimit = n

    # ----------------------------------------------------------------------
    def setLossLimit(self, n):
        """设置最大止损比例"""
        self.lossLimit = n

    # ----------------------------------------------------------------------
    def switchEngineStatus(self):
        """开关风控引擎"""
        self.active = not self.active
        
        if self.active:
            self.writeRiskLog(u'风险管理功能启动')
        else:
            self.writeRiskLog(u'风险管理功能停止')
