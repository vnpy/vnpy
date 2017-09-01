# encoding: UTF-8

import os
import shelve
import logging
from collections import OrderedDict
from datetime import datetime

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
        if self.rmEngine and not self.rmEngine.checkRisk(orderReq):
            return ''

        gateway = self.getGateway(gatewayName)
        
        if gateway:
            return gateway.sendOrder(orderReq)
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
    def getAllWorkingOrders(self):
        """查询所有的活跃的委托（返回列表）"""
        return self.dataEngine.getAllWorkingOrders()
    
    #----------------------------------------------------------------------
    def getAllGatewayDetails(self):
        """查询引擎中所有底层接口的信息"""
        return self.gatewayDetailList
    
    #----------------------------------------------------------------------
    def getAllAppDetails(self):
        """查询引擎中所有上层应用的信息"""
        return self.appDetailList
    
    #----------------------------------------------------------------------
    def initLogEngine(self):
        """初始化日志引擎"""
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
        self.eventEngine.register(EVENT_LOG, self.logEngine.processLogEvent)
        
        # 记录新启动日志引擎
        self.logEngine.info(u"------日志引擎启动------")
        

########################################################################
class DataEngine(object):
    """数据引擎"""
    contractFileName = 'ContractData.vt'
    contractFilePath = getTempPath(contractFileName)

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """Constructor"""
        self.eventEngine = eventEngine
        
        # 保存合约详细信息的字典
        self.contractDict = {}
        
        # 保存委托数据的字典
        self.orderDict = {}
        
        # 保存活动委托数据的字典（即可撤销）
        self.workingOrderDict = {}
        
        # 读取保存在硬盘的合约数据
        self.loadContracts()
        
        # 注册事件监听
        self.registerEvent()
        
    #----------------------------------------------------------------------
    def updateContract(self, event):
        """更新合约数据"""
        contract = event.dict_['data']
        self.contractDict[contract.vtSymbol] = contract
        self.contractDict[contract.symbol] = contract       # 使用常规代码（不包括交易所）可能导致重复
        
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
    def updateOrder(self, event):
        """更新委托数据"""
        order = event.dict_['data']        
        self.orderDict[order.vtOrderID] = order
        
        # 如果订单的状态是全部成交或者撤销，则需要从workingOrderDict中移除
        if order.status in [STATUS_ALLTRADED, STATUS_REJECTED, STATUS_CANCELLED]:
            if order.vtOrderID in self.workingOrderDict:
                del self.workingOrderDict[order.vtOrderID]
        # 否则则更新字典中的数据        
        else:
            self.workingOrderDict[order.vtOrderID] = order
        
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
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_CONTRACT, self.updateContract)
        self.eventEngine.register(EVENT_ORDER, self.updateOrder)


########################################################################
class LogEngine(object):
    """日志引擎"""
    
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
    def addFileHandler(self):
        """添加文件输出"""
        if not self.fileHandler:
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
        function(log.logContent)
    
    
