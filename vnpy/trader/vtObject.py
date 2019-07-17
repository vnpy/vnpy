# encoding: UTF-8

import time
from datetime import datetime


from vnpy.trader.vtConstant import (EMPTY_STRING, EMPTY_UNICODE,
                                    EMPTY_FLOAT, EMPTY_INT, DIRECTION_LONG, DIRECTION_SHORT,
                                    OFFSET_OPEN, OFFSET_CLOSE,
                                    OFFSET_CLOSETODAY, OFFSET_CLOSEYESTERDAY)

from vnpy.trader.language import constant

########################################################################
class VtBaseData(object):
    """回调函数推送数据的基础类，其他数据类继承于此"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.gatewayName = EMPTY_STRING  # Gateway名称
        self.rawData = None  # 原始数据


########################################################################
class VtTickData(VtBaseData):
    """Tick行情数据类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(VtTickData, self).__init__()

        # 代码相关
        self.symbol = EMPTY_STRING  # 合约代码
        self.exchange = EMPTY_STRING  # 交易所代码
        self.vtSymbol = EMPTY_STRING  # 合约在vt系统中的唯一代码，通常是 合约代码.交易所代码

        # 成交数据
        self.lastPrice = EMPTY_FLOAT  # 最新成交价
        self.lastVolume = EMPTY_FLOAT  # 最新成交量
        self.volume = EMPTY_FLOAT  # 今天总成交量
        self.preOpenInterest = EMPTY_INT  # 昨持仓量
        self.openInterest = EMPTY_INT  # 持仓量
        self.time = EMPTY_STRING  # 时间 11:20:56.5
        self.date = EMPTY_STRING  # 日期 2015-10-09
        self.tradingDay = EMPTY_STRING  # 交易日期

        # 常规行情
        self.openPrice = EMPTY_FLOAT  # 今日开盘价
        self.highPrice = EMPTY_FLOAT  # 今日最高价
        self.lowPrice = EMPTY_FLOAT  # 今日最低价
        self.preClosePrice = EMPTY_FLOAT  # 昨收盘价

        self.upperLimit = EMPTY_FLOAT  # 涨停价
        self.lowerLimit = EMPTY_FLOAT  # 跌停价

        # 五档行情
        self.bidPrice1 = EMPTY_FLOAT
        self.bidPrice2 = EMPTY_FLOAT
        self.bidPrice3 = EMPTY_FLOAT
        self.bidPrice4 = EMPTY_FLOAT
        self.bidPrice5 = EMPTY_FLOAT

        self.askPrice1 = EMPTY_FLOAT
        self.askPrice2 = EMPTY_FLOAT
        self.askPrice3 = EMPTY_FLOAT
        self.askPrice4 = EMPTY_FLOAT
        self.askPrice5 = EMPTY_FLOAT

        self.bidVolume1 = EMPTY_FLOAT
        self.bidVolume2 = EMPTY_FLOAT
        self.bidVolume3 = EMPTY_FLOAT
        self.bidVolume4 = EMPTY_FLOAT
        self.bidVolume5 = EMPTY_FLOAT

        self.askVolume1 = EMPTY_FLOAT
        self.askVolume2 = EMPTY_FLOAT
        self.askVolume3 = EMPTY_FLOAT
        self.askVolume4 = EMPTY_FLOAT
        self.askVolume5 = EMPTY_FLOAT

    #----------------------------------------------------------------------
    @staticmethod
    def createFromGateway(gateway, symbol, exchange,
                          lastPrice, lastVolume,
                          highPrice, lowPrice,
                          openPrice=EMPTY_FLOAT,
                          openInterest=EMPTY_INT,
                          upperLimit=EMPTY_FLOAT,
                          lowerLimit=EMPTY_FLOAT):
        tick = VtTickData()
        tick.gatewayName = gateway.gatewayName
        tick.symbol = symbol
        tick.exchange = exchange
        tick.vtSymbol = symbol + '.' + exchange

        tick.lastPrice = lastPrice
        tick.lastVolume = lastVolume
        tick.openInterest = openInterest
        tick.datetime = datetime.now()
        tick.date = tick.datetime.strftime('%Y-%m-%d')
        tick.time = tick.datetime.strftime('%H:%M:%S')

        tick.openPrice = openPrice
        tick.highPrice = highPrice
        tick.lowPrice = lowPrice
        tick.upperLimit = upperLimit
        tick.lowerLimit = lowerLimit
        return tick


