# encoding: UTF-8

'''
vn.shzd的gateway接入
'''


import os
import json
from copy import copy
from datetime import datetime

from vnshzd import ShzdApi
from vtGateway import *


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
#exchangeMap[EXCHANGE_CFFEX] = 'CFFEX'
#exchangeMap[EXCHANGE_SHFE] = 'SHFE'
#exchangeMap[EXCHANGE_CZCE] = 'CZCE'
#exchangeMap[EXCHANGE_DCE] = 'DCE'
exchangeMap[EXCHANGE_HKEX] = 'HKEX'
exchangeMap[EXCHANGE_CME] = 'CME'
exchangeMap[EXCHANGE_ICE] = 'ICE'
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

s = set()

########################################################################
class ShzdGateway(VtGateway):
    """SHZD接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='SHZD'):
        """Constructor"""
        super(ShzdGateway, self).__init__(eventEngine, gatewayName)
        
        self.api = ShzdGatewayApi(self)  
        
        self.qryEnabled = False         # 是否要启动循环查询
        
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
        fileName = self.gatewayName + '_connect.json'
        fileName = os.getcwd() + '/shzdGateway/' + fileName
        
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
        self.api.release()  # 释放接口对象
        
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
        printDict(data)
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
    
        tick.symbol = data['307']
        tick.exchange = exchangeMapReverse.get(data['306'], EXCHANGE_UNKNOWN)
        tick.vtSymbol = '.'.join([tick.symbol, EXCHANGE_UNKNOWN])
    
        tick.volume = int(data['513'])
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
            tick.bidVolume1 = int(data['501'])
            tick.askPrice1 = float(data['502'])
            tick.askVolume1 = int(data['503'])
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
            self.qryContract()
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
            self.localNoDict[order.orderID] = (order['300'], order['301'])

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
        orderID = self.orderNoDict[data['301']]
        order = self.orderDict[orderID]
        order.tradedVolume = int(data['315'])
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
            
            self.orderDict[order.orderID] = order
            self.localNoDict[order.orderID] = (data['300'], data['301'])

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
            
            longPos = copy(pos)
            longPos.direction = DIRECTION_LONG
            longPos.position = int(data['442'])
            longPos.price = float(data['443'])
            longPos.vtPositionName = '.'.join([longPos.vtSymbol, longPos.direction])
            
            shortPos = copy(pos)
            shortPos.direction = DIRECTION_SHORT
            shortPos.position = int(data['445'])
            shortPos.price = float(data['446'])
            shortPos.vtPositionName = '.'.join([shortPos.vtSymbol, shortPos.direction])            
            
            self.gateway.onPosition(longPos)
            self.gateway.onPosition(shortPos)
    
    #----------------------------------------------------------------------
    def onQryAccount(self, data):
        """账户资金查询返回"""
        if '11' in data:
            account = VtAccountData()    
            account.gatewayName = self.gatewayName
            
            account.accountID = data['11']
            account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
            account.preBalance = float(data['218'])
            account.available = float(data['203'])
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
        req['305'] = str(self.localNo)
        
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
            req['12'] = self.userId
            req['11'] = self.accountNo
            req['300'] = systemNo
            req['301'] = orderNo
            req['306'] = exchangeMap.get(order.exchange, '')
            req['307'] = order.symbol
            req['308'] = directionMap.get(order.direction, '')
            req['309'] = str(order.volume)
            req['310'] = 0
            req['315'] = 0
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
def printDict(d):
    """打印字典"""
    print '-' * 50
    l = d.keys()
    l.sort()
    for k in l:
        print k, ':', d[k]
    


if __name__ == '__main__':
    
    api = TestApi()
    
    # 初始化连接
    api.initShZdServer()
    
    # 注册前置机地址
    print api.registerFront('222.73.119.230', 7003)
    print api.registerMarket('222.73.119.230', 9003)
    
    # 登录
    sleep(1)
    data = {}
    data['msgtype'] = 'A'
    data['12'] = 'demo000604'
    data['16'] = '888888'
    api.shzdSendInfoToTrade(data)
    
    # 订阅行情
    sleep(1)
    data = {}
    data['msgtype'] = 'MA'
    data['11'] = '00010337'
    data['201'] = '+'
    data['307'] = "CME,6J1609"
    api.shzdSendInfoToMarket(data)
    
    raw_input()