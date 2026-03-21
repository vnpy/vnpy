"""
Global setting of the trading platform.
"""

import platform
from logging import INFO
from tzlocal import get_localzone_name

from .utility import load_json


if platform.system() == "Darwin":
    DEFAULT_FONT_FAMILY: str = "PingFang SC"
elif platform.system() == "Windows":
    DEFAULT_FONT_FAMILY = "微软雅黑"
else:
    DEFAULT_FONT_FAMILY = "DejaVu Sans"


SETTINGS: dict = {
    "font.family": DEFAULT_FONT_FAMILY,
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
    "database.password": ""
}


# Load global setting from json file.
SETTING_FILENAME: str = "vt_setting.json"
SETTINGS.update(load_json(SETTING_FILENAME))
