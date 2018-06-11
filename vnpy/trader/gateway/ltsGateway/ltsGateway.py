# encoding: UTF-8

'''
vn.lts的gateway接入
'''
from __future__ import print_function

import os
import json

from vnpy.api.lts import MdApi, QryApi, TdApi, defineDict
from vnpy.trader.vtFunction import getTempPath, getJsonPath
from vnpy.trader.vtGateway import *


# 以下为一些VT类型和LTS类型的映射字典
# 价格类型映射
priceTypeMap= {}
priceTypeMap[PRICETYPE_LIMITPRICE] = defineDict["SECURITY_FTDC_OPT_LimitPrice"]
priceTypeMap[PRICETYPE_MARKETPRICE] = defineDict["SECURITY_FTDC_OPT_AnyPrice"]
priceTypeMap[PRICETYPE_FAK] = defineDict["SECURITY_FTDC_OPT_BestPrice"]
priceTypeMap[PRICETYPE_FOK] = defineDict["SECURITY_FTDC_OPT_AllLimitPrice"]
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = defineDict["SECURITY_FTDC_D_Buy"]
directionMap[DIRECTION_SHORT] = defineDict["SECURITY_FTDC_D_Sell"]
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {}
offsetMap[OFFSET_OPEN] = defineDict["SECURITY_FTDC_OF_Open"]
offsetMap[OFFSET_CLOSE] = defineDict["SECURITY_FTDC_OF_Close"]
offsetMap[OFFSET_CLOSETODAY] = defineDict["SECURITY_FTDC_OF_CloseToday"]
offsetMap[OFFSET_CLOSEYESTERDAY] = defineDict["SECURITY_FTDC_OF_CloseYesterday"]
offsetMapReverse = {v:k for k,v in offsetMap.items()}

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_SSE] = 'SSE'
exchangeMap[EXCHANGE_SZSE] = 'SZE'
exchangeMap[EXCHANGE_HKEX] = 'HGE'
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 持仓类型映射
posiDirectionMap = {}
posiDirectionMap[DIRECTION_NET] = defineDict["SECURITY_FTDC_PD_Net"]
posiDirectionMap[DIRECTION_LONG] = defineDict["SECURITY_FTDC_PD_Long"]
posiDirectionMap[DIRECTION_SHORT] = defineDict["SECURITY_FTDC_PD_Short"]
posiDirectionMapReverse = {v:k for k,v in posiDirectionMap.items()}


