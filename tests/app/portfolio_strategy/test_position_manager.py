import pytest
import pandas as pd
import numpy as np

from vnpy.trader.object import BarData
from vnpy.app.portfolio_strategy.portfolio.portfolio_manager import PositionManager


@pytest.fixture
def position_manager():
    return PositionManager()

def test_position_updates(position_manager):
    """Test basic position updates"""
    position_manager.set_position("BTC-USDT.BINANCE", 1.0)
    assert position_manager.get_position("BTC-USDT.BINANCE") == 1.0
    
    # Test position value calculation
    bar = BarData(
        symbol="BTC-USDT",
        exchange="BINANCE",
        datetime=pd.Timestamp.now(),
        interval="1m",
        volume=1.0,
        open_price=50000.0,
        high_price=51000.0,
        low_price=49000.0,
        close_price=50000.0,
        gateway_name="BINANCE"
    )
    
    position_manager.update_price("BTC-USDT.BINANCE", bar)
    assert position_manager.position_df.loc["BTC-USDT.BINANCE", "value"] == 50000.0

def test_portfolio_weights(position_manager):
    """Test portfolio weight calculations"""
    # Setup positions and prices
    symbols = ["BTC-USDT.BINANCE", "ETH-USDT.BINANCE"]
    positions = [1.0, 10.0]
    prices = [50000.0, 3000.0]
    
    for symbol, pos, price in zip(symbols, positions, prices):
        position_manager.set_position(symbol, pos)
        bar = BarData(
            symbol=symbol,
            exchange="BINANCE",
            datetime=pd.Timestamp.now(),
            interval="1m",
            volume=1.0,
            close_price=price,
            gateway_name="BINANCE"
        )
        position_manager.update_price(symbol, bar)
    
    total_value = 50000.0 + 30000.0
    btc_weight = position_manager.position_df.loc["BTC-USDT.BINANCE", "weight"]
    eth_weight = position_manager.position_df.loc["ETH-USDT.BINANCE", "weight"]
    
    assert np.isclose(btc_weight, 50000.0/total_value)
    assert np.isclose(eth_weight, 30000.0/total_value)
