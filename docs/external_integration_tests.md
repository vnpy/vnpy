# External Integration Tests

These tests contact real external systems and are skipped by default.

## When To Run These Tests

Run the safe local suite and the real smoke flow after changes in any of these
areas:

- QMT bridge HTTP handlers or `qmt_test_strategy/src/trader/qmt_trader.py`
- Position reading, rebalance planning, or order execution
- Daily rebalance pipeline
- Auto-trading order routing or risk checks
- Telegram approval flow or private config loading

Do not claim QMT integration is working from unit tests alone. Unit tests prove
contract safety; the smoke flow proves the current Windows/QMT runtime can
respond.

## Default Safe Run

```bash
.venv/bin/python -m pytest tests/test_external_integrations.py -q
```

Expected result:

```text
7 skipped
```

Recommended development preflight:

```bash
.venv/bin/python -m pytest \
  tests/test_qmt_external_smoke_script.py \
  tests/test_external_integrations.py \
  -q

cd qmt_test_strategy
../.venv/bin/python -m pytest tests/test_rebalance.py -q
```

Expected result from the current safe suite:

```text
2 passed, 7 skipped
8 passed
```

The QMT subproject tests include a worker-process timeout regression test. Keep
that test: it prevents a blocked `xtquant` call from freezing the whole HTTP
bridge again.

## Windows QMT Bridge Checklist

The current real-test environment is:

- SSH alias: `win`
- Remote project path: `D:/test`
- MiniQMT client path: `D:/国金证券QMT交易端`
- MiniQMT userdata path in config: `D:/国金证券QMT交易端/userdata_mini`
- Account id in bridge config is local/private; do not commit the real value.
- Bridge port: `18080`
- Bridge URL from macOS: `http://192.168.2.2:18080`
- Local/private remote config: `D:/test/config/config.yaml`
- Interactive desktop startup script: `D:/test/start_qmt_bridge_codex.bat`

Start order:

1. Start and log into QMT on the Windows desktop.
2. Ask the user to double-click `D:\test\start_qmt_bridge_codex.bat` from the
   interactive desktop.
3. Or start it from macOS through the interactive scheduled task wrapper:
   `scripts/qmt_bridge_remote.sh start`
4. Do not rely on `ssh win ... python -m src.main ...` for real trading API
   verification. SSH starts in a different Windows session and can make
   `XtQuantTrader.connect()` fail with `-1`.

Before trying to recover QMT from SSH, check whether a desktop user is logged
in:

```bash
scripts/qmt_bridge_remote.sh status
```

If `query user` reports no user, the `InteractiveToken` scheduled task has no
desktop token to use. Codex can still probe any already-running bridge process,
but it cannot launch or log into the QMT GUI from SSH alone.

The bat file should include:

```bat
@echo off
cd /d D:\test
set QMT_BRIDGE_TOKEN=<local-private-token>
set QMT_BRIDGE_QMT_TIMEOUT_SECONDS=8
start "" D:\test\.venv\Scripts\pythonw.exe -m src.main serve --host 0.0.0.0 --port 18080
```

Keep the token private. Do not commit real tokens, account credentials, or
runtime files.

The local wrapper for repeatable bridge management is:

```bash
scripts/qmt_bridge_remote.sh status
scripts/qmt_bridge_remote.sh start
scripts/qmt_bridge_remote.sh health
scripts/qmt_bridge_remote.sh smoke --token <same token set on Windows>
```

It uses Windows Task Scheduler task `CodexQmtBridge`. That task must have
`LogonType=InteractiveToken` and execute `D:\test\start_qmt_bridge_codex.bat`.

## Sync Remote Code After Bridge Changes

If QMT bridge files changed locally, sync them before running real smoke tests:

```bash
scp qmt_test_strategy/src/main.py win:D:/test/src/main.py
scp qmt_test_strategy/src/trader/qmt_trader.py win:D:/test/src/trader/qmt_trader.py
scp qmt_test_strategy/src/data/history_service.py win:D:/test/src/data/history_service.py
scp qmt_test_strategy/src/utils/config.py win:D:/test/src/utils/config.py
scp qmt_test_strategy/tests/test_rebalance.py win:D:/test/tests/test_rebalance.py
```

Then run the Windows unit suite:

```bash
ssh win "cmd /c D:\test\.venv\Scripts\python.exe -m pytest D:\test\tests\test_rebalance.py -q"
```

## Enable Read-Only External Checks

Recommended QMT smoke command:

```bash
QMT_BRIDGE_TOKEN=<same token set on Windows> \
  scripts/qmt_external_smoke.sh --url http://192.168.2.2:18080
```

Use `NO_PROXY` when testing directly from macOS, otherwise local proxy settings
can make LAN diagnostics misleading:

