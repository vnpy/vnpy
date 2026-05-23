from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime
from enum import Enum


class ChanDirection(Enum):
    """Chan structure direction."""

    UP = "up"
    DOWN = "down"


class FractalType(Enum):
    """Chan fractal type."""

    TOP = "top"
    BOTTOM = "bottom"


class TrendState(Enum):
    """Current Chan trend state."""

    UP = "up"
    DOWN = "down"
    RANGE = "range"
    UNKNOWN = "unknown"


class BuyPointType(Enum):
    """Supported Chan buy point type."""

    FIRST_BUY = "first_buy"
    SECOND_BUY = "second_buy"
    THIRD_BUY = "third_buy"


class SellPointType(Enum):
    """Supported Chan sell point type."""

    FIRST_SELL = "first_sell"
    SECOND_SELL = "second_sell"
    THIRD_SELL = "third_sell"


@dataclass(frozen=True)
class ChanBar:
    """Normalized or raw bar snapshot used by Chan analyzer."""

    index: int
    datetime: datetime
    open_price: float
    high_price: float
    low_price: float
    close_price: float
    source_indexes: tuple[int, ...]


@dataclass(frozen=True)
class Fractal:
    """Confirmed top or bottom fractal."""

    id: int
    type: FractalType
    bar_index: int
    price: float
    datetime: datetime


@dataclass(frozen=True)
class Stroke:
    """Chan stroke connecting two opposite fractals."""

    id: int
    direction: ChanDirection
    start: Fractal
    end: Fractal
    high_price: float
    low_price: float


@dataclass(frozen=True)
class Segment:
    """Chan segment built from strokes."""

    id: int
    direction: ChanDirection
    start_stroke_id: int
    end_stroke_id: int
    high_price: float
    low_price: float


@dataclass(frozen=True)
class Pivot:
    """Chan pivot/center area."""

    id: int
    start_segment_id: int
    end_segment_id: int
    high_price: float
    low_price: float


@dataclass(frozen=True)
class SegmentMetric:
    """Strength proxy for a segment, used by future first-buy divergence checks."""

    segment_id: int
    direction: ChanDirection
    price_change: float
    amplitude: float
    stroke_count: int
    change_per_stroke: float


@dataclass(frozen=True)
class BuySignal:
    """Confirmed Chan buy signal."""

    id: int
    type: BuyPointType
    candidate_index: int
    confirmed_index: int
    stop_price: float
    reason: str
    stroke_id: int | None = None
    segment_id: int | None = None
    pivot_id: int | None = None


@dataclass(frozen=True)
class SellSignal:
    """Confirmed Chan sell signal."""

    id: int
    type: SellPointType
    candidate_index: int
    confirmed_index: int
    stop_price: float
    reason: str
    stroke_id: int | None = None
    segment_id: int | None = None
    pivot_id: int | None = None


@dataclass(frozen=True)
class ChanSnapshot:
    """Complete analyzer output for one calculation point."""

    bars: tuple[ChanBar, ...]
    fractals: tuple[Fractal, ...]
    strokes: tuple[Stroke, ...]
    segments: tuple[Segment, ...]
    pivots: tuple[Pivot, ...]
    segment_metrics: tuple[SegmentMetric, ...]
    trend: TrendState
    signals: tuple[BuySignal, ...]
    sell_signals: tuple[SellSignal, ...]
