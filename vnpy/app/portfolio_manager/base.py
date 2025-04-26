import logging
from typing import Dict, List, TYPE_CHECKING, Optional, Union
from decimal import Decimal
import numpy as np
import pandas as pd
from datetime import datetime

from vnpy.trader.object import TickData, TradeData, ContractData
from vnpy.trader.constant import Direction

if TYPE_CHECKING:
    from .engine import PortfolioEngine

APP_NAME = "PortfolioManager"

class ContractResult:
    """
    Contract position and PnL calculator.
    
    Parameters
    ----------
    engine : PortfolioEngine
        The portfolio engine instance for market data access
    reference : str
        Portfolio reference identifier
    vt_symbol : str
        Virtual trading symbol for contract identification
    open_pos : int, optional
        Initial position at day start, defaults to 0
    
    Attributes
    ----------
    last_pos : int
        Current position after all trades
    trading_pnl : float
        Realized PnL from completed trades
    holding_pnl : float
        Unrealized PnL from open positions
    total_pnl : float
        Combined trading and holding PnL
    trades : Dict[str, TradeData]
        History of all processed trades
    new_trades : List[TradeData]
        Buffer for trades pending processing
    long_volume : float
        Total volume of long positions
    short_volume : float
        Total volume of short positions
    long_cost : float
        Total cost basis of long positions
    short_cost : float
        Total cost basis of short positions
    """

    def __init__(
        self,
        engine: "PortfolioEngine",
        reference: str,
        vt_symbol: str,
        open_pos: Union[float, int] = 0.0

    ) -> None:
        # Initialize logger
        self.logger = logging.getLogger(f"{APP_NAME}.ContractResult")
        
        # Add input validation
        assert isinstance(reference, str), "reference must be string"
        assert isinstance(vt_symbol, str), "vt_symbol must be string"
        assert isinstance(open_pos, Union[float, int]), "open_pos must be integer"
        
        super().__init__()

        self.engine: "PortfolioEngine" = engine

        self.reference: str = reference
        self.vt_symbol: str = vt_symbol

        self.open_pos: int = open_pos
        self.last_pos: int = open_pos

        self.value: float = 0

        self.trading_pnl: float = 0
        self.holding_pnl: float = 0
        self.total_pnl: float = 0

        self.trades: Dict[str, TradeData] = {}
        self.new_trades: List[TradeData] = []

        self.long_volume: float = 0
        self.short_volume: float = 0
        self.long_cost: float = 0
        self.short_cost: float = 0

    def update_trade(self, trade: TradeData) -> None:
        """
        Process new trade and update positions.
        
        Parameters
        ----------
        trade : TradeData
            Trade object containing:
            - vt_tradeid: str, unique trade identifier
            - direction: Direction, LONG or SHORT
            - volume: float, trade volume
            - price: float, trade price
        """
        # 过滤重复成交
        if trade.vt_tradeid in self.trades:
            return
        self.trades[trade.vt_tradeid] = trade
        self.new_trades.append(trade)

        if trade.direction == Direction.LONG:
            self.last_pos += trade.volume
        else:
            self.last_pos -= trade.volume

    def calculate_pnl(self) -> None:
        """
        Calculate PnL metrics for the contract.
        
        Required Market Data:
        - Current price (tick.last_price)
        - Previous close (tick.pre_close)
        - Contract size (contract.size)
        
        Updates
        -------
        - trading_pnl: float
        - holding_pnl: float
        - total_pnl: float
        
        Raises
        ------
        Logs errors for:
        - Missing contract data
        - Missing tick data
        """
        vt_symbol: str = self.vt_symbol

        # Add validation
        contract: Optional[ContractData] = self.engine.get_contract(vt_symbol)
        tick: Optional[TickData] = self.engine.get_tick(vt_symbol)
        if not contract:
            self.logger.error(f"Contract not found: {vt_symbol}")
            return
        if not tick:
            self.logger.debug(f"No tick data for: {vt_symbol}")
            return

        last_price: float = tick.last_price
        size: float = contract.size

        # calculate the contract value
        self.value: float = last_price * self.open_pos * size

        # 计算新成交额
        for trade in self.new_trades:
            trade_volume: float = trade.volume
            trade_cost: float = trade.price * trade_volume * size

            if trade.direction == Direction.LONG:
                self.long_cost += trade_cost
                self.long_volume += trade_volume
            else:
                self.short_cost += trade_cost
                self.short_volume += trade_volume

        self.new_trades.clear()

        # Calculate trading PnL
        long_value = self.long_volume * last_price * size
        long_pnl = long_value - self.long_cost
        short_value = self.short_volume * last_price * size
        short_pnl = self.short_cost - short_value
        self.trading_pnl = long_pnl + short_pnl

        # Calculate holding PnL using overnight positions (open_pos) 
        self.holding_pnl = (last_price - tick.open_price) * self.open_pos * size
        self.total_pnl = self.holding_pnl + self.trading_pnl

    def get_data(self) -> dict:
        """
        Get current state as dictionary.
        
        Returns
        -------
        dict
            Contains:
            - reference: str
            - vt_symbol: str
            - open_pos: int
            - last_pos: int
            - trading_pnl: float
            - holding_pnl: float
            - total_pnl: float
            - long_volume: float
            - short_volume: float
            - long_cost: float
            - short_cost: float
        """
        data: dict = {
            "reference": self.reference,
            "vt_symbol": self.vt_symbol,
            "open_pos": self.open_pos,
            "last_pos": self.last_pos,
            "trading_pnl": self.trading_pnl,
            "holding_pnl": self.holding_pnl,
            "total_pnl": self.total_pnl,
            "long_volume": self.long_volume,
            "short_volume": self.short_volume,
            "long_cost": self.long_cost,
            "short_cost": self.short_cost
        }
        return data


