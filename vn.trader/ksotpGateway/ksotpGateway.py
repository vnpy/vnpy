# encoding: UTF-8

'''
vn.ksotp的gateway接入
'''


import os
import json

from vnksotpmd import MdApi
from vnksotptd import TdApi
from ksotpDataType import *
from vtGateway import *

# 以下为一些VT类型和CTP类型的映射字典
# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = defineDict["KS_OTP_OPT_LimitPrice"]
priceTypeMap[PRICETYPE_MARKETPRICE] = defineDict["KS_OTP_OPT_AnyPrice"]
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = defineDict['KS_OTP_D_Buy']
directionMap[DIRECTION_SHORT] = defineDict['KS_OTP_D_Sell']
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {}
offsetMap[OFFSET_OPEN] = defineDict['KS_OTP_OF_Open']
offsetMap[OFFSET_CLOSE] = defineDict['KS_OTP_OF_Close']
offsetMap[OFFSET_CLOSETODAY] = defineDict['KS_OTP_OF_CloseToday']
offsetMap[OFFSET_CLOSEYESTERDAY] = defineDict['KS_OTP_OF_CloseYesterday']
offsetMapReverse = {v:k for k,v in offsetMap.items()}

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_CFFEX] = 'CFFEX'
exchangeMap[EXCHANGE_SHFE] = 'SHFE'
exchangeMap[EXCHANGE_CZCE] = 'CZCE'
exchangeMap[EXCHANGE_DCE] = 'DCE'
exchangeMap[EXCHANGE_SSE] = 'SSE'
exchangeMap[EXCHANGE_SZSE] = 'SZSE'
exchangeMap[EXCHANGE_UNKNOWN] = ''
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 持仓类型映射
posiDirectionMap = {}
posiDirectionMap[DIRECTION_LONG] = defineDict["KSVOC_PD_Buy"]
posiDirectionMap[DIRECTION_SHORT] = defineDict["KSVOC_PD_Sell"]
posiDirectionMapReverse = {v:k for k,v in posiDirectionMap.items()}


