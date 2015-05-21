# encoding: UTF-8

from datetime import datetime

from pymongo import Connection
from pymongo.errors import *

from eventEngine import *


# 常量定义
OFFSET_OPEN = '0'           # 开仓
OFFSET_CLOSE = '1'          # 平仓

DIRECTION_BUY = '0'         # 买入
DIRECTION_SELL = '1'        # 卖出

PRICETYPE_LIMIT = '2'       # 限价



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
class Trade:
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
 

########################################################################
class Order:
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


########################################################################
class StopOrder:
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
    def __init__(self, eventEngine, mainEngine):
        """Constructor"""
        self.__eventEngine = eventEngine
        self.mainEngine = mainEngine
        
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
        
        # 保存合约代码和相关停止单的字典
        # key为合约代码
        # value为该合约相关的停止单列表
        self.__dictStopOrder = {}
        
        # MongoDB数据库相关
        self.__mongoConnected = False
        self.__mongoConnection = None
        self.__mongoTickDB = None
        
        # 调用函数
        self.__connectMongo()
        self.createStrategy()
        self.__registerEvent()
        
    #----------------------------------------------------------------------
    def createStrategy(self, strategyName, strategySymbol, strategyClass, strategySetting):
        """创建策略"""
        strategy = strategyClass(strategyName, strategySymbol, self)
        self.dictStrategy[strategyName] = strategy
        strategy.initSetting(strategySetting)
    
    #----------------------------------------------------------------------
    def __connectMongo(self):
        """连接MongoDB数据库"""
        try:
            self.__mongoConnection = Connection()
            self.__mongoConnected = True
            self.__mongoTickDB = self.__mongoConnection['TickDB']
            self.writeLog(u'策略引擎连接MongoDB成功')
        except ConnectionFailure:
            self.writeLog(u'策略引擎连接MongoDB失败')

    #----------------------------------------------------------------------
    def __recordTick(self, data):
        """将Tick数据插入到MongoDB中"""
        if self.__mongoConnected:
            symbol = data['InstrumentID']
            data['date'] = self.today
            self.__mongoTickDB[symbol].insert(data)
        
    #----------------------------------------------------------------------
    def loadTick(self, symbol, dt):
        """从MongoDB中读取Tick数据"""
        if self.__mongoConnected:
            collection = self.__mongoTickDB[symbol]
            cx = collection.find({'date':{'$gte':dt}})
            return cx
        else:
            return None  

    #----------------------------------------------------------------------
    def __updateMarketData(self, event):
        """行情更新"""
        data = event.dict_['data']
        symbol = data['InstrumentID']
        
        # 检查是否存在交易该合约的策略
        if symbol in self.__dictSymbolStrategy:
            # 创建TICK数据对象并更新数据
            tick = Tick(symbol)
            
            tick.openPrice = data['OpenPrice']
            tick.highPrice = data['HighestPrice']
            tick.lowPrice = data['LowestPrice']
            tick.lastPrice = data['LastPrice']
            
            tick.volume = data['Volume']
            tick.openInterest = data['OpenInterest']
            
            tick.upperLimit = data['UpperLimitPrice']
            tick.lowerLimit = data['LowerLimitPrice']
            
            tick.time = data['UpdateTime']
            tick.ms = data['UpdateMillisec']
            
            tick.bidPrice1 = data['BidPrice1']
            tick.bidPrice2 = data['BidPrice2']
            tick.bidPrice3 = data['BidPrice3']
            tick.bidPrice4 = data['BidPrice4']
            tick.bidPrice5 = data['BidPrice5']
            
            tick.askPrice1 = data['AskPrice1']
            tick.askPrice2 = data['AskPrice2']
            tick.askPrice3 = data['AskPrice3']
            tick.askPrice4 = data['AskPrice4']
            tick.askPrice5 = data['AskPrice5']   
            
            tick.bidVolume1 = data['BidVolume1']
            tick.bidVolume2 = data['BidVolume2']
            tick.bidVolume3 = data['BidVolume3']
            tick.bidVolume4 = data['BidVolume4']
            tick.bidVolume5 = data['BidVolume5']
            
            tick.askVolume1 = data['AskVolume1']
            tick.askVolume2 = data['AskVolume2']
            tick.askVolume3 = data['AskVolume3']
            tick.askVolume4 = data['AskVolume4']
            tick.askVolume5 = data['AskVolume5']   
            
            # 首先检查停止单是否需要发出
            self.__processStopOrder(tick)
            
            # 将该TICK数据推送给每个策略
            for strategy in self.__dictSymbolStrategy[symbol]:
                strategy.onTick(tick) 
        
        # 将数据插入MongoDB数据库，实盘建议另开程序记录TICK数据
        self.__recordTick(data)
            
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
                    ref = self.sendOrder(symbol, DIRECTION_BUY, so.offset, 
                                         upperLimit, so.volume, strategy)    
                    
                    # 触发策略的止损单发出更新
                    so.strategy.onStopOrder(ref)
                    
                    # 将该止损单对象保存到已发送列表中
                    listSent.append(so)
                
                # 如果是卖出停止单，且最新成交价小于停止触发价
                elif so.direction == DIRECTION_SELL and lastPrice <= so.price:
                    ref = self.sendOrder(symbol, DIRECTION_SELL, so.offset,
                                         lowerLimit, so.volume, strategy)
                    
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
    def __updateOrder(self, event):
        """报单更新"""
        data = event.dict_['data']
        orderRef = data['OrderRef']
        
        # 检查是否存在监听该报单的策略
        if orderRef in self.__dictOrderRefStrategy:
            
            # 创建Order数据对象
            order = Order(data['InstrumentID'])
            
            order.orderRef = data['OrderRef']
            order.direction = data['Direction']
            order.offset = data['ComboOffsetFlag']
            
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
    def __updateTrade(self, event):
        """成交更新"""
        data = event.dict_['data']
        orderRef = data['OrderRef']
        
        if orderRef in self.__dictOrderRefStrategy:
            
            # 创建Trade数据对象
            trade = Trade(data['InstrumentID'])
            
            trade.orderRef = orderRef
            trade.tradeID = data['TradeID']
            trade.direction = data['Direction']
            trade.offset = data['OffsetFlag']
    
            trade.price = data['Price']
            trade.volume = data['Volume']
            
            # 推送给策略
            strategy = self.__dictOrderRefStrategy[orderRef]
            strategy.onTrade(trade)            
        
    #----------------------------------------------------------------------
    def sendOrder(self, symbol, direction, offset, price, volume, strategy):
        """
        发单（仅允许限价单）
        symbol：合约代码
        direction：方向，DIRECTION_BUY/DIRECTION_SELL
        offset：开平，OFFSET_OPEN/OFFSET_CLOSE
        price：下单价格
        volume：下单手数
        strategy：策略对象 
        """
        contract = self.mainEngine.selectInstrument(symbol)
        
        if contract:
            ref = self.mainEngine.sendOrder(symbol,
                                            contract['ExchangeID'],
                                            price,
                                            PRICETYPE_LIMIT,
                                            volume,
                                            direction,
                                            offset)
            
        self.__dictOrderRefStrategy[ref] = strategy
        
        return ref

    #----------------------------------------------------------------------
    def cancelOrder(self, orderRef):
        """
        撤单
        """
        order = self.__dictOrder[orderRef]
        symbol = order['InstrumentID']
        contract = self.mainEngine.selectInstrument(symbol)
        
        if contract:
            self.mainEngine.cancelOrder(symbol,
                                        contract['ExchangeID'],
                                        orderRef,
                                        order['FrontID'],
                                        order['SessionID'])
        
    #----------------------------------------------------------------------
    def __registerEvent(self):
        """注册事件监听"""
        self.__eventEngine.register(EVENT_MARKETDATA, self.__updateMarketData)
        self.__eventEngine.register(EVENT_ORDER, self.__updateOrder)
        self.__eventEngine.register(EVENT_TRADE ,self.__updateTrade)
        
    #----------------------------------------------------------------------
    def writeLog(self, log):
        """写日志"""
        event = Event(type_=EVENT_LOG)
        event.dict_['log'] = log
        self.__eventEngine.put(event)
        
    #----------------------------------------------------------------------
    def registerStrategy(self, symbol, strategy):
        """注册策略对合约TICK数据的监听"""
        # 尝试获取监听该合约代码的策略的列表，若无则创建
        try:
            listStrategy = self.__dictSymbolStrategy[symbol]
        except KeyError:
            listStrategy = []
            self.__dictSymbolStrategy[symbol] = listStrategy
        
        # 防止重复注册
        if strategy not in listStrategy:
            listStrategy.append(strategy)

    #----------------------------------------------------------------------
    def placeStopOrder(self, symbol, direction, offset, price, volume, strategy):
        """
        下停止单（运行于本地引擎中）
        注意这里的price是停止单的触发价
        """
        # 创建止损单对象
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
        for strategy in self.dictStrategy.values():
            strategy.start()
            
    #----------------------------------------------------------------------
    def stopAll(self):
        """停止所有策略"""
        for strategy in self.dictStrategy.values():
            strategy.stop()


