# encoding: UTF-8

'''
vn.huobi的gateway接入
'''


import os
import json
from datetime import datetime
from copy import copy
from threading import Condition
from Queue import Queue
from threading import Thread

import vnhuobi
from vtGateway import *


########################################################################
class HuobiGateway(VtGateway):
    """火币接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='HUOBI'):
        """Constructor"""
        super(HuobiGateway, self).__init__(eventEngine, gatewayName)
        
        self.market = 'cny'
        
        self.tradeApi = HuobiTradeApi(self)
        self.dataApi = HuobiDataApi(self)
        
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
        fileName = self.gatewayName + '_connect.json'
        path = os.path.abspath(os.path.dirname(__file__))
        fileName = os.path.join(path, fileName)
        
        try:
            f = file(fileName)
        except IOError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'读取连接配置出错，请检查'
            self.onLog(log)
            return
        
        # 解析json文件
        setting = json.load(f)
        try:
            accessKey = str(setting['accessKey'])
            secretKey = str(setting['secretKey'])
            interval = setting['interval']
            market = setting['market']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 初始化接口
        self.tradeApi.connect(accessKey, secretKey)
        self.writeLog(u'交易接口初始化成功')
        
        self.dataApi.connect(interval)
        self.writeLog(u'行情接口初始化成功')
        
        # 启动查询
        #self.initQuery()
        #self.startQuery()
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.onLog(log)        
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情，自动订阅全部行情，无需实现"""
        pass
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        pass
        
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        pass
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        pass
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        pass
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.tradeApi.exit()
        self.dataApi.exit()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryAccount]
            
            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 2         # 查询触发点
            self.qryNextFunction = 0    # 上次运行的查询函数索引
            
            self.startQuery()  
    
    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.qryCount += 1
        
        if self.qryCount > self.qryTrigger:
            # 清空倒计时
            self.qryCount = 0
            
            # 执行查询函数
            function = self.qryFunctionList[self.qryNextFunction]
            function()
            
            # 计算下次查询函数的索引，如果超过了列表长度，则重新设为0
            self.qryNextFunction += 1
            if self.qryNextFunction == len(self.qryFunctionList):
                self.qryNextFunction = 0
                
    #----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)
    
    #----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled
    

########################################################################
class HuobiTradeApi(vnhuobi.TradeApi):
    """交易接口"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(HuobiTradeApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
    
    #----------------------------------------------------------------------
    def onError(self, error, reqID):
        """错误推送"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorMsg = str(error)
        err.errorTime = datetime.now().strftime('%H:%M:%S')
        self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onGetAccountInfo(self, data, reqID):
        """查询账户回调"""
        # 推送账户数据
        account = VtAccountData()
        account.gatewayName = self.gatewayName
        account.balance = data['net_asset']
        self.gateway.onAccount(account)
        
        # 推送持仓数据
        if self.market == 'cny':
            posCny = VtPositionData()
            posCny.gatewayName = self.gatewayName
            posCny.position = data['available_cny_display']
            posCny.frozen = data['frozen_cny_display']
            self.gateway.onPosition(posCny)
            
            posLtc = VtPositionData()
            posLtc.gatewayName = self.gatewayName
            posLtc.position = data['available_ltc_display']
            posLtc.frozen = data['frozen_ltc_display']
            self.gateway.onPosition(posLtc)
        else:
            posUsd = VtPositionData()
            posUsd.gatewayName = self.gatewayName
            posUsd.position = data['available_usd_display']
            posUsd.frozen = data['frozen_usd_display']
            self.gateway.onPosition(posUsd)     
            
        posBtc = VtPositionData()
        posBtc.gatewayName = self.gatewayName
        posBtc.position = data['available_btc_display']
        posBtc.frozen = data['frozen_btc_display']
        self.gateway.onPosition(posBtc)        
    
    #----------------------------------------------------------------------
    def onGetOrders(self, data, reqID):
        """查询委托回调"""
        for d in data:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            
            order
        
    #----------------------------------------------------------------------
    def onOrderInfo(self, data, reqID):
        """委托详情回调"""
        print data

    #----------------------------------------------------------------------
    def onBuy(self, data, reqID):
        """买入回调"""
        print data
        
    #----------------------------------------------------------------------
    def onSell(self, data, reqID):
        """卖出回调"""
        print data    
        
    #----------------------------------------------------------------------
    def onBuyMarket(self, data, reqID):
        """市价买入回调"""
        print data
        
    #----------------------------------------------------------------------
    def onSellMarket(self, data, reqID):
        """市价卖出回调"""
        print data        
        
    #----------------------------------------------------------------------
    def onCancelOrder(self, data, reqID):
        """撤单回调"""
        print data
    
    #----------------------------------------------------------------------
    def onGetNewDealOrders(self, data, reqID):
        """查询最新成交回调"""
        print data    
        
    #----------------------------------------------------------------------
    def onGetOrderIdByTradeId(self, data, reqID):
        """通过成交编号查询委托编号回调"""
        print data    
        
    #----------------------------------------------------------------------
    def onWithdrawCoin(self, data, reqID):
        """提币回调"""
        print data
        
    #----------------------------------------------------------------------
    def onCancelWithdrawCoin(self, data, reqID):
        """取消提币回调"""
        print data      
        
    #----------------------------------------------------------------------
    def onGetWithdrawCoinResult(self, data, reqID):
        """查询提币结果回调"""
        print data           
        
    #----------------------------------------------------------------------
    def onTransfer(self, data, reqID):
        """转账回调"""
        print data
        
    #----------------------------------------------------------------------
    def onLoan(self, data, reqID):
        """申请杠杆回调"""
        print data      
        
    #----------------------------------------------------------------------
    def onRepayment(self, data, reqID):
        """归还杠杆回调"""
        print data    
    
    #----------------------------------------------------------------------
    def onLoanAvailable(self, data, reqID):
        """查询杠杆额度回调"""
        print data      
        
    #----------------------------------------------------------------------
    def onGetLoans(self, data, reqID):
        """查询杠杆列表"""
        print data        
    
    #----------------------------------------------------------------------
    def connect(self, accessKey, secretKey, market):
        """连接服务器"""
        self.market = market
        
        self.init(accessKey, secretKey)
        
        
########################################################################
class HuobiDataApi(vnhuobi.DataApi):
    """行情接口"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(HuobiDataApi, self).__init__()
        
        self.gateway = gateway
    
    #----------------------------------------------------------------------
    def onTick(self, data):
        """实时成交推送"""
        print data
        
    #----------------------------------------------------------------------
    def onQuote(self, data):
        """实时报价推送"""
        print data    
    
    #----------------------------------------------------------------------
    def onDepth(self, data):
        """实时深度推送"""
        print data        
        
    #----------------------------------------------------------------------
    def connect(self, interval):
        """连接服务器"""
        self.init(interval)
    
    
    
    
    
    


