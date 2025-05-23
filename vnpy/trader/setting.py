"""
Global setting of the trading platform.
"""

from logging import CRITICAL, DEBUG, INFO
from typing import Dict, Any
from tzlocal import get_localzone_name

from .utility import load_json

_VT_SETTING_LOADED = False


SETTINGS: dict = {
    "font.family": "微软雅黑",
    "font.size": 12,

    "log.active": True,
    "log.level": DEBUG,
    "log.console": True,
    "log.file": True,

    "email.server": "smtp.qq.com",
    "email.port": 465,
    "email.username": "",
    "email.password": "",
    "email.sender": "",
    "email.receiver": "",

    "overview.jsonpath": "",

    "datafeed.name": "",
    "datafeed.username": "",
    "datafeed.password": "",

    "database.timezone": get_localzone_name(),
    # "database.name": "sqlite",
    # "database.database": "database.db",
    "database.name": "clickhouse",
    "database.database": "test",
    "database.host": "",
    "database.port": 0,
    "database.user": "",
    "database.password": "",

    # mycode
    "gateway.api_key": "",
    "gateway.api_secret": "",

    # trading
    "vt_symbols": [],

    "factor.settings_file_path": "factor_settings.json",
    "factor.definitions_file_path": "factor_maker_setting.json",
    "strategy.settings_file_path": "strategy_settings.json",
    "strategy.definitions_file_path": "strategy_template_definitions.json",
}

# Load global setting from json file.
SETTING_FILENAME: str = "vt_setting.json"

if not _VT_SETTING_LOADED:
    SETTINGS.update(load_json(SETTING_FILENAME))
    _VT_SETTING_LOADED = True
    print(f"[vnpy.trader.setting] Updated SETTINGS from {SETTING_FILENAME}")


# def get_settings(prefix: str = "") -> Dict[str, Any]:
#     prefix_length: int = len(prefix)
#     settings = {k[prefix_length:]: v for k, v in SETTINGS.items() if k.startswith(prefix)}
#     return settings