########################################################################
class StrategyTemplate(object):
    """策略模板"""

    #----------------------------------------------------------------------
    def __init__(self, name, symbol, engine):
        """Constructor"""
        self.name = name            # 策略名称（注意唯一性）
        self.symbol = symbol        # 策略交易的合约
        self.__engine = engine      # 策略引擎对象
        
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
        
    #----------------------------------------------------------------------
    def stop(self):
        """
        停止交易
        同上
        """
        self.trading = False
        
    #----------------------------------------------------------------------
    def initSetting(self, setting):
        """
        初始化设置
        setting通常是一个包含了参数设置的字典
        """
        raise NotImplementedError
        
    #----------------------------------------------------------------------
    def __buy(self, price, volume, stopOrder=False):
        """买入开仓"""
        if self.trading:
            if stopOrder:
                so = self.__engine.placeStopOrder(self.symbol, DIRECTION_BUY, 
                                                  OFFSET_OPEN, price, volume, self)
                return so
            else:
                ref = self.__engine.sendOrder(self.symbol, DIRECTION_BUY,
                                              OFFSET_OPEN, price, volume, self)
                return ref
        else:
            return None
    
    #----------------------------------------------------------------------
    def __cover(self, price, volume, StopOrder=False):
        """买入平仓"""
        if self.trading:
            if stopOrder:
                so = self.__engine.placeStopOrder(self.symbol, DIRECTION_BUY,
                                                  OFFSET_CLOSE, price, volume, self)
                return so
            else:
                ref = self.__engine.sendOrder(self.symbol, DIRECTION_BUY,
                                              OFFSET_CLOSE, price, volume, self)
                return ref
        else:
            return None
    
    #----------------------------------------------------------------------
    def __sell(self, price, volume, stopOrder=False):
        """卖出平仓"""
        if self.trading:
            if stopOrder:
                so = self.__engine.placeStopOrder(self.symbol, DIRECTION_SELL,
                                                  OFFSET_CLOSE, price, volume, self)
                return so
            else:
                ref = self.__engine.sendOrder(self.symbol, DIRECTION_SELL,
                                              OFFSET_CLOSE, price, volume, self)
                return ref
        else:
            return None
    
    #----------------------------------------------------------------------
    def __short(self, price, volume, stopOrder=False):
        """卖出开仓"""
        if self.trading:
            if stopOrder:
                so = self.__engine.placeStopOrder(self.symbol, DIRECTION_SELL,
                                                  OFFSET_OPEN, price, volume, self)
                return so
            else:
                ref = self.__engine.sendOrder(self.symbol, DIRECTION_SELL, 
                                              OFFSET_OPEN, price, volume, self)
                return ref    
        else:
            return None
    
    #----------------------------------------------------------------------
    def __cancelOrder(self, orderRef):
        """撤单"""
        self.__engine.cancelOrder(orderRef)
        
    #----------------------------------------------------------------------
    def __cancelStopOrder(self, so):
        """撤销停止单"""
        self.__engine.cancelStopOrder(so)
    
    