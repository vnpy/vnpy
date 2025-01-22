from typing import Optional, Union, Dict, Any

import polars as pl

from vnpy.app.factor_maker.base import FactorMode
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.trader.constant import Interval


class CLOSE(FactorTemplate):
    factor_name = 'close'
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, **kwargs):
        super().__init__(setting, **kwargs)

    def __init_dependencies__(self):
        pass

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]],
                  memory: Optional[pl.DataFrame] = None, *args, **kwargs) -> Any:
        if self.factor_mode not in [FactorMode.Backtest, FactorMode.Live]:
            raise ValueError("Invalid factor_mode. Must be 'Backtest' or 'Live'.")

        if isinstance(input_data, dict):
            close_data = input_data.get('close')
        elif isinstance(input_data, pl.DataFrame):
            close_data = input_data
        else:
            raise ValueError("Invalid input_data format. Expected pl.DataFrame or Dict[str, pl.DataFrame].")

        if not isinstance(close_data, pl.DataFrame):
            raise ValueError("'close' data must be a Polars DataFrame.")

        return close_data

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass


class XSMOM(FactorTemplate):
    factor_name = "xsmom"
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, window: int = None, **kwargs):
        """
        Initialize the XSMOM (cumulative return) factor.

        Parameters:
            setting: The configuration dictionary.
            window (int): The lookback window for cumulative returns.
        """
        super().__init__(setting, window=window, **kwargs)

    def __init_dependencies__(self):
        """
        Define the dependencies for XSMOM, which is the close price data.
        """
        self.close = CLOSE({})
        self.close.factor_mode = self.factor_mode
        setattr(self, 'dependencies_factor', [self.close])

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]], *args, **kwargs) -> pl.DataFrame:
        """
        Calculate the XSMOM (cumulative return) factor.

        Parameters:
            input_data: Input data containing 'close' prices (Polars DataFrame or dict).
            *args: Additional arguments.
            **kwargs: Additional keyword arguments.

        Returns:
            pl.DataFrame: DataFrame containing cumulative returns.
        """
        if isinstance(input_data, dict):
            close_data = input_data.get(self.close.factor_key)
        elif isinstance(input_data, pl.DataFrame):
            close_data = input_data
        else:
            raise ValueError("Invalid input_data format. Expected pl.DataFrame or Dict[str, pl.DataFrame].")

        if not isinstance(close_data, pl.DataFrame):
            raise ValueError("'close' data must be a Polars DataFrame.")

        # Ensure the window parameter is set
        window = self.params.get_parameter("window")
        if window is None:
            raise ValueError("The 'window' parameter must be set for XSMOM.")

        # Calculate cumulative returns over the lookback window
        cumulative_returns = close_data.select(
            [
                (pl.col(col) / pl.col(col).shift(window) - 1).alias(col)
                for col in close_data.columns if col != "datetime"
            ]
        )

        # Add datetime back to the cumulative returns DataFrame
        factor = pl.concat(
            [close_data.select(["datetime"]), cumulative_returns],
            how="horizontal"
        )

        return factor

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass


class RealVol(FactorTemplate):
    factor_name = "realized_vol"
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, window: int = None, **kwargs):
        """
        Initialize the Realized Volatility (RealVol) factor.

        Parameters:
            setting: The configuration dictionary.
            window (int): The lookback window for calculating volatility.
        """
        super().__init__(setting, window=window, **kwargs)

    def __init_dependencies__(self):
        """
        Define the dependencies for RealVol, which is the close price data.
        """
        self.close = CLOSE({})
        self.close.factor_mode = self.factor_mode
        setattr(self, 'dependencies_factor', [self.close])

    def calculate(self, input_data: Optional[Union[pl.DataFrame, Dict[str, Any]]], *args, **kwargs) -> pl.DataFrame:
        """
        Calculate the realized volatility factor.

        Parameters:
            input_data: Input data containing 'close' prices (Polars DataFrame or dict).
            *args: Additional arguments.
            **kwargs: Additional keyword arguments.

        Returns:
            pl.DataFrame: DataFrame containing realized volatility values.
        """
        if isinstance(input_data, dict):
            close_data = input_data.get(self.close.factor_key)
        elif isinstance(input_data, pl.DataFrame):
            close_data = input_data
        else:
            raise ValueError("Invalid input_data format. Expected pl.DataFrame or Dict[str, pl.DataFrame].")

        if not isinstance(close_data, pl.DataFrame):
            raise ValueError("'close' data must be a Polars DataFrame.")

        # Ensure the window parameter is set
        window = self.params.get_parameter("window")
        if window is None:
            raise ValueError("The 'window' parameter must be set for RealVol.")

        # Calculate returns
        returns = close_data.select(
            [
                (pl.col(col) / pl.col(col).shift(1) - 1).alias(col)
                for col in close_data.columns if col != "datetime"
            ]
        )

        # Calculate rolling standard deviation (realized volatility)
        realized_volatility = returns.select(
            [
                (pl.col(col).rolling_std(window)).alias(col)
                for col in returns.columns
            ]
        )

        # Add datetime back to the realized volatility DataFrame
        factor = pl.concat(
            [close_data.select(["datetime"]), realized_volatility],
            how="horizontal"
        )

        return factor

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass


