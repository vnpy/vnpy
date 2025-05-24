# -*- coding: utf-8 -*-
import json
from pathlib import Path
from typing import Any, Dict, List, Optional

_STRATEGY_SETTINGS_INITIALIZED = False

# Attempt to import global SETTINGS from vnpy.trader for root_path configuration
try:
    from vnpy.trader.setting import SETTINGS as VNPY_GLOBAL_SETTINGS
    from vnpy.trader.utility import load_json as vnpy_load_json_utility
except ImportError:
    print("Warning: [vnpy.strategy.setting] Failed to import from vnpy.trader.setting or .utility. Using fallbacks.")
    VNPY_GLOBAL_SETTINGS: Dict[str, Any] = {}
    # Basic load_json fallback for standalone if vnpy.trader.utility.load_json is not available
    def vnpy_load_json_utility(filename: str) -> dict:
        filepath = Path(filename)
        if filepath.exists() and filepath.is_file():
            with open(filepath, 'r', encoding='utf-8') as f:
                try: return json.load(f)
                except json.JSONDecodeError: print(f"Warning: JSONDecodeError in {filename}"); return {}
        return {}

# --- Base Paths ---
# This setting.py file's directory is the base for finding config files and the 'strategies' code module.
MODULE_DIR = Path(__file__).parent

# Root path for strategy-related data (models, persistent data)
# Can be overridden by global SETTINGS["strategy.root_path"]
DEFAULT_STRATEGY_ROOT_PATH = Path.cwd() / ".vnpy_strategy_data" # Default if not in global settings
STRATEGY_ROOT_PATH_STR = VNPY_GLOBAL_SETTINGS.get("strategy.root_path", str(DEFAULT_STRATEGY_ROOT_PATH))
ROOT_PATH = Path(STRATEGY_ROOT_PATH_STR)
MODEL_PATH = ROOT_PATH / "models"
DATA_PATH = ROOT_PATH / "data" # For other strategy-specific data persistence

# Ensure these paths exist
ROOT_PATH.mkdir(parents=True, exist_ok=True)
MODEL_PATH.mkdir(parents=True, exist_ok=True)
DATA_PATH.mkdir(parents=True, exist_ok=True)

# --- Module-level Globals for Strategy Settings ---
STRATEGY_ENGINE_OPERATIONAL_PARAMS: Dict[str, Any] = {}
STRATEGY_INSTANCES_FILEPATH: Optional[Path] = None

if not _STRATEGY_SETTINGS_INITIALIZED:
    # --- Default Operational Parameters for the Strategy Engine ---
    DEFAULT_OPERATIONAL_PARAMS = {
        # Assumes 'strategies' is a sub-package relative to this setting.py file
        "strategy_code_module_path": ".strategies", 
        "default_execution_gateway": "DEFAULT_GW",
        "init_max_workers": 1,
        "default_retrain_interval_days": 30,
        # Add other engine-level operational defaults here
    }

    # --- Fixed Filenames (relative to this module's directory) ---
    OPERATIONAL_PARAMS_FILENAME = "strategy_engine_config.json"
    STRATEGY_INSTANCES_FILENAME = "strategy_config.json"

    # --- Determine Full Paths ---
    operational_params_filepath = MODULE_DIR / OPERATIONAL_PARAMS_FILENAME
    STRATEGY_INSTANCES_FILEPATH = MODULE_DIR / STRATEGY_INSTANCES_FILENAME

    # --- Load and Merge Operational Parameters ---
    # 1. Start with hardcoded defaults
    STRATEGY_ENGINE_OPERATIONAL_PARAMS = DEFAULT_OPERATIONAL_PARAMS.copy()
    print(f"INFO: [vnpy.strategy.setting] Initialized with default operational parameters.")

    # 2. Load from strategy_engine_config.json (overrides defaults)
    if operational_params_filepath.exists():
        loaded_op_params = vnpy_load_json_utility(str(operational_params_filepath))
        if isinstance(loaded_op_params, dict):
            STRATEGY_ENGINE_OPERATIONAL_PARAMS.update(loaded_op_params)
            print(f"INFO: [vnpy.strategy.setting] Loaded operational parameters from {operational_params_filepath}.")
        else:
            print(f"Warning: [vnpy.strategy.setting] Content of {operational_params_filepath} is not a valid JSON object. Using defaults/previous values.")
    else:
        print(f"Warning: [vnpy.strategy.setting] Operational parameters file not found at {operational_params_filepath}. Using defaults. Please create it if needed.")

    # 3. Override with values from global VNPY_GLOBAL_SETTINGS (highest precedence for these specific keys)
    global_overrides_map = {
        # Global Key in VNPY_GLOBAL_SETTINGS : Local Key in STRATEGY_ENGINE_OPERATIONAL_PARAMS
        "strategy.code_module_path": "strategy_code_module_path", # e.g. "vnpy.app.cta_strategy.strategies"
        "strategy.default_gateway": "default_execution_gateway",
        "strategy.init_workers": "init_max_workers",
    }
    overridden_by_global = []
    for global_key, local_key in global_overrides_map.items():
        global_value = VNPY_GLOBAL_SETTINGS.get(global_key)
        if global_value is not None:
            STRATEGY_ENGINE_OPERATIONAL_PARAMS[local_key] = global_value
            overridden_by_global.append(local_key)
    if overridden_by_global:
        print(f"INFO: [vnpy.strategy.setting] Operational parameters overridden by global VNPY_SETTINGS: {overridden_by_global}")

    _STRATEGY_SETTINGS_INITIALIZED = True

def get_strategy_engine_operational_param(key: str, default: Optional[Any] = None) -> Any:
    """Get an operational parameter for the StrategyEngine."""
    return STRATEGY_ENGINE_OPERATIONAL_PARAMS.get(key, default)

def get_strategy_instance_definitions_filepath() -> Path:
    """
    Get the absolute path to the strategy instance definitions JSON file.
    This file lists the strategies to be loaded with their specific settings.
    """
    if STRATEGY_INSTANCES_FILEPATH is None: # Should be set during init
        print("CRITICAL ERROR: [vnpy.strategy.setting] STRATEGY_INSTANCES_FILEPATH is not set.")
        return MODULE_DIR / STRATEGY_INSTANCES_FILENAME # Fallback
    return STRATEGY_INSTANCES_FILEPATH

# Expose for use by the StrategyEngine and other components
__all__ = [
    "STRATEGY_ENGINE_OPERATIONAL_PARAMS",
    "get_strategy_engine_operational_param",
    "STRATEGY_INSTANCES_FILEPATH",
    "get_strategy_instance_definitions_filepath",
    "ROOT_PATH",
    "MODEL_PATH",
    "DATA_PATH"
]
