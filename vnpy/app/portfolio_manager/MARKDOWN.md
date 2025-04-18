# Portfolio Manager Documentation

## Overview
The Portfolio Manager is a VeighNa application designed to manage and track trading portfolios, calculating PnL (Profit and Loss) across multiple contracts and providing real-time portfolio monitoring.

## Core Components

### PortfolioEngine (`engine.py`)
The main engine handling portfolio management operations.

#### Key Features
- Real-time portfolio tracking
- Trade processing and PnL calculation
- Automatic market data subscription
- Data persistence for positions and orders
- Event-driven architecture integration

#### Key Methods
- `process_trade_event`: Handles incoming trade events
- `process_timer_event`: Regular portfolio updates and calculations
- `save_data/load_data`: Position data persistence
- `save_order/load_order`: Order reference data persistence
- `set_timer_interval`: Configure update frequency

### ContractResult (`base.py`)
Manages individual contract positions and calculations.

#### Properties
- `reference`: Portfolio reference identifier
- `vt_symbol`: Contract symbol
- `open_pos`: Opening position
- `last_pos`: Current position
- `trading_pnl`: Realized PnL from trades
- `holding_pnl`: Unrealized PnL from positions
- `total_pnl`: Combined total PnL

#### Methods
- `update_trade`: Process new trades
- `calculate_pnl`: Calculate various PnL metrics
- `get_data`: Return current state as dictionary

### PortfolioResult (`base.py`)
Aggregates results across multiple contracts within a portfolio.

#### Properties
- `reference`: Portfolio identifier
- `trading_pnl`: Total realized PnL
- `holding_pnl`: Total unrealized PnL
- `total_pnl`: Combined portfolio PnL

## Usage Example

```python
# Initialize the engine
portfolio_engine = PortfolioEngine(main_engine, event_engine)

# Set update interval (in seconds)
portfolio_engine.set_timer_interval(5)

# Get portfolio results
portfolio = portfolio_engine.get_portfolio_result("PORTFOLIO_A")
print(f"Total PnL: {portfolio.total_pnl}")
```

## Event Types
- `EVENT_PM_CONTRACT`: Contract-level updates
- `EVENT_PM_PORTFOLIO`: Portfolio-level updates
- `EVENT_PM_TRADE`: Trade processing events

## Dependencies
- VeighNa Core (`vnpy.trader`)
- Event Engine (`vnpy.event`)
- JSON utilities for data persistence

## Data Persistence
The system maintains three JSON files:
- `portfolio_manager_setting.json`: Configuration settings
- `portfolio_manager_data.json`: Position data
- `portfolio_manager_order.json`: Order reference data

## Error Handling
- Robust duplicate trade filtering
- Null contract/tick data handling
- Date transition management for positions

## Performance Considerations
- Configurable update interval
- Efficient event processing
- Minimal memory footprint with selective market data subscription

## Technical Details

### Data Structures

#### ContractResult
```python
class ContractResult:
    reference: str              # Portfolio reference
    vt_symbol: str             # Contract symbol
    open_pos: int              # Opening position
    last_pos: int             # Current position
    trading_pnl: float        # Realized PnL
    holding_pnl: float        # Unrealized PnL
    total_pnl: float          # Total PnL
    trades: Dict[str, TradeData]  # Trade history
    long_volume: float        # Long position volume
    short_volume: float        # Short position volume
    long_cost: float         # Long position cost
    short_cost: float        # Short position cost
```

#### PortfolioResult
```python
class PortfolioResult:
    reference: str           # Portfolio identifier
    trading_pnl: float      # Total realized PnL
    holding_pnl: float      # Total unrealized PnL
    total_pnl: float        # Combined portfolio PnL
```

### Event Processing Flow

1. Trade Event Processing:
```python
Trade Event -> process_trade_event() -> ContractResult.update_trade() -> EVENT_PM_TRADE
```

2. Timer Event Processing:
```python
Timer Event -> process_timer_event() -> 
    ContractResult.calculate_pnl() -> 
    PortfolioResult aggregation -> 
    EVENT_PM_CONTRACT/EVENT_PM_PORTFOLIO
```

### Calculation Logic

#### Position Management
1. Position Types:
   - `open_pos`: Starting position for the day (carried from previous day)
   - `last_pos`: Current actual position after trades

2. Position Tracking:
   - Maintains separate long/short positions
   - Tracks cumulative volumes and costs
   - Updates on each trade

#### PnL Calculation Process

1. Trading PnL (Realized)
   ```python
   # Long positions
   long_value = long_volume * current_price * contract_size
   long_pnl = long_value - long_cost
   
   # Short positions
   short_value = short_volume * current_price * contract_size
   short_pnl = short_cost - short_value
   
   # Total trading PnL
   trading_pnl = long_pnl + short_pnl
   ```

