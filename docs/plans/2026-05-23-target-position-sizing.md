# Target Position Sizing Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Add reusable target-ratio position sizing infra and wire ChanStrategy to use it without breaking fixed-size strategies.

**Architecture:** Add a pure `vnpy/trader/position_sizing.py` helper that converts target exposure ratios into target volume and order deltas. Keep strategies responsible for signal intent, let the strategy shell call sizing infra, and preserve fixed-size mode for existing configs. Update Chan acceptance backtests to exercise target-ratio sizing while keeping DoubleMA fixed-size acceptance unchanged.

**Tech Stack:** Python 3.12, pytest, dataclasses, vn.py CTA strategies, existing BacktestingEngine acceptance runner.

---

### Task 1: Add Position Sizing Infra

**Files:**
- Create: `vnpy/trader/position_sizing.py`
- Create: `tests/test_position_sizing.py`

**Step 1: Write failing tests**

Create `tests/test_position_sizing.py`:

```python
from __future__ import annotations

from vnpy.trader.position_sizing import (
    TargetPositionRequest,
    calculate_target_position,
)


def test_calculate_long_target_from_flat() -> None:
    result = calculate_target_position(
        TargetPositionRequest(
            target_ratio=0.05,
            price=100_000,
            current_volume=0,
            equity=10_000,
            contract_size=1,
        )
    )

    assert result.target_volume == 0.005
    assert result.order_volume == 0.005
    assert result.order_value == 500
    assert result.clipped is False
    assert result.reason == "ok"


def test_calculate_flat_target_from_long() -> None:
    result = calculate_target_position(
        TargetPositionRequest(
            target_ratio=0,
            price=100_000,
            current_volume=0.005,
            equity=10_000,
        )
    )

    assert result.target_volume == 0
    assert result.order_volume == -0.005


def test_calculate_short_target_from_flat() -> None:
    result = calculate_target_position(
        TargetPositionRequest(
            target_ratio=-0.05,
            price=100_000,
            current_volume=0,
            equity=10_000,
        )
    )

    assert result.target_volume == -0.005
    assert result.order_volume == -0.005


def test_calculate_zero_when_already_at_target() -> None:
    result = calculate_target_position(
        TargetPositionRequest(
            target_ratio=0.05,
            price=100_000,
            current_volume=0.005,
            equity=10_000,
        )
    )

    assert result.order_volume == 0
    assert result.order_value == 0
    assert result.reason == "already at target"


def test_clips_target_by_max_position() -> None:
    result = calculate_target_position(
        TargetPositionRequest(
            target_ratio=0.20,
            price=100_000,
            current_volume=0,
            equity=10_000,
            max_position=0.01,
        )
    )

    assert result.target_volume == 0.01
    assert result.order_volume == 0.01
    assert result.clipped is True
    assert "max_position" in result.reason


def test_clips_order_by_max_order_value() -> None:
    result = calculate_target_position(
        TargetPositionRequest(
            target_ratio=0.20,
            price=100_000,
            current_volume=0,
            equity=10_000,
            max_order_value=500,
        )
    )

    assert result.target_volume == 0.02
    assert result.order_volume == 0.005
    assert result.order_value == 500
    assert result.clipped is True
    assert "max_order_value" in result.reason


def test_rejects_order_below_min_volume() -> None:
    result = calculate_target_position(
        TargetPositionRequest(
            target_ratio=0.001,
            price=100_000,
            current_volume=0,
            equity=10_000,
            min_volume=0.001,
        )
    )

    assert result.target_volume == 0
    assert result.order_volume == 0
    assert "min_volume" in result.reason


def test_rounds_volume_step_toward_zero() -> None:
    result = calculate_target_position(
        TargetPositionRequest(
            target_ratio=0.055,
            price=100_000,
            current_volume=0,
            equity=10_000,
            volume_step=0.001,
        )
    )

    assert result.target_volume == 0.005
    assert result.order_volume == 0.005


def test_rejects_invalid_price_or_equity() -> None:
    price_result = calculate_target_position(
        TargetPositionRequest(
            target_ratio=0.05,
            price=0,
            current_volume=0,
            equity=10_000,
        )
    )
    equity_result = calculate_target_position(
        TargetPositionRequest(
            target_ratio=0.05,
            price=100_000,
            current_volume=0,
            equity=0,
        )
    )

    assert price_result.order_volume == 0
    assert "price" in price_result.reason
    assert equity_result.order_volume == 0
    assert "equity" in equity_result.reason
```

