from vnpy.chan import (
    BuyPointType,
    ChanConfig,
    ChanDirection,
    Pivot,
    SellPointType,
    Segment,
    SegmentMetric,
    TrendState,
)
from vnpy.chan.signal import detect_buy_signals, detect_sell_signals


def _segment(
    id: int,
    direction: ChanDirection,
    low_price: float,
    high_price: float,
) -> Segment:
    return Segment(
        id=id,
        direction=direction,
        start_stroke_id=id * 2,
        end_stroke_id=id * 2 + 1,
        high_price=high_price,
        low_price=low_price,
    )


def _metric(
    segment: Segment,
    change_per_stroke: float | None = None,
) -> SegmentMetric:
    price_change = segment.high_price - segment.low_price
    stroke_count = segment.end_stroke_id - segment.start_stroke_id + 1
    return SegmentMetric(
        segment_id=segment.id,
        direction=segment.direction,
        price_change=price_change,
        amplitude=price_change,
        stroke_count=stroke_count,
        change_per_stroke=(
            change_per_stroke
            if change_per_stroke is not None
            else price_change / stroke_count
        ),
    )


def _metrics(
    segments: list[Segment],
    overrides: dict[int, float] | None = None,
) -> list[SegmentMetric]:
    overrides = overrides or {}
    return [
        _metric(segment, overrides.get(segment.id))
        for segment in segments
    ]


def _pivot(
    id: int,
    start_segment_id: int,
    end_segment_id: int,
    low_price: float,
    high_price: float,
) -> Pivot:
    return Pivot(
        id=id,
        start_segment_id=start_segment_id,
        end_segment_id=end_segment_id,
        high_price=high_price,
        low_price=low_price,
    )


def test_detect_buy_signals_confirms_first_buy_on_weaker_lower_low() -> None:
    segments = [
        _segment(0, ChanDirection.DOWN, 8, 13),
        _segment(1, ChanDirection.UP, 8, 11),
        _segment(2, ChanDirection.DOWN, 7.5, 10),
        _segment(3, ChanDirection.UP, 7.5, 12),
    ]

    signals = detect_buy_signals(
        segments,
        [],
        TrendState.DOWN,
        ChanConfig(),
        _metrics(segments, {0: 5, 2: 2}),
    )

    assert len(signals) == 1
    assert signals[0].type is BuyPointType.FIRST_BUY
    assert signals[0].candidate_index == 2
    assert signals[0].confirmed_index == 3
    assert signals[0].stop_price == 7.5
    assert "first buy" in signals[0].reason


def test_detect_buy_signals_rejects_first_buy_without_divergence() -> None:
    segments = [
        _segment(0, ChanDirection.DOWN, 8, 13),
        _segment(1, ChanDirection.UP, 8, 11),
        _segment(2, ChanDirection.DOWN, 7.5, 10),
        _segment(3, ChanDirection.UP, 7.5, 12),
    ]

    signals = detect_buy_signals(
        segments,
        [],
        TrendState.DOWN,
        ChanConfig(),
        _metrics(segments, {0: 3, 2: 4}),
    )

    assert [signal.type for signal in signals] == []


def test_detect_buy_signals_confirms_second_buy() -> None:
    segments = [
        _segment(0, ChanDirection.DOWN, 8, 13),
        _segment(1, ChanDirection.UP, 8, 11),
        _segment(2, ChanDirection.DOWN, 8.5, 10),
        _segment(3, ChanDirection.UP, 8.5, 12),
    ]

    signals = detect_buy_signals(segments, [], TrendState.RANGE, ChanConfig())

    assert len(signals) == 1
    assert signals[0].type is BuyPointType.SECOND_BUY
    assert signals[0].candidate_index == 2
    assert signals[0].confirmed_index == 3
    assert signals[0].stop_price == 8.5
    assert "second buy" in signals[0].reason


def test_detect_buy_signals_rejects_second_buy_when_low_breaks() -> None:
    segments = [
        _segment(0, ChanDirection.DOWN, 8, 13),
        _segment(1, ChanDirection.UP, 8, 11),
        _segment(2, ChanDirection.DOWN, 7.9, 10),
        _segment(3, ChanDirection.UP, 7.9, 12),
    ]

    signals = detect_buy_signals(segments, [], TrendState.RANGE, ChanConfig())

    assert [signal.type for signal in signals] == []


