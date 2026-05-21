from __future__ import annotations

from collections.abc import Sequence

from .config import ChanConfig
from .object import ChanDirection, Fractal, FractalType, Stroke


def build_strokes(fractals: Sequence[Fractal], config: ChanConfig) -> list[Stroke]:
    """Build Chan strokes from alternating fractals."""

    selected: list[Fractal] = []
    for fractal in fractals:
        if not selected:
            selected.append(fractal)
            continue

        last = selected[-1]
        if fractal.type is last.type:
            if _is_more_extreme(fractal, last):
                selected[-1] = fractal
            continue

        if _can_link(last, fractal, config):
            selected.append(fractal)

    strokes: list[Stroke] = []
    for start, end in zip(selected, selected[1:], strict=False):
        direction = _stroke_direction(start, end)
        strokes.append(
            Stroke(
                id=len(strokes),
                direction=direction,
                start=start,
                end=end,
                high_price=max(start.price, end.price),
                low_price=min(start.price, end.price),
            )
        )

    return strokes


def _is_more_extreme(current: Fractal, previous: Fractal) -> bool:
    if current.type is FractalType.TOP:
        return current.price > previous.price
    return current.price < previous.price


def _can_link(start: Fractal, end: Fractal, config: ChanConfig) -> bool:
    if end.bar_index - start.bar_index < config.min_stroke_gap:
        return False

    if not config.strict_stroke:
        return True

    if start.type is FractalType.BOTTOM and end.type is FractalType.TOP:
        return end.price > start.price
    if start.type is FractalType.TOP and end.type is FractalType.BOTTOM:
        return end.price < start.price
    return False


def _stroke_direction(start: Fractal, end: Fractal) -> ChanDirection:
    if start.type is FractalType.BOTTOM and end.type is FractalType.TOP:
        return ChanDirection.UP
    return ChanDirection.DOWN
