# Repository Guidelines

## Project
VeighNa is a Python 3.12 quant trading framework. Keep this as a short index; put durable operational detail in docs, tests, or skill references.

## Core Commands
- Install: `pip install -e .`; dev: `pip install -e ".[dev]"`; test: `python -m pytest` or `pytest tests/<file>.py -q`.
- Lint/type: `ruff check .`, `ruff check --fix .`, `mypy vnpy`.
- Build: `python -m build`.

## Code Rules
- Follow existing module patterns before adding abstractions.
- Use typed Python 3.12 style: `str | None`, `collections.abc`, explicit returns.
- Imports: stdlib, third-party, local absolute, local relative.
- Names: `CamelCase` classes, `snake_case` functions/vars, `UPPER_SNAKE_CASE` constants.
- Public classes/methods need concise docstrings; avoid bare `except`.
- Do not commit secrets, `.env*`, private configs, runtime state, or credentials.

## Testing Rules
- Tests live under `tests/test_<feature>.py` with deterministic `test_<behavior>()` cases.
- Run focused tests for touched areas before commit; broaden when shared/runtime behavior changes.
- After OKX auto-trading, Telegram, risk/order routing, health, or Chan runtime changes, use the focused commands in `docs/troubleshooting/okx-auto-trading.md`.
- External QMT/OKX tests can touch real systems; follow docs first and require explicit intent for unsafe actions.

## Strategy Production
- Strategy skill: `/Users/miaoyuhan/.codex/skills/strategy-production/SKILL.md`.
- Core gate: `docs/strategy_testing_pipeline.md`.
- Sparse live fills: `docs/troubleshooting/strategy-live-trade-gap-diagnostics.md`.
- Chan adapter: `tools/chan_runtime_diagnostics.py`; generic method lives in the playbook above.
- Acceptance: `./.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate all`
- DoubleMA acceptance: `./.venv/bin/python tools/strategy_acceptance.py --strategy double_ma --gate all`

## Troubleshooting Index
- Start at `docs/troubleshooting/README.md`.
- OKX runtime: `docs/troubleshooting/okx-auto-trading.md`; malformed instruments: `docs/troubleshooting/okx-datafeed-malformed-instruments.md`.
- QMT GUI/session traps: `docs/troubleshooting/qmt-gui-session-xtquant-connect-minus-1.md`.
- External integration checklist: `docs/external_integration_tests.md`.
- Add a playbook entry when a reproducible external/runtime issue takes more than one diagnostic pass.

## Safe Commit Workflow
- Stage explicitly with `git add <file...>`; avoid `git add .`.
- Check staged files: `git diff --cached --name-only`.
- Run relevant verification before commit and report exact results.
- Commit messages use bracketed tags, e.g. `[Add]`, `[Mod]`, `[Fix]`; target branch is `dev`.

## Key Locations
- Core: `vnpy/`, `vnpy/trader/`, `vnpy/event/`, `vnpy/alpha/`.
- CTA: `vnpy_ctastrategy/`, `vnpy_ctabacktester/`.
- Runtime entry: `run_auto_trading.py`; health: `tools/okx_auto_health.py`.
- Config/build: `pyproject.toml`; translations: `vnpy/trader/locale/`.
