from typing import Dict, Any, Optional
import polars as pl
import numpy as np
from datetime import datetime

class LabelGenerator:
    """Generate labels for factor model training"""
    
    @staticmethod
    def calculate_returns(
        price_data: pl.DataFrame,
        lookforward_period: int = 1
    ) -> pl.DataFrame:
        """Calculate forward returns for specified period"""
        close_prices = price_data.select("close")
        fwd_returns = (close_prices.shift(-lookforward_period) / close_prices - 1)
        return fwd_returns.with_columns([price_data.select("datetime")])
        
    @staticmethod
    def calculate_excess_returns(
        price_data: pl.DataFrame,
        lookforward_period: int = 1,
        benchmark_data: Optional[pl.DataFrame] = None
    ) -> pl.DataFrame:
        """Calculate excess returns over benchmark"""
        returns = LabelGenerator.calculate_returns(price_data, lookforward_period)
        if benchmark_data is not None:
            benchmark_returns = LabelGenerator.calculate_returns(benchmark_data, lookforward_period)
            excess_returns = returns - benchmark_returns
            return excess_returns
        return returns
        
    def generate(
        self,
        price_data: pl.DataFrame,
        method: str = "returns",
        lookforward_period: int = 1,
        **kwargs
    ) -> pl.DataFrame:
        """Generate labels using specified method"""
        if method == "returns":
            return self.calculate_returns(price_data, lookforward_period)
        elif method == "excess_returns":
            return self.calculate_excess_returns(price_data, lookforward_period, kwargs.get("benchmark_data"))
        else:
            raise ValueError(f"Unsupported label generation method: {method}")
