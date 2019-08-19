# encoding: UTF-8

"""
ctp的gateway接入

1、增加通达信行情（指数行情）的订阅
2、增加支持Bar行情的订阅
3、增加支持自定义套利合约的订阅
"""

import os,sys
import json
import redis

# 加载经booster编译转换的SO API库
from vnpy.api.ctp.vnctpmd import MdApi
from vnpy.api.ctp.vnctptd import TdApi

from vnpy.trader.vtConstant import  *
from vnpy.trader.vtGateway import *
from vnpy.trader.gateway.ctpGateway.language import text
from vnpy.trader.gateway.ctpGateway.ctpDataType import *
from vnpy.trader.vtFunction import getJsonPath,getShortSymbol,roundToPriceTick
from vnpy.trader.app.ctaStrategy.ctaBase import MARKET_DAY_ONLY,NIGHT_MARKET_SQ1,NIGHT_MARKET_SQ2,NIGHT_MARKET_SQ3,NIGHT_MARKET_ZZ,NIGHT_MARKET_DL

from datetime import datetime,timedelta

# 通达信行情相关
from threading import Thread
from time import sleep
from pytdx.exhq import TdxExHq_API
from queue import Queue, Empty
from multiprocessing.dummy import Pool
import traceback
import copy

# 以下为一些VT类型和CTP类型的映射字典
# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = defineDict["THOST_FTDC_OPT_LimitPrice"]
priceTypeMap[PRICETYPE_MARKETPRICE] = defineDict["THOST_FTDC_OPT_AnyPrice"]
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()}

# 方向类型映射
directionMap = {}
directionMap[DIRECTION_LONG] = defineDict['THOST_FTDC_D_Buy']
directionMap[DIRECTION_SHORT] = defineDict['THOST_FTDC_D_Sell']
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {}
offsetMap[OFFSET_OPEN] = defineDict['THOST_FTDC_OF_Open']
offsetMap[OFFSET_CLOSE] = defineDict['THOST_FTDC_OF_Close']
offsetMap[OFFSET_CLOSETODAY] = defineDict['THOST_FTDC_OF_CloseToday']
offsetMap[OFFSET_CLOSEYESTERDAY] = defineDict['THOST_FTDC_OF_CloseYesterday']
offsetMapReverse = {v:k for k,v in offsetMap.items()}

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_CFFEX] = 'CFFEX'
exchangeMap[EXCHANGE_SHFE] = 'SHFE'
exchangeMap[EXCHANGE_CZCE] = 'CZCE'
exchangeMap[EXCHANGE_DCE] = 'DCE'
exchangeMap[EXCHANGE_SSE] = 'SSE'
exchangeMap[EXCHANGE_SZSE] = 'SZSE'
exchangeMap[EXCHANGE_INE] = 'INE'
exchangeMap[EXCHANGE_UNKNOWN] = ''
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 持仓类型映射
posiDirectionMap = {}
posiDirectionMap[DIRECTION_NET] = defineDict["THOST_FTDC_PD_Net"]
posiDirectionMap[DIRECTION_LONG] = defineDict["THOST_FTDC_PD_Long"]
posiDirectionMap[DIRECTION_SHORT] = defineDict["THOST_FTDC_PD_Short"]
posiDirectionMapReverse = {v:k for k,v in posiDirectionMap.items()}

# 产品类型映射
productClassMap = {}
productClassMap[PRODUCT_FUTURES] = defineDict["THOST_FTDC_PC_Futures"]
productClassMap[PRODUCT_OPTION] = defineDict["THOST_FTDC_PC_Options"]
productClassMap[PRODUCT_COMBINATION] = defineDict["THOST_FTDC_PC_Combination"]
productClassMapReverse = {v:k for k,v in productClassMap.items()}
productClassMapReverse[defineDict["THOST_FTDC_PC_ETFOption"]] = PRODUCT_OPTION
productClassMapReverse[defineDict["THOST_FTDC_PC_Stock"]] = PRODUCT_EQUITY

# 委托状态映射
statusMap = {}
statusMap[STATUS_ALLTRADED] = defineDict["THOST_FTDC_OST_AllTraded"]
statusMap[STATUS_PARTTRADED] = defineDict["THOST_FTDC_OST_PartTradedQueueing"]
statusMap[STATUS_NOTTRADED] = defineDict["THOST_FTDC_OST_NoTradeQueueing"]
statusMap[STATUS_CANCELLED] = defineDict["THOST_FTDC_OST_Canceled"]
statusMapReverse = {v:k for k,v in statusMap.items()}

# 全局字典, key:symbol, value:exchange
symbolExchangeDict = {}

# 夜盘交易时间段分隔判断
NIGHT_TRADING = datetime(1900, 1, 1, 20).time()

