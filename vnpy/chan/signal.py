from __future__ import annotations

from collections.abc import Sequence

from .config import ChanConfig
from .object import (
    BuyPointType,
    BuySignal,
    ChanDirection,
    Pivot,
    Segment,
    SegmentMetric,
    SellPointType,
    SellSignal,
    TrendState,
)


def detect_buy_signals(
    segments: Sequence[Segment],
    pivots: Sequence[Pivot],
    trend: TrendState,
    config: ChanConfig,
    segment_metrics: Sequence[SegmentMetric] | None = None,
) -> list[BuySignal]:
    """Detect confirmed first-buy, second-buy and third-buy signals."""

    signals: list[BuySignal] = []

    first_buy = _detect_first_buy(segments, segment_metrics or ())
    if first_buy:
        signals.append(first_buy)

    third_buy = _detect_third_buy(segments, pivots, trend, config)
    if third_buy and all(signal.confirmed_index != third_buy.confirmed_index for signal in signals):
        third_buy = BuySignal(
            id=len(signals),
            type=third_buy.type,
            candidate_index=third_buy.candidate_index,
            confirmed_index=third_buy.confirmed_index,
            stop_price=third_buy.stop_price,
            reason=third_buy.reason,
            stroke_id=third_buy.stroke_id,
            segment_id=third_buy.segment_id,
            pivot_id=third_buy.pivot_id,
        )
        signals.append(third_buy)

    second_buy = _detect_second_buy(segments, pivots, config)
    if second_buy and all(signal.confirmed_index != second_buy.confirmed_index for signal in signals):
        second_buy = BuySignal(
            id=len(signals),
            type=second_buy.type,
            candidate_index=second_buy.candidate_index,
            confirmed_index=second_buy.confirmed_index,
            stop_price=second_buy.stop_price,
            reason=second_buy.reason,
            stroke_id=second_buy.stroke_id,
            segment_id=second_buy.segment_id,
            pivot_id=second_buy.pivot_id,
        )
        signals.append(second_buy)

    return signals


def detect_sell_signals(
    segments: Sequence[Segment],
    pivots: Sequence[Pivot],
    trend: TrendState,
    config: ChanConfig,
    segment_metrics: Sequence[SegmentMetric] | None = None,
) -> list[SellSignal]:
    """Detect confirmed first-sell, second-sell and third-sell signals."""

    signals: list[SellSignal] = []

    first_sell = _detect_first_sell(segments, segment_metrics or ())
    if first_sell:
        signals.append(first_sell)

    third_sell = _detect_third_sell(segments, pivots, trend, config)
    if third_sell and all(signal.confirmed_index != third_sell.confirmed_index for signal in signals):
        third_sell = SellSignal(
            id=len(signals),
            type=third_sell.type,
            candidate_index=third_sell.candidate_index,
            confirmed_index=third_sell.confirmed_index,
            stop_price=third_sell.stop_price,
            reason=third_sell.reason,
            stroke_id=third_sell.stroke_id,
            segment_id=third_sell.segment_id,
            pivot_id=third_sell.pivot_id,
        )
        signals.append(third_sell)

    second_sell = _detect_second_sell(segments, pivots, config)
    if second_sell and all(signal.confirmed_index != second_sell.confirmed_index for signal in signals):
        second_sell = SellSignal(
            id=len(signals),
            type=second_sell.type,
            candidate_index=second_sell.candidate_index,
            confirmed_index=second_sell.confirmed_index,
            stop_price=second_sell.stop_price,
            reason=second_sell.reason,
            stroke_id=second_sell.stroke_id,
            segment_id=second_sell.segment_id,
            pivot_id=second_sell.pivot_id,
        )
        signals.append(second_sell)

    return signals


