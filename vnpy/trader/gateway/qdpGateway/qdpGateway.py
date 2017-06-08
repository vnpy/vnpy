# encoding: UTF-8

'''
vn.qdp的gateway接入

考虑到现阶段大部分QDP中的ExchangeID字段返回的都是空值
vtSymbol直接使用symbol
'''


import os
import json
import datetime
from copy import copy

from vnpy.api.qdp import MdApi, TdApi, defineDict
from vnpy.trader.vtGateway import *


# 以下为一些VT类型和QDP类型的映射字典
# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = defineDict["QDP_FTDC_OPT_LimitPrice"]
priceTypeMap[PRICETYPE_MARKETPRICE] = defineDict["QDP_FTDC_OPT_AnyPrice"]
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = defineDict['QDP_FTDC_D_Buy']
directionMap[DIRECTION_SHORT] = defineDict['QDP_FTDC_D_Sell']
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {}
offsetMap[OFFSET_OPEN] = defineDict['QDP_FTDC_OF_Open']
offsetMap[OFFSET_CLOSE] = defineDict['QDP_FTDC_OF_Close']
offsetMap[OFFSET_CLOSETODAY] = defineDict['QDP_FTDC_OF_CloseToday']
offsetMap[OFFSET_CLOSEYESTERDAY] = defineDict['QDP_FTDC_OF_CloseYesterday']
offsetMapReverse = {v:k for k,v in offsetMap.items()}

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_CFFEX] = defineDict["QDP_EI_CFFEX"]
exchangeMap[EXCHANGE_SHFE] = defineDict["QDP_EI_SHFE"]
exchangeMap[EXCHANGE_CZCE] = defineDict["QDP_EI_ZCE"]
exchangeMap[EXCHANGE_DCE] = defineDict["QDP_EI_DCE"]
exchangeMap[EXCHANGE_SGE] = defineDict["QDP_EI_SGE"]
exchangeMap[EXCHANGE_UNKNOWN] = ''
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 产品类型映射
productClassMapReverse = {}
productClassMapReverse[defineDict["QDP_FTDC_PC_Futures"]] = PRODUCT_FUTURES
productClassMapReverse[defineDict["QDP_FTDC_PC_Options"]] = PRODUCT_OPTION
productClassMapReverse[defineDict["QDP_FTDC_PC_Combination"]] = PRODUCT_COMBINATION
productClassMapReverse[defineDict["QDP_FTDC_PC_Stocks"]] = PRODUCT_EQUITY
productClassMapReverse[defineDict["QDP_FTDC_PC_StockOptions"]] = PRODUCT_OPTION
productClassMapReverse[defineDict["QDP_FTDC_PC_SGE_SPOT"]] = PRODUCT_SPOT
productClassMapReverse[defineDict["QDP_FTDC_PC_SGE_DEFER"]] = PRODUCT_SPOT
productClassMapReverse[defineDict["QDP_FTDC_PC_SGE_FOWARD"]] = PRODUCT_SPOT


