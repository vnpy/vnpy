from __future__ import annotations

from collections.abc import Sequence

from .config import ChanConfig
from .object import (
    BuyPointType,
    BuySignal,
    ChanDirection,
    Pivot,
    Segment,
    TrendState,
)


def detect_buy_signals(
    segments: Sequence[Segment],
    pivots: Sequence[Pivot],
    trend: TrendState,
    config: ChanConfig,
) -> list[BuySignal]:
    """Detect confirmed second-buy and third-buy signals."""

    signals: list[BuySignal] = []

    second_buy = _detect_second_buy(segments, config)
    if second_buy:
        signals.append(second_buy)

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

    return signals


def _detect_second_buy(
    segments: Sequence[Segment],
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
    if len(segments) < 3 or not pivots or trend is TrendState.DOWN:
        return None

    pivot = pivots[-1]
    leave, pullback, confirm = segments[-3:]

    if (
        leave.direction is not ChanDirection.UP
        or pullback.direction is not ChanDirection.DOWN
        or confirm.direction is not ChanDirection.UP
    ):
        return None
    if leave.high_price <= pivot.high_price:
        return None
    if pullback.low_price <= pivot.high_price - config.third_buy_pullback_tolerance:
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