**Step 2: Run tests to verify failure**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python -m pytest tests/test_position_sizing.py -q
```

Expected: FAIL because `vnpy.trader.position_sizing` does not exist.

**Step 3: Implement sizing helper**

Create `vnpy/trader/position_sizing.py`:

```python
from __future__ import annotations

from dataclasses import dataclass
from math import floor


@dataclass(frozen=True)
class TargetPositionRequest:
    """Inputs required to convert target exposure into order volume."""

    target_ratio: float
    price: float
    current_volume: float
    equity: float
    contract_size: float = 1
    min_volume: float = 0
    volume_step: float = 0
    max_position: float = 0
    max_order_value: float = 0


@dataclass(frozen=True)
class TargetPositionResult:
    """Calculated target and order volume."""

    target_volume: float
    order_volume: float
    order_value: float
    clipped: bool
    reason: str


def calculate_target_position(request: TargetPositionRequest) -> TargetPositionResult:
    """Convert target ratio into an executable order delta."""

    if request.price <= 0:
        return _zero("invalid price")
    if request.equity <= 0:
        return _zero("invalid equity")
    if request.contract_size <= 0:
        return _zero("invalid contract_size")

    notional = request.equity * request.target_ratio
    target_volume = notional / (request.price * request.contract_size)
    clipped = False
    reasons: list[str] = []

    if request.max_position > 0 and abs(target_volume) > request.max_position:
        target_volume = _copy_sign(request.max_position, target_volume)
        clipped = True
        reasons.append("max_position")

    target_volume = _round_toward_zero(target_volume, request.volume_step)
    order_volume = target_volume - request.current_volume
    order_volume = _round_toward_zero(order_volume, request.volume_step)

    if request.min_volume > 0 and 0 < abs(order_volume) < request.min_volume:
        return TargetPositionResult(0, 0, 0, True, "below min_volume")

    order_value = abs(order_volume * request.price * request.contract_size)
    if request.max_order_value > 0 and order_value > request.max_order_value:
        clipped_volume = request.max_order_value / (request.price * request.contract_size)
        order_volume = _copy_sign(clipped_volume, order_volume)
        order_volume = _round_toward_zero(order_volume, request.volume_step)
        order_value = abs(order_volume * request.price * request.contract_size)
        clipped = True
        reasons.append("max_order_value")

    if order_volume == 0:
        reason = "already at target" if target_volume == request.current_volume else "zero order"
    else:
        reason = ", ".join(reasons) if reasons else "ok"

    return TargetPositionResult(
        target_volume=target_volume,
        order_volume=order_volume,
        order_value=order_value,
        clipped=clipped,
        reason=reason,
    )


def _zero(reason: str) -> TargetPositionResult:
    return TargetPositionResult(0, 0, 0, False, reason)


def _copy_sign(value: float, signed: float) -> float:
    return value if signed >= 0 else -value


def _round_toward_zero(value: float, step: float) -> float:
    if step <= 0 or value == 0:
        return value
    rounded = floor(abs(value) / step) * step
    return _copy_sign(rounded, value)
```

**Step 4: Run tests**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python -m pytest tests/test_position_sizing.py -q
```

Expected: PASS.

**Step 5: Commit**

```bash
git add vnpy/trader/position_sizing.py tests/test_position_sizing.py
git commit -m "[Add] Calculate target position sizing"
```

