import openai
from typing import Any, Dict

class ChatGPTAgent:
    """
    Agent class for interacting with the ChatGPT API.
    """

    def __init__(self, api_key: str, model_name: str = "gpt-3.5-turbo") -> None:
        """
        Initialize the ChatGPTAgent.

        Parameters:
            api_key (str): API key for authenticating with the ChatGPT API.
            model_name (str): The name of the model to use.
        """
        self.api_key = api_key
        self.model_name = model_name

    def analyze_text(self, text: str) -> Dict[str, Any]:
        """
        Analyze the given text using the ChatGPT API and generate a trading signal.

        Parameters:
            text (str): The text to analyze.

        Returns:
            Dict[str, Any]: The generated trading signal.
        """
        openai.api_key = self.api_key

        try:
            response = openai.ChatCompletion.create(
                model=self.model_name,
                messages=[
                    {"role": "system", "content": "You are a trading assistant."},
                    {"role": "user", "content": text}
                ]
            )

            # Extract the response content
            content = response["choices"][0]["message"]["content"]

            # Placeholder logic to parse the response into a trading signal
            # This should be replaced with actual parsing logic based on your use case
            if "buy" in content.lower():
                signal = "buy"
            elif "sell" in content.lower():
                signal = "sell"
            else:
                signal = "hold"

            return {
                "signal": signal,
                "confidence": 0.9  # Placeholder confidence value
            }

        except openai.error.OpenAIError as e:
            raise RuntimeError(f"Error communicating with ChatGPT API: {e}")