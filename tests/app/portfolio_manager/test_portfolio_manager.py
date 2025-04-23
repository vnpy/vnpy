# tests/test_portfolio_manager.py

import pytest
from unittest.mock import MagicMock, patch, call
from datetime import datetime, date, timedelta, timezone
import pandas as pd
import numpy as np
import os
import logging
import sys
from unittest.mock import MagicMock

# Add the project root to the Python path
sys.path.append("/Users/chenzhao/Documents/crypto_vnpy")

# Mock missing modules if necessary
sys.modules['vnpy_portfoliomanager'] = MagicMock()
sys.modules['vnpy_portfoliomanager.engine'] = MagicMock()
sys.modules['vnpy_portfoliomanager.base'] = MagicMock()

from vnpy.event.engine import EVENT_TIMER
from vnpy.trader.constant import Direction, Status, Exchange
from vnpy.trader.event import EVENT_ORDER, EVENT_TRADE
from vnpy.trader.utility import get_file_path
from vnpy.event import Event
from vnpy.trader.object import OrderData, TradeData, TickData, ContractData
from vnpy.trader.utility import load_json, save_json

# Imports from the application module
# Assuming the app structure allows this import path
try:
    from vnpy.app.portfolio_manager.base_v2 import (
        ContractResult, PortfolioResult, PortfolioStatistics,
        DATE_KEY, DATA_KEY, OPEN_POS_KEY, LAST_POS_KEY, TIMER_INTERVAL_KEY,
        TIMESTAMP_FORMAT, logger as app_logger
    )
    from vnpy.app.portfolio_manager.engine_v2 import (
        PortfolioEngine, APP_NAME,
        EVENT_PM_CONTRACT, EVENT_PM_PORTFOLIO, EVENT_PM_TRADE, EVENT_PM_STATISTICS,
        SETTING_FILENAME, DATA_FILENAME, ORDER_FILENAME, STATS_FILENAME
    )
except ImportError as e:
    print(f"ImportError: {e}")
    raise

# Disable app's logging during tests unless needed for debugging
# app_logger.setLevel(logging.CRITICAL)

# --- Test Data Fixtures ---

@pytest.fixture
def sample_contract():
    """Provides a sample ContractData object."""
    return ContractData(
        symbol="BTCUSDT",
        exchange=Exchange.BINANCE,
        size=1.0,
        gateway_name="binance_spot_gateway"
    )

@pytest.fixture
def sample_tick():
    """Provides a sample TickData object."""
    return TickData(
        symbol="BTCUSDT",
        exchange=Exchange.BINANCE,
        last_price=35000.0,
        pre_close=34800.0,
        datetime=datetime.now()
    )

@pytest.fixture
def sample_trade_long(sample_contract):
    """Provides a sample LONG TradeData object."""
    return TradeData(
        symbol=sample_contract.symbol,
        exchange=sample_contract.exchange,
        tradeid="trade_long_001",
        orderid="order_001",
        direction=Direction.LONG,
        price=34900.0,
        volume=0.1,
        datetime=datetime.now(),
        reference="PF1"  # Ensure reference is set
    )

@pytest.fixture
def sample_trade_short(sample_contract):
    """Provides a sample SHORT TradeData object."""
    return TradeData(
        symbol=sample_contract.symbol,
        exchange=sample_contract.exchange,
        tradeid="trade_short_002",
        orderid="order_002",
        direction=Direction.SHORT,
        price=35100.0,
        volume=0.05,
        datetime=datetime.now(),
        reference="PF1"  # Ensure reference is set
    )

@pytest.fixture
def sample_order(sample_contract):
    """Provides a sample OrderData object."""
    return OrderData(
        symbol=sample_contract.symbol,
        exchange=Exchange.BINANCE,
        orderid="order_001",
        direction=Direction.LONG,
        price=34900.0,
        volume=0.1,
        status=Status.NOTTRADED,
        reference="PF1"  # Ensure reference is set
    )

