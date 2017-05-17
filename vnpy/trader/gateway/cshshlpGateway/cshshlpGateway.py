# encoding: UTF-8

import sys
import os
import json
from time import sleep

from vnpy.api.cshshlp import CsHsHlp
from vnpy.api.ctp import MdApi
from vnpy.trader.vtGateway import *


# 接口常量
FUNCTION_LOGIN = 331100
FUNCTION_SENDORDER = 338011
FUNCTION_CANCELORDER = 338012
FUNCTION_QRYCONTRACT = 338000
FUNCTION_QRYORDER = 338020
FUNCTION_QRYTRADE = 338021
FUNCTION_QRYPOSITION = 338023
FUNCTION_QRYACCOUNT = 338022
FUNCTION_SUBSCRIBE= 620001

ISSUE_ORDER = 33012
ISSUE_TRADE = 33011


# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_SSE] = '1'
exchangeMap[EXCHANGE_SZSE] = '2'
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}
exchangeMapReverse['SSE'] = EXCHANGE_SSE


# 期权类型映射
optionTypeMap = {}
optionTypeMap[OPTION_CALL] = 'C'
optionTypeMap[OPTION_PUT] = 'P'
optionTypeMapReverse = {v:k for k,v in optionTypeMap.items()}

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = '1'
directionMap[DIRECTION_SHORT] = '2'
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {}
offsetMap[OFFSET_OPEN] = 'O'
offsetMap[OFFSET_CLOSE] = 'C'
offsetMapReverse = {v:k for k,v in offsetMap.items()}

# 持仓类型映射
posDirectionMap = {}
posDirectionMap[DIRECTION_LONG] = '0'
posDirectionMap[DIRECTION_SHORT] = '1'
posDirectionMap[DIRECTION_COVEREDSHORT] = '2'
posDirectionMapReverse = {v:k for k,v in posDirectionMap.items()}

# 委托状态映射
statusMapReverse = {}
statusMapReverse['2'] = STATUS_NOTTRADED
statusMapReverse['5'] = STATUS_CANCELLED
statusMapReverse['6'] = STATUS_CANCELLED
statusMapReverse['7'] = STATUS_PARTTRADED
statusMapReverse['8'] = STATUS_ALLTRADED
statusMapReverse['9'] = STATUS_REJECTED

# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = '0'
priceTypeMap[PRICETYPE_MARKETPRICE] = 'OPB'
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 


