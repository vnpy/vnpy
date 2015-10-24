# encoding: UTF-8

from datetime import datetime,timedelta
print u'StragegyEngine.py import datetime.datetime success'

from pymongo import  MongoClient as Connection
print u'demoStrategy.py import pymongo.Connection success'

from pymongo.errors import *
print u'demoStrategy.py import pymongo.errors.* success'

from eventEngine import *
print u'demoStrategy.py import eventEngine.* success'

from vtConstant import *

import MySQLdb

import os
import sys
import cPickle

# 常量定义
OFFSET_OPEN = '0'           # 开仓
OFFSET_CLOSE = '1'          # 平仓

DIRECTION_BUY = '0'         # 买入
DIRECTION_SELL = '1'        # 卖出

PRICETYPE_LIMIT = '2'       # 限价

# buy   买入开仓    : DIRECTION_BUY = '0'   OFFSET_OPEN = '0'
# sell  卖出平仓    : DIRECTION_SELL = '1'  OFFSET_CLOSE = '1'

# short 卖出开仓    : DIRECTION_SELL = '1'  OFFSET_OPEN = '0'
# cover 买入平仓    : DIRECTION_BUY = '0'   OFFSET_CLOSE = '1'

########################################################################
class Tick:
    """Tick数据对象"""

    #----------------------------------------------------------------------
    def __init__(self, symbol):
        """Constructor"""
        self.symbol = symbol        # 合约代码
        
        self.openPrice = 0          # OHLC
        self.highPrice = 0
        self.lowPrice = 0
        self.lastPrice = 0
        
        self.volume = 0             # 成交量
        self.openInterest = 0       # 持仓量
        
        self.upperLimit = 0         # 涨停价
        self.lowerLimit = 0         # 跌停价
        
        self.time = ''              # 更新时间和毫秒
        self.ms= 0
        
        self.bidPrice1 = 0          # 深度行情
        self.bidPrice2 = 0
        self.bidPrice3 = 0
        self.bidPrice4 = 0
        self.bidPrice5 = 0
        
        self.askPrice1 = 0
        self.askPrice2 = 0
        self.askPrice3 = 0
        self.askPrice4 = 0
        self.askPrice5 = 0
        
        self.bidVolume1 = 0
        self.bidVolume2 = 0
        self.bidVolume3 = 0
        self.bidVolume4 = 0
        self.bidVolume5 = 0
        
        self.askVolume1 = 0
        self.askVolume2 = 0
        self.askVolume3 = 0
        self.askVolume4 = 0
        self.askVolume5 = 0        


########################################################################
class Bar(object):
    """K线数据"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""

        self.symbol = EMPTY_STRING          # 代码
        #self.exchange = EMPTY_STRING        # 交易所

        self.open = EMPTY_FLOAT             # OHLC
        self.high = EMPTY_FLOAT
        self.low = EMPTY_FLOAT
        self.close = EMPTY_FLOAT

        self.date = EMPTY_STRING            # bar开始的时间，日期
        self.time = EMPTY_STRING            # 时间
        self.datetime = None                # python的datetime时间对象

        self.volume = EMPTY_INT             # 成交量
        self.openInterest = EMPTY_INT       # 持仓量

########################################################################
class EmaData(object):
    """数据"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""

        self.symbol = EMPTY_STRING          # 代码
        self.fastEMA = EMPTY_FLOAT          # 快速EMA的数值
        self.slowEMA = EMPTY_FLOAT          # 慢速EMA的数值

        self.date = EMPTY_STRING            # EMA开始的时间，日期
        self.time = EMPTY_STRING            # 时间
        self.datetime = None                # python的datetime时间对象



########################################################################
class Trade(object):
    """成交数据对象"""

    #----------------------------------------------------------------------
    def __init__(self, symbol):
        """Constructor"""
        self.symbol = symbol        # 合约代码
        
        self.orderRef = ''          # 报单号
        self.tradeID = ''           # 成交编号
        
        self.direction = None       # 方向
        self.offset = None          # 开平
        self.price = 0              # 成交价
        self.volume = 0             # 成交量

        self.tradeTime = ''         # 成交时间
 