########################################################################
class VtBarData(VtBaseData):
    """K线数据"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(VtBarData, self).__init__()

        self.vtSymbol = EMPTY_STRING        # vt系统代码
        self.symbol = EMPTY_STRING          # 代码
        self.exchange = EMPTY_STRING        # 交易所

        self.open = EMPTY_FLOAT             # OHLC
        self.high = EMPTY_FLOAT
        self.low = EMPTY_FLOAT
        self.close = EMPTY_FLOAT

        self.date = EMPTY_STRING            # bar开始的时间，日期
        self.time = EMPTY_STRING            # 时间
        self.datetime = None                # python的datetime时间对象

        self.volume = EMPTY_FLOAT             # 成交量
        self.openInterest = EMPTY_INT       # 持仓量


class VtTradeData(VtBaseData):
    """成交数据类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(VtTradeData, self).__init__()

        # 账号代码相关
        self.accountID = EMPTY_STRING  # 账户代码
        self.vtAccountID = EMPTY_STRING  # 账户在vt中的唯一代码，通常是 Gateway名.账户代码

        # 代码编号相关
        self.symbol = EMPTY_STRING  # 合约代码
        self.exchange = EMPTY_STRING  # 交易所代码
        self.vtSymbol = EMPTY_STRING  # 合约在vt系统中的唯一代码，通常是 合约代码.交易所代码
        self.vtSymbolName = EMPTY_STRING

        self.tradeID = EMPTY_STRING  # 成交编号(来自交易所得）
        self.vtTradeID = EMPTY_STRING  # 成交在vt系统中的唯一编号，通常是 Gateway名.成交编号

        self.orderID = EMPTY_STRING     # 订单编号（一般是对应本地得委托号)
        self.vtOrderID = EMPTY_STRING   # 订单在vt系统中的唯一编号，通常是 Gateway名.订单编号

        self.sysOrderID = EMPTY_STRING  # 订单编号（来自交易所)

        # 成交相关
        self.direction = EMPTY_UNICODE  # 成交方向
        self.offset = EMPTY_UNICODE  # 成交开平仓
        self.price = EMPTY_FLOAT  # 成交价格
        self.volume = EMPTY_FLOAT  # 成交数量
        self.tradeTime = EMPTY_STRING  # 成交时间
        self.dt = None              # 成交时间（datetime类型）

        self.strategy = EMPTY_STRING  # 策略实例名

        # 股票使用
        self.tradeAmount = EMPTY_FLOAT  # 成交金额
        self.commission = EMPTY_FLOAT  # 手续费(印花税+佣金+过户费）
        self.holder_id = EMPTY_STRING  # 股东代码
        self.comment = EMPTY_STRING    # 备注

    #----------------------------------------------------------------------
    @staticmethod
    def createFromGateway(gateway, symbol, exchange, tradeID, orderID, direction, tradePrice, tradeVolume, sysOrderID=EMPTY_STRING):
        trade = VtTradeData()
        trade.gatewayName = gateway.gatewayName
        trade.symbol = symbol
        trade.exchange = exchange
        trade.vtSymbol = symbol + '.' + exchange

        trade.orderID = orderID
        trade.vtOrderID = trade.gatewayName + '.' + trade.tradeID
        trade.sysOrderID = sysOrderID

        trade.tradeID = tradeID
        trade.vtTradeID = trade.gatewayName + '.' + tradeID

        trade.direction = direction
        trade.price = tradePrice
        trade.volume = tradeVolume
        trade.tradeTime = datetime.now().strftime('%H:%M:%S')
        return trade

    #----------------------------------------------------------------------
    @staticmethod
    def createFromOrderData(order,
                            tradeID,
                            tradePrice,
                            tradeVolume):  # type: (VtOrderData, str, float, float)->VtTradeData
        trade = VtTradeData()
        trade.gatewayName = order.gatewayName
        trade.symbol = order.symbol
        trade.vtSymbol = order.vtSymbol

        trade.orderID = order.orderID
        trade.vtOrderID = order.vtOrderID
        trade.sysOrderID = getattr(order,'sysOrderID', trade.orderID)
        trade.tradeID = tradeID
        trade.vtTradeID = trade.gatewayName + '.' + tradeID
        trade.direction = order.direction
        trade.price = tradePrice
        trade.volume = tradeVolume
        trade.tradeTime = datetime.now().strftime('%H:%M:%S')
        return trade


