# Repository Guidelines

## Project Structure & Module Organization
- `vnpy/` contains the core framework code (trader, apps, and alpha modules).
- `tests/` holds test cases (currently `tests/test_alpha101.py`).
- `examples/` provides sample strategies and usage patterns.
- `docs/` contains user and developer documentation.
- Install scripts live at the repo root (`install.sh`, `install_osx.sh`, `install.bat`).

## Build, Test, and Development Commands
- `bash install.sh` / `bash install_osx.sh` / `install.bat`: install VeighNa from source on Linux/macOS/Windows.
- `python -m pytest` or `pytest tests/test_alpha101.py`: run the test suite (pytest is used by the test module).
- `ruff check .`: run style and lint checks.
- `mypy vnpy`: run static type checks over the core package.

## Coding Style & Naming Conventions
- Python 3.10+ codebase; follow PEP 8 with `ruff` enforcing lint rules (E501 ignored).
- Type annotations are required in core modules; `mypy` is configured in `pyproject.toml` with strict settings.
- Prefer descriptive module names under `vnpy/` and keep test names aligned to files (e.g., `test_alpha101.py`).

## Testing Guidelines
- Framework: `pytest` (see `tests/test_alpha101.py` imports).
- Keep tests focused on deterministic data and small fixtures; reuse shared fixtures where possible.
- Name tests as `test_<feature>.py` and functions `test_<behavior>()`.

## Commit & Pull Request Guidelines
- Commit messages commonly use bracketed tags such as `[Add]` and `[Mod]` (see recent git history); follow this pattern.
- Development typically targets the `dev` branch; create feature branches from `dev` and open PRs back to `dev`.
- PRs should include a clear description, scope, and test status (commands run and results).

## Safe Commit Workflow (Reusable)
- Use narrow staging: `git add <explicit-file-list>`; avoid `git add .` when the working tree is dirty.
- Pre-check what will be committed: `git diff --cached --name-only` and `git diff --cached`.
- Keep local runtime files out of git: settings, API keys, `.env*`, secret json/yaml, private key files.
- Run focused verification before commit (for this repo typically `python -m pytest <targeted-tests>`).
- Final check before commit: `git status --short` should only include intended files in staged area.

## Personal Coding Habits Index
- Prefer adding small deterministic tests for new behavior before implementation.
- Keep strategy parameters explicit and configurable (avoid hidden constants).
- For order sizing, prefer reusable helpers in template/base classes over duplicated per-strategy formulas.
- When touching backtesting + live paths, add both interfaces to keep behavior consistent.

## Configuration & Localization Notes
- Build metadata and tooling configuration live in `pyproject.toml`.
- Locale build hooks are defined under `vnpy/trader/locale/`; keep translations in sync when modifying UI text.

## 模块-文件索引（用于减少重复检索）
- CTA回测 UI 入口/布局/交互：`vnpy_ctabacktester/ui/widget.py`
- CTA回测引擎（参数解析、合约配置、回测/下载流程）：`vnpy_ctabacktester/engine.py`
- CTA回测合约/候选标的辅助逻辑：`vnpy_ctabacktester/symbols.py`
- CTA回测 App 注册/元信息：`vnpy_ctabacktester/__init__.py`
- CTA回测脚本入口：`vnpy_ctabacktester/script/run.py`、`run.py`
- CTA回测文档入口：`docs/community/app/cta_backtester.md`
- CTA回测相关测试：`tests/test_backtester_contract_profile.py`、`tests/test_backtester_history_check.py`、`tests/test_backtester_symbol_candidates.py`
- CTA回测合约静态配置：`cta_backtester_contract_profiles.json`
- CTA回测合约参数自动同步（监听合约事件并持久化）：`vnpy_ctabacktester/engine.py`
- 主界面启动流程/菜单：`vnpy/trader/ui/mainwindow.py`

## 维护规则
- 当我为某个模块完成一次检索并确定主要入口文件后，追加到“模块-文件索引”中。
- 每次新增/修改模块时同步更新对应索引，避免下次重复检索。
