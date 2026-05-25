# OKX Auto-Trading Runtime

## Symptoms

- `scripts/okx_auto_trading.sh status` says the process is running, but no strategy signal or order appears.
- Logs show `创建策略失败，存在重名DoubleMA_Auto`.
- Logs show `行情订阅失败，找不到合约DOGE-USDT-SWAP.GLOBAL` or `Failed to subscribe data, symbol not found`.
- Telegram receives startup messages but no strategy/order/fill messages.
- `scripts/okx_auto_trading.sh health` reports `down` or `degraded`.
- `scripts/okx_auto_trading.sh status` reports `not running`, while
  `~/.vntrader/okx_auto_state.json` still has a fresh `latest_tick_ts`.
- Logs show `socket is already closed` during subscription.
- Logs show `OKX public_api not connected`.
- Logs show `Connection reset by peer` under `launchctl`, but foreground/tmux
  runs connect successfully.
- During initialization, logs show many `TRADE_####` requests in one burst.
- Telegram logs show `Can't parse entities: unsupported start tag`.
- OKX rejects orders with `Wrong passphrase`, `API key doesn't exist`, `Insufficient ... margin`, or local `风控拒单`.

## Root Cause

The OKX auto-trading process depends on five separate readiness gates:

- OKX private config must exist and point to `Server: DEMO` during simulation.
- OKX contract metadata must be loaded before CTA subscribes or initializes.
- OKX public websocket must be connected before sending subscription packets.
- The managed CTA strategy must be `DoubleMATelegramStrategy` on `DOGEUSDT_SWAP_OKX.GLOBAL`.
- The strategy must use the process-owned Telegram notifier, not a second unstarted bot.

Older local CTA settings may contain `DoubleMA_Auto` with `DoubleMaStrategy` and
`DOGE-USDT-SWAP.GLOBAL`. That stale state can make vn.py report the strategy as
started while it has no usable OKX contract subscription.

Confirmed runtime lessons from the 2026-05-17 startup session:

- A raw `nohup ... &` process launched from Codex may be cleaned up after the
  command exits. Use a persistent local session such as `tmux` for manual runs.
- `launchctl submit` kept the process alive, but in this environment OKX
  websocket SSL handshakes repeatedly failed with `Connection reset by peer`.
  Prefer `tmux` unless this is re-tested and proven stable.
- A stale PID file can make `status`/`health` report `down` even while the state
  file is fresh and the real process is alive. Trust the combination of
  `tmux`, `state.pid`, and recent tick/account timestamps.
- CTA initialization replays historical bars. Strategy logic must not send
  Telegram signals or orders until `strategy.trading` is true.
- Telegram messages are sent with `parse_mode="HTML"`, so all dynamic text that
  may include `<` or `>` must be HTML-escaped.
- OKX emits one account event per currency. Risk equity should use the configured
  base currency (currently USDT), otherwise a tiny DOGE balance can trigger a
  false daily-loss/drawdown halt.
- Strategy sizing should use available USDT with
  `trading.sizing_mode=available_percent`, not total balance and not the largest
  non-USDT currency balance.
- Current simulation defaults are `trading.position_ratio=0.05`,
  `risk.max_order_value_usdt=1000.0`, and `risk.max_order_value_pct=0.10`.
  The effective order notional is clipped by the most conservative cap before
  converting to contract volume.
- In `notification.mode=notify_only`, Telegram is informational and the signal
  auto-enters the trading flow. It should not display `/approve` or `/reject`
  commands. Use `approval_required` only when polling is expected to wait for
  manual confirmation.
- On 1-minute DoubleMA, two MA values that display as `0.11` can still differ at
  5-6 decimals and trigger alternating long/short crosses. Check the 6-decimal
  Telegram signal text or logs before treating them as equal. Current filters:
  `runtime.ma_cross_deadband_pct=0.0002`, `runtime.ma_cross_deadband_abs=0`,
  and `runtime.reversal_cooldown_seconds=300`.
- OKX WS order operations require the numeric `instIdCode` from instruments
  metadata. If logs show `50014 Parameter instIdCode can not be empty`, verify
  `ContractData.extra["instIdCode"]` is populated and sent in the WS `order`
  payload.

## Diagnostic Commands

```bash
cd <repo>

scripts/okx_auto_trading.sh status
scripts/okx_auto_trading.sh health
scripts/okx_auto_trading.sh tail

ps -axo pid,ppid,stat,lstart,command | rg 'run_auto_trading.py|okx_auto'
cat ~/.vntrader/okx_auto_state.json
cat ~/.vntrader/okx_auto_trading.pid
cat ~/.vntrader/cta_strategy_setting.json
tail -n 200 ~/.vntrader/log/vt_$(date +%Y%m%d).log
```