def test_detect_buy_signals_rejects_second_buy_inside_same_pivot_range() -> None:
    pivot = _pivot(0, 0, 3, 7.5, 12.5)
    segments = [
        _segment(0, ChanDirection.DOWN, 8, 12),
        _segment(1, ChanDirection.UP, 8, 10.5),
        _segment(2, ChanDirection.DOWN, 8.5, 10),
        _segment(3, ChanDirection.UP, 8.5, 11),
    ]

    signals = detect_buy_signals(segments, [pivot], TrendState.RANGE, ChanConfig())

    assert [signal.type for signal in signals] == []


def test_detect_buy_signals_applies_second_buy_tolerance_boundary() -> None:
    config = ChanConfig(second_buy_low_tolerance=0.2)
    boundary_segments = [
        _segment(0, ChanDirection.DOWN, 8, 13),
        _segment(1, ChanDirection.UP, 8, 11),
        _segment(2, ChanDirection.DOWN, 7.8, 10),
        _segment(3, ChanDirection.UP, 7.8, 12),
    ]
    broken_segments = [
        _segment(0, ChanDirection.DOWN, 8, 13),
        _segment(1, ChanDirection.UP, 8, 11),
        _segment(2, ChanDirection.DOWN, 7.79, 10),
        _segment(3, ChanDirection.UP, 7.79, 12),
    ]

    boundary = detect_buy_signals(boundary_segments, [], TrendState.RANGE, config)
    broken = detect_buy_signals(broken_segments, [], TrendState.RANGE, config)

    assert [signal.type for signal in boundary] == [BuyPointType.SECOND_BUY]
    assert [signal.type for signal in broken] == []


def test_detect_buy_signals_confirms_third_buy() -> None:
    pivot = _pivot(0, 0, 2, 10, 12)
    segments = [
        _segment(0, ChanDirection.UP, 9, 13),
        _segment(1, ChanDirection.DOWN, 10, 12),
        _segment(2, ChanDirection.UP, 10.5, 13),
        _segment(3, ChanDirection.UP, 12.2, 14),
        _segment(4, ChanDirection.DOWN, 12.1, 13),
        _segment(5, ChanDirection.UP, 12.1, 15),
    ]

    signals = detect_buy_signals(segments, [pivot], TrendState.UP, ChanConfig())

    assert len(signals) == 1
    assert signals[0].type is BuyPointType.THIRD_BUY
    assert signals[0].candidate_index == 4
    assert signals[0].confirmed_index == 5
    assert signals[0].pivot_id == 0
    assert signals[0].stop_price == 12.1
    assert "third buy" in signals[0].reason


def test_detect_sell_signals_confirms_third_sell() -> None:
    pivot = _pivot(0, 0, 2, 10, 12)
    segments = [
        _segment(0, ChanDirection.DOWN, 9, 13),
        _segment(1, ChanDirection.UP, 10, 12),
        _segment(2, ChanDirection.DOWN, 9, 11.5),
        _segment(3, ChanDirection.DOWN, 8, 9.8),
        _segment(4, ChanDirection.UP, 8.5, 9.9),
        _segment(5, ChanDirection.DOWN, 7, 9.8),
    ]

    signals = detect_sell_signals(segments, [pivot], TrendState.DOWN, ChanConfig())

    assert len(signals) == 1
    assert signals[0].type is SellPointType.THIRD_SELL
    assert signals[0].candidate_index == 4
    assert signals[0].confirmed_index == 5
    assert signals[0].pivot_id == 0
    assert signals[0].stop_price == 9.9
    assert "third sell" in signals[0].reason


def test_detect_sell_signals_rejects_third_sell_when_pullback_reenters_pivot() -> None:
    pivot = _pivot(0, 0, 2, 10, 12)
    segments = [
        _segment(0, ChanDirection.DOWN, 9, 13),
        _segment(1, ChanDirection.UP, 10, 12),
        _segment(2, ChanDirection.DOWN, 9, 11.5),
        _segment(3, ChanDirection.DOWN, 8, 9.8),
        _segment(4, ChanDirection.UP, 8.5, 10.1),
        _segment(5, ChanDirection.DOWN, 7, 9.8),
    ]

    signals = detect_sell_signals(segments, [pivot], TrendState.DOWN, ChanConfig())

    assert signals == []


def test_detect_buy_signals_rejects_third_buy_when_pullback_reenters_pivot() -> None:
    pivot = _pivot(0, 0, 2, 10, 12)
    segments = [
        _segment(0, ChanDirection.UP, 9, 13),
        _segment(1, ChanDirection.DOWN, 10, 12),
        _segment(2, ChanDirection.UP, 10.5, 13),
        _segment(3, ChanDirection.UP, 12.2, 14),
        _segment(4, ChanDirection.DOWN, 11.9, 13),
        _segment(5, ChanDirection.UP, 11.9, 15),
    ]

    signals = detect_buy_signals(segments, [pivot], TrendState.UP, ChanConfig())

    assert [signal.type for signal in signals] == []


