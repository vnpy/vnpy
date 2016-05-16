# encoding: UTF-8

'''
vn.sgit的gateway接入

飞鼠接口的委托数据更新是分散在多个推送里的：
1. 下单后，通过onRtnOrder通知是否成功，没有ErrorID说明委托到了交易所
2. 后续的成交状态，通过onRtnTrade通知，用户自行累加
3. 撤单的确认，通过onRspOrderAction通知

为了获取实时的委托状态，需要用户自行把这三个数据合并起来，
因此在TdApi中维护了一个委托数据的缓存字典，对vn.trader系统中推送的是本地委托号，
在Gateway中和委托系统号对应起来

飞鼠的撤单需要使用：交易所代码+交易所的系统委托号，撤单时从缓存中
获取委托的系统编号
'''


import os
import json

from vnsgitmd import MdApi
from vnsgittd import TdApi
from sgitDataType import *
from vtGateway import *

# 以下为一些VT类型和SGIT类型的映射字典
# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = defineDict["Sgit_FTDC_OPT_LimitPrice"]
priceTypeMap[PRICETYPE_MARKETPRICE] = defineDict["Sgit_FTDC_OPT_AnyPrice"]
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = defineDict['Sgit_FTDC_D_Buy']
directionMap[DIRECTION_SHORT] = defineDict['Sgit_FTDC_D_Sell']
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {}
offsetMap[OFFSET_OPEN] = defineDict['Sgit_FTDC_OF_Open']
offsetMap[OFFSET_CLOSE] = defineDict['Sgit_FTDC_OF_Close']
offsetMap[OFFSET_CLOSETODAY] = defineDict['Sgit_FTDC_OF_CloseToday']
offsetMap[OFFSET_CLOSEYESTERDAY] = defineDict['Sgit_FTDC_OF_CloseYesterday']
offsetMapReverse = {v:k for k,v in offsetMap.items()}

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_CFFEX] = defineDict['Sgit_FTDC_EIDT_CFFEX']
exchangeMap[EXCHANGE_SHFE] = defineDict['Sgit_FTDC_EIDT_SHFE']
exchangeMap[EXCHANGE_CZCE] = defineDict['Sgit_FTDC_EIDT_CZCE']
exchangeMap[EXCHANGE_DCE] = defineDict['Sgit_FTDC_EIDT_DCE']
exchangeMap[EXCHANGE_SGE] = defineDict['Sgit_FTDC_EIDT_GOLD']
exchangeMap[EXCHANGE_UNKNOWN] = ''
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 持仓类型映射
posiDirectionMap = {}
posiDirectionMap[DIRECTION_NET] = defineDict["Sgit_FTDC_PD_Net"]
posiDirectionMap[DIRECTION_LONG] = defineDict["Sgit_FTDC_PD_Long"]
posiDirectionMap[DIRECTION_SHORT] = defineDict["Sgit_FTDC_PD_Short"]
posiDirectionMapReverse = {v:k for k,v in posiDirectionMap.items()}

