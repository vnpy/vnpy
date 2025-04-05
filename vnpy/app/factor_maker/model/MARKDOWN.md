# Model Engine Documentation

## Purpose
The ModelEngine is designed to facilitate model training and evaluation using factor data. It provides functionality for:
- Loading and managing factor data
- Generating training labels
- Data preprocessing and normalization
- Feature engineering and combination
- Model training data preparation

## Components

### ModelEngine
Main engine for factor model management and training data preparation.

#### Constructor
```python
ModelEngine(
    main_engine: MainEngine,
    event_engine: EventEngine,
    label_generator: Optional[LabelGenerator] = None
)
```

#### Key Methods
```python
def add_factor(self, factor: FactorTemplate) -> None:
    """Add a factor to the model engine"""

def load_factor_data(self, factor_data: Dict[str, pl.DataFrame]) -> None:
    """Load factor data from backtesting or live calculation"""
    
def generate_labels(self, method: str = "returns", lookforward_period: int = 1) -> None:
    """Generate labels for training"""
    
def prepare_training_data(self, start_time: datetime, end_time: datetime) -> tuple[pl.DataFrame, pl.DataFrame]:
    """Prepare feature matrix and label vector for training"""
```

## Usage Examples

### Basic Model Training Setup
```python
from vnpy.app.factor_maker.model.engine import ModelEngine
from vnpy.app.factor_maker.template import FactorTemplate

# Initialize engine
model_engine = ModelEngine(main_engine, event_engine)

# Add factors
model_engine.add_factor(your_factor)

# Load factor data
factor_data = {
    "factor1": pl.DataFrame(...),
    "factor2": pl.DataFrame(...)
}
model_engine.load_factor_data(factor_data)

# Generate labels
model_engine.generate_labels(
    method="returns",
    lookforward_period=5
)

# Get training data
features, labels = model_engine.prepare_training_data(
    start_time=datetime(2023, 1, 1),
    end_time=datetime(2023, 12, 31)
)
```

### Custom Label Generation
```python
from vnpy.app.factor_maker.model.utils.label_generator import LabelGenerator

# Create custom label generator
class CustomLabelGenerator(LabelGenerator):
    def generate(self, price_data: pl.DataFrame, **kwargs) -> pl.DataFrame:
        # Your custom label logic here
        pass

# Use custom generator
model_engine = ModelEngine(
    main_engine=main_engine,
    event_engine=event_engine,
    label_generator=CustomLabelGenerator()
)
```

## Data Requirements

### Factor Data Format
- Must be a polars DataFrame
- Must contain a 'datetime' column
- Values should be numeric
- Missing values will be handled by preprocessing

### Label Data Format
- Must align with factor data datetime
- Can be returns, binary signals, or custom values
- Must be numeric values suitable for training

## Dependencies
- vnpy core framework
- polars for data processing
- numpy for numerical operations

## Error Handling
The engine includes comprehensive error checking for:
- Data format validation
- Missing value handling
- Date alignment
- Feature combination

## Performance Considerations
- Uses polars for efficient data processing
- Implements memory-efficient data structures
- Supports batch processing for large datasets

## Testing
```python
def test_model_engine():
    # Initialize
    engine = ModelEngine(main_engine, event_engine)
    
    # Add test factor
    factor = MockFactor()
    engine.add_factor(factor)
    
    # Test data loading
    test_data = {
        "factor1": pl.DataFrame({
            "datetime": [datetime(2023, 1, 1)],
            "value": [1.0]
        })
    }
    engine.load_factor_data(test_data)
    
    # Test label generation
    engine.generate_labels(method="returns", lookforward_period=1)
    
    # Test data preparation
    features, labels = engine.prepare_training_data(
        start_time=datetime(2023, 1, 1),
        end_time=datetime(2023, 1, 2)
    )
    
    assert isinstance(features, pl.DataFrame)
    assert isinstance(labels, pl.DataFrame)
```