def _detect_first_buy(
    segments: Sequence[Segment],
    segment_metrics: Sequence[SegmentMetric],
) -> BuySignal | None:
    if len(segments) < 4 or len(segment_metrics) < len(segments):
        return None

    first_down, rebound, lower_down, confirm = segments[-4:]
    if (
        first_down.direction is not ChanDirection.DOWN
        or rebound.direction is not ChanDirection.UP
        or lower_down.direction is not ChanDirection.DOWN
        or confirm.direction is not ChanDirection.UP
    ):
        return None

    if lower_down.low_price >= first_down.low_price:
        return None
    if confirm.high_price <= rebound.high_price:
        return None

    metrics_by_segment_id = {
        metric.segment_id: metric
        for metric in segment_metrics
    }
    first_metric = metrics_by_segment_id.get(first_down.id)
    lower_metric = metrics_by_segment_id.get(lower_down.id)
    if not first_metric or not lower_metric:
        return None
    if lower_metric.change_per_stroke >= first_metric.change_per_stroke:
        return None

    return BuySignal(
        id=0,
        type=BuyPointType.FIRST_BUY,
        candidate_index=lower_down.id,
        confirmed_index=confirm.id,
        stop_price=lower_down.low_price,
        reason="confirmed first buy: lower low with weaker down-segment force and upward turn",
        segment_id=confirm.id,
    )


def _detect_second_buy(
    segments: Sequence[Segment],
    pivots: Sequence[Pivot],
    config: ChanConfig,
) -> BuySignal | None:
    if len(segments) < 4:
        return None

    down, rebound, pullback, confirm = segments[-4:]
    if (
        down.direction is not ChanDirection.DOWN
        or rebound.direction is not ChanDirection.UP
        or pullback.direction is not ChanDirection.DOWN
        or confirm.direction is not ChanDirection.UP
    ):
        return None

    if pullback.low_price < down.low_price - config.second_buy_low_tolerance:
        return None
    if confirm.high_price <= rebound.high_price:
        return None
    if _segments_are_inside_latest_pivot((down, rebound, pullback, confirm), pivots):
        return None

    return BuySignal(
        id=0,
        type=BuyPointType.SECOND_BUY,
        candidate_index=pullback.id,
        confirmed_index=confirm.id,
        stop_price=pullback.low_price,
        reason="confirmed second buy: pullback holds above prior low and turns up",
        segment_id=confirm.id,
    )


def _detect_third_buy(
    segments: Sequence[Segment],
    pivots: Sequence[Pivot],
    trend: TrendState,
    config: ChanConfig,
) -> BuySignal | None:
    if (
        len(segments) < 3
        or not pivots
        or trend in {TrendState.DOWN, TrendState.UNKNOWN}
    ):
        return None

    leave, pullback, confirm = segments[-3:]
    pivot = _latest_completed_pivot_before(pivots, leave.id)
    if not pivot:
        return None

    if (
        leave.direction is not ChanDirection.UP
        or pullback.direction is not ChanDirection.DOWN
        or confirm.direction is not ChanDirection.UP
    ):
        return None
    if leave.high_price <= pivot.high_price:
        return None
    if pullback.low_price < pivot.high_price - config.third_buy_pullback_tolerance:
        return None
    if confirm.high_price <= leave.high_price:
        return None

    return BuySignal(
        id=0,
        type=BuyPointType.THIRD_BUY,
        candidate_index=pullback.id,
        confirmed_index=confirm.id,
        stop_price=pullback.low_price,
        reason="confirmed third buy: pullback stays above pivot and turns up",
        segment_id=confirm.id,
        pivot_id=pivot.id,
    )


