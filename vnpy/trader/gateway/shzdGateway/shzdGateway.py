# encoding: UTF-8

'''
vn.shzd的gateway接入

1. 期权合约数量太多，为了方便起见默认接口只接收期货合约数据
2. 直达接口的撤单操作也被视作一个独立的委托，但是在vn.trader中选择忽略
3. 持仓全部平光后，再次查询时会没有该合约的推送（和CTP不同），为了避免最后平仓
   不更新的情况，使用缓存机制来处理
'''


import os
import json
from copy import copy
from datetime import datetime

from vnpy.api.shzd import ShzdApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath


# 以下为一些VT类型和SHZD类型的映射字典
# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = '1'
priceTypeMap[PRICETYPE_MARKETPRICE] = '2'
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = '1'
directionMap[DIRECTION_SHORT] = '2'
directionMapReverse = {v: k for k, v in directionMap.items()}

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_HKEX] = 'HKEX'
exchangeMap[EXCHANGE_CME] = 'CME'
exchangeMap[EXCHANGE_ICE] = 'ICE'
exchangeMap[EXCHANGE_LME] = 'LME'
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 产品类型映射
productClassMap = {}
productClassMap[PRODUCT_FUTURES] = 'F'
productClassMap[PRODUCT_OPTION] = 'O'
productClassMapReverse = {v:k for k,v in productClassMap.items()}

# 委托状态映射
orderStatusMapReverse = {}
orderStatusMapReverse['2'] = STATUS_NOTTRADED
orderStatusMapReverse['3'] = STATUS_PARTTRADED
orderStatusMapReverse['4'] = STATUS_ALLTRADED
orderStatusMapReverse['5'] = STATUS_CANCELLED
orderStatusMapReverse['6'] = STATUS_CANCELLED


