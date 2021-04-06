import traceback
from typing import Dict, Set, Any
from datetime import datetime
from collections import defaultdict
from enum import Enum

try:
    from winsound import PlaySound, SND_ASYNC
except ModuleNotFoundError:
    PlaySound = None

from vnpy.event import Event, EventEngine
from vnpy.trader.utility import save_json, load_json
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.object import (
    SubscribeRequest, ContractData, TickData, LogData,
)
from vnpy.trader.event import EVENT_TICK, EVENT_CONTRACT


APP_NAME = "MarketRadar"

EVENT_RADAR_RULE = "eRadarRule"
EVENT_RADAR_UPDATE = "eRadarUpdate"
EVENT_RADAR_LOG = "eRaderLog"
EVENT_RADAR_SIGNAL = "eRadarSignal"


class RadarRule:
    """"""

    def __init__(self, name: str, formula: str, params: Dict[str, str], ndigits: int):
        """"""
        self.name: str = name
        self.formula: str = formula
        self.params: Dict[str, str] = params
        self.ndigits = ndigits


class SignalType(Enum):
    """"""

    GREATER_THAN = "大于"
    LESS_THAN = "小于"
    EQUAL_TO = "等于"


class RadarSignal:
    """"""

    def __init__(
        self,
        rule_name: str,
        signal_id: int,
        signal_type: SignalType,
        signal_target: float,
        signal_sound: bool,
        signal_email: bool
    ) -> None:
        """"""
        self.rule_name: str = rule_name
        self.signal_id: int = signal_id
        self.signal_type: SignalType = signal_type
        self.signal_target: float = signal_target
        self.signal_sound: bool = signal_sound
        self.signal_email: bool = signal_email

        self.active = True


class RadarEngine(BaseEngine):
    """"""

    setting_filename = "market_radar_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.rules: Dict[str, RadarRule] = {}
        self.symbol_rule_map: Dict[str, Set[RadarRule]] = defaultdict(set)

        self.signals: Dict[int, RadarSignal] = {}
        self.rule_signal_map: Dict[str, Set[RadarSignal]] = defaultdict(set)

        self.signal_id: int = 0

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
        contract: ContractData = event.data
        vt_symbol = contract.vt_symbol

        if vt_symbol in self.symbol_rule_map:
            self.subscribe(vt_symbol)

    def subscribe(self, vt_symbol: str) -> None:
        """"""
        contract: ContractData = self.main_engine.get_contract(vt_symbol)
        if contract:
            req = SubscribeRequest(contract.symbol, contract.exchange)
            self.main_engine.subscribe(req, contract.gateway_name)

    def add_rule(
        self, name: str, formula: str, params: Dict[str, str], ndigits: int
    ) -> bool:
        """"""
        if name in self.rules:
            self.write_log(f"添加失败，已存在同名{name}")
            return False

        if not self.check_rule(formula, params):
            self.write_log(f"添加失败，公式无法运算{formula}")
            return False

        rule = RadarRule(name, formula, params, ndigits)
        self.rules[name] = rule

        for vt_symbol in params.values():
            if vt_symbol not in self.symbol_rule_map:
                self.subscribe(vt_symbol)

            self.symbol_rule_map[vt_symbol].add(rule)

        rule_data = {
            "name": name,
            "formula": formula,
            "params": params,
            "ndigits": ndigits
        }
        self.put_event(EVENT_RADAR_RULE, rule_data)

        self.calculate_rule(rule)

        self.write_log(f"添加成功{name}")
        return True

    def edit_rule(
        self, name: str, formula: str, params: Dict[str, str], ndigits: int
    ) -> bool:
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
            rules = self.symbol_rule_map[vt_symbol]
            if rule in rules:
                rules.remove(rule)

        # Add new symbol map
        rule.formula = formula
        rule.params = params
        rule.ndigits = ndigits

        for vt_symbol in params.values():
            if vt_symbol not in self.symbol_rule_map:
                self.subscribe(vt_symbol)

            self.symbol_rule_map[vt_symbol].add(rule)

        # Push event
        rule_data = {
            "name": name,
            "formula": formula,
            "params": params,
            "ndigits": ndigits
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
            rules = self.symbol_rule_map[vt_symbol]
            if rule in rules:
                rules.remove(rule)

        self.write_log(f"移除成功{name}")
        return True

    def load_setting(self) -> None:
        """"""
        setting = load_json(self.setting_filename)

        for d in setting:
            self.add_rule(d["name"], d["formula"], d["params"], d["ndigits"])

    def save_setting(self) -> None:
        """"""
        setting = []

        for rule in self.rules.values():
            d = {
                "name": rule.name,
                "formula": rule.formula,
                "params": rule.params,
                "ndigits": rule.ndigits
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
        value = round(value, rule.ndigits)

        dt = datetime.now()

        radar_data = {
            "name": rule.name,
            "value": value,
            "time": dt.strftime("%H:%M:%S.%f")
        }
        self.put_event(EVENT_RADAR_UPDATE, radar_data)

        # Check radar signal
        self.check_signal(rule.name, value)

    def check_rule(self, formula: str, params: Dict[str, str]) -> bool:
        """"""
        data = {}

        for name in params.keys():
            data[name] = 1

        try:
            parse_formula(formula, data)
        except Exception:
            msg = f"计算公式校验出错，细节：\n{traceback.format_exc()}"
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

    def add_signal(
        self,
        rule_name: str,
        signal_type: SignalType,
        signal_target: float,
        signal_sound: bool,
        signal_email: bool
    ) -> None:
        """"""
        self.signal_id += 1

        signal = RadarSignal(
            rule_name,
            self.signal_id,
            signal_type,
            signal_target,
            signal_sound,
            signal_email
        )

        self.signals[self.signal_id] = signal
        self.rule_signal_map[rule_name].add(signal)

        self.put_event(EVENT_RADAR_SIGNAL, signal)

    def remove_signal(self, signal_id: int) -> None:
        """"""
        if signal_id not in self.signals:
            return

        signal = self.signals.pop(signal_id)
        signal.active = False

        self.rule_signal_map[signal.rule_name].remove(signal)        
        self.put_event(EVENT_RADAR_SIGNAL, signal)

    def check_signal(self, rule_name: str, rule_value: float) -> None:
        """"""
        signals = self.rule_signal_map[rule_name]
        if not signals:
            return

        for signal in list(signals):
            triggered = False

            if signal.signal_type == SignalType.GREATER_THAN:
                if rule_value > signal.signal_target:
                    triggered = True
            elif signal.signal_type == SignalType.LESS_THAN:
                if rule_value < signal.signal_target:
                    triggered = True
            elif signal.signal_type == SignalType.EQUAL_TO:
                if rule_value == signal.signal_target:
                    triggered = True

            if triggered:
                signal.active = False
                signals.remove(signal)
                self.put_event(EVENT_RADAR_SIGNAL, signal)

                msg = (
                    f"雷达信号{signal.signal_id}已触发，"
                    f"规则{signal.rule_name}实时计算数值{rule_value}，"
                    f"{signal.signal_type.value}目标{signal.signal_target}"
                )

                self.write_log(msg)

                if signal.signal_email:
                    self.main_engine.send_email("市场雷达", msg)

                if signal.signal_sound and PlaySound:
                    PlaySound("SystemHand", SND_ASYNC)


def parse_formula(formula: str, data: Dict[str, float]) -> float:
    """"""
    locals().update(data)
    result = eval(formula)
    return result
