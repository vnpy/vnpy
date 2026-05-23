# Position Sizing Infra Design

## Goal

Build a reusable position-sizing infra layer so strategies can express target
exposure or target risk while the system converts that intent into absolute
order volume for backtesting, paper trading, DEMO trading, and future live
trading.

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
`1 contract`. It should express target exposure or target trade risk, and the
system should calculate the executable quantity.

Fixed notional exposure is also insufficient for higher-quality research. A
5% notional BTC position and a 5% notional DOGE position can have very different
loss distributions. For strategies with a structural stop, the better default is
risk-based sizing: every trade risks a configured percentage of account equity
if the stop is hit.

## Core Principle

Separate three responsibilities:

- Strategy: produce signal intent, target exposure, or target risk.
- Sizing infra: convert target exposure into target volume and order volume.
- Execution shell: route the resulting order through CTA/backtest/live APIs and
  risk gates.

This keeps signal logic pure and makes sizing reusable across strategies.

## Sizing Modes

The first infra version supports three modes:

- `fixed`: legacy absolute volume, used for old strategies and old configs.
- `target_ratio`: target position notional as a fraction of equity.
- `risk_per_trade`: target trade risk as a fraction of equity.

`risk_per_trade` should be preferred for strategies with explicit stop prices,
including Chan buy points.

## Request Model

Introduce a generic sizing request:

```python
@dataclass(frozen=True)
class PositionSizingRequest:
    mode: str
    target_ratio: float
    risk_per_trade: float
    price: float
    current_volume: float
    equity: float
    fixed_volume: float = 0
    stop_price: float = 0
    atr: float = 0
    atr_multiplier: float = 1
    contract_size: float = 1
    min_volume: float = 0
    volume_step: float = 0
    max_position: float = 0
    max_order_value: float = 0
```

Return a sizing result:

```python
@dataclass(frozen=True)
class PositionSizingResult:
    target_volume: float
    order_volume: float
    order_value: float
    unit_risk: float
    risk_amount: float
    clipped: bool
    reason: str
```

Interpretation:

- `target_ratio > 0`: target long exposure in `target_ratio` mode.
- `target_ratio == 0`: flat in `target_ratio` mode.
- `target_ratio < 0`: target short exposure in `target_ratio` mode.
- `risk_per_trade`: max account risk per trade in `risk_per_trade` mode.
- `stop_price`: preferred unit-risk source when available.
- `atr * atr_multiplier`: fallback unit-risk source when no stop price exists.
- `equity` is backtest capital in backtests and account equity or selected
  account currency equity in live/paper runtime.
- `contract_size` converts one contract into notional exposure.

Target-ratio formula:

```text
target_notional = equity * target_ratio
raw_target_volume = target_notional / (price * contract_size)
target_volume = apply max_position, min_volume, and volume_step
order_volume = target_volume - current_volume
order_value = abs(order_volume * price * contract_size)
```

Risk-per-trade formula:

```text
risk_amount = equity * risk_per_trade
if stop_price is available:
    unit_risk = abs(price - stop_price) * contract_size
else:
    unit_risk = atr * atr_multiplier * contract_size
raw_order_volume = risk_amount / unit_risk
target_volume = current_volume + signed(raw_order_volume)
```

For `risk_per_trade`, the signal direction supplies the sign. A long buy signal
uses positive volume, a short signal uses negative volume, and a clear/flat
signal should use `target_ratio = 0` or a dedicated flat intent.

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

New strategies should prefer target exposure or target risk over fixed absolute
size.

For Chan:

- buy signal sizing mode: `risk_per_trade`;
- risk budget: `risk_per_trade = 0.01` by default for research;
- unit risk: `abs(entry_price - signal.stop_price)`;
- ATR fallback: use `atr * atr_multiplier` only when no structural stop exists;
- sell/clear signal target: flat;
- signal details should record target risk, stop reference, and sizing result.

Example Chan signal state:

```python
latest_chan_signal = {
    "type": "second_buy",
    "sizing_mode": "risk_per_trade",
    "risk_per_trade": 0.01,
    "stop_price": 96500.0,
    "sizing": {
        "target_volume": 0.028,
        "order_volume": 0.028,
        "order_value": 2800.0,
        "unit_risk": 3500.0,
        "risk_amount": 100.0,
        "clipped": False,
        "reason": "ok",
    },
}
```

Existing fixed-size strategies remain valid. Migration should be opt-in:

- `sizing_mode = "fixed"` keeps legacy behavior.
- `sizing_mode = "target_ratio"` uses the new infra.
- `sizing_mode = "risk_per_trade"` uses stop distance or ATR-normalized risk.

## Backtest Behavior

Backtests should use the same sizing helper as runtime:

- equity source: configured backtest capital;
- price source: current bar close or configured execution price;
- current volume: current strategy position;
- contract size: backtesting engine size or explicit strategy setting;
- stop price: signal stop reference when available;
- ATR: strategy-provided ATR when no stop price exists;
- risk caps: config values such as `max_position` and `max_order_value`.

For acceptance backtests, the report should include:

- sizing mode;
- target ratio;
- risk per trade;
- stop price or ATR unit-risk source;
- unit risk;
- risk amount;
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
- startup validation must reject order-enabled target-ratio or risk-per-trade
  strategies without max position and max order value caps;
- risk-per-trade mode must also require `risk_per_trade > 0` and either a
  strategy stop reference or ATR source.

Runtime health should expose the latest sizing decision:

- target ratio;
- risk per trade;
- stop price or ATR source;
- unit risk;
- risk amount;
- target volume;
- order volume;
- order value;
- clipped flag;
- reason.

## Edge Cases

The sizing helper must handle:

- zero or negative price: reject with zero order volume;
- zero equity: reject with zero order volume;
- risk-per-trade without positive stop distance or ATR: reject with zero order
  volume;
- stop price equal to entry price: reject with zero order volume;
- ATR equal to zero: reject with zero order volume unless stop distance is
  available;
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
- risk-per-trade from stop distance;
- risk-per-trade from ATR fallback;
- risk-per-trade rejection when both stop and ATR are missing.

Chan strategy tests:

- buy signal in `risk_per_trade` mode submits volume calculated from capital,
  entry price, and signal stop price;
- buy signal in `target_ratio` mode remains available for target-exposure
  research;
- sell signal clears to target ratio `0`;
- fixed-size mode still behaves as before;
- signal-only mode records target ratio and no order;
- max position and order-value caps are reflected in sizing result.

Acceptance tests:

- Chan acceptance backtest uses risk-per-trade sizing.
- DoubleMA acceptance still passes without migrating to target-ratio sizing.
- Acceptance report includes sizing mode and final position.

## Configuration

Suggested Chan backtest config:

```json
{
  "sizing_mode": "risk_per_trade",
  "risk_per_trade": 0.01,
  "atr_window": 14,
  "atr_multiplier": 1.0,
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
- No ATR implementation inside the generic helper; ATR values should be
  supplied by the strategy or shell.
- No automatic migration of every existing CTA example strategy.
- No live order execution changes outside the strategy shell using this helper.

## Rollout

1. Add `position_sizing` infra and unit tests for fixed, target-ratio, and
   risk-per-trade modes.
2. Add risk-per-trade mode to `ChanStrategy` while preserving fixed-size and
   target-ratio compatibility.
3. Update Chan config to use risk-per-trade sizing for acceptance backtests.
4. Update acceptance report to include sizing fields.
5. Re-run `chan` and `double_ma` acceptance gates.
6. Update strategy-production skill if the implementation reveals reusable
   sizing gates or pitfalls.
