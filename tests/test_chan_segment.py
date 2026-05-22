from datetime import datetime, timedelta

from vnpy.chan import ChanConfig, ChanDirection, Fractal, FractalType, Stroke
from vnpy.chan.segment import build_segments


def _fractal(
    id: int,
    type: FractalType,
    bar_index: int,
    price: float,
) -> Fractal:
    return Fractal(
        id=id,
        type=type,
        bar_index=bar_index,
        price=price,
        datetime=datetime(2026, 1, 1, 9, 30) + timedelta(minutes=bar_index),
    )


def _stroke(
    id: int,
    direction: ChanDirection,
    start_price: float,
    end_price: float,
) -> Stroke:
    start_type = FractalType.BOTTOM if direction is ChanDirection.UP else FractalType.TOP
    end_type = FractalType.TOP if direction is ChanDirection.UP else FractalType.BOTTOM
    start = _fractal(id * 2, start_type, id * 2, start_price)
    end = _fractal(id * 2 + 1, end_type, id * 2 + 1, end_price)
    return Stroke(
        id=id,
        direction=direction,
        start=start,
        end=end,
        high_price=max(start_price, end_price),
        low_price=min(start_price, end_price),
    )


def test_build_segments_requires_three_strokes() -> None:
    strokes = [
        _stroke(0, ChanDirection.UP, 9, 13),
        _stroke(1, ChanDirection.DOWN, 13, 10),
    ]

    assert build_segments(strokes, ChanConfig()) == []


def test_build_segments_creates_basic_three_stroke_segment() -> None:
    strokes = [
        _stroke(0, ChanDirection.UP, 9, 13),
        _stroke(1, ChanDirection.DOWN, 13, 10),
        _stroke(2, ChanDirection.UP, 10, 14),
    ]

    segments = build_segments(strokes, ChanConfig())

    assert len(segments) == 1
    assert segments[0].direction is ChanDirection.UP
    assert segments[0].start_stroke_id == 0
    assert segments[0].end_stroke_id == 2
    assert segments[0].high_price == 14
    assert segments[0].low_price == 9


def test_build_segments_extends_continuing_direction() -> None:
    strokes = [
        _stroke(0, ChanDirection.UP, 9, 13),
        _stroke(1, ChanDirection.DOWN, 13, 10),
        _stroke(2, ChanDirection.UP, 10, 14),
        _stroke(3, ChanDirection.DOWN, 14, 11),
        _stroke(4, ChanDirection.UP, 11, 15),
    ]

    segments = build_segments(strokes, ChanConfig())

    assert len(segments) == 1
    assert segments[0].end_stroke_id == 4
    assert segments[0].high_price == 15


def test_build_segments_starts_new_segment_on_reversal() -> None:
    strokes = [
        _stroke(0, ChanDirection.UP, 9, 13),
        _stroke(1, ChanDirection.DOWN, 13, 10),
        _stroke(2, ChanDirection.UP, 10, 14),
        _stroke(3, ChanDirection.DOWN, 14, 8.8),
        _stroke(4, ChanDirection.UP, 8.8, 12),
        _stroke(5, ChanDirection.DOWN, 12, 8),
    ]

    segments = build_segments(strokes, ChanConfig())

    assert len(segments) == 2
    assert [segment.direction for segment in segments] == [
        ChanDirection.UP,
        ChanDirection.DOWN,
    ]
    assert segments[1].start_stroke_id == 2
    assert segments[1].end_stroke_id == 5


def test_build_segments_does_not_reverse_without_breaking_extreme() -> None:
    strokes = [
        _stroke(0, ChanDirection.UP, 9, 13),
        _stroke(1, ChanDirection.DOWN, 13, 10),
        _stroke(2, ChanDirection.UP, 10, 14),
        _stroke(3, ChanDirection.DOWN, 14, 9.2),
        _stroke(4, ChanDirection.UP, 9.2, 13),
        _stroke(5, ChanDirection.DOWN, 13, 9.1),
    ]

    segments = build_segments(strokes, ChanConfig())

    assert len(segments) == 1
    assert segments[0].direction is ChanDirection.UP
