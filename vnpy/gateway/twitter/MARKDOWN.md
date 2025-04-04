# TwitterGateway Documentation

## Purpose
The `TwitterGateway` is designed to receive text content from Twitter in real-time. It streams tweets based on specified keywords and integrates with the event engine to process the incoming data.

## Interface
### Constructor
```python
TwitterGateway(event_engine: EventEngine, gateway_name: str)
```
- **event_engine**: The event engine instance.
- **gateway_name**: The name of the gateway.

### Methods
#### `connect`
```python
def connect(self, setting: dict) -> None
```
Connects to the Twitter API and starts streaming tweets based on the provided keywords.
- **setting**: A dictionary containing connection settings, including `keywords` to track.

#### `subscribe`
```python
def subscribe(self, req: SubscribeRequest) -> None
```
This method is not applicable for the Twitter gateway.

#### `close`
```python
def close(self) -> None
```
Closes the Twitter stream and disconnects the gateway.

#### `write_log`
```python
def write_log(self, msg: str, level=logging.INFO) -> None
```
Writes log messages.
- **msg**: The log message.
- **level**: The logging level.

## Usage Examples
### Example 1: Initialize and Connect
```python
from vnpy.gateway.twitter import TwitterGateway
from vnpy.event import EventEngine

# Initialize event engine
event_engine = EventEngine()

# Create TwitterGateway instance
twitter_gateway = TwitterGateway(event_engine, "Twitter")

# Connect to Twitter API
settings = {
    "keywords": ["crypto", "trading"],
    "api_key": "your_api_key",
    "api_secret": "your_api_secret",
    "access_token": "your_access_token",
    "access_token_secret": "your_access_token_secret"
}
twitter_gateway.connect(settings)
```

## Dependencies
- `tweepy` library for Twitter API interaction.
- `vnpy` framework for event handling and gateway integration.
- `logging` for log management.

## Error Handling
- Logs errors during connection and streaming.
- Disconnects on rate limit errors (status code 420).

## Tests
### Basic Test Case
```python
# Test the connect method
settings = {
    "keywords": ["test"],
    "api_key": "test_api_key",
    "api_secret": "test_api_secret",
    "access_token": "test_access_token",
    "access_token_secret": "test_access_token_secret"
}
twitter_gateway = TwitterGateway(event_engine, "Twitter")
twitter_gateway.connect(settings)
assert twitter_gateway.stream_listener is not None
```

## Notes
- Ensure the Twitter API credentials are valid and have sufficient permissions.
- The `connect` method uses asynchronous streaming to handle real-time tweets.