from collections import defaultdict
from typing import Callable, Dict, Optional, Set
import logging # Use standard logging for potential framework integration
from datetime import datetime # Optional: For daily resets

from vnpy.app.risk_manager.base import ActiveOrderBook
from vnpy.event import Event, EventEngine
from vnpy.trader.object import OrderData, OrderRequest, LogData, TradeData
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import EVENT_TRADE, EVENT_ORDER, EVENT_LOG, EVENT_TIMER
from vnpy.trader.constant import Direction, Status
from vnpy.trader.utility import load_json, save_json

APP_NAME = "RiskManager"
SETTING_FILENAME = "risk_manager_setting.json"
LOG_GATEWAY_NAME = "RiskManager" # Constant for log source


class RiskEngine(BaseEngine):
    """
    Risk management engine to intercept and check orders before sending.

    Applies limits on:
    - Order flow rate
    - Individual order size
    - Total traded volume (cumulative within engine lifetime or optionally daily)
    - Total active orders
    - Order cancellation frequency per contract (cumulative or optionally daily)
    - Potential self-trading based on own active orders
    """

    setting_filename: str = SETTING_FILENAME

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """Initialize the risk engine."""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.active: bool = False           # Master switch for risk checks
        self.order_flow_count: int = 0      # Counter for orders within a time window
        self.order_flow_limit: int = 50     # Max orders allowed in the window
        self.order_flow_clear: int = 1      # Window duration in seconds for flow count reset
        self.order_flow_timer: int = 0      # Timer ticks since last flow reset
        self.order_size_limit: int = 100    # Max volume per order
        self.trade_count: int = 0           # Cumulative traded volume
        self.trade_limit: int = 1000        # Max cumulative traded volume
        self.order_cancel_limit: int = 500  # Max cancels per vt_symbol
        self.active_order_limit: int = 50   # Max total active orders allowed

        # --- State Tracking ---
        # Use defaultdict for convenience
        self.order_cancel_counts: Dict[str, int] = defaultdict(int)
        # Store active order books per symbol
        self.active_order_books: Dict[str, ActiveOrderBook] = {}
        # Efficiently track IDs of all active orders known to the engine
        self.active_order_ids: Set[str] = set()
        # Store the original send_order function
        self._original_send_order: Optional[Callable] = None

        # Optional: For daily reset
        # self.current_trading_day: Optional[date] = None

        self.load_setting()
        self.register_event()
        self.patch_send_order()

    def patch_send_order(self) -> None:
        """
        Replace MainEngine.send_order with our risk-checking version.
        Store the original function to call it after checks pass and for cleanup.
        """
        # Ensure patching happens only once
        if self._original_send_order is None:
            self._original_send_order = self.main_engine.send_order
            self.main_engine.send_order = self.intercept_send_order
            self.write_log("send_order function patched for risk checks.")

    def unpatch_send_order(self) -> None:
        """Restore the original MainEngine.send_order function."""
        if self._original_send_order is not None:
            self.main_engine.send_order = self._original_send_order
            self._original_send_order = None # Mark as unpatched
            self.write_log("Original send_order function restored.")

    def intercept_send_order(self, req: OrderRequest, gateway_name: str) -> str:
        """
        Intercepts outgoing orders, performs risk checks, and forwards
        to the original send_order function if checks pass.
        """
        if not self.check_risk(req, gateway_name):
            # Risk check failed, log already written by check_risk
            # Return empty string to indicate failure (as original code did)
            return ""

        # Risk checks passed, call the original send_order
        if self._original_send_order:
            # Increment flow count *only* if the order is actually being sent
            self.order_flow_count += 1
            return self._original_send_order(req, gateway_name)
        else:
            # Should not happen if initialized correctly, but good to handle
            self.write_log("Error: Original send_order function not found.", level=logging.ERROR)
            return ""

    def update_setting(self, setting: dict) -> None:
        """Update risk management settings from a dictionary."""
        try:
            self.active = setting.get("active", self.active)
            self.order_flow_limit = setting.get("order_flow_limit", self.order_flow_limit)
            self.order_flow_clear = setting.get("order_flow_clear", self.order_flow_clear)
            self.order_size_limit = setting.get("order_size_limit", self.order_size_limit)
            self.trade_limit = setting.get("trade_limit", self.trade_limit)
            self.active_order_limit = setting.get("active_order_limit", self.active_order_limit)
            self.order_cancel_limit = setting.get("order_cancel_limit", self.order_cancel_limit)
            self.write_log(f"Risk settings updated. Active: {self.active}")
        except Exception as e:
            self.write_log(f"Error updating settings: {e}", level=logging.ERROR)


    def get_setting(self) -> dict:
        """Retrieve current risk management settings."""
        return {
            "active": self.active,
            "order_flow_limit": self.order_flow_limit,
            "order_flow_clear": self.order_flow_clear,
            "order_size_limit": self.order_size_limit,
            "trade_limit": self.trade_limit,
            "active_order_limit": self.active_order_limit,
            "order_cancel_limit": self.order_cancel_limit,
        }

    def load_setting(self) -> None:
        """Load settings from the JSON file."""
        setting: Optional[dict] = load_json(self.setting_filename)
        if setting:
            self.write_log(f"Loading settings from {self.setting_filename}")
            self.update_setting(setting)
        else:
             self.write_log(f"Settings file {self.setting_filename} not found or empty, using defaults.", level=logging.WARNING)
             # Optionally save default settings here
             # self.save_setting()


    def save_setting(self) -> None:
        """Save current settings to the JSON file."""
        setting: dict = self.get_setting()
        if save_json(self.setting_filename, setting):
             self.write_log(f"Settings saved to {self.setting_filename}")
        else:
             self.write_log(f"Failed to save settings to {self.setting_filename}", level=logging.ERROR)


    def register_event(self) -> None:
        """Register event listeners."""
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)
        self.event_engine.register(EVENT_ORDER, self.process_order_event)

    def unregister_event(self) -> None:
        """Unregister event listeners."""
        self.event_engine.unregister(EVENT_TRADE, self.process_trade_event)
        self.event_engine.unregister(EVENT_TIMER, self.process_timer_event)
        self.event_engine.unregister(EVENT_ORDER, self.process_order_event)


    def process_order_event(self, event: Event) -> None:
        """Process order updates to track active orders and cancellations."""
        order: OrderData = event.data
        vt_symbol = order.vt_symbol
        vt_orderid = order.vt_orderid

        # Update Active Order Book for self-trade check
        order_book = self.get_order_book(vt_symbol)
        order_book.update_order(order)

        # Update overall active order count/set
        is_active = order.is_active()
        if is_active:
            self.active_order_ids.add(vt_orderid)
        elif vt_orderid in self.active_order_ids: # Check if it *was* active before removing
            self.active_order_ids.remove(vt_orderid)
            # Increment cancel count only when a previously active order becomes inactive *and* is cancelled
            if order.status == Status.CANCELLED:
                 self.order_cancel_counts[vt_symbol] += 1


    def process_trade_event(self, event: Event) -> None:
        """Process trade events to update cumulative trade volume."""
        trade: TradeData = event.data
        self.trade_count += trade.volume


    def process_timer_event(self, event: Event) -> None:
        """Process timer events to reset order flow counter."""
        # Optional: Implement daily reset logic here
        # current_day = datetime.now().date()
        # if current_day != self.current_trading_day:
        #     self.reset_daily_counters(current_day)

        self.order_flow_timer += 1
        if self.order_flow_timer >= self.order_flow_clear:
            # Reset flow counter and timer
            self.order_flow_count = 0
            self.order_flow_timer = 0

    # Optional: Method for daily reset
    # def reset_daily_counters(self, trading_day: date) -> None:
    #      """Resets counters that should be tracked daily."""
    #      self.trade_count = 0
    #      self.order_cancel_counts.clear()
    #      self.current_trading_day = trading_day
    #      self.write_log(f"Daily counters reset for trading day {trading_day}.")


    def write_log(self, msg: str, level: int = logging.INFO) -> None:
        """Write a log message using vn.py's event system."""
        # Map logging levels if needed, or just pass message
        log: LogData = LogData(msg=f"[{APP_NAME}] {msg}", gateway_name=LOG_GATEWAY_NAME) # Prefix msg with app name
        event: Event = Event(type=EVENT_LOG, data=log)
        self.event_engine.put(event)


    def get_order_book(self, vt_symbol: str) -> ActiveOrderBook:
        """Retrieve or create an active order book for the given symbol."""
        order_book = self.active_order_books.get(vt_symbol)
        if not order_book:
            order_book = ActiveOrderBook(vt_symbol)
            self.active_order_books[vt_symbol] = order_book
        return order_book

    # ----------------------------------------------------------------------
    # Risk Checking Logic
    # ----------------------------------------------------------------------

    def check_risk(self, req: OrderRequest, gateway_name: str) -> bool:
        """
        Perform all risk checks for the given order request.
        Returns True if the order passes all checks, False otherwise.
        """
        if not self.active:
            return True # Risk management is disabled

        # Perform individual checks - order matters, fail fast
        if not self._check_order_validity(req):
             return False
        if not self._check_order_size(req):
             return False
        if not self._check_trade_limit(req):
            return False
        if not self._check_order_flow():
            return False
        if not self._check_active_orders():
            return False
        if not self._check_cancellation_limit(req):
            return False
        if not self._check_self_trade(req):
            return False

        # All checks passed
        return True

    def _check_order_validity(self, req: OrderRequest) -> bool:
        """Check basic order validity (e.g., volume > 0)."""
        if req.volume <= 0:
            self.write_log(f"Order rejected: Volume must be positive (Volume={req.volume})", level=logging.WARNING)
            return False
        # Add other basic checks if needed (e.g., price > 0 for limit orders)
        return True

    def _check_order_size(self, req: OrderRequest) -> bool:
        """Check if order volume exceeds the limit."""
        if req.volume > self.order_size_limit:
            self.write_log(
                f"Order rejected: Volume {req.volume} exceeds limit {self.order_size_limit} for {req.vt_symbol}",
                level=logging.WARNING
            )
            return False
        return True

    def _check_trade_limit(self, req: OrderRequest) -> bool:
        """Check if cumulative trade volume would exceed the limit."""
        # Note: This checks *before* the potential trade happens.
        # If the limit is exactly reached by this order, it might be allowed.
        # Consider if limit is inclusive or exclusive. Current logic is inclusive.
        if self.trade_count >= self.trade_limit:
            self.write_log(
                f"Order rejected: Cumulative trade volume {self.trade_count} has reached limit {self.trade_limit}",
                level=logging.WARNING
            )
            return False
        # Optional stricter check: if (self.trade_count + req.volume > self.trade_limit): ...
        return True

    def _check_order_flow(self) -> bool:
        """Check if order rate exceeds the flow limit."""
        if self.order_flow_count >= self.order_flow_limit:
            self.write_log(
                f"Order rejected: Flow count {self.order_flow_count} exceeds limit {self.order_flow_limit} per {self.order_flow_clear}s",
                level=logging.WARNING
            )
            return False
        return True

    def _check_active_orders(self) -> bool:
        """Check if the number of active orders exceeds the limit."""
        current_active_count = len(self.active_order_ids)
        if current_active_count >= self.active_order_limit:
            self.write_log(
                f"Order rejected: Active order count {current_active_count} has reached limit {self.active_order_limit}",
                level=logging.WARNING
            )
            return False
        return True

    def _check_cancellation_limit(self, req: OrderRequest) -> bool:
        """Check if the cancellation count for the symbol exceeds the limit."""
        cancel_count = self.order_cancel_counts.get(req.vt_symbol, 0)
        if cancel_count >= self.order_cancel_limit:
            self.write_log(
                f"Order rejected: Cancellation count {cancel_count} for {req.vt_symbol} has reached limit {self.order_cancel_limit}",
                level=logging.WARNING
            )
            return False
        return True

    def _check_self_trade(self, req: OrderRequest) -> bool:
        """Check for potential self-trade against own active orders."""
        order_book = self.get_order_book(req.vt_symbol)

        if req.direction == Direction.LONG:
            best_ask = order_book.get_best_ask()
            # Check if best_ask exists and if the buy price would cross or match it
            if best_ask is not None and req.price >= best_ask:
                self.write_log(
                    f"Order rejected: Buy price {req.price} >= own best ask {best_ask} for {req.vt_symbol} (Potential self-trade)",
                    level=logging.WARNING
                )
                return False
        elif req.direction == Direction.SHORT: # Use SHORT
            best_bid = order_book.get_best_bid()
            # Check if best_bid exists and if the sell price would cross or match it
            if best_bid is not None and req.price <= best_bid:
                self.write_log(
                    f"Order rejected: Sell price {req.price} <= own best bid {best_bid} for {req.vt_symbol} (Potential self-trade)",
                    level=logging.WARNING
                )
                return False
        return True


    def close(self) -> None:
        """Cleanup resources when the engine stops."""
        self.write_log("Stopping RiskManager Engine.")
        self.unpatch_send_order()
        self.unregister_event()
        self.save_setting() # Save settings on close