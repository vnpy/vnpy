from __future__ import annotations

from collections.abc import Sequence

from .object import Segment, SegmentMetric


def build_segment_metrics(segments: Sequence[Segment]) -> list[SegmentMetric]:
    """Build segment strength proxies for later divergence analysis."""

    metrics: list[SegmentMetric] = []
    for segment in segments:
        price_change = abs(segment.high_price - segment.low_price)
        stroke_count = segment.end_stroke_id - segment.start_stroke_id + 1
        metrics.append(
            SegmentMetric(
                segment_id=segment.id,
                direction=segment.direction,
                price_change=price_change,
                amplitude=segment.high_price - segment.low_price,
                stroke_count=stroke_count,
                change_per_stroke=price_change / stroke_count,
            )
        )

    return metrics
