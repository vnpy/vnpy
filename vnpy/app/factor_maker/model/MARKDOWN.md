# Model Template Documentation

## Purpose
The ModelTemplate provides a base class for implementing factor models in the vnpy trading system. It handles:
- Feature data loading and preprocessing
- Label generation
- Training data preparation
- Model training and prediction interfaces

## Components

### ModelTemplate
Base template class for implementing factor models.

#### Constructor
```python
ModelTemplate(
    factor_keys: List[str],
    label_generator: Optional[LabelGenerator] = None,
    params: Optional[Dict[str, Any]] = None
)
```

#### Key Methods
```python
def load_features(self, factor_data: Dict[str, pl.DataFrame]) -> None:
    """Load and preprocess factor data"""

def generate_labels(
    self,
    price_data: pl.DataFrame,
    method: str = "returns",
    lookforward_period: int = 1
) -> None:
    """Generate labels for training"""

def prepare_data(
    self,
    start_time: datetime,
    end_time: datetime
) -> tuple[pl.DataFrame, pl.DataFrame]:
    """Prepare feature matrix and label vector"""

@abstractmethod
def train(self, features: pl.DataFrame, labels: pl.DataFrame, **kwargs) -> None:
    """Train the model - must be implemented by concrete classes"""

@abstractmethod
def predict(self, features: pl.DataFrame) -> Union[np.ndarray, pl.Series]:
    """Generate predictions - must be implemented by concrete classes"""
```

## Usage Examples

### Basic Model Implementation
```python
from vnpy.app.factor_maker.model.template import ModelTemplate
import polars as pl
import numpy as np
from sklearn.linear_model import LogisticRegression

class SimpleFactorModel(ModelTemplate):
    def __init__(self, factor_keys: List[str]):
        super().__init__(factor_keys=factor_keys)
        self.model = LogisticRegression()
        
    def train(self, features: pl.DataFrame, labels: pl.DataFrame, **kwargs):
        X = features.drop("datetime").to_numpy()
        y = labels.drop("datetime").to_numpy().ravel()
        self.model.fit(X, y)
        
    def predict(self, features: pl.DataFrame):
        X = features.drop("datetime").to_numpy()
        return self.model.predict_proba(X)[:, 1]
```

### Using the Model
```python
# Initialize model
model = SimpleFactorModel(factor_keys=["factor1", "factor2"])

# Load data
factor_data = {
    "factor1": pl.DataFrame(...),
    "factor2": pl.DataFrame(...)
}
model.load_features(factor_data)

# Generate labels from price data
price_data = pl.DataFrame(...)
model.generate_labels(
    price_data=price_data,
    method="returns",
    lookforward_period=5
)

# Prepare training data
features, labels = model.prepare_data(
    start_time=datetime(2023, 1, 1),
    end_time=datetime(2023, 12, 31)
)

# Train model
model.train(features, labels)

# Make predictions
predictions = model.predict(new_features)
```

## Data Requirements

### Feature Data
- Must be provided as Dict[str, pl.DataFrame]
- Each DataFrame must have a 'datetime' column
- Values should be numeric and preprocessed

### Label Data
- Must have matching datetime index with features
- Values should be appropriate for the model type (binary, continuous, etc.)

## Error Handling
The template includes comprehensive error handling for:
- Data validation
- Feature preprocessing
- Training data preparation
- Model operations

## Dependencies
- polars for data processing
- numpy for numerical operations
- logging for error tracking
- datetime for time management

## Testing
```python
def test_model_template():
    # Test data preparation
    model = SimpleFactorModel(factor_keys=["test_factor"])
    
    # Create test data
    factor_data = {
        "test_factor": pl.DataFrame({
            "datetime": [datetime(2023, 1, 1)],
            "value": [1.0]
        })
    }
    
    # Test feature loading
    model.load_features(factor_data)
    assert len(model.feature_data) > 0
    
    # Test label generation
    price_data = pl.DataFrame({
        "datetime": [datetime(2023, 1, 1)],
        "close": [100.0]
    })
    model.generate_labels(price_data)
    assert len(model.label_data) > 0
```

## Notes
- Models should be stateless during prediction
- Use appropriate data validation before training
- Consider using dependency injection for components like label generators
- Implement proper model persistence methods if needed