########################################################################
class CshshlpGateway(VtGateway):
    """"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='CS'):
        """Constructor"""
        super(CshshlpGateway, self).__init__(eventEngine, gatewayName)
        
        self.mdApi = CshshlpMdApi(self)     # 行情API
        self.tdApi = CshshlpTdApi(self)      # 交易API
        
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
            log.logContent = text.LOADING_ERROR
            self.onLog(log)
            return
        
        # 解析json文件
        setting = json.load(f)
        
        try:
            userID = str(setting['userID'])
            ctpPassword = str(setting['ctpPassword'])
            brokerID = str(setting['brokerID'])
            mdAddress = str(setting['mdAddress'])
            
            opEntrustWay = setting['opEntrustWay']
            opStation = setting['opStation']
            fundAccount = setting['fundAccount']
            password = setting['password']
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'配置文件缺少字段'
            self.onLog(log)
            return            
        
        # 创建行情和交易接口对象
        self.mdApi.connect(userID, ctpPassword, brokerID, mdAddress)
        self.tdApi.connect(opEntrustWay, opStation, fundAccount, password)
        
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
    def qryPosition(self):
        """查询持仓"""
        self.tdApi.qryPosition()
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        if self.mdConnected:
            self.mdApi.close()
        
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
class CshshlpTdApi(CsHsHlp):
    """交易API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """"""
        super(CshshlpTdApi, self).__init__()
        
        self.gateway = gateway
        self.gatewayName = gateway.gatewayName
        
        self.callbackDict = {}
        
        self.opBranchNo = ''
        self.opEntrustWay = ''
        self.opStation = ''
        self.branchNo = ''
        self.clientId = ''
        self.fundAccount = ''
        self.password = ''
        self.sysnodeId = ''
        
        #self.batchNo = 0
        self.batchNo = 1000000
        
        self.batchEntrustDict = {}      # key: batchNo, value: entrustNo
        self.entrustBatchDict = {}      # key: entrustNo, value: batchNo
        
        self.orderDict = {}             # key: batchNo, value: order
        self.cancelDict = {}            # key: batchNo, value: cancelReq
        
        self.loginStatus = False
        
        self.initCallback()
        
    #----------------------------------------------------------------------
    def initCallback(self):
        """"""
        self.callbackDict[FUNCTION_LOGIN] = self.onLogin
        self.callbackDict[FUNCTION_SENDORDER] = self.onSendOrder
        self.callbackDict[FUNCTION_CANCELORDER] = self.onCancelOrder
        self.callbackDict[FUNCTION_QRYCONTRACT] = self.onQryContract
        self.callbackDict[FUNCTION_QRYORDER] = self.onQryOrder
        self.callbackDict[FUNCTION_QRYTRADE] = self.onQryTrade
        self.callbackDict[FUNCTION_QRYPOSITION] = self.onQryPosition
        self.callbackDict[FUNCTION_QRYACCOUNT] = self.onQryAccount
        
        self.callbackDict[ISSUE_ORDER] = self.onRtnOrder
        self.callbackDict[ISSUE_TRADE] = self.onRtnTrade
        
    #----------------------------------------------------------------------
    def onMsg(self, type_, data, reqNo, errorNo, errorInfo):
        """收到推送"""
        #print data
        cb = self.callbackDict.get(int(type_), None)
        if not cb:
            self.writeLog(u'无法找到对应类型的回调函数%s' %type_)
            return
        
        cb(data, reqNo, errorNo, errorInfo)
    
    #----------------------------------------------------------------------
    def sendReq(self, type_, d):
        """发送请求"""
        self.beginParam()
        
        for k, v in d.items():
            self.setValue(str(k), str(v))
        
        i = self.bizCallAndCommit(type_)
        
        return i
    
    #----------------------------------------------------------------------
    def generateReq(self):
        """生成标准委托字段的字典"""
        d = {
            "op_branch_no": self.branchNo,
            "op_entrust_way": self.opEntrustWay,
            "op_station": self.opStation,
            "branch_no": self.branchNo,
            "client_id": self.clientId,
            "fund_account": self.fundAccount,
            "password": self.password,
            "asset_prop": "B",
            "sysnode_Id": self.sysnodeId
        }
        
        return d
    
    #----------------------------------------------------------------------
    def writeError(self, errorNo, errorInfo):
        """"""
        error = VtErrorData()
        error.gatewayName = self.gatewayName
        error.errorID = errorNo
        error.errorMsg = errorInfo.decode('GBK')
        self.gateway.onError(error)
    
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)
    
    ###########################################################

    #----------------------------------------------------------------------
    def onLogin(self, data, reqNo, errorNo, errorInfo):
        """"""
        if errorNo:
            self.writeError(errorNo, errorInfo)
            return
        
        for d in data:
            self.branchNo = d['branch_no']
            self.clientId = d['client_id']
            self.fundAccount = d['fund_account']
            self.sysnodeId = d['sysnode_id']
        
        self.loginStatus = True
        self.writeLog(u'交易服务器登录完成')   
        
        self.subscribeOrder()
        self.subscribeTrade()
        self.qryContract()

    #----------------------------------------------------------------------
    def onSendOrder(self, data, reqNo, errorNo, errorInfo):
        """"""
        if errorNo:
            self.writeError(errorNo, errorInfo)
            return
        
        for d in data:
            batchNo = d['batch_no']
            self.batchEntrustDict[batchNo] = d['entrust_no']
            self.entrustBatchDict[d['entrust_no']] = batchNo
            
            # 检查是否需要撤单
            if batchNo in self.cancelDict:
                cancelReq = self.cancelDict[batchNo]
                self.cancelOrder(cancelReq)
                
            # 更新数据
            order = self.orderDict[batchNo]
            t = d['entrust_time'].rjust(6, '0')
            order.orderTime = ':'.join([t[:2], t[2:4], t[4:]])
            self.gateway.onOrder(order)
    
    #----------------------------------------------------------------------
    def onCancelOrder(self, data, reqNo, errorNo, errorInfo):
        """"""
        if errorNo:
            self.writeError(errorNo, errorInfo)
            return
    
    #----------------------------------------------------------------------
    def onQryContract(self, data, reqNo, errorNo, errorInfo):
        """"""
        if errorNo:
            self.writeError(errorNo, errorInfo)
            return

        for d in data:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName
            
            contract.symbol = d['option_code']
            contract.exchange = exchangeMapReverse.get(d['exchange_type'], EXCHANGE_UNKNOWN)
            contract.vtSymbol = '.'.join([contract.symbol, contract.exchange])
            contract.name = d['option_name'].decode('GBK')        
            contract.size = int(float(d['amount_per_hand']))
            contract.priceTick = float(d['opt_price_step'])
            contract.strikePrice = float(d['exercise_price'])
            contract.underlyingSymbol = d['stock_code']
            contract.productClass = PRODUCT_OPTION
            contract.optionType = optionTypeMapReverse[d['option_type']]
            
            self.gateway.onContract(contract)
        
        self.writeLog(u'合约查询完成')
        
        self.qryOrder()
    
    #----------------------------------------------------------------------
    def onQryOrder(self, data, reqNo, errorNo, errorInfo):
        """"""
        if errorNo:
            self.writeError(errorNo, errorInfo)
            return
            
        for d in data:
            order = VtOrderData()
            order.gatewayName = self.gatewayName
            
            order.symbol = d['option_code']
            order.exchange = exchangeMapReverse.get(d['exchange_type'], EXCHANGE_UNKNOWN)
            order.vtSymbol = '.'.join([order.symbol, order.exchange])
            
            batchNo = d['batch_no']
            self.batchNo = max(self.batchNo, int(batchNo))

            order.orderID = batchNo
            order.vtOrderID = '.'.join([order.gatewayName, order.orderID])
            
            self.batchEntrustDict[batchNo] = d['entrust_no']
            self.entrustBatchDict[d['entrust_no']] = batchNo
            
            order.direction = directionMapReverse.get(d['entrust_bs'], DIRECTION_UNKNOWN)
            order.offset = offsetMapReverse.get(d['entrust_oc'], OFFSET_UNKNOWN)
            order.status = statusMapReverse.get(d['entrust_status'], STATUS_UNKNOWN)
            
            order.price = float(d['opt_entrust_price'])
            order.totalVolume = int(float(d['entrust_amount']))
            order.tradedVolume = int(float(d['business_amount']))
            
            t = d['entrust_time'].rjust(6, '0')
            order.orderTime = ':'.join([t[:2], t[2:4], t[4:]])
            
            self.gateway.onOrder(order)
            
            self.orderDict[batchNo] = order
            
        self.writeLog(u'委托查询完成')            
            
        self.qryTrade()
    
    #----------------------------------------------------------------------
    def onQryTrade(self, data, reqNo, errorNo, errorInfo):
        """"""
        if errorNo:
            self.writeError(errorNo, errorInfo)
            return
            
        for d in data:
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName
            
            trade.symbol = d['option_code']
            trade.exchange = exchangeMapReverse.get(d['exchange_type'], EXCHANGE_UNKNOWN)
            trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
            
            batchNo = self.entrustBatchDict[d['entrust_no']]
            trade.orderID = batchNo
            trade.vtOrderID = '.'.join([trade.gatewayName, trade.orderID])
            
            trade.tradeID = d['business_id']
            trade.vtTradeID = '.'.join([trade.gatewayName, trade.tradeID])
            
            trade.direction = directionMapReverse.get(d['entrust_bs'], DIRECTION_UNKNOWN)
            trade.offset = offsetMapReverse.get(d['entrust_oc'], OFFSET_UNKNOWN)
            
            trade.price = float(d['opt_business_price'])
            trade.volume = int(float(d['business_amount']))
            
            t = d['business_time'].rjust(6, '0')
            trade.tradeTime= ':'.join([t[:2], t[2:4], t[4:]])            
            
            self.gateway.onTrade(trade)
            
        self.writeLog(u'成交查询完成')
    
    #----------------------------------------------------------------------
    def onQryPosition(self, data, reqNo, errorNo, errorInfo):
        """"""
        if errorNo:
            self.writeError(errorNo, errorInfo)
            return
        
        for d in data:
            pos = VtPositionData()
            pos.gatewayName = self.gatewayName
            
            pos.symbol = d['option_code']
            pos.exchange = exchangeMapReverse.get(d['exchange_type'], EXCHANGE_UNKNOWN)
            pos.vtSymbol = '.'.join([pos.symbol, pos.exchange])
            pos.direction = posDirectionMapReverse.get(d['opthold_type'], DIRECTION_UNKNOWN)
            pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction]) 
    
            pos.position = int(float(d['hold_amount']))
            pos.positionProfit = float(d['income_balance'])
            pos.price = float(d['opt_cost_price'])
            pos.frozen = int((float(d['hold_amount']) - float(d['enable_amount'])))

            self.gateway.onPosition(pos)
    
    #----------------------------------------------------------------------
    def onQryAccount(self, data, reqNo, errorNo, errorInfo):
        """"""
        if errorNo:
            self.writeError(errorNo, errorInfo)
            return
            
        for d in data:
            account = VtAccountData()
            account.gatewayName = self.gatewayName
            
            account.accountID = self.fundAccount
            account.vtAccountID = '.'.join([self.gatewayName, account.accountID])
            account.available = float(d['enable_balance'])
            account.margin = float(d['real_used_bail'])
            account.positionProfit = float(d['income_balance'])
            account.balance = float(d['total_asset'])
        
            self.gateway.onAccount(account)            
    
    #----------------------------------------------------------------------
    def onRtnTrade(self, data, reqNo, errorNo, errorInfo):
        """"""
        for d in data:
            # 撤单回报business_amount小于0，可以通过其进行过滤
            tradeVolume = int(float(d['business_amount']))
            entrustNo = d['entrust_no']
            batchNo = self.entrustBatchDict.get(entrustNo, '')            
            
            # 成交推送，只有当成交数量大于0时
            if tradeVolume > 0:
                trade = VtTradeData()
                trade.gatewayName = self.gatewayName
                
                trade.symbol = d['option_code']
                trade.exchange = exchangeMapReverse.get(d['exchange_type'], EXCHANGE_UNKNOWN)
                trade.vtSymbol = '.'.join([trade.symbol, trade.exchange])
                
                trade.orderID = batchNo
                trade.vtOrderID = '.'.join([trade.gatewayName, trade.orderID])
                
                trade.tradeID = d['business_id']
                trade.vtTradeID = '.'.join([trade.gatewayName, trade.tradeID])
                
                trade.direction = directionMapReverse.get(d['entrust_bs'], DIRECTION_UNKNOWN)
                trade.offset = offsetMapReverse.get(d['entrust_oc'], OFFSET_UNKNOWN)
                
                trade.price = float(d['opt_business_price'])
                trade.volume = int(float(d['business_amount']))
                
                t = d['business_time'].rjust(6, '0')
                trade.tradeTime= ':'.join([t[:2], t[2:4], t[4:]])
                
                self.gateway.onTrade(trade)     
            
            # 委托推送
            order = self.orderDict[batchNo]
            
            if tradeVolume > 0:
                order.tradedVolume += tradeVolume
                
            order.status = statusMapReverse.get(d['entrust_status'], STATUS_UNKNOWN)  
            
            self.gateway.onOrder(order)
    
    #----------------------------------------------------------------------
    def onRtnOrder(self, data, reqNo, errorNo, errorInfo):
        """"""
        for d in data:
            entrustNo = d['entrust_no']
            if entrustNo not in self.entrustBatchDict:
                return
                
            batchNo = self.entrustBatchDict[entrustNo]
            order = self.orderDict[batchNo]

            order.status = statusMapReverse.get(d['entrust_status'], STATUS_UNKNOWN)            
            order.tradedVolume = int(float(d['business_amount']))
            
            self.gateway.onOrder(order)
        
    ###########################################################
    
    #----------------------------------------------------------------------
    def connect(self, opEntrustWay, opStation, fundAccount, password):
        """"""
        self.opEntrustWay = opEntrustWay
        self.opStation = opStation
        self.fundAccount = fundAccount
        self.password = password        
        
        # 读取配置文件 
        i = self.loadConfig("Hsconfig.ini")
        if i:
            self.writeLog(u'交易加载配置失败，原因：%s' %self.getErrorMsg().decode('GBK'))
            return
        self.writeLog(u'交易加载配置成功')
        
        # 初始化
        i = self.init()
        if i:
            self.writeLog(u'交易初始化失败，原因：%s' %self.getErrorMsg().decode('GBK'))
            return
        self.writeLog(u'交易初始化成功')
        
        # 连接服务器
        i = self.connectServer()
        if i:
            self.writeLog(u'交易服务器连接失败，原因：%s' %self.getErrorMsg().decode('GBK'))
            return
        self.writeLog(u'交易服务器连接成功')
        
        # 登录
        req = {}
        req['identity_type'] = '2'
        req['password_type'] = '2'
        req['input_content'] = '1'
        req['op_entrust_way'] = self.opEntrustWay
        req['password'] = self.password
        req['account_content'] = self.fundAccount
        self.sendReq(FUNCTION_LOGIN, req)
    
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """"""
        req = self.generateReq()
        
        req['exchange_type'] = exchangeMap.get(orderReq.exchange, '')
        req['option_code'] = orderReq.symbol
        req['entrust_amount'] = str(orderReq.volume)
        req['opt_entrust_price'] = str(orderReq.price)
        req['entrust_bs'] = directionMap.get(orderReq.direction, '')
        req['entrust_oc'] = offsetMap.get(orderReq.offset, '')
        req['covered_flag'] = ''
        req['entrust_prop'] = priceTypeMap.get(orderReq.priceType, '')
        
        self.batchNo += 1
        batchNo = str(self.batchNo)        
        req['batch_no'] = batchNo
        
        reqNo = self.sendReq(FUNCTION_SENDORDER, req)
        
        vtOrderID = '.'.join([self.gatewayName, batchNo])
        
        # 缓存委托信息
        order = VtOrderData()
        order.gatewayName = self.gatewayName
        
        order.symbol = orderReq.symbol
        order.exchange = orderReq.exchange
        order.vtSymbol = '.'.join([order.symbol, order.exchange])
        order.orderID = batchNo
        order.vtOrderID = vtOrderID        
        order.direction = orderReq.direction
        order.offset = orderReq.offset        
        order.price = orderReq.price
        order.totalVolume = orderReq.volume
        order.status = STATUS_UNKNOWN
        
        self.orderDict[batchNo] = order
        
        return vtOrderID
    
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelReq):
        """"""        
        # 如果尚未收到委托的柜台编号，则缓存该撤单请求
        batchNo = cancelReq.orderID
        if batchNo not in self.batchEntrustDict:
            self.cancelDict[batchNo] = cancelReq
            return
        
        # 获取对应的柜台委托号，并撤单
        entrustNo = self.batchEntrustDict[batchNo]
        
        req = self.generateReq()
        req['entrust_no'] = entrustNo
        
        self.sendReq(FUNCTION_CANCELORDER, req)
        
        # 移除撤单请求字典中的缓存
        if batchNo in self.cancelDict:
            del self.cancelDict[batchNo]
    
    #----------------------------------------------------------------------
    def qryContract(self):
        """"""
        req = self.generateReq()
        req['request_num'] = '10000'
        self.sendReq(FUNCTION_QRYCONTRACT, req)
    
    #----------------------------------------------------------------------
    def qryPosition(self):
        """"""
        if not self.loginStatus:
            return
        
        req = self.generateReq()
        req['request_num'] = '10000'
        self.sendReq(FUNCTION_QRYPOSITION, req)
    
    #----------------------------------------------------------------------
    def qryAccount(self):
        """"""
        if not self.loginStatus:
            return
        
        req = self.generateReq()
        self.sendReq(FUNCTION_QRYACCOUNT, req)
    
    #----------------------------------------------------------------------
    def qryTrade(self):
        """"""
        req = self.generateReq()
        self.sendReq(FUNCTION_QRYTRADE, req)
    
    #----------------------------------------------------------------------
    def qryOrder(self):
        """"""
        req = self.generateReq()
        self.sendReq(FUNCTION_QRYORDER, req)
        
    #----------------------------------------------------------------------
    def subscribeOrder(self):
        """"""
        req = {}
        req['acc_info'] = '~'.join([self.branchNo, self.fundAccount])
        req['issue_Type'] = ISSUE_ORDER
        
        self.beginParam()
        for k, v in req.items():
            self.setValue(str(k), str(v))
        
        l = self.subscribeData(FUNCTION_SUBSCRIBE)
        for d in l:
            self.writeLog(u'委托推送：%s' %d['result_info'].decode('GBK'))
        
    #----------------------------------------------------------------------
    def subscribeTrade(self):
        """"""
        req = {}
        req['acc_info'] = '~'.join([self.branchNo, self.fundAccount])
        req['issue_Type'] = ISSUE_TRADE
        
        self.beginParam()
        
        for k, v in req.items():
            self.setValue(str(k), str(v))
        
        l = self.subscribeData(FUNCTION_SUBSCRIBE)
        for d in l:
            self.writeLog(u'成交推送：%s' %d['result_info'].decode('GBK'))
    

