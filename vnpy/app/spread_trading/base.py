from typing import Dict, List
from math import floor, ceil
from datetime import datetime

from vnpy.trader.object import TickData, PositionData
from vnpy.trader.constant import Direction


class LegData:
    """"""

    def __init__(
        self,
        vt_symbol: str,
        price_multiplier: float,
        trading_multiplier: float
    ):
        """"""
        self.vt_symbol: str = vt_symbol

        # For calculating spread price
        self.price_multiplier: float = price_multiplier

        # For calculating spread pos and sending orders
        self.trading_multiplier: float = trading_multiplier

        # Price and position data
        self.bid_price: float = 0
        self.ask_price: float = 0
        self.bid_volume: float = 0
        self.ask_volume: float = 0

        self.long_pos: float = 0
        self.short_pos: float = 0
        self.net_pos: float = 0

    def update_tick(self, tick: TickData):
        """"""
        self.bid_price = tick.bid_price_1
        self.ask_price = tick.ask_price_1
        self.bid_volume = tick.bid_volume_1
        self.ask_volume = tick.ask_volume_1

    def update_position(self, position: PositionData):
        """"""
        if position.direction == Direction.NET:
            self.net_pos = position.volume
        else:
            if position.direction == Direction.LONG:
                self.long_pos = position.volume
            else:
                self.short_pos = position.volume
            self.net_pos = self.long_pos - self.short_pos


class SpreadData:
    """"""

    def __init__(
        self,
        name: str,
        legs: List[LegData],
        active_symbol: str
    ):
        """"""
        self.name: str = name

        self.legs: Dict[str, LegData] = {}
        self.active_leg: LegData = None
        self.passive_legs: List[LegData] = []

        for leg in legs:
            self.legs[leg.vt_symbol] = leg
            if leg.vt_symbol == active_symbol:
                self.active_leg = leg
            else:
                self.passive_legs.append(leg)

        # Spread data
        self.bid_price: float = 0
        self.ask_price: float = 0
        self.bid_volume: float = 0
        self.ask_volume: float = 0

        self.net_pos: float = 0
        self.datetime: datetime = None

    def calculate_price(self):
        """"""
        self.clear_price()

        # Go through all legs to calculate price
        for n, leg in enumerate(self.legs.values()):
            # Filter not all leg price data has been received
            if not leg.bid_volume or not leg.ask_volume:
                self.clear_price()
                return

            # Calculate price
            if leg.price_multiplier > 0:
                self.bid_price += leg.bid_price * leg.price_multiplier
                self.ask_price += leg.ask_price * leg.price_multiplier
            else:
                self.bid_price += leg.ask_price * leg.price_multiplier
                self.ask_price += leg.bid_price * leg.price_multiplier

            # Calculate volume
            if leg.trading_multiplier > 0:
                adjusted_bid_volume = floor(
                    leg.bid_volume / leg.trading_multiplier)
                adjusted_ask_volume = floor(
                    leg.ask_volume / leg.trading_multiplier)
            else:
                adjusted_bid_volume = floor(
                    leg.ask_volume / abs(leg.trading_multiplier))
                adjusted_ask_volume = floor(
                    leg.bid_volume / abs(leg.trading_multiplier))

            # For the first leg, just initialize
            if not n:
                self.bid_volume = adjusted_bid_volume
                self.ask_volume = adjusted_ask_volume
            # For following legs, use min value of each leg quoting volume
            else:
                self.bid_volume = min(self.bid_volume, adjusted_bid_volume)
                self.ask_volume = min(self.ask_volume, adjusted_ask_volume)

            # Update calculate time
            self.datetime = datetime.now()

    def calculate_pos(self):
        """"""
        self.net_pos = 0

        for n, leg in enumerate(self.legs.values()):
            adjusted_net_pos = leg.net_pos / leg.trading_multiplier

            if adjusted_net_pos > 0:
                adjusted_net_pos = floor(adjusted_net_pos)
            else:
                adjusted_net_pos = ceil(adjusted_net_pos)

            if not n:
                self.net_pos = adjusted_net_pos
            else:
                if adjusted_net_pos > 0:
                    self.net_pos = min(self.net_pos, adjusted_net_pos)
                else:
                    self.net_pos = max(self.net_pos, adjusted_net_pos)

    def clear_price(self):
        """"""
        self.bid_price = 0
        self.ask_price = 0
        self.bid_volume = 0
        self.ask_volume = 0