### Task 2: Add Target-Ratio Mode To ChanStrategy

**Files:**
- Modify: `vnpy_ctastrategy/strategies/chan_strategy.py`
- Modify: `tests/test_chan_strategy.py`

**Step 1: Write failing Chan strategy tests**

Add tests to `tests/test_chan_strategy.py`:

```python
def test_chan_strategy_uses_target_ratio_sizing_for_buy() -> None:
    strategy, engine = _strategy(
        {
            "sizing_mode": "target_ratio",
            "target_long_ratio": 0.05,
            "capital": 10_000,
            "max_position": 0.05,
            "min_volume": 0.001,
            "volume_step": 0.001,
        }
    )
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 100_000))

    assert engine.orders == [(Direction.LONG, Offset.OPEN, 100_000, 0.005, False)]
    assert strategy.latest_chan_signal["target_ratio"] == 0.05
    assert strategy.latest_chan_signal["sizing"]["order_volume"] == 0.005


def test_chan_strategy_target_ratio_signal_only_records_sizing_without_order() -> None:
    strategy, engine = _strategy(
        {
            "trade_enabled": False,
            "sizing_mode": "target_ratio",
            "target_long_ratio": 0.05,
            "capital": 10_000,
            "volume_step": 0.001,
        }
    )
    strategy.analyzer = FakeAnalyzer([_snapshot(_signal())])

    strategy.on_bar(_bar(0, 100_000))

    assert engine.orders == []
    assert strategy.latest_chan_signal["sizing"]["order_volume"] == 0.005


def test_chan_strategy_target_ratio_sell_signal_clears_position() -> None:
    strategy, engine = _strategy({"sizing_mode": "target_ratio", "capital": 10_000})
    strategy.pos = 0.005
    strategy.active_stop_orderid = "STOP.1"
    strategy.analyzer = FakeAnalyzer([_sell_snapshot(_sell_signal())])

    strategy.on_bar(_bar(0, 100_000))

    assert engine.orders == [(Direction.SHORT, Offset.CLOSE, 100_000, 0.005, False)]
```

Keep existing fixed-size tests unchanged.

**Step 2: Run focused tests to verify failure**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python -m pytest tests/test_chan_strategy.py -q
```

Expected: FAIL because target-ratio mode is not implemented.

**Step 3: Implement target-ratio mode**

In `vnpy_ctastrategy/strategies/chan_strategy.py`:

- import `TargetPositionRequest` and `calculate_target_position`;
- add parameters:
  - `sizing_mode: str = "fixed"`
  - `target_long_ratio: float = 0.05`
  - `capital: float = 0`
  - `min_volume: float = 0`
  - `volume_step: float = 0`
  - `max_order_value: float = 0`
- include them in `parameters`;
- add helper `_calculate_order_volume(bar, target_ratio)`;
- for buy signal:
  - if `sizing_mode == "target_ratio"`, use sizing helper and order `sizing.order_volume` when positive;
  - else keep `fixed_size`;
- for sell signal:
  - if `sizing_mode == "target_ratio"`, calculate target ratio `0` and close the absolute negative order delta;
  - else keep current close-all behavior;
- record sizing result in `latest_chan_signal`.

Implementation sketch:

```python
def _calculate_target_sizing(self, bar: BarData, target_ratio: float):
    equity = self.capital or 0
    return calculate_target_position(
        TargetPositionRequest(
            target_ratio=target_ratio,
            price=bar.close_price,
            current_volume=self.pos,
            equity=equity,
            max_position=self.max_position,
            min_volume=self.min_volume,
            volume_step=self.volume_step,
            max_order_value=self.max_order_value,
        )
    )
```

Use `sizing.__dict__` or `dataclasses.asdict(sizing)` for signal state.

**Step 4: Run Chan strategy tests**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python -m pytest tests/test_chan_strategy.py -q
```

Expected: PASS.

