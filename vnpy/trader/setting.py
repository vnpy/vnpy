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
    "database.password": "",

    # Risk engine: hard circuit breakers enforced inside CtaEngine.send_order.
    # max_daily_loss_pct: drawdown-from-UTC-day-open ratio that halts new opens today.
    # max_drawdown_pct: drawdown-from-peak-equity ratio that halts all new opens.
    # max_order_value_usdt: per-order notional cap; orders above this are rejected.
    # account_currency: currency account used as equity baseline (OKX emits one account per currency).
    # position_size_pct: reserved for strategy-side sizing helpers.
    "risk.enabled": True,
    "risk.account_currency": "USDT",
    "risk.max_daily_loss_pct": 0.03,
    "risk.max_drawdown_pct": 0.10,
    "risk.max_order_value_usdt": 200.0,
    "risk.max_order_value_pct": 0.0,
    "risk.position_size_pct": 0.20,
}


# Load global setting from json file.
SETTING_FILENAME: str = "vt_setting.json"
SETTINGS.update(load_json(SETTING_FILENAME))