```bash
NO_PROXY='*' no_proxy='*' \
  scripts/qmt_external_smoke.sh \
  --url http://192.168.2.2:18080 \
  --token <same token set on Windows>
```

Manual probes:

```bash
ssh win "cmd /c netstat -ano | findstr :18080"

NO_PROXY='*' no_proxy='*' \
  curl --noproxy '*' -m 5 -v http://192.168.2.2:18080/health

NO_PROXY='*' no_proxy='*' \
  curl --noproxy '*' -m 12 -sS -i \
  -H 'Authorization: Bearer <token>' \
  http://192.168.2.2:18080/positions
```

Equivalent manual pytest flow:

```bash
export VNPY_RUN_EXTERNAL_TESTS=1

# QMT bridge
export QMT_BRIDGE_URL=http://192.168.2.2:18080
export QMT_BRIDGE_TOKEN=<same token set on Windows>

# Telegram
export TELEGRAM_BOT_TOKEN=<bot token>
export TELEGRAM_CHAT_ID=<chat id>

.venv/bin/python -m pytest tests/test_external_integrations.py -q
```

This runs:

- QMT `/health`
- QMT `/positions`
- QMT `/rebalance` in `dry_run` mode twice with the same `request_id`
- Telegram `getMe`
- Telegram test message
- `rdagent --help`

## Enable QMT Simulated Execute

This may place orders in the QMT simulated account. Use only after checking the
weights and prices below.

Recommended QMT execute smoke command:

```bash
QMT_BRIDGE_TOKEN=<same token set on Windows> \
  scripts/qmt_external_smoke.sh \
  --url http://192.168.2.2:18080 \
  --weights '{"510300.SH": 0.01}' \
  --prices '{"510300.SH": 4.0}' \
  --execute
```

Equivalent manual pytest flow:

```bash
export VNPY_RUN_EXTERNAL_TESTS=1
export VNPY_RUN_QMT_EXECUTE_TESTS=1
export QMT_TEST_WEIGHTS_JSON='{"510300.SH": 0.01}'
export QMT_TEST_PRICES_JSON='{"510300.SH": 4.0}'

.venv/bin/python -m pytest \
  tests/test_external_integrations.py::test_external_qmt_rebalance_execute \
  -q
```

Keep `QMT_TEST_WEIGHTS_JSON` tiny for the first run. The bridge still enforces
its own single-order cap, token authentication, and `request_id` idempotency.

## 2026-05-05 QMT Debugging Notes

This is the failure pattern observed during the first real integration run:

- QMT GUI was running in Windows session 1.
- A bridge started through SSH could listen on the port but was not a reliable
  real trading API test because it was not in the same interactive desktop
  session.
- A stale desktop bridge process owned `18080`. SSH could see it with `netstat`
  but could not kill it with `taskkill /F` because of session/permission
  boundaries.
- macOS `curl` could complete the TCP connection but received zero bytes until
  timeout. Windows-local `curl http://127.0.0.1:18080/health` also timed out,
  proving the issue was inside the bridge process rather than LAN/firewall.
- Starting a clean diagnostic bridge on another port proved the code path and
  network were healthy.
- The fix was to keep `/health` fast by default and isolate real `xtquant`
  calls in a worker process with a timeout.

How to interpret current failures:

- `/health` returns `200`: the bridge process and HTTP path are alive.
- `/positions` returns `503 connect QMT failed: -1`: the bridge responded, but
  QMT trading API connection failed. Check QMT login, account id, userdata path,
  and whether the bridge was started from the interactive desktop.
- If `query user` shows no logged-in user and QMT processes are absent, ask the
  user to log into the Windows desktop and QMT first; SSH-only recovery is not
  enough for GUI/API startup.
- `/positions` returns `503 QMT worker timed out`: the bridge responded, but
  the child process blocked inside `xtquant`. Keep diagnosing QMT runtime; do
  not remove the worker timeout.
- TCP connects but `/health` times out and no request log appears: close the
  black desktop bridge window and restart `D:\test\start_qmt_bridge_codex.bat`.
- Windows console QuickEdit/text selection can pause the bridge process while
  leaving the port open. Prefer `pythonw.exe` in the startup bat; if a black
  console is already open and requests hang, press `Esc`/`Enter` or close it.
- `taskkill` access denied for the `18080` PID: ask the user to close the
  desktop bridge window instead of repeatedly killing from SSH.

If a temporary diagnostic port is used:

```bash
ssh win "cmd /c netstat -ano | findstr :18082"
ssh win "cmd /c taskkill /PID <pid> /F"
```

Clean up temporary ports after the test so the next run has one obvious bridge
endpoint.
