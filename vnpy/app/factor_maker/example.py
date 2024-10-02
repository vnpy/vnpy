from datetime import datetime

from vnpy.app.factor_maker.backtesting import FactorOptimizer, FactorBacktestingEngine
from vnpy.trader.constant import Interval

# Create an instance of the backtesting engine
engine = FactorBacktestingEngine()

# Set up the MACD factor
macd_factor = MACDFactor()
macd_factor.factor_name = "MACD_Factor"

# Assign the factor to the engine
engine.factor = macd_factor

# Set backtesting parameters
engine.set_parameters(
    vt_symbols=["BTCUSDT.BINANCE", "ETHISDT.BINANCE"],  # Replace with your actual symbols
    start=datetime(2020, 1, 1),
    end=datetime(2021, 12, 31),
    interval=Interval.DAILY,
    commission_rate=0.0001,
    slippage=0.0001,
    size=1,
    price_tick=0.01
)

# Load data
engine.load_data()

# Define parameter bounds for optimization
param_bounds = {
    'fast_period': (5, 15),     # Fast EMA period between 5 and 15
    'slow_period': (20, 30),    # Slow EMA period between 20 and 30
    'signal_period': (5, 15)    # Signal EMA period between 5 and 15
}

# Create an instance of the optimizer
optimizer = FactorOptimizer(engine)

# Run the optimization with a Sharpe ratio threshold of 1.0
result = optimizer.optimize(
    param_bounds=param_bounds,
    init_points=5,
    n_iter=25,
    sharpe_threshold=1.0  # Adjust the threshold as needed
)

if result is not None:
    print(f"Best parameters found: {result['params']}")
    print(f"Sharpe Ratio on test data: {result['sharpe_ratio']}")
else:
    print("No parameters found that exceed the Sharpe ratio threshold on test data.")