from __future__ import annotations

import signal
from pathlib import Path
from threading import Event

from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy_paperaccount import PaperAccountApp
from vnpy_riskmanager import RiskManagerApp

from aqr.config import RiskConfig
from aqr.execution.vnpy.app import AqrExecutionApp
from aqr.execution.vnpy.engine import AqrExecutionEngine
from aqr.risk.vnpy_config_mapper import map_to_vnpy_risk_settings


def build_main_engine() -> tuple[MainEngine, AqrExecutionEngine]:
    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    main_engine.add_app(PaperAccountApp)
    risk_engine = main_engine.add_app(RiskManagerApp)
    risk_path = Path(__file__).resolve().parents[4] / "configs" / "risk" / "default.yaml"
    settings = map_to_vnpy_risk_settings(RiskConfig.from_yaml(risk_path))
    for rule_name, rule_setting in settings.items():
        risk_engine.update_rule_setting(rule_name, rule_setting)
    aqr_engine = main_engine.add_app(AqrExecutionApp)
    if not isinstance(aqr_engine, AqrExecutionEngine):
        raise TypeError("AqrExecutionApp returned an unexpected engine")
    return main_engine, aqr_engine


def main() -> int:
    stop_event = Event()
    main_engine, aqr_engine = build_main_engine()

    def request_stop(*_: object) -> None:
        stop_event.set()

    signal.signal(signal.SIGINT, request_stop)
    signal.signal(signal.SIGTERM, request_stop)
    try:
        aqr_engine.start()
        stop_event.wait()
    finally:
        main_engine.close()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
