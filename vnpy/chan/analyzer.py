from __future__ import annotations

from collections.abc import Sequence
from typing import Any

from .config import ChanConfig
from .fractal import detect_fractals
from .normalizer import normalize_bars
from .object import ChanBar, ChanSnapshot
from .pivot import build_pivots
from .segment import build_segments
from .signal import detect_buy_signals
from .stroke import build_strokes
from .trend import classify_trend


class ChanAnalyzer:
    """Orchestrate Chan structure recognition stages."""

    def __init__(self, config: ChanConfig | None = None) -> None:
        self.config: ChanConfig = config or ChanConfig()
        self.raw_bars: list[ChanBar] = []
        self._snapshot: ChanSnapshot | None = None

    def update_bar(self, bar: Any) -> ChanSnapshot:
        """Append one bar and return the latest Chan snapshot."""

        self.raw_bars.append(self._to_chan_bar(bar, len(self.raw_bars)))
        if self.config.max_bars is not None:
            self.raw_bars = self.raw_bars[-self.config.max_bars :]

        self._snapshot = self._calculate_snapshot(self.raw_bars)
        return self._snapshot

    def calculate(self, bars: Sequence[Any]) -> ChanSnapshot:
        """Calculate Chan snapshot from a full bar sequence."""

        self.raw_bars = [
            self._to_chan_bar(bar, index)
            for index, bar in enumerate(bars)
        ]
        if self.config.max_bars is not None:
            self.raw_bars = self.raw_bars[-self.config.max_bars :]

        self._snapshot = self._calculate_snapshot(self.raw_bars)
        return self._snapshot

    def snapshot(self) -> ChanSnapshot:
        """Return the latest snapshot."""

        if self._snapshot is None:
            self._snapshot = self._calculate_snapshot(self.raw_bars)
        return self._snapshot

    def _calculate_snapshot(self, bars: Sequence[ChanBar]) -> ChanSnapshot:
        normalized = normalize_bars(bars)
        fractals = detect_fractals(normalized)
        strokes = build_strokes(fractals, self.config)
        segments = build_segments(strokes, self.config)
        pivots = build_pivots(segments, self.config)
        trend = classify_trend(segments, pivots)
        signals = detect_buy_signals(segments, pivots, trend, self.config)

        return ChanSnapshot(
            bars=tuple(normalized),
            fractals=tuple(fractals),
            strokes=tuple(strokes),
            segments=tuple(segments),
            pivots=tuple(pivots),
            trend=trend,
            signals=tuple(signals),
        )

    def _to_chan_bar(self, bar: Any, index: int) -> ChanBar:
        if isinstance(bar, ChanBar):
            if bar.index == index:
                return bar
            return ChanBar(
                index=index,
                datetime=bar.datetime,
                open_price=bar.open_price,
                high_price=bar.high_price,
                low_price=bar.low_price,
                close_price=bar.close_price,
                source_indexes=(index,),
            )

        return ChanBar(
            index=index,
            datetime=bar.datetime,
            open_price=bar.open_price,
            high_price=bar.high_price,
            low_price=bar.low_price,
            close_price=bar.close_price,
            source_indexes=(index,),
        )
