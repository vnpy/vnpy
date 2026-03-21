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
