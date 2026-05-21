from __future__ import annotations

from datetime import datetime, timedelta

from vnpy.chan import ChanBar


def _make_bars(values: list[tuple[float, float, float, float]]) -> list[ChanBar]:
    start = datetime(2026, 1, 1, 9, 30)
    bars: list[ChanBar] = []

    for index, (open_price, high_price, low_price, close_price) in enumerate(values):
        bars.append(
            ChanBar(
                index=index,
                datetime=start + timedelta(minutes=index),
                open_price=open_price,
                high_price=high_price,
                low_price=low_price,
                close_price=close_price,
                source_indexes=(index,),
            )
        )

    return bars


def make_inclusion_case() -> list[ChanBar]:
    """Return bars with both nested and directional inclusion."""

    return _make_bars(
        [
            (10, 11, 9, 10.5),
            (10.6, 12, 10, 11.5),
            (11.3, 11.8, 10.4, 11),
            (11.2, 13, 11, 12.5),
            (12.3, 12.6, 11.4, 12),
        ]
    )


def make_fractal_case() -> list[ChanBar]:
    """Return bars containing one top and one bottom fractal."""

    return _make_bars(
        [
            (10, 11, 9, 10.5),
            (10.5, 13, 10, 12),
            (12, 12.2, 9.8, 10),
            (10, 10.5, 8, 8.5),
            (8.6, 11, 8.4, 10.5),
        ]
    )


def make_strict_stroke_case() -> list[ChanBar]:
    """Return alternating swings suitable for strict stroke tests."""

    return _make_bars(
        [
            (10, 11, 9, 10.4),
            (10.4, 13, 10.1, 12.5),
            (12.4, 12.8, 9.5, 10),
            (10, 14, 9.8, 13),
            (13, 13.2, 8.5, 9),
            (9, 12, 8.8, 11.5),
            (11.4, 11.8, 7.8, 8.2),
        ]
    )


def make_basic_segment_case() -> list[ChanBar]:
    """Return swings that should support a basic segment."""

    return _make_bars(
        [
            (10, 11, 9, 10),
            (10, 14, 10, 13),
            (13, 13.5, 9.5, 10),
            (10, 15, 10, 14),
            (14, 14.2, 10.5, 11),
            (11, 16, 11, 15),
            (15, 15.2, 11.5, 12),
        ]
    )


def make_basic_pivot_case() -> list[ChanBar]:
    """Return overlapping swings suitable for pivot tests."""

    return _make_bars(
        [
            (10, 11, 9, 10),
            (10, 14, 10, 13),
            (13, 13.5, 10.5, 11),
            (11, 14.5, 11, 14),
            (14, 14.2, 10.8, 11.2),
            (11.6, 15, 11.5, 14.5),
            (14.4, 14.8, 11.2, 12),
        ]
    )


def make_second_buy_case() -> list[ChanBar]:
    """Return a down structure, first rebound, higher pullback, and confirmation."""

    return _make_bars(
        [
            (15, 15.5, 14.5, 15),
            (15, 15.2, 12, 12.5),
            (12.5, 13, 10, 10.5),
            (10.5, 12.5, 10.2, 12),
            (12, 12.3, 10.6, 11),
            (11, 13.5, 10.9, 13),
            (13, 14.2, 12.5, 14),
        ]
    )


def make_third_buy_case() -> list[ChanBar]:
    """Return a pivot, upward leave, pullback above pivot, and confirmation."""

    return _make_bars(
        [
            (10, 11, 9.5, 10.5),
            (10.5, 13, 10, 12.5),
            (12.5, 12.8, 10.2, 10.8),
            (10.8, 13.2, 10.5, 12.8),
            (12.8, 12.9, 10.4, 11),
            (11.3, 14.5, 11.2, 14),
            (14, 15.5, 13.8, 15),
            (15, 15.2, 13.4, 14),
            (14, 16.2, 13.6, 16),
        ]
    )
