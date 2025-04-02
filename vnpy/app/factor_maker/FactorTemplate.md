# Factor Maker Component

## Purpose
The `factor_maker` component is designed to manage and calculate financial factors used in trading strategies. It provides a flexible framework for defining, initializing, and managing factors with dependencies and parameters.

## Interface

### Classes

#### `FactorTemplate`
- **Description**: Abstract base class for defining factors.
- **Key Methods**:
  - `add_params(param_names: Union[str, List[str]], auto_property: bool = True)`: Add parameters to the factor.
  - `set_params(params_dict: Dict[str, Any])`: Set multiple parameters.
  - `get_params() -> dict`: Retrieve all parameters.
  - `calculate(input_data: Dict[str, pl.DataFrame], memory: Dict[str, pl.DataFrame]) -> pl.DataFrame`: Abstract method for calculating factor values.

#### `FactorParameters`
- **Description**: Utility class for managing factor parameters.
- **Key Methods**:
  - `set_parameters(params: Dict[str, Any])`: Set multiple parameters.
  - `get_parameter(name: str) -> Any`: Retrieve a parameter value.
  - `to_str(with_value: bool = False) -> str`: Convert parameters to a string representation.

### Utility Functions

#### `get_factor_class(class_name: str)`
- **Description**: Load a factor class by name.

#### `save_factor_setting(factors: Dict, setting_filename: str)`
- **Description**: Save factor settings to a JSON file.

#### `load_factor_setting(setting_path: str)`
- **Description**: Load factor settings from a JSON file.

#### `init_factors(f_setting: Dict)`
- **Description**: Initialize factors from settings.

## Usage Examples

### Defining a New Factor
```python
class MyFactor(FactorTemplate):
    def calculate(self, input_data, memory):
        # Custom calculation logic
        return result
```

### Managing Parameters
```python
factor = MyFactor()
factor.add_params(["param1", "param2"])
factor.set_params({"param1": 10, "param2": 20})
print(factor.get_params())
```

### Saving and Loading Settings
```python
from vnpy.app.factor_maker.utils.factor_utils import save_factor_setting, load_factor_setting

# Save settings
save_factor_setting(factors, "settings.json")

# Load settings
settings = load_factor_setting("settings.json")
```

## Dependencies
- `polars`: For data manipulation.
- `vnpy.trader.utility`: For JSON utilities.
- `logging`: For logging messages.

## Tests

### Example Test Case
```python
from vnpy.app.factor_maker.template import FactorTemplate

class TestFactor(FactorTemplate):
    def calculate(self, input_data, memory):
        return input_data["price"] * 2

factor = TestFactor()
factor.add_params("multiplier")
factor.set_params({"multiplier": 2})
assert factor.get_param("multiplier") == 2
```

### Running Tests
Tests can be found in the `tests` directory and executed using `pytest`.