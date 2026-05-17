# QMT GUI Session And xtquant `connect -1`

## Symptoms

- `scripts/qmt_bridge_remote.sh health` or `GET /health` returns `200 OK`, but trading endpoints fail.
- `GET /positions` returns `503` with `connect QMT failed: -1`.
- `GET /health?runtime=1` returns `runtime_ok: false` and says xtquant cannot connect to QMT.
- `scripts/qmt_bridge_remote.sh status` may show only `XtItClient.exe`, or no QMT GUI-related processes.
- `query user` may show no logged-in interactive user, even though SSH works.

## Root Cause

QMT trading APIs depend on a logged-in Windows interactive desktop session and a
fully started/logged-in QMT or MiniQMT client. SSH access alone is not enough.

The bridge process can run as a background HTTP service and still answer
`/health`, but `XtQuantTrader.connect()` returns `-1` until the QMT GUI/API
runtime is actually available in the Windows desktop session.

Important distinction:

- `XtItClient.exe` alone is not proof that QMT trading API is ready.
- A passing `/health` only proves the bridge process is alive.
- `/health?runtime=1`, `/positions`, and `/rebalance dry_run` prove QMT runtime access.

## Diagnostic Commands

From macOS:

```bash
scripts/qmt_bridge_remote.sh status
scripts/qmt_bridge_remote.sh health

NO_PROXY='*' no_proxy='*' \
  curl --noproxy '*' -m 12 -sS -i \
  'http://192.168.2.2:18080/health?runtime=1'

NO_PROXY='*' no_proxy='*' \
  curl --noproxy '*' -m 12 -sS -i \
  -H 'Authorization: Bearer <token>' \
  http://192.168.2.2:18080/positions
```

On Windows through SSH:

```bash
ssh win "cmd /c query user"
ssh win "cmd /c tasklist /v | findstr /i XtMiniQmt"
ssh win "cmd /c tasklist /v | findstr /i XtItClient"
ssh win "cmd /c tasklist /v | findstr /i miniquote"
ssh win "cmd /c netstat -ano | findstr :18080"
```

Interpretation:

- No user from `query user`: Codex cannot launch or log into QMT GUI by SSH alone.
- `XtMiniQmt.exe` and `miniquote.exe` absent: MiniQMT is not fully running.
- `/positions` returns `connect QMT failed: -1`: bridge is reachable, QMT trading API is not.
- If both `D:/国金证券QMT交易端/userdata_mini` and `D:/国金证券QMT交易端/userdata`
  return `connect=-1` in a direct probe, do not keep changing bridge config;
  the QMT xtquant runtime service itself is not available.

Optional direct path probe on Windows:

```python
from xtquant import xttrader

for path in [
    r"D:/国金证券QMT交易端/userdata_mini",
    r"D:/国金证券QMT交易端/userdata",
]:
    trader = xttrader.XtQuantTrader(path, 123456)
    trader.start()
    print(path, trader.connect())
```

## Fix / Recovery

1. Log into the Windows desktop interactively.
2. Open QMT and the trading terminal manually. If the user says "QMT is open"
   but smoke still fails, explicitly remind them to start the trading terminal,
   not only the market/client shell.
3. Complete login and confirm the target account is online in the GUI.
4. Start or restart the bridge with:

```bash
scripts/qmt_bridge_remote.sh start
```

5. Verify:

```bash
scripts/qmt_bridge_remote.sh status
scripts/qmt_bridge_remote.sh health
scripts/qmt_bridge_remote.sh smoke --token <token>
```

If a stale bridge owns port `18080` and SSH cannot kill it, close the desktop
bridge window or restart the Windows desktop-side process. Do not repeatedly
attempt `taskkill` after access is denied.

## Prevention

- Always start real QMT smoke by running `scripts/qmt_bridge_remote.sh status`.
- Treat `/health` as bridge liveness only.
- Do not claim QMT integration is working until `/positions` and `/rebalance dry_run` pass.
- Keep real QMT calls behind the worker-process timeout in `qmt_test_strategy/src/trader/qmt_trader.py`.
- Use `pythonw.exe` for the bridge startup to avoid Windows console QuickEdit pausing the process.

## Verification

Expected bridge liveness:

```text
HTTP/1.0 200 OK
{"ok": true, ...}
```

Expected QMT runtime readiness:

```text
/status -> sees XtMiniQmt.exe, XtItClient.exe, and miniquote.exe
/health?runtime=1 -> "runtime_ok": true
/positions -> {"ok": true, "positions": ..., "cash": ...}
/rebalance dry_run -> {"ok": true, "mode": "dry_run", "orders": ...}
```

2026-05-16 confirmation:

- Starting only enough QMT to show `XtItClient.exe` was not sufficient.
- After the user started the trading terminal, `XtMiniQmt.exe`, `XtItClient.exe`,
  and `miniquote.exe` were all present.
- `/health?runtime=1` changed to `runtime_ok: true`.
- `/positions` returned `{"ok": true, "cash": 1.22, "market_value": 0.0, "total_asset": 1.22, "positions": {}}`.
- Safe smoke passed: `3 passed`; execute remained skipped.

Safe smoke command:

```bash
NO_PROXY='*' no_proxy='*' \
  scripts/qmt_external_smoke.sh \
  --url http://192.168.2.2:18080 \
  --token <token>
```
