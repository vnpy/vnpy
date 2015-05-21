# encoding: UTF-8

"""
该文件中包含的是交易平台的底层接口相关的部分，
主要对API进行了一定程度的简化封装，方便开发。
"""

import os

from vnctpmd import MdApi
from vnctptd import TdApi
from eventEngine import *
from ctp_data_type import defineDict

#----------------------------------------------------------------------
def print_dict(d):
    """打印API收到的字典，该函数主要用于开发时的debug"""
    print '-'*60
    l = d.keys()
    l.sort()
    for key in l:
        print key, ':', d[key]
    

########################################################################
class DemoMdApi(MdApi):
    """
    Demo中的行情API封装
    封装后所有数据自动推送到事件驱动引擎中，由其负责推送到各个监听该事件的回调函数上
    
    对用户暴露的主动函数包括:
    登陆 login
    订阅合约 subscribe
    """

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """
        API对象的初始化函数
        """
        super(DemoMdApi, self).__init__()
        
        # 事件引擎，所有数据都推送到其中，再由事件引擎进行分发
        self.__eventEngine = eventEngine  
        
        # 请求编号，由api负责管理
        self.__reqid = 0
        
        # 以下变量用于实现连接和重连后的自动登陆
        self.__userid = ''
        self.__password = ''
        self.__brokerid = ''
        
        # 以下集合用于重连后自动订阅之前已订阅的合约，使用集合为了防止重复
        self.__setSubscribed = set()
        
        # 初始化.con文件的保存目录为\mdconnection，注意这个目录必须已存在，否则会报错
        self.createFtdcMdApi(os.getcwd() + '\\mdconnection\\')                
        
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'行情服务器连接成功'
        self.__eventEngine.put(event)
        
        # 如果用户已经填入了用户名等等，则自动尝试连接
        if self.__userid:
            req = {}
            req['UserID'] = self.__userid
            req['Password'] = self.__password
            req['BrokerID'] = self.__brokerid
            self.__reqid = self.__reqid + 1
            self.reqUserLogin(req, self.__reqid)
            
    #----------------------------------------------------------------------  
    def onFrontDisconnected(self, n):
        """服务器断开"""
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'行情服务器连接断开'
        self.__eventEngine.put(event)
        
    #---------------------------------------------------------------------- 
    def onHeartBeatWarning(self, n):
        """心跳报警"""
        # 因为API的心跳报警比较常被触发，且与API工作关系不大，因此选择忽略
        pass
    
    #----------------------------------------------------------------------   
    def onRspError(self, error, n, last):
        """错误回报"""
        event = Event(type_=EVENT_LOG)
        log = u'行情错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'行情服务器登陆成功'
        else:
            log = u'登陆回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
        ## 重连后自动订阅之前已经订阅过的合约
        #if self.__setSubscribed:
            #for instrument in self.__setSubscribed:
                #self.subscribe(instrument[0], instrument[1])
                
    #---------------------------------------------------------------------- 
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'行情服务器登出成功'
        else:
            log = u'登出回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
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
        # 行情推送收到后，同时触发常规行情事件，以及特定合约行情事件，用于满足不同类型的监听
        
        # 常规行情事件
        event1 = Event(type_=EVENT_MARKETDATA)
        event1.dict_['data'] = data
        self.__eventEngine.put(event1)
        
        # 特定合约行情事件
        event2 = Event(type_=(EVENT_MARKETDATA_CONTRACT+data['InstrumentID']))
        event2.dict_['data'] = data
        self.__eventEngine.put(event2)
        
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
    def login(self, address, userid, password, brokerid):
        """连接服务器"""
        self.__userid = userid
        self.__password = password
        self.__brokerid = brokerid
        
        # 注册服务器地址
        self.registerFront(address)
        
        # 初始化连接，成功会调用onFrontConnected
        self.init()
        
    #----------------------------------------------------------------------
    def subscribe(self, instrumentid, exchangeid):
        """订阅合约"""
        self.subscribeMarketData(instrumentid)
        
        instrument = (instrumentid, exchangeid)
        self.__setSubscribed.add(instrument)


