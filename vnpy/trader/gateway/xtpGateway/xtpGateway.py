# encoding: UTF-8

'''
vn.xtp的gateway接入
'''


import os
import json,copy
import traceback
from vnpy.api.xtp import *
from vnpy.trader.vtGateway import *
from vnpy.trader.vtFunction import getJsonPath, getTempPath
from vnpy.trader.vtUtility import BarGenerator
from pytdx.hq import TdxHq_API
from multiprocessing.dummy import Pool
from threading import Thread
from time import sleep


# 以下为一些VT类型和XTP类型的映射字典
#XTP_PRICE_TYPE是价格类型
#枚举值
# 1 XTP_PRICE_LIMIT 限价单-沪 / 深 / 沪期权（除普通股票业务外，其余业务均使用此种类型）
# 2 XTP_PRICE_BEST_OR_CANCEL 即时成交剩余转撤销，市价单-深 / 沪期权
# 3 XTP_PRICE_BEST5_OR_LIMIT 最优五档即时成交剩余转限价，市价单-沪
# 4 XTP_PRICE_BEST5_OR_CANCEL 最优5档即时成交剩余转撤销，市价单-沪深
# 5 XTP_PRICE_ALL_OR_CANCEL 全部成交或撤销,市价单-深 / 沪期权
# 6 XTP_PRICE_FORWARD_BEST 本方最优，市价单-深
# 7 XTP_PRICE_REVERSE_BEST_LIMIT 对方最优剩余转限价，市价单-深 / 沪期权
# 8 XTP_PRICE_LIMIT_OR_CANCEL 期权限价申报FOK
# 9 XTP_PRICE_TYPE_UNKNOWN 未知或者无效价格类型

# 价格类型映射
priceTypeMap = {}
priceTypeMap[PRICETYPE_LIMITPRICE] = 1
priceTypeMap[PRICETYPE_MARKETPRICE] = 4

priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()} 

# 方向类型映射
sideMap = {}
#sideMap[(DIRECTION_LONG, OFFSET_NONE)] = 1
sideMap[(DIRECTION_LONG, OFFSET_OPEN)] = 1
#sideMap[(DIRECTION_SHORT, OFFSET_NONE)] = 2
sideMap[(DIRECTION_SHORT, OFFSET_CLOSE)] = 2
#sideMap[(DIRECTION_LONG, OFFSET_OPEN)] = 3
sideMap[(DIRECTION_SHORT, OFFSET_OPEN)] = 4
sideMap[(DIRECTION_LONG, OFFSET_CLOSE)] = 5
#sideMap[(DIRECTION_SHORT, OFFSET_CLOSE)] = 6
sideMapReverse = {v: k for k, v in sideMap.items()}

# 交易所类型映射
exchangeMap = {}
exchangeMap[EXCHANGE_SSE] = 1
exchangeMap[EXCHANGE_SZSE] = 2
exchangeMap[EXCHANGE_UNKNOWN] = 3
exchangeMapReverse = {v:k for k,v in exchangeMap.items()}

# 市场类型映射
marketMap = {}
marketMap[EXCHANGE_UNKNOWN] = 0
marketMap[EXCHANGE_SZSE] = 1
marketMap[EXCHANGE_SSE] = 2
marketMapReverse = {v:k for k,v in marketMap.items()}

# 持仓类型映射
#posiDirectionMap = {}
#posiDirectionMap[DIRECTION_NET] = defineDict["THOST_FTDC_PD_Net"]
#posiDirectionMap[DIRECTION_LONG] = defineDict["THOST_FTDC_PD_Long"]
#posiDirectionMap[DIRECTION_SHORT] = defineDict["THOST_FTDC_PD_Short"]
#posiDirectionMapReverse = {v:k for k,v in posiDirectionMap.items()}

# 产品类型映射
productClassMapReverse = {}
productClassMapReverse[0] = PRODUCT_EQUITY
productClassMapReverse[1] = PRODUCT_INDEX
productClassMapReverse[2] = PRODUCT_EQUITY
productClassMapReverse[3] = PRODUCT_EQUITY
productClassMapReverse[4] = PRODUCT_UNKNOWN

# 委托状态映射
statusMapReverse = {}
statusMapReverse[0] = STATUS_UNKNOWN
statusMapReverse[1] = STATUS_ALLTRADED
statusMapReverse[2] = STATUS_PARTTRADED
statusMapReverse[3] = STATUS_CANCELLED
statusMapReverse[4] = STATUS_NOTTRADED
statusMapReverse[5] = STATUS_CANCELLED
statusMapReverse[6] = STATUS_REJECTED
statusMapReverse[7] = STATUS_UNKNOWN

# 业务类型映射
#businessMap = {}
#businessMap[BUSINESS_CASH] = 0
#businessMap[BUSINESS_IPO] = 1
#businessMap[BUSINESS_REPO] = 2
#businessMap[BUSINESS_ETF] = 3
#businessMap[BUSINESS_MARGIN] = 4
#businessMap[BUSINESS_DESIGNATION] = 5
#businessMap[BUSINESS_ALLOTMENT] = 6
#businessMap[BUSINESS_STRUCTURED_FUND_PURCHASE_REDEMPTION] = 7
#businessMap[BUSINESS_STRUCTURED_FUND_SPLIT_MERGE] = 8
#businessMap[BUSINESS_MONEY_FUND] = 9
#businessMap[BUSINESS_UNKNOWN] = 10
#businessMapReverse = {v:k for k,v in businessMap.items()}


# tdx市场类型映射  # 0 - 深圳， 1 - 上海
tdxMarketMap = {}
tdxMarketMap[EXCHANGE_SZSE] = 0
tdxMarketMap[EXCHANGE_SSE] = 1
tdxMarketMapReverse = {v:k for k,v in tdxMarketMap.items()}

