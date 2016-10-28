# -*- coding: utf-8 -*-

"""
vn.ctp的gateway接入

考虑到现阶段大部分CTP中的ExchangeID字段返回的都是空值
vtSymbol直接使用symbol
"""

import json
import os
from copy import copy

from vnpy.ext.vnctpmd import MdApi
from vnpy.ext.vnctptd import TdApi

from ctpDataType import *
from vnpy.utils.vtFunction import findConfPath, findTempPath
from vnpy.utils.vtGateway import *

# 以下为一些VT类型和CTP类型的映射字典
# 价格类型映射
priceTypeMap = {
    PRICETYPE_LIMITPRICE: defineDict["THOST_FTDC_OPT_LimitPrice"],
    PRICETYPE_MARKETPRICE: defineDict["THOST_FTDC_OPT_AnyPrice"]
}
priceTypeMapReverse = {v: k for k, v in priceTypeMap.items()}

# 方向类型映射
directionMap = {
    DIRECTION_LONG: defineDict['THOST_FTDC_D_Buy'],
    DIRECTION_SHORT: defineDict['THOST_FTDC_D_Sell']
}
directionMapReverse = {v: k for k, v in directionMap.items()}

# 开平类型映射
offsetMap = {
    OFFSET_OPEN: defineDict['THOST_FTDC_OF_Open'],
    OFFSET_CLOSE: defineDict['THOST_FTDC_OF_Close'],
    OFFSET_CLOSETODAY: defineDict['THOST_FTDC_OF_CloseToday'],
    OFFSET_CLOSEYESTERDAY: defineDict['THOST_FTDC_OF_CloseYesterday']
}
offsetMapReverse = {v: k for k, v in offsetMap.items()}

# 交易所类型映射
exchangeMap = {
    EXCHANGE_CFFEX: 'CFFEX',
    EXCHANGE_SHFE: 'SHFE',
    EXCHANGE_CZCE: 'CZCE',
    EXCHANGE_DCE: 'DCE',
    EXCHANGE_SSE: 'SSE',
    EXCHANGE_UNKNOWN: ''
}
exchangeMapReverse = {v: k for k, v in exchangeMap.items()}

# 持仓类型映射
posiDirectionMap = {
    DIRECTION_NET: defineDict["THOST_FTDC_PD_Net"],
    DIRECTION_LONG: defineDict["THOST_FTDC_PD_Long"],
    DIRECTION_SHORT: defineDict["THOST_FTDC_PD_Short"]
}
posiDirectionMapReverse = {v: k for k, v in posiDirectionMap.items()}

# 产品类型映射
productClassMap = {
    PRODUCT_FUTURES: defineDict["THOST_FTDC_PC_Futures"],
    PRODUCT_OPTION: defineDict["THOST_FTDC_PC_Options"],
    PRODUCT_COMBINATION: defineDict["THOST_FTDC_PC_Combination"]
}
productClassMapReverse = {v: k for k, v in productClassMap.items()}


