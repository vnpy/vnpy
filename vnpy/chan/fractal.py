from __future__ import annotations

from collections.abc import Sequence

from .object import ChanBar, Fractal, FractalType


def detect_fractals(bars: Sequence[ChanBar]) -> list[Fractal]:
    """Detect confirmed Chan fractals from normalized bars."""

    fractals: list[Fractal] = []
    next_id = 0

    for position in range(1, len(bars) - 1):
        left = bars[position - 1]
        middle = bars[position]
        right = bars[position + 1]

        if _is_top_fractal(left, middle, right):
            fractals.append(
                Fractal(
                    id=next_id,
                    type=FractalType.TOP,
                    bar_index=middle.index,
                    price=middle.high_price,
                    datetime=middle.datetime,
                )
            )
            next_id += 1
        elif _is_bottom_fractal(left, middle, right):
            fractals.append(
                Fractal(
                    id=next_id,
                    type=FractalType.BOTTOM,
                    bar_index=middle.index,
                    price=middle.low_price,
                    datetime=middle.datetime,
                )
            )
            next_id += 1

    return fractals


def _is_top_fractal(left: ChanBar, middle: ChanBar, right: ChanBar) -> bool:
    return (
        middle.high_price > left.high_price
        and middle.high_price > right.high_price
        and middle.low_price > left.low_price
        and middle.low_price > right.low_price
    )


def _is_bottom_fractal(left: ChanBar, middle: ChanBar, right: ChanBar) -> bool:
    return (
        middle.low_price < left.low_price
        and middle.low_price < right.low_price
        and middle.high_price < left.high_price
        and middle.high_price < right.high_price
    )