@pytest.fixture
def mock_main_engine():
    """Fixture for a mocked MainEngine."""
    return MagicMock()

@pytest.fixture
def mock_event_engine():
    """Fixture for a mocked EventEngine."""
    return MagicMock()

@pytest.fixture
def portfolio_engine(mock_main_engine, mock_event_engine):
    """Fixture to initialize PortfolioEngine with mocks."""
    return PortfolioEngine(mock_main_engine, mock_event_engine)

# --- Test Class for ContractResult ---

class TestContractResult:

    def test_initialization(self):
        cr = ContractResult("PF1", "SYM1.EX", open_pos=5.0)
        assert cr.reference == "PF1"
        assert cr.vt_symbol == "SYM1.EX"
        assert cr.open_pos == 5.0
        assert cr.last_pos == 5.0
        assert cr.trading_pnl == 0.0
        assert cr.holding_pnl == 0.0
        assert cr.open_price_basis == 0.0
        assert not cr.new_trades

    def test_update_trade(self, sample_trade_long, sample_trade_short):
        cr = ContractResult("PF1", sample_trade_long.vt_symbol, open_pos=1.0)
        # Long trade
        cr.update_trade(sample_trade_long)
        assert cr.last_pos == pytest.approx(1.0 + 0.1)
        assert len(cr.new_trades) == 1
        assert cr.new_trades[0] == sample_trade_long
        # Short trade
        cr.update_trade(sample_trade_short)
        assert cr.last_pos == pytest.approx(1.0 + 0.1 - 0.05)
        assert len(cr.new_trades) == 2
        assert cr.new_trades[1] == sample_trade_short
        # Duplicate trade
        cr.update_trade(sample_trade_long)
        assert cr.last_pos == pytest.approx(1.0 + 0.1 - 0.05) # No change
        assert len(cr.new_trades) == 2 # No change

    def test_calculate_pnl_holding_only(self, sample_contract, sample_tick):
        cr = ContractResult("PF1", sample_contract.vt_symbol, open_pos=0.1)
        cr.open_price_basis = sample_tick.pre_close # Assume basis is set

        result = cr.calculate_pnl(sample_tick, sample_contract)
        assert result is True
        expected_holding_pnl = (sample_tick.last_price - cr.open_price_basis) * cr.open_pos * sample_contract.size
        assert cr.holding_pnl == pytest.approx(expected_holding_pnl)
        assert cr.trading_pnl == pytest.approx(0.0)
        assert cr.total_pnl == pytest.approx(expected_holding_pnl)
        assert cr.value == pytest.approx(cr.last_pos * sample_tick.last_price * sample_contract.size)
        assert not cr.new_trades # Should be cleared

    def test_calculate_pnl_trading_only(self, sample_contract, sample_tick, sample_trade_long, sample_trade_short):
        cr = ContractResult("PF1", f"{sample_contract.symbol}.{sample_contract.exchange.value}", open_pos=0.0)
        cr.open_price_basis = sample_tick.pre_close # Basis shouldn't matter for trading PnL if open_pos=0

        # Simulate trades happening before PnL calc
        cr.update_trade(sample_trade_long) # Buy 0.1 @ 34900
        cr.update_trade(sample_trade_short) # Sell 0.05 @ 35100
        assert cr.last_pos == pytest.approx(0.05)

        result = cr.calculate_pnl(sample_tick, sample_contract) # Current price 35000
        assert result is True

        # Expected trading PnL:
        # Long side: (Current Value of Qty Bought) - (Cost of Buys)
        #   = (0.1 * 35000 * 1) - (0.1 * 34900 * 1) = (35000-34900)*0.1*1 = 100*0.1*1 = 10
        # Short side: (Proceeds from Sells) - (Current Value of Qty Sold)
        #   = (0.05 * 35100 * 1) - (0.05 * 35000 * 1) = (35100-35000)*0.05*1 = 100*0.05*1 = 5
        expected_trading_pnl = 10 + 5

        assert cr.trading_pnl == pytest.approx(expected_trading_pnl)
        assert cr.holding_pnl == pytest.approx(0.0) # open_pos is 0
        assert cr.total_pnl == pytest.approx(expected_trading_pnl)
        assert cr.value == pytest.approx(cr.last_pos * sample_tick.last_price * sample_contract.size) # 0.05 * 35000 * 1
        assert not cr.new_trades # Should be cleared

    def test_calculate_pnl_holding_and_trading(self, sample_contract, sample_tick, sample_trade_long):
        cr = ContractResult("PF1", f"{sample_contract.symbol}.{sample_contract.exchange.value}", open_pos=-0.05) # Start short
        cr.open_price_basis = sample_tick.pre_close # Basis = 34800
        cr.update_trade(sample_trade_long) # Buy 0.1 @ 34900. Last pos = -0.05 + 0.1 = 0.05
        assert cr.last_pos == pytest.approx(0.05)

        result = cr.calculate_pnl(sample_tick, sample_contract) # Current price 35000
        assert result is True

        # Holding PnL: (35000 - 34800) * (-0.05) * 1 = 200 * -0.05 * 1 = -10
        expected_holding_pnl = (sample_tick.last_price - cr.open_price_basis) * cr.open_pos * sample_contract.size
        assert cr.holding_pnl == pytest.approx(expected_holding_pnl)

        # Trading PnL (only long trade happened today)
        # Long side: (0.1 * 35000 * 1) - (0.1 * 34900 * 1) = 10
        # Short side: 0
        expected_trading_pnl = 10
        assert cr.trading_pnl == pytest.approx(expected_trading_pnl)

        assert cr.total_pnl == pytest.approx(expected_holding_pnl + expected_trading_pnl) # -10 + 15 = 5
        assert cr.value == pytest.approx(cr.last_pos * sample_tick.last_price * sample_contract.size) # 0.05 * 35000 * 1
        assert not cr.new_trades

    def test_calculate_pnl_missing_data(self, sample_contract, sample_tick):
        cr = ContractResult("PF1", sample_contract.vt_symbol, open_pos=0.1)
        assert cr.calculate_pnl(None, sample_contract) is False # Missing tick
        assert cr.calculate_pnl(sample_tick, None) is False # Missing contract

    def test_rollover_day(self, sample_contract, sample_tick, sample_trade_long):
        cr = ContractResult("PF1", sample_contract.vt_symbol, open_pos=0.1)
        cr.open_price_basis = 34000.0
        cr.update_trade(sample_trade_long) # Buy 0.1 @ 34900. last_pos = 0.1 + 0.1 = 0.2
        cr.calculate_pnl(sample_tick, sample_contract) # last_price=35000, pre_close=34800
        # Store some PnL values before rollover
        trading_pnl_before = cr.trading_pnl
        holding_pnl_before = cr.holding_pnl
        assert trading_pnl_before != 0.0
        assert holding_pnl_before != 0.0

        prev_close_for_rollover = 35050.0 # Assume this was the actual close
        cr.rollover_day(prev_close_for_rollover)

        assert cr.open_pos == pytest.approx(0.2) # Updated to last_pos
        assert cr.last_pos == pytest.approx(0.2) # Remains the same until new trades
        assert cr.open_price_basis == pytest.approx(prev_close_for_rollover) # Updated
        # Intra-day counters reset
        assert cr.trading_pnl == 0.0
        assert cr.holding_pnl == 0.0
        assert cr.total_pnl == 0.0
        assert cr.value == 0.0
        assert cr.long_volume_traded == 0.0
        assert cr.short_volume_traded == 0.0
        assert cr.long_cost_traded == 0.0
        assert cr.short_cost_traded == 0.0
        assert not cr.new_trades