########################################################################
class VtOrderData(VtBaseData):
    """订单数据类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(VtOrderData, self).__init__()

        # 账号代码相关
        self.accountID = EMPTY_STRING  # 账户代码
        self.vtAccountID = EMPTY_STRING  # 账户在vt中的唯一代码，通常是 Gateway名.账户代码

        # 代码编号相关
        self.symbol = EMPTY_STRING  # 合约代码
        self.exchange = EMPTY_STRING  # 交易所代码
        self.vtSymbol = EMPTY_STRING  # 合约在vt系统中的唯一代码，通常是 合约代码.交易所代码
        self.vtSymbolName = EMPTY_STRING

        self.orderID = EMPTY_STRING  # 订单编号(本地生成）
        self.vtOrderID = EMPTY_STRING  # 订单在vt系统中的唯一编号，通常是 Gateway名.订单编号
        self.sysOrderID = EMPTY_STRING  # 订单编号（来自交易所)

        # 报单相关
        self.direction = EMPTY_UNICODE  # 报单方向
        self.offset = EMPTY_UNICODE  # 报单开平仓
        self.price = EMPTY_FLOAT  # 报单价格
        self.totalVolume = EMPTY_FLOAT  # 报单总数量
        self.tradedVolume = EMPTY_FLOAT  # 报单成交数量
        self.status = EMPTY_UNICODE  # 报单状态

        self.orderTime = EMPTY_STRING  # 发单时间
        self.updateTime = EMPTY_STRING  # 最后更新时间
        self.cancelTime = EMPTY_STRING  # 撤单时间

        # CTP/LTS相关
        self.frontID = EMPTY_INT  # 前置机编号
        self.sessionID = EMPTY_INT  # 连接编号

        # 股票相关
        self.holder_id = EMPTY_STRING  # 股东代码

    #----------------------------------------------------------------------
    @staticmethod
    def createFromGateway(gateway,                          # type: VtGateway
                          orderId,                          # type: str
                          symbol,                           # type: str
                          exchange,                         # type: str
                          price,                            # type: float
                          volume,                           # type: int
                          direction,                        # type: str
                          offset=EMPTY_UNICODE,             # type: str
                          tradedVolume=EMPTY_INT,           # type: int
                          status=constant.STATUS_UNKNOWN,   # type: str
                          orderTime=EMPTY_UNICODE,          # type: str
                          cancelTime=EMPTY_UNICODE,         # type: str
                          sysOrderID=EMPTY_STRING           # type：str
                          ):                                # type: (...)->VtOrderData
        vtOrder = VtOrderData()
        vtOrder.gatewayName = gateway.gatewayName
        vtOrder.symbol = symbol
        vtOrder.exchange = exchange
        vtOrder.vtSymbol = symbol + '.' + exchange
        vtOrder.orderID = orderId
        vtOrder.vtOrderID = gateway.gatewayName + '.' + orderId
        vtOrder.sysOrderID = sysOrderID

        vtOrder.direction = direction
        vtOrder.offset = offset
        vtOrder.price = price
        vtOrder.totalVolume = volume
        vtOrder.tradedVolume = tradedVolume
        vtOrder.status = status
        vtOrder.orderTime = orderTime
        vtOrder.cancelTime = cancelTime
        return vtOrder

########################################################################
class VtPositionData(VtBaseData):
    """持仓数据类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(VtPositionData, self).__init__()

        # 账号代码相关
        self.accountID = EMPTY_STRING  # 账户代码
        self.vtAccountID = EMPTY_STRING  # 账户在vt中的唯一代码，通常是 Gateway名.账户代码

        # 代码编号相关
        self.symbol = EMPTY_STRING  # 合约代码
        self.exchange = EMPTY_STRING  # 交易所代码
        self.vtSymbol = EMPTY_STRING  # 合约在vt系统中的唯一代码，合约代码.交易所代码
        self.vtSymbolName = EMPTY_STRING

        # 持仓相关
        self.direction = EMPTY_STRING  # 持仓方向
        self.position = EMPTY_INT  # 持仓量
        self.frozen = EMPTY_INT  # 冻结数量
        self.price = EMPTY_FLOAT  # 持仓均价
        self.vtPositionName = EMPTY_STRING  # 持仓在vt系统中的唯一代码，通常是vtSymbol.方向
        self.ydPosition = EMPTY_INT  # 昨持仓
        self.positionProfit = EMPTY_FLOAT  # 持仓盈亏

        # 股票相关
        self.holder_id = EMPTY_STRING  # 股东代码
    #----------------------------------------------------------------------
    @staticmethod
    def createFromGateway(gateway,                      # type: VtGateway
                          exchange,                     # type: str
                          symbol,                       # type: str
                          direction,                    # type: str
                          position,                     # type: int
                          frozen=EMPTY_INT,             # type: int
                          price=EMPTY_FLOAT,            # type: float
                          yestordayPosition=EMPTY_INT,  # type: int
                          profit=EMPTY_FLOAT            # type: float
                          ):                            # type: (...)->VtPositionData
        vtPosition = VtPositionData()
        vtPosition.gatewayName = gateway.gatewayName
        vtPosition.symbol = symbol
        vtPosition.exchange = exchange
        vtPosition.vtSymbol = symbol + '.' + exchange

        vtPosition.direction = direction
        vtPosition.position = position
        vtPosition.frozen = frozen
        vtPosition.price = price
        vtPosition.vtPositionName = vtPosition.vtSymbol + '.' + direction
        vtPosition.ydPosition = yestordayPosition
        vtPosition.positionProfit = profit
        return vtPosition


