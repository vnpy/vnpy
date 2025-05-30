import unittest
import copy
from typing import Dict, Any

from vnpy.factor.utils.factor_utils import apply_params_to_definition_dict

class TestFactorUtils(unittest.TestCase):

    def test_apply_params_to_root(self):
        """Test applying parameters to the root factor's params."""
        original_def = {
            "class_name": "RootFactor",
            "params": {"alpha": 10, "beta": 20},
            "dependencies_factor": []
        }
        params_to_apply = {"alpha": 15, "gamma": 30}
        
        expected_def = {
            "class_name": "RootFactor",
            "params": {"alpha": 15, "beta": 20, "gamma": 30}, # beta preserved, alpha updated, gamma added
            "dependencies_factor": []
        }
        
        new_def = apply_params_to_definition_dict(original_def, params_to_apply)
        self.assertEqual(new_def, expected_def)
        self.assertIsNot(new_def, original_def, "Should return a new dictionary instance.")
        self.assertEqual(original_def["params"]["alpha"], 10, "Original dictionary should not be modified.")

    def test_apply_params_to_direct_dependency(self):
        """Test applying parameters to a direct dependency."""
        original_def = {
            "class_name": "RootFactor",
            "params": {"root_param": 1},
            "dependencies_factor": [
                {
                    "class_name": "DepFactor1",
                    "params": {"dep1_paramA": 100, "dep1_paramB": 200}
                },
                {
                    "class_name": "DepFactor2",
                    "params": {"dep2_param": 300}
                }
            ]
        }
        params_to_apply = {"dependencies_factor[0].dep1_paramA": 150, "dependencies_factor[1].new_dep2_param": 350}
        
        expected_def = copy.deepcopy(original_def)
        expected_def["dependencies_factor"][0]["params"]["dep1_paramA"] = 150
        expected_def["dependencies_factor"][1]["params"]["new_dep2_param"] = 350
        
        new_def = apply_params_to_definition_dict(original_def, params_to_apply)
        self.assertEqual(new_def, expected_def)
        self.assertIsNot(new_def["dependencies_factor"][0]["params"], 
                         original_def["dependencies_factor"][0]["params"], 
                         "Params dict of dependency should be a new instance due to deepcopy.")
        self.assertEqual(original_def["dependencies_factor"][0]["params"]["dep1_paramA"], 100, 
                         "Original dependency param should not be modified.")


    def test_apply_params_to_nested_dependency(self):
        """Test applying parameters to a nested dependency."""
        original_def = {
            "class_name": "Root",
            "params": {},
            "dependencies_factor": [ # Root's deps = Level 0 deps
                { # Dep 0
                    "class_name": "DepL0_0",
                    "params": {"p_l0_0": 1},
                    "dependencies_factor": [ # Dep 0's deps = Level 1 deps
                        { # Dep 0.0
                            "class_name": "DepL1_0_0",
                            "params": {"p_l1_0_0": 10}
                        },
                        { # Dep 0.1
                             "class_name": "DepL1_0_1",
                             "params": {"p_l1_0_1": 20}
                        }
                    ]
                }
            ]
        }
        params_to_apply = {
            "dependencies_factor[0].dependencies_factor[1].p_l1_0_1": 25,
            "dependencies_factor[0].new_param_for_l0_0": 5
        }

        expected_def = copy.deepcopy(original_def)
        expected_def["dependencies_factor"][0]["dependencies_factor"][1]["params"]["p_l1_0_1"] = 25
        expected_def["dependencies_factor"][0]["params"]["new_param_for_l0_0"] = 5
        
        new_def = apply_params_to_definition_dict(original_def, params_to_apply)
        self.assertEqual(new_def, expected_def)
        self.assertEqual(original_def["dependencies_factor"][0]["dependencies_factor"][1]["params"]["p_l1_0_1"], 20)


    def test_invalid_paths_and_non_existent_dependencies(self):
        """Test behavior with invalid paths or non-existent dependencies."""
        original_def = {
            "class_name": "Root",
            "params": {"root_p": 1},
            "dependencies_factor": [
                {"class_name": "Dep1", "params": {"dep1_p": 10}}
            ]
        }
        # These paths should ideally not cause errors but simply not apply.
        # The function currently might create "params" if missing.
        params_to_apply = {
            "dependencies_factor[5].non_existent_param": 100, # Index out of bounds
            "invalid_segment.param": 200, # Invalid segment format
            "dependencies_factor[0].dependencies_factor[0].p": 300 # Dep[0] has no deps
        }
        
        # Expect no changes to original_def structure for these invalid paths
        # (or params dict might be added if it was missing at a valid path prefix)
        new_def = apply_params_to_definition_dict(original_def, params_to_apply)
        
        # Check for Dep[0]'s original param
        self.assertEqual(new_def["dependencies_factor"][0]["params"]["dep1_p"], 10)
        # Check if "dependencies_factor[0]" got a new "dependencies_factor" list or "params" for it.
        # Based on current apply_params_to_definition_dict, it won't create "dependencies_factor" list.
        # If "dependencies_factor[0].dependencies_factor[0].p" was applied, it means "params" was created.
        # The current logic would fail to traverse "dependencies_factor[0].dependencies_factor[0]"
        # because "dependencies_factor" list doesn't exist in `original_def["dependencies_factor"][0]`
        
        # We expect the definition to be largely unchanged by these invalid paths.
        # A more robust test might check for specific warnings if logging was added to the helper.
        # For now, check that original structure is preserved and no errors occurred.
        self.assertEqual(new_def["class_name"], original_def["class_name"])
        self.assertEqual(new_def["params"], original_def["params"])
        self.assertEqual(len(new_def["dependencies_factor"]), 1)
        self.assertEqual(new_def["dependencies_factor"][0]["params"], original_def["dependencies_factor"][0]["params"])


    def test_empty_params_to_apply(self):
        """Test passing an empty params_with_paths dict."""
        original_def = {"class_name": "MyFactor", "params": {"p1": 1}}
        new_def = apply_params_to_definition_dict(original_def, {})
        self.assertEqual(new_def, original_def)
        self.assertIsNot(new_def, original_def, "Should be a deepcopy.")

    def test_path_to_non_dict_dependency_element(self):
        """Test path pointing to a dependency that isn't a dict (should be skipped)."""
        original_def = {
            "class_name": "Root", "params": {},
            "dependencies_factor": [
                "DepAsStringNotDict" # Invalid dependency structure
            ]
        }
        params_to_apply = {"dependencies_factor[0].some_param": 123}
        new_def = apply_params_to_definition_dict(original_def, params_to_apply)
        # Expect no change as the path traversal will fail at the string element
        self.assertEqual(new_def, original_def)

    def test_params_key_missing_in_target_dict(self):
        """Test if 'params' key is correctly created if missing at target level."""
        original_def = {
            "class_name": "RootFactor",
            # "params": {} # 'params' key is missing
            "dependencies_factor": [
                {
                    "class_name": "DepFactor1"
                    # "params": {} # 'params' key missing in dependency
                }
            ]
        }
        params_to_apply = {
            "root_new_param": 77,
            "dependencies_factor[0].dep_new_param": 88
        }
        
        expected_def = {
            "class_name": "RootFactor",
            "params": {"root_new_param": 77},
            "dependencies_factor": [
                {
                    "class_name": "DepFactor1",
                    "params": {"dep_new_param": 88}
                }
            ]
        }
        new_def = apply_params_to_definition_dict(original_def, params_to_apply)
        self.assertEqual(new_def, expected_def)


if __name__ == '__main__':
    unittest.main()