########################################################################
class XtpGateway(VtGateway):
    """XTP接口"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, gatewayName='XTP'):
        """Constructor"""
        super(XtpGateway, self).__init__(eventEngine, gatewayName)
        
        self.mdApi = XtpMdApi(self)     # 行情API
        self.tdApi = XtpTdApi(self)     # 交易API

        self.tdxApi = None              # 通达信股票行情API
        self.tdx_pool_count = 3         # 通达信行情连接池

        self.mdConnected = False        # 行情API连接状态，登录完成后为True
        self.tdConnected = False        # 交易API连接状态
        self.tdxConnected = False       # 通达信股票行情API得连接状态
        
        self.qryEnabled = False         # 是否要启动循环查询

        self.subscribedSymbols = set()  # 已订阅股票代码

        self.fileName = self.gatewayName + '_connect.json'
        self.filePath = getJsonPath(self.fileName, __file__)

        # 调试信息：显示tick，显示原始数据
        self.debug_display_tick = False
        self.debug_raw_data = False
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
        f.close()
        try:
            userID = str(setting['userID'])
            password = str(setting['password'])
            clientID = int(setting['clientID'])
            softwareKey = str(setting['softwareKey'])
            tdAddress = str(setting['tdAddress'])
            tdPort = int(setting['tdPort'])
            mdAddress = str(setting['mdAddress'])
            mdPort = int(setting['mdPort'])

            self.writeLog(u'使用行情:{}:{}'.format(mdAddress, mdPort))
            self.writeLog(u'使用交易:{}:{}'.format(tdAddress, tdPort))

            self.debug_display_tick = setting.get('debug_display_tick',False)
            self.debug_raw_data = setting.get('debug_raw_data',False)

            # 获取tdx配置
            tdx_conf = setting.get('tdx', None)
            if tdx_conf is not None and isinstance(tdx_conf, dict):
                if self.tdxApi is None:
                    self.writeLog(u'通达信接口未实例化，创建实例')
                    self.tdxApi = TdxMdApi(self)  # 通达信行情API
                ip = tdx_conf.get('ip', None)
                if ip is not None:
                    self.writeLog(u'使用配置文件的tdx服务器:{}'.format(ip))
                    self.tdxApi.best_ip = copy.copy(ip)

                # 获取通达信得缺省连接池数量
                self.tdx_pool_count = tdx_conf.get('pool_count', self.tdx_pool_count)

        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return            
        
        # 创建行情和交易接口对象        
        self.mdApi.connect(userID, password, clientID, mdAddress, mdPort)
        self.tdApi.connect(userID, password, clientID, softwareKey, tdAddress, tdPort)
        
        # 初始化并启动查询
        self.initQuery()

        for req in list(self.subscribedSymbols):
            if self.tdxApi is not None:
                self.writeLog(u'启用tdx，连接通达信行情服务器')
                self.tdxApi.connect(self.tdx_pool_count)
                self.tdxApi.subscribe(req)
            else:
                self.mdApi.subscribe(req)
    
    # ----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅行情"""
        if len(subscribeReq.symbol)==0:
            return

        if self.tdxApi is not None:
            self.writeLog(u'启用tdx，连接通达信行情服务器')
            self.tdxApi.connect(self.tdx_pool_count)
            self.tdxApi.subscribe(subscribeReq)
        else:
            self.mdApi.subscribe(subscribeReq)

        self.subscribedSymbols.add(subscribeReq)

        if subscribeReq.is_bar:
            self.subscribeBar(subscribeReq)

    def subscribeBar(self,subscribeReq):
        """订阅1分钟行情"""

        symbol = subscribeReq.symbol
        if symbol in self.klines:
            return

        # 创建1分钟bar产生器
        self.writeLog(u'创建:{}的一分钟行情'.format(symbol))
        bg = BarGenerator(onBar=self.onBar)
        self.klines.update({symbol:bg})

    #----------------------------------------------------------------------
    def unSubscribe(self, subscribeReq):
        """"""
        self.mdApi.unSubscribe(subscribeReq)
        
    # ----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        return self.tdApi.sendOrder(orderReq)
        
    # ----------------------------------------------------------------------
    def cancelOrder(self, cancelOrderReq):
        """撤单"""
        self.tdApi.sendCancel(cancelOrderReq)
        
    # ----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        if self.tdConnected:
            self.tdApi.qryAccount()
        
    # ----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        if self.tdConnected:    
            self.tdApi.qryPosition()
        
    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        if self.mdConnected:
            self.mdApi.close()
        if self.tdConnected:
            self.tdApi.close()

        if self.tdxApi is not None:
            self.writeLog(u'断开通达信行情API')
            tmp1 = self.tdxApi
            self.tdxApi.connection_status = False
            self.tdxApi = None
            tmp1.close()
            self.tdxConnected = False

    # ----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryAccount, self.qryPosition]
            
            self.qryCount = 0           # 查询触发倒计时
            self.qryTrigger = 2         # 查询触发点
            self.qryNextFunction = 0    # 上次运行的查询函数索引
            
            self.startQuery()
    
    # ----------------------------------------------------------------------
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
    
    # ----------------------------------------------------------------------
    def startQuery(self):
        """启动连续查询"""
        self.eventEngine.register(EVENT_TIMER, self.query)
    
    # ----------------------------------------------------------------------
    def setQryEnabled(self, qryEnabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qryEnabled

    def checkStatus(self):
        if self.tdxApi is not None:
            self.tdxApi.checkStatus()

        self.mdApi.checkStatus()

        return True

########################################################################
class XtpMdApi(QuoteApi):
    """XTP行情API实现"""

    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(XtpMdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.subscribedSymbols = set()      # 已订阅合约代码        
        
        self.userID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.address = EMPTY_STRING         # 服务器地址
        self.port = EMPTY_INT               # 服务器端口

        self.last_tick_dt = None
        self.had_disconnected = False

    #----------------------------------------------------------------------
    def onDisconnected(self, reason):
        """连接断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.mdConnected = False
        self.had_disconnected = True

        content = (u'行情服务器连接断开，原因：%s' %reason)
        self.writeLog(content)

    def reconnect(self):
        # 重新连接
        n = self.login(self.address, self.port, self.userID, self.password, 1)
        if not n:
            self.connectionStatus = True
            self.loginStatus = True
            self.gateway.mdConnected = True
            self.writeLog(u'行情服务器登录成功')
            self.reSubscribe()
            # 订阅上交所/深交所的全行情
            self.writeLog(u'订阅上交所/深交所的全行情')
            self.queryAllTickers(1)  # 上交所
            self.queryAllTickers(2)  # 深交所
        else:
            self.writeLog(u'行情服务器登录失败，原因:%s' %n)

    def checkStatus(self):
        # self.writeLog(u'检查tdx接口状态')
        if len(self.subscribedSymbols) == 0:
            return

        # 若还没有启动连接，就启动连接
        if self.last_tick_dt is not None:
            over_time = (datetime.now() - self.last_tick_dt).total_seconds() > 60
        else:
            over_time = False

        if self.had_disconnected and (not self.connectionStatus or over_time):
            self.writeLog(u'XTP没有行情连接，就启动连接')
            self.reconnect()

    #----------------------------------------------------------------------
    def onError(self, error):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['error_id']
        err.errorMsg = error['error_msg'] # .decode('gbk')
        self.gateway.onError(err)        
        
    #----------------------------------------------------------------------
    def onSubMarketData(self, data, error, last):
        """订阅行情回报"""
        if self.gateway.debug_raw_data:
            print(u'onSubMarketData')
            print(self.gateway.printDict(data))
        
    #----------------------------------------------------------------------
    def onUnSubMarketData(self, data, error, last):
        """退订行情回报"""
        if self.gateway.debug_raw_data:
            print(u'onSubMarketData')
            print(self.gateway.printDict(data))

    #----------------------------------------------------------------------
    def onDepthMarketData(self, *args):
        """行情推送"""
        if self.gateway.debug_raw_data:
            print(u'onDepthMarketData')
            print(self.gateway.printDict(args[0]))

        if len(args)<1:
            return
        try:
            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            data = args[0]

            tick.symbol = data['ticker']
            tick.exchange = exchangeMapReverse.get(data['exchange_id'], EXCHANGE_UNKNOWN)
            #tick.vtSymbol = '.'.join([tick.symbol, tick.exchange])
            tick.vtSymbol = tick.symbol

            tick.lastPrice = data['last_price']
            tick.volume = data['qty']
            #tick.openInterest = data['open_interest']  # 股票tick没有持仓总量

            timestamp = str(data['data_time'])
            tick.date = timestamp[:4] + '-' + timestamp[4:6] + '-' +  timestamp[6:8]
            tick.time = '%s:%s:%s.%s' %(timestamp[8:10], timestamp[10:12], timestamp[12:14], timestamp[14])
            tick.datetime = datetime.strptime('{} {}'.format(tick.date,tick.time),'%Y-%m-%d %H:%M:%S.%f')
            tick.tradingDay = tick.date
            tick.openPrice = data['open_price']
            tick.highPrice = data['high_price']
            tick.lowPrice = data['low_price']
            tick.preClosePrice = data['pre_close_price']

            tick.upperLimit = data['upper_limit_price']
            tick.lowerLimit = data['lower_limit_price']

            tick.bidPrice1, tick.bidPrice2, tick.bidPrice3, tick.bidPrice4, tick.bidPrice5 = data['bid'][0:5]
            tick.askPrice1, tick.askPrice2, tick.askPrice3, tick.askPrice4, tick.askPrice5 = data['ask'][0:5]
            tick.bidVolume1, tick.bidVolume2, tick.bidVolume3, tick.bidVolume4, tick.bidVolume5 = data['bid_qty'][0:5]
            tick.askVolume1, tick.askVolume2, tick.askVolume3, tick.askVolume4, tick.askVolume5 = data['ask_qty'][0:5]

            self.last_tick_dt=tick.datetime

            # 丢弃非交易时间的tick
            if tick.datetime.hour not in [9,10,11,13,14]:
                return
            if tick.datetime.hour == 9 and tick.datetime.minute < 15:
                return

            if self.gateway.debug_display_tick:
                self.writeLog('xtp:{},{},{},{},{},{},{},{},{},{},{},{},{},{}'.format(tick.gatewayName, tick.symbol,
                                                                                 tick.exchange, tick.vtSymbol,
                                                                                 tick.datetime, tick.tradingDay,
                                                                                 tick.openPrice, tick.highPrice,
                                                                                 tick.lowPrice, tick.preClosePrice,
                                                                                 tick.bidPrice1,
                                                                                 tick.bidVolume1, tick.askPrice1,
                                                                                 tick.askVolume1))

            self.gateway.onTick(tick)

            # 推送Bar
            if tick.vtSymbol in self.gateway.klines:
                kline = self.gateway.klines.get(tick.vtSymbol)
                kline.updateTick(copy.copy(tick))

        except Exception as ex:
            self.gateway.writeError(u'onDepthMarketData异常：{}，{}'.format(str(ex),traceback.format_exc()))

        #print(u'onDepthMarketData finished')
    #----------------------------------------------------------------------
    def onQueryAllTickers(self, data, error, last):
        """合约信息推送"""
        if self.gateway.debug_raw_data:
            print(u'onQueryAllTickers')
            print(self.gateway.printDict(data))

        if error and error.get('error_id',None) is not None:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error.get('error_id')
            err.errorMsg = error.get('error_msg',EMPTY_STRING)  #.decode('gbk')
            self.gateway.onError(err)
            return

        try:
            contract = VtContractData()
            contract.gatewayName = self.gatewayName

            contract.symbol = data.get('ticker','ticker')
            contract.exchange = exchangeMapReverse.get(data.get('exchange_id',0), EXCHANGE_UNKNOWN)
            contract.vtSymbol = contract.symbol   # '.'.join([contract.symbol, contract.exchange])

            contract.name = data.get('ticker_name','ticker_name')  #.decode('UTF-8')
            contract.size = 1
            contract.priceTick = data.get('price_tick',0.01)
            contract.productClass = productClassMapReverse.get(data.get('ticker_type',None), PRODUCT_UNKNOWN)

            self.gateway.onContract(contract)
        except Exception as ex:
            self.gateway.writeError(u'onQueryAllTickers Exception:{},{}'.format(str(ex),traceback.format_exc()))

    #----------------------------------------------------------------------
    def onSubOrderBook(self, data, error, last):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onSubOrderBook')
            print(self.gateway.printDict(data))
        
    #----------------------------------------------------------------------
    def onUnSubOrderBook(self, data, error, last):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onUnSubOrderBook')
            print(self.gateway.printDict(data))
    #----------------------------------------------------------------------
    def onOrderBook(self, data):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onOrderBook')
            print(self.gateway.printDict(data))
    #----------------------------------------------------------------------
    def onSubTickByTick(self, data, error, last):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onSubTickByTick')
            print(self.gateway.printDict(data))
    #----------------------------------------------------------------------
    def onUnSubTickByTick(self, data, error, last):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onUnSubTickByTick')
            print(self.gateway.printDict(data))
    #----------------------------------------------------------------------
    def onTickByTick(self, data):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onTickByTick')
            print(self.gateway.printDict(data))

    #----------------------------------------------------------------------
    def onSubscribeAllMarketData(self, error):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onSubscribeAllMarketData')
            print(self.gateway.printDict(error))
        
    #----------------------------------------------------------------------
    def onUnSubscribeAllMarketData(self, error):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onUnSubscribeAllMarketData')
            print(self.gateway.printDict(error))
        
    #----------------------------------------------------------------------
    def onSubscribeAllOrderBook(self, error):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onSubscribeAllOrderBook')
            print(self.gateway.printDict(error))
        
    #----------------------------------------------------------------------
    def onUnSubscribeAllOrderBook(self, error):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onUnSubscribeAllOrderBook')
            print(self.gateway.printDict(error))
        
    #----------------------------------------------------------------------
    def onSubscribeAllTickByTick(self, error):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onSubscribeAllTickByTick')
            print(self.gateway.printDict(error))
        
    #----------------------------------------------------------------------
    def onUnSubscribeAllTickByTick(self, error):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onUnSubscribeAllTickByTick')
            print(self.gateway.printDict(error))
        
    #----------------------------------------------------------------------
    def onQueryTickersPriceInfo(self, data, error, last):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onQueryTickersPriceInfo')
            print(self.gateway.printDict(data))
            print(self.gateway.printDict(error))

    #----------------------------------------------------------------------
    def connect(self, userID, password, clientID, address, port):
        """初始化连接"""
        self.userID = userID                # 账号
        self.password = password            # 密码
        self.address = address              # 服务器地址
        self.port = port                    # 端口号
        try:
            # 如果尚未建立服务器连接，则进行连接
            if not self.connectionStatus:
                path = os.getcwd() + '/temp/' + self.gatewayName + '/'
                if not os.path.exists(path):
                    os.makedirs(path)
                self.createQuoteApi(clientID, path)

                # 1 TCP；2：UDP
                n = self.login(address, port, userID, password, 1)
                if not n:
                    self.connectionStatus = True
                    self.loginStatus = True
                    self.gateway.mdConnected = True
                    self.writeLog(u'行情服务器登录成功')

                    self.writeLog(u'查询合约信息')
                    self.queryAllTickers(1)         # 上交所
                    self.queryAllTickers(2)         # 深交所

                    self.reSubscribe()
                else:
                    self.writeLog(u'行情服务器登录失败，原因:%s' %n)
        except Exception as ex:
            self.gateway.writeError(u'MdApi connect Exception:{} {}'.format(str(ex),traceback.format_exc()))

    def reSubscribe(self):
        """重新订阅行情"""
        for req in list(self.subscribedSymbols):
            if self.loginStatus:
                self.writeLog(u'重新订阅{}行情'.format(req.symbol))
                self.subscribeMarketData([{'ticker': str(req.symbol)}], 1,
                                         exchangeMap.get(req.exchange, 3))

    #----------------------------------------------------------------------
    def subscribe(self, subscribeReq):
        """订阅合约"""
        # 这里的设计是，如果尚未登录就调用了订阅方法
        # 则先保存订阅请求，登录完成后会自动订阅
        if '.' in subscribeReq.symbol:
            subscribeReq.symbol = subscribeReq.symbol.split('.')[0]

        if self.loginStatus:
            self.subscribeMarketData([{'ticker':str(subscribeReq.symbol)}],1,
                                     exchangeMap.get(subscribeReq.exchange,3))
        
        self.subscribedSymbols.add(subscribeReq)   
        
    #----------------------------------------------------------------------
    def unSubscribe(self, subscribeReq):
        """"""
        if self.loginStatus:
            self.unSubscribeMarketData(str(subscribeReq.symbol), 
                                       exchangeMap[subscribeReq.exchange])
    
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.writeLog(u'xtp gateway close')
        self.exit()
        
    #----------------------------------------------------------------------
    def writeLog(self, content):
        """记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)         

########################################################################
class XtpTdApi(TraderApi):
    """XTP交易API实现"""
    
    #----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(XtpTdApi, self).__init__()
        
        self.gateway = gateway                  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称
        
        self.reqID = EMPTY_INT              # 操作请求编号
        
        self.connectionStatus = False       # 连接状态
        self.loginStatus = False            # 登录状态
        
        self.userID = EMPTY_STRING          # 账号
        self.password = EMPTY_STRING        # 密码
        self.address = EMPTY_STRING         # 服务器地址
        self.port = EMPTY_INT               # 服务器端口
        self.clientID = EMPTY_INT           # 客户编号
        
        self.sessionID = EMPTY_INT          # 会话编号
        
        self.orderDict = {}                 # 委托缓存字典

    # ----------------------------------------------------------------------
    def onDisconnected(self, session, reason):
        """连接断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.tdConnected = False

        content = (u'交易服务器连接断开，原因：%s' %reason)
        self.writeLog(content)
        try:
            # 发起重新连接 1TCP，2UDP
            n = self.login(self.address, self.port, self.userID, self.password, 1)

            if n:
                self.sessionID = n
                self.connectionStatus = True
                self.loginStatus = True
                self.gateway.tdConnected = True
                self.writeLog(u'交易服务器登录成功，会话编号：%s' %n)
            else:
                self.writeLog(u'交易服务器登录失败')
        except Exception as ex:
            self.gateway.writeError(u'TdApi onDisconnected Exception:{} {}'.format(str(ex),traceback.format_exc()))
    # ----------------------------------------------------------------------
    def onError(self, error):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['error_id']
        err.errorMsg = error['error_msg']  #.decode('gbk')
        self.gateway.onError(err)    
        
    #----------------------------------------------------------------------
    def onOrderEvent(self, data, error, session):
        """委托数据回报"""
        print('onOrderEvent：{}'.format(data))
        try:
            orderID = str(data['order_xtp_id'])

            if orderID not in self.orderDict:
                # 创建报单数据对象
                order = VtOrderData()
                order.gatewayName = self.gatewayName

                # 保存代码和报单号
                order.symbol = data['ticker']
                order.exchange = marketMapReverse.get(data['market'], EXCHANGE_UNKNOWN)
                order.vtSymbol = order.symbol   # '.'.join([order.symbol, order.exchange])

                order.orderID = orderID
                order.vtOrderID = '.'.join([self.gatewayName, order.orderID])

                order.sessionID = self.sessionID
                order.frontID = self.getClientIDByXTPID(data['order_xtp_id'])

                # 开平和方向
                order.direction, order.offset = sideMapReverse.get(data['side'],
                                                                   (DIRECTION_UNKNOWN, OFFSET_UNKNOWN))

                # 不变的字段
                order.price = data['price']
                order.totalVolume = data['quantity']
                order.priceType = priceTypeMapReverse.get(data['price_type'], '')

                self.orderDict[orderID] = order
            else:
                order = self.orderDict[orderID]

            # 变化字段
            order.status = statusMapReverse.get(data['order_status'], STATUS_UNKNOWN)
            order.tradedVolume = data['qty_traded']

            if data['insert_time']:
                timestamp = str(data['insert_time'])
                order.orderTime = '%s:%s:%s' %(timestamp[8:10], timestamp[10:12], timestamp[12:14])

            if data['cancel_time']:
                timestamp = str(data['cancel_time'])
                order.cancelTime = '%s:%s:%s' %(timestamp[8:10], timestamp[10:12], timestamp[12:14])

            # 推送
            self.gateway.onOrder(order)

            # 错误信息
            if error['error_id']:
                err = VtErrorData()
                err.gatewayName = self.gatewayName
                err.errorID = error['error_id']
                err.errorMsg = u'委托号' + str(order.orderID) + ':' + error['error_msg']  # .decode('gbk')
                err.errorTime = order.orderTime
                self.gateway.onError(err)
        except Exception as ex:
            self.gateway.writeError(u'onOrderEvent Exception:{} {}'.format(str(ex),traceback.format_exc()))

    #----------------------------------------------------------------------
    def onTradeEvent(self, data, session):
        """成交推送"""
        #print('onTradeEvent：{}'.format(data))
        try:
            # 创建报单数据对象
            trade = VtTradeData()
            trade.gatewayName = self.gatewayName

            # 保存代码和报单号
            trade.symbol = data['ticker']
            trade.exchange = marketMapReverse.get(data['market'], EXCHANGE_UNKNOWN)
            trade.vtSymbol = trade.symbol   # '.'.join([trade.symbol, trade.exchange])

            trade.tradeID = str(data['exec_id'])
            trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])

            orderID = str(data['order_xtp_id'])
            trade.orderID = orderID
            trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])

            # 开平和方向
            trade.direction, trade.offset = sideMapReverse.get(data['side'],
                                                               (DIRECTION_UNKNOWN, OFFSET_UNKNOWN))

            # 价格、报单量等数值
            trade.price = data['price']
            trade.volume = data['quantity']

            if data['trade_time']:
                timestamp = str(data['trade_time'])
                trade.tradeTime = '%s:%s:%s' %(timestamp[8:10], timestamp[10:12], timestamp[12:14])

            # 推送
            self.gateway.onTrade(trade)

            # 更新委托数据
            order = self.orderDict.get(orderID, None)
            if (not order or
                order.status is STATUS_ALLTRADED or
                order.status is STATUS_CANCELLED):
                return

            order.tradedVolume += trade.volume

            if order.status is STATUS_NOTTRADED:
                order.status = STATUS_PARTTRADED

            self.gateway.onOrder(order)
        except Exception as ex:
            self.gateway.writeError(u'onTradeEvent Exception:{} {}'.format(str(ex),traceback.format_exc()))

    #----------------------------------------------------------------------
    def onCancelOrderError(self, data, error, session):
        """撤单错误回报"""
        print('onCancelOrderError')
        try:
            if error['error_id']:
                err = VtErrorData()
                err.gatewayName = self.gatewayName
                err.errorID = error['error_id']
                err.errorMsg = u'委托号' + str(data['order_xtp_id']) + ':' + error['error_msg']  # .decode('gbk')
                self.gateway.onError(err)
        except Exception as ex:
            self.gateway.writeError(u'onCancelOrderError Exception:{} {}'.format(str(ex), traceback.format_exc()))
    #----------------------------------------------------------------------
    def onQueryOrder(self, data, error, reqid, last, session):
        """委托查询回报"""
        print('onQueryOrder')
        
    #----------------------------------------------------------------------
    def onQueryTrade(self, data, error, reqid, last, session):
        """成交查询回报"""
        print('onQueryTrade')
        
    #----------------------------------------------------------------------
    def onQueryPosition(self, data, error, reqid, last, session):
        """查询持仓回报"""
        #print('onQueryPosition:{}'.format(data))
        try:

            pos = VtPositionData()
            pos.gatewayName = self.gatewayName

            # 保存代码
            pos.symbol = data['ticker']
            pos.exchange = marketMapReverse.get(data['market'], EXCHANGE_UNKNOWN)
            pos.vtSymbol = pos.symbol    # '.'.join([pos.symbol, pos.exchange])
            pos.name = data['ticker_name'] #.decode('UTF-8')

            # 方向和持仓冻结数量
            pos.direction = DIRECTION_LONG
            pos.position = data.get('total_qty',0)
            pos.frozen = pos.position - data.get('sellable_qty',0)
            pos.ydPosition = data.get('yesterday_position',0)
            pos.price = data.get('avg_price',0.0)

            # VT系统持仓名
            pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])

            # 推送
            self.gateway.onPosition(pos)
        except Exception as ex:
            self.gateway.writeError('onQueryPosition Exception:{},{}'.format(str(ex),traceback.format_exc()))
        
    #----------------------------------------------------------------------
    def onQueryAsset(self, data, error, reqid, last, session):
        """账户查询回报"""
        if self.gateway.debug_raw_data:
            print('onQueryAsset')
            print(self.gateway.printDict(data))

        try:
            account = VtAccountData()
            account.gatewayName = self.gatewayName

            # 账户代码
            account.accountID = self.userID
            account.vtAccountID = '.'.join([self.gatewayName, account.accountID])

            # 数值相关
            account.balance = float(data['total_asset'])
            account.available = float(data['buying_power'])
            account.commission = float(data['fund_buy_fee']) + float(data['fund_sell_fee'])

            # 推送
            self.gateway.onAccount(account)

        except Exception as ex:
            self.gateway.writeError('onQueryAsset Exception:{},{}'.format(str(ex), traceback.format_exc()))

    #----------------------------------------------------------------------
    def onQueryStructuredFund(self, data, error, reqid, last, session):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onQueryStructuredFund')
            print(self.gateway.printDict(data))
        
    #----------------------------------------------------------------------
    def onQueryFundTransfer(self, data, error, reqid, last, session):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onQueryFundTransfer')
            print(self.gateway.printDict(data))
        
    #----------------------------------------------------------------------
    def onFundTransfer(self, data, error, session):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onFundTransfer')
            print(self.gateway.printDict(data))
        
    #----------------------------------------------------------------------
    def onQueryETF(self, data, error, reqid, last, session):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onQueryETF')
            print(self.gateway.printDict(data))
        
    #----------------------------------------------------------------------
    def onQueryETFBasket(self, data, error, reqid, last, session):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onQueryETFBasket')
            print(self.gateway.printDict(data))
        
    #----------------------------------------------------------------------
    def onQueryIPOInfoList(self, data, error, reqid, last, session):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onQueryIPOInfoList')
            print(self.gateway.printDict(data))
        
    #----------------------------------------------------------------------
    def onQueryIPOQuotaInfo(self, data, error, reqid, last, session):
        """"""
        if self.gateway.debug_raw_data:
            print(u'onQueryIPOQuotaInfo')
            print(self.gateway.printDict(data))
           
    #----------------------------------------------------------------------
    def connect(self, userID, password, clientID, softwareKey, address, port):
        """初始化连接"""
        self.userID = userID                # 账号
        self.password = password            # 密码
        self.address = address              # 服务器地址
        self.port = port                    # 端口号
        self.clientID = clientID
        try:
            # 如果尚未建立服务器连接，则进行连接
            if not self.connectionStatus:
                path = os.getcwd() + '/temp/' + self.gatewayName + '/'
                if not os.path.exists(path):
                    os.makedirs(path)
                self.createTraderApi(clientID, path)

                # 设置软件编码，认证用
                self.setSoftwareKey(softwareKey)

                # 设置订单和成交回报重传模式
                self.subscribePublicTopic(0)

                # 发起登录
                n = self.login(address, port, userID, password, 1)

                if n:
                    self.sessionID = n
                    self.connectionStatus = True
                    self.loginStatus = True
                    self.gateway.tdConnected = True
                    self.writeLog(u'交易服务器登录成功，会话编号：%s' %n)
                else:
                    self.writeLog(u'交易服务器登录失败')
        except Exception as ex:
            self.gateway.writeError(u'TdApi connect Exception:{} {}'.format(str(ex), traceback.format_exc()))

    #----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户"""
        if self.sessionID:
            self.reqID += 1
            self.queryAsset(self.sessionID, self.reqID)
        
    #----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        if self.sessionID:
            self.reqID += 1
            self.queryPosition('', self.sessionID, self.reqID)
        
    #----------------------------------------------------------------------
    def sendOrder(self, orderReq):
        """发单"""
        if '.' in orderReq.symbol:
            orderReq.symbol = orderReq.symbol.split('.')[0]

        req = {}
        req['ticker'] = orderReq.symbol
        req['price'] = orderReq.price
        # 这里若下单是股票需要强制转化为int
        req['quantity'] = int(orderReq.volume)
        req['price_type'] = priceTypeMap.get(orderReq.priceType, 0)
        req['market'] = marketMap.get(orderReq.exchange, 0)
        req['business_type'] = 0        # 目前只支持买卖业务

        # 目前尚未支持衍生品交易，因此不适用
        #req['side'] = sideMap.get((orderReq.direction, OFFSET_NONE), 0)
        if orderReq.direction == DIRECTION_LONG:
            req['side'] = 1
            req['position_effect'] = 1
        else:
            req['side'] = 2
            req['position_effect'] = 2

        if self.gateway.debug_raw_data:
            print(u'xtp send order:{}'.format(self.gateway.printDict(req)))

        # 发出委托
        orderID = str(self.insertOrder(req, self.sessionID))        
        vtOrderID = '.'.join([self.gatewayName, orderID])

        order = VtOrderData()

        order.gatewayName = self.gatewayName
        order.symbol = orderReq.symbol
        order.exchange = orderReq.exchange
        order.vtSymbol = orderReq.symbol  # + '.' +order.exchange
        order.orderID = orderID
        order.vtOrderID = vtOrderID

        order.direction = orderReq.direction
        order.offset = OFFSET_OPEN if order.direction == DIRECTION_LONG else OFFSET_CLOSE
        order.price =  orderReq.price
        order.totalVolume = int(orderReq.volume)
        order.tradedVolume = 0
        order.status = STATUS_UNKNOWN
        order.orderTime = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

        self.gateway.onOrder(order)

        # 返回订单号（字符串），便于某些算法进行动态管理
        return vtOrderID
    
    #----------------------------------------------------------------------
    def sendCancel(self, cancelOrderReq):
        """撤单，因为cancelOrder的命名已经被原生接口使用了，所以改为sendCancel"""
        self.cancelOrder(int(cancelOrderReq.orderID), self.sessionID)
        
    #----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()

    #----------------------------------------------------------------------
    def writeLog(self, content):
        """记录日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)   


class TdxMdApi():
    """
    通达信股票数据行情API实现
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

        self.pool = None                 # 线程池

        self.best_ip = None     #'180.153.39.51'
        self.api_dict = {}  # API 的连接会话对象字典
        self.last_tick_dt = {} # 记录该会话对象的最后一个tick时间

        self.instrument_count = 50000

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

        self.writeLog(u'开始选择通达信股票行情服务器')
        # 选取最佳服务器
        from pytdx.util.best_ip import select_best_ip
        if self.best_ip is None:
            self.best_ip = select_best_ip()
            print(u'best_ip:{}'.format(self.best_ip))

        # 创建n个api连接对象实例
        for i in range(n):
            try:
                api = TdxHq_API( heartbeat=True, auto_retry=True,raise_exception=True)
                api.connect(self.best_ip, 7709)
                # 尝试获取市场合约统计
                c =api.get_security_count(0)
                if c is None or c < 10:
                    err_msg = u'该服务器IP {}/{}无响应'.format(self.best_ip,7709)
                    err = VtErrorData()
                    err.gatewayName = self.gatewayName
                    err.errorID = -1
                    err.errorMsg = err_msg
                    self.gateway.onError(err)
                else:
                    self.writeLog(u'创建第{}个tdx股票连接'.format(i+1))
                    self.api_dict[i] = api
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
            self.writeLog(u'重新选择通达信股票行情服务器')
            # 选取最佳服务器
            from pytdx.util.best_ip import select_best_ip
            self.best_ip = select_best_ip()
            print(u'best_ip:{}'.format(self.best_ip))

            api = TdxHq_API(heartbeat=True, auto_retry=True)
            api.connect(self.best_ip,709)
            # 尝试获取市场合约统计
            c = api.get_security_count(0)
            if c is None or c < 10:
                err_msg = u'该服务器IP {}无响应'.format(self.best_ip)
                err = VtErrorData()
                err.gatewayName = self.gatewayName
                err.errorID = -1
                err.errorMsg = err_msg
                self.gateway.onError(err)
            else:
                self.writeLog(u'重新创建第{}个tdx股票连接'.format(i + 1))
                self.api_dict[i] = api
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
        self.writeLog(u'通达信行情订阅 {}'.format(str(vn_symbol)))

        if len(vn_symbol)==0:
            return

        tdx_code = vn_symbol.split('.')[0]
        self.writeLog(u'{}=>{}'.format(vn_symbol,tdx_code))
        self.symbol_vn_dict[tdx_code] = vn_symbol

        if tdx_code not in self.registed_symbol_set:
            self.registed_symbol_set.add(tdx_code)

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

        self.writeLog(u'tdx接口状态正常')

    def qryInstrument(self):
        """
        查询/更新股票信息
        :return:
        """
        if not self.connection_status:
            return

        api = self.api_dict.get(0)
        if api is None:
            self.writeLog(u'取不到api连接，更新合约信息失败')
            return

        for market_id in tdxMarketMap.values():
            exchange = tdxMarketMapReverse.get(market_id)
            self.writeLog(u'查询{}的所有股票清单'.format(exchange))
            start_no = 0
            while(True):
                # 取得所有的合约信息
                stocks = api.get_security_list(market_id,start_no)
                stocks_len = len(stocks)
                if stocks_len == 0:
                    break
                start_no += stocks_len

                if start_no > 15000:
                    break

                for stock in stocks:
                    #OrderedDict([('code', '880643'),
                    #             ('volunit', 100),
                    #             ('decimal_point', 2),
                    #             ('name', '食品加工'),
                    #             ('pre_close', 2158.570068359375)]),
                    tdx_symbol = stock.get('code', None)
                    self.symbol_exchange_dict[tdx_symbol] = exchange
            self.writeLog(u'{}下一共:{}个代码'.format(exchange,start_no))

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

    def __select_market_code(self,code):

        code = str(code)
        if len(code)<3:
            self.writeLog(u'代码{}不足长度:3'.format(code))
            return 0
        if code[0] in ['5', '6', '9'] or code[:3] in ["009", "126", "110", "201", "202", "203", "204"]:
            return 1
        return 0

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

        market_id = self.symbol_market_dict.get(symbol,self.__select_market_code(symbol))
        #self.writeLog(u'tdx[{}] get_security_quotes:({},{})'.format(i,market_id, symbol))
        rt_list = []
        try:
            rt_list = api.get_security_quotes([(market_id,symbol)])
        except Exception as ex:
            self.writeLog(u'获取行情异常:{}'.format(str(ex)))
        if len(rt_list) == 0:
            self.writeLog(u'tdx[{}]: rt_list为空'.format(i))
            return
        #else:
        #    self.writeLog(u'tdx[{}]: rt_list数据:{}'.format(i, rt_list))
        if i in self.last_tick_dt:
            self.last_tick_dt[i] = datetime.now()

        for d in list(rt_list):
            # 忽略成交量为0的无效单合约tick数据
            if d.get('cur_vol', 0) <= 0:
                self.writeLog(u'忽略成交量为0的无效单合约tick数据:{}'.format(d))
                continue

            code = d.get('code',None)
            if symbol != code and code is not None:
                #self.writeLog(u'忽略合约{} {} 不一致的tick数据:{}'.format(symbol,d.get('code'),rt_list))
                #continue
                symbol = code

            tick = VtTickData()
            tick.gatewayName = self.gatewayName

            tick.symbol = self.symbol_vn_dict.get(symbol,symbol)
            tick.symbol = tick.symbol.upper()
            exchange = self.symbol_exchange_dict.get(symbol)
            if exchange is None:
                market_id = self.__select_market_code(symbol)
                exchange = tdxMarketMapReverse.get(market_id)
                self.symbol_exchange_dict.update({symbol:exchange})
            tick.exchange = exchange
            tick.vtSymbol = tick.symbol

            tick.preClosePrice = d.get('last_close')
            tick.highPrice = d.get('high')
            tick.openPrice = d.get('open')
            tick.lowPrice = d.get('low')
            tick.lastPrice = d.get('price')

            tick.volume = d.get('vol',0)
            tick.lastVolume = d.get('cur_vol',0)

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
            tick.tradingDay = tick.date

            # 指数没有涨停和跌停，就用昨日收盘价正负10%
            tick.upperLimit = tick.preClosePrice * 1.1
            tick.lowerLimit = tick.preClosePrice * 0.9

            # 5档行情
            tick.bidPrice1 = d.get('bid1')
            tick.bidVolume1 = d.get('bid_vol1')
            tick.bidPrice2 = d.get('bid2')
            tick.bidVolume2 = d.get('bid_vol2')
            tick.bidPrice3 = d.get('bid3')
            tick.bidVolume3 = d.get('bid_vol3')
            tick.bidPrice4 = d.get('bid4')
            tick.bidVolume4 = d.get('bid_vol4')
            tick.bidPrice5 = d.get('bid5')
            tick.bidVolume5 = d.get('bid_vol5')

            tick.askPrice1 = d.get('ask1')
            tick.askVolume1 = d.get('ask_vol1')
            tick.askPrice2 = d.get('ask2')
            tick.askVolume2 = d.get('ask_vol12')
            tick.askPrice3 = d.get('ask3')
            tick.askVolume3 = d.get('ask_vol3')
            tick.askPrice4 = d.get('ask4')
            tick.askVolume4 = d.get('ask_vol4')
            tick.askPrice5 = d.get('ask5')
            tick.askVolume5 = d.get('ask_vol5')

            if tick.datetime.hour not in [9,10,11,13,14]:
                return
            if tick.datetime.hour == 9 and tick.datetime.minute < 15:
                return
            if self.gateway.debug_display_tick:
                self.writeLog('tdx:{},{},{},{},{},{},{},{},{},{},{},{},{},{}'.format(tick.gatewayName, tick.symbol,
                                                                                 tick.exchange, tick.vtSymbol,
                                                                                 tick.datetime, tick.tradingDay,
                                                                                 tick.openPrice, tick.highPrice,
                                                                                 tick.lowPrice, tick.preClosePrice,
                                                                                 tick.bidPrice1,
                                                                                 tick.bidVolume1, tick.askPrice1,
                                                                                 tick.askVolume1))
                self.gateway.writeLog(
                'ask2:{},a_vol2:{},bid2:{},b_vol2:{}'.format(tick.askPrice2, tick.askVolume2, tick.bidPrice2,
                                                             tick.bidVolume2))
            self.symbol_tick_dict[symbol] = tick

            self.gateway.onTick(tick)

            # 推送Bar
            if tick.vtSymbol in self.gateway.klines:
                kline = self.gateway.klines.get(tick.vtSymbol)
                kline.updateTick(copy.copy(tick))

    # ----------------------------------------------------------------------
    def writeLog(self, content):
        """发出日志"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = content
        self.gateway.onLog(log)

    def writeError(self,content):
        self.gateway.writeError(content)