def _detect_first_sell(
    segments: Sequence[Segment],
    segment_metrics: Sequence[SegmentMetric],
) -> SellSignal | None:
    if len(segments) < 4 or len(segment_metrics) < len(segments):
        return None

    first_up, pullback, higher_up, confirm = segments[-4:]
    if (
        first_up.direction is not ChanDirection.UP
        or pullback.direction is not ChanDirection.DOWN
        or higher_up.direction is not ChanDirection.UP
        or confirm.direction is not ChanDirection.DOWN
    ):
        return None

    if higher_up.high_price <= first_up.high_price:
        return None
    if confirm.low_price >= pullback.low_price:
        return None

    metrics_by_segment_id = {
        metric.segment_id: metric
        for metric in segment_metrics
    }
    first_metric = metrics_by_segment_id.get(first_up.id)
    higher_metric = metrics_by_segment_id.get(higher_up.id)
    if not first_metric or not higher_metric:
        return None
    if higher_metric.change_per_stroke >= first_metric.change_per_stroke:
        return None

    return SellSignal(
        id=0,
        type=SellPointType.FIRST_SELL,
        candidate_index=higher_up.id,
        confirmed_index=confirm.id,
        stop_price=higher_up.high_price,
        reason="confirmed first sell: higher high with weaker up-segment force and downward turn",
        segment_id=confirm.id,
    )


def _detect_second_sell(
    segments: Sequence[Segment],
    pivots: Sequence[Pivot],
    config: ChanConfig,
) -> SellSignal | None:
    if len(segments) < 4:
        return None

    up, decline, rebound, confirm = segments[-4:]
    if (
        up.direction is not ChanDirection.UP
        or decline.direction is not ChanDirection.DOWN
        or rebound.direction is not ChanDirection.UP
        or confirm.direction is not ChanDirection.DOWN
    ):
        return None

    if rebound.high_price > up.high_price + config.second_buy_low_tolerance:
        return None
    if confirm.low_price >= decline.low_price:
        return None
    if _segments_are_inside_latest_pivot((up, decline, rebound, confirm), pivots):
        return None

    return SellSignal(
        id=0,
        type=SellPointType.SECOND_SELL,
        candidate_index=rebound.id,
        confirmed_index=confirm.id,
        stop_price=rebound.high_price,
        reason="confirmed second sell: rebound holds below prior high and turns down",
        segment_id=confirm.id,
    )


def _detect_third_sell(
    segments: Sequence[Segment],
    pivots: Sequence[Pivot],
    trend: TrendState,
    config: ChanConfig,
) -> SellSignal | None:
    if (
        len(segments) < 3
        or not pivots
        or trend in {TrendState.UP, TrendState.UNKNOWN}
    ):
        return None

    leave, pullback, confirm = segments[-3:]
    pivot = _latest_completed_pivot_before(pivots, leave.id)
    if not pivot:
        return None

    if (
        leave.direction is not ChanDirection.DOWN
        or pullback.direction is not ChanDirection.UP
        or confirm.direction is not ChanDirection.DOWN
    ):
        return None
    if leave.low_price >= pivot.low_price:
        return None
    if pullback.high_price > pivot.low_price + config.third_buy_pullback_tolerance:
        return None
    if confirm.low_price >= leave.low_price:
        return None

    return SellSignal(
        id=0,
        type=SellPointType.THIRD_SELL,
        candidate_index=pullback.id,
        confirmed_index=confirm.id,
        stop_price=pullback.high_price,
        reason="confirmed third sell: pullback stays below pivot and turns down",
        segment_id=confirm.id,
        pivot_id=pivot.id,
    )


def _segments_are_inside_latest_pivot(
    segments: Sequence[Segment],
    pivots: Sequence[Pivot],
) -> bool:
    if not pivots:
        return False

    pivot = pivots[-1]
    return all(
        segment.id >= pivot.start_segment_id
        and segment.id <= pivot.end_segment_id
        and segment.low_price >= pivot.low_price
        and segment.high_price <= pivot.high_price
        for segment in segments
    )


def _latest_completed_pivot_before(
    pivots: Sequence[Pivot],
    segment_id: int,
) -> Pivot | None:
    """Return the nearest pivot completed before a leave segment."""
    for pivot in reversed(pivots):
        if pivot.end_segment_id < segment_id:
            return pivot
    return None
