from typing import List, Dict
import pandas as pd
import numpy as np

def calculate_sharpe_ratio(returns: List[float], risk_free_rate: float = 0.0) -> float:
    """Calculate the Sharpe ratio of returns"""
    returns = pd.Series(returns)
    excess_returns = returns - risk_free_rate
    if len(returns) > 0:
        return np.sqrt(252) * excess_returns.mean() / returns.std()
    return 0.0

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
