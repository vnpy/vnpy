# portfolio_manager/engine.py
import logging
from typing import Any, Dict, Set, Optional, Tuple, Callable
from datetime import datetime, date, timezone
import traceback
import os # For checking file existence more reliably

from vnpy.event import Event
from vnpy.trader.engine import (
    MainEngine,
    EventEngine,
    BaseEngine
)
from vnpy.trader.event import (
    EVENT_ORDER,
    EVENT_CONTRACT,
    EVENT_TIMER,
    EVENT_TRADE,
    EVENT_LOG
)
from vnpy.trader.object import (
    ContractData,
    OrderData,
    TickData,
    TradeData,
    SubscribeRequest,
    LogData
)
from vnpy.trader.utility import load_json, save_json, get_file_path # Use vnpy utility

# Import base classes, constants, and logger from the base file/module
try:
    from .base import (
        ContractResult, PortfolioResult, PortfolioStatistics,
        DATE_KEY, DATA_KEY, OPEN_POS_KEY, LAST_POS_KEY, TIMER_INTERVAL_KEY,
        logger # Use the logger defined in base
    )
except ImportError: # Handle running script directly for testing
     from vnpy.app.portfolio_manager.base import (
        ContractResult, PortfolioResult, PortfolioStatistics,
        DATE_KEY, DATA_KEY, OPEN_POS_KEY, LAST_POS_KEY, TIMER_INTERVAL_KEY,
        logger
    )


APP_NAME = "PortfolioManager"

# --- Event Names ---
EVENT_PM_CONTRACT = "ePmContract"      # Event for individual contract result updates
EVENT_PM_PORTFOLIO = "ePmPortfolio"    # Event for aggregated portfolio result updates
EVENT_PM_TRADE = "ePmTrade"            # Event for trades processed by Portfolio Manager (with reference)
EVENT_PM_STATISTICS = "ePmStatistics"  # Event for portfolio statistics updates

# --- Filenames (relative to vnpy's working directory) ---
SETTING_FILENAME = "portfolio_manager_setting.json"
DATA_FILENAME = "portfolio_manager_data.json"
ORDER_FILENAME = "portfolio_manager_order.json"
STATS_FILENAME = "portfolio_manager_statistics.json"


