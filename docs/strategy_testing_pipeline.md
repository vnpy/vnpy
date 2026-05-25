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
- historical warmup feeds signal state without submitting orders
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
- initialization history window, when the live strategy depends on bar-derived
  state

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
- risk per trade: `0.10`
- ATR multiplier: `1.0`
- max position: `0`
- max position ratio: `0.5`
- max order value: `5000`
- runtime initialization history: `runtime.init_days=3`, injected into
  `ChanStrategy.init_days` for live automation only
- backtest range: `2025-05-24` to `2026-05-24`
- bar count: `8708`
- signal counts: `first_buy=357`, `second_buy=802`, `third_buy=24`,
  `first_sell=435`, `second_sell=561`, `third_sell=10`
- order count: `5`
- trade count: `5`
- total return: about `0.20%`
- max drawdown: about `-3.71%`
- final position: approximately `0.001`
- debugging note: third-buy/third-sell require the nearest pivot completed
  before the leave segment; if `pivots[-1]` is an active pivot that includes the
  leave segment, the third-point signal is masked. Third-point signals also
  take priority over second-point signals when both share the same confirmation
  segment.

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
- bar count: `986`
- order count: `163`
- trade count: `157`
- total return: about `-0.00%`
- max drawdown: about `-0.00%`
- final position: `-1.0`

Additional Chan cross-symbol probe:

- symbol: `DOGEUSDT_SWAP_OKX.GLOBAL`
- interval: `1h`
- backtest range: `2025-05-24` to `2026-05-24`
- bar count: `2318`
- risk per trade: `0.10`
- signal counts: `first_buy=95`, `second_buy=170`, `first_sell=58`,
  `second_sell=285`
- order count: `20`
- trade count: `20`
- total return: about `-0.00003%`
- max drawdown: about `-0.00003%`
- final position: `0`
- note: this local DOGE window did not naturally trigger third-buy or
  third-sell, while the BTC acceptance window did.

Additional Chan 15m/30d position-ratio probe:

- config: `risk_per_trade=0.10`, `max_position=0`, `max_position_ratio=0.5`,
  `max_order_value=5000`
- BTC 15m: `2802` bars, `3` trades, max notional about `4948`, total return
  about `0.84%`, max drawdown about `-1.17%`, final position approximately `0`
- DOGE 15m: `2802` bars, `3` trades, max notional about `5000`, total return
  about `4.84%`, max drawdown about `-1.86%`, final position approximately
  `0.001`
- lesson: unit-based `max_position` is not cross-symbol comparable. Low-price
  symbols such as DOGE need notional caps through `max_position_ratio` or
  `max_position_value`.

Known improvement:

- The acceptance backtest currently derives the end datetime at runtime through
  the strategy config path. Future baselines should pin the end datetime to
  remove small drift when newer historical bars are added.
