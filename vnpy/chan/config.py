from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class ChanConfig:
    """Configuration for Chan structure recognition."""

    min_stroke_gap: int = 1
    strict_stroke: bool = True
    pivot_min_segments: int = 3
    pivot_tolerance: float = 0
    third_buy_pullback_tolerance: float = 0
    second_buy_low_tolerance: float = 0
    confirm_on_close: bool = True
    max_bars: int | None = None
