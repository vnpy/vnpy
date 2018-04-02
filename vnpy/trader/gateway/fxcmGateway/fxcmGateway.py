# encoding: UTF-8

import os
import json
from datetime import datetime

from vnpy.api.fxcm import FxcmApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtConstant import *
from vnpy.trader.vtFunction import getJsonPath

# 产品类型映射
productMapReverse = {}
productMapReverse[1] = PRODUCT_FOREX
productMapReverse[2] = PRODUCT_DEFER
productMapReverse[3] = PRODUCT_DEFER
productMapReverse[4] = PRODUCT_DEFER
productMapReverse[5] = PRODUCT_DEFER
productMapReverse[6] = PRODUCT_DEFER
productMapReverse[7] = PRODUCT_INDEX

# 委托状态映射
statusMapReverse = {}
statusMapReverse[1] = STATUS_NOTTRADED
statusMapReverse[3] = STATUS_CANCELLED
statusMapReverse[9] = STATUS_ALLTRADED


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
class FxcmGateway(VtGateway):
    """FXCM接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='FXCM'):
        """Constructor"""
        super(FxcmGateway, self).__init__(eventEngine, gatewayName)
        
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
            port = int(setting['port'])
            url = str(setting['url'])
            token = str(setting['token'])
            proxy = str(setting['proxy'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 初始化接口
        self.api.connect(url, port, token, proxy)
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        #self.api.updateSubscriptions(subscribeReq.symbol)
        self.api.subscribe(subscribeReq.symbol)
        
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
        pass
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        pass
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.api.stop()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        pass
    
    #----------------------------------------------------------------------
    def query(self, event):
        """注册到事件处理引擎上的查询函数"""
        pass
    
    #----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        pass
    
    #----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        pass
    


########################################################################
class Api(FxcmApi):
    """FXCM的API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(Api, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.account = ''
        
        self.orderDict = {}     # 缓存委托数据
        self.tradeDict = {}
        self.accountDict = {}
        self.positionDict = {}  # t:symbol
        
    #----------------------------------------------------------------------
    def onConnect(self):
        """连接回调"""
        self.writeLog(u'服务器连接成功')
        
        self.getInstruments()
        
    #----------------------------------------------------------------------
    def onDisconnect(self):
        """断开回调"""
        self.writeLog(u'服务器连接断开')
        
    #----------------------------------------------------------------------
    def onError(self, error, reqid):
        """错误回调"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = 0
        err.errorTime = datetime.now().strftime('%H:%M:%S')
        err.errorMsg = error
        self.gateway.onError(err)
    
    #----------------------------------------------------------------------
    def onGetInstruments(self, data, reqid):
        """查询合约代码回调"""
        for d in data['data']['instrument']:
            if not d['visible']:
                self.updateSubscriptions(d['symbol'])
                self.writeLog(u'添加合约%s到交易表' %d['symbol'])
                
        self.qryContracts()
        self.qryOrders()
        self.qryTrades()
        self.qryPositions()
        self.qryAccounts()        
        
    #----------------------------------------------------------------------
    def onGetModel(self, data, reqid):
        """查询表回调"""
        if 'offers' in data:
            for d in data['offers']:
                self.processContracts(d)
            self.writeLog(u'合约信息查询成功')
            #self.subscribeModel(self.MODEL_OFFER)
            
        elif 'orders' in data:
            for d in data['orders']:
                self.processOrders(d)
            self.writeLog(u'委托查询成功')
            self.subscribeModel(self.MODEL_ORDER)
            
        elif 'closed_positions' in data:
            for d in data['closed_positions']:
                self.processTrades(d)
            self.writeLog(u'已平成交查询成功')
            self.subscribeModel(self.MODEL_CLOSEDPOSITION)
            
        elif 'open_positions' in data:
            for d in data['open_positions']:
                self.processTrades(d)
            self.writeLog(u'未平成交查询成功')
            self.subscribeModel(self.MODEL_OPENPOSITION)
            
        elif 'summary' in data:
            for d in data['summary']:
                self.processPositions(d)
            self.writeLog(u'持仓查询成功')
            self.subscribeModel(self.MODEL_SUMMARY)
            
        elif 'accounts' in data:
            for d in data['accounts']:
                self.processAccounts(d)
            self.writeLog(u'账户查询成功')
            self.subscribeModel(self.MODEL_ACCOUNT)
    
    #----------------------------------------------------------------------
    def processContracts(self, d):
        """处理合约数据"""
        contract = VtContractData()
        contract.gatewayName = self.gatewayName
        
        contract.symbol = d['currency']
        contract.exchange = EXCHANGE_FXCM
        contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
        
        contract.name = contract.symbol
        contract.productClass = productMapReverse.get(d['instrumentType'], PRODUCT_UNKNOWN)
        contract.priceTick = d['pip'] * d['pipFraction']
        contract.size = 1000
        
        self.gateway.onContract(contract)       
    
    #----------------------------------------------------------------------
    def processOrders(self, d):
        """处理委托"""
        if 'status' not in d:
            return
        
        if d['orderId'] not in self.orderDict:
            order = VtOrderData()
            order.gatewayName = self.gatewayName            

            order.symbol = d['currency']
            order.exchange = EXCHANGE_FXCM
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            order.orderID = d['orderId']
            order.vtOrderID = '.'.join([order.gatewayName, order.orderID])        
            
            if d['isBuy']:
                order.price = d['buy']
                order.direction = DIRECTION_LONG
            else:
                order.price = d['sell']
                order.direction = DIRECTION_SHORT
            
            order.offset = OFFSET_NONE
            
            order.totalVolume = d['amountK']
            order.status = statusMapReverse.get(d['status'], STATUS_UNKNOWN)
            if order.status == STATUS_ALLTRADED:
                order.tradedVolume = order.totalVolume
            
            d, t = getTime(d['time'])
            order.orderTime = t
            
            self.orderDict[order.orderID] = order
        else:
            order = self.orderDict[d['orderId']]
            order.status = statusMapReverse.get(d['status'], STATUS_UNKNOWN)
            if order.status == STATUS_ALLTRADED:
                order.tradedVolume = order.totalVolume
                
        self.gateway.onOrder(order)
    
    #----------------------------------------------------------------------
    def processTrades(self, d):
        """处理成交"""
        if 'isTotal' in d:
            return
        
        # 成交记录只需要推送一次
        if d['tradeId'] in self.tradeDict:
            return
    
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName
        
        trade.symbol = d['currency']
        trade.exchange = EXCHANGE_FXCM
        trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
        
        trade.tradeID = d['tradeId']
        trade.vtTradeID = '.'.join([trade.gatewayName, trade.tradeID])
        
        if d['isBuy']:
            trade.direction = DIRECTION_LONG
        else:
            trade.direction = DIRECTION_SHORT        
        trade.offset = OFFSET_NONE
        
        trade.price = d['open']
        trade.volume = d['amountK']
        
        if 'time' in d:
            s = d['time']
        else:
            s = d['openTime']
            
        d, t = getTime(s)
        
        trade.tradeTime = t            
        
        self.gateway.onTrade(trade)
        
        self.tradeDict[trade.tradeID] = trade
    
    #----------------------------------------------------------------------
    def processAccounts(self, d):
        """处理资金"""
        if 'isTotal' in d:
            return        
        
        account = VtAccountData()
        account.gatewayName = self.gatewayName
        
        account.accountID = d['accountId']
        account.vtAccountID = '.'.join([account.gatewayName, account.accountID])
        
        account.balance = d['equity']
        account.available = d['usableMargin']
        account.margin = d['usdMr3']
        account.positionProfit = d['grossPL']
        
        self.gateway.onAccount(account)
        
        self.account = account.accountID
    
    #----------------------------------------------------------------------
    def processPositions(self, d):
        """处理持仓"""
        if 'isTotal' in d:
            return
        
        # 多头
        position = VtPositionData()
        position.gatewayName = self.gatewayName
        
        if 'currency' in d:
            position.symbol = d['currency']
            self.positionDict[d['t']] = d['currency']
        else:
            position.symbol = self.positionDict[d['t']]
            
        position.exchange = EXCHANGE_FXCM
        position.vtSymbol = '.'.join([position.symbol, position.exchange])
        
        position.direction = DIRECTION_LONG
        position.vtPositionName = '.'.join([position.vtSymbol, position.direction])
        
        position.position = d['amountKBuy']
        position.price = d['avgBuy']
        position.positionProfit = d['plBuy']
        
        self.gateway.onPosition(position)
        
        # 空头
        position = VtPositionData()
        position.gatewayName = self.gatewayName
        
        if 'currency' in d:
            position.symbol = d['currency']
            self.positionDict[d['t']] = d['currency']
        else:
            position.symbol = self.positionDict[d['t']]
            
        position.exchange = EXCHANGE_FXCM
        position.vtSymbol = '.'.join([position.symbol, position.exchange])
        
        position.direction = DIRECTION_SHORT
        position.vtPositionName = '.'.join([position.vtSymbol, position.direction])
        
        position.position = d['amountKSell']
        position.price = d['avgSell']
        position.positionProfit = d['plSell']
        
        self.gateway.onPosition(position)        

    #----------------------------------------------------------------------
    def onSubscribe(self, data, reqid):
        """订阅行情回调"""
        symbol = data['pairs'][0]['Symbol']
        self.writeLog(u'%s行情订阅成功' %symbol)
    
    #----------------------------------------------------------------------
    def onUnsubscribe(self, data, reqid):
        """退订行情回调"""
        pass
        
    #----------------------------------------------------------------------
    def onSubscribeModel(self, data, reqid):
        """订阅表回调"""
        pass
    
    #----------------------------------------------------------------------
    def onUnsubscribeModel(self, data, reqid):
        """退订表回调"""
        pass
    
    #----------------------------------------------------------------------
    def onUpdateSubscriptions(self, data, reqid):
        """订阅表回调"""
        self.writeLog(u'订阅表更新%s' %data)
    
    #----------------------------------------------------------------------
    def onOpenTrade(self, data, reqid):
        """开仓回调"""
        print data, reqid
        
    #----------------------------------------------------------------------
    def onCloseTrade(self, data, reqid):
        """平仓回调"""
        print data, reqid 
        
    #----------------------------------------------------------------------
    def onChangeOrder(self, data, reqid):
        """改单回调"""
        print data, reqid       

    #----------------------------------------------------------------------
    def onDeleteOrder(self, data, reqid):
        """撤单回调"""
        print data, reqid       
    
    #----------------------------------------------------------------------
    def onPriceUpdate(self, data):
        """行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
        
        tick.symbol = data['Symbol']
        tick.exchange = EXCHANGE_FXCM
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])  
        
        rates = data['Rates']
        tick.bidPrice1 = rates[0]
        tick.askPrice1 = rates[1]
        tick.lastPrice = (tick.bidPrice1 + tick.askPrice1)/2
        tick.highPrice = rates[2]
        tick.lowPrice = rates[3]
        
        t = datetime.fromtimestamp(data['Updated']/1000)
        tick.date = t.strftime('%Y%m%d')
        tick.time = t.strftime('%H:%M:%S.%f')
        tick.datetime = t
        
        self.gateway.onTick(tick)
        
    #----------------------------------------------------------------------
    def onModelUpdate(self, data):
        """表推送"""
        if 'orderId' in data:
            self.processOrders(data)
        elif 'tradeId' in data:
            self.processTrades(data)
        elif 'avgBuy' in data:
            self.processPositions(data)
        elif 'accountId' in data:
            self.processAccounts(data)

    #----------------------------------------------------------------------
    def writeLog(self, logContent):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = logContent
        self.gateway.onLog(log)
        
    #----------------------------------------------------------------------
    def qryContracts(self):
        """查询合约"""
        self.getModel(self.MODEL_OFFER)
        
    #----------------------------------------------------------------------
    def qryOrders(self):
        """查询委托"""
        self.getModel(self.MODEL_ORDER)
        
    #----------------------------------------------------------------------
    def qryTrades(self):
        """查询成交"""
        self.getModel(self.MODEL_CLOSEDPOSITION)
        self.getModel(self.MODEL_OPENPOSITION)
        
    #----------------------------------------------------------------------
    def qryAccounts(self):
        """查询资金"""
        self.getModel(self.MODEL_ACCOUNT)
        
    #----------------------------------------------------------------------
    def qryPositions(self):
        """查询持仓"""
        self.getModel(self.MODEL_SUMMARY)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发送委托"""
        accountID = self.account
        symbol = orderReq.symbol
        
        if orderReq.direction == DIRECTION_LONG:
            isBuy = 'true'
        else:
            isBuy = 'false'
            
        amount = orderReq.volume
        rate = orderReq.price
        
        if orderReq.priceType == PRICETYPE_MARKETPRICE:
            reqid = self.openTrade(accountID, symbol, isBuy, amount, 
                                   1, 'AtMarket', 'DAY')
        else:
            reqid = self.createEntryOrder(accountID, symbol, isBuy, rate,
                                          amount, 'AtMarket', 'DAY', limit=1)
            
        return reqid
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤销委托"""
        self.deleteOrder(cancelOrderReq.orderID)



#----------------------------------------------------------------------
def getTime(s):
    """把OANDA返回的时间格式转化为简单的时间字符串"""
    month = s[:2]
    day = s[2:4]
    year = s[4:8]
    hour = s[8:10]
    minute = s[10:12]
    second = s[12:]
    
    t = ':'.join([hour, minute, second])
    d = ''.join([year, month, day])
    return d, t