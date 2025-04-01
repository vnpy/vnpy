# Binance Spot Gateway Documentation

## Overview
The `BinanceSpotGateway` is a gateway implementation for the vn.py framework, designed to interface with Binance's spot trading API. It provides functionalities for connecting to Binance's REST and WebSocket APIs, managing orders, querying account and market data, and subscribing to real-time market updates.

## Key Features
- **REST API Integration**: Supports order placement, cancellation, account queries, and historical data retrieval.
- **WebSocket API Integration**: Provides real-time updates for trades, account changes, and market data.
- **Customizable Settings**: Allows configuration for live or testnet environments.
- **Efficient Data Handling**: Utilizes caching and optimized data structures for performance.

## Classes and Components

### 1. `BinanceSpotGateway`
This is the main gateway class that integrates REST and WebSocket APIs.

#### Attributes:
- `default_name`: Default name of the gateway.
- `default_setting`: Configuration settings for API keys and server type.
- `exchanges`: List of supported exchanges.

#### Methods:
- `connect(setting: dict)`: Connects to the Binance API using the provided settings.
- `subscribe(req: SubscribeRequest)`: Subscribes to market data.
- `send_order(req: OrderRequest)`: Places an order.
- `cancel_order(req: CancelRequest)`: Cancels an order.
- `query_account()`: Queries account balance.
- `query_position()`: Queries open positions.
- `query_history(req: HistoryRequest)`: Retrieves historical market data.
- `close()`: Closes all connections.

### 2. `BinanceSpotRestAPi`
Handles REST API interactions with Binance.

#### Key Methods:
- `connect(key: str, secret: str, server: str)`: Connects to the REST API.
- `query_time()`: Queries server time.
- `query_account()`: Retrieves account balance.
- `query_order()`: Fetches open orders.
- `query_contract()`: Retrieves contract information.
- `send_order(req: OrderRequest)`: Places an order.
- `cancel_order(req: CancelRequest)`: Cancels an order.
- `query_history(req: HistoryRequest)`: Fetches historical market data.

### 3. `BinanceSpotTradeWebsocketApi`
Handles WebSocket API interactions for trade-related data.

#### Key Methods:
- `connect(stream_url: str, listen_key: str)`: Connects to the WebSocket API.
- `on_packet(_, packet)`: Processes incoming WebSocket messages.
- `disconnect()`: Disconnects the WebSocket connection.

### 4. `BinanceSpotDataWebsocketApi`
Handles WebSocket API interactions for market data.

#### Key Methods:
- `connect(server: str)`: Connects to the WebSocket API for market data.
- `subscribe(req: SubscribeRequest)`: Subscribes to market data streams.
- `on_packet(_, packet: dict)`: Processes incoming market data messages.

### 5. `SpotWebsocketStreamClient_vnpy`
A custom WebSocket client for Binance's API.

#### Key Methods:
- `agg_trade(symbol: str)`: Subscribes to aggregate trade streams.
- `kline(symbol: str, interval: str)`: Subscribes to candlestick data streams.
- `ticker(symbol: str)`: Subscribes to ticker data streams.
- `partial_book_depth(symbol: str)`: Subscribes to order book depth streams.

## Configuration

### Default Settings
- `key`: API key for authentication.
- `secret`: API secret for authentication.
- `server`: Server type (`REAL` or `TESTNET`).

### System Mode
- `LIVE`: For live trading.
- `TEST`: For testing purposes.

## Usage

### Connecting to Binance
```python
from vnpy.event import EventEngine
from vnpy.trader.setting import SETTINGS

# Initialize event engine and gateway
event_engine = EventEngine()
gateway = BinanceSpotGateway(event_engine, "BINANCE_SPOT")

# Configure settings
settings = {
    "key": "your_api_key",
    "secret": "your_api_secret",
    "server": "REAL"
}

# Connect to Binance
gateway.connect(settings)
```

### Subscribing to Market Data
```python
from vnpy.trader.object import SubscribeRequest

# Create a subscription request
req = SubscribeRequest(
    symbol="BTCUSDT",
    exchange=Exchange.BINANCE
)

# Subscribe to market data
gateway.subscribe(req)
```

### Placing an Order
```python
from vnpy.trader.object import OrderRequest, Direction, OrderType

# Create an order request
order_req = OrderRequest(
    symbol="BTCUSDT",
    exchange=Exchange.BINANCE,
    direction=Direction.LONG,
    type=OrderType.LIMIT,
    price=50000,
    volume=0.01
)

# Send the order
gateway.send_order(order_req)
```

### Cancelling an Order
```python
from vnpy.trader.object import CancelRequest

# Create a cancel request
cancel_req = CancelRequest(
    symbol="BTCUSDT",
    exchange=Exchange.BINANCE,
    orderid="123456"
)

# Cancel the order
gateway.cancel_order(cancel_req)
```

## Notes
- Ensure that the API key and secret are kept secure.
- Use the testnet environment for testing to avoid unintended trades.
- Monitor the logs for any connection or data issues.

## License
This module is licensed under the MIT License.