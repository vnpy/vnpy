# Model Engine Utilities Documentation

## Purpose
Utility modules for the ModelEngine providing data preprocessing, label generation, and other helper functions.

## Components

### Preprocessing Utils
Located in `preprocessing.py`:

```python
normalize_features(df: pl.DataFrame) -> pl.DataFrame
"""Normalize features using z-score standardization"""

impute_missing_values(df: pl.DataFrame, method: str = "forward_fill") -> pl.DataFrame
"""Handle missing values in factor data"""
```

### Label Generator
Located in `label_generator.py`:

```python
class LabelGenerator:
    def generate(self, price_data: pl.DataFrame, **kwargs) -> pl.DataFrame:
        """Generate labels for model training"""
```

## Usage Examples

### Preprocessing
```python
from vnpy.app.factor_maker.model.utils.preprocessing import normalize_features

# Normalize factor data
normalized_data = normalize_features(factor_data)
```

### Label Generation
```python
from vnpy.app.factor_maker.model.utils.label_generator import LabelGenerator

generator = LabelGenerator()
labels = generator.generate(
    price_data=price_data,
    method="returns",
    lookforward_period=5
)
```

## Dependencies
- polars
- numpy
- logging

## Testing
```python
def test_preprocessing():
    # Test normalization
    data = pl.DataFrame({
        "datetime": [datetime(2023, 1, 1)],
        "value": [1.0]
    })
    normalized = normalize_features(data)
    assert "datetime" in normalized.columns
    
    # Test imputation
    data_with_nulls = pl.DataFrame({
        "datetime": [datetime(2023, 1, 1)],
        "value": [None]
    })
    imputed = impute_missing_values(data_with_nulls)
    assert imputed["value"].null_count() == 0
```