from datetime import datetime, timedelta

from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.database import BarOverview
from vnpy_ctabacktester.engine import (
    BacktesterEngine,
    _get_missing_history_range,
    _get_missing_range_with_existing
)


def test_missing_range_when_empty() -> None:
    start = datetime(2024, 1, 1)
    end = datetime(2024, 1, 10)
    missing = _get_missing_history_range(
        [],
        symbol="IF88",
        exchange=Exchange.CFFEX,
        interval=Interval.MINUTE,
        start=start,
        end=end,
    )
    assert missing == (start, end)


def test_missing_range_when_partial() -> None:
    start = datetime(2024, 1, 1)
    end = datetime(2024, 1, 10)
    overview = BarOverview(
        symbol="IF88",
        exchange=Exchange.CFFEX,
        interval=Interval.MINUTE,
        count=100,
        start=start + timedelta(days=2),
        end=end - timedelta(days=2),
    )
    missing = _get_missing_history_range(
        [overview],
        symbol="IF88",
        exchange=Exchange.CFFEX,
        interval=Interval.MINUTE,
        start=start,
        end=end,
    )
    assert missing == (start, end)


def test_missing_range_when_full_coverage() -> None:
    start = datetime(2024, 1, 1)
    end = datetime(2024, 1, 10)
    overview = BarOverview(
        symbol="IF88",
        exchange=Exchange.CFFEX,
        interval=Interval.MINUTE,
        count=100,
        start=start,
        end=end,
    )
    missing = _get_missing_history_range(
        [overview],
        symbol="IF88",
        exchange=Exchange.CFFEX,
        interval=Interval.MINUTE,
        start=start,
        end=end,
    )
    assert missing is None


def test_pending_backtest_set_and_pop() -> None:
    engine = BacktesterEngine.__new__(BacktesterEngine)
    engine._pending_backtest = None
    engine._set_pending_backtest({"vt_symbol": "IF88.CFFEX"})
    assert engine.has_pending_backtest() is True
    data = engine._pop_pending_backtest()
    assert data["vt_symbol"] == "IF88.CFFEX"
    assert engine.has_pending_backtest() is False


def test_missing_range_with_existing_full_coverage() -> None:
    start = datetime(2024, 1, 1)
    end = datetime(2024, 1, 10)
    missing = _get_missing_range_with_existing(start, end, start, end)
    assert missing is None


def test_missing_range_with_existing_missing_head() -> None:
    start = datetime(2024, 1, 1)
    end = datetime(2024, 1, 10)
    existing_start = datetime(2024, 1, 5)
    existing_end = datetime(2024, 1, 10)
    missing = _get_missing_range_with_existing(start, end, existing_start, existing_end)
    assert missing == (start, existing_start)


def test_missing_range_with_existing_missing_tail() -> None:
    start = datetime(2024, 1, 1)
    end = datetime(2024, 1, 10)
    existing_start = datetime(2024, 1, 1)
    existing_end = datetime(2024, 1, 5)
    missing = _get_missing_range_with_existing(start, end, existing_start, existing_end)
    assert missing == (existing_end, end)
