# encoding: UTF-8

print 'load vtEngine.py'

import shelve
from collections import OrderedDict
import logging

from pymongo import MongoClient
from pymongo.errors import ConnectionFailure

from vnpy.trader.vtEvent import Event as vn_event
from vnpy.trader.language import text
#from vnpy.trader.app.ctaStrategy.ctaEngine import CtaEngine
#from vnpy.trader.app.dataRecorder.drEngine import DrEngine
#from vnpy.trader.app.riskManager.rmEngine import RmEngine
from vnpy.trader.vtFunction import loadMongoSetting
from vnpy.trader.vtGateway import *
from vnpy.trader.app import (ctaStrategy, riskManager)
import psutil
try:
    from util_mail import *
except:
    pass

########################################################################
class MainEngine(object):
    """主引擎"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """Constructor"""
        # 记录今日日期
        self.todayDate = datetime.now().strftime('%Y%m%d')

        # 创建事件引擎
        self.eventEngine = eventEngine
        self.eventEngine.start()
        
        # 创建数据引擎
        self.dataEngine = DataEngine(self, self.eventEngine)
        
        # MongoDB数据库相关
        self.dbClient = None    # MongoDB客户端对象

        # 接口实例
        self.gatewayDict = OrderedDict()
        self.gatewayDetailList = []

        # 应用模块实例
        self.appDict = OrderedDict()
        self.appDetailList = []

        # 扩展模块
        self.ctaEngine = None       # CtaEngine(self, self.eventEngine)  # cta策略运行模块
        self.drEngine = None        # DrEngine(self, self.eventEngine)    # 数据记录模块
        self.rmEngine = None        #   RmEngine(self, self.eventEngine)    # 风险管理模块

        self.connected_gw_name = u''
    # ----------------------------------------------------------------------
    def addGateway(self, gatewayModule,gateway_name=EMPTY_STRING):
        """添加底层接口"""
        # 是否使用指定的gateway_name
        if gateway_name==EMPTY_STRING:
            gatewayName = gatewayModule.gatewayName
        else:
            gatewayName = gateway_name

        # 创建接口实例
        self.gatewayDict[gatewayName] = gatewayModule.gatewayClass(self.eventEngine,
                                                                   gatewayName)

        # 设置接口轮询
        if gatewayModule.gatewayQryEnabled:
            self.gatewayDict[gatewayName].setQryEnabled(gatewayModule.gatewayQryEnabled)

        # 保存接口详细信息
        d = {
            'gatewayName': gatewayName,                         #gatewayModule.gatewayName,
            'gatewayDisplayName': gatewayName,                  #gatewayModule.gatewayDisplayName,
            'gatewayType': gatewayModule.gatewayType
        }
        self.gatewayDetailList.append(d)

        if gateway_name != self.connected_gw_name:
            self.connected_gw_name = gateway_name

    # ----------------------------------------------------------------------
    def addApp(self, appModule):
        """添加上层应用"""
        appName = appModule.appName

        # 创建应用实例
        self.appDict[appName] = appModule.appEngine(self, self.eventEngine)

        # 将应用引擎实例添加到主引擎的属性中
        self.__dict__[appName] = self.appDict[appName]

        # 兼容旧的self.ctaEngine/self.rmEngine
        if appName == ctaStrategy.appName:
            self.ctaEngine = self.appDict[appName]
        elif appName == riskManager.appName:
            self.rmEngine = self.appDict[appName]

        # 保存应用信息
        d = {
            'appName': appModule.appName,
            'appDisplayName': appModule.appDisplayName,
            'appWidget': appModule.appWidget,
            'appIco': appModule.appIco
        }
        self.appDetailList.append(d)

    # ----------------------------------------------------------------------
    def connect(self, gatewayName):
        """连接特定名称的接口"""
        if gatewayName in self.gatewayDict:
            gateway = self.gatewayDict[gatewayName]
            gateway.connect()

            if gatewayName != self.connected_gw_name:
                self.connected_gw_name = gatewayName

            # 接口连接后自动执行数据库连接的任务
            self.dbConnect()
            return True
        else:
            self.writeLog(text.GATEWAY_NOT_EXIST.format(gateway=gatewayName))
            return False

    def checkGatewayStatus(self,gatewayName):
        """check gateway connect status"""
        if gatewayName in self.gatewayDict:
            gateway = self.gatewayDict[gatewayName]
            return gateway.checkStatus()
        else:
            self.writeLog(text.GATEWAY_NOT_EXIST.format(gateway=gatewayName))
            return False

    def qryStatus(self):
        """查询Status"""
        status_dict = OrderedDict()

        # gateway Status
        gw_status_dict = OrderedDict()
        for k,g in self.gatewayDict.items():
            gw_status_dict[k] = g.checkStatus()
        status_dict['gateways']=gw_status_dict

        # ctaEngine Status
        if self.ctaEngine:
            tick_dict,strategy_dict = self.ctaEngine.qryStatus()
            status_dict['ticks']=tick_dict
            status_dict['strategies'] = strategy_dict

        # cpu/mem status
        cpuPercent = psutil.cpu_percent()
        memoryPercent = psutil.virtual_memory().percent
        server_info_dict = {'cpu':cpuPercent, 'mem':memoryPercent}
        status_dict['server'] = server_info_dict
#
        event = vn_event(type_=EVENT_STATUS)
        event.dict_['data']= status_dict
        self.eventEngine.put(event)

        return True
    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq, gatewayName):
        """订阅特定接口的行情"""
        if gatewayName in self.gatewayDict:
            gateway = self.gatewayDict[gatewayName]
            gateway.subscribe(subscribeReq)
        else:
            if len(self.gatewayDict) > 0:
                for gateway in self.gatewayDict.values():
                    gateway.subscribe(subscribeReq)
            else:
                self.writeLog(text.GATEWAY_NOT_EXIST.format(gateway=gatewayName))
        
    # ----------------------------------------------------------------------
    def sendOrder(self, orderReq, gatewayName):
        """对特定接口发单"""
        # 如果风控检查失败则不发单
        if self.rmEngine and not self.rmEngine.checkRisk(orderReq):
            self.writeCritical(u'风控检查不通过')
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

    # ----------------------------------------------------------------------
    def qryAccount(self, gatewayName):
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
        return 当前账号的权益、可用资金、当前仓位比例, 投资仓位比例上限
        """
        if self.rmEngine:
            return self.rmEngine.getAccountInfo()
        else:
            return 0, 0, 0, 0

    # ----------------------------------------------------------------------
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
        if self.drEngine:
            self.drEngine.stop()

        # 保存数据引擎里的合约数据到硬盘
        self.dataEngine.saveContracts()

    def disconnect(self, gateway_name=EMPTY_STRING):
        """断开底层gateway的连接"""
        try:
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

            return True

        except Exception as ex:
            print u'vtEngine.disconnect Exception:{0} '.format(str(ex))
            return False
    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """快速发出日志事件"""
        log = VtLogData()
        log.logContent = content
        event = vn_event(type_ = EVENT_LOG)
        event.dict_['data'] = log
        self.eventEngine.put(event)

        # 写入本地log日志
        logging.info(content)

    # ----------------------------------------------------------------------
    def writeError(self, content):
        """快速发出错误日志事件"""
        log = VtErrorData()
        log.errorMsg = content
        event = vn_event(type_=EVENT_ERROR)
        event.dict_['data'] = log
        self.eventEngine.put(event)

        # 写入本地log日志
        logging.error(content)
    # ----------------------------------------------------------------------
    def writeWarning(self, content):
        """快速发出告警日志事件"""
        log = VtLogData()
        log.logContent = content
        event = vn_event(type_=EVENT_WARNING)
        event.dict_['data'] = log
        self.eventEngine.put(event)

        # 写入本地log日志
        logging.warning(content)

        # 发出邮件
        try:
            sendmail(subject=u'{0} Warning'.format(self.connected_gw_name), msgcontent=content)
        except:
            pass

    # ----------------------------------------------------------------------
    def writeNotification(self, content):
        """快速发出通知日志事件"""
        log = VtLogData()
        log.logContent = content
        event = vn_event(type_=EVENT_NOTIFICATION)
        event.dict_['data'] = log
        self.eventEngine.put(event)

        # 发出邮件
        try:
            sendmail(subject=u'{0} Notification'.format(self.connected_gw_name), msgcontent=content)
        except:
            pass

    # ----------------------------------------------------------------------
    def writeCritical(self, content):
        """快速发出严重错误日志事件"""

        log = VtLogData()
        log.logContent = content
        event = vn_event(type_=EVENT_CRITICAL)
        event.dict_['data'] = log
        self.eventEngine.put(event)

        # 写入本地log日志
        logging.critical(content)

        # 发出邮件
        try:
            sendmail(subject=u'{0} Critical'.format(self.connected_gw_name), msgcontent=content)
        except:
            pass

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
                self.writeError(text.DATABASE_CONNECTING_FAILED)
    
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
        # ----------------------------------------------------------------------

    def getAllGatewayDetails(self):
        """查询引擎中所有底层接口的信息"""
        return self.gatewayDetailList

        # ----------------------------------------------------------------------

    def getAllAppDetails(self):
        """查询引擎中所有上层应用的信息"""
        return self.appDetailList

    # ----------------------------------------------------------------------
    def getApp(self, appName):
        """获取APP引擎对象"""
        return self.appDict[appName]

    def clearData(self):
        """清空数据引擎的数据"""
        self.dataEngine.clearData()
        self.ctaEngine.clearData()

    def saveData(self):
        if self.ctaEngine:
            self.ctaEngine.saveStrategyData()

    def initStrategy(self,name, force = False):
        if not self.ctaEngine:
            self.writeError(u'Cta Engine not started')
            return
        self.ctaEngine.initStrategy(name=name, force=force)
        self.qryStatus()

    def startStrategy(self,name):
        if not self.ctaEngine:
            self.writeError(u'Cta Engine not started')
            return
        self.ctaEngine.startStrategy(name=name)
        self.qryStatus()

    def stopStrategy(self,name):
        if not self.ctaEngine:
            self.writeError(u'Cta Engine not started')
            return
        self.ctaEngine.stopStrategy(name=name)
        self.qryStatus()

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
        if order.status in [STATUS_ALLTRADED, STATUS_REJECTED, STATUS_CANCELLED]:
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