########################################################################
class VtAccountData(VtBaseData):
    """账户数据类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(VtAccountData, self).__init__()

        # 账号代码相关
        self.accountID = EMPTY_STRING  # 账户代码
        self.vtAccountID = EMPTY_STRING  # 账户在vt中的唯一代码，通常是 Gateway名.账户代码

        # 数值相关
        self.preBalance = EMPTY_FLOAT  # 昨日账户结算净值
        self.balance = EMPTY_FLOAT  # 账户净值
        self.available = EMPTY_FLOAT  # 可用资金
        self.frozen = EMPTY_FLOAT      # 冻结资金
        self.withdraw = EMPTY_FLOAT    # 可取资金
        self.commission = EMPTY_FLOAT  # 今日手续费
        self.margin = EMPTY_FLOAT  # 保证金占用
        self.closeProfit = EMPTY_FLOAT  # 平仓盈亏
        self.positionProfit = EMPTY_FLOAT  # 持仓盈亏

        self.tradingDay = EMPTY_STRING  # 当前交易日

        self.currency = EMPTY_STRING    # 币种（缺省人民币）

########################################################################
class VtFundsFlowData(VtBaseData):
    """历史资金流水数据类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(VtFundsFlowData, self).__init__()

        # 账号代码相关
        self.accountID = EMPTY_STRING  # 账户代码
        self.vtAccountID = EMPTY_STRING  # 账户在vt中的唯一代码，通常是 Gateway名.账户代码

        self.currency = EMPTY_STRING            # 币种
        self.trade_date = EMPTY_STRING          # 成交日期
        self.trade_price = EMPTY_FLOAT          # 成交价格
        self.trade_volume = EMPTY_FLOAT         # 成交数量
        self.trade_amount = EMPTY_FLOAT         # 发生金额( 正数代表卖出，或者转入资金，获取分红等，负数代表买入股票或者出金)
        self.fund_remain = EMPTY_FLOAT          # 资金余额
        self.contract_id = EMPTY_STRING         # 合同编号
        self.business_name = EMPTY_STRING       # 业务名称
        self.symbol = EMPTY_STRING              # 合约代码（证券代码）
        self.holder_id = EMPTY_STRING           # 股东代码
        self.direction = EMPTY_STRING           # 买卖类别：转,买，卖..
        self.comment = EMPTY_STRING             # 备注