class PortfolioResult:
    """
    Portfolio level PnL aggregator.
    
    Parameters
    ----------
    reference : str
        Portfolio identifier
    
    Attributes
    ----------
    trading_pnl : float
        Aggregated realized PnL across all contracts
    holding_pnl : float
        Aggregated unrealized PnL across all contracts
    total_pnl : float
        Combined total PnL for portfolio
    """
    
    def __init__(self, reference: str) -> None:
        # Add validation
        assert isinstance(reference, str), "reference must be string"
        
        super().__init__()

        self.reference: str = reference
        self.trading_pnl: float = 0
        self.holding_pnl: float = 0
        self.total_pnl: float = 0
        self.value: float = 0

    def clear_pnl(self) -> None:
        """
        Reset all PnL values to zero.
        
        Used before recalculating portfolio totals.
        
        Returns
        -------
        None
        """
        self.trading_pnl = 0
        self.holding_pnl = 0
        self.total_pnl = 0

        self.value = 0

    def get_total_value(self) -> float:
        """
        Get total value of the portfolio.
        
        Returns
        -------
        float
            Total value of the portfolio
        """
        return self.value
    
    def get_data(self) -> dict:
        """
        Get current portfolio state.
        
        Returns
        -------
        dict
            Contains:
            - reference: str
            - trading_pnl: float
            - holding_pnl: float
            - total_pnl: float
        """
        data: dict = {
            "reference": self.reference,
            "trading_pnl": self.trading_pnl,
            "holding_pnl": self.holding_pnl,
            "total_pnl": self.total_pnl,
        }
        return data


class PortfolioStatistics:
    """
    Portfolio statistics calculator.
    
    Tracks precise portfolio value changes and calculates metrics like Sharpe Ratio and Max Drawdown.
    
    Attributes
    ----------
    daily_values : Dict[str, float]
        Records portfolio values with precise timestamps as strings (format: "%Y-%m-%d %H:%M:%S")
    """

    def __init__(self) -> None:
        self.daily_values: Dict[str, float] = {}

    def record_value(self, timestamp: str, value: float) -> None:
        """
        Record the portfolio value with a precise timestamp.
        
        Parameters
        ----------
        timestamp : str
            Timestamp in the format "%Y-%m-%d %H:%M:%S"
        value : float
            Portfolio value at the given timestamp
        """
        assert isinstance(timestamp, str), "timestamp must be a string"
        assert isinstance(value, (float, int)), "value must be a number"
        self.daily_values[timestamp] = value

    def resample_values(self, frequency: str = "D") -> pd.Series:
        """
        Resample the recorded values to a specified frequency.
        
        Parameters
        ----------
        frequency : str, optional
            Resampling frequency (e.g., "D" for daily, "H" for hourly), defaults to "D"
        
        Returns
        -------
        pd.Series
            Resampled portfolio values
        """
        if not self.daily_values:
            logging.warning("No data available for resampling.")
            return pd.Series(dtype=float)

        # Convert to pandas Series for resampling
        data = pd.Series(self.daily_values, dtype=float)
        data.index = pd.to_datetime(data.index, format="%Y-%m-%d %H:%M:%S")
        resampled_data = data.resample(frequency).last().fillna(method="ffill")
        return resampled_data

    def calculate_sharpe_ratio(self, risk_free_rate: float = 0.0, frequency: str = "D") -> Optional[float]:
        """
        Calculate the Sharpe Ratio based on resampled returns.
        
        Parameters
        ----------
        risk_free_rate : float, optional
            Risk-free rate for Sharpe Ratio calculation, defaults to 0.0
        frequency : str, optional
            Resampling frequency for returns, defaults to "D"
        
        Returns
        -------
        Optional[float]
            Sharpe Ratio, or None if insufficient data
        """
        resampled_data = self.resample_values(frequency)
        if len(resampled_data) < 2:
            logging.warning("Not enough data to calculate Sharpe Ratio.")
            return None

        daily_returns = resampled_data.pct_change().dropna()
        excess_returns = daily_returns - risk_free_rate / 252  # Assuming 252 trading days

        if daily_returns.std() == 0:
            logging.warning("Standard deviation of returns is zero.")
            return None

        sharpe_ratio = excess_returns.mean() / excess_returns.std()
        return sharpe_ratio

    def calculate_max_drawdown(self, frequency: str = "D") -> Optional[float]:
        """
        Calculate the maximum drawdown of the portfolio based on resampled values.
        
        Parameters
        ----------
        frequency : str, optional
            Resampling frequency for drawdown calculation, defaults to "D"
        
        Returns
        -------
        Optional[float]
            Maximum drawdown, or None if insufficient data
        """
        resampled_data = self.resample_values(frequency)
        if len(resampled_data) < 2:
            logging.warning("Not enough data to calculate Max Drawdown.")
            return None

        values = resampled_data.values
        peak = np.maximum.accumulate(values)
        drawdown = (values - peak) / peak
        max_drawdown = np.min(drawdown)
        return max_drawdown

    def get_statistics(self, frequency: str = "D") -> dict:
        """
        Get all calculated statistics based on resampled values.
        
        Parameters
        ----------
        frequency : str, optional
            Resampling frequency for statistics, defaults to "D"
        
        Returns
        -------
        dict
            Contains:
            - sharpe_ratio: Optional[float]
            - max_drawdown: Optional[float]
        """
        return {
            "sharpe_ratio": self.calculate_sharpe_ratio(frequency=frequency),
            "max_drawdown": self.calculate_max_drawdown(frequency=frequency),
        }
