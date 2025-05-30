# Utility functions for factor management

import importlib
import typing # Added import
from types import ModuleType
from typing import Any, Dict, Type, List
import re
import copy

if typing.TYPE_CHECKING:
    from vnpy.factor.template import FactorTemplate # Import for type hinting, made conditional

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
) -> List['FactorTemplate']: # Updated return type hint to string literal
    initialized_factors: List['FactorTemplate'] = [] # Explicitly type initialized_factors to string literal

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

def apply_params_to_definition_dict(
    definition_dict: Dict[str, Any], 
    params_with_paths: Dict[str, Any]
) -> Dict[str, Any]:
    """
    Applies a flat dictionary of path-based parameters to a factor definition dictionary.
    Modifies and returns a deep copy of the original definition_dict.
    Path keys are like "param_name" for root, "dependencies_factor[0].param_name" for a
    direct dependency's param, or "dependencies_factor[0].dependencies_factor[1].param_name" for nested.

    Args:
        definition_dict: The factor definition dictionary (JSON-like structure).
        params_with_paths: Flat dictionary with path-based keys and values to set.

    Returns:
        A new definition dictionary with updated parameters.
    """
    if not params_with_paths:
        return copy.deepcopy(definition_dict)

    new_def_dict = copy.deepcopy(definition_dict)

    for path_key, value_to_set in params_with_paths.items():
        path_parts = path_key.split('.')
        param_name_for_target_level = path_parts[-1]
        traversal_path_segments = path_parts[:-1] 

        current_target_for_traversal = new_def_dict # Correctly re-initialize for each path
        valid_path_so_far = True

        for segment in traversal_path_segments: 
            dep_match = re.fullmatch(r"dependencies_factor\[(\d+)\]", segment) 
            if dep_match:
                dep_index = int(dep_match.group(1))
                if "dependencies_factor" in current_target_for_traversal and \
                   isinstance(current_target_for_traversal["dependencies_factor"], list) and \
                   0 <= dep_index < len(current_target_for_traversal["dependencies_factor"]) and \
                   isinstance(current_target_for_traversal["dependencies_factor"][dep_index], dict):
                    current_target_for_traversal = current_target_for_traversal["dependencies_factor"][dep_index]
                else:
                    # print(f"Warning: Invalid path segment '{segment}' in '{path_key}' during traversal.") # Optional: Add logging
                    valid_path_so_far = False
                    break
            else: 
                # print(f"Warning: Unrecognized segment format '{segment}' in '{path_key}'.") # Optional: Add logging
                valid_path_so_far = False
                break
        
        if valid_path_so_far:
            if "params" not in current_target_for_traversal or \
               not isinstance(current_target_for_traversal["params"], dict):
                current_target_for_traversal["params"] = {} 
            current_target_for_traversal["params"][param_name_for_target_level] = value_to_set
        # else: print(f"Warning: Could not apply parameter for path '{path_key}' due to invalid path.") # Optional: Add logging

    return new_def_dict


"""if __name__ == "__main__":
    factor_setting = load_factor_setting("/Users/chenzhao/Documents/crypto_vnpy/vnpy/vnpy/factor/factor_maker_setting.json")
    factor_module = importlib.import_module("vnpy.factor.factors")
    factors = init_factors(
        module_for_primary_classes=factor_module,
        settings_data=factor_setting,
        dependencies_module_lookup_for_instances=factor_module
    )
    save_factor_setting(
        settings_list_to_save=[factor.to_setting() for factor in factors],
        setting_filename="/Users/chenzhao/Documents/crypto_vnpy/vnpy/vnpy/factor/factor_maker_setting.json"
    )"""