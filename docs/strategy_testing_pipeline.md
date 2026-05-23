# Strategy Testing Pipeline

## Purpose

Use this checklist to move a strategy from idea to paper, DEMO, or live
automation without confusing "it runs" with "it is ready."

## Delivery Levels

- Research prototype
- Backtest candidate
- Paper candidate
- DEMO order candidate
- Live candidate

## Gates

### 1. Idea Spec

Required evidence:

- entry rules
- exit rules
- invalidation rules
- sizing rules
- excluded regimes
- known unimplemented assumptions

### 2. Signal Cases

Required evidence:

- positive cases
- rejected lookalike cases
- boundary cases
- duplicate signal cases
- raw-bar end-to-end cases

### 3. Strategy Shell

Required evidence:

- signal-only mode
- one entry per logical signal
- no accidental de-duplication of different signals
- protective stops
- reverse exits
- max position checks

### 4. Backtest

Required evidence:

- strategy class/config
- symbol, interval, date range, bar count
- signal counts
- order/trade counts
- return, drawdown, Sharpe
- open-position status

### 5. Runtime Safety

Required evidence:

- runtime mode
- exchange server mode
- explicit trade-enabled flag
- risk caps
- health fields
- notification state

### 6. Paper And DEMO Review

Required evidence:

- signal-only run report
- DEMO order run report
- logs and health snapshots
- manual review decision

## Local Acceptance Command

Use:

```bash
.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate all
```

## Promotion Rule

A strategy can move to the next delivery level only when the current gate
passes and remaining risks are explicitly reported.

## Current Acceptance Baseline

As of 2026-05-24, the local acceptance command was verified with:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate all
/Users/miaoyuhan/Project/vnpy/.venv/bin/python tools/strategy_acceptance.py --strategy double_ma --gate all
```

Chan baseline:

- unit gate: passed
- strategy gate: passed
- runtime gate: passed
- backtest gate: passed
- canonical config: `config/trading_config_chan_signal_only.example.json`
- canonical symbol: `BTCUSDT_SWAP_OKX.GLOBAL`
- canonical interval: `1h`
- sizing mode: `risk_per_trade`
- risk per trade: `0.01`
- ATR multiplier: `1.0`
- max position: `0.05`
- max order value: `1000`
- backtest range: `2025-05-24` to `2026-05-24`
- bar count: `8725`
- signal counts: `first_buy=357`, `second_buy=826`, sells empty
- order count: `7`
- trade count: `7`
- total return: about `-1.47%`
- max drawdown: about `-3.83%`
- final position: `0.014`
- known gap: third-sell has synthetic coverage but no natural BTC 1h one-year
  trigger has been confirmed yet

DoubleMA baseline:

- unit gate: passed
- strategy gate: passed
- runtime gate: passed
- backtest gate: passed
- canonical config: `config/trading_config.json`
- canonical symbol: `DOGEUSDT_SWAP_OKX.GLOBAL`
- canonical interval: `1h`
- sizing mode: `fixed`
- backtest range: `2026-02-23` to `2026-05-24`
- bar count: `1003`
- order count: `161`
- trade count: `155`
- total return: about `-0.00%`
- max drawdown: about `-0.00%`
- final position: `-1.0`

Known improvement:

- The acceptance backtest currently derives the end datetime at runtime through
  the strategy config path. Future baselines should pin the end datetime to
  remove small drift when newer historical bars are added.