########################################################################
class QdpGateway(VtGateway):
    """QDP接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='QDP'):
        """Constructor"""
        super(QdpGateway, self).__init__(eventEngine, gatewayName)
        
        self.mdApi = QdpMdApi(self)     # 行情API
        self.tdApi = QdpTdApi(self)     # 交易API
        
        self.mdConnected = False        # 行情API连接状态，登录完成后为True
        self.tdConnected = False        # 交易API连接状态
        
        self.qryEnabled = False         # 是否要启动循环查询
        
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
            userID = str(setting['userID'])
            password = str(setting['password'])
            brokerID = str(setting['brokerID'])
            tdAddress = str(setting['tdAddress'])
            mdAddress = str(setting['mdAddress'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 创建行情和交易接口对象
        self.mdApi.connect(userID, password, brokerID, mdAddress)
        self.tdApi.connect(userID, password, brokerID, tdAddress)
        
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
        pass
        
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
class QdpMdApi(MdApi):
    """QDP行情API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(QdpMdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.subscribedSymbols = set()      # 已订阅合约代码        
        
        self.userID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.brokerID = EMPTY_STRING        # 经纪商代码
        self.address = EMPTY_STRING         # 服务器地址
        
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
            path = os.getcwd() + '/temp/' + self.gatewayName + '/md/'
            if not os.path.exists(path):
                os.makedirs(path)
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
        # 这里的设计是，如果尚未登录就调用了订阅方法
        # 则先保存订阅请求，登录完成后会自动订阅
        if self.loginStatus:
            self.subMarketData(str(subscribeReq.symbol))
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
    def logout(self):
        """登录"""
        # 如果填入了用户名密码等，则登录
        if self.userID and self.brokerID:
            req = {}
            req['UserID'] = self.userID
            req['BrokerID'] = self.brokerID
            self.reqID += 1
            self.reqUserLogout(req, self.reqID)    
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.logout()
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
    def onFrontDisconnected(self, i):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.mdConnected = False
    
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'行情服务器连接断开'
        self.gateway.onLog(log) 
    
    #----------------------------------------------------------------------
    def onHeartBeatWarning(self, i):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onPackageStart(self, topicID, sequenceNo):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onPackageEnd(self, topicID, sequenceNo):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onMultiHeartbeat(self, currTime, multiCastIP):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def udpMarketData(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspError(self, error, id, last):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, id, last):
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
    def onRspUserLogout(self, data, error, id, last):
        """登出回报"""
        # 如果登出成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = False
            self.gateway.mdConnected = False
    
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
    def onRtnQmdInstrumentStatu(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSubscribeTopic(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryTopic(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnDepthMarketData(self, data):
        """行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
    
        tick.symbol = data['InstrumentID']
        tick.exchange = exchangeMapReverse.get(data['ExchangeID'], u'未知')
        tick.vtSymbol = tick.symbol #'.'.join([tick.symbol, EXCHANGE_UNKNOWN])
    
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
    
        # QDP只有一档行情
        tick.bidPrice1 = data['BidPrice1']
        tick.bidVolume1 = data['BidVolume1']
        tick.askPrice1 = data['AskPrice1']
        tick.askVolume1 = data['AskVolume1']
    
        self.gateway.onTick(tick)
    
    #----------------------------------------------------------------------
    def onRspSubMarketData(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspUnSubMarketData(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryDepthMarketData(self, data, error, id, last):
        """"""
        pass


########################################################################
class QdpTdApi(TdApi):
    """QDP交易API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(QdpTdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        self.orderRef =        EMPTY_INT            # 订单编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.userID = EMPTY_STRING          # 账号
        self.investorID = EMPTY_STRING      # 投资账号
        self.password = EMPTY_STRING        # 密码
        self.brokerID = EMPTY_STRING        # 经纪商代码
        self.address = EMPTY_STRING         # 服务器地址
        
        self.frontID = EMPTY_INT            # 前置机编号
        self.sessionID = EMPTY_INT          # 会话编号
        
        self.posBufferDict = {}             # 缓存持仓数据的字典
    
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
            path = os.getcwd() + '/temp/' + self.gatewayName + '/td/'
            if not os.path.exists(path):
                os.makedirs(path)
            self.createFtdcTraderApi(path)

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
            self.reqID += 1
            self.reqUserLogin(req, self.reqID)   
        
    #----------------------------------------------------------------------
    def logout(self):
        """连接服务器"""
        # 如果填入了用户名密码等，则登录
        if self.userID and self.brokerID:
            req = {}
            req['UserID'] = self.userID
            req['BrokerID'] = self.brokerID
            self.reqID += 1
            self.reqUserLogout(req, self.reqID)   
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户"""
        self.reqID += 1
        req = {}
        req['BrokerID'] = self.brokerID
        req['InvestorID'] = self.investorID
        self.reqQryInvestorAccount(req, self.reqID)
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.reqID += 1
        req = {}
        req['BrokerID'] = self.brokerID
        req['InvestorID'] = self.investorID
        self.reqQryInvestorPosition(req, self.reqID)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        self.reqID += 1
        self.orderRef += 1
        
        req = {}
       
        req['InstrumentID'] = orderReq.symbol
        req['LimitPrice'] = orderReq.price
        req['Volume'] = orderReq.volume
        req['ExchangeID'] = str(orderReq.exchange)
        
        # 下面如果由于传入的类型本接口不支持，则会返回空字符串
        req['OrderPriceType'] = priceTypeMap.get(orderReq.priceType, '')
        req['Direction'] = directionMap.get(orderReq.direction, '')
        req['OffsetFlag'] = offsetMap.get(orderReq.offset, '')
            
        req['UserOrderLocalID'] = str(self.orderRef)
        req['InvestorID'] = self.investorID
        req['UserID'] = self.userID
        req['InvestorID'] = self.investorID
        req['BrokerID'] = self.brokerID
        req['HedgeFlag'] = defineDict['QDP_FTDC_CHF_Speculation']           # 投机单
        req['ForceCloseReason'] = defineDict['QDP_FTDC_FCR_NotForceClose']  # 非强平
        req['IsAutoSuspend'] = 0                                            # 非自动挂起
        req['TimeCondition'] = defineDict['QDP_FTDC_TC_GFD']                # 今日有效
        req['VolumeCondition'] = defineDict['QDP_FTDC_VC_AV']               # 任意成交量
        req['MinVolume'] = 1                                                # 最小成交量为1
        
        # 判断FAK和FOK
        if orderReq.priceType == PRICETYPE_FAK:
            req['OrderPriceType'] = defineDict["QDP_FTDC_OPT_LimitPrice"]
            req['TimeCondition'] = defineDict['QDP_FTDC_TC_IOC']
            req['VolumeCondition'] = defineDict['QDP_FTDC_VC_AV']
        if orderReq.priceType == PRICETYPE_FOK:
            req['OrderPriceType'] = defineDict["QDP_FTDC_OPT_LimitPrice"]
            req['TimeCondition'] = defineDict['QDP_FTDC_TC_IOC']
            req['VolumeCondition'] = defineDict['QDP_FTDC_VC_CV']        
        
        self.reqOrderInsert(req, self.reqID)
        
        # 返回订单号（字符串），便于某些算法进行动态管理
        vtOrderID = '.'.join([self.gatewayName, str(self.orderRef)])
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.reqID += 1
        self.orderRef += 1

        req = {}
        
        req['InstrumentID'] = cancelOrderReq.symbol
        req['ExchangeID'] = cancelOrderReq.exchange
        req['UserOrderLocalID'] = cancelOrderReq.orderID
        req['UserOrderActionLocalID'] = str(self.orderRef)
        req['FrontID'] = cancelOrderReq.frontID
        req['SessionID'] = cancelOrderReq.sessionID
        
        req['ActionFlag'] = defineDict['QDP_FTDC_AF_Delete']
        req['BrokerID'] = self.brokerID
        req['InvestorID'] = self.investorID
        req['UserID'] = self.userID
        
        self.reqOrderAction(req, self.reqID)
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.logout()
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
    def onFrontDisconnected(self, i):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.tdConnected = False
    
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'交易服务器连接断开'
        self.gateway.onLog(log)  
    
    #----------------------------------------------------------------------
    def onHeartBeatWarning(self, i):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onPackageStart(self, topicID, sequenceNo):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onPackageEnd(self, topicID, sequenceNo):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspError(self, error, id, last):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, id, last):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
            self.frontID = str(data['FrontID'])
            self.sessionID = str(data['SessionID'])
            self.loginStatus = True
            self.gateway.tdConnected = True
    
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易服务器登录完成'
            self.gateway.onLog(log)
    
            # 获取investorID
            self.reqID += 1
            req = {}
            req['UserID'] = self.userID
            req['Password'] = self.password
            req['BrokerID'] = self.brokerID
            self.reqQryUserInvestor(req,self.reqID)
    
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspUserLogout(self, data, error, id, last):
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
    def onRspUserPasswordUpdate(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspOrderInsert(self, data, error, id, last):
        """发单回报（柜台）"""
        if error['ErrorID'] == 0:
            return    
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspOrderAction(self, data, error, id, last):
        """撤单回报（柜台）"""
        if error['ErrorID'] == 0:
            return
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspFromBankToFutureByFuture(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspFromFutureToBankByFuture(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnFlowMessageCancel(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnTrade(self, data):
        """成交回报"""
        # 创建报单数据对象
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
    
        # 保存代码和报单号
        trade.symbol = data['InstrumentID']
        trade.exchange = exchangeMapReverse[data['ExchangeID']]
        trade.vtSymbol = trade.symbol #'.'.join([trade.symbol, trade.exchange])
    
        trade.tradeID = data['TradeID']
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
    
        trade.orderID = data['UserOrderLocalID']
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
    
        # 方向
        trade.direction = directionMapReverse.get(data['Direction'], '')
    
        # 开平
        trade.offset = offsetMapReverse.get(data['OffsetFlag'], '')
    
        # 价格、报单量等数值
        trade.price = data['TradePrice']
        trade.volume = data['TradeVolume']
        trade.tradeTime = data['TradeTime']
    
        # 推送
        self.gateway.onTrade(trade)
    
    #----------------------------------------------------------------------
    def onRtnOrder(self, data):
        """报单回报"""
        # 更新最大报单编号
        newref = data['UserOrderLocalID']
        if not newref == '':
            self.orderRef = max(self.orderRef, int(newref))
    
        # 创建报单数据对象
        order = VtOrderData()
        order.gatewayName = self.gatewayName
    
        # 保存代码和报单号
        order.symbol = data['InstrumentID']
        order.exchange = exchangeMapReverse[data['ExchangeID']]
        order.vtSymbol = order.symbol #'.'.join([order.symbol, order.exchange])
    
        order.orderID = data['UserOrderLocalID']
    
        # 方向
        if data['Direction'] == '0':
            order.direction = DIRECTION_LONG
        elif data['Direction'] == '1':
            order.direction = DIRECTION_SHORT
        else:
            order.direction = DIRECTION_UNKNOWN
    
        # 开平
        if data['OffsetFlag'] == '0':
            order.offset = OFFSET_OPEN
        elif data['OffsetFlag'] == '1':
            order.offset = OFFSET_CLOSE
        elif data['OffsetFlag'] == '3':
            order.offset = OFFSET_CLOSETODAY
        else:
            order.offset = OFFSET_UNKNOWN
    
        # 状态
        if data['OrderStatus'] == '0':
            order.status = STATUS_ALLTRADED
        elif data['OrderStatus'] == '1':
            order.status = STATUS_PARTTRADED
        elif data['OrderStatus'] == '2':
            order.status = STATUS_PARTTRADED_PARTCANCELED
        elif data['OrderStatus'] == '3':
            order.status = STATUS_NOTTRADED
        elif data['OrderStatus'] == '5':
            order.status = STATUS_CANCELLED
        else:
            order.status = STATUS_UNKNOWN
    
        # 价格、报单量等数值
        order.price = data['LimitPrice']
        order.totalVolume = data['Volume']
        order.tradedVolume = data['VolumeTraded']
        order.orderTime = data['InsertTime']
        order.cancelTime = data['CancelTime']
        order.frontID = data['FrontID']
        order.sessionID = data['SessionID']
    
        # QDP的报单号一致性维护需要基于frontID, sessionID, orderID三个字段
        # 但在本接口设计中，已经考虑了QDP的OrderRef的自增性，避免重复
        # 唯一可能出现OrderRef重复的情况是多处登录并在非常接近的时间内（几乎同时发单）
        # 考虑到VtTrader的应用场景，认为以上情况不会构成问题
        order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
    
        # 推送
        self.gateway.onOrder(order)
    
    #----------------------------------------------------------------------
    def onErrRtnOrderInsert(self, data, error):
        """发单错误回报（交易所）"""
        if error['ErrorID'] == 0:
            return
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onErrRtnOrderAction(self, data, error):
        """撤单错误回报（交易所）"""
        if error['ErrorID'] == 0:
            return
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRtnInstrumentStatus(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnInvestorAccountDeposit(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnMessageNotify(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnQueryBankBalanceByFuture(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnBankToFutureByFuture(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onErrRtnFutureToBankByFuture(self, data, error):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnQueryBankBalanceByFuture(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnFromBankToFutureByFuture(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnFromFutureToBankByFuture(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnSGEDeferRate(self, data):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryOrder(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryTrade(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryUserInvestor(self, data, error, id, last):
        """查询投资账户回报"""
        # 如果查询成功，推送日志信息
        if error['ErrorID'] == 0:
            self.investorID = data['InvestorID']
    
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'投资者查询完成'
            self.gateway.onLog(log)
            
            # 查询合约代码
            self.reqID += 1
            self.reqQryInstrument({}, self.reqID)            
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspQryInvestorAccount(self, data, error, id, last):
        """资金账户查询回报"""
        account = VtAccountData()
        account.gatewayName = self.gatewayName
    
        # 账户代码
        account.accountID = data['AccountID']
        account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
    
        # 数值相关
        account.preBalance = data['PreBalance']
        account.available = data['Available']
        account.commission = data['Fee']
        account.margin = data['Margin']
        account.closeProfit = data['CloseProfit']
        account.positionProfit = data['PositionProfit']
        account.balance = data['DynamicRights']
    
        # 推送
        self.gateway.onAccount(account)
    
    #----------------------------------------------------------------------
    def onRspQryInstrument(self, data, error, id, last):
        """合约查询回报"""
        contract = VtContractData()
        contract.gatewayName = self.gatewayName
    
        contract.symbol = data['InstrumentID']
        contract.exchange = exchangeMapReverse[data['ExchangeID']]
        contract.vtSymbol = contract.symbol #'.'.join([contract.symbol, contract.exchange])
        contract.name = data['InstrumentName'].decode('GBK')
    
        # 合约数值
        contract.size = data['VolumeMultiple']
        contract.priceTick = data['PriceTick']
        contract.strikePrice = data['StrikePrice']
        contract.underlyingSymbol = data['UnderlyingInstrID']
    
        # 合约类型
        contract.productClass = productClassMapReverse.get(data['ProductClass'], 
                                                           PRODUCT_UNKNOWN)
    
        # 期权类型
        if data['OptionsType'] == '1':
            contract.optionType = OPTION_CALL
        elif data['OptionsType'] == '2':
            contract.optionType = OPTION_PUT
    
        # 推送
        self.gateway.onContract(contract)
    
        if last:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易合约信息获取完成'
            self.gateway.onLog(log)
    
    #----------------------------------------------------------------------
    def onRspQryExchange(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInvestorPosition(self, data, error, id, last):
        """持仓查询回报"""
        pos = VtPositionData()
        pos.gatewayName = self.gatewayName
        
        pos.symbol = data['InstrumentID']
        pos.vtSymbol = pos.symbol
        pos.direction = directionMapReverse.get(data['Direction'], DIRECTION_UNKNOWN)
        pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
        
        pos.position = data['Position']
        pos.ydPosition = data['YdPosition']
        pos.frozen = data['FrozenClosing']
        if pos.position:
            pos.price = data['PositionCost'] / pos.position
        
        self.gateway.onPosition(pos)
    
    #----------------------------------------------------------------------
    def onRspSubscribeTopic(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryTopic(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInvestorFee(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInvestorMargin(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryExchangeDiffTime(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryContractBank(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQueryBankAccountMoneyByFuture(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryTransferSerial(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQrySGEDeferRate(self, data, error, id, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryMarketData(self, data, error, id, last):
        """"""
        pass
