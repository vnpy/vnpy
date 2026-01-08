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

## Configuration & Localization Notes
- Build metadata and tooling configuration live in `pyproject.toml`.
- Locale build hooks are defined under `vnpy/trader/locale/`; keep translations in sync when modifying UI text.
