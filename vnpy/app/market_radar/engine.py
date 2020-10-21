import traceback
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

EVENT_RADAR_RULE = "eRadarRule"
EVENT_RADAR_UPDATE = "eRadarUpdate"
EVENT_RADAR_LOG = "eRaderLog"


class RadarRule:
    """"""

    def __init__(self, name: str, formula: str, params: Dict[str, str]):
        """"""
        self.name: str = name
        self.formula: str = formula
        self.params: Dict[str, str] = params


class RadarEngine(BaseEngine):
    """"""

    setting_filename = "market_radar_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.rules: Dict[str, RadarRule] = {}
        self.symbol_rule_map: Dict[str, Set[RadarRule]] = defaultdict(set)
        self.inited = False

        self.register_event()

    def init(self):
        """"""
        if not self.inited:
            self.inited = True
            self.load_setting()

            self.write_log("初始化成功")

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
        contract = event.data
        vt_symbol = contract.vt_symbol

        if vt_symbol in self.symbol_rule_map:
            self.subscribe(vt_symbol)

    def subscribe(self, vt_symbol: str) -> None:
        """"""
        contract = self.main_engine.get_contract(vt_symbol)
        if contract:
            req = SubscribeRequest(contract.symbol, contract.exchange)
            self.main_engine.subscribe(req, contract.gateway_name)

    def add_rule(self, name: str, formula: str, params: Dict[str, str]) -> bool:
        """"""
        if name in self.rules:
            self.write_log(f"添加失败，已存在同名{name}")
            return False

        if not self.check_rule(formula, params):
            self.write_log(f"添加失败，公式无法运算{formula}")
            return False

        rule = RadarRule(name, formula, params)
        self.rules[name] = rule

        for vt_symbol in params.values():
            if vt_symbol not in self.symbol_rule_map:
                self.subscribe(vt_symbol)

            self.symbol_rule_map[vt_symbol].add(rule)

        rule_data = {
            "name": name,
            "formula": formula,
            "params": params
        }
        self.put_event(EVENT_RADAR_RULE, rule_data)

        self.calculate_rule(rule)

        self.write_log(f"添加成功{name}")
        return True

    def edit_rule(self, name: str, formula: str, params: Dict[str, str]) -> bool:
        """"""
        # Check valid
        if name not in self.rules:
            self.write_log(f"修改失败，找不到该名称{name}")
            return False

        if not self.check_rule(formula, params):
            self.write_log(f"修改失败，公式无法运算{formula}")
            return False

        # Remove old symbol map
        rule: RadarRule = self.rules[name]
        for vt_symbol in rule.params.values():
            self.symbol_rule_map[vt_symbol].remove(rule)

        # Add new symbol map
        rule.formula = formula
        rule.params = params

        for vt_symbol in params.values():
            if vt_symbol not in self.symbol_rule_map:
                self.subscribe(vt_symbol)

            self.symbol_rule_map[vt_symbol].add(rule)

        # Push event
        rule_data = {
            "name": name,
            "formula": formula,
            "params": params
        }
        self.put_event(EVENT_RADAR_RULE, rule_data)

        self.calculate_rule(rule)

        self.write_log(f"修改成功{name}")
        return True

    def remove_rule(self, name: str) -> bool:
        """"""
        if name not in self.rules:
            return False

        rule = self.rules.pop(name)
        for vt_symbol in rule.params.values():
            self.symbol_rule_map[vt_symbol].remove(rule)

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

        for name, vt_symbol in rule.params.items():
            tick = self.main_engine.get_tick(vt_symbol)

            if not tick:
                return
            else:
                data[name] = tick.last_price

        value = parse_formula(rule.formula, data)
        if value is None:
            return

        dt = datetime.now()
        dt = LOCAL_TZ.localize(dt)

        radar_data = {
            "name": rule.name,
            "value": value,
            "time": dt
        }
        self.put_event(EVENT_RADAR_UPDATE, radar_data)

    def check_rule(self, formula: str, params: Dict[str, str]) -> bool:
        """"""
        data = {}

        for name in params.keys():
            data[name] = 1

        try:
            parse_formula(formula, data)
        except Exception:
            msg = f"价差公式校验出错，细节：\n{traceback.format_exec()}"
            self.write_log(msg)

            return False

        return True

    def put_event(self, type: str, data: Any) -> None:
        """"""
        event = Event(type, data)
        self.event_engine.put(event)

    def write_log(self, msg: str) -> None:
        """"""
        log = LogData(APP_NAME, msg)
        self.put_event(EVENT_RADAR_LOG, log)


def parse_formula(formula: str, data: Dict[str, float]) -> float:
    """"""
    locals().update(data)
    result = eval(formula)
    return result
