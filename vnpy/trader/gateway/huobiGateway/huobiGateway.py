# encoding: UTF-8

'''
vn.sec的gateway接入
'''

import os
import json
from datetime import datetime
from copy import copy
from math import pow

from vnpy.api.huobi import TradeApi, DataApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath


# 以下为一些VT类型和SEC类型的映射字典
priceTypeMap = {}
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
#directionMap[DIRECTION_LONG] = DATA_TYPE.DFITCSEC_ED_Buy
#directionMap[DIRECTION_SHORT] = DATA_TYPE.DFITCSEC_ED_Sell
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {}
#offsetMap[OFFSET_OPEN] = DATA_TYPE.DFITCSEC_OCF_Open
#offsetMap[OFFSET_CLOSE] = DATA_TYPE.DFITCSEC_OCF_Close
offsetMapReverse = {v:k for k,v in offsetMap.items()}


# 委托状态类型映射
statusMapReverse = {}
statusMapReverse['pre-submitted'] = STATUS_UNKNOWN
statusMapReverse['submitting'] = STATUS_UNKNOWN
statusMapReverse['submitted'] = STATUS_NOTTRADED
statusMapReverse['partial-filled'] = STATUS_PARTTRADED
statusMapReverse['partial-canceled'] = STATUS_CANCELLED
statusMapReverse['filled'] = STATUS_ALLTRADED
statusMapReverse['canceled'] = STATUS_CANCELLED


#----------------------------------------------------------------------
def print_dict(d):
    """"""
    print '-' * 30
    l = d.keys()
    l.sort()
    for k in l:
        print '%s:%s' %(k, d[k])
    