########################################################################
class CtpGateway(VtGateway):
    """CTP接口"""

    # ----------------------------------------------------------------------
    def __init__(self, event_engine, gateway_name='CTP'):
        """Constructor"""
        super(CtpGateway, self).__init__(event_engine, gateway_name)

        self.mdApi = CtpMdApi(self)  # 行情API
        self.tdApi = CtpTdApi(self)  # 交易API

        self.mdConnected = False  # 行情API连接状态，登录完成后为True
        self.tdConnected = False  # 交易API连接状态

        self.qryEnabled = False  # 是否要启动循环查询

        self.qryFunctionList = []

        self.qryCount = 0  # 查询触发倒计时
        self.qryTrigger = 2  # 查询触发点
        self.qryNextFunction = 0  # 上次运行的查询函数索引

    # ----------------------------------------------------------------------
    def connect(self):
        """连接"""
        # 载入json文件
        file_name = findConfPath(self.gatewayName + '_connect.json')

        try:
            f = file(file_name)
        except IOError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'读取连接配置出错，请检查'
            self.onLog(log)
            return

        # 解析json文件
        setting = json.load(f)
        try:
            user_id = str(setting['userID'])
            password = str(setting['password'])
            broker_id = str(setting['brokerID'])
            td_address = str(setting['tdAddress'])
            md_address = str(setting['mdAddress'])
        except KeyError:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'连接配置缺少字段，请检查'
            self.onLog(log)
            return

            # 创建行情和交易接口对象
        self.mdApi.connect(user_id, password, broker_id, md_address)
        self.tdApi.connect(user_id, password, broker_id, td_address)

        # 初始化并启动查询
        self.initQuery()

    # ----------------------------------------------------------------------
    def subscribe(self, subscribe_req):
        """订阅行情"""
        self.mdApi.subscribe(subscribe_req)

    # ----------------------------------------------------------------------
    def sendOrder(self, order_req):
        """发单"""
        return self.tdApi.sendOrder(order_req)

    # ----------------------------------------------------------------------
    def cancelOrder(self, cancel_order_req):
        """撤单"""
        self.tdApi.cancelOrder(cancel_order_req)

    # ----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户资金"""
        self.tdApi.qryAccount()

    # ----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.tdApi.qryPosition()

    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        if self.mdConnected:
            self.mdApi.close()
        if self.tdConnected:
            self.tdApi.close()

    # ----------------------------------------------------------------------
    def initQuery(self):
        """初始化连续查询"""
        if self.qryEnabled:
            # 需要循环的查询函数列表
            self.qryFunctionList = [self.qryAccount, self.qryPosition]

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
    def setQryEnabled(self, qry_enabled):
        """设置是否要启动循环查询"""
        self.qryEnabled = qry_enabled


########################################################################
class CtpMdApi(MdApi):
    """CTP行情API实现"""

    # ----------------------------------------------------------------------
    def __init__(self, gateway):
        """Constructor"""
        super(CtpMdApi, self).__init__()

        self.gateway = gateway  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.reqID = EMPTY_INT  # 操作请求编号

        self.connectionStatus = False  # 连接状态
        self.loginStatus = False  # 登录状态

        self.subscribedSymbols = set()  # 已订阅合约代码

        self.userID = EMPTY_STRING  # 账号
        self.password = EMPTY_STRING  # 密码
        self.brokerID = EMPTY_STRING  # 经纪商代码
        self.address = EMPTY_STRING  # 服务器地址

    # ----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        self.connectionStatus = True

        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'行情服务器连接成功'
        self.gateway.onLog(log)
        self.login()

    # ----------------------------------------------------------------------
    def onFrontDisconnected(self, n):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.mdConnected = False

        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'行情服务器连接断开'
        self.gateway.onLog(log)

    # ----------------------------------------------------------------------
    @staticmethod
    def onHeartBeatWarning(n):
        """心跳报警"""
        # 因为API的心跳报警比较常被触发，且与API工作关系不大，因此选择忽略
        pass

    # ----------------------------------------------------------------------
    def onRspError(self, error, n, last):
        """错误回报"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)

    # ----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = True
            self.gateway.mdConnected = True

            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'行情服务器登录完成'
            self.gateway.onLog(log)

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

    # ----------------------------------------------------------------------
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        # 如果登出成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = False
            self.gateway.mdConnected = False

            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'行情服务器登出完成'
            self.gateway.onLog(log)

        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspSubMarketData(data, error, n, last):
        """订阅合约回报"""
        # 通常不在乎订阅错误，选择忽略
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspUnSubMarketData(data, error, n, last):
        """退订合约回报"""
        # 同上
        pass

    # ----------------------------------------------------------------------
    def onRtnDepthMarketData(self, data):
        """行情推送"""
        tick = VtTickData()
        tick.gatewayName = self.gatewayName

        tick.symbol = data['InstrumentID']
        tick.exchange = exchangeMapReverse.get(data['ExchangeID'], u'未知')
        tick.vtSymbol = tick.symbol  # '.'.join([tick.symbol, EXCHANGE_UNKNOWN])

        tick.lastPrice = data['LastPrice']
        tick.volume = data['Volume']
        tick.openInterest = data['OpenInterest']
        tick.time = '.'.join([data['UpdateTime'], str(data['UpdateMillisec'] / 100)])
        tick.date = data['TradingDay']

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

        self.gateway.onTick(tick)

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspSubForQuoteRsp(data, error, n, last):
        """订阅期权询价"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspUnSubForQuoteRsp(data, error, n, last):
        """退订期权询价"""
        pass

        # ----------------------------------------------------------------------

    @staticmethod
    def onRtnForQuoteRsp(data):
        """期权询价推送"""
        pass

        # ----------------------------------------------------------------------

    def connect(self, user_id, password, broker_id, address):
        """初始化连接"""
        self.userID = user_id  # 账号
        self.password = password  # 密码
        self.brokerID = broker_id  # 经纪商代码
        self.address = address  # 服务器地址

        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            # 创建C++环境中的API对象，这里传入的参数是需要用来保存.con文件的文件夹路径
            path = findTempPath(self.gatewayName)
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

    # ----------------------------------------------------------------------
    def subscribe(self, subscribe_req):
        """订阅合约"""
        # 这里的设计是，如果尚未登录就调用了订阅方法
        # 则先保存订阅请求，登录完成后会自动订阅
        if self.loginStatus:
            self.subscribeMarketData(str(subscribe_req.symbol))
        self.subscribedSymbols.add(subscribe_req)

    # ----------------------------------------------------------------------
    def login(self):
        """登录"""
        # 如果填入了用户名密码等，则登录
        if self.userID and self.password and self.brokerID:
            req = {
                'UserID': self.userID,
                'Password': self.password,
                'BrokerID': self.brokerID
            }
            self.reqID += 1
            print "--->>> reqUserLogin Md"
            self.reqUserLogin(req, self.reqID)

    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()


