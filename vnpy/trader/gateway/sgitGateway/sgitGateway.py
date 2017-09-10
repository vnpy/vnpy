# encoding: UTF-8

'''
vn.sgit的gateway接入

考虑到现阶段大部分SGIT中的ExchangeID字段返回的都是空值
vtSymbol直接使用symbol
'''


import os
import json
from copy import copy
from datetime import datetime

from vnpy.api.sgit import MdApi, TdApi, defineDict
from vnpy.trader.vtFunction import getTempPath, getJsonPath
from vnpy.trader.vtGateway import *


# 以下为一些VT类型和SGIT类型的映射字典
# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = defineDict["THOST_FTDC_OPT_LimitPrice"]
priceTypeMap[PRICETYPE_MARKETPRICE] = defineDict["THOST_FTDC_OPT_AnyPrice"]
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = defineDict['THOST_FTDC_D_Buy']
directionMap[DIRECTION_SHORT] = defineDict['THOST_FTDC_D_Sell']
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {}
offsetMap[OFFSET_OPEN] = defineDict['THOST_FTDC_OF_Open']
offsetMap[OFFSET_CLOSE] = defineDict['THOST_FTDC_OF_Close']
offsetMap[OFFSET_CLOSETODAY] = defineDict['THOST_FTDC_OF_CloseToday']
offsetMap[OFFSET_CLOSEYESTERDAY] = defineDict['THOST_FTDC_OF_CloseYesterday']
offsetMapReverse = {v:k for k,v in offsetMap.items()}

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_CFFEX] = 'CFFEX'
exchangeMap[EXCHANGE_SHFE] = 'SHFE'
exchangeMap[EXCHANGE_CZCE] = 'CZCE'
exchangeMap[EXCHANGE_DCE] = 'DCE'
exchangeMap[EXCHANGE_SGE] = 'SGE'
exchangeMap[EXCHANGE_UNKNOWN] = ''
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 持仓类型映射
posiDirectionMap = {}
posiDirectionMap[DIRECTION_NET] = defineDict["THOST_FTDC_PD_Net"]
posiDirectionMap[DIRECTION_LONG] = defineDict["THOST_FTDC_PD_Long"]
posiDirectionMap[DIRECTION_SHORT] = defineDict["THOST_FTDC_PD_Short"]
posiDirectionMapReverse = {v:k for k,v in posiDirectionMap.items()}

# 产品类型映射
productClassMap = {}
productClassMap[PRODUCT_FUTURES] = defineDict["THOST_FTDC_PC_Futures"]
productClassMap[PRODUCT_OPTION] = defineDict["THOST_FTDC_PC_Options"]
productClassMap[PRODUCT_COMBINATION] = defineDict["THOST_FTDC_PC_Combination"]
productClassMapReverse = {v:k for k,v in productClassMap.items()}

# 委托状态映射
statusMap = {}
statusMap[STATUS_ALLTRADED] = defineDict["THOST_FTDC_OST_AllTraded"]
statusMap[STATUS_PARTTRADED] = defineDict["THOST_FTDC_OST_PartTradedQueueing"]
statusMap[STATUS_NOTTRADED] = defineDict["THOST_FTDC_OST_NoTradeQueueing"]
statusMap[STATUS_CANCELLED] = defineDict["THOST_FTDC_OST_Canceled"]
statusMapReverse = {v:k for k,v in statusMap.items()}


