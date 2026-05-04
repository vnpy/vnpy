# CLAUDE.md - Disruptor Engine Development

## Build & Install
- Build Rust Extension: `cd vnpy-rs && PYO3_USE_ABI3_FORWARD_COMPATIBILITY=1 uv run maturin develop --release`
- Install Dependencies: `uv sync`

## Test Commands
- Full Suite: `uv run pytest tests/`
- Disruptor Integration: `uv run pytest tests/test_disruptor_integration.py -v -s`
- Performance Benchmarks: `uv run pytest tests/test_perf_specs.py -v -s`
- Wait Strategy Bench: `uv run python tests/bench_wait_strategies.py`
- Memory Stress Test: `uv run pytest tests/test_memory_leak.py -s -v`

## Production Settings
- Default Strategy: `blocking` (in `vnpy/trader/setting.py`)
- Default Buffer Size: `65536`

## Coding Standards
- Python: PEP8, use type hints, prefer factory pattern `create_engine()`
- Rust: Use `pyo3` bindings, ensure zero-copy logic, follow `rustfmt`
- Principles: SOLID, KISS, DRY, YAGNI
