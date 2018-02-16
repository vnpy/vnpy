# encoding: UTF-8

from __future__ import division

import os
import shelve
import logging
from collections import OrderedDict
from datetime import datetime
from copy import copy

from pymongo import MongoClient, ASCENDING
from pymongo.errors import ConnectionFailure

from vnpy.event import Event
from vnpy.trader.vtGlobal import globalSetting
from vnpy.trader.vtEvent import *
from vnpy.trader.vtGateway import *
from vnpy.trader.language import text
from vnpy.trader.vtFunction import getTempPath



########################################################################
class MainEngine(object):
    """主引擎"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """Constructor"""
        # 记录今日日期
        self.todayDate = datetime.now().strftime('%Y%m%d')
        
        # 绑定事件引擎
        self.eventEngine = eventEngine
        self.eventEngine.start()
        
        # 创建数据引擎
        self.dataEngine = DataEngine(self.eventEngine)
        
        # MongoDB数据库相关
        self.dbClient = None    # MongoDB客户端对象
        
        # 接口实例
        self.gatewayDict = OrderedDict()
        self.gatewayDetailList = []
        
        # 应用模块实例
        self.appDict = OrderedDict()
        self.appDetailList = []
        
        # 风控引擎实例（特殊独立对象）
        self.rmEngine = None
        
        # 日志引擎实例
        self.logEngine = None
        self.initLogEngine()

    #----------------------------------------------------------------------
    def addGateway(self, gatewayModule):
        """添加底层接口"""
        gatewayName = gatewayModule.gatewayName
        
        # 创建接口实例
        self.gatewayDict[gatewayName] = gatewayModule.gatewayClass(self.eventEngine, 
                                                                   gatewayName)
        
        # 设置接口轮询
        if gatewayModule.gatewayQryEnabled:
            self.gatewayDict[gatewayName].setQryEnabled(gatewayModule.gatewayQryEnabled)
                
        # 保存接口详细信息
        d = {
            'gatewayName': gatewayModule.gatewayName,
            'gatewayDisplayName': gatewayModule.gatewayDisplayName,
            'gatewayType': gatewayModule.gatewayType
        }
        self.gatewayDetailList.append(d)
        
    #----------------------------------------------------------------------
    def addApp(self, appModule):
        """添加上层应用"""
        appName = appModule.appName
        
        # 创建应用实例
        self.appDict[appName] = appModule.appEngine(self, self.eventEngine)
        
        # 将应用引擎实例添加到主引擎的属性中
        self.__dict__[appName] = self.appDict[appName]
        
        # 保存应用信息
        d = {
            'appName': appModule.appName,
            'appDisplayName': appModule.appDisplayName,
            'appWidget': appModule.appWidget,
            'appIco': appModule.appIco
        }
        self.appDetailList.append(d)
        
    #----------------------------------------------------------------------
    def getGateway(self, gatewayName):
        """获取接口"""
        if gatewayName in self.gatewayDict:
            return self.gatewayDict[gatewayName]
        else:
            self.writeLog(text.GATEWAY_NOT_EXIST.format(gateway=gatewayName))
            return None
        
    #----------------------------------------------------------------------
    def connect(self, gatewayName):
        """连接特定名称的接口"""
        gateway = self.getGateway(gatewayName)
        
        if gateway:
            gateway.connect()
            
            # 接口连接后自动执行数据库连接的任务
            self.dbConnect()        
   
    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq, gatewayName):
        """订阅特定接口的行情"""
        gateway = self.getGateway(gatewayName)
        
        if gateway:
            gateway.subscribe(subscribeReq)
  
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq, gatewayName):
        """对特定接口发单"""
        # 如果创建了风控引擎，且风控检查失败则不发单
        if self.rmEngine and not self.rmEngine.checkRisk(orderReq, gatewayName):
            return ''

        gateway = self.getGateway(gatewayName)
        
        if gateway:
            vtOrderID = gateway.sendOrder(orderReq)
            self.dataEngine.updateOrderReq(orderReq, vtOrderID)     # 更新发出的委托请求到数据引擎中
            return vtOrderID
        else:
            return ''
        
    #----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq, gatewayName):
        """对特定接口撤单"""
        gateway = self.getGateway(gatewayName)
        
        if gateway:
            gateway.cancelOrder(cancelOrderReq)   
  
    #----------------------------------------------------------------------
    def qryAccount(self, gatewayName):
        """查询特定接口的账户"""
        gateway = self.getGateway(gatewayName)
        
        if gateway:
            gateway.qryAccount()      
        
    #----------------------------------------------------------------------
    def qryPosition(self, gatewayName):
        """查询特定接口的持仓"""
        gateway = self.getGateway(gatewayName)
        
        if gateway:
            gateway.qryPosition()
            
    #----------------------------------------------------------------------
    def exit(self):
        """退出程序前调用，保证正常退出"""        
        # 安全关闭所有接口
        for gateway in self.gatewayDict.values():        
            gateway.close()
        
        # 停止事件引擎
        self.eventEngine.stop()
        
        # 停止上层应用引擎
        for appEngine in self.appDict.values():
            appEngine.stop()
        
        # 保存数据引擎里的合约数据到硬盘
        self.dataEngine.saveContracts()
    
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """快速发出日志事件"""
        log = VtLogData()
        log.logContent = content
        log.gatewayName = 'MAIN_ENGINE'
        event = Event(type_=EVENT_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)        
    
    #----------------------------------------------------------------------
    def dbConnect(self):
        """连接MongoDB数据库"""
        if not self.dbClient:
            # 读取MongoDB的设置
            try:
                # 设置MongoDB操作的超时时间为0.5秒
                self.dbClient = MongoClient(globalSetting['mongoHost'], globalSetting['mongoPort'], connectTimeoutMS=500)
                
                # 调用server_info查询服务器状态，防止服务器异常并未连接成功
                self.dbClient.server_info()

                self.writeLog(text.DATABASE_CONNECTING_COMPLETED)
                
                # 如果启动日志记录，则注册日志事件监听函数
                if globalSetting['mongoLogging']:
                    self.eventEngine.register(EVENT_LOG, self.dbLogging)
                    
            except ConnectionFailure:
                self.writeLog(text.DATABASE_CONNECTING_FAILED)
    
    #----------------------------------------------------------------------
    def dbInsert(self, dbName, collectionName, d):
        """向MongoDB中插入数据，d是具体数据"""
        if self.dbClient:
            db = self.dbClient[dbName]
            collection = db[collectionName]
            collection.insert_one(d)
        else:
            self.writeLog(text.DATA_INSERT_FAILED)
    
    #----------------------------------------------------------------------
    def dbQuery(self, dbName, collectionName, d, sortKey='', sortDirection=ASCENDING):
        """从MongoDB中读取数据，d是查询要求，返回的是数据库查询的指针"""
        if self.dbClient:
            db = self.dbClient[dbName]
            collection = db[collectionName]
            
            if sortKey:
                cursor = collection.find(d).sort(sortKey, sortDirection)    # 对查询出来的数据进行排序
            else:
                cursor = collection.find(d)

            if cursor:
                return list(cursor)
            else:
                return []
        else:
            self.writeLog(text.DATA_QUERY_FAILED)   
            return []
        
    #----------------------------------------------------------------------
    def dbUpdate(self, dbName, collectionName, d, flt, upsert=False):
        """向MongoDB中更新数据，d是具体数据，flt是过滤条件，upsert代表若无是否要插入"""
        if self.dbClient:
            db = self.dbClient[dbName]
            collection = db[collectionName]
            collection.replace_one(flt, d, upsert)
        else:
            self.writeLog(text.DATA_UPDATE_FAILED)        
            
    #----------------------------------------------------------------------
    def dbLogging(self, event):
        """向MongoDB中插入日志"""
        log = event.dict_['data']
        d = {
            'content': log.logContent,
            'time': log.logTime,
            'gateway': log.gatewayName
        }
        self.dbInsert(LOG_DB_NAME, self.todayDate, d)
    
    #----------------------------------------------------------------------
    def getContract(self, vtSymbol):
        """查询合约"""
        return self.dataEngine.getContract(vtSymbol)
    
    #----------------------------------------------------------------------
    def getAllContracts(self):
        """查询所有合约（返回列表）"""
        return self.dataEngine.getAllContracts()
    
    #----------------------------------------------------------------------
    def getOrder(self, vtOrderID):
        """查询委托"""
        return self.dataEngine.getOrder(vtOrderID)
    
    #----------------------------------------------------------------------
    def getPositionDetail(self, vtSymbol):
        """查询持仓细节"""
        return self.dataEngine.getPositionDetail(vtSymbol)
    
    #----------------------------------------------------------------------
    def getAllWorkingOrders(self):
        """查询所有的活跃的委托（返回列表）"""
        return self.dataEngine.getAllWorkingOrders()
    
    #----------------------------------------------------------------------
    def getAllOrders(self):
        """查询所有委托"""
        return self.dataEngine.getAllOrders()
    
    #----------------------------------------------------------------------
    def getAllTrades(self):
        """查询所有成交"""
        return self.dataEngine.getAllTrades()    
    
    #----------------------------------------------------------------------
    def getAllAccounts(self):
        """查询所有账户"""
        return self.dataEngine.getAllAccounts()
    
    #----------------------------------------------------------------------
    def getAllPositions(self):
        """查询所有持仓"""
        return self.dataEngine.getAllPositions()
    
    #----------------------------------------------------------------------
    def getAllPositionDetails(self):
        """查询本地持仓缓存细节"""
        return self.dataEngine.getAllPositionDetails()
    
    #----------------------------------------------------------------------
    def getAllGatewayDetails(self):
        """查询引擎中所有底层接口的信息"""
        return self.gatewayDetailList
    
    #----------------------------------------------------------------------
    def getAllAppDetails(self):
        """查询引擎中所有上层应用的信息"""
        return self.appDetailList
    
    #----------------------------------------------------------------------
    def getApp(self, appName):
        """获取APP引擎对象"""
        return self.appDict[appName]
    
    #----------------------------------------------------------------------
    def initLogEngine(self):
        """初始化日志引擎"""
        if not globalSetting["logActive"]:
            return
        
        # 创建引擎
        self.logEngine = LogEngine()
        
        # 设置日志级别
        levelDict = {
            "debug": LogEngine.LEVEL_DEBUG,
            "info": LogEngine.LEVEL_INFO,
            "warn": LogEngine.LEVEL_WARN,
            "error": LogEngine.LEVEL_ERROR,
            "critical": LogEngine.LEVEL_CRITICAL,
        }
        level = levelDict.get(globalSetting["logLevel"], LogEngine.LEVEL_CRITICAL)
        self.logEngine.setLogLevel(level)
        
        # 设置输出
        if globalSetting['logConsole']:
            self.logEngine.addConsoleHandler()
            
        if globalSetting['logFile']:
            self.logEngine.addFileHandler()
            
        # 注册事件监听
        self.registerLogEvent(EVENT_LOG)
    
    #----------------------------------------------------------------------
    def registerLogEvent(self, eventType):
        """注册日志事件监听"""
        if self.logEngine:
            self.eventEngine.register(eventType, self.logEngine.processLogEvent)
    
    #----------------------------------------------------------------------
    def convertOrderReq(self, req):
        """转换委托请求"""
        return self.dataEngine.convertOrderReq(req)

    #----------------------------------------------------------------------
    def getLog(self):
        """查询日志"""
        return self.dataEngine.getLog()
    
    #----------------------------------------------------------------------
    def getError(self):
        """查询错误"""
        return self.dataEngine.getError()
    

########################################################################
class DataEngine(object):
    """数据引擎"""
    contractFileName = 'ContractData.vt'
    contractFilePath = getTempPath(contractFileName)
    
    FINISHED_STATUS = [STATUS_ALLTRADED, STATUS_REJECTED, STATUS_CANCELLED]

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """Constructor"""
        self.eventEngine = eventEngine
        
        # 保存数据的字典和列表
        self.contractDict = {}
        self.orderDict = {}
        self.workingOrderDict = {}  # 可撤销委托
        self.tradeDict = {}
        self.accountDict = {}
        self.positionDict= {}
        self.logList = []
        self.errorList = []
        
        # 持仓细节相关
        self.detailDict = {}                                # vtSymbol:PositionDetail
        self.tdPenaltyList = globalSetting['tdPenalty']     # 平今手续费惩罚的产品代码列表
        
        # 读取保存在硬盘的合约数据
        self.loadContracts()
        
        # 注册事件监听
        self.registerEvent()
    
    #----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_CONTRACT, self.processContractEvent)
        self.eventEngine.register(EVENT_ORDER, self.processOrderEvent)
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)
        self.eventEngine.register(EVENT_POSITION, self.processPositionEvent)
        self.eventEngine.register(EVENT_ACCOUNT, self.processAccountEvent)
        self.eventEngine.register(EVENT_LOG, self.processLogEvent)
        self.eventEngine.register(EVENT_ERROR, self.processErrorEvent)
    
    #----------------------------------------------------------------------
    def processContractEvent(self, event):
        """处理合约事件"""
        contract = event.dict_['data']
        self.contractDict[contract.vtSymbol] = contract
        self.contractDict[contract.symbol] = contract       # 使用常规代码（不包括交易所）可能导致重复
    
    #----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """处理委托事件"""
        order = event.dict_['data']        
        self.orderDict[order.vtOrderID] = order
        
        # 如果订单的状态是全部成交或者撤销，则需要从workingOrderDict中移除
        if order.status in self.FINISHED_STATUS:
            if order.vtOrderID in self.workingOrderDict:
                del self.workingOrderDict[order.vtOrderID]
        # 否则则更新字典中的数据        
        else:
            self.workingOrderDict[order.vtOrderID] = order
            
        # 更新到持仓细节中
        detail = self.getPositionDetail(order.vtSymbol)
        detail.updateOrder(order)            
            
    #----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """处理成交事件"""
        trade = event.dict_['data']
        
        self.tradeDict[trade.vtTradeID] = trade
    
        # 更新到持仓细节中
        detail = self.getPositionDetail(trade.vtSymbol)
        detail.updateTrade(trade)        

    #----------------------------------------------------------------------
    def processPositionEvent(self, event):
        """处理持仓事件"""
        pos = event.dict_['data']
        
        self.positionDict[pos.vtPositionName] = pos
    
        # 更新到持仓细节中
        detail = self.getPositionDetail(pos.vtSymbol)
        detail.updatePosition(pos)                
        
    #----------------------------------------------------------------------
    def processAccountEvent(self, event):
        """处理账户事件"""
        account = event.dict_['data']
        self.accountDict[account.vtAccountID] = account
    
    #----------------------------------------------------------------------
    def processLogEvent(self, event):
        """处理日志事件"""
        log = event.dict_['data']
        self.logList.append(log)
    
    #----------------------------------------------------------------------
    def processErrorEvent(self, event):
        """处理错误事件"""
        error = event.dict_['data']
        self.errorList.append(error)
    
    #----------------------------------------------------------------------
    def getContract(self, vtSymbol):
        """查询合约对象"""
        try:
            return self.contractDict[vtSymbol]
        except KeyError:
            return None
        
    #----------------------------------------------------------------------
    def getAllContracts(self):
        """查询所有合约对象（返回列表）"""
        return self.contractDict.values()
    
    #----------------------------------------------------------------------
    def saveContracts(self):
        """保存所有合约对象到硬盘"""
        f = shelve.open(self.contractFilePath)
        f['data'] = self.contractDict
        f.close()
    
    #----------------------------------------------------------------------
    def loadContracts(self):
        """从硬盘读取合约对象"""
        f = shelve.open(self.contractFilePath)
        if 'data' in f:
            d = f['data']
            for key, value in d.items():
                self.contractDict[key] = value
        f.close()
        
    #----------------------------------------------------------------------
    def getOrder(self, vtOrderID):
        """查询委托"""
        try:
            return self.orderDict[vtOrderID]
        except KeyError:
            return None
    
    #----------------------------------------------------------------------
    def getAllWorkingOrders(self):
        """查询所有活动委托（返回列表）"""
        return self.workingOrderDict.values()
    
    #----------------------------------------------------------------------
    def getAllOrders(self):
        """获取所有委托"""
        return self.orderDict.values()
    
    #----------------------------------------------------------------------
    def getAllTrades(self):
        """获取所有成交"""
        return self.tradeDict.values()
    
    #----------------------------------------------------------------------
    def getAllPositions(self):
        """获取所有持仓"""
        return self.positionDict.values()
    
    #----------------------------------------------------------------------
    def getAllAccounts(self):
        """获取所有资金"""
        return self.accountDict.values()
    
    #----------------------------------------------------------------------
    def getPositionDetail(self, vtSymbol):
        """查询持仓细节"""
        if vtSymbol in self.detailDict:
            detail = self.detailDict[vtSymbol]
        else:
            contract = self.getContract(vtSymbol)
            detail = PositionDetail(vtSymbol, contract)
            self.detailDict[vtSymbol] = detail
            
            # 设置持仓细节的委托转换模式
            contract = self.getContract(vtSymbol)
            
            if contract:
                detail.exchange = contract.exchange
                
                # 上期所合约
                if contract.exchange == EXCHANGE_SHFE:
                    detail.mode = detail.MODE_SHFE
                
                # 检查是否有平今惩罚
                for productID in self.tdPenaltyList:
                    if str(productID) in contract.symbol:
                        detail.mode = detail.MODE_TDPENALTY
                
        return detail
    
    #----------------------------------------------------------------------
    def getAllPositionDetails(self):
        """查询所有本地持仓缓存细节"""
        return self.detailDict.values()
    
    #----------------------------------------------------------------------
    def updateOrderReq(self, req, vtOrderID):
        """委托请求更新"""
        vtSymbol = req.vtSymbol
            
        detail = self.getPositionDetail(vtSymbol)
        detail.updateOrderReq(req, vtOrderID)
    
    #----------------------------------------------------------------------
    def convertOrderReq(self, req):
        """根据规则转换委托请求"""
        detail = self.detailDict.get(req.vtSymbol, None)
        if not detail:
            return [req]
        else:
            return detail.convertOrderReq(req)

    #----------------------------------------------------------------------
    def getLog(self):
        """获取日志"""
        return self.logList
    
    #----------------------------------------------------------------------
    def getError(self):
        """获取错误"""
        return self.errorList
    

########################################################################    
class LogEngine(object):
    """日志引擎"""
    
    # 单例模式
    __metaclass__ = VtSingleton
    
    # 日志级别
    LEVEL_DEBUG = logging.DEBUG
    LEVEL_INFO = logging.INFO
    LEVEL_WARN = logging.WARN
    LEVEL_ERROR = logging.ERROR
    LEVEL_CRITICAL = logging.CRITICAL

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.logger = logging.getLogger()        
        self.formatter = logging.Formatter('%(asctime)s  %(levelname)s: %(message)s')
        self.level = self.LEVEL_CRITICAL
        
        self.consoleHandler = None
        self.fileHandler = None
        
        # 添加NullHandler防止无handler的错误输出
        nullHandler = logging.NullHandler()
        self.logger.addHandler(nullHandler)    
        
        # 日志级别函数映射
        self.levelFunctionDict = {
            self.LEVEL_DEBUG: self.debug,
            self.LEVEL_INFO: self.info,
            self.LEVEL_WARN: self.warn,
            self.LEVEL_ERROR: self.error,
            self.LEVEL_CRITICAL: self.critical,
        }
        
    #----------------------------------------------------------------------
    def setLogLevel(self, level):
        """设置日志级别"""
        self.logger.setLevel(level)
        self.level = level
    
    #----------------------------------------------------------------------
    def addConsoleHandler(self):
        """添加终端输出"""
        if not self.consoleHandler:
            self.consoleHandler = logging.StreamHandler()
            self.consoleHandler.setLevel(self.level)
            self.consoleHandler.setFormatter(self.formatter)
            self.logger.addHandler(self.consoleHandler)
            
    #----------------------------------------------------------------------
    def addFileHandler(self, filename=''):
        """添加文件输出"""
        if not self.fileHandler:
            if not filename:
                filename = 'vt_' + datetime.now().strftime('%Y%m%d') + '.log'
            filepath = getTempPath(filename)
            self.fileHandler = logging.FileHandler(filepath)
            self.fileHandler.setLevel(self.level)
            self.fileHandler.setFormatter(self.formatter)
            self.logger.addHandler(self.fileHandler)
    
    #----------------------------------------------------------------------
    def debug(self, msg):
        """开发时用"""
        self.logger.debug(msg)
        
    #----------------------------------------------------------------------
    def info(self, msg):
        """正常输出"""
        self.logger.info(msg)
        
    #----------------------------------------------------------------------
    def warn(self, msg):
        """警告信息"""
        self.logger.warn(msg)
        
    #----------------------------------------------------------------------
    def error(self, msg):
        """报错输出"""
        self.logger.error(msg)
        
    #----------------------------------------------------------------------
    def exception(self, msg):
        """报错输出+记录异常信息"""
        self.logger.exception(msg)

    #----------------------------------------------------------------------
    def critical(self, msg):
        """影响程序运行的严重错误"""
        self.logger.critical(msg)

    #----------------------------------------------------------------------
    def processLogEvent(self, event):
        """处理日志事件"""
        log = event.dict_['data']
        function = self.levelFunctionDict[log.logLevel]     # 获取日志级别对应的处理函数
        msg = '\t'.join([log.gatewayName, log.logContent])
        function(msg)
        
    
########################################################################
class PositionDetail(object):
    """本地维护的持仓信息"""
    WORKING_STATUS = [STATUS_UNKNOWN, STATUS_NOTTRADED, STATUS_PARTTRADED]
    
    MODE_NORMAL = 'normal'          # 普通模式
    MODE_SHFE = 'shfe'              # 上期所今昨分别平仓
    MODE_TDPENALTY = 'tdpenalty'    # 平今惩罚

    #----------------------------------------------------------------------
    def __init__(self, vtSymbol, contract=None):
        """Constructor"""
        self.vtSymbol = vtSymbol
        self.symbol = EMPTY_STRING
        self.exchange = EMPTY_STRING
        self.name = EMPTY_UNICODE    
        self.size = 1
        
        if contract:
            self.symbol = contract.symbol
            self.exchange = contract.exchange
            self.name = contract.name
            self.size = contract.size
        
        self.longPos = EMPTY_INT
        self.longYd = EMPTY_INT
        self.longTd = EMPTY_INT
        self.longPosFrozen = EMPTY_INT
        self.longYdFrozen = EMPTY_INT
        self.longTdFrozen = EMPTY_INT
        self.longPnl = EMPTY_FLOAT
        self.longPrice = EMPTY_FLOAT
        
        self.shortPos = EMPTY_INT
        self.shortYd = EMPTY_INT
        self.shortTd = EMPTY_INT
        self.shortPosFrozen = EMPTY_INT
        self.shortYdFrozen = EMPTY_INT
        self.shortTdFrozen = EMPTY_INT
        self.shortPnl = EMPTY_FLOAT
        self.shortPrice = EMPTY_FLOAT
        
        self.lastPrice = EMPTY_FLOAT
        
        self.mode = self.MODE_NORMAL
        self.exchange = EMPTY_STRING
        
        self.workingOrderDict = {}
        
    #----------------------------------------------------------------------
    def updateTrade(self, trade):
        """成交更新"""
        # 多头
        if trade.direction is DIRECTION_LONG:
            # 开仓
            if trade.offset is OFFSET_OPEN:
                self.longTd += trade.volume
            # 平今
            elif trade.offset is OFFSET_CLOSETODAY:
                self.shortTd -= trade.volume
            # 平昨
            elif trade.offset is OFFSET_CLOSEYESTERDAY:
                self.shortYd -= trade.volume
            # 平仓
            elif trade.offset is OFFSET_CLOSE:
                # 上期所等同于平昨
                if self.exchange is EXCHANGE_SHFE:
                    self.shortYd -= trade.volume
                # 非上期所，优先平今
                else:
                    self.shortTd -= trade.volume
                    
                    if self.shortTd < 0:
                        self.shortYd += self.shortTd
                        self.shortTd = 0    
        # 空头
        elif trade.direction is DIRECTION_SHORT:
            # 开仓
            if trade.offset is OFFSET_OPEN:
                self.shortTd += trade.volume
            # 平今
            elif trade.offset is OFFSET_CLOSETODAY:
                self.longTd -= trade.volume
            # 平昨
            elif trade.offset is OFFSET_CLOSEYESTERDAY:
                self.longYd -= trade.volume
            # 平仓
            elif trade.offset is OFFSET_CLOSE:
                # 上期所等同于平昨
                if self.exchange is EXCHANGE_SHFE:
                    self.longYd -= trade.volume
                # 非上期所，优先平今
                else:
                    self.longTd -= trade.volume
                    
                    if self.longTd < 0:
                        self.longYd += self.longTd
                        self.longTd = 0
                    
        # 汇总
        self.calculatePrice(trade)
        self.calculatePosition()
        self.calculatePnl()
    
    #----------------------------------------------------------------------
    def updateOrder(self, order):
        """委托更新"""
        # 将活动委托缓存下来
        if order.status in self.WORKING_STATUS:
            self.workingOrderDict[order.vtOrderID] = order
            
        # 移除缓存中已经完成的委托
        else:
            if order.vtOrderID in self.workingOrderDict:
                del self.workingOrderDict[order.vtOrderID]
                
        # 计算冻结
        self.calculateFrozen()
    
    #----------------------------------------------------------------------
    def updatePosition(self, pos):
        """持仓更新"""
        if pos.direction is DIRECTION_LONG:
            self.longPos = pos.position
            self.longYd = pos.ydPosition
            self.longTd = self.longPos - self.longYd
            self.longPnl = pos.positionProfit
            self.longPrice = pos.price
        elif pos.direction is DIRECTION_SHORT:
            self.shortPos = pos.position
            self.shortYd = pos.ydPosition
            self.shortTd = self.shortPos - self.shortYd
            self.shortPnl = pos.positionProfit
            self.shortPrice = pos.price
            
        #self.output()
    
    #----------------------------------------------------------------------
    def updateOrderReq(self, req, vtOrderID):
        """发单更新"""
        vtSymbol = req.vtSymbol        
            
        # 基于请求生成委托对象
        order = VtOrderData()
        order.vtSymbol = vtSymbol
        order.symbol = req.symbol
        order.exchange = req.exchange
        order.offset = req.offset
        order.direction = req.direction
        order.totalVolume = req.volume
        order.status = STATUS_UNKNOWN
        
        # 缓存到字典中
        self.workingOrderDict[vtOrderID] = order
        
        # 计算冻结量
        self.calculateFrozen()
        
    #----------------------------------------------------------------------
    def updateTick(self, tick):
        """行情更新"""
        self.lastPrice = tick.lastPrice
        self.calculatePnl()
        
    #----------------------------------------------------------------------
    def calculatePnl(self):
        """计算持仓盈亏"""
        self.longPnl = self.longPos * (self.lastPrice - self.longPrice) * self.size
        self.shortPnl = self.shortPos * (self.shortPrice - self.lastPrice) * self.size
        
    #----------------------------------------------------------------------
    def calculatePrice(self, trade):
        """计算持仓均价（基于成交数据）"""
        # 只有开仓会影响持仓均价
        if trade.offset == OFFSET_OPEN:
            if trade.direction == DIRECTION_LONG:
                cost = self.longPrice * self.longPos
                cost += trade.volume * trade.price
                newPos = self.longPos + trade.volume
                if newPos:
                    self.longPrice = cost / newPos
                else:
                    self.longPrice = 0
            else:
                cost = self.shortPrice * self.shortPos
                cost += trade.volume * trade.price
                newPos = self.shortPos + trade.volume
                if newPos:
                    self.shortPrice = cost / newPos
                else:
                    self.shortPrice = 0
    
    #----------------------------------------------------------------------
    def calculatePosition(self):
        """计算持仓情况"""
        self.longPos = self.longTd + self.longYd
        self.shortPos = self.shortTd + self.shortYd      
        
    #----------------------------------------------------------------------
    def calculateFrozen(self):
        """计算冻结情况"""
        # 清空冻结数据
        self.longPosFrozen = EMPTY_INT
        self.longYdFrozen = EMPTY_INT
        self.longTdFrozen = EMPTY_INT
        self.shortPosFrozen = EMPTY_INT
        self.shortYdFrozen = EMPTY_INT
        self.shortTdFrozen = EMPTY_INT     
        
        # 遍历统计
        for order in self.workingOrderDict.values():
            # 计算剩余冻结量
            frozenVolume = order.totalVolume - order.tradedVolume
            
            # 多头委托
            if order.direction is DIRECTION_LONG:
                # 平今
                if order.offset is OFFSET_CLOSETODAY:
                    self.shortTdFrozen += frozenVolume
                # 平昨
                elif order.offset is OFFSET_CLOSEYESTERDAY:
                    self.shortYdFrozen += frozenVolume
                # 平仓
                elif order.offset is OFFSET_CLOSE:
                    self.shortTdFrozen += frozenVolume
                    
                    if self.shortTdFrozen > self.shortTd:
                        self.shortYdFrozen += (self.shortTdFrozen - self.shortTd)
                        self.shortTdFrozen = self.shortTd
            # 空头委托
            elif order.direction is DIRECTION_SHORT:
                # 平今
                if order.offset is OFFSET_CLOSETODAY:
                    self.longTdFrozen += frozenVolume
                # 平昨
                elif order.offset is OFFSET_CLOSEYESTERDAY:
                    self.longYdFrozen += frozenVolume
                # 平仓
                elif order.offset is OFFSET_CLOSE:
                    self.longTdFrozen += frozenVolume
                    
                    if self.longTdFrozen > self.longTd:
                        self.longYdFrozen += (self.longTdFrozen - self.longTd)
                        self.longTdFrozen = self.longTd
                        
            # 汇总今昨冻结
            self.longPosFrozen = self.longYdFrozen + self.longTdFrozen
            self.shortPosFrozen = self.shortYdFrozen + self.shortTdFrozen
            
    #----------------------------------------------------------------------
    def output(self):
        """"""
        print self.vtSymbol, '-'*30
        print 'long, total:%s, td:%s, yd:%s' %(self.longPos, self.longTd, self.longYd)
        print 'long frozen, total:%s, td:%s, yd:%s' %(self.longPosFrozen, self.longTdFrozen, self.longYdFrozen)
        print 'short, total:%s, td:%s, yd:%s' %(self.shortPos, self.shortTd, self.shortYd)
        print 'short frozen, total:%s, td:%s, yd:%s' %(self.shortPosFrozen, self.shortTdFrozen, self.shortYdFrozen)        
    
    #----------------------------------------------------------------------
    def convertOrderReq(self, req):
        """转换委托请求"""
        # 普通模式无需转换
        if self.mode is self.MODE_NORMAL:
            return [req]
        
        # 上期所模式拆分今昨，优先平今
        elif self.mode is self.MODE_SHFE:
            # 开仓无需转换
            if req.offset is OFFSET_OPEN:
                return [req]
            
            # 多头
            if req.direction is DIRECTION_LONG:
                posAvailable = self.shortPos - self.shortPosFrozen
                tdAvailable = self.shortTd- self.shortTdFrozen
                ydAvailable = self.shortYd - self.shortYdFrozen            
            # 空头
            else:
                posAvailable = self.longPos - self.longPosFrozen
                tdAvailable = self.longTd - self.longTdFrozen
                ydAvailable = self.longYd - self.longYdFrozen
                
            # 平仓量超过总可用，拒绝，返回空列表
            if req.volume > posAvailable:
                return []
            # 平仓量小于今可用，全部平今
            elif req.volume <= tdAvailable:
                req.offset = OFFSET_CLOSETODAY
                return [req]
            # 平仓量大于今可用，平今再平昨
            else:
                l = []
                
                if tdAvailable > 0:
                    reqTd = copy(req)
                    reqTd.offset = OFFSET_CLOSETODAY
                    reqTd.volume = tdAvailable
                    l.append(reqTd)
                    
                reqYd = copy(req)
                reqYd.offset = OFFSET_CLOSEYESTERDAY
                reqYd.volume = req.volume - tdAvailable
                l.append(reqYd)
                
                return l
            
        # 平今惩罚模式，没有今仓则平昨，否则锁仓
        elif self.mode is self.MODE_TDPENALTY:
            # 多头
            if req.direction is DIRECTION_LONG:
                td = self.shortTd
                ydAvailable = self.shortYd - self.shortYdFrozen
            # 空头
            else:
                td = self.longTd
                ydAvailable = self.longYd - self.longYdFrozen
                
            # 这里针对开仓和平仓委托均使用一套逻辑
            
            # 如果有今仓，则只能开仓（或锁仓）
            if td:
                req.offset = OFFSET_OPEN
                return [req]
            # 如果平仓量小于昨可用，全部平昨
            elif req.volume <= ydAvailable:
                if self.exchange is EXCHANGE_SHFE:
                    req.offset = OFFSET_CLOSEYESTERDAY
                else:
                    req.offset = OFFSET_CLOSE
                return [req]
            # 平仓量大于昨可用，平仓再反向开仓
            else:
                l = []
                
                if ydAvailable > 0:
                    reqClose = copy(req)
                    if self.exchange is EXCHANGE_SHFE:
                        reqClose.offset = OFFSET_CLOSEYESTERDAY
                    else:
                        reqClose.offset = OFFSET_CLOSE
                    reqClose.volume = ydAvailable
                    
                    l.append(reqClose)
                    
                reqOpen = copy(req)
                reqOpen.offset = OFFSET_OPEN
                reqOpen.volume = req.volume - ydAvailable
                l.append(reqOpen)
                
                return l
        
        # 其他情况则直接返回空
        return []