2. Holding PnL (Unrealized)
   ```python
   # Based on open position from day start
   holding_pnl = (current_price - previous_close) * open_pos * contract_size
   ```

3. Total PnL
   ```python
   total_pnl = trading_pnl + holding_pnl
   ```

#### Trade Processing Flow
1. New Trade Arrival:
   - Validate trade is not duplicate
   - Update position (last_pos)
   - Store trade for PnL calculation

2. PnL Calculation Cycle:
   - Process new trades
   - Update costs and volumes
   - Calculate current values
   - Update PnL components

### Error Handling

#### Trade Processing
- Duplicate trade detection
- Invalid contract validation
- Position consistency checks

```python
# Example of trade processing with error handling
def process_trade(trade: TradeData) -> None:
    if trade.vt_tradeid in existing_trades:
        logger.warning(f"Duplicate trade ignored: {trade.vt_tradeid}")
        return
        
    if not validate_contract(trade.vt_symbol):
        logger.error(f"Invalid contract: {trade.vt_symbol}")
        return
```

### Advanced Usage Examples

#### Portfolio Performance Monitoring
```python
from vnpy.app.portfolio_manager import PortfolioEngine

def monitor_portfolio_performance(portfolio_engine: PortfolioEngine, threshold: float = -1000):
    """Monitor portfolio performance with alerts"""
    portfolio = portfolio_engine.get_portfolio_result("MAIN")
    
    if portfolio.total_pnl < threshold:
        logger.warning(f"Portfolio drawdown alert: {portfolio.total_pnl}")
        
    return {
        "trading_pnl": portfolio.trading_pnl,
        "holding_pnl": portfolio.holding_pnl,
        "total_pnl": portfolio.total_pnl
    }
```

#### Custom Position Management
```python
def manage_positions(engine: PortfolioEngine, reference: str):
    """Custom position management logic"""
    result = engine.contract_results.get((reference, vt_symbol))
    
    if result:
        current_pos = result.last_pos
        open_pos = result.open_pos
        position_delta = current_pos - open_pos
        
        return {
            "position_delta": position_delta,
            "trading_pnl": result.trading_pnl
        }
```

### Performance Optimization

#### Memory Management
- Selective market data subscription
- Efficient trade history cleanup
- Periodic data persistence

#### Latency Considerations
- Event processing priority
- Update frequency optimization
- Data structure access patterns

### Configuration Options

#### Timer Settings
```python
# Configure update frequency
engine.set_timer_interval(interval=5)  # 5-second updates

# High-frequency monitoring
engine.set_timer_interval(interval=1)  # 1-second updates
```

#### Data Persistence
```json
{
    "portfolio_manager_setting.json": {
        "timer_interval": 5
    },
    "portfolio_manager_data.json": {
        "date": "2023-01-01",
        "positions": {
            "PORTFOLIO_A,BTC-USD": {
                "open_pos": 1.0,
                "last_pos": 1.5
            }
        }
    }
}
```

### System Requirements

- Python 3.7+
- Memory: 4GB minimum recommended
- CPU: Multi-core processor recommended for high-frequency updates
- Network: Low-latency connection for real-time data

### Integration Guidelines

#### Event Engine Integration
```python
# Register custom event handlers
engine.event_engine.register(EVENT_PM_PORTFOLIO, custom_portfolio_handler)
engine.event_engine.register(EVENT_PM_CONTRACT, custom_contract_handler)
```

#### External System Integration
```python
# Export portfolio data
def export_portfolio_data(engine: PortfolioEngine, format: str = "csv"):
    data = {
        ref: result.get_data() 
        for ref, result in engine.portfolio_results.items()
    }
    return format_data(data, format)
```

### Testing Guidelines

#### Unit Tests
```python
def test_contract_result():
    engine = MockPortfolioEngine()
    result = ContractResult(engine, "TEST", "BTC-USD")
    
    # Test trade processing
    trade = create_mock_trade(direction=Direction.LONG, volume=1)
    result.update_trade(trade)
    assert result.last_pos == 1
    
    # Test PnL calculation
    result.calculate_pnl()
    assert result.total_pnl == result.trading_pnl + result.holding_pnl
```

### Troubleshooting

Common issues and solutions:
1. Missing market data
   - Check subscription status
   - Verify data source connectivity
   
2. Incorrect PnL calculations
   - Validate trade history
   - Check position consistency
   
3. Performance issues
   - Optimize update frequency
   - Review subscription list
   - Monitor memory usage
