# encoding: UTF-8

'''
Interactive Brokers的gateway接入，已经替换为vn.ib封装。

注意事项：
1. ib api只能获取和操作当前连接后下的单，并且每次重启程序后，之前下的单子收不到
2. ib api的成交也只会推送当前连接后的成交
3. ib api的持仓和账户更新可以订阅成主推模式，因此qryAccount和qryPosition就用不到了
4. 目前只支持股票和期货交易，ib api里期权合约的确定是基于Contract对象的多个字段，比较复杂暂时没做
5. 海外市场的交易规则和国内有很多细节上的不同，所以一些字段类型的映射可能不合理，如果发现问题欢迎指出
'''
from __future__ import print_function

import os
import json
import calendar
from datetime import datetime, timedelta
from copy import copy

from vnpy.api.ib import *
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath
from .language import text



# 以下为一些VT类型和CTP类型的映射字典
# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = 'LMT'
priceTypeMap[PRICETYPE_MARKETPRICE] = 'MKT'
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = 'BUY'
#directionMap[DIRECTION_SHORT] = 'SSHORT'   # SSHORT在IB系统中代表对股票的融券做空（而不是国内常见的卖出）
directionMap[DIRECTION_SHORT] = 'SELL'      # 出于和国内的统一性考虑，这里选择把IB里的SELL印射为vt的SHORT

directionMapReverse = {v: k for k, v in directionMap.items()}
directionMapReverse['BOT'] = DIRECTION_LONG
directionMapReverse['SLD'] = DIRECTION_SHORT

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_SMART] = 'SMART'
exchangeMap[EXCHANGE_NYMEX] = 'NYMEX'
exchangeMap[EXCHANGE_GLOBEX] = 'GLOBEX'
exchangeMap[EXCHANGE_IDEALPRO] = 'IDEALPRO'
exchangeMap[EXCHANGE_HKEX] = 'HKEX'
exchangeMap[EXCHANGE_HKFE] = 'HKFE'
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 报单状态映射
orderStatusMap = {}
orderStatusMap[STATUS_NOTTRADED] = 'Submitted'
orderStatusMap[STATUS_ALLTRADED] = 'Filled'
orderStatusMap[STATUS_CANCELLED] = 'Cancelled'
orderStatusMapReverse = {v:k for k,v in orderStatusMap.items()}
orderStatusMapReverse['PendingSubmit'] = STATUS_UNKNOWN     # 这里未来视乎需求可以拓展vt订单的状态类型
orderStatusMapReverse['PendingCancel'] = STATUS_UNKNOWN
orderStatusMapReverse['PreSubmitted'] = STATUS_UNKNOWN
orderStatusMapReverse['Inactive'] = STATUS_UNKNOWN

# 合约类型映射
productClassMap = {}
productClassMap[PRODUCT_EQUITY] = 'STK'
productClassMap[PRODUCT_FUTURES] = 'FUT'
productClassMap[PRODUCT_OPTION] = 'OPT'
productClassMap[PRODUCT_FOREX] = 'CASH'
productClassMap[PRODUCT_INDEX] = 'IND'
productClassMap[PRODUCT_SPOT] = 'CMDTY'
productClassMapReverse = {v:k for k,v in productClassMap.items()}

# 期权类型映射
optionTypeMap = {}
optionTypeMap[OPTION_CALL] = 'CALL'
optionTypeMap[OPTION_PUT] = 'PUT'
optionTypeMap = {v:k for k,v in optionTypeMap.items()}

# 货币类型映射
currencyMap = {}
currencyMap[CURRENCY_USD] = 'USD'
currencyMap[CURRENCY_CNY] = 'CNY'
currencyMap[CURRENCY_HKD] = 'HKD'
currencyMap = {v:k for k,v in currencyMap.items()}

# Tick数据的Field和名称映射
tickFieldMap = {}
tickFieldMap[0] = 'bidVolume1'
tickFieldMap[1] = 'bidPrice1'
tickFieldMap[2] = 'askPrice1'
tickFieldMap[3] = 'askVolume1'
tickFieldMap[4] = 'lastPrice'
tickFieldMap[5] = 'lastVolume'
tickFieldMap[6] = 'highPrice'
tickFieldMap[7] = 'lowPrice'
tickFieldMap[8] = 'volume'
tickFieldMap[9] = 'preClosePrice'
tickFieldMap[14] = 'openPrice'
tickFieldMap[22] = 'openInterest'

