from __future__ import annotations

from collections.abc import Sequence

from .config import ChanConfig
from .object import ChanDirection, Pivot, Segment


def build_pivots(segments: Sequence[Segment], config: ChanConfig) -> list[Pivot]:
    """Build Chan pivots from overlapping segment price ranges."""

    min_segments = config.pivot_min_segments
    if len(segments) < min_segments:
        return []

    pivots: list[Pivot] = []
    position = 0

    while position + min_segments <= len(segments):
        window = segments[position : position + min_segments]
        low_price = max(segment.low_price for segment in window)
        high_price = min(segment.high_price for segment in window)

        if low_price > high_price + config.pivot_tolerance:
            position += 1
            continue

        start_segment_id = window[0].id
        end_position = position + min_segments - 1

        while end_position + 1 < len(segments):
            next_segment = segments[end_position + 1]
            if _is_leave_segment(low_price, high_price, next_segment):
                break
            next_low = max(low_price, next_segment.low_price)
            next_high = min(high_price, next_segment.high_price)
            if next_low > next_high + config.pivot_tolerance:
                break
            low_price = next_low
            high_price = next_high
            end_position += 1

        pivots.append(
            Pivot(
                id=len(pivots),
                start_segment_id=start_segment_id,
                end_segment_id=segments[end_position].id,
                high_price=high_price,
                low_price=low_price,
            )
        )
        position = end_position + 1

    return pivots


def _is_leave_segment(
    low_price: float,
    high_price: float,
    segment: Segment,
) -> bool:
    """Return whether an overlapping segment should be treated as leaving pivot."""
    upward_leave = (
        segment.direction is ChanDirection.UP
        and segment.high_price > high_price
        and segment.low_price >= low_price
    )
    downward_leave = (
        segment.direction is ChanDirection.DOWN
        and segment.low_price < low_price
        and segment.high_price <= high_price
    )
    return upward_leave or downward_leave
