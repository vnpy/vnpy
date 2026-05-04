"""
Global setting of the trading platform.
"""

from logging import INFO
from tzlocal import get_localzone_name

from .utility import load_json


SETTINGS: dict = {
    "font.family": "微软雅黑",
    "font.size": 12,

    "log.active": True,
    "log.level": INFO,
    "log.console": True,
    "log.file": True,

    "email.server": "smtp.qq.com",
    "email.port": 465,
    "email.username": "",
    "email.password": "",
    "email.sender": "",
    "email.receiver": "",

    "datafeed.name": "",
    "datafeed.username": "",
    "datafeed.password": "",

    "database.timezone": get_localzone_name(),
    "database.name": "sqlite",
    "database.database": "database.db",
    "database.host": "",
    "database.port": 0,
    "database.user": "",
    "database.password": "",

    "event.use_arrow": False,
    "event.use_disruptor": False,
    "event.buffer_size": 65536,  # Institutional default, must be power of 2
    "event.wait_strategy": "blocking",  # production: blocking (0% CPU), hft: busy_spin
    "event.core_id": None,  # Optional CPU core ID to pin managed worker thread
}


# Load global setting from json file.
SETTING_FILENAME: str = "vt_setting.json"
SETTINGS.update(load_json(SETTING_FILENAME))
