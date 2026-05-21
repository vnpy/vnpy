# Chan Strategy Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Build a Chan theory analyzer and long-only CTA strategy prototype that identifies points, lines, pivots, trend state, and second/third buy points from bar data.

**Architecture:** Add a reusable `vnpy/chan/` core package with deterministic structure-recognition stages and a `vnpy_ctastrategy/strategies/chan_strategy.py` shell that consumes confirmed signals. Use reusable synthetic test cases as the baseline regression library before any real-market optimization.

**Tech Stack:** Python 3.12, pytest, dataclasses, vn.py `BarData`, vn.py CTA strategy template.

---

### Task 1: Core Data Objects And Config

**Files:**
- Create: `vnpy/chan/__init__.py`
- Create: `vnpy/chan/object.py`
- Create: `vnpy/chan/config.py`
- Test: `tests/test_chan_objects.py`

**Step 1: Write failing tests**

Create tests for enum values, dataclass fields, default config values, and snapshot immutability expectations.

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_objects.py -q
```

Expected: FAIL because `vnpy.chan` does not exist.

**Step 2: Implement minimal objects**

Add:

- `ChanDirection`
- `FractalType`
- `TrendState`
- `BuyPointType`
- `ChanBar`
- `Fractal`
- `Stroke`
- `Segment`
- `Pivot`
- `BuySignal`
- `ChanSnapshot`
- `ChanConfig`

All public functions and methods must be typed.

**Step 3: Verify and commit**

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_objects.py -q
git diff --check
```

Commit only the task files:

```bash
git add vnpy/chan/__init__.py vnpy/chan/object.py vnpy/chan/config.py tests/test_chan_objects.py
git commit -m "[Add] Define Chan analyzer objects"
```

### Task 2: Reusable Chan Test Case Library

**Files:**
- Create: `tests/chan_cases.py`
- Test: `tests/test_chan_cases.py`

**Step 1: Write failing tests**

Add helper tests that verify each named case returns deterministic OHLC bars with unique timestamps.

Required builders:

- `make_inclusion_case()`
- `make_fractal_case()`
- `make_strict_stroke_case()`
- `make_basic_segment_case()`
- `make_basic_pivot_case()`
- `make_second_buy_case()`
- `make_third_buy_case()`

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_cases.py -q
```

Expected: FAIL because builders do not exist.

**Step 2: Implement case builders**

Use small synthetic bar sequences with explicit high/low/close values. Keep each case readable and deterministic.

**Step 3: Verify and commit**

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_cases.py -q
```

Commit:

```bash
git add tests/chan_cases.py tests/test_chan_cases.py
git commit -m "[Add] Add Chan structure test cases"
```

### Task 3: K-Line Inclusion Normalizer

**Files:**
- Create: `vnpy/chan/normalizer.py`
- Test: `tests/test_chan_normalizer.py`

**Step 1: Write failing tests**

Cover up-inclusion, down-inclusion, nested inclusion, and no-inclusion.

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_normalizer.py -q
```

Expected: FAIL because normalizer does not exist.

**Step 2: Implement normalizer**

Implement `normalize_bars(bars: Sequence[ChanBar]) -> list[ChanBar]`.

Rules:

- Preserve order and source indexes.
- Merge included bars according to current direction.
- Keep deterministic high/low/open/close behavior.
- Do not mutate input bars.

**Step 3: Verify and commit**

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_normalizer.py -q
```

Commit:

```bash
git add vnpy/chan/normalizer.py tests/test_chan_normalizer.py
git commit -m "[Add] Normalize Chan included bars"
```

### Task 4: Fractal Recognition

**Files:**
- Create: `vnpy/chan/fractal.py`
- Test: `tests/test_chan_fractal.py`

**Step 1: Write failing tests**

Cover top fractal, bottom fractal, ignored edge bars, and no duplicate same-index fractal.

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_fractal.py -q
```

Expected: FAIL because detector does not exist.

**Step 2: Implement detector**

Implement `detect_fractals(bars: Sequence[ChanBar]) -> list[Fractal]`.

Confirm a fractal only when both neighbor bars exist.

**Step 3: Verify and commit**

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_fractal.py -q
```

