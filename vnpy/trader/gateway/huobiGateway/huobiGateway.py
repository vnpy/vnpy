# encoding: UTF-8

'''
vn.sec的gateway接入
'''
from __future__ import print_function

import json
from datetime import datetime, timedelta
from copy import copy
from math import pow

from vnpy.api.huobi import TradeApi, DataApi
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath


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
    print('-' * 30)
    for key in sorted(d):
        print('%s:%s' % (key, d[key]))


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
            f = open(self.filePath)
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
        self.dataApi.connect(exchange, symbols)
        self.tradeApi.connect(exchange, symbols, accessKey, secretKey)

        # 初始化并启动查询
        self.initQuery()

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        pass
        #self.dataApi.subscribe(subscribeReq)

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

        #self.subscribeDict = {}

    #----------------------------------------------------------------------
    def connect(self, exchange, symbols):
        """连接服务器"""
        if exchange == 'huobi':
            url = 'wss://api.huobi.pro/ws'
        else:
            url = 'wss://api.hadax.com/ws'
            
        self.symbols = symbols

        self.connectionStatus = super(HuobiDataApi, self).connect(url)
        self.gateway.mdConnected = True

        if self.connectionStatus:
            self.writeLog(u'行情服务器连接成功')
            
            for symbol in self.symbols:
                self.subscribe(symbol)
            # 订阅所有之前订阅过的行情
            #for req in self.subscribeDict.values():
            #    self.subscribe(req)
            

    #----------------------------------------------------------------------
    def subscribe(self, symbol):
        """订阅合约"""
        #self.subscribeDict[subscribeReq.symbol] = subscribeReq

        if not self.connectionStatus:
            return

        #symbol = subscribeReq.symbol
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
            tick.__setattr__('bidPrice' + str(n+1), float(l[0]))
            tick.__setattr__('bidVolume' + str(n+1), float(l[1]))

        asks = data['tick']['asks']
        for n in range(5):
            l = asks[n]
            tick.__setattr__('askPrice' + str(n+1), float(l[0]))
            tick.__setattr__('askVolume' + str(n+1), float(l[1]))

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
        print(data)

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
        tick.openPrice = float(t['open'])
        tick.highPrice = float(t['high'])
        tick.lowPrice = float(t['low'])
        tick.lastPrice = float(t['close'])
        tick.volume = float(t['vol'])
        tick.preClosePrice = float(tick.openPrice)

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

        #self.activeOrderSet = set() # 活动委托集合

    #----------------------------------------------------------------------
    def connect(self, exchange, symbols, accessKey, secretKey):
        """初始化连接"""
        if not self.connectionStatus:
            self.symbols = symbols

            self.connectionStatus = self.init(exchange, accessKey, secretKey)
            self.gateway.tdConnected = True
            self.start()
            self.writeLog(u'交易服务器连接成功')

            self.getTimestamp()
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
        
        now = datetime.now()
        oneday = timedelta(1)
        todayDate = now.strftime('%Y-%m-%d')
        yesterdayDate = (now - oneday).strftime('%Y-%m-%d')

        statesAll = 'pre-submitted,submitting,submitted,partial-filled,partial-canceled,filled,canceled'
        statesActive = 'submitted,partial-filled'
        
        for symbol in self.symbols:
            self.getOrders(symbol, statesAll, startDate=todayDate)         # 查询今日所有状态的委托
            self.getOrders(symbol, statesActive, endDate=yesterdayDate)    # 查询昨日往前所有未结束的委托

    #----------------------------------------------------------------------
    def qryTrade(self):
        """查询成交"""
        if not self.accountid:
            return
        
        now = datetime.now()
        todayDate = now.strftime('%Y-%m-%d')
        
        for symbol in self.symbols:
            self.getMatchResults(symbol, startDate=todayDate, size=50)     # 只查询今日最新50笔成交

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
        # 忽略请求超时错误
        if '429' in msg or 'api-signature-not-valid' in msg:
            return
        
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
        event = Event(EVENT_LOG+'Time')
        event.dict_['data'] = datetime.fromtimestamp(data/1000)
        self.gateway.eventEngine.put(event)

    #----------------------------------------------------------------------
    def onGetAccounts(self, data, reqid):
        """查询账户回调"""
        for d in data:
            if str(d['type']) == 'spot':
                self.accountid = str(d['id'])
                self.writeLog(u'交易账户%s查询成功' %self.accountid)

    #----------------------------------------------------------------------
    def onGetAccountBalance(self, data, reqid):
        """查询余额回调"""
        accountDict = {}
        
        for d in data['list']:
            currency = d['currency']
            account = accountDict.get(currency, None)

            if not account:
                account = VtAccountData()
                account.gatewayName = self.gatewayName
                account.accountID = d['currency']
                account.vtAccountID = '.'.join([account.gatewayName, account.accountID])
                
                accountDict[currency] = account
                
            account.balance += float(d['balance'])
            if d['type'] == 'fozen':
                account.available = account.balance - float(d['balance'])

        for account in accountDict.values():
            self.gateway.onAccount(account)

    #----------------------------------------------------------------------
    def onGetOrders(self, data, reqid):
        """查询委托回调"""
        # 比对寻找已结束的委托号
        """
        newset = set([d['id'] for d in data])

        print '-'*50
        print [d['id'] for d in data]
        print self.activeOrderSet

        for id_ in self.activeOrderSet:
            if id_ not in newset:
                print 'finished:', id_
                self.getOrder(id_)

        #self.activeOrderSet = newset
        """

        # 推送数据
        #qryOrderID = None

        data.reverse()

        for d in data:
            orderID = d['id']

            #self.activeOrderSet.add(orderID)

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

            newTradedVolume = float(d['field-amount'])
            newStatus = statusMapReverse.get(d['state'], STATUS_UNKNOWN)

            if newTradedVolume != order.tradedVolume or newStatus != order.status:
                updated = True
            
            order.tradedVolume = newTradedVolume
            order.status = newStatus

            # 只推送有更新的数据
            if updated:
                self.gateway.onOrder(order)

            ## 计算查询下标（即最早的未全成或撤委托）
            #if order.status not in [STATUS_ALLTRADED, STATUS_CANCELLED]:
                #if not qryOrderID:
                    #qryOrderID = orderID
                #else:
                    #qryOrderID = min(qryOrderID, orderID)

        ## 更新查询下标
        #if qryOrderID:
            #self.qryOrderID = qryOrderID

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
        #orderID = data['id']
        #strOrderID = str(orderID)
        #localid = self.orderLocalDict[strOrderID]
        #order = self.orderDict[orderID]

        #order.tradedVolume = float(data['field-amount'])
        #order.status = statusMapReverse.get(data['state'], STATUS_UNKNOWN)

        #if data['canceled-at']:
            #order.cancelTime = datetime.fromtimestamp(data['canceled-at']/1000).strftime('%H:%M:%S')

        ## 完成的委托则从集合中移除
        #if order.status in [STATUS_ALLTRADED, STATUS_CANCELLED]:
            #self.activeOrderSet.remove(orderID)

        #self.gateway.onOrder(order)
        pass

    #----------------------------------------------------------------------
    def onGetMatchResult(self, data, reqid):
        """查询单一成交回调"""
        print(reqid, data)

    #----------------------------------------------------------------------
    def onPlaceOrder(self, data, reqid):
        """委托回调"""
        localid = self.reqLocalDict[reqid]

        self.localOrderDict[localid] = data
        self.orderLocalDict[data] = localid

        #self.activeOrderSet.add(data)

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
        print(reqid, data)
