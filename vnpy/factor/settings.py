from pathlib import Path
from typing import Any
from vnpy.trader.setting import SETTINGS

# Base paths
ROOT_PATH = Path(SETTINGS.get("factor.root_path", Path.home() / ".vnpy" / "factor"))
DATA_PATH = ROOT_PATH / "data"
CACHE_PATH = ROOT_PATH / "cache"
SETTINGS_PATH = ROOT_PATH / "settings"

# Ensure directories exist
for path in [ROOT_PATH, DATA_PATH, CACHE_PATH, SETTINGS_PATH]:
    path.mkdir(parents=True, exist_ok=True)

# Factor specific paths and settings
FACTOR_PATHS = {
    "factor_settings": SETTINGS_PATH / "factor_maker_setting.json",
    "factor_data_cache": CACHE_PATH / "factor_data_cache",
    "backtest_data_cache": CACHE_PATH / "backtest_factor_data_cache",
}

# Factor module settings
FACTOR_SETTINGS = {
    "module_name": SETTINGS.get("factor.module_name", "vnpy.factor.factors"),
    "datetime_col": SETTINGS.get("factor.datetime_col", "datetime"),
    "max_memory_length_bar": SETTINGS.get("factor.max_memory_length_bar", 100),
    "max_memory_length_factor": SETTINGS.get("factor.max_memory_length_factor", 500),
    "error_threshold": SETTINGS.get("factor.error_threshold", 3),
}

def get_factor_path(key: str) -> Path:
    """Get a factor-related path by key."""
    path = FACTOR_PATHS.get(key)
    if not path:
        raise KeyError(f"Path key '{key}' not found in FACTOR_PATHS")
    return path

def get_factor_setting(key: str) -> Any:
    """Get a factor-related setting by key."""
    value = FACTOR_SETTINGS.get(key)
    if value is None:
        raise KeyError(f"Setting key '{key}' not found in FACTOR_SETTINGS")
    return value