class PortfolioEngine(BaseEngine):
    """
    Engine for managing and calculating PnL and statistics for multiple portfolios,
    identified by order references. Implements daily UTC rollover for PnL.
    """
    setting_filename: str = SETTING_FILENAME 
    data_filename: str = DATA_FILENAME
    order_filename: str = ORDER_FILENAME
    stats_filename: str = STATS_FILENAME

    contract_results: Dict[Tuple[str, str], ContractResult]

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """Initialize the PortfolioEngine."""
        super().__init__(main_engine, event_engine, APP_NAME)

        # Market Data Access (convenience references)
        self.get_tick: Callable = self.main_engine.get_tick
        self.get_contract: Callable = self.main_engine.get_contract
        self.subscribe: Callable = self.main_engine.subscribe

        # --- State Variables ---
        self.subscribed_symbols: Set[str] = set()
        self.result_symbols: Set[str] = set() # Symbols loaded from data file
        self.order_reference_map: Dict[str, str] = {} # vt_orderid -> reference
        self.contract_results: Dict[Tuple[str, str], ContractResult] = {} # (ref, sym) -> result
        self.portfolio_results: Dict[str, PortfolioResult] = {} # ref -> result
        self.portfolio_statistics: Dict[str, PortfolioStatistics] = {} # ref -> stats

        # --- Timer Settings ---
        self.timer_count: int = 0
        self.timer_interval: int = 60  # Default interval in seconds

        # --- Daily Rollover Tracking ---
        self.current_utc_day: Optional[date] = None # Track current UTC day

        # --- Load Data ---
        # Initialize current_utc_day *before* loading data
        try:
            self.current_utc_day = datetime.now(timezone.utc).date()
            self.write_log(f"Initializing PortfolioEngine for UTC day: {self.current_utc_day}")
        except Exception as e:
            self.write_log(f"Error getting initial UTC date: {e}. Rollover might be affected.", level=logging.ERROR)
            # Proceed cautiously, maybe set current_utc_day later

        self.load_setting()
        self.load_data()
        self.load_order_map()
        self.load_statistics()

        # --- Register Events ---
        self.register_event()
        self.write_log("PortfolioEngine initialized.")

    def register_event(self) -> None:
        """Register event listeners."""
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)
        self.write_log("PortfolioEngine events registered.")

    def unregister_event(self) -> None:
        """Unregister event listeners."""
        self.event_engine.unregister(EVENT_ORDER, self.process_order_event)
        self.event_engine.unregister(EVENT_TRADE, self.process_trade_event)
        self.event_engine.unregister(EVENT_TIMER, self.process_timer_event)
        self.event_engine.unregister(EVENT_CONTRACT, self.process_contract_event)
        self.write_log("PortfolioEngine events unregistered.")


    def process_order_event(self, event: Event) -> None:
        """Process order updates to maintain the vt_orderid -> reference map."""
        try:
            order: OrderData = event.data
            if not isinstance(order, OrderData): return # Basic type check

            # Store reference only if it's available and not already mapped for this order ID
            if order.reference and order.vt_orderid and order.vt_orderid not in self.order_reference_map:
                self.order_reference_map[order.vt_orderid] = order.reference
            # If already mapped, ensure the order object gets the reference back (if missing)
            elif order.vt_orderid and order.vt_orderid in self.order_reference_map and not order.reference:
                 order.reference = self.order_reference_map[order.vt_orderid]

        except Exception:
            self.write_log(f"Error processing order event: {traceback.format_exc()}", level=logging.ERROR)


    def process_trade_event(self, event: Event) -> None:
        """Process new trades, update ContractResult, and subscribe to ticks if needed."""
        try:
            trade: TradeData = event.data
            if not isinstance(trade, TradeData): return

            # Find the portfolio reference associated with this trade's order
            reference: Optional[str] = self.order_reference_map.get(trade.vt_orderid)
            if not reference:
                self.write_log(f"Trade {trade.vt_tradeid} ({trade.vt_symbol}) has no reference in order map, ignoring.", level=logging.DEBUG)
                return

            trade.reference = reference # Add reference to trade data

            # --- Update Contract Result ---
            key: Tuple[str, str] = (reference, trade.vt_symbol)
            contract_result: Optional[ContractResult] = self.contract_results.get(key)

            if not contract_result:
                self.write_log(f"First trade for {trade.vt_symbol} in portfolio '{reference}'. Creating ContractResult.", level=logging.INFO)
                # Position starts at 0.0 if not loaded from file previously.
                contract_result = ContractResult(reference, trade.vt_symbol, open_pos=0.0)
                self.contract_results[key] = contract_result
                self.result_symbols.add(trade.vt_symbol) # Track symbols with active results

            contract_result.update_trade(trade)
            self.write_log(f"Updated trade {trade.vt_tradeid} for {key}. New Last Pos: {contract_result.last_pos}", level=logging.DEBUG)

            # --- Emit Enriched Trade Event ---
            self.event_engine.put(Event(EVENT_PM_TRADE, trade))

            # --- Auto-Subscribe to Ticks ---
            self._subscribe_if_needed(trade.vt_symbol)

        except Exception:
            self.write_log(f"Error processing trade event: {traceback.format_exc()}", level=logging.ERROR)


    def _subscribe_if_needed(self, vt_symbol: str) -> None:
        """Subscribe to tick data for a symbol if not already subscribed."""
        if vt_symbol in self.subscribed_symbols:
            return

        contract: Optional[ContractData] = self.get_contract(vt_symbol)
        if not contract:
            self.write_log(f"Cannot subscribe to tick: Contract details not found for {vt_symbol}.", level=logging.WARNING)
            return

        try:
            # Check if gateway_name exists, required for subscribe
            if not contract.gateway_name:
                 self.write_log(f"Cannot subscribe to {vt_symbol}: ContractData missing gateway_name.", level=logging.ERROR)
                 return

            self.write_log(f"Attempting to subscribe to {vt_symbol} on gateway {contract.gateway_name}", level=logging.INFO)
            req = SubscribeRequest(symbol=contract.symbol, exchange=contract.exchange)
            self.subscribe(req, contract.gateway_name)
            # Assuming subscription is successful - vnpy doesn't have direct confirmation?
            self.subscribed_symbols.add(vt_symbol)
            self.write_log(f"Subscription request sent for {vt_symbol}.", level=logging.INFO)
        except Exception:
             self.write_log(f"Error subscribing to {vt_symbol}: {traceback.format_exc()}", level=logging.ERROR)


    def process_timer_event(self, event: Event) -> None:
        """Periodically trigger PnL calculation and portfolio updates, handling daily rollover."""
        # --- Check for Daily Rollover (UTC) ---
        # Ensure current_utc_day is set
        if self.current_utc_day is None:
             try:
                  self.current_utc_day = datetime.now(timezone.utc).date()
                  self.write_log(f"Initialized current_utc_day on timer event: {self.current_utc_day}", level=logging.WARNING)
             except Exception as e:
                  self.write_log(f"Could not set current_utc_day in timer: {e}. Rollover disabled until resolved.", level=logging.ERROR)
                  return # Cannot proceed without knowing the current day

        try:
            now_utc = datetime.now(timezone.utc)
            today_utc: date = now_utc.date()

            if today_utc != self.current_utc_day:
                self.write_log(f"UTC day change detected: {self.current_utc_day} -> {today_utc}. Performing daily rollover.", level=logging.INFO)
                self._perform_daily_rollover(self.current_utc_day) # Pass previous day
                self.current_utc_day = today_utc # Update tracked day *after* rollover successful
        except Exception:
             self.write_log(f"Error during daily rollover check/execution: {traceback.format_exc()}", level=logging.ERROR)
             # Continue with PnL calculation for the *previous* day's state? Or skip?
             # Let's skip PnL calculation this cycle if rollover failed.
             return

        # --- Regular Timer Processing ---
        self.timer_count += 1
        if self.timer_count < self.timer_interval:
            return
        self.timer_count = 0

        # Record timestamp for statistics (use consistent timezone, e.g., local or UTC)
        # Let's use local time for consistency with typical chart times unless specified otherwise
        record_dt: datetime = datetime.now()
        self.write_log(f"Timer triggered PnL calculation at {record_dt} (Local Time)", level=logging.DEBUG)

        # --- Reset Portfolio Aggregators ---
        for portfolio_result in self.portfolio_results.values():
            portfolio_result.clear_pnl_and_value()

        # --- Calculate PnL for Each Contract ---
        active_contracts = list(self.contract_results.keys()) # Iterate over copy in case dict changes
        for key in active_contracts:
            contract_result = self.contract_results.get(key)
            if not contract_result: continue # Should not happen if using copy, but safe

            reference, vt_symbol = key

            # Fetch necessary market data
            tick: Optional[TickData] = self.get_tick(vt_symbol)
            contract: Optional[ContractData] = self.get_contract(vt_symbol)

            # Validate data needed for calculation
            if not contract:
                self.write_log(f"[{reference}|{vt_symbol}] Skipping PnL calculation: Contract data missing.", level=logging.WARNING)
                continue
            if not tick:
                self.write_log(f"[{reference}|{vt_symbol}] Skipping PnL calculation: Tick data missing this interval.", level=logging.DEBUG)
                continue

            # Calculate PnL for the individual contract
            try:
                pnl_calculated: bool = contract_result.calculate_pnl(tick, contract)
                #print(f"Calculated PnL for {key}: {contract_result.trading_pnl}, {contract_result.holding_pnl}, {contract_result.total_pnl}")
            except Exception:
                 self.write_log(f"Error calculating PnL for {key}: {traceback.format_exc()}", level=logging.ERROR)
                 pnl_calculated = False


            if pnl_calculated:
                # --- Aggregate into Portfolio Result ---
                try:
                    portfolio_result: PortfolioResult = self.get_portfolio_result(reference)
                    portfolio_result.trading_pnl += contract_result.trading_pnl
                    portfolio_result.holding_pnl += contract_result.holding_pnl
                    portfolio_result.total_pnl += contract_result.total_pnl
                    portfolio_result.value += contract_result.value
                except Exception:
                    self.write_log(f"Error aggregating results for portfolio {reference}: {traceback.format_exc()}", level=logging.ERROR)
                    continue # Skip event emission if aggregation fails

                # --- Emit Contract Update Event ---
                contract_data = contract_result.get_data()
                event_contract_update = Event(EVENT_PM_CONTRACT, contract_data)
                self.event_engine.put(event_contract_update)


        # --- Update Statistics and Emit Portfolio Events ---
        active_portfolios = list(self.portfolio_results.keys())
        for reference in active_portfolios:
            portfolio_result = self.portfolio_results.get(reference)
            if not portfolio_result: continue

            # --- Record Statistics ---
            try:
                portfolio_statistics: PortfolioStatistics = self.get_portfolio_statistics(reference)
                total_value = portfolio_result.get_total_value()
                portfolio_statistics.record_value(record_dt, total_value) # Use consistent timestamp
            except Exception:
                 self.write_log(f"Error recording statistics for portfolio {reference}: {traceback.format_exc()}", level=logging.ERROR)
                 # Continue to emit other events

            # --- Emit Portfolio Update Event ---
            portfolio_data = portfolio_result.get_data()
            event_portfolio_update = Event(EVENT_PM_PORTFOLIO, portfolio_data)
            self.event_engine.put(event_portfolio_update)

            # --- Emit Statistics Update Event ---
            try:
                # Fetch statistics object again in case it was created above
                portfolio_statistics: PortfolioStatistics = self.get_portfolio_statistics(reference)
                stats_data = portfolio_statistics.get_statistics() # Get calculated stats
                event_stats_update = Event(EVENT_PM_STATISTICS, stats_data)
                self.event_engine.put(event_stats_update)
            except Exception:
                 self.write_log(f"Error getting/emitting statistics for portfolio {reference}: {traceback.format_exc()}", level=logging.ERROR)


    def _perform_daily_rollover(self, previous_utc_day: Optional[date]) -> None:
        """
        Executes the daily rollover process for all contracts at UTC midnight transition.
        Updates open positions, sets new price basis, resets intra-day counters.
        """
        self.write_log(f"Executing daily rollover process for end of UTC day: {previous_utc_day}", level=logging.INFO)

        rollover_success_count = 0
        contracts_to_rollover = list(self.contract_results.items()) # Iterate over copy

        for key, contract_result in contracts_to_rollover:
            vt_symbol = contract_result.vt_symbol
            reference = contract_result.reference
            try:
                # Get the price basis for the new day (previous day's close)
                # Strategy: Use the pre_close field from the *current* tick data.
                tick: Optional[TickData] = self.get_tick(vt_symbol)
                previous_close_price: Optional[float] = None

                # Determine previous close price using fallbacks
                if tick and tick.pre_close and isinstance(tick.pre_close, (float, int)) and tick.open_price > 0:
                    previous_close_price = tick.pre_close
                elif tick and tick.last_price and isinstance(tick.last_price, (float, int)):
                    previous_close_price = tick.last_price
                    self.write_log(f"[{reference}|{vt_symbol}] Rollover using current last_price ({previous_close_price}) as prev close basis (pre_close missing/invalid).", level=logging.WARNING)
                elif contract_result.last_known_price != 0.0:
                    previous_close_price = contract_result.last_known_price
                    self.write_log(f"[{reference}|{vt_symbol}] Rollover using last known price ({previous_close_price}) as prev close basis (tick missing).", level=logging.WARNING)
                else:
                    self.write_log(f"[{reference}|{vt_symbol}] Cannot determine previous close price for rollover. Skipping rollover.", level=logging.ERROR)
                    continue # Skip rollover for this contract if price is unknown

                # Perform the rollover in the ContractResult object
                contract_result.rollover_day(previous_close_price)
                rollover_success_count += 1

            except Exception:
                self.write_log(f"Error during rollover for contract {key}: {traceback.format_exc()}", level=logging.ERROR)

        self.write_log(f"Daily rollover attempted. Successfully rolled over {rollover_success_count} / {len(contracts_to_rollover)} contracts.", level=logging.INFO)

        # Save data *after* iterating through all contracts to persist new open_pos
        self.save_data()

        # Optional: Clear daily order reference map? Only if references shouldn't persist across days.
        # self.order_reference_map.clear()
        # self.write_log("Cleared daily order reference map after rollover.")
        # Let's keep it for now, save_order_map handles daily file saving.


    def process_contract_event(self, event: Event) -> None:
        """Subscribe to ticks for contracts relevant to loaded results upon receiving contract data."""
        try:
            contract: ContractData = event.data
            if not isinstance(contract, ContractData): return
            # If this contract is part of our results (loaded from file), subscribe
            if contract.vt_symbol in self.result_symbols:
                self._subscribe_if_needed(contract.vt_symbol)
        except Exception:
             self.write_log(f"Error processing contract event: {traceback.format_exc()}", level=logging.ERROR)


    # --- Data Persistence ---

    def _load_json_file(self, filename: str) -> Optional[dict]:
        """Helper to load JSON with existence check and error handling."""
        if not os.path.exists(filename):
             self.write_log(f"File not found: {filename}", level=logging.WARNING)
             return None
        try:
            data = load_json(filename)
            if not isinstance(data, dict): # Ensure it's a dictionary
                 self.write_log(f"Failed to load valid JSON dictionary from {filename}. Found type: {type(data)}", level=logging.ERROR)
                 return None
            return data
        except Exception:
            self.write_log(f"Error loading or parsing JSON from {filename}: {traceback.format_exc()}", level=logging.ERROR)
            return None

    def _save_json_file(self, filename: str, data: dict) -> bool:
        """Helper to save JSON with error handling."""
        try:
            save_json(filename, data)
            self.write_log(f"Saved data to {filename}", level=logging.DEBUG)
            return True
        except Exception:
             self.write_log(f"Failed to save data to {filename}: {traceback.format_exc()}", level=logging.ERROR)
             return False


    def load_data(self) -> None:
        """Load last known positions from the data file."""
        data = self._load_json_file(self.data_filename)
        if not data:
            return

        # Use LOCAL date for comparing saved file date
        file_date_str: str = data.pop(DATE_KEY, "") # Use pop to remove date from items iteration
        today_local_str: str = date.today().strftime("%Y-%m-%d") # Local date
        local_date_changed: bool = (file_date_str != today_local_str)

        self.write_log(f"Loading portfolio data from file dated {file_date_str} (local). Today (local): {today_local_str}. Local date changed: {local_date_changed}", level=logging.INFO)

        loaded_count = 0
        invalid_keys = 0
        # Now data only contains contract entries
        for key_str, contract_data in data.items():
            if not isinstance(contract_data, dict):
                self.write_log(f"Skipping invalid data entry for key '{key_str}' (not a dict): {contract_data}", level=logging.WARNING)
                invalid_keys += 1
                continue
            try:
                # Robust key splitting
                parts = key_str.split(",", 1)
                if len(parts) != 2:
                     self.write_log(f"Skipping invalid key format '{key_str}' in {self.data_filename}", level=logging.WARNING)
                     invalid_keys += 1
                     continue
                reference, vt_symbol = parts

                # Determine initial open_pos based on LOCAL date change detection
                if local_date_changed:
                    # New local day: yesterday's last position is today's initial position
                    initial_pos: float = float(contract_data.get(LAST_POS_KEY, 0.0))
                else:
                    # Same local day: use the saved open position
                    initial_pos: float = float(contract_data.get(OPEN_POS_KEY, 0.0))

                # Create ContractResult instance
                result = ContractResult(reference, vt_symbol, initial_pos)
                self.contract_results[(reference, vt_symbol)] = result
                self.result_symbols.add(vt_symbol)
                loaded_count += 1

            except (ValueError, KeyError, TypeError) as e:
                 self.write_log(f"Error parsing contract data for key '{key_str}': {e} - Data: {contract_data}", level=logging.ERROR)
                 invalid_keys += 1
            except Exception:
                 self.write_log(f"Unexpected error parsing contract data for key '{key_str}': {traceback.format_exc()}", level=logging.ERROR)
                 invalid_keys += 1

        self.write_log(f"Loaded {loaded_count} contract results. Skipped {invalid_keys} invalid entries.", level=logging.INFO)

        # Re-save data if local date changed to update the date marker in the file
        if local_date_changed and loaded_count > 0: # Only save if something was loaded
            self.save_data()


    def save_data(self) -> None:
        """Save current open and last positions using LOCAL date marker."""
        data_to_save: Dict[str, Any] = {DATE_KEY: date.today().strftime("%Y-%m-%d")}

        for contract_result in self.contract_results.values():
            key: str = f"{contract_result.reference},{contract_result.vt_symbol}"
            data_to_save[key] = {
                OPEN_POS_KEY: contract_result.open_pos,
                LAST_POS_KEY: contract_result.last_pos
                # Persist open_price_basis? Only useful if restarting mid-UTC-day.
                # "open_price_basis": contract_result.open_price_basis
            }
        self._save_json_file(self.data_filename, data_to_save)


    def load_setting(self) -> None:
        """Load engine settings (e.g., timer interval)."""
        setting = self._load_json_file(self.setting_filename)
        if setting and TIMER_INTERVAL_KEY in setting:
            try:
                interval = int(setting[TIMER_INTERVAL_KEY])
                if interval > 0:
                    self.timer_interval = interval
                    self.write_log(f"Loaded timer interval: {self.timer_interval} seconds.", level=logging.INFO)
                else:
                     self.write_log(f"Invalid timer_interval in settings ({interval}), using default {self.timer_interval}.", level=logging.ERROR)
            except (ValueError, TypeError):
                 self.write_log(f"Invalid timer_interval format in settings ({setting[TIMER_INTERVAL_KEY]}), using default {self.timer_interval}.", level=logging.ERROR)
        else:
             self.write_log(f"Portfolio settings file missing or invalid, using default timer_interval: {self.timer_interval}.", level=logging.INFO)


    def save_setting(self) -> None:
        """Save current engine settings."""
        setting: Dict[str, int] = {TIMER_INTERVAL_KEY: self.timer_interval}
        self._save_json_file(self.setting_filename, setting)


    def load_order_map(self) -> None:
        """Load the order ID to reference map for the current LOCAL day."""
        order_data = self._load_json_file(self.order_filename)
        if not order_data:
            return

        file_date_str: str = order_data.get(DATE_KEY, "")
        today_local_str: str = date.today().strftime("%Y-%m-%d") # Compare with local date

        if file_date_str == today_local_str:
            loaded_map = order_data.get(DATA_KEY, {})
            if isinstance(loaded_map, dict):
                 self.order_reference_map = loaded_map
                 self.write_log(f"Loaded {len(self.order_reference_map)} order references for today (local date: {today_local_str}).", level=logging.INFO)
            else:
                 self.write_log(f"Invalid format for order reference data in {self.order_filename}, expected dict.", level=logging.ERROR)
                 self.order_reference_map = {}
        else:
            self.write_log(f"Order reference map file is from a previous date ({file_date_str}), starting fresh map for today ({today_local_str}).", level=logging.INFO)
            self.order_reference_map = {} # Discard old map


    def save_order_map(self) -> None:
        """Save the current order ID to reference map using LOCAL date marker."""
        order_data: Dict[str, Any] = {
            DATE_KEY: date.today().strftime("%Y-%m-%d"),
            DATA_KEY: self.order_reference_map
        }
        self._save_json_file(self.order_filename, order_data)


    def load_statistics(self) -> None:
        """Load persisted portfolio statistics data."""
        stats_data_all = self._load_json_file(self.stats_filename)
        if not stats_data_all:
            return

        count = 0
        invalid_refs = 0
        for reference, saved_data in stats_data_all.items():
             if not isinstance(saved_data, dict):
                 self.write_log(f"Skipping invalid statistics data for reference '{reference}' (not a dict).", level=logging.WARNING)
                 invalid_refs += 1
                 continue
             try:
                 stats = PortfolioStatistics.from_saved_data(reference, saved_data)
                 self.portfolio_statistics[reference] = stats
                 count += 1
             except Exception as e:
                  self.write_log(f"Error loading statistics for portfolio '{reference}': {e}", level=logging.ERROR)
                  invalid_refs +=1

        self.write_log(f"Loaded statistics data for {count} portfolios. Skipped {invalid_refs} invalid entries.", level=logging.INFO)


    def save_statistics(self) -> None:
        """Save current portfolio statistics value data."""
        data_to_save: Dict[str, Dict[str, float]] = {}
        for reference, stats in self.portfolio_statistics.items():
            try:
                 data_to_save[reference] = stats.get_data_for_save()
            except Exception:
                 self.write_log(f"Error getting statistics data for saving portfolio {reference}: {traceback.format_exc()}", level=logging.ERROR)

        if data_to_save: # Only save if there's data
             self._save_json_file(self.stats_filename, data_to_save)


    # --- Engine Lifecycle ---

    def close(self) -> None:
        """Stop the engine, unregister events, and save all data."""
        self.write_log("Stopping PortfolioEngine...", level=logging.INFO)
        self.unregister_event()
        # Save data in reverse order of loading dependency? Not strictly necessary here.
        self.save_setting()
        self.save_data()
        self.save_order_map()
        self.save_statistics()
        self.write_log("PortfolioEngine stopped and all data saved.", level=logging.INFO)

    # --- Helper Methods ---

    def get_portfolio_result(self, reference: str) -> PortfolioResult:
        """Get or create a PortfolioResult instance for a given reference."""
        portfolio_result = self.portfolio_results.get(reference)
        if not portfolio_result:
            self.write_log(f"Creating new PortfolioResult for reference: {reference}", level=logging.INFO)
            portfolio_result = PortfolioResult(reference)
            self.portfolio_results[reference] = portfolio_result
        return portfolio_result

    def get_portfolio_statistics(self, reference: str) -> PortfolioStatistics:
        """Get or create a PortfolioStatistics instance for a given reference."""
        portfolio_statistics = self.portfolio_statistics.get(reference)
        if not portfolio_statistics:
            self.write_log(f"Creating new PortfolioStatistics for reference: {reference}", level=logging.INFO)
            portfolio_statistics = PortfolioStatistics(reference)
            self.portfolio_statistics[reference] = portfolio_statistics
        return portfolio_statistics

    # --- Public Control Methods ---

    def set_timer_interval(self, interval: int) -> None:
        """Set the PnL calculation timer interval in seconds."""
        try:
            interval = int(interval)
            if interval > 0:
                self.timer_interval = interval
                self.write_log(f"Timer interval set to {interval} seconds.", level=logging.INFO)
                self.save_setting() # Persist change immediately
            else:
                 self.write_log(f"Invalid timer interval: {interval}. Must be a positive integer.", level=logging.ERROR)
        except (ValueError, TypeError):
             self.write_log(f"Invalid timer interval type: {interval}. Must be an integer.", level=logging.ERROR)


    def get_timer_interval(self) -> int:
        """Get the current timer interval."""
        return self.timer_interval

    def write_log(self, msg: str, level: int = logging.INFO) -> None:
        """Write log message using the standard logger and optionally vnpy's event log."""

        # Optionally, still push to vnpy's log event system if required by UI
        try:
            log_event = Event(EVENT_LOG, LogData(msg=msg, gateway_name=APP_NAME, level=level))
            self.event_engine.put(log_event)
        except Exception as e:
             # Log error about event system failure but don't crash
             logger.error(f"Failed to put log message onto vnpy event bus: {e}")