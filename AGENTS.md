# Repository Guidelines

## Project Overview
VeighNa is a Python-based quantitative trading framework with a modular architecture supporting multiple gateways, trading applications, and data feeds.

## Build, Test, and Development Commands

### Installation
- `bash install.sh` - Install from source on Linux
- `bash install_osx.sh` - Install from source on macOS  
- `install.bat` - Install from source on Windows
- `pip install -e .` - Editable install for development
- `pip install -e ".[alpha]"` - Install with alpha/ML dependencies
- `pip install -e ".[dev]"` - Install with dev dependencies (hatchling, babel, stubs)

### Testing
- `python -m pytest` - Run all tests
- `pytest tests/test_alpha101.py` - Run single test file
- `pytest tests/test_alpha101.py::test_function_name -v` - Run single test with verbose output
- `pytest tests/ -k "test_pattern"` - Run tests matching pattern
- `scripts/qmt_external_smoke.sh --url http://192.168.2.2:18080 --token <token>` - Run real QMT bridge smoke tests after trading/QMT changes
- `scripts/qmt_bridge_remote.sh start|status|health|smoke --token <token>` - Manage the Windows QMT bridge through the interactive scheduled task

### Code Quality
- `ruff check .` - Run linter (reports style issues)
- `ruff check --fix .` - Auto-fix linting issues where possible
- `mypy vnpy` - Run static type checker (strict settings)

### Build
- `python -m build` - Build wheel and sdist (uses hatchling)
- Build includes locale compilation via custom hook in `vnpy/trader/locale/build_hook.py`

## Code Style Guidelines

### Python Version & Environment
- **Python 3.12 required** (see `requires-python = ">=3.12,<3.13"` in pyproject.toml)
- Target version for ruff: py312

### Import Organization (follow existing patterns)
```python
# 1. Standard library imports
import os
from datetime import datetime
from typing import TypeVar
from collections.abc import Callable

# 2. Third-party imports
from vnpy.event import Event, EventEngine
import pandas as pd
import numpy as np

# 3. Local package imports (absolute for cross-module)
from vnpy.trader.object import TickData, OrderData

# 4. Relative imports (within same package)
from .app import BaseApp
from .constant import Direction, Exchange
from .utility import TRADER_DIR
```

### Naming Conventions
- **Classes**: `CamelCase` (e.g., `BaseEngine`, `MainEngine`, `TickData`)
- **Functions/Methods/Variables**: `snake_case` (e.g., `get_contract`, `send_order`)
- **Constants**: `UPPER_SNAKE_CASE` (e.g., `DEFAULT_PATH`, `EVENT_TICK`)
- **Private attributes**: `_leading_underscore` (e.g., `_engine`)

### Type Annotations (Required)
- All function parameters and return types must be annotated
- Use `|` for unions (Python 3.10+): `str | None`, `EventEngine | None`
- Use `TypeVar` for generic types bound to base classes
- See strict mypy config in pyproject.toml - no untyped definitions allowed

### Docstrings
- All classes and public methods must include docstrings
- Use triple quotes `"""` format
- Keep concise but descriptive

### Error Handling
- Use explicit exception types, avoid bare `except:`
- Log errors via the framework logger (`from .logger import logger`)
- Use loguru for internal logging

### Key Dependencies
- PySide6==6.8.2.1 (GUI framework)
- pandas>=2.2.3, numpy>=2.2.3 (data processing)
- polars>=1.26.0 (alpha module, fast DataFrames)
- ta-lib>=0.6.4 (technical analysis)
- loguru>=0.7.3 (logging)
- pyzmq>=26.3.0 (messaging)
- deap>=1.4.2 (genetic algorithms)
- pyqtgraph>=0.13.7 (charting)

## Testing Guidelines
- Framework: pytest
- Test files: `tests/test_<feature>.py`
- Test functions: `test_<behavior>()`
- Use fixtures for shared test data
- Keep tests deterministic (set random seeds)
- Use polars for test DataFrames in alpha module tests

## Troubleshooting Playbook

Recurring mistakes and external-system traps are tracked in `docs/troubleshooting/`.
Before debugging QMT, Telegram, external smoke tests, Windows SSH/session issues,
or any failure that resembles a previous incident, check this playbook first.

### Playbook Index
- `docs/troubleshooting/README.md` - Index and entry template.
- `docs/troubleshooting/qmt-gui-session-xtquant-connect-minus-1.md` - QMT GUI session requirement, `/health` vs real runtime readiness, and `XtQuantTrader.connect() == -1`.
- `docs/troubleshooting/okx-auto-trading.md` - OKX DEMO auto-trading startup, health, Telegram, tmux process management, and websocket/CTA readiness pitfalls.

