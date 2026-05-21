from datetime import datetime, timedelta

from vnpy.chan import ChanConfig, ChanDirection, Fractal, FractalType
from vnpy.chan.stroke import build_strokes


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


def test_build_strokes_links_alternating_fractals() -> None:
    fractals = [
        _fractal(0, FractalType.BOTTOM, 1, 9),
        _fractal(1, FractalType.TOP, 3, 13),
        _fractal(2, FractalType.BOTTOM, 5, 8),
    ]

    strokes = build_strokes(fractals, ChanConfig(min_stroke_gap=1))

    assert len(strokes) == 2
    assert [stroke.direction for stroke in strokes] == [
        ChanDirection.UP,
        ChanDirection.DOWN,
    ]
    assert [(stroke.start.id, stroke.end.id) for stroke in strokes] == [(0, 1), (1, 2)]


def test_build_strokes_rejects_short_gap() -> None:
    fractals = [
        _fractal(0, FractalType.BOTTOM, 1, 9),
        _fractal(1, FractalType.TOP, 2, 13),
    ]

    strokes = build_strokes(fractals, ChanConfig(min_stroke_gap=2))

    assert strokes == []


def test_build_strokes_replaces_same_side_with_more_extreme_fractal() -> None:
    fractals = [
        _fractal(0, FractalType.BOTTOM, 1, 9),
        _fractal(1, FractalType.BOTTOM, 3, 8),
        _fractal(2, FractalType.TOP, 5, 13),
    ]

    strokes = build_strokes(fractals, ChanConfig(min_stroke_gap=1))

    assert len(strokes) == 1
    assert strokes[0].start.id == 1
    assert strokes[0].end.id == 2
    assert strokes[0].low_price == 8


def test_build_strokes_respects_strict_price_relationship() -> None:
    fractals = [
        _fractal(0, FractalType.BOTTOM, 1, 9),
        _fractal(1, FractalType.TOP, 3, 8.5),
    ]

    strokes = build_strokes(fractals, ChanConfig(strict_stroke=True))

    assert strokes == []
