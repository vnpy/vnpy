# Chan Strategy Design

## Goal

Build a Chan theory research and CTA strategy prototype that can identify points, lines, areas, trend state, and buy points from bar data. The first version must prioritize deterministic structure recognition and reusable test cases over trading performance.

## Scope

The first version includes:

- K-line inclusion normalization.
- Fractal point recognition.
- Stroke recognition with configurable strictness.
- Segment recognition.
- Pivot/center recognition.
- Trend state recognition.
- Second-buy and third-buy candidate/confirmed signals.
- A CTA strategy shell that consumes the analyzer and places long-only orders.
- A reusable fixture set that becomes the baseline case library for later optimization.

The first version excludes:

- First-buy signals.
- MACD or volume divergence.
- Multi-level nesting.
- UI drawing.
- Parameter optimization.
- Short-side trading.

## Concept Mapping

Chan theory is represented as four layers:

- Point: normalized bar endpoints, top/bottom fractals, stroke endpoints, segment endpoints, and buy-point candidates.
- Line: strokes and segments that describe directional movement.
- Area: pivots/centers built from overlapping segment ranges.
- Trend: up, down, range, or unknown state derived from segment direction and pivot relationships.

Buy points are not standalone K-line events. They are structure events created by a trend context, a pivot relationship, and a confirmation movement.

## Buy Point Rules

Second-buy:

- A down structure produces a low point.
- A following upward stroke or segment appears.
- The pullback does not break the previous low within the configured tolerance.
- A renewed upward confirmation stroke appears.
- The signal is confirmed on the confirmation stroke endpoint.

Third-buy:

- A valid pivot exists.
- Price leaves the pivot upward.
- A pullback low stays above the pivot upper bound within the configured tolerance.
- A renewed upward confirmation stroke appears.
- The signal is confirmed on the confirmation stroke endpoint.

Both signals must include enough context for review:

- Signal type.
- Candidate index and confirmation index.
- Related fractal/stroke/segment ids.
- Related pivot id for third-buy.
- Stop reference price.
- Human-readable reason.

## Architecture

Create a reusable core package under `vnpy/chan/` and a CTA example strategy under `vnpy_ctastrategy/strategies/`.

Core package:

- `vnpy/chan/object.py`: dataclasses and enums for bars, fractals, strokes, segments, pivots, trends, and signals.
- `vnpy/chan/config.py`: analyzer configuration.
- `vnpy/chan/analyzer.py`: public orchestration API.
- `vnpy/chan/normalizer.py`: inclusion handling.
- `vnpy/chan/fractal.py`: fractal recognition.
- `vnpy/chan/stroke.py`: stroke recognition.
- `vnpy/chan/segment.py`: segment recognition.
- `vnpy/chan/pivot.py`: pivot recognition.
- `vnpy/chan/trend.py`: trend classification.
- `vnpy/chan/signal.py`: buy-point candidate and confirmation recognition.

CTA strategy:

- `vnpy_ctastrategy/strategies/chan_strategy.py`: long-only strategy shell.
- It updates `ChanAnalyzer` on every bar.
- It buys on confirmed second-buy or third-buy signals.
- It uses the signal stop reference for protective exits.

## Data Flow

1. CTA or test code passes bars into `ChanAnalyzer.update_bar()`.
2. Analyzer converts `BarData` into an internal immutable bar snapshot.
3. Inclusion normalizer updates the normalized bar sequence.
4. Fractal detector updates confirmed fractals.
5. Stroke detector links alternating fractals into strokes.
6. Segment detector groups strokes into segments.
7. Pivot detector identifies overlapping segment areas.
8. Trend classifier evaluates current trend state.
9. Signal detector updates second-buy and third-buy candidates and confirmations.
10. Analyzer returns a `ChanSnapshot` for tests, notebooks, and CTA strategy logic.

## Configuration

Initial parameters:

- `min_stroke_gap`: minimum normalized-bar distance between opposite fractals.
- `strict_stroke`: require stricter high/low relationship for strokes.
- `pivot_min_segments`: minimum segment count used to form a pivot.
- `pivot_tolerance`: price tolerance for pivot boundary checks.
- `third_buy_pullback_tolerance`: allowed tolerance when checking whether pullback re-enters a pivot.
- `second_buy_low_tolerance`: allowed tolerance for pullback versus prior low.
- `confirm_on_close`: whether confirmation requires close beyond a reference level.
- `max_bars`: optional rolling window cap.

Defaults should be conservative and deterministic.

## Test Case Library

Tests must be written as reusable cases, not one-off assertions. Store synthetic cases in `tests/chan_cases.py` or fixtures in `tests/test_chan_*.py`.

Required case groups:

- Inclusion cases: up-inclusion, down-inclusion, nested inclusion, and no-inclusion.
- Fractal cases: top fractal, bottom fractal, invalid same-direction fractal, edge bars ignored.
- Stroke cases: valid strict stroke, rejected short-gap stroke, replacement by more extreme same-side fractal.
- Segment cases: basic three-stroke segment and segment direction reversal.
- Pivot cases: valid overlap area, no-overlap rejection, pivot extension.
- Trend cases: up trend, down trend, range, unknown.
- Buy-point cases: valid second-buy, invalid second-buy because prior low breaks, valid third-buy, invalid third-buy because pullback re-enters pivot.
- CTA shell cases: confirmed signal sends buy order, no duplicate order for same signal, stop reference exits long position.

Each case should include expected structure counts and important endpoint prices. These fixtures become the regression suite for future rule refinement.

## Verification

Focused verification:

```bash
.venv/bin/python -m pytest tests/test_chan_normalizer.py tests/test_chan_fractal.py tests/test_chan_stroke.py tests/test_chan_segment.py tests/test_chan_pivot.py tests/test_chan_trend_signal.py tests/test_chan_strategy.py -q
```

Repository checks after implementation:

```bash
.venv/bin/python -m pytest tests/test_chan_normalizer.py tests/test_chan_fractal.py tests/test_chan_stroke.py tests/test_chan_segment.py tests/test_chan_pivot.py tests/test_chan_trend_signal.py tests/test_chan_strategy.py -q
git diff --check
```
