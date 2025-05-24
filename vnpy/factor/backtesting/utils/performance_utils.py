from typing import List, Dict
import pandas as pd
import numpy as np

def calculate_sharpe_ratio(returns: List[float], risk_free_rate: float = 0.0) -> float:
    """Calculate the Sharpe ratio of returns"""
    if not returns: # Handle empty list input early
        return 0.0

    returns_series = pd.Series(returns)
    excess_returns = returns_series - risk_free_rate
    
    # Sharpe ratio is undefined if standard deviation of returns is zero (e.g. all returns are the same)
    # or if there are no returns to calculate std dev (already handled by early exit).
    std_dev = returns_series.std()
    if std_dev == 0:
        return 0.0 # Or handle as appropriate, e.g. np.nan, or raise error

    ANNUALIZATION_FACTOR = 252 # Assuming daily returns for annualization
    sharpe = np.sqrt(ANNUALIZATION_FACTOR) * excess_returns.mean() / std_dev
    return sharpe

def calculate_drawdown(returns: List[float]) -> float:
    """Calculate the maximum drawdown from returns"""
    cumulative = pd.Series(returns).cumsum()
    return (cumulative - cumulative.cummax()).min()

def calculate_trade_stats(trades: List[Dict]) -> Dict:
    """Calculate trading statistics"""
    if not trades:
        return {}
        
    df = pd.DataFrame(trades)
    return {
        'total_trades': len(trades),
        'avg_trade_size': df['size'].mean(),
        'total_commission': df['cost'].sum(),
        'win_rate': len(df[df['type'] == 'buy']) / len(df) if len(df) > 0 else 0
    }