########################################################################
class ShzdGateway(VtGateway):
    """SHZD接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='SHZD'):
        """Constructor"""
        super(ShzdGateway, self).__init__(eventEngine, gatewayName)
        
        self.api = ShzdGatewayApi(self)  
        
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
            frontAddress = str(setting['frontAddress'])
            frontPort = int(setting['frontPort'])
            marketAddress = str(setting['marketAddress'])
            marketPort = int(setting['marketPort'])
            userId = str(setting['userId'])
            userPwd = str(setting['userPwd'])
        except KeyError:
            self.writeLog(u'连接配置缺少字段，请检查')
            return            
        
        # 创建行情和交易接口对象
        self.api.connect(userId, userPwd, 
                         frontAddress, frontPort,
                         marketAddress, marketPort)
        
        # 初始化并启动查询
        self.initQuery()
        
    #----------------------------------------------------------------------
    def writeLog(self, logContent):
        """记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = logContent
        self.onLog(log)        
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        self.api.subscribe(subscribeReq)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.api.sendOrder(orderReq)
        
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.api.cancelOrder(cancelOrderReq)
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        self.api.qryAccount()
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.api.qryPosition()
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.api.close()  # 释放接口对象
        
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
class ShzdGatewayApi(ShzdApi):
    """直达接口的继承实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(ShzdGatewayApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        
        self.userId = EMPTY_STRING      # 用户名
        self.accountNo = EMPTY_STRING   # 查询等用的单一账号
        self.accountNoList = []         # 账号列表
        
        self.tradeCallbacks = {}    # 交易回调函数映射
        self.marketCallbacks = {}   # 行情回调函数映射        
        
        # 委托相关
        self.localNo = EMPTY_INT    # 本地委托号
        self.orderDict = {}         # key为str(localNo)，value为委托对象
        self.orderNoDict = {}       # key为OrderNo，value为localNo
        self.localNoDict = {}       # key为str(localNo)，value为(SystemNo, OrderNo)
        self.cancelDict = {}        # key为等待撤单的str(localNo)，value为CancelOrderReq
        
        # 委托号前缀
        n = datetime.now()
        self.orderPrefix = n.strftime("%H%M%S.")
        
        # 持仓缓存
        self.posDict = {}           # key为vtPositionName，value为VtPositionData
        
        # 是否进行了初始化
        self.inited = False
        
        self.initCallbacks()
        
    #----------------------------------------------------------------------
    def initCallbacks(self):
        """初始化回调函数映射"""
        # 行情推送
        self.marketCallbacks['MA1'] = self.onMarketData
        
        # 登录和查询回报
        self.tradeCallbacks['A1'] = self.onLogin
        self.tradeCallbacks['AC1'] = self.onQryAccount
        self.tradeCallbacks['OS1'] = self.onQryPosition
        self.tradeCallbacks['HY'] = self.onQryContract
        self.tradeCallbacks['ORS1'] = self.onQryOrder
        self.tradeCallbacks['FS1'] = self.onTrade
        
        # 下单和撤单确认
        self.tradeCallbacks['O1'] = self.onSendOrder
        self.tradeCallbacks['C1'] = self.onCancelOrder
        
        # 成交委托推送
        self.tradeCallbacks['O3'] = self.onTrade
        self.tradeCallbacks['OST'] = self.onOrder
        
    #----------------------------------------------------------------------
    def onReceiveErrorInfo(self, errcode, errmsg):
        """错误推送回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = errcode
        err.errorMsg = errmsg
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onReceiveMarketInfo(self, data):
        """行情推送回报"""
        func = self.marketCallbacks.get(data['msgtype'], None)
        if func:
            func(data)
    
    #----------------------------------------------------------------------
    def onReceiveTradeInfo(self, data):
        """交易推送回报"""
        func = self.tradeCallbacks.get(data['msgtype'], None)
        if func:
            func(data)
    
    #----------------------------------------------------------------------
    def onMarketData(self, data):
        """行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
    
        tick.symbol = data['307']
        tick.exchange = exchangeMapReverse.get(data['306'], EXCHANGE_UNKNOWN)
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
    
        tick.volume = int(data['513'])
        
        # LME行情没有持仓量数据
        if data['306'] != 'LME':
            tick.openInterest = int(data['514'])
        
        dt = data['512'].split(' ')
        tick.time = dt[1]
        tick.date = dt[0].replace('_', '')
    
        try:
            tick.lastPrice = float(data['504'])
            tick.openPrice = float(data['508'])
            tick.highPrice = float(data['506'])
            tick.lowPrice = float(data['507'])
            tick.preClosePrice = float(data['509'])
        
            # 可以实现5档深度
            tick.bidPrice1 = float(data['500'])
            tick.bidPrice2 = float(data['515'])
            tick.bidPrice3 = float(data['516'])
            tick.bidPrice4 = float(data['517'])
            tick.bidPrice5 = float(data['518'])
            
            tick.bidVolume1 = int(data['501'])
            tick.bidVolume2 = int(data['519'])
            tick.bidVolume3 = int(data['520'])
            tick.bidVolume4 = int(data['521'])
            tick.bidVolume5 = int(data['522'])
            
            tick.askPrice1 = float(data['502'])
            tick.askPrice2 = float(data['523'])
            tick.askPrice3 = float(data['524'])
            tick.askPrice4 = float(data['525'])
            tick.askPrice5 = float(data['526'])

            tick.askVolume1 = int(data['503'])
            tick.askVolume2 = int(data['527'])
            tick.askVolume3 = int(data['528'])
            tick.askVolume4 = int(data['529'])
            tick.askVolume5 = int(data['530'])
            
        except ValueError:
            pass
    
        self.gateway.onTick(tick)
        
    #----------------------------------------------------------------------
    def onLogin(self, data):
        """登录成功推送"""   
        if '11' in data:
            self.accountNo = data['11']
            self.accountNoList.append(data['11'])

            self.loginStatus = True
            self.gateway.writeLog(u'账户%s，结算货币%s' %(data['11'], data['200']))
            
        if '410' in data and data['410'] == '1':
            self.gateway.writeLog(u'登录成功')
            #self.qryContract()
            self.qryOrder()
            self.qryTrade()
            
    #----------------------------------------------------------------------
    def onSendOrder(self, data):
        """下单回报"""
        if not data['404'] or data['404'] == '00000':
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            
            order.symbol = data['307']
            order.exchange = exchangeMapReverse.get(data['306'], EXCHANGE_UNKNOWN)
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            order.orderID = data['305']
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.direction = directionMapReverse.get(data['308'], DIRECTION_UNKNOWN)
            order.price = float(data['310'])
            order.totalVolume = int(data['309'])
            order.status = orderStatusMapReverse.get(data['405'], STATUS_UNKNOWN)
            order.orderTime = data['346']
            
            self.orderDict[order.orderID] = order
            self.localNoDict[order.orderID] = (data['300'], data['301'])
            self.orderNoDict[data['301']] = order.orderID

            # 委托查询
            if '315' in data:
                order.tradedVolume = int(data['315'])
            
            self.gateway.onOrder(copy(order))
            
            # 检查是否要撤单
            if order.orderID in self.cancelDict:
                self.cancelOrder(self.cancelDict[order.orderID])
                del self.cancelDict[order.orderID]
        else:
            error = VtErrorData()
            error.gatewayName = self.gatewayName
            error.errorID = data['404']
            error.errorMsg = u'委托失败'
            self.gateway.onError(error)        
    
    #----------------------------------------------------------------------
    def onCancelOrder(self, data):
        """撤单回报"""
        orderID = self.orderNoDict[data['301']]
        order = self.orderDict[orderID]
        
        if not data['404'] or data['404'] == '00000':
            order.status = STATUS_CANCELLED
            order.cancelTime = data['326']
            self.gateway.onOrder(copy(order))
        else:
            error = VtErrorData()
            error.gatewayName = self.gatewayName
            error.errorID = data['404']
            error.errorMsg = u'撤单失败'
            self.gateway.onError(error)

    #----------------------------------------------------------------------
    def onTrade(self, data):
        """成交推送"""
        if '307' in data:
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            
            trade.symbol = data['307']
            trade.exchange = exchangeMapReverse.get(data['306'], EXCHANGE_UNKNOWN)
            trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
            
            trade.tradeID = data['304']
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
            
            trade.orderID = data['305']
            trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
            
            trade.direction = directionMapReverse.get(data['308'], DIRECTION_UNKNOWN)
            
            trade.price = float(data['313'])
            trade.volume = int(data['315'])
            trade.tradeTime = data['326']
            
            self.gateway.onTrade(trade)    
            
        elif '410' in data and data['410'] == '1':
            self.gateway.writeLog(u'成交查询完成')        
  
    #----------------------------------------------------------------------
    def onOrder(self, data):
        """委托变化推送"""
        orderID = self.orderNoDict.get(data['301'], None)
        if orderID:
            order = self.orderDict[orderID]
            order.tradedVolume = int(data['315'])
            
            if order.tradedVolume > 0:
                if order.tradedVolume < order.totalVolume:
                    order.status = STATUS_PARTTRADED
                else:
                    order.status = STATUS_ALLTRADED
            
            self.gateway.onOrder(copy(order))
    
    #----------------------------------------------------------------------
    def onQryOrder(self, data):
        """查询委托回报"""
        if '404' in data and data['404'] != '00000':
            error = VtErrorData()
            error.gatewayName = self.gatewayName
            error.errorID = data['404']
            error.errorMsg = u'查询委托失败'
            self.gateway.onError(error)          
        
        elif '410' not in data and '307' in data:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            
            order.symbol = data['307']
            order.exchange = exchangeMapReverse.get(data['306'], EXCHANGE_UNKNOWN)
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            order.orderID = data['305']
            order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
            
            order.direction = directionMapReverse.get(data['308'], DIRECTION_UNKNOWN)
            order.price = float(data['310'])
            order.totalVolume = int(data['309'])
            order.status = orderStatusMapReverse.get(data['405'], STATUS_UNKNOWN)
            order.orderTime = data['346']
            order.cancelTime = data['326']
            
            self.orderDict[order.orderID] = order
            self.localNoDict[order.orderID] = (data['300'], data['301'])
            self.orderNoDict[data['301']] = order.orderID            

            order.tradedVolume = int(data['315'])
            
            self.gateway.onOrder(copy(order))     
            
        elif '410' in data and data['410'] == '1':
            self.gateway.writeLog(u'委托查询完成')        
    
    #----------------------------------------------------------------------
    def onQryPosition(self, data):
        """持仓查询返回"""
        if '307' in data:
            pos = VtPositionData()
            pos.gatewayName = self.gatewayName
            pos.symbol = data['307']
            pos.exchange = exchangeMapReverse.get(data['306'], EXCHANGE_UNKNOWN)
            pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])
            
            # 多头仓位
            longPosName = '.'.join([pos.vtSymbol, DIRECTION_LONG])
            try:
                longPos = self.posDict[longPosName]
            except KeyError:
                longPos = copy(pos)
                longPos.direction = DIRECTION_LONG
                longPos.vtPositionName = longPosName
                self.posDict[longPosName] = longPos
            
            longPos.position = int(data['442'])
            longPos.price = float(data['443'])
            
            # 空头仓位    
            shortPosName = '.'.join([pos.vtSymbol, DIRECTION_SHORT])
            try:
                shortPos = self.posDict[shortPosName]
            except KeyError:
                shortPos = copy(pos)
                shortPos.direction = DIRECTION_SHORT
                shortPos.vtPositionName = shortPosName 
                self.posDict[shortPosName] = shortPos
            
            shortPos.position = int(data['445'])
            shortPos.price = float(data['446'])
        
        # 所有持仓数据推送完成后才向事件引擎中更新持仓数据
        if '410' in data and data['410'] == '1':
            for pos in self.posDict.values():
                self.gateway.onPosition(pos)
    
    #----------------------------------------------------------------------
    def onQryAccount(self, data):
        """账户资金查询返回"""
        if '11' in data:
            account = VtAccountData()    
            account.gatewayName = self.gatewayName
            
            account.accountID = data['11']
            account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
            account.preBalance = float(data['218'])
            account.balance = float(data['203'])
            account.available = float(data['201'])
            account.commission = float(data['221'])
            account.margin = float(data['212'])
            account.closeProfit = float(data['205'])
            account.positionProfit = float(data['216'])
            
            self.gateway.onAccount(account)
    
    #----------------------------------------------------------------------
    def onQryContract(self, data):
        """查询合约推送"""
        if '306' in data and data['306'] in exchangeMapReverse:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            
            contract.symbol = data['333'] + data['307']
            contract.exchange = exchangeMapReverse.get(data['306'], EXCHANGE_UNKNOWN)
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            
            contract.name = data['332'].decode('GBK')
            contract.productClass = productClassMapReverse.get(data['335'], '')
            contract.size = float(data['336'])
            contract.priceTick = float(data['337'])
            
            # 期权合约数量太多，为了方便起见默认接口只接收期货合约数据
            if contract.productClass == PRODUCT_FUTURES:
                self.gateway.onContract(contract)
        
        if '410' in data and data['410'] == '1':
            self.gateway.writeLog(u'合约查询完成')

    #----------------------------------------------------------------------
    def connect(self, userId, userPwd, 
                frontAddress, frontPort, 
                marketAddress, marketPort):
        """连接"""
        self.userId = userId

        # 初始化接口
        n = self.initShZdServer()
        if n:
            self.gateway.writeLog(u'接口初始化失败，原因%s' %n)
            return
        else:
            self.gateway.writeLog(u'接口初始化成功')
        self.inited = True

        # 连接交易服务器
        n = self.registerFront(frontAddress, frontPort)
        if n:
            self.gateway.writeLog(u'交易服务器连接失败，原因%s' %n)
            return
        else:
            self.gateway.writeLog(u'交易服务器连接成功')        

        # 连接行情服务器
        n = self.registerMarket(marketAddress, marketPort)
        if n:
            self.gateway.writeLog(u'行情服务器连接失败，原因%s' %n)
            return
        else:
            self.gateway.writeLog(u'行情服务器连接成功')

        # 登录
        req = {}
        req['msgtype'] = 'A'
        req['12'] = 'demo000604'
        req['16'] = '888888'
        self.shzdSendInfoToTrade(req)     

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        req = {}
        req['msgtype'] = 'MA'
        req['11'] = self.accountNo
        req['201'] = '+'
        req['307'] = ','.join([exchangeMap[subscribeReq.exchange], subscribeReq.symbol])
        self.shzdSendInfoToMarket(req)     
    
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        req = {}
        req['msgtype'] = 'O'
        req['12'] = self.userId
        req['11'] = self.accountNo
        req['306'] = exchangeMap.get(orderReq.exchange, '')
        req['307'] = orderReq.symbol
        req['308'] = directionMap.get(orderReq.direction, '')
        req['309'] = str(orderReq.volume)
        req['310'] = str(orderReq.price)
        req['401'] = priceTypeMap.get(orderReq.priceType, '')
        
        self.localNo += 1
        req['305'] = self.orderPrefix + str(self.localNo).rjust(10, '0')
        
        self.shzdSendInfoToTrade(req)
        
        vtOrderID = '.'.join([self.gatewayName, str(self.localNo)])
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelReq):
        """撤单"""
        tmp = self.localNoDict.get(cancelReq.orderID, None)
        
        if tmp:
            systemNo = tmp[0]
            orderNo = tmp[1]
            order = self.orderDict[cancelReq.orderID]
            
            req = {}
            req['msgtype'] = 'C'
            req['12'] = self.userId
            req['11'] = self.accountNo
            req['300'] = systemNo
            req['301'] = orderNo
            req['306'] = exchangeMap.get(order.exchange, '')
            req['307'] = order.symbol
            req['308'] = directionMap.get(order.direction, '')
            req['309'] = str(order.totalVolume)
            req['310'] = str(order.price)
            req['315'] = str(order.tradedVolume)
            
            self.shzdSendInfoToTrade(req)
        else:
            self.cancelSet.add(cancelReq)
    
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户"""
        req = {}
        req['msgtype'] = 'AC'
        req['12'] = self.userId
        req['11'] = self.accountNo
        self.shzdSendInfoToTrade(req)
    
    #----------------------------------------------------------------------
    def qryPosition(self):
        """持仓查询"""
        req = {}
        req['msgtype'] = 'OS'
        req['12'] = self.userId
        req['11'] = self.accountNo
        self.shzdSendInfoToTrade(req)
        
        # 清空持仓数据
        for pos in self.posDict.values():
            pos.price = 0
            pos.position = 0
    
    #----------------------------------------------------------------------
    def qryContract(self):
        """合约查询"""
        req = {}
        req['msgtype'] = 'HY'
        req['11'] = self.accountNo
        self.shzdSendInfoToTrade(req)
    
    #----------------------------------------------------------------------
    def qryTrade(self):
        """成交查询"""
        req = {}
        req['msgtype'] = 'FS'
        req['12'] = self.userId
        req['11'] = self.accountNo
        self.shzdSendInfoToTrade(req)   

    #----------------------------------------------------------------------
    def qryOrder(self):
        """委托查询"""
        req = {}
        req['msgtype'] = 'ORS'
        req['12'] = self.userId
        req['11'] = self.accountNo
        self.shzdSendInfoToTrade(req)         

    #----------------------------------------------------------------------
    def close(self):
        """关闭接口"""
        if self.inited:
            self.release()

#----------------------------------------------------------------------
def printDict(d):
    """打印字典"""
    print '-' * 50
    l = d.keys()
    l.sort()
    for k in l:
        print k, ':', d[k]
    