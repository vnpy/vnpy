from typing import Dict, Set, Any
from datetime import datetime
from collections import defaultdict
from tzlocal import get_localzone
from dataclasses import dataclass

from vnpy.event import Event, EventEngine
from vnpy.trader.utility import save_json, load_json
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import (
    SubscribeRequest, ContractData, TickData, LogData,
)
from vnpy.trader.event import EVENT_TICK, EVENT_CONTRACT


LOCAL_TZ = get_localzone()
APP_NAME = "MarketRadar"

EVENT_RADAR_ADD = "eRadarAdd"
EVENT_RADAR_UPDATE = "eRadarUpdate"
EVENT_RADAR_REMOVE = "eRadarRemove"


@dataclass
class RadarRule:
    name: str
    formula: str
    params: Dict[str, str]


class RadarEngine(BaseEngine):
    """"""

    setting_filename = "market_radar_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.rules: Dict[str, RadarRule] = {}
        self.symbol_rule_map: Dict[str, Set[RadarRule]] = defaultdict(set)

        self.load_setting()
        self.register_event()

    def register_event(self):
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)

    def process_tick_event(self, event: Event) -> None:
        """"""
        tick: TickData = event.data

        if tick.vt_symbol not in self.symbol_rule_map:
            return

        for rule in self.symbol_rule_map[tick.vt_symbol]:
            self.calculate_rule(rule)

    def process_contract_event(self, event: Event) -> None:
        """"""
        pass

    def add_rule(self, name: str, formula: str, params: Dict[str, str]) -> bool:
        """"""
        if name in self.rules:
            return False

        rule = RadarRule(name, formula, params)
        self.rules[name] = rule

        for vt_symbol in params.values():
            self.symbol_rule_map[vt_symbol].add(rule)

        return True

    def load_setting(self) -> None:
        """"""
        setting = load_json(self.setting_filename)

        for d in setting:
            self.add_rule(d["name"], d["formula"], d["params"])

    def save_setting(self) -> None:
        """"""
        setting = []

        for rule in self.rules.values():
            d = {
                "name": rule.name,
                "formula": rule.formula,
                "params": rule.params
            }
            setting.append(d)

        save_json(self.setting_filename, setting)

    def calculate_rule(self, rule: RadarRule) -> None:
        """"""
        data = {}

        for name, vt_symbol in rule.params:
            tick = self.main_engine.get_tick(vt_symbol)

            if not tick:
                return
            else:
                data[name] = tick.last_price

        result = parse_formula(rule.formula, data)
        if result is None:
            return

        dt = datetime.now()
        dt = LOCAL_TZ.localize(dt)

        radar_data = {
            "name": rule.name,
            "result": result,
            "datetime": dt
        }
        self.put_event(EVENT_RADAR_UPDATE, radar_data)

    def put_event(self, type: str, data: Any) -> None:
        """"""
        event = Event(type, data)
        self.event_engine.put(event)


def parse_formula(formula: str, data: Dict[str, float]) -> float:
    """"""
    locals().update(data)
    result = eval(formula)
    return result
