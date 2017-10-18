# encoding: UTF-8

'''
vn.sec的gateway接入
'''

import os
import json
import time
from copy import copy

from vnpy.api.sec import MdApi, TdApi, DATA_TYPE
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath


# 以下为一些VT类型和SEC类型的映射字典
# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = DATA_TYPE.DFITCSEC_SOP_LimitPrice
priceTypeMap[PRICETYPE_MARKETPRICE] = DATA_TYPE.DFITCSEC_SOP_LastPrice
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = DATA_TYPE.DFITCSEC_ED_Buy
directionMap[DIRECTION_SHORT] = DATA_TYPE.DFITCSEC_ED_Sell
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {}
offsetMap[OFFSET_OPEN] = DATA_TYPE.DFITCSEC_OCF_Open
offsetMap[OFFSET_CLOSE] = DATA_TYPE.DFITCSEC_OCF_Close
offsetMapReverse = {v:k for k,v in offsetMap.items()}


# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_SSE] = DATA_TYPE.DFITCSEC_EI_SH
exchangeMap[EXCHANGE_SZSE] = DATA_TYPE.DFITCSEC_EI_SZ
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}


#----------------------------------------------------------------------
def print_dict(d):
    """"""
    for k, v in d.items():
        print '%s:%s' %(k, v)
    