When the process was started in `tmux`, use these extra checks:

```bash
tmux list-sessions
tmux list-panes -t okx_auto -F '#{pane_pid} #{pane_current_command}'
tmux capture-pane -t okx_auto -p -S -120

cat ~/.vntrader/okx_auto_trading.pid
.venv/bin/python - <<'PY'
import json, os, pathlib
state = json.loads((pathlib.Path.home() / ".vntrader/okx_auto_state.json").read_text())
print("state_pid", state.get("pid"))
print("latest_tick_ts", state.get("latest_tick_ts"))
print("latest_account_ts", state.get("latest_account_ts"))
os.kill(int(state["pid"]), 0)
print("state pid is alive")
PY
```

Expected startup proof in logs:

```text
OKX | REST API started
OKX | SWAP contract data received
OKX | SPOT contract data received
OKX | FUTURES contract data received
OKX | Private API login successful
MainEngine | 订阅行情 -> OKX：SubscribeRequest(symbol='DOGEUSDT_SWAP_OKX'...
CtaStrategy | [DoubleMA_Auto]  策略启动
```

Expected health shape:

```text
"status": "healthy"
"okx_server": "DEMO"
"contract_ready": true
"strategy_inited": true
"strategy_trading": true
"latest_tick_ts": "<recent timestamp>"
```

Known healthy state from 2026-05-17 after tmux startup:

```text
tmux session: okx_auto
pid: 97155
okx_server: DEMO
contract_ready: true
strategy_inited: true
strategy_trading: true
latest_tick_ts: updating
latest_account_ts: updating
risk.daily_halt: false
risk.drawdown_halt: false
```

## Fix / Recovery

1. Confirm `~/.vntrader/connect_okx.json` exists and contains:

```json
{
  "API Key": "...",
  "Secret Key": "...",
  "Passphrase": "...",
  "Server": "DEMO",
  "Proxy Host": "",
  "Proxy Port": 0,
  "Spread Trading": "False",
  "Margin Currency": ""
}
```

2. Restart through the wrapper:

```bash
scripts/okx_auto_trading.sh restart
scripts/okx_auto_trading.sh health
```

For a persistent local manual run, `tmux` was the verified working method:

```bash
tmux kill-session -t okx_auto 2>/dev/null || true
rm -f ~/.vntrader/okx_auto_trading.pid
: > ~/.vntrader/okx_auto_stdout.log
tmux new-session -d -s okx_auto \
  'cd <repo> && PYTHONUNBUFFERED=1 .venv/bin/python run_auto_trading.py >> "$HOME/.vntrader/okx_auto_stdout.log" 2>&1'

sleep 150
.venv/bin/python tools/okx_auto_health.py
```

When a strategy is running but live fills look suspiciously sparse, use the
general diagnostic playbook before changing strategy rules:

```bash
docs/troubleshooting/strategy-live-trade-gap-diagnostics.md
```

For the current Chan adapter, compare runtime state with offline signal replay:

```bash
.venv/bin/python tools/chan_runtime_diagnostics.py
.venv/bin/python tools/chan_runtime_diagnostics.py --replay-signals
```

This separates process/runtime issues, floating-point dust positions after close
fills, and genuine signal scarcity for Chan specifically.

If `status` says `not running` but `state.pid` is alive, the PID file is stale:

```bash
python_pid=$(.venv/bin/python - <<'PY'
import json, pathlib
state = json.loads((pathlib.Path.home() / ".vntrader/okx_auto_state.json").read_text())
print(state["pid"])
PY
)
printf '%s' "$python_pid" > ~/.vntrader/okx_auto_trading.pid
scripts/okx_auto_trading.sh status
```

3. If health still reports no tick, inspect contract/subscription lines:

```bash
rg -n "DOGE|subscribe|找不到合约|Failed to subscribe" ~/.vntrader/log
```

4. If OKX auth fails, rotate or re-enter the DEMO API key/passphrase in the GUI and retry.

5. If orders are rejected for margin, reduce `trading.position_ratio`, `trading.leverage`, or ensure the simulated account has enough USDT margin.

6. If orders are rejected by risk, inspect `config/trading_config.local.json`,
   `config/trading_config.json`, and runtime `risk.*` values. The notional cap
   uses `price * volume * contract.size`. A common failure is strategy sizing
   producing a much larger notional than `risk.max_order_value_usdt` or
   `risk.max_order_value_pct` allows; in that case no order reaches OKX, so the
   OKX simulated account will show no order record.