########################################################################
class KsotpGateway(VtGateway):
    """金仕达期权接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='KSOTP'):
        """Constructor"""
        super(KsotpGateway, self).__init__(eventEngine, gatewayName)
        
        self.mdApi = KsotpMdApi(self)     # 行情API
        self.tdApi = KsotpTdApi(self)     # 交易API
        
        self.mdConnected = False        # 行情API连接状态，登录完成后为True
        self.tdConnected = False        # 交易API连接状态
        
        self.qryEnabled = False         # 是否要启动循环查询
        
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
        fileName = self.gatewayName + '_connect.json'
        fileName = os.getcwd() + '/ksotpGateway/' + fileName
        
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
            self.qryFunctionList = [self.qryAccount, self.qryPosition]
            
            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 2         # 查询触发点，金仕达接口查询非常慢，因此不适合频繁查询
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
class KsotpMdApi(MdApi):
    """金仕达期权的行情API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(KsotpMdApi, self).__init__()
        
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
    def onFrontConnected(self):
        """服务器连接"""
        self.connectionStatus = True
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'行情服务器连接成功'
        self.gateway.onLog(log)
        self.login()
    
    #----------------------------------------------------------------------  
    def onFrontDisconnected(self, n):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.mdConnected = False
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'行情服务器连接断开'
        self.gateway.onLog(log)        
           
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
        
        # CTP只有一档行情
        tick.bidPrice1 = data['BidPrice1']
        tick.bidVolume1 = data['BidVolume1']
        tick.askPrice1 = data['AskPrice1']
        tick.askVolume1 = data['AskVolume1']
        
        self.gateway.onTick(tick)
        
    #---------------------------------------------------------------------- 
    def onRspSubForQuoteRsp(self, data, error, n, last):
        """订阅期权询价"""
        pass
        
    #----------------------------------------------------------------------
    def onRspUnSubForQuoteRsp(self, data, error, n, last):
        """退订期权询价"""
        pass 
        
    #---------------------------------------------------------------------- 
    def onRtnForQuoteRsp(self, data):
        """期权询价推送"""
        pass        
        
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
            self.createOTPMdApi(path)
            
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
            req = {}
            req['InstrumentID'] = subscribeReq.symbol
            req['ExchangeID'] = subscribeReq.exchange
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
class KsotpTdApi(TdApi):
    """金仕达期权的交易API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(KsotpTdApi, self).__init__()
        
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
        
    ##----------------------------------------------------------------------
    #def onFrontConnected(self):
        #"""服务器连接"""
        #self.connectionStatus = True
        
        #log = VtLogData()
        #log.gatewayName = self.gatewayName
        #log.logContent = u'交易服务器连接成功'
        #self.gateway.onLog(log)
        
        #self.login()
    
    ##----------------------------------------------------------------------
    #def onFrontDisconnected(self, n):
        #"""服务器断开"""
        #self.connectionStatus = False
        #self.loginStatus = False
        #self.gateway.tdConnected = False
        
        #log = VtLogData()
        #log.gatewayName = self.gatewayName
        #log.logContent = u'交易服务器连接断开'
        #self.gateway.onLog(log)      
    
    ##----------------------------------------------------------------------
    #def onRspUserLogin(self, data, error, n, last):
        #"""登陆回报"""
        ## 如果登录成功，推送日志信息
        #if error['ErrorID'] == 0:
            #self.frontID = str(data['FrontID'])
            #self.sessionID = str(data['SessionID'])
            #self.loginStatus = True
            #self.gateway.mdConnected = True
            
            #log = VtLogData()
            #log.gatewayName = self.gatewayName
            #log.logContent = u'交易服务器登录完成'
            #self.gateway.onLog(log)
            
            ## 确认结算信息
            #req = {}
            #req['BrokerID'] = self.brokerID
            #req['InvestorID'] = self.userID
            #self.reqID += 1
            #self.reqSettlementInfoConfirm(req, self.reqID)              
                
        ## 否则，推送错误信息
        #else:
            #err = VtErrorData()
            #err.gatewayName = self.gateway
            #err.errorID = error['ErrorID']
            #err.errorMsg = error['ErrorMsg'].decode('gbk')
            #self.gateway.onError(err)
    
    ##----------------------------------------------------------------------
    #def onRspUserLogout(self, data, error, n, last):
        #"""登出回报"""
        ## 如果登出成功，推送日志信息
        #if error['ErrorID'] == 0:
            #self.loginStatus = False
            #self.gateway.tdConnected = False
            
            #log = VtLogData()
            #log.gatewayName = self.gatewayName
            #log.logContent = u'交易服务器登出完成'
            #self.gateway.onLog(log)
                
        ## 否则，推送错误信息
        #else:
            #err = VtErrorData()
            #err.gatewayName = self.gatewayName
            #err.errorID = error['ErrorID']
            #err.errorMsg = error['ErrorMsg'].decode('gbk')
            #self.gateway.onError(err)
    
    ##----------------------------------------------------------------------
    #def onRspUserPasswordUpdate(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspTradingAccountPasswordUpdate(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspOrderInsert(self, data, error, n, last):
        #"""发单错误（柜台）"""
        #err = VtErrorData()
        #err.gatewayName = self.gatewayName
        #err.errorID = error['ErrorID']
        #err.errorMsg = error['ErrorMsg'].decode('gbk')
        #self.gateway.onError(err)
    
    ##----------------------------------------------------------------------
    #def onRspOrderAction(self, data, error, n, last):
        #"""撤单错误（柜台）"""
        #err = VtErrorData()
        #err.gatewayName = self.gatewayName
        #err.errorID = error['ErrorID']
        #err.errorMsg = error['ErrorMsg'].decode('gbk')
        #self.gateway.onError(err)
    
    ##----------------------------------------------------------------------
    #def onRspQueryMaxOrderVolume(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspSettlementInfoConfirm(self, data, error, n, last):
        #"""确认结算信息回报"""
        #log = VtLogData()
        #log.gatewayName = self.gatewayName
        #log.logContent = u'结算信息确认完成'
        #self.gateway.onLog(log)
        
        ## 查询合约代码
        #self.reqID += 1
        #self.reqQryInstrument({}, self.reqID)
        
    ##----------------------------------------------------------------------
    #def onRspRemoveParkedOrder(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspRemoveParkedOrderAction(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspExecOrderInsert(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspExecOrderAction(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspForQuoteInsert(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQuoteInsert(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQuoteAction(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryOrder(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryTrade(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryInvestorPosition(self, data, error, n, last):
        #"""持仓查询回报"""
        #pos = VtPositionData()
        #pos.gatewayName = self.gatewayName
        
        ## 保存代码
        #pos.symbol = data['InstrumentID']
        #pos.vtSymbol = pos.symbol       # 这里因为data中没有ExchangeID这个字段
        
        ## 方向和持仓冻结数量
        #pos.direction = posiDirectionMapReverse.get(data['PosiDirection'], '')
        #if pos.direction == DIRECTION_NET or pos.direction == DIRECTION_LONG:
            #pos.frozen = data['LongFrozen']
        #elif pos.direction == DIRECTION_SHORT:   
            #pos.frozen = data['ShortFrozen']
        
        ## 持仓量
        #pos.position = data['Position']
        #pos.ydPosition = data['YdPosition']        
        
        ## 持仓均价
        #if pos.position:
            #pos.price = data['PositionCost'] / pos.position
        
        ## VT系统持仓名
        #pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
        
        ## 推送
        #self.gateway.onPosition(pos)
    
    ##----------------------------------------------------------------------
    #def onRspQryTradingAccount(self, data, error, n, last):
        #"""资金账户查询回报"""
        #account = VtAccountData()
        #account.gatewayName = self.gatewayName
        
        ## 账户代码
        #account.accountID = data['AccountID']
        #account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
        
        ## 数值相关
        #account.preBalance = data['PreBalance']
        #account.available = data['Available']
        #account.commission = data['Commission']
        #account.margin = data['CurrMargin']
        #account.closeProfit = data['CloseProfit']
        #account.positionProfit = data['PositionProfit']
        
        ## 这里的balance和快期中的账户不确定是否一样，需要测试
        #account.balance = (data['PreBalance'] - data['PreCredit'] - data['PreMortgage'] +
                           #data['Mortgage'] - data['Withdraw'] + data['Deposit'] +
                           #data['CloseProfit'] + data['PositionProfit'] + data['CashIn'] -
                           #data['Commission'])
        
        ## 推送
        #self.gateway.onAccount(account)
    
    ##----------------------------------------------------------------------
    #def onRspQryInvestor(self, data, error, n, last):
        #"""投资者查询回报"""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryTradingCode(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryInstrumentMarginRate(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryInstrumentCommissionRate(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryExchange(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryProduct(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryInstrument(self, data, error, n, last):
        #"""合约查询回报"""
        #contract = VtContractData()
        #contract.gatewayName = self.gatewayName

        #contract.symbol = data['InstrumentID']
        #contract.exchange = exchangeMapReverse[data['ExchangeID']]
        #contract.vtSymbol = contract.symbol #'.'.join([contract.symbol, contract.exchange])
        #contract.name = data['InstrumentName'].decode('GBK')
        
        ## 合约数值
        #contract.size = data['VolumeMultiple']
        #contract.priceTick = data['PriceTick']
        #contract.strikePrice = data['StrikePrice']
        #contract.underlyingSymbol = data['UnderlyingInstrID']
        
        ## 合约类型
        #if data['ProductClass'] == defineDict["KS_OTP_PC_Futures"]:
            #contract.productClass = PRODUCT_FUTURES
        ## 这里把期货和现货的期权统一为期权类型
        #elif data['ProductClass'] == defineDict["KS_OTP_PC_ETFOption"]: 
            #contract.productClass = PRODUCT_OPTION
        #elif data['ProductClass'] == defineDict["KS_OTP_PC_Options"]:
            #contract.productClass = PRODUCT_OPTION        
        #elif defineDict["KS_OTP_PC_Combination"]:
            #contract.productClass = PRODUCT_COMBINATION
        #else:
            #contract.productClass = PRODUCT_UNKNOWN
        
        ## 期权类型
        #if data['OptionsType'] == '1':
            #contract.optionType = OPTION_CALL
        #elif data['OptionsType'] == '2':
            #contract.optionType = OPTION_PUT
        
        ## 推送
        #self.gateway.onContract(contract)
        
        #if last:
            #log = VtLogData()
            #log.gatewayName = self.gatewayName
            #log.logContent = u'交易合约信息获取完成'
            #self.gateway.onLog(log)
    
    ##----------------------------------------------------------------------
    #def onRspQryDepthMarketData(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQrySettlementInfo(self, data, error, n, last):
        #"""查询结算信息回报"""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryTransferBank(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryInvestorPositionDetail(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryNotice(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQrySettlementInfoConfirm(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryInvestorPositionCombineDetail(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryCFMMCTradingAccountKey(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryEWarrantOffset(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryInvestorProductGroupMargin(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryExchangeMarginRate(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryExchangeMarginRateAdjust(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryExchangeRate(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQrySecAgentACIDMap(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryOptionInstrTradeCost(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryOptionInstrCommRate(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryExecOrder(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryForQuote(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryQuote(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryTransferSerial(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryAccountregister(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspError(self, error, n, last):
        #"""错误回报"""
        #err = VtErrorData()
        #err.gatewayName = self.gatewayName
        #err.errorID = error['ErrorID']
        #err.errorMsg = error['ErrorMsg'].decode('gbk')
        #self.gateway.onError(err)
    
    ##----------------------------------------------------------------------
    #def onRtnOrder(self, data):
        #"""报单回报"""
        ## 更新最大报单编号
        #newref = data['OrderRef']
        #self.orderRef = max(self.orderRef, int(newref))
        
        ## 创建报单数据对象
        #order = VtOrderData()
        #order.gatewayName = self.gatewayName
        
        ## 保存代码和报单号
        #order.symbol = data['InstrumentID']
        #order.exchange = exchangeMapReverse[data['ExchangeID']]
        #order.vtSymbol = order.symbol #'.'.join([order.symbol, order.exchange])
        
        #order.orderID = data['OrderRef']
        
        ## 方向
        #if data['Direction'] == '0':
            #order.direction = DIRECTION_LONG
        #elif data['Direction'] == '1':
            #order.direction = DIRECTION_SHORT
        #else:
            #order.direction = DIRECTION_UNKNOWN
            
        ## 开平
        #if data['CombOffsetFlag'] == '0':
            #order.offset = OFFSET_OPEN
        #elif data['CombOffsetFlag'] == '1':
            #order.offset = OFFSET_CLOSE
        #else:
            #order.offset = OFFSET_UNKNOWN
            
        ## 状态
        #if data['OrderStatus'] == '0':
            #order.status = STATUS_ALLTRADED
        #elif data['OrderStatus'] == '1':
            #order.status = STATUS_PARTTRADED
        #elif data['OrderStatus'] == '3':
            #order.status = STATUS_NOTTRADED
        #elif data['OrderStatus'] == '5':
            #order.status = STATUS_CANCELLED
        #else:
            #order.status = STATUS_UNKNOWN
            
        ## 价格、报单量等数值
        #order.price = data['LimitPrice']
        #order.totalVolume = data['VolumeTotalOriginal']
        #order.tradedVolume = data['VolumeTraded']
        #order.orderTime = data['InsertTime']
        #order.cancelTime = data['CancelTime']
        #order.frontID = data['FrontID']
        #order.sessionID = data['SessionID']
        
        ## CTP的报单号一致性维护需要基于frontID, sessionID, orderID三个字段
        ## 但在本接口设计中，已经考虑了CTP的OrderRef的自增性，避免重复
        ## 唯一可能出现OrderRef重复的情况是多处登录并在非常接近的时间内（几乎同时发单）
        ## 考虑到VtTrader的应用场景，认为以上情况不会构成问题
        #order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
        
        ## 推送
        #self.gateway.onOrder(order)
    
    ##----------------------------------------------------------------------
    #def onRtnTrade(self, data):
        #"""成交回报"""
        ## 创建报单数据对象
        #trade = VtTradeData()
        #trade.gatewayName = self.gatewayName
        
        ## 保存代码和报单号
        #trade.symbol = data['InstrumentID']
        #trade.exchange = exchangeMapReverse[data['ExchangeID']]
        #trade.vtSymbol = trade.symbol #'.'.join([trade.symbol, trade.exchange])
        
        #trade.tradeID = data['TradeID']
        #trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
        
        #trade.orderID = data['OrderRef']
        #trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
        
        ## 方向
        #trade.direction = directionMapReverse.get(data['Direction'], '')
            
        ## 开平
        #trade.offset = offsetMapReverse.get(data['OffsetFlag'], '')
            
        ## 价格、报单量等数值
        #trade.price = data['Price']
        #trade.volume = data['Volume']
        #trade.tradeTime = data['TradeTime']
        
        ## 推送
        #self.gateway.onTrade(trade)
    
    ##----------------------------------------------------------------------
    #def onRtnInstrumentStatus(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnTradingNotice(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnErrorConditionalOrder(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnExecOrder(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onErrRtnExecOrderInsert(self, data, error):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onErrRtnExecOrderAction(self, data, error):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onErrRtnForQuoteInsert(self, data, error):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnQuote(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onErrRtnQuoteInsert(self, data, error):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onErrRtnQuoteAction(self, data, error):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnForQuoteRsp(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryContractBank(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryParkedOrder(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryParkedOrderAction(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryTradingNotice(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryBrokerTradingParams(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQryBrokerTradingAlgos(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnFromBankToFutureByBank(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnFromFutureToBankByBank(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnRepealFromBankToFutureByBank(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnRepealFromFutureToBankByBank(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnFromBankToFutureByFuture(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnFromFutureToBankByFuture(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnRepealFromBankToFutureByFutureManual(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnRepealFromFutureToBankByFutureManual(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnQueryBankBalanceByFuture(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onErrRtnBankToFutureByFuture(self, data, error):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onErrRtnFutureToBankByFuture(self, data, error):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onErrRtnRepealBankToFutureByFutureManual(self, data, error):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onErrRtnRepealFutureToBankByFutureManual(self, data, error):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onErrRtnQueryBankBalanceByFuture(self, data, error):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnRepealFromBankToFutureByFuture(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnRepealFromFutureToBankByFuture(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspFromBankToFutureByFuture(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspFromFutureToBankByFuture(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRspQueryBankAccountMoneyByFuture(self, data, error, n, last):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnOpenAccountByBank(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnCancelAccountByBank(self, data):
        #""""""
        #pass
    
    ##----------------------------------------------------------------------
    #def onRtnChangeAccountByBank(self, data):
        #""""""
        #pass
    
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
            self.createOTPTraderApi(path)
            
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
    def sendOrder(self, orderReq):
        """发单"""
        self.reqID += 1
        self.orderRef += 1
        
        req = {}
        
        req['InstrumentID'] = orderReq.symbol
        req['LimitPrice'] = orderReq.price
        req['VolumeTotalOriginal'] = orderReq.volume
        
        # 下面如果由于传入的类型本接口不支持，则会返回空字符串
        try:
            req['OrderPriceType'] = priceTypeMap[orderReq.priceType]
            req['Direction'] = directionMap[orderReq.direction]
            req['OffsetFlag'] = offsetMap[orderReq.offset]
        except KeyError:
            return ''
            
        req['OrderRef'] = str(self.orderRef)
        req['InvestorID'] = self.userID
        req['UserID'] = self.userID
        req['BrokerID'] = self.brokerID
        
        req['HedgeFlag'] = defineDict['KS_OTP_HF_Speculation']       # 投机单
        req['ContingentCondition'] = defineDict['KS_OTP_CC_Immediately'] # 立即发单
        req['ForceCloseReason'] = defineDict['KS_OTP_FCC_NotForceClose'] # 非强平
        req['IsAutoSuspend'] = 0                                             # 非自动挂起
        req['TimeCondition'] = defineDict['KS_OTP_TC_GFD']               # 今日有效
        req['VolumeCondition'] = defineDict['KS_OTP_VC_AV']              # 任意成交量
        req['MinVolume'] = 1                                                 # 最小成交量为1
        
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
        
        req['ActionFlag'] = defineDict['KS_OTP_AF_Delete']
        req['BrokerID'] = self.brokerID
        req['InvestorID'] = self.userID
        
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
    def onRspError(self, error, n, last) :
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last) :
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
            
            # 确认结算信息
            req = {}
            req['BrokerID'] = self.brokerID
            req['InvestorID'] = self.userID
            self.reqID += 1
            self.reqSettlementInfoConfirm(req, self.reqID)              
                
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gateway
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspUserLogout(self, data, error, n, last) :
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
    def onRspUserPasswordUpdate(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspTradingAccountPasswordUpdate(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspOrderInsert(self, data, error, n, last) :
        """发单错误（柜台）"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspOrderAction(self, data, error, n, last) :
        """撤单错误（柜台）"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspQryOrder(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTrade(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInvestorPosition(self, data, error, n, last) :
        """持仓查询回报"""
        pos = VtPositionData()
        pos.gatewayName = self.gatewayName
        
        # 保存代码
        pos.symbol = data['InstrumentID']
        pos.exchange = exchangeMapReverse.get(data['ExchangeID'], EXCHANGE_UNKNOWN)
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
            pos.price = data['PositionCost'] / pos.position
        
        # VT系统持仓名
        pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
        
        # 推送
        self.gateway.onPosition(pos)
        
    #----------------------------------------------------------------------
    def onRspQryTradingAccount(self, data, error, n, last) :
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
        account.balance = (data['PreBalance'] + data['Mortgage'] - data['Withdraw'] + data['Deposit'] +
                           data['CloseProfit'] + data['PositionProfit'] + data['CashIn'] - data['Commission'])
        
        # 推送
        self.gateway.onAccount(account)
        
    #----------------------------------------------------------------------
    def onRspQryInvestor(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTradingCode(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryExchange(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInstrument(self, data, error, n, last) :
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
        contract.strikePrice = data['StrikePrice']
        contract.underlyingSymbol = data['UnderlyingInstrID']
        
        # 合约类型
        if data['ProductClass'] == defineDict["KS_OTP_PC_Futures"]:
            contract.productClass = PRODUCT_FUTURES
        # 这里把期货和现货的期权统一为期权类型
        elif data['ProductClass'] == defineDict["KS_OTP_PC_ETFOption"]: 
            contract.productClass = PRODUCT_OPTION
        elif data['ProductClass'] == defineDict["KS_OTP_PC_Options"]:
            contract.productClass = PRODUCT_OPTION        
        elif defineDict["KS_OTP_PC_Combination"]:
            contract.productClass = PRODUCT_COMBINATION
        else:
            contract.productClass = PRODUCT_UNKNOWN
        
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
    def onRspQryInvestorPositionDetail(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTradingNotice(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspExecOrderInsert(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspLockInsert(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspExecOrderAction(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryExecOrder(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryExecOrderVolume(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryLock(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryLockPosition(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryUnderlyingStockInfo(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryOTPInsCommRate(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInstrumentMarginRate(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryOTPAssignment(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryDepthMarketData(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspFromBankToStockByStock(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnFromBankToStockByStock(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspFromStockToBankByStock(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnFromStockToBankByStock(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnQueryBankBalanceByStock(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryContractBank(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQueryBankAccountMoneyByStock(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTransferSerial(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQrySettlementInfoConfirm(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspSettlementInfoConfirm(self, data, error, n, last) :
        """确认结算信息回报"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'结算信息确认完成'
        self.gateway.onLog(log)
        
        # 查询合约代码
        self.reqID += 1
        self.reqQryInstrument({}, self.reqID)
        
    #----------------------------------------------------------------------
    def onRspQrySettlementInfo(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInvestorTradeLevel(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryPurchaseLimitAmt(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryPositionLimitVol(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryHistoryOrder(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryHistoryTrade(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryHistoryAssignment(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryDelivDetail(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspAutoExecOrderAction(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspCombActionInsert(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryInvestorCombinePosition(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryCombActionVolume(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspFundOutCreditApply(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryFundOutCredit(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryFundOutCreditApply(self, data, error, n, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnOrder(self, data) :
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
        if data['OffsetFlag'] == '0':
            order.offset = OFFSET_OPEN
        elif data['OffsetFlag'] == '1':
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
        order.price = data['LimitPrice']
        order.totalVolume = data['VolumeTotalOriginal']
        order.tradedVolume = data['VolumeTraded']
        order.orderTime = data['InsertTime']
        order.cancelTime = data['CancelTime']
        order.frontID = data['FrontID']
        order.sessionID = data['SessionID']
        
        # CTP的报单号一致性维护需要基于frontID, sessionID, orderID三个字段
        # 但在本接口设计中，已经考虑了CTP的OrderRef的自增性，避免重复
        # 唯一可能出现OrderRef重复的情况是多处登录并在非常接近的时间内（几乎同时发单）
        # 考虑到VtTrader的应用场景，认为以上情况不会构成问题
        order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
        
        # 推送
        self.gateway.onOrder(order)
        
    #----------------------------------------------------------------------
    def onRtnTrade(self, data) :
        """成交回报"""
        # 创建报单数据对象
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        # 保存代码和报单号
        trade.symbol = data['InstrumentID']
        trade.exchange = exchangeMapReverse[data['ExchangeID']]
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
        trade.price = data['Price']
        trade.volume = data['Volume']
        trade.tradeTime = data['TradeTime']
        
        # 推送
        self.gateway.onTrade(trade)
        
    #----------------------------------------------------------------------
    def onRtnExecOrder(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnLock(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnInstrumentStatus(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnTradingNotice(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnCombAction(self, data) :
        """"""
        pass
            
    
        
    


#----------------------------------------------------------------------
def test():
    """测试"""
    from PyQt4 import QtCore
    import sys
    
    def print_log(event):
        log = event.dict_['data']
        print ':'.join([log.logTime, log.logContent])
    
    app = QtCore.QCoreApplication(sys.argv)    

    eventEngine = EventEngine()
    eventEngine.register(EVENT_LOG, print_log)
    eventEngine.start()
    
    gateway = KsotpGateway(eventEngine)
    gateway.connect()
    
    sys.exit(app.exec_())


if __name__ == '__main__':
    test()