########################################################################################
class LtsGateway(VtGateway):
    """Lts接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='LTS'):
        """Constructor"""
        super(LtsGateway, self).__init__(eventEngine, gatewayName)
        
        self.mdApi = LtsMdApi(self)
        self.tdApi = LtsTdApi(self)
        self.qryApi = LtsQryApi(self)
        
        self.mdConnected = False
        self.tdConnected = False
        self.qryConnected = False
        
        self.qryEnabled = False         # 是否要启动循环查询
        
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)             
    
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json 文件
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
            userID = str(setting['userID'])
            mdPassword = str(setting['mdPassword'])
            tdPassword = str(setting['tdPassword'])
            brokerID = str(setting['brokerID'])
            tdAddress = str(setting['tdAddress'])
            mdAddress = str(setting['mdAddress'])
            qryAddress = str(setting['qryAddress'])
            productInfo = str(setting['productInfo'])
            authCode = str(setting['authCode'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
              
        # 创建行情和交易接口对象
        self.mdApi.connect(userID, mdPassword, brokerID, mdAddress)
        self.tdApi.connect(userID, tdPassword, brokerID, tdAddress, productInfo, authCode)
        self.qryApi.connect(userID, tdPassword, brokerID, qryAddress, productInfo, authCode)
        
        # 初始化并启动查询
        self.initQuery()
        self.startQuery()
    
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
        self.qryApi.qryAccount()
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.qryApi.qryPosition()
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        if self.mdConnected:
            self.mdApi.close()
        if self.tdConnected:
            self.tdApi.close()
        if self.qryConnected:
            self.qryApi.close()        
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryAccount, self.qryPosition]
            
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
class LtsMdApi(MdApi):
    """Lts行情API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(LtsMdApi, self).__init__()
        
        self.gateway = gateway                     #gateway对象
        self.gatewayName = gateway.gatewayName     #gateway对象名称
        
        self.reqID = EMPTY_INT                  # 操作请求编号
        
        self.connectionStatus = False           # 连接状态
        self.loginStatus = False                # 登陆状态
        
        self.subscribedSymbols = set()
        
        self.userID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.brokerID = EMPTY_STRING        # 经纪商代码
        self.address = EMPTY_STRING         # 服务器地址            
    
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
    def onFrontDisconnected(self,n):
        """服务器断开"""
        self.connectionStatus= False
        self.loginStatus = False
        self.gateway.mdConnected = False
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'行情服务器连接断开'
        self.gateway.onLog(log) 
        
    #----------------------------------------------------------------------
    def onHeartBeatWarning(self, n):
        """心跳报警"""
        pass
    
    #----------------------------------------------------------------------
    def onRspError(self,error,n,last):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------        
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
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
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)    
    
    #----------------------------------------------------------------------        
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        # 如果登出成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = False
            self.gateway.tdConnected = False
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'行情服务器登出完成'
            self.gateway.onLog(log)
                
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
            
    #----------------------------------------------------------------------  
    def onRspSubMarketData(self, data, error, n, last):
        """订阅合约回报"""
        # 通常不在乎订阅错误，选择忽略
        pass
        
    #----------------------------------------------------------------------  
    def onRspUnSubMarketData(self, data, error, n, last):
        """退订合约回报"""
        # 同上
        pass  
        
    #----------------------------------------------------------------------  
    def onRtnDepthMarketData(self, data):
        """行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
        
        tick.symbol = data['InstrumentID']
        tick.exchange = exchangeMapReverse.get(data['ExchangeID'], u'未知')
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
        
        tick.lastPrice = data['LastPrice']
        tick.volume = data['Volume']
        tick.openInterest = data['OpenInterest']
        tick.time = '.'.join([data['UpdateTime'], str(data['UpdateMillisec']/100)])
        tick.date = data['TradingDay']
        
        tick.openPrice = data['OpenPrice']
        tick.highPrice = data['HighestPrice']
        tick.lowPrice = data['LowestPrice']
        tick.preClosePrice = data['PreClosePrice']
        
        tick.upperLimit = data['UpperLimitPrice']
        tick.lowerLimit = data['LowerLimitPrice']        
        
        # LTS有5档行情
        tick.bidPrice1 = data['BidPrice1']
        tick.bidVolume1 = data['BidVolume1']
        tick.askPrice1 = data['AskPrice1']
        tick.askVolume1 = data['AskVolume1']
        
        tick.bidPrice2 = data['BidPrice2']
        tick.bidVolume2 = data['BidVolume2']
        tick.askPrice2 = data['AskPrice2']
        tick.askVolume2 = data['AskVolume2']  
        
        tick.bidPrice3 = data['BidPrice3']
        tick.bidVolume3 = data['BidVolume3']
        tick.askPrice3 = data['AskPrice3']
        tick.askVolume3 = data['AskVolume3']
        
        tick.bidPrice4 = data['BidPrice4']
        tick.bidVolume4 = data['BidVolume4']
        tick.askPrice4 = data['AskPrice4']
        tick.askVolume4 = data['AskVolume4']
        
        tick.bidPrice5 = data['BidPrice5']
        tick.bidVolume5 = data['BidVolume5']
        tick.askPrice5 = data['AskPrice5']
        tick.askVolume5 = data['AskVolume5']        
        
        self.gateway.onTick(tick)
        
    #----------------------------------------------------------------------
    def connect(self, userID, password, brokerID, address):
        """初始化连接"""
        self.userID = userID                # 账号
        self.password = password            # 密码
        self.brokerID = brokerID            # 经纪商代码
        self.address = address              # 服务器地址
        
        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            # 创建C++环境中的API对象，这里传入的参数是需要用来保存.con文件的文件夹路径
            path = getTempPath(self.gatewayName + '_')
            self.createFtdcMdApi(path)
            
            # 注册服务器地址
            self.registerFront(self.address)
            
            # 初始化连接，成功会调用onFrontConnected
            self.init()
            
        # 若已经连接但尚未登录，则进行登录
        else:
            if not self.loginStatus:
                self.login()
        
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅合约"""
        req = {}
        req['InstrumentID'] = str(subscribeReq.symbol)
        req['ExchangeID'] = exchangeMap.get(str(subscribeReq.exchange), '')
        
        # 这里的设计是，如果尚未登录就调用了订阅方法
        # 则先保存订阅请求，登录完成后会自动订阅
        if self.loginStatus:
            self.subscribeMarketData(req)
        
        self.subscribedSymbols.add(subscribeReq)   
        
    #----------------------------------------------------------------------
    def login(self):
        """登录"""
        # 如果填入了用户名密码等，则登录
        if self.userID and self.password and self.brokerID:
            req = {}
            req['UserID'] = self.userID
            req['Password'] = self.password
            req['BrokerID'] = self.brokerID
            self.reqID += 1
            self.reqUserLogin(req, self.reqID)    

    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()        
        
        
