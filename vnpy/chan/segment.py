from __future__ import annotations

from collections.abc import Sequence

from .config import ChanConfig
from .object import ChanDirection, Segment, Stroke


def build_segments(strokes: Sequence[Stroke], config: ChanConfig) -> list[Segment]:
    """Build conservative Chan segments from strokes."""

    del config

    if len(strokes) < 3:
        return []

    segments: list[Segment] = []
    active = _make_segment(0, strokes[0:3])

    for stroke in strokes[3:]:
        if _continues_segment(active, stroke):
            active = _extend_segment(active, stroke)
            continue

        if _reverses_segment(active, stroke):
            segments.append(active)
            start_index = max(0, stroke.id - 1)
            active = _make_segment(
                len(segments),
                strokes[start_index : stroke.id + 1],
                direction=stroke.direction,
            )

    segments.append(active)
    return segments


def _make_segment(
    id: int,
    strokes: Sequence[Stroke],
    direction: ChanDirection | None = None,
) -> Segment:
    first = strokes[0]
    last = strokes[-1]
    high_price = max(stroke.high_price for stroke in strokes)
    low_price = min(stroke.low_price for stroke in strokes)

    return Segment(
        id=id,
        direction=direction or first.direction,
        start_stroke_id=first.id,
        end_stroke_id=last.id,
        high_price=high_price,
        low_price=low_price,
    )


def _continues_segment(segment: Segment, stroke: Stroke) -> bool:
    if segment.direction is ChanDirection.UP:
        return stroke.high_price > segment.high_price
    return stroke.low_price < segment.low_price


def _reverses_segment(segment: Segment, stroke: Stroke) -> bool:
    if segment.direction is ChanDirection.UP:
        return stroke.low_price < segment.low_price
    return stroke.high_price > segment.high_price


def _extend_segment(segment: Segment, stroke: Stroke) -> Segment:
    return Segment(
        id=segment.id,
        direction=segment.direction,
        start_stroke_id=segment.start_stroke_id,
        end_stroke_id=stroke.id,
        high_price=max(segment.high_price, stroke.high_price),
        low_price=min(segment.low_price, stroke.low_price),
    )
