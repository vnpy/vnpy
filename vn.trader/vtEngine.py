# encoding: UTF-8

import shelve
from collections import OrderedDict
from datetime import datetime

from pymongo import MongoClient
from pymongo.errors import ConnectionFailure

from eventEngine import *
from vtGateway import *
from vtFunction import loadMongoSetting
from language import text

from gateway import GATEWAY_DICT
from ctaStrategy.ctaEngine import CtaEngine
from dataRecorder.drEngine import DrEngine
from riskManager.rmEngine import RmEngine

import logging

########################################################################
class MainEngine(object):
    """主引擎"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        # 记录今日日期
        self.todayDate = datetime.now().strftime('%Y%m%d')

        # 创建事件引擎
        self.eventEngine = EventEngine2()
        self.eventEngine.start()
        
        # 创建数据引擎
        self.dataEngine = DataEngine(self, self.eventEngine)
        
        # MongoDB数据库相关
        self.dbClient = None    # MongoDB客户端对象
        
        # 调用一个个初始化函数
        self.initGateway()

        # 扩展模块
        self.ctaEngine = CtaEngine(self, self.eventEngine)  # cta策略运行模块
        self.drEngine = DrEngine(self, self.eventEngine)    # 数据记录模块
        self.rmEngine = RmEngine(self, self.eventEngine)    # 风险管理模块
        
    #----------------------------------------------------------------------
    def initGateway(self):
        """初始化接口对象"""
        # 用来保存接口对象的字典
        self.gatewayDict = OrderedDict()

        # 初始化的接口模块，以及其指定的名称,CTP是模块，value，是该模块下的多个连接配置文件,如 CTP_JR_connect.json
        init_gateway_names = {'CTP': ['CTP', 'CTP_Prod', 'CTP_Post', 'CTP_EBF', 'CTP_JR']}

        # 遍历接口字典并自动创建所有的接口对象
        for gatewayModule in GATEWAY_DICT.values():
            try:
                if gatewayModule.gatewayName not in init_gateway_names:
                    continue

                for gw_name in init_gateway_names[gatewayModule.gatewayName]:
                    self.addGateway(gatewayModule.gateway,gw_name)
                    if gatewayModule.gatewayQryEnabled:
                        self.gatewayDict[gw_name].setQryEnabled(True)
            except Exception, e:
                print e

    #----------------------------------------------------------------------
    def addGateway(self, gateway, gatewayName=None):
        """创建接口"""
        self.gatewayDict[gatewayName] = gateway(self.eventEngine, gatewayName)
        
    # ----------------------------------------------------------------------
    def connect(self, gatewayName):
        """连接特定名称的接口"""
        if gatewayName in self.gatewayDict:
            gateway = self.gatewayDict[gatewayName]
            gateway.connect()

            # 接口连接后自动执行数据库连接的任务
            self.dbConnect()
        else:
            self.writeLog(text.GATEWAY_NOT_EXIST.format(gateway=gatewayName))

    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq, gatewayName):
        """订阅特定接口的行情"""
        if gatewayName in self.gatewayDict:
            gateway = self.gatewayDict[gatewayName]
            gateway.subscribe(subscribeReq)
        else:
            self.writeLog(text.GATEWAY_NOT_EXIST.format(gateway=gatewayName))
        
    # ----------------------------------------------------------------------
    def sendOrder(self, orderReq, gatewayName):
        """对特定接口发单"""
        # 如果风控检查失败则不发单
        if not self.rmEngine.checkRisk(orderReq):
            self.writeLog(u'风控检查不通过')
            return ''    
        
        if gatewayName in self.gatewayDict:
            gateway = self.gatewayDict[gatewayName]
            return gateway.sendOrder(orderReq)
        else:
            self.writeLog(text.GATEWAY_NOT_EXIST.format(gateway=gatewayName))
    
    # ----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq, gatewayName):
        """对特定接口撤单"""
        if gatewayName in self.gatewayDict:
            gateway = self.gatewayDict[gatewayName]
            gateway.cancelOrder(cancelOrderReq)
        else:
            self.writeLog(text.GATEWAY_NOT_EXIST.format(gateway=gatewayName))

        
    #----------------------------------------------------------------------
    def qryAccont(self, gatewayName):
        """查询特定接口的账户"""
        if gatewayName in self.gatewayDict:
            gateway = self.gatewayDict[gatewayName]
            gateway.qryAccount()
        else:
            self.writeLog(text.GATEWAY_NOT_EXIST.format(gateway=gatewayName))

    def getAccountInfo(self):
        """读取风控的账号与仓位数据
        # Added by IncenseLee
        仅支持一个账号。不支持多账号
        以后支持跨市场套利才更新吧。
        """
        return self.rmEngine.getAccountInfo()

    #----------------------------------------------------------------------
    def qryPosition(self, gatewayName):
        """查询特定接口的持仓"""
        if gatewayName in self.gatewayDict:
            gateway = self.gatewayDict[gatewayName]
            gateway.qryPosition()
        else:
            self.writeLog(text.GATEWAY_NOT_EXIST.format(gateway=gatewayName))
        
    # ----------------------------------------------------------------------
    def exit(self):
        """退出程序前调用，保证正常退出"""        
        # 安全关闭所有接口
        for gateway in self.gatewayDict.values():        
            gateway.close()
        
        # 停止事件引擎
        self.eventEngine.stop()      
        
        # 停止数据记录引擎
        self.drEngine.stop()

        # 保存数据引擎里的合约数据到硬盘
        self.dataEngine.saveContracts()

    def disconnect(self,gateway_name = EMPTY_STRING):
        """断开底层gateway的连接"""

        # 只断开指定的gateway
        if gateway_name != EMPTY_STRING:
            if gateway_name in self.gatewayDict:
                gateway = self.gatewayDict[gateway_name]
                gateway.close()
                return
            else:
                self.writeLog(u'gateway接口不存在：%s' % gateway_name)

        # 断开所有的gateway
        for gateway in self.gatewayDict.values():
            gateway.close()

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """快速发出日志事件"""
        log = VtLogData()
        log.logContent = content
        event = Event(type_=EVENT_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)

        # 写入本地log日志
        logging.info(content)

    # ----------------------------------------------------------------------
    def dbConnect(self):
        """连接MongoDB数据库"""
        if not self.dbClient:
            # 读取MongoDB的设置
            host, port, logging = loadMongoSetting()
                
            try:
                # 设置MongoDB操作的超时时间为0.5秒
                self.dbClient = MongoClient(host, port, connectTimeoutMS=500)
                
                # 调用server_info查询服务器状态，防止服务器异常并未连接成功
                self.dbClient.server_info()

                self.writeLog(text.DATABASE_CONNECTING_COMPLETED)

                # 如果启动日志记录，则注册日志事件监听函数
                if logging:
                    self.eventEngine.register(EVENT_LOG, self.dbLogging)

            except ConnectionFailure:
                self.writeLog(text.DATABASE_CONNECTING_FAILED)
    
    # ----------------------------------------------------------------------
    def dbInsert(self, dbName, collectionName, d):
        """向MongoDB中插入数据，d是具体数据"""
        if self.dbClient:
            db = self.dbClient[dbName]
            collection = db[collectionName]
            collection.insert_one(d)
        else:
            self.writeLog(text.DATA_INSERT_FAILED)
    
    # ----------------------------------------------------------------------
    def dbQuery(self, dbName, collectionName, d):
        """从MongoDB中读取数据，d是查询要求，返回的是数据库查询的指针"""
        if self.dbClient:
            db = self.dbClient[dbName]
            collection = db[collectionName]
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

    # ----------------------------------------------------------------------
    def getAllGatewayNames(self):
        """查询引擎中所有可用接口的名称"""
        return self.gatewayDict.keys()

    def clearData(self):
        """清空数据引擎的数据"""
        self.dataEngine.clearData()
        self.ctaEngine.clearData()

    def saveData(self):
        self.ctaEngine.saveStrategyData()

########################################################################
class DataEngine(object):
    """数据引擎"""
    contractFileName = 'ContractData.vt'

    # ----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
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

        # 已订阅合约代码
        self.subscribedSymbols = set()
        
    # ----------------------------------------------------------------------
    def updateContract(self, event):
        """更新合约数据"""
        contract = event.dict_['data']
        self.contractDict[contract.vtSymbol] = contract
        self.contractDict[contract.symbol] = contract       # 使用常规代码（不包括交易所）可能导致重复
        
    # ----------------------------------------------------------------------
    def getContract(self, vtSymbol):
        """查询合约对象"""
        try:
            return self.contractDict[vtSymbol]
        except KeyError:
            return None
        
    # ----------------------------------------------------------------------
    def getAllContracts(self):
        """查询所有合约对象（返回列表）"""
        return self.contractDict.values()
    
    # ----------------------------------------------------------------------
    def saveContracts(self):
        """保存所有合约对象到硬盘"""
        f = shelve.open(self.contractFileName)
        f['data'] = self.contractDict
        f.close()
    
    # ----------------------------------------------------------------------
    def loadContracts(self):
        """从硬盘读取合约对象"""
        f = shelve.open(self.contractFileName)
        if 'data' in f:
            d = f['data']
            for key, value in d.items():
                self.contractDict[key] = value
        f.close()
        
    # ----------------------------------------------------------------------
    def updateOrder(self, event):
        """更新委托数据"""
        order = event.dict_['data']        
        self.orderDict[order.vtOrderID] = order
        
        # 如果订单的状态是全部成交或者撤销，则需要从workingOrderDict中移除
        if order.status == STATUS_ALLTRADED or order.status == STATUS_CANCELLED:
            if order.vtOrderID in self.workingOrderDict:
                del self.workingOrderDict[order.vtOrderID]
        # 否则则更新字典中的数据        
        else:
            self.workingOrderDict[order.vtOrderID] = order
        
    # ----------------------------------------------------------------------
    def getOrder(self, vtOrderID):
        """查询委托单（报单）"""
        try:
            return self.orderDict[vtOrderID]
        except KeyError:
            return None
    
    # ----------------------------------------------------------------------
    def getAllWorkingOrders(self):
        """查询所有活动委托（返回列表）"""
        return self.workingOrderDict.values()
    
    # ----------------------------------------------------------------------
    def registerEvent(self):
        """注册事件监听"""
        self.eventEngine.register(EVENT_CONTRACT, self.updateContract)
        self.eventEngine.register(EVENT_ORDER, self.updateOrder)
        self.eventEngine.register(EVENT_POSITION, self.updatePosition)
        
    def clearData(self):
        """清空数据"""

        self.orderDict = {}
        self.workingOrderDict = {}
        self.subscribedSymbols.clear()

    def updatePosition(self,event):
        """更新持仓信息"""
        # 在获取更新持仓信息时，自动订阅这个symbol
        # 目的：1、

        position = event.dict_['data']
        symbol = position.symbol

        if symbol is None:
            return

        if len(symbol) == 0:
            return

        # 已存在，不做更新
        if symbol in self.subscribedSymbols:
            return

        self.subscribedSymbols.add(symbol)

        gatewayName = position.gatewayName
        contract = self.mainEngine.getContract(symbol)

        if not contract:
            self.mainEngine.writeLog(u'找不到合约{0}信息'.format(symbol))
            return

        # 订阅合约
        req = VtSubscribeReq()
        req.symbol = symbol
        req.exchange = contract.exchange
        req.currency = ''
        req.productClass = ''

        self.mainEngine.subscribe(req, gatewayName)

        self.mainEngine.writeLog(u'自动订阅合约{0}'.format(symbol))

