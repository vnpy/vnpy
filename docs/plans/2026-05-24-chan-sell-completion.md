# Chan Sell Completion Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Complete Chan first-sell and second-sell recognition, then verify the long-only Chan strategy can clear positions from structural sell points.

**Architecture:** Keep signal recognition pure in `vnpy/chan/signal.py` and keep execution in `vnpy_ctastrategy/strategies/chan_strategy.py`. First-sell and second-sell are implemented as mirrored counterparts of the existing first-buy and second-buy rules, so strategy shell behavior can continue to consume any `SellSignal`.

**Tech Stack:** Python 3.12, pytest, vn.py CTA strategy shell, existing Chan analyzer objects.

---

### Task 1: Refactor AGENTS.md To Index Style

**Files:**
- Modify: `AGENTS.md`

**Steps:**
1. Replace the long Chan acceptance notes with an index linking to durable docs.
2. Keep only quick acceptance commands and current operational stance.
3. Run `git diff --check -- AGENTS.md`.

### Task 2: Add First-Sell Signal Cases

**Files:**
- Modify: `tests/test_chan_signal.py`
- Modify: `vnpy/chan/signal.py`

**Steps:**
1. Write failing tests for first-sell confirmation and no-divergence rejection.
2. Verify the tests fail because first-sell is not emitted.
3. Implement `_detect_first_sell()` as a mirror of `_detect_first_buy()`:
   - segment pattern: up, down, higher up, confirm down;
   - higher up breaks the prior high;
   - confirm down breaks the prior pullback low;
   - higher up has weaker `change_per_stroke` than the first up segment.
4. Add first-sell to `detect_sell_signals()` before third-sell.
5. Run the focused signal tests.

### Task 3: Add Second-Sell Signal Cases

**Files:**
- Modify: `tests/test_chan_signal.py`
- Modify: `vnpy/chan/signal.py`

**Steps:**
1. Write failing tests for second-sell confirmation and high-break rejection.
2. Verify the tests fail because second-sell is not emitted.
3. Implement `_detect_second_sell()` as a mirror of `_detect_second_buy()`:
   - segment pattern: up, down, rebound up, confirm down;
   - rebound high holds at or below the prior up high plus tolerance;
   - confirm down breaks the prior down low;
   - reject the four-segment pattern if it is fully inside the latest pivot.
4. Add duplicate-confirmation suppression in `detect_sell_signals()`.
5. Run the focused signal tests.

### Task 4: Verify Strategy Shell Exits All Sell Types

**Files:**
- Modify: `tests/test_chan_strategy.py`

**Steps:**
1. Parametrize the existing sell-signal exit test across first/second/third sell.
2. Run `pytest tests/test_chan_strategy.py -q`.

### Task 5: Run Acceptance Gates

**Files:**
- Modify if needed: `docs/strategy_testing_pipeline.md`
- Modify if needed: `AGENTS.md`

**Steps:**
1. Run focused pytest:
   ```bash
   /Users/miaoyuhan/Project/vnpy/.venv/bin/python -m pytest \
     tests/test_chan_signal.py tests/test_chan_strategy.py tests/test_chan_analyzer.py \
     tests/test_strategy_acceptance.py tests/test_position_sizing.py \
     tests/test_auto_trading_wiring.py -q
   ```
2. Run Chan acceptance:
   ```bash
   /Users/miaoyuhan/Project/vnpy/.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate all
   ```
3. Run DoubleMA acceptance:
   ```bash
   /Users/miaoyuhan/Project/vnpy/.venv/bin/python tools/strategy_acceptance.py --strategy double_ma --gate all
   ```
4. Run `git diff --check`.
5. Report exact pass/fail results and any changed backtest signal counts.
