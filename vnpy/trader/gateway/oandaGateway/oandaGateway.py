# encoding: UTF-8

'''
vn.oanda的gateway接入

由于OANDA采用的是外汇做市商的交易模式，因此和国内接口方面有若干区别，具体如下：

* 行情数据反映的是OANDA的报价变化，因此只有买卖价，而没有成交价

* OANDA的持仓管理分为单笔成交持仓（Trade数据，国内没有）
  和单一资产汇总持仓（Position数据）
  
* OANDA系统中的所有时间都采用UTC时间（世界协调时，中国是UTC+8）

* 由于采用的是外汇做市商的模式，用户的限价委托当价格被触及时就会立即全部成交，
  不会出现部分成交的情况，因此委托状态只有已报、成交、撤销三种
  
* 外汇市场采用24小时交易，因此OANDA的委托不像国内收盘后自动失效，需要用户指定
  失效时间，本接口中默认设置为24个小时候失效
'''


import os
import json
import datetime

from vnpy.api.oanda import OandaApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath

# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = 'limit'
priceTypeMap[PRICETYPE_MARKETPRICE] = 'market'
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = 'buy'
directionMap[DIRECTION_SHORT] = 'sell'
directionMapReverse = {v: k for k, v in directionMap.items()}


########################################################################
class OandaGateway(VtGateway):
    """OANDA接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='OANDA'):
        """Constructor"""
        super(OandaGateway, self).__init__(eventEngine, gatewayName)
        
        self.api = Api(self)     
        
        self.qryEnabled = False         # 是否要启动循环查询
        
        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)             
        
    #----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
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
            token = str(setting['token'])
            accountId = str(setting['accountId'])
            settingName = str(setting['settingName'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 初始化接口
        self.api.init(settingName, token, accountId)
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'接口初始化成功'
        self.onLog(log)

        # 查询信息
        self.api.qryInstruments()
        self.api.qryOrders()
        self.api.qryTrades()
        
        # 初始化并启动查询
        self.initQuery()
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        pass
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.api.sendOrder_(orderReq)
        
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.api.cancelOrder_(cancelOrderReq)
        
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        self.api.getAccountInfo()
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.api.getPositions()
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.api.exit()
        
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
class Api(OandaApi):
    """OANDA的API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(Api, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.orderDict = {}     # 缓存委托数据
        
    #----------------------------------------------------------------------
    def onError(self, error, reqID):
        """错误信息回调"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorMsg = error
        self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onGetInstruments(self, data, reqID):
        """回调函数"""
        if not 'instruments' in data:
            return
        l = data['instruments']
        for d in l:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            
            contract.symbol = d['instrument']
            contract.name = d['displayName']
            contract.exchange = EXCHANGE_OANDA
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.priceTick = float(d['pip'])
            contract.size = 1
            contract.productClass = PRODUCT_FOREX
            self.gateway.onContract(contract)
        
        self.writeLog(u'交易合约信息查询完成')

    #----------------------------------------------------------------------
    def onGetAccountInfo(self, data, reqID):
        """回调函数"""
        account = VtAccountData()
        account.gatewayName = self.gatewayName
        
        account.accountID = str(data['accountId'])
        account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
        
        account.available = data['marginAvail']
        account.margin = data['marginUsed']
        account.closeProfit = data['realizedPl']
        account.positionProfit = data['unrealizedPl']
        account.balance = data['balance']
        
        self.gateway.onAccount(account)
        
    #----------------------------------------------------------------------
    def onGetOrders(self, data, reqID):
        """回调函数"""
        if not 'orders' in data:
            return
        l = data['orders']  
        
        for d in l:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            
            order.symbol = d['instrument']
            order.exchange = EXCHANGE_OANDA
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            order.orderID = str(d['id'])
            
            order.direction = directionMapReverse.get(d['side'], DIRECTION_UNKNOWN)
            order.offset = OFFSET_NONE
            order.status = STATUS_NOTTRADED     # OANDA查询到的订单都是活动委托
            
            order.price = d['price']
            order.totalVolume = d['units']
            order.orderTime = getTime(d['time'])
            
            order.vtOrderID = '.'.join([self.gatewayName , order.orderID])
            
            self.gateway.onOrder(order)
            
            self.orderDict[order.orderID] = order
            
        self.writeLog(u'委托信息查询完成')
    
    #----------------------------------------------------------------------
    def onGetPositions(self, data, reqID):
        """回调函数"""
        if not 'positions' in data:
            return
        l = data['positions']
        
        for d in l:
            pos = VtPositionData()
            pos.gatewayName = self.gatewayName
            
            pos.symbol = d['instrument']
            pos.exchange = EXCHANGE_OANDA
            pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])
            pos.direction = directionMapReverse.get(d['side'], DIRECTION_UNKNOWN)
            pos.position = d['units']
            pos.price = d['avgPrice']
            pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
            
            self.gateway.onPosition(pos)

    #----------------------------------------------------------------------
    def onGetTransactions(self, data, reqID):
        """回调函数"""
        if not 'transactions' in data:
            return
        l = data['transactions']
        
        for d in l:
            # 这里我们只关心委托成交
            if d['type'] == 'ORDER_FILLED':
                trade = VtTradeData()
                trade.gatewayName = self.gatewayName
                
                trade.symbol = d['instrument']
                trade.exchange = EXCHANGE_OANDA
                trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
                trade.tradeID = str(d['id'])
                trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
                trade.orderID = str(d['orderId'])
                trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])                 
                trade.direction = directionMapReverse.get(d['side'], DIRECTION_UNKNOWN)
                trade.offset = OFFSET_NONE
                trade.price = d['price']
                trade.volume = d['units']
                trade.tradeTime = getTime(d['time'])
                
                self.gateway.onTrade(trade)
                
        self.writeLog(u'成交信息查询完成')
        
    #----------------------------------------------------------------------
    def onPrice(self, data):
        """行情推送"""
        if 'tick' not in data:
            return
        d = data['tick']
        
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
    
        tick.symbol = d['instrument']
        tick.exchange = EXCHANGE_OANDA
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])    
        tick.bidPrice1 = d['bid']
        tick.askPrice1 = d['ask']
        tick.time = getTime(d['time']) + '.0'   # 补齐毫秒部分
        tick.date = datetime.datetime.utcnow().strftime('%Y%m%d')  # OANDA的时间是UTC标准时
        
        # 做市商的TICK数据只有买卖的报价，因此最新价格选用中间价代替
        tick.lastPrice = (tick.bidPrice1 + tick.askPrice1)/2        
        
        self.gateway.onTick(tick)
        
    #----------------------------------------------------------------------
    def onEvent(self, data):
        """事件推送（成交等）"""
        if 'transaction' not in data:
            return
        
        d = data['transaction']
        
        # 委托成交
        if d['type'] == 'ORDER_FILLED':
            # 推送成交事件
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            
            trade.symbol = d['instrument']
            trade.exchange = EXCHANGE_OANDA
            trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
            
            trade.tradeID = str(d['id'])
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
            
            trade.orderID = str(d['orderId'])
            trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])                    

            trade.direction = directionMapReverse.get(d['side'], DIRECTION_UNKNOWN)
            trade.offset = OFFSET_NONE
            
            trade.price = d['price']
            trade.volume = d['units']
            trade.tradeTime = getTime(d['time'])
            
            self.gateway.onTrade(trade)      
            
            # 推送委托事件
            order = self.orderDict.get(str(d['orderId']), None)
            if not order:
                return
            order.status = STATUS_ALLTRADED
            self.gateway.onOrder(order)             
        
        # 委托下达
        elif d['type'] in ['MARKET_ORDER_CREATE', 'LIMIT_ORDER_CREATE']:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
    
            order.symbol = d['instrument']
            order.exchange = EXCHANGE_OANDA
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            order.orderID = str(d['id'])
            order.direction = directionMapReverse.get(d['side'], DIRECTION_UNKNOWN)
            order.offset = OFFSET_NONE
            order.status = STATUS_NOTTRADED    
            order.price = d['price']
            order.totalVolume = d['units']
            order.orderTime = getTime(d['time'])
            order.vtOrderID = '.'.join([self.gatewayName , order.orderID])
    
            self.gateway.onOrder(order)   
            self.orderDict[order.orderID] = order
            
        # 委托撤销
        elif d['type'] == 'ORDER_CANCEL':
            order = self.orderDict.get(str(d['orderId']), None)
            if not order:
                return
            order.status = STATUS_CANCELLED
            self.gateway.onOrder(order)
    
    #----------------------------------------------------------------------
    def writeLog(self, logContent):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = logContent
        self.gateway.onLog(log)
        
    #----------------------------------------------------------------------
    def qryInstruments(self):
        """查询合约"""
        params = {'accountId': self.accountId}
        self.getInstruments(params)
        
    #----------------------------------------------------------------------
    def qryOrders(self):
        """查询委托"""
        self.getOrders({})
        
    #----------------------------------------------------------------------
    def qryTrades(self):
        """查询成交"""
        # 最多查询100条记录
        self.getTransactions({'count': 100})
        
    #----------------------------------------------------------------------
    def sendOrder_(self, orderReq):
        """发送委托"""
        params = {}
        params['instrument'] = orderReq.symbol
        params['units'] = orderReq.volume
        params['side'] = directionMap.get(orderReq.direction, '')
        params['price'] = orderReq.price
        params['type'] = priceTypeMap.get(orderReq.priceType, '')
        
        # 委托有效期24小时
        expire = datetime.datetime.now() + datetime.timedelta(days=1)
        params['expiry'] = expire.isoformat('T') + 'Z'
        
        self.sendOrder(params)
    
    #----------------------------------------------------------------------
    def cancelOrder_(self, cancelOrderReq):
        """撤销委托"""
        self.cancelOrder(cancelOrderReq.orderID)
    
    
#----------------------------------------------------------------------
def getTime(t):
    """把OANDA返回的时间格式转化为简单的时间字符串"""
    return t[11:19]