########################################################################
class Order(object):
    """报单数据对象"""

    #----------------------------------------------------------------------
    def __init__(self, symbol):
        """Constructor"""
        self.symbol = symbol        # 合约代码
        
        self.orderRef = ''          # 报单编号
        
        self.direction = None       # 方向
        self.offset = None          # 开平
        self.price = 0              # 委托价
        self.volumeOriginal = 0     # 报单量
        self.volumeTraded = 0       # 已成交数量
        
        self.insertTime = ''        # 报单时间
        self.cancelTime = ''        # 撤单时间
        
        self.frontID = 0            # 前置机编号
        self.sessionID = 0          # 会话编号
        
        self.status = ''            # 报单状态代码

        self.preTradeID = ''        # 上一成交单编号（用于平仓）


########################################################################
class StopOrder(object):
    """
    停止单对象
    用于实现价格突破某一水平后自动追入
    即通常的条件单和止损单
    """

    #----------------------------------------------------------------------
    def __init__(self, symbol, direction, offset, price, volume, strategy):
        """Constructor"""
        self.symbol = symbol
        self.direction = direction
        self.offset = offset
        self.price = price
        self.volume = volume
        self.strategy = strategy


########################################################################
class StrategyEngine(object):
    """策略引擎"""

    #----------------------------------------------------------------------
    def __init__(self, eventEngine, mainEngine, backtesting=False):
        """Constructor"""
        self.__eventEngine = eventEngine    # 引用事件引擎
        self.mainEngine = mainEngine        # 主引擎，在回测中，为backtestingEngine,在交易中，为MainEngine
        self.backtesting = backtesting      # 是否在进行回测
        
        # 获取代表今日的datetime
        t = datetime.today()
        self.today = t.replace(hour=0, minute=0, second=0, microsecond=0)
        
        # 保存所有报单数据的字典
        self.__dictOrder = {}
        
        # 保存策略对象的字典
        # key为策略名称
        # value为策略对象
        self.dictStrategy = {}
        
        # 保存合约代码和策略对象映射关系的字典
        # key为合约代码
        # value为交易该合约的策略列表
        self.__dictSymbolStrategy = {}
        
        # 保存报单编号和策略对象映射关系的字典
        # key为报单编号
        # value为策略对象
        self.__dictOrderRefStrategy = {}
        
        # 保存合约代码和相关停止单（止损单）的字典
        # key为合约代码
        # value为该合约相关的停止单列表
        self.__dictStopOrder = {}
        
        # MongoDB/Mysql数据库相关
        #self.__mongoConnected = False

        self.__mysqlConnected = False

        #self.__mongoConnection = None
        self.__mysqlConnection = None

        #self.__mongoTickDB = None
        
        # 调用函数
        #self.__connectMongo()
        self.__connectMysql()
        self.__registerEvent()
        
    #----------------------------------------------------------------------
    def createStrategy(self, strategyName, strategySymbol, strategyClass, strategySetting):
        """创建策略（实例化）"""
        strategy = strategyClass(strategyName, strategySymbol, self)

        self.writeLog(u"创建策略:{0}".format(strategyName))

        self.dictStrategy[strategyName] = strategy

        strategy.loadSetting(strategySetting)

        # 订阅合约行情，注意这里因为是CTP，所以ExchangeID可以忽略
        self.mainEngine.subscribe(strategySymbol, None)

        # 注册策略监听
        self.registerStrategy(strategySymbol, strategy)
    
    #----------------------------------------------------------------------
    #def __connectMongo(self):
    #    """连接MongoDB数据库"""
    #    try:
    #        self.__mongoConnection = Connection()
    #        self.__mongoConnected = True
    #        self.__mongoTickDB = self.__mongoConnection['TickDB']
    #        self.writeLog(u'策略引擎连接MongoDB成功')
    #    except ConnectionFailure:
    #        self.writeLog(u'策略引擎连接MongoDB失败')

 #-------------------------------------------#---------------------------
    # def __recordTickToMongo(self, data):
    #     """将Tick数据插入到MongoDB中"""
    #     if self.__mongoConnected:
    #         symbol = data['InstrumentID']
    #         data['date'] = self.today
    #         self.__mongoTickDB[symbol].insert(data)
    #

    # #----------------------------------------------------------------------
    # def loadTickFromMongo(self, symbol, startDate, endDate=None):
    #     """从MongoDB中读取Tick数据"""
    #     if self.__mongoConnected:
    #         collection = self.__mongoTickDB[symbol]
    #
    #         # 如果输入了读取TICK的最后日期
    #         if endDate:
    #             cx = collection.find({'date':{'$gte':startDate, '$lte':endDate}})
    #         else:
    #             cx = collection.find({'date':{'$gte':startDate}})
    #         return cx
    #     else:
    #         return None

    #----------------------------------------------------------------------
    def __connectMysql(self):
        """连接MysqlDB"""
        try:
            self.__mysqlConnection = MySQLdb.connect(host='vnpy.cloudapp.net', user='stockcn', passwd='7uhb*IJN', db='stockcn', port=3306)
            self.__mysqlConnected = True
            self.writeLog(u'策略引擎连接MysqlDB成功')
        except ConnectionFailure:
            self.writeLog(u'策略引擎连接MysqlDB失败')
    #----------------------------------------------------------------------
    def __recordTickToMysql(self, data):
        """将Tick数据插入到MysqlDB中"""
        #if self.__mongoConnected:
        #    symbol = data['InstrumentID']
        #    data['date'] = self.today
        #    self.__mongoTickDB[symbol].insert(data)
        pass

    #----------------------------------------------------------------------
    def __executeMysql(self, sql):
        """执行mysql语句"""
        if not self.__mysqlConnected:
            self.__connectMysql()

        cur = self.__mysqlConnection.cursor(MySQLdb.cursors.DictCursor)

        try:
            cur.execute(sql)
            self.__mysqlConnection.commit()

        except Exception, e:
            print e
            print sql

            self.__connectMysql()
            cur = self.__mysqlConnection.cursor(MySQLdb.cursors.DictCursor)
            cur.execute(sql)
            self.__mysqlConnection.commit()

    #----------------------------------------------------------------------
    def loadTickFromMysql(self, symbol, startDate, endDate=None):
        """从MysqlDB中读取Tick数据"""
        if self.__mysqlConnected:

            #获取指针
            cur = self.__mysqlConnection.cursor(MySQLdb.cursors.DictCursor)

            if endDate:
                #指定开始与结束日期
                sqlstring = ' select \'{0}\' as InstrumentID, str_to_date(concat(ndate,\' \', ntime),' \
                            '\'%Y-%m-%d %H:%i:%s\') as UpdateTime,price as LastPrice,vol as Volume,' \
                            'position_vol as OpenInterest,bid1_price as BidPrice1,bid1_vol as BidVolume1, ' \
                            'sell1_price as AskPrice1, sell1_vol as AskVolume1 from TB_{0}MI ' \
                            'where ndate between cast(\'{1}\' as date) and cast(\'{2}\' as date)'.format(symbol,  startDate, endDate)

            elif startDate:
                #指定开始日期
                sqlstring = ' select \'{0}\' as InstrumentID,str_to_date(concat(ndate,\' \', ntime),' \
                            '\'%Y-%m-%d %H:%i:%s\') as UpdateTime,price as LastPrice,vol as Volume,' \
                            'position_vol as OpenInterest,bid1_price as BidPrice1,bid1_vol as BidVolume1, ' \
                            'sell1_price as AskPrice1, sell1_vol as AskVolume1 from TB__{0}MI ' \
                            'where ndate > cast(\'{1}\' as date)'.format( symbol, startDate)

            else:
                #没有指定，所有日期数据
                sqlstring =' select \'{0}\' as InstrumentID,str_to_date(concat(ndate,\' \', ntime),' \
                           '\'%Y-%m-%d %H:%i:%s\') as UpdateTime,price as LastPrice,vol as Volume,' \
                           'position_vol as OpenInterest,bid1_price as BidPrice1,bid1_vol as BidVolume1, ' \
                           'sell1_price as AskPrice1, sell1_vol as AskVolume1 from TB__{0}MI '.format(symbol)

            print sqlstring

            count = cur.execute(sqlstring)

            # cx = cur.fetchall()
            fetch_counts = 0

            cx = None

            fetch_size = 1000

            while True:
                results = cur.fetchmany(fetch_size)

                if not results:
                    break

                if fetch_counts == 0:
                    cx = results
                else:
                    cx = cx + results

                fetch_counts = fetch_counts+fetch_size

                print u'历史TICK数据载入{0}条'.format(fetch_counts)

            self.writeLog(u'历史TICK数据载入完成，{1}~{2},共{0}条'.format(count,startDate,endDate))

            print u'策略引擎：历史TICK数据载入完成，{1}~{2},共{0}条'.format(count,startDate,endDate)

            return cx
        else:
            return None

    #----------------------------------------------------------------------
    def getMysqlDeltaDate(self,symbol, startDate, decreaseDays):
        """从mysql获取交易日天数差"""
        try:
            if self.__mysqlConnected:

                #获取指针
                cur = self.__mysqlConnection.cursor()

                sqlstring='select distinct ndate from TB_{0}MI where ndate < ' \
                          'cast(\'{1}\' as date) order by ndate desc limit {2},1'.format(symbol, startDate, decreaseDays-1)

                self.writeLog(sqlstring)

                count = cur.execute(sqlstring)

                if count > 0:

                    result = cur.fetchone()

                    return result[0]

                else:
                    self.writeLog(u'MysqlDB没有查询结果，请检查日期')

            else:
                self.writeLog(u'MysqlDB未连接，请检查')

        except MySQLdb.Error, e:
            self.writeLog(u'MysqlDB载入数据失败，请检查.Error %s'.format(e))

        td = timedelta(days=3)

        return startDate-td;
    #----------------------------------------------------------------------
    def saveBarToMysql(self,id, barList):
        """
        保存K线数据到数据库
        id， 回测ID
        barList， 对象为Bar的列表
        """

        # 保存本地pickle文件
        resultPath=os.getcwd()+'\/result'

        if not os.path.isdir(resultPath):
            os.mkdir(resultPath)

        resultFile = u'{0}\\{1}_Bar.pickle'.format(resultPath,id)

        cache= open(resultFile, mode='w')

        cPickle.dump(barList,cache)

        cache.close()

        # 保存数据库

        self.__connectMysql()

        if self.__mysqlConnected:
            sql = 'insert into BackTest.TB_Bar ' \
                  '(Id, symbol, open,high, low,close,date,time,datetime, volume, openInterest) ' \
                  'values '

            values = ''

            print u'共{0}条Bar记录.'.format(len(barList))

            if len(barList) == 0:
                return

            counts = 0

            for bar in barList:

                if len(values) > 0:
                    values = values + ','

                values = values + '(\'{0}\',\'{1}\',{2},{3},{4},{5},\'{6}\',\'{7}\',\'{8}\',{9},{10})'.format(
                    id,
                    bar.symbol,
                    bar.open,
                    bar.high,
                    bar.low,
                    bar.close,
                    bar.date,
                    bar.time,
                    bar.datetime.strftime('%Y-%m-%d %H:%M:%S'),
                    bar.volume,
                    bar.openInterest)

                if counts >= 3600:



                    self.__executeMysql(sql+values)

                    print u'写入{0}条Bar记录'.format(counts)

                    counts = 0
                    values = ''

                else:
                    counts = counts + 1

            if counts > 0:

                self.__executeMysql(sql+values)
                print u'写入{0}条Bar记录'.format(counts)


    #----------------------------------------------------------------------
    def saveEmaToMysql(self, id, emaList):
        """
        保存EMA到数据库
        id,回测的编号
        """

        # 保存本地pickle文件
        resultPath=os.getcwd()+'\/result'

        if not os.path.isdir(resultPath):
            os.mkdir(resultPath)

        resultFile = u'{0}\\{1}_Ema.pickle'.format(resultPath, id)
        cache= open(resultFile, mode='w')
        cPickle.dump(emaList,cache)
        cache.close()

        self.__connectMysql()

        if self.__mysqlConnected:
            sql = 'insert into BackTest.TB_Ema ' \
                    '(Id, symbol ,fastEMA,slowEMA ,date ,time ,datetime) ' \
                    'values '

            values = ''

            print u'共{0}条EMA记录.'.format(len(emaList))

            if len(emaList) == 0:
                return

            counts = 0

            for ema in emaList:

                if len(values) > 0:
                    values = values + ','

                values = values + '(\'{0}\',\'{1}\',{2},{3},\'{4}\',\'{5}\',\'{6}\')'.format(
                    id,
                    ema.symbol,
                    ema.fastEMA,
                    ema.slowEMA,
                    ema.date,
                    ema.time,
                    ema.datetime.strftime('%Y-%m-%d %H:%M:%S'))

                if counts >= 3600:

                    self.__executeMysql(sql+values)
                    print u'写入{0}条EMA记录'.format(counts)

                    counts = 0
                    values = ''

                else:
                    counts = counts + 1

            if counts > 0:

                self.__executeMysql(sql+values)
                print u'写入{0}条EMA记录'.format(counts)


    #----------------------------------------------------------------------
    def updateMarketData(self, event):
        """行情更新"""
        data = event.dict_['data']

        symbol = data['InstrumentID']
        
        # 检查是否存在交易该合约的策略
        if symbol in self.__dictSymbolStrategy:
            # 创建TICK数据对象并更新数据
            tick = Tick(symbol)

            # tick.openPrice = data['OpenPrice']
            # tick.highPrice = data['HighestPrice']
            # tick.lowPrice = data['LowestPrice']
            tick.lastPrice = float(data['LastPrice'])

            tick.volume = data['Volume']
            tick.openInterest = data['OpenInterest']

            #  tick.upperLimit = data['UpperLimitPrice']
            #  tick.lowerLimit = data['LowerLimitPrice']

            tick.time = data['UpdateTime']

            tick.bidPrice1 = float(data['BidPrice1'])
            # tick.bidPrice2 = data['BidPrice2']
            # tick.bidPrice3 = data['BidPrice3']
            # tick.bidPrice4 = data['BidPrice4']
            # tick.bidPrice5 = data['BidPrice5']

            tick.askPrice1 = float(data['AskPrice1'])
            # tick.askPrice2 = data['AskPrice2']
            # tick.askPrice3 = data['AskPrice3']
            # tick.askPrice4 = data['AskPrice4']
            # tick.askPrice5 = data['AskPrice5']

            tick.bidVolume1 = data['BidVolume1']
            # tick.bidVolume2 = data['BidVolume2']
            # tick.bidVolume3 = data['BidVolume3']
            # tick.bidVolume4 = data['BidVolume4']
            # tick.bidVolume5 = data['BidVolume5']

            tick.askVolume1 = data['AskVolume1']
            # tick.askVolume2 = data['AskVolume2']
            # tick.askVolume3 = data['AskVolume3']
            # tick.askVolume4 = data['AskVolume4']
            # tick.askVolume5 = data['AskVolume5']

            # 首先检查停止单是否需要发出
            self.__processStopOrder(tick)
            
            # 将该TICK数据推送给每个策略
            for strategy in self.__dictSymbolStrategy[symbol]:
                strategy.onTick(tick) 
        
        # 将数据插入MongoDB/Mysql数据库，实盘建议另开程序记录TICK数据
        if not self.backtesting:
            # self.__recordTickToMongo(data)
            self.__recordTickToMysql(data)

    #----------------------------------------------------------------------
    def __processStopOrder(self, tick):
        """处理停止单"""
        symbol = tick.symbol
        lastPrice = tick.lastPrice
        upperLimit = tick.upperLimit
        lowerLimit = tick.lowerLimit
        
        # 如果当前有该合约上的止损单
        if symbol in self.__dictStopOrder:

            # 获取止损单列表
            listSO = self.__dictStopOrder[symbol]     # SO:stop order
            
            # 准备一个空的已发止损单列表
            listSent = []
            
            for so in listSO:
                # 如果是买入停止单，且最新成交价大于停止触发价
                if so.direction == DIRECTION_BUY and lastPrice >= so.price:
                    # 以当日涨停价发出限价单买入
                    print u'sendOrder({0},{1},{2},{3},{4}'.format(symbol,'Direction_Buy',so.offset,upperLimit,so.volume)
                    ref = self.sendOrder(symbol, DIRECTION_BUY, so.offset, 
                                         upperLimit, so.volume, tick.time, so.strategy)
                    
                    # 触发策略的止损单发出更新
                    so.strategy.onStopOrder(ref)
                    
                    # 将该止损单对象保存到已发送列表中
                    listSent.append(so)
                
                # 如果是卖出停止单，且最新成交价小于停止触发价
                elif so.direction == DIRECTION_SELL and lastPrice <= so.price:
                    print u'sendOrder({0},{1},{2},{3},{4}'.format(symbol,'Direction_Sell',so.offset,upperLimit,so.volume)
                    ref = self.sendOrder(symbol, DIRECTION_SELL, so.offset,
                                         lowerLimit, so.volume,tick.time, so.strategy)
                    
                    so.strategy.onStopOrder(ref)
                    
                    listSent.append(so)
                    
            # 从停止单列表中移除已经发单的停止单对象
            if listSent:
                for so in listSent:
                    listSO.remove(so)
                    
            # 检查停止单列表是否为空，若为空，则从停止单字典中移除该合约代码
            if not listSO:
                del self.__dictStopOrder[symbol]



    #----------------------------------------------------------------------
    def updateOrder(self, event):
        """事件响应：报单更新"""

        data = event.dict_['data']
        orderRef = data['OrderRef']
        
        # 检查是否存在监听该报单的策略
        if orderRef in self.__dictOrderRefStrategy:
            
            # 创建Order数据对象
            order = Order(data['InstrumentID'])
            
            order.orderRef = data['OrderRef']
            order.direction = data['Direction']
            order.offset = data['CombOffsetFlag']
            
            order.price = data['LimitPrice']
            order.volumeOriginal = data['VolumeTotalOriginal']
            order.volumeTraded = data['VolumeTraded']
            order.insertTime = data['InsertTime']
            order.cancelTime = data['CancelTime']
            order.frontID = data['FrontID']
            order.sessionID = data['SessionID']
            
            order.status = data['OrderStatus']
            
            # 推送给策略
            strategy = self.__dictOrderRefStrategy[orderRef]
            strategy.onOrder(order)
            
        # 记录该Order的数据
        self.__dictOrder[orderRef] = data

    #----------------------------------------------------------------------
    def updateTrade(self, event):
        """事件响应：成交更新"""

        data = event.dict_['data']
        orderRef = data['OrderRef']
        
        if orderRef in self.__dictOrderRefStrategy:
            
            # 创建Trade数据对象
            trade = Trade(data['InstrumentID'])       # 合约代码

            trade.orderRef = orderRef                # 报单号
            trade.tradeID = data['TradeID']          # 成交编号
            trade.direction = data['Direction']      # 方向
            trade.offset = data['OffsetFlag']        # 开平
    
            trade.price = data['Price']              # 成交价
            trade.volume = data['Volume']            # 成交量

            trade.tradeTime = data['TradeTime']      # 成交时间
            
            # 推送给策略
            strategy = self.__dictOrderRefStrategy[orderRef]
            strategy.onTrade(trade)

    #----------------------------------------------------------------------
    def sendOrder(self, symbol, direction, offset, price, volume, ordertime, strategy):
        """
        发单（仅允许限价单）
        symbol：合约代码
        direction：方向，DIRECTION_BUY/DIRECTION_SELL
        offset：开平，OFFSET_OPEN/OFFSET_CLOSE
        price：下单价格
        volume：下单手数
        ordertime:下单时间（回归测试使用）
        strategy：策略对象 
        """

        contract = self.mainEngine.selectInstrument(symbol)
        
        if contract:
            # 调用主引擎的发单函数
            ref = self.mainEngine.sendOrder(symbol,
                                            contract['ExchangeID'],
                                            price,
                                            PRICETYPE_LIMIT,
                                            volume,
                                            direction,
                                            offset,
                                            ordertime)

            # 添加报单编号及其映射的策略
        self.__dictOrderRefStrategy[ref] = strategy


        return ref

    #----------------------------------------------------------------------
    def cancelOrder(self, orderRef):
        """
        撤单
        """
        print u'strategyEngine.py cancelOrder() begin.'
        order = self.__dictOrder[orderRef]
        symbol = order['InstrumentID']
        contract = self.mainEngine.selectInstrument(symbol)
        
        if contract:
            #调用主引擎的撤单函数
            self.mainEngine.cancelOrder(symbol,
                                        contract['ExchangeID'],
                                        orderRef,
                                        order['FrontID'],
                                        order['SessionID'])

        print u'strategyEngine.py cancelOrder() end.'

    #----------------------------------------------------------------------
    def __registerEvent(self):
        """注册事件监听"""

        # 注册 订阅行情数据更新事件
        self.__eventEngine.register(EVENT_MARKETDATA, self.updateMarketData)

        # 注册 订阅订单更新事件
        self.__eventEngine.register(EVENT_ORDER, self.updateOrder)

        # 注册 订阅交易响应事件
        self.__eventEngine.register(EVENT_TRADE ,self.updateTrade)
        
    #----------------------------------------------------------------------
    def writeLog(self, log):
        """写日志"""
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
    #----------------------------------------------------------------------
    def registerStrategy(self, symbol, strategy):
        """注册策略对合约TICK数据的监听"""
        print u'strategyEngine.py registerStrategy() begin.'
        # 尝试获取监听该合约代码的策略的列表，若无则创建
        try:
            listStrategy = self.__dictSymbolStrategy[symbol]
        except KeyError:
            listStrategy = []
            self.__dictSymbolStrategy[symbol] = listStrategy
        
        # 防止重复注册
        if strategy not in listStrategy:
            listStrategy.append(strategy)

        print u'strategyEngine.py registerStrategy() end.'

    #----------------------------------------------------------------------
    def placeStopOrder(self, symbol, direction, offset, price, volume, strategy):
        """
        下停止单（止损单，运行于本地引擎中）
        注意这里的price是停止单的触发价
        """
        # 创建止损单对象
        print u'strategyEngine.py placeStopOrder() symbol:{0}, direction:{1}, offset:{2}, price:{3}, volume:{4}.'\
            .format(symbol, direction, offset, price, volume)

        so = StopOrder(symbol, direction, offset, price, volume, strategy)
        
        # 获取该合约相关的止损单列表
        try:
            listSO = self.__dictStopOrder[symbol]
        except KeyError:
            listSO = []
            self.__dictStopOrder[symbol] = listSO
        
        # 将该止损单插入列表中
        listSO.append(so)

        return so
    
    #----------------------------------------------------------------------
    def cancelStopOrder(self, so):
        """撤销停止单"""

        symbol = so.symbol
        
        try:
            listSO = self.__dictStopOrder[symbol]

            if so in listSO:
                listSO.remove(so)
            
            if not listSO:
                del self.__dictStopOrder[symbol]
        except KeyError:
            pass

        
    #----------------------------------------------------------------------
    def startAll(self):
        """启动所有策略"""
        print( u'启动所有策略')
        for strategy in self.dictStrategy.values():

            strategy.start()
            
    #----------------------------------------------------------------------
    def stopAll(self):
        """停止所有策略"""
        print(u'停止所有策略')
        for strategy in self.dictStrategy.values():
            strategy.stop()

    #----------------------------------------------------------------------
    def saveData(self,id):
        """保存所有策略的过程数据"""
        print(u'保存所有策略的过程数据')
        for strategy in self.dictStrategy.values():
            strategy.saveData(id)