**Step 5: Commit**

```bash
git add vnpy_ctastrategy/strategies/chan_strategy.py tests/test_chan_strategy.py
git commit -m "[Mod] Add target-ratio sizing to Chan strategy"
```

### Task 3: Update Chan Config And Safety Wiring

**Files:**
- Modify: `config/trading_config_chan_signal_only.example.json`
- Modify: `run_auto_trading.py`
- Modify: `tests/test_auto_trading_wiring.py`

**Step 1: Write failing tests for safety validation**

Add tests to `tests/test_auto_trading_wiring.py`:

```python
def test_validate_strategy_safety_rejects_live_target_ratio_without_order_cap() -> None:
    with pytest.raises(ValueError, match="max_order"):
        validate_strategy_safety(
            {
                "strategy": {
                    "class_name": "ChanStrategy",
                    "vt_symbol": "BTCUSDT_SWAP_OKX.GLOBAL",
                    "setting": {
                        "trade_enabled": True,
                        "sizing_mode": "target_ratio",
                        "target_long_ratio": 0.05,
                        "max_position": 0.05,
                    },
                },
                "risk": {
                    "enabled": True,
                    "max_daily_loss_pct": 0.01,
                },
            }
        )
```

Update existing label/safety tests that assume only `fixed_size`.

**Step 2: Run focused tests to verify failure**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python -m pytest tests/test_auto_trading_wiring.py -q
```

Expected: FAIL until validation/config expectations are updated.

**Step 3: Update config**

In `config/trading_config_chan_signal_only.example.json`, strategy setting should use:

```json
"sizing_mode": "target_ratio",
"target_long_ratio": 0.05,
"capital": 10000,
"max_position": 0.05,
"min_volume": 0.001,
"volume_step": 0.001,
"max_order_value": 1000
```

Keep:

```json
"trade_enabled": false
```

Backtest should keep:

```json
"trade_enabled": true
```

**Step 4: Update safety validation**

In `run_auto_trading.py`, keep signal-only permissive, but for order-enabled
Chan target-ratio configs require:

- `risk.enabled`;
- `setting.max_position`;
- `risk.max_order_value_usdt` or `setting.max_order_value`;
- `risk.max_daily_loss_pct`;
- positive `target_long_ratio`.

**Step 5: Run wiring tests**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python -m pytest tests/test_auto_trading_wiring.py -q
```

Expected: PASS.

**Step 6: Commit**

```bash
git add config/trading_config_chan_signal_only.example.json run_auto_trading.py tests/test_auto_trading_wiring.py
git commit -m "[Mod] Configure Chan target-ratio sizing"
```

### Task 4: Add Sizing Evidence To Acceptance Report

**Files:**
- Modify: `tools/strategy_acceptance.py`
- Modify: `tests/test_strategy_acceptance.py`
- Modify: `docs/strategy_testing_pipeline.md`

**Step 1: Write failing acceptance tests**

Add tests:

```python
def test_backtest_report_includes_sizing_fields() -> None:
    report = strategy_acceptance.build_backtest_evidence(
        strategy="chan",
        strategy_class_name="ChanStrategy",
        config_path="/tmp/config.json",
        vt_symbol="BTCUSDT_SWAP_OKX.GLOBAL",
        interval="1h",
        start_date="2025-05-23",
        end_date="2026-05-23",
        bar_count=100,
        signal_counts={"buy": {"first_buy": 1}, "sell": {}},
        order_count=1,
        trade_count=1,
        total_return=1.2,
        sharpe_ratio=0.5,
        max_drawdown=-0.3,
        final_position=0.005,
        strategy_setting={"sizing_mode": "target_ratio", "target_long_ratio": 0.05},
    )

    assert report["sizing_mode"] == "target_ratio"
    assert report["target_long_ratio"] == 0.05
```

