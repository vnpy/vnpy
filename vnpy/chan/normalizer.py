from __future__ import annotations

from collections.abc import Sequence

from .object import ChanBar, ChanDirection


def normalize_bars(bars: Sequence[ChanBar]) -> list[ChanBar]:
    """Normalize bars by merging Chan inclusion relationships."""

    normalized: list[ChanBar] = []

    for bar in bars:
        if not normalized:
            normalized.append(bar)
            continue

        last = normalized[-1]
        if not _is_including(last, bar):
            normalized.append(bar)
            continue

        direction = _detect_direction(normalized, bar)
        normalized[-1] = _merge_bars(last, bar, direction)

    return normalized


def _is_including(left: ChanBar, right: ChanBar) -> bool:
    left_contains_right = (
        left.high_price >= right.high_price
        and left.low_price <= right.low_price
    )
    right_contains_left = (
        right.high_price >= left.high_price
        and right.low_price <= left.low_price
    )
    return left_contains_right or right_contains_left


def _detect_direction(
    normalized: Sequence[ChanBar],
    current: ChanBar,
) -> ChanDirection:
    if len(normalized) >= 2:
        previous = normalized[-2]
        last = normalized[-1]

        if last.high_price >= previous.high_price and last.low_price >= previous.low_price:
            return ChanDirection.UP
        if last.high_price <= previous.high_price and last.low_price <= previous.low_price:
            return ChanDirection.DOWN

    last = normalized[-1]
    if current.close_price >= last.close_price:
        return ChanDirection.UP
    return ChanDirection.DOWN


def _merge_bars(left: ChanBar, right: ChanBar, direction: ChanDirection) -> ChanBar:
    if direction is ChanDirection.UP:
        high_price = max(left.high_price, right.high_price)
        low_price = max(left.low_price, right.low_price)
    else:
        high_price = min(left.high_price, right.high_price)
        low_price = min(left.low_price, right.low_price)

    return ChanBar(
        index=left.index,
        datetime=right.datetime,
        open_price=left.open_price,
        high_price=high_price,
        low_price=low_price,
        close_price=right.close_price,
        source_indexes=left.source_indexes + right.source_indexes,
    )
