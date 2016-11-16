# -*- coding: utf-8 -*-

import os
import shelve
from collections import OrderedDict

from pymongo import MongoClient
from pymongo.errors import ConnectionFailure

from vnpy.engine.cta.ctaEngine import CtaEngine
from vnpy.engine.dr.drEngine import DrEngine
from vnpy.engine.rm.rmEngine import RmEngine
from vnpy.utils.vtFunction import loadMongoSetting, findDataPath, findRootPath
from vnpy.utils.vtGateway import *


########################################################################
class MainEngine(object):
    """主引擎"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        # 创建事件引擎
        self.eventEngine = EventEngine2()
        self.eventEngine.start()

        # 创建数据引擎
        self.dataEngine = DataEngine(self.eventEngine)

        # MongoDB数据库相关
        self.dbClient = None  # MongoDB客户端对象

        # 调用一个个初始化函数
        self.gatewayDict = None
        self.initGateway()

        # 扩展模块
        self.ctaEngine = CtaEngine(self, self.eventEngine)
        self.drEngine = DrEngine(self, self.eventEngine)
        self.rmEngine = RmEngine(self, self.eventEngine)

    # ----------------------------------------------------------------------
    def initGateway(self):
        """初始化接口对象"""
        # 用来保存接口对象的字典
        self.gatewayDict = OrderedDict()

        # 创建我们想要接入的接口对象
        gate_dir = os.listdir(findRootPath() + '/gate')

        for _name in gate_dir:

            if _name.startswith("__"):
                continue
            try:
                gate_module = __import__("vnpy.gate.{}.{}".format(_name.lower(), "{}Gateway".format(_name.lower())),
                                         fromlist=["{}Gateway".format(_name.title())])
                gateway = getattr(gate_module, "{}Gateway".format(_name.title()))
                self.addGateway(gateway, _name.upper())
                self.gatewayDict[_name.upper()].setQryEnabled(True)
            except Exception, e:
                print e

    # ----------------------------------------------------------------------
    def addGateway(self, gateway, gateway_name=None):
        """创建接口"""
        self.gatewayDict[gateway_name] = gateway(self.eventEngine, gateway_name)

    # ----------------------------------------------------------------------
    def connect(self, gateway_name):
        """连接特定名称的接口"""
        if gateway_name in self.gatewayDict:
            gateway = self.gatewayDict[gateway_name]
            gateway.connect()
        else:
            self.writeLog(u'接口不存在：%s' % gateway_name)

    # ----------------------------------------------------------------------
    def subscribe(self, subscribe_req, gateway_name):
        """订阅特定接口的行情"""
        if gateway_name in self.gatewayDict:
            gateway = self.gatewayDict[gateway_name]
            gateway.subscribe(subscribe_req)
        else:
            self.writeLog(u'接口不存在：%s' % gateway_name)

    # ----------------------------------------------------------------------
    def sendOrder(self, order_req, gateway_name):
        """对特定接口发单"""
        # 如果风控检查失败则不发单
        if not self.rmEngine.checkRisk(order_req):
            return ''

        if gateway_name in self.gatewayDict:
            gateway = self.gatewayDict[gateway_name]
            return gateway.sendOrder(order_req)
        else:
            self.writeLog(u'接口不存在：%s' % gateway_name)

    # ----------------------------------------------------------------------
    def cancelOrder(self, cancel_order_req, gateway_name):
        """对特定接口撤单"""
        if gateway_name in self.gatewayDict:
            gateway = self.gatewayDict[gateway_name]
            gateway.cancelOrder(cancel_order_req)
        else:
            self.writeLog(u'接口不存在：%s' % gateway_name)

    # ----------------------------------------------------------------------
    def qryAccount(self, gateway_name):
        """查询特定接口的账户"""
        if gateway_name in self.gatewayDict:
            gateway = self.gatewayDict[gateway_name]
            gateway.qryAccount()
        else:
            self.writeLog(u'接口不存在：%s' % gateway_name)

    # ----------------------------------------------------------------------
    def qryPosition(self, gateway_name):
        """查询特定接口的持仓"""
        if gateway_name in self.gatewayDict:
            gateway = self.gatewayDict[gateway_name]
            gateway.qryPosition()
        else:
            self.writeLog(u'接口不存在：%s' % gateway_name)

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

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """快速发出日志事件"""
        log = VtLogData()
        log.logContent = content
        event = Event(type_=EVENT_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)

    # ----------------------------------------------------------------------
    def dbConnect(self):
        """连接MongoDB数据库"""
        if not self.dbClient:
            # 读取MongoDB的设置
            host, port = loadMongoSetting()

            try:
                # 设置MongoDB操作的超时时间为0.5秒
                self.dbClient = MongoClient(host, port, serverSelectionTimeoutMS=500)

                # 调用server_info查询服务器状态，防止服务器异常并未连接成功
                self.dbClient.server_info()

                self.writeLog(u'MongoDB连接成功')
            except ConnectionFailure:
                self.writeLog(u'MongoDB连接失败')

    # ----------------------------------------------------------------------
    def dbInsert(self, db_name, collection_name, d):
        """向MongoDB中插入数据，d是具体数据"""
        if self.dbClient:
            db = self.dbClient[db_name]
            collection = db[collection_name]
            collection.insert(d)

    # ----------------------------------------------------------------------
    def dbQuery(self, db_name, collection_name, d):
        """从MongoDB中读取数据，d是查询要求，返回的是数据库查询的指针"""
        if self.dbClient:
            db = self.dbClient[db_name]
            collection = db[collection_name]
            cursor = collection.find(d)
            return cursor
        else:
            return None

    # ----------------------------------------------------------------------
    def getContract(self, vt_symbol):
        """查询合约"""
        return self.dataEngine.getContract(vt_symbol)

    # ----------------------------------------------------------------------
    def getAllContracts(self):
        """查询所有合约（返回列表）"""
        return self.dataEngine.getAllContracts()

    # ----------------------------------------------------------------------
    def getOrder(self, vt_order_id):
        """查询委托"""
        return self.dataEngine.getOrder(vt_order_id)

    # ----------------------------------------------------------------------
    def getAllWorkingOrders(self):
        """查询所有的活跃的委托（返回列表）"""
        return self.dataEngine.getAllWorkingOrders()


########################################################################
class DataEngine(object):
    """数据引擎"""
    contractFileName = findDataPath('ContractData.vt')

    # ----------------------------------------------------------------------
    def __init__(self, event_engine):
        """Constructor"""
        self.eventEngine = event_engine

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

    # ----------------------------------------------------------------------
    def updateContract(self, event):
        """更新合约数据"""
        contract = event.dict_['data']
        self.contractDict[contract.vtSymbol] = contract
        self.contractDict[contract.symbol] = contract  # 使用常规代码（不包括交易所）可能导致重复

    # ----------------------------------------------------------------------
    def getContract(self, vt_symbol):
        """查询合约对象"""
        try:
            return self.contractDict[vt_symbol]
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
    def getOrder(self, vt_order_id):
        """查询委托"""
        try:
            return self.orderDict[vt_order_id]
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