########################################################################
class VtErrorData(VtBaseData):
    """错误数据类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(VtErrorData, self).__init__()

        self.errorID = EMPTY_STRING  # 错误代码
        self.errorMsg = EMPTY_UNICODE  # 错误信息
        self.additionalInfo = EMPTY_UNICODE  # 补充信息

        self.errorTime = time.strftime('%X', time.localtime())  # 错误生成时间

########################################################################
class VtLogData(VtBaseData):
    """日志数据类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(VtLogData, self).__init__()

        # self.logTime = time.strftime('%X:%f', time.localtime())    # 日志生成时间
        self.logTime = datetime.now().strftime('%X:%f')
        self.logContent = EMPTY_UNICODE  # 日志信息

class VtSignalData(VtBaseData):
    """信号数据类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        super(VtSignalData, self).__init__()
        self.time = datetime.now().strftime('%X:%f')
        self.source = EMPTY_STRING  # 来源
        self.symbol = EMPTY_STRING  # 合约信息
        self.direction = EMPTY_STRING   #信号方向
        self.price = EMPTY_FLOAT    # 信号价格
        self.level = EMPTY_INT      # 0 普通信号，1，强信号


########################################################################
class VtContractData(VtBaseData):
    """合约详细信息类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(VtContractData, self).__init__()

        self.symbol = EMPTY_STRING  # 代码
        self.exchange = EMPTY_STRING  # 交易所代码
        self.vtSymbol = EMPTY_STRING  # 合约在vt系统中的唯一代码，通常是 合约代码.交易所代码
        self.name = EMPTY_UNICODE  # 合约中文名

        self.productClass = EMPTY_UNICODE  # 合约类型
        self.size = EMPTY_FLOAT  # 合约大小
        self.priceTick = EMPTY_FLOAT  # 合约最小价格TICK

        self.longMarginRatio = EMPTY_FLOAT  # 多头保证金率
        self.shortMarginRatio = EMPTY_FLOAT # 空头保证金率

        # 期权相关
        self.strikePrice = EMPTY_FLOAT  # 期权行权价
        self.underlyingSymbol = EMPTY_STRING  # 标的物合约代码
        self.optionType = EMPTY_UNICODE  # 期权类型
        self.expiryDate = EMPTY_STRING  # 到期日

        # 数字货币有关
        self.volumeTick = EMPTY_FLOAT  #合约最小交易量
    # ----------------------------------------------------------------------
    @staticmethod
    def createFromGateway(gateway,
                          exchange,
                          symbol,
                          productClass,
                          size,
                          priceTick,
                          name=None,
                          strikePrice=EMPTY_FLOAT,
                          underlyingSymbol=EMPTY_STRING,
                          optionType=EMPTY_UNICODE,
                          expiryDate=EMPTY_STRING
                          ):
        d = VtContractData()
        d.gatewayName = gateway.gatewayName
        d.symbol = symbol
        d.exchange = exchange
        d.vtSymbol = symbol + '.' + exchange
        d.productClass = productClass
        d.size = size
        d.priceTick = priceTick
        if name is None:
            d.name = d.symbol
        d.strikePrice = strikePrice
        d.underlyingSymbol = underlyingSymbol
        d.optionType = optionType
        d.expiryDate = expiryDate
        return d