### When To Add A Playbook Entry
- Add an entry whenever an issue takes more than one diagnostic pass or involves an external system, GUI session, credentials, network/proxy, scheduler, or runtime-specific behavior.
- Add an entry when the same failure mode could plausibly recur in future sessions.
- Add an entry when a command appears to succeed but does not prove the thing we actually need, such as QMT bridge `/health` succeeding while `/positions` fails.

### Playbook Entry Workflow
- Create `docs/troubleshooting/<short-kebab-case-title>.md`.
- Include: symptoms, confirmed root cause, diagnostic commands, fix/recovery, prevention, and verification.
- Prefer exact commands and expected outputs over prose-only advice.
- Distinguish bridge/process liveness from real external-system readiness.
- Update the Playbook Index in this `AGENTS.md` and `docs/troubleshooting/README.md`.
- If the issue changes operational flow, update the relevant script or test so the playbook is executable, not just descriptive.

## OKX Auto-Trading Runtime Notes

Use these notes when debugging or maintaining the local OKX DEMO automation
flow (`run_auto_trading.py`, `double_ma_telegram_strategy.py`,
`telegram_notifier.py`, `tools/okx_auto_health.py`, and
`scripts/okx_auto_trading.sh`). See `docs/troubleshooting/okx-auto-trading.md`
for the full playbook and command examples.

### Verified Runtime From 2026-05-17
- The first confirmed healthy run used `tmux` session `okx_auto` with process
  PID `97155`; OKX was `DEMO`, `DoubleMA_Auto` was initialized/trading, tick and
  account timestamps were updating, and risk halts were false.
- Raw `nohup ... &` from Codex did not reliably persist after the shell command
  ended. Prefer `tmux` for manual local runs.
- `launchctl submit` kept a job alive, but in this environment OKX websocket SSL
  handshakes repeatedly failed with `Connection reset by peer`; do not make it
  the default unless re-tested.
- A stale `~/.vntrader/okx_auto_trading.pid` can make `status`/`health` report
  `down` even when `~/.vntrader/okx_auto_state.json` has a live `state.pid` and
  fresh `latest_tick_ts`. Check `tmux`, `state.pid`, and tick/account timestamps
  before restarting.

### OKX Readiness Gates
- Private config must come from `~/.vntrader/connect_okx.json` and use
  `"Server": "DEMO"` during simulation.
- Contract metadata must load before CTA strategy setup; symbol format is
  `DOGEUSDT_SWAP_OKX.GLOBAL`, not stale `DOGE-USDT-SWAP.GLOBAL`.
- OKX public websocket must be connected before calling subscribe; otherwise
  startup can fail with `socket is already closed` or `OKX public_api not connected`.
- The managed CTA strategy must be `DoubleMATelegramStrategy` named
  `DoubleMA_Auto`; stale local CTA settings should be removed/recreated when
  class, symbol, or settings do not match.
- Treat `strategy_trading=true` alone as insufficient; a healthy run also needs
  recent tick/account timestamps, `okx_server=DEMO`, and no latest error.

### Telegram, Init, And Risk Pitfalls
- Strategy callbacks must use the process-owned `TelegramTradeBot`; do not
  construct a second unstarted bot inside a strategy.
- Keep first simulation runs in Telegram `notify_only` mode. Approval mode needs
  Telegram polling and is a separate operational mode.
- CTA initialization replays historical bars; strategy code must not send
  Telegram trade signals or orders until `strategy.trading` is true.
- Telegram messages use HTML parse mode, so dynamic text containing `<` or `>`
  must be escaped and missing backtest fields must have defaults.
- OKX account updates are per currency. Risk equity should use USDT as the base
  currency; otherwise tiny non-USDT balances can trigger false daily-loss or
  drawdown halts.
- Strategy sizing should use available USDT, not total balance or the largest
  non-USDT asset. Current OKX DEMO defaults are `trading.sizing_mode=available_percent`,
  `trading.position_ratio=0.05`, `risk.max_order_value_usdt=1000.0`, and
  `risk.max_order_value_pct=0.10`; final order notional is clipped by the most
  conservative configured cap.
- If Telegram shows many signals but OKX has no order records, search logs for
  `风控拒单` first. A prior failure pattern was 90% account sizing producing
  ~63k USDT notional while `risk.max_order_value_usdt` was 200 USDT, so the
  local RiskEngine vetoed the order before it reached OKX.
- If logs show `Send order failed, status code: 50014, message: Parameter
  instIdCode can not be empty`, inspect OKX contract metadata. WS order
  operations must send `ContractData.extra["instIdCode"]` from the instruments
  response, not only the legacy `instId` string.
- `runtime.signal_cooldown_seconds` suppresses repeated same-direction prompts
  after a signal; the strategy also blocks new prompts while a Telegram approval
  is pending.
