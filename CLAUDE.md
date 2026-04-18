# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Development commands

- Install editable package:
  - `python3 -m pip install -e .`
- Install with optional Alpha dependencies:
  - `python3 -m pip install -e .[alpha]`
- Lint:
  - `python3 -m ruff check .`
  - `python3 -m ruff check vnpy tests`
- Type check:
  - `python3 -m mypy vnpy`
- Run tests:
  - `python3 -m pytest`
- Run a single test file:
  - `python3 -m pytest tests/test_alpha101.py`
- Run a single test case:
  - `python3 -m pytest tests/test_alpha101.py::TestAlpha101::test_alpha1`
- Build package:
  - `python3 -m pip install build`
  - `python3 -m build`
- Local install scripts in repo root:
  - macOS: `bash install.sh`
  - Linux: `bash install_osx.sh`
  - Windows: `install.bat`

Notes:
- `pyproject.toml` requires Python `>=3.10`; local shell may have lower Python, so use an appropriate interpreter/venv.
- Default install scripts use `https://pypi.vnpy.com` index and install TA-Lib prerequisites.

## High-level architecture

### Core runtime: event-driven trading kernel

- `vnpy/event/engine.py`: central event bus (`EventEngine`) with queue + timer thread (`EVENT_TIMER`).
- `vnpy/trader/engine.py`: `MainEngine` orchestrates gateways/apps and boots core engines (`LogEngine`, `OmsEngine`, `EmailEngine`).
- `vnpy/trader/gateway.py`: `BaseGateway` abstraction for broker/market adapters; all runtime data flows back as typed events (`on_tick`, `on_order`, `on_trade`, etc.).

How the pieces fit:
1. External gateway adapters receive market/trade updates.
2. Gateway pushes typed events into `EventEngine`.
3. OMS and UI monitors consume events, update in-memory state, and expose query APIs via `MainEngine` (`get_tick`, `get_order`, etc.).
4. Strategy/apps issue requests (`send_order`, `subscribe`, `query_history`) via `MainEngine` back to gateways.

### Trader app composition model

- `vnpy/trader/app.py`: `BaseApp` metadata contract (engine class, UI widget, icon, module path).
- `MainEngine.add_app()` instantiates app engines.
- `vnpy/trader/ui/mainwindow.py` dynamically loads each app’s UI module from `app_module + ".ui"`, then binds it into the main menu/toolbar.

Implication: most feature extensions are plug-in style (new gateway/app packages), while this repo hosts the framework contracts and built-in UI/kernel.

### Configuration and environment wiring

- `vnpy/trader/setting.py`: global `SETTINGS` defaults + runtime override from `vt_setting.json` in working directory.
- `MainEngine` switches cwd to `TRADER_DIR` on startup (`vnpy/trader/engine.py`), so runtime artifacts/settings are resolved from trader working directory.

### Data access abstraction layers

- `vnpy/trader/database.py`: database adapter boundary (`BaseDatabase`), loaded by `SETTINGS["database.name"]` via dynamic import (`vnpy_<name>`), fallback to `vnpy_sqlite`.
- `vnpy/trader/datafeed.py`: historical datafeed boundary (`BaseDatafeed`), loaded by `SETTINGS["datafeed.name"]` via dynamic import (`vnpy_<name>`), fallback to no-op base implementation.

These two modules are the key inversion points separating core framework from concrete storage/data vendors.

### AI/ML research subsystem (`vnpy.alpha`)

- `vnpy/alpha/lab.py`: `AlphaLab` manages end-to-end research workflow filesystem under a lab path (`daily/`, `minute/`, `dataset/`, `model/`, `signal/`, `component/`).
- Data is persisted as parquet and transformed with Polars; model/dataset abstractions live under `vnpy/alpha/dataset` and `vnpy/alpha/model`.
- Tests currently present in this repo are centered on alpha factor expression execution (`tests/test_alpha101.py`).

### Entry points/examples for manual runs

- `examples/veighna_trader/run.py`: canonical desktop bootstrap pattern (`create_qapp` → `EventEngine` → `MainEngine` → add gateways/apps → `MainWindow`).
- `README.md` also includes minimal `run.py` startup example and contribution checks (`ruff`, `mypy`).

## Repository-specific workflow cues

- Project metadata and tool config are in `pyproject.toml` (ruff + mypy settings, hatch build backend, optional `alpha` extra).
- README contribution flow references developing against `dev` branch in upstream PRs, even if local branch names differ.