########################################################################
class VtHistoryData(object):
    """K线时间序列数据"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.vtSymbol = EMPTY_STRING    # vt系统代码
        self.symbol = EMPTY_STRING      # 代码
        self.exchange = EMPTY_STRING    # 交易所

        self.interval = EMPTY_UNICODE   # K线时间周期
        self.queryID = EMPTY_STRING     # 查询号
        self.barList = []               # VtBarData列表


########################################################################
class VtSubscribeReq(object):
    """订阅行情时传入的对象类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.symbol = EMPTY_STRING  # 代码
        self.exchange = EMPTY_STRING  # 交易所

        self.is_bar = False         # True：订阅1分钟bar行情；False:订阅tick行情，

        # 以下为IB相关
        self.productClass = EMPTY_UNICODE  # 合约类型
        self.currency = EMPTY_STRING  # 合约货币
        self.expiry = EMPTY_STRING  # 到期日
        self.strikePrice = EMPTY_FLOAT  # 行权价
        self.optionType = EMPTY_UNICODE  # 期权类型


########################################################################
class VtOrderReq(object):
    """发单时传入的对象类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.symbol = EMPTY_STRING  # 代码
        self.exchange = EMPTY_STRING  # 交易所
        self.vtSymbol = EMPTY_STRING  # VT合约代码
        self.price = EMPTY_FLOAT  # 价格
        self.volume = EMPTY_FLOAT  # 数量

        self.priceType = EMPTY_STRING  # 价格类型
        self.direction = EMPTY_STRING  # 买卖
        self.offset = EMPTY_STRING  # 开平

        # 以下为IB相关
        self.productClass = EMPTY_UNICODE  # 合约类型
        self.currency = EMPTY_STRING  # 合约货币
        self.expiry = EMPTY_STRING  # 到期日
        self.strikePrice = EMPTY_FLOAT  # 行权价
        self.optionType = EMPTY_UNICODE  # 期权类型
        self.lastTradeDateOrContractMonth = EMPTY_STRING  # 合约月,IB专用
        self.multiplier = EMPTY_STRING  # 乘数,IB专用


########################################################################
class VtCancelOrderReq(object):
    """撤单时传入的对象类"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.symbol = EMPTY_STRING  # 代码
        self.exchange = EMPTY_STRING  # 交易所
        self.vtSymbol = EMPTY_STRING  # VT合约代码

        # 以下字段主要和CTP、LTS类接口相关
        self.orderID = EMPTY_STRING  # 报单号
        self.frontID = EMPTY_STRING  # 前置机号
        self.sessionID = EMPTY_STRING  # 会话号