class GRJMOM(FactorTemplate):
    factor_name = "grjmom"
    dependencies_factor = []
    freq = Interval.MINUTE
    factor_mode = FactorMode.Backtest

    def __init__(self, setting, xsmom_window: int = None, realvol_window: int = None, n_param: float = 1.0, **kwargs):
        """
        Initialize the GRJMOM (Generalized Risk-Adjusted Momentum) factor.

        Parameters:
            setting: The configuration dictionary.
            n_param (float): The tunable parameter for risk adjustment (e.g., 1 for Sharpe ratio, 2 for variance).
        """
        super().__init__(setting, xsmom_window=xsmom_window, realvol_window=realvol_window, n_param=n_param, **kwargs)

    def __init_dependencies__(self):
        """
        Define the dependencies for GRJMOM, which are XSMOM and RealVol.
        """
        self.xsmom = XSMOM({}, window=self.params.get_parameter("xsmom_window"))
        self.realvol = RealVol({}, window=self.params.get_parameter("realvol_window"))
        self.xsmom.factor_mode = self.factor_mode
        self.realvol.factor_mode = self.factor_mode
        setattr(self, 'dependencies_factor', [self.xsmom, self.realvol])

    def calculate(self, input_data: Optional[Dict[str, pl.DataFrame]], *args, **kwargs) -> pl.DataFrame:
        """
        Calculate the GRJMOM factor.

        Parameters:
            input_data: Input data containing XSMOM and RealVol values (Polars DataFrame or dict).
            *args: Additional arguments.
            **kwargs: Additional keyword arguments.

        Returns:
            pl.DataFrame: DataFrame containing GRJMOM factor values.
        """
        if not isinstance(input_data, dict):
            raise ValueError("Input data must be a dictionary containing XSMOM and RealVol data.")

        # Get XSMOM and RealVol data
        xsmom_data = input_data.get(self.xsmom.factor_key)
        realvol_data = input_data.get(self.realvol.factor_key)

        if xsmom_data is None or realvol_data is None:
            raise ValueError("Missing required input data for XSMOM or RealVol.")

        if not isinstance(xsmom_data, pl.DataFrame) or not isinstance(realvol_data, pl.DataFrame):
            raise ValueError("XSMOM and RealVol data must be Polars DataFrames.")

        # Extract the risk adjustment parameter
        n_param = self.params.get_parameter("n_param")
        if n_param is None:
            raise ValueError("The 'n_param' parameter must be set for GRJMOM.")

        if "datetime" in xsmom_data.columns and "datetime" in realvol_data.columns:
            datetime_col = xsmom_data["datetime"]
            realvol_data = realvol_data.drop("datetime")
            xsmom_data = xsmom_data.drop("datetime")

        n_pow = self.params.get_parameter('n_param')
        realvol_data = realvol_data.select([
            pl.col(col).pow(n_pow).alias(col) for col in realvol_data.columns
        ])
        # Calculate GRJMOM = XSMOM / (RealVol^n_param)
        grjmom_values = xsmom_data / realvol_data

        # Add datetime back to the GRJMOM DataFrame
        factor = grjmom_values.insert_column(0, datetime_col)

        return factor

    def calculate_polars(self, input_data: pl.DataFrame, *args, **kwargs) -> Any:
        pass


