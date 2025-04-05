# Backtesting Module Documentation

## Purpose
This module provides a framework for backtesting factor-based trading strategies using historical price data.

## Components
- `Backtester`: Main class for executing backtests
- `BacktestingResult`: Data class for storing backtest results and metrics

## Usage Example
```python
from backtesting import Backtester
from your_factor_template import YourFactorTemplate
from datetime import datetime

# Initialize
factor = YourFactorTemplate()
backtester = Backtester(
    factor_template=factor,
    start_date=datetime(2022, 1, 1),
    end_date=datetime(2023, 1, 1)
)

# Load data
backtester.load_data(your_kline_data)

# Run backtest
backtester.calculate_factors()
result = backtester.run_backtest()

# Access results
print(f"Total Return: {result.metrics['total_return']:.2%}")
print(f"Sharpe Ratio: {result.metrics['sharpe_ratio']:.2f}")
```

## Dependencies
- pandas
- numpy
- logging
- datetime
- dataclasses

## Interface
The factor template must implement:
- `calculate(data: pd.DataFrame) -> pd.DataFrame`
- `generate_signal(data: pd.Series) -> float`
