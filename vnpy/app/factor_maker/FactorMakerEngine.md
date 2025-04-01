# Factor Maker Engine and Factor Template Documentation

## Factor Maker Engine

The **Factor Maker Engine** is a core component of the VeighNa framework, designed to facilitate the creation, management, and execution of financial factors for quantitative trading. It supports both backtesting and live trading modes, enabling users to develop and deploy custom factors efficiently.

### Features

- **Factor Management**: Supports initialization, execution, and stopping of factors.
- **Dependency Handling**: Automatically resolves and initializes factor dependencies.
- **Memory Management**: Maintains historical data (`memory_bar`) and factor results (`memory_factor`) for efficient calculations.
- **Event-Driven Architecture**: Processes market data and triggers factor calculations dynamically.
- **Dask Integration**: Builds computational graphs for parallelized factor calculations.
- **Backtesting and Live Modes**: Supports both historical data backtesting and real-time trading.

### Key Components

#### Initialization
The engine initializes all factors and their dependencies, sets up memory, and builds computational graphs.

```python
# Example of initialization
engine.init_engine(fake=False)
```

#### Memory Management
The engine maintains two types of memory:
- `memory_bar`: Stores historical bar data (e.g., open, high, low, close, volume).
- `memory_factor`: Stores calculated factor values.

#### Event Processing
The engine processes various events, such as market data updates and factor calculations.

#### Factor Execution
The engine executes factor calculations using a pre-built computational graph.

### Usage

1. **Initialization**: Call `init_engine()` with the appropriate settings.
2. **Adding Factors**: Define factors in the configuration file or programmatically.
3. **Running Calculations**: Automatically triggers calculations based on market data events.

---

## Factor Template

The **Factor Template** is an abstract base class that provides a standardized structure for creating custom factors. It defines the lifecycle, dependencies, and calculation logic for factors.

### Features

- **Parameter Management**: Supports dynamic parameter addition and retrieval.
- **Dependency Initialization**: Automatically initializes dependent factors.
- **Flexible Calculation**: Supports both Polars DataFrame and dictionary-based input formats.
- **Backtesting and Live Modes**: Adapts calculation logic based on the selected mode.

### Key Components

#### Initialization
The template initializes parameters, dependencies, and internal states.

#### Dependency Management
Dependencies are initialized and bound to the factor.

#### Parameter Management
Parameters can be dynamically added and retrieved.

#### Calculation
The `calculate` method defines the core logic for factor computation.

### Usage

1. **Creating a Custom Factor**: Inherit from `FactorTemplate` and implement the `calculate` method.

```python
class MyFactor(FactorTemplate):
    def calculate(self, input_data, memory, *args, **kwargs):
        # Custom calculation logic
```

2. **Defining Dependencies**: Specify dependent factors in the `dependencies_factor` attribute.

3. **Setting Parameters**: Add and set parameters dynamically.

---

This documentation provides an overview of the Factor Maker Engine and Factor Template, enabling users to develop and deploy custom factors effectively.