Commit:

```bash
git add vnpy/chan/fractal.py tests/test_chan_fractal.py
git commit -m "[Add] Detect Chan fractals"
```

### Task 5: Stroke Recognition

**Files:**
- Create: `vnpy/chan/stroke.py`
- Test: `tests/test_chan_stroke.py`

**Step 1: Write failing tests**

Cover valid strict stroke, rejected short-gap stroke, alternating fractal requirement, and same-side replacement by more extreme fractal.

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_stroke.py -q
```

Expected: FAIL because stroke builder does not exist.

**Step 2: Implement stroke builder**

Implement `build_strokes(fractals: Sequence[Fractal], config: ChanConfig) -> list[Stroke]`.

Use `min_stroke_gap` and `strict_stroke`. Keep replacement logic deterministic.

**Step 3: Verify and commit**

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_stroke.py -q
```

Commit:

```bash
git add vnpy/chan/stroke.py tests/test_chan_stroke.py
git commit -m "[Add] Build Chan strokes"
```

### Task 6: Segment Recognition

**Files:**
- Create: `vnpy/chan/segment.py`
- Test: `tests/test_chan_segment.py`

**Step 1: Write failing tests**

Cover a basic three-stroke segment, continuation, and direction reversal.

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_segment.py -q
```

Expected: FAIL because segment builder does not exist.

**Step 2: Implement segment builder**

Implement `build_segments(strokes: Sequence[Stroke], config: ChanConfig) -> list[Segment]`.

First version can use a conservative three-stroke minimum and deterministic direction changes.

**Step 3: Verify and commit**

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_segment.py -q
```

Commit:

```bash
git add vnpy/chan/segment.py tests/test_chan_segment.py
git commit -m "[Add] Build Chan segments"
```

### Task 7: Pivot And Trend Recognition

**Files:**
- Create: `vnpy/chan/pivot.py`
- Create: `vnpy/chan/trend.py`
- Test: `tests/test_chan_pivot.py`
- Test: `tests/test_chan_trend.py`

**Step 1: Write failing tests**

Pivot tests:

- Valid overlap area.
- No-overlap rejection.
- Pivot extension.

Trend tests:

- Up trend from rising pivots/segments.
- Down trend from falling pivots/segments.
- Range when pivot dominates.
- Unknown when data is insufficient.

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_pivot.py tests/test_chan_trend.py -q
```

Expected: FAIL because pivot and trend modules do not exist.

**Step 2: Implement pivot and trend modules**

Implement:

- `build_pivots(segments: Sequence[Segment], config: ChanConfig) -> list[Pivot]`
- `classify_trend(segments: Sequence[Segment], pivots: Sequence[Pivot]) -> TrendState`

**Step 3: Verify and commit**

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_pivot.py tests/test_chan_trend.py -q
```

Commit:

```bash
git add vnpy/chan/pivot.py vnpy/chan/trend.py tests/test_chan_pivot.py tests/test_chan_trend.py
git commit -m "[Add] Identify Chan pivots and trend"
```

### Task 8: Second-Buy And Third-Buy Signals

**Files:**
- Create: `vnpy/chan/signal.py`
- Test: `tests/test_chan_signal.py`

**Step 1: Write failing tests**

Cover:

- Valid second-buy.
- Rejected second-buy when pullback breaks prior low.
- Valid third-buy.
- Rejected third-buy when pullback re-enters pivot.
- No duplicate confirmation for the same structure.

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_signal.py -q
```

Expected: FAIL because signal module does not exist.

**Step 2: Implement signal module**

Implement `detect_buy_signals(...) -> list[BuySignal]` using segments, pivots, trend state, and config tolerance values.

Each signal must include a reason string and stop reference price.

**Step 3: Verify and commit**

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_signal.py -q
```

Commit:

```bash
git add vnpy/chan/signal.py tests/test_chan_signal.py
git commit -m "[Add] Detect Chan buy signals"
```

### Task 9: Analyzer Orchestration

**Files:**
- Create: `vnpy/chan/analyzer.py`
- Test: `tests/test_chan_analyzer.py`