########################################################################
class SgitGateway(VtGateway):
    """SGIT接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='SGIT'):
        """Constructor"""
        super(SgitGateway, self).__init__(eventEngine, gatewayName)
        
        self.mdApi = SgitMdApi(self)     # 行情API
        self.tdApi = SgitTdApi(self)     # 交易API
        
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
class SgitMdApi(MdApi):
    """SGIT行情API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(SgitMdApi, self).__init__()
        
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
        # 这里的设计是，如果尚未登录就调用了订阅方法
        # 则先保存订阅请求，登录完成后会自动订阅
        if self.loginStatus:
            self.subscribeMarketData(str(subscribeReq.symbol))
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
        log.logContent = u'行情服务器连接断开'
        self.gateway.onLog(log)    
        
    #----------------------------------------------------------------------
    def onHeartBeatWarning(self, timeLapse):
        """"""
        pass
        
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
    def onRspError(self, error, id, last):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspSubMarketData(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspUnSubMarketData(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspSubForQuoteRsp(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspUnSubForQuoteRsp(self, data, error, id, last):
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
    
        # 这里由于交易所夜盘时段的交易日数据有误，所以选择本地获取
        #tick.date = data['TradingDay']
        tick.date = datetime.now().strftime('%Y%m%d')   
    
        tick.openPrice = data['OpenPrice']
        tick.highPrice = data['HighestPrice']
        tick.lowPrice = data['LowestPrice']
        tick.preClosePrice = data['PreClosePrice']
    
        tick.upperLimit = data['UpperLimitPrice']
        tick.lowerLimit = data['LowerLimitPrice']
    
        # SGIT只有一档行情
        tick.bidPrice1 = data['BidPrice1']
        tick.bidVolume1 = data['BidVolume1']
        tick.askPrice1 = data['AskPrice1']
        tick.askVolume1 = data['AskVolume1']
    
        self.gateway.onTick(tick)
        
    #----------------------------------------------------------------------
    def onRtnForQuoteRsp(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnDeferDeliveryQuot(self, data):
        """"""
        pass
        

########################################################################
class SgitTdApi(TdApi):
    """SGIT交易API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(SgitTdApi, self).__init__()
        
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
        
        self.frontID = EMPTY_INT            # 前置机编号
        self.sessionID = EMPTY_INT          # 会话编号
        
        self.posBufferDict = {}             # 缓存持仓数据的字典
        self.symbolExchangeDict = {}        # 保存合约代码和交易所的印射关系
        self.symbolSizeDict = {}            # 保存合约代码和合约大小的印射关系
    
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
            self.reqID += 1
            self.reqUserLogin(req, self.reqID)   
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户"""
        self.reqID += 1
        self.reqQryTradingAccount({}, self.reqID)
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.reqID += 1
        req = {}
        req['BrokerID'] = self.brokerID
        req['InvestorID'] = self.userID
        self.reqQryInvestorPosition(req, self.reqID)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        self.reqID += 1
        self.orderRef += 1
        orderRef = str(self.orderRef).rjust(10, '0')
        
        req = {}
        
        req['InstrumentID'] = orderReq.symbol
        req['LimitPrice'] = orderReq.price
        req['VolumeTotalOriginal'] = orderReq.volume
        
        # 下面如果由于传入的类型本接口不支持，则会返回空字符串
        req['OrderPriceType'] = priceTypeMap.get(orderReq.priceType, '')
        req['Direction'] = directionMap.get(orderReq.direction, '')
        req['CombOffsetFlag'] = offsetMap.get(orderReq.offset, '')
            
        req['OrderRef'] = orderRef
        req['InvestorID'] = self.userID
        req['UserID'] = self.userID
        req['BrokerID'] = self.brokerID
        
        req['CombHedgeFlag'] = defineDict['THOST_FTDC_HF_Speculation']       # 投机单
        req['ContingentCondition'] = defineDict['THOST_FTDC_CC_Immediately'] # 立即发单
        req['ForceCloseReason'] = defineDict['THOST_FTDC_FCC_NotForceClose'] # 非强平
        req['IsAutoSuspend'] = 0                                             # 非自动挂起
        req['TimeCondition'] = defineDict['THOST_FTDC_TC_GFD']               # 今日有效
        req['VolumeCondition'] = defineDict['THOST_FTDC_VC_AV']              # 任意成交量
        req['MinVolume'] = 1                                                 # 最小成交量为1
        
        # 判断FAK和FOK
        if orderReq.priceType == PRICETYPE_FAK:
            req['OrderPriceType'] = defineDict["THOST_FTDC_OPT_LimitPrice"]
            req['TimeCondition'] = defineDict['THOST_FTDC_TC_IOC']
            req['VolumeCondition'] = defineDict['THOST_FTDC_VC_AV']
        if orderReq.priceType == PRICETYPE_FOK:
            req['OrderPriceType'] = defineDict["THOST_FTDC_OPT_LimitPrice"]
            req['TimeCondition'] = defineDict['THOST_FTDC_TC_IOC']
            req['VolumeCondition'] = defineDict['THOST_FTDC_VC_CV']        
        
        self.reqOrderInsert(req, self.reqID)
        
        # 返回订单号（字符串），便于某些算法进行动态管理
        vtOrderID = '.'.join([self.gatewayName, orderRef])

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
        
        req['ActionFlag'] = defineDict['THOST_FTDC_AF_Delete']
        req['BrokerID'] = self.brokerID
        req['InvestorID'] = self.userID
        req['UserID'] = self.userID
        
        self.reqOrderAction(req, self.reqID)
        
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
        log.logContent = u'交易服务器连接断开'
        self.gateway.onLog(log)   

    #----------------------------------------------------------------------
    def onHeartBeatWarning(self, timeLapse):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspAuthenticate(self, data, error, id, last):
        """"""
        pass
        
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
            
            # 确认结算信息
            req = {}
            req['BrokerID'] = self.brokerID
            req['InvestorID'] = self.userID
            self.reqID += 1
            self.reqSettlementInfoConfirm(req, self.reqID)              
                
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
    def onRspTradingAccountPasswordUpdate(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspOrderInsert(self, data, error, id, last):
        """发单错误（柜台）"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspParkedOrderInsert(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspParkedOrderAction(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspOrderAction(self, data, error, id, last):
        """撤单错误（柜台）"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspQueryMaxOrderVolume(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspSettlementInfoConfirm(self, data, error, id, last):
        """确认结算信息回报"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'结算信息确认完成'
        self.gateway.onLog(log)
    
        # 查询合约代码
        self.reqID += 1
        self.reqQryInstrument({}, self.reqID)
        
    #----------------------------------------------------------------------
    def onRspRemoveParkedOrder(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspRemoveParkedOrderAction(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspExecOrderInsert(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspExecOrderAction(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspForQuoteInsert(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQuoteInsert(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQuoteAction(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspBatchOrderAction(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspCombActionInsert(self, data, error, id, last):
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
    def onRspQryInvestorPosition(self, data, error, id, last):
        """持仓查询回报"""
        # 获取缓存字典中的持仓缓存，若无则创建并初始化
        positionName = '.'.join([data['InstrumentID'], data['PosiDirection']])
        
        if positionName in self.posBufferDict:
            posBuffer = self.posBufferDict[positionName]
        else:
            posBuffer = PositionBuffer(data, self.gatewayName)
            self.posBufferDict[positionName] = posBuffer
        
        # 更新持仓缓存，并获取VT系统中持仓对象的返回值
        exchange = self.symbolExchangeDict.get(data['InstrumentID'], EXCHANGE_UNKNOWN)
        size = self.symbolSizeDict.get(data['InstrumentID'], 1)
        if exchange == EXCHANGE_SHFE:
            posBuffer.updateShfeBuffer(data, size)
        else:
            posBuffer.updateBuffer(data, size)
            
        # 所有持仓数据都更新后，再将缓存中的持仓情况发送到事件引擎中
        if last:
            for buf in self.posBufferDict.values():
                pos = buf.getPos()
                self.gateway.onPosition(pos)
        
    #----------------------------------------------------------------------
    def onRspQryTradingAccount(self, data, error, id, last):
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
        account.closeProfit = data['CloseProfit']
        account.positionProfit = data['PositionProfit']
    
        # 这里的balance和快期中的账户不确定是否一样，需要测试
        account.balance = (data['PreBalance'] - data['PreCredit'] - data['PreMortgage'] +
                           data['Mortgage'] - data['Withdraw'] + data['Deposit'] +
                           data['CloseProfit'] + data['PositionProfit'] + data['CashIn'] -
                           data['Commission'])
    
        # 推送
        self.gateway.onAccount(account)
        
    #----------------------------------------------------------------------
    def onRspQryInvestor(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTradingCode(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInstrumentMarginRate(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInstrumentCommissionRate(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryExchange(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryProduct(self, data, error, id, last):
        """"""
        pass
        
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

        contract.productClass = productClassMapReverse.get(data['ProductClass'], PRODUCT_UNKNOWN)

        # 期权类型
        if data['OptionsType'] == '1':
            contract.optionType = OPTION_CALL
        elif data['OptionsType'] == '2':
            contract.optionType = OPTION_PUT

        # 缓存代码和交易所的印射关系
        self.symbolExchangeDict[contract.symbol] = contract.exchange
        self.symbolSizeDict[contract.symbol] = contract.size

        # 推送
        self.gateway.onContract(contract)

        if last:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易合约信息获取完成'
            self.gateway.onLog(log)
        
    #----------------------------------------------------------------------
    def onRspQryDepthMarketData(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQrySettlementInfo(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTransferBank(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInvestorPositionDetail(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryNotice(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQrySettlementInfoConfirm(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInvestorPositionCombineDetail(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryCFMMCTradingAccountKey(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryEWarrantOffset(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInvestorProductGroupMargin(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryExchangeMarginRate(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryExchangeMarginRateAdjust(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryExchangeRate(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQrySecAgentACIDMap(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryProductExchRate(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryProductGroup(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryOptionInstrTradeCost(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryOptionInstrCommRate(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryExecOrder(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryForQuote(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryQuote(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryCombInstrumentGuard(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryCombAction(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTransferSerial(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryAccountregister(self, data, error, id, last):
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
        order.exchange = exchangeMapReverse[data['ExchangeID']]
        order.vtSymbol = order.symbol #'.'.join([order.symbol, order.exchange])
        
        order.orderID = data['OrderRef']
        order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
        
        order.direction = directionMapReverse.get(data['Direction'], DIRECTION_UNKNOWN)
        order.offset = offsetMapReverse.get(data['CombOffsetFlag'], OFFSET_UNKNOWN)
        order.status = statusMapReverse.get(data['OrderStatus'], STATUS_UNKNOWN)
            
        # 价格、报单量等数值
        order.price = data['LimitPrice']
        order.totalVolume = data['VolumeTotalOriginal']
        order.tradedVolume = data['VolumeTraded']
        order.orderTime = data['InsertTime']
        order.cancelTime = data['CancelTime']
        order.frontID = data['FrontID']
        order.sessionID = data['SessionID']
        
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
        trade.exchange = exchangeMapReverse[data['ExchangeID']]
        trade.vtSymbol = trade.symbol #'.'.join([trade.symbol, trade.exchange])
        
        trade.tradeID = data['TradeID']
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
        
        trade.orderID = data['OrderRef']
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
        
        trade.direction = directionMapReverse.get(data['Direction'], '')
        trade.offset = offsetMapReverse.get(data['OffsetFlag'], '')
            
        # 价格、报单量等数值
        trade.price = data['Price']
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
    def onRtnInstrumentStatus(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnTradingNotice(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnErrorConditionalOrder(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnExecOrder(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onErrRtnExecOrderInsert(self, data, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onErrRtnExecOrderAction(self, data, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onErrRtnForQuoteInsert(self, data, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnQuote(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onErrRtnQuoteInsert(self, data, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onErrRtnQuoteAction(self, data, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnForQuoteRsp(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnCFMMCTradingAccountToken(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onErrRtnBatchOrderAction(self, data, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnCombAction(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onErrRtnCombActionInsert(self, data, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryContractBank(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryParkedOrder(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryParkedOrderAction(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTradingNotice(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryBrokerTradingParams(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryBrokerTradingAlgos(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQueryCFMMCTradingAccountToken(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnFromBankToFutureByBank(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnFromFutureToBankByBank(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnRepealFromBankToFutureByBank(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnRepealFromFutureToBankByBank(self, data):
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
    def onRtnRepealFromBankToFutureByFutureManual(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnRepealFromFutureToBankByFutureManual(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnQueryBankBalanceByFuture(self, data):
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
    def onErrRtnRepealBankToFutureByFutureManual(self, data, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onErrRtnRepealFutureToBankByFutureManual(self, data, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onErrRtnQueryBankBalanceByFuture(self, data, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnRepealFromBankToFutureByFuture(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnRepealFromFutureToBankByFuture(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspFromBankToFutureByFuture(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspFromFutureToBankByFuture(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQueryBankAccountMoneyByFuture(self, data, error, id, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnOpenAccountByBank(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnCancelAccountByBank(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnChangeAccountByBank(self, data):
        """"""
        pass
    

########################################################################
class PositionBuffer(object):
    """用来缓存持仓的数据，处理上期所的数据返回分今昨的问题"""

    #----------------------------------------------------------------------
    def __init__(self, data, gatewayName):
        """Constructor"""
        self.symbol = data['InstrumentID']
        self.direction = posiDirectionMapReverse.get(data['PosiDirection'], '')
        
        self.todayPosition = EMPTY_INT
        self.ydPosition = EMPTY_INT
        self.todayPositionCost = EMPTY_FLOAT
        self.ydPositionCost = EMPTY_FLOAT
        
        # 通过提前创建持仓数据对象并重复使用的方式来降低开销
        pos = VtPositionData()
        pos.symbol = self.symbol
        pos.vtSymbol = self.symbol
        pos.gatewayName = gatewayName
        pos.direction = self.direction
        pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction]) 
        self.pos = pos
        
    #----------------------------------------------------------------------
    def updateShfeBuffer(self, data, size):
        """更新上期所缓存，返回更新后的持仓数据"""
        # 昨仓和今仓的数据更新是分在两条记录里的，因此需要判断检查该条记录对应仓位
        # 因为今仓字段TodayPosition可能变为0（被全部平仓），因此分辨今昨仓需要用YdPosition字段
        if data['YdPosition']:
            self.ydPosition = data['Position']
            self.ydPositionCost = data['PositionCost']   
        else:
            self.todayPosition = data['Position']
            self.todayPositionCost = data['PositionCost']        
            
        # 持仓的昨仓和今仓相加后为总持仓
        self.pos.position = self.todayPosition + self.ydPosition
        self.pos.ydPosition = self.ydPosition
        
        # 如果手头还有持仓，则通过加权平均方式计算持仓均价
        if self.todayPosition or self.ydPosition:
            self.pos.price = ((self.todayPositionCost + self.ydPositionCost)/
                              ((self.todayPosition + self.ydPosition) * size))
        # 否则价格为0
        else:
            self.pos.price = 0
            
        return copy(self.pos)
    
    #----------------------------------------------------------------------
    def updateBuffer(self, data, size):
        """更新其他交易所的缓存，返回更新后的持仓数据"""
        # 其他交易所并不区分今昨，因此只关心总仓位，昨仓设为0
        self.pos.position = data['Position']
        self.pos.ydPosition = 0
        
        if data['Position']:
            self.pos.price = data['PositionCost'] / (data['Position'] * size)
        else:
            self.pos.price = 0
            
        return copy(self.pos)    
    
    #----------------------------------------------------------------------
    def getPos(self):
        """获取当前的持仓数据"""
        return copy(self.pos)