########################################################################
class SecGateway(VtGateway):
    """SEC接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='SEC'):
        """Constructor"""
        super(SecGateway, self).__init__(eventEngine, gatewayName)
        
        self.mdApi = SecMdApi(self)     # 行情API
        self.tdApi = SecTdApi(self)     # 交易API
        
        self.mdConnected = False        # 行情API连接状态，登录完成后为True
        self.tdConnected = False        # 交易API连接状态
        
        self.qryEnabled = False         # 是否要启动循环查询
        
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)             
        
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""       
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
            accountID = str(setting['accountID'])
            password = str(setting['password'])
            tdAddress = str(setting['tdAddress'])
            mdAddress = str(setting['mdAddress'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 创建行情和交易接口对象
        self.mdApi.connect(accountID, password, mdAddress)
        self.tdApi.connect(accountID, password, tdAddress)
        
        # 初始化并启动查询
        self.initQuery()
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        self.mdApi.subscribe(subscribeReq)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.tdApi.sendOrder(orderReq)
        
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.tdApi.cancelOrder(cancelOrderReq)
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        self.tdApi.qryAccount()
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.tdApi.qryPosition()
            
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        if self.mdConnected:
            self.mdApi.close()
        if self.tdConnected:
            self.tdApi.close()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryAccount, self.qryPosition]
            
            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 1         # 查询触发点
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
class SecMdApi(MdApi):
    """SEC行情API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(SecMdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.subscribedSymbols = set()      # 已订阅合约代码        
        
        self.accountID = EMPTY_STRING       # 账号
        self.password = EMPTY_STRING        # 密码
        self.address = EMPTY_STRING         # 服务器地址
        
    #----------------------------------------------------------------------
    def connect(self, accountID, password, address):
        """初始化连接"""
        self.accountID = accountID             # 账号
        self.password = password            # 密码
        self.address = address              # 服务器地址
        
        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            path = getTempPath(self.gatewayName)
            self.createDFITCMdApi(path)

            # 初始化连接，成功会调用onFrontConnected
            self.init(self.address)
            
        # 若已经连接但尚未登录，则进行登录
        else:
            if not self.loginStatus:
                self.login()
        
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅合约"""
        # 这里的设计是，如果尚未登录就调用了订阅方法
        # 则先保存订阅请求，登录完成后会自动订阅
        if self.loginStatus:
            self.reqID += 1
            symbol = str(exchangeMap[subscribeReq.exchange] + subscribeReq.symbol)
            self.subscribeSOPMarketData(symbol, self.reqID)
            
        self.subscribedSymbols.add(subscribeReq)   
        
    #----------------------------------------------------------------------
    def login(self):
        """登录"""
        # 如果填入了用户名密码等，则登录
        if self.accountID and self.password:
            self.reqID += 1
            req = {}
            req['accountID'] = self.accountID
            req['password'] = self.password
            req['requestID'] = self.reqID
            self.reqSOPUserLogin(req)    
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()
    
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        self.connectionStatus = True
    
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'行情服务器连接成功'
        self.gateway.onLog(log)
        self.login()
    
    #----------------------------------------------------------------------
    def onFrontDisconnected(self, reason):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.mdConnected = False
    
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'行情服务器连接断开，原因：%s' %reason
        self.gateway.onLog(log) 
    
    #----------------------------------------------------------------------
    def onRtnNotice(self, data):
        """通知推送"""
        msg = data['noticeMsg']
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'行情消息通知：%s' %msg
        self.gateway.onLog(log)         
    
    #----------------------------------------------------------------------
    def onRspError(self, error):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['errorID']
        err.errorMsg = error['errorMsg'].decode('gbk')
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspStockUserLogin(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockUserLogout(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPUserLogin(self, data, error):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if not error:
            self.loginStatus = True
            self.gateway.mdConnected = True

            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'行情服务器登录完成'
            self.gateway.onLog(log)

            # 重新订阅之前订阅的合约
            for subscribeReq in self.subscribedSymbols:
                self.subscribe(subscribeReq)
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['errorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspSOPUserLogout(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLUserLogin(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLUserLogout(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockSubMarketData(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockUnSubMarketData(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPSubMarketData(self, data, error):
        """订阅期权行情回报"""
        if error:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['errorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspSOPUnSubMarketData(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onStockMarketData(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onSOPMarketData(self, data):
        """期权行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
    
        tick.symbol = data['securityID']
        tick.exchange = exchangeMapReverse.get(data['exchangeID'], u'未知')
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
    
        tick.lastPrice = data['latestPrice']
        tick.volume = data['tradeQty']
        tick.openInterest = data['positionQty']
        tick.time = data['updateTime']
        tick.date = data['tradingDay']
    
        tick.openPrice = data['openPrice']
        tick.highPrice = data['highestPrice']
        tick.lowPrice = data['lowestPrice']
        tick.preClosePrice = data['preClosePrice']
    
        tick.upperLimit = data['upperLimitPrice']
        tick.lowerLimit = data['lowerLimitPrice']
    
        tick.bidPrice1 = data['bidPrice1']
        tick.bidPrice2 = data['bidPrice2']
        tick.bidPrice3 = data['bidPrice3']
        tick.bidPrice4 = data['bidPrice4']
        tick.bidPrice5 = data['bidPrice5']
        
        tick.askPrice1 = data['askPrice1']
        tick.askPrice2 = data['askPrice2']
        tick.askPrice3 = data['askPrice3']
        tick.askPrice4 = data['askPrice4']
        tick.askPrice5 = data['askPrice5']        
        
        tick.bidVolume1 = data['bidQty1']
        tick.bidVolume2 = data['bidQty2']
        tick.bidVolume3 = data['bidQty3']
        tick.bidVolume4 = data['bidQty4']
        tick.bidVolume5 = data['bidQty5']
        
        tick.askVolume1 = data['askQty1']
        tick.askVolume2 = data['askQty2']
        tick.askVolume3 = data['askQty3']
        tick.askVolume4 = data['askQty4']
        tick.askVolume5 = data['askQty5']
        
        self.gateway.onTick(tick)
    
    #----------------------------------------------------------------------
    def onRspStockAvailableQuot(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSopAvailableQuot(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspUserMDPasswordUpdate(self, data, error):
        """"""
        pass
    
    

########################################################################
class SecTdApi(TdApi):
    """SEC交易API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(SecTdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        self.localID = EMPTY_INT            # 订单编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.accountID = EMPTY_STRING       # 账号
        self.password = EMPTY_STRING        # 密码
        self.address = EMPTY_STRING         # 服务器地址
        
        self.orderDict = {}                 # 缓存委托数据的字典
    
    #----------------------------------------------------------------------
    def connect(self, accountID, password, address):
        """初始化连接"""
        self.accountID = accountID          # 账号
        self.password = password            # 密码
        self.address = address              # 服务器地址
        
        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            path = getTempPath(self.gatewayName)
            self.createDFITCSECTraderApi(path)
            
            # 初始化连接，成功会调用onFrontConnected
            self.init(self.address)
            
            # 要求重传所有委托和成交推送
            self.subscribePrivateTopic(2)            
            
        # 若已经连接但尚未登录，则进行登录
        else:
            if not self.loginStatus:
                self.login()    
    
    #----------------------------------------------------------------------
    def login(self):
        """连接服务器"""
        # 如果填入了用户名密码等，则登录
        if self.accountID and self.password:
            self.reqID += 1
            req = {}
            req['accountID'] = self.accountID
            req['password'] = self.password
            req['requestID'] = self.reqID
            self.reqSOPUserLogin(req)  
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户"""
        self.reqID += 1
        req = {}
        req['requestID'] = self.reqID
        req['accountID'] = self.accountID
        self.reqSOPQryCapitalAccountInfo(req)
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.reqID += 1
        req = {}
        req['requestID'] = self.reqID
        req['accountID'] = self.accountID
        self.reqSOPQryPosition(req)
    
    #----------------------------------------------------------------------
    def qryContracts(self):
        """查询合约"""
        # 查询期货合约代码
        self.reqID += 1
        req = {}
        req['requestID'] = self.reqID
        req['accountID'] = self.accountID
        self.reqSOPQryContactInfo(req)            
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        self.reqID += 1
        self.localID += 1

        req = {}
        req['securityID'] = orderReq.symbol
        req['exchangeID'] = exchangeMap.get(orderReq.exchange, '')
        req['entrustPrice'] = orderReq.price
        req['entrustQty'] = orderReq.volume
        
        # 下面如果由于传入的类型本接口不支持，则会返回空字符串
        try:
            req['orderType'] = priceTypeMap[orderReq.priceType]
            req['entrustDirection'] = directionMap[orderReq.direction]
            req['openCloseFlag'] = offsetMap[orderReq.offset]
        except KeyError:
            return ''
            
        req['localOrderID'] = self.localID
        req['accountID'] = self.accountID
        req['requestID'] = self.reqID
        
        self.reqSOPEntrustOrder(req)
        
        # 缓存委托信息
        orderID = str(self.localID)
        vtOrderID = '.'.join([self.gatewayName, orderID])
        
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = orderReq.symbol
        order.exchange = orderReq.exchange
        order.vtSymbol = '.'.join([order.symbol, order.exchange])
        order.orderID = orderID
        order.vtOrderID = vtOrderID
        order.price = orderReq.price
        order.totalVolume = orderReq.volume
        order.direction = orderReq.direction
        order.offset = orderReq.offset
        
        self.orderDict[str(self.localID)] = order
        
        # 返回订单号
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.reqID += 1

        req = {}
        req['localOrderID'] = int(cancelOrderReq.orderID)
        req['accountID'] = self.accountID
        req['requestID'] = self.reqID
        
        self.reqSOPWithdrawOrder(req)
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()
    
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        self.connectionStatus = True
    
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'交易服务器连接成功'
        self.gateway.onLog(log)
    
        self.login()
    
    #----------------------------------------------------------------------
    def onFrontDisconnected(self, reason):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.tdConnected = False
    
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'交易服务器连接断开，原因%s' %reason
        self.gateway.onLog(log) 
    
    #----------------------------------------------------------------------
    def onRtnNotice(self, data):
        """通知推送"""
        msg = data['noticeMsg']
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'交易消息通知：%s' %msg
        self.gateway.onLog(log)   
        
    #----------------------------------------------------------------------
    def onRspError(self, error):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['errorID']
        err.errorMsg = error['errorMsg'].decode('gbk')
        self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onRspStockUserLogin(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockUserLogout(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockUserPasswordUpdate(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockEntrustOrder(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockWithdrawOrder(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryEntrustOrder(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryRealTimeTrade(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQrySerialTrade(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryPosition(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryCapitalAccountInfo(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryAccountInfo(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryShareholderInfo(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockTransferFunds(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockEntrustBatchOrder(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockWithdrawBatchOrder(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockCalcAbleEntrustQty(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockCalcAblePurchaseETFQty(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryFreezeFundsDetail(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryFreezeStockDetail(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryTransferStockDetail(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryTransferFundsDetail(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryStockInfo(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryStockStaticInfo(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspStockQryTradeTime(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onStockEntrustOrderRtn(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onStockTradeRtn(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onStockWithdrawOrderRtn(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPUserLogin(self, data, error):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if not error:
            self.loginStatus = True
            self.gateway.tdConnected = True
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易服务器登录完成'
            self.gateway.onLog(log)
            
            self.qryContracts()

        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['errorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspSOPUserLogout(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPUserPasswordUpdate(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPEntrustOrder(self, data, error):
        """发单错误"""
        if error:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            order.orderID = error['localOrderID']
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            order.status = STATUS_REJECTED      
            self.gateway.onOrder(order)

            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['errorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspSOPGroupSplit(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryGroupPosition(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPLockOUnLockStock(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPWithdrawOrder(self, data, error):
        """撤单错误"""
        if error:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['errorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspSOPQryEntrustOrder(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQrySerialTrade(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryPosition(self, data, error, flag):
        """持仓查询回报"""
        if not data:
            return
        
        pos = VtPositionData()
        pos.gatewayName = self.gatewayName

        # 保存代码
        pos.symbol = data['securityOptionID']
        pos.exchange = exchangeMap.get(data['exchangeID'], EXCHANGE_UNKNOWN)
        pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])
        pos.direction = directionMapReverse.get(data['entrustDirection'], DIRECTION_UNKNOWN)
        pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
        pos.position = data['totalQty']
        pos.price = data['openAvgPrice']
        
        self.gateway.onPosition(pos)
    
    #----------------------------------------------------------------------
    def onRspSOPQryCollateralPosition(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryCapitalAccountInfo(self, data, error):
        """资金账户查询回报"""
        if not data:
            return
        
        account = VtAccountData()
        account.gatewayName = self.gatewayName
    
        # 账户代码
        account.accountID = data['accountID']
        account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
    
        # 数值相关
        account.available = data['availableFunds']
        account.margin = data['usedDeposit']
        account.balance = data['totalFunds'] 
        account.marketValue = data['totalMarket']
        
        # 推送
        self.gateway.onAccount(account)
    
    #----------------------------------------------------------------------
    def onRspSOPQryAccountInfo(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryShareholderInfo(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPCalcAbleEntrustQty(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryAbleLockStock(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryContactInfo(self, data, error, flag):
        """期权合约查询回报"""
        if not data:
            return
        
        contract = VtContractData()
        contract.gatewayName = self.gatewayName

        contract.symbol = data['securityOptionID']
        contract.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_UNKNOWN)
        contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
        
        contract.name = data['contractName'].decode('GBK')
        
        # 合约数值
        contract.size = data['contactUnit']
        contract.priceTick = data['miniPriceChange']
        
        contract.strikePrice = data['execPrice']
        
        contract.underlyingSymbol = data['securityID']
        contract.expiryDate = data['endTradingDay']
        
        # 合约类型
        contract.productClass = PRODUCT_OPTION
        
        # 期权类型
        if data['optType'] == DATA_TYPE.DFITCSEC_OT_CALL:
            contract.optionType = OPTION_CALL
        elif data['optType'] == DATA_TYPE.DFITCSEC_OT_PUT:
            contract.optionType = OPTION_PUT
        
        # 推送
        self.gateway.onContract(contract)
        
        if flag:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易合约信息获取完成'
            self.gateway.onLog(log)
    
    #----------------------------------------------------------------------
    def onRspSOPExectueOrder(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryExecAssiInfo(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryTradeTime(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryExchangeInfo(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryCommission(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryDeposit(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPQryContractObjectInfo(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onSOPEntrustOrderRtn(self, data):
        """报单回报"""
        # 更新最大报单编号
        newLocalID = data['localOrderID']
        self.localID = max(self.localID, newLocalID)
        
        # 获取报单数据对象
        if newLocalID in self.orderDict:
            order = self.orderDict[newLocalID]
        else:
            order = VtOrderData()
            self.orderDict[newLocalID] = order
            order.gatewayName = self.gatewayName
        
            # 保存后续不会变化的数据
            order.symbol = data['securityID']
            order.exchange = exchangeMapReverse[data['exchangeID']]
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            order.orderID = str(newLocalID)
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.direction = directionMapReverse.get(data['entrustDirection'], DIRECTION_UNKNOWN)
            order.offset = offsetMapReverse.get(data['openCloseFlag'], OFFSET_UNKNOWN)

            # 价格、报单量等数值
            order.price = data['entrustPrice']
            order.totalVolume = data['entrustQty']
            order.orderTime = data['entrustTime']
        
        # 确定委托状态
        if order.totalVolume == order.tradedVolume:
            order.status = STATUS_ALLTRADED
        elif order.tradedVolume > 0:
            order.status = STATUS_PARTTRADED
        else:
            order.status = STATUS_NOTTRADED        
        
        # 推送
        self.gateway.onOrder(copy(order))
    
    #----------------------------------------------------------------------
    def onSOPTradeRtn(self, data):
        # 更新成交信息
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        # 保存代码和报单号
        trade.symbol = data['securityID']
        trade.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_UNKNOWN)
        trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
        
        trade.tradeID = data['tradeID']
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
        
        trade.orderID = str(data['localOrderID'])
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])

        trade.direction = directionMapReverse.get(data['entrustDirection'], DIRECTION_UNKNOWN)
        trade.offset = offsetMapReverse.get(data['openCloseFlag'], OFFSET_UNKNOWN)
            
        trade.price = data['tradePrice']
        trade.volume = data['tradeQty']
        trade.tradeTime = data['tradeTime']
        
        # 推送
        self.gateway.onTrade(trade)
        
        # 获取报单数据对象
        localID = data['localOrderID']
        order = self.orderDict.get(localID, None)
        if not order:
            return
        
        order.tradedVolume += trade.volume
        order.tradedVolume = min(order.totalVolume, order.tradedVolume) # 防止成交数量超过总数量
        
        # 确定委托状态
        if order.totalVolume == order.tradedVolume:
            order.status = STATUS_ALLTRADED
        elif order.tradedVolume > 0:
            order.status = STATUS_PARTTRADED        
        
        self.gateway.onOrder(copy(order))   
    
    #----------------------------------------------------------------------
    def onSOPWithdrawOrderRtn(self, data):
        """撤单推送"""
        # 更新最大报单编号
        newLocalID = data['localOrderID']
        self.localID = max(self.localID, int(newLocalID))
        
        # 获取报单数据对象
        if newLocalID in self.orderDict:
            order = self.orderDict[newLocalID]
        else:
            order = VtOrderData()
            self.orderDict[newLocalID] = order
            order.gatewayName = self.gatewayName
        
            # 保存后续不会变化的数据
            order.symbol = data['securityID']
            order.exchange = exchangeMapReverse[data['exchangeID']]
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            order.orderID = str(newLocalID)
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.direction = directionMapReverse.get(data['entrustDirection'], DIRECTION_UNKNOWN)
            order.offset = offsetMapReverse.get(data['openCloseFlag'], OFFSET_UNKNOWN)

            # 价格、报单量等数值
            order.price = data['entrustPrice']
            order.tradedVolume = data['tradeQty']
            order.totalVolume = data['tradeQty'] + data['withdrawQty']
        
        if data['withdrawQty']:
            order.status = STATUS_CANCELLED
        
        # 推送
        self.gateway.onOrder(copy(order))
    
    #----------------------------------------------------------------------
    def onRspFASLUserLogin(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLUserLogout(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryAbleFinInfo(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryAbleSloInfo(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLTransferCollateral(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLDirectRepayment(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLRepayStockTransfer(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLEntrustCrdtOrder(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLEntrustOrder(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLCalcAbleEntrustCrdtQty(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryCrdtFunds(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryCrdtContract(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryCrdtConChangeInfo(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLTransferFunds(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryAccountInfo(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryCapitalAccountInfo(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryShareholderInfo(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryPosition(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryEntrustOrder(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQrySerialTrade(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryRealTimeTrade(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryFreezeFundsDetail(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryFreezeStockDetail(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryTransferFundsDetail(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLWithdrawOrder(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQrySystemTime(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryTransferredContract(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLDesirableFundsOut(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryGuaranteedContract(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFASLQryUnderlyingContract(self, data, error, flag):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onFASLEntrustOrderRtn(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onFASLTradeRtn(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onFASLWithdrawOrderRtn(self, data):
        """"""
        pass



    