# --- Test Class for PortfolioStatistics ---

class TestPortfolioStatistics:

    def test_record_and_get_series(self):
        stats = PortfolioStatistics("PF1")
        dt1 = datetime(2025, 4, 22, 10, 0, 0)
        dt2 = datetime(2025, 4, 22, 11, 0, 0)
        stats.record_value(dt1, 10000.0)
        stats.record_value(dt2, 10100.0)

        series = stats.get_values_as_series()
        assert len(series) == 2
        assert series[dt1] == 10000.0
        assert series[dt2] == 10100.0
        assert isinstance(series.index, pd.DatetimeIndex)

    def test_resample_values(self):
        stats = PortfolioStatistics("PF1")
        dt1 = datetime(2025, 4, 22, 10, 0, 0)
        dt2 = datetime(2025, 4, 22, 14, 0, 0)
        dt3 = datetime(2025, 4, 23, 9, 30, 0)
        stats.record_value(dt1, 10000.0)
        stats.record_value(dt2, 10100.0) # Last value for day 1
        stats.record_value(dt3, 10050.0) # Last value for day 2

        daily_series = stats.resample_values("D")
        assert len(daily_series) == 2
        assert daily_series.index[0].date() == date(2025, 4, 22)
        assert daily_series.iloc[0] == 10100.0 # Takes last value of the day
        assert daily_series.index[1].date() == date(2025, 4, 23)
        assert daily_series.iloc[1] == 10050.0

    def test_persistence(self):
        stats = PortfolioStatistics("PF1")
        dt1 = datetime(2025, 4, 22, 10, 0, 0, 123456)
        dt2 = datetime(2025, 4, 22, 11, 0, 0, 654321)
        stats.record_value(dt1, 10000.0)
        stats.record_value(dt2, 10100.5)

        saved_data = stats.get_data_for_save()
        print(saved_data)
        assert dt1.strftime(TIMESTAMP_FORMAT) in saved_data
        assert dt2.strftime(TIMESTAMP_FORMAT) in saved_data
        assert saved_data[dt1.strftime(TIMESTAMP_FORMAT)] == 10000.0
        assert saved_data[dt2.strftime(TIMESTAMP_FORMAT)] == 10100.5

        new_stats = PortfolioStatistics.from_saved_data("PF1", saved_data)
        print(new_stats.values_over_time)
        assert len(new_stats.values_over_time) == 2
        assert dt1 in new_stats.values_over_time
        assert new_stats.values_over_time[dt1] == 10000.0
        assert new_stats.values_over_time[dt2] == 10100.5


