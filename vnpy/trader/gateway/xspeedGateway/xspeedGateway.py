# encoding: UTF-8

'''
vn.xspeed的gateway接入
'''

import os
import json
import time
from copy import copy

from vnpy.api.xspeed import MdApi, TdApi, defineDict
from vnpy.trader.vtGateway import *

# 以下为一些VT类型和XSPEED类型的映射字典
# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = defineDict["DFITC_LIMITORDER"]
priceTypeMap[PRICETYPE_MARKETPRICE] = defineDict["DFITC_MKORDER"]
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = defineDict['DFITC_SPD_BUY']
directionMap[DIRECTION_SHORT] = defineDict['DFITC_SPD_SELL']
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {}
offsetMap[OFFSET_OPEN] = defineDict['DFITC_SPD_OPEN']
offsetMap[OFFSET_CLOSE] = defineDict['DFITC_SPD_CLOSE']
offsetMap[OFFSET_CLOSETODAY] = defineDict['DFITC_SPD_CLOSETODAY']
#offsetMap[OFFSET_CLOSEYESTERDAY] = defineDict['DFITC_SPD_CLOSE']
offsetMapReverse = {v:k for k,v in offsetMap.items()}


# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_CFFEX] = defineDict['DFITC_EXCHANGE_CFFEX']
exchangeMap[EXCHANGE_SHFE] = defineDict['DFITC_EXCHANGE_SHFE']
exchangeMap[EXCHANGE_CZCE] = defineDict['DFITC_EXCHANGE_CZCE']
exchangeMap[EXCHANGE_DCE] = defineDict['DFITC_EXCHANGE_DCE']
exchangeMap[EXCHANGE_UNKNOWN] = ''
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 合约类型映射
productMap = {}
productMap[PRODUCT_FUTURES] = defineDict["DFITC_COMM_TYPE"]
productMap[PRODUCT_OPTION] = defineDict["DFITC_OPT_TYPE"]
productMapReverse = {v:k for k, v in productMap.items()}

# 委托状态类型映射
orderStatusMap = {}
orderStatusMap[STATUS_ALLTRADED] = defineDict["DFITC_SPD_FILLED"]
orderStatusMap[STATUS_PARTTRADED] = defineDict["DFITC_SPD_PARTIAL"]
orderStatusMap[STATUS_NOTTRADED] = defineDict["DFITC_SPD_IN_QUEUE"]
orderStatusMap[STATUS_CANCELLED] = defineDict["DFITC_SPD_CANCELED"]
orderStatusMapReverse = {v:k for k,v in orderStatusMap.items()}
orderStatusMapReverse[defineDict["DFITC_SPD_PARTIAL_CANCELED"]] = STATUS_CANCELLED


