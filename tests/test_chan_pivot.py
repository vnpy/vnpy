from vnpy.chan import ChanConfig, ChanDirection, Segment
from vnpy.chan.pivot import build_pivots


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


def test_build_pivots_requires_minimum_segments() -> None:
    segments = [
        _segment(0, ChanDirection.UP, 10, 14),
        _segment(1, ChanDirection.DOWN, 11, 13),
    ]

    assert build_pivots(segments, ChanConfig(pivot_min_segments=3)) == []


def test_build_pivots_creates_overlap_area() -> None:
    segments = [
        _segment(0, ChanDirection.UP, 10, 14),
        _segment(1, ChanDirection.DOWN, 11, 13),
        _segment(2, ChanDirection.UP, 12, 15),
    ]

    pivots = build_pivots(segments, ChanConfig(pivot_min_segments=3))

    assert len(pivots) == 1
    assert pivots[0].start_segment_id == 0
    assert pivots[0].end_segment_id == 2
    assert pivots[0].low_price == 12
    assert pivots[0].high_price == 13


def test_build_pivots_rejects_non_overlapping_segments() -> None:
    segments = [
        _segment(0, ChanDirection.UP, 10, 11),
        _segment(1, ChanDirection.DOWN, 12, 13),
        _segment(2, ChanDirection.UP, 14, 15),
    ]

    assert build_pivots(segments, ChanConfig(pivot_min_segments=3)) == []


def test_build_pivots_extends_existing_overlap() -> None:
    segments = [
        _segment(0, ChanDirection.UP, 10, 15),
        _segment(1, ChanDirection.DOWN, 11, 14),
        _segment(2, ChanDirection.UP, 12, 13.5),
        _segment(3, ChanDirection.DOWN, 12.5, 13.2),
    ]

    pivots = build_pivots(segments, ChanConfig(pivot_min_segments=3))

    assert len(pivots) == 1
    assert pivots[0].end_segment_id == 3
    assert pivots[0].low_price == 12.5
    assert pivots[0].high_price == 13.2