7. If OKX rejects with `50014 Parameter instIdCode can not be empty`, the order
   reached OKX but the WS order payload is missing current instrument metadata.
   Check the contract query path and ensure `instIdCode` from `Get instruments`
   is stored on the contract and sent in order/cancel operations.

8. If startup fails with `socket is already closed` or `public_api not connected`,
   confirm logs show `Public API connected` before subscription. The startup code
   should wait for this readiness gate before calling `subscribe`.

8. If logs show many `TRADE_####` lines immediately after historical K-line
   loading, the strategy is sending signals during initialization. Ensure
   `on_bar` returns before trade logic when `strategy.trading` is false.

9. If Telegram reports `Can't parse entities`, inspect the generated message for
   raw `<` or `>` in strategy logic/backtest fields. Escape dynamic text before
   sending with HTML parse mode.

## Prevention

- Prefer one managed runtime at a time. For manual local runs, use `tmux`
  session `okx_auto`; for wrapper runs, use `scripts/okx_auto_trading.sh`.
- Do not use `launchctl submit` for OKX auto trading unless websocket startup is
  re-verified in that environment.
- Treat `strategy_trading=true` alone as insufficient; require a recent tick and DEMO server in health JSON.
- Keep `DOGEUSDT_SWAP_OKX.GLOBAL` format for vn.py OKX symbols. Hyphenated `DOGE-USDT-SWAP.GLOBAL` is stale for this local gateway.
- Use Telegram `notify_only` mode for the first simulation phase. Approval mode requires Telegram polling and is a separate operational concern.
- Keep `runtime.init_days` small enough for startup (currently 3 days) and
  `runtime.init_timeout` long enough for OKX history pagination (currently 180s).
- If Telegram shows alternating long/short signals while fast/slow MA appear
  equal, inspect 6-decimal MA values and the deadband logs for
  `均线差值未超过阈值`.
- During future changes, test that historical initialization does not send
  Telegram trade signals before the strategy is actually started.
- Add new failure modes to this playbook after any issue takes more than one diagnostic pass.

## Verification

```bash
scripts/okx_auto_trading.sh health
.venv/bin/python -m pytest \
  tests/test_auto_trading_wiring.py \
  tests/test_telegram_async.py \
  tests/test_dynamic_sizing.py \
  tests/test_risk_engine.py \
  tests/test_okx_auto_health.py \
  tests/test_okx_auto_trading_script.py -q
```

Healthy runtime verification requires all of:

- health JSON status is `healthy`;
- Telegram receives startup and strategy-start messages;
- `latest_tick_ts` refreshes while the process is running;
- `latest_account_ts` refreshes and `risk.daily_halt=false`, `risk.drawdown_halt=false`;
- logs do not contain fresh `系统错误`, `Traceback`, `socket is already closed`,
  `Telegram确认失败`, or `发送Telegram消息失败`;
- any signal/order/trade or rejection is visible in Telegram and vn.py logs.

## 2026-05-17 Session Notes

What changed during the first successful OKX DEMO automation run:

- Added a process state file and health checker so schedulers can inspect PID,
  DEMO mode, contract readiness, strategy readiness, tick freshness, latest
  account update, latest error, and risk snapshot.
- Wired the managed strategy to `DoubleMATelegramStrategy` and removed stale
  `DoubleMA_Auto` configs when class/symbol/settings do not match.
- Reused one process-owned Telegram notifier; strategy callbacks submit messages
  thread-safely instead of creating an unstarted bot or using `create_task` from
  vn.py callback threads.
- Added `notification.mode=notify_only` for the first simulation phase.
- Added OKX readiness waits: contract metadata first, public websocket connected
  before subscription, then strategy init/start and first tick.
- Reduced live strategy init history to configurable `runtime.init_days` and
  raised `runtime.init_timeout`.
- Prevented historical initialization bars from triggering live trade requests.
- Escaped Telegram HTML dynamic text and defaulted missing backtest fields.
- Added RiskEngine integration and made its equity baseline use USDT to avoid
  false halts from non-USDT currency balances.

What was observed:

- Foreground and `tmux` runs could reach healthy state.
- Raw `nohup &` from Codex did not reliably persist after the shell command.
- `launchctl submit` persisted but repeatedly hit OKX websocket
  `Connection reset by peer`; it was stopped and should not be the default.
- A stale PID file can be the only reason health reports `down`; validate
  `state.pid` and fresh timestamps before restarting.