########################################################################
class XspeedGateway(VtGateway):
    """XSPEED接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='XSPEED'):
        """Constructor"""
        super(XspeedGateway, self).__init__(eventEngine, gatewayName)
        
        self.mdApi = XspeedMdApi(self)     # 行情API
        self.tdApi = XspeedTdApi(self)     # 交易API
        
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
    def qryFuturesPosition(self):
        """查询持仓"""
        self.tdApi.qryFuturesPosition()
        
    #----------------------------------------------------------------------
    def qryOptionPosition(self):
        """查询期权持仓"""
        self.tdApi.qryOptionPosition()        
        
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
            self.qryFunctionList = [self.qryAccount, self.qryFuturesPosition, self.qryOptionPosition]
            
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
class XspeedMdApi(MdApi):
    """XSPEED行情API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(XspeedMdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.subscribedSymbols = set()      # 已订阅合约代码        
        
        self.accountID = EMPTY_STRING          # 账号
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
            self.createDFITCMdApi()

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
            self.subscribeMarketData(str(subscribeReq.symbol), self.reqID)
            
        self.subscribedSymbols.add(subscribeReq)   
        
    #----------------------------------------------------------------------
    def login(self):
        """登录"""
        # 如果填入了用户名密码等，则登录
        if self.accountID and self.password:
            self.reqID += 1
            req = {}
            req['accountID'] = self.accountID
            req['passwd'] = self.password
            req['lRequestID'] = self.reqID
            self.reqUserLogin(req)    
    
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
    def onRspUserLogin(self, data, error) :
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['nErrorID'] == 0:
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
            err.errorID = error['nErrorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
            
    #----------------------------------------------------------------------
    def onRspUserLogout(self, data, error) :
        """登出回报"""
        # 如果登出成功，推送日志信息
        if error['nErrorID'] == 0:
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
            err.errorID = error['nErrorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspError(self, error) :
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['nErrorID']
        err.errorMsg = error['errorMsg'].decode('gbk')
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspSubMarketData(self, data, error) :
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspUnSubMarketData(self, data, error) :
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSubForQuoteRsp(self, data, error) :
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspUnSubForQuoteRsp(self, data, error) :
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onMarketData(self, data) :
        """行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
    
        tick.symbol = data['instrumentID']
        tick.exchange = exchangeMapReverse.get(data['exchangeID'], u'未知')
        tick.vtSymbol = tick.symbol #'.'.join([tick.symbol, EXCHANGE_UNKNOWN])
    
        tick.lastPrice = data['lastPrice']
        tick.volume = data['Volume']
        tick.openInterest = data['openInterest']
        tick.time = '.'.join([data['UpdateTime'], str(data['UpdateMillisec']/100)])
        tick.date = data['tradingDay']
    
        tick.openPrice = data['openPrice']
        tick.highPrice = data['highestPrice']
        tick.lowPrice = data['lowestPrice']
        tick.preClosePrice = data['preClosePrice']
    
        tick.upperLimit = data['upperLimitPrice']
        tick.lowerLimit = data['lowerLimitPrice']
    
        tick.bidPrice1 = data['BidPrice1']
        tick.bidVolume1 = data['BidVolume1']
        tick.askPrice1 = data['AskPrice1']
        tick.askVolume1 = data['AskVolume1']
    
        self.gateway.onTick(tick)
    
    #----------------------------------------------------------------------
    def onCustomMarketData(self, data) :
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRtnForQuoteRsp(self, data) :
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspTradingDay(self, data) :
        """"""
        pass


########################################################################
class XspeedTdApi(TdApi):
    """XSPEED交易API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(XspeedTdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        self.localID = EMPTY_INT           # 订单编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.accountID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.address = EMPTY_STRING         # 服务器地址
        
        self.sessionID = EMPTY_INT          # 会话编号
        
        self.posDict = {}                   # 缓存持仓数据的字典
        self.optionPosReqID = 0             # 期权持仓查询ID
        self.futuresPosReqID = 0            # 期货持仓查询ID
        self.optionPosCompleted = False
        self.futuresPosCompleted = False
        
        self.orderDict = {}                 # 缓存委托数据的字典
        self.spdOrderDict = {}              # 飞创柜台委托号字典
        self.contractDict = {}              # 缓存合约数据的字典
    
    #----------------------------------------------------------------------
    def connect(self, accountID, password, address):
        """初始化连接"""
        self.accountID = accountID                # 账号
        self.password = password            # 密码
        self.address = address              # 服务器地址
        
        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            self.createDFITCTraderApi()
            
            # 初始化连接，成功会调用onFrontConnected
            self.init(self.address)
            
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
            req['passwd'] = self.password
            req['lRequestID'] = self.reqID
            self.reqUserLogin(req)  
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户"""
        self.reqID += 1
        req = {}
        req['lRequestID'] = self.reqID
        req['accountID'] = self.accountID
        self.reqQryCustomerCapital(req)
        
    #----------------------------------------------------------------------
    def qryFuturesPosition(self):
        """查询期货持仓"""
        # 清空缓存
        self.posDict.clear()
        
        self.reqID += 1
        req = {}
        req['lRequestID'] = self.reqID
        req['accountID'] = self.accountID
        req['instrumentType'] = defineDict["DFITC_COMM_TYPE"]
        self.reqQryPosition(req)
        self.futuresPosReqID = self.reqID
        
    #----------------------------------------------------------------------
    def qryOptionPosition(self):
        """查询期权持仓"""
        self.posDict.clear()
        
        self.reqID += 1
        req = {}
        req['lRequestID'] = self.reqID
        req['accountID'] = self.accountID
        req['instrumentType'] = defineDict["DFITC_OPT_TYPE"]
        self.reqQryPosition(req)        
        self.optionPosReqID = self.reqID
    
    #----------------------------------------------------------------------
    def qryContracts(self):
        """查询合约"""
        # 查询期货合约代码
        self.reqID += 1
        req = {}
        req['lRequestID'] = self.reqID
        req['instrumentType'] = defineDict["DFITC_COMM_TYPE"]
        self.reqQryExchangeInstrument(req)      
    
        sleep(1)
    
        # 查询期权合约代码
        self.reqID += 1
        req = {}
        req['lRequestID'] = self.reqID
        req['instrumentType'] = defineDict["DFITC_OPT_TYPE"]
        self.reqQryExchangeInstrument(req)       
        
    #----------------------------------------------------------------------
    def qryTrade(self):
        """查询成交"""
        # 查询成交
        self.reqID += 1
        req = {}
        req['lRequestID'] = self.reqID
        req['accountID'] = self.accountID
        req['instrumentType'] = defineDict["DFITC_COMM_TYPE"]
        self.reqQryMatchInfo(req) 
    
        sleep(1)
    
        self.reqID += 1
        req = {}
        req['lRequestID'] = self.reqID
        req['accountID'] = self.accountID
        req['instrumentType'] = defineDict["DFITC_OPT_TYPE"]
        self.reqQryMatchInfo(req)     
        
    #----------------------------------------------------------------------
    def qryOrder(self):
        """查询委托"""
        # 查询委托
        self.reqID += 1
        req = {}
        req['lRequestID'] = self.reqID
        req['accountID'] = self.accountID
        req['instrumentType'] = defineDict["DFITC_COMM_TYPE"]
        self.reqQryOrderInfo(req)
    
        sleep(1)
    
        self.reqID += 1
        req = {}
        req['lRequestID'] = self.reqID
        req['accountID'] = self.accountID
        req['instrumentType'] = defineDict["DFITC_OPT_TYPE"]
        self.reqQryOrderInfo(req)                   
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        self.reqID += 1
        self.localID += 1

        req = {}
        req['instrumentID'] = orderReq.symbol
        req['insertPrice'] = orderReq.price
        req['orderAmount'] = orderReq.volume
        
        # 下面如果由于传入的类型本接口不支持，则会返回空字符串
        try:
            req['orderType'] = priceTypeMap[orderReq.priceType]
            req['buySellType'] = directionMap[orderReq.direction]
            req['openCloseType'] = offsetMap[orderReq.offset]
        except KeyError:
            return ''
            
        req['localOrderID'] = self.localID
        req['accountID'] = self.accountID
        req['speculator'] = defineDict['DFITC_SPD_SPECULATOR']       # 投机单
        req['minMatchAmount'] = 1                                    # 最小成交量为1
        req['lRequestID'] = self.reqID
        
        # 合约类型获取
        contract = self.contractDict.get(orderReq.symbol, None)
        if contract:
            req['instrumentType'] = productMap.get(contract.productClass, '')
        
        self.reqInsertOrder(req)
        
        # 返回订单号（字符串），便于某些算法进行动态管理
        vtOrderID = '.'.join([self.gatewayName, str(self.localID)])
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.reqID += 1

        req = {}
        req['instrumentID'] = cancelOrderReq.symbol
        req['localOrderID'] = int(cancelOrderReq.orderID)
        req['accountID'] = self.accountID
        req['lRequestID'] = self.reqID
        
        # 添加柜台委托号字段
        localID = int(cancelOrderReq.orderID)
        if localID in self.spdOrderDict:
            req['spdOrderID'] = self.spdOrderDict[localID]
            del req['localOrderID']

        self.reqCancelOrder(req)
        
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
    def onRspUserLogin(self, data, error) :
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['nErrorID'] == 0:
            self.sessionID = data['sessionID']
            
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
            err.errorID = error['nErrorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspUserLogout(self, data, error) :
        """登出回报"""
        # 如果登出成功，推送日志信息
        if error['nErrorID'] == 0:
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
            err.errorID = error['nErrorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspInsertOrder(self, data, error) :
        """发单错误（柜台）"""
        if error['nErrorID']:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            order.symbol = error['instrumentID']
            order.vtSymbol = order.symbol
            order.orderID = str(error['localOrderID'])
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            order.sessionID = error['sessionID']
            order.status = STATUS_REJECTED      
            self.gateway.onOrder(order)

            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['nErrorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspCancelOrder(self, data, error) :
        """撤单错误（柜台）"""
        if error['nErrorID']:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['nErrorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRtnErrorMsg(self, error) :
        """错误回报"""
        if error['nErrorID']:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['nErrorID']
            err.errorMsg = error['errorMsg'].decode('gbk')
            self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRtnMatchedInfo(self, data) :
        """成交回报"""
        # 更新成交信息
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        # 保存代码和报单号
        trade.symbol = data['instrumentID']
        trade.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_UNKNOWN)
        trade.vtSymbol = trade.symbol
        
        trade.tradeID = data['matchID']
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
        
        trade.orderID = str(data['localOrderID'])
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])

        trade.direction = directionMapReverse.get(data['buySellType'], DIRECTION_UNKNOWN)
        trade.offset = offsetMapReverse.get(data['openCloseType'], OFFSET_UNKNOWN)
            
        trade.price = data['insertPrice']
        trade.volume = data['matchedAmount']
        trade.tradeTime = data['matchedTime']
        
        # 推送
        self.gateway.onTrade(trade)
        
        # 获取报单数据对象
        localID = data['localOrderID']
        if localID not in self.orderDict:
            return
        order = self.orderDict[localID]
        
        order.status = orderStatusMapReverse.get(data['orderStatus'], STATUS_UNKNOWN)
        order.tradedVolume += trade.volume
        
        # 推送
        self.gateway.onOrder(copy(order))        
        
    #----------------------------------------------------------------------
    def onRtnOrder(self, data) :
        """报单回报"""
        # 更新最大报单编号
        newLocalID = data['localOrderID']
        self.localID = max(self.localID, newLocalID)
        self.spdOrderDict[newLocalID] = data['spdOrderID']
        
        # 获取报单数据对象
        if newLocalID in self.orderDict:
            order = self.orderDict[newLocalID]
        else:
            order = VtOrderData()
            self.orderDict[newLocalID] = order
            order.gatewayName = self.gatewayName
        
            # 保存后续不会变化的数据
            order.symbol = data['instrumentID']
            order.exchange = exchangeMapReverse[data['exchangeID']]
            order.vtSymbol = order.symbol
            
            order.orderID = str(newLocalID)
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.direction = directionMapReverse.get(data['buySellType'], DIRECTION_UNKNOWN)
            order.offset = offsetMapReverse.get(data['openCloseType'], OFFSET_UNKNOWN)

            # 价格、报单量等数值
            order.price = data['insertPrice']
            order.totalVolume = data['orderAmount']
            order.sessionID = data['sessionID']
            order.orderTime = time.strftime('%H:%M:%S')
        
        order.status = orderStatusMapReverse.get(data['orderStatus'], STATUS_UNKNOWN)
        
        # 推送
        self.gateway.onOrder(copy(order))
        
    #----------------------------------------------------------------------
    def onRtnCancelOrder(self, data) :
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
            order.symbol = data['instrumentID']
            order.exchange = exchangeMapReverse[data['exchangeID']]
            order.vtSymbol = order.symbol
            
            order.orderID = str(newLocalID)
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.direction = directionMapReverse.get(data['buySellType'], DIRECTION_UNKNOWN)
            order.offset = offsetMapReverse.get(data['openCloseType'], OFFSET_UNKNOWN)

            # 价格、报单量等数值
            order.price = data['insertPrice']
            order.totalVolume = data['orderAmount']
            order.sessionID = data['sessionID']            
        
        order.status = orderStatusMapReverse.get(data['orderStatus'], STATUS_UNKNOWN)
        order.cancelTime = data['canceledTime']
        
        # 推送
        self.gateway.onOrder(copy(order))
        
    #----------------------------------------------------------------------
    def onRspQryOrderInfo(self, data, error, last) :
        """查询委托回报"""
        if data['instrumentID']:        
            # 更新最大报单编号
            newLocalID = data['localOrderID']
            self.localID = max(self.localID, int(newLocalID))
            self.spdOrderDict[newLocalID] = data['spdOrderID']
            
            # 获取报单数据对象
            if newLocalID in self.orderDict:
                order = self.orderDict[newLocalID]
            else:
                order = VtOrderData()
                self.orderDict[newLocalID] = order
                order.gatewayName = self.gatewayName
            
                # 保存后续不会变化的数据
                order.symbol = data['instrumentID']
                order.exchange = exchangeMapReverse[data['exchangeID']]
                order.vtSymbol = order.symbol
                
                order.orderID = str(newLocalID)
                order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
                
                order.direction = directionMapReverse.get(data['buySellType'], DIRECTION_UNKNOWN)
                order.offset = offsetMapReverse.get(data['openClose'], OFFSET_UNKNOWN)
    
                order.price = data['insertPrice']
                order.totalVolume = data['orderAmount']
                #order.sessionID = data['sessionID']         
    
            order.status = orderStatusMapReverse.get(data['orderStatus'], STATUS_UNKNOWN)
            order.tradedVolume = data['matchedAmount']
            order.orderTime = data['commTime']
        
            # 推送
            self.gateway.onOrder(copy(order))
        
        if last:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'查询委托完成'
            self.gateway.onLog(log)        
        
    #----------------------------------------------------------------------
    def onRspQryMatchInfo(self, data, error, last) :
        """"""
        if data['instrumentID']:        
            # 创建报单数据对象
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            
            # 保存代码和报单号
            trade.symbol = data['instrumentID']
            trade.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_UNKNOWN)
            trade.vtSymbol = trade.symbol #'.'.join([trade.symbol, trade.exchange])
            
            trade.tradeID = data['matchedID']
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
            
            trade.orderID = str(data['localOrderID'])
            trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
            
            # 方向
            trade.direction = directionMapReverse.get(data['buySellType'], DIRECTION_UNKNOWN)
                
            # 开平
            trade.offset = offsetMapReverse.get(data['openClose'], OFFSET_UNKNOWN)
                
            # 价格、报单量等数值
            trade.price = data['matchedPrice']
            trade.volume = data['matchedAmount']
            trade.tradeTime = data['matchedTime']
            
            # 推送
            self.gateway.onTrade(trade)
        
        if last:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'查询成交完成'
            self.gateway.onLog(log)        
        
    #----------------------------------------------------------------------
    def onRspQryPosition(self, data, error, last) :
        """持仓查询回报"""
        # 忽略空数据
        if data['instrumentID']:
            # 获取缓存字典中的持仓对象，若无则创建并初始化
            positionName = '.'.join([data['instrumentID'], str(data['buySellType'])])
    
            if positionName in self.posDict:
                pos = self.posDict[positionName]
            else:
                pos = VtPositionData()
                self.posDict[positionName] = pos
    
                pos.gatewayName = self.gatewayName
    
                # 保存代码
                pos.symbol = data['instrumentID']
                pos.vtSymbol = pos.symbol       # 这里因为data中没有ExchangeID这个字段
    
                # 方向
                pos.direction = directionMapReverse.get(data['buySellType'], '')
    
                # VT系统持仓名
                pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])            
    
            # 持仓量
            if data['positionAmount']:
                pos.position = data['positionAmount']
    
            if data['lastAmount']:
                pos.ydPosition = data['lastAmount']        
    
            # 持仓均价
            pos.price = data['positionAvgPrice']
            
        # 查询完成后推送
        if last:
            for pos in self.posDict.values():
                self.gateway.onPosition(pos)
        
    #----------------------------------------------------------------------
    def onRspCustomerCapital(self, data, error, last) :
        """资金账户查询回报"""
        if not data['accountID']:
            return
        
        account = VtAccountData()
        account.gatewayName = self.gatewayName
    
        # 账户代码
        account.accountID = data['accountID']
        account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
    
        # 数值相关
        account.preBalance = data['preEquity']
        account.available = data['available']
        account.commission = data['fee']
        account.margin = data['margin']
        account.closeProfit = data['closeProfitLoss']
        account.positionProfit = data['positionProfitLoss']
        account.balance = data['todayEquity'] 
        account.marketValue = account.balance + data['optMarketValue']
        
        # 推送
        self.gateway.onAccount(account)
        
    #----------------------------------------------------------------------
    def onRspQryExchangeInstrument(self, data, error, last) :
        """合约查询回报"""
        contract = VtContractData()
        contract.gatewayName = self.gatewayName

        contract.symbol = data['instrumentID']
        contract.exchange = exchangeMapReverse.get(data['exchangeID'], EXCHANGE_UNKNOWN)
        contract.vtSymbol = contract.symbol #'.'.join([contract.symbol, contract.exchange])
        if data['VarietyName'] == contract.symbol:
            contract.name = data['VarietyName']
        else:
            contract.name = data['VarietyName'].decode('GBK') + contract.symbol
        
        # 合约数值
        contract.size = int(data['contractMultiplier'])
        contract.priceTick = data['minPriceFluctuation']
        contract.strikePrice = data['strikePrice']
        contract.underlyingSymbol = data['underlying']
        contract.expiryDate = data['instrumentMaturity'].replace('.', '')
        
        # 合约类型
        contract.productClass = productMapReverse.get(data['instrumentType'], 
                                                      PRODUCT_UNKNOWN)
        
        # 期权类型
        if data['optionType'] == 1:
            contract.optionType = OPTION_CALL
        elif data['optionType'] == 2:
            contract.optionType = OPTION_PUT
        
        # 推送
        self.gateway.onContract(contract)
        self.contractDict[contract.symbol] = contract
        
        if last and contract.productClass == PRODUCT_OPTION:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易合约信息获取完成'
            self.gateway.onLog(log)
            
            self.qryTrade()
            sleep(1)
            self.qryOrder()
        
    #----------------------------------------------------------------------
    def onRspArbitrageInstrument(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQrySpecifyInstrument(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryPositionDetail(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnTradingNotice(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspResetPassword(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onnRspQryTradeCode(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspBillConfirm(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onnRspEquityComputMode(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryBill(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspConfirmProductInfo(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspTradingDay(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQuoteInsert(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnQuoteInsert(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQuoteCancel(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnQuoteCancel(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnQuoteMatchedInfo(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspCancelAllOrder(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryQuoteNotice(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspForQuote(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnForQuote(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryQuoteOrderInfo(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryForQuote(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTransferBank(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTransferSerial(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspFromBankToFutureByFuture(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspFromFutureToBankByFuture(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnFromBankToFutureByFuture(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnFromFutureToBankByFuture(self, data, error) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnRepealFromFutureToBankByBank(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryExchangeStatus(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRtnExchangeStatus(self, data) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryDepthMarketData(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspQryTradeCode(self, data, error, last) :
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspEquityComputMode(self, data) :
        """"""
        pass
        