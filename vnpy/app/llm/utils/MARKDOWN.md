# ChatGPTAgent Documentation

## Purpose
The `ChatGPTAgent` class is designed to interact with the ChatGPT API to analyze text data and generate trading signals. It serves as a decoupled utility for the `LLMEngine` to process text information.

## Interface
### Constructor
```python
ChatGPTAgent(api_key: str, model_name: str = "gpt-3.5-turbo")
```
- **api_key**: API key for authenticating with the ChatGPT API.
- **model_name**: The name of the model to use (default: `gpt-3.5-turbo`).

### Methods
#### `analyze_text`
```python
def analyze_text(self, text: str) -> Dict[str, Any]
```
- **text**: The text to analyze.
- **Returns**: A dictionary containing the generated trading signal and confidence level.

## Usage Examples
### Example 1: Initialize and Analyze Text
```python
from utils.chatgpt_agent import ChatGPTAgent

# Initialize the agent
agent = ChatGPTAgent(api_key="your_api_key", model_name="gpt-3.5-turbo")

# Analyze text
text = "The market sentiment is bullish."
result = agent.analyze_text(text)
print(result)  # Output: {'signal': 'buy', 'confidence': 0.9}
```

## Dependencies
- `openai` library for API interaction.
- Python standard libraries: `typing`.

## Error Handling
- Raises `RuntimeError` if there is an error communicating with the ChatGPT API.

## Tests
### Basic Test Case
```python
# Test the analyze_text method
agent = ChatGPTAgent(api_key="test_api_key", model_name="gpt-3.5-turbo")
result = agent.analyze_text("The market is bearish.")
assert result["signal"] == "sell"
assert 0 <= result["confidence"] <= 1
```

## Notes
- Ensure the API key is valid and has sufficient quota.
- The `analyze_text` method uses placeholder logic for parsing the API response. Customize it as per your requirements.