########################################################################
class StrategyTemplate(object):
    """策略模板"""

    #----------------------------------------------------------------------
    def __init__(self, name, symbol, engine):
        """Constructor"""
        self.name = name            # 策略名称（注意唯一性）
        self.symbol = symbol        # 策略交易的合约
        self.engine = engine        # 策略引擎对象
        
        self.trading = False        # 策略是否启动交易
        
    #----------------------------------------------------------------------
    def onTick(self, tick):
        """行情更新"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onTrade(self, trade):
        """交易更新"""
        raise NotImplementedError
        
    #----------------------------------------------------------------------
    def onOrder(self, order):
        """报单更新"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onStopOrder(self, orderRef):
        """停止单更新"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def onBar(self, o, h, l, c, volume, time):
        """K线数据更新"""
        raise NotImplementedError
        
    #----------------------------------------------------------------------
    def start(self):
        """
        启动交易
        这里是最简单的改变self.trading
        有需要可以重新实现更复杂的操作
        """
        self.trading = True
        self.engine.writeLog(self.name + u'开始运行')

    #----------------------------------------------------------------------
    def saveData(self,Id):
        """保存数据"""
        raise NotImplementedError

    #----------------------------------------------------------------------
    def stop(self):
        """
        停止交易
        同上
        """
        self.trading = False
        self.engine.writeLog(self.name + u'停止运行')
        
    #----------------------------------------------------------------------
    def loadSetting(self, setting):
        """
        载入设置
        setting通常是一个包含了参数设置的字典
        """
        raise NotImplementedError
        
    #----------------------------------------------------------------------
    def buy(self, price, volume, orderTime, stopOrder=False ):
        """买入开仓"""

        print u'strategyEngine.py StrategyTemplate({3}) buy(symbol:{0}, price:{1},volume:{2},time:{4})'.\
            format(self.symbol, price, volume, self.name,orderTime)

        if self.trading:
            if stopOrder:
                # 止损单
                so = self.engine.placeStopOrder(self.symbol, DIRECTION_BUY, 
                                                  OFFSET_OPEN, price, volume, self)
                return so
            else:
                # 委托单
                ref = self.engine.sendOrder(self.symbol, DIRECTION_BUY,
                                              OFFSET_OPEN, price, volume, orderTime, self)
                return ref
        else:
            return None

        #print (u'strategyEngine.py buy() end.')

    #----------------------------------------------------------------------
    def cover(self, price, volume,orderTime, stopOrder=False):
        """买入平仓"""

        print u'strategyEngine.py StrategyTemplate({3}) cover(symbol:{0}, price:{1},volume:{2},time:{4})'.\
            format(self.symbol, price, volume, self.name, orderTime)

        if self.trading:
            if stopOrder:

                # 止损单
                so = self.engine.placeStopOrder(self.symbol, DIRECTION_BUY,
                                                  OFFSET_CLOSE, price, volume, self)
                return so
            else:
                # 委托单
                ref = self.engine.sendOrder(self.symbol, DIRECTION_BUY,
                                              OFFSET_CLOSE, price, volume, orderTime, self)
                return ref
        else:
            return None
        print (u'strategyEngine.py cover() end.')

    #----------------------------------------------------------------------
    def sell(self, price, volume, orderTime, stopOrder=False):
        """卖出平仓"""

        print u'strategyEngine.py  StrategyTemplate({3}) sell(symbol:{0}, price:{1},volume:{2},time:{4})'.\
            format(self.symbol, price, volume, self.name, orderTime)

        if self.trading:
            if stopOrder:
                # 止损单
                so = self.engine.placeStopOrder(self.symbol, DIRECTION_SELL,
                                                  OFFSET_CLOSE, price, volume, self)
                return so
            else:
                # 委托单
                ref = self.engine.sendOrder(self.symbol, DIRECTION_SELL,
                                              OFFSET_CLOSE, price, volume, orderTime, self)
                return ref
        else:
            return None
        #print u'strategyEngine.py sell() end.'

    #----------------------------------------------------------------------
    def short(self, price, volume, orderTime, stopOrder=False):
        """卖出开仓"""
        print u'strategyEngine.py StrategyTemplate({3}) short(symbol:{0}, price:{1},volume:{2},time:{4})'.\
            format(self.symbol, price, volume, self.name, orderTime)
        if self.trading:
            if stopOrder:
                # 止损单
                so = self.engine.placeStopOrder(self.symbol, DIRECTION_SELL,
                                                  OFFSET_OPEN, price, volume, self)
                return so
            else:
                # 委托单
                ref = self.engine.sendOrder(self.symbol, DIRECTION_SELL, 
                                              OFFSET_OPEN, price, volume, orderTime, self)
                return ref    
        else:
            return None


    #----------------------------------------------------------------------
    def cancelOrder(self, orderRef):
        """撤单"""
        self.engine.cancelOrder(orderRef)

    #----------------------------------------------------------------------
    def cancelStopOrder(self, so):
        """撤销停止单"""
        self.engine.cancelStopOrder(so)
    
    