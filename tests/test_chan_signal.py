from vnpy.chan import (
    BuyPointType,
    ChanConfig,
    ChanDirection,
    Pivot,
    Segment,
    TrendState,
)
from vnpy.chan.signal import detect_buy_signals


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
