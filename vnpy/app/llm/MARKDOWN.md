# LLMEngine Documentation

## Purpose
The `LLMEngine` is designed to process text information using Large Language Models (LLMs) like ChatGPT. It integrates with the event engine to receive text data, analyze it using an LLM API, and generate trading signals.

## Interface
### Constructor
```python
LLMEngine(main_engine: MainEngine, event_engine: EventEngine)
```
- **main_engine**: The main engine instance.
- **event_engine**: The event engine instance.

### Methods
#### `register_event`
```python
def register_event(self) -> None
```
Registers events to handle incoming text data.

#### `process_text_event`
```python
def process_text_event(self, event: Event) -> None
```
Processes incoming text data and generates trading signals.
- **event**: The event containing text data.

#### `analyze_text`
```python
def analyze_text(self, text: str) -> Dict[str, Any]
```
Analyzes text using the LLM API and generates a trading signal.
- **text**: The text to analyze.
- **Returns**: A dictionary containing the generated trading signal.

#### `write_log`
```python
def write_log(self, msg: str, level=logging.INFO) -> None
```
Writes log messages.
- **msg**: The log message.
- **level**: The logging level.

#### `close`
```python
def close(self) -> None
```
Closes the engine.

## Usage Examples
### Example 1: Initialize and Process Text
```python
from vnpy.app.llm.engine import LLMEngine
from vnpy.trader.engine import MainEngine, EventEngine

# Initialize engines
main_engine = MainEngine()
event_engine = EventEngine()

# Create LLMEngine instance
llm_engine = LLMEngine(main_engine, event_engine)

# Simulate a text event
text_event = Event("EVENT_TEXT", data="The market sentiment is bullish.")
llm_engine.process_text_event(text_event)
```

## Dependencies
- `vnpy` framework for event handling and engine integration.
- `logging` for log management.
- `ChatGPTAgent` for LLM API interaction.

## Error Handling
- Logs errors during text processing and LLM API interaction.

## Tests
### Basic Test Case
```python
# Test the analyze_text method
llm_engine = LLMEngine(main_engine, event_engine)
result = llm_engine.analyze_text("The market is bearish.")
assert result["signal"] in ["buy", "sell", "hold"]
assert 0 <= result["confidence"] <= 1
```

## Notes
- Ensure the LLM API key is configured in the settings.
- The `analyze_text` method uses the `ChatGPTAgent` for API interaction.