**Step 1: Write failing tests**

Cover:

- Incremental bar updates.
- Snapshot contains normalized bars, fractals, strokes, segments, pivots, trend, and signals.
- Re-processing the same bars gives identical output.

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_analyzer.py -q
```

Expected: FAIL because analyzer does not exist.

**Step 2: Implement analyzer**

Implement:

- `ChanAnalyzer.update_bar(bar: BarData | ChanBar) -> ChanSnapshot`
- `ChanAnalyzer.calculate(bars: Sequence[BarData | ChanBar]) -> ChanSnapshot`
- `ChanAnalyzer.snapshot() -> ChanSnapshot`

**Step 3: Verify and commit**

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_analyzer.py -q
```

Commit:

```bash
git add vnpy/chan/analyzer.py tests/test_chan_analyzer.py
git commit -m "[Add] Orchestrate Chan analyzer"
```

### Task 10: CTA Strategy Shell

**Files:**
- Create: `vnpy_ctastrategy/strategies/chan_strategy.py`
- Modify: `vnpy_ctastrategy/strategies/__init__.py`
- Test: `tests/test_chan_strategy.py`

**Step 1: Write failing tests**

Cover:

- Strategy updates analyzer on bars.
- Confirmed second-buy sends one buy order.
- Confirmed third-buy sends one buy order.
- Existing long position prevents duplicate entry.
- Stop reference exits long position when violated.

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_strategy.py -q
```

Expected: FAIL because strategy does not exist.

**Step 2: Implement strategy**

Create `ChanStrategy(CtaTemplate)` with parameters mapped from `ChanConfig`.

Initial behavior:

- Long-only.
- Buy on confirmed second-buy or third-buy.
- Stop out below the active signal stop reference.
- Write concise logs with signal type, reason, and stop reference.

**Step 3: Verify and commit**

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_strategy.py -q
```

Commit:

```bash
git add vnpy_ctastrategy/strategies/chan_strategy.py vnpy_ctastrategy/strategies/__init__.py tests/test_chan_strategy.py
git commit -m "[Add] Add Chan CTA strategy"
```

### Task 11: Documentation And Final Verification

**Files:**
- Modify: `docs/community/app/cta_strategy.md`
- Modify: `docs/plans/2026-05-21-chan-strategy-design.md`

**Step 1: Document usage and limits**

Document:

- Strategy is a research prototype.
- It supports second-buy and third-buy only.
- It is long-only.
- Test cases are the source of truth for current rule behavior.

**Step 2: Run focused verification**

Run:

```bash
.venv/bin/python -m pytest tests/test_chan_objects.py tests/test_chan_cases.py tests/test_chan_normalizer.py tests/test_chan_fractal.py tests/test_chan_stroke.py tests/test_chan_segment.py tests/test_chan_pivot.py tests/test_chan_trend.py tests/test_chan_signal.py tests/test_chan_analyzer.py tests/test_chan_strategy.py -q
git diff --check
```

Expected: all tests pass and whitespace check passes.

**Step 3: Commit docs**

```bash
git add docs/community/app/cta_strategy.md docs/plans/2026-05-21-chan-strategy-design.md
git commit -m "[Add] Document Chan strategy prototype"
```

### Task 12: Optional Real Data Sanity Check

**Files:**
- No required file changes.

**Step 1: Run a small backtest or analyzer script**

Use existing CTA backtesting examples as reference. Feed a small historical dataset into `ChanAnalyzer` and print final structure counts.

Expected:

- Normalized bars are less than or equal to raw bars.
- Fractals, strokes, segments, and pivots are non-negative and deterministic.
- Signal reasons are readable.

**Step 2: Do not tune parameters yet**

Only record observations. Any parameter change must become a new test case before being accepted.

### Final Notes

- Treat `tests/chan_cases.py` as the permanent optimization case set.
- When a real-market chart exposes a wrong recognition result, add it as a reduced synthetic case before changing rules.
- Do not implement first-buy or divergence until second-buy and third-buy recognition is stable.
- Keep implementation deterministic; no pandas dependency is needed for the core analyzer.
