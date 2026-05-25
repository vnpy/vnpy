from datetime import datetime

from vnpy_okx.datafeed import Datafeed, _normalize_request_datetime
from vnpy_okx.okx_gateway import CHINA_TZ


def test_normalize_request_datetime_sets_timezone() -> None:
    start = datetime(2024, 1, 1, 0, 0, 0)
    end = datetime(2024, 1, 2, 0, 0, 0)

    normalized_start = _normalize_request_datetime(start)
    normalized_end = _normalize_request_datetime(end)

    assert normalized_start.tzinfo == CHINA_TZ
    assert normalized_end.tzinfo == CHINA_TZ
    assert (normalized_end - normalized_start).total_seconds() > 0


def test_datafeed_skips_malformed_demo_future_symbol() -> None:
    datafeed = Datafeed()

    assert datafeed._map_symbol("TESTING-USDT", "FUTURES") is None