# Example usage with synthetic data

import yfinance as yf
import polars as pl

# Example usage
tickers = [
    "AAPL", "MSFT", "GOOG", "AMZN", "TSLA",  # Tech
    "META", "NFLX", "NVDA", "AMD", "INTC",  # Tech/Chipmakers
    "JPM", "BAC", "GS", "C", "WFC",  # Financials
    "XOM", "CVX", "SLB", "OXY", "BP",  # Energy
    "KO", "PEP", "MCD", "SBUX", "CMG",  # Consumer
    "UNH", "JNJ", "PFE", "MRK", "LLY",  # Healthcare
    "SPY", "QQQ", "DIA", "IWM", "VTI"  # ETFs
]
start_date = "2024-01-01"
end_date = "2024-12-01"
interval = "1d"  # 1-minute, 1-hour, or 1-day


def download_data(tickers: list, start: str, end: str, interval: str = "1m") -> Dict[str, pl.DataFrame]:
    """
    Download historical OHLCV data for given tickers from Yahoo Finance.

    Parameters:
        tickers (list): List of stock tickers to download data for.
        start (str): Start date in the format 'YYYY-MM-DD'.
        end (str): End date in the format 'YYYY-MM-DD'.
        interval (str): Data interval (e.g., '1m', '1h', '1d').

    Returns:
        Dict[str, pl.DataFrame]: A dictionary with keys ('open', 'high', 'low', 'close', 'volume').
    """
    # Download data from Yahoo Finance
    df = yf.download(
        tickers=" ".join(tickers),
        start=start,
        end=end,
        interval=interval,
        group_by="ticker"
    )

    # Reset index to ensure datetime is a column
    df = df.reset_index()

    # Initialize a dictionary to store Polars DataFrames for each OHLCV type
    ohlcv = {}

    # Map for OHLCV columns
    column_map = {
        "open": "Open",
        "high": "High",
        "low": "Low",
        "close": "Close",
        "volume": "Volume"
    }

    for key, suffix in column_map.items():
        # Filter columns with the given suffix (e.g., "Open", "High", etc.)
        relevant_columns = [col for col in df.columns if isinstance(col, tuple) and col[1] == suffix]

        # Create a Polars DataFrame for each OHLCV type
        ohlcv[key] = pl.DataFrame(
            {
                "datetime": df.iloc[:, 0],
                **{col[0]: df[col] for col in relevant_columns}  # Extract ticker names
            }
        )

    return ohlcv


raw_data = download_data(tickers, start=start_date, end=end_date, interval=interval)

# Add MACD factor example
grjmom = GRJMOM({}, xsmom_window=5, realvol_window=12, n_param=1)
grjmom.factor_mode = FactorMode.Backtest
# Perform calculations or integrate with optimizer or backtester

from vnpy.app.factor_maker.backtesting import FactorBacktester
from vnpy.app.factor_maker.optimizer import FactorOptimizer

# Step 1: Create Backtester
backtester = FactorBacktester(
    memory_bar=raw_data,  # Use synthetic OHLCV data
    commission_rate=0.001,
    slippage=0.001,
    trading_freq="1d"
)

# Step 2: Initialize Optimizer
optimizer = FactorOptimizer(backtester=backtester, memory_bar=raw_data)

# Step 3: Add Factor to Optimizer
optimizer.add_factor(grjmom)

# Step 4: Define Parameter Grid for Optimization
param_grid = {
    "n_param": [0.5, 1, 1.5]
}

# Step 5: Optimize Parameters
best_params = optimizer.optimize(param_grid, metric="Sharpe Ratio")

# Step 6: Display Optimization Results
print("Best Parameters:", best_params["best_params"])
print("Best Sharpe Ratio:", best_params["best_score"])

# Step 7: Perform Backtesting with Best Parameters
grjmom.set_params(best_params["best_params"])
factor_values = grjmom.calculate(optimizer.memory_factor)
performance_metrics = backtester.run_backtesting(factor_values, if_report=False)

# Step 8: Display Performance Metrics
print("\nPerformance Metrics:")
for metric, value in performance_metrics.items():
    print(f"{metric}: {value:.4f}")
