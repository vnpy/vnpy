# CLAUDE.md - vnpy.event Python Implementation

## Event Engine Architecture
- **Factory Pattern**: Always use `create_engine()` to instantiate the engine. It handles feature-flag logic for Disruptor vs Legacy engines.
- **Engine Selection**: Controlled by `event.use_disruptor` in global settings.
- **Base Class**: All engines must inherit from `EventEngine` and maintain full API parity.

## Key Files
- `engine.py`: Base `EventEngine` class (Legacy Queue-based).
- `disruptor_engine.py`: `DisruptorEventEngine` (Python wrapper for the Rust extension).
- `__init__.py`: Factory and export logic.

## Test Commands
- API Parity: `uv run pytest tests/test_compatibility.py`
- Integration: `uv run pytest tests/test_disruptor_integration.py`
- E2E Logic: `uv run pytest tests/test_e2e_disruptor.py`

## Coding Standards
- Maintain type hints for all event handlers.
- Ensure `DisruptorEventEngine` correctly manages the lifecycle (start/stop) of the native producer.
- Avoid manual queue manipulation; use `put()` and `put_batch()`.
