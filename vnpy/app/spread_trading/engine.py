from typing import List, Dict
from collections import defaultdict
from copy import copy

from vnpy.event import EventEngine, Event
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import (
    EVENT_TICK, EVENT_POSITION, EVENT_CONTRACT,
    EVENT_ORDER, EVENT_TRADE, EVENT_TIMER
)
from vnpy.trader.utility import load_json, save_json
from vnpy.trader.object import (
    TickData, ContractData, LogData,
    SubscribeRequest, OrderRequest, CancelRequest
)
from vnpy.trader.constant import Direction

from .base import (
    LegData, SpreadData,
    EVENT_SPREAD_DATA, EVENT_SPREAD_ALGO,
    EVENT_SPREAD_LOG, EVENT_SPREAD_STRATEGY
)
from .template import SpreadAlgoTemplate
from .algo import SpreadTakerAlgo


APP_NAME = "SpreadTrading"


class SpreadEngine(BaseEngine):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """Constructor"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.active = False

        self.data_engine: SpreadDataEngine = SpreadDataEngine(self)
        self.algo_engine: SpreadAlgoEngine = SpreadAlgoEngine(self)

    def start(self):
        """"""
        if self.active:
            return
        self.active = True

        self.data_engine.start()
        self.algo_engine.start()

    def write_log(self, msg: str):
        """"""
        log = LogData(
            msg=msg,
            gateway_name=APP_NAME
        )
        event = Event(EVENT_SPREAD_LOG, log)
        self.event_engine.put(event)


class SpreadDataEngine:
    """"""
    setting_filename = "spread_trading_setting.json"

    def __init__(self, spread_engine: SpreadEngine):
        """"""
        self.spread_engine: SpreadEngine = spread_engine
        self.main_engine: MainEngine = spread_engine.main_engine
        self.event_engine: EventEngine = spread_engine.event_engine

        self.write_log = spread_engine.write_log

        self.legs: Dict[str, LegData] = {}          # vt_symbol: leg
        self.spreads: Dict[str, SpreadData] = {}    # name: spread
        self.symbol_spread_map: Dict[str, List[SpreadData]] = defaultdict(list)

    def start(self):
        """"""
        self.load_setting()
        self.register_event()
        self.test()

        self.write_log("价差数据引擎启动成功")

    def test(self):
        """"""
        name = "test"
        leg_settings = [
            {
                "vt_symbol": "XBTUSD.BITMEX",
                "price_multiplier": 1,
                "trading_multiplier": 1
            },
            {
                "vt_symbol": "XBTZ19.BITMEX",
                "price_multiplier": -1,
                "trading_multiplier": -1
            }
        ]
        active_symbol = "XBTUSD.BITMEX"
        self.add_spread(name, leg_settings, active_symbol, True)

    def load_setting(self) -> None:
        """"""
        setting = load_json(self.setting_filename)

        for spread_setting in setting:
            self.add_spread(
                spread_setting["name"],
                spread_setting["leg_settings"],
                spread_setting["active_symbol"],
                save=False
            )

    def save_setting(self) -> None:
        """"""
        setting = []

        for spread in self.spreads.values():
            leg_settings = []
            for leg in spread.legs.values():
                leg_setting = {
                    "vt_symbol": leg.vt_symbol,
                    "price_multiplier": leg.price_multiplier,
                    "trading_multiplier": leg.trading_multiplier
                }
                leg_settings.append(leg_setting)

            spread_setting = {
                "name": spread.name,
                "leg_settings": leg_settings,
                "active_symbol": spread.active_leg.vt_symbol
            }
            setting.append(spread_setting)

        save_json(self.setting_filename, setting)

    def register_event(self) -> None:
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_POSITION, self.process_position_event)
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)

    def process_tick_event(self, event: Event) -> None:
        """"""
        tick = event.data

        leg = self.legs.get(tick.vt_symbol, None)
        if not leg:
            return
        leg.update_tick(tick)

        for spread in self.symbol_spread_map[tick.vt_symbol]:
            spread.calculate_price()

        self.put_data_event(spread)

    def process_position_event(self, event: Event) -> None:
        """"""
        position = event.data

        leg = self.legs.get(position.vt_symbol, None)
        if not leg:
            return
        leg.update_position(position)

        for spread in self.symbol_spread_map[position.vt_symbol]:
            spread.calculate_pos()

        self.put_data_event(spread)

    def process_contract_event(self, event: Event) -> None:
        """"""
        contract = event.data

        if contract.vt_symbol in self.legs:
            req = SubscribeRequest(
                contract.symbol, contract.exchange
            )
            self.main_engine.subscribe(req, contract.gateway_name)

    def put_data_event(self, spread: SpreadData) -> None:
        """"""
        event = Event(EVENT_SPREAD_DATA, spread)
        self.event_engine.put(event)

    def add_spread(
        self,
        name: str,
        leg_settings: List[Dict],
        active_symbol: str,
        save: bool = True
    ) -> None:
        """"""
        if name in self.spreads:
            self.write_log("价差创建失败，名称重复：{}".format(name))
            return

        legs: List[LegData] = []
        for leg_setting in leg_settings:
            vt_symbol = leg_setting["vt_symbol"]

            leg = self.legs.get(vt_symbol, None)
            if not leg:
                leg = LegData(
                    vt_symbol,
                    leg_setting["price_multiplier"],
                    leg_setting["trading_multiplier"]
                )
                self.legs[vt_symbol] = leg

            legs.append(leg)

        spread = SpreadData(name, legs, active_symbol)
        self.spreads[name] = spread

        for leg in spread.legs.values():
            self.symbol_spread_map[leg.vt_symbol].append(spread)

        if save:
            self.save_setting()

        self.write_log("价差创建成功：{}".format(name))
        self.put_data_event(spread)

    def remove_spread(self, name: str) -> None:
        """"""
        if name not in self.spreads:
            return

        spread = self.spreads.pop(name)

        for leg in spread.legs:
            self.symbol_spread_map[leg.vt_symbol].remove(spread)

        self.write_log("价差删除成功：{}".format(name))


class SpreadAlgoEngine:
    """"""
    algo_class = SpreadTakerAlgo

    def __init__(self, spread_engine: SpreadEngine):
        """"""
        self.spread_engine: SpreadEngine = spread_engine
        self.main_engine: MainEngine = spread_engine.main_engine
        self.event_engine: EventEngine = spread_engine.event_engine

        self.write_log = spread_engine.write_log

        self.spreads: Dict[str: SpreadData] = {}
        self.algos: Dict[str: SpreadAlgoTemplate] = {}

        self.order_algo_map: dict[str: SpreadAlgoTemplate] = {}
        self.symbol_algo_map: dict[str: SpreadAlgoTemplate] = defaultdict(list)

        self.algo_count: int = 0

    def start(self):
        """"""
        self.register_event()

        self.write_log("价差算法引擎启动成功")

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def process_spread_event(self, event: Event):
        """"""
        spread: SpreadData = event.data
        self.spreads[spread.name] = spread

    def process_tick_event(self, event: Event):
        """"""
        tick = event.data
        algos = self.symbol_algo_map[tick.vt_symbol]
        if not algos:
            return

        buf = copy(algos)
        for algo in buf:
            if not algo.is_active():
                algos.remove(algo)
            else:
                algo.update_tick(tick)

    def process_order_event(self, event: Event):
        """"""
        order = event.data
        algo = self.order_algo_map.get(order.vt_orderid, None)
        if algo and algo.is_active():
            algo.update_order(order)

    def process_trade_event(self, event: Event):
        """"""
        trade = event.data
        algo = self.order_algo_map.get(trade.vt_orderid, None)
        if algo and algo.is_active():
            algo.update_trade(trade)

    def process_timer_event(self, event: Event):
        """"""
        buf = self.algos.values()

        for algo in buf:
            if not algo.is_active():
                self.algos.pop(algo.algoid)
            else:
                algo.update_timer()

    def start_algo(
        self,
        spread_name: str,
        direction: Direction,
        price: float,
        volume: float,
        payup: int,
        interval: int
    ) -> str:
        # Find spread object
        spread = self.spreads.get(spread_name, None)
        if not spread:
            self.write_log("创建价差算法失败，找不到价差：{}".format(spread_name))
            return ""

        # Generate algoid str
        self.algo_count += 1
        algo_count_str = str(self.algo_count).rjust(6, "0")
        algoid = f"{self.algo_class.algo_name}_{algo_count_str}"

        # Create algo object
        algo = self.algo_class(
            self,
            algoid,
            spread,
            direction,
            price,
            volume,
            payup,
            interval
        )
        self.algos[algoid] = algo

        # Generate map between vt_symbol and algo
        for leg in spread.legs.values():
            self.symbol_algo_map[leg.vt_symbol].append(algo)

        # Put event to update GUI
        self.put_algo_event(algo)

        return algoid

    def stop_algo(
        self,
        algoid: str
    ):
        """"""
        algo = self.algos.get(algoid, None)
        if not algo:
            self.write_log("停止价差算法失败，找不到算法：{}".format(algoid))
            return

        algo.stop()

    def put_algo_event(self, algo: SpreadAlgoTemplate) -> None:
        """"""
        event = Event(EVENT_SPREAD_ALGO, algo)
        self.event_engine.put(event)

    def write_algo_log(self, algo: SpreadAlgoTemplate, msg: str) -> None:
        """"""
        msg = f"{algo.algoid}：{msg}"
        self.write_log(msg)

    def send_order(
        self,
        algo: SpreadAlgoTemplate,
        vt_symbol: str,
        price: float,
        volume: float,
        direction: Direction,
    ) -> List[str]:
        """"""
        pass

    def cancel_order(self, algo: SpreadAlgoTemplate, vt_orderid: str) -> None:
        """"""
        pass

    def get_tick(self, vt_symbol: str) -> TickData:
        """"""
        return self.main_engine.get_tick(vt_symbol)

    def get_contract(self, vt_symbol: str) -> ContractData:
        """"""
        return self.main_engine.get_contract(vt_symbol)