# --- Test Class for PortfolioEngine ---

# Mock file paths for engine tests
MOCK_SETTING_PATH = get_file_path("mock_portfolio_manager_setting.json")
MOCK_DATA_PATH = get_file_path("mock_portfolio_manager_data.json")
MOCK_ORDER_PATH = get_file_path("mock_portfolio_manager_order.json")
MOCK_STATS_PATH = get_file_path("mock_portfolio_manager_statistics.json")

@pytest.fixture
def mock_main_engine(mocker):
    """Fixture for a mocked MainEngine."""
    engine = MagicMock()
    engine.get_tick = MagicMock(return_value=None)
    engine.get_contract = MagicMock(return_value=None)
    engine.subscribe = MagicMock()
    engine.write_log = MagicMock()
    return engine

@pytest.fixture
def mock_event_engine(mocker):
    """Fixture for a mocked EventEngine."""
    engine = MagicMock()
    engine.register = MagicMock()
    engine.unregister = MagicMock()
    engine.put = MagicMock()
    return engine

@pytest.fixture
def portfolio_engine(mocker, mock_main_engine, mock_event_engine):
    """Fixture to initialize PortfolioEngine with mocks and mocked file I/O."""
    # Mock file IO functions used by the engine
    mocker.patch('vnpy_portfoliomanager.engine_v2._load_json_file', return_value=None) # Default: files don't exist or are empty
    mocker.patch('vnpy_portfoliomanager.engine_v2.save_json', return_value=True)
    mocker.patch('vnpy_portfoliomanager.engine_v2.os.path.exists', return_value=False) # Default: files don't exist

    # Patch datetime to control time
    mock_now = datetime(2025, 4, 22, 10, 0, 0, tzinfo=timezone.utc) # Start time UTC
    mocker.patch('vnpy_portfoliomanager.engine_v2.datetime', MagicMock(now=MagicMock(return_value=mock_now)))
    mocker.patch('vnpy_portfoliomanager.engine_v2.date', MagicMock(today=MagicMock(return_value=mock_now.date()))) # Consistent local date mock if needed

    engine = PortfolioEngine(mock_main_engine, mock_event_engine)
    return engine

