from __future__ import annotations

from collections.abc import Sequence

from .object import Pivot, Segment, TrendState


def classify_trend(
    segments: Sequence[Segment],
    pivots: Sequence[Pivot],
) -> TrendState:
    """Classify current Chan trend state conservatively."""

    if len(segments) < 3:
        return TrendState.UNKNOWN

    latest = segments[-1]
    if pivots:
        pivot = pivots[-1]
        if latest.low_price >= pivot.low_price and latest.high_price <= pivot.high_price:
            return TrendState.RANGE

    first = segments[-3]
    middle = segments[-2]

    rising = (
        first.low_price < middle.low_price < latest.low_price
        and first.high_price < middle.high_price < latest.high_price
    )
    if rising:
        return TrendState.UP

    falling = (
        first.low_price > middle.low_price > latest.low_price
        and first.high_price > middle.high_price > latest.high_price
    )
    if falling:
        return TrendState.DOWN

    return TrendState.RANGE
