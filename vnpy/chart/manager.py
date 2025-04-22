from __future__ import annotations

from datetime import datetime
from _collections_abc import dict_keys

from vnpy.trader.object import BarData

from .base import to_int


class BarManager:
    """"""

    def __init__(self) -> None:
        """"""
        self._bars: dict[datetime, BarData] = {}
        self._datetime_index_map: dict[datetime, int] = {}
        self._index_datetime_map: dict[int, datetime] = {}

        self._price_ranges: dict[tuple[int, int], tuple[float, float]] = {}
        self._volume_ranges: dict[tuple[int, int], tuple[float, float]] = {}

    def update_history(self, history: list[BarData]) -> None:
        """
        Update a list of bar data.
        """
        # Put all new bars into dict
        for bar in history:
            self._bars[bar.datetime] = bar

        # Sort bars dict according to bar.datetime
        self._bars = dict(sorted(self._bars.items(), key=lambda tp: tp[0]))

        # Update map relationiship
        ix_list: range = range(len(self._bars))
        dt_list: dict_keys = self._bars.keys()

        self._datetime_index_map = dict(zip(dt_list, ix_list, strict=False))
        self._index_datetime_map = dict(zip(ix_list, dt_list, strict=False))

        # Clear data range cache
        self._clear_cache()

    def update_bar(self, bar: BarData) -> None:
        """
        Update one single bar data.
        """
        dt: datetime = bar.datetime

        if dt not in self._datetime_index_map:
            ix: int = len(self._bars)
            self._datetime_index_map[dt] = ix
            self._index_datetime_map[ix] = dt

        self._bars[dt] = bar

        self._clear_cache()

    def get_count(self) -> int:
        """
        Get total number of bars.
        """
        return len(self._bars)

    def get_index(self, dt: datetime) -> int | None:
        """
        Get index with datetime.
        """
        return self._datetime_index_map.get(dt, None)

    def get_datetime(self, ix: float) -> datetime | None:
        """
        Get datetime with index.
        """
        ix = to_int(ix)
        return self._index_datetime_map.get(ix, None)

    def get_bar(self, ix: float) -> BarData | None:
        """
        Get bar data with index.
        """
        ix = to_int(ix)
        dt: datetime | None = self._index_datetime_map.get(ix, None)
        if not dt:
            return None

        return self._bars[dt]

    def get_all_bars(self) -> list[BarData]:
        """
        Get all bar data.
        """
        return list(self._bars.values())

    def get_price_range(self, min_ix: float | None = None, max_ix: float | None = None) -> tuple[float, float]:
        """
        Get price range to show within given index range.
        """
        if not self._bars:
            return 0, 1

        if min_ix is None or max_ix is None:
            min_ix = 0
            max_ix = len(self._bars) - 1
        else:
            min_ix = to_int(min_ix)
            max_ix = to_int(max_ix)
            max_ix = min(max_ix, self.get_count())

        buf: tuple[float, float] | None = self._price_ranges.get((min_ix, max_ix), None)
        if buf:
            return buf

        bar_list: list[BarData] = list(self._bars.values())[min_ix:max_ix + 1]
        first_bar: BarData = bar_list[0]
        max_price: float = first_bar.high_price
        min_price: float = first_bar.low_price

        for bar in bar_list[1:]:
            max_price = max(max_price, bar.high_price)
            min_price = min(min_price, bar.low_price)

        self._price_ranges[(min_ix, max_ix)] = (min_price, max_price)
        return min_price, max_price

    def get_volume_range(self, min_ix: float | None = None, max_ix: float | None = None) -> tuple[float, float]:
        """
        Get volume range to show within given index range.
        """
        if not self._bars:
            return 0, 1

        if min_ix is None or max_ix is None:
            min_ix = 0
            max_ix = len(self._bars) - 1
        else:
            min_ix = to_int(min_ix)
            max_ix = to_int(max_ix)
            max_ix = min(max_ix, self.get_count())

        buf: tuple[float, float] | None = self._volume_ranges.get((min_ix, max_ix), None)
        if buf:
            return buf

        bar_list: list[BarData] = list(self._bars.values())[min_ix:max_ix + 1]

        first_bar: BarData = bar_list[0]
        max_volume = first_bar.volume
        min_volume = 0

        for bar in bar_list[1:]:
            max_volume = max(max_volume, bar.volume)

        self._volume_ranges[(min_ix, max_ix)] = (min_volume, max_volume)
        return min_volume, max_volume

    def _clear_cache(self) -> None:
        """
        Clear cached range data.
        """
        self._price_ranges.clear()
        self._volume_ranges.clear()

    def clear_all(self) -> None:
        """
        Clear all data in manager.
        """
        self._bars.clear()
        self._datetime_index_map.clear()
        self._index_datetime_map.clear()

        self._clear_cache()
