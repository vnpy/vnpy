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
# 期权价格类型映射
optionPriceTypeMap = {}
optionPriceTypeMap[PRICETYPE_LIMITPRICE] = DATA_TYPE.DFITCSEC_SOP_LimitPrice
optionPriceTypeMap[PRICETYPE_MARKETPRICE] = DATA_TYPE.DFITCSEC_SOP_LastPrice
optionPriceTypeMapReverse = {v: k for k, v in optionPriceTypeMap.items()} 

# 股票价格类型映射 
stockPriceTypeMap = {}
stockPriceTypeMap[PRICETYPE_LIMITPRICE] = DATA_TYPE.DFITCSEC_OT_LimitPrice
stockPriceTypeMap[PRICETYPE_MARKETPRICE] = DATA_TYPE.DFITCSEC_OT_SHBESTFRTradeLeftWithdraw
stockPriceTypeMapReverse = {v: k for k, v in stockPriceTypeMap.items()} 

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
    print '-' * 30
    l = d.keys()
    l.sort()
    for k in l:
        print '%s:%s' %(k, d[k])
    

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
        self.accountID = accountID          # 账号
        self.password = password            # 密码
        self.address = address              # 服务器地址
        
        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            path = getTempPath(self.gatewayName)
            self.createDFITCMdApi(path)

            # 初始化连接，成功会调用onFrontConnected
            self.init(self.address)
        
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅合约"""
        if self.loginStatus:
            self.reqID += 1
            
            if checkOptionSymbol(subscribeReq.symbol):
                symbol = str(exchangeMap[subscribeReq.exchange] + subscribeReq.symbol)
                self.subscribeSOPMarketData(symbol, self.reqID)
            else:
                symbol = str(exchangeMap[subscribeReq.exchange] + subscribeReq.symbol)
                self.subscribeStockMarketData(symbol, self.reqID)
            
        self.subscribedSymbols.add(subscribeReq)   
        
    #----------------------------------------------------------------------
    def login(self):
        """登录"""
        if self.accountID and self.password:
            # 登录期权
            self.reqID += 1
            req = {}
            req['accountID'] = self.accountID
            req['password'] = self.password
            req['requestID'] = self.reqID
            self.reqSOPUserLogin(req)    
            
            # 登录股票
            self.reqID += 1
            req['requestID'] = self.reqID
            self.reqStockUserLogin(req)                
    
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
        """股票登录回报"""
        # 如果登录成功，推送日志信息
        if not error:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'股票行情服务器登录完成'
            self.gateway.onLog(log)
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['errorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspStockUserLogout(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSOPUserLogin(self, data, error):
        """期权登录回报"""
        # 如果登录成功，推送日志信息
        if not error:
            self.loginStatus = True
            self.gateway.mdConnected = True

            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'期权行情服务器登录完成'
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
        """股票行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
    
        tick.symbol = data['securityID']
        tick.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_SSE)
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
    
        tick.lastPrice = data['latestPrice']
        tick.volume = data['tradeQty'] 
        tick.time = data['updateTime']
        tick.date = str(data['tradingDay'])
    
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
    def onSOPMarketData(self, data):
        """期权行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
    
        tick.symbol = data['securityID']
        tick.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_SSE)
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
    
        tick.lastPrice = data['latestPrice']
        tick.volume = data['tradeQty']
        tick.openInterest = data['positionQty']
        tick.time = data['updateTime']
        tick.date = str(data['tradingDay'])
    
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
        self.optionLoginStatus = False      # 期权登录状态
        self.stockLoginStatus = False       # 股票登录状态
        
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
            
            self.reqID += 1
            req['requestID'] = self.reqID
            self.reqStockUserLogin(req)
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户"""
        self.reqID += 1
        req = {}
        req['requestID'] = self.reqID
        req['accountID'] = self.accountID
        self.reqSOPQryCapitalAccountInfo(req)
        
        self.reqID += 1
        req['FundsQryFlag'] = DATA_TYPE.DFITCSEC_FQF_Extend
        self.reqStockQryCapitalAccountInfo(req)
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.reqID += 1
        req = {}
        req['requestID'] = self.reqID
        req['accountID'] = self.accountID
        self.reqSOPQryPosition(req)
        
        self.reqID += 1
        self.reqStockQryPosition(req)
    
    #----------------------------------------------------------------------
    def qryOptionContracts(self):
        """查询期权合约"""
        self.reqID += 1
        req = {}
        req['requestID'] = self.reqID
        req['accountID'] = self.accountID
        self.reqSOPQryContactInfo(req)       
        
    #----------------------------------------------------------------------
    def qryStockContracts(self):
        """查询股票合约"""
        self.reqID += 1
        req = {}
        req['exchangeID'] = 'SH'
        req['requestID'] = self.reqID
        req['accountID'] = self.accountID
        i = self.reqStockQryStockStaticInfo(req)
        
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
        req['localOrderID'] = self.localID
        req['accountID'] = self.accountID
        req['requestID'] = self.reqID        
        req['entrustDirection'] = directionMap.get(orderReq.direction, '')

        # 期权委托
        if checkOptionSymbol(orderReq.symbol):
            req['orderType'] = optionPriceTypeMap.get(orderReq.priceType, '')            
            req['openCloseFlag'] = offsetMap.get(orderReq.offset, '')
            self.reqSOPEntrustOrder(req)
            product = PRODUCT_OPTION
        # 股票委托
        else:
            req['orderType'] = stockPriceTypeMap.get(orderReq.priceType, '')# 股票只支持限价单
            self.reqStockEntrustOrder(req)
            product = PRODUCT_EQUITY
        
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
        order.productClass = product
        
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
        
        order = self.orderDict.get(cancelOrderReq.orderID, None)
        if not order or order.productClass == PRODUCT_OPTION:
            self.reqSOPWithdrawOrder(req)
        else:
            self.reqStockWithdrawOrder(req)
        
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
        """股票登录回报"""
        # 如果登录成功，推送日志信息
        if not error:
            self.stockLoginStatus = True
            self.gateway.tdConnected = True
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'股票交易服务器登录完成'
            self.gateway.onLog(log)
            
            self.qryStockContracts()
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['errorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
    
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
        """股票发单错误"""
        if error:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            order.orderID = str(error['localOrderID'])
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            order.status = STATUS_REJECTED      
            self.gateway.onOrder(order)

            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['errorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
    
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
        """股票持仓查询回报"""
        if not data or not data['securityID']:
            return
        
        pos = VtPositionData()
        pos.gatewayName = self.gatewayName

        # 保存代码
        pos.symbol = data['securityID']
        pos.exchange = exchangeMap.get(data['exchangeID'], EXCHANGE_UNKNOWN)
        pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])
        pos.direction = DIRECTION_LONG
        pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
        pos.position = data['position']
        pos.price = data['avgPositionPrice']
        
        self.gateway.onPosition(pos)
    
    #----------------------------------------------------------------------
    def onRspStockQryCapitalAccountInfo(self, data, error, flag):
        """股票资金账户查询回报"""
        if not data:
            return
        
        account = VtAccountData()
        account.gatewayName = self.gatewayName
    
        # 账户代码
        account.accountID = data['accountID'] + '_Stock'
        account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
    
        # 数值相关
        account.available = data['availableFunds']
        account.balance = data['totalFunds'] 
        account.marketValue = data['totalMarket']
        
        # 推送
        self.gateway.onAccount(account)
    
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
        """股票合约查询回报"""      
        if not data:
            return
        
        if data['securityID'] == '510050':
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
    
            contract.symbol = data['securityID']
            contract.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_SSE)
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            
            contract.name = data['securityName'].decode('GBK')
            
            # 合约数值
            contract.size = data['tradeUnit']
            contract.priceTick = 0.001          # 50ETF的最小价格变动
            
            # 合约类型
            contract.productClass = PRODUCT_EQUITY
            
            # 推送
            self.gateway.onContract(contract)
        
        if flag:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'股票交易合约信息获取完成'
            self.gateway.onLog(log)
    
    #----------------------------------------------------------------------
    def onRspStockQryTradeTime(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onStockEntrustOrderRtn(self, data):
        """股票报单回报"""
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
            order.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_SSE)
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            order.orderID = str(newLocalID)
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.direction = directionMapReverse.get(data['entrustDirection'], DIRECTION_UNKNOWN)

            # 价格、报单量等数值
            order.price = data['entrustPrice']
            order.totalVolume = data['entrustQty']
            order.orderTime = data['entrustTime']
            
            order.productClass = PRODUCT_EQUITY
        
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
    def onStockTradeRtn(self, data):
        """股票成交推送"""
        # 更新成交信息
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        # 保存代码和报单号
        trade.symbol = data['securityID']
        trade.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_SSE)
        trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
        
        trade.tradeID = data['tradeID']
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
        
        trade.orderID = str(data['localOrderID'])
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])

        trade.direction = directionMapReverse.get(data['entrustDirection'], DIRECTION_UNKNOWN)
            
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
    def onStockWithdrawOrderRtn(self, data):
        """股票撤单推送"""
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
            order.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_SSE)
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            order.orderID = str(newLocalID)
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.direction = directionMapReverse.get(data['entrustDirection'], DIRECTION_UNKNOWN)

            # 价格、报单量等数值
            order.price = data['entrustPrice']
            order.tradedVolume = data['tradeQty']
            order.totalVolume = data['tradeQty'] + data['withdrawQty']
            
            order.productClass = PRODUCT_OPTION
        
        if data['withdrawQty']:
            order.status = STATUS_CANCELLED
        
        # 推送
        self.gateway.onOrder(copy(order))
    
    #----------------------------------------------------------------------
    def onRspSOPUserLogin(self, data, error):
        """期权登录回报"""
        # 如果登录成功，推送日志信息
        if not error:
            self.optionLoginStatus = True
            self.gateway.tdConnected = True
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'期权交易服务器登录完成'
            self.gateway.onLog(log)
            
            self.qryOptionContracts()

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
        """期权发单错误"""
        if error:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            order.orderID = str(error['localOrderID'])
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
        """期权持仓查询回报"""
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
        """期权资金账户查询回报"""
        if not data:
            return
        
        account = VtAccountData()
        account.gatewayName = self.gatewayName
    
        # 账户代码
        account.accountID = data['accountID'] + '_Option'
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
        contract.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_SSE)
        contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
        
        contract.name = data['contractName'].decode('GBK')
        
        # 合约数值
        contract.size = data['contactUnit']
        contract.priceTick = data['miniPriceChange']
        
        contract.strikePrice = data['execPrice']
        
        contract.underlyingSymbol = '-'.join([data['securityID'], str(data['endTradingDay'])[2:-2]])
        contract.expiryDate = str(data['endTradingDay'])
        
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
            log.logContent = u'期权交易合约信息获取完成'
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
        """期权报单回报"""
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
            order.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_SSE)
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            order.orderID = str(newLocalID)
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.direction = directionMapReverse.get(data['entrustDirection'], DIRECTION_UNKNOWN)
            order.offset = offsetMapReverse.get(data['openCloseFlag'], OFFSET_UNKNOWN)

            # 价格、报单量等数值
            order.price = data['entrustPrice']
            order.totalVolume = data['entrustQty']
            order.orderTime = data['entrustTime']
            
            order.productClass = PRODUCT_OPTION
        
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
        """期权成交推送"""
        # 更新成交信息
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        # 保存代码和报单号
        trade.symbol = data['securityID']
        trade.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_SSE)
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
        """期权撤单推送"""
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
            order.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_SSE)
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            order.orderID = str(newLocalID)
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.direction = directionMapReverse.get(data['entrustDirection'], DIRECTION_UNKNOWN)
            order.offset = offsetMapReverse.get(data['openCloseFlag'], OFFSET_UNKNOWN)

            # 价格、报单量等数值
            order.price = data['entrustPrice']
            order.tradedVolume = data['tradeQty']
            order.totalVolume = data['tradeQty'] + data['withdrawQty']
            
            order.productClass = PRODUCT_OPTION
        
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



#----------------------------------------------------------------------
def checkOptionSymbol(symbol):
    """检查是否为期权代码"""
    if len(symbol) > 6:
        return True
    return False
    