########################################################################
class CtpTdApi(TdApi):
    """CTP交易API实现"""

    # ----------------------------------------------------------------------
    def __init__(self, gateway):
        """API对象的初始化函数"""
        super(CtpTdApi, self).__init__()

        self.gateway = gateway  # gateway对象
        self.gatewayName = gateway.gatewayName  # gateway对象名称

        self.reqID = EMPTY_INT  # 操作请求编号
        self.orderRef = EMPTY_INT  # 订单编号

        self.connectionStatus = False  # 连接状态
        self.loginStatus = False  # 登录状态

        self.userID = EMPTY_STRING  # 账号
        self.password = EMPTY_STRING  # 密码
        self.brokerID = EMPTY_STRING  # 经纪商代码
        self.address = EMPTY_STRING  # 服务器地址

        self.frontID = EMPTY_INT  # 前置机编号
        self.sessionID = EMPTY_INT  # 会话编号

        self.posBufferDict = {}  # 缓存持仓数据的字典
        self.symbolExchangeDict = {}  # 保存合约代码和交易所的印射关系
        self.symbolSizeDict = {}  # 保存合约代码和合约大小的印射关系

    # ----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        self.connectionStatus = True

        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'交易服务器连接成功'
        self.gateway.onLog(log)

        self.login()

    # ----------------------------------------------------------------------
    def onFrontDisconnected(self, n):
        """服务器断开"""
        self.connectionStatus = False
        self.loginStatus = False
        self.gateway.tdConnected = False

        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'交易服务器连接断开'
        self.gateway.onLog(log)

    # ----------------------------------------------------------------------
    @staticmethod
    def onHeartBeatWarning(n):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspAuthenticate(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        # 如果登录成功，推送日志信息
        if error['ErrorID'] == 0:
            self.frontID = str(data['FrontID'])
            self.sessionID = str(data['SessionID'])
            self.loginStatus = True
            self.gateway.tdConnected = True

            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易服务器登录完成'
            self.gateway.onLog(log)

            # 确认结算信息
            req = {
                'BrokerID': self.brokerID,
                'InvestorID': self.userID
            }
            self.reqID += 1
            print "--->>> reqSettlementInfoConfirm"
            self.reqSettlementInfoConfirm(req, self.reqID)

            # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)

    # ----------------------------------------------------------------------
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        # 如果登出成功，推送日志信息
        if error['ErrorID'] == 0:
            self.loginStatus = False
            self.gateway.tdConnected = False

            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易服务器登出完成'
            self.gateway.onLog(log)

        # 否则，推送错误信息
        else:
            err = VtErrorData()
            err.gatewayName = self.gatewayName
            err.errorID = error['ErrorID']
            err.errorMsg = error['ErrorMsg'].decode('gbk')
            self.gateway.onError(err)

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspUserPasswordUpdate(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspTradingAccountPasswordUpdate(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    def onRspOrderInsert(self, data, error, n, last):
        """发单错误（柜台）"""
        print "onRspOrderInsert", data, error, n, last
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspParkedOrderInsert(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspParkedOrderAction(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    def onRspOrderAction(self, data, error, n, last):
        """撤单错误（柜台）"""
        print 2
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQueryMaxOrderVolume(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    def onRspSettlementInfoConfirm(self, data, error, n, last):
        """确认结算信息回报"""
        log = VtLogData()
        log.gatewayName = self.gatewayName
        log.logContent = u'结算信息确认完成'
        self.gateway.onLog(log)

        # 查询合约代码
        self.reqID += 1
        print "--->>> reqQryInstrument"
        self.reqQryInstrument({}, self.reqID)

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspRemoveParkedOrder(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspRemoveParkedOrderAction(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspExecOrderInsert(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspExecOrderAction(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspForQuoteInsert(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQuoteInsert(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQuoteAction(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspLockInsert(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspCombActionInsert(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryOrder(error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryTrade(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    def onRspQryInvestorPosition(self, data, error, n, last):
        """持仓查询回报"""
        # 获取缓存字典中的持仓缓存，若无则创建并初始化
        position_name = '.'.join([data['InstrumentID'], data['PosiDirection']])

        if position_name in self.posBufferDict:
            pos_buffer = self.posBufferDict[position_name]
        else:
            pos_buffer = PositionBuffer(data, self.gatewayName)
            self.posBufferDict[position_name] = pos_buffer

        # 更新持仓缓存，并获取VT系统中持仓对象的返回值
        exchange = self.symbolExchangeDict.get(data['InstrumentID'], EXCHANGE_UNKNOWN)
        size = self.symbolSizeDict.get(data['InstrumentID'], 1)
        if exchange == EXCHANGE_SHFE:
            pos = pos_buffer.updateShfeBuffer(data, size)
        else:
            pos = pos_buffer.updateBuffer(data, size)
        self.gateway.onPosition(pos)

    # ----------------------------------------------------------------------
    def onRspQryTradingAccount(self, data, error, n, last):
        """资金账户查询回报"""
        account = VtAccountData()
        account.gatewayName = self.gatewayName

        # 账户代码
        account.accountID = data['AccountID']
        account.vtAccountID = '.'.join([self.gatewayName, account.accountID])

        # 数值相关
        account.preBalance = data['PreBalance']
        account.available = data['Available']
        account.commission = data['Commission']
        account.margin = data['CurrMargin']
        account.closeProfit = data['CloseProfit']
        account.positionProfit = data['PositionProfit']

        # 这里的balance和快期中的账户不确定是否一样，需要测试
        account.balance = (data['PreBalance'] - data['PreCredit'] - data['PreMortgage'] +
                           data['Mortgage'] - data['Withdraw'] + data['Deposit'] +
                           data['CloseProfit'] + data['PositionProfit'] + data['CashIn'] -
                           data['Commission'])

        # 推送
        self.gateway.onAccount(account)

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryInvestor(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryTradingCode(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryInstrumentMarginRate(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryInstrumentCommissionRate(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryExchange(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryProduct(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    def onRspQryInstrument(self, data, error, n, last):
        """合约查询回报"""
        contract = VtContractData()
        contract.gatewayName = self.gatewayName

        contract.symbol = data['InstrumentID']
        contract.exchange = exchangeMapReverse[data['ExchangeID']]
        contract.vtSymbol = contract.symbol  # '.'.join([contract.symbol, contract.exchange])
        contract.name = data['InstrumentName'].decode('GBK')

        # 合约数值
        contract.size = data['VolumeMultiple']
        contract.priceTick = data['PriceTick']
        contract.strikePrice = data['StrikePrice']
        contract.underlyingSymbol = data['UnderlyingInstrID']

        contract.productClass = productClassMapReverse.get(data['ProductClass'], PRODUCT_UNKNOWN)

        # 期权类型
        if data['OptionsType'] == '1':
            contract.optionType = OPTION_CALL
        elif data['OptionsType'] == '2':
            contract.optionType = OPTION_PUT

        # 缓存代码和交易所的印射关系
        self.symbolExchangeDict[contract.symbol] = contract.exchange
        self.symbolSizeDict[contract.symbol] = contract.size

        # 推送
        self.gateway.onContract(contract)

        if last:
            log = VtLogData()
            log.gatewayName = self.gatewayName
            log.logContent = u'交易合约信息获取完成'
            self.gateway.onLog(log)

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryDepthMarketData(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQrySettlementInfo(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryTransferBank(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryInvestorPositionDetail(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryNotice(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQrySettlementInfoConfirm(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryInvestorPositionCombineDetail(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryCFMMCTradingAccountKey(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryEWarrantOffset(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryInvestorProductGroupMargin(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryExchangeMarginRate(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryExchangeMarginRateAdjust(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryExchangeRate(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQrySecAgentACIDMap(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryProductExchRate(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryProductGroup(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryOptionInstrTradeCost(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryOptionInstrCommRate(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryExecOrder(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryForQuote(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryQuote(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryLock(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryLockPosition(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryInvestorLevel(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryExecFreeze(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryCombInstrumentGuard(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryCombAction(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryTransferSerial(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryAccountregister(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    def onRspError(self, error, n, last):
        """错误回报"""
        print 3, error, n, last
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)

    # ----------------------------------------------------------------------
    def onRtnOrder(self, data):
        """报单回报"""
        # 更新最大报单编号
        print "onRtnOrder", data
        newref = data['OrderRef']
        self.orderRef = max(self.orderRef, int(newref))

        # 创建报单数据对象
        order = VtOrderData()
        order.gatewayName = self.gatewayName

        # 保存代码和报单号
        order.symbol = data['InstrumentID']
        order.exchange = exchangeMapReverse[data['ExchangeID']]
        order.vtSymbol = order.symbol  # '.'.join([order.symbol, order.exchange])

        order.orderID = data['OrderRef']

        # 方向
        if data['Direction'] == '0':
            order.direction = DIRECTION_LONG
        elif data['Direction'] == '1':
            order.direction = DIRECTION_SHORT
        else:
            order.direction = DIRECTION_UNKNOWN

        # 开平
        if data['CombOffsetFlag'] == '0':
            order.offset = OFFSET_OPEN
        elif data['CombOffsetFlag'] == '1':
            order.offset = OFFSET_CLOSE
        else:
            order.offset = OFFSET_UNKNOWN

        # 状态
        if data['OrderStatus'] == '0':
            order.status = STATUS_ALLTRADED
        elif data['OrderStatus'] == '1':
            order.status = STATUS_PARTTRADED
        elif data['OrderStatus'] == '3':
            order.status = STATUS_NOTTRADED
        elif data['OrderStatus'] == '5':
            order.status = STATUS_CANCELLED
        else:
            order.status = STATUS_UNKNOWN

        # 价格、报单量等数值
        order.price = data['LimitPrice']
        order.totalVolume = data['VolumeTotalOriginal']
        order.tradedVolume = data['VolumeTraded']
        order.orderTime = data['InsertTime']
        order.cancelTime = data['CancelTime']
        order.frontID = data['FrontID']
        order.sessionID = data['SessionID']

        # CTP的报单号一致性维护需要基于frontID, sessionID, orderID三个字段
        # 但在本接口设计中，已经考虑了CTP的OrderRef的自增性，避免重复
        # 唯一可能出现OrderRef重复的情况是多处登录并在非常接近的时间内（几乎同时发单）
        # 考虑到VtTrader的应用场景，认为以上情况不会构成问题
        order.vtOrderID = '.'.join([self.gatewayName, order.orderID])

        # 推送
        self.gateway.onOrder(order)

    # ----------------------------------------------------------------------
    def onRtnTrade(self, data):
        """成交回报"""
        # 创建报单数据对象
        print "onRtnTrade", data
        trade = VtTradeData()
        trade.gatewayName = self.gatewayName

        # 保存代码和报单号
        trade.symbol = data['InstrumentID']
        trade.exchange = exchangeMapReverse[data['ExchangeID']]
        trade.vtSymbol = trade.symbol  # '.'.join([trade.symbol, trade.exchange])

        trade.tradeID = data['TradeID']
        trade.vtTradeID = '.'.join([self.gatewayName, trade.tradeID])

        trade.orderID = data['OrderRef']
        trade.vtOrderID = '.'.join([self.gatewayName, trade.orderID])

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

    # ----------------------------------------------------------------------
    def onErrRtnOrderInsert(self, data, error):
        """发单错误回报（交易所）"""
        print "onErrRtnOrderInsert", data, error
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)

    # ----------------------------------------------------------------------
    def onErrRtnOrderAction(self, data, error):
        """撤单错误回报（交易所）"""
        err = VtErrorData()
        err.gatewayName = self.gatewayName
        err.errorID = error['ErrorID']
        err.errorMsg = error['ErrorMsg'].decode('gbk')
        self.gateway.onError(err)

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnInstrumentStatus(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnTradingNotice(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnErrorConditionalOrder(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnExecOrder(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnExecOrderInsert(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnExecOrderAction(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnForQuoteInsert(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnQuote(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnQuoteInsert(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnQuoteAction(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnForQuoteRsp(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnCFMMCTradingAccountToken(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnLock(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnLockInsert(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnCombAction(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnCombActionInsert(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryContractBank(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryParkedOrder(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryParkedOrderAction(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryTradingNotice(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryBrokerTradingParams(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQryBrokerTradingAlgos(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQueryCFMMCTradingAccountToken(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnFromBankToFutureByBank(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnFromFutureToBankByBank(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnRepealFromBankToFutureByBank(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnRepealFromFutureToBankByBank(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnFromBankToFutureByFuture(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnFromFutureToBankByFuture(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnRepealFromBankToFutureByFutureManual(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnRepealFromFutureToBankByFutureManual(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnQueryBankBalanceByFuture(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnBankToFutureByFuture(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnFutureToBankByFuture(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnRepealBankToFutureByFutureManual(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnRepealFutureToBankByFutureManual(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onErrRtnQueryBankBalanceByFuture(data, error):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnRepealFromBankToFutureByFuture(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnRepealFromFutureToBankByFuture(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspFromBankToFutureByFuture(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspFromFutureToBankByFuture(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRspQueryBankAccountMoneyByFuture(data, error, n, last):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnOpenAccountByBank(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnCancelAccountByBank(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    @staticmethod
    def onRtnChangeAccountByBank(data):
        """"""
        pass

    # ----------------------------------------------------------------------
    def connect(self, user_id, password, broker_id, address):
        """初始化连接"""
        self.userID = user_id  # 账号
        self.password = password  # 密码
        self.brokerID = broker_id  # 经纪商代码
        self.address = address  # 服务器地址

        # 如果尚未建立服务器连接，则进行连接
        if not self.connectionStatus:
            # 创建C++环境中的API对象，这里传入的参数是需要用来保存.con文件的文件夹路径
            path = findTempPath(self.gatewayName)
            if not os.path.exists(path):
                os.makedirs(path)
            self.createFtdcTraderApi(path)

            # 注册服务器地址
            self.registerFront(self.address)

            # 初始化连接，成功会调用onFrontConnected
            self.init()

        # 若已经连接但尚未登录，则进行登录
        else:
            if not self.loginStatus:
                self.login()

    # ----------------------------------------------------------------------
    def login(self):
        """连接服务器"""
        # 如果填入了用户名密码等，则登录
        if self.userID and self.password and self.brokerID:
            req = {
                'UserID': self.userID,
                'Password': self.password,
                'BrokerID': self.brokerID
            }
            self.reqID += 1
            print "--->>> reqUserLogin Td"
            self.reqUserLogin(req, self.reqID)

    # ----------------------------------------------------------------------
    def qryAccount(self):
        """查询账户"""
        self.reqID += 1
        print "--->>> reqQryTradingAccount"
        self.reqQryTradingAccount({}, self.reqID)

    # ----------------------------------------------------------------------
    def qryPosition(self):
        """查询持仓"""
        self.reqID += 1
        req = {
            'BrokerID': self.brokerID,
            'InvestorID': self.userID
        }
        print "--->>> reqQryInvestorPosition"
        self.reqQryInvestorPosition(req, self.reqID)

    # ----------------------------------------------------------------------
    def sendOrder(self, order_req):
        """发单"""
        self.reqID += 1
        self.orderRef += 1

        req = {
            'InstrumentID': order_req.symbol,
            'LimitPrice': order_req.price,
            'VolumeTotalOriginal': order_req.volume,
            'OrderPriceType': priceTypeMap.get(order_req.priceType, ''),
            'Direction': directionMap.get(order_req.direction, ''),
            'CombOffsetFlag': offsetMap.get(order_req.offset, ''),
            'OrderRef': str(self.orderRef),
            'InvestorID': self.userID,
            'UserID': self.userID,
            'BrokerID': self.brokerID,
            'CombHedgeFlag': defineDict['THOST_FTDC_HF_Speculation'],
            'ContingentCondition': defineDict['THOST_FTDC_CC_Immediately'],
            'ForceCloseReason': defineDict['THOST_FTDC_FCC_NotForceClose'],
            'IsAutoSuspend': 0,
            'TimeCondition': defineDict['THOST_FTDC_TC_GFD'],
            'VolumeCondition': defineDict['THOST_FTDC_VC_AV'],
            'MinVolume': 1
        }

        # 下面如果由于传入的类型本接口不支持，则会返回空字符串

        # 判断FAK和FOK
        if order_req.priceType == PRICETYPE_FAK:
            req['OrderPriceType'] = defineDict["THOST_FTDC_OPT_LimitPrice"]
            req['TimeCondition'] = defineDict['THOST_FTDC_TC_IOC']
            req['VolumeCondition'] = defineDict['THOST_FTDC_VC_AV']
        if order_req.priceType == PRICETYPE_FOK:
            req['OrderPriceType'] = defineDict["THOST_FTDC_OPT_LimitPrice"]
            req['TimeCondition'] = defineDict['THOST_FTDC_TC_IOC']
            req['VolumeCondition'] = defineDict['THOST_FTDC_VC_CV']

        print "--->>> reqOrderInsert"
        self.reqOrderInsert(req, self.reqID)

        # 返回订单号（字符串），便于某些算法进行动态管理
        vt_order_id = '.'.join([self.gatewayName, str(self.orderRef)])
        return vt_order_id

    # ----------------------------------------------------------------------
    def cancelOrder(self, cancel_order_req):
        """撤单"""
        self.reqID += 1

        req = {
            'InstrumentID': cancel_order_req.symbol,
            'ExchangeID': cancel_order_req.exchange,
            'OrderRef': cancel_order_req.orderID,
            'FrontID': cancel_order_req.frontID,
            'SessionID': cancel_order_req.sessionID,
            'ActionFlag': defineDict['THOST_FTDC_AF_Delete'],
            'BrokerID': self.brokerID,
            'InvestorID': self.userID
        }
        print "--->>> reqOrderAction"
        self.reqOrderAction(req, self.reqID)

    # ----------------------------------------------------------------------
    def close(self):
        """关闭"""
        self.exit()


########################################################################
class PositionBuffer(object):
    """用来缓存持仓的数据，处理上期所的数据返回分今昨的问题"""

    # ----------------------------------------------------------------------
    def __init__(self, data, gateway_name):
        """Constructor"""
        self.symbol = data['InstrumentID']
        self.direction = posiDirectionMapReverse.get(data['PosiDirection'], '')

        self.todayPosition = EMPTY_INT
        self.ydPosition = EMPTY_INT
        self.todayPositionCost = EMPTY_FLOAT
        self.ydPositionCost = EMPTY_FLOAT

        # 通过提前创建持仓数据对象并重复使用的方式来降低开销
        pos = VtPositionData()
        pos.symbol = self.symbol
        pos.vtSymbol = self.symbol
        pos.gatewayName = gateway_name
        pos.direction = self.direction
        pos.vtPositionName = '.'.join([pos.vtSymbol, pos.direction])
        self.pos = pos

    # ----------------------------------------------------------------------
    def updateShfeBuffer(self, data, size):
        """更新上期所缓存，返回更新后的持仓数据"""
        # 昨仓和今仓的数据更新是分在两条记录里的，因此需要判断检查该条记录对应仓位
        # 因为今仓字段TodayPosition可能变为0（被全部平仓），因此分辨今昨仓需要用YdPosition字段
        if data['YdPosition']:
            self.ydPosition = data['Position']
            self.ydPositionCost = data['PositionCost']
        else:
            self.todayPosition = data['Position']
            self.todayPositionCost = data['PositionCost']

            # 持仓的昨仓和今仓相加后为总持仓
        self.pos.position = self.todayPosition + self.ydPosition
        self.pos.ydPosition = self.ydPosition

        # 如果手头还有持仓，则通过加权平均方式计算持仓均价
        if self.todayPosition or self.ydPosition:
            self.pos.price = ((self.todayPositionCost + self.ydPositionCost) /
                              ((self.todayPosition + self.ydPosition) * size))
        # 否则价格为0
        else:
            self.pos.price = 0

        return copy(self.pos)

    # ----------------------------------------------------------------------
    def updateBuffer(self, data, size):
        """更新其他交易所的缓存，返回更新后的持仓数据"""
        # 其他交易所并不区分今昨，因此只关心总仓位，昨仓设为0
        self.pos.position = data['Position']
        self.pos.ydPosition = 0

        if data['Position']:
            self.pos.price = data['PositionCost'] / (data['Position'] * size)
        else:
            self.pos.price = 0

        return copy(self.pos)


# ----------------------------------------------------------------------

def test():
    """测试"""
    from PyQt4 import QtCore
    import sys

    def print_log(event):
        log = event.dict_['data']
        print ':'.join([log.logTime, log.logContent])

    app = QtCore.QCoreApplication(sys.argv)

    event_engine = EventEngine()
    event_engine.register(EVENT_LOG, print_log)
    event_engine.start()

    gateway = CtpGateway(event_engine)
    gateway.connect()

    sys.exit(app.exec_())


if __name__ == '__main__':
    test()
