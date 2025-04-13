from typing import Dict, List
from datetime import datetime
import pandas as pd
import numpy as np
import logging

from vnpy.trader.object import BarData, TradeData, Direction

logger = logging.getLogger(__name__)

class PortfolioTracker:
    """Portfolio tracking system using DataFrame for positions and dict for portfolio state"""
    
    def __init__(self) -> None:
        # Position tracking with DataFrame
        self.position_df = pd.DataFrame(
            columns=[
                "current", "target", "price", "avg_price",
                "target_weight", "target_value",
                "realized_pnl", "unrealized_pnl"
            ],
            dtype=float
        ).fillna(0.0)
        
        # Portfolio state with dict
        self.portfolio_state = {
            "total_value": 0.0,
            "initial_capital": 0.0,
            "trading_pnl": 0.0,
            "holding_pnl": 0.0,
            "total_pnl": 0.0
        }
        
        # Historical tracking with list
        self.portfolio_values: List[Dict] = []
        
        # Time tracking
        self.last_update_time: datetime = datetime.now()

    def get_position(self, vt_symbol: str) -> float:
        """Get current position"""
        if vt_symbol not in self.position_df.index:
            self.position_df.loc[vt_symbol] = 0.0
        return self.position_df.loc[vt_symbol, "current"]

    def set_position(self, vt_symbol: str, volume: float) -> None:
        """Set position volume"""
        if vt_symbol not in self.position_df.index:
            self.position_df.loc[vt_symbol] = 0.0
        self.position_df.loc[vt_symbol, "current"] = volume

    def update_price(self, vt_symbol: str, bar: BarData) -> None:
        """Update price and calculate unrealized PnL"""
        if vt_symbol not in self.position_df.index:
            self.position_df.loc[vt_symbol] = 0.0
            
        self.position_df.loc[vt_symbol, "price"] = bar.close_price
        
        # Calculate unrealized PnL
        pos = self.position_df.loc[vt_symbol]
        self.position_df.loc[vt_symbol, "unrealized_pnl"] = (
            (bar.close_price - pos["avg_price"]) * pos["current"]
        )
        
        self._update_portfolio_state()
        self._record_portfolio_value()

    def update_trade(self, trade: TradeData) -> None:
        """Update position and PnL from trade"""
        vt_symbol = trade.vt_symbol
        if vt_symbol not in self.position_df.index:
            self.position_df.loc[vt_symbol] = 0.0
            
        current_pos = self.position_df.loc[vt_symbol, "current"]
        current_avg = self.position_df.loc[vt_symbol, "avg_price"]
        
        if trade.direction == Direction.LONG:
            new_pos = current_pos + trade.volume
            # Update average price for long positions
            if new_pos > 0:
                cost = current_avg * current_pos + trade.price * trade.volume
                new_avg = cost / new_pos
            else:
                new_avg = 0.0
                
            self.position_df.loc[vt_symbol, "current"] = new_pos
            self.position_df.loc[vt_symbol, "avg_price"] = new_avg
            
        else:  # SHORT
            new_pos = current_pos - trade.volume
            # Calculate realized PnL for short trades
            realized_pnl = (current_avg - trade.price) * trade.volume
            self.position_df.loc[vt_symbol, "realized_pnl"] += realized_pnl
            
            self.position_df.loc[vt_symbol, "current"] = new_pos
            # Keep average price if position remains, reset if closed
            if new_pos == 0:
                self.position_df.loc[vt_symbol, "avg_price"] = 0.0
        
        # Recalculate unrealized PnL
        if new_pos != 0 and trade.price > 0:
            self.position_df.loc[vt_symbol, "unrealized_pnl"] = (
                trade.price - self.position_df.loc[vt_symbol, "avg_price"]
            ) * new_pos
        
        # Update portfolio state
        self._update_portfolio_state()
        self._record_portfolio_value()
        
        logger.debug(
            f"Trade update for {vt_symbol}: {trade.direction} {trade.volume}@{trade.price}, "
            f"Position: {new_pos}, Avg Price: {self.position_df.loc[vt_symbol, 'avg_price']:.2f}"
        )

    def set_target_weights(self, target_weights: pd.Series) -> None:
        """Set target weights and calculate target positions"""
        # Normalize weights if needed
        if not np.isclose(target_weights.sum(), 1.0, rtol=1e-4):
            target_weights = target_weights / target_weights.sum()
        
        # Calculate targets    
        portfolio_value = self.portfolio_state["total_value"]
        
        for vt_symbol, weight in target_weights.items():
            if vt_symbol not in self.position_df.index:
                self.position_df.loc[vt_symbol] = 0.0
                
            price = self.position_df.loc[vt_symbol, "price"]
            target_value = portfolio_value * weight
            target_pos = target_value / price if price > 0 else 0.0
            
            self.position_df.loc[vt_symbol, "target_weight"] = weight
            self.position_df.loc[vt_symbol, "target_value"] = target_value
            self.position_df.loc[vt_symbol, "target"] = target_pos

    def get_position_changes(self) -> pd.Series:
        """Get required position changes"""
        changes = self.position_df["target"] - self.position_df["current"]
        return changes[abs(changes) > 1e-6]  # Filter small changes

    def _update_portfolio_state(self) -> None:
        """Update portfolio level metrics"""
        total_value = (self.position_df["current"] * self.position_df["price"]).sum()
        realized_pnl = self.position_df["realized_pnl"].sum()
        unrealized_pnl = self.position_df["unrealized_pnl"].sum()
        
        self.portfolio_state["total_value"] = total_value
        self.portfolio_state["trading_pnl"] = realized_pnl
        self.portfolio_state["holding_pnl"] = unrealized_pnl
        self.portfolio_state["total_pnl"] = realized_pnl + unrealized_pnl

    def _record_portfolio_value(self) -> None:
        """Record portfolio value snapshot"""
        self.portfolio_values.append({
            "timestamp": datetime.now(),
            "value": self.portfolio_state["total_value"]
        })

    def get_state(self) -> dict:
        """Get minimal state for persistence"""
        return {
            "positions": self.position_df.to_dict(orient="index"),
            "portfolio": {
                "total_value": self.portfolio_state["total_value"],
                "initial_capital": self.portfolio_state["initial_capital"],
                "total_pnl": self.portfolio_state["total_pnl"]
            }
        }

    def restore_state(self, state: dict) -> None:
        """Restore minimal state"""
        if "positions" in state:
            self.position_df = pd.DataFrame.from_dict(
                state["positions"], 
                orient="index"
            )
        
        if "portfolio" in state:
            self.portfolio_state.update(state["portfolio"])
