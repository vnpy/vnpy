"""Trading config loader with local-private override support."""

from __future__ import annotations

import json
from pathlib import Path
from typing import Any


DEFAULT_TRADING_CONFIG = Path(__file__).parent / "config" / "trading_config.json"


def _deep_merge(base: dict[str, Any], override: dict[str, Any]) -> dict[str, Any]:
    """Return base recursively overlaid with override."""
    merged = dict(base)
    for key, value in override.items():
        if isinstance(value, dict) and isinstance(merged.get(key), dict):
            merged[key] = _deep_merge(merged[key], value)
        else:
            merged[key] = value
    return merged


def resolve_trading_config_path(config_path: str | Path | None = None) -> Path:
    """Return local private config when it exists next to the public template."""
    path = Path(config_path) if config_path is not None else DEFAULT_TRADING_CONFIG
    local_path = path.with_name(f"{path.stem}.local{path.suffix}")
    if local_path.exists():
        return local_path
    return path


def load_trading_config(config_path: str | Path | None = None) -> dict[str, Any]:
    """Load JSON trading config, overlaying ignored local-private overrides."""
    path = Path(config_path) if config_path is not None else DEFAULT_TRADING_CONFIG
    local_path = resolve_trading_config_path(path)

    with path.open("r", encoding="utf-8") as f:
        config = json.load(f)

    if local_path != path:
        with local_path.open("r", encoding="utf-8") as f:
            config = _deep_merge(config, json.load(f))

    return config