def test_detect_buy_signals_rejects_third_buy_when_trend_is_unknown() -> None:
    pivot = _pivot(0, 0, 2, 10, 12)
    segments = [
        _segment(0, ChanDirection.UP, 9, 13),
        _segment(1, ChanDirection.DOWN, 10, 12),
        _segment(2, ChanDirection.UP, 10.5, 13),
        _segment(3, ChanDirection.UP, 12.2, 14),
        _segment(4, ChanDirection.DOWN, 12.1, 13),
        _segment(5, ChanDirection.UP, 12.1, 15),
    ]

    signals = detect_buy_signals(segments, [pivot], TrendState.UNKNOWN, ChanConfig())

    assert [signal.type for signal in signals] == []


def test_detect_buy_signals_requires_third_buy_leave_after_pivot() -> None:
    pivot = _pivot(0, 0, 4, 10, 12)
    segments = [
        _segment(0, ChanDirection.UP, 9, 13),
        _segment(1, ChanDirection.DOWN, 10, 12),
        _segment(2, ChanDirection.UP, 10.5, 13),
        _segment(3, ChanDirection.UP, 12.2, 14),
        _segment(4, ChanDirection.DOWN, 12.1, 13),
        _segment(5, ChanDirection.UP, 12.1, 15),
    ]

    signals = detect_buy_signals(segments, [pivot], TrendState.UP, ChanConfig())

    assert [signal.type for signal in signals] == []


def test_detect_buy_signals_applies_third_buy_tolerance_boundary() -> None:
    pivot = _pivot(0, 0, 2, 10, 12)
    config = ChanConfig(third_buy_pullback_tolerance=0.2)
    boundary_segments = [
        _segment(0, ChanDirection.UP, 9, 13),
        _segment(1, ChanDirection.DOWN, 10, 12),
        _segment(2, ChanDirection.UP, 10.5, 13),
        _segment(3, ChanDirection.UP, 12.2, 14),
        _segment(4, ChanDirection.DOWN, 11.8, 13),
        _segment(5, ChanDirection.UP, 11.8, 15),
    ]
    broken_segments = [
        _segment(0, ChanDirection.UP, 9, 13),
        _segment(1, ChanDirection.DOWN, 10, 12),
        _segment(2, ChanDirection.UP, 10.5, 13),
        _segment(3, ChanDirection.UP, 12.2, 14),
        _segment(4, ChanDirection.DOWN, 11.79, 13),
        _segment(5, ChanDirection.UP, 11.79, 15),
    ]

    boundary = detect_buy_signals(boundary_segments, [pivot], TrendState.UP, config)
    broken = detect_buy_signals(broken_segments, [pivot], TrendState.UP, config)

    assert [signal.type for signal in boundary] == [BuyPointType.THIRD_BUY]
    assert [signal.type for signal in broken] == []


def test_detect_buy_signals_uses_strong_third_buy_confirmation() -> None:
    pivot = _pivot(0, 0, 2, 10, 12)
    segments = [
        _segment(0, ChanDirection.UP, 9, 13),
        _segment(1, ChanDirection.DOWN, 10, 12),
        _segment(2, ChanDirection.UP, 10.5, 13),
        _segment(3, ChanDirection.UP, 12.2, 14),
        _segment(4, ChanDirection.DOWN, 12.1, 13),
        _segment(5, ChanDirection.UP, 12.1, 14),
    ]

    signals = detect_buy_signals(segments, [pivot], TrendState.UP, ChanConfig())

    assert [signal.type for signal in signals] == []


def test_detect_buy_signals_does_not_duplicate_same_confirmation() -> None:
    segments = [
        _segment(0, ChanDirection.DOWN, 8, 13),
        _segment(1, ChanDirection.UP, 8, 11),
        _segment(2, ChanDirection.DOWN, 8.5, 10),
        _segment(3, ChanDirection.UP, 8.5, 12),
    ]

    first = detect_buy_signals(segments, [], TrendState.RANGE, ChanConfig())
    second = detect_buy_signals(segments, [], TrendState.RANGE, ChanConfig())

    assert first == second
    assert len({signal.confirmed_index for signal in first}) == len(first)
