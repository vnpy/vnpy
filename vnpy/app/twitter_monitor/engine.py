import openai
import tweepy
import json
import time
from typing import Optional
from vnpy.trader.constant import Direction, Offset, Exchange, OrderType
from vnpy.trader.object import OrderRequest
from vnpy.app.twitter_monitor.base import APP_NAME
from vnpy.event import EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.utility import load_json


class TwitterEngine(BaseEngine):
    setting_filename: str = "twitter_monitor_setting.json"
    default_exchange: Exchange = Exchange.BINANCE  # Default to Binance

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        super().__init__(main_engine, event_engine, APP_NAME)

        # Load settings from JSON file
        self.client_setting = load_json(self.setting_filename)
        self.client_api_key = self.client_setting['api_key']
        self.client_api_secret = self.client_setting['api_secret']
        self.access_token = self.client_setting['access_token']
        self.access_token_secret = self.client_setting['access_token_secret']
        self.target_account = self.client_setting['target_account']
        self.openai_api_key = self.client_setting['openai_api_key']

        # Authenticate with Twitter API
        self.auth = tweepy.OAuth1UserHandler(
            self.client_api_key, self.client_api_secret,
            self.access_token, self.access_token_secret
        )
        self.api = tweepy.API(self.auth, wait_on_rate_limit=True)

        # Authenticate OpenAI API
        openai.api_key = self.openai_api_key

    def start_streaming(self):
        """Start real-time monitoring of tweets from the target account."""
        stream_listener = TwitterStreamListener(self)
        stream = tweepy.Stream(auth=self.api.auth, listener=stream_listener)
        stream.filter(follow=[self.get_user_id(self.target_account)], is_async=True)

    def get_user_id(self, screen_name: str) -> str:
        """Fetches Twitter user ID from the username (screen_name)."""
        user = self.api.get_user(screen_name=screen_name)
        return str(user.id)

    def analyze_tweet(self, tweet_text: str) -> Optional[dict]:
        """Analyzes a tweet using GPT-4 and extracts trading signals."""
        try:
            response = openai.ChatCompletion.create(
                model="gpt-4",
                messages=[
                    {"role": "system",
                     "content": "You are a financial analyst. Identify trading signals (buy, sell, hold) from the given tweet."},
                    {"role": "user",
                     "content": f"Analyze the following tweet and determine if it suggests a 'BUY', 'SELL', or 'HOLD' action. Provide output in JSON format: {{'signal': 'BUY', 'symbol': 'BTCUSDT'}}\nTweet: {tweet_text}"}
                ],
                max_tokens=50
            )
            result = json.loads(response.choices[0].message["content"])
            return result  # Example: {'signal': 'BUY', 'symbol': 'BTCUSDT'}
        except Exception as e:
            print(f"Error analyzing tweet: {e}")
            return None

    def execute_trade(self, signal_data: dict):
        """Generates an order request if a valid BUY/SELL signal is received."""
        if not signal_data:
            print("No valid trading signal detected.")
            return

        signal = signal_data["signal"].upper()
        symbol = signal_data["symbol"].upper()
        volume = 1  # Default trade volume (can be dynamic)

        # Ensure only BUY or SELL orders are processed
        if signal not in ["BUY", "SELL"]:
            print(f"Ignoring signal: {signal}")
            return

        direction = Direction.LONG if signal == "BUY" else Direction.SHORT

        order_request = OrderRequest(
            symbol=symbol,
            exchange=self.default_exchange,
            direction=direction,
            type=OrderType.MARKET,
            volume=volume,
            price=0,  # Market order doesn't need price
            offset=Offset.OPEN
        )

        # Send the order request to vn.py's main engine
        self.main_engine.send_order(order_request)

        print(f"Order Sent: {signal} {volume} {symbol} on {self.default_exchange}")


class TwitterStreamListener(tweepy.StreamListener):
    """Real-time tweet listener for monitoring a target account."""

    def __init__(self, engine: TwitterEngine):
        super().__init__()
        self.engine = engine

    def on_status(self, status):
        """Triggered when a new tweet is posted by the monitored account."""
        tweet_text = status.text
        print(f"New Tweet: {tweet_text}")

        # Analyze tweet and execute trade if a valid signal is found
        signal_data = self.engine.analyze_tweet(tweet_text)
        self.engine.execute_trade(signal_data)

    def on_error(self, status_code):
        """Handles streaming API errors."""
        print(f"Twitter Streaming Error: {status_code}")
        if status_code == 420:  # Rate limit exceeded
            time.sleep(60)  # Wait before retrying
        return True


# Run the bot
if __name__ == "__main__":
    engine = TwitterEngine(main_engine=None, event_engine=None)
    engine.start_streaming()
