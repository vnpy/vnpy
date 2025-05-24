import json
from pathlib import Path
from typing import Any, Dict

_STRATEGY_SETTINGS_LOADED = False

try:
    from vnpy.trader.setting import SETTINGS
    from vnpy.trader.utility import load_json as load_json_main
except ImportError:
    SETTINGS: Dict[str, Any] = {}
    # Basic load_json fallback for standalone if vnpy.trader.utility.load_json is not available
    def load_json_fallback(filename: str) -> dict:
        filepath = Path(filename)
        if filepath.exists():
            with open(filepath, 'r', encoding='utf-8') as f:
                try:
                    return json.load(f)
                except json.JSONDecodeError:
                    print(f"Warning: JSONDecodeError in {filename}")
                    return {}
        return {}
    load_json_main = load_json_fallback

# Define module-level defaults that might be accessed before/outside the loading block
STRATEGY_MODULE_SETTINGS: Dict[str, Any] = {}
STRATEGY_DEFINITIONS_FILEPATH: Path = None  # For legacy template definitions (if ever needed side-by-side)
STRATEGY_INSTANCE_DEFINITIONS_FILEPATH: Path = None # For new strategy instance configurations

if not _STRATEGY_SETTINGS_LOADED:
    # Default filenames used if not specified in global SETTINGS or for standalone mode
    DEFAULT_STRATEGY_SETTINGS_FILENAME = "strategy_settings.json" # General module settings
    DEFAULT_STRATEGY_DEFINITIONS_FILENAME = "strategy_template_definitions.json" # Legacy template definitions
    DEFAULT_STRATEGY_INSTANCE_DEFINITIONS_FILENAME = "strategy_instance_settings.json" # New instance definitions

    # Root path of this module, used for resolving relative paths in standalone mode
    MODULE_ROOT_PATH = Path(__file__).parent

    # Determine the strategy settings file path
    _strategy_settings_file_path_str = SETTINGS.get("strategy.settings_file_path", DEFAULT_STRATEGY_SETTINGS_FILENAME)
    _strategy_settings_filepath = Path(_strategy_settings_file_path_str)
    if not _strategy_settings_filepath.is_absolute():
        _strategy_settings_filepath = MODULE_ROOT_PATH / _strategy_settings_filepath

    # Determine the strategy definitions file path
    _strategy_definitions_file_path_str = SETTINGS.get("strategy.definitions_file_path", DEFAULT_STRATEGY_DEFINITIONS_FILENAME)
    _temp_strategy_definitions_filepath = Path(_strategy_definitions_file_path_str)
    if not _temp_strategy_definitions_filepath.is_absolute():
        _temp_strategy_definitions_filepath = MODULE_ROOT_PATH / _temp_strategy_definitions_filepath
    STRATEGY_DEFINITIONS_FILEPATH = _temp_strategy_definitions_filepath

    # Determine the strategy instance definitions file path
    _strategy_instance_definitions_file_path_str = SETTINGS.get(
        "strategy.instance_definitions_file_path", DEFAULT_STRATEGY_INSTANCE_DEFINITIONS_FILENAME
    )
    _temp_strategy_instance_definitions_filepath = Path(_strategy_instance_definitions_file_path_str)
    if not _temp_strategy_instance_definitions_filepath.is_absolute():
        _temp_strategy_instance_definitions_filepath = MODULE_ROOT_PATH / _temp_strategy_instance_definitions_filepath
    STRATEGY_INSTANCE_DEFINITIONS_FILEPATH = _temp_strategy_instance_definitions_filepath # Assign to global


    # Load Strategy Module Settings from the JSON file
    _temp_strategy_module_settings: Dict[str, Any] = {}
    if _strategy_settings_filepath.exists():
        _temp_strategy_module_settings = load_json_main(str(_strategy_settings_filepath))
        if not isinstance(_temp_strategy_module_settings, dict): # Ensure it's a dict if file was empty or malformed
            print(f"Warning: Content of strategy settings file {_strategy_settings_filepath} is not a valid JSON object. Initializing with empty settings.")
            _temp_strategy_module_settings = {}
    else:
        print(f"Warning: Strategy settings file not found at {_strategy_settings_filepath}. Initializing with empty settings.")
    
    STRATEGY_MODULE_SETTINGS = _temp_strategy_module_settings # Assign to global

    # Override STRATEGY_MODULE_SETTINGS with values from global SETTINGS if they exist
    _keys_to_override = [
        "default_strategy_path",
        "default_retrain_interval_days"
        # Add other strategy-specific keys here if they become globally configurable
    ]
    for key in _keys_to_override:
        override_value = SETTINGS.get(f"strategy.{key}")
        if override_value is not None:
            STRATEGY_MODULE_SETTINGS[key] = override_value
    
    _STRATEGY_SETTINGS_LOADED = True

# Strategy specific paths (Minimal for now, can be expanded)
# Example: If strategies save models or specific logs to a configurable directory
# STRATEGY_DATA_PATH = Path(SETTINGS.get("strategy.data_path", MODULE_ROOT_PATH / "data"))
# STRATEGY_DATA_PATH.mkdir(parents=True, exist_ok=True)

def get_strategy_setting(key: str) -> Any:
    """
    Get a strategy-related setting by key.
    Checks STRATEGY_MODULE_SETTINGS.
    """
    value = STRATEGY_MODULE_SETTINGS.get(key)
    if value is None and key not in STRATEGY_MODULE_SETTINGS: # Check key existence for explicit None values
        raise KeyError(f"Setting key '{key}' not found in strategy module settings.")
    return value

def get_strategy_definitions_filepath() -> Path:
    """Get the absolute path to the (legacy) strategy template definitions JSON file."""
    return STRATEGY_DEFINITIONS_FILEPATH

def get_strategy_instance_definitions_filepath() -> Path:
    """Get the absolute path to the strategy instance definitions JSON file."""
    return STRATEGY_INSTANCE_DEFINITIONS_FILEPATH

# print(f"LOG: Strategy settings loaded. Legacy Definitions path: {STRATEGY_DEFINITIONS_FILEPATH}")
# print(f"LOG: Strategy Instance Definitions path: {STRATEGY_INSTANCE_DEFINITIONS_FILEPATH}")
# print(f"LOG: Strategy module config: {STRATEGY_MODULE_SETTINGS}")

__all__ = [
    "STRATEGY_MODULE_SETTINGS",
    "get_strategy_setting",
    "STRATEGY_DEFINITIONS_FILEPATH",
    "get_strategy_definitions_filepath",
    "STRATEGY_INSTANCE_DEFINITIONS_FILEPATH",
    "get_strategy_instance_definitions_filepath"
]
