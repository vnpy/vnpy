from collections.abc import Callable

from tests.chan_cases import (
    make_basic_pivot_case,
    make_basic_segment_case,
    make_fractal_case,
    make_inclusion_case,
    make_second_buy_case,
    make_strict_stroke_case,
    make_third_buy_case,
)
from vnpy.chan import ChanBar


CaseBuilder = Callable[[], list[ChanBar]]


def test_case_builders_return_ordered_unique_bars() -> None:
    builders: list[CaseBuilder] = [
        make_inclusion_case,
        make_fractal_case,
        make_strict_stroke_case,
        make_basic_segment_case,
        make_basic_pivot_case,
        make_second_buy_case,
        make_third_buy_case,
    ]

    for builder in builders:
        bars = builder()
        indexes = [bar.index for bar in bars]
        datetimes = [bar.datetime for bar in bars]

        assert len(bars) >= 3
        assert indexes == list(range(len(bars)))
        assert len(set(datetimes)) == len(datetimes)
        assert all(bar.source_indexes == (bar.index,) for bar in bars)


def test_case_builders_return_valid_ohlc_ranges() -> None:
    builders: list[CaseBuilder] = [
        make_inclusion_case,
        make_fractal_case,
        make_strict_stroke_case,
        make_basic_segment_case,
        make_basic_pivot_case,
        make_second_buy_case,
        make_third_buy_case,
    ]

    for builder in builders:
        for bar in builder():
            assert bar.high_price >= bar.open_price
            assert bar.high_price >= bar.close_price
            assert bar.low_price <= bar.open_price
            assert bar.low_price <= bar.close_price
            assert bar.high_price >= bar.low_price