########################################################################
class CtpGateway(VtGateway):
    """CTP接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='CTP'):
        """Constructor"""
        super(CtpGateway, self).__init__(eventEngine, gatewayName)

        self.mdApi = None     # 行情API
        self.tdApi = None     # 交易API
        self.tdxApi = None    # 通达信指数行情API
        self.redisApi = None  # redis行情API

        self.mdConnected = False        # 行情API连接状态，登录完成后为True
        self.tdConnected = False        # 交易API连接状态
        self.tdxConnected = False       # 通达信指数行情API得连接状态
        self.redisConnected = False     # redis行情API的连接状态

        self.qryEnabled = False         # 是否要启动循环查询

        self.subscribedSymbols = set()  # 已订阅合约代码
        self.requireAuthentication = False

        self.debug_tick = False
        self.debug = False

        self.tdx_pool_count = 2         # 通达信连接池内连接数

        self.combiner_conf_dict = {}    # 保存合成器配置
        # 自定义价差/加比的tick合成器
        self.combiners = {}
        self.tick_combiner_map = {}

        # 合约代码与合约名称映射
        self.symbol_name_map = {}
    # ----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
        fileName = self.gatewayName + '_connect.json'
        filePath = getJsonPath(fileName, __file__)

        if self.mdApi is None:
            self.writeLog(u'行情接口未实例化，创建实例')
            self.mdApi = CtpMdApi(self)     # 行情API
        else:
            self.writeLog(u'行情接口已实例化')

        if self.tdApi is None:
            self.writeLog(u'交易接口未实例化，创建实例')
            self.tdApi = CtpTdApi(self)     # 交易API
        else:
            self.writeLog(u'交易接口已实例化')

        setting = None
        try:
            with open(filePath,'r') as f:
                # 解析json文件
                setting = json.load(f)
        except IOError:
            self.writeError('{} {}'.format(filePath,text.LOADING_ERROR))
            return

        try:
            userID = str(setting['userID'])
            password = str(setting['password'])
            brokerID = str(setting['brokerID'])
            tdAddress = str(setting['tdAddress'])
            mdAddress = str(setting['mdAddress'])

            self.debug_tick = setting.get('debug_tick',False)
            self.debug = setting.get('debug',False)

            # 如果json文件提供了验证码
            if 'authCode' in setting:
                authCode = str(setting['authCode'])
                appID = str(setting['appID'])
                userProductInfo = setting.get('userProductInfo',"")
                self.tdApi.requireAuthentication = True
                self.writeLog(u'使用授权码验证')
            else:
                authCode = None
                userProductInfo = None
                appID = EMPTY_STRING

            # 获取redis行情配置
            redis_conf = setting.get('redis', None)
            if redis_conf is not None and isinstance(redis_conf, dict):
                if self.redisApi is None:
                    self.writeLog(u'RedisApi接口未实例化，创建实例')
                    self.redisApi = RedisMdApi(self)  # Redis行情API
                else:
                    self.writeLog(u'Redis行情接口已实例化')

                ip_list = redis_conf.get('ip_list', None)
                if ip_list is not None and len(ip_list) > 0:
                    self.writeLog(u'使用配置文件的redis服务器清单:{}'.format(ip_list))
                    self.redisApi.ip_list = copy.copy(ip_list)

            # 如果没有初始化restApi，就初始化tdxApi
            if self.redisApi is None and self.tdxApi is None:
                self.writeLog(u'通达信接口未实例化，创建实例')
                self.tdxApi = TdxMdApi(self)  # 通达信行情API

            # 获取tdx配置
            tdx_conf = setting.get('tdx',None)
            if tdx_conf is not None and isinstance(tdx_conf,dict):
                if self.tdxApi is None:
                    self.writeLog(u'通达信接口未实例化，创建实例')
                    self.tdxApi = TdxMdApi(self)  # 通达信行情API
                ip_list = tdx_conf.get('ip_list',None)
                if ip_list is not None and len(ip_list)>0:
                    self.writeLog(u'使用配置文件的tdx服务器清单:{}'.format(ip_list))
                    self.tdxApi.ip_list = copy.copy(ip_list)

                # 获取通达信得缺省连接池数量
                self.tdx_pool_count = tdx_conf.get('pool_count', self.tdx_pool_count)

            # 获取自定义价差/价比合约的配置
            try:
                from vnpy.trader.vtEngine import Custom_Contract
                c = Custom_Contract()
                self.combiner_conf_dict = c.get_config()
                if len(self.combiner_conf_dict)>0:
                    self.writeLog(u'加载的自定义价差/价比配置:{}'.format(self.combiner_conf_dict))
            except Exception as ex:
                pass
        except KeyError:
            self.writeLog(text.CONFIG_KEY_MISSING)
            return

        # 创建行情和交易接口对象
        self.writeLog(u'连接行情服务器')
        self.mdApi.connect(userID, password, brokerID, mdAddress)
        self.writeLog(u'连接交易服务器')
        self.tdApi.connect(userID, password, brokerID, tdAddress, authCode, userProductInfo,appID=appID)

        self.setQryEnabled(True)
        # 初始化并启动查询
        self.initQuery()

        for req in list(self.subscribedSymbols):
            # 指数合约，从tdx行情订阅
            if req.symbol[-2:] in ['99']:
                req.symbol = req.symbol.upper()
                if self.tdxApi is not None:
                    self.writeLog(u'有指数订阅，连接通达信行情服务器')
                    self.tdxApi.connect(self.tdx_pool_count)
                    self.tdxApi.subscribe(req)
                elif self.redisApi is not None:
                    self.writeLog(u'有指数订阅，连接Redis行情服务器')
                    self.redisApi.connect()
                    self.redisApi.subscribe(req)
            else:
                self.mdApi.subscribe(req)

    def add_spread_conf(self, conf):
        """添加价差行情配置"""
        self.writeLog(u'添加价差行情配置:{}'.format(conf))

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        try:
            if self.mdApi is not None:

                # 如果是自定义的套利合约符号
                if subscribeReq.symbol in self.combiner_conf_dict:
                    self.writeLog(u'订阅自定义套利合约:{}'.format(subscribeReq.symbol))
                    # 创建合成器
                    if subscribeReq.symbol not in self.combiners:
                        setting = self.combiner_conf_dict.get(subscribeReq.symbol)
                        setting.update({"vtSymbol":subscribeReq.symbol})
                        combiner = TickCombiner(self, setting)
                        # 更新合成器
                        self.writeLog(u'添加{}与合成器映射'.format(subscribeReq.symbol))
                        self.combiners.update({setting.get('vtSymbol'): combiner})

                        # 增加映射（ leg1 对应的合成器列表映射)
                        leg1_symbol = setting.get('leg1_symbol')
                        combiner_list = self.tick_combiner_map.get(leg1_symbol, [])
                        if combiner not in combiner_list:
                            self.writeLog(u'添加Leg1:{}与合成器得映射'.format(leg1_symbol))
                            combiner_list.append(combiner)
                        self.tick_combiner_map.update({leg1_symbol: combiner_list})

                        # 增加映射（ leg2 对应的合成器列表映射)
                        leg2_symbol = setting.get('leg2_symbol')
                        combiner_list = self.tick_combiner_map.get(leg2_symbol, [])
                        if combiner not in combiner_list:
                            self.writeLog(u'添加Leg2:{}与合成器得映射'.format(leg2_symbol))
                            combiner_list.append(combiner)
                        self.tick_combiner_map.update({leg2_symbol: combiner_list})

                        self.writeLog(u'订阅leg1:{}'.format(leg1_symbol))
                        leg1_req = VtSubscribeReq()
                        leg1_req.symbol = leg1_symbol
                        leg1_req.exchange = subscribeReq.exchange
                        self.subscribe(leg1_req)

                        self.writeLog(u'订阅leg2:{}'.format(leg2_symbol))
                        leg2_req = VtSubscribeReq()
                        leg2_req.symbol = leg2_symbol
                        leg2_req.exchange = subscribeReq.exchange
                        self.subscribe(leg2_req)

                        self.subscribedSymbols.add(subscribeReq)
                    else:
                        self.writeLog(u'{}合成器已经在存在'.format(subscribeReq.symbol))
                    return
                elif subscribeReq.symbol.endswith('SPD'):
                    self.writeError(u'自定义合约{}不在CTP设置中'.format(subscribeReq.symbol))

                # 指数合约，从tdx行情订阅
                if subscribeReq.symbol[-2:] in ['99']:
                    subscribeReq.symbol = subscribeReq.symbol.upper()
                    if self.tdxApi:
                        self.tdxApi.subscribe(subscribeReq)
                    elif self.redisApi:
                        self.redisApi.subscribe(subscribeReq)
                else:
                    self.mdApi.subscribe(subscribeReq)

            # Allow the strategies to start before the connection
            self.subscribedSymbols.add(subscribeReq)
        except Exception as ex:
            self.writeError(u'订阅合约异常:{},{}'.format(str(ex),traceback.format_exc()))

    # ----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        if self.tdApi is not None:
            return self.tdApi.sendOrder(orderReq)

    # ----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        if self.tdApi is not None:
            self.tdApi.cancelOrder(cancelOrderReq)

    # ----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        if self.tdApi is None:
            self.tdConnected = False
            return
        self.tdApi.qryAccount()

    # ----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        if self.tdApi is None:
            self.mdConnected = False
            return
        self.tdApi.qryPosition()

    def checkStatus(self):
        """查询md/td的状态"""
        if self.tdxApi is not None:
            self.tdxApi.checkStatus()

        if self.tdApi is None or self.mdApi is None:
            return False

        if not self.tdConnected or not self.mdConnected:
            return False

        return True
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        if self.mdApi is not None:
            self.writeLog(u'断开行情API')
            tmp1 = self.mdApi
            self.mdApi = None
            tmp1.close()
            self.mdConnected = False

        if self.tdApi is not None:
            self.writeLog(u'断开交易API')
            tmp2 = self.tdApi
            self.tdApi = None
            tmp2.close()
            self.tdConnected = False

        if self.tdxApi is not None:
            self.writeLog(u'断开通达信行情API')
            tmp1 = self.tdxApi
            self.tdxApi.connection_status = False
            self.tdxApi = None
            tmp1.close()
            self.tdxConnected = False

        self.writeLog(u'CTP Gateway 主动断开连接')

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

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.onLog(log)

    def onCustomerTick(self,tick):
        """推送自定义合约行情"""
        # 自定义合约行情

        for combiner in self.tick_combiner_map.get(tick.vtSymbol, []):
            tick = copy.copy(tick)
            combiner.onTick(tick)

########################################################################
class CtpMdApi(MdApi):
    """CTP行情API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(CtpMdApi, self).__init__()

        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.reqID = EMPTY_INT              # 操作请求编号

        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态

        self.subscribedSymbols = gateway.subscribedSymbols     # 已订阅合约代码

        self.userID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.brokerID = EMPTY_STRING        # 经纪商代码
        self.address = EMPTY_STRING         # 服务器地址

    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        self.connectionStatus = True

        self.writeLog(text.DATA_SERVER_CONNECTED)

        if not self.loginStatus:
            self.login()

    #----------------------------------------------------------------------
    def onFrontDisconnected(self, n):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.mdConnected = False

        self.writeLog(text.DATA_SERVER_DISCONNECTED)

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
        err.errorMsg = error['ErrorMsg']    #.decode('gbk')
        self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        if getattr(self.gateway,'debug',False):
            print('onRspUserLogin')

        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = True
            self.gateway.mdConnected = True
            self.writeLog(text.DATA_SERVER_LOGIN)
            # 重新订阅之前订阅的合约

            for subscribeReq in self.subscribedSymbols:
                self.subscribe(subscribeReq)

        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg']    #.decode('gbk')
            self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        if getattr(self.gateway,'debug',False):
            print('onRspUserLogout')
        # 如果登出成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = False
            self.gateway.mdConnected = False

            self.writeLog(text.DATA_SERVER_LOGOUT)

        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg']    #.decode('gbk')
            self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onRspSubMarketData(self, data, error, n, last):
        """订阅合约回报"""
        # 通常不在乎订阅错误，选择忽略

    #----------------------------------------------------------------------
    def onRspUnSubMarketData(self, data, error, n, last):
        """退订合约回报"""
        # 同上
        pass

    #----------------------------------------------------------------------
    def onRtnDepthMarketData(self, data):
        """行情推送"""
        # 忽略成交量为0的无效单合约tick数据
        #if not data['Volume'] and '&' not in data['InstrumentID']:
        #    self.writeLog(u'忽略成交量为0的无效单合约tick数据:')
        #    self.writeLog(data)
        #    return

        if not self.connectionStatus:
            self.connectionStatus = True

        if not self.gateway.mdConnected:
            self.gateway.mdConnected = True

        tick = VtTickData()
        tick.gatewayName = self.gatewayName

        tick.symbol = data['InstrumentID']
        tick.exchange = exchangeMapReverse.get(data['ExchangeID'], u'未知')
        tick.vtSymbol = tick.symbol #'.'.join([tick.symbol, EXCHANGE_UNKNOWN])

        tick.lastPrice = data['LastPrice']
        tick.volume = data['Volume']
        tick.openInterest = data['OpenInterest']
        #tick.time = '.'.join([data['UpdateTime'], str(data['UpdateMillisec']/100)])
        # =》 Python 3
        tick.time = '.'.join([data['UpdateTime'], str(data['UpdateMillisec'])])

        # 取当前时间
        dt = datetime.now()

        # 不处理开盘前的tick数据
        if dt.hour in [8,20] and dt.minute < 59:
            return
        if tick.exchange is EXCHANGE_CFFEX and dt.hour == 9 and dt.minute < 14:
            return

        # 日期，取系统时间的日期
        tick.date = dt.strftime('%Y-%m-%d')
        # 生成dateteime
        tick.datetime = datetime.strptime(tick.date + ' ' + tick.time, '%Y-%m-%d %H:%M:%S.%f')
        # 生成TradingDay

        # 正常日盘时间
        tick.tradingDay = tick.date

        # 修正夜盘的tradingDay
        if tick.datetime.hour >= 20:
            # 周一~周四晚上20点之后的tick，交易日属于第二天
            if tick.datetime.isoweekday() in [1,2,3,4]:
                trading_day = tick.datetime + timedelta(days=1)
                tick.tradingDay = trading_day.strftime('%Y-%m-%d')
            # 周五晚上20点之后的tick，交易日属于下周一
            elif tick.datetime.isoweekday() == 5:
                trading_day = tick.datetime + timedelta(days=3)
                tick.tradingDay = trading_day.strftime('%Y-%m-%d')
        elif tick.datetime.hour < 3:
            # 周六凌晨的tick，交易日属于下周一
            if tick.datetime.isoweekday() == 6:
                trading_day = tick.datetime + timedelta(days=2)
                tick.tradingDay = trading_day.strftime('%Y-%m-%d')

        tick.openPrice = data['OpenPrice']
        tick.highPrice = data['HighestPrice']
        tick.lowPrice = data['LowestPrice']
        tick.preClosePrice = data['PreClosePrice']

        tick.upperLimit = data['UpperLimitPrice']
        tick.lowerLimit = data['LowerLimitPrice']

        # CTP只有一档行情
        tick.bidPrice1 = data['BidPrice1']
        tick.bidVolume1 = data['BidVolume1']
        tick.askPrice1 = data['AskPrice1']
        tick.askVolume1 = data['AskVolume1']

        if data.get('BidPrice2',None) !=None:
            tick.bidPrice2 = data.get('BidPrice2')
        if data.get('BidPrice3', None) != None:
            tick.bidPrice3 = data.get('BidPrice3')
        if data.get('BidPrice4', None) != None:
            tick.bidPrice4 = data.get('BidPrice4')
        if data.get('BidPrice5', None) != None:
            tick.bidPrice5 = data.get('BidPrice5')

        if data.get('AskPrice2',None) !=None:
            tick.AskPrice2 = data.get('AskPrice2')
        if data.get('AskPrice3', None) != None:
            tick.AskPrice3 = data.get('AskPrice3')
        if data.get('AskPrice4', None) != None:
            tick.AskPrice4 = data.get('AskPrice4')
        if data.get('AskPrice5', None) != None:
            tick.AskPrice5 = data.get('AskPrice5')

        if data.get('BidVolume2',None) !=None:
            tick.bidVolume2 = data.get('BidVolume2')
        if data.get('BidVolume3', None) != None:
            tick.bidVolume3 = data.get('BidVolume3')
        if data.get('BidVolume4', None) != None:
            tick.bidVolume4 = data.get('BidVolume4')
        if data.get('BidVolume5', None) != None:
            tick.bidVolume5 = data.get('BidVolume5')

        if data.get('AskVolume2',None) !=None:
            tick.AskVolume2 = data.get('AskVolume2')
        if data.get('AskVolume3', None) != None:
            tick.AskVolume3 = data.get('AskVolume3')
        if data.get('AskVolume4', None) != None:
            tick.AskVolume4 = data.get('AskVolume4')
        if data.get('AskVolume5', None) != None:
            tick.AskVolume5 = data.get('AskVolume5')

        self.gateway.onTick(tick)

        self.gateway.onCustomerTick(tick)

    # ----------------------------------------------------------------------
    def onRspSubForQuoteRsp(self, data, error, n, last):
        """订阅期权询价"""
        pass

    #----------------------------------------------------------------------
    def onRspUnSubForQuoteRsp(self, data, error, n, last):
        """退订期权询价"""
        pass

    # ----------------------------------------------------------------------
    def onRtnForQuoteRsp(self, data):
        """期权询价推送"""
        pass

    # ----------------------------------------------------------------------
    def connect(self, userID, password, brokerID, address):
        """初始化连接"""

        self.userID = userID                # 账号
        self.password = password            # 密码
        self.brokerID = brokerID            # 经纪商代码
        self.address = address              # 服务器地址

        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            # 创建C++环境中的API对象，这里传入的参数是需要用来保存.con文件的文件夹路径
            path = os.getcwd() + '/temp/' + str(self.gatewayName) + '/'
            if not os.path.exists(path):
                os.makedirs(path)
            self.createFtdcMdApi(path)
            self.writeLog(u'注册行情服务器地址:{}'.format(self.address))
            # 注册服务器地址
            self.registerFront(self.address)

            # 初始化连接，成功会调用onFrontConnected
            self.init()

            self.login()

        # 若已经连接但尚未登录，则进行登录
        else:
            if not self.loginStatus:
                self.login()

    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅合约"""
        # 这里的设计是，如果尚未登录就调用了订阅方法
        # 则先保存订阅请求，登录完成后会自动订阅


        if self.connectionStatus and  not self.loginStatus:
            self.login()

        # 订阅传统合约
        self.subscribeMarketData(str(subscribeReq.symbol))
        self.writeLog(u'订阅合约:{0}'.format(str(subscribeReq.symbol)))
        self.subscribedSymbols.add(subscribeReq)

    # ----------------------------------------------------------------------
    def login(self):
        """登录"""

        # 如果填入了用户名密码等，则登录
        if self.userID and self.password and self.brokerID:
            self.writeLog(u'登入行情服务器')
            req = {}
            req['UserID'] = self.userID
            req['Password'] = self.password
            req['BrokerID'] = self.brokerID
            self.reqID += 1
            self.reqUserLogin(req, self.reqID)
        else:
            self.writeLog(u'未配置用户/密码,不登录行情服务器')

    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)


########################################################################
class CtpTdApi(TdApi):
    """CTP交易API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(CtpTdApi, self).__init__()

        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.reqID = EMPTY_INT              # 操作请求编号
        self.orderRef = EMPTY_INT           # 订单编号

        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        self.authStatus = False

        self.userID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.brokerID = EMPTY_STRING        # 经纪商代码
        self.address = EMPTY_STRING         # 服务器地址

        self.frontID = EMPTY_INT            # 前置机编号
        self.sessionID = EMPTY_INT          # 会话编号

        self.posDict = {}
        self.symbolExchangeDict = {}        # 保存合约代码和交易所的印射关系
        self.symbolSizeDict = {}            # 保存合约代码和合约大小的印射关系

        self.requireAuthentication = False

        self.tradingDay = None

    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        self.connectionStatus = True
        self.writeLog(text.TRADING_SERVER_CONNECTED)

        if self.requireAuthentication:
            self.authenticate()
        else:
            self.login()

    #----------------------------------------------------------------------
    def onFrontDisconnected(self, n):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.tdConnected = False

        self.writeLog(text.TRADING_SERVER_DISCONNECTED)

    #----------------------------------------------------------------------
    def onHeartBeatWarning(self, n):
        """"""

    #----------------------------------------------------------------------
    def onRspAuthenticate(self, data, error, n, last):
        """验证客户端回报"""
        if error['ErrorID'] == 0:
            self.authStatus = True
            self.writeLog(text.TRADING_SERVER_AUTHENTICATED)
            self.login()
        else:
            self.writeLog(u'授权码验证失败:{}'.format(error))

    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
            self.tradingDay = str(data['TradingDay'])
            self.frontID = str(data['FrontID'])
            self.sessionID = str(data['SessionID'])
            self.loginStatus = True
            self.gateway.tdConnected = True
            self.gateway.mdConnected = True
            self.writeLog(text.TRADING_SERVER_LOGIN)

            # 确认结算信息
            req = {}
            req['BrokerID'] = self.brokerID
            req['InvestorID'] = self.userID
            self.reqID += 1
            self.reqSettlementInfoConfirm(req, self.reqID)

            # 提交合约更新请求
            try:
                self.resentReqQryInstrument()
            except:
                pass

        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg']    #.decode('gbk')
            self.gateway.onError(err)

    def resentReqQryInstrument(self):
        # 查询合约代码
        self.reqID += 1
        self.reqQryInstrument({}, self.reqID)

    #----------------------------------------------------------------------
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        # 如果登出成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = False
            self.gateway.tdConnected = False

            self.writeLog(text.TRADING_SERVER_LOGOUT)

        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg']    #.decode('gbk')
            self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onRspUserPasswordUpdate(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspTradingAccountPasswordUpdate(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspOrderInsert(self, data, error, n, last):
        """发单返回（柜台）"""
        # 推送委托信息
        order = VtOrderData()
        order.accountID = self.userID
        order.vtAccountID = self.gatewayName + '.' + str(self.userID)
        order.gatewayName = self.gatewayName
        order.symbol = data['InstrumentID']
        order.exchange = exchangeMapReverse[data['ExchangeID']]
        order.vtSymbol = order.symbol
        order.vtSymbolName = self.gateway.symbol_name_map.get(order.symbol, order.vtSymbol)

        order.orderID = data['OrderRef']
        order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
        order.direction = directionMapReverse.get(data['Direction'], DIRECTION_UNKNOWN)
        order.offset = offsetMapReverse.get(data['CombOffsetFlag'], OFFSET_UNKNOWN)
        order.status = STATUS_REJECTED
        order.price = data['LimitPrice']
        order.totalVolume = data['VolumeTotalOriginal']
        self.gateway.onOrder(order)

        # 推送错误信息
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg']    #.decode('gbk')
        err.additionalInfo = u'onRspOrderInsert():{0},{1},{2},{3}'.\
            format(order.vtSymbol, order.orderID, order.direction , order.offset)
        self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onRspParkedOrderInsert(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspParkedOrderAction(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspOrderAction(self, data, error, n, last):
        """撤单错误（柜台）"""
        try:
            symbol = data['InstrumentID']
        except KeyError:
            symbol = u'KEYERROR'

        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg']    #.decode('gbk')
        err.additionalInfo = u'onRspOrderAction,{0}'.format(symbol)
        self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onRspQueryMaxOrderVolume(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspSettlementInfoConfirm(self, data, error, n, last):
        """确认结算信息回报"""
        self.writeLog(text.SETTLEMENT_INFO_CONFIRMED)

    #----------------------------------------------------------------------
    def onRspRemoveParkedOrder(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspRemoveParkedOrderAction(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspExecOrderInsert(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspExecOrderAction(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspForQuoteInsert(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQuoteInsert(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQuoteAction(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspLockInsert(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspCombActionInsert(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryOrder(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryTrade(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryInvestorPosition(self, data, error, n, last):
        """持仓查询回报"""

        if self.gateway.debug and data.get('InstrumentID') == 'pp1909':
            self.gateway.writeLog(u'data:\n{}'.format(self.gateway.printDict(data)))
            self.gateway.writeLog('n:{},last:{}'.format(n,last))

        if not data['InstrumentID']:
            return

        if not self.gateway.tdConnected:
            self.gateway.tdConnected = True

        try:
            # 获取持仓缓存对象
            posName = '.'.join([data['InstrumentID'], data['PosiDirection']])
            if posName in self.posDict:
                pos = self.posDict[posName]
            else:
                pos = VtPositionData()
                pos.accountID = self.userID
                pos.vtAccountID = self.gatewayName + '.' + str(self.userID)
                self.posDict[posName] = pos

                pos.gatewayName = self.gatewayName
                pos.symbol = data['InstrumentID']
                pos.vtSymbol = pos.symbol
                pos.vtSymbolName = self.gateway.symbol_name_map.get(pos.symbol, pos.vtSymbol)
                pos.direction = posiDirectionMapReverse.get(data['PosiDirection'], '')
                pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction, pos.gatewayName])

            exchange = self.symbolExchangeDict.get(pos.symbol, EXCHANGE_UNKNOWN)

            # 获取size
            size = self.symbolSizeDict.get(pos.symbol,10)

            # 针对上期所持仓的今昨分条返回（有昨仓、无今仓），读取昨仓数据
            if exchange in [EXCHANGE_SHFE, EXCHANGE_INE]:
                if data['YdPosition'] and not data['TodayPosition']:
                    pos.ydPosition = data['Position']
                    yd_position = data['YdPosition']
                else:
                    yd_position = 0

                # 前汇总，总成本
                pre_cost = pos.price * pos.position * size

                # 仓位累加汇总
                pos.position += data['Position']

                if pos.position > 0 and size > 0:
                    # 计算持仓均价
                    pos.price = (pre_cost + data['OpenCost']) / (pos.position * size)

                    # 上一交易日结算价
                    pre_settlement_price = data['PreSettlementPrice']

                    # 当前一笔的开仓均价
                    open_cost_price = (data['OpenCost'] / (data['Position'] * size)) if data['Position'] > 0 else pre_settlement_price

                    pre_profit = 0
                    # 上-交易日收益 = (上一交易日结算价 - 开仓价)* 昨仓持仓数量 * 杠杆
                    if pos.direction == DIRECTION_LONG:
                        pre_profit = (pre_settlement_price - open_cost_price) * (yd_position * size)
                    else:
                        pre_profit = (open_cost_price - pre_settlement_price) * (yd_position * size)

                    # 汇总收益：上一收益 + 上-交易日收益 + 当日持仓收益
                    pos.positionProfit = pos.positionProfit + pre_profit + data['PositionProfit']

                    if self.gateway.debug and pos.symbol == 'pp1909':
                        self.gateway.writeLog(
                            u'symbol:{} direction:{} pos:{} yd_pos:{}, price:{},open_cost:{},pre_set_price:{}, size:{},pre_profit:{},profit:{}'
                            .format(pos.symbol, pos.direction, pos.position, pos.ydPosition, pos.price, open_cost_price,
                                    pre_settlement_price, size, pre_profit, pos.positionProfit))

            # 否则基于总持仓和今持仓来计算昨仓数据
            else:
                pos.position = data['Position']
                pos.ydPosition = data['Position'] - data['TodayPosition']
                pos.price = data['OpenCost'] / (pos.position * size) if pos.position * size != 0 else data['PreSettlementPrice']
                if pos.position == 0:
                    pos.price = 0

                pos.positionProfit = (data['PositionCost'] - data['OpenCost']) if pos.direction is DIRECTION_LONG else (data['OpenCost'] - data['PositionCost'])
                pos.positionProfit += data['PositionProfit']

            # 读取冻结
            if pos.direction is DIRECTION_LONG:
                pos.frozen += data['LongFrozen']
            else:
                pos.frozen += data['ShortFrozen']

            # 查询回报结束
            if last:
                # 遍历推送
                for pos in list(self.posDict.values()):
                    self.gateway.onPosition(pos)

                # 清空缓存
                self.posDict.clear()
        except Exception as ex:
            self.gateway.writeError('onRspQryInvestorPosition exception:{}'.format(str(ex)))
            self.gateway.writeError('trace {}'.format(traceback.format_exc()))

    #----------------------------------------------------------------------
    def onRspQryTradingAccount(self, data, error, n, last):
        """资金账户查询回报"""

        self.gateway.mdConnected = True

        account = VtAccountData()
        account.gatewayName = self.gatewayName

        # 账户代码
        account.accountID = data['AccountID']
        account.vtAccountID = '.'.join([self.gatewayName, account.accountID])

        # 数值相关
        account.preBalance = data['PreBalance']
        account.available = data['Available']
        account.frozen = float(data['FrozenCash'])
        account.withdraw = float(data['WithdrawQuota'])
        account.commission = data['Commission']
        account.margin = data['CurrMargin']
        account.closeProfit = data['CloseProfit']
        account.positionProfit = data['PositionProfit']
        account.tradingDay = str(data['TradingDay'])
        if '-' not in account.tradingDay and len(account.tradingDay)== 8:
            account.tradingDay = account.tradingDay[0:4] + '-' + account.tradingDay[4:6] + '-' + account.tradingDay[6:8]
        # 这里的balance和快期中的账户不确定是否一样，需要测试
        account.balance = (data['PreBalance'] - data['PreCredit'] - data['PreMortgage'] +
                           data['Mortgage'] - data['Withdraw'] + data['Deposit'] +
                           data['CloseProfit'] + data['PositionProfit'] + data['CashIn'] -
                           data['Commission'])

        account.currency = u'人民币'
        # 推送
        self.gateway.onAccount(account)

    #----------------------------------------------------------------------
    def onRspQryInvestor(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryTradingCode(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryInstrumentMarginRate(self, data, error, n, last):
        """
        获取保证金率
        :param data:
        :param error:
        :param n:
        :param last:
        :return:
        """
        pass

    #----------------------------------------------------------------------
    def onRspQryInstrumentCommissionRate(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryExchange(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryProduct(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryInstrument(self, data, error, n, last):
        """合约查询回报"""

        self.gateway.mdConnected = True
        contract = VtContractData()
        contract.gatewayName = self.gatewayName

        contract.symbol = data['InstrumentID']
        contract.exchange = exchangeMapReverse[data['ExchangeID']]
        contract.vtSymbol = contract.symbol #'.'.join([contract.symbol, contract.exchange])
        contract.name = data['InstrumentName']  #.decode('GBK')

        self.gateway.symbol_name_map.update({contract.symbol:contract.name})

        # 合约数值
        contract.size = data['VolumeMultiple']
        contract.priceTick = data['PriceTick']
        contract.strikePrice = data['StrikePrice']
        contract.underlyingSymbol = data['UnderlyingInstrID']
        contract.longMarginRatio = data['LongMarginRatio']
        contract.shortMarginRatio = data['ShortMarginRatio']

        contract.productClass = productClassMapReverse.get(data['ProductClass'], PRODUCT_UNKNOWN)

        # 期权类型
        if data['OptionsType'] == '1':
            contract.optionType = OPTION_CALL
        elif data['OptionsType'] == '2':
            contract.optionType = OPTION_PUT

        # 缓存代码和交易所的印射关系
        self.symbolExchangeDict[contract.symbol] = contract.exchange
        self.symbolSizeDict[contract.symbol] = contract.size

        idx_contract = copy.copy(contract)

        # 推送
        self.gateway.onContract(contract)

        # 生成指数合约信息
        short_symbol= getShortSymbol(idx_contract.symbol).upper()    # 短合约名称
        # 只推送普通合约的指数
        if short_symbol!= idx_contract.symbol.upper() and len(short_symbol)<=2 and contract.optionType==EMPTY_UNICODE:
            idx_contract.symbol = '{}99'.format(short_symbol)
            idx_contract.vtSymbol = idx_contract.symbol
            idx_contract.name = u'{}指数'.format(short_symbol.upper())
            #self.writeLog(u'更新指数{}的合约信息,size:{}, longMarginRatio:{},shortMarginRatio{}'
            #              .format(idx_contract.vtSymbol,idx_contract.size, idx_contract.longMarginRatio,contract.shortMarginRatio))

            self.gateway.onContract(idx_contract)

        if last:
            self.writeLog(text.CONTRACT_DATA_RECEIVED)

    #----------------------------------------------------------------------
    def onRspQryDepthMarketData(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQrySettlementInfo(self, data, error, n, last):
        """查询结算信息回报"""
        pass
    #----------------------------------------------------------------------
    def onRspQryTransferBank(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryInvestorPositionDetail(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryNotice(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQrySettlementInfoConfirm(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryInvestorPositionCombineDetail(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryCFMMCTradingAccountKey(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryEWarrantOffset(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryInvestorProductGroupMargin(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryExchangeMarginRate(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryExchangeMarginRateAdjust(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryExchangeRate(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQrySecAgentACIDMap(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryProductExchRate(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryProductGroup(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryOptionInstrTradeCost(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryOptionInstrCommRate(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryExecOrder(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryForQuote(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryQuote(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryLock(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryLockPosition(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryInvestorLevel(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryExecFreeze(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryCombInstrumentGuard(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryCombAction(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryTransferSerial(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryAccountregister(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspError(self, error, n, last):
        """错误回报"""

        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = u'onRspError' + error['ErrorMsg']    #.decode('gbk')
        self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onRtnOrder(self, data):
        """报单回报"""
        # 更新最大报单编号
        newref = data['OrderRef']
        self.orderRef = max(self.orderRef, int(newref))

        # 创建报单数据对象
        order = VtOrderData()
        order.accountID = self.userID
        order.vtAccountID = self.gatewayName + '.' + str(self.userID)
        order.gatewayName = self.gatewayName

        order.accountID = self.userID
        order.vtAccountID = self.gatewayName + '.' + str(self.userID)

        # 保存代码和报单号
        order.symbol = data['InstrumentID']
        order.exchange = exchangeMapReverse[data['ExchangeID']]
        order.vtSymbol = order.symbol #'.'.join([order.symbol, order.exchange])
        order.vtSymbolName = self.gateway.symbol_name_map.get(order.symbol,order.vtSymbol)
        order.orderID = data['OrderRef']
        # CTP的报单号一致性维护需要基于frontID, sessionID, orderID三个字段
        # 但在本接口设计中，已经考虑了CTP的OrderRef的自增性，避免重复
        # 唯一可能出现OrderRef重复的情况是多处登录并在非常接近的时间内（几乎同时发单）
        # 考虑到VtTrader的应用场景，认为以上情况不会构成问题
        order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
        order.sysOrderID = data.get('OrderSysID',EMPTY_STRING)

        order.direction = directionMapReverse.get(data['Direction'], DIRECTION_UNKNOWN)
        order.offset = offsetMapReverse.get(data['CombOffsetFlag'], OFFSET_UNKNOWN)
        order.status = statusMapReverse.get(data['OrderStatus'], STATUS_UNKNOWN)

        # 价格、报单量等数值
        order.price = data['LimitPrice']
        order.totalVolume = data['VolumeTotalOriginal']
        order.tradedVolume = data['VolumeTraded']
        order.orderTime = data['InsertTime']
        order.updateTime = data['UpdateTime']
        order.cancelTime = data['CancelTime']
        order.frontID = data['FrontID']
        order.sessionID = data['SessionID']

        # 推送
        self.gateway.onOrder(order)

    #----------------------------------------------------------------------
    def onRtnTrade(self, data):
        """成交回报"""
        # 创建报单数据对象
        trade = VtTradeData()
        trade.accountID = self.userID
        trade.vtAccountID = self.gatewayName + '.' + str(self.userID)
        trade.gatewayName = self.gatewayName

        # 保存代码和报单号
        trade.symbol = data['InstrumentID']
        trade.exchange = exchangeMapReverse[data['ExchangeID']]
        trade.vtSymbol = trade.symbol #'.'.join([trade.symbol, trade.exchange])
        trade.vtSymbolName = self.gateway.symbol_name_map.get(trade.symbol, trade.vtSymbol)

        trade.tradeID = data['TradeID']
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])

        trade.orderID = data['OrderRef']
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])
        trade.sysOrderID = data.get('OrderSysID',EMPTY_STRING)
        # 方向
        trade.direction = directionMapReverse.get(data['Direction'], '')

        # 开平
        trade.offset = offsetMapReverse.get(data['OffsetFlag'], '')

        # 价格、报单量等数值
        trade.price = data['Price']
        trade.volume = data['Volume']
        trade.tradeTime = data['TradeTime']

        # 推送
        self.gateway.onTrade(trade)

    #----------------------------------------------------------------------
    def onErrRtnOrderInsert(self, data, error):
        """发单错误回报（交易所）"""
        # 推送委托信息
        order = VtOrderData()
        order.accountID = self.userID
        order.vtAccountID = self.gatewayName + '.' + str(self.userID)
        order.gatewayName = self.gatewayName
        order.symbol = data['InstrumentID']
        order.exchange = exchangeMapReverse[data['ExchangeID']]
        order.vtSymbol = order.symbol
        order.vtSymbolName = self.gateway.symbol_name_map.get(order.symbol, order.vtSymbol)
        order.orderID = data['OrderRef']
        order.vtOrderID = '.'.join([self.gatewayName, order.orderID])
        order.direction = directionMapReverse.get(data['Direction'], DIRECTION_UNKNOWN)
        order.offset = offsetMapReverse.get(data['CombOffsetFlag'], OFFSET_UNKNOWN)
        order.status = STATUS_REJECTED
        order.price = data['LimitPrice']
        order.totalVolume = data['VolumeTotalOriginal']
        self.gateway.onOrder(order)

        # 推送错误信息
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'] #.decode('gbk')
        err.additionalInfo = u'onErrRtnOrderInsert.{0},v:{1},ref:{2}:'\
            .format(order.vtSymbol , order.totalVolume, order.orderID)
        self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onErrRtnOrderAction(self, data, error):
        """撤单错误回报（交易所）"""

        symbol = data['InstrumentID']

        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg']    #.decode('gbk')
        err.additionalInfo =u'onErrRtnOrderAction.{0}'.format(symbol)
        self.gateway.onError(err)

    #----------------------------------------------------------------------
    def onRtnInstrumentStatus(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnTradingNotice(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnErrorConditionalOrder(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnExecOrder(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnExecOrderInsert(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnExecOrderAction(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnForQuoteInsert(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnQuote(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnQuoteInsert(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnQuoteAction(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnForQuoteRsp(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnCFMMCTradingAccountToken(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnLock(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnLockInsert(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnCombAction(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnCombActionInsert(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryContractBank(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryParkedOrder(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryParkedOrderAction(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryTradingNotice(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryBrokerTradingParams(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQryBrokerTradingAlgos(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQueryCFMMCTradingAccountToken(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnFromBankToFutureByBank(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnFromFutureToBankByBank(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnRepealFromBankToFutureByBank(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnRepealFromFutureToBankByBank(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnFromBankToFutureByFuture(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnFromFutureToBankByFuture(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnRepealFromBankToFutureByFutureManual(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnRepealFromFutureToBankByFutureManual(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnQueryBankBalanceByFuture(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnBankToFutureByFuture(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnFutureToBankByFuture(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnRepealBankToFutureByFutureManual(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnRepealFutureToBankByFutureManual(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onErrRtnQueryBankBalanceByFuture(self, data, error):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnRepealFromBankToFutureByFuture(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnRepealFromFutureToBankByFuture(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspFromBankToFutureByFuture(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspFromFutureToBankByFuture(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRspQueryBankAccountMoneyByFuture(self, data, error, n, last):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnOpenAccountByBank(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnCancelAccountByBank(self, data):
        """"""
        pass

    #----------------------------------------------------------------------
    def onRtnChangeAccountByBank(self, data):
        """"""
        pass

    # ----------------------------------------------------------------------
    def connect(self, userID, password, brokerID, address, authCode, userProductInfo, appID=EMPTY_STRING):
        """初始化连接"""
        self.userID = userID                # 账号
        self.password = password            # 密码
        self.brokerID = brokerID            # 经纪商代码
        self.address = address              # 服务器地址
        self.authCode = authCode            # 验证码
        self.appID = appID                  # 产品ID
        self.userProductInfo = userProductInfo  #产品信息

        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            # 创建C++环境中的API对象，这里传入的参数是需要用来保存.con文件的文件夹路径
            path = os.getcwd() + '/temp/' + str(self.gatewayName) + '/'
            if not os.path.exists(path):
                os.makedirs(path)
            self.createFtdcTraderApi(path)

            # 设置数据同步模式为推送从今日开始所有数据
            self.subscribePrivateTopic(0)
            self.subscribePublicTopic(0)

            # 注册服务器地址
            self.registerFront(self.address)

            # 初始化连接，成功会调用onFrontConnected
            self.init()

        # 若已经连接但尚未登录，则进行登录
        else:
            if self.requireAuthentication and not self.authStatus:
                self.authenticate()
            elif not self.loginStatus:
                self.login()

    # ----------------------------------------------------------------------
    def login(self):
        """登录服务器"""
        # 如果填入了用户名密码等，则登录
        self.writeLog(u'登录交易服务器')
        if self.userID and self.password and self.brokerID:
            req = {}
            req['UserID'] = self.userID
            req['Password'] = self.password
            req['BrokerID'] = self.brokerID
            self.reqID += 1
            self.reqUserLogin(req, self.reqID)

    # ----------------------------------------------------------------------
    def authenticate(self):
        """申请验证"""
        self.writeLog(u'申请授权码验证')
        if self.userID and self.brokerID and self.authCode:
            req = {}
            req['UserID'] = self.userID
            req['BrokerID'] = self.brokerID
            req['AuthCode'] = self.authCode
            if len(self.userProductInfo) > 0:
                req['UserProductInfo'] = self.userProductInfo
            req['AppID'] = self.appID
            self.reqID +=1
            self.writeLog(u'提交验证...')
            self.reqAuthenticate(req, self.reqID)

    # ----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户"""
        self.reqID += 1
        self.reqQryTradingAccount({}, self.reqID)

    # ----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.reqID += 1
        req = {}
        req['BrokerID'] = self.brokerID
        req['InvestorID'] = self.userID
        self.reqQryInvestorPosition(req, self.reqID)

    # ----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        self.reqID += 1
        self.orderRef += 1

        req = {}

        req['InstrumentID'] = orderReq.symbol
        req['LimitPrice'] = orderReq.price

        # 增加检查，ctp不支持float的volume下单
        if isinstance(orderReq.volume, float):
            req['VolumeTotalOriginal'] = int(orderReq.volume)
        else:
            req['VolumeTotalOriginal'] = orderReq.volume

        # 下面如果由于传入的类型本接口不支持，则会 返回空字符串
        req['OrderPriceType'] = priceTypeMap.get(orderReq.priceType, '')
        req['Direction'] = directionMap.get(orderReq.direction, '')
        req['CombOffsetFlag'] = offsetMap.get(orderReq.offset, '')

        req['OrderRef'] = str(self.orderRef)
        req['InvestorID'] = self.userID
        req['ExchangeID'] = orderReq.exchange
        req['UserID'] = self.userID
        req['BrokerID'] = self.brokerID

        req['CombHedgeFlag'] = defineDict['THOST_FTDC_HF_Speculation']       # 投机单
        req['ContingentCondition'] = defineDict['THOST_FTDC_CC_Immediately'] # 立即发单
        req['ForceCloseReason'] = defineDict['THOST_FTDC_FCC_NotForceClose'] # 非强平
        req['IsAutoSuspend'] = 0                                             # 非自动挂起
        req['TimeCondition'] = defineDict['THOST_FTDC_TC_GFD']               # 今日有效
        req['VolumeCondition'] = defineDict['THOST_FTDC_VC_AV']              # 任意成交量
        req['MinVolume'] = 1                                                 # 最小成交量为1

        # 判断FAK和FOK
        if orderReq.priceType == PRICETYPE_FAK:
            req['OrderPriceType'] = defineDict["THOST_FTDC_OPT_LimitPrice"]
            req['TimeCondition'] = defineDict['THOST_FTDC_TC_IOC']
            req['VolumeCondition'] = defineDict['THOST_FTDC_VC_AV']
        if orderReq.priceType == PRICETYPE_FOK:
            req['OrderPriceType'] = defineDict["THOST_FTDC_OPT_LimitPrice"]
            req['TimeCondition'] = defineDict['THOST_FTDC_TC_IOC']
            req['VolumeCondition'] = defineDict['THOST_FTDC_VC_CV']

        self.reqOrderInsert(req, self.reqID)

        # 返回订单号（字符串），便于某些算法进行动态管理
        vtOrderID = '.'.join([self.gatewayName, str(self.orderRef)])
        return vtOrderID

    # ----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.reqID += 1

        req = {}

        req['InstrumentID'] = cancelOrderReq.symbol
        req['ExchangeID'] = cancelOrderReq.exchange
        req['OrderRef'] = cancelOrderReq.orderID
        req['FrontID'] = cancelOrderReq.frontID
        req['SessionID'] = cancelOrderReq.sessionID

        req['ActionFlag'] = defineDict['THOST_FTDC_AF_Delete']
        req['BrokerID'] = self.brokerID
        req['InvestorID'] = self.userID

        self.reqOrderAction(req, self.reqID)

    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

class TdxMdApi():
    """
    通达信数据行情API实现
    通过线程池，仅仅查询订阅的行情，更新合约的数据

    """

    def __init__(self, gateway):
        self.gateway = gateway  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.req_interval = 0.5         # 操作请求间隔500毫秒
        self.req_id = EMPTY_INT         # 操作请求编号
        self.connection_status = False  # 连接状态

        self.symbol_exchange_dict = {}  # tdx合约与vn交易所的字典
        self.symbol_market_dict = {}    # tdx合约与tdx市场的字典
        self.symbol_vn_dict = {}        # tdx合约与vtSymbol的对应
        self.symbol_tick_dict = {}      # tdx合约与最后一个Tick得字典
        self.registed_symbol_set = set()

        #self.queue = Queue()            # 请求队列
        self.pool = None                 # 线程池
        #self.req_thread = None          # 定时器线程

        self.ip_list =  [
                        {"ip": "112.74.214.43", "port": 7727, "name": "扩展市场深圳双线1"},
                        {"ip": "120.24.0.77", "port": 7727,   "name": "扩展市场深圳双线2"},
                        {"ip": "47.107.75.159", "port": 7727, "name": "扩展市场深圳双线3"},

                        {"ip": "113.105.142.136", "port": 443, "name": "扩展市场东莞主站"},
                        {"ip": "113.105.142.133", "port": 443, "name": "港股期货东莞电信"},


                        {"ip": "119.97.185.5", "port": 7727, "name": "扩展市场武汉主站1"},
                        {"ip": "119.97.185.7", "port": 7727, "name": "港股期货武汉主站1"},
                        {"ip": "119.97.185.9", "port": 7727, "name": "港股期货武汉主站2"},

                        {"ip": "202.103.36.71", "port": 443, "name": "扩展市场武汉主站2"},

                        {"ip": "47.92.127.181", "port": 7727, "name": "扩展市场北京主站"},
                        {"ip": "106.14.95.149", "port": 7727, "name": "扩展市场上海双线"},
                        ]

        #  调出 {'ip': '218.80.248.229', 'port': 7721},
        # {"ip": "59.175.238.38", "port": 7727, "name": "扩展市场武汉主站3"},
        self.api_ip_dict = {}  # API 的连接服务器配置
        self.api_dict = {}  # API 的连接会话对象字典
        self.last_tick_dt = {} # 记录该会话对象的最后一个tick时间

        self.last_sort_speed_dt = None
        self.instrument_count = 50000

        self.has_qry_instrument = False

    # ----------------------------------------------------------------------
    def ping(self, ip, port=7709):
        """
        ping行情服务器
        :param ip:
        :param port:
        :param type_:
        :return:
        """
        apix = TdxExHq_API()
        __time1 = datetime.now()
        try:
            with apix.connect(ip, port):
                if apix.get_instrument_count() > 10000:
                    _timestamp = (datetime.now() - __time1).total_seconds() * 1000
                    self.writeLog('服务器{}:{},耗时:{}ms'.format(ip,port,_timestamp))
                    return _timestamp
                else:
                    self.writeLog(u'该服务器IP {}无响应.'.format(ip))
                    return timedelta(seconds=10).total_seconds()* 1000
        except:
            self.writeError(u'tdx ping服务器，异常的响应{}'.format(ip))
            return timedelta(seconds=10).total_seconds() * 1000

    def sort_ip_speed(self):
        """
        对所有服务器进行速度排序
        :return:
        """
        speed_result = []
        for x in self.ip_list:
            speed = self.ping(x['ip'], x['port'])
            x.update({'speed': speed})
            speed_result.append(copy.copy(x))

        # 更新服务器，按照速度排序
        self.ip_list = sorted(speed_result, key=lambda s: s['speed'])
        self.writeLog(u'服务器访问速度排序:{}'.format(self.ip_list))

    # ----------------------------------------------------------------------
    def select_best_ip(self,i=0):
        """
        选择行情服务器
        :return:
        """
        self.writeLog(u'选择通达信行情服务器')
        if self.last_sort_speed_dt is None or (datetime.now() - self.last_sort_speed_dt).total_seconds() > 60:
            self.sort_ip_speed()
            self.last_sort_speed_dt = datetime.now()

        valid_ip_list = [x for x in self.ip_list if x.get('speed',10000)<10000]

        if len(valid_ip_list) == 0:
            self.gateway.writeError(u'未能找到合适速度得行情服务器')
            return None,None

        # 移除旧得api对应服务器IP/port地址配置
        self.api_ip_dict.pop(i,None)

        if len(valid_ip_list) < len(self.api_ip_dict):
            self.writeLog(u'已经选择得服务器数量，大于可供选择得服务器数量，优先选择第一个')
            return valid_ip_list[0].get('ip'),valid_ip_list[0].get('port')

        using_server = self.api_ip_dict.values()
        self.writeLog(u'已经使用得服务器列表:{}'.format(using_server))
        for server in valid_ip_list:
            ip = server.get('ip')
            port = server.get('port')
            if '{}:{}'.format(ip,port) in using_server:
                continue
            return ip, port

        self.writeLog(u'未能有效选择，默认第一个')
        return valid_ip_list[0].get('ip'),valid_ip_list[0].get('port')

    def connect(self,n=3):
        """
        连接通达讯行情服务器
        :param n:
        :return:
        """
        if self.connection_status:
            for api in self.api_dict:
                if api is not None or getattr(api,"client",None) is not None:
                    self.writeLog(u'当前已经连接,不需要重新连接')
                    return

        self.writeLog(u'开始通达信行情服务器')
        # 创建n个api连接对象实例
        for i in range(n):
            try:
                api = TdxExHq_API( heartbeat=True, auto_retry=True,raise_exception=True)
                # 选取最佳服务器
                best_ip,best_port = self.select_best_ip(i)

                if best_ip is None or best_port is None:
                    self.writeError(u'未能选择到服务器')

                self.writeLog(u'api[{}] 选择 {}:{}'.format(i, best_ip, best_port))
                api.connect(best_ip, best_port)
                # 尝试获取市场合约统计
                c = api.get_instrument_count()
                if c is None or c < 10:
                    err_msg = u'该服务器IP {}/{}无响应'.format(best_ip,best_port )
                    err = VtErrorData()
                    err.gatewayName = self.gatewayName
                    err.errorID = -1
                    err.errorMsg = err_msg
                    self.gateway.onError(err)
                else:
                    self.writeLog(u'创建第{}个tdx连接'.format(i+1))
                    self.api_dict[i] = api
                    self.api_ip_dict.update({i:'{}:{}'.format(best_ip,best_port)})
                    self.last_tick_dt[i] = datetime.now()
                    self.connection_status = True
                    self.instrument_count = c

            except Exception as ex:
                self.writeError(u'连接服务器tdx[{}]异常:{},{}'.format(i,str(ex),traceback.format_exc()))
                return

        # 更新 symbol_exchange_dict , symbol_market_dict
        self.qryInstrument()

        #self.req_thread = Thread(target=self.addReq)
        #self.req_thread.start()

        # 创建连接池，每个连接都调用run方法
        self.pool = Pool(n)
        self.pool.map_async(self.run,range(n))

    def reconnect(self,i):
        """
        重连
        :param i:
        :return:
        """
        try:
            best_ip,best_port = self.select_best_ip(i)
            api = TdxExHq_API(heartbeat=True, auto_retry=True)
            api.connect(best_ip,best_port)
            # 尝试获取市场合约统计
            c = api.get_instrument_count()
            if c is None or c < 10:
                err_msg = u'该服务器IP {}/{}无响应'.format(best_ip,best_port)
                err = VtErrorData()
                err.gatewayName = self.gatewayName
                err.errorID = -1
                err.errorMsg = err_msg
                self.gateway.onError(err)
            else:
                self.writeLog(u'重新创建第{}个tdx连接'.format(i + 1))
                self.api_dict[i] = api
                self.api_ip_dict.update({i: '{}:{}'.format(best_ip, best_port)})
            sleep(1)
        except Exception as ex:
            self.writeError(u'重新连接服务器tdx[{}]异常:{},{}'.format(i, str(ex), traceback.format_exc()))
            return

    def close(self):
        """退出API"""
        self.connection_status = False

        if self.pool is not None:
            self.pool.close()
            self.pool.join()
    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅合约"""
        # 这里的设计是，如果尚未登录就调用了订阅方法
        # 则先保存订阅请求，登录完成后会自动订阅
        vn_symbol = str(subscribeReq.symbol)
        vn_symbol = vn_symbol.upper()
        self.writeLog(u'通达信行情订阅 {}'.format(str(vn_symbol)))

        if vn_symbol[-2:] != '99':
            self.writeLog(u'{}不是指数合约，不能订阅'.format(vn_symbol))
            return

        tdx_symbol = vn_symbol[0:-2] + 'L9'
        tdx_symbol = tdx_symbol.upper()
        self.writeLog(u'{}=>{}'.format(vn_symbol,tdx_symbol))
        self.symbol_vn_dict[tdx_symbol] = vn_symbol

        if tdx_symbol not in self.registed_symbol_set:
            self.registed_symbol_set.add(tdx_symbol)

        self.checkStatus()

    def checkStatus(self):
        #self.writeLog(u'检查tdx接口状态')
        if len(self.registed_symbol_set) ==0:
            return

        # 若还没有启动连接，就启动连接
        over_time = [((datetime.now()-dt).total_seconds() > 60) for dt in self.last_tick_dt.values()]
        if not self.connection_status or len(self.api_dict) == 0 or any(over_time):
            self.writeLog(u'tdx还没有启动连接，就启动连接')
            self.close()
            self.pool = None
            self.api_dict = {}
            pool_cout = getattr(self.gateway,'tdx_pool_count',3)
            self.connect(pool_cout)

        #self.writeLog(u'tdx接口状态正常')

    def qryInstrument(self):
        """
        查询/更新合约信息
        :return:
        """
        if not self.connection_status:
            return

        if self.has_qry_instrument:
            return

        api = self.api_dict.get(0)
        if api is None:
            self.writeLog(u'取不到api连接，更新合约信息失败')
            return

        # 取得所有的合约信息
        num = api.get_instrument_count()
        if not isinstance(num,int):
            return

        all_contacts = sum([api.get_instrument_info((int(num / 500) - i) * 500, 500) for i in range(int(num / 500) + 1)],[])
        #[{"category":category,"market": int,"code":sting,"name":string,"desc":string},{}]

        # 对所有合约处理，更新字典 指数合约-tdx市场，指数合约-交易所
        for tdx_contract in all_contacts:
            tdx_symbol = tdx_contract.get('code', None)
            if tdx_symbol is None or tdx_symbol[-2:] not in ['L9']:
                continue
            tdx_market_id = tdx_contract.get('market')
            self.symbol_market_dict[tdx_symbol] = tdx_market_id
            if tdx_market_id == 47:     # 中金所
                self.symbol_exchange_dict[tdx_symbol] = EXCHANGE_CFFEX
            elif tdx_market_id == 28:   # 郑商所
                self.symbol_exchange_dict[tdx_symbol] = EXCHANGE_CZCE
            elif tdx_market_id == 29:   # 大商所
                self.symbol_exchange_dict[tdx_symbol] = EXCHANGE_DCE
            elif tdx_market_id == 30:   # 上期所+能源
                self.symbol_exchange_dict[tdx_symbol] = EXCHANGE_SHFE

        self.has_qry_instrument = True

    def run(self, i):
        """
        版本1：Pool内得线程，持续运行,每个线程从queue中获取一个请求并处理
        版本2：Pool内线程，从订阅合约集合中，取出符合自己下标 mode n = 0的合约，并发送请求
        :param i:
        :return:
        """
        """
        # 版本1
        while self.connection_status:
            try:
                req = self.queue.get(timeout=self.req_interval)
                self.processReq(req,i)
            except Exception as ex:
                self.writeLog(u'tdx[{}] exception:{},{}'.format(i,str(ex),traceback.format_exc()))
        """
        # 版本2：
        try:
            api_count = len(self.api_dict)
            last_dt = datetime.now()
            self.writeLog(u'开始运行tdx[{}],{}'.format(i,last_dt))
            while self.connection_status:
                symbols = set()
                for idx,tdx_symbol in enumerate(list(self.registed_symbol_set)):
                    #self.writeLog(u'tdx[{}], api_count:{}, idx:{}, tdx_symbol:{}'.format(i, api_count, idx, tdx_symbol))
                    if idx % api_count == i:
                        try:
                            symbols.add(tdx_symbol)
                            self.processReq(tdx_symbol, i)
                        except BrokenPipeError as bex:
                            self.writeError(u'BrokenPipeError{},重试重连tdx[{}]'.format(str(bex),i))
                            self.reconnect(i)
                            sleep(5)
                            break
                        except Exception as ex:
                            self.writeError(u'tdx[{}] exception:{},{}'.format(i, str(ex), traceback.format_exc()))

                            #api = self.api_dict.get(i,None)
                            #if api is None or getattr(api,'client') is None:
                            self.writeError(u'重试重连tdx[{}]'.format(i))
                            print(u'重试重连tdx[{}]'.format(i),file=sys.stderr)
                            self.reconnect(i)

                #self.writeLog(u'tdx[{}] sleep'.format(i))
                sleep(self.req_interval)
                dt = datetime.now()
                if last_dt.minute != dt.minute:
                    self.writeLog('tdx[{}] check point. {}, process symbols:{}'.format(i,dt,symbols))
                    last_dt = dt
        except Exception as ex:
            self.writeError(u'tdx[{}] pool.run exception:{},{}'.format(i, str(ex), traceback.format_exc()))

        self.writeError(u'tdx[{}] {}退出'.format(i,datetime.now()))

    def processReq(self, req, i):
        """
        处理行情信息ticker请求
        :param req:
        :param i:
        :return:
        """
        symbol = req
        api = self.api_dict.get(i, None)
        if api is None:
            self.writeLog(u'tdx[{}] Api is None'.format(i))
            raise Exception(u'tdx[{}] Api is None'.format(i))

        #self.writeLog(u'tdx[{}] get_instrument_quote:({},{})'.format(i,self.symbol_market_dict.get(symbol),symbol))
        rt_list = api.get_instrument_quote(self.symbol_market_dict.get(symbol),symbol)
        if rt_list is None or len(rt_list) == 0:
            self.writeLog(u'tdx[{}]: rt_list为空'.format(i))
            return
        #else:
        #    self.writeLog(u'tdx[{}]: rt_list数据:{}'.format(i, rt_list))
        if i in self.last_tick_dt:
            self.last_tick_dt[i] = datetime.now()

        for d in list(rt_list):
            # 忽略成交量为0的无效单合约tick数据
            if d.get('xianliang', 0) <= 0:
                self.writeLog(u'忽略成交量为0的无效单合约tick数据:')
                continue

            code = d.get('code',None)
            if symbol != code and code is not None:
                #self.writeLog(u'忽略合约{} {} 不一致的tick数据:{}'.format(symbol,d.get('code'),rt_list))
                #continue
                symbol = code

            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.symbol = self.symbol_vn_dict.get(symbol,None)
            if tick.symbol is None:
                self.writeLog(u'self.symbol_vn_dict 取不到映射得:{}'.format(symbol))
                return
            tick.symbol = tick.symbol.upper()
            tick.exchange = self.symbol_exchange_dict.get(symbol)
            tick.vtSymbol = tick.symbol

            tick.preClosePrice = d.get('pre_close')
            tick.highPrice = d.get('high')
            tick.openPrice = d.get('open')
            tick.lowPrice = d.get('low')
            tick.lastPrice = d.get('price')

            tick.volume = d.get('zongliang',0)
            tick.openInterest = d.get('chicang')

            tick.datetime = datetime.now()
            # 修正毫秒
            last_tick = self.symbol_tick_dict.get(symbol,None)
            if (last_tick is not None) and tick.datetime.replace(microsecond=0) == last_tick.datetime:
                # 与上一个tick的时间（去除毫秒后）相同,修改为500毫秒
                tick.datetime = tick.datetime.replace(microsecond=500)
                tick.time = tick.datetime.strftime('%H:%M:%S.%f')[0:12]
            else:
                tick.datetime = tick.datetime.replace(microsecond=0)
                tick.time = tick.datetime.strftime('%H:%M:%S.%f')[0:12]

            tick.date = tick.datetime.strftime('%Y-%m-%d')

            # 修正时间
            if tick.datetime.hour >= 20:
                if tick.datetime.isoweekday() == 5:
                    # 交易日是星期下周一
                    tick.tradingDay = tick.datetime + timedelta(days=3)
                else:
                    # 第二天
                    tick.tradingDay = tick.datetime + timedelta(days=1)
            elif tick.datetime.hour < 8 and tick.datetime.isoweekday() == 6:
                # 交易日是星期一
                tick.tradingDay = tick.datetime + timedelta(days=2)
            else:
                tick.tradingDay = tick.datetime
            tick.tradingDay = tick.tradingDay.strftime('%Y-%m-%d')

            # 指数没有涨停和跌停，就用昨日收盘价正负10%
            tick.upperLimit = tick.preClosePrice * 1.1
            tick.lowerLimit = tick.preClosePrice * 0.9

            # CTP只有一档行情
            tick.bidPrice1 = d.get('bid1')
            tick.bidVolume1 = d.get('bid_vol1')
            tick.askPrice1 = d.get('ask1')
            tick.askVolume1 = d.get('ask_vol1')

            short_symbol = tick.vtSymbol
            short_symbol = short_symbol.replace('99', '').upper()

            # 排除非交易时间得tick
            if tick.exchange is EXCHANGE_CFFEX:
                if tick.datetime.hour not in [9,10,11,13,14,15]:
                    return
                if tick.datetime.hour == 9 and tick.datetime.minute < 15:
                    return
                # 排除早盘 11:30~12:00
                if tick.datetime.hour == 11 and tick.datetime.minute >= 30:
                    return
                if tick.datetime.hour == 15 and tick.datetime.minute >= 15:
                    return
            else:  # 大商所/郑商所，上期所，上海能源
                # 排除非开盘小时
                if tick.datetime.hour in [3,4,5,6,7,8,12,15,16,17,18,19,20]:
                    return
                # 排除早盘 10:15~10:30
                if tick.datetime.hour == 10 and 15 <= tick.datetime.minute < 30:
                    return
                # 排除早盘 11:30~12:00
                if tick.datetime.hour == 11 and tick.datetime.minute >= 30:
                    return
                # 排除午盘 13:00 ~13:30
                if tick.datetime.hour == 13 and tick.datetime.minute < 30:
                    return
                # 排除凌晨2:30~3:00
                if tick.datetime.hour == 2 and tick.datetime.minute >= 30:
                    return

                # 排除大商所/郑商所夜盘数据
                if short_symbol in NIGHT_MARKET_ZZ:
                    if tick.datetime.hour == 23 and tick.datetime.minute>=30:
                        return
                    if tick.datetime.hour in [0,1,2]:
                        return

                # 排除上期所夜盘数据 23:00 收盘
                if short_symbol in NIGHT_MARKET_SQ3 or short_symbol in NIGHT_MARKET_DL:
                    if tick.datetime.hour in [23,0,1,2]:
                        return
                # 排除上期所夜盘数据 1:00 收盘
                if short_symbol in NIGHT_MARKET_SQ2:
                    if tick.datetime.hour in [1,2]:
                        return

            # 排除日盘合约在夜盘得数据
            if short_symbol in MARKET_DAY_ONLY and (tick.datetime.hour < 9 or tick.datetime.hour > 16):
                #self.writeLog(u'排除日盘合约{}在夜盘得数据'.format(short_symbol))
                return

            if self.gateway.debug_tick:
                self.writeLog('tdx {},{},{},{},{},{},{},{},{},{},{},{},{},{}'.format(tick.gatewayName, tick.symbol,
                                                                             tick.exchange, tick.vtSymbol,
                                                                             tick.datetime, tick.tradingDay,
                                                                             tick.openPrice, tick.highPrice,
                                                                             tick.lowPrice, tick.preClosePrice,
                                                                             tick.bidPrice1,
                                                                             tick.bidVolume1, tick.askPrice1,
                                                                             tick.askVolume1))


            self.symbol_tick_dict[symbol] = tick

            self.gateway.onTick(tick)
            self.gateway.onCustomerTick(tick)

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    def writeError(self,content):
        self.gateway.writeError(content)

class RedisMdApi():
    """
    Redis数据行情API实现
    通过线程，查询订阅的行情，更新合约的数据

    """

    def __init__(self, gateway):
        """Constructor"""
        self.EventType = "RedisQuotation"
        self.gateway = gateway  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.req_interval = 0.5  # 操作请求间隔500毫秒
        self.connection_status = False  # 连接状态

        self.symbol_tick_dict = {}  # Redis合约与最后一个Tick得字典
        self.registed_symbol_set = set()

        # Redis服务器列表
        self.ip_list = [{'ip': '192.168.1.211', 'port': 6379},
                        {'ip': '192.168.1.212', 'port': 6379},
                        {'ip': '192.168.0.203', 'port': 6379}
                        ]
        self.best_ip = {'ip': None, 'port': None}  # 最佳服务器

        self.last_tick_dt = None  # 记录该会话对象的最后一个tick时间

        # 查询线程
        self.quotation_thread = None

    # ----------------------------------------------------------------------
    def ping(self, ip, port=6379):
        """
        ping行情服务器
        :param ip:
        :param port:
        :param type_:
        :return:
        """
        __time1 = datetime.now()
        try:
            r = redis.Redis(host=ip, port=port, db=0, socket_connect_timeout=2)
            r.set('ping', ip)
            _timestamp = datetime.now() - __time1
            self.writeLog('Redis服务器{}:{},耗时:{}'.format(ip, port, _timestamp))
            return _timestamp
        except:
            self.writeError(u'Redis ping服务器，异常的响应{}'.format(ip))
            return timedelta(9, 9, 0)

    # ----------------------------------------------------------------------
    def select_best_ip(self):
        """
        选择行情服务器
        :return:
        """
        self.writeLog(u'选择Redis行情服务器')

        data_future = [self.ping(x['ip'], x['port']) for x in self.ip_list]

        best_future_ip = self.ip_list[data_future.index(min(data_future))]

        self.writeLog(u'选取 {}:{}'.format(
            best_future_ip['ip'], best_future_ip['port']))
        return best_future_ip

    def connect(self):
        """
        连接Redis行情服务器
        :return:
        """
        if self.connection_status:
            return

        self.writeLog(u'开始连接Redis行情服务器')

        try:
            # 选取最佳服务器
            if self.best_ip['ip'] is None and self.best_ip['port'] is None:
                self.best_ip = self.select_best_ip()

            # 创建Redis连接对象实例
            pool = redis.ConnectionPool(host=self.best_ip['ip'], port=self.best_ip['port'])
            self.redis = redis.Redis(connection_pool=pool)

            self.redis.set('Connect', self.best_ip['ip'])
            self.writeLog(u'连接Redis服务器{}:{}成功'.format(self.best_ip['ip'], self.best_ip['port']))

            self.last_tick_dt = datetime.now()
            self.connection_status = True

            # 查询线程
            self.quotation_thread = Thread(target=self.run, name="QuotationEngine.%s" % self.EventType)
            self.quotation_thread.setDaemon(False)
            # 调用run方法
            self.quotation_thread.start()
        except Exception as ex:
            self.writeLog(u'连接Redis服务器{}:{}异常:{},{}'.format(self.best_ip['ip'], self.best_ip['port'],
                                                            str(ex), traceback.format_exc()))
            return

    def reconnect(self, i):
        """
        重连
        :param i:
        :return:
        """
        self.writeLog(u'开始重连redis服务器')
        try:
            # 选取最佳服务器
            self.best_ip = self.select_best_ip()

            # 创建Redis连接对象实例
            pool = redis.ConnectionPool(host=self.best_ip['ip'], port=self.best_ip['port'])
            self.redis = redis.Redis(connection_pool=pool)
            self.redis.set('Connect', self.best_ip['ip'])
            self.writeLog(u'重新连接Redis服务器{}:{}成功'.format(self.best_ip['ip'], self.best_ip['port']))

            self.last_tick_dt = datetime.now()
            self.connection_status = True

            # 查询线程
            self.quotation_thread = Thread(target=self.run, name="QuotationEngine.%s" % self.EventType)
            self.quotation_thread.setDaemon(False)
            # 调用run方法
            self.quotation_thread.start()

        except Exception as ex:
            self.writeLog(u'重新连接Redis服务器{}:{}异常:{},{}'.format(self.best_ip['ip'], self.best_ip['port'],
                                                              str(ex), traceback.format_exc()))
            return

    def close(self):
        """退出API"""
        self.connection_status = False

    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅合约"""

        # 这里的设计是，如果尚未登录就调用了订阅方法
        # 则先保存订阅请求，登录完成后会自动订阅
        vn_symbol = str(subscribeReq.symbol)
        vn_symbol = vn_symbol.upper()

        if vn_symbol[-2:] != '99':
            self.writeLog(u'Redis行情订阅: {}不是指数合约，不能订阅'.format(vn_symbol))
            return

        redis_symbol_0 = vn_symbol.upper() + '.2'
        redis_symbol_1 = vn_symbol.upper() + '.3'
        self.writeLog(u'Redis行情订阅: {}=>{} & {}'.format(vn_symbol, redis_symbol_0, redis_symbol_1))

        if redis_symbol_0 not in self.registed_symbol_set:
            self.registed_symbol_set.add(redis_symbol_0)
        if redis_symbol_1 not in self.registed_symbol_set:
            self.registed_symbol_set.add(redis_symbol_1)

        self.checkStatus()

    def checkStatus(self):
        """检查连接状态"""

        if len(self.registed_symbol_set) == 0:
            return

        # 若还没有启动连接，就启动连接
        if self.last_tick_dt is None:
            over_time = False
        else:
            over_time = ((datetime.now() - self.last_tick_dt).total_seconds() > 60)

        if not self.connection_status or over_time is True:
            self.writeLog(u'Redis服务器{}:{} 还没有连接，启动连接'.format(self.best_ip['ip'], self.best_ip['port']))
            self.close()
            self.connect()

    def run(self):
        """
        :return:
        """
        try:
            last_dt = datetime.now()
            self.writeLog(u'开始运行Redis行情服务器, {}'.format(last_dt))
            lastResult = dict()
            while self.connection_status:
                if len(self.registed_symbol_set)==0:
                    continue
                # 从Redis中读取指数数据
                symbols = sorted(list(self.registed_symbol_set))
                results = self.redis.mget(symbols)

                # 只有当Tick发生改变时才推送到Gateway
                # 比较2个源的数据, 选择最新&正确的那个
                # 1. 每个源判断接收到的数据是否异常, 异常则抛弃
                #    - 波动幅度>10%
                #    - 价格异常
                # 2. 只有1个源有数据, 就选择那个源
                # 3. 如果2个源都有数据, 就选择时间更新的那个源
                for i in range(0, len(symbols), 2):
                    # 解码Redis返回值
                    rt_tick_dict0 = None
                    rt_tick_dict1 = None

                    if results[i] is not None and len(results[i]) > 0:
                        try:
                            rt_tick_dict0 = json.loads(str(results[i], 'utf-8'))
                            if len(rt_tick_dict0) == 0:
                                self.writeLog(u'redis[{}]: rt_list0 为空, {}'.format(symbols[i], results[i]))
                                rt_tick_dict0 = None
                            elif symbols[i] in lastResult and lastResult[symbols[i]] is not None:
                                if str(rt_tick_dict0) != str(lastResult[symbols[i]]):
                                    change_percent = abs(float(lastResult[symbols[i]]['LastPrice']) - float(rt_tick_dict0['LastPrice'])) / float(lastResult[symbols[i]]['LastPrice']) * 100
                                    if change_percent >= 10:
                                        self.writeLog(u'redis[{}]: rt_list0 数据异常, 变动>10%: {}% ({}, {})'.format(symbols[i],
                                                                    change_percent, lastResult[symbols[i]]['LastPrice'], rt_tick_dict0['LastPrice']))
                                        rt_tick_dict0 = None
                                else:
                                    # 无变动, 不需要更新
                                    rt_tick_dict0 = None
                            else:
                                lastResult[symbols[i]] = rt_tick_dict0
                        except Exception as ex:
                            self.writeError(u'Redis行情服务器 run() exception:{},{}, rt_list0:{}不正确'.format(str(ex),
                                                                                                    traceback.format_exc(),results[i]))
                    if results[i+1] is not None and len(results[i+1]) > 0:
                        try:
                            rt_tick_dict1 = json.loads(str(results[i + 1], 'utf-8'))
                            if len(rt_tick_dict1) == 0:
                                self.writeLog(u'redis[{}]: rt_list1 为空, {}'.format(symbols[i+1], results[i+1]))
                                rt_tick_dict1 = None

                            elif symbols[i+1] in lastResult and lastResult[symbols[i+1]] is not None:
                                if str(rt_tick_dict1) != str(lastResult[symbols[i+1]]):
                                    change_percent = abs(float(lastResult[symbols[i+1]]['LastPrice']) - float(rt_tick_dict1['LastPrice'])) / float(lastResult[symbols[i+1]]['LastPrice']) * 100
                                    if change_percent >= 10:
                                        self.writeLog(u'redis[{}]: rt_list1 数据异常, 变动>10%: {}% ({}, {})'.format(symbols[i+1],
                                                                    change_percent, lastResult[symbols[i+1]]['LastPrice'], rt_tick_dict1['LastPrice']))
                                        rt_tick_dict1 = None
                                else:
                                    # 无变动, 不需要更新
                                    rt_tick_dict1 = None
                            else:
                                lastResult[symbols[i + 1]] = rt_tick_dict1

                        except Exception as ex:
                            self.writeError(u'Redis行情服务器 run() exception:{},{}, rt_list1:{}不正确'
                                            .format(str(ex), traceback.format_exc(),results[i+1]))

                    # 选择非空&时间较新的数据
                    if rt_tick_dict0 is None and rt_tick_dict1 is None:
                        continue

                    rt_tick_dict = None
                    if rt_tick_dict1 is None:
                        rt_tick_dict = rt_tick_dict0
                    elif rt_tick_dict0 is None:
                        rt_tick_dict = rt_tick_dict1
                    else:
                        millionseconds = str(rt_tick_dict0.get('UpdateMillisec',EMPTY_STRING))
                        if len(millionseconds) > 6:
                            millionseconds = millionseconds[0:6]
                        tick_time = '{}.{}'.format(rt_tick_dict0['UpdateTime'], millionseconds)
                        rt_tick0_dt = datetime.strptime(rt_tick_dict0['TradingDay'] + ' ' + tick_time, '%Y%m%d %H:%M:%S.%f')

                        millionseconds = str(rt_tick_dict1.get('UpdateMillisec',EMPTY_STRING))
                        if len(millionseconds) > 6:
                            millionseconds = millionseconds[0:6]
                        tick_time = '{}.{}'.format(rt_tick_dict1['UpdateTime'], millionseconds)
                        rt_tick1_dt = datetime.strptime(rt_tick_dict1['TradingDay'] + ' ' + tick_time, '%Y%m%d %H:%M:%S.%f')

                        if rt_tick0_dt < rt_tick1_dt:
                            rt_tick_dict = rt_tick_dict1
                        else:
                            rt_tick_dict = rt_tick_dict0

                    self.processReq(symbols[i][0:-2], rt_tick_dict)

                # 等待下次查询 (500ms)
                # self.writeLog(u'redis[{}] sleep'.format(i))
                sleep(self.req_interval)
                dt = datetime.now()
                if last_dt.minute != dt.minute:
                    self.writeLog('Redis行情服务器 check point. {}, process symbols:{}'.format(dt, symbols))
                    last_dt = dt
        except Exception as ex:
            self.writeError(u'Redis行情服务器 run() exception:{},{}'.format(str(ex), traceback.format_exc()))

        self.writeError(u'Redis行情服务器在{}退出'.format(datetime.now()))

    def processReq(self, symbol, tick_dict):
        """
        处理行情信息ticker请求
        :param symbol:
        :param req:
        :return:
        """
        if not isinstance(tick_dict,dict):
            self.writeLog(u'行情tick不是dict：{}'.format(tick_dict))
            return

        self.last_tick_dt = datetime.now()

        # 忽略成交量为0的无效单合约tick数据
        if int(tick_dict.get('Volume', 0)) <= 0:
            self.writeLog(u'Redis服务器{}:{} 忽略成交量为0的无效合约tick数据: {}'
                          .format(self.best_ip['ip'], self.best_ip['port'], tick_dict))

        tick = VtTickData()
        tick.gatewayName = self.gatewayName

        tick.symbol = symbol
        if tick.symbol is None:
            return
        tick.exchange = tick_dict.get('ExchangeID')
        tick.vtSymbol = tick.symbol

        short_symbol = tick.vtSymbol
        short_symbol = short_symbol.replace('99', '').upper()

        # 使用本地时间
        tick.datetime = datetime.now()
        # 修正毫秒
        last_tick = self.symbol_tick_dict.get(symbol, None)
        if (last_tick is not None) and tick.datetime.replace(microsecond=0) == last_tick.datetime:
            # 与上一个tick的时间（去除毫秒后）相同,修改为500毫秒
            tick.datetime = tick.datetime.replace(microsecond=500)
            tick.time = tick.datetime.strftime('%H:%M:%S.%f')[0:12]
        else:
            tick.datetime = tick.datetime.replace(microsecond=0)
            tick.time = tick.datetime.strftime('%H:%M:%S.%f')[0:12]

        tick.date = tick.datetime.strftime('%Y-%m-%d')

        # 生成TradingDay
        # 正常日盘时间
        tick.tradingDay = tick.date

        # 修正夜盘的tradingDay
        if tick.datetime.hour >= 20:
            # 周一~周四晚上20点之后的tick，交易日属于第二天
            if tick.datetime.isoweekday() in [1, 2, 3, 4]:
                trading_day = tick.datetime + timedelta(days=1)
                tick.tradingDay = trading_day.strftime('%Y-%m-%d')
            # 周五晚上20点之后的tick，交易日属于下周一
            elif tick.datetime.isoweekday() == 5:
                trading_day = tick.datetime + timedelta(days=3)
                tick.tradingDay = trading_day.strftime('%Y-%m-%d')
        elif tick.datetime.hour < 3:
            # 周六凌晨的tick，交易日属于下周一
            if tick.datetime.isoweekday() == 6:
                trading_day = tick.datetime + timedelta(days=2)
                tick.tradingDay = trading_day.strftime('%Y-%m-%d')

        # 排除非交易时间得tick
        if tick.exchange is EXCHANGE_CFFEX:
            if tick.datetime.hour not in [9, 10, 11, 13, 14, 15]:
                return
            if tick.datetime.hour == 9 and tick.datetime.minute < 15:
                return
            if tick.datetime.hour == 15 and tick.datetime.minute >= 15:
                return
        else:  # 大商所/郑商所，上期所，上海能源
            # 排除非开盘小时
            if tick.datetime.hour in [3, 4, 5, 6, 7, 8, 12, 15, 16, 17, 18, 19, 20]:
                return
            # 排除早盘 10:15~10:30
            if tick.datetime.hour == 10 and 15 <= tick.datetime.minute < 30:
                return
            # 排除早盘 11:30~12:00
            if tick.datetime.hour == 11 and tick.datetime.minute >= 30:
                return
            # 排除午盘 13:00 ~13:30
            if tick.datetime.hour == 13 and tick.datetime.minute < 30:
                return
            # 排除凌晨2:30~3:00
            if tick.datetime.hour == 2 and tick.datetime.minute >= 30:
                return

            # 排除大商所/郑商所夜盘数据
            if  short_symbol in NIGHT_MARKET_ZZ:
                if tick.datetime.hour == 23 and tick.datetime.minute >= 30:
                    return
                if tick.datetime.hour in [0, 1, 2]:
                    return

            # 排除上期所夜盘数据 23:00 收盘
            if  short_symbol in NIGHT_MARKET_DL or short_symbol in NIGHT_MARKET_SQ3:
                if tick.datetime.hour in [23, 0, 1, 2]:
                    return
            # 排除上期所夜盘数据 1:00 收盘
            if short_symbol in NIGHT_MARKET_SQ2:
                if tick.datetime.hour in [1, 2]:
                    return

        # 排除日盘合约在夜盘得数据
        if short_symbol in MARKET_DAY_ONLY and (tick.datetime.hour < 9 or tick.datetime.hour > 16):
            self.writeLog(u'Redis服务器{}:{} 排除日盘合约{}在夜盘得数据, {}'.format(self.best_ip['ip'],
                                                                     self.best_ip['port'], short_symbol, tick_dict))
            return

        # 设置指数价格
        tick.preClosePrice = float(tick_dict.get('PreClosePrice', 0))
        tick.highPrice = float(tick_dict.get('HighestPrice', 0))
        tick.openPrice = float(tick_dict.get('OpenPrice', 0))
        tick.lowPrice = float(tick_dict.get('LowestPrice', 0))
        tick.lastPrice = float(tick_dict.get('LastPrice', 0))

        tick.volume = int(tick_dict.get('Volume', 0))
        tick.openInterest = int(tick_dict.get('OpenInterest', 0))
        tick.lastVolume = 0  # 最新成交量
        tick.upperLimit = float(tick_dict.get('UpperLimitPrice', 0))
        tick.lowerLimit = float(tick_dict.get('LowerLimitPrice', 0))

        # CTP只有一档行情
        if tick_dict.get('BidPrice1', 'nan') == 'nan': # 上期所有时会返回nan
            tick.bidPrice1 = tick.lastPrice
        else:
            tick.bidPrice1 = float(tick_dict.get('BidPrice1', 0))
        tick.bidVolume1 = int(tick_dict.get('BidVolume1', 0))
        if tick_dict.get('AskPrice1', 'nan') == 'nan': # 上期所有时会返回nan
            tick.askPrice1 = tick.lastPrice
        else:
            tick.askPrice1 = float(tick_dict.get('AskPrice1', 0))
        tick.askVolume1 = int(tick_dict.get('AskVolume1', 0))

        tick.preOpenInterest = int(tick_dict.get('PreOpenInterest', 0))  # 昨持仓量

        if self.gateway.debug_tick:
            self.writeLog('Redis服务器{}[{}]:\n gateway:{},symbol:{},exch:{},vtsymbol:{},\n dt:{},td:{},' 
                      'lastPrice:{},volume:{},'
                      'openPirce:{},highprice:{},lowPrice:{},preClosePrice:{},\nbid1:{},bv1:{},ask1:{},av1:{}'
                      .format(self.best_ip['ip'],
                            self.best_ip['port'],
                            tick.gatewayName, tick.symbol,
                            tick.exchange, tick.vtSymbol,
                            tick.datetime, tick.tradingDay,
                            tick.lastPrice,tick.volume,
                            tick.openPrice, tick.highPrice,
                            tick.lowPrice, tick.preClosePrice,
                            tick.bidPrice1,
                            tick.bidVolume1, tick.askPrice1,
                            tick.askVolume1))

        self.symbol_tick_dict[symbol] = tick
        self.gateway.onTick(tick)
        self.gateway.onCustomerTick(tick)

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    def writeError(self, content):
        self.writeLog(content)

class TickCombiner(object):
    """
    Tick合成类
    """
    def __init__(self, gateway, setting):
        self.gateway = gateway

        self.gateway.writeLog(u'创建tick合成类:{}'.format(setting))

        self.vtSymbol = setting.get('vtSymbol',None)
        self.leg1_symbol = setting.get('leg1_symbol',None)
        self.leg2_symbol = setting.get('leg2_symbol',None)
        self.leg1_ratio = setting.get('leg1_ratio', 1)  # 腿1的数量配比
        self.leg2_ratio = setting.get('leg2_ratio', 1)  # 腿2的数量配比
        self.minDiff = setting.get('minDiff',1)         # 合成价差加比后的最小跳动
        # 价差
        self.is_spread = setting.get('is_spread', False)
        # 价比
        self.is_ratio = setting.get('is_ratio', False)

        self.last_leg1_tick = None
        self.last_leg2_tick = None

        # 价差日内最高/最低价
        self.spread_high = None
        self.spread_low = None

        # 价比日内最高/最低价
        self.ratio_high = None
        self.ratio_low = None

        # 当前交易日
        self.tradingDay = None

        if self.is_ratio and self.is_spread:
            self.gateway.writeError(u'{}参数有误，不能同时做价差/加比.setting:{}'.format(self.vtSymbol,setting))
            return

        self.gateway.writeLog(u'初始化{}合成器成功'.format(self.vtSymbol))
        if self.is_spread:
            self.gateway.writeLog(u'leg1:{} * {} - leg2:{} * {}'.format(self.leg1_symbol,self.leg1_ratio,self.leg2_symbol,self.leg2_ratio))
        if self.is_ratio:
            self.gateway.writeLog(u'leg1:{} * {} / leg2:{} * {}'.format(self.leg1_symbol, self.leg1_ratio, self.leg2_symbol,
                                                      self.leg2_ratio))
    def onTick(self, tick):
        """OnTick处理"""
        combinable = False

        if tick.vtSymbol == self.leg1_symbol:
            # leg1合约
            self.last_leg1_tick = tick
            if self.last_leg2_tick is not None:
                if self.last_leg1_tick.datetime.replace(microsecond=0) == self.last_leg2_tick.datetime.replace(microsecond=0):
                    combinable = True

        elif tick.vtSymbol == self.leg2_symbol:
            # leg2合约
            self.last_leg2_tick = tick
            if self.last_leg1_tick is not None:
                if self.last_leg2_tick.datetime.replace(microsecond=0) == self.last_leg1_tick.datetime.replace(microsecond=0):
                    combinable = True

        # 不能合并
        if not combinable:
            return

        if not self.is_ratio and not self.is_spread:
            return

        # 以下情况，基本为单腿涨跌停，不合成价差/价格比 Tick
        if (self.last_leg1_tick.askPrice1 == 0 or self.last_leg1_tick.bidPrice1 == self.last_leg1_tick.upperLimit)\
                and self.last_leg1_tick.askVolume1 == 0:
            self.gateway.writeLog(u'leg1:{0}涨停{1}，不合成价差Tick'.format(self.last_leg1_tick.vtSymbol,self.last_leg1_tick.bidPrice1))
            return
        if (self.last_leg1_tick.bidPrice1 == 0 or self.last_leg1_tick.askPrice1 == self.last_leg1_tick.lowerLimit)\
                and self.last_leg1_tick.bidVolume1 == 0:
            self.gateway.writeLog(u'leg1:{0}跌停{1}，不合成价差Tick'.format(self.last_leg1_tick.vtSymbol, self.last_leg1_tick.askPrice1))
            return
        if (self.last_leg2_tick.askPrice1 == 0 or self.last_leg2_tick.bidPrice1 == self.last_leg2_tick.upperLimit)\
                and self.last_leg2_tick.askVolume1 == 0:
            self.gateway.writeLog(u'leg2:{0}涨停{1}，不合成价差Tick'.format(self.last_leg2_tick.vtSymbol, self.last_leg2_tick.bidPrice1))
            return
        if (self.last_leg2_tick.bidPrice1 == 0 or self.last_leg2_tick.askPrice1 == self.last_leg2_tick.lowerLimit)\
                and self.last_leg2_tick.bidVolume1 == 0:
            self.gateway.writeLog(u'leg2:{0}跌停{1}，不合成价差Tick'.format(self.last_leg2_tick.vtSymbol, self.last_leg2_tick.askPrice1))
            return

        if self.tradingDay != tick.tradingDay:
            self.tradingDay = tick.tradingDay
            self.spread_high = None
            self.spread_low = None
            self.ratio_high = None
            self.ratio_low = None

        if self.is_spread:
            spread_tick = VtTickData()
            spread_tick.vtSymbol = self.vtSymbol
            spread_tick.symbol = self.vtSymbol
            spread_tick.gatewayName = tick.gatewayName
            spread_tick.exchange = tick.exchange
            spread_tick.tradingDay = tick.tradingDay

            spread_tick.datetime = tick.datetime
            spread_tick.date = tick.date
            spread_tick.time = tick.time

            # 叫卖价差=leg1.askPrice1 * 配比 - leg2.bidPrice1 * 配比，volume为两者最小
            spread_tick.askPrice1 = roundToPriceTick(priceTick=self.minDiff,
                                                     price =self.last_leg1_tick.askPrice1 * self.leg1_ratio - self.last_leg2_tick.bidPrice1 * self.leg2_ratio)
            spread_tick.askVolume1 = min(self.last_leg1_tick.askVolume1, self.last_leg2_tick.bidVolume1)

            # 叫买价差=leg1.bidPrice1 * 配比 - leg2.askPrice1 * 配比，volume为两者最小
            spread_tick.bidPrice1 = roundToPriceTick(priceTick=self.minDiff,
                                                     price=self.last_leg1_tick.bidPrice1 * self.leg1_ratio - self.last_leg2_tick.askPrice1 * self.leg2_ratio)
            spread_tick.bidVolume1 = min(self.last_leg1_tick.bidVolume1, self.last_leg2_tick.askVolume1)

            # 最新价
            spread_tick.lastPrice = roundToPriceTick(priceTick=self.minDiff,
                                                     price=(spread_tick.askPrice1 + spread_tick.bidPrice1)/2)
            # 昨收盘价
            if self.last_leg2_tick.preClosePrice >0 and self.last_leg1_tick.preClosePrice > 0:
                spread_tick.preClosePrice = roundToPriceTick(priceTick=self.minDiff,
                                                     price=self.last_leg1_tick.preClosePrice * self.leg1_ratio - self.last_leg2_tick.preClosePrice * self.leg2_ratio)
            # 开盘价
            if self.last_leg2_tick.openPrice > 0 and self.last_leg1_tick.openPrice > 0:
                spread_tick.openPrice = roundToPriceTick(priceTick=self.minDiff,
                                                             price=self.last_leg1_tick.openPrice * self.leg1_ratio - self.last_leg2_tick.openPrice * self.leg2_ratio)
            # 最高价
            self.spread_high = spread_tick.askPrice1 if self.spread_high is None else max(self.spread_high,spread_tick.askPrice1)
            spread_tick.highPrice = self.spread_high

            # 最低价
            self.spread_low = spread_tick.bidPrice1 if self.spread_low is None else min(self.spread_low, spread_tick.bidPrice1)
            spread_tick.lowPrice = self.spread_low

            self.gateway.onTick(spread_tick)

        if self.is_ratio:
            ratio_tick = VtTickData()
            ratio_tick.vtSymbol = self.vtSymbol
            ratio_tick.symbol = self.vtSymbol
            ratio_tick.gatewayName = tick.gatewayName
            ratio_tick.exchange = tick.exchange
            ratio_tick.tradingDay = tick.tradingDay
            ratio_tick.datetime = tick.datetime
            ratio_tick.date = tick.date
            ratio_tick.time = tick.time

            # 比率tick
            ratio_tick.askPrice1 = roundToPriceTick(priceTick=self.minDiff,
                                                    price=100 * self.last_leg1_tick.askPrice1 * self.leg1_ratio / (self.last_leg2_tick.bidPrice1 * self.leg2_ratio))
            ratio_tick.askVolume1 = min(self.last_leg1_tick.askVolume1, self.last_leg2_tick.bidVolume1)

            ratio_tick.bidPrice1 = roundToPriceTick(priceTick=self.minDiff,
                                                    price=100 * self.last_leg1_tick.bidPrice1 * self.leg1_ratio/ (self.last_leg2_tick.askPrice1 * self.leg2_ratio))
            ratio_tick.bidVolume1 = min(self.last_leg1_tick.bidVolume1, self.last_leg2_tick.askVolume1)
            ratio_tick.lastPrice = roundToPriceTick(priceTick=self.minDiff,price=(ratio_tick.askPrice1 + ratio_tick.bidPrice1) / 2)

            # 昨收盘价
            if self.last_leg2_tick.preClosePrice >0 and self.last_leg1_tick.preClosePrice > 0:
                ratio_tick.preClosePrice = roundToPriceTick(priceTick=self.minDiff,
                                                     price=100*self.last_leg1_tick.preClosePrice * self.leg1_ratio/(self.last_leg2_tick.preClosePrice * self.leg2_ratio))
            # 开盘价
            if self.last_leg2_tick.openPrice > 0 and self.last_leg1_tick.openPrice > 0:
                ratio_tick.openPrice = roundToPriceTick(priceTick=self.minDiff,
                                                             price=100 * self.last_leg1_tick.openPrice * self.leg1_ratio / (self.last_leg2_tick.openPrice * self.leg2_ratio))
            # 最高价
            self.ratio_high = ratio_tick.askPrice1 if self.ratio_high is None else max(self.ratio_high,
                                                                                          ratio_tick.askPrice1)
            ratio_tick.highPrice = self.spread_high

            # 最低价
            self.ratio_low = ratio_tick.bidPrice1 if self.ratio_low is None else min(self.ratio_low,
                                                                                        ratio_tick.bidPrice1)
            ratio_tick.lowPrice = self.spread_low

            self.gateway.onTick(ratio_tick)

#----------------------------------------------------------------------
def test():
    """测试"""
    from qtpy import QtCore
    import sys

    def print_log(event):
        log = event.dict_['data']
        print(':'.join([log.logTime, log.logContent]))

    app = QtCore.QCoreApplication(sys.argv)

    eventEngine = EventEngine()
    eventEngine.register(EVENT_LOG, print_log)
    eventEngine.start()

    gateway = CtpGateway(eventEngine)
    gateway.debug_tick = True
    gateway.connect()

    # gateway.connect()
    auto_subscribe_symbols = ['m1909']
    for symbol in auto_subscribe_symbols:
        print(u'自动订阅合约:{}'.format(symbol))
        sub = VtSubscribeReq()
        sub.symbol = symbol
        gateway.subscribe(sub)
    gateway.connect()

    sys.exit(app.exec_())

if __name__ == '__main__':
    try:
        test()
    except Exception as ex:
        print(u'异常:{},{}'.format(str(ex), traceback.format_exc()))
    print('Finished')
