# CTA Backtester UI Improvements Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Add mouse-anchored zoom for the backtest candle chart, auto-fit the balance Y-axis, auto-download missing history data on backtest start, and fix interval dropdown text visibility.

**Architecture:** Introduce a pure helper to compute anchored zoom ranges, integrate it into `ChartWidget.wheelEvent`, add a database-coverage check in `BacktesterEngine` that can auto-download and resume a pending backtest, and adjust UI plotting/combobox styling in the CTA backtester widget.

**Tech Stack:** PySide6, pyqtgraph, vnpy CTA backtester engine, vnpy database interfaces.

### Task 1: History coverage helper + tests

**Files:**
- Create: `tests/test_backtester_history_check.py`
- Modify: `vnpy_ctabacktester/engine.py`

**Step 1: Write the failing test**

```python
from datetime import datetime, timedelta
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.database import BarOverview
from vnpy_ctabacktester.engine import _get_missing_history_range


def test_missing_range_when_empty():
    start = datetime(2024, 1, 1)
    end = datetime(2024, 1, 10)
    missing = _get_missing_history_range(
        [],
        symbol="IF88",
        exchange=Exchange.CFFEX,
        interval=Interval.MINUTE,
        start=start,
        end=end,
    )
    assert missing == (start, end)


def test_missing_range_when_partial():
    start = datetime(2024, 1, 1)
    end = datetime(2024, 1, 10)
    overview = BarOverview(
        symbol="IF88",
        exchange=Exchange.CFFEX,
        interval=Interval.MINUTE,
        count=100,
        start=start + timedelta(days=2),
        end=end - timedelta(days=2),
    )
    missing = _get_missing_history_range(
        [overview],
        symbol="IF88",
        exchange=Exchange.CFFEX,
        interval=Interval.MINUTE,
        start=start,
        end=end,
    )
    assert missing == (start, end)


def test_missing_range_when_full_coverage():
    start = datetime(2024, 1, 1)
    end = datetime(2024, 1, 10)
    overview = BarOverview(
        symbol="IF88",
        exchange=Exchange.CFFEX,
        interval=Interval.MINUTE,
        count=100,
        start=start,
        end=end,
    )
    missing = _get_missing_history_range(
        [overview],
        symbol="IF88",
        exchange=Exchange.CFFEX,
        interval=Interval.MINUTE,
        start=start,
        end=end,
    )
    assert missing is None
```

**Step 2: Run test to verify it fails**

Run: `pytest tests/test_backtester_history_check.py -v`  
Expected: FAIL with `ImportError` or missing function.

**Step 3: Write minimal implementation**

```python
def _get_missing_history_range(
    overviews: list[BarOverview],
    symbol: str,
    exchange: Exchange,
    interval: Interval,
    start: datetime,
    end: datetime
) -> tuple[datetime, datetime] | None:
    ...
```

**Step 4: Run test to verify it passes**

Run: `pytest tests/test_backtester_history_check.py -v`  
Expected: PASS.

**Step 5: Commit**

```bash
git add tests/test_backtester_history_check.py vnpy_ctabacktester/engine.py
git commit -m "[Add] Check missing history range for backtest"
```

### Task 2: Auto-download missing data and resume backtesting

**Files:**
- Modify: `vnpy_ctabacktester/engine.py`
- Modify: `vnpy_ctabacktester/ui/widget.py`

**Step 1: Write the failing test**

```python
def test_pending_backtest_set_and_pop():
    engine = BacktesterEngine.__new__(BacktesterEngine)
    engine._pending_backtest = None
    engine._set_pending_backtest({"vt_symbol": "IF88.CFFEX"})
    assert engine.has_pending_backtest() is True
    data = engine._pop_pending_backtest()
    assert data["vt_symbol"] == "IF88.CFFEX"
    assert engine.has_pending_backtest() is False
```

**Step 2: Run test to verify it fails**

Run: `pytest tests/test_backtester_history_check.py -v`  
Expected: FAIL (missing helper methods).

**Step 3: Write minimal implementation**

Implement in `BacktesterEngine`:
- `_set_pending_backtest(data: dict) -> None`
- `_pop_pending_backtest() -> dict | None`
- `has_pending_backtest() -> bool`
- `ensure_backtesting_data(...) -> bool` that uses `_get_missing_history_range` and triggers download if needed.

Update `BacktesterManager.start_backtesting` to:
- After strategy setting dialog accepted, call `ensure_backtesting_data(...)`.
- If download started, return early (backtest will resume after download).

Update `process_downloading_finished_event` to:
- If `engine.has_pending_backtest()` then call `engine.start_backtesting(...)` with pending data.

**Step 4: Run test to verify it passes**

Run: `pytest tests/test_backtester_history_check.py -v`  
Expected: PASS.

**Step 5: Commit**

```bash
git add vnpy_ctabacktester/engine.py vnpy_ctabacktester/ui/widget.py tests/test_backtester_history_check.py
git commit -m "[Mod] Auto-download missing history before backtest"
```

### Task 3: Mouse-anchored zoom, balance Y auto-fit, interval dropdown visibility

**Files:**
- Create: `vnpy/chart/zoom.py`
- Modify: `vnpy/chart/widget.py`
- Modify: `vnpy_ctabacktester/ui/widget.py`
- Create: `tests/test_chart_zoom.py`

**Step 1: Write the failing test**

```python
from vnpy.chart.zoom import compute_anchored_range


def test_compute_anchored_range_keeps_anchor():
    right_ix = 200
    bar_count = 100
    anchor_ix = 150
    new_right, new_count = compute_anchored_range(
        right_ix=right_ix,
        bar_count=bar_count,
        anchor_ix=anchor_ix,
        zoom_in=True,
        min_bar_count=100,
        max_bar_count=500
    )
    assert new_count < bar_count
    assert new_right - new_count <= anchor_ix <= new_right
```

**Step 2: Run test to verify it fails**

Run: `pytest tests/test_chart_zoom.py -v`  
Expected: FAIL with missing module/function.

**Step 3: Write minimal implementation**

Implement `vnpy/chart/zoom.py`:
- `compute_anchored_range(...) -> tuple[int, int]`
- Ensure anchor stays within range; clamp to `[min_bar_count, max_bar_count]`.

Update `ChartWidget.wheelEvent` to:
- Map mouse position to view X to get `anchor_ix`.
- Call `compute_anchored_range`.
- Update `_right_ix` and `_bar_count` and refresh range.

Update `BacktesterChart.set_data` to:
- Compute min/max of `balance` and set `balance_plot.setRange(yRange=...)` with padding.

Update `interval_combo` to use a custom view/palette so dropdown text is visible under dark theme.

**Step 4: Run test to verify it passes**

Run: `pytest tests/test_chart_zoom.py -v`  
Expected: PASS.

**Step 5: Commit**

```bash
git add vnpy/chart/zoom.py vnpy/chart/widget.py vnpy_ctabacktester/ui/widget.py tests/test_chart_zoom.py
git commit -m "[Mod] Improve backtester chart zoom and UI"
```

