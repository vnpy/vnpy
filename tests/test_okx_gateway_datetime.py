from datetime import datetime, timezone

from vnpy_okx.okx_gateway import CHINA_TZ, _normalize_request_datetime


def test_normalize_request_datetime_sets_timezone() -> None:
    start = datetime(2024, 1, 1, 0, 0, 0)

    normalized_start = _normalize_request_datetime(start)

    assert normalized_start.tzinfo == CHINA_TZ


def test_normalize_request_datetime_converts_timezone() -> None:
    start = datetime(2024, 1, 1, 0, 0, 0, tzinfo=timezone.utc)

    normalized_start = _normalize_request_datetime(start)

    assert normalized_start.tzinfo == CHINA_TZ
    assert normalized_start.astimezone(CHINA_TZ).tzinfo == CHINA_TZ