########################################################################
class DemoTdApi(TdApi):
    """
    Demo中的交易API封装
    主动函数包括：
    login 登陆
    getInstrument 查询合约信息
    getAccount 查询账号资金
    getInvestor 查询投资者
    getPosition 查询持仓
    sendOrder 发单
    cancelOrder 撤单
    """

    #----------------------------------------------------------------------
    def __init__(self, eventEngine):
        """API对象的初始化函数"""
        super(DemoTdApi, self).__init__()
        
        # 事件引擎，所有数据都推送到其中，再由事件引擎进行分发
        self.__eventEngine = eventEngine
        
        # 请求编号，由api负责管理
        self.__reqid = 0
        
        # 报单编号，由api负责管理
        self.__orderref = 0
        
        # 以下变量用于实现连接和重连后的自动登陆
        self.__userid = ''
        self.__password = ''
        self.__brokerid = ''   
        
        # 合约字典（保存合约查询数据）
        self.__dictInstrument = {}
        
        # 初始化.con文件的保存目录为\tdconnection
        self.createFtdcTraderApi(os.getcwd() + '\\tdconnection\\')    
        
    #----------------------------------------------------------------------
    def onFrontConnected(self):
        """服务器连接"""
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'交易服务器连接成功'
        self.__eventEngine.put(event)
        
        # 如果用户已经填入了用户名等等，则自动尝试连接
        if self.__userid:
            req = {}
            req['UserID'] = self.__userid
            req['Password'] = self.__password
            req['BrokerID'] = self.__brokerid
            self.__reqid = self.__reqid + 1
            self.reqUserLogin(req, self.__reqid)
    
    #----------------------------------------------------------------------
    def onFrontDisconnected(self, n):
        """服务器断开"""
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = u'交易服务器连接断开'
        self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def onHeartBeatWarning(self, n):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspAuthenticate(self, data, error, n, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """登陆回报"""
        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'交易服务器登陆成功'
        else:
            log = u'登陆回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
        self.getSettlement()    # 登录完成后立即查询结算信息
    
    #----------------------------------------------------------------------
    def onRspUserLogout(self, data, error, n, last):
        """登出回报"""
        event = Event(type_=EVENT_LOG)
        
        if error['ErrorID'] == 0:
            log = u'交易服务器登出成功'
        else:
            log = u'登出回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        
        event.dict_['log'] = log
        self.__eventEngine.put(event)
    
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
        """发单错误（柜台）"""
        event = Event(type_=EVENT_LOG)
        log = u' 发单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)   
    
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
        event = Event(type_=EVENT_LOG)
        log = u'撤单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def onRspQueryMaxOrderVolume(self, data, error, n, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspSettlementInfoConfirm(self, data, error, n, last):
        """确认结算信息回报"""
        event = Event(type_=EVENT_LOG)
        log = u'结算信息确认完成'
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
        event = Event(type_=EVENT_TDLOGIN)
        self.__eventEngine.put(event)    
    
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
        if error['ErrorID'] == 0:
            event = Event(type_=EVENT_POSITION)
            event.dict_['data'] = data
            self.__eventEngine.put(event)
        else:
            event = Event(type_=EVENT_LOG)
            log = u'持仓查询回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
            event.dict_['log'] = log
            self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def onRspQryTradingAccount(self, data, error, n, last):
        """资金账户查询回报"""
        if error['ErrorID'] == 0:
            event = Event(type_=EVENT_ACCOUNT)
            event.dict_['data'] = data
            self.__eventEngine.put(event)
        else:
            event = Event(type_=EVENT_LOG)
            log = u'账户查询回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
            event.dict_['log'] = log
            self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def onRspQryInvestor(self, data, error, n, last):
        """投资者查询回报"""
        if error['ErrorID'] == 0:
            event = Event(type_=EVENT_INVESTOR)
            event.dict_['data'] = data
            self.__eventEngine.put(event)
        else:
            event = Event(type_=EVENT_LOG)
            log = u'合约投资者回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
            event.dict_['log'] = log
            self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def onRspQryTradingCode(self, data, error, n, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQryInstrumentMarginRate(self, data, error, n, last):
        """"""
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
        """
        合约查询回报
        由于该回报的推送速度极快，因此不适合全部存入队列中处理，
        选择先储存在一个本地字典中，全部收集完毕后再推送到队列中
        （由于耗时过长目前使用其他进程读取）
        """
        if error['ErrorID'] == 0:
            event = Event(type_=EVENT_INSTRUMENT)
            event.dict_['data'] = data
            event.dict_['last'] = last
            self.__eventEngine.put(event)
        else:
            event = Event(type_=EVENT_LOG)
            log = u'合约投资者回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
            event.dict_['log'] = log
            self.__eventEngine.put(event)   
    
    #----------------------------------------------------------------------
    def onRspQryDepthMarketData(self, data, error, n, last):
        """"""
        pass
    
    #----------------------------------------------------------------------
    def onRspQrySettlementInfo(self, data, error, n, last):
        """查询结算信息回报"""
        event = Event(type_=EVENT_LOG)
        log = u'结算信息查询完成'
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
        self.confirmSettlement()    # 查询完成后立即确认结算信息
    
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
        event = Event(type_=EVENT_LOG)
        log = u'交易错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def onRtnOrder(self, data):
        """报单回报"""
        # 更新最大报单编号
        newref = data['OrderRef']
        self.__orderref = max(self.__orderref, int(newref))
        
        # 常规报单事件
        event1 = Event(type_=EVENT_ORDER)
        event1.dict_['data'] = data
        self.__eventEngine.put(event1)
        
        # 特定合约行情事件
        event2 = Event(type_=(EVENT_ORDER_ORDERREF+data['OrderRef']))
        event2.dict_['data'] = data
        self.__eventEngine.put(event2)
    
    #----------------------------------------------------------------------
    def onRtnTrade(self, data):
        """成交回报"""
        # 常规成交事件
        event1 = Event(type_=EVENT_TRADE)
        event1.dict_['data'] = data
        self.__eventEngine.put(event1)
        
        # 特定合约成交事件
        event2 = Event(type_=(EVENT_TRADE_CONTRACT+data['InstrumentID']))
        event2.dict_['data'] = data
        self.__eventEngine.put(event2)
    
    #----------------------------------------------------------------------
    def onErrRtnOrderInsert(self, data, error):
        """发单错误回报（交易所）"""
        event = Event(type_=EVENT_LOG)
        log = u'发单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)
    
    #----------------------------------------------------------------------
    def onErrRtnOrderAction(self, data, error):
        """撤单错误回报（交易所）"""
        event = Event(type_=EVENT_LOG)
        log = u'撤单错误回报，错误代码：' + unicode(error['ErrorID']) + u',' + u'错误信息：' + error['ErrorMsg'].decode('gbk')
        event.dict_['log'] = log
        self.__eventEngine.put(event)
    
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
    
    #----------------------------------------------------------------------
    def login(self, address, userid, password, brokerid):
        """连接服务器"""
        self.__userid = userid
        self.__password = password
        self.__brokerid = brokerid
        
        # 数据重传模式设为从本日开始
        self.subscribePrivateTopic(0)       
        self.subscribePublicTopic(0)            
        
        # 注册服务器地址
        self.registerFront(address)
        
        # 初始化连接，成功会调用onFrontConnected
        self.init()    
        
    #----------------------------------------------------------------------
    def getInstrument(self):
        """查询合约"""
        self.__reqid = self.__reqid + 1
        self.reqQryInstrument({}, self.__reqid)
        
    #----------------------------------------------------------------------
    def getAccount(self):
        """查询账户"""
        self.__reqid = self.__reqid + 1
        self.reqQryTradingAccount({}, self.__reqid)
        
    #----------------------------------------------------------------------
    def getInvestor(self):
        """查询投资者"""
        self.__reqid = self.__reqid + 1
        self.reqQryInvestor({}, self.__reqid)
        
    #----------------------------------------------------------------------
    def getPosition(self):
        """查询持仓"""
        self.__reqid = self.__reqid + 1
        req = {}
        req['BrokerID'] = self.__brokerid
        req['InvestorID'] = self.__userid
        self.reqQryInvestorPosition(req, self.__reqid)
        
    #----------------------------------------------------------------------
    def sendOrder(self, instrumentid, exchangeid, price, pricetype, volume, direction, offset):
        """发单"""
        self.__reqid = self.__reqid + 1
        req = {}
        
        req['InstrumentID'] = instrumentid
        req['OrderPriceType'] = pricetype
        req['LimitPrice'] = price
        req['VolumeTotalOriginal'] = volume
        req['Direction'] = direction
        req['CombOffsetFlag'] = offset
        
        self.__orderref = self.__orderref + 1
        req['OrderRef'] = str(self.__orderref)
        
        req['InvestorID'] = self.__userid
        req['UserID'] = self.__userid
        req['BrokerID'] = self.__brokerid
        req['CombHedgeFlag'] = defineDict['THOST_FTDC_HF_Speculation']       # 投机单
        req['ContingentCondition'] = defineDict['THOST_FTDC_CC_Immediately'] # 立即发单
        req['ForceCloseReason'] = defineDict['THOST_FTDC_FCC_NotForceClose'] # 非强平
        req['IsAutoSuspend'] = 0                                             # 非自动挂起
        req['TimeCondition'] = defineDict['THOST_FTDC_TC_GFD']               # 今日有效
        req['VolumeCondition'] = defineDict['THOST_FTDC_VC_AV']              # 任意成交量
        req['MinVolume'] = 1                                                 # 最小成交量为1
        
        self.reqOrderInsert(req, self.__reqid)
        
        # 返回订单号，便于某些算法进行动态管理
        return self.__orderref
    
    #----------------------------------------------------------------------
    def cancelOrder(self, instrumentid, exchangeid, orderref, frontid, sessionid):
        """撤单"""
        self.__reqid = self.__reqid + 1
        req = {}
        
        req['InstrumentID'] = instrumentid
        req['ExchangeID'] = exchangeid
        req['OrderRef'] = orderref
        req['FrontID'] = frontid
        req['SessionID'] = sessionid   
        
        req['ActionFlag'] = defineDict['THOST_FTDC_AF_Delete']
        req['BrokerID'] = self.__brokerid
        req['InvestorID'] = self.__userid
        
        self.reqOrderAction(req, self.__reqid)
    
    #----------------------------------------------------------------------
    def getSettlement(self):
        """查询结算信息"""
        self.__reqid = self.__reqid + 1
        req = {}
        
        req['BrokerID'] = self.__brokerid
        req['InvestorID'] = self.__userid
        
        self.reqQrySettlementInfo(req, self.__reqid)
        
    #----------------------------------------------------------------------
    def confirmSettlement(self):
        """确认结算信息"""
        self.__reqid = self.__reqid + 1
        req = {}
        
        req['BrokerID'] = self.__brokerid
        req['InvestorID'] = self.__userid
        
        self.reqSettlementInfoConfirm(req, self.__reqid)    