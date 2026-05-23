# Target Position Sizing Design

## Goal

Build a reusable position-sizing infra layer so strategies can express target
exposure as a ratio while the system converts that target into absolute order
volume for backtesting, paper trading, DEMO trading, and future live trading.

The first integration target is `ChanStrategy`, but the infra must be generic
enough for future strategies. Existing fixed-size strategies should continue to
work unchanged.

## Problem

Strategy code currently mixes signal recognition and absolute trade size. For
Chan, a fixed `0.01` BTC size and `0.01` max position make historical results
hard to interpret:

- many signals can produce few trades because the strategy is already holding;
- performance depends heavily on a manually chosen absolute size;
- BTC, DOGE, and other symbols need different absolute sizes;
- sizing logic can drift between backtest and auto-trading runtime.

The strategy should not decide whether to buy `0.01 BTC`, `40 DOGE`, or
`1 contract`. It should express target exposure, and the system should calculate
the executable quantity.

## Core Principle

Separate three responsibilities:

- Strategy: produce signal intent and target exposure.
- Sizing infra: convert target exposure into target volume and order volume.
- Execution shell: route the resulting order through CTA/backtest/live APIs and
  risk gates.

This keeps signal logic pure and makes sizing reusable across strategies.

## Target Model

Introduce a generic target-position request:

```python
@dataclass(frozen=True)
class TargetPositionRequest:
    target_ratio: float
    price: float
    current_volume: float
    equity: float
    contract_size: float = 1
    min_volume: float = 0
    volume_step: float = 0
    max_position: float = 0
    max_order_value: float = 0
```

Return a sizing result:

```python
@dataclass(frozen=True)
class TargetPositionResult:
    target_volume: float
    order_volume: float
    order_value: float
    clipped: bool
    reason: str
```

Interpretation:

- `target_ratio > 0`: target long exposure.
- `target_ratio == 0`: flat.
- `target_ratio < 0`: target short exposure.
- `equity` is backtest capital in backtests and account equity or selected
  account currency equity in live/paper runtime.
- `contract_size` converts one contract into notional exposure.

Formula:

```text
target_notional = equity * target_ratio
raw_target_volume = target_notional / (price * contract_size)
target_volume = apply max_position, min_volume, and volume_step
order_volume = target_volume - current_volume
order_value = abs(order_volume * price * contract_size)
```

`max_order_value` clips the order delta, not the target itself. This lets the
system move toward a target in smaller increments when risk caps require it.

## Proposed Location

Add infra under:

```text
vnpy/trader/position_sizing.py
```

Reason:

- It is not Chan-specific.
- It should be available to CTA strategies, auto-trading runtime, and tests.
- It belongs near trader-level utility/risk concepts rather than inside one
  strategy package.

## Strategy Contract

New strategies should prefer target-position intent over fixed absolute size.

For Chan:

- buy signal target: `target_ratio = target_long_ratio`, for example `0.05`;
- sell/clear signal target: `target_ratio = 0`;
- stop still uses the signal's stop reference;
- signal details should record both target ratio and sizing result.

Example Chan signal state:

```python
latest_chan_signal = {
    "type": "second_buy",
    "target_ratio": 0.05,
    "sizing": {
        "target_volume": 0.0048,
        "order_volume": 0.0048,
        "order_value": 500.0,
        "clipped": False,
        "reason": "ok",
    },
}
```

Existing fixed-size strategies remain valid. Migration should be opt-in:

- `sizing_mode = "fixed"` keeps legacy behavior.
- `sizing_mode = "target_ratio"` uses the new infra.

## Backtest Behavior

Backtests should use the same sizing helper as runtime:

- equity source: configured backtest capital;
- price source: current bar close or configured execution price;
- current volume: current strategy position;
- contract size: backtesting engine size or explicit strategy setting;
- risk caps: config values such as `max_position` and `max_order_value`.

For acceptance backtests, the report should include:

- sizing mode;
- target ratio;
- target volume;
- order volume;
- whether sizing clipped;
- final position.

This prevents "trade count is low because size is capped" from being confused
with "signals did not appear."

## Runtime Behavior

Paper/DEMO/live runtime should use the same helper, but with live account data:

- equity source: selected base currency, usually USDT for OKX;
- available-equity mode can be added later, but total selected equity is enough
  for the first version;
- risk engine remains the final hard gate after sizing;
- startup validation must reject order-enabled target-ratio strategies without
  max position and max order value caps.

Runtime health should expose the latest sizing decision:

- target ratio;
- target volume;
- order volume;
- order value;
- clipped flag;
- reason.

## Edge Cases

The sizing helper must handle:

- zero or negative price: reject with zero order volume;
- zero equity: reject with zero order volume;
- target ratio outside allowed position caps: clip;
- min volume larger than requested volume: return zero order volume with reason;
- volume step rounding: round toward zero so the order never exceeds requested
  risk;
- max order value clipping: reduce only the order delta;
- flat target from long or short position: produce the closing delta;
- already-at-target position: return zero order volume.

## Testing Plan

Unit tests for `vnpy/trader/position_sizing.py`:

- long target from flat position;
- flat target from long position;
- short target from flat position;
- current position already at target;
- max position clipping;
- max order value clipping;
- min volume rejection;
- volume step rounding;
- invalid price/equity rejection.

Chan strategy tests:

- buy signal in `target_ratio` mode submits volume calculated from capital and
  price;
- sell signal clears to target ratio `0`;
- fixed-size mode still behaves as before;
- signal-only mode records target ratio and no order;
- max position and order-value caps are reflected in sizing result.

Acceptance tests:

- Chan acceptance backtest uses target-ratio sizing.
- DoubleMA acceptance still passes without migrating to target-ratio sizing.
- Acceptance report includes sizing mode and final position.

## Configuration

Suggested Chan backtest config:

```json
{
  "sizing_mode": "target_ratio",
  "target_long_ratio": 0.05,
  "capital": 10000,
  "max_position": 0.05,
  "min_volume": 0.001,
  "volume_step": 0.001,
  "max_order_value": 1000
}
```

Runtime config should stay conservative:

- default `trade_enabled=false` for first paper run;
- require explicit risk caps before `trade_enabled=true`;
- keep fixed-size compatibility for old strategies and old config files.

## Non-Goals For First Version

- No portfolio-level allocation across multiple symbols.
- No volatility targeting.
- No Kelly sizing.
- No margin-mode-specific leverage optimization.
- No automatic migration of every existing CTA example strategy.
- No live order execution changes outside the strategy shell using this helper.

## Rollout

1. Add `position_sizing` infra and unit tests.
2. Add target-ratio mode to `ChanStrategy` while preserving fixed-size mode.
3. Update Chan config to use target-ratio sizing for acceptance backtests.
4. Update acceptance report to include sizing fields.
5. Re-run `chan` and `double_ma` acceptance gates.
6. Update strategy-production skill if the implementation reveals reusable
   sizing gates or pitfalls.