**Step 2: Run tests to verify failure**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python -m pytest tests/test_strategy_acceptance.py -q
```

Expected: FAIL because helper does not exist.

**Step 3: Implement evidence helper**

In `tools/strategy_acceptance.py`, extract evidence construction into
`build_backtest_evidence(...)` and include:

- `sizing_mode`;
- `target_long_ratio`;
- `max_position`;
- `max_order_value`;
- existing fields.

Use this helper inside `run_configured_backtest`.

**Step 4: Update docs baseline after running acceptance**

After Task 5 runs, update `docs/strategy_testing_pipeline.md` with the exact
new Chan baseline values.

**Step 5: Run tests**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python -m pytest tests/test_strategy_acceptance.py -q
```

Expected: PASS.

**Step 6: Commit**

```bash
git add tools/strategy_acceptance.py tests/test_strategy_acceptance.py docs/strategy_testing_pipeline.md
git commit -m "[Mod] Report target-ratio sizing evidence"
```

### Task 5: Run Full Acceptance For Chan And DoubleMA

**Files:**
- Modify if needed: `docs/strategy_testing_pipeline.md`

**Step 1: Run unit and strategy test suite**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python -m pytest \
  tests/test_position_sizing.py \
  tests/test_chan_strategy.py \
  tests/test_auto_trading_wiring.py \
  tests/test_strategy_acceptance.py -q
```

Expected: PASS.

**Step 2: Run Chan acceptance**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate all
```

Expected: PASS. Record bar count, signal counts, order count, trade count,
return, drawdown, final position, sizing mode, and target ratio.

**Step 3: Run DoubleMA acceptance**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python tools/strategy_acceptance.py --strategy double_ma --gate all
```

Expected: PASS. DoubleMA should remain fixed-size and unchanged.

**Step 4: Update baseline docs**

Update `docs/strategy_testing_pipeline.md` with exact current results.

**Step 5: Run full focused verification**

Run:

```bash
/Users/miaoyuhan/Project/vnpy/.venv/bin/python -m pytest \
  tests/test_position_sizing.py tests/test_strategy_acceptance.py \
  tests/test_chan_objects.py tests/test_chan_cases.py tests/test_chan_normalizer.py \
  tests/test_chan_fractal.py tests/test_chan_stroke.py tests/test_chan_segment.py \
  tests/test_chan_pivot.py tests/test_chan_trend.py tests/test_chan_signal.py \
  tests/test_chan_analyzer.py tests/test_chan_strategy.py \
  tests/test_auto_trading_wiring.py tests/test_telegram_async.py \
  tests/test_okx_auto_health.py tests/test_okx_auto_trading_script.py \
  tests/test_dynamic_sizing.py tests/test_risk_engine.py -q
git diff --check
```

Expected: PASS.

**Step 6: Commit**

```bash
git add docs/strategy_testing_pipeline.md
git commit -m "[Mod] Refresh target-ratio acceptance baseline"
```

### Task 6: Update Strategy Production Skill

**Files:**
- Modify: `/Users/miaoyuhan/.codex/skills/strategy-production/references/readiness-checklist.md`
- Modify if needed: `/Users/miaoyuhan/.codex/skills/strategy-production/references/vnpy-cta-okx.md`

**Step 1: Add reusable sizing rule**

Add a rule:

- Strategy signal logic should prefer target exposure or target position over
  absolute size when the system has shared sizing infra.
- Backtest and runtime should use the same target-to-volume helper.
- Acceptance reports should include sizing mode and final position.

**Step 2: Validate skill**

Run:

```bash
PYTHONPATH=/tmp/skill-validator-pyyaml python3 \
  /Users/miaoyuhan/.codex/skills/.system/skill-creator/scripts/quick_validate.py \
  /Users/miaoyuhan/.codex/skills/strategy-production
```

Expected: `Skill is valid!`

**Step 3: Report status**

Report:

- sizing infra files changed;
- Chan target-ratio results;
- DoubleMA compatibility results;
- tests run;
- remaining risks.