- 1-minute DoubleMA signals use `runtime.ma_cross_deadband_pct` and
  `runtime.ma_cross_deadband_abs` to filter near-equal fast/slow MA crosses.
  Telegram signal text prints MA values with 6 decimals because 2-decimal DOGE
  display can make real spreads look equal. `runtime.reversal_cooldown_seconds`
  suppresses immediate long/short flips after a signal.

### Quick Commands
```bash
tmux list-sessions
tmux list-panes -t okx_auto -F '#{pane_pid} #{pane_current_command}'
tmux capture-pane -t okx_auto -p -S -120
ps -axo pid,ppid,stat,lstart,command | rg 'run_auto_trading.py|okx_auto'

cat ~/.vntrader/okx_auto_state.json
cat ~/.vntrader/okx_auto_trading.pid
.venv/bin/python tools/okx_auto_health.py
tail -n 200 ~/.vntrader/okx_auto_stdout.log
rg -n "系统错误|Traceback|Telegram确认失败|发送Telegram消息失败|socket is already closed|Connection reset|风控拒单" ~/.vntrader/okx_auto_stdout.log
```

### Focused Verification
- After OKX auto-trading, Telegram, risk/order routing, or health-check changes,
  run:
```bash
.venv/bin/python -m pytest \
  tests/test_auto_trading_wiring.py \
  tests/test_telegram_async.py \
  tests/test_dynamic_sizing.py \
  tests/test_risk_engine.py \
  tests/test_okx_auto_health.py \
  tests/test_okx_auto_trading_script.py -q
```
- `ruff` may not be installed in the local `.venv`; report that explicitly
  instead of claiming lint passed.

## Real External Test Workflow

Use this workflow after changing auto trading, QMT bridge, Telegram approval, rebalance pipeline, or risk/order routing code. These checks contact real external systems and are skipped by default unless explicitly enabled.

### Local Safety Suite
- Run targeted unit tests first: `.venv/bin/python -m pytest tests/test_qmt_external_smoke_script.py tests/test_external_integrations.py -q`
- Run QMT bridge unit tests from the subproject: `cd qmt_test_strategy && ../.venv/bin/python -m pytest tests/test_rebalance.py -q`
- Expected safe result for external pytest without env: external tests skip, script tests pass.

### Windows QMT Bridge Setup
- Windows host is reachable via SSH alias `win`.
- Current remote project path: `D:/test`.
- Current QMT client path: `D:/国金证券QMT交易端`.
- Current QMT account id is local/private; do not commit the real value.
- Remote bridge config lives at `D:/test/config/config.yaml`; do not commit real credentials or account-private runtime files.
- Start the bridge from the interactive Windows desktop session, not from SSH session 0. Double-click `D:\test\start_qmt_bridge_codex.bat` after QMT is open and logged in.
- The bridge token used for smoke testing is set inside that bat file. Keep it local/private and rotate if shared.
- The bat should set `QMT_BRIDGE_QMT_TIMEOUT_SECONDS=8` so blocked `xtquant` calls return 503 instead of freezing the HTTP server.

### Sync And Verify Remote Code
- After QMT bridge code changes, sync the changed files to Windows before real tests, for example:
```bash
scp qmt_test_strategy/src/main.py win:D:/test/src/main.py
scp qmt_test_strategy/src/trader/qmt_trader.py win:D:/test/src/trader/qmt_trader.py
scp qmt_test_strategy/src/data/history_service.py win:D:/test/src/data/history_service.py
scp qmt_test_strategy/src/utils/config.py win:D:/test/src/utils/config.py
scp qmt_test_strategy/tests/test_rebalance.py win:D:/test/tests/test_rebalance.py
```
- Run the remote unit suite: `ssh win "cmd /c D:\test\.venv\Scripts\python.exe -m pytest D:\test\tests\test_rebalance.py -q"`

### Real QMT Smoke Flow
- Prefer the remote-control wrapper for bridge management:
```bash
scripts/qmt_bridge_remote.sh status
scripts/qmt_bridge_remote.sh start
scripts/qmt_bridge_remote.sh health
scripts/qmt_bridge_remote.sh smoke --token <token>
```
- The wrapper uses Windows Task Scheduler task `CodexQmtBridge`, which must be `InteractiveToken` and call `D:\test\start_qmt_bridge_codex.bat`.
- Check the listener first: `ssh win "cmd /c netstat -ano | findstr :18080"`
- Health must be fast and must not call `xtdata.get_client()` unless `runtime=1`: `NO_PROXY='*' no_proxy='*' curl --noproxy '*' -m 5 -v http://192.168.2.2:18080/health`
- Run the safe smoke suite: `NO_PROXY='*' no_proxy='*' scripts/qmt_external_smoke.sh --url http://192.168.2.2:18080 --token <token>`
- The smoke suite covers `/health`, authenticated `/positions`, and authenticated `/rebalance` in `dry_run` mode twice with the same `request_id`.
- Only run execute after explicitly confirming the account is simulated and target weights/prices are tiny: `scripts/qmt_external_smoke.sh --execute --url http://192.168.2.2:18080 --token <token> --weights '{"510300.SH": 0.01}' --prices '{"510300.SH": 4.0}'`

