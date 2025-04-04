import logging
from typing import Any, Dict
from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import EVENT_LOG
from vnpy.trader.object import LogData
from vnpy.trader.setting import SETTINGS
from .utils.chatgpt_agent import ChatGPTAgent

APP_NAME = "LLMEngine"

class LLMEngine(BaseEngine):
    """
    Engine for processing text information using LLM models like ChatGPT.
    """

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """
        Initialize the LLM Engine.

        Parameters:
            main_engine (MainEngine): The main engine instance.
            event_engine (EventEngine): The event engine instance.
        """
        super().__init__(main_engine, event_engine, APP_NAME)

        self.logger = logging.getLogger(APP_NAME)
        self.logger.setLevel(logging.INFO)

        self.api_key = SETTINGS.get("llm.api_key", "")
        self.model_name = SETTINGS.get("llm.model_name", "gpt-3.5-turbo")

        if not self.api_key:
            self.write_log("LLM API key is not configured.", level=logging.ERROR)

        self.agent = ChatGPTAgent(api_key=self.api_key, model_name=self.model_name)

        self.register_event()

    def register_event(self) -> None:
        """
        Register events to handle incoming text data.
        """
        self.event_engine.register("EVENT_TEXT", self.process_text_event)

    def process_text_event(self, event: Event) -> None:
        """
        Process incoming text data and generate trading signals.

        Parameters:
            event (Event): The event containing text data.
        """
        text_data = event.data

        try:
            self.write_log(f"Received text data: {text_data}", level=logging.DEBUG)

            # Call LLM API to analyze text and generate trading signal
            trading_signal = self.analyze_text(text_data)

            # Emit trading signal event
            signal_event = Event("EVENT_TRADING_SIGNAL", trading_signal)
            self.event_engine.put(signal_event)

            self.write_log(f"Generated trading signal: {trading_signal}", level=logging.INFO)

        except Exception as e:
            self.write_log(f"Error processing text event: {e}", level=logging.ERROR)

    def analyze_text(self, text: str) -> Dict[str, Any]:
        """
        Analyze text using the LLM API and generate a trading signal.

        Parameters:
            text (str): The text to analyze.

        Returns:
            Dict[str, Any]: The generated trading signal.
        """
        return self.agent.analyze_text(text)

    def write_log(self, msg: str, level=logging.INFO) -> None:
        """
        Write log messages.

        Parameters:
            msg (str): The log message.
            level (int): The logging level.
        """
        log = LogData(msg=msg, gateway_name=APP_NAME, level=level)
        event = Event(EVENT_LOG, log)
        self.event_engine.put(event)

    def close(self) -> None:
        """
        Close the engine.
        """
        self.write_log("LLM Engine closed.", level=logging.INFO)