########################################################################
class CshshlpMdApi(MdApi):
    """行情API实现，使用的CTP接口，但是字段上和ctpGateway有区别"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(CshshlpMdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.subscribedSymbols = set()      # 已订阅合约代码        
        
        self.userID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.brokerID = EMPTY_STRING        # 经纪商代码
        self.address = EMPTY_STRING         # 服务器地址
        
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        self.connectionStatus = True
        
        self.writeLog(u'行情服务器连接成功')
        
        self.login()
    
    #----------------------------------------------------------------------  
    def onFrontDisconnected(self, n):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.mdConnected = False
        
        self.writeLog(u'行情服务器连接断开')
        
    #---------------------------------------------------------------------- 
    def onHeartBeatWarning(self, n):
        """心跳报警"""
        # 因为API的心跳报警比较常被触发，且与API工作关系不大，因此选择忽略
        pass
    
    #----------------------------------------------------------------------   
    def onRspError(self, error, n, last):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)
        
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = True
            self.gateway.mdConnected = True
            
            self.writeLog(u'行情服务器登录成功')
            
            # 重新订阅之前订阅的合约
            for subscribeReq in self.subscribedSymbols:
                self.subscribe(subscribeReq)
                
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)

    #---------------------------------------------------------------------- 
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        # 如果登出成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = False
            self.gateway.mdConnected = False
            
            self.writeLog(u'行情服务器登出成功')
                
        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)
        
    #----------------------------------------------------------------------  
    def onRspSubMarketData(self, data, error, n, last):
        """订阅合约回报"""
        # 通常不在乎订阅错误，选择忽略
        pass
        
    #----------------------------------------------------------------------  
    def onRspUnSubMarketData(self, data, error, n, last):
        """退订合约回报"""
        # 同上
        pass  
        
    #----------------------------------------------------------------------  
    def onRtnDepthMarketData(self, data):
        """行情推送"""
        # 忽略成交量为0的无效tick数据
        if not data['Volume']:
            return
        
        # 创建对象
        tick = VtTickData()
        tick.gatewayName = self.gatewayName
        
        tick.symbol = data['InstrumentID']
        tick.exchange = exchangeMapReverse.get(data['ExchangeID'], EXCHANGE_UNKNOWN)
        tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
        
        tick.lastPrice = data['LastPrice']
        tick.volume = data['Volume']
        tick.openInterest = data['OpenInterest']
        tick.time = '.'.join([data['UpdateTime'], str(data['UpdateMillisec']/100)])
        tick.date = data['TradingDay']
        
        tick.openPrice = data['OpenPrice']
        tick.highPrice = data['HighestPrice']
        tick.lowPrice = data['LowestPrice']
        tick.preClosePrice = data['PreClosePrice']
        
        tick.upperLimit = data['UpperLimitPrice']
        tick.lowerLimit = data['LowerLimitPrice']
        
        # 期权有五档行情
        tick.bidPrice1 = data['BidPrice1']
        tick.bidPrice2 = data['BidPrice2']
        tick.bidPrice3 = data['BidPrice3']
        tick.bidPrice4 = data['BidPrice4']
        tick.bidPrice5 = data['BidPrice5']
        
        tick.askPrice1 = data['AskPrice1']
        tick.askPrice2 = data['AskPrice2']
        tick.askPrice3 = data['AskPrice3']
        tick.askPrice4 = data['AskPrice4']
        tick.askPrice5 = data['AskPrice5']        
        
        tick.bidVolume1 = data['BidVolume1']
        tick.bidVolume2 = data['BidVolume2']
        tick.bidVolume3 = data['BidVolume3']
        tick.bidVolume4 = data['BidVolume4']
        tick.bidVolume5 = data['BidVolume5']
        
        tick.askVolume1 = data['AskVolume1']
        tick.askVolume2 = data['AskVolume2']
        tick.askVolume3 = data['AskVolume3']
        tick.askVolume4 = data['AskVolume4']
        tick.askVolume5 = data['AskVolume5'] 
        
        self.gateway.onTick(tick)
        
    #---------------------------------------------------------------------- 
    def onRspSubForQuoteRsp(self, data, error, n, last):
        """订阅期权询价"""
        pass
        
    #----------------------------------------------------------------------
    def onRspUnSubForQuoteRsp(self, data, error, n, last):
        """退订期权询价"""
        pass 
        
    #---------------------------------------------------------------------- 
    def onRtnForQuoteRsp(self, data):
        """期权询价推送"""
        pass        
        
    #----------------------------------------------------------------------
    def connect(self, userID, password, brokerID, address):
        """初始化连接"""
        self.userID = userID                # 账号
        self.password = password            # 密码
        self.brokerID = brokerID            # 经纪商代码
        self.address = address              # 服务器地址
        
        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            # 创建C++环境中的API对象，这里传入的参数是需要用来保存.con文件的文件夹路径
            path = os.getcwd() + '/temp/' + self.gatewayName + '/'
            if not os.path.exists(path):
                os.makedirs(path)
            self.createFtdcMdApi(path)
            
            # 注册服务器地址
            self.registerFront(self.address)
            
            # 初始化连接，成功会调用onFrontConnected
            self.init()
            
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
            self.subscribeMarketData(str(subscribeReq.symbol))
        self.subscribedSymbols.add(subscribeReq)   
        
    #----------------------------------------------------------------------
    def login(self):
        """登录"""
        # 如果填入了用户名密码等，则登录
        if self.userID and self.password and self.brokerID:
            req = {}
            req['UserID'] = self.userID
            req['Password'] = self.password
            req['BrokerID'] = self.brokerID
            self.reqID += 1
            self.reqUserLogin(req, self.reqID)    
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)        




