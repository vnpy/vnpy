from typing import Dict, Optional

from vnpy.trader.constant import Direction
from vnpy.trader.object import OrderData


class ActiveOrderBook:
    """
    Stores active buy and sell orders for a specific contract (vt_symbol)
    to facilitate checks like self-trading.
    """

    def __init__(self, vt_symbol: str) -> None:
        """Initialize the active order book."""
        self.vt_symbol: str = vt_symbol
        self.bid_prices: Dict[str, float] = {} # vt_orderid: price
        self.ask_prices: Dict[str, float] = {} # vt_orderid: price

    def update_order(self, order: OrderData) -> None:
        """
        Update the order book based on the order's status and direction.
        Adds active orders and removes inactive ones.
        """
        vt_orderid = order.vt_orderid

        # Remove existing entry if present (handles status changes)
        self.bid_prices.pop(vt_orderid, None)
        self.ask_prices.pop(vt_orderid, None)

        # Add if the order is active
        if order.is_active():
            if order.direction == Direction.LONG:
                self.bid_prices[vt_orderid] = order.price
            elif order.direction == Direction.SHORT: # Use SHORT for clarity
                self.ask_prices[vt_orderid] = order.price

    def get_best_bid(self) -> Optional[float]:
        """Get the highest active bid price. Returns None if no active bids."""
        if not self.bid_prices:
            return None
        return max(self.bid_prices.values())

    def get_best_ask(self) -> Optional[float]:
        """Get the lowest active ask price. Returns None if no active asks."""
        if not self.ask_prices:
            return None
        return min(self.ask_prices.values())