# encoding: UTF-8

import os
import json
from datetime import datetime

from vnpy.api.fxcm import FxcmApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtConstant import *
from vnpy.trader.vtFunction import getJsonPath

# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = 'limit'
priceTypeMap[PRICETYPE_MARKETPRICE] = 'market'
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = 'buy'
directionMap[DIRECTION_SHORT] = 'sell'
directionMapReverse = {v: k for k, v in directionMap.items()}


########################################################################
class FxcmGateway(VtGateway):
    """FXCM接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='FXCM'):
        """Constructor"""
        super(FxcmGateway, self).__init__(eventEngine, gatewayName)
        
        self.api = Api(self)     
        
        self.qryEnabled = False         # 是否要启动循环查询
        
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)             
        
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
        try:
            f = file(self.filePath)
        except IOError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'读取连接配置出错，请检查'
            self.onLog(log)
            return
        
        # 解析json文件
        setting = json.load(f)
        try:
            account = str(setting['account'])
            port = int(setting['port'])
            url = str(setting['url'])
            token = str(setting['token'])
            proxy = str(setting['proxy'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 初始化接口
        self.api.init(account, url, port, token, proxy)
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        self.api.subscribe(subscribeReq.symbol)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.api.sendOrder(orderReq)
        
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.api.cancelOrder(cancelOrderReq)
        
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
        self.api.stop()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        pass
    
    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        pass
    
    #----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        pass
    
    #----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        pass
    


########################################################################
class Api(FxcmApi):
    """FXCM的API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(Api, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.accout = ''
        
        self.orderDict = {}     # 缓存委托数据
        
    #----------------------------------------------------------------------
    def onConnect(self):
        """连接回调"""
        self.writeLog(u'服务器连接成功')
        
    #----------------------------------------------------------------------
    def onDisconnect(self):
        """断开回调"""
        self.writeLog(u'服务器连接断开')
        
    #----------------------------------------------------------------------
    def onError(self, error, reqid):
        """错误回调"""
        err = VtErrorData()
        err.gatewayName = self.gatewayNames
        err.errorID = 0
        err.errorTime = datetime.now().strftime('%H:%M:%S')
        err.errorMsg = error
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onGetInstruments(self, data, reqid):
        """查询合约代码回调"""
        for d in data['data']['instrument']:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            
            contract.symbol = d['symbol']
            contract.exchange = EXCHANGE_FXCM
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            
            contract.name = contract.symbol
            contract.productClass = PRODUCT_FOREX
            contract.priceTick = 0.0001
            contract.size = data['order']
            
            self.gateway.onContract(contract)
        
    #----------------------------------------------------------------------
    def onGetTable(self, data, reqid):
        """查询表回调"""
        print data, reqid        
        
    #----------------------------------------------------------------------
    def onSubscribe(self, data, reqid):
        """订阅行情回调"""
        symbol = data['pairs']['symbol']
        self.writeLog(u'%s行情订阅成功' %symbol)
    
    #----------------------------------------------------------------------
    def onUnsubscribe(self, data, reqid):
        """退订行情回调"""
        pass
        
    #----------------------------------------------------------------------
    def onSubscribeModel(self, data, reqid):
        """订阅表回调"""
        pass
    
    #----------------------------------------------------------------------
    def onUnsubscribeModel(self, data, reqid):
        """退订表回调"""
        pass
        
    #----------------------------------------------------------------------
    def onOpenTrade(self, data, reqid):
        """开仓回调"""
        print data, reqid
        
    #----------------------------------------------------------------------
    def onCloseTrade(self, data, reqid):
        """平仓回调"""
        print data, reqid 
        
    #----------------------------------------------------------------------
    def onChangeOrder(self, data, reqid):
        """改单回调"""
        print data, reqid       

    #----------------------------------------------------------------------
    def onDeleteOrder(self, data, reqid):
        """撤单回调"""
        print data, reqid       
    
    #----------------------------------------------------------------------
    def onPriceUpdate(self, data):
        """行情推送"""
        print data
        
    #----------------------------------------------------------------------
    def onModelUpdate(self, data):
        """表推送"""
        print data   
        
    #----------------------------------------------------------------------
    def init(self, account, url, port, token, proxy):
        """初始化"""
        self.account = account
        
        self.connect(url, port, token, proxy)
        
    #----------------------------------------------------------------------
    def writeLog(self, logContent):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = logContent
        self.gateway.onLog(log)
        
    #----------------------------------------------------------------------
    def qryInstruments(self):
        """查询合约"""
        pass
        
    #----------------------------------------------------------------------
    def qryOrders(self):
        """查询委托"""
        pass
        
    #----------------------------------------------------------------------
    def qryTrades(self):
        """查询成交"""
        pass
        
    #----------------------------------------------------------------------
    def sendOrder_(self, orderReq):
        """发送委托"""
        accountID = self.account
        symbol = orderReq.symbol
        
        if orderReq.direction == DIRECTION_LONG:
            isBuy = True
        else:
            isBuy = False
            
        amount = orderReq.volume
        rate = orderReq.price
        
        self.openTrade(accountID, symbol, isBuy, amount, limit, isInPips, 
                      atMarket, orderType, timeInForce)
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤销委托"""
        pass
    
    
#----------------------------------------------------------------------
def getTime(t):
    """把OANDA返回的时间格式转化为简单的时间字符串"""
    return t[11:19]