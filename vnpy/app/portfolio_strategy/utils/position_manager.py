from typing import Dict, Optional
import pandas as pd
import numpy as np
from dataclasses import dataclass, field
import logging
from vnpy.trader.object import BarData

logger = logging.getLogger(__name__)

@dataclass
class PositionManager:
    """
    Manages position tracking and weight-based portfolio calculations
    
    DataFrame columns:
    - current: Current position in units
    - target: Target position in units  
    - price: Latest price
    - current_value: Current position value
    - target_value: Target position value
    - current_weight: Current portfolio weight
    - target_weight: Target portfolio weight
    """
    
    position_df: pd.DataFrame = field(default_factory=lambda: pd.DataFrame(
        columns=["current", "target", "price", 
                "current_value", "target_value",
                "current_weight", "target_weight"],
        dtype=float
    ).fillna(0.0))
    
    def __post_init__(self):
        """Initialize position tracking DataFrame"""
        required_cols = ["current", "target", "price", 
                        "current_value", "target_value",
                        "current_weight", "target_weight"]
        for col in required_cols:
            if col not in self.position_df.columns:
                self.position_df[col] = 0.0

    def get_position(self, vt_symbol: str) -> float:
        """Get current position for symbol"""
        if vt_symbol not in self.position_df.index:
            self.position_df.loc[vt_symbol] = 0.0
        return self.position_df.loc[vt_symbol, "current"]
    
    def set_position(self, vt_symbol: str, pos: float) -> None:
        """Update current position"""
        self.position_df.loc[vt_symbol, "current"] = pos
        
    def get_target(self, vt_symbol: str) -> float:
        """Get target position for symbol"""
        if vt_symbol not in self.position_df.index:
            self.position_df.loc[vt_symbol] = 0.0
        return self.position_df.loc[vt_symbol, "target"]
    
    def set_target(self, vt_symbol: str, target_weight: float) -> None:
        """Set target weight for a single symbol"""
        if vt_symbol not in self.position_df.index:
            self.position_df.loc[vt_symbol] = 0.0
        self.position_df.loc[vt_symbol, "target_weight"] = target_weight
        self._update_target_positions()

    def set_targets(self, target_weights: pd.Series) -> None:
        """
        Set target weights for multiple symbols at once
        
        Args:
            target_weights (pd.Series): Target weights indexed by vt_symbol
        """
        # Update target weights
        for vt_symbol, weight in target_weights.items():
            if vt_symbol not in self.position_df.index:
                self.position_df.loc[vt_symbol] = 0.0
            self.position_df.loc[vt_symbol, "target_weight"] = weight
            
        self._update_target_positions()

    def _update_target_positions(self) -> None:
        """Update target positions based on current target weights"""
        portfolio_value = self.get_portfolio_value()
        
        # Calculate target values and positions
        self.position_df["target_value"] = portfolio_value * self.position_df["target_weight"]
        price_series = self.position_df["price"]
        
        # Avoid division by zero
        self.position_df["target"] = np.where(
            price_series > 0,
            self.position_df["target_value"] / price_series,
            0.0
        )

    def update_price(self, vt_symbol: str, bar: BarData) -> None:
        """Update price and recalculate current values and weights"""
        if vt_symbol not in self.position_df.index:
            self.position_df.loc[vt_symbol] = 0.0
            
        # Update price and current value    
        self.position_df.loc[vt_symbol, "price"] = bar.close_price
        self.position_df.loc[vt_symbol, "current_value"] = (
            self.position_df.loc[vt_symbol, "current"] * bar.close_price
        )
        
        # Recalculate current weights
        self._update_current_weights()

    def get_price(self, vt_symbol: str) -> float:
        """Get latest price for symbol"""
        if vt_symbol not in self.position_df.index:
            self.position_df.loc[vt_symbol] = 0.0
        return self.position_df.loc[vt_symbol, "price"]

    def _update_current_weights(self) -> None:
        """Update current portfolio weights"""
        portfolio_value = self.get_portfolio_value()
        if portfolio_value > 0:
            self.position_df["current_weight"] = (
                self.position_df["current_value"] / portfolio_value
            )
        else:
            self.position_df["current_weight"] = 0.0

    def get_portfolio_value(self) -> float:
        """Get total portfolio value"""
        return self.position_df["current_value"].sum()

    def get_weight_changes(self) -> pd.Series:
        """Get required changes in portfolio weights"""
        return self.position_df["target_weight"] - self.position_df["current_weight"]
    
    def get_position_changes(self) -> pd.Series:
        """Get required changes in position units"""
        return self.position_df["target"] - self.position_df["current"]

    def get_value_changes(self) -> pd.Series:
        """Get required changes in position values"""
        return self.position_df["target_value"] - self.position_df["current_value"]
