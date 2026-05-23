from tests.chan_cases import make_basic_pivot_case, make_third_buy_case
from vnpy.chan import BuyPointType, ChanAnalyzer, ChanConfig, ChanSnapshot, TrendState


def test_analyzer_calculate_returns_complete_snapshot() -> None:
    analyzer = ChanAnalyzer()

    snapshot = analyzer.calculate(make_basic_pivot_case())

    assert isinstance(snapshot, ChanSnapshot)
    assert len(snapshot.bars) > 0
    assert len(snapshot.fractals) >= 1
    assert len(snapshot.strokes) >= 1
    assert snapshot.trend in {
        TrendState.UP,
        TrendState.DOWN,
        TrendState.RANGE,
        TrendState.UNKNOWN,
    }


def test_analyzer_update_bar_matches_batch_calculation() -> None:
    bars = make_third_buy_case()
    batch_snapshot = ChanAnalyzer().calculate(bars)
    incremental = ChanAnalyzer()

    for bar in bars:
        incremental_snapshot = incremental.update_bar(bar)

    assert incremental_snapshot == batch_snapshot
    assert incremental.snapshot() == batch_snapshot


def test_analyzer_reprocessing_same_bars_is_deterministic() -> None:
    bars = make_third_buy_case()
    analyzer = ChanAnalyzer()

    first = analyzer.calculate(bars)
    second = analyzer.calculate(bars)

    assert first == second


def test_analyzer_respects_max_bars_window() -> None:
    bars = make_third_buy_case()
    analyzer = ChanAnalyzer(ChanConfig(max_bars=5))

    snapshot = analyzer.calculate(bars)

    assert len(analyzer.raw_bars) == 5
    assert all(source_index >= len(bars) - 5 for bar in snapshot.bars for source_index in bar.source_indexes)


def test_analyzer_update_bar_preserves_indexes_after_max_bars_rolls() -> None:
    bars = make_third_buy_case() * 40
    analyzer = ChanAnalyzer(ChanConfig(max_bars=10))

    for bar in bars:
        analyzer.update_bar(bar)

    indexes = [bar.index for bar in analyzer.raw_bars]

    assert indexes == list(range(len(bars) - 10, len(bars)))


def test_analyzer_snapshot_contains_buy_signals() -> None:
    bars = make_third_buy_case()
    analyzer = ChanAnalyzer(ChanConfig(strict_stroke=False))

    snapshot = analyzer.calculate(bars)

    assert all(signal.type in {BuyPointType.SECOND_BUY, BuyPointType.THIRD_BUY} for signal in snapshot.signals)


def test_analyzer_snapshot_contains_segment_metrics_for_first_buy_research() -> None:
    analyzer = ChanAnalyzer(ChanConfig(strict_stroke=False))

    snapshot = analyzer.calculate(make_third_buy_case())

    assert len(snapshot.segment_metrics) == len(snapshot.segments)
    assert snapshot.segment_metrics
    metric = snapshot.segment_metrics[-1]
    segment = snapshot.segments[-1]
    assert metric.segment_id == segment.id
    assert metric.direction == segment.direction
    assert metric.price_change > 0
    assert metric.amplitude >= metric.price_change
    assert metric.stroke_count >= 1
    assert metric.change_per_stroke == metric.price_change / metric.stroke_count