########################################################################
class VtHistoryReq(object):
    """查询历史数据时传入的对象类"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.symbol = EMPTY_STRING              # 代码
        self.exchange = EMPTY_STRING            # 交易所
        self.vtSymbol = EMPTY_STRING            # VT合约代码

        self.interval = EMPTY_UNICODE           # K线周期
        self.start = None                       # 起始时间datetime对象
        self.end = None                         # 结束时间datetime对象


########################################################################
class VtSingleton(type):
    """
    单例，应用方式:静态变量 __metaclass__ = Singleton
    """

    _instances = {}

    #----------------------------------------------------------------------
    def __call__(cls, *args, **kwargs):
        """调用"""
        if cls not in cls._instances:
            cls._instances[cls] = super(VtSingleton, cls).__call__(*args, **kwargs)

        return cls._instances[cls]


########################################################################
class PositionBuffer(object):
    """持仓缓存信息（本地维护的持仓数据）"""

    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.vtSymbol = EMPTY_STRING

        # 多头
        self.longPosition = EMPTY_INT
        self.longToday = EMPTY_INT
        self.longYd = EMPTY_INT

        self.longPrice = EMPTY_FLOAT
        self.longProfit = EMPTY_FLOAT
        self.longFrozen = EMPTY_FLOAT

        # 空头
        self.shortPosition = EMPTY_INT
        self.shortToday = EMPTY_INT
        self.shortYd = EMPTY_INT

        self.shortPrice = EMPTY_FLOAT
        self.shortProfit = EMPTY_FLOAT

        self.shortFrozen = EMPTY_FLOAT

        self.frozen = EMPTY_FLOAT

    # ----------------------------------------------------------------------
    def toStr(self):
        """更新显示信息"""
        str = u'long:{},yd:{},td:{}, short:{},yd:{},td:{}, fz:{};' \
            .format(self.longPosition, self.longYd, self.longToday,
                    self.shortPosition, self.shortYd, self.shortToday, self.frozen)
        return str

    # ----------------------------------------------------------------------
    def updatePositionData(self, pos):
        """更新持仓数据"""
        if pos.direction == DIRECTION_SHORT:
            self.shortPosition = pos.position  # >=0
            self.shortYd = pos.ydPosition  # >=0
            self.shortToday = self.shortPosition - self.shortYd  # >=0

            self.shortPrice = pos.price
            self.shortProfit = pos.positionProfit
            self.shortFrozen = pos.frozen

        else:
            self.longPosition = pos.position  # >=0
            self.longYd = pos.ydPosition  # >=0
            self.longToday = self.longPosition - self.longYd  # >=0

            self.longPrice = pos.price
            self.longProfit = pos.positionProfit
            self.longFrozen = pos.frozen

            self.frozen = self.shortFrozen + self.longFrozen

    # ----------------------------------------------------------------------
    def updateTradeData(self, trade):
        """更新成交数据"""

        if trade.direction == DIRECTION_SHORT:
            # 空头和多头相同
            if trade.offset == OFFSET_OPEN:  # 开仓
                self.shortPosition += trade.volume
                self.shortToday += trade.volume  # 增加的是今仓

            elif trade.offset == OFFSET_CLOSETODAY:  # 平今
                self.longPosition -= trade.volume
                self.longToday -= trade.volume  # 减少今仓

            elif trade.offset == OFFSET_CLOSEYESTERDAY:  # 平昨
                self.longPosition -= trade.volume
                self.longYd -= trade.volume  # 减少昨仓

            else:  # 平仓
                self.longPosition -= trade.volume
                self.longToday -= trade.volume  # 优先减今仓
                if self.longToday < 0:
                    self.longYd += self.longToday
                    self.longToday = 0

            if self.longPosition <= 0:
                self.longPosition = 0
            if self.longToday <= 0:
                self.longToday = 0
            if self.longYd <= 0:
                self.longYd = 0
        else:
            # 多方开仓，则对应多头的持仓和今仓增加
            if trade.offset == OFFSET_OPEN:
                self.longPosition += trade.volume
                self.longToday += trade.volume
            # 多方平今，对应空头的持仓和今仓减少
            elif trade.offset == OFFSET_CLOSETODAY:
                self.shortPosition -= trade.volume
                self.shortToday -= trade.volume

            elif trade.offset == OFFSET_CLOSEYESTERDAY:
                self.shortPosition -= trade.volume
                self.shortYd -= trade.volume
            else:
                self.shortPosition -= trade.volume
                self.shortToday -= trade.volume
                if self.shortToday <= 0:
                    self.shortYd += self.shortToday
                    self.shortToday = 0

            if self.shortPosition <= 0:
                self.shortPosition = 0
            if self.shortToday <= 0:
                self.shortToday = 0
            if self.shortYd <= 0:
                self.shortYd = 0
            # 多方平昨，对应空头的持仓和昨仓减少
