from vnpy.chan import ChanDirection, Pivot, Segment, TrendState
from vnpy.chan.trend import classify_trend


def _segment(
    id: int,
    direction: ChanDirection,
    low_price: float,
    high_price: float,
) -> Segment:
    return Segment(
        id=id,
        direction=direction,
        start_stroke_id=id * 2,
        end_stroke_id=id * 2 + 1,
        high_price=high_price,
        low_price=low_price,
    )


def _pivot(
    id: int,
    start_segment_id: int,
    end_segment_id: int,
    low_price: float,
    high_price: float,
) -> Pivot:
    return Pivot(
        id=id,
        start_segment_id=start_segment_id,
        end_segment_id=end_segment_id,
        high_price=high_price,
        low_price=low_price,
    )


def test_classify_trend_unknown_when_data_is_insufficient() -> None:
    assert classify_trend([], []) is TrendState.UNKNOWN
    assert classify_trend([_segment(0, ChanDirection.UP, 10, 12)], []) is TrendState.UNKNOWN


def test_classify_trend_up_from_rising_segments() -> None:
    segments = [
        _segment(0, ChanDirection.UP, 10, 12),
        _segment(1, ChanDirection.DOWN, 11, 13),
        _segment(2, ChanDirection.UP, 12, 15),
    ]

    assert classify_trend(segments, []) is TrendState.UP


def test_classify_trend_down_from_falling_segments() -> None:
    segments = [
        _segment(0, ChanDirection.DOWN, 12, 15),
        _segment(1, ChanDirection.UP, 11, 14),
        _segment(2, ChanDirection.DOWN, 9, 13),
    ]

    assert classify_trend(segments, []) is TrendState.DOWN


def test_classify_trend_range_when_recent_segment_stays_inside_pivot() -> None:
    segments = [
        _segment(0, ChanDirection.UP, 10, 15),
        _segment(1, ChanDirection.DOWN, 11, 14),
        _segment(2, ChanDirection.UP, 12, 13),
        _segment(3, ChanDirection.DOWN, 11.5, 13.5),
    ]
    pivots = [_pivot(0, 0, 2, 11, 14)]

    assert classify_trend(segments, pivots) is TrendState.RANGE
