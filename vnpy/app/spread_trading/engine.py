# encoding: UTF-8

from vnpy.event import Event, EventEngine
from vnpy.trader.utility import load_json, save_json

from vnpy.trader.event import (
    EVENT_TICK,
    EVENT_TRADE,
    EVENT_POSITION,
    EVENT_TIMER,
    EVENT_ORDER,
)
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import (
    SubscribeRequest,
    OrderRequest,
    CancelRequest,
    LogData,
)
from vnpy.trader.constant import Direction, Offset, OrderType

from .base import (
    APP_NAME,
    EVENT_SPREADTRADING_TICK,
    EVENT_SPREADTRADING_POS,
    EVENT_SPREADTRADING_LOG,
    EVENT_SPREADTRADING_ALGO,
    EVENT_SPREADTRADING_ALGOLOG,
)

from .spread import StSpread

from .template import SpreadTradingTemplate


########################################################################
class SpreadEngine(BaseEngine):
    """"""

    # ----------------------------------------------------------------------
    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """Constructor"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.algos = {}
        self.symbol_algo_map = {}
        self.orderid_algo_map = {}

        self.algo_templates = {}
        self.algo_settings = {}

        self.dataEngine = StDataEngine(main_engine, event_engine)
        self.algoEngine = StAlgoEngine(
            self.dataEngine, main_engine, event_engine
        )

    # ----------------------------------------------------------------------
    def init(self):
        """"""
        self.dataEngine.loadSetting()
        self.algoEngine.loadSetting()

    # ----------------------------------------------------------------------
    def stop(self):
        """"""
        self.dataEngine.saveSetting()

        self.algoEngine.stopAll()
        self.algoEngine.saveSetting()

    # ----------------------------------------------------------------------
    def save_setting(self):
        """"""
        self.dataEngine.save_spread()
        self.algoEngine.save_setting()

    # ----------------------------------------------------------------------
    def add_spread(self, setting):
        """"""
        self.dataEngine.init_spread(setting)
        self.dataEngine.save_spread()

    # ----------------------------------------------------------------------
    def delete_spread(self, setting):
        """"""
        self.dataEngine.delete_spread(setting)
        self.dataEngine.save_spread()

    # ----------------------------------------------------------------------
    def add_algo(self, setting):
        """"""
        self.algoEngine.init_algoSetting(setting)
        self.algoEngine.save_setting()

    # ----------------------------------------------------------------------
    def get_all_strategy_names(self):
        """"""
        return list(self.algoEngine.st_strategies.keys())


########################################################################
class StDataEngine(object):
    """"""

    setting_filename = r"spreadtrading\st_setting.json"

    # ----------------------------------------------------------------------
    def __init__(self, mainEngine, eventEngine):
        """Constructor"""
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine

        #
        self.legDict = {}  # vtSymbol:StLeg
        self.spreadDict = {}  # name:StSpread
        self.vtSymbolSpreadDict = {}  # vtSymbol:StSpread

        #
        self.spread_settings = []

        self.registerEvent()

    # ----------------------------------------------------------------------
    def loadSetting(self):
        """"""
        d = load_json(self.setting_filename)
        for setting in d:
            self.init_spread(setting)

    # ----------------------------------------------------------------------
    def init_spread(self, setting):
        new_spread = StSpread()
        result, msg = new_spread.initSpread(setting)
        if result:
            r, msg = self.check_spread(new_spread)
            if r:
                self.start_spread(new_spread)
                self.spread_settings.append(setting)
            else:
                content = "价差配置加载出错，原因：" + msg
                self.write_Log(content)
        else:
            content = "价差配置加载出错，原因：" + msg
            self.write_Log(content)

    # ----------------------------------------------------------------------
    def save_spread(self):
        """"""
        save_json(self.setting_filename, self.spread_settings)

    # ----------------------------------------------------------------------
    def delete_spread(self, setting):
        """"""
        ns = []
        for s in self.spread_settings:
            if s["name"] != setting["name"]:
                ns.append(s)
        self.spread_settings = ns

    # ----------------------------------------------------------------------
    def check_spread(self, spread):
        result = False
        msg = ""
        #
        if spread.name in self.spreadDict:
            msg = "%s价差存在重名" % spread.name["name"]
            return result, msg

        result = True
        return result, msg

    # ----------------------------------------------------------------------
    def start_spread(self, spread):
        ##
        self.spreadDict[spread.name] = spread
        self.legDict[spread.activeLeg.vt_symbol] = spread.activeLeg
        self.vtSymbolSpreadDict[spread.activeLeg.vt_symbol] = spread
        self.subscribeMarketData(spread.activeLeg.vt_symbol)

        ##
        for d in spread.passiveLegs:
            self.legDict[d.vt_symbol] = d
            self.vtSymbolSpreadDict[d.vt_symbol] = spread

            self.subscribeMarketData(d.vt_symbol)

        ##
        spread.start_spread()

        ##
        self.putSpreadTickEvent(spread)
        self.putSpreadPosEvent(spread)

    # ----------------------------------------------------------------------
    def process_tick_event(self, event):
        """"""
        tick = event.data
        if tick.vt_symbol not in self.legDict:
            return

        #
        leg = self.legDict[tick.vt_symbol]
        leg.bidPrice = tick.bid_price_1
        leg.askPrice = tick.ask_price_1
        leg.bidVolume = tick.bid_volume_1
        leg.askVolume = tick.ask_volume_1

        #
        spread = self.vtSymbolSpreadDict[tick.vt_symbol]
        spread.calculatePrice()

        #
        self.putSpreadTickEvent(spread)

    # ----------------------------------------------------------------------
    def putSpreadTickEvent(self, spread):
        """"""
        event = Event(EVENT_SPREADTRADING_TICK)
        event.data = spread
        self.eventEngine.put(event)

    # ----------------------------------------------------------------------
    def process_trade_event(self, event):
        """"""
        trade = event.data
        if trade.vt_symbol not in self.legDict:
            return

        #
        leg = self.legDict[trade.vt_symbol]
        direction = trade.direction
        offset = trade.offset

        if direction == Direction.LONG:
            if offset == Offset.OPEN:
                leg.longPos += trade.volume
            else:
                leg.shortPos -= trade.volume
        else:
            if offset == Offset.OPEN:
                leg.shortPos += trade.volume
            else:
                leg.longPos -= trade.volume
        leg.netPos = leg.longPos - leg.shortPos

        #
        spread = self.vtSymbolSpreadDict[trade.vt_symbol]
        spread.calculatePos()

        event = Event(EVENT_SPREADTRADING_POS)
        event.data = spread
        self.eventEngine.put(event)

    # ----------------------------------------------------------------------
    def process_position_event(self, event):
        """"""
        pos = event.data
        if pos.vt_symbol not in self.legDict:
            return

        #
        leg = self.legDict[pos.vt_symbol]
        direction = pos.direction

        if direction == Direction.LONG:
            leg.longPos = pos.volume
        else:
            leg.shortPos = pos.volume
        leg.netPos = leg.longPos - leg.shortPos

        #
        spread = self.vtSymbolSpreadDict[pos.vt_symbol]
        spread.calculatePos()

        #
        self.putSpreadPosEvent(spread)

    # ----------------------------------------------------------------------
    def putSpreadPosEvent(self, spread):
        """"""
        event1 = Event(EVENT_SPREADTRADING_POS + spread.name)
        event1.data = spread
        self.eventEngine.put(event1)

        event2 = Event(EVENT_SPREADTRADING_POS)
        event2.data = spread
        self.eventEngine.put(event2)

    # ----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.eventEngine.register(EVENT_TICK, self.process_tick_event)
        self.eventEngine.register(EVENT_TRADE, self.process_trade_event)
        self.eventEngine.register(EVENT_POSITION, self.process_position_event)

    # ----------------------------------------------------------------------
    def subscribeMarketData(self, vtSymbol):
        """"""
        contract = self.mainEngine.get_contract(vtSymbol)
        if not contract:
            self.write_Log("订阅行情失败，找不到该合约%s" % vtSymbol)
            return

        req = SubscribeRequest(
            symbol=contract.symbol, exchange=contract.exchange
        )

        self.mainEngine.subscribe(req, contract.gateway_name)

    # ----------------------------------------------------------------------
    def write_Log(self, msg: str, strategy: SpreadTradingTemplate = None):
        """"""
        if strategy:
            msg = f"{strategy.strategy_name}: {msg}"

        log = LogData(msg=msg, gateway_name="SpreadTrading")
        log.logContent = msg

        event = Event(EVENT_SPREADTRADING_LOG)
        event.data = log
        self.eventEngine.put(event)

    # ----------------------------------------------------------------------
    def getAllSpreads(self):
        """"""
        return list(self.spreadDict.values())

    # ----------------------------------------------------------------------
    def get_spread(self, name):
        return self.spreadDict.get(name, None)


########################################################################
class StAlgoEngine(object):
    """"""

    algoFileName = r"spreadtrading\algo_setting.json"

    # ----------------------------------------------------------------------
    def __init__(self, dataEngine, mainEngine, eventEngine):
        """Constructor"""
        self.dataEngine = dataEngine
        self.mainEngine = mainEngine
        self.eventEngine = eventEngine

        self.algoDict = {}  # spreadName:algo
        self.vtSymbolAlgoDict = {}  # vtSymbol:algo
        self.st_strategies = {}
        self.all_algos = []
        self.all_settings = []

        self.registerEvent()
        self.load_strategies()

    # ----------------------------------------------------------------------
    def registerEvent(self):
        """"""
        self.eventEngine.register(
            EVENT_SPREADTRADING_TICK, self.processSpreadTickEvent
        )
        self.eventEngine.register(
            EVENT_SPREADTRADING_POS, self.processSpreadPosEvent
        )
        self.eventEngine.register(EVENT_TRADE, self.processTradeEvent)
        self.eventEngine.register(EVENT_ORDER, self.processOrderEvent)
        self.eventEngine.register(EVENT_TIMER, self.processTimerEvent)

    # ----------------------------------------------------------------------
    def processSpreadTickEvent(self, event):
        """"""
        spread = event.data

        algos = self.algoDict.get(spread.name, None)
        if algos:
            for algo in list(algos.values()):
                algo.updateSpreadTick(spread)

    # ----------------------------------------------------------------------
    def processSpreadPosEvent(self, event):
        """"""
        spread = event.data

        algos = self.algoDict.get(spread.name, None)
        if algos:
            for algo in list(algos.values()):
                algo.updateSpreadPos(spread)

    # ----------------------------------------------------------------------
    def processTradeEvent(self, event):
        """"""
        trade = event.data

        algos = self.vtSymbolAlgoDict.get(trade.vt_symbol, None)
        if algos:
            for algo in algos:
                algo.updateTrade(trade)

    # ----------------------------------------------------------------------
    def processOrderEvent(self, event):
        """"""
        order = event.data
        algos = self.vtSymbolAlgoDict.get(order.vt_symbol, None)
        if algos:
            for algo in algos:
                algo.updateOrder(order)

    # ----------------------------------------------------------------------
    def processTimerEvent(self, event):
        """"""
        for algo in self.all_algos:
            algo.updateTimer()

    # ----------------------------------------------------------------------
    def sendOrder(self, vtSymbol, direction, offset, price, volume, payup=0):
        """"""
        contract = self.mainEngine.get_contract(vtSymbol)
        if not contract:
            return ""

        if direction == Direction.LONG:
            price = price + payup * contract.pricetick
        else:
            price = price - payup * contract.pricetick

        req = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            direction=direction,
            type=OrderType.LIMIT,
            volume=volume,
            price=price,
            offset=offset,
        )

        vtOrderID = self.mainEngine.send_order(req, contract.gateway_name)

        # convert to list
        vtOrderList = [vtOrderID]

        return vtOrderList

    # ----------------------------------------------------------------------
    def cancelOrder(self, vtOrderID):
        """"""
        order = self.mainEngine.get_order(vtOrderID)
        if not order:
            return

        req = CancelRequest(
            orderid=order.orderID, symbol=order.symbol, exchange=order.exchange
        )

        self.mainEngine.cancel_order(req, order.gateway_name)

    # ----------------------------------------------------------------------
    def buy(self, vtSymbol, price, volume, payup=0):
        """Long-Open"""
        order_return = self.sendOrder(
            vtSymbol, Direction.LONG, Offset.OPEN, price, volume, payup
        )
        return order_return

    # ----------------------------------------------------------------------
    def sell(self, vtSymbol, price, volume, payup=0):
        """Short-Close"""
        order_return = self.sendOrder(
            vtSymbol, Direction.SHORT, Offset.CLOSE, price, volume, payup
        )
        return order_return

    # ----------------------------------------------------------------------
    def short(self, vtSymbol, price, volume, payup=0):
        """Short-Open"""
        order_return = self.sendOrder(
            vtSymbol, Direction.SHORT, Offset.OPEN, price, volume, payup
        )
        return order_return

    # ----------------------------------------------------------------------
    def cover(self, vtSymbol, price, volume, payup=0):
        """Long-Close"""
        order_return = self.sendOrder(
            vtSymbol, Direction.LONG, Offset.CLOSE, price, volume, payup
        )
        return order_return

    # ----------------------------------------------------------------------
    def putAlgoEvent(self, algo):
        """"""
        event = Event(EVENT_SPREADTRADING_ALGO + algo.name)
        self.eventEngine.put(event)

    # ----------------------------------------------------------------------
    def write_Log(self, msg: str, strategy: SpreadTradingTemplate = None):
        """"""
        if strategy:
            msg = f"{strategy.strategy_name}: {msg}"

        log = LogData(msg=msg, gateway_name="SpreadTrading")
        log.logContent = msg

        event = Event(EVENT_SPREADTRADING_ALGOLOG)
        event.data = log
        self.eventEngine.put(event)

    # ----------------------------------------------------------------------
    def save_setting(self):
        """"""
        settings = []
        for algo in self.all_algos:
            s = algo.getAlgoParams()
            settings.append(s)
        save_json(self.algoFileName, settings)

    # ----------------------------------------------------------------------
    def loadSetting(self):
        """"""
        d = load_json(self.algoFileName)
        for setting in d:
            self.init_algoSetting(setting)

    # ----------------------------------------------------------------------
    def init_algoSetting(self, setting):
        spread = self.dataEngine.get_spread(setting["spread_name"])
        if not spread:
            return

        strategy = self.st_strategies[setting["algo_name"]]
        algo = strategy(self, spread)

        if spread.name in self.algoDict:
            self.algoDict[spread.name][setting["algo_name"]] = algo
        else:
            self.algoDict[spread.name] = {setting["algo_name"]: algo}
        self.all_algos.append(algo)

        #
        for leg in spread.allLegs:
            if leg.vt_symbol in self.vtSymbolAlgoDict.keys():
                self.vtSymbolAlgoDict[leg.vt_symbol].append(algo)
            else:
                self.vtSymbolAlgoDict[leg.vt_symbol] = [algo]

        #
        algo.setAlgoParams(setting)

        #
        self.all_settings.append(setting)

    # ----------------------------------------------------------------------
    def stopAll(self):
        """"""
        for algo in list(self.all_algos):
            algo.stop()

    # ----------------------------------------------------------------------
    def startAlgo(self, spreadName, algoName):
        """"""
        algo = self.algoDict[spreadName][algoName]
        algoActive = algo.start()
        return algoActive

    # ----------------------------------------------------------------------
    def stopAlgo(self, spreadName, algoName):
        """"""
        algo = self.algoDict[spreadName][algoName]
        algoActive = algo.stop()
        return algoActive

    # ----------------------------------------------------------------------
    def getAllAlgoParams(self):
        """"""
        return [algo.getAlgoParams() for algo in self.all_algos]

    # ----------------------------------------------------------------------
    def setAlgoBuyPrice(self, spreadName, algoName, buyPrice):
        """"""
        algo = self.algoDict[spreadName][algoName]
        algo.setBuyPrice(buyPrice)

    # ----------------------------------------------------------------------
    def setAlgoSellPrice(self, spreadName, algoName, sellPrice):
        """"""
        algo = self.algoDict[spreadName][algoName]
        algo.setSellPrice(sellPrice)

    # ----------------------------------------------------------------------
    def setAlgoShortPrice(self, spreadName, algoName, shortPrice):
        """"""
        algo = self.algoDict[spreadName][algoName]
        algo.setShortPrice(shortPrice)

    # ----------------------------------------------------------------------
    def setAlgoCoverPrice(self, spreadName, algoName, coverPrice):
        """"""
        algo = self.algoDict[spreadName][algoName]
        algo.setCoverPrice(coverPrice)

    # ----------------------------------------------------------------------
    def setAlgoMode(self, spreadName, algoName, mode):
        """"""
        algo = self.algoDict[spreadName][algoName]
        algo.setMode(mode)

    # ----------------------------------------------------------------------
    def setAlgoMaxOrderSize(self, spreadName, algoName, maxOrderSize):
        """"""
        algo = self.algoDict[spreadName][algoName]
        algo.setMaxOrderSize(maxOrderSize)

    # ----------------------------------------------------------------------
    def setAlgoMaxPosSize(self, spreadName, algoName, maxPosSize):
        """"""
        algo = self.algoDict[spreadName][algoName]
        algo.setMaxPosSize(maxPosSize)

    # ----------------------------------------------------------------------
    def load_strategies(self):
        from .strategies.Sniper import SniperAlgo

        self.add_strategies(SniperAlgo)

    # ----------------------------------------------------------------------
    def add_strategies(self, template: SpreadTradingTemplate):
        """"""
        self.st_strategies[template.__name__] = template