########################################################################
class LtsTdApi(TdApi):
    """LTS交易API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(LtsTdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        self.orderRef = EMPTY_INT           # 订单编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.userID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.brokerID = EMPTY_STRING        # 经纪商代码
        self.address = EMPTY_STRING         # 服务器地址
        self.productInfo = EMPTY_STRING     # 程序产品名称
        self.authCode = EMPTY_STRING        # 授权码
        self.randCode = EMPTY_STRING        # 随机码
        
        self.frontID = EMPTY_INT            # 前置机编号
        self.sessionID = EMPTY_INT          # 会话编号
        
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        self.connectionStatus = True
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'交易服务器连接成功'
        self.gateway.onLog(log)
        
        # 前置机连接后，请求随机码
        self.reqID += 1
        self.reqFetchAuthRandCode({}, self.reqID)        
    
    #----------------------------------------------------------------------
    def onFrontDisconnected(self, n):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.tdConnected = False
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'交易服务器连接断开'
        self.gateway.onLog(log)      
    
    #----------------------------------------------------------------------
    def onHeartBeatWarning(self, n):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
            self.frontID = str(data['FrontID'])
            self.sessionID = str(data['SessionID'])
            self.loginStatus = True
            self.gateway.mdConnected = True
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易服务器登录完成'
            self.gateway.onLog(log)            
                
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gateway
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        # 如果登出成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = False
            self.gateway.tdConnected = False
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易服务器登出完成'
            self.gateway.onLog(log)
                
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspFetchAuthRandCode(self, data, error, n, last):
        """请求随机认证码"""
        self.randCode = data['RandCode']
        self.login()
   
    #----------------------------------------------------------------------    
    def onRspUserPasswordUpdate(self, data, error, n, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspTradingAccountPasswordUpdate(self, data, error, n, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspOrderInsert(self, data, error, n, last):
        """发单错误（柜台）"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspOrderAction(self, data, error, n, last):
        """撤单错误（柜台）"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspError(self, error, n, last):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRtnOrder(self, data):
        """报单回报"""       
        # 更新最大报单编号
        newref = data['OrderRef']
        self.orderRef = max(self.orderRef, int(newref))
        
        # 创建报单数据对象
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        
        # 保存代码和报单号
        order.symbol = data['InstrumentID']
        order.exchange = exchangeMapReverse.get(data['ExchangeID'], '')
        order.vtSymbol = '.'.join([order.symbol, order.exchange])
        
        order.orderID = data['OrderRef']
        
        # 方向
        if data['Direction'] == '0':
            order.direction = DIRECTION_LONG
        elif data['Direction'] == '1':
            order.direction = DIRECTION_SHORT
        else:
            order.direction = DIRECTION_UNKNOWN
            
        # 开平
        if data['CombOffsetFlag'] == '0':
            order.offset = OFFSET_OPEN
        elif data['CombOffsetFlag'] == '1':
            order.offset = OFFSET_CLOSE
        else:
            order.offset = OFFSET_UNKNOWN
            
        # 状态
        if data['OrderStatus'] == '0':
            order.status = STATUS_ALLTRADED
        elif data['OrderStatus'] == '1':
            order.status = STATUS_PARTTRADED
        elif data['OrderStatus'] == '3':
            order.status = STATUS_NOTTRADED
        elif data['OrderStatus'] == '5':
            order.status = STATUS_CANCELLED
        else:
            order.status = STATUS_UNKNOWN
            
        # 价格、报单量等数值
        order.price = float(data['LimitPrice'])
        order.totalVolume = data['VolumeTotalOriginal']
        order.tradedVolume = data['VolumeTraded']
        order.orderTime = data['InsertTime']
        order.cancelTime = data['CancelTime']
        order.frontID = data['FrontID']
        order.sessionID = data['SessionID']
        
        # CTP的报单号一致性维护需要基于frontID, sessionID, orderID三个字段
        order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
        
        # 推送
        self.gateway.onOrder(order)
    
    #----------------------------------------------------------------------
    def onRtnTrade(self, data):
        """成交回报"""
        # 创建报单数据对象
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        # 保存代码和报单号
        trade.symbol = data['InstrumentID']
        trade.exchange = exchangeMapReverse.get(data['ExchangeID'], '')
        trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
        
        trade.tradeID = data['TradeID']
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
        
        trade.orderID = data['OrderRef']
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])   
        
        # 方向
        trade.direction = directionMapReverse.get(data['Direction'], '')
            
        # 开平
        trade.offset = offsetMapReverse.get(data['OffsetFlag'], '')
            
        # 价格、报单量等数值
        trade.price = float(data['Price'])
        trade.volume = data['Volume']
        trade.tradeTime = data['TradeTime']
        
        # 推送
        self.gateway.onTrade(trade)
    
    #----------------------------------------------------------------------
    def onErrRtnOrderInsert(self, data, error):
        """发单错误回报（交易所）"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onErrRtnOrderAction(self, data, error):
        """撤单错误回报（交易所）"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspFundOutByLiber(self, data, error, n, last):
        """LTS发起出金应答"""
        pass   
 
    #----------------------------------------------------------------------    
    def onRtnFundOutByLiber(self, data):
        """LTS发起出金通知"""
        pass        
    
    #----------------------------------------------------------------------
    def onErrRtnFundOutByLiber(self, data, error):
        """LTS发起出金错误回报"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnFundInByBank(self, data):
        """银行发起入金通知"""
        pass

    #----------------------------------------------------------------------
    def onRspFundInterTransfer(self, data, error, n, last):
        """资金内转应答"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnFundInterTransferSerial(self, data):
        """资金内转流水通知"""
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnFundInterTransfer(self, data, error):
        """资金内转错误回报"""
        pass  
         
    #----------------------------------------------------------------------
    def connect(self, userID, password, brokerID, address, productInfo, authCode):
        """初始化连接"""
        self.userID = userID                # 账号
        self.password = password            # 密码
        self.brokerID = brokerID            # 经纪商代码
        self.address = address              # 服务器地址
        self.productInfo = productInfo
        self.authCode = authCode
        
        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            # 创建C++环境中的API对象，这里传入的参数是需要用来保存.con文件的文件夹路径
            path = getTempPath(self.gatewayName + '_')
            self.createFtdcTraderApi(path)
            
            # 设置数据同步模式为推送从今日开始所有数据
            self.subscribePrivateTopic(0)
            self.subscribePublicTopic(0)
            
            # 注册服务器地址
            self.registerFront(self.address)
            
            # 初始化连接，成功会调用onFrontConnected
            self.init()
            
        # 若已经连接但尚未登录，则进行登录
        else:
            if not self.loginStatus:
                self.login()    
    
    #----------------------------------------------------------------------
    def login(self):
        """连接服务器"""
        # 如果填入了用户名密码等，则登录
        if self.userID and self.password and self.brokerID:
            req = {}
            req['UserID'] = self.userID
            req['Password'] = self.password
            req['BrokerID'] = self.brokerID
            req['UserProductInfo'] = self.productInfo
            req['AuthCode'] = self.authCode             
            req['RandCode'] = self.randCode
            self.reqID += 1
            self.reqUserLogin(req, self.reqID)   
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        self.reqID += 1
        self.orderRef += 1
        
        req = {}
        
        req['InstrumentID'] = str(orderReq.symbol)
        req['LimitPrice'] = str(orderReq.price)     # LTS里的价格是字符串
        req['VolumeTotalOriginal'] = int(orderReq.volume)
        req['ExchangeID'] = exchangeMap.get(orderReq.exchange, '')
        
        # 下面如果由于传入的类型本接口不支持，则会返回空字符串
        try:
            req['OrderPriceType'] = priceTypeMap[orderReq.priceType]
            req['Direction'] = directionMap[orderReq.direction]
            req['CombOffsetFlag'] = offsetMap[orderReq.offset]
            req['ExchangeID'] = exchangeMap[orderReq.exchange]
        except KeyError:
            return ''
            
        req['OrderRef'] = str(self.orderRef)
        req['InvestorID'] = self.userID
        req['UserID'] = self.userID
        req['BrokerID'] = self.brokerID
        
        req['CombHedgeFlag'] = defineDict['SECURITY_FTDC_HF_Speculation']       # 投机单
        req['ContingentCondition'] = defineDict['SECURITY_FTDC_CC_Immediately'] # 立即发单
        req['ForceCloseReason'] = defineDict['SECURITY_FTDC_FCC_NotForceClose'] # 非强平
        req['IsAutoSuspend'] = 0                                                # 非自动挂起
        req['TimeCondition'] = defineDict['SECURITY_FTDC_TC_GFD']               # 今日有效
        req['VolumeCondition'] = defineDict['SECURITY_FTDC_VC_AV']              # 任意成交量
        req['MinVolume'] = 1                                                    # 最小成交量为1
        req['UserForceClose'] = 0
        
        self.reqOrderInsert(req, self.reqID)
        
        # 返回订单号（字符串），便于某些算法进行动态管理
        vtOrderID = '.'.join([self.gatewayName, str(self.orderRef)])
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.reqID += 1

        req = {}
        
        req['InstrumentID'] = cancelOrderReq.symbol
        req['ExchangeID'] = cancelOrderReq.exchange
        req['OrderRef'] = cancelOrderReq.orderID
        req['FrontID'] = cancelOrderReq.frontID
        req['SessionID'] = cancelOrderReq.sessionID
        
        req['ActionFlag'] = defineDict['SECURITY_FTDC_AF_Delete']
        req['BrokerID'] = self.brokerID
        req['InvestorID'] = self.userID
        
        self.reqOrderAction(req, self.reqID)
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()


########################################################################
class LtsQryApi(QryApi):
    """Lts账户查询实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(LtsQryApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        self.orderRef = EMPTY_INT           # 订单编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.userID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.brokerID = EMPTY_STRING        # 经纪商代码
        self.address = EMPTY_STRING         # 服务器地址
        self.productInfo = EMPTY_STRING     # 程序产品名称
        self.authCode = EMPTY_STRING        # 授权码
        self.randCode = EMPTY_STRING        # 随机码        
        
        self.frontID = EMPTY_INT            # 前置机编号
        self.sessionID = EMPTY_INT          # 会话编号
    
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        self.connectionStatus = True
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'查询服务器连接成功'
        self.gateway.onLog(log)
        
        # 前置机连接后，请求随机码
        self.reqID += 1
        self.reqFetchAuthRandCode({}, self.reqID) 
        
    #----------------------------------------------------------------------
    def onFrontDisconnected(self, n):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.tdConnected = False
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'查询服务器连接断开'
        self.gateway.onLog(log)      
    
    #----------------------------------------------------------------------
    def onHeartBeatWarning(self, n):
        """"""
        pass    
    
    #----------------------------------------------------------------------
    def onRspError(self, error, n, last):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
            self.frontID = str(data['FrontID'])
            self.sessionID = str(data['SessionID'])
            self.loginStatus = True
            self.gateway.qryConnected = True
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'查询服务器登录完成'
            self.gateway.onLog(log)       
            
            # 查询合约代码
            self.reqID += 1
            self.reqQryInstrument({}, self.reqID)            
                
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gateway
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
                
    #----------------------------------------------------------------------
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        # 如果登出成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = False
            self.gateway.qryConnected = False
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'查询服务器登出完成'
            self.gateway.onLog(log)
                
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
                        
    #----------------------------------------------------------------------  
    def onRspFetchAuthRandCode(self, data, error, n, last):
        """请求随机认证码"""
        self.randCode = data['RandCode']
        self.login()

    #----------------------------------------------------------------------   
    def onRspQryExchange(self, data, error, n, last):
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInstrument(self, data, error, n, last):
        """合约查询回报"""
        contract = VtContractData()
        contract.gatewayName = self.gatewayName

        contract.symbol = data['InstrumentID']
        contract.exchange = exchangeMapReverse[data['ExchangeID']]
        contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
        contract.name = data['InstrumentName'].decode('GBK')
        
        # 合约数值
        contract.size = data['VolumeMultiple']
        contract.priceTick = data['PriceTick']
        contract.strikePrice = data['ExecPrice']
        contract.underlyingSymbol = data['MarketID']
        
        # 合约类型
        if data['ProductClass'] == '1':
            contract.productClass = PRODUCT_FUTURES
        elif data['ProductClass'] == '2':
            contract.productClass = PRODUCT_OPTION
        elif data['ProductClass'] == '3':
            contract.productClass = PRODUCT_COMBINATION
        elif data['ProductClass'] == '6':
            contract.productClass = PRODUCT_EQUITY
        elif data['ProductClass'] == '8':
            contract.productClass = PRODUCT_EQUITY
        else:
            print(data['ProductClass'])
        
        # 期权类型
        if data['InstrumentType'] == '1':
            contract.optionType = OPTION_CALL
        elif data['InstrumentType'] == '2':
            contract.optionType = OPTION_PUT
        
        # 推送
        self.gateway.onContract(contract)
        
        if last:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易合约信息获取完成'
            self.gateway.onLog(log)
                       
    #----------------------------------------------------------------------
    def onRspQryInvestor(self, data, error, n, last):
        """投资者查询回报"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTradingCode(self, data, error, n, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTradingAccount(self, data, error, n, last):
        """资金账户查询回报"""
        account = VtAccountData()
        account.gatewayName = self.gatewayName
        
        # 账户代码
        account.accountID = data['AccountID']
        account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
        
        # 数值相关
        account.preBalance = data['PreBalance']
        account.available = data['Available']
        account.commission = data['Commission']
        account.margin = data['CurrMargin']
        #account.closeProfit = data['CloseProfit']
        #account.positionProfit = data['PositionProfit']
        
        # 这里的balance和快期中的账户不确定是否一样，需要测试
        account.balance = data['Balance']
        
        # 推送
        self.gateway.onAccount(account)
               
    #----------------------------------------------------------------------
    def onRspQryBondInterest(self, data, error, n, last):
        """债券利息查询回报"""
        pass
    
    #----------------------------------------------------------------------   
    def onRspQryMarketRationInfo(self, data, error, n, last):
        """市值配售查询回报"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInstrumentCommissionRate(self, data, error, n, last):
        """合约手续费查询回报"""
        pass
      
    #----------------------------------------------------------------------
    def onRspQryETFInstrument(self, data, error, n, last):
        """ETF基金查询回报"""
        pass
    
    #----------------------------------------------------------------------  
    def onRspQryETFBasket(self, data, error, n, last):
        """ETF股票篮查询回报"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryOFInstrument(self, data, error, n, last):
        """OF合约查询回报"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQrySFInstrument(self, data, error, n, last):
        """SF合约查询回报"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInstrumentUnitMargin(self, data, error, n, last):
        """查询单手保证金"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryPreDelivInfo(self, data, error, n , last):
        """查询预交割信息"""
        pass
    
    #----------------------------------------------------------------------
    def onRsyQryCreditStockAssignInfo(self, data, error, n, last):
        """查询可融券分配"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryCreditCashAssignInfo(self, data, error, n , last):
        """查询可融资分配"""
        pass
    
    #----------------------------------------------------------------------
    def onRsyQryConversionRate(self, data, error, n, last):
        """查询证券这算率"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryHisCreditDebtInfo(self,data, error, n, last):
        """查询历史信用负债"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryMarketDataStaticInfo(self, data, error, n, last):
        """查询行情静态信息"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryExpireRepurchInfo(self, data, error, n, last):
        """查询到期回购信息响应"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryBondPledgeRate(self, data, error, n, last):
        """查询债券质押为标准券比例"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryPledgeBond(self, data, error, n, last):
        """查询债券质押代码对照关系"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryOrder(self, data, error, n, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryTrade(self, data, error, n, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInvestorPosition(self, data, error, n, last):
        """持仓查询回报"""
        pos = VtPositionData()
        pos.gatewayName = self.gatewayName
        
        # 保存代码
        pos.symbol = data['InstrumentID']
        pos.exchange = exchangeMapReverse.get(data['ExchangeID'], '')
        pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])     
        
        # 方向和持仓冻结数量
        pos.direction = posiDirectionMapReverse.get(data['PosiDirection'], '')

        if pos.direction == DIRECTION_NET or pos.direction == DIRECTION_LONG:
            pos.frozen = data['LongFrozen']
        elif pos.direction == DIRECTION_SHORT:   
            pos.frozen = data['ShortFrozen']
        
        # 持仓量
        pos.position = data['Position']
        pos.ydPosition = data['YdPosition']
        
        # 持仓均价
        if pos.position:
            pos.price = data['OpenCost'] / pos.position
        
        # VT系统持仓名
        pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
        
        # 推送
        self.gateway.onPosition(pos)
        
    #----------------------------------------------------------------------
    def OnRspQryFundTransferSerial(self, data, error, n, last):
        """资金转账查询"""
        pass
    
    #----------------------------------------------------------------------  
    def onRspQryFundInterTransferSerial(self, data, error,n, last):
        """资金内转流水查询"""
        pass
    
    #----------------------------------------------------------------------
    def connect(self, userID, password, brokerID, address, productInfo, authCode):
        """初始化连接"""
        self.userID = userID                # 账号
        self.password = password            # 密码
        self.brokerID = brokerID            # 经纪商代码
        self.address = address              # 服务器地址
        self.productInfo = productInfo
        self.authCode = authCode        
        
        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            # 创建C++环境中的API对象，这里传入的参数是需要用来保存.con文件的文件夹路径
            path = getTempPath(self.gatewayName + '_')
            self.createFtdcQueryApi(path)
            
            # 注册服务器地址
            self.registerFront(self.address)
            
            # 初始化连接，成功会调用onFrontConnected
            self.init()

        # 若已经连接但尚未登录，则进行登录
        else:
            if not self.loginStatus:
                self.login()    
    
    #----------------------------------------------------------------------
    def login(self):
        """连接服务器"""
        # 如果填入了用户名密码等，则登录
        
        if self.userID and self.password and self.brokerID:
            req = {}
            req['UserID'] = self.userID
            req['Password'] = self.password
            req['BrokerID'] = self.brokerID
            req['UserProductInfo'] = self.productInfo
            req['AuthCode'] = self.authCode             
            req['RandCode'] = self.randCode          
            self.reqID += 1
            
            self.reqUserLogin(req, self.reqID)   
            
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户"""
        self.reqID += 1
        #是否需要INVESTERID, BROKERID?
        req = {}
        req['BrokerID'] = self.brokerID
        req['InvestorID'] = self.userID
        self.reqQryTradingAccount(req, self.reqID)
         
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.reqID += 1
        req = {}
        req['BrokerID'] = self.brokerID
        req['InvestorID'] = self.userID
        self.reqQryInvestorPosition(req, self.reqID)   
         
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()    
    
        
    