# 委托状态类型映射
orderStatusMap = {}
orderStatusMap[STATUS_ALLTRADED] = defineDict["Sgit_FTDC_OST_AllTraded"]
orderStatusMap[STATUS_PARTTRADED] = defineDict["Sgit_FTDC_OST_PartTradedQueueing"]
orderStatusMap[STATUS_NOTTRADED] = defineDict["Sgit_FTDC_OST_NoTradeQueueing"]
orderStatusMap[STATUS_CANCELLED] = defineDict["Sgit_FTDC_OST_Canceled"]
orderStatusMapReverse = {v:k for k,v in orderStatusMap.items()}


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
        
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
        fileName = self.gatewayName + '_connect.json'
        fileName = os.getcwd() + '/sgitGateway/' + fileName
        
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
        if self.mdConnected:
            self.mdApi.close()
        if self.tdConnected:
            self.tdApi.close()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            # 飞鼠柜台的资金是主动推送的，因此无需查询
            self.qryFunctionList = [self.qryPosition]
            
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
            path = os.getcwd() + '/temp/' + self.gatewayName + '/'
            if not os.path.exists(path):
                os.makedirs(path)
            self.createFtdcMdApi(path)
            
            # 订阅数据流
            self.subscribeMarketTopic(0)             
            
            # 注册服务器地址
            self.registerFront(self.address)
            
            # 初始化连接，成功会调用onFrontConnected
            self.init(False)
            
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
            self.subQuot({'ContractID': str(subscribeReq.symbol)})
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
    def onFrontDisconnected(self, msg):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.mdConnected = False
    
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'行情服务器连接断开'
        self.gateway.onLog(log)       
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, i, last):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = True
            self.gateway.mdConnected = True
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'行情服务器登录完成'
            self.gateway.onLog(log)
            
            # 调用ready
            self.ready()
            
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
    def onRspUserLogout(self, data, error, i, last):
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
    
        # SGIT只有一档行情
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
        self.investorID = EMPTY_STRING      # 投资者代码
        
        self.frontID = EMPTY_INT            # 前置机编号
        self.sessionID = EMPTY_INT          # 会话编号
        
        self.localID = 0                    # 本地委托代码
        self.orderDict = {}                 # 缓存委托对象的字典
        self.localSysDict = {}              # key为本地委托代码，value为交易所系统代码
        self.cancelReqDict = {}             # key为本地委托代码，value为撤单请求
       
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
            path = os.getcwd() + '/temp/' + self.gatewayName + '/'
            if not os.path.exists(path):
                os.makedirs(path)
            self.createFtdcTraderApi(path)
            
            # 订阅数据流
            self.subscribePrivateTopic(0)            
            self.subscribePublicTopic(0)
            
            # 注册服务器地址
            self.registerFront(self.address)

            # 初始化连接，成功会调用onFrontConnected
            self.init(False)
            
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
        self.localID += 1
        strID = str(self.localID).rjust(12, '0')
        
        req = {}
        
        req['InstrumentID'] = orderReq.symbol
        req['LimitPrice'] = orderReq.price
        req['VolumeTotalOriginal'] = orderReq.volume
        
        # 下面如果由于传入的类型本接口不支持，则会返回空字符串
        try:
            req['OrderPriceType'] = priceTypeMap[orderReq.priceType]
            req['Direction'] = directionMap[orderReq.direction]
            req['CombOffsetFlag'] = offsetMap[orderReq.offset]
        except KeyError:
            return ''
            
        req['OrderRef'] = strID
        req['InvestorID'] = self.investorID
        req['UserID'] = self.userID
        req['BrokerID'] = self.brokerID
        
        req['CombHedgeFlag'] = defineDict['Sgit_FTDC_HF_Speculation']       # 投机单
        req['ContingentCondition'] = defineDict['Sgit_FTDC_CC_Immediately'] # 立即发单
        req['ForceCloseReason'] = defineDict['Sgit_FTDC_FCC_NotForceClose'] # 非强平
        req['IsAutoSuspend'] = 0                                             # 非自动挂起
        req['TimeCondition'] = defineDict['Sgit_FTDC_TC_GFD']               # 今日有效
        req['VolumeCondition'] = defineDict['Sgit_FTDC_VC_AV']              # 任意成交量
        req['MinVolume'] = 1                                                 # 最小成交量为1
        
        self.reqOrderInsert(req, self.reqID)
        
        # 返回订单号（字符串），便于某些算法进行动态管理
        vtOrderID = '.'.join([self.gatewayName, strID])
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        # 如果OrderSysID的数据尚未返回，则把撤单请求缓存下来后直接返回
        # 若已经返回，则获取strID对应的OrderSysID，并撤单
        strID = cancelOrderReq.orderID
        
        if strID not in self.localSysDict:
            self.cancelReqDict[strID] = cancelOrderReq
            return
        
        sysID = self.localSysDict[strID]
        
        self.reqID += 1

        req = {}
        req['InstrumentID'] = cancelOrderReq.symbol
        req['ExchangeID'] = exchangeMap[cancelOrderReq.exchange]
        req['OrderSysID'] = sysID
        req['ActionFlag'] = defineDict['Sgit_FTDC_AF_Delete']
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
    def onFrontDisconnected(self, msg):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.mdConnected = False
    
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'交易服务器连接断开'
        self.gateway.onLog(log)   
        
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        '''登陆回报'''
        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = True
            self.gateway.mdConnected = True
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易服务器登录完成'
            self.gateway.onLog(log)
            
            # 调用ready
            self.ready()
            
            # 查询投资者代码
            self.reqID += 1
            self.reqQryInvestor({}, self.reqID)                
            
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
    def onRspUserPasswordUpdate(self, data, error, n, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspOrderInsert(self, data, error, n, last):
        """发单错误（柜台）"""
        if error['ErrorID'] != 0:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspOrderAction(self, data, error, n, last):
        """撤单错误（柜台）"""
        # 获取委托对象
        sysID = data['OrderSysID']
        strID = data['OrderRef']
        
        if sysID in self.orderDict:
            order = self.orderDict[sysID]
        else:
            self.localSysDict[strID] = sysID
            
            order = VtOrderData()
            self.orderDict[sysID] = order
            
            order.gatewayName = self.gatewayName
            order.orderID = strID
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
        
        # 推送错误信息
        if error['ErrorID'] != 0:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
        else:
            order.status = STATUS_CANCELLED
            
        self.gateway.onOrder(order)
        
    #----------------------------------------------------------------------
    def onRspQryOrder(self, data, error, n, last):
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
    def onRspQryInvestor(self, data, error, n, last):
        """"""
        self.investorID = data['InvestorID']
        
        if last:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'投资者编码获取完成'
            self.gateway.onLog(log)        
    
            # 查询合约
            self.reqID += 1
            self.reqQryInstrument({}, self.reqID)              
        
    #----------------------------------------------------------------------
    def onRspQryInstrument(self, data, error, n, last):
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
        
        # 合约类型
        if contract.exchange == EXCHANGE_SGE:
            if '(' in contract.symbol:
                contract.productClass = PRODUCT_DEFER
            else:
                contract.productClass = PRODUCT_SPOT
        else:
            contract.productClass = PRODUCT_FUTURES
        
        # 推送
        self.gateway.onContract(contract)
        
        if last:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易合约信息获取完成'
            self.gateway.onLog(log)
        
    #----------------------------------------------------------------------
    def onRtnOrder(self, data, error):
        """报单回报"""    
        # 获取委托对象
        sysID = data['OrderSysID']
        strID = data['OrderRef']
        
        newID = int(strID)
        if newID > self.localID:
            self.localID = newID
        
        if sysID in self.orderDict:
            order = self.orderDict[sysID]
        else:
            self.localSysDict[strID] = sysID
            
            order = VtOrderData()
            self.orderDict[sysID] = order
            
            order.gatewayName = self.gatewayName
            order.orderID = strID
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
        order.symbol = data['InstrumentID']
        order.exchange = exchangeMapReverse[data['ExchangeID']]
        order.vtSymbol = order.symbol
        order.direction = directionMapReverse.get(data['Direction'], DIRECTION_UNKNOWN)
        order.offset = offsetMapReverse.get(data['CombOffsetFlag'], OFFSET_UNKNOWN)
        order.totalVolume = data['VolumeTotalOriginal']
        order.price = data['LimitPrice']

        # 推送错误信息
        if error['ErrorID'] == 0:
            # 如果没有错误信息，则认为委托有效未成交
            if not order.status:
                order.status = STATUS_NOTTRADED
        else:
            # 如果有错误信息，委托被自动撤单
            order.status = STATUS_CANCELLED
            
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)       
            
        # 推送
        self.gateway.onOrder(order)
        
        # 检查是否有待撤单请求
        if strID in self.cancelReqDict:
            req = self.cancelReqDict.pop(strID)
            self.cancelOrder(req)
        
    #----------------------------------------------------------------------
    def onRtnTrade(self, data):
        """成交回报"""
        # 更新委托
        sysID = data['OrderSysID']
        strID = data['OrderRef']
        
        if sysID in self.orderDict:
            order = self.orderDict[sysID]
        else:
            self.localSysDict[strID] = sysID
    
            order = VtOrderData()
            self.orderDict[sysID] = order
    
            order.gatewayName = self.gatewayName
            order.orderID = strID
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
    
        order.tradedVolume += data['Volume']
    
        if order.tradedVolume == order.totalVolume:
            order.status = STATUS_ALLTRADED
        else:
            order.status = STATUS_PARTTRADED        

        # 更新成交
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        trade.symbol = data['InstrumentID']
        trade.exchange = exchangeMapReverse[data['ExchangeID']]
        trade.vtSymbol = trade.symbol 
        
        trade.tradeID = data['TradeID']
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
        
        trade.orderID = order.orderID
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
        
        # 方向
        trade.direction = directionMapReverse.get(data['Direction'], '')
            
        # 开平
        trade.offset = offsetMapReverse.get(data['OffsetFlag'], '')
            
        # 价格、报单量等数值
        trade.price = data['Price']
        trade.volume = data['Volume']
        trade.tradeTime = data['TradeTime']

        # 推送
        self.gateway.onTrade(trade)
        self.gateway.onOrder(order)
        
    #----------------------------------------------------------------------
    def onRtnInstrumentStatus(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInvestorPositionDetail(self, data, error, n, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInvestorPosition(self, data, error, n, last):
        """持仓查询回报"""
        # 过滤空数据的情况
        if not data['InstrumentID']:
            return 
        
        pos = VtPositionData()
        pos.gatewayName = self.gatewayName
        
        # 保存代码
        pos.symbol = data['InstrumentID']
        pos.vtSymbol = pos.symbol       # 这里因为data中没有ExchangeID这个字段
        
        # 方向和持仓冻结数量
        pos.direction = posiDirectionMapReverse.get(data['PosiDirection'], '')
        if pos.direction == DIRECTION_NET or pos.direction == DIRECTION_LONG:
            pos.frozen = data['LongFrozen']
        elif pos.direction == DIRECTION_SHORT:   
            pos.frozen = data['ShortFrozen']
        
        # 持仓量
        pos.position = data['TodayPosition']
        pos.ydPosition = data['YdPosition']        
        
        # 持仓均价
        if pos.position:
            pos.price = data['PositionCost'] / pos.position
        
        # VT系统持仓名
        pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
        
        # 推送
        self.gateway.onPosition(pos)




#----------------------------------------------------------------------
def print_dict(d):
    """"""
    l = d.keys()
    l.sort()
    for k in l:
        print k, ':', d[k]
    