# --- Engine Test Cases ---

class TestPortfolioEngine:

    def test_process_order_event(self, portfolio_engine, sample_order):
        event = MagicMock(type=EVENT_ORDER, data=sample_order)
        portfolio_engine.process_order_event(event)
        assert portfolio_engine.order_reference_map[sample_order.vt_orderid] == sample_order.reference

        # Test idempotentcy (doesn't change if called again)
        portfolio_engine.process_order_event(event)
        assert portfolio_engine.order_reference_map[sample_order.vt_orderid] == sample_order.reference

        # Test adding reference back to order if missing
        sample_order.reference = None
        portfolio_engine.process_order_event(event)
        assert sample_order.reference == "PF1"


    def test_process_trade_event(self, portfolio_engine, mock_main_engine, mock_event_engine, sample_trade_long, sample_contract):
        # Setup: Order reference exists, contract exists
        portfolio_engine.order_reference_map[sample_trade_long.vt_orderid] = sample_trade_long.reference
        mock_main_engine.get_contract.return_value = sample_contract

        event = MagicMock(type=EVENT_TRADE, data=sample_trade_long)
        portfolio_engine.process_trade_event(event)

        # Check ContractResult created/updated
        key = (sample_trade_long.reference, sample_trade_long.vt_symbol)
        assert key in portfolio_engine.contract_results
        cr = portfolio_engine.contract_results[key]
        assert cr.last_pos == pytest.approx(sample_trade_long.volume) # Started at 0

        portfolio_engine.process_trade_event(event) # Process same trade again (should update pos if unique id)
        # Note: sample_trade_long fixture always creates same ID. Let's make a new one
        trade2 = MagicMock(spec=sample_trade_long, vt_tradeid="trade_long_002", vt_orderid=sample_trade_long.vt_orderid, volume=0.05, reference=sample_trade_long.reference, vt_symbol=sample_trade_long.vt_symbol, direction=Direction.LONG)
        event2 = MagicMock(type=EVENT_TRADE, data=trade2)
        portfolio_engine.process_trade_event(event2)
        assert cr.last_pos == pytest.approx(sample_trade_long.volume + 0.05)


    @patch('vnpy_portfoliomanager.base_v2.ContractResult.calculate_pnl') # Mock inner calc
    def test_timer_event_triggers_pnl(self, mock_calculate_pnl, portfolio_engine, mock_event_engine, sample_contract, sample_tick):
        # Setup: Add a contract result
        portfolio_engine.get_tick.return_value = sample_tick
        portfolio_engine.get_contract.return_value = sample_contract
        ref = "PF_Timer"
        key = (ref, sample_contract.vt_symbol)
        cr = ContractResult(ref, sample_contract.vt_symbol, open_pos=0.1)
        cr.open_price_basis = sample_tick.pre_close # Assume basis is set
        pr = PortfolioResult(ref)
        portfolio_engine.portfolio_results[ref] = pr
        portfolio_engine.contract_results[key] = cr
        mock_calculate_pnl.return_value = True # Assume calculation succeeds

        # Setup mocks for get_tick/get_contract
        portfolio_engine.main_engine.get_tick.return_value = sample_tick
        portfolio_engine.main_engine.get_contract.return_value = sample_contract

        # Simulate timer events past interval
        portfolio_engine.timer_interval = 3
        for i in range(portfolio_engine.timer_interval+2):
             portfolio_engine.process_timer_event(MagicMock(type=EVENT_TIMER))
        assert portfolio_engine.contract_results[key].total_pnl != 0.0 # PnL should be calculated