# Account数据Key和名称的映射
accountKeyMap = {}
accountKeyMap['NetLiquidationByCurrency'] = 'balance'
accountKeyMap['NetLiquidation'] = 'balance'
accountKeyMap['UnrealizedPnL'] = 'positionProfit'
accountKeyMap['AvailableFunds'] = 'available'
accountKeyMap['MaintMarginReq'] = 'margin'


########################################################################
class IbGateway(VtGateway):
    """IB接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='IB'):
        """Constructor"""
        super(IbGateway, self).__init__(eventEngine, gatewayName)
        
        self.host = EMPTY_STRING        # 连接地址
        self.port = EMPTY_INT           # 连接端口
        self.clientId = EMPTY_INT       # 用户编号
        self.accountCode = EMPTY_STRING # 账户编号
        
        self.tickerId = 0               # 订阅行情时的代码编号    
        self.tickDict = {}              # tick快照字典，key为tickerId，value为VtTickData对象
        self.tickProductDict = {}       # tick对应的产品类型字典，key为tickerId，value为产品类型
        
        self.orderId  = 0               # 订单编号
        self.orderDict = {}             # 报单字典，key为orderId，value为VtOrderData对象
        
        self.accountDict = {}           # 账户字典
        
        self.contractDict = {}          # 合约字典
        
        self.subscribeReqDict = {}      # 用来保存订阅请求的字典 
        
        self.connected = False          # 连接状态
        
        self.api = IbWrapper(self)      # API接口
        
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
            log.logContent = text.LOADING_ERROR
            self.onLog(log)
            return
        
        # 解析json文件
        setting = json.load(f)
        try:
            self.host = str(setting['host'])
            self.port = int(setting['port'])
            self.clientId = int(setting['clientId'])
            self.accountCode = str(setting['accountCode'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = text.CONFIG_KEY_MISSING
            self.onLog(log)
            return            
        
        # 发起连接
        self.api.eConnect(self.host, self.port, self.clientId, False)
        
        # 查询服务器时间
        self.api.reqCurrentTime()
    
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        # 如果尚未连接行情，则将订阅请求缓存下来后直接返回
        if not self.connected:
            self.subscribeReqDict[subscribeReq.symbol] = subscribeReq
            return
        
        contract = Contract()
        contract.localSymbol = str(subscribeReq.symbol)
        contract.exchange = exchangeMap.get(subscribeReq.exchange, '')
        contract.secType = productClassMap.get(subscribeReq.productClass, '')
        contract.currency = currencyMap.get(subscribeReq.currency, '')
        contract.expiry = subscribeReq.expiry
        contract.strike = subscribeReq.strikePrice
        contract.right = optionTypeMap.get(subscribeReq.optionType, '')

        # 获取合约详细信息
        self.tickerId += 1
        self.api.reqContractDetails(self.tickerId, contract)        
        
        # 创建合约对象并保存到字典中
        ct = VtContractData()
        ct.gatewayName = self.gatewayName
        ct.symbol = str(subscribeReq.symbol)
        ct.exchange = subscribeReq.exchange
        ct.vtSymbol = '.'.join([ct.symbol, ct.exchange])
        ct.productClass = subscribeReq.productClass
        self.contractDict[ct.vtSymbol] = ct
        
        # 订阅行情
        self.tickerId += 1   
        self.api.reqMktData(self.tickerId, contract, '', False, TagValueList())
        
        # 创建Tick对象并保存到字典中
        tick = VtTickData()
        tick.symbol = subscribeReq.symbol
        tick.exchange = subscribeReq.exchange
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
        tick.gatewayName = self.gatewayName
        self.tickDict[self.tickerId] = tick   
        self.tickProductDict[self.tickerId] = subscribeReq.productClass

    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        # 增加报单号1，最后再次进行查询
        # 这里双重设计的目的是为了防止某些情况下，连续发单时，nextOrderId的回调推送速度慢导致没有更新
        self.orderId += 1
        
        # 创建合约对象
        contract = Contract()
        contract.localSymbol = str(orderReq.symbol)
        contract.exchange = exchangeMap.get(orderReq.exchange, '')
        contract.secType = productClassMap.get(orderReq.productClass, '')
        contract.currency = currencyMap.get(orderReq.currency, '')
        contract.expiry = orderReq.expiry
        contract.strike = orderReq.strikePrice
        contract.right = optionTypeMap.get(orderReq.optionType, '')
        contract.lastTradeDateOrContractMonth = str(orderReq.lastTradeDateOrContractMonth)
        contract.multiplier = str(orderReq.multiplier)
        
        # 创建委托对象
        order = Order()
        order.orderId = self.orderId
        order.clientId = self.clientId
        order.action = directionMap.get(orderReq.direction, '')
        order.lmtPrice = orderReq.price
        order.totalQuantity = orderReq.volume
        order.orderType = priceTypeMap.get(orderReq.priceType, '')
        
        # 发送委托
        self.api.placeOrder(self.orderId, contract, order)
        
        # 查询下一个有效编号
        self.api.reqIds(1)
        
        # 返回委托编号
        vtOrderID = '.'.join([self.gatewayName, str(self.orderId)])
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.api.cancelOrder(int(cancelOrderReq.orderID))
    
    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        log = VtLogData()
        log.gatewayName = self.gatewayName        
        log.logContent = text.NONEED_TO_QRYACCOUNT
        self.onLog(log) 
    
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        log = VtLogData()
        log.gatewayName = self.gatewayName        
        log.logContent = text.NONEED_TO_QRYPOSITION
        self.onLog(log) 
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.api.eDisconnect()


########################################################################
class IbWrapper(IbApi):
    """IB回调接口的实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(IbWrapper, self).__init__()
        
        self.apiStatus = False               # 连接状态
        
        self.gateway = gateway                      # gateway对象
        self.gatewayName = gateway.gatewayName      # gateway对象名称
        
        self.tickDict = gateway.tickDict            # tick快照字典，key为tickerId，value为VtTickData对象
        self.orderDict = gateway.orderDict          # order字典
        self.accountDict = gateway.accountDict      # account字典
        self.contractDict = gateway.contractDict    # contract字典
        self.tickProductDict = gateway.tickProductDict
        self.subscribeReqDict = gateway.subscribeReqDict

    #----------------------------------------------------------------------
    def nextValidId(self, orderId):
        """"""
        self.gateway.orderId = orderId
        
    #----------------------------------------------------------------------
    def currentTime(self, time):
        """连接成功后推送当前时间"""
        dt = datetime.fromtimestamp(time)
        t = dt.strftime("%Y-%m-%d %H:%M:%S.%f")

        self.apiStatus = True
        self.gateway.connected = True
        
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = text.API_CONNECTED.format(time=t)
        self.gateway.onLog(log) 
        
        for symbol, req in self.subscribeReqDict.items():
            del self.subscribeReqDict[symbol]
            self.gateway.subscribe(req)        
        
    #----------------------------------------------------------------------
    def connectAck(self):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def error(self, id_, errorCode, errorString):
        """错误推送"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = errorCode
        err.errorMsg = errorString.decode('GBK')
        self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def accountSummary(self, reqId, account, tag, value, curency):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def accountSummaryEnd(self, reqId):
        """"""
        pass
         
    #----------------------------------------------------------------------
    def tickPrice(self, tickerId, field, price, canAutoExecute):
        """行情价格相关推送"""
        if field in tickFieldMap:
            # 对于股票、期货等行情，有新价格推送时仅更新tick缓存
            # 只有当发生成交后，tickString更新最新成交价时才推送新的tick
            # 即bid/ask的价格变动并不会触发新的tick推送
            tick = self.tickDict[tickerId]
            key = tickFieldMap[field]
            tick.__setattr__(key, price)
            
            # IB的外汇行情没有成交价和时间，通过本地计算生成，同时立即推送
            p = self.tickProductDict[tickerId]
            if p == PRODUCT_FOREX or p == PRODUCT_SPOT:
                tick.lastPrice = (tick.bidPrice1 + tick.askPrice1) / 2
                dt = datetime.now()
                tick.time = dt.strftime('%H:%M:%S.%f')
                tick.date = dt.strftime('%Y%m%d')
            
                # 行情数据更新
                newtick = copy(tick)
                self.gateway.onTick(newtick)
        else:
            print(field)
        
    #----------------------------------------------------------------------
    def tickSize(self, tickerId, field, size):
        """行情数量相关推送"""
        if field in tickFieldMap:
            tick = self.tickDict[tickerId]
            key = tickFieldMap[field]
            tick.__setattr__(key, size)   
        else:
            print(field)
        
    #----------------------------------------------------------------------
    def tickOptionComputation(self, tickerId, tickType, impliedVol, delta, optPrice, pvDividend, gamma, vega, theta, undPrice):
        """"""
        pass

    #----------------------------------------------------------------------
    def tickGeneric(self, tickerId, tickType, value):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def tickString(self, tickerId, tickType, value):
        """行情补充信息相关推送"""
        # 如果是最新成交时间戳更新
        if tickType == '45':
            tick = self.tickDict[tickerId]

            dt = datetime.fromtimestamp(value)
            tick.time = dt.strftime('%H:%M:%S.%f')
            tick.date = dt.strftime('%Y%m%d')

            newtick = copy(tick)
            self.gateway.onTick(newtick)              
        
    #----------------------------------------------------------------------
    def tickEFP(self, tickerId, tickType, basisPoints, formattedBasisPoints, totalDividends, holdDays, futureLastTradeDate, dividendImpact, dividendsToLastTradeDate):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def orderStatus(self, orderId, status, filled, remaining, avgFillPrice, permId, parentId, lastFillPrice, clientId, whyHeld):
        """委托状态更新"""
        orderId = str(orderId)
        
        if orderId in self.orderDict:
            od = self.orderDict[orderId]
        else:
            od = VtOrderData()  # od代表orderData
            od.orderID = orderId
            od.vtOrderID = '.'.join([self.gatewayName, orderId])
            od.gatewayName = self.gatewayName
            self.orderDict[orderId] = od
        
        od.status = orderStatusMapReverse.get(status, STATUS_UNKNOWN)
        od.tradedVolume = filled
        
        newod = copy(od)
        self.gateway.onOrder(newod)
        
    #----------------------------------------------------------------------
    def openOrder(self, orderId, contract, order, orderState):
        """下达委托推送"""
        orderId = str(orderId)  # orderId是整数
        
        if orderId in self.orderDict:
            od = self.orderDict[orderId]
        else:
            od = VtOrderData()  # od代表orderData
            od.orderID = orderId
            od.vtOrderID = '.'.join([self.gatewayName, orderId])
            od.symbol = contract.localSymbol
            od.exchange = exchangeMapReverse.get(contract.exchange, '')
            od.vtSymbol = '.'.join([od.symbol, od.exchange])  
            od.gatewayName = self.gatewayName
            self.orderDict[orderId] = od
        
        od.direction = directionMapReverse.get(order.action, '')
        od.price = order.lmtPrice
        od.totalVolume = order.totalQuantity
        
        newod = copy(od)
        self.gateway.onOrder(newod)
        
    #----------------------------------------------------------------------
    def openOrderEnd(self):
        """"""
        pass
          
    #----------------------------------------------------------------------
    def winError(self, str_, lastError):
        """"""
        pass
 
    #----------------------------------------------------------------------
    def connectionClosed(self):
        """断线"""
        self.apiStatus = False
        self.gateway.connected = False
    
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = text.API_DISCONNECTED
        self.gateway.onLog(log) 
        
    #----------------------------------------------------------------------
    def updateAccountValue(self, key, val, currency, accountName):
        """更新账户数据"""
        # 仅逐个字段更新数据，这里对于没有currency的推送忽略
        if currency:
            name = '.'.join([accountName, currency])
            
            if name in self.accountDict:
                account = self.accountDict[name]
            else:
                account = VtAccountData()
                account.accountID = name
                account.vtAccountID = name
                account.gatewayName = self.gatewayName
                self.accountDict[name] = account
            
            if key in accountKeyMap:
                k = accountKeyMap[key]
                account.__setattr__(k, float(val))
        
    #----------------------------------------------------------------------
    def updatePortfolio(self, contract, position, marketPrice, marketValue, averageCost, unrealizedPNL, realizedPNL, accountName):
        """持仓更新"""
        pos = VtPositionData()
    
        pos.symbol = contract.localSymbol
        pos.exchange = exchangeMapReverse.get(contract.exchange, contract.exchange)
        pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])
        pos.direction = DIRECTION_NET
        pos.position = position
        pos.price = averageCost
        pos.vtPositionName = pos.vtSymbol
        pos.gatewayName = self.gatewayName
    
        self.gateway.onPosition(pos)
        
    #----------------------------------------------------------------------
    def updateAccountTime(self, timeStamp):
        """更新账户时间"""
        # 推送数据
        for account in self.accountDict.values():
            newaccount = copy(account)
            self.gateway.onAccount(newaccount)
        
    #----------------------------------------------------------------------
    def accountDownloadEnd(self, accountName):
        """"""
        pass
         
    #----------------------------------------------------------------------
    def contractDetails(self, reqId, contractDetails):
        """合约查询回报"""
        symbol = contractDetails.summary.localSymbol
        exchange = exchangeMapReverse.get(contractDetails.summary.exchange, EXCHANGE_UNKNOWN)
        vtSymbol = '.'.join([symbol, exchange])
        ct = self.contractDict.get(vtSymbol, None)
        
        if not ct:
            return
        
        ct.name = contractDetails.longName.decode('UTF-8')
        ct.priceTick = contractDetails.minTick        

        # 推送
        self.gateway.onContract(ct)
        
    #----------------------------------------------------------------------
    def bondContractDetails(self, reqId, contractDetails):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def contractDetailsEnd(self, reqId):
        """"""
        pass

    #----------------------------------------------------------------------
    def execDetails(self, reqId, contract, execution):
        """成交推送"""
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName     
        trade.tradeID = execution.execId
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])
    
        trade.symbol = contract.localSymbol
        trade.exchange = exchangeMapReverse.get(contract.exchange, '')
        trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])  
    
        trade.orderID = str(execution.orderId)
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
        trade.direction = directionMapReverse.get(execution.side, '')
        trade.price = execution.price
        trade.volume = execution.shares
        trade.tradeTime = execution.time  
    
        self.gateway.onTrade(trade)
        
    #----------------------------------------------------------------------
    def execDetailsEnd(self, reqId):
        """"""
        pass

    #----------------------------------------------------------------------
    def updateMktDepth(self, id_, position, operation, side, price, size):
        """"""
        pass

    #----------------------------------------------------------------------
    def updateMktDepthL2(self, id_, position, marketMaker, operation, side, price, size):
        """"""
        pass

    #----------------------------------------------------------------------
    def updateNewsBulletin(self, msgId, msgType, newsMessage, originExch):
        """"""
        pass

    #----------------------------------------------------------------------
    def managedAccounts(self, accountsList):
        """推送管理账户的信息"""
        l = accountsList.split(',')
        
        # 请求账户数据主推更新
        for account in l:
            self.reqAccountUpdates(True, account)    
        
    #----------------------------------------------------------------------
    def receiveFA(self, pFaDataType, cxml):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def historicalData(self, reqId, date, open_, high, low, close, volume, barCount, WAP, hasGaps):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def scannerParameters(self, xml):
        """"""
        pass
          
    #----------------------------------------------------------------------
    def scannerData(self, reqId, rank, contractDetails, distance, benchmark, projection, legsStr):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def scannerDataEnd(self, reqId):
        """"""
        pass

    #----------------------------------------------------------------------
    def realtimeBar(self, reqId, time, open_, high, low, close, volume, wap, count):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def fundamentalData(self, reqId, data):
        """"""
        pass
         
    #----------------------------------------------------------------------
    def deltaNeutralValidation(self, reqId, underComp):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def tickSnapshotEnd(self, reqId):
        """"""
        pass

    #----------------------------------------------------------------------
    def marketDataType(self, reqId, marketDataType):
        """"""
        pass
         
    #----------------------------------------------------------------------
    def commissionReport(self, commissionReport):
        """"""
        pass
          
    #----------------------------------------------------------------------
    def position(self, account, contract, position, avgCost):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def positionEnd(self):
        """"""
        pass 
        
    #----------------------------------------------------------------------
    def verifyMessageAPI(self, apiData):
        """"""
        pass
        
    #----------------------------------------------------------------------
    def verifyCompleted(self, isSuccessful, errorText):
        """"""
        pass

    #----------------------------------------------------------------------
    def displayGroupList(self, reqId, groups):
        """"""
        pass
         
    #----------------------------------------------------------------------
    def displayGroupUpdated(self, reqId, contractInfo):
        """"""
        pass   
        
    #----------------------------------------------------------------------
    def verifyAndAuthMessageAPI(self, apiData, xyzChallange):
        """"""
        pass

    #----------------------------------------------------------------------
    def verifyAndAuthCompleted(self, isSuccessful, errorText):
        """"""
        pass
         
    #----------------------------------------------------------------------
    def positionMulti(self, reqId, account, modelCode, contract, pos, avgCost):
        """"""
        pass
         
    #----------------------------------------------------------------------
    def positionMultiEnd(self, reqId):	
        """"""
        pass
          
    #----------------------------------------------------------------------
    def accountUpdateMulti(self, reqId, account, modelCode, key, value, currency):
        """"""
        pass

    #----------------------------------------------------------------------
    def accountUpdateMultiEnd(self, reqId):	
        """"""
        pass

    #----------------------------------------------------------------------
    def securityDefinitionOptionalParameter(self, reqId, exchange, underlyingConId, tradingClass, multiplier, expirations, strikes):
        """"""
        pass

    #----------------------------------------------------------------------
    def securityDefinitionOptionalParameterEnd(self, reqId):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def softDollarTiers(self, reqId, tiers):
        """"""
        pass
        