from datetime import timedelta

from vnpy.trader.constant import Interval
from vnpy_ctastrategy.base import INTERVAL_DELTA_MAP


def test_interval_delta_map_supports_minute_15() -> None:
    assert INTERVAL_DELTA_MAP[Interval.MINUTE_15] == timedelta(minutes=15)


def test_interval_delta_map_supports_weekly() -> None:
    assert INTERVAL_DELTA_MAP[Interval.WEEKLY] == timedelta(weeks=1)
