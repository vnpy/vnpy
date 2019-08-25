# encoding: UTF-8

'''
算法交易引擎
'''

from __future__ import division
import os
import importlib
import json
import traceback
import copy
from datetime import  datetime

from vnpy.event import Event
from vnpy.rpc import RpcServer
from vnpy.trader.vtEvent import EVENT_TIMER, EVENT_TICK, EVENT_ORDER, EVENT_TRADE, EVENT_POSITION
from vnpy.trader.vtConstant import (DIRECTION_LONG, DIRECTION_SHORT,
                                    PRICETYPE_LIMITPRICE, PRICETYPE_MARKETPRICE,
                                    OFFSET_OPEN, OFFSET_CLOSE,
                                    OFFSET_CLOSETODAY, OFFSET_CLOSEYESTERDAY,
                                    EXCHANGE_SHFE,EXCHANGE_INE, EMPTY_STRING, EMPTY_INT, EMPTY_FLOAT)

from vnpy.trader.vtConstant import ALGOTRADING_DB_NAME ,ALGO_SETTING_COL_NAME, ALGO_HISTORY_COL_NAME, ALGO_RUNNING_COL_NAME

from vnpy.trader.vtObject import VtSubscribeReq, VtOrderReq, VtCancelOrderReq, VtLogData,PositionBuffer
from vnpy.trader.vtFunction import getJsonPath, get_data_path, roundToVolumeTick
from vnpy.trader.setup_logger import setup_logger
from .algo import ALGO_DICT
from vnpy.trader.vtGlobal import globalSetting

EVENT_ALGO_LOG = 'eAlgoLog'          # 算法日志事件
EVENT_ALGO_PARAM = 'eAlgoParam'      # 算法参数事件
EVENT_ALGO_VAR = 'eAlgoVar'          # 算法变量事件
EVENT_ALGO_SETTING = 'eAlgoSetting'  # 算法配置事件


