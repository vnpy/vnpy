# encoding: UTF-8

'''
vn.xtp的gateway接入
'''


import os
import json

from vnpy.api.xtp import *
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath


# 以下为一些VT类型和XTP类型的映射字典
# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = 1
priceTypeMap[PRICETYPE_MARKETPRICE] = 2
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
sideMap = {}
sideMap[(DIRECTION_LONG, OFFSET_NONE)] = 1
sideMap[(DIRECTION_SHORT, OFFSET_NONE)] = 2
sideMap[(DIRECTION_LONG, OFFSET_OPEN)] = 3
sideMap[(DIRECTION_SHORT, OFFSET_OPEN)] = 4
sideMap[(DIRECTION_LONG, OFFSET_CLOSE)] = 5
sideMap[(DIRECTION_SHORT, OFFSET_CLOSE)] = 6
sideMapReverse = {v: k for k, v in sideMap.items()}

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_SSE] = 1
exchangeMap[EXCHANGE_SZSE] = 2
exchangeMap[EXCHANGE_UNKNOWN] = 3
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 市场类型映射
marketMap = {}
marketMap[EXCHANGE_UNKNOWN] = 0
marketMap[EXCHANGE_SZSE] = 1
marketMap[EXCHANGE_SSE] = 2
marketMapReverse = {v:k for k,v in marketMap.items()}

# 持仓类型映射
#posiDirectionMap = {}
#posiDirectionMap[DIRECTION_NET] = defineDict["THOST_FTDC_PD_Net"]
#posiDirectionMap[DIRECTION_LONG] = defineDict["THOST_FTDC_PD_Long"]
#posiDirectionMap[DIRECTION_SHORT] = defineDict["THOST_FTDC_PD_Short"]
#posiDirectionMapReverse = {v:k for k,v in posiDirectionMap.items()}

# 产品类型映射
productClassMapReverse = {}
productClassMapReverse[0] = PRODUCT_EQUITY
productClassMapReverse[1] = PRODUCT_INDEX
productClassMapReverse[2] = PRODUCT_EQUITY
productClassMapReverse[3] = PRODUCT_EQUITY
productClassMapReverse[4] = PRODUCT_UNKNOWN


# 委托状态映射
statusMapReverse = {}
statusMapReverse[0] = STATUS_UNKNOWN
statusMapReverse[1] = STATUS_ALLTRADED
statusMapReverse[2] = STATUS_PARTTRADED
statusMapReverse[3] = STATUS_CANCELLED
statusMapReverse[4] = STATUS_NOTTRADED
statusMapReverse[5] = STATUS_CANCELLED
statusMapReverse[6] = STATUS_REJECTED
statusMapReverse[7] = STATUS_UNKNOWN

# 业务类型映射
#businessMap = {}
#businessMap[BUSINESS_CASH] = 0
#businessMap[BUSINESS_IPO] = 1
#businessMap[BUSINESS_REPO] = 2
#businessMap[BUSINESS_ETF] = 3
#businessMap[BUSINESS_MARGIN] = 4
#businessMap[BUSINESS_DESIGNATION] = 5
#businessMap[BUSINESS_ALLOTMENT] = 6
#businessMap[BUSINESS_STRUCTURED_FUND_PURCHASE_REDEMPTION] = 7
#businessMap[BUSINESS_STRUCTURED_FUND_SPLIT_MERGE] = 8
#businessMap[BUSINESS_MONEY_FUND] = 9
#businessMap[BUSINESS_UNKNOWN] = 10
#businessMapReverse = {v:k for k,v in businessMap.items()}


