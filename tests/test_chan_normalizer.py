from tests.chan_cases import make_inclusion_case
from vnpy.chan import ChanBar
from vnpy.chan.normalizer import normalize_bars


def test_normalize_bars_merges_up_inclusion() -> None:
    bars = make_inclusion_case()[:3]

    normalized = normalize_bars(bars)

    assert len(normalized) == 2
    assert normalized[1].high_price == 12
    assert normalized[1].low_price == 10.4
    assert normalized[1].close_price == bars[2].close_price
    assert normalized[1].source_indexes == (1, 2)


def test_normalize_bars_merges_down_inclusion() -> None:
    bars = [
        ChanBar(0, make_inclusion_case()[0].datetime, 10, 12, 9, 11, (0,)),
        ChanBar(1, make_inclusion_case()[1].datetime, 10.5, 11, 8, 8.5, (1,)),
        ChanBar(2, make_inclusion_case()[2].datetime, 9, 10.5, 8.2, 9.5, (2,)),
    ]

    normalized = normalize_bars(bars)

    assert len(normalized) == 2
    assert normalized[1].high_price == 10.5
    assert normalized[1].low_price == 8
    assert normalized[1].close_price == bars[2].close_price
    assert normalized[1].source_indexes == (1, 2)


def test_normalize_bars_handles_nested_inclusion() -> None:
    bars = make_inclusion_case()

    normalized = normalize_bars(bars)

    assert len(normalized) == 3
    assert normalized[1].source_indexes == (1, 2)
    assert normalized[2].source_indexes == (3, 4)


def test_normalize_bars_keeps_non_included_bars() -> None:
    bars = [
        ChanBar(0, make_inclusion_case()[0].datetime, 10, 11, 9, 10.5, (0,)),
        ChanBar(1, make_inclusion_case()[1].datetime, 10.5, 12, 10, 11.5, (1,)),
        ChanBar(2, make_inclusion_case()[2].datetime, 11.5, 13, 11, 12.5, (2,)),
    ]

    normalized = normalize_bars(bars)

    assert normalized == bars
