from vnpy.gateway import BaseGateway
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.event import EVENT_LOG, Event
from vnpy.trader.object import LogData, SubscribeRequest, TickData
from vnpy.trader.constant import Exchange
import tweepy
import logging

from vnpy.trader.setting import SETTINGS

class TwitterGateway(BaseGateway):
    """
    Gateway for receiving text content from Twitter.
    """

    default_name = "Twitter"

    def __init__(self, event_engine: EventEngine, gateway_name: str) -> None:
        """
        Initialize the Twitter Gateway.

        Parameters:
            event_engine (EventEngine): The event engine instance.
            gateway_name (str): The name of the gateway.
        """
        super().__init__(event_engine, gateway_name)

        self.logger = logging.getLogger(gateway_name)
        self.logger.setLevel(logging.INFO)

        self.api_key = SETTINGS.get("twitter.api_key", "")
        self.api_secret = SETTINGS.get("twitter.api_secret", "")
        self.access_token = SETTINGS.get("twitter.access_token", "")
        self.access_token_secret = SETTINGS.get("twitter.access_token_secret", "")

        self.auth = tweepy.OAuthHandler(self.api_key, self.api_secret)
        self.auth.set_access_token(self.access_token, self.access_token_secret)
        self.api = tweepy.API(self.auth)

        self.stream_listener = None

    def connect(self, setting: dict) -> None:
        """
        Connect to Twitter API.
        """
        try:
            self.stream_listener = TwitterStreamListener(self.event_engine)
            stream = tweepy.Stream(auth=self.api.auth, listener=self.stream_listener)
            stream.filter(track=setting.get("keywords", []), is_async=True)
            self.write_log("Twitter Gateway connected successfully.")
        except Exception as e:
            self.write_log(f"Error connecting to Twitter API: {e}", level=logging.ERROR)

    def subscribe(self, req: SubscribeRequest) -> None:
        """
        Subscribe to data updates (not applicable for Twitter).
        """
        pass

    def close(self) -> None:
        """
        Close the gateway.
        """
        if self.stream_listener:
            self.stream_listener.disconnect()
        self.write_log("Twitter Gateway closed.")

    def write_log(self, msg: str, level=logging.INFO) -> None:
        """
        Write log messages.

        Parameters:
            msg (str): The log message.
            level (int): The logging level.
        """
        log = LogData(msg=msg, gateway_name=self.gateway_name, level=level)
        event = Event(EVENT_LOG, log)
        self.event_engine.put(event)

class TwitterStreamListener(tweepy.StreamListener):
    """
    Listener for processing Twitter stream data.
    """

    def __init__(self, event_engine: EventEngine) -> None:
        """
        Initialize the stream listener.

        Parameters:
            event_engine (EventEngine): The event engine instance.
        """
        super().__init__()
        self.event_engine = event_engine

    def on_status(self, status) -> None:
        """
        Handle incoming tweets.

        Parameters:
            status: The tweet status object.
        """
        text = status.text
        event = Event("EVENT_TEXT", text)
        self.event_engine.put(event)

    def on_error(self, status_code) -> bool:
        """
        Handle errors in the stream.

        Parameters:
            status_code: The error status code.

        Returns:
            bool: Whether to continue streaming.
        """
        if status_code == 420:
            return False  # Disconnect on rate limit
        return True