### Known QMT Pitfalls From 2026-05-05
- Do not start the real bridge only through SSH. SSH-launched Python can run in a different Windows session from the logged-in QMT GUI and `XtQuantTrader.connect()` may return `-1`.
- `CodexQmtBridge` uses `InteractiveToken`; it cannot launch GUI/QMT if `query user` shows no logged-in interactive desktop user. In that state, only existing background bridge processes may respond; QMT GUI/API will not be recoverable by SSH alone.
- If `/health?runtime=1` fails after the user says QMT is open, remind them to start and log into the trading terminal too. The verified ready process set is `XtMiniQmt.exe`, `XtItClient.exe`, and `miniquote.exe`; seeing only `XtItClient.exe` is not enough.
- If TCP connects but `/health` or every request times out with no access log, the Python HTTP process is listening but stuck. Close the desktop bridge window and restart the bat from the interactive desktop.
- Windows console QuickEdit/text selection can pause the Python bridge while leaving the port open. Prefer launching `D:\test\start_qmt_bridge_codex.bat` with `pythonw.exe`; if a black console is already open and requests hang, press `Esc`/`Enter` or close it before restarting.
- If an old desktop process owns `18080`, SSH may not have permission to kill it. Ask the user to close the black bridge window; do not waste time with repeated `taskkill` attempts after access is denied.
- Always use `NO_PROXY='*' no_proxy='*'` and `curl --noproxy '*'` from macOS; otherwise proxy settings can obscure LAN diagnostics.
- `/health` is intentionally a process check by default. Use `/health?runtime=1` only when diagnosing QMT runtime because xtquant runtime checks can block.
- Real QMT calls must be isolated behind the worker-process timeout in `qmt_test_strategy/src/trader/qmt_trader.py`. Do not replace it with direct HTTP-thread calls to `xtquant`.
- A `503` with `connect QMT failed: -1` or `QMT worker timed out` means the bridge is healthy enough to respond; continue diagnosing QMT session/account/path instead of HTTP networking.
- When a temporary diagnostic port is used, kill it after testing, for example `ssh win "cmd /c netstat -ano | findstr :18082"` then `ssh win "cmd /c taskkill /PID <pid> /F"`.

See `docs/external_integration_tests.md` for the fuller checklist and command examples.

## Commit & PR Guidelines
- **Target branch**: `dev` (create feature branches from `dev`)
- **Commit message format**: Use bracketed tags like `[Add]`, `[Mod]`, `[Fix]`
- Include clear PR description with scope and test status
- Ensure `ruff check .` and `mypy vnpy` pass before submitting

## Safe Commit Workflow
- Stage explicitly: `git add <file1> <file2>` (avoid `git add .` when dirty)
- Pre-check staged: `git diff --cached --name-only`
- Run verification: `pytest <relevant-tests>` before commit
- Exclude from git: settings, API keys, `.env*`, secrets, runtime files
- Final check: `git status --short` shows only intended files

## Project Structure
- `vnpy/` - Core framework (trader, event engine, alpha module)
- `vnpy/trader/` - Main trading platform (engine, UI, objects)
- `vnpy/alpha/` - AI/ML quant strategies (dataset, model, strategy, lab)
- `vnpy/event/` - Event-driven engine
- `tests/` - pytest test files
- `examples/` - Sample strategies and notebooks
- `docs/` - Documentation (community/ and elite/ subdirs)

## Module File Index (Key Locations)
- CTA backtester UI: `vnpy_ctabacktester/ui/widget.py`
- CTA backtester engine: `vnpy_ctabacktester/engine.py`
- CTA backtester symbols: `vnpy_ctabacktester/symbols.py`
- Main window UI: `vnpy/trader/ui/mainwindow.py`
- Log monitor: `vnpy/trader/ui/widget.py`
- Alpha dataset: `vnpy/alpha/dataset/`
- Alpha models: `vnpy/alpha/model/models/`

## Localization (i18n)
- Translations in `vnpy/trader/locale/`
- Build hook compiles `.po` to `.mo` during build
- Use `_()` function for translatable strings
- Update translations when modifying UI text

## Configuration Files
- `pyproject.toml` - Build metadata, ruff, mypy, hatchling config
- No Cursor rules or Copilot instructions currently defined
