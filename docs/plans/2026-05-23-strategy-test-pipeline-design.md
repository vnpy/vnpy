# Strategy Test Pipeline Design

## Goal

Build a reusable strategy test pipeline that can take a trading idea from
research to DEMO automation with explicit evidence at each gate. The first
version uses the Chan strategy as the reference implementation and keeps the
pipeline small enough to run during normal development.

The pipeline must answer four questions for any strategy:

- What rule or runtime gate is being tested?
- What evidence proves the gate passed?
- What failed, and which layer owns the fix?
- Is the strategy allowed to move to the next delivery level?

## Current Reference Strategy

The Chan strategy is the first pipeline target.

Current status:

- Chan structure recognition exists for normalized bars, fractals, strokes,
  segments, pivots, trend, first-buy, second-buy, third-buy, and third-sell.
- CTA shell supports signal-only mode, long entry, stop order submission,
  duplicate-entry prevention, max position checks, and sell-signal clearing.
- OKX historical backtest runs through the existing CTA backtesting path.
- Runtime wiring can select `ChanStrategy` through auto-trading config.

Known gaps:

- First-sell and second-sell are not implemented.
- Real-history third-sell evidence is still weak; BTC 1h one-year data produced
  no natural third-sell signal.
- Runtime safety gates and health state need more Chan-specific assertions
  before unattended order-enabled DEMO runs.
- Case coverage needs more raw-market slices, not only synthetic structures.

## Delivery Levels

The pipeline classifies each strategy into one of five levels:

- Research prototype: rules and deterministic signal tests exist.
- Backtest candidate: strategy shell and reproducible backtests exist.
- Paper candidate: signal-only runtime can run on live/paper data with health
  evidence.
- DEMO order candidate: risk gates, notifications, and order lifecycle checks
  pass on simulated exchange orders.
- Live candidate: small-size deployment is allowed only after reviewed paper or
  DEMO evidence.

The pipeline should report the current level and the first failing gate. It
must not label a strategy production-ready only because tests pass or a process
starts.

## Pipeline Gates

### Gate 1: Idea Spec

Purpose:

- Convert a trading idea into explicit, reviewable rules.

Required evidence:

- Entry rules.
- Exit rules.
- Invalidation rules.
- Sizing rules.
- Market regimes where the strategy is disabled.
- Assumptions that are not yet implemented.

Chan first version:

- Keep the existing Chan design documents as the source of truth.
- Add future first-sell and second-sell rules before implementation.

### Gate 2: Signal Cases

Purpose:

- Prove that subjective chart interpretation has deterministic cases.

Required evidence:

- Positive cases.
- Rejected lookalike cases.
- Boundary/tolerance cases.
- Duplicate signal cases.
- Raw-bar end-to-end cases.

Chan first version:

- Continue using `tests/chan_cases.py` and `tests/test_chan_*.py`.
- Keep synthetic cases for structure primitives.
- Add raw-market cases for obvious buy/sell points when real examples are
  identified.
- Mirror buy-point work with sell-point cases, especially third-buy and
  third-sell.

### Gate 3: Strategy Shell

Purpose:

- Prove that signal objects create controlled strategy behavior.

Required evidence:

- Signal-only mode logs signals and submits no orders.
- Entry orders are submitted once per logical signal.
- Different confirmed signals are not accidentally de-duplicated.
- Protective stops are submitted after fills.
- Stop exits and reverse structural exits do not repeat while waiting for fill.
- Max position and unsafe size checks block orders.

Chan first version:

- Use `tests/test_chan_strategy.py` as the strategy-shell gate.
- Treat buy/sell signal objects as inputs and keep this gate independent from
  low-level structure recognition.

### Gate 4: Backtest

Purpose:

- Prove that the strategy can run through reproducible historical data and
  produce a comparable report.

Required evidence:

- Strategy class and config.
- Symbol, exchange, interval, start, end, and bar count.
- Signal counts by type.
- Order count and trade count.
- Total return, max drawdown, Sharpe ratio, and final capital.
- Whether an open position remains at the end.
- No-signal or no-sell results must be reported, not hidden.

Chan first version:

- Use BTCUSDT_SWAP_OKX 1h for the initial canonical backtest.
- Keep a 365-day window for regression comparison.
- Include signal diagnostics in addition to the CTA backtest summary.

### Gate 5: Runtime Safety

Purpose:

- Prevent order-enabled automation from starting without the minimum runtime
  evidence and risk controls.

Required evidence:

- Runtime mode: signal-only, DEMO order mode, or live mode.
- Exchange server mode, with OKX first runs expected to use DEMO.
- `trade_enabled` is explicit.
- Max position is configured.
- Max order value is configured.
- Daily loss or drawdown cap is configured before order-enabled runs.
- Health state exposes latest tick, latest bar or strategy update, latest
  signal, latest error, strategy name/class, position, and risk snapshot.
- Telegram or equivalent notification path is configured or explicitly disabled
  with a safe reason.

Chan first version:

- Extend existing OKX auto-trading tests and health checks.
- Reject unsafe order-enabled Chan configs before startup.
- Keep the example config signal-only by default.

### Gate 6: Paper And DEMO Review

Purpose:

- Validate the live-data path and order lifecycle before live trading.

Required evidence:

- Signal-only session report.
- DEMO order session report before live trading.
- Logs for signals, orders, fills, cancels, stops, risk blocks, and errors.
- Health snapshots during the run.
- Telegram messages or notification records.
- Manual review decision: stay, promote, or roll back.

Chan first version:

- Run signal-only first.
- Only enable tiny-size DEMO orders after health and risk gates pass.
- Treat the first DEMO order run as flow validation, not strategy performance
  validation.

## Command Shape

The first implementation should expose one small acceptance command:

```bash
.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate unit
.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate strategy
.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate backtest
.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate runtime
.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate all
```

Expected behavior:

- Print the gate being run.
- Print the exact commands or checks used.
- Return non-zero on failure.
- Print a compact summary with evidence fields.
- Avoid contacting external systems unless the gate explicitly requires it.

The first version should not implement a plugin system. A small internal
registry is enough:

- `chan.unit`: Chan structure and signal pytest files.
- `chan.strategy`: Chan CTA shell pytest file.
- `chan.backtest`: configured CTA backtest plus signal diagnostics.
- `chan.runtime`: auto-trading wiring, health, risk, Telegram-related unit
  tests.

## Artifacts

Initial artifacts:

- `docs/strategy_testing_pipeline.md`: durable user-facing checklist and gate
  definitions.
- `tools/strategy_acceptance.py`: local acceptance runner.
- `tests/test_strategy_acceptance.py`: runner behavior tests.
- Existing Chan test files remain the source of case and strategy-shell
  evidence.

Optional later artifacts:

- `docs/strategy/<name>/acceptance.md` per strategy.
- Machine-readable JSON reports.
- Chart snapshots for raw-market signal review.
- Historical case extraction helpers.

## Error Handling

The runner should distinguish:

- missing strategy name;
- unknown gate;
- pytest failure;
- missing historical data;
- backtest execution failure;
- unsafe runtime config;
- external dependency skipped.

Failures should include the command, exit code, and the shortest useful output
tail. The report should say which gate failed rather than dumping a long log
first.

## Testing Strategy

Test the pipeline itself before relying on it:

- Unit test the gate registry.
- Unit test unknown strategy and unknown gate failures.
- Unit test command execution summarization with a fake command runner.
- Unit test that `--gate all` runs gates in the intended order.
- Keep external or network-dependent checks out of default tests.

Then use the pipeline to run existing strategy checks:

```bash
.venv/bin/python -m pytest tests/test_strategy_acceptance.py -q
.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate all
```

## Non-Goals For The First Version

- No generic strategy discovery across the entire repo.
- No parameter optimization.
- No profit-based pass/fail threshold.
- No live exchange order execution.
- No dashboard or UI.
- No mandatory external smoke tests in the default local gate.

## Rollout Plan

1. Add the durable pipeline checklist document.
2. Add the acceptance runner with unit, strategy, runtime, and backtest gates
   for Chan.
3. Add runner tests.
4. Run the acceptance runner locally and record the Chan baseline.
5. Update the strategy-production skill if the implementation reveals reusable
   testing or readiness rules.

