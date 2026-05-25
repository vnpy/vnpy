# Strategy Live Trade Gap Diagnostics

## Purpose

Use this playbook when an automated strategy is running but live fills are much
fewer than expected. Do not start by changing parameters. First prove whether the
gap is caused by signal scarcity, execution state, risk/order rejection, gateway
health, or data quality.

## Symptoms

- The process is alive and health looks mostly normal, but order/trade count is
  much lower than the strategy should produce.
- Market action looks favorable, but the strategy only traded once or stopped
  trading after a close.
- Backtest or offline replay shows more opportunities than the live runtime.
- Telegram or logs show startup/health, but few or no order records appear at
  the exchange.

## Diagnostic Principle

Separate these layers before fixing anything:

1. Signal layer: did the same rules produce signals on the same market data?
2. Strategy shell: did live state allow the signal to become an order?
3. Risk/order layer: did local risk, sizing, duplicate guards, or caps reject it?
4. Gateway/exchange layer: did the order reach the gateway and exchange?
5. Runtime/data layer: were ticks, bars, historical warmup, and account events
   actually updating?

## Required Evidence

Collect these fields for the affected runtime window:

- strategy class/name and symbol
- runtime mode: signal-only, DEMO order, or live order
- latest tick/account/order/trade timestamps
- current position, active stop state, last signal key, pending approval state
- live order and trade count from logs and exchange records
- offline replay signal count over the same period and interval
- risk rejection, sizing zero, duplicate-suppression, and gateway error logs
- whether startup used historical warmup and which interval/window was used

## Generic Flow

1. Confirm the process is truly operational:

```bash
tmux list-sessions
ps -axo pid,ppid,stat,lstart,command | rg 'run_auto_trading.py|strategy'
cat ~/.vntrader/okx_auto_state.json
.venv/bin/python tools/okx_auto_health.py
```

2. Count live order and trade evidence:

```bash
rg -n "委托下单|成交|Send order failed|风控拒单|买点跳过|信号模式|approval|确认" ~/.vntrader/okx_auto_stdout.log ~/.vntrader/log
```

3. Inspect strategy shell state:

```bash
cat ~/.vntrader/cta_strategy_data.json
```

Look specifically for:

- tiny floating-point residual positions such as `-6.9e-18`
- stale stop ids while flat
- stale `last_signal_key`
- pending approval or duplicate-signal state
- sizing fields that produce zero order volume

4. Replay the same market data with the same signal rules.

The replay should use the live strategy settings, the live interval, and the
same warmup window. If offline replay finds many signals but live has few
orders, focus on strategy shell, risk, and gateway execution. If replay finds no
signals, focus on signal rules and market assumptions.

5. Compare order records at the exchange.

Local logs prove that the strategy attempted an order. Exchange fills prove that
the order reached the account. If local logs show signals but no exchange
orders, search local risk and gateway errors first.

## Chan Adapter

For the current Chan/OKX path, use the adapter script:

```bash
.venv/bin/python tools/chan_runtime_diagnostics.py
.venv/bin/python tools/chan_runtime_diagnostics.py --replay-signals
```

This script is not the general method. It is a concrete adapter for Chan that
implements the generic flow above by reading local runtime state, live order
logs, and recent OKX 1m public bars.

## Common Root Causes

- Exact flat checks such as `pos == 0` block future entries after a close leaves
  a tiny residual float position.
- Strategy state restores stale stop or duplicate-signal fields after restart.
- Signal-only mode is still enabled.
- Local risk caps reject orders before they reach the exchange.
- Sizing returns zero because min volume, volume step, capital, stop distance,
  or max order value clips the order.
- Historical warmup uses a different interval from live bars.
- Live ticks are updating, but completed bars are not reaching the analyzer.
- Exchange websocket reconnects, but state keeps a stale error and health is
  interpreted incorrectly.
- Public/demo instrument metadata contains malformed symbols that abort startup.

## Fix Pattern

- Fix at the layer where evidence shows the gap.
- Add a regression case for the layer-specific failure.
- If the failure depends on runtime state, add a deterministic unit test around
  the strategy shell state transition.
- If the failure depends on an external system, add a playbook entry and a
  narrow parser/adapter test.
- Re-run focused tests, lint, health, and the live trade-gap diagnostic.

## Verification

Minimum verification after a fix:

```bash
.venv/bin/python -m pytest tests/test_chan_strategy.py tests/test_auto_trading_wiring.py tests/test_okx_auto_health.py -q
.venv/bin/python tools/okx_auto_health.py
.venv/bin/python tools/chan_runtime_diagnostics.py
```

When market-data replay is needed:

```bash
.venv/bin/python tools/chan_runtime_diagnostics.py --replay-signals
```

Expected result: runtime state and offline replay no longer point to an
unexplained execution gap. If replay still finds more signals than live orders,
continue debugging instead of tuning strategy parameters.