########################################################################
class XtpGateway(VtGateway):
    """XTP接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='XTP'):
        """Constructor"""
        super(XtpGateway, self).__init__(eventEngine, gatewayName)
        
        self.mdApi = XtpMdApi(self)     # 行情API
        self.tdApi = XtpTdApi(self)     # 交易API
        
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
            clientID = int(setting['clientID'])
            softwareKey = str(setting['softwareKey'])
            tdAddress = str(setting['tdAddress'])
            tdPort = int(setting['tdPort'])
            mdAddress = str(setting['mdAddress'])
            mdPort = int(setting['mdPort'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 创建行情和交易接口对象        
        self.mdApi.connect(userID, password, clientID, mdAddress, mdPort)
        self.tdApi.connect(userID, password, clientID, softwareKey, tdAddress, tdPort)
        
        # 初始化并启动查询
        self.initQuery()
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        self.mdApi.subscribe(subscribeReq)
        
    #----------------------------------------------------------------------
    def unSubscribe(self, subscribeReq):
        """"""
        self.mdApi.unSubscribe(subscribeReq)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.tdApi.sendOrder(orderReq)
        
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.tdApi.sendCancel(cancelOrderReq)
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        if self.tdConnected:
            self.tdApi.qryAccount()
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        if self.tdConnected:    
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
class XtpMdApi(QuoteApi):
    """XTP行情API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(XtpMdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.subscribedSymbols = set()      # 已订阅合约代码        
        
        self.userID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.address = EMPTY_STRING         # 服务器地址
        self.port = EMPTY_INT               # 服务器端口
    
    #----------------------------------------------------------------------
    def onDisconnected(self, reason):
        """连接断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.mdConnected = False
    
        content = (u'行情服务器连接断开，原因：%s' %reason)
        self.writeLog(content)
        
        # 重新连接
        n = self.login(self.address, self.port, self.userID, self.password, 1)
        if not n:
            self.connectionStatus = True
            self.loginStatus = True
            self.gateway.mdConnected = True
            self.writeLog(u'行情服务器登录成功')
        else:
            self.writeLog(u'行情服务器登录失败，原因:%s' %n)        
        
    #----------------------------------------------------------------------
    def onError(self, error):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['error_id']
        err.errorMsg = error['error_msg'].decode('gbk')
        self.gateway.onError(err)        
        
    #----------------------------------------------------------------------
    def onSubMarketData(self, data, error, last):
        """订阅行情回报"""
        pass
        
    #----------------------------------------------------------------------
    def onUnSubMarketData(self, data, error, last):
        """退订行情回报"""
        pass
        
    #----------------------------------------------------------------------
    def onDepthMarketData(self, data):
        """行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
    
        tick.symbol = data['ticker']
        tick.exchange = exchangeMapReverse.get(data['exchange_id'], EXCHANGE_UNKNOWN)
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
    
        tick.lastPrice = data['last_price']
        tick.volume = data['qty']
        tick.openInterest = data['open_interest']

        timestamp = str(data['data_time'])
        tick.date = timestamp[:8]
        tick.time = '%s:%s:%s.%s' %(timestamp[8:10], timestamp[10:12], timestamp[12:14], timestamp[14])
        
        tick.openPrice = data['open_price']
        tick.highPrice = data['high_price']
        tick.lowPrice = data['low_price']
        tick.preClosePrice = data['pre_close_price']
    
        tick.upperLimit = data['upper_limit_price']
        tick.lowerLimit = data['lower_limit_price']
        
        tick.bidPrice1, tick.bidPrice2, tick.bidPrice3, tick.bidPrice4, tick.bidPrice5 = data['bid'][0:5]
        tick.askPrice1, tick.askPrice2, tick.askPrice3, tick.askPrice4, tick.askPrice5 = data['ask'][0:5]
        tick.bidVolume1, tick.bidVolume2, tick.bidVolume3, tick.bidVolume4, tick.bidVolume5 = data['bid_qty'][0:5]
        tick.askVolume1, tick.askVolume2, tick.askVolume3, tick.askVolume4, tick.askVolume5 = data['ask_qty'][0:5]  
    
        self.gateway.onTick(tick)        
        
    #----------------------------------------------------------------------
    def onQueryAllTickers(self, data, error, last):
        """合约信息推送"""
        if error and error['error_id']:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['error_id']
            err.errorMsg = error['error_msg'].decode('gbk')
            self.gateway.onError(err)
            return
        
        contract = VtContractData()
        contract.gatewayName = self.gatewayName
        
        contract.symbol = data['ticker']
        contract.exchange = exchangeMapReverse.get(data['exchange_id'], EXCHANGE_UNKNOWN)
        contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
        
        contract.name = data['ticker_name'].decode('UTF-8')
        contract.size = 1
        contract.priceTick = data['price_tick']
        contract.productClass = productClassMapReverse.get(data['ticker_type'], PRODUCT_UNKNOWN)
        
        self.gateway.onContract(contract)
        
    #----------------------------------------------------------------------
    def onSubOrderBook(self, data, error, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onUnSubOrderBook(self, data, error, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onOrderBook(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onSubTickByTick(self, data, error, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onUnSubTickByTick(self, data, error, last):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onTickByTick(self, data):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onSubscribeAllMarketData(self, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onUnSubscribeAllMarketData(self, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onSubscribeAllOrderBook(self, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onUnSubscribeAllOrderBook(self, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onSubscribeAllTickByTick(self, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onUnSubscribeAllTickByTick(self, error):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onQueryTickersPriceInfo(self, data, error, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def connect(self, userID, password, clientID, address, port):
        """初始化连接"""
        self.userID = userID                # 账号
        self.password = password            # 密码
        self.address = address              # 服务器地址
        self.port = port                    # 端口号
        
        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            path = os.getcwd() + '/temp/' + self.gatewayName + '/'
            if not os.path.exists(path):
                os.makedirs(path)
            self.createQuoteApi(clientID, path)
            
            n = self.login(address, port, userID, password, 1)
            if not n:
                self.connectionStatus = True
                self.loginStatus = True
                self.gateway.mdConnected = True
                self.writeLog(u'行情服务器登录成功')
                
                self.writeLog(u'查询合约信息')
                self.queryAllTickers(1)         # 上交所
                self.queryAllTickers(2)         # 深交所
            else:
                self.writeLog(u'行情服务器登录失败，原因:%s' %n)
        
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅合约"""
        # 这里的设计是，如果尚未登录就调用了订阅方法
        # 则先保存订阅请求，登录完成后会自动订阅
        if self.loginStatus:
            self.subscribeMarketData(str(subscribeReq.symbol), 
                                     exchangeMap[subscribeReq.exchange])
        
        self.subscribedSymbols.add(subscribeReq)   
        
    #----------------------------------------------------------------------
    def unSubscribe(self, subscribeReq):
        """"""
        if self.loginStatus:
            self.unSubscribeMarketData(str(subscribeReq.symbol), 
                                       exchangeMap[subscribeReq.exchange])
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)         


########################################################################
class XtpTdApi(TraderApi):
    """XTP交易API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(XtpTdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.userID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.address = EMPTY_STRING         # 服务器地址
        self.port = EMPTY_INT               # 服务器端口
        self.clientID = EMPTY_INT           # 客户编号
        
        self.sessionID = EMPTY_INT          # 会话编号
        
        self.orderDict = {}                 # 委托缓存字典

    #----------------------------------------------------------------------
    def onDisconnected(self, session, reason):
        """连接断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.tdConnected = False
    
        content = (u'交易服务器连接断开，原因：%s' %reason)
        self.writeLog(content)
        
        # 发起重新连接
        n = self.login(self.address, self.port, self.userID, self.password, 1)
        
        if n:
            self.sessionID = n
            self.connectionStatus = True
            self.loginStatus = True
            self.gateway.tdConnected = True
            self.writeLog(u'交易服务器登录成功，会话编号：%s' %n)
        else:
            self.writeLog(u'交易服务器登录失败')                     
        
    #----------------------------------------------------------------------
    def onError(self, data):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['error_id']
        err.errorMsg = error['error_msg'].decode('gbk')
        self.gateway.onError(err)    
        
    #----------------------------------------------------------------------
    def onOrderEvent(self, data, error, session):
        """委托数据回报"""
        orderID = str(data['order_xtp_id'])
        
        if orderID not in self.orderDict:
            # 创建报单数据对象
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            
            # 保存代码和报单号
            order.symbol = data['ticker']
            order.exchange = marketMapReverse.get(data['market'], EXCHANGE_UNKNOWN)
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            order.orderID = orderID
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
    
            order.sessionID = self.sessionID
            order.frontID = self.getClientIDByXTPID(data['order_xtp_id'])
    
            # 开平和方向
            order.direction, order.offset = sideMapReverse.get(data['side'], 
                                                               (DIRECTION_UNKNOWN, OFFSET_UNKNOWN))
            
            # 不变的字段
            order.price = data['price']
            order.totalVolume = data['quantity']    
            order.priceType = priceTypeMapReverse.get(data['price_type'], '')
            
            self.orderDict[orderID] = order
        else:
            order = self.orderDict[orderID]
            
        # 变化字段
        order.status = statusMapReverse.get(data['order_status'], STATUS_UNKNOWN)
        order.tradedVolume = data['qty_traded']
        
        if data['insert_time']:
            timestamp = str(data['insert_time'])
            order.orderTime = '%s:%s:%s' %(timestamp[8:10], timestamp[10:12], timestamp[12:14])

        if data['cancel_time']:
            timestamp = str(data['cancel_time'])
            order.cancelTime = '%s:%s:%s' %(timestamp[8:10], timestamp[10:12], timestamp[12:14])
            
        # 推送
        self.gateway.onOrder(order)        
        
        # 错误信息
        if error['error_id']:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['error_id']
            err.errorMsg = u'委托号' + str(order.orderID) + ':' + error['error_msg'].decode('gbk')
            err.errorTime = order.orderTime
            self.gateway.onError(err)           
        
    #----------------------------------------------------------------------
    def onTradeEvent(self, data, session):
        """成交推送"""
        # 创建报单数据对象
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        # 保存代码和报单号
        trade.symbol = data['ticker']
        trade.exchange = marketMapReverse.get(data['market'], EXCHANGE_UNKNOWN)
        trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
        
        trade.tradeID = str(data['exec_id'])
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
        
        orderID = str(data['order_xtp_id'])
        trade.orderID = orderID
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
        
        # 开平和方向
        trade.direction, trade.offset = sideMapReverse.get(data['side'], 
                                                           (DIRECTION_UNKNOWN, OFFSET_UNKNOWN))
            
        # 价格、报单量等数值
        trade.price = data['price']
        trade.volume = data['quantity']

        if data['trade_time']:
            timestamp = str(data['trade_time'])
            trade.tradeTime = '%s:%s:%s' %(timestamp[8:10], timestamp[10:12], timestamp[12:14])
        
        # 推送
        self.gateway.onTrade(trade)
        
        # 更新委托数据
        order = self.orderDict.get(orderID, None)
        if (not order or 
            order.status is STATUS_ALLTRADED or
            order.status is STATUS_CANCELLED):
            return
            
        order.tradedVolume += trade.volume
        
        if order.status is STATUS_NOTTRADED:
            order.status = STATUS_PARTTRADED
            
        self.gateway.onOrder(order)
        
    #----------------------------------------------------------------------
    def onCancelOrderError(self, data, error, session):
        """撤单错误回报"""
        if error['error_id']:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['error_id']
            err.errorMsg = u'委托号' + str(data['order_xtp_id']) + ':' + error['error_msg'].decode('gbk')
            self.gateway.onError(err)   
        
    #----------------------------------------------------------------------
    def onQueryOrder(self, data, error, reqid, last, session):
        """委托查询回报"""
        pass
        
    #----------------------------------------------------------------------
    def onQueryTrade(self, data, error, reqid, last, session):
        """成交查询回报"""
        pass       
        
    #----------------------------------------------------------------------
    def onQueryPosition(self, data, error, reqid, last, session):
        """查询持仓回报"""
        pos = VtPositionData()
        pos.gatewayName = self.gatewayName
        
        # 保存代码
        pos.symbol = data['ticker']
        pos.exchange = marketMapReverse.get(data['market'], EXCHANGE_UNKNOWN)
        pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])
        pos.name = data['ticker_name'].decode('UTF-8')
        
        # 方向和持仓冻结数量
        pos.direction = DIRECTION_LONG
        pos.position = data['total_qty']
        pos.frozen = data['total_qty'] - data['sellable_qty']
        pos.price = data['avg_price']
        
        # VT系统持仓名
        pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
        
        # 推送
        self.gateway.onPosition(pos)     
        
    #----------------------------------------------------------------------
    def onQueryAsset(self, data, error, reqid, last, session):
        """账户查询回报"""
        account = VtAccountData()
        account.gatewayName = self.gatewayName
    
        # 账户代码
        account.accountID = self.userID
        account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
    
        # 数值相关
        account.balance = float(data['total_asset'])
        account.available = float(data['buying_power'])
        account.commission = float(data['fund_buy_fee']) + float(data['fund_sell_fee'])
    
        # 推送
        self.gateway.onAccount(account)
    
    #----------------------------------------------------------------------
    def onQueryStructuredFund(self, data, error, reqid, last, session):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onQueryFundTransfer(self, data, error, reqid, last, session):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onFundTransfer(self, data, error, session):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onQueryETF(self, data, error, reqid, last, session):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onQueryETFBasket(self, data, error, reqid, last, session):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onQueryIPOInfoList(self, data, error, reqid, last, session):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def onQueryIPOQuotaInfo(self, data, error, reqid, last, session):
        """"""
        pass
           
    #----------------------------------------------------------------------
    def connect(self, userID, password, clientID, softwareKey, address, port):
        """初始化连接"""
        self.userID = userID                # 账号
        self.password = password            # 密码
        self.address = address              # 服务器地址
        self.port = port                    # 端口号
        self.clientID = clientID
        
        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            path = os.getcwd() + '/temp/' + self.gatewayName + '/'
            if not os.path.exists(path):
                os.makedirs(path)
            self.createTraderApi(clientID, path)
            
            # 设置软件编码，认证用
            self.setSoftwareKey(softwareKey)
            
            # 设置订单和成交回报重传模式
            self.subscribePublicTopic(0)
            
            # 发起登录
            n = self.login(address, port, userID, password, 1)
            
            if n:
                self.sessionID = n
                self.connectionStatus = True
                self.loginStatus = True
                self.gateway.tdConnected = True
                self.writeLog(u'交易服务器登录成功，会话编号：%s' %n)
            else:
                self.writeLog(u'交易服务器登录失败')             
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户"""
        if self.sessionID:
            self.reqID += 1
            self.queryAsset(self.sessionID, self.reqID)
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        if self.sessionID:
            self.reqID += 1
            self.queryPosition('', self.sessionID, self.reqID)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        req = {}
        req['ticker'] = orderReq.symbol
        req['price'] = orderReq.price
        req['quantity'] = orderReq.volume
        req['price_type'] = priceTypeMap.get(orderReq.priceType, 0)
        req['market'] = marketMap.get(orderReq.exchange, 0)
        req['business_type'] = 0        # 目前只支持买卖业务

        # 目前尚未支持衍生品交易，因此不适用
        #req['side'] = sideMap.get((orderReq.direction, OFFSET_NONE), 0)
        if orderReq.direction == DIRECTION_LONG:
            req['side'] = 1
        else:
            req['side'] = 2

        # 发出委托
        orderID = str(self.insertOrder(req, self.sessionID))        
        vtOrderID = '.'.join([self.gatewayName, orderID])

        # 返回订单号（字符串），便于某些算法进行动态管理
        return vtOrderID
    
    #----------------------------------------------------------------------
    def sendCancel(self, cancelOrderReq):
        """撤单，因为cancelOrder的命名已经被原生接口使用了，所以改为sendCancel"""
        self.cancelOrder(int(cancelOrderReq.orderID), self.sessionID)
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)   