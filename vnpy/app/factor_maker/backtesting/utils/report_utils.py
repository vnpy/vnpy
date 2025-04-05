import json
from typing import Dict, Any, List
import numpy as np
import pandas as pd
import quantstats as qs
import plotly.graph_objects as go
from plotly.subplots import make_subplots
from pathlib import Path
import logging
from datetime import datetime

logger = logging.getLogger(__name__)

def generate_quant_stats_report(
    returns: List[float],
    positions: List[float],
    trades: List[Dict],
    benchmark_returns: List[float] = None,
    save_path: Path = None
) -> None:
    """Generate a comprehensive report using QuantStats"""
    # Convert returns to pandas Series
    returns_series = pd.Series(returns, name='Strategy')
    
    if benchmark_returns:
        benchmark_series = pd.Series(benchmark_returns, name='Benchmark')
        # Generate HTML report with benchmark comparison
        qs.reports.html(returns_series, 
                       benchmark=benchmark_series,
                       output=str(save_path),
                       title=f'Factor Performance Report')
    else:
        # Generate HTML report without benchmark
        qs.reports.html(returns_series,
                       output=str(save_path),
                       title=f'Factor Performance Report')

def create_tear_sheet(
    result: Dict[str, Any],
    factor_info: Dict[str, Any],
    save_path: Path
) -> None:
    """Create a detailed tear sheet with multiple analyses"""
    
    # Create returns series
    returns = pd.Series(result['returns'])
    
    # Basic metrics
    metrics = {
        'Total Return': f"{result['metrics']['total_return']:.2%}",
        'Annual Return': f"{result['metrics']['annual_return']:.2%}",
        'Sharpe Ratio': f"{result['metrics']['sharpe_ratio']:.2f}",
        'Max Drawdown': f"{result['metrics']['max_drawdown']:.2%}",
        'Win Rate': f"{result['metrics']['win_rate']:.2%}",
        'Total Trades': len(result['trades'])
    }
    
    # Additional QuantStats metrics
    metrics.update({
        'Sortino Ratio': f"{qs.stats.sortino(returns):.2f}",
        'Calmar Ratio': f"{qs.stats.calmar(returns):.2f}",
        'Max Consecutive Wins': qs.stats.consecutive_wins(returns),
        'Max Consecutive Losses': qs.stats.consecutive_losses(returns),
        'Profit Factor': f"{qs.stats.profit_factor(returns)::.2f}",
        'Average Win': f"{qs.stats.avg_win(returns):.2%}",
        'Average Loss': f"{qs.stats.avg_loss(returns):.2%}",
    })
    
    # Generate plots
    fig = make_subplots(
        rows=3, cols=2,
        subplot_titles=(
            'Cumulative Returns',
            'Drawdown',
            'Monthly Returns',
            'Return Distribution',
            'Rolling Sharpe',
            'Rolling Beta'
        ),
        vertical_spacing=0.1
    )
    
    # Plot 1: Cumulative Returns
    cum_returns = (1 + returns).cumprod()
    fig.add_trace(
        go.Scatter(y=cum_returns, name='Equity Curve'),
        row=1, col=1
    )
    
    # Plot 2: Drawdown
    drawdown = qs.stats.to_drawdown_series(returns)
    fig.add_trace(
        go.Scatter(y=drawdown, name='Drawdown', fill='tozeroy'),
        row=1, col=2
    )
    
    # Plot 3: Monthly Returns Heatmap
    monthly_returns = qs.stats.monthly_returns(returns)
    fig.add_trace(
        go.Heatmap(z=monthly_returns, name='Monthly Returns'),
        row=2, col=1
    )
    
    # Plot 4: Return Distribution
    fig.add_trace(
        go.Histogram(x=returns, name='Return Distribution', nbinsx=50),
        row=2, col=2
    )
    
    # Plot 5: Rolling Sharpe
    rolling_sharpe = qs.stats.rolling_sharpe(returns)
    fig.add_trace(
        go.Scatter(y=rolling_sharpe, name='Rolling Sharpe'),
        row=3, col=1
    )
    
    # Plot 6: Rolling Beta (if benchmark provided)
    rolling_volatility = returns.rolling(window=30).std() * np.sqrt(252)
    fig.add_trace(
        go.Scatter(y=rolling_volatility, name='Rolling Volatility'),
        row=3, col=2
    )
    
    # Update layout
    fig.update_layout(height=1200, showlegend=True, title_text="Factor Performance Analysis")
    
    # Save report
    with open(save_path, 'w') as f:
        f.write(f"""
        <html>
            <head>
                <title>Factor Backtest Report</title>
                <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet">
            </head>
            <body>
                <div class="container mt-5">
                    <h1>Factor Backtest Report</h1>
                    <h2>Factor Information</h2>
                    <div class="card mb-4">
                        <div class="card-body">
                            <h5>Factor Name: {factor_info['factor_name']}</h5>
                            <pre>{json.dumps(factor_info['parameters'], indent=2)}</pre>
                        </div>
                    </div>
                    
                    <h2>Performance Metrics</h2>
                    <div class="row">
                        {_generate_metric_cards(metrics)}
                    </div>
                    
                    <h2>Performance Charts</h2>
                    {fig.to_html(full_html=False)}
                </div>
            </body>
        </html>
        """)

def _generate_metric_cards(metrics: Dict[str, Any]) -> str:
    """Generate HTML for metric cards"""
    cards = []
    for name, value in metrics.items():
        cards.append(f"""
        <div class="col-md-3 mb-4">
            <div class="card">
                <div class="card-body">
                    <h5 class="card-title">{name}</h5>
                    <p class="card-text">{value}</p>
                </div>
            </div>
        </div>
        """)
    return "\n".join(cards)
