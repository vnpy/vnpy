from typing import List, Dict
from collections import defaultdict

from vnpy.event import EventEngine, Event
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import EVENT_TICK, EVENT_POSITION
from vnpy.trader.utility import load_json, save_json

from .base import LegData, SpreadData


APP_NAME = "SpreadTrading"


class SpreadEngine(BaseEngine):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """Constructor"""
        super().__init__(main_engine, event_engine, APP_NAME)

    def write_log(self, msg: str):
        """"""
        pass


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

        self.load_setting()
        self.register_event()

    def load_setting(self):
        """"""
        setting = load_json(self.setting_filename)

        for spread_setting in setting:
            self.add_spread(
                spread_setting["name"],
                spread_setting["leg_settings"],
                spread_setting["active_symbol"],
                save=False
            )

    def save_setting(self):
        """"""
        setting = []

        for spread in self.spreads.values():
            leg_settings = []
            for leg in spread.legs:
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

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_POSITION, self.process_position_event)

    def process_tick_event(self, event: Event):
        """"""
        tick = event.data

        leg = self.legs.get(tick.vt_symbol, None)
        if not leg:
            return
        leg.update_tick(tick)

        for spread in self.symbol_spread_map[tick.vt_symbol]:
            spread.calculate_price()

    def process_position_event(self, event: Event):
        """"""
        position = event.data

        leg = self.legs.get(position.vt_symbol, None)
        if not leg:
            return
        leg.update_position(position)

        for spread in self.symbol_spread_map[position.vt_symbol]:
            spread.calculate_pos()

    def add_spread(
        self,
        name: str,
        leg_settings: List[Dict],
        active_symbol: str,
        save: bool = True
    ):
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

        for leg in spread.legs:
            self.symbol_spread_map[leg.vt_symbol].append(spread)

        if save:
            self.save_setting()

        self.write_log("价差创建成功：{}".format(name))

    def remove_spread(self, name: str):
        """"""
        if name not in self.spreads:
            return

        spread = self.spreads.pop(name)

        for leg in spread.legs:
            self.symbol_spread_map[leg.vt_symbol].remove(spread)

        self.write_log("价差删除成功：{}".format(name))
