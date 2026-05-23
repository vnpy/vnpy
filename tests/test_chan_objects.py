from datetime import datetime

from vnpy.chan import (
    BuyPointType,
    ChanBar,
    ChanConfig,
    ChanDirection,
    ChanSnapshot,
    Fractal,
    FractalType,
    TrendState,
)


def test_chan_enums_expose_stable_values() -> None:
    assert ChanDirection.UP.value == "up"
    assert ChanDirection.DOWN.value == "down"
    assert FractalType.TOP.value == "top"
    assert FractalType.BOTTOM.value == "bottom"
    assert TrendState.UNKNOWN.value == "unknown"
    assert BuyPointType.SECOND_BUY.value == "second_buy"
    assert BuyPointType.THIRD_BUY.value == "third_buy"


def test_chan_config_defaults_are_conservative() -> None:
    config = ChanConfig()

    assert config.min_stroke_gap == 1
    assert config.strict_stroke is True
    assert config.pivot_min_segments == 3
    assert config.pivot_tolerance == 0
    assert config.third_buy_pullback_tolerance == 0
    assert config.second_buy_low_tolerance == 0
    assert config.confirm_on_close is True
    assert config.max_bars is None


def test_chan_bar_keeps_source_indexes_immutable() -> None:
    bar = ChanBar(
        index=3,
        datetime=datetime(2026, 1, 1, 9, 33),
        open_price=10,
        high_price=12,
        low_price=9,
        close_price=11,
        source_indexes=(2, 3),
    )

    assert bar.index == 3
    assert bar.source_indexes == (2, 3)


def test_chan_snapshot_is_immutable_container() -> None:
    bar = ChanBar(
        index=0,
        datetime=datetime(2026, 1, 1, 9, 30),
        open_price=10,
        high_price=11,
        low_price=9,
        close_price=10.5,
        source_indexes=(0,),
    )
    fractal = Fractal(
        id=0,
        type=FractalType.BOTTOM,
        bar_index=0,
        price=9,
        datetime=bar.datetime,
    )
    snapshot = ChanSnapshot(
        bars=(bar,),
        fractals=(fractal,),
        strokes=(),
        segments=(),
        pivots=(),
        segment_metrics=(),
        trend=TrendState.UNKNOWN,
        signals=(),
        sell_signals=(),
    )

    assert snapshot.bars == (bar,)
    assert snapshot.fractals == (fractal,)
    assert snapshot.trend is TrendState.UNKNOWN
