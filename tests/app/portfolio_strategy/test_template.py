import pytest
import pandas as pd
from unittest.mock import Mock, patch

from vnpy.trader.constant import Direction, OrderType
from vnpy.trader.object import BarData, OrderData, TradeData
from vnpy.app.portfolio_strategy.template import StrategyTemplate


class SimpleStrategy(StrategyTemplate):
    """Simple strategy for testing"""
    required_factors = ["factor1", "factor2"]

    def calculate(self, df: pd.DataFrame) -> pd.Series:
        return pd.Series(0.1, index=df.index)  # Simple constant signal
        
    def project_signals_to_positions(self, signals: pd.Series) -> pd.Series:
        return signals  # Direct mapping


@pytest.fixture
def strategy():
    """Create a test strategy instance"""
    engine_mock = Mock()
    engine_mock.get_tick = Mock()
    engine_mock.get_bar = Mock()
    
    return SimpleStrategy(
        strategy_engine=engine_mock,
        strategy_name="test_strategy",
        vt_symbols=["BTC-USDT.BINANCE", "ETH-USDT.BINANCE"],
        state={}
    )

def test_strategy_initialization(strategy):
    """Test strategy initialization"""
    assert strategy.strategy_name == "test_strategy"
    assert len(strategy.vt_symbols) == 2
    assert strategy.inited is False
    assert strategy.trading is False

def test_state_management(strategy):
    """Test state saving and restoration"""
    # Setup initial state
    strategy.position_manager.set_position("BTC-USDT.BINANCE", 1.0)
    strategy.trading_config.position_multiplier = 2.0
    
    # Save state
    state = strategy.get_state()
    
    # Clear positions
    strategy.position_manager.set_position("BTC-USDT.BINANCE", 0.0)
    strategy.trading_config.position_multiplier = 1.0
    
    # Restore state
    strategy.restore_state(state)
    
    assert strategy.position_manager.get_position("BTC-USDT.BINANCE") == 1.0
    assert strategy.trading_config.position_multiplier == 2.0

def test_order_management(strategy):
    """Test order creation and management"""
    # Create mock bar data
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
    
    # Test order creation
    order_req = strategy._create_order_request(
        "BTC-USDT.BINANCE",
        Direction.LONG,
        OrderType.LIMIT,
        50000.0,
        1.0
    )
    
    assert order_req.symbol == "BTC-USDT.BINANCE"
    assert order_req.direction == Direction.LONG
    assert order_req.volume == 1.0

def test_position_updates(strategy):
    """Test position updates via trades"""
    # Create mock trade
    trade = TradeData(
        symbol="BTC-USDT",
        exchange="BINANCE",
        orderid="test",
        tradeid="test",
        direction=Direction.LONG,
        price=50000.0,
        volume=1.0,
        datetime=pd.Timestamp.now(),
        gateway_name="BINANCE"
    )
    
    # Process trade
    strategy.on_trade(trade)
    
    # Verify position update
    assert strategy.position_manager.get_position("BTC-USDT.BINANCE") == 1.0