########################################################################
class HuobiGateway(VtGateway):
    """火币接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='HUOBI'):
        """Constructor"""
        super(HuobiGateway, self).__init__(eventEngine, gatewayName)
        
        self.dataApi = HuobiDataApi(self)       # 行情API
        self.tradeApi = HuobiTradeApi(self)     # 交易API
        
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
            exchange = str(setting['exchange'])
            accessKey = str(setting['accessKey'])
            secretKey = str(setting['secretKey'])
            symbols = setting['symbols']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 创建行情和交易接口对象
        self.dataApi.connect(exchange)
        self.tradeApi.connect(exchange, accessKey, secretKey, symbols)
        
        # 初始化并启动查询
        self.initQuery()
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        self.dataApi.subscribe(subscribeReq)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.tradeApi.sendOrder(orderReq)
        
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.tradeApi.cancelOrder(cancelOrderReq)
        
    #----------------------------------------------------------------------
    def qryInfo(self):
        """查询委托、成交、持仓"""
        self.tradeApi.qryOrder()
        self.tradeApi.qryTrade()
        self.tradeApi.qryPosition()
            
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        if self.mdConnected:
            self.dataApi.close()
        if self.tdConnected:
            self.tradeApi.close()
        
    #----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryInfo]
            
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
class HuobiDataApi(DataApi):
    """行情API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(HuobiDataApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.connectionStatus = False       # 连接状态
        
        self.tickDict = {}
        
    #----------------------------------------------------------------------
    def connect(self, exchange):
        """连接服务器"""
        if exchange == 'huobi':
            url = 'wss://api.huobi.pro/ws'
        else:
            url = 'wss://api.hadax.com/ws'
        
        self.connectionStatus = super(HuobiDataApi, self).connect(url)
        self.gateway.mdConnected = True
        
        if self.connectionStatus:
            self.writeLog(u'行情服务器连接成功')
        
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅合约"""
        if not self.connectionStatus:
            return
        
        symbol = subscribeReq.symbol
        if symbol in self.tickDict:
            return
        
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
        tick.symbol = symbol
        tick.exchange = EXCHANGE_HUOBI
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
        self.tickDict[symbol] = tick
        
        self.subscribeMarketDepth(symbol)
        self.subscribeMarketDetail(symbol)
        #self.subscribeTradeDetail(symbol)
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)
        
    #----------------------------------------------------------------------
    def onError(self, msg):
        """错误推送"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = 'Data'
        err.errorMsg = msg
        self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onMarketDepth(self, data):
        """行情深度推送 """
        symbol = data['ch'].split('.')[1]
        
        tick = self.tickDict.get(symbol, None)
        if not tick:
            return
        
        tick.datetime = datetime.fromtimestamp(data['ts']/1000)
        tick.date = tick.datetime.strftime('%Y%m%d')
        tick.time = tick.datetime.strftime('%H:%M:%S.%f')
        
        bids = data['tick']['bids']
        for n in range(5):
            l = bids[n]
            tick.__setattr__('bidPrice' + str(n+1), l[0])
            tick.__setattr__('bidVolume' + str(n+1), l[1])
        
        asks = data['tick']['asks']    
        for n in range(5):
            l = asks[n]    
            tick.__setattr__('askPrice' + str(n+1), l[0])
            tick.__setattr__('askVolume' + str(n+1), l[1])
        
        #print '-' * 50    
        #for d in data['tick']['asks']:
            #print 'ask', d
            
        #for d in data['tick']['bids']:
            #print 'bid', d
            
        #print '-' * 50    
        #print 'ask5', tick.askPrice5, tick.askVolume5
        #print 'ask4', tick.askPrice4, tick.askVolume4
        #print 'ask3', tick.askPrice3, tick.askVolume3
        #print 'ask2', tick.askPrice2, tick.askVolume2
        #print 'ask1', tick.askPrice1, tick.askVolume1
        
        #print 'bid1', tick.bidPrice1, tick.bidVolume1        
        #print 'bid2', tick.bidPrice2, tick.bidVolume2
        #print 'bid3', tick.bidPrice3, tick.bidVolume3
        #print 'bid4', tick.bidPrice4, tick.bidVolume4
        #print 'bid5', tick.bidPrice5, tick.bidVolume5
        
        if tick.lastPrice:
            newtick = copy(tick)
            self.gateway.onTick(tick)
    
    #----------------------------------------------------------------------
    def onTradeDetail(self, data):
        """成交细节推送"""
        print data
    
    #----------------------------------------------------------------------
    def onMarketDetail(self, data):
        """市场细节推送"""
        symbol = data['ch'].split('.')[1]
        
        tick = self.tickDict.get(symbol, None)
        if not tick:
            return     
        
        tick.datetime = datetime.fromtimestamp(data['ts']/1000)
        tick.date = tick.datetime.strftime('%Y%m%d')
        tick.time = tick.datetime.strftime('%H:%M:%S.%f')
        
        t = data['tick']
        tick.openPrice = t['open']
        tick.highPrice = t['high']
        tick.lowPrice = t['low']
        tick.lastPrice = t['close']
        tick.volume = t['vol']
        tick.preClosePrice = tick.openPrice
        
        if tick.bidPrice1:
            newtick = copy(tick)
            self.gateway.onTick(tick)
        

    
########################################################################
class HuobiTradeApi(TradeApi):
    """交易API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(HuobiTradeApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.connectionStatus = False       # 连接状态
        self.accountid = ''
        
        self.todayDate = datetime.now().strftime('%Y-%m-%d')
        
        self.orderDict = {}                 # 缓存委托数据的字典
        self.symbols = []                   # 所有交易代码的字符串集合
        
        self.qryTradeID = None  # 查询起始成交编号
        self.tradeIDs = set()   # 成交编号集合
        
        self.qryOrderID = None  # 查询起始委托编号
        
        self.localid = 100000       # 订单编号，10000为起始
        self.reqLocalDict = {}      # 请求编号和本地委托编号映射
        self.localOrderDict = {}    # 本地委托编号和交易所委托编号映射
        self.orderLocalDict = {}    # 交易所委托编号和本地委托编号映射
        self.cancelReqDict = {}     # 撤单请求字典
        
    #----------------------------------------------------------------------
    def connect(self, exchange, accessKey, secretKey, symbols=''):
        """初始化连接"""
        if not self.connectionStatus:
            self.symbols = symbols
            
            self.connectionStatus = self.init(exchange, accessKey, secretKey)
            self.gateway.tdConnected = True
            self.start()
            self.writeLog(u'交易服务器连接成功')
            
            self.getSymbols()

    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        if self.accountid:
            self.getAccountBalance(self.accountid)
            
    #----------------------------------------------------------------------
    def qryOrder(self):
        """查询委托"""
        if not self.accountid:
            return
        
        states = 'pre-submitted,submitting,submitted,partial-filled,partial-canceled,filled,canceled'
        for symbol in self.symbols:
            self.getOrders(symbol, states, startDate=self.todayDate)
            #print u'查询委托', self.qryOrderID
            #self.getOrders(symbol, states, startDate=self.todayDate, from_=self.qryOrderID, direct='next')
    
    #----------------------------------------------------------------------
    def qryTrade(self):
        """查询成交"""
        if not self.accountid:
            return
        
        for symbol in self.symbols:
            self.getMatchResults(symbol, startDate=self.todayDate)
            #self.getMatchResults(symbol, startDate=self.todayDate, from_=self.qryTradeID)    
    
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        self.localid += 1
        localid = str(self.localid)
        vtOrderID = '.'.join([self.gatewayName, localid])
        
        if orderReq.direction == DIRECTION_LONG:
            type_ = 'buy-limit'
        else:
            type_ = 'sell-limit'
        
        reqid = self.placeOrder(self.accountid, 
                                str(orderReq.volume), 
                                orderReq.symbol, 
                                type_, 
                                price=str(orderReq.price),
                                source='api')
        
        self.reqLocalDict[reqid] = localid
        
        print 'send', vtOrderID
        # 返回订单号
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        localid = cancelOrderReq.orderID
        orderID = self.localOrderDict.get(localid, None)
        
        if orderID:
            super(HuobiTradeApi, self).cancelOrder(orderID)
            if localid in self.cancelReqDict:
                del self.cancelReqDict[localid]
        else:
            self.cancelReqDict[localid] = cancelOrderReq
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    #----------------------------------------------------------------------
    def onError(self, msg, reqid):
        """错误回调"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = 'Trade'
        err.errorMsg = msg
        self.gateway.onError(err)        
        
    #----------------------------------------------------------------------
    def onGetSymbols(self, data, reqid):
        """查询代码回调"""
        for d in data:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            
            contract.symbol = d['base-currency'] + d['quote-currency']
            contract.exchange = EXCHANGE_HUOBI
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            
            contract.name = '/'.join([d['base-currency'].upper(), d['quote-currency'].upper()])
            contract.priceTick = 1 / pow(10, d['price-precision'])
            contract.size = 1 / pow(10, d['amount-precision'])
            contract.productClass = PRODUCT_SPOT
            
            self.gateway.onContract(contract)
        
        self.writeLog(u'交易代码查询成功')
        self.getAccounts()
    
    #----------------------------------------------------------------------
    def onGetCurrencys(self, data, reqid):
        """查询货币回调"""
        pass
    
    #----------------------------------------------------------------------
    def onGetTimestamp(self, data, reqid):
        """查询时间回调"""
        print reqid, data    
        
    #----------------------------------------------------------------------
    def onGetAccounts(self, data, reqid):
        """查询账户回调"""
        for d in data:
            self.accountid = str(d['id'])
            self.writeLog(u'交易账户%s查询成功' %self.accountid)
    
    #----------------------------------------------------------------------
    def onGetAccountBalance(self, data, reqid):
        """查询余额回调"""
        posDict = {}
        
        for d in data['list']:
            symbol = d['currency']
            pos = posDict.get(symbol, None)

            if not pos:
                pos = VtPositionData()
                pos.gatewayName = self.gatewayName
                pos.symbol = d['currency']
                pos.exchange = EXCHANGE_HUOBI
                pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])
                pos.direction = DIRECTION_LONG
                pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
            
            pos.position += float(d['balance'])
            if d['type'] == 'fozen':
                pos.frozen = float(d['balance'])
                
            posDict[symbol] = pos
        
        for pos in posDict.values():
            if pos.position:
                self.gateway.onPosition(pos)
        
    #----------------------------------------------------------------------
    def onGetOrders(self, data, reqid):
        """查询委托回调"""
        qryOrderID = None
        
        data.reverse()
        
        for d in data:
            orderID = d['id']
            strOrderID = str(orderID)
            updated = False
            
            if strOrderID in self.orderLocalDict:
                localid = self.orderLocalDict[strOrderID]
            else:
                self.localid += 1
                localid = str(self.localid)
                
                self.orderLocalDict[strOrderID] = localid
                self.localOrderDict[localid] = strOrderID
            
            order = self.orderDict.get(orderID, None)
            if not order:
                updated = True
                
                order = VtOrderData()
                order.gatewayName = self.gatewayName
                
                order.orderID = localid
                order.vtOrderID = '.'.join([order.gatewayName, order.orderID])
            
                order.symbol = d['symbol']
                order.exchange = EXCHANGE_HUOBI
                order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
                order.price = float(d['price'])
                order.totalVolume = float(d['amount'])
                order.orderTime = datetime.fromtimestamp(d['created-at']/1000).strftime('%H:%M:%S')
                
                if 'buy' in d['type']:
                    order.direction = DIRECTION_LONG
                else:
                    order.direction = DIRECTION_SHORT
                order.offset = OFFSET_NONE  
                
                self.orderDict[orderID] = order
            
            # 数据更新，只有当成交数量或者委托状态变化时，才执行推送
            if d['canceled-at']:
                order.cancelTime = datetime.fromtimestamp(d['canceled-at']/1000).strftime('%H:%M:%S')
            
            newTradedVolume = d['field-amount']
            newStatus = statusMapReverse.get(d['state'], STATUS_UNKNOWN)
            
            if newTradedVolume != order.tradedVolume or newStatus != order.status:
                updated = True
                order.tradedVolume = float(newTradedVolume)
                order.status = newStatus
            
            # 只推送有更新的数据
            if updated:
                self.gateway.onOrder(order)
                
            # 计算查询下标（即最早的未全成或撤委托）
            if order.status not in [STATUS_ALLTRADED, STATUS_CANCELLED]:
                if not qryOrderID:
                    qryOrderID = orderID
                else:
                    qryOrderID = min(qryOrderID, orderID)
            
        # 更新查询下标        
        if qryOrderID:
            self.qryOrderID = qryOrderID
        
    #----------------------------------------------------------------------
    def onGetMatchResults(self, data, reqid):
        """查询成交回调"""
        data.reverse()
        
        for d in data:
            tradeID = d['match-id']
            
            # 成交仅需要推送一次，去重判断
            if tradeID in self.tradeIDs:
                continue
            self.tradeIDs.add(tradeID)
            
            # 查询起始编号更新
            self.qryTradeID = max(tradeID, self.qryTradeID)
            
            # 推送数据            
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            
            trade.tradeID = str(tradeID)
            trade.vtTradeID = '.'.join([trade.tradeID, trade.gatewayName])
            
            trade.symbol = d['symbol']
            trade.exchange = EXCHANGE_HUOBI
            trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
            
            if 'buy' in d['type']:
                trade.direction = DIRECTION_LONG
            else:
                trade.direction = DIRECTION_SHORT
            trade.offset = OFFSET_NONE
            
            strOrderID = str(d['order-id'])
            localid = self.orderLocalDict.get(strOrderID, '')
            trade.orderID = localid
            trade.vtOrderID = '.'.join([trade.gatewayName, trade.orderID])
            
            trade.tradeID = str(tradeID)
            trade.vtTradeID = '.'.join([trade.gatewayName, trade.tradeID])
            
            trade.price = float(d['price'])
            trade.volume = float(d['filled-amount'])
            
            dt = datetime.fromtimestamp(d['created-at']/1000)
            trade.tradeTime = dt.strftime('%H:%M:%S')
            
            self.gateway.onTrade(trade)
        
    #----------------------------------------------------------------------
    def onGetOrder(self, data, reqid):
        """查询单一委托回调"""
        print reqid, data    
        
    #----------------------------------------------------------------------
    def onGetMatchResult(self, data, reqid):
        """查询单一成交回调"""
        print reqid, data    
        
    #----------------------------------------------------------------------
    def onPlaceOrder(self, data, reqid):
        """委托回调"""
        localid = self.reqLocalDict[reqid]
        
        self.localOrderDict[localid] = data
        self.orderLocalDict[data] = localid
        
        if localid in self.cancelReqDict:
            req = self.cancelReqDict[localid]
            self.cancelOrder(req)
    
    #----------------------------------------------------------------------
    def onCancelOrder(self, data, reqid):
        """撤单回调"""
        self.writeLog(u'委托撤单成功：%s' %data)      
        
    #----------------------------------------------------------------------
    def onBatchCancel(self, data, reqid):
        """批量撤单回调"""
        print reqid, data      