########################################################################
class AlgoEngine(object):
    """
    算法交易引擎
    # changelogs:
     20190408:
     -增加资金账号/合约size,保证金费率得查询接口
     -增加日志输出
    """

    # 策略配置文件
    settingFileName = 'Algo_setting.json'
    settingfilePath = getJsonPath(settingFileName, __file__)

    # ----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine,use_mongodb=False):
        """"""
        self.main_engine = mainEngine
        self.event_engine = eventEngine
        self.rpcServer = None

        # 是否使用数据库进行持久化
        self.use_mongodb = use_mongodb

        self.algo_dict = {}          # algoName:algo
        self.order_algo_dict = {}     # vtOrderID:algo
        self.symbol_algo_dict = {}    # vtSymbol:algo set
        self.setting_dict = {}       # setting_name:setting
        self.history_dict = {}       # algoName:dict

        self.posBufferDict = {}

        # 注册事件
        self.register_event()

        # 日志记录
        self.logger = None
        self.strategy_loggers = {}
        self.create_logger()

        # 记录最新tick
        self.tick_dict = {}

        # 每个算法引擎，对应的交易网关，区分mongodb中的记录
        self.gateway_name = globalSetting.get('gateway_name', 'Gateway')

    # ----------------------------------------------------------------------
    def register_event(self):
        """注册事件监听"""
        self.event_engine.register(EVENT_TICK, self.processTickEvent)
        self.event_engine.register(EVENT_TIMER, self.processTimerEvent)
        self.event_engine.register(EVENT_ORDER, self.processOrderEvent)
        self.event_engine.register(EVENT_TRADE, self.processTradeEvent)
        self.event_engine.register(EVENT_POSITION, self.processPositionEvent)

    # ----------------------------------------------------------------------
    def stop(self):
        """停止"""
        if self.rpcServer:
            self.rpcServer.stop()

    # ----------------------------------------------------------------------
    def processTickEvent(self, event):
        """行情事件"""
        tick = event.dict_['data']

        self.tick_dict.update({tick.vtSymbol: copy.copy(tick)})
        l = self.symbol_algo_dict.get(tick.vtSymbol, None)
        if l:
            for algo in list(l):
                if algo:
                    algo.updateTick(tick)

    # ----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """委托事件"""
        order = event.dict_['data']

        algo = self.order_algo_dict.get(order.vtOrderID, None)
        if algo:
            algo.updateOrder(order)

    # ----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """成交事件"""
        trade = event.dict_['data']

        algo = self.order_algo_dict.get(trade.vtOrderID, None)
        if algo:
            algo.updateTrade(trade)

        # 更新持仓缓存数据
        if trade.vtSymbol in self.symbol_algo_dict.keys():
            posBuffer = self.posBufferDict.get(trade.vtSymbol, None)
            if not posBuffer:
                posBuffer = PositionBuffer()
                posBuffer.vtSymbol = trade.vtSymbol
                self.posBufferDict[trade.vtSymbol] = posBuffer
            posBuffer.updateTradeData(trade)

    # ----------------------------------------------------------------------
    def processPositionEvent(self, event):
        """处理持仓推送"""
        pos = event.dict_['data']

        # 更新持仓缓存数据
        if True:  # pos.vtSymbol in self.tickStrategyDict:
            posBuffer = self.posBufferDict.get(pos.vtSymbol, None)
            if not posBuffer:
                posBuffer = PositionBuffer()
                posBuffer.vtSymbol = pos.vtSymbol
                self.posBufferDict[pos.vtSymbol] = posBuffer
            posBuffer.updatePositionData(pos)

    # ----------------------------------------------------------------------
    def processTimerEvent(self, event):
        """定时事件"""
        for algo_name in list(self.algo_dict.keys()):
            algo = self.algo_dict.get(algo_name, None)

            if algo is None:
                continue

            if getattr(algo, 'active') is False:
                try:
                    self.writeLog(u'processTimerEvent 发现{} 停止,移除策略.'.format(algo_name))
                    self.stopAlgo(algo_name)
                    continue
                except Exception as ex:
                    self.writeError(u'processTimerEvent:stop Algo{} exception:{}'.format(algo_name,str(ex)))
            algo.updateTimer()

        self.sync_db_active_status()

    # ----------------------------------------------------------------------
    def addAlgo(self, algoSetting):
        """新增算法"""
        templateName = algoSetting['templateName']
        algoClass = ALGO_DICT[templateName]
        algo = algoClass.new(self, algoSetting)

        self.algo_dict[algo.algoName] = algo

        return algo.algoName

    # ----------------------------------------------------------------------
    def stopAlgo(self, algoName):
        """停止算法"""
        if algoName in self.algo_dict:
            self.writeLog(u'停止算法:{}'.format(algoName))
            try:
                # 触发策略内部的停止处理
                self.algo_dict[algoName].stop()
                self.putVarEvent(self.algo_dict[algoName],{'active':False, 'stop_time': datetime.now().strftime('%Y-%m-%d %H:%M:%S')})
                del self.algo_dict[algoName]
            except Exception as ex:
                self.writeError(u'stopAlgo:stop Algo{} exception:{}'.format(algoName, str(ex)))

    # ----------------------------------------------------------------------
    def stopAll(self):
        """全部停止"""
        l = self.algo_dict.keys()
        self.writeLog(u'全部停止')
        for algoName in list(l):
            self.stopAlgo(algoName)

    # ----------------------------------------------------------------------
    def subscribe(self, algo, vtSymbol):
        """"""
        contract = self.main_engine.getContract(vtSymbol)
        if not contract:
            self.writeLog(u'%s订阅行情失败，找不到合约%s' %(algo.algoName, vtSymbol))
            return

        # 如果vtSymbol已存在于字典，说明已经订阅过
        if vtSymbol in self.symbol_algo_dict:
            s = self.symbol_algo_dict[vtSymbol]
            s.add(algo)
            return
        # 否则需要添加到字典中并执行订阅
        else:
            s = set()
            self.symbol_algo_dict[vtSymbol] = s
            s.add(algo)

            self.writeLog(u'订阅{}行情数据'.format(vtSymbol))
            req = VtSubscribeReq()
            req.symbol = contract.symbol
            req.exchange = contract.exchange
            self.main_engine.subscribe(req, contract.gatewayName)

    # ----------------------------------------------------------------------
    def sendOrder(self, algo, vtSymbol, direction, price, volume,
                  priceType=None, offset=None):
        """发单"""
        contract = self.main_engine.getContract(vtSymbol)
        if not contract:
            self.writeError(u'{}委托下单失败，找不到合约：{},发送{},{},委托:{},v{}失败'.format(
            algo.algoName, vtSymbol, direction, offset, price, volume))
            return ''

        req = VtOrderReq()
        req.vtSymbol = vtSymbol
        req.symbol = contract.symbol
        req.exchange = contract.exchange
        req.direction = direction
        req.offset = OFFSET_CLOSETODAY
        req.price = price
        req.volume = roundToVolumeTick(volumeTick=contract.volumeTick, volume=volume)  # 数量 volume

        if priceType:
            req.priceType = priceType
        else:
            req.priceType = PRICETYPE_LIMITPRICE

        if offset:
            req.offset = offset
            if offset == OFFSET_CLOSE:
                # 只有上期所才要考虑平今平昨
                if contract.exchange in [EXCHANGE_SHFE,EXCHANGE_INE]:
                    # 获取持仓缓存数据
                    posBuffer = self.posBufferDict.get(vtSymbol, None)

                    if direction == DIRECTION_SHORT:
                        # 如果获取持仓缓存失败，则默认平昨
                        if not posBuffer:
                            self.writeLog(u'获取持仓缓存失败，则默认平昨')
                            req.offset = OFFSET_CLOSE

                        # modified by IncenseLee 2016/11/08，改为优先平昨仓
                        elif posBuffer.longYd:
                            self.writeLog(u'{}优先平昨，昨多仓:{}，平仓数:{}'.format(vtSymbol, posBuffer.longYd, volume))
                            req.offset = OFFSET_CLOSE
                        else:
                            self.writeLog(u'{}平今,今多仓:{},{}'.format(vtSymbol, posBuffer.longToday, volume))
                            req.offset = OFFSET_CLOSETODAY

                    elif direction == DIRECTION_LONG:
                        # 如果获取持仓缓存失败，则默认平昨
                        if not posBuffer:
                            self.writeLog(u'获取持仓缓存失败，则默认平昨')
                            req.offset = OFFSET_CLOSE

                        # modified by IncenseLee 2016/11/08，改为优先平昨仓
                        elif posBuffer.shortYd:
                            self.writeLog(u'{}优先平昨,昨空仓:{},平仓数:{}'.format(vtSymbol, posBuffer.shortYd, volume))
                            req.offset = OFFSET_CLOSE
                        else:
                            self.writeLog(u'{}平今,今空仓:{},平仓数:{}'.format(vtSymbol, posBuffer.shortToday, volume))
                            req.offset = OFFSET_CLOSETODAY

        else:
            req.offset = OFFSET_OPEN

        vtOrderID = self.main_engine.sendOrder(req, contract.gatewayName)
        if vtOrderID is None or len(vtOrderID) == 0:
            self.writeError(u'{}发送委托失败，{} {} {} {}'.format(algo.algoName, vtSymbol, req.offset,
                                                                req.direction, volume, price))
            return ''

        self.order_algo_dict[vtOrderID] = algo
        self.writeError(u'{}发送委托，{} {} {} {}'.format(algo.algoName, vtSymbol, req.offset,
                                                        req.direction, volume, price))

        return vtOrderID

    # ----------------------------------------------------------------------
    def buy(self, algo, vtSymbol, price, volume, priceType=None, offset=None):
        """买入"""
        if offset is None:
            offset = OFFSET_OPEN
        return self.sendOrder(algo, vtSymbol, DIRECTION_LONG, price, volume, priceType, offset)

    # ----------------------------------------------------------------------
    def sell(self, algo, vtSymbol, price, volume, priceType=None, offset=None):
        """卖出"""
        if offset is None:
            offset = OFFSET_CLOSE
        return self.sendOrder(algo, vtSymbol, DIRECTION_SHORT, price, volume, priceType, offset)

    # ----------------------------------------------------------------------
    def cancelOrder(self, algo, vtOrderID):
        """撤单"""
        order = self.main_engine.getOrder(vtOrderID)
        if not order:
            self.writeLog(u'%s委托撤单失败，找不到委托：%s' %(algo.algoName, vtOrderID))
            return

        req = VtCancelOrderReq()
        req.symbol = order.symbol
        req.exchange = order.exchange
        req.orderID = order.orderID
        req.frontID = order.frontID
        req.sessionID = order.sessionID
        self.main_engine.cancelOrder(req, order.gatewayName)

    def create_logger(self, strategy_name=None):
        """
        创建日志记录
        :return:
        """
        currentFolder = os.path.abspath(os.path.join(os.getcwd(), 'logs'))
        if os.path.isdir(currentFolder):
            # 如果工作目录下，存在data子目录，就使用data子目录
            path = currentFolder
        else:
            # 否则，使用缺省保存目录 vnpy/trader/app/ctaStrategy/data
            path = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', 'logs'))

        if strategy_name is None:
            filename = os.path.abspath(os.path.join(path, 'AlgoEngine'))

            print(u'create logger:{}'.format(filename))
            self.logger = setup_logger(filename=filename, name='AlgoEngine', debug=True)
        else:
            filename = os.path.abspath(os.path.join(path, str(strategy_name)))
            print(u'create logger:{}'.format(filename))
            self.strategy_loggers[strategy_name] = setup_logger(filename=filename, name=str(strategy_name), debug=True)

    # ----------------------------------------------------------------------
    def writeLog(self, content, algo=None):
        """输出日志"""
        log = VtLogData()
        log.logContent = content

        if algo:
            log.gatewayName = algo.algoName

        event = Event(EVENT_ALGO_LOG)
        event.dict_['data'] = log
        self.event_engine.put(event)
        if self.logger:
            self.logger.info(content)

    def writeError(self,content,algo=None):
        """
        输出错误日志
        :param content:
        :param algo:
        :return:
        """
        log = VtLogData()
        log.logContent = content

        if algo:
            log.gatewayName = algo.algoName

        event = Event(EVENT_ALGO_LOG)
        event.dict_['data'] = log
        self.event_engine.put(event)
        if self.logger:
            self.logger.error(content)

        if algo is not None:
            if algo.algoName in self.strategy_loggers:
                self.strategy_loggers[algo.algoName].error(content)
            else:
                self.create_logger(strategy_name=algo.algoName)
                try:
                    self.strategy_loggers[algo.algoName].error(content)
                except Exception as ex:
                    pass

        self.main_engine.writeError(content)

    # ----------------------------------------------------------------------
    def putVarEvent(self, algo, d):
        """更新变量"""
        try:
            algoName = algo.algoName

            d['algo_name'] = algoName
            event = Event(EVENT_ALGO_VAR)
            event.dict_['data'] = d
            self.event_engine.put(event)

            # RPC推送
            if self.rpcServer:
                self.rpcServer.publish('AlgoTrading', event)

            # 若不使用mongodb，返回
            if not self.use_mongodb:
                return

            # 保存数据到数据库
            history = self.history_dict.setdefault(algoName, {})
            history['algo_name'] = algoName
            history['gateway_name'] = self.gateway_name
            d.pop('algoName', None)
            var = history.get('var', {})
            var.update(d)
            history.update({'var': var})
            history.update({'progress': getattr(algo, 'progress', 0)})
            history.update({'status': getattr(algo, 'status', '')})
            history.update({'error_msg': getattr(algo, 'error_msg', '')})
            history.update({'active': d.get('active', False)})
            history.update(({'buy_volume': getattr(algo, 'buy_volume')}))
            history.update(({'sell_volume': getattr(algo, 'sell_volume')}))
            history.update(({'buy_price': getattr(algo, 'buy_price')}))
            history.update(({'sell_price': getattr(algo, 'sell_price')}))
            if 'stop_time' in d and d.get('active') == False:
                history.update({'stop_time': d.get('stop_time')})

            flt = {'algoName': algoName, 'gateway_name':self.gateway_name}
            self.main_engine.dbUpdate(ALGOTRADING_DB_NAME,
                                      ALGO_HISTORY_COL_NAME,
                                      history,
                                      flt,
                                      True)
        except Exception as ex:
            self.writeError(u'putVarEvent Exception:{}'.format(str(ex)))
            self.writeError(traceback.format_exc())
    # ----------------------------------------------------------------------
    def putParamEvent(self, algo, d):
        """更新参数事件"""
        try:
            algoName = algo.algoName

            d['algo_name'] = algoName
            event = Event(EVENT_ALGO_PARAM)
            event.dict_['data'] = d
            self.event_engine.put(event)

            # RPC推送
            if self.rpcServer:
                self.rpcServer.publish('AlgoTrading', event)

            # 若不使用mongodb，返回
            if not self.use_mongodb:
                return

            # 保存数据到数据库
            history = self.history_dict.setdefault(algoName, {})
            history.update({'task_id': getattr(algo, 'task_id', 1)})
            history.update({'plan_name': getattr(algo, 'plan_name','')})
            history.update({'plan_id': getattr(algo, 'plan_id', '')})
            history.update({'plan_start_time': getattr(algo, 'plan_start_time', '')})
            history.update({'plan_stop_time': getattr(algo, 'plan_stop_time', '')})
            history.update({'start_time': getattr(algo, 'start_time', '')})
            history.update(({'plan_buy_volume': getattr(algo, 'plan_buy_volume')}))
            history.update(({'plan_sell_volume': getattr(algo, 'plan_sell_volume')}))
            history.update({'vtSymbol': getattr(algo, 'vtSymbol')})

            history['algo_name'] = algoName
            history['gateway_name'] = self.gateway_name
            d.pop('algoName', None)
            param = history.get('param',{})
            param.update(d)
            history.update({'param':param})

            self.main_engine.dbUpdate(ALGOTRADING_DB_NAME,
                                      ALGO_HISTORY_COL_NAME,
                                      history,
                                      {'algoName': algoName, 'gateway_name': self.gateway_name},
                                      True)

        except Exception as ex:
            self.writeError(u'putParamEvent Exception:{}'.format(str(ex)))
            self.writeError(traceback.format_exc())
    # ----------------------------------------------------------------------
    def getTick(self, algo, vtSymbol):
        """查询行情"""
        tick = self.tick_dict.get(vtSymbol,None)
        if not tick:
            self.writeLog(u'%s查询行情失败，找不到报价：%s' %(algo.algoName, vtSymbol))
            return

        return tick

    # ----------------------------------------------------------------------
    def getContract(self, algo, vtSymbol):
        """查询合约"""
        contract = self.main_engine.getContract(vtSymbol)
        if not contract:
            self.writeLog(u'{}查询合约失败，找不到报价：{}'.format(algo.algoName, vtSymbol))
            return  None

        return contract
        # ----------------------------------------------------------------------

    def getAccountInfo(self):
        """获取账号的实时权益、可用资金、仓位比例
        Added by Incenselee
        暂不支持多接口同时运行哦
        """
        return self.main_engine.getAccountInfo()

    def getSize(self, vtSymbol):
        """
        查询合约的大小
        :param vtSymbol:
        :return:
        """
        c = self.main_engine.getContract(vtSymbol)
        if c is None:
            self.writeError(u'getSize:查询不到{}合约信息'.format(vtSymbol))
            return 10
        else:
            return c.size

    def getMarginRate(self, vtSymbol):
        """
        提供给策略查询品种的保证金比率
        :param vtSymbol:
        :return:
        """
        c = self.main_engine.getContract(vtSymbol)
        if c is None:
            self.writeError(u'getMarginRate:查询不到{}合约信息'.format(vtSymbol))
            return 0.1
        else:
            # 返回空头/多头保证金费率的最大值
            if c.longMarginRatio > EMPTY_FLOAT and c.shortMarginRatio > EMPTY_FLOAT:
                return max(c.longMarginRatio, c.shortMarginRatio)
            else:
                self.writeError(u'合约{}的多头保证金率:{},空头保证金率:{}'.format(vtSymbol, c.longMarginRatio, c.shortMarginRatio))
                return 0.1

    # ----------------------------------------------------------------------
    # 策略配置相关
    def saveAlgoSettingToFile(self):
        """保存策略配置"""
        try:
            with open(self.settingfilePath, 'w') as f:
                l = list(self.setting_dict.values())
                jsonL = json.dumps(l, indent=4)
                f.write(jsonL)
        except Exception as ex:
            self.writeError(u'保存算法配置异常:{},{}'.format(str(ex), traceback.format_exc()))

    def loadAlgoSettingFromFile(self):
        """
        读取策略配置文件，Algo_setting.json
        逐一推送事件
        :return:
        """
        if not os.path.isfile(self.settingfilePath):
            self.writeLog(u'算法配置文件不存在')
            return
        try:
            with open(self.settingfilePath, 'r', encoding='UTF-8') as f:
                l = json.load(f)
                for algoSetting in l:
                    setting_name = algoSetting['setting_name']
                    self.setting_dict[setting_name] = algoSetting
                    self.putSettingEvent(setting_name, algoSetting)

        except Exception as ex:
            self.writeError(u'加载算法配置异常:{},{}'.format(str(ex), traceback.format_exc()))

        self.writeLog(u'加载算法配置成功')

    # ----------------------------------------------------------------------
    def saveAlgoSetting(self, algoSetting):
        """保存算法配置"""
        setting_name = algoSetting['setting_name']
        self.setting_dict[setting_name] = algoSetting
        algoSetting.update({'gateway_name': self.gateway_name})

        self.main_engine.dbUpdate(ALGOTRADING_DB_NAME,
                                  ALGO_SETTING_COL_NAME,
                                  algoSetting,
                                  {'setting_name': setting_name, 'gateway_name': self.gateway_name},
                                  True)

        self.putSettingEvent(setting_name, algoSetting)

    # ----------------------------------------------------------------------
    def loadAlgoSetting(self):
        """加载算法配置"""
        if not self.use_mongodb:
            self.loadAlgoSettingFromFile()
            return

        l = self.main_engine.dbQuery(ALGOTRADING_DB_NAME,
                                     ALGO_SETTING_COL_NAME,
                                     {'gateway_name': self.gateway_name},
                                    'templateName')
        for algoSetting in l:
            setting_name = algoSetting['setting_name']
            self.setting_dict[setting_name] = algoSetting
            self.putSettingEvent(setting_name, algoSetting)

    # ----------------------------------------------------------------------
    def deleteAlgoSetting(self, algoSetting):
        """删除算法配置"""
        setting_name = algoSetting['setting_name']

        del self.setting_dict[setting_name]

        if not self.use_mongodb:
            self.saveAlgoSettingToFile()
        else:
            flt = {'setting_name': setting_name, 'gateway_name': self.gateway_name}
            self.main_engine.dbDelete(ALGOTRADING_DB_NAME,
                                      ALGO_SETTING_COL_NAME,
                                      flt)

        self.putSettingEvent(setting_name, {})

    # ----------------------------------------------------------------------
    def putSettingEvent(self, setting_name, algoSetting):
        """发出算法配置更新事件"""
        algoSetting['setting_name'] = setting_name

        event = Event(EVENT_ALGO_SETTING)
        event.dict_['data'] = algoSetting
        self.event_engine.put(event)

    #----------------------------------------------------------------------
    def startRpc(self, repPort, pubPort):
        """启动RPC服务"""
        if self.rpcServer:
            return

        self.rpcServer = AlgoRpcServer(self, repPort, pubPort)
        self.rpcServer.start()
        self.writeLog(u'算法交易RPC服务启动成功，REP端口:%s，PUB端口:%s' %(repPort, pubPort))

    def sync_db_active_status(self):
        """
        获取数据库中所有当前引擎的active清单，与当前运行的清单比较，如果不在当前运行清单中，更新其状态为stop
        :return:
        """
        # 全删除
        flt = {'gateway_name': self.gateway_name}
        self.main_engine.dbDelete(ALGOTRADING_DB_NAME,
                                  ALGO_RUNNING_COL_NAME,
                                  flt)

        running_algos = []
        for algo_name in list(self.algo_dict.keys()):
            algo = self.algo_dict.get(algo_name, None)
            if algo is None:
                continue

            d = {
                 'gateway_name': self.gateway_name,
                 'plan_name': getattr(algo, 'plan_name', ''),
                 'plan_id': getattr(algo, 'plan_id', ''),
                 'algo_name': algo_name,
                 'status': getattr(algo, 'status', 'active'),
                 'progress': getattr(algo, 'progress', 0),
                 'plan_start_time': getattr(algo, 'plan_start_time', ''),
                 'plan_stop_time': getattr(algo, 'plan_stop_time', ''),
                 'start_time': getattr(algo, 'start_time', '')
              }
            running_algos.append(d)

        if len(running_algos) > 0:
            # 重新插入到数据库
            self.main_engine.dbInsertMany(dbName=ALGOTRADING_DB_NAME,
                                          collectionName=ALGO_RUNNING_COL_NAME,
                                          data_list=running_algos)

########################################################################
class AlgoRpcServer(RpcServer):
    """算法交易RPC服务器"""

    # ----------------------------------------------------------------------
    def __init__(self, engine, repPort, pubPort):
        """Constructor"""
        self.engine = engine
        repAddress = 'tcp://*:%s' %repPort
        pubAddress = 'tcp://*:%s' %pubPort

        super(AlgoRpcServer, self).__init__(repAddress, pubAddress)

        self.register(self.engine.addAlgo)
        self.register(self.engine.stopAlgo)
        self.register(self.engine.stopAll)

