# Utility functions for factor management

from types import ModuleType
from typing import Any, Dict, Type, List
from vnpy.factor.template import FactorTemplate # Import for type hinting

from vnpy.trader.utility import load_json, save_json

def get_factor_class(module_to_search: ModuleType, class_name: str) -> Type:
    """
    Retrieves a factor class by its name from a specified module object.

    Parameters:
        module_to_search (ModuleType): The Python module object in which to find the class.
        class_name (str): Name of the class to load.

    Returns:
        The factor class object (Type).

    Raises:
        AttributeError: If the class_name is not found in the module_to_search.
    """
    try:
        return getattr(module_to_search, class_name)
    except AttributeError as e:
        error_msg = (f"Factor class '{class_name}' not found in module "
                     f"'{module_to_search.__name__}'.")
        # You might log this error or let the caller handle it.
        # Re-raising with more context is often good.
        raise AttributeError(error_msg) from e

def save_factor_setting(settings_list_to_save: List[Dict[str, Any]], setting_filename: str) -> None:
    """
    Saves a list of factor settings dictionaries to a JSON file.
    """
    save_json(setting_filename, settings_list_to_save)

def load_factor_setting(setting_path: str) -> List[Dict[str, Any]]:
    """
    Loads a list of factor settings dictionaries from a JSON file.
    """
    loaded_data = load_json(setting_path)
    if not isinstance(loaded_data, list):
        # Optional: Add handling for old dictionary format for backward compatibility
        # For now, enforce the new list format.
        raise TypeError(f"Factor settings file '{setting_path}' is not in the expected list format. "
                        f"Expected a list of factor settings, got {type(loaded_data)}.")
    # Further validation: check if all items in the list are dicts
    if not all(isinstance(item, dict) for item in loaded_data):
        raise ValueError(f"Factor settings file '{setting_path}' contains non-dictionary items in the list.")
    return loaded_data

def init_factors(
    module_for_primary_classes: ModuleType,
    settings_data: List[Dict[str, Any]], # THIS IS NOW A LIST OF ACTUAL SETTINGS DICTS
    dependencies_module_lookup_for_instances: ModuleType
) -> List[FactorTemplate]: # Updated return type hint
    initialized_factors: List[FactorTemplate] = [] # Explicitly type initialized_factors

    if not isinstance(settings_data, list): # Should be caught by load_factor_setting
        raise TypeError(f"init_factors expected settings_data to be a list, got {type(settings_data)}")

    for actual_factor_settings in settings_data: # Iterate directly over settings dicts
        if not isinstance(actual_factor_settings, dict):
            print(f"[FactorUtils] Warning: Expected a dict for factor settings, got {type(actual_factor_settings)}. Skipping.")
            continue

        class_name = actual_factor_settings.get("class_name")
        if not class_name:
            print(f"[FactorUtils] Warning: 'class_name' not found in factor settings: {actual_factor_settings}. Skipping.")
            continue

        try:
            FactorClass = get_factor_class(module_for_primary_classes, class_name)
        except AttributeError as e:
            print(f"[FactorUtils] Error initializing factor: {str(e)} Skipping.")
            continue

        instance = FactorClass(
            setting=actual_factor_settings,
            dependencies_module_lookup=dependencies_module_lookup_for_instances
        )
        initialized_factors.append(instance)
    return initialized_factors