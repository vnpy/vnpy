# encoding: UTF-8

'''
vn.ksgold的gateway接入

金仕达黄金接口在用户登录后，并不提供之前的Order和Trade数据主动推送，
而是需要用户自行查询，因此API里做了初始化后的查询设计。
'''

import os
import json
import time

from vnksgoldtd import TdApi
from ksgoldDataType import *
from vtGateway import *

# 以下类型映射参考的是原生API里的Constant.h

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = '0'
directionMap[DIRECTION_SHORT] = '1'
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {}
offsetMap[OFFSET_OPEN] = '0'
offsetMap[OFFSET_CLOSE] = '1'
offsetMapReverse = {v:k for k,v in offsetMap.items()}


########################################################################
class KsgoldGateway(VtGateway):
    """金仕达黄金接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='KSGOLD'):
        """Constructor"""
        super(KsgoldGateway, self).__init__(eventEngine, gatewayName)

        self.tdApi = KsgoldTdApi(self)  # 黄金接口只有交易API
        self.tdConnected = False        # 交易API连接状态
        self.qryEnabled = False         # 是否要启动循环查询
        
        self.orderInited = False        # 委托初始化查询
        self.tradeInited = False        # 成交初始化查询
        
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
        fileName = self.gatewayName + '_connect.json'
        fileName = os.getcwd() + '/ksgoldGateway/' + fileName
        
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
            address = str(setting['address'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 创建行情和交易接口对象
        self.tdApi.connect(accountID, password, address)
        
        # 初始化并启动查询
        self.initQuery()
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        self.tdApi.subscribe(subscribeReq)
        
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
        if self.tdConnected:
            self.tdApi.close()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        # 需要循环的查询函数列表
        self.qryFunctionList = [self.qryAccount, self.qryPosition]
        
        self.qryCount = 0           # 查询触发倒计时
        self.qryTrigger = 2         # 查询触发点
        self.qryNextFunction = 0    # 上次运行的查询函数索引
    
    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        self.qryCount += 1
        
        if self.qryCount > self.qryTrigger:
            # 清空倒计时
            self.qryCount = 0
            
            # 如果尚未完成委托查询则先查询委托
            if not self.orderInited:
                self.tdApi.getOrder()
            # 然后如果未完成成交查询则再查询成交
            elif not self.tradeInited:
                self.tdApi.getTrade()
            else:
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
        if self.qryEnabled:
            self.eventEngine.register(EVENT_TIMER, self.query)
    
    #----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled
    

########################################################################
class KsgoldTdApi(TdApi):
    """金仕达黄金交易API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(KsgoldTdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        self.orderRef = EMPTY_INT           # 订单编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.accountID = EMPTY_STRING       # 账号
        self.password = EMPTY_STRING        # 密码
        self.memberID = EMPTY_STRING        # 会员代码（应该是银行）
        self.address = EMPTY_STRING         # 服务器地址
        
        self.seatID = EMPTY_STRING;         # 席位号
        self.tradeCode = EMPTY_STRING       # 交易编码
        
        self.subscribedSymbols = set()      # 已订阅合约代码    
        
        self.orderDict = {}                 # 委托字典，用于缓存委托对象，key为整数
        
        # 循环登录相关
        self.loginThread = None
        
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
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
            self.seatID = str(data['SeatNo'])
            self.tradeCode = str(data['tradeCode'])
            
            self.loginStatus = True
            self.gateway.tdConnected = True
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易服务器登录完成'
            self.gateway.onLog(log)
            
            # 重新订阅之前订阅的合约
            for subscribeReq in self.subscribedSymbols:
                self.subscribe(subscribeReq)    
                            
            # 查询合约信息
            self.reqID += 1
            self.reqQryInstrument({}, self.reqID)
            
            # 启动查询
            self.gateway.startQuery()            

        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
            
            if error['ErrorID'] == -8:
                self.login()
    
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
    def onNtyMktStatus(self, data, error, n, last):
        """更新市场状态"""
        pass
    
    #----------------------------------------------------------------------
    def onRspOrderInsert(self, data, error, n, last):
        """发单错误（柜台）"""
        if error['ErrorID']:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onRspOrderAction(self, data, error, n, last):
        """撤单错误（柜台）"""
        if error['ErrorID']:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
       
    #----------------------------------------------------------------------
    def onRspQryOrder(self, data, error, n, last):
        """"""
        if not self.gateway.orderInited:
            self.gateway.orderInited = True
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'委托查询完成'
            self.gateway.onLog(log)            
        
        # 更新最大报单编号
        newref = data['localOrderNo']
        self.orderRef = max(self.orderRef, int(newref))
        
        # 创建报单数据对象
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        
        # 保存代码和报单号
        order.symbol = data['instID']
        order.exchange = EXCHANGE_SGE
        order.vtSymbol = order.symbol
        
        order.orderID = data['localOrderNo']
        
        # 方向
        if data['buyOrSell'] == '0':
            order.direction = DIRECTION_LONG
        elif data['buyOrSell'] == '1':
            order.direction = DIRECTION_SHORT
        else:
            order.direction = DIRECTION_UNKNOWN
            
        # 开平
        if data['offsetFlag'] == '0':
            order.offset = OFFSET_OPEN
        elif data['offsetFlag'] == '1':
            order.offset = OFFSET_CLOSE
        else:
            order.offset = OFFSET_UNKNOWN        
            
        # 状态
        if data['status'] == '5':
            order.status = STATUS_ALLTRADED
        elif data['status'] == '6':
            order.status = STATUS_PARTTRADED
        elif data['status'] == '3':
            order.status = STATUS_NOTTRADED
        elif data['status'] == '4' or data['status'] == '7':    # 全部撤销和部成部撤
            order.status = STATUS_CANCELLED
        else:
            order.status = STATUS_UNKNOWN
        
        # CTP的报单号一致性维护需要基于frontID, sessionID, orderID三个字段
        # 但在本接口设计中，已经考虑了CTP的OrderRef的自增性，避免重复
        # 唯一可能出现OrderRef重复的情况是多处登录并在非常接近的时间内（几乎同时发单）
        # 考虑到VtTrader的应用场景，认为以上情况不会构成问题
        order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
        
        # 价格、报单量等数值
        order.price = data['price']
        order.totalVolume = data['amount']
        order.tradedVolume = data['matchQty']
        order.orderTime = data['entrustTime']
        order.cancelTime = data['cancelTime']    
        
        # 推送
        self.gateway.onOrder(order)        
    
    #----------------------------------------------------------------------
    def onRspQryTrade(self, data, error, n, last):
        """"""
        if not self.gateway.tradeInited:
            self.gateway.tradeInited = True
            
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'成交查询完成'
            self.gateway.onLog(log)
        
        # 创建报单数据对象
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        # 保存代码和报单号
        trade.symbol = data['instID']
        trade.exchange = EXCHANGE_SGE
        trade.vtSymbol = trade.symbol 
        
        trade.tradeID = data['matchNo']
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
        
        trade.orderID = data['localOrderNo']
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
        
        # 方向
        trade.direction = directionMapReverse.get(data['buyOrSell'], '')
            
        # 开平
        trade.offset = offsetMapReverse.get(data['offSetFlag'], '')
            
        # 价格、报单量等数值
        trade.price = data['price']
        trade.volume = data['volume']
        trade.tradeTime = data['matchTime']
        
        # 推送
        self.gateway.onTrade(trade)        
    
    #----------------------------------------------------------------------
    def onRspQryInvestorPosition(self, data, error, n, last):
        """持仓查询回报"""
        # 过滤一些空的数据
        if data['instID']:
            # 黄金API推送的持仓数据把多空仓放在了一条中，需要分离
            longPos = VtPositionData()
            longPos.gatewayName = self.gatewayName
            longPos.symbol = data['instID']
            longPos.vtSymbol = longPos.symbol
            longPos.direction = DIRECTION_LONG
            longPos.frozen = data['longPosiFrozen']
            longPos.position = data['longPosiVol']
            longPos.ydPosition = data['lastLong']
            longPos.price = data['longPosiAvgPrice']
            longPos.vtPositionName = '.'.join([longPos.vtSymbol, longPos.direction])
            self.gateway.onPosition(longPos)
            
            shortPos = VtPositionData()
            shortPos.gatewayName = self.gatewayName
            shortPos.symbol = data['instID']
            shortPos.vtSymbol = shortPos.symbol
            shortPos.direction = DIRECTION_SHORT
            shortPos.frozen = data['shortPosiFrozen']
            shortPos.position = data['shortPosiVol']
            shortPos.ydPosition = data['lastShort']
            shortPos.price = data['shortPosiAvgPrice']
            shortPos.vtPositionName = '.'.join([shortPos.vtSymbol, shortPos.direction])
            self.gateway.onPosition(shortPos)
    
    #----------------------------------------------------------------------
    def onRspQryTradingAccount(self, data, error, n, last):
        """资金账户查询回报"""
        account = VtAccountData()
        account.gatewayName = self.gatewayName
        
        # 账户代码
        account.accountID = 'sge_account'   # API不提供该字段，自行定义
        account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
        
        # 数值相关
        account.available = data['availCap']
        account.commission = data['totalFee']
        account.margin = data['posiMargin']
        
        # 推送
        self.gateway.onAccount(account)
    
    #----------------------------------------------------------------------
    def onRspQryInstrument(self, data, error, n, last):
        """合约查询回报"""
        contract = VtContractData()
        contract.gatewayName = self.gatewayName

        contract.symbol = data['instID']
        contract.exchange = EXCHANGE_SGE    # 交易所只有金交所
        
        # 合约类型分为现货、延期、未知
        if data['marketID'] == '00':
            contract.productClass = PRODUCT_SPOT
        elif data['marketID'] == '10':
            contract.productClass = PRODUCT_DEFER
        else:
            contract.productclass = PRODUCT_UNKNOWN
        
        contract.vtSymbol = contract.symbol 
        contract.name = data['name'].decode('GBK')
        
        # 合约数值
        contract.size = data['unit']
        contract.priceTick = data['tick']
        
        # 推送，考虑到只对T+D类带杠杆的产品感兴趣，API里默认过滤了现货
        if data['marketID'] == '10':
            self.gateway.onContract(contract)
        
        if last:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易合约信息获取完成'
            self.gateway.onLog(log)
    
    #----------------------------------------------------------------------  
    def onRtnDepthMarketData(self, data):
        """行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
        
        tick.symbol = data['InstID']
        tick.vtSymbol = tick.symbol
        
        tick.lastPrice = data['Last']
        tick.volume = data['Volume']
        tick.openInterest = data['OpenInt']
        tick.time = data['QuoteTime']
        tick.date = data['QuoteDate']
        
        tick.openPrice = data['Open']
        tick.highPrice = data['High']
        tick.lowPrice = data['Low']
        tick.preClosePrice = data['PreClose']
        
        tick.upperLimit = data['highLimit']
        tick.lowerLimit = data['lowLimit']
        
        # CTP只有一档行情
        tick.bidPrice1 = data['Bid1']
        tick.bidPrice2 = data['Bid2']
        tick.bidPrice3 = data['Bid3']
        tick.bidPrice4 = data['Bid4']
        tick.bidPrice5 = data['Bid5']
        
        tick.askPrice1 = data['Ask1']
        tick.askPrice2 = data['Ask2']
        tick.askPrice3 = data['Ask3']
        tick.askPrice4 = data['Ask4']
        tick.askPrice5 = data['Ask5']        
        
        tick.bidVolume1 = data['BidLot1']
        tick.bidVolume2 = data['BidLot2']
        tick.bidVolume3 = data['BidLot3']
        tick.bidVolume4 = data['BidLot4']
        tick.bidVolume5 = data['BidLot5']
        
        tick.askVolume1 = data['AskLot1']
        tick.askVolume2 = data['AskLot2']
        tick.askVolume3 = data['AskLot3']
        tick.askVolume4 = data['AskLot4']
        tick.askVolume5 = data['AskLot5']
        
        self.gateway.onTick(tick)
        
    #----------------------------------------------------------------------
    def onRtnOrder(self, data):
        """报单回报"""
        # 更新最大报单编号
        newref = data['localOrderNo']
        self.orderRef = max(self.orderRef, int(newref))
        
        # 创建报单数据对象
        order = self.orderDict.get(int(newref), VtOrderData())
        order.gatewayName = self.gatewayName
        order.exchange = EXCHANGE_SGE
        order.orderID = data['localOrderNo']
        
        # 状态
        if data['status'] == '5':
            order.status = STATUS_ALLTRADED
        elif data['status'] == '6':
            order.status = STATUS_PARTTRADED
        elif data['status'] == '3':
            order.status = STATUS_NOTTRADED
        elif data['status'] == '4' or data['status'] == '7':    # 全部撤销和部成部撤
            order.status = STATUS_CANCELLED
        else:
            order.status = STATUS_UNKNOWN
        
        # 推送
        self.gateway.onOrder(order)
        
    #----------------------------------------------------------------------
    def onForceLogout(self, data):
        """强制登出推送"""
        self.gateway.onLog(u'被强制登出')
    
    #----------------------------------------------------------------------
    def onRtnTrade(self, data):
        """成交回报"""
        # 创建报单数据对象
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        # 保存代码和报单号
        trade.symbol = data['instID']
        trade.exchange = EXCHANGE_SGE
        trade.vtSymbol = trade.symbol 
        
        trade.tradeID = data['matchNo']
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
        
        trade.orderID = data['localOrderNo']
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
        
        # 方向
        trade.direction = directionMapReverse.get(data['buyOrSell'], '')
            
        # 开平
        trade.offset = offsetMapReverse.get(data['offSetFlag'], '')
            
        # 价格、报单量等数值
        trade.price = data['price']
        trade.volume = data['volume']
        trade.tradeTime = data['matchTime']
        
        # 推送
        self.gateway.onTrade(trade)
        
        # 计算还原Order状态，并推送
        order = self.orderDict.get(int(trade.orderID), None)
        if order:
            order.tradedVolume = order.tradedVolume + trade.volume
            
            if order.tradedVolume == order.totalVolume:
                order.status = STATUS_ALLTRADED
            else:
                order.status = STATUS_PARTTRADED
                
        self.gateway.onOrder(order)
    
    #----------------------------------------------------------------------
    def onErrRtnOrderInsert(self, data, error):
        """发单错误回报（交易所）"""
        if error['ErrorID']:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onErrRtnOrderAction(self, data, error):
        """撤单错误回报（交易所）"""
        if error['ErrorID']:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onRspQryClientStorage(self, data, error, n, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onRspSubMarketData(self, data, error, n, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def connect(self, accountID, password, address):
        """初始化连接"""
        self.accountID = accountID 
        self.password = password   
        self.address = address  
        
        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            self.createGoldTraderApi()
            
            # 注册服务器地址
            self.registerFront(self.address)

            # 初始化连接，成功会调用onFrontConnected
            self.init(False)
            self.connectionStatus = True
            
            # 金仕达接口第一次连接不会调用onFrontConnected（只有断线重连才会），直接登录
            self.login()
            
        # 若已经连接但尚未登录，则进行登录
        else:
            if not self.loginStatus:
                self.login()    
    
    #----------------------------------------------------------------------
    def login(self):
        """连接服务器"""
        # 如果填入了用户名密码等，则登录
        if self.accountID and self.password:
            req = {}
            req['accountID'] = self.accountID
            req['password'] = self.password
            req['loginType'] = 1
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
        self.reqQryInvestorPosition({}, self.reqID)
    
    #----------------------------------------------------------------------
    def getTrade(self):
        """查询成交"""
        self.reqID += 1
        self.reqQryTrade({}, self.reqID)    
    
    #----------------------------------------------------------------------
    def getOrder(self):
        """查询委托"""
        self.reqID += 1
        self.reqQryOrder({}, self.reqID)        
    
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        self.reqID += 1
        self.orderRef += 1
        
        req = {}
        
        req['instID'] = orderReq.symbol
        req['marketID'] = '10'
        
        req['price'] = orderReq.price
        req['amount'] = orderReq.volume
        
        # 下面如果由于传入的类型本接口不支持，则会返回空字符串
        try:
            req['buyOrSell'] = directionMap[orderReq.direction]
            req['offsetFlag'] = offsetMap[orderReq.offset]
        except KeyError:
            return ''
        
        strOrderID = generateStrLocalID(self.orderRef)
        req['LocalOrderNo'] = strOrderID
        req['seatID'] = self.seatID
        req['tradeCode'] = self.tradeCode
        
        self.reqOrderInsert(req, self.reqID)
        
        # 返回订单号（字符串），便于某些算法进行动态管理
        vtOrderID = '.'.join([self.gatewayName, strOrderID])
        
        # 保存请求到本地，用于在收到回报时查询
        # 金仕达黄金API的onRtnOrder只推送很有限的几个数据，因此整个数据需要自己还原
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        order.symbol = orderReq.symbol
        order.vtSymbol = orderReq.symbol
        order.exchange = EXCHANGE_SGE
        order.orderID = strOrderID
        order.vtOrderID = strOrderID
        order.direction = orderReq.direction
        order.offset = orderReq.offset
        order.price = orderReq.price
        order.totalVolume = orderReq.volume
        order.orderTime = time.strftime('%H:%M:%S')   # 保存委托时间
        self.orderDict[self.orderRef] = order
        
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.reqID += 1

        req = {}
        req['localOrderNo'] = cancelOrderReq.orderID
        req['marketID'] = '10'  # API默认只允许交易T+D延期
        
        self.reqOrderAction(req, self.reqID)
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        # 黄金API的订阅传入的参数不是具体交易合约代码，而是类型代码
        # 考虑到只希望交易T+D，这里直接传入'10'
        self.subscribeMarketData('10')
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()


#----------------------------------------------------------------------
def generateStrLocalID(localID):
    """把整数的本地委托号转化为字符串"""
    return str(localID).rjust(12, '0')

