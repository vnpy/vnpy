# Chan Auto-Trading Readiness Plan

## Current Status

The Chan strategy is a tested research prototype with a CTA shell and real OKX-history backtests. It is not production-ready for unattended live trading yet.

Completed:

- Chan structure analyzer and buy signals.
- CTA strategy shell.
- BacktestingEngine integration.
- OKX auto-trading runtime can select `ChanStrategy` by config.
- `ChanStrategy` supports `trade_enabled=false` signal-only mode.
- Basic position cap prevents accidental oversized fixed-size entries.

## Production Readiness Gates

### Gate 1: Signal Explainability

Every live signal must persist:

- signal type
- structure counts
- candidate and confirmation ids
- pivot id for third-buy
- stop reference
- exact reason
- current bar datetime and close

Verification:

- Unit tests assert signal detail fields are written.
- Live state file exposes latest Chan signal.

### Gate 2: Safe Runtime Mode

The first live deployment must run with:

- OKX `DEMO`
- `trade_enabled=false`
- Telegram notification enabled
- no order submission

Verification:

- Runtime config can select `ChanStrategy`.
- Strategy logs signal-only mode and submits no order.
- Health output shows strategy class/name and latest signal.

### Gate 3: Risk Controls

Before `trade_enabled=true`, require:

- explicit max position
- configured fixed size or sizing mode
- RiskEngine enabled
- max order value cap
- max daily loss cap
- no stale contract or tick

Verification:

- Unit tests reject unsafe config.
- Health check fails if strategy is live-enabled without risk caps.

### Gate 4: End-To-End Signal Cases

Add raw-bar cases that naturally produce:

- second-buy from bars
- third-buy from bars
- rejected range fake second-buy
- rejected third-buy pullback into pivot

Verification:

- Analyzer tests assert exact signal type and stop reference from raw bars.

### Gate 5: Paper Run Review

Run at least one full session in signal-only mode and review:

- signal chart
- strategy logs
- latest state
- no unexpected orders
- Telegram messages

Only after this gate should small-size DEMO trading be enabled.

## Known Risks

- Current buy signals use segment-level structure; stroke/bar-level confirmation is not implemented.
- `confirm_on_close` is still not implemented because `Segment` has no close.
- First-buy and divergence are intentionally excluded.
- Real backtests produced very few signals, so performance evidence is weak.
- CTA strategy fixed-size defaults are not suitable for real-money deployment without config review.

## Immediate Next Tasks

1. Persist latest Chan signal into runtime state.
2. Add `ChanStrategy` config example with `trade_enabled=false`.
3. Add startup validation that rejects live-enabled Chan config unless risk caps are present.
4. Add raw-bar end-to-end second-buy and third-buy cases.
5. Add a chart/export tool for signal review before live trading.
