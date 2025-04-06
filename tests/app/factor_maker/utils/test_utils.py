from datetime import datetime, timedelta
from typing import List, Dict
import numpy as np
import polars as pl
from vnpy.trader.object import BarData
from vnpy.trader.constant import Exchange, Interval

def generate_test_bars(symbols: List[str], 
                      days: int = 1, 
                      interval: Interval = Interval.MINUTE) -> List[Dict[str, BarData]]:
    """Generate fake bar data for testing"""
    current = datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)
    bars_by_time = []
    
    for day in range(days):
        current_day = current - timedelta(days=day)
        for minute in range(1):  # Generate 60 minutes of data for testing
            dt = current_day + timedelta(minutes=minute)
            bars = {}
            
            for symbol in symbols:
                close = 100 + np.random.normal(0, 1)
                bar = BarData(
                    symbol=symbol,
                    exchange=Exchange.TEST,
                    datetime=dt,
                    interval=interval,
                    volume=1000 * np.random.random(),
                    open_price=close * (1 + 0.001 * np.random.random()),
                    high_price=close * (1 + 0.002 * np.random.random()),
                    low_price=close * (1 - 0.002 * np.random.random()),
                    close_price=close,
                    gateway_name="TEST"
                )
                bars[symbol] = bar
                
            bars_by_time.append(bars)
            
    return bars_by_time
