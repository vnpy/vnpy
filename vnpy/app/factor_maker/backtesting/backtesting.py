from typing import Dict, List, Optional, Any
import polars as pl
import numpy as np
import logging
from datetime import datetime
from dataclasses import dataclass, field
from vnpy.trader.constant import Interval
from vnpy.app.factor_maker.template import FactorTemplate
from vnpy.app.factor_maker.base import FactorMode

@dataclass
class BacktestingResult:
    """Stores backtesting results and performance metrics"""
    returns: List[float] = field(default_factory=list)
    positions: List[float] = field(default_factory=list)
    trades: List[Dict] = field(default_factory=list)
    metrics: Dict = field(default_factory=dict)

class Backtester:
    def __init__(
        self, 
        factor: FactorTemplate,
        init_capital: float = 1000000,
        commission_rate: float = 0.0003
    ):
        """Initialize backtester with a factor template"""
        self.factor = factor
        self.factor.factor_mode = FactorMode.Backtest
        self.init_capital = init_capital
        self.commission_rate = commission_rate
        
        # Data storage
        self.memory_bar: Dict[str, pl.DataFrame] = {}
        self.memory_factor: Dict[str, pl.DataFrame] = {}
        
        # Results
        self.result = BacktestingResult()
        self.logger = logging.getLogger(__name__)
        
    def init_memory(self) -> None:
        """Initialize memory structures for bar and factor data"""
        # Initialize basic OHLCV data memory
        data = {'datetime': []}
        schema = {'datetime': datetime}
        for b in ["open", "high", "low", "close", "volume"]:
            self.memory_bar[b] = pl.DataFrame(data=data, schema=schema)
            
        # Initialize factor memory including dependencies
        for factor_key in self._get_all_factor_keys():
            self.memory_factor[factor_key] = pl.DataFrame(data=data, schema=schema)
    
    def _get_all_factor_keys(self) -> List[str]:
        """Get all factor keys including dependencies"""
        keys = [self.factor.factor_key]
        for dep in self.factor.dependencies_factor:
            keys.extend(self._get_dependency_keys(dep))
        return list(set(keys))
    
    def _get_dependency_keys(self, factor: FactorTemplate) -> List[str]:
        """Recursively get dependency factor keys"""
        keys = [factor.factor_key]
        for dep in factor.dependencies_factor:
            keys.extend(self._get_dependency_keys(dep))
        return keys

    def load_data(self, kline_data: Dict[str, pl.DataFrame]) -> None:
        """Load and preprocess kline data"""
        assert set(kline_data.keys()) >= {"open", "high", "low", "close", "volume"}, \
            "Kline data must contain OHLCV data"
        
        self.memory_bar = kline_data
        self.logger.info(f"Loaded kline data with {len(kline_data['close'])} records")
        
    def calculate_factors(self) -> None:
        """Calculate factors using the provided template and its dependencies"""
        try:
            # Calculate dependent factors first
            for dep_factor in self.factor.dependencies_factor:
                self._calculate_dependency(dep_factor)
            
            # Calculate main factor
            result = self.factor.calculate(
                input_data=self.memory_bar,
                memory=self.memory_factor,
            )
            
            # Store result
            self.memory_factor[self.factor.factor_key] = result
            self.logger.info("Factor calculation completed")
            
        except Exception as e:
            self.logger.error(f"Factor calculation failed: {str(e)}")
            raise

    def _calculate_dependency(self, factor: FactorTemplate) -> None:
        """Calculate a dependency factor"""
        # Recursively calculate sub-dependencies first
        for dep in factor.dependencies_factor:
            self._calculate_dependency(dep)
            
        # Calculate this dependency
        result = factor.calculate(
            input_data=self.memory_bar,
            memory=self.memory_factor
        )
        self.memory_factor[factor.factor_key] = result

    def run_backtest(self) -> BacktestingResult:
        """Execute backtest based on factor signals"""
        position = 0
        capital = self.init_capital
        self.result.positions = []
        self.result.returns = []
        self.result.trades = []
        
        for idx, row in self.memory_bar['close'].iterrows():
            signal = self.factor.generate_signal(row)
            
            # Update position based on signal
            new_position = self._calculate_position(signal)
            if new_position != position:
                trade = self._execute_trade(position, new_position, row)
                self.result.trades.append(trade)
                position = new_position
                
            # Track results
            self.result.positions.append(position)
            returns = self._calculate_returns(position, row)
            self.result.returns.append(returns)
            
        self._calculate_metrics()
        return self.result
    
    def _calculate_position(self, signal: float) -> float:
        """Convert signal to position size"""
        return np.sign(signal)  # Simple -1, 0, 1 position sizing
        
    def _execute_trade(self, old_pos: float, new_pos: float, bar_data: pl.Series) -> Dict:
        """Execute trade and calculate transaction costs"""
        size = abs(new_pos - old_pos)
        cost = size * bar_data['close'] * self.commission_rate
        return {
            'timestamp': bar_data.name,
            'price': bar_data['close'],
            'size': size,
            'cost': cost,
            'type': 'buy' if new_pos > old_pos else 'sell'
        }
        
    def _calculate_returns(self, position: float, bar_data: pl.Series) -> float:
        """Calculate period returns based on position"""
        return position * (bar_data['close'] / bar_data['close_prev'] - 1)
        
    def _calculate_metrics(self) -> None:
        """Calculate performance metrics"""
        returns = pl.Series(self.result.returns)
        self.result.metrics = {
            'total_return': (1 + returns).prod() - 1,
            'annual_return': ((1 + returns).prod() - 1) * 252 / len(returns),
            'sharpe_ratio': returns.mean() / returns.std() * np.sqrt(252),
            'max_drawdown': (returns.cumsum() - returns.cumsum().cummax()).min(),
            'win_rate': sum(returns > 0) / len(returns)
        }
